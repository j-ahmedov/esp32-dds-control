// rti_subscriber.cxx — RTI Connext subscriber for device_state telemetry.
// Reads the ESP32's device_state on domain 0 and prints it. Ctrl-C to stop.
#include <iostream>
#include <thread>
#include <chrono>
#include <dds/dds.hpp>
#include "smart_home.hpp"

int main()
{
    // macOS: use UDPv4 only (skip the built-in shared-memory transport, which
    // fails with the default macOS shared-memory limits).
    dds::domain::qos::DomainParticipantQos pqos =
        dds::core::QosProvider::Default().participant_qos();
    pqos.policy<rti::core::policy::TransportBuiltin>().mask(
        rti::core::policy::TransportBuiltinMask::udpv4());
    dds::domain::DomainParticipant participant(0, pqos);
    dds::sub::Subscriber subscriber(participant);
    dds::topic::Topic<smart_home::DeviceState> topic(participant, "device_state");

    dds::sub::qos::DataReaderQos rqos = subscriber.default_datareader_qos();
    rqos << dds::core::policy::Reliability::Reliable();
    dds::sub::DataReader<smart_home::DeviceState> reader(subscriber, topic, rqos);

    std::cout << "RTI subscriber on device_state (domain 0). Ctrl-C to stop..." << std::endl;
    while (true) {
        auto samples = reader.take();
        for (const auto& s : samples) {
            if (s.info().valid()) {
                const auto& d = s.data();
                std::cout << "device_state:  LED1=" << d.led1
                          << "  LED2=" << d.led2
                          << "  servo=" << d.servo_angle << " deg" << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return 0;
}
