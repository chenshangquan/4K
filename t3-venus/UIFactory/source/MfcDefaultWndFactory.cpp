// MfcDefaultWndFactory.cpp: implementation of the MfcDefaultWndFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "MfcDefaultWndFactory.h"
#include "MfcDefaultArgs.h"
#include "PropertyHelp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

Window* CTransparentDlgFactory::Create( IArgs& iArgs )
{
	try 
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		CTransparentDlg* pDlg = new CTransparentDlg();
		
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
         
		DWORD dwExStyle = 0;
		CWindowDefaultStyleMap::StringToStyle( args.m_strExStyle, dwExStyle );
	 
		BOOL bModalWnd = FALSE;
		bModalWnd = CPropertyHelp::stringToBool( args.m_strModal );

#ifdef _DEBUG
		dwStyle = dwStyle | m_dwDebugStyle;
#endif

		pDlg->Create( args.m_strName.c_str(), IWindowFactory::m_rcDefaultRect, dwStyle, dwExStyle, args.m_pParent, bModalWnd );

#ifdef _DEBUG
        if ( pDlg != NULL && (dwStyle & WS_POPUP) )
        {
            pDlg->SetMoveStatus(TRUE);
        } 

        TRACE( "\n[CTransparentDlg::Create] ( wnd %p, handle %p ) = %s \n", pDlg, pDlg->GetSafeHwnd(), args.m_strName.c_str() );
#else
		CString str = "";
		str.Format("\r\n[CTransparentDlgFactory::Create] name=%s  hwnd=%x \r\n",args.m_strName.c_str(),pDlg->GetSafeHwnd());
		LOGEVENT(str);

#endif     

	
		return pDlg;
	}
	catch( bad_cast )
	{
		return 0;
	}	
}

Window* CButtonFactory::Create( IArgs& iArgs )
{
	try 
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		CButton* pBtn = new CButton();

		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
#ifdef _DEBUG
		dwStyle = dwStyle | m_dwDebugStyle;
#endif

		pBtn->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pBtn;
	}
	catch( bad_cast )
	{
		return 0;
	}	
}

Window* CListFactory::Create( IArgs& iArgs )
{
	try 
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		CListBox* pList = new CListBox();

		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
		
#ifdef _DEBUG
		dwStyle = dwStyle | m_dwDebugStyle;
#endif

		pList->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pList;
	}
	catch( bad_cast )
	{
		return 0;
	}	
}

Window* CEditFactory::Create( IArgs& iArgs )
{
	try 
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		CEdit* pEdit = new CEdit();

		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
		
#ifdef _DEBUG
		dwStyle = dwStyle | m_dwDebugStyle;
#endif

		pEdit->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pEdit;
	}
	catch( bad_cast )
	{
		return 0;
	}	
}

Window* CStaticFactory::Create( IArgs& iArgs )
{	
	try 
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		CStatic* pStatic = new CStatic();

		
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
		
#ifdef _DEBUG
		dwStyle = dwStyle | m_dwDebugStyle;
#endif
		

		pStatic->Create( args.m_strName.c_str(), dwStyle,IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pStatic;
	}
	catch( bad_cast )
	{
		return 0;
	}
}



Window* CIPAddressCtrlFactory::Create( IArgs& iArgs )
{
	try 
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		CIPAddressCtrl* pIP = new CIPAddressCtrl();
		
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
		
#ifdef _DEBUG
		dwStyle = dwStyle | m_dwDebugStyle;
#endif
		
		pIP->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pIP;
	}
	catch( bad_cast )
	{
		return 0;
	}	
}


Window* CSliderCtrlFactory::Create( IArgs& iArgs )
{
    try 
    {
        Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
        CSliderCtrl* pSlider = new CSliderCtrl();
        
        DWORD dwStyle = 0;
        if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
        {
            dwStyle = IWindowFactory::m_dwDefaultStyle;
        }
        
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle;
#endif
        
        pSlider->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
        return pSlider;
    }
    catch( bad_cast )
    {
        return 0;
    }	
}

} // namespace AutoUIFactory end