#pragma once

#include <iostream>

class Printer final : public IPrinter
{
public:
    ~Printer() override = default;
    void print(uint64_t local, uint64_t received, int32_t diff) override
    {
        std::cout << "Local timestamp   : " << local << std::endl;
        std::cout << "Recevied timestamp: " << received << std::endl;
        std::cout << "Difference        : " << diff << std::endl;
        std::cout << "-------" << std::endl;
    }
};
