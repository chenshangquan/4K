// centCfgDisplayDlg.cpp: implementation of the CCentCfgDisplayDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centCfgDisplayDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCentCfgDisplayDlg::CCentCfgDisplayDlg()
:m_strTerminalOut1("TvWallDlg/ComboboxTerminalOut1")
,m_strTVWALLOut1("TvWallDlg/ComboboxTVWALLOut1")
,m_strTerminalOut3("TvWallDlg/ComboboxTerminalOut3")
,m_strTVWALLOut3("TvWallDlg/ComboboxTVWALLOut3")
,m_strDisplay550A("CentCfgDisplayDlg/CheckBtnOfDisplay550A")
,m_strDisplayGM01A("CentCfgDisplayDlg/CheckBtnOfDisplayGM01A")
,m_strDisplayGH01A("CentCfgDisplayDlg/CheckBtnOfDisplayGH01A")
,m_strTvWallSwitch("TvWallDlg/BtnTVWALLSwitch")
,m_strModStatus("CentCfgDisplayDlg/StcModlStatus")
,m_strDisplayCfgSwitch("CentCfgDisplayDlg/BtnDisplayCfgSwitch")
{

}

CCentCfgDisplayDlg::~CCentCfgDisplayDlg()
{

}

void CCentCfgDisplayDlg::RegMsg()
{
	CCentCfgDisplayDlg *pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DISPLAY_IND, CCentCfgDisplayDlg::OnUpdateDisplayInfo, pThis, CCentCfgDisplayDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCentCfgDisplayDlg::OnConfStateNty, pThis, CCentCfgDisplayDlg );
	REG_MSG_HANDLER( UI_CNS_TVSTATE_NTY, CCentCfgDisplayDlg::OnUpdateDisplayModel, pThis, CCentCfgDisplayDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_TVMode_IND, CCentCfgDisplayDlg::OnTvModeInd, pThis, CCentCfgDisplayDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_DISPLAY_SHOW_Nty, CCentCfgDisplayDlg::OnDisplayShowNty, pThis, CCentCfgDisplayDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_DISPLAY_SHOW_Ind, CCentCfgDisplayDlg::OnDisplayShowInd, pThis, CCentCfgDisplayDlg );
}

void CCentCfgDisplayDlg::RegCBFun()
{
	CCentCfgDisplayDlg *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::InitWnd", CCentCfgDisplayDlg::InitWnd, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnBtnDisplayCfg", CCentCfgDisplayDlg::OnBtnDisplayCfg, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnBtnSwitchTVWALL", CCentCfgDisplayDlg::OnBtnSwitchTVWALL, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnBtnSave", CCentCfgDisplayDlg::OnBtnSave, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnBtnCancel", CCentCfgDisplayDlg::OnBtnCancel, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnTerminalOut1Change", CCentCfgDisplayDlg::OnTerminalOut1Change, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnTVWALLOut1Change", CCentCfgDisplayDlg::OnTVWALLOut1Change, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnTerminalOut3Change", CCentCfgDisplayDlg::OnTerminalOut3Change, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnTVWALLOut3Change", CCentCfgDisplayDlg::OnTVWALLOut3Change, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnSelDisplay550A", CCentCfgDisplayDlg::OnSelDisplay550A, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnSelDisplayGM01A", CCentCfgDisplayDlg::OnSelDisplayGM01A, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnSelDisplayGH01A", CCentCfgDisplayDlg::OnSelDisplayGH01A, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnSelDisplay70B17", CCentCfgDisplayDlg::OnSelDisplay70B17, pThis, CCentCfgDisplayDlg );
    REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnSelDisplay665A", CCentCfgDisplayDlg::OnSelDisplay665A, pThis, CCentCfgDisplayDlg );
    REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnSelDisplay70GM44A", CCentCfgDisplayDlg::OnSelDisplay70GM44A, pThis, CCentCfgDisplayDlg );
}

void CCentCfgDisplayDlg::UnRegFunc()
{
	
}

bool CCentCfgDisplayDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	UIFACTORYMGR_PTR->SetCheckState( "CentCfgDisplayDlg/CheckBtnOfDisplayMod1", 1, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetSwitchState( m_strDisplayCfgSwitch, 1, m_pWndTree );
	m_vecOut.push_back("HDMI 1");
	m_vecOut.push_back("HDMI 2");
	m_vecOut.push_back("HDMI 3");
	m_vecOut.push_back("HDMI 4");
// 	m_vecOut.push_back("YPbPr");
// 	m_vecOut.push_back("CVBS1");
// 	m_vecOut.push_back("CVBS2");
// 	m_vecOut.push_back("电脑");
	UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut1, m_vecOut, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut1, m_vecOut, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut3, m_vecOut, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut3, m_vecOut, m_pWndTree ); 
	m_emSelTvMode = emKeShi70GM44A;
	m_emTvMode = emKeShi70GM44A;
	m_vctWndName.clear();
	return true;
}

void CCentCfgDisplayDlg::Clear()
{
	m_vctWndName.clear();
	m_emSelTvMode = emKeShi70GM44A;
	m_emTvMode = emKeShi70GM44A;
	UpdateBtnState();
}

void CCentCfgDisplayDlg::UnRegMsg()
{
	
}

bool CCentCfgDisplayDlg::OnBtnSave( const IArgs& args )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("有会议进行中，不能配置") );
		OnBtnCancel(args);
		return false;	
	}

	if ( m_emSelTvMode != m_emTvMode )	//电视机型号更改
	{
		u16 wRet = COMIFMGRPTR->SetCentreTVModleCmd(m_emSelTvMode);
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "配置电视机型号请求发送失败" );
			
			return false;
		}

		if ( ( m_emSelTvMode == emSharp70LX565A ) )  //Sharp70LX565A没有电视墙服务
		{
			return true;
		}
	}

	bool bOpenState =  false;
	UIFACTORYMGR_PTR->GetSwitchState( m_strDisplayCfgSwitch, bOpenState, m_pWndTree );
	BOOL bDisplayShow = LIBDATAMGRPTR->GetDisplayShowState();
	if( (BOOL)bOpenState != bDisplayShow )
	{
		u16 wRet = COMIFMGRPTR->SetDisplayShowCmd( bOpenState );
		if( wRet != NO_ERROR )
		{
			WARNMESSAGE( "配置显示显示器配置界面请求发送失败" );
			return false;
		}
	}

	bool bOpen = false;
	UIFACTORYMGR_PTR->GetSwitchState( m_strTvWallSwitch, bOpen, m_pWndTree );
	BOOL bDisplay = LIBDATAMGRPTR->GetDisplayState();

	if ( m_emSelTvMode != emSharp70LX565A )
	{
		TTPDisplayType tDisplayType1, tDisplayType3;

		if ( ( (BOOL)bOpen != bDisplay )&&( bOpen == false ) )
		{
			tDisplayType1 = LIBDATAMGRPTR->GetDisplayType1();
			tDisplayType3 = LIBDATAMGRPTR->GetDisplayType3();
		}
		else if( ( ( (BOOL)bOpen != bDisplay )&&( bOpen == true ) )||
			( ( bOpen == true )&&(m_vctWndName.size() > 0 ) ) )
		{
			tDisplayType1.emTPT300Type = GetDisplayType(m_strTerminalOut1);
			tDisplayType1.emTPHduType = GetDisplayType(m_strTVWALLOut1);
			if ( tDisplayType1.emTPT300Type == tDisplayType1.emTPHduType )
			{
				MSG_BOX_OK("显示器1终端输出信号源、电视墙输出信号源必须不一致");
				return false;
			}
			
			tDisplayType3.emTPT300Type = GetDisplayType(m_strTerminalOut3);
			tDisplayType3.emTPHduType = GetDisplayType(m_strTVWALLOut3);
			if ( tDisplayType3.emTPT300Type == tDisplayType3.emTPHduType )
			{
				MSG_BOX_OK("显示器3终端输出信号源、电视墙输出信号源必须不一致");
				return false;
			}
		}
		else
		{
			return true;
		}

		u16 wRet = COMIFMGRPTR->SetDisplayCmd( bOpen, tDisplayType1, tDisplayType3 );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存中控电视墙配置请求发送失败" );
			return false;
		}
	}

	return true;
}

bool CCentCfgDisplayDlg::OnBtnCancel( const IArgs& args )
{
	UpdateTvState(m_emTvMode);
	m_emSelTvMode = m_emTvMode;
	SetDisplayInfo();
	m_vctWndName.clear();
	UpdateBtnState();

	BOOL bDisplayShow = LIBDATAMGRPTR->GetDisplayShowState();
	UIFACTORYMGR_PTR->SetSwitchState( m_strDisplayCfgSwitch, bDisplayShow, m_pWndTree );
	
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		OnConfStateNty(0,0);
		return false;	
	}
	return true;
}

bool CCentCfgDisplayDlg::IsCentCfgDisplayChange()
{
	bool bOpen = false;
	UIFACTORYMGR_PTR->GetSwitchState( m_strTvWallSwitch, bOpen, m_pWndTree );
	BOOL bDisplay = LIBDATAMGRPTR->GetDisplayState();

	if ( ( ( m_emSelTvMode == m_emTvMode ) &&( m_emSelTvMode == emSharp70LX565A ) ) 
		|| ( ( m_emSelTvMode == m_emTvMode )&&( bDisplay == FALSE )&&( bOpen == false ) ) 
			|| (( m_emSelTvMode == m_emTvMode )&&( bDisplay == (BOOL)bOpen )&&( m_vctWndName.size()== 0 ) ) )
	{
		return true;
	}
	else
	{
		return SaveMsgBox();
	}	
}

s32 CCentCfgDisplayDlg::GetCtrlChangeNum()
{
	bool bOpen = false;
	UIFACTORYMGR_PTR->GetSwitchState( m_strTvWallSwitch, bOpen, m_pWndTree );
	BOOL bDisplay = LIBDATAMGRPTR->GetDisplayState();
	
	if ( ( ( m_emSelTvMode == m_emTvMode ) &&( m_emSelTvMode == emSharp70LX565A ) ) 
		|| ( ( m_emSelTvMode == m_emTvMode )&&( bDisplay == FALSE )&&( bOpen == false ) ) 
		|| (( m_emSelTvMode == m_emTvMode )&&( bDisplay == (BOOL)bOpen )&&( m_vctWndName.size()== 0 ) ) )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


bool CCentCfgDisplayDlg::SaveMsgBox()
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

bool CCentCfgDisplayDlg::OnBtnSwitchTVWALL( const IArgs& args )
{
	BOOL bDisplay = LIBDATAMGRPTR->GetDisplayState();
	
	bool bOldDisplay = false;
	UIFACTORYMGR_PTR->GetSwitchState( m_strTvWallSwitch, bOldDisplay, m_pWndTree );

 	if ( bOldDisplay )
 	{
 		UIFACTORYMGR_PTR->LoadScheme( "SchmSwitchOn", m_pWndTree );
 	}
 	else
 	{
// 		TTPDisplayType tDisplayType1, tDisplayType3;
// 		tDisplayType1.emTPT300Type = emTVHDMI1;
// 		tDisplayType1.emTPHduType = emTVHDMI2;
// 		tDisplayType3.emTPT300Type = emTVHDMI1;
// 		tDisplayType3.emTPHduType = emTVHDMI2;
// 		u16 wRet = COMIFMGRPTR->SetDisplayCmd( false, tDisplayType1, tDisplayType3 );
// 		if (wRet != NO_ERROR)
// 		{
// 			WARNMESSAGE( "保存中控电视墙配置请求发送失败" );
// 			return false;
// 		}
// 		m_vctWndName.clear();
// 		UpBtnState();
 		UIFACTORYMGR_PTR->LoadScheme( "SchmSwitchOff", m_pWndTree );
 	}

//	RecoveryTerminalOut( );
//	m_vctWndName.clear();
	UpdateBtnState();
	return true;
}

bool CCentCfgDisplayDlg::OnBtnDisplayCfg(const IArgs& args)
{
	BOOL bDisplayShow = LIBDATAMGRPTR->GetDisplayShowState();

	bool bOldDisplayShow = false;
	UIFACTORYMGR_PTR->GetSwitchState( m_strDisplayCfgSwitch, bOldDisplayShow, m_pWndTree );

	bool bChange = false;
	if( bDisplayShow != (BOOL)bOldDisplayShow )
	{
		bChange = true;
	}
	
	CheckData( m_strDisplayCfgSwitch, bChange );
	return true;
}

LRESULT CCentCfgDisplayDlg::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 && m_pWndTree != NULL )
	{
		return S_FALSE;
	}
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree );
	} 
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree );
	}
	return S_FALSE;

}

LRESULT CCentCfgDisplayDlg::OnDisplayShowNty(WPARAM wparam, LPARAM lparam)
{
	BOOL bDisplayShow = LIBDATAMGRPTR->GetDisplayShowState();
	UIFACTORYMGR_PTR->SetSwitchState( m_strDisplayCfgSwitch, bDisplayShow, m_pWndTree );

	return S_OK;
}

LRESULT CCentCfgDisplayDlg::OnDisplayShowInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bDisplayShow = LIBDATAMGRPTR->GetDisplayShowState();
	UIFACTORYMGR_PTR->SetSwitchState( m_strDisplayCfgSwitch, bDisplayShow, m_pWndTree );

	UpdateBtnState();

	return S_OK;
}

LRESULT CCentCfgDisplayDlg::OnUpdateDisplayModel( WPARAM wParam, LPARAM lParam )
{
	TCentreTVCfg atCentreTVCfg[MAX_CENTRETV_NUM];
	memcpy( atCentreTVCfg, LIBDATAMGRPTR->GetCentreTVCfg(), sizeof(atCentreTVCfg)) ;

	m_emTvMode = atCentreTVCfg[0].emTvModle;
	m_emSelTvMode = m_emTvMode;
	UpdateTvState(m_emTvMode);
	return S_OK;
}

LRESULT CCentCfgDisplayDlg::OnTvModeInd( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = FALSE;

	bSuccess =*(BOOL*)lParam;

	if ( bSuccess == TRUE )
	{
		m_emTvMode = *(EmTVModle*)wParam;
	}
	else
	{
		WARNMESSAGE( "电视机型号配置失败" );
	}
	m_emSelTvMode = m_emTvMode;
	UpdateTvState(m_emTvMode);
	UpdateBtnState();
	return S_OK;
}

LRESULT CCentCfgDisplayDlg::OnUpdateDisplayInfo( WPARAM wParam, LPARAM lParam )
{
/*	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}*/
	BOOL bSuccess = (BOOL)wParam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "中控电视墙配置失败" );
	}
	else
	{
		m_vctWndName.clear();
	}
	SetDisplayInfo();
	UpdateBtnState();

	return S_FALSE;
}

bool CCentCfgDisplayDlg::OnTerminalOut1Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	TTPDisplayType tDisplayType;
	tDisplayType.emTPT300Type = GetDisplayType(m_strTerminalOut1);
	TTPDisplayType tOldDisplayType = LIBDATAMGRPTR->GetDisplayType1();
	
	if ( tOldDisplayType.emTPT300Type != tDisplayType.emTPT300Type )
	{
		bChange = true;	
	}
	
	CheckData( m_strTerminalOut1,bChange );
	UpdateBtnState();

	return true;	
}

bool CCentCfgDisplayDlg::OnTVWALLOut1Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	TTPDisplayType tDisplayType;
	tDisplayType.emTPHduType = GetDisplayType(m_strTVWALLOut1);
	TTPDisplayType tOldDisplayType = LIBDATAMGRPTR->GetDisplayType1();
	
	if ( tOldDisplayType.emTPHduType != tDisplayType.emTPHduType )
	{
		bChange = true;	
	}
	
	CheckData( m_strTVWALLOut1,bChange );
	UpdateBtnState();

	return true;	
}

bool CCentCfgDisplayDlg::OnTerminalOut3Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	TTPDisplayType tDisplayType;
	tDisplayType.emTPT300Type = GetDisplayType(m_strTerminalOut3);
	TTPDisplayType tOldDisplayType = LIBDATAMGRPTR->GetDisplayType3();
	
	if ( tOldDisplayType.emTPT300Type != tDisplayType.emTPT300Type )
	{
		bChange = true;	
	}
	
	CheckData( m_strTerminalOut3, bChange );
	UpdateBtnState();

	return true;	
}

bool CCentCfgDisplayDlg::OnTVWALLOut3Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	TTPDisplayType tDisplayType;
	tDisplayType.emTPHduType = GetDisplayType(m_strTVWALLOut3);
	TTPDisplayType tOldDisplayType = LIBDATAMGRPTR->GetDisplayType3();
	
	if ( tOldDisplayType.emTPHduType != tDisplayType.emTPHduType )
	{
		bChange = true;	
	}
	
	CheckData( m_strTVWALLOut3,bChange );
	UpdateBtnState();
	return true;	
}

bool CCentCfgDisplayDlg::OnSelDisplay550A( const IArgs& args )
{
	bool bChange = false;
	m_emSelTvMode = emSharp70LX550A;
	UpdateTvState(m_emSelTvMode);
	UpdateBtnState();
	return true;	
}

bool CCentCfgDisplayDlg::OnSelDisplayGM01A( const IArgs& args )
{
	bool bChange = false;
	m_emSelTvMode = emKeShi70GMO1A;
	UpdateTvState(m_emSelTvMode);
	UpdateBtnState();
	return true;	
}

bool CCentCfgDisplayDlg::OnSelDisplayGH01A( const IArgs& args )
{
	bool bChange = false;
	m_emSelTvMode = emKeShi70GH01A;
	UpdateTvState(m_emSelTvMode);
	UpdateBtnState();
	return true;	
}

bool CCentCfgDisplayDlg::OnSelDisplay70B17( const IArgs& args )
{
	bool bChange = false;
	m_emSelTvMode = emKangGuan70B17;
	
	UpdateTvState(m_emSelTvMode);
	UpdateBtnState();
	return true;	
}

bool CCentCfgDisplayDlg::OnSelDisplay665A( const IArgs& args )
{
    bool bChange = false;
    m_emSelTvMode = emSharp70LX565A;
    
    UpdateTvState(m_emSelTvMode);
    UpdateBtnState();
    return true;	
}

bool CCentCfgDisplayDlg::OnSelDisplay70GM44A( const IArgs& args )
{
    bool bChange = false;
    m_emSelTvMode = emKeShi70GM44A;
    
    UpdateTvState(m_emSelTvMode);
    UpdateBtnState();
    return true;	
}

EmTVInputSelect CCentCfgDisplayDlg::GetDisplayType( String strCtrl )
{
	String strDisplayType;
	UIFACTORYMGR_PTR->GetComboText( strCtrl, strDisplayType, m_pWndTree );

	if ( strDisplayType.find( "HDMI 1", 0 ) != string::npos )
	{
		return emTVHDMI1;
	}
	else if ( strDisplayType.find( "HDMI 2", 0 ) != string::npos )
	{
		return emTVHDMI2;
	}
	else if ( strDisplayType.find( "HDMI 3", 0 ) != string::npos )
	{
		return emTVHDMI3;
	}
	else if ( strDisplayType.find( "HDMI 4", 0 ) != string::npos )
	{
		return emTVHDMI4;
	}
	else if ( strDisplayType.find( "YPbPr", 0 ) != string::npos )
	{
		return emTVYpbPr;
	}
	else if ( strDisplayType.find( "CVBS1", 0 ) != string::npos )
	{
		return emTVCVBS1;
	}
	else if ( strDisplayType.find( "CVBS2", 0 ) != string::npos )
	{
		return emTVCVBS2;
	}
	else if ( strDisplayType.find( "电脑", 0 ) != string::npos )
	{
		return emTVComputer;
	}
}

string CCentCfgDisplayDlg::TransDisplayType( EmTVInputSelect emType )
{
	string strType;
	switch ( emType )
	{
	case emTVHDMI1:
		strType = "HDMI 1";
		break;
	case emTVHDMI2:
		strType = "HDMI 2";
		break;
	case emTVHDMI3:
		strType = "HDMI 3";
		break;
	case emTVHDMI4:
		strType = "HDMI 4";
		break;
	case emTVYpbPr:
		strType = "YPbPr";
		break;
	case emTVCVBS1:
		strType = "CVBS1";
		break;
	case emTVCVBS2:
		strType = "CVBS2";
		break;
	case emTVComputer:
		strType = "电脑";
		break;
	default:
		strType = "";
		break;
	}

	return strType;
}

void CCentCfgDisplayDlg::SetDisplayInfo()
{
	BOOL bDisplay = LIBDATAMGRPTR->GetDisplayState();
	UIFACTORYMGR_PTR->SetSwitchState( m_strTvWallSwitch, bDisplay, m_pWndTree );
	
	TTPDisplayType tDisplayType = LIBDATAMGRPTR->GetDisplayType1();
	String strType = TransDisplayType( tDisplayType.emTPT300Type );
	UIFACTORYMGR_PTR->SetComboText( m_strTerminalOut1, strType, m_pWndTree );
	
	strType = TransDisplayType( tDisplayType.emTPHduType );
	UIFACTORYMGR_PTR->SetComboText( m_strTVWALLOut1, strType, m_pWndTree );
	
	tDisplayType = LIBDATAMGRPTR->GetDisplayType3();
	strType = TransDisplayType( tDisplayType.emTPT300Type );
	UIFACTORYMGR_PTR->SetComboText( m_strTerminalOut3, strType, m_pWndTree );
	
	strType = TransDisplayType( tDisplayType.emTPHduType );
	UIFACTORYMGR_PTR->SetComboText( m_strTVWALLOut3, strType, m_pWndTree );
	
	if ( bDisplay )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmSwitchOn", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmSwitchOff", m_pWndTree );
	}
}

void CCentCfgDisplayDlg::UpdateTvState( EmTVModle emTvMode)
{
	m_vecOut.clear();

	if ( emTvMode == emSharp70LX565A )
	{
		UIFACTORYMGR_PTR->LoadScheme("Schm665A",m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme("SchHide",m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("SchHide",m_pWndTree);

		if ( emTvMode == emSharp70LX550A )
		{
			m_vecOut.push_back("HDMI 1");
			m_vecOut.push_back("HDMI 2");
			m_vecOut.push_back("HDMI 3");
			m_vecOut.push_back("HDMI 4");
			UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut1, m_vecOut, m_pWndTree ); 
			UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut1, m_vecOut, m_pWndTree ); 
			UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut3, m_vecOut, m_pWndTree ); 
			UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut3, m_vecOut, m_pWndTree );
			SetDisplayInfo();
			UIFACTORYMGR_PTR->LoadScheme("Schm550A",m_pWndTree);
		}
		else if( emTvMode == emKeShi70GMO1A )
		{
			UIFACTORYMGR_PTR->LoadScheme("SchmGM01A",m_pWndTree);
			m_vecOut.push_back("HDMI 1");
			m_vecOut.push_back("HDMI 2");
			UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut1, m_vecOut, m_pWndTree ); 
			UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut1, m_vecOut, m_pWndTree ); 
			UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut3, m_vecOut, m_pWndTree ); 
			UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut3, m_vecOut, m_pWndTree );
			UIFACTORYMGR_PTR->SetComboText( m_strTerminalOut1, "HDMI 1", m_pWndTree );
			UIFACTORYMGR_PTR->SetComboText( m_strTVWALLOut1, "HDMI 2", m_pWndTree );
			UIFACTORYMGR_PTR->SetComboText( m_strTerminalOut3, "HDMI 1", m_pWndTree );
			UIFACTORYMGR_PTR->SetComboText( m_strTVWALLOut3, "HDMI 2", m_pWndTree );
		}
        else if ( emTvMode == emKeShi70GH01A )
        {
            m_vecOut.push_back("HDMI 1");
            m_vecOut.push_back("HDMI 2");
            m_vecOut.push_back("HDMI 3");
            m_vecOut.push_back("HDMI 4");
            UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut1, m_vecOut, m_pWndTree ); 
            UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut1, m_vecOut, m_pWndTree ); 
            UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut3, m_vecOut, m_pWndTree ); 
            UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut3, m_vecOut, m_pWndTree );
            SetDisplayInfo();
			UIFACTORYMGR_PTR->LoadScheme("SchmGH01A",m_pWndTree);
        }
        else if ( emTvMode == emKeShi70GM44A )
        {
            m_vecOut.push_back("HDMI 1");
            m_vecOut.push_back("HDMI 2");
            m_vecOut.push_back("HDMI 3");
            m_vecOut.push_back("HDMI 4");
            UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut1, m_vecOut, m_pWndTree ); 
            UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut1, m_vecOut, m_pWndTree ); 
            UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut3, m_vecOut, m_pWndTree ); 
            UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut3, m_vecOut, m_pWndTree );
            SetDisplayInfo();
            UIFACTORYMGR_PTR->LoadScheme("Schm70GM44A",m_pWndTree);
        }
		else
		{
			m_vecOut.push_back("HDMI 1");
			m_vecOut.push_back("HDMI 2");
			m_vecOut.push_back("HDMI 3");
			m_vecOut.push_back("HDMI 4");
			UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut1, m_vecOut, m_pWndTree ); 
			UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut1, m_vecOut, m_pWndTree ); 
			UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut3, m_vecOut, m_pWndTree ); 
			UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut3, m_vecOut, m_pWndTree );
			SetDisplayInfo();
			UIFACTORYMGR_PTR->LoadScheme("Schm70B17",m_pWndTree);
		}
	}
}

void CCentCfgDisplayDlg::RecoveryTerminalOut( )
{
	TTPDisplayType tDisplayType = LIBDATAMGRPTR->GetDisplayType1();
	String strType = TransDisplayType( tDisplayType.emTPT300Type );
	UIFACTORYMGR_PTR->SetComboText( m_strTerminalOut1, strType, m_pWndTree );
	
	strType = TransDisplayType( tDisplayType.emTPHduType );
	UIFACTORYMGR_PTR->SetComboText( m_strTVWALLOut1, strType, m_pWndTree );
	
	tDisplayType = LIBDATAMGRPTR->GetDisplayType3();
	strType = TransDisplayType( tDisplayType.emTPT300Type );
	UIFACTORYMGR_PTR->SetComboText( m_strTerminalOut3, strType, m_pWndTree );
	
	strType = TransDisplayType( tDisplayType.emTPHduType );
	UIFACTORYMGR_PTR->SetComboText( m_strTVWALLOut3, strType, m_pWndTree );
}

void CCentCfgDisplayDlg::UpdateBtnState( )
{
	bool bOpen = false;
	UIFACTORYMGR_PTR->GetSwitchState( m_strTvWallSwitch, bOpen, m_pWndTree );
	BOOL bDisplay = LIBDATAMGRPTR->GetDisplayState();

	if ( ( ( m_emSelTvMode == m_emTvMode ) &&( m_emSelTvMode == emSharp70LX565A ) ) 
		|| ( ( m_emSelTvMode == m_emTvMode )&&( bDisplay == FALSE )&&( bOpen == false ) ) 
			|| (( m_emSelTvMode == m_emTvMode )&&( bDisplay == (BOOL)bOpen )&&( m_vctWndName.size()== 0 ) ) )
	{
		UIFACTORYMGR_PTR->LoadScheme("SchmUnChange",m_pWndTree);
	}
/*	else if ( ( m_emSelTvMode == m_emTvMode )&&( bDisplay == FALSE )&&( bOpen == false ))
	{
		UIFACTORYMGR_PTR->LoadScheme("SchmUnEnable",m_pWndTree);
	}
	else if ( ( m_emSelTvMode == m_emTvMode )&&( bDisplay == (BOOL)bOpen )&&( m_vctWndName.size()== 0 ))
	{
		UIFACTORYMGR_PTR->LoadScheme("SchmUnEnable",m_pWndTree);
	}*/
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("SchmChange",m_pWndTree);
	}
}