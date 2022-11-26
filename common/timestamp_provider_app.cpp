#include "timestamp_provider_app.h"


TimestampProviderApp::TimestampProviderApp(unsigned port)
    : m_sender(port)
    , m_signal_handler([this](auto) { m_timer.stop(); })
{
}

void TimestampProviderApp::work()
{
    m_timer.start([this]() {
        const auto ts = TimestampFactory::get_timestamp_ms();
        Message msg;
        msg.set_timestamp(ts);
        msg.fill_verification_header();
        if (!msg.verify()) {
            std::cout << "Message is not valid on seding" << std::endl;
        }
        std::cout << "Sending timestamp: " << ts << std::endl;
        m_sender.send(msg);
    }, std::chrono::milliseconds(100));
}
