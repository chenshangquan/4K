// uiDataMgr.cpp: implementation of the CUIDataMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "uiDataMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const string g_stcMsgboxDlg = "MsgboxDlg";	//警示弹出框
const string g_strMainFrame = "MainFrame" ; // 	CfgCnsDlg
const string g_strBasicInfoDlg = "BasicInfoDlg"; //基本信息界面		 
const string g_strCfgFrame = "CfgFrame";        //配置框架	
const string g_strCfgAudioPort = "CfgAudioPortDlg";	//配置框架中的音频接口界面
const string g_strCfgAudioDlg = "CfgAudioDlg";		//配置框架中的音频配置界面
const string g_strCfgMainAudioDlg = "CfgMainAudioDlg";		//配置框架中的主视频配置界面
const string g_strCfgDemonStrationDlg = "CfgDemonStrationDlg";   //配置框架中的演示源设置界面
const string g_strCfgAdjustImageDlg = "CfgAdjustImageDlg" ;   //配置框架中的图像参数配置界面
const String g_strRenameOptDlg = "RenameOptDlg";	//重命名窗口
const String g_strCfgEqDlg = "CfgEqDlg";	//配置框架中的均衡器界面

const string g_strCnsCfg = "CfgCnsFrame";        //CNS配置
const string g_strCfgCnsDlg = "CfgCnsDlg";		//配置框架中的cns界面	
//const string g_strCfgMixDlg = "CfgMixAudioDlg"; //配置框架中的混音配置界面
const String g_strCfgServerDlg = "CfgServerDlg";		//配置框架中的服务器界面
const String g_strCfgCallSer = "CfgCallSerDlg";			//呼叫配置界面
const String g_strCfgAdvanceDlg = "CfgAdvanceDlg";			//高级配置界面

//const string g_strDiagInfoDlg = "DiagInfoDlg";		//诊断测试界面
const string g_strCfgDiagnosticFrame = "CfgDiagnosticFrame";   //诊断测试界面
const string g_strDiagInterfaceDlg = "InterfaceDiagnosticDlg";  //接口诊断界面
const string g_strNetDiagnosticDlg = "NetDiagnosticDlg";        //网络诊断界面
const string g_strNetPacketDlg = "NetPacketDlg";                //网口抓包界面

const string g_strCentCfgFrame = "CentCfgFrame";		//中控信息界面
const string g_strDiagInTestInfo = "DiagTestInDlg";	//输入测试界面
const string g_strDiagOutTestInfo = "DiagTestOutDlg";	//输出测试界面
const string g_strDiagTestFrame = "DiagTestFrame";	//诊断测试显示界面
const string g_strDiagStatistic = "StatisticOptDlg";	//统计界面
const String g_stcStrCfgNetMngDlg		= "CfgNetMngDlg";			//网管配置界面
const String g_stcStrCfgNetSecurityDlg  = "CfgNetSecurityDlg";      //网络安全配置界面
const String g_stcStrNetMngOptDlg		= "NetMngOptDlg";			//网管操作界面
const String g_stcStrRouteCfgDlg        = "RouteCfgInfoDlg";        //路由配置界面
const String g_StrCameraDlg			= "CameraDlg";				//摄像调节界面
const String g_strAddrbookExpDlg = "AddrbookExpDlg";			//地址簿界面
const String g_stcStrImpCommonDlg		= "ImpCommonDlg";		//上传（导入）通用弹出界面  如：导入摄像机参数、升级相关界面   界面基本相同  通过方案区分
const String g_stcStrExpCommonDlg		= "ExpCommonDlg";		//下载（导出）通用弹出界面  如：导出配置、下载日志界面  界面基本相同  通过方案区分
const String g_strWarningDlg = "WaringDlg";
const String g_strCentAirCondition = "CentCfgAirConditionDlg";	//中控空调配置界面
const String g_strCentCameraDlg = "CentCfgCameraDlg";	//中控摄像机界面
const String g_strCentLightDlg = "CentCfgLightDlg";		//中控灯光界面
const String g_strCentDisplayDlg = "CentCfgDisplayDlg";	//中控电视机界面
const String g_strCentStatusMesDlg = "CentCfgStatusMesDlg";	//中控状态信息界面
const String g_strCentCurtainDlg = "CentCfgCurtainDlg";	//中控窗帘配置界面
const String g_strCentDuoVideo = "CentCfgDuoVideo";	//中控双流屏配置界面

//主要方案
const  string g_strShmShow = "SchmShow"; //显示方案 
const  string g_strShmHide = "SchmHide"; //隐藏方案


CUIDataMgr::CUIDataMgr()
{

}

CUIDataMgr::~CUIDataMgr()
{

}

BOOL CUIDataMgr::NotifyOuterWnd( UINT nMsg , WPARAM wparam, LPARAM lparam )
{
	BOOL bRe = FALSE;
	if ( NULL != g_hNotifyWnd )
	{
		::SendMessage( g_hNotifyWnd, nMsg, wparam, lparam );
		bRe = TRUE;
	}

	return bRe;
}

String CUIDataMgr::GetFileFolderPath( const String& strFilePath )
{
	String strFolderPath = strFilePath;
	s32 nPos = strFolderPath.rfind( "\\" );
	if ( nPos != std::string::npos )
	{
		strFolderPath = strFolderPath.substr( 0, nPos );
	}
	
	return strFolderPath;
}

String CUIDataMgr::OpenBrowseForFolder( const String& strFileName, HWND hWnd /*= NULL*/, BOOL bIsAddFileName /*= TRUE */ )
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
		//strFolderPath += "\\";

		if ( bIsAddFileName )
		{
			strFolderPath += strFileName;
		}
	}
	
	return strFolderPath;
}

BOOL CUIDataMgr::OpenFileDialog( const String& strFilter, const String& strDefFileName, String& strFilePathName, String& strFileName, BOOL bOpenStyle /*= TRUE */ )
{
	CFileDialog dlg( bOpenStyle, NULL, strDefFileName.c_str(), OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_NOCHANGEDIR, strFilter.c_str() ); // 参数一标明是浏览还是保存
	CString cstrName  = "";
	if ( dlg.DoModal() == IDOK )  
	{  
		cstrName = dlg.GetPathName();
		strFilePathName = cstrName.GetBuffer(cstrName.GetLength());
		cstrName = dlg.GetFileName();
		strFileName = cstrName.GetBuffer(cstrName.GetLength());
    } 
	else
	{
		return FALSE;
	}
	
	if ( FALSE == bOpenStyle )
	{	
		CFile cFile;
		CFileFind cFindExit;
		BOOL bWorking = cFindExit.FindFile(strFilePathName.c_str());
		if (bWorking == 1)
		{
			MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
			MSG_BOX( nMsgBoxRet, "同名文件已存在,是否替换？" );
			if ( MSGBOX_OK == nMsgBoxRet )
			{
				cFile.Remove(strFilePathName.c_str());
			}
			else
			{
				return false;
			}
		}
	}

	return TRUE;
}

BOOL CUIDataMgr::OpenMutiFileDlg(const String& strFilter, const String& strDefFileName, String& strFilePathName, vector<String>& vecStrFileName, BOOL bOpenStyle /*= TRUE */)
{
	CFileDialog dlg( bOpenStyle, NULL, strDefFileName.c_str(), OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_NOCHANGEDIR, strFilter.c_str() ); // 参数一标明是浏览还是保存
	CString cstrName  = "";
	if ( IDOK == dlg.DoModal() )
	{
		cstrName = dlg.GetPathName();
		strFilePathName = cstrName.GetBuffer(cstrName.GetLength());

		POSITION pos = dlg.GetStartPosition();
		while ( NULL != pos )
		{
			CString strPathName = dlg.GetNextPathName(pos);
			int length = strPathName.GetLength();     
            for( int i=length-1; i>0; i-- )
			{
				if( '\\' == strPathName.GetAt(i) )
				{
					CString StrTempPathName = strPathName.Right(length - i -1);
					vecStrFileName.push_back(StrTempPathName.GetBuffer(0));
					StrTempPathName.ReleaseBuffer();
                    break;
				}
			}
		}
	}

	return TRUE;
}

BOOL CUIDataMgr::CheckTransferFile( const String& strFileFullPath, const String& strCheckFileName )
{
	if ( strFileFullPath.empty() )
	{
		MSG_BOX_OK("路径不能为空!");	
		
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
		MSG_BOX_OK("请输入合法的文件全路径!"); 
		
		return FALSE;
	}
	
	return TRUE;
}

u64 CUIDataMgr::GetFileSize( const String& strFilePath )
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

BOOL CUIDataMgr::IsFileExist( const CString& strFileFullPath )
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

BOOL CUIDataMgr::IsFolderExist( const CString& strFolderFullPath )
{
	DWORD dwAttr; 
    dwAttr = GetFileAttributes(strFolderFullPath); 
    return ( dwAttr != INVALID_FILE_ATTRIBUTES ) && ( dwAttr & FILE_ATTRIBUTE_DIRECTORY); 
}

BOOL CUIDataMgr::IsIniFile( const String& strFileName )
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

CString CUIDataMgr::GetIpStr( unsigned int dwIPAddr )
{
	CString strIP;
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIPAddr);
	strIP = inet_ntoa(addrIPAddr);
	
    return strIP;
}

BOOL CUIDataMgr::RecusionMkDir( CString strFolder )
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

void CUIDataMgr::SetLstSelItem(const String& strLstWnd, IWndTree* pWndTree /*= NULL*/, s32 nItemNo)
{
	CTransparentList* pWnd = (CTransparentList*)UIFACTORYMGR_PTR->GetWindowPtr( strLstWnd, pWndTree );
	if ( NULL != pWnd )
	{
		pWnd->SetSelItem(nItemNo);
	}
}

bool CUIDataMgr::IsValidPWStr(CString szPWStr)
{
	if (szPWStr.IsEmpty())
	{
		return false;
	}
	//要求:8-16个字符，至少包含字母，数字，特殊字符三个中的两个
	int nCount = szPWStr.GetLength();
	if (nCount < 8 || nCount > 16)
	{
		return false;
	}
	//纯数字
	CString szTemp = szPWStr.SpanIncluding(_T("0123456789"));
	if (szTemp == szPWStr)
	{
		return false;
	}
	//纯英文字母
	szTemp = szPWStr.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	if (szTemp == szPWStr)
	{
		return false;
	}
	//纯特殊字符'.','_'
	szTemp = szPWStr.SpanIncluding(_T("._"));
	if (szTemp == szPWStr)
	{
		return false;
	}
	
	return true;
}

bool CUIDataMgr::IsValidNameStr( String strText )
{
	CString strError = INVALID_ALIAS_FOR_CODE;
	CString str(strText.c_str());
	CString strRe = str.SpanExcluding( strError );
	if ( strRe != str )
	{
		return false;
	} 
	return true;
}

bool CUIDataMgr::JudgeIp(char *szIP, IP_Struct::IpAdress_Struct *ipAdress)  
{  
    if (!szIP)
	{
		return false;  
	}
    int index = 0;  
    int first = 0, second = 0, third = 0, forth = 0;     
    std::string ip = std::string(szIP);  
    first = atoi(&ip[index]);    
    if ( first > 255 ) 
	{
        return false;  
	}
    if ( ipAdress )  
	{
        ipAdress->first=first;  
	}
	
    index ++;    
    index = ip.find_first_of('.',index);    
    second = atoi(&ip[++index]);    
    if( second > 255 )
	{
        return false;   
	}
    if (ipAdress)  
	{
        ipAdress->second=second;  
	}
	
    index ++;    
    index = ip.find_first_of('.',index);    
    third=atoi(&ip[++index]);    
    if( third > 255 ) 
	{
        return false;   
	}
    if (ipAdress)  
	{
        ipAdress->third=third;  
	}
	
    index ++;    
    index = ip.find_first_of('.',index);    
    forth = atoi(&ip[++index]);    
    if( forth > 255 )  
	{
        return false;    
	}
    if (ipAdress)
	{
        ipAdress->forth=forth;  
	}
	
    return true;    
}  

//-1 indicates ip格式错误，0表示不同网段，1表示同网段  
int CUIDataMgr::IsSameNetworkSegment(char *szIPAdress, char *szIPAdresss1, char *szMask)  
{  
    if (!szIPAdress || !szMask || !szIPAdresss1) 
	{ 
		return false;  
	}
    IP_Struct::IpAdress_Struct ip,ip1,mask;  
    if (JudgeIp(szIPAdress, &ip) && JudgeIp(szIPAdresss1, &ip1) && JudgeIp(szMask, &mask))  
    {  
		ip.first = ip.first & mask.first;    
		ip.second = ip.second & mask.second;    
		ip.third = ip.third & mask.third;    
		ip.forth = ip.forth & mask.forth;    
		
		ip1.first = ip1.first & mask.first;    
		ip1.second = ip1.second & mask.second;    
		ip1.third = ip1.third & mask.third;    
		ip1.forth = ip1.forth & mask.forth;    
		
		if(ip.first == ip1.first && ip.second == ip1.second && ip.third == ip1.third && ip.forth == ip1.forth )    
		{
			return 1;  
		}
		else    
		{
			return 0;  
		}
    }  
    else  
	{
        return -1;  
	}
}  

bool CUIDataMgr::IsValidCloudUNStr( CString szUNStr )
{
    if (szUNStr.IsEmpty())
    {
        return false;
    }
    //要求:8-16个字符，至少包含字母，数字，特殊字符三个中的两个
    int nCount = szUNStr.GetLength();
    if (nCount < 1 || nCount > 16)
    {
        return false;
    }
    //除限定字符外的字符
    CString szTemp = szUNStr.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*#"));
    if (szTemp != szUNStr)
    {
        return false;
    }
    return true;
}

bool CUIDataMgr::IsValidCloudPWStr( CString szPWStr )
{
    if (szPWStr.IsEmpty())
    {
        return false;
    }
    //要求:8-16个字符，至少包含字母，数字，特殊字符三个中的两个
    int nCount = szPWStr.GetLength();
    if (nCount < 6 || nCount > 32)
    {
        return false;
    }
    //除限定字符外的字符
    CString szTemp = szPWStr.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_."));
    if (szTemp != szPWStr)
    {
        return false;
    }
    return true;
}

unsigned int CUIDataMgr::swapInt32(unsigned int value)  
{  
    return ((value & 0x000000FF) << 24) |  
		((value & 0x0000FF00) << 8) |  
		((value & 0x00FF0000) >> 8) |  
		((value & 0xFF000000) >> 24) ;  
}