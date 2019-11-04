// SchemeTag.cpp: implementation of the CSchemeTag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "SchemeTag.h"
#include "LayoutXmlHandle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


namespace AutoUIFactory
{
const String CSchemeTag::strName = "Name";
CSchemeTag::CSchemeTag() : IXmlTag()
{

}

CSchemeTag::~CSchemeTag()
{

}
	
bool CSchemeTag::ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext /* = 0 */ )
{
	CLayoutHandle* pHandle = (CLayoutHandle*)pContext;
	pHandle->m_bInScheme = true;
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
	String strName = xmlAttributes.getValue( CSchemeTag::strName );
	pInfo->AddScheme( strName, xmlAttributes );

	return true;
}

bool CSchemeTag::ElementEnd( String strElement, void* pContext /* = 0 */ )
{
	CLayoutHandle* pHandle = (CLayoutHandle*)pContext;
	pHandle->m_bInScheme = false;

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
    pInfo->EndScheme();
	return true;
}
	
}