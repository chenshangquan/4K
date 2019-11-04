// CentCfgFrameLogic.cpp: implementation of the CCentCfgFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CentCfgFrameLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCentCfgFrameLogic::CCentCfgFrameLogic()
{
	m_strLstFunMenu = "centCfgMenuDlg/LstcentCfgFuncMenu";
}

CCentCfgFrameLogic::~CCentCfgFrameLogic()
{

}

void CCentCfgFrameLogic::RegCBFun()
{
	CCentCfgFrameLogic *pThis =  GetSingletonPtr();
	
    REG_GOBAL_MEMBER_FUNC( "CCentCfgFrameLogic::InitWnd", CCentCfgFrameLogic::InitWnd, pThis, CCentCfgFrameLogic ) ;
	//列表按钮点击事件
	REG_LIST_CALLFUNC( "CCentCfgFrameLogic::OnClickStatusMesCfg", CCentCfgFrameLogic::OnClickStatusMesCfg, pThis, CCentCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCentCfgFrameLogic::OnClickAirConditionCfg", CCentCfgFrameLogic::OnClickAirConditionCfg, pThis, CCentCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCentCfgFrameLogic::OnClickCameraCfg", CCentCfgFrameLogic::OnClickCameraCfg, pThis, CCentCfgFrameLogic ) ;	
	REG_LIST_CALLFUNC( "CCentCfgFrameLogic::OnClickDisplayCfg", CCentCfgFrameLogic::OnClickDisplayCfg, pThis, CCentCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCentCfgFrameLogic::OnClickCurtainCfg", CCentCfgFrameLogic::OnClickCurtainCfg, pThis, CCentCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCentCfgFrameLogic::OnClickShuangLiuCfg", CCentCfgFrameLogic::OnClickShuangLiuCfg, pThis, CCentCfgFrameLogic ) ;
}

void CCentCfgFrameLogic::RegMsg()
{
	CCentCfgFrameLogic *pThis =  GetSingletonPtr();
//	REG_MSG_HANDLER( UI_CNS_TVSTATE_NTY, CCentCfgFrameLogic::OnDisplayItemNty, pThis, CCentCfgFrameLogic );
	REG_MSG_HANDLER( UI_TPAD_CENTRESLEEP_NTY, CCentCfgFrameLogic::OnCentSleepNty, pThis, CCentCfgFrameLogic );
}

void CCentCfgFrameLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCentCfgFrameLogic::InitWnd" );
}

bool CCentCfgFrameLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	InitCfgFuncMenu();
	UIFACTORYMGR_PTR->ShowWindow( g_strCentStatusMesDlg);
	UIFACTORYMGR_PTR->ShowWindow( g_strCentCurtainDlg,false);
	UIFACTORYMGR_PTR->ShowWindow( g_strCentCameraDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCentAirCondition, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCentDisplayDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCentDuoVideo, false );

	m_strCurWnd = g_strCentStatusMesDlg;
	m_strCfgCurWnd = g_strCentStatusMesDlg;
	return true;
}

LRESULT CCentCfgFrameLogic::OnDisplayItemNty( WPARAM wParam, LPARAM lParam )
{ 
	TMenuItem item;
	ARRAY<TMenuItem> vecItem;
	TCentreTVCfg atCentreTVCfg[MAX_CENTRETV_NUM];
	TCentreTVCfg *pCentreTVCfg = NULL;

	pCentreTVCfg = LIBDATAMGRPTR->GetCentreTVCfg();
	memcpy( atCentreTVCfg, pCentreTVCfg, sizeof(atCentreTVCfg)) ;

	item.SetItemName("显示器配置" );  
	item.SetItemType("ImageItemMenuDisplay");

	if ( atCentreTVCfg[0].emTvModle == emKeShi70GH01A )
	{
		UpdateCentList(item,FALSE);
	}
	else if ( ( atCentreTVCfg[0].emTvModle == emSharp70LCD_LX640A )||( atCentreTVCfg[0].emTvModle == emSharp70LX550A ) )
	{
		UpdateCentList(item,TRUE);
	}

	return S_OK;
}

void CCentCfgFrameLogic::Clear()
{
	m_strCfgCurWnd = g_strCentStatusMesDlg;
	m_VecCurMenuItem = m_VecOldMenuItem;
	if ( m_pWndTree != NULL )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmConfMenuListDefault", m_pWndTree );   //登陆后初始化默认页面
	}
}

void CCentCfgFrameLogic::HideAllWnd()
{
	UIFACTORYMGR_PTR->ShowWindow(g_strCentCurtainDlg,false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCentStatusMesDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCentAirCondition, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCentCameraDlg, false);

	UIFACTORYMGR_PTR->ShowWindow(g_strCentDisplayDlg, false);
	UIFACTORYMGR_PTR->ShowWindow( g_strCentDuoVideo, false );

}

void CCentCfgFrameLogic::UnRegMsg()
{
	
}

void CCentCfgFrameLogic::InitCfgFuncMenu()
{
	TMenuItem item; 
	m_VecOldMenuItem.clear();

	item.SetItemName("状态信息" ); 
	item.SetItemType("ImageItemMenuStatusMes");
	m_VecOldMenuItem.push_back(item);

	item.SetItemName("显示器配置" );  
	item.SetItemType("ImageItemMenuDisplay");
	m_VecOldMenuItem.push_back(item);

	item.SetItemName("摄像机配置" );  
	item.SetItemType("ImageItemMenuCamera");
	m_VecOldMenuItem.push_back(item);
	
	item.SetItemName("空调配置" );  
	item.SetItemType("ImageItemMenuAirCondition");
	m_VecOldMenuItem.push_back(item);

	item.SetItemName("窗帘配置" );  
	item.SetItemType("ImageItemMenuCurtain");
	m_VecOldMenuItem.push_back(item);
	
	item.SetItemName("双流屏配置" );  
	item.SetItemType("ImageItemMenuShuangLiu");
	m_VecOldMenuItem.push_back(item);

	m_VecCurMenuItem = m_VecOldMenuItem;
	Value_ItemMenu valueMenu( &m_VecOldMenuItem ); 
	valueMenu.m_strAlgroithm = IAlgorithm::strVert;
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree ); 
}

bool CCentCfgFrameLogic::OnClickStatusMesCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCentStatusMesDlg);
	return true;
}

bool CCentCfgFrameLogic::OnClickAirConditionCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCentAirCondition);
	return true;
}

bool CCentCfgFrameLogic::OnClickCameraCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCentCameraDlg);
	return true;
}

bool CCentCfgFrameLogic::OnClickDisplayCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCentDisplayDlg);
	return true;
}

bool CCentCfgFrameLogic::OnClickCurtainCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCentCurtainDlg);
	return true;
}

bool CCentCfgFrameLogic::OnClickShuangLiuCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCentDuoVideo);
	return true;
}


void CCentCfgFrameLogic::SwitchCfgTabWnd( string strWnd )
{
	if ( m_strCurWnd == g_strCentDisplayDlg && strWnd != g_strCentDisplayDlg )
	{
		bool bChange = CCentCfgDisplayDlg::GetSingletonPtr()->IsCentCfgDisplayChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}
	}

	if ( m_strCurWnd == g_strCentAirCondition && strWnd != g_strCentAirCondition )
	{
		bool bChange = CCentCfgAirCondition::GetSingletonPtr()->IsACChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 3 );
			return;
		}	
	}
	
	HideAllWnd();
	UIFACTORYMGR_PTR->ShowWindow(strWnd);
	m_strCurWnd = strWnd;
	m_strCfgCurWnd = strWnd;
}

LRESULT CCentCfgFrameLogic::OnXinFengInfoNty( WPARAM wParam, LPARAM lParam )
{
	String strXinFengInfo = "新风：";
	//UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateofXinFeng", "开机", NULL, TRUE);
	
	s8 chXinFeng[8] = {0};
//	sprintf( chXinFeng, "%u", tXinFengInfo.m_byLevel );
	strXinFengInfo += ",";
	strXinFengInfo += chXinFeng;
	strXinFengInfo += "级";
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgXinFengDlg/StcXinFengInfo", strXinFengInfo, NULL, TRUE);
	
	return S_OK;
}

LRESULT CCentCfgFrameLogic::OnCentSleepNty( WPARAM wParam, LPARAM lParam )
{
	//断开cns
	COMIFMGRPTR->DisConnect();
	UIFACTORYMGR_PTR->HideAllWindow();
	LOGICMGR_PTR->DestroyLogic();
	//隐藏cnstool，显示登录界面 		
	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_LOGOFF, 0 );
	return S_OK;
}

void CCentCfgFrameLogic::UpdateCentList( TMenuItem item ,BOOL bAdd )
{
	ARRAY<TMenuItem> vecItem;

	if ( bAdd == FALSE )				//删除列表项
	{
		for ( vector<TMenuItem>::iterator iterCur =m_VecCurMenuItem.begin(); iterCur != m_VecCurMenuItem.end(); iterCur++ )
		{
			if ( strcmp(item.szName,iterCur->szName) == 0 )	
			{
				m_VecCurMenuItem.erase(iterCur);
				break;
			}
		}
	}
	else
	{
		for ( vector<TMenuItem>::iterator iter = m_VecCurMenuItem.begin() ; iter !=m_VecCurMenuItem.end(); iter++ )	//	判断是否存在
		{
			if ( strcmp(item.szName,iter->szName) == 0 )
			{
				return;
			}
		}
		vector<TMenuItem>::iterator iterTemp = m_VecCurMenuItem.begin();
		vector<TMenuItem>::iterator iterCur = m_VecCurMenuItem.begin() ;

		for ( vector<TMenuItem>::iterator iterOld =m_VecOldMenuItem.begin(); iterOld != m_VecOldMenuItem.end(); iterOld++ )
		{
			if ( strcmp(item.szName,iterOld->szName) == 0 )				//如果是增加的项和当前索引的项匹配，增加到临时容器中
			{
				m_VecCurMenuItem.insert(iterTemp,*iterOld);				//插入到匹配的下一项迭代器位置上
				break;
			}
			else																//不是需要增加的列表项
			{
				for ( ; iterCur !=m_VecCurMenuItem.end(); iterCur++ )			//检测当前列表项，是否包含此ITEM
				{
					if ( strcmp( iterCur->szName,iterOld->szName ) == 0)
					{
						iterCur++;
						iterTemp = iterCur;									//找到了，下次遍历从下一个开始
						break;
					}
				}

				if ( iterCur == m_VecCurMenuItem.end() )					//当前应用的列表中没有改项 从上次匹配的后一项开始
				{
					iterCur = iterTemp;
				}
			}
		}
	}

	Value_ItemMenu valueMenu( &m_VecCurMenuItem ); 
	valueMenu.m_strAlgroithm = IAlgorithm::strVert;
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree );
}
