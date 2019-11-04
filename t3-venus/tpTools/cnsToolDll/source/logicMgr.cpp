// logicMgr.cpp: implementation of the CLogicMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "logicMgr.h"

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
	CBasicInfoLogic::GetSingletonPtr()->InitLogic();
	CCfgFrameLogic::GetSingletonPtr()->InitLogic();
	CCfgCnsLogic::GetSingletonPtr()->InitLogic();
	CCfgAudioPortLogic::GetSingletonPtr()->InitLogic();
	CMsgboxDlgLogic::GetSingletonPtr()->InitLogic();
	//CDiagInfoLogic::GetSingletonPtr()->InitLogic();
//	CCentCtrlLogic::GetSingletonPtr()->InitLogic();
	CDiagTestInfoLogic::GetSingletonPtr()->InitLogic();
	CDiagTestFrameLogic::GetSingletonPtr()->InitLogic();
	CCfgDiagnosticFrameLogic::GetSingletonPtr()->InitLogic();
	CDiagInterfaceLogic::GetSingletonPtr()->InitLogic();
	CNetDiagnosticLogic::GetSingletonPtr()->InitLogic();
	CNetPacketLogic::GetSingletonPtr()->InitLogic();
	CRouteCfgdlgLogic::GetSingletonPtr()->InitLogic();
	CCfgNetSecurityLogic::GetSingletonPtr()->InitLogic();
//	CCfgNetMngLogic::GetSingletonPtr()->InitLogic();
//	CNetMngOptDlgLogic::GetSingletonPtr()->InitLogic();
	CCameraLogic::GetSingletonPtr()->InitLogic();
	CAddrbookExpLogic::GetSingletonPtr()->InitLogic();
//	CCfgMixLogic::GetSingletonPtr()->InitLogic();
	CCfgServerLogic::GetSingletonPtr()->InitLogic();
	CCfgEqLogic::GetSingletonPtr()->InitLogic();
	CExpCommonDlgLogic::GetSingletonPtr()->InitLogic();
	CImpCommonDlgLogic::GetSingletonPtr()->InitLogic();
	CWarningLogic::GetSingletonPtr()->InitLogic();
	CCfgCallSerLogic::GetSingletonPtr()->InitLogic();
	CCfgAdvanceDlg::GetSingletonPtr()->InitLogic();
	CCfgAudioDlg::GetSingletonPtr()->InitLogic();
	CCfgMainAudioDlg::GetSingletonPtr()->InitLogic();
	CCfgDemonStrationDlg::GetSingletonPtr()->InitLogic();
	CCfgAdjustImageDlg::GetSingletonPtr()->InitLogic();
	CCRenameOptDlg::GetSingletonPtr()->InitLogic();
	CCfgCnsFrame::GetSingletonPtr()->InitLogic();
	RecordOptDlg::GetSingletonPtr()->InitLogic();
	//ÖÐ¿Ø
	CCentCfgFrameLogic::GetSingletonPtr()->InitLogic();
	CCentCfgDisplayDlg::GetSingletonPtr()->InitLogic();
	CCentCfgStatusMesDlg::GetSingletonPtr()->InitLogic();
	CCentCfgCurtainDlg::GetSingletonPtr()->InitLogic();
	CCentCfgCameraDlg::GetSingletonPtr()->InitLogic();
	CCentCfgDuoVideo::GetSingletonPtr()->InitLogic();
	CCentCfgAirCondition::GetSingletonPtr()->InitLogic();
}
 

void CLogicMgr::DestroyLogic()
{
	CMsgboxDlgLogic::GetSingletonPtr()->Clear();
	CDiagTestInfoLogic::GetSingletonPtr()->Clear();
	CDiagTestFrameLogic::GetSingletonPtr()->Clear();
	CExpCommonDlgLogic::GetSingletonPtr()->Clear();
	CImpCommonDlgLogic::GetSingletonPtr()->Clear();
	CMainFrameLogic::GetSingletonPtr()->Clear();
	CBasicInfoLogic::GetSingletonPtr()->Clear();
	CCfgFrameLogic::GetSingletonPtr()->Clear();
	CCfgCnsLogic::GetSingletonPtr()->Clear();
	CCfgAudioPortLogic::GetSingletonPtr()->Clear();
	CCfgDiagnosticFrameLogic::GetSingletonPtr()->Clear();
	CDiagInterfaceLogic::GetSingletonPtr()->Clear();
	CNetDiagnosticLogic::GetSingletonPtr()->Clear();
	CNetPacketLogic::GetSingletonPtr()->Clear();
	CRouteCfgdlgLogic::GetSingletonPtr()->Clear();
	CCfgNetSecurityLogic::GetSingletonPtr()->Clear();
	//CDiagInfoLogic::GetSingletonPtr()->Clear();
//	CCentCtrlLogic::GetSingletonPtr()->Clear();
//	CCfgNetMngLogic::GetSingletonPtr()->Clear();
//	CNetMngOptDlgLogic::GetSingletonPtr()->Clear();
	CCameraLogic::GetSingletonPtr()->Clear();
	CAddrbookExpLogic::GetSingletonPtr()->Clear();
//	CCfgMixLogic::GetSingletonPtr()->Clear();
	CCfgServerLogic::GetSingletonPtr()->Clear();
	CCfgEqLogic::GetSingletonPtr()->Clear();
	CWarningLogic::GetSingletonPtr()->Clear();
	CCfgCallSerLogic::GetSingletonPtr()->Clear();
	CCfgAdvanceDlg::GetSingletonPtr()->Clear();
	CCfgAudioDlg::GetSingletonPtr()->Clear();
	CCfgMainAudioDlg::GetSingletonPtr()->Clear();
	CCfgDemonStrationDlg::GetSingletonPtr()->Clear();
	CCfgAdjustImageDlg::GetSingletonPtr()->Clear();
	CCRenameOptDlg::GetSingletonPtr()->Clear();
	CCfgCnsFrame::GetSingletonPtr()->Clear();
	RecordOptDlg::GetSingletonPtr()->Clear();
	//ÖÐ¿Ø
	CCentCfgFrameLogic::GetSingletonPtr()->Clear();
	CCentCfgDisplayDlg::GetSingletonPtr()->Clear();
	CCentCfgStatusMesDlg::GetSingletonPtr()->Clear();
	CCentCfgCurtainDlg::GetSingletonPtr()->Clear();
	CCentCfgCameraDlg::GetSingletonPtr()->Clear();
	CCentCfgDuoVideo::GetSingletonPtr()->Clear();
	CCentCfgAirCondition::GetSingletonPtr()->Clear();
}

void CLogicMgr::GetLogic( CCfgCnsLogic **pLogic )
{
    *pLogic = CCfgCnsLogic::GetSingletonPtr();	
}

void CLogicMgr::GetLogic( CCfgAudioPortLogic **pLogic )
{
    *pLogic = CCfgAudioPortLogic::GetSingletonPtr();	
}

 