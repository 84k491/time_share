#include <iostream>
#include "../common/udp_listener.h"
#include "signal_handler.h"
#include "timestamp_factory.h"

class TimestampConsumerApp
{
public:
    TimestampConsumerApp()
        : m_signal_handler([this](int) { m_listener.stop(); })
    {
    }

    int work()
    {
        if (!m_listener.is_ready()) {
            std::cout << "Listener is not ready. Stopping" << std::endl;
            return -1;
        }

        m_listener.listen_loop([this](const void * data, size_t size) {
            const auto * msg_ptr = MessageDecoder::decode(data, size);
            if (!msg_ptr) {
                return;
            }
            on_message_received(*msg_ptr);
        });
        return 0;
    }

private:
    void on_message_received(const Message & msg) const
    {
        const auto local_ts = TimestampFactory::get_timestamp_ms();
        const auto recevied_ts = msg.timestamp();
        std::cout << "Local timestamp   : " << local_ts << std::endl;
        std::cout << "Recevied timestamp: " << recevied_ts << std::endl;
        std::cout << "Difference        : " << local_ts - recevied_ts << std::endl;
        std::cout << "-------" << std::endl;
    }

private:
    UdpListener m_listener;
    OneShotSignalHandler m_signal_handler;
};

int main(int, char **)
{
    TimestampConsumerApp app;
    int rc = app.work();
    std::cout << "Graceful stop" << std::endl;
    return rc;
}
