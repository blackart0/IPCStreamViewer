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
    //把字符串类型的IP地址（例如："123.123.123.123"）转换为字节顺序的网络地址
	unsigned long ResolveIP(CString strIP);  
	//把一个字符串类型的主机名（例如"ComputerName"）通过DNS或者WINS解析，得到字节顺序的网络地址
	unsigned long ResolveName(CString strHostName); 
    //根据给定的网络地址和超时限制，Ping该地址，返回相应的时间
	DWORD PingHost(unsigned long ulIP, int iPingTimeout);
    //与ResolveIP的作用相反，将自己顺序的网络地址转换为字符串类型的IP地址
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



