#include <iostream>
#include "udp_listener.h"
#include "signal_handler.h"
#include "timestamp_factory.h"

class TimestampConsumerApp
{
public:
    TimestampConsumerApp(unsigned port);
    int work();

private:
    void on_message_received(const Message & msg) const;

private:
    UdpListener m_listener;
    OneShotSignalHandler m_signal_handler;
};

