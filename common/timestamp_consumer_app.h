#include <iostream>
#include "signal_handler.h"
#include "timestamp_factory.h"
#include "message_decoder.h"

class Message;
class IListener;

class TimestampConsumerApp
{
public:
    TimestampConsumerApp(IListener & listener);
    int work();

private:
    void on_message_received(const Message & msg) const;

private:
    IListener & m_listener;
    OneShotSignalHandler m_signal_handler;
};

