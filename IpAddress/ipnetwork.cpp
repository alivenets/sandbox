#include "ipnetwork.h"

#include "routerutil.h"

/**
 * @brief Construct IP network
 */
IpNetwork::IpNetwork() : subnet_(), networkPrefix_(0)
{
}

/**
 * @brief Construct IP network from subnet and network prefix
 * @param subnet subnet IP address
 * @param networkPrefix network prefix
 */
IpNetwork::IpNetwork(const IpAddress& subnet, uint8_t networkPrefix)
    : subnet_(subnet)
    , networkPrefix_(networkPrefix > MAX_NETWORK_PREFIX ? MAX_NETWORK_PREFIX : networkPrefix)
{
}

/**
 * @brief Get broadcast network IP address
 * @return @ref IpAddress
 */
IpAddress IpNetwork::getBroadcastAddress() const
{
    return IpAddress(composeSubnetAndHostPart(getSubnet().toInt(), getHostPartMask()));
}

/**
 * @brief Get subnet IP address
 * @return @ref IpAddress
 */
IpAddress IpNetwork::getSubnet() const
{
    return subnet_;
}

/**
 * @brief Get network prefix
 * @return uint8_t
 */
uint8_t IpNetwork::getNetworkPrefix() const
{
    return networkPrefix_;
}

/**
 * @brief Get network string representation in CIDR notation
 * @return std::string
 */
std::string IpNetwork::toString() const
{
    return subnet_.toString() + "/" + std::to_string(static_cast<int>(networkPrefix_));
}

/**
 * @brief Get IP subnet mask
 * @return uint32_t
 */
uint32_t IpNetwork::getSubnetMask() const
{
    return composeSubnetMask(networkPrefix_);
}

/**
 * @brief Get host part mask
 * @return uint32_t
 */
uint32_t IpNetwork::getHostPartMask() const
{
    return composeHostPartMask(networkPrefix_);
}

/**
 * @brief Check if IP network contains IP address
 * @param ip IP address
 * @return bool
 */
bool IpNetwork::containsIpAddress(const IpAddress& ip) const
{
    return ((ip.toInt() & getSubnetMask()) == subnet_.toInt());
}

/**
 * @brief Check if IP address is host IP address.
 * IP address is host address if it is valid, not broadcast and belongs to the same subnet
 * @param ip IP address
 * @return bool
 */
bool IpNetwork::isHostIpAddress(const IpAddress& ip) const
{
    return (containsIpAddress(ip) && (ip != getBroadcastAddress()) && (ip != getSubnet()));
}

/**
 * @brief Get network size.
 * Network size is count of all IP addresses belonging to the network
 * including broadcast address, excluding subnet address
 * @return size_t
 */
size_t IpNetwork::getNetworkSize() const
{
    return static_cast<size_t>(getHostPartMask());
}

/**
 * @brief Extract host part from IP address
 * @param ip IP address
 * @return tuple of boolean flag and @ref IpAddress
 */
std::tuple<bool, IpAddress> IpNetwork::extractHostPart(const IpAddress& ip) const
{
    if (containsIpAddress(ip))
        return std::make_tuple(true, IpAddress(ip.toInt() & getHostPartMask()));

    return std::make_tuple(false, IpAddress());
}

/**
 * @brief Make IP address from host part
 * @param hostPart IP address containing host part
 * @return tuple of boolean flag and @ref IpAddress
 */
std::tuple<bool, IpAddress> IpNetwork::fromHostPart(const IpAddress& hostPart) const
{
    const IpAddress ip(composeSubnetAndHostPart(getSubnet().toInt(), hostPart.toInt()));

    // Check that composed IP is host IP by extracting host part back and comparing it
    const auto result = extractHostPart(ip);
    if (std::get<0>(result) && std::get<1>(result) == hostPart)
        return std::make_tuple(true, ip);

    return std::make_tuple(false, IpAddress());
}

/**
 * @brief Get IP network from string
 * @param str IP network string in CIDR notation
 * @return tuple of boolean flag and @ref IpNetwork
 */
std::tuple<bool, IpNetwork> IpNetwork::fromString(const std::string& str)
{
    // Find slash to detect network prefix
    const auto slashPos = str.find("/");

    if (slashPos == std::string::npos)
        return std::make_tuple(false, IpNetwork());

    const auto ipAddressString = str.substr(0, slashPos);
    const auto subnetString    = str.substr(slashPos + 1);  // skip slash

    // Parse network prefix
    const auto networkPrefixParseResult = stringToUint8(subnetString);
    if (!std::get<0>(networkPrefixParseResult))
        return std::make_tuple(false, IpNetwork());

    const uint8_t networkPrefix = std::get<1>(networkPrefixParseResult);

    if ((networkPrefix < IpNetwork::MIN_NETWORK_PREFIX) || (networkPrefix > IpNetwork::MAX_NETWORK_PREFIX))
        return std::make_tuple(false, IpNetwork());


    // Parse IP address
    const auto ipAddressParseResult = IpAddress::fromString(ipAddressString);
    if (!std::get<0>(ipAddressParseResult))
        return std::make_tuple(false, IpNetwork());

    const IpAddress ip = std::get<1>(ipAddressParseResult);

    // Check invalid address a.b.c.d/0, only 0.0.0.0/0 is valid
    if (ip.toInt() != 0 && networkPrefix == 0)
        return std::make_tuple(false, IpNetwork());

    // Check if subnet overlaps with netmask, e.g. 192.168.1.0/16
    if ((ip.toInt() & composeHostPartMask(networkPrefix)) != 0)
        return std::make_tuple(false, IpNetwork());

    return std::make_tuple(true, IpNetwork(ip, networkPrefix));
}

