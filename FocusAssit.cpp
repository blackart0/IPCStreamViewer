// FocusAssit.cpp : implementation file
//

#include "stdafx.h"
#include "IPCStreamView.h"
#include "FocusAssit.h"

//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int g_WndShowed=FALSE;
/////////////////////////////////////////////////////////////////////////////
// CFocusAssit dialog


CFocusAssit::CFocusAssit(CWnd* pParent /*=NULL*/)
	: CDialog(CFocusAssit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFocusAssit)
	//}}AFX_DATA_INIT
	canSize=FALSE;
}


void CFocusAssit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFocusAssit)
	DDX_Control(pDX, IDC_LIST_TIPS, m_tips);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFocusAssit, CDialog)
	//{{AFX_MSG_MAP(CFocusAssit)
	ON_BN_CLICKED(IDC_BUTTON_SAMPLE, OnButtonSample)
	ON_BN_CLICKED(IDC_BUTTON_START_FOCUS, OnButtonStartFocus)
	ON_BN_CLICKED(IDC_BUTTON_STOP_FOCUS2, OnButtonStopFocus2)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFocusAssit message handlers

void CFocusAssit::OnButtonSample() 
{
	// TODO: Add your control notification handler code here
	// 设置标题
	m_Plot.StartSerieCapture();
}

void CFocusAssit::OnButtonStartFocus() 
{
	// TODO: Add your control notification handler code here
	m_Plot.StopSerieCapture();
	m_Plot.StartHFloatCapture();
}

void CFocusAssit::OnButtonStopFocus2() 
{
	// TODO: Add your control notification handler code here
}

int CFocusAssit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}

void CFocusAssit::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_focusview.Closeconn();
}

void CFocusAssit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if (bShow)
	{
		//InitPreview();
		m_focusview.preview("192.168.1.24",80,"");
	} 
	else
	{
		m_focusview.Closeconn();
	}
	g_WndShowed=bShow;
}

void CFocusAssit::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(g_WndShowed){
		CRect Rect;
		GetClientRect(Rect);
		m_Plot.MoveWindow(Rect);
	}
}

int CFocusAssit::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::DoModal();
}

void CFocusAssit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	/*
	CRect rc;
	CWnd *pwnd=GetDlgItem(IDC_STATIC_VIEW_AREA);
	pwnd->GetClientRect(rc);
	//pwnd->UpdateWindow();
	//InvalidateRect(rc);
	rc.top+=20;
	rc.left+=5;
	rc.right-=5;
	rc.bottom-=5;
	//rc.right+=500;
	CClientDC ddc(pwnd);
	CBrush brush(RGB(0,0,0));
	ddc.FillRect(rc,&brush);
*/
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CFocusAssit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here		
	m_tips.AddString("1.请将摄像头的焦距调到最小");
	m_tips.AddString("2.点击采样按钮，并将焦距缓慢调至最大");
	m_tips.AddString("3.点击开始微调按钮，并缓慢调整焦距");
	m_tips.AddString("4.直至落到绿色区域时，调焦结束");
	m_tips.AddString("5.点击结束微调按钮，结束调焦");
	// init cplot
	InitPlot();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CFocusAssit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(0,0,0));
		HBRUSH b=CreateSolidBrush(RGB(0,0,0));
		return b;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

CRect CFocusAssit::GetPreviewRect()
{
	CRect rect;
	CWnd *pwnd=GetDlgItem(IDC_STATIC_VIEW_AREA);
	pwnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.right -= 10 ;
	rect.left += 5;
	rect.bottom -= 5;
	rect.top += 25;
	return rect;
}

void CFocusAssit::InitPreview()
{
	static BOOL bCreated=FALSE;
	if (bCreated==FALSE)
	{
		CRect rect=GetPreviewRect();
		m_focusview.Create(_T(""), WS_VISIBLE | SS_NOTIFY | SS_CENTER , rect, this, 5);
		bCreated=TRUE;
	}
}

CRect CFocusAssit::GetPlotRect()
{
	CRect rect;
	CWnd *pwnd=GetDlgItem(IDC_STATIC_FOCUS_ASSIST);
	pwnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.right -= 10 ;
	rect.left += 5;
	rect.bottom -= 60;
	rect.top += 25;
	return rect;
}

void CFocusAssit::InitPlot()
{
	CRect Rect=GetPlotRect();
	if(m_Plot.Create(WS_VISIBLE | WS_CHILD,Rect,this,2000)==FALSE){
		printf("create plot error:%d",GetLastError());
		return;
	}
	else{
		printf("create plot success.");
	}
	
	m_Plot.SetSerie(0, PS_SOLID, RGB(255,0,0), 0.0, 1000.0, "Pressure");
	
	m_Plot.SetLegend(0, PS_SOLID, RGB(255,0,0), "Temperature");
	
	m_Plot.m_bAutoScrollX=TRUE;
	m_Plot.m_bctlBorder=FALSE;
	m_Plot.m_bplotBorder=FALSE;
	m_Plot.m_blegendBorder=FALSE;
	m_Plot.m_bPrimaryLegend=FALSE;
	m_Plot.m_bSecondaryLegend=FALSE;
	m_Plot.m_bAxisBX=FALSE;
	m_Plot.m_bAxisLY=FALSE;
	m_Plot.m_bAxisRY=FALSE;
	m_Plot.m_bGridH=TRUE;
	m_Plot.m_bGridV=FALSE;
	m_Plot.m_bLegend=FALSE;

	m_Plot.SetBXRange(CTime::GetCurrentTime()-CTimeSpan(20),CTime::GetCurrentTime());

	// recompute rect
	m_Plot.ComputeRects(TRUE);
	
	SetTimer(1,1000,NULL);
	canSize=TRUE;
}

void CFocusAssit::OnTimer(UINT nIDEvent)
{
	static BOOL pros={FALSE};
	if(!pros){
		pros=TRUE;

		double y =(double)(abs(rand())%1000);
		m_Plot.AddPoint(0,  CTime::GetCurrentTime(), y);
		m_Plot.NewFloatValue(y);
/*	
		CRect rc;
		m_Plot.GetWindowRect(rc);
		ScreenToClient(rc);
		InvalidateRect(rc);
	*/
		pros=FALSE;
	}
	CWnd::OnTimer(nIDEvent);
}
