// LetterIndex.cpp : implementation file
//

#include "stdafx.h"
#include "letterindex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LETTER_HEIGHT  21
/////////////////////////////////////////////////////////////////////////////
// CLetterIndex
CTransparentBaseWnd* CLetterIndex::m_pLetterWnd = NULL;
const CString CLetterIndex::strBkg = "IndexBkg.png";
const CString CLetterIndex::strA = "A.png";
const CString CLetterIndex::strB = "B.png";
const CString CLetterIndex::strC = "C.png";
const CString CLetterIndex::strD = "D.png";
const CString CLetterIndex::strE = "E.png";
const CString CLetterIndex::strF = "F.png";
const CString CLetterIndex::strG = "G.png";
const CString CLetterIndex::strH = "H.png";
const CString CLetterIndex::strI = "I.png";
const CString CLetterIndex::strJ = "J.png";
const CString CLetterIndex::strK = "K.png";
const CString CLetterIndex::strL = "L.png";
const CString CLetterIndex::strM = "M.png";
const CString CLetterIndex::strN = "N.png";
const CString CLetterIndex::strO = "O.png";
const CString CLetterIndex::strP = "P.png";
const CString CLetterIndex::strQ = "Q.png";
const CString CLetterIndex::strR = "R.png";
const CString CLetterIndex::strS = "S.png";
const CString CLetterIndex::strT = "T.png";
const CString CLetterIndex::strU = "U.png";
const CString CLetterIndex::strV = "V.png";
const CString CLetterIndex::strW = "W.png";
const CString CLetterIndex::strX = "X.png";
const CString CLetterIndex::strY = "Y.png";
const CString CLetterIndex::strZ = "Z.png";

CLetterIndex::CLetterIndex(CString strName, CString strUI, CRect rcWnd, CWnd* pWnd, UINT nID, DWORD dStyle, DWORD dwExStyle) 
: CTransparentBaseWnd( rcWnd, pWnd, dStyle, strUI,nID )
{
    m_pImgBkg = NULL;
    for ( int i = 0; i < LETTER_NUM; i++ )
	{
		m_pImgLetter[i] = NULL;
	}
	m_pBindList = NULL;
	m_vcBindList.clear();
	m_bLBtnDown = FALSE;
	m_bTouchBtnDown = FALSE;

	m_fLetterHeight = LETTER_HEIGHT;

	m_bStretch = TRUE;
}

CLetterIndex::~CLetterIndex()
{
}


BEGIN_MESSAGE_MAP(CLetterIndex, CTransparentBaseWnd)
    //{{AFX_MSG_MAP(CLetterIndex)
    ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLetterIndex message handlers

LRESULT CLetterIndex::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
	Graphics *pGraphics = (Graphics*)wParam;
	HWND hGraphWnd = (HWND)lParam;

    if ( IsWindowVisible() == FALSE || pGraphics == NULL || m_pImgBkg == NULL || hGraphWnd == 0 )
    {
        return S_FALSE;
    }

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();

    ::ScreenToClient( hGraphWnd, &point );
    
	//2012-6-19 分辨率自适应  by yjj
	if ( !m_bStretch && ( cRect.Width() != m_pImgBkg->GetWidth()
		|| cRect.Height() != m_pImgBkg->GetHeight() ) )
    {
        SetWindowPos( NULL, 0, 0, m_pImgBkg->GetWidth(), m_pImgBkg->GetHeight(), SWP_NOMOVE|SWP_NOACTIVATE );
    }

    if ( NULL != m_pImgBkg )
    {
        pGraphics->DrawImage( m_pImgBkg, point.x, point.y , cRect.Width()/*m_pImgBkg->GetWidth()*/, cRect.Height()/*m_pImgBkg->GetHeight()*/ );
    }

	if ( m_bStretch )
	{
		m_fOffSet = cRect.Height() * 4 / 554.0;

		float fLetterHeight = ( cRect.Height() - m_fOffSet * 2 ) / 26.0;
		if ( fLetterHeight > 0 && fLetterHeight != m_fLetterHeight )
		{
			SetLetterHeight( fLetterHeight );
		}		
	}

    return S_OK;  
}


void CLetterIndex::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ( nFlags == FLAG_TRANSBASEWND )
	{
		return;
	}
	if ( m_bTouchBtnDown )
	{
		return;
	}
	if ( nFlags == MK_LBUTTON )
	{
		KillTimer( 2 );
	}

	m_bLBtnDown = TRUE;
	Image* pImage = NULL;
	int nLetterIndex = 0;
	pImage = GetClickLetter( point, nLetterIndex ); 
    if ( pImage == NULL )
    {
        return ;
    }
   
	CTransparentBaseWnd* pWnd = GetLetterWindow();
	pWnd->SetOwner( this );
	pWnd->SetImage( pImage, TRUE );

	CRect cRect;
    GetWindowRect( &cRect );
	int nleft = cRect.left - 20 - pImage->GetWidth();
	pWnd->SetWindowPos( NULL, nleft, cRect.top - 50, pImage->GetWidth(), pImage->GetHeight(), SWP_NOSIZE|SWP_NOZORDER|SWP_SHOWWINDOW );
	pWnd->SendMessage( WM_REDRAW_UI, 0, TRUE );
	pWnd->SetFocus();

//	NotifyBindList( nLetterIndex );  2012-8-6 由于mouseMove 里面已经通知过，在此不必重复通知 by yjj

	if ( nFlags == FLAG_TOUCHBUTTONDOWN )
	{
		KillTimer( 2 );
		SetTimer( 2, 400, NULL );
	}

	SetCapture();
}


void CLetterIndex::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( !m_bLBtnDown )
	{
		return;
	}

	CTransparentBaseWnd* pWnd = GetLetterWindow();

	Image* pImage = NULL;
	int nLetterIndex = 0;
	pImage = GetClickLetter( point, nLetterIndex );
	if ( pImage == NULL )
	{
		return;
	}

	pWnd->SetImage( pImage, TRUE );

    //通知绑定列表
	NotifyBindList( nLetterIndex );
}

void CLetterIndex::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( !m_bLBtnDown )
	{
		return;
	}
	m_bLBtnDown = FALSE;
	CTransparentBaseWnd* pWnd = GetLetterWindow();
	pWnd->ShowWindow( SW_HIDE );

    //字母隐藏后焦点设在列表上
    if ( m_pBindList != NULL && m_pBindList->IsWindowVisible() )
    {
        if ( m_pBindList->IsWindowEnabled() )
        {
            m_pBindList->SetFocus();
        }
        else
        {
            this->SetFocus();
        }
    }

	ReleaseCapture();
}

Image* CLetterIndex::GetClickLetter( CPoint point, int& nLetterIndex )
{
	float fY = point.y - m_fOffSet;
	if ( fY < 0 )
	{
		nLetterIndex = 0;
		return m_pImgLetter[0];
	}

	if( m_fLetterHeight <=0 )
	{
		return m_pImgLetter[0];
	}

	int nIndex = fY / m_fLetterHeight;
	if ( nIndex >= LETTER_NUM )
	{
		nLetterIndex = LETTER_NUM - 1 ;
		return m_pImgLetter[LETTER_NUM-1];	
	}
	nLetterIndex = nIndex;

	return m_pImgLetter[nIndex];	
}

LRESULT CLetterIndex::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    if ( message == WM_TOUCH_BUTTONDOWN )
    {
        int nX = LOWORD( lParam );
        int nY = HIWORD( lParam );
        if ( !m_bLBtnDown )
        {
			m_bTouchBtnDown = TRUE;
            //OnLButtonDown( 1, CPoint( nX, nY ) );  
			//使用Timer,防止用手点击后鼠标位置没有跟上
			SetTimer( 1, 200, NULL );
        }		
    }
	
    return CTransparentBaseWnd::DefWindowProc(message, wParam, lParam);
}

void CLetterIndex::OnTimer(UINT nIDEvent) 
{	
	if ( nIDEvent == 1 )
	{
		KillTimer( 1 );
		m_bTouchBtnDown = FALSE;
		CPoint point;
		::GetCursorPos(&point); 
		this->ScreenToClient( &point );
		PostMessage( WM_LBUTTONDOWN, FLAG_TOUCHBUTTONDOWN, MAKELPARAM( point.x, point.y ) );		
	}
	else if ( nIDEvent == 2 )
	{
		KillTimer( 2 );
		if ( m_bLBtnDown )
		{
			m_bLBtnDown = FALSE;
			CTransparentBaseWnd* pWnd = GetLetterWindow();
			pWnd->ShowWindow( SW_HIDE );
            
            if ( m_pBindList != NULL && m_pBindList->IsWindowVisible() )
            {
                if ( m_pBindList->IsWindowEnabled() )
                {
                    m_pBindList->SetFocus();
                }
                else
                {
                    this->SetFocus();
                }
            }
			ReleaseCapture();
		}		
	}
	
    CTransparentBaseWnd::OnTimer( nIDEvent );
}

void CLetterIndex::SetBindList( CWnd* pList )
{
	m_pBindList = pList;

	if ( m_pBindList )
	{
		m_pBindList->SendMessage(WM_BIND_LIST, 0, (LPARAM)this);
	}
}


void CLetterIndex::AddBindList( CWnd* pList )
{
	if ( pList != NULL)
	{
		m_vcBindList.push_back(pList);
	}
}

void CLetterIndex::SetLetterHeight( float fHeight )
{
	m_fLetterHeight = fHeight;
}

CTransparentBaseWnd* CLetterIndex::GetLetterWindow()
{
	if (m_pLetterWnd == NULL) 
	{
		m_pLetterWnd = new CTransparentBaseWnd( CRect(0,0,74,82), NULL, WS_CLIPSIBLINGS|WS_POPUP, "", 0, WS_EX_TOPMOST|WS_EX_TOOLWINDOW );
		m_pLetterWnd->SetAutoHideStatus( TRUE );
	}
	return m_pLetterWnd;
}

void CLetterIndex::SetImage( CString strFolder, BOOL bInvalidate /* = FALSE */ )
{
	String strFile = strFolder + "//" + CLetterIndex::strBkg;
	m_pImgBkg = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strA;
	m_pImgLetter[0] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strB;
	m_pImgLetter[1] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strC;
	m_pImgLetter[2] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strD;
	m_pImgLetter[3] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strE;
	m_pImgLetter[4] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strF;
	m_pImgLetter[5] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strG;
	m_pImgLetter[6] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strH;
	m_pImgLetter[7] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strI;
	m_pImgLetter[8] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strJ;
	m_pImgLetter[9] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strK;
	m_pImgLetter[10] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strL;
	m_pImgLetter[11] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strM;
	m_pImgLetter[12] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strN;
	m_pImgLetter[13] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strO;
	m_pImgLetter[14] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strP;
	m_pImgLetter[15] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strQ;
	m_pImgLetter[16] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strR;
	m_pImgLetter[17] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strS;
	m_pImgLetter[18] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strT;
	m_pImgLetter[19] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strU;
	m_pImgLetter[20] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strV;
	m_pImgLetter[21] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strW;
	m_pImgLetter[22] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strX;
	m_pImgLetter[23] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strY;
	m_pImgLetter[24] = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CLetterIndex::strZ;
	m_pImgLetter[25] = CSrcManage::GetImage( strFile.c_str() );
	
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}

void CLetterIndex::SetImage(  int* pPngId, BOOL bInvalidate /* = FALSE */ )
{
	m_pImgBkg = CSrcManage::GetImage( pPngId[0], "PNG" );
	m_pImgLetter[0] = CSrcManage::GetImage(  pPngId[1], "PNG" );
	m_pImgLetter[1] = CSrcManage::GetImage(  pPngId[2], "PNG" );
	m_pImgLetter[2] = CSrcManage::GetImage(  pPngId[3], "PNG" );
	m_pImgLetter[3] = CSrcManage::GetImage(  pPngId[4], "PNG" );
	m_pImgLetter[4] = CSrcManage::GetImage(  pPngId[5], "PNG" );
	m_pImgLetter[5] = CSrcManage::GetImage(  pPngId[6], "PNG" );
	m_pImgLetter[6] = CSrcManage::GetImage(  pPngId[7], "PNG" );
	m_pImgLetter[7] = CSrcManage::GetImage(  pPngId[8], "PNG" );
	m_pImgLetter[8] = CSrcManage::GetImage(  pPngId[9], "PNG" );
	m_pImgLetter[9] = CSrcManage::GetImage(  pPngId[10], "PNG" );
	m_pImgLetter[10] = CSrcManage::GetImage( pPngId[11], "PNG" );
	m_pImgLetter[11] = CSrcManage::GetImage( pPngId[12], "PNG" );
	m_pImgLetter[12] = CSrcManage::GetImage( pPngId[13], "PNG" );
	m_pImgLetter[13] = CSrcManage::GetImage( pPngId[14], "PNG" );
	m_pImgLetter[14] = CSrcManage::GetImage( pPngId[15], "PNG" );
	m_pImgLetter[15] = CSrcManage::GetImage( pPngId[16], "PNG" );
	m_pImgLetter[16] = CSrcManage::GetImage( pPngId[17], "PNG" );
	m_pImgLetter[17] = CSrcManage::GetImage( pPngId[18], "PNG" );
	m_pImgLetter[18] = CSrcManage::GetImage( pPngId[19], "PNG" );
	m_pImgLetter[19] = CSrcManage::GetImage( pPngId[20], "PNG" );
	m_pImgLetter[20] = CSrcManage::GetImage( pPngId[21], "PNG" );
	m_pImgLetter[21] = CSrcManage::GetImage( pPngId[22], "PNG" );
	m_pImgLetter[22] = CSrcManage::GetImage( pPngId[23], "PNG" );
	m_pImgLetter[23] = CSrcManage::GetImage( pPngId[24], "PNG" );
	m_pImgLetter[24] = CSrcManage::GetImage( pPngId[25], "PNG" );
	m_pImgLetter[25] = CSrcManage::GetImage( pPngId[26], "PNG" );
	
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}


void CLetterIndex::NotifyBindList( int nLetterIndex )
{
	if ( m_pBindList != NULL && m_pBindList->IsWindowVisible() )
	{
		m_pBindList->SendMessage( UI_LETTERINDEX_CLICK, nLetterIndex );
	}

	vector<CWnd*>::iterator it = m_vcBindList.begin();
	while ( it != m_vcBindList.end() )
	{   
		CWnd* pWnd = *it;
		if ( pWnd != NULL && pWnd->IsWindowVisible() )
		{
			pWnd->SendMessage( UI_LETTERINDEX_CLICK, nLetterIndex );
		}

		it++;
	}
}

BOOL CLetterIndex::EnableWindow(BOOL bEnable/* = TRUE*/)
{
	if ( m_pBindList )
	{
		BOOL b = m_pBindList->IsWindowEnabled();
		return CTransparentBaseWnd::EnableWindow(b);
	}

	return CTransparentBaseWnd::EnableWindow(bEnable);
}