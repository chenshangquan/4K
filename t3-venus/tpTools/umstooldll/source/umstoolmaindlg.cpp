// umstoolmaindlg.cpp : implementation file
//

#include "stdafx.h"
#include "umstooldll.h"
#include "umstoolmaindlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUmstoolMainDlg dialog

CUmstoolMainDlg::CUmstoolMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUmstoolMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUmstoolMainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUmstoolMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUmstoolMainDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUmstoolMainDlg, CDialog)
	//{{AFX_MSG_MAP(CUmstoolMainDlg)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_LOGOFF, OnBtnLogoff)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_MESSAGE( UI_UMS_CONNECTED,  OnConnectUmsRsp ) 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUmstoolMainDlg message handlers

void CUmstoolMainDlg::RegMsg()
{
	//REG_MSG_HANDLER( UI_CNS_REGSIP_NOTIFY, CUmstoolMainDlg::UpdateSipCfg, m_pRegLogic, CUmstoolMainDlg );
	//REG_MSG_HANDLER( UI_UMS_CONNECTED, CUmstoolMainDlg::OnConnectUms, this, CUmstoolMainDlg );

	REG_MSG( UI_UMS_CONNECTED, GetSafeHwnd() );

}

bool CUmstoolMainDlg::UnRegFunc()
{
	
	return true;
}

BOOL CUmstoolMainDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	RegMsg();

	this->SetWindowPos( NULL, 0, 0, 800, 600, SWP_SHOWWINDOW );//SWP_HIDEWINDOW

	return TRUE; 
}

void CUmstoolMainDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y ) ); 

	CDialog::OnLButtonDown(nFlags, point);
}

void CUmstoolMainDlg::OnBtnLogoff() 
{
	TplArray<CUserFullInfo> tpUserList = DATAMGRPTR->GetUserListData();

	CString strUserNameString;
	strUserNameString += "用户列表如下：\n";
	for ( s32 nIndexPos = 0; nIndexPos < tpUserList.Size(); nIndexPos++ )
	{
		CString strUserName = tpUserList.GetAt(nIndexPos).GetName();
		if( strUserName.IsEmpty() || strUserName == "admin")
		{
			continue;
		}
		if ( !strUserName.IsEmpty() )
		{
			strUserNameString += strUserName;
			strUserNameString += "\n";
		}
	}
	if ( tpUserList.Size() > 0 )
	{
		AfxMessageBox(strUserNameString);
	}

	CSessionIns::Instance()->DesdroySession();

	AfxGetMainWnd()->CenterWindow();

	CDialog::OnOK();
}

void CUmstoolMainDlg::OnBtnExit() 
{
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
}

LRESULT CUmstoolMainDlg::OnConnectUmsRsp(  WPARAM wParam, LPARAM lParam ) 
{   
	if( 0 == wParam )
	{
		::SendMessage( AfxGetMainWnd()->GetSafeHwnd(), WM_UMS_LOGIN_NOTIFY, wParam, lParam );
	}
	else
	{
		AfxGetMainWnd()->SetWindowPos( NULL, -1000, -1000, 800, 600, SWP_SHOWWINDOW );
	
		CRect rect;
		GetClientRect(&rect);
		long curX =  GetSystemMetrics(SM_CXSCREEN );
		long curY = GetSystemMetrics(SM_CYSCREEN);

		this->SetWindowPos( NULL, (curX - rect.Width())/2, (curY - rect.Height())/2, 800, 600, SWP_SHOWWINDOW );

		this->SetFocus();
	}
	
	return NO_ERROR;
}


