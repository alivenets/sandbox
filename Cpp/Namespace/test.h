#pragma once
#include "test_stub.h"
#include "common.h"
namespace impl {
	class Impl: public stub::Interface
	{
	public:
		virtual void foo(MessageHelper msg);
	};
}