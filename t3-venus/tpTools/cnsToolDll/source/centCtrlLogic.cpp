// centCtrlLogic.cpp: implementation of the CCentCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centCtrlLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//状态信息
CCentCfgStatusMesDlg::CCentCfgStatusMesDlg()
{
	
}

CCentCfgStatusMesDlg::~CCentCfgStatusMesDlg()
{
	
}

void CCentCfgStatusMesDlg::RegCBFun()
{
	CCentCfgStatusMesDlg *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgStatusMesDlg::InitWnd", CCentCfgStatusMesDlg::InitWnd, pThis, CCentCfgStatusMesDlg );
}

void CCentCfgStatusMesDlg::RegMsg()
{
	CCentCfgStatusMesDlg *pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CamPowerState_NTY, CCentCfgStatusMesDlg::OnCameraInfoNty, pThis, CCentCfgStatusMesDlg );
	REG_MSG_HANDLER( UI_CNS_DCAMSTATE_NTY, CCentCfgStatusMesDlg::OnDocCamInfoNty, pThis, CCentCfgStatusMesDlg );
	REG_MSG_HANDLER( UI_CNS_TVSTATE_NTY, CCentCfgStatusMesDlg::OnDisplayInfoNty, pThis, CCentCfgStatusMesDlg );
	REG_MSG_HANDLER( UI_CNS_ACSTATE_NTY, CCentCfgStatusMesDlg::OnUpdateAirInfoNty, pThis, CCentCfgStatusMesDlg );
	REG_MSG_HANDLER( UI_CNS_SCHSTATE_NTY, CCentCfgStatusMesDlg::OnLightInfoNty, pThis, CCentCfgStatusMesDlg );
	REG_MSG_HANDLER( UI_CNS_SCHTEMP_NTY, CCentCfgStatusMesDlg::OnAirInfoNty, pThis, CCentCfgStatusMesDlg );		//空调消息通过灯光消息传过来
}

void CCentCfgStatusMesDlg::UnRegFunc()
{
	
}

bool CCentCfgStatusMesDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	string strstate("关");
	string strShotDown("关机");
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateofXinFeng", "关闭", NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcAirConditionState", strShotDown, NULL, TRUE);
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight1", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight2", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight3", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight4", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight5", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight6", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight7", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight8", strstate, NULL, TRUE);
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfDisplay1", strShotDown, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfDisplay2", strShotDown, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfDisplay3", strShotDown, NULL, TRUE);
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera1", strShotDown, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera2", strShotDown, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera3", strShotDown, NULL, TRUE);
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfDocCamera", strShotDown, NULL, TRUE);
	return true;
}

void CCentCfgStatusMesDlg::Clear()
{
	
}

LRESULT CCentCfgStatusMesDlg::OnCameraInfoNty( WPARAM wParam, LPARAM lParam )
{
	EmCamPowerMode aemCam[MAX_CNCAMERA_NUM];
	for (int i=0;i<3;i++)
	{
		aemCam[i] =  *((EmCamPowerMode*)wParam + i);
	}
	
	String strCamera1Info;
	strCamera1Info += CamStateToString(aemCam[0]);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera1", strCamera1Info, NULL, TRUE );
	
	String strCamera2Info;
	strCamera2Info += CamStateToString(aemCam[1]);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera2", strCamera2Info, NULL, TRUE );
	
	String strCamera3Info;
	strCamera3Info += CamStateToString(aemCam[2]);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera3", strCamera3Info, NULL, TRUE);
	
	return S_OK;
}

String CCentCfgStatusMesDlg::CamStateToString( EmCamPowerMode& emSwitchState )
{
	String strState;
	switch(emSwitchState)
	{
	case emCamPowerOn:
		strState = "开机";
		break;
	case emCamPowerOff:
		strState = "待机";
		break;
	default:
		strState = "关机";
		break;
	}
	return strState;
}

LRESULT CCentCfgStatusMesDlg::OnDocCamInfoNty( WPARAM wParam, LPARAM lParam )
{
	String strState;
	TCentreDCamCfg tDCamCfg = *(TCentreDCamCfg*)wParam;
	
	String strDocCamera;
	
	switch(tDCamCfg.emDCamPowerMode)
	{
	case emDCamPowerOn:
		strState = "开机";
		break;
	case emDCamPowerOff:
		strState = "关机";
		break;
	case emDCamPowerToggle:
		strState = "待机";
		break;
	default:
		strState = "关闭";
	}
	strDocCamera += strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfDocCamera", strDocCamera, NULL, TRUE );
	
	return S_OK;
}

LRESULT CCentCfgStatusMesDlg::OnDisplayInfoNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	TCentreTVCfg atCentreTVCfg[MAX_CENTRETV_NUM];
	memcpy( atCentreTVCfg, LIBDATAMGRPTR->GetCentreTVCfg(), sizeof(atCentreTVCfg)) ;
	
	String strDisplay1Info;
	strDisplay1Info += StateToString(atCentreTVCfg[0].emTvPowerMode);
	UIFACTORYMGR_PTR->SetCaption("CentCfgStatusMesDlg/StcStateOfDisplay1", strDisplay1Info, NULL, TRUE);
	
	String strDisplay2Info;
	strDisplay2Info += StateToString(atCentreTVCfg[1].emTvPowerMode);
	UIFACTORYMGR_PTR->SetCaption("CentCfgStatusMesDlg/StcStateOfDisplay2", strDisplay2Info, NULL, TRUE);
	
	String strDisplay3Info;
	strDisplay3Info += StateToString(atCentreTVCfg[2].emTvPowerMode);
	UIFACTORYMGR_PTR->SetCaption("CentCfgStatusMesDlg/StcStateOfDisplay3", strDisplay3Info, NULL, TRUE);
	
	return S_OK;
}

String CCentCfgStatusMesDlg::StateToString( EmTvPowerMode& emSwitchState )
{
	String strState;
	switch(emSwitchState)
	{
	case emTVPowerON:
		strState = "开机";
		break;
	case emTVPowerOFF:
		strState = "待机";
		break;
	case emTVPowerDown:
		strState = "关机";
		break;
	default:
		strState = "关机";
		break;
	}
	return strState;
}

LRESULT CCentCfgStatusMesDlg::OnUpdateAirInfoNty( WPARAM wParam, LPARAM lParam )
{
	vector<TCentreACCfg> vecCentreAcCfg;
	LIBDATAMGRPTR->GetCentreACCfg(vecCentreAcCfg);
	if ( vecCentreAcCfg.size() > 0 )
	{
		String strAirInfo;
		s8 chAirTemP[8] = {0};
		sprintf( chAirTemP, "%u", vecCentreAcCfg[0].bySetTemp );
		strAirInfo += chAirTemP;
		strAirInfo += "℃";
		
		UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcAirConditionState", "开机", NULL, TRUE);
		UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcTemperateDeg",strAirInfo, NULL, TRUE);
		if ( vecCentreAcCfg[0].emACMode == emCenACChaAir )
		{
			UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateofXinFeng", "开启", NULL, TRUE);
		}
		else
		{
			UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateofXinFeng", "关闭", NULL, TRUE);
		}
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcAirConditionState", "关机", NULL, TRUE);
		UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateofXinFeng", "关闭", NULL, TRUE);
	}
	
	return S_OK;
}

LRESULT CCentCfgStatusMesDlg::OnLightInfoNty( WPARAM wParam, LPARAM lParam )
{
	TCentreSchCfg tSchCfg = *(TCentreSchCfg*)wParam;
	//当前不能获得空调开关,只有温度
	String strAirInfo;	
	s8 chAirTemP[8] = {0};
	sprintf( chAirTemP, "%u", tSchCfg.wSchTem );
	strAirInfo += chAirTemP;
	strAirInfo += "℃";
	String strState;

	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcTemperateDeg", strAirInfo, NULL, TRUE);
	
	//设置灯光状态信息

	String strLight1, strLight2, strLight3, strLight4, strLight5, strLight6, strLight7, strLight8;
	switch( tSchCfg.emSchMidLight )
	{
	case emSchMidLightOn:
		strLight1 += "开";
		break;
	case emSchMidLightOff:
		strLight1 += "关";
		break;
	case emSchMidLightInvalid:
		strLight1 += "关";
		break;
	default:
		break;
	}

//	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcLight1", "顶灯 ：", NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight1", strLight1, NULL, TRUE);

	switch( tSchCfg.emSchScrLight )
	{
	case emSchScrLightOn:
		strLight2 += "开";
		break;
	case emSchScrLightOff:
		strLight2 += "关";
		break;
	case emSchScrLightInvalid:
		strLight2 += "关";
		break;
	default:
		break;
	}

//	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcLight2", "机柜灯 ：", NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight2", strLight2, NULL, TRUE);
	
	switch( tSchCfg.emSchLight )
	{
	case emSchLightOn:
		strState += "开";
		break;
	case emSchLightOff:
		strState += "关";
		break;
	case emSchLightInvalid:
		strState += "关";
		break;
	default:
		break;
	}

	strLight3 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight3", strLight3, NULL, TRUE);
	strLight4 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight4", strLight4, NULL, TRUE);
	strLight5 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight5", strLight5, NULL, TRUE);
/*	strLight6 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight6", strLight6, NULL, TRUE);
	strLight7 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight7", strLight7, NULL, TRUE);
	strLight8 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight8", strLight8, NULL, TRUE);*/
	//Value_ItemLight LightState( &tSchCfg );
	//UIFACTORYMGR_PTR->SetPropertyValue( LightState, "CentCfgLightDlg/StcTPbg", NULL );	
	return S_OK;
}

LRESULT CCentCfgStatusMesDlg::OnAirInfoNty( WPARAM wParam, LPARAM lParam )
{
//	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcAirConditionState", "开机", NULL, TRUE);
	u16 wSchTem = (u16)wParam;
    //当前不能获得空调开关,只有温度
	String strAirInfo = "";
	
	s8 chAirTemP[8] = {0};
	sprintf( chAirTemP, "%u", wSchTem );
	strAirInfo += chAirTemP;
	strAirInfo += "℃";
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcTemperateDeg", strAirInfo, NULL, TRUE);
	return S_OK;
}

//窗帘
CCentCfgCurtainDlg::CCentCfgCurtainDlg()
{
	
}

CCentCfgCurtainDlg::~CCentCfgCurtainDlg()
{
	
}

void CCentCfgCurtainDlg::RegMsg()
{
	CCentCfgCurtainDlg* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_TPAD_CURTAINSTATE_NTY, CCentCfgCurtainDlg::OnUpdateCurNty, pThis, CCentCfgCurtainDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_CENTRE_CurRename_Nty, CCentCfgCurtainDlg::OnUpdateCurName, pThis, CCentCfgCurtainDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_CENTRE_CurOpen_Nty, CCentCfgCurtainDlg::OnCurtainInd, pThis, CCentCfgCurtainDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_CENTRE_CurNumSet_Nty, CCentCfgCurtainDlg::OnCurtainNumInd, pThis, CCentCfgCurtainDlg ); 
}

void CCentCfgCurtainDlg::RegCBFun()
{
	CCentCfgCurtainDlg *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgCurtainDlg::InitWnd", CCentCfgCurtainDlg::InitWnd, pThis, CCentCfgCurtainDlg );

	REG_LIST_CALLFUNC( "CCentCfgCurtainDlg::OnClickCurList", CCentCfgCurtainDlg::OnClickCurList, pThis, CCentCfgCurtainDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCurtainDlg::OnBtnOptRenameDlg", CCentCfgCurtainDlg::OnBtnOptRenameDlg, pThis, CCentCfgCurtainDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCurtainDlg::OnCurNumCfg", CCentCfgCurtainDlg::OnCurNumCfg, pThis, CCentCfgCurtainDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCurtainDlg::OnBtnSwitchCurtain", CCentCfgCurtainDlg::OnBtnSwitchCurtain, pThis, CCentCfgCurtainDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCurtainDlg::OnClickCurLstBlack", CCentCfgCurtainDlg::OnClickCurLstBlack, pThis, CCentCfgCurtainDlg );
}

void CCentCfgCurtainDlg::UnRegFunc()
{
	
}

bool CCentCfgCurtainDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	CString strCurId;

	m_nSelIndex = -1;
	vector<CString> vecCurtainName;
	for ( s32 nIndex = 0 ; nIndex < MAX_CURTAIN_NUM  ; nIndex ++ )
	{
		strCurId.Format( "%d",nIndex+1);
		vecCurtainName.push_back( strCurId);
	}

	UIFACTORYMGR_PTR->SetComboListData( "CentCfgCurtainDlg/ComboboxCurNum", vecCurtainName, m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme("SchmCurDefault",m_pWndTree);
	return true;
}

void CCentCfgCurtainDlg::SetDefaultCurName( )
{
	StrCpy(m_tTempCenCurInfo.tCenCurName[0].achCurName,"窗帘1");
	StrCpy(m_tTempCenCurInfo.tCenCurName[1].achCurName,"窗帘2");
	StrCpy(m_tTempCenCurInfo.tCenCurName[2].achCurName,"窗帘3");
	StrCpy(m_tTempCenCurInfo.tCenCurName[3].achCurName,"窗帘4");
	StrCpy(m_tTempCenCurInfo.tCenCurName[4].achCurName,"窗帘5");
	StrCpy(m_tTempCenCurInfo.tCenCurName[5].achCurName,"窗帘6");
}

void CCentCfgCurtainDlg::Clear()
{
	m_nSelIndex = -1;
	UIFACTORYMGR_PTR->LoadScheme("SchmCurDefault",m_pWndTree);
}

bool CCentCfgCurtainDlg::OnBtnSwitchCurtain( const IArgs& args )
{
	string strCurtainNum;
	bool bOpen;

	UIFACTORYMGR_PTR->GetSwitchState("CentCfgCurtainDlg/CurtainSwitch",bOpen,m_pWndTree);

	u16 nRet = COMIFMGRPTR->SetCurtainOpenCmd( bOpen == true ? TRUE : FALSE );

	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "窗帘开启请求发送失败" );
		UIFACTORYMGR_PTR->SetSwitchState("CentCfgCurtainDlg/CurtainSwitch",!bOpen,m_pWndTree);
	}

//	UIFACTORYMGR_PTR->LoadScheme( "SchmCurExist", m_pWndTree );
	//if ()
	return true;
}

bool CCentCfgCurtainDlg::OnBtnOptRenameDlg( const IArgs& args )
{
	if ( (m_tCentreCurInfo.byCurNum < 1 ) || (m_tCentreCurInfo.byCurNum > MAX_CURTAIN_NUM) || ( m_nSelIndex >= MAX_CURTAIN_NUM ))
	{
		return false;
	}

	if ( m_nSelIndex >= 0 )
	{
		CMsgDispatch::SendMessage( UI_CNSTOOL_CurtainRename_Nty, (WPARAM)&m_tCentreCurInfo,(LPARAM)&m_nSelIndex);
	}
	else
	{
		CMsgDispatch::SendMessage( UI_CNSTOOL_CurtainRename_Nty, (WPARAM)&m_tCentreCurInfo,NULL);
	}

	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_strRenameOptDlg );

	return true;
}

bool CCentCfgCurtainDlg::OnCurNumCfg( const IArgs& args )
{
	string strCurNum;
	u8	   byCurNumber;
	s8	   chValue[5] = "";

	UIFACTORYMGR_PTR->GetComboText("CentCfgCurtainDlg/ComboboxCurNum",strCurNum,m_pWndTree );
	byCurNumber = atoi(strCurNum.c_str());

	u16 nRet = COMIFMGRPTR->SetCurtainNumber( byCurNumber );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "窗帘数量设置请求发送失败" );
		itoa(m_tCentreCurInfo.byCurNum +1,chValue,10);
		UIFACTORYMGR_PTR->SetComboText( "CentCfgCurtainDlg/ComboboxCurNum",chValue,m_pWndTree );
	}	
	return true;
}

HRESULT CCentCfgCurtainDlg::OnUpdateCurNty( WPARAM wparam, LPARAM lparam )
{
	TCentreCurInfo tCurtainInfo;
	s8	   chValue[5] = "";

	tCurtainInfo = LIBDATAMGRPTR->GetCurtainInfo( );

	m_tCentreCurInfo = tCurtainInfo;

	itoa(m_tCentreCurInfo.byCurNum,chValue,10);

	UIFACTORYMGR_PTR->SetComboText("CentCfgCurtainDlg/ComboboxCurNum",chValue,m_pWndTree );

	vector< TCentreCurName > vec_CurName;
	for( s32 nIndex = 0 ; nIndex < tCurtainInfo.byCurNum; nIndex ++ )
	{
		vec_CurName.push_back(tCurtainInfo.tCenCurName[nIndex]);
	}
	
	Value_CurtainList CCurtainNameList( &vec_CurName );
	UIFACTORYMGR_PTR->SetPropertyValue( CCurtainNameList, "CurtainLstDlg/CurtainList", m_pWndTree);

	if ( tCurtainInfo.bCurOpen == FALSE )
	//if ( tCurtainInfo.byCurNum < 1 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCurNotExist", m_pWndTree );
		return S_FALSE;
	}
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmCurExist", m_pWndTree );

	if ( tCurtainInfo.byCurNum < 1)
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmEnable", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmAvaliable", m_pWndTree );
	}
	return S_OK;
}

HRESULT CCentCfgCurtainDlg::OnUpdateCurName( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	m_tCentreCurInfo = *( TCentreCurInfo* )wparam;
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "设置窗帘名称失败" );
		return S_FALSE;
	}

	vector< TCentreCurName > vec_CurName;
	for( s32 nIndex = 0 ; nIndex < m_tCentreCurInfo.byCurNum; nIndex ++ )
	{
		vec_CurName.push_back(m_tCentreCurInfo.tCenCurName[nIndex]);
	}
	
	Value_CurtainList CCurtainNameList( &vec_CurName );
	UIFACTORYMGR_PTR->SetPropertyValue( CCurtainNameList, "CurtainLstDlg/CurtainList", m_pWndTree);

	return S_OK;
}

HRESULT CCentCfgCurtainDlg::OnCurtainInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bOpen = *(BOOL *)wparam;
	BOOL bSuccess = *(BOOL*)lparam;
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "配置窗帘失败" );
		//	return S_FALSE;
	}
	else
	{
		m_tCentreCurInfo.bCurOpen = bOpen;
	}
	
	if ( m_tCentreCurInfo.bCurOpen == false )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCurNotExist", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCurExist", m_pWndTree );
		//	UIFACTORYMGR_PTR->LoadScheme( "SchmAvaliable", m_pWndTree );
	}
	
	return S_OK;
}

HRESULT CCentCfgCurtainDlg::OnCurtainNumInd( WPARAM wparam, LPARAM lparam )
{
	u8 byCurtainNum = *(BOOL *)wparam;
	BOOL bSuccess = *(BOOL*)lparam;
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "配置窗帘数量失败" );
		return S_FALSE;
	}
	else
	{
		m_tCentreCurInfo.byCurNum = byCurtainNum;
	}
	
	vector< TCentreCurName > vec_CurName;
	for( s32 nIndex = 0 ; nIndex < m_tCentreCurInfo.byCurNum; nIndex ++ )
	{
		vec_CurName.push_back(m_tCentreCurInfo.tCenCurName[nIndex]);
	}
	
	Value_CurtainList CCurtainNameList( &vec_CurName );
	UIFACTORYMGR_PTR->SetPropertyValue( CCurtainNameList, "CurtainLstDlg/CurtainList", m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme( "SchmCurDefault", m_pWndTree );

	return S_OK;
}

bool CCentCfgCurtainDlg::OnClickCurList( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
		if ( const Data_CurName * pDataTemp = dynamic_cast< const Data_CurName*>(pIData) )
		{
			TCentreCurName tCurtainName = pDataTemp->m_tCurtainName;
			m_nSelIndex = GetSelItemIndex(tCurtainName);
			return true;
		}
	}

	m_nSelIndex = -1;
	return false;
}

s32 CCentCfgCurtainDlg::GetSelItemIndex( TCentreCurName &tCurtainName )
{
	for( s32 nIndex = 0 ; nIndex < m_tCentreCurInfo.byCurNum; nIndex ++ )
	{
		if ( strcmp(tCurtainName.achCurName,m_tCentreCurInfo.tCenCurName[nIndex].achCurName ) == 0 )
		{
			return nIndex;
		}
	}
	return -1;
}

bool CCentCfgCurtainDlg::OnClickCurLstBlack( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	m_nSelIndex = -1;

	return true;
}


//空调新风

CCentCfgAirCondition::CCentCfgAirCondition()
{
	
}

CCentCfgAirCondition::~CCentCfgAirCondition()
{
	
}

void CCentCfgAirCondition::RegCBFun()
{
	CCentCfgAirCondition *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgAirCondition::InitWnd", CCentCfgAirCondition::InitWnd, pThis, CCentCfgAirCondition );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgAirCondition::OnSwitchAirCondition", CCentCfgAirCondition::OnSwitchAirCondition, pThis, CCentCfgAirCondition );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgAirCondition::OnBtnSave", CCentCfgAirCondition::OnBtnSave, pThis, CCentCfgAirCondition );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgAirCondition::OnBtnCancel", CCentCfgAirCondition::OnBtnCancel, pThis, CCentCfgAirCondition );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgAirCondition::OnACNumCfg", CCentCfgAirCondition::OnACNumCfg, pThis, CCentCfgAirCondition );

}

void CCentCfgAirCondition::RegMsg()
{
	CCentCfgAirCondition *pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_AirCondtition_Nty, CCentCfgAirCondition::OnAirConditionNty, pThis, CCentCfgAirCondition );
	REG_MSG_HANDLER( UI_CNS_ACSTATE_NTY, CCentCfgAirCondition::OnUpdateAirInfoNty, pThis, CCentCfgAirCondition );
}

void CCentCfgAirCondition::UnRegFunc()
{

}

bool CCentCfgAirCondition::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	
	CString strACNum;
	
	vector<CString> vecAcNum;
	for ( s32 nIndex = 1 ; nIndex <= MAX_AC_NUM  ; nIndex ++ )
	{
		strACNum.Format( "%d",nIndex);
		vecAcNum.push_back( strACNum);
	}
	
	UIFACTORYMGR_PTR->SetComboListData( "CentCfgAirConditionDlg/ComboboxACNum", vecAcNum, m_pWndTree );

	m_vctWndName.clear();
	UpBtnState();
//	UIFACTORYMGR_PTR->ShowWindow( g_strRenameOptDlg,false );
	return true;
}

void CCentCfgAirCondition::Clear()
{
	
}

bool CCentCfgAirCondition::OnSwitchAirCondition( const IArgs & arg )
{
	bool bOpen = false;
	string   strScheme;
	string   strAcNum;
	
	UIFACTORYMGR_PTR->GetSwitchState("CentCfgAirConditionDlg/AirConditionButton",bOpen,m_pWndTree);

	if ( bOpen == true )
	{
		strScheme = "SchmACExist";
	}
	else
	{
		strScheme = "SchmACNotExist";
	}

	UIFACTORYMGR_PTR->LoadScheme(strScheme,m_pWndTree);

	UIFACTORYMGR_PTR->GetComboText("CentCfgAirConditionDlg/ComboboxACNum",strAcNum, m_pWndTree);

	if ( strAcNum == "" )
	{
		UIFACTORYMGR_PTR->SetComboText("CentCfgAirConditionDlg/ComboboxACNum","1", m_pWndTree);
	}
	
	UpdateState();
	return true;
}

void CCentCfgAirCondition::UpdateState()
{
	string   strAcNum;
	u8       byAcNum;
	bool bOpen = false;
	bool bChange = false;

	UIFACTORYMGR_PTR->GetSwitchState("CentCfgAirConditionDlg/AirConditionButton",bOpen,m_pWndTree);
	
	if ( bOpen == false )
	{
		byAcNum = 0;
	}
	else
	{
		UIFACTORYMGR_PTR->GetComboText("CentCfgAirConditionDlg/ComboboxACNum",strAcNum, m_pWndTree);
		byAcNum = atoi(strAcNum.c_str());
	}
	
	if ( byAcNum != m_byAcNum )
	{
		bChange = true;
	}

	CheckData("CentCfgAirConditionDlg/ComboboxACNum",bChange);
}

bool CCentCfgAirCondition::OnBtnSave( const IArgs & arg )
{
	bool bOpen = false;
	u8 byAcNum ;
	string strAcNum;

	UIFACTORYMGR_PTR->GetSwitchState("CentCfgAirConditionDlg/AirConditionButton",bOpen,m_pWndTree);

	if ( bOpen == false )
	{
		byAcNum = 0;
	}
	else
	{
		UIFACTORYMGR_PTR->GetComboText("CentCfgAirConditionDlg/ComboboxACNum",strAcNum,m_pWndTree );
		byAcNum = atoi(strAcNum.c_str());
	}
	u16 nRet = COMIFMGRPTR->SetAirConditionCmd( byAcNum );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "空调配置消息发送失败" );
		return false;
	}
	return true;
}

bool CCentCfgAirCondition::OnBtnCancel( const IArgs & arg )
{
	bool bOpen = false;
	
	UpdateAcState();
	m_vctWndName.clear();
	UpBtnState();
/*
	UIFACTORYMGR_PTR->GetSwitchState("CentCfgAirConditionDlg/AirConditionButton",bOpen,m_pWndTree);
	u16 nRet = COMIFMGRPTR->SetAirConditionCmd( bOpen == true ? TRUE : FALSE );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "空调配置消息发送失败" );
		return false;
	}*/
	return true;
}

bool CCentCfgAirCondition::IsACChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCentCfgAirCondition::SaveMsgBox()
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

bool CCentCfgAirCondition::OnACNumCfg( const IArgs & arg )
{
	UpdateState();

	return true;
}

LRESULT CCentCfgAirCondition::OnAirConditionNty( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = FALSE;
	u8 byAcNum ;

	byAcNum = *( u8 *)wParam;
	bSuccess = *( BOOL *)lParam;

	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "空调配置失败" );
		return S_FALSE;
	} 
	else
	{
		m_byAcNum = byAcNum;
	}
	
	UpdateAcState();

	m_vctWndName.clear();
	UpBtnState();
	return S_OK;
}

LRESULT CCentCfgAirCondition::OnUpdateAirInfoNty( WPARAM wParam, LPARAM lParam )
{
	m_byAcNum = *(u8*)wParam;
	UpdateAcState();

	m_vctWndName.clear();
	UpBtnState();
	return S_OK;
}

void CCentCfgAirCondition::UpdateAcState()
{
	string   strScheme;
	CString  cstrAcNum;

	UIFACTORYMGR_PTR->SetSwitchState( "CentCfgAirConditionDlg/AirConditionButton" , m_byAcNum > 0 ? true : false, m_pWndTree);
	
	if ( m_byAcNum > 0 )
	{
		strScheme = "SchmACExist";
		cstrAcNum.Format("%d",m_byAcNum);
	}
	else
	{
		strScheme = "SchmACNotExist";
		cstrAcNum = "";
	}
	UIFACTORYMGR_PTR->LoadScheme(strScheme,m_pWndTree);
	UIFACTORYMGR_PTR->SetComboText("CentCfgAirConditionDlg/ComboboxACNum",cstrAcNum.GetBuffer(cstrAcNum.GetLength()), m_pWndTree);
}

//双流演示源
CCentCfgDuoVideo::CCentCfgDuoVideo()
{
	
}

CCentCfgDuoVideo::~CCentCfgDuoVideo()
{
	
}

void CCentCfgDuoVideo::RegMsg()
{
	CCentCfgDuoVideo *pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_DUALSCREEN_Nty, CCentCfgDuoVideo::OnDuoVideoNty, pThis, CCentCfgDuoVideo );
}

void CCentCfgDuoVideo::RegCBFun()
{
	CCentCfgDuoVideo *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgDuoVideo::InitWnd", CCentCfgDuoVideo::InitWnd, pThis, CCentCfgDuoVideo );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDuoVideo::OnBtnDuoVideo", CCentCfgDuoVideo::OnBtnDuoVideo, pThis, CCentCfgDuoVideo );
}

void CCentCfgDuoVideo::UnRegFunc()
{
}

bool CCentCfgDuoVideo::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	

	m_bOpen = FALSE;
	//	UIFACTORYMGR_PTR->ShowWindow( g_strRenameOptDlg,false );
	return true;
}

bool CCentCfgDuoVideo::OnBtnDuoVideo( const IArgs & arg )
{
/*	CLogicBase::InitWnd( arg );	*/
	bool bOpen = false;
	
	UIFACTORYMGR_PTR->GetSwitchState("CentCfgDuoVideo/DuoVideoSwitchButton",bOpen,m_pWndTree);
	u16 nRet = COMIFMGRPTR->SetDuoVideoCmd( bOpen == true ? TRUE : FALSE );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "双流屏配置消息发送失败" );
		return false;
	}
	return true;
}

void CCentCfgDuoVideo::Clear()
{
	
}

LRESULT CCentCfgDuoVideo::OnDuoVideoNty( WPARAM wParam, LPARAM lParam )
{
/*	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	} 
	BOOL bDual = FALSE;
	TTPCnsInfo tCnsInfo;
	LIBDATAMGRPTR->GetLocalCnsInfo( tCnsInfo );

	if ( 255 == tCnsInfo.m_byDualPos)
	{
		bDual = FALSE;
	} 
	else
	{
		bDual = TRUE;
	}
*/
	BOOL bSuccess = FALSE;
	BOOL bOpen = FALSE;

	bOpen = *( BOOL *)wParam;
	bSuccess = *( BOOL *)lParam;

	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "双流屏配置失败" );
	}
	else
	{
		m_bOpen = bOpen;
	}
	
	UIFACTORYMGR_PTR->SetSwitchState( "CentCfgDuoVideo/DuoVideoSwitchButton" , m_bOpen == TRUE ? true : false, m_pWndTree);
	return S_OK;
}

