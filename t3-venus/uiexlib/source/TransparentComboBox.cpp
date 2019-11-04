// transparentcombobox.cpp : implementation file
//

#include "stdafx.h"
#include "uiexhead.h"
#include <WinSock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// BEGIN_MESSAGE_MAP(CComboBoxList, CTransparentList)
// //{{AFX_MSG_MAP(CComboBoxList)
// ON_WM_MOUSEMOVE()
// //}}AFX_MSG_MAP
// END_MESSAGE_MAP()

BOOL CComboBoxList::m_bIsRegAlgo = FALSE;

/////////////////////////////////////////////////////////////////////////////
// CComboBoxList
CComboBoxList::CComboBoxList( CString strName , CRect rcWnd , CWnd* pWnd, CString strUI, UINT nID, 
							 DWORD dStyle , DWORD dwExStyle ) :
CTransparentList(strName, rcWnd, pWnd, strUI, nID,dStyle, dwExStyle )
{
	//注册排列算法
	if ( !m_bIsRegAlgo )
	{
		REG_ALGORITHM( IAlgorithm::strComboxItem, CLayoutAlgorithm_ComboxItem )
		m_bIsRegAlgo = TRUE;
	}

	m_hComboWnd = NULL;
	m_cBkgColor = Color( 221, 221, 221 );
}

CComboBoxList::~CComboBoxList()
{
}

void CComboBoxList::ListKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	s32 nItemHeight = 0;
	s32 nItemWidth = 0;
	s32 nItemXNum =0;
	s32 nItemYNum = 0;
	s32 nItemShowIndex = 0;

	s32 nItemCount = m_pItemList->GetItemCount();

	if ( m_dwSelDataKey  == -1  )												//	未选中条目时，按键按下获得选中第一个条目
	{
		IItemList* pFirstItem = m_pItemList->GetItemByIndex(0);

		if ( pFirstItem == NULL )
		{
			return ;
		}

		IBaseItem* pSelItem = pFirstItem->GetItemData();
		IData* pData = const_cast<IData*>( pSelItem->GetUserData() );
		this->SetSelItem(pData->GetDataKey(), FALSE );
		return ;
	}

	if ( nItemCount != 0 && m_pItemList != NULL )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( 0 );
		if ( pSubList != 0 )
		{
			IBaseItem* pFirstItem = pSubList->GetItemData();
			nItemHeight = pFirstItem->GetItemHeight();// + CLayoutAlgorithm_Vert::nYSpace;
			nItemWidth = pFirstItem->GetItemWidth();
		}																					//列表条目的长和高
	}

	IBaseItem* pBaseItem = m_pItemList->GetItemData();
	s32 nViewItemHeight = pBaseItem->GetItemHeight() + CLayoutAlgorithm_Vert::nYSpace;		//计算显示区域的宽 高
	s32 nViewItemWidth = pBaseItem->GetItemWidth();	

	if ( nViewItemWidth < nItemWidth )
	{
		nItemXNum = 1;
	}
	else
	{
		nItemXNum = nViewItemWidth/nItemWidth;											//计算横向条目数
	}

	nItemYNum = (-m_nTotalYOffset)/nItemHeight;											//计算纵向隐藏的条目
//	nItemShowIndex = nItemYNum* nItemXNum;												//计算显示的条目索引

	nItemShowIndex = (-m_nTotalYOffset)/nItemHeight;

	if ( nItemShowIndex > ( nItemCount -1 ) )
	{
		nItemShowIndex = nItemCount -1;
	}

	switch( nChar )
	{
		case VK_UP:
			UpArrowPress( nItemHeight, nItemShowIndex );
			break;
		case VK_DOWN:
			DownArrowPress( nItemHeight,nItemShowIndex );
			break;
		default:
			break;
	}
}

void CComboBoxList::DownArrowPress( s32 nItemHeight , s32 nItemShowIndex )
{
	s32 nItemCount = m_pItemList->GetItemCount();

	if ( m_dwSelDataKey == ( nItemCount -1 ) ||( m_dwSelDataKey == -1 ) || ( nItemHeight <= 0 ) )
	{
		return ;
	}

	s32 nBorderIndex = (-m_nTotalYOffset)/nItemHeight + m_rctDlg.Height()/nItemHeight - 1;			//计算显示区域最大边际索引

	IItemList* pNextList = m_pItemList->GetItemByIndex( m_dwSelDataKey + 1 );
	
	if ( pNextList != NULL )
	{
		UpdateListItem(nBorderIndex,-nItemHeight,pNextList);
	}
}

void CComboBoxList::UpArrowPress( s32 nItemHeight , s32 nItemShowIndex )
{
	s32 nItemCount = m_pItemList->GetItemCount();

	if (( m_dwSelDataKey > nItemCount ) ||(  m_dwSelDataKey == 0 ) || ( nItemHeight <= 0 ))
	{
		return ;
	}

	IItemList* pNextList = m_pItemList->GetItemByIndex( m_dwSelDataKey - 1 );
	if ( pNextList != NULL )
	{
		UpdateListItem(nItemShowIndex,nItemHeight,pNextList);
	}
}

void CComboBoxList::UpdateListItem( s32 nBorderIndex , s32 nOffset ,IItemList *pLastSelList )
{
	if ( nBorderIndex < 0 )
	{
		return ;
	}

	if ( pLastSelList != NULL )
	{
		IBaseItem* pLastSelItem = pLastSelList->GetItemData();
		if ( pLastSelItem != NULL && pLastSelItem->GetUserData() != NULL )
		{		
			IData* pData = const_cast<IData*>( pLastSelItem->GetUserData() );
			Data_ComboMenu* pLastData = (Data_ComboMenu*)pData;
			if ( NULL != pLastData )
			{
				m_strLastMoveItem = pLastData->m_strMenuInfo;
			}
			if ( nBorderIndex == m_dwSelDataKey )
			{
				GoToListItem(nOffset,pData);
			}
			else
			{
				GoToListItem(0,pData);
			}
		}
	}
}

void CComboBoxList::GoToListItem( s32 nOffset , IData * pSelData )
{
	if ( pSelData == NULL )
	{
		return ;
	}

	IBaseItem* pItem = m_pItemList->GetItemData();
	m_nTotalYOffset += nOffset;
	CheckYOffset();
	if ( pItem != NULL )
	{
		pItem->SetOffset( CPoint(0, m_nTotalYOffset) );
	}
	this->SetSelItem(pSelData->GetDataKey(), FALSE );
//	SendMessage( WM_REDRAW_UI, 0, 0 );
}

void CComboBoxList::onReturnKey()
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
		IBaseItem* pBaseItem = pList->GetItemData();
		
		if ( const Data_ComboMenu* pItemInfo = dynamic_cast<const Data_ComboMenu*>( pBaseItem->GetUserData() )) 
		{ 
			if( NULL != GetComboWnd() )
			{
				GetComboWnd()->PostMessage( WM_UPDATE_COMBOEDIT_TEXT, (WPARAM)(LPCTSTR)pItemInfo->m_strMenuInfo, 0 );
			}
		}
		
		if ( strFunc == "IconFun" )
		{
			IBaseItem* pParentItem = pList->GetParentItem()->GetItemData();
			const Data_ComboMenu* pParentItemInfo = dynamic_cast<const Data_ComboMenu*>( pParentItem->GetUserData() );
			GetComboWnd()->PostMessage( WM_CLICK_COMBOLISTICON, (WPARAM)(LPCTSTR)pParentItemInfo->m_strMenuInfo, 0 );
		}
	}	
}

void CComboBoxList::ListMouseMove(UINT nFlags, CPoint point)
{
	CTransparentList::ListMouseMove( nFlags, point);

	point.y -= m_nTotalYOffset;

	s32 nItemCount = m_pItemList->GetItemCount();
	for ( s32 nIndex = 0; nIndex < nItemCount; nIndex++ )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( nIndex );
		if ( pSubList != NULL )
		{
			IBaseItem* pSubItem = pSubList->GetItemData();
			if ( pSubItem != NULL && pSubItem->GetUserData() != NULL )
			{		
				CRect rc = pSubItem->GetItemRect();
				if ( rc.PtInRect(point) )
				{
 					IData* pData = const_cast<IData*>( pSubItem->GetUserData() );
					if ( NULL != pData )
					{
						CString strLastMoveItem;
						Data_ComboMenu* pMenuData = (Data_ComboMenu*)pData;
						if ( NULL != pMenuData )
						{
							strLastMoveItem = pMenuData->m_strMenuInfo;
						}

						if ( m_strLastMoveItem == strLastMoveItem )
						{
							return;
						}
						
						m_strLastMoveItem = strLastMoveItem;

						this->SetSelItem(pData->GetDataKey(), FALSE );
						GetComboWnd()->PostMessage( WM_MOUSEMOVE_COMBOLISTSHOWICON, (WPARAM)nIndex, 0 );
					}
				}
			}		
		}
	}
}

void CComboBoxList::Clicked( UINT nFlags, CPoint point )
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
		IBaseItem* pBaseItem = pList->GetItemData();
		
		if ( const Data_ComboMenu* pItemInfo = dynamic_cast<const Data_ComboMenu*>( pBaseItem->GetUserData() )) 
		{ 
			if( NULL != GetComboWnd() )
			{
				GetComboWnd()->PostMessage( WM_UPDATE_COMBOEDIT_TEXT, (WPARAM)(LPCTSTR)pItemInfo->m_strMenuInfo, 0 );
			}
		}
		
		if ( strFunc == "IconFun" )
		{
			IBaseItem* pParentItem = pList->GetParentItem()->GetItemData();
			const Data_ComboMenu* pParentItemInfo = dynamic_cast<const Data_ComboMenu*>( pParentItem->GetUserData() );
			GetComboWnd()->PostMessage( WM_CLICK_COMBOLISTICON, (WPARAM)(LPCTSTR)pParentItemInfo->m_strMenuInfo, 0 );
		}
	}	
}

/////////////////////////////////////////////////////////////////////////////
// CComboxDropBaseWnd
CComboxDropBaseWnd::CComboxDropBaseWnd( CRect rcWnd, CWnd* pWnd,DWORD dStyle,
		CString strUI,UINT nID, DWORD dwExStyle,int nTrans,BOOL bCanMove, BOOL bStretchImage ) 
: CTransparentBaseWnd( rcWnd, pWnd, dStyle, strUI,nID )
{
}

CComboxDropBaseWnd::~CComboxDropBaseWnd()
{
}

BEGIN_MESSAGE_MAP(CComboxDropBaseWnd, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CComboxDropBaseWnd)
	ON_WM_ACTIVATE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CComboxDropBaseWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	if( nState == WA_ACTIVE )
	{
		this->ShowWindow(SW_SHOW);
	}
	else
	{
		this->ShowWindow(SW_HIDE);
	}
    
    CWnd::OnActivate(nState, pWndOther, bMinimized); 
}  

/////////////////////////////////////////////////////////////////////////////
// CTransparentComboBox
CTransparentComboBox::CTransparentComboBox( CString strName, CWnd* pWnd, CRect rcWnd,  UINT nID, DWORD dStyle ) 
: CTransparentBaseWnd( rcWnd, pWnd, dStyle , "",  nID )
{
	m_rcWnd = rcWnd/*CRect(0,0,10,10)*/;

	if ( rcWnd.Width() <= 0 || rcWnd.Height() <= 0 )
	{
		m_rcWnd = CRect(0,0,10,10);
	}

	m_nFontSize = 9;

	m_itemNormalColor = Color(78,78,78);
	m_itemSelColor = Color(240,240,240);

	m_colorNormal = Color( 59, 59, 59 );
	m_colorFocus = Color( 59, 59, 59 );
    m_colorDisable = Color( 153, 153, 153 );

	m_bIsIPStyle = FALSE;
	m_nListHeight = 212;
	m_nListItemHeight = 25;
	m_nListImgHeight = 15;
	m_strComboText = "";

	m_bIsShowListIcon = TRUE;

	m_nEditEdge = 9/*CSize(2,4)*/;

    m_pImgBkg = NULL;
	m_bAutoHide = TRUE;

	m_pTransEdit = NULL;
	m_pDropWnd = NULL;
	m_pDropList = NULL;
	m_bSetBkColor = FALSE;
	m_nSliderWidth = 1;
	m_nEditBackLen = 8;
}

void CTransparentComboBox::InitComboControl()
{
	if ( !m_bIsIPStyle )
	{
		m_pTransEdit = new CTransparentEdit();
	}
	else
	{
		m_pTransEdit = new CTransparentIpEdit();
	}
	
	if ( NULL != m_pTransEdit )
	{
		m_pTransEdit->Create( WS_CHILD|WS_CLIPSIBLINGS, CRect( 0, 0, m_rcWnd.Width(), m_rcWnd.Height() ), this, 0 ); 
		m_pTransEdit->SetWindowPos( NULL, 0, 0, m_rcWnd.Width(), m_rcWnd.Height(), SWP_NOACTIVATE|SWP_SHOWWINDOW );
		m_pTransEdit->SetIconDeleteText(FALSE);
		SetFont( m_nFontSize, "宋体" );

		m_pTransEdit->SetTextColor( m_colorNormal, m_colorFocus );
		m_pTransEdit->SetDisableColor( m_colorDisable );

		m_pTransEdit->SetParent(this);
	}
	
	CRect rectEdit;
	if ( NULL != m_pTransEdit )
	{
		m_pTransEdit->GetWindowRect(&rectEdit);
	}
	
	m_pDropWnd = new CComboxDropBaseWnd( CRect(0,0,m_rcWnd.Width(), m_nListHeight), NULL, WS_POPUP, "DropWnd", 0, WS_EX_TOOLWINDOW );
	::SetWindowLong( m_pDropWnd->GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong( m_pDropWnd->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_TOOLWINDOW | WS_EX_LAYERED );
	if ( NULL != m_pDropWnd )
	{    
		m_pDropWnd->m_bTransparentWithoutBK = TRUE;
		m_pDropWnd->SetImage("");	//必须设置
		//m_pDropWnd->SetParent(this);
	}
	
	m_pDropList = new CComboBoxList( "TransparentComboBoxList", 0, m_pDropWnd, "", 0, WS_CHILD );    //显示一个列表
	if ( NULL != m_pDropList )
	{
		m_pDropList->SetSliderAlwaysShow(TRUE);
		m_pDropList->SetWindowPos( NULL, 0, 0, m_rcWnd.Width() - 2*m_nEditEdge, m_nListHeight, SWP_SHOWWINDOW|SWP_NOACTIVATE );
		m_pDropList->SetParent(m_pDropWnd);
		m_pDropList->SetItemSizeSame( FALSE );
		m_pDropList->SetComboWnd(this);
		m_pDropList->SetRedrawBk(TRUE);
	}
	
	this->SetItemSelColor(Color( 255, 255, 255 ));
	this->SetEditBackLen(m_nEditBackLen);
	this->SetEditFrontLen(14);

	UpdateComboList(&m_vecListData);
	SetListOver(TRUE);
}

void CTransparentComboBox::SetFont( const unsigned int dwFontSize, CString strFontFamily, BOOL bInvalidate )
{
	if ( NULL != m_pTransEdit )
	{
		m_nFontSize = dwFontSize;
		m_pTransEdit->SetFont( m_nFontSize, strFontFamily, bInvalidate );

	}
}

CTransparentComboBox::~CTransparentComboBox()
{
	if ( NULL != m_pTransEdit )
	{
		delete m_pTransEdit;
		m_pTransEdit = NULL;
	}

	if ( NULL != m_pDropWnd )
	{
		delete m_pDropWnd;
		m_pDropWnd = NULL;
	}

	if ( NULL != m_pDropList )
	{
		delete m_pDropList;
		m_pDropList = NULL;
	}

}


BEGIN_MESSAGE_MAP(CTransparentComboBox, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CTransparentComboBox)
ON_WM_LBUTTONDOWN()
ON_WM_SIZE()
ON_WM_KEYDOWN()
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
ON_MESSAGE( UI_EDITDELETE_CLICK, OnDropListClick )
ON_MESSAGE( WM_EDIT_SETFOCUS, OnSetFocus )
ON_MESSAGE( WM_UPDATE_COMBOEDIT_TEXT, OnUpdateEditText )
ON_MESSAGE( WM_CLICK_COMBOLISTICON, OnClickListIcon )
ON_MESSAGE( WM_MOUSEMOVE_COMBOLISTSHOWICON, OnMouseMoveShowIcon )
ON_MESSAGE( WM_EDIT_CHANGED, OnComboEditChange )
ON_MESSAGE( WM_EDIT_ONCHAR, OnComboEditChar )
//ON_WM_ACTIVATE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentComboBox message handlers
LRESULT CTransparentComboBox::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
	Graphics *pGraphics = (Graphics*)wParam;
    HWND hGraphWnd = (HWND )lParam;
    CWnd * pGraphWnd = FromHandle(hGraphWnd);

	if ( pGraphics == NULL )
	{
		NOTIF_PARENT_WND
		return S_OK;
	}

	if ( NULL != m_pTransEdit && IsWindowEnabled() != m_pTransEdit->IsWindowEnabled() )
	{
	 	m_pTransEdit->EnableWindow(this->IsWindowEnabled());
	}

	if( NULL != m_pDropWnd )
	{
		m_pDropWnd->PostMessage( WM_REDRAW_UI, 0, 0 );
	}

	return S_OK;
}

void CTransparentComboBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CTransparentBaseWnd::OnLButtonDown(nFlags,point);
}

LRESULT CTransparentComboBox::OnDropListClick( WPARAM wParam, LPARAM lParam )
{
	if ( m_vecListData.size() == 0 )
	{
		return 0L;
	}

	if ( NULL != m_pDropWnd )
	{
		CString strPreText;
		m_pTransEdit->GetWindowText(strPreText);

		if ( m_pDropWnd->IsWindowVisible() )
		{
			m_pDropWnd->ShowWindow(SW_HIDE);	
			m_pTransEdit->SetFocus();
			this->SetWindowPos( NULL, 0, 0, m_rcWnd.Width(), m_rcWnd.Height(), /*SWP_NOZORDER|*/SWP_NOMOVE|SWP_SHOWWINDOW );
		}
		else
		{
			m_pDropList->SetFocus();     //修正bug：下拉列表中无法使用鼠标滚轮  -- 20140522 by xhx
			int nListSize = m_vecListData.size();
			m_nListHeight = 5*m_nListItemHeight;				   //支持5行
			int nDropWndHeight = nListSize*m_nListItemHeight;      //高度增加编辑框边缘大小
			if ( nDropWndHeight <= 0 )
			{
				nDropWndHeight = 1;
			}

			CRect rectEdit;
			if ( NULL != m_pTransEdit )
			{
				m_pTransEdit->GetWindowRect(&rectEdit);
			}

			if ( nListSize != 0 )
			{
				nDropWndHeight += 4;
			}	

			if ( nListSize >= 5 )
			{
				m_pDropWnd->SetWindowPos( NULL, m_nEditEdge + rectEdit.left, 1 + m_pTransEdit->GetImageSize().cy - m_nEditEdge 
					+ rectEdit.top, m_rcWnd.Width() - 2*m_nEditEdge, m_nListHeight + m_nEditEdge + 4 , SWP_SHOWWINDOW|SWP_NOACTIVATE );
			}
			else
			{
				m_pDropWnd->SetWindowPos( &wndTop, m_nEditEdge + rectEdit.left, 1 + m_pTransEdit->GetImageSize().cy - m_nEditEdge+ rectEdit.top, 
					m_rcWnd.Width() - 2*m_nEditEdge, nDropWndHeight, SWP_SHOWWINDOW );
			}

			CString strEditText;
			m_pTransEdit->GetWindowText(strEditText);
			s32 nLineNum = JumpToSelItem(strEditText);
			UpdateComboList(&m_vecListData, nLineNum );
		}
	}

	return 0L;
}

LRESULT CTransparentComboBox::OnSetFocus( WPARAM wParam, LPARAM lParam )
{
    if ( (HWND)wParam == m_pTransEdit->GetSafeHwnd() )
    {   
		m_pDropWnd->ShowWindow(SW_HIDE);
		this->SetWindowPos( NULL, 0, 0, m_rcWnd.Width(), m_pTransEdit->GetImageSize().cy, /*SWP_NOZORDER|*/SWP_NOMOVE|SWP_SHOWWINDOW );
	}
	
	return 0L;
}

void CTransparentComboBox::UpdateComboList( std::vector<CString>* pListData, s32 nCurMoveItem )
{
	m_vecListData = *reinterpret_cast<std::vector<CString>*>(pListData);

	if ( NULL != m_pDropList )									//清空列表
	{
		m_pDropList->Clear();
		m_pDropList->GetRoot()->DeleteAllItem();
	}

	int nListSize = m_vecListData.size();
	if ( NULL != m_pTransEdit )
	{
		if ( nListSize == 0 )
		{
			m_pTransEdit->SetShowIcon(FALSE);
		}
		else
		{
			m_pTransEdit->SetShowIcon(TRUE);	
		}
	}

	int nDropWndHeight = m_nListItemHeight;
	if ( -1 == nCurMoveItem )
	{
		if ( m_pDropWnd->IsWindowVisible() )
		{
			m_nListHeight = 5*m_nListItemHeight;				//支持5行
			nDropWndHeight = nListSize*m_nListItemHeight;   //高度增加编辑框边缘大小
			if ( nDropWndHeight <= 0 )
			{
				nDropWndHeight = 1;
			}
			
			CRect rectEdit;
			if ( NULL != m_pTransEdit )
			{
				m_pTransEdit->GetWindowRect(&rectEdit);
			}
			
			CRect rc;
			if ( nListSize >= 5 )
			{
				m_pDropList->SetWindowPos( NULL, 0, 0, m_rcWnd.Width() - 2*m_nEditEdge - m_nSliderWidth, m_nListHeight, SWP_NOMOVE|SWP_SHOWWINDOW|SWP_NOACTIVATE );
				
				//设置显示滑块
				m_pDropList->GetWindowRect(&rc);
				m_pDropWnd->ScreenToClient( &rc );
				
				rc.top = rc.top;
				rc.left = rc.Width();
				rc.right = rc.right + m_nSliderWidth;
				rc.bottom = rc.bottom;
				
				m_pDropWnd->SetWindowPos( &wndTop, 0 + rectEdit.left, 0+ rectEdit.top, 
					m_rcWnd.Width() - 2*m_nEditEdge, m_nListHeight + 2, SWP_NOMOVE|SWP_SHOWWINDOW );			
				
				m_pDropList->SetSliderRect( rc );
				
				this->SetWindowPos( NULL, 0, 0, m_rcWnd.Width(), m_rcWnd.Height(), SWP_NOMOVE|SWP_SHOWWINDOW );
			}
			else
			{
				m_pDropList->SetWindowPos( NULL, 0, 0, m_rcWnd.Width() - 2*m_nEditEdge - m_nSliderWidth, nDropWndHeight, SWP_NOMOVE|SWP_SHOWWINDOW|SWP_NOACTIVATE );
				
				//设置显示滑块
				m_pDropList->GetWindowRect(&rc);
				m_pDropWnd->ScreenToClient( &rc );
				
				rc.top = rc.top + 1;
				rc.left = rc.Width();
				rc.right = rc.right + m_nSliderWidth;
				
				m_pDropWnd->SetWindowPos( &wndTop, 0, 0, 
					m_rcWnd.Width() - 2*m_nEditEdge, nDropWndHeight, SWP_NOMOVE|SWP_SHOWWINDOW );
				
				if ( 0 != nListSize )
				{
					m_pDropList->SetSliderRect( rc );
				}

				this->SetWindowPos( NULL, 0, 0, m_rcWnd.Width(), m_rcWnd.Height(), SWP_NOMOVE|SWP_SHOWWINDOW );
			}
		}
		
		if ( m_vecListData.size() == 0 )
		{
			return;
		}
	}

	IBaseItem* pBaseItem = m_pDropList->GetRoot()->GetItemData();

	if( NULL == pBaseItem)
	{
		return;
	}

    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVertNoSplit );
	pBaseItem->SetMoveStatus(true);

	CString strData;
	for ( int nKey = 0; nKey < nListSize; nKey++ )
	{
		strData = m_vecListData[nKey];

		Data_ComboMenu data(strData);
		data.SetDataKey( nKey );

		CListItem* plistItem = new CListItem( "", 0, m_nListItemHeight );
		if ( plistItem != NULL )
		{		
			plistItem->SetImageFolder( (String)m_strListItemFolder );
			plistItem->SetLayoutAlgorithm( IAlgorithm::strComboxItem );
			plistItem->SetUserData( &data ); 
			plistItem->SetFunc( (String)"ItemFun" );
		}


		IItemList *pNew = m_pDropList->GetRoot()->AddItem( nKey, plistItem, emGroup );
		
		if ( NULL != plistItem )
		{
			delete plistItem;
			plistItem = NULL;
		}
		
		CTextItem* pTextItem = new CTextItem( "", m_rcWnd.Width() - m_nListImgHeight, m_nListItemHeight );
		if ( NULL != pTextItem )
		{
			pTextItem->SetText( (String)strData );
			
			Font* pFont = CSrcManage::GetFont( "宋体", m_nFontSize );
			pTextItem->SetFont( pFont );
			pTextItem->SetAlignment( StringAlignmentNear );
			
			pTextItem->SetFontColor( m_itemNormalColor );
			pTextItem->SetSelColor( m_itemSelColor );
			
			pNew->AddItem( 0, pTextItem, emGroup );
			
			if ( NULL != pTextItem )
			{
				delete pTextItem;
				pTextItem = NULL;
			}
		}

		if ( m_bIsShowListIcon )
		{
			// 添加 图标 
			CImageItem* pImageItem = new CImageItem( "", m_nListImgHeight, m_nListImgHeight );
			if ( NULL != pImageItem )
			{
				if ( nCurMoveItem == nKey )
				{
					pImageItem->SetImageFolder( (String)m_strImageItemFolder );
				}
				else
				{
					pImageItem->SetImageFolder( "" );
				}
				
				pImageItem->SetFunc( (String)"IconFun" );
				pNew->AddItem( 1, pImageItem ,emGroup ); 
				if ( NULL != pImageItem )
				{
					delete pImageItem;
					pImageItem = NULL;
				}
			}
		}
	}

	m_pDropList->LayoutItem();			
	m_pDropList->ResetSelItem();		
	
	SendMessage( WM_REDRAW_UI, 0, (LPARAM)0 );   

	//显示滑块 动态调节列表宽度
	BOOL bNeedSlider;
	CRect rc;
	if ( -1 == nCurMoveItem )
	{
		bNeedSlider = m_pDropList->IsNeedSlider();
		if ( m_pDropList->IsNeedSlider() )
		{
			m_pDropList->SetWindowPos( NULL, 0, 0, m_rcWnd.Width() - 2*m_nEditEdge - m_nSliderWidth, m_nListHeight, SWP_NOMOVE|SWP_SHOWWINDOW|SWP_NOACTIVATE );
		}
		else
		{
			m_pDropList->SetWindowPos( NULL, 0, 0, m_rcWnd.Width() - 2*m_nEditEdge, nDropWndHeight, SWP_NOMOVE|SWP_SHOWWINDOW|SWP_NOACTIVATE );		
		}
	}
}

LRESULT CTransparentComboBox::OnUpdateEditText( WPARAM wParam, LPARAM lParam )
{
	LPCTSTR strEditText = (LPCTSTR)wParam;

	if ( NULL != m_pTransEdit )
	{
		if ( strEditText != m_strComboText )						 //Edit数据未变化不发送
		{
			SetComboText(strEditText);
			PostMessage( WM_CLICK_COMBOLIST, wParam, (LPARAM)GetSafeHwnd() );
			GetParent()->PostMessage( WM_CLICK_COMBOLIST, wParam, (LPARAM)GetSafeHwnd() );
		}

		//点击即隐藏列表
		m_pDropWnd->ShowWindow(SW_HIDE);	
		m_pTransEdit->SetFocus();
		this->SetWindowPos( NULL, 0, 0, m_rcWnd.Width(), m_rcWnd.Height(), /*SWP_NOZORDER|*/SWP_NOMOVE|SWP_SHOWWINDOW );
	}

	return 0L;
}

void CTransparentComboBox::SetComboText(CString strComboText)
{ 
	m_strComboText = strComboText;
	if ( NULL != m_pTransEdit )
	{
		if ( m_bIsIPStyle )
		{
			if ( strComboText.IsEmpty() )
			{
				m_pTransEdit->SetWindowText("");
			}
			else
			{
				SetIpAddress(ntohl( inet_addr( strComboText) ));
			}
		}
		else
		{
			m_pTransEdit->SetWindowText(m_strComboText);
		}
	}
}

CString CTransparentComboBox::GetComboText()
{ 
	if ( m_bIsIPStyle )
	{
		CTransparentIpEdit* pIPEdit = (CTransparentIpEdit*)m_pTransEdit;
		if ( NULL != pIPEdit )
		{
			DWORD dwIp = GetIpAddress( ntohl( inet_addr(m_strComboText) ) );
			m_strComboText = pIPEdit->GetIpStr( dwIp );
		}
	}

	return m_strComboText;
}

DWORD  CTransparentComboBox::GetIpAddress( DWORD dwIp )
{
	DWORD dwIpAddr = 0;
	CTransparentIpEdit* pIPEdit = (CTransparentIpEdit*)m_pTransEdit;
	if ( NULL != pIPEdit )
	{
		pIPEdit->GetAddress(dwIp);
		dwIpAddr = dwIp;
	}

	return dwIpAddr;
}

void CTransparentComboBox::IsIpInvalid( BOOL &bIsEmpty/*,BOOL &bIsInvalid */)
{
	CString cstrIp;
	CTransparentIpEdit* pIPEdit = (CTransparentIpEdit*)m_pTransEdit;

	pIPEdit->GetWindowText(cstrIp);

	if ( cstrIp == "" )
	{
		bIsEmpty  = TRUE;
	}
	else
	{
		bIsEmpty = FALSE;
	}
	
/*	int count = -1;
	int i = -1;	
	do
	{
		count++;
		i = cstrIp.Find( 46, i+1 );
	}while( i != -1 );
	
	if ( count != 3 )
	{
		bIsInvalid = TRUE;
	}
	else
	{
		bIsInvalid = FALSE;
	}*/
}

void  CTransparentComboBox::SetIpAddress( DWORD dwIp )
{
	CTransparentIpEdit* pIPEdit = (CTransparentIpEdit*)m_pTransEdit;
	if ( NULL != pIPEdit )
	{
		pIPEdit->SetAddress(dwIp);
	}
}

LRESULT CTransparentComboBox::OnClickListIcon( WPARAM wParam, LPARAM lParam )
{
	GetParent()->PostMessage( WM_CLICK_COMBOLISTICON, wParam, (LPARAM)GetSafeHwnd() );

	return 0L;
}

s32 CTransparentComboBox::JumpToSelItem(const CString& strEditText)
{
	s32 nMatchItem = -1;
	BOOL bMatch = FALSE;	

	s32 nListSize = m_vecListData.size();
	for ( int nIndex = 0; nIndex < nListSize; nIndex++ )
	{
		CString strText;
		strText = m_vecListData[nIndex];
		if ( strText == strEditText )
		{
			bMatch = TRUE;
			nMatchItem = nIndex;
		}
	}

	if ( nListSize > 0 )
	{
		if ( NULL != m_pDropList )
		{
			m_pDropList->SetSelItem( nMatchItem );
			
			UpdateComboList( &m_vecListData);
			
			if ( !bMatch )
			{
				m_pDropList->SetYOffset(0);
			}
		}
	}

	return nMatchItem;
}

void CTransparentComboBox::SetImage( const CString& strImageFolder )
{
	InitComboControl();

	CString strImageTmp;
	if ( NULL != m_pTransEdit )
	{
		strImageTmp = strImageFolder + "\\Edit";
		m_pTransEdit->SetImage( strImageTmp);
	}
	
	if ( NULL != m_pDropList )
	{
		if ( m_bSetBkColor )
		{
			m_pDropList->SetBkgColor( m_colorBkg );
		}

		strImageTmp = strImageFolder + "\\List";

		m_pDropList->SetImage( strImageTmp );

		strImageTmp += "\\VertSlider\\";
		m_pDropList->SetSliderImage(strImageTmp);

		//滑块宽度
		strImageTmp += "BkgMiddle.png";
		Image  *m_pImgBottomCenter = CSrcManage::GetImage( strImageTmp );
		if ( NULL != m_pImgBottomCenter )
		{
			m_nSliderWidth = m_pImgBottomCenter->GetWidth();
		}
	}	

	m_strListItemFolder = strImageFolder + "\\SelListItem";
 	m_strImageItemFolder = strImageFolder + "\\DelImg";

	//得到列表选中行图片高度和图标高度	
	m_nListItemHeight = CSrcManage::GetImageSize(strImageFolder + "\\SelListItem\\FocusLeft.png").cy;
	m_nListImgHeight = CSrcManage::GetImageSize(strImageFolder + "\\DelImg\\Normal.PNG").cy;
}

void CTransparentComboBox::SetReadOnly( BOOL bReadOnly )
{
	if ( NULL != m_pTransEdit )
	{
		m_pTransEdit->SetReadOnly(bReadOnly);
	}
}

void CTransparentComboBox::SetEnableWindow( BOOL bEnable )
{
	if ( NULL != GetSafeHwnd() )     //设置edit的enable状态时候也要将自身combox的enable状态改变，防止重绘的时候自身的enable没有变化，导致enable失败
	{
		EnableWindow(bEnable);
		if ( NULL != m_pTransEdit )
		{   
			m_pTransEdit->EnableWindow(bEnable);
		}
	}

	
}

void CTransparentComboBox::SetEditFrontLen(int nEditFrontLen)
{
	if ( NULL != m_pTransEdit )
	{
		m_pTransEdit->SetEditFrontLen(nEditFrontLen);
	}
}

void CTransparentComboBox::SetEditBackLen(int nEditBackLen)
{
	if ( NULL != m_pTransEdit )
	{
		m_pTransEdit->SetEditBackLen(nEditBackLen);
	}
}

void CTransparentComboBox::SetTextColor( Color colorNormal, Color colorFocus, BOOL bInvalidate)
{
	if ( NULL != m_pTransEdit )
	{
		m_colorNormal = colorNormal;
		m_colorFocus = colorFocus;
		m_pTransEdit->SetTextColor( colorNormal, colorFocus, bInvalidate );
	}
}

void CTransparentComboBox::SetDisableColor( Color colorDisable, BOOL bInvalidate)
{
	if ( NULL != m_pTransEdit )
	{
		m_colorDisable = colorDisable;
		m_pTransEdit->SetDisableColor( colorDisable, bInvalidate );
	}
}

BOOL CTransparentComboBox::AddString(CString strString)
{
	m_vecListData.push_back(strString);
	JumpToSelItem(strString);
	UpdateComboList(&m_vecListData);

	return TRUE;
}

BOOL CTransparentComboBox::DeleteString(CString strString)
{	
	std::vector<CString>::iterator iter = m_vecListData.begin();
	while( iter != m_vecListData.end() )
	{
		CString strDelText;
		strDelText = *iter;
		if ( strDelText == strString )
		{
			iter = m_vecListData.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	
	JumpToSelItem(strString);
	UpdateComboList(&m_vecListData);

	return TRUE;
}

LRESULT CTransparentComboBox::OnComboEditChange( WPARAM wParam, LPARAM lParam )
{ 
	CString strText;
	m_pTransEdit->GetWindowText( strText );
	if ( strText != m_strComboText )
	{
		m_strComboText = strText;

		PostMessage( WM_EDIT_CHANGED );
		GetParent()->PostMessage( WM_EDIT_CHANGED, (WPARAM)GetSafeHwnd() );
	}
	
    NOTIF_PARENT_WND

	return 0L;
}

LRESULT CTransparentComboBox::OnComboEditChar( WPARAM wParam, LPARAM lParam )
{ 
	CString strText;
	m_pTransEdit->GetWindowText( strText );
	if ( strText != m_strComboText )
	{
		m_strComboText = strText;
		
		PostMessage( WM_COMBOX_ONCHAR );
		GetParent()->PostMessage( WM_COMBOX_ONCHAR, (WPARAM)GetSafeHwnd() );
	}
	
    NOTIF_PARENT_WND
		
	return 0L;
}

void CTransparentComboBox::OnSize(UINT nType, int cx, int cy)
{
	this->SetWindowPos( NULL, 0, 0, cx, cy, SWP_NOMOVE|SWP_SHOWWINDOW );
	m_rcWnd = CRect(0,0,cx,cy);
	
	if ( NULL != m_pTransEdit )
	{
		m_pTransEdit->SetWindowPos( NULL, 0, 0, cx, m_pTransEdit->GetImageSize().cy, SWP_NOACTIVATE|SWP_SHOWWINDOW );
	}

	//CTransparentBaseWnd::OnSize(nType, cx, cy);
	CWnd::OnSize(nType, cx, cy);

}

void CTransparentComboBox::SetListBkgColor( Color colorBkg)
{
	m_bSetBkColor = TRUE;
	m_colorBkg = colorBkg;
}

LRESULT CTransparentComboBox::OnMouseMoveShowIcon( WPARAM wParam, LPARAM lParam )
{
	s32 nItemCount = static_cast<s32>(wParam);
	UpdateComboList( &m_vecListData, nItemCount );

	return 0L;
}

void CTransparentComboBox::SetListOver(BOOL bNeedOver)
{
	if ( NULL != m_pDropList )
	{
		m_pDropList->SetListOver(bNeedOver);
	}
}

void CTransparentComboBox::SetTipStr( CString strTip )
{
	if ( NULL != m_pTransEdit )
	{
		m_pTransEdit->SetTipStr(strTip);
	}
}

void CTransparentComboBox::SetTipFont( unsigned int dwFontSize /*= 12*/, CString strFontFamily /*= ("微软雅黑")*/, BOOL bInvalidate /*= FALSE*/ )
{
	if ( NULL != m_pTransEdit )
	{
		m_pTransEdit->SetTipFont( dwFontSize, strFontFamily, bInvalidate );
	}
}

void CTransparentComboBox::SetTipColor( Color colorTip, BOOL bInvalidate /*= FALSE*/ )
{
	if ( NULL != m_pTransEdit )
	{
		m_pTransEdit->SetTipColor( colorTip, bInvalidate );
	}
}

CTransparentEdit* CTransparentComboBox::GetEditPoint()
{
	return 	m_pTransEdit;
}