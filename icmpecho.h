//icmpecho.h
#include <AFXSOCK.H>
#include "ipexport.h"
#include "icmpapi.h"

class CIcmpEcho : public CSocket
{
// Attributes
public:

// Operations
public:
	CIcmpEcho();
	virtual ~CIcmpEcho();
    //���ַ������͵�IP��ַ�����磺"123.123.123.123"��ת��Ϊ�ֽ�˳��������ַ
	unsigned long ResolveIP(CString strIP);  
	//��һ���ַ������͵�������������"ComputerName"��ͨ��DNS����WINS�������õ��ֽ�˳��������ַ
	unsigned long ResolveName(CString strHostName); 
    //���ݸ����������ַ�ͳ�ʱ���ƣ�Ping�õ�ַ��������Ӧ��ʱ��
	DWORD PingHost(unsigned long ulIP, int iPingTimeout);
    //��ResolveIP�������෴�����Լ�˳��������ַת��Ϊ�ַ������͵�IP��ַ
	CString GetIP(unsigned long ulIP);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIcmpEcho)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CIcmpEcho)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};
/////////////////////////////////////////////////////////////////////////////



