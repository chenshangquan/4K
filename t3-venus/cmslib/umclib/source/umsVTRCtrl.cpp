// umsvtrCtrl.cpp: implementation of the CUmsVTRCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umsVTRCtrl.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUmsVTRCtrl::CUmsVTRCtrl(CUmsSession &cUmsSession)
               :CUmsVTRCtrlIF(),
			   m_pUmsSession(NULL),
			   m_vecTVTRCfg(),
			   m_nLeft(0),
			   m_bRegState(FALSE)
{
	m_pUmsSession = &cUmsSession;
    BuildEventsMap();
}
CUmsVTRCtrl::~CUmsVTRCtrl()
{
}

void  CUmsVTRCtrl::BuildEventsMap()
{
	REG_PFUN( ev_VcrAdd_rsp, OnAddVTRRsp );
	REG_PFUN( ev_VcrDel_rsp, OnDelVTRRsp );
	REG_PFUN( ev_VcrMdy_rsp, OnModifyVTRRsp );
	REG_PFUN( ev_Vcr_nty, OnVTRNty );
	

	REG_PFUN( ev_rec_base_info_nty, OnRecBaseInfoNty );
	REG_PFUN( ev_rec_reg_status_nty, OnRecRegStatusNty );
	REG_PFUN( ev_rec_file_list_info, OnRecFileListInfoNty );
	REG_PFUN( ev_rec_conf_rec_info, OnRecConfRecInfoNty );
	REG_PFUN( ev_rec_conf_play_info, OnRecConfPlayInfoNty );
	

	REG_PFUN( ev_rec_mdy_file_nack, OnRecMdyFileNack );
	REG_PFUN( ev_rec_mdy_file_ack, OnRecMdyFileAck );
	

	REG_PFUN( ev_rec_recorder_conf_rsp, OnRecStartConfRsp );
	REG_PFUN( ev_rec_pause_conf_rsp, OnRecPauseConfRsp );
	REG_PFUN( ev_rec_resume_conf_rsp, OnRecResumeConfRsp );
	REG_PFUN( ev_rec_stop_recorder_rsp, OnRecStopConfRsp );
	
	REG_PFUN( ev_rec_start_play_rsp, OnRecStartPlayRsp );
	REG_PFUN( ev_rec_pause_play_rsp, OnRecPausePlayRsp );
	REG_PFUN( ev_rec_resume_play_rsp, OnRecResumePlayRsp );
	REG_PFUN( ev_rec_stop_play_rsp, OnRecStopPlayRsp );

	REG_PFUN(evtp_HungUpConf_result, OnHungUpConfRsp ); 

	REG_PFUN(ev_rec_mt_format_rsp, OnMtFormatRsp ); 
	

    //断链清空资源
    REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
}



u16  CUmsVTRCtrl::VTRAddReq( const TVcrCfg& tVTRCfg )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_VcrAdd_req );
	pcTpMsg->SetBody( &tVTRCfg, sizeof(TVcrCfg) );
 	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tVTRCfg.m_dwIP;
	PrtMsg( ev_VcrAdd_req, emEventTypeUmstoolSend,  
		_T("Name: %s, No: %d, IP: %s"), tVTRCfg.m_achName, tVTRCfg.m_byEqpID, inet_ntoa(tAddr) );

	return wRet;
}

u16  CUmsVTRCtrl::VTRModifyReq( const TVcrCfg& tVTRCfgOld, const TVcrCfg& tVTRCfgNew )
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_VcrMdy_req );
	pcTpMsg->SetBody( &tVTRCfgOld, sizeof(TVcrCfg) );
	pcTpMsg->CatBody( &tVTRCfgNew, sizeof(TVcrCfg) );
 	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddrOld;
	in_addr tAddrNew;
	tAddrOld.S_un.S_addr = tVTRCfgOld.m_dwIP;
	tAddrNew.S_un.S_addr = tVTRCfgNew.m_dwIP;
	PrtMsg( ev_VcrMdy_req, emEventTypeUmstoolSend, 
		_T("tVTRCfgOld: Name: %s, No: %d, IP: %s; tVTRCfgNew: Name: %s, No: %d, IP: %s"),
						tVTRCfgOld.m_achName, tVTRCfgOld.m_byEqpID, inet_ntoa(tAddrOld),
						tVTRCfgNew.m_achName, tVTRCfgNew.m_byEqpID, inet_ntoa(tAddrNew));

	return wRet;
}

u16  CUmsVTRCtrl::VTRDeleteReq( const TVcrCfg& tVTRCfg )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_VcrDel_req );
	pcTpMsg->SetBody( &tVTRCfg, sizeof(TVcrCfg) );
 	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tVTRCfg.m_dwIP;
	PrtMsg( ev_VcrMdy_req, emEventTypeUmstoolSend, 
		_T("Name: %s, No: %d, IP: %s"), tVTRCfg.m_achName, tVTRCfg.m_byEqpID, inet_ntoa(tAddr) );

	return wRet;
}

u16 CUmsVTRCtrl::GetUmsVTRData( TVcrCfg& tVTRCfg )
{
	int nNum = m_vecTVTRCfg.size();

	if ( nNum > 0 )
	{
		tVTRCfg = m_vecTVTRCfg[0];
	}

	return NO_ERROR;
}

u16 CUmsVTRCtrl::GetUmsVTRData( vector<TVcrCfg> &vecTVcrCfg )
{
	vecTVcrCfg = m_vecTVTRCfg;
	return NO_ERROR;
}


void  CUmsVTRCtrl::OnAddVTRRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyVcrRet emRet = *reinterpret_cast<EmModifyVcrRet*>( kdvMsg.GetBody() );

	if ( emRet == em_vcr_modify_success )
	{
		TVcrCfg tVcrCfg = *reinterpret_cast<TVcrCfg*>( kdvMsg.GetBody() + sizeof(EmModifyVcrRet) );
		m_vecTVTRCfg.push_back(tVcrCfg);
	}

	PrtMsg( ev_VcrAdd_rsp, emEventTypeUmstoolRecv, "EmModifyVcrRet = %d", emRet );
	PostEvent( UI_UMSTOOL_ADD_VTR_RSP, (WPARAM)emRet );
}

void  CUmsVTRCtrl::OnDelVTRRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyVcrRet emRet = *reinterpret_cast<EmModifyVcrRet*>( kdvMsg.GetBody() );

	if ( emRet == em_vcr_modify_success )
	{
		TVcrCfg tVcrCfg = *reinterpret_cast<TVcrCfg*>( kdvMsg.GetBody() + sizeof(EmModifyVcrRet) );
		vector<TVcrCfg>::iterator it;
		for ( it = m_vecTVTRCfg.begin(); it != m_vecTVTRCfg.end(); )
		{
			if ( tVcrCfg.m_byEqpID == it->m_byEqpID )
			{
				it = m_vecTVTRCfg.erase(it);
				break;
			}
			it++;
		}
	}

	PrtMsg( ev_VcrDel_rsp, emEventTypeUmstoolRecv, "EmModifyVcrRet = %d", emRet );    
	PostEvent( UI_UMSTOOL_DEL_VTR_RSP, (WPARAM)emRet );
}

void  CUmsVTRCtrl::OnModifyVTRRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyVcrRet emRet = *reinterpret_cast<EmModifyVcrRet*>( kdvMsg.GetBody() );
	TVcrCfg tVcrCfg = *reinterpret_cast<TVcrCfg*>( kdvMsg.GetBody() + sizeof(EmModifyVcrRet) );

	if ( emRet == em_vcr_modify_success )
	{
		vector<TVcrCfg>::iterator it;
		for ( it = m_vecTVTRCfg.begin(); it != m_vecTVTRCfg.end(); it++ )
		{
			*it = tVcrCfg;
			break;
		}
	}

	PrtMsg( ev_VcrMdy_rsp, emEventTypeUmstoolRecv, "EmModifyVcrRet = %d", emRet );
	PostEvent( UI_UMSTOOL_MODIFY_VTR_RSP, (WPARAM)emRet, (LPARAM)&tVcrCfg );
}

void  CUmsVTRCtrl::OnVTRNty(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	u16 wNum = *reinterpret_cast<u16*>( kdvMsg.GetBody() );
	int nT = sizeof(TVcrCfg);
	int nTotal = kdvMsg.GetBodyLen();
	
	m_vecTVTRCfg.clear();

	for ( int n = 0; n < wNum; n++ )
	{
		TVcrCfg tVcrCfg = *reinterpret_cast<TVcrCfg*>( kdvMsg.GetBody() + sizeof(u16) + n*sizeof(TVcrCfg) );
		m_vecTVTRCfg.push_back( tVcrCfg );
	}

	//录像机配置数为0，清空所有录像机信息
	if ( wNum == 0 )
	{
		m_vecTRecBaseInfo.clear();
		m_vecTRecFileInfo.clear();
		m_vecTRecFileInfoNoSuffix.clear();
		m_nLeft = 0;
		m_vecTConRecState.clear();
		m_vecTConfPlayStatus.clear();

		PostEvent( UI_UMSTOOL_REC_BASE_INFO_NTY, NULL, NULL );
		PostEvent( UI_UMSTOOL_REC_FILE_LIST_INFO_NTY, NULL, NULL );
		PostEvent( UI_UMSTOOL_REC_CONF_REC_INFO_NTY, NULL, NULL );
		PostEvent( UI_UMSTOOL_REC_CONF_PLAY_INFO_NTY, NULL, NULL );
	}
	
	

	PrtMsg( ev_Vcr_nty, emEventTypeUmstoolRecv, _T("ev_NMServer_nty, nNum: %d"), wNum );
	PostEvent( UI_UMSTOOL_VTR_NTY, NULL, NULL );
}

u16 CUmsVTRCtrl::GetVtrRegState( BOOL32 &bRegState )
{
	bRegState = m_bRegState;
	return NO_ERROR;
}

void CUmsVTRCtrl::OnRecBaseInfoNty(const CMessage& cMsg)
{
	m_vecTRecBaseInfo.clear();

	CTpMsg kdvMsg( &cMsg );
	TRecBaseInfo tRecBaseInfo1 = *reinterpret_cast<TRecBaseInfo*>( kdvMsg.GetBody() );
	TRecBaseInfo tRecBaseInfo2 = *reinterpret_cast<TRecBaseInfo*>( kdvMsg.GetBody() + sizeof(TRecBaseInfo) );
	m_vecTRecBaseInfo.push_back(tRecBaseInfo1);
	m_vecTRecBaseInfo.push_back(tRecBaseInfo2);

	if ( tRecBaseInfo1.m_achName[0] != '\0' )
	{
		m_bRegState = TRUE;
	}
	
	PrtMsg( ev_rec_base_info_nty, emEventTypeUmstoolRecv, _T("tRecBaseInfo1: Name: %s, FreeSize: %d, TotalSize: %d tRecBaseInfo2: Name: %s, FreeSize: %d, TotalSize: %d"),
			tRecBaseInfo1.m_achName, tRecBaseInfo1.m_dwFreeSize, tRecBaseInfo1.m_dwTotalSize,
			tRecBaseInfo2.m_achName, tRecBaseInfo2.m_dwFreeSize, tRecBaseInfo2.m_dwTotalSize );
	PostEvent( UI_UMSTOOL_REC_BASE_INFO_NTY, NULL, NULL );
}

u16 CUmsVTRCtrl::GetRecBaseInfo( vector<TRecBaseInfo> &vecTRecBaseInfo )
{
	vecTRecBaseInfo = m_vecTRecBaseInfo;
	return NO_ERROR;
}

void CUmsVTRCtrl::OnRecRegStatusNty(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	u8 nID = *reinterpret_cast<u8*>( kdvMsg.GetBody() );
	m_bRegState = *reinterpret_cast<BOOL32*>( kdvMsg.GetBody() + sizeof(u8) );

	if ( m_bRegState == FALSE )
	{
		m_vecTRecBaseInfo.clear();
		m_vecTRecFileInfo.clear();
		m_vecTRecFileInfoNoSuffix.clear();
		m_nLeft = 0;
		m_vecTConRecState.clear();
		m_vecTConfPlayStatus.clear();
		
		PostEvent( UI_UMSTOOL_REC_BASE_INFO_NTY, NULL, NULL );
		PostEvent( UI_UMSTOOL_REC_FILE_LIST_INFO_NTY, NULL, NULL );
		PostEvent( UI_UMSTOOL_REC_CONF_REC_INFO_NTY, NULL, NULL );
		PostEvent( UI_UMSTOOL_REC_CONF_PLAY_INFO_NTY, NULL, NULL );
	}
	
	PrtMsg( ev_rec_reg_status_nty, emEventTypeUmstoolRecv, _T("EqpID: %d, m_bRegState: %d"), nID, m_bRegState );

	PostEvent( UI_UMSTOOL_VTR_REG_STATE_NTY, NULL, NULL );
}

//每200条刷新一次
#define FILE_LIST_REFRESH_SIZE		200
void CUmsVTRCtrl::OnRecFileListInfoNty(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	TRecFileListInfo tRecFileListInfo = *reinterpret_cast<TRecFileListInfo*>( kdvMsg.GetBody() );

	if ( m_nLeft == 0 )
	{
		m_vecTRecFileInfo.clear();
	}

	for ( int n = 0; n < tRecFileListInfo.m_wCurSize; n++ )
	{
		TRecFileInfo tVtrFileInfo;
		tVtrFileInfo.m_byEqpID = tRecFileListInfo.m_byEqpID;
		if ( tRecFileListInfo.m_achFileName[n][0] == '\0' )
		{
			continue;
		}
		strncpy( tVtrFileInfo.m_szFilelName, tRecFileListInfo.m_achFileName[n], TP_REC_FILE_LEN );
		m_vecTRecFileInfo.push_back(tVtrFileInfo);
	}

	SetRecFileListNoSuffix();
	
	int nSize = m_vecTRecFileInfo.size();
	m_nLeft = tRecFileListInfo.m_wTotalSize - nSize;
	
	
	PrtMsg( ev_rec_file_list_info, emEventTypeUmstoolRecv, _T("ev_rec_file_list_info, byEqpID: %d, TotalSize: %d, CurSize: %d, achFileName:%s"),
		tRecFileListInfo.m_byEqpID, tRecFileListInfo.m_wTotalSize, tRecFileListInfo.m_wCurSize, tRecFileListInfo.m_achFileName );

	int nSizeBefore = (nSize - tRecFileListInfo.m_wCurSize) % FILE_LIST_REFRESH_SIZE;

	if ( m_nLeft == 0 )
	{
		PostEvent( UI_UMSTOOL_REC_FILE_LIST_INFO_NTY, NULL, NULL );
	}
	else if ( nSizeBefore < FILE_LIST_REFRESH_SIZE && (nSizeBefore + tRecFileListInfo.m_wCurSize) > FILE_LIST_REFRESH_SIZE )
	{
		PostEvent( UI_UMSTOOL_REC_FILE_LIST_INFO_NTY, NULL, NULL );
	}
}

u16 CUmsVTRCtrl::GetRecFileListInfo( vector<TRecFileInfo> &vecTVtrFileInfo )
{
	vecTVtrFileInfo = m_vecTRecFileInfo;
	
	return NO_ERROR;
}

u16 CUmsVTRCtrl::GetRecFileListInfoNoSuffix( vector<TRecFileInfo> &vecTVtrFileInfoNoSuffix )
{
	vecTVtrFileInfoNoSuffix = m_vecTRecFileInfoNoSuffix;
	
	return NO_ERROR;
}

u16 CUmsVTRCtrl::RecDelFileReq( const TRecFileInfo& tRecFileInfo )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_rec_del_file_req );

	TRecFileInfo tRecFileInfoDel;
	TRecFileInfoNoSuffix2TRecFileInfo( tRecFileInfo, tRecFileInfoDel);
	

	pcTpMsg->SetBody( &tRecFileInfoDel, sizeof(TRecFileInfo) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_rec_del_file_req, emEventTypeUmstoolSend, 
		_T("byEqpID: %d, szFilelName: %s"), tRecFileInfoDel.m_byEqpID, tRecFileInfoDel.m_szFilelName );

	if (wRet == NO_ERROR)
	{
		vector<TRecFileInfo>::iterator it = m_vecTRecFileInfo.begin();
		for ( ; it != m_vecTRecFileInfo.end(); it++ )
		{
			if( it->m_byEqpID == tRecFileInfo.m_byEqpID 
				&& strcmp( it->m_szFilelName, tRecFileInfoDel.m_szFilelName ) == 0 )
			{
				m_vecTRecFileInfo.erase(it);
				break;
			}
		}

		SetRecFileListNoSuffix();

		PostEvent( UI_UMSTOOL_REC_DEL_FILE_RSP, NULL, TRUE );
	}
	else
	{
		PostEvent( UI_UMSTOOL_REC_DEL_FILE_RSP, NULL, FALSE );
	}
	
	return wRet;
}

u16 CUmsVTRCtrl::RecMdyFileReq( const TRecFileInfo& tRecFileInfoNoSuffixOld, const TRecFileInfo& tRecFileInfoNoSuffixNew )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_rec_mdy_file_req );

	TRecFileInfo tRecFileInfoOld;
	TRecFileInfoNoSuffix2TRecFileInfo( tRecFileInfoNoSuffixOld, tRecFileInfoOld );
	

	TRecFileInfo tRecFileInfoNew;
	tRecFileInfoNew.m_byEqpID = tRecFileInfoNoSuffixOld.m_byEqpID;
	CString strFileNameOld = tRecFileInfoOld.m_szFilelName;
	CString strPreSuffix = strFileNameOld.Left( strFileNameOld.ReverseFind('+') + 1 );
	CString strSuffix = strFileNameOld.Right( strFileNameOld.GetLength() - strFileNameOld.Find("_255_") );
	CString strFileNameNew;
	strFileNameNew = strPreSuffix + tRecFileInfoNoSuffixNew.m_szFilelName + strSuffix;
	strncpy( tRecFileInfoNew.m_szFilelName, strFileNameNew, TP_REC_FILE_LEN);
	tRecFileInfoNew.m_szFilelName[TP_REC_FILE_LEN-1] = '\0';

	pcTpMsg->SetBody( &tRecFileInfoOld, sizeof(TRecFileInfo) );
	pcTpMsg->CatBody( &tRecFileInfoNew, sizeof(TRecFileInfo) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_rec_mdy_file_req, emEventTypeUmstoolSend, 
		_T("tRecFileInfoOld: byEqpID: %d, szFilelName: %s, tRecFileInfoNew: byEqpID: %d, szFilelName: %s"),
		tRecFileInfoOld.m_byEqpID, tRecFileInfoOld.m_szFilelName,
		tRecFileInfoNew.m_byEqpID, tRecFileInfoNew.m_szFilelName );
	
	return wRet;
}

void CUmsVTRCtrl::OnRecMdyFileNack(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	TRecFileInfo arrTRecFileInfo[2];
	arrTRecFileInfo[0] = *reinterpret_cast<TRecFileInfo*>( kdvMsg.GetBody() );
	arrTRecFileInfo[1] = *reinterpret_cast<TRecFileInfo*>( kdvMsg.GetBody() + sizeof(TRecFileInfo) );

	PrtMsg( ev_rec_mdy_file_nack, emEventTypeUmstoolRecv, _T("") );
	PostEvent( UI_UMSTOOL_REC_MDY_FILE_RSP, (WPARAM)&arrTRecFileInfo, FALSE );
}

void CUmsVTRCtrl::OnRecMdyFileAck(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	TRecFileInfo arrTRecFileInfo[2];
	arrTRecFileInfo[0] = *reinterpret_cast<TRecFileInfo*>( kdvMsg.GetBody() );
	arrTRecFileInfo[1] = *reinterpret_cast<TRecFileInfo*>( kdvMsg.GetBody() + sizeof(TRecFileInfo) );

	
	vector<TRecFileInfo>::iterator it = m_vecTRecFileInfo.begin();
	for ( ; it != m_vecTRecFileInfo.end(); it++ )
	{
		if ( it->m_byEqpID == arrTRecFileInfo[0].m_byEqpID &&
			strncmp( it->m_szFilelName, arrTRecFileInfo[0].m_szFilelName, TP_REC_FILE_LEN ) == 0 )
		{
			strncpy( it->m_szFilelName, arrTRecFileInfo[1].m_szFilelName, TP_REC_FILE_LEN );
			break;
		}
	}

	SetRecFileListNoSuffix();

	TRecFileInfo arrTRecFileInfoNoSuffix[2];
	for ( int n = 0; n < 2; n++ )
	{
		arrTRecFileInfoNoSuffix[n].m_byEqpID = arrTRecFileInfo[n].m_byEqpID;
		CString strFileName = arrTRecFileInfo[n].m_szFilelName;
		strncpy( arrTRecFileInfoNoSuffix[n].m_szFilelName, (LPCTSTR)strFileName.Mid(strFileName.ReverseFind('+') + 1,strFileName.Find("_255_")-strFileName.ReverseFind('+')-1), TP_REC_FILE_LEN );
		arrTRecFileInfoNoSuffix[n].m_szFilelName[TP_REC_FILE_LEN] = '\0';
	}
	
	PrtMsg( ev_rec_mdy_file_ack, emEventTypeUmstoolRecv, _T("") );
	PostEvent( UI_UMSTOOL_REC_MDY_FILE_RSP, (WPARAM)&arrTRecFileInfoNoSuffix, TRUE );
}

void CUmsVTRCtrl::OnRecConfRecInfoNty(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	TConRecState tConRecState = *reinterpret_cast<TConRecState*>( kdvMsg.GetBody() );

	
	bool bFind = false;
	
	vector<TConRecState>::iterator it = m_vecTConRecState.begin();
	for ( ; it != m_vecTConRecState.end(); it++ )
	{
		if ( it->m_tInfo.m_wConfID == tConRecState.m_tInfo.m_wConfID
			&& it->m_tInfo.m_emType == em_rec_recorder_conf
			&& tConRecState.m_tInfo.m_emType == em_rec_recorder_conf )
		{
			*it = tConRecState;
			bFind = true;
			break;
		}

		if ( it->m_tInfo.m_wConfID == tConRecState.m_tInfo.m_wConfID
			&& it->m_tInfo.m_tMtRecInfo.m_wMtID == tConRecState.m_tInfo.m_tMtRecInfo.m_wMtID
			&& it->m_tInfo.m_emType == em_rec_recorder_mt
			&& tConRecState.m_tInfo.m_emType == em_rec_recorder_mt )
		{
			*it = tConRecState;
			bFind = true;
			break;
		}
	}
	
	if ( !bFind )
	{
		m_vecTConRecState.push_back( tConRecState );
	}

// 	//录像结束添加到文件列表
// 	if ( tConRecState.m_emState == em_rec_finish )
// 	{
// 		TRecFileInfo tRecFileInfo;
// 		tRecFileInfo.m_byEqpID = tConRecState.m_tInfo.m_byEqpID;
// 		strncpy( tRecFileInfo.m_szFilelName, tConRecState.m_tInfo.m_achFileName, TP_REC_FILE_LEN );
// 		tRecFileInfo.m_szFilelName[TP_REC_FILE_LEN-1] = '\0';
// 
// 		m_vecTRecFileInfo.push_back( tRecFileInfo );
// 
// 		SetRecFileListNoSuffix();
// 
// 		PostEvent( UI_UMSTOOL_REC_FILE_LIST_INFO_NTY, NULL, NULL );
// 	}
	
	
	PrtMsg( ev_rec_conf_rec_info, emEventTypeUmstoolRecv,
		_T("m_byEqpID:%d, m_wConfID,%d, m_tMtRecInfo:%d, m_emState:%d, m_dwRecTime:%d"),
		tConRecState.m_tInfo.m_byEqpID, tConRecState.m_tInfo.m_wConfID, tConRecState.m_tInfo.m_tMtRecInfo.m_wMtID, tConRecState.m_emState, tConRecState.m_dwRecTime );
	PostEvent( UI_UMSTOOL_REC_CONF_REC_INFO_NTY, NULL, NULL );
}

void CUmsVTRCtrl::OnRecConfPlayInfoNty(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	TConfPlayStatus tConfPlayStatus = *reinterpret_cast<TConfPlayStatus*>( kdvMsg.GetBody() );
	
	CString strPlayName = GetNoSuffixString( tConfPlayStatus.m_tInfo.m_szFileName );
	if ( strPlayName == "" )
	{
		ASSERT(0);
	}
	
	strncpy( tConfPlayStatus.m_tInfo.m_szFileName, strPlayName, TP_REC_FILE_LEN );
	(tConfPlayStatus.m_tInfo.m_szFileName)[TP_REC_FILE_LEN-1] = '\0';

	bool bFind = false;
	
	vector<TConfPlayStatus>::iterator it = m_vecTConfPlayStatus.begin();
	for ( ; it != m_vecTConfPlayStatus.end(); it++ )
	{
		if ( it->m_tInfo.m_wConfID == tConfPlayStatus.m_tInfo.m_wConfID )
		{
			*it = tConfPlayStatus;

			bFind = true;
			break;
		}
	}
	
	if ( !bFind )
	{
		m_vecTConfPlayStatus.push_back( tConfPlayStatus );
	}
	
	PrtMsg( ev_rec_conf_play_info, emEventTypeUmstoolRecv, _T("") );
	PostEvent( UI_UMSTOOL_REC_CONF_PLAY_INFO_NTY, NULL, NULL );
}

u16 CUmsVTRCtrl::RecStartConfReq( const TRecConfInfo& tRecConfInfo )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}

	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_rec_recorder_conf_req );
	pcTpMsg->SetBody( &tRecConfInfo, sizeof(TRecConfInfo) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_rec_recorder_conf_req, emEventTypeUmstoolSend, 
		_T("m_wConfID:%d m_wMtID:%d m_achFileName:%s"), tRecConfInfo.m_wConfID, tRecConfInfo.m_tMtRecInfo.m_wMtID, tRecConfInfo.m_achFileName );
	
	return wRet;
}

void CUmsVTRCtrl::OnRecStartConfRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	TRecConfRes tRecConfRes = *reinterpret_cast<TRecConfRes*>( kdvMsg.GetBody() );
	EmUseReccorderRes emRet = *reinterpret_cast<EmUseReccorderRes*>( kdvMsg.GetBody() + sizeof(TRecConfRes) );
	
	if ( emRet == em_rec_success )
	{
		TConRecState* pTConRecState = FindRecInfo( tRecConfRes );
		if ( pTConRecState != NULL )
		{
			pTConRecState->m_emState = em_rec_working;
		}
	}
	
	PrtMsg( ev_rec_recorder_conf_rsp, emEventTypeUmstoolRecv, 
		_T("m_byEqpID:%d, m_wConfID:%d, m_wMtID:%d, m_emType:%d, emRet:%d"),
		tRecConfRes.m_byEqpID, tRecConfRes.m_wConfID, tRecConfRes.m_wMtID, tRecConfRes.m_emType, emRet );
	PostEvent( UI_UMSTOOL_REC_START_CONF_RSP, NULL, (LPARAM)emRet );
}

TConRecState* CUmsVTRCtrl::FindRecInfo( TRecConfRes tRecConfRes )
{
	vector<TConRecState>::iterator it = m_vecTConRecState.begin();
	for ( ; it != m_vecTConRecState.end(); it++ )
	{
		if ( it->m_tInfo.m_wConfID == tRecConfRes.m_wConfID && it->m_tInfo.m_tMtRecInfo.m_wMtID == tRecConfRes.m_wMtID )
		{
			return it;
		}
	}

	return NULL;
}

TConfPlayStatus* CUmsVTRCtrl::FindPlayInfo( TPlayStatusMdyInfo& tPlayStatusMdyInfo )
{
	vector<TConfPlayStatus>::iterator it = m_vecTConfPlayStatus.begin();
	for ( ; it != m_vecTConfPlayStatus.end(); it++ )
	{
		if ( it->m_tInfo.m_wConfID == tPlayStatusMdyInfo.m_wConfID )
		{
			return it;
		}
	}
	
	return NULL;
}

u16 CUmsVTRCtrl::RecPauseConfReq( const TRecConfRes& tRecConfRes )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}

	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_rec_pause_conf_req );
	pcTpMsg->SetBody( &tRecConfRes, sizeof(TRecConfRes) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_rec_pause_conf_req, emEventTypeUmstoolSend, 
		_T("m_wConfID:%d m_wMtID:%d"), tRecConfRes.m_wConfID, tRecConfRes.m_wMtID );
	
	return wRet;
}

void CUmsVTRCtrl::OnRecPauseConfRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	TRecConfRes tRecConfRes = *reinterpret_cast<TRecConfRes*>( kdvMsg.GetBody() );
	EmUseReccorderRes emRet = *reinterpret_cast<EmUseReccorderRes*>( kdvMsg.GetBody() + sizeof(TRecConfRes) );

	if ( emRet == em_rec_success )
	{
		TConRecState* pTConRecState = FindRecInfo( tRecConfRes );
		if ( pTConRecState != NULL )
		{
			pTConRecState->m_emState = em_rec_pause;
		}
	}
	
	PrtMsg( ev_rec_pause_conf_rsp, emEventTypeUmstoolRecv, _T("emRet:%d"), emRet );
	PostEvent( UI_UMSTOOL_REC_PAUSE_CONF_RSP, NULL, (LPARAM)emRet );
}

u16 CUmsVTRCtrl::RecResumeConfReq( const TRecConfRes& tRecConfRes )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}
	
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_rec_resume_conf_req );
	pcTpMsg->SetBody( &tRecConfRes, sizeof(TRecConfRes) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_rec_resume_conf_req, emEventTypeUmstoolSend, 
		_T("m_wConfID:%d m_wMtID:%d"), tRecConfRes.m_wConfID, tRecConfRes.m_wMtID );
	
	return wRet;
}

void CUmsVTRCtrl::OnRecResumeConfRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	TRecConfRes tRecConfRes = *reinterpret_cast<TRecConfRes*>( kdvMsg.GetBody() );
	EmUseReccorderRes emRet = *reinterpret_cast<EmUseReccorderRes*>( kdvMsg.GetBody() + sizeof(TRecConfRes) );

	if ( emRet == em_rec_success )
	{
		TConRecState* pTConRecState = FindRecInfo( tRecConfRes );
		if ( pTConRecState != NULL )
		{
			pTConRecState->m_emState = em_rec_working;
		}
	}
	
	PrtMsg( ev_rec_resume_conf_rsp, emEventTypeUmstoolRecv, _T("emRet:%d"), emRet );
	PostEvent( UI_UMSTOOL_REC_RESUME_CONF_RSP, NULL, (LPARAM)emRet );
}

u16 CUmsVTRCtrl::RecStopConfReq( const TRecConfRes& tRecConfRes )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}
	
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_rec_stop_recorder_req );
	pcTpMsg->SetBody( &tRecConfRes, sizeof(TRecConfRes) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_rec_stop_recorder_req, emEventTypeUmstoolSend, 
		_T("m_wConfID:%d m_wMtID:%d"), tRecConfRes.m_wConfID, tRecConfRes.m_wMtID );
	
	return wRet;
}

void CUmsVTRCtrl::OnRecStopConfRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	TRecConfRes tRecConfRes = *reinterpret_cast<TRecConfRes*>( kdvMsg.GetBody() );
	EmUseReccorderRes emRet = *reinterpret_cast<EmUseReccorderRes*>( kdvMsg.GetBody() + sizeof(TRecConfRes) );

	if ( emRet == em_rec_success )
	{
		TConRecState* pTConRecState = FindRecInfo( tRecConfRes );
		if ( pTConRecState != NULL )
		{
			pTConRecState->m_emState = em_rec_finish;
		}
	}
	
	PrtMsg( ev_rec_stop_recorder_rsp, emEventTypeUmstoolRecv, _T("emRet:%d"), emRet );
	PostEvent( UI_UMSTOOL_REC_STOP_CONF_RSP, NULL, (LPARAM)emRet );
}

u16 CUmsVTRCtrl::RecStartPlayReq( const TRecPlayInfo& tRecPlayInfoNoSuffix )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}
	
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_rec_start_play_req );

	TRecFileInfo tRecFileInfo = FindFileName( tRecPlayInfoNoSuffix.m_szFileName );
	TRecPlayInfo tRecPlayInfo = tRecPlayInfoNoSuffix;
	strncpy( tRecPlayInfo.m_szFileName, tRecFileInfo.m_szFilelName, TP_REC_FILE_LEN );
	tRecPlayInfo.m_szFileName[TP_REC_FILE_LEN-1] = '\0';
	
	pcTpMsg->SetBody( &tRecPlayInfo, sizeof(TRecPlayInfo) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_rec_start_play_req, emEventTypeUmstoolSend, _T("m_szFileName:%s"), tRecPlayInfo.m_szFileName );
	
	return wRet;
}

void CUmsVTRCtrl::OnRecStartPlayRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	TRecPlayInfo tRecPlayInfo = *reinterpret_cast<TRecPlayInfo*>( kdvMsg.GetBody() );
	EmUseReccorderRes emRet = *reinterpret_cast<EmUseReccorderRes*>( kdvMsg.GetBody() + sizeof(TRecPlayInfo) );

	if ( emRet == em_rec_success )
	{
		TPlayStatusMdyInfo tPlayStatusMdyInfo;
		tPlayStatusMdyInfo.m_byEqpID = tRecPlayInfo.m_byEqpID;
		tPlayStatusMdyInfo.m_wConfID = tRecPlayInfo.m_wConfID;


		TConfPlayStatus* pTConfPlayStatus = FindPlayInfo( tPlayStatusMdyInfo );
		if ( pTConfPlayStatus != NULL )
		{
			pTConfPlayStatus->m_emState = em_rec_working;
		}
	}
	
	
	PrtMsg( ev_rec_start_play_rsp, emEventTypeUmstoolRecv, _T("emRet:%d"), emRet );
	PostEvent( UI_UMSTOOL_START_PLAY_RSP, NULL, (LPARAM)emRet );
}

u16 CUmsVTRCtrl::RecPausePlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}
	
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_rec_pause_play_req );
	pcTpMsg->SetBody( &tPlayStatusMdyInfo, sizeof(TPlayStatusMdyInfo) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_rec_pause_play_req, emEventTypeUmstoolSend, _T("m_wConfID:%d"), tPlayStatusMdyInfo.m_wConfID );
	
	return wRet;
}

void CUmsVTRCtrl::OnRecPausePlayRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	TPlayStatusMdyInfo tPlayStatusMdyInfo = *reinterpret_cast<TPlayStatusMdyInfo*>( kdvMsg.GetBody() );
	EmUseReccorderRes emRet = *reinterpret_cast<EmUseReccorderRes*>( kdvMsg.GetBody() + sizeof(TPlayStatusMdyInfo) );
	
	if ( emRet == em_rec_success )
	{
		TConfPlayStatus* pTConfPlayStatus = FindPlayInfo( tPlayStatusMdyInfo );
		if ( pTConfPlayStatus != NULL )
		{
			pTConfPlayStatus->m_emState = em_rec_pause;
		}
	}
	
	
	PrtMsg( ev_rec_pause_play_rsp, emEventTypeUmstoolRecv, _T("emRet:%d"), emRet );
	PostEvent( UI_UMSTOOL_PAUSE_PLAY_RSP, NULL, (LPARAM)emRet );
}

u16 CUmsVTRCtrl::RecResumePlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}
	
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_rec_resume_play_req );
	pcTpMsg->SetBody( &tPlayStatusMdyInfo, sizeof(TPlayStatusMdyInfo) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_rec_resume_play_req, emEventTypeUmstoolSend, _T("m_wConfID:%d"), tPlayStatusMdyInfo.m_wConfID );
	
	return wRet;
}

void CUmsVTRCtrl::OnRecResumePlayRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	TPlayStatusMdyInfo tPlayStatusMdyInfo = *reinterpret_cast<TPlayStatusMdyInfo*>( kdvMsg.GetBody() );
	EmUseReccorderRes emRet = *reinterpret_cast<EmUseReccorderRes*>( kdvMsg.GetBody() + sizeof(TPlayStatusMdyInfo) );
	
	if ( emRet == em_rec_success )
	{
		TConfPlayStatus* pTConfPlayStatus = FindPlayInfo( tPlayStatusMdyInfo );
		if ( pTConfPlayStatus != NULL )
		{
			pTConfPlayStatus->m_emState = em_rec_working;
		}
	}
	
	PrtMsg( ev_rec_resume_play_rsp, emEventTypeUmstoolRecv, _T("emRet:%d"), emRet );
	PostEvent( UI_UMSTOOL_RESUME_PLAY_RSP, NULL, (LPARAM)emRet );
}

u16 CUmsVTRCtrl::RecStopPlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}
	
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_rec_stop_play_req );
	pcTpMsg->SetBody( &tPlayStatusMdyInfo, sizeof(TPlayStatusMdyInfo) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_rec_stop_play_req, emEventTypeUmstoolSend, _T("m_wConfID:%d"), tPlayStatusMdyInfo.m_wConfID );
	
	return wRet;
}

void CUmsVTRCtrl::OnRecStopPlayRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	TPlayStatusMdyInfo tPlayStatusMdyInfo = *reinterpret_cast<TPlayStatusMdyInfo*>( kdvMsg.GetBody() );
	EmUseReccorderRes emRet = *reinterpret_cast<EmUseReccorderRes*>( kdvMsg.GetBody() + sizeof(TPlayStatusMdyInfo) );
	
	if ( emRet == em_rec_success )
	{
		TConfPlayStatus* pTConfPlayStatus = FindPlayInfo( tPlayStatusMdyInfo );
		if ( pTConfPlayStatus != NULL )
		{
			pTConfPlayStatus->m_emState = em_rec_finish;
		}
	}
	
	PrtMsg( ev_rec_stop_play_rsp, emEventTypeUmstoolRecv, _T("emRet:%d"), emRet );
	PostEvent( UI_UMSTOOL_STOP_PLAY_RSP, NULL, (LPARAM)emRet );
}


u16 CUmsVTRCtrl::GetRecConfInfo( vector<TConRecState>& vecTConRecState )
{
	vecTConRecState = m_vecTConRecState;
	return NO_ERROR;
}

u16 CUmsVTRCtrl::GetPlayConfInfo( vector<TConfPlayStatus>& vecTConfPlayStatus )
{
	vecTConfPlayStatus = m_vecTConfPlayStatus;
	return NO_ERROR;
}

u16 CUmsVTRCtrl::GetEqpID( u8& byEqpID )
{
	vector<TVcrCfg>::iterator it = m_vecTVTRCfg.begin();
	for ( ; it != m_vecTVTRCfg.end(); it++ )
	{
		byEqpID = it->m_byEqpID;
		return NO_ERROR;
	}
	
	return NO_ERROR;
}

void CUmsVTRCtrl::OnLinkBreak( const CMessage& cMsg )
{
	m_vecTVTRCfg.clear();
	m_vecTRecBaseInfo.clear();
	m_vecTRecFileInfo.clear();
	m_vecTRecFileInfoNoSuffix.clear();
	m_vecTConRecState.clear();
	m_vecTConfPlayStatus.clear();

	m_bRegState = FALSE;
	m_nLeft = 0;
    
    PrtMsg( OSP_DISCONNECT,emEventTypeUmstoolRecv,"清空VTR信息");
//	PostEvent( OSP_DISCONNECT );
}

void CUmsVTRCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
    PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
}

void CUmsVTRCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CUmsVTRCtrl,cMsg);
}

void CUmsVTRCtrl::OnHungUpConfRsp( const CMessage& cMsg )
{  
	CTpMsg kdvMsg(&cMsg);
	u16 wConfID = * reinterpret_cast<u16*>( kdvMsg.GetBody() );
	EmTpDropConfRet emRe = *reinterpret_cast<EmTpDropConfRet*>( kdvMsg.GetBody() + sizeof(u16) );

	if ( emRe == TP_DropConf_Success )
	{
		vector<TConRecState>::iterator itRec = m_vecTConRecState.begin();
		for ( ; itRec != m_vecTConRecState.end(); )
		{
			if ( itRec->m_tInfo.m_wConfID == wConfID )
			{
				itRec = m_vecTConRecState.erase(itRec);
				break;
			}
			else
			{
				itRec++;
			}
		}

		vector<TConfPlayStatus>::iterator itPlay = m_vecTConfPlayStatus.begin();
		for ( ; itPlay != m_vecTConfPlayStatus.end(); itPlay++ )
		{
			if ( itPlay->m_tInfo.m_wConfID == wConfID )
			{
				m_vecTConfPlayStatus.erase(itPlay);
				break;
			}
		}
	}
	
    PrtMsg( evtp_HungUpConf_result,emEventTypeUmsRecv,"ConfID=%d, errCode=%d", wConfID, emRe ); 

	//PostEvent( UI_UMS_HANGUP_CONF_RSP, wConfID, emRe );
}

void CUmsVTRCtrl::SetRecFileListNoSuffix()
{
	m_vecTRecFileInfoNoSuffix.clear();
	vector<TRecFileInfo>::iterator it = m_vecTRecFileInfo.begin();
	for ( ; it != m_vecTRecFileInfo.end() ; it++ )
	{
		CString strFileNameNoSuffix = GetNoSuffixString( it->m_szFilelName );

		if ( strFileNameNoSuffix == "" )
		{
			continue;
		}

		TRecFileInfo tRecFileInfoNoSuffix;
		tRecFileInfoNoSuffix.m_byEqpID = it->m_byEqpID;
		strncpy( tRecFileInfoNoSuffix.m_szFilelName, strFileNameNoSuffix, TP_REC_FILE_LEN );
		tRecFileInfoNoSuffix.m_szFilelName[TP_REC_FILE_LEN-1] = '\0';
		m_vecTRecFileInfoNoSuffix.push_back(tRecFileInfoNoSuffix);
	}
}

TRecFileInfo CUmsVTRCtrl::FindFileName( CString strFileNameNoSuffix )
{
	TRecFileInfo tRecFileInfo;
	vector<TRecFileInfo>::iterator it = m_vecTRecFileInfo.begin();
	for ( ; it != m_vecTRecFileInfo.end() ; it++ )
	{
		CString strFilelName = it->m_szFilelName;
		CString strFileNameNoSuffixInList = GetNoSuffixString( strFilelName );
		if ( strFileNameNoSuffixInList == strFileNameNoSuffix )
		{
			tRecFileInfo = *it;
			break;
		}
	}

	return tRecFileInfo;
}

void CUmsVTRCtrl::TRecFileInfoNoSuffix2TRecFileInfo( const TRecFileInfo& tRecFileInfoNoSuffix, TRecFileInfo& tRecFileInfo )
{
	tRecFileInfo.Clear();

	CString strFileNameNoSuffix = tRecFileInfoNoSuffix.m_szFilelName;
	if ( strFileNameNoSuffix.Find("+A") == -1 && strFileNameNoSuffix.Find("_255_") == -1 )
	{
		tRecFileInfo = FindFileName( strFileNameNoSuffix );
	}

	if ( tRecFileInfo.m_szFilelName[0] == '\0')
	{
		ASSERT(0);
	}
}

CString CUmsVTRCtrl::GetNoSuffixString( CString strFileName )
{
	CString strFileNameNoSuffix;

	int nPosEnd = strFileName.Find("_255_");
	int nPosBegin = strFileName.ReverseFind('+');
	if ( nPosEnd != -1 && nPosBegin != -1 )
	{
		strFileNameNoSuffix = strFileName.Mid( nPosBegin+1, nPosEnd-nPosBegin-1 );
	}

	return strFileNameNoSuffix;
}

u16 CUmsVTRCtrl::RecMtFormatReq( const u16& wConfID, const u16& wMtID )
{
	if ( NULL == m_pUmsSession )
	{
		return ERR_CMS;
	}
	
	
	CTpMsg *pcTpMsg = m_pUmsSession->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_rec_mt_format );
	pcTpMsg->SetBody( &wConfID, sizeof(u16) );
	pcTpMsg->CatBody( &wMtID, sizeof(u16) );
	u16 wRet = m_pUmsSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_rec_mt_format, emEventTypeUmstoolSend, 
		_T("wConfID:%d wMtID:%d"), wConfID, wMtID );
	
	return wRet;
}

void CUmsVTRCtrl::OnMtFormatRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	TTPRecMtFormat tTPRecMtFormat = *reinterpret_cast<TTPRecMtFormat*>( kdvMsg.GetBody() );
	
	
	PrtMsg( ev_rec_mt_format_rsp, emEventTypeUmstoolRecv,
		_T("wConfID:%d wMtID:%d, bValid:%d, emFormat:%d, emRes:%d, wFrameRate:%d, wBitrate:%d, mQualityLvl:%d"), 
		tTPRecMtFormat.m_wConfID, tTPRecMtFormat.m_wMtID, tTPRecMtFormat.m_bValid, tTPRecMtFormat.m_tVidFormat.m_emFormat, 
		tTPRecMtFormat.m_tVidFormat.m_emRes, tTPRecMtFormat.m_tVidFormat.m_wFrameRate, tTPRecMtFormat.m_tVidFormat.m_wBitrate,
		tTPRecMtFormat.m_tVidFormat.m_emQualityLvl );
	PostEvent( UI_UMSTOOL_REC_MT_FORMAT_RSP, (WPARAM)&tTPRecMtFormat, NULL );
}
