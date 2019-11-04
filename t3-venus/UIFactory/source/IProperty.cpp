// IProperty.cpp: implementation of the IProperty class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "IProperty.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

bool IProperty::isDefault(const Window* src) const
{
	String strProperty;
	if ( get( src , strProperty ) )
	{
		return ( strProperty == m_strDefault);
	}
	return false;
}

/*************************************************************************
Returns the default value of the Property as a String.
*************************************************************************/
String IProperty::getDefault(const Window* src) const
{
	return m_strDefault;
}

} // namespace AutoUIFactory end
