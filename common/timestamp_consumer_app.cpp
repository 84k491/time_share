#include "timestamp_consumer_app.h"

#include "i_listener.h"
#include "message.h"

#include <iostream>

TimestampConsumerApp::TimestampConsumerApp(IListener & listener)
    : m_listener(listener)
    , m_signal_handler(m_listener)
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
        const auto * msg_ptr = decode(data, size);
        if (nullptr == msg_ptr) {
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

const Message * TimestampConsumerApp::decode(const void * data, size_t size)
{
    if (size != Message::size()) {
        return nullptr;
    }
    const auto * msg = reinterpret_cast<const Message *>(data);
    if (!msg->verify()) {
        return nullptr;
    }
    return msg;
}
