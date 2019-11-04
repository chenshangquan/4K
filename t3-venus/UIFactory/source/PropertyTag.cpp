// PropertyTag.cpp: implementation of the CPropertyTag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "PropertyTag.h"
#include "LayoutXmlHandle.h"
#include "IPropertyAssist.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

CPropertyTag::CPropertyTag() : IXmlTag()
{

}

CPropertyTag::~CPropertyTag()
{

}

bool CPropertyTag::ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext /* = 0 */ )
{
	CLayoutHandle* pHandle = (CLayoutHandle*)pContext;
	const Window* pParentWindow = pHandle->GetCurWindow();
	if ( pParentWindow == 0 )
	{
		LOGEVENT( "CPropertyTag::ElementStart 窗口没有创建好 " );
		return false;
	}
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
	CPropertyAssist::GetSingletonPtr()->SetProperty( xmlAttributes, pParentWindow, pInfo->strType );
	return false;
}

bool CPropertyTag::ElementEnd( String strElement, void* pContext /* = 0 */ )
{
	return false;
}

} //  namespace AutoUIFactory end
