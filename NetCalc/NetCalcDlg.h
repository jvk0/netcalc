#pragma once

class CNetCalcDlg : public CDialogEx {
public:
    CNetCalcDlg(CWnd* pParent = nullptr);   // Standard constructor

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_NETCALC_DIALOG };
    #endif
protected:
    HICON m_hIcon;

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
    virtual void OnOK() override;
    virtual void OnCancel() override;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
};
