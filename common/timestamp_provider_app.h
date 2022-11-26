#include "signal_handler.h"
#include <iostream>
#include "udp_sender.h"
#include "timestamp_factory.h"
#include "timer.h"

class TimestampProviderApp
{
public:
    TimestampProviderApp(unsigned port);
    void work();

private:
    UdpSender m_sender;
    Timer m_timer;
    OneShotSignalHandler m_signal_handler;
};

