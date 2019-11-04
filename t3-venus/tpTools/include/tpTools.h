// tpTools.h : main header file for the TPTOOLS application
//

#if !defined(AFX_TPTOOLS_H__578DBC86_A466_4C0E_B9F2_23FBA7850844__INCLUDED_)
#define AFX_TPTOOLS_H__578DBC86_A466_4C0E_B9F2_23FBA7850844__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTpToolsApp:
// See tpTools.cpp for the implementation of this class
//

class CTpToolsApp : public CWinApp
{
public:
	CTpToolsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTpToolsApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTpToolsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void RegListMethod();

private:

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TPTOOLS_H__578DBC86_A466_4C0E_B9F2_23FBA7850844__INCLUDED_)
