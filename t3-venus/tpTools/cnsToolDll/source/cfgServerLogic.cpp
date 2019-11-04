// cfgServerLogic.cpp: implementation of the CCfgServerLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgServerLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgServerLogic::CCfgServerLogic()
: m_strEdtSIp("CfgServerNorDlg/SIPCtrlAddress")
, m_strBtnGKSwitch("CfgServerNorDlg/BtnGKSwitch")
, m_strEdtGKIP("CfgServerNorDlg/IPCtrlGKIp")
, m_strEdtCSIP("CfgServerNorDlg/IPCtrlCallServer")
, m_strEdtUGIP("CfgServerNorDlg/IPCtrlUpAddress")
, m_strEdtDCIP("CfgServerNorDlg/IPCtrlDataConfSer")
, m_strEdtMatrixIP("CfgServerNorDlg/IPCtrlDataMatrix")
, m_strBtnQTSwitch("CfgServerNorDlg/BtnQuantumEncrySwitch")
, m_strEdtQtIP("CfgServerNorDlg/IPCtrlDataQuantumEncry")
, m_strEdtQtID("CfgServerNorDlg/IPCtrlIDQuantumEncry")
, m_strEdtTimeSyncIP("CfgServerNorDlg/IPCtrlDataTimeSync")	
, m_strBtnCloudSwitch("CfgServer4KDlg/BtnCloudSwitch")
, m_strEdtCloudIP("CfgServer4KDlg/IPCtrlCloudIp")
, m_strEdtCloudUser("CfgServer4KDlg/IPCtrlCloudUser")
, m_strEdtCloudPW("CfgServer4KDlg/IPCtrlCloudPW")	 
{
	m_vctWndName.clear();
	m_bIsTptoolsSaveQtInfo = FALSE;
}

CCfgServerLogic::~CCfgServerLogic()
{

}

bool CCfgServerLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

void CCfgServerLogic::RegMsg()
{
	CCfgServerLogic *pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNS_REG_GK_NTY, CCfgServerLogic::OnUpdateGkNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNS_REGSIP_NOTIFY, CCfgServerLogic::OnUpdateSipNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CallSer_NTY, CCfgServerLogic::OnCallSerNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeSer_NTY, CCfgServerLogic::OnUpgradeSerNty, pThis, CCfgServerLogic );
	//注册网呈服务器消息反馈
	REG_MSG_HANDLER( UI_CNS_SIPREG_ALIASREPEAT_NOTIFY, CCfgServerLogic::OnRegSIPAliasRepeatNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNS_REGRESULT_NOTIFY, CCfgServerLogic::OnRegSIPResultNty, pThis, CCfgServerLogic );
	//注册GK消息反馈
	REG_MSG_HANDLER( UI_CNS_REG_GK_RSP, CCfgServerLogic::OnRegGKRsp, pThis, CCfgServerLogic );
	//注册呼叫服务器消息反馈
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CallSer_IND, CCfgServerLogic::OnCallSerInd, pThis, CCfgServerLogic );
	//注册升级服务器消息反馈
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeSer_IND, CCfgServerLogic::OnUpgradeSerInd, pThis, CCfgServerLogic );
	//接收会议状态消息
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCfgServerLogic::OnConfStateNty, pThis, CCfgServerLogic );
	//数据会议服务器消息反馈 14/9/4
	REG_MSG_HANDLER( UI_TPPSETDATASERVERINFONTY, CCfgServerLogic::OnWBServerNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_TPPSETDATASERVER_IND, CCfgServerLogic::OnWBServerInd, pThis, CCfgServerLogic );
	//矩阵服务器消息反馈
	REG_MSG_HANDLER( UI_TPSETMATRIXSERVERINFO_NTY, CCfgServerLogic::OnSetMatrixServerInfoNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_TPSETMATRIXSERVERINFO_IND, CCfgServerLogic::OnSetMatrixServerInfoInd, pThis, CCfgServerLogic );
	//量子加密服务器消息反馈
	REG_MSG_HANDLER( UI_SETQTENCRYPTINFO_Nty, CCfgServerLogic::OnSetQtEncryptInfoNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_SETQTENCRYPTINFO_Ind, CCfgServerLogic::OnSetQtEncryptInfoInd, pThis, CCfgServerLogic );

	//时间同步服务器消息反馈
	REG_MSG_HANDLER( UI_TPSETNTPSERVERINFO_NTY, CCfgServerLogic::OnSetNtpServerInfoNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_TPSETNTPSERVERINFO_IND, CCfgServerLogic::OnSetNtpServerInfoInd, pThis, CCfgServerLogic );

	//云服务器配置
	REG_MSG_HANDLER( UI_CNC_CLOUDSERVER_IND, CCfgServerLogic::OnSetCloudServerInfoInd, pThis, CCfgServerLogic );
    //收到版本通知
    REG_MSG_HANDLER( UI_CNSTOOL_VERINFO_NTY, CCfgServerLogic::OnVerInfoNty, pThis, CCfgServerLogic );
	
}

void CCfgServerLogic::UnRegMsg()
{
	
}

void CCfgServerLogic::RegCBFun()
{
	CCfgServerLogic *pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::InitWnd", CCfgServerLogic::InitWnd, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnSave", CCfgServerLogic::OnBtnSave, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnCancel", CCfgServerLogic::OnBtnCancel, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnSwitchGK", CCfgServerLogic::OnBtnSwitchGK, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedSIp", CCfgServerLogic::OnChangedSIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedGKIp", CCfgServerLogic::OnChangedGKIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedCallSerIp", CCfgServerLogic::OnChangedCallSerIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedUpSerIp", CCfgServerLogic::OnChangedUpSerIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedDataConfSerIP",CCfgServerLogic::OnChangedDataConfSerIP, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedDataMatrix",CCfgServerLogic::OnChangedDataMatrix, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnSwitchQuantumEncry", CCfgServerLogic::OnBtnSwitchQuantumEncry, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedDataQuantumEncryIP",CCfgServerLogic::OnChangedDataQuantumEncryIP, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedQuantumEncryID",CCfgServerLogic::OnChangedQuantumEncryID, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedDataTimeSyncIP",CCfgServerLogic::OnChangedDataTimeSyncIP, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnSwitchCloud", CCfgServerLogic::OnBtnSwitchCloud, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedCloudIp", CCfgServerLogic::OnChangedCloudIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedCloudUser", CCfgServerLogic::OnChangedCloudUser, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedCloudPW", CCfgServerLogic::OnChangedCloudPW, pThis, CCfgServerLogic );
}

void CCfgServerLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCfgServerLogic::InitWnd" );	
}

void CCfgServerLogic::Clear()
{
	m_bIsTptoolsSaveQtInfo = FALSE;
	m_vctWndName.clear();
	UpBtnState();

}

bool CCfgServerLogic::OnBtnSave( const IArgs& args )
{
    EmCnModel emCnModel;
    LIBDATAMGRPTR->GetEmCnModelInfo( &emCnModel );

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("有会议进行中，不能配置") );
        if ( emCnModel == T300E_4K )
        {
            SetGKData();
            SetCloudData();
		    SetSipData();
        }
        else
        {
            SetCallSerData();
            SetGKData();
            SetSipData();
            SetUpgradeSerData();
            SetDataConfSerData();
            SetMatrixSerData();
            SetQtEncryptData();
		    SetNtpSerData();
        }

		m_vctWndName.clear();
		UpBtnState();
		OnConfStateNty(0,0);
		return false;	
	}

	bool bSucceed = true;

    if (emCnModel == T300E_4K)
    {
        bSucceed = SaveSip();
        if (false == bSucceed)
        {
            return false;
        }
        bSucceed = SaveGk();
        if (false == bSucceed)
        {
            return false;
        }
        bSucceed = SaveCloud();
        if (false == bSucceed)
        {
            return false;
        }
    }
    else
    {
        bSucceed = SaveSip();
        if (false == bSucceed)
        {
            return false;
        }
        bSucceed = SaveGk();
        if (false == bSucceed)
        {
            return false;
        }
        bSucceed = SaveCallSer();
        if (false == bSucceed)
        {
            return false;
        }
        bSucceed = SaveUpgradeSer();
        if (false == bSucceed)
        {
            return false;
        }
        bSucceed = SaveDataConfSer();
        if (false == bSucceed)
        {
            return false;
        }
        bSucceed = SaveMatrixSer();
        if (false == bSucceed)
        {
            return false;
        }
        bSucceed = SaveQtEncryptSer();
        if (false == bSucceed)
        {
            return false;
        }
        bSucceed = SaveNtpSer();
        if (false == bSucceed)
        {
            return false;
        }
    }

	m_vctWndName.clear();
	UpBtnState();
	return true;
}

bool CCfgServerLogic::OnBtnCancel( const IArgs& args )
{
    EmCnModel emCnModel;
    LIBDATAMGRPTR->GetEmCnModelInfo( &emCnModel );
    if ( emCnModel == T300E_4K )
    {
        SetCloudData();
        SetGKData();
        SetSipData();
    }
    else
    {
        SetCallSerData();
        SetGKData();
        SetSipData();
        SetUpgradeSerData();
        SetDataConfSerData();
        SetMatrixSerData();
        SetNtpSerData();
        SetQtEncryptData();
    }

	m_vctWndName.clear();
	UpBtnState();
	//当会议开启后,配置界面取消保存后将全部界面置灰
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		OnConfStateNty(0,0);
		return false;	
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
void CCfgServerLogic::FocusWindow(String strWindow)
{
	UIFACTORYMGR_PTR->SetFocus( strWindow, m_pWndTree );
}

/*---------------------------------------------------------------------
* 函数名称：SaveSip
* 功    能：保存注册网呈服务器部分	
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgServerLogic::SaveSip( /*const IArgs& args*/ )
{		
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	String strServiceIp;
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtSIp, m_pWndTree ); 
	
	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSIp, strCaption, m_pWndTree );
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "网呈服务器地址非法" );
		FocusWindow(m_strEdtSIp);
		return false;
	}

	TTPSipRegistrarCfg tSipcfg;
	if ( strCaption.empty() )
	{  
		tSipcfg.bUsed = FALSE;
		tSipcfg.dwRegIP = 0;
		tSipcfg.wRegPort = 5060;
		tSipcfg.wExpire = 40;
	}
	else
	{	
		tSipcfg.bUsed = TRUE;
		tSipcfg.dwRegIP = htonl(valIp.dwIP);
		tSipcfg.wRegPort = 5060;
		tSipcfg.wExpire = 40;
	}		
	
	TTPSipRegistrarCfg tOldSipCfg;
	LIBDATAMGRPTR->GetSipCfg( tOldSipCfg );
	
	if ( tSipcfg.dwRegIP != tOldSipCfg.dwRegIP )
	{		 
		u16 wRet = COMIFMGRPTR->CnsRegSipService( tSipcfg );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存网呈服务器配置请求发送失败" );
			return false;
		}
	}
	return true;
}

/*---------------------------------------------------------------------
* 函数名称：SaveGk
* 功    能：保存GK设置
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgServerLogic::SaveGk()
{	
	//GK设置
    TTPGKCfg tOldGkCfg;
    LIBDATAMGRPTR->GetGkCfg( tOldGkCfg );
	
    bool bUseGk = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGk, m_pWndTree );
	
    Value_IpEditData valGkIp;
	UIFACTORYMGR_PTR->GetPropertyValue(valGkIp, m_strEdtGKIP, m_pWndTree); 
	
	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGKIP , strCaption , m_pWndTree ); 

    if ( ( bUseGk != (bool)tOldGkCfg.bUsed ) || htonl( valGkIp.dwIP ) != tOldGkCfg.dwGKIP )
	{   
		if ( bUseGk == true )
		{
			if ( !CCallAddr::IsValidIpV4(valGkIp.dwIP ) )
			{
				if ( strCaption.empty() == true )
				{
					MSG_BOX_OK( "GK服务器地址不能为空" );
				}
				else
				{
					MSG_BOX_OK( "GK服务器地址非法" );
				}
				FocusWindow(m_strEdtGKIP);

				return false;
			}
		}
		else
		{
			if ( !CCallAddr::IsValidIpV4(valGkIp.dwIP) && !strCaption.empty() )
			{
				MSG_BOX_OK( "GK服务器地址非法" );
				SetGKData();
				return false;
			} 
		}

		TTPGKCfg tGkcfg; 
		tGkcfg.wExpire = 40; 
		tGkcfg.bUsed = bUseGk;
		tGkcfg.dwGKIP = htonl(valGkIp.dwIP);  
	
        u16 wRet  = COMIFMGRPTR->CnsRegGkService( tGkcfg );
		if (wRet != NO_ERROR)
		{
			//MSG_BOX_OK( "保存GK配置请求发送失败" );
			WARNMESSAGE( "保存GK服务器配置请求发送失败" );
			return false;
		}		 
	}
	return true;
}

bool CCfgServerLogic::SaveCloud()
{
	//云服务器设置
    TTPCloudPlatServerCfg tOldCloudCfg;
    LIBDATAMGRPTR->GetCloudCfg( tOldCloudCfg );
	
    bool bOpenCloud = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnCloudSwitch, bOpenCloud, m_pWndTree );
	
    //Value_IpEditData valCloudIp;
	//UIFACTORYMGR_PTR->GetPropertyValue(valCloudIp, m_strEdtCloudIP, m_pWndTree); 

	String strIPCaption;
	String strUsrCaption;
	String strPwdCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCloudIP, strIPCaption, m_pWndTree);
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCloudUser, strUsrCaption, m_pWndTree);
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCloudPW, strPwdCaption, m_pWndTree);
	
	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCloudIP , strCaption , m_pWndTree ); 
	
    if ( ( bOpenCloud != (bool)tOldCloudCfg.m_bEnable ) || strcmp(tOldCloudCfg.m_achServerIP , strIPCaption.c_str()) != 0 || 
		strcmp(tOldCloudCfg.m_achUsrName , strUsrCaption.c_str()) != 0 || strcmp(tOldCloudCfg.m_achPwd , strPwdCaption.c_str()) != 0  )
	{   
		if ( bOpenCloud == true )
		{
			if ( strCaption.empty() )
			{
				MSG_BOX_OK( "云服务器地址不能为空" );
				FocusWindow(m_strEdtGKIP);
				return false;
			}

			if(strUsrCaption.empty() || !UIDATAMGR_PTR->IsValidCloudUNStr(strUsrCaption.c_str()))
			{
				MSG_BOX_OK( "云用户名错误" );
				FocusWindow(m_strEdtCloudUser);
				return false;
			}

            if ( strPwdCaption.empty() )
            {
                MSG_BOX_OK("云用户密码不能为空");
                FocusWindow(m_strEdtCloudPW);
                return false;
            }

            if ( strPwdCaption.length() < 6 )
            {
                MSG_BOX_OK("密码长度需在6-32位");
                FocusWindow(m_strEdtCloudPW);
				return false;
            }

			if( !UIDATAMGR_PTR->IsValidCloudPWStr(strPwdCaption.c_str()) )
			{
				MSG_BOX_OK("云用户密码错误");
				FocusWindow(m_strEdtCloudPW);
				return false;
			}
		}
		else
		{
			if ( !CCallAddr::IsValidIpV4(inet_addr(strIPCaption.c_str())) && !strCaption.empty() )
			{
				strIPCaption = tOldCloudCfg.m_achServerIP;
				//valCloudIp.dwIP = UIDATAMGR_PTR->swapInt32( inet_addr(tOldCloudCfg.m_achServerIP));
// 				MSG_BOX_OK( "云服务器地址非法" );
// 				SetCloudData();
// 				return false;
			} 
			if(strUsrCaption.empty() || !UIDATAMGR_PTR->IsValidCloudUNStr(strUsrCaption.c_str()))
			{
				strUsrCaption = tOldCloudCfg.m_achUsrName;
// 				MSG_BOX_OK( "云用户名错误" );
// 				SetCloudData();
// 				return false;
			}
			if(strPwdCaption.empty() || !UIDATAMGR_PTR->IsValidCloudPWStr(strPwdCaption.c_str()))
			{
				strPwdCaption = tOldCloudCfg.m_achPwd;
// 				MSG_BOX_OK("云用户密码错误");
// 				SetCloudData();
// 				return false;
			}
		}
		
		TTPCloudPlatServerCfg tCloudcfg; 
		tCloudcfg.m_bEnable = bOpenCloud;
// 		in_addr tAddr;
// 		tAddr.S_un.S_addr = UIDATAMGR_PTR->swapInt32(valCloudIp.dwIP);
		strcpy(tCloudcfg.m_achServerIP , strIPCaption.c_str()); 
		strcpy(tCloudcfg.m_achUsrName , strUsrCaption.c_str());  
		strcpy(tCloudcfg.m_achPwd , strPwdCaption.c_str());  
		
        u16 wRet  = COMIFMGRPTR->SetCloudServerInfo( tCloudcfg );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存云服务器配置请求发送失败" );
			return false;
		}		 
	}
	return true;
}

LRESULT CCfgServerLogic::OnUpdateGkNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetGKData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnUpdateSipNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetSipData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnRegSIPAliasRepeatNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	TTPRegNameRepeatInfo tRepeatInfo = *(TTPRegNameRepeatInfo*)wParam;
	
	CString strName;
	strName.Format( "%s注册网呈服务器失败：", (s8*)lParam );
	
	CString strTemp = "注册别名重复";
	
	u32 dwSize = tRepeatInfo.dwsize;
	if ( 1 == dwSize )
	{
		TTPRegName tRegName = tRepeatInfo.atTPRegName[0];
		if ( tRegName.emPAAddrType == emTpAlias )
		{
			strTemp = "会场名称重复";
		}
		else if ( tRegName.emPAAddrType == emTpE164Num )
		{
			strTemp = "会场号码重复";
		}
	}
	else if ( 2 == dwSize )
	{
		strTemp = "会场名称和会场号码都重复";
	}
	strName = strName + strTemp;
	//MSG_BOX_OK((String)strName);
	WARNMESSAGE(strName);
	FocusWindow(m_strEdtSIp);
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_SIPRsp_NTY, 0, 0 );
	return S_OK;
}

LRESULT CCfgServerLogic::OnRegSIPResultNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	EmTpCnsRegUms emReg = (EmTpCnsRegUms)wParam;
	
	BOOL bOk = FALSE;
	CString strTemp = "";
    switch( emReg )
    {		
    case tp_CnsRegRet_Success:		//成功
        bOk  = TRUE;
        break;
    case tp_CnsRegRet_MaxRegNum:		//注册满
        strTemp = "注册个数已达到最大值";
        break;
    case tp_CnsRegRet_MaxAliasNum:	//注册满
        strTemp = "注册别名的个数已达到最大值";
        break;
    case tp_CnsRegRet_MsgError:		//注册消息错误
        strTemp = "注册消息错误";
        break;
    case tp_CnsRegRet_AliasRepeat:	//别名重复
        strTemp = "注册别名重复";
        break;
    case tp_CnsRegRet_UnReg:		//删除时，未找到删除记录
        strTemp = "未找到删除记录";
        break;
    case tp_CnsRegRet_SysError:		//APP错误
        strTemp = "APP错误";
        break;
    case tp_CnsRegRet_NotFind:		//查找失败
        strTemp = "查找失败";
        break;   
    case tp_CnsRegRet_Unreachable:   //服务器不可达
        strTemp = "服务器不可达";
        break;
    default:
		strTemp = ""; //"未知错误";  
    }
	
	
    CString strName;
	
	if ( bOk )
	{
		//MSG_BOX_OK( "注册SIP服务器成功" );
		WARNMESSAGE( "注册网呈服务器成功" );
	}
	else
	{   
		strName = "注册网呈服务器失败";
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + "：" + strTemp;
		}
		//String str(strName);
		//MSG_BOX_OK(str);
		WARNMESSAGE(strName);
		FocusWindow(m_strEdtSIp);
	}
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_SIPRsp_NTY, (WPARAM)bOk, 0 );
	return S_OK;
}

LRESULT CCfgServerLogic::OnRegGKRsp( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
    bool bOk = false;
    TUCSipRegResult tRegResult = *(TUCSipRegResult*)wParam;
	
    CString strTemp = "";
    switch( tRegResult.m_emTpCnsRegUms )
    {  
    case tp_CnsRegRet_Success:		//成功
        bOk  = true;
        break;
    case tp_CnsRegRet_MaxRegNum:		//注册满
        strTemp = "注册个数已达到最大值";
        break;
    case tp_CnsRegRet_MaxAliasNum:	//注册满
        strTemp = "注册别名的个数已达到最大值";
        break;
    case tp_CnsRegRet_MsgError:		//注册消息错误
        strTemp = "注册消息错误";
        break;
    case tp_CnsRegRet_AliasRepeat:	//别名重复
        strTemp = "注册别名重复";
        break;
    case tp_CnsRegRet_UnReg:	    //删除时，未找到删除记录
        strTemp = "未找到该记录";
        break;
    case tp_CnsRegRet_SysError:		//APP错误
        strTemp = "APP错误";
        break;
    case tp_CnsRegRet_NotFind:		//查找失败
        strTemp = "查找失败";
        break;   
    case tp_CnsRegRet_Unreachable:   //服务器不可达
        strTemp = "服务器不可达";
        break;
    default:
		strTemp = "";
		break;
    }
	
	CString strName = "注册GK服务器失败";
	
	if ( bOk )
	{
		//MSG_BOX_OK( "注册GK成功" );
		WARNMESSAGE( "注册GK服务器成功" );
	}
	else
	{
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + "：" + strTemp;
		}
		
		//MSG_BOX_OK((String)strName);
		WARNMESSAGE(strName);
		FocusWindow(m_strEdtGKIP);
	}
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_GKRsp_NTY, (WPARAM)bOk, 0 );
	return S_OK;
}

bool CCfgServerLogic::OnBtnSwitchGK( const IArgs& args )
{
	TTPGKCfg tGkCfg;
	LIBDATAMGRPTR->GetGkCfg( tGkCfg );

	bool bUseGK = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGK, m_pWndTree );
    if ( bUseGK )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtGKIP); 
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtGKIP);
    }

	bool bChange = false;
	if ( (BOOL)bUseGK != tGkCfg.bUsed )
	{
		bChange = true;
	}	
	CheckData(m_strBtnGKSwitch,bChange);
	return true;	
}

bool CCfgServerLogic::OnBtnSwitchQuantumEncry( const IArgs& args )
{
	TTpQtEncryptCfg tTpQtEncryptCfg;
	LIBDATAMGRPTR->GetQtEncryptCfg(tTpQtEncryptCfg);

	bool bUseQT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnQTSwitch, bUseQT, m_pWndTree );
    if ( bUseQT )
    {
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree, m_strEdtQtIP); 
        UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree, m_strEdtQtID); 
    }
    else
    {   
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree, m_strEdtQtIP); 
        UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree,m_strEdtQtID);
    }

	bool bChange = false;
	if ( (BOOL)bUseQT != tTpQtEncryptCfg.m_bOpen )
	{
		bChange = true;
	}	
	CheckData(m_strBtnQTSwitch,bChange);
	
	return true;	
}

LRESULT CCfgServerLogic::OnSetCloudServerInfoInd( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}

    BOOL bSuccess = (BOOL)lParam;
    if ( !bSuccess )
    {
        WARNMESSAGE("云服务器配置失败");
        return S_FALSE;
    }

	SetCloudData();
	return S_OK;
}

bool CCfgServerLogic::OnBtnSwitchCloud( const IArgs& args )
{
	TTPCloudPlatServerCfg tCloudCfg;
	LIBDATAMGRPTR->GetCloudCfg( tCloudCfg );
	
	bool bUseCloud = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnCloudSwitch, bUseCloud, m_pWndTree );
    if ( bUseCloud )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtCloudIP); 
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtCloudUser); 
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtCloudPW);
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtCloudIP);
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtCloudUser);
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtCloudPW);
    }
	
	bool bChange = false;
	if ( (BOOL)bUseCloud != tCloudCfg.m_bEnable )
	{
		bChange = true;
	}	
	CheckData(m_strBtnCloudSwitch,bChange);
	return true;	
}

LRESULT CCfgServerLogic::OnCallSerNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetCallSerData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnCallSerInd( WPARAM wParam, LPARAM lParam )
{	
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		//MSG_BOX_OK("设置呼叫服务器地址失败");
		WARNMESSAGE("设置呼叫服务器地址失败");
		FocusWindow(m_strEdtCSIP);
	} 
	return S_OK;	
}

bool CCfgServerLogic::SaveCallSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtCSIP, m_pWndTree ); 
	
	TTPCallSerInfo tCallSerInfo;
	tCallSerInfo.dwCallServiceIP = htonl(valIp.dwIP);
	
	TTPCallSerInfo tOldCallSerInfo;
	LIBDATAMGRPTR->GetCallServerInfo(tOldCallSerInfo);

	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCSIP, strCaption, m_pWndTree );
	
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "呼叫服务器地址非法" );
		FocusWindow(m_strEdtCSIP);
		return false;
	}

	if ( tOldCallSerInfo.dwCallServiceIP != tCallSerInfo.dwCallServiceIP )
	{
		u16 wRet = COMIFMGRPTR->CallServerCmd( tCallSerInfo );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存呼叫服务器配置请求发送失败" );
			return false;
		}
	}
	return true;
}

bool CCfgServerLogic::IsCfgSerChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCfgServerLogic::SaveMsgBox()
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

bool CCfgServerLogic::OnChangedSIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}	
	TTPSipRegistrarCfg tOldSipCfg;
	LIBDATAMGRPTR->GetSipCfg( tOldSipCfg );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldSipCfg.dwRegIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtSIp );
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSIp, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

	if ( /*dwIP != tOldSipCfg.dwRegIP || */strCaption != strOldInfo )
	{
	 	bChange = true;		
	}

	CheckData(m_strEdtSIp,bChange);
	return true;
}

bool CCfgServerLogic::OnChangedGKIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPGKCfg tOldGkCfg;
    LIBDATAMGRPTR->GetGkCfg( tOldGkCfg );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldGkCfg.dwGKIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}

	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtGKIP );
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGKIP, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

    if ( /*dwIP != tOldGkCfg.dwGKIP || */strCaption != strOldInfo )
	{ 
		bChange = true;	
	}

	CheckData(m_strEdtGKIP,bChange);
	return true;	
}

bool CCfgServerLogic::OnChangedCallSerIp( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtCSIP );

	TTPCallSerInfo tCallSerInfo;
	LIBDATAMGRPTR->GetCallServerInfo(tCallSerInfo);
	in_addr tAddr;
	tAddr.S_un.S_addr = tCallSerInfo.dwCallServiceIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCSIP, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

	if ( /*dwIP != tCallSerInfo.dwCallServiceIP || */strCaption != strOldInfo )
	{ 
		bChange = true;	
	}
	
	CheckData(m_strEdtCSIP,bChange);
	return true;	
}

bool CCfgServerLogic::OnChangedUpSerIp( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtUGIP );

	TTPUpgradeSer tUpgradeSer;
	LIBDATAMGRPTR->GetUpgradeSerInfo( tUpgradeSer );
	in_addr tAddr;
	tAddr.S_un.S_addr = tUpgradeSer.dwSerIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtUGIP, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

	if ( /*dwIP != tUpgradeSer.dwSerIP || */strCaption != strOldInfo )
	{ 
		bChange = true;	
	}

	CheckData(m_strEdtUGIP, bChange);
	return true;		
}

bool CCfgServerLogic::OnChangedCloudIp( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	
	TTPCloudPlatServerCfg tCloudSer;
	LIBDATAMGRPTR->GetCloudCfg( tCloudSer );
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCloudIP, strCaption, m_pWndTree);
	
	if ( strcmp(strCaption.c_str() , tCloudSer.m_achServerIP ) != 0 )
	{ 
		bChange = true;	
	}
	
	CheckData(m_strEdtUGIP, bChange);
	return true;		
}

bool CCfgServerLogic::OnChangedCloudUser( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	
	TTPCloudPlatServerCfg tCloudSer;
	LIBDATAMGRPTR->GetCloudCfg( tCloudSer );
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCloudUser, strCaption, m_pWndTree);

    CString strTemp = strCaption.c_str();
    strTemp = strTemp.SpanIncluding( _T("0123456789*#") );
    s32 nPos = strTemp.GetLength();
    if( strTemp.GetLength() != strCaption.length() )
    {
        strCaption = strCaption.erase(nPos,1); 
        UIFACTORYMGR_PTR->SetCaption( m_strEdtCloudUser, strCaption, m_pWndTree);
        Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtCloudUser, m_pWndTree );
        if ( CTransparentEdit* pCWnd = ( CTransparentEdit* )pWnd )
        {
            pCWnd->SetSel( -1 );
		}
        return true;
    }
	
	if ( strcmp(strCaption.c_str() , tCloudSer.m_achUsrName ) != 0 )
	{ 
		bChange = true;	
	}
	
	CheckData(m_strEdtUGIP, bChange);
	return true;		
}

bool CCfgServerLogic::OnChangedCloudPW( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	
	TTPCloudPlatServerCfg tCloudSer;
	LIBDATAMGRPTR->GetCloudCfg( tCloudSer );
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCloudPW, strCaption, m_pWndTree);
	
	if ( strcmp(strCaption.c_str() , tCloudSer.m_achPwd ) != 0 )
	{ 
		bChange = true;	
	}
	
	CheckData(m_strEdtUGIP, bChange);
	return true;		
}

void CCfgServerLogic::SetGKData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	TTPGKCfg tGkCfg;
	LIBDATAMGRPTR->GetGkCfg( tGkCfg );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tGkCfg.dwGKIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGKIP, m_pWndTree ); 

	UIFACTORYMGR_PTR->SetSwitchState( m_strBtnGKSwitch, tGkCfg.bUsed, m_pWndTree );
    if ( tGkCfg.bUsed )
    {
		BOOL bInConf = LIBDATAMGRPTR->IsInConf();
		if ( !bInConf )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtGKIP); 
		}
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtGKIP);
    }
	CheckData(m_strBtnGKSwitch,false);
	CheckData(m_strEdtGKIP,false);
}

void CCfgServerLogic::SetCloudData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	TTPCloudPlatServerCfg tCloudCfg;
	LIBDATAMGRPTR->GetCloudCfg( tCloudCfg );
	
	//Value_IpEditData valIp;
	//if (strcmp(tCloudCfg.m_achServerIP , "") == 0)
	//{
	//	valIp.dwIP = 0;
	//}
	//else
	//{
	//	valIp.dwIP = UIDATAMGR_PTR->swapInt32( inet_addr(tCloudCfg.m_achServerIP) );
	//}
	//UIFACTORYMGR_PTR->SetPropertyValue( tCloudCfg.m_achServerIP, m_strEdtCloudIP, m_pWndTree ); 

	String strServerIP = tCloudCfg.m_achServerIP;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtCloudIP, strServerIP, m_pWndTree ); 
	String strUsername = tCloudCfg.m_achUsrName;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtCloudUser, strUsername, m_pWndTree ); 
	String strPassword = tCloudCfg.m_achPwd;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtCloudPW, strPassword, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetSwitchState( m_strBtnCloudSwitch, tCloudCfg.m_bEnable, m_pWndTree );
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();

    if ( tCloudCfg.m_bEnable && !bInConf )
    {
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtCloudIP); 
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtCloudUser); 
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtCloudPW); 
    }
    else
    {   
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, m_strEdtCloudIP); 
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, m_strEdtCloudUser); 
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, m_strEdtCloudPW); 
    }

	CheckData(m_strBtnCloudSwitch,false);
	CheckData(m_strEdtCloudIP,false);
	CheckData(m_strEdtCloudUser,false);
	CheckData(m_strEdtCloudPW,false);
}

void CCfgServerLogic::SetSipData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	TTPSipRegistrarCfg tSipCfg;
	LIBDATAMGRPTR->GetSipCfg( tSipCfg );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tSipCfg.dwRegIP);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSIp, m_pWndTree ); 
}

void CCfgServerLogic::SetCallSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	TTPCallSerInfo tCallSerInfo;
	LIBDATAMGRPTR->GetCallServerInfo(tCallSerInfo);

	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tCallSerInfo.dwCallServiceIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtCSIP, m_pWndTree ); 
}

LRESULT CCfgServerLogic::OnUpgradeSerNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetUpgradeSerData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnUpgradeSerInd( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		//MSG_BOX_OK("设置升级服务器地址失败");
		WARNMESSAGE("设置升级服务器地址失败");
		FocusWindow(m_strEdtUGIP);
	} 
	return S_OK;
}

void CCfgServerLogic::SetUpgradeSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	TTPUpgradeSer tUpgradeSer;
	LIBDATAMGRPTR->GetUpgradeSerInfo( tUpgradeSer );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tUpgradeSer.dwSerIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtUGIP, m_pWndTree ); 
}

bool CCfgServerLogic::SaveUpgradeSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtUGIP, m_pWndTree ); 

	TTPUpgradeSer tOldUpgradeSer;
	LIBDATAMGRPTR->GetUpgradeSerInfo( tOldUpgradeSer );

	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtUGIP, strCaption, m_pWndTree );

	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "升级服务器地址非法" );
		FocusWindow(m_strEdtUGIP);
		return false;
	}

	if ( htonl(valIp.dwIP) != tOldUpgradeSer.dwSerIP )
	{
		TTPUpgradeSer tUpgradeSer;
		tUpgradeSer.dwSerIP = htonl(valIp.dwIP);
		u16 wRet = COMIFMGRPTR->UpgradeSerCmd( tUpgradeSer );
		if (wRet != NO_ERROR)
		{
			//MSG_BOX_OK( "保存升级服务器配置请求发送失败" );
			WARNMESSAGE( "保存升级服务器配置请求发送失败" );
			return false;
		}
	}
	return true;
}

LRESULT CCfgServerLogic::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0  && m_pWndTree != NULL )
	{
		return S_FALSE;
	}
	bool bUseGk = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGk, m_pWndTree );

	bool bUseCloud = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnCloudSwitch, bUseCloud, m_pWndTree );

	bool bUseQT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnQTSwitch, bUseQT, m_pWndTree );

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree );
		if ( bUseGk )		//会议中所有的窗口置为disable状态
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtGKIP, false, m_pWndTree );
		}
		if ( bUseCloud )		//会议中所有的窗口置为disable状态
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtCloudIP, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtCloudUser, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtCloudPW, false, m_pWndTree );
		}
	} 
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree );
		if ( bUseGk )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtGKIP, true, m_pWndTree );
		} 
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtGKIP, false, m_pWndTree );
		}
		if ( bUseCloud )		//会议中所有的窗口置为disable状态
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtCloudIP, true, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtCloudUser, true, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtCloudPW, true, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtCloudIP, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtCloudUser, false, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtCloudPW, false, m_pWndTree );
		}
		if (!bUseQT)
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree, m_strEdtQtIP); 
			UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree, m_strEdtQtID); 
		}
	}
	return S_OK;
}

DWORD CCfgServerLogic::StrToDWIp( String strName )
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( strName, strCaption, m_pWndTree);
	if ( strCaption == "0." || strCaption == "00." || strCaption == "000." )
	{
		MSG_BOX_OK( "0不是有效项.请指定一个介于1和223间的值." );
		UIFACTORYMGR_PTR->SetCaption( strName, "1.", m_pWndTree);
		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strName, m_pWndTree );
		if ( pWnd )
		{
			(( CEdit *) pWnd)->SetSel( -1 );
		}
	}
	DWORD dwIP = inet_addr(strCaption.c_str());
	if ( strCaption.empty() )
	{
		dwIP = 0;
	}
	return dwIP;
}

// 数据会议服务器地址设置逻辑/消息交互 14/9/4
LRESULT CCfgServerLogic::OnWBServerNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}

	SetDataConfSerData();
	return S_OK;
}

bool CCfgServerLogic::OnChangedDataConfSerIP( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	
    TTPDataConfInfo tWBSerIp;
	LIBDATAMGRPTR->GetWBSerIp( tWBSerIp );
	in_addr tAddr;
	tAddr.S_un.S_addr = tWBSerIp.dwSerIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtDCIP, strCaption, m_pWndTree);
	
	if ( strCaption != strOldInfo )
	{ 
		bChange = true;	
	}
	
	CheckData(m_strEdtDCIP,bChange);
	return true;	
}

bool CCfgServerLogic::OnChangedDataMatrix(const IArgs& args)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	bool bChange = false;
	TTPMatrixServerInfo tTPMatrixServerInfo;
	LIBDATAMGRPTR->GetMatrixSerInfo(tTPMatrixServerInfo);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTPMatrixServerInfo.m_dwSerIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtMatrixIP, strCaption, m_pWndTree);
	
	if ( strCaption != strOldInfo )
	{ 
		bChange = true;	
	}
	
	CheckData( m_strEdtMatrixIP, bChange );
	
	return true;
}

bool CCfgServerLogic::OnChangedDataQuantumEncryIP(const IArgs& args)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	bool bChange = false;
	TTpQtEncryptCfg tTpQtEncryptCfg;
	LIBDATAMGRPTR->GetQtEncryptCfg(tTpQtEncryptCfg);

	in_addr tAddr;
	tAddr.S_un.S_addr = tTpQtEncryptCfg.m_dwQtIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtQtIP, strCaption, m_pWndTree);

	if ( strCaption != strOldInfo )
	{ 
		bChange = true;	
	}
	
	CheckData( m_strEdtQtIP, bChange );
	return true;
}

bool CCfgServerLogic::OnChangedQuantumEncryID(const IArgs& args)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	bool bChange = false;
	TTpQtEncryptCfg tTpQtEncryptCfg;
	LIBDATAMGRPTR->GetQtEncryptCfg( tTpQtEncryptCfg );

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtQtID, strCaption, m_pWndTree);
	u32 dwCaption = atoi(strCaption.c_str());

	if ( dwCaption != tTpQtEncryptCfg.m_dwQtID )
	{ 
		bChange = true;	
	}
	
	CheckData( m_strEdtQtID, bChange );
	return true;
}

bool CCfgServerLogic::OnChangedDataTimeSyncIP(const IArgs& args)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	bool bChange = false;
	TTPNtpSer tTpNtpSer;
	LIBDATAMGRPTR->GetNtpSerIP( tTpNtpSer );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTpNtpSer.dwSerIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTimeSyncIP, strCaption, m_pWndTree);
	
	if ( strCaption != strOldInfo )
	{ 
		bChange = true;	
	}
	
	CheckData( m_strEdtTimeSyncIP, bChange );

	return true;
}

void CCfgServerLogic::SetDataConfSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	
    TTPDataConfInfo tWBSerIp;
	LIBDATAMGRPTR->GetWBSerIp( tWBSerIp );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tWBSerIp.dwSerIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtDCIP, m_pWndTree ); 
}

void CCfgServerLogic::SetQtEncryptData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	TTpQtEncryptCfg tTpQtEncryptCfg;
	LIBDATAMGRPTR->GetQtEncryptCfg(tTpQtEncryptCfg);
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tTpQtEncryptCfg.m_dwQtIP);
	
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtQtIP, m_pWndTree );
	
	s8 chEdtQtID[10] = {0};
	if( tTpQtEncryptCfg.m_dwQtID == 0 )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtQtID, "", m_pWndTree );
	}
	else
	{
		sprintf( chEdtQtID, "%u", tTpQtEncryptCfg.m_dwQtID );
		UIFACTORYMGR_PTR->SetCaption( m_strEdtQtID, chEdtQtID, m_pWndTree );
	}

	if ( tTpQtEncryptCfg.m_bOpen == FALSE )
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnQTSwitch, 0, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree, m_strEdtQtIP); 
        UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree, m_strEdtQtID); 
	}
	else
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnQTSwitch, 1, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree, m_strEdtQtIP); 
        UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree, m_strEdtQtID); 
	}
}

void CCfgServerLogic::SetMatrixSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	TTPMatrixServerInfo tTPMatrixServerInfo;
	LIBDATAMGRPTR->GetMatrixSerInfo(tTPMatrixServerInfo);

	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tTPMatrixServerInfo.m_dwSerIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtMatrixIP, m_pWndTree );
}

void CCfgServerLogic::SetNtpSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	
	TTPNtpSer tTpNtpSer;
	LIBDATAMGRPTR->GetNtpSerIP( tTpNtpSer );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl( tTpNtpSer.dwSerIP );
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtTimeSyncIP, m_pWndTree );
}

LRESULT CCfgServerLogic::OnWBServerInd( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		WARNMESSAGE("设置数据会议服务器地址失败");
		FocusWindow(m_strEdtDCIP);
	} 
	return S_OK;
}

LRESULT CCfgServerLogic::OnSetMatrixServerInfoNty(WPARAM wParam, LPARAM lParam)
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}

	SetMatrixSerData();

	return S_OK;
}

LRESULT CCfgServerLogic::OnSetMatrixServerInfoInd(WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		WARNMESSAGE("设置矩阵服务器地址失败");
		FocusWindow(m_strEdtMatrixIP);
	} 

	return S_OK;
}

LRESULT CCfgServerLogic::OnSetQtEncryptInfoNty(WPARAM wParam, LPARAM lParam)
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}

	SetQtEncryptData();

	return S_OK;
}

LRESULT CCfgServerLogic::OnSetQtEncryptInfoInd(WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		WARNMESSAGE("设置量子加密服务器地址失败");
		FocusWindow(m_strEdtQtIP);
	} 
	
	SetQtEncryptData();

	//bug cnc修改量子信息，tptools也提示重启问题
	if ( bSuccess && m_bIsTptoolsSaveQtInfo)
	{
		m_bIsTptoolsSaveQtInfo = FALSE;

		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, " 量子服务配置需要重启设备，是否重启？" );
		if( MSGBOX_OK == nMsgBoxRet )
		{
			u16 nRet = COMIFMGRPTR->RebootCns();
			if ( nRet != NO_ERROR )
			{
				WARNMESSAGE( "重启cns请求发送失败!" );
			}
		}
	}

	return S_OK;
}

LRESULT CCfgServerLogic::OnSetNtpServerInfoNty(WPARAM wParam, LPARAM lParam)
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	
	SetNtpSerData();

	return S_OK;
}

LRESULT CCfgServerLogic::OnSetNtpServerInfoInd(WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		WARNMESSAGE("设置时间同步服务器地址失败");
		FocusWindow(m_strEdtTimeSyncIP);
	} 

	return S_OK;
}

bool CCfgServerLogic::SaveDataConfSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtDCIP, m_pWndTree ); 

	TTPDataConfInfo tWBSerIp;
	tWBSerIp.dwSerIP = htonl(valIp.dwIP);
	
	TTPDataConfInfo tOldWBSerInfo;
	LIBDATAMGRPTR->GetWBSerIp(tOldWBSerInfo);
		
	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtDCIP, strCaption, m_pWndTree );
	
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "数据会议服务器地址非法" );
		FocusWindow(m_strEdtDCIP);
		return false;
	}
	
	if ( tWBSerIp.dwSerIP != tOldWBSerInfo.dwSerIP )
	{
		u16 wRet = COMIFMGRPTR->SetDataConfSerCmd( tWBSerIp );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存数据会议服务器配置请求发送失败" );
			return false;
		}
	}
	return true;
}

bool CCfgServerLogic::SaveMatrixSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtMatrixIP, m_pWndTree ); 
	
	TTPMatrixServerInfo tTPMatrixServerInfo;
	tTPMatrixServerInfo.m_dwSerIP = htonl(valIp.dwIP);
	
	TTPMatrixServerInfo tTPOldMatrixServerInfo;
	LIBDATAMGRPTR->GetMatrixSerInfo(tTPOldMatrixServerInfo);
	
	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtMatrixIP, strCaption, m_pWndTree );
	
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "矩阵服务器地址非法" );
		FocusWindow(m_strEdtMatrixIP);
		return false;
	}
	
	if ( tTPMatrixServerInfo.m_dwSerIP != tTPOldMatrixServerInfo.m_dwSerIP )
	{
		u16 wRet = COMIFMGRPTR->SetMatrixSerCmd( tTPMatrixServerInfo );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存矩阵服务器配置请求发送失败" );
			return false;
		}
	}
	return true;
}

bool CCfgServerLogic::SaveQtEncryptSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtQtIP, m_pWndTree );

	TTpQtEncryptCfg tTpQtEncryptCfg;
	tTpQtEncryptCfg.m_dwQtIP = htonl(valIp.dwIP);

	TTpQtEncryptCfg tOldQtSerInfo;
	LIBDATAMGRPTR->GetQtEncryptCfg(tOldQtSerInfo);

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtQtIP, strCaption, m_pWndTree );

	String strCaption1;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtQtID, strCaption1, m_pWndTree );

	bool bUseQT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnQTSwitch, bUseQT, m_pWndTree );

	tTpQtEncryptCfg.m_bOpen = bUseQT;

	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "量子加密服务器地址非法" );
		FocusWindow(m_strEdtQtIP);
		return false;
	}

	if( strCaption1.empty() )
	{
		tTpQtEncryptCfg.m_dwQtID = 0;
	}
	else
	{
		u64 dwQtID = _atoi64(strCaption1.c_str());
		if( ( dwQtID < 1 ) || ( dwQtID > 4294967295 ) )
		{
			MSG_BOX_OK("量子加密的ID范围必须在1-4294967295之间");
			FocusWindow(m_strEdtQtID);
			return false;
		}
		else
		{
			tTpQtEncryptCfg.m_dwQtID = atoi( strCaption1.c_str() );
		}
	}

	if( (tTpQtEncryptCfg.m_bOpen != tOldQtSerInfo.m_bOpen) || (tTpQtEncryptCfg.m_dwQtIP != tOldQtSerInfo.m_dwQtIP) || ( tTpQtEncryptCfg.m_dwQtID != tOldQtSerInfo.m_dwQtID ) )
	{
		u16 wRet = COMIFMGRPTR->SetQtEncryptSerCmd(tTpQtEncryptCfg);
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存量子加密服务器配置请求发送失败" );
			return false;
		}
		else
		{
			if ((tTpQtEncryptCfg.m_dwQtIP != tOldQtSerInfo.m_dwQtIP) || ( tTpQtEncryptCfg.m_dwQtID != tOldQtSerInfo.m_dwQtID ))
			{
				m_bIsTptoolsSaveQtInfo = TRUE;
			}
		}
	}

	return true;
}

bool CCfgServerLogic::SaveNtpSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtTimeSyncIP, m_pWndTree ); 
	
	TTPNtpSer tTpNtpSer;
	tTpNtpSer.dwSerIP = htonl(valIp.dwIP);
	
	TTPNtpSer tTPOldNtpSer;
	LIBDATAMGRPTR->GetNtpSerIP(tTPOldNtpSer);
	
	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTimeSyncIP, strCaption, m_pWndTree );
	
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "时间同步服务器地址非法" );
		FocusWindow(m_strEdtTimeSyncIP);
		return false;
	}
	
	if ( tTpNtpSer.dwSerIP != tTPOldNtpSer.dwSerIP )
	{
		u16 wRet = COMIFMGRPTR->SetNtpSerCmd( tTpNtpSer );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存时间同步服务器配置请求发送失败" );
			return false;
		}
	}

	return true;
}

LRESULT CCfgServerLogic::OnVerInfoNty( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree == NULL )
    {
        return S_FALSE;
    }
    
    EmCnModel emCnModel;
    LIBDATAMGRPTR->GetEmCnModelInfo( &emCnModel );
    
    if (emCnModel == T300E_4K)
    {
        RestoreControlFor4K();
        UIFACTORYMGR_PTR->LoadScheme( "SchModelT300E_4K", m_pWndTree );
    }
    else
    {
        ResetControlFor4K();
        UIFACTORYMGR_PTR->LoadScheme( "SchModelNonT300E_4K", m_pWndTree );
    }
    
    return S_OK;
}

void CCfgServerLogic::RestoreControlFor4K()
{
    m_strEdtSIp = _T("CfgServer4KDlg/SIPCtrlAddress");
    
    m_strBtnGKSwitch = _T("CfgServer4KDlg/BtnGKSwitch");
    m_strEdtGKIP = _T("CfgServer4KDlg/IPCtrlGKIp");
}

void CCfgServerLogic::ResetControlFor4K()
{
    m_strEdtSIp = _T("CfgServerNorDlg/SIPCtrlAddress");
    
    m_strBtnGKSwitch = _T("CfgServerNorDlg/BtnGKSwitch");
    m_strEdtGKIP = _T("CfgServerNorDlg/IPCtrlGKIp");
}