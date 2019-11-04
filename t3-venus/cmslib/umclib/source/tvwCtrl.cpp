// tvwCtrl.cpp: implementation of the CTvwCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tvwCtrl.h"
//#include "umshduevent.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTvwCtrl::CTvwCtrl( CUmsSession &cUmsSession )
         :CTvwCtrlIF(),
		 m_pUmsSession(NULL)
{
    m_pUmsSession = &cUmsSession; 
    BuildEventsMap();
}

 

void CTvwCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CTvwCtrl,cMsg);
}

void CTvwCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
    PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
}

void CTvwCtrl::BuildEventsMap()
{    
    //断链清空资源
    REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 

    //REG_PFUN(ev_SysHduEpReg, OnRefeshTvwNotify); 
    //REG_PFUN(ev_SysHduEpDrop, OnRefeshTvwNotify); 

    REG_PFUN(ev_HduPlay_Ack, OnOperateHduRsp); 
    REG_PFUN(ev_HduPlay_NAck, OnOperateHduRsp); 
    REG_PFUN(ev_HduStopPlay_Ack, OnOperateHduRsp); 
    REG_PFUN(ev_HduStopPlay_NAck, OnOperateHduRsp); 

    //REG_PFUN( ev_SysHduCallIsValid, OnCodeStreamNotify ); 

    REG_PFUN( ev_hduPlan_Nty, OnTvwPlanNotify );

    REG_PFUN( ev_HduReg_Status_Nty, OnTvwRegStatusNotify );
     
}


void  CTvwCtrl::OnLinkBreak(const CMessage& cMsg)
{
    //m_tplTvwLst.Clear();
    PrtMsg( OSP_DISCONNECT, emEventTypeUmsRecv, "清空电视墙列表" ); 
    PostEvent( UI_UMS_REFRESH_TVW_LIST_NOTITFY );
}


void  CTvwCtrl::OnOperateHduRsp(const CMessage& cMsg) 
{
    CTpMsg kdvMsg(&cMsg);
    u16 wEvent = kdvMsg.GetEvent();
    //TTPHduPlayReq hduInfo = *reinterpret_cast<TTPHduPlayReq*>( kdvMsg.GetBody() );
    //EmTpHduPlayNackReason emReason = *reinterpret_cast<EmTpHduPlayNackReason*>( kdvMsg.GetBody() + sizeof(TTPHduPlayReq) );

    u16 wIndex = *reinterpret_cast<u16*>( kdvMsg.GetBody() );

    switch( wEvent )
    {
    case ev_HduPlay_Ack:
    case ev_HduStopPlay_Ack:
    case ev_HduStopPlay_NAck:
        {
            PrtMsg( wEvent, emEventTypeUmsRecv, "wIndex:%d", wIndex );
        }        
        break;
    case ev_HduPlay_NAck:
        {
            EmTpHduPlayNackReason emReason = *reinterpret_cast<EmTpHduPlayNackReason*>( kdvMsg.GetBody() + sizeof(u16) );
            PrtMsg( wEvent, emEventTypeUmsRecv, "wIndex:%d, EmTpHduPlayNackReason:%d", wIndex, emReason );
            PostEvent( UI_UMS_PLAY_HDU_RSP, FALSE, emReason );
        }         
        break;
    default:
        break;
    }

}


/*
void CTvwCtrl::OnCodeStreamNotify(const CMessage& cMsg)
{
    CTpMsg kdvMsg(&cMsg);
    TTPHduPlayReq hduInfo = *reinterpret_cast<TTPHduPlayReq*>( kdvMsg.GetBody() );
    BOOL bHasCodeStream =  *reinterpret_cast<BOOL*>( kdvMsg.GetBody() + sizeof(TTPHduPlayReq) );
    PrtMsg( ev_SysHduCallIsValid,emEventTypeUmsRecv,"ChannelHandle=%d, Alias=%s, ScreenNum=%d, bHaveCodeStream=%d", 
		hduInfo.m_nChannelHandle, hduInfo.m_achAlias, hduInfo.m_wScreenNum, bHasCodeStream ) ; 
    s32 nIndex = GetTvwIndexByHandleID( hduInfo.m_nChannelHandle );
    if ( nIndex < 0 )
    {  
        return; 
    }

    m_tplTvwLst.GetAt( nIndex ).bCodeStream = bHasCodeStream;
    PostEvent( UI_UMS_HDU_CODE_STREAM_NOTIFY,hduInfo.m_nChannelHandle,bHasCodeStream  );
}
*/




u16 CTvwCtrl::PlayHduReq( const TTPHduPlayReq & tTvwInfo ) 
{
    if ( NULL == m_pUmsSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
    pMsg->SetEvent( ev_HduPlay_Req );
    pMsg->SetBody(&tTvwInfo,sizeof(tTvwInfo));
    
    u16 awEvent[2];
    awEvent[0] = ev_HduPlay_Ack;  
    awEvent[1] = ev_HduPlay_NAck;   
    u16 wRe = m_pUmsSession->PostCommand(this,awEvent,2 ,TYPE_TPMSG);
    
//    PrtMsg( ev_HduPlay_Req, emEventTypeUmsSend, "Index:%d, Alias:%s, ScreenNum:%d",tTvwInfo.m_wIndex, tTvwInfo.m_achAlias, tTvwInfo.m_wScreenNum );
    
	return wRe;
}


u16 CTvwCtrl::StopHduReq( const TTPHduPlayReq& tTvwInfo ) 
{  
    if ( NULL == m_pUmsSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
    pMsg->SetEvent( ev_HduStopPlay_Req );
    pMsg->SetBody(&tTvwInfo,sizeof(tTvwInfo));
    
    u16 awEvent[2];
    awEvent[0] = ev_HduStopPlay_Ack;  
    awEvent[1] = ev_HduStopPlay_NAck;   
    u16 wRe = m_pUmsSession->PostCommand( this, awEvent, 2,TYPE_TPMSG );
    
//    PrtMsg( ev_HduStopPlay_Req, emEventTypeUmsSend, "Index:%d, Alias:%s, ScreenNum:%d", tTvwInfo.m_wIndex, tTvwInfo.m_achAlias, tTvwInfo.m_wScreenNum );
    return wRe;
}

u16 CTvwCtrl::StopAllHduReq()
{
    if ( NULL == m_pUmsSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
    pMsg->SetEvent( ev_HduAllStopPlay_Req );
    
    u16 wRe = m_pUmsSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_HduAllStopPlay_Req, emEventTypeUmsSend, "" );
    return wRe;
}



const THduPlanData& CTvwCtrl::GetTvwPlanData() const
{
    return m_tHduPlanData;
}


void CTvwCtrl::OnTvwPlanNotify(const CMessage& cMsg)
{
    CTpMsg kdvMsg( &cMsg );
    THduPlanData tHduPlanData = *reinterpret_cast<THduPlanData*>( kdvMsg.GetBody() );
    
    m_tHduPlanData = tHduPlanData;
    
    PrtMsg( ev_hduPlan_Nty, emEventTypeUmsRecv, "THduPlanData: row:%d, col:%d", tHduPlanData.m_byRow, tHduPlanData.m_byCol );
    
    PostEvent( UI_UMS_HDUPLAN_NOTIFY, (WPARAM)&tHduPlanData );
    return;
}

void CTvwCtrl::OnTvwRegStatusNotify(const CMessage& cMsg)
{
    CTpMsg kdvMsg( &cMsg );
    u16 wIndex = *reinterpret_cast<u16*>( kdvMsg.GetBody() );
    BOOL32 bReg = *reinterpret_cast<u16*>( kdvMsg.GetBody() + sizeof(u16) );

    if ( wIndex < HDU_STYLE_MAX_NUM )
    {
        m_tHduPlanData.m_atUnits[wIndex].m_bReged = bReg;
    }
    
    PrtMsg( ev_HduReg_Status_Nty, emEventTypeUmsRecv, "wIndex:%d, bReg:%d", wIndex, bReg );
    
    PostEvent( UI_UMS_HDUPLAN_NOTIFY, (WPARAM)&m_tHduPlanData );
    return;
}