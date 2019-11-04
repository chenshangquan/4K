#include "StdAfx.h"
#include "previewIF.h"


CPreviewIF::CPreviewIF(void)
{
	 m_hwndPreview = NULL;
	 ZeroMemory( &m_rcPreview, sizeof(m_rcPreview)/sizeof(TCHAR) ) ; 
}


CPreviewIF::~CPreviewIF(void)
{
	m_preAs.Unload();
}



void CPreviewIF::SetWindow( HWND hwndPreview, RECT&Rc )
{
	m_hwndPreview = hwndPreview;
	m_rcPreview = Rc;  
}  

void CPreviewIF::SetRect( RECT &Rc )
{
	m_rcPreview = Rc; 

	//如果当前正在preview则更新当前的预览区域
	
}

LONG CPreviewIF::DoPreview( HWND hWnd, RECT &rectPreview, LPCTSTR szFile )
{
	SetWindow( hWnd, rectPreview );

	return DoPreview( szFile );
}


LONG CPreviewIF::DoPreview( LPCTSTR szFile )
{
	Unload();

	if( NULL == szFile )
	{
		return S_FALSE;
	}

	LONG lRe = S_FALSE;
	//BOOL bImg = CUICommon::IsImgFile( szFile );
	//if( bImg )   
	{  
		//if( NULL == m_pPreImg )
		//{
		//	m_pPreImg = new CPreviewImg( m_hwndPreview );/*CWnd::FromHandle(m_hwndPreview)*///remark 
		//}
		// 
		//lRe = m_pPreImg->DoPreview( m_hwndPreview, m_rcPreview, szFile );
	}
	//else
	{
		lRe = m_preAs.DoPreview( m_hwndPreview, m_rcPreview, szFile );
	}
	
	return lRe;	 
}


 

void CPreviewIF::Unload()
{
	m_preAs.Unload();
}
 