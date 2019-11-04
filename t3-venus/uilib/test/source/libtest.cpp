// LibTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LibTest.h"
#include "LibTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibTestApp

BEGIN_MESSAGE_MAP(CLibTestApp, CWinApp)
	//{{AFX_MSG_MAP(CLibTestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibTestApp construction

CLibTestApp::CLibTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLibTestApp object

CLibTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLibTestApp initialization

BOOL CLibTestApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

    CSkinMenu::m_s_crBk[0] = RGB(0, 200, 0);
    CSkinMenu::m_s_crBk[1] = RGB(0, 200, 0);
    CSkinScroll::StaticSetArrowColor(RGB(0,0,0), RGB(200, 200, 200));
    CSkinHeaderCtrl::staticSetColors(RGB(200, 200, 200), RGB(0,0,0), -1);
	CLibTestDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
