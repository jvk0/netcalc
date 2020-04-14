#include "pch.h"

#include "CNetCalcApp.h"
#include "CTabCalc.h"


// CTabCalc dialog

IMPLEMENT_DYNAMIC(CTabCalc, CDialogEx)

CTabCalc::CTabCalc(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_CALC, pParent)
{

}

CTabCalc::~CTabCalc()
{
}

void CTabCalc::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabCalc, CDialogEx)
END_MESSAGE_MAP()


// CTabCalc message handlers
