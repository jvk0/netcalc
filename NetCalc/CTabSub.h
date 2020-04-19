#pragma once

#include "IP4Calc.h"

// CTabSub dialog
class CTabSub : public CDialogEx {
    DECLARE_DYNAMIC(CTabSub)

public:
    CTabSub(CWnd* pParent = nullptr);   //  Standard constructor
    virtual ~CTabSub();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_OLE_PL_TAB1 };
    #endif

protected:
    IP4Calc::HostsVect  m_subnetHosts;
    int                 m_subnetHostsSum;

    int                 m_calcPrefix;
 
    CIPAddressCtrl      m_ctrIPBaseNet;
    CSpinButtonCtrl     m_ctrSpinPrefix;
    
    DWORD               m_valIPBaseNet;
    CString             m_valSTextInfo;
    
    void updateInfoStr();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK() override;
    virtual void OnCancel() override;

    virtual BOOL OnInitDialog() override;
    afx_msg void OnDeltaPosSpinPrefix(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnIPFieldChangedIPBase(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBntClickedSetHosts();
    DECLARE_MESSAGE_MAP()
};
