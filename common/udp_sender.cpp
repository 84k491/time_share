#include "udp_sender.h"
#include <iostream>

UdpSender::UdpSender(unsigned port)
{
    // Creating socket file descriptor
    if ((m_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      std::cout << "Socket creation failed" << std::endl;
      return;
    }

    int turn_on = 1;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_BROADCAST, &turn_on, (socklen_t)sizeof(turn_on)) < 0) {
        std::cout << "Can't set up broadcast" << std::endl;
        return;
    }

    memset(&cliaddr, 0, sizeof(cliaddr)); 
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = INADDR_BROADCAST;
    cliaddr.sin_port = htons(port);
    m_is_ready = true;
}

int UdpSender::send(const void * data, size_t size)
{
    int rc = -1;
    if (rc = sendto(
        m_sockfd,
        data,
        size,
        0,
        reinterpret_cast<const sockaddr *>(&cliaddr),
        sizeof(cliaddr)); rc < 0) {
        std::cout << "Sending failed" << std::endl;
    }
    return rc;
}

UdpSender::~UdpSender()
{
    close(m_sockfd); // TODO check if inited
    std::cout << "Socket " << m_sockfd << " closed" << std::endl;
}
