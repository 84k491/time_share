#pragma once

#include "i_signal_controllable.h"

#include <atomic>
#include <csignal>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <signal.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

class OneShotSignalHandler
{
    static constexpr int signal_to_catch = SIGUSR2;

public:
    OneShotSignalHandler(ISignalControllable & controllable);
    OneShotSignalHandler(const OneShotSignalHandler &) = delete;
    OneShotSignalHandler(OneShotSignalHandler &&) = delete;
    OneShotSignalHandler & operator=(const OneShotSignalHandler &) = delete;
    OneShotSignalHandler & operator=(OneShotSignalHandler &&) = delete;
    ~OneShotSignalHandler();

private:
    static void block_signal();

private:
    std::atomic_bool m_shot = false;
    ISignalControllable & m_controllable;
    std::unique_ptr<std::thread> m_thread_ptr;
};
