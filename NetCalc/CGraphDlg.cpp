#include "pch.h"

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

void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGraphDlg, CDialogEx)
END_MESSAGE_MAP()


// CGraphDlg message handlers
