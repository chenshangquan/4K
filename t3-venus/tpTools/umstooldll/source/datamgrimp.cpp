// datamgrimp.cpp: implementation of the CDataMgrImp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "datamgrimp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CDataMgrImp, CWnd)
END_MESSAGE_MAP()

CDataMgrImp::CDataMgrImp()
{
}

CDataMgrImp::~CDataMgrImp()
{
}

HWND CDataMgrImp::GetRecvWnd()
{
	return GetSafeHwnd();
}

BOOL CDataMgrImp::CreateDataMgr()
{
	if ( NULL == GetRecvWnd() )
	{
		VERIFY( this->CreateEx( 0, AfxRegisterWndClass(CS_DBLCLKS), _T("CDataMgrImp"),
			WS_OVERLAPPEDWINDOW, CRect(10, 10, 10, 10), NULL, NULL, NULL ) );
	}

	SESSIONPTR->GetSessionCtrlPtr()->SetNotifyWnd( GetRecvWnd() ) ;
	SESSIONPTR->GetUserCtrlPtr()->SetNotifyWnd( GetRecvWnd() );
	SESSIONPTR->GetSysInfoCtrlPtr()->SetNotifyWnd( GetRecvWnd() );
	SESSIONPTR->GetTvwBoardCtrlPtr()->SetNotifyWnd( GetRecvWnd() );
	SESSIONPTR->GetBoardCtrlPtr()->SetNotifyWnd( GetRecvWnd() );
	SESSIONPTR->GetExportCtrPtr()->SetNotifyWnd( GetRecvWnd() );
	SESSIONPTR->GetConfigCtrlPtr()->SetNotifyWnd( GetRecvWnd() );
	SESSIONPTR->GetNetMngCtrlPtr()->SetNotifyWnd( GetRecvWnd() );
	SESSIONPTR->GetVTRCtrlPtr()->SetNotifyWnd( GetRecvWnd() );

	return TRUE;
}

void CDataMgrImp::DestroyDataMrg()
{   

}
 
BOOL CDataMgrImp::PreCreateWindow( CREATESTRUCT& cs )
{
    cs.style &= ~WS_SYSMENU; 
    return CWnd::PreCreateWindow(cs);
}

LRESULT CDataMgrImp::DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	if ( message >= CMS_MSG_BEGIN && message <= UMSTOOL_MSG_END )   //派发ums->umc cns->cnc消息到界面UI  其余消息过滤 此消息不能
		                                                           //出现在当前消息接收窗口中 应加入界面业务中 且需注册
	{
		CMsgDispatch::SendMessage( message, wParam, lParam );
	}
	
    return CWnd::DefWindowProc( message, wParam, lParam );
}

/////////////////////////umslib Data//////////////////////////////////////
TTPEthnetInfo CDataMgrImp::GetEthnetCfgData()
{
	TTPEthnetInfo tData;
	if ( SESSIONPTR->GetConfigCtrlPtr() == NULL )
	{
		return tData;
	}
	SESSIONPTR->GetConfigCtrlPtr()->GetEthnetCfg(tData);
	 	
 	return tData; 
}

TTPSipRegistrarCfg CDataMgrImp::GetSipCfgData()
{
	TTPSipRegistrarCfg tData;
	if ( SESSIONPTR->GetConfigCtrlPtr() == NULL )
	{
		return tData;
	}
	SESSIONPTR->GetConfigCtrlPtr()->GetSipCfg(tData);
	
 	return tData; 
}

TTPGKCfg CDataMgrImp::GetGkCfgData()
{
	TTPGKCfg tData;
	if ( SESSIONPTR->GetConfigCtrlPtr() == NULL )
	{
		return tData;
	}
	SESSIONPTR->GetConfigCtrlPtr()->GetGkCfg(tData);
	
 	return tData; 
}

TTPTime CDataMgrImp::GetUmsSystimeData()
{
	TTPTime tData;
	SESSIONPTR->GetConfigCtrlPtr()->GetUmsSystime(tData);
	
 	return tData; 
}

TUmsVersion CDataMgrImp::GetUmsVerData()
{
	TUmsVersion tData;
	SESSIONPTR->GetSysInfoCtrlPtr()->GetUmsVerData(tData);

 	return tData; 
}

TToolSysInfo CDataMgrImp::GetUmsSysInfoData()
{
	TToolSysInfo tData;
	SESSIONPTR->GetSysInfoCtrlPtr()->GetUmsSysInfoData(tData);
	
	return tData; 
}

std::pair<int,int> CDataMgrImp::GetAuthCountData()
{
	return SESSIONPTR->GetSysInfoCtrlPtr()->GetAuthCountData();
}

u32 CDataMgrImp::GetConfCountData()
{
	return SESSIONPTR->GetSysInfoCtrlPtr()->GetConfCountData();
}

TTPBrdUsedInfo CDataMgrImp::GetUmsTvwUsedData()
{
	TTPBrdUsedInfo tData;
	SESSIONPTR->GetSysInfoCtrlPtr()->GetUmsTvwUsedData(tData);
	
	return tData; 
}

TTPBrdUsedInfo CDataMgrImp::GetUmsBoardUsedData()
{
	TTPBrdUsedInfo tData;
	SESSIONPTR->GetBoardCtrlPtr()->GetUmsBoardUsedData(tData);
	
	return tData; 
}

std::multimap<u8,THduCfg> CDataMgrImp::GetUmsTvwBoardData()
{
	std::multimap<u8,THduCfg> mulmapData;
	SESSIONPTR->GetTvwBoardCtrlPtr()->GetUmsTvwBoardData(mulmapData);
	
	return mulmapData; 
}

THduStyleData CDataMgrImp::GetUmsTvwStyleData()
{
	THduStyleData tHduStyleData;
	SESSIONPTR->GetTvwBoardCtrlPtr()->GetUmsTvwStyleData(tHduStyleData);
	
	return tHduStyleData; 
}

u16 CDataMgrImp::GetUmsNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )
{
	return SESSIONPTR->GetNetMngCtrlPtr()->GetUmsNetMngData( vecTTPNMServerCfg );
}

u16 CDataMgrImp::GetUmsVTRData( vector<TVcrCfg> &vecTVcrCfg )
{
	return SESSIONPTR->GetVTRCtrlPtr()->GetUmsVTRData( vecTVcrCfg );
}