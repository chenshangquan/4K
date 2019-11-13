// netmngoptdlglogic.cpp: implementation of the CNetMngOptDlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "netmngoptdlglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetMngOptDlgLogic::CNetMngOptDlgLogic()
: m_strIPCtrlNMServerIP( "IPCtrlNMServerIP" )
, m_strEdtNMReadCommunity( "EdtNMReadCommunity" )
, m_strEdtNMWriteCommunity( "EdtNMWriteCommunity" )
, m_strEdtNMGetSetPort( "EdtNMGetSetPort" )
, m_strEdtNMTrapPort( "EdtNMTrapPort" )
, m_strEdtNMServerNO( "EdtNMServerNO" )
{
}

CNetMngOptDlgLogic::~CNetMngOptDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CNetMngOptDlgLogic::RegMsg()
{    
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_NETMNGSELDATA_Click, CNetMngOptDlgLogic::OnNetMngSelData, NETMNGOPTLOGICRPTR, CNetMngOptDlgLogic );
}

void CNetMngOptDlgLogic::UnRegMsg()
{
}

bool CNetMngOptDlgLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CNetMngOptDlgLogic::InitWnd", CNetMngOptDlgLogic::InitWnd, NETMNGOPTLOGICRPTR, CNetMngOptDlgLogic);
	REG_GOBAL_MEMBER_FUNC( "CNetMngOptDlgLogic::OnBtnOptNetMngOk", CNetMngOptDlgLogic::OnBtnOptNetMngOk, NETMNGOPTLOGICRPTR, CNetMngOptDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CNetMngOptDlgLogic::OnBtnOptNetMngCancel", CNetMngOptDlgLogic::OnBtnOptNetMngCancel, NETMNGOPTLOGICRPTR, CNetMngOptDlgLogic ); 

	return true;
}

bool CNetMngOptDlgLogic::UnRegFunc()
{
	return true;
}

bool CNetMngOptDlgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

    return true;
}

void CNetMngOptDlgLogic::Clear()
{
	memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrNetMngOptDlg );

	ClearAllCtrl();
}

bool CNetMngOptDlgLogic::OnBtnOptNetMngOk( const IArgs & arg )
{
	TTPNMServerCfg tTPNMServerCfg;
	bool bGet = GetAllCtrl(tTPNMServerCfg);
	if ( bGet == true )
	{
		if( em_NETMNGOPT_MODIFY == m_emNMType )	//修改
		{
			u16 nRet = COMMONMGRIFPTR->NetMngModifyReq( tTPNMServerCfg );
			if ( nRet != NO_ERROR )
			{
				MESSAGEWND( "修改网管请求发送失败" );
			}
		}
		else	//添加
		{
			u16 nRet = COMMONMGRIFPTR->NetMngAddReq( tTPNMServerCfg );
			if ( nRet != NO_ERROR )
			{
				MESSAGEWND( "添加网管请求发送失败" );
			}
		}

		memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
		s32 nResult = 0;
		UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrNetMngOptDlg );
	}
	

	return true;
}

bool CNetMngOptDlgLogic::OnBtnOptNetMngCancel( const IArgs & arg )
{
	memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
 	s32 nResult = 0;
 	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrNetMngOptDlg );

	return true;
}


HRESULT CNetMngOptDlgLogic::OnNetMngSelData( WPARAM wparam, LPARAM lparam)
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	m_emNMType = static_cast<EM_NETMNGOPT_TYPE>(lparam);

	if ( em_NETMNGOPT_MODIFY == m_emNMType )    //修改
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchNetMngModify", m_pWndTree );

		TTPNMServerCfg tTPNMServerCfgSel = *reinterpret_cast<TTPNMServerCfg*>(wparam);
		memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
		m_tTPNMServerCfgSel = tTPNMServerCfgSel;
		SetAllCtrl(tTPNMServerCfgSel);
	}
	else	//添加
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchNetMngAdd", m_pWndTree );

		UIFACTORYMGR_PTR->LoadScheme( "SchNetMngAddDefValue", m_pWndTree );

		u16 wNMServerNo = static_cast<int>(wparam);
		string strCaption;
		char arrNMServerNO[5] = {0};
		_itot( wNMServerNo, arrNMServerNO, 10 );
		strCaption = arrNMServerNO;
		UIFACTORYMGR_PTR->SetCaption( m_strEdtNMServerNO, strCaption, m_pWndTree );
	}
	
	//UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlNMServerIP, m_pWndTree );
	
	return S_OK;
}

void CNetMngOptDlgLogic::ClearAllCtrl()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	UIFACTORYMGR_PTR->SetCaption( m_strIPCtrlNMServerIP, "", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtNMReadCommunity, "", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtNMWriteCommunity, "", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtNMGetSetPort, "", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtNMTrapPort, "", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtNMServerNO, "", m_pWndTree );
}

void CNetMngOptDlgLogic::SetAllCtrl( TTPNMServerCfg &tTPNMServerCfg )
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	String strCaption;
	
	strCaption = CUmstoolCommon::GetIpStr( (htonl)(tTPNMServerCfg.dwNMServerIP) );
	UIFACTORYMGR_PTR->SetCaption( m_strIPCtrlNMServerIP, strCaption, m_pWndTree );
	
	strCaption = tTPNMServerCfg.achNMReadCommunity;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtNMReadCommunity, strCaption, m_pWndTree );
	
	strCaption = tTPNMServerCfg.achNMWriteCommunity;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtNMWriteCommunity, strCaption, m_pWndTree );
	
	char arrGetSetPort[10] = {0};
	_itot( tTPNMServerCfg.wNMGetSetPort, arrGetSetPort, 10 );
	strCaption = arrGetSetPort;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtNMGetSetPort, strCaption, m_pWndTree );
	
	char arrTrapPort[5] = {0};
	_itot( tTPNMServerCfg.WNMTrapPort, arrTrapPort, 10 );
	strCaption = arrTrapPort;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtNMTrapPort, strCaption, m_pWndTree );

	char arrNMServerNO[5] = {0};
	_itot( tTPNMServerCfg.wNMServerNO, arrNMServerNO, 10 );
	strCaption = arrNMServerNO;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtNMServerNO, strCaption, m_pWndTree );
}

bool CNetMngOptDlgLogic::GetAllCtrl( TTPNMServerCfg &tTPNMServerCfg )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_WindowCaption valNMServerIP;
	UIFACTORYMGR_PTR->GetPropertyValue( valNMServerIP, m_strIPCtrlNMServerIP, m_pWndTree );
	if ( valNMServerIP.strCaption.empty() )
	{
		MSG_BOX_OK( "网管服务器地址不能为空" );
		UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlNMServerIP, m_pWndTree );
		return false;
	}

	Value_IpEditData valNMSververIP;
    UIFACTORYMGR_PTR->GetPropertyValue(valNMSververIP, m_strIPCtrlNMServerIP, m_pWndTree); 
	CString cstrNErrStr;
	if ( !CCallAddr::IsValidCallIP( valNMSververIP.dwIP, cstrNErrStr, 0 ) ) 
	{
		MSG_BOX_OK( "网管服务器地址无效" );
		UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlNMServerIP, m_pWndTree );
		return false;
	}

	u32_ip dwNMSververIp = htonl(inet_addr(valNMServerIP.strCaption.c_str()));

	if ( em_NETMNGOPT_ADD == m_emNMType || em_NETMNGOPT_MODIFY == m_emNMType )
	{
		vector<TTPNMServerCfg> vecTTPNMServerCfg;
		DATAMGRPTR->GetUmsNetMngData( vecTTPNMServerCfg );
		vector<TTPNMServerCfg>::iterator it = vecTTPNMServerCfg.begin();
		for ( ; it != vecTTPNMServerCfg.end(); it++ )
		{
			if ( it->dwNMServerIP == dwNMSververIp && m_tTPNMServerCfgSel.dwNMServerIP != dwNMSververIp )
			{
				MSG_BOX_OK( "网管服务器地址已存在，无法添加" );
				UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlNMServerIP, m_pWndTree );
				return false;
			}
		}
	}

	tTPNMServerCfg.dwNMServerIP = dwNMSververIp;
	

	Value_WindowCaption valNMReadCommunity;
	UIFACTORYMGR_PTR->GetPropertyValue( valNMReadCommunity, m_strEdtNMReadCommunity, m_pWndTree );
	if ( valNMReadCommunity.strCaption.length() > UMSTOOL_MAX_COMMUNITY_LENGTH )
	{
		CString str;
		str.Format( _T("读共同体超过最大长度：%d"), UMSTOOL_MAX_COMMUNITY_LENGTH );
		MSG_BOX_OK( (LPCTSTR)str );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtNMReadCommunity, m_pWndTree );
		return false;
	}
	strncpy( tTPNMServerCfg.achNMReadCommunity, valNMReadCommunity.strCaption.c_str(), UMSTOOL_MAX_COMMUNITY_LENGTH+1 );
	

	Value_WindowCaption valNMWriteCommunity;
	UIFACTORYMGR_PTR->GetPropertyValue( valNMWriteCommunity, m_strEdtNMWriteCommunity, m_pWndTree );
	if ( valNMWriteCommunity.strCaption.length() > UMSTOOL_MAX_COMMUNITY_LENGTH )
	{
		CString str;
		str.Format( _T("写共同体超过最大长度：%d"), UMSTOOL_MAX_COMMUNITY_LENGTH );
		MSG_BOX_OK( (LPCTSTR)str );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtNMWriteCommunity, m_pWndTree );
		return false;
	}
	strncpy( tTPNMServerCfg.achNMWriteCommunity, valNMWriteCommunity.strCaption.c_str(), UMSTOOL_MAX_COMMUNITY_LENGTH+1 );
	

	Value_WindowCaption valNMGetSetPort;
	UIFACTORYMGR_PTR->GetPropertyValue( valNMGetSetPort, m_strEdtNMGetSetPort, m_pWndTree );
	if ( valNMGetSetPort.strCaption.empty() )
	{
		MSG_BOX_OK( "读写端口不能为空" );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtNMGetSetPort, m_pWndTree );
		return false;
	}

	int nNMGetSetPort = _ttoi(valNMGetSetPort.strCaption.c_str());
	if ( nNMGetSetPort > 65535 || nNMGetSetPort < 1 )
	{
		MSG_BOX_OK( "范围越界，读写端口范围在1-65535之间" );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtNMGetSetPort, m_pWndTree );
		return false;
	}
	tTPNMServerCfg.wNMGetSetPort = nNMGetSetPort;
	

	Value_WindowCaption valNMTrapPort;
	UIFACTORYMGR_PTR->GetPropertyValue( valNMTrapPort, m_strEdtNMTrapPort, m_pWndTree );
	if ( valNMTrapPort.strCaption.empty() )
	{
		MSG_BOX_OK( "发警告端口不能为空" );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtNMTrapPort, m_pWndTree );
		return false;
	}
	int nNMTrapPort = _ttoi(valNMTrapPort.strCaption.c_str());
	if ( nNMTrapPort > 65535 || nNMTrapPort < 1 )
	{
		MSG_BOX_OK( "范围越界，发警告端口范围在1-65535之间" );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtNMTrapPort, m_pWndTree );
		return false;
	}
	tTPNMServerCfg.WNMTrapPort = _ttoi(valNMTrapPort.strCaption.c_str());
	
	
	Value_WindowCaption valNMServerNO;
	UIFACTORYMGR_PTR->GetPropertyValue( valNMServerNO, m_strEdtNMServerNO, m_pWndTree );
	tTPNMServerCfg.wNMServerNO = _ttoi(valNMServerNO.strCaption.c_str());
	
	return true;
}