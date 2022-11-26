#include <iostream>
#include "../common/udp_listener.h"
#include "signal_handler.h"

int main(int, char **)
{
    OneShotSignalHandler::block_signals();

    UdpListener listener;
    if (!listener.is_ready()) {
        return -1;
    }

    listener.listen_loop([](const void * data, size_t size) {
        const auto * msg_ptr = MessageDecoder::decode(data, size);
        if (!msg_ptr) {
            std::cout << "Wrong message received!" << std::endl;
            return;
        }
        const auto & msg = *msg_ptr;
        std::cout << "Message received!. Value: " << msg.timestamp() << std::endl;
    });

    std::cout << "End" << std::endl;
    return 0;
}
