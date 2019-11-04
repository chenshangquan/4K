// SrcManage.cpp: implementation of the CSrcManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "srcManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// 初始化Gdiplus对象
QGdiPlus q;

std::map<CString,Image*> CSrcManage::m_mapImages;
std::map<UINT, Image*> CSrcManage::m_smapImage;
std::map<CFontInfo, Font*> CSrcManage::m_smapFonts;

HBITMAP CSrcManage::CreateImage(UINT nBitmap)
{
    if (nBitmap == 0)
    {
        return NULL;
    }

    HINSTANCE	hInstResource	= NULL;
	
	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmap), RT_BITMAP);
    if (hInstResource == NULL)
    {
        return NULL;
    }
    return (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmap), IMAGE_BITMAP, 0, 0, 0);
}

void CSrcManage::DrawStepBk(CDC *pDC, COLORREF crFrom, COLORREF crTo, CRect rcAll, CRect rcItem, UINT nStyle)
{
    if (rcItem.IsRectEmpty())
    {
        rcItem = rcAll;
    }

    if (crFrom == crTo)
    {
        pDC->FillSolidRect(rcItem, crTo);
        return;
    }
    
    const int nStep = 1;
    int rFrom,gFrom,bFrom;
    int rTo, gTo, bTo;
    
    rFrom = (crFrom & 0x000000ff) << 8;
    gFrom = crFrom & 0x0000ff00;
    bFrom = crFrom & 0x00ff0000;

    rTo = (crTo & 0x000000ff) << 8;
    gTo = crTo & 0x0000ff00;
    bTo = crTo & 0x00ff0000;
    

    int nLength;

    if (nStyle == STEPBK_VERT)
    {
        nLength = rcAll.Height()/nStep;
    }
    else
    {
        nLength = rcAll.Width()/nStep;
    }
    
    int dbMarginr = (rTo-rFrom)/nLength;
    int dbMarging = (gTo-gFrom)/nLength;
    int dbMarginb = (bTo-bFrom)/nLength;

    COLORREF cr;
    if (nStyle == STEPBK_VERT)
    {
        rFrom += (rcItem.top-rcAll.top)*dbMarginr;
        gFrom += (rcItem.top-rcAll.top)*dbMarging;
        bFrom += (rcItem.top-rcAll.top)*dbMarginb;
        for (int y=rcItem.top; y < rcItem.bottom; y+=nStep)
        {
           cr = (bFrom & 0x00ff0000) | (gFrom & 0x0000ff00) | (rFrom >> 8);
           pDC->FillSolidRect(rcItem.left, y, rcItem.right-rcItem.left, nStep, cr);
           rFrom += dbMarginr;
           gFrom += dbMarging;
           bFrom += dbMarginb;
          
        }
    }
    else
    {
        rFrom += (rcItem.left-rcAll.left)*dbMarginr;
        gFrom += (rcItem.left-rcAll.left)*dbMarging;
        bFrom += (rcItem.left-rcAll.left)*dbMarginb;
        for (int x=rcItem.left; x < rcItem.right; x+=nStep)
        {
           cr = (bFrom & 0x00ff0000) | (gFrom & 0x0000ff00) | (rFrom >> 8);
           pDC->FillSolidRect(x, rcItem.top, nStep, rcItem.bottom-rcItem.top, cr);
           rFrom += dbMarginr;
           gFrom += dbMarging;
           bFrom += dbMarginb;
        }
    }
}
HRGN CSrcManage::GenerateRegion(HBITMAP hBitmap, BYTE red, BYTE green, BYTE blue)
{
	WORD wBmpWidth,wBmpHeight;
	HRGN hRgn, hTmpRgn;
	
	// 24bit pixels from the bitmap
	BYTE *pPixels = Get24BitPixels(hBitmap, &wBmpWidth, &wBmpHeight);
	if (!pPixels) return NULL;
	
	// create our working region
	hRgn = CreateRectRgn(0,0,wBmpWidth,wBmpHeight);
	if (!hRgn) { delete pPixels; return NULL; }
	
	DWORD p=0;
	for (WORD y=0; y<wBmpHeight; y++)
	{
		for (WORD x=0; x<wBmpWidth; x++)
		{
			BYTE jRed   = pPixels[p+2];
			BYTE jGreen = pPixels[p+1];
			BYTE jBlue  = pPixels[p+0];
			
			if (jRed==red && jGreen==green && jBlue==blue)
			{
				// remove transparent color from region
				hTmpRgn = CreateRectRgn(x,y,x+1,y+1);
				CombineRgn(hRgn, hRgn, hTmpRgn, RGN_XOR);
				DeleteObject(hTmpRgn);
			}
			
			// next pixel
			p+=3;
		}
	}
	
	// release pixels
	delete pPixels;
	
	// return the region
	return hRgn;
}

BYTE* CSrcManage::Get24BitPixels(HBITMAP pBitmap, WORD *pwWidth, WORD *pwHeight)
{
	BITMAP bmpBmp;
	LPBITMAPINFO pbmiInfo;
	BITMAPINFO bmiInfo;
	WORD wBmpWidth, wBmpHeight;
	
	GetObject(pBitmap, sizeof(bmpBmp),&bmpBmp);
	pbmiInfo   = (LPBITMAPINFO)&bmpBmp;
	
	wBmpWidth  = (WORD)pbmiInfo->bmiHeader.biWidth;
	wBmpWidth -= (wBmpWidth%4);
	wBmpHeight = (WORD)pbmiInfo->bmiHeader.biHeight;
	
	*pwWidth  = wBmpWidth;
	*pwHeight = wBmpHeight;
	
	BYTE *pPixels = new BYTE[wBmpWidth*wBmpHeight*3];
	if (!pPixels) return NULL;
	
	HDC hDC =::GetWindowDC(NULL);
	
	bmiInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiInfo.bmiHeader.biWidth = wBmpWidth;
	bmiInfo.bmiHeader.biHeight = -wBmpHeight;
	bmiInfo.bmiHeader.biPlanes = 1;
	bmiInfo.bmiHeader.biBitCount = 24;
	bmiInfo.bmiHeader.biCompression = BI_RGB;
	bmiInfo.bmiHeader.biSizeImage = wBmpWidth*wBmpHeight*3;
	bmiInfo.bmiHeader.biXPelsPerMeter = 0;
	bmiInfo.bmiHeader.biYPelsPerMeter = 0;
	bmiInfo.bmiHeader.biClrUsed = 0;
	bmiInfo.bmiHeader.biClrImportant = 0;
	
	// get pixels from the original bitmap converted to 24bits
	int iRes = GetDIBits(hDC,pBitmap,0,wBmpHeight,(LPVOID)pPixels,&bmiInfo,DIB_RGB_COLORS);
	
	// release the device context
	::ReleaseDC(NULL,hDC);
	
	// if failed, cancel the operation.
	if (!iRes)
	{
		delete pPixels;
		return NULL;
	};
	
	// return the pixel array
	return pPixels;
}

Image* CSrcManage::GetImage( CString strPath, BOOL bNewCreate /* = FALSE */ )
{
	if( !::PathFileExists( strPath ) )
	{
		return NULL;
	}

	Image* pImage = 0;	
	if ( bNewCreate == TRUE )
	{	
		BSTR bstr = strPath.AllocSysString();
		pImage = new Image( bstr );
		SysFreeString( bstr );
		return pImage;
	}
	ImageMap::iterator itr = m_mapImages.find( strPath );

	if ( itr != m_mapImages.end() )
	{
		pImage = itr->second;
		return pImage;
	}

	BSTR bstr = strPath.AllocSysString();
	pImage = new Image( bstr );
	SysFreeString( bstr );
	if ( pImage != NULL )
	{
		m_mapImages.insert( ImageMap::value_type( strPath, pImage) );
		return pImage;
	}

	return pImage;
}

Image*  CSrcManage::GetImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance /*=NULL*/)
{
	if ( nID == 0 )
	{
		return NULL;
	}
	
	CImageMap::iterator itr = m_smapImage.find( nID );
	
	Image* pImage = NULL;

    if ( m_smapImage.end() == itr )
    {
		pImage = LoadImage( nID, lpszType, hInstance );
		if ( NULL != pImage )
		{
			m_smapImage.insert( CImageMap::value_type( nID, pImage ) );
		}
    }
	else
	{
		pImage = itr->second;
	}
	return pImage;
}

Image* CSrcManage::LoadImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance /*=NULL*/)
{
	Image * pImage = NULL;
	
	if( lpszType == RT_BITMAP )
	{
		HBITMAP hBitmap = ::LoadBitmap( hInstance, MAKEINTRESOURCE(nID) );
		pImage = (Image*)Bitmap::FromHBITMAP(hBitmap, 0);
		::DeleteObject(hBitmap);
		return pImage;
	}		
	
	hInstance = (hInstance == NULL) ? ::AfxGetResourceHandle() : hInstance;
	HRSRC hRsrc = ::FindResource ( hInstance, MAKEINTRESOURCE(nID), lpszType); 
	ASSERT(hRsrc != NULL);
	
	DWORD dwSize = ::SizeofResource( hInstance, hRsrc);
	LPBYTE lpRsrc = (LPBYTE)::LoadResource( hInstance, hRsrc);
	ASSERT(lpRsrc != NULL);
	
	HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, dwSize);
	LPBYTE pMem = (LPBYTE)::GlobalLock(hMem);
	memcpy( pMem, lpRsrc, dwSize);
	IStream * pStream = NULL;
	::CreateStreamOnHGlobal( hMem, FALSE, &pStream);
	
	pImage = Image::FromStream(pStream);
	
	::GlobalUnlock(hMem);
	::GlobalFree(hMem);

	pStream->Release();
	::FreeResource(lpRsrc);
	
	return pImage;
}

Font* CSrcManage::GetFont( CString strFontFamily, unsigned int wSize, FontStyle emFontStyle, BOOL bNewCreate /* = FALSE */ )
{
	Font* pFont = 0;	
	if ( bNewCreate == TRUE )
	{
		BSTR bstrFont = strFontFamily.AllocSysString();
		pFont = new Font( bstrFont, wSize, emFontStyle );
		SysFreeString( bstrFont );
		return pFont;
	}

	FontKey cFontInfo( strFontFamily, wSize, emFontStyle );
	FontMap::iterator itr = m_smapFonts.find( cFontInfo );	
	if ( itr != m_smapFonts.end() )
	{
		pFont = itr->second;
		return pFont;
	}
	
	BSTR bstrFont = strFontFamily.AllocSysString();
    pFont = new Font( bstrFont, wSize, emFontStyle );
	SysFreeString( bstrFont );
	if ( pFont != NULL )
	{
		m_smapFonts.insert( FontMap::value_type( cFontInfo, pFont) );
		return pFont;
	}
	
	return pFont;
}

void CSrcManage::GetChsAndEngCnt( CString cstrText, unsigned short& wChsCnt, unsigned short& wEngCnt)
{ 
	wChsCnt = 0;
	wEngCnt = 0;
	
	for ( unsigned short wIndex = 0; wIndex < cstrText.GetLength(); wIndex++ ) 
	{ 
		if ( ((BYTE)cstrText.GetAt(wIndex)) < 0x80 )		
		{ 		
			wEngCnt++; 	
		}
		else 	
		{
			wChsCnt++;
			wIndex++; 			
		} 		
	} 
	
}




Image* CSrcManage::MosaicHoriImage( CRect& cRect, Image* pImgLeft, Image* pImgRight, Image* pImgMiddle )
{ 
    
    if (  pImgLeft == NULL || pImgRight == NULL || pImgMiddle == NULL )
    {
        return NULL;
    }

    Image* pImgMosaic = NULL; 
    pImgMosaic = new Bitmap( cRect.Width(), cRect.Height() ); 
     
    Graphics* pGraphics = Graphics::FromImage(  pImgMosaic );
    
    if ( pImgLeft != NULL && pImgMiddle != NULL && pImgRight != NULL && pImgMiddle->GetWidth() != 0 )
    {
        unsigned int nPosX = pImgLeft->GetWidth();
        
        unsigned int dwMiddleWidth = 0;
        if ( cRect.Width() > pImgLeft->GetWidth() + pImgRight->GetWidth() )
        {
            dwMiddleWidth = cRect.Width() -  pImgLeft->GetWidth() -  pImgRight->GetWidth();
        }
        
        // 左
        pGraphics->DrawImage( pImgLeft, 0, 0, pImgLeft->GetWidth(), /*pImgLeft->GetHeight()*/cRect.Height() );
        // 右
        pGraphics->DrawImage( pImgRight, cRect.Width() - pImgRight->GetWidth(), 0, pImgRight->GetWidth(), /*pImgRight->GetHeight()*/ cRect.Height());		
        // 中
        for ( unsigned int nIndex = 0; nIndex < ( dwMiddleWidth /  pImgMiddle->GetWidth() ); nIndex++ )
        {
            pGraphics->DrawImage( pImgMiddle, nPosX, 0, pImgMiddle->GetWidth(), /*pImgMiddle->GetHeight()*/ cRect.Height());
            nPosX += pImgMiddle->GetWidth();
        }
        pGraphics->DrawImage( pImgMiddle, nPosX, 0, dwMiddleWidth % pImgMiddle->GetWidth(), /*pImgMiddle->GetHeight()*/cRect.Height() );
    }

    if ( pGraphics )
    {
        delete pGraphics;
        pGraphics = 0; 
    }  

    return pImgMosaic;
}


Image* CSrcManage::MosaicVertImage( CRect& cRect,  Image* pImgTop, Image* pImgBottom, Image* pImgMiddle )
{
    if (  pImgTop == NULL ||  pImgBottom == NULL ||  pImgMiddle == NULL )
    {
         return NULL;
    }

    Image* pImgMosaic = NULL ;
    pImgMosaic = new Bitmap( cRect.Width(), cRect.Height() ); 
        
    
    Graphics* pGraphics = Graphics::FromImage( pImgMosaic );
    
    if (  pImgTop != NULL &&  pImgBottom != NULL &&  pImgMiddle != NULL && pImgMiddle->GetWidth() != 0 )
    {
        unsigned int nPosY = pImgTop->GetHeight();
        
        unsigned int dwMidHeight = 0;
        if ( cRect.Height() > pImgTop->GetHeight() + pImgBottom->GetHeight() )
        {
            dwMidHeight = cRect.Height() - pImgTop->GetHeight() - pImgBottom->GetHeight();
        }
        
        // 上
        pGraphics->DrawImage( pImgTop, 0, 0, /*pImgTop->GetWidth()*/cRect.Width(), pImgTop->GetHeight() );
        // 下
        pGraphics->DrawImage( pImgBottom, 0, cRect.Height() - pImgBottom->GetHeight(), /*pImgBottom->GetWidth()*/cRect.Width(), pImgBottom->GetHeight() );		
        // 中
        for ( unsigned int nIndex = 0; nIndex < ( dwMidHeight /  pImgMiddle->GetHeight() ); nIndex++ )
        {
            pGraphics->DrawImage( pImgMiddle, 0, nPosY, /*pImgMiddle->GetWidth()*/cRect.Width(), pImgMiddle->GetHeight() );
            nPosY += pImgMiddle->GetHeight();
        }
        pGraphics->DrawImage( pImgMiddle, 0, nPosY, /*pImgMiddle->GetWidth()*/cRect.Width(), dwMidHeight % pImgMiddle->GetHeight() );
    }

    if ( pGraphics )
    {
        delete pGraphics;
        pGraphics = 0; 
    }
    return pImgMosaic;
}

CSize CSrcManage::GetImageSize(CString strImgFullPath)
{
	CSize szImgSize(0,0);
	Image* m_pImg = CSrcManage::GetImage( strImgFullPath );
	if ( NULL != m_pImg )
	{
		szImgSize = CSize(m_pImg->GetWidth(),m_pImg->GetHeight());
	}

	return szImgSize;
}

void CSrcManage::ReleaseImage()
{
	CImageMap::iterator itr = m_smapImage.begin();
	for ( ; itr != m_smapImage.end(); itr++ )
	{
		delete itr->second;
	}
	m_smapImage.clear();
}

void CSrcManage::ReleaseFont()
{
	FontMap::iterator itr = m_smapFonts.begin();
	for ( ; itr != m_smapFonts.end(); itr++ )
	{
		delete itr->second;
	}
	m_smapFonts.clear();

}

void CSrcManage::ReleaseSingleImage( CString strPath )
{
	ImageMap::iterator itr = m_mapImages.find( strPath );
	
	if ( itr != m_mapImages.end() )
	{
		delete itr->second;
		m_mapImages.erase(itr);
	}
}