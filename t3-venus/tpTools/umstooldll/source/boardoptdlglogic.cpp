// boardoptdlglogic.cpp: implementation of the CBoardOptDlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umstooldll.h"
#include "boardoptdlglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBoardOptDlgLogic::CBoardOptDlgLogic():
m_strComboboxBoardType("ComboboxBoardType"),
m_strEdtIpAddr("EdtIpAddr"),
m_strStcBoardTypeShow("StcBoardTypeShow"),  
m_strStcShowLayarNo("StcShowLayarNo"),     
m_strStcShowSlotNo("StcShowSlotNo"),
m_strBtnBoardOptOk("BtnBoardOk"),
m_strBtnTvwBoardOptOk("BtnTvwBoardOk")   
{

}

CBoardOptDlgLogic::~CBoardOptDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CBoardOptDlgLogic::RegMsg()
{    
    //REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CBoardOptDlgLogic::OnDisConnect, m_pLogic, CBoardOptDlgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_BOARDSELDATA_Click, CBoardOptDlgLogic::OnBoardSelData, BOARDOPTLOGICRPTR, CBoardOptDlgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_TVWBOARDSELDATA_Click, CBoardOptDlgLogic::OnTvwBoardSelData, BOARDOPTLOGICRPTR, CBoardOptDlgLogic );

}

void CBoardOptDlgLogic::UnRegMsg()
{

}

bool CBoardOptDlgLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CBoardOptDlgLogic::InitWnd", CBoardOptDlgLogic::InitWnd, BOARDOPTLOGICRPTR, CBoardOptDlgLogic);

	REG_GOBAL_MEMBER_FUNC( "CBoardOptDlgLogic::OnBtnOptBoardOk", CBoardOptDlgLogic::OnBtnOptBoardOk, BOARDOPTLOGICRPTR, CBoardOptDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardOptDlgLogic::OnBtnOptBoardCancel", CBoardOptDlgLogic::OnBtnOptBoardCancel, BOARDOPTLOGICRPTR, CBoardOptDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardOptDlgLogic::OnBtnOptTvwBoardOk", CBoardOptDlgLogic::OnBtnOptTvwBoardOk, BOARDOPTLOGICRPTR, CBoardOptDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardOptDlgLogic::OnBtnOptTvwBoardCancel", CBoardOptDlgLogic::OnBtnOptTvwBoardCancel, BOARDOPTLOGICRPTR, CBoardOptDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CBoardOptDlgLogic::OnBoardOptIpChange", CBoardOptDlgLogic::OnBoardOptIpChange, BOARDOPTLOGICRPTR, CBoardOptDlgLogic ); 
	
	return true;
}

bool CBoardOptDlgLogic::UnRegFunc()
{

	return true;
}

bool CBoardOptDlgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

    return true;
}

void CBoardOptDlgLogic::Clear()
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrBoardOptDlg );
}

bool CBoardOptDlgLogic::OnBtnOptBoardOk( const IArgs & arg )
{  
	Value_IpEditData valIp;
	UIFACTORYMGR_PTR->GetPropertyValue(valIp, m_strEdtIpAddr, m_pWndTree); 

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtIpAddr , strCaption , m_pWndTree );

	m_tBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_dwBrdIP = htonl(valIp.dwIP);
	
	String strBrdType;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxBoardType, strBrdType, m_pWndTree );

	if ( strBrdType == "APU2" )
	{
		m_tBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType = em_eapu_brd;
	}
	else if ( strBrdType == "MPC2" )
	{
		m_tBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType = em_mpc_brd;
	}
	else if ( strBrdType == "MPU2" )
	{
		m_tBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType = em_mpu2ecard_brd;
	}
	else if ( strBrdType == "IS2.2" )
	{
		m_tBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType = em_is22_brd;
	}
	else if ( strBrdType == "CRI2" )
	{
		m_tBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType = em_cri2_brd;
	}

	u32 dwData = DATAMGRPTR->GetConfCountData();			
	if ( dwData > 0 )
	{
		MSG_BOX_OK("已有会议开启，不能进行配置");
	}
	else
	{
		if( em_BOARDOPT_MODIFY == m_emBoardType )
		{
			if ( strCaption.empty() )
			{
				MSG_BOX_OK("IP地址不能为空");
				return false;
			}
			
			if ( !CCallAddr::IsValidIpV4(valIp.dwIP) )
			{   
				MSG_BOX_OK("IP地址非法");
				return false;
			}
			
			u16 nRet = COMMONMGRIFPTR->BoardModifyReq(m_tBoardInfoSel.m_tBrdCfg);
			if ( nRet != NO_ERROR )
			{
				MESSAGEWND( "修改单板请求发送失败" );
			}
		}
		else
		{
			if ( strBrdType.empty() )
			{
				MSG_BOX_OK("单板类型不能为空");
				return false;
			}
			
			if ( strCaption.empty() )
			{
				MSG_BOX_OK("IP地址不能为空");
				return false;
			}
			
			if ( !CCallAddr::IsValidIpV4(valIp.dwIP) )
			{   
				MSG_BOX_OK("IP地址非法");
				return false;
			}
			
			u16 nRet = COMMONMGRIFPTR->BoardAddReq(m_tBoardInfoSel.m_tBrdCfg);
			if ( nRet != NO_ERROR )
			{
				MESSAGEWND( "添加单板请求发送失败" );
			}
		}
	}

	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrBoardOptDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchBoardOptClean", m_pWndTree );

	return true;
}

bool CBoardOptDlgLogic::OnBtnOptBoardCancel( const IArgs & arg )
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrBoardOptDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchBoardOptClean", m_pWndTree );
	//UIFACTORYMGR_PTR->SetFocus( m_strEdtIpAddr, m_pWndTree );

	return true;
}

bool CBoardOptDlgLogic::OnBtnOptTvwBoardOk( const IArgs & arg )
{
	Value_IpEditData valIp;
	UIFACTORYMGR_PTR->GetPropertyValue(valIp, m_strEdtIpAddr, m_pWndTree); 
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtIpAddr , strCaption , m_pWndTree );

	if ( strCaption.empty() )
	{
		MSG_BOX_OK("IP地址不能为空");
		return false;
	}

	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) )
	{   
		MSG_BOX_OK("IP地址非法");
		return false;
	}

	TTPBrdPos tTPBrdPos;
	tTPBrdPos.m_dwBrdIP = htonl(valIp.dwIP);
	tTPBrdPos.m_byBrdLayer = m_tHduCfgSel.m_byLayer;
	tTPBrdPos.m_byBrdSlot = m_tHduCfgSel.m_bySlot;

	if( em_TVWBOARDOPT_MODIFY == m_emBoardType )
	{
		u16 nRet = COMMONMGRIFPTR->TvwBoardModifyReq(tTPBrdPos);
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "修改电视墙单板请求发送失败" );
		}
	}
	else
	{
		u16 nRet = COMMONMGRIFPTR->TvwBoardAddReq(tTPBrdPos);
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "添加电视墙单板请求发送失败" );
		}
	}

	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrBoardOptDlg );
	
	return true;
}

bool CBoardOptDlgLogic::OnBtnOptTvwBoardCancel( const IArgs & arg )
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrBoardOptDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchBoardOptClean", m_pWndTree );

	return true;
}

HRESULT CBoardOptDlgLogic::OnBoardSelData( WPARAM wparam, LPARAM lparam)
{	
	m_emBoardType = static_cast<EM_BOARDOPT_TYPE>(lparam);

	m_tBoardInfoSel = *reinterpret_cast<TTPBrdInfo*>(wparam);
	s32 nLayar  = m_tBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdLayer;
	s32 nSlot   = m_tBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_byBrdSlot;

	//设置数据到控
	s8 chLayar[8] = {0};
	sprintf( chLayar, "%d", nLayar );
	UIFACTORYMGR_PTR->SetCaption( m_strStcShowLayarNo, chLayar, m_pWndTree );
	
	s8 chSlot[8] = {0};
	sprintf( chSlot, "%d", nSlot );
	UIFACTORYMGR_PTR->SetCaption( m_strStcShowSlotNo, chSlot, m_pWndTree );		

	if ( em_BOARDOPT_MODIFY == m_emBoardType )    //修改
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchBoardModify", m_pWndTree );

		u32_ip dwIp = m_tBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_dwBrdIP;

		String strBrdType;
		EMBrdType emEqpType = m_tBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_emBrdType;
		switch( emEqpType )
		{
		case em_eapu_brd:
			{
				strBrdType = "APU2";
			}
			break;
		case em_mpc_brd:
			{
				strBrdType = "MPC2";
			}
			break;
		case em_mpu2ecard_brd:
			{
				strBrdType = "MPU2";				
			}
			break;
		case em_is22_brd:
			{
				strBrdType = "IS2.2";				
			}
			break;
		case em_cri2_brd:
			{
				strBrdType = "CRI2";				
			}
			break;
		default:
			{
			}
			break;
		}

		UIFACTORYMGR_PTR->SetCaption( m_strStcBoardTypeShow, strBrdType, m_pWndTree );

		String strIP;
		strIP += CUmstoolCommon::GetIpStr(dwIp);
		UIFACTORYMGR_PTR->SetCaption( m_strEdtIpAddr, strIP, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchBoardAdd", m_pWndTree );

		//单板类型
		std::vector<CString> vecListData;
		if ( nSlot == 0 || nSlot == 9 )
		{
			vecListData.push_back("MPC2");
		}
		else if ( nSlot == 8 )
		{
			vecListData.push_back("IS2.2");
		}
		else
		{
			vecListData.push_back("APU2");
			vecListData.push_back("CRI2");
			vecListData.push_back("MPU2");
		}
		UIFACTORYMGR_PTR->SetComboListData( m_strComboboxBoardType, vecListData, m_pWndTree );

	}

	return S_OK;
}

HRESULT CBoardOptDlgLogic::OnTvwBoardSelData( WPARAM wparam, LPARAM lparam)
{
	m_emBoardType = static_cast<EM_BOARDOPT_TYPE>(lparam);
	
	m_tHduCfgSel = *reinterpret_cast<THduCfg*>(wparam);
	s32 nLayar  = m_tHduCfgSel.m_byLayer;
	s32 nSlot   = m_tHduCfgSel.m_bySlot;
	
	//设置数据到控
	s8 chLayar[8] = {0};
	sprintf( chLayar, "%d", nLayar );
	UIFACTORYMGR_PTR->SetCaption( m_strStcShowLayarNo, chLayar, m_pWndTree );
	
	s8 chSlot[8] = {0};
	sprintf( chSlot, "%d", nSlot );
	UIFACTORYMGR_PTR->SetCaption( m_strStcShowSlotNo, chSlot, m_pWndTree );		
	
	if ( em_TVWBOARDOPT_MODIFY == m_emBoardType )    //修改
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchTvwBoardModify", m_pWndTree );
		
		u32_ip dwIp = m_tHduCfgSel.m_dwIP;
		String strIP;
		strIP += CUmstoolCommon::GetIpStr(dwIp);
		UIFACTORYMGR_PTR->SetCaption( m_strEdtIpAddr, strIP, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchTvwBoardAdd", m_pWndTree );

	}

	return S_OK;
}

bool CBoardOptDlgLogic::OnBoardOptIpChange( const IArgs & arg )
{
	Value_WindowCaption valIp;
	UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtIpAddr, m_pWndTree );   
	
	u32_ip dwIp = inet_addr(valIp.strCaption.c_str());

	if( em_BOARDOPT_MODIFY == m_emBoardType )
	{
		if( dwIp != m_tBoardInfoSel.m_tBrdCfg.m_tBrdPos.m_dwBrdIP )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardOptOk, true, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnBoardOptOk, false, m_pWndTree );
		}
	}
	else if ( em_TVWBOARDOPT_MODIFY == m_emBoardType )
	{
		if( dwIp != m_tHduCfgSel.m_dwIP )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardOptOk, true, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwBoardOptOk, false, m_pWndTree );
		}
	}

	return S_OK;
}