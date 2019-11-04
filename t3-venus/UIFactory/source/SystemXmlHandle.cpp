// SystemXmlHandle.cpp: implementation of the CSystemXmlHandle class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "System.h"
#include "SystemXmlHandle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

const String CSystemXmlHandle::strSystemInfo = "SystemInfo";
const String CSystemXmlHandle::strWindowInfo = "WindowInfo";
const String CSystemXmlHandle::strWindowInfoName = "Name";
const String CSystemXmlHandle::strWindowInfoValue = "Value";
const String CSystemXmlHandle::strImagePath = "ImagePath";
const String CSystemXmlHandle::strLayoutPath = "LayoutPath";
const String CSystemXmlHandle::strItemInfo = "ItemInfo";
const String CSystemXmlHandle::strResolution = "Resolution";//分辨率
CSystemXmlHandle::CSystemXmlHandle()
{

}

CSystemXmlHandle::~CSystemXmlHandle()
{

}

bool CSystemXmlHandle::ElementStart( String strElement, const XMLAttributes& xmlAttributes )
{

// 	if ( strElement == strSystemInfo )
// 	{
// 		SystemInfoStart( xmlAttributes );
// 	}
// 	else if ( strElement == strWindowInfo )
// 	{
// 		WindowInfoStart( xmlAttributes );
// 	}
// 	else
// 	{
// 		LOGEVENT( "没有找到合适的处理函数 " + strElement );
// 	}
	CSystem::GetSingletonPtr()->AddSystemInfo( strElement, xmlAttributes );
	return true;
}

bool CSystemXmlHandle::ElementEnd( String strElement )
{
	return false;
}

// bool CSystemXmlHandle::WindowInfoStart( const XMLAttributes& xmlAttributes )
// {	
// 	String strName = xmlAttributes.getValue( strWindowInfoName );
// 	String strValue = xmlAttributes.getValue( strWindowInfoValue );
// 	CSystem::GetSingletonPtr()->AddWindowXml( strName, xmlAttributes );
// 	return false;
// }
// 
// bool CSystemXmlHandle::WindowInfoEnd()
// {
// 	return false;
// }

// bool CSystemXmlHandle::SystemInfoStart( const XMLAttributes& xmlAttributes )
// {
// 	String strName = xmlAttributes.getValue( strWindowInfoName );
// 	String strValue = xmlAttributes.getValue( strWindowInfoValue );
// 
// 	if ( strName == CSystemXmlHandle::strImagePath)
// 	{		
// 		CSystem::GetSingletonPtr()->SetImagePath( strValue );
// 	}	
// 	else if ( strName == CSystemXmlHandle::strLayoutPath )
// 	{
// 		CSystem::GetSingletonPtr()->SetLayoutPath( strValue );
// 	}
// 	else if ( strName == CSystemXmlHandle::strItemInfo )
// 	{
// 		CSystem::GetSingletonPtr()->SetItemInfoPath( strValue );
// 	}
// 	
// 	return false;
// }
// 
// bool CSystemXmlHandle::SystemInfoEnd()
// {
// 	return false;
// }

} // namespace AutoUIFactory end
