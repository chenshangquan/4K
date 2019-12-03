// impcommonLogic.cpp: implementation of the CImpCommonDlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "impcommonLogic.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static UINT     g_nTransTimeID = 0;                   //timer 的id,用于传输超时
static UINT     g_nUpLoadProcess;                     //上传进度
static UINT     g_nUpLoadProcessTimerID;              //timer 的id,用于控制显示时间
static UINT     g_nTftpOpenTimerID;                   //timer 的id,用于Tftp开启后的延迟上传
#define         TIME_UPLOAD        1000               //定时器时间间隔
#define         TIME_TFTP          2000               //TFTP定时器时间间隔
#define         TFTP_UPLOAD_TIMEOUT     30000         //TFTP upload timeout
#define         SET_ALL_CAM_CFG_COUNT   60            //TFTP upload timeout

#define RKC_UPDATEFILE_TYPE        "lpc1837_app"
#define RKC_UPDATEFILE_NAME        "moon904k30.bin"

VOID  CALLBACK  CUploadTimerFun(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{
    if ( idEvent == g_nUpLoadProcessTimerID )
    {
        CString strtmp = _T("");
        if (g_nUpLoadProcess < 90)
        {
            g_nUpLoadProcess += 10;
        }
        CImpCommonDlgLogic::GetSingletonPtr()->UpdateUploadProgress(g_nUpLoadProcess);
    }
    else if (idEvent == g_nTftpOpenTimerID)
    {
        KillTimer( NULL, g_nTftpOpenTimerID );
        g_nTftpOpenTimerID = 0;
        CImpCommonDlgLogic::GetSingletonPtr()->SendUpdateFirst();
    }
}

VOID  CALLBACK  CWaitTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{   
	BOOL bOk = KillTimer( NULL, g_nTransTimeID );	//关掉定时器
#if 0  //FTP
	if ( IMPCOMMONLOGICRPTR->GetFtpStatus() != emFtpEnd )
	{
		if ( IMPCOMMONLOGICRPTR->GetTimeOutCount() >= 5 )
		{
			IMPCOMMONLOGICRPTR->ClearTransFile();
		}
		else
		{
			IMPCOMMONLOGICRPTR->SetTimeOutCount();
		}
	}
#else  //TFTP
    IMPCOMMONLOGICRPTR->ClearTransFile();
#endif
}

VOID  CALLBACK  CWaitFunc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
    BOOL bRet = TRUE;
    MOONLIBDATAMGRPTR->GetCurStatus(bRet);
    if (!bRet)
    {
        BOOL bOk = KillTimer( NULL, g_nTransTimeID );	//关掉定时器
        IMPCOMMONLOGICRPTR->SetAllCamCfgEnd();
    }
    else
    {
        IMPCOMMONLOGICRPTR->SetTimeOutCount();
    }

    //配置文件参数设置，30s超时
    if ( IMPCOMMONLOGICRPTR->GetTimeOutCount() >= SET_ALL_CAM_CFG_COUNT )
    {
        BOOL bOk = KillTimer( NULL, g_nTransTimeID );	//关掉定时器
        IMPCOMMONLOGICRPTR->SetAllCamCfgEnd();
    }
}

CImpCommonDlgLogic::CImpCommonDlgLogic()
:m_strEdtSaveFolder("EdtImpCommonSaveFolder")
,m_strProgressImp("ProgressImpCommon")
,m_strLstUpgradeFile("BoardUpgradeDlg/LstBoardUpgrade")
,m_nCount(0)
{
	m_pWnd = NULL;
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_dwCurSevr = 0;
    m_strTftpFilePath = _T("");

    g_nTransTimeID = 0;
    g_nUpLoadProcess = 0;
    g_nUpLoadProcessTimerID = 0;
    g_nTftpOpenTimerID = 0;
}

CImpCommonDlgLogic::~CImpCommonDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

bool CImpCommonDlgLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	
	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrImpCommonDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}
	
    return true;
}

void CImpCommonDlgLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_MOONTOOL_UPGRADE_IND, CImpCommonDlgLogic::OnCameraUpgradeInd, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );	
	REG_MSG_HANDLER( UI_CAMMECHANISM_UPGRADE_IND, CImpCommonDlgLogic::OnCamMechanismUpgradeInd, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
    REG_MSG_HANDLER( UI_RKC_UPDATE_FIRST_ACK, CImpCommonDlgLogic::OnRkcUpdateFirstAck, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
    REG_MSG_HANDLER( UI_RKC_UPDATE_FIRST_NTY, CImpCommonDlgLogic::OnRkcUpdateFirstNty, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
    REG_MSG_HANDLER( UI_RKC_UPDATE_SECOND_NTY, CImpCommonDlgLogic::OnRkcUpdateSecondNty, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
}

void CImpCommonDlgLogic::UnRegMsg()
{
	
}

void CImpCommonDlgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::InitWnd", CImpCommonDlgLogic::InitWnd, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic);
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnClose", CImpCommonDlgLogic::OnBtnClose, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnoCamCfg", CImpCommonDlgLogic::OnBtnImportCamCfg, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
    REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnImportAllCamInfo", CImpCommonDlgLogic::OnBtnImportAllCamInfo, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnUpgradeMoon", CImpCommonDlgLogic::OnBtnUpgradeMoon, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnUpgradeMechanism", CImpCommonDlgLogic::OnBtnUpgradeMechanism, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_UPLODEPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnUploadProgress", CImpCommonDlgLogic::OnUploadProgress, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnImportScan", CImpCommonDlgLogic::OnBtnImportScan, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnFolderEditChange", CImpCommonDlgLogic::OnFolderEditChange, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
}

void CImpCommonDlgLogic::UnRegFunc()
{
	
}

void CImpCommonDlgLogic::Clear()
{
	BOOL bOk = KillTimer(NULL,g_nTransTimeID);	//关掉定时器
	CleanTransfer();
	
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );

	//打开升级浏览框时断链，切掉此窗口
	HWND hWnd = ::FindWindow(NULL, _T("打开"));
    if(hWnd)
    {
        ::PostMessage(hWnd, WM_CLOSE, 0, 0);
    }

	//预置位导入浏览框
	hWnd = ::FindWindow(NULL, _T("另存为"));
    if(hWnd)
    {
        ::PostMessage(hWnd, WM_CLOSE, 0, 0);
    }	
}

bool CImpCommonDlgLogic::OnBtnClose( const IArgs & arg )
{
	CleanTransfer();
	
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
	
	return true;
}

bool CImpCommonDlgLogic::OnUploadProgress( const IArgs & arg )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);
	
	switch( m_emFileFtpStatus )
	{
	case emFtpBegin:
		{
			m_dwTotalFileSize = static_cast<u32>(msg.lParam);
			
			UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree );
		}
		break;
	case emFtpTransfer:
		{
			m_nCount = 0;
			if ( m_dwTotalFileSize != 0 )
			{
				u32 dwCurrentTransSize = static_cast<u32>(msg.lParam);   //当前传输的大小
				
				float fCurrTransProgress = (float)dwCurrentTransSize/m_dwTotalFileSize*100;
				if ( dwCurrentTransSize < m_dwTotalFileSize )
				{	
					m_valProgress.nPos = (u32)fCurrTransProgress;
					
					UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressImp, m_pWndTree );
				}
			}
		}
		break;
	case emFtpEnd:
		{
			m_nCount = 0;
			BOOL bOk = KillTimer( NULL, g_nTransTimeID );	//关掉定时器
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP接口0为成功  默认失败
			if ( 0 == dwSuccess )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
				
				//导入成功   修改临时文件为实际文件   避免传输过程中意外终端产生的异常
				String strCurTransRemoteTempFileFullPath;
				strCurTransRemoteTempFileFullPath.append(m_strCurTransRemoteFileFullPath).append(".temp");
				if ( !m_cFtp.RenameFtpFile( strCurTransRemoteTempFileFullPath.c_str(), m_strCurTransRemoteFileFullPath.c_str() ) )
				{
					MSG_BOX_OK("导入文件出错，错误原因：重命名文件失败！");
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
				}

				else
				{
					//预置位配置文件导入成功后，添加是否重启弹框提示
					String strCaption;
					UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
					if ( "导入" == strCaption)
					{
						MSG_BOX_OK( "导入预置位列表文件成功！"  );
						u16 nRet = COMIFMGRPTR->CamParamUploadNty(TRUE);
					}
					else if ( "软件升级" == strCaption )
					{
						s8 chVerFileInfo[TP_MAX_FILENAME_LEN + 1] = {0};
						String strPathName = UPDATEFILE_PATH_NAME;
						strPathName += m_strImpFileName;
						strcpy( chVerFileInfo, strPathName.c_str() );
						
						u16 wRe = COMIFMGRPTR->UpgradeMoon(chVerFileInfo);
						if ( wRe != 0 )
						{
							MSG_BOX_OK("升级失败:升级Moon命令发送失败");
						}

						WARNMESSAGE( "升级文件已成功上传" );
						UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonFolderScan", FALSE, m_pWndTree );
						UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonExport", FALSE, m_pWndTree );
						UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonDlgClose", FALSE, m_pWndTree );

					}
					else if( "机芯升级" == strCaption )
					{
						s8 chVerFileInfo[TP_MAX_FILENAME_LEN + 1] = {0};
						String strPathName = UPDATEFILE_PATH_NAME;
						strPathName += m_strImpFileName;
						strcpy( chVerFileInfo, strPathName.c_str() );
						
						u16 wRe = COMIFMGRPTR->UpdateMoonMechanism(chVerFileInfo);
						if ( wRe != 0 )
						{
							MSG_BOX_OK("升级失败:升级H650机芯命令发送失败");
						}
						
						WARNMESSAGE( "机芯升级文件已成功上传" );
						UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonFolderScan", FALSE, m_pWndTree );
						UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonExport", FALSE, m_pWndTree );
						UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonDlgClose", FALSE, m_pWndTree );
					}
					
					
// 		 				if ( "升级T300" == strCaption )
// 						{
// 							BOOL bInConf = LIBDATAMGRPTR->IsInConf();
// 		 					if ( bInConf )
// 		 					{
// 		 						MSG_BOX_OK("升级失败:当前会场正在开会，请稍后再次升级");
// 		 						s32 nResult = 0;
// 		 						UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
// 		 					}
// 		 					else
// 		 					{
// 		 					}
// 						}
				}
	


			}
			else
			{
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				OspPrintf( TRUE, FALSE, "导入文件出错，错误原因：%s！", pszMsg );
				//MSG_BOX_OK(pszMsg);---  连接的时候错误信息空白,暂不提醒
				String strCurTransRemoteTempFileFullPath;
				strCurTransRemoteTempFileFullPath.append(m_strCurTransRemoteFileFullPath).append(".temp");
				m_cFtp.DeleteFile(strCurTransRemoteTempFileFullPath.c_str());
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp  );
				LocalFree( pszMsg );
				String strCaption;    //升级文件上传未成功   也需发消息通知服务器
				UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
				
				if ( "导入" == strCaption )
				{
					u16 nRet = COMIFMGRPTR->CamParamUploadNty(FALSE);		
				}
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

bool CImpCommonDlgLogic::OnBtnImportScan( const IArgs & arg )
{
	String strFile;
	String strCaption;
	String strFilter;
	UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
	if ( "导入摄像机参数" == strCaption )
	{
		strFile = /*CNSCAMERA_FILE_NAME*/"";  //定义一个宏,内容是摄像机文件名
		strFilter = "摄像机配置文件(cameracfg.ini)|cameracfg.ini||";  
	}
	if ( "升级T300" == strCaption )
	{
		strFile = /*CNSUPGRADE_FILE_NAME*/"t300.bin";	//定义一个宏,内容是T300升级文件名,因为有2种,暂不做限制
		strFilter = "t300升级文件(t300.bin;t300.bin.gz)|t300.bin;t300.bin.gz||";
	}

	if ( "软件升级" == strCaption )
	{
		strFile = /*CNSUPGRADE_FILE_NAME*//*"moon90.bin.gz"*/"";	//定义一个宏,内容是T300升级文件名,因为有2种,暂不做限制
		//strFilter = "Moon90升级文件(moon90.bin;moon90.bin.gz)|moon90.bin;moon90.bin.gz||";
        strFilter = "Moon90升级文件(moon904k30.bin)|moon904k30.bin||";
	}

	if( "机芯升级" == strCaption )
	{
		strFile = "";
		strFilter = "H650升级文件(h650_camera.pkg)|h650_camera.pkg||";
	}

	if ( "导入" == strCaption )
	{
		strFile = MOONCAMERA_FILE_NAME;  //定义一个宏,内容是摄像机文件名
		strFilter = "预置位配置文件(mooncfg.ini)|mooncfg.ini||"; 
	}

    if ( "导入参数" == strCaption )
    {
        strFile = MOONCAMERA_FILE_NAME;  //定义一个宏,内容是摄像机文件名
        strFilter = "界面参数配置文件(mooncfg.ini)|mooncfg.ini||"; 
	}
	
	String strImpFileFullPath;
	UIDATAMGR_PTR->OpenFileDialog( strFilter, strFile, strImpFileFullPath, m_strImpFileName );
	if ( !strImpFileFullPath.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtSaveFolder, strImpFileFullPath, m_pWndTree );
	}
	if ( m_strImpFileName.empty() || strImpFileFullPath.empty() )
	{
		return false;
	}

    //软件升级，需打开tftp服务并通知SvrIP及文件大小给对端
    if ( "软件升级" == strCaption )
    {
        OnUpLoadFileFirst();
    }

	//更新添加的文件到文件列表
	UIFACTORYMGR_PTR->SetCaption( "UpgradeDlg/StcUpSerName", m_strImpFileName, m_pWndTree );
	s64 nSize = UIDATAMGR_PTR->GetFileSize(strImpFileFullPath);
	s8 chSize[8] = {0};
	String strSize;
	if ( 1024 > nSize )
	{
		sprintf( chSize, "%u", nSize );
		strSize = chSize;
		strSize += "byte";
	}
	else if ( 1024 < nSize && nSize < 1024*1024 )
	{
		float fSize = 1.0*nSize/1024;
		sprintf( chSize, "%.1f", fSize );
		strSize = chSize;
		strSize += "Kb";
	}
	else if ( 1024*1024 < nSize )
	{
		float fSize = 1.0*nSize/(1024*1024);
		sprintf( chSize, "%.1f", fSize );
		strSize = chSize;
		strSize += "M";
	}
 	UIFACTORYMGR_PTR->SetCaption( "UpgradeDlg/StcUpSerByte", strSize, m_pWndTree );
// 	TUmsToolFile tFileList;
// 	strncpy( tFileList.chFileName, strImpFileName.c_str(), _MAX_FNAME );
// 	strncpy( tFileList.chFileFullPath, strImpFileFullPath.c_str(), MAX_PATH );
// 	tFileList.nFileSize = CUmstoolCommon::GetFileSize(tFileList.chFileFullPath);
// 	if ( tFileList.nFileSize > 0 )
// 	{
// 		m_vecUpgradeFile.push_back(tFileList);
// 		UpdateUpgradeFileList();
// 	}
	
	return true;
}

bool CImpCommonDlgLogic::OnUpLoadFileFirst()
{
    String strImpFileFullPath;
    UIFACTORYMGR_PTR->GetCaption( m_strEdtSaveFolder, strImpFileFullPath, m_pWndTree );
    m_strTftpFilePath = strImpFileFullPath.c_str();
    if (strImpFileFullPath == "")
    {
        MSG_BOX_OK(_T("还没选择文件路径"));
        return false;
    }

    //开启tftp
    MOONSESSION_MGR_PTR->GetSysCtrlIF()->KillTftpProcess();//先关闭TFTP进程
    if (!MOONSESSION_MGR_PTR->GetSysCtrlIF()->OpenTftp())
    {
        MSG_BOX_OK(_T("TFTP服务器开启失败"));
        return false;
    }
    //设置tftp路径
    string strFileDir = strImpFileFullPath;
    int nIndex = strFileDir.find_last_of('\\');
    if (nIndex > 0 && nIndex < strlen(strFileDir.c_str()))
    {
        strFileDir = strFileDir.substr(0, nIndex);
    }
    if (!MOONSESSION_MGR_PTR->GetSysCtrlIF()->SetTftpPath(strFileDir.c_str()))
    {
        MSG_BOX_OK(_T("设置Tftp文件路径失败"));
        return false;
    }

    //禁用浏览、导入
    //UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonFolderScan", FALSE, m_pWndTree );
    UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonExport", FALSE, m_pWndTree );
    g_nTftpOpenTimerID = SetTimer( NULL, 0, TIME_TFTP, CUploadTimerFun );
    return true;
}

void CImpCommonDlgLogic::SendUpdateFirst()
{
    //bin包大小
    unsigned int nFileSize = 0;
    nFileSize = UIDATAMGR_PTR->GetFileSize(m_strTftpFilePath.GetBuffer(0));

    //数据发送
    TRK100TftpFwUpdate tRK100TftpFwUpdate;
    memset(&tRK100TftpFwUpdate, 0, sizeof(TRK100TftpFwUpdate));
    tRK100TftpFwUpdate.dwTftpSvrIp = UIDATAMGR_PTR->GetLocalIP();
    tRK100TftpFwUpdate.dwFileSize = nFileSize;
    strncpy(tRK100TftpFwUpdate.szFwTypeName , RKC_UPDATEFILE_TYPE, sizeof(RKC_UPDATEFILE_TYPE) );
    strncpy(tRK100TftpFwUpdate.szFileFullName , RKC_UPDATEFILE_NAME, sizeof(RKC_UPDATEFILE_NAME) );
    tRK100TftpFwUpdate.byChkSumValid = 0;
    MOONSESSION_MGR_PTR->GetSysCtrlIF()->SetFtpUpdateFirst(tRK100TftpFwUpdate);
}

void CImpCommonDlgLogic::UpdateUploadProgress(u32 dwPos)
{
    float fCurrTransProgress = (float)dwPos/100*100;
    if ( dwPos <= 100 )
    {
        m_valProgress.nPos = (u32)fCurrTransProgress;
        UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressImp, m_pWndTree );
    }
}

HRESULT CImpCommonDlgLogic::OnRkcUpdateFirstAck( WPARAM wparam, LPARAM lparam )
{
    bool bSuccess = (bool)wparam;
    EMRK100OptRtn emErr = (EMRK100OptRtn)lparam;
    if (bSuccess)
    {
    }
    else
    {
        WARNMESSAGE(_T("Tftp first send error."));
    }

    return S_OK;
}

HRESULT CImpCommonDlgLogic::OnRkcUpdateFirstNty( WPARAM wparam, LPARAM lparam )
{
    bool bSuccess = (bool)wparam;
    EMRK100OptRtn emErr = (EMRK100OptRtn)lparam;
    if (bSuccess)
    {
    }
    else
    {
        MOONSESSION_MGR_PTR->GetSysCtrlIF()->KillTftpProcess();
        WARNMESSAGE(_T("UpLoad first message failed."));
    }

    //导入按钮使能
    UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonExport", TRUE, m_pWndTree );
    
    return S_OK;
}

HRESULT CImpCommonDlgLogic::OnRkcUpdateSecondNty( WPARAM wparam, LPARAM lparam )
{
    MOONSESSION_MGR_PTR->GetSysCtrlIF()->KillTftpProcess();

    //关掉定时器
    KillTimer( NULL, g_nTransTimeID );
    KillTimer( NULL, g_nUpLoadProcessTimerID );

    //TFTP上传文件已超时，不再响应此消息
    if ( g_nUpLoadProcess == 0)
    {
        return S_FALSE;
    }

    m_nCount = 0;
    g_nUpLoadProcess = 0;

    bool bSuccess = (bool)wparam;
    EMRK100OptRtn emErr = (EMRK100OptRtn)lparam;
    if (bSuccess)
    {
        //tftp进度条完成上传
        UpdateUploadProgress(100);
        UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
        MSG_BOX_OK( _T("设备升级成功，即将进入重启，请勿断电！") );
        u16 wRet = COMIFMGRPTR->RebootMoon();
        if ( wRet != NO_ERROR )
        {
            WARNMESSAGE( "重启moon90请求发送失败" );
        }
    }
    else
    {
        WARNMESSAGE(_T("UpLoad failed."));
        UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
        UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
    }
    
    return S_OK;
}

bool CImpCommonDlgLogic::OnFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree, m_strProgressImp );
	
	return true;	
}

bool CImpCommonDlgLogic::OnBtnUpgradeMoon( const IArgs & arg )
{
#if 0  //FTP
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();
	
	UploadCore( /*CNSUPGRADE_FILE_PATH*/UPDATEFILE_PATH_NAME, strFileFullPath, /*CNSUPGRADE_FILE_NAME*/m_strImpFileName );  //参数需要重新设置
#else  //TFTP
    UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree );
    //开始定时器 到达时间后关闭窗口
    g_nUpLoadProcess = 0;
    g_nUpLoadProcessTimerID = SetTimer( NULL, 0, TIME_UPLOAD, CUploadTimerFun );
    //开始上传
    MOONSESSION_MGR_PTR->GetSysCtrlIF()->SetFtpUpdateSecond();
    //TFTP upload timeout
    g_nTransTimeID = SetTimer( NULL, 0, TFTP_UPLOAD_TIMEOUT, CWaitTimerFun );
#endif
	return true;
}

bool CImpCommonDlgLogic::OnBtnUpgradeMechanism(const IArgs & arg)
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();
	
	UploadCore( /*CNSUPGRADE_FILE_PATH*/UPDATEFILE_PATH_NAME, strFileFullPath, /*CNSUPGRADE_FILE_NAME*/m_strImpFileName );  //参数需要重新设置

	return true;
}

BOOL CImpCommonDlgLogic::UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bIsDefServ /*= TRUE */ )
{
	if ( !UIDATAMGR_PTR->IsFileExist( strLocalFile.c_str() ) )
	{
		MSG_BOX_OK("指定文件不存在，无法导入!");
		return false;
	}
	
	if ( !UIDATAMGR_PTR->CheckTransferFile( strLocalFile, strCheckFileName ) )
	{
		return false;
	}
	
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_UPLODEPROGRESS );
	
	CString strIpAddr;
	if ( bIsDefServ )
	{
		u32 dwIp;
		MOONLIBDATAMGRPTR->GetLoginIp(dwIp);
		strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );
	}
	else
	{
		strIpAddr = UIDATAMGR_PTR->GetIpStr( GetSevrIpAddr() );
	}
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, MT_TEL_USRNAME, MT_TEL_PWD );
	if ( !bRet )
	{
		MSG_BOX_OK("连接服务器失败!");
		
		return false;
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFilePath = strRemotePath;
		strRemoteFilePath += strCheckFileName;
		m_strCurTransRemoteFileFullPath = strRemoteFilePath;
		strRemoteFilePath += ".temp";
		m_cFtp.SetIsRenameTransFile(TRUE);
		if ( !m_cFtp.BeginUpload( m_pWnd->GetSafeHwnd(), strRemoteFilePath.c_str(), strLocalFile.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
		{
			MSG_BOX_OK("导入操作失败!");
			
			return false;
		}
		//设置定时器 时间间隔30s
		m_nCount = 0;
		g_nTransTimeID = SetTimer( NULL, 0, 10000, CWaitTimerFun );
	}
	
	return TRUE;
}

void CImpCommonDlgLogic::CleanTransfer()
{
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}

    String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
    if ( "软件升级" == strCaption )
    {
        MOONSESSION_MGR_PTR->GetSysCtrlIF()->KillTftpProcess();
    }

    //关掉定时器
    KillTimer( NULL, g_nTransTimeID );
    KillTimer( NULL, g_nUpLoadProcessTimerID );
    
    m_nCount = 0;
    g_nUpLoadProcess = 0;
	
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_dwCurSevr = 0;
	
	m_strCurTransRemoteFileFullPath = "";
	m_strImpFileName = "";
	//UpdateUpgradeFileList();
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree );
}
// 
// void CImpCommonDlgLogic::UpdateUpgradeFileList()
// {
// 	if ( NULL == m_pWndTree  )
// 	{
// 		return;
// 	}
// 	
// 	Value_ItemBoardUpgrade itemBoardUpgrade( &m_vecUpgradeFile );
// 	UIFACTORYMGR_PTR->SetPropertyValue( itemBoardUpgrade, m_strLstUpgradeFile, m_pWndTree );
// }

bool CImpCommonDlgLogic::OnBtnImportCamCfg( const IArgs & arg )
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );

	if ( "导入" == strCaption )
	{
		u16 nRet = COMIFMGRPTR->CamParamUploadCmd();		
	}
	
	UploadCore( MOONCAMERA_FILE_PATH, strFileFullPath, MOONCAMERA_FILE_NAME );
	
	return true;
}

bool CImpCommonDlgLogic::OnBtnImportAllCamInfo( const IArgs & arg )
{
    Value_WindowCaption valFolderName;
    UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
    
    String strFileFullPath;
    strFileFullPath = valFolderName.strCaption.c_str();
    
    m_dwTotalFileSize = 3*sizeof(TTPMoonCamInfo);
    UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree );
    ReadFromCfgFile(strFileFullPath);

    return true;
}

void CImpCommonDlgLogic::ClearTransFile()
{
#if 0  //FTP
	if ( m_cFtp.GetIsRenameTransFile() && m_emFileFtpStatus == emFtpTransfer )
	{
		String strCurTransRemoteTempFileFullPath;
		strCurTransRemoteTempFileFullPath.append(m_strCurTransRemoteFileFullPath).append(".temp");
		m_cFtp.DeleteFile(strCurTransRemoteTempFileFullPath.c_str());
	}
	m_nCount = 0;
	KillTimer( NULL, g_nTransTimeID );	//关掉定时器	
	MSG_BOX_OK("导入文件出错，错误原因：超时");
	UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
	m_cFtp.EndFtpFile();
#else  //TFTP
    KillTimer( NULL, g_nTransTimeID );	//关掉定时器
    KillTimer( NULL, g_nUpLoadProcessTimerID );
    m_nCount = 0;
    g_nUpLoadProcess = 0;
	MSG_BOX_OK("导入文件出错，错误原因：超时");
    UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree );
    UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
#endif
}

HRESULT CImpCommonDlgLogic::OnCameraUpgradeInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bOk = static_cast<BOOL>(lparam);

	if ( bOk )
	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "升级文件已导入，需要重启才能生效，是否立即重启？" );	
		
		if ( MSGBOX_OK == nMsgBoxRet )
		{
			u16 wRet = COMIFMGRPTR->RebootMoon();
			if ( wRet != NO_ERROR )
			{
				WARNMESSAGE( "重启moon90请求发送失败" );
			}
		}
		if ( MSGBOX_CANCEL == nMsgBoxRet )
		{
			UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonFolderScan", TRUE, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonExport", TRUE, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonDlgClose", TRUE, m_pWndTree );
		}
	}
	else
	{
		WARNMESSAGE( "升级文件已成功上传，但解压失败，请稍后重试！" );	
		UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonFolderScan", TRUE, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonExport", TRUE, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonDlgClose", TRUE, m_pWndTree );
	}

	return S_OK;
}

HRESULT CImpCommonDlgLogic::OnCamMechanismUpgradeInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bOk = static_cast<BOOL>(lparam);

	if( bOk )
	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "机芯升级文件已导入，需要重启才能生效，是否立即重启？" );

		if ( MSGBOX_OK == nMsgBoxRet )
		{
			u16 wRet = COMIFMGRPTR->RebootMoon();
			if ( wRet != NO_ERROR )
			{
				WARNMESSAGE( "重启moon90请求发送失败" );
			}
		}
		if ( MSGBOX_CANCEL == nMsgBoxRet )
		{
			UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonFolderScan", TRUE, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonExport", TRUE, m_pWndTree );
			UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonDlgClose", TRUE, m_pWndTree );
		}
	}
	else
	{
		WARNMESSAGE( "机芯升级文件已成功上传，但解压失败，请稍后重试！" );	
		UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonFolderScan", TRUE, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonExport", TRUE, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonDlgClose", TRUE, m_pWndTree );
	}

	return S_OK;
}

void CImpCommonDlgLogic::SetTimeOutCount()
{
	m_nCount ++;
}

u32 CImpCommonDlgLogic::GetTimeOutCount()
{
	return m_nCount;
}

void HexStrToByte(const char* source, unsigned char* dest, int sourceLen)
{
    short i;
    unsigned char highByte, lowByte;
    
    for (i = 0; i < sourceLen; i += 2)
    {
        highByte = toupper(source[i]);
        lowByte = toupper(source[i + 1]);
        
        if (highByte > 0x39)
            highByte -= 0x37;
        else
            highByte -= 0x30;
        
        if (lowByte > 0x39)
            lowByte -= 0x37;
        else
            lowByte -= 0x30;
        
        dest[i / 2] = (highByte << 4) | lowByte;
    }
    return;
}

void CImpCommonDlgLogic::ReadFromCfgFile(String strPath)
{
    if ( !UIDATAMGR_PTR->IsFileExist( strPath.c_str() ) )
    {
        MSG_BOX_OK("指定文件不存在，无法导入!");
        UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree );
        return;
    }
    
    if ( !UIDATAMGR_PTR->CheckTransferFile( strPath, MOONCAMERA_FILE_NAME ) )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree );
        return;
	}

    TTPMoonCamInfo tCamInfo[3] = {0};
    String strCamID = _T("");
    u32 dwReadSize = 0;
    BOOL bRet = FALSE;
    s8 achNum[8] = {0};
    s8 achBuffer[2*sizeof(TTPMoonCamInfo)+1] = {0};
    
    for (u8 byIndex = 0; byIndex < 3; byIndex++)
    {
        strCamID = _T("Camera");
        ZeroMemory(achBuffer, 2*sizeof(TTPMoonCamInfo)+1);

        itoa(byIndex+1, achNum, 10);
        strCamID += achNum;
        GetPrivateProfileString(strCamID.c_str(), "Param", "", achBuffer, 2*sizeof(TTPMoonCamInfo), strPath.c_str());
        if (strlen(achBuffer) != 0)
        {
            HexStrToByte(achBuffer, (u8*)&tCamInfo[byIndex], strlen(achBuffer));
            dwReadSize += sizeof(TTPMoonCamInfo);
            bRet = ReadProgressPos(dwReadSize);
        }
    }

    if (!bRet)
    {
        MSG_BOX_OK("导入文件异常，非所有参数均正确导入！");
        UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
        UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
    }
    else
    {
        MSG_BOX_OK( "导入配置文件成功！当前摄像机参数将被重置"  );
        MOONLIBDATAMGRPTR->SetAllCamCfg(tCamInfo);
        m_nCount = 0;
        g_nTransTimeID = SetTimer( NULL, 0, 500, CWaitFunc );
    }
}

void CImpCommonDlgLogic::SetAllCamCfgEnd()
{
    UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
    if ( m_nCount >= SET_ALL_CAM_CFG_COUNT )
    {
        MSG_BOX_OK( "摄像机参数设置超时，请检查配置文件是否异常！" );
    }
    else
    {
        MSG_BOX_OK( "摄像机参数已被重置！" );
    }

    m_nCount = 0;
}

BOOL CImpCommonDlgLogic::ReadProgressPos(u32 dwReadSize)
{
    if ( m_dwTotalFileSize != 0 )
    {   
        float fCurrTransProgress = (float)dwReadSize/m_dwTotalFileSize*100;
        if ( dwReadSize <= m_dwTotalFileSize )
        {	
            m_valProgress.nPos = (u32)fCurrTransProgress;
            UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressImp, m_pWndTree );
        }

        if ( dwReadSize == m_dwTotalFileSize )
        {
            return TRUE;
        }
    }

    return FALSE;
}