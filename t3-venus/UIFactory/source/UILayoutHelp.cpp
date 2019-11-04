// UILayoutHelp.cpp: implementation of the CUILayoutHelp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "UILayoutHelp.h"
// #include "WindowManage.h"
#include "WndTreeHelp.h"
// #include "XmlAttrib.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

	const String CUILayoutHelp::strLeft = "Left";
	const String CUILayoutHelp::strRight = "Right";
	const String CUILayoutHelp::strTop = "Top";
	const String CUILayoutHelp::strBottom = "Bottom";
	const String CUILayoutHelp::strCenter = "center";
	const char CUILayoutHelp::chPartitionChar = '|';
CUILayoutHelp::CUILayoutHelp()
{

}

CUILayoutHelp::~CUILayoutHelp()
{

}

bool CUILayoutHelp::LayoutUI( const IWndTree* pWndTree, bool bRecurrence /* = true */ )
{
	if ( pWndTree == 0 )
	{
		return false;
	}

	for ( int nIndex = 0; nIndex < const_cast<IWndTree*>(pWndTree)->GetItemCount(); nIndex++ )
	{
		IWndTree* pSub = const_cast<IWndTree*>(pWndTree)->GetItemByIndex( nIndex );
		if ( pSub != 0 )
		{
			WndInfo* pInfo = pSub->GetItemData();
			if ( pInfo != 0 )
			{
				Layout( pInfo );
			}
			if ( bRecurrence  = true )
			{
				LayoutUI( pSub, bRecurrence );
			}
		}
		
	}
	return true;
}

bool CUILayoutHelp::LayoutUI( const Window* pWnd, bool bRecurrence /* = true */ )
{
	return false;
}

bool CUILayoutHelp::LayoutUI( const String& strWndName, bool bRecurrence /* = true */ )
{
 	const IWndTree* pTree = CWndTreeHelp::GetWindow( strWndName, CWindowManage::GetSingletonPtr()->GetRoot() );
	if ( pTree == 0 )
	{
		return false;
	}
	return LayoutUI( pTree, bRecurrence );
}

bool CUILayoutHelp::Layout( WndInfo* pInfo )
{
/*	if ( pInfo == 0 || pInfo->xmlAttribs.getCount() == 0 )
	{
		return false;
	}
	bool bLeft = false;
	bool bRight = false;
	bool bTop = false;
	bool bBottom = false;
	
	int nLeft = 0;
	int nRight = 0;
	int nTop = 0;
	int nBottom = 0;
	if ( pInfo->xmlAttribs.exists( CUILayoutHelp::strLeft ) )
	{
		bLeft = true;
		nLeft = pInfo->xmlAttribs.getValueAsInteger( CUILayoutHelp::strLeft );
	}
	if ( pInfo->xmlAttribs.exists( CUILayoutHelp::strRight ) )
	{
		bRight = true;
		nRight = pInfo->xmlAttribs.getValueAsInteger( CUILayoutHelp::strRight );
	}
	if ( pInfo->xmlAttribs.exists( CUILayoutHelp::strTop ) )
	{
		bTop = true;
		nTop = pInfo->xmlAttribs.getValueAsInteger( CUILayoutHelp::strTop );
	}
	if ( pInfo->xmlAttribs.exists( CUILayoutHelp::strBottom ) )
	{
		bBottom = true;
		nBottom = pInfo->xmlAttribs.getValueAsInteger( CUILayoutHelp::strBottom );
	}

	CWnd* pTag = pInfo->pWnd;
	if ( pTag == 0 )
	{
		return false;
	}
	CWnd* pParent = pTag->GetParent();
	if ( pParent == 0 )
	{
		pParent = pTag;
	}
	

	CRect rcWnd;
	pTag->GetWindowRect( &rcWnd );
	CRect rcTemp = rcWnd;
	pParent->ScreenToClient( &rcWnd );
	int xLeft = rcWnd.left;
	int yTop = rcWnd.top;
	int nWidth = rcWnd.Width();
	int nHeight = rcWnd.Height();
	
	CRect rcParent;
	pParent->GetWindowRect( rcParent );

	if ( bLeft && bTop && bRight && bBottom )
	{
		nWidth = rcParent.Width() - nLeft - nRight;
		nHeight = rcParent.Height() - nTop - nBottom;
		xLeft = rcParent.left + nLeft;
		yTop = rcParent.top + nTop;	
	}
	else if ( bLeft && bTop && bRight )
	{
		nWidth = rcParent.Width() - nLeft - nRight;
		xLeft = rcParent.left + nLeft;
		yTop = rcParent.top + nTop;
	}
	else if ( bLeft && bBottom && bRight )
	{
		nWidth = rcParent.Width() - nLeft - nRight;
		xLeft = rcParent.left + nLeft;
		yTop = rcParent.top + rcParent.Height() - nHeight - nBottom;
	}
	else if ( bTop && bBottom && bLeft )
	{
		nHeight = rcParent.Height() - nTop - nBottom;
		xLeft = rcParent.left + nLeft;
		yTop = rcParent.top + nTop;
	}
	else if ( bTop && bBottom && bRight )
	{
		nHeight = rcParent.Height() - nTop - nBottom;
		xLeft = rcParent.left + rcParent.Width() - nWidth - nRight;
		yTop = rcParent.top + nTop;
	}
	else if ( bBottom && bRight )
	{
		xLeft = rcParent.left + rcParent.Width() - nWidth - nRight;
		yTop = rcParent.top + rcParent.Height() - nHeight - nBottom;
	}
	else if ( bRight && bTop )
	{
		xLeft = rcParent.left + rcParent.Width() - nWidth - nRight;
		yTop = rcParent.top + nTop;
	}
	else if ( bLeft && bBottom )
	{
		xLeft = rcParent.left + nLeft;
		yTop = rcParent.top + rcParent.Height() - nHeight - nBottom;
	}
	else if ( bLeft && bTop  )
	{	
		xLeft = rcParent.left + nLeft;
		yTop = rcParent.top + nTop;
	}
	else if ( bBottom && bTop )
	{
		xLeft = rcTemp.left;
		yTop = rcParent.top + nTop;
		nHeight = rcParent.Height() - nTop - nBottom;
	}
	else if ( bLeft && bRight )
	{
		xLeft = rcParent.left + nLeft;
		yTop = rcTemp.top;
		nWidth = rcParent.Width() - nLeft - nRight;
	}
	else if ( bLeft )
	{
		xLeft = rcParent.left + nLeft;
		yTop = rcTemp.top;
	}
	else if ( bRight )
	{
		xLeft = rcParent.left + rcParent.Width() - nWidth - nRight;
		yTop = rcTemp.top;
	}
	else if ( bTop )
	{
		xLeft = rcTemp.left;
		yTop = rcParent.top + nTop;
	}
	else if ( bBottom )
	{
		xLeft = rcTemp.left;
		yTop = rcParent.top + rcParent.Height() - nHeight - nBottom;
	}
	else
	{
		return false;
	}
	rcWnd = CRect( xLeft, yTop, xLeft+nWidth,yTop+nHeight );

	DWORD dwStyle   =   GetWindowLong( pTag->m_hWnd,GWL_STYLE );

	if ( dwStyle & WS_CHILD ) 
	{
		pParent->ScreenToClient( rcWnd );
	}
	pTag->MoveWindow(  rcWnd, TRUE );*/
	return true;
}

}	// namespace AutoUIFactory end