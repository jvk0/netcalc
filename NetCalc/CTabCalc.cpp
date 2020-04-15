#include "pch.h"

#include "resource.h"

#include "CNetCalcApp.h"
#include "CTabCalc.h"

#include "IP4Calc.h"


// CTabCalc dialog

IMPLEMENT_DYNAMIC(CTabCalc, CDialogEx)

CTabCalc::CTabCalc(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_CALC, pParent)
    , m_valEdPref(_T(""))
{

}

CTabCalc::~CTabCalc()
{
}

bool CTabCalc::checkMask()
{
    DWORD mask;
    m_ctrIPMask.GetAddress(mask);

    if (!IP4Calc::isMaskValid(mask)) {
        m_ctrSTMask.SetWindowTextW(L"Maska nie je platná!");
        return false;
    } else {
        m_ctrSTMask.SetWindowTextW(L"Maska je platná :)");
        return true;
    }
}

void CTabCalc::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_IP_CALCIP, m_ctrIPAddr);
    DDX_Control(pDX, IDC_IP_CALCMASK, m_ctrIPMask);
    DDX_Control(pDX, IDC_ST_MASK, m_ctrSTMask);
    DDX_Control(pDX, IDC_ED_CALCPREF, m_ctrEdPref);
    DDX_Text(pDX, IDC_ED_CALCPREF, m_valEdPref);
    DDX_Control(pDX, IDC_SPIN_CALCPREF, m_ctrSpinPref);
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

    m_ctrEdPref.SetLimitText(2);
    m_valEdPref = L"24"; // 255.255.255.0
    m_ctrSpinPref.SetRange(1, 32);

    UpdateData(FALSE);

    return TRUE;
}


BEGIN_MESSAGE_MAP(CTabCalc, CDialogEx)
    #pragma warning(disable: 26454)
    ON_NOTIFY(IPN_FIELDCHANGED, IDC_IP_CALCMASK, &CTabCalc::OnIPFieldChangedCalcMask)
    #pragma warning(default: 26454)
END_MESSAGE_MAP()


// CTabCalc message handlers


void CTabCalc::OnIPFieldChangedCalcMask(NMHDR* pNMHDR, LRESULT* pResult)
{
    static bool prevError = false;

    LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);

    if (!checkMask()) {
        if (!prevError) {
            MessageBeep(MB_ICONEXCLAMATION);
            prevError = true;
        }
    } else {
        prevError = false;
    }

    *pResult = 0;
}
