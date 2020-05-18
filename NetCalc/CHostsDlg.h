#pragma once

#include "IP4Calc.h"

// CHostsDlg dialog
class CHostsDlg : public CDialogEx {
    DECLARE_DYNAMIC(CHostsDlg)
public:
    CHostsDlg(const IP4Calc::HostsVect& inHosts, CWnd* pParent = nullptr);
    virtual ~CHostsDlg();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_HOSTS_DIALOG };
    #endif

    IP4Calc::HostsVect getHostsVec();
    int getSumHosts();
private:
    IP4Calc::HostsVect m_outHosts;
    int                m_sumHosts;

    HICON m_dlgIcon;

    CListCtrl          m_ctrListHosts;
    
    CString            m_valEdNum;
    CString            m_valSTextSum;
    
    void addListHostsRow(int num);
    void initListHosts();
    void updateSumText();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
    virtual BOOL OnInitDialog() override;
    virtual void OnOK() override;
    virtual void OnCancel() override;

    afx_msg void OnBntClickedAdd();
    afx_msg void OnBtnClickedRemove();
    afx_msg void OnBntClickedClear();
    DECLARE_MESSAGE_MAP()  
};
