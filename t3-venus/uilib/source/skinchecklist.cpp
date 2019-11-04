/********************************************************************
	模块名:      UILib
	文件名:      skinchecklist.cpp
	相关文件:    UILibHead.h
	文件实现功能 CheckListBox美化
    作者：       朱允荣
	版本：       1.0
------------------------------------------------------------------------
	修改记录:
	日  期		版本		修改人		走读人    修改内容
	2004/09/22	1.0			朱允荣                  创建

*********************************************************************/


#include "stdafx.h"
#include "UILibhead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LB_SETCHECK LB_MSGMAX
//////////////////////////////////////////////////////////////////////////
//CheckListBox中Check框图片。
//////////////////////////////////////////////////////////////////////////

class CNMC_AFX_CHECKLIST_STATE : public CNoTrackObject
{
public:
	CNMC_AFX_CHECKLIST_STATE();
	virtual ~CNMC_AFX_CHECKLIST_STATE();

	HBITMAP m_hbitmapCheck;
	CSize m_sizeCheck;
};

CNMC_AFX_CHECKLIST_STATE::CNMC_AFX_CHECKLIST_STATE()
{
	CBitmap bitmap;

	VERIFY(bitmap.LoadBitmap(AFX_IDB_CHECKLISTBOX_NT));

	BITMAP bm;
	bitmap.GetObject(sizeof (BITMAP), &bm);
	m_sizeCheck.cx = bm.bmWidth / 3;
	m_sizeCheck.cy = bm.bmHeight;
	m_hbitmapCheck = (HBITMAP)bitmap.Detach();
}

CNMC_AFX_CHECKLIST_STATE::~CNMC_AFX_CHECKLIST_STATE()
{
	if (m_hbitmapCheck != NULL)
		::DeleteObject(m_hbitmapCheck);
}

struct TNMC_AFX_CHECK_DATA
{
public:
	int m_nCheck;
	BOOL m_bEnabled;
	DWORD m_dwUserData;
	
	TNMC_AFX_CHECK_DATA()
	{
		m_nCheck = 0;
		m_bEnabled = TRUE;
		m_dwUserData = 0;
	};
};

PROCESS_LOCAL(CNMC_AFX_CHECKLIST_STATE, g_cNmc_afxChecklistState)
/////////////////////////////////////////////////////////////////////////////
// CSkinCheckList
COLORREF CSkinCheckList::m_s_crBk[3] = {RGB(234,236,239),           //Normal
                                        RGB(234,236,239),           //Disable
                                        GetSysColor(COLOR_HIGHLIGHT)};//Highlight
COLORREF CSkinCheckList::m_s_crText[3] = {RGB(0,0,0), RGB(0x80, 0x80, 0x80),
                                            GetSysColor(COLOR_HIGHLIGHTTEXT)};

CSkinCheckList::CSkinCheckList()
{
    for (int i = 0; i < 3; i++)
    {
        m_crBk[i] = m_s_crBk[i];
        m_crText[i] = m_s_crText[i];
    }
}

CSkinCheckList::~CSkinCheckList()
{
}


BEGIN_MESSAGE_MAP(CSkinCheckList, CCheckListBox)
	//{{AFX_MSG_MAP(CSkinCheckList)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_PAINT()
    ON_MESSAGE(LB_GETITEMDATA, OnLBGetItemData)
    ON_MESSAGE(LB_SETCHECK, OnLBSetItemCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinCheckList message handlers


/*=============================================================================
函 数 名： PreSubclassWindow
功    能： 风格设定，创建边框和滚动条。
算法实现： 
全局变量： 
参    数： 
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
void CSkinCheckList::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
    ModifyStyle(0, LBS_OWNERDRAWFIXED );

    CRect rect;
    GetWindowRect(rect);
    GetParent()->ScreenToClient(rect);
    rect.InflateRect(1,1);
    m_stFrame.Create(_T(""), SS_BLACKFRAME, rect, GetParent());
    m_stFrame.ShowWindow(SW_SHOW);
    
    DWORD dw = GetExStyle();
    SetWindowLong(m_hWnd, GWL_EXSTYLE, 
        dw & ~(WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE|WS_EX_STATICEDGE));

    InitializeFlatSB(m_hWnd);    
	FlatSB_EnableScrollBar(m_hWnd, SB_BOTH, ESB_DISABLE_BOTH);
    m_VScroll.InitScrollBar(this, SB_VERT);
    m_VScroll.UpdateThumbSize();
    
	CCheckListBox::PreSubclassWindow();
}


/*=============================================================================
函 数 名： PreDrawItemSelf
功    能： 画Check框。
算法实现： 
全局变量： 
参    数： LPDRAWITEMSTRUCT lpDIS
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
void CSkinCheckList::PreDrawItemSelf(LPDRAWITEMSTRUCT lpDIS)
{
	CNMC_AFX_CHECKLIST_STATE* pChecklistState = g_cNmc_afxChecklistState;
	
	DRAWITEMSTRUCT drawItem;
	memcpy(&drawItem, lpDIS, sizeof(DRAWITEMSTRUCT));
	
	if ((((LONG)drawItem.itemID) >= 0) &&
		((drawItem.itemAction & (ODA_DRAWENTIRE | ODA_SELECT)) != 0))
	{
		int cyItem = GetItemHeight(drawItem.itemID);
		
		CDC* pDC = CDC::FromHandle(drawItem.hDC);
		
		BOOL fDisabled = !IsWindowEnabled() || !IsEnabled(drawItem.itemID);
        
        COLORREF crBK;
        if (fDisabled) 
        {
            crBK = m_crBk[1];
            pDC->SetTextColor(m_crText[1]);
        }
        else if ((drawItem.itemState & ODS_SELECTED) && !fDisabled)
        {
            crBK = m_crBk[2];
            pDC->SetTextColor(m_crText[2]);
        }
        else
        {
            crBK = m_crBk[0];
            pDC->SetTextColor(m_crText[0]);
        }
        pDC->SetBkColor(crBK);
		
		CDC bitmapDC;
		if(bitmapDC.CreateCompatibleDC(pDC))
		{
			int nCheck = GetCheck(drawItem.itemID);
			HBITMAP hOldBitmap = (HBITMAP)::SelectObject(bitmapDC.m_hDC, pChecklistState->m_hbitmapCheck);
			
			CRect rectCheck = drawItem.rcItem;
			rectCheck.left += 1;
			rectCheck.top += 1 + max(0, (cyItem - pChecklistState->m_sizeCheck.cy) / 2);
			rectCheck.right = rectCheck.left + pChecklistState->m_sizeCheck.cx;
			rectCheck.bottom = rectCheck.top + pChecklistState->m_sizeCheck.cy;
			
			CRect rectItem = drawItem.rcItem;
			rectItem.right = rectItem.left + pChecklistState->m_sizeCheck.cx + 2;
			
			CRect rectCheckBox = OnGetCheckPosition(rectItem, rectCheck);
			
			ASSERT(rectCheck.IntersectRect(rectItem, rectCheckBox));
			ASSERT((rectCheck == rectCheckBox) && (rectCheckBox.Size() == pChecklistState->m_sizeCheck));
			
            pDC->FillSolidRect(&rectItem, crBK);
			
			pDC->BitBlt(rectCheckBox.left, rectCheckBox.top,
				pChecklistState->m_sizeCheck.cx, pChecklistState->m_sizeCheck.cy, &bitmapDC,
				pChecklistState->m_sizeCheck.cx  * nCheck, 0, SRCCOPY);
			
			::SelectObject(bitmapDC.m_hDC, hOldBitmap);
		}
	}
	
	if(drawItem.itemData != 0 && drawItem.itemData != LB_ERR)
	{
		TNMC_AFX_CHECK_DATA* pState = (TNMC_AFX_CHECK_DATA*)drawItem.itemData;
		drawItem.itemData = pState->m_dwUserData;
	}
	drawItem.rcItem.left = drawItem.rcItem.left + pChecklistState->m_sizeCheck.cx + 2;
	
	DrawItem(&drawItem);
}


BOOL CSkinCheckList::OnChildNotify(UINT message,
									 WPARAM wParam,
									 LPARAM lParam,
									 LRESULT* pResult)
{
	switch (message)
	{
	case WM_DRAWITEM:
		ASSERT(pResult == NULL);       // no return value expected
		PreDrawItemSelf((LPDRAWITEMSTRUCT)lParam);
		break;
	case WM_MEASUREITEM:
		ASSERT(pResult == NULL);       // no return value expected
		PreMeasureItem((LPMEASUREITEMSTRUCT)lParam);
		break;
	case WM_COMPAREITEM:
		ASSERT(pResult != NULL);       // return value expected
		*pResult = PreCompareItem((LPCOMPAREITEMSTRUCT)lParam);
		break;
	case WM_DELETEITEM:
		ASSERT(pResult == NULL);       // no return value expected
		PreDeleteItem((LPDELETEITEMSTRUCT)lParam);
		break;
	default:
		return CListBox::OnChildNotify(message, wParam, lParam, pResult);
	}
	return TRUE;
}


/*=============================================================================
函 数 名： DrawItem
功    能： 画某一个条目文字
算法实现： 
全局变量： 
参    数： LPDRAWITEMSTRUCT lpDIS
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
void CSkinCheckList::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT((GetStyle() & (LBS_OWNERDRAWFIXED | LBS_HASSTRINGS)) ==
		(LBS_OWNERDRAWFIXED | LBS_HASSTRINGS));
	
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	
	if (((LONG)(lpDIS->itemID) >= 0) &&
		(lpDIS->itemAction & (ODA_DRAWENTIRE | ODA_SELECT)))
	{
		int cyItem = GetItemHeight(lpDIS->itemID);
		
		if (m_cyText == 0)
			VERIFY(cyItem >= CalcMinimumItemHeight());
		
		CString strText;
		GetText(lpDIS->itemID, strText);
		
		pDC->ExtTextOut(lpDIS->rcItem.left,
			lpDIS->rcItem.top + max(0, (cyItem - m_cyText) / 2),
			ETO_OPAQUE, &(lpDIS->rcItem), strText, strText.GetLength(), NULL);
		
	}
	
	if ((lpDIS->itemAction & ODA_FOCUS) != 0)
		pDC->DrawFocusRect(&(lpDIS->rcItem));
}


/*=============================================================================
函 数 名： OnEraseBkgnd
功    能： 刷背景色
算法实现： 
全局变量： 
参    数： CDC* pDC
返 回 值： BOOL 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
BOOL CSkinCheckList::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
  //  CRect rect;
 //   GetClientRect(rect);
 //   pDC->FillSolidRect(&rect, m_crBk[0]);

    m_stFrame.Invalidate();
 //   m_VScroll.UpdateThumbSize();
    return CCheckListBox::OnEraseBkgnd(pDC);
	return TRUE;
}


/*=============================================================================
函 数 名： OnMouseWheel
功    能： 处理鼠标滚动，刷新滚动条滑块位置
算法实现： 
全局变量： 
参    数： UINT nFlags
           short zDelta
           CPoint pt
返 回 值： BOOL 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
BOOL CSkinCheckList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	
    if (m_VScroll.IsWindowVisible()) 
    {
        m_VScroll.UpdateThumbPosition();
    }
	return CCheckListBox::OnMouseWheel(nFlags, zDelta, pt);
}


/*=============================================================================
函 数 名： OnShowWindow
功    能： 显示状态改变时，同步改变边框和滚动条。
算法实现： 
全局变量： 
参    数： BOOL bShow
           UINT nStatus
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
void CSkinCheckList::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CCheckListBox::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
    if (bShow) 
    {
    	m_VScroll.ShowWindow(m_VScroll.GetOldShowState());
        m_stFrame.ShowWindow(SW_SHOW);
    }
    else
    {
        m_VScroll.ShowWindow(SW_HIDE);
        m_stFrame.ShowWindow(SW_HIDE);
    }
}


/*=============================================================================
函 数 名： OnSize
功    能： 重新设定滚动条尺寸。
算法实现： 
全局变量： 
参    数： UINT nType
           int cx
           int cy
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
void CSkinCheckList::OnSize(UINT nType, int cx, int cy) 
{
	CCheckListBox::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect, rcList(0, 0, cx, cy);
    MapWindowPoints(GetParent(), rcList);
 	if (m_VScroll.GetOldShowState())
     {
         m_VScroll.GetClientRect(rect);
         m_VScroll.SetWindowPos(NULL, rcList.right, rcList.top, rect.Width(), cy, SWP_NOZORDER);
         m_VScroll.UpdateRect();
         m_VScroll.UpdateThumbSize();
         m_VScroll.Invalidate();
         rcList.right += rect.Width();
     }
    else
    {
         m_VScroll.GetClientRect(rect);
         m_VScroll.SetWindowPos(NULL, rcList.right-rect.Width(), rcList.top, rect.Width(), cy, SWP_NOZORDER);
    }
    
    rcList.InflateRect(1, 1, 1, 1);
    m_stFrame.MoveWindow(rcList, TRUE);
}


/*=============================================================================
函 数 名： OnMove
功    能： 重新设定滚动条位置。
算法实现： 
全局变量： 
参    数： int x
           int y
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
void CSkinCheckList::OnMove(int x, int y) 
{
	CCheckListBox::OnMove(x, y);
	
	// TODO: Add your message handler code hereCRect rcList;
    CRect rectV, rcList;
    GetWindowRect(rcList);
    GetParent()->ScreenToClient(rcList);

    m_VScroll.GetWindowRect(rectV);
    GetParent()->ScreenToClient(rectV);

    if (m_VScroll.GetOldShowState()) 
    {
        m_VScroll.SetWindowPos(NULL, rcList.right, rcList.top, rectV.Width(), rcList.Height(), SWP_NOZORDER);
    }
    else
    {
        m_VScroll.SetWindowPos(NULL, rcList.right-rectV.Width(), rcList.top, rectV.Width(), rcList.Height(), SWP_NOZORDER);
    }
    m_VScroll.UpdateRect();
    m_VScroll.UpdateThumbSize();
    m_VScroll.Invalidate();
	
}


void CSkinCheckList::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
    CRect rect;
    GetClientRect(rect);
    if (IsWindowEnabled()) 
    {
        dc.FillSolidRect(rect, m_crBk[0]);
    }
    else
    {
        dc.FillSolidRect(rect, m_crBk[1]);
    }
	// TODO: Add your message handler code here
    m_VScroll.UpdateThumbSize();
    
    if (GetCount() != 0) 
    {
        DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
    }
//	DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
	// Do not call CCheckListBox::OnPaint() for painting messages
}


/*=============================================================================
函 数 名： DefWindowProc
功    能： 处理消息，刷新滚动条。
算法实现： 
全局变量： 
参    数： UINT message
           WPARAM wParam
           LPARAM lParam
返 回 值： LRESULT 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
LRESULT CSkinCheckList::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
    switch (message)
    {
    case WM_KEYDOWN:
        switch (wParam) 
        {
        case VK_NEXT:
        case VK_PRIOR:
        case VK_DOWN:
        case VK_UP:
            m_VScroll.UpdateThumbPosition();
        	break;
        default:
        	break;
        }
        break;
    case LB_ADDSTRING:
    case LB_INSERTSTRING:
    case LB_DELETESTRING:
        m_VScroll.UpdateThumbSize();
        break;
    default:
        break;
    }
	return CCheckListBox::DefWindowProc(message, wParam, lParam);
}

//接口

/*=============================================================================
函 数 名： SetBkColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crNormal
           COLORREF crDisable
           COLORREF crHilight
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
void CSkinCheckList::SetBkColor(COLORREF crNormal, COLORREF crDisable, COLORREF crHilight)
{
    m_crBk[0] = crNormal;
    m_crBk[1] = crDisable;
    m_crBk[2] = crHilight;
}


/*=============================================================================
函 数 名： SetTextColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crNormal
           COLORREF crDisable
           COLORREF crHilight
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
void CSkinCheckList::SetTextColor(COLORREF crNormal, COLORREF crDisable, COLORREF crHilight)
{
    m_crText[0] = crNormal;
    m_crText[1] = crDisable;
    m_crText[2] = crHilight;
}


/*=============================================================================
函 数 名： SetCheckBMP
功    能： 
算法实现： 
全局变量： 
参    数： UINT nCheck
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2004/9/22   3.0			朱允荣                  创建
=============================================================================*/
void CSkinCheckList::SetCheckBMP(UINT nCheck)
{ 
    CNMC_AFX_CHECKLIST_STATE* pChecklistState = g_cNmc_afxChecklistState;
    if (pChecklistState->m_hbitmapCheck != NULL) 
    {
        ::DeleteObject(pChecklistState->m_hbitmapCheck);
    }
	CBitmap bitmap;

	VERIFY(bitmap.LoadBitmap(nCheck));

	BITMAP bm;
	bitmap.GetObject(sizeof(BITMAP), &bm);
	pChecklistState->m_sizeCheck.cx = bm.bmWidth / 3;
	pChecklistState->m_sizeCheck.cy = bm.bmHeight;
	pChecklistState->m_hbitmapCheck = (HBITMAP)bitmap.Detach();
}


/*=============================================================================
函 数 名： OnLBGetItemData
功    能： 
算法实现： 
全局变量： 
参    数： WPARAM wParam
           LPARAM lParam
返 回 值： LRESULT 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/01/24  3.6			朱允荣                  创建
=============================================================================*/
LRESULT CSkinCheckList::OnLBGetItemData(WPARAM wParam, LPARAM lParam)
{
    LRESULT lResult = DefWindowProc(LB_GETITEMDATA, wParam, lParam);
    if (lResult != LB_ERR)
    {
        TNMC_AFX_CHECK_DATA* pState = (TNMC_AFX_CHECK_DATA*)lResult;
        if (pState == NULL)
        return 0; // default
        if (lParam == 1)
        {
            lResult = pState->m_nCheck;
        }
        else
        {
            lResult = pState->m_dwUserData;
        }
    }
    return lResult;
}

LRESULT CSkinCheckList::OnLBSetItemCheck(WPARAM wParam, LPARAM lParam)
{
    SetCheck(wParam, lParam);
    return 0;
}


/*=============================================================================
函 数 名： staticSetBkColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crNormal
           COLORREF crDisable
           COLORREF crHilight
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  3.6			朱允荣                  创建
=============================================================================*/
void CSkinCheckList::staticSetBkColor(COLORREF crNormal, COLORREF crDisable,
                                      COLORREF crHilight)
{
    m_s_crBk[0] = crNormal;
    m_s_crBk[1] = crDisable;
    m_s_crBk[2] = crHilight;
}


/*=============================================================================
函 数 名： staticSetTextColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crNormal
           COLORREF crDisable
           COLORREF crHilight
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  3.6			朱允荣                  创建
=============================================================================*/
void CSkinCheckList::staticSetTextColor(COLORREF crNormal, COLORREF crDisable,
                                        COLORREF crHilight)
{
    m_s_crText[0] = crNormal;
    m_s_crText[1] = crDisable;
    m_s_crText[2] = crHilight;
}
