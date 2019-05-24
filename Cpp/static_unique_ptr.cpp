#include <memory>
#include <iostream>

struct A
{
    void f() { std::cout << "!!! " << n << std::endl; n++; }

    int n = 0;
};

void get()
{
    static auto ptr = std::make_unique<A>();
    ptr->f();
}

int main()
{
    get();    
    get();
}