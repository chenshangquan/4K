// confCtrl.cpp: implementation of the CConfCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "confCtrl.h"
#include "cmsConst.h"
#include "eventoutumscall.h"
#include "eventoutumsconftemplate.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 
CConfCtrl::CConfCtrl(CUmsSession &cUmsSession)
          :CConfCtrlIF(),
		  m_pUmsSession(NULL),
		  m_tplConfList()
{
   m_pUmsSession = &cUmsSession;
   BuildEventsMap();
}


CConfCtrl::~CConfCtrl()
{
	m_tplConfList.clear();
}

 
void  CConfCtrl::BuildEventsMap()
{
	REG_PFUN(evtp_StartConfTemplate_Ret,OnStartConfTemplateRsp);
	REG_PFUN(evtp_HungUpConf_result, OnHungUpConfRsp ); 
	REG_PFUN(evtp_HungUp_Conf_Reason, OnHungUpConfNotify ); 
	REG_PFUN(evtp_CallEP_result, OnInviteCnsRsp );

	REG_PFUN(evtp_AddConfList_Notify, OnAddConfListNotify );
	REG_PFUN(evtp_DelConflist_Notify, OnDelConfListNotify );

	REG_PFUN(evtp_UpdateConfCnsList_Notify, OnUpdateConfCnsListNotify ); 
	REG_PFUN(evtp_AuxMixInfo_Notify, OnUpdateConfAuxMixlistNotify ); 
	REG_PFUN(evtp_UpdateConfTurnlist_Notify, OnUpdateConfPolllistNotify ); 
    REG_PFUN(evtp_SpeakerChange_Notify, OnUpdateConfSpeakerNotify ); 
    
	REG_PFUN(evtp_ApplySpeaker_result, OnSetSpokeCnsRsp ); 
    REG_PFUN(evtp_MuteEp_Ind, OnSetMuteCnsRsp ); 
    REG_PFUN(evtp_QuietEp_Ind, OnSetSilenceCnsRsp ); 
    REG_PFUN(evtp_StartDual_Ind, OnSetDualCnsRsp );  
    REG_PFUN(evtp_DualEp_Notify, OnDualCnsNotify );  

   //级联会议通知
    REG_PFUN(evtp_ChairConfInfo_Notify, OnCasadeNotify );  

   //断链清空资源
    REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
		
}







void CConfCtrl::OnLinkBreak( const CMessage& cMsg )
{
   ClearConfLst( m_tplConfList );
   PrtMsg( OSP_DISCONNECT,emEventTypeUmsRecv,"清空会议列表"); 
   PostEvent( UI_UMS_REFRESH_CONF_LIST, emLinkBreak );
}


void  CConfCtrl::ClearConfLst( vector<TCMSConf> &vcConfLst )
{
 
    vector<TCMSConf>::iterator it = vcConfLst.begin();
    while ( it != vcConfLst.end() )
    { 
        it->m_tplCnsList.Clear(); 
        it->m_tplPollList.Clear();
       
        vcConfLst.erase( it );
        it  = vcConfLst.begin();
    }

    vcConfLst.clear(); 
}

u16 CConfCtrl::GetConfList( ARRAY<TCMSConf> &tplConfList )  const
{   
    
    TTPConfInfo conf;
    
    for ( int i = 0; i< m_tplConfList.size(); i++ )
    {   
		conf = m_tplConfList.at(i); 
		TCMSConf cmsConf(conf);
		tplConfList.push_back(  cmsConf );
		tplConfList.at(i).m_emConfType = m_tplConfList.at(i).m_emConfType;
		tplConfList.at(i).m_tplCnsList = m_tplConfList.at(i).m_tplCnsList;
		tplConfList.at(i).m_tplPollList = m_tplConfList.at(i).m_tplPollList;
		tplConfList.at(i).m_tAudmixList = m_tplConfList.at(i).m_tAudmixList;
		tplConfList.at(i).m_bStartAudmix = m_tplConfList.at(i).m_bStartAudmix;		
		tplConfList.at(i).m_tCascadeConfInfo = m_tplConfList.at(i).m_tCascadeConfInfo;
    }
     
	return NO_ERROR;
} 


u16 CConfCtrl::GetConfCnsList( u16 wConfID, TplArray<TCnsInfo> &tplConfCnsList )  const
{
	s32 nIndex = GetConfIndexByID( wConfID  );
    if ( nIndex < 0 )
	{
		return ERR_CMS_NOT_FIND;
    }

   tplConfCnsList = m_tplConfList.at( nIndex ).m_tplCnsList;
   return NO_ERROR;	
}


u16 CConfCtrl::GetConfAudmixList(  u16 wConfID, TAuxMixList&tConfAudmixList )  const
{
	s32 nIndex = GetConfIndexByID( wConfID  );
    if ( nIndex < 0 )
	{
		return ERR_CMS_NOT_FIND;
    }
	
	tConfAudmixList = m_tplConfList.at( nIndex ).m_tAudmixList;
   return NO_ERROR;	
}


u16 CConfCtrl::GetConfPollList(  u16 wConfID, TplArray<u16> &tplConfPollList )  const
{
	s32 nIndex = GetConfIndexByID( wConfID  );
    if ( nIndex < 0 )
	{
		return ERR_CMS_NOT_FIND;
    }
	
	tplConfPollList = m_tplConfList.at( nIndex ).m_tplPollList;
    return NO_ERROR;	
}

u16 CConfCtrl::StartTemplateConfReq( const u16 wConfTemplateID ) 
{   
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}

	CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_StartConfTemplate_Req );
	pMsg->SetBody(&wConfTemplateID,sizeof(u16));

	u16 awEvent[1];
    awEvent[0] = evtp_StartConfTemplate_Ret;   
 	u16 wRe = m_pUmsSession->PostCommand(this,awEvent,1 ,TYPE_TPMSG);

	PrtMsg(evtp_StartConfTemplate_Req,emEventTypeUmsSend,"conftemplateID=%d",wConfTemplateID);
    
	return wRe;
}


u16 CConfCtrl::InviteCnsReq( const TConfCallEpAddr &tEp )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_CallEP_cmd );
	pMsg->SetBody(&tEp,sizeof(TConfCallEpAddr));
	
	u16 awEvent[1];
    awEvent[0] = evtp_CallEP_result;   
	u16 wRe = m_pUmsSession->PostCommand( this,awEvent,1,TYPE_TPMSG );
	
	PrtMsg(evtp_CallEP_cmd,emEventTypeUmsSend,"confID=%d, EPAlias=%s",tEp.m_wConfID,tEp.m_tCallAddr.m_tAlias.m_abyAlias);

	 return wRe;
}


u16 CConfCtrl::CallConfCnsReq( const TConfEpID &tEp )
{
    if ( NULL == m_pUmsSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
    pMsg->SetEvent( evtp_CallExistEP_cmd );
    pMsg->SetBody(&tEp,sizeof(TConfEpID));
    
    u16 awEvent[1];
    awEvent[0] = evtp_CallEP_result;   
    u16 wRe = m_pUmsSession->PostCommand( this,awEvent,1,TYPE_TPMSG );
    
    PrtMsg(evtp_CallExistEP_cmd,emEventTypeUmsSend,"confID=%d, CnsID=%d",tEp.m_wConfID,tEp.m_wEpID);
    
	 return wRe;
}


u16 CConfCtrl::HangupConfReq( const u16 wConfID )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_HungUpConf_cmd );
	pMsg->SetBody(&wConfID,sizeof(u16));
	
	u16 awEvent[1];
    awEvent[0] = evtp_HungUpConf_result;   
	u16 wRe = m_pUmsSession->PostCommand( this,awEvent,1,TYPE_TPMSG );
	
	PrtMsg( evtp_HungUpConf_cmd, emEventTypeUmsSend, "confID=%d", wConfID );
	
	return wRe;
}


u16 CConfCtrl::HangupCNSReq( const TConfEpID &tConfEpInfo )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_DropEp_cmd );
	pMsg->SetBody(&tConfEpInfo,sizeof(tConfEpInfo));
 
	u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	
	PrtMsg( evtp_DropEp_cmd, emEventTypeUmsSend, "confID=%d, CNSID=%d", tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID );
	
	return wRe;
}


u16 CConfCtrl::RemoveCNSReq( const TConfEpID &tConfEpInfo )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_DeleteEp_cmd );
	pMsg->SetBody(&tConfEpInfo,sizeof(tConfEpInfo));
	
	u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	
	PrtMsg( evtp_DeleteEp_cmd, emEventTypeUmsSend, "confID=%d, CNSID=%d", tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID );
	
	return wRe;
}


u16 CConfCtrl::SetSpokeCnsReq( const TConfEpID &tConfEpInfo )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_ApplySpeaker_cmd );
	pMsg->SetBody(&tConfEpInfo,sizeof(tConfEpInfo));

	u16 awEvent[1];
    awEvent[0] = evtp_ApplySpeaker_result;   

	u16 wRe = m_pUmsSession->PostCommand( this,awEvent,1,TYPE_TPMSG );
 
	
	PrtMsg( evtp_ApplySpeaker_cmd, emEventTypeUmsSend, "confID=%d, CNSID=%d", tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID );
	
    return wRe;
    
}



u16 CConfCtrl::SetQuietCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bQuiet)
{
    if ( NULL == m_pUmsSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
    pMsg->SetEvent( evtp_QuietEp_cmd );
    pMsg->SetBody( &tConfEpInfo,sizeof(TConfEpID) );
    pMsg->CatBody(&bQuiet,sizeof(BOOL32));
    
    u16 wRe = m_pUmsSession->PostMsg(TYPE_TPMSG ); 
    
    PrtMsg( evtp_QuietEp_cmd, emEventTypeUmsSend, "confID=%d , cnsID=%d,isStart=%d", 
        tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID,bQuiet); 
	return wRe; 
}


u16 CConfCtrl::SetMuteCnsReq( const TConfEpID &tConfEpInfo , BOOL32 bMute)
{
    if ( NULL == m_pUmsSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
    pMsg->SetEvent( evtp_MuteEp_cmd );
    pMsg->SetBody( &tConfEpInfo,sizeof(TConfEpID) );
    pMsg->CatBody(&bMute,sizeof(BOOL32));
    
    u16 wRe = m_pUmsSession->PostMsg(TYPE_TPMSG ); 
    
    PrtMsg( evtp_MuteEp_cmd, emEventTypeUmsSend, "confID=%d , cnsID=%d,isStart=%d", 
        tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID,bMute); 
	return wRe; 
}


u16 CConfCtrl::SetDualCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bStart )
{
    if ( NULL == m_pUmsSession ) 
    {
        return ERR_CMS;
    }
    
    u16 wCmd = evtp_StopDual_Cmd;
    if ( bStart )
    {
        wCmd = evtp_StartDual_Cmd;
    }

    CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
    pMsg->SetEvent( wCmd );
    pMsg->SetBody( &tConfEpInfo,sizeof(TConfEpID) );
     
    
    u16 wRe = m_pUmsSession->PostMsg(TYPE_TPMSG ); 
    
    PrtMsg( wCmd, emEventTypeUmsSend, "confID=%d , cnsID=%d ", 
        tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID ); 
	return wRe; 
}



u16 CConfCtrl::UpdateAudMixListReq( const TConfAuxMixInfo &tMixInfoList )
{
   
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_UpdateAudMixInfo_cmd );
	pMsg->SetBody( &tMixInfoList, sizeof(TConfAuxMixInfo) );
 
	u16 wRe = m_pUmsSession->PostMsg(TYPE_TPMSG ); 
	
	PrtMsg( evtp_UpdateAudMixInfo_cmd, emEventTypeUmsSend, "confID= %d, bStart= %d ", tMixInfoList.m_wConfID, tMixInfoList.m_bStart );

	PrtMsg( "AudSpeakerIndex= %d, AudList : %d, %d, %d",
			tMixInfoList.m_atAuxMixList.m_awList[0], tMixInfoList.m_atAuxMixList.m_awList[1], tMixInfoList.m_atAuxMixList.m_awList[2], tMixInfoList.m_atAuxMixList.m_awList[3] );		
	
	return wRe;
}


u16 CConfCtrl::UpdatePollListReq( const TConfTurnInfo &tTurnInfoList )
{
   	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_UpdateTurn_cmd );
	pMsg->SetBody( &tTurnInfoList,sizeof(TConfTurnInfo) );
	
	u16 wRe = m_pUmsSession->PostMsg(TYPE_TPMSG ); 
	
	PrtMsg( evtp_UpdateTurn_cmd, emEventTypeUmsSend, "confID=%d, PollCount=%d", tTurnInfoList.m_wConfID,tTurnInfoList.m_atTurnList.m_wNum);
	
	return wRe;
}



u16 CConfCtrl::StartAuxMixReq( const u16 wConfID )
{
   	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_UpdateAudMixInfo_cmd );
	pMsg->SetBody( &wConfID,sizeof(u16) );
    BOOL32 bStart = TRUE;
	pMsg->CatBody(&bStart,sizeof(BOOL32));
	u16 wRe = m_pUmsSession->PostMsg(TYPE_TPMSG ); 
	
//	PrtMsg( evtp_StartAuxMix_cmd, emEventTypeUmsSend, "confID=%d ", wConfID);
	
	return wRe;
}

u16 CConfCtrl::StopAuxMixReq( const u16 wConfID )
{
    if ( NULL == m_pUmsSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
    pMsg->SetEvent( evtp_UpdateAudMixInfo_cmd );
    pMsg->SetBody( &wConfID,sizeof(u16) );
    BOOL32 bStart = FALSE;
    pMsg->CatBody(&bStart,sizeof(BOOL32));
    u16 wRe = m_pUmsSession->PostMsg(TYPE_TPMSG ); 
    
//    PrtMsg( evtp_StartAuxMix_cmd, emEventTypeUmsSend, "confID=%d ", wConfID);
    
	return wRe; 
}


u16 CConfCtrl::StartPollReq( const u16 wConfID )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pUmsSession->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_StartTurn_cmd );
	pMsg->SetBody( &wConfID,sizeof(u16) );
	
	u16 wRe = m_pUmsSession->PostMsg(TYPE_TPMSG ); 
	
	PrtMsg( evtp_StartTurn_cmd, emEventTypeUmsSend, "confID=%d ", wConfID);
	
	return wRe;
}

u16 CConfCtrl::StopPollReq( const u16 wConfID )
{	
	//wait 
	return NO_ERROR;
}


BOOL32 CConfCtrl::DeleteConfByID( const u16 wConfID )
{
    s32 nIndex = GetConfIndexByID(wConfID);
    if ( nIndex >= 0 )
    {   
        m_tplConfList.at(nIndex).m_tplPollList.Clear();
        m_tplConfList.at(nIndex).m_tplPollList = NULL;

        m_tplConfList.at(nIndex).m_tplCnsList.Clear();
        m_tplConfList.at(nIndex).m_tplCnsList = NULL;

        m_tplConfList.erase( &m_tplConfList.at(nIndex) );
        return TRUE;
    }

    return FALSE;

}

/*
TP_StartConf_UnKonw,
TP_StartConf_Success,
TP_StartConf_ConfTemplateUnExist,	//会议模板不存在
TP_StartConf_ConfFull,				//UMS会议满
TP_StartConf_ConfExist,
*/
void CConfCtrl::OnStartConfTemplateRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
	TStartConfResult tRe = * reinterpret_cast<tagTStartConfResult*>( kdvMsg.GetBody() );

    PrtMsg(evtp_StartConfTemplate_Ret,emEventTypeUmsRecv,"ConfID=%d, conftemplateID=%d, errCode=%d ( \
%d:UnKonw, %d:Success, %d:ConfTemplateUnExit, %d:ConfFull, %d:ConfExist )",tRe.m_wConfID,tRe.m_wConfTemplateID,tRe.m_emReason,
TP_StartConf_UnKonw,TP_StartConf_Success,TP_StartConf_ConfTemplateUnExist,TP_StartConf_ConfFull,TP_StartConf_ConfExist);
   
    u32 dwErrID = NO_ERROR;
    switch(tRe.m_emReason)
    {
    case TP_StartConf_UnKonw:
        dwErrID = ERR_UMC_STARTCONF_CONFTEMP_UNKNOW_ERR;
        break;
    case TP_StartConf_ConfTemplateUnExist:
        dwErrID = ERR_UMC_STARTCONF_CONFTEMP_UNEXIST;
        break;
    case TP_StartConf_ConfFull:
        dwErrID = ERR_UMC_STARTCONF_CONF_FULL ;
        break;
    case TP_StartConf_ConfExist:
        dwErrID = ERR_UMC_STARTCONF_CONF_EXIST ;
        break;
    default:
        break;

    }
	PostEvent(UI_UMS_START_CONFTEMPLATE_RSP,(WPARAM)&tRe ,dwErrID);

} 

/*
//挂断会议结果
enum EmTpDropConfRet
{
TP_DropConf_Success,
TP_DropConf_ConfUnExit,	//会议模板不存在
};*/
void CConfCtrl::OnHungUpConfRsp( const CMessage& cMsg )
{  
	CTpMsg kdvMsg(&cMsg);
	u16 wConfID = * reinterpret_cast<u16*>( kdvMsg.GetBody() );
	EmTpDropConfRet emRe = *reinterpret_cast<EmTpDropConfRet*>( kdvMsg.GetBody() + sizeof(u16) );

    PrtMsg(evtp_HungUpConf_result,emEventTypeUmsRecv,"ConfID=%d, errCode=%d ( %d:Success, %d:ConfUnExit )",
                     wConfID, emRe,TP_DropConf_Success,TP_DropConf_ConfUnExit) ; 
    
    u32 dwErrID = NO_ERROR;
    if ( emRe == TP_DropConf_ConfUnExit )
    {
        dwErrID= ERR_UMC_HUNGUP_CONF_UNEXIST;
    }
    else
    {  
        BOOL32 bTrue = DeleteConfByID(wConfID);
        if ( bTrue)
        {    
            PrtMsg(evtp_HungUpConf_result,emEventTypeUmsRecv,"[CConfCtrl::OnHungUpConfRsp] umcLib 删除 ConfID=%d 的会议", wConfID ) ; 
        }
        else
        {
            PrtMsg(evtp_HungUpConf_result,emEventTypeUmsRecv,"[CConfCtrl::OnHungUpConfRsp] umcLib 未找到 ConfID=%d 的会议", wConfID ) ; 
        }
        
    }
    
	PostEvent(UI_UMS_HANGUP_CONF_RSP,wConfID,dwErrID);
}


/*
//呼叫结果
enum EmCnsCallReason	
{
EmCnsCallReason_success,
EmCnsCallReason_hungup,			//对端不接受或者主动挂断
EmCnsCallReason_Unreachable,	//对端不在线，无法呼叫
EmCnsCallReason_resourcefull,	//对端无可用资源
EmCnsCallReason_dstnotfind,		//目标不存在
EmCnsCallReason_Busy,			//对端忙
EmCnsCallReason_Local,			//本地原因
EmCnsCallReason_NoConf,			//会议不存在
EmCnsCallReason_Exist,			//对端已在本会议中
EmCnsCallReason_Rejected,		//对端拒绝
EmCnsCallReason_peerhungup,		//对端挂断
EmCnsCallReason_Abnormal,       //本地掉线挂断
EmCnsCallReason_PeerAbnormal,   //对端掉线挂断
EmCnsCallReason_unknown,   
};
*/
void CConfCtrl::OnInviteCnsRsp( const CMessage& cMsg )
{   

	CTpMsg kdvMsg(&cMsg);
	TConfCallEpAddr tInviteInfo = * reinterpret_cast<TConfCallEpAddr*>( kdvMsg.GetBody() );

	EmCnsCallReason emRe = * reinterpret_cast<EmCnsCallReason*>( kdvMsg.GetBody() + sizeof(TConfCallEpAddr) );

	CString cnsInfo;
    cnsInfo.Format("%s",tInviteInfo.m_tCallAddr.m_tAlias.m_abyAlias);

    PrtMsg( evtp_CallEP_result,emEventTypeUmsRecv,"ConfID=%d, EPAlias=%s, errCode=%d ( \
%d:success, %d:hungup, %d:Unreachable, %d:resourcefull, %d:dstnotfind, %d:Busy, %d:LocalReason, %d:NoConf, %d:CnsHasBeenExisted )",
                                                        tInviteInfo.m_wConfID, cnsInfo, emRe,
                                                        EmCnsCallReason_success, EmCnsCallReason_hungup, 
                                                        EmCnsCallReason_Unreachable, EmCnsCallReason_resourcefull, EmCnsCallReason_dstnotfind,
                                                        EmCnsCallReason_Busy, EmCnsCallReason_Local,EmCnsCallReason_NoConf,EmCnsCallReason_Exist);
    u32 dwErrID = NO_ERROR;
    switch( emRe )
    {
    case EmCnsCallReason_hungup:
        dwErrID = ERR_UMC_CALLCNS_HUNGUP;
        break;
    case EmCnsCallReason_Unreachable:
        dwErrID = ERR_CMS_CALLCNS_UNREACHABLE;
        break;
    case EmCnsCallReason_resourcefull:
        dwErrID = ERR_UMC_CALLCNS_RESOURCE_FULL;
        break;
    case EmCnsCallReason_dstnotfind:
        dwErrID = ERR_UMC_CALLCNS_DST_NOT_FOUND;
        break;
    case EmCnsCallReason_Busy:
        dwErrID = ERR_UMC_CALLCNS_BUSY;
        break;
    case EmCnsCallReason_Local:
        dwErrID = ERR_UMC_CALLCNS_LOCAL;
        break;
    case EmCnsCallReason_NoConf:
        dwErrID = ERR_CMS_CALLCNS_NO_CONF;
        break;
    case EmCnsCallReason_Exist:
        dwErrID = ERR_UMC_CALLCNS_CNS_EXIST;
        break;
    }
   
	PostEvent( UI_UMS_INVITE_CNS_RSP, (WPARAM)&tInviteInfo, dwErrID );
} 



void CConfCtrl::OnAddConfListNotify( const CMessage& cMsg )
{  
	CTpMsg kdvMsg( &cMsg );

	TAddConfList tAddList = *reinterpret_cast<TAddConfList*>( kdvMsg.GetBody() );
  
	CString strPrt;
    
    u16 arrConfID[3] = {0};
	for ( s32 i = 0; i< tAddList.m_wRefreshNum; i++ ) 
	{  
        TCMSConf tConf ;
        tConf = tAddList.m_atTmpList[i];
        m_tplConfList.push_back( tConf ); 

       
        PrtMsg(evtp_AddConfList_Notify,emEventTypeUmsRecv,"(ID=%d name=%s chairManID=%d  speakerID = %d DualID=%d) ",
			tAddList.m_atTmpList[i].m_wConfID,tAddList.m_atTmpList[i].m_achConfName,
            tAddList.m_atTmpList[i].m_wDefaultChairMan,tAddList.m_atTmpList[i].m_wSpeaker,tAddList.m_atTmpList[i].m_wDual);

		//主格式数量
		for ( int n = 0; n < tAddList.m_atTmpList[i].m_wMainNum; n++ )
		{
			TUmsVidFormat tUmsVidFormatMain = tAddList.m_atTmpList[i].m_atTpMainVideoRes[n];

			PrtMsg( evtp_AddConfList_Notify,emEventTypeUmsRecv, "(ID=%d, tUmsVidFormatMain: m_emFormat:%d, m_emRes:%d, m_wFrameRate:%d, m_wBitrate:%d, m_emQualityLvl:%d) ",
				tAddList.m_atTmpList[i].m_wConfID, tUmsVidFormatMain.m_emFormat, tUmsVidFormatMain.m_emRes, tUmsVidFormatMain.m_wFrameRate, tUmsVidFormatMain.m_wBitrate, tUmsVidFormatMain.m_emQualityLvl );
		}

		//双流格式数量
		for ( int m = 0; m < tAddList.m_atTmpList[i].m_wMinorNum; m++ )
		{
			TUmsVidFormat tUmsVidFormatDual = tAddList.m_atTmpList[i].m_atTpMinorVideoRes[m];
			
			PrtMsg( evtp_AddConfList_Notify,emEventTypeUmsRecv, "(ID=%d, tUmsVidFormatDual: m_emFormat:%d, m_emRes:%d, m_wFrameRate:%d, m_wBitrate:%d, m_emQualityLvl:%d) ",
				tAddList.m_atTmpList[i].m_wConfID, tUmsVidFormatDual.m_emFormat, tUmsVidFormatDual.m_emRes, tUmsVidFormatDual.m_wFrameRate, tUmsVidFormatDual.m_wBitrate, tUmsVidFormatDual.m_emQualityLvl );
		}
		

        CTime tmStart( tConf.m_tStartTime ); 
        PrtMsg(  "会议开始时间：%.4d-%.2d-%.2d %.2d:%.2d:%.2d\n", 
                       tmStart.GetYear(), tmStart.GetMonth(),tmStart.GetDay(), tmStart.GetHour(),tmStart.GetMinute(),tmStart.GetSecond() );
// 		CString temp;
// 		temp.Format("(ID=%d name=%s chairManID=%d  speakerID = %d DualID=%d) ",tAddList.m_atTmpList[i].m_wConfID,tAddList.m_atTmpList[i].m_achConfName,
//             tAddList.m_atTmpList[i].m_wDefaultChairMan,tAddList.m_atTmpList[i].m_wSpeaker,tAddList.m_atTmpList[i].m_wDual);
//	    strPrt += temp; 

		arrConfID[i] = tAddList.m_atTmpList[i].m_wConfID;
	}
	
//	PrtMsg( evtp_AddConfList_Notify,emEventTypeUmsRecv,"%s", strPrt);
    

	PostEvent( UI_UMS_REFRESH_CONF_LIST, emAddConfListNotify, (LPARAM)&arrConfID );
} 


void CConfCtrl::OnDelConfListNotify( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	
	TDelConfList tAddList = *reinterpret_cast<TDelConfList*>( kdvMsg.GetBody() );
	
	CString strPrt;  

	u16 arrConfID[3] = {0};
	for ( s32 i = 0; i< tAddList.m_wRefreshNum; i++ ) 
	{  
		CString temp;
		temp.Format("(ConfID=%d ) ",tAddList.m_awConfIDList[i]);
		strPrt += temp;
         
		BOOL32 bRe = DeleteConfByID( tAddList.m_awConfIDList[i] );
		if ( !bRe ) 
		{
            strPrt += "未找到；";
        } 
		
		arrConfID[i] = tAddList.m_awConfIDList[i];
	}
	
	PrtMsg( evtp_DelConflist_Notify,emEventTypeUmsRecv,"%s", strPrt);  
	

	PostEvent(UI_UMS_REFRESH_CONF_LIST, emDelConfListNotify, (LPARAM)&arrConfID);
}



void CConfCtrl::OnUpdateConfCnsListNotify( const CMessage& cMsg )
{   
    BOOL bRefreshUI = FALSE;
	/*
#ifdef _DEBUG
    for ( int k = 0; k< m_tplConfList.Size(); k++ )
    {
        for ( int j = 0; j< m_tplConfList.GetAt(k).m_tplCnsList.Size(); j++ )
        {
            TRACE("\n[CConfCtrl::OnUpdateConfCnsListNotify]before update: confID=%d ,cnsID= %d ,cnsAliars=%s, bOnLine=%d \n",m_tplConfList.GetAt(k).m_wConfID,
                m_tplConfList.GetAt(k).m_tplCnsList.GetAt(j).m_wEpID,
                m_tplConfList.GetAt(k).m_tplCnsList.GetAt(j).m_achRoomName, m_tplConfList.GetAt(k).m_tplCnsList.GetAt(j).m_bOnline);
        }
    }

#endif
 */

	CTpMsg kdvMsg(&cMsg);
    TConfCnsInfo tConfCns = *reinterpret_cast<TConfCnsInfo*>( kdvMsg.GetBody() );
/*    
    PrtMsg( evtp_UpdateConfCnsList_Notify,emEventTypeUmsRecv,"ConfID=%d, CNS Count=%d, operateType=%d (0:Add, 1: Del, 2: Update ) ",
		                                                         tConfCns.m_wConfID, tConfCns.m_wNum,tConfCns.m_emOpr);

//#ifdef _DEBUG
    for ( int j = 0; j< tConfCns.m_wNum; j++ )
    {
        PrtMsg("\n[CConfCtrl::OnUpdateConfCnsListNotify]msginfo: confID=%d ,cnsID= %d ,cnsAliars=%s, bOnLine=%d \n",tConfCns.m_wConfID,
            tConfCns.m_tConfCnsList[j].m_wEpID,
            tConfCns.m_tConfCnsList[j].m_achRoomName,tConfCns.m_tConfCnsList[j].m_bOnline);
      }
//#endif
*/

	if ( tConfCns.m_wNum <= 0 ) 
	{
		return;
	}

	s32 nIndex = GetConfIndexByID( tConfCns.m_wConfID );
	if ( nIndex < 0 || nIndex >= m_tplConfList.size() )
	{
		return;
	}

    // TCMSConf tCmsConf = m_tplConfList.GetAt(nIndex);
	u16 wAddNum = tConfCns.m_wNum;
	switch( tConfCns.m_emOpr ) 
	{
	case tp_OprType_Add:			//增加
        {
		    m_tplConfList.at(nIndex).m_tplCnsList.Add(tConfCns.m_tConfCnsList,tConfCns.m_wNum);	
            bRefreshUI = TRUE;
        }
		break;
	case tp_OprType_Del:			//删除
        {   
            bRefreshUI = TRUE;
			for ( int i = 0; i< tConfCns.m_wNum ;  i++ )
			{   
			    s32 nCnsIndex = m_tplConfList.at(nIndex).GetCnsIndexFrmCnsLst( tConfCns.m_tConfCnsList[i].m_wEpID );
				if ( nCnsIndex >= 0 ) 
				{
                   m_tplConfList.at(nIndex).m_tplCnsList.Delete( nCnsIndex );
				}

			}
		 
		}
		break;
	case tp_OprType_Update:   // 更新
        {   
            TCMSConf tConf = m_tplConfList.at(nIndex);
			for ( int i = 0; i< tConfCns.m_wNum ;  i++ )
			{   
                if ( tConf.m_wConfID == INVALID_WORD ) 
                {
                    return ;
                }
			   s32 Index =	tConf.GetCnsIndexFrmCnsLst( tConfCns.m_tConfCnsList[i].m_wEpID );
				if ( Index >= 0 ) 
                {  
                    if (    tConf.m_tplCnsList.GetAt( Index ).m_bOnline != tConfCns.m_tConfCnsList[i].m_bOnline 
                         || strcmp( tConf.m_tplCnsList.GetAt( Index ).m_achRoomName, tConfCns.m_tConfCnsList[i].m_achRoomName ) != 0  
                         || tConf.m_tplCnsList.GetAt( Index ).m_bMute != tConfCns.m_tConfCnsList[i].m_bMute 
                         || tConf.m_tplCnsList.GetAt( Index ).m_bQuiet != tConfCns.m_tConfCnsList[i].m_bQuiet  )
                    {
                        bRefreshUI = TRUE;
                    }

					m_tplConfList.at(nIndex).m_tplCnsList.SetAt( Index,&tConfCns.m_tConfCnsList[i]);
				} 
			}
		}
		break;
	default:
		 ;
	}

/*
#ifdef _DEBUG
    for ( int i = 0; i< m_tplConfList.Size(); i++ )
    {
        for ( int j = 0; j< m_tplConfList.GetAt(i).m_tplCnsList.Size(); j++ )
        {
            TRACE("\n[CConfCtrl::OnUpdateConfCnsListNotify]afterUpdate confID=%d ,cnsID= %d ,cnsAliars=%s, bOnLine=%d \n",m_tplConfList.GetAt(i).m_wConfID,
                m_tplConfList.GetAt(i).m_tplCnsList.GetAt(j).m_wEpID,
                m_tplConfList.GetAt(i).m_tplCnsList.GetAt(j).m_achRoomName, m_tplConfList.GetAt(i).m_tplCnsList.GetAt(j).m_bOnline);
        }
    }
#endif
*/
	//if ( bRefreshUI )
	//{
		PrtMsg( evtp_UpdateConfCnsList_Notify,emEventTypeUmsRecv,"ConfID=%d, CNS Count=%d, operateType=%d (0:Add, 1: Del, 2: Update ) ",
		                                                         tConfCns.m_wConfID, tConfCns.m_wNum,tConfCns.m_emOpr);

		for ( int j = 0; j< tConfCns.m_wNum; j++ )
		{
			PrtMsg(evtp_UpdateConfCnsList_Notify,emEventTypeUmsRecv,"\n[CConfCtrl::OnUpdateConfCnsListNotify]msginfo: confID=%d ,cnsID= %d ,cnsRoomName=%s, bOnLine=%d, cnsemCallReason=%d \n",tConfCns.m_wConfID,
				tConfCns.m_tConfCnsList[j].m_wEpID,
				tConfCns.m_tConfCnsList[j].m_achRoomName,tConfCns.m_tConfCnsList[j].m_bOnline,tConfCns.m_tConfCnsList[j].m_emCallReason);
		}

        PostEvent(UI_UMS_REFRESH_CONFCNS_LIST,tConfCns.m_wConfID, (LPARAM)&tConfCns ); 

        //更新cns信息 如果是被抢 需要有提示
        if ( tp_OprType_Update == tConfCns.m_emOpr )
        {
            PostEvent(UI_UMS_UPDATE_CONFCNS_LIST,tConfCns.m_wConfID, (LPARAM)&tConfCns );
        }
	//}
	
     
} 

// TP_UMS_ChairIsUMS		10000				//主席是UMS
// TP_UMS_ChairIsMT		    10001				//主席是MT
// TP_UMS_ChairIsMCU		10002				//主席是MCU
// TP_UMS_SuperDropped		10003				//上级掉线
// TP_UMS_SysError			10004				//系统原因

void CConfCtrl::OnHungUpConfNotify( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
	u16 wConfID = * reinterpret_cast<u16*>( kdvMsg.GetBody() );
	u32 wErrorID = * reinterpret_cast<u32*>( kdvMsg.GetBody() + sizeof(u16) );

    PrtMsg(evtp_HungUp_Conf_Reason,emEventTypeUmsRecv,"ConfID=%d, wErrorID=%d ",
        wConfID, wErrorID ) ; 

    PostEvent( UI_HUNGUP_UMS_CONF_REASON, (WPARAM)wConfID , (LPARAM)wErrorID );  
}

void CConfCtrl::OnUpdateConfAuxMixlistNotify( const CMessage& cMsg )
{   
	CTpMsg kdvMsg(&cMsg);
    TConfAuxMixInfo tConfAudList = *reinterpret_cast<TConfAuxMixInfo*>( kdvMsg.GetBody() );

	PrtMsg( evtp_AuxMixInfo_Notify,emEventTypeUmsRecv,"ConfID= %d, bStart= %d,",
		                                                         tConfAudList.m_wConfID, tConfAudList.m_bStart);

	PrtMsg( " AudList : %d, %d, %d, %d",  tConfAudList.m_atAuxMixList.m_awList[0], tConfAudList.m_atAuxMixList.m_awList[1], 
			tConfAudList.m_atAuxMixList.m_awList[2], tConfAudList.m_atAuxMixList.m_awList[3] );		

    
	s32 nIndex = GetConfIndexByID( tConfAudList.m_wConfID );
	if ( nIndex < 0 ) 
	{
		return;
	}   
    m_tplConfList.at(nIndex).m_bStartAudmix = tConfAudList.m_bStart;
    memcpy( &m_tplConfList.at(nIndex).m_tAudmixList, &tConfAudList.m_atAuxMixList, sizeof(TAuxMixList) );
    
    PostEvent( UI_UMS_REFRESH_CONFAUDMIX_LIST, tConfAudList.m_wConfID, tConfAudList.m_bStart );   
} 

void CConfCtrl::OnUpdateConfPolllistNotify( const CMessage& cMsg )
{
 
	CTpMsg kdvMsg(&cMsg);
    TConfTurnInfo tConfPollList = *reinterpret_cast<TConfTurnInfo*>( kdvMsg.GetBody() );
	
	PrtMsg( evtp_UpdateTurn_cmd,emEventTypeUmsRecv,"ConfID=%d, pollMemCount=%d",
		tConfPollList.m_wConfID, tConfPollList.m_atTurnList.m_wNum );
	
	if ( tConfPollList.m_atTurnList.m_wNum <= 0 ) 
	{ 
		return;
	}
    
	s32 nIndex = GetConfIndexByID( tConfPollList.m_wConfID );
	if ( nIndex < 0 ) 
	{
		return;
	}
	
    
	m_tplConfList.at( nIndex ).m_tplPollList.Clear();
    m_tplConfList.at( nIndex ).m_tplPollList.Add(tConfPollList.m_atTurnList.m_awList,tConfPollList.m_atTurnList.m_wNum);
	
    
	PostEvent(UI_UMS_REFRESH_CONFPOLL_LIST,tConfPollList.m_wConfID);
} 


void CConfCtrl::OnUpdateConfSpeakerNotify( const CMessage& cMsg )
{
    
    CTpMsg kdvMsg(&cMsg);
    TConfEpID tConfEp = *reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() );
    
    PrtMsg( evtp_SpeakerChange_Notify,emEventTypeUmsRecv,"ConfID=%d, SpeakerCnsID=%d",
        tConfEp.m_wConfID, tConfEp.m_wEpID );
    
   
    s32 nIndex = GetConfIndexByID( tConfEp.m_wConfID );
    if ( nIndex < 0 ) 
    {   
        PrtMsg( evtp_SpeakerChange_Notify,emEventTypeUmsRecv,"未找到对应Conf信息（ ConfID=%d, SpeakerCnsID=%d ）",
        tConfEp.m_wConfID, tConfEp.m_wEpID );
        return;
    }
    
   
    m_tplConfList.at( nIndex ).m_wSpeaker = tConfEp.m_wEpID;
    
    
    PostEvent(UI_UMS_CHANGE_SPEAKER_NOTIFY,tConfEp.m_wConfID,tConfEp.m_wEpID);
} 

/*
enum EmTpApplySpeakerRet
{
TP_ApplySpeaker_Success,		
TP_ApplySpeaker_ConfUnExist,		//会议不存在
TP_ApplySpeaker_EpIDError,			//会场不存在
TP_ApplySpeaker_EpStateError,		//会场未在线或通道不未建立
};
*/
void CConfCtrl::OnSetSpokeCnsRsp( const CMessage& cMsg )
{
	
 	CTpMsg kdvMsg(&cMsg);
 	TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
 	EmTpApplySpeakerRet emRe = * reinterpret_cast<EmTpApplySpeakerRet*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(evtp_ApplySpeaker_result,emEventTypeUmsRecv,"ConfID=%d, CNSID=%d , \
         result=%d (%d:Success, %d:ConfUnExist, %d:EpIDError, %d:EpStateError)",
         tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,emRe,TP_ApplySpeaker_Success,
         TP_ApplySpeaker_ConfUnExist,TP_ApplySpeaker_EpIDError,TP_ApplySpeaker_EpStateError) ; 
 	
    if ( emRe == TP_ApplySpeaker_Success )
    {
       s32 index =  GetConfIndexByID(tConfEpInfo.m_wConfID);
       if ( index < 0 )
       {   
           TRACE("\n[CConfCtrl::OnSetSpokeCnsRsp] conf(id=%d) is not exist \n",tConfEpInfo.m_wConfID);
           return ;
       }

       m_tplConfList.at(index).m_wSpeaker = tConfEpInfo.m_wEpID;
    }

 	PostEvent(UI_UMS_SET_SPEAKER_RSP,tConfEpInfo.m_wConfID,emRe);	
	return;
} 

void CConfCtrl::OnSetMuteCnsRsp( const CMessage& cMsg ) 
{ 
    CTpMsg kdvMsg(&cMsg);
    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    BOOL32 bRe = * reinterpret_cast<BOOL32*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(evtp_MuteEp_Ind,emEventTypeUmsRecv,"ConfID=%d, CNSID=%d ,bStart=%d  ",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,bRe ) ; 
    
    
    s32 index =  GetConfIndexByID(tConfEpInfo.m_wConfID);
    if ( index < 0 )
    {   
        TRACE("\n[CConfCtrl::OnSetMuteCnsRsp] conf(id=%d) is not exist \n",tConfEpInfo.m_wConfID);
        return ;
    }
    
    s32 CnsIndex = m_tplConfList.at(index).GetCnsIndexFrmCnsLst(tConfEpInfo.m_wEpID);
    if ( index < 0 )
    {   
        TRACE("\n[CConfCtrl::OnSetMuteCnsRsp] confCns(id=%d) is not exist \n",tConfEpInfo.m_wEpID);
        return ;
    }
    
    m_tplConfList.at(index).m_tplCnsList.GetAt(CnsIndex).m_bMute = bRe;
  
    TRACE("\n[CConfCtrl::OnSetMuteCnsRsp] name = %s bOnline=%d\n",
        m_tplConfList.at(index).m_tplCnsList.GetAt(CnsIndex).m_achRoomName, m_tplConfList.at(index).m_tplCnsList.GetAt(CnsIndex).m_bOnline); 
    PostEvent(UI_UMS_SET_MUTE_CNS_RSP,tConfEpInfo.m_wConfID,bRe);	
    return;
} 
 
void CConfCtrl::OnSetSilenceCnsRsp( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);
    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    BOOL32 bRe = * reinterpret_cast<BOOL32*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(evtp_QuietEp_Ind,emEventTypeUmsRecv,"ConfID=%d, CNSID=%d ,bStart=%d  ",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,bRe ) ; 

    s32 index =  GetConfIndexByID(tConfEpInfo.m_wConfID);
    if ( index < 0 )
    {   
        TRACE("\n[CConfCtrl::OnSetMuteCnsRsp] conf(id=%d) is not exist \n",tConfEpInfo.m_wConfID);
        return ;
    }
    
    s32 CnsIndex = m_tplConfList.at(index).GetCnsIndexFrmCnsLst(tConfEpInfo.m_wEpID);
    if ( index < 0 )
    {   
        TRACE("\n[CConfCtrl::OnSetSilenceCnsRsp] confCns(id=%d) is not exist \n",tConfEpInfo.m_wEpID);
        return ;
    }
    
    m_tplConfList.at(index).m_tplCnsList.GetAt(CnsIndex).m_bQuiet = bRe; 

    PostEvent(UI_UMS_SET_QUIET_CNS_RSP,tConfEpInfo.m_wConfID,bRe);	
    return;
    
} 


/*
enum EmTPDualReason
{
emTpDualAccept,
emTpDualBusy,
emTpDualPreemptive,
emTpDualPeerReject,
emTpDualPeerStop,
emTpDualNoVideo
};
*/
void CConfCtrl::OnSetDualCnsRsp( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);
    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    EmTPDualReason emRe = * reinterpret_cast<EmTPDualReason*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(evtp_StartDual_Ind,emEventTypeUmsRecv,"ConfID=%d, CNSID=%d ,erroCode=%d \
        (%d:Accept, %d:DualBusy,%d:Preemptive, %d:PeerReject, %d:PeerStop,%d:NoVideo)",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,emRe ,emTpDualAccept,
        emTpDualBusy,emTpDualPreemptive,emTpDualPeerReject,emTpDualPeerStop,emTpDualNoVideo) ; 
    
    if ( emRe == emTpDualAccept )
    {
        s32 index =  GetConfIndexByID(tConfEpInfo.m_wConfID);
        if ( index < 0 )
        {   
            TRACE("\n[CConfCtrl::OnSetDualCnsRsp] conf(id=%d) is not exist \n",tConfEpInfo.m_wConfID);
            return ;
        }
        
        m_tplConfList.at(index).m_wDual = tConfEpInfo.m_wEpID;
    }

    PostEvent(UI_UMS_SET_DUAL_CNS_RSP,tConfEpInfo.m_wConfID,emRe);	
    return;
    
}  

void CConfCtrl::OnDualCnsNotify( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);
    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() );  
    PrtMsg(evtp_DualEp_Notify,emEventTypeUmsRecv,"ConfID=%d, CNSID=%d ",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID ) ; 
    
    s32 index =  GetConfIndexByID(tConfEpInfo.m_wConfID);
    if ( index < 0 )
    {   
        TRACE("\n[CConfCtrl::OnDualCnsNotify] conf(id=%d) is not exist \n",tConfEpInfo.m_wConfID);
        return ;
    }
    m_tplConfList.at(index).m_wDual = tConfEpInfo.m_wEpID;

    PostEvent(UI_UMS_DUAL_CNS_NOTIFY,tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID);	
    return;
    
}  

void CConfCtrl::OnCasadeNotify( const CMessage& cMsg )
{
    CTpMsg kdvMsg( &cMsg );
    
    TChairConfInfo tChairInfo = *reinterpret_cast<TChairConfInfo*>( kdvMsg.GetBody() );

    PrtMsg( evtp_ChairConfInfo_Notify,emEventTypeUmsRecv,"下级会议ID=%d, 上级会议名=%s，上级主席=%s ",tChairInfo.m_wConfID, tChairInfo.m_tConfName.m_abyAlias, tChairInfo.m_tChairName.m_abyAlias);  

    CString strPrt;  
    
    u16 confID =  tChairInfo.m_wConfID;
    s32 nIndex = GetConfIndexByID( confID );
    if ( nIndex >= 0 ) 
    {   
       // m_tplConfList.at(nIndex).SetCascadeInfo( tChairInfo );
    }
    else
    {
       PrtMsg( evtp_ChairConfInfo_Notify,emEventTypeUmsRecv,"umcLib中未找到ID = %d 的会议 ", confID);  
    } 
    
    PrtMsg( evtp_ChairConfInfo_Notify,emEventTypeUmsRecv,"%s", strPrt);  
    
    PostEvent( UI_UMS_REFRESH_CONF_LIST, emCasadeNotify, confID );
	PostEvent(UI_UMS_CASCADE_CONF_NOTIFY,confID);
}


void CConfCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CConfCtrl, cMsg);
}

void CConfCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
    PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
}


s32 CConfCtrl::GetConfIndexByID( u16 wConfID ) const
{
    vector<TCMSConf>::iterator it =  const_cast<TCMSConf*> ( m_tplConfList.begin() );
    s32 i = 0;
    while( it != m_tplConfList.end() )
    {
        if( wConfID == it->m_wConfID )
        {
            return i;
        }
        it ++;
        i ++;
    }
	 
	return -1;
}