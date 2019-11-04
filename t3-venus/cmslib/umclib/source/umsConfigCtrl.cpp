// umsConfigCtrl.cpp: implementation of the CUmsConfigCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umsConfigCtrl.h"
#include "eventoutumscfg.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUmsConfigCtrl::CUmsConfigCtrl(CUmsSession &cUmsSession)
               :CUmsConfigCtrlIF(),
			   m_pUmsSession(NULL)
{
	m_pUmsSession = &cUmsSession;
    BuildEventsMap();
	m_bIsSipRegistered = TRUE;
	m_bIsGKRegistered = TRUE;
}
CUmsConfigCtrl::~CUmsConfigCtrl()
{
// 	m_vctCnsRegInfo.clear();
// 	m_vctUmsRegInfo.clear();
// 	m_vctAllRegInfo.clear();
	m_vecAllTAliasEx.clear();
}

void  CUmsConfigCtrl::BuildEventsMap()
{
	REG_PFUN(ev_umsRegResult_notify,OnRegSigServRsp);
	REG_PFUN(ev_umsreg_notify,OnRegSigServNotify);

    REG_PFUN(ev_UmsIPCfg_Ind,OnUmsIPNotify);;

	REG_PFUN(ev_umsGKReg_notify, OnGkRegNotify); 
	REG_PFUN(ev_umsGKReg_ret, OnGkRegRsp); //GK Reg Result returned form server
    //REG_PFUN(ev_umsGkRegResult_notify, OnGkRegRely); 


	//REG_PFUN( ev_umsGetRegInfo_Req, ReqSipRegInfo );
	//REG_PFUN( ev_umsGetRegInfo_Rsp, OnRegInfoRsp );

	REG_PFUN( ev_umsGetRegInfo_UmsRspEx, OnRegInfoUmsRspEx );
	REG_PFUN( ev_umsGetRegInfo_CnsRspEx, OnRegInfoCnsRspEx );
	REG_PFUN( ev_umsGetRegInfo_MtRspEx, OnRegInfoMtRspEx );
	REG_PFUN( ev_umsGetRegInfo_McuRspEx, OnRegInfoMcuRspEx );
	

	REG_PFUN( ev_UmsGetSysTime_Rsp, OnGetSystimeRsp );

	REG_PFUN(ev_ums_sipreg_state_nty, OnSipRegResultNotify); 
	REG_PFUN(ev_ums_gkreg_state_nty, OnGkRegResultNotify); 
    
    //断链清空资源
    REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
}
  
void CUmsConfigCtrl::OnLinkBreak( const CMessage& cMsg )
{
// 	m_vctCnsRegInfo.clear();
// 	m_vctUmsRegInfo.clear();
// 	m_vctAllRegInfo.clear();
	m_vecAllTAliasEx.clear();

    memset( &m_tSipRegCfg, 0, sizeof(TTPSipRegistrarCfg)) ;
    memset( &m_tEthnet, 0, sizeof(TTPEthnetInfo)) ;
	memset( &m_tGKRegCfg, 0, sizeof(TTPGKCfg)) ;

	m_bIsSipRegistered = TRUE;
	m_bIsGKRegistered = TRUE;
    
    PrtMsg( OSP_DISCONNECT,emEventTypeUmsRecv,"清空 ums sip注册信息"); 
    //PostEvent( UI_UMS_REG_INFO_NOTIFY );
}

u16 CUmsConfigCtrl::RegSipService( const TTPSipRegistrarCfg &tSipCfg )   
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}

	CTpMsg *pKdvMsg = m_pUmsSession->GetKdvMsgPtr();
	pKdvMsg->SetEvent( ev_umsreg_cmd );
	pKdvMsg->SetBody( &tSipCfg, sizeof(TTPSipRegistrarCfg) );

	u16 wRe = m_pUmsSession->PostCommand(this, ev_umsreg_notify ,TYPE_TPMSG);
    
	in_addr tAddr;
	tAddr.S_un.S_addr = tSipCfg.dwRegIP;
 	PrtMsg( ev_umsreg_cmd, emEventTypeUmsSend, "bUsed=%d, SerIP=%s, SerPort=%d",
 		tSipCfg.bUsed, inet_ntoa(tAddr),tSipCfg.wRegPort);

	return wRe;   
}

 
u16 CUmsConfigCtrl::UnRegSipService( const TTPSipRegistrarCfg &tSipCfg )  
{
	return NO_ERROR;
}


u16 CUmsConfigCtrl::GetSipCfg( TTPSipRegistrarCfg &tSipCfg ) 
{
     tSipCfg = m_tSipRegCfg;
	// memcpy( &tSipCfg, &m_tSipRegCfg,  sizeof( TTPSipRegistrarCfg ) );
	 return NO_ERROR;
}


 /* 功能:  获取IP配置	 
        * @param [out]   
        * @return u16 成功返回0;失败返回非0错误码
        * @remarks	 
        */ 
u16 CUmsConfigCtrl::GetEthnetCfg( TTPEthnetInfo &tEthnetCfg )
{
    tEthnetCfg = m_tEthnet;
    return NO_ERROR;
 
}

u16 CUmsConfigCtrl::GetGkCfg( TTPGKCfg &tGKRegCfg )
{
    tGKRegCfg = m_tGKRegCfg;
    return NO_ERROR;
}

BOOL CUmsConfigCtrl::GetSipRegRsp()
{
    return m_bIsSipRegistered;
}

BOOL CUmsConfigCtrl::GetGKRegRsp()
{
    return m_bIsGKRegistered;
}

u16 CUmsConfigCtrl::GetUmsSystime(TTPTime& pTTime)
{
	pTTime = m_tTime;
	if ( !pTTime.IsValid() )
	{
		return ERR_CMS;
	}
	
	return NO_ERROR;
}

/* 
_event(  ev_UmsIPCfg )
_body(TTPEthnetInfo, 1)
	_ev_end
*/
u16 CUmsConfigCtrl::UpdateEthnetCfg( const TTPEthnetInfo& cfg )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
     

	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
  	pcTpMsg->SetEvent( ev_UmsIPCfg );
	pcTpMsg->SetBody( &cfg, sizeof(TTPEthnetInfo) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = cfg.dwIP;
	PrtMsg( ev_UmsIPCfg, emEventTypeUmsSend, "UmsIP: %s", inet_ntoa(tAddr) );
	return wRet;
}


void CUmsConfigCtrl::OnUmsIPNotify(const CMessage& cMsg)
{
   	CTpMsg kdvMsg( &cMsg );
    m_tEthnet = *reinterpret_cast<TTPEthnetInfo*>( kdvMsg.GetBody() );
    
    in_addr addr;
    addr.S_un.S_addr = m_tEthnet.dwIP;
    PrtMsg( ev_UmsIPCfg_Ind, emEventTypeUmsRecv, "ip = %d(%s)",m_tEthnet.dwIP, inet_ntoa(addr));
    
	PostEvent( UI_UMS_ETHNETINFO_NOTIFY );
}


/* 
enum EmTpCnsRegUms
{
tp_CnsRegRet_Unknow,
tp_CnsRegRet_Success,		//成功
tp_CnsRegRet_MaxRegNum,		//注册满
tp_CnsRegRet_MaxAliasNum,	//注册满
tp_CnsRegRet_MsgError,		//注册消息错误
tp_CnsRegRet_AliasRepeat,	//别名重复
tp_CnsRegRet_UnReg,			//删除时，未找到删除记录
tp_CnsRegRet_SysError,		//APP错误
tp_CnsRegRet_NotFind,		//查找失败
tp_CnsRegRet_Fail,          //其他失败
tp_CnsRegRet_Unreachable,   //服务器不可达
};*/
void CUmsConfigCtrl::OnRegSigServRsp( const CMessage& cMsg ) 
{
   	CTpMsg kdvMsg( &cMsg );
	TUCSipRegResult tRegRe = *reinterpret_cast<TUCSipRegResult*>( kdvMsg.GetBody() );	

	if ( tp_CnsRegRet_Success != tRegRe.m_emTpCnsRegUms )
	{
		m_bIsSipRegistered = FALSE;
	}
	else
	{
		m_bIsSipRegistered = TRUE;
	}

	PrtMsg( ev_umsRegResult_notify, emEventTypeUmsRecv, "errCode=%d \
	     ( 0:tp_CnsRegRet_Unknow, 1: tp_CnsRegRet_Success, 2: tp_CnsRegRet_MaxRegNum, 3: tp_CnsRegRet_MaxAliasNum, \
		 4: tp_CnsRegRet_MsgError, 5: tp_CnsRegRet_AliasRepeat, 6: tp_CnsRegRet_UnReg, 7: SysError, \
		 8: NotFind, 9: RegRet_Fail, 10: Unreachable, 11: UnRegister )"\
		 ,tRegRe);

	PostEvent(UI_UMS_REG_SERV_RSP,(WPARAM)&tRegRe);
}


void CUmsConfigCtrl::OnRegSigServNotify( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );

	m_tSipRegCfg = *reinterpret_cast<TTPSipRegistrarCfg*>( kdvMsg.GetBody() );


    in_addr tAddRegr;
    tAddRegr.S_un.S_addr = m_tSipRegCfg.dwRegIP; 

    in_addr tAddrHost;
    tAddrHost.S_un.S_addr = m_tSipRegCfg.dwHostIP; 

	BOOL bReg = m_tSipRegCfg.bRegistered;

 	PrtMsg( ev_umsreg_notify, emEventTypeUmsRecv, "bUsed=%d,SerIP=%d( %s ),hostIP=%d( %s ),bReg=%d",
  		m_tSipRegCfg.bUsed,m_tSipRegCfg.dwRegIP,inet_ntoa(tAddRegr),m_tSipRegCfg.dwHostIP,inet_ntoa(tAddrHost), bReg);
	
	PostEvent(UI_UMS_REG_INFO_NOTIFY, 0, 0 );
}



void CUmsConfigCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CUmsConfigCtrl,cMsg);
}

void CUmsConfigCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
    PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
}

u16 CUmsConfigCtrl::GkRegReq( const TTPGKCfg & tGkwInfo )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}

	CTpMsg *pKdvMsg = m_pUmsSession->GetKdvMsgPtr();
	pKdvMsg->SetEvent( ev_umsGKReg_cmd );
	pKdvMsg->SetBody( &tGkwInfo, sizeof(TTPGKCfg) );

	u16 wRe = m_pUmsSession->PostCommand(this, ev_umsGKReg_notify ,TYPE_TPMSG);

	_RPT0( 0, "GkRegReq ret = 发送GK注册请求\n");
	//return wRe;
    return 0;   

}

void CUmsConfigCtrl::OnGkRegNotify(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );

    m_tGKRegCfg = *reinterpret_cast<TTPGKCfg*>( kdvMsg.GetBody() );
    
    in_addr tAddRegr;
    tAddRegr.S_un.S_addr = m_tGKRegCfg.dwGKIP; 

	BOOL bReg = m_tGKRegCfg.bRegistered;
	
    PostEvent(UI_CNS_REG_GK_NTY, (WPARAM)&m_tGKRegCfg );  //send DATA to UI

	PrtMsg( ev_umsGKReg_notify, emEventTypeUmsRecv, "bUsed=%d,GKSerIP=%d( %s ),bReg=%d",
		m_tGKRegCfg.bUsed, m_tGKRegCfg.dwGKIP,inet_ntoa(tAddRegr),bReg);
}

void CUmsConfigCtrl::OnGkRegRsp(const CMessage& cMsg)
{
    CTpMsg kdvMsg( &cMsg );
    TUCSipRegResult tSipRegResult = *reinterpret_cast<TUCSipRegResult*>( kdvMsg.GetBody() );

	if ( tp_CnsRegRet_Success != tSipRegResult.m_emTpCnsRegUms )
	{
		m_bIsGKRegistered = FALSE;
	}
	else
	{
		m_bIsGKRegistered = TRUE;
	}

	PrtMsg( ev_umsGKReg_notify, emEventTypeUmsRecv, "errCode=%d \
		( 0:tp_CnsRegRet_Unknow, 1: tp_CnsRegRet_Success, 2: tp_CnsRegRet_MaxRegNum, 3: tp_CnsRegRet_MaxAliasNum,\
		4: tp_CnsRegRet_MsgError, 5: tp_CnsRegRet_AliasRepeat, 6: tp_CnsRegRet_UnReg, 7: tp_CnsRegRet_SysError, \
		8: NotFind, 9: sRegFail, 10: Unreachable, 11: UnRegister )"\
		, tSipRegResult.m_emTpCnsRegUms );


    PostEvent(UI_CNS_REG_GK_RSP, tSipRegResult.m_emTpCnsRegUms );  //send DATA to UI
}

void CUmsConfigCtrl::OnSipRegResultNotify(const CMessage& cMsg)
{
// 	CTpMsg kdvMsg( &cMsg );
// 	BOOL32 bRegRet = *reinterpret_cast<BOOL32*>( kdvMsg.GetBody() );
// 
// 	m_tSipRegCfg= *reinterpret_cast<TTPSipRegistrarCfg*>( kdvMsg.GetBody() + sizeof(BOOL32));
//     
//     in_addr tAddRegr;
//     tAddRegr.S_un.S_addr = m_tSipRegCfg.dwRegIP; 
// 	
//     PostEvent(UI_UMSTOOL_REG_NTY, 0, (LPARAM)bRegRet );
// 	
// 	PrtMsg( ev_ums_sipreg_state_nty, emEventTypeUmstoolRecv, "bReg=%d,SipSerIP=%d( %s ),BOOL:%d",
// 		m_tSipRegCfg.bUsed, m_tSipRegCfg.dwRegIP,inet_ntoa(tAddRegr), bRegRet );
}

void CUmsConfigCtrl::OnGkRegResultNotify(const CMessage& cMsg)
{
// 	CTpMsg kdvMsg( &cMsg );
// 	BOOL32 bRegRet = *reinterpret_cast<BOOL32*>( kdvMsg.GetBody() );
// 
//     m_tGKRegCfg= *reinterpret_cast<TTPGKCfg*>( sizeof(BOOL32) + kdvMsg.GetBody() );
//     
//     in_addr tAddRegr;
//     tAddRegr.S_un.S_addr = m_tGKRegCfg.dwGKIP; 
// 	
//     PostEvent(UI_UMSTOOL_GK_NTY, 0, (LPARAM)bRegRet );
// 	
// 	PrtMsg( ev_ums_gkreg_state_nty, emEventTypeUmstoolRecv, "bReg=%d,GkSerIP=%d( %s ),BOOL:%d",
// 		m_tGKRegCfg.bUsed, m_tGKRegCfg.dwGKIP,inet_ntoa(tAddRegr), bRegRet);
}

/*
const vector<TTPAlias>& CUmsConfigCtrl::GetCnsRegInfo() const
{
	return m_vctCnsRegInfo;
}

const vector<TTPAlias>& CUmsConfigCtrl::GetUmsRegInfo() const
{
	return m_vctUmsRegInfo;
}

const vector<TTPAlias>& CUmsConfigCtrl::GetAllRegInfo() const
{
	return m_vctAllRegInfo;
}
*/

const vector<TAliasEx>& CUmsConfigCtrl::GetAllTAliasEx() const
{
	return m_vecAllTAliasEx;
}

u16 CUmsConfigCtrl::ReqSipRegInfo( EmGetRegInfoType emType )
{
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr();
    
    pcTpMsg->SetEvent( ev_umsGetRegInfo_Req );
    pcTpMsg->SetBody( &emType, sizeof(EmGetRegInfoType) );
	
	if ( emType == emGetRegInfoType_CNS )
	{
		//m_vctCnsRegInfo.clear();
	}
	else if ( emType == emGetRegInfoType_UMS )
	{
		//m_vctUmsRegInfo.clear();
	}
	else
	{
		//m_vctAllRegInfo.clear();
		m_vecAllTAliasEx.clear();
	}
    
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_umsGetRegInfo_Req, emEventTypeUmsSend, "EmGetRegInfoType=%d ( emGetRegInfoType_CNS:%d, emGetRegInfoType_UMS:%d )", emType, emGetRegInfoType_CNS, emGetRegInfoType_UMS );

	//u16 wRet = m_pUmsSession->PostCommand(this, ev_umsGetRegInfo_Req ,TYPE_TPMSG);
  
	return wRet;
}

/*
void CUmsConfigCtrl::OnRegInfoRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);	
	
	TTPSipRegPackInfo tPackInfo = *reinterpret_cast<TTPSipRegPackInfo*>(cTpMsg.GetBody());
	EmGetRegInfoType emType = *(EmGetRegInfoType*)( cTpMsg.GetBody() + sizeof(TTPSipRegPackInfo) );	
	TTPSipRegInfo tRegInfo = *(TTPSipRegInfo*)( cTpMsg.GetBody() + sizeof(TTPSipRegPackInfo) + sizeof(EmGetRegInfoType) );
	
	PrtMsg( ev_umsGetRegInfo_Rsp, emEventTypeUmsRecv, "GetType: %d, TotalPackNum: %d, PackSeq: %d, RegInfoType: %d(CNS: 1, UMS: 2), AliasNum: %d"
		, emType, tPackInfo.m_wTotalPackNum, tPackInfo.m_wPackSeq, tRegInfo.m_emSelfType, tRegInfo.m_wAliasNum );
	
	if ( tRegInfo.m_emSelfType == emTPEndpointTypeCNS )
	{
		//更新全局地址簿
		for ( int i = 0; i < tRegInfo.m_wAliasNum; i++ )
		{
			TTPAlias tAlias = tRegInfo.m_atAlias[i];			
			m_vctAllRegInfo.push_back( tAlias );			
		}
	}
	else if ( tRegInfo.m_emSelfType == emTPEndpointTypeUMS )
	{
		//更新会议模板
		for ( int i = 0; i < tRegInfo.m_wAliasNum; i++ )
		{
			TTPAlias tAlias = tRegInfo.m_atAlias[i];			
			m_vctAllRegInfo.push_back( tAlias );
		}
	}
	else
	{
		for ( int i = 0; i < tRegInfo.m_wAliasNum; i++ )
		{
			TTPAlias tAlias = tRegInfo.m_atAlias[i];			
			m_vctAllRegInfo.push_back( tAlias );
		}
	}

	if ( tPackInfo.m_wPackSeq == tPackInfo.m_wTotalPackNum )
	{			
		if ( emType == emGetRegInfoType_ALL )
		{
			PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );
		}
	}

// 	if ( tRegInfo.m_emSelfType == emTPEndpointTypeCNS )
// 	{
// 		//更新全局地址簿
// 		for ( int i = 0; i < tRegInfo.m_wAliasNum; i++ )
// 		{
// 			TTPAlias tAlias = tRegInfo.m_atAlias[i];			
// 			m_vctCnsRegInfo.push_back( tAlias );			
// 		}
// 		
// 		if ( tPackInfo.m_wPackSeq == tPackInfo.m_wTotalPackNum )
// 		{			
// 			PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );
// 			if ( emType == emGetRegInfoType_ALL )
// 			{
// 				PostEvent( UI_CNS_REFRESH_CONFTEMPLATE_LIST );
// 			}
// 		}
// 	}
// 	else if ( tRegInfo.m_emSelfType == emTPEndpointTypeUMS )
// 	{
// 		//更新会议模板
// 		for ( int i = 0; i < tRegInfo.m_wAliasNum; i++ )
// 		{
// 			TTPAlias tAlias = tRegInfo.m_atAlias[i];			
// 			m_vctUmsRegInfo.push_back( tAlias );
// 		}
// 		
// 		if ( tPackInfo.m_wPackSeq == tPackInfo.m_wTotalPackNum )
// 		{			
// 			PostEvent( UI_CNS_REFRESH_CONFTEMPLATE_LIST );
// 			if ( emType == emGetRegInfoType_ALL )
// 			{
// 				PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );
// 			}
// 		}
// 	}
	
}
*/

void CUmsConfigCtrl::OnRegInfoUmsRspEx(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TUmsRegPackEx tUmsRegPackEx = *reinterpret_cast<TUmsRegPackEx*>(cTpMsg.GetBody());

	int nAliasNum = 0;
	/*
	for ( int i = 0; i < tUmsRegPackEx.m_wSize; i++ )
	{
		for ( int j = 0; j < tUmsRegPackEx.m_atRegInfo[i].m_wAliasNum; j++ )
		{
			nAliasNum++;
			
			TRegAlias tCMSAlias;
			tCMSAlias = tUmsRegPackEx.m_atRegInfo[i].m_atAlias[j];
			tCMSAlias.m_emEndpointType = emTPEndpointTypeUMS;
			
			
			TRegAlias* pTRegAlias = FindTRegAlias(tCMSAlias);
			if ( pTRegAlias != NULL )
			{
				if ( (tCMSAlias.m_emEndpointType == emTPEndpointTypeCNS || tCMSAlias.m_emEndpointType == emTPEndpointTypeUMS)
					&& pTRegAlias->m_emEndpointType != emTPEndpointTypeCNS 
					&& pTRegAlias->m_emEndpointType != emTPEndpointTypeUMS )
				{
					pTRegAlias->m_emEndpointType = tCMSAlias.m_emEndpointType;
				}
			}
			else
			{
				m_vecAllRegInfoEx.push_back( tCMSAlias );
			}
		}
	}*/

	for ( int m = 0; m < tUmsRegPackEx.m_wSize; m++ )
	{
		for ( int n = 0; n < tUmsRegPackEx.m_atRegInfo[m].m_wAliasNum; n++ )
		{
			//ums地址名称和号码未对应
			TAliasEx tCMSAlias;
			tCMSAlias.m_emEndpointType = emTPEndpointTypeUMS;
			tCMSAlias.m_vecTTPAlias.push_back(tUmsRegPackEx.m_atRegInfo[m].m_atAlias[n]);

			TAliasEx* pTRegAlias = FindTAliasEx(tCMSAlias);
			if ( pTRegAlias != NULL )
			{
				if ( (tCMSAlias.m_emEndpointType == emTPEndpointTypeCNS || tCMSAlias.m_emEndpointType == emTPEndpointTypeUMS)
					&& pTRegAlias->m_emEndpointType != emTPEndpointTypeCNS 
					&& pTRegAlias->m_emEndpointType != emTPEndpointTypeUMS )
				{
					pTRegAlias->m_emEndpointType = tCMSAlias.m_emEndpointType;
				}
			}
			else
			{
				m_vecAllTAliasEx.push_back( tCMSAlias );
			}
		}
	}


	PrtMsg( ev_umsGetRegInfo_UmsRspEx, emEventTypeUmsRecv, 
		"m_wSize: %d, m_bIsEnd: %d, RegInfoType: %d(CNS: 1, UMS: 2, MT: 4, MCU:5), nAliasNum: %d"
		, tUmsRegPackEx.m_wSize, tUmsRegPackEx.m_bIsEnd, emTPEndpointTypeUMS, nAliasNum);

	if ( tUmsRegPackEx.m_bIsEnd == TRUE )
	{
		PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOKEX, TRUE );
	}
}

TAliasEx* CUmsConfigCtrl::FindTAliasEx( TAliasEx tCMSAlias )
{
	vector<TAliasEx>::iterator it = m_vecAllTAliasEx.begin();
	for ( ; it != m_vecAllTAliasEx.end(); it++ )
	{
		if ( *it == tCMSAlias )
		{
			return it;
		}
	}
	
	return NULL;
}

void CUmsConfigCtrl::OnRegInfoCnsRspEx(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TCnsRegPackEx tCnsRegPackEx = *reinterpret_cast<TCnsRegPackEx*>(cTpMsg.GetBody());
	
	int nAliasNum = 0;
	/*
	for ( int i = 0; i < tCnsRegPackEx.m_wSize; i++ )
	{
		for ( int j = 0; j < tCnsRegPackEx.m_atRegInfo[i].m_wAliasNum; j++ )
		{
			nAliasNum++;
			
			TRegAlias tCMSAlias;
			tCMSAlias = tCnsRegPackEx.m_atRegInfo[i].m_atAlias[j];
			tCMSAlias.m_emEndpointType = emTPEndpointTypeCNS;
			
			TRegAlias* pTRegAlias = FindTRegAlias(tCMSAlias);
			if ( pTRegAlias != NULL )
			{
				if ( (tCMSAlias.m_emEndpointType == emTPEndpointTypeCNS || tCMSAlias.m_emEndpointType == emTPEndpointTypeUMS)
					&& pTRegAlias->m_emEndpointType != emTPEndpointTypeCNS 
					&& pTRegAlias->m_emEndpointType != emTPEndpointTypeUMS )
				{
					pTRegAlias->m_emEndpointType = tCMSAlias.m_emEndpointType;
				}
			}
			else
			{
				m_vecAllRegInfoEx.push_back( tCMSAlias );
			}
		}
	}*/

	for ( int m = 0; m < tCnsRegPackEx.m_wSize; m++ )
	{
		TAliasEx tCMSAlias;
		for ( int n = 0; n < tCnsRegPackEx.m_atRegInfo[m].m_wAliasNum; n++ )
		{
			tCMSAlias.m_emEndpointType = emTPEndpointTypeCNS;
			tCMSAlias.m_vecTTPAlias.push_back(tCnsRegPackEx.m_atRegInfo[m].m_atAlias[n]);
		}
		
		TAliasEx* pTRegAlias = FindTAliasEx(tCMSAlias);
		if ( pTRegAlias != NULL )
		{
			if ( (tCMSAlias.m_emEndpointType == emTPEndpointTypeCNS || tCMSAlias.m_emEndpointType == emTPEndpointTypeUMS)
				&& pTRegAlias->m_emEndpointType != emTPEndpointTypeCNS 
				&& pTRegAlias->m_emEndpointType != emTPEndpointTypeUMS )
			{
				pTRegAlias->m_emEndpointType = tCMSAlias.m_emEndpointType;
			}
		}
		else
		{
			m_vecAllTAliasEx.push_back( tCMSAlias );
		}
	}
	
	
	PrtMsg( ev_umsGetRegInfo_CnsRspEx, emEventTypeUmsRecv, 
		"m_wSize: %d, m_bIsEnd: %d, RegInfoType: %d(CNS: 1, UMS: 2, MT: 4, MCU:5), nAliasNum: %d"
		, tCnsRegPackEx.m_wSize, tCnsRegPackEx.m_bIsEnd, emTPEndpointTypeCNS, nAliasNum);
	
	if ( tCnsRegPackEx.m_bIsEnd == TRUE )
	{
		PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOKEX, TRUE );
	}
}

void CUmsConfigCtrl::OnRegInfoMtRspEx(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TTPMtRegInfo tTPMtRegInfo = *reinterpret_cast<TTPMtRegInfo*>(cTpMsg.GetBody());
	
	int nAliasNum = 0;
	/*
	for ( int i = 0; i < tTPMtRegInfo.m_wListNum; i++ )
	{
		for ( int j = 0; j < MAX_MT_ALIAS_NUM; j++ )
		{
			nAliasNum++;
			
			TRegAlias tCMSAlias;
			tCMSAlias = tTPMtRegInfo.m_atTerminal[i].m_atAlias[j];
			tCMSAlias.m_emEndpointType = emTPEndpointH323MT;
			
			TRegAlias* pTRegAlias = FindTRegAlias(tCMSAlias);
			if ( pTRegAlias != NULL )
			{
				if ( (tCMSAlias.m_emEndpointType == emTPEndpointTypeCNS || tCMSAlias.m_emEndpointType == emTPEndpointTypeUMS)
					&& pTRegAlias->m_emEndpointType != emTPEndpointTypeCNS 
					&& pTRegAlias->m_emEndpointType != emTPEndpointTypeUMS )
				{
					pTRegAlias->m_emEndpointType = tCMSAlias.m_emEndpointType;
				}
			}
			else
			{
				//判断别名是否为空，mt别名有可能为空
				if ( tCMSAlias.m_abyAlias[0] != '\0' )
				{
					m_vecAllRegInfoEx.push_back( tCMSAlias );
				}
			}
		}
	}*/

	for ( int m = 0; m < tTPMtRegInfo.m_wListNum; m++ )
	{
		TAliasEx tCMSAlias;
		for ( int n = 0; n < MAX_MT_ALIAS_NUM; n++ )
		{
			if ( tTPMtRegInfo.m_atTerminal[m].m_atAlias[n].m_abyAlias[0] != '\0')
			{
				tCMSAlias.m_vecTTPAlias.push_back( tTPMtRegInfo.m_atTerminal[m].m_atAlias[n] );
				tCMSAlias.m_emEndpointType = emTPEndpointH323MT;
			}
		}

		if ( tCMSAlias.m_vecTTPAlias.size() > 0 )
		{
			TAliasEx* pTRegAlias = FindTAliasEx(tCMSAlias);
			if ( pTRegAlias != NULL )
			{
				if ( (tCMSAlias.m_emEndpointType == emTPEndpointTypeCNS || tCMSAlias.m_emEndpointType == emTPEndpointTypeUMS)
					&& pTRegAlias->m_emEndpointType != emTPEndpointTypeCNS 
					&& pTRegAlias->m_emEndpointType != emTPEndpointTypeUMS )
				{
					pTRegAlias->m_emEndpointType = tCMSAlias.m_emEndpointType;
				}
			}
			else
			{
				m_vecAllTAliasEx.push_back( tCMSAlias );
			}
		}
	}
	
	
	PrtMsg( ev_umsGetRegInfo_MtRspEx, emEventTypeUmsRecv, 
		"m_wSize: %d, m_bIsEnd: %d, RegInfoType: %d(CNS: 1, UMS: 2, MT: 4, MCU:5), nAliasNum: %d"
		, tTPMtRegInfo.m_wListNum, tTPMtRegInfo.m_bIsEnd, emTPEndpointH323MT, nAliasNum);
	
	if ( tTPMtRegInfo.m_bIsEnd == TRUE )
	{
		PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOKEX, FALSE );
	}
}

void CUmsConfigCtrl::OnRegInfoMcuRspEx(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	TTPMcuRegInfo tTPMcuRegInfo = *reinterpret_cast<TTPMcuRegInfo*>(cTpMsg.GetBody());
	
	/*
	for ( int i = 0; i < tTPMcuRegInfo.m_wListNum; i++ )
	{
		TRegAlias tCMSAlias;
		tCMSAlias = tTPMcuRegInfo.m_atAlias[i];
		tCMSAlias.m_emEndpointType = emTPEndpointH323MCU;
		
		TRegAlias* pTRegAlias = FindTRegAlias(tCMSAlias);
		if ( pTRegAlias != NULL )
		{
			if ( (tCMSAlias.m_emEndpointType == emTPEndpointTypeCNS || tCMSAlias.m_emEndpointType == emTPEndpointTypeUMS)
				&& pTRegAlias->m_emEndpointType != emTPEndpointTypeCNS 
				&& pTRegAlias->m_emEndpointType != emTPEndpointTypeUMS )
			{
				pTRegAlias->m_emEndpointType = tCMSAlias.m_emEndpointType;
			}
		}
		else
		{
			m_vecAllRegInfoEx.push_back( tCMSAlias );
		}
	}*/

	TAliasEx tCMSAlias;
	for ( int m = 0; m < tTPMcuRegInfo.m_wListNum; m++ )
	{
		tCMSAlias.m_vecTTPAlias.push_back( tTPMcuRegInfo.m_atAlias[m] );
		tCMSAlias.m_emEndpointType = emTPEndpointH323MCU;
	}

	TAliasEx* pTRegAlias = FindTAliasEx(tCMSAlias);
	if ( pTRegAlias != NULL )
	{
		if ( (tCMSAlias.m_emEndpointType == emTPEndpointTypeCNS || tCMSAlias.m_emEndpointType == emTPEndpointTypeUMS)
			&& pTRegAlias->m_emEndpointType != emTPEndpointTypeCNS 
			&& pTRegAlias->m_emEndpointType != emTPEndpointTypeUMS )
		{
			pTRegAlias->m_emEndpointType = tCMSAlias.m_emEndpointType;
		}
	}
	else
	{
		m_vecAllTAliasEx.push_back( tCMSAlias );
	}
	
	
	PrtMsg( ev_umsGetRegInfo_McuRspEx, emEventTypeUmsRecv, 
		"m_bIsEnd: %d, RegInfoType: %d(CNS: 1, UMS: 2, MT: 4, MCU:5), nAliasNum: %d"
		, tTPMcuRegInfo.m_bIsEnd, emTPEndpointH323MCU, tTPMcuRegInfo.m_wListNum);
	
	if ( tTPMcuRegInfo.m_bIsEnd == TRUE )
	{
		PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOKEX, FALSE );
	}
}

u16 CUmsConfigCtrl::OnSysTimeSetReq(const TTPTime& tTime)
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pKdvMsg = m_pUmsSession->GetKdvMsgPtr();
	pKdvMsg->SetEvent( ev_UmsSetSysTime_Cmd );
	pKdvMsg->SetBody( &tTime, sizeof(TTPTime) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	return wRet;
}

void CUmsConfigCtrl::OnGetSystimeRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);	
	m_tTime = *reinterpret_cast<TTPTime*>(cTpMsg.GetBody());

	if ( m_tTime.IsValid() )
	{
		PrtMsg( ev_UmsGetSysTime_Rsp, emEventTypeUmsRecv, " server time: %d-%d-%d %d:%d:%d",
			m_tTime.m_wYear, m_tTime.m_byMonth, m_tTime.m_byMDay, m_tTime.m_byHour, m_tTime.m_byMinute, m_tTime.m_bySecond );
	}

	PostEvent( UI_GET_UMS_SYSTIME );
}

u16  CUmsConfigCtrl::RebootReq()  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_rebootUms_cmd);
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_rebootUms_cmd, emEventTypeUmstoolSend, "发送ums重启请求" );
	
    return NO_ERROR;
}
