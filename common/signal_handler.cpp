#include <signal_handler.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h> // TODO remove?
#include <iostream>
#include <csignal>

// namespace
// {
    // volatile std::sig_atomic_t g_signal_status;
// }
 
void signal_handler(int)
{
    // g_signal_status = signal;
    // std::cout << "some signal recevied" << std::endl;
}

OneShotSignalHandler::OneShotSignalHandler(std::function<void(int)> callback)
    : m_callback(callback)
    , m_thread([this]() {
        signal(SIGUSR1, signal_handler);

        sigset_t signals;
        sigemptyset(&signals);
        sigaddset(&signals, SIGUSR1);
        pthread_sigmask(SIG_BLOCK, &signals, nullptr);

        std::cout << "Waiting for signal" << std::endl;
        // while (g_signal_status != SIGUSR1) {
            // if (sigwait(&signals, &signal_number)) {
                // std::cout << "sigwait returned" << std::endl;
            // }
            // std::cout << "Received some signal" << std::endl;
        // }
        int signal_number = 0;
        sigwait(&signals, &signal_number);
        std::cout << "Received correct signal. Invoking callback" << std::endl;
        m_callback(SIGUSR1);
    })
{
}

OneShotSignalHandler::~OneShotSignalHandler()
{
    m_thread.join();
}
