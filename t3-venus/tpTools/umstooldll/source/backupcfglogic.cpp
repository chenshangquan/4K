// backupcfglogic.cpp: implementation of the CBackupCfgLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umstooldll.h"
#include "backupcfglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBackupCfgLogic::CBackupCfgLogic()
: m_strDlgAsHost( "BackupCfgDlg/AsHostDlg" )
, m_strDlgAsBackup( "BackupCfgDlg/AsBackupDlg" )
, m_strBtnRadioAsHost( "RadioAsHost" )
, m_strBtnRadioAsBackup( "RadioAsBackup" )
, m_strBtnRadioTime1( "AsBackupDlg/RadioTime1" )
, m_strBtnRadioTime2( "AsBackupDlg/RadioTime2" )
, m_strBtnRadioTime3( "AsBackupDlg/RadioTime3" )
, m_strBtnRadioCount1( "AsBackupDlg/RadioCount1" )
, m_strBtnRadioCount2( "AsBackupDlg/RadioCount2" )
, m_strBtnRadioCount3( "AsBackupDlg/RadioCount3" )
, m_strIPBackupIP( "IPBackupIP" )
{
}

CBackupCfgLogic::~CBackupCfgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CBackupCfgLogic::RegMsg()
{    

}

void CBackupCfgLogic::UnRegMsg()
{

}

bool CBackupCfgLogic::RegCBFun()
{ 
	REG_GOBAL_MEMBER_FUNC( "CBackupCfgLogic::InitWnd", CBackupCfgLogic::InitWnd, BACKUPCFGLOGICRPTR, CBackupCfgLogic);
	REG_GOBAL_MEMBER_FUNC( "CBackupCfgLogic::OnBtnRadioIsAsHost", CBackupCfgLogic::OnBtnRadioIsAsHost, BACKUPCFGLOGICRPTR, CBackupCfgLogic);
	REG_GOBAL_MEMBER_FUNC( "CBackupCfgLogic::OnBtnRadioIsAsBackup", CBackupCfgLogic::OnBtnRadioIsAsBackup, BACKUPCFGLOGICRPTR, CBackupCfgLogic);
	REG_GOBAL_MEMBER_FUNC( "CBackupCfgLogic::OnBtnRadioTime", CBackupCfgLogic::OnBtnRadioTime, BACKUPCFGLOGICRPTR, CBackupCfgLogic);
	REG_GOBAL_MEMBER_FUNC( "CBackupCfgLogic::OnBtnRadioCount", CBackupCfgLogic::OnBtnRadioCount, BACKUPCFGLOGICRPTR, CBackupCfgLogic);
	REG_GOBAL_MEMBER_FUNC( "CBackupCfgLogic::OnBtnSwitchBackupClick", CBackupCfgLogic::OnBtnSwitchBackupClick, BACKUPCFGLOGICRPTR, CBackupCfgLogic);
	return true;
}

bool CBackupCfgLogic::UnRegFunc()
{
	return true;
}


bool CBackupCfgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

	Clear();

    return true;
}

void CBackupCfgLogic::Clear()
{
// 	memset( m_abyBackupInfo, 0, sizeof(m_abyBackupInfo) );
// 	memset( m_abyOldBackupInfo, 0, sizeof(m_abyOldBackupInfo) );

	InitLogicData();
}

void CBackupCfgLogic::InitLogicData()
{
	UIFACTORYMGR_PTR->SetCheckState( m_strBtnRadioTime1, 1, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strBtnRadioTime2, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strBtnRadioTime3, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strBtnRadioCount1, 1, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strBtnRadioCount2, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strBtnRadioCount3, 0, m_pWndTree );

	//默认显示 做为主用机 对话框
	UIFACTORYMGR_PTR->SetCheckState( m_strBtnRadioAsHost, 1, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strBtnRadioAsBackup, 0, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strDlgAsHost, true );
	UIFACTORYMGR_PTR->ShowWindow( m_strDlgAsBackup, false );

// 	Value_IpEditData valIp;
// 	valIp.dwIP = ntohl( 0 );
//  UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strIPBackupIP, m_pWndTree ); 
//	UIFACTORYMGR_PTR->SetPropertyValue( "", m_strIPBackupIP, m_pWndTree ); 
}

bool CBackupCfgLogic::OnBtnRadioIsAsHost( const IArgs & arg )
{
	UIFACTORYMGR_PTR->ShowWindow( m_strDlgAsHost, true );
	UIFACTORYMGR_PTR->ShowWindow( m_strDlgAsBackup, false );
	return true;
}

bool CBackupCfgLogic::OnBtnRadioIsAsBackup( const IArgs & arg )
{	
	UIFACTORYMGR_PTR->ShowWindow( m_strDlgAsHost, false );
	UIFACTORYMGR_PTR->ShowWindow( m_strDlgAsBackup, true );

	return true;
}

bool CBackupCfgLogic::OnBtnRadioTime( const IArgs & arg )
{	

	return true;
}

bool CBackupCfgLogic::OnBtnRadioCount( const IArgs & arg )
{

	return true;
}

bool CBackupCfgLogic::OnBtnSwitchBackupClick( const IArgs & arg )
{

	return true;
}