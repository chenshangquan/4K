// SkinPage.cpp : implementation file
//

#include "stdafx.h"
#include "UILibhead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinPage property page

IMPLEMENT_DYNCREATE(CSkinPage, CPropertyPage)

CSkinPage::CSkinPage(UINT nIDTemplate) : CPropertyPage(nIDTemplate)
{
	//{{AFX_DATA_INIT(CSkinPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_psp.dwFlags &= ~PSP_HASHELP;
    m_crBk = RGB(234, 236, 239);
}

CSkinPage::~CSkinPage()
{
}

void CSkinPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkinPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSkinPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSkinPage)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinPage message handlers

BOOL CSkinPage::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
    BOOL bRet = CPropertyPage::OnEraseBkgnd(pDC);
	CRect rcClient;
    GetClientRect(rcClient);
    pDC->FillSolidRect(rcClient, m_crBk);
	return bRet;
}

BOOL CSkinPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class

 	CSkinSheet* psheet = (CSkinSheet*) GetParent(); 
    psheet->MovePage(this);
    
	return CPropertyPage::OnSetActive();
}

BOOL CSkinPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSkinPage::SetTitle(LPCSTR strTitle)
{
    m_psp.dwFlags |= PSP_USETITLE;
    m_strTitle = strTitle;
    m_psp.pszTitle = (LPCSTR)m_strTitle;
}
