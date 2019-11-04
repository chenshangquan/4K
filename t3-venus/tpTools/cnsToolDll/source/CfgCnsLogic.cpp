// CfgCnsLogic.cpp: implementation of the CCfgCnsLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CfgCnsLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
						

CCfgCnsLogic::CCfgCnsLogic()
: m_strEdtSubMask("CfgCnsDlg/NetInterfaceBackupCfgDlg/IPCtrlSubMask")				
, m_strNameEdit("CfgCnsDlg/StcNameEdit")
, m_strEdtGateWay("CfgCnsDlg/NetInterfaceBackupCfgDlg/IPCtrlGateway")
, m_strBtnNATSwitch("CfgCnsDlg/BtnNATSwitch")
, m_strEdtNatIP("CfgCnsDlg/IPCtrlNATIp")
, m_strName164Edit("CfgCnsDlg/StcName164Edit")
, m_strEdtIp("CfgCnsDlg/NetInterfaceBackupCfgDlg/IPCtrlAddress")
, m_strBtnDoubleNet("CfgCnsDlg/AudioGroup2")
, m_strBtnNetBackUp("CfgCnsDlg/AudioGroup1")
, m_strEdtLan1Ip("CfgCnsDlg/NetInterfaceCfgDlg/IPCtrlAddress1")
, m_strEdtLan2Ip("CfgCnsDlg/NetInterfaceCfgDlg/IPCtrlAddress2")
, m_strEdtSubMaskLan1("CfgCnsDlg/NetInterfaceCfgDlg/IPCtrlSubMask1")
, m_strEdtSubMaskLan2("CfgCnsDlg/NetInterfaceCfgDlg/IPCtrlSubMask2")
, m_strEdtGateWayLan1("CfgCnsDlg/NetInterfaceCfgDlg/IPCtrlGateway1")
, m_strEdtGateWayLan2("CfgCnsDlg/NetInterfaceCfgDlg/IPCtrlGateway2")
{
	m_vctWndName.clear();
	m_bNameChange = FALSE;
	m_bCnsIp = FALSE;
	m_bSubMask = FALSE;
	m_bGateWay = FALSE;
	m_bCnsIpLan1 = FALSE;
	m_bSubMaskLanl = FALSE;
	m_bGateWayLan1 = FALSE;
	m_bCnsIpLan2 = FALSE;
	m_bSubMaskLan2 = FALSE;
	m_bGateWayLan2 = FALSE;
	m_emEthState = em_BackMode;
    m_bCloudServerEnable = FALSE;
}

CCfgCnsLogic::~CCfgCnsLogic()
{

}

void CCfgCnsLogic::RegMsg()
{
	CCfgCnsLogic* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNS_REG_NAT_NTY, CCfgCnsLogic::OnUpdateNATNty, pThis, CCfgCnsLogic ); 
	REG_MSG_HANDLER( UI_CNS_ETHNETINFO_NOTIFY, CCfgCnsLogic::OnUpdateEthnetNty, pThis, CCfgCnsLogic );
	REG_MSG_HANDLER( UI_CNS_CNSINFO_NOTIFY, CCfgCnsLogic::OnUpdateCnsInfoNty, pThis, CCfgCnsLogic );
	//升级T300之后的回复
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeCns_NTY, CCfgCnsLogic::OnUpgradeCnsNty, pThis, CCfgCnsLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCfgCnsLogic::OnConfStateNty, pThis, CCfgCnsLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_VERINFO_NTY, CCfgCnsLogic::OnVerInfoNty, pThis, CCfgCnsLogic );
	REG_MSG_HANDLER( UI_CNS_CFGWETHNET_RSP, CCfgCnsLogic::OnSetCfgWEthnetRsp, pThis, CCfgCnsLogic );
	REG_MSG_HANDLER( UI_CNS_CFGWETHNET_NTY, CCfgCnsLogic::OnSetCfgWEthnetNty, pThis, CCfgCnsLogic );
	REG_MSG_HANDLER( UI_CNS_CFGETHSTATE_NTY, CCfgCnsLogic::OnSetCfgEthnetStateNty, pThis, CCfgCnsLogic );
    //云服务器配置回复
	REG_MSG_HANDLER( UI_CNC_CLOUDSERVER_IND, CCfgCnsLogic::OnSetCloudServerInfoInd, pThis, CCfgCnsLogic );
}

void CCfgCnsLogic::RegCBFun()
{
	CCfgCnsLogic* pThis = GetSingletonPtr();
	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_FTPCONFSIGNPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnUploadProgress", CCfgCnsLogic::OnUploadProgress, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::InitWnd", CCfgCnsLogic::InitWnd, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnSave", CCfgCnsLogic::OnBtnSave, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnCancel", CCfgCnsLogic::OnBtnCancel, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnUpgrade", CCfgCnsLogic::OnBtnUpgrade, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnReboot", CCfgCnsLogic::OnBtnReboot, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnExport", CCfgCnsLogic::OnBtnExport, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnImport", CCfgCnsLogic::OnBtnImport, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnSwitchNAT", CCfgCnsLogic::OnBtnSwitchNAT, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedName", CCfgCnsLogic::OnChangedName, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedE164", CCfgCnsLogic::OnChangedE164, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedCnsIp", CCfgCnsLogic::OnChangedCnsIp, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedGatewayIp", CCfgCnsLogic::OnChangedGatewayIp, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedSubMaskIp", CCfgCnsLogic::OnChangedSubMaskIp, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedCnsLan1Ip", CCfgCnsLogic::OnChangedCnsLan1Ip, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedGatewayLan1Ip", CCfgCnsLogic::OnChangedGatewayLan1Ip, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedSubMaskLan1Ip", CCfgCnsLogic::OnChangedSubMaskLan1Ip, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedCnsLan2Ip", CCfgCnsLogic::OnChangedCnsLan2Ip, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedGatewayLan2Ip", CCfgCnsLogic::OnChangedGatewayLan2Ip, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedSubMaskLan2Ip", CCfgCnsLogic::OnChangedSubMaskLan2Ip, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedNATIp", CCfgCnsLogic::OnChangedNATIp, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnSelNetInterfaceStyle", CCfgCnsLogic::OnSelNetInterfaceStyle, pThis, CCfgCnsLogic );
}

void CCfgCnsLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCfgCnsLogic::InitWnd" );	
}

bool CCfgCnsLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
//	SetCnsInfoData();
//	SetEthnetCfgData();
//	SetNATData();
	UpBtnState();
	UIFACTORYMGR_PTR->SetCheckState( m_strBtnNetBackUp, 1, m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmNetBackup", m_pWndTree );
	
	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_strCfgCnsDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}

	return true;
}

void CCfgCnsLogic::Clear()
{
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}
	m_vecConfFile.clear();
	m_vctWndName.clear();
	UpBtnState();
	m_bNameChange = FALSE;
	m_bCnsIp = FALSE;
	m_bSubMask = FALSE;
	m_bGateWay = FALSE;
	m_bCnsIpLan1 = FALSE;
	m_bSubMaskLanl = FALSE;
	m_bGateWayLan1 = FALSE;
	m_bCnsIpLan2 = FALSE;
	m_bSubMaskLan2 = FALSE;
	m_bGateWayLan2 = FALSE;
    m_bCloudServerEnable = FALSE;
}

void CCfgCnsLogic::UnRegMsg()
{
	
}

bool CCfgCnsLogic::OnBtnSave( const IArgs& args )
{	
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("有会议进行中，不能配置") );
		SetNATData();
		SetCnsInfoData();
		SetEthnetCfgData();
		SetWEthnetInfo();
		m_vctWndName.clear();
		UpBtnState();
		OnConfStateNty(0,0);
		return false;	
	}

	bool bNameChange = false;
	bool bNetChange = false;
	bool bDoubleNet = false;
	bool bNATChange = false;

	bool bSucceed = true;
	bSucceed = CheckNameAndE164(bNameChange);
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = CheckNet( bNetChange);
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = CheckNAt(bNATChange);
	if (false == bSucceed)
	{
		return false;
	}
	
	EmTpIpNameNatSyn emTPSynType = emSynInvalid;
	if ( bNameChange&&bNetChange&&bNATChange == true )
	{
		emTPSynType = emTpAll;
	}
	else if ( bNameChange&&bNetChange == true )
	{
		emTPSynType = emTpIpAndName;
	}
	else if ( bNameChange&&bNATChange == true )
	{
		emTPSynType = emTpNameAndNat;
	}
	else if ( bNetChange&&bNATChange == true )
	{
		emTPSynType = emTpIpAndNat;
	}
	else if (bNameChange||bNetChange||bNATChange == true )
	{
		emTPSynType = emSynInvalid;
	}

	if ( bNameChange == true )
	{
		if ( SaveNameAndE164(emTPSynType) == false )
		{
			return false;
		}
	}

	if ( bNATChange == true )
	{
		if ( SaveNAT(emTPSynType) == false )
		{
			return false;
		}
	}

	int nCheckState1;
	UIFACTORYMGR_PTR->GetCheckState( m_strBtnNetBackUp, nCheckState1, m_pWndTree );
	int nCheckState2;
	UIFACTORYMGR_PTR->GetCheckState( m_strBtnDoubleNet, nCheckState2, m_pWndTree );
	
	if( 1 == nCheckState1 )
	{
		m_emEthState = em_BackMode;
	}
	else
	{
		m_emEthState = em_DoubleMode;
	}

	if( m_emEthState == em_BackMode )
	{
		bSucceed = CheckNet( bNetChange);
		if (false == bSucceed)
		{
			return false;
		}
		if ( SaveEthnetCfg(emTPSynType) == false )
		{
			return false;
		}
	}
	else
	{
		bSucceed = CheckDoubleNet(bDoubleNet);
		if (false == bSucceed)
		{
			return false;
		}
		if ( SaveDoubleNet(emTPSynType) == false )
		{
			return false;
		}		
	}
	
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

bool CCfgCnsLogic::OnBtnCancel( const IArgs& args )
{
	SetCnsInfoData();
	SetEthnetCfgData();
	SetWEthnetInfo();
	SetNATData();
	SetEthnetSwitchtype();
	m_vctWndName.clear();
	UpBtnState();

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		OnConfStateNty(0,0);
		return false;	
	}
	return true;	
}

/*---------------------------------------------------------------------
* 函数名称：IsCfgCnsChange
* 功    能：判断cfgcns界面的信息是否被修改
* 特殊说明：属于logic之间的通信
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgCnsLogic::IsCfgCnsChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
  	return true;
}

/*---------------------------------------------------------------------
* 函数名称：SaveMsgBox
* 功    能：弹出是否保存的消息框
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgCnsLogic::SaveMsgBox()
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

/*---------------------------------------------------------------------
* 函数名称：FocusWindow
* 功    能：弹出提示框后定位到具体窗口位置
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
void CCfgCnsLogic::FocusWindow(String strWindow)
{
	UIFACTORYMGR_PTR->SetFocus( strWindow, m_pWndTree );
}

bool CCfgCnsLogic::CheckNameAndE164(bool &bChange )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	TTPCnsInfo tCnsInfo;
	LIBDATAMGRPTR->GetLocalCnsInfo( tCnsInfo );
	
	String strCnsName;
	UIFACTORYMGR_PTR->GetCaption( m_strNameEdit, strCnsName, m_pWndTree );
	if ( strcmp( tCnsInfo.m_achRoomName, strCnsName.c_str() ) != 0 )
	{
		if ( strCnsName.length() <= 0 )
		{
			MSG_BOX_OK("会场名称不能为空");
			FocusWindow(m_strNameEdit);
			return false;
		}
		if ( IsAllE164Number( strCnsName ) )
		{
			MSG_BOX_OK("会场名称不能全为数字及*,号");
			FocusWindow(m_strNameEdit);
			return false;
		}
		if ( !IsValidTPStr( strCnsName ) )
		{ 
			CString cstr; 
			cstr.Format( "会场名称不可以包含空格及括号中的任意字符 [ %s ]", INVALID_ALIAS_FOR_SHOW );			
			MSG_BOX_OK( cstr.GetBuffer(cstr.GetLength()) );
			FocusWindow(m_strNameEdit);
			return false;
		}
		bChange = true;
		m_bNameChange = TRUE;
	}
	
	String strCnsNumber;
	UIFACTORYMGR_PTR->GetCaption( m_strName164Edit, strCnsNumber, m_pWndTree );	
	if ( strcmp( tCnsInfo.m_achE164, strCnsNumber.c_str() ) != 0 )
	{
		CString cstrE164 = "";
		cstrE164.Format( "%s", strCnsNumber.c_str() );
		if ( !cstrE164.IsEmpty() && !CCallAddr::IsValidE164(cstrE164) )
		{
			MSG_BOX_OK("会场号码不合法，E164号只能包含数字及*,号");
			FocusWindow(m_strName164Edit);
			return false;
		}
		bChange = true;
	}
	return true;
}
/*---------------------------------------------------------------------
* 函数名称：SaveNameAndE164
* 功    能：保存会场名称和E164号部分
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgCnsLogic::SaveNameAndE164( EmTpIpNameNatSyn emTpIpType )
{
	String strCnsName;
	UIFACTORYMGR_PTR->GetCaption( m_strNameEdit, strCnsName, m_pWndTree );
	
	String strCnsNumber;
	UIFACTORYMGR_PTR->GetCaption( m_strName164Edit, strCnsNumber, m_pWndTree );	

	TTPCnsInfo tUpCnsInfo;
	strncpy( tUpCnsInfo.m_achRoomName, strCnsName.c_str(), sizeof( tUpCnsInfo.m_achRoomName ) );
	strncpy( tUpCnsInfo.m_achE164, strCnsNumber.c_str(), sizeof( tUpCnsInfo.m_achE164 ) );
	
	u16 wRet = COMIFMGRPTR->UpdateCnsInfo( tUpCnsInfo, 1 ,emTpIpType);
	if (wRet != NO_ERROR)
	{
		WARNMESSAGE( "保存会场配置请求发送失败" );
		return false;
	}

	return true;
}

bool CCfgCnsLogic::CheckNet( bool &bChange )
{
	//网络配置和NAT配置
	Value_IpEditData valCNSIp;
    UIFACTORYMGR_PTR->GetPropertyValue(valCNSIp, m_strEdtIp, m_pWndTree); 
	
	Value_IpEditData valSubMask;
    UIFACTORYMGR_PTR->GetPropertyValue(valSubMask, m_strEdtSubMask, m_pWndTree); 
	
	Value_IpEditData valGateway;
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 
	
	TTPEthnetInfo tOldEthnetInfo;
	LIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );	
	
	if ( htonl( valCNSIp.dwIP ) != tOldEthnetInfo.dwIP || htonl( valSubMask.dwIP ) != tOldEthnetInfo.dwMask
		|| htonl( valGateway.dwIP ) != tOldEthnetInfo.dwGateWay || m_bCnsIp || m_bGateWay || m_bSubMask )
	{
		//效验IP
		String strCaption;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtIp, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			MSG_BOX_OK( "CNS IP地址不能为空" );
			FocusWindow(m_strEdtIp);
			return false;
		}		
		if ( !CCallAddr::IsValidIpV4( valCNSIp.dwIP ) )
        {		
			MSG_BOX_OK( "CNS IP地址非法" );
			FocusWindow(m_strEdtIp);
			return false;
		}
		CString str;		
		if ( !CCallAddr::IsValidCallIP( valCNSIp.dwIP, str, 0 ) ) 
		{			
			MSG_BOX_OK( str.GetBuffer(str.GetLength()) );
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
			
			MSG_BOX_OK( (str.GetBuffer(str.GetLength()) ));
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
				MSG_BOX_OK( "网关不在由IP地址和子网掩码定义的同一网络段上" );
				FocusWindow(m_strEdtGateWay);
				return false; 
			}
		}
		bChange = true;
	}
	return true;
}

bool CCfgCnsLogic::CheckDoubleNet(bool &bChange)
{
	Value_IpEditData valCNSIp;
    UIFACTORYMGR_PTR->GetPropertyValue(valCNSIp, m_strEdtLan1Ip, m_pWndTree); 
	
	Value_IpEditData valSubMask;
    UIFACTORYMGR_PTR->GetPropertyValue(valSubMask, m_strEdtSubMaskLan1, m_pWndTree); 
	
	Value_IpEditData valGateway;
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWayLan1, m_pWndTree); 	
	
	if ( htonl( valCNSIp.dwIP ) != m_tTPWEthnetInfo.atTPEthnetInfo[0].dwIP || htonl( valSubMask.dwIP ) != m_tTPWEthnetInfo.atTPEthnetInfo[0].dwMask
		|| htonl( valGateway.dwIP ) != m_tTPWEthnetInfo.atTPEthnetInfo[0].dwGateWay || m_bCnsIpLan1 || m_bGateWayLan1 || m_bSubMaskLanl )
	{
		//效验IP
		String strCaption;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtLan1Ip, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			MSG_BOX_OK( "CNS IP地址不能为空" );
			FocusWindow(m_strEdtLan1Ip);
			return false;
		}		
		if ( !CCallAddr::IsValidIpV4( valCNSIp.dwIP ) )
        {		
			MSG_BOX_OK( "CNS IP地址非法" );
			FocusWindow(m_strEdtLan1Ip);
			return false;
		}
		CString str;		
		if ( !CCallAddr::IsValidCallIP( valCNSIp.dwIP, str, 0 ) ) 
		{			
			MSG_BOX_OK( str.GetBuffer(str.GetLength()) );
			FocusWindow(m_strEdtLan1Ip);
			return false;
		}
		//效验子网掩码
		UIFACTORYMGR_PTR->GetCaption( m_strEdtSubMaskLan1, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			MSG_BOX_OK( "子网掩码不能为空" );
			FocusWindow(m_strEdtSubMaskLan1);
			return false;
		}
		if ( !CCallAddr::IsValidIpMask(valSubMask.dwIP) )
		{
			MSG_BOX_OK( "子网掩码无效。子网掩码必须是相邻的，请输入有效的掩码" );
			FocusWindow(m_strEdtSubMaskLan1);
			return false;
		}
		if ( !CCallAddr::IsValidDevIP( valCNSIp.dwIP, valSubMask.dwIP, str, 0 ) )
		{
			
			MSG_BOX_OK( (str.GetBuffer(str.GetLength()) ));
			FocusWindow(m_strEdtSubMaskLan1);
			return false;
		}		
		//效验网关
		UIFACTORYMGR_PTR->GetCaption( m_strEdtGateWayLan1, strCaption, m_pWndTree );
		if ( !strCaption.empty() && !CCallAddr::IsValidIpV4( valGateway.dwIP ) )
		{
			MSG_BOX_OK( "网关IP地址非法" );
			FocusWindow(m_strEdtGateWayLan1);
			return false;
		}
		if ( !strCaption.empty() )
		{
			DWORD dwNetID = valCNSIp.dwIP & valSubMask.dwIP;
			DWORD dwNetGate = valGateway.dwIP & valSubMask.dwIP;
			if ( dwNetGate != dwNetID )
			{
				MSG_BOX_OK( "网关不在由IP地址和子网掩码定义的同一网络段上" );
				FocusWindow(m_strEdtGateWayLan1);
				return false; 
			}
		}
		bChange = true;
	}

	UIFACTORYMGR_PTR->GetPropertyValue(valCNSIp, m_strEdtLan2Ip, m_pWndTree); 

    UIFACTORYMGR_PTR->GetPropertyValue(valSubMask, m_strEdtSubMaskLan2, m_pWndTree); 
	
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWayLan2, m_pWndTree);

	if ( htonl( valCNSIp.dwIP ) != m_tTPWEthnetInfo.atTPEthnetInfo[1].dwIP || htonl( valSubMask.dwIP ) != m_tTPWEthnetInfo.atTPEthnetInfo[1].dwMask
		|| htonl( valGateway.dwIP ) != m_tTPWEthnetInfo.atTPEthnetInfo[1].dwGateWay || m_bCnsIpLan2 || m_bGateWayLan2 || m_bSubMaskLan2 )
	{
		//效验IP
		String strCaption;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtLan2Ip, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			MSG_BOX_OK( "CNS IP地址不能为空" );
			FocusWindow(m_strEdtLan2Ip);
			return false;
		}		
		if ( !CCallAddr::IsValidIpV4( valCNSIp.dwIP ) )
        {		
			MSG_BOX_OK( "CNS IP地址非法" );
			FocusWindow(m_strEdtLan2Ip);
			return false;
		}
		CString str;		
		if ( !CCallAddr::IsValidCallIP( valCNSIp.dwIP, str, 0 ) ) 
		{			
			MSG_BOX_OK( str.GetBuffer(str.GetLength()) );
			FocusWindow(m_strEdtLan2Ip);
			return false;
		}
		//效验子网掩码
		UIFACTORYMGR_PTR->GetCaption( m_strEdtSubMaskLan2, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			MSG_BOX_OK( "子网掩码不能为空" );
			FocusWindow(m_strEdtSubMaskLan2);
			return false;
		}
		if ( !CCallAddr::IsValidIpMask(valSubMask.dwIP) )
		{
			MSG_BOX_OK( "子网掩码无效。子网掩码必须是相邻的，请输入有效的掩码" );
			FocusWindow(m_strEdtSubMaskLan2);
			return false;
		}
		if ( !CCallAddr::IsValidDevIP( valCNSIp.dwIP, valSubMask.dwIP, str, 0 ) )
		{
			
			MSG_BOX_OK( (str.GetBuffer(str.GetLength()) ));
			FocusWindow(m_strEdtSubMaskLan2);
			return false;
		}		
		//效验网关
		UIFACTORYMGR_PTR->GetCaption( m_strEdtGateWayLan2, strCaption, m_pWndTree );
		if ( !strCaption.empty() && !CCallAddr::IsValidIpV4( valGateway.dwIP ) )
		{
			MSG_BOX_OK( "网关IP地址非法" );
			FocusWindow(m_strEdtGateWayLan2);
			return false;
		}
		if ( !strCaption.empty() )
		{
			DWORD dwNetID = valCNSIp.dwIP & valSubMask.dwIP;
			DWORD dwNetGate = valGateway.dwIP & valSubMask.dwIP;
			if ( dwNetGate != dwNetID )
			{
				MSG_BOX_OK( "网关不在由IP地址和子网掩码定义的同一网络段上" );
				FocusWindow(m_strEdtGateWayLan2);
				return false; 
			}
		}
		bChange = true;
	}

	return true;
}

/*---------------------------------------------------------------------
* 函数名称：SaveNet
* 功    能：保存网络配置
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
/*bool CCfgCnsLogic::SaveNet()
{
	//网络配置和NAT配置
	Value_IpEditData valCNSIp;
    UIFACTORYMGR_PTR->GetPropertyValue(valCNSIp, m_strEdtIp, m_pWndTree); 
	
	Value_IpEditData valSubMask;
    UIFACTORYMGR_PTR->GetPropertyValue(valSubMask, m_strEdtSubMask, m_pWndTree); 

	Value_IpEditData valGateway;
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 

	TTPEthnetInfo tOldEthnetInfo;
	LIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );	

	if ( htonl( valCNSIp.dwIP ) != tOldEthnetInfo.dwIP || htonl( valSubMask.dwIP ) != tOldEthnetInfo.dwMask
		|| htonl( valGateway.dwIP ) != tOldEthnetInfo.dwGateWay || m_bCnsIp || m_bGateWay || m_bSubMask )
	{
		SaveEthnetCfg();
	}
	return true;
}
*/
bool CCfgCnsLogic::CheckNAt( bool &bChange)
{
	bool bUseNAT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnNATSwitch, bUseNAT, m_pWndTree );
	
	Value_IpEditData valNatIp;
	UIFACTORYMGR_PTR->GetPropertyValue(valNatIp, m_strEdtNatIP, m_pWndTree); 
	
	TTPNatCfg tOldNatInfo;
	LIBDATAMGRPTR->GetNATCfg(tOldNatInfo);
	
	//校验NATIP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtNatIP, strCaption, m_pWndTree );
	
	if ( bUseNAT && strCaption.empty())
	{
		MSG_BOX_OK( "NAT地址不能为空" );
		FocusWindow(m_strEdtNatIP);
		return false;
	}
	
	if ( !CCallAddr::IsValidCallIP( valNatIp.dwIP ) && !strCaption.empty() ) 
	{
		MSG_BOX_OK( "NAT地址非法" );
		FocusWindow(m_strEdtNatIP);
		return false;
	}
	
	if ( htonl(valNatIp.dwIP) != tOldNatInfo.dwNatIP || bUseNAT != (bool)tOldNatInfo.bUsed )
	{
		bChange = true;
	}

	return true;
}

bool CCfgCnsLogic::SaveNAT( EmTpIpNameNatSyn emTpIpType )
{	
	bool bUseNAT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnNATSwitch, bUseNAT, m_pWndTree );
	
	Value_IpEditData valNatIp;
	UIFACTORYMGR_PTR->GetPropertyValue(valNatIp, m_strEdtNatIP, m_pWndTree); 
	
	TTPNatCfg tNatInfo;
	tNatInfo.bUsed = bUseNAT;
	tNatInfo.dwNatIP = htonl(valNatIp.dwIP);
	
	u16 wRet = COMIFMGRPTR->UpdateNATCfg(tNatInfo,emTpIpType);
	if (wRet != NO_ERROR)
	{
		WARNMESSAGE( "保存NAT配置请求发送失败" );
		return false;
	}	
	return true;
}

bool CCfgCnsLogic::OnBtnUpgrade( const IArgs& args )
{	
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchUpgradeCns", NULL, g_stcStrImpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrImpCommonDlg );	
	
	return true;	
}

bool CCfgCnsLogic::OnBtnReboot(const IArgs& args)
{
	//重启功能
    s32 n = 0;
    n = CCfgCnsLogic::GetSingletonPtr()->GetCtrlChangeNum();
	if (n == 0)
	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "是否重启？" );
		if ( MSGBOX_OK == nMsgBoxRet )
		{
			u16 wRet = COMIFMGRPTR->RebootCns();
			if ( wRet != NO_ERROR )
			{
				WARNMESSAGE( "重启cns请求发送失败" );
			}
		}
	}
	else
	{
		MSG_BOX_OK( "配置项已修改，请先保存修改后再重启！" );
	}

	return true;
}

bool CCfgCnsLogic::OnBtnExport( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", NULL, g_stcStrExpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchExportConfig", NULL, g_stcStrExpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrExpCommonDlg );	
	
	return true;
}

bool CCfgCnsLogic::OnBtnImport(const IArgs& args)
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchImportCnsCfg", NULL, g_stcStrImpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrImpCommonDlg );

	return true;
}

bool CCfgCnsLogic::OnBtnSwitchNAT( const IArgs& args )
{
	TTPNatCfg tOldNatInfo;
	LIBDATAMGRPTR->GetNATCfg(tOldNatInfo);

	bool bUseNAT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnNATSwitch, bUseNAT, m_pWndTree );
    if ( bUseNAT )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtNatIP);  
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtNatIP);
    }

	bool bChange = false;
	if ( (BOOL)bUseNAT != tOldNatInfo.bUsed )
	{
		bChange = true;
	}
	CheckData(m_strBtnNATSwitch,bChange);
	return true;	
}

LRESULT CCfgCnsLogic::OnUpdateNATNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetNATData();
	return S_OK;
}

LRESULT CCfgCnsLogic::OnUpdateEthnetNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetEthnetCfgData();
	m_bCnsIp = FALSE;
	m_bSubMask = FALSE;
	m_bGateWay = FALSE;
	return S_OK;
}

LRESULT CCfgCnsLogic::OnSetCfgEthnetStateNty(WPARAM wParam, LPARAM lParam)
{
	EmEthState  emEthState = *(EmEthState*)(wParam);
	m_emEthState = emEthState;

	if( emEthState == em_BackMode )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnNetBackUp, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnDoubleNet, 0, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmNetBackup", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnNetBackUp, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnDoubleNet, 1, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmDoubleNet", m_pWndTree );
	}

	return S_OK;
}

LRESULT CCfgCnsLogic::OnSetCfgWEthnetNty(WPARAM wParam, LPARAM lParam)
{
	TTPWEthnetInfo tTPWEthnetInfo = *(TTPWEthnetInfo*)(wParam);
	m_tTPWEthnetInfo = tTPWEthnetInfo;
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tTPWEthnetInfo.atTPEthnetInfo[0].dwIP);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtLan1Ip, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tTPWEthnetInfo.atTPEthnetInfo[0].dwMask);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSubMaskLan1, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tTPWEthnetInfo.atTPEthnetInfo[0].dwGateWay);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGateWayLan1, m_pWndTree );

	valIp.dwIP = ntohl(tTPWEthnetInfo.atTPEthnetInfo[1].dwIP);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtLan2Ip, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tTPWEthnetInfo.atTPEthnetInfo[1].dwMask);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSubMaskLan2, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tTPWEthnetInfo.atTPEthnetInfo[1].dwGateWay);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGateWayLan2, m_pWndTree );

	m_bCnsIpLan1 = FALSE;
	m_bSubMaskLanl = FALSE;
	m_bGateWayLan1 = FALSE;
	m_bCnsIpLan2 = FALSE;
	m_bSubMaskLan2 = FALSE;
	m_bGateWayLan2 = FALSE;

	return S_OK;
}

LRESULT CCfgCnsLogic::OnSetCfgWEthnetRsp(WPARAM wParam, LPARAM lParam)
{
	TTPWEthnetInfo tTPWEthnetInfo = *(TTPWEthnetInfo*)(wParam);
	m_tTPWEthnetInfo = tTPWEthnetInfo;

	BOOL bSuccess = *(BOOL*)(lParam);

	if( !bSuccess )
	{
		WARNMESSAGE("设置双网口配置失败");
	}

	return S_OK;
}

LRESULT CCfgCnsLogic::OnSetCloudServerInfoInd(WPARAM wParam, LPARAM lParam)
{
    if ( m_pWndTree == NULL )
    {
        return S_FALSE;
    }

    TTPCloudPlatServerCfg tCloudCfg;
	LIBDATAMGRPTR->GetCloudCfg( tCloudCfg );

    Value_WindowEnable valEnableBtn;
    if ( tCloudCfg.m_bEnable )
    {
        m_bCloudServerEnable = TRUE;
        valEnableBtn.bEnable = false;
        UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, m_strNameEdit, m_pWndTree );
        UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, m_strName164Edit, m_pWndTree );
    }
    else
    {
        m_bCloudServerEnable = FALSE;
        valEnableBtn.bEnable = true;
        UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, m_strNameEdit, m_pWndTree );
        UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, m_strName164Edit, m_pWndTree );
    }

    return S_OK;
}

bool CCfgCnsLogic::SaveEthnetCfg( EmTpIpNameNatSyn emTpIpType )
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
	
	u16 wRet = COMIFMGRPTR->UpdateEthnetCfg( tEthnetInfo,emTpIpType);
	if (wRet != NO_ERROR)
	{
		WARNMESSAGE( "保存网络配置请求发送失败" );
		return false;
	}	
	return true;
}

bool CCfgCnsLogic::SaveDoubleNet(EmTpIpNameNatSyn emTpIpType)
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue(valIp, m_strEdtLan1Ip, m_pWndTree); 
	
	Value_IpEditData valSubMask;
    UIFACTORYMGR_PTR->GetPropertyValue(valSubMask, m_strEdtSubMaskLan1, m_pWndTree); 
	
	Value_IpEditData valGateway;
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWayLan1, m_pWndTree); 
	
	TTPWEthnetInfo tWEthnetInfo;
	tWEthnetInfo.atTPEthnetInfo[0].bEnable = TRUE;
	tWEthnetInfo.atTPEthnetInfo[0].dwIP = htonl( valIp.dwIP );
	tWEthnetInfo.atTPEthnetInfo[0].dwMask = htonl( valSubMask.dwIP );
	tWEthnetInfo.atTPEthnetInfo[0].dwGateWay = htonl( valGateway.dwIP );

    UIFACTORYMGR_PTR->GetPropertyValue(valIp, m_strEdtLan2Ip, m_pWndTree); 
    UIFACTORYMGR_PTR->GetPropertyValue(valSubMask, m_strEdtSubMaskLan2, m_pWndTree); 
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWayLan2, m_pWndTree); 

	tWEthnetInfo.atTPEthnetInfo[1].bEnable = TRUE;
	tWEthnetInfo.atTPEthnetInfo[1].dwIP = htonl( valIp.dwIP );
	tWEthnetInfo.atTPEthnetInfo[1].dwMask = htonl( valSubMask.dwIP );
	tWEthnetInfo.atTPEthnetInfo[1].dwGateWay = htonl( valGateway.dwIP );

	if (tWEthnetInfo.atTPEthnetInfo[0].dwMask == tWEthnetInfo.atTPEthnetInfo[1].dwMask)
	{
		in_addr tAddr0;
		tAddr0.S_un.S_addr = tWEthnetInfo.atTPEthnetInfo[0].dwIP;
		char strIpAddr0[16] = {0};
		strcpy(strIpAddr0, inet_ntoa(tAddr0));   

		in_addr tAddr1;
		tAddr1.S_un.S_addr = tWEthnetInfo.atTPEthnetInfo[1].dwIP;
		char strIpAddr1[16] = {0};
		strcpy(strIpAddr1, inet_ntoa(tAddr1));  

		in_addr tMask;
		tMask.S_un.S_addr = tWEthnetInfo.atTPEthnetInfo[0].dwMask;
		char strMask[16] = {0};
		strcpy(strMask, inet_ntoa(tMask));  

		if (UIDATAMGR_PTR->IsSameNetworkSegment(strIpAddr0, strIpAddr1, strMask) == 1)
		{
			MSG_BOX_OK( "两个网口不能配置相同网段" );
			return false;
		}
	}

	u16 wRet = COMIFMGRPTR->SaveWEthnetCfgCmd( tWEthnetInfo, emTpIpType );
	if( wRet != NO_ERROR )
	{
		WARNMESSAGE("保存双网口配置请求发送失败");
		return false;
	}

	return true;
}

LRESULT CCfgCnsLogic::OnUpdateCnsInfoNty( WPARAM wParam, LPARAM lParam )
{
/*	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}*/
	if ( 0 != wParam )
	{
		TTPCnsInfo tCnsInfo = *(TTPCnsInfo*)wParam;
		EmTPCNSInfoRst emRst = (EmTPCNSInfoRst)lParam;
		
		if ( emRst == emTPCNSInfoSuccess )
		{
	//		if ( m_bNameChange ) //B4 会场名修改后，不需要上传台标
			if ( FALSE )
			{
				//绘制台标图片并上传
				CString strFullPath = GetModuleFullPath();
				
				CString str1080Path = strFullPath + "confname1080.bmp";
				BOOL bSuccess1 = ConfSign->MakeImgByChar( tCnsInfo.m_achRoomName, "宋体", FontStyleBold, Color(255,235,0), Color(0,0,0), 
					Color(255,255,255), 48, 2, (LPCSTR)str1080Path );
				
				CString str720Path = strFullPath + "confname720.bmp";
				BOOL bSuccess2 = ConfSign->MakeImgByChar( tCnsInfo.m_achRoomName, "宋体", FontStyleBold, Color(255,235,0), Color(0,0,0), 
					Color(255,255,255), 32, 2, (LPCSTR)str720Path );
				
				if ( bSuccess1 && bSuccess2 )
				{	
					m_vecConfFile.clear();
					m_vecConfFile.push_back("confname1080.bmp");
					m_vecConfFile.push_back("confname720.bmp");
					CString cstrFullPath = GetModuleFullPath();
					string strModlePath = cstrFullPath.GetBuffer(cstrFullPath.GetLength());
					if ( !UploadCore( CNSCONFIG_FILE_PATH, strModlePath+m_vecConfFile.at(0), m_vecConfFile.at(0)) )
					{
						COMIFMGRPTR->ConfSignCmd( FALSE, 1 );
						PrtMsg( 0, emEventTypeCmsWindow, "%s还没开始进行ftp传输便失败！", m_vecConfFile.at(0).c_str() );
					}		
				} 
				else if ( !bSuccess1 && bSuccess2 )
				{
					MSG_BOX_OK( "1080P台标图片生成失败" );
				}
				else if ( bSuccess1 && !bSuccess2 )
				{
					MSG_BOX_OK( "720P台标图片生成失败" );
				}
				m_bNameChange = FALSE;
			}
			m_vctWndName.clear();
		}
		else
		{
			CString strName;
			strName.Format( "会场%s注册失败:", tCnsInfo.m_achRoomName );
			
			CString strTemp = "别名重复";
			
			if ( emRst == emTPCNSRepeatAliasName )
			{
				strTemp = "名称重复";
				
				strName = strName + strTemp;			
				//MSG_BOX_OK((String)strName);
				WARNMESSAGE(strName);
				FocusWindow(m_strNameEdit);
				return S_OK;
			}
			else if ( emRst == emTPCNSRepeatE164 )
			{
				strTemp = "E164号码重复";
				
				strName = strName + strTemp;			
				//MSG_BOX_OK((String)strName);
				WARNMESSAGE(strName);
				FocusWindow(m_strName164Edit);
				return S_OK;
			}
		}
	}
	SetCnsInfoData();
	UpBtnState();
	return S_OK;
}

LRESULT CCfgCnsLogic::OnUpgradeCnsNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

    BOOL bSuccess = *(BOOL*)wParam;
	if ( TRUE != bSuccess )
	{
		WARNMESSAGE("升级失败");
		UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );	//升级失败,恢复界面为初始状态
	} 
	else
	{
		BOOL bInConf = LIBDATAMGRPTR->IsInConf();
		if ( bInConf )
		{
			MSG_BOX_OK("升级成功，当前会场正在开会，请稍后手动重启");
			UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
			s32 nResult = 0;
			UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
		}
		else
		{
			MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
			MSG_BOX( nMsgBoxRet, "升级成功，是否立即重启？" );	
			if ( MSGBOX_OK == nMsgBoxRet )
			{
				if ( bInConf )
				{
					MSG_BOX_OK("升级成功，当前会场正在开会，请稍后手动重启");
					UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
					s32 nResult = 0;
					UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
					return S_OK;
				}
				u16 wRet = COMIFMGRPTR->RebootCns();
				if ( wRet != NO_ERROR )
				{
					WARNMESSAGE( "重启cns请求发送失败" );
				}
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
				s32 nResult = 0;
				UIFACTORYMGR_PTR->Endmodal( nResult, g_stcStrImpCommonDlg );
			}
		}
	}
	return S_OK;
}

bool CCfgCnsLogic::OnChangedName( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPCnsInfo tCnsInfo;
	LIBDATAMGRPTR->GetLocalCnsInfo( tCnsInfo );

	bool bChange = false;
	String strRoomName;
	UIFACTORYMGR_PTR->GetCaption( m_strNameEdit, strRoomName, m_pWndTree);
	if ( 0 != strcmp( tCnsInfo.m_achRoomName, strRoomName.c_str() ) )
	{
		bChange = true;
	}
	CheckData(m_strNameEdit,bChange);
	return true;	
}

bool CCfgCnsLogic::OnChangedE164( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPCnsInfo tCnsInfo;
	LIBDATAMGRPTR->GetLocalCnsInfo( tCnsInfo );

	bool bChange = false;
	String strE164Num;
	UIFACTORYMGR_PTR->GetCaption( m_strName164Edit, strE164Num, m_pWndTree);
	if ( 0 != strcmp( tCnsInfo.m_achE164, strE164Num.c_str() ) )
	{
		bChange = true;
	}

	CheckData(m_strName164Edit,bChange);
	return true;	
}

bool CCfgCnsLogic::OnChangedCnsIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPEthnetInfo tOldEthnetInfo;
	LIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );
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
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}
// 	if ( strCaption == "0." || strCaption == "00." || strCaption == "000." )
// 	{
// 		MSG_BOX_OK( "0不是有效项.请指定一个介于1和223间的值." );
// 		UIFACTORYMGR_PTR->SetCaption( m_strEdtIp, "1.", m_pWndTree);
// 		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strCaption, m_pWndTree );
// 		if ( pWnd )
// 		{
// 			(( CEdit *) pWnd)->SetSel( -1 );
// 		}
// 	}			
	if ( /*dwIP != tOldEthnetInfo.dwIP || */strCaption != strOldEthnetInfo )
	{						
		bChange = true;
		m_bCnsIp = TRUE;
	}

	CheckData(m_strEdtIp,bChange);
	return true;	
}

bool CCfgCnsLogic::OnChangedGatewayIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPEthnetInfo tOldEthnetInfo;
	LIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );
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
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}
	
// 	if ( strCaption == "0." || strCaption == "00." || strCaption == "000." )
// 	{
// 		MSG_BOX_OK( "0不是有效项.请指定一个介于1和223间的值." );
// 		UIFACTORYMGR_PTR->SetCaption( m_strEdtGateWay, "1.", m_pWndTree);
// 		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strCaption, m_pWndTree );
// 		if ( pWnd )
// 		{
// 			(( CEdit *) pWnd)->SetSel( -1 );
// 		}
// 	}		
	if ( /*dwIP != tOldEthnetInfo.dwGateWay || */strCaption != strOldEthnetInfo )
	{
		bChange = true;
		m_bGateWay = TRUE;
	}

	CheckData(m_strEdtGateWay,bChange);
	return true;	
}

bool CCfgCnsLogic::OnChangedSubMaskIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPEthnetInfo tOldEthnetInfo;
	LIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );
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
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}
			
	if ( /*dwIP != tOldEthnetInfo.dwMask || */strCaption != strOldEthnetInfo )
	{
		bChange = true;
		m_bSubMask = TRUE;
	}

	CheckData(m_strEdtSubMask,bChange);
	return true;	
}

bool CCfgCnsLogic::OnChangedCnsLan1Ip(const IArgs& args)
{
	if (m_pWndTree == NULL)
	{
		return false;
	}

	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPWEthnetInfo.atTPEthnetInfo[0].dwIP;
	String strOldWEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldWEthnetInfo )
	{
		strOldWEthnetInfo = "";
	}
	
	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtLan1Ip, strCaption, m_pWndTree);
	
	if ( strCaption != strOldWEthnetInfo )
	{						
		bChange = true;
		m_bCnsIpLan1 = TRUE;
	}
	
	CheckData(m_strEdtLan1Ip, bChange);
	return true;
}


bool CCfgCnsLogic::OnChangedGatewayLan1Ip(const IArgs& args)
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	
	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPWEthnetInfo.atTPEthnetInfo[0].dwGateWay;
	String strOldWEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldWEthnetInfo )
	{
		strOldWEthnetInfo = "";
	}
	
	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGateWayLan1, strCaption, m_pWndTree);		
	if ( strCaption != strOldWEthnetInfo )
	{
		bChange = true;
		m_bGateWayLan1 = TRUE;
	}
	
	CheckData(m_strEdtGateWayLan1, bChange);
	return true;
}

bool CCfgCnsLogic::OnChangedSubMaskLan1Ip(const IArgs& args)
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	
	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPWEthnetInfo.atTPEthnetInfo[0].dwMask;
	String strOldWEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldWEthnetInfo )
	{
		strOldWEthnetInfo = "";
	}
	
	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSubMaskLan1, strCaption, m_pWndTree);
	
	if ( strCaption != strOldWEthnetInfo )
	{
		bChange = true;
		m_bSubMaskLanl = TRUE;
	}
	
	CheckData(m_strEdtSubMaskLan1, bChange);
	return true;
}

bool CCfgCnsLogic::OnChangedCnsLan2Ip(const IArgs& args)
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	
	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPWEthnetInfo.atTPEthnetInfo[1].dwIP;
	String strOldWEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldWEthnetInfo )
	{
		strOldWEthnetInfo = "";
	}
	
	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtLan2Ip, strCaption, m_pWndTree);
	
	if ( strCaption != strOldWEthnetInfo )
	{						
		bChange = true;
		m_bCnsIpLan2 = TRUE;
	}
	
	CheckData(m_strEdtLan2Ip, bChange);
	return true;
}

bool CCfgCnsLogic::OnChangedGatewayLan2Ip(const IArgs& args)
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	
	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPWEthnetInfo.atTPEthnetInfo[1].dwGateWay;
	String strOldWEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldWEthnetInfo )
	{
		strOldWEthnetInfo = "";
	}
	
	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGateWayLan2, strCaption, m_pWndTree);		
	if ( strCaption != strOldWEthnetInfo )
	{
		bChange = true;
		m_bGateWayLan2 = TRUE;
	}
	
	CheckData(m_strEdtGateWayLan2, bChange);
	return true;
}

bool CCfgCnsLogic::OnChangedSubMaskLan2Ip(const IArgs& args)
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	
	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPWEthnetInfo.atTPEthnetInfo[1].dwMask;
	String strOldWEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldWEthnetInfo )
	{
		strOldWEthnetInfo = "";
	}
	
	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSubMaskLan2, strCaption, m_pWndTree);
	
	if ( strCaption != strOldWEthnetInfo )
	{
		bChange = true;
		m_bSubMaskLan2 = TRUE;
	}
	
	CheckData(m_strEdtSubMaskLan2, bChange);
	return true;
}

bool CCfgCnsLogic::OnChangedNATIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}	
	TTPNatCfg tOldNatInfo;
	LIBDATAMGRPTR->GetNATCfg(tOldNatInfo);
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldNatInfo.dwNatIP;
	String strOldNatInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldNatInfo )
	{
		strOldNatInfo = "";
	}
	
	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtNatIP, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}
// 	if ( strCaption == "0." || strCaption == "00." || strCaption == "000." )
// 	{
// 		MSG_BOX_OK( "0不是有效项.请指定一个介于1和223间的值." );
// 		UIFACTORYMGR_PTR->SetCaption( m_strEdtNatIP, "1.", m_pWndTree);
// 		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strCaption, m_pWndTree );
// 		if ( pWnd )
// 		{
// 			(( CEdit *) pWnd)->SetSel( -1 );
// 		}
// 	}

	if ( /*dwIP != tOldNatInfo.dwNatIP || */strCaption != strOldNatInfo )
	{
		bChange = true;
	}

	CheckData(m_strEdtNatIP,bChange);
	return true;	
}

bool CCfgCnsLogic::OnSelNetInterfaceStyle(const IArgs& args)
{
	int nCheckState1;
	UIFACTORYMGR_PTR->GetCheckState( m_strBtnNetBackUp, nCheckState1, m_pWndTree );
	int nCheckState2;
	UIFACTORYMGR_PTR->GetCheckState( m_strBtnDoubleNet, nCheckState2, m_pWndTree );

	EmEthState emEthState;

	if( 1 == nCheckState1 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNetBackup", m_pWndTree );
		SetEthnetCfgData();
		m_vctWndName.clear();
		emEthState = em_BackMode;
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmDoubleNet", m_pWndTree );
		SetWEthnetInfo();
		m_vctWndName.clear();
		emEthState = em_DoubleMode;	
	}

	bool bChange = false;
	if( emEthState != m_emEthState )
	{
		bChange = true;
	}

	CheckData( "RadioBtnSwitch", bChange );
	return true;
}

void CCfgCnsLogic::SetNATData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	TTPNatCfg tNatInfo;
	LIBDATAMGRPTR->GetNATCfg( tNatInfo );

	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tNatInfo.dwNatIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtNatIP, m_pWndTree ); 

	UIFACTORYMGR_PTR->SetSwitchState( m_strBtnNATSwitch, tNatInfo.bUsed, m_pWndTree );
    if ( tNatInfo.bUsed )
    {
		BOOL bInConf = LIBDATAMGRPTR->IsInConf();
		if ( !bInConf )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtNatIP); 
		}
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal",  m_pWndTree ,m_strEdtNatIP);
    }
}

void CCfgCnsLogic::SetCnsInfoData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	TTPCnsInfo tCnsInfo;
	LIBDATAMGRPTR->GetLocalCnsInfo( tCnsInfo );
	
	String strRoomName(tCnsInfo.m_achRoomName);
	UIFACTORYMGR_PTR->SetCaption( m_strNameEdit, strRoomName, m_pWndTree);
	
	String strE164Num(tCnsInfo.m_achE164);
	UIFACTORYMGR_PTR->SetCaption( m_strName164Edit, strE164Num, m_pWndTree);
}

void CCfgCnsLogic::SetEthnetCfgData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	TTPEthnetInfo tEthnetInfo;
	LIBDATAMGRPTR->GetEthnetCfg( tEthnetInfo );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tEthnetInfo.dwIP);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtIp, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tEthnetInfo.dwMask);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSubMask, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tEthnetInfo.dwGateWay);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGateWay, m_pWndTree ); 	
}

void CCfgCnsLogic::SetEthnetSwitchtype()
{
	if( m_emEthState == em_BackMode )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnNetBackUp, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnDoubleNet, 0, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmNetBackup", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnNetBackUp, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnDoubleNet, 1, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmDoubleNet", m_pWndTree );
	}
}

void CCfgCnsLogic::SetWEthnetInfo()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	Value_IpEditData valIp;
	valIp.dwIP = ntohl(m_tTPWEthnetInfo.atTPEthnetInfo[0].dwIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtLan1Ip, m_pWndTree );
	
	valIp.dwIP = ntohl(m_tTPWEthnetInfo.atTPEthnetInfo[0].dwMask);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSubMaskLan1, m_pWndTree );

	valIp.dwIP = ntohl(m_tTPWEthnetInfo.atTPEthnetInfo[0].dwGateWay);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGateWayLan1, m_pWndTree );

	valIp.dwIP = ntohl(m_tTPWEthnetInfo.atTPEthnetInfo[1].dwIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtLan2Ip, m_pWndTree );

	valIp.dwIP = ntohl(m_tTPWEthnetInfo.atTPEthnetInfo[1].dwMask);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSubMaskLan2, m_pWndTree );

	valIp.dwIP = ntohl(m_tTPWEthnetInfo.atTPEthnetInfo[1].dwGateWay);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGateWayLan2, m_pWndTree );

}

bool CCfgCnsLogic::OnUploadProgress( const IArgs & arg )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);
	
	switch( m_emFileFtpStatus )
	{
	case emFtpBegin:
		{
		}
		break;
	case emFtpTransfer:
		{
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP接口0为成功  默认失败
			m_cFtp.EndFtpFile();	
			if ( 0 == dwSuccess )
			{
				if ( m_vecConfFile.size() > 0 )
				{
					vector<String>::iterator itr = m_vecConfFile.begin();
					m_vecConfFile.erase(itr);
					if ( m_vecConfFile.size() > 0 )
					{
						CString cstrPath = GetModuleFullPath();
						string strModulePath = cstrPath.GetBuffer(cstrPath.GetLength());
						if ( !UploadCore( CNSCONFIG_FILE_PATH, strModulePath+m_vecConfFile.at(0), m_vecConfFile.at(0)) )
						{
							COMIFMGRPTR->ConfSignCmd( FALSE, 1 );
							PrtMsg( 0, emEventTypeCmsWindow, "%s还没开始进行ftp传输便失败！", m_vecConfFile.at(0).c_str() );
						}			
					}
					else
					{
						COMIFMGRPTR->ConfSignCmd( TRUE, 1 );
						PrtMsg( 0, emEventTypeCmsWindow, "2张台标图片上传完毕！" );
					}
				}
			}
			else
			{	
				COMIFMGRPTR->ConfSignCmd( FALSE, 1 );
				PrtMsg( 0, emEventTypeCmsWindow, "进行ftp后%s传输失败！", m_vecConfFile.at(0).c_str() );
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				OspPrintf( TRUE, FALSE, "导入文件出错，错误原因：%s！", pszMsg );
				//MSG_BOX_OK(pszMsg);
				LocalFree( pszMsg );
			}		
		}
		break;
	default:
		{
		}
		break;
	}	
	return true;
}

BOOL CCfgCnsLogic::UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName )
{
	CString strIpAddr;
	
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_FTPCONFSIGNPROGRESS );
	
	u32 dwIp;
	LIBDATAMGRPTR->GetLoginIp(dwIp);		
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIp);
	strIpAddr = inet_ntoa(addrIPAddr);

	EmCnModel emCnModel;
	LIBDATAMGRPTR->GetEmCnModelInfo( &emCnModel );
	
	BOOL32 bRet;
	if( LIBDATAMGRPTR->CheckVerNew() == false )
	{
		if( ( emCnModel == T300 ) || ( emCnModel == T300E ) || ( emCnModel == em7920 ) )
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, FTP_CONNECT_USER, FTP_CONNECT_PSWD );
		}
		else
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, T300E_TEL_USRNAME, T300E_TEL_PWD );
		}
	}
	else
	{
		TTPFtpInfo tTPFtpInfo;
		LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
		
		if( tTPFtpInfo.bOpen )
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, tTPFtpInfo.achUserName, tTPFtpInfo.achPassword );
		}
		else
		{
			bRet = 0;
		}
	}

	if ( !bRet )
	{	
		//MSG_BOX_OK("设置FTP上传服务器失败!");
		WARNMESSAGE("设置FTP上传服务器失败!");
		return FALSE;
	}
	
	String strRemoteFilePath = strRemotePath;
	strRemoteFilePath += strCheckFileName;
	
	if ( !m_cFtp.BeginUpload( m_pWnd->GetSafeHwnd(), strRemoteFilePath.c_str(), strLocalFile.c_str(), FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
	{
		//MSG_BOX_OK("上传文件失败，参数错误!");		
		return FALSE;		
	}
	return TRUE;
}

LRESULT CCfgCnsLogic::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 && m_pWndTree != NULL )
	{
// 		MSG_BOX_OK("会议开启，配置不能修改！");
// 		SetNATData();
// 		SetCnsInfoData();
// 		SetEthnetCfgData();
// 		m_vctWndName.clear();
// 		UpBtnState();
		return S_FALSE;
	}
	bool bUseNAT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnNATSwitch, bUseNAT, m_pWndTree );

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree );
		if ( bUseNAT )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtNatIP, false, m_pWndTree );
		}
	} 
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree );
		if ( bUseNAT )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtNatIP, true, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtNatIP, false, m_pWndTree );
		}

        //云服务开启 会场名称与E164号编辑框无效，需置灰
        if ( m_bCloudServerEnable )
        {
            Value_WindowEnable valEnableBtn;
            valEnableBtn.bEnable = false;
            UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, m_strNameEdit, m_pWndTree );
            UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, m_strName164Edit, m_pWndTree );
        }
	}
	return S_OK;
}

LRESULT CCfgCnsLogic::OnVerInfoNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	s8* chVerInfo = (s8*)wparam;

    //去除4K终端型号前缀，格式：“XXX(终端型号)-”
    CString strVerInfo = chVerInfo;
    CString strHardWare = strVerInfo.Left(strlen("T300E-4K-"));

    u8 byOffset = 0;
    if ( strHardWare == "T300E-4K-" )
    {
        byOffset = strHardWare.GetLength();
    }

	UIFACTORYMGR_PTR->SetCaption( "StcVersionInfo", chVerInfo+byOffset, m_pWndTree, true);
	return S_OK;
}
