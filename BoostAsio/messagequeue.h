#pragma once

#include <boost/asio/io_service.hpp>
#include <boost/asio/basic_io_object.hpp>

namespace asio = boost::asio;

class MessageQueue
{
public:
    MessageQueue();
    void run();
    void quit();
    void postTest(int i);
private:
    asio::io_service m_service;
    std::unique_ptr<asio::io_service::work> m_work;
};