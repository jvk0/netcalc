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
    ,m_valIPAddr(0)
    ,m_valIPMask(0)
    ,m_valEdOutAddr(_T(""))
    ,m_valEdOutMask(_T(""))
    ,m_valEdOutWild(_T(""))
    ,m_valEdOutNet(_T(""))
    ,m_valEdOutBrd(_T(""))
    ,m_valEdOutMin(_T(""))
    ,m_valEdOutMax(_T(""))
    ,m_valEdOutNum(_T(""))
    ,m_valEdOutBinAddr(_T(""))
    ,m_valEdOutBinMask(_T(""))
    ,m_valEdOutBinWild(_T(""))
    ,m_valEdOutBinNet(_T(""))
    ,m_valEdOutBinBrd(_T(""))
    ,m_valEdOutBinMin(_T(""))
    ,m_valEdOutBinMax(_T(""))
    ,m_valSTextOutInfo(_T("Info:"))
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
    m_valEdOutAddr = L"";
    m_valEdOutMask = L"";
    m_valEdOutWild = L"";
    m_valEdOutNet  = L"";
    m_valEdOutBrd  = L"";
    m_valEdOutMin  = L"";
    m_valEdOutMax  = L"";
    m_valEdOutNum  = L"";

    m_valEdOutBinAddr = L"";
    m_valEdOutBinMask = L"";
    m_valEdOutBinWild = L"";
    m_valEdOutBinNet  = L"";
    m_valEdOutBinBrd  = L"";
    m_valEdOutBinMin  = L"";
    m_valEdOutBinMax  = L"";

    m_valSTextOutInfo = L"Info:";

    UpdateData(FALSE);
}

void CTabCalc::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB0_IP_ADDR, m_ctrIPAddr);
    DDX_Control(pDX, IDC_TAB0_IP_MASK, m_ctrIPMask);
    DDX_Control(pDX, IDC_TAB0_ST_MASKVALID, m_ctrSTextMaskValid);
    DDX_Control(pDX, IDC_TAB0_SPIN_PREFIX, m_ctrSpinPrefix);
    DDX_Control(pDX, IDC_TAB0_ED_PREFIX, m_ctrEdPrefix);
    DDX_IPAddress(pDX, IDC_TAB0_IP_ADDR, m_valIPAddr);
    DDX_IPAddress(pDX, IDC_TAB0_IP_MASK, m_valIPMask);
    DDX_Text(pDX, IDC_TAB0_ED_OADDR, m_valEdOutAddr);
    DDX_Text(pDX, IDC_TAB0_ED_OMASK, m_valEdOutMask);
    DDX_Text(pDX, IDC_TAB0_ED_OWILD, m_valEdOutWild);
    DDX_Text(pDX, IDC_TAB0_ED_ONET, m_valEdOutNet);
    DDX_Text(pDX, IDC_TAB0_ED_OBRD, m_valEdOutBrd);
    DDX_Text(pDX, IDC_TAB0_ED_OMIN, m_valEdOutMin);
    DDX_Text(pDX, IDC_TAB0_ED_OMAX, m_valEdOutMax);
    DDX_Text(pDX, IDC_TAB0_ED_ONUM, m_valEdOutNum);
    DDX_Text(pDX, IDC_TAB0_ED_OBADDR, m_valEdOutBinAddr);
    DDX_Text(pDX, IDC_TAB0_ED_OBMASK, m_valEdOutBinMask);
    DDX_Text(pDX, IDC_TAB0_ED_OBWILD, m_valEdOutBinWild);
    DDX_Text(pDX, IDC_TAB0_ED_OBNET, m_valEdOutBinNet);
    DDX_Text(pDX, IDC_TAB0_ED_OBBRD, m_valEdOutBinBrd);
    DDX_Text(pDX, IDC_TAB0_ED_OBMIN, m_valEdOutBinMin);
    DDX_Text(pDX, IDC_TAB0_ED_OBMAX, m_valEdOutBinMax);
    DDX_Text(pDX, IDC_TAB0_ST_OINFO, m_valSTextOutInfo);
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
    if (!checkMask()) { // UpdateData(TRUE) was called in checkMask()
        clearOutput();
        MessageBox(L"Zadajte platnú masku siete!", L"Neplatná maska", MB_OK | MB_ICONERROR);
        return;
    } 

    using namespace IP4Calc;
    using namespace IP4Format;

    CString tmpStr;
    IP4Addr tmpAddr;

    int prefix = m_ctrSpinPrefix.GetPos();

    // Addr.
    m_valEdOutAddr    = addr2Str(m_valIPAddr);
    m_valEdOutBinAddr = addr2BinStr(m_valIPAddr);
    
    // Mask and prefix lenght
    tmpStr.Format(L"%s --> /%d", addr2Str(m_valIPMask), prefix);
    m_valEdOutMask    = tmpStr;
    m_valEdOutBinMask = addr2BinStr(m_valIPMask);
    
    // Wildcard
    m_valEdOutWild    = addr2Str(~m_valIPMask);
    m_valEdOutBinWild = addr2BinStr(~m_valIPMask);

    // Network addr.
    tmpAddr           = netAddr(m_valIPAddr, m_valIPMask);
    tmpStr.Format(L"%s/%d", addr2Str(tmpAddr), prefix);
    m_valEdOutNet     = tmpStr;
    m_valEdOutBinNet  = addr2BinStr(tmpAddr);
    
    // Broadcast addr.
    tmpAddr           = brdAddr(m_valIPAddr, m_valIPMask);
    m_valEdOutBrd     = addr2Str(tmpAddr);
    m_valEdOutBinBrd  = addr2BinStr(tmpAddr);

    // Min. host
    tmpAddr           = firstAddr(m_valIPAddr, m_valIPMask);
    m_valEdOutMin     = addr2Str(tmpAddr);
    m_valEdOutBinMin  = addr2BinStr(tmpAddr);

    // Max. host
    tmpAddr           = lastAddr(m_valIPAddr, m_valIPMask);
    m_valEdOutMax     = addr2Str(tmpAddr);
    m_valEdOutBinMax  = addr2BinStr(tmpAddr);
    
    // Num. of hosts
    tmpStr.Format(L"%d", numHostsAddr(prefix));
    m_valEdOutNum     = tmpStr;

    UpdateData(FALSE);
}
