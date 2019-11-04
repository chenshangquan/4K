// SysCfgDlgLogic.cpp: implementation of the CSysCfgDlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysCfgDlgLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysCfgDlgLogic::CSysCfgDlgLogic()	 
:m_strCombOutputStyle("SysCfgDlg/CombOutputStyle")
,m_strSoftWareInfo("SysCfgDlg/StcSoftWareInfo")
,m_strEdtIp("SysCfgDlg/StcIPAddrEdit")
,m_strEdtSubMask("SysCfgDlg/StcSubMaskEdit")
,m_strEdtGateWay("SysCfgDlg/StcGatewayEdit")
,m_strStyleGroup1("SysCfgDlg/StyleGroup1")
,m_strStyleGroup2("SysCfgDlg/StyleGroup2")
,m_strAdjustGroup1("SysCfgDlg/AdjustGroup1")
,m_strAdjustGroup2("SysCfgDlg/AdjustGroup2")
,m_strComboBaudRate("SysCfgDlg/CombBaudRate")
{
	m_bCnsIp = FALSE;
	m_bSubMask = FALSE;
	m_bGateWay = FALSE;
// 	m_emDVIOutPortType = TPMOON_DVI_MODE_HDMI;
// 	m_emImageAdjust = emClosed;
// 	m_emMOONOutMode = em_MoonOutMode_1080P_60fps;
	memset(&m_emDVIOutPortType,0,sizeof(EmTPDVIOutPortType));
	memset(&m_emMOONOutMode,0,sizeof(EmTPMOONOutMode));
	memset(&m_emImageAdjust,0,sizeof(EmTPImageAdjust));
}

CSysCfgDlgLogic::~CSysCfgDlgLogic()
{

}

bool CSysCfgDlgLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	

	//设置输出制式下拉框数据
	std::vector<CString> vecOutputStyle;
	vecOutputStyle.push_back("1080P@25fps");
	vecOutputStyle.push_back("1080P@30fps");
	vecOutputStyle.push_back("1080P@50fps");
	vecOutputStyle.push_back("1080P@60fps");
	vecOutputStyle.push_back("720P@50fps");
	vecOutputStyle.push_back("720P@60fps");
	UIFACTORYMGR_PTR->SetComboListData( m_strCombOutputStyle, vecOutputStyle, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( m_strCombOutputStyle, _T("1080P@60fps"), m_pWndTree );

	std::vector<CString> vecRaudRate;
	vecRaudRate.push_back(TransRaudRateTypeToStr(em_LVDSBaud_9600bps).c_str());
	vecRaudRate.push_back(TransRaudRateTypeToStr(em_LVDSBaud_19200bps).c_str());
	vecRaudRate.push_back(TransRaudRateTypeToStr(em_LVDSBaud_38400bps).c_str());
	vecRaudRate.push_back(TransRaudRateTypeToStr(em_LVDSBaud_115200bps).c_str());
	UIFACTORYMGR_PTR->SetComboListData( m_strComboBaudRate, vecRaudRate, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( m_strComboBaudRate, TransRaudRateTypeToStr(em_LVDSBaud_9600bps).c_str(), m_pWndTree );
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

void CSysCfgDlgLogic::RegMsg()
{
	CSysCfgDlgLogic *pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_MOONTOOL_VERINFO_NTY, CSysCfgDlgLogic::OnSoftWareVerInfoNty, pThis, CSysCfgDlgLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMOUTPUT_INFO_NTY, CSysCfgDlgLogic::OnCamOutputInfoNty, pThis, CSysCfgDlgLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_IMAGE_ADJUST_NTY, CSysCfgDlgLogic::OnCamImageAdjustNty, pThis, CSysCfgDlgLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_ETHNETINFO_NOTIFY, CSysCfgDlgLogic::OnEthnetInfoNty, pThis, CSysCfgDlgLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMOUTPUT_INFO_IND, CSysCfgDlgLogic::OnCamOutputInfoInd, pThis, CSysCfgDlgLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_IMAGE_ADJUST_IND, CSysCfgDlgLogic::OnCamImageAdjustInd, pThis, CSysCfgDlgLogic );
//	REG_MSG_HANDLER( UI_MOONTOOL_LVDSBAUD_IND, CSysCfgDlgLogic::OnLvdsBaudRateInd, pThis, CSysCfgDlgLogic );

}

void CSysCfgDlgLogic::UnRegMsg()
{
	
}

void CSysCfgDlgLogic::RegCBFun()
{
	CSysCfgDlgLogic *pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::InitWnd", CSysCfgDlgLogic::InitWnd, pThis, CSysCfgDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::OnHDMISelClick", CSysCfgDlgLogic::OnHDMISelClick, pThis, CSysCfgDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::OnDVISelClick", CSysCfgDlgLogic::OnDVISelClick,  pThis, CSysCfgDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::OnCombOutputStyleClick", CSysCfgDlgLogic::OnCombOutputStyleClick,  pThis, CSysCfgDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::OnNoTurnClick", CSysCfgDlgLogic::OnNoTurnClick,  pThis, CSysCfgDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::OnTurnClick", CSysCfgDlgLogic::OnTurnClick,  pThis, CSysCfgDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::OnIPAddrChanged", CSysCfgDlgLogic::OnIPAddrChanged,  pThis, CSysCfgDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::OnSubMaskChanged", CSysCfgDlgLogic::OnSubMaskChanged,  pThis, CSysCfgDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::OnGatewayChanged", CSysCfgDlgLogic::OnGatewayChanged,  pThis, CSysCfgDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::OnBtnSave", CSysCfgDlgLogic::OnBtnSave,  pThis, CSysCfgDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::OnBtnCancel", CSysCfgDlgLogic::OnBtnCancel,  pThis, CSysCfgDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgDlgLogic::OnCombBaudRateClick", CSysCfgDlgLogic::OnCombBaudRateClick,  pThis, CSysCfgDlgLogic );
}

void CSysCfgDlgLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CSysCfgDlgLogic::InitWnd" );	
}

void CSysCfgDlgLogic::Clear()
{
	m_vctWndName.clear();
	UpBtnState();
	m_bCnsIp = FALSE;
	m_bSubMask = FALSE;
	m_bGateWay = FALSE;
	memset(&m_emDVIOutPortType,0,sizeof(EmTPDVIOutPortType));
	memset(&m_emMOONOutMode,0,sizeof(EmTPMOONOutMode));
	memset(&m_emImageAdjust,0,sizeof(EmTPImageAdjust));
}

bool CSysCfgDlgLogic::OnBtnSave( const IArgs& args )
{
	//先校验网络IP信息,防止有弹框剩余信息仍能保存成功

	bool bOk = SaveNet(); 

	if ( bOk )
	{
		s32 nCheckState = 0;
		UIFACTORYMGR_PTR->GetCheckState( m_strStyleGroup1, nCheckState, m_pWndTree );
		EmTPDVIOutPortType emDVIOutPortType;
		if ( nCheckState )
		{
			emDVIOutPortType = TPMOON_DVI_MODE_HDMI;
		}
		else
		{
			emDVIOutPortType = TPMOON_DVI_MODE_DVI;
		}
		
		EmTPMOONOutMode emMOONOutMode;
		GetMoonOutMode( emMOONOutMode );
		if ( emDVIOutPortType != m_emDVIOutPortType || emMOONOutMode != m_emMOONOutMode )  //两个中有一个变，或者两个都变
		{
			COMIFMGRPTR->SetOutPortTypeCmd( emDVIOutPortType , emMOONOutMode );
		}
		
		UIFACTORYMGR_PTR->GetCheckState( m_strAdjustGroup1, nCheckState, m_pWndTree );
		EmTPImageAdjust emImageAdjust;
		
		if ( nCheckState )
		{
			emImageAdjust = emClosed;
		}
		else
		{
			emImageAdjust = emVertTurn;
		}
		
		if ( emImageAdjust != m_emImageAdjust )
		{
			COMIFMGRPTR->SetImageAdjustCmd( emImageAdjust );
		}
		
		SaveBaudRate();
		if ( emMOONOutMode != m_emMOONOutMode )
		{
			MSG_BOX_ONLY_READ( _T("切换输出制式需要摄像机复位，正在复位中，请稍候…") );
		}

		//
		m_vctWndName.clear();
		UpBtnState();
		return true;
	}
	return false;
}

bool CSysCfgDlgLogic::OnBtnCancel( const IArgs& args )
{
	//没发消息前接收的数据再设遍
	SetOutPortType(m_emDVIOutPortType);
	SetMoonOutMode(m_emMOONOutMode);
	SetImageAdjust(m_emImageAdjust);
	SetEthnetCfgData();
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

void CSysCfgDlgLogic::FocusWindow(String strWindow)
{
	UIFACTORYMGR_PTR->SetFocus( strWindow, m_pWndTree );
}

bool CSysCfgDlgLogic::OnHDMISelClick( const IArgs& args )
{
	s32 nCheckState = 0;
	s32 nCheckStateInLib = 0;
	UIFACTORYMGR_PTR->GetCheckState( m_strStyleGroup1, nCheckState, m_pWndTree );
	if ( m_emDVIOutPortType == TPMOON_DVI_MODE_HDMI )
	{
		nCheckStateInLib = 1;
	}
	else
	{
		nCheckStateInLib = 0;
	}

	bool bChange = false;
	if ( nCheckState != nCheckStateInLib )
	{
		bChange = true;
	}
	CheckData( m_strStyleGroup1, bChange );

	return true;
}

bool CSysCfgDlgLogic::OnDVISelClick( const IArgs& args )
{
	s32 nCheckState = 0;
	s32 nCheckStateInLib = 0;
	UIFACTORYMGR_PTR->GetCheckState( m_strStyleGroup2, nCheckState, m_pWndTree );
	if ( m_emDVIOutPortType == TPMOON_DVI_MODE_DVI )
	{
		nCheckStateInLib = 1;
	}
	else
	{
		nCheckStateInLib = 0;
	}

	bool bChange = false;
	if ( nCheckState != nCheckStateInLib )
	{
		bChange = true;
	}
	CheckData( m_strStyleGroup2, bChange );

	return true;	
}

bool CSysCfgDlgLogic::OnCombOutputStyleClick( const IArgs& args )
{
	EmTPMOONOutMode emMoonOutMode;
	GetMoonOutMode(emMoonOutMode);
	bool bChange = false;
	if ( emMoonOutMode != m_emMOONOutMode )
	{
		bChange = true;
	}
	CheckData( m_strCombOutputStyle, bChange );
	return true;	
}

bool CSysCfgDlgLogic::OnNoTurnClick( const IArgs& args )
{
	s32 nCheckState = 0;
	s32 nCheckStateInLib = 0;
	UIFACTORYMGR_PTR->GetCheckState( m_strAdjustGroup1, nCheckState, m_pWndTree );
	if ( m_emImageAdjust == emClosed )
	{
		nCheckStateInLib = 1;
	}
	else
	{
		nCheckStateInLib = 0;
	}
	
	bool bChange = false;
	if ( nCheckState != nCheckStateInLib )
	{
		bChange = true;
	}
	CheckData( m_strAdjustGroup1, bChange );

	return true;		
}

bool CSysCfgDlgLogic::OnTurnClick( const IArgs& args )
{
	s32 nCheckState = 0;
	s32 nCheckStateInLib = 0;
	UIFACTORYMGR_PTR->GetCheckState( m_strAdjustGroup2, nCheckState, m_pWndTree );
	if ( m_emImageAdjust == emVertTurn )
	{
		nCheckStateInLib = 1;
	}
	else
	{
		nCheckStateInLib = 0;
	}

	bool bChange = false;
	if ( nCheckState != nCheckStateInLib )
	{
		bChange = true;
	}
	CheckData( m_strAdjustGroup2, bChange );

	return true;	
}

bool CSysCfgDlgLogic::OnIPAddrChanged( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPEthnetInfo tOldEthnetInfo;
	MOONLIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldEthnetInfo.dwIP;
	String strOldEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldEthnetInfo )
	{
		strOldEthnetInfo = "";
	}
	
	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtIp, strCaption, m_pWndTree);
			
	if ( strCaption != strOldEthnetInfo )
	{						
		bChange = true;
	//	m_bCnsIp = TRUE;
	}
	
	CheckData(m_strEdtIp,bChange);
	return true;		
}

bool CSysCfgDlgLogic::OnSubMaskChanged( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPEthnetInfo tOldEthnetInfo;
	MOONLIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldEthnetInfo.dwMask;
	String strOldEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldEthnetInfo )
	{
		strOldEthnetInfo = "";
	}
	
	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSubMask, strCaption, m_pWndTree);
	
	if ( strCaption != strOldEthnetInfo )
	{
		bChange = true;
	//	m_bSubMask = TRUE;
	}
	
	CheckData(m_strEdtSubMask,bChange);
	return true;
}

bool CSysCfgDlgLogic::OnGatewayChanged( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPEthnetInfo tOldEthnetInfo;
	MOONLIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldEthnetInfo.dwGateWay;
	String strOldEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldEthnetInfo )
	{
		strOldEthnetInfo = "";
	}
	
	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGateWay, strCaption, m_pWndTree);	
	
	if ( strCaption != strOldEthnetInfo )
	{
		bChange = true;
	//	m_bGateWay = TRUE;
	}
	
	CheckData(m_strEdtGateWay,bChange);
	return true;	
}

HRESULT CSysCfgDlgLogic::OnSoftWareVerInfoNty( WPARAM wparam, LPARAM lparam )
{
	s8 *achSoftWareVerInfo = (s8*)(wparam);
	UIFACTORYMGR_PTR->SetCaption( m_strSoftWareInfo, (LPCTSTR)achSoftWareVerInfo, m_pWndTree );
	return NO_ERROR;
}

//初次登陆参数设置
HRESULT CSysCfgDlgLogic::OnCamOutputInfoNty( WPARAM wparam, LPARAM lparam )
{
	m_emDVIOutPortType = static_cast<EmTPDVIOutPortType>(wparam);
	m_emMOONOutMode =  static_cast<EmTPMOONOutMode>(lparam);
	SetOutPortType(m_emDVIOutPortType);
	SetMoonOutMode(m_emMOONOutMode);
	return NO_ERROR;	
}

//后续保存操作参数设置
HRESULT CSysCfgDlgLogic::OnCamOutputInfoInd( WPARAM wparam, LPARAM lparam )
{
	CMsgboxDlgLogic::GetSingletonPtr()->Clear();
	m_emDVIOutPortType = static_cast<EmTPDVIOutPortType>(wparam);
	m_emMOONOutMode = static_cast<EmTPMOONOutMode>(lparam);
	SetOutPortType(m_emDVIOutPortType);
	SetMoonOutMode(m_emMOONOutMode);
	return NO_ERROR;
}

void CSysCfgDlgLogic::SetOutPortType( EmTPDVIOutPortType emOutPortType )
{
	if ( emOutPortType == TPMOON_DVI_MODE_HDMI )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("StyleGroup1"), 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( _T("StyleGroup2"), 0, m_pWndTree );
	}
	else if ( emOutPortType == TPMOON_DVI_MODE_DVI )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("StyleGroup1"), 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( _T("StyleGroup2"), 1, m_pWndTree );
	}
}

HRESULT CSysCfgDlgLogic::OnCamImageAdjustNty( WPARAM wparam, LPARAM lparam )
{
	m_emImageAdjust = static_cast<EmTPImageAdjust>(wparam);

	SetImageAdjust(m_emImageAdjust);

	return NO_ERROR;
}

HRESULT CSysCfgDlgLogic::OnCamImageAdjustInd( WPARAM wparam, LPARAM lparam )
{
	m_emImageAdjust = static_cast<EmTPImageAdjust>(wparam);
	
	SetImageAdjust(m_emImageAdjust);
	
	return NO_ERROR;	
}

void CSysCfgDlgLogic::SetMoonOutMode( EmTPMOONOutMode emMoonOutMode )
{
	CString strCaption;
	switch (emMoonOutMode)
	{
	case em_MoonOutMode_720P_60fps:
		{
			strCaption = "720P@60fps";
			UIFACTORYMGR_PTR->SetComboText( m_strCombOutputStyle, (LPCTSTR)strCaption, m_pWndTree );
			break;
		}
	case em_MoonOutMode_720P_50fps:
		{
			strCaption = "720P@50fps";
			UIFACTORYMGR_PTR->SetComboText( m_strCombOutputStyle, (LPCTSTR)strCaption, m_pWndTree );
			break;
		}
	case em_MoonOutMode_1080P_25fps:
		{
			strCaption = "1080P@25fps";
			UIFACTORYMGR_PTR->SetComboText( m_strCombOutputStyle, (LPCTSTR)strCaption, m_pWndTree );
			break;
		}
	case em_MoonOutMode_1080P_30fps:
		{
			strCaption = "1080P@30fps";
			UIFACTORYMGR_PTR->SetComboText( m_strCombOutputStyle, (LPCTSTR)strCaption, m_pWndTree );
			break;
		}
	case em_MoonOutMode_1080P_50fps:
		{
			strCaption = "1080P@50fps";
			UIFACTORYMGR_PTR->SetComboText( m_strCombOutputStyle, (LPCTSTR)strCaption, m_pWndTree );
			break;
		}
	case em_MoonOutMode_1080P_60fps:
		{
			strCaption = "1080P@60fps";
			UIFACTORYMGR_PTR->SetComboText( m_strCombOutputStyle, (LPCTSTR)strCaption, m_pWndTree );
			break;
		}
	default:
		break;
	}

}

void CSysCfgDlgLogic::GetMoonOutMode( EmTPMOONOutMode &emMoonOutMode ) const
{
	String strCaption;	
	UIFACTORYMGR_PTR->GetComboText( m_strCombOutputStyle, strCaption, m_pWndTree );
	if ( strCaption == "720P@60fps")
	{
		emMoonOutMode = em_MoonOutMode_720P_60fps;
	}
	else if ( strCaption == "720P@50fps")
	{
		emMoonOutMode = em_MoonOutMode_720P_50fps;
	}
	else if ( strCaption == "1080P@25fps")
	{
		emMoonOutMode = em_MoonOutMode_1080P_25fps;
	}
	else if ( strCaption == "1080P@30fps" )
	{
		emMoonOutMode = em_MoonOutMode_1080P_30fps;
	}
	else if ( strCaption == "1080P@50fps" )
	{
		emMoonOutMode = em_MoonOutMode_1080P_50fps;
	}
	else if ( strCaption == "1080P@60fps" )
	{
		emMoonOutMode = em_MoonOutMode_1080P_60fps;
	}
}

void CSysCfgDlgLogic::SetImageAdjust( EmTPImageAdjust emImageAdjust )
{
	if ( emImageAdjust == emClosed )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("AdjustGroup1"), 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( _T("AdjustGroup2"), 0, m_pWndTree );
	}
	else if ( emImageAdjust == emVertTurn )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("AdjustGroup1"), 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( _T("AdjustGroup2"), 1, m_pWndTree );
	}
}

HRESULT CSysCfgDlgLogic::OnEthnetInfoNty( WPARAM wparam, LPARAM lparam )
{
	SetEthnetCfgData();
	m_bCnsIp = FALSE;
	m_bSubMask = FALSE;
	m_bGateWay = FALSE;
	return NO_ERROR;	
}

void CSysCfgDlgLogic::SetEthnetCfgData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	TTPEthnetInfo tEthnetInfo;
	MOONLIBDATAMGRPTR->GetEthnetCfg( tEthnetInfo );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tEthnetInfo.dwIP);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtIp, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tEthnetInfo.dwMask);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSubMask, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tEthnetInfo.dwGateWay);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGateWay, m_pWndTree ); 	
}

bool CSysCfgDlgLogic::SaveNet()
{
	//网络配置和NAT配置
	Value_IpEditData valCNSIp;
    UIFACTORYMGR_PTR->GetPropertyValue(valCNSIp, m_strEdtIp, m_pWndTree); 
	
	Value_IpEditData valSubMask;
    UIFACTORYMGR_PTR->GetPropertyValue(valSubMask, m_strEdtSubMask, m_pWndTree); 
	
	Value_IpEditData valGateway;
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 
	
	TTPEthnetInfo tOldEthnetInfo;
	MOONLIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );	
	
	if ( htonl( valCNSIp.dwIP ) != tOldEthnetInfo.dwIP || htonl( valSubMask.dwIP ) != tOldEthnetInfo.dwMask
		|| htonl( valGateway.dwIP ) != tOldEthnetInfo.dwGateWay || m_bCnsIp || m_bGateWay || m_bSubMask )
	{
		//效验IP
		String strCaption;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtIp, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			MSG_BOX_OK( "IP地址不能为空" );
			FocusWindow(m_strEdtIp);
			return false;
		}		
		if ( !CCallAddr::IsValidIpV4( valCNSIp.dwIP ) )
        {		
			MSG_BOX_OK( "IP地址非法" );
			FocusWindow(m_strEdtIp);
			return false;
		}
		CString str;		
		if ( !CCallAddr::IsValidCallIP( valCNSIp.dwIP, str, 0 ) ) 
		{			
			MSG_BOX_OK( (String)str );
			FocusWindow(m_strEdtIp);
			return false;
		}
		//效验子网掩码
		UIFACTORYMGR_PTR->GetCaption( m_strEdtSubMask, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			MSG_BOX_OK( "子网掩码不能为空" );
			FocusWindow(m_strEdtSubMask);
			return false;
		}
		if ( !CCallAddr::IsValidIpMask(valSubMask.dwIP) )
		{
			MSG_BOX_OK( "子网掩码无效。子网掩码必须是相邻的，请输入有效的掩码" );
			FocusWindow(m_strEdtSubMask);
			return false;
		}
		if ( !CCallAddr::IsValidDevIP( valCNSIp.dwIP, valSubMask.dwIP, str, 0 ) )
		{
			
			MSG_BOX_OK( (String)str );
			FocusWindow(m_strEdtSubMask);
			return false;
		}		
		//效验网关
		UIFACTORYMGR_PTR->GetCaption( m_strEdtGateWay, strCaption, m_pWndTree );
		if ( !strCaption.empty() && !CCallAddr::IsValidIpV4( valGateway.dwIP ) )
		{
			MSG_BOX_OK( "网关IP地址非法" );
			FocusWindow(m_strEdtGateWay);
			return false;
		}
		if ( !strCaption.empty() )
		{
			DWORD dwNetID = valCNSIp.dwIP & valSubMask.dwIP;
			DWORD dwNetGate = valGateway.dwIP & valSubMask.dwIP;
			if ( dwNetGate != dwNetID )
			{
                //此种情况让用户判断是否保存网关
	            //MSG_BOX_OK( "网关不在由IP地址和子网掩码定义的同一网络段上" );
				MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
				MSG_BOX( nMsgBoxRet, "网关不在由IP地址和子网掩码定义的同一网络段上,是否保存此配置?" );	

				if ( MSGBOX_CANCEL == nMsgBoxRet )
				{								
					FocusWindow(m_strEdtGateWay);
					return false; 
				}
				

			}
		}

		SaveEthnetCfg();
	}
	return true;
}

bool CSysCfgDlgLogic::SaveEthnetCfg( )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue(valIp, m_strEdtIp, m_pWndTree); 
	
	Value_IpEditData valSubMask;
    UIFACTORYMGR_PTR->GetPropertyValue(valSubMask, m_strEdtSubMask, m_pWndTree); 
	
	Value_IpEditData valGateway;
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 
	
	TTPEthnetInfo tEthnetInfo;
	tEthnetInfo.bEnable = TRUE;
	tEthnetInfo.dwIP = htonl( valIp.dwIP );
	tEthnetInfo.dwMask = htonl( valSubMask.dwIP );
	tEthnetInfo.dwGateWay = htonl( valGateway.dwIP );
	
	u16 wRet = COMIFMGRPTR->UpdateEthnetCfg( tEthnetInfo );
	if (wRet != NO_ERROR)
	{
		WARNMESSAGE( "保存网络配置请求发送失败" );
		return false;
	}	
	return true;
}

bool CSysCfgDlgLogic::IsCfgCnsChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CSysCfgDlgLogic::SaveMsgBox()
{
	IArgs args("");
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "配置项已修改，是否保存配置？" );	
	if ( MSGBOX_OK == nMsgBoxRet )
	{
		return OnBtnSave(args);		 
	}
	else
	{
		OnBtnCancel(args);
	}
	return true;
}

bool CSysCfgDlgLogic::OnCombBaudRateClick( const IArgs& args )
{
	String strBaudRate = "";
	bool bChange = false;

	UIFACTORYMGR_PTR->GetComboText(m_strComboBaudRate,strBaudRate,m_pWndTree );
	EmTPLVDSBaud emBaudRade=TransRaudRateStrToType(strBaudRate);
	
	if ( emBaudRade != m_emBaudRate )
	{
		bChange = true;
	}

	CheckData(m_strCombOutputStyle.c_str(),bChange);
	return true;
}

bool CSysCfgDlgLogic::SaveBaudRate()
{
	String strBaudRate = "";
	
	UIFACTORYMGR_PTR->GetComboText(m_strComboBaudRate,strBaudRate,m_pWndTree );
	EmTPLVDSBaud emBaudRade=TransRaudRateStrToType(strBaudRate);

	if ( emBaudRade != m_emBaudRate )
	{
		if ( COMIFMGRPTR->SetBaudRateCmd(emBaudRade) != NO_ERROR )
		{
			return false;
		}
	}
	return true;
}

HRESULT CSysCfgDlgLogic::OnLvdsBaudRateInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	string strBaudRate = "";

	if ( bSuccess == TRUE )
	{
		m_emBaudRate = *(EmTPLVDSBaud*)wparam;
	}
	else
	{
		WARNMESSAGE( "波特率设置失败" );
	}
	strBaudRate = TransRaudRateTypeToStr(m_emBaudRate);
	UIFACTORYMGR_PTR->SetComboText(m_strComboBaudRate,strBaudRate,m_pWndTree);
//	CheckData(m_strComboBaudRate.c_str(),false);
	return NO_ERROR;	
}

string CSysCfgDlgLogic::TransRaudRateTypeToStr( EmTPLVDSBaud emTpLvdBaudValue )
{
	string strRaudRate = "";
	switch( emTpLvdBaudValue )
	{
	case em_LVDSBaud_9600bps:
		strRaudRate = "9600bps";
		break;
	case em_LVDSBaud_19200bps:
		strRaudRate = "19200bps";
		break;
	case em_LVDSBaud_38400bps:
		strRaudRate = "38400bps";
		break;
	case em_LVDSBaud_115200bps:
		strRaudRate = "115200bps";
		break;
	default:
		break;
	}
	return strRaudRate;
}

EmTPLVDSBaud CSysCfgDlgLogic::TransRaudRateStrToType( string strBaudRate )
{
	EmTPLVDSBaud emLvdBaudRate = em_LVDSBaud_Unknown;

	if( strcmp( strBaudRate.c_str(),"9600bps") ==0 )
	{
		emLvdBaudRate = em_LVDSBaud_9600bps;
	}
	else if ( strcmp(strBaudRate.c_str(),"19200bps") == 0 )
	{
		emLvdBaudRate = em_LVDSBaud_19200bps;
	}
	else if ( strcmp(strBaudRate.c_str(),"38400bps") == 0 )
	{
		emLvdBaudRate = em_LVDSBaud_38400bps;
	}
	else if ( strcmp(strBaudRate.c_str(),"115200bps") == 0 )
	{
		emLvdBaudRate = em_LVDSBaud_115200bps;
	}

	return emLvdBaudRate;
}