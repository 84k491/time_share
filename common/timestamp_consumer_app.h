#include <iostream>
#include "signal_handler.h"
#include "timestamp_factory.h"

class Message;
class IListener;
namespace test {
class ConsumerTest;
class EndToEndTest;
}

class TimestampConsumerApp
{
public:
    TimestampConsumerApp(IListener & listener);
    int work();

private:
    static const Message * decode(const void * data, size_t size);

private:
    friend class test::ConsumerTest;
    friend class test::EndToEndTest;
    std::function<void(const Message & msg)> m_on_msg_received;

    IListener & m_listener;
    OneShotSignalHandler m_signal_handler;
};

