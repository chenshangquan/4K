// logicmanage.cpp: implementation of the CLogicManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umstooldll.h"
#include "logicmanage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogicManage*CLogicManage::m_pLogicManage = NULL;

CLogicManage::CLogicManage() :m_tplLogicList()
{

}

CLogicManage::~CLogicManage()
{

}

CLogicManage *CLogicManage::GetLogicManagePtr()
{
	if ( NULL == m_pLogicManage ) 
	{
		m_pLogicManage = new CLogicManage();

        REG_MSG_HANDLER( UI_UMS_DISCONNECTED, CLogicManage::OnDisConnect, m_pLogicManage, CLogicManage );
        REG_MSG_HANDLER( UI_UMS_GRAB_LOGIN_NOTIFY, CLogicManage::OnLoginGrab, m_pLogicManage, CLogicManage );

	} 

	return m_pLogicManage;
}

HRESULT CLogicManage::OnDisConnect( WPARAM wparam, LPARAM lparam ) 
{
	ClearAllLogic();

    return NO_ERROR;
}

HRESULT CLogicManage::OnLoginGrab( WPARAM wparam, LPARAM lparam )
{
	ClearAllLogic();

	CUmstoolCommon::NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_GRAP, wparam );

    return NO_ERROR;
}

void CLogicManage::ClearAllLogic()
{
	MSGBOXLOGICRPTR->Clear();
	SYSINFOLOGICRPTR->Clear();
	CORRELATIVECFGLOGICRPTR->Clear();
	ADDRBOOKEXPLOGICRPTR->Clear();
	TEMPLATEEXPLOGICRPTR->Clear();
	UMSCFGLOGICRPTR->Clear();
	BOARDOPTLOGICRPTR->Clear();
	BOARDLOGICRPTR->Clear();
	TVWBOARDLOGICRPTR->Clear();
	NETMNGOPTLOGICRPTR->Clear();
	NETMNGCFGLOGICRPTR->Clear();
	TVWSTYLELOGICRPTR->Clear();
	TVWSTYLEOPTLOGICRPTR->Clear();
	IMPCOMMONLOGICRPTR->Clear();
	EXPCOMMONLOGICRPTR->Clear();
	VTRCFGLOGICRPTR->Clear();
	VTROPTLOGICRPTR->Clear();
	VTROPTLOGICRPTR->Clear();
	MAINFRMLOGICRPTR->Clear();
	WARNINGLOGICRPTR->Clear();
	BACKUPCFGLOGICRPTR->Clear();
}

void CLogicManage::DestroyLogic( CWndLogicBase *pLogic )
{
   	int nCnt = m_tplLogicList.Size();
	for ( int i = 0; i< nCnt; i++ ) 
	{  
		CWndLogicBase *p = m_tplLogicList.GetAt(i);
		if ( pLogic == p )
		{
			SAFE_RELEASE(p);
         
			m_tplLogicList.Delete( i );
			break;
		} 
	}
}

void CLogicManage::DestroyLogic()
{
	int nCnt = m_tplLogicList.Size();
	for ( int i = 0; i< nCnt; i++ ) 
	{  
		CWndLogicBase *p = m_tplLogicList.GetAt(i);
		if ( NULL != p )
		{
			delete p;
			p = NULL;
		} 
	}

	m_tplLogicList.Clear();
}

const  TplArray<CWndLogicBase*>* CLogicManage::GetLogicList() const
{
	return &m_tplLogicList;
}

void CLogicManage::OnNotify( WPARAM wparam ,LPARAM lparam )
{

}

void CLogicManage::CreateLogic()
{  
 	MAINFRMLOGICRPTR->InitLogic();
 	SYSINFOLOGICRPTR->InitLogic();
	CORRELATIVECFGLOGICRPTR->InitLogic();
 	ADDRBOOKEXPLOGICRPTR->InitLogic();
	TEMPLATEEXPLOGICRPTR->InitLogic();
	BOARDLOGICRPTR->InitLogic();
	UMSCFGLOGICRPTR->InitLogic();
	BOARDOPTLOGICRPTR->InitLogic();
	MSGBOXLOGICRPTR->InitLogic();
	TVWBOARDLOGICRPTR->InitLogic();
	NETMNGCFGLOGICRPTR->InitLogic();
	NETMNGOPTLOGICRPTR->InitLogic();
	TVWSTYLELOGICRPTR->InitLogic();
	TVWSTYLEOPTLOGICRPTR->InitLogic();
	IMPCOMMONLOGICRPTR->InitLogic();
	EXPCOMMONLOGICRPTR->InitLogic();
	VTRCFGLOGICRPTR->InitLogic();
	VTROPTLOGICRPTR->InitLogic();
	VTROPTLOGICRPTR->InitLogic();
	WARNINGLOGICRPTR->InitLogic();
	BACKUPCFGLOGICRPTR->InitLogic();

} 

