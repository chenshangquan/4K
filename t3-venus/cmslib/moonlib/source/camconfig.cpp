// cncconfig.cpp: implementation of the CCncConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "camconfig.h"
#include "socketmanager.h"
//#include "rkcevent.h"
#include "rkcprintctrl.h"

static UINT g_nTmHandleWaiting = 0;
static BOOL g_bRecZoomACK = FALSE;
static CRkMessage g_rkmsg;  //消息定义
VOID  CALLBACK  CWaitingTimerFun( HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{   
    if ( idEvent == g_nTmHandleWaiting && g_bRecZoomACK )
    {
        SOCKETWORK->SendDataPack(g_rkmsg);//消息发送
        g_bRecZoomACK = FALSE;
    } 
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCamConfig::CCamConfig(CRkcSession &cSession) : CCamConfigIF()
{
	m_pSession = &cSession;
	m_pTPMoonCamCfg = NULL;
	m_byCameraSel = 0;
	m_byCameraSyncSel = 0;
    m_emTPMechanism = emSonyFCBCS8230;
    m_bSetAllCamCfg = FALSE;
    m_bOutputFmtChg = FALSE;

    memset( &m_tCnCameraCfg1, 0, sizeof(TTPMoonCamInfo) );
    memset( &m_tCnCameraCfg2, 0, sizeof(TTPMoonCamInfo) );
	memset( &m_tCnCameraCfg3, 0, sizeof(TTPMoonCamInfo) );
    ZeroMemory(m_atOldCamCfg, 3*sizeof(TTPMoonCamInfo));

	BuildEventsMap();
}

CCamConfig::~CCamConfig()
{

}

void CCamConfig::BuildEventsMap()
{   
    REG_PFUN( UI_RKC_DISCONNECTED, CCamConfig::OnLinkBreak ); 
	REG_PFUN( ev_TpMoonCamInfo_Nty, CCamConfig::OnMoonCamCfgNty );
	REG_PFUN( ev_TpMechanismSelect_Nty, CCamConfig::OnMechanismSelectNty );
	REG_PFUN( ev_TpMechVer_Nty, CCamConfig::OnTpMechverNty );
	REG_PFUN( ev_TpCamSelect_Nty, CCamConfig::OnCamSelNty );
	REG_PFUN( ev_CamParaSynchronize_Ind, CCamConfig::OnCamParaSynchronizeInd );
	REG_PFUN( ev_TpCamSelect_Ind, CCamConfig::OnCamSelInd );
	REG_PFUN( ev_TpMechanismSelect_Ind, CCamConfig::OnCamStyleSelInd );
    REG_PFUN( ev_TpCamSetGamma_Ind, CCamConfig::OnGammaSelInd );
	REG_PFUN( ev_TpCamSetZoonStart_Ind, CCamConfig::OnCamZoomInd );
	REG_PFUN( ev_TpCamSetZoonStop_Ind, CCamConfig::OnCamZoomStopInd );
	REG_PFUN( ev_TpCamSetDrectZoon_Ind, CCamConfig::OnCamZoomValueInd );
	REG_PFUN( ev_TpCamFocusMode_Ind, CCamConfig::OnCamAutoFocusInd );
	REG_PFUN( ev_TpCamFocusNear_Ind, CCamConfig::OnCamFocusNearInd );
	REG_PFUN( ev_TpCamFocusStop_Ind, CCamConfig::OnCamFocusStopInd );
	REG_PFUN( ev_TpCamFocusFar_Ind, CCamConfig::OnCamFocusFarInd );
	REG_PFUN( ev_TpCamExpMode_Ind, CCamConfig::OnAutoExposureInd );
	REG_PFUN( ev_TpCamExpAperture_Ind, CCamConfig::OnCamApertureInd );
	REG_PFUN( ev_TpCamExpGain_Ind, CCamConfig::OnCamGainInd );	
	REG_PFUN( ev_TpCamExpSOrThShutter_Ind, CCamConfig::OnCamShutSpdCInd );
	REG_PFUN( ev_TpCamExpFOrTwShutter_Ind, CCamConfig::OnCamTwShutSpdCInd );
	REG_PFUN( ev_TpCamWhiteBalanceMode_Ind, CCamConfig::OnCamAutoWBInd );
	REG_PFUN( ev_TpCamWhiteBalanceRGain_Ind, CCamConfig::OnCamRGainInd );
	REG_PFUN( ev_TpCamWhiteBalanceBGain_Ind, CCamConfig::OnCamBGainInd );
	REG_PFUN( ev_TpCamImagePara_Ind, CCamConfig::OnCamImageParaInd ); 
	REG_PFUN( ev_TpCamBackLight_Ind, CCamConfig::OnCamLightPensationInd );
	REG_PFUN( ev_TpCamReduNoise_Ind, CCamConfig::OnCamNRInd );
	REG_PFUN( ev_TpSetCam2DNoiseLevle_Ind, CCamConfig::OnCam2DNRInd );
	REG_PFUN( ev_TpSetCam3DNoiseLevle_Ind, CCamConfig::OnCam3DNRInd );
	REG_PFUN( ev_TpCamInitPreset_Ind, CCamConfig::OnCamOrderPosSelInd );
	REG_PFUN( ev_TpCamPreSet_Nty, CCamConfig::OnCamPreSetNty );
	REG_PFUN( ev_TpCamPreSet_Ind, CCamConfig::OnCamPreSetInd );
	REG_PFUN( ev_TpCamPreReset_Ind, CCamConfig::OnCamPreResetInd );
	REG_PFUN( ev_TpCamPreRecall_Ind, CCamConfig::OnCamPreRecallInd );
	REG_PFUN( ev_TpCamPreModify_Ind, CCamConfig::OnCamPreSetModifyInd );	
	REG_PFUN( ev_TpCamParamDefault_Ind, CCamConfig::OnCamParamDefaultInd );
	REG_PFUN( ev_TpImageDistortCorrect_Ind, CCamConfig::OnCamDistortAdjustInd );
	REG_PFUN( ev_TPChangeSideRGB_Nty, CCamConfig::OnChangeSideRGBNty );
	REG_PFUN( ev_TPDirectSetColorRGB_Ind, CCamConfig::OnSetColorRGBDirectInd );
	REG_PFUN( ev_TPSetColorRGB_Ind, CCamConfig::OnSetColorRGBInd );
	REG_PFUN( ev_TPChooseRectangle_Ind, CCamConfig::OnChooseRectangleInd );
	REG_PFUN( ev_TPAutoSetColorConstancy_Ind, CCamConfig::OnSetAutoColorConstancyInd );
	REG_PFUN( ev_TpMoonUpgrade_Ind, CCamConfig::OnMoonUpgradeInd );	
	REG_PFUN( ev_CamUpgrade_Ind, CCamConfig::OnUpdateMechanismInd );
	REG_PFUN( ev_TpSetRefer_Ind, CCamConfig::OnReferenceLineInd );
	REG_PFUN( ev_TpSetRefer_Nty, CCamConfig::OnReferenceLineNty );
	REG_PFUN( ev_TpFlatTurn_Ind, CCamConfig::OnHorizontalFlipInd );
	REG_PFUN( ev_TpFlatTurn_Nty, CCamConfig::OnHorizontalFlipNty );
	REG_PFUN( ev_TpDisortSwitch_Ind, CCamConfig::OnTrapezoidalCorInd );
	REG_PFUN( ev_TPMoonShowRectRegion_Ind, CCamConfig::OnShowRectRegionInd );
	REG_PFUN( ev_TpColorSwich_Ind, CCamConfig::OnColorSwitchInd );
	REG_PFUN( ev_TpSetDisort_Ind, CCamConfig::OnTraCorParamInd );
	REG_PFUN( ev_TpCamSnapshot_Ind, CCamConfig::SnapShotInd );
	REG_PFUN( ev_TPChangeDistor_Ind, CCamConfig::OnChangeDistortInd );
	REG_PFUN( ev_TPDirectSetDistor_Ind, CCamConfig::OnDirectSetDistortInd );
	REG_PFUN( ev_TpSecDefault_Nty, CCamConfig::OnSecDefaultNty );
	REG_PFUN( ev_TpSecBoundary_Nty, CCamConfig::OnSecBoundaryNty );
	//延时矫正
    REG_PFUN( ev_TpFpgaDelayCorrect_Ind, CCamConfig::OnDelayCorrectInd );
	REG_PFUN( ev_TpFpgaDelayCorrect_Nty, CCamConfig::OnDelayCorrectNty );

    //moon904k30
    REG_PFUN( RK100_EVT_LOGIN_ACK, CCamConfig::OnMoonCamCfgNty );//登陆即通知摄像机配置信息
    REG_PFUN( RK100_EVT_SET_CAM_OUTPUT_FORMAT_ACK, CCamConfig::OnOutputFormatRsp );
    REG_PFUN( RK100_EVT_SET_CAM_FOCUS_ACK, CCamConfig::OnCamAutoFocusInd );
    REG_PFUN( RK100_EVT_SET_CAM_EXPOSURE_ACK, CCamConfig::OnAutoExposureInd );
    REG_PFUN( RK100_EVT_SET_CAM_ZOOM_VAL_ACK, CCamConfig::OnSetCamZoomValRsp );
    REG_PFUN( RK100_EVT_SET_CAM_IRIS_ACK, CCamConfig::OnSetCamApertreRsp );
    REG_PFUN( RK100_EVT_SET_CAM_SHUTTER_ACK, CCamConfig::OnCamShutSpdCInd );
    REG_PFUN( RK100_EVT_SET_CAM_GAIN_ACK, CCamConfig::OnCamGainInd );
    REG_PFUN( RK100_EVT_SET_CAM_WB_ACK, CCamConfig::OnCamAutoWBInd );
    REG_PFUN( RK100_EVT_SET_CAM_ImagParam_ACK, CCamConfig::OnCamImageParaInd );
    REG_PFUN( RK100_EVT_SET_CAM_D2NR_ACK, CCamConfig::OnCam2DNRInd );
    REG_PFUN( RK100_EVT_SET_CAM_D3NR_ACK, CCamConfig::OnCam3DNRInd );
    REG_PFUN( RK100_EVT_SET_CAM_ID_ACK, CCamConfig::OnCamParaSynchronizeInd );
    REG_PFUN( RK100_EVT_SET_CAM_Preset_PowOnRecall_ACK, CCamConfig::OnCamOrderPosSelInd );
    REG_PFUN( RK100_EVT_REBOOT_ACK, CCamConfig::OnReBootRkRsp );
    REG_PFUN( RK100_EVT_RECOVERY_DEFAULT_SET_ACK, CCamConfig::OnCamParamDefaultInd );
    REG_PFUN( RK100_EVT_SET_CAM_Preset_Save_ACK, CCamConfig::OnCamPreSet1SaveRsp );
    REG_PFUN( RK100_EVT_PARAM_INPUT_OVER_ACK, CCamConfig::OnCamParamInputOverRsp );

}

void CCamConfig::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CCamConfig, cMsg);
}

void CCamConfig::OnLinkBreak(const CMessage& cMsg)
{
	PrtRkcMsg( UI_RKC_DISCONNECTED, emEventTypeScoketRecv,"[CCamConfig::OnLinkBreak]清空配置信息" );	
	memset( &m_tCnCameraCfg1, 0, sizeof(TTPMoonCamInfo) );
	memset( &m_tCnCameraCfg2, 0, sizeof(TTPMoonCamInfo) );
	memset( &m_tCnCameraCfg3, 0, sizeof(TTPMoonCamInfo) );
	memset( &m_atTPCamPre, 0, sizeof(TTPCamPre) );
    ZeroMemory(m_atOldCamCfg, 3*sizeof(TTPMoonCamInfo));

    m_bSetAllCamCfg = FALSE;
    m_bOutputFmtChg = FALSE;
	m_pTPMoonCamCfg = NULL;
//	再次登陆记住已选择机芯
//	m_byCameraSel = 0;
	PostEvent(UI_MOONTOOL_DISCONNECTED);
}

void CCamConfig::OnTimeOut(u16 wEvent)
{

}

// Moon90摄像机信息
void CCamConfig::OnMoonCamCfgNty( const CMessage& cMsg )
{
	// 收到三条机芯的nty消息 进一次存一次
	//CTpMsg cTpMsg(&cMsg);
	//TTPMoonCamInfo tTPMoonCamInfo = *(TTPMoonCamInfo*)(cTpMsg.GetBody());
	//u8 byIndex = 0;

	//switch( tTPMoonCamInfo.byIndex )
	//{
	//case 0:
	//	{
	//		m_tCnCameraCfg1 = tTPMoonCamInfo;
	//		byIndex = 0;
	//		//PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&byIndex, (LPARAM)&tTPMoonCamInfo.dwZoom ); //设置左图梯形矫正值
	//		PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&tTPMoonCamInfo, NULL );
	//		break;
	//	}
	//case 1:
	//	{
	//		m_tCnCameraCfg2 = tTPMoonCamInfo;
	//		byIndex = 1;
	//		//PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&byIndex, (LPARAM)&tTPMoonCamInfo.dwZoom ); //设置左图梯形矫正值
	//		PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&tTPMoonCamInfo, NULL );
	//		break;
	//	}
	//case 2:
	//	{
	//		m_tCnCameraCfg3 = tTPMoonCamInfo;
	//		byIndex = 2;
	//		//PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&byIndex, (LPARAM)&tTPMoonCamInfo.dwZoom ); //设置左图梯形矫正值
	//		PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&tTPMoonCamInfo, NULL );
	//		break;
	//	}
	//default:
	//	break;
	//}	

	//if ( m_byCameraSel == tTPMoonCamInfo.byIndex )
	//{
	//	PostEvent( UI_MOONTOOL_CAMINFO_NTY, NULL, NULL );
	//}

	//PrtMsg( ev_TpMoonCamInfo_Nty, emEventTypemoontoolRecv, _T("ev_TpMoonCamInfo_Nty") );
	TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
	tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
	tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
	tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
	tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
	tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
	tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
	tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
	tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
	tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
	tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    if (RK100_OPT_RTN_OK != tMsgHead.wOptRtn && tMsgHead.wOptRtn != RK100_OPT_ERR_FIRST_LOGIN)
    {
        PrtRkcMsg( RK100_EVT_LOGIN_ACK, emEventTypeScoketRecv, _T("Login Error."));
        return;
    }

	TTPMoonCamInfo tTPMoonCamInfo;
    ZeroMemory(&tTPMoonCamInfo, sizeof(TTPMoonCamInfo));

	u8 byIndex = 0xff;
    u8 byCount = tMsgHead.wMsgLen/sizeof(TTPMoonCamInfo);
    if ( byCount <= 0 || byCount > 3 )
    {
        PrtRkcMsg( RK100_EVT_LOGIN_ACK, emEventTypeScoketRecv, ("wMsgLen Error:%d"), tMsgHead.wMsgLen);
        return;
    }
    
	if (tMsgHead.wMsgLen != 0)
	{
        PrtRkcMsg( RK100_EVT_LOGIN_ACK, emEventTypeScoketRecv, "wMsgLen:%d, Need Length:%d", tMsgHead.wMsgLen, sizeof(TTPMoonCamInfo));
        for ( s32 nIndex = 0; nIndex < byCount; nIndex++ )
        {
            tTPMoonCamInfo = *reinterpret_cast<TTPMoonCamInfo*>( cMsg.content + sizeof(TRK100MsgHead) + nIndex*sizeof(TTPMoonCamInfo) );

            //机芯控制逻辑界面映射：1->2, 2->3, 3->1
            if ( tTPMoonCamInfo.TCamIDIndex.CamNum1Flag == 1 )
            {
                m_tCnCameraCfg1 = tTPMoonCamInfo;
                byIndex = 2;
            }
            else if ( tTPMoonCamInfo.TCamIDIndex.CamNum2Flag == 1 )
            {
                m_tCnCameraCfg2 = tTPMoonCamInfo;
                byIndex = 0;
            }
            else if ( tTPMoonCamInfo.TCamIDIndex.CamNum3Flag == 1 )
            {
                m_tCnCameraCfg3 = tTPMoonCamInfo;
                byIndex = 1;
            }
            else
            {
                byIndex = 0xff;
            }

            if ( m_byCameraSel == byIndex )
            {
                PostEvent( UI_MOONTOOL_CAMINFO_NTY, m_byCameraSel, NULL );
	        }

            PrtRkcMsg( RK100_EVT_LOGIN_ACK, emEventTypeScoketRecv, "MoonCamInfo Notify:\n \
<CamNumFlag:[%d,%d,%d],dwZoomPos:%d,GainInputVal:%d>\n \
<R Gain:%d, B Gian:%d>\n \
<BrightVal:%d,ColorHueVal:%d,ColorGainVal:%d, Gama:[%d,%d,%d]>\n \
<OutputFmt:[4K30:%d,4K25:%d,1080P60:%d,1080P50:%d,1080P30:%d,1080P25:%d,720P60:%d,720P50:%d]>",
tTPMoonCamInfo.TCamIDIndex.CamNum1Flag, tTPMoonCamInfo.TCamIDIndex.CamNum2Flag, tTPMoonCamInfo.TCamIDIndex.CamNum3Flag,
tTPMoonCamInfo.dwZoomPos, tTPMoonCamInfo.GainMode.GainInputVal, tTPMoonCamInfo.WBMode.RGainVal, tTPMoonCamInfo.WBMode.BGainVal,
tTPMoonCamInfo.CamImagParam.BrightVal, tTPMoonCamInfo.CamImagParam.ColorHueVal, tTPMoonCamInfo.CamImagParam.ColorGainVal,
tTPMoonCamInfo.CamImagParam.Gamma_opt_1_flag, tTPMoonCamInfo.CamImagParam.Gamma_opt_2_flag, tTPMoonCamInfo.CamImagParam.Gamma_opt_3_flag,
tTPMoonCamInfo.OutputFmt.FMT4K_30fps_flag, tTPMoonCamInfo.OutputFmt.FMT4K_25fps_flag, tTPMoonCamInfo.OutputFmt.FMT1080_60fps_flag, tTPMoonCamInfo.OutputFmt.FMT1080_50fps_flag,
tTPMoonCamInfo.OutputFmt.FMT1080_30fps_flag, tTPMoonCamInfo.OutputFmt.FMT1080_25fps_flag, tTPMoonCamInfo.OutputFmt.FMT720_60fps_flag, tTPMoonCamInfo.OutputFmt.FMT720_50fps_flag);
            PrtRkcMsg( RK100_EVT_LOGIN_ACK, emEventTypeScoketRecv, "\n \
<[Sixty:%d, Thirty:%d], [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]>\n \
<[Fifty:%d, TenwFif:%d], [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]>",
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.SixtyFpsModeFlag, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.ThirtyFpsModeFlag, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_30Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_50Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_60Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_90Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_100Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_125Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_180Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_250Sp,tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_350Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_500Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_725Sp,tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_1000Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_1500Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_2000Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_3000Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_4000Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_6000Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_10000Sp, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.FiftyFpsModeFlag,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.TenwFifFpsModeFlag, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_25Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_30Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_50Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_60Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_100Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_120Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_150Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_215Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_300Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_425Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_600Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_1000Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_1250Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_1750Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_2500Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_3500Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_6000Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_10000Spd);
            PrtRkcMsg( RK100_EVT_LOGIN_ACK, emEventTypeScoketRecv, "\n \
<Focus:[Auto:%d,Manual:%d]>\n \
<AutoExposureMode:%d>\n \
<D2NRMode:[On:%d,Off:%d],level:[%d,%d,%d,%d,%d]>\n \
<D3NRMode:[On:%d,Off:%d],level:[%d,%d,%d,%d,%d]>",
tTPMoonCamInfo.FocusMode.AutoModeFlag, tTPMoonCamInfo.FocusMode.ManualModeFlag, tTPMoonCamInfo.ExpMode.ExposAutoModeFlag,
tTPMoonCamInfo.CamD2NRMode.D2NROnFlag, tTPMoonCamInfo.CamD2NRMode.D2NROffFlag, tTPMoonCamInfo.CamD2NRMode.D2NR_level_1_Flag, tTPMoonCamInfo.CamD2NRMode.D2NR_level_2_Flag,
tTPMoonCamInfo.CamD2NRMode.D2NR_level_3_Flag, tTPMoonCamInfo.CamD2NRMode.D2NR_level_4_Flag, tTPMoonCamInfo.CamD2NRMode.D2NR_level_5_Flag,
tTPMoonCamInfo.CamD3NRMode.D3NROnFlag, tTPMoonCamInfo.CamD3NRMode.D3NROffFlag, tTPMoonCamInfo.CamD3NRMode.D3NR_level_1_Flag, tTPMoonCamInfo.CamD3NRMode.D3NR_level_2_Flag,
tTPMoonCamInfo.CamD3NRMode.D3NR_level_3_Flag, tTPMoonCamInfo.CamD3NRMode.D3NR_level_4_Flag, tTPMoonCamInfo.CamD3NRMode.D3NR_level_5_Flag );

            byIndex = 0xff;
            ZeroMemory(&tTPMoonCamInfo, sizeof(TTPMoonCamInfo));
        }
	}
}

void CCamConfig::OnCamSelNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);

	m_byCameraSel = *(u8*)( cTpMsg.GetBody() );
	SetCameraCfgPtr();

	PrtMsg( ev_TpCamSelect_Nty, emEventTypemoontoolRecv, "byCameraSel:%d", m_byCameraSel );*/
	//if send to the interface
	//PostEvent( UI_MOONTOOL_CamSel_IND, NULL, (LPARAM)bSuccess );
	TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
	tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
	tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
	tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
	tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
	tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
	tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
	tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
	tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
	tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
	tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

	if (tMsgHead.wMsgLen != 0)
	{
		m_byCameraSel = *reinterpret_cast<u8*>( cMsg.content + sizeof(u8) );
		SetCameraCfgPtr();
	}

	PrtRkcMsg( ev_TpCamSelect_Nty, emEventTypeScoketRecv, "byCameraSel:%d", m_byCameraSel);
}

u16 CCamConfig::CamSelCmd( const u8& byCameraIndx )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &byCameraIndx, sizeof(u8) );
	pcTpMsg->SetEvent(ev_TpCamSelect_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSelect_Cmd, emEventTypemoontoolSend, "" );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_ID);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamID));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TCamID tCamID;
    ZeroMemory(&tCamID, sizeof(TCamID));

    //机芯控制逻辑界面映射：1->2, 2->3, 3->1
    if ( byCameraIndx == 0 )
    {
        tCamID.CamNum2Flag = 1;
    }
    else if ( byCameraIndx == 1 )
    {
        tCamID.CamNum3Flag = 1;
    }
    else if ( byCameraIndx == 2 )
    {
        tCamID.CamNum1Flag = 1;
    }

    rkmsg.CatBody(&tCamID, sizeof(TCamID));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_ID, emEventTypeScoketSend ,"SyncFlag:%d, byCameraIndx:%d",tCamID.SyncFlag, byCameraIndx);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnCamSelInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	m_byCameraSel = *(u8*)( cTpMsg.GetBody() );
	BOOL bSelCam = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	SetCameraCfgPtr();
	
	PrtMsg( ev_TpCamSelect_Ind, emEventTypemoontoolRecv, "byCameraSel:%d", m_byCameraSel );
	PostEvent( UI_MOONTOOL_CamSel_IND, NULL, (LPARAM)bSelCam );*/
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    if (tMsgHead.wMsgLen != 0)
    {
        m_byCameraSel = *reinterpret_cast<u8*>( cMsg.content + sizeof(TRK100MsgHead) );
    }
    
    PrtRkcMsg( ev_TpCamSelect_Ind, emEventTypeScoketRecv, "byCameraSel:%d", m_byCameraSel);
    PostEvent( UI_MOONTOOL_CamSel_IND, NULL, (LPARAM)tMsgHead.wOptRtn );
}

u16 CCamConfig::SetMoonCamCfgSyncCmd(const u8& byCameraIndx)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &byCameraIndx, sizeof(u8) );
	pcTpMsg->SetEvent(ev_CamParaSynchronize_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CamParaSynchronize_Cmd, emEventTypemoontoolSend, "" );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_ID);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamID));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TCamID tCamID;
    ZeroMemory(&tCamID, sizeof(TCamID));
    tCamID.SyncFlag = 1;
    //机芯控制逻辑界面映射：1->2, 2->3, 3->1
    if ( byCameraIndx == 0 )
    {
        tCamID.CamNum2Flag = 1;
    }
    else if ( byCameraIndx == 1 )
    {
        tCamID.CamNum3Flag = 1;
    }
    else
    {
        tCamID.CamNum1Flag = 1;
    }

    rkmsg.CatBody(&tCamID, sizeof(TCamID));//添加消息体
    PrtRkcMsg( RK100_EVT_SET_CAM_ID, emEventTypeScoketSend ,"SyncFlag:%d, byCameraIndx:%d", tCamID.SyncFlag, byCameraIndx);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnCamParaSynchronizeInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	m_byCameraSyncSel = *(u8*)( cTpMsg.GetBody() );
	BOOL bSelCamSync = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );

	SetCameraParamSync();
	
	PrtMsg( ev_CamParaSynchronize_Ind, emEventTypemoontoolRecv, "byCameraSyncSel:%d", m_byCameraSyncSel );
	PostEvent( UI_MOONTOOL_CamParamSync_IND, (WPARAM)&m_byCameraSyncSel, (LPARAM)bSelCamSync );*/
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TCamID tCamID;
    ZeroMemory(&tCamID, sizeof(TCamID));
    if (tMsgHead.wMsgLen != 0)
    {
        tCamID = *reinterpret_cast<TCamID*>( cMsg.content + sizeof(TRK100MsgHead) );
    }

    //机芯控制逻辑界面映射：1->2, 2->3, 3->1
    if ( tCamID.CamNum1Flag == 1 )
    {
        m_byCameraSel = 2;
    }
    else if ( tCamID.CamNum2Flag == 1 )
    {
        m_byCameraSel = 0;
    }
    else if ( tCamID.CamNum3Flag == 1 )
    {
        m_byCameraSel = 1;
    }
    else
    {
        //error
    }

    if ( tCamID.SyncFlag )
    {
        SetCameraParamSync();
    }
    
    PrtRkcMsg( RK100_EVT_SET_CAM_ID_ACK, emEventTypeScoketRecv, "SyncFlag:%d, wRtn:%d", tCamID.SyncFlag, tMsgHead.wOptRtn );
    PostEvent( UI_MOONTOOL_CamParamSync_IND, (WPARAM)tCamID.SyncFlag, (LPARAM)tMsgHead.wOptRtn );
}

TTPMoonCamInfo CCamConfig::GetCamCfg()
{
	SetCameraCfgPtr();
	return *m_pTPMoonCamCfg;
}

void CCamConfig::SetAllCamCfg(TTPMoonCamInfo tCamInfo[])
{
    //保存原配置  /* 机芯控制逻辑界面映射：1->2, 2->3, 3->1 */
    m_atOldCamCfg[0] = m_tCnCameraCfg2;
    m_atOldCamCfg[1] = m_tCnCameraCfg3;
    m_atOldCamCfg[2] = m_tCnCameraCfg1;
    //导入参数获取
    m_tCnCameraCfg1 = tCamInfo[0];
    m_tCnCameraCfg2 = tCamInfo[1];
    m_tCnCameraCfg3 = tCamInfo[2];
    m_bSetAllCamCfg = TRUE;
    m_bOutputFmtChg = FALSE;
    AllCamCfgCmdSend();
}

void CCamConfig::GetAllCamCfg(TTPMoonCamInfo* ptCamInfo[])
{
    ptCamInfo[0] = &m_tCnCameraCfg1;
    ptCamInfo[1] = &m_tCnCameraCfg2;
    ptCamInfo[2] = &m_tCnCameraCfg3;
}

void CCamConfig::GetCurStatus(BOOL &bSetCamCfgOver, BOOL &bOutputFmtChg)
{
    bSetCamCfgOver = m_bSetAllCamCfg;
    bOutputFmtChg = m_bOutputFmtChg;
}

void CCamConfig::ClearCurStatus()
{
    m_bSetAllCamCfg = FALSE;
    m_bOutputFmtChg = FALSE;
}

u8 CCamConfig::GetCamSel()const
{
	return m_byCameraSel;
}

void CCamConfig::SetCameraCfgPtr()
{
    //机芯控制逻辑界面映射：1->2, 2->3, 3->1
	switch ( m_byCameraSel )
	{
	case 0:
		{
			m_pTPMoonCamCfg = &m_tCnCameraCfg2;
			break;
		}
	case 1:
		{
			m_pTPMoonCamCfg = &m_tCnCameraCfg3;
			break;
		}
	case 2:
		{
			m_pTPMoonCamCfg = &m_tCnCameraCfg1;
			break;
		}
	default:
		break;
	}
	
	return;
}

void CCamConfig::SetCameraParamSync()
{
    //机芯控制逻辑界面映射：1->2, 2->3, 3->1
    TCamID tCamID;
    ZeroMemory(&tCamID, sizeof(TCamID));
	if( m_byCameraSel == 0 )
	{
		m_tCnCameraCfg1 = m_tCnCameraCfg2;
        m_tCnCameraCfg1.TCamIDIndex = tCamID;
        m_tCnCameraCfg1.TCamIDIndex.CamNum1Flag = 1;

		m_tCnCameraCfg3 = m_tCnCameraCfg2;
        m_tCnCameraCfg3.TCamIDIndex = tCamID;
        m_tCnCameraCfg3.TCamIDIndex.CamNum3Flag = 1;
	}
	else if( m_byCameraSel == 1 )
	{
		m_tCnCameraCfg1 = m_tCnCameraCfg3;
        m_tCnCameraCfg1.TCamIDIndex = tCamID;
        m_tCnCameraCfg1.TCamIDIndex.CamNum1Flag = 1;

		m_tCnCameraCfg2 = m_tCnCameraCfg3;
        m_tCnCameraCfg2.TCamIDIndex = tCamID;
        m_tCnCameraCfg2.TCamIDIndex.CamNum2Flag = 1;
	}
	else
	{
		m_tCnCameraCfg3 = m_tCnCameraCfg1;
        m_tCnCameraCfg3.TCamIDIndex = tCamID;
        m_tCnCameraCfg3.TCamIDIndex.CamNum3Flag = 1;

		m_tCnCameraCfg2 = m_tCnCameraCfg1;
		m_tCnCameraCfg2.TCamIDIndex = tCamID;
        m_tCnCameraCfg2.TCamIDIndex.CamNum2Flag = 1;
	}
}

u16 CCamConfig::CamStyleSelCmd( const EmTPMechanism& emTPMechanism )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emTPMechanism, sizeof(EmTPMechanism) );
	pcTpMsg->SetEvent(ev_TpMechanismSelect_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpMechanismSelect_Cmd, emEventTypemoontoolSend, "emTPMechanism: %d", emTPMechanism); 
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(ev_TpMechanismSelect_Cmd);
    tRK100MsgHead.wMsgLen = htons(sizeof(EmTPMechanism));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    //EmTPMechanism emTPMechanismTmp = (EmTPMechanism)htonl(emTPMechanism);
    rkmsg.CatBody(&emTPMechanism, sizeof(EmTPMechanism));//添加消息体
    
    PrtRkcMsg( ev_TpMechanismSelect_Cmd, emEventTypeScoketSend , "emTPMechanism: %d", emTPMechanism);

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
	return NOERROR;
}

void CCamConfig::OnCamStyleSelInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	EmTPMechanism emTPMechanism = *(EmTPMechanism*)( cTpMsg.GetBody() );
	BOOL bSelStyleCam = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTPMechanism) );
	SetCameraCfgPtr();
	
	PrtMsg( ev_TpMechanismSelect_Ind, emEventTypemoontoolRecv, "emTPMechanism: %d, bSelStyleCam: %d", emTPMechanism, bSelStyleCam );
	PostEvent( UI_MOONTOOL_CamStyleSel_IND, (WPARAM)&emTPMechanism, (LPARAM)bSelStyleCam );*/

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    EmTPMechanism emTPMechanism = emH650;
    if (tMsgHead.wMsgLen != 0)
    {
        emTPMechanism = *reinterpret_cast<EmTPMechanism*>( cMsg.content + sizeof(TRK100MsgHead) );
        SetCameraCfgPtr();
    }
    
	PrtRkcMsg( ev_TpMechanismSelect_Ind, emEventTypeScoketRecv, "emTPMechanism: %d, bSelStyleCam: %d", emTPMechanism, tMsgHead.wOptRtn);
    PostEvent( UI_MOONTOOL_CamStyleSel_IND, (WPARAM)&emTPMechanism, (LPARAM)tMsgHead.wOptRtn );
}

u16 CCamConfig::SetOutputFormatCmd( const TPOutputFmt& tOutputFmt)
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_OUTPUT_FORMAT);
    tRK100MsgHead.wMsgLen = htons(sizeof(TPOutputFmt));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tOutputFmt, sizeof(TPOutputFmt));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_OUTPUT_FORMAT, emEventTypeScoketSend , "4K_30:%d, 4K_25:%d, 1080_60:%d, 1080_50:%d, 1080_30:%d, 1080_25:%d, 720_60:%d, 720_50:%d",
        tOutputFmt.FMT4K_30fps_flag, tOutputFmt.FMT4K_25fps_flag,
        tOutputFmt.FMT1080_60fps_flag, tOutputFmt.FMT1080_50fps_flag, tOutputFmt.FMT1080_30fps_flag, tOutputFmt.FMT1080_25fps_flag,
        tOutputFmt.FMT720_60fps_flag, tOutputFmt.FMT720_50fps_flag);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnOutputFormatRsp(const CMessage& cMsg)
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TPOutputFmt tOutputFmt;
    ZeroMemory(&tOutputFmt, sizeof(TPOutputFmt));
    if (tMsgHead.wMsgLen != 0)
    {
        tOutputFmt = *reinterpret_cast<TPOutputFmt*>( cMsg.content + sizeof(TRK100MsgHead) );
    }

    if ( RK100_OPT_RTN_OK == tMsgHead.wOptRtn )
    {
        m_pTPMoonCamCfg->OutputFmt = tOutputFmt;
    }
    
    PrtRkcMsg( RK100_EVT_SET_CAM_OUTPUT_FORMAT_ACK, emEventTypeScoketRecv, "wRtn:%d", tMsgHead.wOptRtn);

    //导入界面参数，若输出制式改变，无需通知界面
    if ( m_bSetAllCamCfg )
    {
        m_bOutputFmtChg = TRUE;
    }
    else
    {
        PostEvent( UI_MOONTOOL_OUTPUT_FORMAT_RSP, (WPARAM)(RK100_OPT_RTN_OK == tMsgHead.wOptRtn), (LPARAM)tMsgHead.wOptRtn );
    }
}

TPOutputFmt CCamConfig::GetOutputFormat()
{
    if (m_pTPMoonCamCfg == NULL)
    {
        SetCameraCfgPtr();
    }
    
	return m_pTPMoonCamCfg->OutputFmt;
}

u16 CCamConfig::SetCamZoomValCmd( const TCamZoomVal& tCamZoomVal)
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_ZOOM_VAL);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamZoomVal));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tCamZoomVal, sizeof(TCamZoomVal));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_ZOOM_VAL, emEventTypeScoketSend , "CamZoomSet:[InputValFlag:%d,Val:%d,Up:%d,Down:%d,Stop:%d]",
        tCamZoomVal.InputPreciseValFlag, tCamZoomVal.InputVal, tCamZoomVal.ZoomUpFlag, tCamZoomVal.ZoomDownFlag, tCamZoomVal.ZoomUpDownStopFlag);
    
    //ZOOM+/- 长按可持续调节
    if (tCamZoomVal.InputPreciseValFlag == 1)
    {
        SOCKETWORK->SendDataPack(rkmsg);//消息发送
    }
    else
    {
        g_rkmsg = rkmsg;
        if ( g_nTmHandleWaiting == 0 )
        {
            SOCKETWORK->SendDataPack(rkmsg);//消息发送
            g_nTmHandleWaiting = SetTimer( NULL, 0, 100, CWaitingTimerFun );
        }
    }

    return NOERROR;
}

void CCamConfig::OnSetCamZoomValRsp(const CMessage& cMsg)
{
    if ( m_pTPMoonCamCfg == NULL )
    {
        SetCameraCfgPtr();
	}

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TCamZoomVal tCamZoomVal;
    if (tMsgHead.wMsgLen != 0)
    {
        tCamZoomVal = *reinterpret_cast<TCamZoomVal*>( cMsg.content + sizeof(TRK100MsgHead) );
    }

    if ( tMsgHead.wOptRtn == RK100_OPT_RTN_OK )
    {
        //zoom持续调节
        if (g_nTmHandleWaiting != 0)
        {
            if ( SetCamZoomValCmd(tCamZoomVal) == NO_ERROR )
            {
                g_bRecZoomACK = TRUE;
            }
        }
        
        m_pTPMoonCamCfg->dwZoomPos = tCamZoomVal.InputVal;
    }

    PrtRkcMsg( RK100_EVT_SET_CAM_ZOOM_VAL_ACK, emEventTypeScoketRecv, "wRtn:%d, InputVal:%d", tMsgHead.wOptRtn, tCamZoomVal.InputVal);
    PostEvent( UI_MOONTOOL_SET_CAMERA_ZOOM_IND, 0, (LPARAM)tMsgHead.wOptRtn );
}

u16 CCamConfig::SetCamZoomCmd( const EmTPZOOM& emZoom, u8 byIndex)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emZoom, sizeof(EmTPZOOM) );
	pcTpMsg->CatBody( &byIndex, sizeof(u8));
	pcTpMsg->SetEvent(ev_TpCamSetZoonStart_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSetZoonStart_Cmd, emEventTypemoontoolSend, "emZoom:%d, byIndex:%d", emZoom, byIndex );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(ev_TpCamSetZoonStart_Cmd);
    tRK100MsgHead.wMsgLen = htons(sizeof(EmTPZOOM) + sizeof(u8));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&emZoom, sizeof(EmTPZOOM));//添加消息体
    rkmsg.CatBody(&byIndex, sizeof(u8));
    
    PrtRkcMsg( ev_TpCamSetZoonStart_Cmd, emEventTypeScoketSend , "emZoom:%d, byIndex:%d", emZoom, byIndex);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

u16 CCamConfig::SetCamZoomStopCmd(u8 byIndex)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&byIndex, sizeof(u8));
	pcTpMsg->SetEvent(ev_TpCamSetZoonStop_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSetZoonStop_Cmd, emEventTypemoontoolSend, "byIndex: %d", byIndex );
	return wRet;*/

    /*TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_ZOOM_VAL);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamZoomVal));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TCamZoomVal tCamZoomVal;
    ZeroMemory(&tCamZoomVal, sizeof(TCamZoomVal));
    tCamZoomVal.InputVal = m_pTPMoonCamCfg->dwZoomPos;
    tCamZoomVal.ZoomUpDownStopFlag = 1;

    rkmsg.CatBody(&tCamZoomVal, sizeof(TCamZoomVal));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_ZOOM_VAL, emEventTypeScoketSend , "CamZoomStop:[InputValFlag:%d,Val:%d,Up:%d,Down:%d,Stop:%d].",
        tCamZoomVal.InputPreciseValFlag, tCamZoomVal.InputVal, tCamZoomVal.ZoomUpFlag, tCamZoomVal.ZoomDownFlag, tCamZoomVal.ZoomUpDownStopFlag);*/

    KillTimer( NULL, g_nTmHandleWaiting );
    g_nTmHandleWaiting = 0;
    
    //SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnCamZoomInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	EmTPZOOM emZoom = *(EmTPZOOM*)( cTpMsg.GetBody() );
	u8 byIndex = *(u8*)( cTpMsg.GetBody() + sizeof(EmTPZOOM) );
	BOOL bCamZoom = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTPZOOM) + sizeof(u8) );
	PrtMsg( ev_TpCamSetZoonStart_Ind, emEventTypemoontoolRecv, "EmTPZOOM:%d, byIndex:%d, BOOL:%d", emZoom, byIndex, bCamZoom );*/
    if ( m_pTPMoonCamCfg == NULL )
    {
        SetCameraCfgPtr();
	}

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    EmTPZOOM emZoom = emEnlarge;
    u8 byIndex = 0;
    if (tMsgHead.wMsgLen != 0)
    {
        emZoom = *reinterpret_cast<EmTPZOOM*>( cMsg.content + sizeof(TRK100MsgHead) );
        byIndex = *reinterpret_cast<u8*>( cMsg.content + sizeof(TRK100MsgHead) + sizeof(EmTPZOOM) );
    }
    
    PrtRkcMsg( ev_TpCamSetZoonStart_Ind, emEventTypeScoketRecv, "EmTPZOOM:%d, byIndex:%d, BOOL:%d", emZoom, byIndex, tMsgHead.wOptRtn);
}

void CCamConfig::OnCamZoomStopInd(const CMessage& cMsg)
 {
	//CTpMsg cTpMsg(&cMsg);

	//u8 byIndex = *(u8*)( cTpMsg.GetBody() );
	//u32 dwZoom = *(u32*)( cTpMsg.GetBody() + sizeof(u8) );
	//BOOL bCamZoom = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(u32) );
	//u32 dwZoomPos = *(u32*)(cTpMsg.GetBody() + sizeof(u8) + sizeof(u32) + sizeof(BOOL) );

	//switch(byIndex)
	//{
	//case 0:
	//	{
	//		m_tCnCameraCfg1.dwZoom = dwZoom;
	//		m_tCnCameraCfg1.dwZoomPos = dwZoomPos;
	//		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg1, (LPARAM)&bCamZoom );
	//		break;
	//	}
	//case 1:
	//	{
	//		m_tCnCameraCfg2.dwZoom = dwZoom;
	//		m_tCnCameraCfg2.dwZoomPos = dwZoomPos;
	//		m_tCnCameraCfg2.byIndex = 1;
	//		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg2, (LPARAM)&bCamZoom );
	//		break;
	//	}
	//case 2:
	//	{
	//		m_tCnCameraCfg3.dwZoom = dwZoom;
	//		m_tCnCameraCfg3.dwZoomPos = dwZoomPos;
	//		m_tCnCameraCfg3.byIndex = 2;
	//		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg3, (LPARAM)&bCamZoom );
	//		break;
	//	}
	//default:break;
	//}

	//if (m_pTPMoonCamCfg->byIndex == byIndex)
	//{
	//	m_pTPMoonCamCfg->dwZoom = dwZoom;
	//	m_pTPMoonCamCfg->dwZoomPos = dwZoomPos;
	//}
	////m_pTPMoonCamCfg->dwZoom = *(u32*)( cTpMsg.GetBody() + sizeof(u8) );
	//PrtMsg( ev_TpCamSetZoonStop_Ind, emEventTypemoontoolRecv, "byIndex:%d, dwZoom: %d, dwZoomPos: %d\n", byIndex, dwZoom, dwZoomPos );

	//if ( byIndex == m_byCameraSel )
	//{
	//	PostEvent( UI_MOONTOOL_SET_CAMERA_ZOOM_IND, 0, (LPARAM)bCamZoom );
	//}
}

u16 CCamConfig::SetCamZoomValueCmd( const u32& dwZoom, u8 byIndex)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &dwZoom, sizeof(u32) );
	pcTpMsg->CatBody( &byIndex, sizeof(u8) );
	pcTpMsg->SetEvent(ev_TpCamSetDrectZoon_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSetDrectZoon_Cmd, emEventTypemoontoolSend, "dwZoom:%d, byIndex: %d", dwZoom, byIndex);
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(ev_TpCamSetDrectZoon_Cmd);
    tRK100MsgHead.wMsgLen = htons(sizeof(u32) + sizeof(u8));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    u32 dwZoomTmp = htonl(dwZoom);
    rkmsg.CatBody(&dwZoomTmp, sizeof(u32));//添加消息体
    rkmsg.CatBody(&byIndex, sizeof(u8));
    
    PrtRkcMsg( ev_TpCamSetDrectZoon_Cmd, emEventTypeScoketSend, "dwZoom:%d, byIndex: %d", dwZoom, byIndex);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnCamZoomValueInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);

	u32 dwZoom = *(u32*)( cTpMsg.GetBody());

	u8 byIndex = *(u8*)( cTpMsg.GetBody()+ sizeof(u32) );

	BOOL bOk = *(BOOL*)( cTpMsg.GetBody()+ sizeof(u32) + sizeof(u8) );

	u32 dwZoomPos = *(u32*)( cTpMsg.GetBody()+ sizeof(u32) + sizeof(u8) + sizeof(BOOL) );

	if( 0 == byIndex )
	{
		m_tCnCameraCfg1.dwZoom = dwZoom;
		m_tCnCameraCfg1.dwZoomPos = dwZoomPos;
		m_tCnCameraCfg1.byIndex = 0;
		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg1, (LPARAM)&bOk );
	}
	else if( 1 == byIndex )
	{
		m_tCnCameraCfg2.dwZoom = dwZoom;
		m_tCnCameraCfg2.dwZoomPos = dwZoomPos;
		m_tCnCameraCfg2.byIndex = 1;
		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg2, (LPARAM)&bOk );
	}
	else
	{
		m_tCnCameraCfg3.dwZoom = dwZoom;
		m_tCnCameraCfg3.byIndex = 2;
		m_tCnCameraCfg3.dwZoomPos = dwZoomPos;
		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg3, (LPARAM)&bOk );
	}

	if (m_pTPMoonCamCfg->byIndex == byIndex)
	{
		m_pTPMoonCamCfg->dwZoom = dwZoom;
		m_pTPMoonCamCfg->dwZoomPos = dwZoomPos;
	}

	PrtMsg( ev_TpCamSetDrectZoon_Ind, emEventTypemoontoolRecv, "byIndex:%d, dwZoom: %d, bOk: %d, dwZoomPos: %d", byIndex, dwZoom, bOk, dwZoomPos );
	
	if ( byIndex == m_byCameraSel )
	{
		PostEvent( UI_MOONTOOL_SET_CAMERA_ZOOM_IND, 0, (LPARAM)bOk );
	}	*/

}

u32 CCamConfig::GetCamZoom()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->dwZoomPos;	
}

u32 CCamConfig::GetExtCamZoom()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	return m_pTPMoonCamCfg->dwZoomPos;	
}

//聚焦 手动/自动
u16 CCamConfig::SetCamAutoFocusCmd(const EmTPMOOMMode& emFocusMode)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emFocusMode, sizeof(EmTPMOOMMode) );
	
	pcTpMsg->SetEvent(ev_TpCamFocusMode_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamFocusMode_Cmd, emEventTypemoontoolSend, "EmTPMOOMMode:%d", emFocusMode );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_FOCUS);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamFocusAutoManualMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TCamFocusAutoManualMode tCamFocusMode;
    ZeroMemory(&tCamFocusMode, sizeof(TCamFocusAutoManualMode));
    if ( emFocusMode == emAuto )
    {
        tCamFocusMode.AutoModeFlag = 1;
    }
    else
    {
        tCamFocusMode.ManualModeFlag = 1;
    }

    rkmsg.CatBody(&tCamFocusMode, sizeof(TCamFocusAutoManualMode));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_FOCUS, emEventTypeScoketSend, "EmTPMOOMMode:%d", emFocusMode);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnCamAutoFocusInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emFocusMode = *(EmTPMOOMMode*)( cTpMsg.GetBody() );

	BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(EmTPMOOMMode) );

	PrtMsg( ev_TpCamFocusMode_Ind, emEventTypemoontoolRecv, "EmTPMOOMMode:%d, BOOL:%d", m_pTPMoonCamCfg->emFocusMode, bOk );
	PostEvent( UI_MOONTOOL_CAMERA_AUTO_FOCUS_IND, (WPARAM)(m_pTPMoonCamCfg->emFocusMode), (LPARAM)bOk );*/
    if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    EmTPMOOMMode emFocusMode = emAuto;
    if (tMsgHead.wMsgLen != 0)
    {
        TCamFocusAutoManualMode tCamFocusAutoManualMode = *reinterpret_cast<TCamFocusAutoManualMode*>( cMsg.content + sizeof(TRK100MsgHead) );
        if (tCamFocusAutoManualMode.AutoModeFlag)
        {
            m_pTPMoonCamCfg->FocusMode.AutoModeFlag = 1;
            m_pTPMoonCamCfg->FocusMode.ManualModeFlag = 0;
            emFocusMode = emAuto;
        }
        else
        {
            m_pTPMoonCamCfg->FocusMode.ManualModeFlag = 1;
            m_pTPMoonCamCfg->FocusMode.AutoModeFlag = 0;
            emFocusMode = emManual;
        }
    }
    
    PrtRkcMsg( RK100_EVT_SET_CAM_FOCUS_ACK, emEventTypeScoketRecv, "EmFocusMode:%d, wRtn:%d", emFocusMode, tMsgHead.wOptRtn);
    PostEvent( UI_MOONTOOL_CAMERA_AUTO_FOCUS_IND, (WPARAM)emFocusMode, (LPARAM)tMsgHead.wOptRtn );
}

//聚焦 拉近/拉远
u16 CCamConfig::SetCamFocusNearCmd()
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	pcTpMsg->SetEvent(ev_TpCamFocusNear_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamFocusNear_Cmd, emEventTypemoontoolSend, "" );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_FOCUS);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamFocusAutoManualMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TCamFocusAutoManualMode tCamFocusMode;
    ZeroMemory(&tCamFocusMode, sizeof(TCamFocusAutoManualMode));
    tCamFocusMode.ManualModeFlag = 1;
    tCamFocusMode.focusNearFlag = 1;
    rkmsg.CatBody(&tCamFocusMode, sizeof(TCamFocusAutoManualMode));//添加消息体

    PrtRkcMsg( RK100_EVT_SET_CAM_FOCUS, emEventTypeScoketSend, "NearFlag:%d, FarFlag:%d", tCamFocusMode.focusNearFlag, tCamFocusMode.focusFarFlag);

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

u16 CCamConfig::SetCamFocusStopCmd()
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	pcTpMsg->SetEvent(ev_TpCamFocusStop_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamFocusStop_Cmd, emEventTypemoontoolSend, "" );
	return wRet;*/
	TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_FOCUS);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamFocusAutoManualMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TCamFocusAutoManualMode tCamFocusMode;
    ZeroMemory(&tCamFocusMode, sizeof(TCamFocusAutoManualMode));
    tCamFocusMode.ManualModeFlag = 1;
    tCamFocusMode.FarNearStopFlag = 1;
    rkmsg.CatBody(&tCamFocusMode, sizeof(TCamFocusAutoManualMode));//添加消息体

    PrtRkcMsg( RK100_EVT_SET_CAM_FOCUS, emEventTypeScoketSend, "Focus stop.");

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

u16 CCamConfig::SetCamFocusFarCmd()
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	pcTpMsg->SetEvent(ev_TpCamFocusFar_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamFocusFar_Cmd, emEventTypemoontoolSend, "" );
	return wRet;*/
	TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_FOCUS);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamFocusAutoManualMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TCamFocusAutoManualMode tCamFocusMode;
    ZeroMemory(&tCamFocusMode, sizeof(TCamFocusAutoManualMode));
    tCamFocusMode.ManualModeFlag = 1;
    tCamFocusMode.focusFarFlag = 1;
    rkmsg.CatBody(&tCamFocusMode, sizeof(TCamFocusAutoManualMode));//添加消息体

    PrtRkcMsg( RK100_EVT_SET_CAM_FOCUS, emEventTypeScoketSend, "NearFlag:%d, FarFlag:%d", tCamFocusMode.focusNearFlag, tCamFocusMode.focusFarFlag);

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnCamFocusNearInd( const CMessage& cMsg )
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);	
	BOOL bFocusNear =  *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	PrtMsg( ev_TpCamFocusNear_Ind, emEventTypemoontoolRecv, "bFocusNear:%d", bFocusNear );*/
    if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    PrtRkcMsg( ev_TpCamFocusNear_Ind, emEventTypeScoketRecv, "bFocusNear:%d", tMsgHead.wOptRtn);
}

void CCamConfig::OnCamFocusStopInd( const CMessage& cMsg )
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);	
	BOOL bIsStop =  *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	PrtMsg( ev_TpCamFocusStop_Ind, emEventTypemoontoolRecv, "bIsStop:%d", bIsStop );*/

    if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    PrtRkcMsg( ev_TpCamFocusStop_Ind, emEventTypeScoketRecv, "bIsStop:%d", tMsgHead.wOptRtn);
}

void CCamConfig::OnCamFocusFarInd( const CMessage& cMsg )
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);	
	BOOL bFocusFar =  *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	PrtMsg( ev_TpCamFocusFar_Ind, emEventTypemoontoolRecv, "bFocusFar:%d", bFocusFar );	*/

    if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    PrtRkcMsg( ev_TpCamFocusFar_Ind, emEventTypeScoketRecv, "bFocusFar:%d", tMsgHead.wOptRtn);
}

//光圈设置 mooon904k30 新增
u16 CCamConfig::SetCamApertreCmd( const TIrisAutoManuMode& tIrisAutoManuMode )
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_IRIS);
    tRK100MsgHead.wMsgLen = htons(sizeof(TIrisAutoManuMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tIrisAutoManuMode, sizeof(TIrisAutoManuMode));//添加消息体

    PrtRkcMsg( RK100_EVT_SET_CAM_IRIS, emEventTypeScoketSend, "IsAuto:%d, IrisBackCompFlag:%d, IrisOpt:<2.8:%d,3.1:%d,3.4:%d,3.7:%d,4.0:%d,4.5:%d>",
        tIrisAutoManuMode.IrisAutoFlag, tIrisAutoManuMode.IrisBackCompFlag, tIrisAutoManuMode.optIrisF2_8Flag, tIrisAutoManuMode.optIrisF3_1Flag,
        tIrisAutoManuMode.optIrisF3_4Flag, tIrisAutoManuMode.optIrisF3_7Flag, tIrisAutoManuMode.optIrisF4_0Flag, tIrisAutoManuMode.optIrisF4_4Flag);

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnSetCamApertreRsp( const CMessage& cMsg )
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TIrisAutoManuMode tIrisAutoManuMode;
    if (tMsgHead.wMsgLen != 0)
    {
        tIrisAutoManuMode = *reinterpret_cast<TIrisAutoManuMode*>( cMsg.content + sizeof(TRK100MsgHead) );
    }

    if ( RK100_OPT_RTN_OK == tMsgHead.wOptRtn )
    {
        if ( 1 == tIrisAutoManuMode.IrisAutoFlag )
        {
            m_pTPMoonCamCfg->IrisMode.IrisAutoFlag = 1;
            m_pTPMoonCamCfg->IrisMode.IrisManuFlag = 0;
            m_pTPMoonCamCfg->IrisMode.IrisBackCompFlag = tIrisAutoManuMode.IrisBackCompFlag;
        }

        if ( 1 == tIrisAutoManuMode.IrisManuFlag )
        {
            m_pTPMoonCamCfg->IrisMode.IrisAutoFlag = 0;
            m_pTPMoonCamCfg->IrisMode.IrisManuFlag = 1;
            m_pTPMoonCamCfg->IrisMode.optIrisF2_8Flag = tIrisAutoManuMode.optIrisF2_8Flag;
            m_pTPMoonCamCfg->IrisMode.optIrisF3_1Flag = tIrisAutoManuMode.optIrisF3_1Flag;
            m_pTPMoonCamCfg->IrisMode.optIrisF3_4Flag = tIrisAutoManuMode.optIrisF3_4Flag;
            m_pTPMoonCamCfg->IrisMode.optIrisF3_7Flag = tIrisAutoManuMode.optIrisF3_7Flag;
            m_pTPMoonCamCfg->IrisMode.optIrisF4_0Flag = tIrisAutoManuMode.optIrisF4_0Flag;
            m_pTPMoonCamCfg->IrisMode.optIrisF4_4Flag = tIrisAutoManuMode.optIrisF4_4Flag;
        }
    }
    
    PrtRkcMsg( RK100_EVT_SET_CAM_IRIS_ACK, emEventTypeScoketRecv, "wRtn:%d, AutoFlag:%d, ManuFlag:%d",
        tMsgHead.wOptRtn, tIrisAutoManuMode.IrisAutoFlag, tIrisAutoManuMode.IrisManuFlag);
    PostEvent( UI_MOONTOOL_CAMERA_APERTRE_RSP, NULL, (LPARAM)tMsgHead.wOptRtn );
}

//是否开启自动曝光
u16 CCamConfig::CamAutoExposureCmd( const EmTPMOOMMode& emExpAuto )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emExpAuto, sizeof(EmTPMOOMMode) );	
	pcTpMsg->SetEvent(ev_TpCamExpMode_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamExpMode_Cmd, emEventTypemoontoolSend, "CamAutoExposureCmd:%d", emExpAuto );
	return wRet;*/
	TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_EXPOSURE);
    tRK100MsgHead.wMsgLen = htons(sizeof(TExposAutoMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TExposAutoMode tExposAutoMode;
    ZeroMemory(&tExposAutoMode, sizeof(TExposAutoMode));
    if ( emExpAuto == emAuto )
    {
        tExposAutoMode.ExposAutoModeFlag = 1;
    }

    rkmsg.CatBody(&tExposAutoMode, sizeof(TExposAutoMode));//添加消息体

    PrtRkcMsg( RK100_EVT_SET_CAM_EXPOSURE, emEventTypeScoketSend, "ExposAutoMode:%d", tExposAutoMode.ExposAutoModeFlag);

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

EmTPMOOMMode CCamConfig::GetCamMoonMode()
{
	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

    EmTPMOOMMode emFocusMode = emAuto;
    if (m_pTPMoonCamCfg->FocusMode.ManualModeFlag)
    {
        emFocusMode = emManual;
    }
	
	return emFocusMode;
}

void CCamConfig::OnAutoExposureInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emExpMode = *(EmTPMOOMMode*)( cTpMsg.GetBody() );
	BOOL bAutoExposure = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(EmTPMOOMMode) );
	
	PrtMsg( ev_TpCamExpMode_Ind, emEventTypemoontoolRecv, "EmExpMode:%d, AutoExposureInd:%d", m_pTPMoonCamCfg->emExpMode, bAutoExposure );
	PostEvent( UI_MOONTOOL_CAMERA_AUTO_EXPOSURE_IND, NULL, (LPARAM)bAutoExposure );*/
    if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    TExposAutoMode tExposAutoMode;
    ZeroMemory(&tExposAutoMode, sizeof(TExposAutoMode));
    if (tMsgHead.wMsgLen != 0)
    {
        tExposAutoMode = *reinterpret_cast<TExposAutoMode*>( cMsg.content + sizeof(TRK100MsgHead) );
    }

    if ( RK100_OPT_RTN_OK == tMsgHead.wOptRtn )
    {
        m_pTPMoonCamCfg->ExpMode.ExposAutoModeFlag = tExposAutoMode.ExposAutoModeFlag;
    }

    PrtRkcMsg( RK100_EVT_SET_CAM_EXPOSURE_ACK, emEventTypeScoketRecv, "EmExpAutoMode:%d, wRtn:%d", tExposAutoMode.ExposAutoModeFlag, tMsgHead.wOptRtn);
    PostEvent( UI_MOONTOOL_CAMERA_AUTO_EXPOSURE_IND, NULL, (LPARAM)tMsgHead.wOptRtn );
}

//光圈
u16 CCamConfig::CamApertureCmd( const EmTPAperture& emAperture )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emAperture, sizeof(EmTPAperture) );
	pcTpMsg->SetEvent(ev_TpCamExpAperture_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamExpAperture_Cmd, emEventTypemoontoolSend, "CamApertureCmd:%d", emAperture );
	return wRet;*/
	TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(ev_TpCamExpAperture_Cmd);
    tRK100MsgHead.wMsgLen = htons(sizeof(EmTPAperture));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&emAperture, sizeof(EmTPAperture));//添加消息体

    PrtRkcMsg( ev_TpCamExpAperture_Cmd, emEventTypeScoketSend, "CamApertureCmd:%d", emAperture);

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

EmTPAperture CCamConfig::GetCamAperture()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
    EmTPAperture tt = em_Aperture_F2_8;
	return tt;
}

void CCamConfig::OnCamApertureInd(const CMessage& cMsg)
{
	//if (m_pTPMoonCamCfg == NULL)
	//{
	//	SetCameraCfgPtr();
	//}
	//
	//CTpMsg cTpMsg(&cMsg);
	//
	//m_pTPMoonCamCfg->emAper = *(EmTPAperture*)( cTpMsg.GetBody() );
	//BOOL bCamAperture = *(BOOL*)( cTpMsg.GetBody() +sizeof(u8) +sizeof(EmTPAperture) );
	//PrtMsg( ev_TpCamExpAperture_Ind, emEventTypemoontoolRecv, "EmTPAperture:%d, BOOL:%d", m_pTPMoonCamCfg->emAper, bCamAperture );
	//// 通知界面操作成功与否
	//PostEvent( UI_MOONTOOL_CAMERA_APERTURE_IND, NULL, (LPARAM)bCamAperture );
    if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    if (tMsgHead.wMsgLen != 0)
    {
        //m_pTPMoonCamCfg->emAper = *reinterpret_cast<EmTPAperture*>( cMsg.content + sizeof(TRK100MsgHead) );
    }

    //PrtRkcMsg( ev_TpCamExpAperture_Ind, emEventTypeScoketRecv, "EmTPAperture:%d, wRtn:%d", m_pTPMoonCamCfg->emAper, tMsgHead.wOptRtn);
}

// 快门
u16 CCamConfig::CamShutSpdCmd( const EmTPSOrThShutter& emShutSpd )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emShutSpd, sizeof(EmTPSOrThShutter) );
	pcTpMsg->SetEvent(ev_TpCamExpSOrThShutter_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamExpSOrThShutter_Cmd, emEventTypemoontoolSend, "CamShutSpdCmd:%d", emShutSpd );
	return wRet;*/

    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_SHUTTER);
    tRK100MsgHead.wMsgLen = htons(sizeof(TShutterMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TShutterMode tShutterMode;
    ZeroMemory(&tShutterMode, sizeof(TShutterMode));
    switch (emShutSpd)
    {
    case em_Shutter_30Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_30Sp = 1;
            break;
        }
    case em_Shutter_50Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_50Sp = 1;
            break;
        }
    case em_Shutter_60Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_60Sp = 1;
            break;
        }
    case em_Shutter_90Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_90Sp = 1;
            break;
        }
    case em_Shutter_100Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_100Sp = 1;
            break;
        }
    case em_Shutter_125Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_125Sp = 1;
            break;
        }
    case em_Shutter_180Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_180Sp = 1;
            break;
        }
    case em_Shutter_250Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_250Sp = 1;
            break;
        }
    case em_Shutter_350Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_350Sp = 1;
            break;
        }
    case em_Shutter_500Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_500Sp = 1;
            break;
        }
    case em_Shutter_725Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_725Sp = 1;
            break;
        }
    case em_Shutter_1000Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_1000Sp = 1;
            break;
        }
    case em_Shutter_1500Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_1500Sp = 1;
            break;
        }
    case em_Shutter_2000Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_2000Sp = 1;
            break;
        }
    case em_Shutter_3000Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_3000Sp = 1;
            break;
        }
    case em_Shutter_4000Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_4000Sp = 1;
            break;
        }
    case em_Shutter_6000Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_6000Sp = 1;
            break;
        }
    case em_Shutter_10000Sp:
        {
            tShutterMode.SixtyOrThirtyMode.Shutter_10000Sp = 1;
            break;
        }
    default:
        break;
    }

    rkmsg.CatBody(&tShutterMode, sizeof(TShutterMode));//添加消息体
    PrtRkcMsg( RK100_EVT_SET_CAM_SHUTTER, emEventTypeScoketSend, "EmTPSOrThShutter:%d", emShutSpd);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

u16 CCamConfig::CamTwShutSpdCmd( const EmTPFOrTwShutter& emTwShutter )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emTwShutter, sizeof(EmTPFOrTwShutter) );
	pcTpMsg->SetEvent(ev_TpCamExpFOrTwShutter_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamExpFOrTwShutter_Cmd, emEventTypemoontoolSend, "CamTwShutSpdCmd:%d", emTwShutter );
	return wRet;*/
	TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_SHUTTER);
    tRK100MsgHead.wMsgLen = htons(sizeof(TShutterMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TShutterMode tShutterMode;
    ZeroMemory(&tShutterMode, sizeof(TShutterMode));
    switch (emTwShutter)
    {
    case em_Shutter_25Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_25Spd = 1;
            break;
        }
    case em_Shutter_30Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_30Spd = 1;
            break;
        }
    case em_Shutter_50Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_50Spd = 1;
            break;
        }
    case em_Shutter_60Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_60Spd = 1;
            break;
        }
    case em_Shutter_100Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_100Spd = 1;
            break;
        }
    case em_Shutter_120Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_120Spd = 1;
            break;
        }
    case em_Shutter_150Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_150Spd = 1;
            break;
        }
    case em_Shutter_215Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_215Spd = 1;
            break;
        }
    case em_Shutter_300Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_300Spd = 1;
            break;
        }
    case em_Shutter_425Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_425Spd = 1;
            break;
        }
    case em_Shutter_600Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_600Spd = 1;
            break;
        }
    case em_Shutter_1000Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_1000Spd = 1;
            break;
        }
    case em_Shutter_1250Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_1250Spd = 1;
            break;
        }
    case em_Shutter_1750Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_1750Spd = 1;
            break;
        }
    case em_Shutter_2500Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_2500Spd = 1;
            break;
        }
    case em_Shutter_3500Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_3500Spd = 1;
            break;
        }
    case em_Shutter_6000Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_6000Spd = 1;
            break;
        }
    case em_Shutter_10000Spd:
        {
            tShutterMode.FiftyOrTwentyMode.Shutter_10000Spd = 1;
            break;
        }
    default:
        break;
    }

    rkmsg.CatBody(&tShutterMode, sizeof(TShutterMode));//添加消息体
    PrtRkcMsg( RK100_EVT_SET_CAM_SHUTTER, emEventTypeScoketSend, "EmTPFOrTwShutter:%d", emTwShutter);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

u16 CCamConfig::SetCamShutterCmd( const TShutterMode& tShutterMode )
{
	TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_SHUTTER);
    tRK100MsgHead.wMsgLen = htons(sizeof(TShutterMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tShutterMode, sizeof(TShutterMode));//添加消息体
    PrtRkcMsg( RK100_EVT_SET_CAM_SHUTTER, emEventTypeScoketSend, "SetCamShutterCmd");
    PrtRkcMsg( RK100_EVT_SET_CAM_SHUTTER, emEventTypeScoketRecv, "\n \
<[Sixty:%d, Thirty:%d], [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]>\n \
<[Fifty:%d, TenwFif:%d], [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]>",
tShutterMode.SixtyOrThirtyMode.SixtyFpsModeFlag, tShutterMode.SixtyOrThirtyMode.ThirtyFpsModeFlag, tShutterMode.SixtyOrThirtyMode.Shutter_30Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_50Sp, tShutterMode.SixtyOrThirtyMode.Shutter_60Sp, tShutterMode.SixtyOrThirtyMode.Shutter_90Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_100Sp, tShutterMode.SixtyOrThirtyMode.Shutter_125Sp, tShutterMode.SixtyOrThirtyMode.Shutter_180Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_250Sp,tShutterMode.SixtyOrThirtyMode.Shutter_350Sp, tShutterMode.SixtyOrThirtyMode.Shutter_500Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_725Sp,tShutterMode.SixtyOrThirtyMode.Shutter_1000Sp, tShutterMode.SixtyOrThirtyMode.Shutter_1500Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_2000Sp, tShutterMode.SixtyOrThirtyMode.Shutter_3000Sp, tShutterMode.SixtyOrThirtyMode.Shutter_4000Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_6000Sp, tShutterMode.SixtyOrThirtyMode.Shutter_10000Sp, tShutterMode.FiftyOrTwentyMode.FiftyFpsModeFlag,
tShutterMode.FiftyOrTwentyMode.TenwFifFpsModeFlag, tShutterMode.FiftyOrTwentyMode.Shutter_25Spd, tShutterMode.FiftyOrTwentyMode.Shutter_30Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_50Spd, tShutterMode.FiftyOrTwentyMode.Shutter_60Spd, tShutterMode.FiftyOrTwentyMode.Shutter_100Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_120Spd, tShutterMode.FiftyOrTwentyMode.Shutter_150Spd, tShutterMode.FiftyOrTwentyMode.Shutter_215Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_300Spd, tShutterMode.FiftyOrTwentyMode.Shutter_425Spd, tShutterMode.FiftyOrTwentyMode.Shutter_600Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_1000Spd, tShutterMode.FiftyOrTwentyMode.Shutter_1250Spd, tShutterMode.FiftyOrTwentyMode.Shutter_1750Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_2500Spd, tShutterMode.FiftyOrTwentyMode.Shutter_3500Spd, tShutterMode.FiftyOrTwentyMode.Shutter_6000Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_10000Spd);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

TPSOrThShutter CCamConfig::GetCamShutSpd()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	return m_pTPMoonCamCfg->ShutterMode.SixtyOrThirtyMode;
}

TPFOrTwShutter CCamConfig::GetTwCamShutSpd()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->ShutterMode.FiftyOrTwentyMode;
}

void CCamConfig::OnCamShutSpdCInd(const CMessage& cMsg)
{
	/*if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emSOrThShutSpd = *(EmTPSOrThShutter*)( cTpMsg.GetBody() );
	BOOL bCamShutSpdC = *(BOOL*)( cTpMsg.GetBody() +sizeof(u8) +sizeof(EmTPSOrThShutter) );
	PrtMsg( ev_TpCamExpSOrThShutter_Ind, emEventTypemoontoolRecv, "EmShutSpd:%d, BOOL:%d", m_pTPMoonCamCfg->emSOrThShutSpd, bCamShutSpdC );
	PostEvent( UI_MOONTOOL_CAMERA_SHUT_SPD_IND, NULL, (LPARAM)bCamShutSpdC );*/
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TShutterMode tShutterMode;
    ZeroMemory(&tShutterMode, sizeof(TShutterMode));
    if (tMsgHead.wMsgLen != 0)
    {
        tShutterMode = *reinterpret_cast<TShutterMode*>( cMsg.content + sizeof(TRK100MsgHead) );
    }

    if ( RK100_OPT_RTN_OK == tMsgHead.wOptRtn )
    {
        m_pTPMoonCamCfg->ShutterMode = tShutterMode ;
    }
    
    PrtRkcMsg( RK100_EVT_SET_CAM_SHUTTER_ACK, emEventTypeScoketRecv, "CamShutterRsp :%d", tMsgHead.wOptRtn);
    PrtRkcMsg( RK100_EVT_SET_CAM_SHUTTER_ACK, emEventTypeScoketRecv, "\n \
<[Sixty:%d, Thirty:%d], [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]>\n \
<[Fifty:%d, TenwFif:%d], [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]>",
tShutterMode.SixtyOrThirtyMode.SixtyFpsModeFlag, tShutterMode.SixtyOrThirtyMode.ThirtyFpsModeFlag, tShutterMode.SixtyOrThirtyMode.Shutter_30Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_50Sp, tShutterMode.SixtyOrThirtyMode.Shutter_60Sp, tShutterMode.SixtyOrThirtyMode.Shutter_90Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_100Sp, tShutterMode.SixtyOrThirtyMode.Shutter_125Sp, tShutterMode.SixtyOrThirtyMode.Shutter_180Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_250Sp,tShutterMode.SixtyOrThirtyMode.Shutter_350Sp, tShutterMode.SixtyOrThirtyMode.Shutter_500Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_725Sp,tShutterMode.SixtyOrThirtyMode.Shutter_1000Sp, tShutterMode.SixtyOrThirtyMode.Shutter_1500Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_2000Sp, tShutterMode.SixtyOrThirtyMode.Shutter_3000Sp, tShutterMode.SixtyOrThirtyMode.Shutter_4000Sp,
tShutterMode.SixtyOrThirtyMode.Shutter_6000Sp, tShutterMode.SixtyOrThirtyMode.Shutter_10000Sp, tShutterMode.FiftyOrTwentyMode.FiftyFpsModeFlag,
tShutterMode.FiftyOrTwentyMode.TenwFifFpsModeFlag, tShutterMode.FiftyOrTwentyMode.Shutter_25Spd, tShutterMode.FiftyOrTwentyMode.Shutter_30Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_50Spd, tShutterMode.FiftyOrTwentyMode.Shutter_60Spd, tShutterMode.FiftyOrTwentyMode.Shutter_100Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_120Spd, tShutterMode.FiftyOrTwentyMode.Shutter_150Spd, tShutterMode.FiftyOrTwentyMode.Shutter_215Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_300Spd, tShutterMode.FiftyOrTwentyMode.Shutter_425Spd, tShutterMode.FiftyOrTwentyMode.Shutter_600Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_1000Spd, tShutterMode.FiftyOrTwentyMode.Shutter_1250Spd, tShutterMode.FiftyOrTwentyMode.Shutter_1750Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_2500Spd, tShutterMode.FiftyOrTwentyMode.Shutter_3500Spd, tShutterMode.FiftyOrTwentyMode.Shutter_6000Spd,
tShutterMode.FiftyOrTwentyMode.Shutter_10000Spd);
    PostEvent( UI_MOONTOOL_CAMERA_SHUT_SPD_IND, NULL, (LPARAM)tMsgHead.wOptRtn );
}

void CCamConfig::OnCamTwShutSpdCInd( const CMessage& cMsg )
{
	/*if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emFOrTwShutSpd = *(EmTPFOrTwShutter*)( cTpMsg.GetBody() );
	BOOL bCamShutSpdC = *(BOOL*)( cTpMsg.GetBody() +sizeof(u8) +sizeof(EmTPFOrTwShutter) );
	PrtMsg( ev_TpCamExpFOrTwShutter_Ind, emEventTypemoontoolRecv, "EmShutSpd:%d, BOOL:%d", m_pTPMoonCamCfg->emFOrTwShutSpd, bCamShutSpdC );
	PostEvent( UI_MOONTOOL_CAMERA_SHUT_SPD_IND, NULL, (LPARAM)bCamShutSpdC );*/	
}

//增益
u16 CCamConfig::CamGainCmd( const EmTPExpGain& emExpGain )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emExpGain, sizeof(EmTPExpGain) );
	pcTpMsg->SetEvent(ev_TpCamExpGain_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamExpGain_Cmd, emEventTypemoontoolSend, "CamGainCmd:%d", emExpGain );
	return wRet;*/
	return true;
}

u16 CCamConfig::SetCamGainCmd( const TGainMode& tGainMode )
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_GAIN);
    tRK100MsgHead.wMsgLen = htons(sizeof(TGainMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tGainMode, sizeof(TGainMode));//添加消息体
    PrtRkcMsg( RK100_EVT_SET_CAM_GAIN, emEventTypeScoketSend, "Up:%d,Down:%d,GainInputVal:%d",
        tGainMode.CAMGainCmdUpFlag, tGainMode.CAMGainCmdDownFlag, tGainMode.GainInputVal);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

EmTPExpGain CCamConfig::GetCamGain()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
    EmTPExpGain tt = em_Gain_Nega10_5dB;
	return tt;
}

void CCamConfig::OnCamGainInd(const CMessage& cMsg)
{
	/*if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emGain = *(EmTPExpGain*)( cTpMsg.GetBody() );
	BOOL bCamGain = *(BOOL*)( cTpMsg.GetBody() +sizeof(u8) +sizeof(EmTPExpGain) );
	PrtMsg( ev_TpCamExpGain_Ind, emEventTypemoontoolRecv, "EmShutSpd:%d, BOOL:%d", m_pTPMoonCamCfg->emGain, bCamGain );
	PostEvent( UI_MOONTOOL_CAMERA_GAIN_IND, NULL, (LPARAM)bCamGain );*/
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TGainMode tCainMode;
    ZeroMemory(&tCainMode, sizeof(TGainMode));
    if (tMsgHead.wMsgLen != 0)
    {
        tCainMode = *reinterpret_cast<TGainMode*>( cMsg.content + sizeof(TRK100MsgHead) );
    }

    if ( RK100_OPT_RTN_OK == tMsgHead.wOptRtn )
    {
        m_pTPMoonCamCfg->GainMode.GainInputVal = tCainMode.GainInputVal;
    }
    
    PrtRkcMsg( RK100_EVT_SET_CAM_GAIN_ACK, emEventTypeScoketRecv, "wRtn:%d, GainVal:%d", tMsgHead.wOptRtn, tCainMode.GainInputVal);
    PostEvent( UI_MOONTOOL_CAMERA_GAIN_IND, (WPARAM)tCainMode.GainInputVal, (LPARAM)tMsgHead.wOptRtn );
}

// 白平衡
u16 CCamConfig::CamAutoWBCmd( const TCamWBMode& tCamWBMode )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emWBMode, sizeof(EmTPMOOMMode) );
	pcTpMsg->SetEvent(ev_TpCamWhiteBalanceMode_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamWhiteBalanceMode_Cmd, emEventTypemoontoolSend, "CamAutoWBCmd:%d", emWBMode );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_WB);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamWBMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tCamWBMode, sizeof(TCamWBMode));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_WB, emEventTypeScoketSend, "AutoMode:%d,ManuMode:%d,RGain:%d,BGain:%d",
        tCamWBMode.CamWBAutoModeFlag, tCamWBMode.CamWBManuModeFlag, tCamWBMode.RGainVal, tCamWBMode.BGainVal);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

EmTPMOOMMode CCamConfig::GetCamWBMode()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
    EmTPMOOMMode emWBMode = emAuto;
    if (m_pTPMoonCamCfg->WBMode.CamWBManuModeFlag)
    {
        emWBMode = emManual;
    }
	return emWBMode;
}

void CCamConfig::OnCamAutoWBInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emWBMode = *(EmTPMOOMMode*)( cTpMsg.GetBody() );
	BOOL bCamAutoWB = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(EmTPMOOMMode) );
	
	PrtMsg( ev_TpCamWhiteBalanceMode_Ind, emEventTypemoontoolRecv, "EmWBMode:%d, CamAutoWBInd:%d", m_pTPMoonCamCfg->emWBMode, bCamAutoWB );
	PostEvent( UI_MOONTOOL_CAMERA_AUTO_WB_IND, NULL, (LPARAM)bCamAutoWB );*/
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TCamWBMode tCamWBMode;
    ZeroMemory(&tCamWBMode, sizeof(TCamWBMode));
    if (tMsgHead.wMsgLen != 0)
    {
        tCamWBMode = *reinterpret_cast<TCamWBMode*>( cMsg.content + sizeof(TRK100MsgHead) );
    }
    
    if ( tMsgHead.wOptRtn == RK100_OPT_RTN_OK )
    {
        m_pTPMoonCamCfg->WBMode = tCamWBMode;
    }
    
    PrtRkcMsg( RK100_EVT_SET_CAM_WB_ACK, emEventTypeScoketRecv, "wRtn:%d,[AutoMode:%d,ManuMode:%d,RGain:%d,BGain:%d]",
        tMsgHead.wOptRtn, tCamWBMode.CamWBAutoModeFlag, tCamWBMode.CamWBManuModeFlag, tCamWBMode.RGainVal, tCamWBMode.BGainVal);
    PostEvent( UI_MOONTOOL_CAMERA_AUTO_WB_IND, NULL, (LPARAM)tMsgHead.wOptRtn );
}

u16 CCamConfig::CamRGainCmd( const u32& dwRGain )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&dwRGain, sizeof(u32));
	pcTpMsg->SetEvent(ev_TpCamWhiteBalanceRGain_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamWhiteBalanceRGain_Cmd, emEventTypemoontoolSend, "dwRGain:%d", dwRGain );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_WB);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamWBMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TCamWBMode tCamWBMode;
    ZeroMemory(&tCamWBMode, sizeof(TCamWBMode));
    tCamWBMode.CamWBManuModeFlag = 1;
    tCamWBMode.RGainVal = dwRGain;
    tCamWBMode.BGainVal = GetCamBGain();
    rkmsg.CatBody(&tCamWBMode, sizeof(TCamWBMode));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_WB, emEventTypeScoketSend, "AutoMode:%d,ManuMode:%d,RGain:%d,BGain:%d",
        tCamWBMode.CamWBAutoModeFlag, tCamWBMode.CamWBManuModeFlag, tCamWBMode.RGainVal, tCamWBMode.BGainVal);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

u32 CCamConfig::GetCamRGain()
{
	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	return m_pTPMoonCamCfg->WBMode.RGainVal;
}

void CCamConfig::OnCamRGainInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	m_pTPMoonCamCfg->dwRGain = *(u32*)( cTpMsg.GetBody() );
	BOOL bCamRGain = *(BOOL*)( cTpMsg.GetBody() + sizeof(u32) +sizeof(u8) );

	PrtMsg( ev_TpCamWhiteBalanceRGain_Ind, emEventTypemoontoolRecv, "dwRGain:%d, bCamRGain:%d", m_pTPMoonCamCfg->dwRGain, bCamRGain );
	PostEvent( UI_MOONTOOL_CAMERA_RGAIN_IND, NULL, (LPARAM)bCamRGain );*/
}

u16 CCamConfig::CamAdjustRangeCmd( const u32& dwAdjustRange )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	TTPDistortParam tTPDistortParam;
	tTPDistortParam.dwCorrectLevel = dwAdjustRange;
	tTPDistortParam.dwEnable = 1;

	pcTpMsg->SetBody(&tTPDistortParam, sizeof(TTPDistortParam));
	pcTpMsg->SetEvent(ev_TpImageDistortCorrect_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpImageDistortCorrect_Cmd, emEventTypemoontoolSend, "dwAdjustRange:%d", dwAdjustRange );
	return wRet;*/
	return true;
}

u16 CCamConfig::CamHoriStretchCmd( const u32& dwHoriStretch )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	TTPDistortParam tTPDistortParam;
	tTPDistortParam.dwStretchRegion = dwHoriStretch;
	
	pcTpMsg->SetBody(&tTPDistortParam, sizeof(TTPDistortParam));
	pcTpMsg->SetEvent(ev_TpImageDistortCorrect_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpImageDistortCorrect_Cmd, emEventTypemoontoolSend, "dwHoriStretch:%d", dwHoriStretch );
	return wRet;*/
	return true;
}

u16 CCamConfig::CamBGainCmd( const u32& dwBGain )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&dwBGain, sizeof(u32));
	pcTpMsg->SetEvent(ev_TpCamWhiteBalanceBGain_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamWhiteBalanceBGain_Cmd, emEventTypemoontoolSend, "dwBGain:%d", dwBGain );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_WB);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamWBMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    
    TCamWBMode tCamWBMode;
    ZeroMemory(&tCamWBMode, sizeof(TCamWBMode));
    tCamWBMode.CamWBManuModeFlag = 1;
    tCamWBMode.BGainVal = dwBGain;
    tCamWBMode.RGainVal = GetCamRGain();
    rkmsg.CatBody(&tCamWBMode, sizeof(TCamWBMode));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_WB, emEventTypeScoketSend, "AutoMode:%d,ManuMode:%d,RGain:%d,BGain:%d",
        tCamWBMode.CamWBAutoModeFlag, tCamWBMode.CamWBManuModeFlag, tCamWBMode.RGainVal, tCamWBMode.BGainVal);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

u32 CCamConfig::GetCamBGain()
{
	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->WBMode.BGainVal;
}

u32 CCamConfig::GetCamAdjustRange()
{
	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
    u32 tt = 0;
	return tt;
}

u32 CCamConfig::GetCamHoriStretch()
{
	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
    u32 tt = 0;
	return tt;
}

void CCamConfig::OnCamBGainInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->dwBGain = *(u32*)( cTpMsg.GetBody() );
	BOOL bCamBGain = *(BOOL*)( cTpMsg.GetBody() + sizeof(u32) +sizeof(u8) );

	PrtMsg( ev_TpCamWhiteBalanceBGain_Ind, emEventTypemoontoolRecv, "dwBGain:%d, bCamBGain:%d", m_pTPMoonCamCfg->dwBGain, bCamBGain );
	PostEvent( UI_MOONTOOL_CAMERA_BGAIN_IND, NULL, (LPARAM)bCamBGain );*/
}

// 图片参数
u16 CCamConfig::CamImageParaCmd( EmTPImagePara emImagePara, const u32& dwImagePara )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&emImagePara, sizeof(EmTPImagePara));
	pcTpMsg->CatBody(&dwImagePara, sizeof(u32));
	pcTpMsg->SetEvent(ev_TpCamImagePara_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamImagePara_Cmd, emEventTypemoontoolSend, "emImagePara:%d, dwImagePara:%d", emImagePara, dwImagePara );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_ImagParam);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamImagParam));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TCamImagParam tCamImgParam;
    ZeroMemory(&tCamImgParam, sizeof(TCamImagParam));
    tCamImgParam = GetCamImagParam();
    
    if ( emImagePara == emBlight )
    {
        tCamImgParam.BrightVal = dwImagePara;
    }
    else if ( emImagePara == emHue )
    {
        tCamImgParam.ColorHueVal = dwImagePara;
    }
    else if ( emImagePara == emSaturat )
    {
        tCamImgParam.ColorGainVal = dwImagePara;
    }
    else if ( emImagePara == emGama )
    {
        //Gamma 调节需清空原有配置
        tCamImgParam.Gamma_opt_1_flag = 0;
        tCamImgParam.Gamma_opt_2_flag = 0;
        tCamImgParam.Gamma_opt_3_flag  =0;

        if ( dwImagePara == emGamma1 )
        {
            tCamImgParam.Gamma_opt_1_flag = 1;
        }
        else if ( dwImagePara == emGamma2 )
        {
            tCamImgParam.Gamma_opt_2_flag = 1;
        }
        else if ( dwImagePara == emGamma3 )
        {
            tCamImgParam.Gamma_opt_3_flag = 1;
        }
    }
    else
    {
        //
    }

    rkmsg.CatBody(&tCamImgParam, sizeof(TCamImagParam));//添加消息体
    PrtRkcMsg( RK100_EVT_SET_CAM_ImagParam, emEventTypeScoketSend, "emImagePara:%d, tCamImgParam:[Bright:%d,Hue:%d,saturation:%d], Gamma:[%d,%d,%d]",
        emImagePara, tCamImgParam.BrightVal, tCamImgParam.ColorHueVal, tCamImgParam.ColorGainVal,
        tCamImgParam.Gamma_opt_1_flag, tCamImgParam.Gamma_opt_2_flag, tCamImgParam.Gamma_opt_3_flag);

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}
// 所有图像参数
u16 CCamConfig::CamImageParaCmd( TCamImagParam &tCamImagParam )
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_ImagParam);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamImagParam));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tCamImagParam, sizeof(TCamImagParam));//添加消息体
    PrtRkcMsg( RK100_EVT_SET_CAM_ImagParam, emEventTypeScoketSend, "tCamImgParam:[Bright:%d,Hue:%d,saturation:%d], Gamma:[%d,%d,%d]",
        tCamImagParam.BrightVal, tCamImagParam.ColorHueVal, tCamImagParam.ColorGainVal,
        tCamImagParam.Gamma_opt_1_flag, tCamImagParam.Gamma_opt_2_flag, tCamImagParam.Gamma_opt_3_flag);

    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnCamImageParaInd(const CMessage& cMsg)
{
	//if ( m_pTPMoonCamCfg == NULL )
	//{
	//	SetCameraCfgPtr();
	//}
	//
	//CTpMsg cTpMsg(&cMsg);
	//
	//EmTPImagePara emTPImagePara = *(EmTPImagePara*)( cTpMsg.GetBody() );
	////值是否要设置到具体的摄像机
	//u32 dwValue = *(u32*)( cTpMsg.GetBody() + sizeof(EmTPImagePara) );
	//switch ( emTPImagePara )
	//{
	//case emBlight:
	//	{
	//		m_pTPMoonCamCfg->dwBright = dwValue;
	//		PostEvent( UI_MOONTOOL_IMAGE_BLIGHT_IND, 0, (LPARAM)(m_pTPMoonCamCfg->dwBright) );
	//		break;
	//	}
	//case emContrast:
	//	{
	//		m_pTPMoonCamCfg->dwContrast = dwValue;
	//		PostEvent( UI_MOONTOOL_IMAGE_CONTRAST_IND, 0, (LPARAM)(m_pTPMoonCamCfg->dwContrast) );
	//		break;
	//	}
	//case emSharp:
	//	{
	//		m_pTPMoonCamCfg->dwSharp = dwValue;
	//		PostEvent( UI_MOONTOOL_IMAGE_Sharp_IND, 0, (LPARAM)(m_pTPMoonCamCfg->dwSharp) );
	//		break;
	//	}
	//case emSaturat:
	//	{
	//		m_pTPMoonCamCfg->dwSaturat = dwValue;
	//		PostEvent( UI_MOONTOOL_IMAGE_SATURAT_IND, 0, (LPARAM)(m_pTPMoonCamCfg->dwSaturat) );
	//		break;
	//	}
	//default:
	//	break;
	//}

	//
	//BOOL bCamImagePara = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTPImagePara) + sizeof(u32) + sizeof(u8) );
	//PrtMsg( ev_TpCamImagePara_Ind, emEventTypemoontoolRecv, "bCamImagePara:%d", bCamImagePara);
	//PostEvent( UI_MOONTOOL_IMAGEPARA_IND, (WPARAM)emTPImagePara, (LPARAM)bCamImagePara );
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TCamImagParam tCamImagParam;
    ZeroMemory(&tCamImagParam, sizeof(TCamImagParam));
    if (tMsgHead.wMsgLen != 0)
    {
        tCamImagParam = *reinterpret_cast<TCamImagParam*>( cMsg.content + sizeof(TRK100MsgHead) );
    }

    if ( RK100_OPT_RTN_OK == tMsgHead.wOptRtn )
    {
        m_pTPMoonCamCfg->CamImagParam = tCamImagParam;
    }
    
    PrtRkcMsg( RK100_EVT_SET_CAM_ImagParam_ACK, emEventTypeScoketRecv, "wRtn:%d", tMsgHead.wOptRtn);
    PostEvent( UI_MOONTOOL_IMAGEPARA_IND, (WPARAM)NULL, (LPARAM)tMsgHead.wOptRtn );
}

TCamImagParam CCamConfig::GetCamImagParam()
{
    if (m_pTPMoonCamCfg == NULL)
    {
        SetCameraCfgPtr();
	}

    return m_pTPMoonCamCfg->CamImagParam;
}

//背光补偿
u16 CCamConfig::CamLightPensation( BOOL bIsOpen)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bIsOpen, sizeof(BOOL));
	pcTpMsg->SetEvent(ev_TpCamBackLight_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamBackLight_Cmd, emEventTypemoontoolSend, "bIsOpen:%d", bIsOpen );
	return wRet;*/
	return true;
}

//梯形校正
u16 CCamConfig::CamKeystoneAdjust(const TTPDistortParam& tTPDistortParam ,EmTPCorrect emMyOption )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&tTPDistortParam, sizeof(TTPDistortParam));
	pcTpMsg->CatBody(&emMyOption, sizeof(EmTPCorrect));
	pcTpMsg->SetEvent(ev_TpImageDistortCorrect_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpImageDistortCorrect_Cmd, emEventTypemoontoolSend, "Correction Value %d ; Tensile value %d ; \
MyOpetion:%d <em_HorizonCorrect:%d ; em_HorizonStretch:%d ; em_VerticalCorrect:%d ; em_VerticalStretch:%d > ",
tTPDistortParam.dwCorrectLevel,tTPDistortParam.dwStretchRegion,emMyOption,em_HorizonCorrect,em_HorizonStretch,em_VerticalCorrect,em_VerticalStretch);
	return wRet;*/
	return true;
}

u16 CCamConfig::SetCorConsistRGBCmd(u8 nPosition, EmTPColorConsistency emMyCorConsOption, EmTPCorrectChange emChangeOption)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&nPosition, sizeof(u8));
	pcTpMsg->CatBody(&emMyCorConsOption, sizeof(EmTPColorConsistency));
	pcTpMsg->CatBody(&emChangeOption, sizeof(EmTPCorrectChange));
	pcTpMsg->SetEvent( ev_TPSetColorRGB_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPSetColorRGB_Cmd, emEventTypemoontoolSend, "nPositon:%d, emMyCorConsOption: %d, emChangeOption:%d", nPosition, emMyCorConsOption, emChangeOption );
	
	return wRet;*/
	return true;
}

u16 CCamConfig::SetChangeDistortCmd(u8 byIndex, EmTPCorrectChange emTPCorrectChange, EmTPDistortPosition emTPDistortPosition)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&byIndex, sizeof(u8));	
	pcTpMsg->CatBody(&emTPDistortPosition, sizeof(EmTPDistortPosition));
	pcTpMsg->CatBody(&emTPCorrectChange, sizeof(EmTPCorrectChange));	
	pcTpMsg->SetEvent( ev_TPChangeDistor_Cmd );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPChangeDistor_Cmd, emEventTypemoontoolSend, "byIndex:%d, emTPDistortPosition: %d, emTPCorrectChange:%d", byIndex, emTPDistortPosition, emTPCorrectChange );

	return wRet;*/
	return true;
}

u16 CCamConfig::SetDirectDistortCmd( const TTPDistortInfo&tTpDistortInfo )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&tTpDistortInfo, sizeof(TTPDistortInfo));
	pcTpMsg->SetEvent( ev_TPDirectSetDistor_Cmd );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPChangeDistor_Cmd, emEventTypemoontoolSend, "byIndex: %d, emDistortType: %d, dwValue: %d", tTpDistortInfo.byIndex, tTpDistortInfo.emDistortType, tTpDistortInfo.dwValue );

	return wRet;*/
	return true;
}

u16 CCamConfig::SetAutoSetColorConstancyCmd()
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetEvent( ev_TPAutoSetColorConstancy_Cmd );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPAutoSetColorConstancy_Cmd, emEventTypemoontoolSend, "" );

	return wRet;*/
	return true;
}

u16 CCamConfig::SetChooseRectangleCmd(const TTPMoonRectRegion& tTPMoonRectRegion)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&tTPMoonRectRegion, sizeof(TTPMoonRectRegion));
	pcTpMsg->SetEvent(ev_TPChooseRectangle_Cmd);

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPChooseRectangle_Cmd, emEventTypemoontoolSend, "byIndex: %d, dwXCoordinate: %d, dwYCoordinate: %d, dwLenth: %d, dwWidth: %d",
		tTPMoonRectRegion.byIndex, tTPMoonRectRegion.dwXCoordinate, tTPMoonRectRegion.dwYCoordinate, tTPMoonRectRegion.dwLenth, tTPMoonRectRegion.dwWidth );
	return wRet;*/
	return true;
}

void CCamConfig::OnChooseRectangleInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	TTPMoonRectRegion tTPMoonRectRegion = *(TTPMoonRectRegion*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPMoonRectRegion));

	PrtMsg( ev_TPChooseRectangle_Ind, emEventTypemoontoolRecv, "byIndex: %d, dwXCoordinate: %d, dwYCoordinate: %d, dwLenth: %d, dwWidth: %d, bOk: %d",
		tTPMoonRectRegion.byIndex, tTPMoonRectRegion.dwXCoordinate, tTPMoonRectRegion.dwYCoordinate, tTPMoonRectRegion.dwLenth, tTPMoonRectRegion.dwWidth, bOk );

	PostEvent( UI_CHOOSERECTANGLE_IND, (WPARAM)&tTPMoonRectRegion, (LPARAM)&bOk );*/
}

void CCamConfig::OnSetColorRGBInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	u8 nPosition = *(u8*)(cTpMsg.GetBody());
	EmTPColorConsistency emMyColorOption = *(EmTPColorConsistency*)(cTpMsg.GetBody()+sizeof(u8));
	u32 dwRGBDirectVal = *(u32*)(cTpMsg.GetBody()+sizeof(u8)+sizeof(EmTPColorConsistency));
	BOOL bSuccess = *(BOOL *)(cTpMsg.GetBody()+sizeof(u8)+sizeof(EmTPColorConsistency)+sizeof(u32));

	TTPColorRGBCoeff tTPColorRGBCoeff;
	tTPColorRGBCoeff.byIndex = nPosition;
	tTPColorRGBCoeff.emColorType = emMyColorOption;
	tTPColorRGBCoeff.dwValue = dwRGBDirectVal;
	
	PrtMsg( ev_TPSetColorRGB_Ind, emEventTypemoontoolRecv, "nPosition: %d, emMyColorOption: %d, dwRGBDirectVal: %d, bSuccess: %d",
		nPosition, emMyColorOption, dwRGBDirectVal, bSuccess);
	
	PostEvent(UI_SETCOLORRGB_IND, (WPARAM)&tTPColorRGBCoeff, (LPARAM)&bSuccess);*/
		
}

void CCamConfig::OnSetAutoColorConstancyInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);

	u32 dwRGBColorValue[MOON_COLOR_COEFF_NUM];

	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody() + sizeof(u32) * MOON_COLOR_COEFF_NUM );
	for( int i=0; i<MOON_COLOR_COEFF_NUM; i++ )
	{
		dwRGBColorValue[i] = *(u32*)( cTpMsg.GetBody() + sizeof(u32)*i);
	}

	PrtMsg( ev_TPAutoSetColorConstancy_Ind, emEventTypemoontoolRecv, "dwRGBColorValue1: %d, dwRGBColorValue2: %d, dwRGBColorValue3: %d, dwRGBColorValue4: %d,\
         dwRGBColorValue5: %d, dwRGBColorValue6: %d, dwRGBColorValue7: %d, dwRGBColorValue8: %d, dwRGBColorValue9: %d, bSuccess : %d", dwRGBColorValue[0], dwRGBColorValue[1], dwRGBColorValue[2],
				  dwRGBColorValue[3], dwRGBColorValue[4], dwRGBColorValue[5], dwRGBColorValue[6], dwRGBColorValue[7], dwRGBColorValue[8], bSuccess );

	PostEvent( UI_AUTOSETCOLORCONSTANCY_IND, (WPARAM)&bSuccess, (LPARAM)&dwRGBColorValue );*/

}

void CCamConfig::OnChangeSideRGBNty(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);

	u32 dwSideColorVal[2];
	EmTPColorConsistency emMyColorOption = *(EmTPColorConsistency*)(cTpMsg.GetBody());
	dwSideColorVal[0] = *(u32*)(cTpMsg.GetBody()+sizeof(EmTPColorConsistency));
	dwSideColorVal[1] = *(u32*)(cTpMsg.GetBody()+sizeof(EmTPColorConsistency)+sizeof(u32));

	PrtMsg(ev_TPChangeSideRGB_Nty, emEventTypemoontoolRecv, "emMyColorOption: %d, dwSideColorVal[0]: %d, dwSideColorVal[1]: %d", emMyColorOption, dwSideColorVal[0], dwSideColorVal[1]);

	PostEvent(UI_CHANGESIDERGB_NTY, (WPARAM)&emMyColorOption, (LPARAM)&dwSideColorVal);*/

}

u16 CCamConfig::SetColorRGBDirectCmd(u8 nPosition, EmTPColorConsistency emMyCorConsOption, const u32& dwRGBDirectValue)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&nPosition, sizeof(u8));
	pcTpMsg->CatBody(&emMyCorConsOption, sizeof(EmTPColorConsistency));
	pcTpMsg->CatBody(&dwRGBDirectValue, sizeof(u32));
	pcTpMsg->SetEvent(ev_TPDirectSetColorRGB_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg(ev_TPDirectSetColorRGB_Cmd, emEventTypemoontoolSend, "nPosition:%d, emMyCorConsOption: %d, emMyCorConsOption: %d", nPosition, emMyCorConsOption, emMyCorConsOption);
	
	return wRet;*/
	return true;
}

void CCamConfig::OnSetColorRGBDirectInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	u8 nPosition = *(u8*)(cTpMsg.GetBody());
	EmTPColorConsistency emMyColorOption = *(EmTPColorConsistency*)(cTpMsg.GetBody()+sizeof(u8));
	u32 dwRGBDirectVal = *(u32*)(cTpMsg.GetBody()+sizeof(u8)+sizeof(EmTPColorConsistency));
	BOOL bSuccess = *(BOOL *)(cTpMsg.GetBody()+sizeof(u8)+sizeof(EmTPColorConsistency)+sizeof(u32));

	TTPColorRGBCoeff tTPColorRGBCoeff;
	tTPColorRGBCoeff.byIndex = nPosition;
	tTPColorRGBCoeff.emColorType = emMyColorOption;
	tTPColorRGBCoeff.dwValue = dwRGBDirectVal;
    
	PrtMsg(ev_TPDirectSetColorRGB_Ind, emEventTypemoontoolRecv, "nPosition: %d, emMyColorOption: %d, dwRGBDirectVal: %d, bSuccess: %d",
		nPosition, emMyColorOption, dwRGBDirectVal, bSuccess);

	PostEvent(UI_DIRECT_SETCOLORRGB_IND, (WPARAM)&tTPColorRGBCoeff, (LPARAM)&bSuccess);*/
}

void CCamConfig::OnCamDistortAdjustInd( const CMessage& cMsg )
{
//	if ( m_pTPMoonCamCfg == NULL )
//	{
//		SetCameraCfgPtr();
//	}
//	
//	CTpMsg cTpMsg(&cMsg);
//	TTPDistortParam tDistortParam = *(TTPDistortParam*)( cTpMsg.GetBody());
//	EmTPCorrect emMyOption = *(EmTPCorrect*)(cTpMsg.GetBody()+sizeof(TTPDistortParam));
//	BOOL bSuccess = *(BOOL *)(cTpMsg.GetBody()+sizeof(TTPDistortParam)+sizeof(EmTPCorrect)+sizeof(u8));
//	if ( bSuccess == TRUE )
//	{
//		if (( emMyOption == em_HorizonCorrect) || ( emMyOption == em_HorizonStretch ))
//		{
//			m_pTPMoonCamCfg->dwHorizonCorrect = tDistortParam.dwCorrectLevel;
//			m_pTPMoonCamCfg->dwHorizonStretch = tDistortParam.dwStretchRegion;
//		}
//		else
//		{
//			m_pTPMoonCamCfg->dwVerticalCorrect = tDistortParam.dwCorrectLevel;
//			m_pTPMoonCamCfg->dwVerticalStretch = tDistortParam.dwStretchRegion;
//		}
//	}
//
////	m_pTPMoonCamCfg->bIsCorrect = tDistortParam.dwEnable;
//	
//	PrtMsg( ev_TpImageDistortCorrect_Ind, emEventTypemoontoolRecv, "Success %d ; Correction Value %d ; Tensile value %d ;MyOpetion:%d <em_HorizonCorrect:%d ; em_HorizonStretch:%d ;\
//		em_VerticalCorrect:%d ; em_VerticalStretch:%d > ",bSuccess,tDistortParam.dwCorrectLevel,tDistortParam.dwStretchRegion,
//		emMyOption,em_HorizonCorrect,em_HorizonStretch,em_VerticalCorrect,em_VerticalStretch );
//	PostEvent( UI_MOONTOOL_CAMERA_DISTORTPARAM_IND, (WPARAM)(&emMyOption), (LPARAM)&bSuccess );	
}


void CCamConfig::OnCamLightPensationInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	m_pTPMoonCamCfg->bIsBLCSwitch = *(BOOL*)( cTpMsg.GetBody());
	BOOL bIsOk = *(BOOL*)( cTpMsg.GetBody() +sizeof(BOOL) +sizeof(u8) );
	PrtMsg( ev_TpCamBackLight_Ind, emEventTypemoontoolRecv, "bIsOpen:%d", m_pTPMoonCamCfg->bIsBLCSwitch );
	PostEvent( UI_MOONTOOL_CAMERA_BACKLIGHT_IND, (WPARAM)(m_pTPMoonCamCfg->bIsBLCSwitch), (LPARAM)bIsOk );*/
}

//降噪
u16 CCamConfig::CamNRCmd( BOOL bIsOpen, EmTPFpgaReduNoise emTPReduNoise )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bIsOpen, sizeof(BOOL));
	pcTpMsg->CatBody(&emTPReduNoise, sizeof(EmTPFpgaReduNoise));
	pcTpMsg->SetEvent(ev_TpCamReduNoise_Cmd);

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamReduNoise_Cmd, emEventTypemoontoolSend, "bIsOpen:%d, emTPReduNoise:%d", bIsOpen, emTPReduNoise );
	return wRet;*/
	return true;
}

u16 CCamConfig::Cam2DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bIsOpen, sizeof(BOOL));
	pcTpMsg->CatBody(&emTPReduNoise, sizeof(EmTPReduNoise));
	pcTpMsg->SetEvent(ev_TpSetCam2DNoiseLevle_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpSetCam2DNoiseLevle_Cmd, emEventTypemoontoolSend, "bIsOpen:%d, emTPReduNoise:%d", bIsOpen, emTPReduNoise );
	return wRet;*/

    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_D2NR);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamD2NRMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容

    TCamD2NRMode tCamNRMode;
    ZeroMemory(&tCamNRMode, sizeof(TCamD2NRMode));
    if (bIsOpen)
    {
        tCamNRMode.D2NROnFlag = 1;
    }
    else
    {
        tCamNRMode.D2NROffFlag = 1;
    }

    switch (emTPReduNoise)
    {
    case emLevelFist:
        {
            tCamNRMode.D2NR_level_1_Flag = 1;
            break;
        }
    case emLevelSecond:
        {
            tCamNRMode.D2NR_level_2_Flag = 1;
            break;
        }
    case emLevelThird:
        {
            tCamNRMode.D2NR_level_3_Flag = 1;
            break;
        }
    case emLevelFourth:
        {
            tCamNRMode.D2NR_level_4_Flag = 1;
            break;
        }
    case emLeVelFifth:
        {
            tCamNRMode.D2NR_level_5_Flag = 1;
            break;
        }
    default:
        {
            break;
        }
    }

    rkmsg.CatBody(&tCamNRMode, sizeof(TCamD2NRMode));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_D2NR, emEventTypeScoketSend, "bIsOpen:%d, emTPReduNoise:%d", bIsOpen, emTPReduNoise);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

u16 CCamConfig::Cam2DNRCmd( TCamD2NRMode &tCamD2NRMode )
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_D2NR);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamD2NRMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tCamD2NRMode, sizeof(TCamD2NRMode));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_D2NR, emEventTypeScoketSend, "tCamD2NRMode:[On:%d,Off:%d,Level<%d,%d,%d,%d,%d>]",
        tCamD2NRMode.D2NROnFlag, tCamD2NRMode.D2NROffFlag, tCamD2NRMode.D2NR_level_1_Flag, tCamD2NRMode.D2NR_level_2_Flag,
        tCamD2NRMode.D2NR_level_3_Flag, tCamD2NRMode.D2NR_level_4_Flag, tCamD2NRMode.D2NR_level_5_Flag);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

u16 CCamConfig::Cam3DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bIsOpen, sizeof(BOOL));
	pcTpMsg->CatBody(&emTPReduNoise, sizeof(EmTPReduNoise));
	pcTpMsg->SetEvent(ev_TpSetCam3DNoiseLevle_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpSetCam3DNoiseLevle_Cmd, emEventTypemoontoolSend, "bIsOpen:%d, emTPReduNoise:%d", bIsOpen, emTPReduNoise );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_D3NR);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamD3NRMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    
    TCamD3NRMode tCamNRMode;
    ZeroMemory(&tCamNRMode, sizeof(TCamD3NRMode));
    if (bIsOpen)
    {
        tCamNRMode.D3NROnFlag = 1;
    }
    else
    {
        tCamNRMode.D3NROffFlag = 1;
    }

    switch (emTPReduNoise)
    {
    case emLevelFist:
        {
            tCamNRMode.D3NR_level_1_Flag = 1;
            break;
        }
    case emLevelSecond:
        {
            tCamNRMode.D3NR_level_2_Flag = 1;
            break;
        }
    case emLevelThird:
        {
            tCamNRMode.D3NR_level_3_Flag = 1;
            break;
        }
    case emLevelFourth:
        {
            tCamNRMode.D3NR_level_4_Flag = 1;
            break;
        }
    case emLeVelFifth:
        {
            tCamNRMode.D3NR_level_5_Flag = 1;
            break;
        }
    default:
        {
            break;
        }
    }
    
    rkmsg.CatBody(&tCamNRMode, sizeof(TCamD3NRMode));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_D3NR, emEventTypeScoketSend, "bIsOpen:%d, emTPReduNoise:%d", bIsOpen, emTPReduNoise);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

u16 CCamConfig::Cam3DNRCmd( TCamD3NRMode &tCamD3NRMode )
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_D3NR);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamD3NRMode));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tCamD3NRMode, sizeof(TCamD3NRMode));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_D3NR, emEventTypeScoketSend, "tCamD3NRMode:[On:%d,Off:%d,Level<%d,%d,%d,%d,%d>]",
        tCamD3NRMode.D3NROnFlag, tCamD3NRMode.D3NROffFlag, tCamD3NRMode.D3NR_level_1_Flag, tCamD3NRMode.D3NR_level_2_Flag,
        tCamD3NRMode.D3NR_level_3_Flag, tCamD3NRMode.D3NR_level_4_Flag, tCamD3NRMode.D3NR_level_5_Flag);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnCamNRInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);
	BOOL bIsOpen = *(BOOL*)( cTpMsg.GetBody());
	m_pTPMoonCamCfg->emReduNoise = *(EmTPFpgaReduNoise*)(cTpMsg.GetBody()+ sizeof(BOOL));

	PrtMsg( ev_TpCamReduNoise_Ind, emEventTypemoontoolRecv, "bIsOpen:%d emTPReduNoise:%d", bIsOpen, m_pTPMoonCamCfg->emReduNoise );
	PostEvent( UI_MOONTOOL_CAMERA_NR_IND, (WPARAM)(m_pTPMoonCamCfg->emReduNoise), (LPARAM)bIsOpen );*/
}

void CCamConfig::OnCam2DNRInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	BOOL bIsOpen = *(BOOL*)( cTpMsg.GetBody());
	m_pTPMoonCamCfg->em2DNoiseLevle = *(EmTPReduNoise*)(cTpMsg.GetBody()+ sizeof(BOOL));
	
	PrtMsg( ev_TpSetCam2DNoiseLevle_Ind, emEventTypemoontoolRecv, "bIsOpen:%d emTPReduNoise:%d", bIsOpen, m_pTPMoonCamCfg->em2DNoiseLevle );
	PostEvent( UI_MOONTOOL_CAMERA_2DNR_IND, (WPARAM)(m_pTPMoonCamCfg->em2DNoiseLevle), (LPARAM)bIsOpen );*/
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TCamD2NRMode tCamD2NRMode;
    ZeroMemory(&tCamD2NRMode, sizeof(TCamD2NRMode));
    if (tMsgHead.wMsgLen != 0)
    {
        tCamD2NRMode = *reinterpret_cast<TCamD2NRMode*>( cMsg.content + sizeof(TRK100MsgHead) );
    }

    if ( RK100_OPT_RTN_OK == tMsgHead.wOptRtn )
    {
        m_pTPMoonCamCfg->CamD2NRMode = tCamD2NRMode;
    }
    
    PrtRkcMsg( RK100_EVT_SET_CAM_D2NR_ACK, emEventTypeScoketRecv, "wRtn:%d", tMsgHead.wOptRtn);
    PostEvent( UI_MOONTOOL_CAMERA_2DNR_IND, (WPARAM)tCamD2NRMode.D2NROnFlag, (LPARAM)tMsgHead.wOptRtn );
}

void CCamConfig::OnCam3DNRInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	BOOL bIsOpen = *(BOOL*)( cTpMsg.GetBody());
	m_pTPMoonCamCfg->em3DNoiseLevle = *(EmTPReduNoise*)(cTpMsg.GetBody()+ sizeof(BOOL));
	
	PrtMsg( ev_TpSetCam3DNoiseLevle_Ind, emEventTypemoontoolRecv, "bIsOpen:%d emTPReduNoise:%d", bIsOpen, m_pTPMoonCamCfg->em3DNoiseLevle );
	PostEvent( UI_MOONTOOL_CAMERA_3DNR_IND, (WPARAM)(m_pTPMoonCamCfg->em3DNoiseLevle), (LPARAM)bIsOpen );*/

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TCamD3NRMode tCamD3NRMode;
    ZeroMemory(&tCamD3NRMode, sizeof(TCamD3NRMode));
    if (tMsgHead.wMsgLen != 0)
    {
        tCamD3NRMode = *reinterpret_cast<TCamD3NRMode*>( cMsg.content + sizeof(TRK100MsgHead) );
    }

    if ( RK100_OPT_RTN_OK == tMsgHead.wOptRtn )
    {
        m_pTPMoonCamCfg->CamD3NRMode = tCamD3NRMode;
    }

    PrtRkcMsg( RK100_EVT_SET_CAM_D3NR_ACK, emEventTypeScoketRecv, "wRtn:%d", tMsgHead.wOptRtn);
    PostEvent( UI_MOONTOOL_CAMERA_3DNR_IND, (WPARAM)tCamD3NRMode.D3NROnFlag, (LPARAM)tMsgHead.wOptRtn );
}

//预置位
u16 CCamConfig::CamOrderPosCheckCmd( const TCamPresetNumberList& tCamPreset )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bCheck, sizeof(BOOL));
	pcTpMsg->SetEvent(ev_TpCamInitPreset_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamInitPreset_Cmd, emEventTypemoontoolSend, "bCheck:%d", bCheck );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_Preset_PowOnRecall);
    tRK100MsgHead.wMsgLen = htons(sizeof(TCamPresetNumberList));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&tCamPreset, sizeof(TCamPresetNumberList));//添加消息体
    
    PrtRkcMsg( RK100_EVT_SET_CAM_Preset_PowOnRecall, emEventTypeScoketSend, "PresetPos:[%d,%d,%d,%d,%d,%d,%d,%d]",
        tCamPreset.PresetNumber1, tCamPreset.PresetNumber2, tCamPreset.PresetNumber3, tCamPreset.PresetNumber4,
        tCamPreset.PresetNumber5, tCamPreset.PresetNumber6, tCamPreset.PresetNumber7, tCamPreset.PresetNumber8);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnCamOrderPosSelInd( const CMessage& cMsg )
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	m_pTPMoonCamCfg->bIsPreUsed = *(BOOL*)( cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+ sizeof(BOOL));
	
	PrtMsg( ev_TpCamInitPreset_Ind, emEventTypemoontoolRecv, "bIsUsed:%d, bOk:%d", m_pTPMoonCamCfg->bIsPreUsed, bOk );
	PostEvent( UI_MOONTOOL_CAMERA_INITPRESET_IND, (WPARAM)(m_pTPMoonCamCfg->bIsPreUsed), (LPARAM)bOk );*/

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TCamPresetNumberList tCamPresetNumberList;
    ZeroMemory(&tCamPresetNumberList, sizeof(TCamPresetNumberList));
    if (tMsgHead.wMsgLen != 0)
    {
        tCamPresetNumberList = *reinterpret_cast<TCamPresetNumberList*>( cMsg.content + sizeof(TRK100MsgHead) );
    }
    
    PrtRkcMsg( RK100_EVT_SET_CAM_Preset_PowOnRecall_ACK, emEventTypeScoketRecv, "wRtn:%d", tMsgHead.wOptRtn);
}

//预置位1保存
u16 CCamConfig::CamPreSet1SaveCmd()
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_CAM_Preset_Save);
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    
    PrtRkcMsg( RK100_EVT_SET_CAM_Preset_Save, emEventTypeScoketSend, "CamPreset Save.");
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CCamConfig::OnCamPreSet1SaveRsp( const CMessage& cMsg )
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    PrtRkcMsg( RK100_EVT_SET_CAM_Preset_Save_ACK, emEventTypeScoketRecv, "wRtn:%d", tMsgHead.wOptRtn);

    if ( m_bOutputFmtChg )
    {
        PostEvent( UI_CAMERA_PRESET1_SAVE_RSP, (WPARAM)(RK100_OPT_RTN_OK == tMsgHead.wOptRtn), FALSE );  //无重启提示弹框
    }
    else
    {
        PostEvent( UI_CAMERA_PRESET1_SAVE_RSP, (WPARAM)(RK100_OPT_RTN_OK == tMsgHead.wOptRtn), TRUE );  //有重启提示弹框
    }
}

//重启MOON
u16 CCamConfig::RebootMoon( )
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_REBOOT);
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    
    PrtRkcMsg( RK100_EVT_REBOOT, emEventTypeScoketSend, "Reboot...");
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

//恢复默认
u16 CCamConfig::MoonCamResetCmd(u8 byIndex)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &byIndex, sizeof(u8) );
	
	pcTpMsg->SetEvent(ev_TpCamParamDefault_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamParamDefault_Cmd, emEventTypemoontoolSend, "MoonCamReset, byIndex: %d", byIndex );
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_RECOVERY_DEFAULT_SET);
    tRK100MsgHead.wMsgLen = htons(sizeof(u8));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&byIndex, sizeof(u8));//添加消息体

    PrtRkcMsg( RK100_EVT_RECOVERY_DEFAULT_SET, emEventTypeScoketSend, "CamReset:%d", byIndex);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

//界面参数设置完成
u16 CCamConfig::InputCamParamOverCmd()
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_PARAM_INPUT_OVER);
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    
    PrtRkcMsg( RK100_EVT_PARAM_INPUT_OVER, emEventTypeScoketSend, "Input Camera Param Over.");
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

//界面参数设置完成 Rsp
void CCamConfig::OnCamParamInputOverRsp( const CMessage& cMsg )
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    PrtRkcMsg( RK100_EVT_PARAM_INPUT_OVER_ACK, emEventTypeScoketRecv, "Input Camera Param Done!");
    //导入界面参数，最后一参数设置完成
    if ( m_bSetAllCamCfg && m_byCameraSel == 0 )
    {
        m_bSetAllCamCfg = FALSE;
    }
}

void CCamConfig::OnCamPreSetNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	TTPPreParam tTpPreParam = *(TTPPreParam*)(cTpMsg.GetBody());
	memcpy( m_atTPCamPre, &tTpPreParam, sizeof(TTPCamPre)*MAX_CAMERA_Pre_NUM );

	PrtMsg( ev_TpCamPreSet_Nty, emEventTypemoontoolRecv, "TTPPreParam1: %d, TTPPreParam2: %d, TTPPreParam3: %d",
        m_atTPCamPre[0].achachDescription, m_atTPCamPre[1].achachDescription, m_atTPCamPre[2].achachDescription );

	PostEvent( UI_MOONTOOL_CAMPRESET_NTY );*/

}

TTPCamPre* CCamConfig::GetCamPreInfo()
{
    return m_atTPCamPre;
}

//保存预置位列表
u16 CCamConfig::CamPreSetSaveCmd( const TTPCamPre& tTPCamPre )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&tTPCamPre, sizeof(TTPCamPre));
	pcTpMsg->SetEvent(ev_TpCamPreSet_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamPreSet_Cmd, emEventTypemoontoolSend, "TTPCamPre:%d", tTPCamPre.byPre );
	return wRet;	*/
	return true;
}

void CCamConfig::OnCamPreSetInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);

	TTPCamPre tTPCamPre = *(TTPCamPre*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(TTPCamPre));

	PrtMsg( ev_TpCamPreSet_Ind, emEventTypemoontoolRecv, "Index:%d, bOk:%d, achachDescription:%s", tTPCamPre.byPre, bOk, tTPCamPre.achachDescription );	

	PostEvent( UI_MOONTOOL_PRESET_IND, (WPARAM)&tTPCamPre, (LPARAM)bOk );*/
}

u16 CCamConfig::OrderPosDeleteReq( const TTPCamPre& tTPCamPre )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&tTPCamPre, sizeof(TTPCamPre));
	pcTpMsg->SetEvent(ev_TpCamPreReset_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamPreReset_Cmd, emEventTypemoontoolSend, "TTPCamPre:%d", tTPCamPre.byPre );
	return wRet;*/	
	return true;
}

void CCamConfig::OnCamPreResetInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);

	TTPCamPre tTPCamPre = *(TTPCamPre*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(TTPCamPre));

	PrtMsg( ev_TpCamPreReset_Ind, emEventTypemoontoolRecv, "Index:%d, bOk:%d, achachDescription:%s", tTPCamPre.byPre, bOk, tTPCamPre.achachDescription  );

	PostEvent( UI_MOONTOOL_PREDEL_IND, (WPARAM)&tTPCamPre, (LPARAM)bOk );*/

}

u16 CCamConfig::OrderPosInvokeCmd( const TTPCamPre& tTPCamPre )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&tTPCamPre, sizeof(TTPCamPre));
	pcTpMsg->SetEvent(ev_TpCamPreRecall_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamPreRecall_Cmd, emEventTypemoontoolSend, "TTPCamPre:%d", tTPCamPre );
	return wRet;	*/
	return true;
}

void CCamConfig::OnCamPreRecallInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	TTPCamPre tTPCamPre = *(TTPCamPre*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(TTPCamPre));
	
	PrtMsg( ev_TpCamPreRecall_Ind, emEventTypemoontoolRecv, "Index:%d, bOk:%d, achachDescription:%s",
		tTPCamPre.byPre, bOk, tTPCamPre.achachDescription  );	*/
}

u16 CCamConfig::CamPreSetModifyCmd( const TTPCamPre& tTPCamPre )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&tTPCamPre, sizeof(TTPCamPre));
	pcTpMsg->SetEvent(ev_TpCamPreModify_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamPreModify_Cmd, emEventTypemoontoolSend, "TTPCamPre:%d", tTPCamPre );
	return wRet;*/	
	return true;
}

void CCamConfig::OnCamPreSetModifyInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	TTPCamPre tTPCamPre = *(TTPCamPre*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(TTPCamPre));
	
	PrtMsg( ev_TpCamPreModify_Ind, emEventTypemoontoolRecv, "Index:%d, bOk:%d, achachDescription:%s", tTPCamPre.byPre, bOk, tTPCamPre.achachDescription  );	

	PostEvent( UI_MOONTOOL_PREMODIFY_IND, (WPARAM)&tTPCamPre, (LPARAM)bOk );*/
}



void CCamConfig::OnCamParamDefaultInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	TTPMoonCamInfo tTPMoonCamInfo = *(TTPMoonCamInfo*)(cTpMsg.GetBody());

	switch( tTPMoonCamInfo.byIndex )
	{
	case 0:
		{
			m_tCnCameraCfg1 = tTPMoonCamInfo;
			break;
		}
	case 1:
		{
			m_tCnCameraCfg2 = tTPMoonCamInfo;
			break;
		}
	case 2:
		{
			m_tCnCameraCfg3 = tTPMoonCamInfo;
			break;
		}
	default:
		break;
	}

	BOOL bIsOk = *(BOOL*)( cTpMsg.GetBody()+ sizeof(TTPMoonCamInfo) );

	PrtMsg( ev_TpCamParamDefault_Ind, emEventTypemoontoolRecv, " bOk:%d ", bIsOk );	

	PostEvent( UI_MOONTOOL_CAMPARAMDEFAULT_IND, (WPARAM)&tTPMoonCamInfo, (LPARAM)bIsOk );*/

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    TTPMoonCamInfo tTPMoonCamInfo;
    TRK100NetParam tNetParam;
    ZeroMemory(&tTPMoonCamInfo, sizeof(TTPMoonCamInfo));
    ZeroMemory(&tNetParam, sizeof(TRK100NetParam));

    if (tMsgHead.wMsgLen != 0 && tMsgHead.wOptRtn == RK100_OPT_RTN_OK)
    {
        tTPMoonCamInfo = *reinterpret_cast<TTPMoonCamInfo*>( cMsg.content + sizeof(TRK100MsgHead) );

        //恢复默认：三个机芯一同恢复为默认参数
        TCamID tCamID;
        ZeroMemory(&tCamID, sizeof(TCamID));
        m_tCnCameraCfg1 = tTPMoonCamInfo;
        m_tCnCameraCfg1.TCamIDIndex = tCamID;
        m_tCnCameraCfg1.TCamIDIndex.CamNum1Flag = 1;

        m_tCnCameraCfg2 = tTPMoonCamInfo;
        m_tCnCameraCfg2.TCamIDIndex = tCamID;
        m_tCnCameraCfg2.TCamIDIndex.CamNum2Flag = 1;

        m_tCnCameraCfg3 = tTPMoonCamInfo;
        m_tCnCameraCfg3.TCamIDIndex = tCamID;
        m_tCnCameraCfg3.TCamIDIndex.CamNum3Flag = 1;

        PostEvent( UI_MOONTOOL_CAMINFO_NTY, m_byCameraSel, NULL );

        PrtRkcMsg( RK100_EVT_RECOVERY_DEFAULT_SET_ACK, emEventTypeScoketRecv, "\n \
<CamNumFlag:[%d,%d,%d],dwZoomPos:%d,GainInputVal:%d>\n \
<R Gain:%d, B Gian:%d>\n \
<BrightVal:%d,ColorHueVal:%d,ColorGainVal:%d, Gama:[%d,%d,%d]>\n \
<OutputFmt:[4K30:%d,4K25:%d,1080P60:%d,1080P50:%d,1080P30:%d,1080P25:%d,720P60:%d,720P50:%d]>",
tTPMoonCamInfo.TCamIDIndex.CamNum1Flag, tTPMoonCamInfo.TCamIDIndex.CamNum2Flag, tTPMoonCamInfo.TCamIDIndex.CamNum3Flag,
tTPMoonCamInfo.dwZoomPos, tTPMoonCamInfo.GainMode.GainInputVal, tTPMoonCamInfo.WBMode.RGainVal, tTPMoonCamInfo.WBMode.BGainVal,
tTPMoonCamInfo.CamImagParam.BrightVal, tTPMoonCamInfo.CamImagParam.ColorHueVal, tTPMoonCamInfo.CamImagParam.ColorGainVal,
tTPMoonCamInfo.CamImagParam.Gamma_opt_1_flag, tTPMoonCamInfo.CamImagParam.Gamma_opt_2_flag, tTPMoonCamInfo.CamImagParam.Gamma_opt_3_flag,
tTPMoonCamInfo.OutputFmt.FMT4K_30fps_flag, tTPMoonCamInfo.OutputFmt.FMT4K_25fps_flag, tTPMoonCamInfo.OutputFmt.FMT1080_60fps_flag, tTPMoonCamInfo.OutputFmt.FMT1080_50fps_flag,
tTPMoonCamInfo.OutputFmt.FMT1080_30fps_flag, tTPMoonCamInfo.OutputFmt.FMT1080_25fps_flag, tTPMoonCamInfo.OutputFmt.FMT720_60fps_flag, tTPMoonCamInfo.OutputFmt.FMT720_50fps_flag);
        PrtRkcMsg( RK100_EVT_RECOVERY_DEFAULT_SET_ACK, emEventTypeScoketRecv, "\n \
<[Sixty:%d, Thirty:%d], [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]>\n \
<[Fifty:%d, TenwFif:%d], [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]>",
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.SixtyFpsModeFlag, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.ThirtyFpsModeFlag, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_30Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_50Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_60Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_90Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_100Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_125Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_180Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_250Sp,tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_350Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_500Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_725Sp,tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_1000Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_1500Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_2000Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_3000Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_4000Sp,
tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_6000Sp, tTPMoonCamInfo.ShutterMode.SixtyOrThirtyMode.Shutter_10000Sp, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.FiftyFpsModeFlag,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.TenwFifFpsModeFlag, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_25Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_30Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_50Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_60Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_100Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_120Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_150Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_215Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_300Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_425Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_600Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_1000Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_1250Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_1750Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_2500Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_3500Spd, tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_6000Spd,
tTPMoonCamInfo.ShutterMode.FiftyOrTwentyMode.Shutter_10000Spd);

        /*tNetParam = *reinterpret_cast<TRK100NetParam*>( cMsg.content + sizeof(TRK100MsgHead) + sizeof(TTPMoonCamInfo) );
        tNetParam.dwIP = ntohl(tNetParam.dwIP);
        tNetParam.dwSubMask = ntohl(tNetParam.dwSubMask);
        tNetParam.dwGateway = ntohl(tNetParam.dwGateway);
        tNetParam.dwMqttIP = ntohl(tNetParam.dwMqttIP);
        tNetParam.MqttPort = ntohs(tNetParam.MqttPort);

        in_addr tAddr;
        tAddr.S_un.S_addr = tNetParam.dwIP;
        PrtRkcMsg( RK100_EVT_RECOVERY_DEFAULT_SET_ACK, emEventTypeScoketRecv, "NetParam[IP:%s]", inet_ntoa(tAddr));
        tAddr.S_un.S_addr = tNetParam.dwSubMask;
        PrtRkcMsg( RK100_EVT_RECOVERY_DEFAULT_SET_ACK, emEventTypeScoketRecv, "NetParam[SubMask:%s]", inet_ntoa(tAddr));
        tAddr.S_un.S_addr = tNetParam.dwGateway;
        PrtRkcMsg( RK100_EVT_RECOVERY_DEFAULT_SET_ACK, emEventTypeScoketRecv, "NetParam[Gateway:%s]", inet_ntoa(tAddr));*/

        //网络设置恢复为默认值
        tNetParam.dwIP = inet_addr("192.169.0.100");
        tNetParam.dwSubMask = inet_addr("255.255.255.0");
        tNetParam.dwGateway = inet_addr("192.169.1.1");
    }
    
    PrtRkcMsg( RK100_EVT_RECOVERY_DEFAULT_SET_ACK, emEventTypeScoketRecv, "wRtn:%d", tMsgHead.wOptRtn);
    PostEvent( UI_MoonSecDefault_Nty, (WPARAM)(RK100_OPT_RTN_OK== tMsgHead.wOptRtn), (LPARAM)&tNetParam );
}



u16 CCamConfig::CamParamUploadCmd()
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	pcTpMsg->SetEvent(ev_TpCamParamUpload_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamParamUpload_Cmd, emEventTypemoontoolSend, "");
	return wRet;	*/
	return true;
}

u16 CCamConfig::UpgradeMoon( const s8* chVerFileInfo )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(chVerFileInfo, TP_MAX_FILENAME_LEN+1);
	pcTpMsg->SetEvent(ev_TpMoonUpgrade_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpMoonUpgrade_Cmd, emEventTypemoontoolSend, "chVerFileInfo:%s", chVerFileInfo );
	return wRet;*/
	return true;
}

u16 CCamConfig::UpdateMoonMechanism(const s8* chVerFileInfo)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(chVerFileInfo, TP_MAX_FILENAME_LEN+1);
	pcTpMsg->SetEvent(ev_CamUpgrade_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CamUpgrade_Cmd, emEventTypemoontoolSend, "chVerFileInfo:%s", chVerFileInfo );
	return wRet;*/
	return true;
}

u16 CCamConfig::CamParamUploadNty(BOOL bSuccess)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bSuccess, sizeof(BOOL));
	pcTpMsg->SetEvent(ev_TpCamParamUpload_Nty);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamParamUpload_Nty, emEventTypemoontoolSend, "bSuccess:%d", bSuccess );
	return wRet;*/
	return true;
}

void CCamConfig::OnMoonUpgradeInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody());
	
	PrtMsg( ev_TpMoonUpgrade_Ind, emEventTypemoontoolRecv, "bOk:%d",  bOk );
	
	PostEvent( UI_MOONTOOL_UPGRADE_IND, NULL, (LPARAM)bOk );*/
}

void CCamConfig::OnUpdateMechanismInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody());
	
	PrtMsg( ev_CamUpgrade_Ind, emEventTypemoontoolRecv, "bOk:%d",  bOk );
	
	PostEvent( UI_CAMMECHANISM_UPGRADE_IND, NULL, (LPARAM)bOk );*/
}

u16 CCamConfig::SetReferenceLineCmd( BOOL bOpen )
{
	/*u8 byCount = 3;
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bOpen, sizeof(BOOL));
	pcTpMsg->CatBody(&byCount,sizeof(u8));
	pcTpMsg->SetEvent(ev_TpSetRefer_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpSetRefer_Cmd, emEventTypemoontoolSend, "Reference Line Open :%d ", bOpen );
	return wRet;*/
	return true;
}

void CCamConfig::OnReferenceLineInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(BOOL));
	PrtMsg( ev_TpSetRefer_Ind, emEventTypemoontoolRecv, "Reference line open:%d  success :%d",  bOpen,bSuccess );
	
	PostEvent( UI_MoonTool_ReferenceLine_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess);*/
}

void CCamConfig::OnReferenceLineNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = TRUE;
	PrtMsg( ev_TpSetRefer_Nty, emEventTypemoontoolRecv, "Reference line open:%d ",  bOpen );
	
	PostEvent( UI_MoonTool_ReferenceLine_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess);*/
}

u16 CCamConfig::SetHorizontalFlipCmd( BOOL bOpen )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&bOpen, sizeof(BOOL));
	pcTpMsg->SetEvent(ev_TpFlatTurn_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpFlatTurn_Cmd, emEventTypemoontoolSend, "Horizontal Flip Line Open :%d ", bOpen );
	return wRet;*/
	return true;
}

void CCamConfig::OnHorizontalFlipInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(BOOL));
	PrtMsg( ev_TpFlatTurn_Ind, emEventTypemoontoolRecv, "Reference line open:%d  success :%d",  bOpen,bSuccess );
	
	PostEvent( UI_MoonTool_HorizontalFlip_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess);*/
}

void CCamConfig::OnHorizontalFlipNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = TRUE;
	PrtMsg( ev_TpFlatTurn_Nty, emEventTypemoontoolRecv, "Reference line open:%d ",  bOpen );
	
	PostEvent( UI_MoonTool_HorizontalFlip_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess);*/
}

u16 CCamConfig::SetTrapezoidalCorCmd( BOOL bOpen )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&bOpen, sizeof(BOOL));
	pcTpMsg->SetEvent(ev_TpDisortSwitch_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpDisortSwitch_Cmd, emEventTypemoontoolSend, "Trapezoidal Correction Open :%d ", bOpen );
	return wRet;*/
	return true;
}

u16 CCamConfig::SetShowRectRegionCmd(BOOL bOpen)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&bOpen, sizeof(BOOL));
	pcTpMsg->SetEvent( ev_TPMoonShowRectRegion_Cmd );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPMoonShowRectRegion_Cmd, emEventTypemoontoolSend, " ShowRectRegion Open :%d ", bOpen );
	return wRet;*/
	return true;
}

u16 CCamConfig::SetRgbConsistSwitchCmd(BOOL bOpen)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&bOpen, sizeof(BOOL));
	pcTpMsg->SetEvent( ev_TpColorSwich_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpColorSwich_Cmd, emEventTypemoontoolSend, " ShowRgbConsistSwitch Open :%d ", bOpen );

	return wRet;*/
	return true;
}

void CCamConfig::OnTrapezoidalCorInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);

	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(BOOL));
	PrtMsg( ev_TpDisortSwitch_Ind, emEventTypemoontoolRecv, "Trapezoidal Correction open:%d  success :%d",  bOpen,bSuccess );
	
	if ( bSuccess == TRUE )
	{
		if ( m_pTPMoonCamCfg == NULL )
		{
			SetCameraCfgPtr();
		}
		m_pTPMoonCamCfg->bIsCorrect = bOpen;
	}

	PostEvent( UI_MoonTool_TrapezoidalCor_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess);*/
}

void CCamConfig::OnShowRectRegionInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(BOOL));
	PrtMsg( ev_TPMoonShowRectRegion_Ind, emEventTypemoontoolRecv, "ShowRectRegion open:%d  success :%d",  bOpen, bSuccess );

	PostEvent( UI_MoonTool_ShowRectRegion_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess );*/
}

void CCamConfig::OnColorSwitchInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(BOOL));
	PrtMsg( ev_TpColorSwich_Ind, emEventTypemoontoolRecv, "ColorSwitch open:%d  success :%d",  bOpen, bSuccess );
	
	PostEvent( UI_MoonTool_ColorSwitch_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess );*/
}

u16 CCamConfig::SetTraCorParamCmd( EmTPCorrect emMyCorOption,EmTPCorrectChange emChangeOption )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&emMyCorOption, sizeof(EmTPCorrect));
	pcTpMsg->CatBody(&emChangeOption, sizeof(EmTPCorrectChange));
	pcTpMsg->SetEvent( ev_TpSetDisort_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpSetDisort_Cmd, emEventTypemoontoolSend, "My Trapezoidal Correction Option :%d <em_HorizonCorrect %d ; \
		em_HorizonStretch %d ; em_VerticalCorrect %d ; em_VerticalStretch %d > ; Increase or decrease %d <emCorrectEnlarge %d ; emCorrectReduce %d >", 
		emMyCorOption,em_HorizonCorrect, em_HorizonStretch,em_VerticalCorrect,em_VerticalStretch,emChangeOption,emCorrectEnlarge,emCorrectReduce);
	return wRet;*/
	return true;
}

void CCamConfig::OnTraCorParamInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	u32 dwValue = *(u32*)(cTpMsg.GetBody());
	EmTPCorrect emMyOption = *(EmTPCorrect*)(cTpMsg.GetBody()+sizeof(u32));

	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	if ( emMyOption == em_HorizonCorrect)
	{
		m_pTPMoonCamCfg->dwHorizonCorrect = dwValue;
	}
	else if ( emMyOption == em_HorizonStretch )
	{
		m_pTPMoonCamCfg->dwHorizonStretch = dwValue;
	}
	else if ( emMyOption == em_VerticalCorrect)
	{
		m_pTPMoonCamCfg->dwVerticalCorrect = dwValue;
	}
	else
	{
		m_pTPMoonCamCfg->dwVerticalStretch = dwValue;
	}

	PrtMsg( ev_TpSetDisort_Ind, emEventTypemoontoolRecv, "My Trapezoidal Correction Option :%d <em_HorizonCorrect %d ; \
		em_HorizonStretch %d ; em_VerticalCorrect %d ; em_VerticalStretch %d > ; Value %lu ", emMyOption
		,em_HorizonCorrect, em_HorizonStretch,em_VerticalCorrect,em_VerticalStretch, dwValue );
	
	PostEvent( UI_MoonTool_TraCorValue_IND, (WPARAM)&emMyOption ,NULL);*/
}

u16 CCamConfig::SnapShotCmd( )
{
	/*TTPSnapshotInfo tSnapShotInfo;
	tSnapShotInfo.byIndex = 3;
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&tSnapShotInfo,sizeof(TTPSnapshotInfo));
	pcTpMsg->SetEvent( ev_TpCamSnapshot_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSnapshot_Cmd, emEventTypemoontoolRecv ,"ev_TpCamSnapshot_Cmd");
	
	return wRet;*/
	return true;
}

void CCamConfig::SnapShotInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(TTPSnapshotInfo));

	TTPSnapshotInfo tSnapShotInfo = *(TTPSnapshotInfo*)( cTpMsg.GetBody());
	if ( tSnapShotInfo.byIndex == 3 )
	{
		PrtMsg( ev_TpCamSnapshot_Ind, emEventTypemoontoolRecv, "Success:%d",bSuccess );
	}
	else
	{
		PrtMsg( ev_TpCamSnapshot_Ind, emEventTypemoontoolRecv, "Success:%d,Index %d ,name %s",bSuccess,tSnapShotInfo.byIndex,tSnapShotInfo.achFileNme);
	}

	PostEvent( UI_MoonTool_SnapShot_IND, (WPARAM)&bSuccess,(LPARAM)&tSnapShotInfo);*/
}

void CCamConfig::OnDirectSetDistortInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	TTPDistortInfo tTPDistortInfo = *(TTPDistortInfo*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPDistortInfo) );
    
	PrtMsg( ev_TPDirectSetDistor_Ind, emEventTypemoontoolRecv, "byIndex: %d, emDistortType: %d, dwValue: %d", tTPDistortInfo.byIndex, tTPDistortInfo.emDistortType, tTPDistortInfo.dwValue );

	PostEvent( UI_DIRECTSETDISTORT_IND, (WPARAM)&tTPDistortInfo, (LPARAM)&bOk );*/
}

void CCamConfig::OnSecDefaultNty(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	TTPSecBoundaryInfo tTPSecBoundaryInfo = *(TTPSecBoundaryInfo*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody() + sizeof(TTPSecBoundaryInfo));

	PrtMsg( ev_TpSecDefault_Nty, emEventTypemoontoolRecv, "");

	PostEvent( UI_MoonSecDefault_Nty, (WPARAM)&tTPSecBoundaryInfo, (LPARAM)&bOk );*/
}

void CCamConfig::OnSecBoundaryNty(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	TTPSecBoundaryInfo tTPSecBoundaryInfo = *(TTPSecBoundaryInfo*)(cTpMsg.GetBody());
	PrtMsg( ev_TpSecBoundary_Nty, emEventTypemoontoolRecv,"");
	PostEvent( UI_SecBoundary_Nty, (WPARAM)&tTPSecBoundaryInfo, NULL );*/
}

void CCamConfig::OnChangeDistortInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	TTPDistortInfo tTPDistortInfo = *(TTPDistortInfo*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPDistortInfo) );
    
	PrtMsg( ev_TPChangeDistor_Ind, emEventTypemoontoolRecv, "byIndex: %d, emDistortType: %d, dwValue: %d", tTPDistortInfo.byIndex, tTPDistortInfo.emDistortType, tTPDistortInfo.dwValue );

	PostEvent(UI_CHANGEDISTORT_IND, (WPARAM)&tTPDistortInfo, (LPARAM)&bOk );*/	
}

u16 CCamConfig::GammaStyleSelCmd( const EmH650Gamma& enH650Gamma)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &enH650Gamma, sizeof( EmH650Gamma) );
	pcTpMsg->SetEvent( ev_TpCamSetGamma_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSetGamma_Cmd, emEventTypemoontoolSend, "emH650Gamma:%d", enH650Gamma ); 

	return wRet;*/
	return true;
}

void CCamConfig::OnGammaSelInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	EmH650Gamma emH650Gamma;
	emH650Gamma = *(EmH650Gamma*)( cTpMsg.GetBody() );
	BOOL bSelGamma = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmH650Gamma) + sizeof(u8) );

	m_pTPMoonCamCfg->emGamma = emH650Gamma;

	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();		
	}
	
	PrtMsg( ev_TpCamSetGamma_Ind, emEventTypemoontoolRecv, "emGammaSel:%d", emH650Gamma );
	PostEvent( UI_MOONTOOL_GammaStyleSel_IND, NULL, (LPARAM)bSelGamma );*/
}

void CCamConfig::OnMechanismSelectNty(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	EmTPMechanism emTPMechanism= *(EmTPMechanism*)( cTpMsg.GetBody() );

	PrtMsg( ev_TpMechanismSelect_Nty, emEventTypemoontoolRecv, "emTPMechanism:%d", emTPMechanism);
	PostEvent( UI_TpMechanismSelect_NTY, NULL, (LPARAM)emTPMechanism);*/
}

void CCamConfig::OnTpMechverNty(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);

	TTPMechVer tTpMechver;
	
	tTpMechver.byIndex = *(u8*)( cTpMsg.GetBody() );
	s8 *achHardwaerVer = (s8*)( cTpMsg.GetBody() + sizeof(u8) );
	s8 *achSoftWareVer = (s8*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(s8)*MOON_MAX_DEVICEVER_LEN  ); 

	memcpy( tTpMechver.achMechHWVer, achHardwaerVer, MOON_MAX_DEVICEVER_LEN );
	memcpy( tTpMechver.achMechSWVer, achSoftWareVer, MOON_MAX_DEVICEVER_LEN );
	
	PrtMsg( ev_TpMechVer_Nty, emEventTypemoontoolRecv, "byIndex:%d, achHardwaerVer:%s, achSoftWareVer:%s", m_byCameraSel, tTpMechver.achMechHWVer, tTpMechver.achMechSWVer);
	PostEvent( UI_TpMechVer_NTY, (WPARAM)&tTpMechver, NULL );*/
}

void CCamConfig::OnDelayCorrectInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	u8 nPosition = *(u8*)(cTpMsg.GetBody());
	u32 dwDelayCorrectVal = *(u32*)(cTpMsg.GetBody()+sizeof(u8));
	BOOL bSuccess = *(BOOL *)(cTpMsg.GetBody()+sizeof(u8)+sizeof(u32));
	
	TTPFpgaDelay tTPDelayInfo;
	tTPDelayInfo.byIndex = nPosition;
	tTPDelayInfo.dwDelay = dwDelayCorrectVal;
	
	PrtMsg( ev_TpFpgaDelayCorrect_Ind, emEventTypemoontoolRecv, "nPosition: %d, dwDelayCorrectVal: %d, bSuccess: %d",
		nPosition, dwDelayCorrectVal, bSuccess);
	
	PostEvent(UI_SETDELAYCORRECT_IND, (WPARAM)&tTPDelayInfo, (LPARAM)&bSuccess);*/
}

void CCamConfig::OnDelayCorrectNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	u8 nPosition = *(u8*)(cTpMsg.GetBody());
	u32 dwDelayCorrectVal = *(u32*)(cTpMsg.GetBody()+sizeof(u8));
	
	TTPFpgaDelay tTPDelayInfo;
	tTPDelayInfo.byIndex = nPosition;
	tTPDelayInfo.dwDelay = dwDelayCorrectVal;
	
	PrtMsg( ev_TpFpgaDelayCorrect_Nty, emEventTypemoontoolRecv, "nPosition: %d, dwDelayCorrectVal: %d",
		nPosition, dwDelayCorrectVal);
	
	PostEvent(UI_SETDELAYCORRECT_NTY, (WPARAM)&tTPDelayInfo, NULL);*/
}

u16 CCamConfig::SetDelayCorrectCmd( u8 nPosition, u32 dwDelay )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());

	pcTpMsg->SetBody(&nPosition, sizeof(u8));
	pcTpMsg->CatBody(&dwDelay, sizeof(u32));
	pcTpMsg->SetEvent( ev_TpFpgaDelayCorrect_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpFpgaDelayCorrect_Cmd, emEventTypemoontoolSend, "nPosition: %d, dwDelay: %d", nPosition, dwDelay);
	
	return wRet;*/
	return true;
}

void CCamConfig::OnReBootRkRsp( const CMessage& cMsg )
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    PrtRkcMsg( RK100_EVT_REBOOT_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);
    
    PostEvent(UI_RKC_REBOOT, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn );
}

void DelaySendCmd(int interval)
{
    HANDLE evt;
    if (interval <= 0)
    {
        interval = 1;
    }

    evt = CreateEvent(NULL, TRUE, FALSE, NULL);
    WaitForSingleObject(evt, interval);
    CloseHandle(evt);
}

void CCamConfig::AllCamCfgCmdSend()
{
    //首先判断输出制式是否相同
    if ( m_tCnCameraCfg2.OutputFmt.FMT4K_25fps_flag != m_atOldCamCfg[0].OutputFmt.FMT4K_25fps_flag
        || m_tCnCameraCfg2.OutputFmt.FMT4K_30fps_flag != m_atOldCamCfg[0].OutputFmt.FMT4K_30fps_flag
        || m_tCnCameraCfg2.OutputFmt.FMT1080_25fps_flag != m_atOldCamCfg[0].OutputFmt.FMT1080_25fps_flag
        || m_tCnCameraCfg2.OutputFmt.FMT1080_30fps_flag != m_atOldCamCfg[0].OutputFmt.FMT1080_30fps_flag
        || m_tCnCameraCfg2.OutputFmt.FMT1080_50fps_flag != m_atOldCamCfg[0].OutputFmt.FMT1080_50fps_flag
        || m_tCnCameraCfg2.OutputFmt.FMT1080_60fps_flag != m_atOldCamCfg[0].OutputFmt.FMT1080_60fps_flag
        || m_tCnCameraCfg2.OutputFmt.FMT720_50fps_flag != m_atOldCamCfg[0].OutputFmt.FMT720_50fps_flag
        || m_tCnCameraCfg2.OutputFmt.FMT720_60fps_flag != m_atOldCamCfg[0].OutputFmt.FMT720_60fps_flag )
    {
        SetOutputFormatCmd(m_tCnCameraCfg2.OutputFmt);
        DelaySendCmd(DELAY_SEND_CMD);
    }

    TTPMoonCamInfo *ptCurCamInfo = NULL ;
    //分别对机芯3，2，1进行参数设置
    for (s8 byIndex = 2; byIndex >= 0 ; byIndex--)
    {
        //机芯选择
        CamSelCmd(byIndex);
        DelaySendCmd(DELAY_SEND_CMD);
        //机芯控制逻辑界面映射：1->2, 2->3, 3->1
        if ( byIndex == 2 )
        {
            ptCurCamInfo = &m_tCnCameraCfg1;
        }
        else if (byIndex == 1)
        {
            ptCurCamInfo = &m_tCnCameraCfg3;
        }
        else
        {
            ptCurCamInfo = &m_tCnCameraCfg2;
        }
        //ZOOM值设置
        if ( m_atOldCamCfg[byIndex].dwZoomPos != ptCurCamInfo->dwZoomPos )
        {
            TCamZoomVal tCamZoomVal;
            ZeroMemory(&tCamZoomVal, sizeof(TCamZoomVal));
            tCamZoomVal.InputPreciseValFlag = 1;
            tCamZoomVal.InputVal = ptCurCamInfo->dwZoomPos;
            SetCamZoomValCmd(tCamZoomVal);
            DelaySendCmd(DELAY_SEND_CMD);
        }
        //聚焦模式设置
        if ( m_atOldCamCfg[byIndex].FocusMode.AutoModeFlag
            != ptCurCamInfo->FocusMode.AutoModeFlag )
        {
            if (ptCurCamInfo->FocusMode.AutoModeFlag == 1)
            {
                SetCamAutoFocusCmd(emAuto);
            }
            else
            {
                SetCamAutoFocusCmd(emManual);
            }
            DelaySendCmd(DELAY_SEND_CMD);
        }
        //光圈模式设置
        if (  m_atOldCamCfg[byIndex].IrisMode.IrisAutoFlag != ptCurCamInfo->IrisMode.IrisAutoFlag
            || m_atOldCamCfg[byIndex].IrisMode.IrisBackCompFlag != ptCurCamInfo->IrisMode.IrisBackCompFlag
            || m_atOldCamCfg[byIndex].IrisMode.optIrisF2_8Flag != ptCurCamInfo->IrisMode.optIrisF2_8Flag
            || m_atOldCamCfg[byIndex].IrisMode.optIrisF3_1Flag != ptCurCamInfo->IrisMode.optIrisF3_1Flag
            || m_atOldCamCfg[byIndex].IrisMode.optIrisF3_4Flag != ptCurCamInfo->IrisMode.optIrisF3_4Flag
            || m_atOldCamCfg[byIndex].IrisMode.optIrisF3_7Flag != ptCurCamInfo->IrisMode.optIrisF3_7Flag
            || m_atOldCamCfg[byIndex].IrisMode.optIrisF4_0Flag != ptCurCamInfo->IrisMode.optIrisF4_0Flag
            || m_atOldCamCfg[byIndex].IrisMode.optIrisF4_4Flag != ptCurCamInfo->IrisMode.optIrisF4_4Flag)
        {
            SetCamApertreCmd( ptCurCamInfo->IrisMode );
            DelaySendCmd(6*DELAY_SEND_CMD);  //响应时间较长
        }
        
        //白平衡设置
        if ( ptCurCamInfo->WBMode.CamWBAutoModeFlag
            != m_atOldCamCfg[byIndex].WBMode.CamWBAutoModeFlag )
        {
            CamAutoWBCmd( ptCurCamInfo->WBMode );
            DelaySendCmd(DELAY_SEND_CMD);
        }
        else if ( ptCurCamInfo->WBMode.RGainVal != m_atOldCamCfg[byIndex].WBMode.RGainVal
            || ptCurCamInfo->WBMode.BGainVal != m_atOldCamCfg[byIndex].WBMode.BGainVal)
        {
            if ( ptCurCamInfo->WBMode.CamWBManuModeFlag == 1 )
            {
                CamAutoWBCmd( ptCurCamInfo->WBMode );
                DelaySendCmd(DELAY_SEND_CMD);
            }
        }
        //图像参数
        if ( ptCurCamInfo->CamImagParam.ColorGainVal != m_atOldCamCfg[byIndex].CamImagParam.ColorGainVal
            || ptCurCamInfo->CamImagParam.ColorHueVal != m_atOldCamCfg[byIndex].CamImagParam.ColorHueVal
            || ptCurCamInfo->CamImagParam.Gamma_opt_1_flag != m_atOldCamCfg[byIndex].CamImagParam.Gamma_opt_1_flag
            || ptCurCamInfo->CamImagParam.Gamma_opt_2_flag != m_atOldCamCfg[byIndex].CamImagParam.Gamma_opt_2_flag
            || ptCurCamInfo->CamImagParam.Gamma_opt_3_flag != m_atOldCamCfg[byIndex].CamImagParam.Gamma_opt_3_flag )
        {
            CamImageParaCmd( ptCurCamInfo->CamImagParam );
            DelaySendCmd(6*DELAY_SEND_CMD);  //响应时间较长
        }
        //2D降噪设置
        if ( ptCurCamInfo->CamD2NRMode.D2NROnFlag != m_atOldCamCfg[byIndex].CamD2NRMode.D2NROnFlag )
        {
            Cam2DNRCmd( ptCurCamInfo->CamD2NRMode );
            DelaySendCmd(DELAY_SEND_CMD);
        }
        else if ( ptCurCamInfo->CamD2NRMode.D2NR_level_1_Flag != m_atOldCamCfg[byIndex].CamD2NRMode.D2NR_level_1_Flag
            || ptCurCamInfo->CamD2NRMode.D2NR_level_2_Flag != m_atOldCamCfg[byIndex].CamD2NRMode.D2NR_level_2_Flag
            || ptCurCamInfo->CamD2NRMode.D2NR_level_3_Flag != m_atOldCamCfg[byIndex].CamD2NRMode.D2NR_level_3_Flag
            || ptCurCamInfo->CamD2NRMode.D2NR_level_4_Flag != m_atOldCamCfg[byIndex].CamD2NRMode.D2NR_level_4_Flag
            || ptCurCamInfo->CamD2NRMode.D2NR_level_5_Flag != m_atOldCamCfg[byIndex].CamD2NRMode.D2NR_level_5_Flag )
        {
            if ( ptCurCamInfo->CamD2NRMode.D2NROnFlag == 1 )
            {
                Cam2DNRCmd( ptCurCamInfo->CamD2NRMode );
                DelaySendCmd(DELAY_SEND_CMD);
            }
        }
        //3D降噪设置
        if ( ptCurCamInfo->CamD3NRMode.D3NROnFlag != m_atOldCamCfg[byIndex].CamD3NRMode.D3NROnFlag )
        {
            Cam3DNRCmd( ptCurCamInfo->CamD3NRMode );
            DelaySendCmd(DELAY_SEND_CMD);
        }
        else if ( ptCurCamInfo->CamD3NRMode.D3NR_level_1_Flag != m_atOldCamCfg[byIndex].CamD3NRMode.D3NR_level_1_Flag
            || ptCurCamInfo->CamD3NRMode.D3NR_level_2_Flag != m_atOldCamCfg[byIndex].CamD3NRMode.D3NR_level_2_Flag
            || ptCurCamInfo->CamD3NRMode.D3NR_level_3_Flag != m_atOldCamCfg[byIndex].CamD3NRMode.D3NR_level_3_Flag
            || ptCurCamInfo->CamD3NRMode.D3NR_level_4_Flag != m_atOldCamCfg[byIndex].CamD3NRMode.D3NR_level_4_Flag
            || ptCurCamInfo->CamD3NRMode.D3NR_level_5_Flag != m_atOldCamCfg[byIndex].CamD3NRMode.D3NR_level_5_Flag )
        {
            if ( ptCurCamInfo->CamD3NRMode.D3NROnFlag == 1 )
            {
                Cam3DNRCmd( ptCurCamInfo->CamD3NRMode );
                DelaySendCmd(DELAY_SEND_CMD);
            }
        }
        // 曝光模式设置
        if (ptCurCamInfo->ExpMode.ExposAutoModeFlag == 1)
        {
            if ( m_atOldCamCfg[byIndex].ExpMode.ExposAutoModeFlag == 0 )
            {
                CamAutoExposureCmd( emAuto );
                DelaySendCmd(DELAY_SEND_CMD);
            }
        }
        else
        {
            if ( m_atOldCamCfg[byIndex].ExpMode.ExposAutoModeFlag == 1 )
            {
                CamAutoExposureCmd( emManual );
                DelaySendCmd(DELAY_SEND_CMD);
                //增益设置
                SetCamGainCmd( ptCurCamInfo->GainMode );
                DelaySendCmd(DELAY_SEND_CMD);
                //快门设置
                SetCamShutterCmd( ptCurCamInfo->ShutterMode );
                DelaySendCmd(2*DELAY_SEND_CMD);  //快门响应时间较长
            }
            else
            {
                //增益设置
                if ( ptCurCamInfo->GainMode.GainInputVal
                    != m_atOldCamCfg[byIndex].GainMode.GainInputVal )
                {
                    SetCamGainCmd( ptCurCamInfo->GainMode );
                    DelaySendCmd(DELAY_SEND_CMD);
                }
                //快门设置
                string strCurParam = _T("");
                string strOldParam = _T("");
                s8 achTemp[8] = {0};
                for (s32 nPos = 0; nPos < sizeof(TShutterMode); nPos++)
                {
                    sprintf( achTemp, "%02x", *((u8*)(&ptCurCamInfo->ShutterMode)+nPos) );
                    strCurParam.append(achTemp);
                    sprintf( achTemp, "%02x", *((u8*)(&m_atOldCamCfg[byIndex].ShutterMode)+nPos) );
                    strOldParam.append(achTemp);
                }

                if ( strCurParam.compare(strOldParam) != 0 )
                {
                    SetCamShutterCmd( ptCurCamInfo->ShutterMode );
                    DelaySendCmd(2*DELAY_SEND_CMD);  //快门响应时间较长
                }
            }
        }

        // 导入参数最后完成消息推送
        /* 必推消息（设置结束标志位：m_bSetAllCamCfg = FALSE，Kill 参数设置超时定时器） */
        if ( byIndex == 0 )
        {
            //输出制式改变需要重启，需提前保存导入的界面参数
            if ( m_bOutputFmtChg )
            {
                CamPreSet1SaveCmd();
            }

            InputCamParamOverCmd();
            ptCurCamInfo = NULL;
        }
    }
}