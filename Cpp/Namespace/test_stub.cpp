#include "test_stub.h"

#include <iostream>

namespace stub {
	void Interface::connect() {
		std::cout << "Connect" << std::endl;
	}
}