#pragma once

#include <iostream>
#include <string>

namespace {
	class MessageHelper {
	public:
		void ret(std::string s) {
			std::cout << "Hello world! " << s << std::endl;
		}
	};
}