#include <iostream>
#include "../common/udp.h"

int main(int, char **)
{
    UdpListener listener;
    listener.listen([](const Message &) {
        std::cout << "Message received!" << std::endl;
    });
    return 0;
}
