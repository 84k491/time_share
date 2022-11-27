#include "i_listener.h"
#include "message.h"
#include "signal_handler.h"

#include <arpa/inet.h>
#include <array>
#include <atomic>
#include <functional>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <tuple>
#include <unistd.h>

class UdpListener final : public IListener
{
public:
    UdpListener(unsigned port);
    ~UdpListener() override;

private:
    std::tuple<int, const void *, size_t> obtain_data() override;

private:
    int m_sockfd = {};
    sockaddr_in address = {};
    std::array<char, 1024> m_data = {};
};
