// datamgrimp.cpp: implementation of the CCommonMgrIF class.
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

//线程控制函数
UINT ThreadConnectUms(LPVOID lpParam)
{   
    u16 re= NO_ERROR;
    re = COMMONMGRIFPTR->LinkUms() ;
    if ( NO_ERROR != re )
    {    
        if ( ERR_UMC_ACTIVE_CONNECTION ==  re )
        {
            SendMessage( DATAMGRPTR->GetRecvWnd() ,UI_UMS_CONNECTED, TRUE, NO_ERROR);
        }
        else
        {
			SendMessage( DATAMGRPTR->GetRecvWnd() ,UI_UMS_CONNECTED, FALSE, ERR_UMC_CREATE_TCP_FAIL);
        }
    }
	
    return re;
} 

CCommonMgrIF::CCommonMgrIF()
{
}

CCommonMgrIF::~CCommonMgrIF()
{
}

void CCommonMgrIF::DestroyCommMgr()
{
}

/////////////////////////umslib req//////////////////////////////////////
u16 CCommonMgrIF::LinkUms()
{   
    u16 re = NO_ERROR;
    re = SESSIONPTR->GetSessionCtrlPtr()->ConnectUms( m_tLoginInfo.dwIp,  m_tLoginInfo.nPort,
            m_tLoginInfo.strName,  m_tLoginInfo.strPswd );
	
    return re;
}

u16 CCommonMgrIF::Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd )
{   
	u16 nReCon = NO_ERROR; 
	
    m_tLoginInfo.dwIp = dwIp;
    m_tLoginInfo.nPort = nPort;
    m_tLoginInfo.strName = pStrUserName;
	m_tLoginInfo.strPswd = pStrPswd;
	
	//连接ums
	AfxBeginThread( ThreadConnectUms , NULL );

	return nReCon;
} 

u16 CCommonMgrIF::DisConnect()
{
	SESSIONPTR->DisConnectUms();

	return NO_ERROR;
}

