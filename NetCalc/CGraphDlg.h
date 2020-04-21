#pragma once

// CGraphDlg dialog
class CGraphDlg : public CDialogEx {
    DECLARE_DYNAMIC(CGraphDlg)

public:
    CGraphDlg(CWnd* pParent = nullptr);   // standard constructor
    virtual ~CGraphDlg();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_GRAPH_DIALOG };
    #endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
};
