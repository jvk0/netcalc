#pragma once

#include "IP4Calc.h"

// CHostsDlg dialog
class CHostsDlg : public CDialogEx {
    DECLARE_DYNAMIC(CHostsDlg)

public:
    CHostsDlg(IP4Calc::HostsVect& outHosts, CWnd* pParent = nullptr); // Modified standard constructor
    virtual ~CHostsDlg();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_HOSTS_DIALOG };
    #endif
protected:
    IP4Calc::HostsVect m_outHosts;

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
    virtual void OnOK() override;
    virtual void OnCancel() override;

    virtual BOOL OnInitDialog() override;
    DECLARE_MESSAGE_MAP()
};
