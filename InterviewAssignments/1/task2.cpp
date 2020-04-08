#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

template<typename T>
T abs(const T &v)
{
    return (v >= 0) ? v : -v;
}

template<typename T>
int sign(const T &v)
{
    if (v == 0)
        return 0;
    return (v >= 0) ? 1 : -1;
}

template<typename T>
bool inInterval(T lower, T upper, T v)
{
    return v >= lower && v <= upper;
}

template<typename T>
T nearest(T lower, T upper, T v)
{
    if (v - lower <= upper - v)
        return lower;

    return upper;
}

int solution(int X, int Y)
{
    Y = Y - X;

    if (Y < 0) {
        Y = Y + 360;
    }
    if (Y <= 90) {
        Y = Y - 180;
    }
    else if (Y <= 180) {
        Y = Y - 180;
    }
    else if (Y <= 270) {
        Y = Y - 180;
    }
    else { // Y > 270 && Y < 360
        Y = Y - 180;
    }

    vector<pair<int, int>> table = {
        {0, 30},
        {30, 90},
        {90, 135},
        {135, 180},
    };

    for (const auto &t: table) {
        if (inInterval(t.first, t.second, abs(Y)))
            return sign(Y) * nearest(t.first, t.second, abs(Y));
    }

    return 0;
}

int main(void)
{
    vector<tuple<int, int, int>> testCases = {
        {
            270, 50,
            -30,
        },
        {
            5, 200,
            0
        },
    };

    for (auto &test: testCases) {
        int ret = solution(std::get<0>(test), std::get<1>(test));
        if (ret == std::get<2>(test)) {
            std::cout << "PASS" << std::endl;
        }
        else {
            std::cout << "FAIL: " << "expected " << std::get<2>(test) << ", got " << ret << std::endl;
        }
    }
    return 0;
}
