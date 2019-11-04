// TransparentSliderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "slider.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentSliderCtrl
const CString CTransparentSliderCtrl::strNormalLeft = "NormalLeft.png";
const CString CTransparentSliderCtrl::strNormalMid = "NormalMid.png";
const CString CTransparentSliderCtrl::strNormalRight = "NormalRight.png";
const CString CTransparentSliderCtrl::strHighLightLeft = "HighLightLeft.png";
const CString CTransparentSliderCtrl::strHighLightMid = "HighLightMid.png";
const CString CTransparentSliderCtrl::strHighLightRight = "HighLightRight.png";
const CString CTransparentSliderCtrl::strThumbNormal = "ThumbNormal.png";
const CString CTransparentSliderCtrl::strThumbPress = "ThumbPress.png";
template<> WNDPROC TransparentAssist<CTransparentSliderCtrl>::m_pWndProc = NULL;

//disable 图标
const CString CTransparentSliderCtrl::strDisableLeft = "DisableLeft.png";
const CString CTransparentSliderCtrl::strDisableMid = "DisableMid.png";
const CString CTransparentSliderCtrl::strDisableRight = "DisableRight.png";
const CString CTransparentSliderCtrl::strDisableHighLightLeft = "DisableHighLightLeft.png";
const CString CTransparentSliderCtrl::strDisableHighLightMid = "DisableHighLightMid.png";
const CString CTransparentSliderCtrl::strDisableHighLightRight = "DisableHighLightRight.png";
const CString CTransparentSliderCtrl::strThumbDisable = "ThumbDisable.png";

CTransparentSliderCtrl::CTransparentSliderCtrl()
{
	RegsiterWndProc();
    m_emStatus = emStatusNormal;

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
}

CTransparentSliderCtrl::CTransparentSliderCtrl( CString strImage )
{
	m_emStatus = emStatusNormal;
	SetImage( strImage );
}

CTransparentSliderCtrl::~CTransparentSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CTransparentSliderCtrl, CSliderCtrl)
    //{{AFX_MSG_MAP(CTransparentSliderCtrl)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_CAPTURECHANGED()
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentSliderCtrl message handlers

void CTransparentSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
    m_emStatus = emStatusSetFocus;

    NOTIF_PARENT_WND

    CSliderCtrl::OnLButtonDown(nFlags, point);
}

void CTransparentSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
    CSliderCtrl::OnLButtonUp(nFlags, point);
}

void CTransparentSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
    if ( m_emStatus == emStatusSetFocus )
    {
        NOTIF_PARENT_WND
    }

    CSliderCtrl::OnMouseMove(nFlags, point);
}

void CTransparentSliderCtrl::OnCaptureChanged(CWnd *pWnd) 
{
    m_emStatus = emStatusNormal;

    NOTIF_PARENT_WND
    this->PostMessage(SLIDER_RELEASED_CAPTURE, NULL, NULL); 
    CSliderCtrl::OnCaptureChanged(pWnd);
}

LRESULT CTransparentSliderCtrl::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
	//获取slider的风格，只考虑垂直和水平
	BOOL bHorz = FALSE;

	if ( ((this->GetStyle() & TBS_VERT) != 0 ) )
	{
		//垂直方向
		bHorz = FALSE;
	}
	else
	{
		//水平方向
		bHorz = TRUE;
	}

    Graphics *pGraphics = (Graphics*)wParam;
    m_hParent = (HWND)GetParent()->m_hWnd;

    HWND hGraphWnd = (HWND )lParam;
  //  CWnd * pGraphWnd = FromHandle(hGraphWnd);
    if ( pGraphics == NULL || hGraphWnd == 0 )
    {
        return S_FALSE;
    }

    if ( IsWindowVisible() == FALSE || m_pImgNormalLeft == NULL )
    {
        return S_FALSE;
    }

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();
    ::ScreenToClient(/* m_hParent*/hGraphWnd, &point );

    
   

    Image * pImgNormalLeft = NULL;
    Image * pImgNormalMiddle = NULL;
    Image * pImgNormalRight = NULL;

    Image * pImgHighLightLeft = NULL;
    Image * pImgHighLightMiddle = NULL;
    Image * pImgHighLightRight = NULL;

    Image *pImgThumb = NULL;
    if ( IsWindowEnabled() )
    {
        if ( m_emStatus == emStatusSetFocus )
        {
            pImgThumb = m_pImgThumbPress;
        }
        else
        {
            pImgThumb = m_pImgThumbNormal;
        }

       
        pImgNormalLeft = m_pImgNormalLeft;
        pImgNormalMiddle = m_pImgNormalMiddle;
        pImgNormalRight = m_pImgNormalRight;
        
        pImgHighLightLeft = m_pImgHighLightLeft;
        pImgHighLightMiddle = m_pImgHighLightMiddle;
        pImgHighLightRight = m_pImgHighLightRight;

    }
    else
    {
        pImgThumb = m_pImgThumbDisable;
       
        pImgNormalLeft = m_pImgDisableLeft;
        pImgNormalMiddle = m_pImgDisableMid;
        pImgNormalRight = m_pImgDisableRight;
        
        pImgHighLightLeft = m_pImgDisableHighLightLeft;
        pImgHighLightMiddle = m_pImgDisableHighLightMid;
        pImgHighLightRight = m_pImgDisableHighLightRight;
    }
    
    
    


	if ( bHorz )
	{
		//绘制水平slider

		// 绘制底图
		int nPosX = point.x +  pImgNormalLeft->GetWidth();
		int nPosY = point.y + ( cRect.Height() -  pImgNormalLeft->GetHeight() ) / 2;
		int nMiddleWidth = cRect.Width() -  pImgNormalLeft->GetWidth() -  pImgNormalLeft->GetWidth();
		// 左
		pGraphics->DrawImage( pImgNormalLeft, point.x, nPosY,  pImgNormalLeft->GetWidth(), pImgNormalLeft->GetHeight() );
		// 右
		pGraphics->DrawImage( pImgNormalRight, point.x + cRect.Width() - pImgNormalRight->GetWidth(), nPosY, pImgNormalRight->GetWidth(), pImgNormalRight->GetHeight() );
	
		if ( nMiddleWidth <= 0 )
		{
			return S_OK;
		}

		for ( unsigned int nIndex = 0; nIndex < ( nMiddleWidth / m_pImgNormalMiddle->GetWidth() ); nIndex++ )
		{
			pGraphics->DrawImage( pImgNormalMiddle, nPosX, nPosY, pImgNormalMiddle->GetWidth(), pImgNormalMiddle->GetHeight() );
			nPosX += pImgNormalMiddle->GetWidth();
		}
		pGraphics->DrawImage( pImgNormalMiddle, nPosX, nPosY, nMiddleWidth % pImgNormalMiddle->GetWidth(), pImgNormalMiddle->GetHeight() );

		// 绘制高亮的地方
		CRect cRectThumb;
		GetThumbRect( &cRectThumb );
		// 左
		pGraphics->DrawImage( pImgHighLightLeft, point.x, nPosY, pImgHighLightLeft->GetWidth(), pImgHighLightLeft->GetHeight() );
		// 右
		pGraphics->DrawImage( pImgHighLightRight, point.x + cRectThumb.right - pImgHighLightRight->GetWidth(), nPosY, pImgHighLightRight->GetWidth(), pImgHighLightRight->GetHeight() );

		nPosX = point.x + pImgHighLightLeft->GetWidth();
		nMiddleWidth = cRectThumb.right - pImgHighLightLeft->GetWidth() - pImgHighLightRight->GetWidth();
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
       
        
        int nY = point.y  + cRect.Height()/ 2 -  pImgThumb->GetHeight()/ 2  ;
        int nx = point.x + cRectThumb.left + cRectThumb.Width()/2 - pImgThumb->GetWidth()/2 + 3;
        TRACE("\n[CTransparentSliderCtrl::OnRedrawUI]: thumb.x=%d\n",nx);

		// 绘制Thumb 
		pGraphics->DrawImage( pImgThumb, nx , nY , pImgThumb->GetWidth(), pImgThumb->GetHeight() );
		//pGraphics->DrawImage( pImgThumb, point.x + cRectThumb.left - 15, point.y - 5, cRectThumb.Width(), cRectThumb.Height() );
	}
	else
	{
		//绘制垂直slider
		CRect cRectThumb;
		GetThumbRect( &cRectThumb );

		POINT point2 = cRect.BottomRight();
		::ScreenToClient( m_hParent, &point2 );

		int nEnlargeSize = 10; //Thumb不可见边缘大小
		int nSliderOffset=8;

		point.y += nSliderOffset;
		// 绘制底图 nSliderOffset/2解决不置顶问题
		int nPosX = point.x + cRectThumb.Width() / 2;
		int nPosY = point.y + m_pImgNormalLeft->GetHeight() + nSliderOffset/2;
		int nMiddleHeight = cRect.Height() - m_pImgNormalLeft->GetHeight() - m_pImgNormalRight->GetHeight() 
			- nSliderOffset*2 - nSliderOffset/2;
		// 上
		pGraphics->DrawImage( m_pImgNormalLeft, nPosX, point.y+nSliderOffset/2, m_pImgNormalLeft->GetWidth(), 
			m_pImgNormalLeft->GetHeight() );
		// 下
		pGraphics->DrawImage( m_pImgNormalRight, nPosX, point.y+cRect.Height()-m_pImgNormalRight->GetHeight()-nSliderOffset*2, 
			m_pImgNormalRight->GetWidth(), m_pImgNormalRight->GetHeight() );

		/* 
		中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
		TRACE("====%ld, %ld,%ld", nMiddleWidth, m_pImgNormalMiddle->GetWidth(), nMiddleWidth / m_pImgNormalMiddle->GetWidth() );
		增加保护，防止死循环
		*/
		if ( nMiddleHeight <= 0 )
		{
			return S_OK;
		}

		
		for ( unsigned int nIndex = 0; nIndex < ( nMiddleHeight / m_pImgNormalMiddle->GetHeight() ); nIndex++ )
		{
			pGraphics->DrawImage( m_pImgNormalMiddle, nPosX, nPosY, m_pImgNormalMiddle->GetWidth(), 
				m_pImgNormalMiddle->GetHeight() );
			nPosY += m_pImgNormalMiddle->GetHeight();
		}
		pGraphics->DrawImage( m_pImgNormalMiddle, nPosX, nPosY, m_pImgNormalMiddle->GetWidth(), 
			nMiddleHeight % m_pImgNormalMiddle->GetHeight() );

		point.y -= nSliderOffset;

		if ( point.y + cRectThumb.bottom <= point.y+cRect.Height() - nSliderOffset - cRectThumb.Height()/2)
		{
			// 绘制高亮的地方
			//上
			if ( point.y + cRectThumb.bottom + m_pImgHighLightLeft->GetHeight() < point.y+cRect.Height() - cRectThumb.Height()/2)
			{
				//当高亮底部长度小于拇指长度时，不需要画上部分
				pGraphics->DrawImage( m_pImgHighLightLeft, nPosX,  point.y+cRectThumb.bottom-nEnlargeSize, 
					m_pImgHighLightLeft->GetWidth(), m_pImgHighLightLeft->GetHeight() );
			}
		
			nPosY =  point.y+cRectThumb.bottom -nEnlargeSize + m_pImgHighLightLeft->GetHeight();
			
			nMiddleHeight = cRect.Height() - cRectThumb.bottom - m_pImgHighLightLeft->GetHeight() - 
				m_pImgHighLightRight->GetHeight()+nEnlargeSize-nSliderOffset;

			// 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
			for ( nIndex = 0; nMiddleHeight > 0 && nIndex < ( nMiddleHeight / m_pImgHighLightMiddle->GetHeight() ); nIndex++ )
			{
				pGraphics->DrawImage( m_pImgHighLightMiddle, nPosX, nPosY, m_pImgHighLightMiddle->GetWidth(), 
					m_pImgHighLightMiddle->GetHeight() );
				nPosY += m_pImgHighLightMiddle->GetHeight();
			}
			if ( nMiddleHeight > 0 )
			{
				pGraphics->DrawImage( m_pImgHighLightMiddle, nPosX, nPosY, m_pImgHighLightMiddle->GetWidth(), 
					nMiddleHeight%m_pImgHighLightMiddle->GetHeight() );
			}

			int nSubHeight = point2.y - (point.y+cRectThumb.bottom-cRectThumb.Height() ) - nSliderOffset*2 ;

			if ( nSubHeight < m_pImgHighLightRight->GetHeight())
			{
				pGraphics->DrawImage( m_pImgHighLightRight, nPosX, (point.y+cRectThumb.bottom-cRectThumb.Height()+nSliderOffset), 
						m_pImgHighLightRight->GetWidth(), nSubHeight );
			}
			else
			{
				pGraphics->DrawImage( m_pImgHighLightRight, nPosX, point.y+cRect.Height()-nSliderOffset-m_pImgHighLightRight->GetHeight(), 
						m_pImgHighLightRight->GetWidth(), m_pImgHighLightRight->GetHeight() );
			}
			
		}

		TRACE("=Thumb %d\n", point.y+cRectThumb.bottom-cRectThumb.Height());
		// 绘制Thumb
		pGraphics->DrawImage( pImgThumb,  point.x, point.y+cRectThumb.bottom-cRectThumb.Height(),
			cRectThumb.Width()+nEnlargeSize, cRectThumb.Height()+nEnlargeSize);
	}
    return S_OK;
}

void CTransparentSliderCtrl::SetImage( CString strFolder, BOOL bInvalidate /* = FALSE */ )
{
	String strFile = strFolder + "//" + CTransparentSliderCtrl::strNormalLeft;
	m_pImgNormalLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSliderCtrl::strNormalMid;
	m_pImgNormalMiddle = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSliderCtrl::strNormalRight;
	m_pImgNormalRight = CSrcManage::GetImage( strFile.c_str() );
	
	strFile = strFolder + "//" + CTransparentSliderCtrl::strHighLightLeft;
	m_pImgHighLightLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSliderCtrl::strHighLightMid;
	m_pImgHighLightMiddle = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSliderCtrl::strHighLightRight;
	m_pImgHighLightRight = CSrcManage::GetImage( strFile.c_str() );

	strFile = strFolder + "//" + CTransparentSliderCtrl::strThumbNormal;
	m_pImgThumbNormal = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSliderCtrl::strThumbPress;
	m_pImgThumbPress = CSrcManage::GetImage( strFile.c_str() );
   


    //disable
    strFile = strFolder + "//" + CTransparentSliderCtrl::strDisableLeft;
    m_pImgDisableLeft = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderCtrl::strDisableMid;
    m_pImgDisableMid  = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderCtrl::strDisableRight;
    m_pImgDisableRight = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderCtrl::strDisableHighLightLeft;
    m_pImgDisableHighLightLeft = CSrcManage::GetImage( strFile.c_str() );

    strFile = strFolder + "//" + CTransparentSliderCtrl::strDisableHighLightMid;
    m_pImgDisableHighLightMid = CSrcManage::GetImage( strFile.c_str() );

    strFile = strFolder + "//" + CTransparentSliderCtrl::strDisableHighLightRight;
    m_pImgDisableHighLightRight = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderCtrl::strThumbDisable;
    m_pImgThumbDisable = CSrcManage::GetImage( strFile.c_str() );

	
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}
