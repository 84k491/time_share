#include <iostream>

#include <set>
#include <thread>
#include <functional>

class OneShotSignalHandler
{
public:
    OneShotSignalHandler(std::function<void(int)> callback);
    ~OneShotSignalHandler();

private:
    std::function<void(int)> m_callback;
    std::thread m_thread;
};
