#include "pch.h"

#include "resource.h"

#include "NetCalc.h"
#include "CTabSub.h"
#include "CHostsDlg.h"
#include "CGraphDlg.h"

#include "IP4String.h"

// CTabSub dialog

IMPLEMENT_DYNAMIC(CTabSub, CDialogEx)

CTabSub::CTabSub(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_TAB1, pParent),
    m_subnetHosts(),
    m_subnetHostsSum(0),
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

void CTabSub::initListNets()
{
    m_ctrListNets.SetExtendedStyle(m_ctrListNets.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

    m_ctrListNets.InsertColumn(0, L"Veľkosť siete", LVCFMT_LEFT, 95);
    m_ctrListNets.InsertColumn(1, L"Požadovaná veľkosť", LVCFMT_LEFT, 135);
    m_ctrListNets.InsertColumn(2, L"Využitie [%]", LVCFMT_LEFT, 85);
    m_ctrListNets.InsertColumn(3, L"Adresa siete", LVCFMT_LEFT, 130);
    m_ctrListNets.InsertColumn(4, L"Maska", LVCFMT_LEFT, 130);
    m_ctrListNets.InsertColumn(5, L"Prvá adresa", LVCFMT_LEFT, 130);
    m_ctrListNets.InsertColumn(6, L"Posledná adresa", LVCFMT_LEFT, 130);

    m_ctrListNets.DeleteAllItems(); // Scrollbar bug fix
}

void CTabSub::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_IPAddress(pDX, IDC_TAB1_IP_BASE, m_valIPBaseNet);
    DDX_Control(pDX, IDC_TAB1_SPIN_PREFIX, m_ctrSpinPrefix);
    DDX_Text(pDX, IDC_TAB1_ST_INFO, m_valSTextInfo);
    DDX_Control(pDX, IDC_TAB1_IP_BASE, m_ctrIPBaseNet);
    DDX_Control(pDX, IDC_TAB1_LIST_NETS, m_ctrListNets);
    DDX_Control(pDX, IDC_TAB1_BNT_SAVE, m_ctrBtnSave);
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
    initListNets();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CTabSub, CDialogEx)
    #pragma warning(disable: 26454)
    ON_NOTIFY(UDN_DELTAPOS, IDC_TAB1_SPIN_PREFIX, &CTabSub::OnDeltaPosSpinPrefix)
    ON_NOTIFY(IPN_FIELDCHANGED, IDC_TAB1_IP_BASE, &CTabSub::OnIPFieldChangedIPBase)
    ON_NOTIFY(NM_DBLCLK, IDC_TAB1_LIST_NETS, &CTabSub::OnDblClkListNets)
    #pragma warning(default: 26454)
    ON_BN_CLICKED(IDC_TAB1_BTN_SETHOSTS, &CTabSub::OnBntClickedSetHosts)
    ON_BN_CLICKED(IDC_TAB1_BTN_CALC, &CTabSub::OnBntClickedCalc)
    ON_BN_CLICKED(IDC_TAB1_BNT_SAVE, &CTabSub::OnBntClickedSave)
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

    if (IDOK == hostsDlg.DoModal()) {
        m_subnetHosts    = hostsDlg.getHostsVec();
        m_subnetHostsSum = hostsDlg.getSumHosts();
    }
}

void CTabSub::OnBntClickedCalc()
{
    using namespace IP4Calc;
    using namespace IP4String;
    
    if (!m_subnetHostsSum) {
        MessageBox(L"Najskôr nastavte podsiete!", L"Chyba", MB_OK | MB_ICONERROR);
        return;
    }

    if (m_subnetHostsSum > IP4Calc::numHostsAddr(m_calcPrefix)) {
        MessageBox(L"Adresový priestor je príliš malý!", L"Chyba", MB_OK | MB_ICONERROR);
        return;
    }

    IP4SubnetsVect subnetsVect = calcSubnets(m_valIPBaseNet & prefix2Mask(m_calcPrefix), m_subnetHosts);
    CString tmpStr;

    m_ctrListNets.DeleteAllItems();
    for (auto i = subnetsVect.rbegin(); i != subnetsVect.rend(); ++i) {
        DWORD addr = std::get<0>(*i);
        int pref   = std::get<1>(*i);
        int req    = std::get<2>(*i);
        int size   = std::get<3>(*i);
        
        DWORD mask = prefix2Mask(pref);

        // Veľkosť siete
        tmpStr.Format(L"%d", size);
        m_ctrListNets.InsertItem(0, tmpStr); 

        // Požadovaná veľkosť
        tmpStr.Format(L"%d", req);
        m_ctrListNets.SetItemText(0, 1, tmpStr); 

        // Využitie
        tmpStr.Format(L"%.2f", double(req) / double(size) * 100.0);
        m_ctrListNets.SetItemText(0, 2, tmpStr);

        // Adresa siete
        tmpStr.Format(L"%s/%d", addr2Str(addr), pref);
        m_ctrListNets.SetItemText(0, 3, tmpStr); 

        // Maska
        m_ctrListNets.SetItemText(0, 4, addr2Str(mask)); 

        // Prvá adresa
        m_ctrListNets.SetItemText(0, 5, addr2Str(firstAddr(addr, mask)));

        // Posledná adresa
        m_ctrListNets.SetItemText(0, 6, addr2Str(lastAddr(addr, mask)));
    }

    m_ctrBtnSave.EnableWindow(TRUE);
}

void CTabSub::OnBntClickedSave()
{
    CString tmpStr(L"Comma-Separated Values File (*.csv)|*.csv|All Files (*.*)|*.*||"); // Filter for CFileDialog

    CFileDialog saveDlg(FALSE, L".csv", NULL, OFN_OVERWRITEPROMPT, tmpStr, NULL, 0, TRUE);

    if (saveDlg.DoModal() != IDOK) // Canceled
        return;

    try {
        CStdioFile fileObj(saveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);

        fileObj.WriteString(L"Size,Required,Used in %,Network address,Mask,First address,Last address\n"); // Header

        int itemCount = m_ctrListNets.GetItemCount();
        for (int i = 0; i < itemCount; i++) {
            tmpStr = m_ctrListNets.GetItemText(i, 0) + ',' +
                m_ctrListNets.GetItemText(i, 1) + ',' +
                m_ctrListNets.GetItemText(i, 2) + ',' +
                m_ctrListNets.GetItemText(i, 3) + ',' +
                m_ctrListNets.GetItemText(i, 4) + ',' +
                m_ctrListNets.GetItemText(i, 5) + ',' +
                m_ctrListNets.GetItemText(i, 6) + '\n';

            fileObj.WriteString(tmpStr);
        }

        fileObj.Close();
    } catch (...) {
        MessageBox(L"Počas zápisu došlo k výnimke", L"Zápis zlyhal", MB_OK | MB_ICONERROR);
    }
}

void CTabSub::OnDblClkListNets(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    double usedPct = _wtof(m_ctrListNets.GetItemText(pNMItemActivate->iItem, 2));

    CGraphDlg graphDlg(usedPct);
    graphDlg.DoModal();

    *pResult = 0;
}
