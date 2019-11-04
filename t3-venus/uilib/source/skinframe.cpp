// SkinFrame.cpp : implementation file
//

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinFrame
COLORREF CSkinFrame::m_s_crFrame = RGB(80, 114, 170);

CSkinFrame::CSkinFrame()
{
    m_crFrame = m_s_crFrame;
}

CSkinFrame::~CSkinFrame()
{
}


BEGIN_MESSAGE_MAP(CSkinFrame, CStatic)
	//{{AFX_MSG_MAP(CSkinFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinFrame message handlers

void CSkinFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
    CRect rect;
    GetClientRect(rect);
    dc.FrameRect(rect, &CBrush(m_crFrame));
}

void CSkinFrame::SetFrameColor(COLORREF crFrame, BOOL bRepaint)
{
    m_crFrame = crFrame;
    if (bRepaint) 
    {
        Invalidate();
    }
}
