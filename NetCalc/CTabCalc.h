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
    CIPAddressCtrl  m_ctrIPAddr;
    CIPAddressCtrl  m_ctrIPMask;
    CStatic         m_ctrSTMask;
    CSpinButtonCtrl m_ctrSpinPref;
    CEdit           m_ctrEdPref;
    CListCtrl       m_ctrListCalc;
    
    DWORD m_valIPmask;

    void initList();
    bool checkMask();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK() override;
    virtual void OnCancel() override;

    afx_msg void OnIPFieldChangedCalcMask(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDeltaPosSpinCalcPref(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBntClickedCalc();
    virtual BOOL OnInitDialog() override;
    DECLARE_MESSAGE_MAP()     
};
