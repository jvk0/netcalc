#include "pch.h"

#include "resource.h"

#include "NetCalc.h"
#include "CTabWild.h"

#include "IP4Calc.h"
#include "IP4String.h"

// CTabWild dialog

IMPLEMENT_DYNAMIC(CTabWild, CDialogEx)

CTabWild::CTabWild(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OLE_PL_TAB3, pParent)
    , m_valIPBase(0)
    , m_valIPWild(0)
    , m_valIPAddr(0)
{
}

CTabWild::~CTabWild()
{
}

void CTabWild::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB3_IP_BASE, m_ctrIPBase);
    DDX_Control(pDX, IDC_TAB3_IP_WILD, m_ctrIPWild);
    DDX_IPAddress(pDX, IDC_TAB3_IP_BASE, m_valIPBase);
    DDX_IPAddress(pDX, IDC_TAB3_IP_WILD, m_valIPWild);
    DDX_IPAddress(pDX, IDC_TAB3_IP_ADDR, m_valIPAddr);
    DDX_Control(pDX, IDC_TAB3_LIST_RES, m_ctrListResults);
}

void CTabWild::OnOK()
{
    // Prevent Enter from closing the dialog  
    if ((GetKeyState(VK_RETURN) & 0x8000) == 0)
        CTabWild::OnOK();
}

void CTabWild::OnCancel()
{
    // Prevent Esc from closing the dialog  
    if ((GetKeyState(VK_ESCAPE) & 0x8000) == 0)
        CTabWild::OnCancel();
}

BOOL CTabWild::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_ctrIPBase.SetAddress(192, 168, 0, 0);
    m_ctrIPWild.SetAddress(0, 0, 255, 255);

    initListResults();

    UpdateData(TRUE);

    return TRUE;
}


BEGIN_MESSAGE_MAP(CTabWild, CDialogEx)
    ON_BN_CLICKED(IDC_TAB3_BTN_TEST, &CTabWild::OnBntClickedTest)
    ON_BN_CLICKED(IDC_TAB3_BTN_CLEAR, &CTabWild::OnBntClickedClear)
END_MESSAGE_MAP()


void CTabWild::OnBntClickedTest()
{
    using IP4String::addr2Str;

    UpdateData(TRUE);

    if (!m_valIPAddr) {
        MessageBox(L"Nastavte testovanú adresu!", L"Neplatná adresa",
            MB_OK | MB_ICONERROR);

        return;
    }
    
    LPCWSTR matchStr = L"Nie";

    if ((~m_valIPWild & m_valIPBase) == (~m_valIPWild & m_valIPAddr))
        matchStr = L"Áno";

    CString tmpStr;
    
    // Filter
    tmpStr.Format(L"%s, %s", addr2Str(m_valIPBase), addr2Str(m_valIPWild));
    m_ctrListResults.InsertItem(0, tmpStr);

    // Adresa
    m_ctrListResults.SetItemText(0, 1, addr2Str(m_valIPAddr));

    // Zhoda?
    m_ctrListResults.SetItemText(0, 2, matchStr);

    m_valIPAddr = 0; // Zero tesing adress

    UpdateData(FALSE);
}

void CTabWild::initListResults()
{
    m_ctrListResults.SetExtendedStyle(
        m_ctrListResults.GetExtendedStyle() |
        0 |
        LVS_EX_FULLROWSELECT
    );

    m_ctrListResults.InsertColumn(0, L"Filter", LVCFMT_LEFT, 170);
    m_ctrListResults.InsertColumn(1, L"Adresa ", LVCFMT_LEFT, 110);
    m_ctrListResults.InsertColumn(2, L"Zhoda? ", LVCFMT_LEFT, 60);

    m_ctrListResults.DeleteAllItems(); // Scrollbar bug fix
}


void CTabWild::OnBntClickedClear()
{
    if (!m_ctrListResults.GetItemCount()) {
        MessageBeep(MB_ICONWARNING);
        return;
    }

    int response = MessageBox(
        L"Vymazať tabuľku?",
        L"Ste si istý?",
        MB_OKCANCEL | MB_ICONWARNING
    );

    if (response == IDOK) {
        m_valIPAddr = 0;
        m_ctrListResults.DeleteAllItems();
        UpdateData(FALSE);
    }
}
