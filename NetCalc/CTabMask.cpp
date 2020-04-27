#include "pch.h"

#include "resource.h"

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

void CTabMask::OnOK()
{
    // Prevent Enter from closing the dialog  
    if ((GetKeyState(VK_RETURN) & 0x8000) == 0)
        CDialogEx::OnOK();
}

void CTabMask::OnCancel()
{
    // Prevent Esc from closing the dialog  
    if ((GetKeyState(VK_ESCAPE) & 0x8000) == 0)
        CDialog::OnCancel();
}

BOOL CTabMask::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CTabMask, CDialogEx)
END_MESSAGE_MAP()

// CTabMask message handlers

