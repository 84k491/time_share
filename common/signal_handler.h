#pragma once

#include <iostream>

#include <atomic>
#include <csignal>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <set>
#include <thread>
#include <functional>
#include <memory>

class OneShotSignalHandler
{
    static constexpr int signal_to_catch = SIGUSR2;
public:
    OneShotSignalHandler(std::function<void(int)> callback);
    ~OneShotSignalHandler();

private:
    static void block_signal();

private:
    std::atomic_bool m_shot = false;
    std::function<void(int)> m_callback;
    std::unique_ptr<std::thread> m_thread_ptr;
};
