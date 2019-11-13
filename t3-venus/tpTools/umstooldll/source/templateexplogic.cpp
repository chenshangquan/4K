// templateexplogic.cpp: implementation of the CTemplateExpLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umstooldll.h"
#include "templateexplogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTemplateExpLogic::CTemplateExpLogic():
m_strEdtImport("EdtImport"),
m_strProgressImp("ProgressImp"),
m_strEdtExport("EdtExport"),
m_strProgressExp("ProgressExp"),
m_strBtnExportTmp("BtnExportTmp"),
m_strBtnExportScan("BtnExportScan")
{
	m_pWnd = NULL;
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_valProgress.nPos = 0;
	m_strImpFileName = "";
	m_strExpFileName = "";
}

CTemplateExpLogic::~CTemplateExpLogic()
{  
	UnRegMsg();
	UnRegFunc();
}

void CTemplateExpLogic::RegMsg()
{    
	REG_MSG_HANDLER( UI_UMSTOOL_EXPTEMPLATE_RSP, CTemplateExpLogic::OnExpTemplateRsp, TEMPLATEEXPLOGICRPTR, CTemplateExpLogic );
}

void CTemplateExpLogic::UnRegMsg()
{

}

bool CTemplateExpLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CTemplateExpLogic::InitWnd", CTemplateExpLogic::InitWnd, TEMPLATEEXPLOGICRPTR, CTemplateExpLogic);

	REG_GOBAL_MEMBER_FUNC( "CTemplateExpLogic::OnBtnImportTmp", CTemplateExpLogic::OnBtnImportTmp, TEMPLATEEXPLOGICRPTR, CTemplateExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTemplateExpLogic::OnBtnExportTmp", CTemplateExpLogic::OnBtnExportTmp, TEMPLATEEXPLOGICRPTR, CTemplateExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTemplateExpLogic::OnBtnImportTmpScan", CTemplateExpLogic::OnBtnImportTmpScan, TEMPLATEEXPLOGICRPTR, CTemplateExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTemplateExpLogic::OnBtnExportTmpScan", CTemplateExpLogic::OnBtnExportTmpScan, TEMPLATEEXPLOGICRPTR, CTemplateExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTemplateExpLogic::OnBtnExportFolder", CTemplateExpLogic::OnBtnExportFolder, TEMPLATEEXPLOGICRPTR, CTemplateExpLogic ); 

	REG_DEFAULT_WINDOW_MSG( WM_UMSTOOL_FTPTEMPLATEPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CTemplateExpLogic::OnTransTmpProgress", CTemplateExpLogic::OnTransTmpProgress, TEMPLATEEXPLOGICRPTR, CTemplateExpLogic );

	REG_GOBAL_MEMBER_FUNC( "CTemplateExpLogic::OnExpFolderEditChange", CTemplateExpLogic::OnExpFolderEditChange, TEMPLATEEXPLOGICRPTR, CTemplateExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTemplateExpLogic::OnImpFolderEditChange", CTemplateExpLogic::OnImpFolderEditChange, TEMPLATEEXPLOGICRPTR, CTemplateExpLogic ); 

	return true;
}

bool CTemplateExpLogic::UnRegFunc()
{

	return true;
}

bool CTemplateExpLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrTemplateExpDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}

    return true;
}

void CTemplateExpLogic::Clear()
{
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}

	CleanTransfer();
}

void CTemplateExpLogic::CleanTransfer()
{	
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}
	
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;

	m_strCurTransRemoteFileFullPath = "";
	m_strImpFileName = "";
	m_strExpFileName = "";

	UIFACTORYMGR_PTR->LoadScheme( "SchmTemplateImpClean", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmTemplateExpClean", m_pWndTree );
}

bool CTemplateExpLogic::OnBtnImportTmpScan( const IArgs & arg )
{ 	
	String strFilter = "会议模板文件(*.conf)|*.conf||";  
	String strImpFileFullPath;
	CUmstoolCommon::OpenFileDialog( strFilter, TEMPLATE_FILE_NAME, strImpFileFullPath, m_strImpFileName );
	if ( !strImpFileFullPath.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtImport, strImpFileFullPath, m_pWndTree );
	}

	return true;
}

bool CTemplateExpLogic::OnBtnExportTmpScan( const IArgs & arg )
{
// 	HWND hWnd = m_pWnd->GetSafeHwnd();
// 	String strExpFileFullPath = CUmstoolCommon::OpenBrowseForFolder(TEMPLATE_FILE_NAME, hWnd);
// 	if ( !strExpFileFullPath.empty() )
// 	{
// 		UIFACTORYMGR_PTR->SetCaption( m_strEdtExport, strExpFileFullPath, m_pWndTree );
// 	}

	String strFilter = "会议模板文件(*.conf)|*.conf||";  
	String strExpFileFullPath;
	CUmstoolCommon::OpenFileDialog( strFilter, TEMPLATE_FILE_NAME, strExpFileFullPath, m_strImpFileName, FALSE );
	if ( !strExpFileFullPath.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtExport, strExpFileFullPath, m_pWndTree );
	}

	return true;
}

bool CTemplateExpLogic::OnBtnImportTmp( const IArgs & arg )
{
	m_emFtpTransType = em_FTPTRANS_IMPORT;
	
	UploadCore();
	
	return true;
}

bool CTemplateExpLogic::OnBtnExportTmp( const IArgs & arg )
{
	m_emFtpTransType = em_FTPTRANS_EXPORT;
	
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtExport, m_pWndTree );
	
	String strSavePath;
	strSavePath = valFolderName.strCaption.c_str();
	
	if ( strSavePath.empty() )
	{
		MSG_BOX_OK("路径不能为空！");	
		
		return false;
	}

	u16 nRet = COMMONMGRIFPTR->ExportInfoReq();;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "导出会议模板ums请求发送失败！" );
	}

	UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
	UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strBtnExportTmp );
	UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strBtnExportScan );

	return true;
}

BOOL CTemplateExpLogic::DownloadCore()
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtExport, m_pWndTree );
	
	String strSavePath;
	strSavePath = valFolderName.strCaption.c_str();

	if ( CUmstoolCommon::IsFileExist( strSavePath.c_str() ) )
	{
		MSGBOX_RET nResult = MSGBOX_OK;
		MSG_BOX( nResult, "导出文件已存在，是否覆盖？");
		if (nResult != MSGBOX_OK)
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strBtnExportTmp );
			UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strBtnExportScan );

			return FALSE;
		}
	}

	m_valProgress.nPos = 10;
	UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressExp, m_pWndTree );

	if ( !CUmstoolCommon::RecusionMkDir(CUmstoolCommon::GetFileFolderPath(strSavePath).c_str()) )
	{
		MSG_BOX_OK("目录创建失败，无法下载！");

		UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strBtnExportTmp );
		UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strBtnExportScan );
		UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
		
		return TRUE;
	}
	
	m_cFtp.RegisterMsgHandle( WM_UMSTOOL_FTPTEMPLATEPROGRESS );
	
	TLoginInfo tLoginInfo = COMMONMGRIFPTR->GetLoginInfo();
	CString strIpAddr = CUmstoolCommon::GetIpStr( htonl(tLoginInfo.dwIp) );
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	if ( !bRet )
	{
		MSG_BOX_OK("连接服务器失败！");

		UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strBtnExportTmp );
		UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strBtnExportScan );
		UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
		
		return FALSE;
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFile = TEMPLATE_FILE_PATH;
		strRemoteFile += TEMPLATE_FILE_NAME;
		if ( !m_cFtp.BeginDownload( m_pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, FALSE ) )
		{
			String strError;
			strError.append("导出会议模板操作失败，参数错误！");
			MSG_BOX_OK(strError);
			UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strBtnExportTmp );
			UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strBtnExportScan );
			UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
			return FALSE;
		}
	}
	
	return TRUE;
}

BOOL CTemplateExpLogic::UploadCore()
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtImport, m_pWndTree );
	
	String strSavePath;
	strSavePath = valFolderName.strCaption.c_str();
	
	if ( strSavePath.empty() )
	{
		MSG_BOX_OK("路径不能为空！");	
		
		return FALSE;
	}
	
	m_cFtp.RegisterMsgHandle( WM_UMSTOOL_FTPTEMPLATEPROGRESS );
	
	TLoginInfo tLoginInfo = COMMONMGRIFPTR->GetLoginInfo();
	CString strIpAddr = CUmstoolCommon::GetIpStr( htonl(tLoginInfo.dwIp) );
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	String strWarning;
	if ( !bRet )
	{
		strWarning.append("连接到").append(strIpAddr).append("服务器失败，").append("导入会议模板失败！"); 
		MSG_BOX_OK(strWarning.c_str());
		
		return false;
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFile = TEMPLATE_FILE_PATH;
		strRemoteFile += m_strImpFileName;
		strRemoteFile += ".temp";
		m_cFtp.SetIsRenameTransFile(TRUE);
		if ( !m_cFtp.BeginUpload( m_pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
		{
			String strError;
			strError.append("导入会议模板操作失败，参数错误！");
			MSG_BOX_OK(strError);
			
			return false;
		}
	}
	
	return TRUE;
}

bool CTemplateExpLogic::OnTransTmpProgress( const IArgs & arg  )
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
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strBtnExportTmp );
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strBtnExportScan );

					MSG_BOX_OK("导出会议模板成功！");
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
				}

				if( m_emFtpTransType == em_FTPTRANS_IMPORT )
				{
					//导入成功   修改临时文件为实际文件   避免传输过程中意外终端产生的异常
					String strCurTransRemoteTempFileFullPath;
					String strRemoteFile = TEMPLATE_FILE_PATH;
					strRemoteFile += m_strImpFileName;
					strCurTransRemoteTempFileFullPath = strRemoteFile;
					strCurTransRemoteTempFileFullPath += ".temp";	
					if ( !m_cFtp.RenameFtpFile( strCurTransRemoteTempFileFullPath.c_str(), strRemoteFile.c_str() ) )
					{
						MSG_BOX_OK("导入文件出错，错误原因：重命名文件失败！");
						
						UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
					}
					else
					{
						u16 nRet = COMMONMGRIFPTR->ImportInfoReq(m_strImpFileName.c_str());;
						if ( nRet != NO_ERROR )
						{
							MESSAGEWND( "导入会议模板ums请求发送失败！" );
						}
						else
						{
							MSG_BOX_OK("导入会议模板成功！");
							UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
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
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
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

bool CTemplateExpLogic::OnBtnExportFolder( const IArgs & arg )
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

bool CTemplateExpLogic::OnImpFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmTemplateImpClean", m_pWndTree, m_strProgressImp );
	
	return true;
}

bool CTemplateExpLogic::OnExpFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmTemplateExpClean", m_pWndTree, m_strProgressExp );
	
	return true;
}

HRESULT CTemplateExpLogic::OnExpTemplateRsp( WPARAM wparam, LPARAM lparam)
{
	DownloadCore();

	return S_OK;
}
