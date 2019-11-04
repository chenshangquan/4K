// userCtrl.cpp: implementation of the CUserCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "userCtrl.h"
#include "eventoutumslogin.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserCtrl::CUserCtrl( CUmsSession &cUmsSession)
          :CUserCtrlIF(),
		  m_pUmsSession(NULL),
		  m_tplUserList()
                                                  
{
   m_pUmsSession = &cUmsSession;
   BuildEventsMap();
} 

CUserCtrl::~CUserCtrl()
{
	m_tplUserList.Clear();
}



void  CUserCtrl::BuildEventsMap()
{  
   REG_PFUN(ev_UmsAddUser_Notify,OnUserChangedNotify);
   REG_PFUN(ev_UmsUpdateUser_Notify,OnUserChangedNotify);
   REG_PFUN(ev_UmsDelUser_Notify,OnUserChangedNotify);

   REG_PFUN(ev_UMSAddUserRet,OnOperateUserRsp);
   REG_PFUN(ev_UMSChangePWDRet,OnOperateUserRsp);
   REG_PFUN(ev_UMSDelUserRet,OnOperateUserRsp);

   //断链清空资源
    REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
}

void  CUserCtrl::OnLinkBreak(const CMessage& cMsg)
{
    m_tplUserList.Clear();
    PrtMsg( OSP_DISCONNECT,emEventTypeUmsRecv,"清空用户列表"); 
    PostEvent( UI_UMS_REFRESH_USER_LIST );
}

void CUserCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CUserCtrl,cMsg);
}

void CUserCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
   PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
} 

u16  CUserCtrl::GetUserList( TplArray<CUserFullInfo>& tplUserList ) const
{   
	tplUserList = m_tplUserList;
	return NO_ERROR;
}
 

u16  CUserCtrl::AddUserReq( const CUserFullInfo& tUser )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}

	CMessage *pCMsg = m_pUmsSession->GetCMsgPtr();
	pCMsg->event = ev_UMSAddUserReq ;
	pCMsg->content = (u8*)&tUser ;
	pCMsg->length = sizeof(CUserFullInfo);

	u16 re = m_pUmsSession->PostMsg( TYPE_CMESSAGE );
 
	PrtMsg(ev_UMSAddUserReq,emEventTypeUmsSend,"userName=%s, pswd=%s",
		                                                tUser.m_achname,tUser.m_achpassword);
    return re;
}


u16  CUserCtrl::ModifyUserReq( const CUserFullInfo& tUser )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CMessage *pCMsg = m_pUmsSession->GetCMsgPtr();
	pCMsg->event = ev_UMSChangePWDReq  ;
	pCMsg->content = (u8*)&tUser;
	pCMsg->length = sizeof(CUserFullInfo) ;
	u16 re = m_pUmsSession->PostMsg( TYPE_CMESSAGE );

	PrtMsg(ev_UMSChangePWDReq,emEventTypeUmsSend,"userName=%s, pswd=%s",
		                                                tUser.m_achname,tUser.m_achpassword);
    return re;
}


u16  CUserCtrl::DeleteUserReq( const CUserFullInfo& tUser )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CMessage *pCMsg = m_pUmsSession->GetCMsgPtr();
	pCMsg->event = ev_UMSDelUserReq ;
	pCMsg->content =  (u8*)&tUser;
	pCMsg->length = sizeof(CUserFullInfo) ;
	u16 re = m_pUmsSession->PostMsg( TYPE_CMESSAGE );

	PrtMsg(ev_UMSDelUserReq,emEventTypeUmsSend,"userName=%s, pswd=%s",
		                                                tUser.m_achname,tUser.m_achpassword);
    return re;
}


void  CUserCtrl::OnUserChangedNotify(const CMessage& cMsg)
{   
   CUserFullInfo tUser = *reinterpret_cast<CUserFullInfo *>( cMsg.content );
   u16 wEvent = cMsg.event;

   PrtMsg(wEvent,emEventTypeUmsRecv,"userName=%s, pswd=%s",
		                                                tUser.m_achname,tUser.m_achpassword);

   BOOL32 bPostEvent = FALSE;
   switch( wEvent ) 
   {
   case ev_UmsAddUser_Notify:
	   {
		   m_tplUserList.Add( &tUser );
           bPostEvent = TRUE;
	   }
	   
   	break;
   case ev_UmsDelUser_Notify:
	   {
		   s16 nIndex = FindUserByName( tUser.GetName() );
		   if ( nIndex >= 0 ) 
		   {
			   m_tplUserList.Delete(nIndex);
			   bPostEvent = TRUE;
		   }  
	   }
	   break;
	    
   case ev_UmsUpdateUser_Notify:
	   {
		   s16 nIndex = FindUserByName( tUser.GetName() );
		   if ( nIndex >= 0 ) 
		   {
			   m_tplUserList.SetAt(nIndex,&tUser);
			   bPostEvent = TRUE;
		   }  
	   }
	   break;
   default:
	   ;
   }

   if ( bPostEvent ) 
   {
	   PostEvent( UI_UMS_REFRESH_USER_LIST, (WPARAM)&tUser );
   }
//   s16 nCnt = msg.GetBodyLen() / (sizeof(CUserFullInfo));
//   m_tplUserList.Add((CUserFullInfo*)msg.GetBody(),nCnt);
}

void  CUserCtrl::OnOperateUserRsp(const CMessage& cMsg)
{    
	CTpMsg kdvMsg( &cMsg ); 
    EmTpRet emRe = *reinterpret_cast<EmTpRet *>( kdvMsg.GetBody() );
	u16 wEvent = cMsg.event;

	PrtMsg( wEvent,emEventTypeUmsRecv,"Error Code: %d ( 0:Failed, 1:Success )",emRe );
    LPARAM lParam = NO_ERROR;
    if ( emRe != tp_Ret_Success )
    {  
        lParam = *reinterpret_cast< u16 *>( kdvMsg.GetBody() + sizeof(EmTpRet) ); 
    }

	PostEvent(UI_UMS_OPERATE_USER_RET,wEvent,lParam);
}


s16  CUserCtrl::FindUserByName( s8 *pName )
{
	s16 re = -1;
	s16 nCont = m_tplUserList.Size();
	for ( s16 i = 0; i< nCont; i++ )
	{  
        bool bIsEqual = m_tplUserList.GetAt(i).IsEqualName( pName );
		if ( bIsEqual ) 
		{
			return i;
			break;
		}
	}

	return -1;
}