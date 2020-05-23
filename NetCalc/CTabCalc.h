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
private:
    CIPAddressCtrl  m_ctrIPAddr;
    CIPAddressCtrl  m_ctrIPMask;
    CStatic         m_ctrSTextMaskValid;
    CSpinButtonCtrl m_ctrSpinPrefix;
    CEdit           m_ctrEdPrefix;
   
    DWORD m_valIPAddr;
    DWORD m_valIPMask;

    // Output variables (Dec)
    CString m_valEdOutAddr;
    CString m_valEdOutMask;
    CString m_valEdOutWild;
    CString m_valEdOutNet;
    CString m_valEdOutBrd;
    CString m_valEdOutMin;
    CString m_valEdOutMax;
    CString m_valEdOutNum;

    // Output variables (Bin)
    CString m_valEdOutBinAddr;
    CString m_valEdOutBinMask;
    CString m_valEdOutBinWild;
    CString m_valEdOutBinNet;
    CString m_valEdOutBinBrd;
    CString m_valEdOutBinMin;
    CString m_valEdOutBinMax;

    // Info string variable
    CString m_valSTextOutInfo;

    bool checkMask();
    void clearOutput();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog() override;
    virtual void OnOK() override;
    virtual void OnCancel() override;

    afx_msg void OnIPFieldChangedCalcAddr(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnIPFieldChangedCalcMask(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDeltaPosSpinCalcPref(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBntClickedCalc();
    afx_msg void OnBntClickedClear();
    DECLARE_MESSAGE_MAP()       
};
