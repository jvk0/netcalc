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
    CString m_valSTextUnused;
    CString m_valSTextUsed;

    void drawGraph(CDC& dc);
    void drawLegend(CDC& dc);

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
    virtual void OnOK() override;

    afx_msg void OnPaint();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    DECLARE_MESSAGE_MAP()
private:
    // Graph colors
    static constexpr COLORREF sliceColor[2] = {RGB(74, 134, 232), RGB(106, 168, 79)};
    static constexpr COLORREF outlineColor  = RGB(240, 240, 240);

    double m_usedPct;
    double m_unusedPct;
};
