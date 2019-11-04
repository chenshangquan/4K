// BaseWnd.cpp : implementation file
//

#include "stdafx.h"
#include "baseWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseWnd
CBaseWnd::CBaseWnd( CString strName, CRect rcWnd, CWnd* pWnd, DWORD dStyle, DWORD dwExStyle, UINT nID, CCreateContext* pContext)
{
	Create( dwExStyle, strName, rcWnd, pWnd, dStyle, nID, pContext );
}

CBaseWnd::~CBaseWnd()
{

}


BEGIN_MESSAGE_MAP(CBaseWnd, CWnd)
	//{{AFX_MSG_MAP(CBaseWnd)
	ON_WM_ERASEBKGND()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBaseWnd message handlers

BOOL CBaseWnd::Create( DWORD dwExStyle, CString strName, CRect rcWnd, CWnd* pWnd,DWORD dStyle,UINT nID, CCreateContext* pContext )
{
    CString szClassName = AfxRegisterWndClass( CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW, 0, (HBRUSH)::GetStockObject(BLACK_BRUSH) );
 	
	CheckParam( dwExStyle, &pWnd, dStyle, nID );
 	BOOL bRet = CWnd::CreateEx(dwExStyle, szClassName, strName,
 		dStyle, rcWnd, pWnd, nID, pContext);
	 
	if (!bRet)
		AfxOutputDebugString("CBaseWnd::Create failed!");
		return FALSE;
	return bRet;

}

void CBaseWnd::CheckParam( DWORD& dwExStyle, CWnd** pWnd,DWORD& dStyle,UINT& nID )
{
	// 如果是想做为一个非子窗口的窗口，ID不能有值，因为在CreateEx里面的参数是作为child的ID
	if ( pWnd == NULL )
	{
		nID = 0;
		if ( dStyle & WS_CHILD )
		{
			dStyle &= ~WS_CHILD;
		}		
	}

	if ( !(dStyle & WS_CHILD) )
	{
		nID = 0;
	}
	if ( dStyle & WS_POPUP )
	{
		*pWnd = NULL;
	}
	
}