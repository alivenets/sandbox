#ifndef IPNETWORK_H
#define IPNETWORK_H

#include <cstdint>
#include <string>
#include <tuple>

#include "ipaddress.h"

/**
 * @brief IP network
 * IP network can be built from CIDR notation string (https://en.wikipedia.org/wiki/Classless_Inter-Domain_Routing)
 * CIDR notation string has format "a.b.c.d/x", where:
 *      "a.b.c.d" is IP address,
 *      x is network prefix in range [0..32] in decimal representation
 */
class IpNetwork
{
public:
    static const uint8_t MIN_NETWORK_PREFIX = 0;
    static const uint8_t MAX_NETWORK_PREFIX = 32U;

    /**
     * @brief Compose host part mask from network prefix
     * @param networkPrefix network prefix
     * @return host part mask
     */
    static constexpr uint32_t composeHostPartMask(uint8_t networkPrefix)
    {
        if (networkPrefix > MAX_NETWORK_PREFIX)
            return 0;

        return ((1U << (MAX_NETWORK_PREFIX - networkPrefix)) - 1U);
    }

    /**
     * @brief Compose subnet mask from network prefix
     * @param networkPrefix network prefix
     * @return subnet mask
     */
    static constexpr uint32_t composeSubnetMask(uint8_t networkPrefix)
    {
        return ~composeHostPartMask(networkPrefix);
    }

    /**
     * @brief Compose subnet and host part into single IP address
     * @param subnet subnet
     * @param hostPart host part
     * @return IP address
     */
    static constexpr uint32_t composeSubnetAndHostPart(uint32_t subnet, uint32_t hostPart)
    {
        return (subnet | hostPart);
    }

    static constexpr bool isSubnetworkAddress(uint32_t addr, uint8_t netmaskBit)
    {
        return !(~IpNetwork::composeSubnetMask(netmaskBit) & addr);
    }

    explicit IpNetwork();

    IpNetwork(const IpNetwork&) = default;

    explicit IpNetwork(const IpAddress& subnet, uint8_t networkPrefix);

    IpAddress getBroadcastAddress() const;
    IpAddress getSubnet() const;
    uint8_t   getNetworkPrefix() const;

    std::string toString() const;

    bool containsIpAddress(const IpAddress& ip) const;

    bool isHostIpAddress(const IpAddress& ip) const;

    size_t getNetworkSize() const;

    std::tuple<bool, IpAddress> extractHostPart(const IpAddress& ip) const;

    std::tuple<bool, IpAddress> fromHostPart(const IpAddress& hostPart) const;

    static std::tuple<bool, IpNetwork> fromString(const std::string& s);

    bool operator==(const IpNetwork& net) const
    {
        return subnet_ == net.getSubnet();
    }

private:
    uint32_t getSubnetMask() const;
    uint32_t getHostPartMask() const;

    IpAddress subnet_;
    uint8_t   networkPrefix_;
};

#endif  // CONNECTIVITY_ROUTER_IPNETWORK_H
