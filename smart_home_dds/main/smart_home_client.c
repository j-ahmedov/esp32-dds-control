// smart_home_client.c — ESP32-S3 Micro XRCE-DDS client (subscriber)
//
// Two build modes, switched by SMART_HOME_BENCH_TEST below:
//   1 (default) -> PHASE A: no networking, no XRCE, no generated types.
//                  app_main just exercises the hardware (LEDs fade, servo sweeps).
//                  Compiles against ONLY the IDF driver/wifi/nvs components.
//   0           -> PHASE B: full XRCE client. Requires you to have:
//                    - generated smart_home.{h,c} via `microxrceddsgen smart_home.idl`
//                    - vendored Micro-XRCE-DDS-Client under ../components/
//                    - added both to main/CMakeLists.txt (see notes there)
//                  Then DIFF the uxr_* calls against your client version's
//                  examples/SubscribeHelloWorldClient/main.c (API drifts v2.x<->v3.x).

#define SMART_HOME_BENCH_TEST 0

// Hardware isolation test: no Wi-Fi, no DDS, no PWM for LEDs — just raw digital
// on/off blink on the LED pins + a basic servo sweep. Set to 1 to diagnose wiring.
#define SMART_HOME_GPIO_TEST  0

// Onboard RGB LED (WS2812) test: blink the DevKitC-1's built-in LED. Confirms the
// board + flash pipeline with ZERO external wiring. Set to 1 to run.
#define SMART_HOME_RGB_TEST   0

// Continuous servo sweep test: no network. Sweeps servo 0<->180 forever + blinks
// LED1 as an "alive" heartbeat. For testing servo wiring by plug/unplug. Set to 1.
#define SMART_HOME_SERVO_TEST 0

// GPIO13 raw-digital blink test: drives GPIO13 (the servo pin) as a plain on/off
// output so an LED moved to pin 13 blinks. Confirms the pin works. Set to 1.
#define SMART_HOME_PIN13_TEST 0
#define RGB_LED_GPIO          48    // DevKitC-1 onboard WS2812 (try 38 if 48 is dark)

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "driver/mcpwm_prelude.h"   // servo via MCPWM (independent of LEDC)
#if SMART_HOME_RGB_TEST
#include "led_strip.h"
#endif

#include "wifi_sta.h"   // wifi_init_sta()

#if !SMART_HOME_BENCH_TEST
#include <uxr/client/client.h>
#include <ucdr/microcdr.h>
#include "smart_home.h"   // generated: microxrceddsgen smart_home.idl
#endif

static const char *TAG = "smarthome";

// ----------------------- user config -----------------------
#define WIFI_SSID   "Fenomeno"         // matches your current Arduino build
#define WIFI_PASS   "flash1234"
#define AGENT_IP    "172.20.10.14"     // Mac running the Micro XRCE-DDS Agent (this Wi-Fi)
#define AGENT_PORT  "8888"
#define DDS_DOMAIN  0                  // MUST equal the RTI participant's domain

// Pins reconciled to your real wiring (from src/main.cpp): 11 / 12 / 13.
#define LED1_GPIO   11
#define LED2_GPIO   12
#define SERVO_GPIO  9    // moved from 13: pin proven to drive this servo (Arduino test)

// ----------------------- LEDC / PWM ------------------------
// LEDs share one timer (5 kHz, 13-bit). Servo gets its own 50 Hz, 16-bit timer.
#define LMODE        LEDC_LOW_SPEED_MODE
#define LED_TIMER    LEDC_TIMER_0
#define LED_RES      LEDC_TIMER_13_BIT      // duty 0..8191
#define LED1_CH      LEDC_CHANNEL_0
#define LED2_CH      LEDC_CHANNEL_1
#define SERVO_TIMER  LEDC_TIMER_1
#define SERVO_RES    LEDC_TIMER_14_BIT      // duty 0..16383 over a 20 ms period (S3 LEDC max is 14-bit)
#define SERVO_FULL   16383u                  // 2^14 - 1
#define SERVO_CH     LEDC_CHANNEL_2

// Servo on MCPWM: 1 MHz tick (1 tick = 1 us), 20 ms period = 50 Hz.
// Pulse 500 us (0deg) .. 2500 us (180deg). Comparator value = pulse width in us.
#define SERVO_MIN_US   544    // 0deg — matches Arduino Servo lib (avoids pegging the stop)
#define SERVO_MAX_US   2400   // 180deg — tune these two per your servo if angles are off
#define SERVO_PERIOD_US 20000
static mcpwm_cmpr_handle_t servo_cmp = NULL;

static void servo_mcpwm_init(void)
{
    mcpwm_timer_handle_t timer = NULL;
    mcpwm_timer_config_t tcfg = {
        .group_id = 0, .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = 1000000, .period_ticks = SERVO_PERIOD_US,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP };
    ESP_ERROR_CHECK(mcpwm_new_timer(&tcfg, &timer));

    mcpwm_oper_handle_t oper = NULL;
    mcpwm_operator_config_t ocfg = { .group_id = 0 };
    ESP_ERROR_CHECK(mcpwm_new_operator(&ocfg, &oper));
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, timer));

    mcpwm_comparator_config_t ccfg = { .flags.update_cmp_on_tez = true };
    ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &ccfg, &servo_cmp));

    mcpwm_gen_handle_t gen = NULL;
    mcpwm_generator_config_t gcfg = { .gen_gpio_num = SERVO_GPIO };
    ESP_ERROR_CHECK(mcpwm_new_generator(oper, &gcfg, &gen));

    mcpwm_comparator_set_compare_value(servo_cmp, 1500);   // center
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(gen,
        MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(gen,
        MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, servo_cmp, MCPWM_GEN_ACTION_LOW)));

    ESP_ERROR_CHECK(mcpwm_timer_enable(timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP));
    ESP_LOGI(TAG, "servo MCPWM ready on GPIO%d (50Hz, 500-2500us)", SERVO_GPIO);
}

static void pwm_init(void)
{
    // LEDs via LEDC (unchanged).
    ledc_timer_config_t led_t = {
        .speed_mode = LMODE, .timer_num = LED_TIMER, .duty_resolution = LED_RES,
        .freq_hz = 5000, .clk_cfg = LEDC_AUTO_CLK };
    ledc_timer_config(&led_t);
    ledc_channel_config_t c1 = { .gpio_num = LED1_GPIO, .speed_mode = LMODE,
        .channel = LED1_CH, .timer_sel = LED_TIMER, .duty = 0, .hpoint = 0 };
    ledc_channel_config_t c2 = { .gpio_num = LED2_GPIO, .speed_mode = LMODE,
        .channel = LED2_CH, .timer_sel = LED_TIMER, .duty = 0, .hpoint = 0 };
    ledc_channel_config(&c1);
    ledc_channel_config(&c2);

    // Servo via MCPWM (not LEDC).
    servo_mcpwm_init();
}

static void apply_led(ledc_channel_t ch, uint16_t brightness)
{
    if (brightness > 255) brightness = 255;
    uint32_t duty = (uint32_t)brightness * 8191u / 255u;   // 8-bit -> 13-bit
    ledc_set_duty(LMODE, ch, duty);
    ledc_update_duty(LMODE, ch);
}

static void apply_servo(uint16_t angle)
{
    if (angle > 180) angle = 180;
    uint32_t us = SERVO_MIN_US + ((uint32_t)(SERVO_MAX_US - SERVO_MIN_US) * angle) / 180;
    if (servo_cmp) mcpwm_comparator_set_compare_value(servo_cmp, us);
}

#if SMART_HOME_BENCH_TEST
// -------- PHASE A: prove the hardware with no network at all. --------
static void bench_loop(void)
{
    ESP_LOGI(TAG, "BENCH TEST: LED1=%d LED2=%d SERVO=%d", LED1_GPIO, LED2_GPIO, SERVO_GPIO);
    while (true) {
        // Fade LED1 up while LED2 fades down, then sweep the servo 0->180->0.
        for (int b = 0; b <= 255; b += 5) {
            apply_led(LED1_CH, b);
            apply_led(LED2_CH, 255 - b);
            vTaskDelay(pdMS_TO_TICKS(20));
        }
        for (int a = 0; a <= 180; a += 5) { apply_servo(a); vTaskDelay(pdMS_TO_TICKS(20)); }
        for (int b = 255; b >= 0; b -= 5) {
            apply_led(LED1_CH, b);
            apply_led(LED2_CH, 255 - b);
            vTaskDelay(pdMS_TO_TICKS(20));
        }
        for (int a = 180; a >= 0; a -= 5) { apply_servo(a); vTaskDelay(pdMS_TO_TICKS(20)); }
    }
}
#else
// -------- PHASE B: XRCE entity IDs + callback --------
#define LED_DR_ID    0x01
#define SERVO_DR_ID  0x02

// Current device state, mirrored back to the domain as telemetry (Phase D).
static uint16_t g_led1 = 0, g_led2 = 0, g_servo = 90;

// Called by uxr_run_session whenever a sample arrives on a subscribed reader.
static void on_topic(uxrSession *session, uxrObjectId object_id, uint16_t request_id,
                     uxrStreamId stream_id, struct ucdrBuffer *ub, uint16_t length, void *args)
{
    (void)session; (void)request_id; (void)stream_id; (void)length; (void)args;

    if (object_id.id == LED_DR_ID) {
        smart_home_LedCommand cmd;
        smart_home_LedCommand_deserialize_topic(ub, &cmd);
        uint16_t b = cmd.brightness > 255 ? 255 : cmd.brightness;
        if (cmd.id == 1) { apply_led(LED1_CH, b); g_led1 = b; }
        else if (cmd.id == 2) { apply_led(LED2_CH, b); g_led2 = b; }
        ESP_LOGI(TAG, "LED%u -> %u", cmd.id, cmd.brightness);
    } else if (object_id.id == SERVO_DR_ID) {
        smart_home_ServoCommand cmd;
        smart_home_ServoCommand_deserialize_topic(ub, &cmd);
        uint16_t a = cmd.angle > 180 ? 180 : cmd.angle;
        apply_servo(a); g_servo = a;
        ESP_LOGI(TAG, "SERVO -> %u", cmd.angle);
    }
}

static void xrce_run(void)
{
    // v3.x API: the UDP platform is embedded in uxrUDPTransport (no separate
    // uxrUDPPlatform arg — that was the 2.x signature). Pattern copied from
    // examples/SubscribeHelloWorld/main.c in the vendored client.
    uxrUDPTransport transport;
    if (!uxr_init_udp_transport(&transport, UXR_IPv4, AGENT_IP, AGENT_PORT)) {
        ESP_LOGE(TAG, "transport init failed"); return;
    }

    uxrSession session;
    uxr_init_session(&session, &transport.comm, 0xAABBCCDD /* client key */);
    uxr_set_topic_callback(&session, on_topic, NULL);
    if (!uxr_create_session(&session)) {
        ESP_LOGE(TAG, "agent unreachable at %s:%s", AGENT_IP, AGENT_PORT); return;
    }

    // Stream buffers must be big enough to hold ALL buffered entity-creation XML
    // (participant + 2 topics + 2 subscribers + 2 datareaders + 2 data requests)
    // before the flush. The skeleton's 512B/history-1 overflowed and silently
    // dropped the servo reader's creation messages -> servo never subscribed.
    // Size like the eProsima examples: MTU * history.
    #define STREAM_HISTORY 8
    static uint8_t out_buf[UXR_CONFIG_UDP_TRANSPORT_MTU * STREAM_HISTORY];
    static uint8_t in_buf[UXR_CONFIG_UDP_TRANSPORT_MTU * STREAM_HISTORY];
    uxrStreamId out = uxr_create_output_reliable_stream(&session, out_buf, sizeof(out_buf), STREAM_HISTORY);
    uxrStreamId in  = uxr_create_input_reliable_stream(&session, in_buf, sizeof(in_buf), STREAM_HISTORY);

    uxrObjectId participant = uxr_object_id(0x01, UXR_PARTICIPANT_ID);
    uxr_buffer_create_participant_xml(&session, out, participant, DDS_DOMAIN,
        "<dds><participant><rtps><name>smart_home_node</name></rtps></participant></dds>", UXR_REPLACE);

    uxrObjectId led_topic = uxr_object_id(0x01, UXR_TOPIC_ID);
    uxr_buffer_create_topic_xml(&session, out, led_topic, participant,
        "<dds><topic><name>led_cmd</name><dataType>smart_home::LedCommand</dataType></topic></dds>", UXR_REPLACE);
    uxrObjectId led_sub = uxr_object_id(0x01, UXR_SUBSCRIBER_ID);
    uxr_buffer_create_subscriber_xml(&session, out, led_sub, participant, "<dds><subscriber/></dds>", UXR_REPLACE);
    uxrObjectId led_dr = uxr_object_id(LED_DR_ID, UXR_DATAREADER_ID);
    uxr_buffer_create_datareader_xml(&session, out, led_dr, led_sub,
        "<dds><data_reader><topic><kind>NO_KEY</kind><name>led_cmd</name>"
        "<dataType>smart_home::LedCommand</dataType></topic></data_reader></dds>", UXR_REPLACE);

    uxrObjectId sv_topic = uxr_object_id(0x02, UXR_TOPIC_ID);
    uxr_buffer_create_topic_xml(&session, out, sv_topic, participant,
        "<dds><topic><name>servo_cmd</name><dataType>smart_home::ServoCommand</dataType></topic></dds>", UXR_REPLACE);
    uxrObjectId sv_sub = uxr_object_id(0x02, UXR_SUBSCRIBER_ID);
    uxr_buffer_create_subscriber_xml(&session, out, sv_sub, participant, "<dds><subscriber/></dds>", UXR_REPLACE);
    uxrObjectId sv_dr = uxr_object_id(SERVO_DR_ID, UXR_DATAREADER_ID);
    uxr_buffer_create_datareader_xml(&session, out, sv_dr, sv_sub,
        "<dds><data_reader><topic><kind>NO_KEY</kind><name>servo_cmd</name>"
        "<dataType>smart_home::ServoCommand</dataType></topic></data_reader></dds>", UXR_REPLACE);

    // --- Phase D: device_state telemetry publisher ---
    uxrObjectId st_topic = uxr_object_id(0x03, UXR_TOPIC_ID);
    uxr_buffer_create_topic_xml(&session, out, st_topic, participant,
        "<dds><topic><name>device_state</name><dataType>smart_home::DeviceState</dataType></topic></dds>", UXR_REPLACE);
    uxrObjectId st_pub = uxr_object_id(0x01, UXR_PUBLISHER_ID);
    uxr_buffer_create_publisher_xml(&session, out, st_pub, participant, "<dds><publisher/></dds>", UXR_REPLACE);
    uxrObjectId st_dw = uxr_object_id(0x01, UXR_DATAWRITER_ID);
    uxr_buffer_create_datawriter_xml(&session, out, st_dw, st_pub,
        "<dds><data_writer><topic><kind>NO_KEY</kind><name>device_state</name>"
        "<dataType>smart_home::DeviceState</dataType></topic></data_writer></dds>", UXR_REPLACE);

    uxrDeliveryControl ctrl = { .max_samples = UXR_MAX_SAMPLES_UNLIMITED };
    uxr_buffer_request_data(&session, out, led_dr, in, &ctrl);
    uxr_buffer_request_data(&session, out, sv_dr, in, &ctrl);
    uxr_flash_output_streams(&session);

    ESP_LOGI(TAG, "entities created, listening + publishing device_state...");
    int tick = 0;
    while (true) {
        uxr_run_session_timeout(&session, 100);   // pumps callbacks (commands in)
        // Publish device_state ~ once per second.
        if (++tick >= 10) {
            tick = 0;
            smart_home_DeviceState st = { g_led1, g_led2, g_servo };
            ucdrBuffer mb;
            uint32_t sz = smart_home_DeviceState_size_of_topic(&st, 0);
            if (uxr_prepare_output_stream(&session, out, st_dw, &mb, sz)) {
                smart_home_DeviceState_serialize_topic(&mb, &st);
                ESP_LOGI(TAG, "state -> led1=%u led2=%u servo=%u", g_led1, g_led2, g_servo);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
#endif

#if SMART_HOME_GPIO_TEST
// Most fundamental test possible: LEDs driven by RAW digital GPIO (not LEDC/PWM),
// servo by a minimal LEDC channel. No network. Blinks forever so it's easy to watch.
static void gpio_test_loop(void)
{
    gpio_config_t io = {
        .pin_bit_mask = (1ULL << LED1_GPIO) | (1ULL << LED2_GPIO),
        .mode = GPIO_MODE_OUTPUT, .pull_up_en = 0, .pull_down_en = 0, .intr_type = GPIO_INTR_DISABLE };
    gpio_config(&io);

    // Minimal LEDC just for the servo on GPIO 13.
    ledc_timer_config_t sv_t = { .speed_mode = LMODE, .timer_num = SERVO_TIMER,
        .duty_resolution = SERVO_RES, .freq_hz = 50, .clk_cfg = LEDC_AUTO_CLK };
    ledc_timer_config(&sv_t);
    ledc_channel_config_t cs = { .gpio_num = SERVO_GPIO, .speed_mode = LMODE,
        .channel = SERVO_CH, .timer_sel = SERVO_TIMER, .duty = 0, .hpoint = 0 };
    ledc_channel_config(&cs);

    ESP_LOGI(TAG, "GPIO TEST: LED1=GPIO%d LED2=GPIO%d SERVO=GPIO%d (raw blink, no network)",
             LED1_GPIO, LED2_GPIO, SERVO_GPIO);
    int on = 0;
    while (true) {
        on = !on;
        gpio_set_level(LED1_GPIO, on);      // 3.3V when on (active-high assumption)
        gpio_set_level(LED2_GPIO, !on);
        apply_servo(on ? 180 : 0);
        ESP_LOGI(TAG, "TICK: LED1=%d LED2=%d servo=%d", on, !on, on ? 180 : 0);
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}
#endif

#if SMART_HOME_RGB_TEST
// Blink the onboard WS2812 RGB LED: green for ~5s (5 blinks), then off. No wiring.
static void rgb_test(void)
{
    led_strip_handle_t strip = NULL;
    led_strip_config_t strip_cfg = {
        .strip_gpio_num = RGB_LED_GPIO,
        .max_leds = 1,
    };
    led_strip_rmt_config_t rmt_cfg = {
        .resolution_hz = 10 * 1000 * 1000,   // 10 MHz
    };
    esp_err_t err = led_strip_new_rmt_device(&strip_cfg, &rmt_cfg, &strip);
    ESP_LOGI(TAG, "RGB TEST: WS2812 on GPIO%d, new_rmt_device -> %s",
             RGB_LED_GPIO, esp_err_to_name(err));
    if (err != ESP_OK) { while (true) vTaskDelay(pdMS_TO_TICKS(1000)); }

    for (int i = 0; i < 5; ++i) {
        led_strip_set_pixel(strip, 0, 0, 64, 0);   // green (R,G,B)
        led_strip_refresh(strip);
        ESP_LOGI(TAG, "RGB ON  (%d/5)", i + 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        led_strip_clear(strip);
        ESP_LOGI(TAG, "RGB OFF");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    led_strip_clear(strip);
    ESP_LOGI(TAG, "RGB TEST done");
    while (true) vTaskDelay(pdMS_TO_TICKS(1000));
}
#endif

#if SMART_HOME_SERVO_TEST
// Continuous servo sweep, no network. Sweeps 0->180->0 smoothly, forever.
// LED1 (GPIO 11) toggles each pass as a board-alive heartbeat.
static void servo_test_loop(void)
{
    gpio_config_t io = { .pin_bit_mask = (1ULL << LED1_GPIO),
        .mode = GPIO_MODE_OUTPUT, .pull_up_en = 0, .pull_down_en = 0, .intr_type = GPIO_INTR_DISABLE };
    gpio_config(&io);
    int hb = 0;
    ESP_LOGI(TAG, "SERVO SWEEP TEST: continuous 0<->180 on GPIO%d, LED1 heartbeat on GPIO%d",
             SERVO_GPIO, LED1_GPIO);
    while (true) {
        for (int a = 0; a <= 180; a += 3) { apply_servo(a); vTaskDelay(pdMS_TO_TICKS(20)); }
        hb = !hb; gpio_set_level(LED1_GPIO, hb);
        for (int a = 180; a >= 0; a -= 3) { apply_servo(a); vTaskDelay(pdMS_TO_TICKS(20)); }
        hb = !hb; gpio_set_level(LED1_GPIO, hb);
        ESP_LOGI(TAG, "sweep cycle done");
    }
}
#endif

#if SMART_HOME_PIN13_TEST
// Raw digital blink on GPIO13 (servo pin). Put an LED+resistor on pin 13 -> GND.
// If it blinks, GPIO13 works as an output and the servo/its power is the fault.
static void pin13_test_loop(void)
{
    gpio_config_t io = { .pin_bit_mask = (1ULL << SERVO_GPIO),
        .mode = GPIO_MODE_OUTPUT, .pull_up_en = 0, .pull_down_en = 0, .intr_type = GPIO_INTR_DISABLE };
    gpio_config(&io);
    ESP_LOGI(TAG, "PIN13 TEST: raw digital blink on GPIO%d (1s on / 1s off)", SERVO_GPIO);
    int on = 0;
    while (true) {
        on = !on;
        gpio_set_level(SERVO_GPIO, on);
        ESP_LOGI(TAG, "GPIO%d = %d", SERVO_GPIO, on);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
#endif

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());

#if SMART_HOME_PIN13_TEST
    pin13_test_loop();                  // never returns
#elif SMART_HOME_SERVO_TEST
    pwm_init();                         // configures the servo LEDC channel
    servo_test_loop();                  // never returns
#elif SMART_HOME_RGB_TEST
    rgb_test();                         // never returns
#elif SMART_HOME_GPIO_TEST
    gpio_test_loop();                   // never returns
#elif SMART_HOME_BENCH_TEST
    pwm_init();
    bench_loop();                       // never returns
#else
    pwm_init();
    wifi_init_sta(WIFI_SSID, WIFI_PASS);
    xrce_run();
#endif
}
