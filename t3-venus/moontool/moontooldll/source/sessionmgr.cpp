#include "stdafx.h"
#include "moonToolDll.h"
#include "sessionmgr.h"
#include "tpmsginit.h"

CMoonlibSessionMgr* CMoonlibSessionMgr::m_pThis = NULL;

CMoonlibSessionMgr::CMoonlibSessionMgr():
 				  m_pMoonSessionIF(NULL)
{
	CreateSession();
}

CMoonlibSessionMgr::~CMoonlibSessionMgr()
{
	DestroySession(); 
}

CMoonlibSessionMgr* CMoonlibSessionMgr::GetSingleTon()
{
	if ( m_pThis == NULL )
    {
        m_pThis = new CMoonlibSessionMgr();	 
    }
	return m_pThis;
}

void CMoonlibSessionMgr::CreateSession()
{
#if 0
	InitTpEvent();
#endif
	//´´½¨cnssession
	CRckLib::CreateSession( &m_pMoonSessionIF );
	if ( NULL == m_pMoonSessionIF )
	{
		return;
	}
#if 0
	m_pMoonSessionIF->InitEnv( AID_MOONTOOL2CAM_APP );
#endif
	// if point init 
    m_pMoonSessionIF->RkcGetInterface( &m_pSysCtrlIf );
	m_pMoonSessionIF->RkcGetInterface( &m_pCamConfigIF );
	m_pMoonSessionIF->RkcGetInterface( &m_pSysConfigIF );
    
}

void CMoonlibSessionMgr::DestroySession()
{
 	CRckLib::DestroySession( &m_pMoonSessionIF );
     
 	m_pMoonSessionIF = NULL;
 
	if (  NULL != m_pThis)
	{
		delete m_pThis;
		m_pThis = NULL;		
	}
}
