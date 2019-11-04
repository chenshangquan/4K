// IProperty.h: interface for the IProperty class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPROPERTY_H__EE8D9631_C168_4A27_A2E1_755C2305AACA__INCLUDED_)
#define AFX_IPROPERTY_H__EE8D9631_C168_4A27_A2E1_755C2305AACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IValue.h"
namespace AutoUIFactory
{

Interface IProperty
{
public:
	IProperty( const String& name, const String& help, const String& defaultValue = "" ) :
	  m_strName(name),
	  m_strHelp(help),
	  m_strDefault(defaultValue)
	{
	}

	virtual ~IProperty(void) {}

	const String& getHelp(void) const {return m_strHelp;}

	const String& getName(void) const {return m_strName;}

	virtual bool get( const Window* src, String& value ) const { return false; }

	virtual bool get( const Window* src, IValue& value ) const { return false; }

	virtual bool set( Window* tag, const String& value ) = 0;

	virtual bool set( Window* tag, const IValue& value ) = 0;

	virtual bool isDefault( const Window* src ) const;

	virtual String	getDefault( const Window* src ) const;

protected:
	String	m_strName;		
	String	m_strHelp;		
	String	m_strDefault;	
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_IPROPERTY_H__EE8D9631_C168_4A27_A2E1_755C2305AACA__INCLUDED_)
