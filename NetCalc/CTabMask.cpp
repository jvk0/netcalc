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
    DDX_Control(pDX, IDC_TAB2_MASK, m_ctrIPMask);
    DDX_Control(pDX, IDC_TAB2_SPIN_PREFIX, m_ctrSpinPrefix);
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

    m_ctrIPMask.SetAddress(255, 255, 0, 0); // Valid mask
    m_ctrIPMask.SetFieldRange(0, 1, 255);

    m_ctrSpinPrefix.SetRange(1, 32);
    m_ctrSpinPrefix.SetPos(16); // 255.255.0.0

    return TRUE;
}

BEGIN_MESSAGE_MAP(CTabMask, CDialogEx)
END_MESSAGE_MAP()

// CTabMask message handlers
