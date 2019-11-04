/********************************************************************
	模块名:      UILib
	文件名:      skinscroll.cpp
	相关文件:    UILIbHead.h
	文件实现功能 
    作者：       朱允荣
	版本：       1.0
--------------------------------------------------------------------------
	修改记录:
	日  期		版本		修改人		走读人    修改内容
	2004/4/8	1.0			朱允荣                  创建

*********************************************************************/


#include "stdafx.h"
#include "UILIbHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MINTHUMB 12  //滚动条中滑块的最小长度。

COLORREF CSkinScroll::m_s_crArrowFk      = RGB(80, 114, 170);
COLORREF CSkinScroll::m_s_crArrowBk      = RGB(234, 236, 239);
COLORREF CSkinScroll::m_s_crThumbBk      = RGB(234, 236, 239);
COLORREF CSkinScroll::m_s_crThumbFrame   = RGB(80, 114, 170);
COLORREF CSkinScroll::m_s_crChannelBk[2] = {RGB(241, 242, 244), -1};

/////////////////////////////////////////////////////////////////////////////
// CSkinScroll

CSkinScroll::CSkinScroll()
{
    m_nLineWidth = 6;
    m_nScrollStyle = SB_VERT;
    m_pCtrl = NULL;
    m_nItemMetric = 1;

    m_bLeftUp = FALSE;
    m_bRightDown = FALSE;
    m_bMouseDown = FALSE;
    m_bRightDownPage = FALSE;
    m_bLeftUpPage = FALSE;

    m_nThumbMetric = MINTHUMB;
    
    m_crArrowFk = m_s_crArrowFk;
    m_crArrowBk = m_s_crArrowBk;
    m_crThumbBk = m_s_crThumbBk;
    m_crThumbFrame = m_s_crThumbFrame;
    m_crChannelBk[0] = m_s_crChannelBk[0];
    m_crChannelBk[1] = m_s_crChannelBk[1];
    m_bOldShow = TRUE;
    m_bOnce = FALSE;
    m_bShowAllways = FALSE;
    m_nOldMax = -1;
    m_bShow3D = FALSE;
}

CSkinScroll::~CSkinScroll()
{
}


BEGIN_MESSAGE_MAP(CSkinScroll, CStatic)
	//{{AFX_MSG_MAP(CSkinScroll)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
    ON_WM_SIZE()
    ON_WM_SIZING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinScroll message handlers

void CSkinScroll::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages
    CRect rcRect;
    GetClientRect(rcRect);

    DrawArrow(&dc, 0, rcRect);
    DrawThumb();

}

void CSkinScroll::DrawArrow(CDC* pDC,int nStyle, CRect rect)
{
    pDC->FillRect(m_rcFirstArrow, &CBrush(m_crArrowBk));
    pDC->FrameRect(m_rcFirstArrow, &CBrush(m_crThumbFrame));
	

    pDC->FillRect(m_rcLastArrow, &CBrush(m_crArrowBk));
    pDC->FrameRect(m_rcLastArrow, &CBrush(m_crThumbFrame));
	
	if (m_bShow3D)
	{		
		pDC->DrawEdge(m_rcFirstArrow,EDGE_RAISED,BF_RECT);
		pDC->DrawEdge(m_rcLastArrow,EDGE_RAISED,BF_RECT);
	}
	
    CRgn rgnFirst, rgnLast;
    CreateArrowRgn(rgnFirst, rgnLast);
    pDC->FillRgn(&rgnFirst, &CBrush(m_crArrowFk));
    pDC->FillRgn(&rgnLast, &CBrush(m_crArrowFk));
}

void CSkinScroll::DrawThumb()
{
    CClientDC dc(this);

    if (m_crChannelBk[1] == -1)
    {
        dc.FillRect(m_rcChannel, &CBrush(m_crChannelBk[0]));
    }
    else
    {
        UINT nWay = (m_nScrollStyle == SB_VERT) ? CUITools::STEPBK_VERT : CUITools::STEPBK_HORZ;
        CUITools::DrawStepBk(&dc, m_crChannelBk[0], m_crChannelBk[1], m_rcChannel, m_rcChannel, nWay);
    }
    
    if (m_bLeftUpPage)
    {
        CRect rect;
        rect = m_rcChannel;
        if (m_nScrollStyle == SB_VERT)
        {
            rect.bottom = m_rcThumb.top;
        }
        else
        {
            rect.right = m_rcThumb.left;
        }
        dc.FillRect(rect, &CBrush(RGB(0,0,0)));
    }
    else if (m_bRightDownPage)
    {
        CRect rect;
        rect = m_rcChannel;
        if (m_nScrollStyle == SB_VERT)
        {
            rect.top = m_rcThumb.bottom;
        }
        else
        {
            rect.left = m_rcThumb.right;
        }
        dc.FillRect(rect, &CBrush(RGB(0,0,0)));
    }
    dc.FillRect(m_rcThumb, &CBrush(m_crThumbBk));
    dc.FrameRect(m_rcThumb, &CBrush(m_crThumbFrame));

	if (m_bShow3D)
	{
		dc.DrawEdge(m_rcThumb,EDGE_RAISED,BF_RECT);
	}	
}

void CSkinScroll::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    CStatic::OnMouseMove(nFlags, point);
	CRect rcClient;
    GetClientRect(rcClient);
    
    if (!m_bMouseDown)
    {
        return;
    }

    double dV;
    double dLength = m_nLenth - m_nThumbMetric;
    if (m_nScrollStyle == SB_VERT)
    {
        m_rcThumb.top = point.y - m_nPointInThumb;
        m_rcThumb.bottom = m_rcThumb.top + m_nThumbMetric;
        dV = double(m_rcThumb.top-m_rcFirstArrow.bottom) / dLength;
    }
    else
    {
        m_rcThumb.left = point.x - m_nPointInThumb;
        m_rcThumb.right = m_rcThumb.left + m_nThumbMetric;
        dV = double(m_rcThumb.left-m_rcFirstArrow.right) / dLength;
    }
//    UpdateThumbPosition();
    double dbMax = m_pCtrl->GetScrollLimit(m_nScrollStyle);

    int nPos = m_pCtrl->GetScrollPos(m_nScrollStyle); 
    int nScrollTimes = int(dbMax * dV) - nPos;
   SCROLLINFO sf;
    sf.cbSize = sizeof(sf);
    sf.fMask = SIF_PAGE;
    m_pCtrl->GetScrollInfo(m_nScrollStyle, &sf);
    if (sf.nPage <= 0) 
    {
        return;
    }
    LimitThumbPosition();

     if (m_nScrollStyle != SB_VERT) {
         if (m_pCtrl->IsKindOf(RUNTIME_CLASS(CListCtrl))) 
         {
              CListCtrl* pList = (CListCtrl*)m_pCtrl;
              pList->Scroll(CSize(nScrollTimes, 0));
              return;
         }
          nScrollTimes /= 6;
      }
    
    if (nScrollTimes > 0)
    {
        if (nScrollTimes >= (int)sf.nPage) 
        {
            SendScrollMessage(SB_PAGEDOWN, nScrollTimes/sf.nPage);
            SendScrollMessage(SB_LINERIGHT, nScrollTimes % sf.nPage);
        }
        else
        {
            SendScrollMessage(SB_LINERIGHT, nScrollTimes);
        }
    }
    else
    {
        int nTemp = -1 * nScrollTimes;
        if (nTemp >= (int)sf.nPage) 
        {
            SendScrollMessage(SB_PAGEUP, nTemp/sf.nPage);
            SendScrollMessage(SB_LINEUP, nTemp % sf.nPage);
        }
        else
        {
            SendScrollMessage(SB_LINEUP, nTemp);
        }
    }
}

void CSkinScroll::UpdateThumbPosition()
{
    double dLength;
    double dPos = m_pCtrl->GetScrollPos(m_nScrollStyle);
    double dMax = m_pCtrl->GetScrollLimit(m_nScrollStyle);
    dLength = m_nLenth - m_nThumbMetric;
    double dNewPos = dPos * dLength / dMax;

    if (m_nScrollStyle == SB_VERT)
    {
        m_rcThumb.top = m_rcFirstArrow.bottom + int(dNewPos);
        m_rcThumb.bottom = m_rcThumb.top + m_nThumbMetric;
    }
    else
    {
        m_rcThumb.left = m_rcFirstArrow.right + int(dNewPos);
        m_rcThumb.right = m_rcThumb.left + m_nThumbMetric;
    }

	LimitThumbPosition();
}

void CSkinScroll::LimitThumbPosition()
{
    if (m_nScrollStyle == SB_VERT)
    {
        if (m_rcThumb.bottom > m_rcLastArrow.top)
        {
            m_rcThumb.OffsetRect(CPoint(0, m_rcLastArrow.top-m_rcThumb.bottom));
        }
        else if (m_rcThumb.top < m_rcFirstArrow.bottom)
        {
            m_rcThumb.OffsetRect(CPoint(0, m_rcFirstArrow.bottom-m_rcThumb.top));
        }
    }
    else
    {
        if (m_rcThumb.right > m_rcLastArrow.left)
        {
            m_rcThumb.OffsetRect(CPoint( m_rcLastArrow.left-m_rcThumb.right,0));
        }
        else if (m_rcThumb.left < m_rcFirstArrow.right)
        {
            m_rcThumb.OffsetRect(CPoint(m_rcFirstArrow.right-m_rcThumb.left,0));
        }
    }

    if (m_bLeftUpPage || m_bRightDownPage)
    {
        CPoint pos;
        GetCursorPos(&pos);
        ScreenToClient(&pos);
        if (m_rcThumb.PtInRect(pos))
        {
            KillTimer(3);
            KillTimer(4);
            m_bLeftUpPage = false;
            m_bRightDownPage = false;
            UpdateThumbPosition();
            return;
        }
    }
        DrawThumb();
}

void CSkinScroll::SendScrollMessage(UINT nMessageType, int nTime)
{
    for (int i = 0 ; i < nTime; i++)
    {
        if (m_nScrollStyle == SB_VERT)
        {
            m_pCtrl->PostMessage(WM_VSCROLL, MAKELONG(nMessageType,0),NULL);
        }
        else
        {
            m_pCtrl->PostMessage(WM_HSCROLL, MAKELONG(nMessageType,0),NULL);
        }
//	UpdateThumbPosition();
    }
}

void CSkinScroll::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    switch(nIDEvent) {
    case 1:
		if(m_bRightDown)
		{
			SendScrollMessage(SB_LINEDOWN);
		}
        else if(m_bLeftUp)
		{
			SendScrollMessage(SB_LINEUP);
		}
        UpdateThumbPosition();
    	break;
    case 2:
		KillTimer(2);
		SetTimer(1, 50, NULL);
        break;
    case 3:
        UpdateThumbPosition();
        if (m_bRightDownPage)
        {
		    SendScrollMessage(SB_PAGEDOWN);
            UpdateThumbPosition();
        }
        break;
    case 4:
        UpdateThumbPosition();
        if (m_bLeftUpPage)
        {
		    SendScrollMessage(SB_PAGEUP);
            UpdateThumbPosition();
        }
    	break;
    default:
        break;
    }
	CStatic::OnTimer(nIDEvent);
}

void CSkinScroll::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	bool bInChannel = true;
	if(m_rcThumb.PtInRect(point))
	{
        if (m_nScrollStyle==SB_VERT)
        {
            m_nPointInThumb = point.y - m_rcThumb.top;
        }
        else
        {
            m_nPointInThumb = point.x - m_rcThumb.left;
        }
		m_bMouseDown = true;
        bInChannel = false;
	}

	if(m_rcLastArrow.PtInRect(point))
	{
		m_bRightDown = true;
		SetTimer(2,250,NULL);
        bInChannel = false;
	}

	if(m_rcFirstArrow.PtInRect(point))
	{
		m_bLeftUp = true;
		SetTimer(2,250,NULL);
        bInChannel = false;
	}
    
    BOOL bLine = (m_nScrollStyle == SB_VERT) ? (point.y > m_rcThumb.top) : (point.x > m_rcThumb.left);
	if(bInChannel && !m_bMouseDown)
	{
		if(bLine)
		{
    		m_bRightDownPage = true;
            SetTimer(3, 50, NULL);
		}
		else
		{
    		m_bLeftUpPage = true;
            SetTimer(4, 50, NULL);
		}
        bInChannel = false;
	}

	CStatic::OnLButtonDown(nFlags, point);
}

void CSkinScroll::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
    KillTimer(3);
    KillTimer(4);
	ReleaseCapture();
	UpdateThumbPosition();
	

	bool bInChannel = true;


	if(m_rcFirstArrow.PtInRect(point) && m_bLeftUp)
	{
		SendScrollMessage(SB_LINEUP);
		bInChannel = false;
	}

	if(m_rcLastArrow.PtInRect(point) && m_bRightDown)
	{
		SendScrollMessage(SB_LINEDOWN);
		bInChannel = false;
	}

	if(m_rcThumb.PtInRect(point))
	{
		bInChannel = false;
	}

	m_bMouseDown = false;
//	bDragging = false;
	m_bLeftUp = false;
	m_bRightDown = false;
    m_bLeftUpPage = false;
    m_bRightDownPage = false;
    UpdateThumbPosition();
	CStatic::OnLButtonUp(nFlags, point);
}


BOOL CSkinScroll::InitScrollBar(CWnd *pCtrl, UINT nStyle)
{
    if (pCtrl == NULL) 
    {
        return FALSE;
    }
    CRect rect;
    m_pCtrl = pCtrl;
    CWnd* pParent = pCtrl->GetParent();

    int nx, ny;
    if (nStyle == SB_VERT) 
    {
        nx = GetSystemMetrics(SM_CXVSCROLL);
        ny = GetSystemMetrics(SM_CYVSCROLL);
    }
    else
    {
        nx = GetSystemMetrics(SM_CXHSCROLL);
        ny = GetSystemMetrics(SM_CYHSCROLL);
    }

    m_nScrollStyle = nStyle;
    pCtrl->GetWindowRect(rect);
    pParent->ScreenToClient(rect);
    CRect rcTemp(rect);
    
    if (nStyle == SB_VERT) 
    {
        rect.left = rect.right- nx;
        rcTemp.right = rect.left;

    }
    else
    {
        rect.top = rect.bottom - ny;
        rcTemp.bottom = rect.top;
    }

    m_rcFirstArrow.SetRect(0, 0, nx, ny);
    BOOL bVRev = Create(NULL, WS_CHILD|SS_LEFT|SS_NOTIFY|WS_VISIBLE|WS_GROUP, rect, pParent);
    if (!bVRev)
    {
        return FALSE;
    }
    pCtrl->SetWindowPos(NULL,rcTemp.left,rcTemp.top,rcTemp.Width(),rcTemp.Height(),SWP_NOZORDER);
    
    UpdateRect();

    UpdateThumbPosition();
    return TRUE;
}

void CSkinScroll::CreateArrowRgn(CRgn &rgnFirst, CRgn &rgnLast)
{
    CPoint p1[3];
    CPoint p2[3];
    if (m_nScrollStyle == SB_VERT)
    {
        int nx = m_rcFirstArrow.Width() / 4;
        int ny = m_rcFirstArrow.Height() / 3;
        p1[0].x = p2[0].x = nx;
        p1[1].x = p2[1].x = 3 * nx;
        p1[2].x = p2[2].x = 2 * nx;

        p1[2].y = ny;
        p1[0].y = p1[1].y = 2 * ny;

        p2[0].y = p2[1].y = ny + m_rcLastArrow.top; 
        p2[2].y =  ny + p2[0].y;
    }
    else
    {
        int nx = m_rcFirstArrow.Width() / 3;
        int ny = m_rcLastArrow.Height() / 4;
                
        p1[0].y = p2[0].y = ny;
        p1[1].y = p2[1].y = 3 * ny;
        p1[2].y = p2[2].y = 2 * ny;

        p1[2].x = nx;
        p1[0].x = p1[1].x = 2 * nx;

        p2[0].x = p2[1].x = nx + m_rcLastArrow.left; 
        p2[2].x = nx + p2[0].x;
    }
    
    rgnFirst.CreatePolygonRgn(p1, 3, WINDING);
    rgnLast.CreatePolygonRgn(p2, 3, WINDING);
}

void CSkinScroll::SetArrowColor(COLORREF crFk, COLORREF crBk, BOOL bRepaint)
{
    m_crArrowFk = crFk;
    m_crArrowBk = crBk;

    if (bRepaint)
    {
        Invalidate();
    }
}

void CSkinScroll::SetThumbColor(COLORREF crBk, COLORREF crFrame, BOOL bRepaint)
{
    m_crThumbBk = crBk;
    m_crThumbFrame = crFrame;
    if (bRepaint)
    {
        Invalidate();
    }
}

void CSkinScroll::SetChannelBk(COLORREF crBkFrom, COLORREF crBkTo, BOOL bRepaint)
{
   m_crChannelBk[0] = crBkFrom;
   m_crChannelBk[1] = crBkTo;
    if (bRepaint)
    {
        Invalidate();
    }
}

BOOL CSkinScroll::UpdateThumbSize()
{
    if (m_pCtrl == NULL)
    {
        return FALSE;
    }

    int dMax = m_pCtrl->GetScrollLimit(m_nScrollStyle);

    if (dMax == m_nOldMax)
    {
        return GetOldShowState();
    }
    else
    {
        m_nOldMax = dMax;
    }
    if (dMax < 1)
    {
        m_nThumbMetric = m_nLenth;
        ShowScroll(m_bShowAllways);
        return m_bShowAllways;
    }
    SCROLLINFO sf;
    sf.cbSize = sizeof(sf);
    sf.fMask = SIF_ALL;
    m_pCtrl->GetScrollInfo(m_nScrollStyle, &sf);
    if (sf.nPage == 0)
    {
        m_nThumbMetric = m_nLenth;
        ShowScroll(m_bShowAllways);
        return m_bShowAllways;
    }
    
    ShowScroll(TRUE);
    m_nThumbMetric = (int) min(max((UINT)m_nLenth * sf.nPage / sf.nMax, (UINT)MINTHUMB), (UINT)m_nLenth);
    UpdateThumbPosition();
    return TRUE;
}

void CSkinScroll::ShowScroll(BOOL bShow, BOOL bShowOld)
{  
    if (bShow == m_bOldShow && !bShowOld)
    {
        return;
    }
    m_bOldShow = bShow;

    int Style = SW_HIDE;
    if (bShow)
    {
        Style = SW_SHOW;
    }

    CRect rcNew;
    m_pCtrl->GetWindowRect(rcNew);
    GetParent()->ScreenToClient(rcNew);

    if (m_nScrollStyle == SB_VERT)
    {
        if (bShow)
        {
            rcNew.right -= m_rcChannel.Width();
        }
        else
        {
            rcNew.right += m_rcChannel.Width();
        }
    }
    else
    {
        if (bShow)
        {
            rcNew.bottom -= m_rcChannel.Height();
        }
        else
        {
            rcNew.bottom += m_rcChannel.Height();
        }
    }
    ShowWindow(Style);
    m_pCtrl->SetWindowPos(NULL, rcNew.left, rcNew.top, rcNew.Width(), rcNew.Height(), SWP_NOZORDER);
}


void CSkinScroll::UpdateRect()
{
    GetClientRect(m_rcChannel);
    m_rcLastArrow = m_rcChannel;
    int nx, ny;
  

    if (m_nScrollStyle == SB_VERT) 
    {
        ny = GetSystemMetrics(SM_CYVSCROLL);
        m_rcLastArrow.top = m_rcLastArrow.bottom - ny;
        m_rcChannel.top = m_rcFirstArrow.bottom;
        m_rcChannel.bottom = m_rcLastArrow.top;
        m_nLenth = m_rcChannel.Height();
        m_rcThumb.left = m_rcChannel.left;
        m_rcThumb.right = m_rcChannel.right;
    }
    else
    {
        nx = GetSystemMetrics(SM_CXHSCROLL);
        m_rcLastArrow.left = m_rcLastArrow.right - nx;
        m_rcChannel.left = m_rcFirstArrow.right;
        m_rcChannel.right = m_rcLastArrow.left;
        m_nLenth = m_rcChannel.Width();
        m_rcThumb.top = m_rcChannel.top;
        m_rcThumb.bottom = m_rcChannel.bottom;
    }
}

BOOL CSkinScroll::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_LBUTTONDBLCLK)
    {
        pMsg->message = WM_LBUTTONDOWN;
    }

	return CStatic::PreTranslateMessage(pMsg);
}

void CSkinScroll::SetShowAllways(BOOL bAllWays)
{
    m_bShowAllways = bAllWays;
}

BOOL CSkinScroll::IsStopPage()
{
    CPoint pos;
    GetCursorPos(&pos);
    ScreenToClient(&pos);
    if (m_rcThumb.PtInRect(pos))
    {
        KillTimer(3);
        KillTimer(4);
        m_bLeftUpPage = FALSE;
        m_bRightDownPage = FALSE;
        UpdateThumbPosition();
        return TRUE;
    }

    return FALSE;
}

UINT CSkinScroll::GetOldShowState()
{
    return m_bOldShow ? SW_SHOW : SW_HIDE;
}

void CSkinScroll::ReInit()
{
    m_nLineWidth = 6;
    m_nScrollStyle = SB_VERT;
    m_pCtrl = NULL;
    m_nItemMetric = 1;

    m_bLeftUp = FALSE;
    m_bRightDown = FALSE;
    m_bMouseDown = FALSE;
    m_bRightDownPage = FALSE;
    m_bLeftUpPage = FALSE;

    m_nThumbMetric = MINTHUMB;
    m_bOldShow = TRUE;
    m_bOnce = FALSE;
    m_bShowAllways = FALSE;
    m_nOldMax = -1;
    
    m_crChannelBk[1] = -1;
}


/*=============================================================================
函 数 名： StaticSetArrowColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crFk
           COLORREF crBk
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/28  1.0			朱允荣                  创建
=============================================================================*/
void CSkinScroll::StaticSetArrowColor(COLORREF crFk, COLORREF crBk)
{
    m_s_crArrowFk = crFk;
    m_s_crArrowBk = crBk;
}


/*=============================================================================
函 数 名： StaticSetChannelBk
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crBkFrom
           COLORREF crBkTo
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/28  3.6			朱允荣                  创建
=============================================================================*/
void CSkinScroll::StaticSetChannelBk(COLORREF crBkFrom, COLORREF crBkTo)
{
   m_s_crChannelBk[0] = crBkFrom;
   m_s_crChannelBk[1] = crBkTo;
}


/*=============================================================================
函 数 名： StaticSetThumbColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crBk
           COLORREF crFrame
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/28  3.6			朱允荣                  创建
=============================================================================*/
void CSkinScroll::StaticSetThumbColor(COLORREF crBk, COLORREF crFrame)
{
    m_s_crThumbBk = crBk;
    m_s_crThumbFrame = crFrame;
}

void CSkinScroll::Set3DShow(BOOL bShow3D)
{
	m_bShow3D=bShow3D;
}
