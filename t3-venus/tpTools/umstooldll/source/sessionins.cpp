// sessionins.cpp: implementation of the CSessionIns class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umstooldll.h"
#include "sessionins.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSessionIns::CSessionIns():
m_pUmsSessCtrlIF(NULL),
m_pUserCtrlIF(NULL),
m_pSysInfoCtrlIF(NULL),
m_pTvwBoardCtrlIF(NULL),
m_pBoardCtrlIFIF(NULL),
m_pExportCtrlIF(NULL),
m_pConfigCtrlIF(NULL),
m_pNetMngCtrlIF(NULL),
m_pVTRCtrlIF(NULL)
{
	InitTpEvent();
}

CSessionIns::~CSessionIns()
{
}

BOOL CSessionIns::CreateSession( u16 wAppId )
{
	if ( NULL == m_pUmsSessCtrlIF )
	{
		CreateUmsSession( &m_pUmsSessCtrlIF, wAppId, FALSE ); 
		
		if ( NULL == m_pUmsSessCtrlIF )
		{
			return FALSE;
		}
		
		m_pUmsSessCtrlIF->GetCtrlInterface( &m_pUserCtrlIF );
		m_pUmsSessCtrlIF->GetCtrlInterface( &m_pSysInfoCtrlIF );
		m_pUmsSessCtrlIF->GetCtrlInterface( &m_pTvwBoardCtrlIF );
		m_pUmsSessCtrlIF->GetCtrlInterface( &m_pBoardCtrlIFIF );
		m_pUmsSessCtrlIF->GetCtrlInterface( &m_pExportCtrlIF );
		m_pUmsSessCtrlIF->GetCtrlInterface( &m_pConfigCtrlIF );
		m_pUmsSessCtrlIF->GetCtrlInterface( &m_pNetMngCtrlIF );
		m_pUmsSessCtrlIF->GetCtrlInterface( &m_pVTRCtrlIF );
	}

	return TRUE;
}

BOOL CSessionIns::DisConnectUms()
{
	if ( NULL != m_pUmsSessCtrlIF )
	{
		m_pUmsSessCtrlIF->DisconnectUms();
	}

	return TRUE;
}

void CSessionIns::DesdroySession()
{   
	DesdoryUmsSession( &m_pUmsSessCtrlIF );
	m_pUmsSessCtrlIF = NULL;
	m_pUserCtrlIF = NULL;
	m_pSysInfoCtrlIF = NULL;
	m_pTvwBoardCtrlIF = NULL;
	m_pBoardCtrlIFIF = NULL;
	m_pExportCtrlIF = NULL;
	m_pConfigCtrlIF = NULL;
	m_pNetMngCtrlIF = NULL;
	m_pVTRCtrlIF = NULL;
}

