// dragwindow.cpp : implementation file
//

#include "stdafx.h"
#include "dragwindow.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragWindow dialog
CDragWindow* CDragWindow::m_pcDragWindow = NULL;

// CDragWindow::CDragWindow(CWnd* pParent /*=NULL*/)
// 	: CDialog(CDragWindow::IDD, pParent)
// {
// 	//{{AFX_DATA_INIT(CDragWindow)
// 		// NOTE: the ClassWizard will add member initialization here
// 	m_pParentWnd = NULL;
// 	m_pLastWnd = NULL;
// //	m_pItemInfo = NULL;
// 	//}}AFX_DATA_INIT
// }

CDragWindow::CDragWindow( CRect rcList, CWnd* pWnd, UINT nID ) : 
	CTransparentBaseWnd( rcList, pWnd, WS_POPUP,"",nID, WS_EX_TOPMOST|WS_EX_TOOLWINDOW, 200, TRUE, FALSE ),
    m_pSrcWnd( NULL )
{
	m_pLastWnd = NULL;
	m_pUserData = NULL;
	m_vctWnd.clear();
    m_pNotifyWnd = NULL;
}


BEGIN_MESSAGE_MAP(CDragWindow, CTransparentBaseWnd)
	//{{AFX_MSG_MAP(CDragWindow)
	ON_WM_MOUSEMOVE()
	//ON_WM_MOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDragWindow::OnMove(int x, int y) 
{
	CTransparentBaseWnd::OnMove(x, y);
	CPoint point;
	GetCursorPos( &point );
	CDragWindow::GetDragWindow()->ReportDragOver( point );
	// TODO: Add your message handler code here
}

void CDragWindow::OnMouseMove(UINT nFlags, CPoint point)
{
 	GetCursorPos( &point );
// 	GetDragWindow()->EndDrag( point );
    
    if ( m_pLastPoint == point )
    {
        return;
    }
    m_pLastPoint = point;

	CDragWindow* pWnd = CDragWindow::GetDragWindow();
	pWnd->ReportDragOver( point );

	CRect rcWindow;
 	pWnd->GetWindowRect(&rcWindow);	
	pWnd->SetWindowPos( 0, point.x - rcWindow.Width()/2, point.y - rcWindow.Height()/2, 
		0, 0,  SWP_NOSIZE|SWP_SHOWWINDOW |SWP_NOZORDER|SWP_SHOWWINDOW  );
	CTransparentBaseWnd::OnMouseMove( nFlags, point );
}

void CDragWindow::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	GetCursorPos( &point );
	GetDragWindow()->EndDrag( point );
}

/////////////////////////////////////////////////////////////////////////////
// CDragWindow message handlers
CDragWindow* CDragWindow::GetDragWindow()
{
	if (m_pcDragWindow == NULL) 
	{
		m_pcDragWindow = new CDragWindow( CRect(0,0,200,200), NULL, 0);
	}
	return m_pcDragWindow;
}

BOOL CDragWindow::BeginDrag( CWnd* pSrcWnd, CPoint point, Image* pBitmap, IData* pData )
{
	SetCapture();
	CDragWindow* pWnd = CDragWindow::GetDragWindow();
    m_pSrcWnd = pSrcWnd;
	pWnd->SetOwner( pSrcWnd );
	pWnd->SetWindowPos( NULL, 0, 0, pBitmap->GetWidth(), pBitmap->GetHeight(), SWP_NOMOVE|SWP_NOACTIVATE );
	SetImage( pBitmap, TRUE );

    //m_pUserData Clone一份，防止拖拽数据被改变
    if ( m_pUserData != NULL )
    {
        delete m_pUserData;
        m_pUserData = NULL;
    } 
    if ( pData != NULL )
    {
        m_pUserData = pData->Clone();
	}

    m_pLastPoint = point;
	
	CRect rcWindow;
	pWnd->GetWindowRect(&rcWindow);
	
	int nWidth = pBitmap->GetWidth();
	int nHeight = pBitmap->GetHeight();
	pWnd->SetWindowPos( 0, point.x - rcWindow.Width()/2, point.y - rcWindow.Height()/2, 
		nWidth, nHeight,  SWP_NOSIZE|SWP_SHOWWINDOW |SWP_NOZORDER|SWP_SHOWWINDOW  );

	pWnd->SetAutoHideStatus( TRUE );
	pWnd->SendMessage( WM_REDRAW_UI, 0, 0 );
	this->SendMessage( WM_LBUTTONDOWN,0,0);

	return TRUE;
}


BOOL CDragWindow::Draging( CPoint point )
{
	ReportDragOver( point );

 	CDragWindow* pWnd = CDragWindow::GetDragWindow();
 	CRect rcWindow;
 	pWnd->GetWindowRect(&rcWindow);	
	
 	return 	pWnd->SetWindowPos( &wndTopMost, point.x - rcWindow.Width()/2, point.y - rcWindow.Height()/2,
		0, 0, SWP_NOSIZE | SWP_SHOWWINDOW  );
}


BOOL CDragWindow::EndDrag( CPoint point )
{
	CWnd* pWindow = GetActiveWindow(point);  

	if ( m_pUserData != NULL )
	{
        if ( IData* pData = dynamic_cast<IData*>(m_pUserData) )
        {
            if ( pWindow != NULL )
            {
                pWindow->PostMessage( UI_DRAG_END, WPARAM(m_pUserData), MAKELPARAM( point.x, point.y ) );
            }
        
            if ( m_pSrcWnd != NULL )
            {
                m_pSrcWnd->PostMessage( UI_BE_DRAG_END, WPARAM(m_pUserData), MAKELPARAM( point.x, point.y ) );
            }
        }
    }

    //ReportNotifyWnd( UI_DRAG_END, point );

	CDragWindow* pWnd = CDragWindow::GetDragWindow();
	pWnd->ShowWindow( SW_HIDE );
    pWnd->SendMessage( WM_REDRAW_UI, 0, 0 );
	m_pLastWnd = NULL; 

	return TRUE; 
}


void CDragWindow::ReportDragOver( CPoint point )
{
	CWnd* pWnd = GetActiveWindow(point);

	if ( m_pLastWnd != NULL && m_pLastWnd != pWnd )
	{    
		//CMsgDispatch::SendMessage( UI_DRAG_LEAVE, 0, MAKELPARAM( point.x, point.y ) );
		m_pLastWnd->PostMessage( UI_DRAG_LEAVE, 0, MAKELPARAM( point.x, point.y ) );
		if ( NULL == pWnd )
		{
			m_pLastWnd = NULL;
		}			
	}

    //通知NotifyWnd坐标
    ReportNotifyWnd( UI_DRAG_OVER, point );

		
	if (pWnd != NULL)
	{	
		if ( m_pLastWnd == pWnd )
		{
			return ;
		}
		m_pLastWnd = pWnd;

		//try
		//{
			if ( m_pUserData != NULL )
			{
				if ( IData* pData = dynamic_cast<IData*>(m_pUserData) )
				{
					pWnd->PostMessage( UI_DRAG_OVER, WPARAM(m_pUserData), MAKELPARAM( point.x, point.y ) );
				}
			}						
		//}
		//catch(...)
		//{
			//拖拽数据被改变
		//}
	}	

}


BOOL CDragWindow::RegisterDropWindow(CWnd* pWnd)
{
	vector<CWnd*>::iterator begin = m_vctWnd.begin();
	for (; begin != m_vctWnd.end(); begin++) 
	{
		if (*begin == pWnd) 
		{
			return FALSE;
		}
	}
	m_vctWnd.push_back(pWnd);
	return TRUE;
}


BOOL CDragWindow::UnRegisterDropWindow(CWnd* pWnd)
{
    vector<CWnd*>::iterator begin = m_vctWnd.begin();
	for (; begin != m_vctWnd.end(); begin++) 
	{
		if (*begin == pWnd) 
		{   
			m_vctWnd.erase(begin);
			return TRUE;
		}
	}
	
	return FALSE;
}


CWnd* CDragWindow::GetActiveWindow( CPoint point )
{
	vector<CWnd*>::iterator begin = m_vctWnd.begin();
	for (; begin != m_vctWnd.end(); begin++) 
	{
		CWnd* pWnd = *begin;
		if ( pWnd->IsWindowVisible() && pWnd != m_pSrcWnd ) 
		{
			CRect rcWindow;
			pWnd->GetWindowRect(&rcWindow);
			if ( rcWindow.PtInRect(point) )
			{   
				return pWnd;
			}
		}
	}
	return NULL;
}

void CDragWindow::SetNotifyWindow( CWnd* pWnd )
{ 
    m_pNotifyWnd = pWnd;
    RegisterDropWindow( pWnd );
}


void CDragWindow::ReportNotifyWnd( UINT message, CPoint point )
{
    if ( m_pNotifyWnd != NULL && m_pNotifyWnd->IsWindowVisible() && m_pNotifyWnd != m_pSrcWnd )
    {
        CRect rcWindow;
        m_pNotifyWnd->GetWindowRect(&rcWindow);
        if ( rcWindow.PtInRect(point) )
        {   
            if ( m_pUserData != NULL )
            {
                if ( IData* pData = dynamic_cast<IData*>(m_pUserData) )
                {
                    m_pNotifyWnd->PostMessage( message, WPARAM(m_pUserData), MAKELPARAM( point.x, point.y ) );
                }
            }
        }
    }
}

