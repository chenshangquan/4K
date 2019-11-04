// TransparentProgress : implementation file
//

#include "stdafx.h"
#include "progress.h"
#include "slider.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const CString CTransparentProgress::strBkgLeft = "BkgLeft.png";
const CString CTransparentProgress::strBkgMid = "BkgMid.png";
const CString CTransparentProgress::strBkgRight = "BkgRight.png";


CTransparentProgress::CTransparentProgress( CString strName, CString strUI,CRect rcWnd, CWnd* pWnd, UINT nID, DWORD dStyle, DWORD dwExStyle ) 
: CTransparentBaseWnd( rcWnd, pWnd, dStyle, strUI,nID )
{
    m_pImgBkgLeft = NULL;
	m_pImgBkgMiddle = NULL;
	m_pImgBkgRight = NULL;
	m_pImgHLLeft = NULL;
	m_pImgHLLeft = NULL;
	m_pImgHLLeft = NULL;

	m_nPos = 0;	
}

CTransparentProgress::~CTransparentProgress()
{
}


BEGIN_MESSAGE_MAP(CTransparentProgress, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CTransparentProgress)
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentProgress message handlers
LRESULT CTransparentProgress::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
	Graphics *pGraphics = (Graphics*)wParam;
	HWND hGraphWnd = (HWND)lParam;
	
    if ( IsWindowVisible() == FALSE || pGraphics == NULL || m_pImgBkgLeft == NULL || hGraphWnd == 0 )
    {
        return S_FALSE;
    }
	
    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();
	
    ::ScreenToClient( hGraphWnd, &point );
    //GetParent()->ScreenToClient( &point );
	

	//底图
	if ( m_pImgBkgLeft != NULL && m_pImgBkgMiddle != NULL && m_pImgBkgRight != NULL && m_pImgBkgMiddle->GetWidth() != 0 )
    {
        unsigned int nPosX = point.x + m_pImgBkgLeft->GetWidth();
		
        unsigned int dwMiddleWidth = 0;
		if ( cRect.Width() > m_pImgBkgLeft->GetWidth() + m_pImgBkgRight->GetWidth() )
		{
			dwMiddleWidth = cRect.Width() - m_pImgBkgLeft->GetWidth() - m_pImgBkgRight->GetWidth();
		}
		
        // 左
        pGraphics->DrawImage( m_pImgBkgLeft, point.x, point.y, m_pImgBkgLeft->GetWidth(), cRect.Height()/*pImgLeft->GetHeight()*/ );
        // 右
		pGraphics->DrawImage( m_pImgBkgRight, point.x + cRect.Width() - m_pImgBkgRight->GetWidth(), point.y,
			m_pImgBkgRight->GetWidth(), cRect.Height()/*pImgRight->GetHeight()*/ );
		
        // 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
        for ( unsigned int nIndex = 0; nIndex < ( dwMiddleWidth / m_pImgBkgMiddle->GetWidth() ); nIndex++ )
        {
            pGraphics->DrawImage( m_pImgBkgMiddle, nPosX, point.y, m_pImgBkgMiddle->GetWidth(), cRect.Height()/*pImgMiddle->GetHeight()*/ );
            nPosX += m_pImgBkgMiddle->GetWidth();
        }
        pGraphics->DrawImage( m_pImgBkgMiddle, nPosX, point.y, dwMiddleWidth % m_pImgBkgMiddle->GetWidth(), cRect.Height()/*pImgMiddle->GetHeight()*/ );
    }

	//进度 0 - 100
	if ( m_nPos > 0 )
	{
		if( m_nPos > 100 )
		{
			m_nPos = 100;
		}
			
		int nLength = cRect.Width() * m_nPos / 100;

		if ( m_pImgHLLeft != NULL && m_pImgHLMiddle != NULL && m_pImgHLRight != NULL && m_pImgHLMiddle->GetWidth() != 0 )
		{
			unsigned int nPosX = point.x + m_pImgHLLeft->GetWidth();
			
			unsigned int dwMiddleWidth = 0;
			if ( nLength > m_pImgHLLeft->GetWidth() + m_pImgHLRight->GetWidth() )
			{
				dwMiddleWidth = nLength - m_pImgHLLeft->GetWidth() - m_pImgHLRight->GetWidth();
			}
			
			// 左
			pGraphics->DrawImage( m_pImgHLLeft, point.x, point.y, m_pImgHLLeft->GetWidth(), cRect.Height() );
		
			if ( dwMiddleWidth > 0 )//防止将m_pImgHLRight绘到m_pImgHLLeft的左边
			{
				// 右
				pGraphics->DrawImage( m_pImgHLRight, point.x + nLength - m_pImgHLRight->GetWidth(), point.y,
					m_pImgHLRight->GetWidth(), cRect.Height() );
			}

			
			// 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
			for ( unsigned int nIndex = 0; nIndex < ( dwMiddleWidth / m_pImgHLMiddle->GetWidth() ); nIndex++ )
			{
				pGraphics->DrawImage( m_pImgHLMiddle, nPosX, point.y, m_pImgHLMiddle->GetWidth(), cRect.Height() );
				nPosX += m_pImgHLMiddle->GetWidth();
			}
			pGraphics->DrawImage( m_pImgHLMiddle, nPosX, point.y, dwMiddleWidth % m_pImgHLMiddle->GetWidth(), cRect.Height() );
		}

	}
	
    return S_OK;  
}

void CTransparentProgress::SetPos( int nPos )
{
	if ( nPos < 0 )
	{
		nPos = 0;
	}
	if ( nPos > 100 )
	{
		nPos = 100;
	}

	m_nPos = nPos;
	NOTIF_PARENT_WND

	return;
}


void CTransparentProgress::SetImage( CString strFolder, BOOL bInvalidate )
{
	String strFile = strFolder + "//" + CTransparentProgress::strBkgLeft;
	m_pImgBkgLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentProgress::strBkgMid;
	m_pImgBkgMiddle = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentProgress::strBkgRight;
	m_pImgBkgRight = CSrcManage::GetImage( strFile.c_str() );
	
	strFile = strFolder + "//" + CTransparentSliderCtrl::strHighLightLeft;
	m_pImgHLLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSliderCtrl::strHighLightMid;
	m_pImgHLMiddle = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSliderCtrl::strHighLightRight;
	m_pImgHLRight = CSrcManage::GetImage( strFile.c_str() );

	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

void CTransparentProgress::SetImage( UINT nImgBkgLeftID, UINT nImgBkgMiddleID, UINT nImgBkgRightID, UINT nImgHLLeftID, UINT nImgHMiddleID, UINT nImgHRightID, BOOL bInvalidate,const CString& strImgType)
{
	m_pImgBkgLeft = CSrcManage::GetImage( nImgBkgLeftID, strImgType );
	m_pImgBkgMiddle = CSrcManage::GetImage( nImgBkgMiddleID, strImgType );
	m_pImgBkgRight = CSrcManage::GetImage( nImgBkgRightID, strImgType );
	
	m_pImgHLLeft = CSrcManage::GetImage( nImgHLLeftID, strImgType );
	m_pImgHLMiddle = CSrcManage::GetImage( nImgHMiddleID, strImgType );
	m_pImgHLRight = CSrcManage::GetImage( nImgHRightID, strImgType );
}