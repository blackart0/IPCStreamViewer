#if !defined(AFX_VIEWWND_H__36C6128B_5E43_4E02_BBD1_08B76593BCD8__INCLUDED_)
#define AFX_VIEWWND_H__36C6128B_5E43_4E02_BBD1_08B76593BCD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewWnd.h : header file
//

#include "ClientA.h"
#include "H264Decode.h"
/////////////////////////////////////////////////////////////////////////////
// CViewWnd window

class CViewWnd : public CStatic
{
// Construction
public:
	CViewWnd();

// Attributes
public:
private:
	CClientA m_ClientSock;
	CH264Decode m_Dec;
	bool	m_bOpenedChl;
	char	m_sAddress[128];
	char	m_sEseeId[64];
	unsigned short m_nPort;
	int		m_nDevId;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CViewWnd();
	int		ConnectToServer(char *sIp,unsigned short nPort,char *sEseeId,int nDevId);
	int		OpenChannel(int nChannel,bool bOpen);
	void    Closeconn();
	void    SetNetPara(char *ip, unsigned short port);
	void    preview(char *ip, unsigned short port, char *eseeid);
	// Generated message map functions
protected:
	//{{AFX_MSG(CViewWnd)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWWND_H__36C6128B_5E43_4E02_BBD1_08B76593BCD8__INCLUDED_)
