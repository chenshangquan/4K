#include "stdafx.h"
#include "cnsToolDll.h"
#include "sessionmgr.h"
#include "tpmsginit.h"

CCnclibSessionMgr* CCnclibSessionMgr::m_pThis = NULL;

CCnclibSessionMgr::CCnclibSessionMgr():
 				  m_pCnsSessionIF(NULL),
				  m_pCnsConfigIF(NULL),
				  m_pCnsConfIF(NULL),
				  m_pCenterCtrlIF(NULL),
				  m_pPortDiagIF(NULL),
				  m_pSysCtrlIF(NULL),				 
				  m_pSipInfoIF(NULL),
				  m_pNetMngCtrlIF(NULL)
{
	CreateSession();
}

CCnclibSessionMgr::~CCnclibSessionMgr()
{
	//DesdroySession(); 
}

CCnclibSessionMgr* CCnclibSessionMgr::GetSingleTon()
{
	if ( m_pThis == NULL )
    {
        m_pThis = new CCnclibSessionMgr();	 
    }
	return m_pThis;
}

void CCnclibSessionMgr::CreateSession()
{
	InitTpEvent();
	//´´½¨cnssession
	CCncLib::CreateSession( &m_pCnsSessionIF );
	if ( NULL == m_pCnsSessionIF )
	{
		return;
	}
	m_pCnsSessionIF->SetUseAddrbook( FALSE );
	m_pCnsSessionIF->InitEnv( AID_CNSTOOL2CNS_APP );
	
	m_pCnsSessionIF->CncGetInterface( &m_pCnsConfigIF );
	
	m_pCnsSessionIF->CncGetInterface( &m_pCnsConfIF );
		
	m_pCnsSessionIF->CncGetInterface( &m_pSipInfoIF );
 
  	m_pCnsSessionIF->CncGetInterface( &m_pSysCtrlIF ) ;
     	
	m_pCnsSessionIF->CncGetInterface( &m_pPortDiagIF ) ;
      
	m_pCnsSessionIF->CncGetInterface( &m_pCenterCtrlIF ) ;
	m_pCnsSessionIF->CncGetInterface( &m_pNetMngCtrlIF );
    
}

void CCnclibSessionMgr::DesdroySession()
{
	CCncLib::DestroySession( &m_pCnsSessionIF );
    
	m_pCnsSessionIF = NULL;
	m_pCenterCtrlIF = NULL;
	m_pPortDiagIF = NULL;
	m_pSysCtrlIF = NULL;
	m_pCnsConfigIF = NULL;
	m_pCnsConfIF = NULL;
	m_pSipInfoIF = NULL;
	m_pNetMngCtrlIF = NULL;

	if (  NULL != m_pThis)
	{
		delete m_pThis;
		m_pThis = NULL;		
	}
}
