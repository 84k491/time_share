#include <signal_handler.h>
#include <iostream>

OneShotSignalHandler::OneShotSignalHandler(std::function<void(int)> callback)
    : m_callback(callback)
{
    block_signal();
    m_thread_ptr = std::make_unique<std::thread>([this]() {

        sigset_t signals;
        sigemptyset(&signals);
        sigaddset(&signals, signal_to_catch);
        int signal_number = 0;
        sigwait(&signals, &signal_number);
        m_shot = true;
        std::cout << "Received correct signal. Invoking callback" << std::endl;
        m_callback(signal_to_catch);
    });
}

OneShotSignalHandler::~OneShotSignalHandler()
{
    if (!m_shot) {
        pthread_kill(m_thread_ptr->native_handle(), signal_to_catch);
    }
    m_thread_ptr->join();
}

void OneShotSignalHandler::block_signal()
{
    sigset_t signals;
    sigemptyset(&signals);
    sigaddset(&signals, signal_to_catch);
    pthread_sigmask(SIG_BLOCK, &signals, nullptr);
}

