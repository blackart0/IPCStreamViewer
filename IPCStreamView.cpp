// IPCStreamView.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "IPCStreamView.h"
#include "IPCStreamViewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPCStreamViewApp

BEGIN_MESSAGE_MAP(CIPCStreamViewApp, CWinApp)
	//{{AFX_MSG_MAP(CIPCStreamViewApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCStreamViewApp construction

CIPCStreamViewApp::CIPCStreamViewApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIPCStreamViewApp object

CIPCStreamViewApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIPCStreamViewApp initialization


BOOL CIPCStreamViewApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	/*
	parse command line
	appname tabIndex ipaddr port blurAlgorithm
	*/
	int tabIndex=0;
	int blurAlgorithm=0;
	if(__argc>1){
		for(int i=0;i<__argc;i++){
			switch (i)
			{
			case 0:
				break;
			case 1:
				tabIndex=atoi(__argv[1]);
				break;
			case 2:
				strcpy(sz_DevIp,__argv[2]);
				break;
			case 3:
				i_Port=atoi(__argv[3]);
				break;
			case 4:
				blurAlgorithm=atoi(__argv[4]);
				break;
			default:break;
			}
		}
	}

	CIPCStreamViewDlg dlg;
	m_pMainWnd = &dlg;
	dlg.m_selTab=tabIndex;
	dlg.m_focusAssist.m_focusview.m_Dec.m_blurjudge.SetJudgeProc(blurAlgorithm);
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
