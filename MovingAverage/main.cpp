#include <iostream>

using namespace std;

#define N 4
class ArrayQueue
{
private:
    int arr[N];
    int lo;
    int hi;
    bool overflow;
public:
    ArrayQueue():
        arr{0},
        lo(0),
        hi(-1)
    {

    }

    void add(int val)
    {
        if (hi == lo)
            lo = (lo + 1) % N;

        if (hi < 0)
            hi = 0;

        arr[hi] = val;

        hi = (hi + 1) % N;
    }
    int low() const
    {
        return lo;
    }
    int high() const
    {
        return hi;
    }

    size_t count() const
    {
        if (hi < 0)
            return 0;

        if (lo < hi)
            return (hi - lo);
        else
            return (N + hi - lo);
    }
    float avg() const
    {
        return (float)sum() / count();
    }
    int sum() const
    {
        int i = lo;
        int res = 0;

        do {
            res += arr[i];
            i = (i + 1) % N;
        } while (i != hi);

        return res;
    }
    int diff() const
    {
        return (arr[hi == 0 ? N - 1 : hi - 1] - arr[lo]);
    }
    void dump()
    {
        for (int i = 0; i < N; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main(int argc, char *argv[])
{
    ArrayQueue mov;

    for(int i = 1; i <= 6; i++) {
        mov.add(1 << i);
        mov.dump();
        cout<< i << ": (" << mov.low() << ", " << mov.high() << "), cnt = " << mov.count() << ", sum = " << mov.sum() << ", diff = " << mov.diff() << endl;
    }
    return 0;
}
