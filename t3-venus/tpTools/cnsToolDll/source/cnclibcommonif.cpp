#include "StdAfx.h"
#include "cnclibcommonif.h"
#include "sessionmgr.h"



CCnclibCommonIF* CCnclibCommonIF::m_pThis = NULL;

CCnclibCommonIF::CCnclibCommonIF()
{

}

CCnclibCommonIF::~CCnclibCommonIF()
{

}

CCnclibCommonIF* CCnclibCommonIF::GetComIF()
{
	if ( m_pThis == NULL )
    {
        m_pThis = new CCnclibCommonIF;	 
    }
	return m_pThis;
}

UINT ThreadConnectCns(LPVOID lpParam)
{   
    u16 re= NO_ERROR;
    re = COMIFMGRPTR->LinkCns();
    if ( re != NO_ERROR )
    {   
        if ( ERR_CNC_ACTIVE_CONNECT ==  re )
        {
            SendMessage( LIBDATAMGRPTR->GetSafeHwnd() ,UI_CNS_CONNECTED, TRUE, NO_ERROR);
        }
        else
        {
			if(Refuse_CNC_LOGIN == re)
			{
				 SendMessage( LIBDATAMGRPTR->GetSafeHwnd() ,UI_CNS_CONNECTED, FALSE, Refuse_CNC_LOGIN);
			}
			else
			{
				SendMessage( LIBDATAMGRPTR->GetSafeHwnd() ,UI_CNS_CONNECTED, FALSE, ERR_CNC_TCPCONNECT);
			}           
        }
	}
    
    return re;
} 

u16 CCnclibCommonIF::LinkCns()
{
    u16 re =  ERR_CMS;
	CCnsSessionCtrlIF* pCnsSession = CNCSESSION_MGR_PTR->GetSessionIF();
    if ( pCnsSession )
    {
        re = pCnsSession->ConnectCns( m_tLoginInfo.dwIp,  m_tLoginInfo.nPort,
            m_tLoginInfo.strName,  m_tLoginInfo.strPswd );
    }
    return re;
}

u16 CCnclibCommonIF::connect( u32 dwIp, u32 dwPort)
{
// 	CCnsSessionCtrlIF* ppp = CNCSESSION_MGR_PTR->GetSessionIF();
// 	u16 re = ppp->ConnectCns( dwIp, dwPort, "admin", "admin");
	u16 re = NO_ERROR; 

    m_tLoginInfo.dwIp = dwIp;
    m_tLoginInfo.nPort = dwPort;
    m_tLoginInfo.strName = "admin";
	m_tLoginInfo.strPswd = "admin";
	
	//Á¬½Ócns
	AfxBeginThread( ThreadConnectCns , NULL );

	return re;
}

u16	CCnclibCommonIF::DisConnect()
{
	u16 re = CNCSESSION_MGR_PTR->GetSessionIF()->DisconnectCns();
	return re;
}
u16 CCnclibCommonIF::CnsRegSipService( const TTPSipRegistrarCfg &tSipCfg )
{
	u16 re = CNCSESSION_MGR_PTR->GetConfigIF()->RegSipService( tSipCfg );
	return re;
}

u16 CCnclibCommonIF::CnsRegGkService( const TTPGKCfg &tCfg )
{
	u16 re = CNCSESSION_MGR_PTR->GetConfigIF()->RegGk( tCfg );
	return re;
}

u16 CCnclibCommonIF::SetCloudServerInfo(const TTPCloudPlatServerCfg& tTpCloudServerInfo)
{
	u16 re = CNCSESSION_MGR_PTR->GetConfigIF()->SetCloudServerInfo( tTpCloudServerInfo );
	return re;
}

u16 CCnclibCommonIF::UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex ,EmTpIpNameNatSyn emTpIpType)
{
	u16 re = CNCSESSION_MGR_PTR->GetConfigIF()->UpdateCnsInfo( tInfo, byIndex ,emTpIpType);
	return re;
}

u16 CCnclibCommonIF::UpdateNATCfg( const TTPNatCfg& tInfo,EmTpIpNameNatSyn emTpIpType)
{
	u16 re = CNCSESSION_MGR_PTR->GetConfigIF()->UpdateNATCfg( tInfo,emTpIpType);
	return re;
}

u16 CCnclibCommonIF::SetAesEncrypCmd( const TTpEncryptKey& tEncryptKey )
{
	u16 re = CNCSESSION_MGR_PTR->GetConfigIF()->SetAesEncrypCmd( tEncryptKey );
	return re;
}

u16 CCnclibCommonIF::SetAudioPortInfoCmd( const TTpAudioPortInfo* atAudioPortInfo )		
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetAudioPortInfoCmd( &atAudioPortInfo );
	return re;
}

u16 CCnclibCommonIF::SetMic10InfoCmd(const TTpMic10Info &tTPMic10Info)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetMic10InfoCmd( tTPMic10Info );
	return re;
}

u16 CCnclibCommonIF::SetNoDeskAudioCmd(bool bNoDeskAudio)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetNoDeskAudioCmd( bNoDeskAudio );
	return re;
}

u16 CCnclibCommonIF::SetAudioEqualizerCmd( const TTPEqualizer* atAudioEqualizer )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->AudioEqualizerCmd( &atAudioEqualizer );
	return re;
}

u16 CCnclibCommonIF::SetAudiotMixerCmd( const u8* aAudioMixerInfo )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->AudiotMixerCmd( &aAudioMixerInfo );
	return re;
}

u16 CCnclibCommonIF::SetDefaultMixerCmd( const u8* aAudioMixerInfo )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->DefaultMixerCmd( &aAudioMixerInfo );
	return re;
}

u16 CCnclibCommonIF::SetDefaultAudioPortCmd( const TTpAudioPortInfo* atAudioPortInfo )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->DefaultAudioPortCmd( &atAudioPortInfo );
	return re;
}

u16 CCnclibCommonIF::SetDefaultEqCmd( const TTPEqualizer* atAudioEqualizer )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->DefaultEqCmd( &atAudioEqualizer);
	return re;
}

u16 CCnclibCommonIF::LostPacketInfoReq()
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->LostPacketInfoReq();
	return re;
}

u16 CCnclibCommonIF::SelAVMatrixCmd( const TTPVgaMixInfo& tVgaMixInfo )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SelAVMatrixCmd( tVgaMixInfo );
	return re;
}
						
u16 CCnclibCommonIF::UpdateTpadListReq()	
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->UpdateTpadListReq();
	return re;
}

u16 CCnclibCommonIF::RebootCns()
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->RebootCns();
	return re;
}

u16 CCnclibCommonIF::UpgradeCns( const TTPFTPFileInfo& tVerFileInfo )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->UpgradeCns(tVerFileInfo);
	return re;
}

u16 CCnclibCommonIF::CamSelCmd( const u8& byCameraIndx )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamSelCmd( byCameraIndx );
	return re;
}

u16 CCnclibCommonIF::CamResetCmd()
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamResetCmd();
	return re;
}

u16 CCnclibCommonIF::SetCamZoomCmd( const EmZoom& emZoom, const EmZoomStatus& emZoomStatus  )	
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->SetCamZoomCmd( emZoom, emZoomStatus );
	return re;
}

u16 CCnclibCommonIF::SetCamOSDCmd( const EmOSDShow& emOSDShow )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->SetCamOSDCmd( emOSDShow );
	return re;
}

u16 CCnclibCommonIF::SetCamAutoFocusCmd(const EmFocusMode& emFocusMode)
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->SetCamAutoFocusCmd(emFocusMode);
	return re;
}

u16 CCnclibCommonIF::SetCamFocusCmd( const EmFocus& emFocus, const EmCnAction& emCnAction )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->SetCamFocusCmd( emFocus, emCnAction );
	return re;
}

u16 CCnclibCommonIF::CamPresetSaveCmd()	
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamPresetSaveCmd();
	return re;
}

u16 CCnclibCommonIF::SetCamPresetMoveCmd( const BOOL& bPresetMove )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->SetCamPresetMoveCmd( bPresetMove );
	return re;
}

u16 CCnclibCommonIF::CamAutoExposureCmd( EmExpMode emExpAuto )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamAutoExposureCmd( emExpAuto );
	return re;
}

u16 CCnclibCommonIF::CamGainCmd( const EmGain& emGain )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamGainCmd( emGain );
	return re;
}

u16 CCnclibCommonIF::CamShutSpdCmd( const EmShutSpd& emShutSpd )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamShutSpdCmd( emShutSpd );
	return re;
}

u16 CCnclibCommonIF::CamBackLightCmd( const EmBackLightType& emBackLightType, const u8& byMulti )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamBackLightCmd( emBackLightType, byMulti );
	return re;
}

u16 CCnclibCommonIF::CamAperture( const u8& byAperture)
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamAperture( byAperture );
	return re;
}

u16 CCnclibCommonIF::CamAutoWBCmd( const EmWBMode& emWBMode )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamAutoWBCmd( emWBMode );
	return re;
}

u16 CCnclibCommonIF::CamRGainCmd( const u16& wRGain )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamRGainCmd( wRGain );
	return re;
}

u16 CCnclibCommonIF::CamBGainCmd( const u16& wBGain )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamBGainCmd( wBGain );
	return re;
}

u16 CCnclibCommonIF::CamPicSceneModeCmd( const EmPicSceMode& emPicSceMode )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamPicSceneModeCmd( emPicSceMode );
	return re;
}

u16 CCnclibCommonIF::CamGammaCmd( const EmGamma& emGamma )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamGammaCmd( emGamma );
	return re;
}

u16 CCnclibCommonIF::CamPicSceAptCmd( const u8& byPicSceApt )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamPicSceAptCmd( byPicSceApt );
	return re;
}

u16 CCnclibCommonIF::CamContrastCmd( const u16& wContrast )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamContrastCmd( wContrast );
	return re;
}

u16 CCnclibCommonIF::CamHueCmd( const u16& wHue )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamHueCmd( wHue );
	return re;
}

u16 CCnclibCommonIF::CamSaturatCmd( const u16& wSaturat )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamSaturatCmd( wSaturat );
	return re;
}

u16 CCnclibCommonIF::CamBrightCmd( const u16& wBright )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamBrightCmd( wBright );
	return re;
}

u16 CCnclibCommonIF::CamNRStmCleanCmd( const EmStmClean& emStmClean )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->CamNRStmCleanCmd( emStmClean );
	return re;
}

u16 CCnclibCommonIF::Cam3DNRCmd( const Em3DNR& em3DNR )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->Cam3DNRCmd( em3DNR );
	return re;
}

u16 CCnclibCommonIF::SetLoadCameraFileNty()
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->SetLoadCameraFileNty();
	return re;
}	

u16 CCnclibCommonIF::SetCamZoomCmd( const u16& wZoom )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->SetCamZoomCmd( wZoom );
	return re;
}

u16 CCnclibCommonIF::UpdateEthnetCfg( const TTPEthnetInfo& tInfo,EmTpIpNameNatSyn emTpIpType)
{
	u16 re = CNCSESSION_MGR_PTR->GetConfigIF()->UpdateEthnetCfg( tInfo,emTpIpType);
	return re;	
}

u16 CCnclibCommonIF::SaveWEthnetCfgCmd(const TTPWEthnetInfo& tTPWEthnetInfo, EmTpIpNameNatSyn emTpIpType)
{
	u16 re = CNCSESSION_MGR_PTR->GetConfigIF()->SaveWEthnetCfgCmd( tTPWEthnetInfo, emTpIpType );
	return re;
}

u16  CCnclibCommonIF::NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	u16 re = CNCSESSION_MGR_PTR->GetNetMngCtrlIF()->NetMngAddCmd( tTPNMServerCfg );
	return re;
}


u16  CCnclibCommonIF::NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	u16 re = CNCSESSION_MGR_PTR->GetNetMngCtrlIF()->NetMngModifyCmd( tTPNMServerCfg );
	return re;
}


u16  CCnclibCommonIF::NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	u16 re = CNCSESSION_MGR_PTR->GetNetMngCtrlIF()->NetMngDeleteCmd( tTPNMServerCfg );
	return re;
}

u16 CCnclibCommonIF::RefreshBasicInfo()
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->ReqRefresh();
	return re;
}

u16 CCnclibCommonIF::CallServerCmd( const TTPCallSerInfo& tCallSerInfo )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->CallServerCmd( tCallSerInfo );
	return re;
}

u16 CCnclibCommonIF::UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->UpgradeSerCmd( tUpgradeSer );
	return re;
}

u16 CCnclibCommonIF::SetDataConfSerCmd( const TTPDataConfInfo& tWBSerIp )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetDataConfSerCmd( tWBSerIp );
	return re;
}

u16 CCnclibCommonIF::SetMatrixSerCmd(const TTPMatrixServerInfo& tTPMatrixServerInfo)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetMatrixSerCmd( tTPMatrixServerInfo );
	return re;
}

u16 CCnclibCommonIF::SetNtpSerCmd(const TTPNtpSer& tTpNtpSer)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetNtpSerCmd( tTpNtpSer );
	return re;
}

u16 CCnclibCommonIF::SetQtEncryptSerCmd(const TTpQtEncryptCfg& tTpQtEncryptCfg)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetQtEncryptSerCmd( tTpQtEncryptCfg );
	return re;
}

u16 CCnclibCommonIF::RouteMngAddCmd(const TRouteCfg& tRouteCfg)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->RouteMngAddCmd(tRouteCfg);
	return re;
}

u16 CCnclibCommonIF::RouteMngDelCmd(const TRouteCfg& tRouteCfg)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->RouteMngDelCmd(tRouteCfg);
	return re;
}

u16 CCnclibCommonIF::StopAVMatrixReq()
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->StopAVMatrixReq();
	return re;
}

u16 CCnclibCommonIF::ConfSignCmd( const BOOL& bOk, u8 byIndex )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->ConfSignCmd( bOk, byIndex );
	return re;
}

u16 CCnclibCommonIF::VideoFormatCmd( const TTPVidForamt& tVidForamt )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->VideoFormatCmd( tVidForamt );
	return re;
}

u16 CCnclibCommonIF::DualVideoFormatCmd( const TTPVidForamt& tVidForamt )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->DualVideoFormatCmd( tVidForamt );
	return re;
}

u16 CCnclibCommonIF::CallRateCmd( const u16 wCallRate )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->CallRateCmd( wCallRate );
	return re;
}

u16 CCnclibCommonIF::DualCallRateCmd( const u16 wDualCallRate )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->DualCallRateCmd( wDualCallRate );
	return re;
}

u16 CCnclibCommonIF::ConfDisCmd( const BOOL& bDis )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->ConfDisCmd( bDis );
	return re;
}

u16 CCnclibCommonIF::ConfPollCmd( const TTPPollInfo& tPollInfo )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->ConfPollCmd( tPollInfo );
	return re;
}

u16 CCnclibCommonIF::AudioFormatCmd( const EmTpAudioFormat& emAudioFormat )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->AudioFormatCmd( emAudioFormat );
	return re;
}

u16 CCnclibCommonIF::SetDisplayCmd( BOOL bDisplay, const TTPDisplayType& tDisplayType1, const TTPDisplayType& tDisplayType3 )
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDisplayCmd( bDisplay, tDisplayType1, tDisplayType3 );
	return re;
}

u16 CCnclibCommonIF::SetCentreTVModleCmd( EmTVModle emTvMode )
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetCentreTVModle( emTvMode );
	return re;
}

u16 CCnclibCommonIF::SetDisplayShowCmd(BOOL bDisplayShow)
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDisplayShowCmd( bDisplayShow );
	return re;
}

u16 CCnclibCommonIF::SetCamTypeCmd( const EmCamType& emCamType )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->SetCamTypeCmd( emCamType );
	return re;
}

u16 CCnclibCommonIF::SonyBackLightCmd( const BOOL& bLight )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->SonyBackLightCmd( bLight );
	return re;
}

u16 CCnclibCommonIF::SonyStmClenCmd( const BOOL& bClen, const u8& bylevel )
{
	u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->SonyStmClenCmd( bClen, bylevel );
	return re;
}

u16 CCnclibCommonIF::SetDefaultAudioCmd( const TTPMPAudioInfo* atAudioInfo )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->DefaultAudioSetCmd( atAudioInfo );
	return re;
}

u16 CCnclibCommonIF::SetDefaultListenPortCmd(const EmAudMixType emAudioMixtype, const u8 byAudMixVolume)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->DefaultListenPortSetCmd( emAudioMixtype, byAudMixVolume );
	return re;
}

u16 CCnclibCommonIF::SetDefaultAux2OutCmd(const EmAudExtend emAudExtend, const u8 byAudExtendVolume)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->DefaultAux2OutSetCmd( emAudExtend, byAudExtendVolume );
	return re;
}


u16 CCnclibCommonIF::SetAudioInfoCmd( const TTPMPAudioInfo* atAudioInfo )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetAudioInfoCmd( atAudioInfo );
	return re;
}

u16 CCnclibCommonIF::SetListenPortCmd(const EmAudMixType emAudioMixtype, const u8 byAudMixVolume)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetListenPortCmd(emAudioMixtype, byAudMixVolume);
	return re;
}

u16 CCnclibCommonIF::SetAux2OutCmd(const EmAudExtend emAudExtend, const u8 byAudExtendVolume)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetAux2OutCmd(emAudExtend, byAudExtendVolume);
	return re;
}

u16 CCnclibCommonIF::SetAudioWhiteNoiseCmd(BOOL bIsOpen ,u32 dwWhiteNoisePort )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetAudioWhiteNoiseCmd( bIsOpen , dwWhiteNoisePort );
	return re;
}

u16 CCnclibCommonIF::SetDefaultMainAudioCmd( const TTPVideoInfoTool* ptAudioInfo )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->DefaultMainAudioCmd( ptAudioInfo );
	return re;
}

u16 CCnclibCommonIF::SnapShotCmd( )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SnapShotCmd();
	return re;
}

u16 CCnclibCommonIF::SetMainAudioInfoCmd( const TTPVideoInfoTool* ptAudioInfo )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetMainAudioInfoCmd( ptAudioInfo );
	return re;
}

u16 CCnclibCommonIF::SetDefaultDemonStrationCmd(const TVgaInfo *ptDisplaySource,
												const TTPDualDisplayStrategy *ptDualDisplayStrategy,
												const EmVgaType emDefaultDisplay)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetDefaultDemonStrationCmd(ptDisplaySource, 
		ptDualDisplayStrategy,emDefaultDisplay);
	return re;
}

u16 CCnclibCommonIF::SetDemonStrationCmd(const TVgaInfo *ptDisplaySource,
										 const TTPDualDisplayStrategy *ptDualDisplayStrategy,
										 const EmVgaType emDefaultDisplay)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetDemonStrationCmd(ptDisplaySource, 
		ptDualDisplayStrategy,emDefaultDisplay);
	return re;
}

u16 CCnclibCommonIF::SetDefParameterCmd(const TTPImageAdjustParam * pImageAdjustParam )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetDefParameterCmd( pImageAdjustParam );
	return re;
}

u16 CCnclibCommonIF::SetParameterCmd(const TTPImageAdjustParam * pImageAdjustParam )
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetParameterCmd( pImageAdjustParam );
	return re;
}

u16 CCnclibCommonIF::SetPanCamNumberCmd( u8 byPanCamNum )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetPanCamNumber( byPanCamNum );
	return re;
}

u16 CCnclibCommonIF::SetDCCamZoomCmd( const EmDCamZoom emZoom ,const EmCnAction emAction )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCamZoom( emZoom, emAction );
	return re;
}

u16 CCnclibCommonIF::SetDCCamZoomValue( const u16& wZoom )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCamZoomValueCmd( wZoom );
	return re;
}

u16 CCnclibCommonIF::SetDCCamAFModeCmd( EmDCamAFMode emMode )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCamAFMode( emMode );
	return re;
}

u16 CCnclibCommonIF::SetDCCamFocusCmd( EmFocus emFocusMode ,EmCnAction emAction )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCCamFocus( emFocusMode,emAction);
	return re;
}

u16 CCnclibCommonIF::SetDCCamWBModeCmd( EmDCamWBMode emWBMode )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCamWBMode( emWBMode );
	return re;
}

u16 CCnclibCommonIF::SetDCCamExposureCmd( EmExpMode emExpMode )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCCamExposure( emExpMode );
	return re;
}

u16 CCnclibCommonIF::SetDCCamApertureCmd( EmDCamIris emAperture )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCCamAperture( emAperture );
	return re;
}

u16 CCnclibCommonIF::SetDCCamExpGain( EmDCamGain emDCCamExpGain )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCCamExpGainCmd( emDCCamExpGain );
	return re;
}

u16 CCnclibCommonIF::SetDCCamShut( EmDCamShutSpd emDCCamExpShut )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCCamShutCmd( emDCCamExpShut );
	return re;
}

u16 CCnclibCommonIF::SetDcCamRGain( u16 wRGain )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDcCamRGainCmd( wRGain );
	return re;
}

u16 CCnclibCommonIF::SetDcCamBGain( u16 wRGain )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDcCamBGainCmd( wRGain );
	return re;
}

u16 CCnclibCommonIF::SetDCamRecallCmd( EmDCamRecallNum emNum )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCamRecall( emNum );
	return re;
}

u16 CCnclibCommonIF::SetDCamSavePresetCmd( EmDCamPresetNum emNum )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCamPreset( emNum );
	return re;
}

u16 CCnclibCommonIF::SetCurtainNumber( u8 byCurNum )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetCurtainNumberCmd( byCurNum );
	return re;
}

u16 CCnclibCommonIF::SetCurtainNameCmd( u8 byCurIndex , TCentreCurName tCurtainName )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetCurtainName( byCurIndex, tCurtainName);
	return re;
}

u16 CCnclibCommonIF::SetCurtainOpenCmd( BOOL bOpen )	
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetCurtainOpen( bOpen);
	return re;
}

u16 CCnclibCommonIF::SetLostPacketCmd( EmTpLostPackageRestore emLostPackage )	
{
	u16 re = CNCSESSION_MGR_PTR->GetConfigIF()->SetLostPacketCmd( emLostPackage );
	return re;
}

u16 CCnclibCommonIF::SetFtpInfoRsq(const TTPFtpInfo &tTPFtpInfo)
{
	u16 re = CNCSESSION_MGR_PTR->GetConfigIF()->SetFtpInfoRsq( tTPFtpInfo );
	return re;
}

u16 CCnclibCommonIF::SetTelInfoRsp(const TTPTelnetInfo &tTPTelnetInfo)
{
	u16 re = CNCSESSION_MGR_PTR->GetConfigIF()->SetTelInfoRsp( tTPTelnetInfo );
	return re;
}

u16 CCnclibCommonIF::SetDuoVideoCmd( BOOL bOpen )
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDuoVideoCmd( bOpen);
	return re;
}

u16 CCnclibCommonIF::SetDCCamOpenCmd( BOOL bOpen )
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCCamOpenCmd( bOpen);
	return re;
}

u16 CCnclibCommonIF::SetDCCamPreset( BOOL bPreset )
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDCCamPreset( bPreset );
	return re;
}

u16 CCnclibCommonIF::SetAirConditionCmd( u8 byAcNum )
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetAirConditionCmd( byAcNum );
	return re;
}

u16 CCnclibCommonIF::SetDcCamModel( EmDCamProType emDcCamType )
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetDcCamModel( emDcCamType );
	return re;
}

u16 CCnclibCommonIF::SetPaCamModel( EmQCamProType emPaCamType )
{
	u16 re = CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetPaCamModel( emPaCamType );
	return re;
}

u16 CCnclibCommonIF::SetCaptureStateCmd(bool bCapture)
{
	u16 re = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetCaptureStateCmd( bCapture );
	return re;
}

u16 CCnclibCommonIF::SetMoon904KCamCfgCmd( const EmCamCfgType& emCamCfgType, const u32& dwValue )
{
    u16 re = CNCSESSION_MGR_PTR->GetSysCtrlIF()->SetMoon904KCamCfgCmd( emCamCfgType, dwValue );
    return re;
}