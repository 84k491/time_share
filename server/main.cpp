#include "argument_parser.h"
#include "timestamp_provider_app.h"
#include "udp_sender.h"

#include <iostream>

int main(int argc, char ** argv)
{
    ArgumentParser arg_parser(argc, argv);
    const auto port_opt = arg_parser.port();
    if (!port_opt) {
        return -1;
    }
    UdpSender sender(port_opt.value());
    TimestampProviderApp app(sender);
    const int rc = app.work();
    std::cout << "Graceful stop" << std::endl;
    return rc;
}
