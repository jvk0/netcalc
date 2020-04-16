#include "pch.h"

#include "IP4Calc.h"

#include <cmath>
#include <algorithm>

namespace IP4Calc {

// For "addrTypeStr"
const char* TYPESTR_PRIVATE  = "Private";
const char* TYPESTR_LOOPBACK = "Loopback";
const char* TYPESTR_APIPA    = "APIPA";
const char* TYPESTR_MCAST    = "Multicast";

IP4Addr makeIP4Addr(Octet first, Octet second, Octet third, Octet fourth)
{
    return (first << 24) | (second << 16) | (third << 8) | (fourth);
}

Octet firstOctet(IP4Addr addr)
{
    return ((addr >> 24) & 0xFF);
}

Octet secondOctet(IP4Addr addr)
{
    return ((addr >> 16) & 0xFF);
}

Octet thirdOctet(IP4Addr addr)
{
    return ((addr >> 8) & 0xFF);
}

Octet fourthOctet(IP4Addr addr)
{
    return (addr & 0xFF);
}

char addrClass(IP4Addr addr)
{
    Octet first = firstOctet(addr);

    if (first >= 0 && first <= 127)
        return 'A';
    else if (first >= 128 && first <= 191)
        return 'B';
    else if (first >= 192 && first <= 223)
        return 'C';
    else if (first >= 224 && first <= 239)
        return 'D';
    else
        return 'E';
}

const char* addrTypeStr(IP4Addr addr)
{
    constexpr IP4Addr PRIVATE0_ADDR = 0xC0A80000; // 192.168.0.0
    constexpr IP4Addr PRIVATE1_ADDR = 0xAC100000; // 172.16.0.0
    constexpr IP4Addr PRIVATE2_ADDR = 0x0A000000; // 10.0.0.0
    constexpr IP4Addr LOOPBACK_ADDR = 0x7F000000; // 127.0.0.0
    constexpr IP4Addr APIPA_ADDR    = 0xA9FE0000; // 169.254.0.0
    constexpr IP4Addr MCAST_ADDR    = 0xE0000000; // 224.0.0.0

    constexpr IP4Addr MASK4         = 0xF0000000; // 240.0.0.0
    constexpr IP4Addr MASK8         = 0xFF000000; // 255.0.0.0
    constexpr IP4Addr MASK12        = 0xFFF00000; // 255.240.0.0
    constexpr IP4Addr MASK16        = 0xFFFF0000; // 255.255.0.0

    // Ugly :{
    if ((addr & MASK16) == PRIVATE0_ADDR ||
        (addr & MASK12) == PRIVATE1_ADDR ||
        (addr & MASK8) == PRIVATE2_ADDR) {
        return TYPESTR_PRIVATE;
    } else if ((addr & MASK8) == LOOPBACK_ADDR) {
        return TYPESTR_LOOPBACK;
    } else if ((addr & MASK16) == APIPA_ADDR) {
        return TYPESTR_APIPA;
    } else if ((addr & MASK4) == MCAST_ADDR) {
        return TYPESTR_MCAST;
    } else {
        return nullptr;
    }
}

IP4Addr prefix2Mask(IP4Prefix prefix)
{
    IP4Addr mask = 0;

    for (int i = 0; i < prefix; i++)
        mask |= 1 << (31 - i);

    return mask;
}

IP4Prefix mask2Prefix(IP4Addr mask)
{
    IP4Prefix prefix = 0;

    if (!isMaskValid(mask))
        return 0;

    while (mask & (1 << (31 - prefix))) {
        if (prefix > 31)
            break;

        ++prefix;
    }

    return prefix;
}

bool isMaskValid(IP4Addr mask)
{
    bool end = false;

    for (int i = 0; i < 32; i++) {
        if (!(mask & (1 << (31 - i)))) {
            end = true;
        } else {
            if (end)
                return false; // Discontinuity!
        }
    }

    return true;
}

int numHostsAddr(IP4Prefix prefix)
{
    if (prefix == 32)
        return 1;

    return (1 << (32 - prefix)) - 2;
}

IP4Addr netAddr(IP4Addr addr, IP4Addr mask)
{
    return (addr & mask);
}

IP4Addr brdAddr(IP4Addr addr, IP4Addr mask)
{
    return (addr | ((~mask) & IP4_MAX));
}

IP4Addr firstAddr(IP4Addr addr, IP4Addr mask)
{
    return netAddr(addr, mask) + 1;
}

IP4Addr lastAddr(IP4Addr addr, IP4Addr mask)
{
    return brdAddr(addr, mask) - 1;
}

int ceilHosts(int hosts)
{
    int i = 0;
    while (hosts > (1 << i)) // hosts > 2^i
        i++;

    return 1 << i;
}

int sumHostReq(const HostsVect& hosts)
{
    int sum = 0;
    for (auto i : hosts)
        sum += ceilHosts(i);
    
    return sum;
}

IP4SubnetsVect calcSubnets(IP4Addr baseNet, const HostsVect& hosts)
{
    IP4SubnetsVect ret;

    using HostsTuple = std::tuple<int, int>;

    // Necessary (evil)
    std::vector<HostsTuple> subnetHosts;
    for (auto i : hosts)
        subnetHosts.push_back(std::make_tuple(i, ceilHosts(i)));
  
    // Sort by "ceilHosts"
    std::sort(subnetHosts.rbegin(), subnetHosts.rend(),
        [] (HostsTuple const& t1, HostsTuple const& t2)
        {
            return std::get<1>(t1) < std::get<1>(t2);
        });

    for (auto i : subnetHosts) {
        int hostsReq     = std::get<0>(i);
        int hostsSub     = std::get<1>(i);
        IP4Prefix prefix = IP4Prefix(((32 - std::log(hostsSub) / std::log(2))));

        ret.push_back(std::make_tuple(baseNet, prefix, hostsReq, hostsSub));
 
        baseNet += hostsSub;
    }

    return ret;
}

} // namespace IP4Calc
