#pragma once

#include "i_signal_controllable.h"

#include <atomic>
#include <functional>

class IListener : public ISignalControllable
{
public:
    IListener() = default;
    ~IListener() override = default;

    void set_on_data_received(std::function<void(const void *, size_t)> callback);
    void listen_loop();
    bool is_ready() const { return m_is_ready; }

    void on_signal(int) override;

protected:
    virtual std::tuple<int, const void *, size_t> obtain_data() = 0;

    bool m_is_ready = false;
    std::atomic_bool m_need_to_stop = false;
    std::function<void(const void *, size_t)> m_on_data_received;
};
