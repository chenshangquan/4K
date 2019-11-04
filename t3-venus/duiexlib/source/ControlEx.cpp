#include "StdAfx.h"
#include "ControlEx.h"

namespace DuiLib {
//////////////////////////////////////////////////////////////////////////
//
CommonScrollContainerUI::CommonScrollContainerUI()
	: m_uButtonState(0), m_dwDelayDeltaY(0), m_dwDelayNum(0), m_dwDelayLeft(0)
{
	m_strScrollXml = _T("scrollview.xml");
	for(int i = 0; i < 1; ++i) 
	{
		CDialogBuilder builder;
		CContainerUI* pDesk = static_cast<CContainerUI*>( builder.Create( m_strScrollXml.c_str(), (UINT)0 ) );
		if( pDesk ) 
		{
			this->Add(pDesk);
		}
		else 
		{
			this->RemoveAll();

			return;
		}
	}

	m_pImgData = NULL;
}

void CommonScrollContainerUI::DoEvent(TEventUI& event) 
{
	if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) 
	{
		if( m_pParent != NULL ) 
		{
			m_pParent->DoEvent(event);
		}
		else 
		{
			CScrollContainerUI::DoEvent(event);
		}

		return;
	}

	if( event.Type == UIEVENT_TIMER && event.wParam == SCROLL_TIMERID )
	{
		if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) 
		{
			POINT pt = m_pManager->GetMousePos();
			LONG cy = (pt.y - m_ptLastMouse.y);
			m_ptLastMouse = pt;
			SIZE sz = GetScrollPos();
			sz.cy -= cy;
			SetScrollPos(sz);

			return;
		}
		else if( m_dwDelayLeft > 0 ) 
		{
			--m_dwDelayLeft;
			SIZE sz = GetScrollPos();
			LONG lDeltaY =  (LONG)(CalculateDelay((double)m_dwDelayLeft / m_dwDelayNum) * m_dwDelayDeltaY);
			if( (lDeltaY > 0 && sz.cy != 0)  || (lDeltaY < 0 && sz.cy != GetScrollRange().cy ) ) 
			{
				sz.cy -= lDeltaY;
				SetScrollPos(sz);

				return;
			}
		}

		m_dwDelayDeltaY = 0;
		m_dwDelayNum = 0;
		m_dwDelayLeft = 0;
		m_pManager->KillTimer(this, SCROLL_TIMERID);

		return;
	}

	if( event.Type == UIEVENT_BUTTONDOWN && IsEnabled() )
	{
		m_uButtonState |= UISTATE_CAPTURED;
		m_ptLastMouse = event.ptMouse;
		m_dwDelayDeltaY = 0;
		m_dwDelayNum = 0;
		m_dwDelayLeft = 0;
		::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
		m_pManager->SetTimer(this, SCROLL_TIMERID, 50U);

		return;
	}
	if( event.Type == UIEVENT_BUTTONUP )
	{
		if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) 
		{
			m_uButtonState &= ~UISTATE_CAPTURED;
			::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));

			if( m_ptLastMouse.y != event.ptMouse.y ) 
			{
				m_dwDelayDeltaY = (event.ptMouse.y - m_ptLastMouse.y);

				if( m_dwDelayDeltaY > 120 ) 
				{
					m_dwDelayDeltaY = 120;
				}
				else if( m_dwDelayDeltaY < -120 ) 
				{
					m_dwDelayDeltaY = -120;
				}

				m_dwDelayNum = (DWORD)sqrt((double)abs(m_dwDelayDeltaY)) * 5;
				m_dwDelayLeft = m_dwDelayNum;

			}
			else
			{
				m_pManager->KillTimer(this, SCROLL_TIMERID);
			}
		}

		return;
	}
	if( event.Type == UIEVENT_SCROLLWHEEL )
	{
		LONG lDeltaY = 0;
		if( m_dwDelayNum > 0 ) 
		{
			lDeltaY =  (LONG)(CalculateDelay((double)m_dwDelayLeft / m_dwDelayNum) * m_dwDelayDeltaY);
		}

		switch( LOWORD(event.wParam) ) 
		{
		case SB_LINEUP:
			if( m_dwDelayDeltaY >= 0 ) 
			{
				m_dwDelayDeltaY = lDeltaY + 8;
			}
			else
			{
				m_dwDelayDeltaY = lDeltaY + 12;
			}
			break;
		case SB_LINEDOWN:
			if( m_dwDelayDeltaY <= 0 ) 
			{
				m_dwDelayDeltaY = lDeltaY - 8;
			}
			else 
			{	
				m_dwDelayDeltaY = lDeltaY - 12;
			}
			break;
		}
		if( m_dwDelayDeltaY > 100 ) 
		{ 
			m_dwDelayDeltaY = 100;
		}
		else if( m_dwDelayDeltaY < -100 ) 
		{
			m_dwDelayDeltaY = -100;
		}

		m_dwDelayNum = (DWORD)sqrt((double)abs(m_dwDelayDeltaY)) * 5;
		m_dwDelayLeft = m_dwDelayNum;
		m_pManager->SetTimer(this, SCROLL_TIMERID, 50U);

		return;
	}

	CScrollContainerUI::DoEvent(event);
}

void CommonScrollContainerUI::SetPos(RECT rc)
{
	if( GetCount() > 0 ) 
	{
		int iDeskWidth = GetItemAt(0)->GetFixedWidth();
		int column = (rc.right - rc.left) / iDeskWidth;
		if( column < 1 ) column = 1;
		SetColumns(column);
	}

	CScrollContainerUI::SetPos(rc);
}

void CommonScrollContainerUI::SetImage( const tString& strImage, double dblZoomRatio, bool bFixedYX )
{
	if ( NULL == m_pImgData || strImage != m_strImage )
	{
		m_strImage = strImage;								//设置载入图片大小
		m_pImgData = CUICommon::GetImgInfo(m_strImage.c_str());
	}

	SIZE szImgXY = {0};
	if ( NULL != m_pImgData )
	{
		CScollImageUI* pScollImageUI = NULL;
		pScollImageUI = static_cast<CScollImageUI*>(m_pManager->FindControl(_T("scrollviewscreen")));
		if ( NULL == pScollImageUI )
		{
			return;
		}

		pScollImageUI->SetScrollContainerUI(this);   //设置CommonScrollContainerUI指针   控制图片滚动、缩放等

		if ( !bFixedYX )
		{
			szImgXY.cx = m_pImgData->nX*dblZoomRatio;
			szImgXY.cy = m_pImgData->nY*dblZoomRatio;
		}
		else
		{
			szImgXY.cx = m_pImgData->nY*dblZoomRatio;
			szImgXY.cy = m_pImgData->nX*dblZoomRatio;
		}

		m_pVerticalScrollBar->SetScrollPos(0);		//置垂直水平滚动条为0 0 
		m_pHorizontalScrollBar->SetScrollPos(0);

		CContainerUI* pContainer = NULL;
		pContainer = static_cast<CContainerUI*>(m_pManager->FindControl(_T("scrollviewcontainer")));

		SIZE szTmpContain;
		szTmpContain.cx = 600;
		szTmpContain.cy = szImgXY.cy;
		pContainer->SetFixedXY(szTmpContain);
		pContainer->SetFixedWidth(szTmpContain.cx);
		pContainer->SetFixedHeight(szTmpContain.cy);


		SIZE szMaxContain = { szTmpContain.cx , pContainer->GetMaxHeight() };
		SetContainSize( szMaxContain );					//设置CContainerUI大小


		RECT rcPos = { 0 };
		rcPos.left = 0;    
		rcPos.top = 0;    
		rcPos.right = szImgXY.cx;    
		rcPos.bottom = szImgXY.cy;    
		SIZE szXY = {rcPos.left >= 0 ? rcPos.left : rcPos.right, rcPos.top >= 0 ? rcPos.top : rcPos.bottom};
		pScollImageUI->SetFixedXY(szXY);
		pScollImageUI->SetFixedWidth(rcPos.right - rcPos.left);
		pScollImageUI->SetFixedHeight(rcPos.bottom - rcPos.top);

		//pScollImageUI->SetFixedXY(szImgXY);
		//pScollImageUI->SetFixedWidth(pImgData->nX);
		pScollImageUI->SetNormalImage( strImage.c_str(), m_pImgData );

		SetImageXY(szImgXY);

		NeedUpdate();
	}
}

void CommonScrollContainerUI::UpdateUILayout( double dblZoomRatio, double dbAngle )
{
	if ( NULL == m_pImgData )
	{
		m_pImgData = CUICommon::GetImgInfo(m_strImage.c_str());
	}

	SIZE szImgXY = {0};
	if ( NULL != m_pImgData )
	{
		if ( dbAngle != 90 && dbAngle != 270 )
		{
			szImgXY.cx = m_pImgData->nX*dblZoomRatio;
			szImgXY.cy = m_pImgData->nY*dblZoomRatio;
		}
		else
		{
			szImgXY.cx = m_pImgData->nY*dblZoomRatio;
			szImgXY.cy = m_pImgData->nX*dblZoomRatio;
		}

		CContainerUI* pContainer = NULL;
		pContainer = static_cast<CContainerUI*>(m_pManager->FindControl(_T("scrollviewcontainer")));
		if ( NULL == pContainer )
		{
			return; 
		}

		SIZE szTmpContain;
		szTmpContain.cx = 600;
		szTmpContain.cy = szImgXY.cy;
		pContainer->SetFixedXY(szTmpContain);
		pContainer->SetFixedWidth(szTmpContain.cx);
		pContainer->SetFixedHeight(szTmpContain.cy);

		SetImageXY(szImgXY);
	}
}


//////////////////////////////////////////////////////////////////////////
//
CScollImageUI::CScollImageUI() : m_uButtonState(0)
{
	m_pScrollContainerUI = NULL;
	m_pImgData = NULL;
	m_dbAngle = 0;
}

LPCTSTR CScollImageUI::GetClass() const
{
	return _T("ScollImageUI");
}

LPVOID CScollImageUI::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, _T("ScollImageUI")) == 0 ) return static_cast<CScollImageUI*>(this);
	return CLabelUI::GetInterface(pstrName);
}

UINT CScollImageUI::GetControlFlags() const
{
	return UIFLAG_TABSTOP | (IsEnabled() ? UIFLAG_SETCURSOR : 0);
}

void CScollImageUI::SetScrollContainerUI(CommonScrollContainerUI* pScrollContainerUI)
{
	m_pScrollContainerUI = pScrollContainerUI;
}

void CScollImageUI::DoEvent(TEventUI& event)
{
	if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) 
	{
		if( m_pParent != NULL ) m_pParent->DoEvent(event);
		else CLabelUI::DoEvent(event);
		return;
	}

	if( event.Type == UIEVENT_SETFOCUS ) 
	{
		Invalidate();
	}
	if( event.Type == UIEVENT_KILLFOCUS ) 
	{
		Invalidate();
	}
	if( event.Type == UIEVENT_KEYDOWN )
	{
		if( event.chKey == VK_SPACE || event.chKey == VK_RETURN ) 
		{
			Activate();
			return;
		}

		else if ( event.chKey == 'Q' )	//缩						//加入键盘控制快捷键
		{
			m_eventUI.tGestureInfo.dblZoomRatio -= 0.1; 
			OnGestureZoom(m_eventUI);
		}
		else if ( event.chKey == 'E' )   //放
		{
			m_eventUI.tGestureInfo.dblZoomRatio += 0.1; 
			OnGestureZoom(m_eventUI);
		}
		else if ( event.chKey == 'W' )   //上
		{
			if ( NULL != m_pScrollContainerUI )
			{
				m_pScrollContainerUI->LineUp(16);
			}		
		}
		else if ( event.chKey == 'S' )	//下
		{
			if ( NULL != m_pScrollContainerUI )
			{
				m_pScrollContainerUI->LineDown(16);
			}
		}
		else if ( event.chKey == 'A' )	//左
		{
			if ( NULL != m_pScrollContainerUI )
			{
				m_pScrollContainerUI->LineLeft(16);
			}
		}
		else if ( event.chKey == 'D' )	//右
		{
			if ( NULL != m_pScrollContainerUI )
			{
				m_pScrollContainerUI->LineRight(16);
			}
		}
		else if ( event.chKey == 'R' )	//旋转
		{
			m_eventUI.tGestureInfo.bEndRotate = true;
			OnGestureRotate( m_eventUI );
		}
		return;


	}
	if( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK )
	{
		if( ::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled() ) 
		{
			m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
			Invalidate();
		}

		return;
	}
	if( event.Type == UIEVENT_MOUSEMOVE )
	{
		if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) 
		{
			if( ::PtInRect(&m_rcItem, event.ptMouse) ) m_uButtonState |= UISTATE_PUSHED;
			else m_uButtonState &= ~UISTATE_PUSHED;
			Invalidate();
		}

		return;
	}
	if( event.Type == UIEVENT_BUTTONUP )
	{
		if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) 
		{
			if( ::PtInRect(&m_rcItem, event.ptMouse) ) Activate();
			m_uButtonState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
			Invalidate();
		}
		return;
	}
	if( event.Type == UIEVENT_CONTEXTMENU )
	{
		if( IsContextMenuUsed() ) 
		{
			m_pManager->SendNotify(this, DUI_MSGTYPE_MENU, event.wParam, event.lParam);
		}
		return;
	}

	if ( event.Type == UIEVENT_TOUCH )			//触屏及手势消息
	{
		return;
	}
	if ( event.Type == UIEVENT_GESTURE )   
	{
		if( ::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled() ) 
		{
			m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
			Invalidate();
		}

		return;
	}
	if ( event.Type == UIEVENT_GESTURENOTIFY )  
	{
		if( ::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled() ) 
		{ 
			m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
			Invalidate();
		}

		return;
	}

	CLabelUI::DoEvent(event);
}

bool CScollImageUI::Activate()
{
	if( !CControlUI::Activate() ) return false;
	if( m_pManager != NULL ) m_pManager->SendNotify( this, DUI_MSGTYPE_CLICK );
	return true;
}

void CScollImageUI::SetEnabled(bool bEnable)
{
	CControlUI::SetEnabled(bEnable);
	if( !IsEnabled() ) {
		m_uButtonState = 0;
	}
}

LPCTSTR CScollImageUI::GetNormalImage()
{
	return m_strNormalImage;
}

void CScollImageUI::SetNormalImage( LPCTSTR pStrImage, TImageInfo* pImgData )
{
	if ( m_strNormalImage != pStrImage )
	{
		m_dbAngle = 0;
	}

	m_strNormalImage = pStrImage;
	m_pImgData = pImgData;

	Invalidate();
}

SIZE CScollImageUI::EstimateSize(SIZE szAvailable)
{
	if( m_cxyFixed.cy == 0 ) return CSize(m_cxyFixed.cx, m_pManager->GetDefaultFontInfo()->tm.tmHeight + 8);
	return CControlUI::EstimateSize(szAvailable);
}

void CScollImageUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if( _tcscmp(pstrName, _T("normalimage")) == 0 ) SetNormalImage(pstrValue);
	else if( _tcscmp(pstrName, _T("isgesture")) == 0 )		//2013 06 06 by ldy  label中图片拉伸控制
	{
		if( _tcscmp( pstrValue, _T("true") ) == 0 )
		{
			this->SetGesture(true);
		}
	}
	else CLabelUI::SetAttribute(pstrName, pstrValue);
}

void CScollImageUI::PaintStatusImage(HDC hDC)
{
	if( !m_strNormalImage.IsEmpty() ) 
	{
		if( !DrawImageGDIPlus( hDC, m_eventUI, CPoint( 0, 0), false, m_strNormalImage.GetData(), true ) ) m_strNormalImage.Empty();
		else return;
	}
}

void CScollImageUI::OnGestureBeg( TEventUI& event )
{
}

void CScollImageUI::OnGestureEnd( TEventUI& event )
{
}

BOOL CScollImageUI::OnGestureZoom( TEventUI& event )
{
	//return TRUE;
	m_eventUI = event;
	m_eventUI.tGestureInfo.dblAngle = m_dbAngle;		//传入当前角度

	if ( NULL != m_pScrollContainerUI )
	{
		m_pScrollContainerUI->UpdateUILayout( m_eventUI.tGestureInfo.dblZoomRatio, m_eventUI.tGestureInfo.dblAngle );
	}

	return TRUE;
}

BOOL CScollImageUI::OnGesturePan( TEventUI& event )
{
	//return TRUE;

	m_eventUI = event;
	m_eventUI.tGestureInfo.dblAngle = m_dbAngle;

	if ( NULL != m_pScrollContainerUI )				//图片滑动效果
	{
		if ( emGestureVerPan == event.tGestureInfo.emGestureType )
		{
			if ( event.tGestureInfo.ptOffset.y > 0 )
			{
				m_pScrollContainerUI->LineUp( abs(event.tGestureInfo.ptOffset.y) );	
			}
			else
			{
				m_pScrollContainerUI->LineDown( abs(event.tGestureInfo.ptOffset.y) );
			}
		}
		else if ( emGestureHorPan == event.tGestureInfo.emGestureType )
		{
			if ( event.tGestureInfo.ptOffset.x > 0 )
			{
				m_pScrollContainerUI->LineLeft( abs(event.tGestureInfo.ptOffset.x) );
			}
			else
			{
				m_pScrollContainerUI->LineRight( abs(event.tGestureInfo.ptOffset.x) );	
			}
		}
	}

	return TRUE;
}

BOOL CScollImageUI::OnGestureRotate( TEventUI& event )
{
	//return TRUE;	//----------------------------------------

	m_eventUI = event;

	if ( m_eventUI.tGestureInfo.bEndRotate )
	{
		m_eventUI.tGestureInfo.dblAngle = m_dbAngle;
		m_eventUI.tGestureInfo.dblAngle += 90;
		m_dbAngle += 90;
		if ( m_eventUI.tGestureInfo.dblAngle == 360 )
		{
			m_eventUI.tGestureInfo.dblAngle = 0;
			m_dbAngle = 0;
		}

		m_eventUI.tGestureInfo.dblAngle = m_dbAngle;	//传入当前角度

		if ( NULL != m_pScrollContainerUI )			//更新图片绘制布局
		{
			if ( m_dbAngle == 90 || m_dbAngle == 270 )
			{
				m_pScrollContainerUI->SetImage( (tString)m_strNormalImage, m_eventUI.tGestureInfo.dblZoomRatio, true );
			}
			else
			{
				m_pScrollContainerUI->SetImage( (tString)m_strNormalImage, m_eventUI.tGestureInfo.dblZoomRatio );
			}
		}
	}

	Invalidate();

	return TRUE;
}

BOOL CScollImageUI::OnGestureTwoFingerTap( TEventUI& event )
{
	return TRUE;
}

BOOL CScollImageUI::OnGesturePressAndTap( TEventUI& event )
{
	return TRUE;	//----------------------------------------

	m_eventUI = event;
	m_eventUI.tGestureInfo.dblAngle = m_dbAngle;	//传入当前角度

	//m_strNormalImage = L"C:\\HP_1.jpg";
	//SetNormalImage(m_strNormalImage);
	
	Invalidate();

	return TRUE;
}



} // namespace DuiLib
