/********************************************************************
	模块名:      UILib.lib
	文件名:      SkinComboBox.cpp
	相关文件:    UILIbHead.h
	文件实现功能 
    作者：       朱允荣
	版本：       1.0
--------------------------------------------------------------------
	修改记录:
	日  期		版本		修改人		走读人    修改内容
	2004/4/8	1.0	        朱允荣               ------------

*********************************************************************/

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinComboBox
COLORREF CSkinComboBox::m_s_crBk[3] = {RGB(241, 242, 244), GetSysColor(COLOR_HIGHLIGHT),
                                        RGB(233, 233, 233)};
COLORREF CSkinComboBox::m_s_crButton[4] = {RGB(80, 114, 170), RGB(241, 242, 244),
                                        RGB(80, 114, 170), RGB(233, 233, 233)};
COLORREF CSkinComboBox::m_s_crText[2] = {RGB(80, 114, 170), RGB(255,255,255)};
COLORREF CSkinComboBox::m_s_crFrame = RGB(80, 114, 170);

CSkinComboBox::CSkinComboBox()
{
    m_crText[0] = m_s_crText[0];          //normal
    m_crText[1] = m_s_crText[1];           //highlight
    m_crBk[0] = m_s_crBk[0];                //normal
    m_crBk[1] = m_s_crBk[1];      //highlight
    m_crBk[2] = m_s_crBk[2];                //disable
    m_brushBk[0].CreateSolidBrush(m_crBk[0]);
    m_brushBk[1].CreateSolidBrush(m_crBk[2]);

    m_crFrame = m_s_crFrame;

    m_crButton[0] = m_s_crButton[0]; //enable arrow
    m_crButton[1] = m_s_crButton[1]; // enable background
    m_crButton[2] = m_s_crButton[2];  // disable arrow
    m_crButton[3] = m_s_crButton[3]; // disable background
    m_bDrop = FALSE;
    m_bEnable = TRUE;

    m_hBitmap[0] = NULL;
    m_hBitmap[1] = NULL;

    m_bNeedFree = FALSE;
}

CSkinComboBox::~CSkinComboBox()
{
    if (m_bNeedFree) 
    {
        if (m_hBitmap[0] != NULL) 
        {
            ::DeleteObject(m_hBitmap[0]);
            m_hBitmap[0] = NULL;
        }
        if (m_hBitmap[1] != NULL) 
        {
            ::DeleteObject(m_hBitmap[1]);
            m_hBitmap[1] = NULL;
        }
        m_bNeedFree = FALSE;
    }
    m_brushBk[0].DeleteObject();
    m_brushBk[1].DeleteObject();
}


BEGIN_MESSAGE_MAP(CSkinComboBox, CComboBox)
	//{{AFX_MSG_MAP(CSkinComboBox)
	ON_WM_PAINT()
	ON_CONTROL_REFLECT_EX(CBN_DROPDOWN, OnDropdown)
	ON_WM_LBUTTONUP()
 	ON_WM_CTLCOLOR()
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinComboBox message handlers

//画listbox里的行
void CSkinComboBox::DrawItem(LPDRAWITEMSTRUCT lpDS) 
{
	// TODO: Add your code to draw the specified item
    CDC* pDC = CDC::FromHandle(lpDS->hDC);
    CRect rect(lpDS->rcItem);

    int nState = lpDS->itemState;

    if (lpDS->itemID == -1)
    {
        return;
    }

    pDC->SetBkMode(TRANSPARENT);

    if ((nState & ODS_COMBOBOXEDIT) != ODS_COMBOBOXEDIT)
    {
//        rect.DeflateRect(0,-1);
    }

    if ((nState & ODS_SELECTED) == ODS_SELECTED)
    {
        pDC->SetTextColor(m_crText[1]);
        pDC->SetBkColor(m_crBk[1]);
        pDC->FillSolidRect(rect, m_crBk[1]);
    }
    else
    {
        CRect rcFull(rect);
  //      rcFull.bottom = rcFull.top + 16;
        pDC->SetTextColor(m_crText[0]);
        pDC->SetBkColor(m_crBk[0]);
        pDC->FillSolidRect(rcFull, m_crBk[0]);
    }

    if ((nState & ODS_FOCUS) == ODS_FOCUS)
    {
        pDC->DrawFocusRect(rect);
    }

    CString str;
    GetLBText(lpDS->itemID, str);
    pDC->DrawText(str, rect, DT_VCENTER|DT_LEFT|DT_SINGLELINE);
}

void CSkinComboBox::DrawImageButton(CDC *pDC, CRect rect)
{
    CDC MemDC;
    MemDC.CreateCompatibleDC(pDC);

    MemDC.SelectObject(m_hBitmap[m_bEnable? 0:1]);
    
    pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &MemDC,
         0, 0, m_sizeButton.cx, m_sizeButton.cy,SRCCOPY);
    MemDC.DeleteDC();
}

//画Combobox边框和按钮
void CSkinComboBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	
	// Do not call CComboBox::OnPaint() for painting messages
    m_bEnable = IsWindowEnabled();
    int nIndex = m_bEnable ? 0 : 2;
       
    dc.SetTextColor(m_crText[0]);
    dc.SetBkColor(m_crBk[nIndex]);

    CRect rect;
    GetClientRect(&rect);
    
    dc.FrameRect(rect, &CBrush(m_crFrame));
    rect.DeflateRect(1,1);

    dc.FillRect(rect, &m_brushBk[nIndex/2]);
    if (m_bDrawList)
    {
        int nSel = GetCurSel();
        if (nSel != -1)
        {
            SetCurSel(nSel);
        }
    }
 
    int cxHThumb     = ::GetSystemMetrics(SM_CXHTHUMB);
    int cyHThumb     = ::GetSystemMetrics(SM_CYVTHUMB);
    int nMetric = (rect.Height() - cyHThumb)/2;
    CRect rcButton(rect);
    rcButton.left = rcButton.right - cxHThumb;
    rcButton.bottom--;
    rcButton.top++;

    //画按钮 
    if (m_hBitmap[0] != NULL)
    {
        DrawImageButton(&dc, rcButton);
        return;
    }


    CPoint pt[3];
    CRgn rgn;

    pt[0].x = rcButton.left + rcButton.Width()/5;
    pt[0].y = rcButton.top + rcButton.Height()/3;
    pt[1].x = rcButton.right - rcButton.Width()/5;
    pt[1].y = pt[0].y;
    pt[2].x = (rcButton.left + rcButton.right)/2;
    pt[2].y = rcButton.bottom - rcButton.Height()/3;
    rgn.CreatePolygonRgn(pt, 3, WINDING);

    if (m_bEnable)
    {
        dc.FillRect(rcButton, &CBrush(m_crButton[m_bDrop? 0:1]));
        dc.FillRgn(&rgn, &CBrush(m_crButton[m_bDrop? 1:0]));
    }
    else
    {
        dc.FillRect(rcButton, &CBrush(m_crButton[3]));
        dc.FillRgn(&rgn, &CBrush(m_crButton[2]));
    }
    dc.FrameRect(rcButton, &CBrush(m_crButton[m_bDrop? 1:0]));
    rgn.DeleteObject();

    if (m_bDrop)
    {
        m_bDrop = FALSE;
    }
}

BOOL CSkinComboBox::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
//	return CComboBox::OnEraseBkgnd(pDC);
}

HBRUSH CSkinComboBox::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
    int nIndex = m_bEnable ? 0 : 2;
	pDC->SetBkColor(m_crBk[nIndex]);
    pDC->SetTextColor(m_crText[nIndex]);
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return m_brushBk[nIndex/2];
}

HBRUSH CSkinComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{      
    HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
    int nIndex = m_bEnable ? 0 : 2;
    pDC->SetTextColor(m_crText[nIndex]);
    pDC->SetBkColor(m_crBk[nIndex]);
    return m_brushBk[nIndex/2];
}

void CSkinComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
   if (lpMeasureItemStruct->itemID != (UINT) -1)
   {
      LPCTSTR lpszText = (LPCTSTR) lpMeasureItemStruct->itemData;
      ASSERT(lpszText != NULL);
      CSize   sz;
      CDC*    pDC = GetDC();

      sz = pDC->GetTextExtent(lpszText);

      ReleaseDC(pDC);

      lpMeasureItemStruct->itemHeight = sz.cy;
   }
}

//下拉时，按钮画下压状态
BOOL CSkinComboBox::OnDropdown() 
{
	// TODO: Add your control notification handler code here
    m_bDrop = TRUE;
    return FALSE;
}

//按钮结束下压
void CSkinComboBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bDrop = FALSE;
    Invalidate();
	CComboBox::OnLButtonUp(nFlags, point);
}

void CSkinComboBox::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
//	ModifyStyleEx(0, CBS_HASSTRINGS |CBS_OWNERDRAWVARIABLE);
	CComboBox::PreSubclassWindow();
    m_bDrawList = (BOOL)((GetStyle() & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST);
}

//接口函数

/*====================================================================
函数名  ：SetTextColor
功  能  ：设置文本颜色。
全局变量：无
输入参数：crText: 正常时的文本色；
          crHighlight:高亮显示时的背景色；
          bRepaint: 是否马上重画。
返回值  ：无
====================================================================*/
void CSkinComboBox::SetTextColor(COLORREF crText, COLORREF crHighlight, BOOL bRepaint)
{
    m_crText[0] = crText;
    m_crText[1] = crHighlight;

    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
函数名  ：SetBkColor
功  能  ：设置文本背景颜色。
全局变量：无
输入参数：crBk: 正常时的文本背景色；
          crHighlight:高亮显示时的文本背景色；
          bRepaint: 是否马上重画。
返回值  ：无
====================================================================*/
void CSkinComboBox::SetBkColor(COLORREF crBk, COLORREF crHighlight, BOOL bRepaint)
{
    m_crBk[0] = crBk;
    m_crBk[1] = crHighlight;

    if (m_brushBk[0].GetSafeHandle() != NULL)
    {
        m_brushBk[0].DeleteObject();
        m_brushBk[0].CreateSolidBrush(m_crBk[0]);
    }
    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
函数名  ：SetFrameColor
功  能  ：设置控件边框颜色。
全局变量：无
输入参数：crFrame: 边框颜色；
          bRepaint: 是否马上重画。
返回值  ：无
====================================================================*/
void CSkinComboBox::SetFrameColor(COLORREF crFrame, BOOL bRepaint)
{
    m_crFrame = crFrame;

    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
函数名  ：SetButtonColor
功  能  ：设置控件下拉按钮的颜色，设置了按钮图片时，该函数无效。
全局变量：无
输入参数：crFront: 按钮前景三角形的颜色；
          crBk: 按钮的背景色；
          crDisableFt: 失效时的按钮前景色；
          crDisableBk: 失效时的按钮背景色。
返回值  ：无
====================================================================*/
void CSkinComboBox::SetButtonColor(COLORREF crFront, COLORREF crBk, COLORREF crDisableFt, COLORREF crDisableBk)
{
    m_crButton[0] = crFront;
    m_crButton[1] = crBk;
    m_crButton[2] = crDisableFt;
    m_crButton[3] = crDisableBk;
}

/*====================================================================
函数名  ：SetButtonImage
功  能  ：设置控件下拉按钮图片。
全局变量：无
输入参数：hBitmap: 正常时按钮图片句柄；
          hDisableBitmap: 失效时的按钮图片句柄。
返回值  ：无
====================================================================*/
void CSkinComboBox::SetButtonImage(HBITMAP hBitmap, HBITMAP hDisableBitmap)
{
    if (m_bNeedFree) 
    {
        if (m_hBitmap[0] != NULL) 
        {
            ::DeleteObject(m_hBitmap[0]);
            m_hBitmap[0] = NULL;
        }
        if (m_hBitmap[1] != NULL) 
        {
            ::DeleteObject(m_hBitmap[1]);
            m_hBitmap[1] = NULL;
        }
        m_bNeedFree = FALSE;
    }

    m_hBitmap[0] = hBitmap;
    m_hBitmap[1] = hDisableBitmap;

    if (m_hBitmap == NULL)
    {
        m_sizeButton.cx = 0;
        m_sizeButton.cy = 0;
        return;
    }

    BITMAP bmp;
    GetObject(m_hBitmap[0], sizeof(bmp), &bmp);
    m_sizeButton.cx = bmp.bmWidth;
    m_sizeButton.cy = bmp.bmHeight;
}

/*====================================================================
函数名  ：SetButtonImage
功  能  ：设置控件下拉按钮图片。
全局变量：无
输入参数：nBitmap: 正常时按钮图片资源ID号；
          nDisableBitmap: 失效时的按钮图片资源ID号。
返回值  ：无
====================================================================*/
void CSkinComboBox::SetButtonImage(UINT nBitmap, UINT nDisableBitmap)
{
    if (nBitmap == 0)
    {
        m_hBitmap[0] = NULL;
        return;
    }

    HBITMAP hBitmap = NULL;
    HBITMAP hDisable = NULL;
    HINSTANCE hInstance = NULL;

    hInstance = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmap), RT_BITMAP);
    hBitmap = (HBITMAP)::LoadImage(hInstance, MAKEINTRESOURCE(nBitmap), 
        IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);

    if (nDisableBitmap != 0)
    {
        hInstance = AfxFindResourceHandle(MAKEINTRESOURCE(nDisableBitmap), RT_BITMAP);
        hDisable = (HBITMAP)::LoadImage(hInstance, MAKEINTRESOURCE(nDisableBitmap), 
        IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);
    }
    else
    {
        hDisable = hBitmap;
    }
    SetButtonImage(hBitmap, hDisable);

    m_bNeedFree = TRUE;
}

#define MES_UNDO        _T("撤销(&U)")
#define MES_CUT         _T("剪切(&T)")
#define MES_COPY        _T("复制(&C)")
#define MES_PASTE       _T("粘贴(&P)")
#define MES_DELETE      _T("删除(&D)")
#define MES_SELECTALL   _T("全选(&A)")

void CSkinComboBox::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
//	SetFocus();
//    CSkinMenu menu;
//    menu.CreatePopupMenu();
//
//    CWnd* pChild = GetWindow(GW_CHILD);
//    if (pChild == NULL) 
//    {
//        return;
//    }
//
//    CEdit* pEdit = NULL;
//    if (pChild->IsKindOf(RUNTIME_CLASS(CEdit))) 
//    {
//        pEdit = (CEdit*)pChild;
//    }
//    else
//    {
//        return;
//    }
//    BOOL bReadOnly = pEdit->GetStyle() & ES_READONLY;
//    DWORD dwFlags = pEdit->CanUndo() && !bReadOnly ? 0 : MF_GRAYED;
//    menu.InsertMenu(0, MF_BYPOSITION | dwFlags, EM_UNDO,
//        MES_UNDO);
//
//    menu.InsertMenu(1, MF_BYPOSITION | MF_SEPARATOR, 0);
//
//    DWORD dwSel = pEdit->GetSel();
//    dwFlags = (LOWORD(dwSel) == HIWORD(dwSel)) ? MF_GRAYED : 0;
//    menu.InsertMenu(2, MF_BYPOSITION | dwFlags, WM_COPY,
//        MES_COPY);
//
//    dwFlags = (dwFlags == MF_GRAYED || bReadOnly) ? MF_GRAYED : 0;
//    menu.InsertMenu(2, MF_BYPOSITION | dwFlags, WM_CUT,
//        MES_CUT);
//    menu.InsertMenu(4, MF_BYPOSITION | dwFlags, WM_CLEAR,
//        MES_DELETE);
//
//    dwFlags = IsClipboardFormatAvailable(CF_TEXT) &&
//        !bReadOnly ? 0 : MF_GRAYED;
//    menu.InsertMenu(4, MF_BYPOSITION | dwFlags, WM_PASTE,
//        MES_PASTE);
//
//    menu.InsertMenu(6, MF_BYPOSITION | MF_SEPARATOR, 0);
//
//    int nLen = GetWindowTextLength();
//    dwFlags = (!nLen || (LOWORD(dwSel) == 0 && HIWORD(dwSel) ==
//        nLen)) ? MF_GRAYED : 0;
//    menu.InsertMenu(7, MF_BYPOSITION | dwFlags, ME_SELECTALL,
//        MES_SELECTALL);
//    
//    menu.InsertSpaces();
//
//    menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON |
//        TPM_RIGHTBUTTON, point.x, point.y, this);
	
}


/*=============================================================================
函 数 名： staticSetBkColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crBk
           COLORREF crHighlight
           COLORREF crDisable
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  1.0			朱允荣                  创建
=============================================================================*/
void CSkinComboBox::staticSetBkColor(COLORREF crBk, COLORREF crHighlight, COLORREF crDisable)
{
    m_s_crBk[0] = crBk;
    m_s_crBk[1] = crHighlight;
    m_s_crBk[2] = crDisable;
}


/*=============================================================================
函 数 名： staticSetButtonColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crFront
           COLORREF crBk
           COLORREF crDisableFt
           COLORREF crDisableBk
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  1.0			朱允荣                  创建
=============================================================================*/
void CSkinComboBox::staticSetButtonColor(COLORREF crFront, COLORREF crBk,
                                         COLORREF crDisableFt, COLORREF crDisableBk)
{
    m_s_crButton[0] = crFront;
    m_s_crButton[1] = crBk;
    m_s_crButton[2] = crDisableFt;
    m_s_crButton[3] = crDisableBk;
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
2005/03/29  1.0			朱允荣                  创建
=============================================================================*/
void CSkinComboBox::staticSetFrameColor(COLORREF crFrame)
{
    m_s_crFrame = crFrame;
}


/*=============================================================================
函 数 名： staticSetTextColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crText
           COLORREF crHighlight
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  1.0			朱允荣                  创建
=============================================================================*/
void CSkinComboBox::staticSetTextColor(COLORREF crText, COLORREF crHighlight)
{
    m_s_crText[0] = crText;
    m_s_crText[1] = crHighlight;
}