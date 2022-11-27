#include "udp_listener.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <tuple>

UdpListener::UdpListener(unsigned port)
{
    if ((m_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cout << "Socket creating failed" << std::endl;
        return;
    }
    const int enable = 1;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        std::cout << "Setting REUSEADDR failed" << std::endl;
        return;
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_BROADCAST;

    if (int rc = bind(
                m_sockfd,
                reinterpret_cast<const struct sockaddr *>(&address),
                sizeof(address));
        rc < 0) {
        std::cout << "Binding on port " << port << " failed! rc: " << rc << std::endl;
        return;
    }

    m_is_ready = true;
    std::cout << "Client is listening on port " << port << std::endl;
}

UdpListener::~UdpListener()
{
    if (0 != m_sockfd) {
        close(m_sockfd);
    }
}

std::tuple<int, const void *, size_t> UdpListener::obtain_data()
{
    struct timeval timeout = {1, 0};

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(m_sockfd, &readSet);

    if (select(m_sockfd + 1, &readSet, nullptr, nullptr, &timeout) >= 0) {
        if (FD_ISSET(m_sockfd, &readSet) > 0) {
            int len = 0;
            int bytes_received = recvfrom(
                    m_sockfd,
                    m_data.data(),
                    m_data.size(),
                    MSG_WAITALL,
                    reinterpret_cast<struct sockaddr *>(&address),
                    reinterpret_cast<socklen_t *>(&len));
            if (bytes_received > 0) {
                return {0, m_data.data(), bytes_received};
            }
        }
        return {0, nullptr, 0};
    }

    return {-1, nullptr, 0};
}
