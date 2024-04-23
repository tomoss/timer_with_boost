#include "TimerTrigger.h"
#include <iostream>

TimerTrigger::TimerTrigger() : m_ioService(), m_work(m_ioService)
{
    try
    {
        m_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &m_ioService));
        std::cout << "Thread used by timers started" << std::endl;
    }
    catch (boost::thread_resource_error& e)
    {
        throw std::runtime_error(e.what());
    }
}

TimerTrigger::~TimerTrigger()
{
    std::cout << "Stopping the thread used by timers..." << std::endl;
    m_ioService.stop();
    if (m_thread.joinable())
    {
        try
        {
            m_thread.join();
            std::cout << "Thread used by timers stopped" << std::endl;
        }
        catch (boost::thread_resource_error& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Thread used by timers not joinable" << std::endl;
    }
}

void TimerTrigger::addTimer(const int& p_timerId, TimeoutEventHandler_t p_timeoutEventHandler)
{
    m_timersList.emplace(std::piecewise_construct, std::forward_as_tuple(p_timerId), std::forward_as_tuple(m_ioService, p_timeoutEventHandler));
    std::cout << "Timer " << p_timerId << " added" << std::endl;
}

void TimerTrigger::deleteTimer(const int& p_timerId)
{
    try
    {
        cancelTimer(p_timerId);
        m_timersList.erase(p_timerId);
        std::cout << "Timer " << p_timerId << " deleted." << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        throw std::runtime_error(e.what());
    }
}

void TimerTrigger::startTimer(const int& p_timerId, const uint32_t& p_seconds)
{
    try
    {
        m_timersList.at(p_timerId).start(p_seconds);
    }
    catch (const std::out_of_range& e)
    {
        throw std::runtime_error(e.what());
    }
}

void TimerTrigger::cancelTimer(const int& p_timerId)
{
    try
    {
        m_timersList.at(p_timerId).cancel();
        std::cout << "Timer " << p_timerId << " canceled." << std::endl;

    }
    catch (const std::out_of_range& e)
    {
        throw std::runtime_error(e.what());
    }
}