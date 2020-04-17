#include "pch.h"

#include "resource.h"

#include "NetCalc.h"
#include "CTabSub.h"


// CTabSub dialog

IMPLEMENT_DYNAMIC(CTabSub, CDialogEx)

CTabSub::CTabSub(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_TAB1, pParent)
    , m_valIPBaseNet(0)
    , m_valSTextInfo(_T(""))
{

}

CTabSub::~CTabSub()
{
}

void CTabSub::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB1_SPIN_PREFIX, m_ctrSpinPrefix);
    DDX_IPAddress(pDX, IDC_TAT1_IP_BASE, m_valIPBaseNet);
    DDX_Text(pDX, IDC_TAB1_ST_INFO, m_valSTextInfo);
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

    return TRUE;
}


BEGIN_MESSAGE_MAP(CTabSub, CDialogEx)
END_MESSAGE_MAP()


// CTabSub message handlers
