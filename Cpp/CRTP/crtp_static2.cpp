#include <iostream>
#include <memory>

template<typename T>
class Base
{
public:
	template<typename... Args>
	static std::unique_ptr<T> create(Args... args)
	{
		std::unique_ptr<T> obj = std::make_unique<T>();

		if (!obj)
			return nullptr;

		if (!obj->init(args...))
			return nullptr;

		return obj;
	}
	virtual ~Base() {}
};

class Impl: public Base<Impl>
{
public:
	bool init(int n) {
		std::cout << "Impl::init, arg: " << n << std::endl;
		return true;
	}
};

int main(void)
{
	auto ptr = Impl::create(42);
	return 0;
}