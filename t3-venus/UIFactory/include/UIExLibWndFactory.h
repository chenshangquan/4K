// UIExLibWndFactory.h: interface for the UIExLibWndFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIEXLIBWNDFACTORY_H__22F92F89_F603_47B7_898F_7F5C665E5611__INCLUDED_)
#define AFX_UIEXLIBWNDFACTORY_H__22F92F89_F603_47B7_898F_7F5C665E5611__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "uifactorydef.h"
#include "windowfactory.h"

/*
 * @name 对UILIB的一些控件进行支持
 * @{
 */
namespace AutoUIFactory
{
// declare window factory begin
DECLARE_WINDOW_FACTORY( CBaseWnd ) //该wnd为不透明的  yujj
//DECLARE_WINDOW_FACTORY( CBmpWnd )
DECLARE_WINDOW_FACTORY( CTransparentBaseWnd )
//DECLARE_WINDOW_FACTORY( CTouchList )
DECLARE_WINDOW_FACTORY( CDragWindow )
//DECLARE_WINDOW_FACTORY( CTransparentWnd )
DECLARE_WINDOW_FACTORY( CTransparentList )
DECLARE_WINDOW_FACTORY( CTransparentHoriList )
DECLARE_WINDOW_FACTORY( CTransparentViewList )
DECLARE_WINDOW_FACTORY( CTransparentBtn )
DECLARE_WINDOW_FACTORY( CTransparentCheckButton )
DECLARE_WINDOW_FACTORY( CTransparentSwitchButton )
DECLARE_WINDOW_FACTORY( CTransparentEdit )
//DECLARE_WINDOW_FACTORY( CTransparentIPAddrCtrl )
DECLARE_WINDOW_FACTORY( CTransparentStatic ) 
DECLARE_WINDOW_FACTORY( CTransparentSliderCtrl )
DECLARE_WINDOW_FACTORY( CLetterIndex ) 
DECLARE_WINDOW_FACTORY( CTransparentIpEdit )
DECLARE_WINDOW_FACTORY( CTransparentSlideBlock )
DECLARE_WINDOW_FACTORY( CTransparentSliderWnd )
DECLARE_WINDOW_FACTORY( CTransparentCalendar )
DECLARE_WINDOW_FACTORY( CTransparentDragButton )
DECLARE_WINDOW_FACTORY( CTransparentProgress )
DECLARE_WINDOW_FACTORY( CVirtualBattery )
DECLARE_WINDOW_FACTORY( CTransparentComboBox )

} // namespace AutoUIFactory end
/** @} */

#endif // !defined(AFX_UIEXLIBWNDFACTORY_H__22F92F89_F603_47B7_898F_7F5C665E5611__INCLUDED_)
