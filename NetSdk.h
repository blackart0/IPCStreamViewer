// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� NETSDK_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// NETSDK_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#pragma once
#ifdef NETSDK_EXPORTS
#define NETSDK_API __declspec(dllexport)
#else
#define NETSDK_API __declspec(dllimport)
#endif

#include "NetData.h"

#define NETSDK_ERROR_PACKOVERFLOW		-1



class NETSDK_API CNetServer {
public:
	CNetServer(void);
	~CNetServer(void);
	int InitAll(LPCSTR cIp, WORD wPort, int nAutoCleanBufferNum);
	int SendCmdToClient(LPCSTR cIp, MY_NET_PACKET_MSG Packet_Msg);
	int SendDataToClient(LPCSTR cIp, MY_NET_PACKET_DATA Packet_Data);
	int SendDataToClient(LPCSTR cIp, int nId, DWORD dwDataLen, LPVOID pData, int nType);
	int GetConnectNum();
	int OpenId(LPCSTR cIp, int nId, BOOL bOpen);

	virtual void OnCommandMsg(unsigned long uIp, MY_NET_PACKET_MSG const &Packet_Msg) = 0;
	virtual void OnCommandData(unsigned long uIp, MY_NET_PACKET_DATA const &Packet_Data) = 0;

public:
	LPVOID m_pServer;
};

class NETSDK_API CNetClient {
public:
	CNetClient(void);
	~CNetClient(void);

 	int ConnectToServer(LPCSTR cAddr, WORD wPort, int nType);// 0 cmd 1 data 2 both
 	int SendCmdToServer(MY_NET_PACKET_MSG PacketMsg);
 	int SendDataToServer(MY_NET_PACKET_DATA PacketData);
	int SendRecCmdToServer(char cCmd,char * Param,int nCmdSize);
 	int OpenId(int nId, BOOL bOpen);
	int BindClient(unsigned int nClientID);
 	int CloseAll();
	bool	GetConnectStatus();
 
	virtual void OnCommandMsg(unsigned long uIp, MY_NET_PACKET_MSG PacketMsg) = 0;
	virtual void OnCommandData(unsigned long uIp, MY_NET_PACKET_DATA PacketData) = 0;
	virtual void OnFileRecv(unsigned long uIp,char *pFileData,unsigned int nFileSize) = 0;
	virtual void OnConnectRefused(char nRes) = 0;

public:
	LPVOID m_pClient;

};

char NETSDK_API *ConvertIP(unsigned long uIP);