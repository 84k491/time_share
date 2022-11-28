#pragma once

#include <cstdint>

class IPrinter
{
public:
    virtual ~IPrinter() = default;
    virtual void print(uint64_t local, uint64_t received, int32_t diff) = 0;
};
