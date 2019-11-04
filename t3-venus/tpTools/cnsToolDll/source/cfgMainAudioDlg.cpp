// cfgMainAudioDlg.cpp: implementation of the CCfgMainAudioDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CfgMainAudioDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static UINT g_nSetTimer = 0;

VOID CALLBACK OnTimerFunc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
	CCfgMainAudioDlg::GetSingletonPtr()->DownloadOvertime();
}

CCfgMainAudioDlg::CCfgMainAudioDlg()
:m_strLayout("CfgMainAudioDlg/ComboboxLayout")
,m_strImageSynthesis("CfgMainAudioDlg/BtnImageSynthesisSwitch")
,m_strDefault("CfgMainAudioDlg/DefaultBtn")
,m_strSave("CfgMainAudioDlg/SaveBtn")
,m_strCancel("CfgMainAudioDlg/CancleBtn")
,m_strStatus("CfgMainAudioDlg/RenameBtnStatus")
,m_strThreeImage("CfgMainAudioDlg/AudioGroup2")
,m_strFourImage("CfgMainAudioDlg/AudioGroup1")
,m_bIsUsedGroup1(false)
{
	m_strLargeImage[0] = "CfgMainAudioDlg/ComboboxLargerImage1";
	m_strLargeImage[1] = "CfgMainAudioDlg/ComboboxLargerImage2";
	m_strLargeImage[2] = "CfgMainAudioDlg/ComboboxLargerImage3";
	m_strSmallImage[0] = "CfgMainAudioDlg/ComboboxSmallImage1";
	m_strSmallImage[1] = "CfgMainAudioDlg/ComboboxSmallImage2";
	m_strSmallImage[2] = "CfgMainAudioDlg/ComboboxSmallImage3";
	m_vecShatShot.push_back("CfgMainAudioDlg/StcSnapShot1");
	m_vecShatShot.push_back("CfgMainAudioDlg/StcSnapShot2");
	m_vecShatShot.push_back("CfgMainAudioDlg/StcSnapShot3");
}

CCfgMainAudioDlg::~CCfgMainAudioDlg()
{

}

void CCfgMainAudioDlg::RegMsg()
{
	CCfgMainAudioDlg* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_VideoSource_NTY, CCfgMainAudioDlg::OnUpdateMainAudioNty, pThis, CCfgMainAudioDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DefAudio_NTY, CCfgMainAudioDlg::OnDefMainAudioNty, pThis, CCfgMainAudioDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpdateVideoSource_Nty, CCfgMainAudioDlg::OnRefreshVideoInfoNty, pThis, CCfgMainAudioDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCfgMainAudioDlg::OnConfStateNty, pThis, CCfgMainAudioDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_SnapShot_Nty, CCfgMainAudioDlg::OnSnapShotNty, pThis, CCfgMainAudioDlg );	
}

void CCfgMainAudioDlg::RegCBFun()
{
	CCfgMainAudioDlg *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::InitWnd", CCfgMainAudioDlg::InitWnd, pThis, CCfgMainAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnLargeImage1Change", CCfgMainAudioDlg::OnLargeImage1Change, pThis, CCfgMainAudioDlg );
    REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnLargeImage2Change", CCfgMainAudioDlg::OnLargeImage2Change, pThis, CCfgMainAudioDlg );
    REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnLargeImage3Change", CCfgMainAudioDlg::OnLargeImage3Change, pThis, CCfgMainAudioDlg );

    REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnSmallImage1Change", CCfgMainAudioDlg::OnSmallImage1Change, pThis, CCfgMainAudioDlg );
    REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnSmallImage2Change", CCfgMainAudioDlg::OnSmallImage2Change, pThis, CCfgMainAudioDlg );
    REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnSmallImage3Change", CCfgMainAudioDlg::OnSmallImage3Change, pThis, CCfgMainAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnBtnOptRenameDlg",CCfgMainAudioDlg::OnBtnOptRenameDlg,pThis, CCfgMainAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnLayoutChange", CCfgMainAudioDlg::OnLayoutChange, pThis, CCfgMainAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnSwitchSynthesis", CCfgMainAudioDlg::OnSwitchSynthesis, pThis, CCfgMainAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnBtnDefault",CCfgMainAudioDlg::OnBtnDefault, pThis, CCfgMainAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnBtnSave",CCfgMainAudioDlg::OnBtnSave, pThis, CCfgMainAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnBtnCancel",CCfgMainAudioDlg::OnBtnCancel, pThis, CCfgMainAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnBtnPreview",CCfgMainAudioDlg::OnBtnPreview,pThis, CCfgMainAudioDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnSelSynthesisStyle",CCfgMainAudioDlg::OnSelSynthesisStyle,pThis, CCfgMainAudioDlg );

	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_FTPSnapDownLoad );

	REG_GOBAL_MEMBER_FUNC( "CCfgMainAudioDlg::OnDownloadProgress", CCfgMainAudioDlg::OnDownloadProgress, pThis, CCfgMainAudioDlg );
}

void CCfgMainAudioDlg::UnRegFunc()
{

}

bool CCfgMainAudioDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	

	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_strCfgMainAudioDlg );

	m_vecLayout.push_back("不等比缩放");
	m_vecLayout.push_back("裁边等比缩放");
	m_vecLayout.push_back("加黑边等比缩放");
	UIFACTORYMGR_PTR->SetComboListData( m_strLayout, m_vecLayout, m_pWndTree ); 

	UIFACTORYMGR_PTR->SetSwitchState( m_strImageSynthesis, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strFourImage, 1, m_pWndTree );
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

HRESULT CCfgMainAudioDlg::OnUpdateMainAudioNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "保存主视频配置失败" );
		return S_FALSE;
	}

	LIBDATAMGRPTR->GetMainAudioInfo( &m_tMainAudioInfo );
	SetMainAudioDate();
	m_vctWndName.clear();

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();						//当设置combobox的列表内容后，会将控件设置为可用，所以在最后加载模式
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmInConf", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmLeaveConf", m_pWndTree );
	}

	UpBtnState();

	if( m_tMainAudioInfo.m_bIsH323PipMerge )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCheckBtnOpen", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCheckBtnClose", m_pWndTree );
	}

	return S_OK;
}

HRESULT CCfgMainAudioDlg::OnDefMainAudioNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	if ( !bSuccess )
	{
		m_tMainAudioInfo = m_tOldMainAudioInfo;
		WARNMESSAGE( "恢复主视频配置默认设置失败" );
		return S_FALSE;
	}
	else
	{
		LIBDATAMGRPTR->GetMainAudioInfo( &m_tMainAudioInfo );
		SetMainAudioDate();
		m_vctWndName.clear();
		UpBtnState();
	}	
	return S_OK;
}

HRESULT CCfgMainAudioDlg::OnRefreshVideoInfoNty( WPARAM wparam, LPARAM lparam )
{
	TTPVideoInfoTool tMainAudioInfo;
	bool bIschange = false;
	TTPVideoSourceName     tVideoSourceName;

	SaveMainAudioInfo();										//将当前的COMBOTEXT保存下来
	LIBDATAMGRPTR->GetMainAudioInfo( &tMainAudioInfo );			//获取最新一次修改正确的值

	memcpy( m_tMainAudioInfo.m_atVideoSourceName,( TTPVideoSourceName * )wparam,
		sizeof(m_tMainAudioInfo.m_atVideoSourceName) );

	for ( s32 nIndex = 0 ;nIndex <= emTPC7Vid; nIndex ++ )
	{
		for ( s32 nNum = 0 ; nNum <= emTPC7Vid ; nNum ++ )
		{
			if ( m_tMainAudioInfo.m_atVideoSourceName[nIndex].m_emPortType == 
				tMainAudioInfo.m_atVideoSourceName[nNum].m_emPortType )
			{
				if ( strcmp(m_tMainAudioInfo.m_atVideoSourceName[nIndex].m_achSourceName,
					tMainAudioInfo.m_atVideoSourceName[nNum].m_achSourceName ) != 0 )
				{
					bIschange = true;
					break;
				}
			}
		}
		if ( bIschange == true )
		{
			break;
		}
	}

	SetMainAudioDate();
	CheckData( m_strStatus,bIschange );
	return S_OK;
}

LRESULT CCfgMainAudioDlg::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 && m_pWndTree != NULL )
	{
		return S_FALSE;
	}
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmInConf", m_pWndTree );
	} 
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmLeaveConf", m_pWndTree );
		if( m_tMainAudioInfo.m_bIsH323PipMerge )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmCheckBtnOpen", m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmCheckBtnClose", m_pWndTree );
		}
	}
	return S_FALSE;
}

void CCfgMainAudioDlg::Clear()
{
	m_vctWndName.clear();
	UIFACTORYMGR_PTR->LoadScheme("SchmNormal");
	m_bIsUsedGroup1 = !m_bIsUsedGroup1;			                
	ReleaseSnapImage();												 //释放正在占用的图片资源
	m_bIsUsedGroup1 = false;
	UpBtnState();
}

bool CCfgMainAudioDlg::IsCfgMainAudioChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCfgMainAudioDlg::SaveMsgBox()
{
	IArgs args("");
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "配置项已修改，是否保存配置？" );	
	if ( MSGBOX_OK == nMsgBoxRet )
	{
		return OnBtnSave(args);		 
	}
	else
	{	
		OnBtnCancel(args);
	}
	return true;
}


bool CCfgMainAudioDlg::OnBtnCancel( const IArgs& args )
{
	LIBDATAMGRPTR->GetMainAudioInfo( &m_tMainAudioInfo );
	SetMainAudioDate();
	m_vctWndName.clear();
	UpBtnState();

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		OnConfStateNty(0,0);
		return false;	
	}
	return true;	
}

bool CCfgMainAudioDlg::OnBtnDefault( const IArgs& args )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("有会议进行中，不能配置") );
		OnBtnCancel(args);
		return false;	
	}

	m_tOldMainAudioInfo = m_tMainAudioInfo;

	memset( &m_tMainAudioInfo, 0, sizeof(m_tMainAudioInfo) );

	SetDefVideoSrcInfo();
	u16 wRet =  COMIFMGRPTR->SetDefaultMainAudioCmd( &m_tMainAudioInfo );
	if ( (NO_ERROR != wRet ) )
	{
		WARNMESSAGE("恢复默认主视频配置请求发送失败");
		m_tMainAudioInfo = m_tOldMainAudioInfo;
		return false;
	}	
	return true;
}

bool CCfgMainAudioDlg::OnBtnSave( const IArgs& args )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("有会议进行中，不能配置") );
		OnBtnCancel(args);
		return false;	
	}

	SaveMainAudioInfo( );
	u16 wRet = COMIFMGRPTR->SetMainAudioInfoCmd( &m_tMainAudioInfo );
	if ( (NO_ERROR != wRet ))
	{
		WARNMESSAGE("保存主视频配置请求发送失败");
		return false;
	}
	else
	{
		return true;
	}
}

bool CCfgMainAudioDlg::OnSwitchSynthesis(const IArgs & arg )
{
	bool bImageSynthesis = false;										
	UIFACTORYMGR_PTR->GetSwitchState( m_strImageSynthesis, bImageSynthesis, m_pWndTree );
	if( bImageSynthesis )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCheckBtnOpen", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCheckBtnClose", m_pWndTree );
	}

	bool bChange = false;
	TTPVideoInfoTool tVideoSource;
	
	LIBDATAMGRPTR->GetMainAudioInfo( &tVideoSource );
	if ( (BOOL)bImageSynthesis != tVideoSource.m_bIsH323PipMerge )
	{
		bChange = true;
	}	
	CheckData(m_strImageSynthesis,bChange);
	return true;
}

void CCfgMainAudioDlg::SetMainAudioDate()
{
	vector<CString> vecVideoSource[3];
	vector<CString> vecLargeImage;
	string strType;

	SetVideoSrc1Data();
	SetVideoSrc2Data();
	SetVideoSrc3Data();

	for ( s32 nIndex =0 ; nIndex < (emEndMPCodec-1) ; nIndex++ )
	{
		strType = TransVideoSourceType(m_tMainAudioInfo.m_aemBigVideoSource[nIndex]);
		UIFACTORYMGR_PTR->SetComboText( m_strLargeImage[nIndex], strType, m_pWndTree );
		
		strType = TransVideoSourceType(m_tMainAudioInfo.m_aemMinVideoSource[nIndex]);
		UIFACTORYMGR_PTR->SetComboText( m_strSmallImage[nIndex], strType, m_pWndTree );
	}

	strType = TransResizeModType(m_tMainAudioInfo.m_emVidEncResizeMode);
	UIFACTORYMGR_PTR->SetComboText( m_strLayout, strType, m_pWndTree ); 

	UIFACTORYMGR_PTR->SetSwitchState( m_strImageSynthesis, m_tMainAudioInfo.m_bIsH323PipMerge, m_pWndTree );

	UIFACTORYMGR_PTR->EnableWindow( m_strThreeImage, m_tMainAudioInfo.m_bIsH323PipMerge, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strFourImage, m_tMainAudioInfo.m_bIsH323PipMerge, m_pWndTree );

	if( m_tMainAudioInfo.m_emVideoMergeStyle == em_MERGE_M3 )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strThreeImage, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strFourImage, 0, m_pWndTree );
	}
	else if( m_tMainAudioInfo.m_emVideoMergeStyle == em_MERGE_M4 )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strThreeImage, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strFourImage, 1, m_pWndTree );
	}
	else
	{

	}

}

bool CCfgMainAudioDlg::OnLargeImage1Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	EmTPMtVideoPort emVideoSourceType = GetVideoSourceType(m_strLargeImage[0]);
	UpdateLargeImage(0,emVideoSourceType);
	
	return true;	
}

bool CCfgMainAudioDlg::OnLargeImage2Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	vector<CString> vecSmallImage;
	String strType;
	string strSmallImage;
	
	UIFACTORYMGR_PTR->GetComboText(m_strSmallImage[1],strSmallImage,m_pWndTree );			//更新COMBOX的列表项内容，当前名字会清空
	EmTPMtVideoPort emVideoSourceType = GetVideoSourceType(m_strLargeImage[1]);

	if ( emVideoSourceType == emTPC4Vid )
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecSmallImage.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC4Vid);
		vecSmallImage.push_back(strType.c_str());
		
		UIFACTORYMGR_PTR->SetComboListData( m_strSmallImage[1], vecSmallImage, m_pWndTree ); 
	}
	else if ( emVideoSourceType == emTPC7Vid )
	{
		strType = TransVideoSourceType( emTPC3Vid );
		vecSmallImage.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC7Vid);
		vecSmallImage.push_back(strType.c_str());
		UIFACTORYMGR_PTR->SetComboListData( m_strSmallImage[1], vecSmallImage, m_pWndTree ); 
	}
	else
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecSmallImage.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC4Vid);
		vecSmallImage.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC7Vid);
		vecSmallImage.push_back(strType.c_str());
		
		UIFACTORYMGR_PTR->SetComboListData( m_strSmallImage[1], vecSmallImage, m_pWndTree ); 
	}

	UIFACTORYMGR_PTR->SetComboText( m_strSmallImage[1], strSmallImage, m_pWndTree );

	UpdateLargeImage(1,emVideoSourceType );
	return true;	
}

bool CCfgMainAudioDlg::OnLargeImage3Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	EmTPMtVideoPort emVideoSourceType = GetVideoSourceType(m_strLargeImage[2]);
	UpdateLargeImage(2,emVideoSourceType );
	return true;	
}

bool CCfgMainAudioDlg::UpdateLargeImage( s32 nIndex , EmTPMtVideoPort emVideoSourceType )
{
	bool bChange = false;

	TTPVideoInfoTool tVideoSource;
	LIBDATAMGRPTR->GetMainAudioInfo( &tVideoSource );
	
	if ( tVideoSource.m_aemBigVideoSource[nIndex]  != emVideoSourceType )
	{
		bChange = true;	
	}
	
	CheckData( m_strLargeImage[nIndex],bChange );
	return true;
}

bool CCfgMainAudioDlg::OnSmallImage1Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	EmTPMtVideoPort emVideoSourceType = GetVideoSourceType(m_strSmallImage[0]);
	UpdateSmallImage(0,emVideoSourceType);
	return true;	
}

bool CCfgMainAudioDlg::OnSmallImage2Change( const IArgs& args )
{
	vector<CString> vecLargeImage;
	String strType;
	String strLargeImage;

	if ( m_pWndTree == NULL )
	{
		return false;
	}

	UIFACTORYMGR_PTR->GetComboText(m_strLargeImage[1],strLargeImage,m_pWndTree );
	EmTPMtVideoPort emVideoSourceType = GetVideoSourceType(m_strSmallImage[1]);

	if ( emVideoSourceType == emTPC4Vid )
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecLargeImage.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC4Vid);
		vecLargeImage.push_back(strType.c_str());
		
		UIFACTORYMGR_PTR->SetComboListData( m_strLargeImage[1], vecLargeImage, m_pWndTree ); 
	}
	else if ( emVideoSourceType == emTPC7Vid )
	{
		strType = TransVideoSourceType( emTPC3Vid );
		vecLargeImage.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC7Vid);
		vecLargeImage.push_back(strType.c_str());
		UIFACTORYMGR_PTR->SetComboListData( m_strLargeImage[1], vecLargeImage, m_pWndTree ); 
	}
	else
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecLargeImage.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC4Vid);
		vecLargeImage.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC7Vid);
		vecLargeImage.push_back(strType.c_str());
		
		UIFACTORYMGR_PTR->SetComboListData( m_strLargeImage[1], vecLargeImage, m_pWndTree ); 
	}
	UIFACTORYMGR_PTR->SetComboText( m_strLargeImage[1], strLargeImage, m_pWndTree );

	UpdateSmallImage(1,emVideoSourceType);
	return true;	
}

/*void CCfgMainAudioDlg::SetGroup2ComboData( string strComBobox , EmTPMtVideoPort emChangeVideoSourceType)
{
	String strType;
	vector<CString> vecLargeImage;

	if ( emChangeVideoSourceType == emTPC4Vid )
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecLargeImage.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC4Vid);
		vecLargeImage.push_back(strType.c_str());
		
		UIFACTORYMGR_PTR->SetComboListData( strComBobox, vecLargeImage, m_pWndTree ); 

	}
	else if ( emChangeVideoSourceType == emTPC7Vid )
	{
		strType = TransVideoSourceType( emTPC3Vid );
		vecLargeImage.push_back(strType.c_str());
		
		UIFACTORYMGR_PTR->SetComboListData( strComBobox, vecLargeImage, m_pWndTree ); 
	}
	else
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecLargeImage.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC4Vid);
		vecLargeImage.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC7Vid);
		vecLargeImage.push_back(strType.c_str());
		
		UIFACTORYMGR_PTR->SetComboListData( strComBobox, vecLargeImage, m_pWndTree ); 
	}
}*/

bool CCfgMainAudioDlg::OnSmallImage3Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	EmTPMtVideoPort emVideoSourceType = GetVideoSourceType(m_strSmallImage[2]);
	UpdateSmallImage(2,emVideoSourceType);
	return true;	
}

bool CCfgMainAudioDlg::OnBtnOptRenameDlg( const IArgs& args )
{
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_RenameVideoSource_Click, (WPARAM)m_tMainAudioInfo.m_atVideoSourceName,NULL);
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_strRenameOptDlg );
	
	return true;
}

bool CCfgMainAudioDlg::OnBtnPreview( const IArgs& args )
{
	TTPFtpInfo tTPFtpInfo;
    LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
	if (!tTPFtpInfo.bOpen)
	{
		//增加提示
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "使用快照功能，需开启FTP服务，请确认是否开启？" );	
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
	}
	

	string strFile;
	string setForder;
	
	u16 wRet =  COMIFMGRPTR->SnapShotCmd( );
	if ( wRet != NO_ERROR )
	{
		MSG_BOX_OK("快照请求发送失败！");
		return false;
	}
	UIFACTORYMGR_PTR->LoadScheme("SchmFtpTra",m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme("SchmFtpTra",NULL,g_strMainFrame);

	return true;
}

bool CCfgMainAudioDlg::OnSelSynthesisStyle(const IArgs& args)
{
	EmVidMergeStyle emVideoMergeStyle;
	s32  nCheckState1;
	UIFACTORYMGR_PTR->GetCheckState( m_strFourImage, nCheckState1, m_pWndTree );
	s32  nCheckState2;
	UIFACTORYMGR_PTR->GetCheckState( m_strThreeImage, nCheckState2, m_pWndTree );

	if( 1 == nCheckState1 )
	{
		emVideoMergeStyle = em_MERGE_M4;
	}
	else
	{
		emVideoMergeStyle = em_MERGE_M3;
	}

	bool bChange = false;
	TTPVideoInfoTool tVideoSource;
	
	LIBDATAMGRPTR->GetMainAudioInfo( &tVideoSource );
	if( emVideoMergeStyle != tVideoSource.m_emVideoMergeStyle )
	{
		bChange = true;
	}

	CheckData("VideoMergeStyle", bChange );

	return true;
}

bool CCfgMainAudioDlg::OnLayoutChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	EmVidEncResizeMode emLayoutType = GetResizeModeType(m_strLayout);
	TTPVideoInfoTool tVideoSource;
	LIBDATAMGRPTR->GetMainAudioInfo( &tVideoSource );

	bool bChange = false;
	if ( tVideoSource.m_emVidEncResizeMode != emLayoutType )
	{
		bChange = true;
	}
	CheckData( m_strLayout,bChange );
	return true;	
}

bool CCfgMainAudioDlg::UpdateSmallImage( s32 nIndex ,EmTPMtVideoPort emVideoSourceType )
{
	bool bChange = false;
	
	TTPVideoInfoTool tVideoSource;
	
	LIBDATAMGRPTR->GetMainAudioInfo( &tVideoSource );
	
	if ( tVideoSource.m_aemMinVideoSource[nIndex] != emVideoSourceType )
	{
		bChange = true;	
	}
	
	CheckData( m_strSmallImage[nIndex],bChange );
	return true;
}

EmTPMtVideoPort CCfgMainAudioDlg::GetVideoSourceType( String strCtrl )
{
	String strDisplayType;
	UIFACTORYMGR_PTR->GetComboText( strCtrl, strDisplayType, m_pWndTree );

	for ( s32 nIndex =0; nIndex <= emTPC7Vid ;nIndex ++ )
	{
		if ( strcmp(strDisplayType.c_str(),m_tMainAudioInfo.m_atVideoSourceName[nIndex].m_achSourceName ) == 0  )
		{
			return m_tMainAudioInfo.m_atVideoSourceName[nIndex].m_emPortType;
		}
	}
	return emTPVidEnd;
}

string CCfgMainAudioDlg::TransVideoSourceType( EmTPMtVideoPort emType )
{
	string strType;

	if ( emType > emTPC7Vid )
	{
		return "";
	}
	else
	{
		for ( s32 nIndex =0; nIndex <= emTPC7Vid ;nIndex ++ )
		{
			if ( m_tMainAudioInfo.m_atVideoSourceName[nIndex].m_emPortType == emType )
			{
				strType = m_tMainAudioInfo.m_atVideoSourceName[nIndex].m_achSourceName;
				break;
			}
		}
	}
	
	return strType;
}

string CCfgMainAudioDlg::TransResizeModType( EmVidEncResizeMode emType )
{
	string strType;
	
	switch ( emType )
	{
	case EmTpBlackSide:
		strType = "加黑边等比缩放"; 
		break;
	case EmTpCuttingEdge:
		strType = "裁边等比缩放";
		break;
	case EmTpNonGeometricDrawing:
		strType = "不等比缩放";
		break;
	default:
		strType = "";
	}
	return strType;
}

EmVidEncResizeMode CCfgMainAudioDlg::GetResizeModeType( String strCtrl )
{
	//	TTPVideoInfoTool
	String strResizeModeType;
	UIFACTORYMGR_PTR->GetComboText( strCtrl, strResizeModeType, m_pWndTree );
	
	if ( strResizeModeType.find( "加黑边等比缩放", 0 ) != string::npos )
	{
		return EmTpBlackSide;
	}
	else if ( strResizeModeType.find( "裁边等比缩放", 0 ) != string::npos )
	{
		return EmTpCuttingEdge;
	}
	else
	//else if ( strResizeModeType.find( "不等比缩放", 0 ) != string::npos )
	{
		return EmTpNonGeometricDrawing;
	}
}

void CCfgMainAudioDlg::SetDefVideoSrcInfo()
{
	m_tMainAudioInfo.m_aemBigVideoSource[0] = emTPC1Vid;
	m_tMainAudioInfo.m_aemBigVideoSource[1] = emTPC3Vid;
	m_tMainAudioInfo.m_aemBigVideoSource[2] = emTPC5Vid;
	
	m_tMainAudioInfo.m_aemMinVideoSource[0] = emTPC1Vid;
	m_tMainAudioInfo.m_aemMinVideoSource[1] = emTPC3Vid;
	m_tMainAudioInfo.m_aemMinVideoSource[2] = emTPC5Vid;

	m_tMainAudioInfo.m_bIsH323PipMerge = TRUE;
	m_tMainAudioInfo.m_emVidEncResizeMode = EmTpNonGeometricDrawing;
	m_tMainAudioInfo.m_emVideoMergeStyle = em_MERGE_M4;

//	m_tMainAudioInfo.m_atVideoSourceName[emTPC1Vid] = ;
	m_tMainAudioInfo.m_atVideoSourceName[emTPC1Vid].m_emPortType = emTPC1Vid;
	strcpy(m_tMainAudioInfo.m_atVideoSourceName[emTPC1Vid].m_achSourceName,"主视频1");

	m_tMainAudioInfo.m_atVideoSourceName[emTPC2Vid].m_emPortType = emTPC2Vid;
	strcpy(m_tMainAudioInfo.m_atVideoSourceName[emTPC2Vid].m_achSourceName,"辅视频1");

	m_tMainAudioInfo.m_atVideoSourceName[emTPC3Vid].m_emPortType = emTPC3Vid;
	strcpy(m_tMainAudioInfo.m_atVideoSourceName[emTPC3Vid].m_achSourceName,"主视频2");

	m_tMainAudioInfo.m_atVideoSourceName[emTPC4Vid].m_emPortType = emTPC4Vid;
	strcpy(m_tMainAudioInfo.m_atVideoSourceName[emTPC4Vid].m_achSourceName,"辅视频2");

	m_tMainAudioInfo.m_atVideoSourceName[emTPC5Vid].m_emPortType = emTPC5Vid;
	strcpy(m_tMainAudioInfo.m_atVideoSourceName[emTPC5Vid].m_achSourceName,"主视频3");

	m_tMainAudioInfo.m_atVideoSourceName[emTPC6Vid].m_emPortType = emTPC6Vid;
	strcpy(m_tMainAudioInfo.m_atVideoSourceName[emTPC6Vid].m_achSourceName,"辅视频3");

	m_tMainAudioInfo.m_atVideoSourceName[emTPC7Vid].m_emPortType = emTPC7Vid;
	strcpy(m_tMainAudioInfo.m_atVideoSourceName[emTPC7Vid].m_achSourceName,"全景摄像机");
}

void CCfgMainAudioDlg::SaveMainAudioInfo( )
{
	EmTPMtVideoPort emLargeImageType;
	EmTPMtVideoPort emSmallImageType;
	bool bImageSynthesisSwitch = false;

	for ( s32 nIndex = 0; nIndex <3; nIndex ++ )
	{
		emLargeImageType = GetVideoSourceType(m_strLargeImage[nIndex]);
		m_tMainAudioInfo.m_aemBigVideoSource[nIndex] = emLargeImageType;

		emSmallImageType = GetVideoSourceType(m_strSmallImage[nIndex]);
		m_tMainAudioInfo.m_aemMinVideoSource[nIndex] = emSmallImageType;
	}

	EmVidEncResizeMode  emVidEncResizeMode = GetResizeModeType( m_strLayout );
	m_tMainAudioInfo. m_emVidEncResizeMode = emVidEncResizeMode;
	
	UIFACTORYMGR_PTR->GetSwitchState( m_strImageSynthesis, bImageSynthesisSwitch, m_pWndTree );
	m_tMainAudioInfo.m_bIsH323PipMerge = bImageSynthesisSwitch;

	s32  nCheckState1;
	UIFACTORYMGR_PTR->GetCheckState( m_strFourImage, nCheckState1, m_pWndTree );
	s32  nCheckState2;
	UIFACTORYMGR_PTR->GetCheckState( m_strThreeImage, nCheckState2, m_pWndTree );
	
	if( m_tMainAudioInfo.m_bIsH323PipMerge )
	{
		if( 1 == nCheckState1 )
		{
			m_tMainAudioInfo.m_emVideoMergeStyle = em_MERGE_M4;
		}
		else
		{
			m_tMainAudioInfo.m_emVideoMergeStyle = em_MERGE_M3;
		}
	}
	else
	{
		m_tMainAudioInfo.m_emVideoMergeStyle = em_MERGE_M1;
	}
	
}

void CCfgMainAudioDlg::SetVideoSrc1Data( )
{
	vector<CString> vecVideoSource[3];
	string strType;
	
	strType = TransVideoSourceType(emTPC1Vid);
	vecVideoSource[0].push_back(strType.c_str());
	strType = TransVideoSourceType(emTPC2Vid);
	vecVideoSource[0].push_back(strType.c_str());
	
	UIFACTORYMGR_PTR->SetComboListData( m_strLargeImage[0], vecVideoSource[0], m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboListData( m_strSmallImage[0], vecVideoSource[0], m_pWndTree );
}

void CCfgMainAudioDlg::SetVideoSrc3Data( )
{
	vector<CString> vecVideoSource[3];
	string strType;

	strType = TransVideoSourceType(emTPC5Vid);
	vecVideoSource[2].push_back(strType.c_str());
	strType = TransVideoSourceType(emTPC6Vid);
	vecVideoSource[2].push_back(strType.c_str());
	UIFACTORYMGR_PTR->SetComboListData( m_strLargeImage[2], vecVideoSource[2], m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboListData( m_strSmallImage[2], vecVideoSource[2], m_pWndTree ); 
}

void CCfgMainAudioDlg::SetVideoSrc2Data( )
{
	vector<CString> vecVideoSource;
	string strType;
	
	if ( m_tMainAudioInfo.m_aemBigVideoSource[1] == emTPC7Vid )
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecVideoSource.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC7Vid);
		vecVideoSource.push_back(strType.c_str());
		UIFACTORYMGR_PTR->SetComboListData( m_strSmallImage[1], vecVideoSource, m_pWndTree ); 
	}
	else if ( m_tMainAudioInfo.m_aemBigVideoSource[1] == emTPC4Vid )
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecVideoSource.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC4Vid);
		vecVideoSource.push_back(strType.c_str());
		UIFACTORYMGR_PTR->SetComboListData( m_strSmallImage[1], vecVideoSource, m_pWndTree ); 
	}
	else
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecVideoSource.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC4Vid);
		vecVideoSource.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC7Vid);
		vecVideoSource.push_back(strType.c_str());
		
		UIFACTORYMGR_PTR->SetComboListData( m_strSmallImage[1], vecVideoSource, m_pWndTree ); 
	}
	
	vecVideoSource.clear();
	if ( m_tMainAudioInfo.m_aemMinVideoSource[1] == emTPC4Vid )
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecVideoSource.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC4Vid);
		vecVideoSource.push_back(strType.c_str());
		UIFACTORYMGR_PTR->SetComboListData( m_strLargeImage[1], vecVideoSource, m_pWndTree ); 
	}
	else if ( m_tMainAudioInfo.m_aemMinVideoSource[1] == emTPC7Vid )
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecVideoSource.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC7Vid);
		vecVideoSource.push_back(strType.c_str());
		UIFACTORYMGR_PTR->SetComboListData( m_strLargeImage[1], vecVideoSource, m_pWndTree ); 
	}
	else
	{
		strType = TransVideoSourceType(emTPC3Vid);
		vecVideoSource.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC4Vid);
		vecVideoSource.push_back(strType.c_str());
		strType = TransVideoSourceType(emTPC7Vid);
		vecVideoSource.push_back(strType.c_str());
		
		UIFACTORYMGR_PTR->SetComboListData( m_strLargeImage[1], vecVideoSource, m_pWndTree ); 
	}
}

bool CCfgMainAudioDlg::OnDownloadProgress( const IArgs & arg )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	EmFtpStatus m_emFileFtpStatus;
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);

	if ( m_emFileFtpStatus ==  emFtpEnd )
	{
		DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP接口0为成功  默认失败
		if ( 0 == dwSuccess )
		{
			if ( m_vctDownFile.size() > 0 )
			{
				vector<String>::iterator itr = m_vctDownFile.begin();
				m_vctDownFile.erase(itr);
				u32 nNum= m_vctDownFile.size();
				//CString str;
				//str.Format( "%d / %d", m_nCount-n+1, m_nCount );
				if ( nNum > 0 )
				{
					//UIFACTORYMGR_PTR->SetCaption( "StcFileCount", (LPCSTR)str, m_pWndTree, true );
					DownloadCore( TP_SNAPSHOT_PATH, m_vctDownFile.at(0) );
				}
				else
				{
					KillTimer( m_pWnd->GetSafeHwnd(), g_nSetTimer );
					for ( vector<string> ::size_type nIndex = 0; nIndex < m_vecFilePath.size(); nIndex ++ )
					{
						UIFACTORYMGR_PTR->SetTransStaticImage(m_vecShatShot[nIndex],m_vecFilePath[nIndex],m_pWndTree);
					}
					m_cFtp.EndFtpFile();

					m_bIsUsedGroup1 = !m_bIsUsedGroup1;
					ReleaseSnapImage();														//将没有使用的快照资源释放，供下次使用
					UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
					UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",NULL,g_strMainFrame);
				}
			} 	
		}
		else
		{
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
				OspPrintf( TRUE, FALSE, (char*)strError.c_str() );
				MSG_BOX_OK( strError.c_str() );	
				LocalFree( pszMsg );
			}

			KillTimer( m_pWnd->GetSafeHwnd(), g_nSetTimer );
			m_cFtp.EndFtpFile();
			UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
		}	
	}
	
	return true;
}

void CCfgMainAudioDlg::DownloadOvertime()
{
	KillTimer( m_pWnd->GetSafeHwnd(), g_nSetTimer );
	m_cFtp.EndFtpFile();
	UIFACTORYMGR_PTR->LoadScheme( "SchmFtpEnd", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmFtpEnd", NULL, g_strMainFrame );
}

LRESULT CCfgMainAudioDlg::OnSnapShotNty( WPARAM wparam, LPARAM lparam )
{
	//判断是否开启ftp
	TTPFtpInfo tTPFtpInfo;
    LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
	if (!tTPFtpInfo.bOpen)
	{
		return S_FALSE;
	}

	bool bSuccess = *(bool*)lparam;
	
	if ( bSuccess == false )
	{
		WARNMESSAGE("快照请求失败!");
		UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",NULL,g_strMainFrame);
		UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
		return S_FALSE;
	}

	g_nSetTimer = SetTimer( m_pWnd->GetSafeHwnd(), 1, 15000, OnTimerFunc );
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_FTPSnapDownLoad );
	
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
		
		return S_FALSE;
	}

	if ( m_cFtp.ConnectServer() )
	{
		m_vecFilePath.clear();
		m_vctDownFile.clear();

		if ( m_cFtp.FindfFtpFile( TP_SNAPSHOT_PATH, CNSSNAPSHOT_FILE_NAME1 ) )
		{
			m_vctDownFile.push_back( CNSSNAPSHOT_FILE_NAME1);
		}
		if ( m_cFtp.FindfFtpFile( TP_SNAPSHOT_PATH, CNSSNAPSHOT_FILE_NAME2 ) )
		{
			m_vctDownFile.push_back( CNSSNAPSHOT_FILE_NAME2 );
		}
		if ( m_cFtp.FindfFtpFile( TP_SNAPSHOT_PATH, CNSSNAPSHOT_FILE_NAME3 ) )
		{
			m_vctDownFile.push_back( CNSSNAPSHOT_FILE_NAME3 );
		}
		
		if ( m_vctDownFile.size() > 0 )
		{
			DownloadCore( TP_SNAPSHOT_PATH, m_vctDownFile.at(0) );
		}
	}
	return S_OK;	
}

/*LRESULT CCfgMainAudioDlg::OnViewLocalIPNty(WPARAM wparam, LPARAM lparam)
{
	m_tMainAudioInfo.m_emVideoMergeStyle = *(EmVideoMergeStyle*)(wparam);

	if( m_tMainAudioInfo.m_emVideoMergeStyle == MERGE_M3 )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strThreeImage, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strFourImage, 0, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strThreeImage, 0, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strFourImage, 1, m_pWndTree );
	}
	
	return S_OK;
}*/

BOOL CCfgMainAudioDlg::DownloadCore(const String& strFilePath,const String & strFileName )
{	
	string strForder = "";
	string strSavePath = "";
	string strFileSaveName = "";

	strFileSaveName = GetSnapShotFileName(strFileName);
	strForder = UIFACTORYMGR_PTR->GetImagePath();				//保存的路径
	strSavePath = strForder + CNSSNAPSHOT_FILE_PATH + "\\";
	strSavePath += strFileSaveName;

	if ( !UIDATAMGR_PTR->RecusionMkDir( UIDATAMGR_PTR->GetFileFolderPath(strSavePath).c_str() ))
	{
		MSG_BOX_OK( "创建文件目录失败!" );	
		
		return true;
	}	
	
	string strSrcPath = "";
	strSrcPath += CNSSNAPSHOT_FILE_PATH;						//加载图片的相对路径
	strSrcPath += "\\" + strFileSaveName;
	m_vecFilePath.push_back(strSrcPath.c_str());

	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_FTPSnapDownLoad );

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
		MSG_BOX_OK( "连接服务器失败!" );	
		return false;
	}	
	if ( NULL != m_pWnd )
	{
		String strRemoteFile;
		strRemoteFile += strFilePath + strFileName;
		if ( !m_cFtp.BeginDownload( m_pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, FALSE ) )
		{
			MSG_BOX_OK( "下载快照图片失败，参数错误!" );
			
		//	CCfgMainAudioDlg * pwnd = CCfgMainAudioDlg::GetSingletonPtr();
			UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",NULL,g_strMainFrame);
			UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);

			return false;
		}
	}
	
	return TRUE;
}

void CCfgMainAudioDlg::ReleaseSnapImage()
{
	string strPath = "";
	string strRelFile = "";

	strPath += CNSSNAPSHOT_FILE_PATH;
	strPath += "\\";

	strRelFile = GetSnapShotFileName(CNSSNAPSHOT_FILE_NAME1);
	strRelFile = strPath+strRelFile;
	UIFACTORYMGR_PTR->ReleaseSingleImage(strRelFile);

	strRelFile = GetSnapShotFileName(CNSSNAPSHOT_FILE_NAME2);
	strRelFile = strPath+strRelFile;
	UIFACTORYMGR_PTR->ReleaseSingleImage(strRelFile);

	strRelFile = GetSnapShotFileName(CNSSNAPSHOT_FILE_NAME3);
	strRelFile = strPath+strRelFile;
	UIFACTORYMGR_PTR->ReleaseSingleImage(strRelFile);
}

string CCfgMainAudioDlg::GetSnapShotFileName( const string strFileName )
{
	string strNewName = "";

	if ( m_bIsUsedGroup1 == false )
	{
		strNewName = strFileName;
	}
	else
	{
		strNewName ="temp" + strFileName;
	}

	return strNewName;
}