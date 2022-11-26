#include "signal_handler.h"
#include <iostream>
#include "udp_sender.h"
#include "timestamp_factory.h"
#include "timer.h"

int main(int, char **)
{
    UdpSender sender;
    Timer timer;
    OneShotSignalHandler signal_handler([&timer](auto) { timer.stop(); });

    timer.start([&]() {
        const auto ts = TimestampFactory::get_timestamp_ms();
        Message msg;
        msg.set_timestamp(ts);
        msg.fill_verification_header();
        if (!msg.verify()) {
            std::cout << "Message is not valid on seding" << std::endl;
        }
        std::cout << "Sending timestamp: " << ts << std::endl;
        sender.send(msg);
    }, std::chrono::milliseconds(100));

    std::cout << "Graceful stop" << std::endl;
    return 0;
}
