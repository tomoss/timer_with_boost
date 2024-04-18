#pragma once

#include "Timer.h"

#include <boost/chrono/chrono.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

class TimerTrigger
{
public:
    TimerTrigger();
    ~TimerTrigger();

    void init();

    void addTimer(const int& p_timerId, TimeoutEventHandler_t p_timeoutEventHandler);
    void deleteTimer(const int& p_timerId);
    void startTimer(const int& p_timerId, uint32_t p_seconds);
    void cancelTimer(const int& p_timerId);

private:
    boost::asio::io_service m_ioService;
    boost::thread m_thread;
    boost::asio::io_service::work m_work;
    std::map<int, Timer> m_timersList;




};