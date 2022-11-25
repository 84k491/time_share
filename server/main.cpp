#include <iostream>
#include "../common/udp.h"

int main(int, char **)
{
    UdpSender sender;
    sender.send(Message());
    return 0;
}
