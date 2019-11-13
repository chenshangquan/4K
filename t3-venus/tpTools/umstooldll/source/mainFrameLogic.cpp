// MainWndLogic.cpp: implementation of the CMainWndLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h" 
#include "umstooldll.h"
#include "mainFrameLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMainFrameLogic::CMainFrameLogic():
m_strDlgMain("TPMainDlg"),
m_strLstFunMenu("LstFuncMenu"),
m_strStcUmsIP("StcUmsIP")  
{   
	m_pWndMain = NULL;
}

CMainFrameLogic::~CMainFrameLogic()
{
	 UnRegMsg();
	 UnRegFunc();
}

void CMainFrameLogic::RegMsg()
{    
	REG_MSG_HANDLER( UI_UMS_CONNECTED, CMainFrameLogic::OnLoginRsp, MAINFRMLOGICRPTR, CMainFrameLogic );
	REG_MSG_HANDLER( UI_UMS_LOGIN_TIMEOUT, CMainFrameLogic::OnLoginTimeOut, MAINFRMLOGICRPTR, CMainFrameLogic );

}

void CMainFrameLogic::UnRegMsg()
{
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::InitWnd", CMainFrameLogic::InitWnd, MAINFRMLOGICRPTR, CMainFrameLogic);
}

bool CMainFrameLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::InitWnd", CMainFrameLogic::InitWnd, MAINFRMLOGICRPTR, CMainFrameLogic ) ;

	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnDownloadLog", CMainFrameLogic::OnBtnDownloadLog, MAINFRMLOGICRPTR, CMainFrameLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnRebootUms", CMainFrameLogic::OnBtnRebootUms, MAINFRMLOGICRPTR, CMainFrameLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnLogoff", CMainFrameLogic::OnBtnLogoff, MAINFRMLOGICRPTR, CMainFrameLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnMinimize", CMainFrameLogic::OnBtnMinimize, MAINFRMLOGICRPTR, CMainFrameLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnClose", CMainFrameLogic::OnBtnClose, MAINFRMLOGICRPTR, CMainFrameLogic ); 
    REG_LIST_CALLFUNC( "CMainFrameLogic::OnMenuLstItem", CMainFrameLogic::OnMenuLstItem, MAINFRMLOGICRPTR, CMainFrameLogic ) ; 

	return true;
}
 
bool CMainFrameLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CMainFrameLogic::InitWnd" );
	return true;
}
 
bool CMainFrameLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

    CreateWnd();

	UIFACTORYMGR_PTR->ShowWindow( g_stcStrMainFrmDlg, false );

	InitFunMenu();

	return true;
}

void CMainFrameLogic::CreateWnd()
{
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrSysinfoDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcWaringDlg, true );
}

void CMainFrameLogic::Clear()
{   
	CUmstoolCommon::NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_LOGOFF, 0 );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrMainFrmDlg, false );

	if ( m_pWndTree != NULL )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmMenuListDefault", m_pWndTree );   //登陆后初始化基本信息页面
	}
}

HRESULT CMainFrameLogic::OnLoginRsp( WPARAM wparam, LPARAM lparam)
{	
	LPCTSTR strErr;
	if( !wparam )
	{
		switch( lparam )
		{
		case ERR_UMC_LOGIN_UMS_USER_ERR:
			strErr = "用户名错误";
			break;
		case ERR_UMC_LOGIN_UMS_PSWD_ERR:
			strErr = "密码错误";
			break;
		case ERR_UMC_LOGIN_UMS_MAX_LOGIN:
			strErr = "已达登录用户最大数";
			break;
		case ERR_UMC_LOGIN_UMS_LOGED:
			strErr = "当前用户已登录";
			break;
		case ERR_UMC_LOGIN_UMS_SYSINITING:
			strErr = "当前系统正在初始化，请稍候";
			break;
		case ERR_UMC_CREATE_TCP_FAIL:
			strErr = "网络连接失败";
			break;
		}
		
		CUmstoolCommon::NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_ERROR_RSQ, LPARAM((LPCTSTR)strErr) );
	}
	else
	{
		UIFACTORYMGR_PTR->ShowWindow( g_stcStrMainFrmDlg, true );
		UIFACTORYMGR_PTR->ShowWindow( g_stcStrSysinfoDlg, true );
		CUmstoolCommon::NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_SUCCESS, 0 );

		//初始化主页面
		SwitchTabWnd(g_stcStrSysinfoDlg.c_str());

		m_pWndMain = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrMainFrmDlg );
		if ( NULL != m_pWndMain )
		{
			m_pWndMain->CenterWindow();
			( reinterpret_cast<CTransparentDlg*>(m_pWndMain) )->SetMoveStatus( true );
		}

		//更新界面显示IP地址
		TLoginInfo tLoginInfo = COMMONMGRIFPTR->GetLoginInfo();
		CString cstrIp = CUmstoolCommon::GetIpStr( htonl(tLoginInfo.dwIp) );
		UIFACTORYMGR_PTR->SetCaption( m_strStcUmsIP, cstrIp.GetBuffer(cstrIp.GetLength()), m_pWndTree );

	}
	
	return S_OK;
}

HRESULT CMainFrameLogic::OnLoginTimeOut( WPARAM wparam, LPARAM lparam)
{
	CUmstoolCommon::NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_TIMEOUT, 0 );	

	return S_OK;
}

bool CMainFrameLogic::OnBtnDownloadLog( const IArgs & arg )
{ 
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", NULL, g_stcStrExpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchLogDownload", NULL, g_stcStrExpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrExpCommonDlg );	

	return true;
}

bool CMainFrameLogic::OnBtnRebootUms( const IArgs & arg )
{ 
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "是否重启ums服务器？"  );
	if ( MSGBOX_OK == nMsgBoxRet)
	{
	//	OspPrintf( TRUE, FALSE, "点击重启服务器 MSG_BOX 重启服务器\n" );
		u16 nRet = COMMONMGRIFPTR->RebootReq();;
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "重启ums请求发送失败" );
		}
	}

	return true;
}

bool CMainFrameLogic::OnBtnLogoff( const IArgs & arg )
{ 
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "是否注销当前系统？"  );
	if ( MSGBOX_OK == nMsgBoxRet)
	//int nRet = AfxMessageBox( "是否注销当前系统？", MB_OKCANCEL );
	//if ( nRet == IDOK )
	{
		COMMONMGRIFPTR->DisConnect();
		CUmstoolCommon::NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_LOGOFF, 0 );
	}

	return true;
}

bool CMainFrameLogic::OnBtnMinimize( const IArgs & arg )
{ 
	UIFACTORYMGR_PTR->MinmizeWnd();

	return true;
}

bool CMainFrameLogic::OnBtnClose( const IArgs & arg )
{ 
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "是否退出当前系统？" );
	if ( MSGBOX_OK == nMsgBoxRet )
	{
		SESSIONPTR->DesdroySession();
		if ( !CUmstoolCommon::NotifyOuterWnd( WM_CLOSE, 0, 0 )  )
		{
			UINT uExitCode = 0; 
			ExitProcess( uExitCode );
		}
	}

	return true;
}

void CMainFrameLogic::SwitchTabWnd(CString strItemName)
{
	if ( m_strCurPage == g_stcStrCorrelativeCfgDlg.c_str() && strItemName != g_stcStrCorrelativeCfgDlg.c_str() )
	{
		bool bRes = CORRELATIVECFGLOGICRPTR->ShowWindow( false );
		if ( bRes== false )
		{
			CUmstoolCommon::SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}

		//检测单板数据信息变化
		if( !BOARDLOGICRPTR->CheckPageDataChangeToSave() )
		{
			CUmstoolCommon::SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}

		//检测电视墙单板数据信息变化
		if( !TVWBOARDLOGICRPTR->CheckPageDataChangeToSave() )
		{
			CUmstoolCommon::SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}

		//检测电视墙预案数据信息变化
		if( !TVWSTYLELOGICRPTR->CheckPageDataChangeToSave() )
		{
			CUmstoolCommon::SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}

	}

	if ( 0 == g_stcStrCorrelativeCfgDlg.compare(strItemName) )
	{
		UMSCFGLOGICRPTR->CheckCtrlState();
	}

	UIFACTORYMGR_PTR->ShowWindow( g_stcStrSysinfoDlg, !g_stcStrSysinfoDlg.compare(strItemName) );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrCorrelativeCfgDlg, !g_stcStrCorrelativeCfgDlg.compare(strItemName) );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrAddrbookExpDlg, !g_stcStrAddrbookExpDlg.compare(strItemName) );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrTemplateExpDlg, !g_stcStrTemplateExpDlg.compare(strItemName) );

	m_strCurPage = strItemName;
}

void CMainFrameLogic::InitFunMenu()
{
	ARRAY<TMenuItem> aryItem;
	TMenuItem item; 
	
	item.SetItemName( g_stcStrSysinfoDlg.c_str() );  
	item.SetItemType("ImageItemMenuSysInfo");
	aryItem.push_back(item);

	item.SetItemName( g_stcStrCorrelativeCfgDlg.c_str() ); 
	item.SetItemType("ImageItemMenuCfg");
	aryItem.push_back(item);
	
	item.SetItemName( g_stcStrAddrbookExpDlg.c_str() );  
	item.SetItemType("ImageItemMenuAddrbookExp");
	aryItem.push_back(item);
	
	item.SetItemName( g_stcStrTemplateExpDlg.c_str() );  
	item.SetItemType("ImageItemMenuTemplateExp");
	aryItem.push_back(item);
	
	Value_ItemMenu valueMenu( &aryItem ); 
	valueMenu.m_strClickItemFunc = "CMainFrameLogic::OnMenuLstItem";
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree ); 
}

bool CMainFrameLogic::OnMenuLstItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_ItemMenu *pItemInfo = dynamic_cast<const Data_ItemMenu*>( pBaseItem->GetUserData() ) )
		{
			CString strMenuItemName = pItemInfo->m_tMenuItem.szName;
			SwitchTabWnd(strMenuItemName);
		}
	}

	return true;
}