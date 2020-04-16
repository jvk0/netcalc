#pragma once

#include <cstdint>
#include <tuple>
#include <vector>

namespace IP4Calc {

using IP4Addr        = uint32_t;
using Octet          = uint8_t;
using IP4Prefix      = uint8_t;
using HostsVect      = std::vector<int>;
using IP4SubnetsVect = std::vector<std::tuple<IP4Addr, IP4Prefix, int, int>>;

constexpr IP4Addr IP4_MAX    = UINT32_MAX;
constexpr size_t OCTSTR_SIZE = sizeof(Octet) * 8 + 1;

IP4Addr makeIP4Addr(Octet first, Octet second, Octet third, Octet fourth);
Octet firstOctet(IP4Addr addr);
Octet secondOctet(IP4Addr addr);
Octet thirdOctet(IP4Addr addr);
Octet fourthOctet(IP4Addr addr);

char addrClass(IP4Addr addr);
const char* addrTypeStr(IP4Addr addr);

IP4Addr prefix2Mask(IP4Prefix prefix);
IP4Prefix mask2Prefix(IP4Addr mask);
bool isMaskValid(IP4Addr mask);
int numHostsAddr(IP4Prefix prefix);

IP4Addr netAddr(IP4Addr addr, IP4Addr mask);
IP4Addr brdAddr(IP4Addr addr, IP4Addr mask);
IP4Addr firstAddr(IP4Addr addr, IP4Addr mask);
IP4Addr lastAddr(IP4Addr addr, IP4Addr mask);

int ceilHosts(int hosts);
int sumHostReq(const HostsVect& hosts);
IP4SubnetsVect calcSubnets(IP4Addr net, const HostsVect& hosts);

} // namespace IP4Calc
