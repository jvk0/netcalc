#include "pch.h"

#include "resource.h"

#include "NetCalc.h"
#include "CTabWild.h"

// CTabWild dialog

IMPLEMENT_DYNAMIC(CTabWild, CDialogEx)

CTabWild::CTabWild(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_TAB3, pParent)
{
}

CTabWild::~CTabWild()
{
}

void CTabWild::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

void CTabWild::OnOK()
{
    // Prevent Enter from closing the dialog  
    if ((GetKeyState(VK_RETURN) & 0x8000) == 0)
        CTabWild::OnOK();
}

void CTabWild::OnCancel()
{
    // Prevent Esc from closing the dialog  
    if ((GetKeyState(VK_ESCAPE) & 0x8000) == 0)
        CTabWild::OnCancel();
}

BOOL CTabWild::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CTabWild, CDialogEx)
END_MESSAGE_MAP()


// CTabWild message handlers
