// umsTvwBoardCtrl.cpp: implementation of the CUmsTvwBoardCtrl class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umsTvwBoardCtrl.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUmsTvwBoardCtrl::CUmsTvwBoardCtrl( CUmsSession &cUmsSession)
          :CUmsTvwBoardCtrlIF(),
		  m_pUmsSession(NULL)                                       
{
    m_pUmsSession = &cUmsSession;
    BuildEventsMap();

	ResetMapTHduCfgData();
} 

CUmsTvwBoardCtrl::~CUmsTvwBoardCtrl()
{

}

void  CUmsTvwBoardCtrl::BuildEventsMap()
{  
   REG_PFUN(ev_hduInfo_Nty,OnRefreshTvwBoardNotify);
   REG_PFUN(ev_hduBrdAdd_rsp,OnTvwBoardAddNotify);
   REG_PFUN(ev_hduBrdModify_rsp,OnTvwBoardModifyNotify);
   REG_PFUN(ev_hduDel_rsp,OnTvwBoardDeleteNotify);
   REG_PFUN(ev_hduChanAdd_rsp,OnTvwBoardModeAddNotify);
   REG_PFUN(ev_hduChanModify_rsp,OnTvwBoardModeModifyNotify);
   REG_PFUN(ev_hduChanDel_rsp,OnTvwBoardModeDeleteNotify);

   REG_PFUN(ev_hduStyle_Nty,OnTvwStyleNotify);
   REG_PFUN(ev_hduStyle_Add_Rsp,OnAddTvwStyleRsp);
//   REG_PFUN(ev_hduStyle_Del_Rsp,OnTvwStyleDeleteRsp);

   REG_PFUN(ev_hduReboot_rsp,OnRebootTvwBoardRsp);
   REG_PFUN(ev_hduUpdate_rsp,OnTvwBoardUpgradeRsp);
   REG_PFUN(ev_hduStyle_update_Rsp,OnUpdateTvwStyleRsp);
   
   
   //断链清空资源
   REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
}

void  CUmsTvwBoardCtrl::OnLinkBreak(const CMessage& cMsg)
{
    PrtMsg( OSP_DISCONNECT,emEventTypeUmsRecv,"清空单板信息"); 

	ResetMapTHduCfgData();
}

void CUmsTvwBoardCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CUmsTvwBoardCtrl,cMsg);
}

void CUmsTvwBoardCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
   PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
} 

u16  CUmsTvwBoardCtrl::GetUmsTvwStyleData( THduStyleData& tHduStyleData ) const
{
	tHduStyleData = m_tHduStyleData;

	return NO_ERROR;
}

u16  CUmsTvwBoardCtrl::GetUmsTvwBoardData( std::multimap<u8,THduCfg>& mulmapTHduCfg ) const
{
	mulmapTHduCfg = m_mulmapTHduCfg;

	return NO_ERROR;
}

u16  CUmsTvwBoardCtrl::TvwBoardDeleteReq( const TTPBrdPos& tTPBrdPos )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_hduDel_req);
	pkdvMsg->SetBody( &tTPBrdPos, sizeof(TTPBrdPos) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_hduDel_req, emEventTypeUmstoolSend, "发送电视墙单板删除请求" );
	
    return NO_ERROR;
}

u16  CUmsTvwBoardCtrl::TvwBoardAddReq( const TTPBrdPos& tTPBrdPos )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_hduBrdAdd_req);
	pkdvMsg->SetBody( &tTPBrdPos, sizeof(TTPBrdPos) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_hduBrdAdd_req, emEventTypeUmstoolSend, "发送电视墙单板添加请求" );
	
    return NO_ERROR;
}

u16  CUmsTvwBoardCtrl::TvwBoardModifyReq( const TTPBrdPos& tTPBrdPos )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_hduBrdModify_req);
	pkdvMsg->SetBody( &tTPBrdPos, sizeof(TTPBrdPos) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_hduBrdModify_req, emEventTypeUmstoolSend, "发送电视墙单板修改请求, u32 = %d", tTPBrdPos.m_dwBrdIP );
	
    return NO_ERROR;
}

u16  CUmsTvwBoardCtrl::TvwBoardModeAddReq( const THduInfo& tTHduInfo )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_hduChanAdd_req);
	pkdvMsg->SetBody( &tTHduInfo, sizeof(THduInfo) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_hduChanAdd_req, emEventTypeUmstoolSend, "发送电视墙单板模式添加请求" );
	
    return NO_ERROR;
}

u16  CUmsTvwBoardCtrl::TvwBoardModeModifyReq( const THduInfo& tTHduInfo )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_hduChanModify_req);
	pkdvMsg->SetBody( &tTHduInfo, sizeof(THduInfo) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_hduChanModify_req, emEventTypeUmstoolSend, "发送电视墙单板模式修改请求" );
	
    return NO_ERROR;
}

u16  CUmsTvwBoardCtrl::TvwBoardModeDeleteReq( const TTPBrdPos& tTPBrdPos )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_hduChanDel_req);
	pkdvMsg->SetBody( &tTPBrdPos, sizeof(TTPBrdPos) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_hduChanDel_req, emEventTypeUmstoolSend, "发送电视墙单板模式删除请求" );
	
    return NO_ERROR;
}

u16  CUmsTvwBoardCtrl::TvwBoardRebootReq( const TTPBrdPos& tTPbrdPos )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_hduReboot_req);
	pkdvMsg->SetBody( &tTPbrdPos, sizeof(TTPBrdPos) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_hduReboot_req, emEventTypeUmstoolSend, "发送电视墙单板重启请求" );

    return NO_ERROR;
}

u16  CUmsTvwBoardCtrl::TvwBoardUpgradeReq( const TTPBrdUpGrade& tBrdUpGrade )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_hduUpdate_req);
	pkdvMsg->SetBody( &tBrdUpGrade, sizeof(TTPBrdUpGrade) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_hduUpdate_req, emEventTypeUmstoolSend, "发送电视墙板子升级请求 Layer Num = %d, Slot = %d, szFileName=%s",
		tBrdUpGrade.m_byLayer, tBrdUpGrade.m_bySlot, tBrdUpGrade.m_szFileName );
	
    return NO_ERROR;
}

u16  CUmsTvwBoardCtrl::AddTvwStyleReq( const THduStyleData& tHduStyleData )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_hduStyle_Add);
	pkdvMsg->SetBody( &tHduStyleData, sizeof(THduStyleData) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_hduStyle_Add, emEventTypeUmstoolSend, "发送添加电视墙风格请求" );
	
	return NO_ERROR;
}

// u16  CUmsTvwBoardCtrl::TvwStyleDeleteReq()
// {
// 	if ( NULL == m_pUmsSession ) 
// 	{
// 		return ERR_CMS;
// 	}
//     
// 	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
//     pkdvMsg->SetEvent(ev_hduStyle_Del_Req);
//     u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
// 	PrtMsg( ev_hduStyle_Del_Req, emEventTypeUmstoolSend, "发送删除电视墙预案请求" );
// 	
// 	return NO_ERROR;
// }

void  CUmsTvwBoardCtrl::OnRefreshTvwBoardNotify(const CMessage& cMsg)
{   
	CTpMsg kdvMsg( &cMsg );
    THduCfg tNewHduCfg = *reinterpret_cast<THduCfg*>( kdvMsg.GetBody() );
	s32 nNewLayer = tNewHduCfg.m_byLayer;
	s32 nNewSlot = tNewHduCfg.m_bySlot;
	for ( std::multimap<u8,THduCfg>::iterator iter = m_mulmapTHduCfg.begin(); iter != m_mulmapTHduCfg.end(); iter++ )
	{
		s32 nLayer = (*iter).first;
 		THduCfg tHduCfg = (*iter).second;
		s32 nSlot = tHduCfg.m_bySlot;
		if( nLayer == nNewLayer && nSlot == nNewSlot )
		{
			(*iter).second = tNewHduCfg;
			break;
		}
	}

	in_addr tAddr;
	tAddr.S_un.S_addr = tNewHduCfg.m_dwIP;

	PrtMsg( ev_hduInfo_Nty, emEventTypeUmstoolRecv, "TvwLayerNo=%d, TvwSlotNo=%d, IP = %s, u32 = %d", tNewHduCfg.m_byLayer, tNewHduCfg.m_bySlot, inet_ntoa(tAddr),
		tNewHduCfg.m_dwIP);

	PostEvent(UI_UMSTOOL_MSG_REFRESHTVWBOARD_NTY );
}

void  CUmsTvwBoardCtrl::OnTvwBoardAddNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>( kdvMsg.GetBody() );
    m_tTPAddBrdPos = *reinterpret_cast<TTPBrdPos*>( sizeof(EmModifyHduRet) + kdvMsg.GetBody() );
	
	if ( em_hdu_modify_success != emRet )
	{
		PrtMsg( ev_hduBrdAdd_rsp, emEventTypeUmstoolRecv, "tvwboard add error code=%d", emRet );

		TTvwBrdOptRet tOptRet;
		tOptRet.emBrdOptType = em_Add_Ret;
		tOptRet.emTvwModifyHduRet = emRet;

		PostEvent(UI_UMSTOOL_MSG_OPTTVWBOARD_RSP, (WPARAM)&m_tTPAddBrdPos,(LPARAM)&tOptRet );	
	}
	else
	{
		s32 nNewLayer = m_tTPAddBrdPos.m_byBrdLayer;
		s32 nNewSlot = m_tTPAddBrdPos.m_byBrdSlot;			
		u32_ip dwIP = m_tTPAddBrdPos.m_dwBrdIP;

		for ( std::multimap<u8,THduCfg>::iterator iter = m_mulmapTHduCfg.begin(); iter != m_mulmapTHduCfg.end(); iter++ )
		{
			s32 nLayer = (*iter).first;
			THduCfg tHduCfg = (*iter).second;
			s32 nSlot = tHduCfg.m_bySlot;
			if( nLayer == nNewLayer && nSlot == nNewSlot )
			{
				tHduCfg.Clear();
				tHduCfg.m_byLayer = nNewLayer;
				tHduCfg.m_bySlot = nNewSlot;
				tHduCfg.m_dwIP = dwIP;
				(*iter).second = tHduCfg;
				break;
			}
		}

		in_addr tAddr;
		tAddr.S_un.S_addr = dwIP;

		PrtMsg( ev_hduBrdAdd_rsp, emEventTypeUmstoolRecv, "tvwboard mode add success byLayerid=%d bySlotid=%d, IP = %s, u32 = %d", 
			m_tTPAddBrdPos.m_byBrdLayer, m_tTPAddBrdPos.m_byBrdSlot, inet_ntoa(tAddr), dwIP );
		PostEvent(UI_UMSTOOL_MSG_OPTTVWBOARD_NTY, (WPARAM)&m_tTPAddBrdPos );	
	}
}

void  CUmsTvwBoardCtrl::OnTvwBoardModifyNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>( kdvMsg.GetBody() );
    m_tTPModifyBrdPos = *reinterpret_cast<TTPBrdPos*>( sizeof(EmModifyHduRet) + kdvMsg.GetBody() );
	
	if ( em_hdu_modify_success != emRet )
	{
		PrtMsg( ev_hduBrdModify_rsp, emEventTypeUmstoolRecv, "tvwboard modify error code=%d", emRet );

		TTvwBrdOptRet tOptRet;
		tOptRet.emBrdOptType = em_Modify_Ret;
		tOptRet.emTvwModifyHduRet = emRet;

		PostEvent(UI_UMSTOOL_MSG_OPTTVWBOARD_RSP, (WPARAM)&m_tTPModifyBrdPos,(LPARAM)&tOptRet );	
	}
	else
	{
		s32 nNewLayer = m_tTPModifyBrdPos.m_byBrdLayer;
		s32 nNewSlot = m_tTPModifyBrdPos.m_byBrdSlot;			
		u32_ip dwIP = m_tTPModifyBrdPos.m_dwBrdIP;
		
		for ( std::multimap<u8,THduCfg>::iterator iter = m_mulmapTHduCfg.begin(); iter != m_mulmapTHduCfg.end(); iter++ )
		{
			s32 nLayer = (*iter).first;
			THduCfg tHduCfg = (*iter).second;
			s32 nSlot = tHduCfg.m_bySlot;
			if( nLayer == nNewLayer && nSlot == nNewSlot )
			{
				tHduCfg.m_byLayer = nNewLayer;
				tHduCfg.m_bySlot = nNewSlot;
				tHduCfg.m_dwIP = dwIP;
				(*iter).second = tHduCfg;
				break;
			}
		}

		in_addr tAddr;
		tAddr.S_un.S_addr = dwIP;

		PrtMsg( ev_hduBrdModify_rsp, emEventTypeUmstoolRecv, "tvwboard mode modify success byLayerid=%d, bySlotid = %d, IP = %s, u32 = %d", 
			m_tTPModifyBrdPos.m_byBrdLayer, m_tTPModifyBrdPos.m_byBrdSlot, inet_ntoa(tAddr), dwIP );
		PostEvent(UI_UMSTOOL_MSG_OPTTVWBOARD_NTY, (WPARAM)&m_tTPModifyBrdPos );	
	}
}

void  CUmsTvwBoardCtrl::OnTvwBoardDeleteNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>( kdvMsg.GetBody() );
    m_tTPDelBrdPos = *reinterpret_cast<TTPBrdPos*>( sizeof(EmModifyHduRet) + kdvMsg.GetBody() );
	
	if ( em_hdu_modify_success != emRet )
	{
		PrtMsg( ev_hduDel_rsp, emEventTypeUmstoolRecv, "tvwboard opt error code=%d", emRet );

		TTvwBrdOptRet tOptRet;
		tOptRet.emBrdOptType = em_Del_Ret;
		tOptRet.emTvwModifyHduRet = emRet;

		PostEvent(UI_UMSTOOL_MSG_OPTTVWBOARD_RSP, (WPARAM)&m_tTPDelBrdPos,(LPARAM)&tOptRet );	
	}
	else
	{
		s32 nNewLayer = m_tTPDelBrdPos.m_byBrdLayer;
		s32 nNewSlot = m_tTPDelBrdPos.m_byBrdSlot;			
		u32_ip dwIP = m_tTPDelBrdPos.m_dwBrdIP;
		
		for ( std::multimap<u8,THduCfg>::iterator iter = m_mulmapTHduCfg.begin(); iter != m_mulmapTHduCfg.end(); iter++ )
		{
			s32 nLayer = (*iter).first;
			THduCfg tHduCfg = (*iter).second;
			s32 nSlot = tHduCfg.m_bySlot;
			if( nLayer == nNewLayer && nSlot == nNewSlot )
			{
				tHduCfg.Clear();
				tHduCfg.m_byLayer = nNewLayer;
				tHduCfg.m_bySlot = nNewSlot;
				tHduCfg.m_dwIP = dwIP;
				tHduCfg.m_tName.Clear();
				tHduCfg.m_atChanInfo->Clear();
				(*iter).second = tHduCfg;
				break;
			}
		}

		PrtMsg( ev_hduDel_rsp, emEventTypeUmstoolRecv, "tvwboard mode opt success byLayerid=%d bySlotid=%d", 
			m_tTPDelBrdPos.m_byBrdLayer, m_tTPDelBrdPos.m_byBrdSlot );
		PostEvent(UI_UMSTOOL_MSG_DELTVWBOARD_NTY, (WPARAM)&m_tTPDelBrdPos );	
	}
}

void  CUmsTvwBoardCtrl::OnTvwBoardModeAddNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>( kdvMsg.GetBody() );
    m_tAddTvwBrdMdlTHduInfo = *reinterpret_cast<THduInfo*>( sizeof(EmModifyHduRet) + kdvMsg.GetBody() );

	if ( em_hdu_modify_success != emRet )
	{
		PrtMsg( ev_hduChanAdd_rsp, emEventTypeUmstoolRecv, "tvwboard opt error code=%d", emRet );

		TTvwBrdOptRet tOptRet;
		tOptRet.emBrdOptType = em_Add_Ret;
		tOptRet.emTvwModifyHduRet = emRet;

		PostEvent(UI_UMSTOOL_MSG_OPTTVWBOARDMODE_RSP, (WPARAM)&m_tAddTvwBrdMdlTHduInfo,(LPARAM)&tOptRet );	
	}
	else
	{
		PrtMsg( ev_hduChanAdd_rsp, emEventTypeUmstoolRecv, "tvwboard mode opt success byLayerid=%d bySlotid=%d", 
			m_tAddTvwBrdMdlTHduInfo.m_byLayer, m_tAddTvwBrdMdlTHduInfo.m_bySlot );

		s32 nNewLayer = m_tAddTvwBrdMdlTHduInfo.m_byLayer;
		s32 nNewSlot = m_tAddTvwBrdMdlTHduInfo.m_bySlot;			
		
		for ( std::multimap<u8,THduCfg>::iterator iter = m_mulmapTHduCfg.begin(); iter != m_mulmapTHduCfg.end(); iter++ )
		{
			s32 nLayer = (*iter).first;
			THduCfg tHduCfg = (*iter).second;
			s32 nSlot = tHduCfg.m_bySlot;
			if( nLayer == nNewLayer && nSlot == nNewSlot )
			{
				tHduCfg.m_tName.SetAlias(m_tAddTvwBrdMdlTHduInfo.m_tName.m_abyAlias);
				//memcpy( tHduCfg.m_tName.m_abyAlias, m_tAddTvwBrdMdlTHduInfo.m_tName.m_abyAlias, TP_MAX_ALIAS_LEN );
				tHduCfg.m_atChanInfo[0].SetOutType(m_tAddTvwBrdMdlTHduInfo.m_atChanInfo[0].GetOutType());
				tHduCfg.m_atChanInfo[1].SetOutType(m_tAddTvwBrdMdlTHduInfo.m_atChanInfo[1].GetOutType());
				tHduCfg.m_atChanInfo[0].SetZoomRate(m_tAddTvwBrdMdlTHduInfo.m_atChanInfo[0].GetZoomRate());
				tHduCfg.m_atChanInfo[1].SetZoomRate(m_tAddTvwBrdMdlTHduInfo.m_atChanInfo[1].GetZoomRate());
				tHduCfg.m_atChanInfo[0].SetShowMode(m_tAddTvwBrdMdlTHduInfo.m_atChanInfo[0].GetShowMode());
				tHduCfg.m_atChanInfo[1].SetShowMode(m_tAddTvwBrdMdlTHduInfo.m_atChanInfo[1].GetShowMode());
				tHduCfg.m_atChanInfo[0].SetOutMode(m_tAddTvwBrdMdlTHduInfo.m_atChanInfo[0].GetOutMode());
				tHduCfg.m_atChanInfo[1].SetOutMode(m_tAddTvwBrdMdlTHduInfo.m_atChanInfo[1].GetOutMode());
				(*iter).second = tHduCfg;
				break;
			}
		}

		PostEvent(UI_UMSTOOL_MSG_OPTTVWBOARDMODE_NTY, (WPARAM)&m_tAddTvwBrdMdlTHduInfo );	
	}
}

void  CUmsTvwBoardCtrl::OnTvwBoardModeModifyNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>( kdvMsg.GetBody() );
    m_tModifyTvwBrdMdlTHduInfo = *reinterpret_cast<THduInfo*>( sizeof(EmModifyHduRet) + kdvMsg.GetBody() );
	
	if ( em_hdu_modify_success != emRet )
	{
		PrtMsg( ev_hduChanModify_rsp, emEventTypeUmstoolRecv, "tvwboard opt error code=%d", emRet );

		TTvwBrdOptRet tOptRet;
		tOptRet.emBrdOptType = em_Modify_Ret;
		tOptRet.emTvwModifyHduRet = emRet;

		PostEvent(UI_UMSTOOL_MSG_OPTTVWBOARDMODE_RSP, (WPARAM)&m_tModifyTvwBrdMdlTHduInfo,(LPARAM)&tOptRet );	
	}
	else
	{
		PrtMsg( ev_hduChanModify_rsp, emEventTypeUmstoolRecv, "tvwboard mode opt success byLayerid=%d bySlotid=%d", 
			m_tModifyTvwBrdMdlTHduInfo.m_byLayer, m_tModifyTvwBrdMdlTHduInfo.m_bySlot );

		s32 nNewLayer = m_tModifyTvwBrdMdlTHduInfo.m_byLayer;
		s32 nNewSlot = m_tModifyTvwBrdMdlTHduInfo.m_bySlot;			
		
		for ( std::multimap<u8,THduCfg>::iterator iter = m_mulmapTHduCfg.begin(); iter != m_mulmapTHduCfg.end(); iter++ )
		{
			s32 nLayer = (*iter).first;
			THduCfg tHduCfg = (*iter).second;
			s32 nSlot = tHduCfg.m_bySlot;
			if( nLayer == nNewLayer && nSlot == nNewSlot )
			{
				tHduCfg.m_tName.SetAlias(m_tModifyTvwBrdMdlTHduInfo.m_tName.m_abyAlias);
				//memcpy( tHduCfg.m_tName.m_abyAlias, m_tModifyTvwBrdMdlTHduInfo.m_tName.m_abyAlias, TP_MAX_ALIAS_LEN );
				tHduCfg.m_atChanInfo[0].SetOutType(m_tModifyTvwBrdMdlTHduInfo.m_atChanInfo[0].GetOutType());
				tHduCfg.m_atChanInfo[1].SetOutType(m_tModifyTvwBrdMdlTHduInfo.m_atChanInfo[1].GetOutType());
				tHduCfg.m_atChanInfo[0].SetZoomRate(m_tModifyTvwBrdMdlTHduInfo.m_atChanInfo[0].GetZoomRate());
				tHduCfg.m_atChanInfo[1].SetZoomRate(m_tModifyTvwBrdMdlTHduInfo.m_atChanInfo[1].GetZoomRate());
				tHduCfg.m_atChanInfo[0].SetShowMode(m_tModifyTvwBrdMdlTHduInfo.m_atChanInfo[0].GetShowMode());
				tHduCfg.m_atChanInfo[1].SetShowMode(m_tModifyTvwBrdMdlTHduInfo.m_atChanInfo[1].GetShowMode());
				tHduCfg.m_atChanInfo[0].SetOutMode(m_tModifyTvwBrdMdlTHduInfo.m_atChanInfo[0].GetOutMode());
				tHduCfg.m_atChanInfo[1].SetOutMode(m_tModifyTvwBrdMdlTHduInfo.m_atChanInfo[1].GetOutMode());
				(*iter).second = tHduCfg;

				//同步更新电视墙预案的单板模式名称
				UpdateUmsTvwStyleData();
				break;
			}
		}

		PostEvent(UI_UMSTOOL_MSG_OPTTVWBOARDMODE_NTY, (WPARAM)&m_tModifyTvwBrdMdlTHduInfo );	
	}
}

void  CUmsTvwBoardCtrl::OnTvwBoardModeDeleteNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>( kdvMsg.GetBody() );
    m_tDelTvwBrdMdlTPBrdPos = *reinterpret_cast<TTPBrdPos*>( sizeof(EmModifyHduRet) + kdvMsg.GetBody() );

	if ( em_hdu_modify_success != emRet )
	{
		PrtMsg( ev_hduChanDel_rsp, emEventTypeUmstoolRecv, "tvwboard opt error code=%d", emRet );

		TTvwBrdOptRet tOptRet;
		tOptRet.emBrdOptType = em_Del_Ret;
		tOptRet.emTvwModifyHduRet = emRet;

		PostEvent(UI_UMSTOOL_MSG_OPTTVWBOARDMODE_RSP, (WPARAM)&m_tDelTvwBrdMdlTPBrdPos,(LPARAM)&tOptRet );	
	}
	else
	{
		PrtMsg( ev_hduChanDel_rsp, emEventTypeUmstoolRecv, "tvwboard mode opt success byLayerid=%d bySlotid=%d", 
			m_tDelTvwBrdMdlTPBrdPos.m_byBrdLayer, m_tDelTvwBrdMdlTPBrdPos.m_byBrdSlot );

		s32 nNewLayer = m_tDelTvwBrdMdlTPBrdPos.m_byBrdLayer;
		s32 nNewSlot = m_tDelTvwBrdMdlTPBrdPos.m_byBrdSlot;			
		
		for ( std::multimap<u8,THduCfg>::iterator iter = m_mulmapTHduCfg.begin(); iter != m_mulmapTHduCfg.end(); iter++ )
		{
			s32 nLayer = (*iter).first;
			THduCfg tHduCfg = (*iter).second;
			s32 nSlot = tHduCfg.m_bySlot;
			if( nLayer == nNewLayer && nSlot == nNewSlot )
			{
				tHduCfg.m_tName.SetAlias("");
				tHduCfg.m_atChanInfo[0].Clear();
				tHduCfg.m_atChanInfo[1].Clear();
				(*iter).second = tHduCfg;
				break;
			}
		}

		PostEvent(UI_UMSTOOL_MSG_DELTVWBOARDMODE_NTY, (WPARAM)&m_tDelTvwBrdMdlTPBrdPos );	
	}
}


void  CUmsTvwBoardCtrl::OnTvwStyleNotify(const CMessage& cMsg)
{
    CTpMsg kdvMsg( &cMsg );
    THduStyleData tHduStyleData = *reinterpret_cast<THduStyleData*>( kdvMsg.GetBody() );

	m_tHduStyleData = tHduStyleData;
    
    PrtMsg( ev_hduStyle_Nty, emEventTypeUmsRecv, "THduStyleData: row:%d, col:%d", tHduStyleData.m_byRow, tHduStyleData.m_byCol );
    
    PostEvent( UI_UMS_HDUSTYLE_NOTIFY, (WPARAM)&tHduStyleData );
}

void CUmsTvwBoardCtrl::OnAddTvwStyleRsp(const CMessage& cMsg)
{
    CTpMsg kdvMsg( &cMsg );
    EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>( kdvMsg.GetBody() );
	
	PrtMsg( ev_hduStyle_Add_Rsp, emEventTypeUmsRecv, "tvwboard style add error code=%d", emRet );
	
    m_tHduStyleData = *reinterpret_cast<THduStyleData*>( sizeof(EmModifyHduRet) + kdvMsg.GetBody() );
	if ( em_hdu_modify_success == emRet )
	{
		PostEvent( UI_UMS_HDUSTYLE_NOTIFY, (WPARAM)&m_tHduStyleData );
	}
	else
	{
		PostEvent( UI_UMS_HDUSTYLE_RSP, (WPARAM)&emRet );
	}
}

// void CUmsTvwBoardCtrl::OnTvwStyleDeleteRsp(const CMessage& cMsg)
// {
//     CTpMsg kdvMsg( &cMsg );
//     EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>( kdvMsg.GetBody() );
// 	
// 	PrtMsg( ev_hduStyle_Del_Rsp, emEventTypeUmsRecv, "tvwboard style delete error code=%d", emRet );
// 	
//     m_tHduStyleData = *reinterpret_cast<THduStyleData*>( sizeof(EmModifyHduRet) + kdvMsg.GetBody() );
// 
// 	PostEvent( UI_UMS_HDUSTYLE_DEL_RSP, (WPARAM)&emRet );
// }

void CUmsTvwBoardCtrl::OnRebootTvwBoardRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>( kdvMsg.GetBody() );
    m_tRebootTPBrdPos = *reinterpret_cast<TTPBrdPos*>( sizeof(EmModifyHduRet) + kdvMsg.GetBody() );

	PostEvent(UI_UMSTOOL_MSG_REBOOTTVWBOARD_RSP, (WPARAM)&m_tRebootTPBrdPos,(LPARAM)&emRet );	

}

void  CUmsTvwBoardCtrl::OnTvwBoardUpgradeRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
    EmUpdateHduRet emRet = *reinterpret_cast<EmUpdateHduRet*>( sizeof(TTPBrdUpGrade) + kdvMsg.GetBody() );
	PostEvent(UI_UMSTOOL_MSG_TVWBOARDUPGRADE_RSP, (WPARAM)emRet );	

	PrtMsg( ev_hduUpdate_rsp, emEventTypeUmsRecv, "tvwboard update result error code=%d", emRet );
}

void CUmsTvwBoardCtrl::ResetMapTHduCfgData()
{
	m_mulmapTHduCfg.clear();
	for ( s32 nXIndex = 0; nXIndex < 10; nXIndex++ )
	{
		s32 nLayer = nXIndex;
		for ( s32 nYIndex = 0; nYIndex < 7; nYIndex++ )
		{
			THduCfg tHduCfg;
			tHduCfg.m_byLayer = nXIndex;
			tHduCfg.m_bySlot = nYIndex;
			tHduCfg.m_dwIP = 0;
			m_mulmapTHduCfg.insert(std::make_pair<u8,THduCfg>( nLayer, tHduCfg) );
		}
	}
}

void CUmsTvwBoardCtrl::UpdateUmsTvwStyleData()
{
	bool bUpdate = false;

	THduStyleData tHduStyleData = m_tHduStyleData;
	for ( s32 nIndex = 0; nIndex < tHduStyleData.m_byRow * tHduStyleData.m_byCol; nIndex++ )
	{
		if( m_tModifyTvwBrdMdlTHduInfo.m_byLayer == tHduStyleData.m_atUnits[nIndex].m_byLayer && 
			m_tModifyTvwBrdMdlTHduInfo.m_bySlot == tHduStyleData.m_atUnits[nIndex].m_bySlot )
		{
			bUpdate = true;

			tHduStyleData.m_atUnits[nIndex].m_tName.Clear();
			tHduStyleData.m_atUnits[nIndex].m_tName.SetAlias(m_tModifyTvwBrdMdlTHduInfo.m_tName.m_abyAlias);		
		}
	}

	if ( bUpdate )
	{
		//AddTvwStyleReq(tHduStyleData);

		if ( NULL == m_pUmsSession ) 
		{
			return;
		}
		
		CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
		pkdvMsg->SetEvent(ev_hduStyle_update_Req);
		pkdvMsg->SetBody( &tHduStyleData, sizeof(THduStyleData) );
		u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
    	PrtMsg( ev_hduStyle_update_Req, emEventTypeUmstoolSend, "发送更新电视墙预案请求" );
	}
}

void CUmsTvwBoardCtrl::OnUpdateTvwStyleRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
    EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>( kdvMsg.GetBody() );
	
	PrtMsg( ev_hduStyle_update_Rsp, emEventTypeUmsRecv, "tvwboard style update error code=%d", emRet );
	
    m_tHduStyleData = *reinterpret_cast<THduStyleData*>( sizeof(EmModifyHduRet) + kdvMsg.GetBody() );
	if ( em_hdu_modify_success == emRet )
	{
		PostEvent( UI_UMS_HDUSTYLE_NOTIFY, (WPARAM)&m_tHduStyleData );
	}
	else
	{
		PostEvent( UI_UMS_HDUSTYLE_UPDATE_RSP, (WPARAM)&emRet );
	}
}
