// LibTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LibTest.h"
#include "LibTestDlg.h"
#include "..\prj_win32\Resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CLibTestDlg dialog

CLibTestDlg::CLibTestDlg(CWnd* pParent /*=NULL*/)
	: CBMPDlg(CLibTestDlg::IDD, pParent)
{

	//{{AFX_DATA_INIT(CLibTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLibTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CBMPDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLibTestDlg)
	DDX_Control(pDX, IDC_EDIT2, m_siEdit);
	DDX_Control(pDX, IDC_BUTTON3, m_colorsel);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_BUTTON2, m_btnPos);
	DDX_Control(pDX, IDC_EDIT1, m_medit);
	DDX_Control(pDX, IDC_LIST1, m_checklist);
	DDX_Control(pDX, IDC_STATIC_GROUP, m_Group);
	DDX_Control(pDX, IDC_SPIN_TEST, m_Spin);
	DDX_Control(pDX, IDC_STATIC_MULLINE, m_staticMuLIne);
	DDX_Control(pDX, IDC_BUTTON_MENU, m_btMenu);
	DDX_Control(pDX, IDC_COMBO_SKIN, m_comboxSkin);
	DDX_Control(pDX, IDC_STATIC_HIDE, m_StaticHide);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipCtrl);
	DDX_Control(pDX, IDC_EDIT_SKIN, m_editSingle);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_Static);
	DDX_Control(pDX, IDC_BUTTON_LIST, m_btList);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
    DDX_ColourPicker(pDX, IDC_BUTTON3, m_crTest);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLibTestDlg, CBMPDlg)
	//{{AFX_MSG_MAP(CLibTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LIST, OnButtonList)
	ON_UPDATE_COMMAND_UI(IDM_MENUBT_ITEM, OnUpdateMenubtItem)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_MEASUREITEM()
	ON_COMMAND(IDM_MENUBT_ITEM1, OnMenubtItem1)
	ON_BN_CLICKED(IDC_BUTTON_MOVEIP, OnButtonMoveip)
    ON_WM_MENUCHAR()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_EN_SETFOCUS(IDC_EDIT2, OnSetfocusEdit2)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_USER + 123, On_MenuCallback)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibTestDlg message handlers

BOOL CLibTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
    
	SetBkImage(IDB_BITMAP1);
 //   SetBkColor(RGB(255,255,0),RGB(255,0,0));
    m_btList.SizeToContent(TRUE);
    m_btList.SetBitmaps(IDB_BITMAP5,IDB_BITMAP5,IDB_BITMAP2,IDB_BITMAP3);
    m_btList.SetTooltipText("结束会议");

    m_btnPos.SetBitmaps(IDB_BITMAP5,IDB_BITMAP5,IDB_BITMAP2,IDB_BITMAP3);
    LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 28;
	strcpy(lf.lfFaceName, "Verdana");
	m_font.CreateFontIndirect(&lf);
    m_Static.SetFont(&m_font);
    m_Static.SetTextColor(RGB(123,45,67));

    m_btnPos.SetFont(&m_font);

    m_btMenu.SetMenuEx(IDR_MENU1, m_hWnd);
    m_Menu.LoadMenu(IDR_MENU1);
//    m_Menu.SetBkColor(RGB(0,0,0), RGB(0,0,0));
//    m_Menu.SetTextColor(RGB(255,255,255), RGB(2,2,2));
    SetMenu(&m_Menu);
    m_btMenu.SetMenuCallBack(m_hWnd, WM_USER+123, 0);
    m_comboxSkin.InsertString(0, "test");

//    m_Slider.SetBkTransparent(FALSE);
 //   m_Slider.SetBkImage(IDB_BITMAP6);
  //  m_Slider.SetTickImage(IDB_BITMAP7);

    m_Slider.SetBkColor(RGB(222,222,22));
    m_Slider.ModifyStyle(0, TBS_FIXEDLENGTH);
    m_btMenu.SetTextColor(0,0,0);

    m_staticMuLIne.SetSingleLine();
    CRect rcIp;
    m_ipCtrl.GetWindowRect(rcIp);
    ScreenToClient(rcIp);
    rcIp.right += 30;
    rcIp.left += 30;
    m_ipCtrl.MoveWindow(rcIp);
    m_ipCtrl.SetBkColor(RGB(25,0,0), RGB(22,222,22));
    m_ipCtrl.SetTextColor(RGB(90,200,200), RGB(0,0,0));


    m_Spin.SetRange(0, 100);

    m_checklist.SetBkColor(RGB(23,34,255), RGB(12,34,56), RGB(255,34,56));
    m_checklist.AddString("dfadfff");

    m_tab.InsertItem(0, "   足足咱的  ");
    m_tab.InsertItem(1, "   adfdf  ");
    m_tab.InsertItem(2, "   adfdf  ");
    m_tab.InsertItem(3, "   adfdf  ");
    m_tab.InsertItem(4, "   adfdf  ");
    m_tab.InsertItem(5, "   adfdf  ");
    m_crTest = RGB(1,1,234);
    m_tab.SetMask(IDB_BITMAP8, IDB_BITMAP11, IDB_BITMAP9, IDB_BITMAP10);
   	// TODO: Add extra initialization her
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLibTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLibTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLibTestDlg::OnButtonList() 
{
	// TODO: Add your control notification handler code here
	
    m_dlg.DoModal();
}

void CLibTestDlg::OnUpdateMenubtItem(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
  /*
      static BOOL bCheck = TRUE;
        bCheck = !bCheck;
    	pCmdUI->SetCheck(bCheck);
        if (pCmdUI->m_pMenu != NULL)
        {
            pCmdUI->m_pMenu->CheckMenuItem(pCmdUI->m_nIndex, MF_BYPOSITION
                |(bCheck ? MF_CHECKED : MF_UNCHECKED));
        }
        else
        {
      //      ASSERT((pCmdUI->m_pOther != NULL);
    		if (pCmdUI->m_pOther->SendMessage(WM_GETDLGCODE) & DLGC_BUTTON)
    			pCmdUI->m_pOther->SendMessage(BM_SETCHECK, bCheck);
        }*/
    
    
}

LRESULT CLibTestDlg::On_MenuCallback(WPARAM wParam, LPARAM lParam)
{
    static BOOL bCheck = TRUE;
    bCheck = !bCheck;
    CSkinMenu* pMenu = (CSkinMenu*) wParam;
    pMenu->EnableMenuItem(IDM_MENUBT_ITEM, bCheck);
    pMenu->DeleteMenu(4, MF_BYPOSITION);
    return 0 ;
}

void CLibTestDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
    static BOOL bEnable = FALSE;
	this->m_ipCtrl.EnableWindow(bEnable);
    this->m_btMenu.EnableWindow(bEnable);
    m_Group.EnableWindow(bEnable);
 //   m_editSingle.EnableWindow(bEnable);
    m_ipCtrl.ShowWindow(bEnable ? SW_SHOW:SW_HIDE);
    m_editSingle.ShowWindow(bEnable ? SW_SHOW:SW_HIDE);
    m_comboxSkin.EnableWindow(bEnable);
    GetDlgItem(IDC_COMBO1)->EnableWindow(bEnable);
    bEnable = !bEnable;
}

void CLibTestDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl == 1)
    {
        lpMeasureItemStruct->itemHeight = 12;
    }
	CBMPDlg::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


LRESULT CLibTestDlg::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	// TODO: Add your message handler code here and/or call default
    if (CSkinMenu::IsMenu(pMenu->m_hMenu)) 
	{
        return ((CSkinMenu*)pMenu)->OnSkinMenuChar(nChar, nFlags, pMenu);
	}
	return CDialog::OnMenuChar(nChar, nFlags, pMenu);
}

void CLibTestDlg::OnMenubtItem1() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("菜单1");
}

void CLibTestDlg::OnButtonMoveip() 
{
	// TODO: Add your control notification handler code here
/*    m_Group.Invalidate();
	CRect rect;
    m_ipCtrl.GetWindowRect(rect);
    ScreenToClient(rect);

    rect.right += 30;
    rect.top += 3;
    m_ipCtrl.MoveWindow(rect, TRUE);

    DWORD ip;
    m_ipCtrl.GetAddress(ip);
    //*/
    ::SendMessage(m_checklist.m_hWnd, LB_MSGMAX, 0, 1);
 //   m_checklist.SetCheck(0, TRUE);
    static BOOL bEnable = FALSE;
    m_btnPos.EnableWindow(bEnable);
    bEnable = !bEnable;
    //*/
}

void CLibTestDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
    static CFlatButton::enTextPos aType[10]
        = {CFlatButton::TEXT_POS_LEFTTOP,     CFlatButton::TEXT_POS_TOP,
        CFlatButton::TEXT_POS_RIGHTTOP,
          CFlatButton::TEXT_POS_LEFT,        CFlatButton::TEXT_POS_CENTER,    
          CFlatButton::TEXT_POS_RIGHT,
          CFlatButton::TEXT_POS_LEFTBOTTOM,  CFlatButton::TEXT_POS_BOTTOM,    
          CFlatButton::TEXT_POS_RIGHTBOTTOM,
          CFlatButton::TEXT_POS_CUSTOM};
    static int i = 0;
    if (i < 10)
    {
	    m_btnPos.SetShowText(TRUE, aType[i++]);
        m_btnPos.Invalidate(TRUE);
        return;
    }

    CPoint pt;
    ::GetCursorPos(&pt);
    m_btnPos.ScreenToClient(&pt);
    m_btnPos.SetShowText(TRUE, pt);
    m_btnPos.Invalidate(TRUE);
    
}

void CLibTestDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
    m_siEdit.SetFocus();
}

void CLibTestDlg::OnSetfocusEdit2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    CSkinMenu::m_s_crBk[0] = m_crTest;
    CSkinMenu::m_s_crBk[1] = m_crTest;
	
}
