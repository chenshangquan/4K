// System.cpp: implementation of the CSystem class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "System.h"
#include "IXmlParser.h"
#include "DefaultXmlParser.h"
#include "IScript.h"
#include "SystemXmlHandle.h"
#include "LayoutXmlHandle.h"
#include "WindowManage.h"
#include "WindowFacotryManage.h"
#include "IPropertyAssist.h"
#include "DefaultLogger.h"
#include "DefaultScript.h"
#include "WndMsgEventManage.h"
#include "CallFuncManage.h"
#include "RegDefaultData.h"
#include "WndTreeHelp.h"
#include "ItemFactory.h"
#include "ItemXmlHandle.h"

#include "SystemInfoManage.h"
#include "UILoadManage.h"
#include "WindowTypeManage.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{
template<> CSystem* Singleton<CSystem>::ms_pSingleton  = 0;
const String CSystem::strName = "Name";
const String CSystem::strValue = "Value";
const String CSystem::strWndParent = "Parent";
CSystem::CSystem( String strMainXml /* =  */,
				 IScript* piScript /* = 0 */, 
				 IXmlParser* pXmlParser /* = 0 */ ) : m_strMainXml( strMainXml )
{  
 
	// 创建log
	if ( ILogger::GetSingletonPtr() == 0 )
	{
		new CDefaultLogger();
	}
	// 创建xml解析类
	if ( IXmlParser::GetSingletonPtr() == 0 )
	{
		new DefaultXmlParser();
	}

	// 创建脚本模块
	if ( IScript::GetSingletonPtr() == 0 )
	{
		new CDefaultScript();
	}
	
	if ( CWindowFacotryManage::GetSingletonPtr() == 0 )
	{
		new CWindowFacotryManage();
	}
	
	if ( CWindowManage::GetSingletonPtr() == 0 )
	{
		new CWindowManage();
	}

	if ( CWndMsgEventManage::GetSingletonPtr() == 0 )
	{
		new CWndMsgEventManage();
	}

	if ( CPropertyAssist::GetSingletonPtr() == 0 )
	{
		new CPropertyAssist();
	}

	if ( CFuncManage::GetSingletonPtr() == 0 )
	{
		new CFuncManage();
	}

	// 注册所有默认的数据信息
	CRegDefaultData::RegAllDefaultData();
	// 读取主配置文件

// 	// 开始创建UI
 	if ( CItemFactory::GetSingletonPtr() == 0 )
 	{
 		new CItemFactory();
 	}
// 	if ( m_strItemInfo != "" )
// 	{
// 		CItemXmlHandle iHandle;
// 		m_pXmlParser->ParserXml( &iHandle, m_strItemInfo );
// 	}
	if ( CSystemInfoManage::GetSingletonPtr() == 0 )
	{
		new CSystemInfoManage();
	}
	AddObserver( CSystemInfoManage::GetSingletonPtr() );
	if ( CUILoadManage::GetSingletonPtr() == 0 )
	{
		new CUILoadManage();
	}
	AddObserver( CUILoadManage::GetSingletonPtr() );
	if ( CWindowTypeManage::GetSingletonPtr() == 0 )
	{
		new CWindowTypeManage();
	}
	AddObserver( CWindowTypeManage::GetSingletonPtr() );
}

CSystem::~CSystem()
{
	 //销毁构造时创建的资源  2012.11.30 yjj
	ILogger::RemoveInstance() ; 
	 
	IXmlParser::RemoveInstance() ; 
 
	IScript::RemoveInstance() ;  

	CWindowFacotryManage::RemoveInstance() ; 

	CWindowManage::RemoveInstance() ; 

	CWndMsgEventManage::RemoveInstance() ;  

	CPropertyAssist::RemoveInstance() ;  

	CFuncManage::RemoveInstance() ;  


	 
	CItemFactory::RemoveInstance() ;  

	CSystemInfoManage::RemoveInstance() ;  


	CUILoadManage::RemoveInstance() ;  

	CWindowTypeManage::RemoveInstance() ;  
 
}

void CSystem::Launch()
{  
    
	if ( m_strMainXml != "" )
    {  
		ReadMainXml( m_strMainXml );
    } 
   
	Update();
	String strItemPath = CSystemInfoManage::GetSingletonPtr()->GetItemInfoPath();
     
	if (  !strItemPath.empty() )// 名称为空就不解析，防止崩溃 2012.11.30 by yjj
	{
		CItemXmlHandle xmlHandle;
		IXmlParser::GetSingletonPtr()->ParserXml( &xmlHandle, strItemPath );
	}

}

void CSystem::Update()
{
	ObserverVec::iterator itr = m_vecObservers.begin();
	Args_SystemObserver args( m_mapSystemInfos );
	while ( itr != m_vecObservers.end() )
	{	
		IObserver* piObserver = *itr;
		if ( piObserver != 0 )
		{
			piObserver->Update( &args );
		}
		itr++;
	}
}

void CSystem::AddObserver( IObserver* piObserver )
{
	m_vecObservers.push_back( piObserver );
}

bool CSystem::ReadMainXml( String strMainXml )
{
//	m_strMainXml = strMainXml;
#ifndef _DEBUG
    CSystemInfoManage::GetSingletonPtr()->MakeFullPath( strMainXml );

#endif
    
    CSystemXmlHandle iHandle;
	return IXmlParser::GetSingletonPtr()->ParserXml( &iHandle, strMainXml );
}

bool CSystem::AddSystemInfo( String strElement, const XMLAttributes& attrib )
{
	m_mapSystemInfos.insert( make_pair( strElement, attrib ) );
	return true;
}


void CSystem::SetImagePath( String strPath )
{
	CSystemInfoManage::GetSingletonPtr()->SetImagePath( strPath );
}

String CSystem::GetImagePath()
{
	return CSystemInfoManage::GetSingletonPtr()->GetImagePath();
}

void CSystem::SetLayoutPath( String strPath )
{
	CSystemInfoManage::GetSingletonPtr()->GetLayoutPath();
}

String CSystem::GetLayoutPath()
{
	return CSystemInfoManage::GetSingletonPtr()->GetLayoutPath();
}

void CSystem::SetItemInfoPath( String strPath )
{
	CSystemInfoManage::GetSingletonPtr()->SetItemInfoPath( strPath );
}

String CSystem::GetItemInfoPath()
{
	return CSystemInfoManage::GetSingletonPtr()->GetItemInfoPath();
}

TFontInfo CSystem::GetEditFontInfo()
{
    return CSystemInfoManage::GetSingletonPtr()->GetEditFontInfo();
}

TFontInfo CSystem::GetStaticFontInfo()
{
    return CSystemInfoManage::GetSingletonPtr()->GetStaticFontInfo();
}

bool CSystem::ReadLayoutXml( String strLayout )
{
	return CUILoadManage::GetSingletonPtr()->ReadLayoutXml( strLayout );
}

bool CSystem::GetWindowXml( String strName, XMLAttributes& attrib )
{
	return CUILoadManage::GetSingletonPtr()->GetWindowXml( strName, attrib );
}
	
bool CSystem::AddWindowXml( String strName, const XMLAttributes& attrib )
{   
	return CUILoadManage::GetSingletonPtr()->AddWindowXml( strName, attrib );
}


String  CSystem::GetWindowXml( String strName  )
{
    return CUILoadManage::GetSingletonPtr()->GetWindowXml( strName );
}

} // namespace AutoUIFactory end

