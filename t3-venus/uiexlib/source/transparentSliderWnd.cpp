// transparentSliderWnd.cpp: implementation of the CTransparentSliderWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "slider.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


const CString CTransparentSliderWnd::strNormalLeft = "NormalLeft.png";
const CString CTransparentSliderWnd::strNormalMid = "NormalMid.png";
const CString CTransparentSliderWnd::strNormalRight = "NormalRight.png";
const CString CTransparentSliderWnd::strHighLightLeft = "HighLightLeft.png";
const CString CTransparentSliderWnd::strHighLightMid = "HighLightMid.png";
const CString CTransparentSliderWnd::strHighLightRight = "HighLightRight.png";
const CString CTransparentSliderWnd::strThumbNormal = "ThumbNormal.png";
const CString CTransparentSliderWnd::strThumbPress = "ThumbPress.png";
/*template<> WNDPROC TransparentAssist<CTransparentSliderWnd>::m_pWndProc = NULL;*/

//disable 图标
const CString CTransparentSliderWnd::strDisableLeft = "DisableLeft.png";
const CString CTransparentSliderWnd::strDisableMid = "DisableMid.png";
const CString CTransparentSliderWnd::strDisableRight = "DisableRight.png";
const CString CTransparentSliderWnd::strDisableHighLightLeft = "DisableHighLightLeft.png";
const CString CTransparentSliderWnd::strDisableHighLightMid = "DisableHighLightMid.png";
const CString CTransparentSliderWnd::strDisableHighLightRight = "DisableHighLightRight.png";
const CString CTransparentSliderWnd::strThumbDisable = "ThumbDisable.png";

const CString CTransparentSliderWnd::strBubble = "Bubble.png";
static UINT g_wTimer = 0;

CTransparentSliderWnd::CTransparentSliderWnd(CString strName, CString strUI, CRect rcWnd, CWnd* pWnd, UINT nID, DWORD dStyle, DWORD dwExStyle) 
: CTransparentBaseWnd( rcWnd, pWnd, dStyle, strUI, nID ),m_rectfThumbRect()
{
    m_pImgNormalLeft = NULL;
    m_pImgNormalMiddle = NULL;
    m_pImgNormalRight = NULL;
    
    m_pImgHighLightLeft = NULL;
    m_pImgHighLightMiddle = NULL;
    m_pImgHighLightRight = NULL;
    
    m_pImgThumbNormal = NULL;
    m_pImgThumbPress = NULL;
    
    
    //disable
    m_pImgDisableLeft = NULL;
    m_pImgDisableMid  = NULL ;
    m_pImgDisableRight = NULL ;
    
    m_pImgDisableHighLightLeft = NULL ;
    m_pImgDisableHighLightMid = NULL ;
    m_pImgDisableHighLightRight = NULL ;
    
    m_pImgThumbDisable = NULL ;
	m_pImgBubble = NULL;

    m_emStyle =   emStyleHorz  ;
    
    m_nMaxOffset = 0;
 
    m_nMax = 0; 
    m_nMin = 0;
    m_nPos = 0;
    m_ptMouseLast.x = 0 ;
    m_ptMouseLast.y = 0 ;
    m_ptMouseNow.x = 0 ;
    m_ptMouseNow.y = 0 ;
    
    m_bLBtnDown = FALSE;
	m_bDownInThumb = TRUE;
}

CTransparentSliderWnd::~CTransparentSliderWnd()
{

}


BEGIN_MESSAGE_MAP(CTransparentSliderWnd, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CTransparentCheckButton)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_SIZE()
ON_WM_TIMER()
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

    

void CTransparentSliderWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{  
    if (  !IsWindowVisible()  )
    {
       return ;
    }
	//设置焦点
	HWND hFocusWnd = ::GetFocus();
	if ( hFocusWnd != m_hWnd )
	{   
		this->SetFocus();
	}	

	CRect rect;
    GetClientRect( &rect );
	if ( !rect.PtInRect( point) )
	{
		return;
	}

	m_bLBtnDown = TRUE;
	
	PointF pointf;
	pointf.X = (float)point.x;
	pointf.Y = (float)point.y;
	if ( !m_rectfThumbRect.Contains( pointf) )   //添加滑块在rect里面点到哪里便移动那里----JYY
	{   
// 		TRACE("\nm_rectfThumbRect=(%d %d %d %d)  mouse=(%d,%d)\n", 
// 			m_rectfThumbRect.X, m_rectfThumbRect.Y,m_rectfThumbRect.X+m_rectfThumbRect.Width,
// 			m_rectfThumbRect.Y+m_rectfThumbRect.Height,point.x,point.y);

		m_bDownInThumb = FALSE;
		CRect rect;
		GetClientRect( &rect );
		if ( point.x > rect.right )
		{
			point.x  =  rect.right ; 
		}
		
		if ( point.x < rect.left )
		{
			point.x = rect.left;
		}
		
		if ( point.y > rect.bottom )
		{
			point.y = rect.bottom  ;
		}
		
		if ( point.y < rect.top )
		{
			point.y = rect.top ; 
		}
		m_ptMouseLast = m_ptMouseNow;
		m_ptMouseNow = point;
		UpdateThumbPos(); 
		SetCapture();
		//PostMessage( SLIDER_CHANGED,  m_nPos);
		NOTIF_PARENT_WND
		return;
	}
//    m_bLBtnDown = TRUE; 

//    m_ptMouseLast = m_ptMouseNow;
//    m_ptMouseNow = point;

    SetTimer( g_wTimer, 200 ,NULL ) ; 
    NOTIF_PARENT_WND
    SetCapture();	
}

void CTransparentSliderWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    if (  !IsWindowVisible()  )
    {
        return ;
    }


    if ( !m_bLBtnDown )
    {
        return;
    }

	PointF pointf;
	pointf.X = (float)point.x;
	pointf.Y = (float)point.y;

	CRect rect;
	GetClientRect( &rect );

	if ( !rect.PtInRect( point) )		//鼠标在控件范围外面
	{
//		KillTimer( g_wTimer );
//      防止音量值拖拽至最大后无法往回拖
// 		if ( GetCapture() == this )
// 		{
// 			ReleaseCapture();
// 		}
//		m_bLBtnDown = FALSE;
		if ( point.x > rect.right )
		{
			point.x  =  rect.right ; 
		}
		
		if ( point.x < rect.left )
		{
			point.x = rect.left;
		}
		
		if ( point.y > rect.bottom )
		{
			point.y = rect.bottom  ;
		}
		
		if ( point.y < rect.top )
		{
			point.y = rect.top ; 
		}
		m_ptMouseLast = m_ptMouseNow;
		m_ptMouseNow = point;
		
		UpdateThumbPos();  
		
	    NOTIF_PARENT_WND 
		//PostMessage( SLIDER_CHANGED,  m_nPos);

		return;
	}

	if ( point.x > rect.right )
	{
		point.x  =  rect.right ; 
	}
	
	if ( point.x < rect.left )
	{
		point.x = rect.left;
	}
	
	if ( point.y > rect.bottom )
	{
		point.y = rect.bottom  ;
	}
	
	if ( point.y < rect.top )
	{
		point.y = rect.top ; 
	}
	
	m_ptMouseLast = m_ptMouseNow;
	m_ptMouseNow = point;

    UpdateThumbPos();  

    NOTIF_PARENT_WND 
}

void CTransparentSliderWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{  
    KillTimer( g_wTimer ); 
	if ( m_bDownInThumb )
	{
		int nLastPos = m_nPos;
		m_nPos = GetPos();
		if ( nLastPos != m_nPos )
		{
			PostMessage( SLIDER_CHANGED, m_nPos );
		}
	}

    if ( GetCapture() == this )
    {
        ReleaseCapture();
	}
 
    if ( !IsWindowVisible() )
    {   
        m_bLBtnDown = FALSE;
        return ;
    } 

    if ( !m_bLBtnDown )
	{
		return;
    }   
   
    m_bLBtnDown = FALSE; 

    
	if (!m_bDownInThumb)
	{    
		m_nPos = GetPos();
		PostMessage( SLIDER_CHANGED,  m_nPos);
		m_bDownInThumb = TRUE;
	}
	
	NOTIF_PARENT_WND    
}

LRESULT  CTransparentSliderWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    /*
    if ( message == WM_TOUCH_BUTTONDOWN )
    {
        int nX = LOWORD( lParam );
        int nY = HIWORD( lParam );
        CPoint point( nX, nY );
        if ( !m_rectThumbRect.PtInRect( point ) )
        {    
            //	m_emThumbStatus = emThumbStatusSetFocus;
            return;
        }
        
        m_bLBtnDown = TRUE; 
        
        m_ptMouseLast = m_ptMouseNow;
        m_ptMouseNow = point;
        
        SetTimer( g_wTimer, 200 ,NULL ) ; 
        NOTIF_PARENT_WND
	    SetCapture();  
    }
    
    */
    return CWnd::DefWindowProc(message, wParam, lParam);
}


void CTransparentSliderWnd::OnTimer(UINT nIDEvent) 
{  
    if ( g_wTimer == nIDEvent )
    {
        int nLastPos = m_nPos  ; 
        m_nPos = GetPos();

// 		if ( m_nPos > m_nMax )
// 		{
// 			m_nPos = m_nMax;
// 		}
// 
// 		if ( m_nPos < m_nMin )
// 		{
// 			m_nPos = m_nMin;
// 		}

        if ( m_nPos != nLastPos )
        { 
            PostMessage( SLIDER_CHANGED,  m_nPos); 
        }

    } 
    
	CTransparentBaseWnd::OnTimer(nIDEvent);

   
}


 

void CTransparentSliderWnd::SetThumbPos( /*int*/float nOffset  )
{  
   UINT nHeight = 0;
   UINT nWidth = 0;

   Image * pImage = NULL; 
   if ( m_bLBtnDown )
   {
        pImage =  m_pImgThumbPress;
   }
   else
   {
        pImage =  m_pImgThumbNormal;
   }


   if ( NULL == pImage  || NULL == m_pImgThumbNormal  )
   {
      return; 
   }

   nHeight = pImage->GetHeight();
   nWidth = pImage->GetWidth();

   m_rectfThumbRect.Width =  m_pImgThumbNormal->GetWidth() ;
   m_rectfThumbRect.Height = m_pImgThumbNormal->GetHeight();
  
   CRect rectWnd;
   GetClientRect( &rectWnd ); 

   if ( emStyleHorz == m_emStyle )
   {
	   m_rectfThumbRect.X = nOffset - rectWnd.left;
	    
	   if ( m_rectfThumbRect.X < rectWnd.left )
	   {
		   m_rectfThumbRect.X = rectWnd.left ;
	   }

	   
	   if ( m_rectfThumbRect.X+m_rectfThumbRect.Width > rectWnd.right )
	   { 
		   m_rectfThumbRect.X = rectWnd.right -  m_pImgThumbNormal->GetWidth() ;
	   }
	   
	   
	   m_rectfThumbRect.Y =  ( rectWnd.Height() - nHeight )/2;
   
   }
   else
   {//添加竖直方向 2013.1.24 yjj
	   m_rectfThumbRect.Y = nOffset - rectWnd.top;
	   if ( m_rectfThumbRect.Y < rectWnd.top )
	   {
		   m_rectfThumbRect.Y = rectWnd.top ;
	   } 
	   
	   if ( m_rectfThumbRect.Y + m_rectfThumbRect.Height > rectWnd.bottom )
	   {
		   m_rectfThumbRect.Y  = rectWnd.bottom - m_rectfThumbRect.Height;
	   } 
	  
	   m_rectfThumbRect.X =  ( rectWnd.Width() - nWidth )/2; 
	    
   }
  
   
  
}

void CTransparentSliderWnd::UpdateThumbPos()
{   
    UINT nHeight = 0;
    UINT nWidth = 0;
    if ( m_pImgThumbNormal == NULL )
    {
		return;
       
    }

	nHeight = m_pImgThumbNormal->GetHeight();
    nWidth = m_pImgThumbNormal->GetWidth();
    
	m_rectfThumbRect.Width =  nWidth ;
    m_rectfThumbRect.Height = nHeight;


    CRect rectWnd;
    GetClientRect( &rectWnd );
    
	if ( emStyleHorz == m_emStyle )
	{
	
		m_rectfThumbRect.X   =  m_ptMouseNow.x -  rectWnd.left - nWidth/2   ;

		if ( m_ptMouseNow.x < rectWnd.left + nWidth/2 )
		{
			m_rectfThumbRect.X = 0;
		}

		m_rectfThumbRect.Y  =  ( rectWnd.Height() - nHeight )/2;
		
		
		if (  m_rectfThumbRect.X  < rectWnd.left )
		{
		     m_rectfThumbRect.X  = rectWnd.left ; 
		} 
		if (  m_rectfThumbRect.X  + nWidth > rectWnd.right )
		{      
			m_rectfThumbRect.X =  rectWnd.right - nWidth;
		} 
	}
	else
	{//添加竖直方向 2013.1.24 yjj
		m_rectfThumbRect.X = ( rectWnd.Width() - nWidth )/2;
		m_rectfThumbRect.Y =   m_ptMouseNow.y -  rectWnd.top - nHeight/2 ;
		
		//判断当滑块滑动到最上边时候,将滑块的偏移量设为0 ---2013.3.7 JYY
		if ( m_ptMouseNow.y < rectWnd.top + nHeight/2 )
		{
			m_rectfThumbRect.Y = 0;
		}
		
		
//		if ( m_rectfThumbRect.Y < rectWnd.top )
//		{
//			m_rectfThumbRect.Y = rectWnd.top ; 
//		} 
		 
		
		if ( m_rectfThumbRect.Y + nHeight  > rectWnd.bottom )
		{      
			m_rectfThumbRect.Y = rectWnd.bottom - nHeight;		 
		}
	}

   
}

//根据当前的偏移量计算 slider对应的值，该值是相对于Range范围而言
float CTransparentSliderWnd::CalculatePos( /*int*/float nOffSet )
{ 
	int nRange = m_nMax - m_nMin;

	UINT nWidth = 0;
	if ( m_pImgThumbNormal != NULL )
	{ 
	   if ( emStyleHorz == m_emStyle )
	   {
		    nWidth = m_pImgThumbNormal->GetWidth();
		    float nPos =  m_nMin + ( (float)nOffSet/((float)m_nMaxOffset - (float)nWidth) * nRange ) ;//修正刻度从非0开始的情况，竖直方向未修正 20140213 景洋洋
			TRACE("\n[CTransparentSliderWnd::CalculatePos] range=%d maxoffset=%d offset=%f  return=%f\n",nRange,m_nMaxOffset,nOffSet,nPos);
			return nPos;
	   }
	   else
	   {//添加竖直方向 2013.1.24 yjj    -----jyy  调整两端
			nWidth = m_pImgThumbNormal->GetHeight();	
// 			if ( nOffSet <= nWidth/2 )
// 			{
// 			   nOffSet = 0;
// 			}
// 
// 			if ( nOffSet >= m_nMaxOffset - nWidth/3 )
// 			{
// 			   nOffSet = m_nMaxOffset;
// 			}
	   }      
	}

	float nPos  = 0;
	if ( 0 != m_nMaxOffset )
	{
	    nPos =  (float)nOffSet/((float)m_nMaxOffset-nWidth/* - (float)nWidth/2*/) * nRange ;
	}
    
	//保持跟界面获取的数值一致,后续整体添加升序降序调整
 	nPos =  m_nMax - nPos;
// 	if ( nPos > m_nMax )
// 	{
// 		nPos = m_nMax;
// 	}
// 	
// 	if ( nPos < m_nMin )
// 	{
// 		nPos = m_nMin;
// 	}
    TRACE("\n[CTransparentSliderWnd::CalculatePos] range=%d maxoffset=%d offset=%f  return=%f\n",nRange,m_nMaxOffset,nOffSet,nPos);
	return nPos;
}

//根据当前相对于range的值，来计算thumb 的偏移量
/*int*/float CTransparentSliderWnd::CalculateOffset( /*int*/float nPos )
{ 
    int nRange = m_nMax - m_nMin;
    UINT nWidth = 0;
    if ( m_pImgThumbNormal != NULL )
    { 
		if ( emStyleHorz == m_emStyle )
		{
			nWidth = m_pImgThumbNormal->GetWidth();
			
			int nPosOffset = nPos - m_nMin;	//修正刻度从非0开始的情况，竖直方向未修正 20140213 景洋洋
			if ( nPosOffset < 0 )
			{
				nPosOffset = 0;
			}

			float nOffset = (float)nPosOffset /nRange *  ( m_nMaxOffset - nWidth );			
			return nOffset;		
		}
		else
		{//添加竖直方向的滑块 2013.1.24 yjj
			nWidth = m_pImgThumbNormal->GetHeight();
			nPos = m_nMax - nPos;
		}
    }
	//对照函数CalculatePos(由偏移量算range值)相应调整,原计算方式为水平方向的计算公式
    float nOffset = (float)nPos /nRange *  ( m_nMaxOffset - nWidth );	
    return nOffset;
}

void CTransparentSliderWnd::OnSize(UINT nType, int cx, int cy)
{ 
    //如果thumb的高度大于当前设置slider的高度，则把 sliderWnd的高度调整为thumb的高度,否则显示不全thumb 
	if ( emStyleHorz == m_emStyle )
	{
		if ( m_pImgThumbNormal != NULL &&  m_pImgThumbNormal->GetHeight() >cy )
		{
			cy =  m_pImgThumbNormal->GetHeight();
			
			if ( m_pImgThumbPress != NULL && m_pImgThumbPress->GetHeight() > cy )
			{
				cy = m_pImgThumbPress->GetHeight();
			}
		}
	}
	else
	{//添加竖直方向的滑块 2013.1.24 yjj
		if ( m_pImgThumbNormal != NULL &&  m_pImgThumbNormal->GetWidth() >cx )
		{
			cx =  m_pImgThumbNormal->GetWidth();
			
			if ( m_pImgThumbPress != NULL && m_pImgThumbPress->GetWidth() > cx )
			{
				cx = m_pImgThumbPress->GetWidth();
			}
		}
	}
    

    CWnd::OnSize( nType, cx, cy );  

    UpdateMaxOffSet();
    SetThumbPos( 0 );
}

void CTransparentSliderWnd::UpdateMaxOffSet()
{
    CRect rect;
    GetClientRect( & rect );
	if ( emStyleHorz == m_emStyle )
	{
	   m_nMaxOffset = rect.Width();  
	}
	else
	{
	   m_nMaxOffset = rect.Height(); 
	}

}

LRESULT CTransparentSliderWnd::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    if ( IsWindowVisible() == FALSE )
    {
        return S_FALSE;
    }
    
    Graphics *pGraphics = (Graphics*)wParam;
    HWND hGraphWnd = (HWND )lParam;
    //  CWnd * pGraphWnd = FromHandle(hGraphWnd);
    if ( pGraphics == NULL || hGraphWnd == 0 )
    {
        return S_FALSE;
    } 
  

  //获取slider的风格  
	if (  emStyleVert == m_emStyle )
	{
		//垂直方向
		DrawVertSlider( pGraphics, hGraphWnd );
	}
	else
	{
		//水平方向
		DrawHorizSlider( pGraphics, hGraphWnd);
    } 

  
    return S_OK;
}


BOOL CTransparentSliderWnd::GetDrawImg( Image ** pImgThumb, Image ** pImgNormalLeft, Image ** pImgNormalMiddle, 
										Image ** pImgNormalRight, Image ** pImgHighLightLeft, Image ** pImgHighLightMiddle, 
										Image ** pImgHighLightRight )
{
	if ( IsWindowEnabled() )
    {
        if ( m_bLBtnDown )
        {
            *pImgThumb = m_pImgThumbPress;
        }
        else
        {
            *pImgThumb = m_pImgThumbNormal;
        }
		
		
        *pImgNormalLeft = m_pImgNormalLeft;
        *pImgNormalMiddle = m_pImgNormalMiddle;
        *pImgNormalRight = m_pImgNormalRight;
        
        *pImgHighLightLeft = m_pImgHighLightLeft;
        *pImgHighLightMiddle = m_pImgHighLightMiddle;
        *pImgHighLightRight = m_pImgHighLightRight;
		
    }
    else
    {
        *pImgThumb = m_pImgThumbDisable;
		
        *pImgNormalLeft = m_pImgDisableLeft;
        *pImgNormalMiddle = m_pImgDisableMid;
        *pImgNormalRight = m_pImgDisableRight;
        
        *pImgHighLightLeft = m_pImgDisableHighLightLeft;
        *pImgHighLightMiddle = m_pImgDisableHighLightMid;
        *pImgHighLightRight = m_pImgDisableHighLightRight;
    }

    if (  pImgThumb == NULL || pImgNormalLeft == NULL || pImgNormalMiddle == NULL || pImgNormalRight == NULL
		|| pImgHighLightLeft == NULL || pImgHighLightMiddle == NULL || pImgHighLightRight == NULL )
    {
        return S_FALSE;
    }

	return TRUE;
}
    
/*---------------------------------------------------------------------
* 功    能：绘制水平方向的slider
* 备    注： 
* 日期			版本		修改人		修改记录
* 2013.1.23    1.0         俞锦锦        创建
----------------------------------------------------------------------*/
void CTransparentSliderWnd::DrawHorizSlider( Graphics *pGraphics, HWND hGraphWnd)
{
	Image * pImgNormalLeft = NULL;
    Image * pImgNormalMiddle = NULL;
    Image * pImgNormalRight = NULL;
	
    Image * pImgHighLightLeft = NULL;
    Image * pImgHighLightMiddle = NULL;
    Image * pImgHighLightRight = NULL;
	
    Image *pImgThumb = NULL;
	
	BOOL bSucess = GetDrawImg( &pImgThumb, &pImgNormalLeft, &pImgNormalMiddle, 
		&pImgNormalRight, &pImgHighLightLeft, &pImgHighLightMiddle,  &pImgHighLightRight );
	if ( !bSucess )
	{ 
		AfxOutputDebugString( "\n[CTransparentSliderWnd::DrawHorizSlider]GetDrawImg false \n" );
		return ;
	}
	
    CRect cRect;
    GetClientRect( &cRect );
    POINT point = cRect.TopLeft();
    if ( pImgNormalLeft != NULL )
    {
        point.y = (cRect.Height() - pImgNormalLeft->GetHeight() )/2;
    }
	::ClientToScreen( GetSafeHwnd(), &point  );
	::ScreenToClient( hGraphWnd, &point );
	
 
	
	POINT tumbPos;
	tumbPos.x = (long)m_rectfThumbRect.X;  
	tumbPos.y  = ( cRect.Height() - pImgThumb->GetHeight()) /2;  
	::ClientToScreen( GetSafeHwnd(), &tumbPos  );
    ::ScreenToClient( hGraphWnd, &tumbPos);
    PointF thumPosF;
	thumPosF.X = tumbPos.x; 
    thumPosF.Y = tumbPos.y;
 
	
	// 绘制底图
	int nPosX = point.x  +  pImgNormalLeft->GetWidth();
	int nPosY = point.y ; 
	int nMiddleWidth = cRect.Width() -  pImgNormalLeft->GetWidth() -  pImgNormalRight->GetWidth();
	// 左
	pGraphics->DrawImage( pImgNormalLeft, point.x, nPosY,  pImgNormalLeft->GetWidth(), pImgNormalLeft->GetHeight() );
	// 右
	pGraphics->DrawImage( pImgNormalRight, point.x + cRect.Width() - pImgNormalRight->GetWidth(), nPosY, pImgNormalRight->GetWidth(), pImgNormalRight->GetHeight() );
	
	if ( nMiddleWidth <= 0 )
	{
		return ;
	}
	
	for ( unsigned int nIndex = 0; nIndex < ( nMiddleWidth / m_pImgNormalMiddle->GetWidth() ); nIndex++ )
	{
		pGraphics->DrawImage( pImgNormalMiddle, nPosX, nPosY, pImgNormalMiddle->GetWidth(), pImgNormalMiddle->GetHeight() );
		nPosX += pImgNormalMiddle->GetWidth();
	}
	pGraphics->DrawImage( pImgNormalMiddle, nPosX, nPosY, nMiddleWidth % pImgNormalMiddle->GetWidth(), pImgNormalMiddle->GetHeight() );
	
	// 绘制高亮的地方 
	if ( thumPosF.X > point.x )
	{
		// 左
		pGraphics->DrawImage( pImgHighLightLeft, point.x, nPosY, pImgHighLightLeft->GetWidth(), pImgHighLightLeft->GetHeight() );
		
		float tempX = thumPosF.X  + pImgThumb->GetWidth()/2 - pImgHighLightRight->GetWidth(); 
		if ( tempX < point.x )
		{
			tempX = point.x;
		}
		// 右
		pGraphics->DrawImage( pImgHighLightRight, tempX, (float)nPosY, pImgHighLightRight->GetWidth(), pImgHighLightRight->GetHeight() );
		
		nPosX = point.x + pImgHighLightLeft->GetWidth();
		nMiddleWidth = ( tempX - point.x );
		// 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
		for ( nIndex = 0; nMiddleWidth > 0 && nIndex < ( nMiddleWidth / pImgHighLightMiddle->GetWidth() ); nIndex++ )
		{
			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, pImgHighLightMiddle->GetWidth(), m_pImgHighLightMiddle->GetHeight() );
			nPosX += m_pImgHighLightMiddle->GetWidth();
		}
		if ( nMiddleWidth > 0 )
		{
			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, nMiddleWidth % pImgHighLightMiddle->GetWidth(), pImgHighLightMiddle->GetHeight() );
		} 
	} 
	
   
	// 绘制Thumb  
	pGraphics->DrawImage( pImgThumb,  thumPosF.X ,  thumPosF.Y , pImgThumb->GetWidth(), pImgThumb->GetHeight() );
}

/*---------------------------------------------------------------------
* 功    能：绘制竖直方向的slider
* 备    注： 
* 日期			版本		修改人		修改记录
* 2013.1.23    1.0         俞锦锦        创建
----------------------------------------------------------------------*/
void CTransparentSliderWnd::DrawVertSlider( Graphics *pGraphics, HWND hGraphWnd)
{
	Image * pImgNormalLeft = NULL;
    Image * pImgNormalMiddle = NULL;
    Image * pImgNormalRight = NULL;
	
    Image * pImgHighLightLeft = NULL;
    Image * pImgHighLightMiddle = NULL;
    Image * pImgHighLightRight = NULL;
	
    Image *pImgThumb = NULL;
	
	BOOL bSucess = GetDrawImg( &pImgThumb, &pImgNormalLeft, &pImgNormalMiddle, 
		&pImgNormalRight, &pImgHighLightLeft, &pImgHighLightMiddle,  &pImgHighLightRight );
	if ( !bSucess )
	{ 
		AfxOutputDebugString( "\n[CTransparentSliderWnd::DrawVertSlider]GetDrawImg false \n" );
		return ;
	}
	
    CRect cRect;
    GetClientRect( &cRect );
    POINT point = cRect.TopLeft();
    
	::ClientToScreen( GetSafeHwnd(), &point  );
	::ScreenToClient( hGraphWnd, &point );
 
	
	// 绘制底图 
	float nPosX = point.x + (cRect.Width() - pImgNormalLeft->GetWidth() )/2;  
	int nMiddleWidth = cRect.Height() -  pImgNormalLeft->GetHeight() -  pImgNormalRight->GetHeight();
	//底图上
	pGraphics->DrawImage( pImgNormalLeft,nPosX, (float)point.y,  pImgNormalLeft->GetWidth(), pImgNormalLeft->GetHeight() );
	// 底图下
	pGraphics->DrawImage( pImgNormalRight, nPosX, (float)(point.y + cRect.Height() - pImgNormalLeft->GetHeight() ) , pImgNormalRight->GetWidth(), pImgNormalRight->GetHeight() );
	
	if ( nMiddleWidth <= 0 )
	{
		return ;
	}
	//底图中间部分
	float nPosY = point.y + pImgNormalLeft->GetHeight(); 
	for ( unsigned int nIndex = 0; nIndex < ( nMiddleWidth / m_pImgNormalMiddle->GetHeight() ); nIndex++ )
	{
		pGraphics->DrawImage( pImgNormalMiddle, nPosX, nPosY, pImgNormalMiddle->GetWidth(), pImgNormalMiddle->GetHeight() );
		nPosY += pImgNormalMiddle->GetHeight();
	}
	pGraphics->DrawImage( pImgNormalMiddle, nPosX, nPosY, pImgNormalMiddle->GetWidth(), nMiddleWidth % pImgNormalMiddle->GetHeight() );
	

	// 绘制高亮的地方 
	POINT tumbPos;
	// 2013.3.7 修正竖直滑块绘制时按钮偏离 ----JYY
	tumbPos.x = ( cRect.Width() - pImgThumb->GetWidth() )/2;
	tumbPos.y = (long)m_rectfThumbRect.Y;
//	tumbPos.x = (long)m_rectfThumbRect.X;  
//	tumbPos.y  = ( cRect.Height() - pImgThumb->GetHeight()) /2;  
	::ClientToScreen( GetSafeHwnd(), &tumbPos  );
    ::ScreenToClient( hGraphWnd, &tumbPos);
   
	PointF thumPosF;
	thumPosF.X = tumbPos.x; 
    thumPosF.Y = tumbPos.y; 

	nPosX = point.x + (cRect.Width() - pImgHighLightLeft->GetWidth() )/2; 


	if ( NULL !=  pImgHighLightLeft &&  /*tumbPos.y > point.y*/tumbPos.y + pImgThumb->GetHeight() < point.y + cRect.bottom )
	{
		// 上
//		pGraphics->DrawImage( pImgHighLightLeft, nPosX, (float)point.y, pImgHighLightLeft->GetWidth(), pImgHighLightLeft->GetHeight() );
		
//		float tempy = tumbPos.y + pImgThumb->GetHeight()/2 - pImgHighLightRight->GetHeight() ; 
//		if ( tempy < point.y )
		{
//			tempy = point.y;
		}
		// 下
//		pGraphics->DrawImage( pImgHighLightRight, nPosX, tempy, pImgHighLightRight->GetWidth(), pImgHighLightRight->GetHeight() );
// 		float tempy = tumbPos.y - pImgThumb->GetHeight()/2 - pImgHighLightLeft->GetHeight() ; 
//		pGraphics->DrawImage( pImgHighLightLeft, nPosX, tempy, pImgHighLightLeft->GetWidth(), pImgHighLightLeft->GetHeight() );
// 
// 		nPosY = point.y + pImgHighLightLeft->GetHeight();
// 		nMiddleWidth = ( tempy - point.y );
// 		// 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
// 		for ( nIndex = 0; nMiddleWidth > 0 && nIndex < ( nMiddleWidth / pImgHighLightMiddle->GetHeight() ); nIndex++ )
// 		{
// 			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, pImgHighLightMiddle->GetWidth(), m_pImgHighLightMiddle->GetHeight() );
// 			nPosY += m_pImgHighLightMiddle->GetHeight();
// 		}
// 		if ( nMiddleWidth > 0 )
// 		{
// 			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, pImgHighLightMiddle->GetWidth(), nMiddleWidth % pImgHighLightMiddle->GetHeight() );
// 		} 		
		//下     --2013.4.18 修改slider的高亮显示方式从下往上   JYY
		pGraphics->DrawImage( pImgHighLightRight, nPosX, point.y + cRect.Height() - pImgHighLightRight->GetHeight(), pImgHighLightRight->GetWidth(), pImgHighLightRight->GetHeight() );		
		float tempy = tumbPos.y + pImgThumb->GetHeight() - pImgHighLightLeft->GetHeight() ; 
		if ( tempy < point.y )
		{
			tempy = point.y;
		}
		//上
		pGraphics->DrawImage( pImgHighLightLeft, nPosX, tempy, pImgHighLightLeft->GetWidth(), pImgHighLightLeft->GetHeight() );

		nPosY = point.y + cRect.Height() - pImgHighLightRight->GetHeight() - m_pImgHighLightMiddle->GetHeight();
		nMiddleWidth = point.y + cRect.bottom - tumbPos.y - pImgThumb->GetHeight()/* - pImgHighLightRight->GetHeight()*/;
		// 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
		for ( nIndex = 0; nMiddleWidth > 0 && nIndex < ( nMiddleWidth / pImgHighLightMiddle->GetHeight() ); nIndex++ )
		{
			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, pImgHighLightMiddle->GetWidth(), m_pImgHighLightMiddle->GetHeight() );
			nPosY -= m_pImgHighLightMiddle->GetHeight();
		}
		if ( nMiddleWidth > 0 )
		{
			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, pImgHighLightMiddle->GetWidth(), nMiddleWidth % pImgHighLightMiddle->GetHeight() );
 		} 
	} 
	// 绘制Thumb  
	pGraphics->DrawImage( pImgThumb, thumPosF.X, thumPosF.Y, pImgThumb->GetWidth(), pImgThumb->GetHeight() );
	if ( TRUE == m_bLBtnDown && NULL != m_pImgBubble )
	{
		// 绘制气泡提示框
		pGraphics->DrawImage( m_pImgBubble, thumPosF.X + pImgThumb->GetWidth(), thumPosF.Y-7, m_pImgBubble->GetWidth(), m_pImgBubble->GetHeight() );
		// 绘制点击按钮时的数据
		CString strText;
		int i = GetPos();
		strText.Format("%i",i);
		BSTR bstrText = strText.AllocSysString();
		Font* pFont = CSrcManage::GetFont( "宋体", 9 );
		StringFormat cStringFormat;
		cStringFormat.SetAlignment( StringAlignmentCenter );
		SolidBrush brush( Color( 254, 15, 79, 81 )  );
		pGraphics->DrawString( bstrText, -1, pFont, RectF( (float)(thumPosF.X+18), (float)(thumPosF.Y+4), 46, 33 ), &cStringFormat, &brush );
		SysFreeString( bstrText );
	}
}


void CTransparentSliderWnd::SetImage( CString strFolder, BOOL bInvalidate /* = FALSE */ )
{
    String strFile = strFolder + "//" + CTransparentSliderWnd::strNormalLeft;
    m_pImgNormalLeft = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strNormalMid;
    m_pImgNormalMiddle = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strNormalRight;
    m_pImgNormalRight = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strHighLightLeft;
    m_pImgHighLightLeft = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strHighLightMid;
    m_pImgHighLightMiddle = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strHighLightRight;
    m_pImgHighLightRight = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strThumbNormal;
    m_pImgThumbNormal = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strThumbPress;
    m_pImgThumbPress = CSrcManage::GetImage( strFile.c_str() );
    
    
    
    //disable
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableLeft;
    m_pImgDisableLeft = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableMid;
    m_pImgDisableMid  = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableRight;
    m_pImgDisableRight = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableHighLightLeft;
    m_pImgDisableHighLightLeft = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableHighLightMid;
    m_pImgDisableHighLightMid = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableHighLightRight;
    m_pImgDisableHighLightRight = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strThumbDisable;
    m_pImgThumbDisable = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strBubble;
    m_pImgBubble = CSrcManage::GetImage( strFile.c_str() );
        

    UpdateMaxOffSet();

    CRect rect;
    GetClientRect( & rect ); 

    if ( bInvalidate )
    {
        NOTIF_PARENT_WND
    } 
    
     
     AdjustSlider();

     SetThumbPos( 0 );
     //TRACE("\n[SetImage]thumbPos(x:%d  y:%d)\n",m_ptThumbPos.x,m_ptThumbPos.y);
}



void CTransparentSliderWnd::GetRange( int& nMin, int& nMax ) const
{
   nMin = m_nMin;
   nMax = m_nMax;

} 

void CTransparentSliderWnd::SetRange( int nMin, int nMax, BOOL bRedraw/* = FALSE */)
{
    m_nMin = nMin;
    m_nMax = nMax;
   
   //调整slider长度
    AdjustSlider();

    if ( bRedraw )
    {
       NOTIF_PARENT_WND;
    }
}


void CTransparentSliderWnd::AdjustSlider()
{  
    if ( m_nMax ==  m_nMin || m_pImgThumbNormal == NULL )
    {
        return;
    }

    CRect rect;
	GetClientRect( &rect );

	if ( m_pImgThumbNormal == NULL )
	{
		return;
	}

	int nThumbWidth = m_pImgThumbNormal->GetWidth(); 
    int nThumbHeight = m_pImgThumbNormal->GetHeight();


	if ( emStyleHorz == m_emStyle )
	{  
        //调整高度 
        if ( m_pImgThumbPress != NULL && m_pImgThumbPress->GetHeight() > nThumbHeight )
        {
            nThumbHeight = m_pImgThumbPress->GetHeight();
        }
        
        if ( nThumbHeight > rect.Height() )
        {
            rect.bottom = rect.bottom +  nThumbHeight - rect.Height() + 6 ;
        }
		
        //调整宽度
        int nSliderWidth = rect.Width();
 
        SetWindowPos(NULL, rect.left , rect.top, nSliderWidth , rect.Height() , SWP_NOMOVE ); 
	}
    else
	{
		//调整宽度 
        if ( m_pImgThumbPress != NULL && m_pImgThumbPress->GetWidth() > nThumbWidth )
        {
            nThumbWidth = m_pImgThumbPress->GetWidth();
        }
        
        if ( nThumbWidth > rect.Width() )
        {
            rect.right = rect.right +  nThumbWidth - rect.Width() + 6 ;
        }
		
        //调整高度
        int nSliderWidth = rect.Height(); 
        
        SetWindowPos(NULL, rect.left , rect.top, rect.Width() , nSliderWidth , SWP_NOMOVE ); 
	}
}

int  CTransparentSliderWnd::GetPos( )  
{  
    CRect rect;
    GetClientRect( &rect );
    int nWidth = 0;
    if ( m_pImgThumbNormal != NULL )
    {
        nWidth = m_pImgThumbNormal->GetWidth()/2;
    }

    int nOffset =  m_rectfThumbRect.X -  rect.left/* + nWidth*/;
	if ( emStyleHorz != m_emStyle )
	{//添加竖直方向 2013.1.24 yjj
		nOffset = /*m_ptMouseNow.y -  rect.top;*/ m_rectfThumbRect.Y -  rect.top;
	}
    if ( nOffset > m_nMaxOffset )
    {
        nOffset = m_nMaxOffset;
    }

    if ( nOffset < 0 )
    {
        nOffset = 0;
    }

    return CalculatePos( nOffset );
}

void CTransparentSliderWnd::SetPos( int nPos )
{
    //防止拖拽时有抖动现象，所有再拖拽时不响应外部的设置
	if ( m_bLBtnDown )
	{
	   return;
	}

//    CString str ;
//    str.Format("\n[setPos: getPos=%d  willSet=%d]\n",GetPos(),nPos );
//    AfxOutputDebugString( str );
	//当偏移量过小,相邻位置之间的界限模糊---jyy
//	if ( GetPos() != nPos )
//	{
	if ( NULL == m_pImgThumbNormal )
	{
		return;	
	}
	m_nPos = nPos;
	UINT nWidth = m_pImgThumbNormal->GetWidth();
	CRect rect;
    GetClientRect( &rect );
	float fThumbRectX =  m_rectfThumbRect.X -  rect.left;		//获取当前滑块所在位置的偏移量
	if ( emStyleHorz != m_emStyle )
	{
		fThumbRectX = m_rectfThumbRect.Y -  rect.top;
	}
	float nOffset  = CalculateOffset( nPos ) ;			//函数需要设置滑块位置的偏移量
	float fOffsetRange = (float)( m_nMaxOffset - nWidth ) / (float)(m_nMax - m_nMin);	//滑块1个刻度的偏移量
	float fsize = nOffset - fThumbRectX;
	if ( fsize <= 0 )
	{
		fsize = -fsize;	
		if ( fsize > fOffsetRange )		//当偏移量小于刻度1时,不动,减少误差
		{
			SetThumbPos(  nOffset  ); 
			NOTIF_PARENT_WND; 
			return;
		}
		const float EPSINON = (const float)0.00001;	//浮点数比较的时候有误差,比较"=="的时候采用这种方式确保绘制成功
		float a = fsize - fOffsetRange;
		if ((a >= - EPSINON)&& (a <= EPSINON))
		{
			SetThumbPos(  nOffset  ); 
			NOTIF_PARENT_WND; 
		}
		return;
	
	}

	SetThumbPos(  nOffset  ); 
	NOTIF_PARENT_WND; 

//      str.Format("\n[setPos: nOffset=%d]\n",nOffset );
//      AfxOutputDebugString( str );
//	} 
  
}
 