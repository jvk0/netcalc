#pragma once


// CTabMask dialog
class CTabMask : public CDialogEx {
    DECLARE_DYNAMIC(CTabMask)

public:
    CTabMask(CWnd* pParent = nullptr);  // Standard constructor
    virtual ~CTabMask();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_OLE_PL_TAB2 };
    #endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK() override;
    virtual void OnCancel() override;

    DECLARE_MESSAGE_MAP()
};
