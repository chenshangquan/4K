// TransparentBaseWnd.cpp : implementation file
//

#include "stdafx.h"
#include "uiexBaseData.h"
#include "transparenBaseWnd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseWnd dialog
const CString CTransparentBaseWnd::strLeft = "Left.png";
const CString CTransparentBaseWnd::strMid = "Middle.png";
const CString CTransparentBaseWnd::strRight = "Right.png";
const CString CTransparentBaseWnd::strTop = "Top.png";
const CString CTransparentBaseWnd::strBottom = "Bottom.png";

std::vector<CWnd*> CTransparentBaseWnd::m_vctIgnoreWnd;

PFN_UpdateLayeredWindow CTransparentBaseWnd::m_s_pfnUpdateLayeredWindow = NULL;

CTransparentBaseWnd::CTransparentBaseWnd(CRect rcWnd, CWnd* pWnd,DWORD dStyle, CString strUI,
								 UINT nID, DWORD dwExStyle, int nTrans /* = 255 */,BOOL bCanMove /* = FALSE */, BOOL bStretchImage,CString strName /* = "" */ )
: CBaseWnd( strName, rcWnd, pWnd, dStyle, dwExStyle, nID )
{  
	m_bDeleteImg = false;
    m_pImageBK = NULL;
    m_bTransparentWithoutBK = FALSE;
    m_bReadyToRedrawUI = FALSE;
    m_bRedrawUIImediately = FALSE;
	m_byteSourceConstantAlpha = nTrans;
 
    m_bCanMove = FALSE;
    m_bAutoHide = FALSE;
    m_hBindWnd = 0;
    m_strImgPath.Empty();
	m_hDcMem = NULL;
	m_hBtMap = NULL;

	HMODULE hUser32Dll = ::GetModuleHandle( _T("user32.dll") );
    ASSERT(hUser32Dll);

	if( NULL == m_s_pfnUpdateLayeredWindow )
    {
        m_s_pfnUpdateLayeredWindow = (PFN_UpdateLayeredWindow)::GetProcAddress( hUser32Dll, "UpdateLayeredWindow" );
        ASSERT(m_s_pfnUpdateLayeredWindow);
	}
	
	//2012-7-10 by yjj
	if ( hUser32Dll )
	{
		FreeLibrary( hUser32Dll );
	}

	::SetWindowLong( m_hWnd, GWL_EXSTYLE, GetWindowLong( m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED );
    if ( m_pImageBK != NULL  )
    {  
        RedrawUI();
    }
}


CTransparentBaseWnd::~CTransparentBaseWnd()
{
	if ( m_bDeleteImg && m_pImageBK != NULL )
	{
		delete m_pImageBK;
	}
	m_vctIgnoreWnd.clear();

	if ( NULL != m_hDcMem )
	{
		::DeleteDC ( m_hDcMem );
		m_hDcMem = NULL;
	}

	if ( NULL != m_hBtMap )
	{
		::DeleteObject( m_hBtMap ); 
		m_hBtMap = NULL;
	}

	
}

BEGIN_MESSAGE_MAP(CTransparentBaseWnd, CBaseWnd)
	//{{AFX_MSG_MAP(CTransparentBaseDlg)
    ON_WM_TIMER()
    ON_WM_SHOWWINDOW()
    ON_WM_ERASEBKGND()
    ON_WM_ACTIVATE()
    ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
    ON_WM_SETCURSOR()
	//ON_WM_PAINT()
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
    ON_MESSAGE( WM_BIND_WND, OnBindWnd )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseWnd message handlers
void CTransparentBaseWnd::OnTimer(UINT nIDEvent) 
{
	if ( nIDEvent == 1 )
	{
		m_bReadyToRedrawUI = FALSE;
		KillTimer( 1 );
		
		RedrawUI();
	}

    CWnd::OnTimer( nIDEvent );
}

BOOL CTransparentBaseWnd::OnEraseBkgnd(CDC* pDC) 
{
    PostMessage( WM_REDRAW_UI, NULL, NULL );

	return TRUE;
    //return CWnd::OnEraseBkgnd(pDC);
}

void CTransparentBaseWnd::OnPaint() 
{
    
}

LRESULT CTransparentBaseWnd::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{  

    if ( m_pImageBK == NULL && FALSE == m_bTransparentWithoutBK )
    {
        return S_FALSE;
    }

//2011-9-16 隐藏的时候也绘制，防止再次显示的时候闪烁出原界面
//     if ( IsWindowVisible() == FALSE )
//     {
//         return S_FALSE;
//     }

	DWORD dwStyle = GetStyle();
	if ( dwStyle & WS_CHILD && GetParent() != NULL )
	{
		if ( !IsWindowVisible() )
		{
			return S_OK;
		}
		
		Graphics *pGraphics = (Graphics*)wParam;
		
		if ( pGraphics == NULL )
		{
			// 为空的话，则是由子控件发来的，需要再向父窗口转发
			CWnd* pParent = GetParent();
			if ( pParent != NULL )
			{
				pParent->SendMessage( WM_REDRAW_UI, wParam, lParam );
			} 
			return S_FALSE;
		}
		
		if ( 0 != m_pImageBK )
		{   
			CRect cRect;
			GetWindowRect( &cRect );
			POINT point = cRect.TopLeft(); 
			
            if ( NULL != GetParent() )
            {
			    GetParent()->ScreenToClient( &point ); 
            }
			
			pGraphics->DrawImage( m_pImageBK, point.x, point.y, m_pImageBK->GetWidth(), m_pImageBK->GetHeight() );			
		}
	}
	else
	{
		 RedrawUI();
	}

	return S_OK;
/*
    if ( TRUE == m_bRedrawUIImediately )
    {
        RedrawUI();

        return S_OK;
    }

    // 控制刷新，提高效率
    if ( TRUE == m_bReadyToRedrawUI )
    {
     //   TRACE( "[CTransparentBaseDlg::OnRedrawUI] m_bReadyToRedrawUI = TRUE\n" );

        return S_OK;
    }

    m_bReadyToRedrawUI = TRUE;
    SetTimer( 1, 20, NULL );

   return S_OK; 
*/
}

void CTransparentBaseWnd::RedrawUI()
{        
    if ( m_pImageBK == NULL && FALSE == m_bTransparentWithoutBK )
    {  
        //PrtMsg("\n[CTransparentBaseDlg::RedrawUI]: return: m_pImageBK == NULL && FALSE == m_bTransparentWithoutBK   handle=%d \n ", m_hWnd);
        return;
    } 

//2011-9-16 隐藏的时候也绘制，防止再次显示的时候闪烁出原界面
//     if( !IsWindowVisible())
//     {   
//         //PrtMsg("\n[CTransparentBaseDlg::RedrawUI]: return: !IsWindowVisible()  handle=%d \n ", m_hWnd);
//         return;
//     }
    
    RECT rc;
    ::GetWindowRect( m_hWnd, &rc );
    POINT ptSrc = { 0, 0 };
    POINT ptWinPos = { rc.left, rc.top };
    SIZE szWin;
//     if ( m_bTransparentWithoutBK == FALSE && m_pImageBK != NULL )
//     { 
//         szWin.cx = m_pImageBK->GetWidth();
//         szWin.cy = m_pImageBK->GetHeight();
//     }
//     else
    {
        szWin.cx = rc.right - rc.left;
        szWin.cy = rc.bottom - rc.top;
    }

	if ( NULL == m_hDcMem )
	{
		InitMemDC();
	}

	HDC hDC = ::GetDC( GetSafeHwnd() );

    BLENDFUNCTION stBlend = { AC_SRC_OVER, 0, m_byteSourceConstantAlpha, AC_SRC_ALPHA };	

	if( NULL != m_hDcMem )     
    {   
		Graphics graph( m_hDcMem );

        graph.Clear( Color( 0, 0, 0, 0 ) );

        graph.SetSmoothingMode( SmoothingModeHighQuality );
        
       
        //解决隐藏界面后更改显示方案 再次显示出来会闪烁的问题
        if ( IsWindowVisible() )
        { 
            if ( NULL != m_pImageBK )
            {
                graph.DrawImage( m_pImageBK, 0, 0, szWin.cx, szWin.cy );
                // PrtMsg("\n[CTransparentBaseDlg::RedrawUI]graph.DrawImage:width:%d  height:%d\n",szWin.cx, szWin.cy  );
            }
            
            
            // 绘制所有子窗口
            DrawChildWnd( &graph, GetSafeHwnd() );
        }
        

        m_s_pfnUpdateLayeredWindow( m_hWnd,
                                    hDC,
                                    &ptWinPos,
                                    &szWin,
                                    m_hDcMem,
                                    &ptSrc,
                                    0,
                                    &stBlend,
                                    ULW_ALPHA
                                   );

    }

	::ReleaseDC( GetSafeHwnd(), hDC );
}

void CTransparentBaseWnd::DrawChildWnd( Graphics *pGraphics, HWND hParentWnd )
{
    HWND hwndChild = ::GetWindow( hParentWnd, GW_CHILD ); 
     

    while( hwndChild != NULL )
    {       
        // 通知子窗口进行绘制
        ::SendMessage( hwndChild, WM_REDRAW_UI, (WPARAM)pGraphics, (LPARAM)m_hWnd );
         
        DrawChildWnd( pGraphics, hwndChild );
// #ifdef _DEBUG
//         CString strWindowText;
//         char abyText[128] = { 0 };
//         ::GetWindowText( hwndChild, abyText, 128 );
//         strWindowText = abyText;
//         TRACE( strWindowText );
// #endif // _DEBUG

        hwndChild = ::GetWindow( hwndChild, GW_HWNDNEXT );
    }
}

void CTransparentBaseWnd::OnShowWindow(BOOL bShow, UINT nStatus) 
{   
    if ( m_hBindWnd != 0 && !bShow )
    {
        // 如果有绑定的窗口，则通知绑定触发绑定窗口 
        CPoint   mousepos; 
        ::GetCursorPos(&mousepos); 
        CPoint   CurPos(mousepos);

        ::ScreenToClient(m_hBindWnd, &mousepos );

        CRect rect;
        ::GetClientRect(m_hBindWnd, &rect );
        if ( !rect.PtInRect( mousepos ) )
        {     
            ::SendMessage(m_hBindWnd, WM_BIND_WND_HIDE, 0, 0 );  
        }   
    }

    CWnd::OnShowWindow(bShow, nStatus);

  
    // TODO: Add your message handler code here
   // if ( TRUE == bShow )  2011-9-16 隐藏的时候也绘制，防止再次显示的时候闪烁出原界面
    {
        PostMessage( WM_REDRAW_UI, NULL, NULL );
    }

}

int CTransparentBaseWnd::GetWindowWidth()
{
	if ( m_pImageBK == NULL )
	{
		return 0;
	}
	return m_pImageBK->GetWidth();
}

int CTransparentBaseWnd::GetWindowHeight()
{
	if ( m_pImageBK == NULL )
	{
		return 0;
	}
	return m_pImageBK->GetHeight();
}



void CTransparentBaseWnd::SetImage( CString strPath, BOOL bInvalidate /* = FALSE */ )
{
   	
    //	if ( strPath.IsEmpty() || strPath.Find( '.' ) >= 0 )
    // 	{
    // 		m_pImage = CSrcManage::GetImage( strPath );		
    // 	}
   
    //如果已经加载过相同路径的图片则直接返回  2011-10-11 by yjj 
    if ( !m_strImgPath.IsEmpty() && strPath == m_strImgPath && m_pImageBK != NULL )
    {
        return;
    }
    m_strImgPath = strPath;

	if ( m_pImageBK != NULL && m_bDeleteImg )
	{ 
		delete m_pImageBK  ;
		m_pImageBK = NULL; 
		
    }
   
    if ( strPath.Find( "windowBkg" ) >= 0 )
    {   
		m_bDeleteImg = true;
        String strFile = strPath + "\\" + CTransparentBaseWnd::strLeft;
        m_pImgLeft = CSrcManage::GetImage( strFile.c_str() );
        strFile = strPath + "\\" + CTransparentBaseWnd::strMid;
        m_pImgMiddle = CSrcManage::GetImage( strFile.c_str() );
        strFile = strPath + "\\" + CTransparentBaseWnd::strRight;
        m_pImgRight = CSrcManage::GetImage( strFile.c_str() );
        
        CRect cRect;
        this->GetWindowRect( &cRect );
        
        if ( m_pImageBK == NULL )
        {
            m_pImageBK = CSrcManage::MosaicHoriImage( cRect,m_pImgLeft, m_pImgRight, m_pImgMiddle );
        }
        
    }
    else if ( strPath.Find( "callDlgBkg" ) >= 0  || strPath.Find( "callDlgBkgEx" ) >= 0)
    {   
        
        String strFile = strPath + "\\" + CTransparentBaseWnd::strTop;
        m_pImgLeft = CSrcManage::GetImage( strFile.c_str() );
        strFile = strPath + "\\" + CTransparentBaseWnd::strMid;
        m_pImgMiddle = CSrcManage::GetImage( strFile.c_str() );
        strFile = strPath + "\\" + CTransparentBaseWnd::strBottom;
        m_pImgRight = CSrcManage::GetImage( strFile.c_str() );
        
        CRect cRect;
        this->GetWindowRect( &cRect ); 
         
        m_bDeleteImg = true;
        m_pImageBK = CSrcManage::MosaicVertImage( cRect,m_pImgLeft, m_pImgRight, m_pImgMiddle );
     
    }
    else
    {   
		m_bDeleteImg = false;
        m_pImageBK = CSrcManage::GetImage( strPath );      
    }
    SetImage( m_pImageBK, bInvalidate );
}

void CTransparentBaseWnd::SetImage( Image* pImage, BOOL bInvalidate /* = FALSE */ )
{   
    m_pImageBK = pImage;

    if ( bInvalidate == TRUE )
    {
        OnRedrawUI( 0, 0 );
    }
}

void CTransparentBaseWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default


    if (m_bCanMove)
    {
        //禁止显示移动矩形窗体框
        ::SystemParametersInfo(SPI_SETDRAGFULLWINDOWS,TRUE,NULL,0);
        //非标题栏移动整个窗口
        PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y)); 
    }
   CWnd::OnLButtonDown(nFlags, point);
}



void CTransparentBaseWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
    if ( m_bAutoHide && nState == WA_INACTIVE )
    {
        bool bChildActivate = false;       
        
        //如果是Owner窗口，不隐藏
        CWnd* pWndTemp = pWndOther;
        while ( pWndTemp != NULL )
        {
            if ( pWndTemp == this )
            {
                bChildActivate = true;
                break;
            }
            pWndTemp = pWndTemp->GetOwner();	
        }
        if ( bChildActivate )
        {
            return;
        }  
        
        
        this->PostMessage(WM_SHOWWINDOW,FALSE,SW_OTHERUNZOOM );
        
        //隐藏后，焦点还给Owner窗口 
        HWND hOwner = this->m_hWndOwner;
        pWndTemp  = FromHandle(hOwner);
        if (  pWndTemp != NULL  )
        {
            // pWndTemp->SetFocus(); 
            pWndTemp->PostMessage( WM_SETFOCUS, 0, 0 );
        }
    }
    
    CWnd::OnActivate(nState, pWndOther, bMinimized); 
}  
 


void CTransparentBaseWnd::AddIgnoreWnd( CWnd* pWnd )
{
    vector<CWnd*>::iterator iter = m_vctIgnoreWnd.begin();
    while( iter != m_vctIgnoreWnd.end() )
    {
        if ( *iter == pWnd )
        {
            return;
        }
        iter++;
    }
    m_vctIgnoreWnd.push_back( pWnd );
}

 
LRESULT CTransparentBaseWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    
    return CWnd::DefWindowProc(message, wParam, lParam);
}

LRESULT CTransparentBaseWnd::OnBindWnd( WPARAM wParam, LPARAM lParam )
{
    HWND bindWnd = (HWND)wParam;
    m_hBindWnd = bindWnd;
    return S_OK;
}




void CTransparentBaseWnd::InitMemDC()
{  	
	if ( NULL != m_hDcMem )
	{
		::DeleteDC ( m_hDcMem ); 
	}
	
	if ( NULL != m_hBtMap )
	{
		::DeleteObject( m_hBtMap )  ; 
	}
	
	RECT rc;
    ::GetWindowRect( m_hWnd, &rc );
	SIZE szWin;
	szWin.cx = rc.right - rc.left;
	szWin.cy = rc.bottom - rc.top ; 
	
	HDC hDc = ::GetDC( GetSafeHwnd() );
    m_hDcMem = ::CreateCompatibleDC(hDc);
	
    BITMAPINFOHEADER stBmpInfoHeader = { 0 };   
    int nBytesPerLine = ((szWin.cx * 32 + 31) & (~31)) >> 3;
    stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);   
    stBmpInfoHeader.biWidth = szWin.cx;   
    stBmpInfoHeader.biHeight = szWin.cy;   
    stBmpInfoHeader.biPlanes = 1;
    stBmpInfoHeader.biBitCount = 32;   
    stBmpInfoHeader.biCompression = BI_RGB;   
    stBmpInfoHeader.biClrUsed = 0;   
    stBmpInfoHeader.biSizeImage = nBytesPerLine * szWin.cy;	
	
    PUINT32 pvBits = NULL;   
    m_hBtMap = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, (LPVOID*)&pvBits, NULL, 0);
	
    ASSERT(m_hBtMap != NULL);
    if(m_hBtMap)   
    {   
		::SelectObject( m_hDcMem, m_hBtMap); 
	}
	
	::ReleaseDC( GetSafeHwnd(), hDc );
}


void CTransparentBaseWnd::OnSize(UINT nType, int cx, int cy) 
{
	CBaseWnd::OnSize(nType, cx, cy);
	
	InitMemDC();
}


BOOL CTransparentBaseWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{   
    //解决 Bug00096452 系统时间设置点击编辑，选中日期编辑框，点击旁边的日历选择日期，此时鼠标显示工字型 2012-7-26 by yjj
    HCURSOR hCurOld = GetCursor();  
    HCURSOR hCur = LoadCursor( NULL, IDC_ARROW ); 
    if ( hCurOld != hCur )
    {
        SetCursor( hCur );
    }
    
    return CWnd::OnSetCursor(pWnd, nHitTest, message);
}