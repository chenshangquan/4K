// MoonAdjustDlg.cpp: implementation of the CMoonAdjustDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MoonAdjustDlg.h"
#include "SetContrastAreaLogic.h"
#include <math.h>
#include "io.h"
#include "sys/stat.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMoonAdjustDlg::CMoonAdjustDlg()
:m_strRefLineSwitchBtn("MoonAdjustDlg/RefLineSwitchBtn")
,m_strHorFlipSwitchBtn("MoonAdjustDlg/HorFlipSwitchBtn")
,m_strTraCorSwitchBtn("MoonAdjustDlg/TraCorSwitchBtn")
,m_strSchemeEnable("EnableScheme")
,m_strSchemeDisable("DisableScheme")
,m_strHorCorEdit("MoonAdjustDlg/HorCorEdit")
,m_strHorStrEdit("MoonAdjustDlg/HorStretchEdit")
,m_strVerCorEdit("MoonAdjustDlg/VerCorEdit")
,m_strVerStrEdit("MoonAdjustDlg/VerStretchEdit")
,m_strRLeftCorEdit("MoonAdjustDlg/RLeftCorEdit")
,m_strGLeftCorEdit("MoonAdjustDlg/GLeftCorEdit")
,m_strBLeftCorEdit("MoonAdjustDlg/BLeftCorEdit")
,m_strRMidCorEdit("MoonAdjustDlg/RMidCorEdit")
,m_strGMidCorEdit("MoonAdjustDlg/GMidCorEdit")
,m_strBMidCorEdit("MoonAdjustDlg/BMidCorEdit")
,m_strRRightCorEdit("MoonAdjustDlg/RRightCorEdit")
,m_strGRightCorEdit("MoonAdjustDlg/GRightCorEdit")
,m_strBRightCorEdit("MoonAdjustDlg/BRightCorEdit")
,m_strRgbConsisSwitchBtn("MoonAdjustDlg/RgbConsisSwitchBtn")
,m_strLeftDelayCorEdit("MoonAdjustDlg/LeftDelayCorEdit")
,m_strMiddleDelayCorEdit("MoonAdjustDlg/MiddleDelayCorEdit")
,m_strRightDelayCorEdit("MoonAdjustDlg/RightDelayCorEdit")
,m_bRefLineOpen(FALSE)
,m_bIsSaveAsSnapShot(FALSE)
,m_bIsFirstGroupUsed(FALSE)
,m_bIsOption(FALSE)
{
	m_mapMaxValue[m_strHorCorEdit.c_str()] = 548;
	m_mapMaxValue[m_strHorStrEdit.c_str()] = 512;
	m_mapMaxValue[m_strVerCorEdit.c_str()] = 548;
	m_mapMaxValue[m_strVerStrEdit.c_str()] = 512;
	m_mapMinValue[m_strRLeftCorEdit.c_str()] = 0.5;
	m_mapMaxValue[m_strRLeftCorEdit.c_str()] = 1.5;
	m_mapMinValue[m_strGLeftCorEdit.c_str()] = 0.5;
	m_mapMaxValue[m_strGLeftCorEdit.c_str()] = 1.5;
	m_mapMinValue[m_strBLeftCorEdit.c_str()] = 0.5;
	m_mapMaxValue[m_strBLeftCorEdit.c_str()] = 1.5;
	m_mapMinValue[m_strRMidCorEdit.c_str()] = 0.5;
	m_mapMaxValue[m_strRMidCorEdit.c_str()] = 1.5;
	m_mapMinValue[m_strGMidCorEdit.c_str()] = 0.5;
	m_mapMaxValue[m_strGMidCorEdit.c_str()] = 1.5;
	m_mapMinValue[m_strBMidCorEdit.c_str()] = 0.5;
	m_mapMaxValue[m_strBMidCorEdit.c_str()] = 1.5;
	m_mapMinValue[m_strRRightCorEdit.c_str()] = 0.5;
	m_mapMaxValue[m_strRRightCorEdit.c_str()] = 1.5;
	m_mapMinValue[m_strGRightCorEdit.c_str()] = 0.5;
	m_mapMaxValue[m_strGRightCorEdit.c_str()] = 1.5;
	m_mapMinValue[m_strBRightCorEdit.c_str()] = 0.5;
	m_mapMaxValue[m_strBRightCorEdit.c_str()] = 1.5;

	m_vecShatShot.push_back("SnapShotDlg/ImageSnapshot1");
	m_vecShatShot.push_back("SnapShotDlg/ImageSnapshot2");
	m_vecShatShot.push_back("SnapShotDlg/ImageSnapshot3");
}

CMoonAdjustDlg::~CMoonAdjustDlg()
{

}

void CMoonAdjustDlg::RegMsg()
{
	CMoonAdjustDlg *pThis = CMoonAdjustDlg::GetSingletonPtr();

	//REG_MSG_HANDLER( UI_MOONTOOL_CAMINFO_NTY, CMoonAdjustDlg::OnTralCorParamInd, pThis, CMoonAdjustDlg );
	REG_MSG_HANDLER( UI_SecBoundary_Nty, CMoonAdjustDlg::OnSecBoundaryNty, pThis, CMoonAdjustDlg );
	REG_MSG_HANDLER( UI_CHANGESIDERGB_NTY, CMoonAdjustDlg::OnSetChangeSideRGBNty, pThis, CMoonAdjustDlg );
	//REG_MSG_HANDLER( UI_MoonSecDefault_Nty, CMoonAdjustDlg::OnSetDefaultParamNty, pThis, CMoonAdjustDlg );
	REG_MSG_HANDLER( UI_MoonTool_ReferenceLine_IND, CMoonAdjustDlg::OnReferenceLineInd, pThis, CMoonAdjustDlg );
	REG_MSG_HANDLER( UI_MoonTool_HorizontalFlip_IND, CMoonAdjustDlg::OnHorizontalFlipInd, pThis, CMoonAdjustDlg );
	REG_MSG_HANDLER( UI_MoonTool_TrapezoidalCor_IND, CMoonAdjustDlg::OnTrapezoidalCorInd, pThis, CMoonAdjustDlg );

	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_DISTORTPARAM_IND, CMoonAdjustDlg::OnSetCamDistortParamInd, pThis, CMoonAdjustDlg );
	REG_MSG_HANDLER( UI_MOONTOOL_CamSel_IND, CMoonAdjustDlg::OnCameraSelectInd, pThis, CMoonAdjustDlg );
	
	REG_MSG_HANDLER( UI_MoonTool_TraCorValue_IND, CMoonAdjustDlg::OnTraCorValueInd, pThis, CMoonAdjustDlg );

	REG_MSG_HANDLER( UI_MoonTool_SnapShot_IND, CMoonAdjustDlg::OnSnapShotNty, pThis, CMoonAdjustDlg );

	REG_MSG_HANDLER( UI_MOONTOOL_CAMPARAMDEFAULT_IND, CMoonAdjustDlg::OnCameraSelectInd, pThis, CMoonAdjustDlg );

	REG_MSG_HANDLER( UI_SETCOLORRGB_IND, CMoonAdjustDlg::OnSetColorRGBInd, pThis, CMoonAdjustDlg );

	REG_MSG_HANDLER( UI_DIRECT_SETCOLORRGB_IND, CMoonAdjustDlg::OnSetDirectColorRGBInd, pThis, CMoonAdjustDlg );

	REG_MSG_HANDLER( UI_AUTOSETCOLORCONSTANCY_IND, CMoonAdjustDlg::OnSetAutoColConstancyInd, pThis, CMoonAdjustDlg );

	REG_MSG_HANDLER( UI_MoonTool_ColorSwitch_IND, CMoonAdjustDlg::OnSetOnColorSwitchInd, pThis, CMoonAdjustDlg );

	//延时矫正
    REG_MSG_HANDLER( UI_SETDELAYCORRECT_IND, CMoonAdjustDlg::OnSetDelayCorrectInd, pThis, CMoonAdjustDlg );
	REG_MSG_HANDLER( UI_SETDELAYCORRECT_NTY, CMoonAdjustDlg::OnSetDelayCorrectNty, pThis, CMoonAdjustDlg );

	return;
}

void CMoonAdjustDlg::UnRegFunc( )
{
	return ;
}

bool CMoonAdjustDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	UIFACTORYMGR_PTR->LoadScheme(m_strSchemeDisable,m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme("SchmNonExist",m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme("SchmNormal",m_pWndTree);

	return true;
}

void CMoonAdjustDlg::Clear()
{
	UIFACTORYMGR_PTR->LoadScheme("SchmClearSnap",m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme("SchmNonExist",m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme("SchmNormal",m_pWndTree);
	m_bIsFirstGroupUsed = !m_bIsFirstGroupUsed;					
	ReleaseSnapImage();											//释放正在占用的图片资源
	m_bIsFirstGroupUsed = FALSE;
	m_bIsSaveAsSnapShot = FALSE;
	m_bIsOption = FALSE;
	if( m_emFileFtpStatus != emFtpEnd )
	{
		m_cFtp.EndFtpFile();
	}
	return ;
}

void CMoonAdjustDlg::RegCBFun()
{
	CMoonAdjustDlg *pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::InitWnd", CMoonAdjustDlg::InitWnd, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRefLineSwitchBtnChange", CMoonAdjustDlg::OnRefLineSwitchBtnChange, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnHorFlipSwitchBtnChange", CMoonAdjustDlg::OnHorFlipSwitchBtnChange, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnSnapShotBtnClick", CMoonAdjustDlg::OnSnapShotBtnClick, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnSnapShotSaveBtnClick", CMoonAdjustDlg::OnSnapShotSaveBtnClick, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnTraCorSwitchBtnChange", CMoonAdjustDlg::OnTraCorSwitchBtnChange, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRgbConsisSwitchBtnChange", CMoonAdjustDlg::OnRgbConsisSwitchBtnChange, pThis, CMoonAdjustDlg );

//	水平矫正
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnHorCorReduceHold", CMoonAdjustDlg::OnBtnHorCorReduceHold, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnHorCorReduceHoldEnd", CMoonAdjustDlg::OnBtnHorCorReduceHoldEnd, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnHorCorEditChange", CMoonAdjustDlg::OnHorCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnHorCorEditKillFocus", CMoonAdjustDlg::OnHorCorEditKillFocus, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnHorCorIncreaseHold", CMoonAdjustDlg::OnBtnHorCorIncreaseHold, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnHorCorIncreaseHoldEnd", CMoonAdjustDlg::OnBtnHorCorIncreaseHoldEnd, pThis, CMoonAdjustDlg );

//	水平拉伸
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnHorStrReduceHold", CMoonAdjustDlg::OnBtnHorStrReduceHold, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnHorStrReduceHoldEnd", CMoonAdjustDlg::OnBtnHorStrReduceHoldEnd, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnHorStrEditChange", CMoonAdjustDlg::OnHorStrEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnHorStrEditKillFocus", CMoonAdjustDlg::OnHorStrEditKillFocus, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnHorStrIncreaseHold", CMoonAdjustDlg::OnBtnHorStrIncreaseHold, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnHorStrIncreaseHoldEnd", CMoonAdjustDlg::OnBtnHorStrIncreaseHoldEnd, pThis, CMoonAdjustDlg );

//	垂直矫正
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnVerCorReduceHold", CMoonAdjustDlg::OnBtnVerCorReduceHold, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnVerCorReduceHoldEnd", CMoonAdjustDlg::OnBtnVerCorReduceHoldEnd, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnVerCorEditChange", CMoonAdjustDlg::OnVerCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnVerCorEditKillFocus", CMoonAdjustDlg::OnVerCorEditKillFocus, pThis, CMoonAdjustDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnVerCorIncreaseHold", CMoonAdjustDlg::OnBtnVerCorIncreaseHold, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnVerCorIncreaseHoldEnd", CMoonAdjustDlg::OnBtnVerCorIncreaseHoldEnd, pThis, CMoonAdjustDlg );
//	垂直拉伸

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnVerStrReduceHold", CMoonAdjustDlg::OnBtnVerStrReduceHold, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnVerStrReduceHoldEnd", CMoonAdjustDlg::OnBtnVerStrReduceHoldEnd, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnVerStrEditChange", CMoonAdjustDlg::OnVerStrEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnVerStrEditKillFocus", CMoonAdjustDlg::OnVerStrEditKillFocus, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnVerStrIncreaseHold", CMoonAdjustDlg::OnBtnVerStrIncreaseHold, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBtnVerStrIncreaseHoldEnd", CMoonAdjustDlg::OnBtnVerStrIncreaseHoldEnd, pThis, CMoonAdjustDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnContrastAreaBtnClick", CMoonAdjustDlg::OnContrastAreaBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnCorrectParaBtnClick", CMoonAdjustDlg::OnCorrectParaBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnAutoCalculateBtnClick", CMoonAdjustDlg::OnAutoCalculateBtnClick, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRLeftReduceBtnClick", CMoonAdjustDlg::OnRLeftReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRLeftCorEditChange", CMoonAdjustDlg::OnRLeftCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRLeftCorEditKillFocus", CMoonAdjustDlg::OnRLeftCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRLeftIncreaseBtnClick", CMoonAdjustDlg::OnRLeftIncreaseBtnClick, pThis, CMoonAdjustDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGLeftReduceBtnClick", CMoonAdjustDlg::OnGLeftReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGLeftCorEditChange", CMoonAdjustDlg::OnGLeftCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGLeftCorEditKillFocus", CMoonAdjustDlg::OnGLeftCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGLeftIncreaseBtnClick", CMoonAdjustDlg::OnGLeftIncreaseBtnClick, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBLeftReduceBtnClick", CMoonAdjustDlg::OnBLeftReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBLeftCorEditChange", CMoonAdjustDlg::OnBLeftCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBLeftCorEditKillFocus", CMoonAdjustDlg::OnBLeftCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBLeftIncreaseBtnClick", CMoonAdjustDlg::OnBLeftIncreaseBtnClick, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRMidReduceBtnClick", CMoonAdjustDlg::OnRMidReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRMidCorEditChange", CMoonAdjustDlg::OnRMidCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRMidCorEditKillFocus", CMoonAdjustDlg::OnRMidCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRMidIncreaseBtnClick", CMoonAdjustDlg::OnRMidIncreaseBtnClick, pThis, CMoonAdjustDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGMidReduceBtnClick", CMoonAdjustDlg::OnGMidReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGMidCorEditChange", CMoonAdjustDlg::OnGMidCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGMidCorEditKillFocus", CMoonAdjustDlg::OnGMidCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGMidIncreaseBtnClick", CMoonAdjustDlg::OnGMidIncreaseBtnClick, pThis, CMoonAdjustDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBMidReduceBtnClick", CMoonAdjustDlg::OnBMidReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBMidCorEditChange", CMoonAdjustDlg::OnBMidCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBMidCorEditKillFocus", CMoonAdjustDlg::OnBMidCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBMidIncreaseBtnClick", CMoonAdjustDlg::OnBMidIncreaseBtnClick, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRRightReduceBtnClick", CMoonAdjustDlg::OnRRightReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRRightCorEditChange", CMoonAdjustDlg::OnRRightCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRRightCorEditKillFocus", CMoonAdjustDlg::OnRRightCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRRightIncreaseBtnClick", CMoonAdjustDlg::OnRRightIncreaseBtnClick, pThis, CMoonAdjustDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGRightReduceBtnClick", CMoonAdjustDlg::OnGRightReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGRightCorEditChange", CMoonAdjustDlg::OnGRightCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGRightCorEditKillFocus", CMoonAdjustDlg::OnGRightCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnGRightIncreaseBtnClick", CMoonAdjustDlg::OnGRightIncreaseBtnClick, pThis, CMoonAdjustDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBRightReduceBtnClick", CMoonAdjustDlg::OnBRightReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBRightCorEditChange", CMoonAdjustDlg::OnBRightCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBRightCorEditKillFocus", CMoonAdjustDlg::OnBRightCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnBRightIncreaseBtnClick", CMoonAdjustDlg::OnBRightIncreaseBtnClick, pThis, CMoonAdjustDlg );

	REG_DEFAULT_WINDOW_MSG( WM_MoonTool_FTPSnapDownLoad );
	
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnDownloadProgress", CMoonAdjustDlg::OnDownloadProgress, pThis, CMoonAdjustDlg );

    //延时矫正
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnLeftDelayReduceBtnClick", CMoonAdjustDlg::OnLeftDelayReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnLeftDelayCorEditChange", CMoonAdjustDlg::OnLeftDelayCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnLeftDelayCorEditKillFocus", CMoonAdjustDlg::OnLeftDelayCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnLeftDelayIncreaseBtnClick", CMoonAdjustDlg::OnLeftDelayIncreaseBtnClick, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnMiddleDelayReduceBtnClick", CMoonAdjustDlg::OnMiddleDelayReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnMiddleDelayCorEditChange", CMoonAdjustDlg::OnMiddleDelayCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnMiddleDelayCorEditKillFocus", CMoonAdjustDlg::OnMiddleDelayCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnMiddleDelayIncreaseBtnClick", CMoonAdjustDlg::OnMiddleDelayIncreaseBtnClick, pThis, CMoonAdjustDlg );

	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRightDelayReduceBtnClick", CMoonAdjustDlg::OnRightDelayReduceBtnClick, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRightDelayCorEditChange", CMoonAdjustDlg::OnRightDelayCorEditChange, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRightDelayCorEditKillFocus", CMoonAdjustDlg::OnRightDelayCorEditKillFocus, pThis, CMoonAdjustDlg );
	REG_GOBAL_MEMBER_FUNC( "CMoonAdjustDlg::OnRightDelayIncreaseBtnClick", CMoonAdjustDlg::OnRightDelayIncreaseBtnClick, pThis, CMoonAdjustDlg );

	return ;
}

void CMoonAdjustDlg::UnRegMsg( )
{
	return ;
}

bool CMoonAdjustDlg::OnRefLineSwitchBtnChange( const IArgs & arg )
{
	bool bOpen = false;

	UIFACTORYMGR_PTR->GetSwitchState(m_strRefLineSwitchBtn,bOpen,m_pWndTree);
	if ( COMIFMGRPTR->SetReferenceLineCmd( (bOpen==true)?TRUE:FALSE )!= NO_ERROR )
	{
		WARNMESSAGE( "参考线设置请求发送失败" );
		UIFACTORYMGR_PTR->SetSwitchState(m_strRefLineSwitchBtn,(( bOpen == true )? false:true ),m_pWndTree);
	}

	return true;
}

bool CMoonAdjustDlg::OnHorFlipSwitchBtnChange( const IArgs & arg )
{
	bool bOpen = false;
	
	UIFACTORYMGR_PTR->GetSwitchState(m_strHorFlipSwitchBtn,bOpen,m_pWndTree);

	if ( COMIFMGRPTR->SetHorizontalFlipCmd((bOpen==true)?TRUE:FALSE ) != NO_ERROR )
	{
		WARNMESSAGE( "参考线设置请求发送失败" );
		UIFACTORYMGR_PTR->SetSwitchState(m_strRefLineSwitchBtn,(( bOpen == true )? false:true ),m_pWndTree);
	}
	return true;
}

bool CMoonAdjustDlg::OnSnapShotBtnClick( const IArgs & arg )
{	
	u16 wRet =  COMIFMGRPTR->SnapShotCmd( );
	if ( wRet != NO_ERROR )
	{
		MSG_BOX_OK("快照请求发送失败！");
		return false;
	}
	m_bIsOption = TRUE;
	WARNMESSAGE("快照准备中，请稍等...");
//	UIFACTORYMGR_PTR->LoadScheme("SchmFtpBegin",NULL,g_strMoonMainFrame); 
	UIFACTORYMGR_PTR->LoadScheme("SchmFtpBegin",m_pWndTree);
	return true;
}

bool CMoonAdjustDlg::OnSnapShotSaveBtnClick( const IArgs & arg )
{
	String strExpFileFullPath;

	m_bIsSaveAsSnapShot = TRUE;

	strExpFileFullPath = UIDATAMGR_PTR->OpenBrowseForFolder("",NULL,FALSE);

	string strForder =  UIFACTORYMGR_PTR->GetImagePath();				//保存的路径
	string strSavePath = strForder + MOONSNAPSHOT_FILE_PATH + "\\";

	CopyImage(strSavePath,strExpFileFullPath);
//	UIDATAMGR_PTR->OpenFileDialog( strFilter, strFile, strExpFileFullPath, strExpFileName, FALSE );	
	return true;
}

bool CMoonAdjustDlg::OnTraCorSwitchBtnChange( const IArgs & arg )
{
	bool bOpen = false;
	
	UIFACTORYMGR_PTR->GetSwitchState(m_strTraCorSwitchBtn,bOpen,m_pWndTree);
	if ( COMIFMGRPTR->SetTrapezoidalCorCmd((bOpen==true)?TRUE:FALSE ) != NO_ERROR )
	{
		WARNMESSAGE( "参考线设置请求发送失败" );
		UIFACTORYMGR_PTR->SetSwitchState( m_strTraCorSwitchBtn, (( bOpen == true )? false:true ), m_pWndTree );
		if( bOpen )
		{
			UIFACTORYMGR_PTR->LoadScheme(m_strSchemeEnable, m_pWndTree);
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme(m_strSchemeDisable, m_pWndTree);
		}
	}
	return true;
}

//	水平矫正
bool CMoonAdjustDlg::OnBtnHorCorReduceHold( const IArgs & arg )
{
	u16 nRet = COMIFMGRPTR->SetTraCorParamCmd( em_HorizonCorrect, emCorrectReduce);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "水平矫正设置请求发送失败" );
	}
	
	return true;
}

bool CMoonAdjustDlg::OnBtnHorCorReduceHoldEnd( const IArgs & arg )
{
	return true;
}

bool CMoonAdjustDlg::OnHorCorEditChange( const IArgs & arg )
{
	UpdateEditNum(arg,m_strHorCorEdit,m_mapMaxValue[m_strHorCorEdit.c_str()], 0);
	return true;
}

bool CMoonAdjustDlg::OnHorCorEditKillFocus( const IArgs & arg )
{
	string strHorCorValue = "";
	UIFACTORYMGR_PTR->GetCaption(m_strHorCorEdit.c_str(),strHorCorValue,m_pWndTree);
	
	s32 nHorCorValue = 0;
	nHorCorValue = atoi(strHorCorValue.c_str());
	nHorCorValue += 1500;

	if ( nHorCorValue != m_tHorParam.dwCorrectLevel )
	{
		TTPDistortParam tTPDistortParam;
		tTPDistortParam = m_tHorParam;
		tTPDistortParam.dwCorrectLevel = nHorCorValue;
		
		u16 nRet = COMIFMGRPTR->CamKeystoneAdjust( tTPDistortParam , em_HorizonCorrect );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE("设置水平矫正消息发送失败!");
			
			SetTraCorrectionParam(em_HorizonCorrect,m_tVerParam);
		}
	}

	return true;
}

bool CMoonAdjustDlg::OnBtnHorCorIncreaseHold( const IArgs & arg )
{
	u16 nRet = COMIFMGRPTR->SetTraCorParamCmd( em_HorizonCorrect, emCorrectEnlarge);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "水平矫正设置请求发送失败" );
	}
	return true;
}

bool CMoonAdjustDlg::OnBtnHorCorIncreaseHoldEnd( const IArgs & arg )
{
	return true;
}

//	水平拉伸
bool CMoonAdjustDlg::OnBtnHorStrReduceHold( const IArgs & arg )
{
	u16 nRet = COMIFMGRPTR->SetTraCorParamCmd( em_HorizonStretch, emCorrectReduce);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "水平拉伸设置请求发送失败" );
	}
	return true;
}

bool CMoonAdjustDlg::OnBtnHorStrReduceHoldEnd( const IArgs & arg )
{
	return true;
}

bool CMoonAdjustDlg::OnHorStrEditChange( const IArgs & arg )
{
	UpdateEditNum(arg,m_strHorStrEdit,m_mapMaxValue[m_strHorStrEdit.c_str()], 0);
	return true;
}

bool CMoonAdjustDlg::OnHorStrEditKillFocus( const IArgs & arg )
{
	string strHorStrValue = "";
	UIFACTORYMGR_PTR->GetCaption(m_strHorStrEdit.c_str(),strHorStrValue,m_pWndTree);
	
	s32 nHorStrValue = 0;
	nHorStrValue = atoi(strHorStrValue.c_str());
	nHorStrValue += 512;

	if ( nHorStrValue != m_tHorParam.dwStretchRegion )
	{
		TTPDistortParam tTPDistortParam;
		tTPDistortParam = m_tHorParam;
		tTPDistortParam.dwStretchRegion = nHorStrValue;
		
		u16 nRet = COMIFMGRPTR->CamKeystoneAdjust( tTPDistortParam , em_HorizonStretch );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE("设置水平拉伸消息发送失败!");
			
			SetTraCorrectionParam(em_HorizonStretch,m_tVerParam);
		}
	}

	return true;
}

bool CMoonAdjustDlg::OnBtnHorStrIncreaseHold( const IArgs & arg )
{
	u16 nRet = COMIFMGRPTR->SetTraCorParamCmd( em_HorizonStretch, emCorrectEnlarge);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "水平矫正设置请求发送失败" );
	}
	return true;
}

bool CMoonAdjustDlg::OnBtnHorStrIncreaseHoldEnd( const IArgs & arg )
{
	return true;
}

//垂直矫正
bool CMoonAdjustDlg::OnBtnVerCorReduceHold( const IArgs & arg )
{
	u16 nRet = COMIFMGRPTR->SetTraCorParamCmd( em_VerticalCorrect, emCorrectReduce);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "垂直矫正设置请求发送失败" );
	}
	return true;
}

bool CMoonAdjustDlg::OnBtnVerCorReduceHoldEnd( const IArgs & arg )
{
	return true;
}

bool CMoonAdjustDlg::OnContrastAreaBtnClick(const IArgs & arg)
{
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrSetContrastAreaDlg );

// 	for ( vector<string> ::size_type nIndex = 0; nIndex < m_vecFilePath.size(); nIndex ++ )
// 	{
// 		SETCONTRASTAREALOGIC->SetContrastAreaImage(m_vecFilePath[nIndex]);
// 	}

	return true;
}

bool CMoonAdjustDlg::OnCorrectParaBtnClick(const IArgs & arg)
{
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrCorrectParamDlg );

	return true;
}

bool CMoonAdjustDlg::OnAutoCalculateBtnClick(const IArgs & arg)
{	
	u16 nRet = COMIFMGRPTR->SetAutoSetColorConstancyCmd();

	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "颜色一致性自动计算请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnRgbConsisSwitchBtnChange(const IArgs & arg)
{
	bool bOpen = false;
	
	UIFACTORYMGR_PTR->GetSwitchState( m_strRgbConsisSwitchBtn, bOpen, m_pWndTree );
	if ( COMIFMGRPTR->SetRgbConsistSwitchCmd((bOpen==true)?TRUE:FALSE ) != NO_ERROR )
	{
		WARNMESSAGE( "颜色一致性开关请求发送失败" );
		UIFACTORYMGR_PTR->SetSwitchState( m_strRgbConsisSwitchBtn, (( bOpen == true )? false:true ), m_pWndTree );
	}

	return true;
}

bool CMoonAdjustDlg::OnRLeftReduceBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(0, emColorRed, emCorrectReduce);

	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnRLeftCorEditChange(const IArgs & arg)
{
	UpdateEditNum(arg,m_strRLeftCorEdit,m_mapMaxValue[m_strRLeftCorEdit.c_str()], m_mapMinValue[m_strRLeftCorEdit.c_str()]);
	
	return true;
}

bool CMoonAdjustDlg::OnRLeftCorEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRLeftCorEdit, str, m_pWndTree );

	SetRGBColorValCmd(str.c_str(), 0, emColorRed);

	return true;
}

bool CMoonAdjustDlg::OnRLeftIncreaseBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(0, emColorRed, emCorrectEnlarge);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnGLeftReduceBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(0, emColorGreen, emCorrectReduce);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnGLeftCorEditChange(const IArgs & arg)
{
	UpdateEditNum(arg,m_strGLeftCorEdit,m_mapMaxValue[m_strGLeftCorEdit.c_str()], m_mapMinValue[m_strGLeftCorEdit.c_str()]);

	return true;
}

bool CMoonAdjustDlg::OnGLeftCorEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strGLeftCorEdit, str, m_pWndTree );
	
	SetRGBColorValCmd(str.c_str(), 0, emColorGreen);

	return true;
}

bool CMoonAdjustDlg::OnGLeftIncreaseBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(0, emColorGreen, emCorrectEnlarge);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnBLeftReduceBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(0, emColorBlue, emCorrectReduce);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnBLeftCorEditChange(const IArgs & arg)
{
	UpdateEditNum( arg, m_strBLeftCorEdit, m_mapMaxValue[m_strBLeftCorEdit.c_str()], m_mapMinValue[m_strBLeftCorEdit.c_str()]);

	return true;
}

bool CMoonAdjustDlg::OnBLeftCorEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strBLeftCorEdit, str, m_pWndTree );
	
	SetRGBColorValCmd(str.c_str(), 0, emColorBlue);
	return true;
}

bool CMoonAdjustDlg::OnBLeftIncreaseBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(0, emColorBlue, emCorrectEnlarge);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnRMidReduceBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(1, emColorRed, emCorrectReduce);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnRMidCorEditChange(const IArgs & arg)
{
	UpdateEditNum(arg,m_strRMidCorEdit,m_mapMaxValue[m_strRMidCorEdit.c_str()], m_mapMinValue[m_strRMidCorEdit.c_str()]);

	return true;
}

bool CMoonAdjustDlg::OnRMidCorEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRMidCorEdit, str, m_pWndTree );
	
	SetRGBColorValCmd(str.c_str(), 1, emColorRed);
	return true;
}

bool CMoonAdjustDlg::OnRMidIncreaseBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(1, emColorRed, emCorrectEnlarge);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;	
}

bool CMoonAdjustDlg::OnGMidReduceBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(1, emColorGreen, emCorrectReduce);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnGMidCorEditChange(const IArgs & arg)
{
	UpdateEditNum(arg,m_strGMidCorEdit,m_mapMaxValue[m_strRMidCorEdit.c_str()], m_mapMinValue[m_strGMidCorEdit.c_str()]);

	return true;
}

bool CMoonAdjustDlg::OnGMidCorEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strGMidCorEdit, str, m_pWndTree );
	
	SetRGBColorValCmd(str.c_str(), 1, emColorGreen);

	return true;
}

bool CMoonAdjustDlg::OnGMidIncreaseBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(1, emColorGreen, emCorrectEnlarge);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnBMidReduceBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(1, emColorBlue, emCorrectReduce);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnBMidCorEditChange(const IArgs & arg)
{
	UpdateEditNum(arg,m_strBMidCorEdit,m_mapMaxValue[m_strBMidCorEdit.c_str()], m_mapMinValue[m_strBMidCorEdit.c_str()]);

	return true;
}

bool CMoonAdjustDlg::OnBMidCorEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strBMidCorEdit, str, m_pWndTree );
	
	SetRGBColorValCmd(str.c_str(), 1, emColorBlue);

	return true;
}

bool CMoonAdjustDlg::OnBMidIncreaseBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(1, emColorBlue, emCorrectEnlarge);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnRRightReduceBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(2, emColorRed, emCorrectReduce);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnRRightCorEditChange(const IArgs & arg)
{
	UpdateEditNum(arg,m_strRRightCorEdit,m_mapMaxValue[m_strRRightCorEdit.c_str()], m_mapMinValue[m_strRRightCorEdit.c_str()]);

	return true;
}

bool CMoonAdjustDlg::OnRRightCorEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRRightCorEdit, str, m_pWndTree );
	
	SetRGBColorValCmd(str.c_str(), 2, emColorRed);
	return true;
}

bool CMoonAdjustDlg::OnRRightIncreaseBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(2, emColorRed, emCorrectEnlarge);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnGRightReduceBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(2, emColorGreen, emCorrectReduce);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnGRightCorEditChange(const IArgs & arg)
{
	UpdateEditNum(arg,m_strGRightCorEdit,m_mapMaxValue[m_strGRightCorEdit.c_str()], m_mapMinValue[m_strGRightCorEdit.c_str()]);

	return true;
}

bool CMoonAdjustDlg::OnGRightCorEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strGRightCorEdit, str, m_pWndTree );
	
	SetRGBColorValCmd(str.c_str(), 2, emColorGreen);
	return true;
}

bool CMoonAdjustDlg::OnGRightIncreaseBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(2, emColorGreen, emCorrectEnlarge);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnBRightReduceBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(2, emColorBlue, emCorrectReduce);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnBRightCorEditChange(const IArgs & arg)
{
	UpdateEditNum(arg,m_strBRightCorEdit,m_mapMaxValue[m_strBRightCorEdit.c_str()], m_mapMinValue[m_strBRightCorEdit.c_str()]);

	return true;
}

bool CMoonAdjustDlg::OnBRightCorEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strBRightCorEdit, str, m_pWndTree );
	
	SetRGBColorValCmd(str.c_str(), 2, emColorBlue);
	return true;
}

bool CMoonAdjustDlg::OnBRightIncreaseBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetCorConsistRGBCmd(2, emColorBlue, emCorrectEnlarge);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置RGB颜色一致性请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnVerCorEditChange( const IArgs & arg )
{
	UpdateEditNum(arg,m_strVerCorEdit,m_mapMaxValue[m_strVerCorEdit.c_str()], 0);
	return true;
}

bool CMoonAdjustDlg::OnVerCorEditKillFocus( const IArgs & arg )
{
	string strVerCorValue = "";
	UIFACTORYMGR_PTR->GetCaption(m_strVerCorEdit.c_str(),strVerCorValue,m_pWndTree);
	
	s32 nVerCorValue = 0;
	nVerCorValue = atoi(strVerCorValue.c_str());
	nVerCorValue += 1500;

	if ( nVerCorValue != m_tVerParam.dwCorrectLevel )
	{
		TTPDistortParam tTPDistortParam;
		tTPDistortParam = m_tVerParam;
		tTPDistortParam.dwCorrectLevel = nVerCorValue;
		
		u16 nRet = COMIFMGRPTR->CamKeystoneAdjust( tTPDistortParam , em_VerticalCorrect );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE("设置垂直矫正消息发送失败!");
			
			SetTraCorrectionParam(em_VerticalCorrect,m_tVerParam);
		}
	}
	return true;
}

bool CMoonAdjustDlg::OnBtnVerCorIncreaseHold( const IArgs & arg )
{
	u16 nRet = COMIFMGRPTR->SetTraCorParamCmd( em_VerticalCorrect, emCorrectEnlarge);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "垂直矫正设置请求发送失败" );
	}
	return true;
}

bool CMoonAdjustDlg::OnBtnVerCorIncreaseHoldEnd( const IArgs & arg )
{
	return true;
}

//垂直拉伸

bool CMoonAdjustDlg::OnBtnVerStrReduceHold( const IArgs & arg )
{
	u16 nRet = COMIFMGRPTR->SetTraCorParamCmd( em_VerticalStretch, emCorrectReduce);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "垂直拉伸设置请求发送失败" );
	}
	return true;
}

bool CMoonAdjustDlg::OnBtnVerStrReduceHoldEnd( const IArgs & arg )
{
	return true;
}

bool CMoonAdjustDlg::OnVerStrEditChange( const IArgs & arg )
{
	UpdateEditNum(arg,m_strVerStrEdit,m_mapMaxValue[m_strVerStrEdit.c_str()], 0);
	return true;
}

bool CMoonAdjustDlg::OnVerStrEditKillFocus( const IArgs & arg )
{
	string strVerStrValue = "";
	UIFACTORYMGR_PTR->GetCaption(m_strVerStrEdit.c_str(),strVerStrValue,m_pWndTree);

	s32 nVerStrValue = 0;
	nVerStrValue = atoi(strVerStrValue.c_str());
	nVerStrValue += 512;

	if ( nVerStrValue != m_tVerParam.dwStretchRegion )
	{
		TTPDistortParam tTPDistortParam;
		tTPDistortParam = m_tVerParam;
		tTPDistortParam.dwStretchRegion = nVerStrValue;

		u16 nRet = COMIFMGRPTR->CamKeystoneAdjust( tTPDistortParam , em_VerticalStretch );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE("设置垂直拉伸消息发送失败!");
			
			SetTraCorrectionParam(em_VerticalStretch,m_tVerParam);
		}
	}

	return true;
}

bool CMoonAdjustDlg::OnBtnVerStrIncreaseHold( const IArgs & arg )
{
	u16 nRet = COMIFMGRPTR->SetTraCorParamCmd( em_VerticalStretch, emCorrectEnlarge);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "垂直拉伸设置请求发送失败" );
	}
	return true;
}

bool CMoonAdjustDlg::OnBtnVerStrIncreaseHoldEnd( const IArgs & arg )
{
	return true;
}


void CMoonAdjustDlg::UpdateEditNum( const IArgs & arg, String strEditName, s32 nMaxValue, s32 nMinValue)
{
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &arg ));
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}

	Value_WindowCaption valueWindowCaption;
	UIFACTORYMGR_PTR->GetPropertyValue( valueWindowCaption, strEditName, m_pWndTree );
	
	CString str;
	str = OnlyFloat( valueWindowCaption.strCaption.c_str() );
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	else
	{
		/*string strEditValue;
		UIFACTORYMGR_PTR->GetCaption( strEditName,strEditValue,m_pWndTree);
		s32 nValue = atoi(strEditValue.c_str());
		if ( nValue > nMaxValue )
		{
			nValue = nMaxValue;
		}
		s8 chValue[10] = "";
		sprintf(chValue,"%d",nValue);
		UIFACTORYMGR_PTR->SetCaption(strEditName,chValue,m_pWndTree);
		
		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strEditName, m_pWndTree );
		//将光标移动至最后一个字
		if ( pWnd )
		{
			(( CEdit *) pWnd)->SetSel( -1 );
		}*/
	}
}

LRESULT CMoonAdjustDlg::OnSnapShotNty( WPARAM wparam, LPARAM lparam )
{
	TTPSnapshotInfo tSnapShotInfo = *( TTPSnapshotInfo*)(lparam);
	if ( ( tSnapShotInfo.byIndex < 3 ) ||( m_bIsOption == FALSE ))
	{
		return S_OK;
	}

	m_bIsOption = FALSE;

	bool bSuccess = *(BOOL*)wparam;

	if ( bSuccess == false )
	{
		WARNMESSAGE("快照请求失败!");
		UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
		return S_FALSE;
	}
	
	WARNMESSAGE("正在下载快照");
	UIFACTORYMGR_PTR->LoadScheme("SchmBegin",NULL,g_strMoonMainFrame);              //为了防止鼠标左键按下后，界面收不到FTP消息，所以在传输中，先将MainFrame禁止拖动 
	m_bIsSaveAsSnapShot = FALSE;													   //为什么没有收到消息问题 还在调查

	m_cFtp.RegisterMsgHandle( WM_MoonTool_FTPSnapDownLoad );
	
	u32 dwIp;
	MOONLIBDATAMGRPTR->GetLoginIp(dwIp);
	CString strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, MT_TEL_USRNAME, MT_TEL_PWD );
	if ( !bRet )
	{
		MSG_BOX_OK("连接服务器失败！");	
		return S_FALSE;
	}
	
	if ( m_cFtp.ConnectServer() )
	{
		m_vecFilePath.clear();
		m_vecDownFile.clear();
		
		if ( m_cFtp.FindfFtpFile( MoonTool_SNAPSHOT_PATH, MOONSNAPSHOT_FILE_NAME1 ) )
		{
			m_vecDownFile.push_back( MOONSNAPSHOT_FILE_NAME1);
		}
		if ( m_cFtp.FindfFtpFile( MoonTool_SNAPSHOT_PATH, MOONSNAPSHOT_FILE_NAME2 ) )
		{
			m_vecDownFile.push_back( MOONSNAPSHOT_FILE_NAME2 );
		}
		if ( m_cFtp.FindfFtpFile( MoonTool_SNAPSHOT_PATH, MOONSNAPSHOT_FILE_NAME3 ) )
		{
			m_vecDownFile.push_back( MOONSNAPSHOT_FILE_NAME3 );
		}
		
		if ( m_vecDownFile.size() > 0 )
		{
			DownloadCore( MoonTool_SNAPSHOT_PATH, m_vecDownFile.at(0) );
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
			UIFACTORYMGR_PTR->LoadScheme("SchmEnd",NULL,g_strMoonMainFrame); 
			CMsgDispatch::SendMessage(WM_MoonTool_StatusSet,NULL,NULL);
			WARNMESSAGE("下载失败");
		//	MSG_BOX_OK("连接服务器失败！");	
			return S_FALSE;
		}
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme("SchmEnd",NULL,g_strMoonMainFrame); 
		CMsgDispatch::SendMessage(WM_MoonTool_StatusSet,NULL,NULL);
		WARNMESSAGE("下载失败");
		MSG_BOX_OK("连接服务器失败！");	
		return S_FALSE;
	}
	return S_OK;	
}

BOOL CMoonAdjustDlg::DownloadCore(const String& strFilePath,const String & strFileName )
{	
	string strForder = "";
	string strSavePath = "";
	string strFileSaveName = "";

	Window * pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_strMoonAdjustDlg );
	
	strFileSaveName = GetSnapShotFileName(strFileName);
	strForder = UIFACTORYMGR_PTR->GetImagePath();				//保存的路径
	strSavePath = strForder + MOONSNAPSHOT_FILE_PATH + "\\";
	strSavePath += strFileSaveName;
	
	if ( !UIDATAMGR_PTR->RecusionMkDir( UIDATAMGR_PTR->GetFileFolderPath(strSavePath).c_str() ))
	{
		MSG_BOX_OK( "创建文件目录失败!" );	
		
		return true;
	}

	m_cFtp.RegisterMsgHandle( WM_MoonTool_FTPSnapDownLoad );

	string strSrcPath = "";
	strSrcPath += MOONSNAPSHOT_FILE_PATH;						//加载图片的相对路径
	strSrcPath += "\\" + strFileSaveName;
	m_vecFilePath.push_back(strSrcPath.c_str());
	
	if ( NULL != pWnd )
	{
		String strRemoteFile;
		strRemoteFile += strFilePath + strFileName;
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

bool CMoonAdjustDlg::OnDownloadProgress( const IArgs & arg )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);
	
	if ( m_emFileFtpStatus ==  emFtpEnd )
	{
		DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP接口0为成功  默认失败
		if ( 0 == dwSuccess )
		{
			if ( m_vecDownFile.size() > 0 )
			{
				vector<String>::iterator itr = m_vecDownFile.begin();
				m_vecDownFile.erase(itr);
				u32 nNum= m_vecDownFile.size();
				if ( nNum > 0 )
				{
					DownloadCore( MoonTool_SNAPSHOT_PATH, m_vecDownFile.at(0) );
				}
				else
				{
					WARNMESSAGE("快照下载完成");
					string strForder = UIFACTORYMGR_PTR->GetImagePath();				//3张快照下载完成后，未加载进内存前，对快照进行备份，另存为后，只需对备份快照拷贝就行
					string strSavePath = strForder + MOONSNAPSHOT_FILE_PATH + "\\";
					CopyImage(strSavePath,strSavePath);

					for ( vector<string> ::size_type nIndex = 0; nIndex < m_vecFilePath.size(); nIndex ++ )
					{
						if ( SetSnapShotImage(m_vecFilePath[nIndex]) != true )
						{
							MSG_BOX_OK("设置快照图片失败");	
							break;
						}
					}
					m_cFtp.EndFtpFile();

					m_bIsFirstGroupUsed = !m_bIsFirstGroupUsed;
					ReleaseSnapImage();							//释放上次被占用的图片资源，供下次使用
					UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
					UIFACTORYMGR_PTR->LoadScheme("SchmEnd",NULL,g_strMoonMainFrame);
					CMsgDispatch::SendMessage(WM_MoonTool_StatusSet,NULL,NULL);
					CheckData("MoonAdjustDlg/SnapShotSaveBtn",true);        //成功后，将该字符串存入容器中，下次失败，可以根据容器大小，来判断是否禁用另存为操作
					UIFACTORYMGR_PTR->LoadScheme("SchmExist",m_pWndTree);
				}
			} 	
		}
		else
		{
			if (( UIFACTORYMGR_PTR->IsVisible(g_strMoonMainFrame,m_pWndTree)) == FALSE )
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
				OspPrintf( TRUE, FALSE, (char*)strError.c_str() );
				MSG_BOX_OK( strError.c_str() );	
				LocalFree( pszMsg );
			}
			m_cFtp.EndFtpFile();

			UIFACTORYMGR_PTR->LoadScheme("SchmFtpEnd",m_pWndTree);
			UIFACTORYMGR_PTR->LoadScheme("SchmEnd",NULL,g_strMoonMainFrame);
			CMsgDispatch::SendMessage(WM_MoonTool_StatusSet,NULL,NULL);
			if( m_vctWndName.size() < 0 )
			{
				UIFACTORYMGR_PTR->LoadScheme("SchmNonExist",m_pWndTree);
			}
		}	
	}

	return true;
}

void CMoonAdjustDlg::ReleaseSnapImage()
{
	string strPath = "";
	string strRelFile = "";
	
	strPath += MOONSNAPSHOT_FILE_PATH;
	strPath += "\\";

	strRelFile = GetSnapShotFileName(MOONSNAPSHOT_FILE_NAME1);
	strRelFile = strPath+strRelFile;
	UIFACTORYMGR_PTR->ReleaseSingleImage(strRelFile);
	
	strRelFile = GetSnapShotFileName(MOONSNAPSHOT_FILE_NAME2);
	strRelFile = strPath+strRelFile;
	UIFACTORYMGR_PTR->ReleaseSingleImage(strRelFile);
	
	strRelFile = GetSnapShotFileName(MOONSNAPSHOT_FILE_NAME3);
	strRelFile = strPath+strRelFile;
	UIFACTORYMGR_PTR->ReleaseSingleImage(strRelFile);
}

HRESULT CMoonAdjustDlg::OnSetOnColorSwitchInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bOpen = *(BOOL*)wparam;
	BOOL bSuccess = *(BOOL*)lparam;

	if( bSuccess == FALSE )
	{
		WARNMESSAGE("颜色一致性设置请求发送失败");
		return S_FALSE;
	}
	
	UIFACTORYMGR_PTR->SetSwitchState( m_strRgbConsisSwitchBtn.c_str(), ((bOpen ==TRUE ) ? true:false), m_pWndTree );
	if( bOpen )
	{
		UIFACTORYMGR_PTR->LoadScheme("EnableColorScheme", m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("DisableColorScheme", m_pWndTree);
	}

	return S_OK;
}

bool CMoonAdjustDlg::SetSnapShotImage( const string strFileName )
{
	if ( strFileName.find(MOONSNAPSHOT_FILE_NAME1) != string::npos )
	{
		UIFACTORYMGR_PTR->SetTransStaticImage(m_vecShatShot[0],strFileName.c_str(),m_pWndTree);	
	}
	else if ( strFileName.find(MOONSNAPSHOT_FILE_NAME2) != string::npos)
	{
		UIFACTORYMGR_PTR->SetTransStaticImage(m_vecShatShot[1],strFileName.c_str(),m_pWndTree);					
	}
	else if ( strFileName.find(MOONSNAPSHOT_FILE_NAME3) != string::npos )
	{
		UIFACTORYMGR_PTR->SetTransStaticImage(m_vecShatShot[2],strFileName.c_str(),m_pWndTree);					
	}
	else
	{
		return false;
	}

	return true;
}

string CMoonAdjustDlg::GetSnapShotFileName( const string strFileName )
{
	string strNewName = "";
	
	if ( m_bIsFirstGroupUsed == FALSE )
	{
		strNewName = strFileName;
	}
	else
	{
		strNewName ="temp" + strFileName;                      //如果已经在使用第一组快照图片时，将快照保存在第二组中
	}
	
	return strNewName;
}

HRESULT CMoonAdjustDlg::OnTralCorParamInd( WPARAM wparam, LPARAM lparam )
{
    /*
	TTPMoonCamInfo tMoonCameraCfg;
	MOONLIBDATAMGRPTR->GetCamCfg( tMoonCameraCfg );

	m_bTraCorOpen = tMoonCameraCfg.bIsCorrect;

	m_tHorParam.dwCorrectLevel = tMoonCameraCfg.dwHorizonCorrect;
	m_tHorParam.dwStretchRegion = tMoonCameraCfg.dwHorizonStretch;
	m_tHorParam.dwEnable = tMoonCameraCfg.bIsCorrect;

	m_tVerParam.dwCorrectLevel = tMoonCameraCfg.dwVerticalCorrect;
	m_tVerParam.dwStretchRegion = tMoonCameraCfg.dwVerticalStretch;
	m_tVerParam.dwEnable = tMoonCameraCfg.bIsCorrect;

	SetTraCorrectionParam(em_HorizonCorrect,m_tHorParam);
	SetTraCorrectionParam(em_HorizonStretch,m_tHorParam);
	SetTraCorrectionParam(em_VerticalCorrect,m_tVerParam);
	SetTraCorrectionParam(em_VerticalStretch,m_tVerParam);

	UIFACTORYMGR_PTR->SetSwitchState(m_strTraCorSwitchBtn.c_str(),((tMoonCameraCfg.bIsCorrect ==TRUE ) ? true:false ),m_pWndTree);
	if( tMoonCameraCfg.bIsCorrect == TRUE )
	{
		UIFACTORYMGR_PTR->LoadScheme(m_strSchemeEnable,m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme(m_strSchemeDisable,m_pWndTree);
	}

	if ( m_bTraCorOpen == TRUE )
	{
		UIFACTORYMGR_PTR->LoadScheme(m_strSchemeEnable,m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme(m_strSchemeDisable,m_pWndTree);
	}
    */
	return S_OK;
}

void CMoonAdjustDlg::SetTraCorrectionParam( EmTPCorrect emTpMyOption , TTPDistortParam &tTraCorParam )
{
	s8 chValue[10] = {0};
	u32 dwValue = 0;
	switch( emTpMyOption )
	{
	case em_HorizonCorrect:
		dwValue = tTraCorParam.dwCorrectLevel-1500;
		sprintf(chValue,"%d",dwValue);
		UIFACTORYMGR_PTR->SetCaption(m_strHorCorEdit,chValue,m_pWndTree);
		break;
	case em_HorizonStretch:
		dwValue = tTraCorParam.dwStretchRegion-512;
		sprintf(chValue,"%d",dwValue);
		UIFACTORYMGR_PTR->SetCaption(m_strHorStrEdit,chValue,m_pWndTree);
		break;
	case em_VerticalCorrect:
		dwValue = tTraCorParam.dwCorrectLevel-1500;
		sprintf(chValue,"%d",dwValue);
		UIFACTORYMGR_PTR->SetCaption(m_strVerCorEdit,chValue,m_pWndTree);
		break;
	case em_VerticalStretch:
		dwValue = tTraCorParam.dwStretchRegion-512;
		sprintf(chValue,"%d",dwValue);
		UIFACTORYMGR_PTR->SetCaption(m_strVerStrEdit,chValue,m_pWndTree);
		break;
	default:
		break;
	}
}

HRESULT CMoonAdjustDlg::OnReferenceLineInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bOpen = *(BOOL*)wparam;
	BOOL bSuccess = *( BOOL*)lparam;

	if ( bSuccess == FALSE )
	{
		bOpen = m_bRefLineOpen;
		WARNMESSAGE("参考线设置失败!");
	}
	m_bRefLineOpen = bOpen;

	UIFACTORYMGR_PTR->SetSwitchState(m_strRefLineSwitchBtn.c_str(),((bOpen ==TRUE ) ? true:false) ,m_pWndTree);
	return S_OK;
}

HRESULT CMoonAdjustDlg::OnHorizontalFlipInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bOpen = *(BOOL*)wparam;
	BOOL bSuccess = *( BOOL*)lparam;
	
	if ( bSuccess == FALSE )
	{
		bOpen = m_bHorFlipOpen;
		WARNMESSAGE("水平翻转设置失败!");
	}
	m_bHorFlipOpen= bOpen;
	UIFACTORYMGR_PTR->SetSwitchState(m_strHorFlipSwitchBtn.c_str(),((bOpen ==TRUE ) ? true:false) ,m_pWndTree);
	return S_OK;
}

HRESULT CMoonAdjustDlg::OnTrapezoidalCorInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bOpen = *(BOOL*)wparam;
	BOOL bSuccess = *( BOOL*)lparam;
	
	if ( bSuccess == FALSE )
	{
		bOpen = m_bTraCorOpen;
		WARNMESSAGE("梯形矫正设置失败!");
	}

	m_bTraCorOpen = bOpen;
	UIFACTORYMGR_PTR->SetSwitchState(m_strTraCorSwitchBtn.c_str(),((bOpen ==TRUE ) ? true:false) ,m_pWndTree);
	if ( m_bTraCorOpen == TRUE )
	{
		UIFACTORYMGR_PTR->LoadScheme(m_strSchemeEnable,m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme(m_strSchemeDisable,m_pWndTree);
	}
	return S_OK;
}

HRESULT CMoonAdjustDlg::OnCameraSelectInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		return S_FALSE;
	}
	
	//OnTralCorParamInd(wparam,lparam);
	
	return S_OK;
}

HRESULT CMoonAdjustDlg::OnTraCorValueInd( WPARAM wparam, LPARAM lparam )
{
    /*
	EmTPCorrect emMyOption = *(EmTPCorrect*)(wparam);
	
	TTPMoonCamInfo tMoonCameraCfg;
	MOONLIBDATAMGRPTR->GetCamCfg( tMoonCameraCfg );
	
	m_tHorParam.dwCorrectLevel = tMoonCameraCfg.dwHorizonCorrect;
	m_tHorParam.dwStretchRegion = tMoonCameraCfg.dwHorizonStretch;
	
	m_tVerParam.dwCorrectLevel = tMoonCameraCfg.dwVerticalCorrect;
	m_tVerParam.dwStretchRegion = tMoonCameraCfg.dwVerticalStretch;
	
	if (( emMyOption == em_HorizonCorrect) || ( emMyOption == em_HorizonStretch ))
	{
		SetTraCorrectionParam(emMyOption,m_tHorParam);
	}
	else
	{
		SetTraCorrectionParam(emMyOption,m_tVerParam);
	}
	*/
	return S_OK;
}

HRESULT CMoonAdjustDlg::OnSecBoundaryNty(WPARAM wparam, LPARAM lparam)
{
	TTPSecBoundaryInfo tTPSecBoundaryInfo = *(TTPSecBoundaryInfo*)(wparam);

	BOOL bDistortSwich = tTPSecBoundaryInfo.bDistortSwich;
	m_bTraCorOpen = bDistortSwich;
	
	UIFACTORYMGR_PTR->SetSwitchState(m_strTraCorSwitchBtn.c_str(),((bDistortSwich ==TRUE ) ? true:false) ,m_pWndTree);
	if ( m_bTraCorOpen == TRUE )
	{
		UIFACTORYMGR_PTR->LoadScheme(m_strSchemeEnable, m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme(m_strSchemeDisable, m_pWndTree);
	}

	BOOL bColorSwitch = tTPSecBoundaryInfo.bColorSwitch;
	UIFACTORYMGR_PTR->SetSwitchState(m_strRgbConsisSwitchBtn.c_str(),((bColorSwitch ==TRUE ) ? true:false) ,m_pWndTree);
	if( bColorSwitch )
	{
		UIFACTORYMGR_PTR->LoadScheme("EnableColorScheme", m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("DisableColorScheme", m_pWndTree);
	}

	TTPColorCoeff tTPColorCoeff1 = tTPSecBoundaryInfo.tColorCoeff[0];
	TTPColorCoeff tTPColorCoeff2 = tTPSecBoundaryInfo.tColorCoeff[1];
	TTPColorCoeff tTPColorCoeff3 = tTPSecBoundaryInfo.tColorCoeff[2];

	UpdateColorRGBVal(tTPColorCoeff1);
	UpdateColorRGBVal(tTPColorCoeff2);
	UpdateColorRGBVal(tTPColorCoeff3);

	return S_OK;
}

void CMoonAdjustDlg::UpdateColorRGBVal(TTPColorCoeff tTPColorCoeff)
{
	float fColorRGBValue[3];
	s8 chColorRedCoeff[10] = {0};
	s8 chColorGreenCoeff[10] = {0};
	s8 chColorBlueCoeff[10] = {0};
	
	fColorRGBValue[0] = tTPColorCoeff.dwRed*1.0/1000 - 1;
	fColorRGBValue[1] = tTPColorCoeff.dwGreen*1.0/1000 - 1;
	fColorRGBValue[2] = tTPColorCoeff.dwBlue*1.0/1000 - 1;
	
	sprintf(chColorRedCoeff, "%.3f", fColorRGBValue[0]);
	sprintf(chColorGreenCoeff, "%.3f", fColorRGBValue[1]);
	sprintf(chColorBlueCoeff, "%.3f", fColorRGBValue[2]);

	if( 0 == tTPColorCoeff.byIndex )
	{
		UIFACTORYMGR_PTR->SetCaption(m_strRLeftCorEdit, chColorRedCoeff, m_pWndTree);
		UIFACTORYMGR_PTR->SetCaption(m_strGLeftCorEdit, chColorGreenCoeff, m_pWndTree);
		UIFACTORYMGR_PTR->SetCaption(m_strBLeftCorEdit, chColorBlueCoeff, m_pWndTree);
	}
	else if( 1 == tTPColorCoeff.byIndex )
	{
		UIFACTORYMGR_PTR->SetCaption(m_strRMidCorEdit, chColorRedCoeff, m_pWndTree);
		UIFACTORYMGR_PTR->SetCaption(m_strGMidCorEdit, chColorGreenCoeff, m_pWndTree);
		UIFACTORYMGR_PTR->SetCaption(m_strBMidCorEdit, chColorBlueCoeff, m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption(m_strRRightCorEdit, chColorRedCoeff, m_pWndTree);
		UIFACTORYMGR_PTR->SetCaption(m_strGRightCorEdit, chColorGreenCoeff, m_pWndTree);
		UIFACTORYMGR_PTR->SetCaption(m_strBRightCorEdit, chColorBlueCoeff, m_pWndTree);
	}
}

HRESULT CMoonAdjustDlg::OnSetChangeSideRGBNty(WPARAM wparam, LPARAM lparam)
{
	EmTPColorConsistency emColorStyle = *(EmTPColorConsistency*)(wparam);
	u32* dwColorValue = (u32*)(lparam);

	float fColorRGBValue[2];
	s8 chLeftColorRGBValue[10] = {0};
	s8 chRightColorRGBValue[10] = {0};

    for(int i=0; i<2; i++)
	{
		fColorRGBValue[i] = dwColorValue[i]*1.0/1000 - 1;
	}

	sprintf(chLeftColorRGBValue, "%.3f", fColorRGBValue[0]);
	sprintf(chRightColorRGBValue, "%.3f", fColorRGBValue[1]);

	if( emColorRed == emColorStyle )
	{
		UIFACTORYMGR_PTR->SetCaption(m_strRLeftCorEdit, chLeftColorRGBValue, m_pWndTree);
		UIFACTORYMGR_PTR->SetCaption(m_strRRightCorEdit, chRightColorRGBValue, m_pWndTree);
	}
	else if( emColorGreen == emColorStyle )
	{
		UIFACTORYMGR_PTR->SetCaption(m_strGLeftCorEdit, chLeftColorRGBValue, m_pWndTree);
		UIFACTORYMGR_PTR->SetCaption(m_strGRightCorEdit, chRightColorRGBValue, m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption(m_strBLeftCorEdit, chLeftColorRGBValue, m_pWndTree);
		UIFACTORYMGR_PTR->SetCaption(m_strBRightCorEdit, chRightColorRGBValue, m_pWndTree);
	}

	return S_OK;
}

HRESULT CMoonAdjustDlg::OnSetDefaultParamNty(WPARAM wparam, LPARAM lparam)
{
	TTPSecBoundaryInfo tTPSecBoundaryInfo = *(TTPSecBoundaryInfo*)(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);
	
	BOOL bDistortSwich = tTPSecBoundaryInfo.bDistortSwich;
	m_bTraCorOpen = bDistortSwich;

	UIFACTORYMGR_PTR->SetSwitchState(m_strTraCorSwitchBtn.c_str(),((bDistortSwich ==TRUE ) ? true:false) ,m_pWndTree);
	if ( m_bTraCorOpen == TRUE )
	{
		UIFACTORYMGR_PTR->LoadScheme(m_strSchemeEnable, m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme(m_strSchemeDisable, m_pWndTree);
	}

	BOOL bColorSwitch = tTPSecBoundaryInfo.bColorSwitch;
	UIFACTORYMGR_PTR->SetSwitchState( m_strRgbConsisSwitchBtn.c_str(),((bColorSwitch ==TRUE ) ? true:false) ,m_pWndTree );
	if( bColorSwitch )
	{
		UIFACTORYMGR_PTR->LoadScheme( "EnableColorScheme", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "DisableColorScheme", m_pWndTree );
	}
	

	s8 chColorRGBCoeff[10] = {0}; 
	float fColorRGBValue = tTPSecBoundaryInfo.tColorCoeff[0].dwRed*1.0/1000 - 1;
	sprintf(chColorRGBCoeff, "%.3f", fColorRGBValue);
	UIFACTORYMGR_PTR->SetCaption(m_strRLeftCorEdit, chColorRGBCoeff, m_pWndTree);

	fColorRGBValue = tTPSecBoundaryInfo.tColorCoeff[0].dwGreen*1.0/1000 - 1;
	sprintf(chColorRGBCoeff, "%.3f", fColorRGBValue);
	UIFACTORYMGR_PTR->SetCaption(m_strGLeftCorEdit, chColorRGBCoeff, m_pWndTree);

	fColorRGBValue = tTPSecBoundaryInfo.tColorCoeff[0].dwBlue*1.0/1000 - 1;
	sprintf(chColorRGBCoeff, "%.3f", fColorRGBValue);
	UIFACTORYMGR_PTR->SetCaption(m_strBLeftCorEdit, chColorRGBCoeff, m_pWndTree);

	fColorRGBValue = tTPSecBoundaryInfo.tColorCoeff[1].dwRed*1.0/1000 - 1;
	sprintf(chColorRGBCoeff, "%.3f", fColorRGBValue);
	UIFACTORYMGR_PTR->SetCaption(m_strRMidCorEdit, chColorRGBCoeff, m_pWndTree);

	fColorRGBValue = tTPSecBoundaryInfo.tColorCoeff[1].dwGreen*1.0/1000 -1 ;
	sprintf(chColorRGBCoeff, "%.3f", fColorRGBValue);
	UIFACTORYMGR_PTR->SetCaption(m_strGMidCorEdit, chColorRGBCoeff, m_pWndTree);

	fColorRGBValue = tTPSecBoundaryInfo.tColorCoeff[1].dwBlue*1.0/1000 - 1;
	sprintf(chColorRGBCoeff, "%.3f", fColorRGBValue);
	UIFACTORYMGR_PTR->SetCaption(m_strBMidCorEdit, chColorRGBCoeff, m_pWndTree);

	fColorRGBValue = tTPSecBoundaryInfo.tColorCoeff[2].dwRed*1.0/1000 - 1;
	sprintf(chColorRGBCoeff, "%.3f", fColorRGBValue);
	UIFACTORYMGR_PTR->SetCaption(m_strRRightCorEdit, chColorRGBCoeff, m_pWndTree);

	fColorRGBValue = tTPSecBoundaryInfo.tColorCoeff[2].dwGreen*1.0/1000 - 1;
	sprintf(chColorRGBCoeff, "%.3f", fColorRGBValue);
	UIFACTORYMGR_PTR->SetCaption(m_strGRightCorEdit, chColorRGBCoeff, m_pWndTree);

	fColorRGBValue = tTPSecBoundaryInfo.tColorCoeff[2].dwBlue*1.0/1000 - 1;
	sprintf(chColorRGBCoeff, "%.3f", fColorRGBValue);
	UIFACTORYMGR_PTR->SetCaption(m_strBRightCorEdit, chColorRGBCoeff, m_pWndTree);

	return S_OK;
}

HRESULT CMoonAdjustDlg::OnSetColorRGBInd(WPARAM wparam, LPARAM lparam)
{
	TTPColorRGBCoeff tTPColorRGBCoeff = *reinterpret_cast<TTPColorRGBCoeff*>(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);
	
	if ( !bSuccess )
	{
		WARNMESSAGE("颜色一致性设置失败!");
		return S_FALSE;
	}

	u8 byIndex = tTPColorRGBCoeff.byIndex;
	u32 dwRGBColorVal = tTPColorRGBCoeff.dwValue;
	EmTPColorConsistency emColorStyle = tTPColorRGBCoeff.emColorType;

	s8 chColorRGBCoeff[10] = {0};
	float fColorRGBValue = dwRGBColorVal*1.0/1000 - 1;
	sprintf(chColorRGBCoeff, "%.3f", fColorRGBValue);

	if( 0 == byIndex)
	{
		if( emColorRed == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strRLeftCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else if( emColorGreen == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strGLeftCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else
		{
			UIFACTORYMGR_PTR->SetCaption(m_strBLeftCorEdit, chColorRGBCoeff, m_pWndTree);
		}
	}
	else if( 1 == byIndex)
	{
		if( emColorRed == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strRMidCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else if( emColorGreen == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strGMidCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else
		{
			UIFACTORYMGR_PTR->SetCaption(m_strBMidCorEdit, chColorRGBCoeff, m_pWndTree);
		}
	}
	else
	{
		if( emColorRed == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strRRightCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else if( emColorGreen == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strGRightCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else
		{
			UIFACTORYMGR_PTR->SetCaption(m_strBRightCorEdit, chColorRGBCoeff, m_pWndTree);
		}
	}

	return S_OK;
}

HRESULT CMoonAdjustDlg::OnSetDirectColorRGBInd(WPARAM wparam, LPARAM lparam)
{
	TTPColorRGBCoeff tTPColorRGBCoeff = *reinterpret_cast<TTPColorRGBCoeff*>(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);
	
	if ( !bSuccess )
	{
		WARNMESSAGE("颜色一致性设置失败!");
		return S_FALSE;
	}
	
	u8 byIndex = tTPColorRGBCoeff.byIndex;
	u32 dwRGBColorVal = tTPColorRGBCoeff.dwValue;
	EmTPColorConsistency emColorStyle = tTPColorRGBCoeff.emColorType;
	
	s8 chColorRGBCoeff[10] = {0};
	float fColorRGBValue = dwRGBColorVal*1.0/1000 - 1;
	sprintf(chColorRGBCoeff, "%.3f", fColorRGBValue);
	
	if( 0 == byIndex)
	{
		if( emColorRed == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strRLeftCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else if( emColorGreen == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strGLeftCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else
		{
			UIFACTORYMGR_PTR->SetCaption(m_strBLeftCorEdit, chColorRGBCoeff, m_pWndTree);
		}
	}
	else if( 1 == byIndex)
	{
		if( emColorRed == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strRMidCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else if( emColorGreen == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strGMidCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else
		{
			UIFACTORYMGR_PTR->SetCaption(m_strBMidCorEdit, chColorRGBCoeff, m_pWndTree);
		}
	}
	else
	{
		if( emColorRed == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strRRightCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else if( emColorGreen == emColorStyle )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strGRightCorEdit, chColorRGBCoeff, m_pWndTree);
		}
		else
		{
			UIFACTORYMGR_PTR->SetCaption(m_strBRightCorEdit, chColorRGBCoeff, m_pWndTree);
		}
	}

	return S_OK;
}

HRESULT CMoonAdjustDlg::OnSetAutoColConstancyInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bSuccess = *(BOOL*)(wparam);
	u32* dwRGBColorVal = (u32*)(lparam);
	float fRGBColorVal[MOON_COLOR_COEFF_NUM];
	s8 chRGBColorVal[10] = {0};

	for(int i=0; i<MOON_COLOR_COEFF_NUM; i++)
	{
		fRGBColorVal[i] = dwRGBColorVal[i]*1.0/1000 - 1;
		sprintf( chRGBColorVal, "%.3f", fRGBColorVal[i] );

		if( 0 == i )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strRLeftCorEdit, chRGBColorVal, m_pWndTree);
		}
		else if( 1 == i )
		{
			UIFACTORYMGR_PTR->SetCaption(m_strGLeftCorEdit, chRGBColorVal, m_pWndTree);
		}
		else if( 2 == i)
		{
			UIFACTORYMGR_PTR->SetCaption(m_strBLeftCorEdit, chRGBColorVal, m_pWndTree);
		}
		else if( 3 == i)
		{
			UIFACTORYMGR_PTR->SetCaption(m_strRMidCorEdit, chRGBColorVal, m_pWndTree);
		}
		else if( 4 == i)
		{
			UIFACTORYMGR_PTR->SetCaption(m_strGMidCorEdit, chRGBColorVal, m_pWndTree);
		}
		else if( 5 == i)
		{
			UIFACTORYMGR_PTR->SetCaption(m_strBMidCorEdit, chRGBColorVal, m_pWndTree);
		}
		else if( 6 == i)
		{
			UIFACTORYMGR_PTR->SetCaption(m_strRRightCorEdit, chRGBColorVal, m_pWndTree);
		}
		else if( 7 == i)
		{
			UIFACTORYMGR_PTR->SetCaption(m_strGRightCorEdit, chRGBColorVal, m_pWndTree);
		}
		else
		{
			UIFACTORYMGR_PTR->SetCaption(m_strBRightCorEdit, chRGBColorVal, m_pWndTree);
		}
	}

	return S_OK;
}

HRESULT CMoonAdjustDlg::OnSetCamDistortParamInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)(lparam);
	EmTPCorrect emMyOption = *(EmTPCorrect*)(wparam);

	if ( !bSuccess )
	{
		string strError= "";
		switch( emMyOption )
		{
		case em_HorizonCorrect:
			strError = "水平矫正";
			break;
		case em_HorizonStretch:
			strError = "水平拉伸";
			break;
		case em_VerticalCorrect:
			strError = "垂直矫正";
			break;
		case em_VerticalStretch:
			strError = "垂直拉伸";
			break;
		default:
			strError = "梯形矫正";
			break;
		}
		strError +="设置失败!";
		WARNMESSAGE(strError.c_str());
	}
	
	OnTraCorValueInd((WPARAM)&emMyOption,NULL);
	
	return S_OK;	
}

void CMoonAdjustDlg::CopyImage( string strCopyPath, string strSavePath )
{
	string strCopyFilePath;
	string strSaveFilePath;


	if ( m_bIsSaveAsSnapShot == FALSE )
	{
		strCopyFilePath = strCopyPath + "\\" + GetSnapShotFileName(MOONSNAPSHOT_FILE_NAME1);
		strSaveFilePath = strSavePath + "\\" + "save" + MOONSNAPSHOT_FILE_NAME1;
		CopyFile(strCopyFilePath,strSaveFilePath);

		strCopyFilePath = strCopyPath + "\\" + GetSnapShotFileName(MOONSNAPSHOT_FILE_NAME2);
		strSaveFilePath = strSavePath + "\\" + "save" + MOONSNAPSHOT_FILE_NAME2;
		CopyFile(strCopyFilePath,strSaveFilePath);

		strCopyFilePath = strCopyPath + "\\" + GetSnapShotFileName(MOONSNAPSHOT_FILE_NAME3);
		strSaveFilePath = strSavePath + "\\" + "save" + MOONSNAPSHOT_FILE_NAME3;
		CopyFile(strCopyFilePath,strSaveFilePath);
	}
	else
	{
		strCopyFilePath = strCopyPath + "\\" + "save" + MOONSNAPSHOT_FILE_NAME1;
		strSaveFilePath = strSavePath + "\\" + MOONSNAPSHOT_FILE_NAME1;
		CopyFile(strCopyFilePath,strSaveFilePath);
		
		strCopyFilePath = strCopyPath + "\\" + "save" + MOONSNAPSHOT_FILE_NAME2;
		strSaveFilePath = strSavePath + "\\" + MOONSNAPSHOT_FILE_NAME2;
		CopyFile(strCopyFilePath,strSaveFilePath);

		strCopyFilePath = strCopyPath + "\\" + "save" + MOONSNAPSHOT_FILE_NAME3;
		strSaveFilePath = strSavePath + "\\" + MOONSNAPSHOT_FILE_NAME3;
		CopyFile(strCopyFilePath,strSaveFilePath);
	}
}

void CMoonAdjustDlg::CopyFile( string strCopyFilePath, string strSaveFilePath )
{
	s8 chBuf[1024*4] = {NULL};
	FILE * fp = NULL;
	FILE * Savefp = NULL;
	
	if ( ( UIDATAMGR_PTR->IsFileExist(strCopyFilePath.c_str())) == FALSE )
	{
		return ;
	}

	fp = fopen( strCopyFilePath.c_str(),"rb");
	if ( fp == NULL )
	{
		WARNMESSAGE("打开文件失败");
		return ;
	}

	Savefp = fopen(strSaveFilePath.c_str(),"wb");
	if ( Savefp == NULL )
	{
		WARNMESSAGE("打开文件失败");
		return ;
	}
	
	while( fread( chBuf,sizeof(s8),sizeof(chBuf),fp) )
	{
		fwrite(chBuf,sizeof(chBuf),1,Savefp);
		
		memset(chBuf,0,sizeof(chBuf));
	}

	fclose(fp);
	fclose(Savefp);
}

void CMoonAdjustDlg::SetRGBColorValCmd( CString str, u8 nPosition, EmTPColorConsistency emMyColorOption )
{
	float fRgbValue = StringToFloatThree( str );
	u32 nRgbValue = 0;

	if( fRgbValue < 0 )
	{
		s32 nTemp = ( fabs(fRgbValue)+1.0e-6 ) * 1000;
		nRgbValue = 1000 - nTemp;
	}
	else
	{
		nRgbValue = (fRgbValue+1.0e-6) * 1000 + 1000 ;
	}

	if( nRgbValue < 500 )
	{
		nRgbValue = 500;
	}

	if( nRgbValue > 1500 )
	{
		nRgbValue = 1500;
	}

	u16 nRet = COMIFMGRPTR->SetColorRGBDirectCmd( nPosition, emMyColorOption, nRgbValue );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "RGB颜色一致性请求发送失败" );
	}
}

float CMoonAdjustDlg::StringToFloatThree(CString str)
{
	float f = 0;
	f = atof((LPCTSTR)str);
	char strRet[10] = {0};
	sprintf(strRet,"%.3f",f);
	f = atof(strRet);
	return f;
}

CString CMoonAdjustDlg::OnlyFloat(CString str)
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

HRESULT CMoonAdjustDlg::OnSetDelayCorrectInd( WPARAM wparam, LPARAM lparam )
{
	TTPFpgaDelay tTPDelayInfo = *reinterpret_cast<TTPFpgaDelay*>(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);
	
	if ( !bSuccess )
	{
		WARNMESSAGE("延时矫正设置失败!");
		return S_FALSE;
	}
	
	u8 byIndex = tTPDelayInfo.byIndex;
	u32 dwDelayVal = tTPDelayInfo.dwDelay;

	s8 chDelay[10] = {0};
	sprintf(chDelay, "%d", dwDelayVal);
	
	if( 0 == byIndex)
	{
		UIFACTORYMGR_PTR->SetCaption(m_strLeftDelayCorEdit, chDelay, m_pWndTree);
	}
	else if( 1 == byIndex)
	{
		UIFACTORYMGR_PTR->SetCaption(m_strMiddleDelayCorEdit, chDelay, m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption(m_strRightDelayCorEdit, chDelay, m_pWndTree);
	}
	
	return S_OK;
}

HRESULT CMoonAdjustDlg::OnSetDelayCorrectNty( WPARAM wparam, LPARAM lparam )
{
	TTPFpgaDelay tTPDelayInfo = *reinterpret_cast<TTPFpgaDelay*>(wparam);
	
	u8 byIndex = tTPDelayInfo.byIndex;
	u32 dwDelayVal = tTPDelayInfo.dwDelay;
	
	s8 chDelay[10] = {0};
	sprintf(chDelay, "%d", dwDelayVal);
	
	if( 0 == byIndex)
	{
		UIFACTORYMGR_PTR->SetCaption(m_strLeftDelayCorEdit, chDelay, m_pWndTree);
	}
	else if( 1 == byIndex)
	{
		UIFACTORYMGR_PTR->SetCaption(m_strMiddleDelayCorEdit, chDelay, m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption(m_strRightDelayCorEdit, chDelay, m_pWndTree);
	}
	
	return S_OK;
}

bool CMoonAdjustDlg::OnLeftDelayReduceBtnClick( const IArgs & arg )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftDelayCorEdit, str, m_pWndTree );
    s32 dwValue = atoi(str.c_str()) - 1;
    if (dwValue < 0)
    {
		return false;
    }
    
	u16 nRet = COMIFMGRPTR->SetDelayCorrectCmd(0, dwValue);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置延时矫正请求发送失败" );
	}
	
	return true;
}

bool CMoonAdjustDlg::OnLeftDelayCorEditChange( const IArgs & arg )
{
	return true;
}

bool CMoonAdjustDlg::OnLeftDelayCorEditKillFocus( const IArgs & arg )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftDelayCorEdit, str, m_pWndTree );
    s32 dwValue = atoi(str.c_str());

    if (dwValue > 5)
    {
		dwValue = 5;
    }
    
	u16 nRet = COMIFMGRPTR->SetDelayCorrectCmd(0, dwValue);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置延时矫正请求发送失败" );
	}
	
	return true;
}

bool CMoonAdjustDlg::OnLeftDelayIncreaseBtnClick( const IArgs & arg )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftDelayCorEdit, str, m_pWndTree );
    s32 dwValue = atoi(str.c_str()) + 1;
    if (dwValue > 5)
    {
		return false;
    }
    
	u16 nRet = COMIFMGRPTR->SetDelayCorrectCmd(0, dwValue);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置延时矫正请求发送失败" );
	}

	return true;
}

bool CMoonAdjustDlg::OnMiddleDelayReduceBtnClick( const IArgs & arg )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strMiddleDelayCorEdit, str, m_pWndTree );
    s32 dwValue = atoi(str.c_str()) - 1;
    if (dwValue < 0)
    {
		return false;
    }
    
	u16 nRet = COMIFMGRPTR->SetDelayCorrectCmd(1, dwValue);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置延时矫正请求发送失败" );
	}
	
	return true;
}

bool CMoonAdjustDlg::OnMiddleDelayCorEditChange( const IArgs & arg )
{
	return true;
}

bool CMoonAdjustDlg::OnMiddleDelayCorEditKillFocus( const IArgs & arg )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strMiddleDelayCorEdit, str, m_pWndTree );
    s32 dwValue = atoi(str.c_str());
	
    if (dwValue > 5)
    {
		dwValue = 5;
    }
    
	u16 nRet = COMIFMGRPTR->SetDelayCorrectCmd(1, dwValue);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置延时矫正请求发送失败" );
	}
	
	return true;
}

bool CMoonAdjustDlg::OnMiddleDelayIncreaseBtnClick( const IArgs & arg )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strMiddleDelayCorEdit, str, m_pWndTree );
    s32 dwValue = atoi(str.c_str()) + 1;
    if (dwValue > 5)
    {
		return false;
    }
    
	u16 nRet = COMIFMGRPTR->SetDelayCorrectCmd(1, dwValue);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置延时矫正请求发送失败" );
	}
	
	return true;
}

bool CMoonAdjustDlg::OnRightDelayReduceBtnClick( const IArgs & arg )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightDelayCorEdit, str, m_pWndTree );
    s32 dwValue = atoi(str.c_str()) - 1;
    if (dwValue < 0)
    {
		return false;
    }
    
	u16 nRet = COMIFMGRPTR->SetDelayCorrectCmd(2, dwValue);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置延时矫正请求发送失败" );
	}
	
	return true;
}

bool CMoonAdjustDlg::OnRightDelayCorEditChange( const IArgs & arg )
{
	return true;
}

bool CMoonAdjustDlg::OnRightDelayCorEditKillFocus( const IArgs & arg )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightDelayCorEdit, str, m_pWndTree );
    s32 dwValue = atoi(str.c_str());
	
    if (dwValue > 5)
    {
		dwValue = 5;
    }
    
	u16 nRet = COMIFMGRPTR->SetDelayCorrectCmd(2, dwValue);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置延时矫正请求发送失败" );
	}
	
	return true;
}

bool CMoonAdjustDlg::OnRightDelayIncreaseBtnClick( const IArgs & arg )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightDelayCorEdit, str, m_pWndTree );
    s32 dwValue = atoi(str.c_str()) + 1;
    if (dwValue > 5)
    {
		return false;
    }
    
	u16 nRet = COMIFMGRPTR->SetDelayCorrectCmd(2, dwValue);
	
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置延时矫正请求发送失败" );
	}
	
	return true;
}
