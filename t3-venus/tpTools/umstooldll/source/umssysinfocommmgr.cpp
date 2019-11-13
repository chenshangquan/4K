// umssysinfocommmgr.cpp: implementation of the CUmsSysInfoCommMgr class.
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
u16 CCommonMgrIF::AuthCountReq()
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetSysInfoCtrlPtr()->AuthCountReq();
	
	return re;
}

u16 CCommonMgrIF::ConfCountReq()
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetSysInfoCtrlPtr()->ConfCountReq();
	
	return re;
}

u16 CCommonMgrIF::RefreshUmsSysInfoReq()
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetSysInfoCtrlPtr()->RefreshUmsSysInfoReq();
	
	return re;
}

u16 CCommonMgrIF::TvwUsedCountReq()
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetSysInfoCtrlPtr()->TvwUsedCountReq();
	
	return re;
}