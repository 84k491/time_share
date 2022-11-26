#include "udp_sender.h"
#include <iostream>

UdpSender::UdpSender()
{
    unsigned to_port = 45163; // TODO remove hardcode

    // Creating socket file descriptor
    if ((m_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      std::cout << "Socket creating failed" << std::endl;
      return;
    }

    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
        
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = INADDR_ANY;
    cliaddr.sin_port = htons(to_port);

    // if (bind(m_sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
      // std::cout << "Binding on port " << local_port << " failed" << std::endl;
      // return;
    // }
    // std::cout << "Socket " << m_sockfd << " binded" << std::endl;
    std::cout << "Server active" << std::endl;
}

bool UdpSender::send(const Message & msg)
{
    // std::cout << "sending msg to " << cliaddr.sin_addr.s_addr << "; port: " << cliaddr.sin_port << std::endl;
    if (int rc = sendto(m_sockfd, msg.data(), msg.size(), 0,
        (const sockaddr *)&cliaddr, sizeof(cliaddr)); rc > 0) {
        // std::cout << "Message sent. rc: " << rc << std::endl;
        return true;
    }

    std::cout << "Sending failed" << std::endl;
    return false;
}

UdpSender::~UdpSender()
{
    close(m_sockfd); // TODO check if inited
    std::cout << "Socket " << m_sockfd << " closed" << std::endl;
}
