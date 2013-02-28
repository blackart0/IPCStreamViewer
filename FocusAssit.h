//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_FOCUSASSIT_H__F927382B_9FA1_4C54_B922_574169AC0AC1__INCLUDED_)
#define AFX_FOCUSASSIT_H__F927382B_9FA1_4C54_B922_574169AC0AC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plot/clPlot.h"

// FocusAssit.h : header file
//
#include "ViewWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CFocusAssit dialog

class CFocusAssit : public CDialog
{
public:
	clPlot m_Plot;
	BOOL canSize;
	CViewWnd m_focusview;
// Construction
public:
	CFocusAssit(CWnd* pParent = NULL);   // standard constructor
	CRect GetPreviewRect();
	void InitPreview();
	//
	CRect GetPlotRect();
	void InitPlot();

protected:
// Dialog Data
	//{{AFX_DATA(CFocusAssit)
	enum { IDD = IDD_DIALOG_FOCUS_ASSIST };
	CIPAddressCtrl	m_ipAddr;
	CListBox	m_tips;
	CString	m_port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFocusAssit)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFocusAssit)
	afx_msg void OnButtonSample();
	afx_msg void OnButtonStartFocus();
	afx_msg void OnButtonStopFocus2();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOCUSASSIT_H__F927382B_9FA1_4C54_B922_574169AC0AC1__INCLUDED_)
