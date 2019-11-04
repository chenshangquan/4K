/*=======================================================================
模块名      :NmsCommon.lib单元测试
文件名      : testnmscommonlib.cpp
相关文件    :
文件实现功能 :
作者        : 李洪强
版本        : V3.6  Copyright(C) 2003-2005 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
--------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2005/01/25	3.6		    李洪强	    创建
=======================================================================*/
// TestNmsCommonLib.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestNmsCommonLib.h"
#include "TestNmsCommonLibDlg.h"
#include "tplarray.h"
#include "calladdr.h"
#include "tplhash.h"
#include "api.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <extensions\TestFactoryRegistry.h>

#pragma comment(lib, "osplib.lib")
#pragma comment(lib, "nmscommon.lib")

CPPUNIT_TEST_SUITE_REGISTRATION(CTplArrayCase);
CPPUNIT_TEST_SUITE_REGISTRATION(CCallAddrCase);
CPPUNIT_TEST_SUITE_REGISTRATION(CAPICase);
CPPUNIT_TEST_SUITE_REGISTRATION(CTplHashCase);


/////////////////////////////////////////////////////////////////////////////
// CTestNmsCommonLibApp

BEGIN_MESSAGE_MAP(CTestNmsCommonLibApp, CWinApp)
	//{{AFX_MSG_MAP(CTestNmsCommonLibApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestNmsCommonLibApp construction

CTestNmsCommonLibApp::CTestNmsCommonLibApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestNmsCommonLibApp object

CTestNmsCommonLibApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestNmsCommonLibApp initialization

BOOL CTestNmsCommonLibApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

    CppUnit::MfcUi::TestRunner cRunner; 

    cRunner.addTest(TestFactoryRegistry::getRegistry().makeTest());
    cRunner.run();
    
//    CTestNmsCommonLibDlg dlg;
//	m_pMainWnd = &dlg;
//	int nResponse = dlg.DoModal();
//	if (nResponse == IDOK)
//	{
//		// TODO: Place code here to handle when the dialog is
//		//  dismissed with OK
//	}
//	else if (nResponse == IDCANCEL)
//	{
//		// TODO: Place code here to handle when the dialog is
//		//  dismissed with Cancel
//	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
