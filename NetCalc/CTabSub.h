#pragma once


// CTabSub dialog
class CTabSub : public CDialogEx {
    DECLARE_DYNAMIC(CTabSub)

public:
    CTabSub(CWnd* pParent = nullptr);   //  Standard constructor
    virtual ~CTabSub();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_OLE_PL_SUB };
    #endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
};
