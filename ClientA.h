#if !defined(AFX_CLIENTA_H__2EE456A3_8943_4D99_A8B6_036EE57C3201__INCLUDED_)
#define AFX_CLIENTA_H__2EE456A3_8943_4D99_A8B6_036EE57C3201__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetSdk.h"
#include "H264Decode.h"

typedef void (* OnUserCheckMsg)(bool bCheck,bool *bAuth,void *pContext);

class CClientA : public CNetClient
{
public:
	CClientA();           // protected constructor used by dynamic creation
	virtual ~CClientA();

// Method:
public:
	virtual void OnCommandMsg(unsigned long uIp, MY_NET_PACKET_MSG PacketMsg);
	virtual void OnCommandData(unsigned long uIp, MY_NET_PACKET_DATA PacketData);
	virtual void OnFileRecv(unsigned long uIp,char *pFileData,unsigned int nFileSize);
	virtual void OnConnectRefused(char nRes);

	void		RegUserCheckMsg(OnUserCheckMsg pFunc,void *pContext);
	void		SetDec(CH264Decode *Dec){m_Dec = Dec;};
	void		GetAviName(char * filename);


// Attribute
public:
	BOOL			m_issavevideo;
	CH264Decode *	m_Dec;
	char			m_sAddress[128];
	char			m_sEseeId[32];
	int				m_sChannel;
	
private:
	OnUserCheckMsg	m_pfOnUserCheckMsg;
	void *			m_pOnUserCheckMsgContext;


//	CH264Decode *	m_Dec;
protected:

};

#endif // !defined(AFX_CLIENTA_H__2EE456A3_8943_4D99_A8B6_036EE57C3201__INCLUDED_)
