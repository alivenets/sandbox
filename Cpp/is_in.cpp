#include <set>
#include <iostream>
#include <cstdio>

template<typename T>
bool is_in(T t, std::set<decltype(t)> u)
{
    return u.count(t);
}

template<typename T, typename V>
bool is_in(T t, std::map<decltype(t), V> u)
{
    return u.count(t);
}

int main(int argc, const char *argv[])
{
    auto list = std::set<int>{5, 6};

    std::cout << is_in(1, list) << std::endl;

    auto m = std::map<int,int>{{1,2},{3,4}};
    std::cout << is_in(1, m) << std::endl;

}