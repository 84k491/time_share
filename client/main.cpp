#include "timestamp_consumer_app.h"
#include "udp_listener.h"

#include <iostream>

int main(int, char **)
{
    UdpListener listener(45163);
    TimestampConsumerApp app(listener);
    int rc = app.work();
    std::cout << "Graceful stop" << std::endl;
    return rc;
}
