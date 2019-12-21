#include "StdAfx.h"
#include "moonlibdatamgr.h"
#include "sessionmgr.h"


CMoonlibDataMgr* CMoonlibDataMgr::m_pThis = NULL;

CMoonlibDataMgr::CMoonlibDataMgr()
{   
	VERIFY( CreateEx( 0, AfxRegisterWndClass(CS_DBLCLKS), _T("moontool"),
			WS_OVERLAPPEDWINDOW, CRect(10, 10, 10, 10), NULL, NULL, NULL ) );
	InitDataMgr();
}

CMoonlibDataMgr::~CMoonlibDataMgr()
{

}

void CMoonlibDataMgr::InitDataMgr()
{
	MOONSESSION_MGR_PTR->GetSessionIF()->SetNotifyWnd( GetSafeHwnd() );
    // new add as the last one 577 if not add interface can't rec msg
	MOONSESSION_MGR_PTR->GetCamConfigIF()->SetNotifyWnd( GetSafeHwnd() );
	MOONSESSION_MGR_PTR->GetSysConfigIF()->SetNotifyWnd( GetSafeHwnd() );
    MOONSESSION_MGR_PTR->GetSysCtrlIF()->SetNotifyWnd( GetSafeHwnd() );
}

CMoonlibDataMgr* CMoonlibDataMgr::GetDataMgrIF()
{
	if ( NULL == m_pThis )
    {
        m_pThis = new CMoonlibDataMgr;
		
    }
	return m_pThis;
}

//ks
// u16 CMoonlibDataMgr::GetSipCfg( TTPSipRegistrarCfg& tSipCfg ) const
// {
// 	tSipCfg = MOONSESSION_MGR_PTR->GetConfigIF()->GetSipRegCfg();
// 	return NO_ERROR;
// }

BOOL CMoonlibDataMgr::PreCreateWindow( CREATESTRUCT& cs )
{
    cs.style &= ~WS_SYSMENU; 
    return CWnd::PreCreateWindow(cs);
}

LRESULT CMoonlibDataMgr::DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	//if ( message > CMS_MSG_BEGIN ) 
	{
		CMsgDispatch::SendMessage( message, wParam, lParam );
	}
	
    return CWnd::DefWindowProc( message, wParam, lParam );
}

u16 CMoonlibDataMgr::GetLoginIp( u32 &dwIP ) const
{
	dwIP = COMIFMGRPTR->GetLoginIp();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamCfg( TTPMoonCamInfo &tMoonCameraCfg )const
{
	tMoonCameraCfg = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamCfg();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::SetAllCamCfg( TTPMoonCamInfo tCamInfo[] )const
{
    MOONSESSION_MGR_PTR->GetCamConfigIF()->SetAllCamCfg(tCamInfo);
    return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCurStatus( BOOL& bSetCamCfgOver, BOOL& bOutputFmtChg )const
{
    MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCurStatus(bSetCamCfgOver, bOutputFmtChg);
    return NO_ERROR;
}

u16 CMoonlibDataMgr::ClearCurStatus()const
{
    MOONSESSION_MGR_PTR->GetCamConfigIF()->ClearCurStatus();
    return NO_ERROR;
}

u16 CMoonlibDataMgr::GetAllCamCfg( TTPMoonCamInfo* ptCamInfo[] )const
{
    MOONSESSION_MGR_PTR->GetCamConfigIF()->GetAllCamCfg(ptCamInfo);
    return NO_ERROR;
}

u16 CMoonlibDataMgr::GetOutputFormat( TPOutputFmt &tPOutputFmt )const
{
    tPOutputFmt = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetOutputFormat();
    return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamZoom( u32& dwZoom )const
{
	dwZoom = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamZoom();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetExtCamZoom(u32& dwZoomPos) const
{
	dwZoomPos = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetExtCamZoom();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamSel( u8& byCameraIndx )const
{
	byCameraIndx = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamSel();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamMoonMode( EmTPMOOMMode& emExpMode ) const
{
	emExpMode = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamMoonMode();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamAperture(TIrisAutoManuMode &tIrisMode) const
{
	tIrisMode = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamAperture();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamGain(EmTPExpGain &emGain) const
{
	emGain = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamGain();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamShutSpd(TPSOrThShutter &tTPSOrThShutSpd) const
{
	tTPSOrThShutSpd = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamShutSpd();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetTwCamShutSpd(TPFOrTwShutter &tTPFOrTwShutSpd) const
{
	tTPFOrTwShutSpd = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetTwCamShutSpd();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamRGain(u32 &dwRGain) const
{
	dwRGain = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamRGain();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamBGain(u32 &dwBGain) const
{
	dwBGain = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamBGain();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamAdjustRange(u32 &dwAdjustRange) const
{
	dwAdjustRange = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamAdjustRange();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamHoriStretch(u32 &dwHoriStretch) const
{
	dwHoriStretch = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamHoriStretch();
	return NO_ERROR;
}

u16 CMoonlibDataMgr::GetCamWBMode( EmTPMOOMMode& emWBMode ) const
{
	emWBMode = MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamWBMode();
	return NO_ERROR;
}

TTPCamPre* CMoonlibDataMgr::GetCamPreInfo()
{
	return MOONSESSION_MGR_PTR->GetCamConfigIF()->GetCamPreInfo();
}

u16 CMoonlibDataMgr::GetEthnetCfg( TTPEthnetInfo &tEthnetInfo )
{
	tEthnetInfo = MOONSESSION_MGR_PTR->GetSysConfigIF()->GetEthnetCfg();
	return NO_ERROR;
}