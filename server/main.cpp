#include <iostream>
#include "timestamp_provider_app.h"

int main(int, char **)
{
    TimestampProviderApp app(45163);
    const int rc = app.work();
    std::cout << "Graceful stop" << std::endl;
    return rc;
}
