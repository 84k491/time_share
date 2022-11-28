#include "timer.h"

#include <thread>

int Timer::work(std::function<int()> callback, std::chrono::milliseconds interval, size_t limit)
{
    int rc = 0;
    auto timepoint = std::chrono::ceil<std::chrono::milliseconds>(std::chrono::steady_clock::now());
    size_t count = 0;
    while ((!m_need_to_stop.load() || 0 == rc) &&
           ((0 == limit) != limit > count)) {
        ++count;
        timepoint += interval;
        std::this_thread::sleep_until(timepoint);
        rc = callback();
    }
    return rc;
}

void Timer::on_signal(int)
{
    m_need_to_stop.store(true);
}
