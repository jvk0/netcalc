#pragma once


// CTabCalc dialog
class CTabCalc : public CDialogEx {
    DECLARE_DYNAMIC(CTabCalc)

public:
    CTabCalc(CWnd* pParent = nullptr);  // Standard constructor
    virtual ~CTabCalc();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_OLE_PL_TAB0 };
    #endif

protected:
    CIPAddressCtrl  m_ctrIPAddr;
    CIPAddressCtrl  m_ctrIPMask;
    CStatic         m_ctrSTextMaskValid;
    CSpinButtonCtrl m_ctrSpinPrefix;
    CEdit           m_ctrEdPrefix;
   
    DWORD m_valIPAddr;
    DWORD m_valIPMask;

    // Output control variables (Dec)
    CEdit m_ctrEdOutAddr;
    CEdit m_ctrEdOutMask;
    CEdit m_ctrEdOutWild;
    CEdit m_ctrEdOutNet;
    CEdit m_ctrEdOutBrd;
    CEdit m_ctrEdOutMin;
    CEdit m_ctrEdOutMax;
    CEdit m_ctrEdOutNum;

    bool checkMask();
    void clearOutput();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK() override;
    virtual void OnCancel() override;

    afx_msg void OnIPFieldChangedCalcMask(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDeltaPosSpinCalcPref(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBntClickedCalc();
    virtual BOOL OnInitDialog() override;
    DECLARE_MESSAGE_MAP()     
};
