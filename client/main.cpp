#include "argument_parser.h"
#include "timestamp_consumer_app.h"
#include "udp_listener.h"

#include <iostream>

int main(int argc, char ** argv)
{
    ArgumentParser arg_parser(argc, argv);
    const auto port_opt = arg_parser.port();
    if (!port_opt) {
        return -1;
    }
    UdpListener listener(port_opt.value());
    TimestampConsumerApp app(listener);
    int rc = app.work();
    std::cout << "Graceful stop" << std::endl;
    return rc;
}
