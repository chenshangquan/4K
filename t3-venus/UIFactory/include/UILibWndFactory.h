// UILibWndFactory.h: interface for the UILibWndFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UILIBWNDFACTORY_H__4FDEC029_339F_46CE_BEB1_65B3F25D391C__INCLUDED_)
#define AFX_UILIBWNDFACTORY_H__4FDEC029_339F_46CE_BEB1_65B3F25D391C__INCLUDED_

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
DECLARE_WINDOW_FACTORY( CFlatButton )
DECLARE_WINDOW_FACTORY( CSkinScroll )
DECLARE_WINDOW_FACTORY( CSkinHeaderCtrl )

DECLARE_WINDOW_FACTORY( CFlatDDButton )
DECLARE_WINDOW_FACTORY( CCheckButton )

DECLARE_WINDOW_FACTORY( CSkinFrame )
DECLARE_WINDOW_FACTORY( CSkinListCtrl )
DECLARE_WINDOW_FACTORY( CSkinDDListCtrl )

DECLARE_WINDOW_FACTORY( CSkinSlider )
DECLARE_WINDOW_FACTORY( CSkinEdit )
DECLARE_WINDOW_FACTORY( CSkinIPCtrl )

DECLARE_WINDOW_FACTORY( CStaticEx )
DECLARE_WINDOW_FACTORY( CSkinComboBox )
DECLARE_WINDOW_FACTORY( CBMPDlg )

DECLARE_WINDOW_FACTORY( CSkinSpinCtrl )
DECLARE_WINDOW_FACTORY( CSkinGroup )
DECLARE_WINDOW_FACTORY( CTextButton30 )

DECLARE_WINDOW_FACTORY( CSkinTab )
DECLARE_WINDOW_FACTORY( CSkinSheet )
DECLARE_WINDOW_FACTORY( CSkinPage )

DECLARE_WINDOW_FACTORY( CSkinCheckList )
DECLARE_WINDOW_FACTORY( CColourPopup )
DECLARE_WINDOW_FACTORY( CColorSelCtrl )

DECLARE_WINDOW_FACTORY( CSkinDateTime )

// declare window factory end

// declare propertyset begin

// declare propertyset end
} // namespace AutoUIFactory end
/** @} */
#endif // !defined(AFX_UILIBWNDFACTORY_H__4FDEC029_339F_46CE_BEB1_65B3F25D391C__INCLUDED_)
