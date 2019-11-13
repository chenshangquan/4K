// sysinfologic.cpp: implementation of the CSysInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umstooldll.h"
#include "sysinfologic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

time_t g_timeDate = 0; 
u16 g_wTimerID = 0;             //服务器时间的timer 的handle
VOID CALLBACK CBTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime ); 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VOID CALLBACK CBTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{  
    if ( idEvent == g_wTimerID)
    {
		SYSINFOLOGICRPTR->UpdateServerTime();
	}
}

CSysInfoLogic::CSysInfoLogic():
m_strStcHardWareVer("StcHardWareVer"),  
m_strStcSoftWareVer("StcSoftWareVer"),  
m_strStcSipSevr("StcSipSevr"),  
m_strStcGkSevr("StcGkSevr"),  
m_strStcAuthCount("StcAuthCount"),  
m_strStcSysTimeValue("StcSysTimeValue"),  
m_strStcCpuRate("StcCpuRate"),  
m_strStcMemeryRate("StcMemeryRate"),  
m_strStcCoufCount("StcCoufCount"),  
m_strStcMixAudioPer("StcMixAudioPer"),  
m_strStcImageCompondPer("StcImageCompondPer"),
m_strStcTvwPer("StcTvwPer"),  
m_strStcSteamAdaptePer("StcSteamAdaptePer"),     
m_strBtnImportAuth("BtnImportAuth"),  
m_strBtnExportAuth("BtnExportAuth"),  
m_strBtnSyncSevr("BtnSyncSevr"),  
m_strBtnRealTimeRefresh("BtnRealTimeRefresh")  
{
	m_bSetTimer = FALSE;
}

CSysInfoLogic::~CSysInfoLogic()
{ 
	UnRegMsg();
	UnRegFunc();
}

void CSysInfoLogic::RegMsg()
{    
    //REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CSysInfoLogic::OnDisConnect, m_pLogic, CSysInfoLogic );
    REG_MSG_HANDLER( UI_UMSTOOL_MSG_UMSVER_NTY, CSysInfoLogic::OnUmsVerNotify, SYSINFOLOGICRPTR, CSysInfoLogic );
//     REG_MSG_HANDLER( UI_UMSTOOL_REG_NTY, CSysInfoLogic::OnUmsSipNotify, SYSINFOLOGICRPTR, CSysInfoLogic );
//     REG_MSG_HANDLER( UI_UMSTOOL_GK_NTY, CSysInfoLogic::OnUmsGkNotify, SYSINFOLOGICRPTR, CSysInfoLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_AUTHCOUNT_NTY, CSysInfoLogic::OnUmsAuthCountNotify, SYSINFOLOGICRPTR, CSysInfoLogic );
    REG_MSG_HANDLER( UI_UMSTOOL_MSG_CONFCOUNT_NTY, CSysInfoLogic::OnUmsConfCountNotify, SYSINFOLOGICRPTR, CSysInfoLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_SYSINFO_NTY, CSysInfoLogic::OnUmsSysInfoNotify, SYSINFOLOGICRPTR, CSysInfoLogic );
	REG_MSG_HANDLER( UI_GET_UMS_SYSTIME, CSysInfoLogic::OnUmsSysTimeNotify, SYSINFOLOGICRPTR, CSysInfoLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_TVWUSED_NTY, CSysInfoLogic::OnTvwUsedNotify, SYSINFOLOGICRPTR, CSysInfoLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_BOARDUSED_NTY, CSysInfoLogic::OnBoardUsedNotify, SYSINFOLOGICRPTR, CSysInfoLogic );

	REG_MSG_HANDLER( UI_UMS_REG_INFO_NOTIFY, CSysInfoLogic::OnRegInfoNty, SYSINFOLOGICRPTR, CSysInfoLogic );
	REG_MSG_HANDLER( UI_CNS_REG_GK_NTY, CSysInfoLogic::OnRegGkNty, SYSINFOLOGICRPTR, CSysInfoLogic );
	
	

}

void CSysInfoLogic::UnRegMsg()
{
    //UN_REG_MSG_HANDLER(  UI_CONNECT_RSP, CSysInfoLogic::OnConnectRep, m_pLogic, CSysInfoLogic);
	
}

bool CSysInfoLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CSysInfoLogic::InitWnd", CSysInfoLogic::InitWnd, SYSINFOLOGICRPTR, CSysInfoLogic);

	REG_GOBAL_MEMBER_FUNC( "CSysInfoLogic::OnBtnRealTimeRefresh", CSysInfoLogic::OnBtnRealTimeRefresh, SYSINFOLOGICRPTR, CSysInfoLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CSysInfoLogic::OnBtnImportAuth", CSysInfoLogic::OnBtnImportAuth, SYSINFOLOGICRPTR, CSysInfoLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CSysInfoLogic::OnBtnExportAuth", CSysInfoLogic::OnBtnExportAuth, SYSINFOLOGICRPTR, CSysInfoLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CSysInfoLogic::OnBtnSyncSevr", CSysInfoLogic::OnBtnSyncSevr, SYSINFOLOGICRPTR, CSysInfoLogic ); 

	return true;
}

bool CSysInfoLogic::UnRegFunc()
{

	return true;
}

bool CSysInfoLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

	InitLogicData();

    return true;
}

void CSysInfoLogic::InitLogicData()
{
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrCorrelativeCfgDlg, false );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrAddrbookExpDlg, false );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrTemplateExpDlg, false );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrBoardCfgDlg, false );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrUmsCfgDlg, true );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrBoardOptDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrNetMngOptDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrVTROptDlg, false );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrTvwBoardCfgDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrNetMngCfgDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrVTRCfgDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrTvwStyleCfgDlg, false );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrTvwStyleOptDlg, false );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrImpCommonDlg, false );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrExpCommonDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcMsgboxDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrBackupCfgDlg, false );
	
}

void CSysInfoLogic::Clear()
{
	::KillTimer( NULL, g_wTimerID );
	m_bSetTimer = FALSE;

	InitLogicData();

	UIFACTORYMGR_PTR->LoadScheme( "SchmClean", m_pWndTree );

}

bool CSysInfoLogic::OnBtnRealTimeRefresh( const IArgs & arg )    //测试点击刷新得到基本信息的数据
{
	u16 nRet = COMMONMGRIFPTR->AuthCountReq();;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "会议数目请求发送失败" );
	}

	nRet = COMMONMGRIFPTR->RefreshUmsSysInfoReq();;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "系统信息请求发送失败" );
	}

	SyncTimeToSevr();

	nRet = COMMONMGRIFPTR->TvwUsedCountReq();;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "电视墙使用情况请求发送失败" );
	}

	nRet = COMMONMGRIFPTR->BoardAudiomixReq();;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "混音器合成使用情况请求发送失败" );
	}

	nRet = COMMONMGRIFPTR->BoardVmpReq();;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "画面合成使用情况请求发送失败" );
	}

	nRet = COMMONMGRIFPTR->BoardBasStreamReq();;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "码流适配使用情况请求发送失败" );
	}

	return true;
}

bool CSysInfoLogic::OnBtnImportAuth( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchImportAuth", NULL, g_stcStrImpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrImpCommonDlg );		

	return true;
}

bool CSysInfoLogic::OnBtnExportAuth( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", NULL, g_stcStrExpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchExportAuth", NULL, g_stcStrExpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrExpCommonDlg );		

	return true;
}

bool CSysInfoLogic::OnBtnSyncSevr( const IArgs & arg )
{
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnSyncSevr, FALSE, m_pWndTree );
	SyncTimeToSevr();

	return true;
}

void CSysInfoLogic::SyncTimeToSevr()
{
	SYSTEMTIME sysTime;
	::GetLocalTime( &sysTime ); 
	TTPTime time;
    time.m_wYear = sysTime.wYear;
    time.m_byMonth = sysTime.wMonth;
    time.m_byMDay = sysTime.wDay;
    time.m_byHour = sysTime.wHour;
    time.m_byMinute = sysTime.wMinute;
    time.m_bySecond = sysTime.wSecond;

	CTime curtime(sysTime);
	//需求修改：同步至服务器时间范围：2000年1月1日8点~2037年12月31日24点  -- 20140701 by xhx
	CTime limittime = CTime( 2000, 1, 1, 8, 0, 0, -1 );
	if ( time.m_wYear > 2037 || time.m_wYear < 2000 || curtime < limittime )
	{
		MESSAGEWND( "系统时间设置不正确，请修改日期" );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnSyncSevr, TRUE, m_pWndTree );
		return;
	}

// 	TTPTime tTime;
// 	CTime m_tmCurrentTime = CTime::GetCurrentTime();
// 	tTime.m_wYear = m_tmCurrentTime.GetYear();
// 	tTime.m_byMonth = m_tmCurrentTime.GetMonth();
// 	tTime.m_byMDay = m_tmCurrentTime.GetDay();
// 	tTime.m_byHour = m_tmCurrentTime.GetHour();
// 	tTime.m_byMinute = m_tmCurrentTime.GetMinute();
// 	tTime.m_bySecond = m_tmCurrentTime.GetSecond();
	u16 nRet = COMMONMGRIFPTR->SysTimeSetReq(time);;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "系统时间请求发送失败" );
	}
}

HRESULT CSysInfoLogic::OnUmsVerNotify( WPARAM wparam, LPARAM lparam)
{
	TUmsVersion tUmsVer = DATAMGRPTR->GetUmsVerData();

	String strData;
	strData = "UMS 硬件版本:  ";
	strData += tUmsVer.m_abHardVersion;
	Value_WindowCaption captValHardVer;
	captValHardVer.strCaption = strData;
	UIFACTORYMGR_PTR->SetCaption( m_strStcHardWareVer, strData, m_pWndTree );

	strData = "UMS 软件版本:  ";
	strData += tUmsVer.m_abSoftVersion;
	UIFACTORYMGR_PTR->SetCaption( m_strStcSoftWareVer, strData, m_pWndTree );
	
	return S_OK;
}

HRESULT CSysInfoLogic::OnUmsSipNotify( WPARAM wparam, LPARAM lparam)
{
	BOOL32 bRegRet = static_cast<BOOL32>( lparam );
	TTPSipRegistrarCfg tData = DATAMGRPTR->GetSipCfgData();
    
	if ( bRegRet )
	{
		String strData;
		strData = "UMS 注册网呈服务器:  ";
		strData += CUmstoolCommon::GetIpStr(tData.dwRegIP);
		
		UIFACTORYMGR_PTR->SetCaption( m_strStcSipSevr, strData, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcSipSevr, "UMS 注册网呈服务器:  未注册", m_pWndTree );
	}

	return S_OK;
}

HRESULT CSysInfoLogic::OnUmsGkNotify( WPARAM wparam, LPARAM lparam)
{
	BOOL32 bRegRet = static_cast<BOOL32>( lparam );
    TTPGKCfg tData = DATAMGRPTR->GetGkCfgData();

	if ( bRegRet )
	{
		String strData;
		strData = "注册GK:  ";
		strData += CUmstoolCommon::GetIpStr(tData.dwGKIP);
		
		UIFACTORYMGR_PTR->SetCaption( m_strStcGkSevr, strData, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcGkSevr, "注册GK:  未注册", m_pWndTree );
	}

	return S_OK;
}

HRESULT CSysInfoLogic::OnUmsAuthCountNotify( WPARAM wparam, LPARAM lparam)
{
	std::pair<int,int> authCount = DATAMGRPTR->GetAuthCountData();
	s8 chCount[8] = {0};
	sprintf( chCount, "%d", authCount.first );
	
	String strData;
	strData = "授权数目:  ";  //没收到
	strData += chCount;
	
	UIFACTORYMGR_PTR->SetCaption( m_strStcAuthCount, strData, m_pWndTree );

	return S_OK;
}

HRESULT CSysInfoLogic::OnUmsConfCountNotify( WPARAM wparam, LPARAM lparam)
{
	u32 dwData = DATAMGRPTR->GetConfCountData();
	s8 chCount[8] = {0};
	sprintf( chCount, "%u", dwData );
	
	String strData;
	strData = "会议数目:  ";
	strData += chCount;
	strData += "个会议";
	
	UIFACTORYMGR_PTR->SetCaption( m_strStcCoufCount, strData, m_pWndTree );

	return S_OK;
}

HRESULT CSysInfoLogic::OnUmsSysInfoNotify( WPARAM wparam, LPARAM lparam)
{
	TToolSysInfo tData = DATAMGRPTR->GetUmsSysInfoData();
	
	String strData;
	strData = "CPU使用率:  ";
	s8 chCpuRate[8] = {0};
	sprintf( chCpuRate, "%u", tData.m_dwCpuRate );
	strData += chCpuRate;
	strData += "%";

	UIFACTORYMGR_PTR->SetCaption( m_strStcCpuRate, strData, m_pWndTree );

	strData = "内存使用率:  ";
	s8 chMemRate[8] = {0};
	sprintf( chMemRate, "%u", tData.m_dwMemRate );
	strData += chMemRate;
	strData += "%";

	UIFACTORYMGR_PTR->SetCaption( m_strStcMemeryRate, strData, m_pWndTree );

	return S_OK;
}

HRESULT CSysInfoLogic::OnUmsSysTimeNotify( WPARAM wparam, LPARAM lparam)
{
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnSyncSevr, TRUE, m_pWndTree );

	if ( !m_bSetTimer )
	{
		g_wTimerID = ::SetTimer( NULL, 0, 1000, CBTimerFun );
		m_bSetTimer = TRUE;
	}

	TTPTime tData = DATAMGRPTR->GetUmsSystimeData();
	if ( !tData.IsValid() )
	{
		MESSAGEWND( "服务器时间无效" );
		return S_FALSE;
	}
	else
	{
		s8 chDate[50] = {0};
		sprintf( chDate, "%d年%.2d月%.2d日 %.2d:%.2d:%.2d", tData.m_wYear, tData.m_byMonth, tData.m_byMDay, 
			tData.m_byHour, tData.m_byMinute, tData.m_bySecond );  
		
		UIFACTORYMGR_PTR->SetCaption( m_strStcSysTimeValue, chDate, m_pWndTree );
	}

	struct tm tmDate;
	memset(&tmDate, 0, sizeof(tmDate));
	tmDate.tm_year = tData.m_wYear - 1900;
	tmDate.tm_mon = tData.m_byMonth - 1;
	tmDate.tm_mday = tData.m_byMDay;
	tmDate.tm_hour = tData.m_byHour;
	tmDate.tm_min = tData.m_byMinute;
	tmDate.tm_sec = tData.m_bySecond;
	
	g_timeDate = mktime(&tmDate);
	
	return S_OK;
}

void CSysInfoLogic::UpdateServerTime()
{
	g_timeDate += 1;
	struct tm tmTmpDate;
	CUmstoolCommon::TimeToTm( tmTmpDate, g_timeDate );
	
	s8 chDate[50] = {0};
	sprintf( chDate, "%d年%.2d月%.2d日 %.2d:%.2d:%.2d", tmTmpDate.tm_year, tmTmpDate.tm_mon, tmTmpDate.tm_mday, 
			tmTmpDate.tm_hour, tmTmpDate.tm_min, tmTmpDate.tm_sec ); 
	
	UIFACTORYMGR_PTR->SetCaption( m_strStcSysTimeValue, chDate, m_pWndTree, true );
}

HRESULT CSysInfoLogic::OnTvwUsedNotify( WPARAM wparam, LPARAM lparam)
{
	TTPBrdUsedInfo tTPBrdUsedInfo = DATAMGRPTR->GetUmsTvwUsedData();

	s8 chRegCount[8] = {0};
	sprintf( chRegCount, "%d", tTPBrdUsedInfo.m_wRegNum );

	s8 chUsedCount[8] = {0};
	sprintf( chUsedCount, "%d", tTPBrdUsedInfo.m_wUsedNum );
	
	String strData;
	strData = "电视墙占用情况:  ";  //没收到
	strData += chUsedCount;
	strData += "/";
	strData += chRegCount;

	UIFACTORYMGR_PTR->SetCaption( m_strStcTvwPer, strData, m_pWndTree );

	return S_OK;
}

HRESULT CSysInfoLogic::OnBoardUsedNotify( WPARAM wparam, LPARAM lparam)
{
	TTPBrdUsedInfo tTPBrdUsedInfo = *reinterpret_cast<TTPBrdUsedInfo*>(wparam);

	s8 chRegCount[8] = {0};
	sprintf( chRegCount, "%d", tTPBrdUsedInfo.m_wRegNum );
	
	s8 chUsedCount[8] = {0};
	sprintf( chUsedCount, "%d", tTPBrdUsedInfo.m_wUsedNum );

	String strData;
	switch( tTPBrdUsedInfo.m_emType )
	{
	case em_audmix_mdl:
		{
			strData = "混音器占用情况:  ";  //没收到
			strData += chUsedCount;
			strData += "/";
			strData += chRegCount;

			UIFACTORYMGR_PTR->SetCaption( m_strStcMixAudioPer, strData, m_pWndTree );
		}
		break;
	case em_vmp_mdl:
		{
			strData = "画面合成器占用情况:  ";  //没收到
			strData += chUsedCount;
			strData += "/";
			strData += chRegCount;
			
			UIFACTORYMGR_PTR->SetCaption( m_strStcImageCompondPer, strData, m_pWndTree );
		}
		break;
	case em_bas_mdl:
		{		
			strData = "码流适配器占用情况:  ";  //没收到
			strData += chUsedCount;
			strData += "/";
			strData += chRegCount;
				
			UIFACTORYMGR_PTR->SetCaption( m_strStcSteamAdaptePer, strData, m_pWndTree );
		}
		break;
	default:
		{
		}
		break;
	}
	
	return S_OK;
}


HRESULT CSysInfoLogic::OnRegInfoNty( WPARAM wparam, LPARAM lparam)
{
	TTPSipRegistrarCfg tData = DATAMGRPTR->GetSipCfgData();
    
	if ( tData.bRegistered )
	{
		String strData;
		strData = "UMS 注册网呈服务器:  ";
		strData += CUmstoolCommon::GetIpStr(tData.dwRegIP);
		
		UIFACTORYMGR_PTR->SetCaption( m_strStcSipSevr, strData, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcSipSevr, "UMS 注册网呈服务器:  未注册", m_pWndTree );
	}
	
	return S_OK;
}

HRESULT CSysInfoLogic::OnRegGkNty( WPARAM wparam, LPARAM lparam)
{
    TTPGKCfg tData = DATAMGRPTR->GetGkCfgData();
	
	if ( tData.bRegistered )
	{
		String strData;
		strData = "注册GK:  ";
		strData += CUmstoolCommon::GetIpStr(tData.dwGKIP);
		
		UIFACTORYMGR_PTR->SetCaption( m_strStcGkSevr, strData, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcGkSevr, "注册GK:  未注册", m_pWndTree );
	}
	
	return S_OK;
}