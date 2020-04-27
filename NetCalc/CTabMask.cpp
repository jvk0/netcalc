#include "pch.h"

#include "resource.h"

#include "NetCalc.h"
#include "CTabMask.h"

#include "IP4Calc.h"
#include "IP4String.h"

// CTabMask dialog

IMPLEMENT_DYNAMIC(CTabMask, CDialogEx)

CTabMask::CTabMask(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_TAB2, pParent)
{

}

CTabMask::~CTabMask()
{
}

void CTabMask::initComboMask()
{
    for (int i = 0; i < 32; i++)
        m_ctrComboMask.InsertString(i, IP4String::addr2Str(IP4Calc::prefix2Mask(i + 1)));

    m_ctrComboMask.SetCurSel(15); // 255.255.0.0
}

void CTabMask::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB2_COMBO_MASK, m_ctrComboMask);
    DDX_Control(pDX, IDC_TAB2_SLIDER_MASK, m_ctrSliderMask);
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
    
    m_ctrSliderMask.SetRange(1, 32, TRUE);
    m_ctrSliderMask.SetPos(16); // 255.255.0.0

    initComboMask();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CTabMask, CDialogEx)
    ON_CBN_SELCHANGE(IDC_TAB2_COMBO_MASK, &CTabMask::OnComboSelChangeMask)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CTabMask message handlers


void CTabMask::OnComboSelChangeMask()
{
    m_ctrSliderMask.SetPos(m_ctrComboMask.GetCurSel() + 1);
}

void CTabMask::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if (pScrollBar->GetDlgCtrlID() == IDC_TAB2_SLIDER_MASK)
        m_ctrComboMask.SetCurSel(m_ctrSliderMask.GetPos() - 1);

    CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
