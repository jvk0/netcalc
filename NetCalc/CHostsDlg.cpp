#include "pch.h"

#include "NetCalc.h"
#include "CHostsDlg.h"


// CHostsDlg dialog

IMPLEMENT_DYNAMIC(CHostsDlg, CDialogEx)

CHostsDlg::CHostsDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_HOSTS_DIALOG, pParent)
{
}

CHostsDlg::~CHostsDlg()
{
}

void CHostsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
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

    return TRUE;
}


BEGIN_MESSAGE_MAP(CHostsDlg, CDialogEx)
END_MESSAGE_MAP()


// CHostsDlg message handlers
