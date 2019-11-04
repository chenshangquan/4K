// TransparentSlideBlock.cpp : implementation file
//

#include "stdafx.h"
#include "slider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentSlideBlock

#define SLIDEBLOCK_INTERVAL   2    //间隙
#define TIMER_HANDLE_MOVING  100 
#define TIMER_HANDLE_BACK    101

#define AUTO_BACK_SPEED      30    //滑块自动返回速度

const CString CTransparentSlideBlock::strBkImg = "BkImg.png";
const CString CTransparentSlideBlock::strBlockNormal = "Normal.png";
const CString CTransparentSlideBlock::strBlockPress = "Press.png";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTransparentSlideBlock::CTransparentSlideBlock(CString strName, CString strUI, CRect rcWnd, CWnd* pWnd, UINT nID, DWORD dStyle, DWORD dwExStyle) 
: CTransparentBaseWnd( rcWnd, pWnd, dStyle, strUI, nID )
{
    m_pImgBkg = NULL;
	m_pImgBlockNormal = NULL;
	m_pImgBlockPress = NULL;
	m_bLBtnDown = FALSE;
	m_nOffset = 0;
	m_nMaxOffset = 0;
	m_nMoveSpeed = 0;
}

CTransparentSlideBlock::~CTransparentSlideBlock()
{
}


BEGIN_MESSAGE_MAP(CTransparentSlideBlock, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CTransparentCheckButton)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_TIMER()
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


LRESULT CTransparentSlideBlock::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
	Graphics *pGraphics = (Graphics*)wParam; 	
    HWND hGraphWnd = (HWND )lParam;
	CWnd *pGraphWnd = FromHandle(hGraphWnd);

    if ( !IsWindowVisible() || GetParent() == NULL || m_pImgBkg == NULL || pGraphics == NULL || pGraphWnd == NULL )
    {
        return S_FALSE;
    }
	

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();
	
    //GetParent()->ScreenToClient( &point );
	pGraphWnd->ScreenToClient( &point );
		
    if ( NULL != m_pImgBkg )
    {
        pGraphics->DrawImage( m_pImgBkg, point.x, point.y, /*m_pImgBkg->GetWidth(), m_pImgBkg->GetHeight()*/cRect.Width(), cRect.Height() );        
    }

	Image *pImage = NULL;
	if ( m_bLBtnDown )
	{
		pImage = m_pImgBlockPress;
	}
	else
	{
		pImage = m_pImgBlockNormal;
	}

    //滑块大小自适应
    int nBlockWidth = pImage->GetWidth();  
    if ( m_pImgBkg->GetWidth() != 0 )
    {
        nBlockWidth = nBlockWidth * cRect.Width() / m_pImgBkg->GetWidth();
    }  

	int nPosX = m_nOffset + SLIDEBLOCK_INTERVAL;
	if ( NULL != pImage )
	{
		pGraphics->DrawImage( pImage, point.x + nPosX, point.y + SLIDEBLOCK_INTERVAL, nBlockWidth, cRect.Height() - SLIDEBLOCK_INTERVAL - 1);

		m_nMaxOffset = cRect.Width() - nBlockWidth - 2 * SLIDEBLOCK_INTERVAL;
	}

	m_cBlockRect.SetRect( nPosX, SLIDEBLOCK_INTERVAL, nBlockWidth + nPosX , /*m_pImgBlockNormal->GetHeight()*/cRect.Height() - 1 );
		
//     if ( cRect.Width() != m_pImgBkg->GetWidth()
// 		|| cRect.Height() != m_pImgBkg->GetHeight() )
//     {
//         SetWindowPos( NULL, 0, 0, m_pImgBkg->GetWidth(), m_pImgBkg->GetHeight(), SWP_NOMOVE|SWP_NOACTIVATE );
//     }
	
    return S_OK;  
}

void CTransparentSlideBlock::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ( !m_cBlockRect.PtInRect( point ) )
	{    
		return;
	}
	m_bLBtnDown = TRUE;

	if ( m_nMoveSpeed != 0 )
	{   		
		m_nMoveSpeed = 0;
		KillTimer(TIMER_HANDLE_MOVING);	
		KillTimer(TIMER_HANDLE_BACK);
	} 

	m_ptMouseNow = point;
	m_ptMouseLast = point;

	NOTIF_PARENT_WND
	SetCapture();	
}

void CTransparentSlideBlock::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( !m_bLBtnDown )
	{
		return;
	}

	m_ptMouseLast = m_ptMouseNow;
	m_ptMouseNow = point;

	BlockMove();

	NOTIF_PARENT_WND
}

void CTransparentSlideBlock::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( !m_bLBtnDown )
	{
		return;
	}
	m_bLBtnDown = FALSE;
	
	if ( abs(m_ptMouseNow.x - m_ptMouseLast.x) > 6 ) //产生惯性运动
    {
		m_nMoveSpeed = (m_ptMouseNow.x - m_ptMouseLast.x) / 5;
		SetTimer( TIMER_HANDLE_MOVING, 20, NULL );	   
    }
	else if ( m_nOffset < m_nMaxOffset )
	{
		m_nMoveSpeed = AUTO_BACK_SPEED;
		SetTimer( TIMER_HANDLE_BACK, 20, NULL );
	}
	else
	{
		m_nOffset = 0;
		GetParent()->PostMessage( UI_SLIDEBLOCK_ENDLOCK );
	}
	
	if ( GetCapture() == this )
	{
		ReleaseCapture();
	}
	NOTIF_PARENT_WND
}


void CTransparentSlideBlock::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if ( nIDEvent == TIMER_HANDLE_MOVING )
	{		
		BlockAutoMove();
	}
	else if ( nIDEvent == TIMER_HANDLE_BACK )
	{
		BlockAutoBack();
	}
	
	CTransparentBaseWnd::OnTimer(nIDEvent);
}

void CTransparentSlideBlock::BlockMove()
{
	m_nOffset += ( m_ptMouseNow.x - m_ptMouseLast.x );
	
	if ( m_nOffset < 0 )
	{
		m_nOffset = 0;  			
	}
	
	if ( m_nOffset > m_nMaxOffset )
	{
		m_nOffset = m_nMaxOffset;		
	} 
}

void CTransparentSlideBlock::BlockAutoMove()
{
	m_nOffset += m_nMoveSpeed;
	m_nMoveSpeed *= 0.96;
	
	if ( m_nOffset < 0 )
	{
		m_nMoveSpeed = 0;
		m_nOffset = 0;  			
	}
	
	if ( m_nOffset > m_nMaxOffset )
	{
		m_nMoveSpeed = 0;
		m_nOffset = m_nMaxOffset;		
	} 

	if ( 0 == m_nMoveSpeed )
	{ 
		KillTimer(TIMER_HANDLE_MOVING);  
		if ( m_nOffset < m_nMaxOffset )
		{
			m_nMoveSpeed = AUTO_BACK_SPEED;
			SetTimer( TIMER_HANDLE_BACK, 20, NULL );
		}
		else
		{
			m_nOffset = 0;
			GetParent()->PostMessage( UI_SLIDEBLOCK_ENDLOCK );
		}
	} 
	NOTIF_PARENT_WND
}

void CTransparentSlideBlock::BlockAutoBack()
{
	m_nOffset -= m_nMoveSpeed;

	if ( m_nOffset <= 0 )
	{
		m_nOffset = 0;
		m_nMoveSpeed = 0;
		KillTimer(TIMER_HANDLE_BACK);  
	}
	NOTIF_PARENT_WND
}

void CTransparentSlideBlock::SetImage( CString strFolder, BOOL bInvalidate /* = FALSE */ )
{
	String strFile = strFolder + "//" + CTransparentSlideBlock::strBkImg;
	m_pImgBkg = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSlideBlock::strBlockNormal;
	m_pImgBlockNormal = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSlideBlock::strBlockPress;
	m_pImgBlockPress = CSrcManage::GetImage( strFile.c_str() );

	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}