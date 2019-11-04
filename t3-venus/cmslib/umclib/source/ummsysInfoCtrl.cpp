// umssysinfoCtrl.cpp: implementation of the CUmsSysInfoCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umssysinfoCtrl.h"
#include "eventoutumslogin.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUmsSysInfoCtrl::CUmsSysInfoCtrl( CUmsSession &cUmsSession)
          :CUmsSysInfoCtrlIF(),
		  m_pUmsSession(NULL)                                       
{
   m_pUmsSession = &cUmsSession;
   BuildEventsMap();
} 

CUmsSysInfoCtrl::~CUmsSysInfoCtrl()
{

}

void  CUmsSysInfoCtrl::BuildEventsMap()
{  
   REG_PFUN(ev_verInfo_Nty,OnRefreshUmsVerNotify);
   REG_PFUN(ev_sysInfo_Nty,OnRefreshUmsSysInfoNotify);
   REG_PFUN(ev_confCount_Nty,OnConfCountNotify);
   REG_PFUN(ev_authCount_Nty,OnAuthCountNotify);
   REG_PFUN(ev_hduCount_Nty,OnTvwUsedNotify);

   //断链清空资源
   REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
}

void  CUmsSysInfoCtrl::OnLinkBreak(const CMessage& cMsg)
{
    PrtMsg( OSP_DISCONNECT,emEventTypeUmstoolRecv,"清空ums系统信息"); 
}

void CUmsSysInfoCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CUmsSysInfoCtrl,cMsg);
}

void CUmsSysInfoCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
   PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
} 
 
u16  CUmsSysInfoCtrl::RefreshUmsSysInfoReq()  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_sysInfo_req);
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_sysInfo_req, emEventTypeUmstoolSend, "发送ums系统信息请求" );

    return NO_ERROR;
}

void  CUmsSysInfoCtrl::OnRefreshUmsVerNotify(const CMessage& cMsg)
{   
	CTpMsg kdvMsg( &cMsg );
    m_tUmsVer = *reinterpret_cast<TUmsVersion*>( kdvMsg.GetBody() );

	PrtMsg( ev_verInfo_Nty, emEventTypeUmstoolRecv, "SoftVer=%s HardVer=%s", m_tUmsVer.m_abSoftVersion, m_tUmsVer.m_abHardVersion );
	
	PostEvent(UI_UMSTOOL_MSG_UMSVER_NTY);
}

void  CUmsSysInfoCtrl::OnRefreshUmsSysInfoNotify(const CMessage& cMsg)
{   
	CTpMsg kdvMsg( &cMsg );
    m_tUmsSysInfo = *reinterpret_cast<TToolSysInfo*>( kdvMsg.GetBody() );
	
	PrtMsg( ev_sysInfo_Nty, emEventTypeUmstoolRecv, "CpuRate=%d MemRate=%d", m_tUmsSysInfo.m_dwCpuRate, m_tUmsSysInfo.m_dwMemRate );
	PostEvent(UI_UMSTOOL_MSG_SYSINFO_NTY);
}

u16  CUmsSysInfoCtrl::GetUmsVerData( TUmsVersion& tUmsVer) const
{
	tUmsVer = m_tUmsVer;

	return NO_ERROR;
}

u16  CUmsSysInfoCtrl::GetUmsSysInfoData( TToolSysInfo& tUmsSysInfo) const
{
	tUmsSysInfo = m_tUmsSysInfo;

	return NO_ERROR;
}

u16  CUmsSysInfoCtrl::GetUmsTvwUsedData( TTPBrdUsedInfo& tTvwUsed) const
{
	tTvwUsed = m_tTvwUsed;
	
	return NO_ERROR;
}

u16  CUmsSysInfoCtrl::ConfCountReq()  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_confCount_req);
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_confCount_req, emEventTypeUmstoolSend, "发送ums会议数请求" );
	
    return NO_ERROR;
}

void  CUmsSysInfoCtrl::OnConfCountNotify(const CMessage& cMsg)
{   
	CTpMsg kdvMsg( &cMsg );
    m_nConfCount = *reinterpret_cast<u32*>( kdvMsg.GetBody() );
	
	PrtMsg( ev_confCount_Nty, emEventTypeUmstoolRecv, "ConfCount=%d", m_nConfCount );
	PostEvent(UI_UMSTOOL_MSG_CONFCOUNT_NTY);
}

u16  CUmsSysInfoCtrl::AuthCountReq()  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_authCount_req);
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_authCount_req, emEventTypeUmstoolSend, "发送授权数目请求" );
	
    return NO_ERROR;
}

void  CUmsSysInfoCtrl::OnAuthCountNotify(const CMessage& cMsg)
{   
	CTpMsg kdvMsg( &cMsg );
    u32 nAuthTotalCount = *reinterpret_cast<u32*>( kdvMsg.GetBody() );
    u32 nAuthCount = *reinterpret_cast<u32*>( kdvMsg.GetBody() + sizeof(u32) );

	m_nAuthCount = std::pair<int,int>( nAuthTotalCount, nAuthCount );

	PrtMsg( ev_authCount_Nty, emEventTypeUmstoolRecv, "AuthCount=%d AuthTotalCount=%d", nAuthCount, nAuthTotalCount );
	PostEvent(UI_UMSTOOL_MSG_AUTHCOUNT_NTY);	
}

u16  CUmsSysInfoCtrl::TvwUsedCountReq()  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_hduCount_req);
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_hduCount_req, emEventTypeUmstoolSend, "发送电视墙占用情况请求" );
	
    return NO_ERROR;
}

void  CUmsSysInfoCtrl::OnTvwUsedNotify(const CMessage& cMsg)
{   
	CTpMsg kdvMsg( &cMsg );
    m_tTvwUsed = *reinterpret_cast<TTPBrdUsedInfo*>( kdvMsg.GetBody() );

	PrtMsg( ev_hduCount_Nty, emEventTypeUmstoolRecv, "EMEqpType:%d", m_tTvwUsed.m_emType );

	PostEvent(UI_UMSTOOL_MSG_TVWUSED_NTY);	
}




