#include "signal_handler.h"
#include <iostream>
#include "udp_sender.h"
#include "timestamp_factory.h"
#include "timer.h"

class TimestampProviderApp
{
public:
    TimestampProviderApp(unsigned port);
    int work();
    void set_iterations_limit(size_t m_iterations_limit);

private:
    size_t m_iterations_limit = 0;
    UdpSender m_sender;
    Timer m_timer;
    OneShotSignalHandler m_signal_handler;
};

