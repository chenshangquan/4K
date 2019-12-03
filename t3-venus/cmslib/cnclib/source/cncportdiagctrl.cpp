#include "StdAfx.h"
#include "cncportdiagctrl.h"

CCncPortDiagCtrl::CCncPortDiagCtrl(CCnsSession &cSession)
:CCncPortDiagCtrlIF()
{
	m_bWhiteNoise[0]= FALSE;
	m_bWhiteNoise[1]= FALSE;
	m_bWhiteNoise[2]= FALSE;
	m_pSession = &cSession;
    m_emCnModel = emUnknownCnModel;
	BuildEventsMap();
}

CCncPortDiagCtrl::~CCncPortDiagCtrl()
{
	
}

void CCncPortDiagCtrl::BuildEventsMap()
{
	REG_PFUN( ev_tppSetAudioPort_Ind, CCncPortDiagCtrl::OnAudioPortInfoInd );
	REG_PFUN( ev_CnSetDesktopMicInfo_Nty, CCncPortDiagCtrl::OnSetDesktopMicInfoNty );
	REG_PFUN( ev_CnSetDesktopMicInfo_Ind, CCncPortDiagCtrl::OnSetDesktopMicInfoInd );
	REG_PFUN( ev_tppSetMic10Info_Ind, CCncPortDiagCtrl::OnSetMic10InfoInd );
	REG_PFUN( ev_tppAudioRestoreDefaults_Ind, CCncPortDiagCtrl::OnDefaultAudPortInd );
	REG_PFUN( ev_tppGetLostPacketInfo_Rsp, CCncPortDiagCtrl::OnLostPacketInfoRsp );
	REG_PFUN( ev_tppGetUpDownstreamRate_Nty, CCncPortDiagCtrl::OnUpDownstreamRateNty );
	REG_PFUN( ev_tppSelAVMatrixProject_Ind, CCncPortDiagCtrl::OnAVMatrixInfoInd );
	REG_PFUN( ev_tppGetTPadIpList_Rsp, CCncPortDiagCtrl::OnTpadListRsp );
	REG_PFUN( ev_tppGetTPadIpList_Nty, CCncPortDiagCtrl::OnTpadListNty );
//	REG_PFUN( ev_tppSetAudiotMixer_Ind, CCncPortDiagCtrl::OnAudiotMixerInd );
	REG_PFUN( ev_tppMixRestoreDefaults_Ind, CCncPortDiagCtrl::OnDefaulttMixerInd );	
	REG_PFUN( ev_tppSetAudioEqualizer_Ind, CCncPortDiagCtrl::OnAudioEqualizerInd );
	REG_PFUN( ev_tppEqualizerReDefaults_Ind, CCncPortDiagCtrl::OnDefaultEqInd );
	REG_PFUN( ev_tppUpdate_Ind, CCncPortDiagCtrl::OnUpgradeCnsInd );
	REG_PFUN( ev_tppSetCallServerInfo_Ind, CCncPortDiagCtrl::OnCallServerInd );
	REG_PFUN( ev_tppSetCallServerInfo_Nty, CCncPortDiagCtrl::OnCallServerNty );
	REG_PFUN( ev_tppSetUpgradeServerInfo_Ind, CCncPortDiagCtrl::OnUpgradeSerInd );
	REG_PFUN( ev_tppSetUpgradeServerInfo_Nty, CCncPortDiagCtrl::OnUpgradeSerNty );
	REG_PFUN( ev_tppStopAVMatrixProject_Rsp, CCncPortDiagCtrl::OnStopAVMatrixRsp );
	REG_PFUN( ev_CnCfgVideoFormat_Ind, CCncPortDiagCtrl::OnVideoFormatInd );
	REG_PFUN( ev_CnCfgDualVideoFormat_Ind, CCncPortDiagCtrl::OnDualVideoFormatInd );
	REG_PFUN( ev_CnCfgCallRate_Ind, CCncPortDiagCtrl::OnCallRateInd );	
	REG_PFUN( ev_CnCfgDualCallRate_Ind, CCncPortDiagCtrl::OnDualCallRateInd );
	REG_PFUN( ev_CnVerInfo_Nty, CCncPortDiagCtrl::OnVerInfoNty );
	REG_PFUN( ev_CnCfgConfDis_Ind, CCncPortDiagCtrl::OnConfDisInd );
	REG_PFUN( ev_CnCfgConfPoll_Ind, CCncPortDiagCtrl::OnConfPollInd );
	REG_PFUN( ev_CnCfgAudioFormat_Ind, CCncPortDiagCtrl::OnAudioFormatInd );
	//数据会议服务器告知
	REG_PFUN( ev_tppSetDataServerInfo_Nty, CCncPortDiagCtrl::OnWBServerNty );
	REG_PFUN( ev_tppSetDataServerInfo_Ind, CCncPortDiagCtrl::OnWBServerInd );
	//矩阵服务器通知
	REG_PFUN( ev_CnSetMatrixServerInfo_Nty, CCncPortDiagCtrl::OnSetMatrixServerInfoNty );
	REG_PFUN( ev_CnSetMatrixServerInfo_Ind, CCncPortDiagCtrl::OnSetMatrixServerInfoInd );
	//量子加密服务器通知
	REG_PFUN( ev_tppSetQtEncryptInfo_Nty, CCncPortDiagCtrl::OnSetQtEntryptInfoNty);
	REG_PFUN( ev_tppSetQtEncryptInfo_Ind, CCncPortDiagCtrl::OnSetQtEncryptInfoInd);

	//时间同步服务器通知
	REG_PFUN( ev_tppSetNtpServerInfo_Nty, CCncPortDiagCtrl::OnSetNtpServerInfoNty);
	REG_PFUN( ev_tppSetNtpServerInfo_Ind, CCncPortDiagCtrl::OnSetNtpServerInfoInd);

	//网络安全
	REG_PFUN( ev_CnFtpInfo_Nty, CCncPortDiagCtrl::OnSetFtpInfoNty);
	REG_PFUN( ev_CnSetFtp_Rsp, CCncPortDiagCtrl::OnSetFtpRsp);
	REG_PFUN( ev_CnTelnetInfo_Nty, CCncPortDiagCtrl::OnSetTelnetInfoNty);	
	REG_PFUN( ev_CnSetTelnet_Rsp, CCncPortDiagCtrl::OnSetTelnetRsp);
	
	REG_PFUN( OSP_DISCONNECT, CCncPortDiagCtrl::OnLinkBreak );

	//音频配置
	REG_PFUN( ev_CnSetAudioInfo_Ind, CCncPortDiagCtrl::OnAudioInfoInd);
	REG_PFUN( ev_CnSetDefaultAudioInfo_Ind, CCncPortDiagCtrl::OnDefaultAudioSetInd);
	REG_PFUN( ev_CnWhiteNoise_Rsp, CCncPortDiagCtrl::OnAudioWhiteNoiseRsp );
	REG_PFUN( ev_WhiteNoiseRate_Notify, CCncPortDiagCtrl::OnUpdateWhiteNoise );
	REG_PFUN( ev_TppSetMixType_Ind, CCncPortDiagCtrl::OnSetMixTypeInd);
	REG_PFUN( ev_TppSetLocalAudExtend_Ind, CCncPortDiagCtrl::OnSetAUX2InfoInd);
	//主视频配置
	REG_PFUN( ev_CnSetVedioInfoTool_Ind, CCncPortDiagCtrl::OnVedioSourceInd);
	REG_PFUN( ev_CnSetDefVedioInfoTool_Ind, CCncPortDiagCtrl::OnDefaultMainAudioInd);
	REG_PFUN( ev_tppSetSnapShotInd, CCncPortDiagCtrl::OnSnapShotInd);
	//演示源配置
	REG_PFUN( ev_CnSetDisplaySourceTool_Ind, CCncPortDiagCtrl::OnDisplaySourceInd);
	REG_PFUN( ev_CnSetDefDisplaySrcTool_Ind, CCncPortDiagCtrl::OnDefaultDisplaySourceInd);
	//图像参数调节
	REG_PFUN( ev_CnSetImageAdjust_Ind, CCncPortDiagCtrl::OnImageAdjustInd);
	REG_PFUN( ev_CnSetDefaultImageAdjust_Ind, CCncPortDiagCtrl::OnDefaultImageAdjustInd);

	//路由配置	
	REG_PFUN( ev_tppRouteInfo_Nty, CCncPortDiagCtrl::OnSetRouteInfoNty);
	REG_PFUN( ev_tppAddRoute_Ind, CCncPortDiagCtrl::OnAddRouteInfoInd);
	REG_PFUN( ev_tppDelRoute_Ind, CCncPortDiagCtrl::OnDelRouteInfoInd);
}

void CCncPortDiagCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN( CCncPortDiagCtrl, cMsg);
}

void CCncPortDiagCtrl::OnTimeOut(u16 wEvent)
{

}
		
void CCncPortDiagCtrl::OnLinkBreak(const CMessage& cMsg)
{
	memset( m_aAudioMixerInfo, 0, sizeof(m_aAudioMixerInfo) );	
	memset( m_atAudioPortInfo, 0, sizeof(m_atAudioPortInfo) );
	memset( &m_tAudioDiagInfo, 0, sizeof(m_tAudioDiagInfo) );
	memset( &m_tVideoDiagInfo, 0, sizeof(m_tVideoDiagInfo) );
    memset( &m_tTPadList, 0, sizeof(m_tTPadList) );
	memset( &m_tUpDownSpeedInfo, 0, sizeof(m_tUpDownSpeedInfo) );
	memset( &m_atEqualizer, 0, sizeof(m_atEqualizer) );
	memset( &m_tCallSerInfo, 0, sizeof(m_tCallSerInfo) );
	memset( &m_tUpgradeSer, 0, sizeof(m_tUpgradeSer) );
	memset( &m_tDualVidForamt, 0, sizeof(m_tDualVidForamt) );
	memset( &m_tVidForamt, 0, sizeof(m_tVidForamt) );
	memset( &m_tPollInfo, 0, sizeof(m_tPollInfo) );
    memset( &m_tWBSerIp, 0, sizeof(m_tWBSerIp) );
	memset( &m_tMatrixServerInfo, 0, sizeof(m_tMatrixServerInfo));
	memset( &m_tTpQtEncryptCfg, 0, sizeof(m_tTpQtEncryptCfg) );

	memset( &m_tAudioSetInfo, 0, sizeof(m_tAudioSetInfo) );
	memset( &m_tVideoSource, 0 , sizeof( m_tVideoSource ));
	memset( &m_tTPFtpInfo, 0, sizeof( m_tTPFtpInfo ));
	memset( &m_tTPTelnetInfo, 0, sizeof( m_tTPTelnetInfo ));
	m_vecTRouteCfg.clear();
	m_strLostPacketInfo.Empty();
    m_emCnModel = emUnknownCnModel;

    PrtMsg( OSP_DISCONNECT, emEventTypecnstoolRecv,"[CCncPortDiagCtrl::OnLinkBreak]清空配置信息" );
}

//音频接口配置
u16 CCncPortDiagCtrl::SetAudioPortInfoCmd( const TTpAudioPortInfo** atAudioPortInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );

    pcTpMsg->SetEvent( ev_tppSetAudioPort_Cmd );
	pcTpMsg->SetBody( *atAudioPortInfo, sizeof(TTpAudioPortInfo) );
	pcTpMsg->CatBody( (*atAudioPortInfo)+1, sizeof(TTpAudioPortInfo) );
	pcTpMsg->CatBody( (*atAudioPortInfo)+2, sizeof(TTpAudioPortInfo) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_tppSetAudioPort_Cmd, emEventTypecnstoolSend, "SetAudioPortInfoCmd" );
	
	return wRet;
}

u16 CCncPortDiagCtrl::SetMic10InfoCmd(const TTpMic10Info &tTPMic10Info)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_tppSetMic10Info_Cmd );
	pcTpMsg->SetBody( &tTPMic10Info, sizeof( TTpMic10Info ));

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	PrtMsg( ev_tppSetMic10Info_Cmd, emEventTypecnstoolSend, "m_emGroupIndex: %d, m_bAudioPort: %d", tTPMic10Info.m_emGroupIndex, tTPMic10Info.m_bAudioPort );

	return wRet;
}

u16 CCncPortDiagCtrl::SetNoDeskAudioCmd(bool bNoDeskAudio)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnSetDesktopMicInfo_Cmd );
	pcTpMsg->SetBody( &bNoDeskAudio, sizeof(bool));

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetDesktopMicInfo_Cmd, emEventTypecnstoolSend, "SetNodeskMicCmd: %d",  bNoDeskAudio );

	return 0;
}

s8* CCncPortDiagCtrl::GetSoftVersionInfo()
{
	return m_achVerInfo;
}

EmCnModel CCncPortDiagCtrl::GetEmCnModelInfo()
{
	return m_emCnModel;
}

TTpAudioPortInfo* CCncPortDiagCtrl::GetAudioPortInfo()
{
	return m_atAudioPortInfo;
}

void CCncPortDiagCtrl::OnAudioPortInfoInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + 3 * sizeof(TTpAudioPortInfo) );
	if ( bSuccess )
	{
		memset( &m_atAudioPortInfo, 0, sizeof(m_atAudioPortInfo) );
		for ( int i = 0; i < 3; i++ )
		{
			TTpAudioPortInfo tAudioPortInfo = *(TTpAudioPortInfo*)( cTpMsg.GetBody() + i * sizeof(TTpAudioPortInfo) );
			m_atAudioPortInfo[i] = tAudioPortInfo;
		}
	}
	PrtMsg( ev_tppSetAudioPort_Ind, emEventTypecnstoolRecv, "AudioPortInfoInd:%d", bSuccess );

	PostEvent( UI_CNSTOOL_MSG_AudPort_NTY, 0, (LPARAM)&bSuccess );
}

void CCncPortDiagCtrl::OnSetDesktopMicInfoNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	BOOL bSetDesktopMic = *(BOOL*)cTpMsg.GetBody();
	
	PrtMsg( ev_CnSetDesktopMicInfo_Nty, emEventTypecnstoolRecv, "DesktopMic:%d", bSetDesktopMic );

	PostEvent( UI_CNSTOOL_SETDESKTOPMIC_NTY, 0, (LPARAM)&bSetDesktopMic);
}

void CCncPortDiagCtrl::OnSetDesktopMicInfoInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	BOOL bSetDesktopMic = *(BOOL*)cTpMsg.GetBody();
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(BOOL) );

	PrtMsg( ev_CnSetDesktopMicInfo_Ind, emEventTypecnstoolRecv, "DesktopMic:%d, bSuccess: %d", bSetDesktopMic, bSuccess );

	PostEvent( UI_CNSTOOL_SETDESKTOPMIC_IND, (WPARAM)&bSuccess, (LPARAM)&bSetDesktopMic);
}

void CCncPortDiagCtrl::OnSetMic10InfoInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	m_tTpMic10Info = *(TTpMic10Info*)cTpMsg.GetBody();
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTpMic10Info) );

	PrtMsg( ev_tppSetMic10Info_Ind, emEventTypecnstoolRecv, "m_emGroupIndex: %d, m_bAudioPort: %d, bSuccess: %d ", m_tTpMic10Info.m_emGroupIndex, m_tTpMic10Info.m_bAudioPort, bSuccess );
	
	PostEvent( UI_CNSTOOL_SETMIC10INFO_IND, (WPARAM)&bSuccess, (LPARAM)&m_tTpMic10Info);
}

u16 CCncPortDiagCtrl::DefaultAudioPortCmd( const TTpAudioPortInfo** atAudioPortInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tppAudioRestoreDefaults_Cmd );
	pcTpMsg->SetBody( *atAudioPortInfo, sizeof(TTpAudioPortInfo) );
	pcTpMsg->CatBody( (*atAudioPortInfo)+1, sizeof(TTpAudioPortInfo) );
	pcTpMsg->CatBody( (*atAudioPortInfo)+2, sizeof(TTpAudioPortInfo) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_tppAudioRestoreDefaults_Cmd, emEventTypecnstoolSend, "DefaultAudioPortCmd" );
	
	return wRet;
}

void CCncPortDiagCtrl::OnDefaultAudPortInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)cTpMsg.GetBody();

	PrtMsg( ev_tppAudioRestoreDefaults_Ind, emEventTypecnstoolRecv, "DefaultAudPortInd:%d", bSuccess );
	
	PostEvent( UI_CNSTOOL_MSG_DftAudPort_NTY, 0, (LPARAM)&bSuccess );
}

//丢包
u16 CCncPortDiagCtrl::LostPacketInfoReq()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tppGetLostPacketInfo_Req );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppGetLostPacketInfo_Req, emEventTypecnstoolSend, "" );
	return wRet;
}

const CString& CCncPortDiagCtrl::GetLostPacketInfo()const
{
	return m_strLostPacketInfo;
}

void CCncPortDiagCtrl::OnLostPacketInfoRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	u32 LostPacketNum = *(u32*)( cTpMsg.GetBody() );

	u32 TotalLostPacNum = *(u32*)( cTpMsg.GetBody() + sizeof(u32));
	
	float LostPacketRate;
	if(TotalLostPacNum != 0)
	{
		LostPacketRate = (float)LostPacketNum/TotalLostPacNum*100;
	}
	else
	{
		LostPacketRate = 0;
	}

    //丢包率不应为负数  问题单号：SDM-00158560
    if ( LostPacketRate <= 0 )
    {
        LostPacketRate = 0;
    }
    	
	m_strLostPacketInfo.Format("%.2f", LostPacketRate);
	 
	PrtMsg( ev_tppGetLostPacketInfo_Rsp, emEventTypecnstoolRecv, "LostPacketNum:%d, TotalLostPacNum:%d, LostPacketRate:%s", LostPacketNum, TotalLostPacNum, m_strLostPacketInfo );
	PostEvent( UI_CNSTOOL_MSG_LostPacket_Rsp, 0, 0 );
}

//检测上下行网络速率
const TTPUpDownSpeedInfo& CCncPortDiagCtrl::GetUpDownstreamRate()const
{
	return m_tUpDownSpeedInfo;
}

void CCncPortDiagCtrl::OnUpDownstreamRateNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	m_tUpDownSpeedInfo = *(TTPUpDownSpeedInfo*)( cTpMsg.GetBody() );
	PrtMsg( ev_tppGetUpDownstreamRate_Nty, emEventTypecnstoolRecv, "Up:%d, Down:%d", m_tUpDownSpeedInfo.m_wUpSpeed, m_tUpDownSpeedInfo.m_wDownSpeed );
	PostEvent( UI_CNSTOOL_MSG_UpDownstream_NTY, 0, 0 );	
}

//Tpad列表
u16 CCncPortDiagCtrl::UpdateTpadListReq()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tppGetTPadIpList_Req );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppGetTPadIpList_Req, emEventTypecnstoolSend, "" );
	return wRet;
}

const TTPTPadList& CCncPortDiagCtrl::GetTpadList()const
{
	return m_tTPadList;
}

void CCncPortDiagCtrl::OnTpadListRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPTPadList tTPadList = *(TTPTPadList*)(cTpMsg.GetBody());
	PrtMsg( ev_tppGetTPadIpList_Rsp, emEventTypecnstoolRecv, "" );
	PostEvent( UI_CNSTOOL_MSG_TPadIP_RSP, (WPARAM)&tTPadList, 0 );
}

void CCncPortDiagCtrl::OnTpadListNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPTPadList tTPadList = *(TTPTPadList*)(cTpMsg.GetBody());
	m_tTPadList = tTPadList;
	PrtMsg( ev_tppGetTPadIpList_Nty, emEventTypecnstoolRecv, "" );
	PostEvent( UI_CNSTOOL_MSG_TPadIP_NTY, 0, 0 );
}

//音视频方案选择
u16 CCncPortDiagCtrl::SelAVMatrixCmd( const TTPVgaMixInfo& tVgaMixInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tVgaMixInfo, sizeof(TTPVgaMixInfo) );

    pcTpMsg->SetEvent( ev_tppSelAVMatrixProject_Cmd );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppSelAVMatrixProject_Cmd, emEventTypecnstoolSend, "" );
	return wRet;
}

const TTPVideoDiagInfo& CCncPortDiagCtrl::GetVideoDiagInfo()const
{
	return m_tVideoDiagInfo;
}
const TTPAudioDiagInfo& CCncPortDiagCtrl::GetAudioDiagInfo()const
{
	return m_tAudioDiagInfo;
}

const TTPFtpInfo& CCncPortDiagCtrl::GetFtpInfo() const
{
	return m_tTPFtpInfo;
}

const TTPTelnetInfo& CCncPortDiagCtrl::GetTelnetInfo() const
{
	return m_tTPTelnetInfo;
}

void CCncPortDiagCtrl::OnAVMatrixInfoInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	memset( &m_tAudioDiagInfo, 0, sizeof(m_tAudioDiagInfo) );
	memset( &m_tVideoDiagInfo, 0, sizeof(m_tVideoDiagInfo) );

	TTPVideoDiagInfo tVideoDiagInfo = *(TTPVideoDiagInfo*)( cTpMsg.GetBody() );
	TTPAudioDiagInfo tAudioDiagInfo = *(TTPAudioDiagInfo*)( cTpMsg.GetBody() + sizeof(TTPVideoDiagInfo) );
	
	m_tAudioDiagInfo = tAudioDiagInfo;
	m_tVideoDiagInfo = tVideoDiagInfo;
	
	PostEvent( UI_CNSTOOL_MSG_AVDiag_IND, 0, 0  );
	PrtMsg( ev_tppSelAVMatrixProject_Ind, emEventTypecnstoolRecv, 
		"\n VideoInput1:%d, %d, %d\n VideoInput2:%d, %d, %d\n VideoInput3:%d, %d, %d\n VideoInCurrent:%d, %d, %d, %d\n VideoOutput1:%d, %d, %d\n VideoOutput2:%d, %d, %d\n VideoOutput3:%d, %d, %d\n VideoOutCurrent:%d, %d, %d, %d",
		tVideoDiagInfo.m_atPrimVideoInputPort[0].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoInputPort[0].m_emRes, tVideoDiagInfo.m_atPrimVideoInputPort[0].m_byFrameRate,
		tVideoDiagInfo.m_atPrimVideoInputPort[1].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoInputPort[1].m_emRes, tVideoDiagInfo.m_atPrimVideoInputPort[1].m_byFrameRate,
		tVideoDiagInfo.m_atPrimVideoInputPort[2].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoInputPort[2].m_emRes, tVideoDiagInfo.m_atPrimVideoInputPort[2].m_byFrameRate,
		tVideoDiagInfo.m_tDemoVideoInputPort.m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_byInputDemoIndex, tVideoDiagInfo.m_tDemoVideoInputPort.m_emRes, tVideoDiagInfo.m_tDemoVideoInputPort.m_byFrameRate,
		tVideoDiagInfo.m_atPrimVideoOutputPort[0].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoOutputPort[0].m_emRes, tVideoDiagInfo.m_atPrimVideoOutputPort[0].m_byFrameRate,
		tVideoDiagInfo.m_atPrimVideoOutputPort[1].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoOutputPort[1].m_emRes, tVideoDiagInfo.m_atPrimVideoOutputPort[1].m_byFrameRate,
		tVideoDiagInfo.m_atPrimVideoOutputPort[2].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoOutputPort[2].m_emRes, tVideoDiagInfo.m_atPrimVideoOutputPort[2].m_byFrameRate,
		tVideoDiagInfo.m_tDemoVideoOutputPort.m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_byOutputDemoIndex, tVideoDiagInfo.m_tDemoVideoOutputPort.m_emRes, tVideoDiagInfo.m_tDemoVideoOutputPort.m_byFrameRate );
	PrtMsg( ev_tppSelAVMatrixProject_Ind, emEventTypecnstoolRecv,
		"\n AudioInput1:%d , %d\n AudioInput2:%d , %d\n AudioInput3:%d , %d\n AudioInput110:%d , %d\n AudioInput4:%d , %d\n AudioInput5:%d , %d\n AudioInput6:%d , %d\n AudioInput210:%d , %d\n AudioInput7:%d , %d\n AudioInput8:%d , %d\n AudioInput9:%d , %d\n AudioInput310:%d , %d\n AudioOutput1:%d , %d\n AudioOutput2:%d , %d\n AudioOutput3:%d , %d",
		tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[0],
		tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abAudioPort[1], tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[1],
		tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abAudioPort[2], tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[2],
		tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abAudioPort[3], tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[3],
		tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[0],
		tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[1], tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[1],
		tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[2], tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[2],
		tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[3], tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[3],
		tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[0],
		tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abAudioPort[1], tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[1],
		tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abAudioPort[2], tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[2],
		tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abAudioPort[3], tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[3],		
		tAudioDiagInfo.m_atPrimAudioOutputPort[0].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioOutputPort[0].m_abyVolume[0],
		tAudioDiagInfo.m_atPrimAudioOutputPort[1].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioOutputPort[1].m_abyVolume[0],
		tAudioDiagInfo.m_atPrimAudioOutputPort[2].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioOutputPort[2].m_abyVolume[0]);
}

//停止诊断测试命令			
u16 CCncPortDiagCtrl::StopAVMatrixReq()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );	
    pcTpMsg->SetEvent( ev_tppStopAVMatrixProject_Req );	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	PrtMsg( ev_tppStopAVMatrixProject_Req, emEventTypecnstoolSend, "StopAVMatrixProjectReq" );
	
	return wRet;
}

void CCncPortDiagCtrl::OnStopAVMatrixRsp( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	PostEvent( UI_CNSTOOL_MSG_StopAVMatrix_RSP, 0, 0 );

	PrtMsg( ev_tppStopAVMatrixProject_Rsp, emEventTypecnstoolRecv, "StopAVMatrixProjectRsp" );
}

//重启Cns
u16 CCncPortDiagCtrl::RebootCns()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tppReboot_Nty );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppReboot_Nty, emEventTypecnstoolSend, "RebootCns" );
	return wRet;
}

//升级T300
u16 CCncPortDiagCtrl::UpgradeCns( const TTPFTPFileInfo& tVerFileInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );	
    pcTpMsg->SetEvent( ev_tppUpdate_Cmd );
	pcTpMsg->SetBody( &tVerFileInfo, sizeof(TTPFTPFileInfo) );	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppUpdate_Cmd, emEventTypecnstoolSend, "UpgradeCns" );
	return wRet;
}

void CCncPortDiagCtrl::OnUpgradeCnsInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL* bSuccess = (BOOL*)(cTpMsg.GetBody());
	if ( NULL != bSuccess )
	{
		PostEvent( UI_CNSTOOL_MSG_UpgradeCns_NTY, (WPARAM)bSuccess, 0 );
        PrtMsg( ev_tppUpdate_Ind, emEventTypecnstoolRecv, "bSuccess:%d", *bSuccess );
	}
    else
    {
        PrtMsg( ev_tppUpdate_Ind, emEventTypecnstoolRecv, "bSuccess:NULL" );
    }
	
}

//维护工具刷新界面请求
u16 CCncPortDiagCtrl::ReqRefresh()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tppRefresh_Req );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppRefresh_Req, emEventTypecnstoolSend, "RefreshCnsTool" );
	return wRet;
}

//混音配置
u16 CCncPortDiagCtrl::AudiotMixerCmd( const u8** aAudioMixerInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );	
    pcTpMsg->SetEvent( ev_tppSetAudiotMixer_Cmd );
	pcTpMsg->SetBody( *aAudioMixerInfo, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+1, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+2, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+3, sizeof(u8) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_tppSetAudiotMixer_Cmd, emEventTypecnstoolSend, "AudiotMixerCmd" );
	
	return wRet;
}

u8* CCncPortDiagCtrl::GetAudioMixerInfo()
{
	return m_aAudioMixerInfo;
}

void CCncPortDiagCtrl::OnAudiotMixerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + 4 * sizeof(u8) );
	if ( bSuccess )
	{
		memset( &m_aAudioMixerInfo, 0, sizeof(m_aAudioMixerInfo) );
		for ( int i = 0; i < 4; i++ )
		{
			u8* pMixerInfo = (u8*)( cTpMsg.GetBody() + i * sizeof(u8) );
			if ( NULL != pMixerInfo )
			{
				m_aAudioMixerInfo[i] = *pMixerInfo;
			}     
		}
	}
	
	PrtMsg( ev_tppSetAudiotMixer_Ind, emEventTypecnstoolRecv, "AudiotMixerInd:%d", bSuccess );
	
	PostEvent( UI_CNSTOOL_MSG_AudMixer_NTY, 0, (LPARAM)&bSuccess );
}

u16 CCncPortDiagCtrl::DefaultMixerCmd( const u8** aAudioMixerInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );	
	pcTpMsg->SetEvent( ev_tppMixRestoreDefaults_Cmd );
	pcTpMsg->SetBody( *aAudioMixerInfo, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+1, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+2, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+3, sizeof(u8) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_tppMixRestoreDefaults_Cmd, emEventTypecnstoolSend, "DefaultMixerCmd" );
	
	return wRet;
}

void CCncPortDiagCtrl::OnDefaulttMixerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)cTpMsg.GetBody();

	PrtMsg( ev_tppMixRestoreDefaults_Ind, emEventTypecnstoolRecv, "DefaultMixerInd:%d", bSuccess );
	
	PostEvent( UI_CNSTOOL_MSG_DftMixer_NTY, 0, (LPARAM)&bSuccess );
}

//均衡器设置
u16 CCncPortDiagCtrl::AudioEqualizerCmd( const TTPEqualizer** atEqualizer )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( *atEqualizer, sizeof(TTPEqualizer) );
	pcTpMsg->CatBody( (*atEqualizer)+1, sizeof(TTPEqualizer) );
	pcTpMsg->CatBody( (*atEqualizer)+2, sizeof(TTPEqualizer) );
	
    pcTpMsg->SetEvent( ev_tppSetAudioEqualizer_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppSetAudioEqualizer_Cmd, emEventTypecnstoolSend, "AudioEqualizerCmd" );
	return wRet;
}

TTPEqualizer* CCncPortDiagCtrl::GetAudioEqualizer()
{
	return m_atEqualizer;
}

void CCncPortDiagCtrl::OnAudioEqualizerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + 3 * sizeof(TTPEqualizer) );
	if ( bSuccess )
	{
		memset( &m_atEqualizer, 0, sizeof(m_atEqualizer) );	
		for ( int i = 0; i < 3; i++ )
		{
			TTPEqualizer* ptEqualizer = (TTPEqualizer*)( cTpMsg.GetBody() + i * sizeof(TTPEqualizer) );
			
			if ( NULL != ptEqualizer )
			{
				m_atEqualizer[i] = *ptEqualizer;
			}
		}
	}

	PostEvent( UI_CNSTOOL_MSG_AudEqualizer_NTY, 0, (LPARAM)&bSuccess  );
	PrtMsg( ev_tppSetAudioEqualizer_Ind, emEventTypecnstoolRecv, "AudioEqInd:%d", bSuccess );
}

u16 CCncPortDiagCtrl::DefaultEqCmd( const TTPEqualizer** atEqualizer )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( *atEqualizer, sizeof(TTPEqualizer) );
	pcTpMsg->CatBody( (*atEqualizer)+1, sizeof(TTPEqualizer) );
	pcTpMsg->CatBody( (*atEqualizer)+2, sizeof(TTPEqualizer) );
	
    pcTpMsg->SetEvent( ev_tppEqualizerReDefaults_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppEqualizerReDefaults_Cmd, emEventTypecnstoolSend, "DefaultEqCmd" );
	return wRet;
}

void CCncPortDiagCtrl::OnDefaultEqInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)cTpMsg.GetBody();

	PostEvent( UI_CNSTOOL_MSG_DftEq_NTY, 0, (LPARAM)&bSuccess  );
	PrtMsg( ev_tppEqualizerReDefaults_Ind, emEventTypecnstoolRecv, "DefaultEqInd:%d", bSuccess );
}

//呼叫服务器
u16 CCncPortDiagCtrl::CallServerCmd( const TTPCallSerInfo& tCallSerInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tCallSerInfo, sizeof(TTPCallSerInfo) );
	
    pcTpMsg->SetEvent( ev_tppSetCallServerInfo_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = tCallSerInfo.dwCallServiceIP;
	PrtMsg( ev_tppSetCallServerInfo_Cmd, emEventTypecnstoolSend, _T( "CallSerIP:%s" ), inet_ntoa(tAddr) );
	return wRet;
}

const TTPCallSerInfo& CCncPortDiagCtrl::GetCallServerInfo() const
{
	return m_tCallSerInfo;
}

void CCncPortDiagCtrl::OnCallServerNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	memset( &m_tCallSerInfo, 0, sizeof(m_tCallSerInfo) );

	m_tCallSerInfo = *(TTPCallSerInfo*)( cTpMsg.GetBody() );

	PostEvent( UI_CNSTOOL_MSG_CallSer_NTY, 0, 0  );
	in_addr tAddr;
	tAddr.S_un.S_addr = m_tCallSerInfo.dwCallServiceIP;
	PrtMsg( ev_tppSetCallServerInfo_Nty, emEventTypecnstoolRecv, _T("CallSerIP:%s"), inet_ntoa(tAddr) );
}

void CCncPortDiagCtrl::OnCallServerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

    memset( &m_tCallSerInfo, 0, sizeof(m_tCallSerInfo) );
	
	TTPCallSerInfo tCallSerInfo = *(TTPCallSerInfo*)( cTpMsg.GetBody() );
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPCallSerInfo) );
	if ( TRUE == bSuccess )
	{
		m_tCallSerInfo = tCallSerInfo;
	}
	PostEvent( UI_CNSTOOL_MSG_CallSer_IND, (WPARAM)&tCallSerInfo, (LPARAM)&bSuccess );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tCallSerInfo.dwCallServiceIP;
	PrtMsg( ev_tppSetCallServerInfo_Ind, emEventTypecnstoolRecv,_T("CallSerIP: %s, BOOL:%d"), inet_ntoa(tAddr), bSuccess );

}

//升级服务器			
u16 CCncPortDiagCtrl::UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tUpgradeSer, sizeof(TTPUpgradeSer) );
	
    pcTpMsg->SetEvent( ev_tppSetUpgradeServerInfo_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = tUpgradeSer.dwSerIP;
	PrtMsg( ev_tppSetUpgradeServerInfo_Cmd, emEventTypecnstoolSend, "UpgradeSerIP: %s", inet_ntoa(tAddr) );

	return wRet;
}

const TTPUpgradeSer& CCncPortDiagCtrl::GetUpgradeSerInfo() const
{
	return m_tUpgradeSer;
}

void CCncPortDiagCtrl::OnUpgradeSerNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	m_tUpgradeSer = *(TTPUpgradeSer*)( cTpMsg.GetBody() );

	PostEvent( UI_CNSTOOL_MSG_UpgradeSer_NTY, 0, 0  );
	in_addr tAddr;
	tAddr.S_un.S_addr = m_tUpgradeSer.dwSerIP;
	PrtMsg( ev_tppSetUpgradeServerInfo_Nty, emEventTypecnstoolRecv, "UpgradeSerIP: %s", inet_ntoa(tAddr) );
}

void CCncPortDiagCtrl::OnUpgradeSerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	TTPUpgradeSer tUpgradeSer = *(TTPUpgradeSer*)( cTpMsg.GetBody() );
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPUpgradeSer) );
	if ( TRUE == bSuccess )
	{
		m_tUpgradeSer = tUpgradeSer;
	}
	PostEvent( UI_CNSTOOL_MSG_UpgradeSer_IND, 0, (LPARAM)&bSuccess );

	in_addr tAddr;
	tAddr.S_un.S_addr = tUpgradeSer.dwSerIP;
	PrtMsg( ev_tppSetUpgradeServerInfo_Ind, emEventTypecnstoolRecv, "UpgradeSerIP: %s, BOOL:%d", inet_ntoa(tAddr), bSuccess );
}

u16 CCncPortDiagCtrl::ConfSignCmd( const BOOL& bOk, u8 byIndex )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &bOk, sizeof(BOOL) );
	pcTpMsg->CatBody( &byIndex, sizeof(u8) );
    pcTpMsg->SetEvent( ev_tppSetBannerLogo_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppSetBannerLogo_Cmd, emEventTypecnstoolSend, "SetBannerLogoCmd:%d, From:%d ", bOk, byIndex );
	return wRet;
}

//会议优选格式
u16 CCncPortDiagCtrl::VideoFormatCmd( const TTPVidForamt& tVidForamt )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tVidForamt, sizeof(TTPVidForamt) );
    pcTpMsg->SetEvent( ev_CnCfgVideoFormat_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgVideoFormat_Cmd, emEventTypecnstoolSend, _T( "u16:%d, EmTpVideoResolution:%d, EmTpVideoQualityLevel:%d" )
		, tVidForamt.wVidFrameRate, tVidForamt.emTpVideoResolution, tVidForamt.emTpVideoQualityLevel );
	return wRet;
}

void CCncPortDiagCtrl::OnVideoFormatInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	TTPVidForamt tVidForamt = *(TTPVidForamt*)( cTpMsg.GetBody() );
	m_tVidForamt = tVidForamt;

	PostEvent( UI_CNSTOOL_VIDEOFORMAT_IND, 0, 0 );

	PrtMsg( ev_CnCfgVideoFormat_Ind, emEventTypecnstoolRecv, _T( "u16:%d, EmTpVideoResolution:%d, EmTpVideoQualityLevel:%d" )
		, tVidForamt.wVidFrameRate, tVidForamt.emTpVideoResolution, tVidForamt.emTpVideoQualityLevel );
}

const TTPVidForamt& CCncPortDiagCtrl::GetVideoFormatInfo() const
{
	return m_tVidForamt;
}

//演示优选格式
u16 CCncPortDiagCtrl::DualVideoFormatCmd( const TTPVidForamt& tVidForamt )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tVidForamt, sizeof(TTPVidForamt) );
    pcTpMsg->SetEvent( ev_CnCfgDualVideoFormat_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgDualVideoFormat_Cmd, emEventTypecnstoolSend, _T( "u16:%d, EmTpVideoResolution:%d, EmTpVideoQualityLevel:%d" )
		, tVidForamt.wVidFrameRate, tVidForamt.emTpVideoResolution, tVidForamt.emTpVideoQualityLevel );
	return wRet;
}

void CCncPortDiagCtrl::OnDualVideoFormatInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	TTPVidForamt tVidForamt = *(TTPVidForamt*)( cTpMsg.GetBody() );
	m_tDualVidForamt = tVidForamt;
	
	PostEvent( UI_CNSTOOL_DUALVIDEOFORMAT_IND, 0, 0 );
	
	PrtMsg( ev_CnCfgDualVideoFormat_Ind, emEventTypecnstoolRecv, _T( "u16:%d, EmTpVideoResolution:%d, EmTpVideoQualityLevel:%d" )
		, tVidForamt.wVidFrameRate, tVidForamt.emTpVideoResolution, tVidForamt.emTpVideoQualityLevel );
}

const TTPVidForamt& CCncPortDiagCtrl::GetDualVideoFormatInfo() const
{
	return m_tDualVidForamt;
}

//单屏码率
u16 CCncPortDiagCtrl::CallRateCmd( const u16 wCallRate )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &wCallRate, sizeof(u16) );
    pcTpMsg->SetEvent( ev_CnCfgCallRate_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgCallRate_Cmd, emEventTypecnstoolSend, _T( "wCallRate(send):%d" ), wCallRate );
	return wRet;
}

void CCncPortDiagCtrl::OnCallRateInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	u16 wCallRate = *(u16*)( cTpMsg.GetBody() );
	m_wCallRate = wCallRate;
	
	PostEvent( UI_CNSTOOL_CALLRATE_IND, 0, 0 );
	PrtMsg( ev_CnCfgCallRate_Ind, emEventTypecnstoolRecv, _T( "wCallRate(recv):%d" ), wCallRate );
}

const u16 CCncPortDiagCtrl::GetCallRate() const
{
	return m_wCallRate;
}

//演示码率
u16 CCncPortDiagCtrl::DualCallRateCmd( const u16 wDualCallRate )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &wDualCallRate, sizeof(u16) );
    pcTpMsg->SetEvent( ev_CnCfgDualCallRate_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgDualCallRate_Cmd, emEventTypecnstoolSend, _T( "wDualCallRate(send):%d" ), wDualCallRate );
	return wRet;
}

void CCncPortDiagCtrl::OnDualCallRateInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	u16 wDualCallRate = *(u16*)( cTpMsg.GetBody() );
	m_wDualCallRate = wDualCallRate;
	
	PostEvent( UI_CNSTOOL_DUALCALLRATE_IND, 0, 0 );
	PrtMsg( ev_CnCfgDualCallRate_Ind, emEventTypecnstoolRecv, _T( "wDualCallRate(recv):%d" ), wDualCallRate );
}

const u16 CCncPortDiagCtrl::GetDualCallRate() const
{
	return m_wDualCallRate;
}

//版本信息通知
void CCncPortDiagCtrl::OnVerInfoNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	s8* achVerInfo = (s8*)( cTpMsg.GetBody() );
	memcpy( m_achVerInfo, achVerInfo, MAX_DEVICEVER_LEN );
	EmCnModel emCnModel = *( EmCnModel *)( cTpMsg.GetBody() +sizeof(s8)*MAX_DEVICEVER_LEN );
	m_emCnModel = emCnModel;

	PostEvent( UI_CNSTOOL_VERINFO_NTY, (WPARAM)achVerInfo, (LPARAM)&emCnModel );
	PrtMsg( ev_CnVerInfo_Nty, emEventTypecnstoolRecv, _T( "achVerInfo: %s, emCnModel: %d" ), achVerInfo, emCnModel );
}

//会议轮询
u16 CCncPortDiagCtrl::ConfPollCmd( const TTPPollInfo& tPollInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tPollInfo, sizeof(TTPPollInfo) );
    pcTpMsg->SetEvent( ev_CnCfgConfPoll_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgConfPoll_Cmd, emEventTypecnstoolSend, _T( "bIsPoll:%d, wPollExpire:%d" ), tPollInfo.bIsPoll, tPollInfo.wPollExpire );
	return wRet;
}

void CCncPortDiagCtrl::OnConfPollInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	TTPPollInfo tPollInfo = *(TTPPollInfo*)( cTpMsg.GetBody() );
	m_tPollInfo = tPollInfo;
	
	PostEvent( UI_CNSTOOL_CONFPOOL_IND, 0, 0 );
	PrtMsg( ev_CnCfgConfPoll_Ind, emEventTypecnstoolRecv, _T( "bIsPoll:%d, wPollExpire:%d" ), tPollInfo.bIsPoll, tPollInfo.wPollExpire );
}

const TTPPollInfo& CCncPortDiagCtrl::GetConfPollInfo() const
{
	return m_tPollInfo;
}

//会议讨论
u16 CCncPortDiagCtrl::ConfDisCmd( const BOOL& bDis )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &bDis, sizeof(BOOL) );
    pcTpMsg->SetEvent( ev_CnCfgConfDis_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgConfDis_Cmd, emEventTypecnstoolSend, _T( "bDis:%d" ), bDis );
	return wRet;
}

void CCncPortDiagCtrl::OnConfDisInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	BOOL bDis = *(BOOL*)( cTpMsg.GetBody() );
	m_bDis = bDis;
	
	PostEvent( UI_CNSTOOL_CONFDIS_IND, 0, 0 );
	PrtMsg( ev_CnCfgConfDis_Ind, emEventTypecnstoolRecv, _T( "bDis:%d" ), bDis );
}

const BOOL& CCncPortDiagCtrl::GetConfDisInfo() const
{
	return m_bDis;
}

//音频格式
u16 CCncPortDiagCtrl::AudioFormatCmd( const EmTpAudioFormat& emAudioFormat )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &emAudioFormat, sizeof(EmTpAudioFormat) );
    pcTpMsg->SetEvent( ev_CnCfgAudioFormat_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgAudioFormat_Cmd, emEventTypecnstoolSend, _T( "AudioFormat:%d( emTPAMpegAACLD:%d, emTPAG711a:%d, emTPAG711u:%d, \
emTPAG719:%d, emTPAG7221:%d, emTPAMP3:%d, emTPAMpegAACLC:%d )" ), emAudioFormat, emTPAMpegAACLD, emTPAG711a, emTPAG711u, emTPAG719, \
emTPAG7221, emTPAMP3, emTPAMpegAACLC );
	return wRet;
}

void CCncPortDiagCtrl::OnAudioFormatInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	EmTpAudioFormat emAudioFormat = *(EmTpAudioFormat*)( cTpMsg.GetBody() );
	m_emAudioFormat = emAudioFormat;
	
	PostEvent( UI_CNSTOOL_AUDIOFORMAT_IND, 0, 0 );
	PrtMsg( ev_CnCfgAudioFormat_Ind, emEventTypecnstoolRecv, _T( "AudioFormat:%d( emTPAMpegAACLD:%d, emTPAG711a:%d, emTPAG711u:%d, \
emTPAG719:%d, emTPAG7221:%d, emTPAMP3:%d, emTPAMpegAACLC:%d )" ), emAudioFormat, emTPAMpegAACLD, emTPAG711a, emTPAG711u, emTPAG719, \
emTPAG7221, emTPAMP3, emTPAMpegAACLC );
}

const EmTpAudioFormat& CCncPortDiagCtrl::GetAudioFormatInfo() const
{
	return m_emAudioFormat;
}

void CCncPortDiagCtrl::GetRouteInfoData(vector<TRouteCfg> &vecTRouteCfg) const
{
	vecTRouteCfg = m_vecTRouteCfg;
}

u16 CCncPortDiagCtrl::SetDataConfSerCmd( const TTPDataConfInfo& tWBSerIp )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tWBSerIp, sizeof(TTPDataConfInfo) );
	
    pcTpMsg->SetEvent( ev_tppSetDataServerInfo_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tWBSerIp.dwSerIP;
	PrtMsg( ev_tppSetDataServerInfo_Cmd, emEventTypecnstoolSend, "DataConfSerIP: %s", inet_ntoa(tAddr) );
	
	return wRet;
}

u16 CCncPortDiagCtrl::SetMatrixSerCmd(const TTPMatrixServerInfo& tTPMatrixServerInfo)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tTPMatrixServerInfo, sizeof(TTPMatrixServerInfo) );
	
    pcTpMsg->SetEvent( ev_CnSetMatrixServerInfo_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTPMatrixServerInfo.m_dwSerIP;
	PrtMsg( ev_CnSetMatrixServerInfo_Cmd, emEventTypecnstoolSend, "tTPMatrixServerInfo: %s", inet_ntoa(tAddr) );

	return 0;
}

u16 CCncPortDiagCtrl::SetNtpSerCmd( const TTPNtpSer& tTpNtpSer )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tTpNtpSer, sizeof(TTPNtpSer) );
	
    pcTpMsg->SetEvent( ev_tppSetNtpServerInfo_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTpNtpSer.dwSerIP;
	PrtMsg( ev_tppSetNtpServerInfo_Cmd, emEventTypecnstoolSend, "tTPNtpServerInfo: %s", inet_ntoa(tAddr) );
	
	return 0;
}

u16 CCncPortDiagCtrl::SetQtEncryptSerCmd( const TTpQtEncryptCfg& tTpQtEncryptCfg)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody(&tTpQtEncryptCfg, sizeof(TTpQtEncryptCfg));

	pcTpMsg->SetEvent( ev_tppSetQtEncryptInfo_Cmd );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = tTpQtEncryptCfg.m_dwQtIP;
	PrtMsg( ev_tppSetQtEncryptInfo_Cmd, emEventTypecnstoolSend, "bOpen:%d QtEncryptSerIP: %s, QtEncryptSerID: %d", tTpQtEncryptCfg.m_bOpen, inet_ntoa(tAddr), tTpQtEncryptCfg.m_dwQtID );

	return wRet;
}

const TTPDataConfInfo& CCncPortDiagCtrl::GetWBSerIp() const
{
    return m_tWBSerIp;
}

const TTpQtEncryptCfg& CCncPortDiagCtrl::GetQtEncryptCfg() const
{
	return m_tTpQtEncryptCfg;
}

const TTPNtpSer& CCncPortDiagCtrl::GetNtpSerIP() const
{
	return m_tTpNtpSerIp;
}

const TTPMatrixServerInfo& CCncPortDiagCtrl::GetMatrixSerInfo() const
{
	return m_tMatrixServerInfo;
}

void CCncPortDiagCtrl::OnWBServerNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    
    m_tWBSerIp = *reinterpret_cast<TTPDataConfInfo*>(cTpMsg.GetBody());
    
    PrtMsg( ev_tppSetDataServerInfo_Nty, emEventTypeCnsRecv, _T( "set WBServerIp " ) );
    
    PostEvent( UI_TPPSETDATASERVERINFONTY, 0, 0 );

}

void CCncPortDiagCtrl::OnSetMatrixServerInfoNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg); 
    
    m_tMatrixServerInfo = *reinterpret_cast<TTPMatrixServerInfo*>(cTpMsg.GetBody());

    in_addr tAddr;
	tAddr.S_un.S_addr = m_tMatrixServerInfo.m_dwSerIP;
    PrtMsg( ev_CnSetMatrixServerInfo_Nty, emEventTypeCnsRecv, _T( "set Matrixip: %s " ), inet_ntoa(tAddr));
    
    PostEvent( UI_TPSETMATRIXSERVERINFO_NTY, 0, 0 );
}

void CCncPortDiagCtrl::OnSetQtEntryptInfoNty(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	
	m_tTpQtEncryptCfg = *(TTpQtEncryptCfg*)(cTpMsg.GetBody());
	
	PrtMsg( ev_tppSetQtEncryptInfo_Nty, emEventTypeCnsRecv, "bOpen:%d QtIP: %d, QtID: %d",m_tTpQtEncryptCfg.m_bOpen, m_tTpQtEncryptCfg.m_dwQtIP, m_tTpQtEncryptCfg.m_dwQtID );
	PostEvent( UI_SETQTENCRYPTINFO_Nty, 0, 0 );
}

void CCncPortDiagCtrl::OnSetQtEncryptInfoInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	memset( &m_tTpQtEncryptCfg, 0, sizeof(m_tTpQtEncryptCfg) );

	TTpQtEncryptCfg tTpQtEncryptCfg = *(TTpQtEncryptCfg*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTpQtEncryptCfg));

	if( TRUE == bSuccess)
	{
		m_tTpQtEncryptCfg = tTpQtEncryptCfg;
	}

	PostEvent( UI_SETQTENCRYPTINFO_Ind, (WPARAM)&tTpQtEncryptCfg, (LPARAM)&bSuccess);

	in_addr tAddr;
	tAddr.S_un.S_addr = tTpQtEncryptCfg.m_dwQtIP;
	PrtMsg( ev_tppSetDataServerInfo_Ind, emEventTypecnstoolRecv,_T("bOpen:%d QtEncryptSerIP: %s, QtEncryptSerID: %d, BOOL:%d"), tTpQtEncryptCfg.m_bOpen, inet_ntoa(tAddr), tTpQtEncryptCfg.m_dwQtID, bSuccess );
}

void CCncPortDiagCtrl::OnSetNtpServerInfoNty(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg); 
    
    m_tTpNtpSerIp = *reinterpret_cast<TTPNtpSer*>(cTpMsg.GetBody());
	
    in_addr tAddr;
	tAddr.S_un.S_addr = m_tTpNtpSerIp.dwSerIP;
    PrtMsg( ev_tppSetNtpServerInfo_Nty, emEventTypeCnsRecv, _T( "set NtpSerIp: %s " ), inet_ntoa(tAddr));
    
    PostEvent( UI_TPSETNTPSERVERINFO_NTY, 0, 0 );
}

void CCncPortDiagCtrl::OnSetNtpServerInfoInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	memset( &m_tTpNtpSerIp, 0, sizeof(m_tTpNtpSerIp) );
	
	TTPNtpSer tTpNtpSer = *(TTPNtpSer*)(cTpMsg.GetBody());
	
	BOOL bSuccess =  *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPNtpSer) );
	
	if ( TRUE == bSuccess )
	{
		m_tTpNtpSerIp = tTpNtpSer;
	}
	PostEvent( UI_TPSETMATRIXSERVERINFO_IND, (WPARAM)&tTpNtpSer, (LPARAM)&bSuccess );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTpNtpSer.dwSerIP;
	PrtMsg( ev_tppSetNtpServerInfo_Ind, emEventTypecnstoolRecv,_T("NtpSerIP: %s, BOOL:%d"), inet_ntoa(tAddr), bSuccess );
}

void CCncPortDiagCtrl::OnSetFtpInfoNty(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TTPFtpInfo tTPFtpInfo = *(TTPFtpInfo*)(cTpMsg.GetBody());
	memset( &m_tTPFtpInfo, 0, sizeof( m_tTPFtpInfo ));
	m_tTPFtpInfo = tTPFtpInfo;

	PrtMsg( ev_CnFtpInfo_Nty, emEventTypeCnsRecv, _T( "tTPFtpInfo.achUserName: %s, tTPFtpInfo.achPassword: %s, tTPFtpInfo.bOpen: %d" ), tTPFtpInfo.achUserName, tTPFtpInfo.achPassword, tTPFtpInfo.bOpen );

	PostEvent( UI_FTPINFO_Nty, (WPARAM)&m_tTPFtpInfo, 0 );
}

void CCncPortDiagCtrl::OnSetFtpRsp(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TTPFtpInfo tTPFtpInfo = *(TTPFtpInfo*)( cTpMsg.GetBody() );
	memset( &m_tTPFtpInfo, 0, sizeof( m_tTPFtpInfo ));
	m_tTPFtpInfo = tTPFtpInfo;
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPFtpInfo) );

	PrtMsg( ev_CnSetFtp_Rsp, emEventTypeCnsRecv, _T( "tTPFtpInfo.achUserName: %s, tTPFtpInfo.achPassword: %s, tTPFtpInfo.bOpen: %d, bSuccess: %d" ), tTPFtpInfo.achUserName, tTPFtpInfo.achPassword, tTPFtpInfo.bOpen, bSuccess );

	PostEvent( UI_SETFTPINFO_Rsp, (WPARAM)&m_tTPFtpInfo, (LPARAM)&bSuccess);
}

void CCncPortDiagCtrl::OnSetTelnetInfoNty(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TTPTelnetInfo tTPTelnetInfo = *(TTPTelnetInfo*)(cTpMsg.GetBody());
	memset( &m_tTPTelnetInfo, 0, sizeof( m_tTPTelnetInfo ));
	m_tTPTelnetInfo = tTPTelnetInfo;
	
	PrtMsg( ev_CnTelnetInfo_Nty, emEventTypeCnsRecv, _T( "tTPTelnetInfo.achUserName: %s, tTPTelnetInfo.achPassword: %s, tTPTelnetInfo.bOpen: %d" ), tTPTelnetInfo.achUserName, tTPTelnetInfo.achPassword, tTPTelnetInfo.bOpen );
	
	PostEvent( UI_TELNETINFO_Nty, (WPARAM)&m_tTPTelnetInfo, 0 );
}

void CCncPortDiagCtrl::OnSetTelnetRsp(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TTPTelnetInfo tTPTelnetInfo = *(TTPTelnetInfo*)( cTpMsg.GetBody() );
	memset( &m_tTPTelnetInfo, 0, sizeof( m_tTPTelnetInfo ));
	m_tTPTelnetInfo = tTPTelnetInfo;
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPTelnetInfo) );
	
	PrtMsg( ev_CnSetTelnet_Rsp, emEventTypeCnsRecv, _T( "tTPTelnetInfo.achUserName: %s, tTPTelnetInfo.achPassword: %s, tTPTelnetInfo.bOpen: %d, bSuccess: %d" ), tTPTelnetInfo.achUserName, tTPTelnetInfo.achPassword, tTPTelnetInfo.bOpen, bSuccess );
	
	PostEvent( UI_SETTELNETINFO_Rsp, (WPARAM)&m_tTPTelnetInfo, (LPARAM)&bSuccess);
}

void CCncPortDiagCtrl::OnWBServerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	memset( &m_tWBSerIp,0, sizeof(m_tWBSerIp) );

	TTPDataConfInfo tWBSerIp= *(TTPDataConfInfo*)(cTpMsg.GetBody());

	BOOL bSuccess =  *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPDataConfInfo) );

	if ( TRUE == bSuccess )
	{
		m_tWBSerIp = tWBSerIp;
	}
	PostEvent( UI_TPPSETDATASERVER_IND, (WPARAM)&tWBSerIp, (LPARAM)&bSuccess );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tWBSerIp.dwSerIP;
	PrtMsg( ev_tppSetDataServerInfo_Ind, emEventTypecnstoolRecv,_T("DataConfSerIP: %s, BOOL:%d"), inet_ntoa(tAddr), bSuccess );

}

void CCncPortDiagCtrl::OnSetMatrixServerInfoInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	memset( &m_tMatrixServerInfo, 0, sizeof(m_tMatrixServerInfo) );
	
	TTPMatrixServerInfo tTPMatrixServerInfo= *(TTPMatrixServerInfo*)(cTpMsg.GetBody());
	
	BOOL bSuccess =  *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPMatrixServerInfo) );
	
	if ( TRUE == bSuccess )
	{
		m_tMatrixServerInfo = tTPMatrixServerInfo;
	}
	PostEvent( UI_TPSETMATRIXSERVERINFO_IND, (WPARAM)&tTPMatrixServerInfo, (LPARAM)&bSuccess );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTPMatrixServerInfo.m_dwSerIP;
	PrtMsg( ev_CnSetMatrixServerInfo_Ind, emEventTypecnstoolRecv,_T("MatrixSerIP: %s, BOOL:%d"), inet_ntoa(tAddr), bSuccess );
}

//音频配置

u16 CCncPortDiagCtrl::SetAudioInfoCmd( const TTPMPAudioInfo* ptAudioPortInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_CnSetAudioInfo_Cmd );
	pcTpMsg->SetBody( ptAudioPortInfo, sizeof(TTPMPAudioInfo) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_CnSetAudioInfo_Cmd, emEventTypecnstoolSend, "AudioInfoSetCmd ,增益1:%d, 增益2:%d, 增益3:%d,MAEC:%d,AGC:%d" ,
		ptAudioPortInfo->m_abyOutputGain[0],ptAudioPortInfo->m_abyOutputGain[1],ptAudioPortInfo->m_abyOutputGain[2],
		ptAudioPortInfo->m_bIsAECEnable,ptAudioPortInfo->m_bIsAGCEnable);	
	return wRet;
}

u16 CCncPortDiagCtrl::SetListenPortCmd(const EmAudMixType emAudMixtype, const u8 byAudMixVolume )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_TppSetMixType_Cmd );
	pcTpMsg->SetBody( &emAudMixtype, sizeof(EmAudMixType) );
	pcTpMsg->CatBody( &byAudMixVolume, sizeof(u8) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	PrtMsg( ev_TppSetMixType_Cmd, emEventTypecnstoolSend, "emAudMixType: %d Volume:%d", emAudMixtype, byAudMixVolume );
	return wRet;
}

u16 CCncPortDiagCtrl::SetAux2OutCmd(const EmAudExtend emAudExtend, const u8 byAudExtendVolume )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	
	pcTpMsg->SetEvent( ev_TppSetLocalAudExtend_Cmd );
	pcTpMsg->SetBody( &emAudExtend, sizeof(EmAudExtend) );
	pcTpMsg->CatBody( &byAudExtendVolume, sizeof(u8) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_TppSetLocalAudExtend_Cmd, emEventTypecnstoolSend, "EmAudExtend: %d Volume:%d", emAudExtend, byAudExtendVolume );
	return wRet;
}

void CCncPortDiagCtrl::OnAudioInfoInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TTPMPAudioInfo tAudioInfo= *(TTPMPAudioInfo*)(cTpMsg.GetBody());

	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() +  sizeof(TTPMPAudioInfo) );
	if ( bSuccess )
	{
		memset( &m_tAudioSetInfo, 0, sizeof(m_tAudioSetInfo) );
		m_tAudioSetInfo = tAudioInfo;
	}
	
	PrtMsg( ev_CnSetAudioInfo_Ind, emEventTypecnstoolRecv, "AudioInfoInd:%d ,增益1:%d, 增益2:%d, 增益3:%d,MAEC:%d,AGC:%d",bSuccess ,
		tAudioInfo.m_abyOutputGain[0],tAudioInfo.m_abyOutputGain[1],tAudioInfo.m_abyOutputGain[2],
		tAudioInfo.m_bIsAECEnable,tAudioInfo.m_bIsAGCEnable);
	PostEvent( UI_CNSTOOL_MSG_Audio_NTY, 0, (LPARAM)&bSuccess );
}

void CCncPortDiagCtrl::OnSetMixTypeInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	EmAudMixType emAudMixtype = *(EmAudMixType *)( cTpMsg.GetBody());
	u8 byAudMixValume = *(u8 *)( cTpMsg.GetBody() + sizeof(EmAudMixType));
	
	PrtMsg( ev_TppSetMixType_Ind, emEventTypecnstoolRecv, "emAudMixType: %d Valume: %d", emAudMixtype, byAudMixValume);
	
	PostEvent(UI_CNSTOOL_MSG_Listen_NTY, (WPARAM)&byAudMixValume, (LPARAM)&emAudMixtype );
}

void CCncPortDiagCtrl::OnSetAUX2InfoInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	EmAudExtend emAudExtend = *(EmAudExtend *)( cTpMsg.GetBody());
	u8 byAudExtendValume = *(u8 *)( cTpMsg.GetBody() + sizeof(EmAudExtend));
	
	PrtMsg( ev_TppSetLocalAudExtend_Ind, emEventTypecnstoolRecv, "emAudExtend: %d Valume: %d", emAudExtend, byAudExtendValume);
	
	PostEvent( UI_CNSTOOL_MSG_AUX2_NTY, (WPARAM)&byAudExtendValume, (LPARAM)&emAudExtend);
}

u16 CCncPortDiagCtrl::DefaultAudioSetCmd( const TTPMPAudioInfo* ptAudioPortInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_CnSetDefaultAudioInfo_Cmd );
	pcTpMsg->SetBody( ptAudioPortInfo, sizeof(TTPMPAudioInfo) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetDefaultAudioInfo_Cmd, emEventTypecnstoolSend, "DefaultAudioCmd ,增益1:%d, 增益2:%d, 增益3:%d,MAEC:%d,AGC:%d" ,
		ptAudioPortInfo->m_abyOutputGain[0],ptAudioPortInfo->m_abyOutputGain[1],ptAudioPortInfo->m_abyOutputGain[2],
		ptAudioPortInfo->m_bIsAECEnable,ptAudioPortInfo->m_bIsAGCEnable);	
	return wRet;
}

u16 CCncPortDiagCtrl::DefaultListenPortSetCmd(const EmAudMixType emAudMixtype, const u8 byAudMixVolume)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	
	pcTpMsg->SetEvent( ev_TppSetMixType_Cmd );
	pcTpMsg->SetBody( &emAudMixtype, sizeof(EmAudMixType) );
	pcTpMsg->CatBody( &byAudMixVolume, sizeof(u8) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_TppSetMixType_Cmd, emEventTypecnstoolSend, "emAudMixType: %d Volume: %d", emAudMixtype, byAudMixVolume );
	return wRet;
}

u16 CCncPortDiagCtrl::DefaultAux2OutSetCmd(const EmAudExtend emAudExtend, const u8 byAudExtendVolume)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	
	pcTpMsg->SetEvent( ev_TppSetLocalAudExtend_Cmd );
	pcTpMsg->SetBody( &emAudExtend, sizeof(EmAudExtend) );
	pcTpMsg->CatBody( &byAudExtendVolume, sizeof(u8) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_TppSetLocalAudExtend_Cmd, emEventTypecnstoolSend, "EmAudExtend: %d Volume: %d", emAudExtend, byAudExtendVolume );
	return wRet;
}

void CCncPortDiagCtrl::OnDefaultAudioSetInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TTPMPAudioInfo tAudioInfo= *(TTPMPAudioInfo*)(cTpMsg.GetBody());

	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPMPAudioInfo) );
	
	if ( bSuccess == TRUE )
	{
		m_tAudioSetInfo = tAudioInfo;
	}
	PrtMsg( ev_CnSetDefaultAudioInfo_Ind, emEventTypecnstoolRecv, "DefaultAudioInfoInd:%d ,增益1:%d, 增益2:%d, 增益3:%d,MAEC:%d,AGC:%d",bSuccess ,
		tAudioInfo.m_abyOutputGain[0],tAudioInfo.m_abyOutputGain[1],tAudioInfo.m_abyOutputGain[2],
		tAudioInfo.m_bIsAECEnable,tAudioInfo.m_bIsAGCEnable);
	PostEvent( UI_CNSTOOL_MSG_DftAudio_NTY, 0, (LPARAM)&bSuccess );
}

u16 CCncPortDiagCtrl::SetAudioWhiteNoiseCmd( BOOL bIsOpen ,u32 dwWhiteNoisePort )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_CnWhiteNoise_Req );
	pcTpMsg->SetBody( &dwWhiteNoisePort, sizeof(u32) );
	pcTpMsg->CatBody(&bIsOpen,sizeof(BOOL));
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_CnWhiteNoise_Req, emEventTypecnstoolSend, "WhiteNoiseReq" );
	return wRet;
}

void CCncPortDiagCtrl::OnAudioWhiteNoiseRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bIsOpen = *(BOOL*)( cTpMsg.GetBody() +  sizeof(u32) );
	BOOL bSuccess;

	u32 dwWhiteNoiseMp = *( u32 *)(cTpMsg.GetBody());

	if (( dwWhiteNoiseMp >= 3 )||( dwWhiteNoiseMp < 0 ))
	{
		bSuccess = FALSE;
	}
	else
	{
		if ( m_bWhiteNoise[dwWhiteNoiseMp] == bIsOpen )
		{
			bSuccess = FALSE;
		}
		else
		{
			m_bWhiteNoise[dwWhiteNoiseMp] = bIsOpen;
			bSuccess = TRUE;
		}
	}

	PrtMsg( ev_CnWhiteNoise_Rsp, emEventTypecnstoolRecv, "WhiteNoiseSetRsp[%d]= %d",dwWhiteNoiseMp,bIsOpen );
	PostEvent( UI_CNSTOOL_MSG_WhiteNoise_NTY ,0, (LPARAM)&bSuccess );
}

const TTPMPAudioInfo& CCncPortDiagCtrl::GetAudioInfo() const
{
	return m_tAudioSetInfo;
}

BOOL * CCncPortDiagCtrl::GetWhiteNoiseInfo()
{
	return m_bWhiteNoise;
}

void CCncPortDiagCtrl::OnUpdateWhiteNoise(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	
	u8 byWhiteNoiseTime = *(u8*)( cTpMsg.GetBody() +  sizeof(u32) );
	
	u32 dwWhiteNoiseNum = *( u32 *)(cTpMsg.GetBody());
	
	PrtMsg( ev_WhiteNoiseRate_Notify, emEventTypecnstoolRecv, "Number%u ,WhiteNoiseRate_Notify[%d] ",dwWhiteNoiseNum+1 ,byWhiteNoiseTime );
	if ( m_bWhiteNoise[dwWhiteNoiseNum] == FALSE )
	{
		m_bWhiteNoise[dwWhiteNoiseNum] = TRUE;
	}
	PostEvent(UI_CNSTOOL_MSG_WhiteNoiseUpdate_NTY,(WPARAM)&dwWhiteNoiseNum,(LPARAM)&byWhiteNoiseTime);
}

//主视频配置
u16 CCncPortDiagCtrl::SetMainAudioInfoCmd( const TTPVideoInfoTool* ptAudioInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_CnSetVedioInfoTool_Cmd );
	pcTpMsg->SetBody( ptAudioInfo, sizeof(TTPVideoInfoTool) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetVedioInfoTool_Cmd, emEventTypecnstoolSend, "MainAudioCmd" );
	return wRet;
}

void CCncPortDiagCtrl::OnVedioSourceInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TTPVideoInfoTool tVideoSourceInfo= *(TTPVideoInfoTool*)(cTpMsg.GetBody());
//	BOOL bChange = FALSE;

	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPVideoInfoTool) );
	if ( bSuccess )
	{
		memset( &m_tVideoSource, 0, sizeof(m_tVideoSource) );
		m_tVideoSource = tVideoSourceInfo;

/*		for( s32 nIndex = 0 ;nIndex < 5; nIndex ++ )
		{
			if ( (m_atDemoSourceName[nIndex].m_emVgaType == emVgaTypeFullScreenCamera)&&
				( strcmp(m_atDemoSourceName[nIndex].m_achAlias,m_tVideoSource.m_atVideoSourceName[emTPC7Vid].m_achSourceName )!= 0 ))
			{
				strcpy(m_atDemoSourceName[nIndex].m_achAlias,m_tVideoSource.m_atVideoSourceName[emTPC7Vid].m_achSourceName);
				bChange = TRUE;
				break;
			}
		}*/
	}
	
/*	if ( bChange == TRUE )
	{
		PostEvent( UI_CNSTOOL_MSG_DisplaySource_Nty, 0, (LPARAM)&bSuccess );				//通知界面更演示源名称  后设置后生效
	}*/
	PrtMsg( ev_CnSetVedioInfoTool_Ind, emEventTypecnstoolRecv, "bSuccess:%d", bSuccess );
	PostEvent( UI_CNSTOOL_MSG_VideoSource_NTY, 0, (LPARAM)&bSuccess );
}


const TTPVideoInfoTool &CCncPortDiagCtrl::GetMainAudioInfo( ) const
{
	return m_tVideoSource;
}

u16 CCncPortDiagCtrl::DefaultMainAudioCmd( const TTPVideoInfoTool* ptAudioInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_CnSetDefVedioInfoTool_Cmd );
	pcTpMsg->SetBody( ptAudioInfo, sizeof(TTPVideoInfoTool) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetDefVedioInfoTool_Cmd, emEventTypecnstoolSend, "DefaultMainAudioCmd" );
	return wRet;
}

void CCncPortDiagCtrl::OnDefaultMainAudioInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	TTPVideoInfoTool tMainAudioInfo= *(TTPVideoInfoTool*)(cTpMsg.GetBody());
//	BOOL bChange = FALSE;

	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPVideoInfoTool) );
	
	if ( bSuccess == TRUE )
	{
		m_tVideoSource = tMainAudioInfo;
/*		for( s32 nIndex = 0 ;nIndex < 5; nIndex ++ )
		{
			if ( (m_atDemoSourceName[nIndex].m_emVgaType == emVgaTypeFullScreenCamera)&&
				( strcmp(m_atDemoSourceName[nIndex].m_achAlias,m_tVideoSource.m_atVideoSourceName[emTPC7Vid].m_achSourceName )!= 0 ))
			{
				strcpy(m_atDemoSourceName[nIndex].m_achAlias,m_tVideoSource.m_atVideoSourceName[emTPC7Vid].m_achSourceName);
				bChange = TRUE;
				break;
			}
		}*/
	}

/*	if ( bChange == TRUE )
	{
		PostEvent( UI_CNSTOOL_MSG_DisplaySource_Nty, 0, (LPARAM)&bSuccess );				//通知界面更演示源名称  后设置后生效
	}*/
	PrtMsg( ev_CnSetDefVedioInfoTool_Ind, emEventTypecnstoolRecv, "bSuccess:%d", bSuccess );
	PostEvent( UI_CNSTOOL_MSG_DefAudio_NTY, 0, (LPARAM)&bSuccess );
}

u16 CCncPortDiagCtrl::SnapShotCmd( )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	EmTpSnapShotType emSnapShotType = EmTpSnatShot_ThreeVideo;

    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tppSetSnapShotCmd );
	pcTpMsg->CatBody(&emSnapShotType,sizeof(emSnapShotType));

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppSetSnapShotCmd, emEventTypecnstoolSend, "ev_tppSetSnapShotCmd" );
	return wRet;
}

void CCncPortDiagCtrl::OnSnapShotInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	EmTpSnapShotType emSnapShotType =*( EmTpSnapShotType *)cTpMsg.GetBody();;
	BOOL bSuccess = *(BOOL *)(cTpMsg.GetBody()+sizeof(EmTpSnapShotType));
	
	if ( emSnapShotType != EmTpSnatShot_ThreeVideo )
	{
		return ;
	}
	PrtMsg( ev_tppSetSnapShotInd, emEventTypecnstoolRecv, "ev_tppSetSnapShotInd bSuccess %d",bSuccess );
	PostEvent( UI_CNSTOOL_SnapShot_Nty, 0, (LPARAM)&bSuccess );
}

void CCncPortDiagCtrl::OnSetRouteInfoNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TRouteCfg tRouteCfg[10];

	memset( tRouteCfg, 0, sizeof(tRouteCfg) );
	m_vecTRouteCfg.clear();
	for( int i = 0; i< TP_ROUTE_COUNT; i++ )
	{
		tRouteCfg[i] = *(TRouteCfg*)( cTpMsg.GetBody() + sizeof(TRouteCfg) * i );
		if( (tRouteCfg[i].dwDstNet == 0) && ( tRouteCfg[i].dwDstNetMask == 0 ) && ( tRouteCfg[i].dwNextIP == 0 ) )
		{
			continue;
		}
		else
		{
			if( ( tRouteCfg[i].dwDstNet == 0 ) && ( tRouteCfg[i].dwDstNetMask == 0 ) && ( tRouteCfg[i].dwNextIP == 4263514284 ) )
			{
				tRouteCfg[i].dwPri = 1;
			}
			bool bhave = false;
			vector<TRouteCfg>::iterator it = m_vecTRouteCfg.begin();
			for ( ; it != m_vecTRouteCfg.end(); it++ )
			{
				if ( it->dwDstNet == tRouteCfg[i].dwDstNet )
				{
					bhave = true;
					break;
				}
			}
			if (!bhave)
			{
				m_vecTRouteCfg.push_back( tRouteCfg[i] );
			}
		}
	}

	PrtMsg( ev_tppRouteInfo_Nty, emEventTypecnstoolRecv, "ev_tppRouteInfo_Nty");
	
	PostEvent( UI_ROUTEINFO_Nty, 0, 0 );
}

void CCncPortDiagCtrl::OnAddRouteInfoInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TRouteCfg tRouteCfg = *(TRouteCfg*)( cTpMsg.GetBody() );
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TRouteCfg) ); 
	if(bSuccess)
	{
		bool bhave = false;
		vector<TRouteCfg>::iterator it = m_vecTRouteCfg.begin();
		for ( ; it != m_vecTRouteCfg.end(); it++ )
		{
			if ( it->dwDstNet == tRouteCfg.dwDstNet )
			{
				bhave = true;
				break;
			}
		}
		if (!bhave)
		{
			m_vecTRouteCfg.push_back( tRouteCfg );
		}
	}
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tRouteCfg.dwDstNet;

	in_addr tAddr1;
	tAddr1.S_un.S_addr = tRouteCfg.dwDstNetMask;

	in_addr tAddr2;
	tAddr2.S_un.S_addr = tRouteCfg.dwNextIP;
	PrtMsg( ev_tppAddRoute_Ind, emEventTypecnstoolRecv, "dwDstNet: %s, dwDstNetMask:%s, dwNextIP: %s, dwPri: %d, bSuccess: %d", inet_ntoa(tAddr), inet_ntoa(tAddr1), 
		inet_ntoa(tAddr2), tRouteCfg.dwPri, bSuccess );
	
	PostEvent( UI_ADDROUTE_Ind, (WPARAM)&bSuccess, 0 );

}

void CCncPortDiagCtrl::OnDelRouteInfoInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TRouteCfg tRouteCfg = *(TRouteCfg*)( cTpMsg.GetBody() );
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TRouteCfg) ); 
	if( bSuccess )
	{
		vector<TRouteCfg>::iterator it;
		for ( it = m_vecTRouteCfg.begin(); it != m_vecTRouteCfg.end(); )
		{
			if ( (tRouteCfg.dwDstNet == it->dwDstNet) && ( tRouteCfg.dwDstNetMask == it->dwDstNetMask) && ( tRouteCfg.dwNextIP == it->dwNextIP ) )
			{
				it = m_vecTRouteCfg.erase(it);
				break;
			}
			it++;
		}
	}

	in_addr tAddr;
	tAddr.S_un.S_addr = tRouteCfg.dwDstNet;
	
	in_addr tAddr1;
	tAddr1.S_un.S_addr = tRouteCfg.dwDstNetMask;
	
	in_addr tAddr2;
	tAddr2.S_un.S_addr = tRouteCfg.dwNextIP;
	PrtMsg( ev_tppDelRoute_Ind, emEventTypecnstoolRecv, "dwDstNet: %s, dwDstNetMask:%s, dwNextIP: %s, dwPri: %d, bSuccess: %d", inet_ntoa(tAddr), inet_ntoa(tAddr1), 
		inet_ntoa(tAddr2), tRouteCfg.dwPri, bSuccess );

	PostEvent( UI_DelROUTE_Ind, (WPARAM)&bSuccess, 0 );
}

u16 CCncPortDiagCtrl::SetDemonStrationCmd( const TVgaInfo *ptDisplaySource,
										  const TTPDualDisplayStrategy *ptDualDisplayStrategy,
										  const EmVgaType emDefaultDisplay )
{
	TVgaInfo tDisplaySource;
	for ( s32 nIndex = 0 ;nIndex <5; nIndex ++ )
	{
		if (ptDisplaySource[nIndex].m_emVgaType == emDefaultDisplay )
		{
			memcpy(&tDisplaySource,&ptDisplaySource[nIndex],sizeof(TVgaInfo));
		}
	}
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_CnSetDisplaySourceTool_Cmd );
	pcTpMsg->SetBody( ptDisplaySource, sizeof(TVgaInfo)*5 );
	pcTpMsg->CatBody( ptDualDisplayStrategy,sizeof(TTPDualDisplayStrategy));
	pcTpMsg->CatBody( &tDisplaySource,sizeof(TVgaInfo));
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetDisplaySourceTool_Cmd, emEventTypecnstoolSend, "DisplaySourceCmd" );
	return wRet;
}

void CCncPortDiagCtrl::OnDisplaySourceInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	TVgaInfo tDefaultDisplay;
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(m_atDemoSourceName) +
		sizeof( TTPDualDisplayStrategy )+sizeof(TVgaInfo) );
//	BOOL bChange = FALSE;

	if ( bSuccess == TRUE )
	{
		for ( int i = 0; i < CNS_VGA_TYPE_NUM; i++ )
		{
			m_atDemoSourceName[i] = *(TVgaInfo*)( cTpMsg.GetBody() + i * sizeof(TVgaInfo) );
			
		/*	if ( (m_atDemoSourceName[i].m_emVgaType == emVgaTypeFullScreenCamera)&&
				( strcmp(m_atDemoSourceName[i].m_achAlias,m_tVideoSource.m_atVideoSourceName[emTPC7Vid].m_achSourceName )!= 0 ))
			{
				strcpy(m_tVideoSource.m_atVideoSourceName[emTPC7Vid].m_achSourceName,m_atDemoSourceName[i].m_achAlias);
				bChange = TRUE;
			}*/
		}

		m_tDisplayStrategy = *( TTPDualDisplayStrategy *)( cTpMsg.GetBody() + CNS_VGA_TYPE_NUM * sizeof(TVgaInfo));

		tDefaultDisplay = * ( TVgaInfo * )( cTpMsg.GetBody() + sizeof(m_atDemoSourceName) +
		sizeof( TTPDualDisplayStrategy ) );
		m_emDefaultDisplay = tDefaultDisplay.m_emVgaType;
	}

	PrtMsg( ev_CnSetDisplaySourceTool_Ind, emEventTypecnstoolRecv, "bSuccess:%d", bSuccess );

/*	if ( bChange == TRUE )
	{
//		PostEvent( UI_CNSTOOL_MSG_VideoSource_NTY, 0, (LPARAM)&bSuccess );					//通知界面更新主视频名称  后设置后生效
	}*/
	PostEvent( UI_CNSTOOL_MSG_DisplaySource_Nty, 0, (LPARAM)&bSuccess );
}

TVgaInfo *CCncPortDiagCtrl::GetDisplaySourceInfo( )
{
	return m_atDemoSourceName;
}

TTPDualDisplayStrategy &CCncPortDiagCtrl::GetDisplayStrategyInfo( )
{
	return m_tDisplayStrategy;
}

EmVgaType CCncPortDiagCtrl::GetDefaultDisplay( )
{
	return m_emDefaultDisplay;
}

u16 CCncPortDiagCtrl::SetDefaultDemonStrationCmd( const TVgaInfo *ptDisplaySource,
								   const TTPDualDisplayStrategy *ptDualDisplayStrategy,
								   const EmVgaType emDefaultDisplay )
{
	TVgaInfo tDisplaySource;
	for ( s32 nIndex = 0 ;nIndex <5; nIndex ++ )
	{
		if (ptDisplaySource[nIndex].m_emVgaType == emDefaultDisplay )
		{
			memcpy(&tDisplaySource,&ptDisplaySource[nIndex],sizeof(TVgaInfo));
		}
	}
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_CnSetDefDisplaySrcTool_Cmd );
	pcTpMsg->SetBody( ptDisplaySource, sizeof(TVgaInfo)*5 );
	pcTpMsg->CatBody( ptDualDisplayStrategy,sizeof(TTPDualDisplayStrategy));
	pcTpMsg->CatBody( &tDisplaySource,sizeof(TVgaInfo));

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetDefDisplaySrcTool_Cmd, emEventTypecnstoolSend, "DefaultDisplaySourceCmd" );
	return wRet;
}

void CCncPortDiagCtrl::OnDefaultDisplaySourceInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TVgaInfo tDefaultDisplay;
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(m_atDemoSourceName) +
		sizeof( TTPDualDisplayStrategy )+sizeof(TVgaInfo) );
//	BOOL bChange= FALSE;

	if ( bSuccess == TRUE )
	{
		for ( int i = 0; i < 5; i++ )
		{
			m_atDemoSourceName[i] = *(TVgaInfo*)( cTpMsg.GetBody() + i * sizeof(TVgaInfo) );

	/*		if ( (m_atDemoSourceName[i].m_emVgaType == emVgaTypeFullScreenCamera)&&
				( strcmp(m_atDemoSourceName[i].m_achAlias,m_tVideoSource.m_atVideoSourceName[emTPC7Vid].m_achSourceName )!= 0 ))
			{
				strcpy(m_tVideoSource.m_atVideoSourceName[emTPC7Vid].m_achSourceName,m_atDemoSourceName[i].m_achAlias);
				bChange = TRUE;
			}*/
		}
		
		m_tDisplayStrategy = *( TTPDualDisplayStrategy *)( cTpMsg.GetBody() + 5 * sizeof(TVgaInfo));
		tDefaultDisplay = * ( TVgaInfo * )( cTpMsg.GetBody() + sizeof(m_atDemoSourceName) +
			sizeof( TTPDualDisplayStrategy ) );
		m_emDefaultDisplay = tDefaultDisplay.m_emVgaType;
	}
/*	
//	if ( bChange == TRUE )
	{
		PostEvent( UI_CNSTOOL_MSG_VideoSource_NTY, 0, (LPARAM)&bSuccess );					//通知界面更新主视频名称  后设置后生效
	}
*/	
	PrtMsg( ev_CnSetDefDisplaySrcTool_Ind, emEventTypecnstoolRecv, "bSuccess:%d", bSuccess );
	
	PostEvent( UI_CNSTOOL_MSG_DefaultDisplaySource_Nty, 0, (LPARAM)&bSuccess );
}

//图像参数调节
u16 CCncPortDiagCtrl::SetParameterCmd(const TTPImageAdjustParam * pImageAdjustParam )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_CnSetImageAdjust_Cmd );
	pcTpMsg->SetBody( pImageAdjustParam, sizeof(TTPImageAdjustParam)*3 );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetImageAdjust_Cmd, emEventTypecnstoolSend, "ImageParameterCmd" );
	return wRet;
}

u16 CCncPortDiagCtrl::RouteMngAddCmd(const TRouteCfg& tRouteCfg)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_tppAddRoute_Cmd );
	pcTpMsg->SetBody( &tRouteCfg, sizeof(TRouteCfg) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tRouteCfg.dwDstNet;
	
	in_addr tAddr1;
	tAddr1.S_un.S_addr = tRouteCfg.dwDstNetMask;
	
	in_addr tAddr2;
	tAddr2.S_un.S_addr = tRouteCfg.dwNextIP;
	PrtMsg( ev_tppAddRoute_Cmd, emEventTypecnstoolSend, "dwDstNet: %s, dwDstNetMask:%s, dwNextIP: %s, dwPri: %d", inet_ntoa(tAddr), inet_ntoa(tAddr1), 
		inet_ntoa(tAddr2), tRouteCfg.dwPri );

	return wRet;
}

u16 CCncPortDiagCtrl::RouteMngDelCmd(const TRouteCfg& tRouteCfg)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
	pcTpMsg->SetEvent( ev_tppDelRoute_Cmd );
	pcTpMsg->SetBody( &tRouteCfg, sizeof(TRouteCfg) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tRouteCfg.dwDstNet;
	
	in_addr tAddr1;
	tAddr1.S_un.S_addr = tRouteCfg.dwDstNetMask;
	
	in_addr tAddr2;
	tAddr2.S_un.S_addr = tRouteCfg.dwNextIP;
	PrtMsg( ev_tppDelRoute_Cmd, emEventTypecnstoolSend, "dwDstNet: %s, dwDstNetMask:%s, dwNextIP: %s, dwPri: %d", inet_ntoa(tAddr), inet_ntoa(tAddr1), 
		inet_ntoa(tAddr2), tRouteCfg.dwPri );

	return 0;
}

void CCncPortDiagCtrl::OnImageAdjustInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(m_atImageAdjust) );
		u16 length = cTpMsg.GetBodyLen();
	if ( bSuccess == TRUE )
	{
		for ( s32 nINdex=0 ; nINdex < 3 ; nINdex ++ )
		{
			m_atImageAdjust[nINdex] = *(TTPImageAdjustParam*)( cTpMsg.GetBody() + nINdex * sizeof(TTPImageAdjustParam) );
		}
	}
	PrtMsg( ev_CnSetImageAdjust_Ind, emEventTypecnstoolRecv, "bSuccess:%d", bSuccess );
	
	PostEvent( UI_CNSTOOL_MSG_ImageAdjust_Nty, 0, (LPARAM)&bSuccess );
}

TTPImageAdjustParam * CCncPortDiagCtrl::GetImageParam()
{
	return m_atImageAdjust;
}

u16 CCncPortDiagCtrl::SetDefParameterCmd(const TTPImageAdjustParam * pImageAdjustParam )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_CnSetDefaultImageAdjust_Cmd );
	pcTpMsg->SetBody( pImageAdjustParam, sizeof(TTPImageAdjustParam)*3 );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetDefaultImageAdjust_Cmd, emEventTypecnstoolSend, "DefaultImageParameterCmd" );
	return wRet;
}

void CCncPortDiagCtrl::OnDefaultImageAdjustInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody());
	u16 length = cTpMsg.GetBodyLen();
	PrtMsg( ev_CnSetDefaultImageAdjust_Ind, emEventTypecnstoolRecv, "bSuccess:%d", bSuccess );
	
	PostEvent( UI_CNSTOOL_MSG_DefaultImageAdjust_Nty, 0, (LPARAM)&bSuccess );
}

u16 CCncPortDiagCtrl::SetCaptureStateCmd(const BOOL& bCapture) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_TppToolgetPak_Cmd );
	pcTpMsg->SetBody( &bCapture,sizeof( BOOL ) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TppToolgetPak_Cmd, emEventTypeCnsSend, "Capture:%d ", bCapture);
	return wRet;
}





