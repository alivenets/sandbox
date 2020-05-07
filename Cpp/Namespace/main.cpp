#include "test.h"

#include <memory>

int main(void)
{
	impl::Impl impl;
	impl.connect();

	MessageHelper msg;
	impl.foo(msg);
	
	return 0;
}