// RegDefaultData.cpp: implementation of the CRegDefaultData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RegDefaultData.h"
#include "WindowFacotryManage.h"
#include "PropertySet.h"
#include "IPropertyAssist.h"
#include "MfcDefaultWndFactory.h"
#include "MfcDefaultWndProperty.h"
#include "MfcDefaultWndPropertySet.h"
#include "UILibWndFactory.h"
#include "UILibPropertySet.h"
#include "UIExLibWndFactory.h"
#include "UIExLibPropertySet.h"
#include "WndMsgEventManage.h"
#include "msgIdDispatch.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

CRegDefaultData::CRegDefaultData()
{

}

CRegDefaultData::~CRegDefaultData()
{

}

void CRegDefaultData::RegAllDefaultData()
{
	CRegDefaultData::RegDefaultWindowFactory();
	CRegDefaultData::RegDefaultWindowProperty();
	CRegDefaultData::RegDefaultWindowPropertySet();
	CRegDefaultData::RegDefaultWindowEvent();
	CRegDefaultData::RegUILibPropertySet();
	CRegDefaultData::RegUILibWindowFactory();
	CRegDefaultData::RegDefaultStyle();
	//CRegDefaultData::RegDefaultAlgorithm();
}

void CRegDefaultData::RegDefaultWindowFactory()
{   
	REG_WINDOW_FACTORY( CButton );
	REG_WINDOW_FACTORY( CEdit );
	REG_WINDOW_FACTORY( CStatic );
	REG_WINDOW_FACTORY( CIPAddressCtrl );
    REG_WINDOW_FACTORY( CSliderCtrl  );
}

//注册属性
void CRegDefaultData::RegDefaultWindowProperty()
{
 	REG_PROPERTY( WindowPos );
 	REG_PROPERTY( WindowCaption );
 	REG_PROPERTY( WindowSize );
 	REG_PROPERTY( WindowVisible );
 	REG_PROPERTY( WindowEnable );  
	REG_PROPERTY( WindowOwer );
	REG_PROPERTY( CIPAddressCtrlData ); 
	REG_PROPERTY( CButtonCheckState );

    //2012.11.28 by yjj
	REG_PROPERTY( TransparentDlgBaseImage ); 
	REG_PROPERTY( TransparentDlgBaseAutoHideStatus );
	REG_PROPERTY( TransparentDlgBaseMoveStatus ); 
	REG_PROPERTY( TransparentDlgBaseBkStretch ); 

/*	REG_PROPERTY( BmpWndImage );
	REG_PROPERTY( BmpWndMoveStatus );
	REG_PROPERTY( BmpWndStrethStatus );
	REG_PROPERTY( BmpWndChanageRgnStatus );*/
	REG_PROPERTY( LayoutAlgorithm );
	REG_PROPERTY( SortAlgorithm );
//	REG_PROPERTY( TransparentWndImage );
    REG_PROPERTY( TransparentBaseWndImage );
	REG_PROPERTY( TransparentListImage );
	REG_PROPERTY( TransparentListSingleImage );
	REG_PROPERTY( TransparentBtnImage );
    REG_PROPERTY( TransparentBtnUseTimer );  //add btn hold timer
	REG_PROPERTY( TransparentCheckBtnImage );
	REG_PROPERTY( TransparentCheckBtnFontSpan );
	REG_PROPERTY( TransparentCheckBtnFontColor );
	REG_PROPERTY( TransparentCheckBtnFontSize );
	REG_PROPERTY( TransparentSwitchBtnImage );
	REG_PROPERTY( TransparentSwitchBtnFontSize );
	REG_PROPERTY( TransparentEditImage );
	REG_PROPERTY( TransparentEditFontSize );
	REG_PROPERTY( TransparentEditFontColor );
	REG_PROPERTY( TransparentEditShowIcon );
	REG_PROPERTY( TransparentEditLimitLength );
	REG_PROPERTY( TransparentEditFrontLen );
	REG_PROPERTY( TransparentEditBackLen );
	REG_PROPERTY( TransparentEditTipStr );
	REG_PROPERTY( TransparentEditAlign );
	REG_PROPERTY( TransparentEditSearch );
	REG_PROPERTY( TransparentEditDeleteText );
    REG_PROPERTY( TransparentEditDisableImg );
	REG_PROPERTY( TransparentBaseWndMoveStatus );
//	REG_PROPERTY( TransparentIPAddrCtrlImage );
	REG_PROPERTY( TransparentBaseWndAutoHideStatus );
	REG_PROPERTY( TransparentStaticImage );
	REG_PROPERTY( TransparentStaticFontSize );
	REG_PROPERTY( TransparentStaticFontName );
	REG_PROPERTY( TransparentStaticFontColor );
    REG_PROPERTY( TransparentStaticFontStyle );
	REG_PROPERTY( TransparentStaticAlign );
    REG_PROPERTY( StaticExBkTransparent );
	REG_PROPERTY( StaticExTextColor );
	REG_PROPERTY( StaticExFontSize );
    REG_PROPERTY( CSliderCtrlPos );
    REG_PROPERTY( CSliderCtrlRange );
    REG_PROPERTY( TransparentSliderCtrlImage );
	REG_PROPERTY( CTransparentListShowItemStatus );
	REG_PROPERTY( TransparentListDrag );
	REG_PROPERTY( TransparentListClickNoSel );
    REG_PROPERTY( TransparentListSelItem );
	REG_PROPERTY( TransparentListOffset );
	REG_PROPERTY( TransparentListClickFocus );
	REG_PROPERTY( TransparentListBkgColor );
	REG_PROPERTY( TransparentListItemSizeSame );
	REG_PROPERTY( TransparentListMultiSel );
	REG_PROPERTY( TransparentListOver );
	REG_PROPERTY( TransparentListData );
	REG_PROPERTY( SwitchState );
	REG_PROPERTY( SwitchBtnBindWnd );
    REG_PROPERTY( SwitchBtnShowText );
	REG_PROPERTY( LetterIndexImage );
	REG_PROPERTY( BindList );	
	REG_PROPERTY( IpEditData );
	REG_PROPERTY( TransparentSlideBlockImage );
	REG_PROPERTY( TransparentCalendarImage );
    REG_PROPERTY( CTransparentSliderWndImage );
    REG_PROPERTY( CTransparentSliderWndRange );
	REG_PROPERTY( CTransparentSliderWndStyle );
    REG_PROPERTY( CTransparentSliderWndPos );
	REG_PROPERTY( TransparentDragBtnImage );
	REG_PROPERTY( DragButtonOnline );
	REG_PROPERTY( DragButtonSel );
	REG_PROPERTY( DragButtonData );
	REG_PROPERTY( TransparentProgressImage );
	REG_PROPERTY( ProgressPos );
	REG_PROPERTY( VirtualBatteryImage );
	REG_PROPERTY( BatteryLife );
	REG_PROPERTY( TransparentComboBoxIPStyle );
	REG_PROPERTY( TransparentComboBoxListBkColor );
	REG_PROPERTY( TransparentComboBoxImage );
	REG_PROPERTY( TransparentComboBoxFontSize );
	REG_PROPERTY( TransparentComboBoxEditEdgeHeight );
	REG_PROPERTY( TransparentComboBoxDropListHeight );
	REG_PROPERTY( TransparentComboBoxEditFrontLen );
	REG_PROPERTY( TransparentComboBoxEditBackLen );
	REG_PROPERTY( TransparentComboBoxShowIcon );
	REG_PROPERTY( TransparentComboBoxReadOnly );
	REG_PROPERTY( TransparentComboBoxText );
	REG_PROPERTY( TransparentComboBoxLimitLength );
    REG_PROPERTY( TransHoriListOffset );
    REG_PROPERTY( TransHoriListSelItem ); 
	REG_PROPERTY( TransparentListData );
    REG_PROPERTY( TransparentViewListImage );
	REG_PROPERTY( TransparentViewListOver );
    REG_PROPERTY( ViewListSelItem );
    REG_PROPERTY( ViewListVertSliderOffset);
    REG_PROPERTY( ViewListHoriSliderOffset);
}

void CRegDefaultData::RegDefaultWindowPropertySet()
{   
	REG_PROPERTY_SET( CWnd ); 
	REG_PROPERTY_SET( CButton );
	REG_PROPERTY_SET( CEdit );
	REG_PROPERTY_SET( CStatic ); 
	REG_PROPERTY_SET( CIPAddressCtrl );
    REG_PROPERTY_SET( CSliderCtrl ); 

}

void CRegDefaultData::RegDefaultWindowEvent()
{
	REG_DEFAULT_WINDOW_MSG( WM_LBUTTONUP );
	REG_DEFAULT_WINDOW_MSG( WM_LBUTTONDBLCLK );
	REG_DEFAULT_WINDOW_MSG( WM_LBUTTONDOWN );
	REG_DEFAULT_WINDOW_MSG( WM_RBUTTONDOWN );
	REG_DEFAULT_WINDOW_MSG( WM_RBUTTONUP );
	REG_DEFAULT_WINDOW_MSG( WM_RBUTTONDBLCLK );
	REG_DEFAULT_WINDOW_MSG( UI_DRAG_OVER );
	REG_DEFAULT_WINDOW_MSG( UI_DRAG_LEAVE );
	REG_DEFAULT_WINDOW_MSG( UI_DRAG_END );
    REG_DEFAULT_WINDOW_MSG( UI_BE_DRAG_END );
	REG_DEFAULT_WINDOW_MSG( UI_EDITDELETE_CLICK );
	REG_DEFAULT_WINDOW_MSG( UI_SLIDEBLOCK_ENDLOCK );
    
    REG_DEFAULT_WINDOW_MSG( NM_RELEASEDCAPTURE );   
    REG_DEFAULT_WINDOW_MSG( SLIDER_RELEASED_CAPTURE ); //slider 放开thumb通知    
    REG_DEFAULT_WINDOW_MSG( SLIDER_CHANGED );  //slider thumb位置变化通知
    REG_DEFAULT_WINDOW_MSG( WM_LST_UN_SELECT_ITEM );//list当前没有选中项
	REG_DEFAULT_WINDOW_MSG( UI_CALENDAR_SELECT_DATE );
    REG_DEFAULT_WINDOW_MSG( WM_EDIT_SETFOCUS );    //编辑框获取到焦点
	REG_DEFAULT_WINDOW_MSG( WM_EDIT_ONCHAR );
	REG_DEFAULT_WINDOW_MSG( WM_COMBOX_ONCHAR );
	REG_DEFAULT_WINDOW_MSG( WM_EDIT_CHANGED );
	REG_DEFAULT_WINDOW_MSG( WM_EDIT_CHANGED_NOFOCUS );  //编辑框里面值改变但是没有获取到焦点---JYY  供cnstool使用
	REG_DEFAULT_WINDOW_MSG( WM_CLICK_COMBOLIST );
    REG_DEFAULT_WINDOW_MSG( WM_BUTTON_CLICK );    
	REG_DEFAULT_WINDOW_MSG( WM_KILL_FOCUS );

    REG_DEFAULT_WINDOW_MSG( WM_SETFOCUS );
    REG_DEFAULT_WINDOW_MSG( WM_KILLFOCUS );

	REG_DEFAULT_WINDOW_MSG( UI_LISTOFFSET_NOTIFY );	
    REG_DEFAULT_WINDOW_MSG( WM_CHAR );   
    REG_DEFAULT_WINDOW_MSG( WM_BTN_HOLD );   
    REG_DEFAULT_WINDOW_MSG( WM_BTN_HOLD_END );  
    REG_DEFAULT_WINDOW_MSG( WM_SOFTKEYBOARD_SHOW );
    REG_DEFAULT_WINDOW_MSG( WM_SOFTKEYBOARD_HIDE );

    REG_DEFAULT_WINDOW_MSG( WM_HIDE_WND ); //窗口隐藏向自己发消息

    REG_DEFAULT_WINDOW_MSG( WM_POST_DOMODAL );

    REG_DEFAULT_WINDOW_MSG( WM_BUTTON_DOWN ); //单击鼠标左键消息 dyy 2014年4月28日 响应文档摄像机点击down时发送actBegin消息
    REG_DEFAULT_WINDOW_MSG( WM_BUTTONSTATUS_NORMAL );
}

void CRegDefaultData::RegUILibWindowFactory()
{
   	/*REG_WINDOW_FACTORY( CFlatButton );
	REG_WINDOW_FACTORY( CSkinScroll);
	REG_WINDOW_FACTORY( CSkinHeaderCtrl );

	REG_WINDOW_FACTORY( CFlatDDButton );
	REG_WINDOW_FACTORY( CCheckButton );
	
	REG_WINDOW_FACTORY( CSkinFrame );
	REG_WINDOW_FACTORY( CSkinListCtrl );
	REG_WINDOW_FACTORY( CSkinDDListCtrl );
	
	REG_WINDOW_FACTORY( CSkinSlider );
	REG_WINDOW_FACTORY( CSkinEdit );
	REG_WINDOW_FACTORY( CSkinIPCtrl );
	
	REG_WINDOW_FACTORY( CStaticEx );
	REG_WINDOW_FACTORY( CSkinComboBox );
	REG_WINDOW_FACTORY( CBMPDlg );
	
	REG_WINDOW_FACTORY( CSkinSpinCtrl );
	REG_WINDOW_FACTORY( CSkinGroup );
	REG_WINDOW_FACTORY( CTextButton30 );
	
	REG_WINDOW_FACTORY( CSkinTab );
	REG_WINDOW_FACTORY( CSkinSheet );
	REG_WINDOW_FACTORY( CSkinPage );
	
	REG_WINDOW_FACTORY( CSkinCheckList );
	REG_WINDOW_FACTORY( CColourPopup );
	REG_WINDOW_FACTORY( CColorSelCtrl );
	
	REG_WINDOW_FACTORY( CSkinDateTime );
    */
	REG_WINDOW_FACTORY( CTransparentBaseWnd );
//	REG_WINDOW_FACTORY( CBmpWnd );
    REG_WINDOW_FACTORY( CBaseWnd );//不透明wnd
//	REG_WINDOW_FACTORY( CTouchList );

//	REG_WINDOW_FACTORY( CTransparentWnd );
	REG_WINDOW_FACTORY( CTransparentEdit );
	REG_WINDOW_FACTORY( CTransparentBtn );
	REG_WINDOW_FACTORY( CTransparentCheckButton );
	REG_WINDOW_FACTORY( CTransparentSwitchButton );
	REG_WINDOW_FACTORY( CTransparentList );
    REG_WINDOW_FACTORY( CTransparentHoriList );
    REG_WINDOW_FACTORY( CTransparentViewList );
//	REG_WINDOW_FACTORY( CTransparentIPAddrCtrl );
	REG_WINDOW_FACTORY( CTransparentStatic );
	REG_WINDOW_FACTORY( CStaticEx );
    REG_WINDOW_FACTORY( CTransparentSliderCtrl );
    REG_WINDOW_FACTORY( CTransparentSliderWnd );
	REG_WINDOW_FACTORY( CLetterIndex );
	REG_WINDOW_FACTORY( CTransparentIpEdit );
	REG_WINDOW_FACTORY( CTransparentSlideBlock );
	REG_WINDOW_FACTORY( CTransparentCalendar );
	REG_WINDOW_FACTORY( CTransparentDragButton );
	REG_WINDOW_FACTORY( CTransparentProgress );
	REG_WINDOW_FACTORY( CVirtualBattery ); 
	REG_WINDOW_FACTORY( CTransparentDlg );//2012.11.28 by yjj
	REG_WINDOW_FACTORY( CTransparentComboBox );
}

void CRegDefaultData::RegUILibPropertySet()
{
    /*
	REG_PROPERTY_SET( CFlatButton );
	REG_PROPERTY_SET( CSkinScroll);
	REG_PROPERTY_SET( CSkinHeaderCtrl );
	
	REG_PROPERTY_SET( CFlatDDButton );
	REG_PROPERTY_SET( CCheckButton );
	
	REG_PROPERTY_SET( CSkinFrame );
	REG_PROPERTY_SET( CSkinListCtrl );
	REG_PROPERTY_SET( CSkinDDListCtrl );
	
	REG_PROPERTY_SET( CSkinSlider );
	REG_PROPERTY_SET( CSkinEdit );
	REG_PROPERTY_SET( CSkinIPCtrl );
	
	REG_PROPERTY_SET( CStaticEx );
	REG_PROPERTY_SET( CSkinComboBox );
	REG_PROPERTY_SET( CBMPDlg );
	
	REG_PROPERTY_SET( CSkinSpinCtrl );
	REG_PROPERTY_SET( CSkinGroup );
	REG_PROPERTY_SET( CTextButton30 );
	
	REG_PROPERTY_SET( CSkinTab );
	REG_PROPERTY_SET( CSkinSheet );
	REG_PROPERTY_SET( CSkinPage );
	
	REG_PROPERTY_SET( CSkinCheckList );
	REG_PROPERTY_SET( CColourPopup );
	REG_PROPERTY_SET( CColorSelCtrl );
	
	REG_PROPERTY_SET( CSkinDateTime );*/
//	REG_PROPERTY_SET( CBmpWnd );
	REG_PROPERTY_SET( CTransparentBaseWnd );
    REG_PROPERTY_SET( CBaseWnd ); 
//	REG_PROPERTY_SET( CTouchList );	
//	REG_PROPERTY_SET( CTransparentWnd );
	REG_PROPERTY_SET( CTransparentEdit);
	REG_PROPERTY_SET( CTransparentBtn );
	REG_PROPERTY_SET( CTransparentCheckButton );
	REG_PROPERTY_SET( CTransparentSwitchButton );
	REG_PROPERTY_SET( CTransparentList );
    REG_PROPERTY_SET( CTransparentHoriList );
    REG_PROPERTY_SET( CTransparentViewList );
//	REG_PROPERTY_SET( CTransparentIPAddrCtrl );
	REG_PROPERTY_SET( CTransparentStatic );
	REG_PROPERTY_SET( CStaticEx );
    REG_PROPERTY_SET( CTransparentSliderCtrl );
    REG_PROPERTY_SET( CTransparentSliderWnd );
	REG_PROPERTY_SET( CLetterIndex );
	REG_PROPERTY_SET( CTransparentIpEdit );
	REG_PROPERTY_SET( CTransparentSlideBlock );
	REG_PROPERTY_SET( CTransparentCalendar );
	REG_PROPERTY_SET( CTransparentDragButton );
	REG_PROPERTY_SET( CTransparentProgress );	
	REG_PROPERTY_SET( CVirtualBattery ); 
	REG_PROPERTY_SET( CTransparentDlgBase ); //2012.11.28 by yjj
	REG_PROPERTY_SET( CTransparentDlg );//2012.11.28 by yjj
	REG_PROPERTY_SET( CTransparentComboBox );
}

void CRegDefaultData::RegDefaultStyle()
{
	REG_DEFAULT_WINDOW_STYLE( WS_OVERLAPPED );
	REG_DEFAULT_WINDOW_STYLE( WS_POPUP );
	REG_DEFAULT_WINDOW_STYLE( WS_CHILD );
	REG_DEFAULT_WINDOW_STYLE( WS_MINIMIZE );
	REG_DEFAULT_WINDOW_STYLE( WS_VISIBLE );
	REG_DEFAULT_WINDOW_STYLE( WS_DISABLED );
	REG_DEFAULT_WINDOW_STYLE( WS_CLIPSIBLINGS );
	REG_DEFAULT_WINDOW_STYLE( WS_CLIPCHILDREN );
	REG_DEFAULT_WINDOW_STYLE( WS_MAXIMIZE );
	REG_DEFAULT_WINDOW_STYLE( WS_CAPTION );     /* WS_BORDER | WS_DLGFRAME  */
	REG_DEFAULT_WINDOW_STYLE( WS_BORDER );
	REG_DEFAULT_WINDOW_STYLE( WS_DLGFRAME );
	REG_DEFAULT_WINDOW_STYLE( WS_VSCROLL );
	REG_DEFAULT_WINDOW_STYLE( WS_HSCROLL );
	REG_DEFAULT_WINDOW_STYLE( WS_SYSMENU );
	REG_DEFAULT_WINDOW_STYLE( WS_THICKFRAME );
	REG_DEFAULT_WINDOW_STYLE( WS_GROUP );
	REG_DEFAULT_WINDOW_STYLE( WS_TABSTOP );
	
	REG_DEFAULT_WINDOW_STYLE( WS_MINIMIZEBOX );
	REG_DEFAULT_WINDOW_STYLE( WS_MAXIMIZEBOX );
	
	//2012.12.12 yjj dlgStyle 
	REG_DEFAULT_WINDOW_STYLE( DS_CENTER );
	REG_DEFAULT_WINDOW_STYLE( DS_CENTERMOUSE );

	REG_DEFAULT_WINDOW_STYLE( WS_TILED );
	REG_DEFAULT_WINDOW_STYLE( WS_ICONIC );
	REG_DEFAULT_WINDOW_STYLE( WS_SIZEBOX );
	REG_DEFAULT_WINDOW_STYLE( WS_TILEDWINDOW );
	
	/*
	* Common Window Styles
	*/
	REG_DEFAULT_WINDOW_STYLE( WS_OVERLAPPEDWINDOW );
	REG_DEFAULT_WINDOW_STYLE( WS_POPUPWINDOW );
	REG_DEFAULT_WINDOW_STYLE( WS_CHILDWINDOW );
	
	/*
	* Extended Window Styles
	*/
	REG_DEFAULT_WINDOW_STYLE( WS_EX_DLGMODALFRAME );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_NOPARENTNOTIFY );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_TOPMOST );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_ACCEPTFILES );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_TRANSPARENT );
#if(WINVER >= 0x0400)
	REG_DEFAULT_WINDOW_STYLE( WS_EX_MDICHILD );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_TOOLWINDOW );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_WINDOWEDGE );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_CLIENTEDGE );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_CONTEXTHELP );
	
	REG_DEFAULT_WINDOW_STYLE( WS_EX_RIGHT );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_LEFT );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_RTLREADING );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_LTRREADING );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_LEFTSCROLLBAR );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_RIGHTSCROLLBAR );
	
	REG_DEFAULT_WINDOW_STYLE( WS_EX_CONTROLPARENT );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_STATICEDGE );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_APPWINDOW );
	
	
	REG_DEFAULT_WINDOW_STYLE( WS_EX_OVERLAPPEDWINDOW );
	REG_DEFAULT_WINDOW_STYLE( WS_EX_PALETTEWINDOW );
#endif /* WINVER >= 0x0400 */

	 /*
	* CButton Style
	*/
    REG_DEFAULT_WINDOW_STYLE( BS_AUTOCHECKBOX  );
    REG_DEFAULT_WINDOW_STYLE( BS_AUTORADIOBUTTON  );
    REG_DEFAULT_WINDOW_STYLE( BS_AUTO3STATE  );
    REG_DEFAULT_WINDOW_STYLE( BS_CHECKBOX );
    REG_DEFAULT_WINDOW_STYLE( BS_DEFPUSHBUTTON  );
    REG_DEFAULT_WINDOW_STYLE( BS_GROUPBOX  );
    REG_DEFAULT_WINDOW_STYLE( BS_LEFTTEXT  );
    REG_DEFAULT_WINDOW_STYLE( BS_OWNERDRAW );
    REG_DEFAULT_WINDOW_STYLE( BS_PUSHBUTTON );
    REG_DEFAULT_WINDOW_STYLE( BS_RADIOBUTTON ); 
    REG_DEFAULT_WINDOW_STYLE( BS_3STATE );

     /*
	* CSliderCtrl Style
	*/
    REG_DEFAULT_WINDOW_STYLE( TBS_HORZ  );
    REG_DEFAULT_WINDOW_STYLE( TBS_VERT  );
    REG_DEFAULT_WINDOW_STYLE( TBS_AUTOTICKS  );
    REG_DEFAULT_WINDOW_STYLE( TBS_NOTICKS );
    REG_DEFAULT_WINDOW_STYLE( TBS_BOTTOM  );
    REG_DEFAULT_WINDOW_STYLE( TBS_TOP  );
    REG_DEFAULT_WINDOW_STYLE( TBS_RIGHT  );
    REG_DEFAULT_WINDOW_STYLE( TBS_ENABLESELRANGE );

     /*
	* CEdit Style
	*/
    REG_DEFAULT_WINDOW_STYLE( ES_PASSWORD );
    REG_DEFAULT_WINDOW_STYLE( ES_AUTOHSCROLL );
    REG_DEFAULT_WINDOW_STYLE( ES_AUTOVSCROLL );
    REG_DEFAULT_WINDOW_STYLE( ES_CENTER );
    REG_DEFAULT_WINDOW_STYLE( ES_LEFT );
    REG_DEFAULT_WINDOW_STYLE( ES_LOWERCASE );
    REG_DEFAULT_WINDOW_STYLE( ES_NOHIDESEL );
    REG_DEFAULT_WINDOW_STYLE( ES_OEMCONVERT );
    REG_DEFAULT_WINDOW_STYLE( ES_RIGHT );
    REG_DEFAULT_WINDOW_STYLE( ES_UPPERCASE );
    REG_DEFAULT_WINDOW_STYLE( ES_READONLY );
    REG_DEFAULT_WINDOW_STYLE( ES_WANTRETURN ); 
    REG_DEFAULT_WINDOW_STYLE( ES_NUMBER ); 
	REG_DEFAULT_WINDOW_STYLE( ES_MULTILINE );


	 /*
	* Static Style
	*/
	REG_DEFAULT_WINDOW_STYLE( SS_LEFT ); 
	REG_DEFAULT_WINDOW_STYLE( SS_CENTER );
	REG_DEFAULT_WINDOW_STYLE( SS_RIGHT );
	REG_DEFAULT_WINDOW_STYLE( SS_ICON );
	REG_DEFAULT_WINDOW_STYLE( SS_BLACKRECT );
	REG_DEFAULT_WINDOW_STYLE( SS_GRAYRECT );
	REG_DEFAULT_WINDOW_STYLE( SS_WHITERECT );
	REG_DEFAULT_WINDOW_STYLE( SS_USERITEM );
	REG_DEFAULT_WINDOW_STYLE( SS_SIMPLE );
	REG_DEFAULT_WINDOW_STYLE( SS_LEFTNOWORDWRAP );
#if(WINVER >= 0x0400)
	REG_DEFAULT_WINDOW_STYLE( SS_NOTIFY );
	REG_DEFAULT_WINDOW_STYLE( SS_CENTERIMAGE );
	REG_DEFAULT_WINDOW_STYLE( SS_RIGHTJUST );
	REG_DEFAULT_WINDOW_STYLE( SS_REALSIZEIMAGE );
	REG_DEFAULT_WINDOW_STYLE( SS_SUNKEN );
#endif /* WINVER >= 0x0400 */	            

}

void CRegDefaultData::RegDefaultAlgorithm()
{
	REG_ALGORITHM( IAlgorithm::strVert, CLayoutAlgorithm_Vert )
	REG_ALGORITHM( IAlgorithm::strHori, CLayoutAlgorithm_Hori )
	REG_ALGORITHM( IAlgorithm::strCharacter, CSortAlgorithm_Char )
	REG_ALGORITHM( IAlgorithm::strNormalItem, CLayoutAlgorithm_NormalItem )
	REG_ALGORITHM( IAlgorithm::strAddrGroupItem, CLayoutAlgorithm_AddrGroupItem )
    REG_ALGORITHM( IAlgorithm::strHoriConfLst, CLayoutAlgorithm_HoriConfLst )	
	REG_ALGORITHM( IAlgorithm::strTextOnly, CLayoutAlgorithm_TextOnly )
	REG_ALGORITHM( IAlgorithm::strDoubleColumn, CLayoutAlgorithm_DoubleColumn )
	REG_ALGORITHM( IAlgorithm::strTPadMainMenu, CLayoutAlgorithm_TPadMainMenu )
	REG_ALGORITHM( IAlgorithm::strTextBottom, CLayoutAlgorithm_TextBottom )
	REG_ALGORITHM( IAlgorithm::strWifiItem, CLayoutAlgorithm_WifiItem )
    REG_ALGORITHM( IAlgorithm::strFileManagerItem, CLayoutAlgorithm_FileManagerItem )
	
}

} // namespace AutoUIFactory end
