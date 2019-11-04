// ItemXmlHandle.cpp: implementation of the CItemXmlHandle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "ItemXmlHandle.h"
#include "ItemFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AutoUIFactory
{
const String CItemXmlHandle::strType = "Name";
const String CItemXmlHandle::strName = "Item";

CItemXmlHandle::CItemXmlHandle()
{

}

CItemXmlHandle::~CItemXmlHandle()
{

}

bool CItemXmlHandle::ElementStart( String strElement, const XMLAttributes& xmlAttributes )
{
    try 
    {
        if ( strElement == strName )
        {
            if ( xmlAttributes.exists( CItemXmlHandle::strType ) )
            {
                String strName = xmlAttributes.getValue( CItemXmlHandle::strType );
                return CItemFactory::GetSingletonPtr()->AddItemInfo( strName, xmlAttributes );
            }		
        }	
    }
    catch ( ... )
    {
        return false;	
    }
     
	
	return false;
}

bool CItemXmlHandle::ElementEnd( String strElement )
{
	return false;
}

}