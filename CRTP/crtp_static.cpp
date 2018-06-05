#include <iostream>
#include <memory>

template<typename T>
class Base
{
public:
	static std::unique_ptr<T> create()
	{
		std::unique_ptr<T> obj = std::make_unique<T>();

		if (!obj)
			return nullptr;

		if (!obj->init())
			return nullptr;

		return obj;
	}
	virtual ~Base() {}
};

class Impl: public Base<Impl>
{
public:
	bool init() {
		std::cout << "Impl::init" << std::endl;
		return true;
	}
};

int main(void)
{
	auto ptr = Impl::create();
	return 0;
}