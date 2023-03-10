#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

class Message
{
public:
    static constexpr std::string_view s_header = "TMSTP.V1";

    uint64_t timestamp() const { return m_timestamp; }
    void set_timestamp(const uint64_t v) { m_timestamp = v; }

    void fill_verification_header()
    {
        std::copy(s_header.begin(), s_header.end(), m_verification_header.begin());
    }

    bool verify() const
    {
        return std::equal(s_header.begin(), s_header.end(), m_verification_header.begin());
    }

    const void * data() const { return this; }
    static constexpr size_t size() { return sizeof(Message); }

private:
    std::array<char, s_header.size()> m_verification_header;
    uint64_t m_timestamp;
};
