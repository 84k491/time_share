#pragma once

class ISignalControllable
{
public:
    virtual ~ISignalControllable() = default;
    virtual void on_signal(int) = 0;
};
