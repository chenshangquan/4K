// TestNmsCommonLibDlg.h : header file
//

#if !defined(AFX_TESTNMSCOMMONLIBDLG_H__042A96F5_C224_44EF_934D_E6607B9A6DF7__INCLUDED_)
#define AFX_TESTNMSCOMMONLIBDLG_H__042A96F5_C224_44EF_934D_E6607B9A6DF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestNmsCommonLibDlg dialog

class CTestNmsCommonLibDlg : public CDialog
{
// Construction
public:
	CTestNmsCommonLibDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestNmsCommonLibDlg)
	enum { IDD = IDD_TESTNMSCOMMONLIB_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestNmsCommonLibDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestNmsCommonLibDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTNMSCOMMONLIBDLG_H__042A96F5_C224_44EF_934D_E6607B9A6DF7__INCLUDED_)
