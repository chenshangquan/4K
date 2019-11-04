// MfcDefaultWndPropertySet.h: interface for the MfcDefaultWndPropertySet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCDEFAULTWNDPROPERTYSET_H__296760B5_4C36_434F_9543_347830BCA392__INCLUDED_)
#define AFX_MFCDEFAULTWNDPROPERTYSET_H__296760B5_4C36_434F_9543_347830BCA392__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "PropertySet.h"

/*
 * @defgroup Mfc默认控件的属性集 \n
	如果添加了新控件、并且需要继承wnd的一些默认属性，请继承与CWndPropertySet类 \n
	如果这个新空间有新的属性，请在构造函数里面添加	\n
	在这个文件里面添加了属性集 需要在CRegDefaultData里面注册

 * @author  牟兴茂
 * @version 1.0
 * @date  2011/05/31
 * @{
 */
namespace AutoUIFactory
{
/*
 *	默认窗口属性集 、在构造函数里面添加属性
 */
DECLARE_PROPERTYSET_BEGIN( CWnd, IPropertySet )
	AddProperty( "WindowPos", "WindowPos" );
	AddProperty( "WindowCaption", "WindowCaption" );
	AddProperty( "WindowSize", "WindowSize" );
	AddProperty( "WindowVisible", "WindowVisible" );
	AddProperty( "WindowEnable", "WindowEnable" );
	AddProperty( "WindowOwer","WindowOwer" );
DECLARE_PROPERTYSET_END


/*
 *transparentDlgBase属性集 、在构造函数里面添加属性
 */
DECLARE_PROPERTYSET_BEGIN( CTransparentDlgBase, CWndPropertySet )
	AddProperty( "Image", "TransparentDlgBaseImage" ); 
	AddProperty( "MoveStatus", "TransparentDlgBaseMoveStatus" );
	AddProperty( "AutoHideStatus","TransparentDlgBaseAutoHideStatus" ); 
	AddProperty( "BkStretch","TransparentDlgBaseBkStretch" ); 
DECLARE_PROPERTYSET_END



//声明属性集
DECLARE_PROPERTYSET_BEGIN( CTransparentDlg, CTransparentDlgBasePropertySet )  
DECLARE_PROPERTYSET_END 
 
 


/*
 *	默认按钮属性集 、继承了wnd的属性
 */
DECLARE_PROPERTYSET_BEGIN( CButton, CWndPropertySet )
AddProperty( "CButtonCheckState", "CButtonCheckState" ); 
DECLARE_PROPERTYSET_END
/*
 *	默认编辑框属性集 、继承了wnd的属性
 */
DECLARE_PROPERTYSET_BEGIN( CEdit, CWndPropertySet )
 // 如果有新增属性请到这里添加
DECLARE_PROPERTYSET_END

/*
 *	默认静态控件属性集 、继承了wnd的属性
 */
DECLARE_PROPERTYSET_BEGIN( CStatic, CWndPropertySet )
// 如果有新增属性请到这里添加
DECLARE_PROPERTYSET_END
/*
 *	默认列表属性集 、继承了wnd的属性
 */
DECLARE_PROPERTYSET_BEGIN( CList, CWndPropertySet )
 // 如果有新增属性请到这里添加
DECLARE_PROPERTYSET_END


/*
 *	默认IP控件属性集 、继承了wnd的属性
 */
DECLARE_PROPERTYSET_BEGIN( CIPAddressCtrl, CWndPropertySet ) 
 AddProperty( "CIPAddressCtrlData", "CIPAddressCtrlData" );
DECLARE_PROPERTYSET_END


/*
 *	默认CSliderCtrl控件属性集 、继承了wnd的属性
 */
DECLARE_PROPERTYSET_BEGIN( CSliderCtrl, CWndPropertySet ) 
 AddProperty( "CSliderCtrlRange", "CSliderCtrlRange" );
 AddProperty( "CSliderCtrlPos", "CSliderCtrlPos" );
DECLARE_PROPERTYSET_END


} // namespace AutoUIFactory end

/** @} */ 

#endif // !defined(AFX_MFCDEFAULTWNDPROPERTYSET_H__296760B5_4C36_434F_9543_347830BCA392__INCLUDED_)
