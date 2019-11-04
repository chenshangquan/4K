#include "StdAfx.h"
#include "previewImg.h"

static Image*    g_staPImg ;
CPreviewImg::CPreviewImg()
{
}
CPreviewImg::CPreviewImg( HWND pParent)
{
	m_Token = 0;
	g_staPImg = NULL;
	Gdiplus::GdiplusStartupInput input; 
	Gdiplus::GdiplusStartup(& m_Token, & input, NULL); 
 
	RECT rc;	
	ZeroMemory(&rc,sizeof(RECT));  
	
    int nLen = sizeof(DLGTEMPLATE) + sizeof(DWORD)  + sizeof(DWORD) + sizeof(DWORD) + sizeof(DWORD);   //menu + class + title + font 均为0 ,有需要单独设置
    HANDLE h = GlobalAlloc(GHND, nLen); 
    DLGTEMPLATE *pDlgTemp = NULL;
  	pDlgTemp = (DLGTEMPLATE*) GlobalLock(h);  
  
	pDlgTemp-> style =  WS_CHILD/* | WS_VISIBLE*/; 
	pDlgTemp-> dwExtendedStyle = 0;  
	pDlgTemp-> cdit = 0;  
	pDlgTemp-> x = 0; 
	pDlgTemp-> y = 0; 
	pDlgTemp-> cx = 0; 
	pDlgTemp-> cy = 0;   
	//remark CreateIndirect(pDlgTemp, pParent);  
	GlobalUnlock( h ); 
	GlobalFree( h );	
	pDlgTemp = NULL; 

	if ( NULL != m_pManager )
	{
		if ( !m_pManager->SetTimer( this, TIMER_ID_REDRAWPREVIEW, 1000U ) )
		{
			OutputDebugString( L"\n TIMER_ID_REDRAWPREVIEW Set Fails" );
		}
	}
}


CPreviewImg::~CPreviewImg(void)
{   
	Unload();
	Gdiplus::GdiplusShutdown(m_Token);
 
}

LPCTSTR CPreviewImg::GetClass() const
{
	return _T("CPreviewImg");
}

LPVOID CPreviewImg::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, _T("CPreviewImg")) == 0 ) return static_cast<CPreviewImg*>(this);
	return CControlUI::GetInterface(pstrName);
}

void CPreviewImg::Draw()
{
	HDC hDC = NULL;
	hDC = GetDC(m_hWndThis);
	DrawImage( hDC, m_rcDraw ); //ldy    绘制图片
} 

void CPreviewImg::DrawImage(HDC hDC, const RECT& rc)
{
	// draw the image
	if( NULL == g_staPImg )
		return;

	Graphics gc( hDC );
	//gc.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	gc.DrawImage( g_staPImg, m_rcDraw.left, m_rcDraw.top, m_rcDraw.GetWidth(), m_rcDraw.GetHeight() );	
	//ReleaseDC( m_hWndThis,hDC );
	return;
}

void CPreviewImg::SetPrevRect( RECT &Rc )
{ 
	SetWindowPos( NULL, NULL,0, 0, Rc.right-Rc.left,Rc.bottom-Rc.top,SWP_NOZORDER ); 
}

void CPreviewImg::SetPrevWindow( HWND hwndPreview, RECT&Rc )
{
	m_hWndThis = hwndPreview;  
	m_rcDraw = Rc;   

	::SetParent( NULL,hwndPreview );  
	SetPrevRect( Rc );
}

LONG CPreviewImg::DoPreview( LPCTSTR  szFile )
{
	if( NULL == szFile || !::IsWindow( m_hWndThis ) )
	{
		return S_FALSE;
	}
	
	AdaptImg( szFile ); 

	Draw();

	ShowWindow( m_hWndThis, SW_SHOW );  

	return S_OK;
}

LONG CPreviewImg::DoPreview( HWND hWnd, RECT &rectPreview, LPCTSTR szFile )
{
	SetPrevWindow( hWnd,rectPreview );

	return DoPreview( szFile );
}

LONG CPreviewImg::DoPreview( RECT &rectPreview, LPCTSTR szFile )
{
	SetPrevRect( rectPreview );
	return DoPreview( szFile );
}

void CPreviewImg::Unload()
{  
	 if( ::IsWindow(m_hWndThis ) ) 
	 {    
		 ShowWindow( NULL, SW_HIDE ); 
	 }
	
	if( NULL != g_staPImg )
	{
		delete g_staPImg;
		g_staPImg = NULL;
	} 
	 
} 

void CPreviewImg::AdaptImg ( LPCTSTR szFile )
{  
	if( NULL != g_staPImg )
	{
		Unload();
	}

	USES_CONVERSION;
	g_staPImg = new Image(szFile);
	//USES_CONVERSION; 
	//m_pImg->FromFile( A2W((LPSTR)strPath) );

	CRect rc;
	//remark GetClientRect(&rc);
  
	int nImgWidth = g_staPImg->GetWidth();
	int nImgHeight = g_staPImg->GetHeight();

	float fRadioWid = 1;
	if( nImgWidth > rc.GetWidth() )
	{
		fRadioWid = (float)rc.GetWidth()/nImgWidth;
	}

	float fRadioHei = 1;
	if( nImgHeight > rc.GetHeight() )
	{
		fRadioHei = (float)rc.GetHeight()/nImgHeight;
	}

	//按照比例小的进行缩小
	if( fRadioWid > fRadioHei )
	{
		fRadioWid = fRadioHei;
	} 

	if( fRadioWid < 1 )
	{  
		nImgWidth = (int)(nImgWidth * fRadioWid);
		nImgHeight = (int)(nImgHeight *fRadioWid);
	}
		 

	//矫正位置，使图片居中显示
	m_rcImg.left  = rc.left +  (rc.GetWidth() - nImgWidth )/2;
	m_rcImg.top  = rc.top + (rc.GetHeight() - nImgHeight)/2; 
	m_rcImg.right = m_rcImg.left + nImgWidth;
	m_rcImg.bottom = m_rcImg.top + nImgHeight;
}

 HGLOBAL m_hGlobal;
LONG CPreviewImg::GetThumb( LPCTSTR szFile /*= NULL */,OUT HBITMAP &hbt,OUT WTS_ALPHATYPE &alpha  )
{//IThumbnailProvider
	 
	LONG hRe = S_OK;
	CLSID rclsid = GUID_NULL; 
	IThumbnailProvider * m_pIThumbnail;
	CLSIDFromString( _T("{C7657C4A-9F68-40fa-A4DF-96BC08EB3551}"), &rclsid); 

	CoInitialize( NULL );
	hRe = CoCreateInstance(  rclsid , NULL,  CLSCTX_INPROC_SERVER| CLSCTX_LOCAL_SERVER ,
		IID_IThumbnailProvider ,(LPVOID*) &m_pIThumbnail  ); 

	if( FAILED(hRe) )
	{
		TRACE(L"\n[CPreviewAsisst::InitEnv] 获取注册类失败 \n"); 
		//return 0;
	}

	IInitializeWithStream *m_pIStream = NULL;
	hRe = m_pIThumbnail->QueryInterface( IID_IInitializeWithStream, (LPVOID*)&m_pIStream );
	if ( S_OK == hRe  )
	{   IStream *m_pStream = NULL;
		HANDLE hFile = CreateFile(szFile,FILE_READ_DATA,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL );
		if( INVALID_HANDLE_VALUE != hFile )
		{
		DWORD dwSize = GetFileSize( hFile,NULL );
		m_hGlobal= GlobalAlloc(GPTR, dwSize );
		BYTE * pByte = (BYTE *)GlobalLock(m_hGlobal);

		if( pByte )
		{
			ReadFile(hFile,pByte,dwSize,&dwSize,NULL);	
			GlobalUnlock(m_hGlobal);

			CreateStreamOnHGlobal(m_hGlobal, TRUE, &m_pStream);	
			hRe = m_pIStream->Initialize( m_pStream,STGM_READ);
		}

		CloseHandle( hFile );
		}
	} 
	 
	Rect		DesRect;
	RECT		clRect; 
    //remark GetClientRect(&clRect);
	DesRect.X = clRect.left;
	DesRect.Y = clRect.top;
	DesRect.Width = clRect.right - clRect.left;
	DesRect.Height = clRect.bottom - clRect.top;
	m_pIThumbnail->GetThumbnail( DesRect.Width,&hbt,&alpha);
	CoUninitialize(); 
	return 	   S_OK;
 
} 
 
void CPreviewImg::DoPaint(HDC hDC, const RECT& rcPaint)
{
}

void CPreviewImg::PaintBkImage(HDC hDC)
{
}

void CPreviewImg::PaintText(HDC hDC)
{
}
 
void CPreviewImg::DoEvent(TEventUI& event) 
{
}
