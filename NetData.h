#ifndef __NETSDKDATA_HEAD__
#define __NETSDKDATA_HEAD__


// ��Ϣ��
typedef struct tagPacketMsg
{
	unsigned int nLen;					// ��Ϣ����
	char *		cMsg;					// ��Ϣ����
}MY_NET_PACKET_MSG;

// ���ݰ�
typedef struct tagPacketData
{
	unsigned long		nLen;			// ���ݳ���
	unsigned char		nType;			// ��������
	unsigned char		nId;			// ����ͨ��
	char *				cData;			// ��������
	DWORD				dwTimeStamp;	//yqw:ʱ���
}MY_NET_PACKET_DATA;



#endif