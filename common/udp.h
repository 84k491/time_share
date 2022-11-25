#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <array>
#include <functional>

class Message
{
public:
    Message() {}

    void set_timestamp(uint64_t) {}

    const void * data() const { return m_data.data(); }
    size_t size() const { return m_data.size(); }

private:
    std::array<char, 64> m_data;
};

class UdpSender
{
public:
    UdpSender();
    ~UdpSender();
    // TODO other ctors = delete

    bool send(const Message & msg);

private:
    int m_sockfd = {};
    sockaddr_in servaddr;
    sockaddr_in cliaddr;
};

class UdpListener
{
public:
    UdpListener();
    ~UdpListener();

    bool listen(std::function<void(const Message &)> callback);

private:
    int m_sockfd = {};
    sockaddr_in address;
    char buffer[1024]; 
};
