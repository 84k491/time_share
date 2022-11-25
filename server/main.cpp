#include <iostream>
#include "../common/udp_sender.h"

int main(int, char **)
{
    UdpSender sender;
    Message msg;
    msg.fill_verification_header();
    if (!msg.verify()) {
        std::cout << "Messages did not verified" << std::endl;
    }
    sender.send(msg);
    return 0;
}
