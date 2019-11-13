// TvwBoardcfglogic.cpp: implementation of the CTvwBoardCfgLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umstooldll.h"
#include "TvwBoardcfglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTvwBoardCfgLogic::CTvwBoardCfgLogic():
m_strLstTvwBoardFloor("LstTvwBoardFloor"),
m_strLstTvwFloorMenu("LstTvwFloorMenu"),
m_strBtnTvwBoardDel("BtnTvwBoardDel"),
m_strBtnTvwBoardModify("BtnTvwBoardModify"),
m_strBtnTvwBoardAdd("BtnTvwBoardAdd"),
m_strBtnTvwBoardModeDel("BtnTvwBoardModeDel"),
m_strBtnTvwBoardModeSave("BtnTvwBoardModeSave"),
m_strBtnTvwBoardReboot("BtnTvwBoardReboot"),
m_strBtnTvwBoardUpgrade("BtnTvwBoardUpgrade"),
m_strEdtTvwBoardModeName("EdtTvwBoardModeName"),
m_strComboxTvwBoardInputPortOne("StcComboxTvwBoardInputPortOne"),
m_strComboxTvwBoardInputPortTwo("StcComboxTvwBoardInputPortTwo"),
m_strComboxTvwBoardInputPortOneNTSC("StcComboxTvwBoardInputPortOneNTSC"),
m_strComboxTvwBoardInputPortTwoNTSC("StcComboxTvwBoardInputPortTwoNTSC"),
m_strComboxTvwBoardInputPortOnePer("StcComboxTvwBoardInputPortOnePer"),
m_strComboxTvwBoardInputPortTwoPer("StcComboxTvwBoardInputPortTwoPer"),
m_strComboxTvwBoardInputPortOnePerPloy("StcComboxTvwBoardInputPortOnePerPloy"),
m_strComboxTvwBoardInputPortTwoPerPloy("StcComboxTvwBoardInputPortTwoPerPloy")
{
	m_bMdlDataChange = FALSE;
	m_nCurFloorNo = 0;
}

CTvwBoardCfgLogic::~CTvwBoardCfgLogic()
{  
	UnRegMsg();
	UnRegFunc();
}

void CTvwBoardCfgLogic::RegMsg()
{    
    //REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CTvwBoardCfgLogic::OnDisConnect, m_pLogic, CTvwBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_REFRESHTVWBOARD_NTY, CTvwBoardCfgLogic::OnRefreshTvwBoardInfoNotify, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_OPTTVWBOARD_NTY, CTvwBoardCfgLogic::OnOptTvwBoardNotify, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_OPTTVWBOARD_RSP, CTvwBoardCfgLogic::OnOptTvwBoardRsp, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_DELTVWBOARD_NTY, CTvwBoardCfgLogic::OnDelTvwBoardNotify, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_OPTTVWBOARDMODE_NTY, CTvwBoardCfgLogic::OnOptTvwBoardModeNotify, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_DELTVWBOARDMODE_NTY, CTvwBoardCfgLogic::OnDelTvwBoardModeNotify, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_OPTTVWBOARDMODE_RSP, CTvwBoardCfgLogic::OnOptTvwBoardModeRsp, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_TVWBOARDUPGRADE_RSP, CTvwBoardCfgLogic::OnTvwBoardUpgradeRsp, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_TVWBOARDBEGINUPGRADE, CTvwBoardCfgLogic::OnTvwBoardBeginUpgrade, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic );

}

void CTvwBoardCfgLogic::UnRegMsg()
{

}

bool CTvwBoardCfgLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::InitWnd", CTvwBoardCfgLogic::InitWnd, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic );
	REG_LIST_CALLFUNC( "CTvwBoardCfgLogic::OnMenuLstItem", CTvwBoardCfgLogic::OnMenuLstItem, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_LIST_CALLFUNC( "CTvwBoardCfgLogic::OnTvwBoardLstFloorItem", CTvwBoardCfgLogic::OnTvwBoardLstFloorItem, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 

	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnBtnTvwBoardDel", CTvwBoardCfgLogic::OnBtnTvwBoardDel, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnBtnTvwBoardModify", CTvwBoardCfgLogic::OnBtnTvwBoardModify, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnBtnTvwBoardAdd", CTvwBoardCfgLogic::OnBtnTvwBoardAdd, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnBtnTvwBoardReboot", CTvwBoardCfgLogic::OnBtnTvwBoardReboot, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnBtnTvwBoardUpgrade", CTvwBoardCfgLogic::OnBtnTvwBoardUpgrade, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnBtnTvwBoardModeDel", CTvwBoardCfgLogic::OnBtnTvwBoardModeDel, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnBtnTvwBoardModeSave", CTvwBoardCfgLogic::OnBtnTvwBoardModeSave, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortOneChange", CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortOneChange, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortTwoChange", CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortTwoChange, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnTvwBoardMdlEditInputNTFSOneChange", CTvwBoardCfgLogic::OnTvwBoardMdlEditInputNTFSOneChange, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnTvwBoardMdlEditInputNTFSTwoChange", CTvwBoardCfgLogic::OnTvwBoardMdlEditInputNTFSTwoChange, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 

	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortOneClick", CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortOneClick, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortTwoClick", CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortTwoClick, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwBoardCfgLogic::OnClickTvwBoardLstBlack", CTvwBoardCfgLogic::OnClickTvwBoardLstBlack, TVWBOARDLOGICRPTR, CTvwBoardCfgLogic ); 

	return true;
}

bool CTvwBoardCfgLogic::UnRegFunc()
{

	return true;
}

bool CTvwBoardCfgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

	InitFunMenu();
 	InitTvwBoardListData();

 	ResetTvwBoardPageControl();

    return true;
}

void CTvwBoardCfgLogic::ResetTvwBoardPageControl()
{
	m_tHduCfgSel.Clear();
	UIFACTORYMGR_PTR->LoadScheme( "SchmTvwBoardListDataClean", m_pWndTree );
	
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardDel, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModify, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardAdd, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardReboot, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardUpgrade, false, m_pWndTree );

	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeDel, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeSave, false, m_pWndTree );

	CleanTvwMdlControlShow();
}

void CTvwBoardCfgLogic::InitTvwBoardListData()
{
	UpdateTvwBoardLayarList(0);
}

void CTvwBoardCfgLogic::UpdateTvwBoardLayarList(s32 nLayar)
{
	UpdateLayarList(nLayar);
}

void CTvwBoardCfgLogic::UpdateLayarList( s32 nLayar, BOOL bIsReset )
{
	std::multimap<u8,THduCfg> mulmapHduCfg;
	if ( !bIsReset )
	{
		mulmapHduCfg = DATAMGRPTR->GetUmsTvwBoardData();
	}
	else
	{
		mulmapHduCfg.clear();
		for ( s32 nXIndex = 0; nXIndex < 10; nXIndex++ )
		{
			s32 nLayer = nXIndex;
			for ( s32 nYIndex = 0; nYIndex < 7; nYIndex++ )
			{
				THduCfg tHduCfg;
				tHduCfg.m_byLayer = nXIndex;
				tHduCfg.m_bySlot = nYIndex;
				tHduCfg.m_dwIP = 0;
				mulmapHduCfg.insert(std::make_pair<u8,THduCfg>( nLayer, tHduCfg) );
			}
		}
	}

	m_vecTPTvwBrdInfo.clear();

	THduCfg tHduCfg;
	for ( std::multimap<u8,THduCfg>::iterator iter = mulmapHduCfg.begin(); iter != mulmapHduCfg.end(); iter++ )
	{
		tHduCfg = (*iter).second;
		
		if ( nLayar == tHduCfg.m_byLayer )
		{
			m_vecTPTvwBrdInfo.push_back(tHduCfg);
		}
		
		if ( m_tHduCfgSel.m_byLayer == tHduCfg.m_byLayer &&
			m_tHduCfgSel.m_bySlot == tHduCfg.m_bySlot )
		{
			m_tHduCfgSel = tHduCfg;
			if( m_tHduCfgSel.m_bBrdReg && m_tHduCfgSel.m_bServiceReg )
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardReboot, true, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardUpgrade, true, m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardReboot, false, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardUpgrade, false, m_pWndTree );
			}
		}
	}
	
	Value_ViewListTvwBoard valBoard(&m_vecTPTvwBrdInfo);
	valBoard.m_strClickItemFunc = "CTvwBoardCfgLogic::OnTvwBoardLstFloorItem";
	UIFACTORYMGR_PTR->SetPropertyValue( valBoard, m_strLstTvwBoardFloor, m_pWndTree );
}

void CTvwBoardCfgLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmTvwFloorMenuListDefault", m_pWndTree );   //登陆后初始化基本信息页面
	}

	InitTvwBoardListData();
	ResetTvwBoardPageControl();
 	m_vecTPTvwBrdInfo.clear();
	m_bMdlDataChange = FALSE;

	m_nCurFloorNo = 0;

	UpdateLayarList( 0, TRUE );
}

void CTvwBoardCfgLogic::InitFunMenu()
{
	ARRAY<TMenuItem> aryItem;
	TMenuItem item; 
	
	item.SetItemName( "0" );  
	item.SetItemType("ImageTvwItemMenuZeroFloor");
	aryItem.push_back(item);

	item.SetItemName( "1" ); 
	item.SetItemType("ImageTvwItemMenuFirFloor");
	aryItem.push_back(item);

	item.SetItemName( "2" );  
	item.SetItemType("ImageTvwItemMenuSecFloor");
	aryItem.push_back(item);
	
	item.SetItemName( "3" );  
	item.SetItemType("ImageTvwItemMenuThiFloor");
	aryItem.push_back(item);

	item.SetItemName( "4" );  
	item.SetItemType("ImageTvwItemMenuForFloor");
	aryItem.push_back(item);
	
	item.SetItemName( "5" ); 
	item.SetItemType("ImageTvwItemMenuFifFloor");
	aryItem.push_back(item);
	
	item.SetItemName( "6" );  
	item.SetItemType("ImageTvwItemMenuSixFloor");
	aryItem.push_back(item);
	
	item.SetItemName( "7" );  
	item.SetItemType("ImageTvwItemMenuSevenFloor");
	aryItem.push_back(item);

	item.SetItemName( "8" );  
	item.SetItemType("ImageTvwItemMenuEightFloor");
	aryItem.push_back(item);
	
	item.SetItemName( "9" );  
	item.SetItemType("ImageTvwItemMenuNineFloor");
	aryItem.push_back(item);

	Value_ItemMenu valueMenu( &aryItem ); 
	valueMenu.m_strClickItemFunc = "CTvwBoardCfgLogic::OnMenuLstItem";
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstTvwFloorMenu, m_pWndTree ); 
}

bool CTvwBoardCfgLogic::OnMenuLstItem( const IArgs & arg )
{
	if ( !CheckPageDataChangeToSave() )
	{
		CUmstoolCommon::SetLstSelItem( m_strLstTvwFloorMenu, m_pWndTree, m_tHduCfgSel.m_byLayer );
		return false;
	}

	m_bMdlDataChange = FALSE;

	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_ItemMenu *pItemInfo = dynamic_cast<const Data_ItemMenu*>( pBaseItem->GetUserData() ) )
		{
			String strMenuItemName = pItemInfo->m_tMenuItem.szName;
			m_nCurFloorNo = atoi( strMenuItemName.c_str() );
			UpdateTvwBoardLayarList(m_nCurFloorNo);
			ResetTvwBoardPageControl();   //切换以后目前不清空   保持原选中项不变

			//切换后  如果切换到其他层   则置列表为非选中状态    如果选中层号和切换层号相同则置槽号为选中项
// 			if( m_nCurFloorNo == m_tHduCfgSel.m_byLayer )
// 			{
// 				CUmstoolCommon::SetLstSelItem( m_strLstTvwBoardFloor, m_pWndTree, m_tHduCfgSel.m_bySlot );
// 			}
// 			else
// 			{
// 				CUmstoolCommon::SetLstSelItem( m_strLstTvwBoardFloor, m_pWndTree, -1 );
// 			}
		}
	}

	return true;
}

bool CTvwBoardCfgLogic::OnBtnTvwBoardDel( const IArgs & arg )
{ 
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "确定要删除电视墙单板？"  );
	if ( MSGBOX_OK == nMsgBoxRet)
	{
		TTPBrdPos tTPBrdPos;
		tTPBrdPos.m_byBrdLayer = m_tHduCfgSel.m_byLayer;
		tTPBrdPos.m_byBrdSlot = m_tHduCfgSel.m_bySlot;

		u16 nRet = COMMONMGRIFPTR->TvwBoardDeleteReq(tTPBrdPos);;
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "删除电视墙单板请求发送失败" );
		}
	}

	return true;
}

bool CTvwBoardCfgLogic::OnBtnTvwBoardModify( const IArgs & arg )
{
	CMsgDispatch::SendMessage( UI_UMSTOOL_MSG_TVWBOARDSELDATA_Click, (WPARAM)&m_tHduCfgSel, (LPARAM)em_TVWBOARDOPT_MODIFY );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrBoardOptDlg );

	return true;
}

bool CTvwBoardCfgLogic::OnBtnTvwBoardAdd( const IArgs & arg )
{ 
	if ( !ControlNotNullBoradLayorCount() )
	{
		MSG_BOX_OK( "电视墙单板配置已达到4层!" );
		return true;
	}
	else
	{
		CMsgDispatch::SendMessage( UI_UMSTOOL_MSG_TVWBOARDSELDATA_Click, (WPARAM)&m_tHduCfgSel, (LPARAM)em_TVWBOARDOPT_ADD );
		s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrBoardOptDlg );
	}
	
	return true;
}

bool CTvwBoardCfgLogic::OnBtnTvwBoardReboot( const IArgs & arg )
{ 
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "是否重启电视墙单板操作？" );
	if ( MSGBOX_OK == nMsgBoxRet)
	{
		TTPBrdPos	tBrdPos;
		tBrdPos.m_byBrdLayer = m_tHduCfgSel.m_byLayer;
		tBrdPos.m_byBrdSlot = m_tHduCfgSel.m_bySlot;
		u16 nRet = COMMONMGRIFPTR->TvwBoardRebootReq(tBrdPos);;
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "单板重启请求发送失败" );
		}
	}

	return true;
}

bool CTvwBoardCfgLogic::OnBtnTvwBoardUpgrade( const IArgs & arg )
{ 
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchUpgradeBoard", NULL, g_stcStrImpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrImpCommonDlg );	

	return true;
}

bool CTvwBoardCfgLogic::SetTvwModeControlInfoToSevr()
{
	String strTvwBoardModeName;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTvwBoardModeName, strTvwBoardModeName, m_pWndTree );   
	
	String strTvwBoardInputPortOne;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOne, strTvwBoardInputPortOne, m_pWndTree );
	
	String strTvwBoardInputPortTwo;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwo, strTvwBoardInputPortTwo, m_pWndTree );
	
	String strTvwBoardInputPortOneNTSC;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOneNTSC, strTvwBoardInputPortOneNTSC, m_pWndTree );
	
	String strTvwBoardInputPortTwoNTSC;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwoNTSC, strTvwBoardInputPortTwoNTSC, m_pWndTree );
	
	String strTvwBoardInputPortOnePer;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOnePer, strTvwBoardInputPortOnePer, m_pWndTree );
	
	String strTvwBoardInputPortTwoPer;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwoPer, strTvwBoardInputPortTwoPer, m_pWndTree );
	
	String strTvwBoardInputPortOnePerPloy;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOnePerPloy, strTvwBoardInputPortOnePerPloy, m_pWndTree );
	
	String strTvwBoardInputPortTwoPerPloy;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwoPerPloy, strTvwBoardInputPortTwoPerPloy, m_pWndTree );
	
	if ( !CheckPageTvwBoardMdlData() )
	{
		return false;
	}

	THduInfo tTHduInfo;
	tTHduInfo.m_byLayer = m_tHduCfgSel.m_byLayer;
	tTHduInfo.m_bySlot = m_tHduCfgSel.m_bySlot;
	tTHduInfo.m_tName.SetAlias(strTvwBoardModeName.c_str());
	tTHduInfo.m_atChanInfo[0].m_emOutPortType = StringToEmHduOutPort(strTvwBoardInputPortOne);
	tTHduInfo.m_atChanInfo[1].m_emOutPortType = StringToEmHduOutPort(strTvwBoardInputPortTwo);
	tTHduInfo.m_atChanInfo[0].m_emOutModeType = StringToEmHduOutMode(strTvwBoardInputPortOneNTSC);
	tTHduInfo.m_atChanInfo[1].m_emOutModeType = StringToEmHduOutMode(strTvwBoardInputPortTwoNTSC);
	tTHduInfo.m_atChanInfo[0].m_emZoomRate = StringToEmHduZoomRate(strTvwBoardInputPortOnePer);
	tTHduInfo.m_atChanInfo[1].m_emZoomRate = StringToEmHduZoomRate(strTvwBoardInputPortTwoPer);
	tTHduInfo.m_atChanInfo[0].m_emShowMode = StringToEmHduShowMode(strTvwBoardInputPortOnePerPloy);
	tTHduInfo.m_atChanInfo[1].m_emShowMode = StringToEmHduShowMode(strTvwBoardInputPortTwoPerPloy);

	u16 nRet = COMMONMGRIFPTR->TvwBoardModeModifyReq(tTHduInfo);;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "修改电视墙单板模式请求发送失败" );
		return false;
	}

	return true;
}

bool CTvwBoardCfgLogic::OnBtnTvwBoardModeSave( const IArgs & arg )
{ 
	if ( !SetTvwModeControlInfoToSevr() )
	{
		return false;
	}

	return true;
}

bool CTvwBoardCfgLogic::OnBtnTvwBoardModeDel( const IArgs & arg )
{ 
	TTPBrdPos tTPBrdPos;
	tTPBrdPos.m_byBrdLayer = m_tHduCfgSel.m_byLayer;
	tTPBrdPos.m_byBrdSlot = m_tHduCfgSel.m_bySlot;
	u16 nRet = COMMONMGRIFPTR->TvwBoardModeDeleteReq(tTPBrdPos);;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "清空电视墙单板模式请求发送失败" );
	}

	return true;
}

bool CTvwBoardCfgLogic::OnTvwBoardLstFloorItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_TvwBoardInfo * pDataTemp = dynamic_cast< const Data_TvwBoardInfo*>(pIData) )
        {  
			String strTvwBoardInputPortOneText;
			UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOne, strTvwBoardInputPortOneText, m_pWndTree );

			m_tHduCfgSel = pDataTemp->m_tTvwBoardInfo;

			IMPCOMMONLOGICRPTR->SerSevrIpAddr(m_tHduCfgSel.m_dwIP);
			IMPCOMMONLOGICRPTR->SetEMEqpType(em_hdu_mdl);

			CleanTvwMdlControlShow();

			DWORD dwIp = m_tHduCfgSel.m_dwIP;
			if ( 0 == dwIp )
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardDel, false, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModify, false, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardAdd, true, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardReboot, false, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardUpgrade, false, m_pWndTree );
				
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeDel, false, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeSave, false, m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardDel, true, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModify, true, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardAdd, false, m_pWndTree );

				SetSelMdlDataToCtrl();
			}

  			SetModePortOneDataToCtrl(FALSE);
  			SetModePortTwoDataToCtrl(FALSE);
			//设置其他层三个列表非选中项			

		}
	}
	return true;
}

void CTvwBoardCfgLogic::SetSelMdlDataToCtrl()
{
	if( m_tHduCfgSel.m_bBrdReg && m_tHduCfgSel.m_bServiceReg )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardReboot, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardUpgrade, true, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardReboot, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardUpgrade, false, m_pWndTree );
	}
	
	TTPName tMdlName = m_tHduCfgSel.m_tName;
	if ( tMdlName.IsEmpty() )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeDel, false, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeDel, true, m_pWndTree );
	}
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeSave, false, m_pWndTree );
	
	InitMdlComboList();
	
	String strModeName;
	strModeName = m_tHduCfgSel.m_tName.m_abyAlias;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtTvwBoardModeName, strModeName, m_pWndTree );
	
	if ( !strModeName.empty() )
	{
		String strTvwBoardInputPortOne;
		strTvwBoardInputPortOne = EmHduOutPortToString(m_tHduCfgSel.m_atChanInfo[0].m_emOutPortType);
		String strTvwBoardInputPortTwo;
		strTvwBoardInputPortTwo = EmHduOutPortToString(m_tHduCfgSel.m_atChanInfo[1].m_emOutPortType);
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOne, strTvwBoardInputPortOne, m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwo, strTvwBoardInputPortTwo, m_pWndTree );
		
		String strTvwBoardInputPortOneNTSC;
		strTvwBoardInputPortOneNTSC = EmHduOutModeToString(m_tHduCfgSel.m_atChanInfo[0].m_emOutModeType);
		String strTvwBoardInputPortTwoNTSC;
		strTvwBoardInputPortTwoNTSC = EmHduOutModeToString(m_tHduCfgSel.m_atChanInfo[1].m_emOutModeType);
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOneNTSC, strTvwBoardInputPortOneNTSC, m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoNTSC, strTvwBoardInputPortTwoNTSC, m_pWndTree );
		
		String strTvwBoardInputPortOnePer;
		strTvwBoardInputPortOnePer = EmHduZoomRateToString(m_tHduCfgSel.m_atChanInfo[0].m_emZoomRate);
		String strTvwBoardInputPortTwoPer;
		strTvwBoardInputPortTwoPer = EmHduZoomRateToString(m_tHduCfgSel.m_atChanInfo[1].m_emZoomRate);
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePer, strTvwBoardInputPortOnePer, m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPer, strTvwBoardInputPortTwoPer, m_pWndTree );
		
		String strTvwBoardInputPortOnePerPloy;
		strTvwBoardInputPortOnePerPloy = EmHduShowModeToString(m_tHduCfgSel.m_atChanInfo[0].m_emShowMode);
		String strTvwBoardInputPortTwoPerPloy;
		strTvwBoardInputPortTwoPerPloy = EmHduShowModeToString(m_tHduCfgSel.m_atChanInfo[1].m_emShowMode);
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePerPloy, strTvwBoardInputPortOnePerPloy, m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPerPloy, strTvwBoardInputPortTwoPerPloy, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOne, "DVI", m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwo, "DVI", m_pWndTree );
		
		UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortOneNTSC, m_vecHduOutModeCommon, m_pWndTree );
		UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortTwoNTSC, m_vecHduOutModeCommon, m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOneNTSC, "1080P_60fps", m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoNTSC, "1080P_60fps", m_pWndTree );
		
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePer, "16:9", m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPer, "16:9", m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePerPloy, "不等比缩放", m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPerPloy, "不等比缩放", m_pWndTree );
	}
}

HRESULT CTvwBoardCfgLogic::OnRefreshTvwBoardInfoNotify( WPARAM wparam, LPARAM lparam)
{
	UpdateTvwBoardLayarList(m_nCurFloorNo);

	return S_OK;
}

HRESULT CTvwBoardCfgLogic::OnOptTvwBoardNotify( WPARAM wparam, LPARAM lparam)
{
	if( m_pWndTree != NULL )
    {
		TTPBrdPos tTPBrdPos = *reinterpret_cast<TTPBrdPos*>(wparam);

		s32 nLayer = tTPBrdPos.m_byBrdLayer;

		m_tHduCfgSel.m_byLayer = nLayer;
		m_tHduCfgSel.m_bySlot = tTPBrdPos.m_byBrdSlot;
		m_tHduCfgSel.m_dwIP = tTPBrdPos.m_dwBrdIP;

		IMPCOMMONLOGICRPTR->SerSevrIpAddr(m_tHduCfgSel.m_dwIP);
		IMPCOMMONLOGICRPTR->SetEMEqpType(em_hdu_mdl);

		CleanTvwMdlControlShow();

		UpdateTvwBoardLayarList(nLayer);
    }

	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardDel, true, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModify, true, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardAdd, false, m_pWndTree );

	if( m_tHduCfgSel.m_bBrdReg && m_tHduCfgSel.m_bServiceReg )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardReboot, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardUpgrade, true, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardReboot, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardUpgrade, false, m_pWndTree );
	}

	InitMdlComboList();

	//模式类别-------------------------------------------
	TTPName tMdlName = m_tHduCfgSel.m_tName;
	if ( tMdlName.IsEmpty() )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeDel, false, m_pWndTree );

		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOne, "DVI", m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwo, "DVI", m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePer, "16:9", m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPer, "16:9", m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePerPloy, "不等比缩放", m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPerPloy, "不等比缩放", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeDel, true, m_pWndTree );

		SetSelMdlDataToCtrl();

	}
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeSave, false, m_pWndTree );

	String strTvwBoardInputPortOneText;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOne, strTvwBoardInputPortOneText, m_pWndTree );

	SetMdlDataChange(FALSE);

	SetModePortOneDataToCtrl(FALSE);
	SetModePortTwoDataToCtrl(FALSE);

	return S_OK;
}

void CTvwBoardCfgLogic::InitMdlComboList()
{
	InitHduOutPortValue();	
	InitHduOutModeValue();	
	InitHduZoomRateValue();	
	InitHduShowModeValue();
}

HRESULT CTvwBoardCfgLogic::OnOptTvwBoardRsp( WPARAM wparam, LPARAM lparam)
{
	TTvwBrdOptRet tRet = *reinterpret_cast<TTvwBrdOptRet*>( lparam );
	
	String strError;
	switch( tRet.emBrdOptType )
	{
	case em_Add_Ret:
		{
			strError = "添加电视墙单板失败：";
		}
		break;
	case em_Modify_Ret:
		{
			strError = "修改电视墙单板失败：";
		}
		break;
	case em_Del_Ret:
		{
			strError = "删除电视墙单板失败：";
		}
		break;
	}

	switch( tRet.emTvwModifyHduRet )
	{
	case em_hdu_modify_success:
		{
			return S_OK;
		}
		break;
	case em_hdu_brd_no_cfg:
		{
			strError += "无效的索引";
		}
		break;
	case em_hdu_invalid_index:
		{
			strError += "板子未配置";
		}
		break;
	}

	if ( !strError.empty() )
	{
		MESSAGEWND(strError.c_str());
	}

	return S_OK;
}

HRESULT CTvwBoardCfgLogic::OnDelTvwBoardNotify( WPARAM wparam, LPARAM lparam)
{
	if( m_pWndTree != NULL )
    {
		TTPBrdPos tTPBrdPos = *reinterpret_cast<TTPBrdPos*>(wparam);
		s32 nLayer = tTPBrdPos.m_byBrdLayer;
		s32 nSlot = tTPBrdPos.m_byBrdSlot;

		//删除成功清空选中电视墙板子数据的非层、槽
		m_tHduCfgSel.Clear();
		m_tHduCfgSel.m_byLayer = nLayer;
		m_tHduCfgSel.m_bySlot = nSlot;

		IMPCOMMONLOGICRPTR->SerSevrIpAddr(m_tHduCfgSel.m_dwIP);
		IMPCOMMONLOGICRPTR->SetEMEqpType(em_hdu_mdl);

		UpdateTvwBoardLayarList(nLayer);

		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardDel, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModify, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardAdd, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardReboot, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardUpgrade, false, m_pWndTree );
		
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeDel, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeSave, false, m_pWndTree );
		
		//模式类别-------------------------------------------	
		CleanTvwMdlControlShow();
    }

	SetMdlDataChange(FALSE);

	return S_OK;
}

HRESULT CTvwBoardCfgLogic::OnOptTvwBoardModeNotify( WPARAM wparam, LPARAM lparam)
{
	if( m_pWndTree != NULL )
    {
		THduInfo tHduInfo = *reinterpret_cast<THduInfo*>(wparam);
		
		s32 nLayer = tHduInfo.m_byLayer;
		
		m_tHduCfgSel.m_tName.SetAlias(tHduInfo.m_tName.m_abyAlias);
		m_tHduCfgSel.m_atChanInfo[0] = tHduInfo.m_atChanInfo[0];
		m_tHduCfgSel.m_atChanInfo[1] = tHduInfo.m_atChanInfo[1];
			
		UpdateTvwBoardLayarList(nLayer);

		SetTvwModeDataToControl(m_tHduCfgSel);    //设置电视墙模式控件数据

		IMPCOMMONLOGICRPTR->SerSevrIpAddr(m_tHduCfgSel.m_dwIP);
		IMPCOMMONLOGICRPTR->SetEMEqpType(em_hdu_mdl);
    }

	SetMdlDataChange(FALSE);

	UpdateTvwBoardLayarList(m_nCurFloorNo);

	return S_OK;
}

BOOL CTvwBoardCfgLogic::SetTvwModeDataToControl(const THduCfg& tHduCfgSel)
{
	//模式类别-------------------------------------------
	TTPName tMdlName = tHduCfgSel.m_tName;
	if ( tMdlName.IsEmpty() )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeDel, false, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeDel, true, m_pWndTree );
	}
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeSave, false, m_pWndTree );
	
	String strModeName;
	strModeName = tHduCfgSel.m_tName.m_abyAlias;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtTvwBoardModeName, strModeName, m_pWndTree );
	
	String strTvwBoardInputPortOne;
	strTvwBoardInputPortOne = EmHduOutPortToString(tHduCfgSel.m_atChanInfo[0].m_emOutPortType);
	String strTvwBoardInputPortTwo;
	strTvwBoardInputPortTwo = EmHduOutPortToString(tHduCfgSel.m_atChanInfo[1].m_emOutPortType);
	UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOne, strTvwBoardInputPortOne, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwo, strTvwBoardInputPortTwo, m_pWndTree );
	
	String strTvwBoardInputPortOneNTSC;
	strTvwBoardInputPortOneNTSC = EmHduOutModeToString(tHduCfgSel.m_atChanInfo[0].m_emOutModeType);
	String strTvwBoardInputPortTwoNTSC;
	strTvwBoardInputPortTwoNTSC = EmHduOutModeToString(tHduCfgSel.m_atChanInfo[1].m_emOutModeType);
	UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOneNTSC, strTvwBoardInputPortOneNTSC, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoNTSC, strTvwBoardInputPortTwoNTSC, m_pWndTree );
	
	String strTvwBoardInputPortOnePer;
	strTvwBoardInputPortOnePer = EmHduZoomRateToString(tHduCfgSel.m_atChanInfo[0].m_emZoomRate);
	String strTvwBoardInputPortTwoPer;
	strTvwBoardInputPortTwoPer = EmHduZoomRateToString(tHduCfgSel.m_atChanInfo[1].m_emZoomRate);
	UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePer, strTvwBoardInputPortOnePer, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPer, strTvwBoardInputPortTwoPer, m_pWndTree );
	
	String strTvwBoardInputPortOnePerPloy;
	strTvwBoardInputPortOnePerPloy = EmHduShowModeToString(tHduCfgSel.m_atChanInfo[0].m_emShowMode);
	String strTvwBoardInputPortTwoPerPloy;
	strTvwBoardInputPortTwoPerPloy = EmHduShowModeToString(tHduCfgSel.m_atChanInfo[1].m_emShowMode);
	UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePerPloy, strTvwBoardInputPortOnePerPloy, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPerPloy, strTvwBoardInputPortTwoPerPloy, m_pWndTree );

	return TRUE;
}

HRESULT CTvwBoardCfgLogic::OnDelTvwBoardModeNotify( WPARAM wparam, LPARAM lparam)
{
	if( m_pWndTree != NULL )
    {
		TTPBrdPos tTPBrdPos = *reinterpret_cast<TTPBrdPos*>(wparam);
		
		s32 nLayer = tTPBrdPos.m_byBrdLayer;

		m_tHduCfgSel.m_tName.SetAlias("");
		m_tHduCfgSel.m_atChanInfo[0].Clear();
		m_tHduCfgSel.m_atChanInfo[1].Clear();

		SetTvwModeDataToControl(m_tHduCfgSel);    //清空显示电视墙模式控件数据

		IMPCOMMONLOGICRPTR->SerSevrIpAddr(m_tHduCfgSel.m_dwIP);
		IMPCOMMONLOGICRPTR->SetEMEqpType(em_hdu_mdl);

		UpdateTvwBoardLayarList(nLayer);

		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeDel, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeSave, false, m_pWndTree );
	}

	return S_OK;
}

HRESULT CTvwBoardCfgLogic::OnOptTvwBoardModeRsp( WPARAM wparam, LPARAM lparam)
{
	TTvwBrdOptRet tRet = *reinterpret_cast<TTvwBrdOptRet*>( lparam );
	
	String strError;
	switch( tRet.emBrdOptType )
	{
	case em_Add_Ret:
		{
			strError = "电视墙单板模式保存失败：";
		}
		break;
	case em_Modify_Ret:
		{
			strError = "电视墙单板模式保存失败：";
		}
		break;
	case em_Del_Ret:
		{
			strError = "删除电视墙单板模式失败：";
		}
		break;
	}
	
	switch( tRet.emTvwModifyHduRet )
	{
	case em_hdu_modify_success:
		{
			return S_OK;
		}
		break;
	case em_hdu_brd_no_cfg:
		{
			strError += "无效的索引";
		}
		break;
	case em_hdu_invalid_index:
		{
			strError += "板子未配置";
		}
		break;
	}
	
	if ( !strError.empty() )
	{
		MESSAGEWND(strError.c_str());
	}

	return S_OK;
}

void CTvwBoardCfgLogic::CleanTvwMdlControlShow()
{
	UIFACTORYMGR_PTR->SetCaption( m_strEdtTvwBoardModeName, "", m_pWndTree );

	UIFACTORYMGR_PTR->CleanComboListData( m_strComboxTvwBoardInputPortOne, m_pWndTree );	
	UIFACTORYMGR_PTR->CleanComboListData( m_strComboxTvwBoardInputPortTwo, m_pWndTree );
	UIFACTORYMGR_PTR->CleanComboListData( m_strComboxTvwBoardInputPortOneNTSC, m_pWndTree );
	UIFACTORYMGR_PTR->CleanComboListData( m_strComboxTvwBoardInputPortTwoNTSC, m_pWndTree );
	UIFACTORYMGR_PTR->CleanComboListData( m_strComboxTvwBoardInputPortOnePer, m_pWndTree );
	UIFACTORYMGR_PTR->CleanComboListData( m_strComboxTvwBoardInputPortTwoPer, m_pWndTree );
	UIFACTORYMGR_PTR->CleanComboListData( m_strComboxTvwBoardInputPortOnePerPloy, m_pWndTree );
	UIFACTORYMGR_PTR->CleanComboListData( m_strComboxTvwBoardInputPortTwoPerPloy, m_pWndTree );

	DWORD dwIp = m_tHduCfgSel.m_dwIP;
	if ( 0 == dwIp )
	{	
		UIFACTORYMGR_PTR->EnableWindow( m_strEdtTvwBoardModeName, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortOne, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortTwo, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortOneNTSC, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortTwoNTSC, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortOnePer, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortTwoPer, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortOnePerPloy, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortTwoPerPloy, false, m_pWndTree );

		SetMdlDataChange(FALSE);
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strEdtTvwBoardModeName, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortOne, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortTwo, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortOneNTSC, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortTwoNTSC, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortOnePer, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortTwoPer, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortOnePerPloy, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboxTvwBoardInputPortTwoPerPloy, true, m_pWndTree );
	}
}

void CTvwBoardCfgLogic::InitHduOutPortValue()
{
	m_vecHduOutPort.clear();
	m_vecHduOutPort.push_back("YPbPr");
	m_vecHduOutPort.push_back("VGA");
	m_vecHduOutPort.push_back("DVI");
	m_vecHduOutPort.push_back("HDMI");

	UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortOne, m_vecHduOutPort, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortTwo, m_vecHduOutPort, m_pWndTree );
}

void CTvwBoardCfgLogic::InitHduOutModeValue()
{
	m_vecHduOutModeCommon.clear();
	//接口类型为DVI（默认）/HDMI/YPbPr
	m_vecHduOutModeCommon.push_back("1080P_24fps");
	m_vecHduOutModeCommon.push_back("1080P_25fps");
	m_vecHduOutModeCommon.push_back("1080P_29.97fps");
	m_vecHduOutModeCommon.push_back("1080P_30fps");
	m_vecHduOutModeCommon.push_back("1080P_50fps");
	m_vecHduOutModeCommon.push_back("1080P_59.94fps");
	m_vecHduOutModeCommon.push_back("1080P_60fps");

	m_vecHduOutModeCommon.push_back("1080i_50Hz");
	m_vecHduOutModeCommon.push_back("1080i_60Hz");

	m_vecHduOutModeCommon.push_back("720P_50fps");
	m_vecHduOutModeCommon.push_back("720P_60fps");

	//接口类型为VGA
	m_vecHduOutModeVGA.clear();
	m_vecHduOutModeVGA.push_back("VGA_60Hz");
	m_vecHduOutModeVGA.push_back("VGA_75Hz");

	m_vecHduOutModeVGA.push_back("SVGA_60Hz");
	m_vecHduOutModeVGA.push_back("SVGA_75Hz");

	m_vecHduOutModeVGA.push_back("XGA_60Hz");
	m_vecHduOutModeVGA.push_back("XGA_75Hz");

	m_vecHduOutModeVGA.push_back("WXGA(1280*800)_60Hz");
	m_vecHduOutModeVGA.push_back("WXGA(1280*800)_75Hz");
	m_vecHduOutModeVGA.push_back("WXGA(1280*768)_60Hz");

	m_vecHduOutModeVGA.push_back("WSXGA_60Hz");
	m_vecHduOutModeVGA.push_back("SXGA_60Hz");

	m_vecHduOutModeVGA.push_back("WSXGA+_60Hz");
	m_vecHduOutModeVGA.push_back("UXGA_60Hz");

	std::vector<CString> vecHduOutMode;   
	vecHduOutMode.insert(vecHduOutMode.end(), m_vecHduOutModeCommon.begin(), m_vecHduOutModeCommon.end());   
	vecHduOutMode.insert(vecHduOutMode.end(), m_vecHduOutModeVGA.begin(), m_vecHduOutModeVGA.end());   

	UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortOneNTSC, vecHduOutMode, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortTwoNTSC, vecHduOutMode, m_pWndTree );
}

void CTvwBoardCfgLogic::InitHduZoomRateValue()
{
	m_vecHduZoomRate.clear();
	m_vecHduZoomRate.push_back("4:3");
	m_vecHduZoomRate.push_back("16:9");

	UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortOnePer, m_vecHduZoomRate, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortTwoPer, m_vecHduZoomRate, m_pWndTree );
}

void CTvwBoardCfgLogic::InitHduShowModeValue()
{
	m_vecHduShowMode.clear();
	m_vecHduShowMode.push_back("不等比缩放");
	m_vecHduShowMode.push_back("裁边等比缩放");
	m_vecHduShowMode.push_back("加黑边等比缩放");

	UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortOnePerPloy, m_vecHduShowMode, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortTwoPerPloy, m_vecHduShowMode, m_pWndTree );
// 	UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePerPloy, "不等比缩放", m_pWndTree );
// 	UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPerPloy, "不等比缩放", m_pWndTree );
}

String CTvwBoardCfgLogic::EmHduOutPortToString(EmHduOutPort emValue)
{
	String strValue;  
	switch(emValue)
	{
	case em_hdu_outport_YPbPr:
		{
			strValue = "YPbPr";
		}
		break;
	case em_hdu_outport_VGA:
		{
			strValue = "VGA";
		}
		break;
	case em_hdu_outport_DVI:
		{
			strValue = "DVI";
		}
		break;
	case em_hdu_outport_HDMI:
		{
			strValue = "HDMI";
		}
		break;
	default:
		{
			strValue = "";
		}
		break;
	}

	return strValue;
}

EmHduOutPort CTvwBoardCfgLogic::StringToEmHduOutPort(String strValue)
{
	EmHduOutPort emValue;
	if ( "YPbPr" == strValue )
	{
		emValue = em_hdu_outport_YPbPr;
	}
	else if ( "VGA" == strValue )
	{
		emValue = em_hdu_outport_VGA;
	}
	else if ( "DVI" == strValue )
	{
		emValue = em_hdu_outport_DVI;
	}
	else if ( "HDMI" == strValue )
	{
		emValue = em_hdu_outport_HDMI;
	}
	else
	{
		emValue = em_hdu_outport_unknow;
	}

	return emValue;
}

String CTvwBoardCfgLogic::EmHduOutModeToString(EmHduOutMode emValue)
{
	String strValue;
	switch( emValue)
	{
	//1080p
	case em_hdu_outmode_YPbPr_1080P_24fps:
		{
			strValue = "1080P_24fps";
		}
		break;
	case em_hdu_outmode_YPbPr_1080P_25fps:
		{
			strValue = "1080P_25fps";
		}
		break;
	case em_hdu_outmode_YPbPr_1080P_30fps:
		{
			strValue = "1080P_30fps";
		}
		break;
	case em_hdu_outmode_YPbPr_1080P_50fps:
		{
			strValue = "1080P_50fps";
		}
		break;
	case em_hdu_outmode_YPbPr_1080P_60fps:
		{
			strValue = "1080P_60fps";
		}
		break;
	case em_hdu_outmode_YPbPr_1080P_29970HZ:
		{
			strValue = "1080P_29.97fps";
		}
		break;
	case em_hdu_outmode_YPbPr_1080P_59940HZ:
		{
			strValue = "1080P_59.94fps";
		}
		break;
	//1080i
	case em_hdu_outmode_YPbPr_1080i_50HZ:
		{
			strValue = "1080i_50Hz";
		}
		break;
	case em_hdu_outmode_YPbPr_1080i_60HZ:
		{
			strValue = "1080i_60Hz";
		}
		break;
	//720p
	case em_hdu_outmode_YPbPr_720P_50fps:
		{
			strValue = "720P_50fps";
		}
		break;
	case em_hdu_outmode_YPbPr_720P_60fps:
		{
			strValue = "720P_60fps";
		}
		break;
	//VGA
	case em_hdu_outmode_VGA_VGA_60HZ:
		{
			strValue = "VGA_60Hz";
		}
		break;
	case em_hdu_outmode_VGA_VGA_75HZ:
		{
			strValue = "VGA_75Hz";
		}
		break;
	//SVGA
	case em_hdu_outmode_VGA_SVGA_60HZ:
		{
			strValue = "SVGA_60Hz";
		}
		break;
	case em_hdu_outmode_VGA_SVGA_75HZ:
		{
			strValue = "SVGA_75Hz";
		}
		break;
	//XGA
	case em_hdu_outmode_VGA_XGA_60HZ:
		{
			strValue = "XGA_60Hz";
		}
		break;
	case em_hdu_outmode_VGA_XGA_75HZ:
		{
			strValue = "XGA_75Hz";
		}
		break;
	//WXGA(1280*800)
	case em_hdu_outmode_VGA_WXGA_1280_800_60HZ:
		{
			strValue = "WXGA(1280*800)_60Hz";
		}
		break;
	case em_hdu_outmode_WXGA_1280_800_75HZ:
		{
			strValue = "WXGA(1280*800)_75Hz";
		}
		break;
		//WXGA(1280*768)
	case em_hdu_outmode_VGA_WXGA_1280_768_60HZ:
		{
			strValue = "WXGA(1280*768)_60Hz";
		}
		break;
		//WSXGA(1440*900)
	case em_hdu_outmode_VGA_WSXGA_60HZ:
		{
			strValue = "WSXGA_60Hz";
		}
		break;
		//SXGA
	case em_hdu_outmode_VGA_SXGA_60HZ:
		{
			strValue = "SXGA_60Hz";
		}
		break;
		//WSXGA+（1680x1050）@60Hz     未找到
	case em_hdu_outmode_VGA_SXGAPlus_60HZ:
		{
			strValue = "WSXGA+_60Hz";
		}
		break;
		//UXGA
	case em_hdu_outmode_VGA_UXGA_60HZ:
		{
			strValue = "UXGA_60Hz";
		}
		break;
	default:
		{
			strValue = "";
		}
		break;
	}

	return strValue;
}

EmHduOutMode CTvwBoardCfgLogic::StringToEmHduOutMode(String strValue)
{
	EmHduOutMode emValue;
	if ( "1080P_24fps" == strValue )
	{
		emValue = em_hdu_outmode_YPbPr_1080P_24fps;
	}
	else if ( "1080P_25fps" == strValue )
	{
		emValue = em_hdu_outmode_YPbPr_1080P_25fps;
	}
	else if ( "1080P_30fps" == strValue )
	{
		emValue = em_hdu_outmode_YPbPr_1080P_30fps;
	}
	else if ( "1080P_50fps" == strValue )
	{
		emValue = em_hdu_outmode_YPbPr_1080P_50fps;
	}
	else if ( "1080P_60fps" == strValue )
	{
		emValue = em_hdu_outmode_YPbPr_1080P_60fps;
	}
	else if ( "1080P_29.97fps" == strValue )
	{
		emValue = em_hdu_outmode_YPbPr_1080P_29970HZ;
	}
	else if ( "1080P_59.94fps" == strValue )
	{
		emValue = em_hdu_outmode_YPbPr_1080P_59940HZ;
	}
	else if ( "1080i_50Hz" == strValue )
	{
		emValue = em_hdu_outmode_YPbPr_1080i_50HZ;
	}
	else if ( "1080i_60Hz" == strValue )
	{
		emValue = em_hdu_outmode_YPbPr_1080i_60HZ;
	}
	else if ( "720P_50fps" == strValue )
	{
		emValue = em_hdu_outmode_YPbPr_720P_50fps;
	}
	else if ( "720P_60fps" == strValue )
	{
		emValue = em_hdu_outmode_YPbPr_720P_60fps;
	}
	else if ( "VGA_60Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_VGA_60HZ;
	}
	else if ( "VGA_75Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_VGA_75HZ;
	}
	else if ( "SVGA_60Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_SVGA_60HZ;
	}
	else if ( "SVGA_75Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_SVGA_75HZ;
	}
	else if ( "XGA_60Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_XGA_60HZ;
	}
	else if ( "XGA_75Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_XGA_75HZ;
	}
	else if ( "WXGA(1280*800)_60Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_WXGA_1280_800_60HZ;
	}
	else if ( "WXGA(1280*800)_75Hz" == strValue )
	{
		emValue = em_hdu_outmode_WXGA_1280_800_75HZ;
	}
	else if ( "WXGA(1280*768)_60Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_WXGA_1280_768_60HZ;
	}
	else if ( "WSXGA_60Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_WSXGA_60HZ;
	}
	else if ( "SXGA_60Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_SXGA_60HZ;
	}
	else if ( "WSXGA+_60Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_SXGAPlus_60HZ;
	}
	else if ( "UXGA_60Hz" == strValue )
	{
		emValue = em_hdu_outmode_VGA_UXGA_60HZ;
	}
	else
	{
		emValue = em_hdu_outmode_unknow;
	}

	return emValue;
}

String CTvwBoardCfgLogic::EmHduZoomRateToString(EmHduZoomRate emValue)
{
	String strValue;
	switch( emValue)
	{
	case em_hdu_zoomrate_4_3:
		{
			strValue = "4:3";
		}
		break;
	case em_hdu_zoomrate_16_9:
		{
			strValue = "16:9";
		}
		break;
	default:
		{
			strValue = "";
		}
		break;
	}

	return strValue;
}

EmHduZoomRate CTvwBoardCfgLogic::StringToEmHduZoomRate(String strValue)
{
	EmHduZoomRate emValue;
	if ( "4:3" == strValue )
	{
		emValue = em_hdu_zoomrate_4_3;
	}
	else if ( "16:9" == strValue )
	{
		emValue = em_hdu_zoomrate_16_9;
	}
	else
	{
		emValue = em_hdu_zoomrate_unknow;
	}

	return emValue;
}

String CTvwBoardCfgLogic::EmHduShowModeToString(EmHduShowMode emValue)
{
	String strValue;
	switch( emValue)
	{
	case em_hdu_showmode_NONGEOMETRIC:
		{
			strValue = "不等比缩放";
		}
		break;
	case em_hdu_showmode_CUTEDGEGEOME:
		{
			strValue = "裁边等比缩放";
		}
		break;
	case em_hdu_showmode_BLACKEDGEGEOME:
		{
			strValue = "加黑边等比缩放";
		}
		break;
	default:
		{
			strValue = "";
		}
		break;
	}

	return strValue;
}

EmHduShowMode CTvwBoardCfgLogic::StringToEmHduShowMode(String strValue)
{
	EmHduShowMode emValue;
	if ( "不等比缩放" == strValue )
	{
		emValue = em_hdu_showmode_NONGEOMETRIC;
	}
	else if ( "裁边等比缩放" == strValue )
	{
		emValue = em_hdu_showmode_CUTEDGEGEOME;
	}
	else if ( "加黑边等比缩放" == strValue )
	{
		emValue = em_hdu_showmode_BLACKEDGEGEOME;
	}
	else
	{
		emValue = em_hdu_showmode_unknow;
	}

	return emValue;
}

BOOL CTvwBoardCfgLogic::CheckPageDataChangeToSave()
{	
	BOOL bShow = UIFACTORYMGR_PTR->IsVisible( g_stcStrTvwBoardCfgDlg.c_str()/*, m_pWndTree*/ );
	if ( !bShow )
	{
		return TRUE;
	}

	if ( GetMdlDataChange() )
	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "单板模块信息有改动，是否保存？" );
		if ( MSGBOX_OK == nMsgBoxRet )
		{
			IArgs arg("");
			//保存电视墙单板模式
			if ( !OnBtnTvwBoardModeSave(arg) )
			{
				return FALSE;
			}
		}
		else    //取消则恢复原始模式信息
		{		
			SetTvwModeDataToControl(m_tHduCfgSel);

			//取消操作   如果是非空单板   且没有配置    则重新设置默认数据
			String strModeName;
			strModeName = m_tHduCfgSel.m_tName.m_abyAlias;
			if ( strModeName.empty() && 0 != m_tHduCfgSel.m_dwIP )
			{
				UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOne, "DVI", m_pWndTree );
				UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwo, "DVI", m_pWndTree );

				UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortOneNTSC, m_vecHduOutModeCommon, m_pWndTree );
				UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortTwoNTSC, m_vecHduOutModeCommon, m_pWndTree );
				UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOneNTSC, "1080P_60fps", m_pWndTree );
				UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoNTSC, "1080P_60fps", m_pWndTree );

				UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePer, "16:9", m_pWndTree );
				UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPer, "16:9", m_pWndTree );
				UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePerPloy, "不等比缩放", m_pWndTree );
				UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPerPloy, "不等比缩放", m_pWndTree );
			}
		}
	}

	return TRUE;
}

bool CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortOneChange( const IArgs & arg )
{
	//SetModePortOneDataToCtrl();


	return true;
}

bool CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortOneClick( const IArgs & arg )
{
	SetModePortOneDataToCtrl();	
	CompareDataChange();

	return true;
}

void CTvwBoardCfgLogic::SetModePortOneDataToCtrl(BOOL bIsEditDataChange)
{
	//动态通过接口设置支持制式类型
	DWORD dwIp = m_tHduCfgSel.m_dwIP;
	if ( 0 == dwIp )						//电视墙板子未知   禁止输入  清空模式名
	{
		UIFACTORYMGR_PTR->CleanComboListData( m_strComboxTvwBoardInputPortOne, m_pWndTree );
	}
	else
	{
		String strTvwBoardInputPortOne;
		UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOne, strTvwBoardInputPortOne, m_pWndTree );
		if ( !strTvwBoardInputPortOne.empty() )
		{
			if ( strTvwBoardInputPortOne == "VGA" )
			{
				UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortOneNTSC, m_vecHduOutModeVGA, m_pWndTree );
				String strTvwBoardInputPortOneNTSC;
				strTvwBoardInputPortOneNTSC = EmHduOutModeToString(m_tHduCfgSel.m_atChanInfo[0].m_emOutModeType);
				if ( bIsEditDataChange || strTvwBoardInputPortOneNTSC.empty() )
				{
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOneNTSC, "SXGA_60Hz", m_pWndTree );
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePer, "4:3", m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOneNTSC, strTvwBoardInputPortOneNTSC, m_pWndTree );
				}
			}
			else
			{
				UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortOneNTSC, m_vecHduOutModeCommon, m_pWndTree );
				String strTvwBoardInputPortOneNTSC;
				strTvwBoardInputPortOneNTSC = EmHduOutModeToString(m_tHduCfgSel.m_atChanInfo[0].m_emOutModeType);
				if ( bIsEditDataChange || strTvwBoardInputPortOneNTSC.empty() )
				{
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOneNTSC, "1080P_60fps", m_pWndTree );
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOnePer, "16:9", m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortOneNTSC, strTvwBoardInputPortOneNTSC, m_pWndTree );
				}
			}
		}
	}
}

void CTvwBoardCfgLogic::SetModePortTwoDataToCtrl(BOOL bIsEditDataChange)
{
	//动态通过接口设置支持制式类型
	DWORD dwIp = m_tHduCfgSel.m_dwIP;
	if ( 0 == dwIp )						//电视墙板子未知   禁止输入  清空模式名
	{
		UIFACTORYMGR_PTR->CleanComboListData( m_strComboxTvwBoardInputPortTwo, m_pWndTree );
	}
	else
	{
		String strTvwBoardInputPortTwo;
		UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwo, strTvwBoardInputPortTwo, m_pWndTree );
		if ( !strTvwBoardInputPortTwo.empty() )
		{
			if ( strTvwBoardInputPortTwo == "VGA" )
			{
				UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortTwoNTSC, m_vecHduOutModeVGA, m_pWndTree );
				String strTvwBoardInputPortTwoNTSC;
				strTvwBoardInputPortTwoNTSC = EmHduOutModeToString(m_tHduCfgSel.m_atChanInfo[1].m_emOutModeType);
				if ( bIsEditDataChange || strTvwBoardInputPortTwoNTSC.empty()  )
				{
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoNTSC, "SXGA_60Hz", m_pWndTree );
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPer, "4:3", m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoNTSC, strTvwBoardInputPortTwoNTSC, m_pWndTree );
				}
			}
			else
			{
				UIFACTORYMGR_PTR->SetComboListData( m_strComboxTvwBoardInputPortTwoNTSC, m_vecHduOutModeCommon, m_pWndTree );
				String strTvwBoardInputPortTwoNTSC;
				strTvwBoardInputPortTwoNTSC = EmHduOutModeToString(m_tHduCfgSel.m_atChanInfo[1].m_emOutModeType);
				if ( bIsEditDataChange || strTvwBoardInputPortTwoNTSC.empty()  )
				{
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoNTSC, "1080P_60fps", m_pWndTree );
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoPer, "16:9", m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->SetComboText( m_strComboxTvwBoardInputPortTwoNTSC, strTvwBoardInputPortTwoNTSC, m_pWndTree );
				}
			}
		}
	}
}


bool CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortTwoChange( const IArgs & arg )
{
	//SetModePortTwoDataToCtrl();
	
	return true;
}

bool CTvwBoardCfgLogic::OnTvwBoardMdlEditInputPortTwoClick( const IArgs & arg )
{
	SetModePortTwoDataToCtrl();
	CompareDataChange();

	return true;
}

bool CTvwBoardCfgLogic::OnClickTvwBoardLstBlack( const IArgs & arg )
{
	ResetTvwBoardPageControl();

	return true;
}

bool CTvwBoardCfgLogic::OnTvwBoardMdlEditInputNTFSOneChange( const IArgs & arg )
{
	CompareDataChange();

	return true;
}

bool CTvwBoardCfgLogic::OnTvwBoardMdlEditInputNTFSTwoChange( const IArgs & arg )
{
	CompareDataChange();
	
	return true;
}

void CTvwBoardCfgLogic::CompareDataChange()
{
	//电视墙单板原始模式数据-------------------------------------------
	DWORD dwIp = m_tHduCfgSel.m_dwIP;
	if ( 0 == dwIp )						//电视墙板子未知   禁止输入  清空模式名
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtTvwBoardModeName, "", m_pWndTree );
		
		return;
	}
	
	String strTvwBoardOrgModeName;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTvwBoardModeName, strTvwBoardOrgModeName, m_pWndTree );   
	
	String strTvwBoardOrgInputPortOne;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOne, strTvwBoardOrgInputPortOne, m_pWndTree );
	
	String strTvwBoardOrgInputPortTwo;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwo, strTvwBoardOrgInputPortTwo, m_pWndTree );
	
	String strTvwBoardOrgInputPortOneNTSC;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOneNTSC, strTvwBoardOrgInputPortOneNTSC, m_pWndTree );
	
	String strTvwBoardOrgInputPortTwoNTSC;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwoNTSC, strTvwBoardOrgInputPortTwoNTSC, m_pWndTree );
	
	String strTvwBoardOrgInputPortOnePer;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOnePer, strTvwBoardOrgInputPortOnePer, m_pWndTree );
	
	String strTvwBoardOrgInputPortTwoPer;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwoPer, strTvwBoardOrgInputPortTwoPer, m_pWndTree );
	
	String strTvwBoardOrgInputPortOnePerPloy;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOnePerPloy, strTvwBoardOrgInputPortOnePerPloy, m_pWndTree );
	
	String strTvwBoardOrgInputPortTwoPerPloy;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwoPerPloy, strTvwBoardOrgInputPortTwoPerPloy, m_pWndTree );
	
	
	//当前选中项模式数据-------------------------------------------
	String strTvwBoardModeName;
	strTvwBoardModeName = m_tHduCfgSel.m_tName.m_abyAlias;
	
	String strTvwBoardInputPortOne;
	strTvwBoardInputPortOne = EmHduOutPortToString(m_tHduCfgSel.m_atChanInfo[0].m_emOutPortType);
	String strTvwBoardInputPortTwo;
	strTvwBoardInputPortTwo = EmHduOutPortToString(m_tHduCfgSel.m_atChanInfo[1].m_emOutPortType);
	
	String strTvwBoardInputPortOneNTSC;
	strTvwBoardInputPortOneNTSC = EmHduOutModeToString(m_tHduCfgSel.m_atChanInfo[0].m_emOutModeType);
	String strTvwBoardInputPortTwoNTSC;
	strTvwBoardInputPortTwoNTSC = EmHduOutModeToString(m_tHduCfgSel.m_atChanInfo[1].m_emOutModeType);
	
	String strTvwBoardInputPortOnePer;
	strTvwBoardInputPortOnePer = EmHduZoomRateToString(m_tHduCfgSel.m_atChanInfo[0].m_emZoomRate);
	String strTvwBoardInputPortTwoPer;
	strTvwBoardInputPortTwoPer = EmHduZoomRateToString(m_tHduCfgSel.m_atChanInfo[1].m_emZoomRate);
	
	String strTvwBoardInputPortOnePerPloy;
	strTvwBoardInputPortOnePerPloy = EmHduShowModeToString(m_tHduCfgSel.m_atChanInfo[0].m_emShowMode);
	String strTvwBoardInputPortTwoPerPloy;
	strTvwBoardInputPortTwoPerPloy = EmHduShowModeToString(m_tHduCfgSel.m_atChanInfo[1].m_emShowMode);
	
	if( strTvwBoardOrgModeName != strTvwBoardModeName || strTvwBoardOrgInputPortOne != strTvwBoardInputPortOne ||
		strTvwBoardOrgInputPortTwo != strTvwBoardInputPortTwo || strTvwBoardOrgInputPortOneNTSC != strTvwBoardInputPortOneNTSC || 
		strTvwBoardOrgInputPortTwoNTSC != strTvwBoardInputPortTwoNTSC || strTvwBoardOrgInputPortOnePer != strTvwBoardInputPortOnePer || 
		strTvwBoardOrgInputPortTwoPer != strTvwBoardInputPortTwoPer || strTvwBoardOrgInputPortOnePerPloy != strTvwBoardInputPortOnePerPloy || 		
		strTvwBoardOrgInputPortTwoPerPloy != strTvwBoardInputPortTwoPerPloy
		)
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeSave, true, m_pWndTree );
		
		SetMdlDataChange(TRUE);
		
		return ;
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardModeSave, false, m_pWndTree );
		
		SetMdlDataChange(FALSE);
	}
}

BOOL CTvwBoardCfgLogic::CheckPageTvwBoardMdlData()
{
	String strTvwBoardModeName;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTvwBoardModeName, strTvwBoardModeName, m_pWndTree );   
	
	String strTvwBoardInputPortOne;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOne, strTvwBoardInputPortOne, m_pWndTree );
	
	String strTvwBoardInputPortTwo;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwo, strTvwBoardInputPortTwo, m_pWndTree );
	
	String strTvwBoardInputPortOneNTSC;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOneNTSC, strTvwBoardInputPortOneNTSC, m_pWndTree );
	
	String strTvwBoardInputPortTwoNTSC;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwoNTSC, strTvwBoardInputPortTwoNTSC, m_pWndTree );
	
	String strTvwBoardInputPortOnePer;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOnePer, strTvwBoardInputPortOnePer, m_pWndTree );
	
	String strTvwBoardInputPortTwoPer;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwoPer, strTvwBoardInputPortTwoPer, m_pWndTree );
	
	String strTvwBoardInputPortOnePerPloy;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortOnePerPloy, strTvwBoardInputPortOnePerPloy, m_pWndTree );
	
	String strTvwBoardInputPortTwoPerPloy;
	UIFACTORYMGR_PTR->GetComboText( m_strComboxTvwBoardInputPortTwoPerPloy, strTvwBoardInputPortTwoPerPloy, m_pWndTree );
	
	if ( strTvwBoardModeName.empty() )
	{
		MSG_BOX_OK("模块名称不能为空！");
		UIFACTORYMGR_PTR->SetFocus( m_strEdtTvwBoardModeName, m_pWndTree );
		
		return FALSE;
	}
	else if ( CUmstoolCommon::IsInvalidChar( strTvwBoardModeName, 3, " ", ",", "，" ) )
	{
		MSG_BOX_OK("模块名称包含非法的字符：空格或逗号！");
		UIFACTORYMGR_PTR->SetFocus( m_strEdtTvwBoardModeName, m_pWndTree );
		
		return FALSE;
	}
	else if( IsExistMdlName() )
	{
		MSG_BOX_OK("模块名称已存在，保存失败！");
		UIFACTORYMGR_PTR->SetFocus( m_strEdtTvwBoardModeName, m_pWndTree );
		
		return FALSE;
	}
	else if ( strTvwBoardInputPortOne.empty() )
	{
		MSG_BOX_OK("输出接口1不能为空！");
		
		return FALSE;
	}
	else if ( strTvwBoardInputPortTwo.empty() )
	{
		MSG_BOX_OK("输出接口2不能为空！");
		
		return FALSE;
	}
	else if ( strTvwBoardInputPortOneNTSC.empty() )
	{
		MSG_BOX_OK("接口1输出制式不能为空！");
		
		return FALSE;
	}
	else if ( strTvwBoardInputPortTwoNTSC.empty() )
	{
		MSG_BOX_OK("接口2输出制式不能为空！");
		
		return FALSE;
	}
	else if ( strTvwBoardInputPortOnePer.empty() )
	{
		MSG_BOX_OK("接口1输出比例不能为空！");
		
		return FALSE;
	}
	else if ( strTvwBoardInputPortTwoPer.empty() )
	{
		MSG_BOX_OK("接口2输出比例不能为空！");
		
		return FALSE;
	}
	else if ( strTvwBoardInputPortOnePerPloy.empty() )
	{
		MSG_BOX_OK("接口1比例调整策略不能为空！");
		
		return FALSE;
	}
	else if ( strTvwBoardInputPortTwoPerPloy.empty() )
	{
		MSG_BOX_OK("接口2比例调整策略不能为空！");
		
		return FALSE;
	}
	
	return TRUE;
}

BOOL CTvwBoardCfgLogic::IsExistMdlName()
{
	String strTvwBoardModeName;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTvwBoardModeName, strTvwBoardModeName, m_pWndTree );   

	String strHduCfgSelName = m_tHduCfgSel.m_tName.m_abyAlias;

	THduCfg tHduCfg;
	String strMdlName;
	std::multimap<u8,THduCfg> mulmapHduCfg = DATAMGRPTR->GetUmsTvwBoardData();
	for ( std::multimap<u8,THduCfg>::iterator iter = mulmapHduCfg.begin(); iter != mulmapHduCfg.end(); iter++ )
	{
		tHduCfg = (*iter).second;
		strMdlName = tHduCfg.m_tName.m_abyAlias;
		if ( strMdlName == strTvwBoardModeName /*&& !strHduCfgSelName.empty()*/ && strHduCfgSelName != strTvwBoardModeName )
		{
			return TRUE;
		}
	}

	return FALSE;
}

HRESULT CTvwBoardCfgLogic::OnTvwBoardBeginUpgrade( WPARAM wparam, LPARAM lparam)
{ 
	LPCTSTR strCurTransFile = (LPCTSTR)wparam;
	TTPBrdUpGrade tBrdUpGrade;
	tBrdUpGrade.m_byLayer = m_tHduCfgSel.m_byLayer;
	tBrdUpGrade.m_bySlot = m_tHduCfgSel.m_bySlot;
	memcpy( tBrdUpGrade.m_szFileName, strCurTransFile, TP_UPGRADE_FILENAME_LENGTH );
	COMMONMGRIFPTR->TvwBoardUpgradeReq(tBrdUpGrade);
	return S_OK;
}

HRESULT CTvwBoardCfgLogic::OnTvwBoardUpgradeRsp( WPARAM wparam, LPARAM lparam)
{ 
    EmUpdateHduRet emRet = static_cast<EmUpdateHduRet>( wparam );
	if( em_hdu_update_success != emRet )
	{
		MESSAGEWND("电视墙单板升级失败！");
		UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
	}
	else    //升级完成关闭升级窗口
	{	
		s32 nResult = 0;
		UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
	}
	
	return S_OK;
}

BOOL CTvwBoardCfgLogic::ControlNotNullBoradLayorCount()
{
	std::set<int> setLayorCount;
	THduCfg tHduCfg;
	String strMdlName;
	std::multimap<u8,THduCfg> mulmapHduCfg = DATAMGRPTR->GetUmsTvwBoardData();
	for ( std::multimap<u8,THduCfg>::iterator iter = mulmapHduCfg.begin(); iter != mulmapHduCfg.end(); iter++ )
	{
		tHduCfg = (*iter).second;
		if ( 0 != tHduCfg.m_dwIP )
		{
			setLayorCount.insert(tHduCfg.m_byLayer);
		}
	}

	if ( setLayorCount.size() >= 4 )
	{
		std::set<int>::iterator iter = setLayorCount.find(m_tHduCfgSel.m_byLayer);
		if ( iter != setLayorCount.end() )
		{
			return TRUE;
		}
	}
	else
	{
		return TRUE;
	}

	return FALSE;
}