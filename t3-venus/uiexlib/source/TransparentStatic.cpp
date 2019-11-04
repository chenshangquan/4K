// TransparentStatic.cpp : implementation file
//

#include "stdafx.h"
#include "static.h"
#include "srcManage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentStatic
template<> WNDPROC TransparentAssist<CTransparentStatic>::m_pWndProc = NULL;
CTransparentStatic::CTransparentStatic()
{
	RegsiterWndProc();
	m_pFont = CSrcManage::GetFont( "微软雅黑", 12 );
	m_pImgBk = NULL;
	m_cNormalColor = Color( 146, 157, 183 );	 
	m_cDisableColor = Color( 124,124,124 );
	m_cStringFormat.SetAlignment( StringAlignmentNear );
	m_cStringFormat.SetLineAlignment( StringAlignmentCenter );
	//将文本修整成最接近的字符，并在被修整的行的末尾插入一个省略号
	m_cStringFormat.SetTrimming( StringTrimmingEllipsisCharacter );
	m_MosaicHoriImage = FALSE;
}

CTransparentStatic::~CTransparentStatic()
{	
	if ( m_MosaicHoriImage )
	{
		if ( NULL != m_pImgBk )
		{
			delete m_pImgBk;
			m_pImgBk = NULL;
		}
	}
}


BEGIN_MESSAGE_MAP(CTransparentStatic, CStatic)
	//{{AFX_MSG_MAP(CTransparentStatic)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentStatic message handlers
LRESULT CTransparentStatic::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    Graphics *pGraphics = (Graphics*)wParam;

    HWND hGraphWnd = (HWND )lParam;
    CWnd * pGraphWnd = FromHandle(hGraphWnd);

    if ( pGraphics == NULL || pGraphWnd == NULL )
    {
        return S_FALSE;
    }

    if ( !IsWindowVisible() || GetParent() == NULL )
    {
        return S_FALSE;
    }
	
    CRect cRect;
	Color colorText;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();
	
   // GetParent()->ScreenToClient( &point );
     pGraphWnd->ScreenToClient( &point );
	
    if ( NULL != m_pImgBk && m_pImgBk->GetWidth() != 0 )
    {
        pGraphics->DrawImage( m_pImgBk, point.x, point.y,/* m_pImgBk->GetWidth()*/cRect.Width(),cRect.Height()/*m_pImgBk->GetHeight()*/ );
    }  

    CString strText;
    GetWindowText( strText );
 	
	if ( !strText.IsEmpty() )
	{   
		if ( IsWindowEnabled() )
		{
			colorText = m_cNormalColor;
		}
		else
		{
			colorText = m_cDisableColor; 
		}

		//CheckTextLength( strText, cRect );
        SolidBrush brush( colorText  ); // 创建实心刷（写字符串用）

        //宋体字不做平滑处理、去毛边
        if ( m_strFontName != _T("宋体") )
        {
            pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
        }

		BSTR bstrText = strText.AllocSysString();
		pGraphics->DrawString( bstrText, -1, m_pFont, RectF( (float)point.x, (float)point.y, cRect.Width(), cRect.Height() ), &m_cStringFormat, &brush );
		SysFreeString( bstrText );
	}
	
    return S_OK;    
}

void CTransparentStatic::SetImage( CString strImage, BOOL bInvalidate )
{
	m_pImgBk = CSrcManage::GetImage( strImage );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

void CTransparentStatic::SetImage( UINT nImgID ,const CString& strImgType )
{
	m_pImgBk = CSrcManage::GetImage( nImgID, strImgType );
	NOTIF_PARENT_WND
}

void CTransparentStatic::SetMosaicHoriImage( UINT nImgLeft, UINT nImgMid, UINT nImgRight, const CString& strImgType )
{
	Image   *pImgLeft = NULL;
	Image   *pImgMiddle = NULL;
	Image   *pImgRight = NULL;
	pImgLeft = CSrcManage::GetImage( nImgLeft, "PNG" );
	pImgMiddle = CSrcManage::GetImage( nImgMid, "PNG" );
	pImgRight = CSrcManage::GetImage( nImgRight, "PNG" );
	CRect cRect;
	this->GetWindowRect( &cRect );

	if ( m_pImgBk == NULL )
	{
		m_MosaicHoriImage = TRUE;
		m_pImgBk = CSrcManage::MosaicHoriImage( cRect,pImgLeft, pImgMiddle, pImgRight );
	}
}

CSize CTransparentStatic::GetImageSize()
{
    CSize sz(0);
    if ( m_pImgBk != NULL )
    {
        sz.cx = m_pImgBk->GetWidth();
        sz.cy = m_pImgBk->GetHeight();
    }

    return sz;
}



void CTransparentStatic::SetWindowText( CString strWindowText, BOOL bInvalidate )
{
	CStatic::SetWindowText( strWindowText );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

void CTransparentStatic::SetTextColor( Color colorNormal, BOOL bInvalidate )
{
	m_cNormalColor = colorNormal;

    //如果是宋体，将color的ALPHA值设为254，防止文字透明
    if ( m_strFontName == _T("宋体") )
    {
        ARGB argb = m_cNormalColor.GetValue(); 
        argb = (argb & 0x00FFFFFF) | ( 0xFE << 24 );
        m_cNormalColor.SetValue( argb );
    }

	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

void CTransparentStatic::SetDisableColor( Color coDisable, BOOL bInvalidate )
{
	m_cDisableColor = coDisable;

    if ( m_strFontName == _T("宋体") )
    {
        ARGB argb = m_cDisableColor.GetValue(); 
        argb = (argb & 0x00FFFFFF) | ( 0xFE << 24 );
        m_cDisableColor.SetValue( argb );
    }

	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

void CTransparentStatic::SetTextAlign( StringAlignment emTextAlign, BOOL bInvalidate )
{
	m_cStringFormat.SetAlignment( emTextAlign );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}

void CTransparentStatic::SetFont( unsigned int dwFontSize /* = 18  */, CString strFontFamily /* = */, FontStyle emStyle, BOOL bInvalidate )
{
    m_strFontName = strFontFamily;
	m_pFont = CSrcManage::GetFont( strFontFamily, dwFontSize, emStyle );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

void CTransparentStatic::CheckTextLength( CString& strText, CRect cRect )
{
	Graphics graphics(m_hWnd);
	RectF rectString;

	WCHAR *pwszText = NULL;
	pwszText = new WCHAR[strText.GetLength() + 1];
	int nLen = MultiByteToWideChar( CP_ACP, 0, strText, -1, NULL, NULL ); 
	MultiByteToWideChar( CP_ACP, 0, strText, -1, pwszText, nLen );
	unsigned int dwTextLen = wcslen(pwszText);

	graphics.MeasureString( pwszText, -1, m_pFont, RectF(0,0,0,0), &m_cStringFormat, &rectString );
	//如果只显示一条且长度不够，则把Text最后添加...
	if ( rectString.Width > cRect.Width() && (rectString.Height * 2) > cRect.Height() )
	{
		RectF rectPoint;
		CString strPoint = "...";
        BSTR bstrText = strPoint.AllocSysString();
		graphics.MeasureString( bstrText, -1, m_pFont, RectF(0,0,0,0), &m_cStringFormat, &rectPoint );
        SysFreeString(bstrText);
		for ( int i = 0; i < dwTextLen; i++ )
		{
			graphics.MeasureString( pwszText, dwTextLen - i, m_pFont, RectF(0,0,0,0), &m_cStringFormat, &rectString );

			if ( rectString.Width + rectPoint.Width <= cRect.Width() )
			{
				CString strTemp;

				int len = WideCharToMultiByte( CP_ACP, 0, pwszText, dwTextLen - i, NULL, 0, NULL, NULL);
				char *buffer = new char[len + 1];
				WideCharToMultiByte( CP_ACP, 0, pwszText, dwTextLen - i, buffer, len, NULL, NULL );
				buffer[len] = '\0';	
				
				strTemp.Format( "%s", buffer );				
				strText = strTemp + strPoint;
				if ( NULL != buffer )
				{
					delete []buffer;
					buffer = NULL;
				}					
				break;
			}
		}
	}
	
	if ( NULL != pwszText )
	{
		delete []pwszText;
		pwszText = NULL;
	}
}
