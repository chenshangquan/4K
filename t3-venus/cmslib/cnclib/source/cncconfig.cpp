// cncconfig.cpp: implementation of the CCncConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cncconfig.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCncConfig::CCncConfig(CCnsSession &cSession) : CCncConfigIF(),m_tGkCfg()
{
	m_pSession = &cSession;

	memset( m_achMainRoom, 0, sizeof(m_achMainRoom) );

	BuildEventsMap();
}

CCncConfig::~CCncConfig()
{

}

void CCncConfig::BuildEventsMap()
{
    REG_PFUN( ev_CnCfgCnsInfo_Ind, CCncConfig::OnCnsInfoNty );
    REG_PFUN( ev_CnCfgEthnet_Ind, CCncConfig::OnEthnetInfoInd );
    REG_PFUN( ev_tppRegisterRs_Req, CCncConfig::OnRegSipNty );
    REG_PFUN( ev_tpRegisterResult_Nty, CCncConfig::OnRegResultNty );
    REG_PFUN( ev_CnSetMainRoom_Ind, CCncConfig::OnMainCnsInd );
    REG_PFUN( ev_tpRoomOffline_Nty, CCncConfig::OnCnsOfflineNty );
    REG_PFUN( ev_CnGetSysTime_Rsp, CCncConfig::OnSysTimeRsp );
    REG_PFUN( ev_tpRegisterResultFail_Nty, CCncConfig::OnRegResultFailNty );
    REG_PFUN( ev_CnsGKReg_Ret, CCncConfig::OnRegGkRsp );
    REG_PFUN( ev_CnsGKReg_Nty, CCncConfig::OnRegGkNty );

	REG_PFUN( ev_tppNatReg_Nty, CCncConfig::OnRegNatNty);

    REG_PFUN( ev_TppSetDualInputPortName_Ind, CCncConfig::OnSetDualPortNameInd );
    REG_PFUN( ev_TppSelDualInputPort_Ind, CCncConfig::OnSelDualInputPortInd );
    REG_PFUN( ev_TppCurrentVgaInfo_Nty, CCncConfig::OnVgaInfoNty );
    REG_PFUN( ev_TppConfVgaInfo_Nty, CCncConfig::OnConfVgaInfoNty );
	REG_PFUN( ev_Cn_SetSleepInfoInd, CCncConfig::OnSysSleepNty );
	REG_PFUN( ev_tppSetEncryptInfo_Ind, CCncConfig::OnEncryptionInd);  
	REG_PFUN( ev_CnCfgLostPackageRestore_Ind, CCncConfig::OnLostPackageInd);

	//CNS双网口和网口备份
	REG_PFUN( ev_CnCfgWEthnet_Nty, CCncConfig::OnSetCfgWEthnetNty );
	REG_PFUN( ev_CnCfgWEthnet_Rsp, CCncConfig::OnSetCfgWEthnetRsp );
	REG_PFUN( ev_CnCfgEthState_Nty, CCncConfig::OnSetCfgEthnetStateNty );

	//云平台服务器配置
    REG_PFUN( ev_tppCloudPlatServerCfgInd, CCncConfig::OnSetCloudServerInd);  
    REG_PFUN( ev_tppCloudPlatServerCfgNty, CCncConfig::OnSetCloudServerNty); 

    REG_PFUN( OSP_DISCONNECT, CCncConfig::OnLinkBreak ); 
}

void CCncConfig::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CCncConfig, cMsg);
}


void CCncConfig::OnTimeOut(u16 wEvent)
{
    //PostEvent(MTC_UI_CMD_TIMEOUT, wEvent);
}


u16 CCncConfig::RegSipService(const TTPSipRegistrarCfg& tSipCfg)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( ins_each );
	pcTpMsg->SetEvent( ev_tppRegisterRs_Req );
	pcTpMsg->SetBody( &tSipCfg, sizeof(TTPSipRegistrarCfg) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = tSipCfg.dwRegIP;
	PrtMsg( ev_tppRegisterRs_Req, emEventTypeCnsSend, "TTPSipRegistrarCfg: RegIP: %s ", inet_ntoa(tAddr) );
	return wRet;
}

u16 CCncConfig::UnRegSipService()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( ins_each );
	pcTpMsg->SetEvent( ev_tppUnRegisterRs_Req );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	PrtMsg( ev_tppUnRegisterRs_Req, emEventTypeCnsSend, "" );
	return wRet;
}

 
u16 CCncConfig::RegGk( const TTPGKCfg& tGkCfg )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( ins_each );
   
    pcTpMsg->SetEvent( ev_CnsGKReg_Cmd );
    pcTpMsg->SetBody( &tGkCfg, sizeof(TTPGKCfg) );
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    in_addr tAddr;
    tAddr.S_un.S_addr = tGkCfg.dwGKIP;
    PrtMsg( ev_CnsGKReg_Cmd, emEventTypeCnsSend, "RegGk: isUse=%d  GkRegIP: %s ", tGkCfg.bUsed, inet_ntoa(tAddr) );
    
	return wRet;
}

const TTPGKCfg& CCncConfig::GetGkCfg() const
{
    return m_tGkCfg;
} 


u16 CCncConfig::UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex ,EmTpIpNameNatSyn emTpIpType)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnCfgCnsInfo_Cmd );
	pcTpMsg->SetBody( &tInfo, sizeof(TTPCnsInfo) );
	pcTpMsg->CatBody( &byIndex, sizeof(u8) );
	pcTpMsg->CatBody( &emTpIpType, sizeof(EmTpIpNameNatSyn) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	PrtMsg( ev_CnCfgCnsInfo_Cmd, emEventTypeCnsSend, "TTPCnsInfo: CnsName: %s, E164: %s, CnsLevel: %d, ScreenNum: %d, From: %d ,EmTpIpNameNatSyn %d",
		tInfo.m_achRoomName, tInfo.m_achE164, tInfo.m_emLevel, tInfo.m_wScreenNum, byIndex,emTpIpType);
	return wRet;
}

u16 CCncConfig::SetMainCns( s8* pbyRoomName )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( LOCAL_CNS );
	pcTpMsg->SetEvent( ev_CnSetMainRoom_Cmd );
	s8 achName[TP_MAX_NAME_LEN+1] = {0};
	strcpy( achName, pbyRoomName );
	pcTpMsg->SetBody( achName, sizeof(achName) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_CnSetMainRoom_Cmd, emEventTypeCnsSend, "MainCnsName: %s", pbyRoomName );
	return wRet;
}

u16 CCncConfig::UpdateEthnetCfg( const TTPEthnetInfo& cfg ,EmTpIpNameNatSyn emTpIpType)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnCfgEthnet_Cmd );
	pcTpMsg->SetBody( &cfg, sizeof(TTPEthnetInfo) );
	pcTpMsg->CatBody( &emTpIpType, sizeof(EmTpIpNameNatSyn) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = cfg.dwIP;
	PrtMsg( ev_CnCfgEthnet_Cmd, emEventTypeCnsSend, "CnsIP: %s,EmTpIpNameNatSyn %d", inet_ntoa(tAddr),emTpIpType );
	return wRet;
}

u16 CCncConfig::SaveWEthnetCfgCmd(const TTPWEthnetInfo& tTPWEthnetInfo, EmTpIpNameNatSyn emTpIpType)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnCfgWEthnet_Cmd );
	pcTpMsg->SetBody( &tTPWEthnetInfo, sizeof(TTPWEthnetInfo) );
	pcTpMsg->CatBody( &emTpIpType, sizeof(EmTpIpNameNatSyn) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgWEthnet_Cmd, emEventTypeCnsSend, "" );

	return wRet;
}

const TTPSipRegistrarCfg& CCncConfig::GetSipRegCfg() const
{
	return m_tSipCfg;
}

const TTPEthnetInfo& CCncConfig::GetEthnetCfg() const
{
	return m_tEthnetInfo;
}


const TTPCnsInfo& CCncConfig::GetLocalCnsInfo() const
{
	return m_tLocalCnsInfo;
}

const vector<TTPCnsInfo>& CCncConfig::GetLocalCnsList() const
{
	return m_vctCnsList;
}

const s8* CCncConfig::GetMainCnsName() const
{
	return m_achMainRoom;
}

const TDualSrcInfo& CCncConfig::GetDualSrcInfo() const
{
    return m_tDualSrcInfo;
}

const TCenDevSleepInfo& CCncConfig::GetSysSleepInfo() const
{
    return m_tCenDevSleepInfo;
}

const TTPVgaMixInfo& CCncConfig::GetVgaMixInfo() const
{
	return m_tVgaMixInfo;
}

void CCncConfig::OnCnsInfoNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
    
    u8 uInst = cTpMsg.GetHomeplace();

	TTPCnsInfo tCnsInfo = *reinterpret_cast<TTPCnsInfo*>(cTpMsg.GetBody());

	EmTPCNSInfoRst tRst = *(EmTPCNSInfoRst*)( cTpMsg.GetBody() + sizeof(TTPCnsInfo) );

	//UpdateCnsList( tCnsInfo );
	
	if ( tRst == emTPCNSInfoSuccess )
	{
		m_tLocalCnsInfo = tCnsInfo;	
	}
	
	PostEvent( UI_CNS_CNSINFO_NOTIFY, (WPARAM)&tCnsInfo, (LPARAM)tRst );	

	PrtMsg( ev_CnCfgCnsInfo_Ind, emEventTypeCnsRecv, "TTPCnsInfo: CnsName: %s, E164: %s, CnsLevel: %d, ScreenNum: %d, emRst: %d, Inst: %d ", 
		tCnsInfo.m_achRoomName, tCnsInfo.m_achE164, tCnsInfo.m_emLevel, tCnsInfo.m_wScreenNum, tRst, uInst );
}

void CCncConfig::OnRegSipNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

    m_tSipCfg = *reinterpret_cast<TTPSipRegistrarCfg*>(cTpMsg.GetBody());

	PostEvent( UI_CNS_REGSIP_NOTIFY );

	in_addr tAddr;
	tAddr.S_un.S_addr = m_tSipCfg.dwRegIP;
	PrtMsg( ev_tppRegisterRs_Req, emEventTypeCnsRecv, "TTPSipRegCfg: bUsed: %d, RegIp: %s", m_tSipCfg.bUsed, inet_ntoa(tAddr) );
}

void CCncConfig::OnRegResultNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
    u8 uInst = cTpMsg.GetHomeplace();

	BOOL bResult = *(BOOL*)(cTpMsg.GetBody());	

	s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	strncpy( achCnsName, (s8*)(cTpMsg.GetBody()+sizeof(BOOL)), TP_MAX_ALIAS_LEN + 1 );
	
	PostEvent( UI_CNS_REGRESULT_NOTIFY, bResult, (LPARAM)achCnsName );
	
	PrtMsg( ev_tpRegisterResult_Nty, emEventTypeCnsRecv, "RegResult: %d, RoomName: %s, Inst: %d", bResult, achCnsName, uInst );
}

void CCncConfig::OnRegResultFailNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	//BOOL bResult = *(BOOL*)(cTpMsg.GetBody());	
	
	s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	strncpy( achCnsName, (s8*)cTpMsg.GetBody(), TP_MAX_ALIAS_LEN + 1 );

	EmTpCnsRegUms emReg = *(EmTpCnsRegUms*)( cTpMsg.GetBody()+TP_MAX_ALIAS_LEN+1 );

	if ( emReg == tp_CnsRegRet_AliasRepeat || emReg == tp_CnsRegRet_NameDup )
	{
		TTPRegNameRepeatInfo tRepeatInfo = *(TTPRegNameRepeatInfo*)( cTpMsg.GetBody()+ TP_MAX_ALIAS_LEN+1 + sizeof(EmTpCnsRegUms) );

		PostEvent( UI_CNS_SIPREG_ALIASREPEAT_NOTIFY, (WPARAM)&tRepeatInfo, (LPARAM)achCnsName );
		
		PrtMsg( ev_tpRegisterResultFail_Nty, emEventTypeCnsRecv, "RoomName: %s, EmTpCnsRegUms: %d, RepeatSize: %d", achCnsName, emReg, tRepeatInfo.dwsize );
	}
	else
	{
		PostEvent( UI_CNS_REGRESULT_NOTIFY, emReg, (LPARAM)achCnsName );

        u8 uInst = cTpMsg.GetHomeplace();
		
		PrtMsg( ev_tpRegisterResultFail_Nty, emEventTypeCnsRecv, "RoomName: %s, EmTpCnsRegUms: %d, Inst: %d", achCnsName, emReg, uInst );
	}
}


/*
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
*/
void CCncConfig::OnRegGkRsp(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    TUCSipRegResult tResult = *(TUCSipRegResult*)(cTpMsg.GetBody());
      
	PrtMsg( ev_CnsGKReg_Ret, emEventTypeCnsRecv, "RegResult: %d(tp_CnsRegRet_Unknow:%d,tp_CnsRegRet_Success:%d )",
              tResult.m_emTpCnsRegUms, tp_CnsRegRet_Unknow, tp_CnsRegRet_Success );

	PostEvent( UI_CNS_REG_GK_RSP, (WPARAM)&tResult, 0 ); 
}

void CCncConfig::OnRegGkNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    TTPGKCfg tResult = *(TTPGKCfg*)(cTpMsg.GetBody());
    
    m_tGkCfg = tResult;
    
    in_addr tAddr;
    tAddr.S_un.S_addr = tResult.dwGKIP;
    PrtMsg( ev_CnsGKReg_Nty, emEventTypeCnsRecv, "RegGk: isUse=%d  GkRegIP: %s  ", tResult.bUsed, inet_ntoa(tAddr) ); 
    
	PostEvent( UI_CNS_REG_GK_NTY, 0, 0 ); 
}

void CCncConfig::OnEthnetInfoInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);	

    u8 uInst = cTpMsg.GetHomeplace();

    TTPEthnetInfo tEthnetInfo = *reinterpret_cast<TTPEthnetInfo*>(cTpMsg.GetBody());

	m_tEthnetInfo = tEthnetInfo;
	PostEvent( UI_CNS_ETHNETINFO_NOTIFY );

	in_addr tAddr;
	tAddr.S_un.S_addr = tEthnetInfo.dwIP;
	PrtMsg( ev_CnCfgEthnet_Ind, emEventTypeCnsRecv, "TTPEthnetInfo: Ip: %s, Inst: %d", inet_ntoa(tAddr), uInst );
}

void CCncConfig::OnSetCfgWEthnetNty(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	u8 uInst = cTpMsg.GetHomeplace();
	TTPWEthnetInfo tTPWEthnetInfo = *(TTPWEthnetInfo*)( cTpMsg.GetBody() );
	PostEvent( UI_CNS_CFGWETHNET_NTY, (WPARAM)&tTPWEthnetInfo, 0 );
	
	PrtMsg( ev_CnCfgWEthnet_Nty, emEventTypeCnsRecv, _T( "set DoubleNetInfo " ) );
}

void CCncConfig::OnSetCfgWEthnetRsp(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	u8 uInst = cTpMsg.GetHomeplace();
	TTPWEthnetInfo tTPWEthnetInfo = *(TTPWEthnetInfo*)( cTpMsg.GetBody() );
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPWEthnetInfo) + sizeof(EmTpIpNameNatSyn) );

	PostEvent( UI_CNS_CFGWETHNET_RSP, (WPARAM)&tTPWEthnetInfo, (LPARAM)&bSuccess );
	
	PrtMsg( ev_CnCfgWEthnet_Rsp, emEventTypeCnsRecv, "bSuccess: %d", bSuccess );	
}

void CCncConfig::OnSetCfgEthnetStateNty(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	u8 uInst = cTpMsg.GetHomeplace();

	EmEthState emEthState = *(EmEthState*)(cTpMsg.GetBody());
	PostEvent( UI_CNS_CFGETHSTATE_NTY, (WPARAM)&emEthState, 0 );	
	PrtMsg( ev_CnCfgEthState_Nty, emEventTypeCnsRecv, "emEthState: %d", emEthState);
}

void CCncConfig::OnMainCnsInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
    
    u8 uInst = cTpMsg.GetHomeplace();
    
	s8 *pRoomName = reinterpret_cast<s8 *>(cTpMsg.GetBody());
	memcpy( m_achMainRoom, pRoomName, sizeof(m_achMainRoom) );
	
	PostEvent( UI_CNS_MAINROOM_NOTIFY );	

	PrtMsg( ev_CnSetMainRoom_Ind, emEventTypeCnsRecv, "MainCnsName: %s, Inst: %d", m_achMainRoom, uInst );
}


void CCncConfig::UpdateCnsList( TTPCnsInfo tCnsInfo )
{
	for ( u32 i = 0; i < m_vctCnsList.size(); i++ )
	{
		TTPCnsInfo tInfo = m_vctCnsList.at(i);
		if ( strcmp( tInfo.m_achRoomName, tCnsInfo.m_achRoomName ) == 0 )
		{
			m_vctCnsList[i] = tCnsInfo;
			return;
		}
	}
	m_vctCnsList.push_back( tCnsInfo );
}

void CCncConfig::OnCnsOfflineNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
    
    u8 uInst = cTpMsg.GetHomeplace();
    
	s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	s8 *pRoomName = reinterpret_cast<s8 *>(cTpMsg.GetBody());
	memcpy( achCnsName, pRoomName, sizeof(achCnsName) );

	BOOL bLocalCns = FALSE;
	if ( strcmp( m_tLocalCnsInfo.m_achRoomName, achCnsName ) == 0 )
	{
		bLocalCns = TRUE;
		memset( &m_tLocalCnsInfo, 0, sizeof(m_tLocalCnsInfo) );
	}

// 	vector<TTPCnsInfo>::iterator iter = m_vctCnsList.begin();
// 	while( iter != m_vctCnsList.end() )
// 	{
// 		if ( strcmp( (*iter).m_achRoomName, achCnsName ) == 0 )
// 		{
// 			m_vctCnsList.erase( iter );
// 			break;
// 		}
// 		iter++;
// 	}	

	PrtMsg( ev_tpRoomOffline_Nty, emEventTypeCnsRecv, "CnsOffline: %s, LocalCns: %d, Inst: %d", achCnsName, bLocalCns, uInst );
	
	PostEvent( UI_CNS_ROOMOFFLINE, (WPARAM)achCnsName, bLocalCns );
}


// 断链清空数据
void CCncConfig::OnLinkBreak(const CMessage& cMsg)
{
	memset( &m_tEthnetInfo, 0, sizeof(m_tEthnetInfo) );
	memset( &m_tSipCfg, 0, sizeof(m_tSipCfg) );
	memset( &m_tLocalCnsInfo, 0, sizeof(m_tLocalCnsInfo) );
	memset( m_achMainRoom, 0, sizeof(m_achMainRoom) );
    memset( &m_tGkCfg, 0, sizeof(m_tGkCfg) );
	memset( &m_tVgaMixInfo, 0, sizeof(m_tVgaMixInfo) );
	m_vctCnsList.clear();
    m_tDualSrcInfo.Clear();
    PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv,"[CCncConfig::OnLinkBreak]清空配置信息" );
}




//设置系统时间
u16 CCncConfig::UpdateSysTime( const TTPTime& time )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnSetSysTime_Cmd );
    pcTpMsg->SetBody( &time, sizeof(TTPTime) );
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
     
    PrtMsg( ev_CnSetSysTime_Cmd, emEventTypeCnsSend, "time: %d/%d/%d %d:%d:%d", time.m_wYear, time.m_byMonth, time.m_byMDay,time.m_byHour,time.m_byMinute,time.m_bySecond  );
	return wRet;
}

//获取系统时间
u16 CCncConfig::ReqSysTime()
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnGetSysTime_Req ); 
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
    PrtMsg( ev_CnGetSysTime_Req, emEventTypeCnsSend,"" );
	return wRet;
}


// 
void CCncConfig::OnSysTimeRsp(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    TTPTime time = *reinterpret_cast<TTPTime *>(cTpMsg.GetBody()); 
	PrtMsg( ev_CnGetSysTime_Rsp, emEventTypeCnsRecv, "time: %d/%d/%d %d:%d:%d", 
         time.m_wYear, time.m_byMonth, time.m_byMDay,time.m_byHour,time.m_byMinute,time.m_bySecond  );

    PostEvent( UI_CNS_SYSTIME_RSP, (WPARAM)&time, 0 );
}


u16 CCncConfig::SelDualInputPort( EmVgaType emType )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );

    pcTpMsg->SetEvent( ev_TppSelDualInputPort_Cmd ); 
    pcTpMsg->SetBody( &emType, sizeof(EmVgaType) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
    PrtMsg( ev_TppSelDualInputPort_Cmd, emEventTypeCnsSend, "EmVgaType: %d", emType );
    return wRet;
     
}

u16 CCncConfig::SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_TppSetDualInputPortName_Cmd ); 
    pcTpMsg->SetBody( &tVgaInfo, sizeof(TVgaInfo) );
    pcTpMsg->CatBody( &bDefault, sizeof(BOOL) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
    PrtMsg( ev_TppSetDualInputPortName_Cmd, emEventTypeCnsSend, "EmVgaType: %d, Name: %s, bDefault: %d", tVgaInfo.m_emVgaType, tVgaInfo.m_achAlias, bDefault );
    return wRet;
}

void CCncConfig::OnSetDualPortNameInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    BOOL bOk = *reinterpret_cast<BOOL *>(cTpMsg.GetBody());	
    
	PrtMsg( ev_TppSetDualInputPortName_Ind, emEventTypeCnsRecv, "bOK: %d", bOk );
}

void CCncConfig::OnSelDualInputPortInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *reinterpret_cast<BOOL*>(cTpMsg.GetBody());	

    EmVgaType emType = *reinterpret_cast<EmVgaType*>( cTpMsg.GetBody() + sizeof(BOOL) );

    EmVgaSwitchResult emResult = *reinterpret_cast<EmVgaSwitchResult*>( cTpMsg.GetBody() + sizeof(BOOL) + sizeof(EmVgaType) );
    
	PrtMsg( ev_TppSelDualInputPort_Ind, emEventTypeCnsRecv, "bOk: %d, emType: %d, emResult:%d", bOk, emType, emResult );

    if ( emResult == em_VgaSwitchSucc )
    {
        m_tDualSrcInfo.emCurrentType = emType;
        PostEvent( UI_CNS_CONFVGAINFO_NOTIFY );
    }
    else
    {
        PostEvent( UI_CNS_SELDUALPORT_IND, bOk, emResult );
    }
    
}

void CCncConfig::OnVgaInfoNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    m_tDualSrcInfo.Clear();

    for ( int i = 0; i < CNS_VGA_TYPE_NUM; i++ )
    {
        TVgaInfo tVgaInfo = *reinterpret_cast<TVgaInfo *>( cTpMsg.GetBody() + i * sizeof(TVgaInfo) );
        m_tDualSrcInfo.vctVgaInfo.push_back( tVgaInfo );
    }
    
    TVgaInfo tDefaultVga = *reinterpret_cast<TVgaInfo *>( cTpMsg.GetBody() + CNS_VGA_TYPE_NUM * sizeof(TVgaInfo) );

    m_tDualSrcInfo.emDefaultType = tDefaultVga.m_emVgaType;
    m_tDualSrcInfo.emCurrentType = *reinterpret_cast<EmVgaType *>( cTpMsg.GetBody() + (CNS_VGA_TYPE_NUM+1) * sizeof(TVgaInfo) );

	m_tVgaMixInfo = *reinterpret_cast<TTPVgaMixInfo *>( cTpMsg.GetBody() + (CNS_VGA_TYPE_NUM+1) * sizeof(TVgaInfo) + sizeof(EmVgaType) );
    PrtMsg( ev_TppCurrentVgaInfo_Nty, emEventTypeCnsRecv, "DefaultType: %d, CurrentType: %d, OutCurrent:%d, OutFstName:%s, OutFstName:%s", 
		m_tDualSrcInfo.emDefaultType, m_tDualSrcInfo.emCurrentType, m_tVgaMixInfo.m_emDualOutputType, m_tVgaMixInfo.m_achVgaOutputFstName, m_tVgaMixInfo.m_achVgaOutputSndName );

    PostEvent( UI_CNS_VGAINFO_NOTIFY );
}
 
void CCncConfig::OnConfVgaInfoNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    EmVgaType emType = *reinterpret_cast<EmVgaType*>(cTpMsg.GetBody());

    m_tDualSrcInfo.emCurrentType = emType;

    PrtMsg( ev_TppConfVgaInfo_Nty, emEventTypeCnsRecv, "CurrentType: %d", emType );

    PostEvent( UI_CNS_CONFVGAINFO_NOTIFY );
}

u16 CCncConfig::UpdateNATCfg( const TTPNatCfg& cfg,EmTpIpNameNatSyn emTpIpType)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( ins_each );//此类消息需要通知所有会场
	pcTpMsg->SetEvent( ev_tppNatReg_Cmd );
	pcTpMsg->SetBody( &cfg, sizeof(TTPNatCfg) );
	pcTpMsg->CatBody( &emTpIpType, sizeof(EmTpIpNameNatSyn) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = cfg.dwNatIP;
	PrtMsg( ev_tppNatReg_Cmd, emEventTypeCnsSend, "NATIP: %s,EmTpIpNameNatSyn %d", inet_ntoa(tAddr) ,emTpIpType);
	return wRet;
}

const TTPNatCfg& CCncConfig::GetNATCfg() const
{
	return m_tNATCfg;
}

void CCncConfig::OnRegNatNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    TTPNatCfg tResult = *(TTPNatCfg*)(cTpMsg.GetBody());
    
    m_tNATCfg = tResult;
    
    in_addr tAddr;
    tAddr.S_un.S_addr = tResult.dwNatIP;
    PrtMsg( ev_tppNatReg_Nty, emEventTypeCnsRecv, "RegNAT: isUse=%d  NATRegIP: %s  ", tResult.bUsed, inet_ntoa(tAddr) ); 
    
	PostEvent( UI_CNS_REG_NAT_NTY, 0, 0 ); 	
}

u16 CCncConfig::SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_Cn_SetSleepInfoCmd ); 
    pcTpMsg->SetBody( &tCenDevSleepInfo, sizeof(TCenDevSleepInfo) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
    PrtMsg( ev_Cn_SetSleepInfoCmd, emEventTypeCnsSend, "SleepTimes: %d, bOpen: %d", tCenDevSleepInfo.wSleepWaitTime, tCenDevSleepInfo.bSleepUsed );
    return wRet;
}

void CCncConfig::OnSysSleepNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    TCenDevSleepInfo tResult = *(TCenDevSleepInfo*)(cTpMsg.GetBody());
    
    m_tCenDevSleepInfo = tResult;

    
    PrtMsg( ev_Cn_SetSleepInfoInd, emEventTypeCnsRecv,  "SleepTimes: %d, bOpen: %d", m_tCenDevSleepInfo.wSleepWaitTime, m_tCenDevSleepInfo.bSleepUsed ); 
    
	PostEvent( UI_CNS_SLEEPINFO_NOTIFY, 0, 0 ); 
}

u16 CCncConfig::SetDataServerInfoCmd( u32 dwIp )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( 1 );
    pcTpMsg->SetEvent( ev_tppSetDataServerInfo_Cmd );
    
    TTPDataConfInfo tDCInfo;
    tDCInfo.dwSerIP = dwIp;
    
    pcTpMsg->SetBody( &tDCInfo, sizeof(TTPDataConfInfo) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    in_addr tAddr;
    tAddr.S_un.S_addr = dwIp;
    PrtMsg( ev_tppSetDataServerInfo_Cmd, emEventTypeCnsSend, "DataConfIp:%s", inet_ntoa(tAddr) );
    
    return wRet;
}

u16 CCncConfig::SetAesEncrypCmd( const TTpEncryptKey& tEncryptKey )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_tppSetEncryptInfo_Cmd );
	pcTpMsg->SetBody( &tEncryptKey, sizeof(TTpEncryptKey) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppSetEncryptInfo_Cmd, emEventTypeCnsSend, "emTPEncryptType: %d, emQtKeyFrequency: %d", tEncryptKey.emTPEncryptType, tEncryptKey.emQtKeyFrequency );

	return wRet;
}

void CCncConfig::OnEncryptionInd( const CMessage &cMsg )
{	
    CTpMsg cTpMsg(&cMsg); 
	TTpEncryptKey tEncryptKey = *(TTpEncryptKey*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTpEncryptKey) );
	
	PrtMsg( ev_tppSetEncryptInfo_Ind, emEventTypeCnsRecv, "emTPEncryptType: %d, emQtKeyFrequency: %d, Success: %d ", tEncryptKey.emTPEncryptType, tEncryptKey.emQtKeyFrequency, bSuccess );
	PostEvent( UI_CNSTOOL_EncryptInfo_Nty, (WPARAM)&bSuccess, (LPARAM)&tEncryptKey ); 
}

u16 CCncConfig::SetLostPacketCmd( EmTpLostPackageRestore emLostPackage )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnCfgLostPackageRestore_Cmd );
	pcTpMsg->SetBody( &emLostPackage, sizeof(EmTpLostPackageRestore) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgLostPackageRestore_Cmd, emEventTypeCnsSend, "ev_CnCfgLostPackageRestore_Cmd");
	
	return wRet;
}

u16 CCncConfig::SetFtpInfoRsq(const TTPFtpInfo &tTPFtpInfo)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnSetFtp_Req );
	pcTpMsg->SetBody( &tTPFtpInfo, sizeof(TTPFtpInfo) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetFtp_Req, emEventTypeCnsSend, "tTPFtpInfo.bOpen: %d, tTPFtpInfo.achUserName: %s, tTPFtpInfo.achPassword: %s", tTPFtpInfo.bOpen, tTPFtpInfo.achUserName, tTPFtpInfo.achPassword );

	return wRet;
}

u16 CCncConfig::SetTelInfoRsp(const TTPTelnetInfo &tTPTelnetInfo)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnSetTelnet_Req );
	pcTpMsg->SetBody( &tTPTelnetInfo, sizeof(TTPTelnetInfo) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetTelnet_Req, emEventTypeCnsSend, "tTPTelnetInfo.bOpen: %d, tTPTelnetInfo.achUserName: %s, tTPTelnetInfo.achPassword: %s", tTPTelnetInfo.bOpen, tTPTelnetInfo.achUserName, tTPTelnetInfo.achPassword );
	
	return wRet;
}

void CCncConfig::OnLostPackageInd( const CMessage &cMsg )
{	
    CTpMsg cTpMsg(&cMsg); 
	EmTpLostPackageRestore emLostPackage = *(EmTpLostPackageRestore*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTpLostPackageRestore) );
	
	PrtMsg( ev_CnCfgLostPackageRestore_Ind, emEventTypeCnsRecv, " Success %d ",bSuccess);
	PostEvent( UI_CNSTOOL_LostPacket_Nty, (WPARAM)&bSuccess, (LPARAM)&emLostPackage ); 
}

u16 CCncConfig::SetCloudServerInfo(const TTPCloudPlatServerCfg& tTpCloudServerInfo)
{
    if ( NULL == m_pSession ) 
    {
        return ERR_CMS;
    }
	
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_tppCloudPlatServerCfgCmd );
    pcTpMsg->SetBody( &tTpCloudServerInfo, sizeof(tTpCloudServerInfo) );
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
    PrtMsg( ev_tppCloudPlatServerCfgCmd, emEventTypeCnsSend,  _T("IP:%s ID:%s PW:%s"), tTpCloudServerInfo.m_achServerIP, tTpCloudServerInfo.m_achUsrName, tTpCloudServerInfo.m_achPwd );
    return wRet;
}

void CCncConfig::OnSetCloudServerInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg); 
	
    TTPCloudPlatServerCfg tTpCloudServerInfo = *reinterpret_cast<TTPCloudPlatServerCfg*>(cTpMsg.GetBody());
    BOOL bIsOk = *reinterpret_cast<BOOL*>(cTpMsg.GetBody() + sizeof(TTPCloudPlatServerCfg));
	
    PrtMsg( ev_tppCloudPlatServerCfgInd, emEventTypeCnsRecv, _T("IsOK:%d IP:%s ID:%s PW:%s"), bIsOk, tTpCloudServerInfo.m_achServerIP, tTpCloudServerInfo.m_achUsrName, tTpCloudServerInfo.m_achPwd );
	
    if (bIsOk)
    {
        m_tTpCloudServerInfo = tTpCloudServerInfo;
    }

    PostEvent( UI_CNC_CLOUDSERVER_IND , 1, bIsOk );
}

void CCncConfig::OnSetCloudServerNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg); 
	
    TTPCloudPlatServerCfg tTpCloudServerInfo = *reinterpret_cast<TTPCloudPlatServerCfg*>(cTpMsg.GetBody());
    m_tTpCloudServerInfo = tTpCloudServerInfo;
    PrtMsg( ev_tppCloudPlatServerCfgNty, emEventTypeCnsRecv, _T("IP:%s ID:%s PW:%s"), m_tTpCloudServerInfo.m_achServerIP, m_tTpCloudServerInfo.m_achUsrName, m_tTpCloudServerInfo.m_achPwd);
	
    PostEvent( UI_CNC_CLOUDSERVER_IND, 1, TRUE );
}

const TTPCloudPlatServerCfg& CCncConfig::GetCloudServerInfo()const
{
    return m_tTpCloudServerInfo;
}
