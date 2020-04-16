#pragma once

#include <atlstr.h>

#include "IP4Calc.h"

namespace IP4Format {
    CString addr2Str(IP4Calc::IP4Addr addr);
    CString addr2BinStr(IP4Calc::IP4Addr addr);

} // namespace IP4Format