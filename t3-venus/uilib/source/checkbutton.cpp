/********************************************************************
	模块名:      UILib
	文件名:      checkbutton.cpp
	相关文件:    UILibHead.h
	文件实现功能 
    作者：       朱允荣
	版本：       1.0
-----------------------------------------------------------------------
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
// CCheckButton

COLORREF CCheckButton::m_s_crFrame[2] = {RGB(80, 114, 170), RGB(80, 114, 170)};
COLORREF CCheckButton::m_s_crText[2]  = {RGB(80, 114, 170), -1};
COLORREF CCheckButton::m_s_crCheck[2] = {RGB(0,0,0),::GetSysColor(COLOR_3DSHADOW)};
COLORREF CCheckButton::m_s_crBk       = RGB(241, 242, 244);

CCheckButton::CCheckButton()
{
    //八种种状态时的图片句柄
    for (int i = 0; i < STATE_MAX; i++)
    {
        m_hBitmap[i] = NULL;
    }

    for (i = 0; i < 2; i++)
    {
        m_crFrame[i] = m_s_crFrame[i];
        m_crCheck[i] = m_s_crCheck[i];
        m_crText[i] = m_s_crText[i];
    }


    m_crBk = m_s_crBk;//::GetSysColor(COLOR_3DFACE);
    m_crFocus = RGB(0, 0, 0);

    m_bDisable = FALSE;
    m_bIsFocussed = FALSE;
    m_bMouseIn = FALSE;

    m_nFrameSize = 15;

    m_bChecked = FALSE;
    m_bTrans = FALSE;
    m_bDown = FALSE;

    //按钮和图片大小适应关系,默认按钮适应图片。
    m_bSizeToContent = FALSE;

    m_pbmpOldBk = NULL;
    m_dcBk.m_hDC = NULL;

    m_pParent = NULL;

    m_bNeedFree = FALSE;
}

CCheckButton::~CCheckButton()
{
    if (m_bNeedFree) 
    {
        FreeResource();
    }
    	// Restore old bitmap (if any)
    if (m_dcBk.m_hDC != NULL) 
    {
        if (m_pbmpOldBk != NULL)
        {
            ::SelectObject(m_dcBk.m_hDC,m_pbmpOldBk);
        }
        ::DeleteObject(m_dcBk.m_hDC);
    }
}


BEGIN_MESSAGE_MAP(CCheckButton, CButton)
	//{{AFX_MSG_MAP(CCheckButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_CXSHADE_RADIO , OnRadioInfo)
	ON_MESSAGE(BM_SETCHECK , OnBMSetCheck)
	ON_MESSAGE(BM_GETCHECK , OnBMGetCheck)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckButton message handlers

void CCheckButton::DrawItem(LPDRAWITEMSTRUCT lpDS) 
{
	// TODO: Add your code to draw the specified item
    CDC* pDC = CDC::FromHandle(lpDS->hDC);

    pDC->SetBkMode(TRANSPARENT);
    m_bDisable = (lpDS->itemState & ODS_DISABLED);
    m_bIsFocussed = (lpDS->itemState & ODS_FOCUS);
    m_bDown = (lpDS->itemState & ODS_SELECTED);

    CRect rcFull(lpDS->rcItem);
    CRect rcCheckFrame;
    //Draw background
    if (m_bTrans)
    {
        PaintBk(pDC);
    }
    else
    {
        pDC->FillRect(rcFull, &CBrush(m_crBk));
    }

    if (m_hBitmap[0] != NULL)
    {
        if (m_bSizeToContent)
        {
            GetClientRect(rcCheckFrame);
            DrawBitmap(pDC, rcCheckFrame);
            return;
        }
        rcCheckFrame.left = rcFull.left + 1;
        BITMAP bit;
        GetObject(m_hBitmap[0], sizeof(bit), &bit);
        rcCheckFrame.right = rcCheckFrame.left + bit.bmWidth;
        rcCheckFrame.bottom = (rcFull.top + rcFull.bottom + bit.bmHeight) / 2;
        rcCheckFrame.top = rcCheckFrame.bottom - m_nFrameSize;
        DrawBitmap(pDC, rcCheckFrame);
    }
    else
    {
        rcCheckFrame.left = rcFull.left + 1;
        rcCheckFrame.right = rcCheckFrame.left + m_nFrameSize;
        rcCheckFrame.bottom = (rcFull.top + rcFull.bottom + m_nFrameSize) / 2;
        rcCheckFrame.top = rcCheckFrame.bottom - m_nFrameSize;
        DrawTextCheck(pDC, rcCheckFrame);
    }

    //Draw the text
    CRect rcText(rcFull);
    rcText.left = rcCheckFrame.right + 3;
 
    CString strText;
    GetWindowText(strText);

    if (m_bDisable)
    {
        if (m_crText[1] == (DWORD)-1)
        {
            rcText.OffsetRect(1,1);
            pDC->SetTextColor(RGB(255,255,255));
            pDC->DrawText(strText, rcText, DT_VCENTER|DT_LEFT|DT_SINGLELINE);
            rcText.OffsetRect(-1,-1);
            pDC->SetTextColor(RGB(128,128,128));
        }
        else
        {
             pDC->SetTextColor(m_crText[1]);
        }
    }
    else
    {
        pDC->SetTextColor(m_crText[0]);
    }
    pDC->DrawText(strText, rcText, DT_VCENTER|DT_LEFT|DT_SINGLELINE);

}

BOOL CCheckButton::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}

void CCheckButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_Style=GetButtonStyle();	///get specific BS_ styles
	if ((m_Style & BS_AUTOCHECKBOX)==BS_AUTOCHECKBOX)
//		||((m_Style & BS_CHECKBOX)==BS_CHECKBOX))
    {
		m_Style=BS_CHECKBOX;
    }
	else if ((m_Style & BS_AUTORADIOBUTTON)==BS_AUTORADIOBUTTON)
//			||((m_Style & BS_RADIOBUTTON)==BS_RADIOBUTTON))
    {
        m_Style=BS_RADIOBUTTON;
    }
	else 
    {
       m_Style=BS_PUSHBUTTON; 
    }

	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}

void CCheckButton::CancelHover()
{
    if (m_bMouseIn)
    {
        m_bMouseIn = FALSE;
        Invalidate();
    }
}

void CCheckButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd*				wndUnderMouse = NULL;
	CWnd*				wndActive = this;
	CButton::OnMouseMove(nFlags, point);

    ClientToScreen(&point);
	wndUnderMouse = WindowFromPoint(point);

    if ((nFlags & MK_LBUTTON) && !m_bMouseIn)
    {
        return;
    }

    if (NULL == wndUnderMouse)
    {
        return;
    }

    if ((wndUnderMouse->m_hWnd == m_hWnd) && (wndActive != NULL))
    {
        if (!m_bMouseIn)
        {
            m_bMouseIn = TRUE;
            Invalidate();

	        TRACKMOUSEEVENT		csTME;
            csTME.cbSize = sizeof(csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = m_hWnd;
			::_TrackMouseEvent(&csTME);
        }
    }
    else
    {
        CancelHover();
    }
	
	CButton::OnMouseMove(nFlags, point);
}

LRESULT CCheckButton::OnMouseLeave(WPARAM, LPARAM)
{
    CancelHover();
	return 0;
}

void CCheckButton::DrawTextCheck(CDC* pDC, CRect rcCheckFrame)
{

    if (m_Style == BS_RADIOBUTTON)
    {
        CRgn rgn;
        rgn.CreateEllipticRgn(rcCheckFrame.left, rcCheckFrame.top, rcCheckFrame.right, rcCheckFrame.bottom);
        if (!m_bDisable)
        {
            pDC->FillRgn(&rgn, &CBrush(RGB(255,255,255)));
            pDC->FrameRgn(&rgn, &CBrush(m_crFrame[0]), 1, 1);
        }
        else
        {
            pDC->FrameRgn(&rgn, &CBrush(m_crFrame[1]), 1, 1);
        }
    }
    else
    {
            //Draw Frame
        rcCheckFrame.DeflateRect(1,1);
        if (!m_bDisable)
        {
            pDC->FillRect(rcCheckFrame, &CBrush(RGB(255,255,255)));
            pDC->FrameRect(rcCheckFrame, &CBrush(m_crFrame[0])); 
        }
        else
        {
            pDC->FrameRect(rcCheckFrame, &CBrush(m_crFrame[1])); 
        }
    }


    //Draw Check
    if (m_bChecked)
    {
        DrawCheck(pDC, rcCheckFrame, m_crCheck[m_bDisable? 1 : 0]);
    }
}

void CCheckButton::DrawCheck(CDC *pDC, CRect rect, COLORREF crCheck)
{
    rect.DeflateRect(2, 2);
    if (m_Style == BS_RADIOBUTTON)
    {
        CRgn rgn;
        rgn.CreateEllipticRgn(rect.left, rect.top, rect.right, rect.bottom);
        pDC->FillRgn(&rgn, &CBrush(crCheck));
        return;
    }

    CPen checkPen;
    CPen *pOldPen;

    int nSize = rect.Width()/2;
    checkPen.CreatePen(PS_SOLID , 2, crCheck);
    pOldPen = pDC->SelectObject(&checkPen);

    pDC->MoveTo(rect.left, rect.bottom - nSize);
    pDC->LineTo(rect.left + nSize, rect.bottom);
    pDC->LineTo(rect.right, rect.top);

    checkPen.DeleteObject();
    pDC->SelectObject(pOldPen);
}

void CCheckButton::PaintBk(CDC *pDC)
{
	CRect rect;
	GetClientRect(rect);

    if (NULL == m_pParent) 
    {
        m_pParent = GetParent();
    }

	if (m_dcBk.m_hDC == NULL)
	{
        CClientDC clDC(m_pParent);
	    CRect rect1;

	    GetWindowRect(rect1);
	    m_pParent->ScreenToClient(rect1);

		m_dcBk.CreateCompatibleDC(&clDC);
		m_bmpBk.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
	} // if

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
}

BOOL CCheckButton::OnClicked() 
{
	// TODO: Add your control notification handler code here
    if (m_Style == BS_RADIOBUTTON)
    {
        SetCheck(1);
    }
    else
    {
        SetCheck(m_bChecked ? 0 : 1);
    }
//	m_bChecked = !m_bChecked;
    Invalidate();
    return FALSE;
}

BOOL CCheckButton::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    InitTooltip();
	m_ToolTip.RelayEvent(pMsg);
    if (pMsg->message == WM_LBUTTONDBLCLK)
    {
        pMsg->message = WM_LBUTTONDOWN;
    }
	
	return CButton::PreTranslateMessage(pMsg);
}

LRESULT CCheckButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// 截取ToolTip所需的鼠标消息
	if (m_ToolTip.GetSafeHwnd () != NULL)
	{
		if (message == WM_LBUTTONDOWN ||
			message == WM_LBUTTONUP ||
			message == WM_MOUSEMOVE)
		{
			MSG msg;
			ZeroMemory(&msg, sizeof(MSG));
			msg.message = message;
			msg.hwnd = m_hWnd;
			msg.wParam = wParam;
			msg.lParam = lParam;
			GetCursorPos(&msg.pt);
			msg.time = 0;
			m_ToolTip.RelayEvent(&msg);
		}
	}
	
	return CButton::DefWindowProc(message, wParam, lParam);
}

LRESULT CCheckButton::OnBMSetCheck(WPARAM wparam, LPARAM)
{
	BOOL bChecked = (wparam != 0);

    if (bChecked && m_bChecked)
    {
        return 0;
    }
    else
    {
        m_bChecked = bChecked;
    }

    if (m_Style == BS_RADIOBUTTON && m_bChecked)
    {
		HWND hthis,hwnd2,hpwnd;
        HWND hFirstFindWnd = NULL;
		hpwnd = GetParent()->GetSafeHwnd(); //get button parent handle
		hwnd2 = hthis = GetSafeHwnd();      //get this button handle
		if ( hthis != NULL && hpwnd != NULL )
        {				//consistency check
			while ( true )
            {
                //  wanghao 2006/04/12 GetNextDlgGroupItem只能取Enable的控件, 
                //      如果此时有Disable的Radio, 则会造成死循环
                //scan the buttons within the group
				hwnd2=::GetNextDlgGroupItem(hpwnd,hwnd2,0);
				//until we reach again this button or finnished finding
				if ( (hwnd2 == hthis) || (hwnd2 == NULL)
                     || ( hFirstFindWnd != NULL && hFirstFindWnd == hwnd2 ) )
                {
                    break;
                }

                if ( hFirstFindWnd == NULL )
                {
                    hFirstFindWnd = hwnd2;
                }
				//post the uncheck message
                CButton* pRadio = (CButton*)FromHandle(hwnd2);
                if (NULL == pRadio)
                {
                    return 0;
                }
                if ( pRadio->IsWindowEnabled() )//&& pRadio->IsWindowVisible())
                {
                    pRadio->SetCheck(0);
                }
			}
		}
	}

	Invalidate();
	return 0;
}

LRESULT CCheckButton::OnBMGetCheck(WPARAM wparam, LPARAM)
{
   return m_bChecked; 
}	//returns the state for check & radio buttons

LRESULT CCheckButton::OnRadioInfo(WPARAM wparam, LPARAM)
{
	if (m_bChecked)
    {	//only checked buttons need to be unchecked
		m_bChecked = FALSE;
		Invalidate();
	}
	return 0;
}

void CCheckButton::DrawBitmap(CDC *pDC, CRect rcBit)
{
    int nIndex = (m_bChecked ? 0 : 1);
    
    CDC dcMem;
    dcMem.CreateCompatibleDC(pDC);

    if (m_bDisable)
    {
        if (m_hBitmap[nIndex+STATE_DISCHECK] == NULL)
        {
            dcMem.SelectObject(m_hBitmap[nIndex]);
            CDC dcDis;
            CBitmap BMP;
            dcDis.CreateCompatibleDC(pDC);

            BMP.CreateCompatibleBitmap(pDC,  rcBit.Width(), rcBit.Height());
            dcDis.SelectObject(BMP);
            dcDis.BitBlt(rcBit.left, rcBit.top, rcBit.Width(), rcBit.Height(), &dcMem, 0, 0, SRCCOPY);

            DeleteDC(dcDis);
            DeleteDC(dcMem);
            pDC->DrawState(rcBit.TopLeft(), rcBit.Size(), 
                &BMP , DST_BITMAP | DSS_DISABLED);
            return;
        }
        else
        {
            nIndex += STATE_DISCHECK;
        }
    }
    else if (m_bDown)
    {
        if (m_hBitmap[nIndex + STATE_DOWNCHECK] != NULL)
        {
            nIndex += STATE_DOWNCHECK;
        }
    }
    else if (m_bMouseIn)
    {
        if (m_hBitmap[nIndex + STATE_HOTCHECK] != NULL)
        {
            nIndex += STATE_HOTCHECK;
        }
    }

    dcMem.SelectObject(m_hBitmap[nIndex]);
    pDC->BitBlt(rcBit.left, rcBit.top, rcBit.Width(), rcBit.Height(), &dcMem, 0, 0, SRCCOPY);
    dcMem.DeleteDC();
}

//接口函数

/*====================================================================
函数名  ：SetBitmaps
功  能  ：设定按钮背景的颜色
全局变量：无
输入参数：hBMPCheck:         按钮有效且选中时，按钮Check图片的句柄。
          hBMPUncheck:       按钮有效且未选中时，按钮Check图片的句柄。
	      hBMPDisableCheck:  按钮失效且选中时，按钮Check图片的句柄。
	      hBMPDisableUncheck:按钮失效且未选中时，按钮Check图片的句柄。
	      hBMPHotCheck:  按钮在鼠标下且选中时，按钮Check图片的句柄。
	      hBMPHotUncheck:按钮在鼠标下且未选中时，按钮Check图片的句柄。
返回值  ：无
====================================================================*/
void CCheckButton::SetBitmaps(HBITMAP hBMPCheck, HBITMAP hBMPUncheck, 
                              HBITMAP hBMPDisableCheck, HBITMAP hBMPDisableUncheck,
                              HBITMAP hBMPHotCheck, HBITMAP hBMPHotUncheck,
                              HBITMAP hBMPDownCheck, HBITMAP hBMPDownUncheck)
{
    
    if (m_bNeedFree) 
    {
        FreeResource();
        m_bNeedFree = FALSE;
    }

    m_hBitmap[STATE_CHECK] = hBMPCheck;
    m_hBitmap[STATE_UNCHECK] = hBMPUncheck;
    m_hBitmap[STATE_DISCHECK] = hBMPDisableCheck;
    m_hBitmap[STATE_DISUNCHECK] = hBMPDisableUncheck;
    m_hBitmap[STATE_HOTCHECK] = hBMPHotCheck;
    m_hBitmap[STATE_HOTUNCHECK] = hBMPHotUncheck;
    m_hBitmap[STATE_DOWNCHECK] = hBMPDownCheck;
    m_hBitmap[STATE_DOWNUNCHECK] = hBMPDownUncheck;

    if (NULL != hBMPCheck)
    {        
        BITMAP csBMP;
        int nRetValue = ::GetObject(hBMPCheck, sizeof(csBMP), &csBMP);
        if (0 == nRetValue)
        {
            return;
        }
        m_sizeBitmap.cx = csBMP.bmWidth;
        m_sizeBitmap.cy = csBMP.bmHeight;
        CRect rect;
        GetWindowRect(rect);
        m_sizeButton = rect.Size();
        if (m_bSizeToContent)
        {
            SetWindowPos(NULL, -1, -1, csBMP.bmWidth, csBMP.bmHeight,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
        }
    }
}

/*====================================================================
函数名  ：SetBitmaps
功  能  ：设定按钮背景的颜色
全局变量：无
输入参数：nBMPCheck:         按钮有效且选中时，按钮Check图片的资源号。
          nBMPUncheck:       按钮有效且未选中时，按钮Check图片的资源号。
	      nBMPDisableCheck:  按钮失效且选中时，按钮Check图片的资源号。
	      nBMPDisableUncheck:按钮失效且未选中时，按钮Check图片的资源号。
	      nBMPHotCheck:  按钮在鼠标下且选中时，按钮Check图片的资源号。
	      nBMPHotUncheck:按钮在鼠标下且未选中时，按钮Check图片的资源号。
	      nBMPDownCheck:  鼠标按下且选中时，按钮Check图片的资源号。
	      nBMPDownUncheck:鼠标按下且未选中时，按钮Check图片的资源号。
返回值  ：无
====================================================================*/
void CCheckButton::SetBitmaps(UINT nBMPCheck, UINT nBMPUncheck, 
                              UINT nBMPDisableCheck, UINT nBMPDisableUncheck,
                              UINT nBMPHotCheck, UINT nBMPHotUncheck,
                              UINT nBMPDownCheck, UINT nBMPDownUncheck)
{
    if (0 == nBMPCheck)
    {
        m_hBitmap[STATE_CHECK] = NULL;
        return;
    }
    
        
    SetBitmaps(CUITools::CreateImage(nBMPCheck), CUITools::CreateImage(nBMPUncheck), 
        CUITools::CreateImage(nBMPDisableCheck), CUITools::CreateImage(nBMPDisableUncheck), 
        CUITools::CreateImage(nBMPHotCheck), CUITools::CreateImage(nBMPHotUncheck),
        CUITools::CreateImage(nBMPDownCheck), CUITools::CreateImage(nBMPDownUncheck));

    m_bNeedFree = TRUE;
}

/*====================================================================
函数名  ：SetFrameSize
功  能  ：设定Check框的大小
全局变量：无
输入参数：nSize:Check框的边长（或直径）默认为15。
返回值  ：无
====================================================================*/
void CCheckButton::SetFrameSize(int nSize)
{
    m_nFrameSize = nSize;
}

/*====================================================================
函数名  ：SetFrameColor
功  能  ：设定Check框的颜色
全局变量：无
输入参数：crFrame	按钮有效时，Check框的颜色。
	      crDisable	按钮失效时，Check框的颜色。
          bRepaint	参数值为TRUE时，按钮马上重画；参数值为FALSE时，按钮在下次刷新时重画。
返回值  ：无
====================================================================*/
void CCheckButton::SetFrameColor(COLORREF crFrame, COLORREF crDisable, BOOL bRepaint)
{
    m_crFrame[0] = crFrame;
    m_crFrame[1] = crDisable;
    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
函数名  ：SetTextColor
功  能  ：设定按钮背景的颜色
全局变量：无
输入参数：crText	按钮有效时，按钮文字的颜色。
	      crDisable	按钮失效时，按钮文字的颜色。
          bRepaint	参数值为TRUE时，按钮马上重画；参数值为FALSE时，按钮在下次刷新时重画。
返回值  ：无
====================================================================*/
void CCheckButton::SetTextColor(COLORREF crText, COLORREF crDisable, BOOL bRepaint)
{
    m_crText[0] = crText;
    m_crText[1] = crDisable;
    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
函数名  ：SetCheckColor
功  能  ：设定按钮选中标记的颜色（小勾或圆点）
全局变量：无
输入参数：crCheck	按钮有效时，选中标记的颜色。
	      crDisable	按钮失效时，选中标记的颜色。
          bRepaint	参数值为TRUE时，按钮马上重画；参数值为FALSE时，按钮在下次刷新时重画。
返回值  ：无
====================================================================*/
void CCheckButton::SetCheckColor(COLORREF crCheck, COLORREF crDisable, BOOL bRepaint)
{
    m_crCheck[0] = crCheck;
    m_crCheck[1] = crDisable;
    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
函数名  ：SetBkColor
功  能  ：设定按钮背景的颜色
全局变量：无
输入参数：crBk	按钮背景的颜色。
          bRepaint	参数值为TRUE时，按钮马上重画；参数值为FALSE时，按钮在下次刷新时重画。
返回值  ：无
====================================================================*/
void CCheckButton::SetBkColor(COLORREF crBk, BOOL bRepaint)
{
    m_crBk = crBk;
    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
函数名  ：SetBk
功  能  ：画父窗口的背景，比较安全的显示透明效果。
全局变量：无
输入参数：CDC* pDC	父窗口画背景的CDC指针。
返回值  ：无
====================================================================*/
void CCheckButton::SetBk(CDC *pDC)
{
    if (m_bTrans && (pDC != NULL))
    {
        // Restore old bitmap (if any)
        if (m_dcBk.m_hDC != NULL && m_pbmpOldBk != NULL)
        {
	        m_dcBk.SelectObject(m_pbmpOldBk);
        } // if

        m_bmpBk.DeleteObject();
        m_dcBk.DeleteDC();
        m_dcBk.m_hDC = NULL;
        m_pbmpOldBk = NULL;

        CRect rect;
        CRect rect1;

        GetClientRect(rect);

        GetWindowRect(rect1);
        GetParent()->ScreenToClient(rect1);

        m_dcBk.CreateCompatibleDC(pDC);
        m_bmpBk.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
        m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
        m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rect1.left, rect1.top, SRCCOPY);
	} // if
}

/*====================================================================
函数名  ：InitTooltip
功  能  ：初始化Tooltip变量
全局变量：无
输入参数：无
返回值  ：无
====================================================================*/
void CCheckButton::InitTooltip()
{
    if (NULL == m_ToolTip.m_hWnd)
    {
        m_ToolTip.Create(this);
        m_ToolTip.Activate(FALSE);
        m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
        m_ToolTip.SetDelayTime( TTDT_AUTOPOP, TOOLTIP_SHOWTIME );
    }
}

/*====================================================================
函数名  ：SetTooltipText
功  能  ：设置Tooltip文本
全局变量：无
输入参数：lpszText: 文本内容；
          bActivate:是否启动Tooltip功能。
返回值  ：无
====================================================================*/
void CCheckButton::SetTooltipText(LPCTSTR lpszText, BOOL bActivate)
{
    if (NULL == lpszText)
    {
        return;
    }

    InitTooltip();

    if (m_ToolTip.GetToolCount() == 0)
    {
        CRect rcBtn;
        GetClientRect(&rcBtn);
        m_ToolTip.AddTool(this, lpszText, rcBtn, 1);
    }

    m_ToolTip.UpdateTipText(lpszText, this, 1);
    m_ToolTip.Activate(bActivate);
}

/*====================================================================
函数名  ：SetTooltipText
功  能  ：设置Tooltip文本
全局变量：无
输入参数：nText: 文本内容在资源表里的ID号；
          bActivate:是否启动Tooltip功能。
返回值  ：无
====================================================================*/
void CCheckButton::SetTooltipText(UINT nText, BOOL bActivate)
{
    CString strText;
    strText.LoadString(nText);

    if (!strText.IsEmpty())
    {
        SetTooltipText(strText, bActivate);
    }
}

/*====================================================================
函数名  ：EnableTooltipText
功  能  ：开关Tooltip功能。
全局变量：无
输入参数：bActivate:是否启动Tooltip功能。
返回值  ：无
====================================================================*/
void CCheckButton::EnableTooltipText(BOOL bActivate)
{
    if (m_ToolTip.GetToolCount() == 0)
    {
        return;
    }

    m_ToolTip.Activate(bActivate);
}

/*====================================================================
函数名  ：SizeToContent
功  能  ：设定按钮和图片大小的适应关系。
全局变量：无
输入参数：bActivate:TRUE时按钮适应图片，FALSE图片适应按钮。
返回值  ：无
====================================================================*/
void CCheckButton::SizeToContent(BOOL bEnable)
{
    m_bSizeToContent = bEnable;

    if (NULL != m_hBitmap[0])
    {
        if (bEnable)
        {
            SetWindowPos(NULL, -1, -1, m_sizeBitmap.cx, m_sizeBitmap.cy,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
        }
        else
        {
            SetWindowPos(NULL, -1, -1, m_sizeButton.cx, m_sizeButton.cy,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
        }
    }
}

/*====================================================================
函数名  ：SetBkTrans
功  能  ：设定按钮是否透明。
全局变量：无
输入参数：bTrans:TRUE时按钮透明，背景取父窗口，FALSE按钮不透明。
返回值  ：无
====================================================================*/
void CCheckButton::SetBkTrans(BOOL bTrans)
{
    m_bTrans = bTrans;
}

/*====================================================================
函数名  ：SetBkParent
功  能  ：设定按钮的父窗口。
全局变量：无
输入参数：bTrans:TRUE时按钮透明，背景取父窗口，FALSE按钮不透明。
返回值  ：无
====================================================================*/
void CCheckButton::SetBkParent(CWnd *pParent)
{
    if (pParent != NULL) 
    {
        m_pParent = pParent;
    }
    else
    {
        m_pParent = GetParent();
    }
}

void CCheckButton::FreeResource()
{
    for (INT i = 0; i < STATE_MAX; i++)
    {
        if (NULL != m_hBitmap[i])
        {
            ::DeleteObject(m_hBitmap[i]);
            m_hBitmap[i] = NULL;
        }
    }
}



/*=============================================================================
函 数 名： staticSetBkColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crBk
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  1.0			朱允荣                  创建
=============================================================================*/
void CCheckButton::staticSetBkColor(COLORREF crBk)
{
    m_s_crBk = crBk;
}


/*=============================================================================
函 数 名： staticSetCheckColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crCheck
           COLORREF crDisable
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  1.0			朱允荣                  创建
=============================================================================*/
void CCheckButton::staticSetCheckColor(COLORREF crCheck, COLORREF crDisable)
{
    m_s_crCheck[0] = crCheck;
    m_s_crCheck[1] = crDisable;
}


/*=============================================================================
函 数 名： staticSetFrameColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crFrame
           COLORREF crDisable
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  1.0			朱允荣                  创建
=============================================================================*/
void CCheckButton::staticSetFrameColor(COLORREF crFrame, COLORREF crDisable)
{
    m_s_crFrame[0] = crFrame;
    m_s_crFrame[1] = crDisable;
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
2005/03/29  1.0			朱允荣                  创建
=============================================================================*/
void CCheckButton::staticSetTextColor(COLORREF crText, COLORREF crDisable /* = -1 */)
{
    m_s_crText[0] = crText;
    m_s_crText[1] = crDisable;
}