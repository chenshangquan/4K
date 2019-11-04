// XmlAttrib.h: interface for the XmlAttrib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLATTRIB_H__0AF36DA5_F4C4_4FDD_B86C_ED76F8B1DDEF__INCLUDED_)
#define AFX_XMLATTRIB_H__0AF36DA5_F4C4_4FDD_B86C_ED76F8B1DDEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*---------------------------------------------------------------------
* 类	名：XMLAttributes
* 功    能：描述xml属性的类
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/11	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
#include "uifactorydef.h"
namespace AutoUIFactory
{

class XMLAttributes
{
public:
	XMLAttributes(void);
	
	virtual ~XMLAttributes(void);

	void add(const String& attrName, const String& attrValue);
	
	void remove(const String& attrName);
	
	bool exists(const String& attrName) const;
	
	size_t getCount(void) const;
	
	const String& getName(size_t index) const;
	
	const String& getValue(size_t index) const;
	
	const String& getValue(const String& attrName) const;
	
	const String& getValueAsString(const String& attrName, const String& def = "") const;
	
	bool getValueAsBool(const String& attrName, bool def = false) const;
	
	
	int getValueAsInteger(const String& attrName, int def = 0) const;
	
	float getValueAsFloat(const String& attrName, float def = 0.0f) const;

	StringAlignment getValueAsAlignment(const String& attrName, StringAlignment def = StringAlignmentCenter) const;
	
protected:
	typedef std::map<String, String> AttributeMap;
	mutable AttributeMap    d_attrs;
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_XMLATTRIB_H__0AF36DA5_F4C4_4FDD_B86C_ED76F8B1DDEF__INCLUDED_)
