#include <chrono>
#include <atomic>
#include <functional>

class Timer
{
public:
    void start(std::function<void()> callback, std::chrono::microseconds interval)
    {
        auto timepoint = std::chrono::steady_clock::now();
        while (!m_need_to_stop.load()) {
            timepoint += interval;
            std::this_thread::sleep_until(timepoint);
            callback();
        }
    }

    void stop()
    {
        m_need_to_stop.store(true);
    }

private:
    std::atomic_bool m_need_to_stop = false;
};
