// rti_publisher.cxx — RTI Connext publisher for the smart_home device.
// Publishes on led_cmd / servo_cmd (domain 0), same IDL/type as the ESP32 device.
//   usage: rti_publisher led   <id 1|2> <brightness 0..255>
//          rti_publisher servo <angle 0..180>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <dds/dds.hpp>
#include "smart_home.hpp"

int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cout << "usage:\n"
                  << "  rti_publisher led   <id 1|2> <brightness 0..255>\n"
                  << "  rti_publisher servo <angle 0..180>\n";
        return 1;
    }
    const std::string kind = argv[1];

    // macOS: disable the built-in shared-memory transport (its default limits are
    // too small and stale segments accumulate); use UDPv4 only. RTI <-> agent talk
    // over the network anyway, so there is no downside.
    dds::domain::qos::DomainParticipantQos pqos =
        dds::core::QosProvider::Default().participant_qos();
    pqos.policy<rti::core::policy::TransportBuiltin>().mask(
        rti::core::policy::TransportBuiltinMask::udpv4());
    dds::domain::DomainParticipant participant(0, pqos);
    dds::pub::Publisher publisher(participant);
    dds::pub::qos::DataWriterQos wqos = publisher.default_datawriter_qos();
    wqos << dds::core::policy::Reliability::Reliable()
         << dds::core::policy::Durability::TransientLocal();   // late-joiner gets last cmd

    if (kind == "led") {
        if (argc < 4) { std::cout << "led needs <id> <brightness>\n"; return 1; }
        dds::topic::Topic<smart_home::LedCommand> topic(participant, "led_cmd");
        dds::pub::DataWriter<smart_home::LedCommand> writer(publisher, topic, wqos);
        smart_home::LedCommand cmd;
        cmd.id = (uint16_t)std::atoi(argv[2]);           // public fields
        cmd.brightness = (uint16_t)std::atoi(argv[3]);
        for (int i = 0; i < 5; ++i) {   // repeat a few times for reliable delivery
            writer.write(cmd);
            std::cout << "LED" << cmd.id << " -> " << cmd.brightness << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } else if (kind == "servo") {
        dds::topic::Topic<smart_home::ServoCommand> topic(participant, "servo_cmd");
        dds::pub::DataWriter<smart_home::ServoCommand> writer(publisher, topic, wqos);
        smart_home::ServoCommand cmd;
        cmd.angle = (uint16_t)std::atoi(argv[2]);
        for (int i = 0; i < 5; ++i) {
            writer.write(cmd);
            std::cout << "SERVO -> " << cmd.angle << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } else {
        std::cout << "unknown kind '" << kind << "'\n"; return 1;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(300));  // let last sample flush
    return 0;
}
