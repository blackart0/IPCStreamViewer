// IPCStreamViewDlg.h : header file
//

#if !defined(AFX_IPCSTREAMVIEWDLG_H__BD85A48F_D382_4EE3_8C84_F7398907325F__INCLUDED_)
#define AFX_IPCSTREAMVIEWDLG_H__BD85A48F_D382_4EE3_8C84_F7398907325F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ViewWnd.h"
#include "Preview.h"
#include "FocusAssit.h"

/////////////////////////////////////////////////////////////////////////////
// CIPCStreamViewDlg dialog

class CIPCStreamViewDlg : public CDialog
{
// Construction
//private:
//	CViewWnd m_streamview;
private:
	int m_selTab;
	CPreview m_preview;
	CFocusAssit m_focusAssist;
	CDialog *m_dialogs[2];

public:
	CIPCStreamViewDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIPCStreamViewDlg)
	enum { IDD = IDD_IPCSTREAMVIEW_DIALOG };
	CTabCtrl	m_tab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPCStreamViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIPCStreamViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnSelchangingTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPCSTREAMVIEWDLG_H__BD85A48F_D382_4EE3_8C84_F7398907325F__INCLUDED_)
