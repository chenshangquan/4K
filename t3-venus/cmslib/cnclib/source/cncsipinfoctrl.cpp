// cncsipinfoctrl.cpp: implementation of the CCncSipInfoCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cncsipinfoctrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCncSipInfoCtrl::CCncSipInfoCtrl( CCnsSession &cSession ) : CCncSipInfoCtrlIF()
{
	m_pSession = &cSession;
				
	BuildEventsMap();
}

CCncSipInfoCtrl::~CCncSipInfoCtrl()
{

}

void CCncSipInfoCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CCncSipInfoCtrl, cMsg);
}

void CCncSipInfoCtrl::OnTimeOut(u16 wEvent)
{

}


void CCncSipInfoCtrl::BuildEventsMap()
{
	REG_PFUN( ev_tppGetRegInfo_Rsp, CCncSipInfoCtrl::OnRegInfoRsp );
	REG_PFUN( ev_tppGetRegInfo_Nty, CCncSipInfoCtrl::OnRegInfoNty );

    REG_PFUN( ev_tppGetRegGKInfo_Nty, CCncSipInfoCtrl::OnGetGkRegInfo );
    REG_PFUN( ev_tppGetRegInfoCNS_Rsp, CCncSipInfoCtrl::OnGetCnsRegInfo );
    REG_PFUN( ev_tppGetRegInfoUMS_Rsp, CCncSipInfoCtrl::OnGetUmsRegInfo );
    
	REG_PFUN( OSP_DISCONNECT, CCncSipInfoCtrl::OnLinkBreak ); 
}


const vector<TAddrInfo>& CCncSipInfoCtrl::GetCnsRegInfo() const
{
	return m_vctCnsRegInfo;
}

const vector<TTPAlias>& CCncSipInfoCtrl::GetUmsRegInfo() const
{
	return m_vctUmsRegInfo;
}


u16 CCncSipInfoCtrl::ReqSipRegInfo( EmGetRegInfoType emType )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_tppGetRegInfo_Req );
    pcTpMsg->SetBody( &emType, sizeof(EmGetRegInfoType) );

	if ( emType == emGetRegInfoType_CNS )
	{
		m_vctCnsRegInfo.clear();
        m_vctGkRegInfo.clear();
	}
	else if ( emType == emGetRegInfoType_UMS )
	{
		m_vctUmsRegInfo.clear();
	}
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_tppGetRegInfo_Req, emEventTypeCnsSend, "EmGetRegInfoType=%d ( emGetRegInfoType_CNS:%d, emGetRegInfoType_UMS:%d )", emType, emGetRegInfoType_CNS, emGetRegInfoType_UMS );
    return wRet;
}




void CCncSipInfoCtrl::OnRegInfoRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPSipRegPackInfo tPackInfo = *reinterpret_cast<TTPSipRegPackInfo*>(cTpMsg.GetBody());
	EmGetRegInfoType emType = *(EmGetRegInfoType*)( cTpMsg.GetBody() + sizeof(TTPSipRegPackInfo) );	
	TTPSipRegInfo tRegInfo = *(TTPSipRegInfo*)( cTpMsg.GetBody() + sizeof(TTPSipRegPackInfo) + sizeof(EmGetRegInfoType) );
	
	PrtMsg( ev_tppGetRegInfo_Rsp, emEventTypeCnsRecv, "GetType: %d, TotalPackNum: %d, PackSeq: %d, RegInfoType: %d(CNS: 1, UMS: 2), AliasNum: %d"
		, emType, tPackInfo.m_wTotalPackNum, tPackInfo.m_wPackSeq, tRegInfo.m_emSelfType, tRegInfo.m_wAliasNum );
	
	if ( tRegInfo.m_emSelfType == emTPEndpointTypeCNS )
	{
		//更新全局地址簿
		for ( int i = 0; i < tRegInfo.m_wAliasNum; i++ )
		{
            TAddrInfo tAddrInfo;
            TTPAlias tAlias = tRegInfo.m_atAlias[i];
            if ( tAlias.m_byType == tp_Alias_e164 )
            {
                strncpy( tAddrInfo.achE164, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
            }
            else
            {
                strncpy( tAddrInfo.achEntryName, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
            }  
            m_vctCnsRegInfo.push_back( tAddrInfo );
			//TTPAlias tAlias = tRegInfo.m_atAlias[i];			
			//m_vctCnsRegInfo.push_back( tAlias );			
		}

		if ( tPackInfo.m_wPackSeq == tPackInfo.m_wTotalPackNum )
		{			
			PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );
			if ( emType == emGetRegInfoType_ALL )
			{
				PostEvent( UI_CNS_REFRESH_CONFTEMPLATE_LIST );
			}
		}
	}
	else if ( tRegInfo.m_emSelfType == emTPEndpointTypeUMS )
	{
		//更新会议模板
		for ( int i = 0; i < tRegInfo.m_wAliasNum; i++ )
		{
			TTPAlias tAlias = tRegInfo.m_atAlias[i];			
			m_vctUmsRegInfo.push_back( tAlias );
		}
		
		if ( tPackInfo.m_wPackSeq == tPackInfo.m_wTotalPackNum )
		{			
			PostEvent( UI_CNS_REFRESH_CONFTEMPLATE_LIST );
			if ( emType == emGetRegInfoType_ALL )
			{
				PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );
			}
		}
	}
	else
	{
		if ( tPackInfo.m_wPackSeq == tPackInfo.m_wTotalPackNum )
		{	
			if ( emType == emGetRegInfoType_CNS )
			{
				PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );
			}
			else
			{
				PostEvent( UI_CNS_REFRESH_CONFTEMPLATE_LIST );
			}
		}
	}
	
}


void CCncSipInfoCtrl::OnRegInfoNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPSipRegInfo tRegInfo = *reinterpret_cast<TTPSipRegInfo*>(cTpMsg.GetBody());

	PrtMsg( ev_tppGetRegInfo_Nty, emEventTypeCnsRecv, "RegInfoType, AliasNum: %d", tRegInfo.m_emSelfType, tRegInfo.m_wAliasNum );
}


void CCncSipInfoCtrl::OnGetGkRegInfo(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
   
    TTPMtRegInfo tRegInfo = *reinterpret_cast<TTPMtRegInfo*>(cTpMsg.GetBody());
    
    PrtMsg( ev_tppGetRegGKInfo_Nty, emEventTypeCnsRecv, "Num: %d, IsEnd: %d", tRegInfo.m_wListNum, tRegInfo.m_bIsEnd );

    //加入在线地址簿
    for ( int i = 0; i < tRegInfo.m_wListNum; i++ )
    {
        TTPMtTerminal tMt = tRegInfo.m_atTerminal[i];
        
        TAddrInfo tAddrInfo;
        for ( int j = 0; j < MAX_MT_ALIAS_NUM; j++ )
        {
            TTPAlias tAlias = tMt.m_atAlias[j];
            if ( tAlias.m_byType == tp_Alias_e164 )
            {
                strncpy( tAddrInfo.achE164, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
            }
            else if ( tAlias.m_byType == tp_Alias_h323 )
            {
                strncpy( tAddrInfo.achEntryName, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
            }         
        }
        tAddrInfo.m_emEndpointType = tMt.m_emType;
        
        m_vctGkRegInfo.push_back( tAddrInfo );
        //m_vctCnsRegInfo.push_back( tAddrInfo );	
	}
}

void CCncSipInfoCtrl::OnGetCnsRegInfo(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    TRegPackInfoEx tPackInfo = *reinterpret_cast<TRegPackInfoEx*>( cTpMsg.GetBody() );
    EmGetRegInfoType emType = *reinterpret_cast<EmGetRegInfoType*>( cTpMsg.GetBody() + sizeof(TRegPackInfoEx) );
    TCnsRegPackEx tRegPack = *reinterpret_cast<TCnsRegPackEx*>( cTpMsg.GetBody() + sizeof(TRegPackInfoEx) + sizeof(EmGetRegInfoType) );
    
    PrtMsg( ev_tppGetRegInfoCNS_Rsp, emEventTypeCnsRecv, "TotalPackNum: %d, PackSeq: %d, PackSize: %d"
        , tPackInfo.m_tPackInfo.m_wTotalPackNum, tPackInfo.m_tPackInfo.m_wPackSeq, tRegPack.m_wSize );

    //更新全局地址簿
    for ( int i = 0; i < tRegPack.m_wSize; i++ )
    {
        TCnsRegInfoEx tRegInfo = tRegPack.m_atRegInfo[i];
        
        TAddrInfo tAddrInfo;
        for ( int j = 0; j < tRegInfo.m_wAliasNum; j++ )
        {
            TTPAlias tAlias = tRegInfo.m_atAlias[j];
            if ( tAlias.m_byType == tp_Alias_e164 )
            {
                strncpy( tAddrInfo.achE164, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
            }
            else
            {
                strncpy( tAddrInfo.achEntryName, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
            }         
        }
        tAddrInfo.m_emEndpointType = tRegInfo.m_emEndpointType;

        //如果gk中也注册了，用sip替换掉
        vector<TAddrInfo>::iterator itfind = m_vctGkRegInfo.begin();
        for ( ; itfind != m_vctGkRegInfo.end(); itfind++ )
        {
            if ( strcmp( tAddrInfo.achEntryName, "" ) == 0 )
            {
                if ( 0 == strcmp( tAddrInfo.achE164, itfind->achE164 ) )
                {
                    break;
                }
            }
            else
            {
                if ( 0 == strcmp( tAddrInfo.achEntryName, itfind->achEntryName ) )
                {
                    break;
                }
            }
        }
        if ( itfind == m_vctGkRegInfo.end() )
        {
            m_vctCnsRegInfo.push_back( tAddrInfo );
        }
        else
        {
            strncpy( itfind->achEntryName, tAddrInfo.achEntryName, TP_MAX_ALIAS_LEN_CNC+1 );
            strncpy( itfind->achE164, tAddrInfo.achE164, TP_MAX_ALIAS_LEN_CNC+1 );
            itfind->m_emEndpointType = tAddrInfo.m_emEndpointType;
        }    			
    }
    
    if ( tPackInfo.m_tPackInfo.m_wPackSeq == tPackInfo.m_tPackInfo.m_wTotalPackNum )
    {			
        m_vctCnsRegInfo.insert( m_vctCnsRegInfo.begin(), m_vctGkRegInfo.begin(), m_vctGkRegInfo.end() );
        PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );
	}
}

void CCncSipInfoCtrl::OnGetUmsRegInfo(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    TRegPackInfoEx tPackInfo = *reinterpret_cast<TRegPackInfoEx*>( cTpMsg.GetBody() );
    EmGetRegInfoType emType = *reinterpret_cast<EmGetRegInfoType*>( cTpMsg.GetBody() + sizeof(TRegPackInfoEx) );
    TUmsRegPackEx tRegPack = *reinterpret_cast<TUmsRegPackEx*>( cTpMsg.GetBody() + sizeof(TRegPackInfoEx) + sizeof(EmGetRegInfoType) );
    
    PrtMsg( ev_tppGetRegInfoUMS_Rsp, emEventTypeCnsRecv, "TotalPackNum: %d, PackSeq: %d, PackSize: %d"
        , tPackInfo.m_tPackInfo.m_wTotalPackNum, tPackInfo.m_tPackInfo.m_wPackSeq, tRegPack.m_wSize );

    for ( int i = 0; i < tRegPack.m_wSize; i++ )
    {
        TUmsRegInfoEx tRegInfo = tRegPack.m_atRegInfo[i];

        for ( int j = 0; j < tRegInfo.m_wAliasNum; j++ )
        {
            TTPAlias tAlias = tRegInfo.m_atAlias[j];
            m_vctUmsRegInfo.push_back( tAlias );    
        }		
    }
    
    if ( tPackInfo.m_tPackInfo.m_wPackSeq == tPackInfo.m_tPackInfo.m_wTotalPackNum )
    {			
        PostEvent( UI_CNS_REFRESH_CONFTEMPLATE_LIST );
	}
}



void CCncSipInfoCtrl::OnLinkBreak(const CMessage& cMsg)
{
    m_vctGkRegInfo.clear();
	m_vctCnsRegInfo.clear();
	m_vctUmsRegInfo.clear();
	PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv,"[CCncSipInfoCtrl::OnLinkBreak]清空注册信息" );
}