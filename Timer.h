#pragma once

#include <boost/asio/steady_timer.hpp>
#include <boost/asio.hpp>

typedef std::function<void()> TimeoutEventHandler_t;

class Timer
{
public:
    Timer(TimeoutEventHandler_t p_hdlr);
    ~Timer();
    Timer& operator=(const Timer&) = delete;
    void create(boost::asio::io_service& p_ioService);
    void start(uint32_t p_seconds);
    void cancel();

private:
    void timerHandler(const boost::system::error_code& p_error);
    boost::shared_ptr<boost::asio::steady_timer> mp_timer;
    TimeoutEventHandler_t m_timeoutEventHandler;
};