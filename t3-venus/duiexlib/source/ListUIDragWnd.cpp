#include "stdafx.h"

CListUIDragWnd::CListUIDragWnd( HWND wndMain,CPaintManagerUI& cPaintManager )
:m_hWndMain(wndMain),
m_cPaintManager(cPaintManager)
{
	Create(NULL, _T("ListUIDrag"), WS_POPUP, WS_EX_TOOLWINDOW, 0, 0);

	m_hdc = NULL;
	m_mdc = NULL;
	m_bmpItem = NULL;
}

CListUIDragWnd::~CListUIDragWnd()
{
	ResetDraw();
}

CRect CListUIDragWnd::GetMainFrameRect()
{
	if ( NULL != m_hWndMain )
	{
		GetWindowRect( m_hWndMain, &m_rcMainFrame );
	}

	return m_rcMainFrame;
}

void CListUIDragWnd::SetListItemHeight( int nListItemHeight )
{ 
	m_nListItemHeight = nListItemHeight; 

	SIZE size;
	size.cx = m_rcThis.right - m_rcThis.left;
	size.cy = m_rcThis.bottom - m_rcThis.top;
	if ( size.cx != 0 )
	{
		::SetWindowPos( m_hWnd, NULL, 0, 0, 
			size.cx, m_nListItemHeight, SWP_HIDEWINDOW );
	}
}

LPCTSTR CListUIDragWnd::GetWindowClassName() const 
{ 
	return _T("CListUIDragWnd");
}

void CListUIDragWnd::ShowWnd(bool bShow)
{
	ShowWindow(bShow);
}

void CListUIDragWnd::MoveWnd( POINT pt, CListContainerElementUI* pLsElem )
{
	//::SetWindowPos( m_hWnd, NULL, pt.x + GetMainFrameRect().left - m_rcThis.GetWidth()/2, pt.y + GetMainFrameRect().top - m_nListItemHeight/2/*- m_rcThis.GetHeight()/2*/ /*+ m_nListItemHeight/2*/, 
	//	10, 10, SWP_NOSIZE|SWP_SHOWWINDOW );  //MoveWindow( m_hWnd, pt.x, pt.y, 140, 165, FALSE );

	::SetWindowPos( m_hWnd, NULL, pt.x + GetMainFrameRect().left - m_rcThis.GetWidth()/2, pt.y + GetMainFrameRect().top - m_nListItemHeight/2/*- m_rcThis.GetHeight()/2*/ /*+ m_nListItemHeight/2*/, 
		10, 10, SWP_NOSIZE|SWP_SHOWWINDOW );

	if ( NULL != pLsElem )
	{
		Draw(pLsElem);
	}
}

void CListUIDragWnd::ResetDraw()
{
	if ( NULL != m_hdc )
	{
		::DeleteDC( m_hdc );
		m_hdc = NULL;
	}
	if ( NULL != m_mdc )
	{
		::DeleteDC( m_mdc );
		m_mdc = NULL;
	}
	if ( NULL != m_bmpItem )
	{
		::DeleteObject( m_bmpItem );
		m_bmpItem = NULL;
	}
}

void CListUIDragWnd::Draw(CListContainerElementUI* pLsElem)
{
 	if( NULL != pLsElem )
 	{
		if ( NULL == m_hdc )
		{
			m_hdc = ::GetDC(m_hWnd);
		}
 		
		if( NULL == m_bmpItem )
		{
 			m_bmpItem = CRenderEngine::GenerateBitmap( &m_cPaintManager, pLsElem, pLsElem->GetControlRect() );
		}
		if ( NULL == m_mdc )
		{
			m_mdc = ::CreateCompatibleDC(m_hdc);
			::SelectObject( m_mdc, m_bmpItem );
		}
		BitBlt( m_hdc, 0, 0, pLsElem->GetControlRect().right - pLsElem->GetControlRect().left, pLsElem->GetControlRect().bottom - pLsElem->GetControlRect().top, m_mdc, 0, 0, SRCCOPY );
 	}
}