// TransparentBtn.cpp : implementation file
//

#include "stdafx.h"
#include "button.h"
#include "srcManage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentBtn

const CString CTransparentBtn::strNormalImage = "Normal.png";
const CString CTransparentBtn::strPressImage = "Sel.png";
const CString CTransparentBtn::strDisableImage = "Disable.png";
const CString CTransparentBtn::strOverImage = "Over.png";
template<> WNDPROC TransparentAssist<CTransparentBtn>::m_pWndProc = NULL;
CTransparentBtn::CTransparentBtn()
{
    m_emStatus = emStatusNormal;
    m_pImgNormal = NULL;
    m_pImgPress = NULL;
    m_pImgDisable = NULL;
	m_pImgOver = NULL;
	m_bImageOver = FALSE;

	m_cStringFormat.SetAlignment( StringAlignmentCenter );
    m_bShowText = TRUE;

    m_cPoint = CPoint( 0, 0 );

	m_pFont = CSrcManage::GetFont( "Arial", 18 );
	
	m_wOffset = 0;
    m_bStretch = TRUE;
	m_bLButtonDown = FALSE;
	m_coText = Color::Black;

	m_hParentWnd = NULL;

    m_nTimer = 0;
    m_bUseTimer = FALSE; //default not intend  to use the timer
    m_bMouseTrack = TRUE;
	m_dwElapse = 300;
    m_bTouchUp = FALSE;
    m_bTouchDown = FALSE;
}

CTransparentBtn::CTransparentBtn( CString strImage )
{
	SetImage( strImage );
	m_emStatus = emStatusNormal;
	m_cStringFormat.SetAlignment( StringAlignmentCenter );
    m_bShowText = TRUE;
	
    m_cPoint = CPoint( 0, 0 );
	
	m_pFont = CSrcManage::GetFont( "Arial", 18 );
	
	m_wOffset = 0;
    m_bStretch = FALSE;
	m_bLButtonDown = TRUE;
	m_coText = Color::Black;
	m_hParentWnd = NULL;

    m_nTimer = 0;
    m_bUseTimer = FALSE; //default not intend  to use the timer
    m_bMouseTrack = TRUE;
	m_dwElapse = 300;
    m_bTouchUp = FALSE;
    m_bTouchDown = FALSE;
}

CTransparentBtn::~CTransparentBtn()
{	

}


BEGIN_MESSAGE_MAP(CTransparentBtn, CButton)
	//{{AFX_MSG_MAP(CTransparentBtn)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
    ON_WM_ENABLE()
    ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave )
	ON_MESSAGE( WM_MOUSEHOVER, OnMouseHover )
    ON_MESSAGE( WM_PARENT_HIDE, OnParentHide )
    //ON_WM_DESTROY
END_MESSAGE_MAP()

int CTransparentBtn::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	RegsiterWndProc();
	// TODO: Add your specialized creation code here
	
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CTransparentBtn message handlers
#define WM_GESTURENOTIFY                0x011A

LRESULT CTransparentBtn::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
 	if ( message == WM_TOUCH_BUTTONDOWN )
 	{
		int nX = LOWORD( lParam );
		int nY = HIWORD( lParam );
		//屏幕坐标点
		if ( !m_bLButtonDown )
		{
			OnTouchButtonDown( CPoint( nX, nY ) );
			m_bLButtonDown = TRUE;           
		}		
	}
	if ( message == WM_LBUTTONUP )
	{
		m_bLButtonDown = FALSE;
	}
    else if ( message == WM_TOUCH )
    {
        if ( m_bTouchUp )
        {
            return CButton::DefWindowProc(message, wParam, lParam);
        }

        WINSDK_GetTouchInputInfo _WINSDK_GetTouchInputInfo;
        
        UINT cInputs = LOWORD(wParam);
        TOUCHINPUT tInput;

        HINSTANCE hInstLibrary = LoadLibrary("windowsexsdk.dll");
        if (hInstLibrary != NULL)
        {
            _WINSDK_GetTouchInputInfo = (WINSDK_GetTouchInputInfo)GetProcAddress( hInstLibrary, "WINSDK_GetTouchInputInfo" );
            if ( _WINSDK_GetTouchInputInfo != NULL )
            {
                _WINSDK_GetTouchInputInfo( lParam, cInputs, tInput );

                if ( tInput.dwFlags & TOUCHEVENTF_DOWN )
                {
                    m_bTouchUp = FALSE;
                    //此时已经响应过WM_TOUCH_BUTTONDOWN
                    //OnTouchButtonDown( CPoint( 0, 0 ) );
                    m_emStatus = emStatusBtnDown;
                    NOTIF_PARENT_WND_IMMEDIATLY_DRAW
                
                    m_bTouchDown = TRUE;

                    //CString msg;
                    //msg.Format( _T("\nBtn WM_TOUCH,TOUCHEVENTF_DOWN.m_bTouchDown: %d, m_bTouchUp:%d \n"), m_bTouchDown, m_bTouchUp );
		            //AfxOutputDebugString( msg );

                    PostMessage( WM_BUTTON_DOWN );
                }
                if ( tInput.dwFlags & TOUCHEVENTF_UP )
                {
                    //响应触摸放开的消息，防止按钮一直高亮
                    //CString msg;
                    //msg.Format( _T("\nBtn WM_TOUCH,TOUCHEVENTF_UP.m_bTouchDown: %d, m_emStatus:%d \n"), m_bTouchDown, m_emStatus );
		            //AfxOutputDebugString( msg );

                    OnTouchButtonUp();               
                }

            }
            FreeLibrary( hInstLibrary );
        }    
    }

    return CButton::DefWindowProc(message, wParam, lParam);
}

LRESULT CTransparentBtn::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{   
    Graphics *pGraphics = (Graphics*)wParam; 
    
    HWND hGraphWnd = (HWND )lParam;
    // CWnd * pGraphWnd = FromHandle(hGraphWnd);
    
    if ( !IsWindowVisible() || GetParent() == NULL || m_pImgNormal == NULL || pGraphics == NULL || hGraphWnd == 0  )
    {
// 		if ( m_bUseTimer )
// 		{
// 			str.Format("\n[CTransparentBtn::OnRedrawUI]handle=%x  return false :IsVisible=%d,  \
// 				getparent=%x, m_pImgNormal isNull=%d, pGraphics isNULL=%d hGraphWnd isNULL=%d\n",
// 				GetSafeHwnd() ,IsWindowVisible(),GetParent(),m_pImgNormal==NULL,pGraphics==NULL,hGraphWnd==NULL);
// 			AfxOutputDebugString( str );
// 		}
        m_emStatus = emStatusNormal;
        return S_FALSE;
    }
	m_hParentWnd = ::GetParent( m_hWnd );
    
	
    CRect cRect;
    GetWindowRect( &cRect );
    
	if ( ( cRect.Width() != m_pImgNormal->GetWidth()
		|| cRect.Height() != m_pImgNormal->GetHeight() ) )
	{
		if ( FALSE == m_bStretch )
		{
			cRect.right = cRect.left + m_pImgNormal->GetWidth();
			cRect.bottom = cRect.top + m_pImgNormal->GetHeight();			
			SetWindowPos( NULL, 0, 0, m_pImgNormal->GetWidth(), m_pImgNormal->GetHeight(), SWP_NOMOVE );
		}
	}
    
    POINT point = cRect.TopLeft();

    //::ScreenToClient( m_hParentWnd, &point );
    ::ScreenToClient( hGraphWnd, &point );
    
    Image *pImage = NULL;
    switch ( m_emStatus )
    {
    case emStatusNormal:
        pImage = m_pImgNormal;
        break;
    case emStatusBtnDown:
        pImage = m_pImgPress;
        break;
	case emStatusBtnOver:
        pImage = m_pImgOver;
        break;
    }

    if ( FALSE == IsWindowEnabled() )
    {
        pImage = m_pImgDisable;
    }

    if ( NULL != pImage )
    {
		if ( pImage->GetWidth() != 0 )
		{
			pGraphics->DrawImage( pImage, point.x, point.y, cRect.Width(), cRect.Height() );
		}
		
		if ( pImage->GetWidth() == 0 && pImage->GetHeight() == 0 )
		{		
			if ( TRUE == m_bShowText )
			{
				SolidBrush brush( m_coText ); // 创建实心刷（写字符串用）
				//pGraphics->SetTextRenderingHint( TextRenderingHint( TextRenderingHintAntiAlias ) );

				CString strText;
				GetWindowText( strText );   
				BSTR bstr = strText.AllocSysString();
				pGraphics->DrawString( bstr, -1, m_pFont, RectF( (float)point.x, (float)point.y, cRect.Width(), cRect.Height() ), &m_cStringFormat, &brush );	
				SysFreeString( bstr );
			}
		}
    }
	return S_OK;    
}

void CTransparentBtn::OnLButtonDown(UINT nFlags, CPoint point) 
{     
	m_emStatus = emStatusBtnDown;
	
// 	if ( m_bUseTimer )
// 	{
// 	 CString str;
// 	 str.Format("OnLButtonDown, nFlags: %d, m_bTouchDown:%d\n", nFlags, m_bTouchDown );
//     AfxOutputDebugString( str );
// 	}

	UpdateUI();

	//放在CButton::CButton::OnLButtonDown()之后响应不到点击事件
	SetCapture();

    if ( m_bUseTimer && 0 == m_nTimer )
    {
        m_nTimer = SetTimer( 1, m_dwElapse, NULL );      
    }

    if ( !m_bTouchDown )
    {
        PostMessage( WM_BUTTON_DOWN );
    }
    m_bTouchDown = FALSE;
    
	CButton::OnLButtonDown(nFlags, point);
}

void CTransparentBtn::OnLButtonDblClk(UINT nFlags, CPoint point) 
{ 
	m_emStatus = emStatusBtnDown;
	
// 	if ( m_bUseTimer )
// 	{
//		CString str;
//		str.Format("\n[CTransparentBtn::OnLButtonDblClk]handle=%x\n",GetSafeHwnd() );
//		AfxOutputDebugString( str );
// 	} 
	
  	UpdateUI();
	SetCapture();

	if ( m_bUseTimer && 0 == m_nTimer )
    {
        m_nTimer = SetTimer( 1, m_dwElapse, NULL );
    }
	 
	CButton::OnLButtonDblClk(nFlags, point);
	
}

void CTransparentBtn::OnTouchButtonDown( CPoint pt )
{	
    m_bTouchUp = FALSE;

    m_emStatus = emStatusBtnDown;		
    UpdateUI( TRUE );

    SetCapture();

    if ( m_bUseTimer && 0 == m_nTimer )
    {
        m_nTimer = SetTimer( 1, m_dwElapse, NULL );
        //PostMessage( WM_LBUTTON_DOWN ); 触摸时 收到会先收到WM_TOUCH_BUTTONDOWN 再收到LButtondwon 所以此处不发消息 dyy 2014-4-29
    }

    //CString str;
    //str.Format("\n[CTransparentBtn::OnTouchButtonDown]handle=%x\n",GetSafeHwnd() );
    //AfxOutputDebugString( str );
}

void CTransparentBtn::OnTouchButtonUp()
{
    if ( m_bUseTimer && 0 != m_nTimer )
    {
        KillTimer( m_nTimer );
        m_nTimer = 0;
        GetParent()->PostMessage( WM_BTN_HOLD_END, (WPARAM)GetSafeHwnd(), NULL );
        PostMessage( WM_BTN_HOLD_END, NULL, NULL );
    }  
    
    if ( m_emStatus != emStatusBtnDown  )
    {
        ReleaseCapture();   
        return;
    } 

    m_bTouchUp = TRUE;
    
    m_bLButtonDown = FALSE;
    m_emStatus = emStatusNormal;

    PostMessage( WM_BUTTONSTATUS_NORMAL );

    UpdateUI();
    
    ReleaseCapture();
}


void CTransparentBtn::OnLButtonUp(UINT nFlags, CPoint point) 
{   
    //CString str;
    //str.Format("\n[CTransparentBtn::OnLButtonUp]m_bTouchUp=%d, m_emStatus:%d \n", m_bTouchUp, m_emStatus );
	//AfxOutputDebugString( str );

    if ( m_bUseTimer && 0 != m_nTimer )
    {
        KillTimer( m_nTimer );
        m_nTimer = 0;
        GetParent()->PostMessage( WM_BTN_HOLD_END, (WPARAM)GetSafeHwnd(), NULL );
        PostMessage( WM_BTN_HOLD_END, NULL, NULL );
    }  

    if ( m_emStatus != emStatusBtnDown )
    {
        m_bTouchUp = FALSE;
        CButton::OnLButtonUp(nFlags, point); 
        ReleaseCapture();          
        return;
    } 

    m_bLButtonDown = FALSE;
    m_bTouchDown = FALSE;
	m_emStatus = emStatusNormal;

	UpdateUI();

    PostMessage( WM_BUTTON_CLICK );	 

    if ( !m_bTouchUp )
    {
        PostMessage( WM_BUTTONSTATUS_NORMAL );	
    }
    m_bTouchUp = FALSE;

	CButton::OnLButtonUp(nFlags, point); 

    ReleaseCapture();
}

void CTransparentBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( !IsWindowEnabled() || !IsWindowVisible() )
	{
		return;
	}
	CRect rect;    
    GetClientRect( &rect );

	if ( m_pImgOver != NULL )
	{
		if ( m_bMouseTrack )     //2013.5.21  ---找到鼠标最后停留的窗口,解决切换程序窗口失去鼠标焦点后的over绘制问题
		{
			TRACKMOUSEEVENT csTME;
			csTME.cbSize = sizeof (csTME);
			csTME.dwFlags = TME_LEAVE|TME_HOVER; //开启事件
			csTME.hwndTrack = GetSafeHwnd() ;// 指定要 追踪 的窗口 
			csTME.dwHoverTime = 10;  // 鼠标在按钮上停留超过 10ms ，才认为状态为 HOVER
			::_TrackMouseEvent (&csTME); // 开启 Windows 的 WM_MOUSELEAVE|WM_MOUSEHOVER事件支持 
			
			m_bMouseTrack = FALSE;   // 若已经 追踪 ，则停止 追踪 
		}
	}

	//当鼠标Down下后,移动鼠标,若是鼠标不在button内(没有WM_MOUSELEAVE消息),则将button置为normal状态
    if ( !rect.PtInRect( point) && m_emStatus == emStatusBtnDown )   
    {   
        if ( m_bUseTimer )
        {
            KillTimer( m_nTimer );
            m_nTimer = 0;
            //TRACE( "[CTransparentBtn::OnMouseMove] KILL timer !\n");
            GetParent()->PostMessage( WM_BTN_HOLD_END, (WPARAM)GetSafeHwnd(), NULL );
            PostMessage( WM_BTN_HOLD_END, NULL, NULL );
        }
        ReleaseCapture();
        m_emStatus = emStatusNormal;

        PostMessage( WM_BUTTONSTATUS_NORMAL );

        //CString str;
        //str.Format("\n[CTransparentBtn::OnMouseMove] nFlags: %d, m_bTouchUp:%d\n", nFlags,m_bTouchUp );
        //AfxOutputDebugString( str );
		
		UpdateUI(); 
    }

    // UpdateUI(); 不应有鼠标就绘制 2012-7-2 by yjj
     
}
 

BOOL CTransparentBtn::EnableWindow(BOOL bEnable /* = TRUE */)
{	
	BOOL bRet = CButton::EnableWindow( bEnable );
	
	if( bEnable )
	{
		m_emStatus = emStatusNormal;
	}
	else
	{
		m_emStatus = emStatusBtnDisable;
	}
	UpdateUI();		
	return bRet;  
}

void CTransparentBtn::SetTextAlign( StringAlignment emTextAlign, BOOL bInvalidate /* = FALSE */ )
{	  
	m_cStringFormat.SetAlignment( emTextAlign );	
	if ( bInvalidate )
	{
		UpdateUI();
	}	
}

void CTransparentBtn::MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint )
{
	CButton::MoveWindow( x, y, nWidth, nHeight, bRepaint );	
	if ( bRepaint )
	{
		UpdateUI();
	}
}

void CTransparentBtn::MoveWindow(LPCRECT lpRect, BOOL bRepaint )
{
	CButton::MoveWindow( lpRect, bRepaint );
	if ( bRepaint )
	{
		UpdateUI();
	}	
}

void CTransparentBtn::SetFont( unsigned int dwFontSize /* = 18  */, CString strFontFamily /* = */ , BOOL bInvalidate )
{
	m_pFont = CSrcManage::GetFont( strFontFamily, dwFontSize );
	if ( bInvalidate )
	{
		UpdateUI();
	}
}

void CTransparentBtn::SetImage( CString strFolder, BOOL bInvalidate /* = FALSE */ )
{
	String strFile = strFolder + "//" + CTransparentBtn::strNormalImage;
	m_pImgNormal = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentBtn::strPressImage;
	m_pImgPress = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentBtn::strDisableImage;
	m_pImgDisable = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentBtn::strOverImage;
	m_pImgOver = CSrcManage::GetImage( strFile.c_str() );
	if ( NULL != m_pImgOver )
	{
		m_bImageOver = TRUE;
	}
	if ( bInvalidate )
	{
		UpdateUI();
	}	
}
  
void CTransparentBtn::SetImage( UINT nImgNormalID, UINT nImgPressID, UINT nImgDisableID, BOOL bInvalidate,const CString& strImgType)
{
	m_pImgNormal  = CSrcManage::GetImage( nImgNormalID, strImgType );
	m_pImgPress   = CSrcManage::GetImage( nImgPressID, strImgType );
	m_pImgDisable = CSrcManage::GetImage( nImgDisableID, strImgType );
 
}


CSize CTransparentBtn::GetImageSize()
{
    CSize sz(0);
    if ( m_pImgNormal != NULL )
    {
        sz.cx = m_pImgNormal->GetWidth();
        sz.cy = m_pImgNormal->GetHeight();
    }
    
    return sz;
}

void CTransparentBtn::ShowText( BOOL bShow )
{
	m_bShowText = bShow;
	UpdateUI();
}

void CTransparentBtn::UpdateUI( BOOL bDrawImmediatly /*= FALSE*/  )
{
	if ( m_hParentWnd != NULL )
	{    
		if ( bDrawImmediatly )
		{
			NOTIF_PARENT_WND_IMMEDIATLY_DRAW
		}
		else
		{
		    NOTIF_PARENT_WND
		}
	}
}

void CTransparentBtn::OnTimer( UINT nIDEvent )
{
    if( m_nTimer == nIDEvent )
    {   
        GetParent()->PostMessage( WM_BTN_HOLD, (WPARAM)GetSafeHwnd(), NULL );
        PostMessage( WM_BTN_HOLD, NULL, NULL );
    }
}


void CTransparentBtn::OnEnable(BOOL bEnable)
{
    if( bEnable )
    {
        m_emStatus = emStatusNormal;
    }
    else
    {
        m_emStatus = emStatusBtnDisable;
	}

    CWnd::OnEnable(bEnable);
}

LRESULT CTransparentBtn::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{
	if( IsWindowEnabled() && m_emStatus != emStatusNormal )
    {
		m_emStatus = emStatusNormal;
		NOTIF_PARENT_WND
    }
	m_bMouseTrack = TRUE;
	return S_OK;
}

LRESULT CTransparentBtn::OnMouseHover( WPARAM wParam, LPARAM lParam )
{	
	if ( IsWindowEnabled() && m_emStatus == emStatusNormal )
	{
		m_emStatus = emStatusBtnOver;					
		NOTIF_PARENT_WND			
	}
	return S_OK;
}

//父窗口隐藏了，按钮状态置为正常 Bug00167582 dyy
LRESULT CTransparentBtn::OnParentHide( WPARAM wParam, LPARAM lParam )
{	
    if ( IsWindowEnabled() && m_emStatus != emStatusNormal )
    {
        m_emStatus = emStatusNormal;					
        //NOTIF_PARENT_WND			
    }
    return S_OK;
}
