// ITag.h: interface for the ITag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITAG_H__E9FF08A1_6D88_4675_B727_EEE6718717A4__INCLUDED_)
#define AFX_ITAG_H__E9FF08A1_6D88_4675_B727_EEE6718717A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*---------------------------------------------------------------------
* 类	名：IXmlTag
* 功    能：用于分析xml标签的类、每类标签对应一种解析类
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/11	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
#include "XmlAttrib.h"
namespace AutoUIFactory
{

Interface IXmlTag  
{
public:
	IXmlTag();
	virtual ~IXmlTag();
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext = 0 ) = 0;
	virtual bool ElementEnd( String strElement,  void* pContext = 0 ) = 0;
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_ITAG_H__E9FF08A1_6D88_4675_B727_EEE6718717A4__INCLUDED_)
