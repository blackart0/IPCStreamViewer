// ClientA.cpp : implementation file
//
#include "stdafx.h"
#include "ClientA.h"
#include "netpacket.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientA


CClientA::CClientA()
{
	m_Dec = NULL;
	m_issavevideo = FALSE;

	sprintf(m_sAddress,"0.0.0.0");
	sprintf(m_sEseeId,"00000000");

}

CClientA::~CClientA()
{
// 	if (GetConnectStatus())
// 	{
// 		CloseAll();
// 	}
}

void CClientA::OnCommandData(unsigned long uIp, MY_NET_PACKET_DATA PacketData)
{
	if (PacketData.nType == 1 || PacketData.nType == 2)
	{
		m_Dec->InputDate(PacketData.cData,PacketData.nLen);
	}
}

void CClientA::OnCommandMsg(unsigned long uIp, MY_NET_PACKET_MSG PacketMsg)
{
	if (PacketMsg.cMsg)
	{
		CmdFormat *msgCmd=(CmdFormat*)PacketMsg.cMsg;
		switch(msgCmd->cHead[0])
		{
		case CMDPAC_TYPE_USERVRF_B:
			{
				m_pfOnUserCheckMsg(msgCmd->userverifyrst.bVerify,msgCmd->userverifyrst.Auth,m_pOnUserCheckMsgContext);
			} 
			break;
		}
	}
}

void CClientA::OnFileRecv(unsigned long uIp,char *pFileData,unsigned int nFileSize)
{
	return;
}

void CClientA::OnConnectRefused(char nRes)
{
	return;
}

void CClientA::RegUserCheckMsg(OnUserCheckMsg pFunc,void *pContext)
{
	m_pfOnUserCheckMsg = pFunc;
	m_pOnUserCheckMsgContext = pContext;

}



