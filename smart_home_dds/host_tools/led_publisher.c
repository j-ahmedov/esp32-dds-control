// led_publisher.c — a host-side Micro-XRCE-DDS *publisher* client.
//
// It connects to the SAME agent as the ESP32 and publishes smart_home::LedCommand
// on topic "led_cmd" (domain 0). The agent bridges both clients over real DDS, so
// these samples reach the ESP32's led_cmd DataReader and drive the LED.
//
// This is the "eProsima publisher" for Phase C — pure Micro XRCE-DDS, same IDL,
// no Fast-DDS/RTI install required. Build with host_tools/build.sh.
//
//   usage: led_publisher <agent_ip> <port> <led_id 1|2> <brightness 0..255> [repeat]
//          led_publisher <agent_ip> <port> --fade <led_id>     # sweep 0..255..0

#include "smart_home.h"          // generated types (shared with the firmware)

#include <uxr/client/client.h>
#include <ucdr/microcdr.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STREAM_HISTORY 8
#define BUFFER_SIZE    (UXR_CONFIG_UDP_TRANSPORT_MTU * STREAM_HISTORY)

int main(int argc, char** argv)
{
    if (argc < 4) {
        printf("usage: %s <agent_ip> <port> <led_id 1|2> <brightness 0..255> [repeat]\n", argv[0]);
        printf("       %s <agent_ip> <port> --fade <led_id 1|2>\n", argv[0]);
        return 1;
    }
    const char* ip   = argv[1];
    const char* port = argv[2];
    int fade = (strcmp(argv[3], "--fade") == 0);
    uint16_t led_id, brightness = 0;
    int repeat = 3;
    if (fade) {
        led_id = (uint16_t)atoi(argv[4]);
    } else {
        led_id     = (uint16_t)atoi(argv[3]);
        brightness = (uint16_t)atoi(argv[4]);
        if (argc >= 6) repeat = atoi(argv[5]);
    }

    // --- transport + session (same v3.x API as the firmware) ---
    uxrUDPTransport transport;
    if (!uxr_init_udp_transport(&transport, UXR_IPv4, ip, port)) {
        printf("Error: transport init\n"); return 1;
    }
    uxrSession session;
    uxr_init_session(&session, &transport.comm, 0x1A2B3C4D);   // distinct client key
    if (!uxr_create_session(&session)) {
        printf("Error: agent unreachable at %s:%s\n", ip, port); return 1;
    }

    uint8_t out_buf[BUFFER_SIZE], in_buf[BUFFER_SIZE];
    uxrStreamId out = uxr_create_output_reliable_stream(&session, out_buf, BUFFER_SIZE, STREAM_HISTORY);
    uxr_create_input_reliable_stream(&session, in_buf, BUFFER_SIZE, STREAM_HISTORY);

    // --- entities: participant / topic / publisher / datawriter ---
    // Topic name + dataType MUST match the firmware's reader exactly.
    uxrObjectId participant = uxr_object_id(0x01, UXR_PARTICIPANT_ID);
    uint16_t rp = uxr_buffer_create_participant_xml(&session, out, participant, 0,
        "<dds><participant><rtps><name>led_publisher</name></rtps></participant></dds>", UXR_REPLACE);

    uxrObjectId topic = uxr_object_id(0x01, UXR_TOPIC_ID);
    uint16_t rt = uxr_buffer_create_topic_xml(&session, out, topic, participant,
        "<dds><topic><name>led_cmd</name><dataType>smart_home::LedCommand</dataType></topic></dds>", UXR_REPLACE);

    uxrObjectId publisher = uxr_object_id(0x01, UXR_PUBLISHER_ID);
    uint16_t rpub = uxr_buffer_create_publisher_xml(&session, out, publisher, participant, "", UXR_REPLACE);

    uxrObjectId dw = uxr_object_id(0x01, UXR_DATAWRITER_ID);
    uint16_t rdw = uxr_buffer_create_datawriter_xml(&session, out, dw, publisher,
        "<dds><data_writer><topic><kind>NO_KEY</kind><name>led_cmd</name>"
        "<dataType>smart_home::LedCommand</dataType></topic></data_writer></dds>", UXR_REPLACE);

    uint16_t reqs[4] = { rp, rt, rpub, rdw };
    uint8_t  st[4];
    if (!uxr_run_session_until_all_status(&session, 1000, reqs, st, 4)) {
        printf("Error creating entities: p=%d t=%d pub=%d dw=%d\n", st[0], st[1], st[2], st[3]);
        return 1;
    }
    printf("entities ready; publishing on led_cmd (domain 0)\n");

    // --- publish ---
    smart_home_LedCommand cmd;
    if (fade) {
        for (int pass = 0; pass < 2; ++pass) {
            for (int b = 0; b <= 255; b += 15) {
                cmd.id = led_id; cmd.brightness = (uint16_t)b;
                ucdrBuffer ub;
                uxr_prepare_output_stream(&session, out, dw, &ub, smart_home_LedCommand_size_of_topic(&cmd, 0));
                smart_home_LedCommand_serialize_topic(&ub, &cmd);
                printf("  LED%u -> %u\n", cmd.id, cmd.brightness);
                uxr_run_session_time(&session, 120);
            }
            for (int b = 255; b >= 0; b -= 15) {
                cmd.id = led_id; cmd.brightness = (uint16_t)b;
                ucdrBuffer ub;
                uxr_prepare_output_stream(&session, out, dw, &ub, smart_home_LedCommand_size_of_topic(&cmd, 0));
                smart_home_LedCommand_serialize_topic(&ub, &cmd);
                printf("  LED%u -> %u\n", cmd.id, cmd.brightness);
                uxr_run_session_time(&session, 120);
            }
        }
    } else {
        for (int i = 0; i < repeat; ++i) {
            cmd.id = led_id; cmd.brightness = brightness;
            ucdrBuffer ub;
            uxr_prepare_output_stream(&session, out, dw, &ub, smart_home_LedCommand_size_of_topic(&cmd, 0));
            smart_home_LedCommand_serialize_topic(&ub, &cmd);
            printf("  LED%u -> %u\n", cmd.id, cmd.brightness);
            uxr_run_session_time(&session, 300);
        }
    }

    uxr_delete_session(&session);
    uxr_close_udp_transport(&transport);
    printf("done\n");
    return 0;
}
