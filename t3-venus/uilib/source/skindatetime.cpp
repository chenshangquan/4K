// SkinDateTime.cpp : implementation file
//

#include "stdafx.h"
#include "uilibhead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinDateTime
COLORREF CSkinDateTime::m_s_crBk[2] = {RGB(255, 255, 255), RGB(233,233,233)};
//{RGB(0, 0, 0), RGB(233,233,233)};//
COLORREF CSkinDateTime::m_s_crText[2] = {RGB(0, 0, 0), RGB(128, 128, 128)};
// {RGB(255, 255, 255), RGB(80, 114, 170)};//
COLORREF CSkinDateTime::m_s_crFrame = RGB(0, 0, 0);

CSkinDateTime::CSkinDateTime()
{
        m_crBk[0] = m_s_crBk[0];
        m_crBk[1] = m_s_crBk[1];

        m_crText[0] = m_s_crText[0];
        m_crText[1] = m_s_crText[1];
        m_crFrame = m_s_crFrame;
}

CSkinDateTime::~CSkinDateTime()
{
}


BEGIN_MESSAGE_MAP(CSkinDateTime, CDateTimeCtrl)
	//{{AFX_MSG_MAP(CSkinDateTime)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinDateTime message handlers

HBRUSH CSkinDateTime::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	if (IsWindowEnabled())
    {
        pDC->SetTextColor(m_crText[0]);
        pDC->SetBkColor(m_crBk[0]);
        return (HBRUSH)m_brushBk[0];
    }
    else
    {
        pDC->SetTextColor(m_crText[1]);
        pDC->SetBkColor(m_crBk[1]);
        return (HBRUSH)m_brushBk[1];
    }
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}



HBRUSH CSkinDateTime::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDateTimeCtrl::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	if (IsWindowEnabled())
    {
        pDC->SetTextColor(m_crText[0]);
        pDC->SetBkColor(m_crBk[0]);
        return (HBRUSH)m_brushBk[0];
    }
    else
    {
        pDC->SetTextColor(m_crText[1]);
        pDC->SetBkColor(m_crBk[1]);
        return (HBRUSH)m_brushBk[1];
    }
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSkinDateTime::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
    GetClientRect(rect);
	// Do not call CDateTimeCtrl::OnPaint() for painting messages
    dc.FillSolidRect(rect, m_crBk[0]);

    dc.SetTextColor(m_crText[0]);
    DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
   // dc.FrameRect(rect, &CBrush(m_crFrame));
    CWindowDC wdc(this);
    rect.InflateRect(-1,-1,2,2);
    wdc.FrameRect(rect, &CBrush(m_crBk[0]));
    rect.InflateRect(1,1,0,0);
    wdc.FrameRect(rect, &CBrush(m_crFrame));
}


void CSkinDateTime::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	DWORD dwStyle = GetExStyle();
    SetWindowLong(m_hWnd, GWL_EXSTYLE, 
        dwStyle & ~(WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE|WS_EX_STATICEDGE|WS_EX_DLGMODALFRAME));
    
    BOOL bret = m_Spin.SubclassDlgItem(1000, this);
    if (bret)
    {
        CRect rect;
        m_Spin.GetWindowRect(rect);
        ScreenToClient(rect);
        rect.DeflateRect(0,0,2,2);
        m_Spin.MoveWindow(rect);
    }
	CDateTimeCtrl::PreSubclassWindow();
}


BOOL CSkinDateTime::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
    NMHDR* pNMHDR = (NMHDR*)lParam;
	
	BOOL bRet =  CDateTimeCtrl::OnNotify(wParam, lParam, pResult);
    if (pNMHDR->code == UDN_DELTAPOS && pNMHDR->idFrom == 1000)
    {
        return FALSE;
    }
    return bRet;
}

void CSkinDateTime::SetFrameColor(COLORREF crFrame)
{
    m_crFrame = crFrame;
}

void CSkinDateTime::SetBackColor(COLORREF crBK, COLORREF crDisable)
{
    m_crBk[0] = crBK;
    m_crBk[1] = crDisable;
}

void CSkinDateTime::SetTextColor(COLORREF crText, COLORREF crDisable)
{
    m_crText[0] = crText;
    m_crText[1] = crDisable;
}

void CSkinDateTime::static_SetFrameColor(COLORREF crFrame)
{
    m_s_crFrame = crFrame;
}

void CSkinDateTime::static_SetBackColor(COLORREF crBK, COLORREF crDisable)
{
    m_s_crBk[0] = crBK;
    m_s_crBk[1] = crDisable;
}

void CSkinDateTime::static_SetTextColor(COLORREF crText, COLORREF crDisable)
{
    m_s_crText[0] = crText;
    m_s_crText[1] = crDisable;
}