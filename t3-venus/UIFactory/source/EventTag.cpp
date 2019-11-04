// EventTag.cpp: implementation of the CEventTag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "LayoutXmlHandle.h"
#include "WndMsgEventManage.h"
#include "EventTag.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

const String CEventTag::strFuncType = "FuncType";
const String CEventTag::strFunc = "Value";
const String CEventTag::strEventID = "Type";

CEventTag::CEventTag() : IXmlTag()
{

}

CEventTag::~CEventTag()
{

}

bool CEventTag::ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext /* = 0 */ )
{
	CLayoutHandle* pHandle = static_cast<CLayoutHandle*>(pContext);
	const Window* pCurWnd = pHandle->GetCurWindow();
	if ( pCurWnd == 0 )
	{
		LOGEVENT( "CEventTag::ElementStart 没有找到对应窗体 strElement = " + strElement );
		return false;
	}
	String strFuncType = CWndMsgEventManage::strFunc;
	String strEventID = "";
	String strFunc = "";
	if ( xmlAttributes.exists( CEventTag::strFunc ) && xmlAttributes.exists( CEventTag::strEventID ) )
	{
		strEventID = xmlAttributes.getValue( CEventTag::strEventID );
		strFunc = xmlAttributes.getValue( CEventTag::strFunc );
	}
	if ( xmlAttributes.exists( CEventTag::strFuncType ) )
	{
		strFuncType = xmlAttributes.getValue( CEventTag::strFuncType );
	}
	
	REG_WND_MSG_EVENT( pCurWnd->GetSafeHwnd(), strEventID, strFunc, strFuncType );
	return true;
}

bool CEventTag::ElementEnd( String strElement, void* pContext /* = 0 */ )
{
	return false;
}

} // namespace AutoUIFactory end
