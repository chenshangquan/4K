// DefaultXmlParser.h: interface for the DefaultXmlParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFAULTXMLPARSER_H__9DE688AD_807B_4988_BC2D_1D4596501AE2__INCLUDED_)
#define AFX_DEFAULTXMLPARSER_H__9DE688AD_807B_4988_BC2D_1D4596501AE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IXmlParser.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：DefaultXmlParser
* 功    能：默认xml解析类，用了tinyxml
* 特殊说明：如果需要解析中文，请将xml文件里面的编码变成gb2312
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class DefaultXmlParser : public IXmlParser
{
public:
	DefaultXmlParser(void){}
	~DefaultXmlParser(void){}
	
/**  解析xml文件
 *  @param[in] piXmlHandle 处理句柄
 *  @param[in] strFileName 文件路径
 *  @return 是否成功
 */
	bool ParserXml( IXmlHanlde* piXmlHandle, String strFileName );
	
protected:
	// Implementation of abstract interface.
	bool initialiseImpl(void);
	void cleanupImpl(void);
};

}
#endif // !defined(AFX_DEFAULTXMLPARSER_H__9DE688AD_807B_4988_BC2D_1D4596501AE2__INCLUDED_)
