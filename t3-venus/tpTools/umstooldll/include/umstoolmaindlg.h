#if !defined(AFX_UMSTOOLMAINDLG_H__A7CB6120_0BD4_4CB3_8EED_5E0085B8A884__INCLUDED_)
#define AFX_UMSTOOLMAINDLG_H__A7CB6120_0BD4_4CB3_8EED_5E0085B8A884__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// umstoolmaindlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUmstoolMainDlg dialog

class CUmstoolMainDlg : public CDialog
{
// Construction
public:
	CUmstoolMainDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUmstoolMainDlg)
	enum { IDD = IDD_DIALOG_UMSTOOLMAIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUmstoolMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUmstoolMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBtnLogoff();
	afx_msg void OnBtnExit();
	afx_msg LRESULT OnConnectUmsRsp(  WPARAM wParam, LPARAM lParam ) ;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	virtual bool UnRegFunc();
	virtual void RegMsg();


private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UMSTOOLMAINDLG_H__A7CB6120_0BD4_4CB3_8EED_5E0085B8A884__INCLUDED_)
