// ColorSelCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "uilibhead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void AFXAPI DDX_ColourPicker(CDataExchange *pDX, int nIDC, COLORREF& crColour)
{
    HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
    ASSERT (hWndCtrl != NULL); 
    if (pDX->m_pDlgWnd == NULL)
    {
        return;
    }
    
    if (pDX->m_bSaveAndValidate)
    {
        ::SendMessage(hWndCtrl, CSM_GETCOLOR, (WPARAM)&crColour, 0);
    }
    else // initializing
    {
        ::SendMessage(hWndCtrl, CSM_SETCOLOR, crColour, 0);
    }
}

const int g_ciArrowSizeX = 4;
const int g_ciArrowSizeY = 2;
/////////////////////////////////////////////////////////////////////////////
// CColorSelCtrl

CColorSelCtrl::CColorSelCtrl():
	m_crColor(CLR_DEFAULT),
	m_crDefault(::GetSysColor(COLOR_APPWORKSPACE)),
	m_strDefaultText(_T("自动")),
	m_strCustomText(_T("其他颜色...")),
	m_bPopupActive(FALSE),
    m_bMouseIn(FALSE),
    m_bDefautText(TRUE),
	m_bTrackSelection(TRUE)
{
    for (int i = 0; i < 4; i++)
    {
        m_hBitmap[i] = NULL;
    }

    m_crFrame     = RGB(86, 114, 171);
    m_crBackgroud = RGB(214, 233, 243);
}

CColorSelCtrl::~CColorSelCtrl()
{
    for (int i = 0; i < 4; i++)
    {
        if (NULL != m_hBitmap[i])
        {
            ::DeleteObject(m_hBitmap[i]);
            m_hBitmap[i] = NULL;
        }
    }
}


BEGIN_MESSAGE_MAP(CColorSelCtrl, CButton)
	//{{AFX_MSG_MAP(CColorSelCtrl)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
    ON_MESSAGE(CPN_SELENDOK,     OnSelEndOK)
    ON_MESSAGE(CPN_SELENDCANCEL, OnSelEndCancel)
    ON_MESSAGE(CPN_SELCHANGE,    OnSelChange)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorSelCtrl message handlers

LONG CColorSelCtrl::OnSelEndOK(UINT lParam, LONG /*wParam*/)
{
	m_bPopupActive = FALSE;

    COLORREF OldColor = m_crColor;
	
	Color = (COLORREF)lParam;

    CWnd *pParent = GetParent();

    if (pParent) 
	{
        pParent->SendMessage(CPN_CLOSEUP, lParam, (WPARAM) GetDlgCtrlID());
        pParent->SendMessage(CPN_SELENDOK, lParam, (WPARAM) GetDlgCtrlID());
    }

    if (OldColor != m_crColor)
        if (pParent) pParent->SendMessage(CPN_SELCHANGE, m_crColor, (WPARAM) GetDlgCtrlID());

    return TRUE;
}


LONG CColorSelCtrl::OnSelEndCancel(UINT lParam, LONG /*wParam*/)
{
	m_bPopupActive = FALSE;
	
	Color = (COLORREF)lParam;

    CWnd *pParent = GetParent();

    if (pParent) 
	{
        pParent->SendMessage(CPN_CLOSEUP, lParam, (WPARAM) GetDlgCtrlID());
        pParent->SendMessage(CPN_SELENDCANCEL, lParam, (WPARAM) GetDlgCtrlID());
    }

    return TRUE;
}


LONG CColorSelCtrl::OnSelChange(UINT lParam, LONG /*wParam*/)
{
    if (m_bTrackSelection) 
		Color = (COLORREF)lParam;

    CWnd *pParent = GetParent();

    if (pParent) pParent->SendMessage(CPN_SELCHANGE, lParam, (WPARAM) GetDlgCtrlID());

    return TRUE;
}

// Handler for WM_MOUSELEAVE
LRESULT CColorSelCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	CancelHover();
	return 0;
} 

BOOL CColorSelCtrl::OnClicked() 
{
	// TODO: Add your control notification handler code here
	m_bPopupActive = TRUE;

    CRect rDraw;
    GetWindowRect(rDraw);

    CString strDefault;
    CString strCustom;
    if (m_bDefautText)
    {
        strDefault = CColourPopup::m_s_bUserChinese ?
            _T("自动") : _T("Automatic");
        strCustom = CColourPopup::m_s_bUserChinese ?
            _T("其他颜色...") : _T("More Colours...");

        new CColourPopup(CPoint(rDraw.left, rDraw.bottom),		// Point to display popup
                         m_crColor,								// Selected colour
                         m_crDefault,
                         this,									// parent
                         strDefault,						// "Default" text area
                         strCustom);						// Custom Text
    }
    else
    {
        new CColourPopup(CPoint(rDraw.left, rDraw.bottom),		// Point to display popup
                         m_crColor,								// Selected colour
                         m_crDefault,
                         this,									// parent
                         m_strDefaultText,						// "Default" text area
                         m_strCustomText);						// Custom Text
    }

    CWnd *pParent = GetParent();

    if (pParent)
        pParent->SendMessage(CPN_DROPDOWN, (LPARAM)m_crColor, (WPARAM) GetDlgCtrlID());

    return TRUE;
}

int CColorSelCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CColorSelCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
    ModifyStyle(0, BS_OWNERDRAW);  
	CButton::PreSubclassWindow();
}

LRESULT CColorSelCtrl::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == CSM_GETCOLOR)
    {
        *((COLORREF*)(wParam)) = GetColor();
        return 0;
    }
    else if (message == CSM_SETCOLOR)
    {
        SetColor(wParam);
        return 0;
    }
    return CButton::DefWindowProc(message, wParam, lParam);
}

void CColorSelCtrl::CancelHover()
{
    if (m_bMouseIn)
    {
        m_bMouseIn = FALSE;
        Invalidate();
    }
}

void CColorSelCtrl::OnMouseMove(UINT nFlags, CPoint point) 
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
}

void CColorSelCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	ASSERT(lpDrawItemStruct);

	CDC*    pDC      = CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT    state    = lpDrawItemStruct->itemState;
    CRect   rDraw    = lpDrawItemStruct->rcItem;
	CRect	rArrow;

	if (m_bPopupActive)
		state |= ODS_SELECTED|ODS_FOCUS;

	UINT uFrameState = DFCS_BUTTONPUSH|DFCS_ADJUSTRECT;

	if (state & ODS_SELECTED)
		uFrameState |= DFCS_PUSHED;

	if (state & ODS_DISABLED)
		uFrameState |= DFCS_INACTIVE;
	
    pDC->FillSolidRect(rDraw, m_crBackgroud);
    pDC->FrameRect(&rDraw, &CBrush(m_crFrame));

    rDraw.DeflateRect(1,1);

		RECT rFocus = rDraw;


	rDraw.DeflateRect(::GetSystemMetrics(SM_CXEDGE)+1,
					  ::GetSystemMetrics(SM_CYEDGE)+1);

    HBITMAP hBitmap = NULL;
    if (m_hBitmap[0] != NULL)
    {
        if (state & ODS_DISABLED)
        {
            hBitmap = m_hBitmap[STATE_DISABLE];
        }
        else if (state & ODS_SELECTED)
        {
            hBitmap = m_hBitmap[STATE_DOWN];
        }
        else if (m_bMouseIn)
        {
            hBitmap = m_hBitmap[STATE_HILIGHT];
        }
        else
        {
            hBitmap = m_hBitmap[STATE_NORMAL];
        }
    }

    if (NULL == hBitmap)
    {
        
	    if (state & ODS_SELECTED)
		    rDraw.OffsetRect(1,1);
	    rArrow.left		= rDraw.right - g_ciArrowSizeX
            - ::GetSystemMetrics(SM_CXEDGE) /2;
	    rArrow.right	= rArrow.left + g_ciArrowSizeX;
	    rArrow.top		= (rDraw.bottom + rDraw.top)/2 - g_ciArrowSizeY / 2;
	    rArrow.bottom	= (rDraw.bottom + rDraw.top)/2 + g_ciArrowSizeY / 2;

	    DrawArrow(pDC,
			      &rArrow,
			      0,
			      (state & ODS_DISABLED) 
			      ? ::GetSysColor(COLOR_GRAYTEXT) 
			      : RGB(0,0,0));


	    rDraw.right = rArrow.left - ::GetSystemMetrics(SM_CXEDGE)/2;

	    pDC->DrawEdge(&rDraw,
				      EDGE_ETCHED,
				      BF_RIGHT);

	    rDraw.right -= (::GetSystemMetrics(SM_CXEDGE) * 2) + 1 ;
    }
    else
    {
        BITMAP bmp;
        GetObject(hBitmap, sizeof(BITMAP), &bmp);
        CDC dcMem;
        dcMem.CreateCompatibleDC(pDC);
        HBITMAP hOldBitmap = (HBITMAP)dcMem.SelectObject(hBitmap);

	    rArrow.left		= rDraw.right - bmp.bmWidth + 2;
	    rArrow.top		= (rDraw.bottom + rDraw.top - bmp.bmHeight)/2;

        pDC->BitBlt(rArrow.left, rArrow.top, bmp.bmWidth, bmp.bmHeight,
            &dcMem, 0, 0, SRCCOPY);
        
        dcMem.SelectObject(hOldBitmap);
	    DeleteDC(dcMem);

	    if (state & ODS_SELECTED)
		    rDraw.OffsetRect(1,1);
	    rDraw.right = rArrow.left - 3;
        
        
    }
				  
	if ((state & ODS_DISABLED) == 0)
	{
		pDC->FillSolidRect(&rDraw,
						   (m_crColor == CLR_DEFAULT)
						   ? m_crDefault
						   : m_crColor);

		::FrameRect(pDC->m_hDC,
					&rDraw,
					(HBRUSH)::GetStockObject(BLACK_BRUSH));
	}
	if (state & ODS_FOCUS) 
    {
  
        pDC->DrawFocusRect(&rFocus);
    }
	
//	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CColorSelCtrl::DrawArrow(CDC* pDC, 
							 RECT* pRect, 
							 int iDirection,
							 COLORREF clrArrow /*= RGB(0,0,0)*/)
{
	POINT ptsArrow[3];

	switch (iDirection)
	{
		case 0 : // Down
		{
			ptsArrow[0].x = pRect->left;
			ptsArrow[0].y = pRect->top;
			ptsArrow[1].x = pRect->right;
			ptsArrow[1].y = pRect->top;
			ptsArrow[2].x = (pRect->left + pRect->right)/2;
			ptsArrow[2].y = pRect->bottom;
			break;
		}

		case 1 : // Up
		{
			ptsArrow[0].x = pRect->left;
			ptsArrow[0].y = pRect->bottom;
			ptsArrow[1].x = pRect->right;
			ptsArrow[1].y = pRect->bottom;
			ptsArrow[2].x = (pRect->left + pRect->right)/2;
			ptsArrow[2].y = pRect->top;
			break;
		}

		case 2 : // Left
		{
			ptsArrow[0].x = pRect->right;
			ptsArrow[0].y = pRect->top;
			ptsArrow[1].x = pRect->right;
			ptsArrow[1].y = pRect->bottom;
			ptsArrow[2].x = pRect->left;
			ptsArrow[2].y = (pRect->top + pRect->bottom)/2;
			break;
		}

		case 3 : // Right
		{
			ptsArrow[0].x = pRect->left;
			ptsArrow[0].y = pRect->top;
			ptsArrow[1].x = pRect->left;
			ptsArrow[1].y = pRect->bottom;
			ptsArrow[2].x = pRect->right;
			ptsArrow[2].y = (pRect->top + pRect->bottom)/2;
			break;
		}
	}
	
	CBrush brsArrow(clrArrow);
	CPen penArrow(PS_SOLID, 1 , clrArrow);

	CBrush* pOldBrush = pDC->SelectObject(&brsArrow);
	CPen*   pOldPen   = pDC->SelectObject(&penArrow);
	
	pDC->SetPolyFillMode(WINDING);
	pDC->Polygon(ptsArrow, 3);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

//////////////////////////////////////////////////////////////////////////
//interface

COLORREF CColorSelCtrl::GetColor() const
{
    return (m_crColor == CLR_DEFAULT) ? m_crDefault:m_crColor;
}

void CColorSelCtrl::SetColor(COLORREF crColor)
{
    m_crColor = crColor;
    if (::IsWindow(m_hWnd))
    {
        RedrawWindow();
    }
}

COLORREF CColorSelCtrl::GetDefaultColor() const
{
    return m_crDefault;
}

void CColorSelCtrl::SetDefaultColor(COLORREF crColor)
{
    m_crDefault = crColor;
}

void CColorSelCtrl::SetCustomText(LPCSTR lpText)
{
    m_strCustomText = lpText;
}

void CColorSelCtrl::SetDefaultText(LPCSTR lpText)
{
    m_strDefaultText = lpText;
}

BOOL CColorSelCtrl::GetTrackSelection() const
{
    return m_bTrackSelection;
}

void CColorSelCtrl::SetTrackSelection(BOOL bTrack)
{
    m_bTrackSelection = bTrack;
}

void CColorSelCtrl::SetBtnImage(UINT nNoraml, UINT nHilight, UINT nDown, UINT nDisable)
{
    m_hBitmap[STATE_NORMAL] = CreateImage(nNoraml);
    m_hBitmap[STATE_HILIGHT] = CreateImage(nHilight);
    m_hBitmap[STATE_DOWN] = CreateImage(nDown);
    m_hBitmap[STATE_DISABLE] = CreateImage(nDisable);
}

HBITMAP CColorSelCtrl::CreateImage(UINT nBitmap)
{
    if (nBitmap == 0)
    {
        return NULL;
    }

    HINSTANCE	hInstResource	= NULL;
	
	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmap), RT_BITMAP);
    if (hInstResource == NULL)
    {
        return NULL;
    }
    return (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmap), IMAGE_BITMAP, 0, 0, 0);
}
