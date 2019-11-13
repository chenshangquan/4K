// umsconfigcommmgr.cpp: implementation of the CUmsSysInfoCommMgr class.
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
u16 CCommonMgrIF::SysTimeSetReq(const TTPTime& time)
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetConfigCtrlPtr()->OnSysTimeSetReq(time);
	
	return re;
}

u16 CCommonMgrIF::RebootReq()
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetConfigCtrlPtr()->RebootReq();
	
	return re;
}

u16  CCommonMgrIF::UpdateEthnetCfg( TTPEthnetInfo &tEthnetInfo )
{
	u16 re = NO_ERROR;
	re = SESSIONPTR->GetConfigCtrlPtr()->UpdateEthnetCfg(tEthnetInfo);
	
	return re;
}

u16 CCommonMgrIF::UpdateGKCfg( TTPGKCfg & tGkwInfo )
{
	u16 re = NO_ERROR;
	re = SESSIONPTR->GetConfigCtrlPtr()->GkRegReq(tGkwInfo);
	
	return re;
}

u16 CCommonMgrIF::UpdateSipCfg( TTPSipRegistrarCfg &tSipInfo )
{
	u16 re = NO_ERROR;
	re = SESSIONPTR->GetConfigCtrlPtr()->RegSipService(tSipInfo);
	
	return re;
}

u16 CCommonMgrIF::ImportInfoReq(const s8* strFileName)
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetExportCtrPtr()->ImportInfoReq(strFileName);
	
	return re;
}

u16 CCommonMgrIF::ExportInfoReq()
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetExportCtrPtr()->ExportInfoReq();
	
	return re;
}

u16 CCommonMgrIF::ExportAuthReq()
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetExportCtrPtr()->ExportAuthReq();
	
	return re;
}
