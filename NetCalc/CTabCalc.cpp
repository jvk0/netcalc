#include "pch.h"

#include "resource.h"

#include "NetCalc.h"
#include "CTabCalc.h"

#include "IP4Calc.h"
#include "IP4Format.h"

// CTabCalc dialog

IMPLEMENT_DYNAMIC(CTabCalc, CDialogEx)

CTabCalc::CTabCalc(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_TAB0, pParent)
    , m_valIPAddr(0)
    , m_valIPMask(0)
    
{

}

CTabCalc::~CTabCalc()
{
}

bool CTabCalc::checkMask()
{
    UpdateData(TRUE);

    if (!IP4Calc::isMaskValid(m_valIPMask)) {
        m_ctrSTextMaskValid.SetWindowTextW(L"Maska nie je platná!");
        return false;
    } else {
        m_ctrSTextMaskValid.SetWindowTextW(L"Maska je platná :)");
        return true;
    }
}

void CTabCalc::clearOutput()
{
}

void CTabCalc::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB0_IP_ADDR, m_ctrIPAddr);
    DDX_Control(pDX, IDC_TAB0_IP_MASK, m_ctrIPMask);
    DDX_Control(pDX, IDC_TAB0_ST_MASKVALID, m_ctrSTextMaskValid);
    DDX_Control(pDX, IDC_TAB0_SPIN_PREFIX, m_ctrSpinPrefix);
    DDX_IPAddress(pDX, IDC_TAB0_IP_MASK, m_valIPMask);
    DDX_Control(pDX, IDC_TAB0_ED_PREFIX, m_ctrEdPrefix);
    DDX_Control(pDX, IDC_TAB0_ED_OADDR, m_ctrEdOutAddr);
    DDX_Control(pDX, IDC_TAB0_ED_OMASK, m_ctrEdOutMask);
    DDX_Control(pDX, IDC_TAB0_ED_OWILD, m_ctrEdOutWild);
    DDX_Control(pDX, IDC_TAB0_ED_ONET, m_ctrEdOutNet);
    DDX_Control(pDX, IDC_TAB0_ED_OBRD, m_ctrEdOutBrd);
    DDX_Control(pDX, IDC_TAB0_ED_OMIN, m_ctrEdOutMin);
    DDX_Control(pDX, IDC_TAB0_ED_OMAX, m_ctrEdOutMax);
    DDX_Control(pDX, IDC_TAB0_ED_ONUM, m_ctrEdOutNum);
    DDX_IPAddress(pDX, IDC_TAB0_IP_ADDR, m_valIPAddr);
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

    m_ctrIPAddr.SetAddress(192, 168, 1, 0);
    m_ctrIPMask.SetAddress(255, 255, 255, 0); // Valid mask
    m_ctrIPMask.SetFieldRange(0, 1, 255);

    checkMask();

    m_ctrSpinPrefix.SetRange(1, 32);
    m_ctrSpinPrefix.SetPos(24); // 255.255.255.0
    
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
        m_ctrSpinPrefix.SetPos(IP4Calc::mask2Prefix(m_valIPMask));
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
    
    m_valIPMask = IP4Calc::prefix2Mask(newNum);
    
    UpdateData(FALSE);
    
    checkMask();

    *pResult = 0;
}

void CTabCalc::OnBntClickedCalc()
{
    if (!checkMask()) // UpdateData(TRUE) was called in checkMask()
        return;
    
    using namespace IP4Calc;
    using namespace IP4Format;

    CString tmpStr;

    int prefix = m_ctrSpinPrefix.GetPos();

    // Addr
    m_ctrEdOutAddr.SetWindowTextW(addr2Str(m_valIPAddr));

    // Mask and prefix lenght
    tmpStr.Format(L"%s --> /%d", addr2Str(m_valIPMask), prefix);
    m_ctrEdOutMask.SetWindowTextW(tmpStr);

    // Wildcard
    m_ctrEdOutWild.SetWindowTextW(addr2Str(~m_valIPMask));

    // Network addr
    tmpStr.Format(L"%s/%d", addr2Str(netAddr(m_valIPAddr, m_valIPMask)), prefix);
    m_ctrEdOutNet.SetWindowTextW(tmpStr);

    // Broadcast addr
    m_ctrEdOutBrd.SetWindowTextW(addr2Str(brdAddr(m_valIPAddr, m_valIPMask)));

    // Min. host
    m_ctrEdOutMin.SetWindowTextW(addr2Str(firstAddr(m_valIPAddr, m_valIPMask)));

    // Max. host
    m_ctrEdOutMax.SetWindowTextW(addr2Str(lastAddr(m_valIPAddr, m_valIPMask)));

    // Num. of hosts
    tmpStr.Format(L"%d", numHostsAddr(prefix));
    m_ctrEdOutNum.SetWindowTextW(tmpStr);
}
