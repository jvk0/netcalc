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
    CIPAddressCtrl m_ctrIPCalc;
    CIPAddressCtrl m_ctrIPMask;

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog() override;
    DECLARE_MESSAGE_MAP()
public:
    
};
