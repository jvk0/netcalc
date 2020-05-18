#pragma once

#ifndef __AFXWIN_H__
    #error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"

class CNetCalcApp : public CWinApp {
public:
    CNetCalcApp();
private:
    virtual BOOL InitInstance();

    DECLARE_MESSAGE_MAP()
};

extern CNetCalcApp theApp;
