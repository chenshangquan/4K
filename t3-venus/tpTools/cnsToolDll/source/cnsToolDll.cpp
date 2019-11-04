// cnsToolDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "cnsToolDll.h"
  
 
// #include "logicMgr.h"
//  #include "uiDataMgr.h"
// 
// //异常处理
// #include "exceptioncatch.h" 
// 
// #pragma comment(lib, "cnclib.lib") 
// 
// //cns组提供的库
// #pragma comment(lib, "xmlengine.lib")
// #pragma comment(lib, "tpmsg.lib")
// #pragma comment(lib, "tpmsgmgr.lib") 
// 
// 
// //windows 库
// #pragma comment (lib, "UIFactory.lib ") 
// 
// //nms组提供的库
// #pragma comment(lib, "nmscommon.lib")
// 
// //公共库
// #pragma comment(lib, "osplib.lib")
// #pragma comment(lib, "kdvsys.lib")
// #pragma comment(lib, "kdvlog.lib")
// #pragma comment(lib, "kdvaddrbook.lib")
// 
// 
// //异常处理输出文件
// #define EXCEPTION_FILE_PATH _T("cnsToolExcep.log")



 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CCnsToolDllApp

BEGIN_MESSAGE_MAP(CCnsToolDllApp, CWinApp)
	//{{AFX_MSG_MAP(CCnsToolDllApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCnsToolDllApp construction

CCnsToolDllApp::CCnsToolDllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCnsToolDllApp object

CCnsToolDllApp theApp; 

void CCnsToolDllApp::InitEnv()
 {/*
	//异常处理
	CString strFullPath = GetModuleFullPath();
	strFullPath += EXCEPTION_FILE_PATH;
	CExceptionCatch::LogToFile( (LPSTR)(LPCSTR)strFullPath );
	CExceptionCatch::Start();  
	
	//初始化lib
	
	
	
	//初始化uifactory
	UIFACTORYMGR_PTR->InitUIFactory("cnsTool\\system.xml");
	
	
	//初始化窗口管理逻辑信息
	CLogicMgr::GetSingletonPtr()->CreateLogic(); 
*/	 
 }
 
BOOL CCnsToolDllApp::InitInstance()
{    
	/*InitEnv();
 	IWndTree* pTree = const_cast<IWndTree*>( UIFACTORYMGR_PTR->GetWindow( g_strMainFrame )); 


	if ( pTree == 0 )
	{
	    return  FALSE;
	}
	WndInfo* pInfo = pTree->GetItemData();


	m_pMainWnd = pInfo->pWnd ;  
	m_pMainWnd->SendMessage( WM_REDRAW_UI ,0 ,0 ); 

	::SetProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName, (HANDLE)1 );

	m_pMainWnd->RunModalLoop();
 */
    return  CWinApp::InitInstance();
}


int CCnsToolDllApp::ExitInstance()
{   
	
 	return  CWinApp::ExitInstance();
} 

BOOL CCnsToolDllApp::PreTranslateMessage(MSG* pMsg) 
{
    UIFACTORYMGR_PTR->HandleMsg(pMsg );    
    return CWinApp::PreTranslateMessage(pMsg); 
    
}

 