#include "pch.h"

#include "NetCalc.h"
#include "CTabSub.h"


// CTabSub dialog

IMPLEMENT_DYNAMIC(CTabSub, CDialogEx)

CTabSub::CTabSub(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_SUB, pParent)
{

}

CTabSub::~CTabSub()
{
}

void CTabSub::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabSub, CDialogEx)
END_MESSAGE_MAP()


// CTabSub message handlers
