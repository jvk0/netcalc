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
    CComboBox   m_ctrComboMask;
    CSliderCtrl m_ctrSliderMask;

    // Output variables
    CString m_valEditOutMask;
    CString m_valEditOutWild;
    CString m_valEdOutNum;
    CString m_valEditOutPrefix;
    CString m_valEditOutBinMask;
    CString m_valEditOutBinWild;

    void initComboMask();
    void calcOutput(int prefix);

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK() override;
    virtual void OnCancel() override;

    virtual BOOL OnInitDialog() override;
    afx_msg void OnComboSelChangeMask();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    DECLARE_MESSAGE_MAP()   
private:
    static constexpr int DEFAULT_PREFIX      = 16;
    static constexpr COLORREF OUT_PREFIX_CLR = RGB(0, 0, 255);  
};
