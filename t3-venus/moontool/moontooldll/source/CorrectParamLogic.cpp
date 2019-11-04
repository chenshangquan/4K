// CorrectParamLogic.cpp: implementation of the CCorrectParamLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CorrectParamLogic.h"
#include "cameractrlLogic.h"
#include <math.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCorrectParamLogic::CCorrectParamLogic()
:m_strRotateLeftEdit("LeftRectAreaDlg/BtnRotateLeftEdit")
,m_strRotateRightEdit("RightRectAreaDlg/BtnRotateRightEdit")
,m_strEdtLeftZoom("EdtLeftZoom")
,m_strStcLeftZoom("StcLeftZoom")
,m_strStcRightZoom("StcRightZoom")
,m_strEdtRightZoom("EdtRightZoom")
,m_strLeftOneEdit("BtnLeftOneEdit")
,m_strLeftTwoEdit("BtnLeftTwoEdit")
,m_strLeftThreeEdit("BtnLeftThreeEdit")
,m_strLeftFourEdit("BtnLeftFourEdit")
,m_strLeftFiveEdit("BtnLeftFiveEdit")
,m_strLeftSixEdit("BtnLeftSixEdit")
,m_strLeftSevenEdit("BtnLeftSevenEdit")
,m_strLeftEightEdit("BtnLeftEightEdit")
,m_strLeftNineEdit("BtnLeftNineEdit")
,m_strLeftTenEdit("BtnLeftTenEdit")
,m_strLeftElevenEdit("BtnLeftElevenEdit")
,m_strLeftTwelveEdit("BtnLeftTwelveEdit")
,m_strRightOneEdit("BtnRightOneEdit")
,m_strRightTwoEdit("BtnRightTwoEdit")
,m_strRightThreeEdit("BtnRightThreeEdit")
,m_strRightFourEdit("BtnRightFourEdit")
,m_strRightFiveEdit("BtnRightFiveEdit")
,m_strRightSixEdit("BtnRightSixEdit")
,m_strRightSevenEdit("BtnRightSevenEdit")
,m_strRightEightEdit("BtnRightEightEdit")
,m_strRightNineEdit("BtnRightNineEdit")
,m_strRightTenEdit("BtnRightTenEdit")
,m_strRightElevenEdit("BtnRightElevenEdit")
,m_strRightTwelveEdit("BtnRightTwelveEdit")
,m_strBtnUppage("BtnUppage")
,m_strBtnDownpage("BtnDownpage")
,m_strStcCamStyle1("StcCamStyle1")
,m_strStcCamStyle2("StcCamStyle2")
{	
	m_nbyIndex = 0;
	m_dwZoom1 = 0;
	m_dwZoom2 = 0;
	m_dwZoom3 = 0;
	m_dwZoomPos1 = 0;
	m_dwZoomPos2 = 0;
	m_dwZoomPos3 = 0;
	memset( &m_tTPAllDistortParam1, 0, sizeof(TTPAllDistortParam) );
	memset( &m_tTPAllDistortParam2, 0, sizeof(TTPAllDistortParam) );
	memset( &m_tTPAllDistortParam3, 0, sizeof(TTPAllDistortParam) );

	m_pWnd = NULL;
}

CCorrectParamLogic::~CCorrectParamLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CCorrectParamLogic::RegMsg()
{
	CCorrectParamLogic *pThis = CCorrectParamLogic::GetSingletonPtr();

	REG_MSG_HANDLER( UI_DISTORTZOOM_NTY, CCorrectParamLogic::OnSetDistortZoomValNty, pThis, CCorrectParamLogic );
	REG_MSG_HANDLER( UI_TpMechanismSelect_NTY, CCorrectParamLogic::OnTpMechanismSelectNty, pThis, CCorrectParamLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CamStyleSel_IND, CCorrectParamLogic::OnCameraStyleSelectInd, pThis, CCorrectParamLogic );
	REG_MSG_HANDLER( UI_SecBoundary_Nty, CCorrectParamLogic::OnSecBoundaryNty, pThis, CCorrectParamLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMSETZOON_STOP_IND, CCorrectParamLogic::OnSetCamZoomStopInd, pThis, CCorrectParamLogic );
	//REG_MSG_HANDLER( UI_MOONTOOL_CamParamSync_IND, CCorrectParamLogic::OnCamParamSyncInd, pThis, CCorrectParamLogic );
	REG_MSG_HANDLER( UI_CHANGEDISTORT_IND, CCorrectParamLogic::OnChangeDistortInd, pThis, CCorrectParamLogic );
	REG_MSG_HANDLER( UI_DIRECTSETDISTORT_IND, CCorrectParamLogic::OnDirectSetDistortInd, pThis, CCorrectParamLogic );
	REG_MSG_HANDLER( UI_MoonSecDefault_Nty, CCorrectParamLogic::OnSetDefaultParamNty, pThis, CCorrectParamLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMPARAMDEFAULT_IND, CCorrectParamLogic::OnSetDefaultZoomInd, pThis, CCorrectParamLogic );
}

void CCorrectParamLogic::UnRegMsg()
{
	
}

void CCorrectParamLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::InitWnd", CCorrectParamLogic::InitWnd, CORRECTPARAMLOGIC, CCorrectParamLogic);
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnBtnClose", CCorrectParamLogic::OnBtnClose, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRotateLeftReduceBtnClick", CCorrectParamLogic::OnRotateLeftReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRotateLeftEditChange", CCorrectParamLogic::OnRotateLeftEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRotateLeftEditKillFocus", CCorrectParamLogic::OnRotateLeftEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRotateLeftIncreaseBtnClick", CCorrectParamLogic::OnRotateLeftIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftOneReduceBtnClick", CCorrectParamLogic::OnLeftOneReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftOneEditChange", CCorrectParamLogic::OnLeftOneEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftOneEditKillFocus", CCorrectParamLogic::OnLeftOneEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftOneIncreaseBtnClick", CCorrectParamLogic::OnLeftOneIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTwoReduceBtnClick", CCorrectParamLogic::OnLeftTwoReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTwoEditChange", CCorrectParamLogic::OnLeftTwoEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTwoEditKillFocus", CCorrectParamLogic::OnLeftTwoEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTwoIncreaseBtnClick", CCorrectParamLogic::OnLeftTwoIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftThreeReduceBtnClick", CCorrectParamLogic::OnLeftThreeReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftThreeEditChange", CCorrectParamLogic::OnLeftThreeEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftThreeEditKillFocus", CCorrectParamLogic::OnLeftThreeEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftThreeIncreaseBtnClick", CCorrectParamLogic::OnLeftThreeIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftFourReduceBtnClick", CCorrectParamLogic::OnLeftFourReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftFourEditChange", CCorrectParamLogic::OnLeftFourEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftFourEditKillFocus", CCorrectParamLogic::OnLeftFourEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftFourIncreaseBtnClick", CCorrectParamLogic::OnLeftFourIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftFiveReduceBtnClick", CCorrectParamLogic::OnLeftFiveReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftFiveEditChange", CCorrectParamLogic::OnLeftFiveEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftFiveEditKillFocus", CCorrectParamLogic::OnLeftFiveEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftFiveIncreaseBtnClick", CCorrectParamLogic::OnLeftFiveIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftSixReduceBtnClick", CCorrectParamLogic::OnLeftSixReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftSixEditChange", CCorrectParamLogic::OnLeftSixEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftSixEditKillFocus", CCorrectParamLogic::OnLeftSixEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftSixIncreaseBtnClick", CCorrectParamLogic::OnLeftSixIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftSevenReduceBtnClick", CCorrectParamLogic::OnLeftSevenReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftSevenEditChange", CCorrectParamLogic::OnLeftSevenEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftSevenEditKillFocus", CCorrectParamLogic::OnLeftSevenEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftSevenIncreaseBtnClick", CCorrectParamLogic::OnLeftSevenIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftEightReduceBtnClick", CCorrectParamLogic::OnLeftEightReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftEightEditChange", CCorrectParamLogic::OnLeftEightEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftEightEditKillFocus", CCorrectParamLogic::OnLeftEightEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftEightIncreaseBtnClick", CCorrectParamLogic::OnLeftEightIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftNineReduceBtnClick", CCorrectParamLogic::OnLeftNineReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftNineEditChange", CCorrectParamLogic::OnLeftNineEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftNineEditKillFocus", CCorrectParamLogic::OnLeftNineEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftNineIncreaseBtnClick", CCorrectParamLogic::OnLeftNineIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTenReduceBtnClick", CCorrectParamLogic::OnLeftTenReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTenEditChange", CCorrectParamLogic::OnLeftTenEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTenEditKillFocus", CCorrectParamLogic::OnLeftTenEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTenIncreaseBtnClick", CCorrectParamLogic::OnLeftTenIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftElevenReduceBtnClick", CCorrectParamLogic::OnLeftElevenReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftElevenEditChange", CCorrectParamLogic::OnLeftElevenEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftElevenEditKillFocus", CCorrectParamLogic::OnLeftElevenEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftElevenIncreaseBtnClick", CCorrectParamLogic::OnLeftElevenIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTwelveReduceBtnClick", CCorrectParamLogic::OnLeftTwelveReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTwelveEditChange", CCorrectParamLogic::OnLeftTwelveEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTwelveEditKillFocus", CCorrectParamLogic::OnLeftTwelveEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLeftTwelveIncreaseBtnClick", CCorrectParamLogic::OnLeftTwelveIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLBtnDownZoomPlus", CCorrectParamLogic::OnLBtnDownZoomPlus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLBtnUpZoomPlus", CCorrectParamLogic::OnLBtnUpZoomPlus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLBtnDoubleDownZoomPlus", CCorrectParamLogic::OnLBtnDoubleDownZoomPlus, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLBtnDownZoomSub", CCorrectParamLogic::OnLBtnDownZoomSub, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLBtnUpZoomSub", CCorrectParamLogic::OnLBtnUpZoomSub, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnLBtnDoubleDownZoomSub", CCorrectParamLogic::OnLBtnDoubleDownZoomSub, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnEdtLeftZoomChange", CCorrectParamLogic::OnEdtLeftZoomChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnEdtLeftZoomKillFocus", CCorrectParamLogic::OnEdtLeftZoomKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRotateRightReduceBtnClick", CCorrectParamLogic::OnRotateRightReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRotateRightEditChange", CCorrectParamLogic::OnRotateRightEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRotateRightEditKillFocus", CCorrectParamLogic::OnRotateRightEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRotateRightIncreaseBtnClick", CCorrectParamLogic::OnRotateRightIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightOneReduceBtnClick", CCorrectParamLogic::OnRightOneReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightOneEditChange", CCorrectParamLogic::OnRightOneEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightOneEditKillFocus", CCorrectParamLogic::OnRightOneEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightOneIncreaseBtnClick", CCorrectParamLogic::OnRightOneIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTwoReduceBtnClick", CCorrectParamLogic::OnRightTwoReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTwoEditChange", CCorrectParamLogic::OnRightTwoEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTwoEditKillFocus", CCorrectParamLogic::OnRightTwoEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTwoIncreaseBtnClick", CCorrectParamLogic::OnRightTwoIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightThreeReduceBtnClick", CCorrectParamLogic::OnRightThreeReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightThreeEditChange", CCorrectParamLogic::OnRightThreeEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightThreeEditKillFocus", CCorrectParamLogic::OnRightThreeEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightThreeIncreaseBtnClick", CCorrectParamLogic::OnRightThreeIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightFourReduceBtnClick", CCorrectParamLogic::OnRightFourReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightFourEditChange", CCorrectParamLogic::OnRightFourEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightFourEditKillFocus", CCorrectParamLogic::OnRightFourEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightFourIncreaseBtnClick", CCorrectParamLogic::OnRightFourIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightFiveReduceBtnClick", CCorrectParamLogic::OnRightFiveReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightFiveEditChange", CCorrectParamLogic::OnRightFiveEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightFiveEditKillFocus", CCorrectParamLogic::OnRightFiveEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightFiveIncreaseBtnClick", CCorrectParamLogic::OnRightFiveIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightSixReduceBtnClick", CCorrectParamLogic::OnRightSixReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightSixEditChange", CCorrectParamLogic::OnRightSixEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightSixEditKillFocus", CCorrectParamLogic::OnRightSixEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightSixIncreaseBtnClick", CCorrectParamLogic::OnRightSixIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightSevenReduceBtnClick", CCorrectParamLogic::OnRightSevenReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightSevenEditChange", CCorrectParamLogic::OnRightSevenEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightSevenEditKillFocus", CCorrectParamLogic::OnRightSevenEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightSevenIncreaseBtnClick", CCorrectParamLogic::OnRightSevenIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightEightReduceBtnClick", CCorrectParamLogic::OnRightEightReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightEightEditChange", CCorrectParamLogic::OnRightEightEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightEightEditKillFocus", CCorrectParamLogic::OnRightEightEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightEightIncreaseBtnClick", CCorrectParamLogic::OnRightEightIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightNineReduceBtnClick", CCorrectParamLogic::OnRightNineReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightNineEditChange", CCorrectParamLogic::OnRightNineEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightNineEditKillFocus", CCorrectParamLogic::OnRightNineEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightNineIncreaseBtnClick", CCorrectParamLogic::OnRightNineIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTenReduceBtnClick", CCorrectParamLogic::OnRightTenReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTenEditChange", CCorrectParamLogic::OnRightTenEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTenEditKillFocus", CCorrectParamLogic::OnRightTenEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTenIncreaseBtnClick", CCorrectParamLogic::OnRightTenIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightElevenReduceBtnClick", CCorrectParamLogic::OnRightElevenReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightElevenEditChange", CCorrectParamLogic::OnRightElevenEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightElevenEditKillFocus", CCorrectParamLogic::OnRightElevenEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightElevenIncreaseBtnClick", CCorrectParamLogic::OnRightElevenIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTwelveReduceBtnClick", CCorrectParamLogic::OnRightTwelveReduceBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTwelveEditChange", CCorrectParamLogic::OnRightTwelveEditChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTwelveEditKillFocus", CCorrectParamLogic::OnRightTwelveEditKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRightTwelveIncreaseBtnClick", CCorrectParamLogic::OnRightTwelveIncreaseBtnClick, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRBtnDownZoomPlus", CCorrectParamLogic::OnRBtnDownZoomPlus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRBtnUpZoomPlus", CCorrectParamLogic::OnRBtnUpZoomPlus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRBtnDoubleDownZoomPlus", CCorrectParamLogic::OnRBtnDoubleDownZoomPlus, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRBtnDownZoomSub", CCorrectParamLogic::OnRBtnDownZoomSub, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRBtnUpZoomSub", CCorrectParamLogic::OnRBtnUpZoomSub, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnRBtnDoubleDownZoomSub", CCorrectParamLogic::OnRBtnDoubleDownZoomSub, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnEdtRightZoomChange", CCorrectParamLogic::OnEdtRightZoomChange, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnEdtRightZoomKillFocus", CCorrectParamLogic::OnEdtRightZoomKillFocus, CORRECTPARAMLOGIC, CCorrectParamLogic );

	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnBtnUppage", CCorrectParamLogic::OnBtnUppage, CORRECTPARAMLOGIC, CCorrectParamLogic );
	REG_GOBAL_MEMBER_FUNC( "CCorrectParamLogic::OnBtnDownpage", CCorrectParamLogic::OnBtnDownpage, CORRECTPARAMLOGIC, CCorrectParamLogic );
	
}

void CCorrectParamLogic::UnRegFunc()
{
	
}

bool CCorrectParamLogic::InitWnd(const IArgs & arg)
{
	CLogicBase::InitWnd( arg );
	
	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrCorrectParamDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}
	
	return true;
}

void CCorrectParamLogic::Clear()
{
	if ( NULL== m_pWndTree )
	{
		return;
	}

	memset( &m_tTPAllDistortParam1, 0, sizeof(TTPAllDistortParam) );
	memset( &m_tTPAllDistortParam2, 0, sizeof(TTPAllDistortParam) );
	memset( &m_tTPAllDistortParam3, 0, sizeof(TTPAllDistortParam) );
	
	m_dwZoom1 = 0;
	m_dwZoom2 = 0;
	m_dwZoom3 = 0;

	m_dwZoomPos1 = 0;
	m_dwZoomPos2 = 0;
	m_dwZoomPos3 = 0;

	UIFACTORYMGR_PTR->ShowWindow( g_stcStrCorrectParamDlg, false );
}

HRESULT CCorrectParamLogic::OnSecBoundaryNty(WPARAM wparam, LPARAM lparam)
{
	TTPSecBoundaryInfo tTPSecBoundaryInfo = *(TTPSecBoundaryInfo*)(wparam);
	
	m_tTPAllDistortParam1 = tTPSecBoundaryInfo.tAllDistortParam[0];
	m_tTPAllDistortParam2 = tTPSecBoundaryInfo.tAllDistortParam[1];
	m_tTPAllDistortParam3 = tTPSecBoundaryInfo.tAllDistortParam[2];

	SetLeftDistortValue(m_tTPAllDistortParam1);
	SetRightDistortValue(m_tTPAllDistortParam2);
	
	return S_OK;
}

HRESULT CCorrectParamLogic::OnSetCamZoomStopInd(WPARAM wparam, LPARAM lparam)
{
/*
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	TTPMoonCamInfo tTpMoonCamInfo = *(TTPMoonCamInfo*)(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);

	if( !bSuccess )
	{
		WARNMESSAGE( "zoom设置失败");
	}

	u32 dwZoom = tTpMoonCamInfo.dwZoom;
	u32 dwZoomPos = tTpMoonCamInfo.dwZoomPos;
	float fZoom;
	String strComboText = CAMERALOGICRPTR->GetCamMechnismStyle();

	if( strComboText == "Sony")
	{
		CString strCaption;
		fZoom = (float)dwZoom/100;
		strCaption.Format( "%.2f", fZoom );
		if( 0 == m_nbyIndex )
		{
			if( 0 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom1 = tTpMoonCamInfo.dwZoom;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
			}
			else if( 1 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom2 = tTpMoonCamInfo.dwZoom;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
			}
			else
			{
				m_dwZoomPos3 = tTpMoonCamInfo.dwZoomPos;
				m_dwZoom3 = tTpMoonCamInfo.dwZoom;
			}
		}
		else
		{
			if( 1 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom2 = tTpMoonCamInfo.dwZoom;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
			}
			else if( 2 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom3 = tTpMoonCamInfo.dwZoom;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
			}
			else
			{
				m_dwZoom1 = tTpMoonCamInfo.dwZoom;
			}
		}
	}
	else
	{
		CString strCaption;
		dwZoom = dwZoom - 199;
		strCaption.Format( "%d", dwZoom );
		CString strCaption1;
		float fZoomPos = dwZoomPos*1.0/100;
		strCaption1.Format( "%.2f", fZoomPos );

		if( 0 == m_nbyIndex )
		{
			if( 0 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom1 = tTpMoonCamInfo.dwZoom;
				m_dwZoomPos1 = tTpMoonCamInfo.dwZoomPos;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
				UIFACTORYMGR_PTR->SetCaption( m_strStcLeftZoom, (String)strCaption1, m_pWndTree );
			}
			else if( 1 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom2 = tTpMoonCamInfo.dwZoom;
				m_dwZoomPos2 = tTpMoonCamInfo.dwZoomPos;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
				UIFACTORYMGR_PTR->SetCaption( m_strStcRightZoom, (String)strCaption1, m_pWndTree );
			}
			else
			{
				m_dwZoomPos3 = tTpMoonCamInfo.dwZoomPos;
				m_dwZoom3 = tTpMoonCamInfo.dwZoom;
			}
		}
		else
		{
			if( 1 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom2 = tTpMoonCamInfo.dwZoom;
				m_dwZoomPos2 = tTpMoonCamInfo.dwZoomPos;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
				UIFACTORYMGR_PTR->SetCaption( m_strStcLeftZoom, (String)strCaption1, m_pWndTree );
			}
			else if( 2 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom3 = tTpMoonCamInfo.dwZoom;
				m_dwZoomPos3 = tTpMoonCamInfo.dwZoomPos;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
				UIFACTORYMGR_PTR->SetCaption( m_strStcRightZoom, (String)strCaption1, m_pWndTree );
			}
			else
			{
				m_dwZoom1 = tTpMoonCamInfo.dwZoom;
				m_dwZoomPos1 = tTpMoonCamInfo.dwZoomPos;
			}
		}
		
	}
*/
	return S_OK;
}

HRESULT CCorrectParamLogic::OnCamParamSyncInd(WPARAM wparam, LPARAM lparam)
{
	u8 byIndex = *(u8*)(wparam);

	if( 0 == byIndex)
	{
		int dwZoom = m_dwZoom1;
		m_dwZoom2 = m_dwZoom1;
		m_dwZoom3 = m_dwZoom1;
		m_dwZoomPos2 = m_dwZoomPos1;
		m_dwZoomPos3 = m_dwZoomPos1;
		if( m_nbyIndex == 0 )
		{
			SetDistortZoomVal( 1, m_dwZoom2, m_dwZoomPos2 );
		}
		else
		{
			SetDistortZoomVal( 1, m_dwZoom2, m_dwZoomPos2 );
			SetDistortZoomVal( 2, m_dwZoom3, m_dwZoomPos3 );
		}
	}
	else if( 1 == byIndex )
	{
		m_dwZoom1 = m_dwZoom2;
		m_dwZoom3 = m_dwZoom2;
		m_dwZoomPos1 = m_dwZoomPos2;
		m_dwZoomPos3 = m_dwZoomPos2;
		if( m_nbyIndex == 0 )
		{
			SetDistortZoomVal( 0, m_dwZoom1, m_dwZoomPos1 );
		}
		else
		{
			SetDistortZoomVal( 2, m_dwZoom3, m_dwZoomPos3 );
		}
	}
	else
	{
		m_dwZoom1 = m_dwZoom3;
		m_dwZoom2 = m_dwZoom3;
		m_dwZoomPos1 = m_dwZoomPos3;
		m_dwZoomPos2 = m_dwZoomPos3;
		if( m_nbyIndex == 0 )
		{
			SetDistortZoomVal( 0, m_dwZoom1, m_dwZoomPos1 );
			SetDistortZoomVal( 1, m_dwZoom2, m_dwZoomPos2 );
		}
		else
		{
			SetDistortZoomVal( 1, m_dwZoom2, m_dwZoomPos2 );
		}
	}

	return S_OK;
}

HRESULT CCorrectParamLogic::OnChangeDistortInd(WPARAM wparam, LPARAM lparam)
{
	TTPDistortInfo tTPDistortInfo = *(TTPDistortInfo*)(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);
	
	if( !bSuccess )
	{
		WARNMESSAGE("梯形矫正参数设置失败");
	}

	if( 0 == m_nbyIndex )
	{
		if( 0 == tTPDistortInfo.byIndex )
		{
			UpdateDistortIndVal( tTPDistortInfo, m_tTPAllDistortParam1 );
			SetLeftDistortValue( m_tTPAllDistortParam1 );			
		}
		else
		{
			UpdateDistortIndVal( tTPDistortInfo, m_tTPAllDistortParam2 );
			SetRightDistortValue( m_tTPAllDistortParam2 );
		}
	}
	else
	{
		if( 1 == tTPDistortInfo.byIndex )
		{
			UpdateDistortIndVal( tTPDistortInfo, m_tTPAllDistortParam2);
			SetLeftDistortValue( m_tTPAllDistortParam2 );
		}
		else
		{
			UpdateDistortIndVal( tTPDistortInfo, m_tTPAllDistortParam3);
			SetRightDistortValue( m_tTPAllDistortParam3 );
		}
	}
	
	return S_OK;
}

HRESULT CCorrectParamLogic::OnDirectSetDistortInd(WPARAM wparam, LPARAM lparam)
{
	TTPDistortInfo tTPDistortInfo = *(TTPDistortInfo*)(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);
	
	if( !bSuccess )
	{
		WARNMESSAGE("直接设置梯形矫正参数值失败");
	}

	if( 0 == m_nbyIndex )
	{
		if( 0 == tTPDistortInfo.byIndex )
		{
			UpdateDistortIndVal( tTPDistortInfo, m_tTPAllDistortParam1 );
			SetLeftDistortValue( m_tTPAllDistortParam1 );			
		}
		else
		{
			UpdateDistortIndVal( tTPDistortInfo, m_tTPAllDistortParam2 );
			SetRightDistortValue( m_tTPAllDistortParam2 );
		}
	}
	else
	{
		if( 1 == tTPDistortInfo.byIndex )
		{
			UpdateDistortIndVal( tTPDistortInfo, m_tTPAllDistortParam2 );
			SetLeftDistortValue( m_tTPAllDistortParam2 );
		}
		else
		{
			UpdateDistortIndVal( tTPDistortInfo, m_tTPAllDistortParam3 );
			SetRightDistortValue( m_tTPAllDistortParam3 );
		}
	}

	return S_OK;
}

void CCorrectParamLogic::UpdateDistortIndVal( TTPDistortInfo tTPDistortInfo, TTPAllDistortParam &tTPAllDistortParam )
{

	if( tTPDistortInfo.emDistortType == emUperLeftHorizon )
	{
		tTPAllDistortParam.dwUperLeftHorizon = tTPDistortInfo.dwValue;
	}
	else if( tTPDistortInfo.emDistortType == emUperLeftVertical )
	{
		tTPAllDistortParam.dwUperLeftVertical = tTPDistortInfo.dwValue;
	}
	else if( tTPDistortInfo.emDistortType == emUperRightHorizon )
	{
		tTPAllDistortParam.dwUperRightHorizon = tTPDistortInfo.dwValue;
	}
	else if( tTPDistortInfo.emDistortType == emUperRightVertical )
	{
		tTPAllDistortParam.dwUperRightVertical = tTPDistortInfo.dwValue;
	}
	else if( tTPDistortInfo.emDistortType == emLowerRightHorizon )
	{
		tTPAllDistortParam.dwLowerRightHorizon = tTPDistortInfo.dwValue;
	}
	else if( tTPDistortInfo.emDistortType == emLowerRightVertical )
	{
		tTPAllDistortParam.dwLowerRightVertical = tTPDistortInfo.dwValue;
	}
	else if( tTPDistortInfo.emDistortType == emLowerLeftHorizon )
	{
		tTPAllDistortParam.dwLowerLeftHorizon = tTPDistortInfo.dwValue;
	}
	else if( tTPDistortInfo.emDistortType == emLowerLeftVertical )
	{
		tTPAllDistortParam.dwLowerLeftVertical = tTPDistortInfo.dwValue;
	}
	else if( tTPDistortInfo.emDistortType == emLeftSide )
	{
		tTPAllDistortParam.dwLeftSide = tTPDistortInfo.dwValue;
	}
	else if( tTPDistortInfo.emDistortType == emRightSide )
	{
		tTPAllDistortParam.dwRightSide = tTPDistortInfo.dwValue;
	}
	else if( tTPDistortInfo.emDistortType == emTopSide )
	{
		tTPAllDistortParam.dwTopSide = tTPDistortInfo.dwValue;
	}
	else if( tTPDistortInfo.emDistortType == emBottomSide )
	{
		tTPAllDistortParam.dwBottomSide = tTPDistortInfo.dwValue;
	}
	else
	{
		tTPAllDistortParam.dwCenterRotate = tTPDistortInfo.dwValue;
	}
}

HRESULT CCorrectParamLogic::OnSetDefaultParamNty(WPARAM wparam, LPARAM lparam)
{
	TTPSecBoundaryInfo tTPSecBoundaryInfo = *(TTPSecBoundaryInfo*)(wparam);
//	BOOL bSuccess = *(BOOL*)(lparam);
	
	m_tTPAllDistortParam1.dwUperLeftHorizon = tTPSecBoundaryInfo.tAllDistortParam[0].dwUperLeftHorizon;
	m_tTPAllDistortParam1.dwUperLeftVertical = tTPSecBoundaryInfo.tAllDistortParam[0].dwUperLeftVertical;
	m_tTPAllDistortParam1.dwUperRightHorizon = tTPSecBoundaryInfo.tAllDistortParam[0].dwUperRightHorizon;
	m_tTPAllDistortParam1.dwUperRightVertical = tTPSecBoundaryInfo.tAllDistortParam[0].dwUperRightVertical;
	m_tTPAllDistortParam1.dwLowerRightHorizon = tTPSecBoundaryInfo.tAllDistortParam[0].dwLowerRightHorizon;
	m_tTPAllDistortParam1.dwLowerRightVertical = tTPSecBoundaryInfo.tAllDistortParam[0].dwLowerRightVertical;
	m_tTPAllDistortParam1.dwLowerLeftHorizon = tTPSecBoundaryInfo.tAllDistortParam[0].dwLowerLeftHorizon;
	m_tTPAllDistortParam1.dwLowerLeftVertical = tTPSecBoundaryInfo.tAllDistortParam[0].dwLowerLeftVertical;
	m_tTPAllDistortParam1.dwLeftSide = tTPSecBoundaryInfo.tAllDistortParam[0].dwLeftSide;
	m_tTPAllDistortParam1.dwRightSide = tTPSecBoundaryInfo.tAllDistortParam[0].dwRightSide;
	m_tTPAllDistortParam1.dwTopSide = tTPSecBoundaryInfo.tAllDistortParam[0].dwTopSide;
	m_tTPAllDistortParam1.dwBottomSide = tTPSecBoundaryInfo.tAllDistortParam[0].dwBottomSide;
	m_tTPAllDistortParam1.dwCenterRotate = tTPSecBoundaryInfo.tAllDistortParam[0].dwCenterRotate;

	m_tTPAllDistortParam2.dwUperLeftHorizon = tTPSecBoundaryInfo.tAllDistortParam[1].dwUperLeftHorizon;
	m_tTPAllDistortParam2.dwUperLeftVertical = tTPSecBoundaryInfo.tAllDistortParam[1].dwUperLeftVertical;
	m_tTPAllDistortParam2.dwUperRightHorizon = tTPSecBoundaryInfo.tAllDistortParam[1].dwUperRightHorizon;
	m_tTPAllDistortParam2.dwUperRightVertical = tTPSecBoundaryInfo.tAllDistortParam[1].dwUperRightVertical;
	m_tTPAllDistortParam2.dwLowerRightHorizon = tTPSecBoundaryInfo.tAllDistortParam[1].dwLowerRightHorizon;
	m_tTPAllDistortParam2.dwLowerRightVertical = tTPSecBoundaryInfo.tAllDistortParam[1].dwLowerRightVertical;
	m_tTPAllDistortParam2.dwLowerLeftHorizon = tTPSecBoundaryInfo.tAllDistortParam[1].dwLowerLeftHorizon;
	m_tTPAllDistortParam2.dwLowerLeftVertical = tTPSecBoundaryInfo.tAllDistortParam[1].dwLowerLeftVertical;
	m_tTPAllDistortParam2.dwLeftSide = tTPSecBoundaryInfo.tAllDistortParam[1].dwLeftSide;
	m_tTPAllDistortParam2.dwRightSide = tTPSecBoundaryInfo.tAllDistortParam[1].dwRightSide;
	m_tTPAllDistortParam2.dwTopSide = tTPSecBoundaryInfo.tAllDistortParam[1].dwTopSide;
	m_tTPAllDistortParam2.dwBottomSide = tTPSecBoundaryInfo.tAllDistortParam[1].dwBottomSide;
	m_tTPAllDistortParam2.dwCenterRotate = tTPSecBoundaryInfo.tAllDistortParam[1].dwCenterRotate;

	m_tTPAllDistortParam3.dwUperLeftHorizon = tTPSecBoundaryInfo.tAllDistortParam[2].dwUperLeftHorizon;
	m_tTPAllDistortParam3.dwUperLeftVertical = tTPSecBoundaryInfo.tAllDistortParam[2].dwUperLeftVertical;
	m_tTPAllDistortParam3.dwUperRightHorizon = tTPSecBoundaryInfo.tAllDistortParam[2].dwUperRightHorizon;
	m_tTPAllDistortParam3.dwUperRightVertical = tTPSecBoundaryInfo.tAllDistortParam[2].dwUperRightVertical;
	m_tTPAllDistortParam3.dwLowerRightHorizon = tTPSecBoundaryInfo.tAllDistortParam[2].dwLowerRightHorizon;
	m_tTPAllDistortParam3.dwLowerRightVertical = tTPSecBoundaryInfo.tAllDistortParam[2].dwLowerRightVertical;
	m_tTPAllDistortParam3.dwLowerLeftHorizon = tTPSecBoundaryInfo.tAllDistortParam[2].dwLowerLeftHorizon;
	m_tTPAllDistortParam3.dwLowerLeftVertical = tTPSecBoundaryInfo.tAllDistortParam[2].dwLowerLeftVertical;
	m_tTPAllDistortParam3.dwLeftSide = tTPSecBoundaryInfo.tAllDistortParam[2].dwLeftSide;
	m_tTPAllDistortParam3.dwRightSide = tTPSecBoundaryInfo.tAllDistortParam[2].dwRightSide;
	m_tTPAllDistortParam3.dwTopSide = tTPSecBoundaryInfo.tAllDistortParam[2].dwTopSide;
	m_tTPAllDistortParam3.dwBottomSide = tTPSecBoundaryInfo.tAllDistortParam[2].dwBottomSide;
	m_tTPAllDistortParam3.dwCenterRotate = tTPSecBoundaryInfo.tAllDistortParam[2].dwCenterRotate;

	if( 0 == m_nbyIndex )
	{
		SetLeftDistortValue(m_tTPAllDistortParam1);
		SetRightDistortValue(m_tTPAllDistortParam2);
	}
	else
	{
		SetLeftDistortValue(m_tTPAllDistortParam2);
		SetRightDistortValue(m_tTPAllDistortParam3);
	}

	return S_OK;
}

HRESULT CCorrectParamLogic::OnSetDistortZoomValNty(WPARAM wparam, LPARAM lparam)
{
    /*
	TTPMoonCamInfo tTPMoonCamInfo = *(TTPMoonCamInfo*)(wparam);

	if( 0 == tTPMoonCamInfo.byIndex )
	{
		m_dwZoom1 = tTPMoonCamInfo.dwZoom;
		m_dwZoomPos1 = tTPMoonCamInfo.dwZoomPos;
	}
	else if( 1 == tTPMoonCamInfo.byIndex )
	{
        m_dwZoom2 = tTPMoonCamInfo.dwZoom;
		m_dwZoomPos2 = tTPMoonCamInfo.dwZoomPos;
	}
	else
	{
        m_dwZoom3 = tTPMoonCamInfo.dwZoom;
		m_dwZoomPos3 = tTPMoonCamInfo.dwZoomPos;
	}

	UpdateDistortParam( m_nbyIndex );

	SetDistortZoomVal( tTPMoonCamInfo.byIndex, tTPMoonCamInfo.dwZoom, tTPMoonCamInfo.dwZoomPos );
*/	
	return S_OK;
}

HRESULT CCorrectParamLogic::OnTpMechanismSelectNty(WPARAM wparam, LPARAM lparam)
{
	EmTPMechanism emTPMechanism = static_cast<EmTPMechanism>(lparam);
	
	Window *pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtLeftZoom, m_pWndTree );
	Window *pWnd1 = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtRightZoom, m_pWndTree );

	if( emTPMechanism == emSony )
	{
		m_emTPMechanism = emSony;
		UIFACTORYMGR_PTR->ShowWindow( m_strStcLeftZoom, false, m_pWndTree );
		UIFACTORYMGR_PTR->ShowWindow( m_strStcRightZoom, false, m_pWndTree );
		pWnd->ModifyStyle(ES_NUMBER, WS_CHILD|WS_CLIPSIBLINGS|ES_MULTILINE);
		pWnd1->ModifyStyle(ES_NUMBER, WS_CHILD|WS_CLIPSIBLINGS|ES_MULTILINE);
	}
	else
	{
		m_emTPMechanism = emH650;
		UIFACTORYMGR_PTR->ShowWindow( m_strStcLeftZoom, true, m_pWndTree );
		UIFACTORYMGR_PTR->ShowWindow( m_strStcRightZoom, true, m_pWndTree );
		pWnd->ModifyStyle(0, WS_CHILD|WS_CLIPSIBLINGS|ES_NUMBER );
		pWnd1->ModifyStyle(0, WS_CHILD|WS_CLIPSIBLINGS|ES_NUMBER );
	}

	return S_OK;
}

HRESULT CCorrectParamLogic::OnCameraStyleSelectInd(WPARAM wparam, LPARAM lparam)
{
	EmTPMechanism emTPMechanism = *(EmTPMechanism*)(wparam);
	Window *pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtLeftZoom, m_pWndTree );
	Window *pWnd1 = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtRightZoom, m_pWndTree );

	if( emTPMechanism == emSony )
	{
		m_emTPMechanism = emSony;
		UIFACTORYMGR_PTR->ShowWindow( m_strStcLeftZoom, false, m_pWndTree );
		UIFACTORYMGR_PTR->ShowWindow( m_strStcRightZoom, false, m_pWndTree );
		pWnd->ModifyStyle(ES_NUMBER, WS_CHILD|WS_CLIPSIBLINGS|ES_MULTILINE);
		pWnd1->ModifyStyle(ES_NUMBER, WS_CHILD|WS_CLIPSIBLINGS|ES_MULTILINE);
	}
	else
	{
		m_emTPMechanism = emH650;
		UIFACTORYMGR_PTR->ShowWindow( m_strStcLeftZoom, true, m_pWndTree );
		UIFACTORYMGR_PTR->ShowWindow( m_strStcRightZoom, true, m_pWndTree );
		pWnd->ModifyStyle(0, WS_CHILD|WS_CLIPSIBLINGS|ES_NUMBER );
		pWnd1->ModifyStyle(0, WS_CHILD|WS_CLIPSIBLINGS|ES_NUMBER );
	}
	
	return S_OK;
}

HRESULT CCorrectParamLogic::OnSetDefaultZoomInd(WPARAM wparam, LPARAM lparam)
{
    /*
	TTPMoonCamInfo tTpMoonCamInfo = *(TTPMoonCamInfo*)(wparam);

	u32 dwZoom = tTpMoonCamInfo.dwZoom;
	u32 dwZoomPos = tTpMoonCamInfo.dwZoomPos;
	float fZoom;
	String strComboText = CAMERALOGICRPTR->GetCamMechnismStyle();
	
	if( strComboText == "Sony")
	{
		CString strCaption;
		fZoom = (float)dwZoom/100;
		strCaption.Format( "%.2f", fZoom );
		
		if( 0 == m_nbyIndex )
		{
			if( 0 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom1 = tTpMoonCamInfo.dwZoom;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
			}
			else if( 1 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom2 = tTpMoonCamInfo.dwZoom;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
			}
			else
			{
				m_dwZoom3 = tTpMoonCamInfo.dwZoom;
			}
		}
		else
		{
			if( 1 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom2 = tTpMoonCamInfo.dwZoom;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
			}
			else if( 2 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom3 = tTpMoonCamInfo.dwZoom;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
			}
			else
			{
				m_dwZoom1 = tTpMoonCamInfo.dwZoom;
			}
		}
	}
	else
	{
		CString strCaption;
		dwZoom = dwZoom - 199;
		strCaption.Format( "%d", dwZoom );
		CString strCaption1;
		float fZoomPos = dwZoomPos*1.0/100;
		strCaption1.Format( "%.2f", fZoomPos );
		
		if( 0 == m_nbyIndex )
		{
			if( 0 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom1 = tTpMoonCamInfo.dwZoom;
				m_dwZoomPos1 = tTpMoonCamInfo.dwZoomPos;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
				UIFACTORYMGR_PTR->SetCaption( m_strStcLeftZoom, (String)strCaption1, m_pWndTree );
			}
			else if( 1 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom2 = tTpMoonCamInfo.dwZoom;
				m_dwZoomPos2 = tTpMoonCamInfo.dwZoomPos;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
				UIFACTORYMGR_PTR->SetCaption( m_strStcRightZoom, (String)strCaption1, m_pWndTree );
			}
			else
			{
				m_dwZoomPos3 = tTpMoonCamInfo.dwZoomPos;
				m_dwZoom3 = tTpMoonCamInfo.dwZoom;
			}
		}
		else
		{
			if( 1 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom2 = tTpMoonCamInfo.dwZoom;
				m_dwZoomPos2 = tTpMoonCamInfo.dwZoomPos;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
				UIFACTORYMGR_PTR->SetCaption( m_strStcLeftZoom, (String)strCaption1, m_pWndTree );
			}
			else if( 2 == tTpMoonCamInfo.byIndex )
			{
				m_dwZoom3 = tTpMoonCamInfo.dwZoom;
				m_dwZoomPos3 = tTpMoonCamInfo.dwZoomPos;
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
				UIFACTORYMGR_PTR->SetCaption( m_strStcRightZoom, (String)strCaption1, m_pWndTree );
			}
			else
			{
				m_dwZoom1 = tTpMoonCamInfo.dwZoom;
				m_dwZoomPos1 = tTpMoonCamInfo.dwZoomPos;
			}
		}	
	}	
	*/
	return S_OK;
}

bool CCorrectParamLogic::OnBtnClose(const IArgs & arg)
{
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrCorrectParamDlg, false );
	
	return true;
}

bool CCorrectParamLogic::OnRotateLeftReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emCenterRotate;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRotateLeftEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRotateLeftEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRotateLeftEdit, str, m_pWndTree );
	float fRotateValue  =  StringToFloatTwo( str.c_str() );
	s32 nRotateValue = 0;
	
	if( fRotateValue < 0 )
	{
		s32 nTemp = (fabs(fRotateValue)+1.0e-6)*100;
		nRotateValue = 150 - nTemp;
	}
	else
	{
		nRotateValue = (fRotateValue+1.0e-6)*100 + 150;
	}

	if( nRotateValue < 0 )
	{
		nRotateValue = 0;
	}
	if( nRotateValue > 300 )
	{
		nRotateValue = 300;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = (u32)nRotateValue;
	tTpDistortInfo.emDistortType = emCenterRotate;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRotateLeftIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emCenterRotate;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftOneReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperLeftHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftOneEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);

	return true;
}

bool CCorrectParamLogic::OnLeftOneEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftOneEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );

	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}

	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emUperLeftHorizon;

	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftOneIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperLeftHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftTwoReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLeftSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftTwoEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnLeftTwoEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftTwoEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emLeftSide;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftTwoIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLeftSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftThreeReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerLeftHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}
bool CCorrectParamLogic::OnLeftThreeEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnLeftThreeEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftThreeEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emLowerLeftHorizon;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftThreeIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerLeftHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftFourReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperLeftVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftFourEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnLeftFourEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftFourEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emUperLeftVertical;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftFourIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperLeftVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftFiveReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emTopSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftFiveEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnLeftFiveEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftFiveEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emTopSide;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftFiveIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emTopSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftSixReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperRightVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftSixEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnLeftSixEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftSixEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emUperRightVertical;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftSixIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperRightVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftSevenReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperRightHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftSevenEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnLeftSevenEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftSevenEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emUperRightHorizon;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftSevenIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperRightHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftEightReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emRightSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftEightEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnLeftEightEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftEightEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emRightSide;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftEightIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emRightSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftNineReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerRightHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftNineEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnLeftNineEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftNineEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emLowerRightHorizon;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftNineIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerRightHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftTenReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerLeftVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftTenEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnLeftTenEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftTenEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emLowerLeftVertical;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftTenIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition =emLowerLeftVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftElevenReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emBottomSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftElevenEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnLeftElevenEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftElevenEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emBottomSide;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftElevenIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emBottomSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftTwelveReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerRightVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftTwelveEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnLeftTwelveEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strLeftTwelveEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emLowerRightVertical;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 0;
	}
	else
	{
		tTpDistortInfo.byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLeftTwelveIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerRightVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLBtnDownZoomPlus(const IArgs & arg)
{
	EmTPZOOM emZoom = emEnlarge;
	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, byIndex);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLBtnUpZoomPlus(const IArgs & arg)
{
	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}

	u16 nRet = COMIFMGRPTR->SetCamZoomStopCmd(byIndex);

	return true;
}

bool CCorrectParamLogic::OnLBtnDoubleDownZoomPlus(const IArgs & arg)
{
	EmTPZOOM emZoom = emEnlarge;

	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, byIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLBtnDownZoomSub(const IArgs & arg)
{
	EmTPZOOM emZoom = emReduce;

	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, byIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnLBtnUpZoomSub(const IArgs & arg)
{
	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}

	u16 nRet = COMIFMGRPTR->SetCamZoomStopCmd( byIndex );

	return true;
}

bool CCorrectParamLogic::OnLBtnDoubleDownZoomSub(const IArgs & arg)
{
	EmTPZOOM emZoom = emReduce;

	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}

	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, byIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnEdtLeftZoomChange(const IArgs & arg)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
  	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &arg ));
   
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}

	Value_WindowCaption valueWindowCaption;
	UIFACTORYMGR_PTR->GetPropertyValue( valueWindowCaption, m_strEdtLeftZoom, m_pWndTree );
	
	CString str;
	str = OnlyFloat( valueWindowCaption.strCaption.c_str() );

	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}

	if ( nChar == 0x0d )
	{
		SetZoomCmd( str, byIndex );


		SetFocus(NULL);
	}

	return true;
}

bool CCorrectParamLogic::OnEdtLeftZoomKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtLeftZoom, str, m_pWndTree );

	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 0;
	}
	else
	{
		byIndex = 1;
	}
	
	SetZoomCmd(str.c_str(), byIndex );
	return true;
}

bool CCorrectParamLogic::OnRotateRightReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emCenterRotate;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRotateRightEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRotateRightEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRotateRightEdit, str, m_pWndTree );
	float fRotateValue  =  StringToFloatTwo( str.c_str() );
	s32 nRotateValue = 0;
	
	if( fRotateValue < 0 )
	{
		s32 nTemp = (fabs(fRotateValue)+1.0e-6)*100;
		nRotateValue = 150 - nTemp;
	}
	else
	{
		nRotateValue = (fRotateValue+1.0e-6)*100 + 150;
	}
	
	if( nRotateValue < 0 )
	{
		nRotateValue = 0;
	}
	if( nRotateValue > 300 )
	{
		nRotateValue = 300;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = (u32)nRotateValue;
	tTpDistortInfo.emDistortType = emCenterRotate;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRotateRightIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emCenterRotate;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightOneReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperLeftHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightOneEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightOneEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightOneEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emUperLeftHorizon;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightOneIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperLeftHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightTwoReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLeftSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightTwoEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightTwoEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightTwoEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emLeftSide;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightTwoIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLeftSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightThreeReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerLeftHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightThreeEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightThreeEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightThreeEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emLowerLeftHorizon;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightThreeIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerLeftHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightFourReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperLeftVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightFourEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightFourEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightFourEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emUperLeftVertical;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightFourIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperLeftVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightFiveReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emTopSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightFiveEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightFiveEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightFiveEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emTopSide;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightFiveIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emTopSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightSixReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperRightVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightSixEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightSixEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightSixEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emUperRightVertical;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightSixIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperRightVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightSevenReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperRightHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightSevenEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightSevenEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightSevenEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emUperRightHorizon;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightSevenIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emUperRightHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightEightReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emRightSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightEightEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightEightEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightEightEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emRightSide;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightEightIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emRightSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightNineReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerRightHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightNineEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightNineEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightNineEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emLowerRightHorizon;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightNineIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerRightHorizon;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightTenReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerLeftVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightTenEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightTenEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightTenEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emLowerLeftVertical;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightTenIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerLeftVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightElevenReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emBottomSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightElevenEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightElevenEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightElevenEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emBottomSide;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightElevenIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emBottomSide;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightTwelveReduceBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectReduce;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerRightVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightTwelveEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CCorrectParamLogic::OnRightTwelveEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRightTwelveEdit, str, m_pWndTree );
	u32 nEditvalue = atoi( str.c_str() );
	
	if( nEditvalue > 200 )
	{
		nEditvalue = 200;
	}
	
	TTPDistortInfo tTpDistortInfo;
	tTpDistortInfo.dwValue = nEditvalue;
	tTpDistortInfo.emDistortType = emLowerRightVertical;
	
	if( 0 == m_nbyIndex )
	{
		tTpDistortInfo.byIndex = 1;
	}
	else
	{
		tTpDistortInfo.byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetDirectDistortCmd( tTpDistortInfo );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRightTwelveIncreaseBtnClick(const IArgs & arg)
{
	EmTPCorrectChange emTPCorrectChange = emCorrectEnlarge;
	u8 byIndex = 0;
	EmTPDistortPosition emTPDistortPosition = emLowerRightVertical;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetChangeDistortCmd( byIndex, emTPCorrectChange, emTPDistortPosition );
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置梯形矫正参数请求发送失败" );
	}

	return true;
}

bool CCorrectParamLogic::OnRBtnDownZoomPlus(const IArgs & arg)
{
	EmTPZOOM emZoom = emEnlarge;
	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, byIndex);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	
	return true;
}

bool CCorrectParamLogic::OnRBtnUpZoomPlus(const IArgs & arg)
{
	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}

	u16 nRet = COMIFMGRPTR->SetCamZoomStopCmd(byIndex);
	
	return true;
}

bool CCorrectParamLogic::OnRBtnDoubleDownZoomPlus(const IArgs & arg)
{
	EmTPZOOM emZoom = emEnlarge;
	
	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, byIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	
	return true;
}

bool CCorrectParamLogic::OnRBtnDownZoomSub(const IArgs & arg)
{
	EmTPZOOM emZoom = emReduce;
	
	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, byIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	
	return true;
}

bool CCorrectParamLogic::OnRBtnUpZoomSub(const IArgs & arg)
{
	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetCamZoomStopCmd( byIndex );
	
	return true;
}

bool CCorrectParamLogic::OnRBtnDoubleDownZoomSub(const IArgs & arg)
{
	EmTPZOOM emZoom = emReduce;
	
	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, byIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	
	return true;
}

bool CCorrectParamLogic::OnEdtRightZoomChange(const IArgs & arg)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &arg ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	Value_WindowCaption valueWindowCaption;
	UIFACTORYMGR_PTR->GetPropertyValue( valueWindowCaption, m_strEdtRightZoom, m_pWndTree );
	
	CString str;
	str = OnlyFloat( valueWindowCaption.strCaption.c_str() );
	
	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	if ( nChar == 0x0d )
	{
		SetZoomCmd( str, byIndex );	
		
		SetFocus(NULL);
	}
	
	return true;
}

bool CCorrectParamLogic::OnEdtRightZoomKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtRightZoom, str, m_pWndTree );

	u8 byIndex = 0;
	if( 0 == m_nbyIndex )
	{
		byIndex = 1;
	}
	else
	{
		byIndex = 2;
	}
	
	SetZoomCmd( str.c_str(), byIndex );
	return true;
}

bool CCorrectParamLogic::OnBtnUppage(const IArgs & arg)
{
	int nUpPage = 0;
	m_nbyIndex = 0;
	UpdateDistortParam( nUpPage );

	UIFACTORYMGR_PTR->EnableWindow(m_strBtnUppage, false, m_pWndTree);
	UIFACTORYMGR_PTR->EnableWindow(m_strBtnDownpage, true, m_pWndTree);

	UIFACTORYMGR_PTR->SetCaption( m_strStcCamStyle1, "摄像机1", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strStcCamStyle2, "摄像机2", m_pWndTree );

	return true;
}

bool CCorrectParamLogic::OnBtnDownpage(const IArgs & arg)
{
    int nDownPage = 1;
	m_nbyIndex = 1;
	UpdateDistortParam( nDownPage );

	UIFACTORYMGR_PTR->EnableWindow(m_strBtnUppage, true, m_pWndTree);
	UIFACTORYMGR_PTR->EnableWindow(m_strBtnDownpage, false, m_pWndTree);

	UIFACTORYMGR_PTR->SetCaption( m_strStcCamStyle1, "摄像机2", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strStcCamStyle2, "摄像机3", m_pWndTree );

	return true;
}

void CCorrectParamLogic::SetH650ZoomValue(u32 dwZoom, u32 dwZoomPos)
{
	CString strCaption;
	dwZoom = dwZoom - 199;
	strCaption.Format( "%d", dwZoom );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
	
	CString strCaption1;
	float fZoomPos = dwZoomPos*1.0/100;
	strCaption1.Format( "%.2f", fZoomPos );
	UIFACTORYMGR_PTR->SetCaption( m_strStcLeftZoom, (String)strCaption1, m_pWndTree );
}

void CCorrectParamLogic::UpdateDistortParam(int nPage)
{
	if( nPage == 0 )
	{
		SetDistortZoomVal( 0, m_dwZoom1, m_dwZoomPos1);
		SetDistortZoomVal( 1, m_dwZoom2, m_dwZoomPos2);
		SetLeftDistortValue(m_tTPAllDistortParam1);
		SetRightDistortValue(m_tTPAllDistortParam2);
	}
	else
	{
		SetDistortZoomVal( 1, m_dwZoom2, m_dwZoomPos2);
		SetDistortZoomVal( 2, m_dwZoom3, m_dwZoomPos3);
		SetLeftDistortValue(m_tTPAllDistortParam2);
		SetRightDistortValue(m_tTPAllDistortParam3);
	}
}

void CCorrectParamLogic::UpdateEditNum(const IArgs & arg)
{
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &arg ));
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

void CCorrectParamLogic::SetLeftDistortValue( TTPAllDistortParam tTPAllDistortParam )
{
	s8 chUperLeftHorizon[10] = {0};
	s8 chUperLeftVertical[10] = {0};
	s8 chUperRightHorizon[10] = {0};
	s8 chUperRightVertical[10] = {0};
	s8 chLowerRightHorizon[10] = {0};
	s8 chLowerRightVertical[10] = {0};
	s8 chLowerLeftHorizon[10] = {0};
	s8 chLowerLeftVertical[10] = {0};
	s8 chLeftSide[10] = {0};
	s8 chRightSide[10] = {0};
	s8 chTopSide[10] = {0};
	s8 chBottomSide[10] = {0};
	s8 chCenterRotate[10] = {0};
	float fCenterRotate;

	sprintf( chUperLeftHorizon,"%d", tTPAllDistortParam.dwUperLeftHorizon );
	sprintf( chUperLeftVertical,"%d", tTPAllDistortParam.dwUperLeftVertical );
	sprintf( chUperRightHorizon,"%d", tTPAllDistortParam.dwUperRightHorizon );
	sprintf( chUperRightVertical,"%d", tTPAllDistortParam.dwUperRightVertical );
	sprintf( chLowerRightHorizon,"%d", tTPAllDistortParam.dwLowerRightHorizon );
	sprintf( chLowerRightVertical,"%d", tTPAllDistortParam.dwLowerRightVertical );
	sprintf( chLowerLeftHorizon,"%d", tTPAllDistortParam.dwLowerLeftHorizon );
	sprintf( chLowerLeftVertical,"%d", tTPAllDistortParam.dwLowerLeftVertical );
	sprintf( chLeftSide,"%d", tTPAllDistortParam.dwLeftSide );
	sprintf( chRightSide,"%d", tTPAllDistortParam.dwRightSide );
	sprintf( chTopSide,"%d", tTPAllDistortParam.dwTopSide );
	sprintf( chBottomSide,"%d", tTPAllDistortParam.dwBottomSide );
	
	s32 dwRotateVal = tTPAllDistortParam.dwCenterRotate - 150;
	if( dwRotateVal < 0 )
	{
		fCenterRotate = (float)(fabs(dwRotateVal*1.0)/100);
		fCenterRotate = -fCenterRotate;
	}
	else
	{
		fCenterRotate = dwRotateVal*1.0/100;
	}

	sprintf(chCenterRotate, "%.2f", fCenterRotate);

	UIFACTORYMGR_PTR->SetCaption(m_strLeftOneEdit, chUperLeftHorizon, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strLeftTwoEdit, chLeftSide, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strLeftThreeEdit, chLowerLeftHorizon, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strLeftFourEdit, chUperLeftVertical, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strLeftFiveEdit, chTopSide, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strLeftSixEdit, chUperRightVertical, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strLeftSevenEdit, chUperRightHorizon, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strLeftEightEdit, chRightSide, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strLeftNineEdit, chLowerRightHorizon, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strLeftTenEdit, chLowerLeftVertical, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strLeftElevenEdit, chBottomSide, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strLeftTwelveEdit, chLowerRightVertical, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRotateLeftEdit, chCenterRotate, m_pWndTree);

}

void CCorrectParamLogic::SetRightDistortValue( TTPAllDistortParam tTPAllDistortParam )
{
	s8 chUperLeftHorizon[10] = {0};
	s8 chUperLeftVertical[10] = {0};
	s8 chUperRightHorizon[10] = {0};
	s8 chUperRightVertical[10] = {0};
	s8 chLowerRightHorizon[10] = {0};
	s8 chLowerRightVertical[10] = {0};
	s8 chLowerLeftHorizon[10] = {0};
	s8 chLowerLeftVertical[10] = {0};
	s8 chLeftSide[10] = {0};
	s8 chRightSide[10] = {0};
	s8 chTopSide[10] = {0};
	s8 chBottomSide[10] = {0};
	s8 chCenterRotate[10] = {0};
	float fCenterRotate;
	
	sprintf( chUperLeftHorizon,"%d", tTPAllDistortParam.dwUperLeftHorizon );
	sprintf( chUperLeftVertical,"%d", tTPAllDistortParam.dwUperLeftVertical );
	sprintf( chUperRightHorizon,"%d", tTPAllDistortParam.dwUperRightHorizon );
	sprintf( chUperRightVertical,"%d", tTPAllDistortParam.dwUperRightVertical );
	sprintf( chLowerRightHorizon,"%d", tTPAllDistortParam.dwLowerRightHorizon );
	sprintf( chLowerRightVertical,"%d", tTPAllDistortParam.dwLowerRightVertical );
	sprintf( chLowerLeftHorizon,"%d", tTPAllDistortParam.dwLowerLeftHorizon );
	sprintf( chLowerLeftVertical,"%d", tTPAllDistortParam.dwLowerLeftVertical );
	sprintf( chLeftSide,"%d", tTPAllDistortParam.dwLeftSide );
	sprintf( chRightSide,"%d", tTPAllDistortParam.dwRightSide );
	sprintf( chTopSide,"%d", tTPAllDistortParam.dwTopSide );
	sprintf( chBottomSide,"%d", tTPAllDistortParam.dwBottomSide );
	
	s32 dwRotateVal = tTPAllDistortParam.dwCenterRotate  - 150;
	if( dwRotateVal < 0 )
	{
		fCenterRotate = (float)(fabs(dwRotateVal*1.0)/100);
		fCenterRotate = -fCenterRotate;
	}
	else
	{
		fCenterRotate = dwRotateVal*1.0/100;
	}

	sprintf(chCenterRotate, "%.2f", fCenterRotate);

	UIFACTORYMGR_PTR->SetCaption(m_strRightOneEdit, chUperLeftHorizon, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRightTwoEdit, chLeftSide, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRightThreeEdit, chLowerLeftHorizon, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRightFourEdit, chUperLeftVertical, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRightFiveEdit, chTopSide, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRightSixEdit, chUperRightVertical, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRightSevenEdit, chUperRightHorizon, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRightEightEdit, chRightSide, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRightNineEdit, chLowerRightHorizon, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRightTenEdit, chLowerLeftVertical, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRightElevenEdit, chBottomSide, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRightTwelveEdit, chLowerRightVertical, m_pWndTree);
	UIFACTORYMGR_PTR->SetCaption(m_strRotateRightEdit, chCenterRotate, m_pWndTree);

}

void CCorrectParamLogic::SetZoomCmd( CString str, u8 byIndex)
{
	String strComboText = CAMERALOGICRPTR->GetCamMechnismStyle();
	
	u32 dwZoom = 0;
	if( strComboText == "Sony")
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

		dwZoom = (fZoom+1.0e-6)*100;
	}
	else
	{
		dwZoom = atoi(LPCTSTR(str));

		if( dwZoom < 1 )
		{
			dwZoom = 1;
		}
		else if( dwZoom > 6775 )
		{
			dwZoom = 6775;
		}

		dwZoom += 199;
	}

	u16 nRet = COMIFMGRPTR->SetCamZoomValueCmd( dwZoom, byIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "zoom请求发送失败" );
	}
}

void CCorrectParamLogic::SetDistortZoomVal( u8 byIndex, u32 dwZoom, u32 dwZoomPos )
{
	if( 0 == m_nbyIndex )
	{
		if( 0 == byIndex )
		{
			float fZoom;
			String strComboText = CAMERALOGICRPTR->GetCamMechnismStyle();
			
			if( strComboText == "Sony")
			{
				fZoom = (float)dwZoom/100;
				CString strCaption;
				strCaption.Format( "%.2f", fZoom );
				
				UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
			}
			else
			{
				CString strCaption;
				dwZoom = dwZoom - 199;
				strCaption.Format( "%d", dwZoom );
				UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
				
				CString strCaption1;
				float fZoomPos = dwZoomPos*1.0/100;
				strCaption1.Format( "%.2f", fZoomPos );
				UIFACTORYMGR_PTR->SetCaption( m_strStcLeftZoom, (String)strCaption1, m_pWndTree );
			}
			
			
		}
		else if( 1 == byIndex )
		{
			float fZoom;
			String strComboText = CAMERALOGICRPTR->GetCamMechnismStyle();
			
			if( strComboText == "Sony")
			{
				fZoom = (float)dwZoom/100;
				CString strCaption;
				strCaption.Format( "%.2f", fZoom );
				
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
			}
			else
			{
				CString strCaption;
				dwZoom = dwZoom - 199;
				strCaption.Format( "%d", dwZoom );
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
				
				CString strCaption1;
				float fZoomPos = dwZoomPos*1.0/100;
				strCaption1.Format( "%.2f", fZoomPos );
				UIFACTORYMGR_PTR->SetCaption( m_strStcRightZoom, (String)strCaption1, m_pWndTree );
			}
		}
	}	
	else
	{
		if( 1 == byIndex )
		{
			float fZoom;
			String strComboText = CAMERALOGICRPTR->GetCamMechnismStyle();
			
			if( strComboText == "Sony")
			{
				fZoom = (float)dwZoom/100;
				CString strCaption;
				strCaption.Format( "%.2f", fZoom );
				
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
			}
			else
			{
				CString strCaption;
				dwZoom = dwZoom - 199;
				strCaption.Format( "%d", dwZoom );
				UIFACTORYMGR_PTR->SetCaption( m_strEdtLeftZoom, (String)strCaption, m_pWndTree );
				
				CString strCaption1;
				float fZoomPos = dwZoomPos*1.0/100;
				strCaption1.Format( "%.2f", fZoomPos );
				UIFACTORYMGR_PTR->SetCaption( m_strStcLeftZoom, (String)strCaption1, m_pWndTree );
			}
			
		}
		else if( 2 == byIndex )
		{
			float fZoom;
			String strComboText = CAMERALOGICRPTR->GetCamMechnismStyle();
			
			if( strComboText == "Sony")
			{
				fZoom = (float)dwZoom/100;
				CString strCaption;
				strCaption.Format( "%.2f", fZoom );
				
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
			}
			else
			{
				CString strCaption;
				dwZoom = dwZoom - 199;
				strCaption.Format( "%d", dwZoom );
				UIFACTORYMGR_PTR->SetCaption( m_strEdtRightZoom, (String)strCaption, m_pWndTree );
				
				CString strCaption1;
				float fZoomPos = dwZoomPos*1.0/100;
				strCaption1.Format( "%.2f", fZoomPos );
				UIFACTORYMGR_PTR->SetCaption( m_strStcRightZoom, (String)strCaption1, m_pWndTree );
			}
			
		}
	}
}

float CCorrectParamLogic::StringToFloatTwo(CString str)
{
	float f = 0;
	f = atof((LPCTSTR)str);
	char strRet[10] = {0};
	sprintf(strRet,"%.2f",f);
	f = atof(strRet);
	return f;
}

float CCorrectParamLogic::StringToFloatThree(CString str)
{
	float f = 0;
	f = atof((LPCTSTR)str);
	char strRet[10] = {0};
	sprintf(strRet,"%.3f",f);
	f = atof(strRet);
	return f;
}

CString CCorrectParamLogic::OnlyFloat(CString str)
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