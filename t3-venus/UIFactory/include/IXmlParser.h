// IXmlParser.h: interface for the IXmlParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IXMLPARSER_H__6ED0A159_76CD_41B6_9049_EEAA15B70723__INCLUDED_)
#define AFX_IXMLPARSER_H__6ED0A159_76CD_41B6_9049_EEAA15B70723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AutoUIFactory
{

class IXmlHanlde;
/*---------------------------------------------------------------------
* 类	名：IXmlParser
* 功    能：xml的一个解析基类，目前默认的解析类是用的tinyxml
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
Interface IXmlParser : public Singleton<IXmlParser>
{
public:
	IXmlParser();
	virtual ~IXmlParser();
/**  解析xml文件
 *  @param[in] piXmlHandle 处理类
 *  @param[in] strFileName 文件名
 *  @return 是否成功
 */
	virtual bool ParserXml( IXmlHanlde* piXmlHandle, String strFileName ) = 0;
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_IXMLPARSER_H__6ED0A159_76CD_41B6_9049_EEAA15B70723__INCLUDED_)
