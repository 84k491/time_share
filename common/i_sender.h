#pragma once

#include <cstddef>

class ISender
{
public:
    virtual ~ISender() = default;

    virtual int send(const void * data, size_t size) = 0;
    virtual bool is_ready() const = 0;                    // TODO just move it here, no need to override it
};
