// NetPacketLogic.cpp: implementation of the CNetPacketLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "NetPacketLogic.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static UINT g_nCaptureTime = 0;

VOID CALLBACK OnStartTimer( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
	CNETPACKETLOGIC->UpdateCaptureData();
}

CNetPacketLogic::CNetPacketLogic()
:m_strBtnStartPacket("BtnOfPacket")
,m_strBtnCaptureExport("BtnofExport")
,m_strCaptureTimer("StcCaptureTimer")
,m_strCaptureFileSize("StcCaptureFileSize")
,m_strExportProgress("ProgressExp")
{
	m_pWnd = NULL;
	m_emFileFtpStatus = emFtpEnd;
	m_valProgress.nPos = 0;
	m_dwTime = 0;
	m_dwCaptureFileSize = 0;
	m_dwTotalFileSize = 0;
	m_bIsCapturing = FALSE;
	m_bIsExporting = FALSE;
	m_nThreeCount = 0;
	m_bIsClickBtnPacket = FALSE;
	m_bIsClickBtnExport = FALSE;
}

CNetPacketLogic::~CNetPacketLogic()
{	
}

void CNetPacketLogic::RegCBFun()
{
	CNetPacketLogic *pThis =  GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CNetPacketLogic::InitWnd", CNetPacketLogic::InitWnd, pThis, CNetPacketLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetPacketLogic::OnBtnPacket", CNetPacketLogic::OnBtnPacket, pThis, CNetPacketLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetPacketLogic::OnBtnExport", CNetPacketLogic::OnBtnExport, pThis, CNetPacketLogic );

	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_FTPCAPTUREPROGRESS );
	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_CAPTUREMAXSIZE );
	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_CAPTUREFAIL );
	REG_GOBAL_MEMBER_FUNC( "CNetPacketLogic::OnExportProgress", CNetPacketLogic::OnExportProgress, pThis, CNetPacketLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CNetPacketLogic::OnCaptureMaxSize", CNetPacketLogic::OnCaptureMaxSize, pThis, CNetPacketLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CNetPacketLogic::OnCaptureFail", CNetPacketLogic::OnCaptureFail, pThis, CNetPacketLogic );
}

void CNetPacketLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CNetPacketLogic::InitWnd" );
}

bool CNetPacketLogic::InitWnd(const IArgs & arg)
{
	CLogicBase::InitWnd( arg );
	UIFACTORYMGR_PTR->LoadScheme( "SchStartPacket", m_pWndTree);

	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_strNetPacketDlg );
	if ( NULL == m_pWnd )
	{
		return false;
	}

	return true;
}

void CNetPacketLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchStartPacket", m_pWndTree);
	}

	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}

	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	UIFACTORYMGR_PTR->LoadScheme( "SchmCaptureExpClean", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strCaptureFileSize, "文件大小: 0M", m_pWndTree );

	m_bIsClickBtnPacket = FALSE;
	m_bIsClickBtnExport = FALSE;
}

void CNetPacketLogic::RegMsg()
{
	CNetPacketLogic *pThis =  GetSingletonPtr(); 	
	REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CNetPacketLogic::OnDisConnect, pThis, CNetPacketLogic );
 
    REG_MSG_HANDLER( UI_SETFTPINFO_Rsp, CNetPacketLogic::OnSetFtpInfoRsp, pThis, CNetPacketLogic );
    REG_MSG_HANDLER( UI_SETTELNETINFO_Rsp, CNetPacketLogic::OnSetTelnetInfoRsp, pThis, CNetPacketLogic );
}

void CNetPacketLogic::UnRegMsg()
{
	
}

bool CNetPacketLogic::OnBtnPacket(const IArgs & arg)
{
	if(!m_bIsCapturing)
	{
		//判断ftp、telnet是否开启
		TTPFtpInfo tTPFtpInfo;
        LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );

		TTPTelnetInfo tTPTelnetInfo;
	    LIBDATAMGRPTR->GetTelnetInfo(tTPTelnetInfo);

		if (!tTPFtpInfo.bOpen || !tTPTelnetInfo.bOpen)
		{
			//增加提示
			MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
			MSG_BOX( nMsgBoxRet, "开始抓包，需开启FTP和telnet服务，请确认是否开启？" );	
			if ( nMsgBoxRet != MSGBOX_OK )
			{
				return false;		 
			}

			if (!tTPFtpInfo.bOpen)
			{
				tTPFtpInfo.bOpen = TRUE;
				u16 wRet = COMIFMGRPTR->SetFtpInfoRsq(tTPFtpInfo);
				
				if( wRet != NO_ERROR)
				{
					WARNMESSAGE("FTP服务请求设置失败");
					return false;
				}
			}

			if (!tTPTelnetInfo.bOpen)
			{
				tTPTelnetInfo.bOpen = TRUE;
				u16 wRet1 = COMIFMGRPTR->SetTelInfoRsp(tTPTelnetInfo);
				
				if( wRet1 != NO_ERROR )
				{
					WARNMESSAGE("TELNET服务请求设置失败");
					return false;
				}
			}

			m_bIsClickBtnPacket = TRUE;
		}
		else
		{
			StartCapture();
		}  
	}
	else
	{
		BtnStopCapture();
	}	
	
	return S_OK;
}

bool CNetPacketLogic::OnBtnExport(const IArgs & arg)
{
	TTPFtpInfo tTPFtpInfo;
    LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
	if (!tTPFtpInfo.bOpen)
	{
		//增加提示
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "导出抓包，需开启FTP服务，请确认是否开启？" );	
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
		m_bIsClickBtnExport = TRUE;
	}
	else
	{
		ExportPacket();
	}
   
	return S_OK;
}

void CNetPacketLogic::BtnStartCapture()
{
	m_bIsCapturing = TRUE;
	if(NULL == m_cTelnet)
	{
		m_bIsCapturing = FALSE;
		return;
	}
	if (m_cFtp.FindfFtpFile(CNSCAPTURE_FILE_PATH, CAPTURE_FILE_NAME))
	{
		m_cFtp.DeleteFile(REMOTE_FILE_NAME);							
	}

	TLoginInfo tInfo;
	LIBDATAMGRPTR->GetLoginIp(tInfo.dwIp);
	m_cTelnet.SetLoginInfo(tInfo);

	if(m_cTelnet.Create())
	{
		m_cTelnet.AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT | FD_OOB);
		m_cTelnet.ConnectRemote();
	}
	else
	{
		m_cTelnet.Close();
		m_bIsCapturing = FALSE;
	}

	u16 wRet = COMIFMGRPTR->SetCaptureStateCmd(m_bIsCapturing);
	
	if(NO_ERROR != wRet)
	{
		WARNMESSAGE("是否正在操作抓包消息发送失败！");
	}

	Value_WindowEnable valEnableBtn;
	valEnableBtn.bEnable = false;
	UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, "BtnofExport", m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme( "SchEndPacket", m_pWndTree);
	m_dwTime = 0;
	g_nCaptureTime = SetTimer(NULL, 1, 1000, OnStartTimer);

	return;
}

void CNetPacketLogic::StartExportFile()
{
	s8 szCurrentDirectory[EXPORT_FILE_NAME_LENGTH] = {0};
	GetCurrentDirectory(EXPORT_FILE_NAME_LENGTH, szCurrentDirectory);
	CFileDialog fOpenDlg(FALSE, ".pcap", "kdvcapture.pcap", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, ".pcap Files(*.pcap)|*.pcap||");
	if (IDOK != fOpenDlg.DoModal())
	{
		return ;
	}
	SetCurrentDirectory(szCurrentDirectory);
	// 获取文件名和文件路径
	CString strFileName = fOpenDlg.GetFileName();
	CString strSaveFilePath = fOpenDlg.GetPathName();
	
	if (0 == strlen(strFileName)
		|| 0 == strlen(strSaveFilePath))
	{
		MSG_BOX_OK("路径不能为空！");
		return ;
	}

	m_cFtp.RegisterMsgHandle(WM_CNSTOOL_FTPCAPTUREPROGRESS);
	if ( !m_cFtp.BeginDownload(m_pWnd->GetSafeHwnd(), REMOTE_FILE_NAME, strSaveFilePath,
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT , FALSE) )
	{
		MSG_BOX_OK("导出抓包文件操作失败，参数错误！");
		return ;
	}

	m_bIsExporting = TRUE;
	u16 wRet = COMIFMGRPTR->SetCaptureStateCmd(m_bIsExporting);
	
	if(NO_ERROR != wRet)
	{
		WARNMESSAGE("是否正在操作抓包消息发送失败！");
	}
	Value_WindowEnable valEnableBtn;
	valEnableBtn.bEnable = false;
	UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, "BtnOfPacket", m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme( "SchmExportbtnBeg", m_pWndTree, m_strBtnCaptureExport);
	return;
}

void CNetPacketLogic::UpdateCaptureData()
{
	u16 dwMinute = 0;
	u16 dwSecend = 0;
	s8 chMinute[4];
	s8 chSecend[4];
	s8 chFileSize[40];
	s8 chDate[STC_CAPTURE_MES];	
	s8 chfilesize[STC_CAPTURE_MES];
	
	memset(chMinute, 0, sizeof(chMinute));
	memset(chSecend, 0, sizeof(chSecend));
	memset(chFileSize, 0, sizeof(chFileSize));
	memset(chDate, 0, sizeof(chDate));
	memset(chfilesize, 0, sizeof(chfilesize));

	m_nThreeCount++;
	if( m_nThreeCount%3 == 0 )
	{
		IsCaptureSuccess();
	}

	m_dwTime++;
	dwMinute = m_dwTime/60;
	dwSecend = m_dwTime%60;
	if(dwMinute < 60)
	{		
		if ( dwMinute < 10 )
		{
			sprintf( chMinute, "0%u",dwMinute);
		}
		else
		{
			sprintf( chMinute, "%u",dwMinute);
		}
		
		if ( dwSecend < 10 )
		{
			sprintf( chSecend, "0%u",dwSecend);
		}
		else
		{
			sprintf( chSecend, "%u",dwSecend);
		}
	}
	else
	{
		m_dwTime = 0;
		sprintf( chMinute, "0%u", 0);
		sprintf( chSecend, "0%u", 0);
	}

	m_cFtp.SetRemoteFileName( REMOTE_FILE_NAME );
	m_dwCaptureFileSize = m_cFtp.GetRemoteFileSize();
	GetFileSize( m_dwCaptureFileSize, chFileSize );

	if( m_dwCaptureFileSize > CAPTURE_FILE_MAX_SIZE)
	{
		::PostMessage(m_pWnd->GetSafeHwnd(), WM_CNSTOOL_CAPTUREMAXSIZE, 0, 0);
		return ;
	}

	sprintf( chDate, "时间:%s:%s", chMinute, chSecend );
	sprintf( chfilesize, "文件大小:%s", chFileSize);
	UIFACTORYMGR_PTR->SetCaption( m_strCaptureTimer, chDate, m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strCaptureFileSize, chfilesize, m_pWndTree );

	return;
}

void CNetPacketLogic::IsCaptureSuccess()
{
	u32 dwIp = 0;
	TLoginInfo tInfo;
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
	
	if(!m_cFtp.ConnectServer())
	{
		::PostMessage(m_pWnd->GetSafeHwnd(), WM_CNSTOOL_CAPTUREFAIL, 0, 0);
		m_nThreeCount = 0;
		return;
	}
	
	if (!m_cFtp.FindfFtpFile(CNSCAPTURE_FILE_PATH, CAPTURE_FILE_NAME))
	{
		::PostMessage(m_pWnd->GetSafeHwnd(), WM_CNSTOOL_CAPTUREFAIL, 0, 0);
		m_nThreeCount = 0;
		return;
	}

	return;
}

void CNetPacketLogic::BtnStopCapture()
{
	s8 chFileSize[40];
	s8 chfilesize[STC_CAPTURE_MES];
	memset(chFileSize, 0, sizeof(chFileSize));
	memset(chfilesize, 0, sizeof(chfilesize));
	m_bIsCapturing = FALSE;
	m_nThreeCount = 0;
	m_cTelnet.Close();
	KillTimer(NULL, g_nCaptureTime);
	m_cFtp.SetRemoteFileName(REMOTE_FILE_NAME);
	m_dwCaptureFileSize = m_cFtp.GetRemoteFileSize();
	GetFileSize(m_dwCaptureFileSize, chFileSize);
	sprintf( chfilesize, "文件大小:%s", chFileSize);
	u16 wRet = COMIFMGRPTR->SetCaptureStateCmd(m_bIsCapturing);
	
	if(NO_ERROR != wRet)
	{
		WARNMESSAGE("是否正在操作抓包消息发送失败！");
	}
	Value_WindowEnable valEnableBtn;
	valEnableBtn.bEnable = true;
	UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, "BtnofExport", m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme( "SchStartPacket", m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strCaptureFileSize, chfilesize, m_pWndTree);
}

bool CNetPacketLogic::OnCaptureMaxSize(const IArgs & arg)
{
	s8 chFileSize[40];
	s8 chfilesize[STC_CAPTURE_MES];
	memset(chFileSize, 0, sizeof(chFileSize));
	memset(chfilesize, 0, sizeof(chfilesize));
	m_bIsCapturing = FALSE;
	u16 wRet = COMIFMGRPTR->SetCaptureStateCmd(m_bIsCapturing);
	
	if(NO_ERROR != wRet)
	{
		WARNMESSAGE("是否正在操作抓包消息发送失败！");
	}
	m_cTelnet.Close();
	KillTimer(NULL, g_nCaptureTime);
	m_cFtp.SetRemoteFileName(REMOTE_FILE_NAME);
	m_dwCaptureFileSize = m_cFtp.GetRemoteFileSize();
	GetFileSize(m_dwCaptureFileSize, chFileSize);
	sprintf( chfilesize, "文件大小:%s", chFileSize);
	Value_WindowEnable valEnableBtn;
	valEnableBtn.bEnable = true;
	UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, "BtnofExport", m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme( "SchStartPacket", m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strCaptureFileSize, chfilesize, m_pWndTree);
	
	return true;
}

bool CNetPacketLogic::OnCaptureFail(const IArgs & arg)
{
	m_bIsCapturing = FALSE;
	u16 wRet = COMIFMGRPTR->SetCaptureStateCmd(m_bIsExporting);
	
	if(NO_ERROR != wRet)
	{
		WARNMESSAGE("是否正在操作抓包消息发送失败！");
	}

	m_cTelnet.Close();
	KillTimer(NULL, g_nCaptureTime);
	Value_WindowEnable valEnableBtn;
	valEnableBtn.bEnable = true;
	UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, "BtnofExport", m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption( m_strCaptureTimer, "时间:00:00", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strCaptureFileSize, "文件大小: 0M", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchStartPacket", m_pWndTree);

	return S_OK;
}

void CNetPacketLogic::GetFileSize(u32 m_dwCaptureFileSize, s8 *chFileSize)
{
	float fFileSizeNumber;
	
	if ( m_dwCaptureFileSize < MBIT_SIZE )
	{
		fFileSizeNumber = m_dwCaptureFileSize*1.0/( KBIT_SIZE );
 		sprintf(chFileSize, " %.2f KB", fFileSizeNumber);
	}
	else if ( m_dwCaptureFileSize< GBIT_SIZE )
	{
		fFileSizeNumber = m_dwCaptureFileSize*1.0/( MBIT_SIZE );
		sprintf(chFileSize, " %.2f MB", fFileSizeNumber);
	}
	else 
	{
		fFileSizeNumber = m_dwCaptureFileSize*1.0/( GBIT_SIZE );
		sprintf(chFileSize, " %.2f GB", fFileSizeNumber);
	}
}

HRESULT CNetPacketLogic::OnDisConnect(WPARAM wparam, LPARAM lparam)
{
	if(m_bIsCapturing)
	{
		m_bIsCapturing = FALSE;
		m_cTelnet.Close();
		m_cFtp.EndFtpFile();
		KillTimer(NULL, g_nCaptureTime);
	}

	m_bIsExporting = FALSE;
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	UIFACTORYMGR_PTR->LoadScheme( "SchmCaptureExpClean", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchStartPacket", m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption( m_strCaptureTimer, "时间:00:00", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strCaptureFileSize, "文件大小: 0M", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmExportbtnEnd", m_pWndTree, m_strBtnCaptureExport );
	return S_OK;
}

bool CNetPacketLogic::OnExportProgress(const IArgs & arg)
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);
	
	switch( m_emFileFtpStatus )
	{
	case emFtpBegin:
		{
			if(m_emFtpTransType == em_FTPCAPTRANS_EXPORT)
			{
				m_dwTotalFileSize = static_cast<u32>(msg.lParam);						
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strExportProgress );	
			}					
		}
		break;
	case emFtpTransfer:
		{
			if(m_emFtpTransType == em_FTPCAPTRANS_EXPORT)
			{
				if ( m_dwTotalFileSize != 0 )
				{
					u32 dwCurrentTransSize = static_cast<u32>(msg.lParam);   //当前传输的大小				
					float fCurrTransProgress = (float)dwCurrentTransSize/m_dwTotalFileSize*100;
					if ( dwCurrentTransSize < m_dwTotalFileSize )
					{	
						m_valProgress.nPos = (u32)fCurrTransProgress;										
						UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strExportProgress, m_pWndTree );					
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
				if ( m_emFtpTransType == em_FTPCAPTRANS_IMPORT )
				{
					BtnStartCapture();
				}
				else
				{
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strExportProgress );
					MSGBOX_RET nResult = MSGBOX_CANCEL;
					MSG_BOX( nResult, "导出抓包文件成功，是否删除抓包文件？");
					m_bIsExporting = FALSE;
					u16 wRet = COMIFMGRPTR->SetCaptureStateCmd(m_bIsExporting);
					
					if(NO_ERROR != wRet)
					{
						WARNMESSAGE("是否正在操作抓包消息发送失败！");
					}
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strExportProgress );
					UIFACTORYMGR_PTR->LoadScheme( "SchmExportbtnEnd", m_pWndTree, m_strBtnCaptureExport);
					Value_WindowEnable valEnableBtn;
					valEnableBtn.bEnable = true;
					UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, "BtnOfPacket", m_pWndTree);
					if (nResult == MSGBOX_OK)
					{
						if (m_cFtp.FindfFtpFile(CNSCAPTURE_FILE_PATH, CAPTURE_FILE_NAME))
						{
							if(m_cFtp.DeleteFile(REMOTE_FILE_NAME))
							{
								UIFACTORYMGR_PTR->SetCaption(m_strCaptureTimer, "时间:00:00", m_pWndTree);
								UIFACTORYMGR_PTR->SetCaption( m_strCaptureFileSize, "文件大小: 0M", m_pWndTree );
							}
						}
					}
				}				
			}
			else
			{
				if ( m_emFtpTransType == em_FTPCAPTRANS_IMPORT )
				{
					MSG_BOX_OK("上传抓包工具失败！");
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
					String strError = "导出文件出错，错误原因：";
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
				}

				m_bIsExporting = FALSE;
				u16 wRet = COMIFMGRPTR->SetCaptureStateCmd(m_bIsExporting);
				
				if(NO_ERROR != wRet)
				{
					WARNMESSAGE("是否正在操作抓包消息发送失败！");
				}
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strExportProgress );
				UIFACTORYMGR_PTR->LoadScheme( "SchmExportbtnEnd", m_pWndTree, m_strBtnCaptureExport);
				Value_WindowEnable valEnableBtn;
				valEnableBtn.bEnable = true;
				UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, "BtnOfPacket", m_pWndTree);
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

bool CNetPacketLogic::GetCaptureState()
{
	return m_bIsCapturing;
}

bool CNetPacketLogic::GetExportState()
{
	return m_bIsExporting;
}

void CNetPacketLogic::SetCaptureFileSize()
{
	u32 dwIp = 0;
	s8 chFileSize[40];
	s8 chfilesize[STC_CAPTURE_MES];
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
			return;
		}
	}

	if(!bRet)
	{	
		return;
	}
	
	if(!m_cFtp.ConnectServer())
	{
		return;
	}

	m_cFtp.SetRemoteFileName( REMOTE_FILE_NAME );
	u32 dwCaptureFileSize = m_cFtp.GetRemoteFileSize();
	GetFileSize( dwCaptureFileSize, chFileSize );
	if( dwCaptureFileSize > 0)
	{
		sprintf( chfilesize, "文件大小:%s", chFileSize);
		UIFACTORYMGR_PTR->SetCaption( m_strCaptureFileSize, chfilesize, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption( m_strCaptureFileSize, "文件大小: 0M", m_pWndTree );
	}	
}

void CNetPacketLogic::StartCapture()
{
	u32 dwIp = 0;
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
		MSG_BOX_OK(" 连接到服务器失败！");		
		return;
	}
	
	if ( !m_cFtp.ConnectServer() )
	{
		MSG_BOX_OK("FTP连接服务器失败！");
		return;
	}
	
	if ( NULL != m_pWnd )
	{
		String strT300EFilePath = GetModulePath();
		String strCaptureFilePath = CNSCAPTURE_FILE_PATH;
		strCaptureFilePath += CNS_T300E_TUMP_NAME;
		strT300EFilePath += "rescnstool\\";
		strT300EFilePath += CNS_T300E_TUMP_NAME;
		
		if (!m_cFtp.FindfFtpFile( CNSCAPTURE_FILE_PATH, CNS_T300E_TUMP_NAME ))
		{
			FILE  *fp = NULL;
			fp = fopen(strT300EFilePath.c_str(), "r");
			if( NULL == fp )
			{
				MSG_BOX_OK("本地抓包工具不存在！");
				return;
			}
			
			fclose(fp);
			fp = NULL;
			
			m_emFtpTransType = em_FTPCAPTRANS_IMPORT;
			m_cFtp.RegisterMsgHandle(WM_CNSTOOL_FTPCAPTUREPROGRESS);
			if( !m_cFtp.BeginUpload(m_pWnd->GetSafeHwnd(), strCaptureFilePath.c_str(), strT300EFilePath.c_str(),
				FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
			{
				String strError;
				strError.append("上传抓包工具失败！");
				MSG_BOX_OK(strError);
				return;
			}
		}
		else
		{
			BtnStartCapture();
		}
	}
}

HRESULT CNetPacketLogic::OnSetFtpInfoRsp( WPARAM wparam, LPARAM lparam )
{
	TTPFtpInfo tTPFtpInfo = *(TTPFtpInfo*)(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);
	if( bSuccess ) 
	{
		//点击“开始抓包”处理
		if (m_bIsClickBtnPacket)
		{
			if(!m_bIsCapturing)
			{
				//判断ftp、telnet是否开启
				TTPTelnetInfo tTPTelnetInfo;
				LIBDATAMGRPTR->GetTelnetInfo(tTPTelnetInfo);
				
				if (tTPFtpInfo.bOpen && tTPTelnetInfo.bOpen)
				{
					m_bIsClickBtnPacket = FALSE;
					StartCapture(); 
				}
			}
		}
	
		//点击“导出抓包”处理
		if (m_bIsClickBtnExport)
		{
			if (tTPFtpInfo.bOpen)
			{
				m_bIsClickBtnExport = FALSE;
				ExportPacket();
			}
		}
	}
	
	return S_OK;
}

HRESULT CNetPacketLogic::OnSetTelnetInfoRsp( WPARAM wparam, LPARAM lparam )
{
	TTPTelnetInfo tTPTelnetInfo = *(TTPTelnetInfo*)(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);
	if( bSuccess ) 
	{
		//点击“开始抓包”处理
		if (m_bIsClickBtnPacket)
		{
			if(!m_bIsCapturing)
			{
				//判断ftp、telnet是否开启
				TTPFtpInfo tTPFtpInfo;
				LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
				if (tTPFtpInfo.bOpen && tTPFtpInfo.bOpen)
				{
					m_bIsClickBtnPacket = FALSE;
					StartCapture();
				}
			}
		}
	}
	
	return S_OK;
}

void CNetPacketLogic::ExportPacket()
{
	u32 dwIp = 0;
	TLoginInfo tInfo;
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
	
	if(!bRet)
	{
		MSG_BOX_OK("设置服务器参数失败！");		
		return;
	}
	
	if(!m_cFtp.ConnectServer())
	{
		MSG_BOX_OK("FTP连接服务器失败！");
	}
	
	if ( NULL != m_pWnd )
	{	
		if (m_cFtp.FindfFtpFile(CNSCAPTURE_FILE_PATH, CAPTURE_FILE_NAME))
		{
			m_emFtpTransType = em_FTPCAPTRANS_EXPORT;
			StartExportFile();
		}
		else
		{
			MSG_BOX_OK("抓包文件不存在！");
			return;
		}
	}
}












