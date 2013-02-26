// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 NETSDK_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// NETSDK_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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