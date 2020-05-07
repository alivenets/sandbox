#pragma once

#include "common.h"

namespace stub 
{
	class Interface
	{
	public:
		void connect();
	protected:
		virtual void foo(MessageHelper msg) = 0;
	};
}