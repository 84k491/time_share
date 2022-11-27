#include "i_listener.h"

void IListener::set_on_data_received(std::function<void(const void *, size_t)> callback)
{
    m_on_data_received = callback;
}

void IListener::listen_loop()
{
    if (!m_is_ready) {
        return;
    }

    while (!m_need_to_stop.load()) {
        const auto [rc, data, size] = obtain_data();
        if (rc != 0) {
            break;
        }
        m_on_data_received(data, size);
    }
}

void IListener::on_signal(int)
{
    m_need_to_stop.store(true);
}
