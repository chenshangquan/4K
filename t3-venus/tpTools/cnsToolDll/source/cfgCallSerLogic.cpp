// cfgCallSerLogic.cpp: implementation of the CCfgCallSerLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgCallSerLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgCallSerLogic::CCfgCallSerLogic()
: m_strCallMode("ComboboxCallMode")
, m_strShowMode("ComboboxShowMode")
, m_strShowQuantumErp("ComboboxShowQuantumErp")
/*, m_strBtnAESSwitch("CfgCallSerDlg/BtnAESSwitch")*/
, m_strNoEncrptyPort("CfgCallSerDlg/AudioGroup1")
, m_strAESEncrptyPort("CfgCallSerDlg/AudioGroup2")
, m_strQuantumErpPort("CfgCallSerDlg/AudioGroup3")
{
	//m_emTPEncryptType = emTPEncryptTypeNone;
}

CCfgCallSerLogic::~CCfgCallSerLogic()
{

}

void CCfgCallSerLogic::RegMsg()
{
	CCfgCallSerLogic* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_VIDEOFORMAT_IND, CCfgCallSerLogic::OnUpdateVideoFormat, pThis, CCfgCallSerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_DUALVIDEOFORMAT_IND, CCfgCallSerLogic::OnUpdateDualVideoFormat, pThis, CCfgCallSerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CALLRATE_IND, CCfgCallSerLogic::OnUpdateCallRate, pThis, CCfgCallSerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_DUALCALLRATE_IND, CCfgCallSerLogic::OnUpdateDualCallRate, pThis, CCfgCallSerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CONFDIS_IND, CCfgCallSerLogic::OnUpdateConfDis, pThis, CCfgCallSerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CONFPOOL_IND, CCfgCallSerLogic::OnUpdateConfPoll, pThis, CCfgCallSerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCfgCallSerLogic::OnConfStateNty, pThis, CCfgCallSerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_AUDIOFORMAT_IND, CCfgCallSerLogic::OnUpdateAudioFormat, pThis, CCfgCallSerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_EncryptInfo_Nty, CCfgCallSerLogic::OnEncryptInfoNty, pThis, CCfgCallSerLogic );
}

void CCfgCallSerLogic::RegCBFun()
{
	CCfgCallSerLogic* pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::InitWnd", CCfgCallSerLogic::InitWnd, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnBtnSave", CCfgCallSerLogic::OnBtnSave, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnBtnCancel", CCfgCallSerLogic::OnBtnCancel, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnCallModeChange", CCfgCallSerLogic::OnCallModeChange, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnShowModeChange", CCfgCallSerLogic::OnShowModeChange, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnBtnSwitchDiscuss", CCfgCallSerLogic::OnBtnSwitchDiscuss, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnBtnSwitchPolling", CCfgCallSerLogic::OnBtnSwitchPolling, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnPollTimeChange", CCfgCallSerLogic::OnPollTimeChange, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnConfRateChange", CCfgCallSerLogic::OnConfRateChange, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnShowRateChange", CCfgCallSerLogic::OnShowRateChange, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnConfRateNoFocus", CCfgCallSerLogic::OnConfRateNoFocus, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnShowRateNoFocus", CCfgCallSerLogic::OnShowRateNoFocus, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnAudioModeChange", CCfgCallSerLogic::OnAudioModeChange, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnSelEncrptyStyle", CCfgCallSerLogic::OnSelEncrptyStyle, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnShowQuantumErpChange", CCfgCallSerLogic::OnShowQuantumErpChange, pThis, CCfgCallSerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCallSerLogic::OnShowQuantumErpNoFocus", CCfgCallSerLogic::OnShowQuantumErpNoFocus, pThis, CCfgCallSerLogic );

}

void CCfgCallSerLogic::UnRegFunc()
{
	
}

bool CCfgCallSerLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	m_vecCallModeData.push_back("4K@30fps");
	m_vecCallModeData.push_back("4K@25fps");
	m_vecCallModeData.push_back("1080P@60fps");
	m_vecCallModeData.push_back("1080P@50fps");
	m_vecCallModeData.push_back("1080P@30fps");
	m_vecCallModeData.push_back("1080P@25fps");
	m_vecCallModeData.push_back("720P@60fps");
	m_vecCallModeData.push_back("720P@50fps");
	m_vecCallModeData.push_back("720P@30fps");
	m_vecCallModeData.push_back("720P@25fps");
// 	m_vecCallModeData.push_back("H.264 BP 1080P@60fps");
// 	m_vecCallModeData.push_back("H.264 BP 1080P@50fps");
// 	m_vecCallModeData.push_back("H.264 BP 1080P@30fps");
// 	m_vecCallModeData.push_back("H.264 BP 1080P@25fps");
// 	m_vecCallModeData.push_back("H.264 BP 720P@60fps");
// 	m_vecCallModeData.push_back("H.264 BP 720P@50fps");
// 	m_vecCallModeData.push_back("H.264 BP 720P@30fps");
// 	m_vecCallModeData.push_back("H.264 BP 720P@25fps");
	m_vecCallModeData.push_back("4CIF@25fps");
	UIFACTORYMGR_PTR->SetComboListData( m_strCallMode, m_vecCallModeData, m_pWndTree ); 
	//UIFACTORYMGR_PTR->SetComboText( m_strCallMode, "H.264 HP 1080P@60fps", m_pWndTree );
	m_vecShowModeData.push_back("4K@30fps");
	m_vecShowModeData.push_back("4K@25fps");
	m_vecShowModeData.push_back("1080P@60fps");
	m_vecShowModeData.push_back("1080P@50fps");
	m_vecShowModeData.push_back("1080P@30fps");
	m_vecShowModeData.push_back("1080P@25fps");
	m_vecShowModeData.push_back("720P@60fps");
	m_vecShowModeData.push_back("720P@50fps");
	m_vecShowModeData.push_back("720P@30fps");
	m_vecShowModeData.push_back("720P@25fps");
// 	m_vecShowModeData.push_back("H.264 BP 1080P@60fps");
// 	m_vecShowModeData.push_back("H.264 BP 1080P@50fps");
// 	m_vecShowModeData.push_back("H.264 BP 1080P@30fps");
// 	m_vecShowModeData.push_back("H.264 BP 1080P@25fps");
// 	m_vecShowModeData.push_back("H.264 BP 720P@60fps");
// 	m_vecShowModeData.push_back("H.264 BP 720P@50fps");
// 	m_vecShowModeData.push_back("H.264 BP 720P@30fps");
// 	m_vecShowModeData.push_back("H.264 BP 720P@25fps");
 	m_vecShowModeData.push_back("4CIF@25fps");
	m_vecShowModeData.push_back("UXGA@60fps");
	m_vecShowModeData.push_back("WXGA@30fps");
	m_vecShowModeData.push_back("SXGA@30fps");
	m_vecShowModeData.push_back("WXGA@5fps");
	m_vecShowModeData.push_back("SXGA@5fps");
	m_vecShowModeData.push_back("XGA@5fps");
	UIFACTORYMGR_PTR->SetComboListData( m_strShowMode, m_vecShowModeData, m_pWndTree ); 
	//UIFACTORYMGR_PTR->SetComboText( m_strShowMode, "H.264 HP 1080P@60fps", m_pWndTree );
	m_vecAudioRateData.push_back("MPEG4 AAC-LD单声道");
	m_vecAudioRateData.push_back("G.711A");
	m_vecAudioRateData.push_back("G.711U");
	m_vecAudioRateData.push_back("G.719");
	m_vecAudioRateData.push_back("G.722.1 Annex C Polycom Siren14");
	m_vecAudioRateData.push_back("MP3");
	m_vecAudioRateData.push_back("MPEG4 AAC-LC单声道");
	UIFACTORYMGR_PTR->SetComboListData( "ComboboxAudioMode", m_vecAudioRateData, m_pWndTree ); 
	//UIFACTORYMGR_PTR->SetComboText( "ComboboxAudioMode", "MPEG4 AAC-LD单声道", m_pWndTree );
	m_vecConfRateData.push_back("512");
	m_vecConfRateData.push_back("1024");
	m_vecConfRateData.push_back("2048");
	m_vecConfRateData.push_back("3072");
	m_vecConfRateData.push_back("4096");
	m_vecConfRateData.push_back("5120");
	m_vecConfRateData.push_back("6144");
	m_vecConfRateData.push_back("7168");
	m_vecConfRateData.push_back("8192");
	UIFACTORYMGR_PTR->SetComboListData( "ComboboxConfRate", m_vecConfRateData, m_pWndTree ); 
	//UIFACTORYMGR_PTR->SetComboText( "ComboboxConfRate", "4096", m_pWndTree );
	m_vecShowRateData.push_back("512");
	m_vecShowRateData.push_back("1024");
	m_vecShowRateData.push_back("2048");
	m_vecShowRateData.push_back("3072");
	m_vecShowRateData.push_back("4096");
	m_vecShowRateData.push_back("5120");
	m_vecShowRateData.push_back("6144");
	m_vecShowRateData.push_back("7168");
	m_vecShowRateData.push_back("8192");
	UIFACTORYMGR_PTR->SetComboListData( "ComboboxShowRate", m_vecShowRateData, m_pWndTree );
	//UIFACTORYMGR_PTR->SetComboText( "ComboboxShowRate", "2048", m_pWndTree );
	m_vecQuantumErpData.push_back("一秒一密");
	m_vecQuantumErpData.push_back("一分一密");
	m_vecQuantumErpData.push_back("一会一密");
	UIFACTORYMGR_PTR->SetComboListData( m_strShowQuantumErp, m_vecQuantumErpData, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( m_strShowQuantumErp, "一秒一密", m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strNoEncrptyPort, 1, m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmNoQuantumErp", m_pWndTree );
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

void CCfgCallSerLogic::Clear()
{
	m_vecCallModeData.clear();
	m_vecShowModeData.clear();
	m_vecConfRateData.clear();
	m_vecShowRateData.clear();
	m_vecAudioRateData.clear();
	m_vctWndName.clear();
	UpBtnState();
}

void CCfgCallSerLogic::UnRegMsg()
{
	
}

bool CCfgCallSerLogic::OnBtnSave( const IArgs& args )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("有会议进行中，不能配置") );
		SetVideoFormat();
		SetDualVideoFormat();
		SetCallRate();
		SetDualCallRate();
		SetConfDisState();
		SetConfPollInfo();
		SetEncryptType();
		SetAudioFormat();
		m_vctWndName.clear();
		UpBtnState();
		return false;	
	}
	String strCaption;
	bool bchange = false;
// 	UIFACTORYMGR_PTR->GetCaption( "EditPollTime", strCaption, m_pWndTree );
// 	u16 wVal = atoi( strCaption.c_str() );
// 	if ( wVal > 7200 || wVal < 5 )
// 	{
// 		MSG_BOX_OK("轮询间隔为 5～7200 间的整数");
// 		UIFACTORYMGR_PTR->SetFocus( "EditPollTime", m_pWndTree );
// 		return false;
// 	}
	//单屏码率
	UIFACTORYMGR_PTR->GetComboText( "ComboboxConfRate", strCaption, m_pWndTree );
	u16 wVal = atoi( strCaption.c_str() );
	UIFACTORYMGR_PTR->GetComboText( "ComboboxShowRate", strCaption, m_pWndTree );
	u16 wDualVal = atoi( strCaption.c_str() );
	if ( wVal <= 0 )
	{
		MSG_BOX_OK( "单屏码率必须为64～8192间的整数" );
		CWnd* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( "ComboboxConfRate", m_pWndTree );
		((CTransparentComboBox*)pWnd)->GetEditPoint()->SetFocus();
		return false;
	}
	if ( wDualVal < 0 )
	{
		MSG_BOX_OK( "演示码率必须为0～8192间的整数" );
		CWnd* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( "ComboboxShowRate", m_pWndTree );
		((CTransparentComboBox*)pWnd)->GetEditPoint()->SetFocus();
		return false;
	}
	if ( wVal + wDualVal > 8192 )
	{
		MSG_BOX_OK("单屏码率+演示码率必须小于等于8192Kbps");
		return false;
	}
	if ( wVal + wDualVal < 64 )
	{
		MSG_BOX_OK("单屏码率+演示码率必须大于等于64Kbps");
		return false;
	}
	bchange = FindCtrlName("ComboboxConfRate");
	if ( bchange )
	{
		u16 wRet = COMIFMGRPTR->CallRateCmd(wVal);
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存单屏码率请求发送失败" );
			return false;
		}
	}
	//演示码率
	bchange = FindCtrlName("ComboboxShowRate");
	if ( bchange )
	{
		u16 wRet = COMIFMGRPTR->DualCallRateCmd(wDualVal);
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存演示码率请求发送失败" );
			return false;
		}
	}
	//会议优选格式
	bchange = FindCtrlName("ComboboxCallMode");
	if ( bchange )
	{
		TTPVidForamt tVidForamt;
		GetCallMode(tVidForamt);
		u16 wRet = COMIFMGRPTR->VideoFormatCmd(tVidForamt);
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存会议优选格式请求发送失败" );
			return false;
		}
	}

	//演示优选格式
	bchange = FindCtrlName("ComboboxShowMode");
	if ( bchange )
	{
		TTPVidForamt tVidForamt;
		GetShowMode(tVidForamt);
		u16 wRet = COMIFMGRPTR->DualVideoFormatCmd(tVidForamt);
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存演示优选格式请求发送失败" );
			return false;
		}
	}

	//会议讨论
/*	bchange = FindCtrlName("BtnDiscuss");
	if ( bchange )
	{
		bool bUse = false;
		UIFACTORYMGR_PTR->GetSwitchState( "BtnDiscuss", bUse, m_pWndTree );
		u16 wRet = COMIFMGRPTR->ConfDisCmd(bUse);
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存会议讨论设置请求发送失败" );
			return false;
		}
	}
*/
	//会议轮询
/*	bchange = FindCtrlName("BtnPolling");
	bool bEditChange = FindCtrlName("EditPollTime");
	if ( bchange || bEditChange )
	{
		bool bUse = false;
		TTPPollInfo tPollInfo;
		UIFACTORYMGR_PTR->GetSwitchState( "BtnPolling", bUse, m_pWndTree );
		UIFACTORYMGR_PTR->GetCaption( "EditPollTime", strCaption, m_pWndTree );
		u16 wTime = atoi( strCaption.c_str() );
		tPollInfo.wPollExpire = wTime;
		tPollInfo.bIsPoll = (BOOL)bUse;
		u16 wRet = COMIFMGRPTR->ConfPollCmd(tPollInfo);
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存会议轮询设置请求发送失败" );
			return false;
		}
	}
*/
	//音频格式
	bchange = FindCtrlName("ComboboxAudioMode");
	if ( bchange )
	{
		EmTpAudioFormat emAudioFormat = GetAudioFormat();
		u16 wRet = COMIFMGRPTR->AudioFormatCmd(emAudioFormat);
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存音频格式设置请求发送失败" );
			return false;
		}
	}

	//量子加密
	bool bSucceed = SaveEncryptType();
	if (false == bSucceed)
	{
		return false;
	}
	m_vctWndName.clear();

	UpBtnState();
	return true;
}

bool CCfgCallSerLogic::OnBtnCancel( const IArgs& args )
{
	SetVideoFormat();
	SetDualVideoFormat();
	SetCallRate();
	SetDualCallRate();
	SetConfDisState();
	SetConfPollInfo();
	SetAudioFormat();
	SetEncryptType();
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

bool CCfgCallSerLogic::IsCfgCallChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCfgCallSerLogic::SaveMsgBox()
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

bool CCfgCallSerLogic::OnCallModeChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	TTPVidForamt tVidForamt;
	GetCallMode(tVidForamt);
	TTPVidForamt tOldVidForamt;
	LIBDATAMGRPTR->GetVideoFormatInfo(tOldVidForamt);
	if ( tOldVidForamt.emTpVideoResolution != tVidForamt.emTpVideoResolution /*|| tOldVidForamt.emTpVideoQualityLevel != tVidForamt.emTpVideoQualityLevel*/
		|| tOldVidForamt.wVidFrameRate != tVidForamt.wVidFrameRate)
	{
		bChange = true;	
	}
	
	CheckData(m_strCallMode,bChange);
	return true;	
}

bool CCfgCallSerLogic::OnShowModeChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	TTPVidForamt tVidForamt;
	GetShowMode(tVidForamt);
	TTPVidForamt tOldVidForamt;
	LIBDATAMGRPTR->GetDualVideoFormatInfo(tOldVidForamt);
	if ( tOldVidForamt.emTpVideoResolution != tVidForamt.emTpVideoResolution /*|| tOldVidForamt.emTpVideoQualityLevel != tVidForamt.emTpVideoQualityLevel*/
		|| tOldVidForamt.wVidFrameRate != tVidForamt.wVidFrameRate)
	{
		bChange = true;	
	}
	
	CheckData(m_strShowMode,bChange);
	return true;
}

void CCfgCallSerLogic::GetCallMode( TTPVidForamt& tVidForamt ) const
{
	//获取多会场呼叫会议格式
	String strCallMode;
	UIFACTORYMGR_PTR->GetComboText( m_strCallMode, strCallMode, m_pWndTree );

	if ( strCallMode.empty() )
	{
		return;
	}

	tVidForamt = GetMode( strCallMode );
}

void CCfgCallSerLogic::GetShowMode( TTPVidForamt& tVidForamt ) const
{
	//获取多会场呼叫演示格式
	String strShowMode;
	UIFACTORYMGR_PTR->GetComboText( m_strShowMode, strShowMode, m_pWndTree );
	if ( strShowMode.empty() )
	{
		return;
	}

	tVidForamt = GetMode( strShowMode );
}

TTPVidForamt CCfgCallSerLogic::GetMode( String strMode ) const
{
	TTPVidForamt tVidForamt;
// 	if( strMode.find( "HP", 0 ) != string::npos )
// 	{
// 		tVidForamt.emTpVideoQualityLevel = emTPH264HP;
// 	}
// 	else
// 	{
// 		tVidForamt.emTpVideoQualityLevel = emTPH264BP;
// 	}
	if ( strMode.find( "4K", 0 ) != string::npos )
	{
		tVidForamt.emTpVideoResolution = emTPVRes3840x2160;
	} 
	else if ( strMode.find( "1080", 0 ) != string::npos )
	{
		tVidForamt.emTpVideoResolution = emTPVHD1080p1920x1080;
	}
	else if ( strMode.find( "720", 0 ) != string::npos )
	{
		tVidForamt.emTpVideoResolution = emTPVHD720p1280x720;
	}
	else if ( strMode.find( "UXGA", 0 ) != string::npos )
	{
		tVidForamt.emTpVideoResolution = emTPVGA1600x1200;
	} 
	else if ( strMode.find( "SXGA", 0 ) != string::npos )
	{
		tVidForamt.emTpVideoResolution = emTPVGA1280x1024;
	}
	else if ( strMode.find( "WXGA", 0 ) != string::npos )
	{
		tVidForamt.emTpVideoResolution = emTPVGA1280x800;
	}
	else if ( strMode.find( "XGA", 0 ) != string::npos )
	{
		tVidForamt.emTpVideoResolution = emTPVGA1024x768;
	}
	else if ( strMode.find( "4CIF", 0 ) != string::npos )
	{
		tVidForamt.emTpVideoResolution = emTPV4CIF;
	}
	
	if ( strMode.find( "60", 0 ) != string::npos )
	{	
		tVidForamt.wVidFrameRate = 60;
	}
	else if ( strMode.find( "50", 0 ) != string::npos )
	{	
		tVidForamt.wVidFrameRate = 50;
	}
	else if ( strMode.find( "30", 0 ) != string::npos )
	{	
		tVidForamt.wVidFrameRate = 30;
	}
	else if ( strMode.find( "25", 0 ) != string::npos )
	{	
		tVidForamt.wVidFrameRate = 25;
	}
	else if ( strMode.find( "5", 0 ) != string::npos )
	{	
		tVidForamt.wVidFrameRate = 5;
	}
	return tVidForamt;
}

bool CCfgCallSerLogic::OnBtnSwitchDiscuss( const IArgs& args )
{
	BOOL bDis;
	LIBDATAMGRPTR->GetConfDisInfo( bDis );

	bool bUse = false;
    UIFACTORYMGR_PTR->GetSwitchState( "BtnDiscuss", bUse, m_pWndTree );

	bool bChange = false;
	if ( bDis != (BOOL)bUse )
	{
		bChange = true;
	}
	CheckData( "BtnDiscuss", bChange );
	return true;
}

bool CCfgCallSerLogic::OnBtnSwitchPolling( const IArgs& args )
{
	TTPPollInfo tPollInfo;
	LIBDATAMGRPTR->GetConfPollInfo( tPollInfo );

	bool bUse = false;
    UIFACTORYMGR_PTR->GetSwitchState( "BtnPolling", bUse, m_pWndTree );
// 	if ( bUse )
//     {
//         UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree );  
//     }
//     else
//     {   
//         UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree );
//     }
	
	bool bChange = false;
	if ( tPollInfo.bIsPoll != (BOOL)bUse )
	{
		bChange = true;
	}
	CheckData( "BtnPolling", bChange );
	return true;	
}

bool CCfgCallSerLogic::OnPollTimeChange( const IArgs& args )
{
	TTPPollInfo tPollInfo;
	LIBDATAMGRPTR->GetConfPollInfo( tPollInfo );

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "EditPollTime", strCaption, m_pWndTree );
	u16 wVal = atoi( strCaption.c_str() );
// 	if ( wVal > 7200 || wVal < 5 )
// 	{
// 		if ( wVal > 7200 )
// 		{
// 			wVal = 7200;
// 			UIFACTORYMGR_PTR->SetCaption( "EditPollTime", "7200", m_pWndTree);
// 		}
// 		else if ( wVal < 5 )
// 		{
// 			wVal = 5;
// 			UIFACTORYMGR_PTR->SetCaption( "EditPollTime", "5", m_pWndTree);
// 		}	
// 		UIFACTORYMGR_PTR->SetEditFocusEnd( "EditPollTime", m_pWndTree ); 
// 	}

	bool bChange = false;
	if ( tPollInfo.wPollExpire != wVal )
	{
		bChange = true;
	}
	CheckData( "EditPollTime", bChange );
	return true;
}

bool CCfgCallSerLogic::OnConfRateChange( const IArgs& args )
{
	u16 wCallRate;
	LIBDATAMGRPTR->GetCallRateInfo( wCallRate );
	
 	String strCaption;
 	UIFACTORYMGR_PTR->GetComboText( "ComboboxConfRate", strCaption, m_pWndTree );
 	u32 nVal = atoi( strCaption.c_str() );
	if ( nVal > 8192 )
	{
		nVal = 8192;
	}

	s8 chVal[5] = { 0 };
	itoa( nVal, chVal,10 );
	if ( !strCaption.empty() )
	{
		UIFACTORYMGR_PTR->SetComboText( "ComboboxConfRate", chVal, m_pWndTree );
		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( "ComboboxConfRate", m_pWndTree );
		if ( CTransparentComboBox* pCWnd = ( CTransparentComboBox* )pWnd )
		{
			if( CTransparentEdit* pEdit = pCWnd->GetEditPoint() )
			{
				pEdit->SetSel( -1 );
			}
		}
	}
	
	bool bChange = false;
	if ( wCallRate != nVal )
	{
		bChange = true;
	}
	CheckData( "ComboboxConfRate", bChange );

	return true;
}

bool CCfgCallSerLogic::OnShowRateChange( const IArgs& args )
{
	u16 wShowRate;
	LIBDATAMGRPTR->GetDualCallRateInfo( wShowRate );
	
	String strCaption;
	UIFACTORYMGR_PTR->GetComboText( "ComboboxShowRate", strCaption, m_pWndTree );
	u32 nVal = atoi( strCaption.c_str() );

	if ( nVal > 8192 )
	{
		nVal = 8192;
	}

	s8 chVal[5] = { 0 };
	itoa( nVal, chVal,10 );
	if ( !strCaption.empty() )
	{
		UIFACTORYMGR_PTR->SetComboText( "ComboboxShowRate", chVal, m_pWndTree );
		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( "ComboboxShowRate", m_pWndTree );
		if ( CTransparentComboBox* pCWnd = ( CTransparentComboBox* )pWnd )
		{
			if( CTransparentEdit* pEdit = pCWnd->GetEditPoint() )
			{
				pEdit->SetSel( -1 );
			}
		}
	}

	bool bChange = false;
	if ( wShowRate != nVal )
	{
		bChange = true;
	}
	CheckData( "ComboboxShowRate", bChange );
	return true;
}

bool CCfgCallSerLogic::OnConfRateNoFocus( const IArgs& args )
{
	// 	HWND hWnd = GetActiveWindow();
	// 	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_strMainFrame );
	// 	HWND hWnd2 = pWnd->GetSafeHwnd();
	// 	if ( hWnd != hWnd2 )
	// 	{
	// 		return false;
	// 	}
	//单屏码率64~8192
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	if( pMsg != NULL )
	{
		Window* pNewWnd = (Window*)pMsg->m_Msg.lParam;
		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( "BtnCancle", m_pWndTree );
		
		if( pWnd != pNewWnd )
		{
			String strCaption;
			UIFACTORYMGR_PTR->GetComboText( "ComboboxConfRate", strCaption, m_pWndTree );
			u32 nVal = atoi( strCaption.c_str() );
			u16 wValue = nVal%64;
			if ( wValue != 0 && nVal <= 8192 && nVal > 64 )
			{
				MSG_BOX_OK("码率必须为64的倍数");
				if ( wValue <= 32 )
				{
					nVal -= wValue;
				}
				else
				{
					nVal += 64 - wValue;
				}
			}
			else if ( nVal < 64 )
			{
				MSG_BOX_OK("单屏码率必须为64～8192间的整数");
				nVal = 64;
			}
			s8 chCaption[8] = {0};
			itoa( nVal, chCaption, 10 );
			UIFACTORYMGR_PTR->SetComboText( "ComboboxConfRate", chCaption, m_pWndTree);
			
			u16 wCallRate;
			LIBDATAMGRPTR->GetCallRateInfo( wCallRate );
			bool bChange = false;
			if ( wCallRate != nVal )
			{
				bChange = true;
			}
			CheckData( "ComboboxConfRate", bChange );
		}
		else
		{
			return false;
		}
	}
	
	return true;
}

bool CCfgCallSerLogic::OnShowRateNoFocus( const IArgs& args )
{
// 	HWND hWnd = GetActiveWindow();
// 	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_strMainFrame );
// 	HWND hWnd2 = pWnd->GetSafeHwnd();
// 	if ( hWnd != hWnd2 )
// 	{
// 		return false;
// 	}
	//演示码率0~8192

	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));

	if( pMsg != NULL )
	{
		Window* pNewWnd = (Window*)pMsg->m_Msg.lParam;
		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( "BtnCancle", m_pWndTree );

		if( pWnd != pNewWnd )
		{
			String strCaption;
			UIFACTORYMGR_PTR->GetComboText( "ComboboxShowRate", strCaption, m_pWndTree );
			u32 nVal = atoi( strCaption.c_str() );
			u16 wValue = nVal%64;
			if ( wValue != 0 && nVal <= 8192 )
			{
				MSG_BOX_OK("码率必须为64的倍数");
				if ( wValue <= 32 )
				{
					nVal -= wValue;
				}
				else
				{
					nVal += 64 - wValue;
				}
			}
			s8 chCaption[8] = {0};
			itoa( nVal, chCaption, 10 );
			UIFACTORYMGR_PTR->SetComboText( "ComboboxShowRate", chCaption, m_pWndTree);
			
			u16 wShowRate;
			LIBDATAMGRPTR->GetDualCallRateInfo( wShowRate );
			bool bChange = false;
			if ( wShowRate != nVal )
			{
				bChange = true;
			}
			CheckData( "ComboboxShowRate", bChange );
		}
		else
		{
			return false;
		}
	}
	
	return true;
}

bool CCfgCallSerLogic::OnShowQuantumErpChange(const IArgs& args)
{
	String strCaption;
	UIFACTORYMGR_PTR->GetComboText( m_strShowQuantumErp, strCaption, m_pWndTree );
	EmQtEncryptFrequency emQtEncryptFrenquency;

	if( strCaption == "一秒一密" )
	{
		emQtEncryptFrenquency = emQtFrequencyEverySeconds;
	}
	else if( strCaption == "一分一密" )
	{
		emQtEncryptFrenquency = emQtFrequencyEveryMinutes;
	}
	else
	{
		emQtEncryptFrenquency = emQtFrequencyEveryConf;
	}


	bool bChange = false;
	if( emQtEncryptFrenquency != m_tEncryptKey.emQtKeyFrequency )
	{
		bChange = true;
	}

	CheckData( "QtKeyFrequency", bChange );

	return true;
}

bool CCfgCallSerLogic::OnShowQuantumErpNoFocus(const IArgs& args)
{
	String strCaption;
	UIFACTORYMGR_PTR->GetComboText( m_strShowQuantumErp, strCaption, m_pWndTree );
	EmQtEncryptFrequency emQtEncryptFrenquency;
	
	if( strCaption == "一秒一密" )
	{
		emQtEncryptFrenquency = emQtFrequencyEverySeconds;
	}
	else if( strCaption == "一分一密" )
	{
		emQtEncryptFrenquency = emQtFrequencyEveryMinutes;
	}
	else
	{
		emQtEncryptFrenquency = emQtFrequencyEveryConf;
	}
	
	
	bool bChange = false;
	if( emQtEncryptFrenquency != m_tEncryptKey.emQtKeyFrequency )
	{
		bChange = true;
	}
	
	CheckData( "QtKeyFrequency", bChange );

	return true;
}

HRESULT CCfgCallSerLogic::OnUpdateVideoFormat( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetVideoFormat();
	return S_OK;
}

void CCfgCallSerLogic::SetVideoFormat()
{
	TTPVidForamt tVidForamt;
	LIBDATAMGRPTR->GetVideoFormatInfo(tVidForamt);
	SetFormat( tVidForamt, m_strCallMode );
}

HRESULT CCfgCallSerLogic::OnUpdateDualVideoFormat( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetDualVideoFormat();
	return S_OK;
}

void CCfgCallSerLogic::SetDualVideoFormat()
{
	TTPVidForamt tDualVidForamt;
	LIBDATAMGRPTR->GetDualVideoFormatInfo(tDualVidForamt);
	SetFormat( tDualVidForamt, m_strShowMode );
}

HRESULT CCfgCallSerLogic::OnUpdateCallRate( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetCallRate();
	return S_OK;	
}

void CCfgCallSerLogic::SetCallRate()
{
	u16 wCallRate;
	LIBDATAMGRPTR->GetCallRateInfo( wCallRate );
	s8 chCallRate[8] = {0};
	sprintf( chCallRate, "%u", wCallRate );
	
	UIFACTORYMGR_PTR->SetComboText( "ComboboxConfRate", chCallRate, m_pWndTree );
}

HRESULT CCfgCallSerLogic::OnUpdateDualCallRate( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetDualCallRate();
	return S_OK;	
}

void CCfgCallSerLogic::SetDualCallRate()
{
	u16 wDualCallRate;
	LIBDATAMGRPTR->GetDualCallRateInfo( wDualCallRate );
	s8 chDualCallRate[8] = {0};
	sprintf( chDualCallRate, "%u", wDualCallRate );
	
	UIFACTORYMGR_PTR->SetComboText( "ComboboxShowRate", chDualCallRate, m_pWndTree );
}

HRESULT CCfgCallSerLogic::OnUpdateConfDis( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetConfDisState();
	return S_OK;	
}

void CCfgCallSerLogic::SetConfDisState()
{
	BOOL bDis;
	LIBDATAMGRPTR->GetConfDisInfo( bDis );
	UIFACTORYMGR_PTR->SetSwitchState( "BtnDiscuss", bDis, m_pWndTree );
}

HRESULT CCfgCallSerLogic::OnUpdateConfPoll( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetConfPollInfo();
	return S_OK;	
}

void CCfgCallSerLogic::SetConfPollInfo()
{
	TTPPollInfo tPollInfo;
	LIBDATAMGRPTR->GetConfPollInfo( tPollInfo );
	
	s8 chPollTime[8] = {0};
	sprintf( chPollTime, "%u", tPollInfo.wPollExpire );
	UIFACTORYMGR_PTR->SetCaption( "EditPollTime", chPollTime, m_pWndTree);
	
	UIFACTORYMGR_PTR->SetSwitchState( "BtnPolling", tPollInfo.bIsPoll, m_pWndTree );
// 	if ( tPollInfo.bIsPoll )
//     {
// 		BOOL bInConf = LIBDATAMGRPTR->IsInConf();
// 		if ( !bInConf )
// 		{
// 			UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree ); 
// 		}
//     }
//     else
//     {   
//         UIFACTORYMGR_PTR->LoadScheme( "SchmNormal",  m_pWndTree );
//     }
}

void CCfgCallSerLogic::SetFormat( TTPVidForamt& tVidForamt, String strControl )
{	
	CString strFormat = "";
// 	if ( emTPH264HP == tVidForamt.emTpVideoQualityLevel )
// 	{
// 		strFormat = "H.264 HP";
// 	}
// 	else
// 	{
// 		strFormat = "H.264 BP";
// 	}
	if ( emTPVRes3840x2160 == tVidForamt.emTpVideoResolution )
	{
		strFormat = "4K@";
	} 
	else if ( emTPVHD1080p1920x1080 == tVidForamt.emTpVideoResolution )
	{
		strFormat = "1080P@";
	} 
	else if ( emTPVHD720p1280x720 == tVidForamt.emTpVideoResolution )
	{
		strFormat = "720P@";
	}
	else if ( emTPVGA1600x1200 == tVidForamt.emTpVideoResolution )
	{
		strFormat = "UXGA@";			
	}
	else if ( emTPVGA1024x768 == tVidForamt.emTpVideoResolution )
	{
		strFormat = "XGA@";		
	}
	else if ( emTPVGA1280x768 == tVidForamt.emTpVideoResolution || emTPVGA1280x800 == tVidForamt.emTpVideoResolution || emTPVGA1366x768 == tVidForamt.emTpVideoResolution )
	{
		strFormat = "WXGA@";
	}
	else if ( emTPVGA1280x1024 == tVidForamt.emTpVideoResolution )
	{
		strFormat = "SXGA@";
	}
	else if ( emTPV4CIF == tVidForamt.emTpVideoResolution )
	{
		strFormat = "4CIF@";
	}

    //非规格内的分辨率格式，不再处理
    if ( strFormat == "" )
    {
        char chVidRes[3];
        memset( chVidRes, 0, 3 );
        itoa( tVidForamt.emTpVideoResolution, chVidRes, 10 );

        CString strDispInfo = "优选格式非规格分辨率：";
        strDispInfo += chVidRes;
        WARNMESSAGE( strDispInfo );
        return;
    }

	if ( 60 == tVidForamt.wVidFrameRate )
	{
		strFormat += "60fps";
	} 
	else if ( 50 == tVidForamt.wVidFrameRate )
	{
		strFormat += "50fps";
	}
	else if ( 30 == tVidForamt.wVidFrameRate )
	{
		strFormat += "30fps";
	}
	else if ( 25 == tVidForamt.wVidFrameRate )
	{
		strFormat += "25fps";
	}
	else if ( 5 == tVidForamt.wVidFrameRate )
	{
		strFormat += "5fps";
	}

	UIFACTORYMGR_PTR->SetComboText( strControl, strFormat.GetBuffer(strFormat.GetLength()), m_pWndTree );
}

HRESULT CCfgCallSerLogic::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 && m_pWndTree != NULL )
	{
		return S_FALSE;
	}
	bool bUse = false;
    UIFACTORYMGR_PTR->GetSwitchState( "BtnPolling", bUse, m_pWndTree );
	
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree );
// 		if ( bUse )
// 		{
			UIFACTORYMGR_PTR->EnableWindow( "EditPollTime", false, m_pWndTree );
//		}
	} 
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree );
// 		if ( bUse )
// 		{
			UIFACTORYMGR_PTR->EnableWindow( "EditPollTime", true, m_pWndTree );
// 		}
// 		else
// 		{
// 			UIFACTORYMGR_PTR->EnableWindow( "EditPollTime", false, m_pWndTree );
// 		}
	}
	return S_OK;
}

bool CCfgCallSerLogic::OnAudioModeChange( const IArgs& args )
{
	EmTpAudioFormat emAudioFormat, emLibAudioFormat;
	emAudioFormat = GetAudioFormat();
	emLibAudioFormat = LIBDATAMGRPTR->GetAudioFormatInfo();	
 
	bool bChange = false;
	if ( emAudioFormat != emLibAudioFormat )
	{
		bChange = true;
	}
	CheckData( "ComboboxAudioMode", bChange );
	
	return true;
}

HRESULT CCfgCallSerLogic::OnUpdateAudioFormat( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}

	SetAudioFormat();
	return S_OK;
}

LRESULT CCfgCallSerLogic::OnEncryptInfoNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	BOOL bSuccess = *(BOOL*)wparam;
	if ( bSuccess == TRUE )
	{
		m_tEncryptKey = *(TTpEncryptKey * )lparam;
	}
	else
	{
		WARNMESSAGE("选择加密类型设置失败");
	}
	
	SetEncryptType();
	return S_OK;
}

void CCfgCallSerLogic::SetAudioFormat()
{
	EmTpAudioFormat emAudioFormat;
	emAudioFormat = LIBDATAMGRPTR->GetAudioFormatInfo();

	CString strFormat = "";
	switch ( emAudioFormat )
	{
	case emTPAMpegAACLD:
		{
			strFormat += "MPEG4 AAC-LD单声道";
			break;
		}
	case emTPAG711a:
		{
			strFormat += "G.711A";
			break;
		}
	case emTPAG711u:
		{
			strFormat += "G.711U";
			break;
		}
	case emTPAG719:
		{
			strFormat += "G.719";
			break;
		}
	case emTPAG7221:
		{
			strFormat += "G.722.1 Annex C Polycom Siren14";
			break;
		}
	case emTPAMP3:
		{
			strFormat += "MP3";
			break;
		}
	case emTPAMpegAACLC:
		{
			strFormat += "MPEG4 AAC-LC单声道";
			break;
		}
	default:
		break;
	}

	UIFACTORYMGR_PTR->SetComboText( "ComboboxAudioMode", strFormat.GetBuffer(strFormat.GetLength()), m_pWndTree );
}

EmTpAudioFormat CCfgCallSerLogic::GetAudioFormat()
{
	String strCaption;
	UIFACTORYMGR_PTR->GetComboText( "ComboboxAudioMode", strCaption, m_pWndTree );
	
	EmTpAudioFormat emAudioFormat;
	if ( strCaption.find( "G.711A", 0 ) != string::npos )
	{
		emAudioFormat = emTPAG711a;
	} 
	else if ( strCaption.find( "G.711U", 0 ) != string::npos )
	{
		emAudioFormat = emTPAG711u;
	}
	else if ( strCaption.find( "G.719", 0 ) != string::npos )
	{
		emAudioFormat = emTPAG719;
	}
	else if ( strCaption.find( "G.722.1", 0 ) != string::npos )
	{
		emAudioFormat = emTPAG7221;
	}
	else if ( strCaption.find( "MP3", 0 ) != string::npos )
	{
		emAudioFormat = emTPAMP3;
	}
	else if ( strCaption.find( "MPEG4 AAC-LC", 0 ) != string::npos )
	{
		emAudioFormat = emTPAMpegAACLC;
	}
	else if ( strCaption.find( "MPEG4 AAC-LD", 0 ) != string::npos )
	{
		emAudioFormat = emTPAMpegAACLD;
	}

	return emAudioFormat;
}

bool CCfgCallSerLogic::SaveEncryptType()
{
	bool bAesState = false;
	bool bchange = false;
	TTpEncryptKey tPEncryptType = m_tEncryptKey;
	
	s32  nCheckState1;
	UIFACTORYMGR_PTR->GetCheckState( m_strNoEncrptyPort, nCheckState1, m_pWndTree );
	s32  nCheckState2;
	UIFACTORYMGR_PTR->GetCheckState( m_strAESEncrptyPort, nCheckState2, m_pWndTree );
	s32  nCheckState3;
	UIFACTORYMGR_PTR->GetCheckState( m_strQuantumErpPort, nCheckState3, m_pWndTree );

	if( 1 == nCheckState1 )
	{
		tPEncryptType.emTPEncryptType = emTPEncryptTypeNone;
	}
	else if( 1 == nCheckState2 )
	{
		tPEncryptType.emTPEncryptType = emTPEncryptTypeAES;
	}
	else
	{
		tPEncryptType.emTPEncryptType = emTPEncryptTypeQt;

		String strCaption;
		UIFACTORYMGR_PTR->GetComboText( m_strShowQuantumErp, strCaption, m_pWndTree );
		
		if( strCaption == "一秒一密" )
		{
			tPEncryptType.emQtKeyFrequency = emQtFrequencyEverySeconds;
		}
		else if( strCaption == "一分一密" )
		{
			tPEncryptType.emQtKeyFrequency = emQtFrequencyEveryMinutes;
		}
		else
		{
			tPEncryptType.emQtKeyFrequency = emQtFrequencyEveryConf;
		}
	}

	if ( (m_tEncryptKey.emTPEncryptType != tPEncryptType.emTPEncryptType) || ( m_tEncryptKey.emQtKeyFrequency != tPEncryptType.emQtKeyFrequency ) )
	{
		u16 wRet = COMIFMGRPTR->SetAesEncrypCmd(tPEncryptType);
		if ( wRet != NO_ERROR )
		{
			WARNMESSAGE("选择加密类型消息发送失败");
			return false;
		}
	}
	
	return true;
}

void CCfgCallSerLogic::SetEncryptType()
{
	if( m_tEncryptKey.emTPEncryptType == emTPEncryptTypeNone )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strNoEncrptyPort, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strAESEncrptyPort, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strQuantumErpPort, 0, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoQuantumErp", m_pWndTree );
	}
	else if( m_tEncryptKey.emTPEncryptType == emTPEncryptTypeAES )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strNoEncrptyPort, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strAESEncrptyPort, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strQuantumErpPort, 0, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoQuantumErp", m_pWndTree );
	}
	else if( m_tEncryptKey.emTPEncryptType == emTPEncryptTypeQt )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strNoEncrptyPort, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strAESEncrptyPort, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strQuantumErpPort, 1, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmQuantumErp", m_pWndTree );
		if( m_tEncryptKey.emQtKeyFrequency == emQtFrequencyEverySeconds )
		{
			UIFACTORYMGR_PTR->SetComboText( m_strShowQuantumErp, "一秒一密", m_pWndTree );
		}
		else if( m_tEncryptKey.emQtKeyFrequency == emQtFrequencyEveryMinutes )
		{
			UIFACTORYMGR_PTR->SetComboText( m_strShowQuantumErp, "一分一密", m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->SetComboText( m_strShowQuantumErp, "一会一密", m_pWndTree );
		}
	}
	else
	{
		
	}
}

bool CCfgCallSerLogic::OnSelEncrptyStyle(const IArgs& args)
{
	EmTPEncryptType emTPEncryptType;
	s32  nCheckState1;
	UIFACTORYMGR_PTR->GetCheckState( m_strNoEncrptyPort, nCheckState1, m_pWndTree );
	s32  nCheckState2;
	UIFACTORYMGR_PTR->GetCheckState( m_strAESEncrptyPort, nCheckState2, m_pWndTree );
	s32  nCheckState3;
	UIFACTORYMGR_PTR->GetCheckState( m_strQuantumErpPort, nCheckState3, m_pWndTree );

	if( nCheckState1 == 1 )
	{
		emTPEncryptType = emTPEncryptTypeNone;
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoQuantumErp", m_pWndTree );
	}
	else if( nCheckState2 == 1 )
	{
		emTPEncryptType = emTPEncryptTypeAES;
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoQuantumErp", m_pWndTree );
    }
	else
	{
		emTPEncryptType = emTPEncryptTypeQt;
		UIFACTORYMGR_PTR->LoadScheme( "SchmQuantumErp", m_pWndTree );
	}

	bool bChange = false;
	if( emTPEncryptType == m_tEncryptKey.emTPEncryptType )
	{
		bChange = false;
	}
	else 
	{
		bChange = true;
	}

	CheckData( "EncryptType", bChange );

	return true;
}
