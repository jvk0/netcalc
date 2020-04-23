#include "pch.h"

#include <cmath>

#include "resource.h"

#include "NetCalc.h"
#include "CGraphDlg.h"


// CGraphDlg dialog

IMPLEMENT_DYNAMIC(CGraphDlg, CDialogEx)

CGraphDlg::CGraphDlg(double usedPct, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_GRAPH_DIALOG, pParent),
    m_usedPct(usedPct)
{
}

CGraphDlg::~CGraphDlg()
{
}

void CGraphDlg::drawGraph(CDC& dc)
{
    // Margin for drawing area 
    constexpr int DRAW_MARGIN = 15;
    // Graph colors
    constexpr COLORREF sliceColor[2] = {RGB(74, 134, 232), RGB(106, 168, 79)};
    constexpr COLORREF outlineColor  = RGB(240, 240, 240);
    // For degree calculation
    constexpr double TAU = 2.0 * 3.14159265359;	

    CRect drawRect;
    GetClientRect(&drawRect);

    // Set drawing area 
    drawRect.top    += DRAW_MARGIN;
    drawRect.left   += DRAW_MARGIN;
    drawRect.bottom -= (drawRect.Height() / 9 + DRAW_MARGIN); // Room for button
    drawRect.right  -= DRAW_MARGIN;

    dc.FillSolidRect(&drawRect, RGB(255, 0, 255)); // TODO: Remove

    // Pie graph center points
    int centerX = drawRect.left + drawRect.Width() / 2;
    int centerY = drawRect.top  + drawRect.Height() / 2;

    // Pie graph radius
    int radius = min(drawRect.Height(), drawRect.Width()) / 2;

    // Pie graph bounding rectangle
    CRect pieRect;
    pieRect.top    = centerY - radius;
    pieRect.left   = centerX - radius;
    pieRect.bottom = centerY + radius;
    pieRect.right  = centerX + radius;

    int  newX;
    int  newY;
    int  lastX;
    int  lastY;

    lastX = centerX + radius;
    lastY = centerY;

    CBrush tmpBrush;
    CPen   tmpPen;

    double nextVal = ( 100 - m_usedPct) / 100;
    for (int i = 0; i < 2; i++) {
        newX = centerX + int(radius * std::cos(TAU * nextVal));
        newY = centerY - int(radius * std::sin(TAU * nextVal));

        tmpBrush.CreateSolidBrush(sliceColor[i]);
        if (m_usedPct == 100)
            tmpPen.CreatePen(PS_SOLID, 1, sliceColor[i]); // No outline
        else
            tmpPen.CreatePen(PS_SOLID, 1, outlineColor);
   
        dc.SelectObject(&tmpPen);
        dc.SelectObject(&tmpBrush);

        dc.Pie(pieRect, CPoint(lastX, lastY), CPoint(newX, newY));
        
        tmpBrush.Detach();
        tmpPen.Detach();
        
        lastX   = newX;
        lastY   = newY;

        nextVal = 1.0;
    }
}

void CGraphDlg::drawLegend(CDC& dc)
{
}

void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

void CGraphDlg::OnOK()
{
    // Prevent Enter from closing the dialog  
    if ((GetKeyState(VK_RETURN) & 0x8000) == 0)
        CDialogEx::OnOK();
}

BEGIN_MESSAGE_MAP(CGraphDlg, CDialogEx)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CGraphDlg message handlers


void CGraphDlg::OnPaint()
{
    CPaintDC dc(this); 
    
    drawGraph(dc);
}
