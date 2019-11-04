// WindowTag.h: interface for the CWindowTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWTAG_H__8D2CCF46_1DD6_45D4_8914_F75C8423D7BA__INCLUDED_)
#define AFX_WINDOWTAG_H__8D2CCF46_1DD6_45D4_8914_F75C8423D7BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ITag.h"
/*---------------------------------------------------------------------
* 类	名：CWindowTag
* 功    能：专门解析Window标签
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/12	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
namespace AutoUIFactory
{

class CWindowTag : public IXmlTag
{
public:
	const static String strName;
	const static String strValue;
	const static String strType;
	const static String strArgs;
	const static String strStyle;
	const static String strExStyle;
	const static String strModal; //是否为模态窗口 2012.12.3 yjj
	enum emWndCreateArg
	{
		CreateByFactory = 0,
		CreateByXml,
	};
public:
	CWindowTag();
	virtual ~CWindowTag();
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext = 0 );
	virtual bool ElementEnd( String strElement,  void* pContext = 0 );
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_WINDOWTAG_H__8D2CCF46_1DD6_45D4_8914_F75C8423D7BA__INCLUDED_)
