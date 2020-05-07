#include <iostream>

template<typename T>
class Base
{
public:
    void interface()
    {
	static_cast<T*>(this)->implementation();
    }
};

class Impl: public Base<Impl>
{
public:
    void implementation()
    {
	std::cout << "Hello from Impl!" << std::endl;
    }
};

int main(void)
{
    Impl impl;
    impl.interface();
    return 0;
}