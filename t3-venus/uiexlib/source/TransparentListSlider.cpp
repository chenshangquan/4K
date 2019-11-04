/*****************************************************************************
模块名      : 列表滑动条
文件名      : TransparentListSlider.cpp
相关文件    : TransparentListSlider.h
文件实现功能: 包含于列表，用于显示列表当前位置
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
  日  期      版本        修改人      修改内容
2012/11/28    1.0         肖楚然        创建
******************************************************************************/
#include "stdafx.h"
#include "TransparentListSlider.h"


const CString CTransparentListSlider::strNormalTop = "NormalTop.png";
const CString CTransparentListSlider::strNormalMiddle = "NormalMiddle.png";
const CString CTransparentListSlider::strNormalBottom = "NormalBottom.png";
const CString CTransparentListSlider::strHilightTop = "HilightTop.png";
const CString CTransparentListSlider::strHilightMiddle = "HilightMiddle.png";
const CString CTransparentListSlider::strHilightBottom = "HilightBottom.png";
const CString CTransparentListSlider::strBkTop = "BkgTop.png";
const CString CTransparentListSlider::strBkMiddle = "BkgMiddle.png";
const CString CTransparentListSlider::strBkBottom = "BkgBottom.png";
const CString CTransparentListSlider::strBkUpMove = "BkgUpMove.png";
const CString CTransparentListSlider::strBkDownMove = "BkgDownMove.png";
const CString CTransparentListSlider::strBkUpMoveDown = "BkgUpMoveDown.png";
const CString CTransparentListSlider::strBkDownMoveDown = "BkgDownMoveDown.png";
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTransparentListSlider::CTransparentListSlider( CString strName, CRect rcWnd, CWnd* pParentWnd, UINT nID, DWORD dStyle, DWORD dwExStyle )
: CTransparentBaseWnd( rcWnd, pParentWnd, dStyle, "", nID, dwExStyle )
{
    m_nListHeight = 0;
    m_nListYOffset = 0;
    m_bLButtonDown = FALSE;
    m_bAlwaysShow = FALSE;
    m_pListWnd = NULL;
    m_nBkgImgOffset = 0;

    m_pImgSliderBkUp = NULL;
    m_pImgSliderBkCenter = NULL;
    m_pImgSliderBkDown = NULL;
    m_pImgSliderNormalUp = NULL;
    m_pImgSliderNormalCenter = NULL;
	m_pImgSliderNormalDown = NULL;
    m_pImgSliderHilightUp = NULL;
    m_pImgSliderHilightCenter = NULL;
	m_pImgSliderHilightDown = NULL;

	m_pImgUpMove = NULL;
	m_pImgDownMove = NULL;
	
	m_emUpMoveStatus = emStatusMoveBtnNormal;
	m_emDownMoveStatus = emStatusMoveBtnNormal;
}

CTransparentListSlider::~CTransparentListSlider()
{
    m_pListWnd = NULL;
}



BEGIN_MESSAGE_MAP(CTransparentListSlider, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CTransparentListSlider)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_SIZE()
//}}AFX_MSG_MAP
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
END_MESSAGE_MAP()


LRESULT CTransparentListSlider::OnRedrawUI( WPARAM wParam, LPARAM lParam )
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

	int nUpPosX = 0;   //记录 上下移动按钮的坐标位置
	int nUpPosY = 0;
	int nDownPosY = 0;

    // 绘制底图
    if ( m_pImgSliderBkUp != NULL && m_pImgSliderBkCenter != NULL && m_pImgSliderBkDown != NULL )
    {   
        int nBKUpHeight = m_pImgSliderBkUp->GetHeight();
        int nBkMidHeight = m_pImgSliderBkCenter->GetHeight();
        int nBkDownHeight = m_pImgSliderBkDown->GetHeight();
        int nBkWidth = m_pImgSliderBkUp->GetWidth();
           
        int nPosX = point.x;
        int nPosY = point.y ;
        int nCenterHeight = cRect.Height() - nBKUpHeight - nBkDownHeight;
        // 上
        pGraphics->DrawImage( m_pImgSliderBkUp, nPosX, nPosY, nBkWidth, nBKUpHeight );
        // 下
        pGraphics->DrawImage( m_pImgSliderBkDown, nPosX, nPosY + nBKUpHeight + nCenterHeight, nBkWidth, nBkDownHeight );

		nUpPosX = nPosX;
		nUpPosY = nPosY;
		nDownPosY = nPosY + nBKUpHeight + nCenterHeight + nBkDownHeight;

        nPosY += nBKUpHeight;   
        // 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
        for ( int nIndex = 0; nIndex < ( nCenterHeight / nBkMidHeight ); nIndex++ )
        {
            pGraphics->DrawImage( m_pImgSliderBkCenter, nPosX, nPosY, nBkWidth, nBkMidHeight);
            nPosY += nBkMidHeight;
        } 
        pGraphics->DrawImage( m_pImgSliderBkCenter, nPosX, nPosY, nBkWidth, nCenterHeight % nBkMidHeight );
    }


	//绘制左 右侧移动的图片
	Image *pImageUpMove = NULL;
    switch ( m_emUpMoveStatus )
    {
    case emStatusMoveBtnNormal:
        pImageUpMove = m_pImgUpMove;
        break;
    case emStatusMoveBtnDown:
        pImageUpMove = m_pImgUpMoveDown;
        break;
    }
	
	Image *pImageDownMove = NULL;
    switch ( m_emDownMoveStatus )
    {
    case emStatusMoveBtnNormal:
        pImageDownMove = m_pImgDownMove;
        break;
    case emStatusMoveBtnDown:
        pImageDownMove = m_pImgDownMoveDown;
        break;
    }
	
	if ( pImageUpMove != NULL && pImageDownMove != NULL )
	{
		nDownPosY -= pImageDownMove->GetHeight();
		pGraphics->DrawImage( pImageUpMove, nUpPosX + 1, nUpPosY + 2, pImageUpMove->GetWidth(), pImageUpMove->GetHeight() );
		pGraphics->DrawImage( pImageDownMove, nUpPosX + 1, nDownPosY - 2, pImageDownMove->GetWidth(), pImageDownMove->GetHeight() );
		
		m_cUpMoveIconRect.SetRect( nUpPosX + 1, nUpPosY + 2, nUpPosX + 1 + pImageUpMove->GetWidth(), nUpPosY + 2 +pImageUpMove->GetHeight() );
		m_cDownMoveIconRect.SetRect( nUpPosX + 1, nDownPosY - 2, nUpPosX + 1 + pImageDownMove->GetWidth(), nDownPosY - 2 + pImageDownMove->GetHeight() );
	}


    Image* pSliderUp = NULL;
    Image* pSliderCenter = NULL;
    Image* pSliderDown = NULL;

    if ( m_bLButtonDown )
    {
        pSliderUp = m_pImgSliderHilightUp;
        pSliderCenter = m_pImgSliderHilightCenter;
        pSliderDown = m_pImgSliderHilightDown;
    }
    else
    {
        pSliderUp = m_pImgSliderNormalUp;
        pSliderCenter = m_pImgSliderNormalCenter;
        pSliderDown = m_pImgSliderNormalDown;
    }

    if ( pSliderUp == NULL || pSliderCenter == NULL || pSliderDown == NULL )
    {   
        return S_FALSE;
	}

    int nSliderUpHeight = pSliderUp->GetHeight();
    int nSliderMidHeight = pSliderCenter->GetHeight();
    int nSliderDownHeight = pSliderDown->GetHeight();
    int nSliderWidth = pSliderUp->GetWidth();

    int nSliderPos = 0;
    int nSliderHeight = 0;
    
    //计算滑条位置
	if ( NULL == pImageUpMove )
	{
		CalSliderPos( cRect.Height(), nSliderUpHeight + nSliderDownHeight, nSliderPos, nSliderHeight );	
	}
    else
	{
		CRect cListRect;
		m_pListWnd->GetClientRect( cListRect );
		CalSliderPos( cRect.Height() - 2*(m_pImgUpMove->GetHeight() + 2) - 2, cListRect.Height(), nSliderUpHeight + nSliderDownHeight, nSliderPos, nSliderHeight );
		nSliderPos += (m_pImgUpMove->GetHeight() + 2) + 1;
	}
    
    m_rctSlider.top = nSliderPos;
	m_rctSlider.bottom = nSliderPos + nSliderHeight;  

    //绘制滑动条
    int nPosX = point.x + m_nBkgImgOffset;
    int nPosY = point.y + nSliderPos;
    int nSliderCenterHeight = nSliderHeight - nSliderUpHeight - nSliderDownHeight;
    // 上
    pGraphics->DrawImage( pSliderUp, nPosX, nPosY, nSliderWidth, nSliderUpHeight );
    // 下
    pGraphics->DrawImage( pSliderDown, nPosX, nPosY + nSliderUpHeight + nSliderCenterHeight, nSliderWidth, nSliderDownHeight );  
    nPosY += nSliderUpHeight;   
    // 中
    for ( int nIndex = 0; nIndex < ( nSliderCenterHeight / nSliderMidHeight ); nIndex++ )
    {
        pGraphics->DrawImage( pSliderCenter, nPosX, nPosY, nSliderWidth, nSliderMidHeight );
        nPosY += nSliderMidHeight;
    } 
    pGraphics->DrawImage( pSliderCenter, nPosX, nPosY, nSliderWidth, nSliderCenterHeight % nSliderMidHeight );

    return S_OK;
}

/*=============================================================================
函 数 名:CalSliderPos
功    能:计算滑条位置及长度
参    数:[in]nAllHeight     滑动条总高度=列表dlg高度
         [in]nSliderMinHeight 滑条最小长度
         [out]nSliderPos    滑条起始位置
         [out]nSliderHeight 滑条高度
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/11/28  1.0     肖楚然     创建
=============================================================================*/
void CTransparentListSlider::CalSliderPos( int nAllHeight, int nSliderMinHeight, int& nSliderPos, int& nSliderHeight )
{
    if ( m_nListHeight == 0 )
    {
        nSliderPos = 0;
        nSliderHeight = 0;
        return;
    }

    if ( nAllHeight < m_nListHeight )
    {
        nSliderPos = (float)m_nListYOffset * nAllHeight / m_nListHeight;

        nSliderHeight = (float)nAllHeight * nAllHeight / m_nListHeight; 
        
        if ( nSliderHeight < nSliderMinHeight )
        {
            nSliderHeight = nSliderMinHeight;

            nSliderPos = (float)m_nListYOffset * ( nAllHeight - nSliderHeight ) / ( m_nListHeight - nAllHeight );
        }
    }
    else
    {
        nSliderPos = 0;
        nSliderHeight = nAllHeight;
    }
}

void CTransparentListSlider::CalSliderPos( int nAllHeight, int nListDlgHeight, int nSliderMinHeight, int& nSliderPos, int& nSliderHeight )
{
    if ( m_nListHeight == 0 )
    {
        nSliderPos = 0;
        nSliderHeight = 0;
        return;
    }

    if ( nAllHeight < m_nListHeight )
    {
        nSliderPos = (float)m_nListYOffset * nAllHeight / m_nListHeight;

        nSliderHeight = (float)nAllHeight * nListDlgHeight / m_nListHeight; 
        
        if ( nSliderHeight < nSliderMinHeight )
        {
            nSliderHeight = nSliderMinHeight;

            nSliderPos = (float)m_nListYOffset * ( nAllHeight - nSliderHeight ) / ( m_nListHeight - nListDlgHeight );
        }
    }
    else
    {
        nSliderPos = 0;
        nSliderHeight = nAllHeight;
    }
}

void CTransparentListSlider::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int nMoveBtnOffset = 0;
	if ( NULL != m_pListWnd && NULL != m_pImgUpMove && NULL != m_pImgUpMove )   //点击左移 右移
	{
		CPoint pointOffset;
		pointOffset.y = 10;
		pointOffset.x = 0;
		CPoint ptRect;
		ptRect.x = m_cUpMoveIconRect.left + point.x;
		ptRect.y = m_cUpMoveIconRect.top + point.y;
		
		if ( m_cDownMoveIconRect.PtInRect( ptRect ) 
			&& !m_cUpMoveIconRect.PtInRect( ptRect ) )
		{
			m_bLButtonDown = TRUE;
			
			SetCapture();
			m_emDownMoveStatus = emStatusMoveBtnDown;
			m_pListWnd->SendMessage( WM_LIST_UPDATEPROGRESS, (WPARAM)&pointOffset, 0 );
			
			m_ptMouseDown = point;
			
			nMoveBtnOffset = m_pImgDownMove->GetWidth();
			
			NOTIF_PARENT_WND
				return;
		}
		else if ( m_cUpMoveIconRect.PtInRect( ptRect )
			&& !m_cDownMoveIconRect.PtInRect( ptRect ) )
		{
			m_bLButtonDown = TRUE;
			
			SetCapture();
			m_emUpMoveStatus = emStatusMoveBtnDown;
			pointOffset.y = -10;
			m_pListWnd->SendMessage( WM_LIST_UPDATEPROGRESS, (WPARAM)&pointOffset, 0 );
			
			m_ptMouseDown = point;
			
			nMoveBtnOffset = m_pImgDownMove->GetWidth();
			
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

void CTransparentListSlider::OnLButtonUp(UINT nFlags, CPoint point) 
{  
    if ( !m_bLButtonDown )
    {
        return;
	}

	if ( MoveButtonUpdate(point) )
	{
		return;
	}
	
	m_emUpMoveStatus = emStatusMoveBtnNormal;
	m_emDownMoveStatus = emStatusMoveBtnNormal;


    ReleaseCapture();
    m_bLButtonDown = FALSE;

    NOTIF_PARENT_WND
}

void CTransparentListSlider::OnMouseMove(UINT nFlags, CPoint point) 
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

    int nYOffSet = point.y - m_ptMouseDown.y;

    m_ptMouseDown = point;

    CRect cRect;
    GetWindowRect( &cRect );
    int nDlgHeight = cRect.Height();
    int nListOffset = 0;
    //换算为列表需要移动的距离
    if ( nDlgHeight > 0 && m_nListHeight > nDlgHeight )
    {
        nListOffset = nYOffSet * m_nListHeight / nDlgHeight;
    }

    CPoint pointOffset;
    pointOffset.x = 0;
    pointOffset.y = nListOffset;
    if ( m_pListWnd != NULL )
    {
        m_pListWnd->SendMessage( WM_LIST_UPDATEPROGRESS, (WPARAM)&pointOffset, 0 );
    }
}

BOOL CTransparentListSlider::MoveButtonUpdate(CPoint point)
{
	if ( NULL == m_pImgDownMove )
	{
		return FALSE;
	}
	
	CPoint ptRect;
	ptRect.x = m_cUpMoveIconRect.left + point.x;
	ptRect.y = m_cUpMoveIconRect.top + point.y;
	
	if ( !m_bLButtonDown )
	{
		if ( NULL != m_pImgDownMove && m_cDownMoveIconRect.PtInRect( ptRect )
			&& !m_cUpMoveIconRect.PtInRect( ptRect ))
		{
			m_emDownMoveStatus = emStatusMoveBtnNormal;
			m_emUpMoveStatus = emStatusMoveBtnNormal;
			m_bLButtonDown = FALSE;
			ReleaseCapture();
			NOTIF_PARENT_WND
				return TRUE;
		}
		else if ( NULL != m_pImgUpMove && m_cUpMoveIconRect.PtInRect( ptRect )
			&& !m_cDownMoveIconRect.PtInRect( ptRect ) )
		{
			m_emUpMoveStatus = emStatusMoveBtnNormal;
			m_emDownMoveStatus = emStatusMoveBtnNormal;
			m_bLButtonDown = FALSE;
			ReleaseCapture();
			NOTIF_PARENT_WND
				return TRUE;
		}
	}
	
	return FALSE;
}

void CTransparentListSlider::OnSize(UINT nType, int cx, int cy)
{
    CTransparentBaseWnd::OnSize(nType, cx, cy);
    CRect rect;
    GetClientRect(&rect);
    m_rctSlider.left = rect.left;
    m_rctSlider.right = rect.right; 
}


void CTransparentListSlider::SetImage( CString strImageFolder )
{
    if ( "" == strImageFolder )
    {
        return;
    }

    String strFile = strImageFolder + "\\" + CTransparentListSlider::strNormalTop;
    m_pImgSliderNormalUp = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListSlider::strNormalMiddle;
    m_pImgSliderNormalCenter = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListSlider::strNormalBottom;
    m_pImgSliderNormalDown = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListSlider::strHilightTop;
    m_pImgSliderHilightUp = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListSlider::strHilightMiddle;
    m_pImgSliderHilightCenter = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListSlider::strHilightBottom;
    m_pImgSliderHilightDown = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListSlider::strBkTop;
    m_pImgSliderBkUp = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListSlider::strBkMiddle;
    m_pImgSliderBkCenter = CSrcManage::GetImage( strFile.c_str() );
    strFile = strImageFolder + "\\" + CTransparentListSlider::strBkBottom;
    m_pImgSliderBkDown = CSrcManage::GetImage( strFile.c_str() );


	strFile = strImageFolder + "\\" + CTransparentListSlider::strBkUpMove;
	m_pImgUpMove = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentListSlider::strBkDownMove;
    m_pImgDownMove = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentListSlider::strBkUpMoveDown;
	m_pImgUpMoveDown = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentListSlider::strBkDownMoveDown;
    m_pImgDownMoveDown = CSrcManage::GetImage( strFile.c_str() );
   
    if ( m_pImgSliderBkCenter != NULL && GetParent() != NULL )
    {
        //滑条宽度根据图片调节
        int nWidth = m_pImgSliderBkCenter->GetWidth();
        CRect rect;
        GetWindowRect( &rect ); 
        GetParent()->ScreenToClient( rect );    
        rect.right = rect.left + nWidth;
        MoveWindow( &rect );

        //调节背景图片与滑条图片间距
        if ( m_pImgSliderNormalCenter != NULL )
        {
            int nNorWidth = m_pImgSliderNormalCenter->GetWidth();
            if ( nWidth > nNorWidth )
            {
                m_nBkgImgOffset = ( nWidth - nNorWidth ) / 2;
            }
        }
    }
}


void CTransparentListSlider::SetImage( CString strImageTop, CString strImageMiddle, CString strImageBottom,
                                       CString strBkTop, CString strBkMiddle, CString strBkBottom )
{
	m_pImgSliderNormalUp = CSrcManage::GetImage( strImageTop );
    m_pImgSliderNormalCenter = CSrcManage::GetImage( strImageMiddle );
    m_pImgSliderNormalDown = CSrcManage::GetImage( strImageBottom );

    if ( !strBkTop.IsEmpty() )
    {
        m_pImgSliderBkUp = CSrcManage::GetImage( strBkTop );
    }
    if ( !strBkMiddle.IsEmpty() )
    {
        m_pImgSliderBkCenter = CSrcManage::GetImage( strBkMiddle );
    }
    if ( !strBkBottom.IsEmpty() )
    {
        m_pImgSliderBkDown = CSrcManage::GetImage( strBkBottom );
    }
}

void CTransparentListSlider::SetImage( UINT nImgNormalUp, UINT nImgNormalCenter, UINT nImgNormalDown, 
                                      UINT nImgHilightUp, UINT nImgHilightCenter, UINT nImgHilightDown,
                                      UINT nImgBkUp, UINT nImgBkCenter, UINT nImgBkDown, const CString& strImgType )
{   
    m_pImgSliderNormalUp = CSrcManage::GetImage( nImgNormalUp, strImgType );
    m_pImgSliderNormalCenter = CSrcManage::GetImage( nImgNormalCenter, strImgType );
    m_pImgSliderNormalDown = CSrcManage::GetImage( nImgNormalDown, strImgType );
    m_pImgSliderHilightUp = CSrcManage::GetImage( nImgHilightUp, strImgType );
    m_pImgSliderHilightCenter = CSrcManage::GetImage( nImgHilightCenter, strImgType );
    m_pImgSliderHilightDown = CSrcManage::GetImage( nImgHilightDown, strImgType );
    m_pImgSliderBkUp = CSrcManage::GetImage( nImgBkUp, strImgType );
    m_pImgSliderBkCenter = CSrcManage::GetImage( nImgBkCenter, strImgType );
    m_pImgSliderBkDown = CSrcManage::GetImage( nImgBkDown, strImgType );

    if ( m_pImgSliderBkCenter != NULL && m_pImgSliderNormalCenter != NULL )
    {
        //调节背景图片与滑条图片间距
        int nWidth = m_pImgSliderBkCenter->GetWidth();                
        int nNorWidth = m_pImgSliderNormalCenter->GetWidth();
        if ( nWidth > nNorWidth )
        {
            m_nBkgImgOffset = ( nWidth - nNorWidth ) / 2;
        }
    }
}