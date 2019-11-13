// addrbookexplogic.cpp: implementation of the CAddrbookExpLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umstooldll.h"
#include "addrbookexplogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAddrbookExpLogic::CAddrbookExpLogic():
m_strEdtImport("EdtImport"),
m_strProgressImp("ProgressImp"),
m_strEdtExport("EdtExport"),
m_strProgressExp("ProgressExp")
{
	m_pWnd = NULL;
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_valProgress.nPos = 0;
}

CAddrbookExpLogic::~CAddrbookExpLogic()
{  
	UnRegMsg();
	UnRegFunc();
}

void CAddrbookExpLogic::RegMsg()
{    

}

void CAddrbookExpLogic::UnRegMsg()
{

}

bool CAddrbookExpLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::InitWnd", CAddrbookExpLogic::InitWnd, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic);

	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnBtnImportAddrbook", CAddrbookExpLogic::OnBtnImportAddrbook, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnBtnExportAddrbook", CAddrbookExpLogic::OnBtnExportAddrbook, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnBtnImportAddrbookScan", CAddrbookExpLogic::OnBtnImportAddrbookScan, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnBtnExportAddrbookScan", CAddrbookExpLogic::OnBtnExportAddrbookScan, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnBtnExportFolder", CAddrbookExpLogic::OnBtnExportFolder, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 

	REG_DEFAULT_WINDOW_MSG( WM_UMSTOOL_FTPADDRBOOKPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnTransAddrbookProgress", CAddrbookExpLogic::OnTransAddrbookProgress, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic );

	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnExpFolderEditChange", CAddrbookExpLogic::OnExpFolderEditChange, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnImpFolderEditChange", CAddrbookExpLogic::OnImpFolderEditChange, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 
		
	return true;
}

bool CAddrbookExpLogic::UnRegFunc()
{

	return true;
}

bool CAddrbookExpLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrAddrbookExpDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}

    return true;
}

void CAddrbookExpLogic::Clear()
{
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}

	CleanTransfer();
}

void CAddrbookExpLogic::CleanTransfer()
{	
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}
	
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;

	m_strCurTransRemoteFileFullPath = "";

	UIFACTORYMGR_PTR->LoadScheme( "SchmAddrbookImpClean", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmAddrbookExpClean", m_pWndTree );
}

bool CAddrbookExpLogic::OnBtnImportAddrbookScan( const IArgs & arg )
{ 	
	String strFilter = "地址簿文件(*.adk)|*.adk||";  
	String strImpFileFullPath;
	String strImpFileName;
	CUmstoolCommon::OpenFileDialog( strFilter, ADDRBOOK_FILE_NAME, strImpFileFullPath, strImpFileName );
	if ( !strImpFileFullPath.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtImport, strImpFileFullPath, m_pWndTree );
	}

	return true;
}

bool CAddrbookExpLogic::OnBtnExportAddrbookScan( const IArgs & arg )
{
// 	HWND hWnd = m_pWnd->GetSafeHwnd();
// 	String strExpFileFullPath = CUmstoolCommon::OpenBrowseForFolder(ADDRBOOK_FILE_NAME, hWnd);
// 	if ( !strExpFileFullPath.empty() )
// 	{
// 		UIFACTORYMGR_PTR->SetCaption( m_strEdtExport, strExpFileFullPath, m_pWndTree );
// 	}

	String strFilter = "地址簿文件(*.adk)|*.adk||";  
	String strExpFileFullPath;
	String strExpFileName;
	CUmstoolCommon::OpenFileDialog( strFilter, ADDRBOOK_FILE_NAME, strExpFileFullPath, strExpFileName, FALSE );
	if ( !strExpFileFullPath.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtExport, strExpFileFullPath, m_pWndTree );
	}

	return true;
}

bool CAddrbookExpLogic::OnBtnImportAddrbook( const IArgs & arg )
{
	m_emFtpTransType = em_FTPTRANS_IMPORT;
	
	UploadCore(ADDRBOOK_FILE_NAME);
	
	return true;
}

bool CAddrbookExpLogic::OnBtnExportAddrbook( const IArgs & arg )
{
	m_emFtpTransType = em_FTPTRANS_EXPORT;
	
	DownloadCore(ADDRBOOK_FILE_NAME);

	return true;
}

BOOL CAddrbookExpLogic::DownloadCore(const String& strCheckFileName)
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtExport, m_pWndTree );
	
	String strSavePath;
	strSavePath = valFolderName.strCaption.c_str();
	if ( !CUmstoolCommon::CheckTransferFile( strSavePath, strCheckFileName ) )
	{
		return true;
	}

	if ( CUmstoolCommon::IsFileExist( strSavePath.c_str() ) )
	{
		MSGBOX_RET nResult = MSGBOX_OK;
		MSG_BOX( nResult, "导出文件已存在，是否覆盖？");
		if (nResult != MSGBOX_OK)
		{
			return FALSE;
		}
	}
	
	if ( !CUmstoolCommon::RecusionMkDir(CUmstoolCommon::GetFileFolderPath(strSavePath).c_str()) )
	{
		MSG_BOX_OK("目录创建失败，无法下载！");
		
		return true;
	}
	
	m_cFtp.RegisterMsgHandle( WM_UMSTOOL_FTPADDRBOOKPROGRESS );
	
	TLoginInfo tLoginInfo = COMMONMGRIFPTR->GetLoginInfo();
	CString strIpAddr = CUmstoolCommon::GetIpStr( htonl(tLoginInfo.dwIp) );
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	String strWarning;
	if ( !bRet )
	{
		MSG_BOX_OK("连接服务器失败！");
		
		return false;
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFile = ADDRBOOK_FILE_PATH;
		strRemoteFile += strCheckFileName;
		if ( !m_cFtp.BeginDownload( m_pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, FALSE ) )
		{
			String strError;
			strError.append("导出地址簿操作失败，参数错误！");
			MSG_BOX_OK(strError);
			
			return false;
		}
	}
	
	return TRUE;
}

BOOL CAddrbookExpLogic::UploadCore(const String& strCheckFileName)
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtImport, m_pWndTree );
	
	String strSavePath;
	strSavePath = valFolderName.strCaption.c_str();
	
	if ( !CUmstoolCommon::IsFileExist( strSavePath.c_str() ) )
	{
		MSG_BOX_OK("指定文件不存在，无法导入！");
		return false;
	}

	if ( !CUmstoolCommon::CheckTransferFile( strSavePath, strCheckFileName ) )
	{
		return true;
	}
	
	m_cFtp.RegisterMsgHandle( WM_UMSTOOL_FTPADDRBOOKPROGRESS );
	
	TLoginInfo tLoginInfo = COMMONMGRIFPTR->GetLoginInfo();
	CString strIpAddr = CUmstoolCommon::GetIpStr( htonl(tLoginInfo.dwIp) );
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	if ( !bRet )
	{
		MSG_BOX_OK("连接到服务器失败！");
		
		return false;
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFile = ADDRBOOK_FILE_PATH;
		strRemoteFile += strCheckFileName;
		strRemoteFile += ".temp";
		m_cFtp.SetIsRenameTransFile(TRUE);
		if ( !m_cFtp.BeginUpload( m_pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
		{
			String strError;
			strError.append("导入地址簿操作失败，参数错误！");
			MSG_BOX_OK(strError);
			
			return false;
		}
	}
	
	return TRUE;
}

bool CAddrbookExpLogic::OnTransAddrbookProgress( const IArgs & arg  )
{	
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);
	
	switch( m_emFileFtpStatus )
	{
	case emFtpBegin:
		{
			m_dwTotalFileSize = static_cast<u32>(msg.lParam);
			
			if ( em_FTPTRANS_IMPORT == m_emFtpTransType )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
			}
		}
		break;
	case emFtpTransfer:
		{
			if ( m_dwTotalFileSize != 0 )
			{
				u32 dwCurrentTransSize = static_cast<u32>(msg.lParam);   //当前传输的大小
				
				float fCurrTransProgress = (float)dwCurrentTransSize/m_dwTotalFileSize*100;
				if ( dwCurrentTransSize < m_dwTotalFileSize )
				{	
					m_valProgress.nPos = (u32)fCurrTransProgress;
					
					if ( em_FTPTRANS_IMPORT == m_emFtpTransType )
					{
						UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressImp, m_pWndTree );
					}
					else
					{
						UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressExp, m_pWndTree );
					}
				}
			}
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP接口0为成功  默认失败
			if ( 0 == dwSuccess )
			{
				if ( em_FTPTRANS_IMPORT == m_emFtpTransType )
				{
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strProgressImp );
				}
				else
				{
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strProgressExp );

					MSG_BOX_OK("导出地址簿成功！");
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
				}

				if ( m_emFtpTransType == em_FTPTRANS_IMPORT )
				{
					//导入成功   修改临时文件为实际文件   避免传输过程中意外终端产生的异常
					String strCurTransRemoteTempFileFullPath;
					String strRemoteFile = ADDRBOOK_FILE_PATH;
					strRemoteFile += ADDRBOOK_FILE_NAME;
					strCurTransRemoteTempFileFullPath = strRemoteFile;
					strCurTransRemoteTempFileFullPath += ".temp";				
					if ( !m_cFtp.RenameFtpFile( strCurTransRemoteTempFileFullPath.c_str(), strRemoteFile.c_str() ) )
					{
						MSG_BOX_OK("导入文件出错，错误原因：重命名文件失败！");
						
						UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
					}
					else
					{
						//地址簿成功后提醒是否重启
						MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
						MSG_BOX( nMsgBoxRet, "地址簿导入成功，是否重启ums服务器生效？"  );
						if ( MSGBOX_OK == nMsgBoxRet)
						{
						//	OspPrintf( TRUE, FALSE, "地址簿导入成功 MSG_BOX 重启服务器\n" );
							u16 nRet = COMMONMGRIFPTR->RebootReq();;
							if ( nRet != NO_ERROR )
							{
								MSG_BOX_OK( "重启ums请求发送失败！" );
							}
						}
					}
				}

				
			}
			else
			{
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				String strError = "导入导出文件出错，错误原因：";
				if( dwSuccess == 122 )    //win7中文件不存在时候的异常提醒“传递给系统调用的数据区域太小”
				{
					strError += "系统找不到指定的文件。";
					OspPrintf( TRUE, FALSE, (char*)strError.c_str() );
					MSG_BOX_OK(strError);
					LocalFree( pszMsg );
				}
				else
				{
					strError += pszMsg;
					OspPrintf( TRUE, FALSE, (char*)strError.c_str() );
					MSG_BOX_OK(strError);
					LocalFree( pszMsg );
				}

				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
			}
			
			m_cFtp.EndFtpFile();
		}
		break;
	default:
		{
		}
		break;
	}

	return true;
}

bool CAddrbookExpLogic::OnBtnExportFolder( const IArgs & arg )
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtExport, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();
	
	if ( CUmstoolCommon::IsFileExist( strFileFullPath.c_str() ) )
	{
		CString strParam("/select,");
		strParam += strFileFullPath.c_str();
		u32 dwIns = (u32)ShellExecute( 0, "open", "Explorer.exe", strParam, 0, SW_NORMAL );
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

bool CAddrbookExpLogic::OnImpFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmAddrbookImpClean", m_pWndTree, m_strProgressImp );
	
	return true;
}

bool CAddrbookExpLogic::OnExpFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmAddrbookExpClean", m_pWndTree, m_strProgressExp );
	
	return true;
}
