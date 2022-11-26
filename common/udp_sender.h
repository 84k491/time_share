#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include "i_sender.h"

#include <message.h>

class UdpSender final : public ISender
{
public:
    UdpSender(unsigned port);
    ~UdpSender();
    // TODO other ctors = delete

    bool is_ready() const override { return m_is_ready; }
    int send(const Message & msg) override;

private:
    bool m_is_ready = false;
    int m_sockfd = {};
    sockaddr_in cliaddr;
};
