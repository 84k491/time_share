#include "i_signal_controllable.h"

#include <atomic>
#include <chrono>
#include <functional>

class Timer : public ISignalControllable
{
public:
    ~Timer() override = default;

    int work(std::function<int()> callback, std::chrono::milliseconds interval, size_t limit = 0);
    void on_signal(int) override;

private:
    std::atomic_bool m_need_to_stop = false;
};
