#include "pch.h"

#include <cmath>

#include "resource.h"

#include "NetCalc.h"
#include "CGraphDlg.h"

// CGraphDlg dialog

IMPLEMENT_DYNAMIC(CGraphDlg, CDialogEx)

CGraphDlg::CGraphDlg(double usedPct, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_GRAPH_DIALOG, pParent),
    m_usedPct(usedPct),
    m_unusedPct(100 - usedPct)
{
    m_dlgIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); // Main app icon

    m_valSTextUnused.Format(L"Nevyužité Adresy (%.2f%%)", m_unusedPct);
    m_valSTextUsed.Format(L"Využité Adresy (%.2f%%)", m_usedPct);
}

CGraphDlg::~CGraphDlg()
{
}

void CGraphDlg::drawGraph(CDC& dc)
{
    // Margins for graph drawing area 
    constexpr int TOP_MARGIN    = 11;
    constexpr int LEFT_MARGIN   = 13;
    constexpr int BOTTOM_MARGIN = 10;
    constexpr int RIGHT_MARGIN  = 42;
    // Graph border
    constexpr int BORDER        = 5;
    // For degree calculation
    constexpr double TAU        = 2.0 * 3.14159265359;	

    CRect drawRect;
    GetClientRect(&drawRect);

    // Set drawing area 
    drawRect.top    += TOP_MARGIN;
    drawRect.left   += LEFT_MARGIN;
    drawRect.bottom -= LONG(drawRect.Height() / 7 + BOTTOM_MARGIN); // Room for button
    drawRect.right  -= LONG(drawRect.Width() / 3 + RIGHT_MARGIN); // Room for legend

    // Pie graph radius
    int radius = min(drawRect.Height(), drawRect.Width()) / 2;

    // Pie graph center points
    int centerX = drawRect.left + radius;
    int centerY = drawRect.top  + drawRect.Height() / 2;  

    // Pie graph bounding rectangle
    CRect pieRect;
    pieRect.top    = centerY - radius;
    pieRect.left   = centerX - radius;
    pieRect.bottom = centerY + radius;
    pieRect.right  = centerX + radius;

    dc.DrawEdge(pieRect, EDGE_ETCHED, BF_RECT);

    pieRect.DeflateRect(BORDER, BORDER);
    
    int  endX;
    int  endY;
    int  beginX;
    int  beginY;

    beginX = centerX + radius;
    beginY = centerY;

    CBrush tmpBrush;
    CPen   tmpPen;

    double endStep = m_unusedPct / 100;
    for (int i = 0; i < 2; i++) {
        endX = centerX + int(radius * std::cos(TAU * endStep));
        endY = centerY - int(radius * std::sin(TAU * endStep));

        tmpBrush.CreateSolidBrush(sliceColor[i]);
        if (!m_unusedPct)
            tmpPen.CreatePen(PS_SOLID, 1, sliceColor[i]); // No outline
        else
            tmpPen.CreatePen(PS_SOLID, 1, outlineColor);
   
        dc.SelectObject(&tmpPen);
        dc.SelectObject(&tmpBrush);

        dc.Pie(pieRect, CPoint(beginX, beginY), CPoint(endX, endY));
        
        tmpBrush.Detach();
        tmpPen.Detach();
        
        beginX   = endX;
        beginY   = endY;

        endStep  = 1.0;
    }
}

void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);

    DDX_Text(pDX, IDC_GRAPH_ST_UNUSED, m_valSTextUnused);
    DDX_Text(pDX, IDC_GRAPH_ST_USED, m_valSTextUsed);
}

BOOL CGraphDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetIcon(m_dlgIcon, TRUE);
    SetIcon(m_dlgIcon, FALSE);

    return TRUE;
}

void CGraphDlg::OnOK()
{
    // Prevent Enter from closing the dialog  
    if ((GetKeyState(VK_RETURN) & 0x8000) == 0)
        CDialogEx::OnOK();
}


BEGIN_MESSAGE_MAP(CGraphDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CGraphDlg message handlers


void CGraphDlg::OnPaint()
{
    CPaintDC dc(this); 
    
    drawGraph(dc);
}

HBRUSH CGraphDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    if (nCtlColor == CTLCOLOR_STATIC) {
        switch (pWnd->GetDlgCtrlID()) {
            case IDC_GRAPH_ST_UNUSED:
                pDC->SetTextColor(sliceColor[0]);
                break;
            case IDC_GRAPH_ST_USED:
                pDC->SetTextColor(sliceColor[1]);
                break;
        }
    }

    return hbr;
}
