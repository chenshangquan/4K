#include "stdafx.h"
#include "ControlEx.h"

CCommonListUI::CCommonListUI()
	: m_pNodeRoot(NULL)
	, m_delayDeltaY(0)
	, m_delayNumber(0)
	, m_delayLeft(0)
	, m_strLevelExpandImg(_T(""))			//层级图标
	, m_strLevelCollapseImg(_T(""))			//层级选中图标
	, m_strProgressName(_T(""))
	, m_nLevelTextStartPos(10)
	, m_rcTextPadding(10, 0, 0, 0)
	, m_nListItemHeight(32)
	, m_nListItemSelHeight(50)
	, m_nListItemSelBkPos(0)
	, m_nVirtualItemPos(-1)
	, m_bShowVirtualItem(FALSE)
{
	SetItemShowHtml(true);
	ResetNodeRoot();

	m_bDrag = FALSE;

	m_wndListUIDrag = NULL;
	m_bLButtonDown = FALSE;
	m_pListDragWnd = NULL;
	m_pNodeSelItem = NULL;

	m_bTimer = FALSE;
	m_hWndMain = NULL;

	m_pManageUI = NULL;

	m_pListCheckState = static_cast<CStdDataList<bool>*>( malloc( sizeof(CStdDataList<bool>) ) ); //new CStdDataList<bool>;
	m_pListCheckState->Clear();

	m_paryListData = static_cast<CStdDataArray<IData*>*>( malloc( sizeof(CStdDataArray<IData*>) ) );
	m_paryListData->Clear();
}

CCommonListUI::~CCommonListUI()
{
	SAFE_RELEASE(m_pNodeRoot);

	m_pListCheckState->Clear();
	m_paryListData->Clear();
}

LPCTSTR CCommonListUI::GetClass() const
{
	return _T("CommonListUI");
}

LPVOID CCommonListUI::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, _T("CommonListUI")) == 0 ) return static_cast<CCommonListUI*>(this);
	return CListUI::GetInterface(pstrName);
}

void CCommonListUI::SetMainFrameWnd(RECT rcRect)
{ 
	if ( NULL == m_hWndMain )
	{
		m_hWndMain = m_pManager->GetPaintWindow();

		if( NULL == m_wndListUIDrag && m_bDrag )											//操作列表第一次进入创建拖拽显示窗口
		{
			if ( NULL != m_hWndMain && NULL != m_pManager )
			{
				m_wndListUIDrag = new CListUIDragWnd( m_hWndMain,  *m_pManageUI );
			}
			
			m_wndListUIDrag->SetThisRect(rcRect);
			m_wndListUIDrag->SetListItemHeight(m_nListItemSelHeight);
		}
	}
}

// bool CCommonListUI::Add(CControlUI* pControl)
// {
// 	if (!pControl)	return false;
// 	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) == 0)	return false;
// 
// 	return CListUI::Add(pControl);
// }

// bool CCommonListUI::AddAt(CControlUI* pControl, int iIndex)
// {
// 	if (!pControl)	return false;
// 	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) != 0)	
// 		return false;
// 
// 	return CListUI::AddAt(pControl, iIndex);
// }

// bool CCommonListUI::Remove(CControlUI* pControl)
// {
// 	if (!pControl)	return false;
// 	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) == 0)	return false;
// 
// 	return CListUI::Remove(pControl);
// }

// bool CCommonListUI::RemoveAt(int iIndex)
// {
// 	CControlUI* pControl = GetItemAt(iIndex);
// 
// 	if (!pControl)	return false;
// 	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) != 0)	return false;
// 
// 	return CListUI::RemoveAt(iIndex);
// }

void CCommonListUI::RemoveAll()
{
	CListUI::RemoveAll();

	ResetNodeRoot();
}

void CCommonListUI::ResetNodeRoot()
{
	SAFE_RELEASE(m_pNodeRoot);

	m_pNodeRoot = new Node;
	m_pNodeRoot->GetData().nLevel = -1;
	m_pNodeRoot->GetData().bChildVisible = true;
	m_pNodeRoot->GetData().bHasChild = true;
	m_pNodeRoot->GetData().pListElement = NULL;
}

BOOL CCommonListUI::DragEnd()
{
	int nIndex = GetDragListCtrlWnd()->GetVirtualItemPos();
	GetDragListCtrlWnd()->RemoveVirtualItem();
	GetDragListCtrlWnd()->SetVirtualItemPos(nIndex);

	IData* pData = const_cast<IData*>(GetSelectItemNode()->GetUserData());
	if ( NULL == pData )
	{
		return FALSE;
	}
	GetDragListCtrlWnd()->AddNode( *pData, NULL );

	//更新列表数据
	CStdDataArray<IData*>* paryListData = NULL;
	GetDragListCtrlWnd()->GetListData( &paryListData );
	if ( -1 == GetDragListCtrlWnd()->GetVirtualItemPos() )
	{
		paryListData->AddAtAnd( pData );
	}
	else
	{
		paryListData->AddAt( GetDragListCtrlWnd()->GetVirtualItemPos(), pData );
	}

	GetDragListCtrlWnd()->SetVirtualItemPos(-1);
	GetDragListCtrlWnd()->SelectItem( nIndex  );

	if( m_pManager != NULL ) 
	{
		m_pManager->SendNotify( this->GetItemAt(m_iCurSel), DUI_MSGTYPE_DRAG_END, (WPARAM)m_iCurSel );
	}

	return TRUE;
}

void CCommonListUI::DoEvent(TEventUI& event) 
{
	//控制列表拖拽窗口显示
	if( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_RBUTTONDOWN )
    {
		if ( m_bDrag && NULL != GetSelectItemNode() )
		{
			if ( !GetSelectItemNode()->IsFolder() )
			{
				m_ptLButtonDown = event.ptMouse;
				m_bLButtonDown = TRUE;
				m_bTimer = FALSE;

				if ( NULL != m_pManager )
				{
					if ( !m_pManager->SetTimer( this, TIMER_ID_DRAGWNDLIST, 1000U ) )
					{
						OutputDebugString( L"\n TIMER_ID_DRAGWNDLIST Set Fails" );
					}
				}
			}
		}

		SetDragWndIng(false);
    }
	if( event.Type == UIEVENT_BUTTONUP && IsEnabled() ) 
	{
		if ( m_bDrag )
		{
			m_bLButtonDown = FALSE;

			if( m_bDrag && NULL != GetDragListCtrlWnd() && NULL != GetSelectItemNode() && m_bTimer )   														//拖拽到列表，添加数据到目标列表
			{
				RECT rcFilelistright = GetDragListCtrlWnd()->GetControlRect();
				if ( !GetSelectItemNode()->IsFolder() && ::PtInRect( &rcFilelistright, event.ptMouse )\
					&& GetDragListCtrlWnd() != this )
				{
					DragEnd();
				}

				SetDragWndIng(false);
			}

			if ( m_bDrag && NULL != m_pManager )
			{
				if ( !m_pManager->KillTimer( this, TIMER_ID_DRAGWNDLIST ) )
				{
					OutputDebugString( L"\nTIMER_ID_DRAGWNDLIST Kill Fails" );
				}
				else
				{
					m_bTimer = FALSE;
				}
			}

			if( NULL != m_wndListUIDrag )
			{
				m_wndListUIDrag->ShowWnd(false);
				m_wndListUIDrag->ResetDraw();
			}
		}
    }
    if( event.Type == UIEVENT_MOUSEMOVE ) 
	{
		if ( m_bDrag && NULL != m_pNodeSelItem && m_bTimer )
		{
			if ( !m_pNodeSelItem->IsFolder() )
			{
				if ( m_bLButtonDown )
				{
					//if( !::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled() )			//拖出列表外绘制拖拽条目,否则隐藏
					{
						SetMainFrameWnd(m_pNodeSelItem->GetData().pListElement->GetControlRect());
						m_wndListUIDrag->MoveWnd(event.ptMouse, m_pNodeSelItem->GetData().pListElement);
					}
// 					else
// 					{
// 						m_wndListUIDrag->ShowWnd(false);
// 					}

					if( m_bDrag && NULL != GetDragListCtrlWnd() && m_bTimer )   														//拖拽到列表，添加数据到目标列表
					{
						RECT rcLstRight = GetDragListCtrlWnd()->GetControlRect();
						if ( ::PtInRect( &rcLstRight, event.ptMouse ) && GetDragListCtrlWnd() != this )
						{
							GetDragListCtrlWnd()->SelectItem( -1  );

							CControlUI* pControl = static_cast<CControlUI*>(m_pManager->FindControl(event.ptMouse));
							BOOL bPointInElement = FALSE;
							while ( NULL != pControl )
							{
								if ( _tcsicmp( pControl->GetClass(), _T("ListContainerElementUI")) == 0 )
								{
									bPointInElement = TRUE;
									
									CListContainerElementUI* pListItem = static_cast<CListContainerElementUI*>(pControl);
									if ( NULL != pListItem )
									{
										int nIndex = pListItem->GetIndex();
										if ( GetDragListCtrlWnd()->GetVirtualItemPos() != nIndex )
										{
											if ( ( GetDragListCtrlWnd()->GetVirtualItemPos() != nIndex - 1 ) &&
												GetDragListCtrlWnd()->IsVirtualItemShow() )
											{
												GetDragListCtrlWnd()->RemoveVirtualItem();
											}
											
											if ( -1 == GetDragListCtrlWnd()->GetVirtualItemPos() )
											{
												GetDragListCtrlWnd()->SetVirtualItemPos( nIndex );
												GetDragListCtrlWnd()->ShowVirtualItemData();
											}
										}
									}
									break;
								}
								pControl = pControl->GetParent();
							}

							if ( !bPointInElement )
							{
								if ( ( GetDragListCtrlWnd()->GetVirtualItemPos() != -1 ) &&
									( GetDragListCtrlWnd()->IsVirtualItemShow() ) &&
									( GetDragListCtrlWnd()->GetVirtualItemPos() != GetDragListCtrlWnd()->GetCount() - 1 ) )
								{
									GetDragListCtrlWnd()->RemoveVirtualItem();
								}

								if ( ( GetDragListCtrlWnd()->GetVirtualItemPos() == -1 ) &&
									!( GetDragListCtrlWnd()->IsVirtualItemShow() ) )
								{
									GetDragListCtrlWnd()->ShowVirtualItemData();
								}
							}
						}
						else
						{
							GetDragListCtrlWnd()->RemoveVirtualItem();
						}
					}
				}
				else
				{
					if( NULL != m_wndListUIDrag ) 
					{
						m_wndListUIDrag->ShowWnd(false);
					}
				}
			}
			else
			{
				if( NULL != m_wndListUIDrag ) 
				{
					m_wndListUIDrag->ShowWnd(false);
				}
			}
		}
    }
	if( event.Type == UIEVENT_TIMER && event.wParam == TIMER_ID_DRAGWNDLIST )
	{
		if ( m_bDrag )
		{
			m_bTimer = TRUE;

			if( NULL != m_wndListUIDrag && !::IsWindowVisible(m_wndListUIDrag->GetHWND()) )															//操作列表第一次进入创建拖拽显示窗口
			{
				m_wndListUIDrag->MoveWnd(event.ptMouse,NULL);
			}

			SetDragWndIng(true);
		}
	}

	CListUI::DoEvent(event);
}

Node* CCommonListUI::GetRoot()
{
	return m_pNodeRoot;
}

Node* CCommonListUI::AddNode(const IData& item, Node* pParent)
{
	if ( NULL == pParent )	pParent = m_pNodeRoot;

// 	if ( -1 == m_nVirtualItemPos )
// 	{
// 		m_paryListData->AddAtAnd( const_cast<IData*>(&item) );
// 	}
// 	else
// 	{
// 		m_paryListData->AddAt( this->GetVirtualItemPos(), const_cast<IData*>(&item) );
// 	}

	if ( !m_strStyle.empty() )
	{
		ADD_NODE_VALUE_EX( Data_FileList, item, pParent )
		ADD_NODE_VALUE_EX( Data_ConfList, item, pParent )
		ADD_NODE_VALUE_EX( Data_AddrList, item, pParent )
	}
	else
	{
		ADD_NODE_VALUE( Data_DynamicList, item, pParent )
		ADD_NODE_VALUE( Data_BoardList, item, pParent )
		ADD_NODE_VALUE( Data_TvwStyleList, item, pParent )
	}
	
	return NULL;
}

void CCommonListUI::RemoveNode(Node* node)
{
	if ( !node || node == m_pNodeRoot ) return;

	for ( int i = 0; i < node->GetChildNum(); ++i )
	{
		Node* child = node->GetChild(i);
		RemoveNode(child);
	}

	CListUI::Remove(node->GetData().pListElement);
	SAFE_RELEASE(node->GetData().pListElement);
	node->GetParent()->RemoveChild(node);
	SAFE_RELEASE(node);
}

bool CCommonListUI::CanExpand(Node* node) const
{
	if (!node || node == m_pNodeRoot)	return false;

	return node->GetData().bHasChild;
}

bool CCommonListUI::SelectItem(int iIndex)
{
    if( iIndex == m_iCurSel ) return true;

	TListInfoUI* ptListInfoUI = this->GetListInfo();
	ptListInfoUI->dwSelectedBkColor = 0xFF121212;
	RECT rc = ptListInfoUI->rcTextPadding;

    //默认不选中ITEM
    if( m_iCurSel >= 0 ) 
	{
        CControlUI* pControl = GetItemAt(m_iCurSel);
        if( pControl != NULL) 
		{
            IListItemUI* pListItem = static_cast<IListItemUI*>( pControl->GetInterface(_T("ListItem") ) );
            if( pListItem != NULL )
			{
				CListContainerElementUI* pCommonListItem = static_cast<CListContainerElementUI*>(pControl);
				Node* node = (Node*)pControl->GetTag();
				if ( ( pCommonListItem != NULL ) && ( node != NULL ) && !node->IsFolder() )
				{
					pCommonListItem->SetFixedHeight(m_nListItemHeight);
					CContainerUI* pOperatorPannel = static_cast<CContainerUI*>( m_pManager->FindSubControlByName( pCommonListItem, PRO_PANE_LISTITEM_HIDE ) );
					if (pOperatorPannel != NULL)
					{
						pOperatorPannel->SetVisible(false);
					}
				}
				pListItem->Select(false);
			}
        }

        m_iCurSel = -1;
    }

    if( iIndex < 0 )	return false;
	if ( !__super::SelectItem(iIndex) )	return false;

	CControlUI* pControl = GetItemAt(m_iCurSel);
	if( pControl != NULL) 
	{
		CListContainerElementUI* pCommonListItem = static_cast<CListContainerElementUI*>(pControl);
		Node* node = (Node*)pControl->GetTag();
		if ((pCommonListItem != NULL) && (node != NULL) && !node->IsFolder())
		{
			pCommonListItem->SetFixedHeight(m_nListItemSelHeight);
			pCommonListItem->SetSelBkPos(m_nListItemSelBkPos);
			CContainerUI* pOperatorPannel = static_cast<CContainerUI*>( m_pManager->FindSubControlByName( pCommonListItem, PRO_PANE_LISTITEM_HIDE ) );
			if (pOperatorPannel != NULL)
			{
				pOperatorPannel->SetVisible(true);
			}

			m_pNodeSelItem = node;							//得到当前选中的行数据
		}
		else												//目录则直接清空m_pNodeSelItem    不需要拖拽
		{
			m_pNodeSelItem = NULL;
		}
	}

	return true;
}

void CCommonListUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
	if( _tcscmp( pstrName, _T("header") ) == 0 )			//此属性必须设置  否则间距会有问题
	{
		GetHeader()->SetVisible( _tcscmp(pstrValue, _T("hidden")) != 0 );
	}
	else if( _tcscmp(pstrName, _T("isdrag")) == 0 )
	{
		if ( _tcscmp(pstrValue, _T("true") ) == 0 )
		{
			m_bDrag = TRUE;
		}
	}
	else if( _tcscmp(pstrName, _T("levelexpandimg")) == 0 )
	{
		if ( wcslen( pstrValue ) != 0 )
		{
			m_strLevelExpandImg = L"<i "; 
			m_strLevelExpandImg += pstrValue;
			m_strLevelExpandImg += L">"; 
		}
		
	}
	else if( _tcscmp(pstrName, _T("levelcollapseimg")) == 0 )
	{
		if ( wcslen( pstrValue ) != 0 )
		{
			m_strLevelCollapseImg = L"<i "; 
			m_strLevelCollapseImg += pstrValue;
			m_strLevelCollapseImg += L">"; 
		}
	}
	else if( _tcscmp(pstrName, _T("style")) == 0 )
	{
		m_strStyle = pstrValue;
	}
	else if( _tcscmp(pstrName, _T("listitemheight")) == 0 )
	{
		m_nListItemHeight = _ttoi(pstrValue);
	}
	else if( _tcscmp(pstrName, _T("listitemselheight")) == 0 )
	{
		m_nListItemSelHeight = _ttoi(pstrValue);
	}
	else if( _tcscmp(pstrName, _T("listitemselbkpos")) == 0 )
	{
		m_nListItemSelBkPos = _ttoi(pstrValue);
	}
	else /*CVerticalLayoutUI*/
	{
		CListUI::SetAttribute( pstrName, pstrValue );
	}
}

void CCommonListUI::UpdateList(std::vector<IData*>& vecData)
{
	if ( this->GetCount() > 0 )
	{
		this->RemoveAll();
	}


	Node* pRoot = NULL;
	IData* pListItemData = NULL;
	for( size_t nIndex = 0; nIndex < vecData.size(); nIndex++ )
	{
		pListItemData = vecData[nIndex];

		if ( NULL == pListItemData )
		{
			continue;
		}

		//const Data_FileList* pData = dynamic_cast<const Data_FileList*>( pListItemData ); 
		//if ( pData->m_tData.bFolder )
		//{
		//	pRoot = AddNode( *pListItemData, NULL);    //目录则设置一个新节点  以下的节点都加入其中   为展开目录需要  目前项目不需要  可点击
		//}
		//else
		//{
		//	this->AddNode( *pListItemData, pRoot );
		//}
		this->AddNode( *pListItemData, pRoot );
	}
}

void CCommonListUI::UpdateList(CStdDataArray<IData*>& vecData)
{
	if ( this->GetCount() > 0 )
	{
		this->RemoveAll();
	}

	this->SetListData( vecData );

	Node* pRoot = NULL;
	IData* pListItemData = NULL;
	for( size_t nIndex = 0; nIndex < vecData.GetSize(); nIndex++ )
	{
		pListItemData = vecData[nIndex];

		if ( NULL == pListItemData )
		{
			continue;
		}

		this->AddNode( *pListItemData, pRoot );
	}
}

CListContainerElementUI* CCommonListUI::CreateElement()
{
	CListContainerElementUI* pListElement = NULL;
	if( !m_dlgBuilder.GetMarkup()->IsValid() ) 
	{
		tString strStyleXml;
		strStyleXml = m_strStyle;
		strStyleXml += _T(".xml")  ;
		pListElement = static_cast<CListContainerElementUI*>( m_dlgBuilder.Create( strStyleXml.c_str(), (UINT)0, NULL, m_pManager ) );
	}
	else 
	{
		pListElement = static_cast<CListContainerElementUI*>( m_dlgBuilder.Create( (UINT)0, m_pManager ) );
	}

	if ( this->GetMosaicBk() )
	{
		pListElement->SetMosaicItemImage(/*this->*/GetBkImage());
		pListElement->PreDrawMosaicSelectItemBk();
	}

	return pListElement;
}

void CCommonListUI::SetContainerVisible( CControlUI* pItemList, const tString& strWndName, bool bVisible )
{
	CContainerUI* ct = static_cast<CContainerUI*>(m_pManager->FindSubControlByName( pItemList, strWndName.c_str() ) );
	if (ct != NULL)
	{
		ct->SetVisible(bVisible);
	}
}

CButtonUI* CCommonListUI::SetButtonNode( CControlUI* pItemList, const tString& strWndName, bool (*pFn)(void*) )
{
	CButtonUI* pBtn = static_cast<CButtonUI*>(m_pManager->FindSubControlByName( pItemList, strWndName.c_str() ) );
	if (pBtn != NULL)
	{
		pBtn->OnEvent += MakeDelegate(pFn);
	}

	return pBtn;
}

CLabelUI* CCommonListUI::SetLabelNode( CControlUI* pItemList, const tString& strWndName, const tString& strText, bool bShowHtml )
{
	CLabelUI* plb = static_cast<CLabelUI*>( m_pManager->FindSubControlByName( pItemList, strWndName.c_str() ) );
	if ( plb != NULL )
	{
		plb->SetShowHtml(bShowHtml);
		plb->SetFont(7);
		plb->SetText( strText.c_str() );
	}

	return plb;
}

CProgressUI* CCommonListUI::SetProgressNode( CControlUI* pItemList, const tString& strWndName, int nValue, bool bShowHtml )
{
	CProgressUI* pPro = static_cast<CProgressUI*>( m_pManager->FindSubControlByName( pItemList, strWndName.c_str() ) );
	if ( pPro != NULL )
	{
		pPro->SetShowHtml(bShowHtml);		
		pPro->SetValue( nValue );
		m_strProgressName = strWndName;
	}

	return pPro;
}

CListIconUI* CCommonListUI::SetClickLabelNode( CControlUI* pItemList, const tString& strWndName, int nIndex,
	bool bSelState, const tString& strItemName, Node* pItemNode )
{
	CListIconUI* plb = static_cast<CListIconUI*>( m_pManager->FindSubControlByName( pItemList, strWndName.c_str() ) );
	if ( plb != NULL )
	{
		plb->SetLabelIndex(nIndex);
		plb->SetLabelSelState(bSelState);
		plb->SetItemName(strItemName);
		if ( NULL != m_pManageUI )
		{
			plb->SetManagerUI(m_pManageUI);
		}
		//设置对应列表项的数据
		plb->SetTag((UINT_PTR)pItemNode);
	}

	return plb;
}

CListContainerElementUI* CCommonListUI::CreateElement( const tString& strHeight, const tString& strWidth )
{
	CListContainerElementUI* pItemList = new CListContainerElementUI;
	if ( NULL != pItemList )
	{
		tString strHtml;
		strHtml.append(_T("height=\"")).append(strHeight.c_str());
		
		if ( !strWidth.empty() )
		{
			strHtml.append(_T("\" width=\"")).append(strWidth.c_str());
		}

		strHtml.append(_T("\""));

		pItemList->ApplyAttributeList(strHtml.c_str());
	}

	return pItemList;
}

CLabelUI* CCommonListUI::CreateLabel(const TItemNodeUI& tItemNodeUI)
{
	CLabelUI* plb = new CLabelUI;
	if ( NULL != plb )
	{
		tString strHtml;
		strHtml.append(_T("textcolor=\"#FFFF22DD\" pos=\"")).append(tItemNodeUI.strPos.c_str()).append(_T("\" width=\"")).append(tItemNodeUI.strWidth.c_str()).append(_T("\" showhtml=\"true\""));
		plb->ApplyAttributeList(strHtml.c_str());
		plb->SetText(tItemNodeUI.strText.c_str());
		plb->SetName(_T("down_name"));
	}

	return plb;
}

CTextUI* CCommonListUI::CreateText(const TItemNodeUI& tItemNodeUI)
{
	CTextUI* pText = new CTextUI;
	if ( NULL != pText )
	{
		tString strHtml;
		strHtml.append(_T("name=\"jdtbk\" float=\"true\" pos=\"")).append(tItemNodeUI.strPos.c_str()).append(_T("\" width=\"")).append(tItemNodeUI.strWidth.c_str()).
			append(_T("\" height=\"")).append(tItemNodeUI.strHeight.c_str()).append(_T("\" text=\"")).append(tItemNodeUI.strText.c_str()).append(_T("\" textcolor=\"")).
			append(tItemNodeUI.strFontColor.c_str()).append(_T("\" bkimage=\"file=''\""));
		pText->ApplyAttributeList(strHtml.c_str());
		pText->SetFont(tItemNodeUI.nFont);
	}

	return pText;
}

CButtonUI* CCommonListUI::CreateButton(const TItemNodeUI& tItemNodeUI)
{
	CButtonUI* pBtn = new CButtonUI;
	if ( NULL != pBtn )
	{
		tString strHtml;
		strHtml.append(_T("name=\"stop\" float=\"true\" pos=\"")).append(tItemNodeUI.strPos.c_str()).append(_T("\" width=\"")).append(tItemNodeUI.strWidth.c_str()).
			append(_T("\" height=\"")).append(tItemNodeUI.strHeight.c_str()).append(_T("\" tooltip=\"tip..\" normalimage=\"file='")).append(tItemNodeUI.strImgPath.c_str()).append(L"\\Normal.png").
		append(_T("'\" focusedimage=\"file='")).append(tItemNodeUI.strImgPath.c_str()).append(L"\\Sel.png").append(_T("'\" pushedimage=\"file='")).append(tItemNodeUI.strImgPath.c_str()).append(L"\\Sel.png").
		append(_T("'\" hotimage=\"file='")).append(tItemNodeUI.strImgPath.c_str()).append(L"\\Over.png").append(_T("'\""));
		pBtn->ApplyAttributeList(strHtml.c_str());
	}

	return pBtn;
}

CProgressUI* CCommonListUI::CreateProgress(const TItemNodeUI& tItemNodeUI)
{
	CProgressUI *pProgress = new CProgressUI;
	if ( NULL != pProgress )
	{
		tString strHtml;
		strHtml.append(_T("name=\"jdt\" float=\"true\" pos=\"")).append(tItemNodeUI.strPos.c_str()).append(_T("\" width=\"")).append(tItemNodeUI.strWidth.c_str()).
			append(_T("\" height=\"")).append(tItemNodeUI.strHeight.c_str()).append(_T("\" fgimage=\"file='")).append(tItemNodeUI.strImgPath.c_str()).append(_T("'\""));
		pProgress->ApplyAttributeList(strHtml.c_str());
		pProgress->SetMaxValue(100);
		pProgress->SetValue(tItemNodeUI.nValue);
		pProgress->SetMinValue(0);
	}

	return pProgress;
}

//bool CCommonListUI::AddAtEnd( CControlUI* pItemList, Node* pParent )
//{
//	int nIndex = 0;												//将结点加入到最后    也可以动态加入到其他位置
//	if ( pParent->IsHasChild() )
//	{
//		Node* pPrev = pParent->GetLastChild();
//		nIndex = pPrev->GetData().pListElement->GetIndex() + 1;
//	}
//	else 
//	{
//		if ( pParent == m_pNodeRoot )
//		{
//			nIndex = 0;
//		}
//		else
//		{
//			nIndex = pParent->GetData().pListElement->GetIndex() + 1;
//		}
//	}
//	if ( !CListUI::AddAt( pItemList, nIndex ) )
//	{
//		return false;
//	}
//
//	return true;
//}

bool CCommonListUI::AddAtEnd( CControlUI* pItemList, Node* pParent )
{
	if ( NULL == pItemList )
	{
		return false;
	}

	if ( !CListUI::AddAt( pItemList, this->GetCount() ) )
	{
		return false;
	}

	return true;
}

bool CCommonListUI::AddAt( CControlUI* pControl, Node* pParent )
{
	if ( NULL == pControl )
	{
		return false;
	}

	if ( !CListUI::AddAt( pControl, m_nVirtualItemPos ) )
	{
		return false;
	}

	return true;
}

bool CCommonListUI::RemoveAt(int iIndex)
{
	CControlUI* pControl = GetItemAt(iIndex);
	if ( NULL == pControl )
	{
		return false;
	}

	pControl->SetTag( NULL );

	return CListUI::RemoveAt(iIndex);
}

 BOOL CCommonListUI::RemoveVirtualItem()
 {
	 if ( m_nVirtualItemPos != -1 && m_bShowVirtualItem )
	 {
		if ( !this->RemoveAt( m_nVirtualItemPos ) )
		{
			return FALSE;
		}

		if ( m_nVirtualItemPos == 0 )
		{
			this->ResetNodeRoot();
		}

		m_nVirtualItemPos = -1;
		m_bShowVirtualItem = FALSE;

		return TRUE;
	 }

	 return FALSE;	
 }

 void CCommonListUI::ShowVirtualItemData()
 {
	 if ( m_bShowVirtualItem )
	 {
		 return;
	 }

	 CListContainerElementUI* pItemList = this->CreateElement();
	 if ( pItemList == NULL )	return;
	 pItemList->Select(true);
	 pItemList->SetFixedHeight(m_nListItemHeight);			
	 pItemList->SetItemName(this->GetName());

	 Node* pItemNode = new Node;
	 if ( NULL == pItemNode )	return;
	 pItemNode->GetData().pListElement = pItemList;
	 pItemList->SetTag((UINT_PTR)pItemNode);

	 if ( -1 == m_nVirtualItemPos )
	 {
		 this->AddAtEnd( pItemList, NULL );
	 }
	 else
	 {
		 this->AddAt( pItemList, NULL );
	 }
	 
	 m_bShowVirtualItem = TRUE;

	 if ( -1 == m_nVirtualItemPos )
	 {
		 m_nVirtualItemPos = this->GetCount() - 1;
	 } 
 }

 bool CCommonListUI::SetCheckStateMap(int nKey, bool bSelState)
 {
	 TSNode<bool>* pNode = m_pListCheckState->FindByKey(nKey);
	 if ( NULL != pNode )
	 {
		 if ( bSelState == pNode->m_val )
		 {
			 return false;
		 }

		 m_pListCheckState->Remove(nKey);
	 }
	 
	 if ( bSelState )
	 {
		 if ( -1 == m_nVirtualItemPos )
		 {
			 m_pListCheckState->InsertItem(nKey, bSelState);
		 }
		 else
		 {
			 m_pListCheckState->InsertAt(m_nVirtualItemPos, nKey, bSelState);
			 this->SetVirtualItemPos(-1);
		 }
	 }

	 return true;
 }

 void CCommonListUI::SetListData(CStdDataArray<IData*>& aryListData)
 {
	m_paryListData->Clear();
	*m_paryListData = aryListData; 
 }

