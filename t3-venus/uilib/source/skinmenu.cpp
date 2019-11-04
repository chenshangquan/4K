/********************************************************************
	模块名:      UILib
	文件名:      skinmenu.cpp
	相关文件:    UILibHead.h
	文件实现功能 
    作者：       朱允荣
	版本：       1.0
---------------------------------------------------------------------------
	修改记录:
	日  期		版本		修改人		走读人    修改内容
	2004/4/8	1.0			朱允荣               

*********************************************************************/


#include "stdafx.h"
#include "UILibHead.h"
#include <afxpriv.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMenuItem::~CMenuItem()
{
    delete[] m_szMenuText;
    delete[] m_szHotItem;
}

CString CMenuItem::GetString()//returns the menu text in ANSI or UNICODE
//depending on the MFC-Version we are using
{
	CString strText;
	if (NULL != m_szMenuText)
    {
#ifdef UNICODE
		strText = m_szMenuText;
#else
		USES_CONVERSION;
		strText=W2A(m_szMenuText);     //SK:  see MFC Tech Note 059
#endif    
    }
	return strText;
}

CString CMenuItem::GetHotString()
{
	CString strText;
	if (NULL != m_szMenuText)
    {
#ifdef UNICODE
		strText = m_szHotItem;
#else
		USES_CONVERSION;
		strText=W2A(m_szHotItem);     //SK:  see MFC Tech Note 059
#endif    
    }
	return strText;
}

void CMenuItem::SetWideString(const wchar_t *szWideString)
{
    
	delete[] m_szMenuText;//Need not check for NULL because ANSI X3J16 allows "delete NULL"
	
	if (NULL != szWideString)
    {
		m_szMenuText = new wchar_t[sizeof(wchar_t)*(wcslen(szWideString)+1)];
		if (m_szMenuText)
			wcscpy(m_szMenuText,szWideString);
    }
	else
    {
		m_szMenuText = NULL;//set to NULL so we need not bother about dangling non-NULL Ptrs
    }
}

void CMenuItem::SetAnsiString(LPCSTR szAnsiString)
{
    USES_CONVERSION;
	SetWideString(A2W(szAnsiString));  //SK:  see MFC Tech Note 059
}


void CMenuItem::SetHotString(LPCSTR szHotString)
{
    USES_CONVERSION;
	SetHotString(A2W(szHotString)); 
}


void CMenuItem::SetHotString(const wchar_t *szHotString)
{
    delete[] m_szHotItem;//Need not check for NULL because ANSI X3J16 allows "delete NULL"
	
	if (NULL != szHotString)
    {
		m_szHotItem = new wchar_t[sizeof(wchar_t)*(wcslen(szHotString)+1)];
		if (NULL != m_szHotItem)
        {
			wcscpy(m_szHotItem, szHotString);
        }
    }
	else
    {
		m_szHotItem = NULL;//set to NULL so we need not bother about dangling non-NULL Ptrs
    }
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTypedPtrArray<CPtrArray, HMENU> CSkinMenu::m_AllSubMenus;
int CSkinMenu::m_s_nType = TYPE_NORMAL;

COLORREF CSkinMenu::m_s_crBk[3] = {
    RGB(105,146,214), RGB(34,52,88), RGB(241, 242, 244)};

COLORREF CSkinMenu::m_s_crText[3] = 
{RGB(241, 242, 244), RGB(80, 114, 170), RGB(176, 180, 186)};

IMPLEMENT_DYNAMIC(CSkinMenu, CMenu)

CSkinMenu::CSkinMenu() : m_pcFont(NULL)
{
    if (m_s_nType == TYPE_NMC) 
    {
        m_crBk[0] = RGB(0x3c, 0x58, 0x7a);
        m_crBk[1] = RGB(0x3c, 0x58, 0x7a);
        m_crBk[2] = RGB(0xb4, 0xc5, 0xd5);

        m_crText[0] = RGB(255 ,255, 255);
        m_crText[1] = RGB(0, 0, 0);
        m_crText[2] = RGB(0xb3, 0xba, 0xc1);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            m_crBk[i] = m_s_crBk[i];
            m_crText[i] = m_s_crText[i];
        }
    }
	
	// set the color used for the transparent background in all bitmaps
	m_bLoadMenu=FALSE;
    m_nHeigth = 20;
    m_nWidth = -1;
}


CSkinMenu::~CSkinMenu()
{
   DestroyMenu();
}

void CSkinMenu::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);
    if (pDC == NULL) 
    {
        return;
    }

    CMenuItem* pItem = reinterpret_cast<CMenuItem *>(lpDIS->itemData);
    CRect rectFull(lpDIS->rcItem);
    CRect rcAll(0, 0, lpDIS->rcItem.right, GetMenuItemCount() * (m_nHeigth));

    CRect rectIcon(rectFull.left,rectFull.top,rectFull.left+20,rectFull.top+20);
	CRect rectText(rectIcon.right,rectFull.top,rectFull.right,rectFull.bottom);

    UINT nState = GetMenuState(lpDIS->itemID, MF_BYCOMMAND);

    if (lpDIS->itemAction & ODA_DRAWENTIRE ||
        (!(lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & ODA_SELECT)))
	{
        // paint the brush and icon item in requested
		CRect rect;

        CUITools::DrawStepBk(pDC, m_crBk[0], m_crBk[1], rcAll, rectFull);
		// paint item background 
        

        if (!(nState & MF_POPUP)) 
        {
            // 2004/11/27 李洪强 对Popup菜单项而言,通过GetMenuState返回的
            // nState与普通菜单项意义不同,要区别处理
		    if (nState & MF_SEPARATOR)	// item is separator
		    {	// draw a etched edge
			    rect.CopyRect(rectFull);
			    rect.OffsetRect(5,3);
                if (m_s_nType == TYPE_NMC) 
                {
                    pDC->FillSolidRect(rect.left, rect.top, rect.Width(),
                        1, RGB(0xaa, 0xaa, 0xaa));
                }
                else
                {
			        pDC->DrawEdge(rect,EDGE_ETCHED,BF_TOP);
                }
		    }
        }
		if (nState & MFS_CHECKED) // item has been checked
		{
			// paint the frame and brush,then draw a check mark
			rect.CopyRect(rectIcon);
			rect.DeflateRect(1,1,1,1);
			pDC->FrameRect(rect,&CBrush(RGB(64,64,128)));

			rect.DeflateRect(1,1,1,1);
			pDC->FillRect(rect,&CBrush(RGB(216,216,235)));
			DrawCheckMark(pDC,rect.left+5,rect.top+5,RGB(64,64,128));
		}			

        if (pItem->m_hBitmap)	// item has bitmap
		{	// draw a bitmap
			CDC memDC;
			memDC.CreateCompatibleDC(pDC);
            HBITMAP hOldBitmap = (HBITMAP)::SelectObject(memDC.m_hDC, pItem->m_hBitmap);
			pDC->BitBlt(rectIcon.left+2,rectIcon.top+2,16,16,&memDC,0,0,SRCCOPY);
			::SelectObject(memDC.m_hDC, hOldBitmap);
		}

        // draw display text
		rect.CopyRect(rectText);

        COLORREF crText;
		if (nState & MFS_DISABLED )	// item has been disabled
        {
    /*
                    pDC->SetBkMode(TRANSPARENT);
                        rect.OffsetRect(3,1);
                        pDC->SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));//RGB(255,255,255)
                        pDC->DrawText(pItem->GetString(), rect, DT_VCENTER|DT_LEFT|DT_SINGLELINE);
                        rect.OffsetRect(-3,-1);*/
            
            crText = m_crText[2];//GetSysColor(COLOR_3DSHADOW)GetSysColor(COLOR_3DFACE);RGB(128,128,128)
        }
        else
        {
            crText = m_crText[0];
        }
		
        DrawItemText(pDC, crText, rect, pItem);
    }

    //高亮显示
    if ((lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		// item has been selected
		if( nState & MFS_DISABLED )	
			return;					// item has been disabled  
		CRect  rect;

		// item has bitmap - draw a raised edge
		if( !(nState & MFS_CHECKED ) && (pItem->m_hBitmap != NULL) )	
			pDC->DrawEdge(rectIcon,EDGE_RAISED,BF_RECT);

        if (nState & MFS_CHECKED)
        {
            rectFull = rectText;
        }

		pDC->FillRect(rectFull,&CBrush(m_crBk[2]));

        
		// draw display text
		rect.CopyRect(rectText);

        DrawItemText(pDC, m_crText[1], rect, pItem);
        
		m_curSel = lpDIS->itemID;	// get current selected
	}
}

BOOL CSkinMenu::AppendMenu(UINT nFlags, UINT nIDNewItem, LPCSTR lpszNewItem, UINT nIDBitmap, HICON hIcon)
{
	if (!nIDNewItem)
    {
		if (nFlags&MF_BYPOSITION) 
        {
            nFlags = MF_SEPARATOR|MF_OWNERDRAW|MF_BYPOSITION;
        }
		else
        {
            nFlags = MF_SEPARATOR|MF_OWNERDRAW;
        }
	}
	else if(!(nFlags & MF_OWNERDRAW))
    {
        nFlags |= MF_OWNERDRAW;
    }

    if((nFlags & MF_POPUP))
    {
        m_SubMenus.Add((HMENU(nIDNewItem)));
        m_AllSubMenus.Add(HMENU(nIDNewItem));
    }
    
    CMenuItem* pItem = new CMenuItem(lpszNewItem,NULL,hIcon);
    //CMenuItem* pItem = new CMenuItem;

    m_MenuList.Add(pItem);

    if (m_nWidth != -1)
    {
        pItem->m_nHeight = m_nHeigth;	 // set current menu height
	    pItem->m_nWidth  = m_nWidth;		// set current menu width
    }

    pItem->SetAnsiString(_T(""));
    pItem->SetHotString(_T(""));
	int n;
    CString str = lpszNewItem;
    n = str.Find("\t", 0);
	if( n != -1 )	// get item string and hotkey string
	{
        pItem->SetAnsiString(str.Left(n));
        str = str.Right(str.GetLength()-n);		
		pItem->SetHotString(str);
	}	
	else
    {
        pItem->SetAnsiString(lpszNewItem);
    }
    pItem->m_nFlags = nFlags;
    pItem->m_nID = nIDNewItem;
    pItem->m_hIcon = hIcon;
    pItem->m_hBitmap = CUITools::CreateImage(nIDBitmap);
    
    return CMenu::AppendMenu(nFlags, nIDNewItem, LPCSTR(pItem));
}

void CSkinMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
    UINT state;// = GetMenuState(lpMIS->itemID,MF_BYCOMMAND);

	CMenuItem* pItem = reinterpret_cast<CMenuItem *>(lpMIS->itemData);
    state = pItem->m_nFlags;
	if( state & MF_SEPARATOR )		// item state is separator
	{
		lpMIS->itemWidth =  pItem->m_nWidth;
		lpMIS->itemHeight = 6;
	}
	else							// other item state
	{
		lpMIS->itemWidth =  pItem->m_nWidth;
		lpMIS->itemHeight = pItem->m_nHeight;
	}
}

BOOL CSkinMenu::LoadMenu(UINT uMenuID)
{
    return LoadMenu(MAKEINTRESOURCE(uMenuID));
}

BOOL CSkinMenu::LoadMenu(LPCTSTR lpszResourceName)
{
    ASSERT_VALID(this);
	ASSERT(lpszResourceName != NULL);
	
	// Find the Menu Resource:
	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName,RT_MENU);
	HRSRC hRsrc = ::FindResource(hInst,lpszResourceName,RT_MENU);
	if (hRsrc == NULL)
    {
		hInst = NULL;
		hRsrc = ::FindResource(hInst,lpszResourceName,RT_MENU);
	}
	if(hRsrc == NULL)
    {
        return FALSE;
    }
	
	// Load the Menu Resource:
	HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
	if(hGlobal == NULL)
    {
        return FALSE;
    }

	// first destroy the menu if we're trying to loadmenu again
	DestroyMenu();

	// Attempt to create us as a menu...
	if(!CMenu::CreateMenu())
    {
        return FALSE;
    }

    MENUITEMTEMPLATEHEADER *pTpHdr = (MENUITEMTEMPLATEHEADER*)LockResource(hGlobal);
	BYTE* pTp = (BYTE*)pTpHdr + (sizeof(MENUITEMTEMPLATEHEADER) + pTpHdr->offset);

    int j=0;
	WORD    dwFlags = 0;              // Flags of the Menu Item
	WORD    dwID  = 0;              // ID of the Menu Item
	UINT    uFlags;                  // Actual Flags.
	wchar_t *szCaption=NULL;
	int      nLen   = 0;                // Length of caption
	CTypedPtrArray<CPtrArray, CSkinMenu*>  arrayStack;    // Popup menu stack
	CArray<BOOL,BOOL>  arrayStackEnd;    // Popup menu stack
	arrayStack.Add(this);                  // Add it to this...
	arrayStackEnd.Add(FALSE);

    do
    {
        BOOL bTest = arrayStackEnd[0];
        BOOL bNewTest = arrayStackEnd[arrayStack.GetUpperBound()];
		// Obtain Flags and (if necessary), the ID...
		memcpy(&dwFlags, pTp, sizeof(WORD));
        pTp += sizeof(WORD);// Obtain Flags
		if (!(dwFlags & MF_POPUP))
        {
			memcpy(&dwID, pTp, sizeof(WORD)); // Obtain ID
			pTp+=sizeof(WORD);
		}
		else
        {
            dwID = 0;
        }
		
		uFlags = (UINT)dwFlags; // Remove MF_END from the flags that will
		if(uFlags & MF_END) // be passed to the Append(OD)Menu functions.
        {
			uFlags -= MF_END;
        }
		
		// Obtain Caption (and length)
		nLen = 0;
		szCaption = new wchar_t[wcslen((wchar_t *)pTp)+1];
		wcscpy(szCaption,(wchar_t *)pTp);
		pTp = &pTp[(wcslen((wchar_t *)pTp)+1)*sizeof(wchar_t)];//modified SK
		
		// Handle popup menus first....
		
		//WideCharToMultiByte
		if (dwFlags & MF_POPUP)
        {
			if (dwFlags & MF_END)
            {
                arrayStackEnd.SetAt(arrayStack.GetUpperBound(),TRUE);
            }
			CSkinMenu* pSubMenu = new CSkinMenu;
				
            pSubMenu->m_nWidth = m_nWidth;
            pSubMenu->m_nHeigth = m_nHeigth;
			pSubMenu->CreatePopupMenu();
			
			// Append it to the top of the stack:
			
			arrayStack[arrayStack.GetUpperBound()]->AppendODMenuW(szCaption,uFlags,
				(UINT)pSubMenu->m_hMenu, -1);
			arrayStack.Add(pSubMenu);
			arrayStackEnd.Add(FALSE);
		}
		else 
        {
			arrayStack[arrayStack.GetUpperBound()]->AppendODMenuW(szCaption, uFlags,
				dwID, -1);
			if(dwFlags & MF_END)
            {
                arrayStackEnd.SetAt(arrayStack.GetUpperBound(),TRUE);
            }
			j = arrayStack.GetUpperBound();
			while (j>=0 && arrayStackEnd.GetAt(j))
            {
				arrayStack[arrayStack.GetUpperBound()]->InsertSpaces();
				arrayStack.RemoveAt(j);
				arrayStackEnd.RemoveAt(j);
				--j;
			}
		}
		
		delete[] szCaption;
	}
    while(arrayStack.GetUpperBound() != -1);

    for (int i=0; i<(int)GetMenuItemCount(); ++i)
    {
        CMenuItem* pItem = (CMenuItem*)m_MenuList[i];
		CString str = pItem->GetString();
		if (GetSubMenu(i))
        {
			pItem->m_nFlags = MF_POPUP|MF_BYPOSITION;
			ModifyMenu(i,MF_POPUP|MF_BYPOSITION,
				(UINT)GetSubMenu(i)->m_hMenu,str);
		}
		else
        {
			pItem->m_nFlags=MF_STRING|MF_BYPOSITION;
			ModifyMenu(i,MF_STRING|MF_BYPOSITION,pItem->m_nID,str);
		}
	}

	m_bLoadMenu = TRUE;
    
    return TRUE;
}

BOOL CSkinMenu::AppendODMenuW(wchar_t *lpstrText, UINT nFlags, UINT nID, CImageList *il, int xoffset)
{
    return TRUE;
}

BOOL CSkinMenu::AppendODMenuW(wchar_t *lpstrText, UINT nFlags, UINT nID, int nIconNormal)
{
    CString strText;
	if (lpstrText)
    {
#ifdef UNICODE
		strText = lpstrText;
#else
		USES_CONVERSION;
		strText=W2A(lpstrText);     //SK:  see MFC Tech Note 059
#endif    
    }
   return AppendMenu(nFlags, nID, strText);
}

void CSkinMenu::InsertSpaces()
{
    if (m_nWidth != -1) //如果指定了宽度，则不再计算。
    {
        return;
    }
	CFont m_fontMenu;
	LOGFONT m_lf;
	
	ZeroMemory ((PVOID) &m_lf,sizeof (LOGFONT));
	NONCLIENTMETRICS nm;
	nm.cbSize = sizeof(NONCLIENTMETRICS);
	VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS, nm.cbSize, &nm, 0)); 
	m_lf =  nm.lfMenuFont;
	m_fontMenu.CreateFontIndirect (&m_lf);
	
	CWnd *pWnd = AfxGetMainWnd();  
	if (pWnd == NULL)
    {
        pWnd = CWnd::GetDesktopWindow();
    }
	CDC *pDC = pWnd->GetDC();
	CFont* pFont = pDC->SelectObject(&m_fontMenu);
	
	int nItemCount = GetMenuItemCount();
	int nMaxlength = -1;
    CString strItem, strNewString;
    CSize tSize;
    
	int i,nStrLen;
    //计算最大长度。
	for (i=0; i<nItemCount; ++i)
    {
        if (m_MenuList[i]->m_nFlags & MF_SEPARATOR) 
        {
            continue;
        }
		strItem = m_MenuList[i]->GetString();
		nStrLen = strItem.Find((char)9);
		strNewString.Empty();
		if (nStrLen != -1)
        {
            strNewString = strItem.Left(nStrLen);
        }
		else
        {
            strNewString = strItem;
        }
		strNewString += _T(" ");//SK: modified for Unicode correctness. 
		LPCTSTR lpstrText = (LPCTSTR)strNewString;
		tSize = pDC->GetTextExtent(lpstrText,_tcslen(lpstrText));
		if (tSize.cx > nMaxlength)
        {
            nMaxlength = tSize.cx;
        }
	}


	for (i=0; i<nItemCount; ++i)
    {
		strItem = m_MenuList[i]->GetString();
		nStrLen = strItem.Find((char)9);
		if (nStrLen != -1)
        {
			strNewString.Empty();
			strNewString = strItem.Left(nStrLen);
			LPCTSTR lpstrText = (LPCTSTR)(strNewString);
			tSize = pDC->GetTextExtent(lpstrText,_tcslen(lpstrText));
			while (tSize.cx < nMaxlength)
            {
				nMaxlength += _T(' ');//SK: modified for Unicode correctness
				LPCTSTR lpstrText = (LPCTSTR)(strNewString);
				tSize = pDC->GetTextExtent(lpstrText,_tcslen(lpstrText));
			}
			strNewString += strItem.Mid(nStrLen);
#ifdef UNICODE      
			m_MenuList[i]->SetWideString(strNewString);//SK: modified for dynamic allocation
#else
			m_MenuList[i]->SetAnsiString(strNewString);
#endif
		}
            m_MenuList[i]->m_nWidth = nMaxlength + 25;
            if (!(m_MenuList[i]->m_nFlags & MF_SEPARATOR)) 
            {
                m_MenuList[i]->m_nHeight = max(tSize.cy + 5, 20);
            }
	}
	pDC->SelectObject (pFont);              // Select old font in
	pWnd->ReleaseDC(pDC);       // Release the DC
	m_fontMenu.DeleteObject();
}

void CSkinMenu::DrawCheckMark(CDC *pDC, int x, int y, COLORREF color)
{
	CPen Pen;

	Pen.CreatePen(PS_SOLID,0,color);
	CPen *pOldPen = pDC->SelectObject(&Pen);
	
	pDC->MoveTo(x,y+2);
	pDC->LineTo(x,y+5);
	
	pDC->MoveTo(x+1,y+3);
	pDC->LineTo(x+1,y+6);
	
	pDC->MoveTo(x+2,y+4);
	pDC->LineTo(x+2,y+7);
	
	pDC->MoveTo(x+3,y+3);
	pDC->LineTo(x+3,y+6);
	
	pDC->MoveTo(x+4,y+2);
	pDC->LineTo(x+4,y+5);
	
	pDC->MoveTo(x+5,y+1);
	pDC->LineTo(x+5,y+4);
	
	pDC->MoveTo(x+6,y);
	pDC->LineTo(x+6,y+3);

	pDC->SelectObject(pOldPen);
	Pen.DeleteObject();

}

BOOL CSkinMenu::IsMenu(HMENU hMenu)
{
	int numSubMenus = m_AllSubMenus.GetUpperBound();
	for (int i=0; i <= numSubMenus; ++i)
    {
		if (hMenu == m_AllSubMenus[i])
        {
            return TRUE;
        }
	}
	return FALSE;
}

void CSkinMenu::SetBkColor(COLORREF crFrom, COLORREF crTo, COLORREF crHilight)
{
    m_crBk[0] = crFrom;
    m_crBk[1] = crTo;

    if (crHilight != -1) 
    {
        m_crBk[2] = crHilight;
    }

    int nSub = m_SubMenus.GetUpperBound();
    while (nSub >= 0) 
    {
        CMenu* pMenu = FromHandle(m_SubMenus[nSub]);
        if (pMenu->IsKindOf(RUNTIME_CLASS(CSkinMenu))) 
        {
           ((CSkinMenu*)pMenu)->SetBkColor(crFrom, crTo, crHilight);
        }
        nSub--;
    }
}

void CSkinMenu::DrawItemText(CDC* pDC, COLORREF crText, CRect rect, CMenuItem* pItem)
{
    if (NULL == pItem || NULL == pDC)
    {
        return;
    }
    rect.OffsetRect(2, 0);

	pDC->SetBkMode(TRANSPARENT);
    COLORREF crOld = pDC->SetTextColor(crText);

    //  wanghao 2006/11/08 设置菜单文字字体
    CFont *pcOldFont = NULL;
    if ( m_pcFont != NULL )
    {
        pcOldFont = pDC->SelectObject( m_pcFont );
    }

	pDC->DrawText(pItem->GetString(), pItem->GetString().GetLength(), rect, 
        DT_LEFT|DT_SINGLELINE|DT_VCENTER);

	if (!pItem->GetHotString().IsEmpty()) 
    {
    	pDC->DrawText(pItem->GetHotString(), pItem->GetHotString().GetLength(),
				  CRect(rect.right-60,rect.top,rect.right,rect.bottom),
                  DT_LEFT|DT_SINGLELINE|DT_VCENTER);
    }

    pDC->SetTextColor(crOld);
    if ( m_pcFont != NULL )
    {
        pDC->SelectObject( pcOldFont );
    }
}


BOOL CSkinMenu::DeleteMenu(UINT nPosition, UINT nFlags)
{
    if (MF_BYPOSITION & nFlags)
    {
        UINT uint = GetMenuState(nPosition, MF_BYPOSITION);
		if ((uint & MF_SEPARATOR) && !(uint & MF_POPUP))
        {
			// make sure it's a separator
			int nMenuListSize = m_MenuList.GetSize();	
			if (nPosition < (UINT)nMenuListSize)
            {
				CString str = m_MenuList[nPosition]->GetString();
				if (str.IsEmpty())
                {
					delete m_MenuList.GetAt(nPosition);
					m_MenuList.RemoveAt(nPosition);
				}
			}
        }
        else
        {
            CSkinMenu* pSubMenu = (CSkinMenu*) GetSubMenu(nPosition);
            if (NULL == pSubMenu) //一般菜单， 只要删除相关的数据
            {
                UINT uCommandId = GetMenuItemID(nPosition);
				for (int i=0; i<m_MenuList.GetSize(); i++)
                {
					if (m_MenuList[i]->m_nID == uCommandId)
                    {
						delete m_MenuList.GetAt(i);
						m_MenuList.RemoveAt(i);
						break;
					}
				}
            }
            else
            {
                //POP类菜单，从删除SubMenus和AllSubMenus菜单中删除。
                int nSubMenus = m_SubMenus.GetUpperBound();
				for (int m = nSubMenus; m >= 0; m--)
                {
					if (m_SubMenus[m] == pSubMenu->m_hMenu)
                    {
						m_SubMenus.RemoveAt(m);
					}
				}

				int numAllSubMenus = m_AllSubMenus.GetUpperBound();
				for (int n = numAllSubMenus; n>= 0; n--)
                {
					if (m_AllSubMenus[n] == pSubMenu->m_hMenu)
                    {
                        m_AllSubMenus.RemoveAt(n);
                    }
				}
                
				int num = pSubMenu->GetMenuItemCount()-1;
				for (; num>=0 ;--num)
                {
                    pSubMenu->DeleteMenu(num,MF_BYPOSITION);
                }

				for(num = m_MenuList.GetUpperBound(); num>=0; num--)
                {
					if (m_MenuList[num]->m_nID == (UINT)pSubMenu->m_hMenu)
                    {
						delete m_MenuList.GetAt(num);
						m_MenuList.RemoveAt(num);
						break;
					}
				}
				delete pSubMenu;
            } //end of else (pSubMenu == NULL)
        } //end of else ((uint & MF_SEPARATOR) && !(uint & MF_POPUP))
    } // end if
    else
    {
        int iPosition =0;
		CSkinMenu* pMenu = FindMenuOption(nPosition,iPosition);
		if (NULL != pMenu) 
        {
            return pMenu->DeleteMenu(iPosition,MF_BYPOSITION);
        }
    }

    return(CMenu::DeleteMenu(nPosition,nFlags));
}

CSkinMenu* CSkinMenu::FindMenuOption(int nID, int &nLoc)
{
    nLoc = -1;

    int nCount = GetMenuItemCount();
    CSkinMenu* pSubMenu;
    CSkinMenu* pTempMenu;
    for (int i=0; i < nCount; i++)
    {
        pSubMenu = (CSkinMenu*) GetSubMenu(i);

        if (NULL != pSubMenu)
        {
            pTempMenu = pSubMenu->FindMenuOption(nID, nLoc);
            if (NULL != pTempMenu)
            {
                return pTempMenu;
            }
        }
        else if (nID == (int)GetMenuItemID(i))
        {
            nLoc = i;
            return this;
        }
    }

    return NULL;
}


BOOL CSkinMenu::CreatePopupMenu()
{
    BOOL bRev = CMenu::CreatePopupMenu();
    if (!bRev) 
    {
        return FALSE;
    }

    m_AllSubMenus.Add(m_hMenu);
    return TRUE;
}


BOOL CSkinMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT nID, wchar_t *lpstrText, 
                           CImageList *il, int xoffset)
{
    if (!(nFlags & MF_BYPOSITION)) 
    {
        int nPos = 0;
        CSkinMenu* pSubMenu = FindMenuOption(nPosition, nPos);
        
        if (NULL != pSubMenu) 
        {
            return pSubMenu->InsertMenu(nPos, nFlags|MF_BYPOSITION, nID, lpstrText, il, xoffset);
        }
        else
        {
            return FALSE;
        }
    }

    if (0 == nID) 
    {
        nFlags = MF_SEPARATOR|MF_OWNERDRAW|MF_BYPOSITION;
    }
    else if (!(nFlags & MF_OWNERDRAW))
    {
        nFlags |= MF_OWNERDRAW;
    }

    if (nFlags & MF_POPUP) 
    {
        m_AllSubMenus.Add((HMENU)nID);
        m_SubMenus.InsertAt(nPosition, (HMENU)nID);
    }

    if ((UINT)-1 == nPosition) 
    {
        nPosition = GetMenuItemCount();
    }

    CMenuItem* pItem = new CMenuItem;
    if (NULL == pItem) 
    {
        return FALSE;
    }
    m_MenuList.InsertAt(nPosition, pItem);
    pItem->SetWideString(lpstrText);

    if (0 == nID) 
    {
        pItem->m_nHeight = 6;
    }

    pItem->m_nFlags = nFlags;
    pItem->m_pImaList = il;
    pItem->m_nImage = xoffset;
    return CMenu::InsertMenu(nPosition, nFlags, nID, (LPCTSTR)pItem);
}

BOOL CSkinMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT nID, LPCTSTR lpstrText)
{
    USES_CONVERSION;
    return InsertMenu(nPosition, nFlags, nID, A2W(lpstrText));
}

void CSkinMenu::SetTextColor(COLORREF crText, COLORREF crHilight, COLORREF crDisable)
{
    m_crText[0] = crText;
    m_crText[1] = crHilight;

    if (crDisable == -1) 
    {
        crDisable = RGB(128, 128, 128);
    }
    m_crText[2] = crDisable;

    int nSub = m_SubMenus.GetUpperBound();
    while (nSub >= 0) 
    {
        CMenu* pMenu = FromHandle(m_SubMenus[nSub]);
        if (pMenu->IsKindOf(RUNTIME_CLASS(CSkinMenu))) 
        {
           ((CSkinMenu*)pMenu)->SetTextColor(crText, crHilight, crDisable);
        }
        nSub--;
    }
}

BOOL CSkinMenu::DestroyMenu()
{
    int nAllSub = m_AllSubMenus.GetUpperBound();

    while (nAllSub >= 0)
    {
        if (m_AllSubMenus[nAllSub] == m_hMenu) 
        {
            m_AllSubMenus.RemoveAt(nAllSub);
        }
        nAllSub--;
    }

    int nSub = m_SubMenus.GetUpperBound();
    while (nSub >= 0) 
    {
        nAllSub = m_AllSubMenus.GetUpperBound();
        while (nAllSub >= 0) 
        {
            if (m_AllSubMenus[nAllSub] == m_SubMenus[nSub]) 
            {
                m_AllSubMenus.RemoveAt(nAllSub);
            }
            nAllSub--;
        }
        CMenu* pMenu = FromHandle(m_SubMenus[nSub]);
        if (pMenu->IsKindOf(RUNTIME_CLASS(CSkinMenu))) 
        {
            delete (CSkinMenu*)pMenu;
        }
        nSub--;
    }
    m_SubMenus.RemoveAll();

    int nItems = m_MenuList.GetUpperBound();
    while (nItems >=0) 
    {
        delete m_MenuList[nItems--];
    }
    m_MenuList.RemoveAll();

    return CMenu::DestroyMenu();
}

CSize CSkinMenu::GetMenuSize()
{
    if (m_MenuList.GetSize() <= 0) 
    {
        return CSize(0,0);
    }
    CSize size;
    size.cx = m_MenuList[0]->m_nWidth;
    size.cy = m_MenuList[0]->m_nHeight * GetMenuItemCount();
    return size;
}

LRESULT CSkinMenu::OnSkinMenuChar(UINT nChar, UINT nFlags, CMenu *pMenu)
{
#ifdef _CPPRTTI
    CSkinMenu* pSkinMenu = dynamic_cast<CSkinMenu*>(pMenu);
#else
    CSkinMenu* pSkinMenu = (CSkinMenu*)pMenu;
#endif

    if ((pSkinMenu != NULL) && (nFlags&MF_POPUP)) 
    {
        CString strKey(_T('&'), 2);
        strKey.SetAt(1, (TCHAR)nChar);
        strKey.MakeLower();
        
        CString strMenuText;
        int nSize = pSkinMenu->GetMenuItemCount();
        for (int i = 0; i < nSize; i++) 
        {
            pSkinMenu->GetMenuString(i, strMenuText);
            strMenuText.MakeLower();
            if (strMenuText.Find(strKey, 0) >= 0) 
            {
                return MAKELRESULT(i, 2);
            }
        }
    }
    return 0;
}

int CSkinMenu::GetMenuString(UINT nIDItem, CString &rString, UINT nFlag)
{
    if (nFlag & MF_BYPOSITION) 
    {
        UINT nMax = m_MenuList.GetUpperBound();
        if (nIDItem <= nMax) 
        {
            rString = m_MenuList[nIDItem]->GetString();
            return rString.GetLength();
        }
    }
    else
    {
        int nLoc;
        CSkinMenu* pMenu = FindMenuOption(nIDItem, nLoc);
        if (pMenu != NULL) 
        {
            return pMenu->GetMenuString(nLoc, rString);
        }
    }
    rString = _T("");
    return 0;
}

int CSkinMenu::GetMenuString(UINT nIDItem, char** pString, UINT nSize, UINT nFlag)
{
    CString strLen;
    int nLen = GetMenuString(nIDItem, strLen, nFlag);

    nLen = min(nLen, (int)nSize-1);
    if (nLen > 0 && pString != NULL && *pString != NULL)
    {
        strncpy(*pString, (LPCTSTR)strLen, nLen);
        *((*pString) + nLen) = 0;
    }
    return nLen;
}

void CSkinMenu::SetMenuString(UINT nIDItem, LPCSTR lpString, UINT nFlag)
{
    if (nFlag & MF_BYPOSITION) 
    {
        UINT nMax = m_MenuList.GetUpperBound();
        if (nIDItem <= nMax) 
        {
            m_MenuList[nIDItem]->SetAnsiString(lpString);
        }
    }
    else
    {
        int nLoc;
        CSkinMenu* pMenu = FindMenuOption(nIDItem, nLoc);
        if (pMenu != NULL) 
        {
            pMenu->SetMenuString(nLoc, lpString);
        }
    }
}

