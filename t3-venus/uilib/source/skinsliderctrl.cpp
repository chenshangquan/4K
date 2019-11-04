/********************************************************************
	模块名:      UILib
	文件名:      skinsliderctrl.cpp
	相关文件:    UILIbHead.h
	文件实现功能 
    作者：       朱允荣
	版本：       1.0
--------------------------------------------------------------------------------
	修改记录:
	日  期		版本		修改人		走读人    修改内容
	2004/4/8	1.0			朱允荣                  创建

*********************************************************************/


#include "stdafx.h"
#include "UILIbHead.h"
#include "msgIdDispatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinSlider

COLORREF CSkinSlider::m_s_crThumb[ISTATEMAX] = {RGB(118,168,239), RGB(184,221,252),
                                                RGB(64,91,143), RGB(118,168,239)};
COLORREF CSkinSlider::m_s_crBk = RGB(241, 242, 244);

CSkinSlider::CSkinSlider()
{
    m_hDCBk = NULL;
    m_BitmapBk = NULL;
    m_OldBitmapBk = NULL;

    m_BitmapTrBk = NULL;

    m_BitmapThumb[0] = NULL;
    m_BitmapThumb[1] = NULL;
    m_hThumbMask[0] = NULL;
    m_hThumbMask[1] = NULL;

    m_bTransparent = FALSE;
    m_bAllBkImage = FALSE;
    m_crBk = m_s_crBk;
    m_brushBk.CreateSolidBrush(m_crBk);

    for (int i = 0; i < ISTATEMAX; i++)
    {
        m_crThumb[i] = m_s_crThumb[i];
    }
    m_bHot = FALSE;
}

CSkinSlider::~CSkinSlider()
{
    if (m_hDCBk != NULL && m_OldBitmapBk != NULL)
    {
        ::SelectObject(m_hDCBk, m_OldBitmapBk);
        ::DeleteObject(m_hDCBk);
        m_hDCBk = NULL;
    }

    if (m_BitmapBk != NULL)
    {
        ::DeleteObject(m_BitmapBk);
        m_BitmapBk = NULL;
    }
    if (m_BitmapTrBk != NULL)
    {
        ::DeleteObject(m_BitmapTrBk);
        m_BitmapTrBk = NULL;
    }

    for (int i = 0; i < 2; i++)
    {
        if (m_BitmapThumb[i] != NULL)
        {
            ::DeleteObject(m_BitmapThumb[i]);
            m_BitmapThumb[i] = NULL;
        }
        if (m_hThumbMask[i] != NULL)
        {
            ::DeleteObject(m_hThumbMask[i]);
            m_hThumbMask[i] = NULL;
        }
    }

    if (m_brushBk.m_hObject != NULL)
    {
        m_brushBk.DeleteObject();
    }
}


BEGIN_MESSAGE_MAP(CSkinSlider, CSliderCtrl)
	//{{AFX_MSG_MAP(CSkinSlider)
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_MOUSEMOVE()
    ON_WM_CAPTURECHANGED()
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinSlider message handlers

BOOL CSkinSlider::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
    if (m_bAllBkImage && m_BitmapBk != NULL)
    {
        CRect rcClient;
        GetClientRect(&rcClient);

        HDC hDCBk;
        hDCBk = CreateCompatibleDC(pDC->m_hDC);
	    HBITMAP OldBitmapBk = (HBITMAP)::SelectObject(hDCBk, m_BitmapBk);
        BITMAP bmp;  
        int nRetValue = ::GetObject(m_BitmapBk, sizeof(bmp), &bmp);
        if (nRetValue == 0)
        {
            return TRUE;
        }
    
	    COLORREF crOldBack = ::SetBkColor(pDC->m_hDC, RGB(255,255,255));
	    COLORREF crOldText = ::SetTextColor(pDC->m_hDC, RGB(0,0, 0));
         ::StretchBlt(pDC->m_hDC,rcClient.left, rcClient.top, 
             rcClient.Width(), rcClient.Height(), hDCBk, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

	    ::SetBkColor(pDC->m_hDC, crOldBack);
	    ::SetTextColor(pDC->m_hDC, crOldText);
        ::SelectObject(hDCBk, OldBitmapBk);
        ::DeleteObject(hDCBk);
    }
	return TRUE;
}

void CSkinSlider::DrawChannel(CDC *pDC, LPNMCUSTOMDRAW lpcd, BOOL& bFocus)
{
    if (m_bTransparent)
    {
        DrawTrans(pDC, lpcd->rc, bFocus);
    }
    else if (bFocus)
    {
        CRect crect;
        GetClientRect(crect);
        pDC->FrameRect(crect, &m_brushBk);
	    COLORREF crOldBack = ::SetBkColor(pDC->m_hDC, RGB(0,0,0));
	    COLORREF crOldText = ::SetTextColor(pDC->m_hDC, RGB(255, 255, 255));
        pDC->DrawFocusRect(crect);
        bFocus = FALSE;
	    ::SetBkColor(pDC->m_hDC, crOldBack);
	    ::SetTextColor(pDC->m_hDC, crOldText);
    }

    if (m_BitmapBk == NULL)
    {  
	    DrawEdge(pDC->m_hDC, &lpcd->rc, EDGE_SUNKEN, BF_RECT | BF_ADJUST);
    }
    else if (!m_bAllBkImage)
    {
        DrawBMPChannel(pDC, lpcd, bFocus);
    }
}


void CSkinSlider::DrawBMPChannel(CDC *pDC, LPNMCUSTOMDRAW lpcd, BOOL &bFocus)
{

    CRect rcClient(lpcd->rc);

    HDC hDCBk;
    hDCBk = CreateCompatibleDC(pDC->m_hDC);
	HBITMAP OldBitmapBk = (HBITMAP)::SelectObject(hDCBk, m_BitmapBk);
    BITMAP bmp;  
    int nRetValue = ::GetObject(m_BitmapBk, sizeof(bmp), &bmp);
    if (nRetValue == 0)
    {
        return;
    }
    
	COLORREF crOldBack = ::SetBkColor(pDC->m_hDC, RGB(255,255,255));
	COLORREF crOldText = ::SetTextColor(pDC->m_hDC, RGB(0,0, 0));
 //    ::BitBlt(pDC->m_hDC, rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), m_hDCBk, 5, 0, SRCCOPY);
     ::StretchBlt(pDC->m_hDC,rcClient.left, rcClient.top, 
         rcClient.Width(), rcClient.Height(), hDCBk, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

	::SetBkColor(pDC->m_hDC, crOldBack);
	::SetTextColor(pDC->m_hDC, crOldText);
    ::SelectObject(hDCBk, OldBitmapBk);
    ::DeleteObject(hDCBk);
}

void CSkinSlider::DrawTrans(CDC *pDC, CRect rect, BOOL &bFocus)
{
    CClientDC clientDC(GetParent());
	CRect crect;
	CRect wrect;		
	GetClientRect(crect);
	GetWindowRect(wrect);
	GetParent()->ScreenToClient(wrect);

	if (m_hDCBk == NULL)
	{
        m_hDCBk = CreateCompatibleDC(clientDC.m_hDC);
		m_BitmapTrBk = CreateCompatibleBitmap(clientDC.m_hDC, crect.Width(), crect.Height());
		m_OldBitmapBk = (HBITMAP)::SelectObject(m_hDCBk, m_BitmapTrBk);
		::BitBlt(m_hDCBk, 0, 0, crect.Width(), crect.Height(), clientDC.m_hDC, wrect.left, wrect.top, SRCCOPY);
	}
//	//This bit does the tics marks transparently.
//	//create a memory dc to hold a copy of the oldbitmap data that includes the tics,
//	//because when we add the background in we will lose the tic marks
	HDC hSaveHDC;
	HBITMAP hSaveBmp;
	int iWidth = crect.Width();
	int iHeight = crect.Height();
	hSaveHDC = ::CreateCompatibleDC(pDC->m_hDC);
	hSaveBmp = ::CreateCompatibleBitmap(hSaveHDC, iWidth, iHeight);
	HBITMAP hSaveCBmpOld = (HBITMAP)::SelectObject(hSaveHDC, hSaveBmp);			
	//set the colours for the monochrome mask bitmap
	COLORREF crOldBack = ::SetBkColor(pDC->m_hDC, RGB(0,0,0));
	COLORREF crOldText = ::SetTextColor(pDC->m_hDC, RGB(255,255,255));		
	::BitBlt(hSaveHDC, 0, 0, iWidth, iHeight, pDC->m_hDC, crect.left, crect.top, SRCCOPY);
	::BitBlt(pDC->m_hDC, 0, 0, iWidth, iHeight, m_hDCBk, 0, 0, SRCCOPY);
	::BitBlt(pDC->m_hDC, 0, 0, iWidth, iHeight, hSaveHDC, 0, 0, SRCAND);

    if (bFocus)
    {
        pDC->DrawFocusRect(crect);
        bFocus = FALSE;
    }
	//restore and clean up
	::SetBkColor(pDC->m_hDC, crOldBack);
	::SetTextColor(pDC->m_hDC, crOldText);
	::SelectObject(hSaveHDC, hSaveCBmpOld);
	::DeleteObject(hSaveBmp);
	::DeleteDC(hSaveHDC);
	
}

void CSkinSlider::DrawThumb(CDC *pDC, LPNMCUSTOMDRAW lpcd)
{
    CRect rcThumb(lpcd->rc);
    m_rcThumb = rcThumb;

    if (m_BitmapThumb[0] == NULL)
    {
        int nState = GetState(lpcd->uItemState);
     //   pDC->Draw3dRect(rcThumb, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
        pDC->Draw3dRect(rcThumb, m_crThumb[nState], m_crThumb[ISTATESELECT]);
        rcThumb.DeflateRect(1,1);
        pDC->FillRect(rcThumb, &CBrush(m_crThumb[nState]));
        return;
    }

    CDC dc, dcMask;
    dc.CreateCompatibleDC(pDC);
    dcMask.CreateCompatibleDC(pDC);

    CBitmap bmp;
    if (!IsWindowEnabled())
    {
        int a = 0;
    }
    HBITMAP pOldBitmap = (HBITMAP)::SelectObject(dc.m_hDC, m_BitmapThumb[IsWindowEnabled()? 0:1]);
    HBITMAP pOldMask = (HBITMAP)::SelectObject(dcMask.m_hDC, m_hThumbMask[IsWindowEnabled()? 0:1]);
    
    COLORREF crOldText = ::SetTextColor(pDC->m_hDC, RGB(0,0,0));
	COLORREF crOldBack = ::SetBkColor(pDC->m_hDC, RGB(255,255,255));	

    BITMAP szBMP;
    int nRevValue = ::GetObject(m_BitmapThumb[0], sizeof(szBMP), &szBMP);
    if (nRevValue == 0)
    {
        return;
    }
    pDC->StretchBlt(rcThumb.left, rcThumb.top, rcThumb.Width(), rcThumb.Height(), &dcMask, 0, 0, szBMP.bmWidth, szBMP.bmHeight, SRCAND);
    pDC->StretchBlt(rcThumb.left, rcThumb.top, rcThumb.Width(), rcThumb.Height(), &dc, 0, 0, szBMP.bmWidth, szBMP.bmHeight, SRCPAINT);

    ::SelectObject(dc.m_hDC, pOldBitmap);
    ::SelectObject(dcMask.m_hDC, pOldMask);
    pDC->SetTextColor(crOldText);
    pDC->SetBkColor(crOldBack);
    dc.DeleteDC();
    dcMask.DeleteDC();
}

int CSkinSlider::GetState(UINT uState)
{
    switch(uState) 
    {
    case CDIS_SELECTED:
    	return ISTATESELECT;
    case CDIS_DISABLED:
    	return ISTATEDISABLE;
    case CDIS_HOT:
        return ISTATEHOT;
    default:
    	return ISTATENORMAL;
    }    
}

HBRUSH CSkinSlider::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here

	// TODO: Return a non-NULL brush if the parent's handler should not be called
	pDC->SetBkColor(m_crBk);
	return (HBRUSH)m_brushBk.m_hObject;
}

void CSkinSlider::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
   /*
   	BOOL bHot = m_rcThumb.PtInRect(point);
       if (bHot != m_bHot) 
       {
           m_bHot = bHot;
           if (m_bHot)
           {
   	        TRACKMOUSEEVENT		csTME;
               csTME.cbSize = sizeof(csTME);
   			csTME.dwFlags = TME_LEAVE;
   			csTME.hwndTrack = m_hWnd;
   			::_TrackMouseEvent(&csTME);
           }
       }*/
   
	CSliderCtrl::OnMouseMove(nFlags, point);
}

LRESULT CSkinSlider::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
   /*
     m_bHot = FALSE;
        InvalidateRect(m_rcThumb);*/
    
    return 0;
}


void CSkinSlider::OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMCUSTOMDRAW lpcd = (LPNMCUSTOMDRAW)pNMHDR;
	CDC *pDC = CDC::FromHandle(lpcd->hdc);
	static BOOL bFocus = FALSE;
    
	switch(lpcd->dwDrawStage)
	{
		case CDDS_PREPAINT:
            if (CDIS_FOCUS  == (lpcd->uItemState&CDIS_FOCUS))
            {
                bFocus = TRUE;
            }
			*pResult = CDRF_NOTIFYITEMDRAW;
		    break;
		case CDDS_ITEMPREPAINT:
		{
			switch(lpcd->dwItemSpec)
			{
				case TBCD_TICS:
					*pResult = CDRF_DODEFAULT;
					break;
				case TBCD_THUMB:
					DrawThumb(pDC, lpcd);
					*pResult = CDRF_SKIPDEFAULT;
				    break;
				case TBCD_CHANNEL:
                    if (!m_bTransparent && m_BitmapBk == NULL)
                    {
                        *pResult = CDRF_DODEFAULT;
                    }
                    else
                    {
					    DrawChannel(pDC, lpcd, bFocus);
					    *pResult = CDRF_SKIPDEFAULT;
                    }
					break;
                default:
                    break;
			}

			break;
		}
        case CDDS_POSTPAINT:
            bFocus = FALSE;
            *pResult = CDRF_DODEFAULT;
            break;
        default:
            *pResult = CDRF_DODEFAULT;
            break;
	}
}

HBITMAP CSkinSlider::CreateImage(UINT nBitmap)
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

HBITMAP CSkinSlider::CreateMask(HBITMAP hSourceBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTransColor)
{
    HBITMAP     hMask       = NULL;
	HDC			hdcSrc		= NULL;
	HDC			hdcDest		= NULL;
	HBITMAP		hbmSrcT		= NULL;
	HBITMAP		hbmDestT	= NULL;
	COLORREF	crSaveBk;
	COLORREF	crSaveDestText;

	hMask = ::CreateBitmap(dwWidth, dwHeight, 1, 1, NULL);
	if (hMask == NULL)	return NULL;

	hdcSrc	= ::CreateCompatibleDC(NULL);
	hdcDest	= ::CreateCompatibleDC(NULL);

	hbmSrcT = (HBITMAP)::SelectObject(hdcSrc, hSourceBitmap);
	hbmDestT = (HBITMAP)::SelectObject(hdcDest, hMask);

	crSaveBk = ::SetBkColor(hdcSrc, crTransColor);

	::BitBlt(hdcDest, 0, 0, dwWidth, dwHeight, hdcSrc, 0, 0, SRCCOPY);

	crSaveDestText = ::SetTextColor(hdcSrc, RGB(255, 255, 255));
	::SetBkColor(hdcSrc,RGB(0, 0, 0));

	::BitBlt(hdcSrc, 0, 0, dwWidth, dwHeight, hdcDest, 0, 0, SRCAND);

	SetTextColor(hdcDest, crSaveDestText);

	::SetBkColor(hdcSrc, crSaveBk);
	::SelectObject(hdcSrc, hbmSrcT);
	::SelectObject(hdcDest, hbmDestT);

	::DeleteDC(hdcSrc);
	::DeleteDC(hdcDest);

	return hMask;
}

//接口函数


/*====================================================================
函数名	：    SetTickImage
功能		：设置滑块图片
算法实现	：（可选项）
引用全局变量：无
输入参数说明：hBitmap:有效时滑块的图片
              crTans:图片的背景色，可以屏蔽该颜色，透明显示该颜色的区域
              hDisableBitmap:失效时的滑块图片
              crDisableTans:失效时的图片的透明色。
返回值说明：  无
====================================================================*/
void CSkinSlider::SetTickImage(HBITMAP hBitmap, COLORREF crTans, HBITMAP hDisableBitmap, COLORREF crDisableTans)
{
    if (m_BitmapThumb[0] != NULL)
    {
        DeleteObject(m_BitmapThumb[0]);
        m_BitmapThumb[0] = NULL;
    }

    m_BitmapThumb[0] = hBitmap;
    if (m_BitmapThumb[0] == NULL)
    {
        return;
    }

    if (m_BitmapThumb[1] != NULL)
    {
        DeleteObject(m_BitmapThumb[1]);
        m_BitmapThumb[1] = NULL;
    }

    if (hDisableBitmap == NULL)
    {
        m_BitmapThumb[1] = m_BitmapThumb[0];
    }
    else
    {
        m_BitmapThumb[1] = hDisableBitmap;
    }

    BITMAP bmp;
    if (GetObject(m_BitmapThumb[0], sizeof(bmp), &bmp) == 0)
    {
        m_hThumbMask[0] = NULL;
        m_hThumbMask[1] = NULL;
        return;
    }
    m_hThumbMask[0] = CreateMask(m_BitmapThumb[0], bmp.bmWidth, bmp.bmHeight, crTans);
    m_hThumbMask[1] = CreateMask(m_BitmapThumb[1], bmp.bmWidth, bmp.bmHeight, crDisableTans);
}

/*====================================================================
函数名	：    SetTickImage
功能		：设置滑块图片
算法实现	：（可选项）
引用全局变量：无
输入参数说明：nBitmap:有效时滑块的图片
              crTans:图片的背景色，可以屏蔽该颜色，透明显示该颜色的区域
              nDisableBitmap:失效时的滑块图片
              crDisableTans:失效时的图片的透明色。
返回值说明：  无
====================================================================*/
void CSkinSlider::SetTickImage(UINT nBitmap, COLORREF crTans, UINT nDisableBitmap, COLORREF crDisableTans)
{
    SetTickImage(CreateImage(nBitmap), crTans, CreateImage(nDisableBitmap), crDisableTans);
}


/*====================================================================
函数名	：    SetBkColor
功能		：设定控件背景色
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crBk:背景色
              bRepaint:是否马上重画。
返回值说明：  无
====================================================================*/
void CSkinSlider::SetBkColor(COLORREF crBk, BOOL bRepaint)
{
    m_crBk = crBk;
    if (m_brushBk.m_hObject != NULL)
    {
        m_brushBk.DeleteObject();
    }
    m_brushBk.CreateSolidBrush(m_crBk);

    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
函数名	：    SetBkImage
功能		：设置背景图
算法实现	：（可选项）
引用全局变量：无
输入参数说明：hBitmap:背景图句柄
返回值说明：  无
====================================================================*/
void CSkinSlider::SetBkImage(HBITMAP hBitmap)
{
    if (m_BitmapBk != NULL)
    {
        DeleteObject(m_BitmapBk);
        m_BitmapBk = NULL;
    }
    m_BitmapBk = hBitmap;
}

/*====================================================================
函数名	：    SetBkImage
功能		：设置背景图
算法实现	：（可选项）
引用全局变量：无
输入参数说明：nBitmap:背景图资源ID号。
返回值说明：  无
====================================================================*/
void CSkinSlider::SetBkImage(UINT nBitmap)
{
    SetBkImage(CreateImage(nBitmap));
}

/*====================================================================
函数名	：    SetBkTransparent
功能		：是否背景透明
算法实现	：（可选项）
引用全局变量：无
输入参数说明：bTans:是否背景透明。
返回值说明：  无
====================================================================*/
void CSkinSlider::SetBkTransparent(BOOL bTans)
{
    m_bTransparent = bTans;
}

/*====================================================================
函数名	：    SetTickColor
功能		：设置滑块的颜色
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crNormal:正常时的颜色；
              crSelect:拖动时的颜色；
              crDisable:失效时的颜色；
              bRepaint:是否马上重画。
返回值说明：  无
====================================================================*/
void CSkinSlider::SetTickColor(COLORREF crNormal, COLORREF crSelect, COLORREF crDisable, BOOL bRepaint)
{
    m_crThumb[ISTATENORMAL] = crNormal;
    m_crThumb[ISTATESELECT] = crSelect;
    if (crDisable != -1) 
    {
        m_crThumb[ISTATEDISABLE] = crDisable;
    }
    else
    {
        m_crThumb[ISTATEDISABLE] = crNormal;
    }

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
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  3.6			朱允荣                  创建
=============================================================================*/
void CSkinSlider::staticSetBkColor(COLORREF crBk)
{
    m_s_crBk = crBk;
}

void CSkinSlider::staticSetTickColor(COLORREF crNormal, COLORREF crSelect, COLORREF crDisable)
{
    m_s_crThumb[ISTATENORMAL] = crNormal;
    m_s_crThumb[ISTATESELECT] = crSelect;
    m_s_crThumb[ISTATEDISABLE] = crDisable;
}



/*=============================================================================
函 数 名： OnCaptureChanged
功    能： 
算法实现： 
全局变量： 
参    数：  
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2011/07/19  1.0			俞锦锦                  创建
=============================================================================*/
void CSkinSlider::OnCaptureChanged(CWnd *pWnd) 
{ 
   // this->SendMessage(SLIDER_RELEASED_CAPTURE, NULL, NULL );   ---接收不到
    this->PostMessage(SLIDER_RELEASED_CAPTURE, NULL, NULL);
    CSliderCtrl::OnCaptureChanged(pWnd);
}