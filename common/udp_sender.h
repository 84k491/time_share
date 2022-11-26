#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include <message.h>

class UdpSender
{
public:
    UdpSender(unsigned port);
    ~UdpSender();
    // TODO other ctors = delete

    bool send(const Message & msg);

private:
    int m_sockfd = {};
    sockaddr_in cliaddr;
};
