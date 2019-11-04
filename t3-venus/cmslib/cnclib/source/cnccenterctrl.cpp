#include "StdAfx.h"
#include "cnccenterctrl.h"

CCncCenterCtrl::CCncCenterCtrl(CCnsSession &cSession):CCncCenterCtrlIF()
{
	m_pSession = &cSession;
	BuildEventsMap();
}

CCncCenterCtrl::~CCncCenterCtrl()
{

}

void CCncCenterCtrl::BuildEventsMap()
{ 
    REG_PFUN( ev_cns_centreSchStateNty, CCncCenterCtrl::OnSchStateNty );
    REG_PFUN( ev_Cn_Sch_Temp_FB_Notify, CCncCenterCtrl::OnSchTempNty );
    
    REG_PFUN( ev_Cn_Sch_Power_Ind, CCncCenterCtrl::OnSchPowerInd );
    REG_PFUN( ev_Cn_Sch_Power_FB_Notify, CCncCenterCtrl::OnSchPowerNty );
    REG_PFUN( ev_Cn_Sch_Light_Ind, CCncCenterCtrl::OnSchLightInd );
    REG_PFUN( ev_Cn_Sch_Light_FB_Notify, CCncCenterCtrl::OnSchLightNty );
    REG_PFUN( ev_Cn_Sch_MidLight_Ind, CCncCenterCtrl::OnSchMainLightInd );
    REG_PFUN( ev_Cn_Sch_ScrLight_Ind, CCncCenterCtrl::OnSchAuxiLightInd );

    REG_PFUN( ev_cns_centreTVStateNty, CCncCenterCtrl::OnTvStateNty );
    REG_PFUN( ev_cns_centreselectTV_Ind, CCncCenterCtrl::OnSeleteTvInd );
    REG_PFUN( ev_cns_centreTVMode_Ind, CCncCenterCtrl::OnTvPowerModeInd );
    REG_PFUN( ev_cns_centreTVAudVisMode_Ind, CCncCenterCtrl::OnTvAudVisModeInd );
    REG_PFUN( ev_cns_centreTVDisMode_Ind, CCncCenterCtrl::OnTvDisModeInd );  
    REG_PFUN( ev_cns_centreTVInpSelect_Ind, CCncCenterCtrl::OnTvAudInpSelectInd );  
    REG_PFUN( ev_Cn_centreTVModleInd, CCncCenterCtrl::OnCentreTVModleInd );

    REG_PFUN( ev_Cn_DCamPower_Ind, CCncCenterCtrl::OnDCamPowerInd );
    REG_PFUN( ev_Cn_DCamAFMode_Ind, CCncCenterCtrl::OnDCamAFModeInd );
	REG_PFUN( ev_Cn_SetDCamPreset_Ind, CCncCenterCtrl::OnDCCamPresetInd );
    REG_PFUN( ev_Cn_DCamWBMode_Ind, CCncCenterCtrl::OnDCamWBModeInd );
    REG_PFUN( ev_Cn_DCamZoom_Ind, CCncCenterCtrl::OnDCamZoomInd );
	REG_PFUN( ev_Cn_SetDCamZoom_Ind, CCncCenterCtrl::OnDCamZoomValueInd );
    REG_PFUN( ev_Cn_DCamPreset_Ind, CCncCenterCtrl::OnDCamPresetInd );
    REG_PFUN( ev_Cn_DCamRecall_Ind, CCncCenterCtrl::OnDCamRecallInd );
	REG_PFUN( ev_Cn_DCamAutoExposureInd, CCncCenterCtrl::OnDCamExpModeInd );
	REG_PFUN( ev_Cn_DCamGainInd, CCncCenterCtrl::OnDCamExpGainNty );
	REG_PFUN( ev_Cn_DCamShutSpdInd, CCncCenterCtrl::OnDCamShutSpdNty );
	REG_PFUN( ev_Cn_DCamApertureInd, CCncCenterCtrl::OnDCamApertureNty );
	REG_PFUN( ev_Cn_DCamRGainInd, CCncCenterCtrl::OnDCamRGainInd );
	REG_PFUN( ev_Cn_DCamBGainInd, CCncCenterCtrl::OnDCamBGainInd );
    REG_PFUN( ev_cns_centreDCamStateNty, CCncCenterCtrl::OnDCamStateNty );

    REG_PFUN( ev_cns_centreACStateNty, CCncCenterCtrl::OnACStateNty );
    REG_PFUN( ev_Cn_CentreSetACTempInd, CCncCenterCtrl::OnACTempInd );
    REG_PFUN( ev_Cn_CentreSetACModeInd, CCncCenterCtrl::OnACModeInd );
    REG_PFUN( ev_Cn_CentreSetAirVolInd, CCncCenterCtrl::OnACAirVolInd );
	REG_PFUN( ev_Cn_CentreSetACPowerInd, CCncCenterCtrl::OnAirPowerInd );
	REG_PFUN( ev_cns_centreSelectAC_Ind, CCncCenterCtrl::OnSeleteAirInd );
	REG_PFUN( ev_cns_centreACCopyInd, CCncCenterCtrl::OnApplyToAllInd);
 
	REG_PFUN( ev_Cn_CamPowerStateNty, CCncCenterCtrl::OnCamStateNty );

	REG_PFUN( ev_CnCfgDisplay_Ind, CCncCenterCtrl::OnDisplayInd );
	REG_PFUN( ev_CnCfgDisplayShow_Nty, CCncCenterCtrl::OnCfgDisplayShowNty );
	REG_PFUN( ev_CnCfgDisplayShow_Ind, CCncCenterCtrl::OnCfgDisplayShowInd );

	//REG_PFUN( ev_Cn_CentreSleepNty, OnCentreSleepNty ); //在cnssession中响应
	//窗帘
	REG_PFUN( ev_Cn_centreCurInfoNty, CCncCenterCtrl::OnCurtainStateNty );
	REG_PFUN( ev_Cn_centreCurActInd, CCncCenterCtrl::OnCurtainActInd );
	REG_PFUN( ev_Cn_centreCurNameInd, CCncCenterCtrl::OnCurtainNameInd );
	REG_PFUN( ev_Cn_centreCurOpenInd, CCncCenterCtrl::OnCurtainInd );

	REG_PFUN( ev_Cn_DualScreenInfoNty, CCncCenterCtrl::OnDualScreenNty );
	REG_PFUN( ev_Cn_DualScreenOpenInd, CCncCenterCtrl::OnDualScreenInd );
	REG_PFUN( ev_Cn_centreCurNumInd, CCncCenterCtrl::OnCurtainNumberInd );

	REG_PFUN( ev_Cn_CentreSetACUsedInd,CCncCenterCtrl::OnAirConditionInd);
    //全景摄像机
	REG_PFUN( ev_Cns_SetPanCamNumInd,CCncCenterCtrl::OnPanCamNumberInd);
	REG_PFUN( ev_Cns_SetPanCamTypeInd,CCncCenterCtrl::OnPaCamModelInd);	
	//文档摄像机
	REG_PFUN( ev_Cn_DocSetUsedInd,CCncCenterCtrl::OnDCCamCfgInd);
	REG_PFUN( ev_Cn_DocSetTypeInd,CCncCenterCtrl::OnDcCamModelInd);	
	//断链通知
	REG_PFUN( OSP_DISCONNECT, CCncCenterCtrl::OnLinkBreak );
}

void CCncCenterCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CCncCenterCtrl, cMsg);
}

void CCncCenterCtrl::OnLinkBreak(const CMessage& cMsg)
{
	m_bDisplay = FALSE;
	m_bDisplayShow = FALSE;
	memset( &m_tDisplayType1, 0, sizeof(m_tDisplayType1) );
	memset( &m_tDisplayType3, 0, sizeof(m_tDisplayType3) );
	memset( m_atbIsCtrl, 0, sizeof(m_atbIsCtrl) );
    PrtMsg( OSP_DISCONNECT, emEventTypecnstoolRecv,"[CCncCenterCtrl::OnLinkBreak]清空配置信息" );
}

void CCncCenterCtrl::OnTimeOut(u16 wEvent)
{
	
}

//系统电源
u16 CCncCenterCtrl::SetSysPower( EmSchPower emPower )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_Sch_Power_Cmd );
    pcTpMsg->SetBody( &emPower, sizeof(EmSchPower) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_Sch_Power_Cmd, emEventTypeCnsSend, "EmSchPower: %d", emPower );
    
    return wRet;
}

void CCncCenterCtrl::OnSchPowerInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);

    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );

    EmSchPower emPower = *(EmSchPower*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_Sch_Power_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchPower: %d", bOk, emPower );

    PostEvent( UI_CNS_SCHPOWER_IND, bOk, emPower );
}

void CCncCenterCtrl::OnSchPowerNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    EmSchPower emPower = *(EmSchPower*)( cTpMsg.GetBody() );
    
    PrtMsg( ev_Cn_Sch_Power_FB_Notify, emEventTypeCnsRecv, "EmSchPower: %d", emPower );
}



u16 CCncCenterCtrl::SetSysAllLight( EmSchLight emLight )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_Sch_Light_Cmd );
    pcTpMsg->SetBody( &emLight, sizeof(EmSchLight) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_Sch_Light_Cmd, emEventTypeCnsSend, "EmSchLight: %d", emLight );
    
    return wRet;
}

void CCncCenterCtrl::OnSchLightInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmSchLight emLight = *(EmSchLight*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_Sch_Light_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchLight: %d", bOk, emLight );

    PostEvent( UI_CNS_SCHALLLIGHT_IND, bOk, emLight );
}

void CCncCenterCtrl::OnSchLightNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    EmSchLight emLight = *(EmSchLight*)( cTpMsg.GetBody() );
    
    PrtMsg( ev_Cn_Sch_Light_FB_Notify, emEventTypeCnsRecv, "EmSchLight: %d", emLight );

    PostEvent( UI_CNS_SCHLIGHT_NTY, emLight );
}

u16 CCncCenterCtrl::SetMainLight( EmSchMidLight emMidLight )
{
//     CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
//     pcTpMsg->SetUserData( m_pSession->GetInst() );
//     pcTpMsg->SetEvent( ev_Cn_Sch_MidLight_Cmd );
//     pcTpMsg->SetBody( &emMidLight, sizeof(EmSchMidLight) );
//     
//     u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
//     
//     PrtMsg( ev_Cn_Sch_MidLight_Cmd, emEventTypeCnsSend, "EmSchMidLight: %d", emMidLight );
    
    return TRUE;
}

void CCncCenterCtrl::OnSchMainLightInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmSchMidLight emLight = *(EmSchMidLight*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_Sch_MidLight_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchMidLight: %d", bOk, emLight );

    PostEvent( UI_CNS_SCHMIDLIGHT_IND, bOk, emLight );
}

u16 CCncCenterCtrl::SetAuxiLight( EmSchScrLight emScrLight )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_Sch_ScrLight_Cmd );
    pcTpMsg->SetBody( &emScrLight, sizeof(EmSchScrLight) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_Sch_ScrLight_Cmd, emEventTypeCnsSend, "EmSchScrLight: %d", emScrLight );
    
    return wRet;
}

void CCncCenterCtrl::OnSchAuxiLightInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmSchScrLight emLight = *(EmSchScrLight*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_Sch_ScrLight_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchScrLight: %d", bOk, emLight );

    PostEvent( UI_CNS_SCHSCRLIGHT_IND, bOk, emLight );
}

void CCncCenterCtrl::OnSchTempNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    u16 wTemp = *(u16*)( cTpMsg.GetBody() );
    
    PrtMsg( ev_Cn_Sch_Temp_FB_Notify, emEventTypeCnsRecv, "Temp: %d", wTemp );

    PostEvent( UI_CNS_SCHTEMP_NTY, wTemp );
}

void CCncCenterCtrl::OnSchStateNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    TCentreSchCfg tSchCfg = *(TCentreSchCfg*)( cTpMsg.GetBody() );
    
    PrtMsg( ev_cns_centreSchStateNty, emEventTypeCnsRecv, "EmSchPower: %d, EmSchLight: %d, EmSchMidLight: %d, EmSchScrLight: %d, Temp: %d",
        tSchCfg.emSchPower, tSchCfg.emSchLight, tSchCfg.emSchMidLight, tSchCfg.emSchScrLight, tSchCfg.wSchTem );

    PostEvent( UI_CNS_SCHSTATE_NTY, (WPARAM)&tSchCfg );
}



//电视机
u16 CCncCenterCtrl::SelectTV( u8 byIndex )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreselectTV_cmd );
    pcTpMsg->SetBody( &byIndex, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreselectTV_cmd, emEventTypeCnsSend, "Index: %d", byIndex );
    
	return wRet;
}

u16 CCncCenterCtrl::SetTVPowerMode( u8 byIndex, EmTvPowerMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVMode_cmd );  
    pcTpMsg->SetBody( &emMode, sizeof(EmTvPowerMode) );
    pcTpMsg->CatBody( &byIndex, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVMode_cmd, emEventTypeCnsSend, "Index: %d, EmTvPowerMode: %d", byIndex, emMode );
    
	return wRet;
}

u16 CCncCenterCtrl::SetTVAudVisMode( EmTVAudVisMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVAudVisMode_cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmTVAudVisMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVAudVisMode_cmd, emEventTypeCnsSend, "EmAudVisMode: %d", emMode );
    
    return wRet;
}

u16 CCncCenterCtrl::SetTVDisMode( EmTVDisplayMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVDisMode_cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmTVDisplayMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVDisMode_cmd, emEventTypeCnsSend, "EmDisplayMode: %d", emMode );
    
    return wRet;
}

u16 CCncCenterCtrl::SetTVInpSelect( u8 byIndex,  EmTVInputSelect emSelect )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVInpSelect_cmd );
    pcTpMsg->SetBody( &byIndex, sizeof(u8) );
	pcTpMsg->CatBody( &emSelect, sizeof(EmTVInputSelect) );
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVInpSelect_cmd, emEventTypeCnsSend,  "Index: %d, EmInputSelect: %d", byIndex, emSelect );
    
    return wRet;
}

void CCncCenterCtrl::OnTvStateNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    TCentreTVCfg *ptCentreTVCfg = reinterpret_cast<TCentreTVCfg *>(cTpMsg.GetBody());

    memcpy( m_atTVCfg, ptCentreTVCfg, sizeof(TCentreTVCfg)*MAX_CENTRETV_NUM );
    
    PrtMsg( ev_cns_centreTVStateNty, emEventTypeCnsRecv, "TvPowerMode1: %d, TvPowerMode2: %d, TvPowerMode3: %d, TVMode %d <emSharp70LCD_LX640A:%d \
	emSharp70LX550A:%d, emKeShi70GH01A:%d >",
        m_atTVCfg[0].emTvPowerMode, m_atTVCfg[1].emTvPowerMode, m_atTVCfg[2].emTvPowerMode ,m_atTVCfg[0].emTvModle,emSharp70LCD_LX640A,emSharp70LX550A,emKeShi70GH01A);

    PostEvent( UI_CNS_TVSTATE_NTY );
}

TCentreTVCfg* CCncCenterCtrl::GetCentreTVCfg()
{
    return m_atTVCfg;
}

//设置显示器型号
u16 CCncCenterCtrl::SetCentreTVModle( EmTVModle  emTvMode)
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_centreTVModleCmd );
    pcTpMsg->SetBody( &emTvMode, sizeof(EmTVModle) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_Cn_centreTVModleCmd, emEventTypeCnsSend,"DisplayMode %d < emSharp70LCD_LX640A:%d ; emSharp70LX550A:%d ;emKeShi70GH01A :%d ; emKangGuan70B17 : %d>", emTvMode,emSharp70LCD_LX640A,emSharp70LX550A,emKeShi70GH01A,emKangGuan70B17);
    
    return wRet;
}

u16 CCncCenterCtrl::SetDisplayShowCmd(BOOL bDisplayShow)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnCfgDisplayShow_Cmd );
	pcTpMsg->SetBody( &bDisplayShow, sizeof(BOOL) );

	u16 wRet = m_pSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_CnCfgDisplayShow_Cmd, emEventTypeCnsSend, "bDisplayShow: %d", bDisplayShow );

	return wRet;
}

void CCncCenterCtrl::OnCentreTVModleInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
	
    EmTVModle emTvMode = *(EmTVModle*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTVModle) );
	
    PrtMsg( ev_Cn_centreTVModleInd, emEventTypeCnsRecv,"Success %d ;DisplayMode %d < emSharp70LCD_LX640A:%d ; emSharp70LX550A:%d ; emKeShi70GH01A :%d ; emKangGuan70B17 : %d >",bOk,emTvMode,emSharp70LCD_LX640A,emSharp70LX550A,emKeShi70GH01A,emKangGuan70B17);
	PostEvent( UI_CNSTOOL_MSG_TVMode_IND, (WPARAM)&emTvMode, (LPARAM)&bOk);
}

void CCncCenterCtrl::OnSeleteTvInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    u8 byIndex = *(u8*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );

    PrtMsg( ev_cns_centreselectTV_Ind, emEventTypeCnsRecv, "Index: %d, bOk: %d", byIndex, bOk );
	PostEvent( UI_CNS_SELETETV_IND, byIndex, bOk);
}

void CCncCenterCtrl::OnTvPowerModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmTvPowerMode emMode = *(EmTvPowerMode*)( cTpMsg.GetBody() );
    u8 byIndex = *(u8*)( cTpMsg.GetBody() + sizeof(EmTvPowerMode) );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTvPowerMode) + sizeof(u8) );
    
    PrtMsg( ev_cns_centreTVMode_Ind, emEventTypeCnsRecv, "EmTvPowerMode: %d, Index: %d, bOK: %d", emMode, byIndex, bOk );

    if ( !bOk )
    {
        PostEvent( UI_CNS_TVPOWERMODE_IND, byIndex, emMode );
    }   
}

void CCncCenterCtrl::OnTvAudVisModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmTVAudVisMode emMode = *(EmTVAudVisMode*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTVAudVisMode) );
    
    PrtMsg( ev_cns_centreTVAudVisMode_Ind, emEventTypeCnsRecv, "EmTVAudVisMode: %d, bOK: %d", emMode, bOk );
}

void CCncCenterCtrl::OnTvDisModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmTVDisplayMode emMode = *(EmTVDisplayMode*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTVDisplayMode) );
    
    PrtMsg( ev_cns_centreTVDisMode_Ind, emEventTypeCnsRecv, "EmTVDisplayMode: %d, bOK: %d", emMode, bOk );
}

void CCncCenterCtrl::OnTvAudInpSelectInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
	u8 byIndex = *(u8*)( cTpMsg.GetBody() );
    EmTVInputSelect emMode = *(EmTVInputSelect*)( cTpMsg.GetBody() + sizeof(u8) );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTVInputSelect) + sizeof(u8) );
    
    PrtMsg( ev_cns_centreTVInpSelect_Ind, emEventTypeCnsRecv, "Index: %d, EmTVInputSelect: %d, bOK: %d", byIndex, emMode, bOk );
}


//文档摄像机
u16 CCncCenterCtrl::SetDCamPower( EmDCamPower emPower )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamPower_Cmd );
    pcTpMsg->SetBody( &emPower, sizeof(EmDCamPower) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamPower_Cmd, emEventTypeCnsSend, "EmDCamPower: %d", emPower );

    return wRet;
}

//自动焦距
u16 CCncCenterCtrl::SetDCamAFMode( EmDCamAFMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamAFMode_Cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmDCamAFMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamAFMode_Cmd, emEventTypeCnsSend, "EmDCamAFMode: %d  <emDcamAFOff %d , emDCamAFOn %d >", emMode ,emDcamAFOff,emDCamAFOn);
    
    return wRet;
}

//白平衡模式
u16 CCncCenterCtrl::SetDCamWBMode( EmDCamWBMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamWBMode_Cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmDCamWBMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamWBMode_Cmd, emEventTypeCnsSend, "EmDCamWBMode: %d <emDcamWBAuto %d , emDCamWBManual %d  >", emMode,emDcamWBAuto, emDCamWBManual);
    
    return wRet;
}

//视野调节
u16 CCncCenterCtrl::SetDCamZoom( EmDCamZoom emZoom, EmCnAction emAction )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamZoom_Cmd );
    pcTpMsg->SetBody( &emAction, sizeof(EmCnAction) );
    pcTpMsg->CatBody( &emZoom, sizeof(EmDCamZoom) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

    PrtMsg( ev_Cn_DCamZoom_Cmd, emEventTypeCnsSend,"EmCnAction: %d,EmZoom: %d",emAction, emZoom );
    
    return wRet;
}

//预置位
u16 CCncCenterCtrl::SetDCamPreset( EmDCamPresetNum emNum )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamPreset_Cmd );
    pcTpMsg->SetBody( &emNum, sizeof(EmDCamPresetNum) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamPreset_Cmd, emEventTypeCnsSend, "EmDCamPresetNum: %d", emNum  );
    
    return wRet;
}

u16 CCncCenterCtrl::SetDCamRecall( EmDCamRecallNum emNum )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamRecall_Cmd );
    pcTpMsg->SetBody( &emNum, sizeof(EmDCamRecallNum) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamRecall_Cmd, emEventTypeCnsSend, "EmDCamPresetNum: %d", emNum  );
    
    return wRet;
}


void CCncCenterCtrl::OnDCamPowerInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamPower emPower = *(EmDCamPower*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamPower_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamPower: %d", bOk, emPower );

    PostEvent( UI_CNS_DCAMPOWER_IND, bOk, emPower );
}

void CCncCenterCtrl::OnDCamAFModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamAFMode emMode = *(EmDCamAFMode*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamAFMode_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamAFMode: %d", bOk, emMode );

	PostEvent( UI_CNSTOOL_DCCAMERA_AUTO_FOCUS_IND, (WPARAM)emMode, (LPARAM)bOk );
}

void CCncCenterCtrl::OnDCamWBModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamWBMode emMode = *(EmDCamWBMode*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamWBMode_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamWBMode: %d", bOk, emMode );

	PostEvent( UI_CNSTOOL_DCCAMERA_WB_Nty, (WPARAM)emMode, (LPARAM)bOk );
}
	
void CCncCenterCtrl::OnDCamZoomInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamZoom emZoom = *(EmDCamZoom*)( cTpMsg.GetBody() + sizeof(BOOL) );
	u16  wZoonValue = *( u16 *)( cTpMsg.GetBody() + sizeof(BOOL) +sizeof( EmDCamZoom) );
    
    PrtMsg( ev_Cn_DCamZoom_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamZoom: %d,value %d", bOk, emZoom,wZoonValue);
	PostEvent( UI_CNSTOOL_DCCAMERA_ZOOM_Nty, (WPARAM)&wZoonValue, (LPARAM)&bOk );
}

u16 CCncCenterCtrl::SetDCamZoomValueCmd( const u16& wZoom )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &wZoom, sizeof(u16) );
	pcTpMsg->SetEvent(ev_Cn_SetDCamZoom_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_SetDCamZoom_Cmd, emEventTypecnstoolSend, "wZoom:%d", wZoom );
	return wRet;
}

void CCncCenterCtrl::OnDCamZoomValueInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    u16 wValue = *(u16*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u16) );
    
    PrtMsg( ev_Cn_SetDCamZoom_Ind, emEventTypecnstoolRecv, "bOk: %d, Value: %d", bOk, wValue );
	PostEvent( UI_CNSTOOL_DCCAMERA_ZOOM_Nty, (WPARAM)&wValue,(LPARAM)&bOk);
}

void CCncCenterCtrl::OnDCamPresetInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamPresetNum emNum = *(EmDCamPresetNum*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamPreset_Ind, emEventTypecnstoolRecv, "bOk: %d, EmDCamPresetNum: %d", bOk, emNum );
	PostEvent( UI_CNSTOOL_DCCAMERA_SavePreSet_Nty, (WPARAM)&bOk );
}

void CCncCenterCtrl::OnDCamRecallInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamRecallNum emNum = *(EmDCamRecallNum*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamRecall_Ind, emEventTypecnstoolRecv, "bOk: %d, EmDCamRecallNum: %d", bOk, emNum );
	PostEvent( UI_CNSTOOL_DCCAMERA_CallPreSet_Nty, (WPARAM)&bOk );
}

void CCncCenterCtrl::OnDCamStateNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    TCentreDCamCfg tDCamCfg = *(TCentreDCamCfg*)( cTpMsg.GetBody() );
    
    PrtMsg( ev_cns_centreDCamStateNty, emEventTypecnstoolRecv, "EmDCamPower: %d, EmDCamRecallNum: %d,EmDCamAFMode :%d,bRecallPresetOne:%d",
        tDCamCfg.emDCamPowerMode, tDCamCfg.emDCamRecallNum,tDCamCfg.tDCamCurPresetInfo.emDCamAFMode,tDCamCfg.bRecallPresetOne);

    PostEvent( UI_CNS_DCAMSTATE_NTY, (WPARAM)&tDCamCfg );
}


//空调
u16 CCncCenterCtrl::SetACTemp( u8 byTemp )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACTempCmd );
    pcTpMsg->SetBody( &byTemp, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACTempCmd, emEventTypeCnsSend, "Temp: %d", byTemp  );
    
    return wRet;
}

void CCncCenterCtrl::OnACTempInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    u8 byTemp = *(u8*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
    
    PrtMsg( ev_Cn_CentreSetACTempInd, emEventTypecnstoolRecv, "Temp: %d, bOk: %d", byTemp, bOk );
}

u16 CCncCenterCtrl::SetACMode( EmCentreACMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACModeCmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmCentreACMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACModeCmd, emEventTypeCnsSend, "EmCentreACMode: %d", emMode  );
    
    return wRet;
}

void CCncCenterCtrl::OnACModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmCentreACMode emMode = *(EmCentreACMode*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmCentreACMode) );
    
    PrtMsg( ev_Cn_CentreSetACModeInd, emEventTypeCnsRecv, "EmCentreACMode: %d, bOk: %d", emMode, bOk );
}

u16 CCncCenterCtrl::SetACAirVol( EmCentreACAirVol emAirVol )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACAirVolCmd );
    pcTpMsg->SetBody( &emAirVol, sizeof(EmCentreACAirVol) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACAirVolCmd, emEventTypeCnsSend, "EmCentreACAirVol: %d", emAirVol );
    
    return wRet;
}

void CCncCenterCtrl::OnACAirVolInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmCentreACAirVol emAirVol = *(EmCentreACAirVol*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmCentreACAirVol) );
    
    PrtMsg( ev_Cn_CentreSetAirVolInd, emEventTypeCnsRecv, "EmCentreACAirVol: %d, bOk: %d", emAirVol, bOk );
}


// void CCncCenterCtrl::OnACStateNty(const CMessage& cMsg)
// {
//     CTpMsg cTpMsg(&cMsg);
//     
//     TCentreACCfg tACCfg = *(TCentreACCfg*)( cTpMsg.GetBody() );
//     
//     PrtMsg( ev_cns_centreACStateNty, emEventTypeCnsRecv, "ACPower:%d, EmCentreACMode: %d, SetTemp: %d, CurTemp: %d, AirVol: %d",
//         tACCfg.emACPower ,tACCfg.emACMode, tACCfg.bySetTemp, tACCfg.byCurTemp, tACCfg.emACAirVol );
//     
//     PostEvent( UI_CNS_ACSTATE_NTY, (WPARAM)&tACCfg );
// }

//空调界面电源开关控制 by wqq
// u16 CCncCenterCtrl::SetAirPower( EmCentreACPower emPower )
// {
//     CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
//     pcTpMsg->SetUserData( m_pSession->GetInst() );
//     pcTpMsg->SetEvent( ev_Cn_CentreSetACPowerCmd );
//     pcTpMsg->SetBody( &emPower, sizeof( EmCentreACPower ) );
//     
//     u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
//     
//     PrtMsg( ev_Cn_CentreSetACPowerCmd, emEventTypeCnsSend, "EmCentreACPower: %d", emPower );
// 	
//     return wRet;
// }

u16 CCncCenterCtrl::SelectAir( u8 byIndex )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreSelectAC_Cmd );
    pcTpMsg->SetBody( &byIndex, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreSelectAC_Cmd, emEventTypeCnsSend, "Index: %d", byIndex );
    
	return wRet;
}

//选择空调项回复消息
void CCncCenterCtrl::OnSeleteAirInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
	
    u8 byIndex = *(u8*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	
    PrtMsg( ev_cns_centreSelectAC_Ind, emEventTypeCnsRecv, "Index: %d, bOk: %d", byIndex, bOk );

	PostEvent( UI_CNS_SELECTAIR_IND, byIndex, bOk );
}

void CCncCenterCtrl::OnACStateNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	
	TCentreACInfo tCentreACInfo = *reinterpret_cast<TCentreACInfo *>(cTpMsg.GetBody());
	m_vecTCentreACCfg.clear();
	for ( int i = 0; i < MAX_AC_NUM; i++ )
	{
		TCentreACCfg tCentreACCfg = tCentreACInfo.tCentreACCfg[i];//*reinterpret_cast<TCentreACCfg *>(cTpMsg.GetBody() + sizeof(TCentreACCfg)*i);
		
		BOOL bIsExist = tCentreACInfo.bACFlag[i];//*(BOOL *)(cTpMsg.GetBody() + sizeof(TCentreACCfg)*MAX_AC_NUM + sizeof(BOOL)*i);
		
		
		if ( bIsExist == TRUE)
		{
			m_vecTCentreACCfg.push_back( tCentreACCfg );
		}
	}
    
    PrtMsg( ev_cns_centreACStateNty, emEventTypeCnsRecv, "tCentreACInfo.byACNum=%d", tCentreACInfo.byACNum );
	
	PostEvent( UI_CNS_ACSTATE_NTY, ( WPARAM )&tCentreACInfo.byACNum, NULL );
}

void CCncCenterCtrl::GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg )const
{
     vecTCentreACCfg = m_vecTCentreACCfg;
	 return;
}

u16 CCncCenterCtrl::SetACPowerMode( u8 byIndex, EmCentreACPower emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACPowerCmd );  
	pcTpMsg->SetBody( &byIndex, sizeof(u8) );
    pcTpMsg->CatBody( &emMode, sizeof(EmCentreACPower) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACPowerCmd, emEventTypeCnsSend, "Index: %d, EmCentreACPower: %d", byIndex, emMode );
    
	return wRet;
}

void CCncCenterCtrl::OnAirPowerInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
	u8 byIndex = *(u8*)( cTpMsg.GetBody() );
	EmCentreACPower emPower = *(EmCentreACPower*)( cTpMsg.GetBody() + sizeof( u8 ) );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() +sizeof(u8) +sizeof( EmCentreACPower ) );
	
    PrtMsg( ev_Cn_CentreSetACPowerInd, emEventTypeCnsRecv, "Index: %d, EmCentreACPower: %d, bOk: %d", byIndex, emPower, bOk );
	
    //PostEvent( UI_CNS_ACPOWERSTATE_IND, emPower, bOk );
}

u16 CCncCenterCtrl::SetApplyToAll( u8 byIndex, BOOL** atbIsCtrl )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_cns_centreACCopyCmd ); 
	pcTpMsg->SetBody( &byIndex, sizeof(u8) );
	pcTpMsg->CatBody( *atbIsCtrl, sizeof(BOOL) );
	pcTpMsg->CatBody( (*atbIsCtrl)+1, sizeof(BOOL) );
	pcTpMsg->CatBody( (*atbIsCtrl)+2, sizeof(BOOL) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_cns_centreACCopyCmd, emEventTypeCnsSend,"Index: %d, SetApplyToAll", byIndex );
	return wRet;
}

void CCncCenterCtrl::OnApplyToAllInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	for ( int i = 0; i < MAX_AC_NUM; i++ )
	{
		BOOL bIsInCtrl = *(BOOL*)( cTpMsg.GetBody()+sizeof(BOOL)*i );
		m_atbIsCtrl[i] = bIsInCtrl;
		BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody()+3*sizeof(BOOL)+sizeof(BOOL)*i );
	}
	PrtMsg( ev_cns_centreACCopyInd, emEventTypeCnsRecv,"OnApplyToAllInd" );

//	PostEvent( UI_CNS_APPLYTOALL_IND );
}

BOOL* CCncCenterCtrl::GetApplyToAllInfo()
{
	return m_atbIsCtrl;
}

//摄像机
void CCncCenterCtrl::OnCamStateNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	EmCamPowerMode aemCam[MAX_CNCAMERA_NUM];
	for ( int i=0; i<MAX_CNCAMERA_NUM; i++ )
	{
		aemCam[i] = *(EmCamPowerMode*)( cTpMsg.GetBody() + i*sizeof(EmCamPowerMode) );
	}
     
    PrtMsg( ev_Cn_CamPowerStateNty, emEventTypeCnsRecv, "Cam1: %d, Cam2: %d, Cam3: %d", aemCam[0], aemCam[1], aemCam[2] );
	
    PostEvent( UI_CNSTOOL_MSG_CamPowerState_NTY, (WPARAM)aemCam );
}


void CCncCenterCtrl::OnCentreSleepNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    PrtMsg( ev_Cn_CentreSleepNty, emEventTypeCnsRecv, "" );
    
    PostEvent( UI_TPAD_CENTRESLEEP_NTY );
}

//中控电视墙
u16 CCncCenterCtrl::SetDisplayCmd( BOOL bDisplay, const TTPDisplayType& tDisplayType1, const TTPDisplayType& tDisplayType3 )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnCfgDisplay_Cmd );  
	pcTpMsg->SetBody( &bDisplay, sizeof(BOOL) );
    pcTpMsg->CatBody( &tDisplayType1, sizeof(TTPDisplayType) );
    pcTpMsg->CatBody( &tDisplayType3, sizeof(TTPDisplayType) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_CnCfgDisplay_Cmd, emEventTypeCnsSend, "bDisplay: %d, tDisplayType1: %d,%d, tDisplayType3: %d,%d \
<emTVHDMI1:%d,emTVHDMI2:%d,emTVHDMI3:%d,emTVHDMI4:%d,emTVYpbPr:%d,emTVCVBS1:%d,emTVCVBS2:%d,emTVComputer:%d>", 
bDisplay, tDisplayType1.emTPT300Type, tDisplayType1.emTPHduType, tDisplayType3.emTPT300Type, tDisplayType3.emTPHduType, \
emTVHDMI1, emTVHDMI2, emTVHDMI3, emTVHDMI4, emTVYpbPr, emTVCVBS1, emTVCVBS2, emTVComputer );
    
	return wRet;
}

const BOOL& CCncCenterCtrl::GetDisplayState() const
{
	return m_bDisplay;
}

const TTPDisplayType& CCncCenterCtrl::GetDisplayType1() const
{
	return m_tDisplayType1;
}

const TTPDisplayType& CCncCenterCtrl::GetDisplayType3() const
{
	return m_tDisplayType3;
}

const BOOL& CCncCenterCtrl::GetDisplayShowState() const
{
	return m_bDisplayShow;
}

void CCncCenterCtrl::OnDisplayInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	m_bDisplay = *(BOOL*)cTpMsg.GetBody();
	m_tDisplayType1 = *(TTPDisplayType*)( cTpMsg.GetBody() + sizeof(BOOL) );
	m_tDisplayType3 = *(TTPDisplayType*)( cTpMsg.GetBody() + sizeof(TTPDisplayType) + sizeof(BOOL) );
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPDisplayType)*2 + sizeof(BOOL) );

    PrtMsg( ev_CnCfgDisplay_Ind, emEventTypeCnsRecv, "bDisplay: %d, tDisplayType1: %d,%d, tDisplayType3: %d,%d \
<emTVHDMI1:%d,emTVHDMI2:%d,emTVHDMI3:%d,emTVHDMI4:%d,emTVYpbPr:%d,emTVCVBS1:%d,emTVCVBS2:%d,emTVComputer:%d>", 
m_bDisplay, m_tDisplayType1.emTPT300Type, m_tDisplayType1.emTPHduType, m_tDisplayType3.emTPT300Type, m_tDisplayType3.emTPHduType, \
emTVHDMI1, emTVHDMI2, emTVHDMI3, emTVHDMI4, emTVYpbPr, emTVCVBS1, emTVCVBS2, emTVComputer );
	
    PostEvent( UI_CNSTOOL_MSG_DISPLAY_IND, bSuccess, 0 );
}

void CCncCenterCtrl::OnCfgDisplayShowNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	m_bDisplayShow = *(BOOL*)cTpMsg.GetBody();

	PrtMsg( ev_CnCfgDisplayShow_Nty, emEventTypeCnsRecv, "bDisplayShow: %d", m_bDisplayShow );
	PostEvent( UI_CNSTOOL_DISPLAY_SHOW_Nty, 0, 0 );	
}

void CCncCenterCtrl::OnCfgDisplayShowInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	m_bDisplayShow = *(BOOL*)cTpMsg.GetBody();

	PrtMsg( ev_CnCfgDisplayShow_Ind, emEventTypeCnsRecv, "bDisplayShow: %d", m_bDisplayShow );
	PostEvent( UI_CNSTOOL_DISPLAY_SHOW_Ind, 0, 0 );	
}

//577 3/10
void CCncCenterCtrl::GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName ) const
{
	vecTCentreCurName = m_vecTCentreCurName;
}

void CCncCenterCtrl::OnCurtainStateNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	TCentreCurInfo tCurttain;
	tCurttain = *(TCentreCurInfo*)(cTpMsg.GetBody());
	m_vecTCentreCurName.clear();
	for ( int i=0; i < tCurttain.byCurNum; i++ )
	{
		TCentreCurName tCentreCurName = tCurttain.tCenCurName[i];

		m_vecTCentreCurName.push_back( tCentreCurName );
	//	PrtMsg( ev_Cn_centreCurInfoNty, emEventTypeCnsRecv, "%s ", tCentreCurName.achCurName );
	}

	u8 nCurNum = tCurttain.byCurNum;
	m_tCentreCurtain = tCurttain;
	PrtMsg( ev_Cn_centreCurInfoNty, emEventTypeCnsRecv, " CurtainNum: %d", nCurNum );

	PostEvent( UI_TPAD_CURTAINSTATE_NTY, nCurNum );
}

u16 CCncCenterCtrl::SetCurtainState( BOOL** bIsCtrl, EmCurAction emCurAction )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	
	pcTpMsg->SetEvent( ev_Cn_centreCurActCmd ); 
	pcTpMsg->SetBody( *bIsCtrl, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+1, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+2, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+3, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+4, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+5, sizeof(BOOL) );
	pcTpMsg->CatBody( &emCurAction, sizeof(EmCurAction));
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_centreCurActCmd, emEventTypeCnsSend,"SetCurtainState" );
	return wRet;
}

void CCncCenterCtrl::OnCurtainActInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	for ( int i = 0; i < MAX_CURTAIN_NUM; i++ )
	{
		BOOL bIsCtrl = *(BOOL*)( cTpMsg.GetBody()+sizeof(BOOL)*i );
		m_bIsCtrl[i] = bIsCtrl;
		EmCurAction emCurAction = *(EmCurAction*)( cTpMsg.GetBody() + 6*sizeof(BOOL) );
		BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody()+6*sizeof(BOOL)+sizeof(EmCurAction)+sizeof(BOOL)*i );
	}
	PrtMsg( ev_Cn_centreCurActInd, emEventTypeCnsRecv,"IsCtrl1: %d, IsCtrl2: %d, IsCtrl3: %d, IsCtrl4: %d, IsCtrl5: %d, IsCtrl6: %d", m_bIsCtrl[0], m_bIsCtrl[1], m_bIsCtrl[2], m_bIsCtrl[3], m_bIsCtrl[4], m_bIsCtrl[5] );
}

const TCentreCurInfo& CCncCenterCtrl::GetCurtainInfo( ) const
{
	return m_tCentreCurtain;
}

u16 CCncCenterCtrl::SetPanCamNumber( const u8 &byPanCamNum ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cns_SetPanCamNumCmd );
    pcTpMsg->SetBody( &byPanCamNum, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
    PrtMsg( ev_Cns_SetPanCamNumCmd, emEventTypeCnsSend,"Panoramic camera Number: %d ",byPanCamNum );
    
    return wRet;
}

void CCncCenterCtrl::OnPanCamNumberInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	u8 byPanCamNum =  *(u8*)(cTpMsg.GetBody()+ sizeof(BOOL) );
	BOOL bSuccess =  *(BOOL*)(cTpMsg.GetBody());

	PrtMsg( ev_Cns_SetPanCamNumInd, emEventTypecnstoolRecv, "byPanCamNum %d  ;Success %d ",byPanCamNum ,bSuccess);
	
	PostEvent( UI_CNSTOOL_PanCamNum_Nty, (WPARAM)&byPanCamNum,(LPARAM)&bSuccess );
}

u16 CCncCenterCtrl::SetDCCamFocus( EmFocus emFocusMode ,EmCnAction emAction ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamFocusCmd );
    pcTpMsg->SetBody( &emFocusMode, sizeof(EmFocus) );
    pcTpMsg->CatBody( &emAction, sizeof(EmCnAction) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
    PrtMsg( ev_Cn_DCamFocusCmd, emEventTypeCnsSend,"EmFocus: %d < emFar : 0 ; emNear : 1 > , %d ",emFocusMode, emAction);
    
    return wRet;
}

u16 CCncCenterCtrl::SetDCCamExposure( EmExpMode emExpMode ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamAutoExposureCmd );
    pcTpMsg->SetBody( &emExpMode, sizeof(EmExpMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
    PrtMsg( ev_Cn_DCamAutoExposureCmd, emEventTypeCnsSend,"EmExpMode: %d < emExpAuto : 0 ; emExpManuel : 1 >",emExpMode );
    
    return wRet;
}

void CCncCenterCtrl::OnDCamExpModeInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	EmExpMode emDCamExpMode = *(EmExpMode*)( cTpMsg.GetBody() );
	BOOL bSuccess = *( BOOL * )( cTpMsg.GetBody() + sizeof( EmExpMode ) );
	
	PrtMsg( ev_Cn_DCamAutoExposureInd, emEventTypecnstoolRecv,"bSuccess: %d , EmExpMode: %d  <emExpAuto %d ; emExpManuel %d >",bSuccess,emDCamExpMode,emExpAuto, emExpManuel);
	
    PostEvent( UI_CNSTOOL_DCamExposure_Nty, (WPARAM)&emDCamExpMode,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetDCCamExpGainCmd( EmDCamGain emExpGain ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamGainCmd );
    pcTpMsg->SetBody( &emExpGain, sizeof(EmDCamGain) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
    PrtMsg( ev_Cn_DCamGainCmd, emEventTypeCnsSend,"EmDCamGain: %d < 0:emN10_5dB ;1:emN9dB ;2:emN7_5dB ;3:emN6dB ;4:emN4_5dB ;5:emN3dB ; \
		6:emN1_5dB ;7:emD0dB ;8:emP1_5dB ;9:emP3dB ;10:emP4_5dB ;11:emP6dB ;12:emP7_5dB ;13:emP9dB ;14:emP10_5dB >",emExpGain );
    
    return wRet;
}

void CCncCenterCtrl::OnDCamExpGainNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	EmDCamGain emDCamGain = *(EmDCamGain*)( cTpMsg.GetBody() );
	BOOL bSuccess = *( BOOL * )( cTpMsg.GetBody() + sizeof( EmDCamGain ) );
	
	PrtMsg( ev_Cn_DCamGainInd, emEventTypecnstoolRecv,"bSuccess: %d , EmDCamGain: %d  < 0:emN10_5dB ;1:emN9dB ;2:emN7_5dB ;3:emN6dB ;4:emN4_5dB ;5:emN3dB ;\
		6:emN1_5dB ;7:emD0dB ;8:emP1_5dB ;9:emP3dB ;10:emP4_5dB ;11:emP6dB ;12:emP7_5dB ;13:emP9dB ;14:emP10_5dB >",bSuccess,emDCamGain );
	
    PostEvent( UI_CNSTOOL_DCamGain_Nty, (WPARAM)&emDCamGain,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetDCCamAperture( EmDCamIris emAperture ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamApertureCmd );
    pcTpMsg->SetBody( &emAperture, sizeof(EmDCamIris) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_DCamApertureCmd, emEventTypeCnsSend,"EmDCamIris: %d",emAperture);
	
	return wRet;
}

void CCncCenterCtrl::OnDCamApertureNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	EmDCamIris emDCamAperture = *(EmDCamIris*)( cTpMsg.GetBody() );
	BOOL bSuccess = *( BOOL * )( cTpMsg.GetBody() + sizeof( EmDCamIris ) );
	
	PrtMsg( ev_Cn_DCamApertureInd, emEventTypecnstoolRecv,"bSuccess: %d , EmDCamIris: %d  < 0:emDIrisClose ;1:emDIrisF14 ;2:emDIrisF11 ;3:emDIrisF9_6 ;4:emDIrisF8 ;5:emDIrisF6_8 ;\
		6:emDIrisF5_6 ;7:emDIrisF4_8 ;8:emDIrisF4 ;9:emDIrisF3_4 ;10:emDIrisF2_8 ;11:emDIrisF2_4 ;12:emDIrisF2 ;13:emDIrisF1_6 >",bSuccess,emDCamAperture );
	
    PostEvent( UI_CNSTOOL_DCamAperture_Nty,(WPARAM)&emDCamAperture,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetDCCamShutCmd( EmDCamShutSpd emShutSpd ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamShutSpdCmd );
    pcTpMsg->SetBody( &emShutSpd, sizeof(EmDCamShutSpd) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_Cn_DCamShutSpdCmd, emEventTypeCnsSend,"EmDCamShutSpd: %d ",emShutSpd );
	return wRet;
}

void CCncCenterCtrl::OnDCamShutSpdNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	EmDCamShutSpd emDCamShutSpd = *(EmDCamShutSpd*)( cTpMsg.GetBody() );
	BOOL bSuccess = *( BOOL * )( cTpMsg.GetBody() + sizeof( EmDCamShutSpd ) );
	
	PrtMsg( ev_Cn_DCamShutSpdInd, emEventTypecnstoolRecv,"bSuccess: %d , EmDCamGain: %d  < 0:emDShutSpd0 ;1:emDShutSpd1 ;2:emDShutSpd2 ;3:emDShutSpd3 ;4:emDShutSpd4 ;5:emDShutSpd5 ;\
		6:emDShutSpd6 ;7:emDShutSpd7 ;8:emDShutSpd8 ;9:emDShutSpd9 ;10:emDShutSpdA ;11:emDShutSpdB ;12:emDShutSpdC ;13:emDShutSpdD ;14:emDShutSpdE ;15:emDShutSpdF ;16:emDShutSpd10 >",bSuccess,emDCamShutSpd );
	
    PostEvent( UI_CNSTOOL_DCamShut_Nty, (WPARAM)&emDCamShutSpd,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetDcCamRGainCmd( const u16& wRGain ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamRGainCmd );
    pcTpMsg->SetBody( &wRGain, sizeof( u16 ) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_DCamRGainCmd, emEventTypeCnsSend, "wRGain:%d", wRGain );
	return wRet;
}

void CCncCenterCtrl::OnDCamRGainInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	u16 wRGain = *(u16*)( cTpMsg.GetBody() );
	BOOL bSuccess = *( BOOL * )( cTpMsg.GetBody() + sizeof( u16 ) );
	
	PrtMsg( ev_Cn_DCamRGainInd, emEventTypecnstoolRecv,"bSuccess: %d , RGain: %d ",bSuccess,wRGain );
	
    PostEvent( UI_CNSTOOL_DCCAMERA_RGain_Nty,(WPARAM)&wRGain,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetDcCamBGainCmd( const u16& wBGain ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamBGainCmd );
    pcTpMsg->SetBody( &wBGain, sizeof( u16 ) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_DCamBGainCmd, emEventTypeCnsSend, "wBGain:%d", wBGain );
	return wRet;
}

void CCncCenterCtrl::OnDCamBGainInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	u16 wBGain = *(u16*)( cTpMsg.GetBody() );
	BOOL bSuccess = *( BOOL * )( cTpMsg.GetBody() + sizeof( u16 ) );
	
	PrtMsg( ev_Cn_DCamBGainInd, emEventTypecnstoolRecv,"bSuccess: %d , BGain: %d ",bSuccess,wBGain );
	
    PostEvent( UI_CNSTOOL_DCCAMERA_BGain_Nty,(WPARAM)&wBGain,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetCurtainNumberCmd( const u8& byCurNum ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_centreCurNumCmd );
    pcTpMsg->SetBody( &byCurNum, sizeof( u8 ) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_centreCurNumCmd, emEventTypeCnsSend, "Curtain Number:%d", byCurNum );
	return wRet;
}

void CCncCenterCtrl::OnCurtainNumberInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	u8 byCurtainNum = *(u8*)( cTpMsg.GetBody() );
	BOOL bSuccess = *( BOOL * )( cTpMsg.GetBody() + sizeof( u8 ) );
	
	if ( bSuccess == TRUE )
	{
		m_tCentreCurtain.byCurNum = byCurtainNum;
	}

	PrtMsg( ev_Cn_centreCurNumInd, emEventTypecnstoolRecv,"bSuccess: %d , CurtainNum: %d ",bSuccess,byCurtainNum );
	
    PostEvent( UI_CNSTOOL_CENTRE_CurNumSet_Nty,(WPARAM)&byCurtainNum,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetCurtainName( const u8& byCurIndex, const TCentreCurName &tCurtainName) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_centreCurNameCmd );
    pcTpMsg->SetBody( &byCurIndex, sizeof( u8 ) );
	pcTpMsg->CatBody( &tCurtainName, sizeof( tCurtainName ) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_centreCurNameCmd, emEventTypeCnsSend, "Curtain Index :%d, Curtain Name %s", byCurIndex ,tCurtainName.achCurName);
	return wRet;
}

void CCncCenterCtrl::OnCurtainNameInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	u8 byCurtainIndex = *(u8*)( cTpMsg.GetBody() );
	TCentreCurName tCurtainName = *(TCentreCurName*)( cTpMsg.GetBody() +sizeof(u8));
	BOOL bSuccess = *( BOOL * )( cTpMsg.GetBody() + sizeof( u8 ) +sizeof(TCentreCurName));
	
	PrtMsg( ev_Cn_centreCurNameInd, emEventTypecnstoolRecv,"bSuccess: %d , CurtainIndex: %d  Name %s",bSuccess,byCurtainIndex,tCurtainName.achCurName);
	if ( bSuccess == TRUE )
	{
		if ( (byCurtainIndex >=0 )&&( byCurtainIndex < 6 ))
		{
			m_tCentreCurtain.tCenCurName[byCurtainIndex] = tCurtainName;
		}
	}
	
	PostEvent( UI_CNSTOOL_CENTRE_CurRename_Nty,(WPARAM)&m_tCentreCurtain,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetCurtainOpen( const BOOL& bOpen ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_centreCurOpenCmd );
    pcTpMsg->SetBody( &bOpen,sizeof( BOOL ) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_centreCurOpenCmd, emEventTypeCnsSend, "Curtain:%d ", bOpen);
	return wRet;
}

void CCncCenterCtrl::OnCurtainInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)( cTpMsg.GetBody() );
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() +sizeof(BOOL));
	
	PrtMsg( ev_Cn_centreCurOpenInd, emEventTypecnstoolRecv,"bOpen: %d , bSuccess: %d ",bOpen,bSuccess );
	
	PostEvent( UI_CNSTOOL_CENTRE_CurOpen_Nty,(WPARAM)&bOpen,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetDuoVideoCmd( const BOOL& bOpen ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DualScreenOpenCmd );
    pcTpMsg->SetBody( &bOpen,sizeof( BOOL ) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_DualScreenOpenCmd, emEventTypeCnsSend, "Duovideo:%d ", bOpen);
	return wRet;
}

void CCncCenterCtrl::OnDualScreenInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody());
	BOOL bOpen = *(BOOL*)( cTpMsg.GetBody() +sizeof(BOOL) );

	PrtMsg( ev_Cn_DualScreenOpenInd, emEventTypecnstoolRecv,"bOpen: %d , bSuccess: %d ",bOpen,bSuccess );
	
	PostEvent( UI_CNSTOOL_DUALSCREEN_Nty,(WPARAM)&bOpen,(LPARAM)&bSuccess);
}

void CCncCenterCtrl::OnDualScreenNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	BOOL bSuccess = TRUE;

	TDualScreenInfo tDualScreenInfo = *(TDualScreenInfo*)( cTpMsg.GetBody() );

	PrtMsg( ev_Cn_DualScreenInfoNty, emEventTypecnstoolRecv,"bOpen: %d",tDualScreenInfo.bDualScreenOpen );
	
	PostEvent( UI_CNSTOOL_DUALSCREEN_Nty,(WPARAM)&tDualScreenInfo.bDualScreenOpen,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetDCCamOpenCmd( const BOOL& bOpen ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_Cn_DocSetUsedCmd );
	pcTpMsg->SetBody( &bOpen,sizeof( BOOL ) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_DocSetUsedCmd, emEventTypeCnsSend, "DC Camera:%d ", bOpen);
	return wRet;
}

u16 CCncCenterCtrl::SetDCCamPreset( const BOOL& bPreset ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_Cn_SetDCamPreset_Cmd );
	pcTpMsg->SetBody( &bPreset,sizeof( BOOL ) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_SetDCamPreset_Cmd, emEventTypeCnsSend, "预置位1:%d ", bPreset);
	return wRet;
}

void CCncCenterCtrl::OnDCCamPresetInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody());
	BOOL bPreset = *(BOOL*)( cTpMsg.GetBody() +sizeof(BOOL) );
	
	PrtMsg( ev_Cn_SetDCamPreset_Ind, emEventTypecnstoolRecv,"预置位1: %d , bSuccess: %d ",bPreset,bSuccess );
	
	PostEvent( UI_CNSTOOL_DCCamBootCallPreset_Nty,(WPARAM)&bPreset,(LPARAM)&bSuccess);
}

void CCncCenterCtrl::OnDCCamCfgInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody());
	BOOL bOpen = *(BOOL*)( cTpMsg.GetBody() +sizeof(BOOL) );
	
	PrtMsg( ev_Cn_DocSetUsedInd, emEventTypecnstoolRecv,"bOpen: %d , bSuccess: %d ",bOpen,bSuccess );
	
	PostEvent( UI_CNSTOOL_DCCamCfg_Nty,(WPARAM)&bOpen,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetAirConditionCmd( const u8& byAcNum ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_Cn_CentreSetACUsedCmd );
	pcTpMsg->SetBody( &byAcNum,sizeof( u8 ) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_CentreSetACUsedCmd, emEventTypeCnsSend, "AC Number :%d ", byAcNum);
	return wRet;
}

void CCncCenterCtrl::OnAirConditionInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody());
	u8 byAcNum = *(u8*)( cTpMsg.GetBody() +sizeof(BOOL) );
	
	PrtMsg( ev_Cn_CentreSetACUsedInd, emEventTypecnstoolRecv,"AC Number: %d , bSuccess: %d ",byAcNum,bSuccess );
	
	PostEvent( UI_CNSTOOL_AirCondtition_Nty,(WPARAM)&byAcNum,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetDcCamModel( EmDCamProType emDcCamType ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_Cn_DocSetTypeCmd );
	pcTpMsg->SetBody( &emDcCamType,sizeof( EmDCamProType ) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_DocSetTypeCmd, emEventTypeCnsSend, "Dc Camera Type :%d< Invalid %d , PRS200 %d , IPC822 %d > ", emDcCamType,emDcamInvalid,emVISCAPro,emPELCOPro);
	return wRet;
}

void CCncCenterCtrl::OnDcCamModelInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	EmDCamProType emDcCamType = *(EmDCamProType*)( cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() +sizeof(EmDCamProType) );
	
	PrtMsg( ev_Cn_DocSetTypeInd, emEventTypecnstoolRecv,"Dc Camera Type :%d< Invalid %d , PRS200 %d , IPC822 %d >  Success: %d", 
		emDcCamType,emDcamInvalid,emVISCAPro,emPELCOPro ,bSuccess);
	
	PostEvent( UI_CNSTOOL_DocCamType_Nty,(WPARAM)&emDcCamType,(LPARAM)&bSuccess);
}

u16 CCncCenterCtrl::SetPaCamModel( EmQCamProType emPaCamType ) const
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_Cns_SetPanCamTypeCmd );
	pcTpMsg->SetBody( &emPaCamType,sizeof( EmQCamProType ) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cns_SetPanCamTypeCmd, emEventTypeCnsSend, "Pa Camera Type :%d< Invalid %d , 120E %d , MOON50 %d > ", emPaCamType,emQamInvalid,em120E,emMoon50);
	return wRet;
}

void CCncCenterCtrl::OnPaCamModelInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() );
	EmQCamProType emPaCamType = *(EmQCamProType*)( cTpMsg.GetBody() + sizeof(BOOL)  );
	
	PrtMsg( ev_Cns_SetPanCamTypeInd, emEventTypecnstoolRecv,"Pa Camera Type :%d< Invalid %d , 120E %d , MOON50 %d >  Success: %d", 
		emPaCamType,emQamInvalid,em120E,emMoon50 ,bSuccess);
	
	PostEvent( UI_CNSTOOL_PanCamType_Nty,(WPARAM)&emPaCamType,(LPARAM)&bSuccess);
}
