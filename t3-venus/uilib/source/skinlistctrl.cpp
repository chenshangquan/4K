/********************************************************************
	模块名:      UILib
	文件名:      skinlistctrl.cpp
	相关文件:    UILIbHead.h
	文件实现功能 
    作者：       朱允荣
	版本：       1.0
--------------------------------------------------------------------------------
	修改记录:
	日  期		版本		修改人		走读人    修改内容
	2004/4/8	1.0			朱允荣               

*********************************************************************/

#include "stdafx.h"
#include "UILibHead.h"
#include "changelandef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct tagItemData
{
    DWORD m_dwData;
    UINT  m_nIndex;
} TITEMDATA;

COLORREF CSkinListCtrl::m_s_crBk[4] = {RGB(234,236,239), RGB(234,236,239),
                                       GetSysColor(COLOR_HIGHLIGHT), RGB(169,185,213)};
COLORREF CSkinListCtrl::m_s_crText[4] = {RGB(0,0,0), RGB(0,0,0),
                                       GetSysColor(COLOR_HIGHLIGHTTEXT), RGB(55,55,0)};

/////////////////////////////////////////////////////////////////////////////
// CSkinListCtrl
IMPLEMENT_DYNAMIC(CSkinListCtrl, CListCtrl)
CSkinListCtrl::CSkinListCtrl()
{
    m_nSingleColBk = -1;
    m_crSingleBk = RGB(255,255,200);

    m_bSortAscending = FALSE;
    m_nSortColumn = -1;
    m_pfn = NULL;

    m_bSort = TRUE;

    m_bHighlight = TRUE;
    m_nHighlighted = -1;

    for (int i = 0; i < CRMAX; i++)
    {
        m_crBk[i] = m_s_crBk[i];
        m_crText[i] = m_s_crText[i];
    }

    m_bReport = FALSE;
    m_wHitMask = LVHT_ONITEM;
    m_uToolTipStyle = TTS_HIDEITME;//TTS_WHOLEROW;
    m_crClient.SetRect(0,0,0,0);
    m_bHighLight = TRUE;
    m_hCursor = NULL;
    m_hOldCursor = NULL;
    m_bNewFont = FALSE;
    m_bOldHightState = TRUE;
    m_nODItemChanged = 0;
    
    m_bLockChange = FALSE;

    m_bShowFrame = TRUE;
}

CSkinListCtrl::~CSkinListCtrl()
{
    if (m_bkBrush.GetSafeHandle() != NULL)
    {
        m_bkBrush.DeleteObject();
    }

    if (m_hOldCursor != NULL)
    {
        DestroyCursor(m_hOldCursor);
    }
}


BEGIN_MESSAGE_MAP(CSkinListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CSkinListCtrl)
    ON_WM_SIZE()
    ON_WM_MOVE()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_WM_PAINT()
    ON_WM_MOUSEMOVE()
    ON_WM_SHOWWINDOW()
    ON_NOTIFY_REFLECT_EX(LVN_ITEMCHANGED, OnItemchanged)
	ON_WM_MOUSEWHEEL()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
    ON_NOTIFY_REFLECT( NM_CUSTOMDRAW, OnCustomDrawList )
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)

    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinListCtrl message handlers
void CSkinListCtrl::OnCustomDrawList ( NMHDR* pNMHDR, LRESULT* pResult )
{
    NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	static BOOL bSelected = false;

    *pResult = CDRF_DODEFAULT;
    int nRow;

    switch (pLVCD->nmcd.dwDrawStage)
    {
    case CDDS_PREPAINT:
//        if (m_bReport)
//        {
//            *pResult = CDRF_NOTIFYSUBITEMDRAW;//| CDRF_NOTIFYPOSTPAINT;
 //       }
/*
                {
                    CRect rect;
                    GetClientRect(rect);
                    CBrush br(RGB(0,0,0));
                    rect.InflateRect(0,0,0,1);
                    
                    FrameRect(pLVCD->nmcd.hdc, &rect, (HBRUSH)br.m_hObject);
                }*/
        
        
     
            *pResult = CDRF_NOTIFYITEMDRAW; 
        break;
    case CDDS_POSTPAINT:
            *pResult = CDRF_DODEFAULT; 
        break;
    case CDDS_ITEMPREPAINT:
        nRow = (int)pLVCD->nmcd.dwItemSpec;
        bSelected = IsRowSelect(m_hWnd, nRow);
        if (!IsWindowEnabled())
        {
            pLVCD->clrText = m_crText[CRDISABLE];
            pLVCD->clrTextBk = m_crBk[CRDISABLE];  
            *pResult = CDRF_DODEFAULT | CDRF_NOTIFYPOSTPAINT;
            break;
        }
        
        if (bSelected)
        {
            pLVCD->clrText = m_crText[CRSELECT];
            pLVCD->clrTextBk = m_crBk[CRSELECT];
            m_nODItemChanged = 2;
            EnableRowSelect(m_hWnd, nRow, FALSE);
        }
       else if ((nRow == m_nHighlighted) && m_bHighLight)
  //       else if (nRow == GetHotItem())
        {
            pLVCD->clrText = m_crText[CRHIGHLIGHT];
            pLVCD->clrTextBk = m_crBk[CRHIGHLIGHT];            
        }
        else
        {
            pLVCD->clrText = m_crText[CRNORMAL];
            pLVCD->clrTextBk = m_crBk[ CRNORMAL];  
        }
        *pResult = CDRF_DODEFAULT | CDRF_NOTIFYPOSTPAINT;
        break;
    case CDDS_ITEMPOSTPAINT:
        if (bSelected)
        {
            nRow = (int)pLVCD->nmcd.dwItemSpec;
            m_nODItemChanged = 2;
            EnableRowSelect(m_hWnd, nRow, TRUE);
        }
        *pResult = CDRF_DODEFAULT;
        break;
 /*
    case CDDS_SUBITEM|CDDS_ITEMPREPAINT :
         if (!IsWindowEnabled())
         {
             pLVCD->clrText = m_crText[CRDISABLE];
             pLVCD->clrTextBk = m_crBk[CRDISABLE];  
             break;
         }
 
         nRow = (int)pLVCD->nmcd.dwItemSpec;
         if (pLVCD->iSubItem == 0)
         {
             bSelected = IsRowSelect(m_hWnd, nRow);
         }
         if (bSelected&& 0)
         {
             if (pLVCD->iSubItem == -1)
             {
                 EnableRowSelect(m_hWnd, nRow, FALSE);
                 pLVCD->clrText = m_crText[CRSELECT];
                 pLVCD->clrTextBk = m_crBk[CRSELECT];
             }
         }
         else if (nRow == GetHotItem())
         {
             if (pLVCD->iSubItem == 0)
             {
                 pLVCD->clrText = m_crText[CRHIGHLIGHT];
                 pLVCD->clrTextBk = m_crBk[CRHIGHLIGHT];  
             }
         }
         else
         {
             if (pLVCD->iSubItem == m_nSingleColBk)
             {
                 pLVCD->clrTextBk = m_crSingleBk; 
             }
             else
             {
                 pLVCD->clrTextBk = m_crBk[CRNORMAL]; 
             }
             pLVCD->clrText = m_crText[CRNORMAL]; 
         }
         *pResult = CDRF_DODEFAULT | CDRF_NOTIFYPOSTPAINT;
         break;
     case CDDS_SUBITEM|CDDS_ITEMPOSTPAINT :
     
            if (bSelected && 0)
                 {
                     if (pLVCD->iSubItem == -1)
                     {
                         nRow = (int)pLVCD->nmcd.dwItemSpec;
                         EnableRowSelect(m_hWnd, nRow, TRUE);
                     }
                 }
         
         *pResult = 0;//CDRF_SKIPDEFAULT;
         break;*/
 
    default:
        break;
    }
}

void CSkinListCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
    m_nFlags |= WF_TOOLTIPS;
	CListCtrl::PreSubclassWindow();
    
    GetWindowRect(m_crClient);
    GetParent()->ScreenToClient(m_crClient);

	if (GetHeaderCtrl() != NULL)
    {
        m_Header.SubclassWindow(GetHeaderCtrl()->m_hWnd);
    }

    CRect rect = m_crClient;
    rect.InflateRect(1,1);
    m_stFrame.Create(_T(""), SS_BLACKFRAME, rect, GetParent());
  
    DWORD dw = GetStyle();
    m_bReport = ((GetStyle()&LVS_TYPEMASK) == LVS_REPORT);
    if (m_bShowFrame ) 
    {
        m_stFrame.ShowWindow(SW_SHOW);
    }
    else
    {
        m_stFrame.ShowWindow(SW_HIDE);
    }

    dw = GetExStyle();
    SetWindowLong(m_hWnd, GWL_EXSTYLE, 
        dw & ~(WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE|WS_EX_STATICEDGE));
    
    DWORD dwData = ::GetWindowLong(m_hWnd, GWL_USERDATA);
    ::SetWindowLong(m_hWnd, GWL_USERDATA, dwData | STYLE_LISTCTRL);   
  
    m_hCursor = GetHotCursor();
    m_hOldCursor = LoadCursor(NULL, IDC_ARROW);
    if (m_hOldCursor == NULL)
    {
        m_hOldCursor = CopyCursor(GetCursor());
    }
    
#ifdef USESKINSCROLL
    dw = ListView_GetExtendedListViewStyle(m_hWnd);
    if (m_bReport)
    {
        ListView_SetExtendedListViewStyle(m_hWnd, dw|LVS_EX_FULLROWSELECT  
            | LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE);
        InitializeFlatSB(m_hWnd);    
	    FlatSB_EnableScrollBar(m_hWnd, SB_BOTH, ESB_DISABLE_BOTH);
        m_VScroll.InitScrollBar(this, SB_VERT);
        m_HScroll.InitScrollBar(this, SB_HORZ);
        m_VScroll.UpdateThumbSize();
        m_HScroll.UpdateThumbSize();
    }
#endif
}

LRESULT CSkinListCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	SetHotItem(-1);
    m_nHighlighted = -1;
    Invalidate(); 
    
	return 0;
} 


void CSkinListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CListCtrl::OnMouseMove(nFlags, point);
    if (!m_bReport)
    {
        return;
    }
    if (!m_bHighLight)
    {
        if (m_hOldCursor != NULL)
        {
            SetCursor(m_hOldCursor);
        }
        return;
    }
    int nItem = HitTest(point);
    if (nItem != -1 && m_hCursor != NULL)
    {
        SetCursor(m_hCursor);
    }
    if (nItem != m_nHighlighted)
    {
        int nOld = m_nHighlighted;
        m_nHighlighted = nItem;
        SetHotItem(nItem);
        RedrawItems(nOld -1, nOld + 1);
        RedrawItems(m_nHighlighted-1, m_nHighlighted+1);
    }
}

BOOL CSkinListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
#ifdef USESKINSCROLL
    if (m_bReport)
    {
        if (m_VScroll.IsWindowVisible()) 
        {
            m_VScroll.UpdateThumbPosition();
        }
        else if (m_HScroll.IsWindowVisible()) 
        {
            m_HScroll.UpdateThumbPosition();
        }
    }
#endif
	
	return CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
}

void CSkinListCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    CRect rect;
    GetClientRect(rect);
    dc.FillRect(rect, &CBrush(m_crBk[IsWindowEnabled()? CRNORMAL:CRDISABLE]));
	// Do not call CListCtrl::OnPaint() for painting messages
#ifdef USESKINSCROLL
    if (m_bReport)
    {
        m_HScroll.UpdateThumbSize();
        m_VScroll.UpdateThumbSize();
    }
#endif
    m_stFrame.Invalidate();
    DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
}

BOOL CSkinListCtrl::OnToolTipText(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
    TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;

    *pResult = 0;
	//Ignore messages from the built in tooltip, we are processing them internally
	if ((pNMHDR->idFrom == (UINT)m_hWnd) &&
		 ( ((pNMHDR->code == TTN_NEEDTEXTA) && (pTTTA->uFlags & TTF_IDISHWND))
          ||((pNMHDR->code == TTN_NEEDTEXTW) && (pTTTW->uFlags & TTF_IDISHWND)) ))
    {
      return FALSE;
    }

    const MSG* pMessage = GetCurrentMessage();
    ASSERT(pMessage);
    CPoint pt = pMessage->pt;
    ScreenToClient(&pt);
    
    int nItem, nSubItem;
    LVHITTESTINFO lvhitTestInfo;
    lvhitTestInfo.pt = pt;
    nItem = SubItemHitTest(&lvhitTestInfo);
    if (nItem < 0) 
    {
        return TRUE;
    }

  
    if (lvhitTestInfo.flags & m_wHitMask)
    {
        nSubItem = lvhitTestInfo.iSubItem;
        CString strTip = GetTooltipText(nItem, nSubItem);
        if (strTip.IsEmpty())
        {
            return FALSE;
        }

        if (strTip.Left(1) != "0")
        {
            int a = 0;
        }

         ::SendMessage(pNMHDR->hwndFrom,TTM_SETMAXTIPWIDTH, 0, 300);
        if (pNMHDR->code == TTN_NEEDTEXTA)
            lstrcpyn(pTTTA->szText, strTip, 80);
	    else
//	        MultiByteToWideChar(CP_THREAD_ACP, MB_PRECOMPOSED, strTip, 80, pTTTW->szText, 80);
            _mbstowcsz(pTTTW->szText, strTip, 80);  //  wanghao 2005/03/15 解决乱码问题

    }

    return FALSE;
}

int CSkinListCtrl::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
    LVHITTESTINFO lvhitTestInfo;

	lvhitTestInfo.pt	= point;

	int nItem = ListView_SubItemHitTest(m_hWnd,	&lvhitTestInfo);
	int nSubItem = lvhitTestInfo.iSubItem;

	UINT nFlags =   lvhitTestInfo.flags;

   //nFlags is 0 if the SubItemHitTest fails
   //Therefore, 0 & <anything> will equal false
   if (nFlags & m_wHitMask)
   {
      //If it did fall on a list item,
      //and it was also hit one of the
      //item specific sub-areas we wish to show tool tips for

      //Get the client (area occupied by this control
      RECT rcClient;
      GetClientRect( &rcClient );

      //Fill in the TOOLINFO structure
      pTI->hwnd = m_hWnd;
      pTI->uId = (UINT) (nItem * 100 + nSubItem+1);
      pTI->lpszText = LPSTR_TEXTCALLBACK;
      pTI->rect = rcClient;
      pTI->uFlags |= TTF_DI_SETITEM | TTF_SUBCLASS  ;
        CString strTip = GetTooltipText(nItem, nSubItem);
      
      if (!strTip.IsEmpty())
      {
          pTI->lpszText = new char[strTip.GetLength() + 1];
          strcpy(pTI->lpszText, strTip);
      }

      return pTI->uId; //By returning a unique value per listItem,
                       //we ensure that when the mouse moves over another list item,
                       //the tooltip will change
   }
   else
    {
      //Otherwise, we aren't interested, so let the message propagate
      return -1;
   }
}

CString CSkinListCtrl::GetTooltipText(int nItem, int nSubItem) const
{
    CString str = _T("");

    if (!m_bReport || m_Header.m_hWnd == NULL)
    {
        return str + GetItemText(nItem, 0);
    }

    switch (m_uToolTipStyle)
    {
    case TTS_WHOLEROW:
        {
            str = m_Header.GetItemText(0) + ":";
            str += GetItemText(nItem, 0);
            for (int i=1; i<m_Header.GetItemCount(); i++)
            {
                str += "\r\n";
                str += m_Header.GetItemText(i) + ":";
                str += GetItemText(nItem, i);
            }
        }
        break;
    case TTS_HIDEITME:
        {
            CDC* pDC = CDC::FromHandle(::GetWindowDC(m_hWnd));
            if (pDC == NULL)
            {
                return str;
            }
            CFont* pFont = pDC->SelectObject(GetFont());
            str = GetItemText(nItem, nSubItem);
          CRect rect;
   //         GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rect);

	//    RECT rect;
	    rect.top = nSubItem;
	    rect.left = LVIR_LABEL;
	    ::SendMessage(m_hWnd, LVM_GETSUBITEMRECT,
		    nItem, (LPARAM) &rect);


            int dx = pDC->GetTextExtent(str).cx;
            if ( dx - rect.Width() < -11)
            {
                str = _T("");
            }

            pDC->SelectObject(pFont);

            ::ReleaseDC( m_hWnd, pDC->GetSafeHdc() );
        }
        break;
    default:
        break;
    }
/**/
   return str;
}

void CSkinListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	// TODO: Add your control notification handler code here
    if (!m_bSort)
    {
        return;
    }

	const int nColumn = pNMListView->iSubItem;
    if (nColumn == m_nSortColumn)
    {
        m_bSortAscending = !m_bSortAscending;
    }
    else
    {
        m_nSortColumn = nColumn;
    }
        ResetIndex();

    m_Header.SetSortArrow(m_nSortColumn, m_bSortAscending);
    SortItems(MyCompare, (DWORD)this);
}

void CSkinListCtrl::ResortItem(int nItem)
{
    if (!m_bSort)
    {
        return;
    }
    if (nItem == -1 && m_nSortColumn == -1)
    {
        return;
    }

    if (nItem != -1)
    {
        if (nItem == m_nSortColumn)
        {
            m_bSortAscending = !m_bSortAscending;
        }
        else
        {
            m_nSortColumn = nItem;
        }
    }
        
    ResetIndex();
    m_Header.SetSortArrow(m_nSortColumn, m_bSortAscending);

    SortItems(MyCompare, (DWORD)this);
}

int CALLBACK CSkinListCtrl::MyCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamData)
{
    CSkinListCtrl* pList = (CSkinListCtrl*)lParamData;
    TITEMDATA* pData1 = reinterpret_cast<TITEMDATA*>(lParam1);
    TITEMDATA* pData2 = reinterpret_cast<TITEMDATA*>(lParam2);

    if (pList->m_pfn != NULL)
    {
        return pList->m_bSortAscending ? pList->m_pfn(pData1->m_dwData, pData2->m_dwData, pList->m_pVoid, pList->m_nSortColumn)
            : pList->m_pfn(pData2->m_dwData, pData1->m_dwData,pList->m_pVoid,pList->m_nSortColumn);
    }
    
    CString str1 = pList->GetItemText(pData1->m_nIndex, pList->m_nSortColumn);
    CString str2 = pList->GetItemText(pData2->m_nIndex, pList->m_nSortColumn);

    return (pList->m_bSortAscending ? str1.Compare(str2) : str2.Compare(str1));
}

BOOL CSkinListCtrl::IsRowSelect(HWND hWnd, int row)
{
    return ListView_GetItemState(hWnd, row, LVIS_SELECTED) != 0;
}

void CSkinListCtrl::EnableRowSelect(HWND hWnd, int row, BOOL bSelected)
{
    ListView_SetItemState(hWnd, row, bSelected? 0xff: 0, LVIS_SELECTED);
}


void CSkinListCtrl::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CListCtrl::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
    if (bShow)
    {        
        if (m_bReport) 
        {
            m_HScroll.ShowWindow(m_HScroll.GetOldShowState());
            m_VScroll.ShowWindow(m_VScroll.GetOldShowState());
        }
        m_stFrame.ShowWindow(m_bShowFrame? SW_SHOW: SW_HIDE);
    }
    else
    {
        if (m_bReport) 
        {
            m_HScroll.ShowWindow(SW_HIDE);
            m_VScroll.ShowWindow(SW_HIDE);
        }
        m_stFrame.ShowWindow(SW_HIDE);
    }
}

//接口函数

/*====================================================================
函数名	：    SetCompareFun
功能		：设置比较回调函数，用于排序。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：pfnCompare:比较函数名。该函数的声明必须为
                         static int CALLBACK FunName(LPARAM,LPARAM,LPARAM,LPARAM);
                         前两个参数为比较的数据（由SetItemData设置），
                         第三个为设置比较函数时传递的参数（即本函数的第二个参数lparam）
                         第四个为当前排序的列。
              lparam:可以随回调函数传回的参数。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetCompareFun(PFNNEWCOMPARE pfnCompare, LPARAM lparam)
{
    m_pfn = pfnCompare;
    m_pVoid = lparam;
}

/*====================================================================
函数名	：    EnableSort
功能		：是否启动排序功能
算法实现	：（可选项）
引用全局变量：无
输入参数说明：bEnable:是否排序。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::EnableSort(BOOL bEnable)
{
    m_bSort = bEnable;
    if (!bEnable)
    {
        m_Header.SetSortArrow(-1, m_bSortAscending);
    }
    else
    {
        m_Header.SetSortArrow(m_nSortColumn, m_bSortAscending);
    }
}

int CSkinListCtrl::InsertColumn(int nCol, const LVCOLUMN* pColumn)
{
	int nRetVal=CListCtrl::InsertColumn(nCol,pColumn);

	if (nRetVal != -1 && m_bReport)
	{
		HDITEM hdr;
		memset(&hdr,0,sizeof(HDITEM));

		hdr.mask=HDI_FORMAT;
		m_Header.GetItem(nRetVal,&hdr);
		hdr.fmt|= HDF_OWNERDRAW;

		m_Header.SetItem(nRetVal,&hdr);
	}
	return nRetVal;
}

int CSkinListCtrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
	int nFormat, int nWidth , int nSubItem)
{
	int nRetVal=CListCtrl::InsertColumn(nCol,lpszColumnHeading,nFormat,nWidth,nSubItem);

	if (nRetVal != -1 && m_bReport)
	{
	
		HDITEM hdr;
		memset(&hdr,0,sizeof(HDITEM));

		hdr.mask=HDI_FORMAT;
		m_Header.GetItem(nRetVal,&hdr);
		hdr.fmt|= HDF_OWNERDRAW;

		m_Header.SetItem(nRetVal,&hdr);
	}
	return nRetVal;
}

/*====================================================================
函数名	：    SetTitleFont
功能		：设置标题栏的字体
算法实现	：（可选项）
引用全局变量：无
输入参数说明：pFont:设置的字体的指针。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetTitleFont(CFont *pFont)
{
    m_Header.SetFont(pFont);
//    m_bNewFont = TRUE;
    Invalidate();
}

/*====================================================================
函数名	：    SetTitleTextColor
功能		：设置标题栏字体的颜色
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crText:标题栏字体的颜色
              bRepaint:是否马上重画。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetTitleTextColor(COLORREF crText, BOOL bRepaint)
{
    m_Header.SetTextColor(crText, bRepaint);
}

/*====================================================================
函数名	：    SetTitleBkColor
功能		：设置标题栏的背景色。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crBk:设置的标题栏背景色
              bRepaint:是否马上重画。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetTitleBkColor(COLORREF crBk, BOOL bRepaint)
{
    m_Header.SetBkColor(crBk, bRepaint);
}


/*====================================================================
函数名	：    SetTitleFrameColor
功能		：设置标题栏边框颜色
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crFrame:设置的标题栏边框色
              bRepaint:是否马上重画。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetTitleFrameColor(COLORREF crFrame, BOOL bRepaint)
{
    m_Header.SetFrameColor(crFrame, bRepaint);
}


/*====================================================================
函数名	：    SetTitleDivideColor
功能		：设置标题栏分割竖线的颜色和风格
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crDivide:设置的标题栏分割竖线的颜色
              npenStyel:竖线的风格：PS_SOLID:实心；PS_DOT：点线。
              bRepaint:是否马上重画。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetTitleDivideColor(COLORREF crDivide, int npenStyle, BOOL bRepaint)
{
    m_Header.SetDivideColor(crDivide, npenStyle, bRepaint);
}

/*====================================================================
函数名	：    SetTextColor
功能		：设置下面内容的文本颜色。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crText:有效时的文本颜色。
              crDisable:失效时的文本颜色。
              bRepaint:是否马上重画。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetTextColor(COLORREF crText, COLORREF crDisable, BOOL bRepaint)
{
    m_crText[0] = crText;
    m_crText[1] = crDisable;
    CListCtrl::SetTextColor(crText);

    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
函数名	：    SetTextBkColor
功能		：设置下面内容的背景颜色。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crBk:有效时的背景颜色。
              crDisable:失效时的背景颜色。
              bRepaint:是否马上重画。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetTextBkColor(COLORREF crBk, COLORREF crDisable, BOOL bRepaint)
{
    m_crBk[0] = crBk;
    m_crBk[1] = crDisable;

    if (bRepaint)
    {
        Invalidate();
    }

}

/*====================================================================
函数名	：    SetTextFont
功能		：设置内容的字体。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：pFont:字体指针。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetTextFont(CFont *pFont)
{
    CFont* pOld = m_Header.GetFont();
    SetFont(pFont);
    SetTitleFont(pFont);
}

/*====================================================================
函数名	：    EnableHighlight
功能		：设置光标下的行是否可以自动改变背景色。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：bHighlight:是否启动该功能。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::EnableHighlight(BOOL bHighlight)
{
    m_bHighLight = bHighlight;
  
    DWORD style = ListView_GetExtendedListViewStyle(m_hWnd);
    if (bHighlight)
    {
        ListView_SetExtendedListViewStyle(m_hWnd, style|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT);
    }
    else
    {
         style &= ~(LVS_EX_TWOCLICKACTIVATE|LVS_EX_ONECLICKACTIVATE);
         ListView_SetExtendedListViewStyle(m_hWnd, style);
    }

}

/*====================================================================
函数名	：    EnableHeadDragDrop
功能		：是否允许标题拖拽换位
算法实现	：（可选项）
引用全局变量：无
输入参数说明：bEable:是否允许。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::EnableHeadDragDrop(BOOL bEnable)
{
    DWORD style = ListView_GetExtendedListViewStyle(m_hWnd);
    if (bEnable)
    {
        ListView_SetExtendedListViewStyle(m_hWnd, style|LVS_EX_HEADERDRAGDROP);
    }
    else
    {
         style &= ~LVS_EX_HEADERDRAGDROP;
         ListView_SetExtendedListViewStyle(m_hWnd, style);
    }    
}

/*====================================================================
函数名	：    SetSelectColor
功能		：设置被选中的行的字体及背景色。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crText:字体颜色
              crBk:背景色
              bRepaint:是否马上重画。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetSelectColor(COLORREF crText, COLORREF crBk, BOOL bRepaint)
{
    if (crText != -1)
    {
        m_crText[CRSELECT] = crText;
    }

    if (crBk != -1)
    {
        m_crBk[CRSELECT] = crBk;
    }

    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
函数名	：    SetHighlightColor
功能		：设置高亮显示的文字及背景颜色
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crText:字体颜色
              crBk:背景色
              bRepaint:是否马上重画。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetHighlightColor(COLORREF crText, COLORREF crBk, BOOL bRepaint)
{
    if (crText != -1)
    {
        m_crText[CRHIGHLIGHT] = crText;
    }

    if (crBk != -1)
    {
        m_crBk[CRHIGHLIGHT] = crBk;
    }

    if (bRepaint)
    {
        Invalidate();
    }

}

/*====================================================================
函数名	：    SetToolTipStyle
功能		：设置Tooltips提示方式。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：nStyle: TTS_WHOLEROW表示提示整行内容, TTS_HIDEITME表示只提示不能完全显示的单元格
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetToolTipStyle(UINT nStyle)
{
    m_uToolTipStyle = nStyle;
    EnableToolTips();
}

/*====================================================================
函数名	：    SetColumnBkColor
功能		：设置单列的背景色
算法实现	：（可选项）
引用全局变量：无
输入参数说明：nColnum:被单独设颜色的列
              crBk:该列的背景色。
              bRepaint:是否马上重画。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetColumnBkColor(int nColnum, COLORREF crBk, BOOL bRepaint)
{
    m_nSingleColBk = nColnum;
    m_crSingleBk = crBk;

    if (bRepaint)
    {
        Invalidate();
    }
}


/*====================================================================
函数名	：    SetFrameColor
功能		：设置边框的颜色
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crFrame:边框的颜色。
              bRepaint:是否马上重画。
              bShow: 是否显示边框。
返回值说明：  无
====================================================================*/
void CSkinListCtrl::SetFrameColor(COLORREF crFrame, BOOL bRepaint, BOOL bShow)
{
    m_bShowFrame = bShow;
    if (m_stFrame.GetSafeHwnd() != NULL) 
    {
        m_stFrame.ShowWindow(m_bShowFrame? SW_SHOW: SW_HIDE);
    }
       
    m_stFrame.SetFrameColor(crFrame, bRepaint);

}

#ifdef USESKINSCROLL
void CSkinListCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CListCtrl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
    CRect rect, rcList(0, 0, cx, cy);
    MapWindowPoints(GetParent(), rcList);
    
    if (!m_bReport)
    {
        m_crClient = rcList;
        rect = m_crClient;
        rect.InflateRect(1, 1, 1, 1);
        m_stFrame.MoveWindow(rect, TRUE);
        return;
    }
 	if (m_VScroll.GetOldShowState())
     {
         m_VScroll.GetClientRect(rect);
         m_VScroll.SetWindowPos(NULL, rcList.right, rcList.top, rect.Width(), cy, SWP_NOZORDER);
         m_VScroll.UpdateRect();
         m_VScroll.UpdateThumbSize();
         m_VScroll.Invalidate();
         m_crClient.right = m_crClient.left + cx + rect.Width();
     }
    else
    {
         m_VScroll.GetClientRect(rect);
         m_VScroll.SetWindowPos(NULL, rcList.right-rect.Width(), rcList.top, rect.Width(), cy, SWP_NOZORDER);
         m_crClient.right = m_crClient.left + cx;
    }
  
 	if (m_HScroll.GetOldShowState())
     {
         m_HScroll.GetClientRect(rect);
         m_HScroll.SetWindowPos(NULL, rcList.left, rcList.bottom, cx, rect.Height(), SWP_NOZORDER);
         m_HScroll.UpdateRect();
         m_HScroll.UpdateThumbSize();
         m_HScroll.Invalidate();
         m_crClient.bottom = m_crClient.top + cy + rect.Height();
     }
    else
    {
         m_HScroll.GetClientRect(rect);
         m_HScroll.SetWindowPos(NULL, rcList.left, rcList.bottom - rect.Height(), cx, rect.Height(), SWP_NOZORDER);
         m_crClient.bottom = m_crClient.top + cy;
    }
  

    rect = m_crClient;

    rect.InflateRect(1, 1, 1, 1);
    m_stFrame.MoveWindow(rect, TRUE);
 
}

void CSkinListCtrl::OnMove(int x, int y) 
{
	CListCtrl::OnMove(x, y);
	
	// TODO: Add your message handler code here
    CRect rcList;
    CRect rectV, rectH;
    GetWindowRect(rcList);
    GetParent()->ScreenToClient(rcList);

    m_crClient = rcList;


	if (!m_bReport)
    {
        rcList.InflateRect(1, 1, 1, 1);
        m_stFrame.MoveWindow(rcList, TRUE);
        return;
    }

    m_VScroll.GetWindowRect(rectV);
    m_HScroll.GetWindowRect(rectH);
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

    // 	m_VScroll.MoveWindow(rect.left+x, rect.top+y, rect.Width(), rect.Height());
    if (m_HScroll.GetOldShowState()) 
    {
        m_HScroll.SetWindowPos(NULL, rcList.left, rcList.bottom, rcList.Width(), rectH.Height(), SWP_NOZORDER);
    }
    else
    {
        m_HScroll.SetWindowPos(NULL, rcList.left, rcList.bottom-rectH.Height(), rcList.Width(), rectH.Height(), SWP_NOZORDER);
    }
    m_HScroll.UpdateRect();
    m_HScroll.UpdateThumbSize();
    m_HScroll.Invalidate();

    rcList.InflateRect(1, 1, 1, 1);
    m_stFrame.MoveWindow(rcList, TRUE);
}

#endif

#ifdef USESKINSCROLL
void CSkinListCtrl::SetScrollArrowColor(COLORREF crBk, COLORREF crArrow, COLORREF crFrame, BOOL bRepaint)
{
    m_VScroll.SetArrowColor(crArrow, crBk, bRepaint);
    m_HScroll.SetArrowColor(crArrow, crBk, bRepaint);
    m_VScroll.SetThumbColor(crBk, crFrame, bRepaint);
    m_HScroll.SetThumbColor(crBk, crFrame, bRepaint);
}
#endif 

#ifdef USESKINSCROLL
void CSkinListCtrl::SetScrollBkColor(COLORREF crFrom, COLORREF crTo, BOOL bRepaint)
{

    m_VScroll.SetChannelBk(crFrom, crTo, bRepaint);
    m_HScroll.SetChannelBk(crFrom, crTo, bRepaint);
 
}
#endif 

BOOL CSkinListCtrl::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
#ifdef USESKINSCROLL
    if (m_bReport)
    {
        m_HScroll.UpdateThumbSize();
        m_VScroll.UpdateThumbSize();
    }
#endif
    if ((m_nODItemChanged > 0) || m_bLockChange)
    {
        m_nODItemChanged = 0;
        return TRUE; 
    } 
    return FALSE;
	*pResult = 0;
}



BOOL CSkinListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
 	return CListCtrl::PreTranslateMessage(pMsg);
}

LRESULT CSkinListCtrl::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
   if (//message == WM_LBUTTONDOWN ||
		//	message == WM_LBUTTONUP ||
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
			FilterToolTipMessage(&msg);
            return 0;
		}
   if (message == WM_ENABLE)
   {
       m_VScroll.EnableWindow(wParam);
       m_HScroll.EnableWindow(wParam);
       m_VScroll.Invalidate();
       m_HScroll.Invalidate();
   }
    LRESULT LRec = CListCtrl::DefWindowProc(message, wParam, lParam);
#ifdef USESKINSCROLL
	if (m_bReport)
    {
        switch(message) 
        {
        case WM_MOVE:
                
        	break;
        case LVM_DELETEALLITEMS:
            wParam = VK_LEFT;
        case WM_KEYDOWN:
            switch (wParam) 
            {
            case VK_LEFT:
            case VK_RIGHT:
                m_HScroll.UpdateThumbPosition();
        	    break;
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
        default:
        	break;
        }
    }
        
#endif
	return LRec;
}

//add for sort  [zhuyr][6/16/2004]

BOOL CSkinListCtrl::SetItemData(int nItem, DWORD dwData)
{
    if (nItem > GetItemCount()) 
    {
        return FALSE;
    }
    TITEMDATA* pData = reinterpret_cast<TITEMDATA*>(CListCtrl::GetItemData(nItem));
    
    if (NULL == pData) 
    {
        return FALSE;
    }
    pData->m_dwData = dwData;

    return TRUE;
}

BOOL CSkinListCtrl::SetItem( const LVITEM* pItem )
{
    int nItem = pItem->iItem;
    if (nItem > GetItemCount()) 
    {
        return FALSE;
    }
    TITEMDATA* pData = reinterpret_cast<TITEMDATA*>(CListCtrl::GetItemData(nItem));
    if (NULL == pData) 
    {
        return FALSE;
    }
    if (pItem->mask&LVIF_PARAM) 
    {
        pData->m_dwData = pItem->lParam;
    }
    
    return CListCtrl::SetItem(pItem);
}

BOOL CSkinListCtrl::SetItem( int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem, int nImage, UINT nState, UINT nStateMask, LPARAM lParam )
{    
	ASSERT(::IsWindow(m_hWnd));
	ASSERT((GetStyle() & LVS_OWNERDATA)==0);
    
    if (nItem > GetItemCount()) 
    {
        return FALSE;
    }
    TITEMDATA* pData = reinterpret_cast<TITEMDATA*>(CListCtrl::GetItemData(nItem));
    if (nMask&LVIF_PARAM)
    {
        pData->m_dwData = lParam;
    }

	LVITEM lvi;
	lvi.mask = nMask;
	lvi.iItem = nItem;
	lvi.iSubItem = nSubItem;
	lvi.stateMask = nStateMask;
	lvi.state = nState;
	lvi.pszText = (LPTSTR) lpszItem;
	lvi.iImage = nImage;
	lvi.lParam = (DWORD)pData;
	return (BOOL) ::SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)&lvi);
}

int CSkinListCtrl::InsertItem(const LVITEM *pItem)
{
    int nItem = CListCtrl::InsertItem(pItem);
    if (nItem >= 0) 
    {
        TITEMDATA* pData = new TITEMDATA;
        if (pData != NULL) 
        {
            pData->m_dwData = pItem->lParam;
            m_bLockChange = TRUE;
            CListCtrl::SetItemData(nItem, (DWORD)pData);
            m_bLockChange = FALSE;
        }
    }
    return nItem;
}

int CSkinListCtrl::InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask, int nImage, LPARAM lParam)
{
    int nTItem = CListCtrl::InsertItem(nMask, nItem, lpszItem, nState, nStateMask, nImage, lParam);
    if (nTItem >= 0) 
    {
        TITEMDATA* pData = new TITEMDATA;
        if (pData != NULL) 
        {
            pData->m_dwData = lParam;
            m_bLockChange = TRUE;
            CListCtrl::SetItemData(nTItem, (DWORD)pData);
            m_bLockChange = FALSE;
        }
    }
    return nTItem;
}

int CSkinListCtrl::InsertItem(int nItem, LPCTSTR lpszItem)
{
    return InsertItem(LVIF_TEXT, nItem, lpszItem, 0, 0, 0, 0);
}

int CSkinListCtrl::InsertItem(int nItem, LPCTSTR lpszItem, int nImage)
{
    return InsertItem(LVIF_TEXT|LVIF_IMAGE, nItem, lpszItem, 0, 0, nImage, 0);
}

void CSkinListCtrl::OnDestroy()
{
    m_bLockChange = TRUE;
    for (int nItem = 0; nItem < GetItemCount(); nItem++)
    {
        FreeData(nItem);
    }
    m_bLockChange = FALSE;
    
#ifdef USESKINSCROLL
    m_VScroll.ReInit();
    m_HScroll.ReInit();
#endif
    
    CListCtrl::OnDestroy();
}

void CSkinListCtrl::FreeData(int nItem)
{
    TITEMDATA* pData = reinterpret_cast<TITEMDATA*>(CListCtrl::GetItemData(nItem));

    if (NULL != pData) 
    {
        delete pData;
        CListCtrl::SetItemData(nItem, 0);
    }
}

BOOL CSkinListCtrl::DeleteItem(int nItem)
{
    if (nItem < 0 || nItem > GetItemCount()) 
    {
        return FALSE;
    }
    FreeData(nItem);
    return CListCtrl::DeleteItem(nItem);
}

BOOL CSkinListCtrl::DeleteAllItems()
{
    for (int nItem = 0; nItem < GetItemCount(); nItem++)
    {
        FreeData(nItem);
    }
    return CListCtrl::DeleteAllItems();
}

DWORD CSkinListCtrl::GetItemData(int nItem) const
{
    if (nItem > GetItemCount()) 
    {
        return 0;
    }
    TITEMDATA* pData = reinterpret_cast<TITEMDATA*>(CListCtrl::GetItemData(nItem));
    if (NULL == pData) 
    {
        return 0;
    }
    return pData->m_dwData;
}

BOOL CSkinListCtrl::GetItem( LVITEM* pItem ) const
{
    BOOL bRev = CListCtrl::GetItem(pItem);
    if (bRev) 
    {
        if (0 != pItem->lParam) 
        {
            TITEMDATA* pData = reinterpret_cast<TITEMDATA*>(pItem->lParam);
            pItem->lParam = pData->m_dwData;
        }
        return TRUE;
    }
    return FALSE;
}


void CSkinListCtrl::ResetIndex()
{
    for (int nItem = 0; nItem < GetItemCount(); nItem++)
    {
        TITEMDATA* pData = reinterpret_cast<TITEMDATA*>(CListCtrl::GetItemData(nItem));
        if (NULL == pData) 
        {
            pData = new TITEMDATA;
            CListCtrl::SetItemData(nItem, (DWORD)pData);
        }
        pData->m_nIndex = nItem;
    }
}


/*=============================================================================
函 数 名： staticSetBkColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crBkNormal
           COLORREF crBkDisable
           COLORREF crBkSelect
           COLORREF crBkHighlight
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  1.0			朱允荣                  创建
=============================================================================*/
void CSkinListCtrl::staticSetBkColor(COLORREF crBkNormal, COLORREF crBkDisable,
                                     COLORREF crBkSelect, COLORREF crBkHighlight)
{
    m_s_crBk[CRNORMAL] = crBkNormal;
    m_s_crBk[CRDISABLE] = crBkDisable;
    m_s_crBk[CRSELECT] = crBkSelect;
    m_s_crBk[CRHIGHLIGHT] = crBkHighlight;
}


/*=============================================================================
函 数 名： staticSetTextColor
功    能： 
算法实现： 
全局变量： 
参    数： COLORREF crTextNormal
           COLORREF crTextDisable
           COLORREF crTextSelect
           COLORREF crTextHighlight
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2005/03/29  1.0			朱允荣                  创建
=============================================================================*/
void CSkinListCtrl::staticSetTextColor(COLORREF crTextNormal, COLORREF crTextDisable,
                                       COLORREF crTextSelect, COLORREF crTextHighlight)
{
    m_s_crText[CRNORMAL] = crTextNormal;
    m_s_crText[CRDISABLE] = crTextDisable;
    m_s_crText[CRSELECT] = crTextSelect;
    m_s_crText[CRHIGHLIGHT] = crTextHighlight;
}