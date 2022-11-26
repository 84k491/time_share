#include <chrono>
#include <atomic>
#include <functional>

class Timer
{
public:
    void start(std::function<void()> callback, std::chrono::microseconds interval)
    {
        while (!m_need_to_stop.load()) {
            std::this_thread::sleep_for(interval);
            callback();
        }
    }

    void stop()
    {
        m_need_to_stop.store(true);
    }

private:
    std::atomic_bool m_need_to_stop = false;
    std::function<void()> m_callback;
};
