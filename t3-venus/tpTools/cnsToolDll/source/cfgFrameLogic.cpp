// cfgFrameLogic.cpp: implementation of the CCfgFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "cfgFrameLogic.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgFrameLogic::CCfgFrameLogic()
{
	m_strLstFunMenu = "CfgMenuDlg/LstCfgFuncMenu";
}

CCfgFrameLogic::~CCfgFrameLogic()
{

}


void CCfgFrameLogic::RegCBFun()
{
	CCfgFrameLogic *pThis =  GetSingletonPtr();
	
    REG_GOBAL_MEMBER_FUNC( "CCfgFrameLogic::InitWnd", CCfgFrameLogic::InitWnd, pThis, CCfgFrameLogic ) ;
	//列表按钮点击事件
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickAudioPortCfg", CCfgFrameLogic::OnClickAudioPortCfg, pThis, CCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickEqCfg", CCfgFrameLogic::OnClickEqCfg, pThis, CCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickAudioCfg", CCfgFrameLogic::OnClickAudioCfg, pThis, CCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickMainAudioCfg", CCfgFrameLogic::OnClickMainAudioCfg, pThis, CCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickDemonStrationCfg", CCfgFrameLogic::OnClickDemonStrationCfg, pThis, CCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickAdjustImageCfg", CCfgFrameLogic::OnClickAdjustImageCfg, pThis, CCfgFrameLogic ) ;

}

void CCfgFrameLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCfgFrameLogic::InitWnd" );
}

bool CCfgFrameLogic::InitWnd( const IArgs & arg )
{    
	CLogicBase::InitWnd( arg );
	InitCfgFuncMenu();
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgAudioPort);
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgAudioDlg,false);
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgMainAudioDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgDemonStrationDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgEqDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgAdjustImageDlg, false);
	m_strCurWnd = g_strCfgAudioPort;
	m_strCfgCurWnd = g_strCfgAudioPort;
	return true;
}

void CCfgFrameLogic::Clear()
{
	m_strCfgCurWnd = g_strCfgAudioPort;
	if ( m_pWndTree != NULL )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmConfMenuListDefault", m_pWndTree );   //登陆后初始化默认页面 
	}
}

void CCfgFrameLogic::RegMsg()
{
	CCfgFrameLogic *pThis =  GetSingletonPtr(); 
	//REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CCfgFrameLogic::OnDisConnect, pThis, CCfgFrameLogic );
    REG_MSG_HANDLER( UI_CNSTOOL_VERINFO_NTY, CCfgFrameLogic::OnVerInfoNty, pThis, CCfgFrameLogic );
	
}

void CCfgFrameLogic::UnRegMsg()
{
	
}

bool CCfgFrameLogic::OnClickAudioPortCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgAudioPort);
	return true;
}

void CCfgFrameLogic::SwitchCfgTabWnd( string strWnd )
{
	if ( m_strCurWnd == g_strCfgAudioPort && strWnd != g_strCfgAudioPort )
	{
		bool bChange = CCfgAudioPortLogic::GetSingletonPtr()->IsCfgAudioChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 0 );
			return;
		}
	}

	if ( m_strCurWnd == g_strCfgAudioDlg && strWnd != g_strCfgAudioDlg )
	{
		bool bChange = CCfgAudioDlg::GetSingletonPtr()->IsCfgAudioChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}
	}

	if ( m_strCurWnd == g_strCfgEqDlg && strWnd != g_strCfgEqDlg )
	{
		bool bChange = CCfgEqLogic::GetSingletonPtr()->IsCfgEqChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 2 );
			return;
		}	
	}

	if ( m_strCurWnd == g_strCfgMainAudioDlg && strWnd != g_strCfgMainAudioDlg )
	{
		bool bChange = CCfgMainAudioDlg::GetSingletonPtr()->IsCfgMainAudioChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 3 );
			return;
		}
	}

	if ( m_strCurWnd == g_strCfgAdjustImageDlg && strWnd != g_strCfgAdjustImageDlg )
	{
		bool bChange = CCfgAdjustImageDlg::GetSingletonPtr()->IsCfgParameterChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 5 );
			return;
		}
	}

	HideAllWnd();
	UIFACTORYMGR_PTR->ShowWindow(strWnd);
	m_strCurWnd = strWnd;
	m_strCfgCurWnd = strWnd;
}

void CCfgFrameLogic::InitCfgFuncMenu()
{
	ARRAY<TMenuItem> aryItem;
	TMenuItem item; 
	
	item.SetItemName("音频接口配置" ); 
	item.SetItemType("ImageItemMenuAudioPortCfg");
	aryItem.push_back(item);

	item.SetItemName("音频配置" );  
	item.SetItemType("ImageItemMenuCfgAudio");
	aryItem.push_back(item);

	item.SetItemName("均衡器配置" );  
	item.SetItemType("ImageItemMenuEqCfg");
	aryItem.push_back(item);

 	item.SetItemName("主视频配置" );  
 	item.SetItemType("ImageItemMenuCfgMainAudio");
 	aryItem.push_back(item);
	
 	item.SetItemName("演示源设置" );  
 	item.SetItemType("ImageItemMenuCfgDemonStration");
 	aryItem.push_back(item);

 	item.SetItemName("图像参数设置" );  
 	item.SetItemType("ImageItemMenuCfgAdjustImage");
 	aryItem.push_back(item);

	Value_ItemMenu valueMenu( &aryItem ); 
	valueMenu.m_strAlgroithm = IAlgorithm::strVert;
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree ); 
}

bool CCfgFrameLogic::OnClickAudioCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgAudioDlg);
	return true;
}

bool CCfgFrameLogic::OnClickEqCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgEqDlg);
	return true;
}

bool CCfgFrameLogic::OnClickMainAudioCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgMainAudioDlg);
	return true;
}

bool CCfgFrameLogic::OnClickDemonStrationCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgDemonStrationDlg);
	return true;
}

bool CCfgFrameLogic::OnClickAdjustImageCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgAdjustImageDlg);
	return true;
}

void CCfgFrameLogic::HideAllWnd()
{
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgAudioDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgAudioPort, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgEqDlg, false);
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgMainAudioDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgDemonStrationDlg, false );
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgAdjustImageDlg, false);
}

LRESULT CCfgFrameLogic::OnVerInfoNty( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree == NULL )
    {
        return S_FALSE;
    }

    ReInitCfgFuncMenu();
    return S_OK;
}

void CCfgFrameLogic::ReInitCfgFuncMenu()
{
    EmCnModel emCnModel;
    LIBDATAMGRPTR->GetEmCnModelInfo( &emCnModel );

    ARRAY<TMenuItem> aryItem;
    TMenuItem item;
    
    item.SetItemName("音频接口配置" ); 
    item.SetItemType("ImageItemMenuAudioPortCfg");
    aryItem.push_back(item);
    
    item.SetItemName("音频配置" );  
    item.SetItemType("ImageItemMenuCfgAudio");
    aryItem.push_back(item);
    
    item.SetItemName("均衡器配置" );  
    item.SetItemType("ImageItemMenuEqCfg");
    aryItem.push_back(item);

    //T300E_4K 不支持主视频配置
    if (emCnModel != T300E_4K)
    {
        item.SetItemName("主视频配置" );  
        item.SetItemType("ImageItemMenuCfgMainAudio");
        aryItem.push_back(item);
    }

    item.SetItemName("演示源设置" );  
    item.SetItemType("ImageItemMenuCfgDemonStration");
    aryItem.push_back(item);

    //T300E_4K 不支持图像参数调节
    if (emCnModel != T300E_4K)
    {
        item.SetItemName("图像参数设置" );  
        item.SetItemType("ImageItemMenuCfgAdjustImage");
        aryItem.push_back(item);
    }

    Value_ItemMenu valueMenu( &aryItem );
    valueMenu.m_strAlgroithm = IAlgorithm::strVert;
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree );
}