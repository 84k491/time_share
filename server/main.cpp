#include "timestamp_provider_app.h"
#include "udp_sender.h"

#include <iostream>

int main(int, char **)
{
    UdpSender sender(45163);
    TimestampProviderApp app(sender);
    const int rc = app.work();
    std::cout << "Graceful stop" << std::endl;
    return rc;
}
