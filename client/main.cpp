#include <iostream>
#include "../common/udp_listener.h"

int main(int, char **)
{
    UdpListener listener;
    if (!listener.is_ready()) {
        return -1;
    }

    listener.listen([](const void * data, size_t size) {
        const auto * msg = MessageDecoder::decode(data, size);
        if (!msg) {
            std::cout << "Wrong message received!" << std::endl;
            return;
        }
        std::cout << "Message received!" << std::endl;
    });
    return 0;
}
