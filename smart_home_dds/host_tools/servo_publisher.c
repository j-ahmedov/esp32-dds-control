// servo_publisher.c — host XRCE publisher for servo_cmd (smart_home::ServoCommand).
// Same pattern as led_publisher.c; drives the servo on the ESP32 (GPIO 13).
//   usage: servo_publisher <agent_ip> <port> <angle 0..180> [repeat]
//          servo_publisher <agent_ip> <port> --sweep

#include "smart_home.h"
#include <uxr/client/client.h>
#include <ucdr/microcdr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STREAM_HISTORY 8
#define BUFFER_SIZE    (UXR_CONFIG_UDP_TRANSPORT_MTU * STREAM_HISTORY)

static void publish_angle(uxrSession* s, uxrStreamId out, uxrObjectId dw, uint16_t angle)
{
    smart_home_ServoCommand cmd; cmd.angle = angle;
    ucdrBuffer ub;
    uxr_prepare_output_stream(s, out, dw, &ub, smart_home_ServoCommand_size_of_topic(&cmd, 0));
    smart_home_ServoCommand_serialize_topic(&ub, &cmd);
    printf("  SERVO -> %u\n", angle);
    uxr_run_session_time(s, 250);
}

int main(int argc, char** argv)
{
    if (argc < 4) {
        printf("usage: %s <agent_ip> <port> <angle 0..180> [repeat]\n", argv[0]);
        printf("       %s <agent_ip> <port> --sweep\n", argv[0]);
        return 1;
    }
    const char* ip = argv[1]; const char* port = argv[2];
    int sweep = (strcmp(argv[3], "--sweep") == 0);

    uxrUDPTransport transport;
    if (!uxr_init_udp_transport(&transport, UXR_IPv4, ip, port)) { printf("transport err\n"); return 1; }
    uxrSession session;
    uxr_init_session(&session, &transport.comm, 0x5E60A011);
    if (!uxr_create_session(&session)) { printf("agent unreachable %s:%s\n", ip, port); return 1; }

    uint8_t ob[BUFFER_SIZE], ibuf[BUFFER_SIZE];
    uxrStreamId out = uxr_create_output_reliable_stream(&session, ob, BUFFER_SIZE, STREAM_HISTORY);
    uxr_create_input_reliable_stream(&session, ibuf, BUFFER_SIZE, STREAM_HISTORY);

    uxrObjectId participant = uxr_object_id(0x01, UXR_PARTICIPANT_ID);
    uint16_t rp = uxr_buffer_create_participant_xml(&session, out, participant, 0,
        "<dds><participant><rtps><name>servo_publisher</name></rtps></participant></dds>", UXR_REPLACE);
    uxrObjectId topic = uxr_object_id(0x01, UXR_TOPIC_ID);
    uint16_t rt = uxr_buffer_create_topic_xml(&session, out, topic, participant,
        "<dds><topic><name>servo_cmd</name><dataType>smart_home::ServoCommand</dataType></topic></dds>", UXR_REPLACE);
    uxrObjectId pub = uxr_object_id(0x01, UXR_PUBLISHER_ID);
    uint16_t rpub = uxr_buffer_create_publisher_xml(&session, out, pub, participant, "", UXR_REPLACE);
    uxrObjectId dw = uxr_object_id(0x01, UXR_DATAWRITER_ID);
    uint16_t rdw = uxr_buffer_create_datawriter_xml(&session, out, dw, pub,
        "<dds><data_writer><topic><kind>NO_KEY</kind><name>servo_cmd</name>"
        "<dataType>smart_home::ServoCommand</dataType></topic></data_writer></dds>", UXR_REPLACE);

    uint16_t reqs[4] = { rp, rt, rpub, rdw }; uint8_t st[4];
    if (!uxr_run_session_until_all_status(&session, 1000, reqs, st, 4)) {
        printf("entity create failed: p=%d t=%d pub=%d dw=%d\n", st[0], st[1], st[2], st[3]); return 1;
    }
    printf("entities ready; publishing on servo_cmd (domain 0)\n");

    if (sweep) {
        for (int a = 0; a <= 180; a += 30) publish_angle(&session, out, dw, (uint16_t)a);
        for (int a = 180; a >= 0; a -= 30) publish_angle(&session, out, dw, (uint16_t)a);
    } else {
        uint16_t angle = (uint16_t)atoi(argv[3]);
        int repeat = (argc >= 5) ? atoi(argv[4]) : 3;
        for (int i = 0; i < repeat; ++i) publish_angle(&session, out, dw, angle);
    }

    uxr_delete_session(&session);
    uxr_close_udp_transport(&transport);
    printf("done\n");
    return 0;
}
