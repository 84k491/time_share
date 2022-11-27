#pragma once

#include <chrono>
#include <cstdint>
#include <iostream>

class TimestampFactory
{
public:
    static uint64_t get_timestamp_ms()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                .count();
    }
};
