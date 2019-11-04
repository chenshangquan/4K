#ifndef _LOCAL_XML_TYPE_H_
#define _LOCAL_XML_TYPE_H_

#include "tpcommonxmltype.h"

const char XmlLocalTypeVersion[] = "2019-10-30 16:49:5";

//Local Data struct type begin
enum EmXDataLocalType
{
	emx_EmTpMcuSelView = _placeholder_emxEnumTptypeEnd, //Local枚举类型数据开始,紧接Tp枚举结束
	emx_EmTpColor,
	emx_EmTpSize,
	emx_EmTpLogoStyle,
	emx_EmTpStyle,
	emx_emTpTransparency,
	emx_EmTVModle,
	emx_EmPanCamBright,
	emx_EmTpWorkMode,
	emx_EmTpVEncCodecType,
	emx_EmTpChannelHandle,
	emx_EmTpVideoLoopTest,
	emx_EmTpDualIdleReason,
	emx_EmTpPadMaxCap,
	emx_EmTpIpNameNatSyn,
	emx_EmCnsHduRunStatus,
	emx_EmCnsHduPlayNackReason,
	emx_EmCnsHduSetVolRes,
	emx_EmCnsHduChangeChanModeRes,
	emx_EmEthState,
	emx_TTPMCUSelViewReq = _placeholder_emxTpStructTypeend, //Local数据结构类型数据开始,紧接Tp结构体结束
	emx_TTPShowLogo,
	emx_TTPLogo,
	emx_TTPLogoInfo,
	emx_TTPShowBanner,
	emx_TTPBanner,
	emx_TTPBannerInfo,
	emx_TTPVideoSourceName,
	emx_TTPVideoInfoTool,
	emx_TCentreTVCfg,
	emx_TCentreCurInfo,
	emx_TPanCamName,
	emx_TPanCamGroupName,
	emx_TPanCamInfo,
	emx_TDualScreenInfo,
	emx_TTPVAdapterInfo,
	emx_TTPAutoTestLoopInfo,
	emx_TTPInterFaceTestInfo,
	emx_TTPCapMap,
	emx_TTPCapPack,
	emx_TTPVideoLoopTestInfo,
	emx_TTpConfEpInfo,
	emx_TTpHduUnitPlayInfo,
	emx_TTpHduPlanUnit,
	emx_TTpHduPlanPackData,
	emx_TTpHduPlayReq,
	emx_TTpHduBaseInfo,
	emx_TTpHduSetVolInfo,
	emx_TTpHduChanModeSetInfo,
	emx_TTpRollCallList,
	emx_TTpConfRollCallInfo,
	emx_TTpRollCallNextEpInfo,
	emx_TTpAudMixList,
	emx_TTpAudMixInfo,
	emx_TTpAudMixModeCmdRes,
	emx_TTpAudMixListCmd,
	emx_TTpAudMixListCmdRes,
	emx_TTpUpdataRollCallList,
	emx_TTpUpdataRollCallListRes,
	emx_TTpRollCallPresentStateEpInfo,
	emx_TTpRollCallPresentStateMsg,
_placeholder_emxDataTypeEnd = emxDataTypeEnd, //类型定义结束
};
//Local Data struct type end
 
#define TpEnumIdString(type, index) index, GetTpEnumString(emx_##type, index)
#define TpEnumString(type, index) GetTpEnumString(emx_##type, index)
s8* GetTpEnumString(u16 wType, u16 wIndex);
TXDATAINFO** CombineEnumDateInfo(void);
TXDATAINFO** CombineStructDateInfo(void);
void CombineEnumXDescripTbl(void);

#endif //_LOCAL_XML_TYPE_H_
