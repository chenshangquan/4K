// WndMsgEventManage.cpp: implementation of the CWndMsgEventManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "CallFuncManage.h"
#include "WndMsgEventManage.h"
#include "RegDefaultData.h"
#include "MfcDefaultArgs.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AutoUIFactory
{
template<> CWndMsgEventManage* Singleton<CWndMsgEventManage>::ms_pSingleton = 0;
std::map< unsigned int, String >  CWindowDefaultMsgMap::m_mapMsgs;
const String CWndMsgEventManage::strFunc = "Func";
const String CWndMsgEventManage::strScript = "Script";

CWndMsgEventManage::CWndMsgEventManage()
{
}

CWndMsgEventManage::~CWndMsgEventManage()
{
	UnRegAllEvent();
}

bool CWndMsgEventManage::TransMsg( WindowMsg* pMsg )
{
	String strMsg;
	if ( CWindowDefaultMsgMap::MsgToString( pMsg->message, strMsg ) == false )
	{
//		LOGEVENT( "CWndMsgEventManage::TransMsg 从id无法找到对应的消息 " );
		return false;
	}

	const EventSet* pFuncMap = GetFuncMap( pMsg->hwnd );
	if ( pFuncMap == 0 )
	{
//		LOGEVENT( "CWndMsgEventManage::TransMsg 没有找到对应处理函数" );
		return false;
	}
		
	Args_WindowMsg msg( *pMsg );

	EventSet::iterator itr = const_cast<EventSet*>(pFuncMap)->find( strMsg );
	if ( itr != const_cast<EventSet*>(pFuncMap)->end() )
	{
		FuncInfo funcInfo = itr->second;
	
		if ( funcInfo.first == CWndMsgEventManage::strFunc )
		{
			return CFuncManage::GetSingletonPtr()->ExeFunc( funcInfo.second, msg );		 
		}
		else if ( funcInfo.first == CWndMsgEventManage::strScript )
		{
			return IScript::GetSingletonPtr()->ExecuteScript( funcInfo.second );
		}
	}
	
	return false;
}

bool CWndMsgEventManage::RegEvent( HWND hWnd, String strEvent, String strFunc, 
								  String strType /* = CWndMsgEventManage::strFuncType */, bool bCover /* = false */ )
{
	const EventSet* pFuncMap = GetFuncMap( hWnd );
	FuncInfo funcInfo( strType, strFunc );
	if ( pFuncMap == 0 )
	{
		EventSet* pFuncMapTmp = new EventSet;
		
		pFuncMapTmp->insert( EventSet::value_type( strEvent, funcInfo ) );
		m_mapEvents.insert( EventMap::value_type( hWnd, pFuncMapTmp ) );
//		LOGEVENT( "CWndMsgEventManage::RegEvent 新增函数 类型=" + strEvent + " 名称=" + strFunc );
		return true;
	}
	
	EventSet::iterator itrFunc = const_cast<EventSet*>(pFuncMap)->find( strEvent );
	if ( itrFunc != const_cast<EventSet*>(pFuncMap)->end() )
	{
		if ( bCover == true )
		{
			itrFunc->second = funcInfo;
		}
		else
		{
			LOGEVENT( "CWndMsgEventManage::RegEvent 已经存在该事件的处理函数 事件=" + strEvent );
		}	
		return false;
	}
	const_cast<EventSet*>(pFuncMap)->insert( EventSet::value_type( strEvent, funcInfo ) );
	return true;
}

bool CWndMsgEventManage::UnRegEvent( HWND hWnd, String strEvent )
{
	const EventSet* pFuncMap = GetFuncMap( hWnd );
	if ( pFuncMap == 0 )
	{
		LOGEVENT( "CWndMsgEventManage::UnRegEvent 该窗口没有对应函数集" );
		return false;
	}
	
	EventSet::iterator itrFunc = const_cast<EventSet*>(pFuncMap)->find( strEvent );
	if ( itrFunc != const_cast<EventSet*>(pFuncMap)->end() )
	{
	
		LOGEVENT( "CWndMsgEventManage::UnRegEvent 已经移除事件" + strEvent );
		const_cast<EventSet*>(pFuncMap)->erase( itrFunc );
		return true;
	}
	return false;
}

void CWndMsgEventManage::UnRegAllEvent()
{ 
	EventMap::iterator itrEvent = m_mapEvents.begin();
	
	while( itrEvent != m_mapEvents.end())
	{  
		delete itrEvent->second;
		itrEvent->second = 0;
		m_mapEvents.erase( itrEvent );
		itrEvent = m_mapEvents.begin();
	}
 
}

const std::map<String, pair<String,String> >* CWndMsgEventManage::GetFuncMap( HWND hWnd )
{
	EventMap::iterator itr = m_mapEvents.find( hWnd );
	if ( itr == m_mapEvents.end() )
	{
		LOGEVENT( "CWndMsgEventManage::GetFuncMap 没有找到对应的函数集合" );
		return 0;
	}
	return itr->second;
}


bool CWindowDefaultMsgMap::MsgToString( unsigned int wMsg, String& str )
{
	DefaultMsgMap::iterator itr = m_mapMsgs.find( wMsg );
	if ( itr != m_mapMsgs.end() )
	{
		str = itr->second;
		return true;
	}
	return false;
}

bool CWindowDefaultMsgMap::RegMsg( unsigned int wMsg, String str )
{
	DefaultMsgMap::iterator itr = m_mapMsgs.find( wMsg );
	if ( itr == m_mapMsgs.end() )
	{
		m_mapMsgs.insert( DefaultMsgMap::value_type( wMsg, str) );
		return true;
	}
	return false;
}

}// namespace AutoUIFactory end
