#include "pch.h"

#include "NetCalc.h"
#include "CTabMask.h"


// CTabMask dialog

IMPLEMENT_DYNAMIC(CTabMask, CDialogEx)

CTabMask::CTabMask(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_TAB2, pParent)
{

}

CTabMask::~CTabMask()
{
}

void CTabMask::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTabMask, CDialogEx)
END_MESSAGE_MAP()

// CTabMask message handlers
