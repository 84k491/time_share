#include <signal_handler.h>
#include <iostream>

OneShotSignalHandler::OneShotSignalHandler(std::function<void(int)> callback)
    : m_callback(callback)
    , m_thread([this]() {

        sigset_t signals;
        sigemptyset(&signals);
        sigaddset(&signals, signal_to_catch);
        std::cout << "Waiting for signal" << std::endl;
        int signal_number = 0;
        sigwait(&signals, &signal_number);
        std::cout << "Received correct signal. Invoking callback" << std::endl;
        m_callback(signal_to_catch);
    })
{
}

OneShotSignalHandler::~OneShotSignalHandler()
{
    m_thread.join();
}

void OneShotSignalHandler::block_signals()
{
    sigset_t signals;
    sigemptyset(&signals);
    sigaddset(&signals, signal_to_catch);
    pthread_sigmask(SIG_BLOCK, &signals, nullptr);
}

