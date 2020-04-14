#pragma once


// CTabCalc dialog
class CTabCalc : public CDialogEx {
    DECLARE_DYNAMIC(CTabCalc)

public:
    CTabCalc(CWnd* pParent = nullptr);  // Standard constructor
    virtual ~CTabCalc();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_OLE_PL_CALC };
    #endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
};
