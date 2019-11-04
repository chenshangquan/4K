// ItemXmlHandle.h: interface for the CItemXmlHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMXMLHANDLE_H__0D89A944_118D_4FEA_94ED_3204EB689851__INCLUDED_)
#define AFX_ITEMXMLHANDLE_H__0D89A944_118D_4FEA_94ED_3204EB689851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IXmlHanlde.h"

namespace AutoUIFactory
{

class CItemXmlHandle : public IXmlHanlde
{
public:
	static const String strName;
	static const String strType;
public:
	CItemXmlHandle();
	virtual ~CItemXmlHandle();
/**  解析进入一个标签的时候处理函数
 *  @param[in] strElement 标签名
 *  @param[in] xmlAttributes 所获取到的属性
 *  @return 是否成功
 */
	bool ElementStart( String strElement, const XMLAttributes& xmlAttributes );

/**  解析出一个标签的时候处理函数
 *  @param[in] strElement 标签名
 *  @node 一般来说，这里就是把当前的状态切换，如果是窗口读取，就需要设置当前窗口为前一个
 *  @return 是否成功
 */
	bool ElementEnd( String strElement );
};

}

#endif // !defined(AFX_ITEMXMLHANDLE_H__0D89A944_118D_4FEA_94ED_3204EB689851__INCLUDED_)
