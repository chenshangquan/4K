// IPropertyAssist.h: interface for the IPropertyAssist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPROPERTYASSIST_H__15CEDED9_6BB9_4167_A3EC_7DBA88E0906E__INCLUDED_)
#define AFX_IPROPERTYASSIST_H__15CEDED9_6BB9_4167_A3EC_7DBA88E0906E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "System.h"
#include "IProperty.h"
#include "PropertySet.h"
namespace AutoUIFactory
{
class CPropertyAssist : public Singleton< CPropertyAssist >
{
public:
	static const String strName;
	static const String strValue;
public:
	CPropertyAssist();
	virtual ~CPropertyAssist();
/**  为一个窗口设置属性
 *  @param[in] xmlAttrib 属性所代表的xml信息
 *  @param[in] window 窗口
 *  @param[in] strWndType 窗口类型
 *  @return 是否设置成功
 *  @note 窗口类型决定了会到哪个PropertySet里面去查询，然后根据xmlAttrib里面的名字去找到Property，最后设置window属性
 */
	bool SetProperty( const XMLAttributes& xmlAttrib, const Window* window, const String& strWndType );
/**  通过Value对控件设值
 *  @param[in] value 所传入的值
 *  @param[in] window 对应窗口
 *  @param[in] strWndType 窗口类型
 *  @return 是否设置成功
 */
	bool SetProperty( const IValue& value, const Window* window,  const String& strWndType );

/**  获取一个窗口特定的值
 *  @param[out] value 需要返回的值
 *  @param[in] 参见；
 *  @param[out] 参见；
 *  @return 返回写入的长度
 */
	bool GetValue( IValue& value, const Window* window, const String& strWndType );


/** 清空所有属性和属性集 
 *  @return  
 *  @mark 当推出uifactory时使用  2012.12.3 yjj
 */
	void ClearAllProperty();
	void ClearAllPropertySet();

public:
/**  在全局的一个属性表里面添加一个属性
 *  @param[in] strName 属性名，必须全局唯一
 *  @param[in] piProperty 属性
 *  @return 返回设置是否成功
 */
	bool AddProperty( String strName, IProperty* piProperty, bool bCover = false );

/**  在全局的一个属性表里面获取一个属性
 *  @param[in] strName 属性名
 *  @return 对应的属性
 */
	IProperty* GetProperty( String strName );

/**  向全局的一个属性集的表里面添加一个属性集
 *  @param[in] strName 属性集名字 必须唯一
 *  @param[in] piPropertySet 属性集
 *  @return 是否添加成功
 */
	bool AddPropertySet( String strName, IPropertySet* piPropertySet, bool bCover = false );

/**  向全局的一个属性集的表里面获取一个属性集
 *  @param[in] strName 属性集名字 必须唯一
 *  @return 属性集
 */
	IPropertySet* GetPropertySet( String strName );

/**  通过传入窗口类型，获取到属性集，然后通过该属性集，获得需要的属性
 *  @param[in] strWndType 窗口类型
 *  @param[in] strName 窗口名称
 *  @return 属性
 */
	IProperty* GetPropertyByCommonName( String strWndType, String strName );

/**  添加属性到属性集中
 *  @param[in] strWndType 窗口类型
 *  @param[in] strProperty 属性名，value类型
 *  @param[in] strValue 属性类名
 *  @return 是否设置成功 
 *  @mark 用于在已有属性集中动态添加 -2012.12.14 xcr
          strProperty是IValue子类，而strValue是IProperty子类
 */
    bool AddPropertyToSet( String strWndType, String strProperty, String strValue );

protected:
	typedef std::map< String, IProperty* > PropertyMap;
/*
 * 全局的一个属性的表\n 
 * 这里面存了不同控件不同的属性，比如就Size这一项 \n
 * 里面就有ButtonSize,BmpButtonSize,WindowSize等
 */
	PropertyMap m_mapProperties;

	typedef std::map< String, IPropertySet* > PropertySetMap;
/*
 * 全局的一个属性集的表\n 
 * 属性集里面存的是一类窗口公用的属性，String对String的，\n
 * 前面个String是公用的名字，后面一个String对应的就是全局的属性表里面的名字
 */
	PropertySetMap m_mapPropertySets;
};

/*
* 注册属性
* name 属性 className属性对应的处理类
* 为了保证命名一致，所以注册的时候需要按照要求填写宏
* 如果不想用这样的明明方式，可以写其他宏，或者直接调用对应函数
*/
#define REG_PROPERTY( name ) \
CPropertyAssist::GetSingletonPtr()->AddProperty( #name, new Property_##name )

/*
* 注册属性集
* name 属性 className属性集类
* 为了保证命名一致，所以注册的时候需要按照要求填写宏
* 如果不想用这样的明明方式，可以写其他宏，或者直接调用对应函数
*/
#define REG_PROPERTY_SET( name ) \
CPropertyAssist::GetSingletonPtr()->AddPropertySet( #name, new name##PropertySet )

/*
* 在属性集中增加新属性
* wndtype 窗口类型 propertyname属性类型 valuename属性类名
* 用于在程序中向已有属性集动态添加属性
* 为了保证命名一致，所以注册的时候需要按照要求填写宏
*/
#define ADD_PROPERTY_TO_SET( wndtype, propertyname, valuename ) \
CPropertyAssist::GetSingletonPtr()->AddPropertyToSet( #wndtype, propertyname, valuename )


} // namespace AutoUIFactory end
#endif // !defined(AFX_IPROPERTYASSIST_H__15CEDED9_6BB9_4167_A3EC_7DBA88E0906E__INCLUDED_)

