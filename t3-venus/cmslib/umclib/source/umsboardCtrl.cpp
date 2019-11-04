// umsboardCtrl.cpp: implementation of the CUmsBoardCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umsboardCtrl.h"
#include "eventoutumslogin.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUmsBoardCtrl::CUmsBoardCtrl( CUmsSession &cUmsSession)
          :CUmsBoardCtrlIF(),
		  m_pUmsSession(NULL)                                       
{
   m_pUmsSession = &cUmsSession;
   BuildEventsMap();
} 

CUmsBoardCtrl::~CUmsBoardCtrl()
{

}

void  CUmsBoardCtrl::BuildEventsMap()
{  
   REG_PFUN(ev_cardInfo_Nty,OnRefreshboardNotify);
   REG_PFUN(ev_cardModify_rsp,OnBoardModifyNotify);
   REG_PFUN(ev_cardDel_rsp,OnBoardDeleteNotify);
   REG_PFUN(ev_cardAdd_rsp,OnBoardAddNotify);
// REG_PFUN(ev_cardModeAdd_rsp,OnBoardModeAddNotify);
   REG_PFUN(ev_cardModeModify_rsp,OnBoardModeModifyNotify);
   REG_PFUN(ev_cardModeDel_rsp,OnBoardModeDeleteNotify);
   REG_PFUN(ev_card_used_nty,OnBoardUsedNotify);
   REG_PFUN(ev_card_upgrade_res,OnBoardUpgradeRsp);
   
   //断链清空资源
   REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
}

void  CUmsBoardCtrl::OnLinkBreak(const CMessage& cMsg)
{
    PrtMsg( OSP_DISCONNECT,emEventTypeUmsRecv,"清空单板信息"); 
}

void CUmsBoardCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CUmsBoardCtrl,cMsg);
}

void CUmsBoardCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
   PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
} 

u16  CUmsBoardCtrl::GetUmsBoardUsedData( TTPBrdUsedInfo& tBoardUsed) const
{
	tBoardUsed = m_tBoardUsed;

	return NO_ERROR;
}
 
u16  CUmsBoardCtrl::BoardModifyReq( const TTPBrdCfg& tTPbrdCfg )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_cardModify_req);
	pkdvMsg->SetBody( &tTPbrdCfg, sizeof(TTPBrdCfg) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_cardModify_req, emEventTypeUmstoolSend, "发送单板修改请求" );
	
    return NO_ERROR;
}

u16  CUmsBoardCtrl::BoardDeleteReq( const TTPBrdCfg& tTPbrdCfg )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_cardDel_req);
	pkdvMsg->SetBody( &tTPbrdCfg, sizeof(TTPBrdCfg) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_cardDel_req, emEventTypeUmstoolSend, "发送单板删除请求" );
	
    return NO_ERROR;
}

u16  CUmsBoardCtrl::BoardAddReq( const TTPBrdCfg& tTPbrdCfg )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_cardAdd_req);
	pkdvMsg->SetBody( &tTPbrdCfg, sizeof(TTPBrdCfg) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );

	in_addr tIP;
	tIP.S_un.S_addr = tTPbrdCfg.m_tBrdPos.m_dwBrdIP; 

	PrtMsg( ev_cardAdd_req, emEventTypeUmstoolSend, "发送单板添加请求 Layer Num = %d, Slot = %d, IP = %s",
		tTPbrdCfg.m_tBrdPos.m_byBrdLayer, tTPbrdCfg.m_tBrdPos.m_byBrdSlot, inet_ntoa(tIP) );
	
    return NO_ERROR;
}

// u16  CUmsBoardCtrl::BoardModeAddReq( const TTPBrdMdlInfo& tTPbrdMdlInfo )  
// {
// 	if ( NULL == m_pUmsSession ) 
// 	{
// 		return ERR_CMS;
// 	}
//     
// 	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
//     pkdvMsg->SetEvent(ev_cardModeAdd_req);
// 	pkdvMsg->SetBody( &tTPbrdMdlInfo, sizeof(TTPBrdMdlInfo) );
//     u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
// 	PrtMsg( ev_cardModeAdd_req, emEventTypeUmstoolSend, "发送单板模式添加请求" );
// 	
//     return NO_ERROR;
// }

u16  CUmsBoardCtrl::BoardModeModifyReq( const TTPBrdMdlInfo& tTPbrdMdlInfo )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_cardModeModify_req);
	pkdvMsg->SetBody( &tTPbrdMdlInfo, sizeof(TTPBrdMdlInfo) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_cardModeModify_req, emEventTypeUmstoolSend, "发送单板模式修改请求" );
	
    return NO_ERROR;
}

u16  CUmsBoardCtrl::BoardModeDeleteReq( const TTPBrdMdlInfo& tTPbrdMdlInfo )  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_cardModeDel_req);
	pkdvMsg->SetBody( &tTPbrdMdlInfo, sizeof(TTPBrdMdlInfo) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_cardModeDel_req, emEventTypeUmstoolSend, "发送单板模式删除请求" );
	
    return NO_ERROR;
}

u16  CUmsBoardCtrl::BoardRebootReq( const TTPBrdPos& tTPbrdPos )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_card_reboot_req);
	pkdvMsg->SetBody( &tTPbrdPos, sizeof(TTPBrdPos) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_card_reboot_req, emEventTypeUmstoolSend, "发送单板重启请求" );

    return NO_ERROR;
}

// u16  CUmsBoardCtrl::BoardUpgradeReq( const TTPBrdPos& tTPbrdPos )
// {
// 	if ( NULL == m_pUmsSession ) 
// 	{
// 		return ERR_CMS;
// 	}
//     
// 	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
//     pkdvMsg->SetEvent(ev_card_reboot_req);
// 	pkdvMsg->SetBody( &tTPbrdPos, sizeof(TTPBrdPos) );
//     u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
// 	PrtMsg( ev_card_reboot_req, emEventTypeUmstoolSend, "发送单板重启请求" );
// 	
//     return NO_ERROR;
// }

u16  CUmsBoardCtrl::BoardAudiomixReq()
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_card_audiomix_used_req);
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_card_audiomix_used_req, emEventTypeUmstoolSend, "发送混音器占用请求" );
	
    return NO_ERROR;
}

u16  CUmsBoardCtrl::BoardVmpReq()
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_card_vmp_used_req);
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_card_vmp_used_req, emEventTypeUmstoolSend, "发送画面合成占用请求" );
	
    return NO_ERROR;
}

u16  CUmsBoardCtrl::BoardBasStreamReq()
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_card_bas_used_req);
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_card_bas_used_req, emEventTypeUmstoolSend, "发送码流适配占用请求" );
	
    return NO_ERROR;
}

u16  CUmsBoardCtrl::BoardUpgradeReq( const TTPBrdUpGrade& tBrdUpGrade )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_card_upgrade_req);
	pkdvMsg->SetBody( &tBrdUpGrade, sizeof(TTPBrdUpGrade) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_card_upgrade_req, emEventTypeUmstoolSend, "发送板子升级请求 Layer Num = %d, Slot = %d, FileName = %s",
		tBrdUpGrade.m_byLayer, tBrdUpGrade.m_bySlot, tBrdUpGrade.m_szFileName );
	
    return NO_ERROR;
}

void  CUmsBoardCtrl::OnRefreshboardNotify(const CMessage& cMsg)
{   
	CTpMsg kdvMsg( &cMsg );
    m_tTPBrdInfo = *reinterpret_cast<TTPBrdInfo*>( kdvMsg.GetBody() );

	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPBrdInfo.m_tBrdCfg.m_tBrdPos.m_dwBrdIP;
	PrtMsg( ev_cardInfo_Nty, emEventTypeUmstoolRecv, "BrdID = %d, IsReg = %d, IP = %s", m_tTPBrdInfo.m_tBrdCfg.m_byBrdID,  m_tTPBrdInfo.m_bReg, inet_ntoa(tAddr) );
	
	PostEvent(UI_UMSTOOL_MSG_REFRESHBOARD_NTY, (WPARAM)&m_tTPBrdInfo );
}

void  CUmsBoardCtrl::OnBoardModifyNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
    m_tTPBrdCfgModify = *reinterpret_cast<TTPBrdCfg*>( kdvMsg.GetBody() );

	EmTpBoardRet emRet = *reinterpret_cast<EmTpBoardRet*>( sizeof(TTPBrdCfg) + kdvMsg.GetBody() );

	if ( emTP_Board_ModifySuccess != emRet )
	{
		PrtMsg( ev_cardModify_rsp, emEventTypeUmstoolRecv, "board modify error code=%d", emRet );

		TBrdOptRet tTvwOptRet;
		tTvwOptRet.emBrdOptType = em_Modify_Ret;
		tTvwOptRet.emTpBoardRet = emRet;
		PostEvent(UI_UMSTOOL_MSG_OPTBOARD_RSP, (WPARAM)&m_tTPBrdCfgModify,(LPARAM)&tTvwOptRet );	
	}
	else
	{
		PrtMsg( ev_cardModify_rsp, emEventTypeUmstoolRecv, "board modify success brdid=%d", m_tTPBrdCfgModify.m_byBrdID );
		PostEvent(UI_UMSTOOL_MSG_OPTBOARD_NTY, (WPARAM)&m_tTPBrdCfgModify );	
	}
}

void  CUmsBoardCtrl::OnBoardDeleteNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
    m_tTPBrdCfgDelete = *reinterpret_cast<TTPBrdCfg*>( kdvMsg.GetBody() );
	
	EmTpBoardRet emRet = *reinterpret_cast<EmTpBoardRet*>( sizeof(TTPBrdCfg) + kdvMsg.GetBody() );
	
	if ( emTP_Board_DelSuccess != emRet )
	{
		PrtMsg( ev_cardDel_rsp, emEventTypeUmstoolRecv, "board delete error code=%d", emRet );

		TBrdOptRet tTvwOptRet;
		tTvwOptRet.emBrdOptType = em_Del_Ret;
		tTvwOptRet.emTpBoardRet = emRet;
		PostEvent(UI_UMSTOOL_MSG_OPTBOARD_RSP, (WPARAM)&m_tTPBrdCfgDelete,(LPARAM)&tTvwOptRet );	
	}
	else
	{
		PrtMsg( ev_cardDel_rsp, emEventTypeUmstoolRecv, "board delete success brdid=%d", m_tTPBrdCfgDelete.m_byBrdID );
		PostEvent(UI_UMSTOOL_MSG_DELETEBOARD_NTY, (WPARAM)&m_tTPBrdCfgDelete );	
	}
}

void  CUmsBoardCtrl::OnBoardAddNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
    m_tTPBrdCfgAdd = *reinterpret_cast<TTPBrdCfg*>( kdvMsg.GetBody() );

	EmTpBoardRet emRet = *reinterpret_cast<EmTpBoardRet*>( sizeof(TTPBrdCfg) + kdvMsg.GetBody() );

	if ( emTP_Board_AddSuccess != emRet )
	{
		PrtMsg( ev_cardAdd_rsp, emEventTypeUmstoolRecv, "board add error code=%d", emRet );

		TBrdOptRet tOptRet;
		tOptRet.emBrdOptType = em_Add_Ret;
		tOptRet.emTpBoardRet = emRet;
		PostEvent(UI_UMSTOOL_MSG_OPTBOARD_RSP, (WPARAM)&m_tTPBrdCfgAdd,(LPARAM)&tOptRet );	
	}
	else
	{
		in_addr tIP;
		tIP.S_un.S_addr = m_tTPBrdCfgAdd.m_tBrdPos.m_dwBrdIP; 

		PrtMsg( ev_cardAdd_rsp, emEventTypeUmstoolRecv, "board add success  Layer Num = %d, Slot = %d, IP = %s",
		m_tTPBrdCfgAdd.m_tBrdPos.m_byBrdLayer, m_tTPBrdCfgAdd.m_tBrdPos.m_byBrdSlot, inet_ntoa(tIP) );
		PostEvent(UI_UMSTOOL_MSG_OPTBOARD_NTY, (WPARAM)&m_tTPBrdCfgAdd );	
	}
}

// void  CUmsBoardCtrl::OnBoardModeAddNotify(const CMessage& cMsg)
// {
// 	CTpMsg kdvMsg( &cMsg );
//     m_tTPBrdModeCfgAdd = *reinterpret_cast<TTPBrdMdlInfo*>( kdvMsg.GetBody() );
// 	
// 	EmTpBoardRet emRet = *reinterpret_cast<EmTpBoardRet*>( sizeof(TTPBrdMdlInfo) + kdvMsg.GetBody() );
// 	
// 	if ( emTP_Board_Mode_AddSuccess != emRet )
// 	{
// 		TBrdOptRet tTvwOptRet;
// 		tTvwOptRet.emBrdOptType = em_Add_Ret;
// 		tTvwOptRet.emTpBoardRet = emRet;
// 		PrtMsg( ev_cardModeAdd_rsp, emEventTypeUmstoolRecv, "board mode add error code=%d", emRet );
// 		PostEvent(UI_UMSTOOL_MSG_OPTBOARDMODE_RSP, (WPARAM)&m_tTPBrdModeCfgAdd, (LPARAM)&tTvwOptRet );	
// 	}
// 	else
// 	{
// 		PrtMsg( ev_cardModeAdd_rsp, emEventTypeUmstoolRecv, "board mode add success byLayerid=%d", m_tTPBrdModeCfgAdd.m_byLayer );
// 		PostEvent(UI_UMSTOOL_MSG_OPTBOARDMODE_NTY, (WPARAM)&m_tTPBrdModeCfgAdd, em_Add_Ret );	
// 	}
// }

void  CUmsBoardCtrl::OnBoardModeModifyNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
    m_tTPBrdModeCfgModify = *reinterpret_cast<TTPBrdMdlInfo*>( kdvMsg.GetBody() );
	
	EmTpBoardRet emRet = *reinterpret_cast<EmTpBoardRet*>( sizeof(TTPBrdMdlInfo) + kdvMsg.GetBody() );

	if ( emTP_Board_Mode_ModifySuccess != emRet )
	{
		TBrdOptRet tOptRet;
		tOptRet.emBrdOptType = em_Modify_Ret;
		tOptRet.emTpBoardRet = emRet;
		PrtMsg( ev_cardModeModify_rsp, emEventTypeUmstoolRecv, "board mode modify error code=%d", emRet );
		PostEvent(UI_UMSTOOL_MSG_OPTBOARDMODE_RSP, (WPARAM)&m_tTPBrdModeCfgModify, (LPARAM)&tOptRet );	
	}
	else
	{
		PrtMsg( ev_cardModeModify_rsp, emEventTypeUmstoolRecv, "board mode modify success byLayerid=%d", m_tTPBrdModeCfgModify.m_byLayer );
		PostEvent(UI_UMSTOOL_MSG_OPTBOARDMODE_NTY, (WPARAM)&m_tTPBrdModeCfgModify, em_Modify_Ret );	
	}
}

void  CUmsBoardCtrl::OnBoardModeDeleteNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
    m_tTPBrdModeCfgDelete = *reinterpret_cast<TTPBrdMdlInfo*>( kdvMsg.GetBody() );
	
	EmTpBoardRet emRet = *reinterpret_cast<EmTpBoardRet*>( sizeof(TTPBrdMdlInfo) + kdvMsg.GetBody() );

	if ( emTP_Board_Mode_DelSuccess != emRet )
	{
		TBrdOptRet tTvwOptRet;
		tTvwOptRet.emBrdOptType = em_Del_Ret;
		tTvwOptRet.emTpBoardRet = emRet;
		PrtMsg( ev_cardModeDel_rsp, emEventTypeUmstoolRecv, "board mode delete error code=%d", emRet );
		PostEvent(UI_UMSTOOL_MSG_OPTBOARDMODE_RSP, (WPARAM)&m_tTPBrdModeCfgDelete, (LPARAM)&tTvwOptRet );	
	}
	else
	{
		PrtMsg( ev_cardModeDel_rsp, emEventTypeUmstoolRecv, "board mode delete success byLayerid=%d", m_tTPBrdModeCfgDelete.m_byLayer );
		PostEvent(UI_UMSTOOL_MSG_OPTBOARDMODE_NTY, (WPARAM)&m_tTPBrdModeCfgDelete, em_Del_Ret );	
	}
}

void  CUmsBoardCtrl::OnBoardUsedNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
    m_tBoardUsed = *reinterpret_cast<TTPBrdUsedInfo*>( kdvMsg.GetBody() );

	PrtMsg( ev_card_used_nty, emEventTypeUmstoolRecv, "EMEqpType:%d", m_tBoardUsed.m_emType );
	
	PostEvent( UI_UMSTOOL_MSG_BOARDUSED_NTY, (WPARAM)&m_tBoardUsed );
}

void  CUmsBoardCtrl::OnBoardUpgradeRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
    BOOL* pBrdUpGradeRsp = (BOOL*)( sizeof(u8) + sizeof(u8) + kdvMsg.GetBody() );
	if ( NULL != pBrdUpGradeRsp )
	{
		PostEvent(UI_UMSTOOL_MSG_BOARDUPGRADE_RSP, (WPARAM)pBrdUpGradeRsp );	
		
		if ( *pBrdUpGradeRsp )
		{
			PrtMsg( ev_card_upgrade_res, emEventTypeUmstoolRecv, "board upgrade success" );
		}
		else
		{
			PrtMsg( ev_card_upgrade_res, emEventTypeUmstoolRecv, "board upgrade fails" );
		}
	}
	else
	{
		PrtMsg( ev_card_upgrade_res, emEventTypeUmstoolRecv, "invlid board upgrade data" );
	}	
}


