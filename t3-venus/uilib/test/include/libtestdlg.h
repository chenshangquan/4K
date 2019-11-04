// LibTestDlg.h : header file
//

#if !defined(AFX_LIBTESTDLG_H__94C1A0FF_8812_4BA3_9722_7289F368AA73__INCLUDED_)
#define AFX_LIBTESTDLG_H__94C1A0FF_8812_4BA3_9722_7289F368AA73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "listTestDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CLibTestDlg dialog

class CLibTestDlg : public CBMPDlg
{
// Construction
public:
	CFont m_font;
	CLibTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLibTestDlg)
	enum { IDD = IDD_LIBTEST_DIALOG };
	CEdit	m_siEdit;
	CColorSelCtrl	m_colorsel;
	CSkinTab	m_tab;
	CFlatButton	m_btnPos;
	CSkinEdit	m_medit;
	CSkinCheckList	m_checklist;
	CSkinGroup	m_Group;
	CSkinSpinCtrl	m_Spin;
	CStaticEx	m_staticMuLIne;
	CFlatButton	m_btMenu;
	CSkinComboBox	m_comboxSkin;
	CStaticEx	m_StaticHide;
	CSkinIPCtrl	m_ipCtrl;
	CSkinEdit	m_editSingle;
	CStaticEx	m_Static;
	CFlatButton	m_btList;
	CSkinSlider	m_Slider;
    COLORREF    m_crTest;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    CSkinMenu m_Menu;
    CListTestDlg m_dlg;

	// Generated message map functions
	//{{AFX_MSG(CLibTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonList();
	afx_msg void OnUpdateMenubtItem(CCmdUI* pCmdUI);
    afx_msg LRESULT On_MenuCallback(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButton1();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnMenubtItem1();
	afx_msg void OnButtonMoveip();
    afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	afx_msg void OnSetfocusEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBTESTDLG_H__94C1A0FF_8812_4BA3_9722_7289F368AA73__INCLUDED_)
