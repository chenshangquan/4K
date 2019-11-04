// umclib.h: interface for the CUmcLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UMCLIB_H__0716A064_82EA_4A2A_AF20_4D58037DB76E__INCLUDED_)
#define AFX_UMCLIB_H__0716A064_82EA_4A2A_AF20_4D58037DB76E__INCLUDED_

//#ifndef UMCLIB_H
//#define UMCLIB_H

#pragma warning( disable : 4786 )	// 标识符名称超过255字节	// 标识符名称超过255字节
#include "kdvtype.h"
#include "umsSessionCtrlIF.h" 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

  
/*功  能	创建session
参  数	无
返回值	 
说  明	无*/
void	CreateUmsSession( CUmsSessionCtrlIF ** ppSession = NULL, u16 wAppId = AID_CMS2UMS_APP, BOOL bUseAddr = TRUE );

/*功  能	销毁session
参  数	无
返回值	 
说  明	无*/
void    DesdoryUmsSession( CUmsSessionCtrlIF ** ppSession );

 

#endif // !defined(AFX_UMCLIB_H__0716A064_82EA_4A2A_AF20_4D58037DB76E__INCLUDED_)
