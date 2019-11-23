// tpToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "moontool.h"
#include "moontoolDlg.h"
#include "../../common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace AutoTinyXml;

/////////////////////////////////////////////////////////////////////////////
// CTpToolsDlg dialog

extern EM_SERVERAPP_TYPE g_emServerType;

CTpToolsDlg::CTpToolsDlg(CWnd* pParent /*=NULL*/)
	: CTransparentDlgBase(CTpToolsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTpToolsDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pComboWnd = NULL;
}

void CTpToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CTransparentDlgBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTpToolsDlg)
//	DDX_Control(pDX, IDC_STATIC_UMSTAB, m_stUmsTab);
//	DDX_Control(pDX, IDC_STATIC_CNSTAB, m_stCnsTab);
	DDX_Control(pDX, IDC_STATIC_VERSION, m_stVersion);
	DDX_Control(pDX, IDC_BTN_MIN, m_btnMin);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_BTN_LOGIN, m_btnLogin);
	DDX_Control(pDX, IDC_RADIO_UMS, m_btnRadioUms);
	DDX_Control(pDX, IDC_RADIO_CNS, m_btnRadioCns);
	DDX_Control(pDX, IDC_STATIC_WARNINGICON, m_stWarningIcon);
	DDX_Control(pDX, IDC_STATIC_WARNINGTEXT, m_stWarningText);
//	DDX_Control(pDX, IDC_STATIC_MOONTAB, m_stMoonTab);
	DDX_Control(pDX, IDC_STATIC_MOON, m_btnRadioMoon);
	DDX_Control(pDX, IDC_Static_CopyRight, m_stCoryRight);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTpToolsDlg, CTransparentDlgBase)
	//{{AFX_MSG_MAP(CTpToolsDlg)
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_BN_CLICKED(IDC_BTN_MIN, OnBtnMin)
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
// 	ON_BN_CLICKED(IDC_RADIO_UMS, OnRadioUms)
// 	ON_BN_CLICKED(IDC_RADIO_CNS, OnRadioCns)
// 	ON_BN_CLICKED(IDC_RADIO_MOON, OnRadioMoon)
	ON_MESSAGE( WM_CLICK_COMBOLISTICON, OnComboClickListIcon )
	ON_MESSAGE( WM_TPTOOL_LOGINRESULT, OnLoginResult )
	ON_MESSAGE( WM_EDIT_CHANGED, OnIpAddrChange )
	ON_MESSAGE( WM_CLICK_COMBOLIST, OnComboClickList )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTpToolsDlg message handlers
BOOL CTpToolsDlg::InitControl()
{
	//初始化对话框
	this->SetWindowPos( NULL, 0, 0, 454, 282, SWP_SHOWWINDOW );
	this->SetWindowText("网呈维护工具");
	AfxGetMainWnd()->CenterWindow();
	this->SetImage( "res\\background.png" );

	CRect rectClient;
	this->GetClientRect(&rectClient);

	//初始化控件
	m_stCoryRight.SetImage("res\\Copyright.png");
	m_stCoryRight.SetWindowPos( NULL, rectClient.Width()/2-m_stCoryRight.GetImageSize().cx-111,  rectClient.bottom - 29, m_stCoryRight.GetImageSize().cx, m_stCoryRight.GetImageSize().cy, SWP_SHOWWINDOW );


	CString strVersion = "             2012-2019 苏州科达科技股份有限公司 ";
	strVersion += KDV_NMS_MOONTOOL_VER_PREFIX_90H;
	strVersion = strVersion.Left(strVersion.GetLength()-1);
	m_stVersion.SetWindowPos( NULL, 0,  rectClient.bottom - 31, rectClient.Width(), 14, SWP_SHOWWINDOW );
	m_stVersion.SetWindowText(strVersion);
//	m_stVersion.SetWindowText("CoryRight(c) 2012-2015 苏州科达科技股份有限公司 v1.1.4.0.0");

    m_stVersion.SetFont( 9, "宋体" );
	m_stVersion.SetTextAlign(StringAlignmentCenter);
	m_stVersion.SetTextColor(Color( 142, 141, 141 ));	

	m_btnClose.SetImage( "res\\CloseBtn");
	m_btnClose.SetWindowPos( NULL, rectClient.right - m_btnClose.GetImageSize().cx - 17, 8, m_btnClose.GetImageSize().cx, 
	m_btnClose.GetImageSize().cy, SWP_SHOWWINDOW );

	m_btnMin.SetImage( "res\\MinBtn");
	m_btnMin.SetWindowPos( NULL, rectClient.right - m_btnClose.GetImageSize().cx - m_btnMin.GetImageSize().cx - 17, 8, m_btnMin.GetImageSize().cx, 
	m_btnMin.GetImageSize().cy, SWP_SHOWWINDOW ); 

	m_btnLogin.SetImage( "res\\LoginBtn");
	m_btnLogin.SetWindowPos( NULL, rectClient.right - m_btnLogin.GetImageSize().cx - 37, 148 + 5,
	m_btnLogin.GetImageSize().cx, m_btnLogin.GetImageSize().cy, SWP_SHOWWINDOW );

// 	m_stUmsTab.SetImage( "res\\tabumssel.png" );
// 	m_stUmsTab.SetWindowPos( NULL, 8, 61, m_stUmsTab.GetImageSize().cx, m_stUmsTab.GetImageSize().cy, SWP_SHOWWINDOW );
// 	
// 	m_stCnsTab.SetImage( "res\\tabcnssel.png" );
// 	m_stCnsTab.SetWindowPos( NULL, 8, 61, m_stCnsTab.GetImageSize().cx, m_stCnsTab.GetImageSize().cy, SWP_HIDEWINDOW );

// 	m_stMoonTab.SetImage( "res\\tabmoonsel.png" );
// 	m_stMoonTab.SetWindowPos( NULL, 8, 61, m_stMoonTab.GetImageSize().cx, m_stMoonTab.GetImageSize().cy, SWP_HIDEWINDOW );

//  m_btnRadioUms.SetImage( "res\\CheckUMS");
//  m_btnRadioUms.SetWindowPos( NULL, 8, rectClient.top + 61, 219, 60, SWP_SHOWWINDOW );
// 
// 	m_btnRadioCns.SetImage( "res\\CheckCns");
// 	m_btnRadioCns.SetWindowPos( NULL, 227, rectClient.top + 61, 219, 60, SWP_SHOWWINDOW );

#ifndef _MOON904K30
	m_btnRadioMoon.SetImage("res\\CheckMoon");
	m_btnRadioMoon.SetWindowPos( NULL, 120, rectClient.top + 61, 219, 60, SWP_SHOWWINDOW );
#else
    m_btnRadioMoon.SetImage("res\\CheckMoon904K30");
	m_btnRadioMoon.SetWindowPos( NULL, 172, rectClient.top + 71, 114, 50, SWP_SHOWWINDOW );
#endif
// 	m_btnRadioUms.SetCheck(BST_CHECKED);
// 	m_btnRadioCns.SetCheck(BST_UNCHECKED);
//	m_btnRadioMoon.SetCheck(BST_UNCHECKED);

	//ComboBox IP
	m_pComboWnd = new CTransparentComboBox( "ComboBox", this, CRect(0,0,296,50),  
		0, WS_CHILD|WS_CLIPSIBLINGS );
	if( m_pComboWnd != NULL )
	{
		m_pComboWnd->SetIpStyle(TRUE);
		m_pComboWnd->SetImage("res\\Combobox");
		m_pComboWnd->SetReadOnly(FALSE);
		m_pComboWnd->MoveWindow(CRect( 31, 148, 296, 50 ));
		m_pComboWnd->SetEditFrontLen(16);
		m_pComboWnd->SetEditBackLen(11);
		m_pComboWnd->SetTextColor( Color( 149, 149, 149), Color( 78, 78, 78 ) );
		m_pComboWnd->SetDisableColor( Color( 132, 132, 132 ) );
		m_pComboWnd->SetWindowPos( NULL, 31, 148, 296, 50, SWP_NOACTIVATE|SWP_SHOWWINDOW );

		m_pComboWnd->SetTipColor( Color(149, 149, 149) );
		m_pComboWnd->SetTipFont( 9, "宋体" );
		m_pComboWnd->SetTipStr("请配置登录IP");

		ReadIpAddr();
	}

	m_stWarningIcon.SetImage( "res\\warning.png" );
	m_stWarningIcon.SetWindowPos( NULL, 40, 198, m_stWarningIcon.GetImageSize().cx, m_stWarningIcon.GetImageSize().cy, SWP_HIDEWINDOW );

	s32 nTextXPos = m_stWarningIcon.GetImageSize().cx + 5;
	m_stWarningText.SetWindowPos( NULL, 40 + nTextXPos, 198, /*296 - nTextXPos - 10*/rectClient.right - 37 - 40 - nTextXPos+10, 30, SWP_SHOWWINDOW );
	m_stWarningText.SetWindowText("");
    m_stWarningText.SetFont( 9, "宋体" );
	m_stWarningText.SetTextAlign(StringAlignmentNear);
	m_stWarningText.SetTextColor(Color( 255, 255, 255 ));

	return TRUE;
}

LRESULT CTpToolsDlg::OnComboClickListIcon( WPARAM wParam, LPARAM lParam )
{
	LPCTSTR strItemText = (LPCTSTR)wParam;

	if ( NULL == m_pComboWnd )
	{
		return 0L;
	}

	if ( (HWND)lParam == m_pComboWnd->GetSafeHwnd() )
	{
		std::vector<CString>::iterator iter = m_vecCombList.begin();
		CString strCurIPAddr;
		CString strText;
		while( iter != m_vecCombList.end() )
		{
			strText = *iter;
			if ( strText == strItemText )
			{
				iter = m_vecCombList.erase(iter);

				if ( NULL != m_pComboWnd )
				{
					strCurIPAddr = m_pComboWnd->GetComboText();

					m_pComboWnd->UpdateComboList(&m_vecCombList);
					
					m_pComboWnd->JumpToSelItem(strItemText);
					
					WriteIpAddr(m_vecCombList);

					if ( strCurIPAddr == strItemText )
					{
						m_pComboWnd->SetComboText("");
					}
				}

				break;
			}
			else
			{
				++iter;
			}
		}

		ClearWarningText();
	}
	
	return 0L;
}

LRESULT CTpToolsDlg::OnIpAddrChange( WPARAM wParam, LPARAM lParam )
{
	ClearWarningText();

	return 0L;
}

LRESULT CTpToolsDlg::OnComboClickList( WPARAM wParam, LPARAM lParam )
{
	ClearWarningText();

	return 0L;
}

BOOL CTpToolsDlg::ClearWarningText()
{
	CString strWarningText;
	m_stWarningText.GetWindowText(strWarningText);
	if ( !strWarningText.IsEmpty() )
	{
		ShowWarningText("");
	}

	return TRUE;
}

BOOL CTpToolsDlg::OnInitDialog()
{
	CTransparentDlgBase::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	::SetWindowLong( this->GetSafeHwnd(), GWL_STYLE, GetWindowLong( this->GetSafeHwnd(), GWL_STYLE) - WS_CAPTION ); //去除标题栏

	//登陆ip存储文件
	m_strIpConfigFullPath = GetModuleFullPath();
	m_strIpConfigFullPath += "LOGINIPCFG\\";
	::CreateDirectory( m_strIpConfigFullPath, NULL );
	m_strIpConfigFullPath += "tptoolcfg.xml"; 

	InitControl();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTpToolsDlg::OnPaint() 
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
		CTransparentDlgBase::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTpToolsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTpToolsDlg::OnDestroy() 
{
	/*if ( UMSTOOLSPACE::IsInitUmsTool() )
	{
		UMSTOOLSPACE::DestoryUmsToolUI();
	}

	if ( CNSTOOL::IsInitCnsTool() )
	{
		CNSTOOL::DestroyCnsTool();
	}*/

	if( NULL != m_pComboWnd )
	{
		delete m_pComboWnd;
		m_pComboWnd = NULL;
	}

	CTransparentDlgBase::OnDestroy();
}

void CTpToolsDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	//非标题栏鼠标拖动对话框
	PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y ) ); 

	CTransparentDlgBase::OnLButtonDown(nFlags, point);
}

void CTpToolsDlg::OnBtnClose() 
{
	CTransparentDlgBase::OnCancel();
}

void CTpToolsDlg::OnBtnMin() 
{
	this->ShowWindow(SW_MINIMIZE);
}

void CTpToolsDlg::OnBtnLogin() 
{ 
	ShowWarningText("");
	
	if ( NULL != m_pComboWnd )
	{
		m_pComboWnd->SetWindowPos( NULL, 31, 148, 296, 50, SWP_NOACTIVATE|SWP_SHOWWINDOW );
		
		CString strIP;
		//IP检测成功
		if ( !CheckIPAddr(strIP) )
		{
			return;
		}
		
		EnableControl(FALSE);				//登陆中对一些按钮的保护
		
		g_emServerType = em_MOONTOOL_APP;
		if ( !MOONTOOL::IsInitMoonTool() )
		{
			MOONTOOL::InitMoonTool( AfxGetMainWnd()->GetSafeHwnd() );
		}
		MOONTOOL::ConnectMoon( (inet_addr(strIP)));
		
	}
}

/*void CTpToolsDlg::OnRadioUms() 
{
	if ( !m_stUmsTab.IsWindowVisible() )
	{
		ClearWarningText();
	}

 	m_stUmsTab.ShowWindow(SW_SHOW);
 	m_stCnsTab.ShowWindow(SW_HIDE);
	m_stMoonTab.ShowWindow(SW_HIDE);
}

void CTpToolsDlg::OnRadioCns() 
{
	if ( !m_stCnsTab.IsWindowVisible() )
	{
		ClearWarningText();
	}

 	m_stUmsTab.ShowWindow(SW_HIDE);
 	m_stCnsTab.ShowWindow(SW_SHOW);
	m_stMoonTab.ShowWindow(SW_HIDE);
}

void CTpToolsDlg::OnRadioMoon()
{
// 	if ( !m_stMoonTab.IsWindowVisible() )
// 	{
// 		ClearWarningText();
// 	}
// 
// 	m_stMoonTab.ShowWindow(SW_SHOW);	
// 	m_stUmsTab.ShowWindow(SW_HIDE);
//  m_stCnsTab.ShowWindow(SW_HIDE);
}
*/

BOOL CTpToolsDlg::CheckIPAddr(CString& strIp)
{
	BOOL bIsEmpty = FALSE;
//	BOOL bIsInvalid  = FALSE;
	CString strIPAddr;
	if ( NULL != m_pComboWnd )
	{
		strIPAddr = m_pComboWnd->GetComboText();
	}
	else
	{
		return FALSE;
	}

	if( strIPAddr.GetLength() == 0 || strIPAddr == "0.0.0.0")
//	if ( bIsEmpty == TRUE )				//IP EDIT为空 取出来的字符串为0.0.0.0
	{
		ShowWarningText( "IP地址不能为空，请重新输入"  );
		
		return FALSE;
	}

	if( !CCallAddr::IsValidIpV4(strIPAddr)  )
	{
		ShowWarningText( "IP 地址非法，请重新输入" );
		
		return FALSE;
	}
	
	strIp = strIPAddr;

	return TRUE;
}

void CTpToolsDlg::ShowWarningText(const CString& strText)
{
	if ( !strText.IsEmpty() )
	{
		m_stWarningIcon.ShowWindow(SW_SHOW);
		m_stWarningText.SetWindowText(strText);
	}
	else
	{
		m_stWarningIcon.ShowWindow(SW_HIDE);
		m_stWarningText.SetWindowText("");
	}

	Invalidate(TRUE);
}

LRESULT CTpToolsDlg::OnLoginResult( WPARAM wParam, LPARAM lParam )
{ 
	EnableControl(TRUE);
	m_btnLogin.EnableWindow(TRUE);

	switch( wParam )
	{
	case em_LOGIN_SUCCESS:
		{
			LoginSuccess();
		}
		break;
	case em_LOGIN_ERROR_RSQ:
		{
			LoginFails((LPCTSTR)lParam);
		}
		break;
	case em_LOGIN_TIMEOUT:
		{
			LoginTimeOut();
		}
		break;
	case em_LOGIN_LOGOFF:
		{
			LoginLogoff();
		}
		break;
	case em_LOGIN_GRAP:
		{
			LoginGrab(lParam);
		}
		break;
	case em_LOGIN_BREAK:
		{
			LoginBreak();
		}
		break;
    case em_LOGIN_REBOOT:
        {
            LoginReboot();
        }
		break;
	default: 
		{
		}
		break;
	}

	return 0L;
}

BOOL CTpToolsDlg::LoginSuccess()
{
	//登陆到umstool or cnstool
	if ( NULL != m_pComboWnd )
	{
		CString strIpAddr;
		strIpAddr = m_pComboWnd->GetComboText();
		if ( strIpAddr.IsEmpty() )
		{
			return FALSE;
		}
		
		std::vector<CString>::iterator iterIpList = find(m_vecCombList.begin(), m_vecCombList.end(), strIpAddr );
		if ( iterIpList == m_vecCombList.end() )
		{
			if ( m_vecCombList.size() < 5 )
			{
				std::reverse( m_vecCombList.begin(), m_vecCombList.end() );
				if ( NULL != m_pComboWnd )
				{
					m_vecCombList.push_back(strIpAddr);
				}
			}
			else
			{	
				m_vecCombList.pop_back();
				
				std::reverse( m_vecCombList.begin(), m_vecCombList.end() );
				m_vecCombList.push_back(strIpAddr);
			}
		}
		else
		{
			std::vector<CString>::iterator iter = m_vecCombList.begin();
			while( iter != m_vecCombList.end() )
			{
				CString strText;
				strText = *iter;
				if ( strText == strIpAddr )
				{
					iter = m_vecCombList.erase(iter);
					std::reverse( m_vecCombList.begin(), m_vecCombList.end() );
					break;
				}
				else
				{
					++iter;
				}
			}
			m_vecCombList.push_back(strIpAddr);
		}
	}
	
	std::reverse( m_vecCombList.begin(), m_vecCombList.end() );
	WriteIpAddr(m_vecCombList);
	
	this->ShowWindow(SW_HIDE);
	ShowWarningText( "" );

	return TRUE;
}

BOOL CTpToolsDlg::LoginFails(CString strErrorText)
{
	CString strRet;
	strRet = "登录";
	if ( m_btnRadioUms.GetCheck() )
	{
		strRet += "ums";
	}
	else if (m_btnRadioCns.GetCheck())
	{
		strRet += "cns";
	}
	else                           
	{
		strRet += "moon90";				
	}
	strRet += "服务器失败，失败原因：";
	strRet += strErrorText;
	if( !strErrorText.IsEmpty() )
	{
		ShowWarningText( strRet );
	}
	
	if ( !this->IsWindowVisible() )
	{
		this->ShowWindow(SW_SHOW);
	}

	return TRUE;
}

BOOL CTpToolsDlg::LoginGrab(u32 dwIP)
{
	CString strIP;
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr =  dwIP;
	strIP = inet_ntoa(addrIPAddr);
	
	CString strIpAddr;
	//strIpAddr.Format( "您已经被[%s]强制下线，该账户已在另一个地方登录", strIP );
    strIpAddr.Format( "您已经被强制下线，该账户已在另一个地方登录" );  //暂不支持IP通知
	ShowWarningText( strIpAddr );
	
	if ( !this->IsWindowVisible() )
	{
		this->ShowWindow(SW_RESTORE);
	}

	return 0L;
}

BOOL CTpToolsDlg::LoginLogoff()
{
	if ( !this->IsWindowVisible() )
	{
		this->ShowWindow(SW_RESTORE);
	}

	return TRUE;
}

BOOL CTpToolsDlg::LoginBreak()
{
	if ( !this->IsWindowVisible() )
	{
		this->ShowWindow(SW_RESTORE);
	}
	
	return TRUE;
}

BOOL CTpToolsDlg::LoginReboot()
{
    /*CString strIpAddr;
    strIpAddr = _T("设备正在重启中，请稍后再试...");
	ShowWarningText( strIpAddr );*/

    if ( !this->IsWindowVisible() )
    {
        this->ShowWindow(SW_RESTORE);
    }
    
    return TRUE;
}

BOOL CTpToolsDlg::LoginTimeOut()
{
	ShowWarningText( "登录服务器请求超时" );
	
	if ( !this->IsWindowVisible() )
	{
		this->ShowWindow(SW_SHOW);
	}

	return TRUE;
}

BOOL CTpToolsDlg::WriteIpAddr(std::vector<CString> vecIpAddr)
{	
    TiXmlDocument doc;  
    TiXmlDeclaration* tiDecl = new TiXmlDeclaration("1.0", "", "");  
    TiXmlElement* tiHeadElement = new TiXmlElement( "Tptool" );  
    TiXmlElement* tiElement = new TiXmlElement( "Element" );
	if ( (NULL == tiElement) || (NULL == tiDecl) || (NULL == tiDecl) )
	{
		return FALSE;
	}

	tiElement->SetAttribute("name", "LoginIpCfg");
	
    TiXmlElement* tiAttrElement = NULL;
	for( s32 nIndex = 0; nIndex < m_vecCombList.size(); nIndex++ )
	{
		CString strAttrHead;
		tiAttrElement = new TiXmlElement("Attribute");
		if( NULL == tiAttrElement )
		{
			continue;
		}
		
		s8 chNum[2];
		memset( chNum, 0 , 2 );
		itoa( nIndex, chNum, 10 );

		strAttrHead = chNum;
		strAttrHead += "st";

		tiAttrElement->SetAttribute("name", strAttrHead);
		tiAttrElement->SetAttribute("ip", m_vecCombList[nIndex] );
		
		tiElement->LinkEndChild(tiAttrElement);  
	}
    tiHeadElement->LinkEndChild(tiElement);  
    
    doc.LinkEndChild(tiDecl);  
    doc.LinkEndChild(tiHeadElement); 
    doc.SaveFile(m_strIpConfigFullPath);
	
	ReadIpAddr();

	return TRUE;
}

BOOL CTpToolsDlg::ReadIpAddr() 
{
	m_vecCombList.clear();
    TiXmlDocument doc;                              
    if (doc.LoadFile(m_strIpConfigFullPath)) 
	{
        doc.Print();
    } 
	else 
	{
        return FALSE;
    }

    TiXmlElement* tiRootElement = doc.RootElement();  
    TiXmlElement* tiHeadElement = tiRootElement->FirstChildElement();
    TiXmlElement* tiElement = tiHeadElement->FirstChildElement(); 
	if ( (NULL == tiRootElement) || (NULL == tiHeadElement) || (NULL == tiElement) )
	{
		return FALSE;
	}

    for (; tiElement != NULL; tiElement = tiElement->NextSiblingElement() ) 
	{
        TiXmlAttribute* tiAttr = tiElement->FirstAttribute(); 
        for (;tiAttr != NULL; tiAttr = tiAttr->Next() ) 
		{ 
			CString strAttrName  = tiAttr->Name();
			CString strAttrValue = tiAttr->Value();
			if ( strAttrName == "ip" )
			{
				m_vecCombList.push_back(strAttrValue);
			}
        }                                   
    }

	if( m_pComboWnd != NULL )
	{
		m_pComboWnd->UpdateComboList(&m_vecCombList);

		m_pComboWnd->SetComboText(m_vecCombList[0]);
	}

	return TRUE;
}

void CTpToolsDlg::EnableControl( BOOL bEnable )
{
	m_btnLogin.EnableWindow(bEnable);
	m_btnRadioUms.EnableWindow(bEnable);
	m_btnRadioCns.EnableWindow(bEnable);
	m_btnRadioMoon.EnableWindow(bEnable);
	if ( NULL != m_pComboWnd )
	{
		m_pComboWnd->SetEnableWindow(bEnable);
	}
}


