// EventTag.h: interface for the CEventTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTTAG_H__95194AC1_C546_4698_B1F2_9FB61F33E919__INCLUDED_)
#define AFX_EVENTTAG_H__95194AC1_C546_4698_B1F2_9FB61F33E919__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ITag.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：CEventTag
* 功    能：事件标签，用于分析时间标签，基本上就是注册事件
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CEventTag : public IXmlTag
{
public:
	const static String strEventID;
	const static String strFuncType;
	const static String strFunc;
public:
	CEventTag();
	virtual ~CEventTag();
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext = 0 );
	virtual bool ElementEnd( String strElement,  void* pContext = 0 );
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_EVENTTAG_H__95194AC1_C546_4698_B1F2_9FB61F33E919__INCLUDED_)
