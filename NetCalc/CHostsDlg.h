#pragma once

#include "IP4Calc.h"

// CHostsDlg dialog
class CHostsDlg : public CDialogEx {
    DECLARE_DYNAMIC(CHostsDlg)

public:
    CHostsDlg(const IP4Calc::HostsVect& inHosts, CWnd* pParent = nullptr); // Modified standard constructor
    virtual ~CHostsDlg();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_HOSTS_DIALOG };
    #endif

    IP4Calc::HostsVect getHostsVec();
protected:
    IP4Calc::HostsVect m_outHosts;

    void addListHostsRow(int num);
    void initListHosts();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
    virtual void OnOK() override;
    virtual void OnCancel() override;

    virtual BOOL OnInitDialog() override;
    DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_ctrListHosts;
};
