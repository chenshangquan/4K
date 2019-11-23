// moonToolDllIF.cpp : main header file for the MOONTOOLDLL DLL
/*---------------------------------------------------------------------
* 文 件	名： moonToolDllIF.cpp
* 功    能： moonToolDll 的接口文件 
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2014.11.25   1.0         吴蒨蒨        创建
----------------------------------------------------------------------*/

#include "stdafx.h"
#include "moonToolDllIF.h"
 
#include "logicMgr.h"

#include "moonlibdatamgr.h"
#include "moonlibcommonif.h"
//异常处理
#include "exceptioncatch.h" 

#define _NMS_COMMON_CPP_
#include "common.h"

//#pragma comment(lib, "moonlib.lib") 
#pragma comment(lib, "moonlib.lib") 

//cns组提供的库
#pragma comment(lib, "xmlengine.lib")
//#pragma comment(lib, "cnmsg.lib")

//#pragma comment(lib, "moonmsg.lib")
//#pragma comment(lib, "tpmsgmgr.lib") 


//windows 库
#pragma comment (lib, "UIFactory.lib ") 

//nms组提供的库
#pragma comment(lib, "nmscommon.lib")

//公共库
#pragma comment(lib, "osplib.lib")
#pragma comment(lib, "kdvsys.lib")
#pragma comment(lib, "kdvlog.lib")
//#pragma comment(lib, "kdvaddrbook.lib")


//异常处理输出文件
#define EXCEPTION_FILE_PATH _T("moonToolExcep.log")
   


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
static BOOL bInit = FALSE;
HWND g_hNotifyWnd = 0;

MOONTOOLDLL_API BOOL _stdcall IsInitMoonTool()
{   
	return bInit;
}


MOONTOOLDLL_API void _stdcall InitMoonTool( HWND hNotifyWnd )
{ 
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	g_hNotifyWnd = hNotifyWnd;

	if( !bInit )
	{    
		bInit = TRUE;
		//异常处理
		CString strFullPath = GetModuleFullPath();
		strFullPath += EXCEPTION_FILE_PATH;
		CExceptionCatch::LogToFile( (LPSTR)(LPCSTR)strFullPath );
		CExceptionCatch::Start();  

		//初始化lib
 		MOONLIBDATAMGRPTR->InitDataMgr();

		
 		//初始化uifactory
 		UIFACTORYMGR_PTR->InitUIFactory("resmoontool\\system.xml");
		
 		//初始化窗口管理逻辑信息
 		CLogicMgr::GetSingletonPtr()->CreateLogic(); 
       
 		//初始化后将所有的窗口创建,但并不显示,等到接收成功回复时在显示(解决domal窗口显示在mainframe后面)----JYY
  		UIFACTORYMGR_PTR->ShowWindow( g_strMoonMainFrame, FALSE );
 
 		//向OSP注册本模块
 		ModuleRegToOsp();
 		
 		DWORD dwProcessId = GetCurrentProcessId();
 		TCHAR aszPrompt[32] = "";
 		
 		sprintf( aszPrompt, "moontool(%d):", dwProcessId );
 		OspSetPrompt( aszPrompt );

	}
}


MOONTOOLDLL_API void _stdcall DestroyMoonTool()
{  
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if( bInit ) 
	{   
		bInit = FALSE; 
	
		//2013.9.5----JYY  保证mainframe窗口首先创建,销毁部分与init创建冲突
		//销毁lib
		//CNCSESSION_MGR_PTR->DesdroySession();

		//销毁uifactroy
		//UIFACTORYMGR_PTR->DestoryAllWnd();		------可能窗口指针没清空,后续查看
		//UIFACTORYMGR_PTR->UnInitUIFactory();

		//释放异常检测
    	CExceptionCatch::Free();
	}
}

 
 
MOONTOOLDLL_API UINT _stdcall ConnectMoon( DWORD dwCnsIP, DWORD dwCnsPort )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	//调用common中的链接接口登陆cns 	 JYY  2013.4.2  启动线程来连接cns,连接结果直接由mainframe界面接收
 	/*u16 wRet = */

	COMIFMGRPTR->connect(dwCnsIP, dwCnsPort);


//   	if ( NO_ERROR != wRet )
//   	{
//   		LPCTSTR strErr = "网络连接失败";
//   		UIDATAMGR_PTR->NotifyOuterWnd(  WM_TPTOOL_LOGINRESULT, em_LOGIN_ERROR_RSQ, LPARAM(strErr)); 
// 		wRet = 1;
//   	}	
	return NO_ERROR;
}

 

MOONTOOLDLL_API BOOL _stdcall HandleMoonToolMsg( MSG* pMsg )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	if ( NULL == pMsg )
	{
		return FALSE;
	}

	//20130805---------CCTransparentDlg已经对回车键屏蔽sc
	//20130522sc edit控件响应回车消息
// 	if ( pMsg->wParam == VK_RETURN && pMsg->hwnd )
// 	{		
// 		if ( UIFACTORYMGR_PTR->IsVisible( g_strMainFrame ) && UIFACTORYMGR_PTR->IsVisible( g_StrCameraDlg )  )
// 		{
// 			return AfxGetApp()->PreTranslateMessage(pMsg);
// 		}
// 	}

	if ( pMsg->message == WM_COMMAND && pMsg->wParam == WM_DESTROY )	//任务栏右键点击关闭程序  2013年11月8日 JYY
	{

		if ( !UIDATAMGR_PTR->NotifyOuterWnd(WM_CLOSE, 0, 0) )
		{
			UINT uExitCode = 0; 
			ExitProcess( uExitCode );
		}

	}

	

	//解决domodal后 无法接收到cns消息的问题  2013.1.23  yjj
	// UIFACTORYMGR_PTR->HandleMsg(pMsg );    
	return AfxGetApp()->PreTranslateMessage(pMsg);

  
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
    PrtMsg( "moontool version: %s ", GetMoonToolBuildVersion() ); 
    PrtMsg( "compile time:%s %s", __DATE__, __TIME__ );
}

API void prt()
{
    CRkcPrintCtrl::GetPrintCtrl()->PrintAllMsg();
}


API void prtlevel( u8 byLevel )
{
    CRkcPrintCtrl::GetPrintCtrl()->PrintMsgLevel( byLevel );
}

API void stopprt()
{
	CRkcPrintCtrl::GetPrintCtrl()->StopPrint();
}

API void prtid( u32 msgID )
{
	CRkcPrintCtrl::GetPrintCtrl()->SetPrintMsgID( msgID );
}

API void prtrange( u32 beginID, u32 endID )
{ 
    CRkcPrintCtrl::GetPrintCtrl()->SetPrintMsgRange( beginID, endID ); 
}

API void prtrecive( BOOL bPrint /*= TRUE */ )
{
    //CPrintCtrl::GetPrintCtrl()->PrintEnterMsg( bPrint ); 
}

API void prtsend( BOOL bPrint/* = TRUE */)
{
	//CRkcPrintCtrl::GetPrintCtrl()->PrintOutMsg( bPrint );
}