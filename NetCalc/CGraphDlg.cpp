#include "pch.h"

#include <cmath>

#include "resource.h"

#include "NetCalc.h"
#include "CGraphDlg.h"


// CGraphDlg dialog

IMPLEMENT_DYNAMIC(CGraphDlg, CDialogEx)

CGraphDlg::CGraphDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_GRAPH_DIALOG, pParent)
{
}

CGraphDlg::~CGraphDlg()
{
}

void CGraphDlg::drawGraph(CDC& dc)
{
	constexpr int DRAW_MARGIN = 20;
	// Graph colors
	constexpr COLORREF sliceColor[2] = {RGB(255, 0, 0), RGB(0, 255, 0)};
	// For degree calculation
	constexpr double TAU = 2.0 * 3.14159265359;	

	double slice[2] = {0};
	slice[0] = (double) (75 / double(100));
	slice[1] = (double) (25 / double(100));

	CRect drawRect;
	GetClientRect(&drawRect);

	// Set drawing area 
	drawRect.top    += DRAW_MARGIN;
	drawRect.left   += DRAW_MARGIN;
	drawRect.bottom -= DRAW_MARGIN;
	drawRect.right  -= drawRect.Width() / 3 + DRAW_MARGIN;
	
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
	
	double sum = 0;
	for (int i = 0; i < 2; i++) {
		sum += slice[i];

		newX = centerX + int(radius * std::cos(TAU * sum));
		newY = centerY - int(radius * std::sin(TAU * sum));

		CBrush tmpBrush(sliceColor[i]);
		CPen   tmpPen(PS_SOLID, 1, sliceColor[i]);
		
		dc.SelectObject(&tmpPen);
		dc.SelectObject(&tmpBrush);

		dc.Pie(pieRect, CPoint(lastX, lastY), CPoint(newX, newY));

		lastX = newX;
		lastY = newY;
	}
}

void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
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
