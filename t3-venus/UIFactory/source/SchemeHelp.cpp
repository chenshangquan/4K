// SchemeHelp.cpp: implementation of the CSchemeHelp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "SchemeHelp.h"
#include "LayoutXmlHandle.h"
#include "IPropertyAssist.h"
#include "EventTag.h"
#include "WndMsgEventManage.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AutoUIFactory
{

CSchemeHelp::CSchemeHelp() 
{

}

CSchemeHelp::~CSchemeHelp()
{

}

bool CSchemeHelp::LoadScheme( String strName, IWndTree* pWndTree )
{
	if ( pWndTree == 0 )
	{
		return false;
	}
	WndInfo* pInfo = pWndTree->GetItemData();
	if ( pInfo == 0 )
	{
		return false;
	}
	SchemeMap* pScheme = pInfo->GetSchemeMap( strName );
	if ( pScheme != 0 )
	{
		int nCounts = pScheme->GetItemCount();
		for ( int i = 0; i < nCounts; i++ )
		{
			SchemeMap* pSub = pScheme->GetItemByIndex( i );
			if ( pSub != 0 )
			{
				CTagInfo* pTagInfo = pSub->GetItemData();
				ResetWindow( pTagInfo, pInfo );
			}
		}
		pInfo->SetCurUseScheme( strName );
	}
	
	int nCounts = pWndTree->GetItemCount();
	for ( int i = 0; i < nCounts; i++ )
	{
		IWndTree* pSub = pWndTree->GetItemByIndex( i );
		if ( pSub != 0 )
		{
			CSchemeHelp::LoadScheme( strName, pSub );
		}
	}

	return true;
}

bool CSchemeHelp::ResetWindow( CTagInfo* pTagInfo, WndInfo* pInfo )
{
	if ( pInfo == 0 )
	{
		return 0;
	}
	if ( pTagInfo->m_strTag == CLayoutHandle::strProperty )
	{
		return CSchemeHelp::ResetWindowProperty( pTagInfo->m_xmlAttribs, pInfo );
	}
	else if ( pTagInfo->m_strTag == CLayoutHandle::strEvent )
	{
		return CSchemeHelp::ResetWindowEvent( pTagInfo->m_xmlAttribs, pInfo );
	}
	else if ( pTagInfo->m_strTag == CLayoutHandle::strCallBackFunc )
	{
		return CSchemeHelp::ResetWindowCallBackFunc( pTagInfo->m_xmlAttribs, pInfo );
	}
	else if ( pTagInfo->m_strTag == CLayoutHandle::strLayout )
	{
		return CSchemeHelp::ResetWindowLayout( pTagInfo->m_xmlAttribs, pInfo );
	}
	return false;
}

bool CSchemeHelp::ResetWindowCallBackFunc( XMLAttributes& xmlAttribs, WndInfo* pInfo )
{
	return false;
}

bool CSchemeHelp::ResetWindowEvent( XMLAttributes& xmlAttribs, WndInfo* pInfo )
{  
    if( pInfo->pWnd != NULL )
    {
		String strFuncType = CWndMsgEventManage::strFunc;
		String strEventID = "";
		String strFunc = "";
		if ( xmlAttribs.exists( CEventTag::strFunc ) && xmlAttribs.exists( CEventTag::strEventID ) )
		{
			strEventID = xmlAttribs.getValue( CEventTag::strEventID );
			strFunc = xmlAttribs.getValue( CEventTag::strFunc );
		}
		
        CWndMsgEventManage::GetSingletonPtr()->RegEvent( pInfo->pWnd->GetSafeHwnd(), strEventID, strFunc, strFuncType, true );
        return true;
	 } 
	return false;
}

bool CSchemeHelp::ResetWindowLayout( XMLAttributes& xmlAttribs, WndInfo* pInfo )
{
	return false;
}

bool CSchemeHelp::ResetWindowProperty( XMLAttributes& xmlAttribs, WndInfo* pInfo )
{
	CPropertyAssist::GetSingletonPtr()->SetProperty( xmlAttribs, pInfo->pWnd, pInfo->strType );
	return false;
}
} // namespace AutoUIFactory end