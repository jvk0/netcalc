#include "pch.h"

#include "resource.h"

#include "CNetCalcApp.h"
#include "CTabCalc.h"

#include "IP4Calc.h"


// CTabCalc dialog

IMPLEMENT_DYNAMIC(CTabCalc, CDialogEx)

CTabCalc::CTabCalc(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_CALC, pParent)
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
    LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
    
    checkMask();

    *pResult = 0;
}
