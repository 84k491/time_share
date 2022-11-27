#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include <atomic>
#include <functional>
#include <array>
#include <iostream>
#include <tuple>

#include "message.h"
#include "signal_handler.h"
#include "i_listener.h"

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
