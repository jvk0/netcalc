#pragma once


// CHostsDlg dialog
class CHostsDlg : public CDialogEx {
    DECLARE_DYNAMIC(CHostsDlg)

public:
    CHostsDlg(CWnd* pParent = nullptr); // Standard constructor
    virtual ~CHostsDlg();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_HOSTS_DIALOG };
    #endif
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
};
