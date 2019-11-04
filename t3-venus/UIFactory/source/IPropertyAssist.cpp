// IPropertyAssist.cpp: implementation of the IPropertyAssist class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "IValue.h"
#include "IPropertyAssist.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

template<> CPropertyAssist* Singleton<CPropertyAssist>::ms_pSingleton = 0;
const String CPropertyAssist::strName = "Name";
const String CPropertyAssist::strValue = "Value";
CPropertyAssist::CPropertyAssist()
{

}

CPropertyAssist::~CPropertyAssist()
{
	ClearAllProperty();
	ClearAllPropertySet();
}

bool CPropertyAssist::AddProperty( String strName, IProperty* piProperty, bool bCover /* = false */ )
{
	PropertyMap::iterator itr = m_mapProperties.find( strName );
	if ( itr != m_mapProperties.end() )
	{
		if ( bCover == true )
		{
			itr->second = piProperty;
			return true;
		}
		LOGEVENT( "IPropertyAssist::AddProperty 属性已经存在 name = " + strName );
		return false;
	}
	m_mapProperties.insert( PropertyMap::value_type( strName, piProperty ) );
	return true;
}

IProperty* CPropertyAssist::GetProperty( String strName ) 
{
	PropertyMap::iterator itr = m_mapProperties.find( strName );
	if ( itr != m_mapProperties.end() )
	{
		return itr->second;
	}
	LOGEVENT( "IPropertyAssist::GetProperty 没有属性 strName = " + strName );
	return 0;
}

bool CPropertyAssist::SetProperty( const XMLAttributes& xmlAttrib, const Window* window, const String& strWndType )
{
	String strName = xmlAttrib.getValue( CPropertyAssist::strName );
	String strValue = xmlAttrib.getValue( CPropertyAssist::strValue );
	IProperty* piProperty = GetPropertyByCommonName(strWndType, strName );
	if ( piProperty == 0 )
	{
		LOGEVENT( "CPropertyAssist::SetProperty 没有对应的属性 name= " + strName );
		return false;
	}
	piProperty->set( const_cast<Window*>(window), strValue );
	return true;
}

bool CPropertyAssist::SetProperty( const IValue& value, const Window* window, const String& strWndType )
{
	IProperty* piProperty = GetPropertyByCommonName(strWndType, value.GetType() );
	
	if ( piProperty == 0 )
	{
		LOGEVENT( "CPropertyAssist::SetProperty 没有对应的属性 name= " + strName );
		return false;
	}
	piProperty->set( const_cast<Window*>(window), value );

	return true;
}

bool CPropertyAssist::GetValue( IValue& value, const Window* window, const String& strWndType )
{
	IProperty* piProperty = GetPropertyByCommonName( strWndType, value.GetType() );
	if ( piProperty == 0 )
	{
		LOGEVENT( "CPropertyAssist::SetProperty 没有对应的属性 name= " + strName );
		return false;
	}
	return piProperty->get( window, value );
}


void CPropertyAssist::ClearAllProperty()
{
	PropertyMap::iterator itr = m_mapProperties.begin();
	while( itr != m_mapProperties.end() )
	{
		delete itr->second ;
		itr->second = 0;
		m_mapProperties.erase( itr );
		itr = m_mapProperties.begin();
	}
}
void CPropertyAssist::ClearAllPropertySet()
{
	PropertySetMap::iterator itr = m_mapPropertySets.begin();
	while( itr != m_mapPropertySets.end() )
	{
		delete itr->second ;
		itr->second = 0;
		m_mapPropertySets.erase( itr );
		itr = m_mapPropertySets.begin();
	}
}

bool CPropertyAssist::AddPropertySet( String strName, IPropertySet* piPropertySet, bool bCover /* = false */ )
{
	PropertySetMap::iterator itr = m_mapPropertySets.find( strName );
	if ( itr != m_mapPropertySets.end() )
	{
		if ( bCover == true )
		{
			itr->second = piPropertySet;
			return true;
		}	
		LOGEVENT( "CPropertyAssist::AddPropertySet 已经存在属性集 name=" + strName );				
		return false;
	}
	m_mapPropertySets.insert( PropertySetMap::value_type( strName, piPropertySet ) );
//	LOGEVENT( "CPropertyAssist::AddPropertySet 添加属性集成功 name=" + strName );
	return true;
}

IPropertySet* CPropertyAssist::GetPropertySet( String strName )
{
	PropertySetMap::iterator itr = m_mapPropertySets.find( strName );
	if ( itr != m_mapPropertySets.end() )
	{
		return itr->second;
	}

	LOGEVENT( "CPropertyAssist::GetPropertySet 没有找到以下属性集 name=" + strName );
	return 0;
}

IProperty* CPropertyAssist::GetPropertyByCommonName( String strWndType, String strName )
{
	IPropertySet* piPropertySet = GetPropertySet( strWndType );
	if ( piPropertySet == 0 )
	{
		return 0;
	}
	
	String strPropertyName;
	if ( piPropertySet->GetProperty( strName, strPropertyName ) == false )
	{
		return 0;
	}
	return GetProperty( strPropertyName );
}

bool CPropertyAssist::AddPropertyToSet( String strWndType, String strProperty, String strValue )
{
    IPropertySet* piPropertySet = GetPropertySet( strWndType );
    if ( piPropertySet == 0 )
    {
        return false;
	}

    return piPropertySet->AddProperty( strProperty, strValue );
}


} // namespace AutoUIFactory end
