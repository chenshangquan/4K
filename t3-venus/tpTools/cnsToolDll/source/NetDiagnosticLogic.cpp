// NetDiagnosticLogic.cpp: implementation of the CNetDiagnosticLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "kdvdispevent.h"
#include "NetDiagnosticLogic.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CNetDiagnosticLogic::CNetDiagnosticLogic()
: m_strLostPacket("StcLostPacket")
, m_strUpstream("StcUpstream")
, m_strDownstream("StcDownstream")
,m_bIsRecording(FALSE)
{
	
}

CNetDiagnosticLogic::~CNetDiagnosticLogic()
{
	
}

void CNetDiagnosticLogic::RegCBFun()
{
	CNetDiagnosticLogic *pThis =  GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CNetDiagnosticLogic::InitWnd", CNetDiagnosticLogic::InitWnd, pThis, CNetDiagnosticLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetDiagnosticLogic::OnBtnStatistic", CNetDiagnosticLogic::OnBtnStatistic, pThis, CNetDiagnosticLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetDiagnosticLogic::OnBtnRefresh", CNetDiagnosticLogic::OnBtnRefresh, pThis, CNetDiagnosticLogic );
}

void CNetDiagnosticLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CNetDiagnosticLogic::InitWnd" );	
}

bool CNetDiagnosticLogic::InitWnd(const IArgs & arg)
{
	CLogicBase::InitWnd( arg );
	UIFACTORYMGR_PTR->LoadScheme( "SchStartStatistics", m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagStatistic, false );
	return true;
}

void CNetDiagnosticLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		m_bIsRecording = FALSE;
		UIFACTORYMGR_PTR->LoadScheme( "SchStartStatistics", m_pWndTree );
	}
}

void CNetDiagnosticLogic::RegMsg()
{
	CNetDiagnosticLogic *pThis =  GetSingletonPtr(); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpDownstream_NTY, CNetDiagnosticLogic::OnUpDownstreamNty, pThis, CNetDiagnosticLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_LostPacket_Rsp, CNetDiagnosticLogic::OnLostPacketRsp, pThis, CNetDiagnosticLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CNetDiagnosticLogic::OnConfStateNty, pThis, CNetDiagnosticLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_StartRecorder_Nty, CNetDiagnosticLogic::OnRecordMes, pThis, CNetDiagnosticLogic );
}

void CNetDiagnosticLogic::UnRegMsg()
{
	
}

LRESULT CNetDiagnosticLogic::OnUpDownstreamNty(WPARAM wparam, LPARAM lparam)
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	
	TTPUpDownSpeedInfo tUpDownSpeedInfo;
	LIBDATAMGRPTR->GetUpDownstreamRate( tUpDownSpeedInfo );
	//上行速率
	s8 chUp[8] = {0};
	String strUpstream;
	if ( 1024 < tUpDownSpeedInfo.m_wUpSpeed )
	{
		float fUpSpeed = 1.0*tUpDownSpeedInfo.m_wUpSpeed/1024;
		sprintf( chUp, "%.1f", fUpSpeed );
		strUpstream = chUp;
		strUpstream += "Mpbs";
	}
	else
	{
		sprintf( chUp, "%u", tUpDownSpeedInfo.m_wUpSpeed );
		strUpstream = chUp;
		strUpstream += "Kpbs";
	}
	UIFACTORYMGR_PTR->SetCaption(m_strUpstream, strUpstream, m_pWndTree, true);
	//下行速率
	s8 chDown[8] = {0};
	String strDownstream;
	if ( 1024 < tUpDownSpeedInfo.m_wDownSpeed )
	{
		float fDownSpeed = 1.0*tUpDownSpeedInfo.m_wDownSpeed/1024;
		sprintf( chDown, "%.1f", fDownSpeed );
		strDownstream = chDown;
		strDownstream += "Mpbs";
	}
	else
	{
		sprintf( chDown, "%u", tUpDownSpeedInfo.m_wDownSpeed );
		strDownstream = chDown;
		strDownstream += "Kpbs";
	}
	UIFACTORYMGR_PTR->SetCaption(m_strDownstream, strDownstream, m_pWndTree, true);
	
	if ( m_bIsRecording == TRUE )
	{
		if ( m_cFile.m_hFile == (UINT)INVALID_HANDLE_VALUE )
		{
			return S_FALSE;
		}
		else
		{
			WriteToFile();
		}
	}
	
	return S_OK;
}

LRESULT CNetDiagnosticLogic::OnLostPacketRsp(WPARAM wparam, LPARAM lparam)
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	CString strLostPacketInfo;
	LIBDATAMGRPTR->GetLostPacketInfo( strLostPacketInfo );
	
	//s8 chLostPacket[8] ={0};
	//sprintf( chLostPacket, "%u", LostPacketInfo );
	String strLostInfo(strLostPacketInfo);
	strLostInfo += "%";
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->SetCaption(m_strLostPacket, strLostInfo, m_pWndTree, true);
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption(m_strLostPacket, "---", m_pWndTree, true);
	}
	return S_OK;
}

LRESULT CNetDiagnosticLogic::OnConfStateNty(WPARAM wparam, LPARAM lparam)
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if(!bInConf)
	{
		//没有会议的时候,丢包率显示---  石文娟确认
		UIFACTORYMGR_PTR->SetCaption(m_strLostPacket, "---", m_pWndTree, true);
	}
	return S_OK;
}

HRESULT CNetDiagnosticLogic::OnRecordMes(WPARAM wparam, LPARAM lparam)
{
	memcpy(&m_cFile,(CFile *)wparam,sizeof(m_cFile));
	
	if ( m_cFile.m_hFile == (UINT)INVALID_HANDLE_VALUE )
	{
		return S_FALSE;
	}
	
	m_bIsRecording	= TRUE;
	UIFACTORYMGR_PTR->LoadScheme( "SchEndOfStatistics", m_pWndTree );
	return S_OK;
}

void CNetDiagnosticLogic::WriteToFile()
{
	String  strLostInfo;
	String	strUpSpeed;
	String	strDownSpeed;
	
	UIFACTORYMGR_PTR->GetCaption(m_strLostPacket, strLostInfo, m_pWndTree);
	UIFACTORYMGR_PTR->GetCaption(m_strUpstream, strUpSpeed, m_pWndTree);
	UIFACTORYMGR_PTR->GetCaption(m_strDownstream, strDownSpeed, m_pWndTree);
	
	if ( m_cFile.m_hFile != (UINT)INVALID_HANDLE_VALUE )
	{
		String strRecord;
		
		SYSTEMTIME st;
		GetLocalTime(&st);  
		CString time = "";
		time.Format("%4d/%.2d/%.2d %.2d:%.2d:%.2d\n",
			st.wYear, st.wMonth,  st.wDay,
			st.wHour, st.wMinute, st.wSecond);
		
		strRecord	+=time;
		strRecord	+=" 丢包率："+ strLostInfo;
		strRecord	+=" 上传速率："+ strUpSpeed;
		strRecord	+=" 下载速率："+ strDownSpeed;
		strRecord	+="\r\n";
		m_cFile.Write( strRecord.c_str(), strRecord.size() );
	}
}

bool CNetDiagnosticLogic::OnBtnStatistic(const IArgs & arg)
{
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_Statistic_Nty, (WPARAM)&m_bIsRecording,NULL);
	
	if ( m_bIsRecording == TRUE )
	{
		m_bIsRecording = FALSE;
		UIFACTORYMGR_PTR->LoadScheme( "SchStartStatistics", m_pWndTree );
	}
	
	UIFACTORYMGR_PTR->Domodal( g_strDiagStatistic );
	return true;
}

bool CNetDiagnosticLogic::OnBtnRefresh(const IArgs & arg)
{
	COMIFMGRPTR->RefreshBasicInfo();
	return true;
}


