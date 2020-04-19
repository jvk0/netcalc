#include "pch.h"

#include "resource.h"

#include "NetCalc.h"
#include "CHostsDlg.h"


// CHostsDlg dialog

IMPLEMENT_DYNAMIC(CHostsDlg, CDialogEx)

CHostsDlg::CHostsDlg(const IP4Calc::HostsVect& inHosts, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_HOSTS_DIALOG, pParent),
    m_sumHosts(IP4Calc::sumHostReq(inHosts)),
    m_outHosts(inHosts),
    m_valEdNum(_T("0")),
    m_valSTextSum(_T(""))
{
}

CHostsDlg::~CHostsDlg()
{
}

IP4Calc::HostsVect CHostsDlg::getHostsVec()
{
    return m_outHosts;
}

int CHostsDlg::getSumHosts()
{
    return m_sumHosts;
}

void CHostsDlg::addListHostsRow(int num)
{
    CString tmpStr;

    tmpStr.Format(L"%d", num);
    m_ctrListHosts.InsertItem(0, tmpStr); // Požiadavka

    tmpStr.Format(L"%d", IP4Calc::ceilHosts(num)); // Zaokrúhlené
    m_ctrListHosts.SetItemText(0, 1, tmpStr);

}

void CHostsDlg::initListHosts()
{
    m_ctrListHosts.SetExtendedStyle(
        m_ctrListHosts.GetExtendedStyle() |
        LVS_EX_GRIDLINES |
        LVS_EX_FULLROWSELECT);

    CRect rect;
    m_ctrListHosts.GetClientRect(&rect);
    
    int colWidth = rect.Width() / 2;
    
    m_ctrListHosts.InsertColumn(0, _T("Požadovaný"), LVCFMT_LEFT, colWidth);
    m_ctrListHosts.InsertColumn(1, _T("Zaokrúhlený "), LVCFMT_LEFT, colWidth);

    for (auto i : m_outHosts)
        addListHostsRow(i);
}

void CHostsDlg::updateSumText()
{
    m_valSTextSum.Format(L"Suma zaokrúhlených: %d", m_sumHosts);
    
    UpdateData(FALSE);
}

void CHostsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_HDLG_LIST_HOSTS, m_ctrListHosts);
    DDX_Text(pDX, IDC_HDLG_ED_NUM, m_valEdNum);
    DDX_Text(pDX, IDC_HDLG_ST_SUM, m_valSTextSum);
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
    updateSumText();

    return TRUE;
}


BEGIN_MESSAGE_MAP(CHostsDlg, CDialogEx)
    ON_BN_CLICKED(IDC_HDLG_BTN_ADD, &CHostsDlg::OnBntClickedAdd)
    ON_BN_CLICKED(IDC_HDLG_BTN_REMOVE, &CHostsDlg::OnBtnClickedRemove)
END_MESSAGE_MAP()


// CHostsDlg message handlers

void CHostsDlg::OnBntClickedAdd()
{
    UpdateData(TRUE);

    int num = _ttoi(m_valEdNum);

    if (num < 1) {
        MessageBox(L"Počet požadovaných adries musí byť aspoň 1!", L"Chybná hodnota", MB_OK | MB_ICONERROR);
        return;
    }

    m_outHosts.push_back(num);
    addListHostsRow(num);
    
    m_sumHosts += IP4Calc::ceilHosts(num); // Update sum
    updateSumText();
}

void CHostsDlg::OnBtnClickedRemove()
{
    int nItem = m_ctrListHosts.GetSelectionMark();

    if (nItem == -1) {
        MessageBeep(MB_ICONWARNING);
        return;
    }

    std::size_t end = m_outHosts.size() - 1;
    
    m_sumHosts -= IP4Calc::ceilHosts(m_outHosts[end - nItem]); // Update sum
    m_outHosts.erase(m_outHosts.begin() + (end - nItem));
    
    m_ctrListHosts.DeleteItem(nItem);

    updateSumText();
}
