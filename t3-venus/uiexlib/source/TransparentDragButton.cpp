// TransparentDragButton.cpp : implementation file
//

#include "stdafx.h"
#include "button.h"
#include "srcManage.h"
#include "dragWindow.h"
#include "bitmapHelp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define  TIMER_MOUSE_HOVER  120 

/////////////////////////////////////////////////////////////////////////////
// CTransparentDragButton

CTransparentDragButton::CTransparentDragButton()
{
    m_emStatus = emStatusNormal;
    m_pImgOnNormal = NULL;
    m_pImgOnPress = NULL;
/*	m_pImgOnSel = NULL;*/
    m_pImgOffNormal = NULL;
	m_pImgOffPress = NULL;
/*	m_pImgOffSel = NULL;*/
	m_pImage = NULL;
	
	m_pUserData = NULL;
	m_bOn = TRUE;
	m_bTimer = FALSE;

	m_pFont = CSrcManage::GetFont( "微软雅黑", 14 );
	m_colTextOn = Color( 46, 55, 76 );
	m_colTextOff = Color( 76, 84, 88 );
	m_cStringFormat.SetAlignment( StringAlignmentCenter );
	m_cStringFormat.SetLineAlignment(StringAlignmentCenter);
}

CTransparentDragButton::~CTransparentDragButton()
{
}


BEGIN_MESSAGE_MAP(CTransparentDragButton, CButton)
    //{{AFX_MSG_MAP(CTransparentDragButton)
    ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
    //}}AFX_MSG_MAP 
/*	ON_MESSAGE(BM_SETCHECK , OnBMSetCheck)*/
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentDragButton message handlers

LRESULT CTransparentDragButton::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    m_hParent = (HWND)lParam;
    if ( IsWindowVisible() == FALSE || GetParent() == NULL || m_pImgOnNormal == NULL )
    {
        return S_FALSE;
    }

    Graphics *pGraphics = (Graphics*)wParam;
    HWND hGraphWnd = (HWND )lParam;
    CWnd * pGraphWnd = FromHandle(hGraphWnd);
    
    if ( pGraphics == NULL || pGraphWnd == NULL )
    {
        return S_FALSE;
    }

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();
    pGraphWnd->ScreenToClient( &point );

    switch ( m_emStatus )
    {
    case emStatusNormal:
		m_pImage = ( m_bOn == TRUE ? m_pImgOnNormal : m_pImgOffNormal );
        break;
    case emStatusPress:
		m_pImage = ( m_bOn == TRUE ? m_pImgOnPress : m_pImgOffPress );
		break;
// 	case emStatusSel:
// 		m_pImage = ( m_bOn == TRUE ? m_pImgOnSel : m_pImgOffSel );
//        break;
    }

    if ( NULL != m_pImage && m_pImage->GetWidth() != 0 )
    {
        pGraphics->DrawImage( m_pImage, point.x, point.y, m_pImage->GetWidth(), m_pImage->GetHeight() );
    }

	Color color;
	if ( m_bOn )
	{
		color = m_colTextOn;
	}
	else
	{
		color = m_colTextOff;
	}

	CString strText;
	GetWindowText( strText ); 

	if ( strText.GetLength() > 0 )
	{
		SolidBrush brush( color );
		pGraphics->SetTextRenderingHint( TextRenderingHint( TextRenderingHintAntiAlias ) );
				
		BSTR bstr = strText.AllocSysString();
		pGraphics->DrawString( bstr, -1, m_pFont, RectF( (float)point.x, (float)point.y, cRect.Width(), cRect.Height() ), &m_cStringFormat, &brush );
		SysFreeString( bstr );
	}

//     if ( m_pImgOnNormal->GetWidth() != 0 && ( cRect.Width() != m_pImgOnNormal->GetWidth()
//          || cRect.Height() != m_pImgOnNormal->GetHeight() ) )
//     {
//         SetWindowPos( NULL, 0, 0, m_pImgOnNormal->GetWidth(), m_pImgOnNormal->GetHeight(), SWP_NOMOVE|SWP_NOACTIVATE );
//     }

    return S_OK;  
}


void CTransparentDragButton::OnLButtonDown(UINT nFlags, CPoint point) 
{   
	SetCapture();
	m_emStatus = emStatusPress;
// 	if ( m_emStatus = emStatusPress )
// 	{
// 		m_bTimer = TRUE;
// 		SetTimer( TIMER_MOUSE_HOVER, 1000U, NULL );
// 	}

	NOTIF_PARENT_WND
    CButton::OnLButtonDown(nFlags, point);
}

void CTransparentDragButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( GetCapture() == this )
	{
		ReleaseCapture();
	}
	if ( m_emStatus != emStatusPress)
	{
		return;
	}

//	m_emStatus = emStatusSel;
	NOTIF_PARENT_WND
	CButton::OnLButtonUp(nFlags, point);

	GetCursorPos( &point );
 	PostMessage( WM_BUTTON_CLICK, (WPARAM)m_pUserData, MAKELPARAM( point.x, point.y ) );   
}

void CTransparentDragButton::OnMouseMove(UINT nFlags, CPoint point)
{
    CRect rect;    
    GetClientRect( &rect );
    if ( !rect.PtInRect( point) && m_emStatus == emStatusPress )
    {   
		if ( GetCapture() == this )
		{
			ReleaseCapture();
		}
		CDragWindow* pDragWnd = CDragWindow::GetDragWindow(); 	
		if ( pDragWnd != NULL && m_pImage != NULL && m_pUserData != NULL )
		{
 			CString strText;
 			GetWindowText( strText );

			Color color;
			if ( m_bOn )
			{
				color = m_colTextOn;
			}
			else
			{
				color = m_colTextOff;
			}
			Bitmap* pBitmap = CBitmapHelp::CreateBitmap( m_pImage, strText, m_pFont, m_cStringFormat, color );
			CPoint pt;
			GetCursorPos( &pt );
			pDragWnd->BeginDrag( this, pt, pBitmap, m_pUserData );
		}
	
        NOTIF_PARENT_WND 
    }
    
}

void CTransparentDragButton::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	m_emStatus = emStatusNormal;

	if ( CButton* pBtn = dynamic_cast<CButton*>( pNewWnd ) )
	{
		//点中button不发消息
	}
	else
	{
		PostMessage( WM_KILL_FOCUS );
	}	

	NOTIF_PARENT_WND
}

// LRESULT CTransparentDragButton::OnBMSetCheck( WPARAM wParam, LPARAM lParam )
// {
//     DefWindowProc( BM_SETCHECK, wParam, lParam );
// 	
//     NOTIF_PARENT_WND
// 		
//     return 0;	
// }

void CTransparentDragButton::SetSelState( BOOL bSel )
{
	if ( bSel )
	{
		m_emStatus = emStatusPress;
	}
	else
	{
		m_emStatus = emStatusNormal;
	}
	NOTIF_PARENT_WND
}

BOOL CTransparentDragButton::GetSelState()
{
	if ( m_emStatus == emStatusPress )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CTransparentDragButton::SetOnline( BOOL bOnline )
{
	m_bOn = bOnline;
}

void CTransparentDragButton::SetUserData( IData* pData )
{
	m_pUserData = pData;	
}


void CTransparentDragButton::OnTouchButtonDown( CPoint pt )
{	
    SetCapture();
    m_emStatus = emStatusPress;		
    NOTIF_PARENT_WND 
}

LRESULT CTransparentDragButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    if ( message == WM_TOUCH_BUTTONDOWN )
    {
        int nX = LOWORD( lParam );
        int nY = HIWORD( lParam );
        //屏幕坐标点
        if ( m_emStatus != emStatusPress )
        {
            OnTouchButtonDown( CPoint( nX, nY ) );  
        }     
    }

    return CButton::DefWindowProc(message, wParam, lParam);
}


void CTransparentDragButton::SetImage( CString strFolder, BOOL bInvalidate /* = FALSE */ )
{
	String strFile = strFolder + "//" + CTransparentSwitchButton::strOnNormal;
	m_pImgOnNormal = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSwitchButton::strOnPress;
	m_pImgOnPress = CSrcManage::GetImage( strFile.c_str() );
// 	strFile = strFolder + "//" + CTransparentSwitchButton::strOnSel;
// 	m_pImgOnSel = CSrcManage::GetImage( strFile.c_str() );
	
	strFile = strFolder + "//" + CTransparentSwitchButton::strOffNormal;
	m_pImgOffNormal = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSwitchButton::strOffPress;
	m_pImgOffPress = CSrcManage::GetImage( strFile.c_str() );
// 	strFile = strFolder + "//" + CTransparentSwitchButton::strOffSel;
// 	m_pImgOffSel = CSrcManage::GetImage( strFile.c_str() );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}
