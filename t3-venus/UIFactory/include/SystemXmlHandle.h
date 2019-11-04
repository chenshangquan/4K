// SystemXmlHandle.h: interface for the CSystemXmlHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMXMLHANDLE_H__763DFA04_BC85_425C_AF11_484E6D6B2834__INCLUDED_)
#define AFX_SYSTEMXMLHANDLE_H__763DFA04_BC85_425C_AF11_484E6D6B2834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IXmlHanlde.h"
#include "ITag.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：CSystemXmlHandle
* 功    能：专门用于解析系统xml文件的一个类
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CSystemXmlHandle : public IXmlHanlde 
{
public:
	static const String strSystemInfo;
	static const String strWindowInfo;
	static const String strWindowInfoName;
	static const String strWindowInfoValue;
	static const String strImagePath;
	static const String strLayoutPath;
	static const String strItemInfo;
    static const String strResolution;//分辨率
public:
	CSystemXmlHandle();
	virtual ~CSystemXmlHandle();
/*---------------------------------------------------------------------
* 函 数 名：ElementStart
* 功    能：根据特定的标签去找相关的处理类
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/11	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes );
/*---------------------------------------------------------------------
* 函 数 名：
* 功    能：
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/11	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
	virtual bool ElementEnd( String strElement );
protected:
// /*---------------------------------------------------------------------
// * 函 数 名：WindowInfoStart
// * 功    能：读写WindowInfo
// * 参数说明：
// * 返 回 值：
// * 修改记录：
// * 日期			版本		修改人		修改记录
// * 2011/05/11	v1.0		牟兴茂		创建
// ----------------------------------------------------------------------*/
// 	bool WindowInfoStart( const XMLAttributes& xmlAttributes );
// 	bool WindowInfoEnd();
// /*---------------------------------------------------------------------
// * 函 数 名：SystemInfoStart
// * 功    能：读取SystemInfo
// * 参数说明：
// * 返 回 值：
// * 修改记录：
// * 日期			版本		修改人		修改记录
// * 2011/05/11	v1.0		牟兴茂		创建
// ----------------------------------------------------------------------*/
// 	bool SystemInfoStart( const XMLAttributes& xmlAttributes );
// 	bool SystemInfoEnd();
// 
// 	/*---------------------------------------------------------------------
// 	* 函 数 名：ItemInfoStart
// 	* 功    能：读取ItemInfo
// 	* 参数说明：
// 	* 返 回 值：
// 	* 修改记录：
// 	* 日期			版本		修改人		修改记录
// 	* 2011/05/11	v1.0		牟兴茂		创建
// 	----------------------------------------------------------------------*/
// 	bool ItemInfoStart( const XMLAttributes& xmlAttributes );
// 	bool ItemInfoEnd();
protected:
	typedef std::map<String, IXmlTag*> XmlTagMap;
	XmlTagMap    m_mapXmlTag;
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_SYSTEMXMLHANDLE_H__763DFA04_BC85_425C_AF11_484E6D6B2834__INCLUDED_)
