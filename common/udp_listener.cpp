#include "udp_listener.h"
#include <iostream>

UdpListener::UdpListener()
    : m_signal_handler([this](int) {
        std::cout << "Callback called!" << std::endl;
        m_need_to_stop.store(true);
    })
{
    unsigned port = 45163;

    if ((m_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cout << "Socket creating failed" << std::endl;
        return;
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    if (int rc = bind(m_sockfd, (const struct sockaddr *)&address, sizeof(address)); rc < 0) {
        std::cout << "Binding on port " << port << " failed! rc: " << rc << std::endl;
        return;
    }

    m_is_ready = true;
    std::cout << "Client is listening on port " << port << std::endl;
}

UdpListener::~UdpListener()
{
    close(m_sockfd);
    std::cout << "Socket " << m_sockfd << " closed" << std::endl;
}

void UdpListener::listen_loop(std::function<void(const void *, size_t)> callback)
{
    if (!m_is_ready) {
        return;
    }
    // int len = 0;
    // int bytes_received = recvfrom(m_sockfd, m_data.data(), m_data.size(), MSG_WAITALL,
        // (struct sockaddr *)&address, (socklen_t *)&len);

    while(!m_need_to_stop)
    {
       struct timeval timeout = {1, 0};
 
       fd_set readSet;
       FD_ZERO(&readSet);
       FD_SET(m_sockfd, &readSet);
 
       if (select(m_sockfd+1, &readSet, NULL, NULL, &timeout) >= 0)
       {
          if (FD_ISSET(m_sockfd, &readSet))
          {
             int len = 0;
             int bytes_received = recvfrom(m_sockfd, m_data.data(), m_data.size(), MSG_WAITALL,
                 (struct sockaddr *)&address, (socklen_t *)&len);
             callback(m_data.data(), bytes_received);
          }
       }
       else {
            std::cout << "some error" << std::endl;
        }
    }
    std::cout << "Stop listening" << std::endl;
}
