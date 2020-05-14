#pragma once


// CTabWild dialog
class CTabWild : public CDialogEx {
    DECLARE_DYNAMIC(CTabWild)
public:
    CTabWild(CWnd* pParent = nullptr);   // standard constructor
    virtual ~CTabWild();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_OLE_PL_TAB3 };
    #endif
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK() override;
    virtual void OnCancel() override;

    virtual BOOL OnInitDialog() override;
    afx_msg void OnBntClickedTest();
    DECLARE_MESSAGE_MAP()
public:
    CIPAddressCtrl m_ctrIPBase;
    CIPAddressCtrl m_ctrIPWild;

    DWORD m_valIPBase;
    DWORD m_valIPWild;
    DWORD m_valIPAddr;
private:
    void initListResults();
public:
    CListCtrl m_ctrListResults;
    afx_msg void OnBntClickedClear();
};
