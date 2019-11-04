#include "stdafx.h"
#include "BaseWindowWnd.h"

#if !defined(UNDER_CE) && defined(_DEBUG)
#define new   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#if USE(ZIP_SKIN)
static const TCHAR* const g_kResourceSkinZipFileName = L"";
#endif

CBaseWindowWnd::CBaseWindowWnd()
{
}

CBaseWindowWnd::~CBaseWindowWnd()
{
}

UINT CBaseWindowWnd::GetClassStyle() const
{
	return CS_DBLCLKS;
}

CControlUI* CBaseWindowWnd::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

void CBaseWindowWnd::OnFinalMessage(HWND /*hWnd*/)
{
	m_cPaintManager.RemovePreMessageFilter(this);
	m_cPaintManager.RemoveNotifier(this);
	m_cPaintManager.ReapObjects(m_cPaintManager.GetRoot());
}

void CBaseWindowWnd::Init()
{
}

LRESULT CBaseWindowWnd::OnClose( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;
	return 0;
}

LRESULT CBaseWindowWnd::OnDestroy( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;
	return 0;
}

#if defined(WIN32) && !defined(UNDER_CE)
LRESULT CBaseWindowWnd::OnNcActivate( UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled )
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CBaseWindowWnd::OnNcCalcSize( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return 0;
}

LRESULT CBaseWindowWnd::OnNcPaint( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return 0;
}

LRESULT CBaseWindowWnd::OnNcHitTest( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect( *this, &rcClient );

	if( !::IsZoomed(*this) ) 
	{
		RECT rcSizeBox = m_cPaintManager.GetSizeBox();
		if( pt.y < rcClient.top + rcSizeBox.top ) 
		{
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
			return HTTOP;
		}
		else if( pt.y > rcClient.bottom - rcSizeBox.bottom ) 
		{
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
		if( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
	}

	RECT rcCaption = m_cPaintManager.GetCaptionRect();
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) 
	{
			CControlUI* pControl = static_cast<CControlUI*>(m_cPaintManager.FindControl(pt));
			if( pControl && _tcsicmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
				_tcsicmp(pControl->GetClass(), _T("OptionUI")) != 0 /*&&
				_tcsicmp(pControl->GetClass(), _T("TextUI")) != 0 */)
				return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT CBaseWindowWnd::OnGetMinMaxInfo( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-rcWork.left, -rcWork.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
	lpMMI->ptMaxPosition.x	= rcWork.left;
	lpMMI->ptMaxPosition.y	= rcWork.top;
	lpMMI->ptMaxSize.x		= rcWork.right;
	lpMMI->ptMaxSize.y		= rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

LRESULT CBaseWindowWnd::OnMouseWheel( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;
	return 0; 
}
#endif


LRESULT CBaseWindowWnd::OnSetFocus( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;
	return 0;
}

LRESULT CBaseWindowWnd::OnLButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;
	return 0;
}

LRESULT CBaseWindowWnd::OnMouseMove( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;
	return 0;
}

LRESULT CBaseWindowWnd::OnLButtonUp( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;
	return 0;
}

LRESULT CBaseWindowWnd::OnKeyDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;
	return 0;
}

LRESULT CBaseWindowWnd::OnKillFocus( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;
	return 0;
}

LRESULT CBaseWindowWnd::OnSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	SIZE szRoundCorner = m_cPaintManager.GetRoundCorner();
#if defined(WIN32) && !defined(UNDER_CE)
	if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) 
	{
		CRect rcWnd;
		::GetWindowRect( *this, &rcWnd );
		rcWnd.Offset( -rcWnd.left, -rcWnd.top );
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn( rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy );
		::SetWindowRgn( *this, hRgn, TRUE );
		::DeleteObject(hRgn);
	}
#endif
	bHandled = FALSE;
	return 0;
}


LRESULT CBaseWindowWnd::OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	if (wParam == SC_CLOSE)
	{
		bHandled = TRUE;
		return 0;
	}

#if defined(WIN32) && !defined(UNDER_CE)
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage( uMsg, wParam, lParam );
	if( ::IsZoomed(*this) != bZoomed )
	{
	}
#else
	LRESULT lRes = CWindowWnd::HandleMessage( uMsg, wParam, lParam );
#endif
	return lRes;
}

const TCHAR* CBaseWindowWnd::GetSkinFolder()
{
	TCHAR chPath[MAX_PATH] = {0};
	wcscat( chPath, CPaintManagerUI::GetInstancePath() );
	wcscat( chPath , _T("skin\\") );
	return chPath;
}

LRESULT CBaseWindowWnd::OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	LONG styleValue = ::GetWindowLong( *this, GWL_STYLE );
	styleValue &= ~WS_CAPTION;
	::SetWindowLong( *this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
	RECT rcClient;
	::GetClientRect( *this, &rcClient );
	::SetWindowPos( *this, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, \
		rcClient.bottom - rcClient.top, SWP_FRAMECHANGED );

	m_cPaintManager.Init(m_hWnd);
	m_cPaintManager.AddPreMessageFilter(this);

	CDialogBuilder builder;

//  #if USE(ZIP_SKIN)
//  
//  #if defined(UNDER_CE)
//  	static bool resource_unzipped = false;
//  	if (!resource_unzipped)
//  	{
//  		resource_unzipped = true;
//  		paint_manager_.SetResourceZip(kResourceSkinZipFileName);
//  		paint_manager_.UnzipResource();
//  		paint_manager_.SetResourceZip(_T(""));
//  	}
//  	tString tstrSkin = paint_manager_.GetResourcePath();
//  	tstrSkin += GetSkinFile();
//  #else
//  	paint_manager_.SetResourceZip(kResourceSkinZipFileName);
//  	tString tstrSkin = GetSkinFile();
//  #endif
//  
//   #else
 	tString tstrSkin;// = paint_manager_.GetResourcePath();     //Ïà¶ÔÂ·¾¶¡°main.xml¡±
 	tstrSkin += GetSkinFile();
// #endif

 	CControlUI* pRoot = builder.Create( tstrSkin.c_str(), (UINT)0, this, &m_cPaintManager );
 	m_cPaintManager.AttachDialog(pRoot);
 	m_cPaintManager.AddNotifier(this);

	Init();

	return 0;
}

LRESULT CBaseWindowWnd::HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return 0;
}

LRESULT CBaseWindowWnd::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg)
	{
	case WM_CREATE:			lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:			lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:		lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
#if defined(WIN32) && !defined(UNDER_CE)
	case WM_NCACTIVATE:		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:		lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO:	lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_MOUSEWHEEL:		lRes = OnMouseWheel(uMsg, wParam, lParam, bHandled); break;
#endif
	case WM_SIZE:			lRes = OnSize(uMsg, wParam, lParam, bHandled); break;	
	case WM_SYSCOMMAND:		lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	case WM_KEYDOWN:		lRes = OnKeyDown(uMsg, wParam, lParam, bHandled); break;
	case WM_KILLFOCUS:		lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); break;
	case WM_SETFOCUS:		lRes = OnSetFocus(uMsg, wParam, lParam, bHandled); break;
	case WM_LBUTTONUP:		lRes = OnLButtonUp(uMsg, wParam, lParam, bHandled); break;
	case WM_LBUTTONDOWN:	lRes = OnLButtonDown(uMsg, wParam, lParam, bHandled); break;
	case WM_MOUSEMOVE:		lRes = OnMouseMove(uMsg, wParam, lParam, bHandled); break;
	default:				bHandled = FALSE; break;
	}
	if (bHandled) return lRes;

	lRes = HandleCustomMessage( uMsg, wParam, lParam, bHandled );
	if (bHandled) return lRes;

	if ( m_cPaintManager.MessageHandler( uMsg, wParam, lParam, lRes ) ) return lRes;
	return CWindowWnd::HandleMessage( uMsg, wParam, lParam);
}

LRESULT CBaseWindowWnd::MessageHandler( UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& /*bHandled*/ )
{
	if (uMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return ResponseDefaultKeyEvent(wParam);
		default:
			break;
		}
	}
	return FALSE;
}

LRESULT CBaseWindowWnd::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		Close();
		return TRUE;
	}

	return FALSE;
}