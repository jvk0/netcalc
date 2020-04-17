#include "pch.h"

#include "resource.h"

#include "NetCalc.h"
#include "CTabSub.h"

#include "IP4Calc.h"
#include "IP4String.h"

// CTabSub dialog

IMPLEMENT_DYNAMIC(CTabSub, CDialogEx)

CTabSub::CTabSub(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_TAB1, pParent)
    ,m_valIPBaseNet(0)
    ,m_valSTextInfo(_T(""))
{
}

CTabSub::~CTabSub()
{
}

void CTabSub::updateInfoStr()
{
    UpdateData(TRUE);

    int prefix = m_ctrSpinPrefix.GetPos();
    
    m_valSTextInfo.Format(L"Adresa siete: %s/%d\nPočet adries: %d",
        IP4String::addr2Str(m_valIPBaseNet),
        prefix, 
        IP4Calc::numHostsAddr(prefix));

    UpdateData(FALSE);
}

void CTabSub::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_IPAddress(pDX, IDC_TAB1_IP_BASE, m_valIPBaseNet);
    DDX_Control(pDX, IDC_TAB1_SPIN_PREFIX, m_ctrSpinPrefix);
    DDX_Text(pDX, IDC_TAB1_ST_INFO, m_valSTextInfo);
    DDX_Control(pDX, IDC_TAB1_IP_BASE, m_ctrIPBaseNet);
}

void CTabSub::OnOK()
{
    // Prevent Enter from closing the dialog  
    if ((GetKeyState(VK_RETURN) & 0x8000) == 0)
        CDialogEx::OnOK();
}

void CTabSub::OnCancel()
{
    // Prevent Esc from closing the dialog  
    if ((GetKeyState(VK_ESCAPE) & 0x8000) == 0)
        CDialog::OnCancel();
}

BOOL CTabSub::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_ctrIPBaseNet.SetAddress(192, 168, 0, 0);
    m_ctrSpinPrefix.SetRange(1, 32);
    m_ctrSpinPrefix.SetPos(16); // 255.255.0.0

    updateInfoStr();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CTabSub, CDialogEx)
END_MESSAGE_MAP()


// CTabSub message handlers
