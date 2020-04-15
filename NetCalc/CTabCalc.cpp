#include "pch.h"

#include "resource.h"

#include "CNetCalcApp.h"
#include "CTabCalc.h"


// CTabCalc dialog

IMPLEMENT_DYNAMIC(CTabCalc, CDialogEx)

CTabCalc::CTabCalc(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_CALC, pParent)
{

}

CTabCalc::~CTabCalc()
{
}

void CTabCalc::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_IP_IPCALC, m_ctrIPCalc);
    DDX_Control(pDX, IDC_IP_IPMASK, m_ctrIPMask);
}

BOOL CTabCalc::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_ctrIPCalc.SetAddress(192, 168, 0, 1);
    m_ctrIPMask.SetAddress(255, 255, 255, 0);

    return TRUE;
}


BEGIN_MESSAGE_MAP(CTabCalc, CDialogEx)
END_MESSAGE_MAP()


// CTabCalc message handlers
