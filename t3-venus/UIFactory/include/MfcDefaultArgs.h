// MfcDefaultArgs.h: interface for the MfcDefaultArgs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCDEFAULTARGS_H__8C76FABC_9650_4119_93C3_7EFECC22CD30__INCLUDED_)
#define AFX_MFCDEFAULTARGS_H__8C76FABC_9650_4119_93C3_7EFECC22CD30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "templateClass.h"
#include "WindowManage.h"
/*
 * @DefaultArgs 一些默认的参数类
 * @{
 */
namespace AutoUIFactory
{
	class Args_WindowMsg : public IArgs
	{
	public:
		Args_WindowMsg( WindowMsg& msg ) : IArgs( "WindowMsg" ),m_Msg( msg ){}
		WindowMsg m_Msg;
	};
	class Args_WindowTree : public IArgs
	{
	public:
		Args_WindowTree( IWndTree* piTree ) : IArgs( "WindowTree" ), m_piTree( piTree ){}
		IWndTree* m_piTree;
	};
	class Args_WindowCreate : public IArgs
	{
	public:
		Args_WindowCreate( String& strType, String& strName, String& strStyle, Window* pParent,String strExStyle = "", String strModal= "" ) : IArgs( "WindowCreate") ,
			  m_strType( strType ), m_strName( strName ), m_strStyle( strStyle ), m_pParent( pParent ), m_strExStyle(strExStyle),m_strModal(strModal){}
		String m_strType;
		String m_strName;
		String m_strStyle;
		String m_strExStyle;
		Window* m_pParent;	
		String m_strModal;//是否是模态窗口 2012.12.3 yjj
	};
} // namespace AutoUIFactory end

/** @} */
#endif // !defined(AFX_MFCDEFAULTARGS_H__8C76FABC_9650_4119_93C3_7EFECC22CD30__INCLUDED_)
