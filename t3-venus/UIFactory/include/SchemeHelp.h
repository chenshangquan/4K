// SchemeHelp.h: interface for the CSchemeHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHEMEHELP_H__27822529_C4B3_45AC_91AC_C9663A514754__INCLUDED_)
#define AFX_SCHEMEHELP_H__27822529_C4B3_45AC_91AC_C9663A514754__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "templateClass.h"
#include "WindowManage.h"
namespace AutoUIFactory
{

class CSchemeHelp  
{
public:
	CSchemeHelp();
	virtual ~CSchemeHelp();
public:
	static bool LoadScheme( String strName, IWndTree* pWndTree );
	static bool ResetWindow( CTagInfo* pTagInfo, WndInfo* pInfo );
	static bool ResetWindowProperty( XMLAttributes& xmlAttribs, WndInfo* pInfo );
	static bool ResetWindowEvent( XMLAttributes& xmlAttribs, WndInfo* pInfo );
	static bool ResetWindowCallBackFunc( XMLAttributes& xmlAttribs, WndInfo* pInfo );
	static bool ResetWindowLayout( XMLAttributes& xmlAttribs, WndInfo* pInfo );
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_SCHEMEHELP_H__27822529_C4B3_45AC_91AC_C9663A514754__INCLUDED_)
