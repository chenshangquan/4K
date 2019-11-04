// cfgAudioDlg.cpp: implementation of the CCfgAudioDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgAudioDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgAudioDlg::CCfgAudioDlg()
:m_strMaxPlayTime("01:30")
,m_strMixPort1("CfgAudioDlg/AudioGroup1")
,m_strMixPort2("CfgAudioDlg/AudioGroup2")
,m_strMixPort3("CfgAudioDlg/AudioGroup3")
{
	memset(&m_tOldAudioSetInfo,0,sizeof(m_tOldAudioSetInfo));
	memset(&m_atAudioSetInfo,0,sizeof(m_atAudioSetInfo));
	m_bOldWhiteNoise[0] = FALSE;
	m_bOldWhiteNoise[1] = FALSE;
	m_bOldWhiteNoise[2]= FALSE;
	m_byLastWhiteNoiseTime[0] = 0;
	m_byLastWhiteNoiseTime[1] = 0;
	m_byLastWhiteNoiseTime[2] = 0;
	m_emAux2State = em_Conf_Mix;
	m_emCheckState = em_Mix_Local;
	m_byAudMixVolume = 0;
	m_byAudExtendVolume = 0;
}

CCfgAudioDlg::~CCfgAudioDlg()
{

}

void CCfgAudioDlg::RegMsg()
{
	CCfgAudioDlg* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_Audio_NTY, CCfgAudioDlg::OnUpdateAudioNty, pThis, CCfgAudioDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_Listen_NTY, CCfgAudioDlg::OnSetMixType, pThis, CCfgAudioDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_AUX2_NTY, CCfgAudioDlg::OnSetAux2Info, pThis, CCfgAudioDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DftAudio_NTY, CCfgAudioDlg::OnDefaultAudioNty, pThis, CCfgAudioDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_WhiteNoise_NTY, CCfgAudioDlg::OnWhiteNoiseNty, pThis, CCfgAudioDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_WhiteNoiseUpdate_NTY, CCfgAudioDlg::OnUpdateWhiteNoiseNty, pThis, CCfgAudioDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCfgAudioDlg::OnConfStateNty, pThis, CCfgAudioDlg );
}

void CCfgAudioDlg::RegCBFun()
{
	CCfgAudioDlg *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::InitWnd", CCfgAudioDlg::InitWnd, pThis, CCfgAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnSliderGain1Changed", CCfgAudioDlg::OnSliderGain1Changed, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnSliderGain2Changed", CCfgAudioDlg::OnSliderGain2Changed, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnSliderGain3Changed", CCfgAudioDlg::OnSliderGain3Changed, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnSliderGain4Changed", CCfgAudioDlg::OnSliderGain4Changed, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnSliderGain5Changed", CCfgAudioDlg::OnSliderGain5Changed, pThis, CCfgAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnEditGain1Changed",CCfgAudioDlg::OnEditGain1Changed, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnEditGain2Changed",CCfgAudioDlg::OnEditGain2Changed, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnEditGain3Changed",CCfgAudioDlg::OnEditGain3Changed, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnEditGain4Changed",CCfgAudioDlg::OnEditGain4Changed, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnEditGain5Changed",CCfgAudioDlg::OnEditGain5Changed, pThis, CCfgAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnBtnSwitch1",CCfgAudioDlg::OnBtnSwitch1, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnBtnSwitch2",CCfgAudioDlg::OnBtnSwitch2, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnBtnSwitch3",CCfgAudioDlg::OnBtnSwitch3, pThis, CCfgAudioDlg );

//	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnSliderNoise1Changed",CCfgAudioDlg::OnSliderNoise1Changed, pThis, CCfgAudioDlg );
//	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnSliderNoise2Changed",CCfgAudioDlg::OnSliderNoise2Changed, pThis, CCfgAudioDlg );
//	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnSliderNoise2Changed",CCfgAudioDlg::OnSliderNoise2Changed, pThis, CCfgAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnBtnMAEC",CCfgAudioDlg::OnBtnMAEC, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnBtnAGC",CCfgAudioDlg::OnBtnAGC, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnBtnMANS",CCfgAudioDlg::OnBtnMANS, pThis, CCfgAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnSelMixSound", CCfgAudioDlg::OnSelMixSound, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnBtnAUX2", CCfgAudioDlg::OnBtnAUX2, pThis, CCfgAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnBtnDefault",CCfgAudioDlg::OnBtnDefault, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnBtnSave",CCfgAudioDlg::OnBtnSave, pThis, CCfgAudioDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioDlg::OnBtnCancel",CCfgAudioDlg::OnBtnCancel, pThis, CCfgAudioDlg );
}

void CCfgAudioDlg::UnRegFunc()
{
	
}

bool CCfgAudioDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioDlg/SwitchButton1", FALSE, m_pWndTree);
	UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioDlg/SwitchButton2", FALSE, m_pWndTree);
	UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioDlg/SwitchButton3", FALSE, m_pWndTree);
	UIFACTORYMGR_PTR->SetCheckState( m_strMixPort1, 1, m_pWndTree );
	InitCtrlEnable();
	UpBtnState();
	return true;
}

void CCfgAudioDlg::Clear()
{
	m_vctWndName.clear();
	UpBtnState();
}

bool CCfgAudioDlg::IsCfgAudioChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCfgAudioDlg::SaveMsgBox()
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

bool CCfgAudioDlg::OnBtnCancel( const IArgs& args )
{
	LIBDATAMGRPTR->GetAudioInfo( &m_tOldAudioSetInfo );
	SetAudioData();
	SetMixType();
	SetAux2Info();
	m_vctWndName.clear();
	UpBtnState();

	return true;	
}

bool CCfgAudioDlg::OnBtnDefault( const IArgs& args )
{
	memset( &m_atAudioSetInfo, 0, sizeof(m_atAudioSetInfo) );
	SetDefaultAudioInfo();
	SetDefaultAux2Info();
	SetDefaultMixType();
	memcpy( &m_atAudioSetInfo, &m_tOldAudioSetInfo, sizeof(m_tOldAudioSetInfo) );
	u16 wRet =  COMIFMGRPTR->SetDefaultAudioCmd( &m_atAudioSetInfo );

	u16 wRet1 = COMIFMGRPTR->SetDefaultListenPortCmd(m_emCheckState, m_byAudMixVolume);
	
	u16 wRet2 = COMIFMGRPTR->SetDefaultAux2OutCmd(m_emAux2State, m_byAudExtendVolume);

	if ( NO_ERROR != wRet )
	{
		WARNMESSAGE("恢复默认音频配置请求发送失败");
		return false;
	}
	
	if(NO_ERROR != wRet1)
	{
		WARNMESSAGE("恢复默认监听输出混音端口请求发送失败");
		return false;
	}
	
	if(NO_ERROR != wRet2)
	{
		WARNMESSAGE("恢复默认本地扩声输出请求发送失败");
		return false;
	}

	return true;
}

bool CCfgAudioDlg::OnBtnSave( const IArgs& args )
{
	SaveGroup();
	
	u16 wRet = COMIFMGRPTR->SetAudioInfoCmd( &m_atAudioSetInfo );

	u16 wRet1 = COMIFMGRPTR->SetListenPortCmd(m_emCheckState, m_byAudMixVolume );

	u16 wRet2 = COMIFMGRPTR->SetAux2OutCmd(m_emAux2State, m_byAudExtendVolume);

	if ( NO_ERROR != wRet )
	{
		WARNMESSAGE("保存音频接口配置请求发送失败");
		return false;
	}

	if(NO_ERROR != wRet1)
	{
		WARNMESSAGE("保存监听输出混音端口请求发送失败");
		return false;
	}

	if(NO_ERROR != wRet2)
	{
		WARNMESSAGE("保存本地扩声输出请求发送失败");
		return false;
	}

	return true;
}

bool CCfgAudioDlg::OnSliderGain1Changed(const IArgs & arg )
{
	UpdateGainNum( "CfgAudioDlg/SliderGain1", "CfgAudioDlg/GainEdit1" , 0 );
	return true;
}

bool CCfgAudioDlg::OnSliderGain2Changed(const IArgs & arg )
{
	UpdateGainNum( "CfgAudioDlg/SliderGain2", "CfgAudioDlg/GainEdit2" , 1 );
	return true;
}

bool CCfgAudioDlg::OnSliderGain3Changed(const IArgs & arg )
{
	UpdateGainNum( "CfgAudioDlg/SliderGain3", "CfgAudioDlg/GainEdit3" , 2 );
	return true;
}

bool CCfgAudioDlg::OnSliderGain4Changed(const IArgs & arg )
{
	Value_CSliderCtrlPos pos;
	UIFACTORYMGR_PTR->GetPropertyValue( pos, "CfgAudioDlg/SliderGain4", m_pWndTree );
	s8 chData[8];
	sprintf( chData, "%u", pos.nPos );
	UIFACTORYMGR_PTR->SetCaption( "CfgAudioDlg/GainEdit4", chData, m_pWndTree);
	
	//GetAudioInfo();
	bool bChange = false;
	if ( pos.nPos != m_byAudMixVolume )
	{
		bChange = true;
	}
	CheckData( "CfgAudioDlg/SliderGain4", bChange );	
	return true;
}

bool CCfgAudioDlg::OnSliderGain5Changed(const IArgs & arg )
{
	Value_CSliderCtrlPos pos;
	UIFACTORYMGR_PTR->GetPropertyValue( pos, "CfgAudioDlg/SliderGain5", m_pWndTree );
	s8 chData[8];
	sprintf( chData, "%u", pos.nPos );
	UIFACTORYMGR_PTR->SetCaption( "CfgAudioDlg/GainEdit5", chData, m_pWndTree);
	
	//GetAudioInfo();
	bool bChange = false;
	if ( pos.nPos != m_byAudExtendVolume )
	{
		bChange = true;
	}
	CheckData( "CfgAudioDlg/SliderGain5", bChange );
	return true;
}

bool CCfgAudioDlg::OnEditGain1Changed(const IArgs & arg )
{
	UpdateGainEdit( "CfgAudioDlg/GainEdit1","CfgAudioDlg/SliderGain1",0 );
	return true;
}

bool CCfgAudioDlg::OnEditGain2Changed(const IArgs & arg )
{
	UpdateGainEdit( "CfgAudioDlg/GainEdit2","CfgAudioDlg/SliderGain2",1 );
	return true;
}

bool CCfgAudioDlg::OnEditGain3Changed(const IArgs & arg )
{
	UpdateGainEdit( "CfgAudioDlg/GainEdit3","CfgAudioDlg/SliderGain3",2 );
	return true;
}

bool CCfgAudioDlg::OnEditGain4Changed(const IArgs & arg )
{
	String strEdit;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioDlg/GainEdit4", strEdit, m_pWndTree );
	Value_CSliderCtrlPos pos;
	pos.nPos = atoi(strEdit.c_str());
	if ( pos.nPos >= 31 )
	{
		pos.nPos = 31;
	}
	
	s8 chVal[5] = { 0 };
	itoa( pos.nPos, chVal,10 );
	UIFACTORYMGR_PTR->SetCaption( "CfgAudioDlg/GainEdit4", chVal, m_pWndTree );
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( "CfgAudioDlg/GainEdit4", m_pWndTree );
	//将光标移动至最后一个字
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	UIFACTORYMGR_PTR->SetPropertyValue( pos,"CfgAudioDlg/SliderGain4",m_pWndTree );
	
	//GetAudioInfo();
	bool bChange = false;
	if ( pos.nPos != m_byAudMixVolume)
	{
		bChange = true;
	}
	CheckData("CfgAudioDlg/GainEdit4",bChange);	
	CheckData("CfgAudioDlg/SliderGain4",bChange);	//slider
	return true;
}

bool CCfgAudioDlg::OnEditGain5Changed(const IArgs & arg )
{
	String strEdit;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioDlg/GainEdit5", strEdit, m_pWndTree );
	Value_CSliderCtrlPos pos;
	pos.nPos = atoi(strEdit.c_str());
	if ( pos.nPos >= 31 )
	{
		pos.nPos = 31;
	}
	
	s8 chVal[5] = { 0 };
	itoa( pos.nPos, chVal,10 );
	UIFACTORYMGR_PTR->SetCaption( "CfgAudioDlg/GainEdit5", chVal, m_pWndTree );
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( "CfgAudioDlg/GainEdit5", m_pWndTree );
	//将光标移动至最后一个字
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	UIFACTORYMGR_PTR->SetPropertyValue( pos,"CfgAudioDlg/SliderGain5",m_pWndTree );
	
	//GetAudioInfo();
	bool bChange = false;
	if ( pos.nPos != m_byAudMixVolume)
	{
		bChange = true;
	}
	CheckData("CfgAudioDlg/GainEdit5",bChange);	
	CheckData("CfgAudioDlg/SliderGain5",bChange);	//slider
	return true;
}

bool CCfgAudioDlg::OnBtnSwitch1(const IArgs & arg )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{	
		MSG_BOX_OK( _T("有会议进行中，禁止开启白噪声") );
		return false;	
	} 

	SendWhiteNoiseReq("CfgAudioDlg/SwitchButton1", 0 );
	return true;
}

bool CCfgAudioDlg::OnBtnSwitch2(const IArgs & arg )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{	
		MSG_BOX_OK( _T("有会议进行中，禁止开启白噪声") );
		return false;	
	} 
	SendWhiteNoiseReq("CfgAudioDlg/SwitchButton2", 1 );
	return true;
}

bool CCfgAudioDlg::OnBtnSwitch3(const IArgs & arg )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{	
		MSG_BOX_OK( _T("有会议进行中，禁止开启白噪声") );
		return false;	
	} 
	SendWhiteNoiseReq("CfgAudioDlg/SwitchButton3", 2 );
	return true;
}

bool CCfgAudioDlg::OnBtnMAEC(const IArgs & arg )
{
	bool bMAECSwitch = false;										
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioDlg/SwitchButtonOfMAEC", bMAECSwitch, m_pWndTree );
	bool bChange = false;
	if ( (BOOL)bMAECSwitch != m_tOldAudioSetInfo.m_bIsAECEnable )
	{
		bChange = true;
	}	
	CheckData("CfgAudioDlg/SwitchButtonOfMAEC",bChange);
	return true;
}

bool CCfgAudioDlg::OnBtnAGC(const IArgs & arg )
{
	bool bAGCSwitch = false;										
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioDlg/SwitchButtonOfAGC", bAGCSwitch, m_pWndTree );
	bool bChange = false;
	if ( (BOOL)bAGCSwitch != m_tOldAudioSetInfo.m_bIsAGCEnable )
	{
		bChange = true;
	}	
	CheckData("CfgAudioDlg/SwitchButtonOfAGC",bChange);
	return true;
}

bool CCfgAudioDlg::OnBtnMANS(const IArgs & arg )
{
	bool bMANSSwitch = false;										
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioDlg/SwitchButtonOfMANS", bMANSSwitch, m_pWndTree );
	bool bChange = false;
	if ( (BOOL)bMANSSwitch != m_tOldAudioSetInfo.m_bIsANSEnable )
	{
		bChange = true;
	}	
	CheckData("CfgAudioDlg/SwitchButtonOfMANS",bChange);
	return true;
}


HRESULT CCfgAudioDlg::OnUpdateAudioNty( WPARAM wparam, LPARAM lparam )
{
/*	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
*/	
	BOOL bSuccess = *(BOOL*)lparam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "保存音频配置失败" );
		return S_FALSE;
	}

	LIBDATAMGRPTR->GetAudioInfo( &m_tOldAudioSetInfo );
	SetAudioData();
	
	m_vctWndName.clear();
	UpBtnState();
	UIFACTORYMGR_PTR->LoadScheme( "SchmLeaveConf", m_pWndTree );
	return S_OK;
}

HRESULT CCfgAudioDlg::OnSetMixType(WPARAM wparam, LPARAM lparam)
{
	EmAudMixType emAudMixType = *(EmAudMixType *)lparam;
	m_byAudMixVolume = *(u8 *)wparam;
	
	if( emAudMixType == em_Mix_Local)
	{
		m_emCheckState = em_Mix_Local;
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort1, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort2, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort3, 0, m_pWndTree );
	}
	else if( emAudMixType == em_Mix_Peer)
	{
		m_emCheckState = em_Mix_Peer;
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort2, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort1, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort3, 0, m_pWndTree );
	}
	else
	{
		m_emCheckState = em_Mix_LP;
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort3, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort2, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort1, 0, m_pWndTree );
	}

	s8 chData[8] = {0};
	Value_CSliderCtrlPos valuePos;
	valuePos.nPos = m_byAudMixVolume;
	UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioDlg/SliderGain4",m_pWndTree );
	sprintf( chData, "%u", m_byAudMixVolume );
	UIFACTORYMGR_PTR->SetCaption( "CfgAudioDlg/GainEdit4", chData, m_pWndTree);
	
	return S_OK;
}

HRESULT CCfgAudioDlg::OnSetAux2Info(WPARAM wparam, LPARAM lparam)
{
	EmAudExtend emAudExtend  = *(EmAudExtend *)lparam;
	m_byAudExtendVolume = *(u8 *)wparam;
	
	if(emAudExtend == em_Conf_Mix)
	{
		m_emAux2State = em_Conf_Mix;
		UIFACTORYMGR_PTR->SetSwitchState("CfgAudioDlg/SwitchButtonOfAUX2", FALSE, m_pWndTree);
	}
	else
	{
		m_emAux2State = em_Local_Extend;
		UIFACTORYMGR_PTR->SetSwitchState("CfgAudioDlg/SwitchButtonOfAUX2", TRUE, m_pWndTree);
	}

	s8 chData[8] = {0};
	Value_CSliderCtrlPos valuePos;
	valuePos.nPos = m_byAudExtendVolume;
	UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioDlg/SliderGain5",m_pWndTree );
	sprintf( chData, "%u", m_byAudExtendVolume );
	UIFACTORYMGR_PTR->SetCaption( "CfgAudioDlg/GainEdit5", chData, m_pWndTree);
	
	return S_OK;
}

HRESULT CCfgAudioDlg::OnDefaultAudioNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "恢复音频配置默认设置失败" );
		return S_FALSE;
	}
	else
	{
		SetDefaultAudioInfo();
		SetAudioData();
		m_vctWndName.clear();
		UpBtnState();
	}	
	return S_OK;			
}

HRESULT CCfgAudioDlg::OnWhiteNoiseNty( WPARAM wparam, LPARAM lparam )
{
	BOOL *bWhiteNoise = NULL;
	BOOL bSuccess = *(BOOL*)lparam;
	LIBDATAMGRPTR->GetWhiteNoiseInfo( &bWhiteNoise );
	for( s16 swIndex = 0; swIndex < 3; swIndex ++ )
	{
		m_bOldWhiteNoise[swIndex] = *( bWhiteNoise + swIndex );
	}

	initWhiteNoise();
	if ( !bSuccess )
	{
		WARNMESSAGE( "设置白噪声失败" );
		return S_FALSE;
	}
	return S_OK;			
}

/*
bool CCfgAudioDlg::OnSliderNoise1Changed(const IArgs & arg )
{
	UpdatePlayTimer("CfgAudioDlg/SliderNoise1","CfgAudioDlg/stcPlayTime1",0);
	return true;
}

bool CCfgAudioDlg::OnSliderNoise2Changed(const IArgs & arg )
{
	UpdatePlayTimer("CfgAudioDlg/SliderNoise2","CfgAudioDlg/stcPlayTime2",1);
	return true;
}

bool CCfgAudioDlg::OnSliderNoise3Changed(const IArgs & arg )
{
	UpdatePlayTimer("CfgAudioDlg/SliderNoise3","CfgAudioDlg/stcPlayTime3",2);
	return true;
}
*/

bool CCfgAudioDlg::SendWhiteNoiseReq( String strWndName, s32 nNum )
{
	bool bNoiseBtnSwitch = false;												//噪声开关
	UIFACTORYMGR_PTR->GetSwitchState( strWndName, bNoiseBtnSwitch, m_pWndTree );
	u16 wRet =  COMIFMGRPTR->SetAudioWhiteNoiseCmd( bNoiseBtnSwitch , nNum );	
	if ( NO_ERROR != wRet )
	{
		WARNMESSAGE("设置白噪声开关失败");
		return false;
	}	
	return true;
}

void CCfgAudioDlg::UpdateGainEdit( String strEditName, String strSliderName, s32 nNum )
{	
	String strEdit;
	UIFACTORYMGR_PTR->GetCaption( strEditName, strEdit, m_pWndTree );
	Value_CSliderCtrlPos pos;
	pos.nPos = atoi(strEdit.c_str());
	if ( pos.nPos >= 31 )
	{
		pos.nPos = 31;
	}
	
	s8 chVal[5] = { 0 };
	itoa( pos.nPos, chVal,10 );
	UIFACTORYMGR_PTR->SetCaption( strEditName, chVal, m_pWndTree );
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strEditName, m_pWndTree );
	//将光标移动至最后一个字
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	UIFACTORYMGR_PTR->SetPropertyValue( pos,strSliderName,m_pWndTree );
	
	//GetAudioInfo();
	bool bChange = false;
	if ( pos.nPos != m_tOldAudioSetInfo.m_abyOutputGain[nNum])
	{
		bChange = true;
	}
	CheckData(strEditName,bChange);	
	CheckData(strSliderName,bChange);	//slider
}

void CCfgAudioDlg::UpdateGainNum( String strGainName, String strEditName, s32 nNum )
{
	Value_CSliderCtrlPos pos;
	UIFACTORYMGR_PTR->GetPropertyValue( pos, strGainName, m_pWndTree );
	s8 chData[8];
	sprintf( chData, "%u", pos.nPos );
	UIFACTORYMGR_PTR->SetCaption( strEditName, chData, m_pWndTree);
	
	//GetAudioInfo();
	bool bChange = false;
	if ( pos.nPos != m_tOldAudioSetInfo.m_abyOutputGain[nNum] )
	{
		bChange = true;
	}
	CheckData( strGainName, bChange );	
}

void CCfgAudioDlg::initWhiteNoise( )
{
	UpdateWhiteNoiseState("CfgAudioDlg/SwitchButton1",m_bOldWhiteNoise[0]);
	if ( m_bOldWhiteNoise[0] == FALSE )
	{
		UpdatePlayTimer("CfgAudioDlg/SliderNoise1","CfgAudioDlg/stcPlayTime1",0,0);
	}

	UpdateWhiteNoiseState("CfgAudioDlg/SwitchButton2",m_bOldWhiteNoise[1]);
	if ( m_bOldWhiteNoise[1] == FALSE )
	{
		UpdatePlayTimer("CfgAudioDlg/SliderNoise2","CfgAudioDlg/stcPlayTime2",1,0);
	}

	UpdateWhiteNoiseState("CfgAudioDlg/SwitchButton3",m_bOldWhiteNoise[2]);
	if ( m_bOldWhiteNoise[2] == FALSE )
	{
		UpdatePlayTimer("CfgAudioDlg/SliderNoise3","CfgAudioDlg/stcPlayTime3",2,0);
	}
}

void CCfgAudioDlg::UpdateWhiteNoiseState( String strWndName ,BOOL bIsOpen )
{
	bool bWhiteNoiseState = false;
	bool bCurrentState = false;

	UIFACTORYMGR_PTR->GetSwitchState( strWndName, bCurrentState, m_pWndTree);
	bWhiteNoiseState = ( bIsOpen == TRUE );
	if ( bCurrentState != bWhiteNoiseState )
	{
		UIFACTORYMGR_PTR->SetSwitchState( strWndName, bIsOpen, m_pWndTree);
	}
}

HRESULT CCfgAudioDlg::OnUpdateWhiteNoiseNty( WPARAM wparam, LPARAM lparam  )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		return false;	
	} 

	u8 byWhiteNoiseTime = *(u8*)( lparam);
	u32 dwWhiteNoiseNum = *( u32 *)( wparam );
	
	switch( dwWhiteNoiseNum )
	{
	case 0:
		UpdateWhiteNoiseState("CfgAudioDlg/SwitchButton1",TRUE);
		UpdatePlayTimer("CfgAudioDlg/SliderNoise1","CfgAudioDlg/stcPlayTime1",0,byWhiteNoiseTime);
		break;
	case 1:
		UpdateWhiteNoiseState("CfgAudioDlg/SwitchButton2",TRUE);
		UpdatePlayTimer("CfgAudioDlg/SliderNoise2","CfgAudioDlg/stcPlayTime2",1,byWhiteNoiseTime);
		break;
	case 2:
		UpdateWhiteNoiseState("CfgAudioDlg/SwitchButton3",TRUE);
		UpdatePlayTimer("CfgAudioDlg/SliderNoise3","CfgAudioDlg/stcPlayTime3",2,byWhiteNoiseTime);
		break;
	default:
		break;
	}

	return S_OK;
}

void CCfgAudioDlg::UpdatePlayTimer( String strWhiteNoiseSlider, String strPlayTimeName,s32 nNum ,u8 byWhiteNoiseTime )
{
	Value_CSliderCtrlPos pos;
	u16 dwMinute = 0;
	u16 dwSecend = 0;
	s8 chMinute[4];
	s8 chSecend[4];
	memset(chMinute,0,sizeof(chMinute));
	memset(chSecend,0,sizeof(chSecend));

	UIFACTORYMGR_PTR->GetPropertyValue( pos, strWhiteNoiseSlider, m_pWndTree );
	//	swMinute = pos.nPos/60;
	//	swSecend = pos.nPos%60;
	if ( m_byLastWhiteNoiseTime[nNum] != byWhiteNoiseTime )
	{
		m_byLastWhiteNoiseTime[nNum] = byWhiteNoiseTime;
		dwMinute = byWhiteNoiseTime/60;
		dwSecend = byWhiteNoiseTime%60;
		s8 chData[12];
		if ( dwMinute < 10 )
		{
			sprintf( chMinute, "0%u",dwMinute);
		}
		else
		{
			sprintf( chMinute, "%u",dwMinute);
		}
		
		if ( dwSecend <10 )
		{
			sprintf( chSecend, "0%u",dwSecend);
		}
		else
		{
			sprintf( chSecend, "%u",dwSecend);
		}
		
		memset(chData,0,sizeof(chData));
		sprintf( chData, "%s:%s/%s",chMinute,chSecend,m_strMaxPlayTime.c_str());
		UIFACTORYMGR_PTR->SetCaption( strPlayTimeName, chData, m_pWndTree);
	}

	if ( pos.nPos != byWhiteNoiseTime )
	{
		pos.nPos = byWhiteNoiseTime;
		if ( pos.nPos >= 90 )
		{
			pos.nPos = 90;
		}
		UIFACTORYMGR_PTR->SetPropertyValue( pos,strWhiteNoiseSlider,m_pWndTree );
	}
}


void CCfgAudioDlg::SetAudioData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	//将界面控件初始化
	InitCtrlEnable();
	
	UpdateGroup(m_tOldAudioSetInfo);

}

void CCfgAudioDlg::SetMixType()
{
	if( m_emCheckState == em_Mix_Local)
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort1, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort2, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort3, 0, m_pWndTree );
	}
	if( m_emCheckState == em_Mix_Peer)
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort1, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort2, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort3, 0, m_pWndTree );
	}
	if(m_emCheckState == em_Mix_LP)
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort1, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort2, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strMixPort3, 1, m_pWndTree );
	}
}

void CCfgAudioDlg::SetAux2Info()
{
	if(m_emAux2State == em_Conf_Mix)
	{
		UIFACTORYMGR_PTR->SetSwitchState("CfgAudioDlg/SwitchButtonOfAUX2", FALSE, m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->SetSwitchState("CfgAudioDlg/SwitchButtonOfAUX2", TRUE, m_pWndTree);
	}
}

void CCfgAudioDlg::InitCtrlEnable()
{
	UIFACTORYMGR_PTR->LoadScheme( "NoWhiteNoise1", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "NoWhiteNoise2", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "NoWhiteNoise3", m_pWndTree );

	UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioDlg/SwitchButtonOfMAEC", FALSE, m_pWndTree);
	UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioDlg/SwitchButtonOfAGC", FALSE, m_pWndTree);
}

bool CCfgAudioDlg::UpdateGroup( TTPMPAudioInfo& tAudioInfo )
{
	s8 chData[8] = {0};
	Value_CSliderCtrlPos valuePos;
	for( int i = 0; i <3; i++ )
	{
		switch( i )
		{
		case 0:
			//第一路音频输出
			valuePos.nPos = tAudioInfo.m_abyOutputGain[0];
			UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioDlg/SliderGain1",m_pWndTree );
			sprintf( chData, "%u", tAudioInfo.m_abyOutputGain[0] );
			UIFACTORYMGR_PTR->SetCaption( "CfgAudioDlg/GainEdit1", chData, m_pWndTree);
			break;
		case 1:
			//第二路音频输出
			valuePos.nPos = tAudioInfo.m_abyOutputGain[1];
			UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioDlg/SliderGain2",m_pWndTree );
			sprintf( chData, "%u", tAudioInfo.m_abyOutputGain[1] );
			UIFACTORYMGR_PTR->SetCaption( "CfgAudioDlg/GainEdit2", chData, m_pWndTree);
			break;
		case 2:
			//第三路音频输出
			valuePos.nPos = tAudioInfo.m_abyOutputGain[2];
			UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioDlg/SliderGain3",m_pWndTree );
			sprintf( chData, "%u", tAudioInfo.m_abyOutputGain[2] );
			UIFACTORYMGR_PTR->SetCaption( "CfgAudioDlg/GainEdit3", chData, m_pWndTree);
			break;
		default:
			break;
		}		
	}
	UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioDlg/SwitchButtonOfAGC", tAudioInfo.m_bIsAGCEnable, m_pWndTree);
	UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioDlg/SwitchButtonOfMAEC", tAudioInfo.m_bIsAECEnable, m_pWndTree);
	UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioDlg/SwitchButtonOfMANS", tAudioInfo.m_bIsANSEnable, m_pWndTree);

	return true;
}

void CCfgAudioDlg::SetDefaultAudioInfo()
{
	memset(&m_tOldAudioSetInfo,0,sizeof(m_tOldAudioSetInfo));
	m_tOldAudioSetInfo.m_abyOutputGain[0]=16;
	m_tOldAudioSetInfo.m_abyOutputGain[1]=16;
	m_tOldAudioSetInfo.m_abyOutputGain[2]=16;
	m_tOldAudioSetInfo.m_bIsAGCEnable = FALSE;
	m_tOldAudioSetInfo.m_bIsAECEnable = TRUE;
	m_tOldAudioSetInfo.m_bIsANSEnable = FALSE;
}

void CCfgAudioDlg::SetDefaultMixType()
{
	m_emCheckState = em_Mix_Local;
	UIFACTORYMGR_PTR->SetCheckState( m_strMixPort1, 1, m_pWndTree );
	m_byAudMixVolume = 16;
}

void CCfgAudioDlg::SetDefaultAux2Info()
{
	m_emAux2State = em_Conf_Mix;
	UIFACTORYMGR_PTR->SetSwitchState("CfgAudioDlg/SwitchButtonOfAUX2", FALSE, m_pWndTree);
	m_byAudExtendVolume = 16;
}

void CCfgAudioDlg::SaveGroup( )
{
	String strEdit;				//
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioDlg/GainEdit1", strEdit, m_pWndTree );
	m_atAudioSetInfo.m_abyOutputGain[0] = /*posGain.nPos*/atoi(strEdit.c_str());

	UIFACTORYMGR_PTR->GetCaption( "CfgAudioDlg/GainEdit2", strEdit, m_pWndTree );
	m_atAudioSetInfo.m_abyOutputGain[1] = /*posGain.nPos*/atoi(strEdit.c_str());

	UIFACTORYMGR_PTR->GetCaption( "CfgAudioDlg/GainEdit3", strEdit, m_pWndTree );
	m_atAudioSetInfo.m_abyOutputGain[2] = /*posGain.nPos*/atoi(strEdit.c_str());

	UIFACTORYMGR_PTR->GetCaption( "CfgAudioDlg/GainEdit4", strEdit, m_pWndTree );
	m_byAudMixVolume = /*posGain.nPos*/atoi(strEdit.c_str());

	UIFACTORYMGR_PTR->GetCaption( "CfgAudioDlg/GainEdit5", strEdit, m_pWndTree );
	m_byAudExtendVolume = /*posGain.nPos*/atoi(strEdit.c_str());

	bool bAGCSwitch = false;										
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioDlg/SwitchButtonOfAGC", bAGCSwitch, m_pWndTree );
	m_atAudioSetInfo.m_bIsAGCEnable = bAGCSwitch;

	bool bMAECSwitch = false;										
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioDlg/SwitchButtonOfMAEC", bMAECSwitch, m_pWndTree );
	m_atAudioSetInfo.m_bIsAECEnable = bMAECSwitch;

	bool bMANSSwitch = false;										
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioDlg/SwitchButtonOfMANS", bMANSSwitch, m_pWndTree );
	m_atAudioSetInfo.m_bIsANSEnable = bMANSSwitch;

	s32  nCheckState1;
	UIFACTORYMGR_PTR->GetCheckState( m_strMixPort1, nCheckState1, m_pWndTree );
	s32  nCheckState2;
	UIFACTORYMGR_PTR->GetCheckState( m_strMixPort2, nCheckState2, m_pWndTree );
	s32  nCheckState3;
	UIFACTORYMGR_PTR->GetCheckState( m_strMixPort3, nCheckState3, m_pWndTree );	
	
	if(1 == nCheckState1)
	{
		m_emCheckState = em_Mix_Local;
	}
	else if(1 == nCheckState2)
	{
		m_emCheckState = em_Mix_Peer;
	}
	else
	{
		m_emCheckState = em_Mix_LP;
	}
	
	bool bAux2Switch = false;
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioDlg/SwitchButtonOfAUX2", bAux2Switch, m_pWndTree );
	if(bAux2Switch)
	{
		m_emAux2State = em_Local_Extend;
	}
	else
	{
		m_emAux2State = em_Conf_Mix;
	}
}

LRESULT CCfgAudioDlg::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 && m_pWndTree != NULL )
	{
		return S_FALSE;
	}
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmInConf1", m_pWndTree );
	} 
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmLeaveConf1", m_pWndTree );
	}
	return S_FALSE;
}

bool CCfgAudioDlg::OnSelMixSound(const IArgs& args)
{
	EmAudMixType emMixtype;
	s32  nCheckState1;
	UIFACTORYMGR_PTR->GetCheckState( m_strMixPort1, nCheckState1, m_pWndTree );
	s32  nCheckState2;
	UIFACTORYMGR_PTR->GetCheckState( m_strMixPort2, nCheckState2, m_pWndTree );
	s32  nCheckState3;
	UIFACTORYMGR_PTR->GetCheckState( m_strMixPort3, nCheckState3, m_pWndTree );
	
	if(nCheckState1 == 1)
	{
		emMixtype = em_Mix_Local;
	}
	else if(nCheckState2 == 1)
	{
		emMixtype = em_Mix_Peer;
    }
	else
	{
		emMixtype = em_Mix_LP;
	}

	bool bChange = false;
	if(emMixtype == m_emCheckState)
	{
		bChange = false;
	}
	else 
	{
		bChange = true;
	}
	
	CheckData("MixAudType", bChange);
	return true;
}

bool CCfgAudioDlg::OnBtnAUX2(const IArgs& args)
{	
	EmAudExtend emAudExtend;
	bool bAux2Switch = false;
    UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioDlg/SwitchButtonOfAUX2", bAux2Switch, m_pWndTree );
	if(!bAux2Switch)
	{
		emAudExtend = em_Conf_Mix;
	}
	else
	{
		emAudExtend = em_Local_Extend;
	}

	bool bChange = false;
	if(m_emAux2State == emAudExtend)
	{
		bChange = false;
	}
	else
	{
		bChange = true;
	}

	CheckData("CfgAudioDlg/SwitchButtonOfAUX2", bChange);

	return true;
}






