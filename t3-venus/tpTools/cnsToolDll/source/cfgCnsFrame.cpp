// cfgCnsFrame.cpp: implementation of the CcfgCnsFrame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgCnsFrame.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgCnsFrame::CCfgCnsFrame()
:m_strLstFunMenu("cfgCnsMenuDlg/LstcfgCnsFuncMenu")
{

}

CCfgCnsFrame::~CCfgCnsFrame()
{

}

void CCfgCnsFrame::RegCBFun()
{
	CCfgCnsFrame *pThis =  GetSingletonPtr();
	
    REG_GOBAL_MEMBER_FUNC( "CCfgCnsFrame::InitWnd", CCfgCnsFrame::InitWnd, pThis, CCfgCnsFrame ) ;

	REG_LIST_CALLFUNC( "CCfgCnsFrame::OnClickCnsCfg", CCfgCnsFrame::OnClickCnsCfg, pThis, CCfgCnsFrame ) ;
//	REG_LIST_CALLFUNC( "CCfgCnsFrame::OnClickNetMgrCfg", CCfgCnsFrame::OnClickNetMgrCfg, pThis, CCfgCnsFrame ) ;
//	REG_LIST_CALLFUNC( "CCfgCnsFrame::OnClickMixCfg", CCfgCnsFrame::OnClickMixCfg, pThis, CCfgCnsFrame ) ;
	REG_LIST_CALLFUNC( "CCfgCnsFrame::OnClickServerCfg", CCfgCnsFrame::OnClickServerCfg, pThis, CCfgCnsFrame ) ;
	REG_LIST_CALLFUNC( "CCfgCnsFrame::OnClickCallSerCfg", CCfgCnsFrame::OnClickCallSerCfg, pThis, CCfgCnsFrame ) ;
	REG_LIST_CALLFUNC( "CCfgCnsFrame::OnClickNetSecurityMgrCfg", CCfgCnsFrame::OnClickNetSecurityMgrCfg, pThis, CCfgCnsFrame ) ;
	REG_LIST_CALLFUNC( "CCfgCnsFrame::OnClickAdvanceCfg", CCfgCnsFrame::OnClickAdvanceCfg, pThis, CCfgCnsFrame ) ;
}

void CCfgCnsFrame::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCfgCnsFrame::InitWnd" );
}

bool CCfgCnsFrame::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	InitCfgFuncMenu();
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgCnsDlg );
//	UIFACTORYMGR_PTR->ShowWindow( g_stcStrCfgNetMngDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgServerDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgCallSer, false );
//	UIFACTORYMGR_PTR->ShowWindow( g_stcStrNetMngOptDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgAdvanceDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrRouteCfgDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrCfgNetSecurityDlg, false );
	m_strCurWnd = g_strCfgCnsDlg;
	m_strCfgCurWnd = g_strCfgCnsDlg;
	return true;
}

void CCfgCnsFrame::Clear()
{
	m_strCfgCurWnd = g_strCfgCnsDlg;
	if ( m_pWndTree != NULL )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmConfMenuListDefault", m_pWndTree );   //µÇÂ½ºó³õÊ¼»¯Ä¬ÈÏÒ³Ãæ
	}
}

void CCfgCnsFrame::HideAllWnd()
{
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgCallSer, false );
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgCnsDlg, false);
//	UIFACTORYMGR_PTR->ShowWindow(g_stcStrCfgNetMngDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgServerDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_stcStrCfgNetSecurityDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgAdvanceDlg, false);
}

void CCfgCnsFrame::InitCfgFuncMenu()
{
	ARRAY<TMenuItem> aryItem;
	TMenuItem item; 	
	item.SetItemName("»áÒéÅäÖÃ" );  
	item.SetItemType("ImageItemMenuCfgCns");
	aryItem.push_back(item);
	
	item.SetItemName("ºô½ÐÅäÖÃ" );  
	item.SetItemType("ImageItemMenuCfgCall");
	aryItem.push_back(item);
	
	item.SetItemName("·þÎñÆ÷ÅäÖÃ" );  
	item.SetItemType("ImageItemMenuServerCfg");
	aryItem.push_back(item);

	item.SetItemName("ÍøÂç°²È«ÅäÖÃ");
	item.SetItemType("ImageItemMenuNetSecurityMgrCfg");
	aryItem.push_back(item);
				
	item.SetItemName("¸ß¼¶ÅäÖÃ" );  
	item.SetItemType("ImageItemAdvanceCfg");
	aryItem.push_back(item);
	
	Value_ItemMenu valueMenu( &aryItem ); 
	valueMenu.m_strAlgroithm = IAlgorithm::strVert;
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree ); 
}

bool CCfgCnsFrame::OnClickCnsCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgCnsDlg);
	return true;
}

bool CCfgCnsFrame::OnClickNetSecurityMgrCfg(const IArgs& args)
{
	SwitchCfgTabWnd(g_stcStrCfgNetSecurityDlg);
	return true;
}

bool CCfgCnsFrame::OnClickNetMgrCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_stcStrCfgNetMngDlg);
	return true;
}

bool CCfgCnsFrame::OnClickServerCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgServerDlg);
	return true;
}

bool CCfgCnsFrame::OnClickCallSerCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgCallSer);
	return true;
}

bool CCfgCnsFrame::OnClickAdvanceCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgAdvanceDlg);
	return true;
}

void CCfgCnsFrame::SwitchCfgTabWnd( string strWnd )
{	
	if ( m_strCurWnd == g_strCfgCnsDlg && strWnd != g_strCfgCnsDlg )
	{
		bool bChange = CCfgCnsLogic::GetSingletonPtr()->IsCfgCnsChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 0 );
			return;
		}
	}

	if ( m_strCurWnd == g_strCfgCallSer && strWnd != g_strCfgCallSer )
	{
		bool bChange = CCfgCallSerLogic::GetSingletonPtr()->IsCfgCallChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}
	}
	
	if ( m_strCurWnd == g_strCfgServerDlg && strWnd != g_strCfgServerDlg )
	{
		bool bChange = CCfgServerLogic::GetSingletonPtr()->IsCfgSerChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 2 );
			return;
		}
	}

	if ( m_strCurWnd == g_stcStrCfgNetSecurityDlg && strWnd != g_stcStrCfgNetSecurityDlg )
	{
		bool bChange = CCfgNetSecurityLogic::GetSingletonPtr()->IsCfgNetChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 3 );
			return;
		}
	}

	if ( m_strCurWnd == g_strCfgAdvanceDlg && strWnd != g_strCfgAdvanceDlg )
	{
		bool bChange = CCfgAdvanceDlg::GetSingletonPtr()->IsCfgChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 4 );
			return;
		}
	}
	
	HideAllWnd();
	UIFACTORYMGR_PTR->ShowWindow(strWnd);
	m_strCurWnd = strWnd;
	m_strCfgCurWnd = strWnd;
}
