// RegDefaultData.h: interface for the CRegDefaultData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGDEFAULTDATA_H__46668158_5ACE_4AC5_8DBA_7C562AF7320F__INCLUDED_)
#define AFX_REGDEFAULTDATA_H__46668158_5ACE_4AC5_8DBA_7C562AF7320F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "uifactorydef.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：CRegDefaultData
* 功    能：注册一些默认数据
* 特殊说明：一般只给System用
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
/*
添加一个新控件的流程
1、添加工厂，如果你的空间名为CXXX，请用宏DECLARE_WINDOW_FACTORY(CXXX)
2、添加了工厂，需要到CRegDefaultData里面的RegDefaultWindowFactory函数里面注册
	请使用宏REG_WINDOW_FACTORY(CXXX)
3、控件写好后，需要为其添加属性集，请使用宏 DECLARE_PROPERTYSET_BEGIN( CXXX, IPropertySet ) 和 DECLARE_PROPERTYSET_END
	如果需要集成一些默认的属性，请将IPropertySet修改为CWndPropertySet
4、写好控件集过后，需要在CRegDefaultData里面的RegDefaultWindowPropertySet函数里面注册
	也请使用宏REG_PROPERTY_SET(CXXX)
5、如果控件有新添加的属性，请使用宏DECLARE_VALUE_BEGIN(CXXXImage) DECLARE_VALUE_END 进行申明
	具体注意事项请参看宏
6、新属性如果需要替换老属性：比如CXXXImage需要替换WindowPos这个属性，直接在第3步的宏中间添加
	AddProperty( "WindowPos", "CXXXImage" );
7、添加新属性后，需要在CRegDefaultData里面的RegDefaultWindowProperty函数里面注册
	使用宏REG_PROPERTY(CXXXImage)
*/
class CRegDefaultData  
{
public:
	CRegDefaultData();
	virtual ~CRegDefaultData();
/*
*  注册全部数据
*/
	static void RegAllDefaultData();
/*
 * 注册默认的工厂\n 
 */
	static void RegDefaultWindowFactory();
/*
 * 注册默认的属性\n 
 */
	static void RegDefaultWindowProperty();
/*
 * 注册默认属性集\n 
 */
	static void RegDefaultWindowPropertySet();
/*
 * 注册默认事件\n 
 */
	static void RegDefaultWindowEvent();
	
/*
 * 注册uilib的工厂\n
 */
	static void RegUILibWindowFactory();

/*
 * 注册uilib控件的属性集\n 
 */
	static void RegUILibPropertySet();

/*
 * 注册默认的风格\n 
 */
	static void RegDefaultStyle();

/*
 * 注册默认的算法\n
 */
	static void RegDefaultAlgorithm();
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_REGDEFAULTDATA_H__46668158_5ACE_4AC5_8DBA_7C562AF7320F__INCLUDED_)
