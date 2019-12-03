// cfgDemonStrationDlg.cpp: implementation of the CCfgDemonStrationDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgDemonStrationDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgDemonStrationDlg::CCfgDemonStrationDlg()
:m_strIdleSwitch("CfgDemonStrationDlg/BtnIdleSwitch")
,m_strConfSwitch("CfgDemonStrationDlg/BtnConfSwitch")
,m_strList("CfgDemonStrationDlg/DemoSourceList")
{
	m_strIdleStrategy[0] = "CfgDemonStrationDlg/CheckBtnOfLeft1";
	m_strIdleStrategy[1] = "CfgDemonStrationDlg/CheckBtnOfMid1";
	m_strIdleStrategy[2] = "CfgDemonStrationDlg/CheckBtnOfRight1";

	m_strConfStrategy[0] = "CfgDemonStrationDlg/CheckBtnOfLeft2";
	m_strConfStrategy[1] = "CfgDemonStrationDlg/CheckBtnOfMid2";
	m_strConfStrategy[2] = "CfgDemonStrationDlg/CheckBtnOfRight2";
}

CCfgDemonStrationDlg::~CCfgDemonStrationDlg()
{

}

void CCfgDemonStrationDlg::RegMsg()
{
	CCfgDemonStrationDlg* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DisplaySource_Nty, CCfgDemonStrationDlg::OnDisplaySourceNty, pThis, CCfgDemonStrationDlg ); 

	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DefaultDisplaySource_Nty, CCfgDemonStrationDlg::OnDefDisplaySourceNty, pThis, CCfgDemonStrationDlg ); 

	REG_MSG_HANDLER( UI_CNSTOOL_MSG_RenameDisplaySource_Nty, CCfgDemonStrationDlg::OnUpdateDisplaySource, pThis, CCfgDemonStrationDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCfgDemonStrationDlg::OnConfStateNty, pThis, CCfgDemonStrationDlg );
    REG_MSG_HANDLER( UI_CNSTOOL_VERINFO_NTY, CCfgDemonStrationDlg::OnVerInfoNty, pThis, CCfgDemonStrationDlg );
}

void CCfgDemonStrationDlg::RegCBFun()
{
	CCfgDemonStrationDlg *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::InitWnd", CCfgDemonStrationDlg::InitWnd, pThis, CCfgDemonStrationDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnBtnIdleSwitch", CCfgDemonStrationDlg::OnBtnIdleSwitch, pThis, CCfgDemonStrationDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnBtnConfSwitch", CCfgDemonStrationDlg::OnBtnConfSwitch, pThis, CCfgDemonStrationDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnBtnOptRenameDlg", CCfgDemonStrationDlg::OnBtnOptRenameDlg, pThis, CCfgDemonStrationDlg );
	
	REG_LIST_CALLFUNC( "CCfgDemonStrationDlg::OnClickVideoSourceList", CCfgDemonStrationDlg::OnClickVideoSourceList, pThis, CCfgDemonStrationDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnBtnDefault", CCfgDemonStrationDlg::OnBtnDefault, pThis, CCfgDemonStrationDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnBtnSetDefault", CCfgDemonStrationDlg::OnBtnSetDefault, pThis, CCfgDemonStrationDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnClickDisplayLstBlack", CCfgDemonStrationDlg::OnClickDisplayLstBlack, pThis, CCfgDemonStrationDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnSelLeft1", CCfgDemonStrationDlg::OnSelLeft1, pThis, CCfgDemonStrationDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnSelMid1", CCfgDemonStrationDlg::OnSelMid1, pThis, CCfgDemonStrationDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnSelRight1", CCfgDemonStrationDlg::OnSelRight1, pThis, CCfgDemonStrationDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnSelLeft2", CCfgDemonStrationDlg::OnSelLeft2, pThis, CCfgDemonStrationDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnSelMid2", CCfgDemonStrationDlg::OnSelMid2, pThis, CCfgDemonStrationDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgDemonStrationDlg::OnSelRight2", CCfgDemonStrationDlg::OnSelRight2, pThis, CCfgDemonStrationDlg );

}

void CCfgDemonStrationDlg::UnRegFunc()
{
	
}

bool CCfgDemonStrationDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	InitCtrlEnable();
	UpBtnState();
	return true;
}


void CCfgDemonStrationDlg::Clear()
{
	memset(&m_tCurSelEntry,0,sizeof(m_tCurSelEntry));
	UIFACTORYMGR_PTR->LoadScheme( "SchVideoSourceListDefault", m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( "CfgDemonStrationDlg/SetDefaultBtn", false, m_pWndTree );
}

HRESULT CCfgDemonStrationDlg::OnDisplaySourceNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	if ( !bSuccess )
	{
		GetDemoStrationData();
		SetDemonStrationDate();
		WARNMESSAGE( "演示源配置失败" );
		return S_FALSE;
	}

	GetDemoStrationData();
	SetDemonStrationDate();
	SetListDate( );
	UIFACTORYMGR_PTR->EnableWindow( "CfgDemonStrationDlg/SetDefaultBtn", false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( "CfgDemonStrationDlg/RenameBtn", true, m_pWndTree );
	return S_OK;
}

HRESULT CCfgDemonStrationDlg::OnDefDisplaySourceNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "恢复默认演示源配置失败" );
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
	}

	GetDemoStrationData();
	SetDemonStrationDate( );
	SetListDate( );
	
	return S_OK;
}

HRESULT CCfgDemonStrationDlg::OnUpdateDisplaySource( WPARAM wparam, LPARAM lparam )
{
	TVgaInfo atDisplaySource[5];
	TTPDualDisplayStrategy tDualDisplayStrategy;
	
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("有会议进行中，不能配置") );
		return false;	
	}

	memcpy(atDisplaySource,(TVgaInfo*)wparam,sizeof(atDisplaySource));

    SaveDemoStrationData(tDualDisplayStrategy);
	u16 wRet = COMIFMGRPTR->SetDemonStrationCmd( atDisplaySource , &tDualDisplayStrategy ,m_emDefault);
	
	if ( NO_ERROR != wRet )
	{
		WARNMESSAGE("重命名演示源请求发送失败");
		return S_FALSE;
	}
	return S_OK;
}

LRESULT CCfgDemonStrationDlg::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	SetDemonStrationDate();
	return S_FALSE;
}

bool CCfgDemonStrationDlg::OnBtnIdleSwitch( const IArgs & arg )
{
	bool bIdle = false;										
	bool bChange = false;
	TTPDualDisplayStrategy tDualDisplayStrategy;
	
	UIFACTORYMGR_PTR->GetSwitchState( m_strIdleSwitch, bIdle, m_pWndTree );

	if ( bIdle == false )
	{
		UIFACTORYMGR_PTR->LoadScheme( "NoDemonstration1", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "Demonstration1", m_pWndTree );

		s32 nCheckState;
		BOOL bCheck = FALSE;
		
		for ( s32 nIndex = 0 ; nIndex < ( emEndMPCodec -1 ) ; nIndex ++ )
		{
			UIFACTORYMGR_PTR->GetCheckState( m_strIdleStrategy[nIndex], nCheckState, m_pWndTree );
			
			if ( nCheckState >0 )
			{
				bCheck = TRUE;
				break;
			}
		}

		if ( bCheck == FALSE )
		{
			UIFACTORYMGR_PTR->SetCheckState( m_strIdleStrategy[1], 1, m_pWndTree );
		}
	}

	SendCommand();
	return true;
}

bool CCfgDemonStrationDlg::OnBtnDefault( const IArgs & arg )
{
	TVgaInfo atDisplaySource[5];
	TTPDualDisplayStrategy tDualDisplayStrategy;
	EmVgaType emDefaultDisplay;
	
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("有会议进行中，不能配置") );
		return false;	
	}

	memcpy(atDisplaySource,m_atDemoSourceName,sizeof(atDisplaySource));
	SetDefaultDemonStration( tDualDisplayStrategy,emDefaultDisplay);
	u16 wRet = COMIFMGRPTR->SetDefaultDemonStrationCmd( m_atDemoSourceName , &tDualDisplayStrategy ,emDefaultDisplay);

	memcpy(m_atDemoSourceName,atDisplaySource,sizeof(atDisplaySource));
	if ( NO_ERROR != wRet )
	{
		WARNMESSAGE("恢复默认演示源请求发送失败");
		return false;
	}
	return true;
}

bool CCfgDemonStrationDlg::OnBtnSetDefault( const IArgs & arg )
{
	if ( strcmp( m_tCurSelEntry.m_tDisplaySourceInfo.m_achAlias,"" ) == 0 )
	{
		return false;
	}

	TVgaInfo atDisplaySource[5];
	TTPDualDisplayStrategy tDualDisplayStrategy;
	EmVgaType  emDefault =m_tCurSelEntry.m_tDisplaySourceInfo.m_emVgaType;

	SaveDemoStrationData(tDualDisplayStrategy);
	u16 wRet = COMIFMGRPTR->SetDemonStrationCmd( m_atDemoSourceName , &tDualDisplayStrategy ,emDefault );
	
	if ( NO_ERROR != wRet )
	{
		WARNMESSAGE("设置默认请求发送失败");
	}

	return true;
}

bool CCfgDemonStrationDlg::OnSelLeft1( const IArgs & arg )
{
	if ( CheckIdleStrategy() == FALSE )
	{
		UIFACTORYMGR_PTR->SetSwitchState(m_strIdleSwitch,false,m_pWndTree );
	}
	SendCommand();
	return true;
}

bool CCfgDemonStrationDlg::OnSelMid1( const IArgs & arg )
{
	if ( CheckIdleStrategy() == FALSE )
	{
		UIFACTORYMGR_PTR->SetSwitchState(m_strIdleSwitch,false,m_pWndTree );
	}

	SendCommand();
	return true;
}

bool CCfgDemonStrationDlg::OnSelRight1( const IArgs & arg )
{
	if ( CheckIdleStrategy() == FALSE )
	{
		UIFACTORYMGR_PTR->SetSwitchState(m_strIdleSwitch,false,m_pWndTree );
	}

	SendCommand();
	return true;
}

bool CCfgDemonStrationDlg::OnSelLeft2( const IArgs & arg )
{
	if ( CheckConfStrategy() == FALSE )
	{
		UIFACTORYMGR_PTR->SetSwitchState(m_strConfSwitch,false,m_pWndTree );
	}
	SendCommand();
	return true;
}

bool CCfgDemonStrationDlg::OnSelMid2( const IArgs & arg )
{
	if ( CheckConfStrategy() == FALSE )
	{
		UIFACTORYMGR_PTR->SetSwitchState(m_strConfSwitch,false,m_pWndTree );
	}
	SendCommand();
	return true;
}

bool CCfgDemonStrationDlg::OnSelRight2( const IArgs & arg )
{
	if ( CheckConfStrategy() == FALSE )
	{
		UIFACTORYMGR_PTR->SetSwitchState(m_strConfSwitch,false,m_pWndTree );
	}
	SendCommand();
	return true;
}

bool CCfgDemonStrationDlg::OnBtnConfSwitch( const IArgs & arg )
{
	bool bConfernce = false;										
	bool bChange = false;
	TTPDualDisplayStrategy tDualDisplayStrategy;
	
	UIFACTORYMGR_PTR->GetSwitchState( m_strConfSwitch, bConfernce, m_pWndTree );
	
	if ( bConfernce == false )
	{
		UIFACTORYMGR_PTR->LoadScheme( "NoDemonstration2", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "Demonstration2", m_pWndTree );

		s32 nCheckState;
		BOOL bCheck = FALSE;
		
		for ( s32 nIndex = 0 ; nIndex < ( emEndMPCodec -1 ) ; nIndex ++ )
		{
			UIFACTORYMGR_PTR->GetCheckState( m_strConfStrategy[nIndex], nCheckState, m_pWndTree );
			
			if ( nCheckState >0 )
			{
				bCheck = TRUE;
				break;
			}
		}
		
		if ( bCheck == FALSE )
		{
			UIFACTORYMGR_PTR->SetCheckState( m_strConfStrategy[0], 1, m_pWndTree );
			UIFACTORYMGR_PTR->SetCheckState( m_strConfStrategy[1], 1, m_pWndTree );
			UIFACTORYMGR_PTR->SetCheckState( m_strConfStrategy[2], 1, m_pWndTree );
		}
	}

	SendCommand();
	return true;
}

bool CCfgDemonStrationDlg::OnBtnOptRenameDlg( const IArgs& args )
{
	if ( strcmp( m_tCurSelEntry.m_tDisplaySourceInfo.m_achAlias,"" ) == 0 )
	{
		CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_ReDisplaySrc_Click, (WPARAM)m_atDemoSourceName,NULL);
	}
	else
	{
		CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_ReDisplaySrc_Click, (WPARAM)m_atDemoSourceName,(LPARAM)&( m_tCurSelEntry.m_tDisplaySourceInfo ));
	}
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_strRenameOptDlg );
	
	return true;
}

bool CCfgDemonStrationDlg::OnClickVideoSourceList( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
		if ( const Data_DisplaySource * pDataTemp = dynamic_cast< const Data_DisplaySource*>(pIData) )
		{
			m_tCurSelEntry = pDataTemp->m_tDisplaySource;
			if ( m_tCurSelEntry.m_bDefault == false )
			{
				UIFACTORYMGR_PTR->EnableWindow( "CfgDemonStrationDlg/SetDefaultBtn", true, m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->EnableWindow( "CfgDemonStrationDlg/SetDefaultBtn", false, m_pWndTree );
			}
		}
	}
	return true;
}

bool CCfgDemonStrationDlg::OnClickDisplayLstBlack( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	UIFACTORYMGR_PTR->EnableWindow( "CfgDemonStrationDlg/SetDefaultBtn", false, m_pWndTree );
	memset(&m_tCurSelEntry,0,sizeof(m_tCurSelEntry));
	return true;
}

void CCfgDemonStrationDlg::InitCtrlEnable()
{
	UIFACTORYMGR_PTR->SetSwitchState( m_strIdleSwitch, false, m_pWndTree);
	
	UIFACTORYMGR_PTR->SetSwitchState( m_strConfSwitch, false, m_pWndTree);
	
	UIFACTORYMGR_PTR->EnableWindow( "CfgDemonStrationDlg/RenameBtn", false, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( "CfgDemonStrationDlg/SetDefaultBtn", false, m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "NoDemonstration1", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "NoDemonstration2", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchVideoSourceListDefault", m_pWndTree );
}

void CCfgDemonStrationDlg::GetDemoStrationData()
{
	TVgaInfo * ptDisplaySource = NULL;
	
	LIBDATAMGRPTR->GetDisplaySourceList( &ptDisplaySource );
	LIBDATAMGRPTR->GetDisplayStrategy( &m_tDualDisplayStrategy );
	LIBDATAMGRPTR->GetDefaultDisplay(&m_emDefault );
	
	memcpy(m_atDemoSourceName,ptDisplaySource,sizeof(m_atDemoSourceName));
}

void CCfgDemonStrationDlg::SetDemonStrationDate( )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();

	UIFACTORYMGR_PTR->SetSwitchState( m_strIdleSwitch, 
		m_tDualDisplayStrategy.m_tOnIdle.m_bIsAutoDisPlay, m_pWndTree);
	
	UIFACTORYMGR_PTR->SetSwitchState( m_strConfSwitch, 
		m_tDualDisplayStrategy.m_tOnConf.m_bIsAutoDisPlay, m_pWndTree);
	
	for ( s32 nIndex = 0 ; nIndex < ( emEndMPCodec -1 ) ; nIndex ++ )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strIdleStrategy[nIndex],
			m_tDualDisplayStrategy.m_tOnIdle.m_abIsScreensDisPlay[nIndex]);
		
		UIFACTORYMGR_PTR->SetCheckState( m_strConfStrategy[nIndex],
			m_tDualDisplayStrategy.m_tOnConf.m_abIsScreensDisPlay[nIndex]);
	}	

	if ( bInConf == TRUE )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmInConf", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmLeaveConf", m_pWndTree );
	}

	if ( ( bInConf == FALSE ) && ( m_tDualDisplayStrategy.m_tOnIdle.m_bIsAutoDisPlay == FALSE ))
	{
		UIFACTORYMGR_PTR->LoadScheme( "NoDemonstration1", m_pWndTree );
	}
	
	if ( ( bInConf == FALSE ) && ( m_tDualDisplayStrategy.m_tOnConf.m_bIsAutoDisPlay == FALSE ))
	{
		UIFACTORYMGR_PTR->LoadScheme( "NoDemonstration2", m_pWndTree );
	}
}

void CCfgDemonStrationDlg::SendCommand()
{
	TVgaInfo atDisplaySource[5];
	TTPDualDisplayStrategy tDualDisplayStrategy;
	
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("有会议进行中，不能配置") );
		return;	
	}

	SaveDemoStrationData(tDualDisplayStrategy);
	u16 wRet = COMIFMGRPTR->SetDemonStrationCmd( m_atDemoSourceName , &tDualDisplayStrategy ,m_emDefault );
	
	if ( NO_ERROR != wRet )
	{
		WARNMESSAGE("设置请求发送失败");
	}
}

void CCfgDemonStrationDlg::SetListDate( )
{
	vector<Value_DisplaySrc::TDisplaySrcData> vecTDisplaySource;
	Value_DisplaySrc::TDisplaySrcData tDisplayData;
	
	for ( s32 nNum = 0; nNum < 5; nNum ++ )
	{
		tDisplayData.m_tDisplaySourceInfo = m_atDemoSourceName[nNum];
		if ( m_atDemoSourceName[nNum].m_emVgaType == m_emDefault )
		{
			tDisplayData.m_bDefault = true;
		}
		else
		{
			tDisplayData.m_bDefault = false;
		}
		vecTDisplaySource.push_back(tDisplayData);
	}

	SoftDemoStrationData(vecTDisplaySource);
	
	Value_DisplaySrc CVideoSource( &vecTDisplaySource );
	UIFACTORYMGR_PTR->SetPropertyValue( CVideoSource, "DemonStrationDlg/DemoSourceList", m_pWndTree);
}

void CCfgDemonStrationDlg::SoftDemoStrationData( vector<Value_DisplaySrc::TDisplaySrcData> &vecTDisplaySource )
{
    EmCnModel emCnModel = emUnknownCnModel;
    LIBDATAMGRPTR->GetEmCnModelInfo( &emCnModel );
    if (emCnModel == T300E_4K)
    {
        SwapDemoSourceData(0,emVgaTypeFullScreenCamera,vecTDisplaySource);
        SwapDemoSourceData(1,emVgaTypeDocCamera,vecTDisplaySource);
        SwapDemoSourceData(2,emVgaType001,vecTDisplaySource);
        //SwapDemoSourceData(3,emVgaType002,vecTDisplaySource);
        //去除演示源2和3
        if (vecTDisplaySource.size() == 5)
        {
            vecTDisplaySource.pop_back();
            vecTDisplaySource.pop_back();
        }  
    }
    else
    {
        SwapDemoSourceData(0,emVgaTypeDocCamera,vecTDisplaySource);
        SwapDemoSourceData(1,emVgaType001,vecTDisplaySource);
        SwapDemoSourceData(2,emVgaType002,vecTDisplaySource);
        SwapDemoSourceData(3,emVgaType003,vecTDisplaySource);
	    SwapDemoSourceData(4,emVgaTypeFullScreenCamera,vecTDisplaySource);
    }
}

void CCfgDemonStrationDlg::SetDefaultDemonStration( TTPDualDisplayStrategy & tDualDisplayStrategy, EmVgaType &emDefaultDisplay )
{
	tDualDisplayStrategy.m_tOnIdle.m_bIsAutoDisPlay= TRUE;
	tDualDisplayStrategy.m_tOnIdle.m_abIsScreensDisPlay[0]= FALSE;
	tDualDisplayStrategy.m_tOnIdle.m_abIsScreensDisPlay[1]= TRUE;
	tDualDisplayStrategy.m_tOnIdle.m_abIsScreensDisPlay[2]= FALSE;

	tDualDisplayStrategy.m_tOnConf.m_bIsAutoDisPlay= TRUE;
	tDualDisplayStrategy.m_tOnConf.m_abIsScreensDisPlay[0]= TRUE;
	tDualDisplayStrategy.m_tOnConf.m_abIsScreensDisPlay[1]= TRUE;
	tDualDisplayStrategy.m_tOnConf.m_abIsScreensDisPlay[2]= TRUE;

	m_atDemoSourceName[0].m_emVgaType = emVgaTypeFullScreenCamera;
	strcpy(m_atDemoSourceName[0].m_achAlias,"全景摄像机");
	
	m_atDemoSourceName[1].m_emVgaType = emVgaType001;
	strcpy(m_atDemoSourceName[1].m_achAlias,"演示源 1");

	m_atDemoSourceName[2].m_emVgaType = emVgaType002;
	strcpy(m_atDemoSourceName[2].m_achAlias,"演示源 2");

	m_atDemoSourceName[3].m_emVgaType = emVgaType003;
	strcpy(m_atDemoSourceName[3].m_achAlias,"演示源 3");

	m_atDemoSourceName[4].m_emVgaType = emVgaTypeDocCamera;
	strcpy(m_atDemoSourceName[4].m_achAlias,"文档摄像机");

	emDefaultDisplay = emVgaTypeDocCamera;
}

void CCfgDemonStrationDlg::SwapDemoSourceData( s32 nNum  ,EmVgaType emType ,
											  vector<Value_DisplaySrc::TDisplaySrcData> &vecTDisplaySource )
{
	for ( s32 nIndex =0; nIndex < emVgaTypeInValid ;nIndex ++ )
	{
		if ( vecTDisplaySource[nIndex].m_tDisplaySourceInfo.m_emVgaType == emType )
		{
			if ( nIndex != nNum )
			{
				Value_DisplaySrc::TDisplaySrcData tTempVideoSourceInfo;
				tTempVideoSourceInfo = vecTDisplaySource[nIndex];
				vecTDisplaySource[nIndex] = vecTDisplaySource[nNum];
				vecTDisplaySource[nNum] = tTempVideoSourceInfo;
			}
			break;
		}
	}
}

void CCfgDemonStrationDlg::SaveDemoStrationData( TTPDualDisplayStrategy &tDualDisplayStrategy )
{
	bool bState;
	s32 nCheckState;

	for ( s32 nIndex = 0 ; nIndex < ( emEndMPCodec -1 ) ; nIndex ++ )
	{
		UIFACTORYMGR_PTR->GetCheckState( m_strIdleStrategy[nIndex], nCheckState, m_pWndTree );
		tDualDisplayStrategy.m_tOnIdle.m_abIsScreensDisPlay[nIndex] = ( ( nCheckState >0 )? TRUE :FALSE );
/*		if ( nCheckState >0 )
		{
			tDualDisplayStrategy.m_tOnIdle.m_abIsScreensDisPlay[nIndex] = TRUE;
		}
		else
		{
			tDualDisplayStrategy.m_tOnIdle.m_abIsScreensDisPlay[nIndex] = FALSE;
		}
*/	
		UIFACTORYMGR_PTR->GetCheckState( m_strConfStrategy[nIndex], nCheckState, m_pWndTree );
		tDualDisplayStrategy.m_tOnConf.m_abIsScreensDisPlay[nIndex] = ( ( nCheckState >0 )? TRUE :FALSE );
	}

	UIFACTORYMGR_PTR->GetSwitchState(m_strIdleSwitch,bState,m_pWndTree );
	tDualDisplayStrategy.m_tOnIdle.m_bIsAutoDisPlay = ( ( bState == false)? FALSE:TRUE );

	UIFACTORYMGR_PTR->GetSwitchState(m_strConfSwitch,bState,m_pWndTree );
	tDualDisplayStrategy.m_tOnConf.m_bIsAutoDisPlay = ( ( bState == false)? FALSE:TRUE );
}

BOOL CCfgDemonStrationDlg::CheckIdleStrategy( )
{
	s32 nCheckState;
//	BOOL bCheck = FALSE;

	for ( s32 nIndex = 0 ; nIndex < ( emEndMPCodec -1 ) ; nIndex ++ )
	{
		UIFACTORYMGR_PTR->GetCheckState( m_strIdleStrategy[nIndex], nCheckState, m_pWndTree );

		if ( nCheckState >0 )
		{
			return TRUE;
		}
	}
	return FALSE;
/*	if ( bCheck == FALSE )
	{
		UIFACTORYMGR_PTR->SetSwitchState(m_strIdleSwitch,false,m_pWndTree );
	}*/
}

BOOL CCfgDemonStrationDlg::CheckConfStrategy( )
{
	s32 nCheckState;
//	BOOL bCheck = FALSE;
	
	for ( s32 nIndex = 0 ; nIndex < ( emEndMPCodec -1 ) ; nIndex ++ )
	{
		UIFACTORYMGR_PTR->GetCheckState( m_strConfStrategy[nIndex], nCheckState, m_pWndTree );
		
		if ( nCheckState >0 )
		{
			return TRUE;
			break;
		}
	}
	
	return FALSE;
/*	if ( bCheck == FALSE )
	{
		UIFACTORYMGR_PTR->SetSwitchState(m_strConfSwitch,false,m_pWndTree );
	}*/
}

LRESULT CCfgDemonStrationDlg::OnVerInfoNty( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree == NULL )
    {
        return S_FALSE;
    }
    
    EmCnModel emCnModel;
    LIBDATAMGRPTR->GetEmCnModelInfo( &emCnModel );

    if (emCnModel == T300E_4K)
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchModelT300E_4K", m_pWndTree );
    }
    else
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchModelNonT300E_4K", m_pWndTree );

    }

    return S_OK;
}
