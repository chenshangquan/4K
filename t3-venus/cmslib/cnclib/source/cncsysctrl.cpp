#include "StdAfx.h"
#include "cncsysctrl.h"

CCncSysCtrl::CCncSysCtrl( CCnsSession &cSession ):CCncSysCtrlIF()
{
	m_pSession = &cSession;
	BuildEventsMap();
	m_byCameraSel = 0;
	m_pTCnCameraCfg = NULL;
}

CCncSysCtrl::~CCncSysCtrl()
{

}

void CCncSysCtrl::BuildEventsMap()
{
	REG_PFUN(OSP_DISCONNECT, CCncSysCtrl::OnLinkBreak);
	REG_PFUN(ev_tppGetSysInfo_Rsp, CCncSysCtrl::OnSysInfoRsp);
	REG_PFUN(ev_tppGetSysInfo_Nty, CCncSysCtrl::OnSysInfoNty);
	REG_PFUN(ev_tppCnConfInfo_Nty, CCncSysCtrl::OnCnConfInfoNty);
	REG_PFUN(ev_Cn_CameraCfgNty, CCncSysCtrl::OnCameraCfgNty);
	REG_PFUN(ev_Cn_CameraAutoExposureInd, CCncSysCtrl::OnAutoExposureInd);
	REG_PFUN(ev_Cn_Camera3DNRInd, CCncSysCtrl::OnCam3DNRInd);
	REG_PFUN(ev_Cn_CameraApertureInd, CCncSysCtrl::OnCamApertureInd);
	REG_PFUN(ev_Cn_CameraAutoFocusInd, CCncSysCtrl::OnCamAutoFocusInd);
	REG_PFUN(ev_Cn_CameraSelectInd, CCncSysCtrl::OnCamSelInd);
	REG_PFUN(ev_Cn_CameraResetInd, CCncSysCtrl::OnCamResetInd);
	REG_PFUN(ev_Cn_CameraZoomInd, CCncSysCtrl::OnCamZoomInd);
	REG_PFUN(ev_Cn_CameraOSDShowInd, CCncSysCtrl::OnCamOSDInd);
	REG_PFUN(ev_Cn_CameraFocusInd, CCncSysCtrl::OnCamFocusInd);
	REG_PFUN(ev_Cn_CameraPersetSaveInd, CCncSysCtrl::OnCamPresetSaveInd);
	REG_PFUN(ev_Cn_CameraPresetInd, CCncSysCtrl::OnCamPresetMoveInd);
	REG_PFUN(ev_Cn_CameraGainInd, CCncSysCtrl::OnCamGainInd);
	REG_PFUN(ev_Cn_CameraShutSpdInd,CCncSysCtrl::OnCamShutSpdCInd);
	REG_PFUN(ev_Cn_CameraBackLightInd, CCncSysCtrl::OnCamBackLightInd);
	REG_PFUN(ev_Cn_CameraAutoWBInd, CCncSysCtrl::OnCamAutoWBInd);
	REG_PFUN(ev_Cn_CameraRGainInd, CCncSysCtrl::OnCamRGainInd);
	REG_PFUN(ev_Cn_CameraBGainInd, CCncSysCtrl::OnCamBGainInd);
	REG_PFUN(ev_Cn_CameraPicSceneModeInd, CCncSysCtrl::OnCamPicSceneModeInd);
	REG_PFUN(ev_Cn_CameraGammaInd, CCncSysCtrl::OnCamGammaInd);
	REG_PFUN(ev_Cn_CameraPicSceAptInd, CCncSysCtrl::OnCamPicSceAptInd);
	REG_PFUN(ev_Cn_CameraContrastInd, CCncSysCtrl::OnCamContrastInd);
	REG_PFUN(ev_Cn_CameraHueInd, CCncSysCtrl::OnCamHueInd);
	REG_PFUN(ev_Cn_CameraSaturatInd, CCncSysCtrl::OnCamSaturatInd);
	REG_PFUN(ev_Cn_CameraBrightInd, CCncSysCtrl::OnCamBrightInd);
	REG_PFUN(ev_Cn_CameraNRStmCleanInd, CCncSysCtrl::OnCamNRStmCleanInd);
	REG_PFUN(ev_Cn_SetCameraZoomInd, CCncSysCtrl::OnSetCameraZoomInd);
	REG_PFUN(ev_Cn_CameraPowerOnNty, CCncSysCtrl::OnCameraPowerOnNty);
    REG_PFUN(ev_Cn_CamCfg_Ind, CCncSysCtrl::OnMoon904KCamCfgInd);
    REG_PFUN(ev_TpSrcOffLine_Nty, CCncSysCtrl::OnSrcOffLineNty);
}

void CCncSysCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CCncSysCtrl, cMsg);
}

void CCncSysCtrl::OnTimeOut(u16 wEvent)
{

}

void CCncSysCtrl::OnLinkBreak(const CMessage& cMsg)
{
	PrtMsg( OSP_DISCONNECT, emEventTypecnstoolRecv,"[CCncSysCtrl::OnLinkBreak]清空配置信息" );
	memset( &m_tSysInfo, 0, sizeof(m_tSysInfo) );
    memset( &m_tConfStatus, 0, sizeof(m_tConfStatus) );
    memset( &m_tVideoParam, 0, sizeof(m_tVideoParam) );
	m_byCameraSel = 0;
	memset( &m_tCnCameraCfg1, 0, sizeof(TCnCameraCfg) );
	memset( &m_tCnCameraCfg2, 0, sizeof(TCnCameraCfg) );
	memset( &m_tCnCameraCfg3, 0, sizeof(TCnCameraCfg) );
	m_pTCnCameraCfg = NULL;
}

//cpu/内存的信息
u16 CCncSysCtrl::ReqSysInfo()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetEvent(ev_tppGetSysInfo_Req);

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg(ev_tppGetSysInfo_Req, emEventTypecnstoolSend, "");
	return wRet;
}

const TTPSysInfo& CCncSysCtrl::GetSysInfo()const
{
	return m_tSysInfo;
}

void CCncSysCtrl::OnSysInfoRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPSysInfo tSysInfo = *(TTPSysInfo*)(cTpMsg.GetBody());
	PrtMsg( ev_tppGetSysInfo_Rsp, emEventTypecnstoolRecv, "" );
//	PostEvent( , (WPARAM)&tSysInfo, 0 );
}

void CCncSysCtrl::OnSysInfoNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPSysInfo tSysInfo = *(TTPSysInfo*)(cTpMsg.GetBody());
	m_tSysInfo = tSysInfo;
	PrtMsg( ev_tppGetSysInfo_Nty, emEventTypecnstoolRecv, "CPU:%u,RAM:%u", tSysInfo.m_byCpuRate, tSysInfo.m_dwAllocByte*100/tSysInfo.m_dwTotalByte );
	PostEvent( UI_CNSTOOL_MSG_CPURAM_NTY, 0, 0 );
}

//会议信息
const TTPCnsConfStatus& CCncSysCtrl::GetCnConfStatus()const
{
	return m_tConfStatus;
}
const TTPCnConfInfo& CCncSysCtrl::GetCnConfVideoParam()const
{
	return m_tVideoParam;
}

void CCncSysCtrl::OnCnConfInfoNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPCnsConfStatus tConfStatus = *(TTPCnsConfStatus*)(cTpMsg.GetBody());
	TTPCnConfInfo tVideoParam = *(TTPCnConfInfo*)(cTpMsg.GetBody() + sizeof(TTPCnsConfStatus));

	m_tConfStatus = tConfStatus;
	m_tVideoParam = tVideoParam;
	PrtMsg( ev_tppCnConfInfo_Nty, emEventTypecnstoolRecv, "ConfName: %s, ConfProtocol: %d, ConfRate: %d, ConfHold: %d,\
 HPBP: %d, ConfRes: %d, ConfFrameRate: %d, emTpAudioFormat: %d, DualCallRate: %d",
		tConfStatus.achConfName, tConfStatus.m_emConfProtocal, tVideoParam.tCnVideoParam.wChanMaxBitrate, 
		tVideoParam.tCnVideoParam.emFormat, tVideoParam.tCnVideoParam.m_dwProfile, tVideoParam.tCnVideoParam.emRes, tVideoParam.tCnVideoParam.byFrameRate, tVideoParam.emTpAudioFormat, tVideoParam.wDualCallBit );
	PostEvent( UI_CNSTOOL_MSG_CONF_NTY, 0, 0);
}

//摄像头信息
void CCncSysCtrl::OnCameraCfgNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	m_tCnCameraCfg1 = *(TCnCameraCfg*)( cTpMsg.GetBody() );
	m_tCnCameraCfg2 = *(TCnCameraCfg*)( cTpMsg.GetBody() + sizeof(TCnCameraCfg) );
	m_tCnCameraCfg3 = *(TCnCameraCfg*)( cTpMsg.GetBody() + sizeof(TCnCameraCfg) + sizeof(TCnCameraCfg) );
	m_byCameraSel = *(u8*)( cTpMsg.GetBody() + 3*sizeof(TCnCameraCfg) );


	PrtMsg( ev_Cn_CameraCfgNty, emEventTypecnstoolRecv, _T("ev_Cn_CameraCfgNty") );
	PostEvent( UI_CNSTOOL_CAMERA_CFG_NTY, NULL, NULL );
	PostEvent( UI_CNSTOOL_CAMERA_SELECT_IND, NULL, (LPARAM)TRUE );
}

u16 CCncSysCtrl::CamSelCmd( const u8& byCameraIndx )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &byCameraIndx, sizeof(u8) );
	pcTpMsg->SetEvent(ev_Cn_CameraSelectCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraSelectCmd, emEventTypecnstoolSend, "" );
	return wRet;
}

u16 CCncSysCtrl::GetCamCfgAll( vector<TCnCameraCfg>& vecTCnCameraCfg )
{
	vecTCnCameraCfg.push_back( m_tCnCameraCfg1 );
	vecTCnCameraCfg.push_back( m_tCnCameraCfg2 );
	vecTCnCameraCfg.push_back( m_tCnCameraCfg3 );

	return NO_ERROR;
}

TCnCameraCfg CCncSysCtrl::GetCamCfg()
{
	SetCameraCfgPtr();
	return *m_pTCnCameraCfg;
}

void CCncSysCtrl::OnCamSelInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	m_byCameraSel = *(u8*)( cTpMsg.GetBody() );
	BOOL bSelCam = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	SetCameraCfgPtr();

	PrtMsg( ev_Cn_CameraSelectInd, emEventTypecnstoolRecv, "byCameraSel:%d", m_byCameraSel );
	PostEvent( UI_CNSTOOL_CAMERA_SELECT_IND, NULL, (LPARAM)bSelCam );
}

u8 CCncSysCtrl::GetCamSel()const
{
	return m_byCameraSel;
}

u16 CCncSysCtrl::CamResetCmd()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());

	pcTpMsg->SetEvent(ev_Cn_CameraResetCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraResetCmd, emEventTypecnstoolSend, "" );
	return wRet;
}

void CCncSysCtrl::OnCamResetInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TCnCameraCfg tCnCameraCfg = *(TCnCameraCfg*)( cTpMsg.GetBody() );
	u8 byCamIndex = *(u8*)( cTpMsg.GetBody() + sizeof(TCnCameraCfg) );
	BOOL bSelCam = *(BOOL*)( cTpMsg.GetBody() + sizeof(TCnCameraCfg) + sizeof(u8) );

	if ( bSelCam )
	{
		switch ( byCamIndex )
		{
		case 0:
			{
				m_tCnCameraCfg1 = tCnCameraCfg;
				break;
			}
		case 1:
			{
				m_tCnCameraCfg2 = tCnCameraCfg;
				break;
			}
		case 2:
			{
				m_tCnCameraCfg3 = tCnCameraCfg;
				break;
			}
		default:
			break;
		}
	}

	PrtMsg( ev_Cn_CameraResetInd, emEventTypecnstoolRecv, "" );
	PostEvent( UI_CNSTOOL_CAMERA_RESET_IND, NULL, (LPARAM)bSelCam );
}

u16 CCncSysCtrl::SetCamZoomCmd( const EmZoom& emZoom, const EmZoomStatus& emZoomStatus )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emZoom, sizeof(EmZoom) );
	pcTpMsg->CatBody( &emZoomStatus, sizeof(EmZoomStatus) );
	pcTpMsg->SetEvent(ev_Cn_CameraZoomCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraZoomCmd, emEventTypecnstoolSend, "emZoom:%d , emZoomStatus:%d", emZoom , emZoomStatus );
	return wRet;
}

void CCncSysCtrl::OnCamZoomInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	EmZoom emZoom = *(EmZoom*)( cTpMsg.GetBody() );
	m_pTCnCameraCfg->wZoom = *(u16*)( cTpMsg.GetBody() + sizeof(EmZoom) );
	BOOL bCamZoom = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmZoom) + sizeof(u16) );
	PrtMsg( ev_Cn_CameraZoomInd, emEventTypecnstoolRecv, "EmZoom:%d, wZoom:%d, BOOL:%d", emZoom, m_pTCnCameraCfg->wZoom, bCamZoom );
	PostEvent( UI_CNSTOOL_SET_CAMERA_ZOOM_IND, /*(WPARAM)emZoom*/0, (LPARAM)bCamZoom );
}

u16 CCncSysCtrl::SetCamOSDCmd( const EmOSDShow& emOSDShow )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emOSDShow, sizeof(EmOSDShow) );

	pcTpMsg->SetEvent(ev_Cn_CameraOSDShowCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraOSDShowCmd, emEventTypecnstoolSend, "SetCamOSDCmd:%d", emOSDShow );
	return wRet;
}
EmOSDShow CCncSysCtrl::GetCamOSD()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->emOSDShow;
}
void CCncSysCtrl::OnCamOSDInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

    m_pTCnCameraCfg->emOSDShow = *(EmOSDShow*)( cTpMsg.GetBody() );
	BOOL bCamOSD = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmOSDShow) );

	PrtMsg( ev_Cn_CameraOSDShowInd, emEventTypecnstoolRecv, "EmOSDShow:%d,BOOL:%d", m_pTCnCameraCfg->emOSDShow, bCamOSD );
	PostEvent( UI_CNSTOOL_CAMERA_OSDSHOW_IND, NULL, (LPARAM)bCamOSD );
}

u16 CCncSysCtrl::SetCamAutoFocusCmd(const EmFocusMode& emFocusMode)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emFocusMode, sizeof(EmFocusMode) );

	pcTpMsg->SetEvent(ev_Cn_CameraAutoFocusCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraAutoFocusCmd, emEventTypecnstoolSend, "EmFocusMode:%d", emFocusMode );
	return wRet;
}

void CCncSysCtrl::OnCamAutoFocusInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	EmFocusMode emFocusMode = *(EmFocusMode*)( cTpMsg.GetBody() );
	BOOL bCamAutoFocus = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmFocusMode) );
	PrtMsg( ev_Cn_CameraAutoFocusInd, emEventTypecnstoolRecv, "EmFocusMode:%d, BOOL:%d", emFocusMode, bCamAutoFocus );
	PostEvent( UI_CNSTOOL_CAMERA_AUTO_FOCUS_IND, (WPARAM)emFocusMode, (LPARAM)bCamAutoFocus );
}

u16 CCncSysCtrl::SetCamFocusCmd( const EmFocus& emFocus, const EmCnAction& emCnAction )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emFocus, sizeof(EmFocus) );
	pcTpMsg->CatBody( &emCnAction, sizeof(EmCnAction) );
	pcTpMsg->SetEvent(ev_Cn_CameraFocusCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraFocusCmd, emEventTypecnstoolSend, "EmFocus:%d, EmCnAction:%d", emFocus, emCnAction );
	return wRet;
}

void CCncSysCtrl::OnCamFocusInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	EmFocus emFocus = *(EmFocus*)( cTpMsg.GetBody() );
	BOOL bCamFocus = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmFocus) );
	PrtMsg( ev_Cn_CameraFocusInd, emEventTypecnstoolRecv, "EmFocus:%d, BOOL:%d", emFocus, bCamFocus );
	PostEvent( UI_CNSTOOL_CAMERA_FOCUS_IND, (WPARAM)emFocus, (LPARAM)bCamFocus );
}

u16 CCncSysCtrl::CamPresetSaveCmd()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());

	pcTpMsg->SetEvent(ev_Cn_CameraPersetSaveCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraPersetSaveCmd, emEventTypecnstoolSend, "CamPresetSaveCmd" );
	return wRet;
}

void CCncSysCtrl::OnCamPresetSaveInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bCamPresetSave = *(BOOL*)( cTpMsg.GetBody() );
	PrtMsg( ev_Cn_CameraPersetSaveInd, emEventTypecnstoolRecv, "BOOL:%d", bCamPresetSave );
	PostEvent( UI_CNSTOOL_CAMERA_PERSET_SAVE_IND, 0, (LPARAM)bCamPresetSave );
}

u16 CCncSysCtrl::SetCamPresetMoveCmd( const BOOL& bPresetMove )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &bPresetMove, sizeof(BOOL) );
	
	pcTpMsg->SetEvent(ev_Cn_CameraPresetCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraPresetCmd, emEventTypecnstoolSend, "SetCamPresetCmd:%d", bPresetMove );
	return wRet;
}

void CCncSysCtrl::OnCamPresetMoveInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTCnCameraCfg->bUsed = *(BOOL*)( cTpMsg.GetBody() );
	BOOL bCamPresetMove = *(BOOL*)( cTpMsg.GetBody() + sizeof(BOOL) );
	
	PrtMsg( ev_Cn_CameraPresetInd, emEventTypecnstoolRecv, "bUsed:%d,BOOL:%d", m_pTCnCameraCfg->bUsed, bCamPresetMove );
	PostEvent( UI_CNSTOOL_CAMERA_PERSET_MOVE_IND, NULL, (LPARAM)bCamPresetMove );
}

BOOL CCncSysCtrl::GetCamPresetMove()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	return m_pTCnCameraCfg->bUsed;
}


u16 CCncSysCtrl::CamAutoExposureCmd( const EmExpMode& emExpAuto )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emExpAuto, sizeof(EmExpMode) );	
	pcTpMsg->SetEvent(ev_Cn_CameraAutoExposureCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraAutoExposureCmd, emEventTypecnstoolSend, "CamAutoExposureCmd:%d", emExpAuto );
	return wRet;
}

EmExpMode CCncSysCtrl::GetCamExpMode()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	return m_pTCnCameraCfg->emExpMode;
}

void CCncSysCtrl::OnAutoExposureInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->emExpMode = *(EmExpMode*)( cTpMsg.GetBody() );
	BOOL bAutoExposure = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmExpMode) );

	PrtMsg( ev_Cn_CameraAutoExposureInd, emEventTypecnstoolRecv, "EmExpMode:%d, AutoExposureInd:%d", m_pTCnCameraCfg->emExpMode, bAutoExposure );
	PostEvent( UI_CNSTOOL_CAMERA_AUTO_EXPOSURE_IND, NULL, (LPARAM)bAutoExposure );
}

u16 CCncSysCtrl::CamGainCmd( const EmGain& emGain )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emGain, sizeof(EmGain) );
	pcTpMsg->SetEvent(ev_Cn_CameraGainCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraGainCmd, emEventTypecnstoolSend, "CamGainCmd:%d", emGain );
	return wRet;
}

EmGain CCncSysCtrl::GetCamGain()
{
	if (m_pTCnCameraCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->emGain;
}

void CCncSysCtrl::OnCamGainInd(const CMessage& cMsg)
{
	if (m_pTCnCameraCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->emGain = *(EmGain*)( cTpMsg.GetBody() );
	BOOL bCamGain = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmGain) );
	PrtMsg( ev_Cn_CameraGainInd, emEventTypecnstoolRecv, "EmGain:%d, BOOL:%d", m_pTCnCameraCfg->emGain, bCamGain );
	PostEvent( UI_CNSTOOL_CAMERA_GAIN_IND, NULL, (LPARAM)bCamGain );
}

u16 CCncSysCtrl::CamShutSpdCmd( const EmShutSpd& emShutSpd )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emShutSpd, sizeof(EmGain) );
	pcTpMsg->SetEvent(ev_Cn_CameraShutSpdCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraShutSpdCmd, emEventTypecnstoolSend, "CamShutSpdCmd:%d", emShutSpd );
	return wRet;
}

EmShutSpd CCncSysCtrl::GetCamShutSpd()
{
	if (m_pTCnCameraCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->emShutSpd;
}

void CCncSysCtrl::OnCamShutSpdCInd(const CMessage& cMsg)
{
	if (m_pTCnCameraCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->emShutSpd = *(EmShutSpd*)( cTpMsg.GetBody() );
	BOOL bCamShutSpdC = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmShutSpd) );
	PrtMsg( ev_Cn_CameraShutSpdInd, emEventTypecnstoolRecv, "EmShutSpd:%d, BOOL:%d", m_pTCnCameraCfg->emShutSpd, bCamShutSpdC );
	PostEvent( UI_CNSTOOL_CAMERA_SHUT_SPD_IND, NULL, (LPARAM)bCamShutSpdC );
}

u16 CCncSysCtrl::CamBackLightCmd( const EmBackLightType& emBackLightType, const u8& byMulti )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emBackLightType, sizeof(EmBackLightType) );
	pcTpMsg->CatBody( &byMulti, sizeof(u8) );
	pcTpMsg->SetEvent(ev_Cn_CameraBackLightCmd);

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraBackLightCmd, emEventTypecnstoolSend, "CamBackLightCmd:%d, byMulti:%d", emBackLightType, byMulti );
	return wRet;
}

EmBackLightType CCncSysCtrl::GetCamBackLightType()
{
	if (m_pTCnCameraCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->emBackLightType;
}

u8 CCncSysCtrl::GetCamBackLightIndex()
{
	if (m_pTCnCameraCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->byMulti;
}

void CCncSysCtrl::OnCamBackLightInd(const CMessage& cMsg)
{
	if (m_pTCnCameraCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

    m_pTCnCameraCfg->emBackLightType = *(EmBackLightType*)( cTpMsg.GetBody() );
	m_pTCnCameraCfg->byMulti = *(u8*)( cTpMsg.GetBody() + sizeof(EmBackLightType) );
	BOOL bCamBackLight = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmBackLightType) + sizeof(u8) );
	PrtMsg( ev_Cn_CameraBackLightInd, emEventTypecnstoolRecv, "EmBackLightType:%d, byIndex:%d, BOOL:%d", m_pTCnCameraCfg->emBackLightType, m_pTCnCameraCfg->byMulti, bCamBackLight );
	PostEvent( UI_CNSTOOL_CAMERA_BACK_LIGHT_IND, NULL, (LPARAM)bCamBackLight );
}

u16 CCncSysCtrl::CamAperture( const u8& byAperture)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &byAperture, sizeof(u8) );
	pcTpMsg->SetEvent(ev_Cn_CameraApertureCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraApertureCmd, emEventTypecnstoolSend, "byAperture:%d", byAperture );
	return wRet;
}

u8 CCncSysCtrl::GetCamAperture()
{
	if (m_pTCnCameraCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->byApt;
}

void CCncSysCtrl::OnCamApertureInd(const CMessage& cMsg)
{
	if (m_pTCnCameraCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->byApt = *(u8*)( cTpMsg.GetBody() );
	BOOL bCamAperture = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	PrtMsg( ev_Cn_CameraApertureInd, emEventTypecnstoolRecv, "CamApertureInd:%d, BOOL:%d", m_pTCnCameraCfg->byApt, bCamAperture );
	PostEvent( UI_CNSTOOL_CAMERA_APERTURE_IND, NULL, (LPARAM)bCamAperture );
}

u16 CCncSysCtrl::CamAutoWBCmd( const EmWBMode& emWBMode )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emWBMode, sizeof(EmWBMode) );
	pcTpMsg->SetEvent(ev_Cn_CameraAutoWBCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraAutoWBCmd, emEventTypecnstoolSend, "CamAutoWBCmd:%d", emWBMode );
	return wRet;
}

EmWBMode CCncSysCtrl::GetCamWBMode()
{
	if (m_pTCnCameraCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	return m_pTCnCameraCfg->emWBMode;
}

u16 CCncSysCtrl::SetLoadCameraFileNty()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetEvent(ev_Cn_LoadCameraFileNty);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_LoadCameraFileNty, emEventTypecnstoolSend, _T("SetLoadCameraFileNty") );
	return wRet;
}


void CCncSysCtrl::OnCamAutoWBInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->emWBMode = *(EmWBMode*)( cTpMsg.GetBody() );
	BOOL bCamAutoWB = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmWBMode) );

	PrtMsg( ev_Cn_CameraAutoWBInd, emEventTypecnstoolRecv, "EmWBMode:%d, CamAutoWBInd:%d", m_pTCnCameraCfg->emWBMode, bCamAutoWB );
	PostEvent( UI_CNSTOOL_CAMERA_AUTO_WB_IND, NULL, (LPARAM)bCamAutoWB );
}

u16 CCncSysCtrl::CamRGainCmd( const u16& wRGain )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&wRGain, sizeof(u16));
	pcTpMsg->SetEvent(ev_Cn_CameraRGainCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraRGainCmd, emEventTypecnstoolSend, "wRGain:%d", wRGain );
	return wRet;
}

u16 CCncSysCtrl::GetCamRGain()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	return m_pTCnCameraCfg->wRGain;
}

void CCncSysCtrl::OnCamRGainInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);
	m_pTCnCameraCfg->wRGain = *(u16*)( cTpMsg.GetBody() );
	BOOL bCamRGain = *(BOOL*)( cTpMsg.GetBody() + sizeof(u16) );
	PrtMsg( ev_Cn_CameraRGainInd, emEventTypecnstoolRecv, "wRGain:%d, bCamRGain:%d", m_pTCnCameraCfg->wRGain, bCamRGain );
	PostEvent( UI_CNSTOOL_CAMERA_RGAIN_IND, NULL, (LPARAM)bCamRGain );
}

u16 CCncSysCtrl::CamBGainCmd( const u16& wBGain )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&wBGain, sizeof(u16));
	pcTpMsg->SetEvent(ev_Cn_CameraBGainCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraBGainCmd, emEventTypecnstoolSend, "wBGain:%d", wBGain );
	return wRet;
}

u16 CCncSysCtrl::GetCamBGain()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->wBGain;
}

void CCncSysCtrl::OnCamBGainInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->wBGain = *(u16*)( cTpMsg.GetBody() );
	BOOL bCamBGain = *(BOOL*)( cTpMsg.GetBody() + sizeof(u16) );
	PrtMsg( ev_Cn_CameraBGainInd, emEventTypecnstoolRecv, "wBGain:%d, bCamBGain:%d", m_pTCnCameraCfg->wBGain, bCamBGain );
	PostEvent( UI_CNSTOOL_CAMERA_BGAIN_IND, NULL, (LPARAM)bCamBGain );
}

u16 CCncSysCtrl::CamPicSceneModeCmd( const EmPicSceMode& emPicSceMode )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&emPicSceMode, sizeof(EmPicSceMode));
	pcTpMsg->SetEvent(ev_Cn_CameraPicSceneModeCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraPicSceneModeCmd, emEventTypecnstoolSend, "CamPicSceneModeCmd:%d", emPicSceMode );
	return wRet;
}

EmPicSceMode CCncSysCtrl::GetCamPicSceneMode()
{
	if ( m_pTCnCameraCfg ==NULL )
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->emPicSceMode;
}

void CCncSysCtrl::OnCamPicSceneModeInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg ==NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->emPicSceMode = *(EmPicSceMode*)( cTpMsg.GetBody() );
	BOOL bCamPicSceneMode = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmPicSceMode) );
	PrtMsg( ev_Cn_CameraPicSceneModeInd, emEventTypecnstoolRecv, "emPicSceMode:%d, bCamPicSceneMode:%d", m_pTCnCameraCfg->emPicMode, bCamPicSceneMode );
	PostEvent( UI_CNSTOOL_CAMERA_PIC_SCENE_MODE_IND, NULL, (LPARAM)bCamPicSceneMode );
}

u16 CCncSysCtrl::CamGammaCmd( const EmGamma& emGamma )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&emGamma, sizeof(EmGamma));
	pcTpMsg->SetEvent(ev_Cn_CameraGammaCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraGammaCmd, emEventTypecnstoolSend, "CamGammaCmd:%d", emGamma );
	return wRet;
}

EmGamma CCncSysCtrl::GetCamGamma()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->emGamma;
}

void CCncSysCtrl::OnCamGammaInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->emGamma = *(EmGamma*)( cTpMsg.GetBody() );
	BOOL bCamGamma = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmGamma) );
	PrtMsg( ev_Cn_CameraGammaInd, emEventTypecnstoolRecv, "emGamma:%d, bCamGamma:%d", m_pTCnCameraCfg->emGamma, bCamGamma );
	PostEvent( UI_CNSTOOL_CAMERA_GAMMA_IND, NULL, (LPARAM)bCamGamma );
}

u16 CCncSysCtrl::CamPicSceAptCmd( const u8& byPicSceApt )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&byPicSceApt, sizeof(u8));
	pcTpMsg->SetEvent(ev_Cn_CameraPicSceAptCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraPicSceAptCmd, emEventTypecnstoolSend, "CamPicSceAptCmd:%d", byPicSceApt );
	return wRet;
}

u8 CCncSysCtrl::GetCamPicSceApt()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->byPicApt;
}

void CCncSysCtrl::OnCamPicSceAptInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->byPicApt = *(u8*)( cTpMsg.GetBody() );
	BOOL bCamPicSceApt = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	PrtMsg( ev_Cn_CameraPicSceAptInd, emEventTypecnstoolRecv, "byPicSceApt:%d, bCamPicSceApt:%d", m_pTCnCameraCfg->byPicApt, bCamPicSceApt );
	PostEvent( UI_CNSTOOL_CAMERA_PIC_SCE_APT_IND, NULL, (LPARAM)bCamPicSceApt );
}

u16 CCncSysCtrl::CamContrastCmd( const u16& wContrast )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&wContrast, sizeof(u16));
	pcTpMsg->SetEvent(ev_Cn_CameraContrastCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraContrastCmd, emEventTypecnstoolSend, "CamContrastCmd:%d", wContrast );
	return wRet;
}

u16 CCncSysCtrl::GetCamContrast()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->wContrast;
}

void CCncSysCtrl::OnCamContrastInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->wContrast = *(u16*)( cTpMsg.GetBody() );
	BOOL bCamContrast = *(BOOL*)( cTpMsg.GetBody() + sizeof(u16) );
	PrtMsg( ev_Cn_CameraContrastInd, emEventTypecnstoolRecv, "wContrast:%d, bCamContrast:%d", m_pTCnCameraCfg->wContrast, bCamContrast );
	PostEvent( UI_CNSTOOL_CAMERA_CONTRAST_IND, NULL, (LPARAM)bCamContrast );
}

u16 CCncSysCtrl::CamHueCmd( const u16& wHue )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&wHue, sizeof(u16));
	pcTpMsg->SetEvent(ev_Cn_CameraHueCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraHueCmd, emEventTypecnstoolSend, "CamContrastCmd:%d", wHue );
	return wRet;
}

u16 CCncSysCtrl::GetCamHue()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->wHue;
}

void CCncSysCtrl::OnCamHueInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->wHue = *(u16*)( cTpMsg.GetBody() );
	BOOL bCamHue = *(BOOL*)( cTpMsg.GetBody() + sizeof(u16) );
	PrtMsg( ev_Cn_CameraHueInd, emEventTypecnstoolRecv, "wHue:%d, bCamHue:%d", m_pTCnCameraCfg->wHue, bCamHue );
	PostEvent( UI_CNSTOOL_CAMERA_HUE_IND, NULL, (LPARAM)bCamHue );
}

u16 CCncSysCtrl::CamSaturatCmd( const u16& wSaturat )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&wSaturat, sizeof(u16));
	pcTpMsg->SetEvent(ev_Cn_CameraSaturatCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraSaturatCmd, emEventTypecnstoolSend, "CamContrastCmd:%d", wSaturat );
	return wRet;
}

u16 CCncSysCtrl::GetCamSaturat()
{
	return m_pTCnCameraCfg->wSaturat;
}

void CCncSysCtrl::OnCamSaturatInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->wSaturat = *(u16*)( cTpMsg.GetBody() );
	BOOL bCamSaturat = *(BOOL*)( cTpMsg.GetBody() + sizeof(u16) );
	PrtMsg( ev_Cn_CameraSaturatInd, emEventTypecnstoolRecv, "wSaturat:%d, bCamSaturat:%d", m_pTCnCameraCfg->wSaturat, bCamSaturat );
	PostEvent( UI_CNSTOOL_CAMERA_SATURAT_IND, NULL, (LPARAM)bCamSaturat );
}

u16 CCncSysCtrl::CamBrightCmd( const u16& wBright )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&wBright, sizeof(u16));
	pcTpMsg->SetEvent(ev_Cn_CameraBrightCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraBrightCmd, emEventTypecnstoolSend, "CamContrastCmd:%d", wBright );
	return wRet;
}

u16 CCncSysCtrl::GetCamBright()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->wBright;
}

void CCncSysCtrl::OnCamBrightInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->wBright = *(u16*)( cTpMsg.GetBody() );
	BOOL bCamBright = *(BOOL*)( cTpMsg.GetBody() + sizeof(u16) );
	PrtMsg( ev_Cn_CameraBrightInd, emEventTypecnstoolRecv, "wBright:%d, bCamBright:%d", m_pTCnCameraCfg->wBright, bCamBright );
	PostEvent( UI_CNSTOOL_CAMERA_BRIGHT_IND, NULL, (LPARAM)bCamBright );
}

u16 CCncSysCtrl::CamNRStmCleanCmd( const EmStmClean& emStmClean )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&emStmClean, sizeof(EmStmClean));
	pcTpMsg->SetEvent(ev_Cn_CameraNRStmCleanCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CameraNRStmCleanCmd, emEventTypecnstoolSend, "CamNRStmCleanCmd:%d", emStmClean );
	return wRet;
}

EmStmClean CCncSysCtrl::GetCamNRStmClean()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->emStmClean;
}

void CCncSysCtrl::OnCamNRStmCleanInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->emStmClean = *(EmStmClean*)( cTpMsg.GetBody() );
	BOOL bCamNRStmClean = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmStmClean) );
	PrtMsg( ev_Cn_CameraNRStmCleanInd, emEventTypecnstoolRecv, "emStmClean:%d, bCamNRStmClean:%d", m_pTCnCameraCfg->emStmClean, bCamNRStmClean );
	PostEvent( UI_CNSTOOL_CAMERA_NR_STM_CLEAN_IND, NULL, (LPARAM)bCamNRStmClean );
}

u16 CCncSysCtrl::Cam3DNRCmd( const Em3DNR& em3DNR )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&em3DNR, sizeof(Em3DNR));
	pcTpMsg->SetEvent(ev_Cn_Camera3DNRCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_Camera3DNRCmd, emEventTypecnstoolSend, "Cam3DNRCmd:%d", em3DNR );
	return wRet;
}

Em3DNR CCncSysCtrl::GetCam3DNR()
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	return m_pTCnCameraCfg->em3DNR;
}

void CCncSysCtrl::OnCam3DNRInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);

	m_pTCnCameraCfg->em3DNR = *(Em3DNR*)( cTpMsg.GetBody() );
	BOOL bCam3DNR = *(BOOL*)( cTpMsg.GetBody() + sizeof(Em3DNR) );
	PrtMsg( ev_Cn_Camera3DNRInd, emEventTypecnstoolRecv, "em3DNR:%d, bCam3DNR:%d", m_pTCnCameraCfg->em3DNR, bCam3DNR );
	PostEvent( UI_CNSTOOL_CAMERA_3DNR_IND, NULL, (LPARAM)bCam3DNR );
}

void CCncSysCtrl::SetCameraCfgPtr()
{
	switch ( m_byCameraSel )
	{
	case 0:
		{
			m_pTCnCameraCfg = &m_tCnCameraCfg1;
			break;
		}
	case 1:
		{
			m_pTCnCameraCfg = &m_tCnCameraCfg2;
			break;
		}
	case 2:
		{
			m_pTCnCameraCfg = &m_tCnCameraCfg3;
			break;
		}
	default:
		break;
	}

	return;
}

u16 CCncSysCtrl::GetCamZoom()
{
	if (m_pTCnCameraCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	return m_pTCnCameraCfg->wZoom;	
}

u16 CCncSysCtrl::SetCamZoomCmd( const u16& wZoom )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&wZoom, sizeof(u16));
	pcTpMsg->SetEvent(ev_Cn_SetCameraZoomCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_SetCameraZoomCmd, emEventTypecnstoolSend, "%d", wZoom );
	return wRet;
}

void CCncSysCtrl::OnSetCameraZoomInd(const CMessage& cMsg)
{
	if ( m_pTCnCameraCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTCnCameraCfg->wZoom = *(u16*)( cTpMsg.GetBody() );
	BOOL bRet = *(BOOL*)( cTpMsg.GetBody() + sizeof(u16) );
	
	PrtMsg( ev_Cn_SetCameraZoomInd, emEventTypecnstoolRecv, "u16:%d,BOOL:%d", m_pTCnCameraCfg->wZoom, bRet );
	PostEvent( UI_CNSTOOL_SET_CAMERA_ZOOM_IND, NULL, (LPARAM)bRet );
}

void CCncSysCtrl::OnCameraPowerOnNty(const CMessage& cMsg)
{		
	CTpMsg cTpMsg(&cMsg);
	BOOL bLoginByOther = *(BOOL*)( cTpMsg.GetBody() ); //TRUE tptools抢登时发送正在上电的通知; FALSE 正常情况
	PrtMsg( ev_Cn_CameraPowerOnNty, emEventTypecnstoolRecv, "bLoginByOther:%d", bLoginByOther );
	PostEvent( UI_CNSTOOL_CAMERA_POWER_ON_NTY, NULL, (LPARAM)bLoginByOther );
}

u16 CCncSysCtrl::SetCamTypeCmd( const EmCamType& emCamType )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&emCamType, sizeof(emCamType));
	pcTpMsg->SetEvent(ev_Cn_SetCamType_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_SetCamType_Cmd, emEventTypecnstoolSend, "emCamType:%d(emCamHD95D:%d,emCamSony:%d)", emCamType, emCamHD95D, emCamSony );
	return wRet;
}

u16 CCncSysCtrl::SonyBackLightCmd( const BOOL& bLight )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bLight, sizeof(BOOL));
	pcTpMsg->SetEvent(ev_Cn_SonyBackLightCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_SonyBackLightCmd, emEventTypecnstoolSend, "bsonyLight:%d", bLight );
	return wRet;
}

u16 CCncSysCtrl::SonyStmClenCmd( const BOOL& bClen, const u8& bylevel )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bClen, sizeof(BOOL));
	pcTpMsg->CatBody(&bylevel,sizeof(u8));
	pcTpMsg->SetEvent(ev_Cn_SonyStmClenCmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_SonyStmClenCmd, emEventTypecnstoolSend, "bClen:%d,bylevel:%d", bClen, bylevel );
	return wRet;
}

u16 CCncSysCtrl::SetMoon904KCamCfgCmd( const EmCamCfgType& emCamCfgType, const u32& dwValue )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData(m_pSession->GetInst());
    pcTpMsg->SetBody(&emCamCfgType, sizeof(EmCamCfgType));

    switch(emCamCfgType)
    {
    case emCfgSensitivity:
    case emCfgAntiFlicker:
    case emCfgSpotLight:
    case emCfgBackLight:
    case emCfgWDR:
    case emCfgPicEffect:
    case emCfgPicFlip:
    case emCfgPicMode:
    case emCfgCamResolution:
    case emCfgCamBaudRate:
        {
            pcTpMsg->CatBody(&dwValue,sizeof(u32));
            break;
        }
    case emCfgGainValue:
    case emCfgGainLimit:
    case emCfgBackLightLevel:
    case emCfgWDRLevel:
    case emCfgPicGamma:
    case emCfgPic2DNR:
    case emCfgPic3DNR:
        {
            u8 byValue = (u8)dwValue;
            pcTpMsg->CatBody(&byValue,sizeof(u8));
            break;
        }
    case emCfgExposureComp:
    case emCfgColorTemperature:
    case emCfgPicSharpness:
        {
            u16 wValue = (u16)dwValue;
            pcTpMsg->CatBody(&wValue,sizeof(u16));
            break;
        }
    case emCfgSpotLighetPos:
        {
            //聚光灯位置
            break;
        }

    default:
        {
            break;
        }
    }

    pcTpMsg->SetEvent(ev_Cn_CamCfg_Cmd);
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_Cn_CamCfg_Cmd, emEventTypecnstoolSend, "EmCamCfgType:%d,Content:%d", emCamCfgType, dwValue );
    return wRet;
}

void CCncSysCtrl::OnMoon904KCamCfgInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
    EmCamCfgType emCamCfgType = *(EmCamCfgType*)( cTpMsg.GetBody() );
    u8 byOffset = 0;
    switch (emCamCfgType)
    {
    case emCfgSensitivity:
    case emCfgAntiFlicker:
    case emCfgSpotLight:
    case emCfgBackLight:
    case emCfgWDR:
    case emCfgPicEffect:
    case emCfgPicFlip:
    case emCfgPicMode:
    case emCfgCamResolution:
    case emCfgCamBaudRate:
        {
            byOffset = sizeof(u32);
            break;
        }
    case emCfgGainValue:
    case emCfgGainLimit:
    case emCfgBackLightLevel:
    case emCfgWDRLevel:
    case emCfgPicGamma:
    case emCfgPic2DNR:
    case emCfgPic3DNR:
        {
            byOffset = sizeof(u8);
            break;
        }
    case emCfgExposureComp:
    case emCfgColorTemperature:
    case emCfgPicSharpness:
        {
            byOffset = sizeof(u16);
            break;
        }
    case emCfgSpotLighetPos:
        {
            //聚光灯位置
            break;
        }
        
    default:
        {
            break;
        }
    }
	BOOL bRet = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmCamCfgType) + byOffset );
	PrtMsg( ev_Cn_CamCfg_Ind, emEventTypecnstoolRecv, "EmCamCfgType:%d,Result:%d", emCamCfgType, bRet );
    PostEvent( UI_CNSTOOL_MOON904KCAMCFG_IND, (WPARAM)emCamCfgType, (LPARAM)bRet );
}

u8 CCncSysCtrl::GetMoon90CamExpGain()
{
    if ( m_pTCnCameraCfg == NULL )
    {
        SetCameraCfgPtr();
    }
    return m_pTCnCameraCfg->byGainValue;
}

u16 CCncSysCtrl::GetMoon90CamExCompRate()
{
    if ( m_pTCnCameraCfg == NULL )
    {
        SetCameraCfgPtr();
    }
    return m_pTCnCameraCfg->wExposureComp;
}

u8 CCncSysCtrl::GetMoon90CamBLCRate()
{
    if ( m_pTCnCameraCfg == NULL )
    {
        SetCameraCfgPtr();
    }
    return m_pTCnCameraCfg->byBackLightLevel;
}

u8 CCncSysCtrl::GetMoon90CamWDRRate()
{
    if ( m_pTCnCameraCfg == NULL )
    {
        SetCameraCfgPtr();
    }
    return m_pTCnCameraCfg->byWideDynamicsLevel;
}

void CCncSysCtrl::OnSrcOffLineNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	u8 byIndex = *(u8*)( cTpMsg.GetBody() );
	PrtMsg( ev_TpSrcOffLine_Nty, emEventTypecnstoolRecv, "Index:%d", byIndex );
    PostEvent( UI_SRCOFFLINE_NTY, NULL, NULL );
}