// SaveXmlHelp.h: interface for the CSaveXmlHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAVEXMLHELP_H__9D9CD1F7_4740_46CB_9C75_E962E2116EDD__INCLUDED_)
#define AFX_SAVEXMLHELP_H__9D9CD1F7_4740_46CB_9C75_E962E2116EDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "templateClass.h"
#include "uifactorydef.h"
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：CSaveXmlHelp
* 功    能：用于保存UI的信息到文件
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CSaveXmlHelp  
{
public:
	CSaveXmlHelp();
	virtual ~CSaveXmlHelp();
/**  保存一个UI的信息到一个xml文件
 *  @param[in] strWindow 窗口名
 *  @param[in] strSavePropertyName 要保存的属性名
 *  @param[in] bForceSave 如果要保存的属性不在当前方案中，是否强制保存
 *  @return 是否成功
 */
	static bool SaveXml( String strWindow,string strWndName = "" , string strSavePerpertyName = "" ,BOOL bForceSave = FALSE );
 

};

} // namespace AutoUIFactory end
#endif // !defined(AFX_SAVEXMLHELP_H__9D9CD1F7_4740_46CB_9C75_E962E2116EDD__INCLUDED_)
