// moontooldll.h : main header file for the MOONTOOLDLL DLL
//

#if !defined(AFX_MOONTOOLDLL_H__A6408C1E_7FB0_432C_831B_E541B9724209__INCLUDED_)
#define AFX_MOONTOOLDLL_H__A6408C1E_7FB0_432C_831B_E541B9724209__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMoontooldllApp
// See moontooldll.cpp for the implementation of this class
//

class CMoontooldllApp : public CWinApp
{
public:
	CMoontooldllApp();

	void InitEnv();
	virtual BOOL InitInstance();
	virtual int ExitInstance(); // return app exit code
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoontooldllApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMoontooldllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOONTOOLDLL_H__A6408C1E_7FB0_432C_831B_E541B9724209__INCLUDED_)
