#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <array>
#include <cstdint>
#include <string>
#include <tuple>

/**
 * @brief IP address
 * IP address is stored in little-endian format.
 * Can be build from string in format "a.b.c.d", where:
 *      a, b, c, d - integers in range [0..255] in decimal representation
 */
class IpAddress
{
public:
    static const uint32_t UNSPECIFIED_IP = 0;

    explicit IpAddress();

    IpAddress(const IpAddress&) = default;

    explicit IpAddress(uint32_t addr);

    uint32_t               toInt() const;
    std::array<uint8_t, 4> toArray() const;
    std::string            toString() const;

    IpAddress& operator=(uint32_t addr)
    {
        addr_ = addr;
        return *this;
    }
    /**
     * Hash function
     */
    std::size_t operator()(const IpAddress& key) const
    {
        return std::hash<uint32_t>()(key.addr_);
    }

    /**
     * @brief Compare IP addresses for equality
     * @param addr IP address
     * @return bool
     */
    bool operator==(const IpAddress& addr) const
    {
        return addr_ == addr.addr_;
    }

    /**
     * @brief Compare IP addresses for inequality
     * @param addr IP address
     * @return bool
     */
    bool operator!=(const IpAddress& addr) const
    {
        return !(*this == addr);
    }

    /**
     * @brief      Compare for less-than
     * @param[in]  addr  The ip address
     * @return     bool
     */
    bool operator<(const IpAddress& addr) const
    {
        return addr_ < addr.addr_;
    }

    static std::tuple<bool, IpAddress> fromString(const std::string& s);

private:
    uint32_t addr_;
};

#endif  // IPADDRESS_H
