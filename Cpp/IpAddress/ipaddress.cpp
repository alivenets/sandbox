#include "ipaddress.h"

#include <arpa/inet.h>

#include <sstream>

/**
 * @brief Construct IP address
 */
IpAddress::IpAddress() : addr_(UNSPECIFIED_IP)
{
}

/**
 * @brief Construct IP address from integer in little-endian (host byte order) format
 * @param addr
 */
IpAddress::IpAddress(uint32_t addr) : addr_(addr)
{
}

/**
 * @brief Convert IP address to integer
 * @return uint32_t
 */
uint32_t IpAddress::toInt() const
{
    return addr_;
}

/**
 * @brief Convert IP address to array
 * @return array of 4 integers(in MSB format), e.g. first element is most significant byte
 */
std::array<uint8_t, 4> IpAddress::toArray() const
{
    return {{
        static_cast<uint8_t>((addr_ >> 24) & 0xFF),
        static_cast<uint8_t>((addr_ >> 16) & 0xFF),
        static_cast<uint8_t>((addr_ >> 8) & 0xFF),
        static_cast<uint8_t>(addr_ & 0xFF),
    }};
}

/**
 * @brief Convert IP address to string
 * @return std::string
 */
std::string IpAddress::toString() const
{
    const auto bytes = toArray();

    std::ostringstream ostr;

    ostr << static_cast<unsigned int>(bytes[0]) << "." << static_cast<unsigned int>(bytes[1]) << "." << static_cast<unsigned int>(bytes[2])
         << "." << static_cast<unsigned int>(bytes[3]);

    return ostr.str();
}

/**
 * @brief Get IP address from string
 * @param s IP address string
 * @return tuple of boolean flag and @ref IpAddress
 */
std::tuple<bool, IpAddress> IpAddress::fromString(const std::string& s)
{
    struct in_addr addr = {0};

    const int ret = inet_pton(AF_INET, s.c_str(), &addr);

    if (ret == 1) {
        const uint32_t hostAddr = ntohl(addr.s_addr);
        return std::make_tuple(true, IpAddress(hostAddr));
    }

    return std::make_tuple(false, IpAddress());
}
