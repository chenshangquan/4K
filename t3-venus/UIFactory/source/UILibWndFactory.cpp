// UILibWndFactory.cpp: implementation of the UILibWndFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "UILibWndFactory.h"
#include "MfcDefaultArgs.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AutoUIFactory
{

Window* CFlatButtonFactory::Create( IArgs& iArgs )
{
	try 
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		
		CFlatButton* pWnd = new CFlatButton();	
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch( bad_cast )
	{
		return 0;
	}
}

Window* CSkinScrollFactory::Create( IArgs& iArgs )
{
	try
	{	
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinScroll* pWnd = new CSkinScroll();
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch( bad_cast )
	{
		return 0;
	}
}
Window* CSkinHeaderCtrlFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinHeaderCtrl* pWnd = new CSkinHeaderCtrl();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch( bad_cast )
	{
		return 0;
	}
}

Window* CFlatDDButtonFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CFlatDDButton* pWnd = new CFlatDDButton();
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}	
}
Window* CCheckButtonFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CCheckButton* pWnd = new CCheckButton();
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CSkinFrameFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinFrame* pWnd = new CSkinFrame();
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CSkinListCtrlFactory::Create( IArgs& iArgs )
{	
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinListCtrl* pWnd = new CSkinListCtrl();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CSkinDDListCtrlFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinDDListCtrl* pWnd = new CSkinDDListCtrl();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CSkinSliderFactory::Create( IArgs& iArgs )
{	
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinSlider* pWnd = new CSkinSlider();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}
Window* CSkinEditFactory::Create( IArgs& iArgs )
{	
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinEdit* pWnd = new CSkinEdit();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}
Window* CSkinIPCtrlFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinIPCtrl* pWnd = new CSkinIPCtrl();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CStaticExFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CStaticEx* pWnd = new CStaticEx();
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CSkinComboBoxFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinComboBox* pWnd = new CSkinComboBox();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}
Window* CBMPDlgFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);		
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CBMPDlg* pWnd = new CBMPDlg();
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CSkinSpinCtrlFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinSpinCtrl* pWnd = new CSkinSpinCtrl();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CSkinGroupFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinGroup* pWnd = new CSkinGroup();
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CTextButton30Factory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CTextButton30* pWnd = new CTextButton30();
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CSkinTabFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinTab* pWnd = new CSkinTab();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}
Window* CSkinSheetFactory::Create( IArgs& iArgs )
{	
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		Window* pWnd = 0;//new CSkinSheet();
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}
Window* CSkinPageFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinPage* pWnd = new CSkinPage();
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CSkinCheckListFactory::Create( IArgs& iArgs )
{	
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinCheckList* pWnd = new CSkinCheckList();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CColourPopupFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);	
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CColourPopup* pWnd = new CColourPopup();
	//	pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CColorSelCtrlFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CColorSelCtrl* pWnd = new CColorSelCtrl();
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CSkinDateTimeFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CSkinDateTime* pWnd = new CSkinDateTime();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

} // namespace AutoUIFactory end