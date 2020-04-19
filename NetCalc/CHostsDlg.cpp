#include "pch.h"

#include "resource.h"

#include "NetCalc.h"
#include "CHostsDlg.h"


// CHostsDlg dialog

IMPLEMENT_DYNAMIC(CHostsDlg, CDialogEx)

CHostsDlg::CHostsDlg(const IP4Calc::HostsVect& inHosts, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_HOSTS_DIALOG, pParent),
    m_outHosts(inHosts)
{
}

CHostsDlg::~CHostsDlg()
{
}

IP4Calc::HostsVect CHostsDlg::getHostsVec()
{
    return m_outHosts;
}

void CHostsDlg::initListHosts()
{
    CRect rect;
    m_ctrListHosts.GetClientRect(&rect);
    
    int colWidth = rect.Width() / 2;

    m_ctrListHosts.InsertColumn(0, _T("Požiadavka"), LVCFMT_CENTER, colWidth);
    m_ctrListHosts.InsertColumn(1, _T("Zaokrúhlené "), LVCFMT_CENTER, colWidth);
}

void CHostsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_HDLG_LIST_HOSTS, m_ctrListHosts);
}

void CHostsDlg::OnOK()
{
    // Prevent Enter from closing the dialog  
    if ((GetKeyState(VK_RETURN) & 0x8000) == 0)
        CDialogEx::OnOK();
}

void CHostsDlg::OnCancel()
{
    // Prevent Esc from closing the dialog  
    if ((GetKeyState(VK_ESCAPE) & 0x8000) == 0)
        CDialog::OnCancel();
}

BOOL CHostsDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    initListHosts();

    return TRUE;
}


BEGIN_MESSAGE_MAP(CHostsDlg, CDialogEx)
END_MESSAGE_MAP()


// CHostsDlg message handlers
