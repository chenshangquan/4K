#ifndef _PROPERTYSET_H_
#define _PROPERTYSET_H_
#include "IProperty.h"

#include "uifactorydef.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：IPropertySet
* 功    能：提供一个映射关系，可以将某一类空间的属性映射到全局的一个属性表里面去
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class IPropertySet
{
public:
	IPropertySet(){}
	virtual ~IPropertySet(){}
	bool GetProperty( const String& strType, String& strProperty );
	bool AddProperty( String strProperty, String strValue );
	bool RemoveProperty( String strProperty );
protected:
	typedef std::map< String, String > CtrlPropertyMap;
	CtrlPropertyMap m_mapCtrlProperties;
};

/*
 *  用于定义属性集，默认所有窗口类空间都派生自CWndPropertySet \n
 *	如果需要添加新的属性，请在两个宏中间用AddProerty来进行添加\n 
 */
#define DECLARE_PROPERTYSET_BEGIN( classname,baseclass ) \
	class classname ## PropertySet : public baseclass \
{ \
public: \
classname ## PropertySet(){ \

#define DECLARE_PROPERTYSET_END } \
}; \

} // namespace AutoUIFactory end
#endif