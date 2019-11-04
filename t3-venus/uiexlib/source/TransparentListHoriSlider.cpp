/*****************************************************************************
模块名      : 列表横向滑动条
文件名      : TransparentListHoriSlider.cpp
相关文件    : TransparentListHoriSlider.h
文件实现功能: 包含于列表，用于显示列表当前横向位置
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
  日  期      版本        修改人      修改内容
2012/11/29    1.0         肖楚然        创建
******************************************************************************/
#include "stdafx.h"
#include "TransparentListHoriSlider.h"

const CString CTransparentListHoriSlider::strNormalLeft = "NormalLeft.png";
const CString CTransparentListHoriSlider::strNormalMiddle = "NormalMiddle.png";
const CString CTransparentListHoriSlider::strNormalRight = "NormalRight.png";
const CString CTransparentListHoriSlider::strHilightLeft = "HilightLeft.png";
const CString CTransparentListHoriSlider::strHilightMiddle = "HilightMiddle.png";
const CString CTransparentListHoriSlider::strHilightRight = "HilightRight.png";
const CString CTransparentListHoriSlider::strBkLeft = "BkgLeft.png";
const CString CTransparentListHoriSlider::strBkMiddle = "BkgMiddle.png";
const CString CTransparentListHoriSlider::strBkRight = "BkgRight.png";
const CString CTransparentListHoriSlider::strBkLeftMove = "BkgLeftMove.png";
const CString CTransparentListHoriSlider::strBkRightMove = "BkgRightMove.png";
const CString CTransparentListHoriSlider::strBkLeftMoveDown = "BkgLeftMoveDown.png";
const CString CTransparentListHoriSlider::strBkRightMoveDown = "BkgRightMoveDown.png";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransparentListHoriSlider::CTransparentListHoriSlider( CString strName, CRect rcWnd, CWnd* pParentWnd, UINT nID, DWORD dStyle, DWORD dwExStyle )
: CTransparentBaseWnd( rcWnd, pParentWnd, dStyle, "", nID, dwExStyle )
{
    m_nListWidth = 0;
    m_nListXOffset = 0;
    m_bLButtonDown = FALSE;
    m_pListWnd = NULL;
    m_nBkgImgOffset = 0;
    
    m_pImgSliderBkLeft = NULL;
    m_pImgSliderBkCenter = NULL;
    m_pImgSliderBkRight = NULL;
    m_pImgSliderNormalLeft = NULL;
    m_pImgSliderNormalCenter = NULL;
    m_pImgSliderNormalRight = NULL;
    m_pImgSliderHilightLeft = NULL;
    m_pImgSliderHilightCenter = NULL;
	m_pImgSliderHilightRight = NULL;

	m_pImgLeftMove = NULL;
	m_pImgRightMove = NULL;

	m_emLeftMoveStatus = emStatusMoveBtnNormal;
	m_emRightMoveStatus = emStatusMoveBtnNormal;
}

CTransparentListHoriSlider::~CTransparentListHoriSlider()
{
    m_pListWnd = NULL;
}



BEGIN_MESSAGE_MAP(CTransparentListHoriSlider, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CTransparentListHoriSlider)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_SIZE()
//}}AFX_MSG_MAP
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()


LRESULT CTransparentListHoriSlider::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{  
    Graphics *pGraphics = (Graphics*)wParam;
    HWND hGraphWnd = (HWND )lParam;
    CWnd * pGraphWnd = FromHandle(hGraphWnd);

    if ( IsWindowVisible() == FALSE || GetParent() == NULL || pGraphWnd == NULL )
    {
        return S_FALSE;
    }

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();
    pGraphWnd->ScreenToClient( &point );

    if ( m_pImgSliderBkLeft == NULL || m_pImgSliderBkCenter == NULL || m_pImgSliderBkRight == NULL )
    {   
        return S_FALSE;
	}

    int nBKLeftWidth = m_pImgSliderBkLeft->GetWidth();
    int nBkMidWidth = m_pImgSliderBkCenter->GetWidth();
    int nBkRightWidth = m_pImgSliderBkRight->GetWidth();
    int nBkHeight = m_pImgSliderBkLeft->GetHeight();
    
    // 绘制底图
    int nPosX = point.x;
    int nPosY = point.y ;
    int nCenterWidth = cRect.Width() - nBKLeftWidth - nBkRightWidth;
    // 左
    pGraphics->DrawImage( m_pImgSliderBkLeft, nPosX, nPosY, nBKLeftWidth, nBkHeight );
    // 右
    pGraphics->DrawImage( m_pImgSliderBkRight, nPosX + nBKLeftWidth + nCenterWidth, nPosY, nBkRightWidth, nBkHeight );
    
	int nLeftPosX = nPosX;
	int nLeftPosY = nPosY + nBkHeight/2;
	int nRightPosX = nPosX + nBKLeftWidth + nCenterWidth + nBkRightWidth;

    nPosX += nBKLeftWidth;   

    // 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
    for ( int nIndex = 0; nIndex < ( nCenterWidth / nBkMidWidth ); nIndex++ )
    {
        pGraphics->DrawImage( m_pImgSliderBkCenter, nPosX, nPosY, nBkMidWidth, nBkHeight);
        nPosX += nBkMidWidth;
    } 
    pGraphics->DrawImage( m_pImgSliderBkCenter, nPosX, nPosY, nCenterWidth % nBkMidWidth, nBkHeight );


	//绘制左 右侧移动的图片
	Image *pImageLeftMove = NULL;
    switch ( m_emLeftMoveStatus )
    {
    case emStatusMoveBtnNormal:
        pImageLeftMove = m_pImgLeftMove;
        break;
    case emStatusMoveBtnDown:
        pImageLeftMove = m_pImgLeftMoveDown;
        break;
    }

	Image *pImageRightMove = NULL;
    switch ( m_emRightMoveStatus )
    {
    case emStatusMoveBtnNormal:
        pImageRightMove = m_pImgRightMove;
        break;
    case emStatusMoveBtnDown:
        pImageRightMove = m_pImgRightMoveDown;
        break;
    }

	if ( pImageLeftMove != NULL && pImageRightMove != NULL )
	{
		nLeftPosY -= pImageLeftMove->GetHeight()/2;
		nRightPosX -= pImageRightMove->GetWidth();
		pGraphics->DrawImage( pImageLeftMove, nLeftPosX + 2, nLeftPosY, pImageLeftMove->GetWidth(), pImageLeftMove->GetHeight() );
		pGraphics->DrawImage( pImageRightMove, nRightPosX - 2, nLeftPosY, pImageRightMove->GetWidth(), pImageRightMove->GetHeight() );
	
		m_cLeftMoveIconRect.SetRect( nLeftPosX + 2, nLeftPosY, nLeftPosX + 2 + pImageLeftMove->GetWidth(), nLeftPosY + pImageLeftMove->GetHeight() );
		m_cRightMoveIconRect.SetRect( nRightPosX - 2, nLeftPosY, nRightPosX - 2 + pImageLeftMove->GetWidth(),nLeftPosY + pImageLeftMove->GetHeight() );
	}

    Image* pSliderLeft = NULL;
    Image* pSliderCenter = NULL;
    Image* pSliderRight = NULL;

    if ( m_bLButtonDown )
    {
        pSliderLeft = m_pImgSliderHilightLeft;
        pSliderCenter = m_pImgSliderHilightCenter;
        pSliderRight = m_pImgSliderHilightRight;
    }
    else
    {
        pSliderLeft = m_pImgSliderNormalLeft;
        pSliderCenter = m_pImgSliderNormalCenter;
        pSliderRight = m_pImgSliderNormalRight;
    }

    if ( pSliderLeft == NULL || pSliderCenter == NULL || pSliderRight == NULL )
    {   
        return S_FALSE;
	}

    int nSliderLeftWidth = pSliderLeft->GetWidth();
    int nSliderMidWidth = pSliderCenter->GetWidth();
    int nSliderRightWidth = pSliderRight->GetWidth();
    int nSliderHeight = pSliderLeft->GetHeight();

    int nSliderPos = 0;
    int nSliderWidth = 0;
    
	if ( NULL == pImageLeftMove )
	{
		CalSliderPos( cRect.Width(), nSliderLeftWidth + nSliderRightWidth, nSliderPos, nSliderWidth );	
	}
    else
	{
		CRect cListRect;
		m_pListWnd->GetClientRect( cListRect );
		CalSliderPos( cRect.Width() - 2*(m_pImgLeftMove->GetWidth() + 2) - 2, cListRect.Width(), nSliderLeftWidth + nSliderRightWidth, nSliderPos, nSliderWidth );
		nSliderPos += (m_pImgLeftMove->GetWidth() + 2) + 1;
	}

    m_rctSlider.left = nSliderPos;
	m_rctSlider.right = nSliderPos + nSliderWidth; 

    //绘制滑动条
    nPosX = point.x + nSliderPos;
    nPosY = point.y + m_nBkgImgOffset;

    int nSliderCenterWidth = nSliderWidth - nSliderLeftWidth - nSliderRightWidth;

    // 左
    pGraphics->DrawImage( pSliderLeft, nPosX, nPosY, nSliderLeftWidth, nSliderHeight );
    // 右
    pGraphics->DrawImage( pSliderRight, nPosX + nSliderLeftWidth + nSliderCenterWidth, nPosY, nSliderRightWidth, nSliderHeight );  
    nPosX += nSliderLeftWidth;   
	// 中
    for ( nIndex = 0; nIndex < ( nSliderCenterWidth / nSliderMidWidth ); nIndex++ )
    {
        pGraphics->DrawImage( pSliderCenter, nPosX, nPosY, nSliderMidWidth, nSliderHeight );
        nPosX += nSliderMidWidth;
    } 
    pGraphics->DrawImage( pSliderCenter, nPosX, nPosY, nSliderCenterWidth % nSliderMidWidth, nSliderHeight );

    return S_OK;
}

/*=============================================================================
函 数 名:CalSliderPos
功    能:计算滑条位置及长度
参    数:[in]nAllHeight     滑动条总宽度=列表dlg宽度
         [in]nSliderMinWidth 滑条最小宽度
         [out]nSliderPos    滑条起始位置
         [out]nSliderWidth  滑条宽度
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/11/29  1.0     肖楚然     创建
=============================================================================*/
void CTransparentListHoriSlider::CalSliderPos( int nBkgWidth, int nSliderMinWidth, int& nSliderPos, int& nSliderWidth )
{
    if ( m_nListWidth == 0 )
    {
        nSliderPos = 0;
        nSliderWidth = 0;
        return;
    }

    if ( nBkgWidth < m_nListWidth )
    {
        nSliderPos = (float)m_nListXOffset * nBkgWidth / m_nListWidth;

        nSliderWidth = (float)nBkgWidth * nBkgWidth / m_nListWidth; 
        
        if ( nSliderWidth < nSliderMinWidth )
        {
            nSliderWidth = nSliderMinWidth;
            
            nSliderPos = (float)m_nListXOffset * ( nBkgWidth - nSliderWidth ) / ( m_nListWidth - nBkgWidth );
        }
    }
    else
    {
        nSliderPos = 0;
        nSliderWidth = nBkgWidth;
    }
}

void CTransparentListHoriSlider::CalSliderPos( int nBkgWidth, int nListDlgWidth, int nSliderMinWidth, int& nSliderPos, int& nSliderWidth )
{
    if ( m_nListWidth == 0 )
    {
        nSliderPos = 0;
        nSliderWidth = 0;
        return;
    }
	
    if ( nBkgWidth < m_nListWidth )
    {
        nSliderPos = (float)m_nListXOffset * nBkgWidth / m_nListWidth;
		
        nSliderWidth = (float)nBkgWidth * nListDlgWidth / m_nListWidth; 
        
        if ( nSliderWidth < nSliderMinWidth )
        {
            nSliderWidth = nSliderMinWidth;
            
            nSliderPos = (float)m_nListXOffset * ( nBkgWidth - nSliderWidth ) / ( m_nListWidth - nListDlgWidth );
        }
    }
    else
    {
        nSliderPos = 0;
        nSliderWidth = nBkgWidth;
    }
}

void CTransparentListHoriSlider::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int nMoveBtnOffset = 0;
	if ( NULL != m_pListWnd && NULL != m_pImgLeftMove && NULL != m_pImgLeftMove )   //点击左移 右移
	{
		CPoint pointOffset;
		pointOffset.x = 50;
		pointOffset.y = 0;
		CPoint ptRect;
		ptRect.x = m_cLeftMoveIconRect.left + point.x;
		ptRect.y = m_cLeftMoveIconRect.top + point.y;

		if ( m_cRightMoveIconRect.PtInRect( ptRect ) 
			&& !m_cLeftMoveIconRect.PtInRect( ptRect ) )
		{
			m_bLButtonDown = TRUE;

			SetCapture();
			m_emRightMoveStatus = emStatusMoveBtnDown;
			m_pListWnd->SendMessage( WM_LIST_UPDATEPROGRESS, (WPARAM)&pointOffset, 0 );
		
			m_ptMouseDown = point;

			nMoveBtnOffset = m_pImgRightMove->GetWidth();
			
			NOTIF_PARENT_WND
			return;
		}
		else if ( m_cLeftMoveIconRect.PtInRect( ptRect )
			 && !m_cRightMoveIconRect.PtInRect( ptRect ) )
		{
			m_bLButtonDown = TRUE;

			SetCapture();
			m_emLeftMoveStatus = emStatusMoveBtnDown;
 			pointOffset.x = -50;
 			m_pListWnd->SendMessage( WM_LIST_UPDATEPROGRESS, (WPARAM)&pointOffset, 0 );

			m_ptMouseDown = point;

			nMoveBtnOffset = m_pImgRightMove->GetWidth();
			
			NOTIF_PARENT_WND
			return;
 		}
		else
		{
			nMoveBtnOffset = 0;
		}
	}

	if ( !m_rctSlider.PtInRect(point) )
	{
		return;
	}

    SetCapture();

    m_bLButtonDown = TRUE;
    m_ptMouseDown = point;
    

    NOTIF_PARENT_WND
}

void CTransparentListHoriSlider::OnLButtonUp(UINT nFlags, CPoint point) 
{  
    if ( !m_bLButtonDown )
    {
        return;
	}
 
	if ( MoveButtonUpdate(point) )
	{
		return;
	}

	m_emLeftMoveStatus = emStatusMoveBtnNormal;
	m_emRightMoveStatus = emStatusMoveBtnNormal;

    ReleaseCapture();
    m_bLButtonDown = FALSE;

    NOTIF_PARENT_WND

}

void CTransparentListHoriSlider::OnMouseMove(UINT nFlags, CPoint point) 
{ 
    if ( !m_bLButtonDown )
    {
        return;
	}

    if( m_ptMouseDown == point )
    {
        return;
    }

	if ( MoveButtonUpdate(point) )
	{
		return;
	}

    int nXOffSet = point.x - m_ptMouseDown.x;

    m_ptMouseDown = point;

    CRect cRect;
    GetWindowRect( &cRect );
    int nDlgWidth = cRect.Width();
    int nListOffset = 0;
    //换算为列表需要移动的距离
    if ( nDlgWidth > 0 && m_nListWidth > nDlgWidth )
    {
        nListOffset = nXOffSet * m_nListWidth / nDlgWidth;
    }

    CPoint pointOffset;
    pointOffset.x = nListOffset;
    pointOffset.y = 0;
    if ( m_pListWnd != NULL )
    {
        m_pListWnd->SendMessage( WM_LIST_UPDATEPROGRESS, (WPARAM)&pointOffset, 0 );
    }

	NOTIF_PARENT_WND
}

BOOL CTransparentListHoriSlider::MoveButtonUpdate(CPoint point)
{
	if ( NULL == m_pImgRightMove )
	{
		return FALSE;
	}

	CPoint ptRect;
	ptRect.x = m_cLeftMoveIconRect.left + point.x;
	ptRect.y = m_cLeftMoveIconRect.top + point.y;
	
	if ( !m_bLButtonDown )
	{
		if ( NULL != m_pImgRightMove && m_cRightMoveIconRect.PtInRect( ptRect )
			&& !m_cLeftMoveIconRect.PtInRect( ptRect ))
		{
			m_emRightMoveStatus = emStatusMoveBtnNormal;
			m_emLeftMoveStatus = emStatusMoveBtnNormal;
			m_bLButtonDown = FALSE;
			ReleaseCapture();
			NOTIF_PARENT_WND
				return TRUE;
		}
		else if ( NULL != m_pImgLeftMove && m_cLeftMoveIconRect.PtInRect( ptRect )
			&& !m_cRightMoveIconRect.PtInRect( ptRect ) )
		{
			m_emLeftMoveStatus = emStatusMoveBtnNormal;
			m_emRightMoveStatus = emStatusMoveBtnNormal;
			m_bLButtonDown = FALSE;
			ReleaseCapture();
			NOTIF_PARENT_WND
				return TRUE;
 		}
	}

	return FALSE;
}

void CTransparentListHoriSlider::OnSize(UINT nType, int cx, int cy)
{
    CTransparentBaseWnd::OnSize(nType, cx, cy);

    CRect rect;
    GetClientRect(&rect);
    m_rctSlider.top = rect.top;
    m_rctSlider.bottom = rect.bottom; 
}

void CTransparentListHoriSlider::SetImage( CString strImageFolder )
{
    if ( "" == strImageFolder )
    {
        return;
    }
    
    String strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strNormalLeft;
    m_pImgSliderNormalLeft = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strNormalMiddle;
    m_pImgSliderNormalCenter = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strNormalRight;
    m_pImgSliderNormalRight = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strHilightLeft;
    m_pImgSliderHilightLeft = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strHilightMiddle;
    m_pImgSliderHilightCenter = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strHilightRight;
    m_pImgSliderHilightRight = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strBkLeft;
    m_pImgSliderBkLeft = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strBkMiddle;
    m_pImgSliderBkCenter = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strBkRight;
    m_pImgSliderBkRight = CSrcManage::GetImage( strFile.c_str() );

	strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strBkLeftMove;
	m_pImgLeftMove = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strBkRightMove;
    m_pImgRightMove = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strBkLeftMoveDown;
	m_pImgLeftMoveDown = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentListHoriSlider::strBkRightMoveDown;
    m_pImgRightMoveDown = CSrcManage::GetImage( strFile.c_str() );


    //滑条高度根据图片调节
    if ( m_pImgSliderBkCenter != NULL && GetParent() != NULL )
    {
        int nHeight = m_pImgSliderBkCenter->GetHeight();
        CRect rect;
        GetWindowRect( &rect ); 
        GetParent()->ScreenToClient( rect );
        rect.bottom = rect.top + nHeight;
        MoveWindow( &rect );

        //调节背景图片与滑条图片间距
        if ( m_pImgSliderNormalCenter != NULL )
        {
            int nNorHeight = m_pImgSliderNormalCenter->GetHeight();
            if ( nHeight > nNorHeight )
            {
                m_nBkgImgOffset = ( nHeight - nNorHeight ) / 2;
            }
        }
    }

	if ( NULL != m_pImgLeftMove )
	{
		CRect rectSlider;
		GetWindowRect( &rectSlider ); 
		GetParent()->ScreenToClient( rectSlider );
		rectSlider.left -= 12;
		rectSlider.right += 12;
		this->MoveWindow( &rectSlider );
	}
}


void CTransparentListHoriSlider::SetImage( UINT nImgNormalLeft, UINT nImgNormalCenter, UINT nImgNormalRight, 
                                          UINT nImgHilightLeft, UINT nImgHilightCenter, UINT nImgHilightRight, 
                                          UINT nImgBkLeft, UINT nImgBkCenter, UINT nImgBkRight,  const CString& strImgType )
{ 
    m_pImgSliderNormalLeft = CSrcManage::GetImage( nImgNormalLeft, strImgType );
    m_pImgSliderNormalCenter = CSrcManage::GetImage( nImgNormalCenter, strImgType );
    m_pImgSliderNormalRight = CSrcManage::GetImage( nImgNormalRight, strImgType );
    m_pImgSliderHilightLeft = CSrcManage::GetImage( nImgHilightLeft, strImgType );
    m_pImgSliderHilightCenter = CSrcManage::GetImage( nImgHilightCenter, strImgType );
    m_pImgSliderHilightRight = CSrcManage::GetImage( nImgHilightRight, strImgType );
    m_pImgSliderBkLeft = CSrcManage::GetImage( nImgBkLeft, strImgType );
    m_pImgSliderBkCenter = CSrcManage::GetImage( nImgBkCenter, strImgType );
    m_pImgSliderBkRight = CSrcManage::GetImage( nImgBkRight, strImgType );

    if ( m_pImgSliderBkCenter != NULL && m_pImgSliderNormalCenter != NULL )
    {
        //调节背景图片与滑条图片间距
        int nHeight = m_pImgSliderBkCenter->GetHeight();              
        int nNorHeight = m_pImgSliderNormalCenter->GetHeight();
        if ( nHeight > nNorHeight )
        {
            m_nBkgImgOffset = ( nHeight - nNorHeight ) / 2;
        }
    }
}
