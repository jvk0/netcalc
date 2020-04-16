#include "pch.h"

#include "IP4String.h"

namespace IP4String {

// For "addrTypeStr"
LPCWSTR TYPESTR_PRIVATE  = L"Private";
LPCWSTR TYPESTR_LOOPBACK = L"Loopback";
LPCWSTR TYPESTR_APIPA    = L"APIPA";
LPCWSTR TYPESTR_MCAST    = L"Multicast";

CString addr2Str(IP4Calc::IP4Addr addr)
{
    using namespace IP4Calc;

    CString ret; // :{
    
    ret.Format(L"%u.%u.%u.%u", firstOctet(addr), secondOctet(addr), thirdOctet(addr), fourthOctet(addr));

    return ret;
}

CString addr2BinStr(IP4Calc::IP4Addr addr)
{
    CString ret; // :{
    
    for (int i = (32 - 1); i >= 0; i--) {
        ret += static_cast<WCHAR>((addr & 1) + '0');
        
        if (!(i % 8) && i)
            ret += '.';
        
        addr >>= 1;
    }

    return ret.MakeReverse(); // :{
}

LPCWSTR addrTypeStr(IP4Calc::IP4Addr addr)
{
    constexpr IP4Calc::IP4Addr PRIVATE0_ADDR = 0xC0A80000; // 192.168.0.0
    constexpr IP4Calc::IP4Addr PRIVATE1_ADDR = 0xAC100000; // 172.16.0.0
    constexpr IP4Calc::IP4Addr PRIVATE2_ADDR = 0x0A000000; // 10.0.0.0
    constexpr IP4Calc::IP4Addr LOOPBACK_ADDR = 0x7F000000; // 127.0.0.0
    constexpr IP4Calc::IP4Addr APIPA_ADDR    = 0xA9FE0000; // 169.254.0.0
    constexpr IP4Calc::IP4Addr MCAST_ADDR    = 0xE0000000; // 224.0.0.0

    constexpr IP4Calc::IP4Addr MASK4  = 0xF0000000; // 240.0.0.0
    constexpr IP4Calc::IP4Addr MASK8  = 0xFF000000; // 255.0.0.0
    constexpr IP4Calc::IP4Addr MASK12 = 0xFFF00000; // 255.240.0.0
    constexpr IP4Calc::IP4Addr MASK16 = 0xFFFF0000; // 255.255.0.0

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

} // namespace IP4String