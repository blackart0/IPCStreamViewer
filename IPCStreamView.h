// IPCStreamView.h : main header file for the IPCSTREAMVIEW application
//

#if !defined(AFX_IPCSTREAMVIEW_H__3BB26420_BD4B_412D_A703_B7059183D383__INCLUDED_)
#define AFX_IPCSTREAMVIEW_H__3BB26420_BD4B_412D_A703_B7059183D383__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIPCStreamViewApp:
// See IPCStreamView.cpp for the implementation of this class
//

class CIPCStreamViewApp : public CWinApp
{
public:
	CIPCStreamViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPCStreamViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIPCStreamViewApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPCSTREAMVIEW_H__3BB26420_BD4B_412D_A703_B7059183D383__INCLUDED_)
