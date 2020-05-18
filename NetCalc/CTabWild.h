#pragma once

// CTabWild dialog
class CTabWild : public CDialogEx {
    DECLARE_DYNAMIC(CTabWild)
public:
    CTabWild(CWnd* pParent = nullptr); // Standard constructor
    virtual ~CTabWild();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_OLE_PL_TAB3 };
    #endif
private:
    static constexpr COLORREF LIST_TEXT_CLR = RGB(72, 140, 234); // Looks better

    CListCtrl m_ctrListResults;

    DWORD m_valIPBase;
    DWORD m_valIPWild;
    DWORD m_valIPAddr;

    void initListResults();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog() override;
    virtual void OnOK() override;
    virtual void OnCancel() override;

    afx_msg void OnBntClickedTest();
    afx_msg void OnBntClickedClear();
    DECLARE_MESSAGE_MAP()
};
