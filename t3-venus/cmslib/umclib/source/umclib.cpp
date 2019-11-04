// umclib.cpp: implementation of the CUmcLib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umclib.h"
#include "umsSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
void  CreateUmsSession( CUmsSessionCtrlIF ** ppSession,  u16 wAppId, BOOL bUseAddr )
{   
	if ( NULL == *ppSession )
	{
		*ppSession = new CUmsSession(wAppId, bUseAddr);
	}
}
  
   
void  DesdoryUmsSession( CUmsSessionCtrlIF ** ppSession )
{
	CUmsSession *p = dynamic_cast<CUmsSession*> (*ppSession);
	if ( NULL != p)
	{
		delete p;
		p = NULL;
	}

}