// OrderListDlgLogic.cpp: implementation of the COrderListDlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OrderListDlgLogic.h"
#include "MoonAdjustDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COrderListDlgLogic::COrderListDlgLogic()
:m_bIsSelect(FALSE)
{
	m_strLstOrderPos = "OrderListChildDlg/LstOrderPos";
}

COrderListDlgLogic::~COrderListDlgLogic()
{

}

bool COrderListDlgLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	

	if ( NULL == m_pListWnd )
	{
		m_pListWnd = (CTransparentViewList*)UIFACTORYMGR_PTR->GetWindowPtr( m_strLstOrderPos, m_pWndTree );
	}
	m_bIsSelect = FALSE;
	return true;
}

void COrderListDlgLogic::RegMsg()
{
	COrderListDlgLogic *pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_MOONTOOL_CAMPRESET_NTY, COrderListDlgLogic::OnCamPreSetNty, pThis, COrderListDlgLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_PREDEL_IND, COrderListDlgLogic::OnCamPreDelInd, pThis, COrderListDlgLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_PREMODIFY_IND, COrderListDlgLogic::OnCamPreModifyInd, pThis, COrderListDlgLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_PRESET_IND, COrderListDlgLogic::OnCamPreSetInd, pThis, COrderListDlgLogic );
	REG_MSG_HANDLER( UI_MoonTool_SnapShot_IND, COrderListDlgLogic::OnSnapShotNty, pThis, COrderListDlgLogic );
}

void COrderListDlgLogic::UnRegMsg()
{
	
}

void COrderListDlgLogic::RegCBFun()
{
	COrderListDlgLogic *pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "COrderListDlgLogic::InitWnd", COrderListDlgLogic::InitWnd, pThis, COrderListDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "COrderListDlgLogic::OnBtnImport", COrderListDlgLogic::OnBtnImport, pThis, COrderListDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "COrderListDlgLogic::OnBtnExport", COrderListDlgLogic::OnBtnExport, pThis, COrderListDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "COrderListDlgLogic::OnBtnModify", COrderListDlgLogic::OnBtnModify, pThis, COrderListDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "COrderListDlgLogic::OnBtnInvoke", COrderListDlgLogic::OnBtnInvoke, pThis, COrderListDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "COrderListDlgLogic::OnBtnDelete", COrderListDlgLogic::OnBtnDelete, pThis, COrderListDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "COrderListDlgLogic::OnBtnBack", COrderListDlgLogic::OnBtnBack, pThis, COrderListDlgLogic );

	REG_GOBAL_MEMBER_FUNC( "COrderListDlgLogic::OnClickOrderLstDlgBlack", COrderListDlgLogic::OnClickOrderLstDlgBlack, pThis, COrderListDlgLogic );

	REG_LIST_CALLFUNC( "COrderListDlgLogic::OnClickOrderPosItem", COrderListDlgLogic::OnClickOrderPosItem, pThis, COrderListDlgLogic );

	REG_DEFAULT_WINDOW_MSG( WM_MoonTool_FTP_PreSetSnapDownLoad );

	REG_GOBAL_MEMBER_FUNC( "COrderListDlgLogic::OnDownloadProgress", COrderListDlgLogic::OnDownloadProgress, pThis, COrderListDlgLogic );
}

void COrderListDlgLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "COrderListDlgLogic::InitWnd" );	
}

void COrderListDlgLogic::Clear()
{
	m_bIsSelect = FALSE;
	//防止登陆上方切换按钮丢失，具体原因未知
	UIFACTORYMGR_PTR->LoadScheme( "SchmNoItemCheck", m_pWndTree );

	for( std::vector<TTPCamPreOption>::iterator iter = m_vecTPCamPreInfo.begin(); iter!= m_vecTPCamPreInfo.end();
		iter ++ )
	{
		iter->m_tCamPre.bIsUsed = FALSE;
	}

	Value_ItemOrderPos valOrderPos(&m_vecTPCamPreInfo);
	valOrderPos.m_strClickItemFunc = "COrderListDlgLogic::OnClickOrderPosItem";
	UIFACTORYMGR_PTR->SetPropertyValue( valOrderPos, m_strLstOrderPos, m_pWndTree );				//设置预制位静态图片
	ReleaseAllImage(m_vecTPCamPreInfo);																//释放正在占用的图片资源
	
	m_vecTPCamPreInfo.clear();
	if( m_emFileFtpStatus != emFtpEnd )
	{
		m_cFtp.EndFtpFile();
		m_emFileFtpStatus = emFtpEnd;
	}
	CMsgDispatch::SendMessage( UI_MOONTOOL_LISTMENU_OPTION, NULL, (LPARAM)em_MENULIST_SHOW );
}

bool COrderListDlgLogic::OnBtnImport( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchImportOrderList", NULL, g_stcStrImpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrImpCommonDlg );
	return true;
}

bool COrderListDlgLogic::OnBtnExport( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", NULL, g_stcStrExpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchExportOrderList", NULL, g_stcStrExpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrExpCommonDlg );	
	return true;	
}

bool COrderListDlgLogic::OnBtnModify( const IArgs& args )
{
	if ( m_bIsSelect == TRUE )
	{
		CMsgDispatch::SendMessage( UI_MOONTOOL_ORDERPOS_MODIFY, (WPARAM)&m_tCamPreSel, (LPARAM)em_ORDERPOSOPT_MODIFY );
	}
	else
	{
		CMsgDispatch::SendMessage( UI_MOONTOOL_ORDERPOS_MODIFY, NULL, (LPARAM)em_ORDERPOSOPT_MODIFY );
	}
	return true;	
}

bool COrderListDlgLogic::OnBtnInvoke( const IArgs& args )
{
	u16 nRet = COMIFMGRPTR->OrderPosInvokeCmd(m_tCamPreSel);
	m_bIsSelect = FALSE;
	UIFACTORYMGR_PTR->ShowWindow( g_strOrderListDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCamCtrlDlg );

	CMsgDispatch::SendMessage( UI_MOONTOOL_LISTMENU_OPTION, NULL, (LPARAM)em_MENULIST_SHOW );
	UIFACTORYMGR_PTR->LoadScheme( "SchmOrderListDataClean", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmNoItemCheck", m_pWndTree );
	return true;	
} 

bool COrderListDlgLogic::OnBtnDelete( const IArgs& args )
{
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "是否删除预置位？" );
	if ( MSGBOX_OK == nMsgBoxRet)
	{
		u16 nRet = COMIFMGRPTR->OrderPosDeleteReq(m_tCamPreSel);
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "删除预置位请求发送失败" );
		}
	}
	return true;	
}

bool COrderListDlgLogic::OnBtnBack( const IArgs& args )
{
	m_bIsSelect = FALSE;
	UIFACTORYMGR_PTR->ShowWindow( g_strOrderListDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCamCtrlDlg );
	//每次点返回前清空下列表选中项
	UIFACTORYMGR_PTR->LoadScheme( "SchmOrderListDataClean", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmNoItemCheck", m_pWndTree );
	CMsgDispatch::SendMessage( UI_MOONTOOL_LISTMENU_OPTION, NULL, (LPARAM)em_MENULIST_SHOW );
	return true;	
}

bool COrderListDlgLogic::OnClickOrderPosItem( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
	{
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_ItemOrderPos *pItemInfo = dynamic_cast<const Data_ItemOrderPos*>( pBaseItem->GetUserData() ) )
		{
			m_bIsSelect = TRUE;

			m_tCamPreSel.byPre = pItemInfo->m_tOrderPosItem.m_tCamPre.byPre;
			m_tCamPreSel.bIsUsed = pItemInfo->m_tOrderPosItem.m_tCamPre.bIsUsed;
			strcpy( m_tCamPreSel.achachDescription,pItemInfo->m_tOrderPosItem.m_tCamPre.achachDescription );
			
			if ( m_tCamPreSel.bIsUsed == TRUE )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmItemCheck", m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmNoItemCheck", m_pWndTree );
			}

		}

	}
	return true;
}

bool COrderListDlgLogic::OnClickOrderLstDlgBlack( const IArgs& args )
{
	if ( m_vecTPCamPreInfo.size()> 0 )
	{
		m_tCamPreSel = m_vecTPCamPreInfo.at(0).m_tCamPre;
	}

	m_bIsSelect = FALSE;
	UIFACTORYMGR_PTR->LoadScheme( "SchmNoItemCheck", m_pWndTree );
	return true;
}

HRESULT COrderListDlgLogic::OnCamPreSetNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
	TTPCamPre atTPCamPre[MAX_CAMERA_Pre_NUM];
	std::vector<TTPCamPreOption> vetTemp = m_vecTPCamPreInfo;

	memcpy( &atTPCamPre, MOONLIBDATAMGRPTR->GetCamPreInfo(), sizeof(TTPCamPre)*MAX_CAMERA_Pre_NUM );
	UIFACTORYMGR_PTR->LoadScheme( "SchmOrderListDataClean", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmNoItemCheck", m_pWndTree );
	//切换摄像机机芯时，先清空预支位列表，再根据机芯编号重设
	
	m_vecTPCamPreInfo.clear();

	for ( s32 nIndex = 0; nIndex < MAX_CAMERA_Pre_NUM; nIndex++  )
	{
		TTPCamPreOption tTPCamPre;
		tTPCamPre.m_tCamPre.byIndex = atTPCamPre[nIndex].byIndex;
		tTPCamPre.m_tCamPre.byPre = nIndex;
		tTPCamPre.m_tCamPre.bIsUsed =  atTPCamPre[nIndex].bIsUsed;
		tTPCamPre.m_bIsStatic = TRUE;
		tTPCamPre.m_bIsOriPic = TRUE;
		strcpy( tTPCamPre.m_tCamPre.achachDescription,atTPCamPre[nIndex].achachDescription );
		m_vecTPCamPreInfo.push_back(tTPCamPre);				
	}

	Value_ItemOrderPos valOrderPos(&m_vecTPCamPreInfo);
	valOrderPos.m_strClickItemFunc = "COrderListDlgLogic::OnClickOrderPosItem";
	UIFACTORYMGR_PTR->SetPropertyValue( valOrderPos, m_strLstOrderPos, m_pWndTree );

	ReleaseAllImage(vetTemp);

	DownLoadFile(m_vecTPCamPreInfo);
	CMsgDispatch::SendMessage(WM_MoonTool_PresetListParam_IND,(WPARAM)&m_vecTPCamPreInfo,NULL);
	return NO_ERROR;	
}

HRESULT COrderListDlgLogic::OnCamPreDelInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
	TTPCamPre tTPCamPre = *reinterpret_cast<TTPCamPre*>(wparam);

	BOOL bOk = (BOOL)(lparam);

	if ( bOk )
	{
		for( s32 nIndex = 0; nIndex < MAX_CAMERA_Pre_NUM; nIndex++ )
		{
			if ( nIndex == tTPCamPre.byPre )
			{
				m_vecTPCamPreInfo.at(nIndex).m_tCamPre.byPre = nIndex;
				m_vecTPCamPreInfo.at(nIndex).m_tCamPre.bIsUsed = FALSE;
				strcpy( m_vecTPCamPreInfo.at(nIndex).m_tCamPre.achachDescription,"" );
				Value_ItemOrderPos valOrderPos(&m_vecTPCamPreInfo);
				valOrderPos.m_strClickItemFunc = "COrderListDlgLogic::OnClickOrderPosItem";
				UIFACTORYMGR_PTR->SetPropertyValue( valOrderPos, m_strLstOrderPos, m_pWndTree );

				CMsgDispatch::SendMessage(WM_MoonTool_PresetListParam_IND,(WPARAM)&m_vecTPCamPreInfo,NULL);
				
				if ( m_tCamPreSel.byPre == tTPCamPre.byPre )
				{
					m_tCamPreSel = m_vecTPCamPreInfo.at(nIndex).m_tCamPre;
				}
				
				s8 chFileName[20] = {0};

				sprintf(chFileName,MOONPRESET_SNAPSHOT,m_vecTPCamPreInfo.at(nIndex).m_tCamPre.byIndex,m_vecTPCamPreInfo.at(nIndex).m_tCamPre.byPre);	
				
				string strFilePath = MOONSNAPSHOT_FILE_PATH;
				strFilePath += "\\";
				string strFileName = strFilePath + chFileName;
				UIFACTORYMGR_PTR->ReleaseSingleImage(strFileName);										//释放原始图片资源
				
				strFileName = CSystem::GetSingletonPtr()->GetImagePath()+ "//" + strFileName;

				remove(strFileName.c_str());
				
				break;
			}
		}
	}
	else
	{
		WARNMESSAGE( "未能成功删除预置位");
	}

	return NO_ERROR;	
}

HRESULT COrderListDlgLogic::OnCamPreModifyInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

	TTPCamPre tTPCamPre = *reinterpret_cast<TTPCamPre*>(wparam);

	BOOL bOk = (BOOL)(lparam);

	if ( bOk )
	{
		for( s32 nIndex = 0; nIndex < MAX_CAMERA_Pre_NUM; nIndex++ )
		{
			if ( nIndex == tTPCamPre.byPre )
			{
				m_vecTPCamPreInfo.at(nIndex).m_tCamPre.byPre = nIndex;
				m_vecTPCamPreInfo.at(nIndex).m_tCamPre.bIsUsed = tTPCamPre.bIsUsed;
				strcpy( m_vecTPCamPreInfo.at(nIndex).m_tCamPre.achachDescription,tTPCamPre.achachDescription );
				//收到修改回复消息时，将选中项的描述更新，防止反复点修改弹框值不对
				Value_ItemOrderPos valOrderPos(&m_vecTPCamPreInfo);
				valOrderPos.m_strClickItemFunc = "COrderListDlgLogic::OnClickOrderPosItem";
				UIFACTORYMGR_PTR->SetPropertyValue( valOrderPos, m_strLstOrderPos, m_pWndTree );

				CMsgDispatch::SendMessage(WM_MoonTool_PresetListParam_IND,(WPARAM)&m_vecTPCamPreInfo,NULL);

				if ( m_tCamPreSel.byPre == tTPCamPre.byPre )
				{
					strcpy( m_tCamPreSel.achachDescription,tTPCamPre.achachDescription );
					m_tCamPreSel = m_vecTPCamPreInfo.at(nIndex).m_tCamPre;
				}
				break;
			}
		}
	}
	else
	{
		WARNMESSAGE( "只能修改已有预置位描述");
	}
	

	return NO_ERROR;	
}

HRESULT COrderListDlgLogic::OnCamPreSetInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

	TTPCamPre tTPCamPre = *reinterpret_cast<TTPCamPre*>(wparam);

	BOOL bOk = (BOOL)(lparam);

	if ( bOk )
	{
		for( s32 nIndex = 0; nIndex < MAX_CAMERA_Pre_NUM; nIndex++ )
		{
			if ( nIndex == tTPCamPre.byPre )
			{
				if ( m_vecTPCamPreInfo.at(nIndex).m_tCamPre.bIsUsed == TRUE )
				{
					m_vecTPCamPreInfo.at(nIndex).m_bIsStatic = FALSE;                    //当保存的预制位已经存在时 切换时不进行静态转换
				}
				else
				{
					m_vecTPCamPreInfo.at(nIndex).m_bIsStatic = TRUE;					//预制位不存在时，中间用静态图片过度
				}

				m_vecTPCamPreInfo.at(nIndex).m_tCamPre.byPre = nIndex;
				m_vecTPCamPreInfo.at(nIndex).m_tCamPre.bIsUsed = tTPCamPre.bIsUsed;
				strcpy( m_vecTPCamPreInfo.at(nIndex).m_tCamPre.achachDescription,tTPCamPre.achachDescription );
				m_vecTPCamPreInfo.at(nIndex).m_bIsOriPic = TRUE;
				
				Value_ItemOrderPos valOrderPos(&m_vecTPCamPreInfo);
				valOrderPos.m_strClickItemFunc = "COrderListDlgLogic::OnClickOrderPosItem";
				UIFACTORYMGR_PTR->SetPropertyValue( valOrderPos, m_strLstOrderPos, m_pWndTree );
				
				CMsgDispatch::SendMessage(WM_MoonTool_PresetListParam_IND,(WPARAM)&m_vecTPCamPreInfo,NULL);

				if ( m_tCamPreSel.byPre == tTPCamPre.byPre )
				{
					strcpy( m_tCamPreSel.achachDescription,tTPCamPre.achachDescription );
					m_tCamPreSel = m_vecTPCamPreInfo.at(nIndex).m_tCamPre;
				}
				break;
			}
		}
	}
	else
	{
		WARNMESSAGE( "已有预置位不允许再保存，只能进行修改操作");
	}
	
	return NO_ERROR;	
}

void COrderListDlgLogic::DownLoadFile( vector<TTPCamPreOption> &VecTCamPreInfo )
{
	if ( VecTCamPreInfo.size() < 0 )
	{
		return ;
	}

	s8 chFileName[20] = {""};
	u32 dwIp;

	MOONLIBDATAMGRPTR->GetLoginIp(dwIp);
	CString strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );

	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, MT_TEL_USRNAME, MT_TEL_PWD );
	if ( !bRet )
	{
		MSG_BOX_OK("连接服务器失败！");	
		return ;
	}
	
	m_cFtp.RegisterMsgHandle( WM_MoonTool_FTP_PreSetSnapDownLoad );

	if ( m_cFtp.ConnectServer() )
	{
		m_vecDownLoadfile.clear();

		for( vector<TTPCamPre>::size_type nIndex = 0; nIndex < VecTCamPreInfo.size(); nIndex ++ )
		{
			if ( VecTCamPreInfo.at(nIndex).m_tCamPre.bIsUsed == TRUE )
			{	
				sprintf(chFileName,MOONPRESET_SNAPSHOT,VecTCamPreInfo.at(nIndex).m_tCamPre.byIndex,VecTCamPreInfo.at(nIndex).m_tCamPre.byPre);

				if ( m_cFtp.FindfFtpFile( MoonTool_SNAPSHOT_PATH, chFileName ) )
				{
					m_vecDownLoadfile.push_back(chFileName);
					VecTCamPreInfo.at(nIndex).m_bIsStatic = FALSE;
				}
				else
				{
					VecTCamPreInfo.at(nIndex).m_bIsStatic = TRUE;                        //文件不存在时，也采用静态图片
				}
				
				memset( chFileName,0,sizeof(chFileName));
			}
		}

		if ( m_vecDownLoadfile.size() > 0 )
		{
			m_vecWaitDownLoad = m_vecDownLoadfile;
			DownloadCore(m_vecWaitDownLoad[0]);
			UIFACTORYMGR_PTR->LoadScheme("SchmBegin",NULL,g_strMoonMainFrame);
		}
	}
}


BOOL COrderListDlgLogic::DownloadCore( const String & strFileName )
{	
	string strForder = "";
	string strSavePath = "";

	Window * pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_strOrderListDlg );
	
	strForder = UIFACTORYMGR_PTR->GetImagePath();				//本地保存的路径
	strSavePath = strForder + MOONSNAPSHOT_FILE_PATH + "\\" + "temp" + strFileName;							//先将图片保存在temp开头的文件中
	
	if ( !UIDATAMGR_PTR->RecusionMkDir( UIDATAMGR_PTR->GetFileFolderPath(strSavePath).c_str() ))
	{
		MSG_BOX_OK( "创建文件目录失败!" );	
		
		return true;
	}	
	
	m_cFtp.RegisterMsgHandle( WM_MoonTool_FTP_PreSetSnapDownLoad );

	if ( NULL != pWnd )
	{
		String strRemoteFile = "";
		strRemoteFile = MoonTool_SNAPSHOT_PATH + strFileName;
		if ( !m_cFtp.BeginDownload( pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, FALSE ) )
		{
			MSG_BOX_OK( "下载快照图片失败，参数错误!" );
			
			UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
			UIFACTORYMGR_PTR->LoadScheme("SchmEnd",NULL,g_strMoonMainFrame);
			CMsgDispatch::SendMessage(WM_MoonTool_StatusSet,NULL,NULL);
			return false;
		}
	}
	
	return TRUE;
}

bool COrderListDlgLogic::OnDownloadProgress( const IArgs & arg )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);

	if ( m_emFileFtpStatus ==  emFtpEnd )
	{
		DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP接口0为成功  默认失败
		if ( 0 == dwSuccess )
		{
			if ( m_vecWaitDownLoad.size() > 0 )
			{
				vector<String>::iterator itr = m_vecWaitDownLoad.begin();
				m_vecWaitDownLoad.erase(itr);
				u32 nNum= m_vecWaitDownLoad.size();
				if ( nNum > 0 )
				{
					DownloadCore( m_vecWaitDownLoad.at(0) );
				}
				else
				{
					SwapImage();
					UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
					UIFACTORYMGR_PTR->LoadScheme("SchmEnd",NULL,g_strMoonMainFrame);
					CMsgDispatch::SendMessage(WM_MoonTool_StatusSet,NULL,NULL);
					m_cFtp.EndFtpFile();
				}
			} 	
		}
		else
		{
			if (( UIFACTORYMGR_PTR->IsVisible(g_strMoonMainFrame)) == FALSE )
			{
				if( m_emFileFtpStatus != emFtpEnd )
				{
					m_cFtp.EndFtpFile();
					m_emFileFtpStatus = emFtpEnd;
				}
				return false;
			}
			//FtpFindFirstFile Error With 18--没有更多文件.这是获取远端文件大小的时候提示的错误,不关闭Ftp,之后可以成功
			if ( dwSuccess == 18 )  
			{
				return S_FALSE;
			}
			LPTSTR pszMsg = NULL;
			m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
			String strError = "下载文件出错，错误原因：";
			if( dwSuccess == 122 )    //win7中文件不存在时候的异常提醒“传递给系统调用的数据区域太小”
			{
				strError += "系统找不到指定的文件。";
				OspPrintf( TRUE, FALSE, (char*)strError.c_str() );
				MSG_BOX_OK( strError.c_str() );					
				LocalFree( pszMsg );
			}
			else
			{
				strError += pszMsg;
				strError+m_vecDownLoadfile.at(0);
				OspPrintf( TRUE, FALSE, (char*)strError.c_str() );
				MSG_BOX_OK( strError.c_str() );	
				LocalFree( pszMsg );
			}
			m_cFtp.EndFtpFile();

			UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
			UIFACTORYMGR_PTR->LoadScheme("SchmEnd",NULL,g_strMoonMainFrame);
			CMsgDispatch::SendMessage(WM_MoonTool_StatusSet,NULL,NULL);
		}	
	}

	return true;
}

void COrderListDlgLogic::SwapImage( )
{
	string strFilePathMid,strFilePathTemp;
	std::vector<TTPCamPreOption> vecCamPreInfo;
	s32 nCamIndex,nPreSetIndex;

	if ( m_vecTPCamPreInfo.size() ==0 )
	{
		return ;
	}

	if ( CopySnapShotImage(false) == false )									//将下载完成的图片拷贝到临时文件中
	{
		MSG_BOX_OK( "拷贝文件失败!" );
		
		return;
	}

	vecCamPreInfo = m_vecTPCamPreInfo;

	for( vector<string>::size_type nSize = 0; nSize < m_vecDownLoadfile.size(); nSize ++ )
	{
		if ( sscanf(m_vecDownLoadfile.at(nSize).c_str(),MOONPRESET_SNAPSHOT,&nCamIndex,&nPreSetIndex) != 2)
		{
			return ;
		}

		if ( nPreSetIndex < 0 || nPreSetIndex >= MAX_CAMERA_Pre_NUM )
		{
			return ;
		}
		
		vecCamPreInfo.at(nSize).m_bIsOriPic = FALSE;                                                //准备进行图片切换 到temp文件名图片中
	}

	Value_ItemOrderPos valOrderPos(&vecCamPreInfo);
	valOrderPos.m_strClickItemFunc = "COrderListDlgLogic::OnClickOrderPosItem";
	UIFACTORYMGR_PTR->SetPropertyValue( valOrderPos, m_strLstOrderPos, m_pWndTree );				//加载下载的temp临时文件快照文件进内存
	
	ReleaseSnapShotImage(true);																		//释放原始占用的快照图片资源 
	CopySnapShotImage(true);																		//将inter中间图片拷贝到原始快照文件中
	vecCamPreInfo = m_vecTPCamPreInfo;
	Value_ItemOrderPos valOrderPos2(&vecCamPreInfo);
	valOrderPos2.m_strClickItemFunc = "COrderListDlgLogic::OnClickOrderPosItem";
	UIFACTORYMGR_PTR->SetPropertyValue( valOrderPos2, m_strLstOrderPos, m_pWndTree );				//加载原始快照图片

	ReleaseSnapShotImage(false);																	//释放temp文件名临时图片资源
	DeleteFile();																					//删除切换用的temp和inter过度文件
	
	return ;
}

bool COrderListDlgLogic::CopySnapShotImage( bool bIsSwaped )
{
	string strPath =  CSystem::GetSingletonPtr()->GetImagePath();
	string strFilePath = strPath + "\\" + MOONSNAPSHOT_FILE_PATH + "\\";
	string strSrcFileName = "";						//源文件路径名
	string strDisFileName = "";						//拷贝的目标文件路径名

	CMoonAdjustDlg * pAdjustDlg = CMoonAdjustDlg::GetSingletonPtr();

	if ( pAdjustDlg == NULL )
	{
		return false;
	}

	for ( vector<string>::size_type nSize = 0; nSize < m_vecDownLoadfile.size(); nSize ++ )
	{
		if ( bIsSwaped == false )
		{
			strSrcFileName = strFilePath + "temp" + m_vecDownLoadfile.at(nSize);								//原文件在使用中时，保持平滑切换 使用两组图片作为中介进行切换
			strDisFileName = strFilePath + "inter" + m_vecDownLoadfile.at(nSize);
			if ( PictureChange(strSrcFileName,strDisFileName) == false )										//更改图片的尺寸，测试中发现加载多张1920*1080的图片将导致界面卡顿严重
			{
				return false;
			}	
		}
		else
		{
			strSrcFileName = strFilePath + "inter" + m_vecDownLoadfile.at(nSize);
			strDisFileName = strFilePath + m_vecDownLoadfile.at(nSize);

			pAdjustDlg->CopyFile(strSrcFileName,strDisFileName);
		}
	}

	return true;
}

void COrderListDlgLogic::ReleaseSnapShotImage( bool bIsRelOriPic )
{
	string strFilePath = MOONSNAPSHOT_FILE_PATH;
	strFilePath += "\\";

	string strFileName = "";	

	for ( vector<string>::size_type nSize = 0; nSize < m_vecDownLoadfile.size(); nSize ++ )
	{
		if ( bIsRelOriPic == true )
		{
			strFileName = strFilePath + m_vecDownLoadfile.at(nSize);									//最终占用快照图片资源 与服务器快照名称相同
		}
		else
		{
			strFileName = strFilePath + "temp" + m_vecDownLoadfile.at(nSize);							//需要释放临时图片资源名称作为中间切换时使用
		}

		UIFACTORYMGR_PTR->ReleaseSingleImage(strFileName);
	}
}

void COrderListDlgLogic::DeleteFile()
{
	string strPath =  CSystem::GetSingletonPtr()->GetImagePath();
	string strFilePath = strPath + "\\" + MOONSNAPSHOT_FILE_PATH + "\\";
	string strFileName = "";

	for( vector<string>::size_type nSize = 0; nSize < m_vecDownLoadfile.size(); nSize ++ )        //删除快照下载完成后，交换图片使用的所有中间图片
	{
		strFileName = strFilePath + "temp" + m_vecDownLoadfile.at(nSize);

		if ( ( UIDATAMGR_PTR->IsFileExist(strFileName.c_str())) == TRUE )
		{
			remove(strFileName.c_str());
		}
		
		strFileName = strFilePath + "inter" + m_vecDownLoadfile.at(nSize);

		if ( ( UIDATAMGR_PTR->IsFileExist(strFileName.c_str())) == TRUE )
		{
			remove(strFileName.c_str());
		}
	}
}

LRESULT COrderListDlgLogic::OnSnapShotNty( WPARAM wparam, LPARAM lparam )
{
	TTPSnapshotInfo tSnapShotInfo = *( TTPSnapshotInfo*)(lparam);
	if ( tSnapShotInfo.byIndex == 3 )
	{
		return S_OK;
	}
	
	bool bSuccess = *(BOOL*)wparam;
	
	if ( bSuccess == false )
	{
		UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
		return S_FALSE;
	}
	
	u32 dwIp;
	MOONLIBDATAMGRPTR->GetLoginIp(dwIp);
	CString strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, MT_TEL_USRNAME, MT_TEL_PWD );
	if ( !bRet )
	{
		MSG_BOX_OK("连接服务器失败！");	
		return S_FALSE;
	}
	string strFilePath = tSnapShotInfo.achFileNme;

	m_cFtp.RegisterMsgHandle( WM_MoonTool_FTP_PreSetSnapDownLoad );
	
	if ( m_cFtp.ConnectServer() )
	{
		m_vecDownLoadfile.clear();
		
		size_t nSize = strFilePath.rfind("/");
		if ( nSize == string::npos )
		{
			return S_FALSE;
		}
		string strFileName(&strFilePath[nSize+1],strFilePath.end());

		s32 nCamIndex,nPreSetIndex;
		
		if ( sscanf(strFileName.c_str(),MOONPRESET_SNAPSHOT,&nCamIndex,&nPreSetIndex) != 2)
		{
			return S_FALSE;
		}
		
		if ( nPreSetIndex < 0 || nPreSetIndex >= MAX_CAMERA_Pre_NUM )
		{
			return S_FALSE;
		}

		if ( m_cFtp.FindfFtpFile( MoonTool_SNAPSHOT_PATH, strFileName.c_str() ) )
		{
			m_vecDownLoadfile.push_back(strFileName.c_str());
			m_vecTPCamPreInfo.at(nPreSetIndex).m_bIsStatic = FALSE;    
		}
		else
		{
			m_vecTPCamPreInfo.at(nPreSetIndex).m_bIsStatic = TRUE;    
		}
		
		if ( m_vecDownLoadfile.size() > 0 )
		{
			m_vecWaitDownLoad = m_vecDownLoadfile;
			DownloadCore(m_vecWaitDownLoad[0]);
			UIFACTORYMGR_PTR->LoadScheme("SchmBegin",NULL,g_strMoonMainFrame);
		}
	}
	return S_OK;
}

void COrderListDlgLogic::ReleaseAllImage( vector<TTPCamPreOption> &VecTCamPreInfo )
{
	s8 chFileName[20] = {0};
	
	for( vector<TTPCamPre>::size_type nIndex = 0; nIndex < VecTCamPreInfo.size(); nIndex ++ )
	{	
		sprintf(chFileName,MOONPRESET_SNAPSHOT,VecTCamPreInfo.at(nIndex).m_tCamPre.byIndex,VecTCamPreInfo.at(nIndex).m_tCamPre.byPre);
		
		if ( UIDATAMGR_PTR->IsFileExist(chFileName) == TRUE )
		{
			m_vecDownLoadfile.push_back(chFileName);
		}
		
		memset( chFileName,0,sizeof(chFileName));
	}

	ReleaseSnapShotImage(true);
	ReleaseSnapShotImage(false);
}

bool COrderListDlgLogic::PictureChange(string strSrcName, string strDestName )
{
	string strForder,strPath,strFileName;

	WCHAR wFileNameTemp[255];

	memset(wFileNameTemp,0,sizeof(wFileNameTemp));
	s32 len = strSrcName.size()*sizeof(WCHAR);
	MultiByteToWideChar(CP_ACP,0,strSrcName.c_str(),strSrcName.size(),wFileNameTemp,len);  
	Gdiplus::Bitmap BitMapSnapShot(wFileNameTemp);
	
	Gdiplus::Bitmap* pBitmap=new Bitmap(326,256);
	
	if ( pBitmap == NULL )
	{
		return false;
	}

	Gdiplus::Graphics gGraphics(pBitmap);

	gGraphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	gGraphics.DrawImage( &BitMapSnapShot, 0, 0 , 326, 256 );

	CLSID pngClsid;
	GetEncoderClsid(L"image/jpeg", &pngClsid);

	memset(wFileNameTemp,0,sizeof(wFileNameTemp));
	len = strDestName.size()*sizeof(WCHAR);
	MultiByteToWideChar(CP_ACP,0,strDestName.c_str(),strDestName.size(),wFileNameTemp,len); 

	pBitmap->Save(wFileNameTemp,&pngClsid);                                   //保存缩放后的图片
	
	delete pBitmap;
	
	return true;
}

int COrderListDlgLogic::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)  
{  
    UINT  num = 0;  
    UINT  size = 0;  
    ImageCodecInfo* pImageCodecInfo = NULL;  
    GetImageEncodersSize(&num, &size);  
    if(size == 0)  
        return -1;  
	
    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));  
    if(pImageCodecInfo == NULL)  
        return -1;  
	
    GetImageEncoders(num, size, pImageCodecInfo);  
    for(UINT j = 0; j < num; ++j)  
    {  
        if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )  
        {  
            *pClsid = pImageCodecInfo[j].Clsid;  
            free(pImageCodecInfo);  
            return j;  
        }      
    }  
    free(pImageCodecInfo);  
    return -1;  
} 