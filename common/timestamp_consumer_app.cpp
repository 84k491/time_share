#include "timestamp_consumer_app.h"

TimestampConsumerApp::TimestampConsumerApp(unsigned port)
    : m_listener([this](const void * data, size_t size){
        const auto * msg_ptr = MessageDecoder::decode(data, size);
        if (!msg_ptr) {
            return;
        }
        on_message_received(*msg_ptr);
    }, port)
    , m_signal_handler([this](int) { m_listener.stop(); })
{
}

int TimestampConsumerApp::work()
{
    if (!m_listener.is_ready()) {
        std::cout << "Listener is not ready. Stopping" << std::endl;
        return -1;
    }

    m_listener.listen_loop();
    return 0;
}

void TimestampConsumerApp::on_message_received(const Message & msg) const
{
    const auto local_ts = TimestampFactory::get_timestamp_ms();
    const auto recevied_ts = msg.timestamp();
    std::cout << "Local timestamp   : " << local_ts << std::endl;
    std::cout << "Recevied timestamp: " << recevied_ts << std::endl;
    std::cout << "Difference        : " << local_ts - recevied_ts << std::endl;
    std::cout << "-------" << std::endl;
}
