// umstooldll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "umstooldll.h"

#define _NMS_COMMON_CPP_
#include "common.h"

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
// CUmstooldllApp

BEGIN_MESSAGE_MAP(CUmstooldllApp, CWinApp)
	//{{AFX_MSG_MAP(CUmstooldllApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUmstooldllApp construction

CUmstooldllApp::CUmstooldllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

BOOL CUmstooldllApp::PreTranslateMessage(MSG* pMsg) 
{
    UIFACTORYMGR_PTR->HandleMsg( pMsg );
    
    return CWinApp::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUmstooldllApp object

CUmstooldllApp theApp;
HWND g_hNotifyWnd = NULL;
static BOOL g_bInit = FALSE;

TOOLDLL_API void DestoryUmsToolUI()
{ 
	g_bInit = FALSE;
};

TOOLDLL_API BOOL IsInitUmsTool()
{   
	return g_bInit;
}

TOOLDLL_API void InitUmsTool( HWND hNotifyWnd )
{ 
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	g_hNotifyWnd = hNotifyWnd;
	if( !g_bInit )
	{
		g_bInit = TRUE;

		//异常处理
		CString strFullPath = GetModuleFullPath();
		strFullPath += UMSTOOLEXCEPTION_FILE;
		CExceptionCatch::LogToFile( (LPSTR)(LPCSTR)strFullPath );
		CExceptionCatch::Start();  

		//初始化窗口信息
		UIFACTORYMGR_PTR->InitUIFactory(SYSTEM_UMSTOOL_XML);
		
		SESSIONPTR->CreateSession(AID_UMSTOOL2UMS_APP);//初始化创建Session
		DATAMGRPTR->CreateDataMgr();

		//向OSP注册本模块
		ModuleRegToOsp();
		
		DWORD dwProcessId = GetCurrentProcessId();
		TCHAR aszPrompt[32] = "";
		
		sprintf( aszPrompt, "tptool(%d):", dwProcessId );
		OspSetPrompt( aszPrompt );
		
		//初始化窗口管理逻辑信息
		CLogicManage::GetLogicManagePtr()->CreateLogic();
		
		IWndTree* pTree = const_cast<IWndTree*>( UIFACTORYMGR_PTR->GetWindow( g_stcStrMainFrmDlg )); 
		UIFACTORYMGR_PTR->ShowWindow( g_stcStrSysinfoDlg  );
		
		if ( pTree == 0 )
		{
			return;
		}
		
		WndInfo* pInfo = pTree->GetItemData();
		
		CWnd* pMainWnd = AfxGetMainWnd()/*theApp.GetMainWnd()*/;
		
		pMainWnd = pInfo->pWnd ;  
		pMainWnd->SendMessage( WM_REDRAW_UI ,0 ,0 ); 
	}
}

TOOLDLL_API BOOL ConnectToUms(  LPCTSTR strIpAddr, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd )
{ 
 	AFX_MANAGE_STATE( AfxGetStaticModuleState());

	//连接到ums服务器
	u16 nRet = COMMONMGRIFPTR->Connect( htonl(inet_addr(strIpAddr)), nPort, pStrUserName, pStrPswd );
	if ( nRet != NO_ERROR )
	{
		LPCTSTR strErr = "网络连接失败";
		CUmstoolCommon::NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_ERROR_RSQ, LPARAM(strErr));

		return FALSE;
	}

	return TRUE;
};

TOOLDLL_API BOOL /*PASCAL*/ DllPreTranslateMessage(MSG *pMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.PreTranslateMessage(pMsg);
}

//////////////////////////////////OSP打印函数/////////////////////////////////////////////
API void help()
{
    PrtMsg( "\n    showver:                    显示版本和编译时间");
	PrtMsg( "\n    prt:                        打印所有级别为3以上的消息");
	PrtMsg( "\n    prtlevel nLevel:            打印级别为nLevel的消息；消息级别 1-3，\n \
                                               1为级别最高的消息，该级别的消息对系统可能产生致命影响\n \
                                               2为一般级别的消息\n \
                                               3为最低级别消息 " );
	PrtMsg( "\n    stopprt:                    停止打印");
	PrtMsg( "\n    prtid msgID:                打印消息号是msgID的消息");
    PrtMsg( "\n    prtrange beginID endID:     打印消息号范围在 beginID 和 endID 之间的消息");
    PrtMsg( "\n    prtrecive 0 / 1:            打印所有接受到的消息, 0:不打印，1:打印");
    PrtMsg( "\n    prtsend 0 / 1:              打印所有发送出去的消息, 0:不打印，1:打印");
}

API void showver()
{   
    PrtMsg( "umstool version: %s ", GetUmsToolBuildVersion() ); 
    PrtMsg( "compile time:%s %s", __DATE__, __TIME__ );
}

API void prt()
{
    CPrintCtrl::GetPrintCtrl()->PrintAllMsg();
}


API void prtlevel( u8 byLevel )
{
    CPrintCtrl::GetPrintCtrl()->PrintMsgLevel( byLevel );
}

API void stopprt()
{
	CPrintCtrl::GetPrintCtrl()->StopPrint();
}

API void prtid( u32 msgID )
{
	CPrintCtrl::GetPrintCtrl()->SetPrintMsgID( msgID );
}

API void prtrange( u32 beginID, u32 endID )
{ 
    CPrintCtrl::GetPrintCtrl()->SetPrintMsgRange( beginID, endID ); 
}

API void prtrecive( BOOL bPrint /*= TRUE */ )
{
    CPrintCtrl::GetPrintCtrl()->PrintEnterMsg( bPrint ); 
}

API void prtsend( BOOL bPrint/* = TRUE */)
{
	CPrintCtrl::GetPrintCtrl()->PrintOutMsg( bPrint );
}