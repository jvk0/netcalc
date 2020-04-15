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
    CIPAddressCtrl m_ctrIPAddr;
    CIPAddressCtrl m_ctrIPMask;
    CStatic m_ctrSTMask;

    bool checkMask();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK() override;
    virtual void OnCancel() override;

    afx_msg void OnIPFieldChangedCalcMask(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog() override;
    DECLARE_MESSAGE_MAP()
public:
    CEdit m_ctrEdPref;
    CString m_valEdPref;
    CSpinButtonCtrl m_ctrSpinPref;
    DWORD m_valIPmask;
};
