#include "messagequeue.h"

#include <thread>
#include <chrono>

int main(void)
{
    MessageQueue mq;
    std::thread t{
	[&]() {
	    for (int i = 0;;++i) { 
		mq.postTest(i);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	    }
	}
    };
    mq.run();
}