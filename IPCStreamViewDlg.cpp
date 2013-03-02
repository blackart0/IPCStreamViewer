// IPCStreamViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPCStreamView.h"
#include "IPCStreamViewDlg.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int g_Created=FALSE;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCStreamViewDlg dialog

CIPCStreamViewDlg::CIPCStreamViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPCStreamViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPCStreamViewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_selTab=0;
}

void CIPCStreamViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPCStreamViewDlg)
	DDX_Control(pDX, IDC_TAB_MAIN, m_tab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIPCStreamViewDlg, CDialog)
	//{{AFX_MSG_MAP(CIPCStreamViewDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_MAIN, OnSelchangingTabMain)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, OnSelchangeTabMain)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCStreamViewDlg message handlers

BOOL CIPCStreamViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// init ddraw
	DdrawInit(GetSafeHwnd());
	InitializeCriticalSection(&g_csDecInit);
	//
	CRect rc;
	MoveWindow(0,0,800,600,TRUE);
	GetWindowRect(rc);
	m_tab.MoveWindow(rc);
	// init tab
	//为Tab Control增加两个页面
	m_tab.InsertItem(0, _T("图像预览"));
	m_tab.InsertItem(1, _T("摄像头调焦助手"));
	//创建两个对话框
	m_preview.Create(IDD_DIALOG_PREVIEW, &m_tab);
	m_focusAssist.Create(IDD_DIALOG_FOCUS_ASSIST, &m_tab);
	//设定在Tab内显示的范围
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_preview.MoveWindow(&rc);
	m_focusAssist.MoveWindow(&rc);
	
	//把对话框对象指针保存起来
	m_dialogs[0] = &m_preview;
	m_dialogs[1] = &m_focusAssist;

	// init for preview
	m_preview.InitPreview();
	m_focusAssist.InitPreview();

	//显示初始页面
	m_dialogs[0]->ShowWindow(SW_HIDE);
	m_dialogs[1]->ShowWindow(SW_HIDE);
	m_dialogs[m_selTab]->ShowWindow(SW_SHOW);
	//保存当前选择
	//m_selTab = 0;
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIPCStreamViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIPCStreamViewDlg::OnPaint() 
{
	
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIPCStreamViewDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIPCStreamViewDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	g_Created=bShow;
}

void CIPCStreamViewDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(g_Created){
		CRect rc;
		CWnd *pwnd=GetDlgItem(IDC_TAB_MAIN);
		GetWindowRect(rc);
		rc.bottom=rc.bottom-rc.top;
		rc.top=0;
		rc.right=rc.right-rc.left;
		rc.left=0;
		pwnd->MoveWindow(rc);
		rc.bottom-=20;
		rc.top+=20;
		m_dialogs[0]->MoveWindow(rc);
		m_dialogs[1]->MoveWindow(rc);
	}
}

void CIPCStreamViewDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_preview.m_streamview.Closeconn();
	m_focusAssist.m_focusview.Closeconn();
	DdrawDeinit();
	
}

void CIPCStreamViewDlg::OnSelchangingTabMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CIPCStreamViewDlg::OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int sel=m_tab.GetCurSel();
	m_dialogs[m_selTab]->ShowWindow(FALSE);
	m_dialogs[m_tab.GetCurSel()]->ShowWindow(TRUE);
	m_selTab=m_tab.GetCurSel();

	*pResult = 0;
}
