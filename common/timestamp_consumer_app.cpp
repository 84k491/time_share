#include "timestamp_consumer_app.h"

#include "i_listener.h"
#include "message.h"
#include "printer.h"

#include <iostream>


TimestampConsumerApp::TimestampConsumerApp(IListener & listener)
    : m_listener(listener)
    , m_printer(std::make_unique<Printer>())
    , m_signal_handler(m_listener)
{
    m_on_msg_received = [this](const Message & msg) {
        if (!m_printer) {
            return;
        }
        const auto local_ts = TimestampFactory::get_timestamp_ms();
        const auto recevied_ts = msg.timestamp();
        m_printer->print(local_ts, recevied_ts, local_ts - recevied_ts);
    };

    listener.set_on_data_received([this](const void * data, size_t size) {
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
