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

#include <message.h>
#include "signal_handler.h"

class MessageDecoder
{
public:
    static const Message * decode(const void * data, size_t size)
    {
        if (size != Message::size()) {
            std::cout << "Received size = " << size << std::endl;
            return nullptr;
        }
        const auto * msg = reinterpret_cast<const Message *>(data);
        if (!msg->verify()) {
            msg->print();
            std::cout << "message not verified" << std::endl;
            return nullptr;
        }
        return msg;
    }
};

class UdpListener
{
public:
    UdpListener();
    ~UdpListener();

    void listen_loop(std::function<void(const void *, size_t)> callback);
    bool is_ready() const { return m_is_ready; }
    void stop();

private:
    int m_sockfd = {};
    sockaddr_in address;
    std::array<char, 1024> m_data;
    bool m_is_ready = false;
    std::atomic_bool m_need_to_stop = false;
};
