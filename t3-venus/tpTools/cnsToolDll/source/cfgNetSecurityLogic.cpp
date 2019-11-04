// cfgNetSecurityLogic.cpp: implementation of the cfgNetSecurityLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgNetSecurityLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgNetSecurityLogic::CCfgNetSecurityLogic()
: m_strEdtFtpUsername("EdtFtpUsername")
, m_strEdtFtpPasswd("EdtFtpPasswd")
, m_strBtnFtpServerSwitch("BtnFtpServerSwitch")
, m_strBtnTelnetServerSwitch("BtnTelnetServerSwitch")
, m_strEdtTelnetUsername("EdtTelnetUsername")
, m_strEdtTelnetPasswd("EdtTelnetPasswd")
{

}

CCfgNetSecurityLogic::~CCfgNetSecurityLogic()
{

}

void CCfgNetSecurityLogic::RegMsg()
{
	CCfgNetSecurityLogic *pThis = GetSingletonPtr();

	//接收会议状态消息
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCfgNetSecurityLogic::OnConfStateNty, pThis, CCfgNetSecurityLogic );

	REG_MSG_HANDLER( UI_FTPINFO_Nty, CCfgNetSecurityLogic::OnSetFtpInfoNty, pThis, CCfgNetSecurityLogic );
	REG_MSG_HANDLER( UI_SETFTPINFO_Rsp, CCfgNetSecurityLogic::OnSetFtpInfoRsp, pThis, CCfgNetSecurityLogic );
	REG_MSG_HANDLER( UI_TELNETINFO_Nty, CCfgNetSecurityLogic::OnSetTelnetInfoNty, pThis, CCfgNetSecurityLogic );
	REG_MSG_HANDLER( UI_SETTELNETINFO_Rsp, CCfgNetSecurityLogic::OnSetTelnetInfoRsp, pThis, CCfgNetSecurityLogic );	
}

void CCfgNetSecurityLogic::UnRegMsg()
{
	
}

void CCfgNetSecurityLogic::RegCBFun()
{
	CCfgNetSecurityLogic *pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::InitWnd", CCfgNetSecurityLogic::InitWnd, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnBtnSave", CCfgNetSecurityLogic::OnBtnSave, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnBtnCancel", CCfgNetSecurityLogic::OnBtnCancel, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnBtnSwitchFtpServer", CCfgNetSecurityLogic::OnBtnSwitchFtpServer, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnFtpUsernameChange", CCfgNetSecurityLogic::OnFtpUsernameChange, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnEdtFtpPasswdSetFocus", CCfgNetSecurityLogic::OnEdtFtpPasswdSetFocus, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnFtpPasswdChange", CCfgNetSecurityLogic::OnFtpPasswdChange, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnEdtFtpPasswdKillFocus", CCfgNetSecurityLogic::OnEdtFtpPasswdKillFocus, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnBtnSwitchTelnetServer", CCfgNetSecurityLogic::OnBtnSwitchTelnetServer, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnTelnetUsernameChange", CCfgNetSecurityLogic::OnTelnetUsernameChange, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnTelnetPasswdChange", CCfgNetSecurityLogic::OnTelnetPasswdChange, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnEdtTelnetPasswdKillFocus", CCfgNetSecurityLogic::OnEdtTelnetPasswdKillFocus, pThis, CCfgNetSecurityLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetSecurityLogic::OnEdtTelnetPasswdSetFocus", CCfgNetSecurityLogic::OnEdtTelnetPasswdSetFocus, pThis, CCfgNetSecurityLogic );
}

void CCfgNetSecurityLogic::UnRegFunc()
{
	
}

bool CCfgNetSecurityLogic::InitWnd(const IArgs & arg)
{
	CLogicBase::InitWnd( arg );

	memset( &m_tTPFtpInfo, 0, sizeof(TTPFtpInfo) );
	memset( &m_tTPTelnetInfo, 0, sizeof(TTPTelnetInfo) );

	m_vctWndName.clear();
	UpBtnState();
	
	return true;
}

void CCfgNetSecurityLogic::Clear()
{
	memset( &m_tTPFtpInfo, 0, sizeof(TTPFtpInfo) );
	memset( &m_tTPTelnetInfo, 0, sizeof(TTPTelnetInfo) );

	m_vctWndName.clear();
	UpBtnState();
}

bool CCfgNetSecurityLogic::IsCfgNetChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

LRESULT CCfgNetSecurityLogic::OnConfStateNty(WPARAM wparam, LPARAM lparam)
{

	if ( m_vctWndName.size() > 0  && m_pWndTree != NULL )
	{
		return S_FALSE;
	}

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree );
	}

	return S_OK;
}

HRESULT CCfgNetSecurityLogic::OnSetFtpInfoNty(WPARAM wparam, LPARAM lparam)
{
	TTPFtpInfo tTPFtpInfo = *(TTPFtpInfo*)(wparam);
	m_tTPFtpInfo = tTPFtpInfo;

	String strUsrname = tTPFtpInfo.achUserName;
	String StrPasswd = tTPFtpInfo.achPassword;

	//BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	//if( !bInConf )
	{
		if( tTPFtpInfo.bOpen )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmFtpSerOpen", m_pWndTree );
			UIFACTORYMGR_PTR->SetSwitchState( m_strBtnFtpServerSwitch, 1, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmFtpSerClose", m_pWndTree );
			UIFACTORYMGR_PTR->SetSwitchState( m_strBtnFtpServerSwitch, 0, m_pWndTree );
		}
	}

	UIFACTORYMGR_PTR->SetCaption( m_strEdtFtpUsername, strUsrname, m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtFtpPasswd, StrPasswd, m_pWndTree );

	UpdateFtpPasswdTip(StrPasswd);

	return S_OK;
}

HRESULT CCfgNetSecurityLogic::OnSetFtpInfoRsp(WPARAM wparam, LPARAM lparam)
{
	TTPFtpInfo tTPFtpInfo = *(TTPFtpInfo*)(wparam);
	m_tTPFtpInfo = tTPFtpInfo;
	
	BOOL bSuccess = *(BOOL*)(lparam);
	if( !bSuccess ) 
	{
		WARNMESSAGE("设置FTP用户名和密码失败");
		return S_FALSE;
	}

   	SetFtpInfo();
	
	return S_OK;
}

HRESULT CCfgNetSecurityLogic::OnSetTelnetInfoNty(WPARAM wparam, LPARAM lparam)
{
	TTPTelnetInfo tTPTelnetInfo = *(TTPTelnetInfo*)(wparam);
	m_tTPTelnetInfo = tTPTelnetInfo;
	
	String strUsrname = tTPTelnetInfo.achUserName;
	String StrPasswd = tTPTelnetInfo.achPassword;

//	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
//	if( !bInConf )
	{
		if( m_tTPTelnetInfo.bOpen )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmTelSerOpen", m_pWndTree );
			UIFACTORYMGR_PTR->SetSwitchState( m_strBtnTelnetServerSwitch, 1, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmTelSerClose", m_pWndTree );
			UIFACTORYMGR_PTR->SetSwitchState( m_strBtnTelnetServerSwitch, 0, m_pWndTree );
		}
	}

	UIFACTORYMGR_PTR->SetCaption( m_strEdtTelnetUsername, strUsrname, m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtTelnetPasswd, StrPasswd, m_pWndTree );
	
	UpdateTelnetPasswdTip( StrPasswd );

	return S_OK;
}

HRESULT CCfgNetSecurityLogic::OnSetTelnetInfoRsp(WPARAM wparam, LPARAM lparam)
{
	TTPTelnetInfo tTPTelnetInfo = *(TTPTelnetInfo*)(wparam);
	m_tTPTelnetInfo = tTPTelnetInfo;
	
	BOOL bSuccess = *(BOOL*)(lparam);
	if( !bSuccess ) 
	{
		WARNMESSAGE("设置Telnet用户名和密码失败");
		return S_FALSE;
	}

	SetTelnetInfo();

	return S_OK;
}

bool CCfgNetSecurityLogic::SaveMsgBox()
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

void CCfgNetSecurityLogic::SetFtpInfo()
{
	if( m_tTPFtpInfo.bOpen )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmFtpSerOpen", m_pWndTree );
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnFtpServerSwitch, 1, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmFtpSerClose", m_pWndTree );
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnFtpServerSwitch, 0, m_pWndTree );
	}

	UIFACTORYMGR_PTR->SetCaption( m_strEdtFtpUsername, m_tTPFtpInfo.achUserName, m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtFtpPasswd, m_tTPFtpInfo.achPassword, m_pWndTree );

	UpdateFtpPasswdTip( m_tTPFtpInfo.achPassword );
}

void CCfgNetSecurityLogic::SetTelnetInfo()
{
	if( m_tTPTelnetInfo.bOpen )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmTelSerOpen", m_pWndTree );
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnTelnetServerSwitch, 1, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmTelSerClose", m_pWndTree );
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnTelnetServerSwitch, 0, m_pWndTree );
	}
	
	UIFACTORYMGR_PTR->SetCaption( m_strEdtTelnetUsername, m_tTPTelnetInfo.achUserName, m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtTelnetPasswd, m_tTPTelnetInfo.achPassword, m_pWndTree );

	UpdateTelnetPasswdTip( m_tTPTelnetInfo.achPassword );
}

bool CCfgNetSecurityLogic::IsValidPWChar(CString szPWStr)
{
	if (szPWStr.IsEmpty())
	{
		return false;
	}

	CString  szTemp = szPWStr.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._"));
	if (szTemp != szPWStr)
	{
		return false;
	}

	return true;
}

bool CCfgNetSecurityLogic::IsValidPWCharStyle(CString szPWStr)
{
	if (szPWStr.IsEmpty())
	{
		return false;
	}

	//纯数字
	CString szTemp = szPWStr.SpanIncluding(_T("0123456789"));
	if (szTemp == szPWStr)
	{
		return false;
	}
	//纯英文字母
	szTemp = szPWStr.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	if (szTemp == szPWStr)
	{
		return false;
	}
	//纯特殊字符'.','_'
	szTemp = szPWStr.SpanIncluding(_T("._"));
	if (szTemp == szPWStr)
	{
		return false;
	}

	//其他特殊字符
	szTemp = szPWStr.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._"));
	if (szTemp != szPWStr)
	{
		return false;
	}
	
	return true;
}

void CCfgNetSecurityLogic::UpdateFtpPasswdTip(String strPasswd)
{
	bool bCheckResult = UIDATAMGR_PTR->IsValidPWStr(strPasswd.c_str());
	if( !bCheckResult )
	{
		UIFACTORYMGR_PTR->LoadScheme("NoFocus", m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme("ScheNoFocusImg2", m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme("NofocusError", m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("NoFocus", m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme("NofocusNor", m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme("NofocusOK", m_pWndTree);
		if( !strPasswd.empty() )
		{
			if( (strPasswd.find('.') == std::string::npos) && (strPasswd.find('_') == std::string::npos) )
			{		
				UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusImg1", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusTipLow", m_pWndTree );
			}
			else
			{
				if( (strPasswd.find('.') != std::string::npos) && (strPasswd.find('_') != std::string::npos) )
				{
					UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusImg1", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusTipHigh", m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusImg1", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusTipMid", m_pWndTree );
				}
			}
		}
	}
}

void CCfgNetSecurityLogic::UpdateTelnetPasswdTip(String strPasswd)
{
	bool bCheckResult = UIDATAMGR_PTR->IsValidPWStr(strPasswd.c_str());
	if( !bCheckResult )
	{
		UIFACTORYMGR_PTR->LoadScheme("NoTelFocus", m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme("ScheTelNoFocusImg2", m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme("NoTelfocusError", m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("NoTelFocus", m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme( "NoTelfocusNor", m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme("NoTelfocusOK", m_pWndTree);
		if( !strPasswd.empty() )
		{
			if( (strPasswd.find('.') == std::string::npos) && (strPasswd.find('_') == std::string::npos) )
			{		
				UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusImg1", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusTipLow", m_pWndTree );
			}
			else
			{
				if( (strPasswd.find('.') != std::string::npos) && (strPasswd.find('_') != std::string::npos) )
				{
					UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusImg1", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusTipHigh", m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusImg1", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusTipMid", m_pWndTree );
				}
			}
		}
	}
}

bool CCfgNetSecurityLogic::OnBtnSave(const IArgs& args)
{
// 	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
// 	if ( bInConf )
// 	{		
// 		MSG_BOX_OK( _T("有会议进行中，不能修改") );
// 		OnBtnCancel(args);
// 		return false;	
// 	}

	bool bOpenState;
	String strUsrCaption;
	String strPwdCaption;
	UIFACTORYMGR_PTR->GetSwitchState( m_strBtnFtpServerSwitch, bOpenState, m_pWndTree );
	UIFACTORYMGR_PTR->GetCaption( m_strEdtFtpUsername, strUsrCaption, m_pWndTree);	
	UIFACTORYMGR_PTR->GetCaption( m_strEdtFtpPasswd, strPwdCaption, m_pWndTree);

	bool bCheckResult = UIDATAMGR_PTR->IsValidPWStr( strPwdCaption.c_str() );
	if( !bCheckResult )
	{
		MSG_BOX_OK("Ftp密码设置不符合要求！");
		UIFACTORYMGR_PTR->SetFocus( m_strEdtFtpPasswd, m_pWndTree );
		return false;
	}

	if( ( bOpenState != (bool)m_tTPFtpInfo.bOpen ) || ( strUsrCaption != m_tTPFtpInfo.achUserName ) || ( strPwdCaption != m_tTPFtpInfo.achPassword ))
	{
		TTPFtpInfo tTPFtpInfo;
		tTPFtpInfo.bOpen = bOpenState;
		memcpy( tTPFtpInfo.achUserName, strUsrCaption.c_str(), strUsrCaption.length()+1 );
		memcpy( tTPFtpInfo.achPassword, strPwdCaption.c_str(), strPwdCaption.length()+1 );
		u16 wRet = COMIFMGRPTR->SetFtpInfoRsq(tTPFtpInfo);

		if( wRet != NO_ERROR)
		{
			WARNMESSAGE("FTP服务请求设置失败");
		}
	}

	UIFACTORYMGR_PTR->GetSwitchState( m_strBtnTelnetServerSwitch, bOpenState, m_pWndTree );
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTelnetUsername, strUsrCaption, m_pWndTree);	
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTelnetPasswd, strPwdCaption, m_pWndTree);

	bCheckResult = UIDATAMGR_PTR->IsValidPWStr( strPwdCaption.c_str() );
	if( !bCheckResult )
	{
		MSG_BOX_OK("Telnet密码设置不符合要求！");
		UIFACTORYMGR_PTR->SetFocus( m_strEdtTelnetPasswd, m_pWndTree );
		return false;
	}

	if( ( bOpenState != (bool)m_tTPTelnetInfo.bOpen ) || ( strUsrCaption != m_tTPTelnetInfo.achUserName ) || ( strPwdCaption != m_tTPTelnetInfo.achPassword ))
	{
		TTPTelnetInfo tTPTelnetInfo;
		tTPTelnetInfo.bOpen = bOpenState;
		memcpy( tTPTelnetInfo.achUserName, strUsrCaption.c_str(), strUsrCaption.length()+1 );
		memcpy( tTPTelnetInfo.achPassword, strPwdCaption.c_str(), strPwdCaption.length()+1 );
		u16 wRet1 = COMIFMGRPTR->SetTelInfoRsp(tTPTelnetInfo);

		if( wRet1 != NO_ERROR )
		{
			WARNMESSAGE("TELNET服务请求设置失败");
		}
	}

	m_vctWndName.clear();
	UpBtnState();
	
	return true;
}

bool CCfgNetSecurityLogic::OnBtnCancel(const IArgs& args)
{
	SetFtpInfo();
	SetTelnetInfo();
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

bool CCfgNetSecurityLogic::OnBtnSwitchFtpServer(const IArgs& args)
{
	bool bOpenState;
	UIFACTORYMGR_PTR->GetSwitchState( m_strBtnFtpServerSwitch, bOpenState, m_pWndTree );
	if (!bOpenState)
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtFtpUsername, m_tTPFtpInfo.achUserName, m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strEdtFtpPasswd, m_tTPFtpInfo.achPassword, m_pWndTree );
	}

	bool bChange = false;
	if( !bOpenState && ( bOpenState != (bool)m_tTPFtpInfo.bOpen) )
	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "关闭FTP服务将导致下列功能不能使用：1.软件升级；2.FTP上传、下载；3.日志导出；4.抓包功能；5.快照功能；6.台标和横幅功能；您确定要关闭吗？" );
		if ( MSGBOX_OK == nMsgBoxRet)
		{	
			UIFACTORYMGR_PTR->LoadScheme( "SchmFtpSerClose", m_pWndTree );
			if( bOpenState != (bool)m_tTPFtpInfo.bOpen )
			{
				bChange = true;
			}
			
			CheckData( m_strBtnFtpServerSwitch, bChange );
			return true;
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmFtpSerOpen", m_pWndTree );
			UIFACTORYMGR_PTR->SetSwitchState( m_strBtnFtpServerSwitch, !bOpenState, m_pWndTree );
			return false;
		}
	}
	else
	{
		if( bOpenState )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmFtpSerOpen", m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmFtpSerClose", m_pWndTree );
		}

		if( bOpenState != (bool)m_tTPFtpInfo.bOpen )
		{
			bChange = true;
		}
		
		CheckData( m_strBtnFtpServerSwitch, bChange );
	}

    return true;
}

bool CCfgNetSecurityLogic::OnFtpUsernameChange(const IArgs& args)
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtFtpUsername, strCaption, m_pWndTree);

	bool bChange = false;
	if( strCaption != m_tTPFtpInfo.achUserName )
	{
		bChange = true;
	}

	CheckData(m_strEdtFtpUsername, bChange);

	return true;
}

bool CCfgNetSecurityLogic::OnEdtFtpPasswdSetFocus(const IArgs& args)
{
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtFtpPasswd, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtFtpPasswd, strCaption, m_pWndTree);

	if( strCaption.empty() )
	{
		UIFACTORYMGR_PTR->LoadScheme( "ScheFocus", m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "PswEmpty", m_pWndTree );
	}

	return true;
}

bool CCfgNetSecurityLogic::OnFtpPasswdChange(const IArgs& args)
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtFtpPasswd, strCaption, m_pWndTree);

	CTransparentEdit *pEdtWnd = (CTransparentEdit*)UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtFtpPasswd, m_pWndTree );
	if( pEdtWnd -> IsFocus() )
	{
		UIFACTORYMGR_PTR->LoadScheme( "ScheFocus", m_pWndTree );
		if( !strCaption.empty() )
		{
			UIFACTORYMGR_PTR->LoadScheme("OnFtpPswFocus", m_pWndTree );
			if( strCaption.length() < 8 || strCaption.length() > 16 )
			{
				UIFACTORYMGR_PTR->LoadScheme( "LengthCheckNO", m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "LengthCheckOK", m_pWndTree );
			}

			if( IsValidPWChar(strCaption.c_str()) )
			{
				UIFACTORYMGR_PTR->LoadScheme( "CharactorCheckOK", m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "CharactorCheckNO", m_pWndTree );
			}

			if( IsValidPWCharStyle( strCaption.c_str() ) )
			{
				UIFACTORYMGR_PTR->LoadScheme( "CharStyleCheckOK", m_pWndTree );
				if( (strCaption.find('.') == std::string::npos) && (strCaption.find('_') == std::string::npos) )
				{
					UIFACTORYMGR_PTR->LoadScheme( "TipSec1Img2", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "PswLow", m_pWndTree );
				}
				else
				{
					if( (strCaption.find('.') != std::string::npos) && (strCaption.find('_') != std::string::npos) )
					{
						UIFACTORYMGR_PTR->LoadScheme( "PswHigh", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipSec2Img2", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipSec3Img2", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipSec1Img2", m_pWndTree );
					}
					else
					{
						UIFACTORYMGR_PTR->LoadScheme( "PswMid", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipSec2Img2", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipSec1Img2", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipSec3Img1", m_pWndTree );
					}
				}
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "CharStyleCheckNO", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "TipSec1Img2", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "TipSec2Img1", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "TipSec3Img1", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "PswLow", m_pWndTree );
			}
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "PswEmpty", m_pWndTree );
		}
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("NoFocus", m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme("NofocusNor", m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme("NofocusOK", m_pWndTree);
		if( !strCaption.empty() )
		{
			if( (strCaption.find('.') == std::string::npos) && (strCaption.find('_') == std::string::npos) )
			{		
				UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusImg1", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusTipLow", m_pWndTree );
			}
			else
			{
				if( (strCaption.find('.') != std::string::npos) && (strCaption.find('_') != std::string::npos) )
				{
					UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusImg1", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusTipHigh", m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusImg1", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "ScheNoFocusTipMid", m_pWndTree );
				}
			}
		}
	}

	bool bChange = false;
	if( strCaption != m_tTPFtpInfo.achPassword )
	{
		bChange = true;
	}

	CheckData( m_strEdtFtpPasswd, bChange );

	return true;
}

bool CCfgNetSecurityLogic::OnEdtFtpPasswdKillFocus(const IArgs& args)
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtFtpPasswd, strCaption, m_pWndTree);

	UpdateFtpPasswdTip(strCaption);

	return true;
}

bool CCfgNetSecurityLogic::OnBtnSwitchTelnetServer(const IArgs& args)
{
	bool bOpenState;
	UIFACTORYMGR_PTR->GetSwitchState( m_strBtnTelnetServerSwitch, bOpenState, m_pWndTree );

	if (!bOpenState)
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtTelnetUsername, m_tTPTelnetInfo.achUserName, m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strEdtTelnetPasswd, m_tTPTelnetInfo.achPassword, m_pWndTree );
	}
	
	bool bChange = false;
	if( !bOpenState && ( bOpenState != (bool)m_tTPTelnetInfo.bOpen) )
	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "关闭Telnet服务将导致下列功能不能使用：抓包功能。您确定要关闭吗？" );
		if ( MSGBOX_OK == nMsgBoxRet)
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmTelSerClose", m_pWndTree );
			if( bOpenState != (bool)m_tTPTelnetInfo.bOpen )
			{
				bChange = true;
			}
			
			CheckData( m_strBtnTelnetServerSwitch, bChange );
			return true;
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmTelSerOpen", m_pWndTree );
			UIFACTORYMGR_PTR->SetSwitchState( m_strBtnTelnetServerSwitch, !bOpenState, m_pWndTree );
			return false;
		}
	}
	else
	{
		if( bOpenState )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmTelSerOpen", m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmTelSerClose", m_pWndTree );
		}

		if( bOpenState != (bool)m_tTPTelnetInfo.bOpen )
		{
			bChange = true;
		}
		
		CheckData( m_strBtnTelnetServerSwitch, bChange );
	}

	return true;
}

bool CCfgNetSecurityLogic::OnTelnetUsernameChange(const IArgs& args)
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTelnetUsername, strCaption, m_pWndTree);
	
	bool bChange = false;
	if( strCaption != m_tTPTelnetInfo.achUserName )
	{
		bChange = true;
	}
	
	CheckData( m_strEdtTelnetUsername, bChange );

	return true;
}

bool CCfgNetSecurityLogic::OnTelnetPasswdChange(const IArgs& args)
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTelnetPasswd, strCaption, m_pWndTree);
	
	CTransparentEdit *pEdtWnd = (CTransparentEdit*)UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtTelnetPasswd, m_pWndTree );
	if( pEdtWnd -> IsFocus() )
	{
		UIFACTORYMGR_PTR->LoadScheme( "ScheTelFocus", m_pWndTree );
		if( !strCaption.empty() )
		{
			UIFACTORYMGR_PTR->LoadScheme( "OnTelPswFocus", m_pWndTree );
			if( strCaption.length() < 8 || strCaption.length() > 16 )
			{
				UIFACTORYMGR_PTR->LoadScheme( "LengthTelCheckNO", m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "LengthTelCheckOK", m_pWndTree );
			}
			
			if( IsValidPWChar(strCaption.c_str()) )
			{
				UIFACTORYMGR_PTR->LoadScheme( "CharactorTelCheckOK", m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "CharactorTelCheckNO", m_pWndTree );
			}
			
			if( IsValidPWCharStyle( strCaption.c_str() ) )
			{
				UIFACTORYMGR_PTR->LoadScheme( "CharStyleTelCheckOK", m_pWndTree );
				if( (strCaption.find('.') == std::string::npos) && (strCaption.find('_') == std::string::npos) )
				{
					UIFACTORYMGR_PTR->LoadScheme( "TipTelSec1Img2", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "PswTelLow", m_pWndTree );
				}
				else
				{
					if( (strCaption.find('.') != std::string::npos) && (strCaption.find('_') != std::string::npos) )
					{
						UIFACTORYMGR_PTR->LoadScheme( "PswTelHigh", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipTelSec2Img2", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipTelSec3Img2", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipTelSec1Img2", m_pWndTree );
					}
					else
					{
						UIFACTORYMGR_PTR->LoadScheme( "PswTelMid", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipTelSec2Img2", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipTelSec1Img2", m_pWndTree );
						UIFACTORYMGR_PTR->LoadScheme( "TipTelSec3Img1", m_pWndTree );
					}
				}
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "CharStyleTelCheckNO", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "TipTelSec1Img2", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "TipTelSec2Img1", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "TipTelSec3Img1", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "PswTelLow", m_pWndTree );
			}
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "PswTelEmpty", m_pWndTree );
		}
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("NoTelFocus", m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme("NoTelfocusNor", m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme("NoTelfocusOK", m_pWndTree);
		if( !strCaption.empty() )
		{
			if( (strCaption.find('.') == std::string::npos) && (strCaption.find('_') == std::string::npos) )
			{		
				UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusImg1", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusTipLow", m_pWndTree );
			}
			else
			{
				if( (strCaption.find('.') != std::string::npos) && (strCaption.find('_') != std::string::npos) )
				{
					UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusImg1", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusTipHigh", m_pWndTree );
				}
				else
				{
					UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusImg1", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "ScheTelNoFocusTipMid", m_pWndTree );
				}
			}
		}
	}

	bool bChange = false;

	if( strCaption != m_tTPTelnetInfo.achPassword )
	{
		bChange = true;
	}

	CheckData( m_strEdtTelnetPasswd, bChange );

	return true;
}

bool CCfgNetSecurityLogic::OnEdtTelnetPasswdSetFocus(const IArgs& args)
{
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtTelnetPasswd, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTelnetPasswd, strCaption, m_pWndTree);
	
	if( strCaption.empty() )
	{
		UIFACTORYMGR_PTR->LoadScheme( "ScheTelFocus", m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "PswTelEmpty", m_pWndTree );
	}

	return true;
}

bool CCfgNetSecurityLogic::OnEdtTelnetPasswdKillFocus(const IArgs& args)
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTelnetPasswd, strCaption, m_pWndTree);

	UpdateTelnetPasswdTip(strCaption);

	return true;
}