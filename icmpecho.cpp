//icmpecho.cpp
//-------------------------------------------------------------------------------------------------------

// IcmpEcho.cpp : implementation file
//
#include "stdafx.h"
#include "IcmpEcho.h"

extern "C" {
#include "ipexport.h"
#include "icmpapi.h"
}

#define PING_TIMEOUT 100

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIcmpEcho

CIcmpEcho::CIcmpEcho()
{
}

CIcmpEcho::~CIcmpEcho()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CIcmpEcho, CSocket)
	//{{AFX_MSG_MAP(CIcmpEcho)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CIcmpEcho member functions
unsigned long CIcmpEcho::ResolveIP(CString strIP)
{
	//Task 1:	Given IP Address i.e. "111.111.111.111",
	//	Return Network byte ordered address (ulIP)

	unsigned long ulIP;

	ulIP =(IPAddr)inet_addr(strIP);

	return ulIP;
}

unsigned long CIcmpEcho::ResolveName(CString strHostName)
{
	//Task 1:	Resolve HostName (through DNS or WINS, whichever appropriate)
	//Task 2:	Return network byte ordered address (ulIP)

	unsigned long ulIP;
	hostent* phostent;

	phostent = gethostbyname(strHostName);
	
	if (phostent == NULL)
		return 0;

	ulIP = *(DWORD*)(*phostent->h_addr_list);

	return ulIP;

}

DWORD CIcmpEcho::PingHost(unsigned long ulIP, int iPingTimeout)
{
	//Task 1:	Open ICMP Handle
	//Task 2:	Create Structure to receive ping reply
	//Task 3:	SendPing (SendEcho)
	//Task 4:	Close ICMP Handle
	//Task 5:	Return RoundTripTime

	unsigned long ip = ulIP;

	HANDLE icmphandle = IcmpCreateFile();

	char reply[sizeof(icmp_echo_reply)+8];

	icmp_echo_reply* iep=(icmp_echo_reply*)&reply;
	iep->RoundTripTime = 0xffffffff;

	IcmpSendEcho(icmphandle,ip,0,0,NULL,reply,sizeof(icmp_echo_reply)+8,iPingTimeout);

	IcmpCloseHandle(icmphandle);

	return iep->RoundTripTime;

}

CString CIcmpEcho::GetIP(unsigned long ulIP)
{
	//Task 1:	Given a host order ulIP Address
	//	Return a IP address in format of xxx.xxx.xxx.xxx

	LPSTR szAddr;

	struct in_addr inetAddr;
	
	inetAddr.s_addr = (IPAddr)ulIP;

	szAddr = inet_ntoa(inetAddr);

	CString csIP = szAddr;

	return csIP;

}
