// WindowTypeManage.cpp: implementation of the CWindowTypeManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "WindowTypeManage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{
const String CWindowTypeManage::strSrcType = "SrcType";
const String CWindowTypeManage::strTagType = "TagType";
const String CWindowTypeManage::strType = "WindowType";
template<> CWindowTypeManage* Singleton<CWindowTypeManage>::ms_pSingleton  = 0;
CWindowTypeManage::CWindowTypeManage()
{

}

CWindowTypeManage::~CWindowTypeManage()
{

}

String CWindowTypeManage::GetType( String& strSrcType )
{
	TypeMaps::iterator itr = m_mapTypes.find( strSrcType );
	if ( itr != m_mapTypes.end() )
	{
		return itr->second;
	}
	return strSrcType;
}

void CWindowTypeManage::Update( IArgs* pArgs )
{
	if (  Args_SystemObserver* pObser = dynamic_cast<Args_SystemObserver*>(pArgs) )
	{
		SystemInfoMultiMap::iterator itr = pObser->m_mapSystemInfos.begin();
		while ( itr != pObser->m_mapSystemInfos.end() )
		{
			if ( itr->first == CWindowTypeManage::strType )
			{
				Update( itr->second );
			}
			itr++;
		}
	}
}

void CWindowTypeManage::Update( XMLAttributes& xmlAttribs )
{
	if ( !xmlAttribs.exists( CWindowTypeManage::strSrcType ) || !xmlAttribs.exists( CWindowTypeManage::strTagType ) )
	{
		return;
	}
	String strSrcType = xmlAttribs.getValue( CWindowTypeManage::strSrcType );
	String strTagType = xmlAttribs.getValue( CWindowTypeManage::strTagType );
	m_mapTypes[strSrcType] = strTagType;
}

}