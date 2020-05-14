#pragma once

#include "CTabCalc.h"
#include "CTabSub.h"
#include "CTabMask.h"
#include "CTabWild.h"

class CNetCalcDlg : public CDialogEx {
public:
    CNetCalcDlg(CWnd* pParent = nullptr);   // Standard constructor

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_NETCALC_DIALOG };
    #endif
protected:
    HICON m_hIcon;

    CTabCtrl m_ctrTabMain;

    CTabCalc m_tabCalc;
    CTabSub  m_tabSub;
    CTabMask m_tabMask;
    CTabWild m_tabWild;

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
    virtual void OnOK() override;
    virtual void OnCancel() override;

    void initTabs();

    // Generated message map functions
    afx_msg void OnTcnSelChangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
};

