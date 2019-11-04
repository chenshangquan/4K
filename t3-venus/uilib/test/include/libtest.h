// LibTest.h : main header file for the LIBTEST application
//

#if !defined(AFX_LIBTEST_H__93688E2B_A3F6_4D42_9080_2AC3934EACC4__INCLUDED_)
#define AFX_LIBTEST_H__93688E2B_A3F6_4D42_9080_2AC3934EACC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "..\prj_win32\resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLibTestApp:
// See LibTest.cpp for the implementation of this class
//

class CLibTestApp : public CWinApp
{
public:
	CLibTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLibTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBTEST_H__93688E2B_A3F6_4D42_9080_2AC3934EACC4__INCLUDED_)
