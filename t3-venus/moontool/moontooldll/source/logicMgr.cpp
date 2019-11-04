// logicMgr.cpp: implementation of the CLogicMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "moonToolDll.h"
#include "logicMgr.h"
#include "cameractrlLogic.h"
#include "SysCfgDlgLogic.h"
#include "OrderListDlgLogic.h"
#include "impcommonlogic.h"
#include "expcommonlogic.h"
#include "OrderPosInfoLogic.h"
#include "MoonAdjustDlg.h"
#include "SetContrastAreaLogic.h"
#include "CorrectParamLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//template<> CLogicMgr* ISingleTon<CLogicMgr>::ms_pSingleton = 0;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogicMgr::CLogicMgr()
{

}

CLogicMgr::~CLogicMgr()
{

}

 
void CLogicMgr::CreateLogic()
{
	CMainFrameLogic::GetSingletonPtr()->InitLogic();
	CCameraCtrlLogic::GetSingletonPtr()->InitLogic();
	CSysCfgDlgLogic::GetSingletonPtr()->InitLogic();
	CMsgboxDlgLogic::GetSingletonPtr()->InitLogic();
	COrderListDlgLogic::GetSingletonPtr()->InitLogic();
	CImpCommonDlgLogic::GetSingletonPtr()->InitLogic();
	CExpCommonDlgLogic::GetSingletonPtr()->InitLogic();
	COrderPosInfoLogic::GetSingletonPtr()->InitLogic();
	CCorrectParamLogic::GetSingletonPtr()->InitLogic();
	CSetContrastAreaLogic::GetSingletonPtr()->InitLogic();
	CWarningLogic::GetSingletonPtr()->InitLogic();
	CMoonAdjustDlg::GetSingletonPtr()->InitLogic();
}
 

void CLogicMgr::DestroyLogic()
{
	CMainFrameLogic::GetSingletonPtr()->Clear();
	CCameraCtrlLogic::GetSingletonPtr()->Clear();
	CSysCfgDlgLogic::GetSingletonPtr()->Clear();
	CMsgboxDlgLogic::GetSingletonPtr()->Clear();
	COrderListDlgLogic::GetSingletonPtr()->Clear();
	CImpCommonDlgLogic::GetSingletonPtr()->Clear();
	CExpCommonDlgLogic::GetSingletonPtr()->Clear();
	COrderPosInfoLogic::GetSingletonPtr()->Clear();
	CCorrectParamLogic::GetSingletonPtr()->Clear();
	CSetContrastAreaLogic::GetSingletonPtr()->Clear();
	CWarningLogic::GetSingletonPtr()->Clear();
	CMoonAdjustDlg::GetSingletonPtr()->Clear();
}


 