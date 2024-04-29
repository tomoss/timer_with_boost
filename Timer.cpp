#include "Timer.h"
#include <iostream>
#include <boost/bind.hpp>

Timer::Timer(TimeoutEventHandler_t p_hdlr) : m_timeoutEventHandler(p_hdlr)
{
    
}

Timer::~Timer()
{
    this->cancel();
}

void Timer::create(boost::asio::io_service& p_ioService)
{
    mp_timer = boost::shared_ptr<boost::asio::steady_timer>(new boost::asio::steady_timer(p_ioService));
}

void Timer::start(uint32_t p_seconds)
{
    try
    {
        mp_timer->cancel();
        mp_timer->expires_from_now(std::chrono::seconds(p_seconds));
        mp_timer->async_wait(boost::bind(&Timer::timerHandler, this, boost::asio::placeholders::error));
    }
    catch(boost::system::system_error& e)
    {
        throw std::runtime_error(e.what());
    }
}

void Timer::timerHandler(const boost::system::error_code &p_error)
{
    if (p_error)
    {
        if (ECANCELED == p_error.value())
        {
            //Timer has been canceled
        }
        else
        {
            throw std::runtime_error(p_error.message());
        }
    }
    else
    {
        if(nullptr != m_timeoutEventHandler)
        {
            m_timeoutEventHandler();
        }
         else
        {
            throw std::runtime_error("Timer has unitialized timeout event handler");

        }
    }
}

void Timer::cancel()
{
    try
    {
        mp_timer->cancel();
    }
    catch(boost::system::system_error& e)
    {
        throw std::runtime_error(e.what());
    }
}