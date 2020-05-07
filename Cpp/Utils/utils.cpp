#include <vector>
#include <string>

#include <netinet/in.h>

std::vector<std::string> splitVector(const std::string &s, char delim)
{
    std::vector<std::string> v;
    size_t pos = 0, npos = 0;

    while (npos < s.size() && (npos = s.find(delim, pos)) != std::string::npos) {
        if (npos >= pos)
       	    v.push_back(s.substr(pos, npos - pos));
        pos = npos + 1;
    }

    if (pos != string::npos && pos < s.size()) {
        v.push_back(s.substr(pos));
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

std::string ipAddressToString(struct in_addr addr)
{
    const uint32_t ipAddr = addr.s_addr;

    return std::to_string(static_cast<unsigned char>((ipAddr      ) & 0xFF)) + "."
         + std::to_string(static_cast<unsigned char>((ipAddr >>  8) & 0xFF)) + "."
         + std::to_string(static_cast<unsigned char>((ipAddr >> 16) & 0xFF)) + "."
         + std::to_string(static_cast<unsigned char>((ipAddr >> 24) & 0xFF));
}

