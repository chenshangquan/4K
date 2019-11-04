#include "stdafx.h"
#include "rkcmsgdriver.h"
#include "rkcmsgrecver.h"
#include "rkcprintctrl.h"

CRkcMsgDriver* CRkcMsgDriver::s_pMsgDriver = NULL;

CRkcMsgDriver::CRkcMsgDriver()
{
    // 构造事件名称表
    MappingEventName();
    s_pMsgDriver = this;
}

CRkcMsgDriver::~CRkcMsgDriver()
{
}

COspMsg* CRkcMsgDriver::GetOspMsgPtr(BOOL32 bClear)
{
    if (bClear) 
    {
        ZeroMemory(&m_tOspMsg, sizeof(COspMsg));
    }

    return &m_tOspMsg;
}
//注册一个处理消息的类的指针
void CRkcMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
{
    m_vpDispEvent.push_back(pDispEvnet);
}

void CRkcMsgDriver::MappingEventName()
{
    RKCMAPPING_HELPER( RK100_EVT_LOGIN, _T("RK100_EVT_LOGIN") );
    RKCMAPPING_HELPER( RK100_EVT_LOGIN_ACK, _T("RK100_EVT_LOGIN_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_SET_PASSWORD, _T("RK100_EVT_SET_PASSWORD") );
    RKCMAPPING_HELPER( RK100_EVT_SET_PASSWORD_ACK, _T("RK100_EVT_SET_PASSWORD_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_GET_BRD_INFO, _T("RK100_EVT_GET_BRD_INFO") );
    RKCMAPPING_HELPER( RK100_EVT_GET_BRD_INFO_ACK, _T("RK100_EVT_GET_BRD_INFO_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_SET_BRD_INFO, _T("RK100_EVT_SET_BRD_INFO") );
    RKCMAPPING_HELPER( RK100_EVT_SET_BRD_INFO_ACK, _T("RK100_EVT_SET_BRD_INFO_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_GET_BRD_INFO, _T("RK100_EVT_GET_BRD_INFO") );
    RKCMAPPING_HELPER( RK100_EVT_GET_BRD_INFO_ACK, _T("RK100_EVT_GET_BRD_INFO_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_REBOOT, _T("RK100_EVT_REBOOT") );
    RKCMAPPING_HELPER( RK100_EVT_REBOOT_ACK, _T("RK100_EVT_REBOOT_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_FIRST, _T("RK100_EVT_TFTP_UPDATE_FIRST") );
    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_FIRST_ACK, _T("RK100_EVT_TFTP_UPDATE_FIRST_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_SECOND, _T("RK100_EVT_TFTP_UPDATE_SECOND") );
    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_SECOND_ACK, _T("RK100_EVT_TFTP_UPDATE_SECOND_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_GET_NETPARAM, _T("RK100_EVT_GET_NETPARAM") );
    RKCMAPPING_HELPER( RK100_EVT_GET_NETPARAM_ACK, _T("RK100_EVT_GET_NETPARAM_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_SET_NETPARAM, _T("RK100_EVT_SET_NETPARAM") );
    RKCMAPPING_HELPER( RK100_EVT_SET_NETPARAM_ACK, _T("RK100_EVT_SET_NETPARAM_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_RESTORE, _T("RK100_EVT_RESTORE") );
    RKCMAPPING_HELPER( RK100_EVT_RESTORE_ACK, _T("RK100_EVT_RESTORE_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_GET_WORK_MODE, _T("RK100_EVT_GET_WORK_MODE") );
    RKCMAPPING_HELPER( RK100_EVT_GET_WORK_MODE_ACK, _T("RK100_EVT_GET_WORK_MODE_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_SET_WORK_MODE, _T("RK100_EVT_SET_WORK_MODE") );
    RKCMAPPING_HELPER( RK100_EVT_SET_WORK_MODE_ACK, _T("RK100_EVT_SET_WORK_MODE_ACK") );

    RKCMAPPING_HELPER( RK100_EVT_SET_HEART_BEAT, _T("RK100_EVT_SET_HEART_BEAT") ,3);
    RKCMAPPING_HELPER( RK100_EVT_SET_HEART_BEAT_ACK, _T("RK100_EVT_SET_HEART_BEAT_ACK") ,3);

    RKCMAPPING_HELPER( RK100_EVT_GET_POWER, _T("RK100_EVT_GET_POWER") ,3);
    RKCMAPPING_HELPER( RK100_EVT_GET_POWER_ACK, _T("RK100_EVT_GET_POWER_ACK") ,3);

    RKCMAPPING_HELPER( RK100_EVT_LOGIN_OTHER, _T("RK100_EVT_LOGIN_OTHER") );

    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_FIRST_NOTIFY, _T("RK100_EVT_TFTP_UPDATE_FIRST_NOTIFY") );
    RKCMAPPING_HELPER( RK100_EVT_TFTP_UPDATE_SECOND_NOTIFY, _T("RK100_EVT_TFTP_UPDATE_SECOND_NOTIFY") );

    RKCMAPPING_HELPER( RK100_EVT_SET_DEBUG_MODE, _T("RK100_EVT_SET_DEBUG_MODE"));
    RKCMAPPING_HELPER( RK100_EVT_SET_DEBUG_MODE_ACK, _T("RK100_EVT_SET_DEBUG_MODE_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_GET_DEBUG_MODE, _T("RK100_EVT_GET_DEBUG_MODE"));
    RKCMAPPING_HELPER( RK100_EVT_GET_DEBUG_MODE_ACK, _T("RK100_EVT_GET_DEBUG_MODE_ACK"));

    //moon904k30 新增
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_FOCUS, _T("RK100_EVT_SET_CAM_FOCUS"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_FOCUS_ACK, _T("RK100_EVT_SET_CAM_FOCUS_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_ZOOM_VAL, _T("RK100_EVT_SET_CAM_ZOOM_VAL"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_ZOOM_VAL_ACK, _T("RK100_EVT_SET_CAM_ZOOM_VAL_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_IRIS, _T("RK100_EVT_SET_CAM_IRIS"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_IRIS_ACK, _T("RK100_EVT_SET_CAM_IRIS_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_EXPOSURE, _T("RK100_EVT_SET_CAM_EXPOSURE"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_EXPOSURE_ACK, _T("RK100_EVT_SET_CAM_EXPOSURE_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_WB, _T("RK100_EVT_SET_CAM_WB"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_WB_ACK, _T("RK100_EVT_SET_CAM_WB_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_ImagParam, _T("RK100_EVT_SET_CAM_ImagParam"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_ImagParam_ACK, _T("RK100_EVT_SET_CAM_ImagParam_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_D2NR, _T("RK100_EVT_SET_CAM_D2NR"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_D2NR_ACK, _T("RK100_EVT_SET_CAM_D2NR_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_Preset_PowOnRecall, _T("RK100_EVT_SET_CAM_Preset_PowOnRecall"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_Preset_PowOnRecall_ACK, _T("RK100_EVT_SET_CAM_Preset_PowOnRecall_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_GET_CAM_WB, _T("RK100_EVT_GET_CAM_WB"));
    RKCMAPPING_HELPER( RK100_EVT_GET_CAM_WB_ACK, _T("RK100_EVT_GET_CAM_WB_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_OUTPUT_FORMAT, _T("RK100_EVT_SET_CAM_OUTPUT_FORMAT"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_OUTPUT_FORMAT_ACK, _T("RK100_EVT_SET_CAM_OUTPUT_FORMAT_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_Preset_List, _T("RK100_EVT_SET_CAM_Preset_List"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_Preset_List_ACK, _T("RK100_EVT_SET_CAM_Preset_List_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_Preset_Save, _T("RK100_EVT_SET_CAM_Preset_Save"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_Preset_Save_ACK, _T("RK100_EVT_SET_CAM_Preset_Save_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_SHUTTER, _T("RK100_EVT_SET_CAM_SHUTTER"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_SHUTTER_ACK, _T("RK100_EVT_SET_CAM_SHUTTER_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_GAIN, _T("RK100_EVT_SET_CAM_GAIN"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_GAIN_ACK, _T("RK100_EVT_SET_CAM_GAIN_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_D3NR, _T("RK100_EVT_SET_CAM_D3NR"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_D3NR_ACK, _T("RK100_EVT_SET_CAM_D3NR_ACK"));

    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_ID, _T("RK100_EVT_SET_CAM_ID"));
    RKCMAPPING_HELPER( RK100_EVT_SET_CAM_ID_ACK, _T("RK100_EVT_SET_CAM_ID_ACK"));

    //摄像机
	RKCMAPPING_HELPER( ev_TpMoonCamInfo_Nty, _T("ev_TpMoonCamInfo_Nty"));
	RKCMAPPING_HELPER( ev_TpCamSelect_Cmd, _T("ev_TpCamSelect_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamSelect_Ind, _T("ev_TpCamSelect_Ind"));
	RKCMAPPING_HELPER( ev_TpCamSelect_Nty, _T("ev_TpCamSelect_Nty"));
	RKCMAPPING_HELPER( ev_CamParaSynchronize_Cmd, _T("ev_CamParaSynchronize_Cmd"));
	RKCMAPPING_HELPER( ev_CamParaSynchronize_Ind, _T("ev_CamParaSynchronize_Ind"));
	RKCMAPPING_HELPER( ev_TpMechanismSelect_Nty, _T("ev_TpMechanismSelect_Nty"));
	RKCMAPPING_HELPER( ev_TpMechVer_Nty, _T("ev_TpMechVer_Nty"));
	RKCMAPPING_HELPER( ev_TpMechanismSelect_Cmd, _T("ev_TpMechanismSelect_Cmd"));
	RKCMAPPING_HELPER( ev_TpMechanismSelect_Ind, _T("ev_TpMechanismSelect_Ind"));
	RKCMAPPING_HELPER( ev_TpCamSetZoonStart_Cmd, _T("ev_TpCamSetZoonStart_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamSetZoonStart_Ind, _T("ev_TpCamSetZoonStart_Ind"));
	RKCMAPPING_HELPER( ev_TpCamSetZoonStop_Cmd, _T("ev_TpCamSetZoonStop_Cmd"));	
	RKCMAPPING_HELPER( ev_TpCamSetZoonStop_Ind, _T("ev_TpCamSetZoonStop_Ind"));
	RKCMAPPING_HELPER( ev_TpCamSetDrectZoon_Cmd, _T("ev_TpCamSetDrectZoon_Cmd"));	
	RKCMAPPING_HELPER( ev_TpCamSetDrectZoon_Ind, _T("ev_TpCamSetDrectZoon_Ind"));	
	RKCMAPPING_HELPER( ev_TpCamFocusMode_Cmd, _T("ev_TpCamFocusMode_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamFocusMode_Ind, _T("ev_TpCamFocusMode_Ind"));
	RKCMAPPING_HELPER( ev_TpCamFocusNear_Cmd, _T("ev_TpCamFocusNear_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamFocusStop_Cmd, _T("ev_TpCamFocusStop_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamFocusFar_Cmd, _T("ev_TpCamFocusFar_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamFocusNear_Ind, _T("ev_TpCamFocusNear_Ind"));
	RKCMAPPING_HELPER( ev_TpCamFocusStop_Ind, _T("ev_TpCamFocusStop_Ind"));
	RKCMAPPING_HELPER( ev_TpCamFocusFar_Ind, _T("ev_TpCamFocusFar_Ind"));
	RKCMAPPING_HELPER( ev_TpCamExpMode_Cmd, _T("ev_TpCamExpMode_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamExpMode_Ind, _T("ev_TpCamExpMode_Ind"));
	RKCMAPPING_HELPER( ev_TpCamExpAperture_Cmd, _T("ev_TpCamExpAperture_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamExpAperture_Ind, _T("ev_TpCamExpAperture_Ind"));
	RKCMAPPING_HELPER( ev_TpCamExpSOrThShutter_Cmd, _T("ev_TpCamExpSOrThShutter_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamExpSOrThShutter_Ind, _T("ev_TpCamExpSOrThShutter_Ind"));
	RKCMAPPING_HELPER( ev_TpCamExpGain_Cmd, _T("ev_TpCamExpGain_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamExpGain_Ind, _T("ev_TpCamExpGain_Ind"));
	RKCMAPPING_HELPER( ev_TpCamWhiteBalanceMode_Cmd, _T("ev_TpCamWhiteBalanceMode_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamWhiteBalanceMode_Ind, _T("ev_TpCamWhiteBalanceMode_Ind"));
	RKCMAPPING_HELPER( ev_TpCamWhiteBalanceRGain_Cmd, _T("ev_TpCamWhiteBalanceRGain_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamWhiteBalanceRGain_Ind, _T("ev_TpCamWhiteBalanceRGain_Ind"));
	RKCMAPPING_HELPER( ev_TpCamWhiteBalanceBGain_Cmd, _T("ev_TpCamWhiteBalanceBGain_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamWhiteBalanceBGain_Ind, _T("ev_TpCamWhiteBalanceBGain_Ind"));
	RKCMAPPING_HELPER( ev_TpCamImagePara_Cmd, _T("ev_TpCamImagePara_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamImagePara_Ind, _T("ev_TpCamImagePara_Ind"));
	RKCMAPPING_HELPER( ev_TpCamSetGamma_Cmd, _T("ev_TpCamSetGamma_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamSetGamma_Ind, _T("ev_TpCamSetGamma_Ind"));
	RKCMAPPING_HELPER( ev_TpCamBackLight_Cmd, _T("ev_TpCamBackLight_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamBackLight_Ind, _T("ev_TpCamBackLight_Ind"));
	RKCMAPPING_HELPER( ev_TpImageDistortCorrect_Cmd, _T("ev_TpImageDistortCorrect_Cmd"));
	RKCMAPPING_HELPER( ev_TpImageDistortCorrect_Ind, _T("ev_TpImageDistortCorrect_Ind"));	
	RKCMAPPING_HELPER( ev_TpCamReduNoise_Cmd, _T("ev_TpCamReduNoise_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamReduNoise_Ind, _T("ev_TpCamReduNoise_Ind"));
	RKCMAPPING_HELPER( ev_TpSetCam2DNoiseLevle_Cmd, _T("ev_TpSetCam2DNoiseLevle_cmd"));
	RKCMAPPING_HELPER( ev_TpSetCam2DNoiseLevle_Ind, _T("ev_TpSetCam2DNoiseLevle_Ind"));	
	RKCMAPPING_HELPER( ev_TpSetCam3DNoiseLevle_Cmd, _T("ev_TpSetCam3DNoiseLevle_cmd"));
	RKCMAPPING_HELPER( ev_TpSetCam3DNoiseLevle_Ind, _T("ev_TpSetCam3DNoiseLevle_Ind"));
	RKCMAPPING_HELPER( ev_TpCamInitPreset_Cmd, _T("ev_TpCamInitPreset_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamInitPreset_Ind, _T("ev_TpCamInitPreset_Ind"));
	RKCMAPPING_HELPER( ev_tpMoonReboot_Cmd, _T("ev_tpMoonReboot_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamPreSet_Nty, _T("ev_TpCamPreSet_Nty"));
	RKCMAPPING_HELPER( ev_TpCamPreSet_Cmd, _T("ev_TpCamPreSet_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamPreSet_Ind, _T("ev_TpCamPreSet_Ind"));
	RKCMAPPING_HELPER( ev_TpCamPreReset_Cmd, _T("ev_TpCamPreReset_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamPreReset_Ind, _T("ev_TpCamPreReset_Ind"));
	RKCMAPPING_HELPER( ev_TpCamPreModify_Cmd, _T("ev_TpCamPreModify_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamPreModify_Ind, _T("ev_TpCamPreModify_Ind"));
	RKCMAPPING_HELPER( ev_TpCamPreRecall_Cmd, _T("ev_TpCamPreRecall_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamPreRecall_Ind, _T("ev_TpCamPreRecall_Ind"));
	RKCMAPPING_HELPER( ev_TpCamParamUpload_Cmd, _T("ev_TpCamParamUpload_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamParamUpload_Ind, _T("ev_TpCamParamUpload_Ind"));
	RKCMAPPING_HELPER( ev_TpCamParamUpload_Nty, _T("ev_TpCamParamUpload_Nty"));
	RKCMAPPING_HELPER( ev_TpMoonUpgrade_Ind, _T("ev_TpMoonUpgrade_Ind"));
	RKCMAPPING_HELPER( ev_TpMoonUpgrade_Cmd, _T("ev_TpMoonUpgrade_Cmd"));	
	RKCMAPPING_HELPER( ev_CamUpgrade_Cmd, _T("ev_CamUpgrade_Cmd"));	
	RKCMAPPING_HELPER( ev_CamUpgrade_Ind, _T("ev_CamUpgrade_Ind"));
	RKCMAPPING_HELPER( ev_TpCamParamDefault_Cmd, _T("ev_TpCamParamDefault_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamParamDefault_Ind, _T("ev_TpCamParamDefault_Ind"));	
	RKCMAPPING_HELPER( ev_TpSetRefer_Cmd, _T("ev_TpSetRefer_Cmd"));	
	RKCMAPPING_HELPER( ev_TpSetRefer_Ind, _T("ev_TpSetRefer_Ind"));
	RKCMAPPING_HELPER( ev_TpSetRefer_Nty, _T("ev_TpSetRefer_Nty"));	
	RKCMAPPING_HELPER( ev_TpFlatTurn_Cmd, _T("ev_TpFlatTurn_Cmd"));	
	RKCMAPPING_HELPER( ev_TpFlatTurn_Ind, _T("ev_TpFlatTurn_Ind"));
	RKCMAPPING_HELPER( ev_TpFlatTurn_Nty, _T("ev_TpFlatTurn_Nty"));
	RKCMAPPING_HELPER( ev_TpDisortSwitch_Cmd, _T("ev_TpDisortSwitch_Cmd"));
	RKCMAPPING_HELPER( ev_TpDisortSwitch_Ind, _T("ev_TpDisortSwitch_Ind"));
	RKCMAPPING_HELPER( ev_TpSetDisort_Cmd, _T("ev_TpSetDisort_Cmd"));
	RKCMAPPING_HELPER( ev_TpSetDisort_Ind, _T("ev_TpSetDisort_Ind"));
	RKCMAPPING_HELPER( ev_TpCamSnapshot_Cmd, _T("ev_TpCamSnapshot_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamSnapshot_Ind, _T("ev_TpCamSnapshot_Ind"));
	RKCMAPPING_HELPER( ev_TPSetColorRGB_Cmd, _T("ev_TPSetColorRGB_Cmd"));
	RKCMAPPING_HELPER( ev_TPSetColorRGB_Ind, _T("ev_TPSetColorRGB_Ind"));
	RKCMAPPING_HELPER( ev_TPAutoSetColorConstancy_Cmd, _T("ev_TPAutoSetColorConstancy_Cmd"));
	RKCMAPPING_HELPER( ev_TPAutoSetColorConstancy_Ind, _T("ev_TPAutoSetColorConstancy_Ind"));	
	RKCMAPPING_HELPER( ev_TPDirectSetColorRGB_Cmd, _T("ev_TPDirectSetColorRGB_Cmd"));
	RKCMAPPING_HELPER( ev_TPDirectSetColorRGB_Ind, _T("ev_TPDirectSetColorRGB_Ind"));
	RKCMAPPING_HELPER( ev_TPChangeSideRGB_Nty, _T("ev_TPChangeSideRGB_Nty"));
//	RKCMAPPING_HELPER( ev_TPRectInfo_Nty, _T("ev_TPRectInfo_Nty"));
	RKCMAPPING_HELPER( ev_TPChooseRectangle_Cmd, _T("ev_TPChooseRectangle_Cmd"));
	RKCMAPPING_HELPER( ev_TPChooseRectangle_Ind, _T("ev_TPChooseRectangle_Ind"));
	RKCMAPPING_HELPER( ev_TPChangeDistor_Cmd, _T("ev_TPChangeDistor_Cmd"));
	RKCMAPPING_HELPER( ev_TPChangeDistor_Ind, _T("ev_TPChangeDistor_Ind"));
	RKCMAPPING_HELPER( ev_TPDirectSetDistor_Cmd, _T("ev_TPDirectSetDistor_Cmd"));
	RKCMAPPING_HELPER( ev_TPDirectSetDistor_Ind, _T("ev_TPDirectSetDistor_Ind"));	
	RKCMAPPING_HELPER( ev_TPMoonShowRectRegion_Cmd, _T("ev_TPMoonShowRectRegion_Cmd"));
	RKCMAPPING_HELPER( ev_TPMoonShowRectRegion_Ind, _T("ev_TPMoonShowRectRegion_Ind"));
	RKCMAPPING_HELPER( ev_TpColorSwich_Cmd, _T("ev_TpColorSwich_Cmd"));
	RKCMAPPING_HELPER( ev_TpColorSwich_Ind, _T("ev_TpColorSwich_Ind"));
//	RKCMAPPING_HELPER( ev_TPMoonShowRectRegion_Nty, _T("ev_TPMoonShowRectRegion_Nty"));
	RKCMAPPING_HELPER( ev_TpSecDefault_Nty, _T("ev_TpSecDefault_Nty"));
	RKCMAPPING_HELPER( ev_TpSecBoundary_Nty, _T("ev_TpSecBoundary_Nty"));
    RKCMAPPING_HELPER( ev_TpFpgaDelayCorrect_Cmd, _T("ev_TpFpgaDelayCorrect_Cmd"));
    RKCMAPPING_HELPER( ev_TpFpgaDelayCorrect_Ind, _T("ev_TpFpgaDelayCorrect_Ind"));
    RKCMAPPING_HELPER( ev_TpFpgaDelayCorrect_Nty, _T("ev_TpFpgaDelayCorrect_Nty"));

	//系统设置
	RKCMAPPING_HELPER( ev_TpMoonVerInfo_Nty, _T("ev_TpMoonVerInfo_Nty"));
	RKCMAPPING_HELPER( ev_TpCamOutPortInfo_Nty, _T("ev_TpCamOutPortInfo_Nty"));
	RKCMAPPING_HELPER( ev_TpCamImageAdjust_Nty, _T("ev_TpCamImageAdjust_Nty"));
	RKCMAPPING_HELPER( ev_TpMoonCfgEthnet_Ind, _T("ev_TpMoonCfgEthnet_Ind"));
	RKCMAPPING_HELPER( ev_TpCamOutPortInfo_Cmd, _T("ev_TpCamOutPortInfo_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamOutPortInfo_Ind, _T("ev_TpCamOutPortInfo_Ind"));
	RKCMAPPING_HELPER( ev_TpCamImageAdjust_Cmd, _T("ev_TpCamImageAdjust_Cmd"));
	RKCMAPPING_HELPER( ev_TpCamImageAdjust_Ind, _T("ev_TpCamImageAdjust_Ind"));	
	RKCMAPPING_HELPER( ev_TpMoonCfgEthnet_Cmd, _T("ev_TpMoonCfgEthnet_Cmd"));	
	RKCMAPPING_HELPER( ev_TpSetLVDSBaud_Ind, _T("ev_TpSetLVDSBaud_Ind"));
	RKCMAPPING_HELPER( ev_TpSetLVDSBaud_Nty, _T("ev_TpSetLVDSBaud_Nty"));
}

u16 CRkcMsgDriver::PostMsg(u32 dwType)
{  
    u16 wRet = NO_ERROR;
    u16 wEvent = 0;
    if (TYPE_TPMSG == dwType) 
    {  
        wRet = OspPost(MAKEIID(AID_RKC_APP,0), m_tOspMsg.GetEvent(),m_tOspMsg.GetBody(),m_tOspMsg.GetBodyLen());
    }
    return wRet;
}

void CRkcMsgDriver::OnOspMessageComing(WPARAM wParam, LPARAM lParam)
{
    // 从OSP回调线程提取消息
    CRkcMsgHandler *pHandler = CRkcMsgHandler::GetMsgHandler();
    if (!pHandler) 
    {
        return;
    }
    CRkcMsgQueue cMsgQue;
    pHandler->PopAllMsg(cMsgQue);
    // 分发消息
    while(!cMsgQue.IsEmpty())
    {
        const CMessage &cMsg = cMsgQue.Front();

        //打印输出
        CString strEvent = CRkcPrintCtrl::GetPrintCtrl()->GetEventDescribe(cMsg.event); 

        PrtRkcMsg(cMsg.event, "\n[RkcLib]: 收到消息:%s(%u).", strEvent,cMsg.event);

        // 检索消息分发表
        vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
        BOOL bFind = FALSE;
        for(; itr != m_vpDispEvent.end(); itr++)
        {
            if ((*itr)->HasRegEvent(cMsg.event)) 
            {
                (*itr)->DispEvent(cMsg);
                bFind = TRUE;
            }
        }
        if (!bFind) 
        {	  	 
            PrtRkcMsg( "[RkcLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n", strEvent, cMsg.event);		
        }

        cMsgQue.Pop();
    }
}

