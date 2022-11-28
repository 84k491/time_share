#pragma once

#include "i_sender.h"
#include "signal_handler.h"
#include "timer.h"
#include "timestamp_factory.h"

#include <iostream>

namespace test {
class EndToEndTest;
class ProviderTest;
} // namespace test

class TimestampProviderApp
{
    static constexpr auto sendind_interval = std::chrono::milliseconds(100);

public:
    TimestampProviderApp(ISender & sender);
    int work();

private:
    friend class test::EndToEndTest;
    friend class test::ProviderTest;
    void set_iterations_limit(size_t m_iterations_limit);

private:
    size_t m_iterations_limit = 0;
    bool m_do_printout = true;
    ISender & m_sender;
    Timer m_timer;
    OneShotSignalHandler m_signal_handler;
};
