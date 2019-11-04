
#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinSheet
COLORREF CSkinSheet::m_s_crBk = RGB(234,236,239);
IMPLEMENT_DYNAMIC(CSkinSheet, CPropertySheet)

CSkinSheet::CSkinSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
    Init();
}


CSkinSheet::CSkinSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
    Init();
}

CSkinSheet::~CSkinSheet()
{
    delete m_pTab;
    m_pTab = NULL;
}


BEGIN_MESSAGE_MAP(CSkinSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CSkinSheet)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinSheet message handlers

BOOL CSkinSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
    m_bWizard = m_psh.dwFlags & PSH_WIZARD;
    CTabCtrl *pTab = GetTabControl();
	if (NULL != pTab && !m_bWizard) 
	{
        m_pTab->SubclassWindow(pTab->GetSafeHwnd());

        if (!m_bCreate) 
        {
            CRect rcTab;
            m_pTab->GetWindowRect(&rcTab);
            ScreenToClient(&rcTab);
            rcTab.top += m_nCapHeight;
            rcTab.OffsetRect(3, 0);
            m_pTab->MoveWindow(&rcTab,TRUE);
        }
        m_btnOK.SubclassDlgItem(IDOK, this);
        m_btnApply.SubclassDlgItem(ID_APPLY_NOW, this);
	}
    else
    {
        m_btnFinish.SubclassDlgItem(ID_WIZFINISH, this);
        m_btnNext.SubclassDlgItem(ID_WIZNEXT, this);
        m_btnBack.SubclassDlgItem(ID_WIZBACK, this);
        if (NULL != pTab) 
        {
            pTab->ShowWindow(SW_HIDE);
        }
    }
	SetActivePage(0);

    m_btnHelp.SubclassDlgItem(IDHELP, this);
    m_btnCancel.SubclassDlgItem(IDCANCEL, this);
        
    if (m_bCreate) 
    {
        return bResult;
    }
    CRect rcWindow;
    GetWindowRect(rcWindow);
    rcWindow.bottom -= m_nCapHeight;
    MoveWindow(rcWindow);
    
    GetClientRect(m_rcCaption);
    m_rcCaption.bottom = m_nCapHeight;
	return bResult;
}

BOOL CSkinSheet::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
    BOOL bResult = CPropertySheet::OnEraseBkgnd(pDC);
    pDC->SelectObject(GetFont());
	CRect rcClient;
    GetClientRect(rcClient);
    CUITools::DrawStepBk(pDC, RGB(105,146,214), RGB(34,52,88), rcClient, rcClient);

    if (!m_bCreate) 
    {
        pDC->FillSolidRect(0, m_nCapHeight, rcClient.right, 1, m_crBk);

        pDC->FillSolidRect(HMARGIN, m_nCapHeight+VMARGIN, rcClient.Width()-HMARGIN*2,
            rcClient.Height()-m_nCapHeight-VMARGIN*2, m_crBk);

        rcClient.top = 0;
        rcClient.left += HMARGIN;
        rcClient.bottom = m_nCapHeight;

        CString strTitle;
        GetWindowText(strTitle);
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(m_crBk);
        pDC->DrawText(strTitle, rcClient, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
    }


	return bResult;
}

BOOL CSkinSheet::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
    cs.style &= ~(WS_SYSMENU|WS_CAPTION);
	return CPropertySheet::PreCreateWindow(cs);
}

void CSkinSheet::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(WS_SYSMENU|WS_CAPTION, 0);
    ModifyStyleEx(WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE|WS_EX_STATICEDGE
        |WS_EX_DLGMODALFRAME, 0);
	CPropertySheet::PreSubclassWindow();
}

void CSkinSheet::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (point.y <= m_nCapHeight && !m_bCreate)
    {
        PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
    }
	CPropertySheet::OnLButtonDown(nFlags, point);
}

void CSkinSheet::Init()
{
    m_pTab  = new CSkinTab;
    m_psh.dwFlags &= ~PSH_HASHELP;
    m_nCapHeight = 20;

    m_crBk = m_s_crBk;
    m_bWizard = FALSE;
    m_rcCaption.SetRect(0,0,0,0);
    m_bCreate = FALSE;
}

CSkinTab* CSkinSheet::GetSkinTab()
{
    return m_pTab;
}

void CSkinSheet::FreshButton()
{

}

void CSkinSheet::MovePage(CPropertyPage *pPage)
{
    InvalidateRect(m_rcCaption);
    if (NULL == pPage || !m_bWizard) 
    {
        return;
    }
    CRect rcWindow;
    pPage->GetWindowRect(rcWindow);
    rcWindow.top += m_nCapHeight;
    ScreenToClient(rcWindow);
    pPage->MoveWindow(rcWindow);
}
