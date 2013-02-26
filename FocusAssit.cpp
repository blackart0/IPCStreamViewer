// FocusAssit.cpp : implementation file
//

#include "stdafx.h"
#include "IPCStreamView.h"
#include "FocusAssit.h"

// use for mschart
#include "VcPlot.h"
#include "VcAxis.h"
#include "VcValueScale.h"
#include "VcSeriesCollection.h"
#include "VcSeries.h"
#include "VcPen.h"
#include "VcCategoryScale.h"
#include "VcColor.h"
#include "VcDataGrid.h"
#include "VcBackdrop.h"
#include "VcFill.h"
#include "VcBrush.h"
#include "VcDataPoints.h"
#include "VcDataPoint.h"
#include "VcDataPointLabel.h"
#include "VcAxisTitle.h"
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
}


void CFocusAssit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFocusAssit)
	DDX_Control(pDX, IDC_LIST_TIPS, m_tips);
	DDX_Control(pDX, IDC_MSCHART1, m_chart);
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
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFocusAssit message handlers

void CFocusAssit::OnButtonSample() 
{
	// TODO: Add your control notification handler code here
	// ���ñ���
}

void CFocusAssit::OnButtonStartFocus() 
{
	// TODO: Add your control notification handler code here
	
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
	CRect rc(0,0,0,0);
	//CWnd *pwnd=GetDlgItem(IDC_STATIC_FOCUS_ASSIST);
	//pwnd->GetWindowRect(rc);
	//GetClientRect(&rc);	
	if(!m_chart.Create(_T(""), WS_VISIBLE | WS_CHILD, rc, this, 10))
	{
		int err=GetLastError();
		printf("error no:%d\n",err);
		return -1;
	}
	
	//InitChart();
	//DrawChart();

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
	if( m_chart.GetSafeHwnd() )
		m_chart.MoveWindow( 0, 0, cx, cy );	
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
	m_tips.AddString("1.�뽫����ͷ�Ľ��������С");
	m_tips.AddString("2.���������ť���������໺���������");
	m_tips.AddString("3.�����ʼ΢����ť����������������");
	m_tips.AddString("4.ֱ���䵽��ɫ����ʱ����������");
	m_tips.AddString("5.�������΢����ť����������");
	//init chart
	CRect rc;
	CWnd *pwnd=GetDlgItem(IDC_STATIC_FOCUS_ASSIST);
	pwnd->GetWindowRect(rc);
	m_chart.MoveWindow(rc);
	InitChart();
	DrawChart();

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
	RECT ViewRect;
	RECT WndRect;
	GetWindowRect(&WndRect);
	CWnd *pwnd=GetDlgItem(IDC_STATIC_VIEW_AREA);
	//pwnd->GetClientRect(&ViewRect);
	pwnd->GetWindowRect(&ViewRect);
	rect.right = ViewRect.right + WndRect.left - 15 ;
	rect.left = ViewRect.left + WndRect.left +5;
	rect.bottom = ViewRect.bottom - WndRect.top - 5;
	rect.top = ViewRect.top-WndRect.top+25;
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

void CFocusAssit::InitChart()
{	
	m_chart.SetChartType(1 | 2);

	// ���ñ���
	m_chart.SetTitleText("mschart test");
	
	// ��������ı䱳��ɫ
	m_chart.GetBackdrop().GetFill().SetStyle(1);
	m_chart.GetBackdrop().GetFill().GetBrush().GetFillColor().Set(255, 255, 255);
	
	// ��ʾͼ��
	m_chart.SetShowLegend(TRUE);
	m_chart.SetColumn(1);
	m_chart.SetColumnLabel((LPCTSTR)"1�Ż�");
	
	// ջģʽ
	m_chart.SetStacking(FALSE);
	
	// Y������
	VARIANT var;
	m_chart.GetPlot().GetAxis(1,var).GetValueScale().SetAuto(FALSE);	// ���Զ���עY��̶�
	m_chart.GetPlot().GetAxis(1,var).GetValueScale().SetMaximum(100);	// Y�����̶�
	m_chart.GetPlot().GetAxis(1,var).GetValueScale().SetMinimum(0);		// Y����С�̶�
	m_chart.GetPlot().GetAxis(1,var).GetValueScale().SetMajorDivision(5);	// Y��̶�5�ȷ�
	m_chart.GetPlot().GetAxis(1,var).GetValueScale().SetMinorDivision(1);	// ÿ�̶�һ���̶���
	m_chart.GetPlot().GetAxis(1,var).GetAxisTitle().SetText("Сʱ");	// Y������
	
	// n������
	m_chart.SetColumnCount(1); 
	
	// ��ɫ
	m_chart.GetPlot().GetSeriesCollection().GetItem(1).GetPen().GetVtColor().Set(0, 0, 255);
	
	// �߿�(�Ե���ͼ��Ч)
	m_chart.GetPlot().GetSeriesCollection().GetItem(1).GetPen().SetWidth(50);
	
	// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
	// 0: ����ʾ	1: ��ʾ����״ͼ��
	// 2: ��ʾ����״ͼ���Ϸ�	3: ��ʾ����״ͼ���м�	4: ��ʾ����״ͼ���·�
	m_chart.GetPlot().GetSeriesCollection().GetItem(1).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);

}

void CFocusAssit::DrawChart()
{
	int nRowCount = 2;
	m_chart.SetRowCount(nRowCount);
	
	VARIANT var;
	m_chart.GetPlot().GetAxis(0,var).GetCategoryScale().SetAuto(FALSE);			// ���Զ���עX��̶�
	m_chart.GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerLabel(1);// ÿ�̶�һ����ע
	m_chart.GetPlot().GetAxis(0,var).GetCategoryScale().SetDivisionsPerTick(1); // ÿ�̶�һ���̶���
	m_chart.GetPlot().GetAxis(0,var).GetAxisTitle().SetText("����");			// X������
	
	char buf[32];
	srand( (unsigned)time( NULL ) );
	
	for(int row = 1; row <= nRowCount; ++row)
	{
		m_chart.SetRow(row);
		sprintf(buf, "%d��", row);
		
		m_chart.SetRowLabel((LPCTSTR)buf);
		m_chart.GetDataGrid().SetData(row, 1, rand() * 100 / RAND_MAX, 0);
    }
	
	m_chart.Refresh();	

}
