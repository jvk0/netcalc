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
    
    virtual void OnOK() override;
    virtual void OnCancel() override;

    virtual BOOL OnInitDialog() override;
    DECLARE_MESSAGE_MAP()
};
