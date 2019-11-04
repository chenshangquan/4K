// DefaultScript.h: interface for the CDefaultScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFAULTSCRIPT_H__C30C34C8_D237_468D_8E75_3149EB55F7A6__INCLUDED_)
#define AFX_DEFAULTSCRIPT_H__C30C34C8_D237_468D_8E75_3149EB55F7A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IScript.h"
namespace AutoUIFactory
{
class CDefaultScript : public IScript
{
public:
	CDefaultScript();
	~CDefaultScript();
	virtual bool ExecuteScript( String strScript, String strTpye = 0 );
};
} // namespace AutoUIFactory end
#endif // !defined(AFX_DEFAULTSCRIPT_H__C30C34C8_D237_468D_8E75_3149EB55F7A6__INCLUDED_)
