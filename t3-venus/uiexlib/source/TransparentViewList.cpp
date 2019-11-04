// TransparentViewList.cpp: implementation of the CTransparentViewList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TransparentViewList.h"
//#include "dragWindow.h"
#include "bitmapHelp.h"
#include "listfuncmanage.h"
#include "item.h"

#define  TIMER_HANDLE_MOVING  110 

const CString CTransparentViewList::strBkgImg = "Bkg.png";
const CString CTransparentViewList::strVertSliderImg = "VertSlider";
const CString CTransparentViewList::strHoriSliderImg = "HoriSlider";
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTransparentViewList::CTransparentViewList( CString strName, CRect rcWnd, CWnd* pWnd, UINT nID, DWORD dStyle, DWORD dwExStyle )
: IList( rcWnd.Width(), rcWnd.Height() ), CTransparentBaseWnd( rcWnd, pWnd, dStyle, "", nID, dwExStyle )
{
    m_nTotalYOffset = 0;
    m_nTotalXOffset = 0;
    m_nMoveSpeed = 0;
    m_bLBtnDown = FALSE;
    m_bDragEnable = FALSE;
    m_bClickNoSel = FALSE;
    m_bMultiSel = FALSE;
    m_pSelItem = NULL;
    m_pLastItem = NULL;
    m_dwSelDataKey = -1;
    m_pDragOverItem = NULL;
    
    m_cBkgColor = Color( 213, 228, 250 );
    /*
    m_pImgTopLeft = NULL;
    m_pImgTopCenter = NULL;
    m_pImgTopRight = NULL;	
    m_pImgCenterLeft = NULL;
    m_pImgCenterRight = NULL;
    m_pImgBottomLeft = NULL;
    m_pImgBottomCenter = NULL;
	m_pImgBottomRight = NULL;
    */

    SetItemSizeSame( false );

    m_pVertSlider = NULL;
    m_pVertSlider = new CTransparentListSlider( "", CRect(0,0,0,0), GetParent(), 0, WS_CHILD );

    m_pHoriSlider = NULL;
    m_pHoriSlider = new CTransparentListHoriSlider( "", CRect(0,0,0,0), GetParent(), 0, WS_CHILD );
    
    m_pMouseHoverItem = NULL;
	m_bNeedOver = FALSE;
	m_bMouseTrack = TRUE;
}

CTransparentViewList::~CTransparentViewList()
{
    if ( NULL != m_pImageBK )
    {
        delete m_pImageBK;
        m_pImageBK = NULL;
    }   
    
    Clear();

    if ( m_pVertSlider != NULL )
    {
        m_pVertSlider->DestroyWindow();
        delete m_pVertSlider;
        m_pVertSlider = NULL;
    }
    if ( m_pHoriSlider != NULL )
    {
        m_pHoriSlider->DestroyWindow();
        delete m_pHoriSlider;
        m_pHoriSlider = NULL;
    }
}


BEGIN_MESSAGE_MAP(CTransparentViewList, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CTransparentViewList)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_SIZE()
ON_WM_TIMER()
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
ON_MESSAGE( WM_LIST_UPDATEPROGRESS, OnUpdateProgress )
ON_MESSAGE( UI_DRAG_OVER, OnDragOver )
ON_MESSAGE( UI_DRAG_LEAVE, OnDragLeave )
ON_MESSAGE( UI_DRAG_END, OnDragEnd )
//}}AFX_MSG_MAP
ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave )
ON_MESSAGE( WM_MOUSEHOVER, OnMouseHover )
END_MESSAGE_MAP()



LRESULT CTransparentViewList::OnRedrawUI( WPARAM wParam, LPARAM lParam )
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
    
    DrawUI( pGraphics, pGraphWnd ); 

    if ( m_pVertSlider != NULL )
    {
        m_pVertSlider->SetListYOffset( -m_nTotalYOffset );
	}
    if ( m_pHoriSlider != NULL )
    {
        m_pHoriSlider->SetListXOffset( -m_nTotalXOffset );
    }
    
    return S_OK;
}


void CTransparentViewList::Draw( IArgs* pArgs )
{
    IList::Draw( pArgs, -m_nTotalYOffset, m_rctDlg.Height() );
}

void CTransparentViewList::DrawUI( Graphics* pGraphics, CWnd* pParent )
{   
    if ( pGraphics == NULL || pParent == NULL )
    {
        return ;
    }
    
    CRect rc = GetListRect();
    
    Bitmap* pSubBitmap = new Bitmap( rc.Width(), rc.Height() ); 
    Graphics* pGraph = Graphics::FromImage( pSubBitmap );
    
    pGraph->DrawImage( m_pImageBK, 0, 0, rc.Width(), rc.Height() );   
    
    Args_Graphics args_Graphics( pGraph, Rect( rc.left, rc.top, rc.Width(), rc.Height() ) );
    Draw( &args_Graphics );	
    
    CRect rcWnd;
    this->GetWindowRect( rcWnd );
    pParent->ScreenToClient( rcWnd );
    pGraphics->DrawImage( pSubBitmap, rcWnd.left, rcWnd.top );
    
    if ( pSubBitmap != NULL )
    {
        delete pSubBitmap;
        pSubBitmap = NULL;
    }
    if ( pGraph != NULL )
    {
        delete pGraph;
        pGraph = NULL;
    }
    
} 

CRect CTransparentViewList::GetListRect()
{
    this->GetClientRect( m_rctDlg );
    
    return m_rctDlg;
}

void CTransparentViewList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( NULL != m_pMouseHoverItem )
	{
		IBaseItem* pItemLastHover = m_pMouseHoverItem->GetItemData();
		if( NULL != pItemLastHover )
			pItemLastHover->SetItemStatus(emItemStatusNormal);
		
		m_pMouseHoverItem = NULL;
	}
	// TODO: Add your message handler code here and/or call default
	m_bLBtnDown = FALSE;

	HWND hFocusWnd = ::GetFocus();
	if ( hFocusWnd != m_hWnd )
	{   
		this->SetFocus();
	}

    if ( m_pItemList == NULL )
    {
        return;
	}

	if ( m_nMoveSpeed != 0 )
	{   		
		m_nMoveSpeed = 0;
		KillTimer(TIMER_HANDLE_MOVING);	
	} 

	//如有多个选中项，在点击时清空高亮
    if ( m_bMultiSel )
    {
	    ClearAllSel();
    }

	m_bLBtnDown = TRUE;
	m_ptMouseNow = point;
	m_ptMouseLast = point;
	m_ptMouseDown = point;

	IItemList* pSelList = NULL;
	IsClick( m_pItemList, point, &pSelList );

	if ( m_pSelItem != NULL)
	{
		SetSelItemStatus( emItemStatusNormal );
				
		m_pSelItem = NULL;
		m_pLastItem = NULL;	        
    }
    m_dwSelDataKey = -1;   
    
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

    NOTIF_PARENT_WND_IMMEDIATLY_DRAW
	
//	SetCapture();
//	CTransparentWnd::OnLButtonDown(nFlags, point);
}

void CTransparentViewList::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( NULL != m_pMouseHoverItem )
	{
		IBaseItem* pItemLastHover = m_pMouseHoverItem->GetItemData();
		if( NULL != pItemLastHover )
			pItemLastHover->SetItemStatus(emItemStatusNormal);
		
		m_pMouseHoverItem = NULL;
	}
	// TODO: Add your message handler code here and/or call default
	if ( !m_bLBtnDown )
	{   
		return;
	} 	
	
	m_bLBtnDown = FALSE;
			
	
	if ( m_pSelItem != NULL )
	{
		if ( point == m_ptMouseDown )
		{
            SetSelItemStatus( emItemStatusSel );

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

			//通知外部当前没有选中项
			PostMessage(WM_LST_UN_SELECT_ITEM);
			//发给父窗口用于Umcweb
			GetParent()->PostMessage( WM_LST_UN_SELECT_ITEM, (WPARAM)GetSafeHwnd(), 0 );
		}		
	}

	if ( abs(m_ptMouseLast.y - m_ptMouseNow.y) > 6 ) //产生惯性运动
    {
		m_nMoveSpeed = (m_ptMouseNow.y - m_ptMouseLast.y) / 5;
		SetTimer( TIMER_HANDLE_MOVING, 20, NULL );	   
    }

	if ( GetCapture() == this )
	{
		ReleaseCapture();
	}
	
	if ( m_pSelItem == m_pItemList  )
    {
		m_dwSelDataKey = -1;
        //通知外部当前没有选中项
		PostMessage(WM_LST_UN_SELECT_ITEM);
		//发给父窗口用于Umcweb
		GetParent()->PostMessage( WM_LST_UN_SELECT_ITEM, (WPARAM)GetSafeHwnd(), 0 );
    }

    NOTIF_PARENT_WND

//	CTransparentWnd::OnLButtonUp(nFlags, point);
}

void CTransparentViewList::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( !IsWindowEnabled() || !IsWindowVisible() )
	{
		return;
	}

	if ( m_bNeedOver && !m_bLBtnDown )
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
		else
		{
			ListMouseMove(nFlags,point);
		}
	}
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
    
    /*
    //拖动后清空选中项
    if ( m_pSelItem != NULL )
    {
        SetSelItemStatus( emItemStatusNormal );
        m_pSelItem = NULL;
        m_dwSelDataKey = -1;     
        
        //通知外部当前没有选中项
        PostMessage(WM_LST_UN_SELECT_ITEM);
        GetParent()->PostMessage( WM_LST_UN_SELECT_ITEM, (WPARAM)GetSafeHwnd(), 0 );
    }*/
    
    ListMove();
    
    //移出对话框，拖拽开始	
    /*
    if ( m_bDragEnable && m_pLastItem != NULL && IsReadyForDrag() )
    {    				
        IItemList* pDragItem = m_pLastItem; //m_pSelItem;
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
    }*/ 	
       
    NOTIF_PARENT_WND
    //CTransparentWnd::OnMouseMove(nFlags, point);
}

void CTransparentViewList::ListMouseMove(UINT nFlags, CPoint point)
{		
	//判断point在哪个Item上,若为选中状态则不进行over绘制
	IItemList* item = NULL;
	bool bClick = IsClick( m_pItemList, point, &item , FALSE );
	if ( NULL != item && m_pMouseHoverItem != item)
	{			
		if( NULL != m_pMouseHoverItem )
		{
			IBaseItem* pItemLastHover = m_pMouseHoverItem->GetItemData();
			if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pItemLastHover) )
			{
				IItemList* pParentItem = m_pMouseHoverItem->GetParentItem();
				if ( pParentItem != NULL )
				{
					pItemLastHover = pParentItem->GetItemData();
				}
			}
			if( NULL != pItemLastHover )
				pItemLastHover->SetItemStatus(emItemStatusNormal);
			m_pMouseHoverItem = NULL;
		}
		
		IBaseItem* pItem = item->GetItemData();
		
		if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pItem) )
		{
			pItem = item->GetParentItem()->GetItemData();
		}
		
		if ( pItem->GetItemStatus() != emItemStatusSel )
		{		
			m_pMouseHoverItem = item;
			pItem->SetItemStatus( emItemStatusOver );
		} 
		NOTIF_PARENT_WND
	}
}

void CTransparentViewList::ListMove()
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
    
    m_nTotalXOffset += ( m_ptMouseNow.x - m_ptMouseLast.x );
    m_nTotalYOffset += ( m_ptMouseNow.y - m_ptMouseLast.y );  
    
    CheckXOffset();        
    CheckYOffset();
    
    IBaseItem* pItem = pSelList->GetItemData();
    if ( pItem != NULL )
    {
        pItem->SetOffset( CPoint(m_nTotalXOffset, m_nTotalYOffset) );
    }
}

void CTransparentViewList::ListAutoMove()
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
    
    m_nTotalYOffset += m_nMoveSpeed;
    m_nMoveSpeed *= 0.96;
    
    if ( m_nTotalYOffset > 0 )
    {    
        m_nMoveSpeed = 0; 
        m_nTotalYOffset = 0;  	 
    }
    
    if ( m_nTotalYOffset < m_rctDlg.Height() - m_rctList.Height() )
    {
        m_nTotalYOffset = m_rctDlg.Height() - m_rctList.Height();	
        if ( m_nTotalYOffset > 0 )
        {	 
            m_nMoveSpeed = 0;
            m_nTotalYOffset = 0; 
        } 
    }  
    
    IBaseItem* pItem = pSelList->GetItemData();
    if ( pItem != NULL )
    {
        pItem->SetOffset( CPoint(m_nTotalXOffset, m_nTotalYOffset) );
    }
    
    if ( 0 == m_nMoveSpeed )
    { 
        KillTimer(TIMER_HANDLE_MOVING);  
    } 
    
    NOTIF_PARENT_WND
}

/*=============================================================================
函 数 名:CheckXOffset/CheckYOffset
功    能:检查列表偏移是否越界
参    数:无 
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/11/29  1.0     肖楚然     创建
=============================================================================*/
void CTransparentViewList::CheckXOffset()
{
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
}

void CTransparentViewList::CheckYOffset()
{
    if ( m_nTotalYOffset > 0 )
    {
        m_nTotalYOffset = 0;  	
    }	
    if ( m_nTotalYOffset < m_rctDlg.Height() - m_rctList.Height() )
    {
        m_nTotalYOffset = m_rctDlg.Height() - m_rctList.Height();	
        if ( m_nTotalYOffset > 0 )
        {	
            m_nTotalYOffset = 0;
        }	
    }
}


void CTransparentViewList::SetSelItemStatus( EmItemStatus emStatus )
{	
    if ( m_pSelItem != NULL )
    {
        IItemList* pList = m_pSelItem;
        while( pList != NULL && pList->GetParentItem() != NULL )
        {
            IBaseItem* pItem = pList->GetItemData();
            if ( pItem != NULL && pItem->GetItemStatus() != emItemStatusDisable )
            {
                pItem->SetItemStatus( emStatus );
            }
            pList = pList->GetParentItem();
        }
    }
}


CRect CTransparentViewList::GetFrameInScreen( IItemList* pList )
{
    ASSERT( pList );
    IItemList* pTemp = pList;
    IBaseItem* pData = pTemp->GetItemData();
    ASSERT( pData );
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

/*=============================================================================
函 数 名:SetListOffset
功    能:设置列表偏移量
参    数:point 偏移位置  
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/11/29  1.0     肖楚然     创建
=============================================================================*/
void CTransparentViewList::SetListOffset( CPoint point )
{
    if ( m_nMoveSpeed != 0 )
    {   		
        m_nMoveSpeed = 0;
        KillTimer(TIMER_HANDLE_MOVING);	
    }

    m_nTotalXOffset = point.x;
    m_nTotalYOffset = point.y;
    
    CheckXOffset();  
    CheckYOffset();
    
    IBaseItem* pItem = m_pItemList->GetItemData();
    if ( pItem != NULL )
    {
        pItem->SetOffset( CPoint(m_nTotalXOffset, m_nTotalYOffset) );
    }
    
    NOTIF_PARENT_WND
}

/*=============================================================================
函 数 名:SetXOffset
功    能:设置列表X轴偏移量
参    数:nOffset 偏移位置  
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/11/21  1.0     肖楚然     创建
=============================================================================*/
void CTransparentViewList::SetXOffset( int nOffset )
{
    if ( m_nMoveSpeed != 0 )
    {   		
        m_nMoveSpeed = 0;
        KillTimer(TIMER_HANDLE_MOVING);	
    }

    m_nTotalXOffset = nOffset;
       
    CheckXOffset();  
    
    IBaseItem* pItem = m_pItemList->GetItemData();
    if ( pItem != NULL )
    {
        pItem->SetOffset( CPoint(m_nTotalXOffset, m_nTotalYOffset) );
    }
    
    NOTIF_PARENT_WND
}

/*=============================================================================
函 数 名:SetYOffset
功    能:设置列表Y轴偏移量
参    数:nOffset 偏移位置  
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/11/21  1.0     肖楚然     创建
=============================================================================*/
void CTransparentViewList::SetYOffset( int nOffset )
{
    if ( m_nMoveSpeed != 0 )
    {   		
        m_nMoveSpeed = 0;
        KillTimer(TIMER_HANDLE_MOVING);	
    }
    
    m_nTotalYOffset = nOffset;
    
    CheckYOffset();
    
    IBaseItem* pItem = m_pItemList->GetItemData();
    if ( pItem != NULL )
    {
        pItem->SetOffset( CPoint(m_nTotalXOffset, m_nTotalYOffset) );
    }
    
    NOTIF_PARENT_WND
}

/*=============================================================================
函 数 名:ResetSelItem
功    能:重置选中项
参    数:bResetOffset 重置位置  
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/11/21  1.0     肖楚然     创建
=============================================================================*/
void CTransparentViewList::ResetSelItem( BOOL bResetOffset )
{
    if ( m_nMoveSpeed != 0 )
    {   		
        m_nMoveSpeed = 0;
        KillTimer(TIMER_HANDLE_MOVING);	
    } 
    
    int nItemCount = m_pItemList->GetItemCount();
    if ( nItemCount <= 0)
    {
        m_nTotalYOffset = 0;
    }
    
    m_rctList = GetFrame( m_pItemList );

    //设置滑动条数据
    GetListRect();
    if ( m_pVertSlider != NULL )
    {
        if ( m_rctList.Height() <= m_rctDlg.Height() )
        {
            m_pVertSlider->ShowWindow( SW_HIDE );
        }
        else
        {
            m_pVertSlider->SetListTotalHeight( m_rctList.Height() );
            m_pVertSlider->ShowWindow( SW_SHOW );
        }       
    }
    if ( m_pHoriSlider != NULL )
    {
        if ( m_rctList.Width() <= m_rctDlg.Width() )
        {
            m_pHoriSlider->ShowWindow( SW_HIDE );
        }
        else
        {
            m_pHoriSlider->SetListTotalWidth( m_rctList.Width() );
            m_pHoriSlider->ShowWindow( SW_SHOW );
        }    
    }
    
    //将位置重设一次，防止刷新后界面显示条目不够的情况
    if ( !bResetOffset )
    {
        SetListOffset( CPoint( m_nTotalXOffset, m_nTotalYOffset ) );
    }
    
    if ( m_dwSelDataKey == -1 )
    {
        return;
    }		
    
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
                    m_pSelItem = pSubList;
                    pSubItem->SetItemStatus( emItemStatusSel );
                    if ( bResetOffset )
                    {
                        //int nYOffset = GetOffsetHeight( nIndex );
                        //SetYOffset( nYOffset );
                    }					
                    return;
                }
            }		
        }
    }
    
}

void CTransparentViewList::SetSelItem( unsigned long dwDataKey )
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

IBaseItem* CTransparentViewList::GetSelItem()
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


void CTransparentViewList::OnSize(UINT nType, int cx, int cy) 
{
    CTransparentBaseWnd::OnSize(nType, cx, cy);
    // TODO: Add your message handler code here	

    CRect rc;
    //this->GetClientRect( rc );
    this->GetWindowRect(rc);
    //
    SetListSize( rc.Width(), rc.Height() );   

    CRect rectDlg = rc;
    GetParent()->ScreenToClient( rectDlg );
    if ( m_pVertSlider != NULL )
    {
        m_pVertSlider->SetListWnd( this );        

        CRect rectSlider = rectDlg;
        rectSlider.left = rectDlg.right + 15;
        rectSlider.right = rectSlider.left + 7;
	    m_pVertSlider->MoveWindow( &rectSlider );
        m_pVertSlider->ShowWindow( SW_HIDE );      
    }

    if ( m_pHoriSlider != NULL )
    {
        m_pHoriSlider->SetListWnd( this );
       
        CRect rectSlider = rectDlg;
        rectSlider.top = rectDlg.bottom + 13;
        rectSlider.bottom = rectSlider.top + 7;
        m_pHoriSlider->MoveWindow( &rectSlider );
        m_pHoriSlider->ShowWindow( SW_HIDE ); 
    }
}

void CTransparentViewList::OnTimer(UINT nIDEvent) 
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

void CTransparentViewList::Clicked( UINT nFlags, CPoint point )
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


LRESULT CTransparentViewList::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    if ( message == WM_TOUCH_BUTTONDOWN )
    {
        int nX = LOWORD( lParam );
        int nY = HIWORD( lParam );
        //屏幕坐标点
        if ( !m_bLBtnDown )
        {
            CPoint point( nX, nY );
            this->ScreenToClient( &point );
            OnLButtonDown( MK_LBUTTON, point );  
        }     
    }
    
    return CTransparentBaseWnd::DefWindowProc(message, wParam, lParam);
}

/*=============================================================================
函 数 名:OnUpdateProgress
功    能:相应列表滚动条拖动事件
参    数:wParam 偏移量  
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/11/28  1.0     肖楚然     创建
=============================================================================*/
LRESULT	CTransparentViewList::OnUpdateProgress( WPARAM wParam, LPARAM lParam )
{
    CPoint pointOffset = *(CPoint*)wParam;

    //滑动条滑动方向与列表移动方向相反，因此-=
    if ( pointOffset.x != 0 )
    {
        m_nTotalXOffset -= pointOffset.x;
        SetXOffset( m_nTotalXOffset );
    }

    if ( pointOffset.y != 0 )
    {
        m_nTotalYOffset -= pointOffset.y;
        SetYOffset( m_nTotalYOffset );
    }
    
    return NO_ERROR;
}


void CTransparentViewList::SetVertSliderOffsetPos( CPoint ptOffset )
{
    CRect rectDlg;
    this->GetWindowRect(rectDlg);
    GetParent()->ScreenToClient( rectDlg );

    if ( m_pVertSlider != NULL )
    {      
        CRect rect;
        m_pVertSlider->GetClientRect( &rect ); 

        CRect rectSlider = rectDlg;
        rectSlider.left = rectDlg.right + ptOffset.x;
        rectSlider.right = rectSlider.left + rect.Width();
        rectSlider.top = rectDlg.top + ptOffset.y;
		rectSlider.bottom = rectSlider.top + rect.Height();
        m_pVertSlider->MoveWindow( &rectSlider );
    }
}

void CTransparentViewList::SetHoriSliderOffsetPos( CPoint ptOffset )
{
    CRect rectDlg;
    this->GetWindowRect(rectDlg);
    GetParent()->ScreenToClient( rectDlg );
    
    if ( m_pHoriSlider != NULL )
    {      
        CRect rect;
        m_pHoriSlider->GetClientRect( &rect ); 
        
        CRect rectSlider = rectDlg;
        rectSlider.top = rectDlg.bottom + ptOffset.y;
        rectSlider.bottom = rectSlider.top + rect.Height();
        rectSlider.left = rectDlg.left + ptOffset.x;
		rectSlider.right = rectSlider.left + rect.Width();
        m_pHoriSlider->MoveWindow( &rectSlider );
    }
}


void CTransparentViewList::SetImage( CString strImageFolder )
{
    if ( "" == strImageFolder )
    {
        return;
    }

    CString strFile = strImageFolder + "\\" + CTransparentViewList::strBkgImg;
    m_pImageBK = CSrcManage::GetImage( strFile );

    strFile = strImageFolder + "\\" + CTransparentViewList::strVertSliderImg;
    if( m_pVertSlider != NULL )
    {
        m_pVertSlider->SetImage( strFile );
	}

    strFile = strImageFolder + "\\" + CTransparentViewList::strHoriSliderImg;
    if( m_pHoriSlider != NULL )
    {
        m_pHoriSlider->SetImage( strFile );
	}

}


void CTransparentViewList::SetVertSliderImage( UINT nImgNormalUp, UINT nImgNormalCenter, UINT nImgNormalDown, UINT nImgHilightUp, 
         UINT nImgHilightCenter, UINT nImgHilightDown, UINT nImgBkUp, UINT nImgBkCenter, UINT nImgBkDown, const CString& strImgType )
{
    if ( m_pVertSlider != NULL )
    {
        m_pVertSlider->SetImage( nImgNormalUp, nImgNormalCenter, nImgNormalDown, nImgHilightUp, 
            nImgHilightCenter, nImgHilightDown, nImgBkUp, nImgBkCenter, nImgBkDown, strImgType );
    }
}

void CTransparentViewList::SetHoriSliderImage( UINT nImgNormalLeft, UINT nImgNormalCenter, UINT nImgNormalRight, UINT nImgHilightLeft, 
         UINT nImgHilightCenter, UINT nImgHilightRight,  UINT nImgBkLeft, UINT nImgBkCenter, UINT nImgBkRight, const CString& strImgType )
{
    if ( m_pHoriSlider != NULL )
    {
        m_pHoriSlider->SetImage( nImgNormalLeft, nImgNormalCenter, nImgNormalRight, nImgHilightLeft, 
            nImgHilightCenter, nImgHilightRight, nImgBkLeft, nImgBkCenter, nImgBkRight, strImgType );
    }
}


void CTransparentViewList::SetBkgColor( Color colorBkg, BOOL bInvalidate /* = FALSE */ )
{
    m_cBkgColor = colorBkg;
    
    if ( bInvalidate )
    {
        NOTIF_PARENT_WND
    }
}


void  CTransparentViewList::Clear()
{   
    m_pSelItem = NULL;
    m_pLastItem = NULL;
    m_pMouseHoverItem = NULL;
    m_pDragOverItem = NULL;
    
    if ( m_pItemList != NULL )
    {
        m_pItemList->DeleteAllItem();
    }
}


LRESULT	CTransparentViewList::OnDragOver( WPARAM wParam, LPARAM lParam )
{
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
	CPoint point(x, y);

    ScreenToClient( &point );

    IItemList* pSelList = NULL;
	IsClick( m_pItemList, point, &pSelList );

    if ( pSelList != NULL )
    {    
        while( pSelList != NULL && pSelList->GetParentItem() != NULL )
        {
            IBaseItem* pBaseItem = pSelList->GetItemData();           
            if ( pBaseItem == NULL )
            {             
                return NO_ERROR;
            }
     
            if ( pBaseItem->GetUserData() != NULL && pBaseItem->GetFunc() != IBaseItem::strDefaultFunc )
            {
                if ( m_pDragOverItem != pSelList )
                {
                    if ( m_pDragOverItem != NULL )
                    {
                        GetParent()->PostMessage( UI_DRAG_LEAVE, wParam, (LPARAM)m_pDragOverItem );
                    }
                    m_pDragOverItem = pSelList;                
                    GetParent()->PostMessage( UI_DRAG_OVER, wParam, (LPARAM)m_pDragOverItem );
                }
              
                return NO_ERROR;
            }

            pSelList = pSelList->GetParentItem();
        }
	}

    if ( m_pDragOverItem != NULL )
    {
        GetParent()->PostMessage( UI_DRAG_LEAVE, wParam, (LPARAM)m_pDragOverItem );
        m_pDragOverItem = NULL;
    }

    return NO_ERROR;
}

LRESULT	CTransparentViewList::OnDragLeave( WPARAM wParam, LPARAM lParam )
{
    if ( m_pDragOverItem != NULL )
    {
        GetParent()->PostMessage( UI_DRAG_LEAVE, wParam, (LPARAM)m_pDragOverItem );
        m_pDragOverItem = NULL;
    }
    return NO_ERROR;
}

LRESULT	CTransparentViewList::OnDragEnd( WPARAM wParam, LPARAM lParam )
{
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    CPoint point(x, y);
    
    ScreenToClient( &point );
    
    IItemList* pSelList = NULL;
    IsClick( m_pItemList, point, &pSelList );
    
    if ( pSelList != NULL )
    {    
        while( pSelList != NULL && pSelList->GetParentItem() != NULL )
        {
            IBaseItem* pBaseItem = pSelList->GetItemData();           
            if ( pBaseItem == NULL )
            {             
                return NO_ERROR;
            }
            
            if ( pBaseItem->GetUserData() != NULL && pBaseItem->GetFunc() != IBaseItem::strDefaultFunc )
            {                          
                GetParent()->PostMessage( UI_DRAG_END, wParam, (LPARAM)m_pDragOverItem );
              
                return NO_ERROR;
            }
            
            pSelList = pSelList->GetParentItem();
        }
	}
    return NO_ERROR;
}


void CTransparentViewList::SetMultiSelSet( set<unsigned long> setMultiSel )
{
    //ClearAllSel();

    int nItemCount = m_pItemList->GetItemCount();

    m_bMultiSel = TRUE;
    for ( int nIndex = 0; nIndex < nItemCount; nIndex++ )
    {
        IItemList* pSubList = m_pItemList->GetItemByIndex( nIndex );
        if ( pSubList == NULL )
        {
            return;
        }

        for ( int i = 0; i < pSubList->GetItemCount(); i++ )
        {
            IItemList* pList = pSubList->GetItemByIndex( i );
            if ( pList == NULL )
			{
                return;
            }

            IBaseItem* pSubItem = pList->GetItemData();
            if ( pSubItem != NULL && pSubItem->GetUserData() != NULL )
            {		
                IData* pData = const_cast<IData*>( pSubItem->GetUserData() );

                if ( !setMultiSel.empty() )
                {
                    std::set<unsigned long>::iterator iter = setMultiSel.find( pData->GetDataKey() );
                    if ( iter != setMultiSel.end() )
                    {
                        pSubItem->SetItemStatus( emItemStatusSel );
                     
                        setMultiSel.erase( iter );
                        if ( setMultiSel.empty() )
                        {
                            NOTIF_PARENT_WND
                            return;
                        }
                    }
                }
            }		
        }
    }
}


void CTransparentViewList::ClearAllSel()
{
    int nCount = m_pItemList->GetItemCount();
  
    for ( int nIndex = 0; nIndex < nCount; nIndex++ )
    {
        IItemList* pSubList = m_pItemList->GetItemByIndex( nIndex );
        if ( pSubList == NULL )
        {
            return;
        }
        
        for ( int i = 0; i < pSubList->GetItemCount(); i++ )
        {
            IItemList* pList = pSubList->GetItemByIndex( i );
            if ( pList == NULL )
            {
                return;
            }
            IBaseItem* pItem = pList->GetItemData();
            if ( pItem != NULL )
            {
                if ( pItem->GetItemStatus() == emItemStatusSel )
                {
                    pItem->SetItemStatus( emItemStatusNormal );
                }
            }
        }
    }
    m_bMultiSel = FALSE;
	m_dwSelDataKey = -1;
    NOTIF_PARENT_WND
}

LRESULT CTransparentViewList::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{	
	if( NULL != m_pMouseHoverItem )
	{
		IBaseItem* pItemLastHover = m_pMouseHoverItem->GetItemData();
		if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pItemLastHover) )
		{
			IItemList* pParentItem = m_pMouseHoverItem->GetParentItem();
			if ( pParentItem != NULL )
			{
				pItemLastHover = pParentItem->GetItemData();
			}			
		}
		if( NULL != pItemLastHover )
			pItemLastHover->SetItemStatus(emItemStatusNormal);
		
		m_pMouseHoverItem = NULL;		
	}
	NOTIF_PARENT_WND
	m_bMouseTrack = TRUE;
	return S_OK;
}

LRESULT CTransparentViewList::OnMouseHover( WPARAM wParam, LPARAM lParam )
{	
	m_bMouseTrack = FALSE;
	return S_OK;
}