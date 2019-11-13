// umstoolcommon.cpp: implementation of the CUmstoolCommon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umstooldll.h"
#include "umstoolcommon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern HWND g_hNotifyWnd;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUmstoolCommon::CUmstoolCommon()
{

}

CUmstoolCommon::~CUmstoolCommon()
{

}

BOOL CUmstoolCommon::IsFileExist(const CString& strFileFullPath)
{
	if( strFileFullPath.IsEmpty() )
	{
	   return FALSE;
	}

	DWORD dwAttr = GetFileAttributes(strFileFullPath);
	if( INVALID_FILE_ATTRIBUTES == dwAttr || ( dwAttr & FILE_ATTRIBUTE_DIRECTORY ) )
	{
	   return FALSE;
	}

	return TRUE;
}

BOOL CUmstoolCommon::IsFolderExist(const CString& strFolderFullPath)
{
    DWORD dwAttr; 
    dwAttr = GetFileAttributes(strFolderFullPath); 
    return ( dwAttr != INVALID_FILE_ATTRIBUTES ) && ( dwAttr & FILE_ATTRIBUTE_DIRECTORY); 
}

BOOL CUmstoolCommon::IsIniFile(const String& strFileName)
{
	if ( !IsFileExist(strFileName.c_str()) )
	{
		return FALSE;
	}

	String strFileExtName;
	s32 nPos = strFileName.rfind( "." );
	if ( nPos != std::string::npos )
	{
		strFileExtName = strFileName.substr( nPos + 1, strFileName.size() );
		if ( strFileExtName == "ini" )
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}

	return FALSE;
}

CString CUmstoolCommon::GetIpStr(unsigned int dwIPAddr)
{
	CString strIP;
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = dwIPAddr;
	strIP = inet_ntoa(addrIPAddr);

    return strIP;
}

void CUmstoolCommon::TimeToTm( struct tm& tmDate, const time_t& timeDate )
{
	time_t tm = timeDate;
	tmDate = *(localtime(&tm));
	tmDate.tm_year += 1900;
	tmDate.tm_mon += 1;
}

BOOL CUmstoolCommon::NotifyOuterWnd( UINT nMsg , WPARAM wparam, LPARAM lparam )
{
	BOOL bRe = FALSE;
	if ( NULL != g_hNotifyWnd )
	{
		::SendMessage( g_hNotifyWnd, nMsg, wparam, lparam );
		bRe = TRUE;
	}
	
	return bRe;	
}

void CUmstoolCommon::SetLstSelItem(const String& strLstWnd, IWndTree* pWndTree /*= NULL*/, s32 nItemNo)
{
	CTransparentList* pWnd = (CTransparentList*)UIFACTORYMGR_PTR->GetWindowPtr( strLstWnd, pWndTree );
	if ( NULL != pWnd )
	{
		pWnd->SetSelItem(nItemNo);
	}
}

BOOL CUmstoolCommon::RecusionMkDir(CString strFolder)
{
    s32 nLen = strFolder.GetLength();
    if( nLen < 2 ) 
	{
		return FALSE; 
    }

    if( '\\' == strFolder[nLen-1] )
    {
        strFolder = strFolder.Left( nLen-1 );
        nLen = strFolder.GetLength();
    }

    if ( nLen <= 0 ) 
	{
		return FALSE;
    }

    if ( nLen <= 3 ) 
    {
        if ( IsFolderExist(strFolder) )
		{
			return TRUE;
        }
		else
		{
			return FALSE; 
		}
    }

    if ( IsFolderExist(strFolder) )
	{
		return TRUE;
	}

    CString strParent;
    strParent = strFolder.Left( strFolder.ReverseFind('\\') );
    if( strParent.GetLength() <= 0)
	{
		return FALSE; 
    }

    BOOL bRet = RecusionMkDir(strParent); 
    if( bRet ) 
    {
        SECURITY_ATTRIBUTES sa;
        sa.nLength = sizeof(SECURITY_ATTRIBUTES);
        sa.lpSecurityDescriptor = NULL;
        sa.bInheritHandle = 0;
        bRet = CreateDirectory( strFolder, &sa );

        return bRet;
    }
    else
	{
        return FALSE;
	}

	return TRUE;
}

String CUmstoolCommon::GetFileFolderPath(const String& strFilePath)
{
	String strFolderPath = strFilePath;
	s32 nPos = strFolderPath.rfind( "\\" );
	if ( nPos != std::string::npos )
	{
		strFolderPath = strFolderPath.substr( 0, nPos );
	}

	return strFolderPath;
}

String CUmstoolCommon::OpenBrowseForFolder( const String& strFileName, HWND hWnd /*= NULL*/, BOOL bIsAddFileName )
{
	String    strFolderPath;
	BROWSEINFO broInfo = {0};
	TCHAR       szDisName[MAX_PATH] = {0};
	
	broInfo.hwndOwner = hWnd/*NULL*/;
	broInfo.pidlRoot  = NULL;
	broInfo.pszDisplayName = szDisName;
	broInfo.lpszTitle = _T("选择保存路径");
	broInfo.ulFlags   = BIF_NEWDIALOGSTYLE | BIF_DONTGOBELOWDOMAIN
		| BIF_BROWSEFORCOMPUTER | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
	broInfo.lpfn      = NULL;
	broInfo.lParam    = NULL;
	
	LPITEMIDLIST pIDList = SHBrowseForFolder(&broInfo);
	if (pIDList != NULL)
	{
		memset(szDisName, 0, sizeof(szDisName));
		SHGetPathFromIDList(pIDList, szDisName);
		strFolderPath = szDisName;

		CString str(strFolderPath.c_str());
		s32 nIndex = str.Find( "\\", str.GetLength()-1 );
		if ( nIndex == -1 )
		{
			strFolderPath += "\\";
	    }

		if ( bIsAddFileName )
		{
			strFolderPath += strFileName;
		}
	}
	
	return strFolderPath;
}

BOOL CUmstoolCommon::OpenFileDialog( const String& strFilter, const String& strDefFileName, String& strFilePathName,
		 String& strFileName, BOOL bOpenStyle, BOOL bUpdate )
{
	if ( bUpdate )
	{
		//kdvmpu2、kdvapu2升级只有.bin格式
		if ( strDefFileName == "kdvmpu2.bin" || strDefFileName == "kdvapu2.bin" )
		{
			CString str;
			str.Format( "Layer Files (%s)|%s;)||", strDefFileName.c_str(), strDefFileName.c_str() );
			CFileDialog dlg( bOpenStyle, NULL, strDefFileName.c_str(), 
				OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_NOCHANGEDIR,	str ); // 参数一标明是浏览还是保存
			if ( dlg.DoModal() == IDOK )  
			{  
				CString cstrPathName = dlg.GetPathName();
				CString cstrFullName = dlg.GetFileName();
				strFilePathName = cstrPathName.GetBuffer(cstrPathName.GetLength());  
				strFileName = cstrFullName.GetBuffer(cstrFullName.GetLength()); 
			}
		}
		else
		{
			CString strDefFileNameGz(strDefFileName.c_str());
			strDefFileNameGz += ".gz";
			CString str;
			str.Format( "Layer Files (%s or %s)|%s;%s;)||", strDefFileName.c_str(), strDefFileNameGz, strDefFileName.c_str(), strDefFileNameGz );
			CFileDialog dlg( bOpenStyle, NULL, strDefFileName.c_str(), 
				OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_NOCHANGEDIR,	str ); // 参数一标明是浏览还是保存
			if ( dlg.DoModal() == IDOK )  
			{  
				CString cstrPathName = dlg.GetPathName();
				CString cstrFullName = dlg.GetFileName();
				strFilePathName = cstrPathName.GetBuffer(cstrPathName.GetLength());  
				strFileName = cstrFullName.GetBuffer(cstrFullName.GetLength()); 
			} 
		}
	}
	else
	{
		CString str;
		str.Format( "Layer Files (%s)|%s;)||", strDefFileName.c_str(), strDefFileName.c_str() );
		CFileDialog dlg( bOpenStyle, NULL, strDefFileName.c_str(),
			OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_NOCHANGEDIR,	str ); // 参数一标明是浏览还是保存
		if ( dlg.DoModal() == IDOK )  
		{  
			CString cstrPathName = dlg.GetPathName();
			CString cstrFullName = dlg.GetFileName();
			strFilePathName = cstrPathName.GetBuffer(cstrPathName.GetLength());  
			strFileName = cstrFullName.GetBuffer(cstrFullName.GetLength()); 
		} 
	}
	
	return TRUE;
}

BOOL CUmstoolCommon::CheckTransferFile( const String& strFileFullPath, const String& strCheckFileName )
{	
	if ( strFileFullPath.empty() )
	{
		MSG_BOX_OK("路径不能为空！");	
		
		return FALSE;
	}
	
	s32 nPos = strFileFullPath.rfind( "\\" );
	String strFileName = strFileFullPath;
	if ( nPos != std::string::npos )
	{
		strFileName = strFileName.substr( nPos + 1, strFileName.size() );
	}
	
	if ( strCheckFileName != strFileName )
	{
		MSG_BOX_OK("请输入合法的文件全路径！");
		
		return FALSE;
	}
	
	return TRUE;
}

u64 CUmstoolCommon::GetFileSize( const String& strFilePath )
{
	if( strFilePath.empty() )
	{
		return 0;
	}
	
	if ( !::PathFileExists(strFilePath.c_str()) )
	{
		return 0;
	}
	
	CFileException ex;
	CFile file;
	if ( !file.Open( strFilePath.c_str(), CFile::modeRead|CFile::shareDenyNone ) )
	{
		TCHAR chError[1024];
		ex.GetErrorMessage( chError, 1024 );
		return 0;
	}
	
	u64 nFileSize = file.GetLength();
	file.Close();
	
	return nFileSize;
}

std::vector<CString> CUmstoolCommon::GetDeviceName()
{
	std::vector<CString> vecDeviceName;	
	THduCfg tHduCfg;
	String  strMdlName;
	std::multimap<u8,THduCfg> mulmapHduCfg = DATAMGRPTR->GetUmsTvwBoardData();
	for ( std::multimap<u8,THduCfg>::iterator iter = mulmapHduCfg.begin(); iter != mulmapHduCfg.end(); iter++ )
	{
		tHduCfg = (*iter).second;
		strMdlName = tHduCfg.m_tName.m_abyAlias;
		if ( !strMdlName.empty() )
		{
			vecDeviceName.push_back(tHduCfg.m_tName.m_abyAlias);
		}
	}
	
	return vecDeviceName;
}

BOOL CUmstoolCommon::IsInvalidChar(const String& strText, int argc, ...)
{
	// 声明一个指针, 用于持有可变参数
	va_list pArg;
	// 将 pArg 初始化为指向第一个参数
	va_start(pArg, argc);
	for(int i = 0; i != argc; ++i)
	{
		char* pChar = va_arg(pArg, char*);
		// 获取 pArg 所指向的参数
		if ( strText.find(pChar) != std::string::npos || strText.find(pChar) != std::string::npos 
			|| strText.find(pChar) != std::string::npos )
		{
			return TRUE;
		}
	}
	va_end(pArg);

	return FALSE;
}
