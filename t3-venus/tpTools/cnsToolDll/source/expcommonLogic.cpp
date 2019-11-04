// expcommonLogic.cpp: implementation of the CExpCommonDlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "expcommonLogic.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExpCommonDlgLogic::CExpCommonDlgLogic()
:m_strEdtSaveFolder("EdtExpCommonSaveFolder")
,m_strProgressExp("ProgressExpCommon")
{
	m_pWnd = NULL;
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_nCount = 0;
	m_nCfgCount = 0;
	m_vctDownFile.clear();
	m_vctDownCfgFile.clear();
	m_bDownloadLog = FALSE;
	m_bExportConfig = FALSE;
}

CExpCommonDlgLogic::~CExpCommonDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CExpCommonDlgLogic::RegMsg()
{
	CExpCommonDlgLogic *pThis =  GetSingletonPtr();
	
    REG_MSG_HANDLER( UI_SETFTPINFO_Rsp, CExpCommonDlgLogic::OnSetFtpInfoRsp, pThis, CExpCommonDlgLogic );
}

void CExpCommonDlgLogic::UnRegMsg()
{
	
}

void CExpCommonDlgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::InitWnd", CExpCommonDlgLogic::InitWnd, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic);
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnClose", CExpCommonDlgLogic::OnBtnClose, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnDownloadLogWork", CExpCommonDlgLogic::OnBtnDownloadLogWork, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnExportConfigWork", CExpCommonDlgLogic::OnBtnExportConfigWork, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnExportCameraCfg", CExpCommonDlgLogic::OnBtnExportCameraCfg, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_FTPLOGPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnDownloadProgress", CExpCommonDlgLogic::OnDownloadProgress, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnExportScan", CExpCommonDlgLogic::OnBtnExportScan, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnOpenFolder", CExpCommonDlgLogic::OnBtnOpenFolder, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnFolderEditChange", CExpCommonDlgLogic::OnFolderEditChange, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
}

void CExpCommonDlgLogic::UnRegFunc()
{
	
}

bool CExpCommonDlgLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	
	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrExpCommonDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}

	return true;
}

void CExpCommonDlgLogic::Clear()
{
	 if ( NULL== m_pWndTree )
	 {
		 return;
	 }

	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrExpCommonDlg );
	
	CleanTransfer();	
	m_bDownloadLog = FALSE;
	m_bExportConfig = FALSE;
}

bool CExpCommonDlgLogic::OnBtnClose( const IArgs & arg )
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrExpCommonDlg );
	
	CleanTransfer();
	
	return true;
}

bool CExpCommonDlgLogic::OnBtnDownloadLogWork( const IArgs & arg )
{
//	DownloadCore( CNSLOG_FILE_PATH, CNSLOG_FILE_NAME );
	//m_lstFtpFile.clear();
    //m_dwTotalFileSize = 0;
    
    //m_pThread = AfxBeginThread(ThreadDwonLoad, this); 
	String strSavePath;
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	strSavePath = valFolderName.strCaption.c_str();
	
	if ( strSavePath.empty() )
	{
		MSG_BOX_OK("路径不能为空！");	
		return false;
	}

	TTPFtpInfo tTPFtpInfo;
    LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
	if (!tTPFtpInfo.bOpen)
	{
		//增加提示
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "日志下载，需开启FTP服务，请确认是否开启？" );	
		if ( nMsgBoxRet != MSGBOX_OK )
		{
			return false;		 
		}
        tTPFtpInfo.bOpen = TRUE;
		u16 wRet = COMIFMGRPTR->SetFtpInfoRsq(tTPFtpInfo);
		
		if( wRet != NO_ERROR)
		{
			WARNMESSAGE("FTP服务请求设置失败");
			return false;
		}

		m_bDownloadLog = TRUE;
	}
	else
	{
		DownloadLogWork();
	}

	return true;	
}

bool CExpCommonDlgLogic::OnBtnExportConfigWork( const IArgs & arg )
{
	String strSavePath;
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	strSavePath = valFolderName.strCaption.c_str();
	
	if ( strSavePath.empty() )
	{
		MSG_BOX_OK("路径不能为空！");	
		return false;
	}

	TTPFtpInfo tTPFtpInfo;
    LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
	if (!tTPFtpInfo.bOpen)
	{
		//增加提示
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "导出文件需开启FTP服务，请确认是否开启？" );	
		if ( nMsgBoxRet != MSGBOX_OK )
		{
			return false;		 
		}

		tTPFtpInfo.bOpen = TRUE;
		u16 wRet = COMIFMGRPTR->SetFtpInfoRsq(tTPFtpInfo);
		
		if( wRet != NO_ERROR)
		{
			WARNMESSAGE("FTP服务请求设置失败");
			return false;
		}

        m_bExportConfig = TRUE;
	}
	else
	{
		ExportConfigWork();
	}
		
	return true;
}

bool CExpCommonDlgLogic::OnBtnExportCameraCfg( const IArgs & arg )
{
	DownloadCore(CNSCAMERA_FILE_PATH, CNSCAMERA_FILE_NAME );
	
	return true;
}

bool CExpCommonDlgLogic::OnDownloadProgress( const IArgs & arg )
{
	string strCaption;
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);
	
	UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
	switch( m_emFileFtpStatus )
	{
	case emFtpBegin:
		{
			m_dwTotalFileSize = static_cast<u32>(msg.lParam);
			
// 			if ( ( "下载日志" != strCaption ) || ( ( "下载日志" == strCaption )&&( m_vctDownFile.size() == m_nCount)))
// 			{
// 				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree );
// 			}

			if( ( "导出摄像机配置" == strCaption ) || (( "下载日志" == strCaption )&&( m_vctDownFile.size() == m_nCount )) || (( "导出配置" == strCaption )&&( m_vctDownCfgFile.size() == m_nCfgCount)) )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree );
			}

		}
		break;
	case emFtpTransfer:
		{
			if ( m_dwTotalFileSize != 0 )
			{
				Value_ProgressPos valProgress;
				float fCurrTransProgress;
				u32 dwCurrentTransSize = static_cast<u32>(msg.lParam);   //当前传输的大小
				
				if ( "下载日志" == strCaption )
				{
					fCurrTransProgress = (float)dwCurrentTransSize/m_dwTotalFileSize*100/m_nCount + ( m_nCount-m_vctDownFile.size() )*100/m_nCount;
				}
				else if( "导出配置" == strCaption )
				{
					fCurrTransProgress = (float)dwCurrentTransSize/m_dwTotalFileSize*100/m_nCfgCount + ( m_nCount-m_vctDownFile.size() )*100/m_nCfgCount;
				}
				else
				{
					fCurrTransProgress = (float)dwCurrentTransSize/m_dwTotalFileSize*100 ;
				}

				UIFACTORYMGR_PTR->GetPropertyValue(valProgress,m_strProgressExp,m_pWndTree);
				
				m_valProgress.nPos = (u32)fCurrTransProgress;
				
				if ( valProgress.nPos < m_valProgress.nPos )
				{
					UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressExp, m_pWndTree );
				}
			}
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP接口0为成功  默认失败
			if ( 0 == dwSuccess )
			{
				if ( m_vctDownFile.size() > 0 )
				{
					vector<String>::iterator itr = m_vctDownFile.begin();
					m_vctDownFile.erase(itr);
					u32 n= m_vctDownFile.size();
					//CString str;
					//str.Format( "%d / %d", m_nCount-n+1, m_nCount );
					if ( n > 0 )
					{	
						DownLoadLogFile( CNSLOG_FILE_PATH, m_vctDownFile.at(0) );
						return true;
					}
				}
				
				if( m_vctDownCfgFile.size() > 0 )
				{
					vector<String>::iterator itr = m_vctDownCfgFile.begin();
					m_vctDownCfgFile.erase(itr);
					u32 n= m_vctDownCfgFile.size();

					if ( n > 0 )
					{	
						DownLoadLogFile( CNSCONFIG_FILE_EXT_PATH, m_vctDownCfgFile.at(0) );
						return true;
					}
				}

				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
				m_cFtp.EndFtpFile();

				if ( "下载日志" == strCaption )
				{
					MSG_BOX_OK_SAFE("下载日志成功！",g_stcStrExpCommonDlg);
				}
				else if ( "导出配置" == strCaption )
				{
					MSG_BOX_OK_SAFE("导出配置成功！",g_stcStrExpCommonDlg);
				}
				else if ( "导出摄像机配置" == strCaption )
				{
					MSG_BOX_OK_SAFE("导出摄像机参数成功！",g_stcStrExpCommonDlg);
				}

				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
			}
			else
			{
				//FtpFindFirstFile Error With 18--没有更多文件.这是获取远端文件大小的时候提示的错误,不关闭Ftp,之后可以成功
				if ( dwSuccess == 18 )  
				{
					break;
				}
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				String strError = "导入导出文件出错，错误原因：";
				if( dwSuccess == 122 )    //win7中文件不存在时候的异常提醒“传递给系统调用的数据区域太小”
				{
					strError += "系统找不到指定的文件。";
					OspPrintf( TRUE, FALSE, (char*)strError.c_str() );
					MSG_BOX_OK_SAFE(strError,g_stcStrExpCommonDlg);
					LocalFree( pszMsg );
				}
				else
				{
					strError += pszMsg;
					OspPrintf( TRUE, FALSE, (char*)strError.c_str() );
					MSG_BOX_OK_SAFE(strError,g_stcStrExpCommonDlg);
					LocalFree( pszMsg );
				}
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBreak", m_pWndTree );
				m_cFtp.EndFtpFile();
			}	
			
		}
		break;
	default:
		{
		}
		break;
	}
	
	return true;
}

bool CExpCommonDlgLogic::OnBtnExportScan( const IArgs & arg )
{
	String strFile;
	String strCaption;
	String strFilter;
	String strFolder;
	UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
	if ( "下载日志" == strCaption )
	{
		strFile+= ""; 
		strFilter = "日志文件(*.ini)|*.ini||";
	}
	else if ( "导出配置" == strCaption )
	{
		strFile+= "";  
	}
	else if ( "导出摄像机配置" == strCaption )
	{
		strFile+= CNSCAMERA_FILE_NAME;  
		strFilter = "摄像机配置文件(cameracfg.ini)|cameracfg.ini||";
	}
/*	HWND hWnd = m_pWnd->GetSafeHwnd();*/
    String strExpFileFullPath;
	String strExpFileName;

	if ( "下载日志" == strCaption )																//日志文件含有多个，将弹出框改成保存路径的模式
	{
		strExpFileFullPath = UIDATAMGR_PTR->OpenBrowseForFolder("",NULL,FALSE);
	}
	else if( "导出配置" == strCaption )
	{
		strExpFileFullPath = UIDATAMGR_PTR->OpenBrowseForFolder("",NULL,FALSE);
	}
	else
	{
		UIDATAMGR_PTR->OpenFileDialog( strFilter, strFile, strExpFileFullPath, strExpFileName, FALSE );
	}
	
	if ( !strExpFileFullPath.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtSaveFolder, strExpFileFullPath, m_pWndTree );
		return true;
	}
	return false;
}

bool CExpCommonDlgLogic::OnBtnOpenFolder( const IArgs & arg )
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
	if ( "下载日志" == strCaption )
	{
		strFileFullPath+= "kdvlog_0.txt";  
	}
	
	if( "导出配置" == strCaption )
	{
		strFileFullPath+= CNSCONFIG_FILE_NAME;
	}

	if ( UIDATAMGR_PTR->IsFileExist( strFileFullPath.c_str() ) )
	{
		CString strParam("/select,");
		strParam += strFileFullPath.c_str();
		u32 dwIns = (u32)ShellExecute( 0, "open", "Explorer.exe", strParam, 0, SW_NORMAL );
		//u32 dwIns = (u32)::ShellExecute( NULL, "open", UIDATAMGR_PTR->GetFileFolderPath(strFileFullPath).c_str(), NULL, NULL, SW_SHOWNORMAL );
		if ( dwIns <= 32 )
		{
			MSG_BOX_OK("目录打开异常！");
		}
	}
	else
	{
		MSG_BOX_OK("路径文件不存在，打开失败！");
	}
	
	return true;
}

bool CExpCommonDlgLogic::OnFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", m_pWndTree, m_strProgressExp );
	
	return true;
}

void CExpCommonDlgLogic::CleanTransfer()
{
	if ( NULL == m_pWndTree )
	{
		return;
	}

	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}
	
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", m_pWndTree );
}

BOOL CExpCommonDlgLogic::DownloadCore( const String& strFilePath, const String& strCheckFileName )
{
	String strCaption;
	String strSavePath;
	Value_WindowCaption valFolderName;

	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	strSavePath = valFolderName.strCaption.c_str();

	if ( strSavePath.empty() )
	{
		MSG_BOX_OK("路径不能为空！");	
		
		return FALSE;
	}

	UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
	if ( "下载日志" == strCaption )
	{
		strSavePath+= m_vctDownFile.at(0);  
	}

	if( "导出配置" == strCaption )
	{
		strSavePath+= m_vctDownCfgFile.at(0);
	}

 	if ( !UIDATAMGR_PTR->CheckTransferFile( strSavePath, strCheckFileName ) )
 	{
 		return true;
 	}
	
	if ( UIDATAMGR_PTR->IsFileExist( strSavePath.c_str() ) || isLogFileExist( valFolderName.strCaption) || isCfgFileExist(valFolderName.strCaption)  )
	{
		MSGBOX_RET nResult = MSGBOX_OK;
		MSG_BOX( nResult, "导出文件已存在，是否覆盖？");
		if (nResult != MSGBOX_OK)
		{
			return FALSE;
		}
	}

	if ( !UIDATAMGR_PTR->RecusionMkDir(UIDATAMGR_PTR->GetFileFolderPath(strSavePath).c_str()) )
	{
		MSG_BOX_OK("目录创建失败，无法导出！");
		
		return true;
	}
	
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_FTPLOGPROGRESS );
	
	u32 dwIp;
	LIBDATAMGRPTR->GetLoginIp(dwIp);
	CString strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );

	EmCnModel emCnModel;
	LIBDATAMGRPTR->GetEmCnModelInfo( &emCnModel );

	BOOL32 bRet;
	if( LIBDATAMGRPTR->CheckVerNew() == false )
	{
		if( (emCnModel == T300) || (emCnModel == T300E ) || ( emCnModel == em7920 ) )
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, FTP_CONNECT_USER, FTP_CONNECT_PSWD );
		}
		else
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, T300E_TEL_USRNAME, T300E_TEL_PWD );
		}
	}
	else
	{
		TTPFtpInfo tTPFtpInfo;
		LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
		
		if( tTPFtpInfo.bOpen )
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, tTPFtpInfo.achUserName, tTPFtpInfo.achPassword );
		}
		else
		{
			bRet = 0;
		}
	}

	if ( !bRet )
	{
		MSG_BOX_OK("连接服务器失败！");	
		return false;
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFile = strFilePath;
		strRemoteFile += strCheckFileName;
		if ( !m_cFtp.BeginDownload( m_pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, FALSE ) )
		{
			MSG_BOX_OK("导出操作失败，参数错误！");
			UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBreak", m_pWndTree );
			return false;
		}
	}
	
	return TRUE;
}

BOOL CExpCommonDlgLogic::DownLoadLogFile( const String& strFilePath, const String& strCheckFileName )
{
	string strCaption;
	String strSavePath;
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	strSavePath = valFolderName.strCaption.c_str();
	strSavePath +=strCheckFileName;
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFile = strFilePath;
		strRemoteFile += strCheckFileName;
		if ( !m_cFtp.BeginDownload( m_pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, FALSE ) )
		{
			MSG_BOX_OK("导出操作失败，参数错误！");
			UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBreak", m_pWndTree );
			return FALSE;
		}
	}
	
	return TRUE;
}

BOOL CExpCommonDlgLogic::isLogFileExist( string &strSavePath )
{
	String strCaption;
	string strFileFullPath;
	UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
	
	if ( strCaption == "下载日志")
	{
		for( vector<String>::size_type index = 0 ; index < m_vctDownFile.size() ;index++ )
		{
			if ( m_vctDownFile.at(index).c_str() != NULL )
			{
				strFileFullPath = strSavePath+ m_vctDownFile.at(index).c_str();
				if( UIDATAMGR_PTR->IsFileExist( strFileFullPath.c_str() ) == TRUE )
				{
					return TRUE;
				}
			}
			else
			{
				return FALSE;
			}
		}
	}
	
	return FALSE;
}

BOOL CExpCommonDlgLogic::isCfgFileExist(string &strSavePath)
{
	String strCaption;
	string strFileFullPath;
	UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
	
	if ( strCaption == "导出配置")
	{
		for( vector<String>::size_type index = 0 ; index < m_vctDownCfgFile.size() ;index++ )
		{
			if ( m_vctDownCfgFile.at(index).c_str() != NULL )
			{
				strFileFullPath = strSavePath+ m_vctDownCfgFile.at(index).c_str();
				if( UIDATAMGR_PTR->IsFileExist( strFileFullPath.c_str() ) == TRUE )
				{
					return TRUE;
				}
			}
			else
			{
				return FALSE;
			}
		}
	}

	return FALSE;
}

HRESULT CExpCommonDlgLogic::OnSetFtpInfoRsp( WPARAM wparam, LPARAM lparam )
{
	TTPFtpInfo tTPFtpInfo = *(TTPFtpInfo*)(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);
	if( bSuccess ) 
	{
		//下载日志
		if (m_bDownloadLog)
		{
			if (tTPFtpInfo.bOpen)
			{
				m_bDownloadLog = FALSE;
                DownloadLogWork();
			}
		}

		//导出配置
	    if (m_bExportConfig)
	    {
			if (tTPFtpInfo.bOpen)
			{
				m_bExportConfig = FALSE;
                ExportConfigWork();
			}
	    }
	}
	return S_OK;
}

void CExpCommonDlgLogic::DownloadLogWork()
{
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_FTPLOGPROGRESS );
	
	u32 dwIp;
	LIBDATAMGRPTR->GetLoginIp(dwIp);
	CString strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );
	
	EmCnModel emCnModel;
	LIBDATAMGRPTR->GetEmCnModelInfo( &emCnModel );
	
	BOOL32 bRet;
	if( LIBDATAMGRPTR->CheckVerNew() == false )
	{
		if( (emCnModel == T300) || (emCnModel == T300E ) || ( emCnModel == em7920 ) )
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, FTP_CONNECT_USER, FTP_CONNECT_PSWD );
		}
		else
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, T300E_TEL_USRNAME, T300E_TEL_PWD );
		}
	}
	else
	{
		TTPFtpInfo tTPFtpInfo;
		LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
		
		if( tTPFtpInfo.bOpen )
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, tTPFtpInfo.achUserName, tTPFtpInfo.achPassword );
		}
		else
		{
			bRet = 0;
		}
	}
	
	if ( !bRet )
	{
		MSG_BOX_OK("连接服务器失败！");	
		return;
	}
	
	if ( m_cFtp.ConnectServer() )
	{
		m_vctDownFile.clear();
		if ( m_cFtp.FindfFtpFile( CNSLOG_FILE_PATH, "kdvlog_0.txt" ) )
		{
			m_nCount = 1;
			m_vctDownFile.push_back( "kdvlog_0.txt" );
		}
		if ( m_cFtp.FindfFtpFile( CNSLOG_FILE_PATH, "kdvlog_1.txt" ) )
		{
			m_nCount = 2;
			m_vctDownFile.push_back( "kdvlog_1.txt" );
		}
		if ( m_cFtp.FindfFtpFile( CNSLOG_FILE_PATH, "kdvlog_2.txt" ) )
		{
			m_nCount = 3;
			m_vctDownFile.push_back( "kdvlog_2.txt" );
		}
		
		if ( m_vctDownFile.size() > 0 )
		{
			DownloadCore( CNSLOG_FILE_PATH, m_vctDownFile.at(0) );
		}
		
		//CString str;
		//str.Format( "1 / %d", m_nCount );
		//UIFACTORYMGR_PTR->SetCaption( "StcFileCount", (LPCSTR)str, m_pWndTree );
	}
}

void CExpCommonDlgLogic::ExportConfigWork()
{
	m_vctDownCfgFile.clear();
	
	m_vctDownCfgFile.push_back( CNSCONFIG_FILE_NAME );
	m_vctDownCfgFile.push_back( CNSCONFIG_FILE_NAME_ZERO);
	m_vctDownCfgFile.push_back( CNSCONFIG_FILE_NAME_ONE);
	
	m_nCfgCount = 3;
	
	if( m_vctDownCfgFile.size() > 0 )
	{
		DownloadCore( CNSCONFIG_FILE_PATH, m_vctDownCfgFile.at(0) );
	}
}
