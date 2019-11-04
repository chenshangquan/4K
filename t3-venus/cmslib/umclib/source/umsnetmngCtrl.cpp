// umsConfigCtrl.cpp: implementation of the CUmsConfigCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umsnetmngCtrl.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUmsNetMngCtrl::CUmsNetMngCtrl(CUmsSession &cUmsSession)
               :CUmsNetMngCtrlIF(),
			   m_pUmsSession(NULL),
			   m_vecTTPNMServerCfg()
{
	m_pUmsSession = &cUmsSession;
    BuildEventsMap();
}
CUmsNetMngCtrl::~CUmsNetMngCtrl()
{
}

void  CUmsNetMngCtrl::BuildEventsMap()
{
	REG_PFUN( ev_NMServerAdd_rsp, OnAddNetMngRsp );
	REG_PFUN( ev_NMServerDel_rsp, OnDelNetMngRsp );
	REG_PFUN( ev_NMServerMdy_rsp, OnModifyNetMngRsp );
	REG_PFUN( ev_NMServer_nty, OnNetMngNty );

    //断链清空资源
    REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
}



u16  CUmsNetMngCtrl::NetMngAddReq( const TTPNMServerCfg& tTPNMServerCfg )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_NMServerAdd_req );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
	PrtMsg( ev_NMServerAdd_req, emEventTypeUmstoolSend, 
		"NMServerIP: %s, NMReadCommunity: %s, NMWriteCommunity: %s, NMGetSetPort: %d, NMTrapPort: %d, NMServerNO: %d",
		inet_ntoa(tAddr), tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity,
		tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.wNMServerNO );
	return wRet;
}

u16  CUmsNetMngCtrl::NetMngModifyReq( const TTPNMServerCfg& tTPNMServerCfg )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_NMServerMdy_req );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
	PrtMsg( ev_NMServerMdy_req, emEventTypeUmstoolSend, 
		"NMServerIP: %s, NMReadCommunity: %s, NMWriteCommunity: %s, NMGetSetPort: %d, NMTrapPort: %d, NMServerNO: %d",
		inet_ntoa(tAddr), tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity,
		tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.wNMServerNO );
	return wRet;
}

u16  CUmsNetMngCtrl::NetMngDeleteReq( const TTPNMServerCfg& tTPNMServerCfg )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_NMServerDel_req );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
	PrtMsg( ev_NMServerDel_req, emEventTypeUmstoolSend, 
		"NMServerIP: %s, NMReadCommunity: %s, NMWriteCommunity: %s, NMGetSetPort: %d, NMTrapPort: %d, NMServerNO: %d",
		inet_ntoa(tAddr), tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity,
		tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.wNMServerNO );
	return wRet;
}

u16 CUmsNetMngCtrl::GetUmsNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )
{
	vecTTPNMServerCfg = m_vecTTPNMServerCfg;
	return NO_ERROR;
}


void  CUmsNetMngCtrl::OnAddNetMngRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() );

	if ( emRet == em_nmserver_modify_success )
	{
		TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() + sizeof(EmModifyNMServerRet) );
		m_vecTTPNMServerCfg.push_back(tTPNMServerCfg);
	}

	PrtMsg( ev_NMServerAdd_rsp, emEventTypeUmstoolRecv, "netmng add issuccess =%d", emRet );
	PostEvent( UI_UMSTOOL_ADD_NETMNG_RSP, (WPARAM)emRet );
}

void  CUmsNetMngCtrl::OnDelNetMngRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() );

	if ( emRet == em_nmserver_modify_success )
	{
		TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() + sizeof(EmModifyNMServerRet) );
		vector<TTPNMServerCfg>::iterator it;
		for ( it = m_vecTTPNMServerCfg.begin(); it != m_vecTTPNMServerCfg.end(); )
		{
			if ( tTPNMServerCfg.wNMServerNO == it->wNMServerNO )
			{
				it = m_vecTTPNMServerCfg.erase(it);
				break;
			}
			it++;
		}
	}

	PrtMsg( ev_NMServerDel_rsp, emEventTypeUmstoolRecv, "netmng del issuccess =%d", emRet );    
	PostEvent( UI_UMSTOOL_DEL_NETMNG_RSP, (WPARAM)emRet );
}

void  CUmsNetMngCtrl::OnModifyNetMngRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() );

	if ( emRet == em_nmserver_modify_success )
	{
		TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() + sizeof(EmModifyNMServerRet) );
		vector<TTPNMServerCfg>::iterator it;
		for ( it = m_vecTTPNMServerCfg.begin(); it != m_vecTTPNMServerCfg.end(); it++ )
		{
			if ( tTPNMServerCfg.wNMServerNO == it->wNMServerNO )
			{
				*it = tTPNMServerCfg;
				break;
			}
		}
	}

	PrtMsg( ev_NMServerMdy_rsp, emEventTypeUmstoolRecv, "netmng mdy issuccess =%d", emRet );
	PostEvent( UI_UMSTOOL_MODIFY_NETMNG_RSP, (WPARAM)emRet );
}

void  CUmsNetMngCtrl::OnNetMngNty(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	u16 wNum = *reinterpret_cast<u16*>( kdvMsg.GetBody() );

	m_vecTTPNMServerCfg.clear();

	for ( int n = 0; n < wNum; n++ )
	{
		TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() + sizeof(u16) + n*sizeof(TTPNMServerCfg) );
		m_vecTTPNMServerCfg.push_back( tTPNMServerCfg );
	}
	

	PrtMsg( ev_NMServer_nty, emEventTypeUmstoolRecv, _T("ev_NMServer_nty") );
	PostEvent( UI_UMSTOOL_NETMNG_NTY, NULL, NULL );
}

void CUmsNetMngCtrl::OnLinkBreak( const CMessage& cMsg )
{
	m_vecTTPNMServerCfg.clear();
    
    PrtMsg( OSP_DISCONNECT,emEventTypeUmstoolRecv,"清空net mng注册信息");
}

void CUmsNetMngCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
    PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
}

void CUmsNetMngCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CUmsNetMngCtrl,cMsg);
}
