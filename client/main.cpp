#include <iostream>
#include "../common/udp_listener.h"
#include "signal_handler.h"
#include "timestamp_factory.h"

int main(int, char **)
{
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
        const auto local_ts = TimestampFactory::get_timestamp_ms();
        const auto recevied_ts = msg.timestamp();
        std::cout << "Local timestamp   : " << local_ts << std::endl;
        std::cout << "Recevied timestamp: " << recevied_ts << std::endl;
        std::cout << "Difference        : " << local_ts - recevied_ts << std::endl;
        std::cout << "-------" << std::endl;
    });

    std::cout << "Graceful stop" << std::endl;
    return 0;
}
