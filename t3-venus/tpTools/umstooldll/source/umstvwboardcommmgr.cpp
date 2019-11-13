// umstvwboardcommmgr.cpp: implementation of the CUmsSysInfoCommMgr class.
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

u16  CCommonMgrIF::TvwBoardAddReq( const TTPBrdPos& tTPBrdPos )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetTvwBoardCtrlPtr()->TvwBoardAddReq(tTPBrdPos);
	
	return re;
}

u16  CCommonMgrIF::TvwBoardModifyReq( const TTPBrdPos& tTPBrdPos )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetTvwBoardCtrlPtr()->TvwBoardModifyReq(tTPBrdPos);
	
	return re;
}

u16  CCommonMgrIF::TvwBoardDeleteReq( const TTPBrdPos& tTPBrdPos )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetTvwBoardCtrlPtr()->TvwBoardDeleteReq(tTPBrdPos);
	
	return re;
}

u16  CCommonMgrIF::TvwBoardModeAddReq( const THduInfo& tTHduInfo )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetTvwBoardCtrlPtr()->TvwBoardModeAddReq(tTHduInfo);
	
	return re;
}

u16  CCommonMgrIF::TvwBoardModeModifyReq( const THduInfo& tTHduInfo )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetTvwBoardCtrlPtr()->TvwBoardModeModifyReq(tTHduInfo);
	
	return re;
}

u16  CCommonMgrIF::TvwBoardModeDeleteReq( const TTPBrdPos& tTPBrdPos )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetTvwBoardCtrlPtr()->TvwBoardModeDeleteReq(tTPBrdPos);
	
	return re;
}

u16  CCommonMgrIF::TvwBoardRebootReq( const TTPBrdPos& tTPbrdPos )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetTvwBoardCtrlPtr()->TvwBoardRebootReq(tTPbrdPos);
	
	return re;
}

u16  CCommonMgrIF::TvwBoardUpgradeReq( const TTPBrdUpGrade& tBrdUpGrade )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetTvwBoardCtrlPtr()->TvwBoardUpgradeReq(tBrdUpGrade);
	
	return re;
}

u16  CCommonMgrIF::AddTvwStyleReq( const THduStyleData& tHduStyleData  )
{
	u16 re = NO_ERROR;
    re = SESSIONPTR->GetTvwBoardCtrlPtr()->AddTvwStyleReq(tHduStyleData);
	
	return re;
}

// u16  CCommonMgrIF::TvwStyleDeleteReq()
// {
// 	u16 re = NO_ERROR;
//     re = SESSIONPTR->GetTvwBoardCtrlPtr()->TvwStyleDeleteReq();
// 	
// 	return re;
// }