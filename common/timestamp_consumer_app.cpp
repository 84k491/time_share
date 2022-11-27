#include "timestamp_consumer_app.h"
#include "i_listener.h"

TimestampConsumerApp::TimestampConsumerApp(IListener & listener)
    : m_listener(listener)
    , m_signal_handler([this](int) { m_listener.stop(); })
{
    m_on_msg_received = [](const Message & msg) {
        const auto local_ts = TimestampFactory::get_timestamp_ms();
        const auto recevied_ts = msg.timestamp();
        std::cout << "Local timestamp   : " << local_ts << std::endl;
        std::cout << "Recevied timestamp: " << recevied_ts << std::endl;
        std::cout << "Difference        : " << local_ts - recevied_ts << std::endl;
        std::cout << "-------" << std::endl;
    };

    listener.set_callback([this](const void * data, size_t size) {
        const auto * msg_ptr = MessageDecoder::decode(data, size);
        if (!msg_ptr || !msg_ptr->verify()) {
            return;
        }
        m_on_msg_received(*msg_ptr);
    });
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
