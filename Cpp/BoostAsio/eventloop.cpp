#include "eventloop.h"

#include <future>
#include <iostream>
#include <thread>

namespace asio = boost::asio;

EventLoop::EventLoop():
    m_service{},
    m_work{std::make_unique<asio::io_service::work>(m_service)}
{

}

void EventLoop::quit()
{
    m_service.post([this]() {
        this->m_work.reset();
    });
}

void EventLoop::post(const std::function<void()> &callback)
{
    m_service.post([callback]() {
        callback();
    });
}

void EventLoop::executeSync(const std::function<void()> &callback)
{
    std::packaged_task<void()> task{callback};
    std::future<void> f = task.get_future();

    m_service.post([&task]() {
        task();
    });

    f.wait();
}

void EventLoop::run()
{
    m_service.run();
}
