#include "test.h"

namespace impl {
	void Impl::foo(MessageHelper msg)
	{
		msg.ret("Foo Bar");
	}
}