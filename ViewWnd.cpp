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

CString szApp="IPC-ASSIST";
CString szINI="C:\\Program Files\\AutoDVRTEST\\IPCStreamView\\conf.ini";
char sz_DevIp[16]="192.168.1.22";
unsigned i_Port=80;
bool m_toggle=true;

/////////////////////////////////////////////////////////////////////////////
// CViewWnd

CViewWnd::CViewWnd()
{
	m_connected=false;
	m_toggle=true;
}

CViewWnd::~CViewWnd()
{
	m_connected=false;
	m_toggle=false;
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
	m_toggle=false;
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
		printf("connect failed\n");
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

void CViewWnd::ClearPreviewArea()
{
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);
}

bool CViewWnd::GetNetworkConnectState()
{
	return m_connected;
}

UINT ConnectProc(LPVOID pParam)
{	
	int ret;
	CViewWnd *viewwnd=(CViewWnd *)pParam;
	if(viewwnd==NULL /*|| !viewwnd->IsKindOf(RUNTIME_CLASS(CViewWnd)) */){
		return 1;
	}
	m_toggle=true;
	printf("create thread success.\n");
	while(m_toggle){
		if((ret=viewwnd->m_ping.PingHost(viewwnd->m_ping.ResolveIP(sz_DevIp),10))>=10)
		{
			printf("ping timeout:%d\n",ret);
			viewwnd->m_connected=false;
			viewwnd->ClearPreviewArea();
			continue;
		}
		else{// connected
			printf("ping ret:%d\n",ret);
			viewwnd->m_connected=true;
		}
		if (viewwnd->m_ClientSock.GetConnectStatus())// connected
		{
			Sleep(1000);
			continue;
		}
		else{
			ret=viewwnd->ConnectToServer(sz_DevIp, i_Port, "", 0);
			viewwnd->OpenChannel(0, true);
			if(ret==0){// connected success
				Sleep(1000);
			}
			else{
				printf("connecting failed\n");
				viewwnd->ClearPreviewArea();
			}
		}
	}
	printf("exit thread success.\n");
	return 0;
}


