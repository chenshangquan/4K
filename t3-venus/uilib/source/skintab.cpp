// SkinTab.cpp : implementation file
//

#include "stdafx.h"
#include "UILIbHead.h"
#include "changelandef.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinTab
COLORREF CSkinTab::m_s_crFrame = RGB(80, 114, 170);
COLORREF CSkinTab::m_s_crHBk = RGB(234, 236, 239);
COLORREF CSkinTab::m_s_crLBk = RGB(202, 231, 251);
COLORREF CSkinTab::m_s_crTableBK = RGB(234, 236, 239);
COLORREF CSkinTab::m_s_crText = RGB(80, 114, 170);

CSkinTab::CSkinTab()
{
    m_crLBk = m_s_crLBk;
    m_crHBk = m_s_crHBk;
    m_crFrame = m_s_crFrame;
    m_crTableBK = m_s_crTableBK;
    m_crText = m_s_crText;

    m_nType = TYPE_ROUNTRECT;

    for (int i = 0; i < 4; i++)
    {
        m_hBitmap[i] = NULL;
        m_nImageWidth[i] = 0;
    }
    m_bSigleLine = TRUE;
}

CSkinTab::~CSkinTab()
{
    for (int i = 0; i < 4; i++)
    {
        if (NULL != m_hBitmap[i]) 
        {
            ::DeleteObject(m_hBitmap[i]);
        }
    }
}


BEGIN_MESSAGE_MAP(CSkinTab, CTabCtrl)
	//{{AFX_MSG_MAP(CSkinTab)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinTab message handlers

void CSkinTab::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
    dc.SelectObject(GetFont());

	// TODO: Add your message handler code here
	DRAWITEMSTRUCT dis;
	dis.CtlType = ODT_TAB;
	dis.CtlID = GetDlgCtrlID();
	dis.hwndItem = GetSafeHwnd();
	dis.hDC = dc.GetSafeHdc();
	dis.itemAction = ODA_DRAWENTIRE;

    // draw the rest of the border
	CRect rPage;
    GetWindowRect(&rPage);
    ScreenToClient(&rPage);
 //	dc.FillRect(rPage, &CBrush(m_crHBk));
    dc.FillSolidRect(rPage, m_crTableBK);
   
	GetClientRect(&rPage);
	m_rcClient = rPage;
	AdjustRect(FALSE, rPage);
	rPage.top -= 3;
	m_rcClient.top = rPage.top;
    dc.FrameRect(m_rcClient, &CBrush(m_crFrame));

    int nTab = GetItemCount();
    if (0 == nTab) 
    {
        return;
    }
    
	int nSel = GetCurSel();
    while (nTab--)
	{
		if (nTab != nSel)
		{
			dis.itemID = nTab;
			dis.itemState = GetItemState(nTab, TCIF_STATE);
			VERIFY(GetItemRect(nTab, &dis.rcItem));
			DrawItem(&dis);
		}
	}

    dis.itemID = nSel;
	dis.itemState = ODS_SELECTED;
	
	VERIFY(GetItemRect(nSel, &dis.rcItem));
	
	dis.rcItem.top -= 2;
    dis.rcItem.left -= 2;
    
    m_rcClient.top = dis.rcItem.top;
    m_rcClient.bottom = dis.rcItem.bottom;
	DrawItem(&dis);
}

void CSkinTab::DrawItem(LPDRAWITEMSTRUCT lpdis)
{
    BOOL bSel = lpdis->itemState & ODS_SELECTED;
    BOOL bHot = lpdis->itemState & TCIS_HIGHLIGHTED;

    CDC* pDC = CDC::FromHandle(lpdis->hDC);
    CRect rcItem(lpdis->rcItem);
    pDC->SetBkMode(TRANSPARENT);

    if (rcItem.left < 0) 
    {
        return;
    }
    if (NULL != m_hBitmap[0]) 
    {
        DrawImageBorder(pDC, rcItem, bSel);
    }
    else
    {
        DrawSimpleBorder(pDC, rcItem, bSel);
    }
     

    CString strTmp;
  	TC_ITEM     tci;
    TCHAR pcTemp[100];
	memset(pcTemp, 0, sizeof(pcTemp));
	tci.mask        = TCIF_TEXT | TCIF_IMAGE;
	tci.pszText		= pcTemp;
	tci.cchTextMax  = 99;
	GetItem(lpdis->itemID, &tci);
   
    strTmp = pcTemp;

    HIMAGELIST hilTabs = (HIMAGELIST)TabCtrl_GetImageList(GetSafeHwnd());
    if (NULL != hilTabs) 
    {
        IMAGEINFO info;
        ZeroMemory(&info, sizeof(IMAGEINFO));
        ImageList_GetImageInfo(hilTabs, tci.iImage, &info);
        int nTop = (rcItem.top+rcItem.bottom + info.rcImage.top - info.rcImage.bottom)/2;
        int nLeft = (rcItem.left + 18 + info.rcImage.left - info.rcImage.right);
		ImageList_Draw(hilTabs, tci.iImage, *pDC, nLeft, nTop, ILD_TRANSPARENT);
		rcItem.left += 18;
    }

    pDC->SetBkColor(m_crHBk);
    if(NULL != m_hBitmap[0])
    {
        // 使用图片时才会用m_crText值来绘制字体，默认时使用框架的颜色
        pDC->SetTextColor(m_crText);

        // 居中显示
        pDC->DrawText(strTmp, rcItem, DT_NOPREFIX|DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
    else
    {
        pDC->SetTextColor(m_crFrame);

        rcItem.left += 3;

        pDC->DrawText(strTmp, rcItem, DT_NOPREFIX|DT_LEFT|DT_VCENTER|DT_SINGLELINE);
    }
}



void CSkinTab::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CTabCtrl::PreSubclassWindow();
     DWORD dwData = ::GetWindowLong(m_hWnd, GWL_USERDATA);
    ::SetWindowLong(m_hWnd, GWL_USERDATA, dwData | STYLE_TABTRL);
    if (m_bSigleLine) 
    {
	    ModifyStyle(TCS_MULTILINE, TCS_OWNERDRAWFIXED|TCS_SINGLELINE);
        m_Spin.SubclassDlgItem(1, this);
        return;
    }
    
	ModifyStyle(0, TCS_OWNERDRAWFIXED);
}

void CSkinTab::GetRgn(CRect& rect, CRgn& rgn, BOOL bSel, int& nWidth)
{
    switch(m_nType) 
    {
    case TYPE_ROUNTRECT:
        {
            rgn.CreateRoundRectRgn(rect.left, rect.top, rect.right,
                rect.bottom, 3, 3);
            
            CRgn rgnTmp;
            rgnTmp.CreateRectRgn(rect.left, rect.top+5, rect.right-1,
            rect.bottom);

            rgn.CombineRgn(&rgn, &rgnTmp, RGN_OR);
            rgnTmp.DeleteObject();

            nWidth = rect.Width()-3;
        }
    	break;
    case TYPE_POLYGON:
        {
            CPoint pt[4];
            pt[0] = rect.TopLeft();
            pt[1] = CPoint(rect.right - rect.bottom + rect.top, rect.top);
            pt[2] = rect.BottomRight();
            pt[3] = CPoint(rect.left, rect.bottom);
            rgn.CreatePolygonRgn(pt, 4, WINDING);
            nWidth = rect.Width()-3;
        }
    	break;
    case TYPE_TRAPEZIA:
        {
            rect.right += 10;
            CPoint pt[4];
            pt[0] = CPoint(rect.left + rect.bottom - rect.top-2, rect.top);
            pt[1] = CPoint(rect.right - rect.bottom + rect.top, rect.top);
            pt[2] = rect.BottomRight();
            pt[3] = CPoint(rect.left-2, rect.bottom);

            nWidth = rect.Width() - 3;
            rect.left = pt[0].x - 2;
            rect.right = pt[1].x;
            rgn.CreatePolygonRgn(pt, 4, WINDING);
        }
        break;
    default:
        {
            rgn.CreateRectRgn(rect.left, rect.top, rect.Width(), rect.Height());
        }
    	break;
    }

}


void CSkinTab::DrawImageBorder(CDC *pDC, CRect rect, BOOL bSel)
{
    CDC memDCL, memDCR;
    memDCL.CreateCompatibleDC(pDC);
    memDCR.CreateCompatibleDC(pDC);

    COLORREF crFrame;

    if (bSel) 
    {
        memDCL.SelectObject(m_hBitmap[0]);
        memDCR.SelectObject(m_hBitmap[1]);
        crFrame = memDCR.GetPixel(0,0);

        pDC->FillSolidRect(rect, m_crHBk);
        pDC->FillSolidRect(rect.left, rect.top, rect.Width(), 1, crFrame);
        pDC->BitBlt(rect.left, rect.top, m_nImageWidth[0], 
            rect.Height(), &memDCL, 0, 0, SRCCOPY);
        pDC->BitBlt(rect.right - m_nImageWidth[1], rect.top, m_nImageWidth[1], 
            rect.Height(), &memDCR, 0, 0, SRCCOPY);
    }
    else
    {
        memDCL.SelectObject(m_hBitmap[2]);
        memDCR.SelectObject(m_hBitmap[3]);
        crFrame = memDCR.GetPixel(0,0);
        pDC->FillSolidRect(rect, m_crLBk);
        pDC->FillSolidRect(rect.left, rect.top, rect.Width(), 1, crFrame);
        pDC->BitBlt(rect.left, rect.top, m_nImageWidth[2], 
            rect.Height(), &memDCL, 0, 0, SRCCOPY);
        pDC->BitBlt(rect.right - m_nImageWidth[3], rect.top, m_nImageWidth[3], 
            rect.Height(), &memDCR, 0, 0, SRCCOPY);
        pDC->FillSolidRect(rect.left, rect.bottom-1, rect.Width(), 1, crFrame);

    }
    
//    pDC->FillSolidRect(rect.left-1, rect.bottom, rect.Width()-2, 2, m_crHBk);

    memDCL.DeleteDC();
    memDCR.DeleteDC();
}

void CSkinTab::DrawSimpleBorder(CDC *pDC, CRect& rect, BOOL bSel)
{
    CRgn rgn;

    CRect rcOld = rect;
    int nWidth;

     if (!bSel) 
     {
         GetRgn(rect, rgn, FALSE, nWidth);
         pDC->FillRgn(&rgn, &CBrush(m_crLBk));
     }
     else
     {
         rect.right += 2;
         rcOld.right += 2;
         GetRgn(rect, rgn, TRUE, nWidth);
         pDC->FillRgn(&rgn, &CBrush(m_crHBk));
     }
 
     pDC->FrameRgn(&rgn, &CBrush(m_crFrame), 1, 1);
     
     rcOld.DeflateRect(1,1);
     if (bSel) 
     {
         pDC->FillSolidRect(rcOld.left, rcOld.bottom, nWidth, 1, m_crHBk);
     }
 
     rgn.DeleteObject();
}

void CSkinTab::SetType(UINT nType)
{
    m_nType = nType;
}

void CSkinTab::SetMask(UINT nHLeft, UINT nHRight, UINT nLLeft, UINT nLRight)
{    
    m_hBitmap[0] = CUITools::CreateImage(nHLeft);
    m_hBitmap[1] = CUITools::CreateImage(nHRight);
    m_hBitmap[2] = CUITools::CreateImage(nLLeft);
    m_hBitmap[3] = CUITools::CreateImage(nLRight); 

    BITMAP bmp;
    for (int iIndex = 0; iIndex < 4; iIndex++)
    {
        GetObject(m_hBitmap[iIndex], sizeof(BITMAP), &bmp);
        m_nImageWidth[iIndex] = bmp.bmWidth;
    }
}

void CSkinTab::SetColors(COLORREF crFrame, COLORREF crHBk, COLORREF crLBk, COLORREF crText)
{
    m_crFrame = crFrame;
    m_crHBk = crHBk;
    m_crLBk = crLBk;
    m_crText = crText;
}


void CSkinTab::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if (m_rcClient.PtInRect(point)) 
    {
	    InvalidateRect(m_rcClient);
    }
	CTabCtrl::OnLButtonDown(nFlags, point);
}

void CSkinTab::staticSetColors(COLORREF crFrame, COLORREF crHBk, COLORREF crLBk, COLORREF crText)
{
    m_s_crFrame = crFrame;
    m_s_crHBk = crHBk;
    m_s_crLBk = crLBk;
    m_s_crText = crText;
}


/*=============================================================================
函 数 名： SetBKColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crBk
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/09/19  4.0			朱允荣                  创建
=============================================================================*/
void CSkinTab::SetBKColor(COLORREF crBk)
{
    m_crTableBK = crBk;
}


/*=============================================================================
函 数 名： staticSetBKColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crBk
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/09/19  4.0			朱允荣                  创建
=============================================================================*/
void CSkinTab::staticSetBKColor(COLORREF crBk)
{
    m_s_crTableBK = crBk;
}