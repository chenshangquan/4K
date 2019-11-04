// LayoutTag.cpp: implementation of the LayoutTag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "LayoutTag.h"
#include "LayoutXmlHandle.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{
CLayoutTag::CLayoutTag() : IXmlTag()
{

}

CLayoutTag::~CLayoutTag()
{

}

bool CLayoutTag::ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext /* = 0 */ )
{
	CLayoutHandle* pHandle = (CLayoutHandle*)pContext;
	const IWndTree* pWndTree = pHandle->GetCurWindowTree();
	if ( pWndTree == 0 )
	{
		return false;
	}
	WndInfo* pInfo = const_cast<IWndTree*>(pWndTree)->GetItemData();
	if ( pInfo == 0 )
	{
		return false;
	}
	return true;
}

bool CLayoutTag::ElementEnd( String strElement, void* pContext /* = 0 */ )
{
	return false;
}

}