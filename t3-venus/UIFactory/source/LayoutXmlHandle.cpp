// LayoutXmlHandle.cpp: implementation of the CLayoutXmlHandle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "LayoutXmlHandle.h"
#include "WindowTag.h"
#include "EventTag.h"
#include "PropertyTag.h"
#include "CallBackFuncTag.h"
#include "LayoutTag.h"
#include "SchemeTag.h"
#include "WindowTypeManage.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AutoUIFactory
{
	
const String CLayoutHandle::strCreateWindow = "Window";
const String CLayoutHandle::strProperty = "Property";
const String CLayoutHandle::strEvent = "Event";
const String CLayoutHandle::strCallBackFunc = "CallBackFunc";
const String CLayoutHandle::strLayout = "Layout";
const String CLayoutHandle::strScheme = "Scheme";
CLayoutHandle::CLayoutHandle() : m_bInScheme( false )
{
	m_pCurWindow = 0;
	IniDefaultTags();
}

CLayoutHandle::~CLayoutHandle()
{
	ClearTags();
}

bool CLayoutHandle::ElementStart( String strElement, const XMLAttributes& xmlAttributes )
{
	if ( m_bInScheme == false )
	{
		TagMap::iterator itr = m_mapTags.find( strElement );
		if ( itr != m_mapTags.end() )
		{
			(IXmlTag*)(itr->second)->ElementStart( strElement, xmlAttributes, this );
		}
		else
		{
			LOGEVENT( "没有找到处理函数 element=" + strElement );
			return false;
		}
	}
	

	if ( strElement != CLayoutHandle::strCreateWindow )
	{
		const IWndTree* pWndTree = GetCurWindowTree();
		if ( pWndTree == 0 )
		{
			return false;
		}
		WndInfo* pInfo = const_cast<IWndTree*>(pWndTree)->GetItemData();
		if ( pInfo == 0 )
		{
			return false;
		}
		pInfo->AddAttribs( strElement, xmlAttributes );
	}
	return true;
}

bool CLayoutHandle::ElementEnd( String strElement )
{
	if ( m_bInScheme == false || strElement == CLayoutHandle::strScheme)
	{
		TagMap::iterator itr = m_mapTags.find( strElement );
		if ( itr != m_mapTags.end() )
		{
			(IXmlTag*)(itr->second)->ElementEnd( strElement, this );
		}
		else
		{
			LOGEVENT( "没有找到处理函数 element=" + strElement );
			return false;
		}
		return false;
	}
	else
	{
		return true;
	}
}

bool CLayoutHandle::IniDefaultTags()
{
	AddXmlTag( strCreateWindow, new CWindowTag() );
	AddXmlTag( strProperty, new CPropertyTag() );
	AddXmlTag( strEvent, new CEventTag() );
	AddXmlTag( strCallBackFunc, new CCallBackFuncTag() );
	AddXmlTag( strLayout, new CLayoutTag() );
	AddXmlTag( strScheme, new CSchemeTag() );
	return true;
}

bool CLayoutHandle::AddXmlTag( String strElement, IXmlTag* pXmlTag )
{
	TagMap::iterator itr = m_mapTags.find( strElement );
	if ( itr == m_mapTags.end() )
	{
		m_mapTags.insert( TagMap::value_type( strElement, pXmlTag ) );
	}
	else
	{
		LOGEVENT( "CLayoutHandle::AddXmlTag 已经存在相关处理函数 element=" + strElement );
		return false;
	}
	return false;
}

bool CLayoutHandle::AppendWindow( Window* pWnd, String strName, XMLAttributes xmlAttribs )
{
	AppendWindowInTree( pWnd, strName, xmlAttribs );
	m_stackWnd.push_back( pWnd );
	m_pCurWindow = pWnd;
	return true;
}

bool CLayoutHandle::PopWindow()
{
	PopWindowFromTree();

	if ( m_stackWnd.empty() )
	{
		return false;
	}
	m_stackWnd.pop_back();
	if ( m_stackWnd.empty() )
	{
		m_pCurWindow = 0;
		return true;
	}
	m_pCurWindow = m_stackWnd[ m_stackWnd.size() - 1 ];

	return true;
}

const Window* CLayoutHandle::GetCurWindow()
{
	return m_pCurWindow;
}

const IWndTree* CLayoutHandle::GetCurWindowTree()
{
	return m_pCurWndTree;
}

bool CLayoutHandle::AppendWindowInTree( Window* pWnd, String strName, XMLAttributes xmlAttribs )
{
	IWndTree* pWndTree = new CItemGroup<WndInfo,String>();
	String strType = xmlAttribs.getValue( CWindowTag::strType );
	strType = CWindowTypeManage::GetSingletonPtr()->GetType( strType );

	WndInfo tWndInfo;
	tWndInfo.strType = strType;
	tWndInfo.pWnd = pWnd;

	tWndInfo.AddScheme( WndInfo::strDefaultScheme, xmlAttribs );
	pWndTree->SetItemData( &tWndInfo );
	if ( m_pCurWndTree->AddItem( strName, pWndTree ) )
	{	
		m_pCurWndTree = m_pCurWndTree->GetItemByKey( strName );
		m_stackWndTree.push_back( m_pCurWndTree );
		delete pWndTree;
		pWndTree = 0;
		LOGEVENT( "CLayoutHandle::AppendWindowInTree 成功添加节点 name = " + strName )
		return true;
	}	
	else
	{
		LOGEVENT( "CLayoutHandle::AppendWindowInTree 有相同名字的节点存在 name = " + strName )
	}
	delete pWndTree;
	pWndTree = 0;
	return false;
}

bool CLayoutHandle::PopWindowFromTree()
{
	if ( m_stackWndTree.empty() )
	{
		return false;
	}
	m_stackWndTree.pop_back();
	if ( m_stackWndTree.empty() )
	{
		m_pCurWndTree = 0;
		return true;
	}
	m_pCurWndTree = m_stackWndTree[ m_stackWndTree.size() - 1 ];
	return true;
}

void CLayoutHandle::SetCurWndTree( IWndTree* pWndTree )
{
	
	m_stackWndTree.push_back( pWndTree );
	m_pCurWndTree = pWndTree;
	WndInfo* pWndInfo = pWndTree->GetItemData();
	if ( pWndInfo != 0 )
	{
		SetCurWnd( pWndInfo->pWnd );
	}	
}


void CLayoutHandle::ClearTags()
{
	TagMap::iterator itr =	m_mapTags.begin();
	while ( itr != m_mapTags.end() )
	{
		delete itr->second;
		itr->second = 0;
		m_mapTags.erase( itr );
		itr = m_mapTags.begin();
	}
}
} // namespace AutoUIFactory end
