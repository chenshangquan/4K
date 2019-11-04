#ifndef UIEXLIB_PROPERTY_SET_H
#define UIEXLIB_PROPERTY_SET_H

namespace AutoUIFactory
{		
// 	DECLARE_PROPERTYSET_BEGIN( CBmpWnd , CWndPropertySet )
// 	AddProperty( "Image", "BmpWndImage" );
// 	AddProperty( "MoveStatus", "BmpWndMoveStatus" );
// 	AddProperty( "StrethStatus", "BmpWndStrethStatus" );
// 	AddProperty( "ChangeRgn", "BmpWndChanageRgnStatus" );
// 	DECLARE_PROPERTYSET_END


    DECLARE_PROPERTYSET_BEGIN( CBaseWnd , CWndPropertySet ) 
     
	DECLARE_PROPERTYSET_END


	DECLARE_PROPERTYSET_BEGIN( CTransparentBaseWnd , CWndPropertySet )
    AddProperty( "Image", "TransparentBaseWndImage" );
    AddProperty( "MoveStatus", "TransparentBaseWndMoveStatus" );
	AddProperty( "AutoHideStatus","TransparentBaseWndAutoHideStatus" );
	AddProperty( "TransparentListData","TransparentListData" );
	DECLARE_PROPERTYSET_END
        

// 	DECLARE_PROPERTYSET_BEGIN( CTransparentWnd , CWndPropertySet )
// 	AddProperty( "Image", "TransparentWndImage" );
// 	AddProperty( "MoveStatus", "TransparentWndMoveStatus" );
// 	AddProperty( "AutoHideStatus","TransparentWndAutoHideStatus" );
// 	DECLARE_PROPERTYSET_END
		
	DECLARE_PROPERTYSET_BEGIN( CTransparentList, CTransparentBaseWndPropertySet );
	AddProperty( "ListImage", "TransparentListImage" );
	AddProperty( "Image", "TransparentListSingleImage" );
	AddProperty( "ShowItemAlways", "CTransparentListShowItemStatus" );
	AddProperty( "LayoutAlgorithm", "LayoutAlgorithm" );
	AddProperty( "SortAlgorithm", "SortAlgorithm" );
	AddProperty( "Drag", "TransparentListDrag" );
	AddProperty( "ClickNoSel", "TransparentListClickNoSel" );
	AddProperty( "ClickFocus", "TransparentListClickFocus" );
	AddProperty( "TransparentListSelItem", "TransparentListSelItem" );
    AddProperty( "TransparentListOffset", "TransparentListOffset" );
	AddProperty( "BkgColor", "TransparentListBkgColor" );
	AddProperty( "EveryItemSizeSame", "TransparentListItemSizeSame" );
	AddProperty( "MultiSel", "TransparentListMultiSel" );
	AddProperty( "TransparentListOver", "TransparentListOver" );
	DECLARE_PROPERTYSET_END

    DECLARE_PROPERTYSET_BEGIN( CTransparentHoriList, CTransparentBaseWndPropertySet );
    AddProperty( "TransHoriListOffset", "TransHoriListOffset" );
    AddProperty( "TransHoriListSelItem", "TransHoriListSelItem" );
	DECLARE_PROPERTYSET_END

    DECLARE_PROPERTYSET_BEGIN( CTransparentViewList, CTransparentBaseWndPropertySet );
    AddProperty( "ListImage", "TransparentViewListImage" );
    AddProperty( "ViewListSelItem", "ViewListSelItem" );
    AddProperty( "VertSliderOffset", "ViewListVertSliderOffset" );
    AddProperty( "HoriSliderOffset", "ViewListHoriSliderOffset" );
	AddProperty( "TransparentViewListOver", "TransparentViewListOver" );
	DECLARE_PROPERTYSET_END
				
	DECLARE_PROPERTYSET_BEGIN( CTransparentBtn , CButtonPropertySet )
	AddProperty( "Image", "TransparentBtnImage");
    AddProperty( "TransparentBtnUseTimer", "TransparentBtnUseTimer");
	DECLARE_PROPERTYSET_END		
	
	DECLARE_PROPERTYSET_BEGIN( CTransparentCheckButton, CButtonPropertySet )
	AddProperty( "Image", "TransparentCheckBtnImage");
	AddProperty( "FontSpan", "TransparentCheckBtnFontSpan");
	AddProperty( "FontColor", "TransparentCheckBtnFontColor");
	AddProperty( "FontSize", "TransparentCheckBtnFontSize");
	DECLARE_PROPERTYSET_END

	DECLARE_PROPERTYSET_BEGIN( CTransparentSwitchButton, CButtonPropertySet )
	AddProperty( "Image", "TransparentSwitchBtnImage");
	AddProperty( "SwitchState", "SwitchState" );
	AddProperty( "BindWnd", "SwitchBtnBindWnd" );
	AddProperty( "SwitchBtnBindWnd", "SwitchBtnBindWnd" );
    AddProperty( "ShowText", "SwitchBtnShowText" );
	AddProperty( "FontSize", "TransparentSwitchBtnFontSize");
	DECLARE_PROPERTYSET_END

	DECLARE_PROPERTYSET_BEGIN( CTransparentEdit , CWndPropertySet )
	AddProperty( "Image", "TransparentEditImage");
	AddProperty( "FontSize", "TransparentEditFontSize");
	AddProperty( "FontColor", "TransparentEditFontColor");
	AddProperty( "LimitLength", "TransparentEditLimitLength");
	AddProperty( "FrontLen", "TransparentEditFrontLen");
	AddProperty( "BackLen", "TransparentEditBackLen");
	AddProperty( "ShowIcon", "TransparentEditShowIcon");
	AddProperty( "TipStr", "TransparentEditTipStr");
	AddProperty( "Alignment", "TransparentEditAlign");	
	AddProperty( "SearchEdit", "TransparentEditSearch");
	AddProperty( "IconDeleteText", "TransparentEditDeleteText");
    AddProperty( "DisableImg", "TransparentEditDisableImg"); 
	DECLARE_PROPERTYSET_END

// 	DECLARE_PROPERTYSET_BEGIN( CTransparentIPAddrCtrl , CIPAddressCtrlPropertySet )
// 	AddProperty( "Image", "TransparentIPAddrCtrlImage");
// 	DECLARE_PROPERTYSET_END

	DECLARE_PROPERTYSET_BEGIN( CTransparentStatic , CWndPropertySet )
	AddProperty( "Image", "TransparentStaticImage");
    AddProperty( "TransparentStaticImage", "TransparentStaticImage");
	AddProperty( "FontSize", "TransparentStaticFontSize");
	AddProperty( "FontName", "TransparentStaticFontName");
	AddProperty( "FontColor", "TransparentStaticFontColor");
    AddProperty( "FontStyle", "TransparentStaticFontStyle");
	AddProperty( "Alignment", "TransparentStaticAlign");
	DECLARE_PROPERTYSET_END

    
 
    DECLARE_PROPERTYSET_BEGIN( CTransparentSliderCtrl , CSliderCtrlPropertySet )
    AddProperty( "Image", "TransparentSliderCtrlImage" );
	DECLARE_PROPERTYSET_END

    DECLARE_PROPERTYSET_BEGIN( CTransparentSliderWnd , CWndPropertySet )
    AddProperty( "Image", "CTransparentSliderWndImage" );
    AddProperty( "CSliderCtrlRange", "CTransparentSliderWndRange" ); 
    AddProperty( "CSliderCtrlPos",   "CTransparentSliderWndPos" );
	AddProperty( "CSliderCtrlStyle",   "CTransparentSliderWndStyle" );
    DECLARE_PROPERTYSET_END

	DECLARE_PROPERTYSET_BEGIN( CLetterIndex, CWndPropertySet )
	AddProperty( "Image", "LetterIndexImage" );
	AddProperty( "BindList", "BindList" );
	DECLARE_PROPERTYSET_END

	DECLARE_PROPERTYSET_BEGIN( CTransparentIpEdit, CTransparentEditPropertySet )
	AddProperty( "IpEditData", "IpEditData" );
	DECLARE_PROPERTYSET_END

	DECLARE_PROPERTYSET_BEGIN( CTransparentSlideBlock, CWndPropertySet )
	AddProperty( "Image", "TransparentSlideBlockImage" );
	DECLARE_PROPERTYSET_END

	DECLARE_PROPERTYSET_BEGIN( CTransparentCalendar, CWndPropertySet )
	AddProperty( "Image", "TransparentCalendarImage" );
	DECLARE_PROPERTYSET_END

	DECLARE_PROPERTYSET_BEGIN( CTransparentDragButton, CButtonPropertySet )
	AddProperty( "Image", "TransparentDragBtnImage");
	AddProperty( "DragButtonOnline", "DragButtonOnline");
	AddProperty( "DragButtonSel", "DragButtonSel");
	AddProperty( "DragButtonData", "DragButtonData");
	DECLARE_PROPERTYSET_END

	DECLARE_PROPERTYSET_BEGIN( CTransparentProgress, CWndPropertySet )
	AddProperty( "Image", "TransparentProgressImage" );
	AddProperty( "ProgressPos", "ProgressPos" );
	DECLARE_PROPERTYSET_END

	DECLARE_PROPERTYSET_BEGIN( CVirtualBattery, CWndPropertySet )
	AddProperty( "Image", "VirtualBatteryImage" );
	AddProperty( "BatteryLife", "BatteryLife" );
	DECLARE_PROPERTYSET_END



	/*
	 *CTransparentComboBox属性集 、在构造函数里面添加属性
	 */
	DECLARE_PROPERTYSET_BEGIN( CTransparentComboBox, CWndPropertySet )
	AddProperty( "IsIPStyle", "TransparentComboBoxIPStyle" );
	AddProperty( "TransparentComboBoxListBkColor", "TransparentComboBoxListBkColor" );
	AddProperty( "Image", "TransparentComboBoxImage" );
	AddProperty( "FontSize", "TransparentComboBoxFontSize");
	AddProperty( "EditEdgeHeight", "TransparentComboBoxEditEdgeHeight" );
	AddProperty( "DropListHeight", "TransparentComboBoxDropListHeight" );
	AddProperty( "ComboEditFrontLen", "TransparentComboBoxEditFrontLen" );
	AddProperty( "ComboEditBackLen", "TransparentComboBoxEditBackLen" );
	AddProperty( "ComboShowIcon", "TransparentComboBoxShowIcon" );	
	AddProperty( "ReadOnly", "TransparentComboBoxReadOnly" );
	AddProperty(  /*"ComboText"*/ "TransparentComboBoxText","TransparentComboBoxText");
	AddProperty( "LimitLength", "TransparentComboBoxLimitLength");
	DECLARE_PROPERTYSET_END
        
} // namespace AutoUIFactory end
#endif

