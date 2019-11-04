/********************************************************************
	模块名:      UILib
	文件名:      skinipctrl.cpp
	相关文件:    UILibHead.h
	文件实现功能 
    作者：       朱允荣
	版本：       1.0
--------------------------------------------------------------------------------
	修改记录:
	日  期		版本		修改人		走读人    修改内容
	2004/4/8	1.0			朱允荣                 创建

*********************************************************************/

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinIPCtrl
UINT CSkinIPCtrl::m_s_nType = TYPE_NORMAL;
COLORREF CSkinIPCtrl::m_s_crBk[2] = {RGB(241, 242, 244), RGB(233,233,233)};
COLORREF CSkinIPCtrl::m_s_crText[2] = {RGB(80, 114, 170), RGB(80, 114, 170)};
COLORREF CSkinIPCtrl::m_s_crFrame = RGB(80, 114, 170);

CSkinIPCtrl::CSkinIPCtrl()
{
    if (m_s_nType == TYPE_NORMAL) 
    {
        m_crBk[0] = m_s_crBk[0];
        m_crBk[1] = m_s_crBk[1];

        m_crText[0] = m_s_crText[0];
        m_crText[1] = m_s_crText[1];
        m_crFrame = m_s_crFrame;
    }
    else
    {
        m_crBk[0] = RGB(0xeb, 0xf6, 0xe8);
        m_crBk[1] = RGB(0xeb, 0xf6, 0xe8);

        m_crText[0] = RGB(0, 0, 0);
        m_crText[1] = RGB(128, 128, 128);
        m_crFrame = RGB(0, 0, 0);
    }
    m_brushBk[0].CreateSolidBrush(m_crBk[0]);
    m_brushBk[1].CreateSolidBrush(m_crBk[1]);

}

CSkinIPCtrl::~CSkinIPCtrl()
{
    m_brushBk[0].DeleteObject();
    m_brushBk[1].DeleteObject();
}


BEGIN_MESSAGE_MAP(CSkinIPCtrl, CIPAddressCtrl)
	//{{AFX_MSG_MAP(CSkinIPCtrl)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_CTLCOLOR()
    ON_WM_PAINT()
	ON_WM_ENABLE()
    ON_WM_MOVE()
    ON_WM_SIZE()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinIPCtrl message handlers

HBRUSH CSkinIPCtrl::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	 
    if (IsWindowEnabled())
    {
        pDC->SetTextColor(m_crText[0]);
        pDC->SetBkColor(m_crBk[0]);
        return (HBRUSH)m_brushBk[0].m_hObject;
    }
    else
    {
        pDC->SetTextColor(m_crText[1]);
        pDC->SetBkColor(m_crBk[1]);
        return (HBRUSH)m_brushBk[1].m_hObject;
    }
	return NULL;
}

HBRUSH CSkinIPCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CIPAddressCtrl::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Change any attributes of the DC here
	 	 
    if (IsWindowEnabled())
    {
        pDC->SetTextColor(m_crText[0]);
        pDC->SetBkColor(m_crBk[0]);
        return (HBRUSH)m_brushBk[0].m_hObject;
    }
    else
    {
        pDC->SetTextColor(m_crText[1]);
        pDC->SetBkColor(m_crBk[1]);
        return (HBRUSH)m_brushBk[1].m_hObject;
    }
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSkinIPCtrl::PreSubclassWindow()
{
    CIPAddressCtrl::PreSubclassWindow();
    CRect rect;
    GetWindowRect(rect);
    rect.bottom -= 3;
    GetParent()->ScreenToClient(rect);
    MoveWindow(rect);
}
void CSkinIPCtrl::OnEnable(BOOL bEnable) 
{
	CIPAddressCtrl::OnEnable(bEnable);
	
	// TODO: Add your message handler code here
	Invalidate();
}

void CSkinIPCtrl::OnNcPaint() 
{
	// TODO: Add your message handler code here
	
	// Do not call CIPAddressCtrl::OnNcPaint() for painting messages

}

void CSkinIPCtrl::OnPaint() 
{
	// TODO: Add your message handler code here
	
	// Do not call CIPAddressCtrl::OnNcPaint() for painting messages
    CRect rcClient;
    GetClientRect(rcClient);

    int y = (rcClient.bottom+rcClient.top)/2;
    int x = rcClient.Width()/4;


    CPaintDC cdc(this);
    cdc.FillRect(rcClient, &m_brushBk[IsWindowEnabled() ? 0:1]);
    cdc.SetBkMode(TRANSPARENT);
    cdc.SetPixel(x, y, 0x0);
    cdc.SetPixel(2*x, y, 0x0);
    cdc.SetPixel(3*x, y, 0x0);
   

	CWindowDC dc(this);
    rcClient.InflateRect(0,0,4,4);
    dc.FrameRect(rcClient, &CBrush(m_crFrame));

}

void CSkinIPCtrl::OnMove(int x, int y)
{
    CIPAddressCtrl::OnMove(x, y);

    CRect rcIp;
    GetClientRect(rcIp);

    int nHeight = rcIp.Height();
    int nMatric = min(rcIp.Width() / 35 + 1, 3);
    int nWidth = (rcIp.Width() - nMatric * 8 - 2) / 4;
    int nLeft = rcIp.Width() / 4;

    HWND hChild = ::GetWindow(m_hWnd, GW_CHILD);

    for (int i = 3; i >= 0; i--)
    {
        if (NULL == hChild) 
        {
            return;
        }
        ::MoveWindow(hChild, i*nLeft+nMatric, 1, nWidth, nHeight, TRUE);
        hChild = ::GetWindow(hChild, GW_HWNDNEXT);

    }

}

void CSkinIPCtrl::OnSize(UINT nType, int cx, int cy)
{
    CIPAddressCtrl::OnSize(nType, cx, cy);
    
    int nHeight = cy;
    int nMatric = min(cx / 35 + 1, 3);
    int nWidth = (cx - nMatric * 8 - 2) / 4;
    int nLeft = cx / 4;

    HWND hChild = ::GetWindow(m_hWnd, GW_CHILD);

    for (int i = 3; i >= 0; i--)
    {
        if (NULL == hChild) 
        {
            return;
        }
        ::MoveWindow(hChild, i*nLeft+nMatric, 1, nWidth, nHeight, TRUE);
        hChild = ::GetWindow(hChild, GW_HWNDNEXT);
    }
}

void CSkinIPCtrl::SetBkColor(COLORREF crBk, COLORREF crDisable, BOOL bRepaint)
{
    m_crBk[0] = crBk;
    m_crBk[1] = crDisable;

    if (NULL != m_brushBk[0].m_hObject) 
    {
        m_brushBk[0].DeleteObject();
        m_brushBk[0].CreateSolidBrush(crBk);
    }

    if (NULL != m_brushBk[1].m_hObject) 
    {
        m_brushBk[1].DeleteObject();
        m_brushBk[1].CreateSolidBrush(crDisable);
    }

    if (bRepaint) 
    {
        Invalidate();
    }
}

void CSkinIPCtrl::SetTextColor(COLORREF crText, COLORREF crDisable, BOOL bRepaint)
{
    m_crText[0] = crText;

    if (bRepaint) 
    {
        Invalidate();
    }
}

void CSkinIPCtrl::SetFrameColor(COLORREF crFrame, BOOL bRepaint)
{
    m_crFrame = crFrame;

    if (bRepaint)
    {
        Invalidate();
    }
}


/*=============================================================================
函 数 名： staticSetBkColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crBk
           COLORREF crDisable
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  3.6			朱允荣                  创建
=============================================================================*/
void CSkinIPCtrl::staticSetBkColor(COLORREF crBk, COLORREF crDisable)
{
    m_s_crBk[0] = crBk;
    m_s_crBk[1] = crDisable;
}


/*=============================================================================
函 数 名： staticSetTextColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crText
           COLORREF crDisable
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  3.6			朱允荣                  创建
=============================================================================*/
void CSkinIPCtrl::staticSetTextColor(COLORREF crText, COLORREF crDisable)
{
    m_s_crText[0] = crText;
    m_s_crText[1] = crDisable;
}


/*=============================================================================
函 数 名： staticSetFrameColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crFrame
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  3.6			朱允荣                  创建
=============================================================================*/
void CSkinIPCtrl::staticSetFrameColor(COLORREF crFrame)
{
    m_s_crFrame = crFrame;
}
