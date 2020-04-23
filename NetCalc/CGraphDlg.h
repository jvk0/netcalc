#pragma once

// CGraphDlg dialog
class CGraphDlg : public CDialogEx {
    DECLARE_DYNAMIC(CGraphDlg)
public:
    CGraphDlg(double usedPct, CWnd* pParent = nullptr);    // Modified standard constructor
    virtual ~CGraphDlg();

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_GRAPH_DIALOG };
    #endif

protected:
    void drawGraph(CDC& dc);

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
    virtual void OnOK() override;

    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()
private:
    double m_usedPct;
};
