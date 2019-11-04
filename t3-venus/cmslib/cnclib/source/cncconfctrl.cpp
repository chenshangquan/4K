// cncconfctrl.cpp: implementation of the CCncConfCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cncconfctrl.h"
#include "tptype.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCncConfCtrl::CCncConfCtrl(CCnsSession &cSession) : CCncConfCtrlIF(), 
                                                    m_bRecvDual(FALSE),
                                                    m_nVideoNode(TP_INVALID_INDEX),
                                                    m_nAudioNode(TP_INVALID_INDEX)
{
	m_pSession = &cSession;
	m_bMute = FALSE;
	m_bQuite = FALSE;
	m_byInputVol = 0;
	m_byOutputVol = 0;
	m_bySpeakSeat = 0;
    m_bPoll = FALSE;       //是否开启轮询
    m_bDual = FALSE;
	m_bLocalPIP = FALSE;

	BuildEventsMap();
}

CCncConfCtrl::~CCncConfCtrl()
{
	
}


void CCncConfCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CCncConfCtrl, cMsg);
}


void CCncConfCtrl::BuildEventsMap()
{
    REG_PFUN( ev_CnConfState_Nty, CCncConfCtrl::OnConfStateNty );
    REG_PFUN( ev_tppQuietInd, CCncConfCtrl::OnQuietInd );
    REG_PFUN( ev_tppMuteInd, CCncConfCtrl::OnMuteInd );
    REG_PFUN( ev_tppInputVolumeInd, CCncConfCtrl::OnInputVolInd );
    REG_PFUN( ev_tppOutputVolumeInd, CCncConfCtrl::OnOutPutVolInd );
    REG_PFUN( ev_CnSetInnerSpeaker_Ind, CCncConfCtrl::OnSetInnerSpeaker );
  //  REG_PFUN( ev_CnYouAreSeeing_Ind, OnScreenDisplayInd );	改用ev_CnPosAllStatus_Nty，2012-3-15 yjj
  //  REG_PFUN( ev_CnActivePos_Nty, OnScreenStateNotify );  改用ev_CnPosAllStatus_Nty，2012-3-15 yjj

    REG_PFUN( ev_CnPosAllStatus_Nty, CCncConfCtrl::OnScreenStateNotify );
   
    REG_PFUN( ev_TppStartDual_Ind, CCncConfCtrl::OnStartDualRsp );
    REG_PFUN( ev_TppStopDual_Ind, CCncConfCtrl::OnStartDualRsp );
    REG_PFUN( ev_TppIsDual_Nty, CCncConfCtrl::OnDualStatusNty );
    
    REG_PFUN( ev_CnStartPoll_Ind, CCncConfCtrl::OnStartPollRsp );
    REG_PFUN( ev_CnStopPoll_Ind,  CCncConfCtrl::OnStartPollRsp );  
	REG_PFUN( ev_CnPollStatus_Nty,  CCncConfCtrl::OnPollStatusNty ); 

	REG_PFUN( ev_TppHangUp_Ind,  CCncConfCtrl::OnHungupNotify );

    REG_PFUN( ev_TppAddDualRcvAddr_Ind, CCncConfCtrl::OnStartDualCdStrmRsp );
    REG_PFUN( ev_TppDelDualRcvAddr_Ind, CCncConfCtrl::OnStopDualCdStrmRsp );

    REG_PFUN( ev_TppIsRcvDual_Nty, CCncConfCtrl::OnRecvDualNty );

    REG_PFUN( ev_CnSingleView_Ind, CCncConfCtrl::OnSetSelViewRsp );
    REG_PFUN( ev_CnCancelSingleView_Ind, CCncConfCtrl::OnSetSelViewRsp);  

    REG_PFUN( ev_TppSelDualView_Ind, CCncConfCtrl::OnScrnDisplayDualRsp );
    REG_PFUN( ev_TppCancelSelDualView_Ind, CCncConfCtrl::OnStopScrnDisplayDualRsp );


    REG_PFUN( ev_CnViewLocal_Ind, CCncConfCtrl::OnScrnDisplayLocalRsp );
    REG_PFUN( ev_CnCancelViewLocal_Ind, CCncConfCtrl::OnStopDisplayLocalRsp );

	REG_PFUN( ev_tpCnRoomDualOffline_Nty, CCncConfCtrl::OnCnDualOfflineNty );	
    REG_PFUN( ev_TppDualRcvInterrupt_Nty, CCncConfCtrl::OnDualRcvInterruptNty );
	
    REG_PFUN( ev_tppCodecEncryptKey_Nty, OnDualCodeEnCryptKeyNty );

	REG_PFUN( ev_CnViewLocalPIP_Ind, CCncConfCtrl::OnViewLocalPIPInd );
	REG_PFUN( ev_CnViewLocalPIP_Nty, CCncConfCtrl::OnViewLocalPIPNty );
	
    REG_PFUN( ev_CnSelTVSView_Ind, CCncConfCtrl::OnSetSelTVSViewRsp );
    REG_PFUN( ev_CnCancelSelTVSView_Ind, CCncConfCtrl::OnSetSelTVSViewRsp);  

    REG_PFUN( OSP_DISCONNECT, CCncConfCtrl::OnLinkBreak ); 
}


void CCncConfCtrl::ClearCnsScreenInfo()
{
    m_vctScreenInfo.clear();   
}


void CCncConfCtrl::OnTimeOut(u16 wEvent)
{
    //PostEvent(MTC_UI_CMD_TIMEOUT, wEvent);
}

 
const u16 CCncConfCtrl::MakeCall( TTPDialParam &tDialParam )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppMakeCall_Cmd );
    pcTpMsg->SetBody( &tDialParam, sizeof(TTPDialParam) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppMakeCall_Cmd, emEventTypeCnsSend, "callingType: %d, tCalledAddr.achAlias: %s, tCalledAddr.achE164: %s, calledType: %d(%d:emTpAlias, %d:emTpE164Num), \
bCreateConf: %d, ConfName: %s, TerNum:%d", 
		tDialParam.tCallingAddr.emType, tDialParam.tCalledAddr.achAlias, tDialParam.tCalledAddr.achE164, 
        tDialParam.tCalledAddr.emType, emTpAlias, emTpE164Num, tDialParam.bCreateConf, tDialParam.tConfInfo.achConfName, tDialParam.byTerNum );
    return wRet;
}

const u16 CCncConfCtrl::HungupPtpConf()
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppHangUp_Cmd ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppHangUp_Cmd, emEventTypeCnsSend, "hungup ptp conf" );
    return wRet;
}


const TTPCnsConfStatus& CCncConfCtrl::GetCnsConfStatus() const
{
	return m_tCnsConfStatus;
}


u16 CCncConfCtrl::SetInnerSpeaker( u8 byIndex )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnSetInnerSpeaker_Cmd );
	pcTpMsg->SetBody( &byIndex, sizeof(u8) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetInnerSpeaker_Cmd, emEventTypeCnsSend, "SpeakerIndex: %d", byIndex );
    return wRet;
}

u8 CCncConfCtrl::GetInnerSpeaker() const
{
	return m_bySpeakSeat;
}


BOOL CCncConfCtrl::IsLocalCnsMute() const
{
	return m_bMute;
}

BOOL CCncConfCtrl::IsLocalCnsQuite() const
{
	return m_bQuite;
}

u16 CCncConfCtrl::SetCnsMute( BOOL bMute /* = TRUE */ )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_tppMute_Cmd );
	pcTpMsg->SetBody( &bMute, sizeof(BOOL) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppMute_Cmd, emEventTypeCnsSend, "bMute: %d", bMute );
    return wRet;
}

u16 CCncConfCtrl::SetCnsQutie( BOOL bQutie /* = TRUE */ )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_tppQuiet_Cmd );
	pcTpMsg->SetBody( &bQutie, sizeof(BOOL) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppQuiet_Cmd, emEventTypeCnsSend, "bQutie: %d", bQutie );
    return wRet;
}

const u8& CCncConfCtrl::GetInputVol() const
{
	return m_byInputVol;
}

u16 CCncConfCtrl::AdjustInputVol( u8 byVolume )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_tppInputVolumeCmd );	
	pcTpMsg->SetBody( &byVolume, sizeof(u8) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppInputVolumeCmd, emEventTypeCnsSend, "Volume: %d", byVolume );
	return wRet;
}

const u8& CCncConfCtrl::GetOutputVol() const 
{
	return m_byOutputVol;
}

u16 CCncConfCtrl::AdjustOutputVol( u8 byVolume )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_tppOutputVolumeCmd );
	pcTpMsg->SetBody( &byVolume, sizeof(u8) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppOutputVolumeCmd, emEventTypeCnsSend, "Volume: %d", byVolume );
	return wRet;
}

    
u16 CCncConfCtrl::SetSelView( u8 byScreenID, u16 wEpID )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnSingleView_Cmd );
    pcTpMsg->SetBody( &byScreenID, sizeof(u8) );
    pcTpMsg->CatBody( &wEpID, sizeof(u16) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnSingleView_Cmd, emEventTypeCnsSend, "screenID: %d, EpID: %d", byScreenID, wEpID );
	return wRet;
}
 

u16 CCncConfCtrl::CancleSelView( u8 byScreenID )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnCancelSingleView_Cmd );
    pcTpMsg->SetBody( &byScreenID, sizeof(u8) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnCancelSingleView_Cmd, emEventTypeCnsSend, "screenID: %d ", byScreenID );
    return wRet;
}


BOOL CCncConfCtrl::IsLocalCnsPoll() const
{
	return m_bPoll;
}

u16 CCncConfCtrl::StartPoll( BOOL bStart )
{   
	u16 wEvent = ev_CnStartPoll_Cmd;
	if ( !bStart )
	{
		wEvent = ev_CnStopPoll_Cmd;
	}
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( wEvent ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( wEvent, emEventTypeCnsSend, "bStart: %d", bStart );
	return wRet;
}

BOOL CCncConfCtrl::IsLocalCnsDual() const
{
	return m_bDual;
}

 
u16 CCncConfCtrl::StartDualCodeStream( const TTPCnMediaTransPort &tVideoTransAddr, const TTPCnMediaTransPort &tAudioTransAddr ) const
{     
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
   
    pcTpMsg->SetEvent( ev_TppAddDualRcvAddr_Cmd ); 
    pcTpMsg->SetBody( &tVideoTransAddr, sizeof(TTPCnMediaTransPort) );  
    pcTpMsg->CatBody( &tAudioTransAddr, sizeof(TTPCnMediaTransPort) );
   
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    in_addr tAddr;
    tAddr.S_un.S_addr = tVideoTransAddr.m_tRtpPort.m_dwIP;
    in_addr tAudioAddr;
    tAudioAddr.S_un.S_addr = tAudioTransAddr.m_tRtpPort.m_dwIP;

    PrtMsg( ev_TppAddDualRcvAddr_Cmd, emEventTypeCnsSend, "VideoAddr: %s, Port: %d, AudioAddr: %s, Port: %d", inet_ntoa(tAddr), tVideoTransAddr.m_tRtpPort.m_wPort
        ,inet_ntoa(tAudioAddr), tAudioTransAddr.m_tRtpPort.m_wPort );

	return wRet;
}


u16 CCncConfCtrl::StopDualCodeStream() const 
{   
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_TppDelDualRcvAddr_Cmd );  
    pcTpMsg->SetBody( &m_nVideoNode, sizeof(u16) );
    
     
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppDelDualRcvAddr_Cmd, emEventTypeCnsSend,"" ); 
     

    pcTpMsg->SetBody( &m_nAudioNode, sizeof(u16)  );
    wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppDelDualRcvAddr_Cmd, emEventTypeCnsSend,"" );

   
	return wRet;
}

u16 CCncConfCtrl::ReqKeyFrame( BOOL32 bForce ) const 
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_TppPadDualKeyFrame_Req  );  
    pcTpMsg->SetBody( &m_nVideoNode, sizeof(u16) );
	pcTpMsg->CatBody( &bForce, sizeof(BOOL32) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppPadDualKeyFrame_Req , emEventTypeCnsSend ,"");
	return wRet;
}

u16 CCncConfCtrl::ScrnDisplayDual( const u16 wScrnID ) const 
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_TppSelDualView_Cmd  );  
    pcTpMsg->SetBody( &wScrnID, sizeof(u16) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppSelDualView_Cmd , emEventTypeCnsSend ,"");
	return wRet;
}


u16 CCncConfCtrl::ScrnStopDisplayDual( const u16 wScrnID ) const
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_TppCancelSelDualView_Cmd  );  
    pcTpMsg->SetBody( &wScrnID, sizeof(u16) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppCancelSelDualView_Cmd  , emEventTypeCnsSend ,"");
	return wRet;
}

/** 
* 功能  屏幕回显
* @return    
* @remarks 
*/
u16 CCncConfCtrl::ScrnDisplayLocal( const u16 wScrnID ) const  
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_CnViewLocal_Cmd  );  
    pcTpMsg->SetBody( &wScrnID, sizeof(u16) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnViewLocal_Cmd  , emEventTypeCnsSend ,"");
    return wRet;
}

/** 
* 功能  取消屏幕回显
* @return    
* @remarks 
*/
u16 CCncConfCtrl::ScrnStopDisplayLocal( const u16 wScrnID ) const  
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent(  ev_CnCancelViewLocal_Cmd  );  
    pcTpMsg->SetBody( &wScrnID, sizeof(u16) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg(  ev_CnCancelViewLocal_Cmd  , emEventTypeCnsSend ,"");
    return wRet;
}



u16 CCncConfCtrl::StartDual( BOOL  bStart )
{
    u16 msgID = ev_TppStartDual_Cmd;
    if ( !bStart )
    {
        msgID = ev_TppStopDual_Cmd;
    }
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( msgID );
    pcTpMsg->SetBody( &bStart, sizeof(BOOL) ); 
   
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( msgID, emEventTypeCnsSend, "bStart: %d", bStart );
	return wRet;
}

const vector<TScreenInfo>& CCncConfCtrl::GetCnsScreenInfo() const
{
	return m_vctScreenInfo;
}


void CCncConfCtrl::OnConfStateNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
				
    TTPCnsConfStatus tConfStatus = *reinterpret_cast<TTPCnsConfStatus*>(cTpMsg.GetBody());

	PrtMsg( ev_CnConfState_Nty, emEventTypeCnsRecv, "TTPCnsConfStatus: ConfName: %s, ConfID: %d, State: %d \
 (%d:em_CALL_IDLE, %d:em_CALL_CALLING, %d:em_CALL_CONNECTED),\
 ConfType: %d (%d:emCallType_P2P, %d:emCallType_Conf),  bMixMotive:%d  ", 
		tConfStatus.achConfName, tConfStatus.wConfID, tConfStatus.emState, 
        em_CALL_IDLE, em_CALL_CALLING, em_CALL_CONNECTED, tConfStatus.m_emCallType, emCallType_P2P, emCallType_Conf, tConfStatus.m_bMixMotive );

	m_tCnsConfStatus = tConfStatus;
	BOOL bInConf = FALSE;
	if ( m_tCnsConfStatus.emState == em_CALL_CONNECTED )
	{
		bInConf = TRUE;
	}
	
    //em_CALL_CALLING状态界面不需要刷新
    if ( m_tCnsConfStatus.emState != em_CALL_CALLING )
    {
	    PostEvent( UI_CNS_CONFSTATE_NOTIFY, bInConf, (LPARAM)&m_tCnsConfStatus );
    }
}

void CCncConfCtrl::OnQuietInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);

    u8 uInst = cTpMsg.GetHomeplace();

	BOOL bQuiet = *(BOOL*)(cTpMsg.GetBody());
	PrtMsg( ev_tppQuietInd, emEventTypeCnsRecv, "bQuite: %d, Inst: %d", bQuiet, uInst );

	if ( m_bQuite != bQuiet )
	{
		m_bQuite = bQuiet;
		PostEvent( UI_CNS_QUITE_MUTE, TRUE, m_bQuite );
	}			
}

void CCncConfCtrl::OnMuteInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
    u8 uInst = cTpMsg.GetHomeplace();

	BOOL bMute = *(BOOL*)(cTpMsg.GetBody());
	PrtMsg( ev_tppMuteInd, emEventTypeCnsRecv, "bMute: %d, Inst: %d", bMute, uInst );

	if ( m_bMute != bMute )
	{
		m_bMute = bMute;
		PostEvent( UI_CNS_QUITE_MUTE, FALSE, m_bMute );
	}			
}

void CCncConfCtrl::OnInputVolInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	u8 uInst = cTpMsg.GetHomeplace();
	if ( m_pSession->GetInst() == uInst )
	{
		m_byInputVol = *(u8*)(cTpMsg.GetBody());
		
		PostEvent( UI_CNS_INVOL_UPDATE , m_byInputVol, 0 );
	}
	
	PrtMsg( ev_tppInputVolumeInd, emEventTypeCnsRecv, "InputVol: %d, Inst: %d", m_byInputVol, uInst );
}

void CCncConfCtrl::OnOutPutVolInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	u8 uInst = cTpMsg.GetHomeplace();
	if ( m_pSession->GetInst() == uInst )
	{
		m_byOutputVol = *(u8*)(cTpMsg.GetBody());

		PostEvent( UI_CNS_OUTVOL_UPDATE );
	}

	PrtMsg( ev_tppOutputVolumeInd, emEventTypeCnsRecv, "OutputVol: %d, Inst: %d", m_byOutputVol, uInst );
}

void CCncConfCtrl::OnSetInnerSpeaker(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	
	u8 uInst = cTpMsg.GetHomeplace();
	if ( m_pSession->GetInst() == uInst )
	{
		m_bySpeakSeat = *(u8*)(cTpMsg.GetBody());
		PostEvent( UI_CNS_SPOKES_SEAT_NOTIFY, m_bySpeakSeat );

		PrtMsg( ev_CnSetInnerSpeaker_Ind, emEventTypeCnsRecv, "SpeakSeat: %d, Inst: %d", m_bySpeakSeat, uInst );
	}
	
	
}

void CCncConfCtrl::OnScreenDisplayInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	u8 byScreen = *(u8*)(cTpMsg.GetBody());	
	if ( byScreen >= 3 )
	{
		return;
	}	
	s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	strncpy( achCnsName, (s8*)(cTpMsg.GetBody()+sizeof(u8)), TP_MAX_ALIAS_LEN );

	u8 uInst = cTpMsg.GetHomeplace();

	if ( m_pSession->GetInst() == uInst )
	{
		UpdateScreenInfo( byScreen, achCnsName );
		PostEvent( UI_CNS_SCREEN_NAME_NOTIFY, byScreen, (LPARAM)achCnsName );

		PrtMsg( ev_CnYouAreSeeing_Ind, emEventTypeCnsRecv, "Screen: %d, CnsName: %s, Inst: %d", byScreen, achCnsName, uInst );
	}	
}

void CCncConfCtrl::OnScreenStateNotify( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
	u8 byScreenID = *(u8*)(cTpMsg.GetBody());	

    EMPosPic emPic = *(EMPosPic*)( cTpMsg.GetBody() + sizeof(u8));
    
    s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	strncpy( achCnsName, (s8*)(cTpMsg.GetBody()+sizeof(u8)) + sizeof(EMPosPic), TP_MAX_ALIAS_LEN );

  /* 
    EmTPPosStatus emState = *(EmTPPosStatus*)( cTpMsg.GetBody() + sizeof(u8) );	
	EMPosPic emPos = *(EMPosPic*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(EmTPPosStatus) );

    PrtMsg( ev_CnActivePos_Nty, emEventTypeCnsRecv, "Screen: %d, emState: %d, emPosPic: %d ", byScreen, emState, emPos );
    ev_CnPosAllStatus_Nty*/

    PrtMsg( ev_CnPosAllStatus_Nty, emEventTypeCnsRecv, "Screen: %d, emPosPic: %d , scrnName: %s", byScreenID,emPic ,achCnsName);
	UpdateScreenInfo( byScreenID, achCnsName, emPic );
	PostEvent( UI_CNS_SCREEN_STATE_NOTIFY, byScreenID, emPic ); 
}

// TScreenInfo *CCncConfCtrl::GetScreenInfoByID( const u8 byeScreenID ) 
// {
//     vector<TScreenInfo>::iterator it = m_vctScreenInfo.begin();
//     while ( it != m_vctScreenInfo.end() )
//     {
//         if ( it->byScreenID == byeScreenID )
//         {
//             return (TScreenInfo*)(&it);
//         }
// 		it++;
//     }
//     return NULL;
// }

void CCncConfCtrl::UpdateScreenInfo( u8 byScreen, s8* achCnsName )
{
	TScreenInfo tInfo;
	for ( u8 i = 0; i < m_vctScreenInfo.size(); i++ )
	{
		tInfo = m_vctScreenInfo.at(i);
		if ( tInfo.byScreenID == byScreen )
		{
			strncpy( m_vctScreenInfo[i].achCnsName, achCnsName, TP_MAX_ALIAS_LEN_CNC+1 );
			return;
		}
	}
	tInfo.byScreenID = byScreen;
	strncpy( tInfo.achCnsName, achCnsName, TP_MAX_ALIAS_LEN_CNC+1 );
	m_vctScreenInfo.push_back( tInfo );
}


void CCncConfCtrl::UpdateScreenInfo( u8 byScreen, s8* achCnsName,EMPosPic emPic )
{
    TScreenInfo tInfo;
    for ( u8 i = 0; i < m_vctScreenInfo.size(); i++ )
    {
        tInfo = m_vctScreenInfo.at(i);
        if ( tInfo.byScreenID == byScreen )
        {
            strncpy( m_vctScreenInfo[i].achCnsName, achCnsName, TP_MAX_ALIAS_LEN_CNC );
            m_vctScreenInfo[i].emPosPic = emPic; 

            return;
        }
    }
    tInfo.byScreenID = byScreen;
    strncpy( tInfo.achCnsName, achCnsName, TP_MAX_ALIAS_LEN_CNC );
    tInfo.emPosPic = emPic;
    m_vctScreenInfo.push_back( tInfo );
}

void CCncConfCtrl::UpdateScreenInfo( u8 byScreen, EmTPPosStatus emStatus, EMPosPic emPos )
{
	TScreenInfo tInfo;
	for ( u8 i = 0; i < m_vctScreenInfo.size(); i++ )
	{
		tInfo = m_vctScreenInfo.at(i);
		if ( tInfo.byScreenID == byScreen )
		{
			m_vctScreenInfo[i].emScreenState = emStatus;
			m_vctScreenInfo[i].emPosPic = emPos;
			return;
		}
	}
	tInfo.byScreenID = byScreen;
	tInfo.emScreenState = emStatus;
	tInfo.emPosPic = emPos;
	m_vctScreenInfo.push_back( tInfo );
}


void CCncConfCtrl::OnSetSelViewRsp( const CMessage &cMsg )
{ 

    CTpMsg cTpMsg(&cMsg);  
    u8 byScreenID = *(u8*)(cTpMsg.GetBody());	
    EmTPViewResult emRe = *(EmTPViewResult*)( cTpMsg.GetBody() + sizeof(u8) );
    u16 wEvent = cTpMsg.GetEvent();

    PrtMsg( wEvent, emEventTypeCnsRecv, "Screen: %d, errorCode: %d", byScreenID, emRe );
      
    //如果当前屏未处于激活状态，则不相应该消息  2011-12-27 by yjj
//     TScreenInfo *tScreen = GetScreenInfoByID( byScreenID );
//     if ( tScreen == NULL /*|| tScreen->emScreenState != emPosAcitve*/ )//emPosAcitve 状态不用了，用EMPosPic消息统一管理  dyy 2013-10-10 
//     {
//        return;
//     }

    if ( wEvent ==  ev_CnCancelSingleView_Ind )
    {
	    if ( emRe == emViewSucceed  )
	    {
		    UpdateScreenInfo( byScreenID, emPosAcitve, emPic_Invalid );
	    }
        PostEvent( UI_CNS_CANCLE_SEL_VIEW_RSP, byScreenID, emRe ); 
    }
    else
    {
	    if ( emRe == emViewSucceed )
	    {
		    UpdateScreenInfo( byScreenID, emPosAcitve, emPic_SelView );
	    }
        PostEvent( UI_CNS_SEL_VIEW_RSP, byScreenID, emRe ); 
    }
    
}

void CCncConfCtrl::OnStartPollRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    
    u16 wEvent = cTpMsg.GetEvent();

	EmTPPollResult emRe = *(EmTPPollResult*)( cTpMsg.GetBody() ); 

    PrtMsg( wEvent, emEventTypeCnsRecv, " emResult: %d ", emRe );
    
	BOOL bPoll = FALSE;
    if ( wEvent == ev_CnStartPoll_Ind )
    {       
        bPoll = TRUE;          
    }
    else if( wEvent == ev_CnStopPoll_Ind )
    {     
		bPoll = FALSE;
    } 
	PostEvent( UI_CNS_START_POLL_RSP, (WPARAM)bPoll, emRe ); 
}

void CCncConfCtrl::OnPollStatusNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);  

    u8 uInst = cTpMsg.GetHomeplace();

	BOOL bPoll = *(BOOL*)(cTpMsg.GetBody());
	PrtMsg( ev_CnPollStatus_Nty, emEventTypeCnsRecv, " bPoll: %d, Inst: %d ", bPoll, uInst );

	if ( m_bPoll != bPoll )
	{
		m_bPoll = bPoll;
		PostEvent( UI_CNS_POLL_STATE_NOTIFY, m_bPoll, 0 ); 
	}		
}

/*
enum EmCnsCallReason	
{
	EmCnsCallReason_success,
	EmCnsCallReason_hungup,			//本地挂断
	EmCnsCallReason_Unreachable,	//对端不在线，无法呼叫
	EmCnsCallReason_resourcefull,	//对端无可用资源
	EmCnsCallReason_dstnotfind,		//目标不存在
	EmCnsCallReason_Busy,			//对端忙
	EmCnsCallReason_Local,			//本地原因
	EmCnsCallReason_NoConf,			//会议不存在
	EmCnsCallReason_Exist,			//对端已在本会议中
	EmCnsCallReason_Rejected,		//对端拒绝
	EmCnsCallReason_peerhungup,		//对端挂断
//	EmCnsCallReason_AlreadyDual,    //对端在双流
	EmCnsCallReason_Abnormal,       //本地掉线挂断
	EmCnsCallReason_PeerAbnormal,   //对端掉线挂断
	EmCnsCallReason_ConfOver,	//会议结束
	EmCnsCallReason_cncallexception,	//接入模块(cncall)掉线
	EmCnsCallReason_ConfExist,		//会议已存在
	EmCnsCallReason_unknown,  
	
	  
}; 
*/
void CCncConfCtrl::OnHungupNotify( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    
    u8 uInst = cTpMsg.GetHomeplace();
    
    EmCnsCallReason emRe = *(EmCnsCallReason*)(cTpMsg.GetBody()); 

    PrtMsg( ev_TppHangUp_Ind, emEventTypeCnsRecv, "Inst: %d, emReason:%d ",uInst, emRe );

	if ( emRe != EmCnsCallReason_success )
	{
		PrtMsg( " ( %d:EmCnsCallReason_success, %d:EmCnsCallReason_hungup, %d:EmCnsCallReason_Unreachable, %d:EmCnsCallReason_resourcefull \
%d:EmCnsCallReason_dstnotfind, %d:EmCnsCallReason_Busy, %d:EmCnsCallReason_Local, %d:EmCnsCallReason_NoConf, \
%d:EmCnsCallReason_Exist, %d:EmCnsCallReason_Rejected, %d:EmCnsCallReason_peerhungup, %d:EmCnsCallReason_Abnormal, \
%d:EmCnsCallReason_PeerAbnormal, %d:EmCnsCallReason_ConfOver ,  %d:EmCnsCallReason_cncallexception , \
%d:EmCnsCallReason_ConfExist ,%d:EmCnsCallReason_unknown ) ",  
             EmCnsCallReason_success,EmCnsCallReason_hungup,EmCnsCallReason_Unreachable, EmCnsCallReason_resourcefull,
			 EmCnsCallReason_dstnotfind, EmCnsCallReason_Busy, EmCnsCallReason_Local,EmCnsCallReason_NoConf,EmCnsCallReason_Exist,
			 EmCnsCallReason_Rejected,EmCnsCallReason_peerhungup,EmCnsCallReason_Abnormal,EmCnsCallReason_PeerAbnormal,
			 EmCnsCallReason_ConfOver,EmCnsCallReason_cncallexception,EmCnsCallReason_ConfExist,EmCnsCallReason_unknown );
	}
    
    PostEvent( UI_CNS_HUNGUP_P2P_NOTIFY, emRe, 0 ); 
}

void CCncConfCtrl::OnStartDualCdStrmRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg);    

    EmTPAddDualRcvResult emReVideo = *(EmTPAddDualRcvResult*)(cTpMsg.GetBody()); 
   
    if ( emReVideo == emAddDualRcvSucceed )
    {
        m_tVideoTranAddr = *(TTPCnMediaTransPort*)(cTpMsg.GetBody() + sizeof( EmTPAddDualRcvResult )*2 );
        
        m_nVideoNode = *(u16*)(cTpMsg.GetBody() + 
                                    sizeof( EmTPAddDualRcvResult ) * 2 +
                                    sizeof(TTPCnMediaTransPort ) * 2  );

        
    }
    

    EmTPAddDualRcvResult emReAudio = *(EmTPAddDualRcvResult*)(cTpMsg.GetBody() + sizeof( EmTPAddDualRcvResult ) ); 
    if ( emReAudio == emAddDualRcvSucceed )
    {
        m_tAudioTranAddr = *(TTPCnMediaTransPort*)(cTpMsg.GetBody() + sizeof( EmTPAddDualRcvResult )*2 + 
                                 sizeof(TTPCnMediaTransPort ) );
        
        m_nAudioNode = *(u16*)(cTpMsg.GetBody() +  sizeof( EmTPAddDualRcvResult )*2 + 
                                  sizeof(TTPCnMediaTransPort )*2 + sizeof(u16 ) );
    }
         
    u8 uInst = cTpMsg.GetHomeplace();
    
    PrtMsg( ev_TppAddDualRcvAddr_Ind, emEventTypeCnsRecv, "Inst: %d, emVideoReason:%d , emAudioReaso=%d  \
( %d:emAddDualRcvSucceed,%d:emAddDualRcvFailNoDual,%d:emAddDualRcvFailIllegalPos，%d:emAddDualRcvFailNoPos, \
%d:emAddDualRcvFailUnKown)",uInst, emReVideo,emReAudio, emAddDualRcvSucceed,emAddDualRcvFailNoDual,
emAddDualRcvFailIllegalPos,emAddDualRcvFailNoPos,emAddDualRcvFailUnKown );
     
    
    
    PostEvent( UI_CNSINS_START_DUALCODESTREAM_RSP,  emReVideo , emReAudio ); 
}
 

 
void CCncConfCtrl::OnStopDualCdStrmRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 

    m_nVideoNode = TP_INVALID_INDEX;
    m_nAudioNode = TP_INVALID_INDEX;

	EmTPDeleteDualRcvResult emReVideo = *(EmTPDeleteDualRcvResult*)(cTpMsg.GetBody());

	PrtMsg( ev_TppDelDualRcvAddr_Ind, emEventTypeCnsRecv, "" );
}

void CCncConfCtrl::OnScrnDisplayDualRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg);    

	u16 wScrnID =  *(u16*)( cTpMsg.GetBody() );
    EmTPAddDualRcvResult emRe = *(EmTPAddDualRcvResult*)( cTpMsg.GetBody() + sizeof(u16) );
    
    PrtMsg( ev_TppSelDualView_Ind, emEventTypeCnsRecv, "scrnID: %d, result: %d", wScrnID,emRe );

    PostEvent( UI_CNS_SCRN_DISPLAY_DUAL_RSP, wScrnID, emRe );  
}

void CCncConfCtrl::OnStopScrnDisplayDualRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    
	u16  wScrnID =  *(u16*)( cTpMsg.GetBody() );
    EmTPDeleteDualRcvResult emRe = *(EmTPDeleteDualRcvResult*)( cTpMsg.GetBody() + sizeof(u16) );
    
    
    PrtMsg( ev_TppCancelSelDualView_Ind, emEventTypeCnsRecv, "scrnID:%d, result: %d", wScrnID,emRe);
    
    PostEvent( UI_CNS_STOP_SCRN_DISPLAY_DUAL_RSP, wScrnID, emRe );  
}


void CCncConfCtrl::OnScrnDisplayLocalRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    
	u16 wScrnID = *(u16*)( cTpMsg.GetBody() );
    EmTPViewLocalResult emRe = *(EmTPViewLocalResult*)( cTpMsg.GetBody() + sizeof(u16) );    
    
    PrtMsg( ev_CnViewLocal_Ind, emEventTypeCnsRecv, "scrnID:%d, result: %d", wScrnID, emRe );
    
    PostEvent( UI_CNS_SCRN_DISPLAY_LOCAL_RSP, wScrnID, emRe );  
}


void CCncConfCtrl::OnStopDisplayLocalRsp( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 
    
	u16  wScrnID = *(u16*)( cTpMsg.GetBody() );
    EmTPViewLocalResult emRe = *(EmTPViewLocalResult*)( cTpMsg.GetBody() + sizeof(u16) );
       
    PrtMsg( ev_CnCancelViewLocal_Ind, emEventTypeCnsRecv, "scrnID:%d, result: %d", wScrnID, emRe );
    
    PostEvent( UI_CNS_STOP_SCRN_DISPLAY_LOCAL_RSP, wScrnID, emRe );  
}


void CCncConfCtrl::OnStartDualRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    EmTPDualReason emSuc = *(EmTPDualReason*)(cTpMsg.GetBody()); 
    u16 wEvent = cTpMsg.GetEvent();

	BOOL bStart = FALSE;
    if ( wEvent == ev_TppStartDual_Ind )
    {
		bStart = TRUE;       	
    }
    else
    {
		bStart = FALSE;    
    } 

	PrtMsg( wEvent, emEventTypeCnsRecv, "result: %d ( emTpDualAccept:%d, \
emTpDualBusy:%d, emTpDualPreemptive:%d, emTpDualPeerReject:%d, emTpDualPeerStop:%d, emTpDualNoVideo:%d, emTpDualLocalStop:%d, emTpDualSndFail:%d )", 
			emSuc, emTpDualAccept, emTpDualBusy, emTpDualPreemptive, emTpDualPeerReject, emTpDualPeerStop, emTpDualNoVideo, emTpDualLocalStop, emTpDualSndFail );

	PostEvent( UI_CNS_START_DUAL_RSP, bStart, (LPARAM)emSuc );  
}

void CCncConfCtrl::OnDualStatusNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 
    
    u8 uInst = cTpMsg.GetHomeplace();
     
	BOOL bDual = *(BOOL*)(cTpMsg.GetBody());
	PrtMsg( ev_TppIsDual_Nty, emEventTypeCnsRecv, "bDual: %d, Inst: %d ", bDual, uInst );
	 
	if ( m_bDual != bDual )
	{
		m_bDual = bDual;
		PostEvent( UI_CNS_DUAL_STATE_NOTIFY, m_bDual, 0 ); 
	}		
}


void CCncConfCtrl::OnRecvDualNty( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    
    u8 uInst = cTpMsg.GetHomeplace();
    
    BOOL bDual = *(BOOL*)(cTpMsg.GetBody());
    PrtMsg( ev_TppIsRcvDual_Nty, emEventTypeCnsRecv, "bRcvDual: %d, Inst: %d ", bDual, uInst );
    
    if ( m_bRecvDual!= bDual )
    {
        m_bRecvDual = bDual;
        PostEvent( UI_CNS_RECV_DUAL_NOTIFY, m_bRecvDual, 0 ); 
    }		
}


void CCncConfCtrl::OnCnDualOfflineNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	PrtMsg( ev_tpCnRoomDualOffline_Nty, emEventTypeCnsRecv, "" );
	
	PostEvent( UI_CNS_DUALOFFLINE_NOTIFY, 0, 0 ); 
}

void CCncConfCtrl::OnDualRcvInterruptNty( const CMessage &cMsg )
{    
    CTpMsg cTpMsg(&cMsg); 

    EmTPChannelReason emReason = *(EmTPChannelReason*)(cTpMsg.GetBody()); 
    PrtMsg( ev_TppDualRcvInterrupt_Nty, emEventTypeCnsRecv, "reason:%d" ,emReason);
    
    PostEvent( UI_RECV_DUAL_INTERRUPT, emReason, 0 ); 
}
 
void CCncConfCtrl::OnDualCodeEnCryptKeyNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	TTpEncryptKey tTpEncryptKey = *(TTpEncryptKey*)(cTpMsg.GetBody());
	
	PrtMsg( ev_tppCodecEncryptKey_Nty, emEventTypeCnsRecv, "Key:%s, EmTPEncryptType:%d, Length:%d", tTpEncryptKey.byKey, tTpEncryptKey.emTPEncryptType, tTpEncryptKey.byLen );
	
	PostEvent( UI_CNS_DUAL_KEY_NOTIFY, (WPARAM)&tTpEncryptKey, 0  );
}

// 断链清空数据
void CCncConfCtrl::OnLinkBreak(const CMessage& cMsg)
{ 
	memset( &m_tCnsConfStatus, 0, sizeof(m_tCnsConfStatus) );
	m_bMute = FALSE;
	m_bQuite = FALSE;
	m_bDual = FALSE;
	m_bPoll = FALSE;
	m_byInputVol = 0;
	m_byOutputVol = 0;
	m_bySpeakSeat = 0;
	m_vctScreenInfo.clear();
	m_bLocalPIP = FALSE;

    m_bRecvDual = FALSE ;
    m_nVideoNode = TP_INVALID_INDEX ;
    m_nAudioNode = TP_INVALID_INDEX;
    PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv,"[CCncConfCtrl::OnLinkBreak]清空会议状态信息" );
    
}

//开启画中画
u16 CCncConfCtrl::ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnViewLocalPIP_Cmd );
	pcTpMsg->SetBody( &byScrnID, sizeof(u8) ); 
	pcTpMsg->CatBody( &bLocalP, sizeof(BOOL) ); 

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnViewLocalPIP_Cmd, emEventTypeCnsSend, "byScrnID: %d, bViewPIP:%d", byScrnID, bLocalP );
	return wRet;
}

void CCncConfCtrl::OnViewLocalPIPInd( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 
	
    u8 byScrnID = *(u8*)(cTpMsg.GetBody());			//B3版本中只有中间屏开启画中画,屏号为1
	EmTPViewLocalResult emViewRes = *(EmTPViewLocalResult*)( cTpMsg.GetBody() + sizeof(u8) );
    PrtMsg( ev_CnViewLocalPIP_Ind, emEventTypeCnsRecv, "byScrnID:%d, emViewRes:%d( emViewLocalSucceed:%d, \
emViewLocalFailUnKown:%d, emViewLocalFailStatusError:%d, emViewLocalFailOffline:%d, emViewLocalFailIllegalPos:%d )",
byScrnID, emViewRes, emViewLocalSucceed,emViewLocalFailUnKown,emViewLocalFailStatusError,emViewLocalFailOffline,emViewLocalFailIllegalPos );

	PostEvent( UI_CNS_VIEWLOCALPIP_IND, (WPARAM)byScrnID, emViewRes ); 
	
}

BOOL CCncConfCtrl::IsViewLocalPIP() const
{
	return m_bLocalPIP;
}

void CCncConfCtrl::OnViewLocalPIPNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 
	
    u8 byScrnID = *(u8*)(cTpMsg.GetBody());			//B3版本中只有中间屏开启画中画,屏号为1
	BOOL bLocalPIP = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
    PrtMsg( ev_CnViewLocalPIP_Nty, emEventTypeCnsRecv, "byScrnID:%d, bLocalPIP:%d", byScrnID, bLocalPIP );

	if ( m_bLocalPIP != bLocalPIP )
	{
		m_bLocalPIP = bLocalPIP;
		PostEvent( UI_CNS_VIEWLOCALPIP_NTY ); 
	}	
}

//选看电视墙
u16 CCncConfCtrl::SelTVSView( u8 byScreenID )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnSelTVSView_Cmd );
    pcTpMsg->SetBody( &byScreenID, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnSelTVSView_Cmd, emEventTypeCnsSend, "screenID: %d", byScreenID );
	return wRet;
}

u16 CCncConfCtrl::CancelSelTVSView( u8 byScreenID )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnCancelSelTVSView_Cmd );
    pcTpMsg->SetBody( &byScreenID, sizeof(u8) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnCancelSelTVSView_Cmd, emEventTypeCnsSend, "screenID: %d ", byScreenID );
    return wRet;	
}

void CCncConfCtrl::OnSetSelTVSViewRsp( const CMessage &cMsg )
{	
    CTpMsg cTpMsg(&cMsg);  
    u8 byScreenID = *(u8*)(cTpMsg.GetBody());	
    BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
    u16 wEvent = cTpMsg.GetEvent();
	
    PrtMsg( wEvent, emEventTypeCnsRecv, "Screen: %d, bSuccess: %d", byScreenID, bSuccess );
	
    //如果当前屏未处于激活状态，则不相应该消息  2011-12-27 by yjj
//     TScreenInfo *tScreen = GetScreenInfoByID( byScreenID );
//     if ( tScreen == NULL /*|| tScreen->emScreenState != emPosAcitve*/ )//emPosAcitve 状态不用了，用EMPosPic消息统一管理  dyy 2013-10-10 
//     {
// 		return;
//     }
	
    if ( wEvent ==  ev_CnCancelSelTVSView_Ind )
    {
		if ( bSuccess  )
		{
			UpdateScreenInfo( byScreenID, emPosAcitve, emPic_Invalid );
		}
        PostEvent( UI_CNS_CANCLE_SEL_TVSVIEW_RSP, byScreenID, bSuccess ); 
    }
    else
    {
		if ( bSuccess )
		{
			UpdateScreenInfo( byScreenID, emPosAcitve, emPic_SelTVS );
		}
        PostEvent( UI_CNS_SEL_TVSVIEW_RSP, byScreenID, bSuccess ); 
    }
}
