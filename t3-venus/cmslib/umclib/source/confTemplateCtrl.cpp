// confTemplateCtrl.cpp: implementation of the CConfTemplateCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "confTemplateCtrl.h"
#include "eventoutumsconftemplate.h"
#include "tpmsg.h"
#include "cmsstruct.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 
CConfTemplateCtrl::CConfTemplateCtrl(CUmsSession &cUmsSession) 
                  : CConfTemplateCtrlIF(),
				  m_pUmsSession(NULL),
				  m_tplConfTempList()
{  
   m_pUmsSession = &cUmsSession;
   BuildEventsMap();
}

CConfTemplateCtrl::~CConfTemplateCtrl()
{
	m_tplConfTempList.Clear();
}
 

void CConfTemplateCtrl::BuildEventsMap() 
{   
	REG_PFUN(evpt_OperatorConfTemplate_Ret,OnOperateConfTempRsp);
	REG_PFUN(evtp_AddConftemplate_Notify,OnAddConfTempNotify);
    REG_PFUN(evtp_Delconftemplate_Notify,OnDelConfTempNotify);
	REG_PFUN(evtp_Updateconftemplate_Notify,OnUpdateConfTempNotify);
	REG_PFUN(ev_conf_bas_used_nty,OnUpdateResUsedCountNotify);
	REG_PFUN(ev_del_all_conftemp_rsp,OnDelAllConfTempRsp);
    //断链清空资源
    REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
 
}

void CConfTemplateCtrl::OnLinkBreak( const CMessage& cMsg )
{
    m_tplConfTempList.Clear();
    PrtMsg( OSP_DISCONNECT,emEventTypeUmsRecv,"清空会议模板列表"); 
    PostEvent( UI_UMS_REFRESH_CONFTEMPLATE_LIST );
}

u16 CConfTemplateCtrl::GetConfTemplateList( TplArray<TTPConfTemplate> &tplConfTempList ) const
{   
    tplConfTempList = m_tplConfTempList;
	return NO_ERROR;
}


u16 CConfTemplateCtrl::AddConfTemplateReq( const TTPConfTemplate &tConfTemp )    
{   
	if ( NULL == m_pUmsSession ) 
	{
		return  ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(evtp_AddConfTemplate_req);
	int i = sizeof(TTPConfTemplate);
	pkdvMsg->SetBody( &tConfTemp,sizeof(TTPConfTemplate) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg(evtp_AddConfTemplate_req,emEventTypeUmsSend,"ConfTemplateID=%d, name=%s,E164=%s",
		                                  tConfTemp.m_wID,tConfTemp.m_achConfName,tConfTemp.m_achConfE164);
	return wRe;
}


u16 CConfTemplateCtrl::ModifyConfTemplateReq( const TTPConfTemplate &tConfTemp )    
{   
	
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(evtp_Updateconftemplate_Req);
	pkdvMsg->SetBody( &tConfTemp,sizeof(TTPConfTemplate) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg(evtp_Updateconftemplate_Req,emEventTypeUmsSend,"ConfTemplateID=%d, E164Name=%s",
		                                                tConfTemp.m_wID,tConfTemp.m_achConfName);
	return wRe;
}


u16 CConfTemplateCtrl::DeleteConfTemplateReq( const u16 wConfTempID )   
{ 
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(evtp_DelConftemplate_Req);
	pkdvMsg->SetBody( &wConfTempID,sizeof(u16) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg(evtp_DelConftemplate_Req,emEventTypeUmsSend,"ConfTemplateID=%d",wConfTempID);	                                               
	return wRe;	
	
}

u16 CConfTemplateCtrl::DelAllConfTempReq()   
{ 
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_del_all_conftemp_req);
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_del_all_conftemp_req, emEventTypeUmsSend, "del all conftemp req" );	                                               
	return wRe;
}
 
void CConfTemplateCtrl::OnOperateConfTempRsp( const CMessage& cMsg )
{  
	CTpMsg msg(&cMsg);
 
    tagTOprConfTmpResult tTemplate = *reinterpret_cast<tagTOprConfTmpResult*>(msg.GetBody());

	PrtMsg(evpt_OperatorConfTemplate_Ret,emEventTypeUmsRecv,"ConfTemplateID=%d, opReslt=%d ( \
0:UnKonw, 1:AddSuccess, 2:DelSuccess, 3:UpdateSuccess,4:MaxNum,	5:E164Repeat, 6:UnFindConf )",
		                                                tTemplate.m_wID,tTemplate.m_emReason);

    PostEvent(UI_UMS_OPERATE_CONFTEMP_RET, tTemplate.m_emReason, tTemplate.m_wID );
}

void CConfTemplateCtrl::OnAddConfTempNotify( const CMessage& cMsg )
{   
	CTpMsg msg(&cMsg); 
	TTPConfTemplate tTemplate = *reinterpret_cast<TTPConfTemplate*>(msg.GetBody());
	BOOL32 bIsEnd = *reinterpret_cast<BOOL32*>(msg.GetBody() + sizeof(TTPConfTemplate));

	PrtMsg(evtp_AddConftemplate_Notify,emEventTypeUmsRecv,"ConfTemplateID=%d, name=%s, E164=%s, bIsEnd=%d",
             tTemplate.m_wID,tTemplate.m_achConfName,tTemplate.m_achConfE164,bIsEnd);

	m_tplConfTempList.Add(&tTemplate/*tTemplate.m_atTmpList ,tTemplate.m_wRefreshNum*/);

	if ( bIsEnd )
	{
		PostEvent( UI_UMS_REFRESH_CONFTEMPLATE_LIST,(WPARAM)tTemplate.m_wID );
	}
}


void CConfTemplateCtrl::OnDelConfTempNotify( const CMessage& cMsg )
{
    CTpMsg msg(&cMsg); 
	TDelRefreshConfTemplate tDelTemplateList = *reinterpret_cast<TDelRefreshConfTemplate*>(msg.GetBody());

	PrtMsg(evtp_Delconftemplate_Notify,emEventTypeUmsRecv,"DeleteNum=%d, first confTemplateID=%d",
		                                           tDelTemplateList.m_wRefreshNum,tDelTemplateList.m_awTmpList[0]);

    for ( int i = 0; i<tDelTemplateList.m_wRefreshNum; i++ ) 
	{   
		int iIndex = FindConfTemplateByID( tDelTemplateList.m_awTmpList[i]);
		if ( iIndex < 0 ) 
		{
			continue;
		}

		m_tplConfTempList.Delete( iIndex );
    } 

	PostEvent( UI_UMS_REFRESH_CONFTEMPLATE_LIST, (WPARAM)tDelTemplateList.m_awTmpList[0]);
}


void CConfTemplateCtrl::OnUpdateConfTempNotify( const CMessage& cMsg )
{
	CTpMsg msg(&cMsg); 
	TTPConfTemplate tTemplate = *reinterpret_cast<TTPConfTemplate*>(msg.GetBody());
	BOOL32 bIsEnd = *reinterpret_cast<BOOL32*>(msg.GetBody() + sizeof(TTPConfTemplate));

	PrtMsg(evtp_Updateconftemplate_Notify,emEventTypeUmsRecv,"ConfTemplateID=%d, name=%s, E164=%s, bIsEnd=%d",
        tTemplate.m_wID,tTemplate.m_achConfName,tTemplate.m_achConfE164,bIsEnd);
 

	int iIndex = FindConfTemplateByID( tTemplate.m_wID);
 	if ( iIndex >= 0 ) 
	{
		m_tplConfTempList.SetAt( iIndex,&tTemplate );
		if ( bIsEnd )
		{
			PostEvent( UI_UMS_REFRESH_CONFTEMPLATE_LIST  ,(WPARAM)tTemplate.m_wID);
		}
	}
 
	//		
//		m_tplConfTempList.SetAt(iIndex,&tDelTemplateList.m_atTmpList[i] );

//	TAddRefreshConfTemplate tDelTemplateList = *reinterpret_cast<TAddRefreshConfTemplate*>(msg.GetBody());
//    for ( int i = 0; i<tDelTemplateList.m_wRefreshNum; i++ ) 
//	{   
//		int iIndex = FindConfTemplateByID( tDelTemplateList.m_atTmpList[i].m_wID );
//		if ( iIndex < 0 ) 
//		{
//			break;
//		}
//		
//		m_tplConfTempList.SetAt(iIndex,&tDelTemplateList.m_atTmpList[i] );
//    }
	
//	PostEvent(UI_UMS_REFRESH_CONFTEMPLATE);
}

void CConfTemplateCtrl::DispEvent(const CMessage &cMsg)
{
   DISP_FUN(CConfTemplateCtrl, cMsg);
}

void CConfTemplateCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
    PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
}

BOOL32  CConfTemplateCtrl::IsExistConfTemplate ( u16 wConfTemplateID )
{   
	BOOL32 bRe = FALSE;
	u16 wCont = m_tplConfTempList.Size();
	for ( u16 i = 0; i < wCont; i++ ) 
	{
		if ( m_tplConfTempList[i].m_wID == wConfTemplateID)
		{
			bRe = TRUE;
			break;
		}
	}

	return bRe;
}

int CConfTemplateCtrl::FindConfTemplateByID( u16 wConfTemplateID )
{    
	int wCont = m_tplConfTempList.Size();
	for ( int i = 0; i < wCont; i++ ) 
	{
		if ( m_tplConfTempList[i].m_wID == wConfTemplateID)
		{   
			return i;
		}
	}
	
	return -1;
}

void CConfTemplateCtrl::OnUpdateResUsedCountNotify( const CMessage& cMsg )
{
	CTpMsg msg(&cMsg); 
	u16* wUsedCount = (u16*)(msg.GetBody());
	if ( NULL != wUsedCount )
	{
		PrtMsg(ev_conf_bas_used_nty,emEventTypeUmsRecv,"res used count=%d", *wUsedCount);
			
		PostEvent( UI_UMS_CONFTMPRESUSEDCOUNT_NOTIFY,(WPARAM)wUsedCount);
	}
	else
	{
		PrtMsg( ev_card_upgrade_res, emEventTypeUmstoolRecv, "invlid res used count data" );
	}
}

void CConfTemplateCtrl::OnDelAllConfTempRsp( const CMessage& cMsg )
{
	CTpMsg msg(&cMsg);
    TOprConfTmpResult tTemplate = *reinterpret_cast<TOprConfTmpResult*>(msg.GetBody());

	if ( TP_ConfTemplate_DelSuccess == tTemplate.m_emReason )
	{
		m_tplConfTempList.Clear();
		PrtMsg( ev_del_all_conftemp_rsp, emEventTypeUmsRecv, "del all conftemp success");
	} 
	else
	{
		PrtMsg( ev_del_all_conftemp_rsp, emEventTypeUmsRecv, "del all conftemp fail");
	}

    PostEvent(UI_UMS_DEL_ALL_CONFTEMP_RET, tTemplate.m_emReason);
}