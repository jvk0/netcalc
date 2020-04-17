#pragma once


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
    CSpinButtonCtrl m_ctrSpinPrefix;
    
    DWORD   m_valIPBaseNet;
    CString m_valSTextInfo;
    
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK() override;
    virtual void OnCancel() override;

    virtual BOOL OnInitDialog() override;
    DECLARE_MESSAGE_MAP()
};
