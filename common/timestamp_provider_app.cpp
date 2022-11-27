#include "timestamp_provider_app.h"

#include "message.h"

TimestampProviderApp::TimestampProviderApp(ISender & sender)
    : m_sender(sender)
    , m_signal_handler([this](auto) { m_timer.stop(); })
{
}

int TimestampProviderApp::work()
{
    return m_timer.work(
            [this]() -> int {
                const auto ts = TimestampFactory::get_timestamp_ms();
                Message msg;
                msg.set_timestamp(ts);
                msg.fill_verification_header();
                if (!msg.verify()) {
                    std::cout << "Message is not valid on seding" << std::endl;
                    return -1;
                }
                if (m_do_printout) {
                    std::cout << "Sending timestamp: " << ts << std::endl;
                }
                return m_sender.send(msg.data(), Message::size());
            },
            sendind_interval,
            m_iterations_limit);
}

void TimestampProviderApp::set_iterations_limit(size_t iterations_limit)
{
    m_iterations_limit = iterations_limit;
}
