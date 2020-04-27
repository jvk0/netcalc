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
    , m_valEditOutMask(_T(""))
    , m_valEditOutWild(_T(""))
    , m_valEditOutPrefix(_T(""))
    , m_valEditOutBinMask(_T(""))
    , m_valEditOutBinWild(_T(""))
{

}

CTabMask::~CTabMask()
{
}

void CTabMask::initComboMask()
{
    for (int i = 0; i < 32; i++)
        m_ctrComboMask.InsertString(i, IP4String::addr2Str(IP4Calc::prefix2Mask(i + 1)));

    m_ctrComboMask.SetCurSel(DEFAULT_PREFIX - 1);
}

void CTabMask::calcOutput(int prefix)
{
    IP4Calc::IP4Addr mask = IP4Calc::prefix2Mask(prefix);
    IP4Calc::IP4Addr wild = ~mask;

    m_valEditOutMask    = IP4String::addr2Str(mask);
    m_valEditOutBinMask = IP4String::addr2BinStr(mask);

    m_valEditOutWild    = IP4String::addr2Str(wild);
    m_valEditOutBinWild = IP4String::addr2BinStr(wild);

    m_valEditOutPrefix.Format(L"/%d", prefix);

    UpdateData(FALSE);
}

void CTabMask::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB2_COMBO_MASK, m_ctrComboMask);
    DDX_Control(pDX, IDC_TAB2_SLIDER_MASK, m_ctrSliderMask);
    DDX_Text(pDX, IDC_TAB2_ED_OMASK, m_valEditOutMask);
    DDX_Text(pDX, IDC_TAB2_ED_OWILD, m_valEditOutWild);
    DDX_Text(pDX, IDC_TAB2_ED_OPREFIX, m_valEditOutPrefix);
    DDX_Text(pDX, IDC_TAB2_ED_OBMASK, m_valEditOutBinMask);
    DDX_Text(pDX, IDC_TAB2_ED_OBWILD, m_valEditOutBinWild);
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
   
    initComboMask();

    m_ctrSliderMask.SetRange(1, 32, TRUE);
    m_ctrSliderMask.SetPos(DEFAULT_PREFIX);
    
    calcOutput(DEFAULT_PREFIX);

    return TRUE;
}

BEGIN_MESSAGE_MAP(CTabMask, CDialogEx)
    ON_CBN_SELCHANGE(IDC_TAB2_COMBO_MASK, &CTabMask::OnComboSelChangeMask)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CTabMask message handlers


void CTabMask::OnComboSelChangeMask()
{
    int selPrefix = m_ctrComboMask.GetCurSel() + 1;

    m_ctrSliderMask.SetPos(selPrefix);

    calcOutput(selPrefix);
}

void CTabMask::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if (pScrollBar->GetDlgCtrlID() == IDC_TAB2_SLIDER_MASK) {
        m_ctrComboMask.SetCurSel(m_ctrSliderMask.GetPos() - 1);
        calcOutput(m_ctrSliderMask.GetPos());
    }

    CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
