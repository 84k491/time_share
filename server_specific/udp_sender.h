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

    int send(const void * data, size_t size) override;

private:
    int m_sockfd = {};
    sockaddr_in cliaddr = {};
};
