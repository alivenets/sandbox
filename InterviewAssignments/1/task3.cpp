#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

int calcAdjacent(int v)
{
    int ov = 0;
    for (int i = 0; i < 8; i++) {
        if ((v >> i) & 0x1) {
            ov = ov | (0x1 << i);
            int l = i - 1;
            int r = i + 1;
            if (l >= 0)
                ov = ov | (0x1 << l);
            if (r < 8)
                ov = ov | (0x1 << r);
        }
    }
    return ov & 0xFF;
}

int solution(vector<int> &A)
{
    int cnt = -1;

    int tmp = 0;
    for (int v: A) {
        if (cnt == -1) {
            tmp = v;
            if (v == 0)
                return -1;
            cnt = 0;
            continue;
        }
        // cout << "! " << tmp << " " << calcAdjacent(tmp) << " " << v << endl;
        if ((tmp & v) == 0) {
            // check for adjacent bits to move. If there are no adjacent bits, return -1
            if ((calcAdjacent(tmp) & v) != 0) {
                tmp = calcAdjacent(tmp) & v;
                cnt++;
            }
            else
                return -1;
        }
        else {
            tmp = tmp & v;
        }
    }

    return cnt;
}

// Cases:
// [2,3,1,1,]
// [1,3,2,1,]
// [1,2,1,1,]
bool getNext(vector<int> &v, int base)
{
    int i = 0;
    while (i < v.size()) {
        if (v[i] < base) {
            v[i]++;
            return true;
        }
        else {
            v[i] = 0;
        }
        i++;
    }
    return false;
}

ostream &operator <<(ostream &ostr, const vector<int> &v)
{
    ostr << "[";

    for (int i: v)
        ostr << i << ",";

    ostr << "]";
}
int main(void)
{
    vector<int> base = {0, 0, 0, 0};

    vector<tuple<vector<int>, int>> testCases = {
    };

    for (int i = 0; i < 512; ++i) {
        testCases.push_back(std::make_tuple(base, 0));
        bool b = getNext(base, 3);
        if (!b)
            break;
    }

    for (auto &test: testCases) {
        int ret = solution(get<0>(test));
        cout << get<0>(test) << " " << ret << endl;
    }
}
