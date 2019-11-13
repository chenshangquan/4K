// umsboardcommmgr.cpp: implementation of the CUmsSysInfoCommMgr class.
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
u16  CCommonMgrIF::BoardModifyReq( const TTPBrdCfg& tTPbrdCfg )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetBoardCtrlPtr()->BoardModifyReq(tTPbrdCfg);
	
	return re;
}

u16  CCommonMgrIF::BoardDeleteReq( const TTPBrdCfg& tTPbrdCfg )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetBoardCtrlPtr()->BoardDeleteReq(tTPbrdCfg);
	
	return re;
}

u16  CCommonMgrIF::BoardAddReq( const TTPBrdCfg& tTPbrdCfg )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetBoardCtrlPtr()->BoardAddReq(tTPbrdCfg);
	
	return re;
}

// u16  CCommonMgrIF::BoardModeAddReq( const TTPBrdMdlInfo& tTPbrdMdlInfo )
// {
// 	u16 re = NO_ERROR;
//     re = SESSIONPTR->GetBoardCtrlPtr()->BoardModeAddReq(tTPbrdMdlInfo);
// 	
// 	return re;
// }

u16  CCommonMgrIF::BoardModeModifyReq( const TTPBrdMdlInfo& tTPbrdMdlInfo )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetBoardCtrlPtr()->BoardModeModifyReq(tTPbrdMdlInfo);
	
	return re;
}

u16  CCommonMgrIF::BoardModeDeleteReq( const TTPBrdMdlInfo& tTPbrdMdlInfo )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetBoardCtrlPtr()->BoardModeDeleteReq(tTPbrdMdlInfo);
	
	return re;
}

u16  CCommonMgrIF::BoardRebootReq( const TTPBrdPos& tTPbrdPos )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetBoardCtrlPtr()->BoardRebootReq(tTPbrdPos);
	
	return re;
}

u16  CCommonMgrIF::BoardUpgradeReq( const TTPBrdUpGrade& tBrdUpGrade )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetBoardCtrlPtr()->BoardUpgradeReq(tBrdUpGrade);
	
	return re;
}

u16  CCommonMgrIF::BoardAudiomixReq()
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetBoardCtrlPtr()->BoardAudiomixReq();
	
	return re;
}

u16  CCommonMgrIF::BoardVmpReq()
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetBoardCtrlPtr()->BoardVmpReq();
	
	return re;
}

u16  CCommonMgrIF::BoardBasStreamReq()
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetBoardCtrlPtr()->BoardBasStreamReq();
	
	return re;
}

