#include "signal_handler.h"
#include <iostream>
#include "udp_sender.h"
#include "timestamp_factory.h"
#include "timer.h"

class TimestampProviderApp
{
public:
    TimestampProviderApp(unsigned port)
        : m_sender(port)
        , m_signal_handler([this](auto) { m_timer.stop(); })
    {
    }

    void work()
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

private:
    UdpSender m_sender;
    Timer m_timer;
    OneShotSignalHandler m_signal_handler;
};

int main(int, char **)
{
    TimestampProviderApp app(45163);
    app.work();
    std::cout << "Graceful stop" << std::endl;
    return 0;
}
