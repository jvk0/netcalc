#pragma once

#include <atlstr.h>

#include "IP4Calc.h"

namespace IP4String {
    CString addr2Str(IP4Calc::IP4Addr addr);
    CString addr2BinStr(IP4Calc::IP4Addr addr);
    LPCWSTR addrTypeStr(IP4Calc::IP4Addr addr);

} // namespace IP4String