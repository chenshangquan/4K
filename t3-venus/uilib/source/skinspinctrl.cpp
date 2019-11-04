/********************************************************************
	模块名:      UILib
	文件名:      skinspinctrl.cpp
	相关文件:    UILibHead.h
	文件实现功能 
    作者：       朱允荣
	版本：       1.0
------------------------------------------------------------------------
	修改记录:
	日  期		版本		修改人		走读人    修改内容
	2004/05/10	1.0			朱允荣                  创建

*********************************************************************/

#include "stdafx.h"
#include "UILIbHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinSpinCtrl
COLORREF CSkinSpinCtrl::m_s_crFore[4] = {RGB(241, 242, 244), RGB(64, 91, 143),
                                        RGB(184, 221, 252), RGB(126, 150, 195)};
COLORREF CSkinSpinCtrl::m_s_crBk[4] = {RGB(105, 146, 214),
                                       // RGB(105, 146, 214),
                                        RGB(241, 242, 244),
                                        RGB(105, 146, 214), RGB(178, 198, 227)};

CSkinSpinCtrl::CSkinSpinCtrl()
{
    for (int i = 0; i < STAll; i++)
    {
        m_crFore[i] = m_s_crFore[i];
        m_crBk[i] = m_s_crBk[i];
    }

    m_nSpinAlign = Outside;
    m_bVertical = TRUE;
    m_bPressed = FALSE;

    m_nHotPos = -1;
    m_rcPressed.SetRectEmpty();
    m_nHotPos = NoHot;

    m_nMax = 0;
    m_nMin = 0;
    m_nPos = 0;
}

CSkinSpinCtrl::~CSkinSpinCtrl()
{
}


BEGIN_MESSAGE_MAP(CSkinSpinCtrl, CSpinButtonCtrl)
	//{{AFX_MSG_MAP(CSkinSpinCtrl)
	ON_WM_PAINT()
	ON_NOTIFY_REFLECT_EX(UDN_DELTAPOS, OnDeltapos)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinSpinCtrl message handlers

void CSkinSpinCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CSpinButtonCtrl::OnPaint() for painting messages
    GetClientRect(m_rcFirst);
    dc.FillRect(m_rcFirst, &CBrush(m_crBk[0]));

    m_rcLast = m_rcFirst;
    if (m_bVertical) 
    {
        m_rcFirst.bottom = m_rcFirst.bottom / 2;
        m_rcLast.top = m_rcFirst.bottom;
    }
    else
    {
        m_rcFirst.right /= 2;
        m_rcLast.left = m_rcFirst.right;
    }


    int nFirst = STNormal, nLast = STNormal;

    if (m_nHotPos == FirstHot)
    {
        nFirst = m_bPressed ? STPressed : STHilight;
    }
    else if (m_nHotPos == LastHot)
    {
        nLast = m_bPressed ? STPressed : STHilight;
    }
    
    if (m_nMax <= m_nPos)
    {
        nLast = STDisable;
    }
    else if (m_nMin >= m_nPos)
    {
        nFirst = STDisable;
    }

    CRgn rgnFirst, rgnLast;
    CreateArrowRgn(rgnFirst, rgnLast);
    m_rcFirst.DeflateRect(1,1);
    m_rcLast.DeflateRect(1,1);

    if (nFirst != STNormal)
    {
        dc.FillSolidRect(m_rcFirst, m_crBk[nFirst]);
    }
    if (nLast != STNormal)
    {
        dc.FillSolidRect(m_rcLast, m_crBk[nLast]);
    }

    dc.FillRgn(&rgnFirst, &CBrush(m_crFore[nFirst]));
    dc.FillRgn(&rgnLast, &CBrush(m_crFore[nLast]));
    m_bPressed = FALSE;

    rgnLast.DeleteObject();
    rgnFirst.DeleteObject();
}

LRESULT CSkinSpinCtrl::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) 
    {
    case UDM_SETPOS:
        {
            m_nPos = lParam;
        }
    	break;
    case UDM_SETRANGE:
        {
            m_nMin = wParam;
            m_nMax = lParam;
            Invalidate(TRUE);
        }
    	break;
    default:
    	break;
    }

    return CSpinButtonCtrl::DefWindowProc(message, wParam, lParam);
}


void CSkinSpinCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	DWORD dwStyle = GetStyle();

    if (dwStyle & UDS_ALIGNRIGHT) 
    {
        m_nSpinAlign = OnRightInside;
    }
    else if (dwStyle & UDS_ALIGNLEFT) 
    {
        m_nSpinAlign = OnLeftInside;
    }

    if (dwStyle & UDS_HORZ) 
    {
        m_bVertical = FALSE;
    }

	CSpinButtonCtrl::PreSubclassWindow();
}

void CSkinSpinCtrl::CreateArrowRgn(CRgn &rgnFirst, CRgn &rgnLast)
{
    CPoint p1[3];
    CPoint p2[3];
    if (m_bVertical)
    {
        int ny = min(4, m_rcFirst.Height() / 2);
        int nx = ny + ny;
        
        p1[0].x = p2[0].x = (m_rcFirst.right - nx) / 2;
        p1[1].x = p2[1].x = p1[0].x + nx;
        p1[2].x = p2[2].x = m_rcFirst.right / 2;

        p1[2].y = (m_rcFirst.bottom - ny) / 2 - 1;
        p1[0].y = p1[1].y = p1[2].y + ny + 1;

        p2[0].y = p2[1].y = p1[2].y + m_rcLast.top - m_rcFirst.top + 1; 
        p2[2].y =  ny + p2[0].y ;
        p2[0].x++;
    }
    else
    {
        int nx = m_rcFirst.Width() / 2 -2;
        int ny = nx + nx;
                
        p1[0].y = p2[0].y = (m_rcFirst.bottom - ny) / 2;
        p1[1].y = p2[1].y = p1[0].y + ny;
        p1[2].y = p2[2].y = m_rcFirst.bottom / 2;

        p1[2].x = (m_rcFirst.right - nx) / 2;
        p1[0].x = p1[1].x = p1[2].x + nx;

        p2[0].x = p2[1].x = p1[2].x + m_rcLast.left; 
        p2[2].x = nx + p2[0].x;
    }
    
    rgnFirst.CreatePolygonRgn(p1, 3, WINDING);
    rgnLast.CreatePolygonRgn(p2, 3, WINDING);
}

BOOL CSkinSpinCtrl::OnDeltapos(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
    if (pNMUpDown->iDelta != 0) 
    {
        m_bPressed = TRUE;
    }
	*pResult = 0;
    return FALSE;
}

void CSkinSpinCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
    UpdateWindow();
	CSpinButtonCtrl::OnLButtonUp(nFlags, point);
    //顾振华@2006.01.12
    m_nPos = LOWORD(GetPos());
}

void CSkinSpinCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int nHot;
    if (m_rcFirst.PtInRect(point)) 
    {
        nHot = FirstHot;
        m_rcPressed = m_rcFirst;
        m_rcPressed.DeflateRect(1,1);

    }
    else if (m_rcLast.PtInRect(point)) 
    {
        nHot = LastHot;
        m_rcPressed = m_rcLast;
        m_rcPressed.DeflateRect(1,1);
    }
    else
    {
        nHot = NoHot;
        m_rcPressed.SetRectEmpty();
    }

    if (nHot != m_nHotPos) 
    {
        if (m_nHotPos == NoHot) 
        {            
	        TRACKMOUSEEVENT		csTME;
            csTME.cbSize = sizeof(csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = m_hWnd;
			::_TrackMouseEvent(&csTME);
        }
        m_nHotPos = nHot;
        Invalidate();
    }
	CSpinButtonCtrl::OnMouseMove(nFlags, point);
}

LRESULT CSkinSpinCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_nHotPos = NoHot;
    m_rcPressed.SetRectEmpty();
    Invalidate();
	return 0;
} 
//接口

/*====================================================================
函数名	：    SetBkColor
功能		：设定按钮的背景色
算法实现	：（可选项）
引用全局变量：无
输入参数说明：COLORREF crBk:正常状态下的颜色
              COLORREF crPressed：下压时的颜色
              COLORREF crHilight：在鼠标下时的颜色
              BOOL bRepaint：是否马上重画
返回值说明：  无
----------------------------------------------------------------------
修改记录:
日  期		版本		修改人		走读人    修改内容
2004/05/10				朱允荣                  创建
====================================================================*/
void CSkinSpinCtrl::SetBkColor(COLORREF crBk, COLORREF crPressed, COLORREF crHilight, BOOL bRepaint)
{
    m_crBk[0] = crBk;
    m_crBk[1] = crPressed;
    if (crHilight == -1) 
    {
        m_crBk[2] = crBk;
    }
    else
    {
        m_crBk[2] = crHilight;
    }

    if (bRepaint) 
    {
        Invalidate();
    }
}


/*====================================================================
函数名	：    SetForeColor
功能		：设定按钮的前景色（三角）
算法实现	：（可选项）
引用全局变量：无
输入参数说明：COLORREF crFore:正常状态下的颜色
              COLORREF crPressed：下压时的颜色
              COLORREF crHilight：在鼠标下时的颜色
              BOOL bRepaint：是否马上重画
返回值说明：  无
----------------------------------------------------------------------
修改记录:
日  期		版本		修改人		走读人    修改内容
2004/05/10				朱允荣                  创建
====================================================================*/
void CSkinSpinCtrl::SetForeColor(COLORREF crFore, COLORREF crPressed, COLORREF crHilight, BOOL bRepaint)
{
    m_crFore[0] = crFore;
    m_crFore[1] = crPressed;
    m_crFore[2] = crHilight;

    if (bRepaint) 
    {
        Invalidate();
    }
}


void CSkinSpinCtrl::staticSetBkColor(COLORREF crBk, COLORREF crPressed,
                                     COLORREF crHilight, COLORREF crDisable)
{
    m_s_crBk[STNormal] = crBk;
    m_s_crBk[STPressed] = crPressed;
    m_s_crBk[STHilight] = crHilight;
    m_s_crBk[STDisable] = crDisable;
}

void CSkinSpinCtrl::staticSetForeColor(COLORREF crFore, COLORREF crPressed,
                                       COLORREF crHilight, COLORREF crDisable)
{
    m_s_crFore[STNormal] = crFore;
    m_s_crFore[STPressed] = crPressed;
    m_s_crFore[STHilight] = crHilight;
    m_s_crFore[STDisable] = crDisable;
}


/*=============================================================================
函 数 名： SetDisableColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crFore
           COLORREF crBk
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/06/11  3.6			朱允荣                  创建
=============================================================================*/
void CSkinSpinCtrl::SetDisableColor(COLORREF crFore, COLORREF crBk)
{
    m_crFore[STDisable] = crFore;
    m_crBk[STDisable] = crBk;
}