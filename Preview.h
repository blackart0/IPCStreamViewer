#if !defined(AFX_PREVIEW_H__AF3BB0EE_DD7B_49A9_A272_4DAF8AAA6F18__INCLUDED_)
#define AFX_PREVIEW_H__AF3BB0EE_DD7B_49A9_A272_4DAF8AAA6F18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Preview.h : header file
//
#include "ViewWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CPreview dialog

class CPreview : public CDialog
{
public:
	CViewWnd m_streamview;

// Construction
public:
	CPreview(CWnd* pParent = NULL);   // standard constructor
	CRect GetPreviewRect();
	void InitPreview();
// Dialog Data
	//{{AFX_DATA(CPreview)
	enum { IDD = IDD_DIALOG_PREVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPreview)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEW_H__AF3BB0EE_DD7B_49A9_A272_4DAF8AAA6F18__INCLUDED_)
