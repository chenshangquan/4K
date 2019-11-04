// CallBackFuncTag.h: interface for the CCallBackFuncTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALLBACKFUNCTAG_H__E8FC515A_620C_4277_8F3A_74864B848FC5__INCLUDED_)
#define AFX_CALLBACKFUNCTAG_H__E8FC515A_620C_4277_8F3A_74864B848FC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "ITag.h"
namespace AutoUIFactory
{

/*---------------------------------------------------------------------
* 类	名：CCallBackFuncTag
* 功    能：回调函数的标签处理，一般就是执行该回调函数
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CCallBackFuncTag : public IXmlTag
{
public:
	const static String strType;
	const static String strValue;
public:
	CCallBackFuncTag();
	virtual ~CCallBackFuncTag();
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext = 0 );
	virtual bool ElementEnd( String strElement,  void* pContext = 0 );
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_CALLBACKFUNCTAG_H__E8FC515A_620C_4277_8F3A_74864B848FC5__INCLUDED_)
