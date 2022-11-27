#pragma once

#include "i_signal_controllable.h"

#include <atomic>
#include <functional>

class IListener : public ISignalControllable
{
public:
    IListener() = default;
    ~IListener() override = default;

    // TODO rename callback
    void set_callback(std::function<void(const void *, size_t)> callback)
    {
        m_callback = callback;
    }

    // TODO move to CPP
    void listen_loop()
    {
        if (!m_is_ready) {
            return;
        }

        while (!m_need_to_stop.load()) {
            const auto [rc, data, size] = obtain_data();
            if (rc != 0) {
                break;
            }
            m_callback(data, size);
        }
    }

    bool is_ready() const { return m_is_ready; }

    void on_signal(int) override
    {
        m_need_to_stop.store(true);
    }

protected:
    virtual std::tuple<int, const void *, size_t> obtain_data() = 0;

    bool m_is_ready = false;
    std::atomic_bool m_need_to_stop = false;
    std::function<void(const void *, size_t)> m_callback;
};
