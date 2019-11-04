#include "StdAfx.h"
#include "logicManager.h"




namespace DuiLib {
LOGICMAP CLogicManager::m_logicMap;
 

BOOL CLogicManager::RegLogic( INotifyUI* pLogic, LPCTSTR szLogicName )
{
	LOGICMAP::iterator it = m_logicMap.find( szLogicName );
	if( it == m_logicMap.end() )
	{
		m_logicMap.insert( LOGICMAP::value_type(szLogicName,pLogic) );
		return TRUE;
	}
	
	return FALSE;
}

INotifyUI* CLogicManager::FindLogicByName( LPCTSTR szLogicName )
{
	LOGICMAP::iterator it = m_logicMap.find( szLogicName );
	if( it != m_logicMap.end() )
	{
		return it->second;
	}

	return NULL;
}





 


}