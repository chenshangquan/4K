#if !defined(AFX_LISTTESTDLG_H__5DF40D58_3C12_4E1F_AB28_77696B87092A__INCLUDED_)
#define AFX_LISTTESTDLG_H__5DF40D58_3C12_4E1F_AB28_77696B87092A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// listtestdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListTestDlg dialog

class CListTestDlg : public CBMPDlg
{
// Construction
public:
	CFont m_font;
	CFont m_fontText;
	COLORREF GetColor();
    static int CALLBACK MCompare(LPARAM lp1, LPARAM lp2, LPARAM lp3, LPARAM lp4);
	void InitList();
	CListTestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CListTestDlg)
	enum { IDD = IDD_DIALOG1 };
	CTextButton30	m_btnAddItem;
	CTextButton30	m_btnNew;
	CSkinListCtrl	m_listHide;
	CCheckButton	m_raToolTip3;
	CCheckButton	m_raToolTip2;
	CCheckButton	m_raToolTip1;
	CCheckButton	m_ckDrag;
	CCheckButton	m_ckEnable;
	CCheckButton	m_ckSort;
	CCheckButton	m_ckHot;
	CSkinListCtrl	m_list;
	CString	m_date;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHeadBk();
	afx_msg void OnListText();
	afx_msg void OnListFont();
	afx_msg void OnItemBk();
	afx_msg void OnItemText();
	afx_msg void OnItemFont();
	afx_msg void OnCheckHot();
	afx_msg void OnCheckSort();
	afx_msg void OnCheckEable();
	afx_msg void OnHighlightBk();
	afx_msg void OnHighlightText();
	afx_msg void OnSelectBk();
	afx_msg void OnSelectText();
	afx_msg void OnCheckDrag();
	afx_msg void OnRadioDisable();
	afx_msg void OnRadioFullrow();
	afx_msg void OnRadioHide();
    afx_msg void OnAddItem();
	afx_msg void OnButtonArrow();
	afx_msg void OnButtonScrollbk();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonTurn();
	afx_msg void OnButtonMove();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTTESTDLG_H__5DF40D58_3C12_4E1F_AB28_77696B87092A__INCLUDED_)
