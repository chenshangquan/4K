// WndTreeHelp.cpp: implementation of the CWndTreeHelp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "WndTreeHelp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

const char CWndTreeHelp::chPartitionChar = '/';
CWndTreeHelp::CWndTreeHelp()
{

}

CWndTreeHelp::~CWndTreeHelp()
{

}

const IWndTree* CWndTreeHelp::GetWindow( String strName, const IWndTree* pWndTree )
{
	return GetWindowByPartitionString( strName, pWndTree );
}

const IWndTree* CWndTreeHelp::GetWindow( Window* pWnd, const IWndTree* pWndTree )
{
	if ( pWndTree == 0 )
	{
		LOGEVENT( "CWndTreeHelp::GetWindow 传入的控件树非法" );
		return 0;
	}
	for ( int i = 0; i < const_cast<IWndTree*>(pWndTree)->GetItemCount(); i++ )
	{
		IWndTree* pTree = const_cast<IWndTree*>(pWndTree)->GetItemByIndex( i );
		WndInfo* pWndInfo = pTree->GetItemData();
		if ( pWndInfo != 0 && pWndInfo->pWnd == pWnd )
		{
			return pTree;
		}
		const IWndTree* piSub = GetWindow( pWnd, pTree );
		if ( piSub != 0 )
		{
			return piSub;
		}
	}
	return 0;
}

const IWndTree* CWndTreeHelp::GetWindowByPartitionString( const String& strName, const IWndTree* pWndTree )
{
	if ( pWndTree == 0 )
	{
		LOGEVENT( "CWndTreeHelp::GetWindow 传入的控件树非法" );
		return 0;
	}
	
	IWndTree* piSub = const_cast<IWndTree*>(pWndTree);
	stringstream ss( strName );
	string sub_str;
	IWndTree* pResult = 0;
	while( getline( ss, sub_str, CWndTreeHelp::chPartitionChar ) )         
	{
		bool bFind = false;
		for ( int i = 0; i < piSub->GetItemCount(); i++ )
		{
			IWndTree* pTree = piSub->GetItemByIndex( i );
			if ( pTree != 0 )
			{
				String strKey = pTree->GetItemName();
				if ( strKey == sub_str )
				{
					piSub = pTree;
					pResult = piSub;
					bFind = true;
					break;
				}
			}		
		} 
		if ( bFind == false )
		{
			pResult = 0;
		}
	}
	return pResult;
}

} // namespace AutoUIFactory end