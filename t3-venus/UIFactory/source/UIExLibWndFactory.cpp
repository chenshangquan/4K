// UIExLibWndFactory.cpp: implementation of the UIExLibWndFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "MfcDefaultArgs.h"
#include "UIExLibWndFactory.h"
#include "PropertyHelp.h"

//lint -e1018    屏蔽pclint错误
//lint -e84      

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AutoUIFactory
{
    Window* CBaseWndFactory::Create( IArgs& iArgs )
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
            DWORD dwExStyle = 0;
            if ( CWindowDefaultStyleMap::StringToStyle( args.m_strExStyle, dwExStyle ) == false )
            {
                dwExStyle = 0;
            }
            CBaseWnd* pWnd = new CBaseWnd( args.m_strName.c_str(),IWindowFactory::m_rcDefaultRect, 
                args.m_pParent,  dwStyle, dwExStyle ,GETUNIQID );
            
 
            return pWnd;
        }
        catch (bad_cast)
        {
            return 0;
        }
	}


/*
	Window* CBmpWndFactory::Create( IArgs& iArgs )
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
            DWORD dwExStyle = 0;
            if ( CWindowDefaultStyleMap::StringToStyle( args.m_strExStyle, dwExStyle ) == false )
            {
                dwExStyle = 0;
	    	}
			CBmpWnd* pWnd = new CBmpWnd( args.m_strName.c_str(), "", IWindowFactory::m_rcDefaultRect, 
				args.m_pParent, GETUNIQID, dwStyle, dwExStyle );
			
#ifdef _DEBUG
			if ( pWnd != NULL )
			{
				pWnd->SetMoveStatus(TRUE);
			} 
#endif 
			return pWnd;
		}
		catch (bad_cast)
		{
			return 0;
		}
	}

*/
	Window* CTransparentBaseWndFactory::Create( IArgs& iArgs )
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
            DWORD dwExStyle = 0;
            if ( CWindowDefaultStyleMap::StringToStyle( args.m_strExStyle, dwExStyle ) == false )
            {
                dwExStyle = 0;
			}
			CTransparentBaseWnd* pWnd = new CTransparentBaseWnd( IWindowFactory::m_rcDefaultRect, args.m_pParent, 
				        dwStyle, args.m_strName.c_str(),GETUNIQID );

		 
			
#ifdef _DEBUG
			if ( pWnd != NULL )
			{
				pWnd->SetMoveStatus(TRUE);
			} 
#endif 
			return pWnd;
		}
		catch (bad_cast)
		{
			return 0;
		}
	}

/*
Window* CTransparentWndFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
		DWORD dwExStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strExStyle, dwExStyle ) == false )
		{
			dwExStyle = 0;
		}
#ifdef _DEBUG
 		dwStyle = dwStyle | m_dwDebugStyle; 
#endif
		CTransparentWnd* pWnd = new CTransparentWnd( IWindowFactory::m_rcDefaultRect, args.m_pParent, dwStyle, "",GETUNIQID, dwExStyle );
	//	CTransparentWnd* pWnd = new CTransparentWnd( CRect(100,100,1000,1000), 0, WS_VISIBLE|WS_POPUP, "1.png", 0, 0, 50, TRUE );
#ifdef _DEBUG 
        if ( pWnd != NULL )
        {
            pWnd->SetMoveStatus(TRUE);
        }
		TRACE( "\n[CTransparentWndFactory::Create] %p = %s \n", pWnd, args.m_strName.c_str() );
#endif

		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}*/

Window* CTransparentEditFactory::Create( IArgs& iArgs )
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
		CTransparentEdit* pWnd = new CTransparentEdit();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent,GETUNIQID );

        //设置Edit默认字体信息
        TFontInfo tFontInfo = CSystem::GetSingletonPtr()->GetEditFontInfo();
        if ( !tFontInfo.strFontName.empty() )
        {
            pWnd->SetFont( tFontInfo.nFontSize, tFontInfo.strFontName.c_str() );

            if ( !tFontInfo.strNormalColor.empty() )
            {
                COLORREF col = CPropertyHelp::stringToColor(tFontInfo.strNormalColor);
                Color colorNormal = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
                Color colorFocus = colorNormal;
                if ( !tFontInfo.strFocusColor.empty() )
                {
                    COLORREF col = CPropertyHelp::stringToColor(tFontInfo.strFocusColor);
                    colorFocus = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
                }
                pWnd->SetTextColor( colorNormal, colorFocus );
            }

            if ( !tFontInfo.strDisableColor.empty() )
            {
                COLORREF col = CPropertyHelp::stringToColor(tFontInfo.strDisableColor);
                Color colorDis = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
                pWnd->SetDisableColor( colorDis );
            }
        }
        if ( !tFontInfo.strDisableImg.empty() )
        {
            bool bImg = CPropertyHelp::stringToBool( tFontInfo.strDisableImg );
            pWnd->SetDisableImg( bImg );
        }

		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CTransparentBtnFactory::Create( IArgs& iArgs )
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
		CTransparentBtn* pWnd = new CTransparentBtn();
        int nID = GETUNIQID;
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent,nID );

        if ( dwStyle & BS_DEFPUSHBUTTON )
        {   
            try 
            {   
                if ( CDialog*pDlg =  dynamic_cast<CDialog*>(args.m_pParent) )
                {
                    pDlg->SetDefID(nID);
                }
            } 
            catch( ... )
            {

            }
        }

		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CTransparentCheckButtonFactory::Create( IArgs& iArgs )
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
		CTransparentCheckButton* pWnd = new CTransparentCheckButton();
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent,GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CTransparentSwitchButtonFactory::Create( IArgs& iArgs )
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
		CTransparentSwitchButton* pWnd = new CTransparentSwitchButton();
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent,GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CTransparentListFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
        DWORD dwExStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
        if ( CWindowDefaultStyleMap::StringToStyle( args.m_strExStyle, dwExStyle ) == false )
        {
            dwExStyle = 0;
        }

// #ifdef _DEBUG
// 		dwStyle = dwStyle | m_dwDebugStyle; 
// #endif
		CTransparentList* pWnd = new CTransparentList( args.m_strName.c_str(), IWindowFactory::m_rcDefaultRect, args.m_pParent, "", GETUNIQID, dwStyle, dwExStyle );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CTransparentHoriListFactory::Create( IArgs& iArgs )
{
    try
    {
        Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
        DWORD dwStyle = 0;
        DWORD dwExStyle = 0;
        if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
        {
            dwStyle = IWindowFactory::m_dwDefaultStyle;
        }
        if ( CWindowDefaultStyleMap::StringToStyle( args.m_strExStyle, dwExStyle ) == false )
        {
            dwExStyle = 0;
        }
// #ifdef _DEBUG
//         dwStyle = dwStyle | m_dwDebugStyle; 
// #endif
        CTransparentHoriList* pWnd = new CTransparentHoriList( args.m_strName.c_str(), IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID, dwStyle, dwExStyle );
        return pWnd;
    }
    catch (bad_cast)
    {
        return 0;
    }
}

Window* CTransparentViewListFactory::Create( IArgs& iArgs )
{
    try
    {
        Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
        DWORD dwStyle = 0;
        DWORD dwExStyle = 0;
        if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
        {
            dwStyle = IWindowFactory::m_dwDefaultStyle;
        }
        if ( CWindowDefaultStyleMap::StringToStyle( args.m_strExStyle, dwExStyle ) == false )
        {
            dwExStyle = 0;
        }

        CTransparentViewList* pWnd = new CTransparentViewList( args.m_strName.c_str(), IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID, dwStyle, dwExStyle );
        return pWnd;
    }
    catch (bad_cast)
    {
        return 0;
    }
}

/*
Window* CTransparentIPAddrCtrlFactory::Create( IArgs& iArgs )
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
		CTransparentIPAddrCtrl* pWnd = new CTransparentIPAddrCtrl();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}*/

Window* CTransparentStaticFactory::Create( IArgs& iArgs )
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
        CTransparentStatic* pWnd = new CTransparentStatic();
        pWnd->Create(args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent );

        //设置Static默认字体信息
        TFontInfo tFontInfo = CSystem::GetSingletonPtr()->GetStaticFontInfo();
        if ( !tFontInfo.strFontName.empty() )
        {
            pWnd->SetFont( tFontInfo.nFontSize, tFontInfo.strFontName.c_str() );
            
            if ( !tFontInfo.strNormalColor.empty() )
            {
                COLORREF col = CPropertyHelp::stringToColor(tFontInfo.strNormalColor);
                Color colorNormal = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );               
                pWnd->SetTextColor( colorNormal );
            }
            
            if ( !tFontInfo.strDisableColor.empty() )
            {
                COLORREF col = CPropertyHelp::stringToColor(tFontInfo.strDisableColor);
                Color colorDis = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
                pWnd->SetDisableColor( colorDis );
            }
        }
        return pWnd;
    }
    catch (bad_cast)
    {
        return 0;
    }
 
} 
Window* CTransparentSliderCtrlFactory::Create( IArgs& iArgs )
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
        CTransparentSliderCtrl* pWnd = new CTransparentSliderCtrl();
        pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent,GETUNIQID );
        return pWnd;
    }
    catch (bad_cast)
    {
        return 0;
    }
}

Window* CLetterIndexFactory::Create( IArgs& iArgs )
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
		CLetterIndex* pWnd = new CLetterIndex( args.m_strName.c_str(), "", IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID, dwStyle );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CTransparentIpEditFactory::Create( IArgs& iArgs )
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
		CTransparentIpEdit* pWnd = new CTransparentIpEdit();
		pWnd->Create( dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent,GETUNIQID );

        //设置Edit默认字体信息
        TFontInfo tFontInfo = CSystem::GetSingletonPtr()->GetEditFontInfo();
        if ( !tFontInfo.strFontName.empty() )
        {
            pWnd->SetFont( tFontInfo.nFontSize, tFontInfo.strFontName.c_str() );
            
            if ( !tFontInfo.strNormalColor.empty() )
            {
                COLORREF col = CPropertyHelp::stringToColor(tFontInfo.strNormalColor);
                Color colorNormal = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
                Color colorFocus = colorNormal;
                if ( !tFontInfo.strFocusColor.empty() )
                {
                    COLORREF col = CPropertyHelp::stringToColor(tFontInfo.strFocusColor);
                    colorFocus = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
                }
                pWnd->SetTextColor( colorNormal, colorFocus );
            }
            
            if ( !tFontInfo.strDisableColor.empty() )
            {
                COLORREF col = CPropertyHelp::stringToColor(tFontInfo.strDisableColor);
                Color colorDis = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
                pWnd->SetDisableColor( colorDis );
            }
        }
        if ( !tFontInfo.strDisableImg.empty() )
        {
            bool bImg = CPropertyHelp::stringToBool( tFontInfo.strDisableImg );
            pWnd->SetDisableImg( bImg );
        }
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CTransparentSlideBlockFactory::Create( IArgs& iArgs )
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
		CTransparentSlideBlock* pWnd = new CTransparentSlideBlock( args.m_strName.c_str(), "", IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID, dwStyle );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}


Window* CTransparentSliderWndFactory::Create( IArgs& iArgs )
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
        CTransparentSliderWnd* pWnd = new CTransparentSliderWnd( args.m_strName.c_str(), "", IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID, dwStyle );
        return pWnd;
    }
    catch (bad_cast)
    {
        return 0;
    }
}

Window* CTransparentCalendarFactory::Create( IArgs& iArgs )
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
		CTransparentCalendar* pWnd = new CTransparentCalendar( args.m_strName.c_str(), "", IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID, dwStyle );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CTransparentDragButtonFactory::Create( IArgs& iArgs )
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
		CTransparentDragButton* pWnd = new CTransparentDragButton();
		pWnd->Create( args.m_strName.c_str(), dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent,GETUNIQID );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CTransparentProgressFactory::Create( IArgs& iArgs )
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
		CTransparentProgress* pWnd = new CTransparentProgress( args.m_strName.c_str(), "", IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID, dwStyle );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CVirtualBatteryFactory::Create( IArgs& iArgs )
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
		CVirtualBattery* pWnd = new CVirtualBattery( args.m_strName.c_str(), "", IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID, dwStyle );
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

Window* CTransparentComboBoxFactory::Create( IArgs& iArgs )
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
		CTransparentComboBox* pWnd = new CTransparentComboBox( args.m_strName.c_str(), 
 			args.m_pParent, IWindowFactory::m_rcDefaultRect, GETUNIQID, dwStyle );

		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}


	return NULL;
}


}