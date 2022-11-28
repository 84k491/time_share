#pragma once

#include <cstddef>

class ISender
{
public:
    virtual ~ISender() = default;

    virtual int send(const void * data, size_t size) = 0;
    bool is_ready() const { return m_is_ready; }

protected:
    bool m_is_ready = false;
};
