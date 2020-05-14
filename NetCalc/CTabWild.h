#pragma once


// CTabWild dialog
class CTabWild : public CDialogEx {
    DECLARE_DYNAMIC(CTabWild)
public:
    CTabWild(CWnd* pParent = nullptr);   // standard constructor
    virtual ~CTabWild();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_OLE_PL_TAB3 };
    #endif
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK() override;
    virtual void OnCancel() override;

    virtual BOOL OnInitDialog() override;
    DECLARE_MESSAGE_MAP()
};
