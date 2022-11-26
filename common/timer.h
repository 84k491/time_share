#include <chrono>
#include <atomic>
#include <functional>

class Timer
{
public:
    int work(std::function<int()> callback, std::chrono::microseconds interval, size_t limit = 0)
    {
        int rc = 0;
        auto timepoint = std::chrono::steady_clock::now();
        size_t count = 0;
        while (!m_need_to_stop.load() || 0 == rc || ((0 == limit) != limit > count)) {
            ++count;
            timepoint += interval;
            std::this_thread::sleep_until(timepoint);
            rc = callback();
        }
        return rc;
    }

    void stop()
    {
        m_need_to_stop.store(true);
    }

private:
    std::atomic_bool m_need_to_stop = false;
};
