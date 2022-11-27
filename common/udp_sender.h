#pragma once

#include "i_sender.h"

#include <arpa/inet.h>
#include <message.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class UdpSender final : public ISender
{
public:
    UdpSender(unsigned port);
    UdpSender(const UdpSender&) = delete;
    UdpSender(UdpSender&&) = delete;
    UdpSender & operator=(const UdpSender&) = delete;
    UdpSender & operator=(UdpSender&&) = delete;
    ~UdpSender() override;

    bool is_ready() const override { return m_is_ready; }
    int send(const void * data, size_t size) override;

private:
    bool m_is_ready = false;
    int m_sockfd = {};
    sockaddr_in cliaddr = {};
};
