// cncnetmngctrl.cpp: implementation of the CUmsConfigCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cncnetmngctrl.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCncNetMngCtrl::CCncNetMngCtrl(CCnsSession &cSession)
               :CCncNetMngCtrlIF(),
			   m_pSession(NULL),
			   m_vecTTPNMServerCfg()
{
	m_pSession = &cSession;
    BuildEventsMap();
}
CCncNetMngCtrl::~CCncNetMngCtrl()
{
}

void  CCncNetMngCtrl::BuildEventsMap()
{
 	REG_PFUN( ev_tppCnAgtAddNMServer_Ind, CCncNetMngCtrl::OnAddNetMngInd );
 	REG_PFUN( ev_tppCnAgtDelNMServer_Ind, CCncNetMngCtrl::OnDelNetMngInd );
 	REG_PFUN( ev_tppCnAgtModifyNMServer_Ind, CCncNetMngCtrl::OnModifyNetMngInd );
 	REG_PFUN( ev_tppCurAgtNMServerInfo_Nty, CCncNetMngCtrl::OnNetMngNty );

    //断链清空资源
    REG_PFUN(OSP_DISCONNECT, CCncNetMngCtrl::OnLinkBreak); 
}



u16  CCncNetMngCtrl::NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if ( NULL == m_pSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnAgtAddNMServerCmd );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
	PrtMsg( ev_CnAgtAddNMServerCmd, emEventTypeCnsSend, 
		"NMServerIP: %s, NMReadCommunity: %s, NMWriteCommunity: %s, NMGetSetPort: %d, NMTrapPort: %d, NMServerNO: %d",
		inet_ntoa(tAddr), tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity,
		tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.wNMServerNO );
	return wRet;
}

u16  CCncNetMngCtrl::NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if ( NULL == m_pSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnAgtModifyNMServerCmd );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
	PrtMsg( ev_CnAgtModifyNMServerCmd, emEventTypeCnsSend, 
		"NMServerIP: %s, NMReadCommunity: %s, NMWriteCommunity: %s, NMGetSetPort: %d, NMTrapPort: %d, NMServerNO: %d",
		inet_ntoa(tAddr), tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity,
		tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.wNMServerNO );
	return wRet;
}

u16  CCncNetMngCtrl::NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if ( NULL == m_pSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnAgtDelNMServerCmd );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
	PrtMsg( ev_CnAgtDelNMServerCmd, emEventTypeCnsSend, 
		"NMServerIP: %s, NMReadCommunity: %s, NMWriteCommunity: %s, NMGetSetPort: %d, NMTrapPort: %d, NMServerNO: %d",
		inet_ntoa(tAddr), tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity,
		tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.wNMServerNO );
	return wRet;
}

void CCncNetMngCtrl::GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )const
{
	vecTTPNMServerCfg = m_vecTTPNMServerCfg;
	return;
}


void  CCncNetMngCtrl::OnAddNetMngInd(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );

	TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() + sizeof(TTPNMServerCfg) );

	if ( emRet == em_nmserver_modify_success )
	{
		if ( 0 == tTPNMServerCfg.wNMServerNO )		
		{
			m_vecTTPNMServerCfg.insert( m_vecTTPNMServerCfg.begin(), tTPNMServerCfg );
		}
		else
		{
			m_vecTTPNMServerCfg.push_back(tTPNMServerCfg);
		}
	}

 	PrtMsg( ev_tppCnAgtAddNMServer_Ind, emEventTypeCnsRecv, "netmng add issuccess =%d", emRet );
	PostEvent( UI_CNSTOOL_ADD_NETMNG_IND, (WPARAM)emRet );
}

void  CCncNetMngCtrl::OnDelNetMngInd(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );

	TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() + sizeof(TTPNMServerCfg) );

	if ( emRet == em_nmserver_modify_success )
	{
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

	PrtMsg( ev_tppCnAgtDelNMServer_Ind, emEventTypeCnsRecv, "netmng del issuccess =%d", emRet );    
	PostEvent( UI_CNSTOOL_DEL_NETMNG_IND, (WPARAM)emRet );
}

void  CCncNetMngCtrl::OnModifyNetMngInd(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );

	TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() + sizeof(TTPNMServerCfg) );

	if ( emRet == em_nmserver_modify_success )
	{
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

	PrtMsg( ev_tppCnAgtModifyNMServer_Ind, emEventTypeCnsRecv, "netmng mdy issuccess =%d", emRet );
	PostEvent( UI_CNSTOOL_MODIFY_NETMNG_IND, (WPARAM)emRet );
}

void  CCncNetMngCtrl::OnNetMngNty(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );

	TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() );
	m_vecTTPNMServerCfg.push_back( tTPNMServerCfg );

	in_addr tAddr;
	tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
	PrtMsg( ev_tppCurAgtNMServerInfo_Nty, emEventTypeCnsRecv, "NMServerIP: %s, NMReadCommunity: %s, NMWriteCommunity: %s, NMGetSetPort: %d, NMTrapPort: %d, NMServerNO: %d",
		inet_ntoa(tAddr), tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity,
		tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.wNMServerNO );
	PostEvent( UI_CNSTOOL_NETMNG_NTY, (WPARAM)&tTPNMServerCfg );
}

void CCncNetMngCtrl::OnLinkBreak( const CMessage& cMsg )
{
	m_vecTTPNMServerCfg.clear();
    
    PrtMsg( OSP_DISCONNECT,emEventTypeCnsRecv,"清空net mng注册信息");
}

void CCncNetMngCtrl::OnTimeOut(u16 wEvent)
{
}

void CCncNetMngCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CCncNetMngCtrl,cMsg);
}
