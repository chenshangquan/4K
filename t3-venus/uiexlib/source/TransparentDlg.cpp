// TransparentDlg.cpp: implementation of the CTransparentDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TransparentDlg.h"
#include "atlconv.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransparentDlg::CTransparentDlg():
			     CTransparentDlgBase(0, NULL)
{  
	m_pDlgTemp = NULL;
	m_strTxt.Empty();
}

CTransparentDlg::~CTransparentDlg()
{   
	ClearDlgTempBuff(); 
}


BOOL CTransparentDlg::Create( CString strDlgName, CRect rc,DWORD dwStyle, DWORD dwExtendedStyle, CWnd* pParent, BOOL bModal )
{    
	if ( !CheckParam(dwStyle, pParent,bModal) )
	{
	   return FALSE;
	}


	BOOL re = TRUE;
	DLGTEMPLATE* pTempl = ConstructDlgTemp( rc, dwStyle, dwExtendedStyle );

    if ( !bModal )
    { //如果是非模态窗口则直接创建
		re =  CreateIndirect(pTempl, pParent);  
		ClearDlgTempBuff();
		if( re )
		{ 
			////设置标题 
			SetWindowText( strDlgName );
		}
		else
		{
			PrtError( "CTransparentDlg::CreateModeless", "CreateIndirect()=false" );
		} 
    }
	else
	{ 
		m_pParentWnd = pParent;
		m_strTxt = strDlgName; 
	 
	}  

	return re;
}


 

int  CTransparentDlg::DoModal()
{   
	int nRe = -1;
	if( NULL!= m_pDlgTemp )
	{   
		//DLGTEMPLATE* pTempl = ( DLGTEMPLATE* )(m_hDlgTempBuff);
    	BOOL re = InitModalIndirect(m_pDlgTemp, m_pParentWnd); 
	 	if( re )
		{   
		 //	SetWindowText( m_strTxt );
			nRe =	CTransparentDlgBase::DoModal();
		}
		else
		{
			PrtError( "CTransparentDlg::DoModal", "doMoadl fail: InitModalIndirect() = false " );
		}
	     
	}
	else
	{
		PrtError( "CTransparentDlg::DoModal", "doMoadl fail: m_hDlgTempBuff = NULL " );
	}

	return nRe;
}



int  CTransparentDlg::DoModal(CString strDlgName, CRect rc,DWORD dwStyle, DWORD dwExtendedStyle, CWnd* pParent )
{   
	CheckParam(dwStyle, NULL,TRUE);
 
	int nRe = -1;
	DLGTEMPLATE* pTempl = ConstructDlgTemp( rc, dwStyle, dwExtendedStyle );
	BOOL re = InitModalIndirect(pTempl, pParent); 
	if( re )
	{   
		//	SetWindowText( m_strTxt );
		nRe =	CTransparentDlgBase::DoModal();
	}
	else
	{
		PrtError( "CTransparentDlg::DoModal", "doMoadl fail: InitModalIndirect() = false " );
	}

	ClearDlgTempBuff();
	return nRe;
 
}

BOOL CTransparentDlg::IsInModalLoop()
{
	return m_nFlags&WF_MODALLOOP;
}

int CTransparentDlg::StartModalLoop()
{ 
	if ( m_hWnd == NULL )
	{   
		PrtError("CTransparentDlg::BeginModalLoop"," m_hWnd = 0 ");
		return -1;
	}  

	 
	LONG lStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	if( lStyle & WS_CHILDWINDOW )
	{
		PrtError("CTransparentDlg::BeginModalLoop"," 当前窗口为child类型，不可domodal ");
		return -1;
	}
	
 
	if (  (m_nFlags & WF_MODALLOOP) &&  (m_nFlags| WF_CONTINUEMODAL ) )
	{   
		PrtError("CTransparentDlg::BeginModalLoop"," StartModalLoop失败：当前窗口已经处于domodal状态");
	  /*  StopModalLoop(-1);  快速重复调用一个窗口的domoadl时，
		不能及时结束掉modalloop，引起崩溃，添加IsInModalLoop，
		可以在调用startmodal前判断，以避免startmodal失败情况2013.2.28 yjj*/
		
	 	return -1; 
	 
	}
   

	m_nFlags  |=  WF_CONTINUEMODAL;
	
	
  //-------PreModal();-------
	// disable parent  
	// allow OLE servers to disable themselves
	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL)
       pApp->EnableModeless(FALSE);
	// find parent HWND
  	HWND hWndParent =  CWnd::GetSafeOwner_(m_pParentWnd->GetSafeHwnd(), &m_hWndTop);

	if ( hWndParent == m_hWnd )//有时候获取的owner窗口为自身
	{
		hWndParent = AfxGetMainWnd()->GetSafeHwnd();
	}
 
  	BOOL bEnableParent = FALSE;
	if (hWndParent != NULL && ::IsWindowEnabled(hWndParent))
	{
		::EnableWindow(hWndParent, FALSE); 
		bEnableParent = TRUE;
	}

    // find owner HWND
    BOOL bEnableOwner = FALSE;
    HWND hOwnerWnd = NULL;
    CWnd* pWnd = CWnd::FromHandle(m_hWnd);
    if ( pWnd != NULL )
    {
        CWnd* pOwnerWnd = pWnd->GetOwner();
        if ( pOwnerWnd != NULL )
        {
            hOwnerWnd = pOwnerWnd->GetSafeHwnd();
            if (hOwnerWnd != NULL && ::IsWindowEnabled(hOwnerWnd))
            {
                ::EnableWindow(hOwnerWnd, FALSE); 
                bEnableOwner = TRUE;
	        }
        }
    }       
	
	TRY
	{ 
		if (m_nFlags & WF_CONTINUEMODAL)
		{
			// enter modal loop
			DWORD dwFlags = MLF_SHOWONIDLE;
			if (GetStyle() & DS_NOIDLEMSG)
				dwFlags |= MLF_NOIDLEMSG;
			::ShowWindow( m_hWnd, SW_SHOWNORMAL);
			BOOL bOk = SetForegroundWindow(); 
			VERIFY(RunModalLoop(dwFlags) == m_nModalResult);
		}
		
		// hide the window before enabling the parent, etc.
		if (m_hWnd != NULL)
			SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW|
			SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
		 
	}
	CATCH_ALL(e)
	{
		do { e->Delete(); } while (0);
		m_nModalResult = -1;
	}
	END_CATCH_ALL
		

    if ( bEnableOwner && hOwnerWnd != NULL )
    {
        ::EnableWindow(hOwnerWnd, TRUE); 
	}

	if (bEnableParent)
	{
		::EnableWindow(hWndParent, TRUE);
	}

	if (hWndParent != NULL && ::GetActiveWindow() == m_hWnd)
	{
		::SetActiveWindow(hWndParent);
	}
		
	// destroy modal window
    //DestroyWindow();  //2012.12.4 yjj
	   
  //-----------PostModal();---------------
    //AfxUnhookWindowCreate();   // just in case 
	//Detach(); 由于窗口并不销毁，所以无需从handlemap
	//re-enable windows
	if (::IsWindow(m_hWndTop))
	{
		::EnableWindow(m_hWndTop, TRUE);
	} 
	//m_hWndTop = NULL; 
	if (pApp != NULL)
	{
		pApp->EnableModeless(TRUE);
	}
 

	return m_nModalResult;
}
 

void CTransparentDlg::StopModalLoop( int nResult )
{ 
	if ( m_nFlags &( WF_MODALLOOP | WF_CONTINUEMODAL ) && ( NULL != m_hWnd) )   //未在domodal状态，则不进行任何处理 2013.1.31 yjj
	{
		EndModalLoop(nResult);    //解决多个domodal窗口并存可点击下层窗口问题
	} 
}
 

DLGTEMPLATE* CTransparentDlg::ConstructDlgTemp( CRect rc, DWORD dwStyle, DWORD dwExtendedStyle )
{
	ClearDlgTempBuff();     
	int nLen = sizeof(DLGTEMPLATE) + sizeof(DWORD)  + sizeof(DWORD) + sizeof(DWORD) + sizeof(DWORD); //menu + class + title + font 均为0 ,有需要单独设置
    HANDLE h = GlobalAlloc(GHND, nLen); 
	m_pDlgTemp = (DLGTEMPLATE*) GlobalLock(h);  
	
	m_pDlgTemp-> style = dwStyle; //WS_OVERLAPPEDWINDOW | WS_VISIBLE | DS_CENTER | DS_3DLOOK; 
	m_pDlgTemp-> dwExtendedStyle = dwExtendedStyle; 

	m_pDlgTemp-> cdit = 0; 

	//由于DLGTEMPLATE 中使用的是窗口单位，故需要由像素转为以窗口为单位的大小
	//另外，由窗口单位转为像素单位可使用接口：MapDialogRect() 
	CSize base = ::GetDialogBaseUnits(); 
	int xDlg = MulDiv(rc.Width(), 4, base.cx); // rc.Width();
	int yDlg = MulDiv(rc.Height(), 8, base.cy); //rc.Height(); 
    
	int x = MulDiv( rc.left, 8, base.cy);//rc.left; 
	int y = MulDiv( rc.top, 8, base.cy);//rc.top; 

	m_pDlgTemp-> x = x; 
	m_pDlgTemp-> y = y; 
	m_pDlgTemp-> cx = xDlg; 
	m_pDlgTemp-> cy = yDlg;    
    return m_pDlgTemp;

}



void CTransparentDlg::ClearDlgTempBuff()
{
	if ( NULL != m_pDlgTemp )
	{
		GlobalUnlock( (HGLOBAL)m_pDlgTemp ); 
		GlobalFree( (HGLOBAL)m_pDlgTemp );	
		m_pDlgTemp = NULL;
		m_pParentWnd = NULL;
		m_strTxt = "";
		
	}
}


BOOL CTransparentDlg::CheckParam( DWORD& dStyle, CWnd* pParent, BOOL bModalDlg )
{
	BOOL bRe = TRUE;

    //domodal 类型不可以为child
	if ( bModalDlg && (dStyle & WS_CHILD) )
	{
		dStyle &= ~WS_CHILD;
		dStyle |= WS_POPUP;
	}  

	//若为子窗口，则其父窗口不可以为空
	if ( (dStyle & WS_CHILD) && NULL == pParent )
	{  
		PrtError("CTransparentDlg::CheckParam","child类型的dlg的父窗口不可以为空");
		bRe = FALSE;
	}

	return bRe;
	
}


void CTransparentDlg::PrtError( CString strErrFun,CString strErr  )
{
	CString str; 
	str.Format("\n[%s] %s , errorCode=%d\n",strErrFun, strErr ,GetLastError());
	AfxOutputDebugString(str);//如果是release版，可用debugview来查看错误输出
}

BOOL CTransparentDlg::PreTranslateMessage( MSG* pMsg )
{
	if( ( IsInModalLoop()|| GetWindowLong(GetSafeHwnd(),GWL_STYLE)&WS_CHILD )&& pMsg->message == WM_KEYDOWN 
		&& ( pMsg->wParam == VK_ESCAPE ||pMsg->wParam == VK_RETURN ) )
	{  
		return TRUE;
	}
    
	return CDialog::PreTranslateMessage(pMsg);
				 
}
