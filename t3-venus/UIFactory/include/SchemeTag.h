// SchemeTag.h: interface for the CSchemeTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHEMETAG_H__4E849144_0685_462D_8537_968273470C02__INCLUDED_)
#define AFX_SCHEMETAG_H__4E849144_0685_462D_8537_968273470C02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ITag.h"
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：CSchemeTag
* 功    能：方案的tag，主要存储不同状态下UI的变化
* 特殊说明：在不同状态下，button可以绑定不同的事件
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/07/01	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CSchemeTag : public IXmlTag
{
public:
	const static String strName;
public:
	CSchemeTag();
	virtual ~CSchemeTag();
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext = 0 );
	virtual bool ElementEnd( String strElement,  void* pContext = 0 );
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_SCHEMETAG_H__4E849144_0685_462D_8537_968273470C02__INCLUDED_)
