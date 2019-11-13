// umsnetmngcommmgr.cpp: implementation of the CUmsNetMngCommMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umstooldll.h"
#include "commonmgrif.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
u16  CCommonMgrIF::NetMngAddReq( const TTPNMServerCfg& tTPNMServerCfg )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetNetMngCtrlPtr()->NetMngAddReq( tTPNMServerCfg );
	
	return re;
}

u16  CCommonMgrIF::NetMngModifyReq( const TTPNMServerCfg& tTPNMServerCfg )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetNetMngCtrlPtr()->NetMngModifyReq( tTPNMServerCfg );
	
	return re;
}

u16  CCommonMgrIF::NetMngDeleteReq( const TTPNMServerCfg& tTPNMServerCfg )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetNetMngCtrlPtr()->NetMngDeleteReq( tTPNMServerCfg );
	
	return re;
}

u16  CCommonMgrIF::VTRAddReq( const TVcrCfg& tVTRCfg )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetVTRCtrlPtr()->VTRAddReq( tVTRCfg );
	
	return re;
}

u16  CCommonMgrIF::VTRModifyReq( const TVcrCfg& tVTRCfgOld, const TVcrCfg& tVTRCfgNew )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetVTRCtrlPtr()->VTRModifyReq( tVTRCfgOld, tVTRCfgNew );
	
	return re;
}
	
u16  CCommonMgrIF::VTRDeleteReq( const TVcrCfg& tVTRCfg )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetVTRCtrlPtr()->VTRDeleteReq( tVTRCfg );
	
	return re;
}
