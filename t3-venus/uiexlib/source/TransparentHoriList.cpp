/*****************************************************************************
模块名      : 通用横排列表
文件名      : transparenthorilist.cpp
相关文件    : transparenthorilist.h
文件实现功能: 通用列表相关功能，列表第一级子条目横排
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
  日  期      版本        修改人      修改内容
2012/04/01    1.0         肖楚然        创建
2012/12/14    2.0         肖楚然      整合到uiexlib
******************************************************************************/

#include "stdafx.h"
#include "TransparentHoriList.h"
#include "item.h"
#include "dragWindow.h"
#include "bitmapHelp.h"
#include "algorithm.h"
#include "listfuncmanage.h"

#define  TIMER_HANDLE_MOVING  101     //定时器ID
#define  TIMER_INTERVAL       10      //定时器时间间隔
#define  MOVE_SPEED           350       
const CString CTransparentHoriList::strTopLeft = "topleft.png";
const CString CTransparentHoriList::strTopCenter = "topcenter.png";
const CString CTransparentHoriList::strTopRight = "topright.png";
const CString CTransparentHoriList::strCenterLeft = "centerleft.png";
const CString CTransparentHoriList::strCenterRight = "centerright.png";
const CString CTransparentHoriList::strBottomLeft = "bottomleft.png";
const CString CTransparentHoriList::strBottomCenter = "bottomcenter.png";
const CString CTransparentHoriList::strBottomRight = "bottomright.png";
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransparentHoriList::CTransparentHoriList(CString strName, CRect rcWnd, CWnd* pWnd, UINT nID, DWORD dStyle, DWORD dwExStyle ) 
: IList( rcWnd.Width(), rcWnd.Height() ) , CTransparentBaseWnd( rcWnd, pWnd, dStyle, "", nID, dwExStyle )
{
	m_nTotalXOffset = 0;
	m_nMoveSpeed = 0;
	m_nNextXOffset = 0;
	m_bLBtnDown = FALSE;
    m_bTouchDown = FALSE;
	m_bDragEnable = FALSE;
	m_bClickNoSel = FALSE;
	m_pSelItem = NULL;
	m_pLastItem = NULL;
	m_dwSelDataKey = -1;
	
	m_pImgTopLeft = NULL;
    m_pImgTopCenter = NULL;
    m_pImgTopRight = NULL;	
    m_pImgCenterLeft = NULL;
	m_pImgCenterRight = NULL;
    m_pImgBottomLeft = NULL;
    m_pImgBottomCenter = NULL;
	m_pImgBottomRight = NULL;
}

CTransparentHoriList::~CTransparentHoriList()
{
    if ( NULL != m_pImageBK )
    {
        delete m_pImageBK;
        m_pImageBK = NULL;
    }
    
    Clear();
}


BEGIN_MESSAGE_MAP(CTransparentHoriList, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CTransparentList)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDBLCLK()
ON_WM_SIZE()
ON_WM_TIMER()
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
ON_MESSAGE( WM_BIND_WND_HIDE, OnBindWndHide )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentHoriList message handlers
LRESULT CTransparentHoriList::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{  
	if ( IsWindowVisible() == FALSE )
	{
		return S_FALSE;
	}
	Graphics* pGraphics = (Graphics*)wParam;
	if ( pGraphics == NULL )
	{
        if ( GetParent() != NULL )
        {
		    GetParent()->SendMessage( WM_REDRAW_UI, wParam, lParam );
        }
		return S_OK;
	}

    HWND hGraphWnd = (HWND )lParam;
    CWnd * pGraphWnd = FromHandle(hGraphWnd);
    if ( hGraphWnd == NULL )
    {
        return S_FALSE;
    }
	
	DrawUI( pGraphics, /*GetParent()*/ pGraphWnd );
	return S_OK;
}

void CTransparentHoriList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bLBtnDown = FALSE;

	if ( m_pItemList == NULL )
	{
		return;
	}

	//设置焦点
	HWND hFocusWnd = ::GetFocus();
	if ( hFocusWnd != m_hWnd )
	{   
		this->SetFocus();
	}	

	if ( m_nMoveSpeed != 0 )
	{   		
		m_nMoveSpeed = 0;
		KillTimer(TIMER_HANDLE_MOVING);	
	} 

	m_bLBtnDown = TRUE;
	m_ptMouseNow = point;
	m_ptMouseLast = point;
	m_ptMouseDown = point;

	IItemList* pSelList = NULL;
	IsClick( m_pItemList, point, &pSelList );

	if ( m_pSelItem != NULL && m_pSelItem != pSelList )
	{
		SetSelItemStatus( emItemStatusNormal );
		
		m_pSelItem = NULL;
		m_pLastItem = NULL;
		m_dwSelDataKey = -1;
	}

	if ( pSelList != NULL )
	{
		m_pSelItem = pSelList;

		while( pSelList != NULL && pSelList->GetParentItem() != NULL )
		{
			IBaseItem* pBaseItem = pSelList->GetItemData();

			if ( pBaseItem->GetItemStatus() == emItemStatusDisable )
			{    
				m_pSelItem = NULL;
            
				return;
			}
			pBaseItem->SetItemStatus( emItemStatusDown );

			if ( pBaseItem->GetUserData() != NULL )
			{
				IData* pData = const_cast<IData*>( pBaseItem->GetUserData() );
				m_dwSelDataKey = pData->GetDataKey();
			}
            //如果点击条目有响应事件，不再将父条目设为选中
            if ( pBaseItem->GetFunc() != IBaseItem::strDefaultFunc )
            {
                break;
            }

			pSelList = pSelList->GetParentItem();
		}
			
		m_pLastItem = m_pSelItem;
	}

	SendMessage( WM_REDRAW_UI, 0, TRUE );
	
	SetCapture();
}

void CTransparentHoriList::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    OnLButtonDown( nFlags, point ); 
}

void CTransparentHoriList::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( !m_bLBtnDown )
	{   
		return;
	} 	

    //CString msg;
    //msg.Format( _T("\nCTransparentHoriList OnLButtonUp, point.x: %d, point.y: %d \n"), point.x, point.y );
    //AfxOutputDebugString( msg );
	
	m_bLBtnDown = FALSE;
    //m_bTouchDown = FALSE;
				
	if ( m_pSelItem != NULL )
	{
		if ( point == m_ptMouseDown )
		{

			SetSelItemStatus( emItemStatusSel );

			IBaseItem* pItem = m_pSelItem->GetItemData();
			if ( CCheckItem* pCheckItem = dynamic_cast<CCheckItem*>(pItem) )
			{
				if ( pCheckItem != NULL && pCheckItem->GetItemStatus() != emItemStatusDisable )
				{
					pCheckItem->Click();
				}
				//CheckItem设为不选中状态，认为没有选中项。防止刷新后有选中项
				if ( FALSE == pCheckItem->IsItemSel() )
				{
					m_dwSelDataKey = -1;
				}
			}
            
            if ( CButtonItem* pCheckItem = dynamic_cast<CButtonItem*>(pItem) ) //如果是CButtonItem的话，释放capture 修改Bug00147721
            {
                if ( GetCapture() == this )
                {
                    ReleaseCapture();
	            }
            }

			Clicked( nFlags, point );

			if ( m_bClickNoSel )
			{
				SetSelItemStatus( emItemStatusNormal );
				m_pSelItem = NULL;
				m_dwSelDataKey = -1;
			}
		}
		else
		{
			SetSelItemStatus( emItemStatusNormal );
			m_pSelItem = NULL;
			m_dwSelDataKey = -1;           
		}		
	}
 
	if ( abs(m_ptMouseLast.x - m_ptMouseNow.x) > 6 ) //翻页
    {
		BOOL bNext = TRUE;
		if ( m_ptMouseNow.x - m_ptMouseLast.x > 0 )
		{
			bNext = FALSE;
			m_nMoveSpeed = MOVE_SPEED;
		}
		else
		{
			m_nMoveSpeed = -MOVE_SPEED;
		}
		//m_nMoveSpeed = (m_ptMouseNow.x - m_ptMouseLast.x) / 5;
		m_nNextXOffset = GetNextPageOffset( bNext );
		SetTimer( TIMER_HANDLE_MOVING, TIMER_INTERVAL, NULL );	   
    }
	else
	{
		m_nNextXOffset = GetBackPageOffset();
		if ( m_nTotalXOffset > -m_nNextXOffset )
		{
			m_nMoveSpeed = -MOVE_SPEED;
		}
		else if ( m_nTotalXOffset < -m_nNextXOffset )
		{
			m_nMoveSpeed = MOVE_SPEED;
		}
		else
		{
			m_nMoveSpeed = 0;
			PostMessage( UI_LISTOFFSET_NOTIFY );
		}
		if ( m_nMoveSpeed != 0 )
		{
			SetTimer( TIMER_HANDLE_MOVING, TIMER_INTERVAL, NULL );
		}		
	}

	if ( GetCapture() == this )
	{
		ReleaseCapture();
	}
	
    //if ( m_pSelItem == NULL || m_pSelItem == m_pItemList  )
    //{
    //    //通知外部当前没有选中项
    //     PostMessage(WM_LST_UN_SELECT_ITEM);
    //}
   
	SendMessage( WM_REDRAW_UI, 0, 0 );

//	CTransparentWnd::OnLButtonUp(nFlags, point);
}

void CTransparentHoriList::SetSelItemStatus( EmItemStatus emStatus )
{	
	if ( m_pSelItem != NULL )
	{
		IItemList* pList = m_pSelItem;
		while( pList != NULL && pList->GetParentItem() != NULL )
		{
			IBaseItem* pItem = pList->GetItemData();
			if ( pItem->GetItemStatus() != emItemStatusDisable )
			{
				pItem->SetItemStatus( emStatus );
			}
			pList = pList->GetParentItem();
		}
	}
}


void CTransparentHoriList::Clicked( UINT nFlags, CPoint point )
{
    if ( m_pSelItem == 0 )
    {
        return;
    }
    IBaseItem* pBaseItem = m_pSelItem->GetItemData();
    if ( pBaseItem == 0 )
    {
        return;
    }
    
    bool bFind = false;
    String strFunc = pBaseItem->GetFunc();
    IItemList* pList = m_pSelItem;
    while( pList != 0 && pList->GetParentItem() != 0 )
    {		
        pBaseItem = pList->GetItemData();
        strFunc = pBaseItem->GetFunc();
        if ( strFunc != IBaseItem::strDefaultFunc )
        {
            bFind = true;
            break;
        }
        pList = pList->GetParentItem();
    }
    if ( bFind == true )
    {
        CRect rcFrame = GetFrameInScreen( pList );
        Args_ClickItemInfo clickInfo( this, pList, rcFrame );
        
        CListFuncManage::GetSingletonPtr()->ExeFunc( strFunc, clickInfo );
    }	
    else
    {
        //LOGEVENT( "条目点击，但是没有找到任何注册的事件" );
    }
}


CRect CTransparentHoriList::GetFrameInScreen( IItemList* pList )
{
	ASSERT( pList );
	IItemList* pTemp = pList;
	IBaseItem* pData = pTemp->GetItemData();
	CRect rcChild = pData->GetItemRect();
	while ( pTemp != 0 && pTemp->GetParentItem() != 0 && pTemp->GetParentItem()->GetParentItem() != 0 )
	{		
		pTemp = pTemp->GetParentItem();
		pData = pTemp->GetItemData();
		rcChild = pData->GetItemRect();
	}
	pData = m_pItemList->GetItemData();
	CPoint ptOffset = pData->GetOffset();
	rcChild.OffsetRect( ptOffset );
	ClientToScreen( &rcChild );
	return rcChild;
}


void CTransparentHoriList::Draw( IArgs* pArgs )
{
	IList::Draw( pArgs, 0, m_rctDlg.Height() );
}

void CTransparentHoriList::DrawUI( Graphics* pGraphics, CWnd* pParent )
{   
    if ( pGraphics == NULL  || pParent == NULL )
    {
        return ;
    }

// 	delete m_pCacheAllImage1;	
// 	m_pCacheAllImage1 = new Bitmap( m_BakWidth, m_BakHeight );
// 	Graphics g( m_pCacheAllImage1 );
// 	g.DrawImage( m_pCacheBkImage, 0, 0, m_BakWidth, m_BakHeight );

	CRect rc = GetListRect();

	Bitmap* pSubBitmap = new Bitmap( rc.Width(), rc.Height() ); 
	Graphics* pGraph = Graphics::FromImage( pSubBitmap );
	
	if ( m_pImageBK != NULL )
	{
		pGraph->DrawImage( m_pImageBK, 0, 0, rc.Width(), rc.Height() );
	}	
	
	Args_Graphics args_Graphics( pGraph, Rect( rc.left, rc.top, rc.Width(), rc.Height() ) );
	Draw( &args_Graphics );	

	CRect rcWnd;
	this->GetWindowRect( rcWnd );
	pParent->ScreenToClient( rcWnd );
	pGraphics->DrawImage( pSubBitmap, rcWnd.left, rcWnd.top );

	delete pSubBitmap;
 	pSubBitmap = 0;
	delete pGraph;
	pGraph = 0;
//	CTransparentWnd::DrawUI( pGraphics, pParent );
} 

CRect CTransparentHoriList::GetListRect()
{
	
	this->GetClientRect( m_rctDlg );

	return m_rctDlg;
}


void CTransparentHoriList::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( nFlags != MK_LBUTTON || !m_bLBtnDown  )
    {   
		return;
    }
	
	m_ptMouseLast = m_ptMouseNow;
	m_ptMouseNow = point;

    if( m_ptMouseNow == m_ptMouseLast )
    {
        return;
    }

	ListMove();
		
	//移出对话框，拖拽开始		
	if ( m_bDragEnable && m_pSelItem != NULL && IsReadyForDrag() )
	{    				
		IItemList* pDragItem = m_pSelItem ;
		while( pDragItem != NULL && pDragItem != m_pItemList )
		{
			IBaseItem* pItem = pDragItem->GetItemData();
			if ( pItem == NULL )
			{
				break;
			}
			if ( pItem->GetDragStatus() )
			{
				if ( GetCapture() == this )
				{
					ReleaseCapture();
				}
				CDragWindow * pDragWnd = CDragWindow::GetDragWindow(); 	
				pDragWnd->SetWindowText( "DragWnd" );
				if ( pDragWnd != NULL )
				{
				//	m_bDraging = TRUE;				
					Bitmap* pBitmap = CBitmapHelp::CreateBitmap( pDragItem );
					IData *pData = const_cast<IData*>( pItem->GetUserData() );
					CPoint pt;
					GetCursorPos( &pt );
					pDragWnd->BeginDrag( this, pt, pBitmap, pData );
					break;
				}
			}
			pDragItem = pDragItem->GetParentItem();
		}		
	} 	


	SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
}

void CTransparentHoriList::ListMove()
{
	if ( m_pSelItem == NULL )
	{
		return;
	}
	
	IItemList* pSelList = m_pSelItem;
	while( pSelList != NULL )
	{
		IBaseItem* pItem = pSelList->GetItemData();
		if ( pItem != NULL && pItem->GetMoveStatus() )
		{
			break;
		}
		pSelList = pSelList->GetParentItem();
	}
	if ( pSelList == NULL )
	{
		return;
	}

	//m_nTotalYOffset += ( m_ptMouseNow.y - m_ptMouseLast.y );
	m_nTotalXOffset += ( m_ptMouseNow.x - m_ptMouseLast.x );

	//CRect retList = GetFrame( pSelList );

	if ( m_nTotalXOffset > 0 )
	{
		m_nTotalXOffset = 0;  	
	}	
	if ( m_nTotalXOffset < m_rctDlg.Width() - m_rctList.Width() )
	{
		m_nTotalXOffset = m_rctDlg.Width() - m_rctList.Width();	
		if ( m_nTotalXOffset > 0 )
		{	
			m_nTotalXOffset = 0;
		}	
	}
						
	IBaseItem* pItem = pSelList->GetItemData();
	if ( pItem != NULL )
	{
		pItem->SetOffset( CPoint(m_nTotalXOffset, 0) );
	}
}

void CTransparentHoriList::ListAutoMove()
{	
	if ( m_pLastItem == NULL )
	{
		m_nMoveSpeed = 0;
		return;
	}

	IItemList* pSelList = m_pLastItem;    
	while( pSelList != NULL )
	{
		IBaseItem* pItem = pSelList->GetItemData();
		if ( pItem != NULL && pItem->GetMoveStatus() )
		{
			break;
		}
		pSelList = pSelList->GetParentItem();
	}	
	if ( pSelList == NULL )
	{
		return;
	}

	m_nTotalXOffset += m_nMoveSpeed;
	//m_nMoveSpeed *= 0.96;
	
	if ( m_nMoveSpeed > 0 )
	{
		if ( m_nTotalXOffset >= -m_nNextXOffset )
		{
			m_nTotalXOffset = -m_nNextXOffset;
			m_nMoveSpeed = 0;
		}
	}
	else
	{
		if ( m_nTotalXOffset <= -m_nNextXOffset )
		{
			m_nTotalXOffset = -m_nNextXOffset;
			m_nMoveSpeed = 0;
		}
	}

	if ( m_nTotalXOffset > 0 )
	{    
		m_nMoveSpeed = 0; 
		m_nTotalXOffset = 0;  	 
	}
	
	if ( m_nTotalXOffset < m_rctDlg.Width() - m_rctList.Width() )
	{
		m_nTotalXOffset = m_rctDlg.Width() - m_rctList.Width();	
		if ( m_nTotalXOffset > 0 )
		{	 
			m_nMoveSpeed = 0;
			m_nTotalXOffset = 0; 
		} 
	}  

	IBaseItem* pItem = pSelList->GetItemData();
	if ( pItem != NULL )
	{
		pItem->SetOffset( CPoint(m_nTotalXOffset, 0) );
	}
	
	if ( 0 == m_nMoveSpeed )
	{
		CheckTotalOffset();

		int nOffsetIndex = GetOffsetIndex();
		PostMessage( UI_LISTOFFSET_NOTIFY, nOffsetIndex );
		
		KillTimer(TIMER_HANDLE_MOVING);  
	} 

	SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
}



void CTransparentHoriList::OnSize(UINT nType, int cx, int cy) 
{
	CTransparentBaseWnd::OnSize(nType, cx, cy);
	
	CRect rc;
//	this->GetClientRect( rc );
	this->GetWindowRect(rc);
	SetListSize( rc.Width(), rc.Height() );
	// TODO: Add your message handler code here	
}

void CTransparentHoriList::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if ( nIDEvent == TIMER_HANDLE_MOVING )
	{
		if ( m_nMoveSpeed == 0 )
		{   
			KillTimer(TIMER_HANDLE_MOVING);
		} 
		
		ListAutoMove();
	}
	
	CTransparentBaseWnd::OnTimer(nIDEvent);
}


void CTransparentHoriList::SetDragEnable( BOOL bDrag )
{
	m_bDragEnable = bDrag;
}

void CTransparentHoriList::SetClickNoSel( BOOL bSel )
{
	m_bClickNoSel = bSel;
}

void CTransparentHoriList::ResetSelItem( BOOL bResetOffset )
{
    int nItemCount = m_pItemList->GetItemCount();
    if ( nItemCount <= 0)
    {
		m_nTotalXOffset = 0;
    }

	if ( m_nMoveSpeed != 0 )
	{   		
		//m_nMoveSpeed = 0;
		//KillTimer(TIMER_HANDLE_MOVING);
		m_pLastItem = m_pItemList;
	} 
	else
	{
		CheckTotalOffset(); //检查是否刷新后超过了最后一页
	}

	m_rctList = GetFrame( m_pItemList );

	if ( m_dwSelDataKey == -1 )
	{
		return;
	}
	
	for ( int nIndex = 0; nIndex < nItemCount; nIndex++ )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( nIndex );
		if ( pSubList != NULL )
		{
			for ( int i = 0; i < pSubList->GetItemCount(); i++ )
			{
				IItemList* pList = pSubList->GetItemByIndex( i );
				if ( pList != NULL )
				{
					IBaseItem* pSubItem = pList->GetItemData();
					if ( pSubItem != NULL && pSubItem->GetUserData() != NULL )
					{		
						IData* pData = const_cast<IData*>( pSubItem->GetUserData() );
						if ( pData->GetDataKey() == m_dwSelDataKey )
						{
							m_pSelItem = pList;
							pSubItem->SetItemStatus( emItemStatusSel );
							
							if ( !m_bLBtnDown )//LBtnDown时不设置，防止BtnUp后再设一次
							{
								if ( CCheckItem* pCheckItem = dynamic_cast<CCheckItem*>(pSubItem) )
								{
									if ( pCheckItem != NULL && pCheckItem->GetItemStatus() != emItemStatusDisable )
									{
										pCheckItem->Click();
									}
								}
							}
															
							if ( bResetOffset )
							{
								//int nYOffset = GetOffsetHeight( nIndex );
								//SetYOffset( -nYOffset );
							}					
							return;
						}
					}	
				}					
			}					
		}
	}

}


void CTransparentHoriList::SetSelItem( unsigned long dwDataKey )
{
	if ( m_pSelItem != NULL )
	{
		SetSelItemStatus( emItemStatusNormal );
		m_pSelItem = NULL;
	}

	if ( dwDataKey == -1 )
	{
		m_dwSelDataKey = -1;
		return;
	}

	m_dwSelDataKey = dwDataKey;
	ResetSelItem( TRUE );
}

IBaseItem* CTransparentHoriList::GetSelItem()
{
	if ( m_pSelItem == NULL || m_dwSelDataKey == -1 )
	{
		return NULL;
	}

	int nItemCount = m_pItemList->GetItemCount();
	for ( int nIndex = 0; nIndex < nItemCount; nIndex++ )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( nIndex );
		if ( pSubList != NULL )
		{
			IBaseItem* pSubItem = pSubList->GetItemData();
			if ( pSubItem != NULL && pSubItem->GetUserData() != NULL )
			{		
				IData* pData = const_cast<IData*>( pSubItem->GetUserData() );
				if ( pData->GetDataKey() == m_dwSelDataKey )
				{
					return pSubItem;
				}
			}		
		}
	}
	return NULL;
}

void CTransparentHoriList::CheckTotalOffset()
{
	int nItemCount = m_pItemList->GetItemCount();
	if ( nItemCount > 0 )
	{
		int nOffset = GetOffSetWidth( nItemCount - 1 );
		if ( abs(m_nTotalXOffset) > nOffset )
		{
			m_nTotalXOffset = -nOffset;
			SetTotalOffset( m_nTotalXOffset );
		}
	}
	else
	{
		m_nTotalXOffset = 0;
		SetTotalOffset( m_nTotalXOffset );
	}
}


int CTransparentHoriList::GetNextPageOffset( BOOL bNext )
{
	int nIndex = 0;
	int nCount = m_pItemList->GetItemCount();
	
	int nWidth = 0;
	int nOffset = 0;

	for ( int i = 0; i < nCount; i++ )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( i );
		if ( pSubList != NULL )
		{
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem != NULL )
			{
				nWidth += pItem->GetItemWidth() + CLayoutAlgorithm_Hori::nXSpace;

				if ( abs(m_nTotalXOffset) >= nWidth )
				{
					nIndex++;
				}
				else
				{
					break;
				}
			}			
		}		
	}

	if ( bNext )
	{
		nIndex++;
		if ( nIndex > nCount - 1 )
		{
			nIndex = nCount - 1;
		}
	}

	nOffset = GetOffSetWidth( nIndex );

	return nOffset;
}


int CTransparentHoriList::GetBackPageOffset()
{
	int nIndex = 0;
	int nCount = m_pItemList->GetItemCount();
	
	int nWidth = 0;

	for ( int i = 0; i < nCount; i++ )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( i );
		if ( pSubList != NULL )
		{
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem != NULL )
			{
				nWidth += pItem->GetItemWidth() + CLayoutAlgorithm_Hori::nXSpace;
				
				if ( abs(m_nTotalXOffset) >= nWidth )
				{
					nIndex++;
				}
				else
				{
					int nLength = nWidth + m_nTotalXOffset;
					if ( nLength < ( pItem->GetItemWidth() / 2 ) )
					{
						nIndex++;
					}
					break;
				}
			}			
		}		
	}

	int nOffset = GetOffSetWidth( nIndex );
	
	return nOffset;
}


int CTransparentHoriList::GetOffSetWidth( int nIndex )
{
	int nWidth = 0;

	for ( int i = 0; i < nIndex; i++ )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( i );
		if ( pSubList != NULL )
		{
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem != NULL )
			{
				nWidth += pItem->GetItemWidth() + CLayoutAlgorithm_Hori::nXSpace;
			}			
		}		
	}

	return nWidth;
}

int CTransparentHoriList::GetItemCount()
{
	int nCount = 0;
	if ( m_pItemList != NULL )
	{
		nCount = m_pItemList->GetItemCount();
	}
	return nCount;
}

int CTransparentHoriList::GetOffsetIndex()
{
	int nIndex = 0;
	int nCount = m_pItemList->GetItemCount();
	
	int nWidth = 0;

	for ( int i = 0; i < nCount; i++ )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( i );
		if ( pSubList != NULL )
		{
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem != NULL )
			{
				nWidth += pItem->GetItemWidth() + CLayoutAlgorithm_Hori::nXSpace;
				
				if ( abs(m_nTotalXOffset) >= nWidth )
				{
					nIndex++;
				}
				else
				{
					break;
				}
			}			
		}		
	}	

	return nIndex;
}


void CTransparentHoriList::SetOffsetIndex( int nIndex )
{
	if ( m_nMoveSpeed != 0 )
	{
		m_nMoveSpeed = 0;
		KillTimer(TIMER_HANDLE_MOVING);
	}

	int nOffset = GetOffSetWidth( nIndex );
	m_nNextXOffset = nOffset;
	
	if ( m_nTotalXOffset > -m_nNextXOffset )
	{
		m_nMoveSpeed = -MOVE_SPEED;
	}
	else if ( m_nTotalXOffset < -m_nNextXOffset )
	{
		m_nMoveSpeed = MOVE_SPEED;
	}
	else
	{
		m_nMoveSpeed = 0;
	}

	if ( m_pItemList != NULL )
	{
		m_pLastItem = m_pItemList;
	}

	SetTimer( TIMER_HANDLE_MOVING, TIMER_INTERVAL, NULL );
}


void CTransparentHoriList::SetTotalOffset( int nOffset )
{
	m_nTotalXOffset = nOffset;
	
	//CRect retList = GetFrame( m_pItemList );
	
	if ( m_nTotalXOffset > 0 )
	{    
		m_nTotalXOffset = 0;  	 
	}
	if ( m_nTotalXOffset < m_rctDlg.Width() - m_rctList.Width() )
	{
		m_nTotalXOffset = m_rctDlg.Width() - m_rctList.Width();	
		if ( m_nTotalXOffset > 0 )
		{	 
			m_nTotalXOffset = 0; 
		} 
	}  
	
	IBaseItem* pItem = m_pItemList->GetItemData();
	if ( pItem != NULL )
	{
		pItem->SetOffset( CPoint(m_nTotalXOffset, 0) );
	}
	
	SendMessage( WM_REDRAW_UI, 0, 0 );
}


LRESULT CTransparentHoriList::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    if ( message == WM_TOUCH_BUTTONDOWN )
    {
        //屏幕坐标点
        if ( !m_bLBtnDown )
        {
            //CPoint  point; 
            //::GetCursorPos(&point);          
            //this->ScreenToClient( &point );
            //OnLButtonDown( MK_LBUTTON, point );  
            //此时获取的坐标不对，不能执行OnLButtonDown
            OnTouchButtonDown();
        }     
    }
    //通过win7 Dll，注册窗口响应WM_TOUCH 触摸事件 -2014.3.6 xcr
    else if ( message == WM_TOUCH )
    {
//         if ( m_bTouchDown )
//         {
//             return CTransparentBaseWnd::DefWindowProc(message, wParam, lParam);
//         }
        
//       WINSDK_GetTouchInputPoint _WINSDK_GetTouchInputPoint;
//         
//       UINT cInputs = LOWORD(wParam);
        POINT ptInput;

        /*WINSDK_GetTouchInputInfo( lParam, cInputs, ptInput );*/
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
					ptInput.x = TOUCH_COORD_TO_PIXEL(tInput.x);  
					ptInput.y = TOUCH_COORD_TO_PIXEL(tInput.y);
					this->ScreenToClient( &ptInput );
                
                    //CString msg;
                    //msg.Format( _T("\nCTransparentHoriList WM_TOUCH Down, ptInput.x: %d, ptInput.y: %d \n"), ptInput.x, ptInput.y );
                    //AfxOutputDebugString( msg );

                    //m_bTouchDown = TRUE;

					OnLButtonDown( MK_LBUTTON, ptInput );
				}
                else if ( tInput.dwFlags & TOUCHEVENTF_UP )
                {            
                    ptInput.x = TOUCH_COORD_TO_PIXEL(tInput.x);  
					ptInput.y = TOUCH_COORD_TO_PIXEL(tInput.y);
                    this->ScreenToClient( &ptInput );

                    //CString msg;
                    //msg.Format( _T("\nCTransparentHoriList WM_TOUCH Up, ptInput.x: %d, ptInput.y: %d \n"), ptInput.x, ptInput.y );
                    //AfxOutputDebugString( msg );
                    
                    OnTouchUp( ptInput );
				}
			} 
			FreeLibrary( hInstLibrary );
		}
    }
	
    return CTransparentBaseWnd::DefWindowProc(message, wParam, lParam);
}


void CTransparentHoriList::OnTouchButtonDown()
{
    if ( m_nMoveSpeed != 0 )
    {   		
        m_nMoveSpeed = 0;
        KillTimer(TIMER_HANDLE_MOVING);	
    } 
    
	TCHAR chTemp[128];
	wsprintf(chTemp,_T("OnTouchButtonDown" ));
	::OutputDebugString(chTemp);

	m_bLBtnDown = TRUE;
}

void CTransparentHoriList::OnTouchUp( CPoint point )
{
    m_bLBtnDown = FALSE;
				
    if ( m_pSelItem != NULL )
    {
        if ( point == m_ptMouseDown )
        {           
            SetSelItemStatus( emItemStatusSel );

            if ( m_bClickNoSel )
            {
                SetSelItemStatus( emItemStatusNormal );
                m_pSelItem = NULL;
                m_dwSelDataKey = -1;
			}
        }
        else
        {
            SetSelItemStatus( emItemStatusNormal );
            m_pSelItem = NULL;
            m_dwSelDataKey = -1;           
        }		
	}

    if ( GetCapture() == this )
    {
        ReleaseCapture();
	}

	TCHAR chTemp[128];
	wsprintf(chTemp,_T("OnTouchUp" ));
	::OutputDebugString(chTemp);

    SendMessage( WM_REDRAW_UI, 0, 0 );
}



LRESULT CTransparentHoriList::OnBindWndHide( WPARAM wParam, LPARAM lParam )
{	
	if ( m_pSelItem != NULL && !m_bLBtnDown )
	{
		SetSelItemStatus( emItemStatusNormal );
		m_pSelItem = NULL;
		m_dwSelDataKey = -1;

		SendMessage( WM_REDRAW_UI, 0, 0 );
	}		
	return S_OK;
}


BOOL CTransparentHoriList::IsReadyForDrag()
{
	BOOL bDrag = FALSE;
	IBaseItem* pRootItem = m_pItemList->GetItemData();
	if ( pRootItem != NULL )
	{
		String strLayout = pRootItem->GetLayoutAlgorithm();
		if ( strLayout == IAlgorithm::strHori )
		{
			if ( m_rctDlg.top > m_ptMouseNow.y || m_rctDlg.bottom < m_ptMouseNow.y )
			{
				bDrag = TRUE;
			}
		}
		else
		{
			if ( m_rctDlg.left > m_ptMouseNow.x || m_rctDlg.right < m_ptMouseNow.x )
			{
				bDrag = TRUE;
			}
		}
	}
	return bDrag;
}


void CTransparentHoriList::SetImage( CString strImageFolder, BOOL bInvalidate /* = FALSE */ )
{	
	if ( "" == strImageFolder )
	{
		return;
	}
	String strFile = strImageFolder + "\\" + CTransparentHoriList::strTopLeft;
	m_pImgTopLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentHoriList::strTopCenter;
	m_pImgTopCenter = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentHoriList::strTopRight;
	m_pImgTopRight = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentHoriList::strCenterLeft;
	m_pImgCenterLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentHoriList::strCenterRight;
	m_pImgCenterRight = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentHoriList::strBottomLeft;
	m_pImgBottomLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentHoriList::strBottomCenter;
	m_pImgBottomCenter = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentHoriList::strBottomRight;
	m_pImgBottomRight = CSrcManage::GetImage( strFile.c_str() );
	
	m_pImageBK = MosaicListImage();

	CTransparentBaseWnd::SetImage( m_pImageBK, bInvalidate );
}

Image* CTransparentHoriList::MosaicListImage()
{
    if ( m_pImageBK != NULL )
    {
        return m_pImageBK;
    }

	CRect cRect;
	this->GetWindowRect( &cRect );

	if ( m_pImageBK == NULL )
	{
		m_pImageBK = new Bitmap( cRect.Width(), cRect.Height() );
	}	
	
	Graphics* pGraphics = Graphics::FromImage( m_pImageBK );
	
	if ( m_pImgTopLeft != NULL && m_pImgTopCenter != NULL && m_pImgTopRight != NULL && m_pImgBottomRight != NULL
		 && m_pImgCenterLeft != NULL && m_pImgCenterRight != NULL && m_pImgBottomLeft != NULL && m_pImgBottomCenter != NULL
		 && m_pImgTopLeft->GetWidth() != 0 && m_pImgTopCenter->GetWidth() != 0 && m_pImgBottomCenter->GetWidth() != 0
		 && m_pImgCenterLeft->GetHeight() != 0 && m_pImgCenterRight->GetHeight() != 0 )
    {
        unsigned int nPosTopX = m_pImgTopLeft->GetWidth();
		
        unsigned int dwTopCenterWidth = 0;
		if ( cRect.Width() > m_pImgTopLeft->GetWidth() + m_pImgTopRight->GetWidth() )
		{
			dwTopCenterWidth = cRect.Width() - m_pImgTopLeft->GetWidth() - m_pImgTopRight->GetWidth();
		}
		
        // 左上
        pGraphics->DrawImage( m_pImgTopLeft, 0, 0, m_pImgTopLeft->GetWidth(), m_pImgTopLeft->GetHeight() );
        // 右上
        pGraphics->DrawImage( m_pImgTopRight, cRect.Width() - m_pImgTopRight->GetWidth(), 0, m_pImgTopRight->GetWidth(), m_pImgTopRight->GetHeight() );		
        // 中上
        for ( unsigned int nIndex = 0; nIndex < ( dwTopCenterWidth / m_pImgTopCenter->GetWidth() ); nIndex++ )
        {
            pGraphics->DrawImage( m_pImgTopCenter, nPosTopX, 0, m_pImgTopCenter->GetWidth(), m_pImgTopCenter->GetHeight() );
            nPosTopX += m_pImgTopCenter->GetWidth();
        }
        pGraphics->DrawImage( m_pImgTopCenter, nPosTopX, 0, dwTopCenterWidth % m_pImgTopCenter->GetWidth(), m_pImgTopCenter->GetHeight() );

		unsigned int nPosBottomX = m_pImgBottomLeft->GetWidth();
		int nPosBottomY = cRect.Height() - m_pImgBottomRight->GetHeight();
        unsigned int dwBottomCenterWidth = 0;
		if ( cRect.Width() > m_pImgBottomLeft->GetWidth() + m_pImgBottomRight->GetWidth() )
		{
			dwBottomCenterWidth = cRect.Width() - m_pImgBottomLeft->GetWidth() - m_pImgBottomRight->GetWidth();
		}
		//左下  
		pGraphics->DrawImage( m_pImgBottomLeft, 0, cRect.Height() - m_pImgBottomLeft->GetHeight(), m_pImgTopLeft->GetWidth(), m_pImgTopLeft->GetHeight() );
		//右下
		pGraphics->DrawImage( m_pImgBottomRight, cRect.Width() - m_pImgBottomRight->GetWidth(), nPosBottomY, m_pImgBottomRight->GetWidth(), m_pImgBottomRight->GetHeight() );
		//中下
		nPosBottomY = cRect.Height() - m_pImgBottomCenter->GetHeight();
		for ( nIndex = 0; nIndex < ( dwBottomCenterWidth / m_pImgBottomCenter->GetWidth() ); nIndex++ )
        {
            pGraphics->DrawImage( m_pImgBottomCenter, nPosBottomX, nPosBottomY, m_pImgBottomCenter->GetWidth(), m_pImgBottomCenter->GetHeight() );
            nPosBottomX += m_pImgBottomCenter->GetWidth();
        }
        pGraphics->DrawImage( m_pImgBottomCenter, nPosBottomX, nPosBottomY, dwBottomCenterWidth % m_pImgBottomCenter->GetWidth(), m_pImgBottomCenter->GetHeight() );

		//左边
		unsigned int nPosLeftY = m_pImgTopLeft->GetHeight();
		unsigned int dwLeftHeight = 0;
		if ( cRect.Height() > m_pImgTopLeft->GetHeight() + m_pImgBottomLeft->GetHeight() )
		{
			dwLeftHeight = cRect.Height() - m_pImgTopLeft->GetHeight() - m_pImgBottomLeft->GetHeight();
		}
		for ( nIndex = 0; nIndex < ( dwLeftHeight / m_pImgCenterLeft->GetHeight() ); nIndex++ )
        {
            pGraphics->DrawImage( m_pImgCenterLeft, 0, nPosLeftY, m_pImgCenterLeft->GetWidth(), m_pImgCenterLeft->GetHeight() );
            nPosLeftY += m_pImgCenterLeft->GetHeight();
        }
        pGraphics->DrawImage( m_pImgCenterLeft, 0, nPosLeftY, m_pImgCenterLeft->GetWidth(), dwLeftHeight % m_pImgCenterLeft->GetHeight() );

		//右边
		unsigned int nPosRightY = m_pImgTopRight->GetHeight();
		int nPosRightX = cRect.Width() - m_pImgCenterRight->GetWidth();
		unsigned int dwRightHeight = 0;
		if ( cRect.Height() > m_pImgTopRight->GetHeight() + m_pImgBottomRight->GetHeight() )
		{
			dwRightHeight = cRect.Height() - m_pImgTopRight->GetHeight() - m_pImgBottomRight->GetHeight();
		}
		for ( nIndex = 0; nIndex < ( dwRightHeight / m_pImgCenterRight->GetHeight() ); nIndex++ )
        {
            pGraphics->DrawImage( m_pImgCenterRight, nPosRightX, nPosRightY, m_pImgCenterRight->GetWidth(), m_pImgCenterRight->GetHeight() );
            nPosRightY += m_pImgCenterRight->GetHeight();
        }
        pGraphics->DrawImage( m_pImgCenterRight, nPosRightX, nPosRightY, m_pImgCenterRight->GetWidth(), dwRightHeight % m_pImgCenterRight->GetHeight() );

		SolidBrush cBrush( Color(213,228,250) );	
		pGraphics->FillRectangle( &cBrush, m_pImgCenterLeft->GetWidth(), m_pImgTopLeft->GetHeight(), (int)dwTopCenterWidth, (int)dwLeftHeight );
    }
	if( pGraphics != NULL )
	{
		delete pGraphics;
		pGraphics = NULL;
	}
	return m_pImageBK;
}

void CTransparentHoriList::Clear()
{
    m_pSelItem = NULL;
    m_pLastItem = NULL;

    if ( m_pItemList != NULL )
    {
        m_pItemList->DeleteAllItem();
    }
}
