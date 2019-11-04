#include "StdAfx.h"
#include "dlgManager.h" 
#include <sstream> 
 

namespace DuiLib {

CDlgManager::CDlgManager()
{ 
	 //注册窗口类型
	REG_WINDOW_STYLE( WS_OVERLAPPED );
	REG_WINDOW_STYLE( WS_POPUP );
	REG_WINDOW_STYLE( WS_CHILD );
	REG_WINDOW_STYLE( WS_MINIMIZE );;
	REG_WINDOW_STYLE( WS_CLIPSIBLINGS );
	REG_WINDOW_STYLE( WS_CLIPCHILDREN );
	REG_WINDOW_STYLE( WS_MAXIMIZE );
	REG_WINDOW_STYLE( WS_CAPTION );     /* WS_BORDER | WS_DLGFRAME  */ 
	REG_WINDOW_STYLE( WS_DLGFRAME );  
	REG_WINDOW_STYLE( WS_THICKFRAME );  
	
	REG_WINDOW_STYLE( WS_MINIMIZEBOX );
	REG_WINDOW_STYLE( WS_MAXIMIZEBOX );
	
	 
	REG_WINDOW_STYLE( DS_CENTER ); 
	REG_WINDOW_STYLE( WS_SIZEBOX );
	REG_WINDOW_STYLE( WS_TILEDWINDOW );
	
	/*
	* Common Window Styles
	*/
	REG_WINDOW_STYLE( WS_OVERLAPPEDWINDOW );
	REG_WINDOW_STYLE( WS_POPUPWINDOW );
	REG_WINDOW_STYLE( WS_CHILDWINDOW );
	
	/*
	* Extended Window Styles
	*/
	REG_WINDOW_STYLE( WS_EX_DLGMODALFRAME ); 
	REG_WINDOW_STYLE( WS_EX_TOPMOST ); 
  ;
	REG_WINDOW_STYLE( WS_EX_TOOLWINDOW );
 
	REG_WINDOW_STYLE( WS_EX_APPWINDOW ); 
	REG_WINDOW_STYLE( WS_EX_OVERLAPPEDWINDOW );
	REG_WINDOW_STYLE( WS_EX_PALETTEWINDOW );
 
}


CDlgManager::~CDlgManager(void)
{
	LIVEDLGMAP::iterator it =  m_liveDlgMap.begin();
	while( it != m_liveDlgMap.end() )
	{ 
		m_liveDlgMap.begin()->second->Close();
		delete  m_liveDlgMap.begin()->second;
		m_liveDlgMap.erase(  m_liveDlgMap.begin() );
		
		it =  m_liveDlgMap.begin();
	}
}

CDUIDialog* CDlgManager::FindDlgByName( const LPCTSTR szDlgName )
{
	if( NULL == szDlgName )
	{
		return NULL;
	}

	//若已经创建过了，则直接返回对应的指针
	LIVEDLGMAP::iterator it = m_liveDlgMap.find( szDlgName ) ;
	if( it != m_liveDlgMap.end() )
		return it->second;

	
	//需要创建
	CDUIDialog *pDlg =  CreateDlgByName( szDlgName );
	
	if( NULL != pDlg )
	{
		m_liveDlgMap.insert( LIVEDLGMAP::value_type(szDlgName,pDlg ) );
	}
	return pDlg;
}



BOOL CDlgManager::CloseDlg( const LPCTSTR szDlgName )
{
	CDUIDialog *pDlg = FindDlgByName( szDlgName );
	if( NULL != pDlg )
	{
		pDlg->Close();
		delete pDlg;
	    m_liveDlgMap.erase( szDlgName );
		return TRUE;
	}

	return FALSE;
}


CDUIDialog* CDlgManager::CreateDlgByName( const LPCTSTR szDlgName )
{
	DLGMAP::iterator it = m_dlgMap.find( szDlgName );
	if( it == m_dlgMap.end() )	
	{
		return NULL;
	}

	HWND hParentWnd = NULL;
	CDUIDialog* pParent = FindDlgByName(it->second.tcParent);
	if ( NULL != pParent )
	{
		hParentWnd = pParent->GetHWND();
	}


	CStdString strLayout =  it->second.tcLayoutFile ;
	CDUIDialog* pDlg =  new CDUIDialog( (LPCTSTR)strLayout  );
	pDlg->Create( hParentWnd/*NULL*/,szDlgName,it->second.dwStyle,it->second.dwExStyle );      //2014.03.25  ldy   加入设置父窗口功能
	return pDlg;

}

BOOL CDlgManager::InitDlgMap( const LPCTSTR szDlgMapXml )
{
	if( NULL == szDlgMapXml )
	{
		return FALSE;
	}

	CMarkup  xmlMarkup;
	if( !xmlMarkup.LoadFromFile( szDlgMapXml ))
		return FALSE;

	CMarkupNode root = xmlMarkup.GetRoot();
	 
	while( root.IsValid() )
	{   
		LPCTSTR pstrClass = root.GetName();
		if( _tcscmp(pstrClass, _T("Dialog")) != 0 ) 
		{  
			 root = root.GetSibling();
			continue;
		}

		int nAttributes = root.GetAttributeCount();
	 
		LPCTSTR pstrDlgName = NULL;
		TDlgAttrib attri;
		for( int i = 0; i < nAttributes; i++ )
		{    
			LPCTSTR pstrName = root.GetAttributeName(i);
			LPCTSTR pstrValue = root.GetAttributeValue(i);
			

			if ( _tcscmp(pstrName, _T("Name")) == 0 ) 
			{
				pstrDlgName = pstrValue; 
			}
			else if( _tcscmp(pstrName, _T("Style")) == 0 )
			{   
				 
				attri.dwStyle = CWindowStyleMap::StringToStyle( pstrValue ) ;
			}
			else if( _tcscmp(pstrName, _T("ExStyle")) == 0 )
			{
				attri.dwExStyle = CWindowStyleMap::StringToStyle( pstrValue ) ;
			}
			else if( _tcscmp(pstrName, _T("Parent")) == 0 )
			{
				_sntprintf_s(attri.tcParent,sizeof(attri.tcParent),pstrValue);
			} 
			else if( _tcscmp(pstrName, _T("AutoHide")) == 0 )
			{
				attri.bAuotHide = (_tcscmp(pstrValue, _T("true")) == 0);
			}
			else if( _tcscmp(pstrName, _T("Layout")) == 0 )
			{
				_sntprintf_s(attri.tcLayoutFile,sizeof(attri.tcLayoutFile),pstrValue);
			} 
			 
		}
 
		m_dlgMap.insert(  DLGMAP::value_type(pstrDlgName, attri) );

		root = root.GetSibling();
	} 

	return TRUE;
}

BOOL CDlgManager::DoCase( const LPCTSTR szCaseName, const LPCTSTR szDlgName  )
{
	CDUIDialog* pDlg = FindDlgByName(  szDlgName );
	if ( NULL != pDlg )
	{
		return pDlg->DoCase( szCaseName );
	}
	return FALSE;
}

int CDlgManager::DoModal( const LPCTSTR szDlgMapXml )
{
	CDUIDialog*  pDlg = FindDlgByName( szDlgMapXml );
	if( NULL != pDlg )
	{
		return pDlg->DoModal();
	}
	return -1;

}

void CDlgManager::EndModal( const LPCTSTR szDlgMapXml, int nResult )
{
	CDUIDialog*  pDlg = FindDlgByName( szDlgMapXml );
	if( NULL != pDlg )
	{
		 pDlg->EndModal( nResult );
	}
	 
}





///////////////////////CWindowStyleMap////////////////////////////////////////////////////////////

#ifdef _UNICODE
typedef std::wstring tstring;
typedef std::wstringstream tstringstream;
#else
typedef std::string tstring;
typedef std::stringstream tstringstream;
#endif

const TCHAR	CWindowStyleMap::m_chPartitionChar = _T('|');
std::map< CStdString, DWORD >  CWindowStyleMap::m_mapStyles;
DWORD CWindowStyleMap::StringToStyle( LPCTSTR str  )
{ 
	tstring sub_str;
	DWORD dwResult = 0;
	bool bFind = false;
 
	tstringstream  ss( str );
	while( getline( ss, sub_str, CWindowStyleMap::m_chPartitionChar ) )         
	{
		DefaultStyleMap::iterator itr = m_mapStyles.find( sub_str.c_str() );

		if ( itr != m_mapStyles.end() )
		{		
			dwResult |= itr->second;
			bFind = true;					
		}	
	} 
	 
	return dwResult;
}


bool CWindowStyleMap::StringToStyle( LPCTSTR str, DWORD& dwStyle, DWORD& dwStyleEx )
{
	bool bFind = false;
	tstringstream ss( str );
	tstring sub_str;
	DWORD dwResult = 0;

	while( getline( ss, sub_str, CWindowStyleMap::m_chPartitionChar ) )         
	{
		DefaultStyleMap::iterator itr = m_mapStyles.find( sub_str.c_str() );

		if ( itr != m_mapStyles.end() )
		{	
			if ( sub_str.find(_T("EX")))
			{
				dwStyleEx |= itr->second;
			}
			else
			{
				dwResult |= itr->second;
			}

			bFind = true;					
		}	
	}
	dwStyle = dwResult;
	return bFind;
}


bool CWindowStyleMap::RegStyle( DWORD dwStyle, LPCTSTR str )
{
	DefaultStyleMap::iterator itr = m_mapStyles.find( str );
	if ( itr == m_mapStyles.end() )
	{
		m_mapStyles.insert( DefaultStyleMap::value_type( str, dwStyle) );
		return true;
	}
	return false;
}

}