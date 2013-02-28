// ViewWnd.cpp : implementation file
//

#include "stdafx.h"
//#include "hjipcsetupdlg.h"
#include "ViewWnd.h"
#include "gfun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *sz_DevIp="192.168.1.22";
unsigned i_Port=80;
/////////////////////////////////////////////////////////////////////////////
// CViewWnd

CViewWnd::CViewWnd()
{
}

CViewWnd::~CViewWnd()
{
	//m_Dec.DeinitDec();
}


BEGIN_MESSAGE_MAP(CViewWnd, CStatic)
	//{{AFX_MSG_MAP(CViewWnd)
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewWnd message handlers
int CViewWnd::OpenChannel(int nChannel,bool bOpen)
{
	
	if (bOpen)
	{
		if (m_bOpenedChl)
		{
			m_ClientSock.OpenId(nChannel,false);
		}
		m_Dec.EnablePreview(true);
	}
	m_bOpenedChl =false;
	m_bOpenedChl = bOpen;
	m_ClientSock.m_sChannel = nChannel;
	
	return m_ClientSock.OpenId(nChannel,bOpen);
}

void CViewWnd::Closeconn() 
{
	// TODO: Add your command handler code here
	if (m_ClientSock.GetConnectStatus())
	{
		m_ClientSock.CloseAll();
	}
	m_bOpenedChl = false;
	memset(m_sAddress,0,sizeof(m_sAddress));
	memset(m_sEseeId,-1,sizeof(m_sEseeId));
	sprintf(m_ClientSock.m_sAddress,"0.0.0.0");
	sprintf(m_ClientSock.m_sEseeId,"00000000");
	m_nPort = 0;
	m_nDevId = -1;
	m_Dec.EnablePreview(false);
	m_Dec.DeinitDec();
}

int CViewWnd::ConnectToServer(char *sIp,unsigned short nPort,char *sEseeId, int nDevId)
{
	if ((!strcmp(sIp,m_sAddress) || !strcmp(sEseeId,m_sEseeId)) && (nPort == m_nPort))
	{
		return 0;
	}
	else
	{
		if (m_ClientSock.GetConnectStatus())
		{
			m_ClientSock.CloseAll();
			sprintf(m_ClientSock.m_sAddress,"0.0.0.0");
			sprintf(m_ClientSock.m_sEseeId,"00000000");
		}
	}
	if (strlen(sIp) > 0)
	{
		strcpy(m_sAddress,sIp);
		strcpy(m_ClientSock.m_sAddress,sIp);
	}
	if (strlen(sEseeId) > 0)
	{
		strcpy(m_sEseeId,sEseeId);
		strcpy(m_ClientSock.m_sEseeId,sEseeId);
	}
	m_nPort = nPort;
	m_nDevId = nDevId;
	
	char sConIp[128];
	memset(sConIp,0,sizeof(sConIp));
	Domain2Ip(sIp,sConIp);
	
	int nRet = m_ClientSock.ConnectToServer(sConIp,nPort,2);
	if (0 != nRet)
	{
		memset(m_sAddress,0,sizeof(m_sAddress));
		memset(m_sEseeId,-1,sizeof(m_sEseeId));
		sprintf(m_ClientSock.m_sAddress,"0.0.0.0");
		sprintf(m_ClientSock.m_sEseeId,"00000000");
		m_nPort = 0;
		m_nDevId = -1;
	}
	return nRet;
}

void CViewWnd::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CStatic::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here

}

int CViewWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	memset(m_sAddress,0, sizeof(m_sAddress));
	memset(m_sEseeId, 0, sizeof(m_sEseeId));
	sprintf(m_sAddress,"0.0.0.0");
	sprintf(m_sEseeId,"00000000");
	m_nPort = 0;
	m_Dec.InitDec();
	m_Dec.SetPreviewWnd(GetSafeHwnd());
	m_Dec.EnablePreview(false);
	m_ClientSock.SetDec(&m_Dec);
	return 0;
}

void CViewWnd::SetNetPara(char *ip, unsigned short port)
{
	memcpy(m_sAddress, ip, strlen(ip));
	m_nPort = port;
}

void CViewWnd::preview(char *ip, unsigned short port, char *eseeid)
{
	ConnectToServer(ip, port, eseeid, 0);
	OpenChannel(0, true);
}
