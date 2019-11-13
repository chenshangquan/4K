// umscfglogic.cpp: implementation of the CUmsCfgLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h" 
#include "umscfglogic.h"


// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUmsCfgLogic::CUmsCfgLogic()
: m_strEdtUmsIp( "IPCtrlUmsIP" )
, m_strEdtSubnetMask( "IPCtrlSubnetMask" )
, m_strEdtGateWay( "IPCtrlGateway" )
, m_strEdtSipIP( "IPCtrlSipIP" )
, m_strBtnGKSwitch( "BtnGKSwitch" )
, m_strEdtGKIP( "IPCtrlGKIP" )
, m_strBtnSave( "BtnSave" )
, m_strBtnReduction( "BtnReduction" )
, m_strBtnExport( "BtnExport" )
{
	m_bIsUmsIPChanged = FALSE;
	m_bIsSubnetMaskChanged = FALSE;
	m_bIsGateWayChanged = FALSE;
	m_bIsSipIPChanged = FALSE;
	m_bIsGKIPSwitchChanged = FALSE;
	m_bIsGKIPChanged = FALSE;
}

CUmsCfgLogic::~CUmsCfgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CUmsCfgLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_UMS_ETHNETINFO_NOTIFY, CUmsCfgLogic::OnEthnetInfoNty, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_MSG_HANDLER( UI_UMS_REG_INFO_NOTIFY, CUmsCfgLogic::OnSipInfoRsp, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_MSG_HANDLER( UI_UMS_REG_SERV_RSP, CUmsCfgLogic::OnRegSipResult, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_MSG_HANDLER( UI_CNS_REG_GK_NTY, CUmsCfgLogic::OnGKInfoRsp, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_MSG_HANDLER( UI_CNS_REG_GK_RSP, CUmsCfgLogic::OnRegGKResult, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_MSG_HANDLER( UI_UMS_CMD_TIMEOUT, CUmsCfgLogic::OnTimeOut, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_REG_NTY, CUmsCfgLogic::OnSipInfoNty, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_GK_NTY, CUmsCfgLogic::OnGKInfoNty, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_CONFCOUNT_NTY, CUmsCfgLogic::OnConfCount, UMSCFGLOGICRPTR, CUmsCfgLogic );
}

void CUmsCfgLogic::UnRegMsg()
{
}

bool CUmsCfgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CUmsCfgLogic::InitWnd", CUmsCfgLogic::InitWnd, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CUmsCfgLogic::OnBtnSwitchGKClick", CUmsCfgLogic::OnBtnSwitchGKClick, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CUmsCfgLogic::OnBtnSaveClick", CUmsCfgLogic::OnBtnSaveClick, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CUmsCfgLogic::OnBtnReductionClick", CUmsCfgLogic::OnBtnReductionClick, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CUmsCfgLogic::OnBtnExportClick", CUmsCfgLogic::OnBtnExportClick, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CUmsCfgLogic::OnChangedIPCtrlUmsIP", CUmsCfgLogic::OnChangedIPCtrlUmsIP, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CUmsCfgLogic::OnChangedIPCtrlSubnetMask", CUmsCfgLogic::OnChangedIPCtrlSubnetMask, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CUmsCfgLogic::OnChangedIPCtrlGateway", CUmsCfgLogic::OnChangedIPCtrlGateway, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CUmsCfgLogic::OnChangedIPCtrlSipIP", CUmsCfgLogic::OnChangedIPCtrlSipIP, UMSCFGLOGICRPTR, CUmsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CUmsCfgLogic::OnChangedIPCtrlGKIP", CUmsCfgLogic::OnChangedIPCtrlGKIP, UMSCFGLOGICRPTR, CUmsCfgLogic );

	return true;
}

bool CUmsCfgLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CUmsCfgLogic::InitWnd" );
	return true;
}

bool CUmsCfgLogic::InitWnd(  const IArgs & arg )
{
	CWndLogicBase::InitWnd( arg );

	return true;
}

void CUmsCfgLogic::Clear()
{
	//RecductUmsCfg();
	ResetAllData();
	//UpdBtnState();
}

bool CUmsCfgLogic::OnBtnSwitchGKClick( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}

	bool bUseGK = false;
	Value_SwitchState valueState;
    valueState.bState = false;
	bool bRe = UIFACTORYMGR_PTR->GetPropertyValue( valueState, m_strBtnGKSwitch, m_pWndTree );
	bUseGK = valueState.bState;

	if ( bUseGK )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtGKIP);
    }
    else
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtGKIP);
    }


	TTPGKCfg tOldGKInfo = DATAMGRPTR->GetGkCfgData();
	if ( (BOOL)bUseGK != tOldGKInfo.bUsed )
	{
		m_bIsGKIPSwitchChanged = TRUE;
	}
	else
	{
		m_bIsGKIPSwitchChanged = FALSE;
	}
	
	UpdBtnState();

    return true;
}

bool CUmsCfgLogic::OnBtnSaveClick( const IArgs& args )
{
	if ( m_bIsUmsIPChanged || m_bIsSubnetMaskChanged || m_bIsGateWayChanged || m_bIsSipIPChanged || m_bIsGKIPSwitchChanged || m_bIsGKIPChanged )
	{
		u32 dwData = DATAMGRPTR->GetConfCountData();
		if ( dwData > 0 )
		{
			MSG_BOX_OK( _T("有会议进行中，不能配置") );
			
			RecductUmsCfg();
			Clear();
			UpdBtnState();
			UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree );
			
			return true;
		}

		if ( CheckAll() )
		{
			SaveAll();
		}
	}

	return true;
}

bool CUmsCfgLogic::OnBtnReductionClick( const IArgs& args )
{
	RecductUmsCfg();
	
	return true;
}

bool CUmsCfgLogic::OnBtnExportClick( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", NULL, g_stcStrExpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchExportConfig", NULL, g_stcStrExpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrExpCommonDlg );	

	return true;
}

bool CUmsCfgLogic::OnChangedIPCtrlUmsIP( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}

	TTPEthnetInfo tOldEthnetInfo = DATAMGRPTR->GetEthnetCfgData();
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldEthnetInfo.dwIP;
	String strOldCaption = inet_ntoa(tAddr);

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtUmsIp, strCaption, m_pWndTree);
	DWORD dwUmsIP = inet_addr(strCaption.c_str());
	if ( "" == strCaption )
	{
		strCaption = "0.0.0.0";
	}

	if ( dwUmsIP != tOldEthnetInfo.dwIP || strCaption != strOldCaption )
	{
		m_bIsUmsIPChanged = TRUE;
	}
	else
	{
		m_bIsUmsIPChanged = FALSE;
	}

	UpdBtnState();

	return true;
}

bool CUmsCfgLogic::OnChangedIPCtrlSubnetMask( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}

	TTPEthnetInfo tOldEthnetInfo = DATAMGRPTR->GetEthnetCfgData();
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldEthnetInfo.dwMask;
	String strOldCaption = inet_ntoa(tAddr);
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSubnetMask, strCaption, m_pWndTree);
	DWORD dwSubnetMask = inet_addr(strCaption.c_str());
	if ( "" == strCaption )
	{
		strCaption = "0.0.0.0";
	}
	
	if ( dwSubnetMask != tOldEthnetInfo.dwMask || strCaption != strOldCaption )
	{
		m_bIsSubnetMaskChanged = TRUE;
	}
	else
	{
		m_bIsSubnetMaskChanged = FALSE;
	}
	
	UpdBtnState();
	
	return true;
}

bool CUmsCfgLogic::OnChangedIPCtrlGateway( const IArgs& args )
{	
	if (m_pWndTree == NULL)
	{
		return false;
	}

	TTPEthnetInfo tOldEthnetInfo = DATAMGRPTR->GetEthnetCfgData();
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldEthnetInfo.dwGateWay;
	String strOldCaption = inet_ntoa(tAddr);
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGateWay, strCaption, m_pWndTree);
	DWORD dwGateWay = inet_addr(strCaption.c_str());
	if ( "" == strCaption )
	{
		strCaption = "0.0.0.0";
	}

	if ( dwGateWay != tOldEthnetInfo.dwGateWay /*|| ( dwGateWay == tOldEthnetInfo.dwGateWay && dwGateWay == 0 )*/
												|| strCaption != strOldCaption )
	{
		m_bIsGateWayChanged = TRUE;
	}
	else
	{
		m_bIsGateWayChanged = FALSE;
	}

	
	
	UpdBtnState();
	
	return true;
}

bool CUmsCfgLogic::OnChangedIPCtrlSipIP( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}

	TTPSipRegistrarCfg tOldSipInfo = DATAMGRPTR->GetSipCfgData();
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldSipInfo.dwRegIP;
	String strOldCaption = inet_ntoa(tAddr);
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSipIP, strCaption, m_pWndTree);
	DWORD dwSipIP = inet_addr(strCaption.c_str());
	if ( "" == strCaption )
	{
		strCaption = "0.0.0.0";
	}
	
	if ( dwSipIP != tOldSipInfo.dwRegIP || strCaption != strOldCaption )
	{
		m_bIsSipIPChanged = TRUE;
	}
	else
	{
		m_bIsSipIPChanged = FALSE;
	}
	
	UpdBtnState();
	
	return true;
}

bool CUmsCfgLogic::OnChangedIPCtrlGKIP( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}

	TTPGKCfg tOldGKInfo = DATAMGRPTR->GetGkCfgData();
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldGKInfo.dwGKIP;
	String strOldCaption = inet_ntoa(tAddr);
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGKIP, strCaption, m_pWndTree);
	DWORD dwGKIP = inet_addr(strCaption.c_str());
	if ( "" == strCaption )
	{
		strCaption = "0.0.0.0";
	}

	if ( dwGKIP != tOldGKInfo.dwGKIP || strCaption != strOldCaption )
	{
		m_bIsGKIPChanged = TRUE;
	}
	else
	{
		m_bIsGKIPChanged = FALSE;
	}
	
	UpdBtnState();
	
	return true;
}

LRESULT CUmsCfgLogic::OnEthnetInfoNty( WPARAM wParam, LPARAM lParam )
{
	SetEthnetInfo();

	return NO_ERROR;
}

LRESULT CUmsCfgLogic::OnSipInfoNty( WPARAM wParam, LPARAM lParam )
{
	BOOL32 bRet = static_cast<BOOL32>(lParam);

// 	if ( bRet == FALSE )
// 	{
// 		MSG_BOX_OK( "sip服务器注册失败");
// 	}

	SetSipInfo();

	return NO_ERROR;
}

LRESULT CUmsCfgLogic::OnSipInfoRsp( WPARAM wParam, LPARAM lParam )
{
	BOOL32 bRet = static_cast<BOOL32>(lParam);

// 	if ( bRet == FALSE )
// 	{
// 		MSG_BOX_OK( "sip服务器注册失败");
// 	}

	SetSipInfo();
	
	return NO_ERROR;
}

LRESULT CUmsCfgLogic::OnRegSipResult( WPARAM wParam, LPARAM lParam )
{
	TUCSipRegResult tRegResult = *reinterpret_cast<TUCSipRegResult*>(wParam);
	EmTpCnsRegUms tRegUms = (EmTpCnsRegUms)tRegResult.m_emTpCnsRegUms;
	CString strErr;
	switch( tRegUms )
	{
	case tp_CnsRegRet_Unknow:
		{
			strErr = "未知的SIP服务器";
		}
		break;
	case tp_CnsRegRet_Success:
		{
			strErr = "注册SIP服务器成功";
			MESSAGEWND( strErr );
			
			return NO_ERROR;
		}
		break;
	case tp_CnsRegRet_MaxRegNum:
		{
			strErr = "注册个数已达到最大值";
		}
		break;
	case tp_CnsRegRet_MaxAliasNum:
		{
			strErr = "注册别名的个数已达到最大值";
		}
		break;
	case tp_CnsRegRet_MsgError:
		{
			strErr = "注册消息错误";
		}
		break;
	case tp_CnsRegRet_AliasRepeat:
		{
			if ( tRegResult.m_nAliasNum == 0 )
			{
				strErr = "SIP服务器注册别名重复";
				MESSAGEWND( strErr );
				return NO_ERROR;
			}
			
			for ( s32 nIndex = 0; nIndex < tRegResult.m_nAliasNum; nIndex++ )
			{
				strErr = "注册 ";
				strErr += tRegResult.m_atTPAlias[nIndex].m_abyAlias;
				strErr += " 别名重复";
				MESSAGEWND( strErr );
			}
			
			return NO_ERROR;
		}
		break;
	case tp_CnsRegRet_UnReg:
		{
			strErr = "未找到删除记录";
		}
		break;
	case tp_CnsRegRet_SysError:
		{
			strErr = "APP错误";
		}
		break;
	case tp_CnsRegRet_NotFind:
		{
			strErr = "查找失败";
		}
		break;
	case tp_CnsRegRet_Fail:
		{
			strErr = "";
		}
		break;
	case tp_CnsRegRet_Unreachable:
		{
			strErr = "服务器不可达";
		}
		break;
	default:
		{
			strErr = ""; //"未知错误";	2012-8-7 SE石文娟确认未知错误不做提示 by yjj  
		}
		break;
	}
	
	if ( !strErr.IsEmpty() )
	{
		CString strTemp = "注册SIP服务器失败";
		if ( !strErr.IsEmpty() )
		{
			strTemp  = strTemp + ": " + strErr;
		}
		
		MESSAGEWND( strTemp );
	}
	else
	{
		MESSAGEWND( "注册SIP服务器失败" );
	}
	
	return NO_ERROR;
}

LRESULT CUmsCfgLogic::OnGKInfoNty( WPARAM wParam, LPARAM lParam )
{
	BOOL32 bRet = static_cast<BOOL32>(lParam);

	SetGKInfo();
	
	return NO_ERROR;
}

LRESULT CUmsCfgLogic::OnGKInfoRsp( WPARAM wParam, LPARAM lParam )
{
	SetGKInfo();
	
	return NO_ERROR;
}

LRESULT CUmsCfgLogic::OnRegGKResult( WPARAM wParam, LPARAM lParam )
{
	bool bOk = false;
    EmTpCnsRegUms emRe = (EmTpCnsRegUms)wParam;
    
    CString strTemp = "";
    switch( wParam )
    {
        
    case tp_CnsRegRet_Success:		    //成功
        bOk  = true;
        break;
    case tp_CnsRegRet_MaxRegNum:		//注册满
        strTemp = "注册个数以达到最大值";
        break;
    case tp_CnsRegRet_MaxAliasNum:	    //注册满
        strTemp = "注册别名的个数以达到最大值";
        break;
    case tp_CnsRegRet_MsgError:	    	//注册消息错误
        strTemp = "注册消息错误";
        break;
    case tp_CnsRegRet_AliasRepeat:	    //别名重复
        strTemp = "注册别名重复";
        break;
    case tp_CnsRegRet_UnReg:			//删除时，未找到删除记录
        strTemp = "未找到该记录";
        break;
    case tp_CnsRegRet_SysError:		    //APP错误
        strTemp = "APP错误";
        break;
    case tp_CnsRegRet_NotFind:		    //查找失败
        strTemp = "查找失败";
        break;   
    case tp_CnsRegRet_Unreachable:      //服务器不可达
        strTemp = "服务器不可达";
        break;
    default:
        strTemp = "" ;                  //"未知错误";2012-8-7 SE石文娟确认未知错误不做提示 by yjj
        break;
    }
    
    CString strName = "注册GK失败";
    
    if ( bOk )
    {
        MESSAGEWND( "注册GK成功" );
    }
    else
    {   
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + ": " + strTemp;
		}
		
        MESSAGEWND( strName );
	}
	
	return NO_ERROR;
}

LRESULT CUmsCfgLogic::OnTimeOut( WPARAM wParam, LPARAM lParam )
{
//	MSG_BOX_OK( "请求超时" );
	return NO_ERROR;
}

LRESULT CUmsCfgLogic::OnConfCount( WPARAM wparam, LPARAM lparam)
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	
	u32 dwData = DATAMGRPTR->GetConfCountData();
	if ( dwData <= 0 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree );

		UpdBtnState();

		TTPGKCfg tGKInfo = DATAMGRPTR->GetGkCfgData();		
		if ( !tGKInfo.bUsed )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, m_strEdtGKIP);
		}
	}

	return NO_ERROR;
}

bool CUmsCfgLogic::ShowWindow( BOOL32 bShow )
{
	CWndLogicBase::ShowWindow( bShow );

	if ( bShow == false )
	{
		if ( m_bIsUmsIPChanged || m_bIsSubnetMaskChanged || m_bIsGateWayChanged || m_bIsSipIPChanged || m_bIsGKIPSwitchChanged || m_bIsGKIPChanged )
		{
			MSGBOX_RET nResult = MSGBOX_OK;
			MSG_BOX( nResult, "数据有改动是否保存？");
			if (nResult == MSGBOX_OK)
			{	
				u32 dwData = DATAMGRPTR->GetConfCountData();
				if ( dwData > 0 )
				{
					MSG_BOX_OK( _T("有会议进行中，不能配置") );

					RecductUmsCfg();
					Clear();
					UpdBtnState();

					return true;
				}

				bool bCheck = CheckAll();
				if ( bCheck == false )
				{
					return false;
				}
				else
				{
					SaveAll();
				}
			}
			else
			{
				RecductUmsCfg();
				Clear();
				UpdBtnState();
			}
		}
	}

	return true;
}

void CUmsCfgLogic::CheckCtrlState()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	u32 dwData = DATAMGRPTR->GetConfCountData();
	if ( dwData > 0 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree );
		
		UpdBtnState();
		
		TTPGKCfg tGKInfo = DATAMGRPTR->GetGkCfgData();		
		if ( !tGKInfo.bUsed )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, m_strEdtGKIP);
		}
	}

	return;
}

void CUmsCfgLogic::SetEthnetInfo()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	TTPEthnetInfo tEthnetInfo = DATAMGRPTR->GetEthnetCfgData();

 	Value_IpEditData valIp;
//     UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtUmsIp, m_pWndTree ); 
// 	if ( tEthnetInfo.dwIP != valIp.dwIP )
//	{
//		Value_IpEditData valIp;
		valIp.dwIP = ntohl(tEthnetInfo.dwIP);
		UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtUmsIp, m_pWndTree ); 
//	}

// 	UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtSubnetMask, m_pWndTree ); 
// 	if ( tEthnetInfo.dwMask != valIp.dwIP )
//	{
//		Value_IpEditData valIp;
		valIp.dwIP = ntohl(tEthnetInfo.dwMask);
		UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSubnetMask, m_pWndTree ); 
//	}

// 	UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtGateWay, m_pWndTree );
// 	if ( tEthnetInfo.dwGateWay != valIp.dwIP )
// 	{
//		Value_IpEditData valIp;
		valIp.dwIP = ntohl(tEthnetInfo.dwGateWay);
	    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGateWay, m_pWndTree );
//	}

	m_bIsUmsIPChanged = FALSE;
	m_bIsSubnetMaskChanged = FALSE;
	m_bIsGateWayChanged = FALSE;

	UpdBtnState();
}

void CUmsCfgLogic::SetSipInfo()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtSipIP, m_pWndTree );
	if ( pWnd )
	{
		HWND hWnd = ::GetFocus();
		if ( hWnd == pWnd->GetSafeHwnd() )
		{
			return;
		}
	}

	TTPSipRegistrarCfg tSipInfo = DATAMGRPTR->GetSipCfgData();

// 	Value_IpEditData valIp;
//     UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtSipIP, m_pWndTree ); 
// 
// 	if ( tSipInfo.dwRegIP != valIp.dwIP )
// 	{
		Value_IpEditData valIp;
		valIp.dwIP = ntohl(tSipInfo.dwRegIP);
        UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSipIP, m_pWndTree ); 
/*	}*/
	
	m_bIsSipIPChanged = FALSE;
	UpdBtnState();
}

void CUmsCfgLogic::SetGKInfo()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	TTPGKCfg tGKInfo = DATAMGRPTR->GetGkCfgData();

	Value_SwitchState valueState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueState, m_strBtnGKSwitch, m_pWndTree );

		
	valueState.bState = tGKInfo.bUsed;
	UIFACTORYMGR_PTR->SetPropertyValue( valueState, m_strBtnGKSwitch, m_pWndTree );

	u32 dwData = DATAMGRPTR->GetConfCountData();
	if ( dwData <= 0 )
	{
		if ( tGKInfo.bUsed )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtGKIP);
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtGKIP);
		}
	}


// 	Value_IpEditData valIp;
//     UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtGKIP, m_pWndTree );
// 	if ( tGKInfo.dwGKIP != valIp.dwIP )
// 	{
	if ( tGKInfo.bUsed )		//当GK开关为开的时候才刷新ip地址 2013年10月30日  jyy
	{
		Value_IpEditData valIp;
		valIp.dwIP = ntohl(tGKInfo.dwGKIP);
		UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGKIP, m_pWndTree );
	}
/*	}*/

	m_bIsGKIPSwitchChanged = FALSE;
	m_bIsGKIPChanged = FALSE;
	UpdBtnState();
}

bool CUmsCfgLogic::CheckAll()
{
	if ( CheckEthnet() == false )
	{
		return false;
	}
	
	if ( CheckSip() == false )
	{
		return false;
	}
	
	if ( CheckGK() == false )
	{
		return false;
	}
	
	return true;
}

void CUmsCfgLogic::SaveAll()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	//保存Ethnet
	Value_IpEditData valUmsIp;
    UIFACTORYMGR_PTR->GetPropertyValue(valUmsIp, m_strEdtUmsIp, m_pWndTree);
	Value_IpEditData valSubnetMask;
    UIFACTORYMGR_PTR->GetPropertyValue(valSubnetMask, m_strEdtSubnetMask, m_pWndTree);
	Value_IpEditData valGateway;
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 

	TTPEthnetInfo tOldEthnetInfo = DATAMGRPTR->GetEthnetCfgData();

	if ( htonl( valUmsIp.dwIP ) != tOldEthnetInfo.dwIP || htonl( valSubnetMask.dwIP ) != tOldEthnetInfo.dwMask
		|| htonl( valGateway.dwIP ) != tOldEthnetInfo.dwGateWay )
	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "修改Ethnet配置后服务器将立即重启，请确认后点击确定" );
		if ( MSGBOX_OK == nMsgBoxRet)
		{
			TTPEthnetInfo tEthnetInfo;
			tEthnetInfo.bEnable = TRUE;
			tEthnetInfo.dwIP = htonl( valUmsIp.dwIP );
			tEthnetInfo.dwMask = htonl( valSubnetMask.dwIP );
			tEthnetInfo.dwGateWay = htonl( valGateway.dwIP );
			SaveEthnet( tEthnetInfo );
		}
		else
		{
			SetEthnetInfo();
		}
	}


	//保存Sip
	Value_IpEditData valSipIP;
    UIFACTORYMGR_PTR->GetPropertyValue(valSipIP, m_strEdtSipIP, m_pWndTree); 
	TTPSipRegistrarCfg tOldSipInfo = DATAMGRPTR->GetSipCfgData();
	if ( htonl(valSipIP.dwIP) != tOldSipInfo.dwRegIP)
	{
		TTPSipRegistrarCfg tSipInfo;
		tSipInfo.bUsed = TRUE;
		tSipInfo.dwRegIP = htonl(valSipIP.dwIP);
		tSipInfo.wRegPort = 5060;
		tSipInfo.wExpire = 30;
		SaveSip( tSipInfo );
	}
	

	//保存GK
	Value_IpEditData valGKIp;
	UIFACTORYMGR_PTR->GetPropertyValue(valGKIp, m_strEdtGKIP, m_pWndTree);
	bool bUseGK = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGK, m_pWndTree );
	
	TTPGKCfg tOldGKInfo = DATAMGRPTR->GetGkCfgData();

	if ( htonl(valGKIp.dwIP) != tOldGKInfo.dwGKIP || bUseGK != (bool)tOldGKInfo.bUsed )
	{
		TTPGKCfg tGKtInfo;
		tGKtInfo.bUsed = bUseGK;
		tGKtInfo.dwGKIP = htonl(valGKIp.dwIP);
		SaveGK( tGKtInfo );
	}
}

bool CUmsCfgLogic::CheckEthnet()
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_IpEditData valUmsIp;
    UIFACTORYMGR_PTR->GetPropertyValue(valUmsIp, m_strEdtUmsIp, m_pWndTree);
	
	Value_IpEditData valSubnetMask;
    UIFACTORYMGR_PTR->GetPropertyValue(valSubnetMask, m_strEdtSubnetMask, m_pWndTree);
	
    //效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtUmsIp, strCaption, m_pWndTree );
	if ( strCaption.empty() )
	{
		MSG_BOX_OK( "Ums地址不能为空" );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtUmsIp, m_pWndTree );
		return false;
	}
	
	CString cstrErrStr;
	if ( !CCallAddr::IsValidCallIP( valUmsIp.dwIP, cstrErrStr, 0 ) ) 
	{
		MSG_BOX_OK( _T("Ums地址非法") );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtUmsIp, m_pWndTree );
		return false;
    }
	
    //效验子网掩码
    UIFACTORYMGR_PTR->GetCaption( m_strEdtSubnetMask, strCaption, m_pWndTree );
    if ( strCaption.empty() )
    {
		MSG_BOX_OK( "子网掩码不能为空" );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtSubnetMask, m_pWndTree );
        return false;
    }
	
	if ( !CCallAddr::IsValidIpMask(valSubnetMask.dwIP) )
	{
		MSG_BOX_OK( "子网掩码无效。子网掩码必须是相邻的，请输入有效的掩码" );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtSubnetMask, m_pWndTree );
		return false;
	}
	
	if ( !CCallAddr::IsValidDevIP( valUmsIp.dwIP, valSubnetMask.dwIP, cstrErrStr, 0 ) )
	{
		MSG_BOX_OK( _T("子网掩码非法") );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtSubnetMask, m_pWndTree );
		return false;
	}
	
    //效验网关
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGateWay, strCaption, m_pWndTree );
	Value_IpEditData valGateway;
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 
	if ( !strCaption.empty() && !CCallAddr::IsValidIpV4( valGateway.dwIP ) )
	{
		MSG_BOX_OK( "网关IP地址非法" );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtGateWay, m_pWndTree );
		return false;
	}
	
    if ( !strCaption.empty() )
    {
        DWORD dwNetID = valUmsIp.dwIP & valSubnetMask.dwIP;
        DWORD dwNetGate = valGateway.dwIP & valSubnetMask.dwIP;
        if ( dwNetGate != dwNetID )
        {
			MSG_BOX_OK( "网关不在由IP地址和子网掩码定义的同一网络段上" );
			UIFACTORYMGR_PTR->SetFocus( m_strEdtGateWay, m_pWndTree );
            return false; 
        }
	}

	return true;
}

bool CUmsCfgLogic::CheckSip()
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	//效验Sip服务器
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSipIP, strCaption, m_pWndTree );
	Value_IpEditData valSipIP;
    UIFACTORYMGR_PTR->GetPropertyValue(valSipIP, m_strEdtSipIP, m_pWndTree); 

	if ( strCaption.empty() )
	{
// 		MSG_BOX_OK( "Sip服务器地址不能为空" );
// 		UIFACTORYMGR_PTR->SetFocus( m_strEdtSipIP, m_pWndTree );
// 		return false;
		//20130724----------修改bug：sip地址可以为空  by xhx
		return true;
	}
	
	CString cstrNErrStr;
	if ( !CCallAddr::IsValidCallIP( valSipIP.dwIP, cstrNErrStr, 0 ) ) 
	{
		MSG_BOX_OK( _T("Sip服务器地址非法") );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtSipIP, m_pWndTree );
		return false;
	}

	return true;
}

bool CUmsCfgLogic::CheckGK()
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	//添加关于GK的设置
	String strCaption;
	bool bUseGK = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGK, m_pWndTree );
	
	Value_IpEditData valGKIp;
	UIFACTORYMGR_PTR->GetPropertyValue(valGKIp, m_strEdtGKIP, m_pWndTree); 
	
	if (bUseGK)
	{	
		//效验NATIP
		UIFACTORYMGR_PTR->GetCaption( m_strEdtGKIP, strCaption, m_pWndTree );

		if ( strCaption.empty() )
		{
			MSG_BOX_OK( "GK服务器地址不能为空" );
			UIFACTORYMGR_PTR->SetFocus( m_strEdtGKIP, m_pWndTree );
			return false;
		}

		CString cstrNErrStr;
		if ( !CCallAddr::IsValidCallIP( valGKIp.dwIP, cstrNErrStr, 0 ) ) 
		{
			MSG_BOX_OK( _T("GK服务器地址非法") );
			UIFACTORYMGR_PTR->SetFocus( m_strEdtGKIP, m_pWndTree );
			return false;
		}
	}

	return true;
}


void CUmsCfgLogic::SaveEthnet( TTPEthnetInfo &tTPEthnetInfo )
{	
	u16 wRet = COMMONMGRIFPTR->UpdateEthnetCfg( tTPEthnetInfo );
	if (wRet != NO_ERROR)
	{
		MESSAGEWND( "保存Ethnet配置请求发送失败" );
	}
}

void CUmsCfgLogic::SaveSip( TTPSipRegistrarCfg &tTPSipRegistrarCfg )
{
	u16 wRet = COMMONMGRIFPTR->UpdateSipCfg(tTPSipRegistrarCfg);
	if (wRet != NO_ERROR)
	{
		MESSAGEWND( "保存Sip配置请求发送失败" );
	}
}

void CUmsCfgLogic::SaveGK( TTPGKCfg &tTPGKCfg )
{
	u16 wRet = COMMONMGRIFPTR->UpdateGKCfg(tTPGKCfg);
	if (wRet != NO_ERROR)
	{
		MESSAGEWND( "保存GK配置请求发送失败" );
	}
}

void CUmsCfgLogic::UpdBtnState()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	Value_WindowEnable valEnableBtnSave;
	Value_WindowEnable valEnableBtnReduction;
	if ( m_bIsUmsIPChanged || m_bIsSubnetMaskChanged || m_bIsGateWayChanged || m_bIsSipIPChanged || m_bIsGKIPSwitchChanged || m_bIsGKIPChanged )
	{
	 	valEnableBtnSave.bEnable = true;
	 	valEnableBtnReduction.bEnable = true;
	}
	else
	{
		valEnableBtnSave.bEnable = false;
		valEnableBtnReduction.bEnable = false;
	}

	UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtnSave, m_strBtnSave, m_pWndTree);
	UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtnReduction, m_strBtnReduction, m_pWndTree);
}

void CUmsCfgLogic::ResetAllData()
{
	m_bIsUmsIPChanged = FALSE;
	m_bIsSubnetMaskChanged = FALSE;
	m_bIsGateWayChanged = FALSE;
	m_bIsSipIPChanged = FALSE;
	m_bIsGKIPSwitchChanged = FALSE;
	m_bIsGKIPChanged = FALSE;
}

void CUmsCfgLogic::RecductUmsCfg()
{
	SetEthnetInfo();
	SetSipInfo();
	SetGKInfo();
}