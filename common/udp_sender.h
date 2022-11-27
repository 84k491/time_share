#pragma once

#include "i_sender.h"

#include <netinet/in.h>

class UdpSender final : public ISender
{
public:
    UdpSender(unsigned port);
    UdpSender(const UdpSender &) = delete;
    UdpSender(UdpSender &&) = delete;
    UdpSender & operator=(const UdpSender &) = delete;
    UdpSender & operator=(UdpSender &&) = delete;
    ~UdpSender() override;

    bool is_ready() const override { return m_is_ready; }
    int send(const void * data, size_t size) override;

private:
    bool m_is_ready = false;
    int m_sockfd = {};
    sockaddr_in cliaddr = {};
};
