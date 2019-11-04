// LayoutTag.h: interface for the LayoutTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYOUTTAG_H__F9942780_C46F_4E15_84D7_98A41692162E__INCLUDED_)
#define AFX_LAYOUTTAG_H__F9942780_C46F_4E15_84D7_98A41692162E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ITag.h"
namespace AutoUIFactory
{

/*---------------------------------------------------------------------
* 类	名：CLayoutTag
* 功    能：用于布局的标签
* 特殊说明：里面表示了当前窗口是否需要进行动态布局
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/10	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CLayoutTag : public IXmlTag
{
public:
	CLayoutTag();
	virtual ~CLayoutTag();
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext = 0 );
	virtual bool ElementEnd( String strElement,  void* pContext = 0 );
};

}

#endif // !defined(AFX_LAYOUTTAG_H__F9942780_C46F_4E15_84D7_98A41692162E__INCLUDED_)
