#include "pch.h"

#include "resource.h"

#include "NetCalc.h"
#include "CTabSub.h"
#include "CHostsDlg.h"

#include "IP4String.h"

// CTabSub dialog

IMPLEMENT_DYNAMIC(CTabSub, CDialogEx)

CTabSub::CTabSub(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_TAB1, pParent),
    m_calcPrefix(0),
    m_valIPBaseNet(0),
    m_valSTextInfo(_T(""))
{
}

CTabSub::~CTabSub()
{
}

void CTabSub::updateInfoStr()
{
    UpdateData(TRUE);

    DWORD mask = IP4Calc::prefix2Mask(m_calcPrefix);

    m_valSTextInfo.Format(L"Adresa siete: %s/%d\nPočet adries: %d",
        IP4String::addr2Str(m_valIPBaseNet & mask),
        m_calcPrefix,
        IP4Calc::numHostsAddr(m_calcPrefix));

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
    m_calcPrefix = 16; // Manually update prefix 
    
    updateInfoStr();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CTabSub, CDialogEx)
    #pragma warning(disable: 26454)
    ON_NOTIFY(UDN_DELTAPOS, IDC_TAB1_SPIN_PREFIX, &CTabSub::OnDeltaPosSpinPrefix)
    ON_NOTIFY(IPN_FIELDCHANGED, IDC_TAB1_IP_BASE, &CTabSub::OnIPFieldChangedIPBase)
    #pragma warning(default: 26454)
    ON_BN_CLICKED(IDC_TAB1_BTN_SETHOSTS, &CTabSub::OnBntClickedSetHosts)
END_MESSAGE_MAP()


// CTabSub message handlers


void CTabSub::OnDeltaPosSpinPrefix(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    
    m_calcPrefix = (pNMUpDown->iPos + pNMUpDown->iDelta);

    if (m_calcPrefix < 1)
        m_calcPrefix = 1; // Bug fix

    updateInfoStr();

    *pResult = 0;
}

void CTabSub::OnIPFieldChangedIPBase(NMHDR* pNMHDR, LRESULT* pResult)
{
    // LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
    
    updateInfoStr();

    *pResult = 0;
}

void CTabSub::OnBntClickedSetHosts()
{
    CHostsDlg hostsDlg(m_subnetHosts);

    if (IDOK == hostsDlg.DoModal())
        m_subnetHosts = hostsDlg.getHostsVec();
    else
        MessageBox(L"!IDOK", L"DEBUG"); // REMOVE
}
