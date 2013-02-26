#ifndef __NETSDKDATA_HEAD__
#define __NETSDKDATA_HEAD__


// 消息包
typedef struct tagPacketMsg
{
	unsigned int nLen;					// 消息长度
	char *		cMsg;					// 消息内容
}MY_NET_PACKET_MSG;

// 数据包
typedef struct tagPacketData
{
	unsigned long		nLen;			// 数据长度
	unsigned char		nType;			// 数据类型
	unsigned char		nId;			// 数据通道
	char *				cData;			// 数据内容
	DWORD				dwTimeStamp;	//yqw:时间戳
}MY_NET_PACKET_DATA;



#endif