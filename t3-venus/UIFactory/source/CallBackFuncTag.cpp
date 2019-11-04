// CallBackFuncTag.cpp: implementation of the CCallBackFuncTag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "CallBackFuncTag.h"
#include "LayoutXmlHandle.h"
#include "CallFuncManage.h"
#include "MfcDefaultArgs.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

const String CCallBackFuncTag::strType = "Type";
const String CCallBackFuncTag::strValue = "Value";

CCallBackFuncTag::CCallBackFuncTag()
{

}

CCallBackFuncTag::~CCallBackFuncTag()
{

}


bool CCallBackFuncTag::ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext /* = 0 */ )
{
	CLayoutHandle* pHandle = static_cast<CLayoutHandle*>(pContext);
	const Window* pCurWnd = pHandle->GetCurWindow();
	if ( pCurWnd == 0 )
	{
		LOGEVENT( "CEventTag::ElementStart 没有找到对应窗体 strElement = " + strElement );
		return false;
	}
	String strType = xmlAttributes.getValue( CCallBackFuncTag::strType );
	String strFunc = xmlAttributes.getValue( CCallBackFuncTag::strValue );
	
	const IWndTree* piWndTree = pHandle->GetCurWindowTree();
	Args_WindowTree argsWindowTree( const_cast<IWndTree*>(piWndTree) );
	bool bResult = CFuncManage::GetSingletonPtr()->ExeFunc( strFunc, argsWindowTree );
	if ( bResult == false )
	{
		LOGEVENT( "CCallBackFuncTag::ElementStart  函数没有执行成功 name= " + strFunc );
	}
	return false;
}

bool CCallBackFuncTag::ElementEnd( String strElement, void* pContext /* = 0 */ )
{
	return false;
}

} // namespace AutoUIFactory end
