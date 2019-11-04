// userCtrl.cpp: implementation of the CUserCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cncuserctrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCncUserCtrl::CCncUserCtrl( CCnsSession &cSession)
			:CCncUserCtrlIF(),
		     m_tplUserList()
                                                  
{
	m_pSession = &cSession;
	BuildEventsMap();
} 

CCncUserCtrl::~CCncUserCtrl()
{
	
}


void CCncUserCtrl::BuildEventsMap()
{  
	REG_PFUN(ev_CNSAddUser_Notify, CCncUserCtrl::OnUserChangedNotify);
	REG_PFUN(ev_CNSUpdateUser_Notify, CCncUserCtrl::OnUserChangedNotify);
	REG_PFUN(ev_CNSDelUser_Notify, CCncUserCtrl::OnUserChangedNotify);

	REG_PFUN(ev_CNSAddUserRet, CCncUserCtrl::OnOperateUserRsp);
	REG_PFUN(ev_CNSChangePWDRet, CCncUserCtrl::OnOperateUserRsp);
	REG_PFUN(ev_CNSDelUserRet, CCncUserCtrl::OnOperateUserRsp);

	//断链清空资源
	REG_PFUN(OSP_DISCONNECT, CCncUserCtrl::OnLinkBreak); 
}

void CCncUserCtrl::OnLinkBreak(const CMessage& cMsg)
{
    m_tplUserList.Clear();
    PrtMsg( OSP_DISCONNECT,emEventTypeCnsRecv,"清空用户列表"); 
    PostEvent( UI_UMS_REFRESH_USER_LIST );
}

void CCncUserCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN( CCncUserCtrl, cMsg) ;
}

void CCncUserCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
   PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
} 

u16  CCncUserCtrl::GetUserList( TplArray<CUserFullInfo>& tplUserList ) const
{   
	tplUserList = m_tplUserList;
	return NO_ERROR;
}
 

u16  CCncUserCtrl::AddUserReq( const CUserFullInfo& tUser )  
{
	if ( NULL == m_pSession ) 
	{
		return ERR_CMS;
	}

	CMessage *pCMsg = m_pSession->GetCMsgPtr();
	pCMsg->event = ev_CNSAddUserReq ;
	pCMsg->content = (u8*)&tUser ;
	pCMsg->length = sizeof(CUserFullInfo);

	u16 re = m_pSession->PostMsg( TYPE_CMESSAGE );
 
	PrtMsg(ev_CNSAddUserReq, emEventTypeCnsSend, "username=%s, pswd=%s", tUser.m_achname,tUser.m_achpassword);
    return re;
}


u16  CCncUserCtrl::ModifyUserReq( const CUserFullInfo& tUser )  
{
	if ( NULL == m_pSession ) 
	{
		return ERR_CMS;
	}
	
	CMessage *pCMsg = m_pSession->GetCMsgPtr();
	pCMsg->event = ev_CNSChangePWDReq  ;
	pCMsg->content = (u8*)&tUser;
	pCMsg->length = sizeof(CUserFullInfo) ;
	u16 re = m_pSession->PostMsg( TYPE_CMESSAGE );

	PrtMsg(ev_CNSChangePWDReq, emEventTypeCnsSend,"username=%s, pswd=%s", tUser.m_achname,tUser.m_achpassword);
    return re;
}


u16  CCncUserCtrl::DeleteUserReq( const CUserFullInfo& tUser )  
{
	if ( NULL == m_pSession ) 
	{
		return ERR_CMS;
	}
	
	CMessage *pCMsg = m_pSession->GetCMsgPtr();
	pCMsg->event = ev_CNSDelUserReq ;
	pCMsg->content =  (u8*)&tUser;
	pCMsg->length = sizeof(CUserFullInfo) ;
	u16 re = m_pSession->PostMsg( TYPE_CMESSAGE );

	PrtMsg(ev_CNSDelUserReq, emEventTypeCnsSend, "username=%s, pswd=%s", tUser.m_achname,tUser.m_achpassword);
    return re;
}


void  CCncUserCtrl::OnUserChangedNotify(const CMessage& cMsg)
{   
   CUserFullInfo tUser = *reinterpret_cast<CUserFullInfo *>( cMsg.content );
   u16 wEvent = cMsg.event;

   PrtMsg(wEvent,emEventTypeCnsRecv,"userName=%s, pswd=%s",
		                                                tUser.m_achname,tUser.m_achpassword);

   BOOL32 bPostEvent = FALSE;
   switch( wEvent ) 
   {
   case ev_CNSAddUser_Notify:
	   {
		   m_tplUserList.Add( &tUser );
           bPostEvent = TRUE;
	   }
	   
   	break;
   case ev_CNSDelUser_Notify:
	   {
		   s16 nIndex = FindUserByName( tUser.GetName() );
		   if ( nIndex >= 0 ) 
		   {
			   m_tplUserList.Delete(nIndex);
			   bPostEvent = TRUE;
		   }  
	   }
	   break;
	    
   case ev_CNSUpdateUser_Notify:
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
	   PostEvent(UI_UMS_REFRESH_USER_LIST);
   }
//   s16 nCnt = msg.GetBodyLen() / (sizeof(CUserFullInfo));
//   m_tplUserList.Add((CUserFullInfo*)msg.GetBody(),nCnt);
}

void  CCncUserCtrl::OnOperateUserRsp(const CMessage& cMsg)
{    
	CTpMsg kdvMsg( &cMsg ); 
    EmTpRet emRe = *reinterpret_cast<EmTpRet *>( kdvMsg.GetBody() );
	u16 wEvent = cMsg.event;

	PrtMsg( wEvent,emEventTypeCnsRecv,"Error Code: %d ( 0:Failed, 1:Success )",emRe );
    LPARAM lParam = NO_ERROR;
    if ( emRe != tp_Ret_Success )
    {  
        lParam = *reinterpret_cast< u16 *>( kdvMsg.GetBody() + sizeof(EmTpRet) ); 
    }

	PostEvent(UI_UMS_OPERATE_USER_RET,wEvent,lParam);
}


s16  CCncUserCtrl::FindUserByName( s8 *pName )
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