#pragma once

#include <boost/asio/io_service.hpp>

class EventLoop
{
public:
    EventLoop();

    void run();

    void quit();

    void post(const std::function<void()> &callback);

    void executeSync(const std::function<void()> &callback);

private:
    boost::asio::io_service m_service;
    std::unique_ptr<boost::asio::io_service::work> m_work;
};
