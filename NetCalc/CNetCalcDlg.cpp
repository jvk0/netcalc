#include "pch.h"

#include "CNetCalcApp.h"
#include "CNetCalcDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx {
public:
    CAboutDlg();

    #ifdef AFX_DESIGN_TIME
        enum { IDD = IDD_ABOUTBOX };
    #endif
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CNetCalcDlg dialog
CNetCalcDlg::CNetCalcDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_NETCALC_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetCalcDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_MAIN, m_ctrTabMain);
}

void CNetCalcDlg::OnOK()
{
    // Prevent Enter from closing the dialog  
    if ((GetKeyState(VK_RETURN) & 0x8000) == 0)
        CDialog::OnOK();
}

void CNetCalcDlg::OnCancel()
{
    // Prevent Esc from closing the dialog  
    if ((GetKeyState(VK_ESCAPE) & 0x8000) == 0)
        CDialog::OnCancel();
}

void CNetCalcDlg::initTabs()
{  
    m_tabCalc.Create(IDD_OLE_PL_CALC, &m_ctrTabMain);
    m_tabSub.Create(IDD_OLE_PL_SUB, &m_ctrTabMain);
    m_tabMask.Create(IDD_OLE_PL_MASK, &m_ctrTabMain);

    TCITEM tab0;
    tab0.mask = TCIF_TEXT | TCIF_PARAM;
    tab0.lParam = reinterpret_cast<LPARAM>(&m_tabCalc);
    tab0.pszText = L"Kalkulačka";
    m_ctrTabMain.InsertItem(0, &tab0);

    TCITEM tab1;
    tab1.mask = TCIF_TEXT | TCIF_PARAM;
    tab1.lParam = reinterpret_cast<LPARAM>(&m_tabSub);
    tab1.pszText = L"VLSM podsieťovanie";
    m_ctrTabMain.InsertItem(1, &tab1);

    TCITEM tab2;
    tab2.mask = TCIF_TEXT | TCIF_PARAM;
    tab2.lParam = reinterpret_cast<LPARAM>(&m_tabMask);
    tab2.pszText = L"Maska/Prefix";
    m_ctrTabMain.InsertItem(2, &tab2);

    CRect rect;
    m_ctrTabMain.GetItemRect(0, &rect);
   
    m_tabCalc.SetWindowPos(NULL, rect.left, rect.bottom + 1, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    m_tabSub.SetWindowPos(NULL, rect.left, rect.bottom + 1, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    m_tabMask.SetWindowPos(NULL, rect.left, rect.bottom + 1, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    m_tabCalc.ShowWindow(SW_SHOW);
    m_tabSub.ShowWindow(SW_HIDE);
    m_tabMask.ShowWindow(SW_HIDE);
}

BEGIN_MESSAGE_MAP(CNetCalcDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    #pragma warning(disable: 26454)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CNetCalcDlg::OnTcnSelChangeTabMain)
    #pragma warning(default: 26454)
END_MESSAGE_MAP()

// CNetCalcDlg message handlers
BOOL CNetCalcDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    #pragma warning(disable: 6286)
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);
    #pragma warning(default: 6286)

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr) {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    // when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);     // Set big icon
    SetIcon(m_hIcon, FALSE);    // Set small icon

    // ****** Extra initialization ******
    initTabs();

    return TRUE;    // "return TRUE" unless you set the focus to a control
}

void CNetCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    } else {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
// to draw the icon.  For MFC applications using the document/view model,
// this is automatically done for you by the framework.
void CNetCalcDlg::OnPaint()
{
    if (IsIconic()) {
        CPaintDC dc(this);  // Device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    } else {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
// the minimized window.
HCURSOR CNetCalcDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CNetCalcDlg::OnTcnSelChangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
    *pResult = 0;
 
    int selectedTab = m_ctrTabMain.GetCurSel();

    switch (selectedTab) {
        case 0:
            m_tabCalc.ShowWindow(SW_SHOW);
            m_tabSub.ShowWindow(SW_HIDE);
            m_tabMask.ShowWindow(SW_HIDE);
            break;
        case 1:
            m_tabCalc.ShowWindow(SW_HIDE);
            m_tabSub.ShowWindow(SW_SHOW);
            m_tabMask.ShowWindow(SW_HIDE);
            break;
        case 2:
            m_tabCalc.ShowWindow(SW_HIDE);
            m_tabSub.ShowWindow(SW_HIDE);
            m_tabMask.ShowWindow(SW_SHOW);
            break;
        default:
            m_tabCalc.ShowWindow(SW_SHOW);
            m_tabSub.ShowWindow(SW_HIDE);
            m_tabMask.ShowWindow(SW_HIDE);
    }
}

