// correlativecfglogic.cpp: implementation of the CCorrelativeCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umstooldll.h"
#include "correlativecfglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCorrelativeCfgLogic::CCorrelativeCfgLogic():
m_strLstCfgFunMenu( "CfgMenuDlg/LstCfgFuncMenu" )
{
	
}

CCorrelativeCfgLogic::~CCorrelativeCfgLogic()
{  
	UnRegMsg();
	UnRegFunc();
}

void CCorrelativeCfgLogic::RegMsg()
{    
    //REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CCorrelativeCfgLogic::OnDisConnect, m_pLogic, CCorrelativeCfgLogic );
}

void CCorrelativeCfgLogic::UnRegMsg()
{
	
}

bool CCorrelativeCfgLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CCorrelativeCfgLogic::InitWnd", CCorrelativeCfgLogic::InitWnd, CORRELATIVECFGLOGICRPTR, CCorrelativeCfgLogic);
	REG_LIST_CALLFUNC( "CCorrelativeCfgLogic::OnMenuLstItem", CCorrelativeCfgLogic::OnMenuLstItem, CORRELATIVECFGLOGICRPTR, CCorrelativeCfgLogic ) ; 

	return true;
}

bool CCorrelativeCfgLogic::UnRegFunc()
{
	
	return true;
}


bool CCorrelativeCfgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

	InitCfgFuncMenu();

	SwitchConfigTabWnd(g_stcStrUmsCfgDlg.c_str());
	
    return true;
}

void CCorrelativeCfgLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmConfMenuListDefault", m_pWndTree );   //登陆后初始化默认页面
	}

}

void CCorrelativeCfgLogic::InitCfgFuncMenu()
{
	ARRAY<TMenuItem> aryItem;
	TMenuItem item; 
	
	item.SetItemName( g_stcStrUmsCfgDlg.c_str() );  
	item.SetItemType("ImageItemToUmsConfig");
	aryItem.push_back(item);
	
	item.SetItemName( g_stcStrBoardCfgDlg.c_str() ); 
	item.SetItemType("ImageItemToBoardConfig");
	aryItem.push_back(item);
	
	item.SetItemName( g_stcStrTvwBoardCfgDlg.c_str() );  
	item.SetItemType("ImageItemToTvwConfig");
	aryItem.push_back(item);
	
	item.SetItemName( g_stcStrTvwStyleCfgDlg.c_str() );  
	item.SetItemType("ImageItemToTvwdefConfig");
	aryItem.push_back(item);
	
	item.SetItemName( g_stcStrNetMngCfgDlg.c_str() ); 
	item.SetItemType("ImageItemToNetmngConfig");
	aryItem.push_back(item);
	
	item.SetItemName( g_stcStrBackupCfgDlg.c_str() );  
	item.SetItemType("ImageItemTobakupConfig");
	aryItem.push_back(item);

	item.SetItemName( g_stcStrVTRCfgDlg.c_str() ); 
	item.SetItemType("ImageItemToVTRConfig");
	aryItem.push_back(item);
	
	Value_ItemMenu valueMenu( &aryItem ); 
	valueMenu.m_strAlgroithm = IAlgorithm::strVert;
	valueMenu.m_strClickItemFunc = "CCorrelativeCfgLogic::OnMenuLstItem";
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstCfgFunMenu, m_pWndTree ); 
}

bool CCorrelativeCfgLogic::OnMenuLstItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_ItemMenu *pItemInfo = dynamic_cast<const Data_ItemMenu*>( pBaseItem->GetUserData() ) )
		{
			//UIFACTORYMGR_PTR->EnableWindow( m_strLstCfgFunMenu, false, m_pWndTree );
			CString strMenuItemName = pItemInfo->m_tMenuItem.szName;
			SwitchConfigTabWnd(strMenuItemName);
			//UIFACTORYMGR_PTR->EnableWindow( m_strLstCfgFunMenu, true, m_pWndTree );
		}
	}
	
	return true;
}

void CCorrelativeCfgLogic::SwitchConfigTabWnd(CString strItemName)
{
	if ( m_strCurPage == g_stcStrUmsCfgDlg.c_str() && strItemName != g_stcStrUmsCfgDlg.c_str() )
	{
		bool bRes = UMSCFGLOGICRPTR->ShowWindow( false );
		if ( bRes == false )
		{
			CUmstoolCommon::SetLstSelItem( m_strLstCfgFunMenu, m_pWndTree, 0 );
			return;
		}
	}
	
	//检测单板数据信息变化
	if ( m_strCurPage == g_stcStrBoardCfgDlg.c_str() && strItemName != g_stcStrBoardCfgDlg.c_str() )
	{
		if( !BOARDLOGICRPTR->CheckPageDataChangeToSave() )
		{
			CUmstoolCommon::SetLstSelItem( m_strLstCfgFunMenu, m_pWndTree, 1 );
			return;
		}
	}	
	
	//检测电视墙单板数据信息变化
	if ( m_strCurPage == g_stcStrTvwBoardCfgDlg.c_str() && strItemName != g_stcStrTvwBoardCfgDlg.c_str() )
	{
		if( !TVWBOARDLOGICRPTR->CheckPageDataChangeToSave() )
		{
			CUmstoolCommon::SetLstSelItem( m_strLstCfgFunMenu, m_pWndTree, 2 );
			return;
		}
	}

	
	//检测电视墙预案数据信息变化
	if ( m_strCurPage == g_stcStrTvwStyleCfgDlg.c_str() && strItemName != g_stcStrTvwStyleCfgDlg.c_str() )
	{
		if( !TVWSTYLELOGICRPTR->CheckPageDataChangeToSave() )
		{
			CUmstoolCommon::SetLstSelItem( m_strLstCfgFunMenu, m_pWndTree, 3 );
			return;
		}
	}

	if ( 0 == g_stcStrUmsCfgDlg.compare(strItemName) )
	{
		UMSCFGLOGICRPTR->CheckCtrlState();
	}
	else if ( 0 == g_stcStrTvwStyleCfgDlg.compare(strItemName) )
	{
		TVWSTYLELOGICRPTR->UpdateTvwStyleList();
	}


	UIFACTORYMGR_PTR->ShowWindow( g_stcStrUmsCfgDlg, !g_stcStrUmsCfgDlg.compare(strItemName) );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrBoardCfgDlg, !g_stcStrBoardCfgDlg.compare(strItemName) );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrTvwBoardCfgDlg, !g_stcStrTvwBoardCfgDlg.compare(strItemName) );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrNetMngCfgDlg, !g_stcStrNetMngCfgDlg.compare(strItemName) );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrTvwStyleCfgDlg, !g_stcStrTvwStyleCfgDlg.compare(strItemName) );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrVTRCfgDlg, !g_stcStrVTRCfgDlg.compare(strItemName) );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrBackupCfgDlg, !g_stcStrBackupCfgDlg.compare(strItemName) );

	m_strCurPage = strItemName;
}

bool CCorrelativeCfgLogic::ShowWindow( BOOL32 bShow )
{	
	if ( m_strCurPage == g_stcStrUmsCfgDlg.c_str() )
	{
		bool bRes = UMSCFGLOGICRPTR->ShowWindow( false );
		if ( bRes == false )
		{
			return false;
		}
	}
	
	return true;
}