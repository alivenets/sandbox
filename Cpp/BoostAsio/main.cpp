#include "eventloop.h"

#include <thread>
#include <chrono>

int main(void)
{
    EventLoop ev;
    std::thread t{
	[&]() {
	    for (int i = 0;;++i) { 
		ev.post([](){});
		std::this_thread::sleep_for(std::chrono::seconds(1));
	    }
	}
    };
    ev.run();
}