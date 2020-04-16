#include "pch.h"

#include "resource.h"

#include "NetCalc.h"
#include "CTabCalc.h"

#include "IP4Calc.h"


// CTabCalc dialog

IMPLEMENT_DYNAMIC(CTabCalc, CDialogEx)

CTabCalc::CTabCalc(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_TAB0, pParent)
    , m_valIPmask(0)
{

}

CTabCalc::~CTabCalc()
{
}

void CTabCalc::initList()
{
    m_ctrListCalc.InsertColumn(0, L"", LVCFMT_CENTER, 100);
    m_ctrListCalc.InsertColumn(1, L"Decimálna reprezentácia", LVCFMT_CENTER, 200);
    m_ctrListCalc.InsertColumn(2, L"Binárna reprezentácia", LVCFMT_CENTER, 300);
}

bool CTabCalc::checkMask()
{
    UpdateData(TRUE);

    if (!IP4Calc::isMaskValid(m_valIPmask)) {
        m_ctrSTextMaskValid.SetWindowTextW(L"Maska nie je platná!");
        return false;
    } else {
        m_ctrSTextMaskValid.SetWindowTextW(L"Maska je platná :)");
        return true;
    }
}

void CTabCalc::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB0_IP_ADDR, m_ctrIPAddr);
    DDX_Control(pDX, IDC_TAB0_IP_MASK, m_ctrIPMask);
    DDX_Control(pDX, IDC_TAB0_ST_MASKVALID, m_ctrSTextMaskValid);
    DDX_Control(pDX, IDC_TAB0_SPIN_PREFIX, m_ctrSpinPrefix);
    DDX_IPAddress(pDX, IDC_TAB0_IP_MASK, m_valIPmask);
    DDX_Control(pDX, IDC_TAB0_ED_PREFIX, m_ctrEdPrefix);
    DDX_Control(pDX, IDC_TAB0_LIST_CALC, m_ctrListCalc);
}

void CTabCalc::OnOK()
{
    // Prevent Enter from closing the dialog  
    if ((GetKeyState(VK_RETURN) & 0x8000) == 0)
        CDialogEx::OnOK();
}

void CTabCalc::OnCancel()
{
    // Prevent Esc from closing the dialog  
    if ((GetKeyState(VK_ESCAPE) & 0x8000) == 0)
        CDialog::OnCancel();
}

BOOL CTabCalc::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_ctrIPAddr.SetAddress(192, 168, 0, 1);
    m_ctrIPMask.SetAddress(255, 255, 255, 0);
    m_ctrIPMask.SetFieldRange(0, 1, 255);

    checkMask();

    m_ctrSpinPrefix.SetRange(1, 32);
    m_ctrSpinPrefix.SetPos(24); // 255.255.255.0

    initList();
    
    return TRUE;
}


BEGIN_MESSAGE_MAP(CTabCalc, CDialogEx)
    #pragma warning(disable: 26454)
    ON_NOTIFY(IPN_FIELDCHANGED, IDC_TAB0_IP_MASK, &CTabCalc::OnIPFieldChangedCalcMask)
    ON_NOTIFY(UDN_DELTAPOS, IDC_TAB0_SPIN_PREFIX, &CTabCalc::OnDeltaPosSpinCalcPref)
    #pragma warning(default: 26454)
    ON_BN_CLICKED(IDC_TAB0_BTN_CALC, &CTabCalc::OnBntClickedCalc)
END_MESSAGE_MAP()


// CTabCalc message handlers


void CTabCalc::OnIPFieldChangedCalcMask(NMHDR* pNMHDR, LRESULT* pResult)
{
    static bool prevError = false;

    // LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);

    if (!checkMask()) {
        if (!prevError) {
            MessageBeep(MB_ICONEXCLAMATION);
            m_ctrEdPrefix.SetWindowTextW(L"!");
            prevError = true;
        }
    } else {
        // UpdateData(TRUE) was called in checkMask()
        m_ctrSpinPrefix.SetPos(IP4Calc::mask2Prefix(m_valIPmask));
        prevError = false;
    }

    *pResult = 0;
}

void CTabCalc::OnDeltaPosSpinCalcPref(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    
    int newNum = (pNMUpDown->iPos + pNMUpDown->iDelta);

    if (newNum < 1)
        newNum = 1; // Bug fix
    
    m_valIPmask = IP4Calc::prefix2Mask(newNum);
    
    UpdateData(FALSE);
    
    checkMask();

    *pResult = 0;
}

void CTabCalc::OnBntClickedCalc()
{
    // TODO: Add your control notification handler code here
}
