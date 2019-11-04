#include "StdAfx.h"
#include "UICommon.h"

namespace DuiLib {
//////////////////////////////////////////////////////////////////////////
ImageMap CUICommon::m_mapImages;

CUICommon::CUICommon()
{
}

CUICommon::~CUICommon()
{
}

BOOL CUICommon::IsImgFile( LPCTSTR szFile )
{
	TCHAR*pExtern = StrRChr( szFile, NULL, _T('.') ); 

	if(  NULL != pExtern  && StrStr( (LPCTSTR)IMAGE_FILE_EXT,pExtern) != NULL  )
	{
		return TRUE;
	}

	return FALSE; 
}

TImageInfo* CUICommon::GetImgInfo( LPCTSTR szImgFile )
{
	TImageInfo* pImgInfo = NULL;
	pImgInfo = CRenderEngine::LoadImage(szImgFile);

	return pImgInfo; 
}

Image* CUICommon::GetImage( tString strPath, BOOL bNewCreate /* = FALSE */ )
{
	bool bRelativePath = true;
	TCHAR chFile[MAX_PATH] = {0};  
	tString strTmpFile = strPath;
	if ( std::string::npos != strTmpFile.find(L":") )
	{
		bRelativePath = false;
	}

	if( bRelativePath )  
	{
		wcscat( chFile, CPaintManagerUI::GetResourcePath() );
	}

	tString strFileFullPath;
	strFileFullPath += chFile;
	strFileFullPath += strTmpFile;

	if( !::PathFileExists( strFileFullPath.c_str() ) )
	{
		return NULL;
	}

	Image* pImage = 0;	
	if ( bNewCreate == TRUE )
	{	
		pImage = new Image( strFileFullPath.c_str() );
		return pImage;
	}
	ImageMap::iterator itr = m_mapImages.find( strFileFullPath );

	if ( itr != m_mapImages.end() )
	{
		pImage = itr->second;
		return pImage;
	}

	pImage = new Image( strFileFullPath.c_str() );
	if ( pImage != NULL )
	{
		m_mapImages.insert( ImageMap::value_type( strFileFullPath, pImage) );
		return pImage;
	}

	return pImage;
}

};