#include "signal_handler.h"
#include <iostream>
#include "i_sender.h"
#include "timestamp_factory.h"
#include "timer.h"

namespace test {
class SenderTest;
}

class TimestampProviderApp
{
    friend class test::SenderTest;
public:
    TimestampProviderApp(ISender & sender);
    int work();

private:
    void set_iterations_limit(size_t m_iterations_limit);

private:
    size_t m_iterations_limit = 0;
    ISender & m_sender;
    Timer m_timer;
    OneShotSignalHandler m_signal_handler;
};

