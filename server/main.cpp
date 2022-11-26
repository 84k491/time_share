#include <iostream>
#include "../common/udp_sender.h"
#include "timestamp_factory.h"

int main(int, char **)
{
    UdpSender sender;
    Message msg;
    const auto ts = TimestampFactory::get_timestamp_ms();
    std::cout << "Sending timestamp: " << ts << std::endl;
    msg.set_timestamp(ts);
    msg.fill_verification_header();
    if (!msg.verify()) {
        std::cout << "Messages did not verified" << std::endl;
    }
    sender.send(msg);
    return 0;
}
