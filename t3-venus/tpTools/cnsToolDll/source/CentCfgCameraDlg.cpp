// CentCfgCameraDlg.cpp: implementation of the CCentCfgCameraDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CentCfgCameraDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCentCfgCameraDlg::CCentCfgCameraDlg()
:m_strPanSwitchBtn("CentCfgCameraDlg/PanCamSwitchBtn")
,m_strPancombobox("CentCfgCameraDlg/PanCamNumCombobox")
,m_strDocSwitch("CentCfgCameraDlg/DocCameraSwitch")
,m_strDocZoonPlusBtn("DocCameraDlg/BtnZoomPlus")
,m_strDocZoonSubBtn("DocCameraDlg/BtnZoomSub")
,m_strDocZoonEdit("DocCameraDlg/EdtZoom")
,m_strDocAperture("DocCameraDlg/ComboboxAperture")
,m_strDocExposureGain("DocCameraDlg/ComboboxExposureGain")
,m_strDocShutter("DocCameraDlg/ComboboxShut" )
,m_strDocPreset("DocCameraDlg/CheckBtnPreset")
,m_strDocLastState("DocCameraDlg/CheckBtnLastState")
,m_strDocAutoFocus("DocCameraDlg/BtnSwitchAutoFocus")
,m_strDocManualFocus("DocCameraDlg/BtnManualFocus")
,m_strDocFocusNear("DocCameraDlg/BtnFocusNear")
,m_strDocFocusAway("DocCameraDlg/BtnFocusFar")
,m_strDocAutoExposure("DocCameraDlg/BtnSwitchAutoExposure")
,m_strDocAutoWB("DocCameraDlg/BtnSwitchWB")
,m_strDocRGainSlider("DocCameraDlg/SliderRGain")
,m_strDocBGainSlider("DocCameraDlg/SliderBGain")
,m_strDocRGainEdit("DocCameraDlg/EditRGain")
,m_strDocBGainEdit("DocCameraDlg/EditBGain")
,m_strCMASwitchBtn("CentCfgCameraDlg/CMACameraSwitch")
,StrDocCamExistSch("SchmDocCamExist")
,StrDocCamNonExistSch("SchmDocCamNotExist")
{
	m_byPanCamNum = 0;
}

CCentCfgCameraDlg::~CCentCfgCameraDlg()
{

}

void CCentCfgCameraDlg::RegCBFun()
{
	CCentCfgCameraDlg* m_pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::InitWnd", CCentCfgCameraDlg::InitWnd, m_pThis, CCentCfgCameraDlg ) ;
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnPanCamBtnChange", CCentCfgCameraDlg::OnPanCamBtnChange, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnDocCameraBtnChange", CCentCfgCameraDlg::OnDocCameraBtnChange, m_pThis, CCentCfgCameraDlg );
    REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnCMACameraBtnChange", CCentCfgCameraDlg::OnCMACameraBtnChange, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnPanCamNumChange", CCentCfgCameraDlg::OnPanCamNumChange, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnSelPreset", CCentCfgCameraDlg::OnSelPreset, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnSelLastPreset", CCentCfgCameraDlg::OnSelLastPreset, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnLBtnDownZoonPlus", CCentCfgCameraDlg::OnLBtnDownZoonPlus, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnLBtnUpZoonPlus", CCentCfgCameraDlg::OnLBtnUpZoonPlus, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnLBtnDownZoonSub", CCentCfgCameraDlg::OnLBtnDownZoonSub, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnLBtnUpZoonSub", CCentCfgCameraDlg::OnLBtnUpZoonSub, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnEdtZoomChange", CCentCfgCameraDlg::OnEdtZoomChange, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnEdtZoomKillFocus", CCentCfgCameraDlg::OnEdtZoomKillFocus, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnBtnAutoFocusClick", CCentCfgCameraDlg::OnBtnAutoFocusClick, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnBtnManualFocusClick", CCentCfgCameraDlg::OnBtnManualFocusClick, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnLBtnDownFocusNear", CCentCfgCameraDlg::OnLBtnDownFocusNear, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnLBtnUpFocusNear", CCentCfgCameraDlg::OnLBtnUpFocusNear, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnLBtnDownFocusFar", CCentCfgCameraDlg::OnLBtnDownFocusFar, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnLBtnUpFocusFar", CCentCfgCameraDlg::OnLBtnUpFocusFar, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnBtnSwitchAutoExposure", CCentCfgCameraDlg::OnBtnSwitchAutoExposure, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnBtnSwitchAutoWB", CCentCfgCameraDlg::OnBtnSwitchAutoWB, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnSliderRGainChanged", CCentCfgCameraDlg::OnSliderRGainChanged, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnSliderBGainChanged", CCentCfgCameraDlg::OnSliderBGainChanged, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnEditRGainChange", CCentCfgCameraDlg::OnEditRGainChange, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnEditRGainKillFocus", CCentCfgCameraDlg::OnEditRGainKillFocus, m_pThis, CCentCfgCameraDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnEditBGainChange", CCentCfgCameraDlg::OnEditBGainChange, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnEditBGainKillFocus", CCentCfgCameraDlg::OnEditBGainKillFocus, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnComboboxApertureClick", CCentCfgCameraDlg::OnComboboxApertureClick, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnComboboxShutClick", CCentCfgCameraDlg::OnComboboxShutClick, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnComboboxExpGainClick", CCentCfgCameraDlg::OnComboboxExpGainClick, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnBtnSavePreSet", CCentCfgCameraDlg::OnBtnSavePreSet, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnBtnCallPreSet", CCentCfgCameraDlg::OnBtnCallPreSet, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnSelIPC822", CCentCfgCameraDlg::OnSelIPC822, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnSelPRS200", CCentCfgCameraDlg::OnSelPRS200, m_pThis, CCentCfgCameraDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnSel120E", CCentCfgCameraDlg::OnSel120E, m_pThis, CCentCfgCameraDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCameraDlg::OnSelMOON50", CCentCfgCameraDlg::OnSelMOON50, m_pThis, CCentCfgCameraDlg );
}

void CCentCfgCameraDlg::RegMsg()
{
	CCentCfgCameraDlg* m_pThis = GetSingletonPtr();

//	REG_MSG_HANDLER( UI_CNSTOOL_PanCam_Nty, CCentCfgCameraDlg::OnPanCamNty, m_pThis, CCentCfgCameraDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_PanCamNum_Nty, CCentCfgCameraDlg::OnPanCamNumNty, m_pThis, CCentCfgCameraDlg );
	
	REG_MSG_HANDLER( UI_CNSTOOL_DCCamCfg_Nty, CCentCfgCameraDlg::OnDocCamCfg, m_pThis, CCentCfgCameraDlg );
	REG_MSG_HANDLER( UI_CNS_DCAMSTATE_NTY, CCentCfgCameraDlg::OnDocCamInfoNty, m_pThis, CCentCfgCameraDlg );

	REG_MSG_HANDLER( UI_CNSTOOL_DocCamType_Nty, CCentCfgCameraDlg::OnDocCamModelNty, m_pThis, CCentCfgCameraDlg );

	REG_MSG_HANDLER( UI_CNSTOOL_PanCamType_Nty, CCentCfgCameraDlg::OnPanCamModelNty, m_pThis, CCentCfgCameraDlg );
	
	REG_MSG_HANDLER( UI_CNSTOOL_DCCamBootCallPreset_Nty, CCentCfgCameraDlg::OnDocCamBootCall, m_pThis, CCentCfgCameraDlg );

	REG_MSG_HANDLER( UI_CNSTOOL_DCCAMERA_ZOOM_Nty, CCentCfgCameraDlg::OnDocCamZoomNty, m_pThis, CCentCfgCameraDlg );
//	REG_MSG_HANDLER( UI_CNSTOOL_DCCAMERA_ZOOMValue_Nty, CCentCfgCameraDlg::OnDocCamZoomValueNty, m_pThis, CCentCfgCameraDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_DCCAMERA_AUTO_FOCUS_IND, CCentCfgCameraDlg::OnDocCamAutoFocusNty, m_pThis, CCentCfgCameraDlg );

	REG_MSG_HANDLER( UI_CNSTOOL_DCamExposure_Nty, CCentCfgCameraDlg::OnDcCamExpMode, m_pThis, CCentCfgCameraDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_DCamGain_Nty, CCentCfgCameraDlg::OnDcCamExpGain, m_pThis, CCentCfgCameraDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_DCamShut_Nty, CCentCfgCameraDlg::OnDCCamShutNty, m_pThis, CCentCfgCameraDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_DCamAperture_Nty, CCentCfgCameraDlg::OnDCCamApertureNty, m_pThis, CCentCfgCameraDlg );

	REG_MSG_HANDLER( UI_CNSTOOL_DCCAMERA_WB_Nty, CCentCfgCameraDlg::OnDocCamWBNty, m_pThis, CCentCfgCameraDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_DCCAMERA_RGain_Nty, CCentCfgCameraDlg::OnDocCamRGainNty, m_pThis, CCentCfgCameraDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_DCCAMERA_BGain_Nty, CCentCfgCameraDlg::OnDocCamBGainNty, m_pThis, CCentCfgCameraDlg );

	REG_MSG_HANDLER( UI_CNSTOOL_DCCAMERA_SavePreSet_Nty, CCentCfgCameraDlg::OnDocCamSavePreSetNty, m_pThis, CCentCfgCameraDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_DCCAMERA_CallPreSet_Nty, CCentCfgCameraDlg::OnDocCamCallPreSetNty, m_pThis, CCentCfgCameraDlg );
}

void CCentCfgCameraDlg::UnRegFunc()
{
	
}

bool CCentCfgCameraDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	vector<CString> m_vecPanCamNum;
	vector<CString> vecDCAperture;
	vector<CString> vecShut;
	vector<CString> vecExposureGain;

	string strDcAperture = "";
	string strExposureGain = "";
	string strShutter = "";

	UIFACTORYMGR_PTR->SetSwitchState( m_strPanSwitchBtn,false, m_pWndTree );

	m_vecPanCamNum.clear();
	m_vecPanCamNum.push_back("1");
	m_vecPanCamNum.push_back("2");
	m_vecPanCamNum.push_back("3");
	m_vecPanCamNum.push_back("4");

	UIFACTORYMGR_PTR->SetComboListData( m_strPancombobox, m_vecPanCamNum, m_pWndTree ); 
	UIFACTORYMGR_PTR->LoadScheme( "SchmPanCamNotExist", m_pWndTree );

	vecDCAperture.clear();

	strDcAperture = TransApertureTypeToString(emDIrisClose);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF14);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF11);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF9_6);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF8);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF6_8);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF5_6);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF4_8);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF4);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF3_4);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF2_8);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF2_4);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF2);
	vecDCAperture.push_back(strDcAperture.c_str());
	strDcAperture = TransApertureTypeToString(emDIrisF1_6);
	vecDCAperture.push_back(strDcAperture.c_str());
	UIFACTORYMGR_PTR->SetComboListData( m_strDocAperture, vecDCAperture, m_pWndTree );
																
	//设置快门下拉框数据
	strShutter = TransShutterTypeToString(emDShutSpd0);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpd1);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpd2);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpd3);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpd4);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpd5);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpd6);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpd7);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpd8);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpd9);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpdA);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpdB);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpdC);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpdD);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpdE);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpdF);
	vecShut.push_back( strShutter.c_str() );
	strShutter = TransShutterTypeToString(emDShutSpd10);
	vecShut.push_back( strShutter.c_str() );
	UIFACTORYMGR_PTR->SetComboListData( m_strDocShutter, vecShut, m_pWndTree );  
	
	//设置曝光增益下拉框数据
	strExposureGain = TransGainTypeToString(emN10_5dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emN9dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emN7_5dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emN6dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emN4_5dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emN3dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emN1_5dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emD0dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emP1_5dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emP3dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emP4_5dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emP6dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emP7_5dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emP9dB);
	vecExposureGain.push_back(strExposureGain.c_str());
	strExposureGain = TransGainTypeToString(emP10_5dB);
	vecExposureGain.push_back(strExposureGain.c_str());

	UIFACTORYMGR_PTR->SetComboListData( m_strDocExposureGain, vecExposureGain, m_pWndTree );  

	return true;
}

void CCentCfgCameraDlg::Clear()
{
	m_byPanCamNum = 0;
}
/*
LRESULT CCentCfgCameraDlg::OnPanCamNty( WPARAM wParam, LPARAM lParam )
{
	TPanCamInfo tPanCamInfo = *(TPanCamInfo*)wParam;
	m_tPanCamInfo = tPanCamInfo;
	
	UIFACTORYMGR_PTR->SetSwitchState( m_strPanSwitchBtn, true , m_pWndTree );
	CString strPanNum = "";
	strPanNum.Format( "%d", tPanCamInfo.byPanCamNum );
	UIFACTORYMGR_PTR->SetComboText( m_strPancombobox,strPanNum.GetBuffer(strPanNum.GetLength()), m_pWndTree ); 
	
	return S_OK;
}
*/
LRESULT CCentCfgCameraDlg::OnPanCamNumNty( WPARAM wParam, LPARAM lParam )
{
	u8 byPanCamNum = *(u8*)wParam;
	BOOL bSuccess = *(BOOL *)lParam;
	CString strPanNum = "";
	string strScheme = "";

	if ( bSuccess == TRUE )
	{	
		m_byPanCamNum = byPanCamNum;
	}
	else
	{
		WARNMESSAGE( "全景摄像机数量设置失败" );
	}
	
	if ( m_byPanCamNum == 0 )
	{
		strPanNum = "";
		strScheme = "SchmPanCamNotExist";
	}
	else
	{
		strPanNum.Format( "%d", m_byPanCamNum );
		strScheme = "SchmPanCamExist";
	}

	UIFACTORYMGR_PTR->SetComboText( m_strPancombobox,strPanNum.GetBuffer(strPanNum.GetLength()), m_pWndTree ); 
	UIFACTORYMGR_PTR->LoadScheme(strScheme,m_pWndTree);

	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDcCamExpMode( WPARAM wParam, LPARAM lParam )
{
	EmExpMode emDCamExpMode = *(EmExpMode*)wParam;
	string strDcGain;
	
	BOOL bSuccess = *( BOOL * )lParam;
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "曝光模式设置失败" );
	}
	else
	{
		m_tDCamInfo.tDCamCurPresetInfo.emDCamExpMode = emDCamExpMode;
	}
	
	if ( m_tDCamInfo.tDCamCurPresetInfo.emDCamExpMode == emExpAuto )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchAutoExp", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchManuelExp", m_pWndTree );
	}
	
	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDcCamExpGain( WPARAM wParam, LPARAM lParam )
{
	EmDCamGain emDCamGainInfo = *(EmDCamGain*)wParam;
	string strDcGain;

	BOOL bSuccess = *( BOOL * )lParam;

	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "曝光增益设置失败" );
	}
	else
	{
		m_tDCamInfo.tDCamCurPresetInfo.emDCamGain = emDCamGainInfo;
	}

	strDcGain = TransGainTypeToString(m_tDCamInfo.tDCamCurPresetInfo.emDCamGain);
	UIFACTORYMGR_PTR->SetComboText( m_strDocExposureGain,(string)strDcGain, m_pWndTree ); 
	
	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDCCamShutNty( WPARAM wParam, LPARAM lParam )
{	
	EmDCamShutSpd emDCamShut = *(EmDCamShutSpd*)wParam;
	string strDcShut;
	
	BOOL bSuccess = *( BOOL * )lParam;
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "曝光快门设置失败" );
	}
	else
	{
		m_tDCamInfo.tDCamCurPresetInfo.emDCamShutSpd = emDCamShut;
	}
	
	strDcShut = TransShutterTypeToString(m_tDCamInfo.tDCamCurPresetInfo.emDCamShutSpd);
	UIFACTORYMGR_PTR->SetComboText( m_strDocShutter,(string)strDcShut, m_pWndTree ); 
	
	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDCCamApertureNty( WPARAM wParam, LPARAM lParam )
{	
	EmDCamIris emDCamAperture = *(EmDCamIris*)wParam;
	string strDcAperture;
	
	BOOL bSuccess = *( BOOL * )lParam;
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "曝光快门设置失败" );
	}
	else
	{
		m_tDCamInfo.tDCamCurPresetInfo.emDCamIris = emDCamAperture;
	}
	
	strDcAperture = TransApertureTypeToString( m_tDCamInfo.tDCamCurPresetInfo.emDCamIris );
	UIFACTORYMGR_PTR->SetComboText( m_strDocAperture,(string)strDcAperture, m_pWndTree ); 
	
	return S_OK;
}

bool CCentCfgCameraDlg::OnPanCamBtnChange( const IArgs& args )
{	
	bool bOpen = false;
	u8 byPanCamNum;
	UIFACTORYMGR_PTR->GetSwitchState( m_strPanSwitchBtn, bOpen, m_pWndTree );
	
	if ( bOpen == true )
	{
		byPanCamNum = 1;
	}
	else
	{
		byPanCamNum = 0;
	}

	u16 nRet = COMIFMGRPTR->SetPanCamNumberCmd( byPanCamNum );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "配置全景摄像机请求发送失败" );
		
		UIFACTORYMGR_PTR->SetSwitchState( m_strPanSwitchBtn, !bOpen, m_pWndTree );   
	}
	
	return true;
}

LRESULT CCentCfgCameraDlg::OnDocCamInfoNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	String strState,strComboxText;
	TCentreDCamCfg tDCamCfg = *(TCentreDCamCfg*)wParam;
	
	m_tDCamInfo = tDCamCfg;

	if( m_tDCamInfo.emDcamProType == emVISCAPro )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmPRS200", m_pWndTree );
	}
	else if ( m_tDCamInfo.emDcamProType == emPELCOPro  )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmIPC822", m_pWndTree );
	}

	if ( tDCamCfg.bDCamUsed == TRUE )
	{
		UIFACTORYMGR_PTR->LoadScheme( StrDocCamExistSch.c_str(), m_pWndTree );
		if ( m_tDCamInfo.emDcamProType != emVISCAPro )                            //ipc822维护工具不对摄像机进行控制
		{
			UIFACTORYMGR_PTR->LoadScheme( StrDocCamNonExistSch.c_str(), m_pWndTree ,"CentCfgCameraDlg/DocCameraDlg");
		}
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( StrDocCamNonExistSch.c_str(), m_pWndTree );
	}

	if ( tDCamCfg.bRecallPresetOne == TRUE )
	{
		UIFACTORYMGR_PTR->LoadScheme("SchmPreset1",m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("SchmLastPreset",m_pWndTree);
	}

	SetZoomValue( ((float)tDCamCfg.tDCamCurPresetInfo.wZoom)/100 );
//聚焦
	switch( tDCamCfg.tDCamCurPresetInfo.emDCamAFMode )
	{
		case emDcamAFOff:
			UIFACTORYMGR_PTR->LoadScheme( "SchManualFocus", m_pWndTree );
			break;
		case emDCamAFOn:
			UIFACTORYMGR_PTR->LoadScheme( "SchAutoFocus", m_pWndTree );
			break;
		default:
			UIFACTORYMGR_PTR->LoadScheme( "SchInvalidFocus", m_pWndTree );
			break;
	}
//曝光
	if ( tDCamCfg.tDCamCurPresetInfo.emDCamExpMode == emExpAuto )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchAutoExp", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchManuelExp", m_pWndTree );
	}

	strComboxText = TransApertureTypeToString(tDCamCfg.tDCamCurPresetInfo.emDCamIris);
	UIFACTORYMGR_PTR->SetComboText( m_strDocAperture, strComboxText, m_pWndTree );  

	strComboxText = TransShutterTypeToString(tDCamCfg.tDCamCurPresetInfo.emDCamShutSpd);
	UIFACTORYMGR_PTR->SetComboText( m_strDocShutter, strComboxText, m_pWndTree );  

	strComboxText = TransGainTypeToString(tDCamCfg.tDCamCurPresetInfo.emDCamGain);
	UIFACTORYMGR_PTR->SetComboText( m_strDocExposureGain, strComboxText, m_pWndTree );  
//白平衡
	switch ( tDCamCfg.tDCamCurPresetInfo.emDCamWBMode )
	{
	case emDcamWBAuto:
		UIFACTORYMGR_PTR->LoadScheme( "SchAutoWB", m_pWndTree );
		break;
	case emDCamWBManual:
		UIFACTORYMGR_PTR->LoadScheme( "SchManualWB", m_pWndTree );
		break;
	default:
		UIFACTORYMGR_PTR->LoadScheme( "SchInvalidWB", m_pWndTree );
		break;
	}

	SetGainValue(tDCamCfg.tDCamCurPresetInfo.wRGain,m_strDocRGainSlider,m_strDocRGainEdit);
	SetGainValue(tDCamCfg.tDCamCurPresetInfo.wBGain,m_strDocBGainSlider,m_strDocBGainEdit);

	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDocCamCfg( WPARAM wParam, LPARAM lParam )
{
	BOOL bOpen = FALSE;
	BOOL bSuccess = FALSE;

	bOpen = *( BOOL * )wParam;
	bSuccess = *( BOOL * )lParam;

	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "配置文档摄像机失败" );
		UIFACTORYMGR_PTR->SetSwitchState( m_strDocSwitch, m_tDCamInfo.bDCamUsed ? true : false , m_pWndTree );
		
		return S_FALSE;
	}
	else
	{
		m_tDCamInfo.bDCamUsed = bOpen;

		if ( bOpen == TRUE )
		{
			UIFACTORYMGR_PTR->LoadScheme( StrDocCamExistSch.c_str(), m_pWndTree );
			if ( m_tDCamInfo.emDcamProType != emVISCAPro )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmIPC822", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( StrDocCamNonExistSch.c_str(), m_pWndTree ,"CentCfgCameraDlg/DocCameraDlg");
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmPRS200", m_pWndTree);
			}
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( StrDocCamNonExistSch.c_str(), m_pWndTree );
		}
	}
	return S_OK;
}


LRESULT CCentCfgCameraDlg::OnDocCamAutoFocusNty( WPARAM wParam, LPARAM lParam )
{
	BOOL bRet = static_cast<BOOL>(lParam);
	EmDCamAFMode emFocus = static_cast<EmDCamAFMode>(wParam);
	if ( bRet == false )
	{
		WARNMESSAGE( "焦距设置失败" );

/*		if ( emFocus == emDcamAFOff )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchAutoFocus", m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchManualFocus", m_pWndTree );
		}*/
	}
	else
	{
		m_tDCamInfo.tDCamCurPresetInfo.emDCamAFMode = emFocus;
	}

	if ( m_tDCamInfo.tDCamCurPresetInfo.emDCamAFMode == emDcamAFOff )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchManualFocus", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchAutoFocus", m_pWndTree );
	}

	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDocCamZoomNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	u16 wZoom = 0;
	BOOL bRet = *( BOOL *)(lParam);
	wZoom = *( u16 *)(wParam);
//	wZoom = static_cast<u16>(wParam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "zoom设置失败");
	}
	else
	{
		m_tDCamInfo.tDCamCurPresetInfo.wZoom = wZoom;
	}
	
	SetZoomValue((float)m_tDCamInfo.tDCamCurPresetInfo.wZoom/100);
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strDocZoonEdit, m_pWndTree );
/*	if ( pWnd )
	{
		pWnd->ShowWindow(SW_HIDE);
		pWnd->ShowWindow(SW_SHOW);
	}
*/	
	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDocCamWBNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	EmDCamWBMode emWBMode = static_cast<EmDCamWBMode>(wParam);
	BOOL bRet = static_cast<BOOL>(lParam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "白平衡设置失败");

/*		if ( emWBMode == emDcamWBAuto )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchManualWB", m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchAutoWB", m_pWndTree );
		}*/
	}
	else
	{
		m_tDCamInfo.tDCamCurPresetInfo.emDCamWBMode = emWBMode;
	}

	if ( m_tDCamInfo.tDCamCurPresetInfo.emDCamWBMode == emDcamWBAuto )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchAutoWB", m_pWndTree );
	}
	else if ( m_tDCamInfo.tDCamCurPresetInfo.emDCamWBMode == emDcamWBAuto )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchManualWB", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchManualWB", m_pWndTree );
	}
	
	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDocCamRGainNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	Value_CSliderCtrlPos valuePos;
	u16 wRGain = 0;
	BOOL bRet = *( BOOL *)(lParam);
	wRGain = *( u16 * )(wParam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "R增益设置失败");
	}
	else
	{
		m_tDCamInfo.tDCamCurPresetInfo.wRGain = wRGain;
	}

	SetGainValue(m_tDCamInfo.tDCamCurPresetInfo.wRGain,m_strDocRGainSlider,m_strDocRGainEdit);
	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDocCamBGainNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	Value_CSliderCtrlPos valuePos;
	u16 wBGain = 0;
	BOOL bRet = *( BOOL *)(lParam);
	wBGain = *( u16 * )(wParam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "B增益设置失败");
	}
	else
	{
		m_tDCamInfo.tDCamCurPresetInfo.wBGain = wBGain;
	}

	SetGainValue(m_tDCamInfo.tDCamCurPresetInfo.wBGain,m_strDocBGainSlider,m_strDocBGainEdit);
	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDocCamSavePreSetNty( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = *(BOOL *)(wParam);
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "保存预置位失败");
	}

	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDocCamCallPreSetNty( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = *(BOOL *)(wParam);
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "调用预置位失败");
	}
	
	return S_OK;
}

bool CCentCfgCameraDlg::OnDocCameraBtnChange( const IArgs& args )
{	
	bool bOpen = false;
	UIFACTORYMGR_PTR->GetSwitchState( m_strDocSwitch, bOpen, m_pWndTree );
	
	u16 nRet = COMIFMGRPTR->SetDCCamOpenCmd( bOpen );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "配置文档摄像机请求发送失败" );
		UIFACTORYMGR_PTR->SetSwitchState( m_strDocSwitch, m_tDCamInfo.bDCamUsed ? true : false , m_pWndTree );
	}
	
	return true;
}

bool CCentCfgCameraDlg::OnCMACameraBtnChange( const IArgs& args )
{	
    bool bOpen = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strCMASwitchBtn, bOpen, m_pWndTree );

    u16 nRet = 1;
    //u16 nRet = COMIFMGRPTR->SetDCCamOpenCmd( bOpen );
    if ( nRet != NO_ERROR )
    {
        WARNMESSAGE( "配置CMA300摄像机请求发送失败" );
        UIFACTORYMGR_PTR->SetSwitchState( m_strCMASwitchBtn, false ? true : false , m_pWndTree );
    }
    
    return true;
}

bool CCentCfgCameraDlg::OnPanCamNumChange( const IArgs& args )
{
	string strPanCamNum = "";
	s8	    chPanNum[5] = "";
	
	UIFACTORYMGR_PTR->GetComboText( m_strPancombobox, strPanCamNum, m_pWndTree );
	
	u8 byPanCamNum =(u8)atoi(strPanCamNum.c_str());
	u16 nRet = COMIFMGRPTR->SetPanCamNumberCmd( byPanCamNum );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "全景摄像机请求发送失败" );
		itoa(m_byPanCamNum,chPanNum,10);
		strPanCamNum= chPanNum;
		
		UIFACTORYMGR_PTR->SetComboText( m_strPancombobox, strPanCamNum, m_pWndTree );   
	}
	return true;
}

bool CCentCfgCameraDlg::OnSelPreset( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme("SchmPreset1",m_pWndTree);

	BOOL bPreset = TRUE;

	u16 nRet = COMIFMGRPTR->SetDCCamPreset( bPreset );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "文档摄像机设置预置位请求发送失败" );
	}
	
	return true;
}

bool CCentCfgCameraDlg::OnSelLastPreset( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme("SchmLastPreset",m_pWndTree);

	BOOL bPreset = FALSE;

	u16 nRet = COMIFMGRPTR->SetDCCamPreset( bPreset );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "文档摄像机设置预置位请求发送失败" );
	}
	
	return true;
}

LRESULT CCentCfgCameraDlg::OnDocCamBootCall( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = FALSE;
	BOOL bPreset = FALSE;

	bSuccess = *( BOOL * )lParam;
	bPreset = *( BOOL * )wParam;

	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "配置开机调用预置位失败" );

		if ( m_tDCamInfo.bRecallPresetOne == FALSE )
		{
			UIFACTORYMGR_PTR->LoadScheme("SchmPreset1",m_pWndTree);
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme("SchmLastPreset",m_pWndTree);
		}
	}
	else
	{
		m_tDCamInfo.bRecallPresetOne = bPreset;
	}

	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnDocCamModelNty( WPARAM wParam, LPARAM lParam )
{
	EmDCamProType emCamModelType = *(EmDCamProType*)wParam;
	BOOL bSuccess = *(BOOL*)lParam;

	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "配置文档摄像机型号失败" );
	}
	else
	{
		m_tDCamInfo.emDcamProType = emCamModelType;
	}

	if (  m_tDCamInfo.emDcamProType == emVISCAPro )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmPRS200", m_pWndTree);
	
		UIFACTORYMGR_PTR->LoadScheme( StrDocCamExistSch.c_str(), m_pWndTree ,"CentCfgCameraDlg/DocCameraDlg");
	}
	else if ( m_tDCamInfo.emDcamProType == emPELCOPro )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmIPC822", m_pWndTree );
		
		UIFACTORYMGR_PTR->LoadScheme( StrDocCamNonExistSch.c_str(), m_pWndTree ,"CentCfgCameraDlg/DocCameraDlg");
	}

	return S_OK;
}

LRESULT CCentCfgCameraDlg::OnPanCamModelNty( WPARAM wParam, LPARAM lParam )
{
	EmQCamProType emCamModelType = *(EmQCamProType*)wParam;
	BOOL bSuccess = *(BOOL*)lParam;
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "配置全景摄像机型号失败" );
	}
	else
	{
		m_tQCamInfo.emQCamProType = emCamModelType;
	}
	
	if (  m_tQCamInfo.emQCamProType == em120E )
	{
		UIFACTORYMGR_PTR->LoadScheme( "Schm120E", m_pWndTree);
	}
	else if ( m_tQCamInfo.emQCamProType == emMoon50 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmMOON50", m_pWndTree );
	}
	
	return S_OK;
}

bool CCentCfgCameraDlg::OnLBtnDownZoonPlus( const IArgs& args )
{
	EmDCamZoom emZoom ;
	EmCnAction emAction ;
	
	emZoom = emDCamZoomTele;
	emAction = emCnStart;
	u16 nRet = COMIFMGRPTR->SetDCCamZoomCmd( emZoom, emAction);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "文档摄像机Zoom请求发送失败" );
	}
	
	return true;
}

bool CCentCfgCameraDlg::OnLBtnUpZoonPlus( const IArgs& args )
{
	EmDCamZoom emZoom ;
	EmCnAction emAction ;
	
	emZoom = emDCamZoomTele;
	emAction = emCnStop;

	u16 nRet = COMIFMGRPTR->SetDCCamZoomCmd( emZoom, emAction);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "文档摄像机Zoom请求发送失败" );
	}
	return true;
}

bool CCentCfgCameraDlg::OnLBtnDownZoonSub( const IArgs& args )
{
	EmDCamZoom emZoom ;
	EmCnAction emAction ;
	
	emZoom = emDCamZoomWide;
	emAction = emCnStart;
	u16 nRet = COMIFMGRPTR->SetDCCamZoomCmd( emZoom, emAction);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "文档摄像机Zoom请求发送失败" );
	}
	
	return true;
}

bool CCentCfgCameraDlg::OnLBtnUpZoonSub( const IArgs& args )
{
	EmDCamZoom emZoom ;
	EmCnAction emAction ;
	
	emZoom = emDCamZoomWide;
	emAction = emCnStop;
	
	u16 nRet = COMIFMGRPTR->SetDCCamZoomCmd( emZoom, emAction);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "文档摄像机Zoom请求发送失败" );
	}
	return true;
}

void CCentCfgCameraDlg::SetZoomValue( float fZoom )
{
	CString strCaption;
	strCaption.Format( "%.2f", fZoom );
	UIFACTORYMGR_PTR->SetCaption( m_strDocZoonEdit,strCaption.GetBuffer(strCaption.GetLength()), m_pWndTree );
}

bool CCentCfgCameraDlg::OnEdtZoomChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	Value_WindowCaption valueWindowCaption;
	UIFACTORYMGR_PTR->GetPropertyValue( valueWindowCaption, m_strDocZoonEdit, m_pWndTree );
	
	CString str;
	str = OnlyFloat( valueWindowCaption.strCaption.c_str() );
//	(( CEdit *) pWnd)->GetSel( -1 );
	UIFACTORYMGR_PTR->SetCaption( m_strDocZoonEdit, str.GetBuffer(str.GetLength()), m_pWndTree );
	
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strDocZoonEdit, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	if ( nChar == 0x0d )	//0x0d表示为\n
	{
		SetZoomCmd(str);
			
		SetFocus(NULL);
	}
	
	return true;
}

void CCentCfgCameraDlg::SetZoomCmd( CString str )
{
	float fZoom = StringToFloatTwo( str );
	
	if ( fZoom > 10 )
	{
		fZoom = 10.00;
	}
	else if ( fZoom < 1)
	{
		fZoom = 1.00;
	}
	
	u16 wZoom = (fZoom+1.0e-6)*100;

	u16 nRet = COMIFMGRPTR->SetDCCamZoomValue( wZoom );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "zoom请求发送失败" );
		SetZoomValue((float)m_tDCamInfo.tDCamCurPresetInfo.wZoom/100);
	}
}

bool CCentCfgCameraDlg::OnEdtZoomKillFocus( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strDocZoonEdit, str, m_pWndTree );
	
	SetZoomCmd(str.c_str());
	
	return true;
}

bool CCentCfgCameraDlg::OnBtnAutoFocusClick( const IArgs& args )
{
	EmDCamAFMode emAutoFocusMode = emDCamAFOn;
	UIFACTORYMGR_PTR->LoadScheme( "SchAFocus", m_pWndTree );
	u16 nRet = COMIFMGRPTR->SetDCCamAFModeCmd(emAutoFocusMode);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "自动焦距请求发送失败" );
		UIFACTORYMGR_PTR->LoadScheme( "SchMFocus", m_pWndTree );
	}
	return true;
}

bool CCentCfgCameraDlg::OnBtnManualFocusClick( const IArgs& args )
{
	EmDCamAFMode emAutoFocusMode = emDcamAFOff;
	UIFACTORYMGR_PTR->LoadScheme( "SchMFocus", m_pWndTree );
	u16 nRet = COMIFMGRPTR->SetDCCamAFModeCmd(emAutoFocusMode);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "手动焦距请求发送失败" );
		UIFACTORYMGR_PTR->LoadScheme( "SchAFocus", m_pWndTree );
	}
	return true;
}

bool CCentCfgCameraDlg::OnLBtnDownFocusNear( const IArgs& args )
{
	EmFocus emFocus = emNear;
	EmCnAction emCnAction = emCnStart;

	u16 nRet = COMIFMGRPTR->SetDCCamFocusCmd( emFocus , emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "拉近焦距请求发送失败" );
	}

	return true;
}

bool CCentCfgCameraDlg::OnLBtnUpFocusNear( const IArgs& args )
{
	EmFocus emFocus = emNear;
	EmCnAction emCnAction = emCnStop;
	
	u16 nRet = COMIFMGRPTR->SetDCCamFocusCmd( emFocus, emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "焦距拉近请求发送失败" );
	}
	
	return true;
}

bool CCentCfgCameraDlg::OnLBtnDownFocusFar( const IArgs& args )
{
	EmFocus emFocus = emFar;
	EmCnAction emCnAction = emCnStart;
	
	u16 nRet = COMIFMGRPTR->SetDCCamFocusCmd( emFocus, emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "焦距拉远请求发送失败" );
	}
	
	return true;
}

bool CCentCfgCameraDlg::OnLBtnUpFocusFar( const IArgs& args )
{
	EmFocus emFocus = emFar;
	EmCnAction emCnAction = emCnStop;
	
	u16 nRet = COMIFMGRPTR->SetDCCamFocusCmd( emFocus, emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "焦距拉远请求发送失败" );
	}
	
	return true;
}

bool CCentCfgCameraDlg::OnBtnSwitchAutoExposure( const IArgs& args )
{
	bool bAutoExposure = false;
	EmExpMode emExpMode;
	string strScheme = "";

	UIFACTORYMGR_PTR->GetSwitchState( m_strDocAutoExposure, bAutoExposure, m_pWndTree );
	if ( bAutoExposure == true )
	{
		emExpMode = emExpAuto;
	//	strScheme = "SchAutoExp";
	}
	else
	{
		emExpMode = emExpManuel;
	//	strScheme = "SchManuelExp";
	}
//	UIFACTORYMGR_PTR->LoadScheme( strScheme, m_pWndTree );
	u16 nRet = COMIFMGRPTR->SetDCCamExposureCmd(emExpMode);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "曝光请求发送失败" );
		UIFACTORYMGR_PTR->SetSwitchState( m_strDocAutoExposure, !bAutoExposure, m_pWndTree );
	}
	return true;
}

bool CCentCfgCameraDlg::OnBtnSwitchAutoWB( const IArgs& args )
{
	bool bAutoWB = false;
	EmDCamWBMode emDcWBMode;
	string strScheme = "";
	UIFACTORYMGR_PTR->GetSwitchState( m_strDocAutoWB, bAutoWB, m_pWndTree );
	if ( bAutoWB == true )
	{
		emDcWBMode = emDcamWBAuto;
//		strScheme = "SchAutoWB";
	}
	else
	{
		emDcWBMode = emDCamWBManual;
//		strScheme = "SchManualWB";
	}
//	UIFACTORYMGR_PTR->LoadScheme( strScheme, m_pWndTree );
//	EmDCamAFMode emAutoFocusMode = emDcamAFOff;
	u16 nRet = COMIFMGRPTR->SetDCCamWBModeCmd(emDcWBMode);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "白平衡请求发送失败" );
		UIFACTORYMGR_PTR->SetSwitchState( m_strDocAutoWB, !bAutoWB, m_pWndTree );
	}
	return true;
}

bool CCentCfgCameraDlg::OnSliderRGainChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strDocRGainSlider, m_pWndTree );
	
	SetGainValue(valueCSliderCtrlPos.nPos,m_strDocRGainSlider,m_strDocRGainEdit);
	
	u16 wRGain = valueCSliderCtrlPos.nPos;
	u16 wRGainInLib = 0;

	if ( wRGain == m_tDCamInfo.tDCamCurPresetInfo.wRGain)
	{
		return true;
	}
	
	u16 nRet = COMIFMGRPTR->SetDcCamRGain( wRGain );

	if ( nRet != NO_ERROR )
	{
		Value_CSliderCtrlPos valuePos;
		
		WARNMESSAGE( "RGain调节请求发送失败" );
		
		valuePos.nPos = m_tDCamInfo.tDCamCurPresetInfo.wRGain;
		UIFACTORYMGR_PTR->SetPropertyValue( valuePos,m_strDocBGainSlider,m_pWndTree );
	}
	
	return true;
}

bool CCentCfgCameraDlg::OnSliderBGainChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strDocBGainSlider, m_pWndTree );
	
	SetGainValue(valueCSliderCtrlPos.nPos,m_strDocBGainSlider,m_strDocBGainEdit);
	
	u16 wRGain = valueCSliderCtrlPos.nPos;
	u16 wRGainInLib = 0;

//	LIBDATAMGRPTR->GetCamRGain( wRGainInLib );
	if ( wRGain == m_tDCamInfo.tDCamCurPresetInfo.wBGain )
	{
		return true;
	}
	
	u16 nRet = COMIFMGRPTR->SetDcCamBGain( wRGain );
	if ( nRet != NO_ERROR )
	{
		Value_CSliderCtrlPos valuePos;

		WARNMESSAGE( "BGain调节请求发送失败" );

		valuePos.nPos = m_tDCamInfo.tDCamCurPresetInfo.wBGain;
		UIFACTORYMGR_PTR->SetPropertyValue( valuePos,m_strDocBGainSlider,m_pWndTree );
	}
	
	return true;
}

void CCentCfgCameraDlg::SetGainValue( u16 wRGain ,string strStrliderName, string strEditName )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wRGain;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, strStrliderName, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wRGain );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, strEditName, m_pWndTree );
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strEditName, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

bool CCentCfgCameraDlg::OnEditRGainChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}

	GainEditChange(args,m_strDocRGainEdit,m_strDocRGainSlider);

	return true;
}

bool CCentCfgCameraDlg::OnEditBGainChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	GainEditChange(args,m_strDocBGainEdit,m_strDocBGainSlider);
	
	return true;
}

void CCentCfgCameraDlg::GainEditChange( const IArgs& args ,string strEditName, string strSliderName )
{
	String strEdit;
	UIFACTORYMGR_PTR->GetCaption( strEditName, strEdit, m_pWndTree );
/*	Value_CSliderCtrlPos pos;
	pos.nPos = atoi(strEdit.c_str());
	UIFACTORYMGR_PTR->SetPropertyValue( pos,strSliderName,m_pWndTree );
*/
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strEditName, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
}

bool CCentCfgCameraDlg::OnEditRGainKillFocus( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strDocRGainEdit, str, m_pWndTree );
	
	s32 nGain = atoi( str.c_str() );
	
	if ( nGain > 255 )
	{
		nGain = 255;
	}
	else if ( nGain < 0)
	{
		nGain = 0;
	}
	
	u16 nRet = COMIFMGRPTR->SetDcCamRGain( nGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "RGain调节请求发送失败" );
		SetGainValue(m_tDCamInfo.tDCamCurPresetInfo.wRGain,m_strDocRGainSlider,m_strDocRGainEdit);
	}
	
	return true;
}

bool CCentCfgCameraDlg::OnEditBGainKillFocus( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strDocBGainEdit, str, m_pWndTree );
	
	s32 nGain = atoi( str.c_str() );
	
	if ( nGain > 255 )
	{
		nGain = 255;
	}
	else if ( nGain < 0)
	{
		nGain = 0;
	}

	u16 nRet = COMIFMGRPTR->SetDcCamBGain( nGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "BGain调节请求发送失败" );
		SetGainValue(m_tDCamInfo.tDCamCurPresetInfo.wBGain,m_strDocBGainSlider,m_strDocBGainEdit);
	}
	
	return true;
}

bool CCentCfgCameraDlg::OnComboboxApertureClick( const IArgs& args )
{
	EmDCamIris emDcAperture;

	string strAperture = "";

	UIFACTORYMGR_PTR->GetComboText( m_strDocAperture, strAperture, m_pWndTree );
	emDcAperture = TransApertureTextToType(strAperture);

	u16 nRet = COMIFMGRPTR->SetDCCamApertureCmd( emDcAperture );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "光圈请求发送失败" );

		strAperture = TransApertureTypeToString(m_tDCamInfo.tDCamCurPresetInfo.emDCamIris);
		UIFACTORYMGR_PTR->SetComboText( m_strDocAperture, strAperture, m_pWndTree );   
	}
	return true;
}

bool CCentCfgCameraDlg::OnComboboxShutClick( const IArgs& args )
{
	EmDCamShutSpd emDcCamShut;	
	string strDcCamShut = "";
	
	UIFACTORYMGR_PTR->GetComboText( m_strDocShutter, strDcCamShut, m_pWndTree );
	emDcCamShut = TransShutterTextToType(strDcCamShut);
	
	u16 nRet = COMIFMGRPTR->SetDCCamShut( emDcCamShut );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "曝光快门请求发送失败" );
		
		strDcCamShut = TransShutterTypeToString(m_tDCamInfo.tDCamCurPresetInfo.emDCamShutSpd);
		UIFACTORYMGR_PTR->SetComboText( m_strDocShutter, strDcCamShut, m_pWndTree );   
	}

	return true;
}

bool CCentCfgCameraDlg::OnComboboxExpGainClick( const IArgs& args )
{
	EmDCamGain emDcCamExpGain;	
	string strDcCamExpGain = "";
	
	UIFACTORYMGR_PTR->GetComboText( m_strDocExposureGain, strDcCamExpGain, m_pWndTree );
	emDcCamExpGain = TransGainTextToType(strDcCamExpGain);
	
	u16 nRet = COMIFMGRPTR->SetDCCamExpGain( emDcCamExpGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "曝光增益请求发送失败" );

		strDcCamExpGain = TransGainTypeToString(m_tDCamInfo.tDCamCurPresetInfo.emDCamGain);
		UIFACTORYMGR_PTR->SetComboText( m_strDocExposureGain, strDcCamExpGain, m_pWndTree ); 
	}
	return true;
}

bool CCentCfgCameraDlg::OnBtnSavePreSet( const IArgs& args )
{
	BOOL bSave = TRUE;
    EM_PRESET_STYLE emPresetStyle = em_CamDoc_Num3;
	CMsgDispatch::SendMessage( UI_CNSTOOL_DCCAMERA_PreSet_Nty, (WPARAM)&bSave, (LPARAM)&emPresetStyle);
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_strRenameOptDlg );
	
	return true;
}

bool CCentCfgCameraDlg::OnBtnCallPreSet( const IArgs& args )
{
	BOOL bSave = FALSE;
    EM_PRESET_STYLE emPresetStyle = em_CamDoc_Num3;
	CMsgDispatch::SendMessage( UI_CNSTOOL_DCCAMERA_PreSet_Nty, (WPARAM)&bSave, (LPARAM)&emPresetStyle);
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_strRenameOptDlg );
	
	return true;
}

bool CCentCfgCameraDlg::OnSelIPC822( const IArgs& args )
{	
	if ( m_tDCamInfo.emDcamProType == emPELCOPro )
	{
		return false;
	}

	u16 nRet = COMIFMGRPTR->SetDcCamModel( emPELCOPro );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "配置文档摄像机型号请求发送失败" );

		if( m_tDCamInfo.emDcamProType == emVISCAPro )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmPRS200", m_pWndTree );
		}
	}
 	return true;
}

bool CCentCfgCameraDlg::OnSelPRS200( const IArgs& args )
{	
	if ( m_tDCamInfo.emDcamProType == emVISCAPro )
	{
		return false;
	}

	u16 nRet = COMIFMGRPTR->SetDcCamModel( emVISCAPro );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "配置文档摄像机型号请求发送失败" );
		
		if( m_tDCamInfo.emDcamProType == emPELCOPro )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmIPC822", m_pWndTree );
		}
	}
 	return true;
}

bool CCentCfgCameraDlg::OnSel120E( const IArgs& args )
{	
	if ( m_tQCamInfo.emQCamProType == em120E )
	{
		return false;
	}
	
	u16 nRet = COMIFMGRPTR->SetPaCamModel( em120E );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "配置文档摄像机型号请求发送失败" );
		
		if( m_tQCamInfo.emQCamProType == em120E )
		{
			UIFACTORYMGR_PTR->LoadScheme( "Schm120E", m_pWndTree );
		}
	}
	return true;
}

bool CCentCfgCameraDlg::OnSelMOON50( const IArgs& args )
{	
	if ( m_tQCamInfo.emQCamProType == emMoon50 )
	{
		return false;
	}
	
	u16 nRet = COMIFMGRPTR->SetPaCamModel( emMoon50 );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "配置文档摄像机型号请求发送失败" );
		
		if( m_tQCamInfo.emQCamProType == emMoon50 )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmMOON50", m_pWndTree );
		}
	}
	return true;
}

CString CCentCfgCameraDlg::OnlyFloat( CString str )
{
	// 只允许输数据
	int nStringLength = str.GetLength();
	int nDotCount = 0;
	// 点字符不能多于1个
	int nIndex = 0;
	for ( ; nIndex < nStringLength; nIndex++ )
	{
		if ( str[ nIndex ] == '.' )
		{
			nDotCount++;
			if ( nDotCount > 1 )
			{
				CString csTmp;
				csTmp = str.Left( nIndex );
				csTmp += str.Right( str.GetLength() - nIndex - 1 );
				//csRadius = csRadius.Left( nIndex + 1 ) + csRadius.Right( nStringLength - ( nIndex + 1 ) - 1 );
				//GetDlgItem( IDC_EDIT_AREA_S )->SetWindowText( csTmp );
				return csTmp;
			}
		}
	}
	
	// 不允许输入数字和点以外的字符
	nIndex = 0;
	for ( ; nIndex < nStringLength; nIndex++ )
	{
		if ( str[ nIndex ] != '.' && ( str[ nIndex ] > '9' || str[ nIndex ] < '0' ) )
		{
			str = str.Left( nIndex ) + str.Right( str.GetLength() - nIndex - 1 );
			//GetDlgItem( IDC_EDIT_AREA_S )->SetWindowText( csTmp );
			return str;
		}
	}
	
	return str;
}

float CCentCfgCameraDlg::StringToFloatTwo( CString str )
{
	float f = 0;
	f = atof((LPCTSTR)str);
	char strRet[10] = {0};
	sprintf(strRet,"%.2f",f);
	f = atof(strRet);
	return f;
}

/*HRESULT CCameraLogic::OnSetCameraZoomInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	u16 wZoom = 0;
	LIBDATAMGRPTR->GetCamZoom( wZoom );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "zoom设置失败");
	}
	
	SetZoomValue((float)wZoom/100);
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtZoom, m_pWndTree );
	if ( pWnd )
	{
		pWnd->ShowWindow(SW_HIDE);
		pWnd->ShowWindow(SW_SHOW);
	}
	
	return S_OK;
}
*/

string CCentCfgCameraDlg::TransApertureTypeToString( EmDCamIris emAperture )
{
	string strAperture = "";
	switch( emAperture )
	{
		case emDIrisClose:
			strAperture = "Close";
			break;
		case emDIrisF14:
			strAperture = "F14";
			break;
		case emDIrisF11:
			strAperture = "F11";
			break;
		case emDIrisF9_6:
			strAperture = "F9.6";
			break;
		case emDIrisF8:
			strAperture = "F8.0";
			break;
		case emDIrisF6_8:
			strAperture = "F6.8";
			break;
		case emDIrisF5_6:
			strAperture = "F5.6";
			break;
		case emDIrisF4_8:
			strAperture = "F4.8";
			break;
		case emDIrisF4:
			strAperture = "F4.0";
			break;
		case emDIrisF3_4:
			strAperture = "F3.4";
			break;
		case emDIrisF2_8:
			strAperture = "F2.8";
			break;
		case emDIrisF2_4:
			strAperture = "F2.4";
			break;
		case emDIrisF2:
			strAperture = "F2.0";
			break;
		case emDIrisF1_6:
			strAperture = "F1.6";
			break;
		default:
			break;
	}

	return strAperture;
}

EmDCamIris CCentCfgCameraDlg::TransApertureTextToType( string strAperture )
{
	EmDCamIris emAperture;

	if ( strcmp( strAperture.c_str(),"Close" ) == 0 )
	{
		emAperture = emDIrisClose; 
	}
	else if ( strcmp(  strAperture.c_str(),"F14" ) == 0 )
	{
		emAperture = emDIrisF14;
	}
	else if ( strcmp(  strAperture.c_str(),"F11" ) == 0 )
	{
		emAperture = emDIrisF11;
	}
	else if ( strcmp(  strAperture.c_str(),"F9.6" ) == 0 )
	{
		emAperture = emDIrisF9_6;
	}
	else if ( strcmp(  strAperture.c_str(),"F8.0" ) == 0 )
	{
		emAperture = emDIrisF8;
	}
	else if ( strcmp(  strAperture.c_str(),"F6.8" ) == 0 )
	{
		emAperture = emDIrisF6_8;
	}
	else if ( strcmp(  strAperture.c_str(),"F5.6" ) == 0 )
	{
		emAperture = emDIrisF5_6;
	}
	else if ( strcmp(  strAperture.c_str(),"F4.8" ) == 0 )
	{
		emAperture = emDIrisF4_8;
	}
	else if ( strcmp(  strAperture.c_str(),"F4.0" ) == 0 )
	{
		emAperture = emDIrisF4;
	}
	else if ( strcmp(  strAperture.c_str(),"F3.4" ) == 0 )
	{
		emAperture = emDIrisF3_4;
	}
	else if ( strcmp(  strAperture.c_str(),"F2.8" ) == 0 )
	{
		emAperture = emDIrisF2_8;
	}
	else if ( strcmp(  strAperture.c_str(),"F2.4" ) == 0 )
	{
		emAperture = emDIrisF2_4;
	}
	else if ( strcmp(  strAperture.c_str(),"F2.0" ) == 0 )
	{
		emAperture = emDIrisF2;
	}
	else if ( strcmp(  strAperture.c_str(),"F1.6" ) == 0 )
	{
		emAperture = emDIrisF1_6;
	}
	
	return emAperture;
}

string CCentCfgCameraDlg::TransGainTypeToString( EmDCamGain emDCGain )
{
	string strGain = "";

	switch( emDCGain )
	{
		case emN10_5dB:
			strGain = "-10.5dB";
			break;
		case emN9dB:
			strGain = "-9dB";
			break;
		case emN7_5dB:
			strGain = "-7.5dB";
			break;
		case emN6dB:
			strGain = "-6dB";
			break;
		case emN4_5dB:
			strGain = "-4.5dB";
			break;
		case emN3dB:
			strGain = "-3dB";
			break;
		case emN1_5dB:
			strGain = "-1.5dB";
			break;
		case emD0dB:
			strGain = "0dB";
			break;
		case emP1_5dB:
			strGain = "+1.5dB";
			break;
		case emP3dB:
			strGain = "+3dB";
			break;
		case emP4_5dB:
			strGain = "+4.5dB";
			break;
		case emP6dB:
			strGain = "+6dB";
			break;
		case emP7_5dB:
			strGain = "+7.5dB";
			break;
		case emP9dB:
			strGain = "+9dB";
			break;
		case emP10_5dB:
			strGain = "+10.5dB";
			break;
		default:
			break;
	}
	return strGain;
}

EmDCamGain CCentCfgCameraDlg::TransGainTextToType( string strGainText )
{
	EmDCamGain emDcGain;

	if ( strcmp( strGainText.c_str(),"-10.5dB" ) == 0 )
	{
		emDcGain = emN10_5dB;
	}
	else if ( strcmp( strGainText.c_str(),"-9dB" ) == 0 )
	{
		emDcGain  = emN9dB;
	}
	else if ( strcmp( strGainText.c_str(),"-7.5dB" ) == 0 )
	{
		emDcGain  = emN7_5dB;
	}
	else if ( strcmp( strGainText.c_str(),"-6dB" ) == 0 )
	{
		emDcGain  = emN6dB;
	}
	else if ( strcmp( strGainText.c_str(),"-4.5dB" ) == 0 )
	{
		emDcGain  = emN4_5dB;
	}
	else if ( strcmp( strGainText.c_str(),"-3dB" ) == 0 )
	{
		emDcGain  = emN3dB;
	}
	else if ( strcmp( strGainText.c_str(),"-1.5dB" ) == 0 )
	{
		emDcGain  = emN1_5dB;
	}
	else if ( strcmp( strGainText.c_str(),"0dB" ) == 0 )
	{
		emDcGain  = emD0dB;
	}
	else if ( strcmp( strGainText.c_str(),"+1.5dB" ) == 0 )
	{
		emDcGain  = emP1_5dB;
	}
	else if ( strcmp( strGainText.c_str(),"+3dB" ) == 0 )
	{
		emDcGain  = emP3dB;
	}
	else if ( strcmp( strGainText.c_str(),"+4.5dB" ) == 0 )
	{
		emDcGain  = emP4_5dB;
	}
	else if ( strcmp( strGainText.c_str(),"+6dB" ) == 0 )
	{
		emDcGain  = emP6dB;
	}
	else if ( strcmp( strGainText.c_str(),"+7.5dB" ) == 0 )
	{
		emDcGain  = emP7_5dB;
	}
	else if ( strcmp( strGainText.c_str(),"+9dB" ) == 0 )
	{
		emDcGain  = emP9dB;
	}
	else if ( strcmp( strGainText.c_str(),"+10.5dB" ) == 0 )
	{
		emDcGain  = emP10_5dB;
	}

	return emDcGain;
}

string CCentCfgCameraDlg::TransShutterTypeToString( EmDCamShutSpd emDCShut )
{
	string strShut = "";
	
	switch( emDCShut )
	{
		case emDShutSpd0:
			strShut = "1/30";
			break;
		case emDShutSpd1:
			strShut = "1/60";
			break;
		case emDShutSpd2:
			strShut = "1/90";
			break;
		case emDShutSpd3:
			strShut = "1/100";
			break;
		case emDShutSpd4:
			strShut = "1/125";
			break;
		case emDShutSpd5:
			strShut = "1/180";
			break;
		case emDShutSpd6:
			strShut = "1/250";
			break;
		case emDShutSpd7:
			strShut = "1/350";
			break;
		case emDShutSpd8:
			strShut = "1/500";
			break;
		case emDShutSpd9:
			strShut = "1/725";
			break;
		case emDShutSpdA:
			strShut = "1/1000";
			break;
		case emDShutSpdB:
			strShut = "1/1500";
			break;
		case emDShutSpdC:
			strShut = "1/2000";
			break;
		case emDShutSpdD:
			strShut = "1/3000";
			break;
		case emDShutSpdE:
			strShut = "1/4000";
			break;
		case emDShutSpdF:
			strShut = "1/6000";
			break;
		case emDShutSpd10:
			strShut = "1/10000";
			break;
		default:
			break;
	}
	return strShut;
}

EmDCamShutSpd CCentCfgCameraDlg::TransShutterTextToType( string strShutterText )
{
	EmDCamShutSpd emShut;
	
	if ( strcmp( strShutterText.c_str(),"1/30" ) == 0 )
	{
		emShut = emDShutSpd0;
	}
	else if ( strcmp( strShutterText.c_str(),"1/60" ) == 0 )
	{
		emShut = emDShutSpd1;
	}
	else if ( strcmp( strShutterText.c_str(),"1/90" ) == 0 )
	{
		emShut = emDShutSpd2;
	}
	else if ( strcmp( strShutterText.c_str(),"1/100" ) == 0 )
	{
		emShut = emDShutSpd3;
	}
	else if ( strcmp( strShutterText.c_str(),"1/125" ) == 0 )
	{
		emShut = emDShutSpd4;
	}
	else if ( strcmp( strShutterText.c_str(),"1/180" ) == 0 )
	{
		emShut = emDShutSpd5;
	}
	else if ( strcmp( strShutterText.c_str(),"1/250" ) == 0 )
	{
		emShut = emDShutSpd6;
	}
	else if ( strcmp( strShutterText.c_str(),"1/350" ) == 0 )
	{
		emShut = emDShutSpd7;
	}
	else if ( strcmp( strShutterText.c_str(),"1/500" ) == 0 )
	{
		emShut = emDShutSpd8;
	}
	else if ( strcmp( strShutterText.c_str(),"1/725" ) == 0 )
	{
		emShut = emDShutSpd9;
	}
	else if ( strcmp( strShutterText.c_str(),"1/1000" ) == 0 )
	{
		emShut = emDShutSpdA;
	}
	else if ( strcmp( strShutterText.c_str(),"1/1500" ) == 0 )
	{
		emShut = emDShutSpdB;
	}
	else if ( strcmp( strShutterText.c_str(),"1/2000" ) == 0 )
	{
		emShut = emDShutSpdC;
	}
	else if ( strcmp( strShutterText.c_str(),"1/3000" ) == 0 )
	{
		emShut = emDShutSpdD;
	}
	else if ( strcmp( strShutterText.c_str(),"1/4000" ) == 0 )
	{
		emShut = emDShutSpdE;
	}
	else if ( strcmp( strShutterText.c_str(),"1/6000" ) == 0 )
	{
		emShut = emDShutSpdF;
	}
	else if ( strcmp( strShutterText.c_str(),"1/10000" ) == 0 )
	{
		emShut = emDShutSpd10;
	}

	return emShut;
}
