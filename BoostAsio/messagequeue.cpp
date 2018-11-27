#include "messagequeue.h"

#include <iostream>

MessageQueue::MessageQueue():
    m_service{},
    m_work{std::make_unique<asio::io_service::work>(m_service)}
{

}

void MessageQueue::quit()
{
    // TODO: check if it is multi-threaded
    m_work.reset();
    // FIXME: post message with destroying work
}

void MessageQueue::run()
{
    m_service.run();
}

void MessageQueue::postTest(int i)
{
    m_service.post([=](){ std::cout << i << std::endl;});
}