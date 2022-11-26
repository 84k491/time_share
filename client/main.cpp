#include <iostream>
#include "timestamp_consumer_app.h"

int main(int, char **)
{
    TimestampConsumerApp app(45163);
    int rc = app.work();
    std::cout << "Graceful stop" << std::endl;
    return rc;
}
