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
    int                m_sumHosts;

    CListCtrl          m_ctrListHosts;
    
    CString            m_valEdNum;
    CString            m_valSTextSum;
    
    void addListHostsRow(int num);
    void initListHosts();
    void updateSumText();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
    virtual void OnOK() override;
    virtual void OnCancel() override;

    virtual BOOL OnInitDialog() override;
    afx_msg void OnBntClickedAdd();
    DECLARE_MESSAGE_MAP()  
public:
    afx_msg void OnBtnClickedRemove();
};
