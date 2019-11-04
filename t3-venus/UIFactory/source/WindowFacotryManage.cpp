// WindowFacotryManage.cpp: implementation of the CWindowFacotryManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "WindowFacotryManage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AutoUIFactory
{
template<> CWindowFacotryManage* Singleton<CWindowFacotryManage>::ms_pSingleton  = 0;
CWindowFacotryManage::CWindowFacotryManage()
{

}

CWindowFacotryManage::~CWindowFacotryManage()
{
	ClearFactory();
}

bool CWindowFacotryManage::AddFactory( String strType, IWindowFactory* pWindowFactory, bool bCover /* = false */ )
{
	FactoryMap::iterator itr = m_mapFactories.find( strType );
	if ( itr != m_mapFactories.end() )
	{
		if ( bCover == true )
		{
			itr->second = pWindowFactory;
			return true;
		}
		LOGEVENT( "CWindowFacotryManage::AddFactory 添加工厂失败，已经存在该工厂\n")
		return false;
	}
	m_mapFactories.insert( FactoryMap::value_type( strType, pWindowFactory ) );
	return true;
}

const IWindowFactory* CWindowFacotryManage::GetFactory( String strType )
{
	FactoryMap::iterator itr = m_mapFactories.find( strType );
	if ( itr != m_mapFactories.end() )
	{
		return itr->second;
	}
	LOGEVENT( "CWindowFacotryManage::GetFactory 没有找到工厂 = " + strType );
	return 0;
}


void CWindowFacotryManage::ClearFactory( )
{
	FactoryMap::iterator itr = m_mapFactories.begin();
	if ( itr != m_mapFactories.end() )
	{
	    delete itr->second;
		itr->second  = 0;
		m_mapFactories.erase( itr );

	}	
}

} // namespace AutoUIFactory end
