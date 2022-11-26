#pragma once

#include <iostream>

#include <csignal>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <set>
#include <thread>
#include <functional>

class OneShotSignalHandler
{
    static constexpr int signal_to_catch = SIGUSR2;
public:
    OneShotSignalHandler(std::function<void(int)> callback);
    ~OneShotSignalHandler();

    static void block_signals();
private:
    std::function<void(int)> m_callback;
    std::thread m_thread;
};
