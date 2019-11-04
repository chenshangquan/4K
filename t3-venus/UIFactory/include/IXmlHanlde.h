// IXmlHanlde.h: interface for the IXmlHanlde class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IXMLHANLDE_H__2C7B1485_9344_4DCD_8F6C_C166364C71D4__INCLUDED_)
#define AFX_IXMLHANLDE_H__2C7B1485_9344_4DCD_8F6C_C166364C71D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AutoUIFactory
{
#include "uifactorydef.h"
#include "XmlAttrib.h"

/*---------------------------------------------------------------------
* 类	名：IXmlHanlde
* 功    能：xml文件解析基类
* 特殊说明：xml每个节点的解析只有两种模式，一种就是进去，一种就是出来
*			进去的时候获得了属性，出来的时候释放资源、设置当前状态
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
Interface IXmlHanlde  
{
public:
	IXmlHanlde();
	virtual ~IXmlHanlde();
/**  解析进入一个标签的时候处理函数
 *  @param[in] strElement 标签名
 *  @param[in] xmlAttributes 所获取到的属性
 *  @return 是否成功
 */
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes ) = 0;

/**  解析出一个标签的时候处理函数
 *  @param[in] strElement 标签名
 *  @node 一般来说，这里就是把当前的状态切换，如果是窗口读取，就需要设置当前窗口为前一个
 *  @return 是否成功
 */
	virtual bool ElementEnd( String strElement ) = 0;
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_IXMLHANLDE_H__2C7B1485_9344_4DCD_8F6C_C166364C71D4__INCLUDED_)
