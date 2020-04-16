#include "pch.h"

#include "IP4Format.h"

namespace IP4Format {
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

} // namespace IP4Format