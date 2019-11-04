// UILoadManage.cpp: implementation of the CUILoadManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "UILoadManage.h"
#include "SystemInfoManage.h"
#include "WindowManage.h"
#include "WndTreeHelp.h"
#include "LayoutXmlHandle.h"
#include "IXmlParser.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{
const String CUILoadManage::strName = "Name";	
const String CUILoadManage::strValue = "Value";
const String CUILoadManage::strType = "WindowInfo";
template<> CUILoadManage* Singleton<CUILoadManage>::ms_pSingleton  = 0;
CUILoadManage::CUILoadManage()
{

}

CUILoadManage::~CUILoadManage()
{

}

bool CUILoadManage::ReadLayoutXml( String strName )
{  
     
	XMLAttributes attrib;
	bool bFind = GetWindowXml( strName, attrib );
	if ( bFind == false )
	{
		LOGEVENT( "[CUILoadManage::ReadLayoutXml]窗口xml信息不全 strName= " + strName );
		return false;
	}
	String strParent = attrib.getValue( CSystem::strWndParent );
	
	const IWndTree* pWndTree = CWndTreeHelp::GetWindow( strParent, CWindowManage::GetSingletonPtr()->GetRoot() );
	if ( pWndTree == 0 )
	{
		pWndTree = CWindowManage::GetSingletonPtr()->GetRoot();
	}
	
	CLayoutHandle iHandle;
	String strXmlPath = attrib.getValue( CSystem::strValue );
	
	String strTemp = CSystemInfoManage::GetSingletonPtr()->GetLayoutPath() + strXmlPath;
	
	iHandle.SetCurWndTree( const_cast<IWndTree*>(pWndTree) );
	return IXmlParser::GetSingletonPtr()->ParserXml( &iHandle, strTemp );
}

bool CUILoadManage::GetWindowXml( String strName, XMLAttributes& attrib )
{
	WindowAttribMap::iterator itr = m_mapWindowAttribs.find( strName );
	if ( itr == m_mapWindowAttribs.end() )
	{
		LOGEVENT( "没有找到该窗口" + strName );
		return false;
    } 
     
	attrib = itr->second;
	return true;
}


//2011-11-16 by yjj
String CUILoadManage::GetWindowXml( String strName )  
{   
    String strFileName = "";
    
    XMLAttributes attrib;
    bool re = GetWindowXml(  strName, attrib );
    if ( re )
    {
        strFileName = attrib.getValue( CSystem::strValue );
        strFileName = CSystemInfoManage::GetSingletonPtr()->GetLayoutPath() + strFileName;
        return strFileName;
    }

    return "";
}



bool CUILoadManage::AddWindowXml( String strName,const XMLAttributes& attrib )
{
	m_mapWindowAttribs[strName] = attrib;
     
	return true;
}

void CUILoadManage::Update( IArgs* pArgs )
{
	if (  Args_SystemObserver* pObser = dynamic_cast<Args_SystemObserver*>(pArgs) )
	{
		SystemInfoMultiMap::iterator itr = pObser->m_mapSystemInfos.begin();
		while ( itr != pObser->m_mapSystemInfos.end() )
		{
			if ( itr->first == CUILoadManage::strType )
			{
				Update( itr->second );
			}
			itr++;
		}
	}
}

void CUILoadManage::Update( XMLAttributes& xmlAttribs )
{
	if ( !xmlAttribs.exists( CUILoadManage::strName ) || !xmlAttribs.exists( CUILoadManage::strValue) )
    {   
        LOGEVENT("[CUILoadManage::Update] 返回： 不存在   " + CUILoadManage::strName + "或者不存在" + CUILoadManage::strValue  );
		return;
	}
	String strName = xmlAttribs.getValue( CUILoadManage::strName );
 	String strValue = xmlAttribs.getValue( CUILoadManage::strValue );
 	AddWindowXml( strName, xmlAttribs );
}

}