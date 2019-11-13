// boardcfglogic.cpp: implementation of the CBoardCfgLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umstooldll.h"
#include "boardcfglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBoardCfgLogic::CBoardCfgLogic():
m_strLstBoardZeroFloor("LstBoardZeroFloor"),
m_strLstBoardFirstFloor("LstBoardFirstFloor"),
m_strLstBoardSecondFloor("LstBoardSecondFloor"),
m_strLstBoardThirdFloor("LstBoardThirdFloor"),
m_strLstMenuFloor("LstFloorMenu"),
m_strEdtBoardModeName("EdtBoardModeName"),
m_strComboboxModeType("ComboboxModeType"),
m_strBtnBoardDel("BtnBoardDel"),
m_strBtnBoardModify("BtnBoardModify"),
m_strBtnBoardAdd("BtnBoardAdd"),
m_strBtnBoardModeDel("BtnBoardModeDel"),
m_strBtnBoardModeSave("BtnBoardModeSave"),
m_strBtnBoardReboot("BtnBoardReboot"),
m_strBtnBoardUpgrade("BtnBoardUpgrade"),
m_strStBoardModeName("StcStaticBoardModeName"),
m_strStBoardModeType("StcStaticBoardModeType"),
m_strStAudioMixName1("StcStaticAudioMixName1"),
m_strStAudioMixName2("StcStaticAudioMixName2"),
m_strEdtAudioMixName1("EdtAudioMixName1"),
m_strEdtAudioMixName2("EdtAudioMixName2"),
m_strStAudioMixNum1("StcStaticAudioMixNum1"),
m_strStAudioMixNum2("StcStaticAudioMixNum2"),
m_strEdtAudioMixNum1("EdtAudioMixNum1"),
m_strEdtAudioMixNum2("EdtAudioMixNum2")
{
	m_bMdlDataChange = FALSE;
	m_bApuMdlNameChange = FALSE;
	m_bApuMdlNum1Change = FALSE;
	m_bApuMdlNum2Change = FALSE;
	m_bSelItem = FALSE;
}

CBoardCfgLogic::~CBoardCfgLogic()
{  
	UnRegMsg();
	UnRegFunc();
}

void CBoardCfgLogic::RegMsg()
{    
    //REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CBoardCfgLogic::OnDisConnect, m_pLogic, CBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_REFRESHBOARD_NTY, CBoardCfgLogic::OnRefreshBoardInfoNotify, BOARDLOGICRPTR, CBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_OPTBOARD_NTY, CBoardCfgLogic::OnOptBoardNotify, BOARDLOGICRPTR, CBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_OPTBOARD_RSP, CBoardCfgLogic::OnOptBoardRsp, BOARDLOGICRPTR, CBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_DELETEBOARD_NTY, CBoardCfgLogic::OnDelBoardNotify, BOARDLOGICRPTR, CBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_OPTBOARDMODE_NTY, CBoardCfgLogic::OnOptBoardModeNotify, BOARDLOGICRPTR, CBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_OPTBOARDMODE_RSP, CBoardCfgLogic::OnOptBoardModeRsp, BOARDLOGICRPTR, CBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_BOARDUPGRADE_RSP, CBoardCfgLogic::OnBoardUpgradeRsp, BOARDLOGICRPTR, CBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_BOARDBEGINUPGRADE, CBoardCfgLogic::OnBoardBeginUpgrade, BOARDLOGICRPTR, CBoardCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_CONFCOUNT_NTY, CBoardCfgLogic::OnConfCount, BOARDLOGICRPTR, CBoardCfgLogic );
}

void CBoardCfgLogic::UnRegMsg()
{

}

bool CBoardCfgLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::InitWnd", CBoardCfgLogic::InitWnd, BOARDLOGICRPTR, CBoardCfgLogic );
	REG_LIST_CALLFUNC( "CBoardCfgLogic::OnMenuLstItem", CBoardCfgLogic::OnMenuLstItem, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_LIST_CALLFUNC( "CBoardCfgLogic::OnBoardLstFloorItem", CBoardCfgLogic::OnBoardLstFloorItem, BOARDLOGICRPTR, CBoardCfgLogic ); 

	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnBtnBoardDel", CBoardCfgLogic::OnBtnBoardDel, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnBtnBoardModify", CBoardCfgLogic::OnBtnBoardModify, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnBtnBoardAdd", CBoardCfgLogic::OnBtnBoardAdd, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnBtnBoardReboot", CBoardCfgLogic::OnBtnBoardReboot, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnBtnBoardUpgrade", CBoardCfgLogic::OnBtnBoardUpgrade, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnBtnBoardModeDel", CBoardCfgLogic::OnBtnBoardModeDel, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnBtnBoardModeSave", CBoardCfgLogic::OnBtnBoardModeSave, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnBoardMdlEditChange", CBoardCfgLogic::OnBoardMdlEditChange, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnClickBoardLstBlack", CBoardCfgLogic::OnClickBoardLstBlack, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnBoardAudioMixNameEditChange", CBoardCfgLogic::OnBoardAudioMixNameEditChange, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnBoardAudioMixNum1EditChange", CBoardCfgLogic::OnBoardAudioMixNum1EditChange, BOARDLOGICRPTR, CBoardCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardCfgLogic::OnBoardAudioMixNum2EditChange", CBoardCfgLogic::OnBoardAudioMixNum2EditChange, BOARDLOGICRPTR, CBoardCfgLogic ); 

	return true;
}

bool CBoardCfgLogic::UnRegFunc()
{

	return true;
}

bool CBoardCfgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

	SwitchTabWnd(m_strLstBoardZeroFloor.c_str());

	InitFunMenu();

	InitBoardListData();
	ResetBoardPageControl();

    return true;
}

void CBoardCfgLogic::ResetBoardPageControl()
{
	m_tTBoardInfoSel.Clear();
				
	UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardDel, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModify, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardAdd, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );

	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeDel, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, false, m_pWndTree );

	UIFACTORYMGR_PTR->EnableWindow( m_strEdtBoardModeName, false, m_pWndTree );	
	UIFACTORYMGR_PTR->EnableWindow( m_strComboboxModeType, false, m_pWndTree );

	ResetBoardMdlData(TRUE);
	ShowBoardMdlCfg();
	EnableApuBoardMdlEdit(FALSE);
}

void CBoardCfgLogic::UpdateBtnState()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	
	u32 dwData = DATAMGRPTR->GetConfCountData();

	if ( dwData > 0 )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmEnable", m_pWndTree);
    }
	else
	{
		String strMdlAlias = m_tTBoardInfoSel.m_tBrdMode[0].m_szEqpAlias;

		if ( em_unknow_brd == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType )
		{
			if ( m_bSelItem )
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardAdd, true, m_pWndTree );
			}
			
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardDel, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModify, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeDel, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, false, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardDel, true, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModify, true, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardAdd, false, m_pWndTree );
			
			if ( strMdlAlias.empty() )
			{
				if( m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType == em_cri2_brd || 
					m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType == em_mpu2ecard_brd )   //对于这两种板子   无模式则禁止升级
				{
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
				}
				else
				{
					if( m_tTBoardInfoSel.m_abEqpReg[0] )
					{
						UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, true, m_pWndTree );
						UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, true, m_pWndTree );
					}
					else
					{
						UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
						UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
					}
				}
				
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeDel, false, m_pWndTree );
			}
			else
			{
				if( m_tTBoardInfoSel.m_abEqpReg[0] )
				{
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, true, m_pWndTree );
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, true, m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
				}

				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeDel, true, m_pWndTree );
			}
		}
		
		if ( m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdSlot == 8 )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardDel, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModify, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardAdd, false, m_pWndTree );
		}	

		if ( m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType == em_cri2_brd || m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType == em_mpu2ecard_brd )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtBoardModeName, true, m_pWndTree );	
			UIFACTORYMGR_PTR->EnableWindow( m_strComboboxModeType, true, m_pWndTree );	
		}
		else if ( m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType == em_eapu_brd )
		{
			EnableApuBoardMdlEdit(TRUE);
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtBoardModeName, false, m_pWndTree );	
			UIFACTORYMGR_PTR->EnableWindow( m_strComboboxModeType, false, m_pWndTree );
		}
	}
}

void CBoardCfgLogic::InitBoardListData()
{
	m_vecTPBrdInfoZero.clear();
	m_vecTPBrdInfoFirst.clear();
	m_vecTPBrdInfoSecond.clear();
	m_vecTPBrdInfoThird.clear();

	s32 nIndex = 0;
	for ( nIndex = 0; nIndex < 17; nIndex++ )
	{
		TTPBrdInfo tBrdCfg;
		tBrdCfg.m_tBrdCfg.m_tBrdPos.m_emBrdType = em_unknow_brd;
		tBrdCfg.m_tBrdCfg.m_tBrdPos.m_byBrdLayer = 0;
		tBrdCfg.m_tBrdCfg.m_tBrdPos.m_byBrdSlot = nIndex;
		m_vecTPBrdInfoZero.push_back(tBrdCfg);

		Value_ViewListBoard valBoard(&m_vecTPBrdInfoZero);
		valBoard.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
		UIFACTORYMGR_PTR->SetPropertyValue( valBoard, m_strLstBoardZeroFloor, m_pWndTree );
	}

	for ( nIndex = 0; nIndex < 17; nIndex++ )
	{
		TTPBrdInfo tTPBrdInfo;
		tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType = em_unknow_brd;
		tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer = 1;
		tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot = nIndex;
		m_vecTPBrdInfoFirst.push_back(tTPBrdInfo);

		Value_ViewListBoard valBoard(&m_vecTPBrdInfoFirst);
		valBoard.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
		UIFACTORYMGR_PTR->SetPropertyValue( valBoard, m_strLstBoardFirstFloor, m_pWndTree );
	}

	for ( nIndex = 0; nIndex < 17; nIndex++ )
	{
		TTPBrdInfo tTPBrdInfo;
		tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType = em_unknow_brd;
		tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer = 2;
		tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot = nIndex;
		m_vecTPBrdInfoSecond.push_back(tTPBrdInfo);

		Value_ViewListBoard valBoard(&m_vecTPBrdInfoSecond);
		valBoard.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
		UIFACTORYMGR_PTR->SetPropertyValue( valBoard, m_strLstBoardSecondFloor, m_pWndTree );
	}

	for ( nIndex = 0; nIndex < 17; nIndex++ )
	{
		TTPBrdInfo tTPBrdInfo;
		tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType = em_unknow_brd;
		tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer = 3;
		tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot = nIndex;
		m_vecTPBrdInfoThird.push_back(tTPBrdInfo);

		Value_ViewListBoard valBoard(&m_vecTPBrdInfoThird);
		valBoard.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
		UIFACTORYMGR_PTR->SetPropertyValue( valBoard, m_strLstBoardThirdFloor, m_pWndTree );
	}
}

void CBoardCfgLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmFloorMenuListDefault", m_pWndTree );   //登陆后初始化基本信息页面
	}

	InitBoardListData();
	ResetBoardPageControl();

	m_bMdlDataChange = FALSE;
	m_bApuMdlNameChange = FALSE;
	m_bApuMdlNum1Change = FALSE;
	m_bApuMdlNum2Change = FALSE;
	m_bSelItem = FALSE;

	SwitchTabWnd(m_strLstBoardZeroFloor.c_str());
}

HRESULT CBoardCfgLogic::OnRefreshBoardInfoNotify( WPARAM wparam, LPARAM lparam)
{   
    if( m_pWndTree != NULL )
    {
		TTPBrdInfo tTPBrdInfo = *reinterpret_cast<TTPBrdInfo*>(wparam);

		u8 abyLayer = tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer;
		u8 abySlot = tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot;		
		
		//单板列表
		if ( 0 == tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer )
		{
			m_vecTPBrdInfoZero[abySlot] = tTPBrdInfo;
			Value_ViewListBoard valBoard(&m_vecTPBrdInfoZero);
			valBoard.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoard, m_strLstBoardZeroFloor, m_pWndTree );
		}
		else if ( 1 == tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer )
		{
			m_vecTPBrdInfoFirst[abySlot] = tTPBrdInfo;
			Value_ViewListBoard valBoardFir(&m_vecTPBrdInfoFirst);
			valBoardFir.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardFir, m_strLstBoardFirstFloor, m_pWndTree );
		}
		else if ( 2 == tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer )
		{	
			m_vecTPBrdInfoSecond[abySlot] = tTPBrdInfo;
			Value_ViewListBoard valBoardSec(&m_vecTPBrdInfoSecond);
			valBoardSec.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardSec, m_strLstBoardSecondFloor, m_pWndTree );
		}
		else if ( 3 == tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer )
		{	
			m_vecTPBrdInfoThird[abySlot] = tTPBrdInfo;
			Value_ViewListBoard valBoardThi(&m_vecTPBrdInfoThird);
			valBoardThi.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardThi, m_strLstBoardThirdFloor, m_pWndTree );
		}

		if ( tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdLayer &&
			tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdSlot )
		{
			m_tTBoardInfoSel = tTPBrdInfo;
			ShowBoardMdlCfg();
			//若已有会议，umc退出再登录时，不会再给tptool发送ev_confCount_Nty消息  20131227 by xhx
			u32 dwData = DATAMGRPTR->GetConfCountData();			
			if ( dwData <= 0 )
			{
				if( m_tTBoardInfoSel.m_abEqpReg[0] )
				{
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, true, m_pWndTree );
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, true, m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
				}
			}
			else
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
			}
		}
    }
    
	return S_OK;
}

HRESULT CBoardCfgLogic::OnOptBoardNotify( WPARAM wparam, LPARAM lparam)
{ 
    if( m_pWndTree != NULL )
    {
		TTPBrdCfg tTPBrdCfg = *reinterpret_cast<TTPBrdCfg*>(wparam);
		m_tTBoardInfoSel.m_tBrdCfg = tTPBrdCfg;

		//自动匹配默认模式
		EMBrdType emEqpType = tTPBrdCfg.m_tBrdPos.m_emBrdType;
		switch( emEqpType )
		{
		case em_eapu_brd:
			{
				m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType = em_audmix_mdl;
				m_tTBoardInfoSel.m_tBrdMode[1].m_emEqpType = em_audmix_mdl;
			}
			break;
		case em_mpc_brd:
			{
				m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType = em_mpc_mdl;
			}
			break;
		case em_mpu2ecard_brd:
			{
			}
			break;
		case em_is22_brd:
			{
				m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType = em_netbuf_mdl;				
			}
			break;
		case em_cri2_brd:
			{
				m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType = em_dataswitch_mdl;
			}
			break;
		default:   //em_unknow_brd
			{
			}
			break;
		}

		IMPCOMMONLOGICRPTR->SerSevrIpAddr(m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_dwBrdIP);
		IMPCOMMONLOGICRPTR->SetEMEqpType(m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType);
		
		u8 abyLayer = tTPBrdCfg.m_tBrdPos.m_byBrdLayer;
		u8 abySlot = tTPBrdCfg.m_tBrdPos.m_byBrdSlot;			

		//单板列表
		if ( 0 == tTPBrdCfg.m_tBrdPos.m_byBrdLayer )
		{
			m_vecTPBrdInfoZero[abySlot] = m_tTBoardInfoSel;
			Value_ViewListBoard valBoard(&m_vecTPBrdInfoZero);
			valBoard.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoard, m_strLstBoardZeroFloor, m_pWndTree );
		}
		else if ( 1 == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdLayer )
		{
			m_vecTPBrdInfoFirst[abySlot] = m_tTBoardInfoSel;
			Value_ViewListBoard valBoardFir(&m_vecTPBrdInfoFirst);
			valBoardFir.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardFir, m_strLstBoardFirstFloor, m_pWndTree );
		}
		else if ( 2 == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdLayer )
		{	
			m_vecTPBrdInfoSecond[abySlot] = m_tTBoardInfoSel;
			Value_ViewListBoard valBoardSec(&m_vecTPBrdInfoSecond);
			valBoardSec.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardSec, m_strLstBoardSecondFloor, m_pWndTree );
		}
		else if ( 3 == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdLayer )
		{		
			m_vecTPBrdInfoThird[abySlot] = m_tTBoardInfoSel;
			Value_ViewListBoard valBoardThi(&m_vecTPBrdInfoThird);
			valBoardThi.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardThi, m_strLstBoardThirdFloor, m_pWndTree );
		}

		if ( m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdSlot == 8 )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardDel, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModify, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardAdd, false, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardDel, true, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModify, true, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardAdd, false, m_pWndTree );
		}
		
		if( m_tTBoardInfoSel.m_abEqpReg[0] )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, true, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, true, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );	
		}
		
		ShowBoardMdlCfg();

		//模式类别
		EMBrdType emBrdType = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType;

		std::vector<CString> vecBrdType =  EMBrdTypeToVector(emBrdType);
		if ( em_eapu_brd == emBrdType )
		{
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixName1, "", m_pWndTree );
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixName2, "", m_pWndTree );
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum1, "64", m_pWndTree );
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum2, "0", m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtAudioMixNum1, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtAudioMixNum2, false, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->SetComboListData( m_strComboboxModeType, vecBrdType, m_pWndTree );  //设置对应单板类型combo列表
			if ( vecBrdType.size() > 0 )
			{
				UIFACTORYMGR_PTR->SetComboText( m_strComboboxModeType, EMEqpTypeToString(m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType), m_pWndTree );  //设置单板默认类型名
			}
		}
		
		String strMdlAlias = m_tTBoardInfoSel.m_tBrdMode[0].m_szEqpAlias;
		if ( strMdlAlias.empty() )
		{
			if( /*m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType == em_cri2_brd || */
				m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType == em_mpu2ecard_brd )   //对于这两种板子   无模式则禁止升级
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
			}
			else
			{
				if( m_tTBoardInfoSel.m_abEqpReg[0] )
				{
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, true, m_pWndTree );
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, true, m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
				}
			}

			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeDel, false, m_pWndTree );
		}
		else
		{
			if( m_tTBoardInfoSel.m_abEqpReg[0] )
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, true, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, true, m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
			}

			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeDel, true, m_pWndTree );
		}

		UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, false, m_pWndTree );   //点击浏览和添加成功  Enable false

		u32 dwData = DATAMGRPTR->GetConfCountData();	
		if ( dwData <= 0 )
		{
			if ( /*emBrdType == em_cri2_brd ||*/ emBrdType == em_mpu2ecard_brd )
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strEdtBoardModeName, true, m_pWndTree );	
				UIFACTORYMGR_PTR->EnableWindow( m_strComboboxModeType, true, m_pWndTree );	
			}
			else if ( emBrdType == em_eapu_brd )
			{
				EnableApuBoardMdlEdit(TRUE);
			}
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtBoardModeName, false, m_pWndTree );	
			UIFACTORYMGR_PTR->EnableWindow( m_strComboboxModeType, false, m_pWndTree );
			EnableApuBoardMdlEdit(FALSE);
		}
    }

	SetMdlDataChange(FALSE);

	return S_OK;
}

HRESULT CBoardCfgLogic::OnOptBoardRsp( WPARAM wparam, LPARAM lparam)
{ 
	TBrdOptRet tRet = *reinterpret_cast<TBrdOptRet*>( lparam );
	
	String strError;
	switch( tRet.emBrdOptType )
	{
	case em_Add_Ret:
		{
			strError = "添加单板失败：";
		}
		break;
	case em_Modify_Ret:
		{
			strError = "修改单板失败：";
		}
		break;
	case em_Del_Ret:
		{
			strError = "删除单板失败：";
		}
		break;
	}

	strError += EmTpBoardRetToString(tRet.emTpBoardRet);
	if ( !strError.empty() )
	{
		MESSAGEWND(strError.c_str());
	}

	return S_OK;
}

HRESULT CBoardCfgLogic::OnDelBoardNotify( WPARAM wparam, LPARAM lparam)
{ 
	if( m_pWndTree != NULL )
    {
		TTPBrdCfg tTPBrdCfg = *reinterpret_cast<TTPBrdCfg*>(wparam);
		m_tTBoardInfoSel.m_tBrdCfg = tTPBrdCfg;
		for( s32 nIndex = 0; nIndex < TP_UMS_BRD_MAXNUM_EQP; nIndex++ )
		{
			m_tTBoardInfoSel.m_tBrdMode[nIndex].Clear();
		}

		IMPCOMMONLOGICRPTR->SerSevrIpAddr(m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_dwBrdIP);
		IMPCOMMONLOGICRPTR->SetEMEqpType(m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType);
		
		u8 abyLayer = tTPBrdCfg.m_tBrdPos.m_byBrdLayer;
		u8 abySlot = tTPBrdCfg.m_tBrdPos.m_byBrdSlot;	
		
		TTPBrdInfo tTPBrdInfo;
		tTPBrdInfo.m_tBrdCfg = tTPBrdCfg;
		//单板列表
		if ( 0 == tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer )
		{
			m_vecTPBrdInfoZero[abySlot] = tTPBrdInfo;
			Value_ViewListBoard valBoard(&m_vecTPBrdInfoZero);
			valBoard.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoard, m_strLstBoardZeroFloor, m_pWndTree );
		}
		else if ( 1 == tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer )
		{
			m_vecTPBrdInfoFirst[abySlot] = tTPBrdInfo;
			Value_ViewListBoard valBoardFir(&m_vecTPBrdInfoFirst);
			valBoardFir.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardFir, m_strLstBoardFirstFloor, m_pWndTree );
		}
		else if ( 2 == tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer )
		{	
			m_vecTPBrdInfoSecond[abySlot] = tTPBrdInfo;
			Value_ViewListBoard valBoardSec(&m_vecTPBrdInfoSecond);
			valBoardSec.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardSec, m_strLstBoardSecondFloor, m_pWndTree );
		}
		else if ( 3 == tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer )
		{		
			m_vecTPBrdInfoThird[abySlot] = tTPBrdInfo;
			Value_ViewListBoard valBoardThi(&m_vecTPBrdInfoThird);
			valBoardThi.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardThi, m_strLstBoardThirdFloor, m_pWndTree );
		}
    }

	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardDel, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModify, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardAdd, true, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );

	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeDel, false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, false, m_pWndTree );

	UIFACTORYMGR_PTR->EnableWindow( m_strEdtBoardModeName, false, m_pWndTree );	
	UIFACTORYMGR_PTR->EnableWindow( m_strComboboxModeType, false, m_pWndTree );

	ResetBoardMdlData(TRUE);
	ShowBoardMdlCfg();
	EnableApuBoardMdlEdit(FALSE);

	SetMdlDataChange(FALSE);

	return S_OK;
}

HRESULT CBoardCfgLogic::OnOptBoardModeRsp( WPARAM wparam, LPARAM lparam)
{
	TBrdOptRet tRet = *reinterpret_cast<TBrdOptRet*>( lparam );

	String strError;
	switch( tRet.emBrdOptType )
	{
	case em_Add_Ret:
		{
			strError = "单板模式保存失败：";
		}
		break;
	case em_Modify_Ret:
		{
			strError = "单板模式保存失败：";
		}
		break;
	case em_Del_Ret:
		{
			strError = "删除单板模式失败：";
		}
		break;
	}
	
	strError += EmTpBoardRetToString(tRet.emTpBoardRet);
	if ( !strError.empty() )
	{
		MESSAGEWND(strError.c_str());
	}

	ResetBoardMdlData(FALSE);

	return S_OK;
}

void CBoardCfgLogic::InitFunMenu()
{
	ARRAY<TMenuItem> aryItem;
	TMenuItem item; 
	
	item.SetItemName( m_strLstBoardZeroFloor.c_str() );  
	item.SetItemType("ImageItemMenuZeroFloor");
	aryItem.push_back(item);
	
	item.SetItemName( m_strLstBoardFirstFloor.c_str() ); 
	item.SetItemType("ImageItemMenuFirFloor");
	aryItem.push_back(item);
	
	item.SetItemName( m_strLstBoardSecondFloor.c_str() );  
	item.SetItemType("ImageItemMenuSecFloor");
	aryItem.push_back(item);
	
	item.SetItemName( m_strLstBoardThirdFloor.c_str() );  
	item.SetItemType("ImageItemMenuThiFloor");
	aryItem.push_back(item);
	
	Value_ItemMenu valueMenu( &aryItem ); 
	valueMenu.m_strClickItemFunc = "CBoardCfgLogic::OnMenuLstItem";
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstMenuFloor, m_pWndTree ); 
}

void CBoardCfgLogic::SwitchTabWnd(CString strItemName)
{
	UIFACTORYMGR_PTR->ShowWindow( m_strLstBoardZeroFloor, !m_strLstBoardZeroFloor.compare(strItemName), m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strLstBoardFirstFloor, !m_strLstBoardFirstFloor.compare(strItemName), m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strLstBoardSecondFloor, !m_strLstBoardSecondFloor.compare(strItemName), m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strLstBoardThirdFloor, !m_strLstBoardThirdFloor.compare(strItemName), m_pWndTree );
}

bool CBoardCfgLogic::OnMenuLstItem( const IArgs & arg )
{
	if ( !CheckPageDataChangeToSave() )
	{
		CUmstoolCommon::SetLstSelItem( m_strLstMenuFloor, m_pWndTree, m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdLayer );
		return false;
	}

	m_bMdlDataChange = FALSE;
	m_bApuMdlNameChange = FALSE;
	m_bApuMdlNum1Change = FALSE;
	m_bApuMdlNum2Change = FALSE;
	m_bSelItem = FALSE;

	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_ItemMenu *pItemInfo = dynamic_cast<const Data_ItemMenu*>( pBaseItem->GetUserData() ) )
		{
			CString strMenuItemName = pItemInfo->m_tMenuItem.szName;
			SwitchTabWnd(strMenuItemName);
			ResetBoardPageControl();     //切换以后目前不清空   保持原选中项不变
		}
	}
	return true;
}

bool CBoardCfgLogic::OnBtnBoardDel( const IArgs & arg )
{ 
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "确定要删除单板？"  );
	if ( MSGBOX_OK == nMsgBoxRet)
	{
		u16 nRet = COMMONMGRIFPTR->BoardDeleteReq(m_tTBoardInfoSel.m_tBrdCfg);;
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "删除单板请求发送失败" );
		}
	}

	return true;
}

bool CBoardCfgLogic::OnBtnBoardModify( const IArgs & arg )
{
	CMsgDispatch::SendMessage( UI_UMSTOOL_MSG_BOARDSELDATA_Click, (WPARAM)&m_tTBoardInfoSel, (LPARAM)em_BOARDOPT_MODIFY );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrBoardOptDlg );

	return true;
}

bool CBoardCfgLogic::OnBtnBoardAdd( const IArgs & arg )
{ 
	CMsgDispatch::SendMessage( UI_UMSTOOL_MSG_BOARDSELDATA_Click, (WPARAM)&m_tTBoardInfoSel, (LPARAM)em_BOARDOPT_ADD );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrBoardOptDlg );
	
	return true;
}

bool CBoardCfgLogic::OnBtnBoardReboot( const IArgs & arg )
{ 
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "是否重启单板操作？" );
	if ( MSGBOX_OK == nMsgBoxRet)
	{
		u16 nRet = COMMONMGRIFPTR->BoardRebootReq(m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos);;
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "单板重启请求发送失败" );
		}
	}

	return true;
}

bool CBoardCfgLogic::OnBtnBoardUpgrade( const IArgs & arg )
{ 
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchUpgradeBoard", NULL, g_stcStrImpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrImpCommonDlg );	

	return true;
}

bool CBoardCfgLogic::OnBtnBoardModeDel( const IArgs & arg )
{ 
	TTPBrdMdlInfo tBrdInfo;
	tBrdInfo.m_byLayer = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdLayer;
	tBrdInfo.m_bySlot = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdSlot;
	
	if ( em_eapu_brd == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType )
	{
		tBrdInfo.m_atMdlCfg[0].m_byAudmixNum = m_tTBoardInfoSel.m_tBrdMode[0].m_byAudmixNum;
		strncpy( tBrdInfo.m_atMdlCfg[0].m_szEqpAlias, m_tTBoardInfoSel.m_tBrdMode[0].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );
	
		tBrdInfo.m_atMdlCfg[1].m_byAudmixNum = m_tTBoardInfoSel.m_tBrdMode[1].m_byAudmixNum;
		strncpy( tBrdInfo.m_atMdlCfg[1].m_szEqpAlias, m_tTBoardInfoSel.m_tBrdMode[1].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );

		tBrdInfo.m_atMdlCfg[0].m_emEqpType = em_audmix_mdl;
		tBrdInfo.m_atMdlCfg[1].m_emEqpType = em_audmix_mdl;

		tBrdInfo.m_byIndex = 2;
	}
	else
	{
		tBrdInfo.m_atMdlCfg[0].m_emEqpType = m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType;
		strncpy( tBrdInfo.m_atMdlCfg[0].m_szEqpAlias, m_tTBoardInfoSel.m_tBrdMode[0].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );

		tBrdInfo.m_byIndex = 1;
	}


	u16 nRet = COMMONMGRIFPTR->BoardModeDeleteReq(tBrdInfo);
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "清空单板请求发送失败" );
	}
	
	return true;
}

bool CBoardCfgLogic::OnBtnBoardModeSave( const IArgs & arg )
{ 
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	String strWarning;
	strWarning = "单板模块信息有改动，是否保存？";
	MSG_BOX( nMsgBoxRet, strWarning );
	if ( MSGBOX_OK == nMsgBoxRet )
	{		
		if ( !CheckPageBoardMdlData() )
		{
			return false;
		}
		
		TTPBrdMdlInfo tBrdInfo;
		tBrdInfo.m_byLayer = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdLayer;
		tBrdInfo.m_bySlot = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdSlot;

		if ( em_eapu_brd == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType )
		{
			String strMdlName1;
			UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixName1, strMdlName1, m_pWndTree );   
			String strMdlName2;
			UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixName2, strMdlName2, m_pWndTree );  
			String strAudmixNum1;
			UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixNum1, strAudmixNum1, m_pWndTree );
			String strAudmixNum2;
			UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixNum2, strAudmixNum2, m_pWndTree );
	
			strncpy( tBrdInfo.m_atMdlCfg[0].m_szEqpAlias, strMdlName1.c_str(), strMdlName1.size() );
			strncpy( tBrdInfo.m_atMdlCfg[1].m_szEqpAlias, strMdlName2.c_str(), strMdlName2.size() );

			u8 byAudmixNum1 = atoi(strAudmixNum1.c_str());
			u8 byAudmixNum2 = atoi(strAudmixNum2.c_str());
			tBrdInfo.m_atMdlCfg[0].m_byAudmixNum = byAudmixNum1;
			tBrdInfo.m_atMdlCfg[1].m_byAudmixNum = byAudmixNum2;

			tBrdInfo.m_atMdlCfg[0].m_emEqpType = em_audmix_mdl;
			tBrdInfo.m_atMdlCfg[1].m_emEqpType = em_audmix_mdl;

			tBrdInfo.m_byIndex = 2;
		} 
		else
		{
			String strMdlName;
			UIFACTORYMGR_PTR->GetCaption( m_strEdtBoardModeName, strMdlName, m_pWndTree );   
			
			String strMdlType;
			UIFACTORYMGR_PTR->GetComboText( m_strComboboxModeType, strMdlType, m_pWndTree );

			tBrdInfo.m_atMdlCfg[0].m_emEqpType = StringToEMEqpType(strMdlType);
			strncpy( tBrdInfo.m_atMdlCfg[0].m_szEqpAlias, strMdlName.c_str(), strMdlName.size() );

			tBrdInfo.m_byIndex = 1;
		}

		u16 nRet = COMMONMGRIFPTR->BoardModeModifyReq(tBrdInfo);;
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "单板模式保存请求发送失败" );
			return false;
		}
	}
	else	//还原为模式配置前的数据
	{
		ResetBoardMdlData(FALSE);
	}
	
	return true;
}

bool CBoardCfgLogic::OnBoardLstFloorItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_BoardInfo * pDataTemp = dynamic_cast< const Data_BoardInfo*>(pIData) )
        {   
			m_bMdlDataChange = FALSE;
			m_bApuMdlNameChange = FALSE;
			m_bApuMdlNum1Change = FALSE;
			m_bApuMdlNum2Change = FALSE;
			m_bSelItem = TRUE;
			m_tTBoardInfoSel = pDataTemp->m_tBoardInfo;

			IMPCOMMONLOGICRPTR->SerSevrIpAddr(m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_dwBrdIP);
			IMPCOMMONLOGICRPTR->SetEMEqpType(m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType);

			ShowBoardMdlCfg();
			ResetBoardMdlData(FALSE);
			
			//设置其他层三个列表非选中项
			u32 nCurLayar = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdLayer;
			SetLstNoSelItem(nCurLayar);
			
			UpdateBtnState();
			
        	UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, false, m_pWndTree );			
		}
	}

	return true;
}

void CBoardCfgLogic::SetLstNoSelItem(s32 nExceptLayarNo)
{
	if ( 0 == nExceptLayarNo )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardFirstFloor );
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardSecondFloor );
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardThirdFloor );
	}
	else if( 1 == nExceptLayarNo )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardZeroFloor );
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardSecondFloor );
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardThirdFloor );
	}
	else if ( 2 == nExceptLayarNo )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardZeroFloor );
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardFirstFloor );
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardThirdFloor );
	}
	else if ( 3 == nExceptLayarNo )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardZeroFloor );
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardFirstFloor );
		UIFACTORYMGR_PTR->LoadScheme( "SchmBoardListDataClean", m_pWndTree, m_strLstBoardSecondFloor );
	}
}

void CBoardCfgLogic::ShowBoardMdlCfg()
{
	EMBrdType emBrdType = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType;
	bool bHide = true; 
	if ( em_eapu_brd == emBrdType )
	{
		bHide = false;
	}

	UIFACTORYMGR_PTR->ShowWindow( m_strStBoardModeName, bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strStBoardModeType, bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strEdtBoardModeName, bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strComboboxModeType, bHide, m_pWndTree );
	
	UIFACTORYMGR_PTR->ShowWindow( m_strStAudioMixName1, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strStAudioMixName2, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strEdtAudioMixName1, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strEdtAudioMixName2, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strStAudioMixNum1, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strStAudioMixNum2, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strEdtAudioMixNum1, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strEdtAudioMixNum2, !bHide, m_pWndTree );
}

void CBoardCfgLogic::EnableApuBoardMdlEdit(BOOL bEnable)
{
	UIFACTORYMGR_PTR->EnableWindow( m_strEdtAudioMixName1, bEnable, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strEdtAudioMixName2, bEnable, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strEdtAudioMixNum1, bEnable, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strEdtAudioMixNum2, bEnable, m_pWndTree );
}

void CBoardCfgLogic::ResetBoardMdlData(BOOL bDefault)
{
	if ( bDefault )
	{
		//设置默认显示数据
		UIFACTORYMGR_PTR->SetCaption( m_strEdtBoardModeName, "", m_pWndTree );
		
		std::vector<CString> vecMdlTypeData;
		UIFACTORYMGR_PTR->SetComboListData( m_strComboboxModeType, vecMdlTypeData, m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( m_strComboboxModeType, "无", m_pWndTree );
		
		UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixName1, "", m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixName2, "", m_pWndTree );
		
		UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum1, "64", m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum2, "0", m_pWndTree );
	}
	else
	{
		//还原为模式配置前的数据
		if ( em_eapu_brd == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType )
		{
			String strMdlAlias1 = m_tTBoardInfoSel.m_tBrdMode[0].m_szEqpAlias;
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixName1, strMdlAlias1, m_pWndTree );
			String strMdlAlias2 = m_tTBoardInfoSel.m_tBrdMode[1].m_szEqpAlias;
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixName2, strMdlAlias2, m_pWndTree );
			
			u8 byAudmixNum1 = m_tTBoardInfoSel.m_tBrdMode[0].m_byAudmixNum;
			u8 byAudmixNum2 = m_tTBoardInfoSel.m_tBrdMode[1].m_byAudmixNum;
			char chData1[3] = {0};
			itoa( byAudmixNum1 , chData1, 10 );
			char chData2[3] = {0};
			itoa( byAudmixNum2 , chData2, 10 );
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum1, chData1, m_pWndTree );
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum2, chData2, m_pWndTree );
		}
		else
		{
			String strMdlAlias = m_tTBoardInfoSel.m_tBrdMode[0].m_szEqpAlias;
			UIFACTORYMGR_PTR->SetCaption( m_strEdtBoardModeName,  strMdlAlias, m_pWndTree );

			EMEqpType emEqpTy = m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType;			
			EMBrdType emEqpType   = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType;
			std::vector<CString> vecBrdType =  EMBrdTypeToVector(emEqpType);
			UIFACTORYMGR_PTR->SetComboListData( m_strComboboxModeType, vecBrdType, m_pWndTree );  //设置对应单板类型combo列表
			if( vecBrdType.size() > 0 )
			{
				UIFACTORYMGR_PTR->SetComboText( m_strComboboxModeType, EMEqpTypeToString(emEqpTy), m_pWndTree );  //设置单板默认类型名
			}
			
			if ( em_unknow_brd == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType )
			{
				UIFACTORYMGR_PTR->SetComboText( m_strComboboxModeType, "无", m_pWndTree );
			}
		}
	}
}

HRESULT CBoardCfgLogic::OnOptBoardModeNotify( WPARAM wparam, LPARAM lparam)
{ 
	if( m_pWndTree != NULL )
    {
		m_bMdlDataChange = FALSE;
		m_bApuMdlNameChange = FALSE;
		m_bApuMdlNum1Change = FALSE;
		m_bApuMdlNum2Change = FALSE;
		
		TTPBrdMdlInfo tMdlInfo = *reinterpret_cast<TTPBrdMdlInfo*>(wparam);
		//单板列表
		if ( 0 == tMdlInfo.m_byLayer )
		{
			TTPBrdInfo* pTTPBrdInfo = &m_vecTPBrdInfoZero[tMdlInfo.m_bySlot];
			if ( NULL != pTTPBrdInfo )
			{
				pTTPBrdInfo->m_tBrdCfg.m_tBrdPos.m_byBrdLayer = tMdlInfo.m_byLayer;
				pTTPBrdInfo->m_tBrdCfg.m_tBrdPos.m_byBrdSlot = tMdlInfo.m_bySlot;
				
				pTTPBrdInfo->m_tBrdMode[0].m_emEqpType = tMdlInfo.m_atMdlCfg[0].m_emEqpType;
				strncpy( pTTPBrdInfo->m_tBrdMode[0].m_szEqpAlias, tMdlInfo.m_atMdlCfg[0].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );
				pTTPBrdInfo->m_tBrdMode[0].m_szEqpAlias[TP_MAXLEN_EQP_ALIAS] = '\0';
				pTTPBrdInfo->m_tBrdMode[0].m_byAudmixNum = tMdlInfo.m_atMdlCfg[0].m_byAudmixNum;

				if ( 2 == tMdlInfo.m_byIndex )
				{
					pTTPBrdInfo->m_tBrdMode[1].m_emEqpType = tMdlInfo.m_atMdlCfg[1].m_emEqpType;
					strncpy( pTTPBrdInfo->m_tBrdMode[1].m_szEqpAlias, tMdlInfo.m_atMdlCfg[1].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );
					pTTPBrdInfo->m_tBrdMode[1].m_szEqpAlias[TP_MAXLEN_EQP_ALIAS] = '\0';
					pTTPBrdInfo->m_tBrdMode[1].m_byAudmixNum = tMdlInfo.m_atMdlCfg[1].m_byAudmixNum;
				}
			}

			Value_ViewListBoard valBoardZero(&m_vecTPBrdInfoZero);
			valBoardZero.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardZero, m_strLstBoardZeroFloor, m_pWndTree );
		}
		else if ( 1 == tMdlInfo.m_byLayer )
		{
			TTPBrdInfo* pTTPBrdInfo = &m_vecTPBrdInfoFirst[tMdlInfo.m_bySlot];
			if ( NULL != pTTPBrdInfo )
			{
				pTTPBrdInfo->m_tBrdCfg.m_tBrdPos.m_byBrdLayer = tMdlInfo.m_byLayer;
				pTTPBrdInfo->m_tBrdCfg.m_tBrdPos.m_byBrdSlot = tMdlInfo.m_bySlot;
				
				pTTPBrdInfo->m_tBrdMode[0].m_emEqpType = tMdlInfo.m_atMdlCfg[0].m_emEqpType;
				strncpy( pTTPBrdInfo->m_tBrdMode[0].m_szEqpAlias, tMdlInfo.m_atMdlCfg[0].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );
				pTTPBrdInfo->m_tBrdMode[0].m_szEqpAlias[TP_MAXLEN_EQP_ALIAS] = '\0';
				pTTPBrdInfo->m_tBrdMode[0].m_byAudmixNum = tMdlInfo.m_atMdlCfg[0].m_byAudmixNum;
				
				if ( 2 == tMdlInfo.m_byIndex )
				{
					pTTPBrdInfo->m_tBrdMode[1].m_emEqpType = tMdlInfo.m_atMdlCfg[1].m_emEqpType;
					strncpy( pTTPBrdInfo->m_tBrdMode[1].m_szEqpAlias, tMdlInfo.m_atMdlCfg[1].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );
					pTTPBrdInfo->m_tBrdMode[1].m_szEqpAlias[TP_MAXLEN_EQP_ALIAS] = '\0';
					pTTPBrdInfo->m_tBrdMode[1].m_byAudmixNum = tMdlInfo.m_atMdlCfg[1].m_byAudmixNum;
				}
			}

			//m_vecTPBrdInfoFirst[abySlot] = tTPBrdInfo;
			Value_ViewListBoard valBoardFir(&m_vecTPBrdInfoFirst);
			valBoardFir.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardFir, m_strLstBoardFirstFloor, m_pWndTree );
		}
		else if ( 2 == tMdlInfo.m_byLayer )
		{	
			TTPBrdInfo* pTTPBrdInfo = &m_vecTPBrdInfoSecond[tMdlInfo.m_bySlot];
			if ( NULL != pTTPBrdInfo )
			{
				pTTPBrdInfo->m_tBrdCfg.m_tBrdPos.m_byBrdLayer = tMdlInfo.m_byLayer;
				pTTPBrdInfo->m_tBrdCfg.m_tBrdPos.m_byBrdSlot = tMdlInfo.m_bySlot;
				
				pTTPBrdInfo->m_tBrdMode[0].m_emEqpType = tMdlInfo.m_atMdlCfg[0].m_emEqpType;
				strncpy( pTTPBrdInfo->m_tBrdMode[0].m_szEqpAlias, tMdlInfo.m_atMdlCfg[0].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );
				pTTPBrdInfo->m_tBrdMode[0].m_szEqpAlias[TP_MAXLEN_EQP_ALIAS] = '\0';
				pTTPBrdInfo->m_tBrdMode[0].m_byAudmixNum = tMdlInfo.m_atMdlCfg[0].m_byAudmixNum;
				
				if ( 2 == tMdlInfo.m_byIndex )
				{
					pTTPBrdInfo->m_tBrdMode[1].m_emEqpType = tMdlInfo.m_atMdlCfg[1].m_emEqpType;
					strncpy( pTTPBrdInfo->m_tBrdMode[1].m_szEqpAlias, tMdlInfo.m_atMdlCfg[1].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );
					pTTPBrdInfo->m_tBrdMode[1].m_szEqpAlias[TP_MAXLEN_EQP_ALIAS] = '\0';
					pTTPBrdInfo->m_tBrdMode[1].m_byAudmixNum = tMdlInfo.m_atMdlCfg[1].m_byAudmixNum;
				}
			}

			//m_vecTPBrdInfoSecond[abySlot] = tTPBrdInfo;
			Value_ViewListBoard valBoardSec(&m_vecTPBrdInfoSecond);
			valBoardSec.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardSec, m_strLstBoardSecondFloor, m_pWndTree );
		}
		else if ( 3 == tMdlInfo.m_byLayer )
		{		
			TTPBrdInfo* pTTPBrdInfo = &m_vecTPBrdInfoThird[tMdlInfo.m_bySlot];
			if ( NULL != pTTPBrdInfo )
			{
				pTTPBrdInfo->m_tBrdCfg.m_tBrdPos.m_byBrdLayer = tMdlInfo.m_byLayer;
				pTTPBrdInfo->m_tBrdCfg.m_tBrdPos.m_byBrdSlot = tMdlInfo.m_bySlot;
				
				pTTPBrdInfo->m_tBrdMode[0].m_emEqpType = tMdlInfo.m_atMdlCfg[0].m_emEqpType;
				strncpy( pTTPBrdInfo->m_tBrdMode[0].m_szEqpAlias, tMdlInfo.m_atMdlCfg[0].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );
				pTTPBrdInfo->m_tBrdMode[0].m_szEqpAlias[TP_MAXLEN_EQP_ALIAS] = '\0';
				pTTPBrdInfo->m_tBrdMode[0].m_byAudmixNum = tMdlInfo.m_atMdlCfg[0].m_byAudmixNum;
				
				if ( 2 == tMdlInfo.m_byIndex )
				{
					pTTPBrdInfo->m_tBrdMode[1].m_emEqpType = tMdlInfo.m_atMdlCfg[1].m_emEqpType;
					strncpy( pTTPBrdInfo->m_tBrdMode[1].m_szEqpAlias, tMdlInfo.m_atMdlCfg[1].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );
					pTTPBrdInfo->m_tBrdMode[1].m_szEqpAlias[TP_MAXLEN_EQP_ALIAS] = '\0';
					pTTPBrdInfo->m_tBrdMode[1].m_byAudmixNum = tMdlInfo.m_atMdlCfg[1].m_byAudmixNum;
				}
			}

			//m_vecTPBrdInfoThird[abySlot] = tTPBrdInfo;
			Value_ViewListBoard valBoardThi(&m_vecTPBrdInfoThird);
			valBoardThi.m_strClickItemFunc = "CBoardCfgLogic::OnBoardLstFloorItem";
			UIFACTORYMGR_PTR->SetPropertyValue( valBoardThi, m_strLstBoardThirdFloor, m_pWndTree );
		}

		if ( m_bSelItem == FALSE )
		{
			return 0;
		}

		m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType = tMdlInfo.m_atMdlCfg[0].m_emEqpType;
		strncpy( m_tTBoardInfoSel.m_tBrdMode[0].m_szEqpAlias, tMdlInfo.m_atMdlCfg[0].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );
		m_tTBoardInfoSel.m_tBrdMode[0].m_byAudmixNum = tMdlInfo.m_atMdlCfg[0].m_byAudmixNum;
		if ( 2 == tMdlInfo.m_byIndex )
		{
			m_tTBoardInfoSel.m_tBrdMode[1].m_emEqpType = tMdlInfo.m_atMdlCfg[1].m_emEqpType;
			strncpy( m_tTBoardInfoSel.m_tBrdMode[1].m_szEqpAlias, tMdlInfo.m_atMdlCfg[1].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS );
			m_tTBoardInfoSel.m_tBrdMode[1].m_byAudmixNum = tMdlInfo.m_atMdlCfg[1].m_byAudmixNum;
		}
		
		IMPCOMMONLOGICRPTR->SerSevrIpAddr(m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_dwBrdIP);
		IMPCOMMONLOGICRPTR->SetEMEqpType(m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType);
		
		u8 abyLayer = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdLayer;
		u8 abySlot = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdSlot;			

		String strMdlAlias = m_tTBoardInfoSel.m_tBrdMode[0].m_szEqpAlias;
		if ( strMdlAlias.empty() )
		{
			if( /*m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType == em_cri2_brd ||*/ 
				m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType == em_mpu2ecard_brd )   //对于这两种板子   无模式则禁止升级
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
			}
			else
			{
				if( m_tTBoardInfoSel.m_abEqpReg[0] )
				{
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, true, m_pWndTree );
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, true, m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
					UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
				}
			}

			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeDel, false, m_pWndTree );
		}
		else
		{
			if( m_tTBoardInfoSel.m_abEqpReg[0] )
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, true, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, true, m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardReboot, false, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardUpgrade, false, m_pWndTree );
			}

			if ( m_bSelItem )
			{
				UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeDel, true, m_pWndTree );
			}
		}
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, false, m_pWndTree );   //点击浏览和添加成功  Enable false

		ResetBoardMdlData(FALSE);

		SetMdlDataChange(FALSE);

		//删除单板模式 如果在线板子提醒重启      130528   ldy    新需求去除重启提醒   有服务器自动重启
// 		if ( m_tTBoardInfoSel.m_abEqpReg[0] )
// 		{
// 			if( em_Del_Ret == lparam || em_Modify_Ret == lparam )
// 			{
// 				MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
// 				String strWarning;
// 				if ( em_Del_Ret == lparam )
// 				{
// 					strWarning = "板子模式已清空，是否重启生效？";
// 				}
// 				else
// 				{
// 					strWarning = "板子模式已修改";
// 					MSG_BOX_OK(strWarning);
// 					return S_OK;
// 				}
// 
// 				MSG_BOX( nMsgBoxRet, strWarning );
// 				if ( MSGBOX_OK == nMsgBoxRet )
// 				{		
// 					COMMONMGRIFPTR->BoardRebootReq(m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos);
// 				}
// 			}
// 		}
	}

	return S_OK;
}

String CBoardCfgLogic::EmTpBoardRetToString(EmTpBoardRet emValue)
{
	String strError;
	switch( emValue )
	{
	case emTP_Board_UnKonw:
		{
			strError = "单板未知";
		}
		break;
	case emTP_Board_AddSuccess: //单板添加成功
		{
			strError = "";		
		}
		break;
	case emTP_Board_DelSuccess: //单板删除成功
		{
			strError = "";
		}
		break;
	case emTP_Board_ModifySuccess: //单板修改成功
		{
			strError = "";		
		}
		break;
	case emTP_Board_MaxNum:
		{
			strError = "单板数量达到最大值";	
		}
		break;
	case emTP_Board_Mode_AddSuccess: //单板模式添加成功
		{
			strError = "";	
		}
		break;
	case emTP_Board_Mode_DelSuccess: //单板模式删除成功
		{
			strError = "";	
		}
		break;
	case emTP_Board_Mode_ModifySuccess: //单板模式修改成功
		{
			strError = "";	
		}
		break;
	case emTP_Board_UnFind: 
		{
			strError = "未找到条目";	
		}
		break;
	case emTP_Board_UnKnowLoc: 
		{
			strError = "单板层号槽号未知";	
		}
		break;
	case emTP_Board_Repeat: 
		{
			strError = "单板重复";	
		}
		break;
	case emTP_BrdType_NotMatch_EqpType: 
		{
			strError = "单板类型与外设类型不匹配";	
		}
		break;
	case emTP_BrdMode_Repeat: 
		{
			strError = "要修改的模式与原模式相同";	
		}
		break;
	case emTP_BrdMode_MaxNum: 
		{
			strError = "单板模式达到最大值";	
		}
		break;
	default:
		{
		}
		break;
	}
	
	return strError;
}

String CBoardCfgLogic::EMEqpTypeToString(EMEqpType emValue)
{
	String strEqpType;
	switch( emValue )	//外设模式类型
	{
	case em_adapter_mdl:
		{
			strEqpType = "regserver";	
		}
		break;
	case em_dataswitch_mdl:
		{
			strEqpType = "mediatrans";						
		}
		break;
	case em_netbuf_mdl:
		{
			strEqpType = "ums";						
		}
		break;
	case em_audmix_mdl:
		{
			strEqpType = "audiomix";						
		}
		break;
	case em_mpc_mdl:
		{
			strEqpType = "mpc";						
		}
		break;
	case em_bas_mdl:
		{
			strEqpType = "bap";						
		}
		break;
	case em_vmp_mdl:
		{
			strEqpType = "vmp";						
		}
		break;
	default:   //em_unknow_mdl
		{		
			strEqpType = "";
		}
		break;
	}

	return strEqpType;
}

EMEqpType CBoardCfgLogic::StringToEMEqpType(String strType)
{
	EMEqpType emEqpTy;
	if ( "regserver" == strType )
	{
		emEqpTy = em_adapter_mdl;
	}
	else if( "mediatrans" == strType )
	{
		emEqpTy = em_dataswitch_mdl;
	}
	else if( "ums" == strType )
	{
		emEqpTy = em_netbuf_mdl;	
	}
	else if( "audiomix" == strType )
	{
		emEqpTy = em_audmix_mdl;		
	}
	else if( "mpc" == strType )
	{
		emEqpTy = em_mpc_mdl;		
	}
	else if( "bap" == strType )
	{
		emEqpTy = em_bas_mdl;		
	}
	else if( "vmp" == strType )
	{
		emEqpTy = em_vmp_mdl;		
	}
	else
	{
		emEqpTy = em_unknow_mdl;	
	}

	return emEqpTy;
}

std::vector<CString> CBoardCfgLogic::EMBrdTypeToVector(EMBrdType emBrdType)
{
	std::vector<CString> vecMdlTypeData;
	switch( emBrdType )  //单板类型
	{
	case em_eapu_brd:
		{
			//vecMdlTypeData.push_back("audiomix");   //目前需求：一种模式不显示
		}
		break;
	case em_mpc_brd:
		{
			//vecMdlTypeData.push_back("mpc");
		}
		break;
	case em_mpu2ecard_brd:
		{
			vecMdlTypeData.push_back("bap");
			vecMdlTypeData.push_back("vmp");
		}
		break;
	case em_is22_brd:
		{
			//vecMdlTypeData.push_back("ums");			
		}
		break;
	case em_cri2_brd:
		{
			//vecMdlTypeData.push_back("regserver");	
			//vecMdlTypeData.push_back("mediatrans");		//目前需求：一种模式不显示
		}
		break;
	default:   //em_unknow_brd
		{		
		}
		break;
	}

	return vecMdlTypeData;
}

BOOL CBoardCfgLogic::CheckPageDataChangeToSave()
{
// 	String strOrgMdlName = m_tTBoardInfoSel.m_tBrdMode->m_szEqpAlias;
// 	String strOrgMdlType = EMEqpTypeToString(m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType);

	if ( GetMdlDataChange() )
	{
// 		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
// 		MSG_BOX( nMsgBoxRet, "单板模块信息有改动，是否保存？" );
// 		if ( MSGBOX_OK == nMsgBoxRet )
// 		{
			IArgs arg("");
			//保存单板模式
			if ( !OnBtnBoardModeSave(arg) )
			{
				return FALSE;
			}
// 		}
// 		else    //取消则恢复原始模式名称和类型
// 		{
// 			UIFACTORYMGR_PTR->SetCaption( m_strEdtBoardModeName, strOrgMdlName, m_pWndTree );
// 			
// 			//模式类别
// 			EMBrdType emBrdType = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType;
// 			std::vector<CString> vecBrdType =  EMBrdTypeToVector(emBrdType);
// 			UIFACTORYMGR_PTR->SetComboListData( m_strComboboxModeType, vecBrdType, m_pWndTree );  //设置对应单板类型combo列表
// 			if ( vecBrdType.size() > 0 )
// 			{
// 				UIFACTORYMGR_PTR->SetComboText( m_strComboboxModeType, strOrgMdlType, m_pWndTree );  //设置单板默认类型名
// 			}
// 		}
	}
	
	return TRUE;
}

BOOL CBoardCfgLogic::CheckPageBoardMdlData()
{
	if ( em_eapu_brd == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType )
	{
		String strMdlName1;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixName1, strMdlName1, m_pWndTree );   
		String strMdlName2;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixName2, strMdlName2, m_pWndTree );  
		
		String strAudmixNum1;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixNum1, strAudmixNum1, m_pWndTree );
		String strAudmixNum2;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixNum2, strAudmixNum2, m_pWndTree );
		u8 byAudmixNum1 = atoi(strAudmixNum1.c_str());
		u8 byAudmixNum2 = atoi(strAudmixNum2.c_str());

		if ( strMdlName1.empty() )
		{
			MSG_BOX_OK("混音器1别名不能为空！");
			UIFACTORYMGR_PTR->SetFocus( m_strEdtAudioMixName1, m_pWndTree );
			return FALSE;
		}
		else if ( strMdlName2.empty() )
		{
			MSG_BOX_OK("混音器2别名不能为空！");
			UIFACTORYMGR_PTR->SetFocus( m_strEdtAudioMixName2, m_pWndTree );
			return FALSE;
		}
		else if ( CUmstoolCommon::IsInvalidChar( strMdlName1, 3, " ", ",", "，" ) )
		{
			MSG_BOX_OK("混音器1别名包含非法的字符：空格或逗号！");
			UIFACTORYMGR_PTR->SetFocus( m_strEdtAudioMixName1, m_pWndTree );
			return FALSE;
		}
		else if ( CUmstoolCommon::IsInvalidChar( strMdlName2, 3, " ", ",", "，" ) )
		{
			MSG_BOX_OK("混音器2别名包含非法的字符：空格或逗号！");
			UIFACTORYMGR_PTR->SetFocus( m_strEdtAudioMixName2, m_pWndTree );
			return FALSE;
		}
		else if ( strAudmixNum1.empty() )
		{
			MSG_BOX_OK("混音器1最大混音路数不能为空！");
			UIFACTORYMGR_PTR->SetFocus( m_strEdtAudioMixNum1, m_pWndTree );
			return FALSE;
		}
		else if ( strAudmixNum2.empty() )
		{
			MSG_BOX_OK("混音器2最大混音路数不能为空！");
			UIFACTORYMGR_PTR->SetFocus( m_strEdtAudioMixNum2, m_pWndTree );
			return FALSE;
		}
		//需求：混音器通道数允许配置范围：0、2-64间的整数 -- 20140701 by xhx
		else if ( 1 == byAudmixNum1 )
		{
			MSG_BOX_OK("混音器通道数允许配置范围：0、2-64间的整数！");
			UIFACTORYMGR_PTR->SetFocus( m_strEdtAudioMixNum1, m_pWndTree );
			return FALSE;
		}
		else if ( 1 == byAudmixNum2 )
		{
			MSG_BOX_OK("混音器通道数允许配置范围：0、2-64间的整数！");
			UIFACTORYMGR_PTR->SetFocus( m_strEdtAudioMixNum2, m_pWndTree );
			return FALSE;
		}
		//混音器通道数之和不大于64
		else if ( byAudmixNum1 + byAudmixNum2 > 64 )
		{
			MSG_BOX_OK("混音器最大混音路数不能超过64！");
			UIFACTORYMGR_PTR->SetFocus( m_strEdtAudioMixNum1, m_pWndTree );
			return FALSE;
		}
	} 
	else
	{
		String strMdlName;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtBoardModeName, strMdlName, m_pWndTree );   

		String strMdlType;
		UIFACTORYMGR_PTR->GetComboText( m_strComboboxModeType, strMdlType, m_pWndTree );

		if ( strMdlName.empty() )
		{
			MSG_BOX_OK("模块名称不能为空！");
			UIFACTORYMGR_PTR->SetFocus( m_strEdtBoardModeName, m_pWndTree );
			
			return FALSE;
		}
		else if ( CUmstoolCommon::IsInvalidChar( strMdlName, 3, " ", ",", "，" ) )
		{
			MSG_BOX_OK("模块名称包含非法的字符：空格或逗号！");
			UIFACTORYMGR_PTR->SetFocus( m_strEdtBoardModeName, m_pWndTree );
			
			return FALSE;
		}
		else if ( strMdlType.empty() )
		{
			MSG_BOX_OK("模块类别不能为空！");
			UIFACTORYMGR_PTR->SetFocus( m_strComboboxModeType, m_pWndTree );
			
			return FALSE;
		}
	}

	return TRUE;
}

bool CBoardCfgLogic::OnBoardMdlEditChange( const IArgs & arg )
{
	if( em_unknow_brd == m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType )  //板子未知   禁止输入  清空模式名
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtBoardModeName, "", m_pWndTree );
		
		return TRUE;
	}

	String strOrgMdlName = m_tTBoardInfoSel.m_tBrdMode[0].m_szEqpAlias;
	String strOrgMdlType = EMEqpTypeToString(m_tTBoardInfoSel.m_tBrdMode[0].m_emEqpType);
	
	String strMdlName;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtBoardModeName, strMdlName, m_pWndTree );   
	
	String strMdlType;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxModeType, strMdlType, m_pWndTree );
	
	if ( strMdlName != strOrgMdlName )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, true, m_pWndTree );
		SetMdlDataChange(TRUE);
	}
	else if ( strMdlType != strOrgMdlType )
	{
		if ( strMdlType != "" && strMdlType != "无" )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, true, m_pWndTree );
			SetMdlDataChange(TRUE);
		}
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, false, m_pWndTree );

		SetMdlDataChange(FALSE);
	}

	return true;
}

bool CBoardCfgLogic::OnBoardAudioMixNameEditChange( const IArgs & arg )
{
	if( em_eapu_brd != m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixName1, "", m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixName2, "", m_pWndTree );
		return TRUE;
	}

	String strOrgMixName1 = m_tTBoardInfoSel.m_tBrdMode[0].m_szEqpAlias;
	String strOrgMixName2 = m_tTBoardInfoSel.m_tBrdMode[1].m_szEqpAlias;
	
	String strMixName1;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixName1, strMixName1, m_pWndTree );   
	String strMixName2;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixName2, strMixName2, m_pWndTree ); 
	
	if ( ( strMixName1 != strOrgMixName1 ) || ( strMixName2 != strOrgMixName2 ) )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, true, m_pWndTree );
		m_bApuMdlNameChange = TRUE;
		SetMdlDataChange(TRUE);
	}
	else
	{
		m_bApuMdlNameChange = FALSE;
		if ( !m_bApuMdlNum1Change && !m_bApuMdlNum2Change )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, false, m_pWndTree );
			SetMdlDataChange(FALSE);
		}
	}
	
	return true;
}

bool CBoardCfgLogic::OnBoardAudioMixNum1EditChange( const IArgs & arg )
{
	if( em_eapu_brd != m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType )
	{
		return TRUE;
	}

	String strMixNum;
	u8 byMixNum = 0;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixNum1, strMixNum, m_pWndTree );
	if ( "" != strMixNum )
	{
		byMixNum = atoi(strMixNum.c_str());
		s32 nLen = strMixNum.size();
		if ( (strMixNum.at(nLen - 1) > '9') || (strMixNum.at(nLen - 1) < '0') )
		{
			String strMixNumShow = strMixNum.substr(0, nLen - 1);
			byMixNum = atoi(strMixNumShow.c_str());
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum1, strMixNumShow, m_pWndTree );
		}

		if ( nLen != 1 )
		{
			if ( (strMixNum.at(0) > '9') || (strMixNum.at(0) < '0') )
			{
				String strMixNumShow = strMixNum.substr(1, nLen - 1);
				byMixNum = atoi(strMixNumShow.c_str());
				UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum1, strMixNumShow, m_pWndTree );
			}
		}
		
		if ( byMixNum > 64 )
		{
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum1, "64", m_pWndTree );
			byMixNum = 64;
		}  
	}     
	
	UIFACTORYMGR_PTR->SetFocus( m_strEdtAudioMixNum1, m_pWndTree );

	u8 byOrgAudmixNum = m_tTBoardInfoSel.m_tBrdMode[0].m_byAudmixNum;
	if ( byOrgAudmixNum != byMixNum )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, true, m_pWndTree );
		m_bApuMdlNum1Change = TRUE;
		SetMdlDataChange(TRUE);
	}
	else
	{
		m_bApuMdlNum1Change = FALSE;
		if ( !m_bApuMdlNameChange && !m_bApuMdlNum2Change )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, false, m_pWndTree );
			SetMdlDataChange(FALSE);
		}
	}
	
	return true;
}

bool CBoardCfgLogic::OnBoardAudioMixNum2EditChange( const IArgs & arg )
{
	if( em_eapu_brd != m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType )
	{
		return TRUE;
	}
	
	String strMixNum;
	u8 byMixNum = 0;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtAudioMixNum2, strMixNum, m_pWndTree );
	if ( "" != strMixNum )
	{
		byMixNum = atoi(strMixNum.c_str());
		s32 nLen = strMixNum.size();
		if ( (strMixNum.at(nLen - 1) > '9') || (strMixNum.at(nLen - 1) < '0') )
		{
			String strMixNumShow = strMixNum.substr(0, nLen - 1);
			byMixNum = atoi(strMixNumShow.c_str());
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum2, strMixNumShow, m_pWndTree );
		}

		if ( nLen != 1 )
		{
			if ( (strMixNum.at(0) > '9') || (strMixNum.at(0) < '0') )
			{
				String strMixNumShow = strMixNum.substr(1, nLen - 1);
				byMixNum = atoi(strMixNumShow.c_str());
				UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum2, strMixNumShow, m_pWndTree );
			}
		}
		
		if ( byMixNum > 64 )
		{
			UIFACTORYMGR_PTR->SetCaption( m_strEdtAudioMixNum2, "64", m_pWndTree );
			byMixNum = 64;
		}  
	}     
	
	UIFACTORYMGR_PTR->SetFocus( m_strEdtAudioMixNum2, m_pWndTree );
	
	u8 byOrgAudmixNum = m_tTBoardInfoSel.m_tBrdMode[1].m_byAudmixNum;
	if ( byOrgAudmixNum != byMixNum )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, true, m_pWndTree );
		m_bApuMdlNum2Change = TRUE;
		SetMdlDataChange(TRUE);
	}
	else
	{
		m_bApuMdlNum2Change = FALSE;
		if ( !m_bApuMdlNameChange && !m_bApuMdlNum1Change )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardModeSave, false, m_pWndTree );
			SetMdlDataChange(FALSE);
		}
	}

	return true;
}

bool CBoardCfgLogic::OnClickBoardLstBlack( const IArgs & arg )
{
	ResetBoardPageControl();

	return true;
}

HRESULT CBoardCfgLogic::OnBoardUpgradeRsp( WPARAM wparam, LPARAM lparam)
{ 
	BOOL* pBrdUpGradeRsp = (BOOL*)( wparam );
	if ( NULL != pBrdUpGradeRsp )
	{
		if( !*pBrdUpGradeRsp )
		{
			MESSAGEWND("单板升级失败！");
			UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
		}
		else    //升级完成关闭升级窗口
		{	
			s32 nResult = 0;
			UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
		}
	}

	return S_OK;
}

HRESULT CBoardCfgLogic::OnBoardBeginUpgrade( WPARAM wparam, LPARAM lparam)
{ 
	LPCTSTR strCurTransFile = (LPCTSTR)wparam;
	TTPBrdUpGrade tBrdUpGrade;
	tBrdUpGrade.m_byLayer = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdLayer;
	tBrdUpGrade.m_bySlot = m_tTBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdSlot;
	memcpy( tBrdUpGrade.m_szFileName, strCurTransFile, TP_UPGRADE_FILENAME_LENGTH );
	COMMONMGRIFPTR->BoardUpgradeReq(tBrdUpGrade);	

	return S_OK;
}

HRESULT CBoardCfgLogic::OnConfCount( WPARAM wparam, LPARAM lparam)
{
	if ( !GetMdlDataChange() )
	{
		UpdateBtnState();
	}
	
	return S_OK;
}
