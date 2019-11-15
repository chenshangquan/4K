#include "StdAfx.h"
#include "moonlibcommonif.h"
#include "sessionmgr.h"
#include "rkcprintctrl.h"

CMoonlibCommonIF* CMoonlibCommonIF::m_pThis = NULL;

CMoonlibCommonIF::CMoonlibCommonIF()
{

}

CMoonlibCommonIF::~CMoonlibCommonIF()
{

}

CMoonlibCommonIF* CMoonlibCommonIF::GetComIF()
{
	if ( m_pThis == NULL )
    {
        m_pThis = new CMoonlibCommonIF;	 
    }
	return m_pThis;
}

UINT ThreadConnectMoon(LPVOID lpParam)
{   
    u16 re= NO_ERROR;
	re = COMIFMGRPTR->LinkMoon();
    if ( re != NO_ERROR )
    {   
        SendMessage( MOONLIBDATAMGRPTR->GetSafeHwnd() ,UI_MOONTOOL_CONNECTED, FALSE, re);
	}
    else
    {
#ifdef NO_CAM_LOGIN
        SendMessage( MOONLIBDATAMGRPTR->GetSafeHwnd() ,UI_MOONTOOL_CONNECTED, TRUE, NO_ERROR);  //界面调试可用
#endif
        TRK100LoginInfo tRK100LoginInfo;
        ZeroMemory(tRK100LoginInfo.szUsr, sizeof(tRK100LoginInfo.szUsr));
        ZeroMemory(tRK100LoginInfo.szPwd, sizeof(tRK100LoginInfo.szPwd));
        strncpy(tRK100LoginInfo.szUsr, "Keda_User", sizeof(tRK100LoginInfo.szUsr));
        strncpy(tRK100LoginInfo.szPwd, "Pwd_Change", sizeof(tRK100LoginInfo.szPwd));
        MOONSESSION_MGR_PTR->GetSysCtrlIF()->SendLoginReq(tRK100LoginInfo);
    }

    return re;
} 

u16 CMoonlibCommonIF::LinkMoon()
{
    u16 re =  -1;
	CRkcSysCtrlIF* pSysCtrlIf = MOONSESSION_MGR_PTR->GetSysCtrlIF();
    if ( pSysCtrlIf )
    {
        in_addr tAddr;
        tAddr.S_un.S_addr = m_tCamLoginInfo.dwIp;
        re = pSysCtrlIf->SocketConnect( (char*)inet_ntoa(tAddr),  m_tCamLoginInfo.nPort );
    }
    return re;
}

u16 CMoonlibCommonIF::connect( u32 dwIp, u32 dwPort)
{
	u16 re = NO_ERROR; 

    m_tCamLoginInfo.dwIp = dwIp;
    m_tCamLoginInfo.nPort = dwPort;

	//连接cns
	AfxBeginThread( ThreadConnectMoon , NULL );

	return re;
}

u16	CMoonlibCommonIF::DisConnect()
{
#if 0
	u16 re = MOONSESSION_MGR_PTR->GetSessionIF()->DisconnectMoon();
#else
    u16 re = MOONSESSION_MGR_PTR->GetSysCtrlIF()->CloseSocket();
#endif
    return true;
}

u16 CMoonlibCommonIF::SetOutputFormatCmd( const TPOutputFmt& tOutputFmt)
{
    u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetOutputFormatCmd( tOutputFmt );
    return re;
}

u16 CMoonlibCommonIF::SetCamZoomCmd( const EmTPZOOM& emZoom, u8 byIndex)
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetCamZoomCmd( emZoom, byIndex );
	return re;
}

u16 CMoonlibCommonIF::SetCamZoomValCmd( const TCamZoomVal& tCamZoomVal )
{
    u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetCamZoomValCmd( tCamZoomVal );
    return re;
}

u16 CMoonlibCommonIF::SetCamZoomValueCmd( const u32& dwZoom, u8 byIndex )	
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetCamZoomValueCmd( dwZoom, byIndex );
	return re;
}

u16 CMoonlibCommonIF::SetCamZoomStopCmd(u8 byIndex)	
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetCamZoomStopCmd( byIndex );
	return re;
}

u16 CMoonlibCommonIF::SetCamAutoFocusCmd(const EmTPMOOMMode& emFocusMode)
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetCamAutoFocusCmd(emFocusMode);
	return re;
}

u16 CMoonlibCommonIF::CamSelCmd( const u8& byCameraIndx )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamSelCmd( byCameraIndx );
	return re;
}

u16 CMoonlibCommonIF::SetMoonCamCfgSyncCmd( const u8& byCameraIndx )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetMoonCamCfgSyncCmd( byCameraIndx );
	return re;
}

u16 CMoonlibCommonIF::CamStyleSelCmd( const EmTPMechanism& emTPMechanism )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamStyleSelCmd( emTPMechanism );
	return re;
}

u16 CMoonlibCommonIF::GammaStyleSelCmd(const EmH650Gamma& enH650Gamma)
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->GammaStyleSelCmd( enH650Gamma );
	return re;
}

u16 CMoonlibCommonIF::SetCamFocusNearCmd()
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetCamFocusNearCmd();
	return re;
}

u16 CMoonlibCommonIF::SetCamFocusStopCmd()
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetCamFocusStopCmd();
	return re;
}

u16 CMoonlibCommonIF::SetCamFocusFarCmd()
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetCamFocusFarCmd();
	return re;
}

u16 CMoonlibCommonIF::SetCamApertreCmd( const TIrisAutoManuMode& tIrisAutoManuMode )
{
    u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetCamApertreCmd( tIrisAutoManuMode );
    return re;
}

u16 CMoonlibCommonIF::CamAutoExposureCmd( EmTPMOOMMode emExpAuto )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamAutoExposureCmd( emExpAuto );
	return re;
}

u16 CMoonlibCommonIF::CamApertureCmd( const EmTPAperture &emTPAperture )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamApertureCmd( emTPAperture );
	return re;
}

u16 CMoonlibCommonIF::CamShutSpdCmd( const EmTPSOrThShutter& emShutSpd )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamShutSpdCmd( emShutSpd );
	return re;
}

u16 CMoonlibCommonIF::CamTwShutSpdCmd( const EmTPFOrTwShutter& emTwShutter )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamTwShutSpdCmd( emTwShutter );
	return re;
}

u16 CMoonlibCommonIF::CamGainCmd( const EmTPExpGain& emGain )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamGainCmd( emGain );
	return re;
}

u16 CMoonlibCommonIF::SetCamGainCmd( const TGainMode& tGainMode )
{
    u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetCamGainCmd( tGainMode );
	return re;
}

u16 CMoonlibCommonIF::CamAutoWBCmd( const TCamWBMode& tCamWBMode )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamAutoWBCmd( tCamWBMode );
	return re;
}

u16 CMoonlibCommonIF::CamRGainCmd( const u32& dwRGain )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamRGainCmd( dwRGain );
	return re;
}

u16 CMoonlibCommonIF::CamBGainCmd( const u32& dwBGain )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamBGainCmd( dwBGain );
	return re;
}

u16 CMoonlibCommonIF::CamAdjustRangeCmd( const u32& dwAdjustRange )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamAdjustRangeCmd( dwAdjustRange );
	return re;
}

u16 CMoonlibCommonIF::CamHoriStretchCmd( const u32& dwHoriStretch )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamHoriStretchCmd( dwHoriStretch );
	return re;
}

u16 CMoonlibCommonIF::CamImageParaCmd( EmTPImagePara emImagePara, const u32& dwImagePara )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamImageParaCmd( emImagePara, dwImagePara );
	return re;
}

u16 CMoonlibCommonIF::CamLightPensation( BOOL bIsOpen )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamLightPensation( bIsOpen );
	return re;
}

u16 CMoonlibCommonIF::CamKeystoneAdjust( const TTPDistortParam& tTPDistortParam ,EmTPCorrect emMyOpetion )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamKeystoneAdjust( tTPDistortParam ,emMyOpetion);
	return re;
}

u16 CMoonlibCommonIF::SetColorRGBDirectCmd(u8 nPosition, EmTPColorConsistency emMyCorConsOption, const u32& dwRGBDirectValue)
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetColorRGBDirectCmd( nPosition, emMyCorConsOption, dwRGBDirectValue);
	return re;
}

u16 CMoonlibCommonIF::CamNRCmd( BOOL bIsOpen, EmTPFpgaReduNoise emTPReduNoise )
{	
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamNRCmd( bIsOpen, emTPReduNoise );
	return re;
}

u16 CMoonlibCommonIF::Cam2DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise )
{	
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->Cam2DNRCmd( bIsOpen, emTPReduNoise );
	return re;
}

u16 CMoonlibCommonIF::Cam3DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise )
{	
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->Cam3DNRCmd( bIsOpen, emTPReduNoise );
	return re;
}

u16 CMoonlibCommonIF::CamOrderPosCheckCmd( const TCamPresetNumberList& tCamPreset )
{	
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamOrderPosCheckCmd( tCamPreset );
	return re;
}

u16 CMoonlibCommonIF::RebootMoon()
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->RebootMoon();
	return re;
}

u16 CMoonlibCommonIF::MoonCamResetCmd(u8 byIndex)
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->MoonCamResetCmd(byIndex);
	return re;
}

u16 CMoonlibCommonIF::SetOutPortTypeCmd( EmTPDVIOutPortType emDVIOutPortType, EmTPMOONOutMode emMOONOutMode )
{
	u16 re = MOONSESSION_MGR_PTR->GetSysConfigIF()->SetOutPortTypeCmd( emDVIOutPortType, emMOONOutMode );
	return re;
}

u16 CMoonlibCommonIF::SetImageAdjustCmd( EmTPImageAdjust emImageAdjust )
{
	u16 re = MOONSESSION_MGR_PTR->GetSysConfigIF()->SetImageAdjustCmd( emImageAdjust );
	return re;
}

u16 CMoonlibCommonIF::UpdateEthnetCfg( const TRK100NetParam& tInfo )
{
	u16 re = MOONSESSION_MGR_PTR->GetSysConfigIF()->UpdateEthnetCfg( tInfo );
	return re;	
}

u16 CMoonlibCommonIF::GetNetWorkConfig()
{
    u16 re = MOONSESSION_MGR_PTR->GetSysConfigIF()->GetNetWorkConfig();
    return re;	
}

u16 CMoonlibCommonIF::GetNetWorkConfig( TRK100NetParam& tRK100NetParam )
{
    u16 re = MOONSESSION_MGR_PTR->GetSysConfigIF()->GetNetWorkConfig( tRK100NetParam );
    return re;	
}

u16 CMoonlibCommonIF::CamPreSetSaveCmd( const TTPCamPre& tTPCamPre )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamPreSetSaveCmd( tTPCamPre );
	return re;	
}

u16 CMoonlibCommonIF::OrderPosDeleteReq( const TTPCamPre& tTPCamPre )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->OrderPosDeleteReq( tTPCamPre );
	return re;	
}

u16 CMoonlibCommonIF::OrderPosInvokeCmd( const TTPCamPre& tTPCamPre )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->OrderPosInvokeCmd( tTPCamPre );
	return re;	
}

u16 CMoonlibCommonIF::CamPreSetModifyCmd( const TTPCamPre& tTPCamPre )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamPreSetModifyCmd( tTPCamPre );
	return re;	
}

u16 CMoonlibCommonIF::CamParamUploadCmd()
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamParamUploadCmd( );
	return re;	
}

u16 CMoonlibCommonIF::CamParamUploadNty( BOOL bSuccess )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->CamParamUploadNty( bSuccess );
	return re;	
}

u16 CMoonlibCommonIF::UpgradeMoon( const s8* chVerFileInfo )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->UpgradeMoon( chVerFileInfo );
	return re;	
}

u16 CMoonlibCommonIF::UpdateMoonMechanism(const s8* chVerFileInfo)
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->UpdateMoonMechanism( chVerFileInfo );
	return re;
}

u16 CMoonlibCommonIF::SetBaudRateCmd( EmTPLVDSBaud emBaudRate )
{
	u16 re = MOONSESSION_MGR_PTR->GetSysConfigIF()->SetBaudRateCmd( emBaudRate );
	return re;	
}

u16 CMoonlibCommonIF::SetReferenceLineCmd( BOOL bOpen )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetReferenceLineCmd( bOpen );
	return re;	
}

u16 CMoonlibCommonIF::SetHorizontalFlipCmd( BOOL bOpen )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetHorizontalFlipCmd( bOpen );
	return re;	
}

u16 CMoonlibCommonIF::SetTrapezoidalCorCmd( BOOL bOpen )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetTrapezoidalCorCmd( bOpen );
	return re;
}

u16 CMoonlibCommonIF::SetShowRectRegionCmd(BOOL bOpen)
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetShowRectRegionCmd( bOpen );
	return re;
}

u16 CMoonlibCommonIF::SetRgbConsistSwitchCmd(BOOL bOpen)
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetRgbConsistSwitchCmd( bOpen );
	return re;
}

u16 CMoonlibCommonIF::SetTraCorParamCmd( EmTPCorrect emMyCorOption,EmTPCorrectChange emChangeOption )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetTraCorParamCmd( emMyCorOption,emChangeOption);
	return re;
}

u16 CMoonlibCommonIF::SetCorConsistRGBCmd( u8 nPosition, EmTPColorConsistency emMyCorConsOption,EmTPCorrectChange emChangeOption )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetCorConsistRGBCmd(nPosition, emMyCorConsOption, emChangeOption);
	return re;
}

u16 CMoonlibCommonIF::SetChangeDistortCmd(u8 byIndex, EmTPCorrectChange emTPCorrectChange, EmTPDistortPosition emTPDistortPosition)
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	return re;
}

u16 CMoonlibCommonIF::SetDirectDistortCmd(const TTPDistortInfo& tTpDistortInfo)
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetDirectDistortCmd( tTpDistortInfo );
	return re;
}

u16 CMoonlibCommonIF::SetAutoSetColorConstancyCmd()
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetAutoSetColorConstancyCmd( );
	return re;
}

u16 CMoonlibCommonIF::SetChooseRectangleCmd( const TTPMoonRectRegion& tTPMoonRectRegion )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetChooseRectangleCmd( tTPMoonRectRegion );
	return re;
}

u16 CMoonlibCommonIF::SnapShotCmd( )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SnapShotCmd( );
	return re;
}

u16 CMoonlibCommonIF::SetDelayCorrectCmd( u8 nPosition, u32 dwDelay )
{
	u16 re = MOONSESSION_MGR_PTR->GetCamConfigIF()->SetDelayCorrectCmd( nPosition, dwDelay );
	return re;
}
