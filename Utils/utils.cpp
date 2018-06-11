#include <vector>
#include <string>

std::vector<std::string> splitVector(const std::string &s, char delim)
{
    std::vector<std::string> v;
    size_t pos = 0, npos = 0;

    while (npos < s.size() && (npos = s.find(delim, pos)) != std::string::npos) {
        v.push_back(s.substr(pos, npos - pos));
        pos = npos + 1;
    }

    return v;
}

std::string joinVector(const std::vector<std::string> &v, char delim)
{
    std::string s;

    for (const auto &i : v) {
        if (!s.empty())
            s += delim;
        s += i;
    }

    return s;
}
