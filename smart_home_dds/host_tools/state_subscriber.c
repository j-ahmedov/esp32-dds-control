// state_subscriber.c — host XRCE subscriber for device_state (Phase D telemetry).
// Connects to the same agent and prints the ESP32's live state as it arrives.
//   usage: state_subscriber <agent_ip> <port>   (Ctrl-C to stop)

#include "smart_home.h"
#include <uxr/client/client.h>
#include <ucdr/microcdr.h>
#include <stdio.h>
#include <stdlib.h>

#define STREAM_HISTORY 8
#define BUFFER_SIZE    (UXR_CONFIG_UDP_TRANSPORT_MTU * STREAM_HISTORY)

static void on_state(uxrSession* s, uxrObjectId oid, uint16_t rid, uxrStreamId sid,
                     struct ucdrBuffer* ub, uint16_t len, void* args)
{
    (void)s; (void)oid; (void)rid; (void)sid; (void)len; (void)args;
    smart_home_DeviceState st;
    smart_home_DeviceState_deserialize_topic(ub, &st);
    printf("device_state:  LED1=%-3u  LED2=%-3u  servo=%u deg\n", st.led1, st.led2, st.servo_angle);
    fflush(stdout);
}

int main(int argc, char** argv)
{
    if (argc < 3) { printf("usage: %s <agent_ip> <port>\n", argv[0]); return 1; }
    const char* ip = argv[1]; const char* port = argv[2];

    uxrUDPTransport transport;
    if (!uxr_init_udp_transport(&transport, UXR_IPv4, ip, port)) { printf("transport err\n"); return 1; }
    uxrSession session;
    uxr_init_session(&session, &transport.comm, 0x57A7E123);   // distinct client key
    uxr_set_topic_callback(&session, on_state, NULL);
    if (!uxr_create_session(&session)) { printf("agent unreachable %s:%s\n", ip, port); return 1; }

    uint8_t ob[BUFFER_SIZE], ibuf[BUFFER_SIZE];
    uxrStreamId out = uxr_create_output_reliable_stream(&session, ob, BUFFER_SIZE, STREAM_HISTORY);
    uxrStreamId in  = uxr_create_input_reliable_stream(&session, ibuf, BUFFER_SIZE, STREAM_HISTORY);

    uxrObjectId participant = uxr_object_id(0x01, UXR_PARTICIPANT_ID);
    uint16_t rp = uxr_buffer_create_participant_xml(&session, out, participant, 0,
        "<dds><participant><rtps><name>state_monitor</name></rtps></participant></dds>", UXR_REPLACE);
    uxrObjectId topic = uxr_object_id(0x01, UXR_TOPIC_ID);
    uint16_t rt = uxr_buffer_create_topic_xml(&session, out, topic, participant,
        "<dds><topic><name>device_state</name><dataType>smart_home::DeviceState</dataType></topic></dds>", UXR_REPLACE);
    uxrObjectId sub = uxr_object_id(0x01, UXR_SUBSCRIBER_ID);
    uint16_t rs = uxr_buffer_create_subscriber_xml(&session, out, sub, participant, "<dds><subscriber/></dds>", UXR_REPLACE);
    uxrObjectId dr = uxr_object_id(0x01, UXR_DATAREADER_ID);
    uint16_t rd = uxr_buffer_create_datareader_xml(&session, out, dr, sub,
        "<dds><data_reader><topic><kind>NO_KEY</kind><name>device_state</name>"
        "<dataType>smart_home::DeviceState</dataType></topic></data_reader></dds>", UXR_REPLACE);

    uint16_t reqs[4] = { rp, rt, rs, rd }; uint8_t stt[4];
    if (!uxr_run_session_until_all_status(&session, 1000, reqs, stt, 4)) {
        printf("entity create failed: p=%d t=%d s=%d r=%d\n", stt[0], stt[1], stt[2], stt[3]); return 1;
    }
    uxrDeliveryControl ctrl = { .max_samples = UXR_MAX_SAMPLES_UNLIMITED };
    uxr_buffer_request_data(&session, out, dr, in, &ctrl);
    uxr_flash_output_streams(&session);

    printf("listening for device_state (Ctrl-C to stop)...\n");
    while (true) {
        uxr_run_session_timeout(&session, 500);
    }
    return 0;
}
