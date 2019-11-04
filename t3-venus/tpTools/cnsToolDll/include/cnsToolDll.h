// cnsToolDll.h : main header file for the CNSTOOLDLL DLL
//

#if !defined(AFX_CNSTOOLDLL_H__72D0D324_44BE_48B6_A7D1_BDC47BBF30CE__INCLUDED_)
#define AFX_CNSTOOLDLL_H__72D0D324_44BE_48B6_A7D1_BDC47BBF30CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCnsToolDllApp
// See cnsToolDll.cpp for the implementation of this class
//

class CCnsToolDllApp : public CWinApp
{
public:
	CCnsToolDllApp();

	void InitEnv();

	virtual BOOL InitInstance();
	virtual int ExitInstance(); // return app exit code
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCnsToolDllApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCnsToolDllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
 
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNSTOOLDLL_H__72D0D324_44BE_48B6_A7D1_BDC47BBF30CE__INCLUDED_)
