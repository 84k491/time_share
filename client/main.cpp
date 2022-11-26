#include <iostream>
#include "../common/udp_listener.h"
#include <csignal> // TODO remove

int main(int, char **)
{
    sigset_t signals;
    sigemptyset(&signals);
    sigaddset(&signals, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &signals, nullptr);

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
