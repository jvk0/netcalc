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


BEGIN_MESSAGE_MAP(CHostsDlg, CDialogEx)
END_MESSAGE_MAP()


// CHostsDlg message handlers
