// recordOptDlg.cpp: implementation of the RecordOptDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "recordOptDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RecordOptDlg::RecordOptDlg()
:m_StrStartingSch("SchStartStatistics")
,m_StrEndingSch("SchEndOfStatistics")
,m_StrCleanSch("SchClean")
,m_StrForder("StatisticOptDlg/EditOfStoreDirectory")
,m_StrFileName("StatisticOptDlg/EditOfFileName")
,m_bIsRecording(false)
{

}

RecordOptDlg::~RecordOptDlg()
{

}

void RecordOptDlg::RegCBFun()
{
	RecordOptDlg *pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "RecordOptDlg::InitWnd", RecordOptDlg::InitWnd, pThis, RecordOptDlg);

	REG_GOBAL_MEMBER_FUNC( "RecordOptDlg::OnBtnClose", RecordOptDlg::OnBtnClose, pThis, RecordOptDlg);
	REG_GOBAL_MEMBER_FUNC( "RecordOptDlg::OnBtnScan", RecordOptDlg::OnBtnScan, pThis, RecordOptDlg);
	REG_GOBAL_MEMBER_FUNC( "RecordOptDlg::OnOpenFolder", RecordOptDlg::OnOpenFolder, pThis, RecordOptDlg);
	REG_GOBAL_MEMBER_FUNC( "RecordOptDlg::OnBtnSave", RecordOptDlg::OnBtnSave, pThis, RecordOptDlg);

}

void RecordOptDlg::RegMsg()
{
	RecordOptDlg *pThis =  GetSingletonPtr(); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_Statistic_Nty, RecordOptDlg::OnInterfaceSelection, pThis, RecordOptDlg );
	
}

void RecordOptDlg::UnRegFunc()
{
	
}

void RecordOptDlg::UnRegMsg()
{
	
}

bool RecordOptDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	UIFACTORYMGR_PTR->LoadScheme( m_StrStartingSch, m_pWndTree );
	return true;
}

void RecordOptDlg::Clear()
{
	if ( m_bIsRecording == true )
	{
		if ( m_cFile.m_hFile != (UINT)INVALID_HANDLE_VALUE )
		{
			m_cFile.Close();
		}
		m_bIsRecording = false;
	}
	UIFACTORYMGR_PTR->Endmodal(0, g_strDiagStatistic );
}

bool RecordOptDlg::OnBtnClose( const IArgs & arg )
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_strDiagStatistic );
	
	return true;
}

bool RecordOptDlg::OnBtnScan( const IArgs & arg )
{	
	String strFile;
	String strFolder;
	String strFileName;
	
	strFile += CNSSTATISTIC_FILE_NAME;
	strFolder = UIDATAMGR_PTR->OpenBrowseForFolder(strFile,NULL,FALSE);
	//	memset(chFileFolder,0,sizeof(chFileFolder));
	//	strFilter += "存储文件(*.txt)|*.txt||";
	//	UIDATAMGR_PTR->OpenFileDialog( strFilter, strFile, strFileFullPath, m_strFileName);
	if ( !strFolder.empty() )
	{
		//		byFolderLen = strFileFullPath.size()-m_strFileName.size();
		//		memcpy(chFileFolder,strFileFullPath.c_str(),byFolderLen);
		UIFACTORYMGR_PTR->SetCaption( m_StrForder, strFolder, m_pWndTree);
		
		UIFACTORYMGR_PTR->GetCaption(m_StrFileName,strFileName,m_pWndTree);
		if ( strFileName.size() == 0 )
		{
			strFileName = strFile;
		}
		
		String strFileFullPath;
		CString cstrNewFileName;
		
		strFileFullPath = strFolder+ strFileName;
		
		if ( UIDATAMGR_PTR->IsFileExist( strFileFullPath.c_str() ) )
		{
			cstrNewFileName = getNewFileName( strFolder , strFileName ) ;
		}
		else
		{
			cstrNewFileName = strFileName.c_str();
		}
		
		UIFACTORYMGR_PTR->SetCaption(m_StrFileName,cstrNewFileName.GetBuffer(cstrNewFileName.GetLength()-1),m_pWndTree);
		
		return true;
	}
	else
	{
		return false;
	}
}

bool RecordOptDlg::OnOpenFolder( const IArgs & arg )
{
	String strFileName;
	String strFileFullPath;
	
	UIFACTORYMGR_PTR->GetCaption( m_StrForder, strFileFullPath, m_pWndTree);
	UIFACTORYMGR_PTR->GetCaption( m_StrFileName, strFileName, m_pWndTree);
	
	strFileFullPath+=strFileName;
	
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

bool RecordOptDlg::OnBtnSave( const IArgs & arg )
{
	String  strFolder;
	String  strFileName;
	string  strFilePath;
	s32 nResult = 0;

/*	if ( m_emStatistics != EM_START_STATISTICS )
	{
		return false;
	}
*/
	UIFACTORYMGR_PTR->GetCaption( m_StrFileName, strFileName, m_pWndTree);
	UIFACTORYMGR_PTR->GetCaption( m_StrForder, strFolder, m_pWndTree);

	if ( strFileName.empty() || strFolder.empty() )
	{
		MSG_BOX_OK("文件路径无效");
		return false;
	}
	
/*	if ( UIDATAMGR_PTR->IsIniFile( strFileName ) == FALSE )
	{
		MSG_BOX_OK("文件类型必须为.ini文件");
	}*/

	if ( UIDATAMGR_PTR->IsFolderExist(strFolder.c_str()) == FALSE )
	{
		MSG_BOX_OK("文件夹不存在");
		return false;
	}

	strFilePath = strFolder + strFileName;
	if ( UIDATAMGR_PTR->IsFileExist(strFilePath.c_str()) == TRUE )
	{
		CFile cFile;
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "同名文件已存在,是否替换？" );
		if ( MSGBOX_OK == nMsgBoxRet )
		{
			cFile.Remove(strFilePath.c_str());
			m_cFile.Open(strFilePath.c_str(), CFile::modeCreate|CFile::modeWrite);

			if ( m_cFile.m_hFile == (UINT)INVALID_HANDLE_VALUE )
			{
				MSG_BOX_OK("文件创建失败");
				return false;
			}
		}
		else if ( MSGBOX_CANCEL == nMsgBoxRet )
		{
			CString cStrNewFileName = getNewFileName( strFolder,strFileName );

			UIFACTORYMGR_PTR->SetCaption(m_StrFileName,cStrNewFileName.GetBuffer(cStrNewFileName.GetLength()-1),m_pWndTree );

			strFilePath = strFolder + cStrNewFileName.GetBuffer(cStrNewFileName.GetLength()-1);
	
			m_cFile.Open(strFilePath.c_str(), CFile::modeCreate|CFile::modeWrite);

			if ( m_cFile.m_hFile == (UINT)INVALID_HANDLE_VALUE )
			{
				MSG_BOX_OK("文件打开失败");
				return false;
			}
		}
	}
	else
	{
		m_cFile.Open(strFilePath.c_str(), CFile::modeCreate|CFile::modeWrite);
		if ( m_cFile.m_hFile == (UINT)INVALID_HANDLE_VALUE )
		{
			MSG_BOX_OK("文件创建失败");
			return false;
		}
	}

	m_bIsRecording = true;
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_StartRecorder_Nty, (WPARAM)&m_cFile,NULL);
	UIFACTORYMGR_PTR->Endmodal(nResult, g_strDiagStatistic );
	return true;
}

HRESULT RecordOptDlg::OnInterfaceSelection( WPARAM wparam, LPARAM lparam )
{
	BOOL bRecording = FALSE;
	bRecording = *(BOOL*)wparam;

	if ( bRecording == FALSE )
	{
		UIFACTORYMGR_PTR->LoadScheme( m_StrStartingSch, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( m_StrCleanSch, m_pWndTree );
	}
	else
	{
		if ( m_cFile.m_hFile != (UINT)INVALID_HANDLE_VALUE )
		{
			m_cFile.Close();
		}
		m_bIsRecording = false;
		UIFACTORYMGR_PTR->LoadScheme( m_StrEndingSch, m_pWndTree );
	}
	return S_OK;
}

CString RecordOptDlg::getNewFileName( string strFolder , string strFileName )
{
	s32 nINdex = 1;			
	s8 chFile[8];

	CString CStrFile( strFileName.c_str() );
	CString CStrFilePath = "";
	CString cstrFileLeft;

	int nFind = CStrFile.ReverseFind( '.' );
	if ( nFind == -1 )
	{
		return "";
	}

	cstrFileLeft = CStrFile.Left( nFind );

	s32 nReFind = CStrFile.ReverseFind( ')' );
	if ( nReFind != -1 )
	{
		nReFind = CStrFile.ReverseFind( '(' );

		if ( nReFind  != -1 )
		{
			cstrFileLeft = CStrFile.Left( nReFind );
		}
	}

	CString cstrFileRight = CStrFile.Right(CStrFile.GetLength() -nFind );
	CString cstrFileTemp = "";

	memset(chFile,0,sizeof(chFile));
	sprintf(chFile,"(%d)",nINdex);
	cstrFileTemp = cstrFileLeft + chFile;
	cstrFileTemp += cstrFileRight;
	CStrFilePath = strFolder.c_str();
	CStrFilePath += cstrFileTemp ;

	while( UIDATAMGR_PTR->IsFileExist( CStrFilePath ) == TRUE )
	{
		nINdex ++;

		memset(chFile,0,sizeof(chFile));
		sprintf(chFile,"(%d)",nINdex);

		cstrFileTemp = cstrFileLeft + chFile;
		cstrFileTemp += cstrFileRight;

		CStrFilePath = strFolder.c_str();
		CStrFilePath += cstrFileTemp;
	}

	return cstrFileTemp;
}