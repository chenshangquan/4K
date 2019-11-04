// WindowTag.cpp: implementation of the CWindowTag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "WindowTag.h"
#include "LayoutXmlHandle.h"
#include "WindowManage.h"
#include "MfcDefaultArgs.h"
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

const String CWindowTag::strName = "Name";
const String CWindowTag::strType = "Type";
const String CWindowTag::strValue = "Value";
const String CWindowTag::strArgs = "Args";
const String CWindowTag::strStyle = "Style";
const String CWindowTag::strExStyle = "ExStyle";
const String CWindowTag::strModal = "Modal";
CWindowTag::CWindowTag() : IXmlTag()
{

}

CWindowTag::~CWindowTag()
{

}

bool CWindowTag::ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext /* = 0 */ )
{
	CLayoutHandle* pHandle = (CLayoutHandle*)pContext;
	const Window* pParentWindow = pHandle->GetCurWindow();
	String strType = xmlAttributes.getValue( CWindowTag::strType );
	String strName = xmlAttributes.getValue( CWindowTag::strName );
	String strStyle = "";
	if ( xmlAttributes.exists(CWindowTag::strStyle) == true )
	{
		strStyle = xmlAttributes.getValue( CWindowTag::strStyle );
	}

	strType = CWindowTypeManage::GetSingletonPtr()->GetType( strType );

	Args_WindowCreate args( strType, strName, strStyle,const_cast<Window*>(pParentWindow) );
	if ( xmlAttributes.exists( CWindowTag::strExStyle ) == true )
	{
		args.m_strExStyle = xmlAttributes.getValue( CWindowTag::strExStyle );
	}

	//增加模态窗口类型 2012.12.3 yjj
	if ( xmlAttributes.exists( CWindowTag::strModal ) == true )
	{
		args.m_strModal = xmlAttributes.getValue( CWindowTag::strModal );
	}

	Window* pNew = CWindowManage::GetSingletonPtr()->Create( args );
	pHandle->AppendWindow( pNew, strName, xmlAttributes );
	if ( pNew == 0 )
	{
		LOGEVENT( "CWindowTag::ElementStart 创建窗口失败 element = " + strElement );
		return false;
	}
	
	return true;
}

bool CWindowTag::ElementEnd( String strElement, void* pContext /* = 0 */ )
{
	CLayoutHandle* pHandle = (CLayoutHandle*)pContext;
	pHandle->PopWindow();
	return true;
}

} // namespace AutoUIFactory end
