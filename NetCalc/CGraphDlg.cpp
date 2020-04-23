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
    m_valSTextUnused.Format(L"Nevyužité Adresy (%.2f%%)", m_unusedPct);
    m_valSTextUsed.Format(L"Využité Adresy (%.2f%%)", m_usedPct);
}

CGraphDlg::~CGraphDlg()
{
}

void CGraphDlg::drawGraph(CDC& dc)
{
    // Margin for graph drawing area 
    constexpr int DRAW_MARGIN = 15;
    // For degree calculation
    constexpr double TAU = 2.0 * 3.14159265359;	

    CRect drawRect;
    GetClientRect(&drawRect);

    // Set drawing area 
    drawRect.top    += DRAW_MARGIN;
    drawRect.left   += DRAW_MARGIN;
    drawRect.bottom -= LONG(drawRect.Height() / 7 + DRAW_MARGIN); // Room for button
    drawRect.right  -= LONG(drawRect.Width() / 2.5 + DRAW_MARGIN); // Room for legend

    // dc.FillSolidRect(&drawRect, RGB(255, 255, 0)); // TODO: Remove

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

    int  endX;
    int  endY;
    int  beginX;
    int  beginY;

    beginX = centerX + radius;
    beginY = centerY;

    CBrush tmpBrush;
    CPen   tmpPen;

    double nextVal = m_unusedPct / 100;
    for (int i = 0; i < 2; i++) {
        endX = centerX + int(radius * std::cos(TAU * nextVal));
        endY = centerY - int(radius * std::sin(TAU * nextVal));

        tmpBrush.CreateSolidBrush(sliceColor[i]);
        if (m_usedPct == 100)
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

        nextVal = 1.0;
    }

}

void CGraphDlg::drawLegend(CDC& dc)
{
    CRect drawRect;
    GetClientRect(&drawRect);

}

void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_GRAPH_ST_UNUSED, m_valSTextUnused);
    DDX_Text(pDX, IDC_GRAPH_ST_USED, m_valSTextUsed);
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
    drawLegend(dc);
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