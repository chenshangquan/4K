#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H
#include "uifactorydef.h"
/*---------------------------------------------------------------------
* 类	名：windowfactory
* 功    能：UI控件工厂基类
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/09	v1.0		牟兴茂		创建
---------------------------------------------------------------------*/
namespace AutoUIFactory
{

class IWindowFactory
{
public:
	/*---------------------------------------------------------------------
	* 函 数 名：createWindow
	* 功    能：创建一个控件
	* 参数说明：[in] name 名称
	* 返 回 值：目前返回CWnd指针
	* 修改记录：
	* 日期			版本		修改人		修改记录
	* 2011/05/09	v1.0		牟兴茂		创建
	----------------------------------------------------------------------*/
	virtual Window* Create( IArgs& iAgrs ) = 0;

	static unsigned int GetUniqID()
	{
		static unsigned int wID = 10000;
		return wID++;
	}
public:
	static const DWORD m_dwDefaultStyle;
	static const DWORD m_dwDebugStyle;
	static const CRect m_rcDefaultRect;
};

#ifndef GETUNIQID
#define GETUNIQID IWindowFactory::GetUniqID()
#endif


#define DECLARE_WINDOW_FACTORY( classname ) \
class classname ## Factory : public IWindowFactory \
{ \
public: \
	virtual Window* Create( IArgs& iArgs ); \
}; 

/*---------------------------------------------------------------------
* 类	CWindowDefaultStyleMap
* 功    能：提供一个从字符串到风格Style转换，比如WS_VISIBLE是一个字符串，需要转换为宏
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CWindowDefaultStyleMap
{
public:
	static const char m_chPartitionChar;
public:
	/**  通过一个字符串转换为一个风格
	 *  @param[in] str 字符串
	 *  @param[out] dwStyle 风格
	 *  @return 是否成功
	 */
	static bool StringToStyle( String& str, DWORD& dwStyle );


    static bool StringToStyle( String& str, DWORD& dwStyle, DWORD& dwStyleEx );

	/**  注册一个风格对应关系 默认注册会在CRegDefaultData里面
	 *  @param[in] dwStyle	风格
	 *  @param[in] str		字符串
	 *  @return 是否成功
	 */
	static bool RegStyle( DWORD dwStyle, String str );
protected:
	typedef std::map< String, DWORD > DefaultStyleMap;
	static DefaultStyleMap m_mapStyles;
};

/*
 * 注册从一个ID到一个字符串的映射\n 
 */
#ifndef REG_DEFAULT_WINDOW_STYLE
#define REG_DEFAULT_WINDOW_STYLE( id ) CWindowDefaultStyleMap::RegStyle( id, #id );
#endif


} // namespace AutoUIFactory end
#endif