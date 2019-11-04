#include "StdAfx.h"
#include "DUIDialog.h"
 
 
namespace DuiLib { 

CDUIDialog::CDUIDialog( LPCTSTR szLayXml ):m_strLayFile(szLayXml)
{
	 m_bAutoHide = FALSE;
	 m_bContinueModal = FALSE;
	 m_nModalResult = 0;
}


CDUIDialog::~CDUIDialog(void)
{
}

void CDUIDialog::OnFinalMessage( HWND hWnd )
{
	//m_paintMng.RemoveNotifier( this );
	m_paintMng.RemoveMessageFilter( this );
	m_paintMng.RemovePreMessageFilter( this );
	
}

UINT CDUIDialog::GetClassStyle() const
{
	return CS_DBLCLKS;
}

 

CControlUI* CDUIDialog::CreateControl( LPCTSTR pstrClass )
{

	return NULL;
}



LRESULT CDUIDialog::OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_OK;
}

LRESULT CDUIDialog::OnDestroy( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_OK;
}

//添加失去焦点就隐藏功能
LRESULT CDUIDialog::OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = false;

	
	return S_OK;
}

LRESULT CDUIDialog::OnNcActivate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE; 
}

LRESULT CDUIDialog::OnNcCalcSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_OK;
}

LRESULT CDUIDialog::OnNcPaint( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_OK;
}

BOOL CDUIDialog::CanBeMoved( CControlUI* pControl )
{
	if ( NULL == pControl )
	{
		return FALSE;
	}

	CControlUI* pParent = pControl->GetParent();
	BOOL bMove = FALSE;
	if ( _tcsicmp( pControl->GetClass(), _T("HorizontalLayoutUI") ) == 0 
		|| _tcsicmp( pControl->GetClass(), _T("VerticalLayoutUI") ) == 0 
		|| _tcsicmp( pControl->GetClass(), _T("ControlUI") ) == 0 )
	{
		bMove = TRUE;

		while( 1 )
		{
			if ( NULL != pParent )
			{
				if ( _tcsicmp( pParent->GetClass(), _T("CommonListUI")) == 0 )
				{
					bMove = FALSE;
					break;
				}
			}
			else
			{
				break;
			}

			pParent = pParent->GetParent();
		}
	}

	return bMove;
}

LRESULT CDUIDialog::OnNcHitTest( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if( !::IsZoomed(*this) ) {
		RECT rcSizeBox = m_paintMng.GetSizeBox();
		if( pt.y < rcClient.top + rcSizeBox.top ) {
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
			return HTTOP;
		}
		else if( pt.y > rcClient.bottom - rcSizeBox.bottom ) {
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
		if( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
	}

	RECT rcCaption = m_paintMng.GetCaptionRect();
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) 
	{
			CControlUI* pControl = static_cast<CControlUI*>(m_paintMng.FindControl(pt));

			if ( CanBeMoved(pControl) )
			{
				return HTCAPTION;
			}

// 			if( pControl && _tcsicmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
// 				_tcsicmp(pControl->GetClass(), _T("OptionUI")) != 0 /*&&
// 				_tcsicmp(pControl->GetClass(), _T("TextUI")) != 0 */)
// 				return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT CDUIDialog::OnGetMinMaxInfo( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	DuiLib::CRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-rcWork.left, -rcWork.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
	lpMMI->ptMaxPosition.x	= rcWork.left;
	lpMMI->ptMaxPosition.y	= rcWork.top;
	lpMMI->ptMaxSize.x		= rcWork.right;
	lpMMI->ptMaxSize.y		= rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

LRESULT CDUIDialog::OnMouseWheel( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_OK;
}

LRESULT CDUIDialog::OnSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	
	SIZE szRoundCorner = m_paintMng.GetRoundCorner(); 
	if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {
		DuiLib::CRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}
 
	bHandled = FALSE;
	return 0;
}

LRESULT CDUIDialog::OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	if (wParam == SC_CLOSE){
		bHandled = TRUE;
		return 0;
	}
 
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if( ::IsZoomed(*this) != bZoomed ){
	}
	
	return lRes;
}

LRESULT CDUIDialog::OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN); 
	m_paintMng.Init(m_hWnd);
	m_paintMng.AddPreMessageFilter(this);
	m_paintMng.AddMessageFilter( this );

	CDialogBuilder builder; 
	CControlUI* pRoot = builder.Create(  (LPCTSTR)m_strLayFile  , (UINT)0, this, &m_paintMng);
	m_paintMng.AttachDialog(pRoot);
	//m_paintMng.AddNotifier(this); 
 
	return 0;
}

LRESULT CDUIDialog::OnKeyDown( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_OK;
}

LRESULT CDUIDialog::OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_OK;
}

LRESULT CDUIDialog::OnSetFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_OK;
}

LRESULT CDUIDialog::OnLButtonDown( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_OK;
}

LRESULT CDUIDialog::OnLButtonUp( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_OK;
}

LRESULT CDUIDialog::OnMouseMove( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_FALSE;
}

// void CDUIDialog::Notify(TNotifyUI& msg)
// {
// 
// }

//preTranslateMessage()
LRESULT CDUIDialog::MessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled )
{
	if (uMsg == WM_KEYDOWN)
	{
		switch( wParam )
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return FALSE; 
		}
	}

	return FALSE;
}


//winPorc
LRESULT CDUIDialog::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{ 
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg)
	{
	case WM_CREATE:			lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:			lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:		lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
 
	case WM_NCACTIVATE:		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:		lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO:	lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_MOUSEWHEEL:		lRes = OnMouseWheel(uMsg, wParam, lParam, bHandled); break;
 
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

	lRes = HandleCustomMessage(uMsg, wParam, lParam, bHandled);
	if (bHandled) return lRes;

	if (m_paintMng.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CDUIDialog::HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;
	return S_FALSE;
}
 
 

BOOL CDUIDialog::DoCase( const LPCTSTR szCaseName )
{
	return m_paintMng.DoCase( szCaseName );
}

int CDUIDialog::DoModal()
{
	if( !::IsWindow(m_hWnd) )
	{
		OutputDebugString(_T("\n[CDUIDialog::DoModal] fail:窗口句柄为空\n"));
		return -1;
	}

	if( m_bContinueModal )
	{
		OutputDebugString(_T("\n[CDUIDialog::DoModal] fail:当前正在modalloop中\n"));
		return -1;
	} 

	m_bContinueModal = TRUE; 

	HWND hLastActive = NULL;
	HWND hWndParent = GetWindowOwner(m_hWnd);
	 
	if( NULL != hWndParent )
	{
		::EnableWindow(hWndParent, FALSE); 
	}
	else
	{  
		HWND hTop =  GetForegroundWindow(); 
		hLastActive  = GetLastActivePopup( hTop );
		if( NULL != hLastActive )
		{
			::EnableWindow(hLastActive, FALSE); 			
		}	 
	}  

	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	CenterWindow();
	
	MSG msg = { 0 };
	while( ::IsWindow(m_hWnd) && ::GetMessage(&msg, NULL, 0, 0) )
	{
		if (!m_bContinueModal)  
			break;

		if( msg.message == WM_CLOSE && msg.hwnd == m_hWnd )  
			break; 

		if( msg.message == WM_QUIT ) 
			break;

		if( !CPaintManagerUI::TranslateMessage(&msg) ) 
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		} 
		
	}

	::ShowWindow(m_hWnd, SW_HIDE);
 
	if( NULL != hWndParent )
	{
		::EnableWindow(hWndParent, TRUE);
		::SetFocus(hWndParent);
	}
	else if( NULL != hLastActive )
	{
		::EnableWindow(hLastActive, TRUE);
		::SetFocus(hLastActive);
	} 
	 
	return m_nModalResult;
 
 
}

void CDUIDialog::EndModal( int nResult )
{
	if( m_bContinueModal )
	{
		m_nModalResult = nResult;
	 	m_bContinueModal = FALSE;
		PostMessage(   WM_NULL ); 
	}
	
}

//////////////////////////////////////////////////////////////////////////
//
CWindowChildUI::CWindowChildUI()
{
}

LPCTSTR CWindowChildUI::GetClass() const
{
	return _T("WindowChildUI");
}

LPVOID CWindowChildUI::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, _T("WindowChildUI")) == 0 ) return static_cast<CWindowChildUI*>(this);
	return CContainerUI::GetInterface(pstrName);
}

// bool CWindowChildUI::SetItemIndex(CControlUI* pControl, int iIndex)
// {
// 	for( int it = 0; it < m_items.GetSize(); it++ )
// 	{
// 		if( static_cast<CControlUI*>(m_items[it]) == pControl )
// 		{
// 			NeedUpdate();            
// 			m_items.Remove(it);
// 			pControl->SetFloat(true);
// 			return m_items.InsertAt(iIndex, pControl);
// 		}
// 	}
// 
// 	return false;
// }
// 
// bool CWindowChildUI::Add(CControlUI* pControl)
// {
// 	if( pControl == NULL) return false;
// 	pControl->SetFloat(true);
// 	if( m_pManager != NULL ) m_pManager->InitControls(pControl, this);
// 	if( IsVisible() ) NeedUpdate();
// 	else pControl->SetInternVisible(false);
// 	return m_items.Add(pControl);   
// }

// 
// bool CWindowChildUI::AddAt(CControlUI* pControl, int iIndex)
// {
// 	if( pControl == NULL) return false;
// 	pControl->SetFloat(true);
// 	if( m_pManager != NULL ) m_pManager->InitControls(pControl, this);
// 	if( IsVisible() ) NeedUpdate();
// 	else pControl->SetInternVisible(false);
// 	return m_items.InsertAt(iIndex, pControl);
// }

}