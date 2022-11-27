#pragma once

#include "i_listener.h"
#include "signal_handler.h"

#include <array>
#include <netinet/in.h>

class UdpListener final : public IListener
{
public:
    UdpListener(unsigned port);
    UdpListener(const UdpListener&) = delete;
    UdpListener(UdpListener&&) = delete;
    UdpListener & operator=(const UdpListener&) = delete;
    UdpListener & operator=(UdpListener&&) = delete;
    ~UdpListener() override;

private:
    std::tuple<int, const void *, size_t> obtain_data() override;

private:
    int m_sockfd = {};
    sockaddr_in address = {};
    std::array<char, 1024> m_data = {};
};
