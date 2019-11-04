// listtestdlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\libtest.h"
#include "..\include\listtestdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListTestDlg dialog


CListTestDlg::CListTestDlg(CWnd* pParent /*=NULL*/)
	: CBMPDlg(CListTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListTestDlg)
	m_date = _T("");
	//}}AFX_DATA_INIT
}


void CListTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CBMPDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListTestDlg)
	DDX_Control(pDX, IDC_BUTTON_ADDITEM, m_btnAddItem);
	DDX_Control(pDX, IDC_HEAD_BK, m_btnNew);
	DDX_Control(pDX, IDC_LIST2, m_listHide);
	DDX_Control(pDX, IDC_RADIO_HIDE, m_raToolTip3);
	DDX_Control(pDX, IDC_RADIO_FULLROW, m_raToolTip2);
	DDX_Control(pDX, IDC_RADIO_DISABLE, m_raToolTip1);
	DDX_Control(pDX, IDC_CHECK_DRAG, m_ckDrag);
	DDX_Control(pDX, IDC_CHECK_EABLE, m_ckEnable);
	DDX_Control(pDX, IDC_CHECK_SORT, m_ckSort);
	DDX_Control(pDX, IDC_CHECK_HOT, m_ckHot);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListTestDlg, CBMPDlg)
	//{{AFX_MSG_MAP(CListTestDlg)
	ON_BN_CLICKED(IDC_HEAD_BK, OnHeadBk)
	ON_BN_CLICKED(IDC_LIST_TEXT, OnListText)
	ON_BN_CLICKED(IDC_LIST_FONT, OnListFont)
	ON_BN_CLICKED(IDC_ITEM_BK, OnItemBk)
	ON_BN_CLICKED(IDC_ITEM_TEXT, OnItemText)
	ON_BN_CLICKED(IDC_ITEM_FONT, OnItemFont)
	ON_BN_CLICKED(IDC_CHECK_HOT, OnCheckHot)
	ON_BN_CLICKED(IDC_CHECK_SORT, OnCheckSort)
	ON_BN_CLICKED(IDC_CHECK_EABLE, OnCheckEable)
	ON_BN_CLICKED(IDC_HIGHLIGHT_BK, OnHighlightBk)
	ON_BN_CLICKED(IDC_HIGHLIGHT_TEXT, OnHighlightText)
	ON_BN_CLICKED(IDC_SELECT_BK, OnSelectBk)
	ON_BN_CLICKED(IDC_SELECT_TEXT, OnSelectText)
	ON_BN_CLICKED(IDC_CHECK_DRAG, OnCheckDrag)
	ON_BN_CLICKED(IDC_RADIO_DISABLE, OnRadioDisable)
	ON_BN_CLICKED(IDC_RADIO_FULLROW, OnRadioFullrow)
	ON_BN_CLICKED(IDC_RADIO_HIDE, OnRadioHide)
    ON_BN_CLICKED(IDC_BUTTON_ADDITEM, OnAddItem)
	ON_BN_CLICKED(IDC_BUTTON_ARROW, OnButtonArrow)
	ON_BN_CLICKED(IDC_BUTTON_SCROLLBK, OnButtonScrollbk)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON_TURN, OnButtonTurn)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, OnButtonMove)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListTestDlg message handlers

BOOL CListTestDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	SetBkImage(IDB_BITMAP1);
    SetBkColor(RGB(255,255,0), RGB(255,255,255));
    InitList();
    m_btnNew.EnableWindow(FALSE);

    m_ckEnable.SetCheck(1);
    m_ckHot.SetCheck(1);
    m_ckSort.SetCheck(1);
    m_ckDrag.SetCheck(1);
    m_raToolTip3.SetCheck(2);

    m_ckDrag.SetTooltipText("ÍÏ¶¯");
    m_ckDrag.SizeToContent();
    m_ckDrag.SetBitmaps(IDB_B_SPK1, IDB_B_SPK4,0,0, IDB_B_SPK2, IDB_B_SPK5,IDB_B_SPK3, IDB_B_SPK6);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CListTestDlg::InitList()
{
    m_list.InsertColumn(0, "Column1", LVCFMT_RIGHT, 140);
	m_list.InsertColumn(1, "Column2", LVCFMT_LEFT, 900);
	m_list.InsertColumn(2, "Column3", LVCFMT_CENTER, 90);
	m_list.InsertColumn(3, "Column4", LVCFMT_RIGHT, 90);
    
    CString str;
    for (int i = 0; i < 6; i++)
    {
        str.Format("(%d,0)",i);
        m_list.InsertItem(i, str);
        m_list.SetItemData(i, i);
        for (int j = 1; j < 10; j++)
        {
            str.Format("(%d,%d)",i,j);
            m_list.SetItemText(i, j, str);
        }
    }
    m_list.SetItemText(4, 0, "This is test tool tips.");
    CRect rect; 
    m_list.GetWindowRect(rect);
    ScreenToClient(rect);
    rect.left += 10;
    rect.right += 40;
//    m_list.MoveWindow(0, 0, rect.Width(), rect.Height());
 //   m_list.MoveWindow(rect);

    m_list.EnableWindow(FALSE);
 //   m_list.SetCompareFun(MCompare, (LPARAM)&m_list);
 
    m_list.EnableToolTips();
 //   m_list.SetTitleFrameColor(RGB(255,255,0));
    m_list.SetTitleDivideColor(RGB(222,255,0), PS_DOT);

    m_listHide.ShowWindow(SW_HIDE);
  //  m_list.SetFrameColor(1, FALSE, FALSE);
    
    CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST3);
    if (pList)
    {
        pList->InsertColumn(0, "Column1", LVCFMT_RIGHT, 140);
        pList->InsertColumn(0, "Column1", LVCFMT_RIGHT, 140);
        pList->InsertColumn(0, "Column1", LVCFMT_RIGHT, 140);
        pList->InsertColumn(0, "Column1", LVCFMT_RIGHT, 140);
        pList->EnableWindow(FALSE);
    }

}


int CListTestDlg::MCompare(LPARAM lp1, LPARAM lp2, LPARAM lp3, LPARAM lp4)
{/*

    int bRev = ((lp4-lp1)*(lp4-lp1)-(lp4-lp2)*(lp4-lp2));
    if (bRev > 0)
    {
        return -1;
    }
    else if (bRev < 0)
    {
        return 1;
    }
    return 0;*/
    CSkinListCtrl* pList = (CSkinListCtrl*)lp3;
    CString str1 = pList->GetItemText(lp1, lp4);
    CString str2 = pList->GetItemText(lp2, lp4);
   
        return str1.Compare(str2.GetBuffer(0));

}

void CListTestDlg::OnHeadBk() 
{
	// TODO: Add your control notification handler code here
    COLORREF cr = GetColor();
    if (cr == (DWORD)-1)
    {
        return;
    }
    m_list.SetTitleBkColor(cr);
}

COLORREF CListTestDlg::GetColor()
{
	CColorDialog dlg;

    if (dlg.DoModal() != IDOK)
    {
        return -1;
    }
    return dlg.GetColor();
}

void CListTestDlg::OnListText() 
{
	// TODO: Add your control notification handler code here
    COLORREF cr = GetColor();
    if (cr == (DWORD)-1)
    {
        return;
    }
    m_list.SetTitleTextColor(cr);
	
}

void CListTestDlg::OnListFont() 
{
	// TODO: Add your control notification handler code here
	CFontDialog dlg;
    if (dlg.DoModal() != IDOK)
    {
        return;
    }
   LOGFONT lf;
   memcpy(&lf, dlg.m_cf.lpLogFont, sizeof(LOGFONT));

   if (m_font.m_hObject)
   {
       m_font.DeleteObject();
   }
   VERIFY(m_font.CreateFontIndirect(&lf));
   // Done with the font. Delete the font object.
    m_list.SetTitleFont(&m_font);
}

void CListTestDlg::OnItemBk() 
{
	// TODO: Ad1d your control notification handler code here
    COLORREF cr1 = GetColor();
    if (cr1 == (DWORD)-1)
    {
        return;
    }
    COLORREF cr2 = GetColor();
    if (cr2 == (DWORD)-1)
    {
        return;
    }
    m_list.SetTextBkColor(cr1,cr2);
	
}

void CListTestDlg::OnItemText() 
	
{
	// TODO: Add your control notification handler code here
    COLORREF cr1 = GetColor();
    if (cr1 == (DWORD)-1)
    {
        return;
    }
    COLORREF cr2 = GetColor();
    if (cr2 == (DWORD)-1)
    {
        return;
    }
    m_list.SetTextColor(cr1,cr2);	
}

void CListTestDlg::OnItemFont() 
{
	// TODO: Add your control notification handler code here
	CFontDialog dlg;
    if (dlg.DoModal() != IDOK)
    {
        return;
    }
   LOGFONT lf;
   memcpy(&lf, dlg.m_cf.lpLogFont, sizeof(LOGFONT));

   if (m_fontText.m_hObject)
   {
       m_fontText.DeleteObject();
   }
   VERIFY(m_fontText.CreateFontIndirect(&lf));
   // Done with the font. Delete the font object.
    m_list.SetTextFont(&m_fontText);
	
}

void CListTestDlg::OnCheckHot() 
{
	// TODO: Add your control notification handler code here
    m_list.EnableHighlight(m_ckHot.GetCheck());
}

void CListTestDlg::OnCheckSort() 
{
	// TODO: Add your control notification handler code here
	m_list.EnableSort(m_ckSort.GetCheck());
}

void CListTestDlg::OnCheckEable() 
{
	// TODO: Add your control notification handler code here
	m_list.EnableWindow(!m_list.IsWindowEnabled());
}

void CListTestDlg::OnHighlightBk() 
{
	// TODO: Add your control notification handler code here
    COLORREF cr = GetColor();
    if (cr == -1)
    {
        return;
    }
	m_list.SetHighlightColor(-1,cr);
	
}

void CListTestDlg::OnHighlightText() 
{
	// TODO: Add your control notification handler code here
    COLORREF cr = GetColor();
    if (cr == -1)
    {
        return;
    }
	m_list.SetHighlightColor(cr);
	
}

void CListTestDlg::OnSelectBk() 
{
	// TODO: Add your control notification handler code here
    COLORREF cr = GetColor();
    if (cr == -1)
    {
        return;
    }
	m_list.SetSelectColor(-1,cr);
//    m_list.SetColumnBkColor(0, cr);
	
}

void CListTestDlg::OnSelectText() 
{
	// TODO: Add your control notification handler code here
    COLORREF cr = GetColor();
    if (cr == -1)
    {
        return;
    }
	m_list.SetSelectColor(cr);
}

void CListTestDlg::OnCheckDrag() 
{
	// TODO: Add your control notification handler code here
	m_list.EnableHeadDragDrop(m_ckDrag.GetCheck());
}

void CListTestDlg::OnRadioDisable() 
{
	// TODO: Add your control notification handler code here
    m_list.SetToolTipStyle(CSkinListCtrl::TTS_DISABLE);
}

void CListTestDlg::OnRadioFullrow() 
{
	// TODO: Add your control notification handler code here
    m_list.SetToolTipStyle(CSkinListCtrl::TTS_WHOLEROW);
}

void CListTestDlg::OnRadioHide() 
{
	// TODO: Add your control notification handler code here
    m_list.SetToolTipStyle(CSkinListCtrl::TTS_HIDEITME);
	
}

void CListTestDlg::OnAddItem()
{
    m_list.DeleteAllItems();
    int nCount = m_list.GetItemCount();

    m_list.Invalidate();

    static BOOL bEnable = TRUE;
    m_btnNew.EnableWindow(bEnable);
    bEnable = !bEnable;
}

void CListTestDlg::OnButtonArrow() 
{
	// TODO: Add your control notification handler code here
	COLORREF cr = GetColor();
    if (cr == -1)
    {
        return;
    }
//    m_list.SetScrollArrowColor(cr);
}

void CListTestDlg::OnButtonScrollbk() 
{
	// TODO: Add your control notification handler code here
	COLORREF cr = GetColor();
    if (cr == -1)
    {
        return;
    }
    COLORREF cr2 = GetColor();
 //   m_list.SetScrollBkColor(cr, cr2);
	
}

void CListTestDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
   
 /*
   POSITION pos = m_list.GetFirstSelectedItemPosition();

    if (pos == NULL)
    {
        m_date = "";
    }
    else
    {
 //   int nItem = m_list.GetNextSelectedItem(pos);
 //   m_date = m_list.GetItemText(nItem, 0);
    }
//    UpdateData(FALSE);*/

	*pResult = 0;
}

void CListTestDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
    POSITION pos = m_list.GetFirstSelectedItemPosition();

    if (pos == NULL)
    {
        m_date = "";
    }
    else
    {
        int nItem = m_list.GetNextSelectedItem(pos);
        m_date = m_list.GetItemText(nItem, 0);
    }
    UpdateData(FALSE);	
 /*
       static int a = 0;
        TRACE("\n_____%d", a++);*/
    
	*pResult = 0;
}

void CListTestDlg::OnButtonTurn() 
{
	// TODO: Add your control notification handler code here
    static bool bTurn = false;
  //  m_list.ShowWindow(bTurn ? SW_SHOW:SW_HIDE);
  //  m_listHide.ShowWindow(bTurn ? SW_HIDE:SW_SHOW);
    m_list.EnableWindow(bTurn);
	bTurn = !bTurn;
}

void CListTestDlg::OnButtonMove() 
{
	// TODO: Add your control notification handler code here
    static bool bType = false;
    CRect rect;
	GetWindowRect(rect);
    rect.OffsetRect(5, 5);
  //  ScreenToClient(rect);
    if (bType) 
    {
        rect.right += 40;
    }
    else
    {
        rect.right -= 40;
    }
    bType = !bType;
//    m_list.MoveWindow(0, 0, rect.Width(), rect.Height());
    MoveWindow(rect);
}

void CListTestDlg::OnSize(UINT nType, int cx, int cy) 
{
	CBMPDlg::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
    if (m_list.m_hWnd == NULL) 
    {
        return;
    }
	CRect rect;
    GetClientRect(rect);

    rect.top = 30;
    rect.left = 20;
    rect.bottom /= 2;
    rect.right -= 30;
    m_list.MoveWindow(rect);
}

#define MES_UNDO        _T("&Undo")
#define MES_CUT         _T("Cu&t")
#define MES_COPY        _T("&Copy")
#define MES_PASTE       _T("&Paste")
#define MES_DELETE      _T("&Delete")
#define MES_SELECTALL   _T("Select &All")



void CListTestDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	 SetFocus();
    CSkinMenu menu;
    menu.CreatePopupMenu();

    BOOL bm = CSkinMenu::IsMenu(menu.m_hMenu);
    BOOL bReadOnly = TRUE;
    DWORD flags =  0;
    menu.InsertMenu(0, MF_BYPOSITION | flags, EM_UNDO,
        MES_UNDO);

    DWORD sel = 0;
    flags = LOWORD(sel) == HIWORD(sel) ? MF_GRAYED : 0;
    menu.InsertMenu(2, MF_BYPOSITION | flags, WM_COPY,
        MES_COPY);

    flags = (flags == MF_GRAYED || bReadOnly) ? MF_GRAYED : 0;
    menu.InsertMenu(2, MF_BYPOSITION | flags, WM_CUT,
        MES_CUT);
    menu.InsertMenu(4, MF_BYPOSITION | flags, WM_CLEAR,
        MES_DELETE);

  

    menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON |
        TPM_RIGHTBUTTON, point.x, point.y, this);
}
