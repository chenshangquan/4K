#ifndef _TP_COMMON_XML_STRUCT_H_
#define _TP_COMMON_XML_STRUCT_H_

#include "xmlengine.h"
#include "msgmgr.h"
#include "tpcommontype.h"
#include "tpcommonstruct.h"
#include "tpcommonxmltype.h"

const char XmlTpStructVersion[] = "2019-10-30 16:49:1";

#define XML_TP_TYPE_NUM      333
#define XML_TP_STRUCT_NUM    439

#define ENUMTYPE( type )\
	const TXDATAINFO type##membertable[] = {#type,emx_##type,"enum",4,1,0,0,(char*)#type};

#define TYPESTRUCT_BEGIN( s )\
	const TXDATAINFO s##membertable[]={
#define TYPESTRUCT_MEMBER( s,type ,m )\
	{#s,emx_##type,#type,sizeof(type),XML_SizeOfMember(s,m)/sizeof(type),0,XML_OffSetOf(s,m),(char*)#m},
#define TYPESTRUCT_MATRIX( s,type ,m )\
	{#s,emx_##type,#type,sizeof(type),XML_SizeOfMember(s,m)/sizeof(type),XML_SizeOfMatrix(s,type,m),XML_OffSetOf(s,m),(char*)#m},
#define TYPESTRUCT_END( s )\
	{#s,emxDataTypeEnd,0,sizeof(s),0,0,0,#s}};

ENUMTYPE(EmTPDevRegUpdateSer);
ENUMTYPE(EmTPUpdateType);
ENUMTYPE(EmWiFiLinkStat);
ENUMTYPE(EmWiFiSelType);
ENUMTYPE(EmWiFiNetType);
ENUMTYPE(EmWiFiEncryptType);
ENUMTYPE(EmWiFiEncryptArithmetic);
ENUMTYPE(EmVODRejCode);
ENUMTYPE(EmVODState);
ENUMTYPE(EmTextAlign);
ENUMTYPE(EmRollMode);
ENUMTYPE(EmRollSpeed);
ENUMTYPE(EmStopBits);
ENUMTYPE(EmParityCheck);
ENUMTYPE(EmSerialType);
ENUMTYPE(EmLanguage);
ENUMTYPE(EmConfProtocol);
ENUMTYPE(EmEncodeMode);
ENUMTYPE(EmLostPackageRestore);
ENUMTYPE(EmMatrixType);
ENUMTYPE(EmDualVideoShowMode);
ENUMTYPE(EmDisplayRatio);
ENUMTYPE(EmVideoType);
ENUMTYPE(EmVideoStandard);
ENUMTYPE(EmVideoInterface);
ENUMTYPE(EmMtVideoPort);
ENUMTYPE(EmTripMode);
ENUMTYPE(EmLabelType);
ENUMTYPE(EmDLProtocol);
ENUMTYPE(EmAuthenticationType);
ENUMTYPE(EmFrameUnitType);
ENUMTYPE(EmMediaType);
ENUMTYPE(EmVideoFormat);
ENUMTYPE(EmAudioFormat);
ENUMTYPE(EmVideoResolution);
ENUMTYPE(EmQoS);
ENUMTYPE(EmTOS);
ENUMTYPE(EmSite);
ENUMTYPE(EmChanType);
ENUMTYPE(EmCodecComponent);
ENUMTYPE(EmMtModel);
ENUMTYPE(EmFileSys);
ENUMTYPE(EmEncryptArithmetic);
ENUMTYPE(EmAction);
ENUMTYPE(EmOptRet);
ENUMTYPE(EmConfMode);
ENUMTYPE(EmMtAddrType);
ENUMTYPE(EmDirection);
ENUMTYPE(EmCallState);
ENUMTYPE(EmCallSiteState);
ENUMTYPE(EmTransMode);
ENUMTYPE(EmMtInstType);
ENUMTYPE(EmVMPStyle);
ENUMTYPE(EmVMPMmbType);
ENUMTYPE(EmSMSType);
ENUMTYPE(EmMtFile);
ENUMTYPE(EmCallRate);
ENUMTYPE(EmPCCapFormat);
ENUMTYPE(EmPiPMode);
ENUMTYPE(EmDVBComponent);
ENUMTYPE(EmUIPosion);
ENUMTYPE(EmCallDisconnectReason);
ENUMTYPE(EmMCMode);
ENUMTYPE(EmInnerVMPStyle);
ENUMTYPE(EmVMPComponent);
ENUMTYPE(EmCapType);
ENUMTYPE(EmPPPoEState);
ENUMTYPE(EmDhcpState);
ENUMTYPE(EmAddrGroupOptType);
ENUMTYPE(EmHotKeyType);
ENUMTYPE(EmMtOSType);
ENUMTYPE(EmFxoState);
ENUMTYPE(EmMtLoudspeakerVal);
ENUMTYPE(EmNetType);
ENUMTYPE(EmSysRunSuccessFlag);
ENUMTYPE(EmMcuNtfMsgType);
ENUMTYPE(EmAutoTestType);
ENUMTYPE(EmGKRegFailedReason);
ENUMTYPE(EmSleepState);
ENUMTYPE(EmMtAppName);
ENUMTYPE(HD_PORT_MASK);
ENUMTYPE(EmHDAudPortIn);
ENUMTYPE(EmHDAudPortOut);
ENUMTYPE(EmLogStatus);
ENUMTYPE(EmLogExportResult);
ENUMTYPE(EmFecModeType);
ENUMTYPE(EmLabelPosType);
ENUMTYPE(EmMtcBoxCallIndex);
ENUMTYPE(EmSipRegFailedReason);
ENUMTYPE(EMtRecChnnlState);
ENUMTYPE(EMtRecChnnlType);
ENUMTYPE(EMtRecMode);
ENUMTYPE(EMtRecEnum);
ENUMTYPE(EmMtRegResult);
ENUMTYPE(EmTpRet);
ENUMTYPE(EmTpHduPlayNackReason);
ENUMTYPE(EmTpHduSetVolRes);
ENUMTYPE(EmTpLoginUmsRet);
ENUMTYPE(EmTpAliasType);
ENUMTYPE(EmTpOprType);
ENUMTYPE(EmConfAddEpRet);
ENUMTYPE(EmTpIFrameCheckType);
ENUMTYPE(EmTPEncryptType);
ENUMTYPE(EmQtEncryptFrequency);
ENUMTYPE(EmTPQTReason);
ENUMTYPE(EmTPRcvAlignType);
ENUMTYPE(EmCnsCallReason);
ENUMTYPE(EmTPChannelReason);
ENUMTYPE(EmTpCnsType);
ENUMTYPE(EmTpCnsRegUms);
ENUMTYPE(EmTpConfTemplateRet);
ENUMTYPE(EmTpStartConfRet);
ENUMTYPE(EmTpApplySpeakerRet);
ENUMTYPE(EmTpDropConfRet);
ENUMTYPE(EmTpApplySpeakRet);
ENUMTYPE(EmUmsConfNodeState);
ENUMTYPE(EmFlowCtrlOpr);
ENUMTYPE(EMBrdType);
ENUMTYPE(EMEqpType);
ENUMTYPE(EMEqpModleType);
ENUMTYPE(EMOsType);
ENUMTYPE(EMVmpStyle);
ENUMTYPE(EmTpVideoFormat);
ENUMTYPE(EmTpEncodeMode);
ENUMTYPE(EmTpVideoQualityLevel);
ENUMTYPE(EmTpCallLevel);
ENUMTYPE(EmTpVideoResolution);
ENUMTYPE(EmTpMediaType);
ENUMTYPE(EmTpPCCapFormat);
ENUMTYPE(EmTpCodecComponent);
ENUMTYPE(EmTpAudioFormat);
ENUMTYPE(EmTpLostPackageRestore);
ENUMTYPE(EmTpCallMode);
ENUMTYPE(EmTpConnectionType);
ENUMTYPE(EmTpConfProtocol);
ENUMTYPE(EmTPAddrType);
ENUMTYPE(EmTPEndpointType);
ENUMTYPE(EmTPSipLevel);
ENUMTYPE(EmCALLSTATE);
ENUMTYPE(EmCallType);
ENUMTYPE(EmTPVideoType);
ENUMTYPE(EmTPVideoPort);
ENUMTYPE(EmTPCNSInfoRst);
ENUMTYPE(EmTPRegResult);
ENUMTYPE(EmCnMtRegResult);
ENUMTYPE(EmCnModel);
ENUMTYPE(EmFocusMode);
ENUMTYPE(EmSensitivity);
ENUMTYPE(EmFocus);
ENUMTYPE(EmZoom);
ENUMTYPE(EmZoomStatus);
ENUMTYPE(EmCnAction);
ENUMTYPE(EmOSDShow);
ENUMTYPE(EmWBMode);
ENUMTYPE(EmExpMode);
ENUMTYPE(EmGain);
ENUMTYPE(EmShutSpd);
ENUMTYPE(EmAntiFlicker);
ENUMTYPE(EmSpotLighet);
ENUMTYPE(EmBackLightType);
ENUMTYPE(EmWideDynamics);
ENUMTYPE(EmPicSceMode);
ENUMTYPE(EmGamma);
ENUMTYPE(EmStmClean);
ENUMTYPE(Em3DNR);
ENUMTYPE(EmPicEffect);
ENUMTYPE(EmPicFlip);
ENUMTYPE(EmPicMode);
ENUMTYPE(EmResolution);
ENUMTYPE(EmBaudRate);
ENUMTYPE(EmCamPowerMode);
ENUMTYPE(EmCenSchMode);
ENUMTYPE(EmSonyIris);
ENUMTYPE(EmMoon904K60Iris);
ENUMTYPE(EmCamType);
ENUMTYPE(EmCamCfgType);
ENUMTYPE(EmTvPowerMode);
ENUMTYPE(EmTvSrcPowerMode);
ENUMTYPE(EmTVAudVisMode);
ENUMTYPE(EmTVDisplayMode);
ENUMTYPE(EmTVInputSelect);
ENUMTYPE(EmDCamWBMode);
ENUMTYPE(EmDCamAFMode);
ENUMTYPE(EmDCamPower);
ENUMTYPE(EmDCamZoom);
ENUMTYPE(EmDCamPresetNum);
ENUMTYPE(EmDCamRecallNum);
ENUMTYPE(EmDCamGain);
ENUMTYPE(EmDCamShutSpd);
ENUMTYPE(EmDCamIris);
ENUMTYPE(EmSchPower);
ENUMTYPE(EmSchLight);
ENUMTYPE(EmSchMidLight);
ENUMTYPE(EmSchScrLight);
ENUMTYPE(EmSchCameraAndTVPower);
ENUMTYPE(EmSchArgus);
ENUMTYPE(EmCentreACPower);
ENUMTYPE(EmCentreACAirVol);
ENUMTYPE(EmCentreACMode);
ENUMTYPE(EmCurAction);
ENUMTYPE(EmCurChannelMode);
ENUMTYPE(EmSchGatewayType);
ENUMTYPE(EmTpMixStatus);
ENUMTYPE(EmTPDualReason);
ENUMTYPE(EmTPPayloadType);
ENUMTYPE(EmTPPosStatus);
ENUMTYPE(EmTPPollResult);
ENUMTYPE(EmPollStat);
ENUMTYPE(EmTPViewResult);
ENUMTYPE(EmTPViewLocalResult);
ENUMTYPE(EmTPDisOprType);
ENUMTYPE(EMPosPic);
ENUMTYPE(EMDSCREATETYPE);
ENUMTYPE(EmTPAddDualRcvResult);
ENUMTYPE(EmTPDeleteDualRcvResult);
ENUMTYPE(EmTPMtModel);
ENUMTYPE(EmDsType);
ENUMTYPE(EmCnAudioMixID);
ENUMTYPE(EmGetRegInfoType);
ENUMTYPE(EmGetRegInfoOpr);
ENUMTYPE(EmTPChanType);
ENUMTYPE(EmTPAACSampleFreq);
ENUMTYPE(EmTPG7221Rate);
ENUMTYPE(EmTPAACChnlCfg);
ENUMTYPE(EmTPTpApplySpeakerRet);
ENUMTYPE(EmTPChanSubType);
ENUMTYPE(EmMakeCallType);
ENUMTYPE(EmTpRegType);
ENUMTYPE(EmDisListOprType);
ENUMTYPE(EmDisListOprReslt);
ENUMTYPE(EmVgaType);
ENUMTYPE(EmDualInputType);
ENUMTYPE(EmDualOutputType);
ENUMTYPE(EmVgaSwitchResult);
ENUMTYPE(EmVgaSwitchReason);
ENUMTYPE(EmCnState);
ENUMTYPE(EmTPCapSign);
ENUMTYPE(EmSwitchState);
ENUMTYPE(EmTpBoardRet);
ENUMTYPE(EmHduOutPort);
ENUMTYPE(EmHduZoomRate);
ENUMTYPE(EmHduOutMode);
ENUMTYPE(EmHduShowMode);
ENUMTYPE(EmModifyNMServerRet);
ENUMTYPE(EmModifyVcrRet);
ENUMTYPE(EmModifyHduRet);
ENUMTYPE(EmUpdateHduRet);
ENUMTYPE(EmMPCodec);
ENUMTYPE(EmTPHDAudPortIn);
ENUMTYPE(EmTPHDDualAudPortIn);
ENUMTYPE(EmTPHDAudPortOut);
ENUMTYPE(EmTPMtVideoPort);
ENUMTYPE(EmTPMtVideoOutPort);
ENUMTYPE(EmTPAutoTestType);
ENUMTYPE(EmTPHduRunStatus);
ENUMTYPE(EmTPLoudspeakerVal);
ENUMTYPE(EmTPFrameUnitType);
ENUMTYPE(EmTPVideoStandard);
ENUMTYPE(EmTPLabelType);
ENUMTYPE(EmTPLabelPosType);
ENUMTYPE(EmTPDualVideoShowMode);
ENUMTYPE(EmTPDisplayRatio);
ENUMTYPE(EmTPFecModeType);
ENUMTYPE(EmTPNetType);
ENUMTYPE(EmTPEqualizerRate);
ENUMTYPE(EmTPPIPMode);
ENUMTYPE(EmTPDVIMode);
ENUMTYPE(EmTPMCMode);
ENUMTYPE(EmCnsUpdateState);
ENUMTYPE(EmTPCnLoginUpdateRet);
ENUMTYPE(EmTPFileSrvUsedVersion);
ENUMTYPE(EmTPFileSrvFileType);
ENUMTYPE(EmTPOSType);
ENUMTYPE(EmMPAudEncCodec);
ENUMTYPE(EmToolType);
ENUMTYPE(EmProducetestType);
ENUMTYPE(EmMdyRecFileRes);
ENUMTYPE(EmUseReccorderRes);
ENUMTYPE(EmRecorderType);
ENUMTYPE(EmConfRecState);
ENUMTYPE(EmTpProfile);
ENUMTYPE(EmTPHandleCfgType);
ENUMTYPE(EmTpCodecType);
ENUMTYPE(EmToolState);
ENUMTYPE(EmTPAudPlayMode);
ENUMTYPE(EmTPAudDualInMode);
ENUMTYPE(EmTPDualType);
ENUMTYPE(EmTPDsNode);
ENUMTYPE(EMScreenLooked);
ENUMTYPE(EmUmsVmpStyle);
ENUMTYPE(EmVmpEncMode);
ENUMTYPE(EmVmpShowMode);
ENUMTYPE(EmVmpRes);
ENUMTYPE(EmAudPlayMode);
ENUMTYPE(EmResetAudMode);
ENUMTYPE(EmCheckAudPak);
ENUMTYPE(EmViewEpType);
ENUMTYPE(EmViewRetReason);
ENUMTYPE(EmUIType);
ENUMTYPE(EmGetVidRes);
ENUMTYPE(EmBrdVmpRet);
ENUMTYPE(EmBrdVmpStat);
ENUMTYPE(EmRervesVmpRet);
ENUMTYPE(EmCnmpLogType);
ENUMTYPE(EmCnmpLogCt);
ENUMTYPE(EmAudAecType);
ENUMTYPE(EmGetVidType);
ENUMTYPE(EmVidEncResizeMode);
ENUMTYPE(EmTpVendorID);
ENUMTYPE(EMScreenObj);
ENUMTYPE(EmTpBannerTransparency);
ENUMTYPE(EmTpBannerType);
ENUMTYPE(EmTpLogoType);
ENUMTYPE(EmTpSnapShotType);
ENUMTYPE(EmTpCtrlMode);
ENUMTYPE(EmDiscussOprRes);
ENUMTYPE(EmDiscussRspRet);
ENUMTYPE(EmDCamProType);
ENUMTYPE(EmIconType);
ENUMTYPE(EmAudMixType);
ENUMTYPE(EmAudExtend);
ENUMTYPE(EmRollCallRspRet);
ENUMTYPE(EmAudMixMode);
ENUMTYPE(EmAudMixListOpr);
ENUMTYPE(EmAudMixRes);
ENUMTYPE(EmRollCallPresentState);
ENUMTYPE(EmVidMergeStyle);
ENUMTYPE(EmMeetingRoomSize);
ENUMTYPE(EmAudGroupIndex);
ENUMTYPE(EmUpdateFrequency);
ENUMTYPE(EmQCamProType);
ENUMTYPE(EmP2PCallStrategyLevel);
ENUMTYPE(EMDS_SUBTYPE);

TXDATAINFO* g_tTpEnumData[]={
	(TXDATAINFO*)EmTPDevRegUpdateSermembertable,
	(TXDATAINFO*)EmTPUpdateTypemembertable,
	(TXDATAINFO*)EmWiFiLinkStatmembertable,
	(TXDATAINFO*)EmWiFiSelTypemembertable,
	(TXDATAINFO*)EmWiFiNetTypemembertable,
	(TXDATAINFO*)EmWiFiEncryptTypemembertable,
	(TXDATAINFO*)EmWiFiEncryptArithmeticmembertable,
	(TXDATAINFO*)EmVODRejCodemembertable,
	(TXDATAINFO*)EmVODStatemembertable,
	(TXDATAINFO*)EmTextAlignmembertable,
	(TXDATAINFO*)EmRollModemembertable,
	(TXDATAINFO*)EmRollSpeedmembertable,
	(TXDATAINFO*)EmStopBitsmembertable,
	(TXDATAINFO*)EmParityCheckmembertable,
	(TXDATAINFO*)EmSerialTypemembertable,
	(TXDATAINFO*)EmLanguagemembertable,
	(TXDATAINFO*)EmConfProtocolmembertable,
	(TXDATAINFO*)EmEncodeModemembertable,
	(TXDATAINFO*)EmLostPackageRestoremembertable,
	(TXDATAINFO*)EmMatrixTypemembertable,
	(TXDATAINFO*)EmDualVideoShowModemembertable,
	(TXDATAINFO*)EmDisplayRatiomembertable,
	(TXDATAINFO*)EmVideoTypemembertable,
	(TXDATAINFO*)EmVideoStandardmembertable,
	(TXDATAINFO*)EmVideoInterfacemembertable,
	(TXDATAINFO*)EmMtVideoPortmembertable,
	(TXDATAINFO*)EmTripModemembertable,
	(TXDATAINFO*)EmLabelTypemembertable,
	(TXDATAINFO*)EmDLProtocolmembertable,
	(TXDATAINFO*)EmAuthenticationTypemembertable,
	(TXDATAINFO*)EmFrameUnitTypemembertable,
	(TXDATAINFO*)EmMediaTypemembertable,
	(TXDATAINFO*)EmVideoFormatmembertable,
	(TXDATAINFO*)EmAudioFormatmembertable,
	(TXDATAINFO*)EmVideoResolutionmembertable,
	(TXDATAINFO*)EmQoSmembertable,
	(TXDATAINFO*)EmTOSmembertable,
	(TXDATAINFO*)EmSitemembertable,
	(TXDATAINFO*)EmChanTypemembertable,
	(TXDATAINFO*)EmCodecComponentmembertable,
	(TXDATAINFO*)EmMtModelmembertable,
	(TXDATAINFO*)EmFileSysmembertable,
	(TXDATAINFO*)EmEncryptArithmeticmembertable,
	(TXDATAINFO*)EmActionmembertable,
	(TXDATAINFO*)EmOptRetmembertable,
	(TXDATAINFO*)EmConfModemembertable,
	(TXDATAINFO*)EmMtAddrTypemembertable,
	(TXDATAINFO*)EmDirectionmembertable,
	(TXDATAINFO*)EmCallStatemembertable,
	(TXDATAINFO*)EmCallSiteStatemembertable,
	(TXDATAINFO*)EmTransModemembertable,
	(TXDATAINFO*)EmMtInstTypemembertable,
	(TXDATAINFO*)EmVMPStylemembertable,
	(TXDATAINFO*)EmVMPMmbTypemembertable,
	(TXDATAINFO*)EmSMSTypemembertable,
	(TXDATAINFO*)EmMtFilemembertable,
	(TXDATAINFO*)EmCallRatemembertable,
	(TXDATAINFO*)EmPCCapFormatmembertable,
	(TXDATAINFO*)EmPiPModemembertable,
	(TXDATAINFO*)EmDVBComponentmembertable,
	(TXDATAINFO*)EmUIPosionmembertable,
	(TXDATAINFO*)EmCallDisconnectReasonmembertable,
	(TXDATAINFO*)EmMCModemembertable,
	(TXDATAINFO*)EmInnerVMPStylemembertable,
	(TXDATAINFO*)EmVMPComponentmembertable,
	(TXDATAINFO*)EmCapTypemembertable,
	(TXDATAINFO*)EmPPPoEStatemembertable,
	(TXDATAINFO*)EmDhcpStatemembertable,
	(TXDATAINFO*)EmAddrGroupOptTypemembertable,
	(TXDATAINFO*)EmHotKeyTypemembertable,
	(TXDATAINFO*)EmMtOSTypemembertable,
	(TXDATAINFO*)EmFxoStatemembertable,
	(TXDATAINFO*)EmMtLoudspeakerValmembertable,
	(TXDATAINFO*)EmNetTypemembertable,
	(TXDATAINFO*)EmSysRunSuccessFlagmembertable,
	(TXDATAINFO*)EmMcuNtfMsgTypemembertable,
	(TXDATAINFO*)EmAutoTestTypemembertable,
	(TXDATAINFO*)EmGKRegFailedReasonmembertable,
	(TXDATAINFO*)EmSleepStatemembertable,
	(TXDATAINFO*)EmMtAppNamemembertable,
	(TXDATAINFO*)HD_PORT_MASKmembertable,
	(TXDATAINFO*)EmHDAudPortInmembertable,
	(TXDATAINFO*)EmHDAudPortOutmembertable,
	(TXDATAINFO*)EmLogStatusmembertable,
	(TXDATAINFO*)EmLogExportResultmembertable,
	(TXDATAINFO*)EmFecModeTypemembertable,
	(TXDATAINFO*)EmLabelPosTypemembertable,
	(TXDATAINFO*)EmMtcBoxCallIndexmembertable,
	(TXDATAINFO*)EmSipRegFailedReasonmembertable,
	(TXDATAINFO*)EMtRecChnnlStatemembertable,
	(TXDATAINFO*)EMtRecChnnlTypemembertable,
	(TXDATAINFO*)EMtRecModemembertable,
	(TXDATAINFO*)EMtRecEnummembertable,
	(TXDATAINFO*)EmMtRegResultmembertable,
	(TXDATAINFO*)EmTpRetmembertable,
	(TXDATAINFO*)EmTpHduPlayNackReasonmembertable,
	(TXDATAINFO*)EmTpHduSetVolResmembertable,
	(TXDATAINFO*)EmTpLoginUmsRetmembertable,
	(TXDATAINFO*)EmTpAliasTypemembertable,
	(TXDATAINFO*)EmTpOprTypemembertable,
	(TXDATAINFO*)EmConfAddEpRetmembertable,
	(TXDATAINFO*)EmTpIFrameCheckTypemembertable,
	(TXDATAINFO*)EmTPEncryptTypemembertable,
	(TXDATAINFO*)EmQtEncryptFrequencymembertable,
	(TXDATAINFO*)EmTPQTReasonmembertable,
	(TXDATAINFO*)EmTPRcvAlignTypemembertable,
	(TXDATAINFO*)EmCnsCallReasonmembertable,
	(TXDATAINFO*)EmTPChannelReasonmembertable,
	(TXDATAINFO*)EmTpCnsTypemembertable,
	(TXDATAINFO*)EmTpCnsRegUmsmembertable,
	(TXDATAINFO*)EmTpConfTemplateRetmembertable,
	(TXDATAINFO*)EmTpStartConfRetmembertable,
	(TXDATAINFO*)EmTpApplySpeakerRetmembertable,
	(TXDATAINFO*)EmTpDropConfRetmembertable,
	(TXDATAINFO*)EmTpApplySpeakRetmembertable,
	(TXDATAINFO*)EmUmsConfNodeStatemembertable,
	(TXDATAINFO*)EmFlowCtrlOprmembertable,
	(TXDATAINFO*)EMBrdTypemembertable,
	(TXDATAINFO*)EMEqpTypemembertable,
	(TXDATAINFO*)EMEqpModleTypemembertable,
	(TXDATAINFO*)EMOsTypemembertable,
	(TXDATAINFO*)EMVmpStylemembertable,
	(TXDATAINFO*)EmTpVideoFormatmembertable,
	(TXDATAINFO*)EmTpEncodeModemembertable,
	(TXDATAINFO*)EmTpVideoQualityLevelmembertable,
	(TXDATAINFO*)EmTpCallLevelmembertable,
	(TXDATAINFO*)EmTpVideoResolutionmembertable,
	(TXDATAINFO*)EmTpMediaTypemembertable,
	(TXDATAINFO*)EmTpPCCapFormatmembertable,
	(TXDATAINFO*)EmTpCodecComponentmembertable,
	(TXDATAINFO*)EmTpAudioFormatmembertable,
	(TXDATAINFO*)EmTpLostPackageRestoremembertable,
	(TXDATAINFO*)EmTpCallModemembertable,
	(TXDATAINFO*)EmTpConnectionTypemembertable,
	(TXDATAINFO*)EmTpConfProtocolmembertable,
	(TXDATAINFO*)EmTPAddrTypemembertable,
	(TXDATAINFO*)EmTPEndpointTypemembertable,
	(TXDATAINFO*)EmTPSipLevelmembertable,
	(TXDATAINFO*)EmCALLSTATEmembertable,
	(TXDATAINFO*)EmCallTypemembertable,
	(TXDATAINFO*)EmTPVideoTypemembertable,
	(TXDATAINFO*)EmTPVideoPortmembertable,
	(TXDATAINFO*)EmTPCNSInfoRstmembertable,
	(TXDATAINFO*)EmTPRegResultmembertable,
	(TXDATAINFO*)EmCnMtRegResultmembertable,
	(TXDATAINFO*)EmCnModelmembertable,
	(TXDATAINFO*)EmFocusModemembertable,
	(TXDATAINFO*)EmSensitivitymembertable,
	(TXDATAINFO*)EmFocusmembertable,
	(TXDATAINFO*)EmZoommembertable,
	(TXDATAINFO*)EmZoomStatusmembertable,
	(TXDATAINFO*)EmCnActionmembertable,
	(TXDATAINFO*)EmOSDShowmembertable,
	(TXDATAINFO*)EmWBModemembertable,
	(TXDATAINFO*)EmExpModemembertable,
	(TXDATAINFO*)EmGainmembertable,
	(TXDATAINFO*)EmShutSpdmembertable,
	(TXDATAINFO*)EmAntiFlickermembertable,
	(TXDATAINFO*)EmSpotLighetmembertable,
	(TXDATAINFO*)EmBackLightTypemembertable,
	(TXDATAINFO*)EmWideDynamicsmembertable,
	(TXDATAINFO*)EmPicSceModemembertable,
	(TXDATAINFO*)EmGammamembertable,
	(TXDATAINFO*)EmStmCleanmembertable,
	(TXDATAINFO*)Em3DNRmembertable,
	(TXDATAINFO*)EmPicEffectmembertable,
	(TXDATAINFO*)EmPicFlipmembertable,
	(TXDATAINFO*)EmPicModemembertable,
	(TXDATAINFO*)EmResolutionmembertable,
	(TXDATAINFO*)EmBaudRatemembertable,
	(TXDATAINFO*)EmCamPowerModemembertable,
	(TXDATAINFO*)EmCenSchModemembertable,
	(TXDATAINFO*)EmSonyIrismembertable,
	(TXDATAINFO*)EmMoon904K60Irismembertable,
	(TXDATAINFO*)EmCamTypemembertable,
	(TXDATAINFO*)EmCamCfgTypemembertable,
	(TXDATAINFO*)EmTvPowerModemembertable,
	(TXDATAINFO*)EmTvSrcPowerModemembertable,
	(TXDATAINFO*)EmTVAudVisModemembertable,
	(TXDATAINFO*)EmTVDisplayModemembertable,
	(TXDATAINFO*)EmTVInputSelectmembertable,
	(TXDATAINFO*)EmDCamWBModemembertable,
	(TXDATAINFO*)EmDCamAFModemembertable,
	(TXDATAINFO*)EmDCamPowermembertable,
	(TXDATAINFO*)EmDCamZoommembertable,
	(TXDATAINFO*)EmDCamPresetNummembertable,
	(TXDATAINFO*)EmDCamRecallNummembertable,
	(TXDATAINFO*)EmDCamGainmembertable,
	(TXDATAINFO*)EmDCamShutSpdmembertable,
	(TXDATAINFO*)EmDCamIrismembertable,
	(TXDATAINFO*)EmSchPowermembertable,
	(TXDATAINFO*)EmSchLightmembertable,
	(TXDATAINFO*)EmSchMidLightmembertable,
	(TXDATAINFO*)EmSchScrLightmembertable,
	(TXDATAINFO*)EmSchCameraAndTVPowermembertable,
	(TXDATAINFO*)EmSchArgusmembertable,
	(TXDATAINFO*)EmCentreACPowermembertable,
	(TXDATAINFO*)EmCentreACAirVolmembertable,
	(TXDATAINFO*)EmCentreACModemembertable,
	(TXDATAINFO*)EmCurActionmembertable,
	(TXDATAINFO*)EmCurChannelModemembertable,
	(TXDATAINFO*)EmSchGatewayTypemembertable,
	(TXDATAINFO*)EmTpMixStatusmembertable,
	(TXDATAINFO*)EmTPDualReasonmembertable,
	(TXDATAINFO*)EmTPPayloadTypemembertable,
	(TXDATAINFO*)EmTPPosStatusmembertable,
	(TXDATAINFO*)EmTPPollResultmembertable,
	(TXDATAINFO*)EmPollStatmembertable,
	(TXDATAINFO*)EmTPViewResultmembertable,
	(TXDATAINFO*)EmTPViewLocalResultmembertable,
	(TXDATAINFO*)EmTPDisOprTypemembertable,
	(TXDATAINFO*)EMPosPicmembertable,
	(TXDATAINFO*)EMDSCREATETYPEmembertable,
	(TXDATAINFO*)EmTPAddDualRcvResultmembertable,
	(TXDATAINFO*)EmTPDeleteDualRcvResultmembertable,
	(TXDATAINFO*)EmTPMtModelmembertable,
	(TXDATAINFO*)EmDsTypemembertable,
	(TXDATAINFO*)EmCnAudioMixIDmembertable,
	(TXDATAINFO*)EmGetRegInfoTypemembertable,
	(TXDATAINFO*)EmGetRegInfoOprmembertable,
	(TXDATAINFO*)EmTPChanTypemembertable,
	(TXDATAINFO*)EmTPAACSampleFreqmembertable,
	(TXDATAINFO*)EmTPG7221Ratemembertable,
	(TXDATAINFO*)EmTPAACChnlCfgmembertable,
	(TXDATAINFO*)EmTPTpApplySpeakerRetmembertable,
	(TXDATAINFO*)EmTPChanSubTypemembertable,
	(TXDATAINFO*)EmMakeCallTypemembertable,
	(TXDATAINFO*)EmTpRegTypemembertable,
	(TXDATAINFO*)EmDisListOprTypemembertable,
	(TXDATAINFO*)EmDisListOprResltmembertable,
	(TXDATAINFO*)EmVgaTypemembertable,
	(TXDATAINFO*)EmDualInputTypemembertable,
	(TXDATAINFO*)EmDualOutputTypemembertable,
	(TXDATAINFO*)EmVgaSwitchResultmembertable,
	(TXDATAINFO*)EmVgaSwitchReasonmembertable,
	(TXDATAINFO*)EmCnStatemembertable,
	(TXDATAINFO*)EmTPCapSignmembertable,
	(TXDATAINFO*)EmSwitchStatemembertable,
	(TXDATAINFO*)EmTpBoardRetmembertable,
	(TXDATAINFO*)EmHduOutPortmembertable,
	(TXDATAINFO*)EmHduZoomRatemembertable,
	(TXDATAINFO*)EmHduOutModemembertable,
	(TXDATAINFO*)EmHduShowModemembertable,
	(TXDATAINFO*)EmModifyNMServerRetmembertable,
	(TXDATAINFO*)EmModifyVcrRetmembertable,
	(TXDATAINFO*)EmModifyHduRetmembertable,
	(TXDATAINFO*)EmUpdateHduRetmembertable,
	(TXDATAINFO*)EmMPCodecmembertable,
	(TXDATAINFO*)EmTPHDAudPortInmembertable,
	(TXDATAINFO*)EmTPHDDualAudPortInmembertable,
	(TXDATAINFO*)EmTPHDAudPortOutmembertable,
	(TXDATAINFO*)EmTPMtVideoPortmembertable,
	(TXDATAINFO*)EmTPMtVideoOutPortmembertable,
	(TXDATAINFO*)EmTPAutoTestTypemembertable,
	(TXDATAINFO*)EmTPHduRunStatusmembertable,
	(TXDATAINFO*)EmTPLoudspeakerValmembertable,
	(TXDATAINFO*)EmTPFrameUnitTypemembertable,
	(TXDATAINFO*)EmTPVideoStandardmembertable,
	(TXDATAINFO*)EmTPLabelTypemembertable,
	(TXDATAINFO*)EmTPLabelPosTypemembertable,
	(TXDATAINFO*)EmTPDualVideoShowModemembertable,
	(TXDATAINFO*)EmTPDisplayRatiomembertable,
	(TXDATAINFO*)EmTPFecModeTypemembertable,
	(TXDATAINFO*)EmTPNetTypemembertable,
	(TXDATAINFO*)EmTPEqualizerRatemembertable,
	(TXDATAINFO*)EmTPPIPModemembertable,
	(TXDATAINFO*)EmTPDVIModemembertable,
	(TXDATAINFO*)EmTPMCModemembertable,
	(TXDATAINFO*)EmCnsUpdateStatemembertable,
	(TXDATAINFO*)EmTPCnLoginUpdateRetmembertable,
	(TXDATAINFO*)EmTPFileSrvUsedVersionmembertable,
	(TXDATAINFO*)EmTPFileSrvFileTypemembertable,
	(TXDATAINFO*)EmTPOSTypemembertable,
	(TXDATAINFO*)EmMPAudEncCodecmembertable,
	(TXDATAINFO*)EmToolTypemembertable,
	(TXDATAINFO*)EmProducetestTypemembertable,
	(TXDATAINFO*)EmMdyRecFileResmembertable,
	(TXDATAINFO*)EmUseReccorderResmembertable,
	(TXDATAINFO*)EmRecorderTypemembertable,
	(TXDATAINFO*)EmConfRecStatemembertable,
	(TXDATAINFO*)EmTpProfilemembertable,
	(TXDATAINFO*)EmTPHandleCfgTypemembertable,
	(TXDATAINFO*)EmTpCodecTypemembertable,
	(TXDATAINFO*)EmToolStatemembertable,
	(TXDATAINFO*)EmTPAudPlayModemembertable,
	(TXDATAINFO*)EmTPAudDualInModemembertable,
	(TXDATAINFO*)EmTPDualTypemembertable,
	(TXDATAINFO*)EmTPDsNodemembertable,
	(TXDATAINFO*)EMScreenLookedmembertable,
	(TXDATAINFO*)EmUmsVmpStylemembertable,
	(TXDATAINFO*)EmVmpEncModemembertable,
	(TXDATAINFO*)EmVmpShowModemembertable,
	(TXDATAINFO*)EmVmpResmembertable,
	(TXDATAINFO*)EmAudPlayModemembertable,
	(TXDATAINFO*)EmResetAudModemembertable,
	(TXDATAINFO*)EmCheckAudPakmembertable,
	(TXDATAINFO*)EmViewEpTypemembertable,
	(TXDATAINFO*)EmViewRetReasonmembertable,
	(TXDATAINFO*)EmUITypemembertable,
	(TXDATAINFO*)EmGetVidResmembertable,
	(TXDATAINFO*)EmBrdVmpRetmembertable,
	(TXDATAINFO*)EmBrdVmpStatmembertable,
	(TXDATAINFO*)EmRervesVmpRetmembertable,
	(TXDATAINFO*)EmCnmpLogTypemembertable,
	(TXDATAINFO*)EmCnmpLogCtmembertable,
	(TXDATAINFO*)EmAudAecTypemembertable,
	(TXDATAINFO*)EmGetVidTypemembertable,
	(TXDATAINFO*)EmVidEncResizeModemembertable,
	(TXDATAINFO*)EmTpVendorIDmembertable,
	(TXDATAINFO*)EMScreenObjmembertable,
	(TXDATAINFO*)EmTpBannerTransparencymembertable,
	(TXDATAINFO*)EmTpBannerTypemembertable,
	(TXDATAINFO*)EmTpLogoTypemembertable,
	(TXDATAINFO*)EmTpSnapShotTypemembertable,
	(TXDATAINFO*)EmTpCtrlModemembertable,
	(TXDATAINFO*)EmDiscussOprResmembertable,
	(TXDATAINFO*)EmDiscussRspRetmembertable,
	(TXDATAINFO*)EmDCamProTypemembertable,
	(TXDATAINFO*)EmIconTypemembertable,
	(TXDATAINFO*)EmAudMixTypemembertable,
	(TXDATAINFO*)EmAudExtendmembertable,
	(TXDATAINFO*)EmRollCallRspRetmembertable,
	(TXDATAINFO*)EmAudMixModemembertable,
	(TXDATAINFO*)EmAudMixListOprmembertable,
	(TXDATAINFO*)EmAudMixResmembertable,
	(TXDATAINFO*)EmRollCallPresentStatemembertable,
	(TXDATAINFO*)EmVidMergeStylemembertable,
	(TXDATAINFO*)EmMeetingRoomSizemembertable,
	(TXDATAINFO*)EmAudGroupIndexmembertable,
	(TXDATAINFO*)EmUpdateFrequencymembertable,
	(TXDATAINFO*)EmQCamProTypemembertable,
	(TXDATAINFO*)EmP2PCallStrategyLevelmembertable,
	(TXDATAINFO*)EMDS_SUBTYPEmembertable,
	(TXDATAINFO*)NULL
};

//TTPFTPFileInfo
TYPESTRUCT_BEGIN( TTPFTPFileInfo )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, u32_ip, dwSerIP )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, u16, wSerPort )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, u8, byUserNameLen )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, s8, achUserName )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, u8, byPasswordLen )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, s8, achPassword )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, u8, byFilePathLen )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, s8, achFilePath )
TYPESTRUCT_END(  TTPFTPFileInfo )

//TTPDev
TYPESTRUCT_BEGIN( TTPDev )
    TYPESTRUCT_MEMBER( TTPDev, EmTPDevRegUpdateSer, m_emDevRegUpdateSer )
    TYPESTRUCT_MEMBER( TTPDev, s8, m_achDevVersion )
    TYPESTRUCT_MEMBER( TTPDev, TTPFTPFileInfo, m_tDevVerFileInfo )
    TYPESTRUCT_MEMBER( TTPDev, EmTPUpdateType, m_emTPUpdateType )
TYPESTRUCT_END(  TTPDev )

//TTPDevVerInfo
TYPESTRUCT_BEGIN( TTPDevVerInfo )
    TYPESTRUCT_MEMBER( TTPDevVerInfo, TTPDev, m_atDev )
TYPESTRUCT_END(  TTPDevVerInfo )

//TTPLocalVerInfo
TYPESTRUCT_BEGIN( TTPLocalVerInfo )
    TYPESTRUCT_MEMBER( TTPLocalVerInfo, EmTPDevRegUpdateSer, m_emDevRegUpdateSer )
    TYPESTRUCT_MEMBER( TTPLocalVerInfo, s8, m_achDevVersion )
TYPESTRUCT_END(  TTPLocalVerInfo )

//TTPLocalDevVerInfo
TYPESTRUCT_BEGIN( TTPLocalDevVerInfo )
    TYPESTRUCT_MEMBER( TTPLocalDevVerInfo, EmTPDevRegUpdateSer, m_emDevRegUpdateSer )
    TYPESTRUCT_MEMBER( TTPLocalDevVerInfo, TTPLocalVerInfo, m_atLocalVerInfo )
TYPESTRUCT_END(  TTPLocalDevVerInfo )

//TTPTPadVerInfo
TYPESTRUCT_BEGIN( TTPTPadVerInfo )
    TYPESTRUCT_MEMBER( TTPTPadVerInfo, EmTPUpdateType, m_emTPUpdateType )
    TYPESTRUCT_MEMBER( TTPTPadVerInfo, TTPFTPFileInfo, m_tPadVerFileInfo )
    TYPESTRUCT_MEMBER( TTPTPadVerInfo, s8, m_achTPadVersion )
TYPESTRUCT_END(  TTPTPadVerInfo )

//TH323Cfg
TYPESTRUCT_BEGIN( TH323Cfg )
    TYPESTRUCT_MEMBER( TH323Cfg, s8, achMtAlias )
    TYPESTRUCT_MEMBER( TH323Cfg, s8, achE164 )
    TYPESTRUCT_MEMBER( TH323Cfg, BOOL, bIsUseGk )
    TYPESTRUCT_MEMBER( TH323Cfg, s8, achGKPwd )
    TYPESTRUCT_MEMBER( TH323Cfg, u32_ip, dwGkIp )
    TYPESTRUCT_MEMBER( TH323Cfg, s8, achGkIpName )
    TYPESTRUCT_MEMBER( TH323Cfg, BOOL, bIsH239Enable )
    TYPESTRUCT_MEMBER( TH323Cfg, BOOL, bIsEnctyptEnable )
    TYPESTRUCT_MEMBER( TH323Cfg, EmEncryptArithmetic, emEncrptMode )
    TYPESTRUCT_MEMBER( TH323Cfg, u16, wRoundTrip )
TYPESTRUCT_END(  TH323Cfg )

//TGuideCfg
TYPESTRUCT_BEGIN( TGuideCfg )
    TYPESTRUCT_MEMBER( TGuideCfg, EmLanguage, emLanguage )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bIsDHCPEnable )
    TYPESTRUCT_MEMBER( TGuideCfg, u32_ip, dwIp )
    TYPESTRUCT_MEMBER( TGuideCfg, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TGuideCfg, u32_ip, dwGateWay )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bH323Enable )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bH320Enable )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bSIPEnable )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bSATEnable )
    TYPESTRUCT_MEMBER( TGuideCfg, TH323Cfg, tH323Info )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bUserCfgPwdEnable )
    TYPESTRUCT_MEMBER( TGuideCfg, s8, achUserCfgPwd )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bNetCfgPwdEnable )
    TYPESTRUCT_MEMBER( TGuideCfg, s8, achNetCfgPwd )
TYPESTRUCT_END(  TGuideCfg )

//TSymboPoint
TYPESTRUCT_BEGIN( TSymboPoint )
    TYPESTRUCT_MEMBER( TSymboPoint, u16, X )
    TYPESTRUCT_MEMBER( TSymboPoint, u16, Y )
TYPESTRUCT_END(  TSymboPoint )

//TOsdCfg
TYPESTRUCT_BEGIN( TOsdCfg )
    TYPESTRUCT_MEMBER( TOsdCfg, BOOL, bIsAutoPip )
    TYPESTRUCT_MEMBER( TOsdCfg, BOOL, bIsShowConfLapse )
    TYPESTRUCT_MEMBER( TOsdCfg, BOOL, bIsShowSysTime )
    TYPESTRUCT_MEMBER( TOsdCfg, BOOL, bIsShowState )
    TYPESTRUCT_MEMBER( TOsdCfg, EmLabelType, emLabelType )
    TYPESTRUCT_MEMBER( TOsdCfg, TSymboPoint, tLableCoordinate )
    TYPESTRUCT_MEMBER( TOsdCfg, EmLabelPosType, emLabelPosType )
    TYPESTRUCT_MEMBER( TOsdCfg, EmDualVideoShowMode, emDualMode )
    TYPESTRUCT_MEMBER( TOsdCfg, EmDisplayRatio, emPrimaryDisplayRatio )
    TYPESTRUCT_MEMBER( TOsdCfg, EmDisplayRatio, emSecondDisplayRatio )
TYPESTRUCT_END(  TOsdCfg )

//TMtKdvTime
TYPESTRUCT_BEGIN( TMtKdvTime )
    TYPESTRUCT_MEMBER( TMtKdvTime, u16, m_wYear )
    TYPESTRUCT_MEMBER( TMtKdvTime, u8, m_byMonth )
    TYPESTRUCT_MEMBER( TMtKdvTime, u8, m_byMDay )
    TYPESTRUCT_MEMBER( TMtKdvTime, u8, m_byHour )
    TYPESTRUCT_MEMBER( TMtKdvTime, u8, m_byMinute )
    TYPESTRUCT_MEMBER( TMtKdvTime, u8, m_bySecond )
TYPESTRUCT_END(  TMtKdvTime )

//TUserCfg
TYPESTRUCT_BEGIN( TUserCfg )
    TYPESTRUCT_MEMBER( TUserCfg, EmTripMode, emAnswerMode )
    TYPESTRUCT_MEMBER( TUserCfg, BOOL, bIsAutoCallEnable )
    TYPESTRUCT_MEMBER( TUserCfg, s8, achTerminal )
    TYPESTRUCT_MEMBER( TUserCfg, u16, wCallRate )
    TYPESTRUCT_MEMBER( TUserCfg, BOOL, bIsRmtCtrlEnbale )
    TYPESTRUCT_MEMBER( TUserCfg, BOOL, bIsSleepEnable )
    TYPESTRUCT_MEMBER( TUserCfg, u16, wSleepTime )
    TYPESTRUCT_MEMBER( TUserCfg, BOOL, bDisableTelephone )
TYPESTRUCT_END(  TUserCfg )

//TVgaOutCfg
TYPESTRUCT_BEGIN( TVgaOutCfg )
    TYPESTRUCT_MEMBER( TVgaOutCfg, BOOL, bVgaOut )
    TYPESTRUCT_MEMBER( TVgaOutCfg, u16, wRefreshRate )
TYPESTRUCT_END(  TVgaOutCfg )

//TMtEquipmentCapset
TYPESTRUCT_BEGIN( TMtEquipmentCapset )
    TYPESTRUCT_MEMBER( TMtEquipmentCapset, BOOL, bMicAdjustSupport )
    TYPESTRUCT_MEMBER( TMtEquipmentCapset, BOOL, bMcSupport )
TYPESTRUCT_END(  TMtEquipmentCapset )

//TInnerMcCfg
TYPESTRUCT_BEGIN( TInnerMcCfg )
    TYPESTRUCT_MEMBER( TInnerMcCfg, BOOL, bUseMc )
    TYPESTRUCT_MEMBER( TInnerMcCfg, EmMCMode, emMode )
    TYPESTRUCT_MEMBER( TInnerMcCfg, BOOL, bAutoVMP )
TYPESTRUCT_END(  TInnerMcCfg )

//TEthnetInfo
TYPESTRUCT_BEGIN( TEthnetInfo )
    TYPESTRUCT_MEMBER( TEthnetInfo, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TEthnetInfo, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TEthnetInfo, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TEthnetInfo, BOOL, bIsUserAssignBandWidth )
    TYPESTRUCT_MEMBER( TEthnetInfo, u32, dwUpBandWidth )
    TYPESTRUCT_MEMBER( TEthnetInfo, u32, dwDownBandWidth )
TYPESTRUCT_END(  TEthnetInfo )

//TE1Unit
TYPESTRUCT_BEGIN( TE1Unit )
    TYPESTRUCT_MEMBER( TE1Unit, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TE1Unit, u32, dwE1TSMask )
    TYPESTRUCT_MEMBER( TE1Unit, EmDLProtocol, emProtocol )
    TYPESTRUCT_MEMBER( TE1Unit, u32, dwEchoInterval )
    TYPESTRUCT_MEMBER( TE1Unit, u32, dwEchoMaxRetry )
TYPESTRUCT_END(  TE1Unit )

//TE1Config
TYPESTRUCT_BEGIN( TE1Config )
    TYPESTRUCT_MEMBER( TE1Config, u8, byUnitNum )
    TYPESTRUCT_MEMBER( TE1Config, BOOL, bIsBind )
    TYPESTRUCT_MEMBER( TE1Config, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TE1Config, u32_ip, dwIPMask )
    TYPESTRUCT_MEMBER( TE1Config, EmAuthenticationType, emAuthenticationType )
    TYPESTRUCT_MEMBER( TE1Config, u32, dwFragMinPackageLen )
    TYPESTRUCT_MEMBER( TE1Config, s8, achSvrUsrName )
    TYPESTRUCT_MEMBER( TE1Config, s8, achSvrUsrPwd )
    TYPESTRUCT_MEMBER( TE1Config, s8, achSentUsrName )
    TYPESTRUCT_MEMBER( TE1Config, s8, achSentUsrPwd )
    TYPESTRUCT_MEMBER( TE1Config, TE1Unit, atE1Unit )
TYPESTRUCT_END(  TE1Config )

//TSerialCfg
TYPESTRUCT_BEGIN( TSerialCfg )
    TYPESTRUCT_MEMBER( TSerialCfg, u32, dwBaudRate )
    TYPESTRUCT_MEMBER( TSerialCfg, u8, byByteSize )
    TYPESTRUCT_MEMBER( TSerialCfg, EmParityCheck, emCheck )
    TYPESTRUCT_MEMBER( TSerialCfg, EmStopBits, emStopBits )
TYPESTRUCT_END(  TSerialCfg )

//TRouteCfg
TYPESTRUCT_BEGIN( TRouteCfg )
    TYPESTRUCT_MEMBER( TRouteCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TRouteCfg, u32_ip, dwDstNet )
    TYPESTRUCT_MEMBER( TRouteCfg, u32_ip, dwDstNetMask )
    TYPESTRUCT_MEMBER( TRouteCfg, u32_ip, dwNextIP )
    TYPESTRUCT_MEMBER( TRouteCfg, u32, dwPri )
TYPESTRUCT_END(  TRouteCfg )

//TPPPOECfg
TYPESTRUCT_BEGIN( TPPPOECfg )
    TYPESTRUCT_MEMBER( TPPPOECfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TPPPOECfg, s8, abyUserName )
    TYPESTRUCT_MEMBER( TPPPOECfg, s8, abyPassword )
    TYPESTRUCT_MEMBER( TPPPOECfg, s8, abyServerName )
    TYPESTRUCT_MEMBER( TPPPOECfg, BOOL, bAutoDialEnable )
    TYPESTRUCT_MEMBER( TPPPOECfg, BOOL, bDefaultRouteEnable )
    TYPESTRUCT_MEMBER( TPPPOECfg, BOOL, bDebug )
    TYPESTRUCT_MEMBER( TPPPOECfg, u32, dwAutoDialInterval )
    TYPESTRUCT_MEMBER( TPPPOECfg, u16, wDialRetryTimes )
    TYPESTRUCT_MEMBER( TPPPOECfg, u16, wLcpEchoSendInterval )
    TYPESTRUCT_MEMBER( TPPPOECfg, u16, wLcpEchoRetryTimes )
    TYPESTRUCT_MEMBER( TPPPOECfg, u8, byEthID )
TYPESTRUCT_END(  TPPPOECfg )

//TPPPoEStates
TYPESTRUCT_BEGIN( TPPPoEStates )
    TYPESTRUCT_MEMBER( TPPPoEStates, BOOL, bPppoeRunning )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwLocalIpAddr )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwPeerIpAddr )
    TYPESTRUCT_MEMBER( TPPPoEStates, s8, abyServerName )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwLinkKeepTimes )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwLinkDownTimes )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwPktsSend )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwPktsRecv )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwBytesSend )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwBytesRecv )
TYPESTRUCT_END(  TPPPoEStates )

//TPPPoEAuthFailed
TYPESTRUCT_BEGIN( TPPPoEAuthFailed )
    TYPESTRUCT_MEMBER( TPPPoEAuthFailed, s8, abyUserName )
    TYPESTRUCT_MEMBER( TPPPoEAuthFailed, s8, abyPassword )
TYPESTRUCT_END(  TPPPoEAuthFailed )

//TPPPoEConnNotify
TYPESTRUCT_BEGIN( TPPPoEConnNotify )
    TYPESTRUCT_MEMBER( TPPPoEConnNotify, u32, dwOurIpAddr )
    TYPESTRUCT_MEMBER( TPPPoEConnNotify, u32, dwPeerIpAddr )
    TYPESTRUCT_MEMBER( TPPPoEConnNotify, u32, dwDnsServer1 )
    TYPESTRUCT_MEMBER( TPPPoEConnNotify, u32, dwDnsServer2 )
TYPESTRUCT_END(  TPPPoEConnNotify )

//TPPPoENoServer
TYPESTRUCT_BEGIN( TPPPoENoServer )
    TYPESTRUCT_MEMBER( TPPPoENoServer, s8, abyServerName )
TYPESTRUCT_END(  TPPPoENoServer )

//TSNMPCfg
TYPESTRUCT_BEGIN( TSNMPCfg )
    TYPESTRUCT_MEMBER( TSNMPCfg, s8, achUserName )
    TYPESTRUCT_MEMBER( TSNMPCfg, u32_ip, dwTrapServerIp )
TYPESTRUCT_END(  TSNMPCfg )

//TIPQoS
TYPESTRUCT_BEGIN( TIPQoS )
    TYPESTRUCT_MEMBER( TIPQoS, EmQoS, emType )
    TYPESTRUCT_MEMBER( TIPQoS, u8, abySignalling )
    TYPESTRUCT_MEMBER( TIPQoS, u8, abyData )
    TYPESTRUCT_MEMBER( TIPQoS, u8, abyAudio )
    TYPESTRUCT_MEMBER( TIPQoS, u8, abyVideo )
    TYPESTRUCT_MEMBER( TIPQoS, EmTOS, emTOS )
TYPESTRUCT_END(  TIPQoS )

//TStreamMedia
TYPESTRUCT_BEGIN( TStreamMedia )
    TYPESTRUCT_MEMBER( TStreamMedia, BOOL, bUse )
    TYPESTRUCT_MEMBER( TStreamMedia, BOOL, bForwardLocalVideo )
    TYPESTRUCT_MEMBER( TStreamMedia, u32_ip, dwMCIP )
    TYPESTRUCT_MEMBER( TStreamMedia, u16, wPort )
    TYPESTRUCT_MEMBER( TStreamMedia, u8, byTTL )
    TYPESTRUCT_MEMBER( TStreamMedia, s8, achChannelName )
    TYPESTRUCT_MEMBER( TStreamMedia, s8, achPassword )
TYPESTRUCT_END(  TStreamMedia )

//TVideoParam
TYPESTRUCT_BEGIN( TVideoParam )
    TYPESTRUCT_MEMBER( TVideoParam, BOOL, bUseFixedFrame )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byFrameRate )
    TYPESTRUCT_MEMBER( TVideoParam, EmFrameUnitType, emFrameUnit )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byQualMaxValue )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byQualMinValue )
    TYPESTRUCT_MEMBER( TVideoParam, u16, wIKeyRate )
    TYPESTRUCT_MEMBER( TVideoParam, EmEncodeMode, emEncodeMode )
    TYPESTRUCT_MEMBER( TVideoParam, EmLostPackageRestore, emRestoreType )
    TYPESTRUCT_MEMBER( TVideoParam, u16, wH264IKeyRate )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byH264QualMaxValue )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byH264QualMinValue )
    TYPESTRUCT_MEMBER( TVideoParam, u16, wWidth )
    TYPESTRUCT_MEMBER( TVideoParam, u16, wHeight )
    TYPESTRUCT_MEMBER( TVideoParam, EmMediaType, emCapType )
    TYPESTRUCT_MEMBER( TVideoParam, EmPCCapFormat, emPCCapFormat )
    TYPESTRUCT_MEMBER( TVideoParam, u8, by720pFrameRate )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byVgaFrameRate )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byD1FrameRate )
TYPESTRUCT_END(  TVideoParam )

//TAVPriorStrategy
TYPESTRUCT_BEGIN( TAVPriorStrategy )
    TYPESTRUCT_MEMBER( TAVPriorStrategy, EmVideoFormat, emVideoFormat )
    TYPESTRUCT_MEMBER( TAVPriorStrategy, EmAudioFormat, emAudioFormat )
    TYPESTRUCT_MEMBER( TAVPriorStrategy, EmVideoResolution, emVideoResolution )
TYPESTRUCT_END(  TAVPriorStrategy )

//TLostPackResend
TYPESTRUCT_BEGIN( TLostPackResend )
    TYPESTRUCT_MEMBER( TLostPackResend, BOOL, bUse )
    TYPESTRUCT_MEMBER( TLostPackResend, EmNetType, emNetType )
    TYPESTRUCT_MEMBER( TLostPackResend, u8, byResendLevel )
    TYPESTRUCT_MEMBER( TLostPackResend, u16, wFirstTimeSpan )
    TYPESTRUCT_MEMBER( TLostPackResend, u16, wSecondTimeSpan )
    TYPESTRUCT_MEMBER( TLostPackResend, u16, wThirdTimeSpan )
    TYPESTRUCT_MEMBER( TLostPackResend, u16, wRejectTimeSpan )
    TYPESTRUCT_MEMBER( TLostPackResend, u16, wSendBufTimeSpan )
    TYPESTRUCT_MEMBER( TLostPackResend, BOOL, bUseSmoothSend )
    TYPESTRUCT_MEMBER( TLostPackResend, BOOL, bUseAdaptSend )
TYPESTRUCT_END(  TLostPackResend )

//TCameraTypeInfo
TYPESTRUCT_BEGIN( TCameraTypeInfo )
    TYPESTRUCT_MEMBER( TCameraTypeInfo, s8, achName )
    TYPESTRUCT_MEMBER( TCameraTypeInfo, u8, byMaxAddr )
    TYPESTRUCT_MEMBER( TCameraTypeInfo, u8, byMaxSpeedLevel )
TYPESTRUCT_END(  TCameraTypeInfo )

//TCameraCfg
TYPESTRUCT_BEGIN( TCameraCfg )
    TYPESTRUCT_MEMBER( TCameraCfg, BOOL, bUse )
    TYPESTRUCT_MEMBER( TCameraCfg, s8, achCamera )
    TYPESTRUCT_MEMBER( TCameraCfg, u8, byAddr )
    TYPESTRUCT_MEMBER( TCameraCfg, u8, bySpeedLevel )
    TYPESTRUCT_MEMBER( TCameraCfg, EmSerialType, emSerialType )
    TYPESTRUCT_MEMBER( TCameraCfg, u32_ip, dwSerialServerIP )
    TYPESTRUCT_MEMBER( TCameraCfg, u16, wSerialServerPort )
TYPESTRUCT_END(  TCameraCfg )

//TVideoStandard
TYPESTRUCT_BEGIN( TVideoStandard )
    TYPESTRUCT_MEMBER( TVideoStandard, EmVideoType, emVideoType )
    TYPESTRUCT_MEMBER( TVideoStandard, BOOL, bIsInPort )
    TYPESTRUCT_MEMBER( TVideoStandard, EmVideoStandard, emStandard )
TYPESTRUCT_END(  TVideoStandard )

//TVideoSource
TYPESTRUCT_BEGIN( TVideoSource )
    TYPESTRUCT_MEMBER( TVideoSource, EmVideoInterface, emMainCam )
    TYPESTRUCT_MEMBER( TVideoSource, u8, byCPortIndex )
    TYPESTRUCT_MEMBER( TVideoSource, EmVideoInterface, emVideoOut )
    TYPESTRUCT_MEMBER( TVideoSource, u8, byFrequency )
TYPESTRUCT_END(  TVideoSource )

//TSnapInfo
TYPESTRUCT_BEGIN( TSnapInfo )
    TYPESTRUCT_MEMBER( TSnapInfo, BOOL, bResult )
    TYPESTRUCT_MEMBER( TSnapInfo, u32, dwMaxSize )
    TYPESTRUCT_MEMBER( TSnapInfo, u32, dwUsedSize )
    TYPESTRUCT_MEMBER( TSnapInfo, u32, dwPicNum )
TYPESTRUCT_END(  TSnapInfo )

//TBannerInfo
TYPESTRUCT_BEGIN( TBannerInfo )
    TYPESTRUCT_MEMBER( TBannerInfo, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwTextClr )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwBkgClr )
    TYPESTRUCT_MEMBER( TBannerInfo, EmTextAlign, emTextAlign )
    TYPESTRUCT_MEMBER( TBannerInfo, EmRollMode, emRollMode )
    TYPESTRUCT_MEMBER( TBannerInfo, u8, byTransParent )
    TYPESTRUCT_MEMBER( TBannerInfo, EmRollSpeed, emRollSpeed )
    TYPESTRUCT_MEMBER( TBannerInfo, u8, byRollNum )
    TYPESTRUCT_MEMBER( TBannerInfo, u8, byStayTime )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwStartXPos )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwStartYPos )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwDisplayWidth )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwDisplayHeight )
    TYPESTRUCT_MEMBER( TBannerInfo, u8, achWinInfo )
    TYPESTRUCT_MEMBER( TBannerInfo, s8, achBannerText )
TYPESTRUCT_END(  TBannerInfo )

//TMtId
TYPESTRUCT_BEGIN( TMtId )
    TYPESTRUCT_MEMBER( TMtId, u8, byMcuNo )
    TYPESTRUCT_MEMBER( TMtId, u8, byTerNo )
TYPESTRUCT_END(  TMtId )

//TConfBaseInfo
TYPESTRUCT_BEGIN( TConfBaseInfo )
    TYPESTRUCT_MEMBER( TConfBaseInfo, s8, achConfId )
    TYPESTRUCT_MEMBER( TConfBaseInfo, s8, achConfName )
    TYPESTRUCT_MEMBER( TConfBaseInfo, s8, achConfNumber )
    TYPESTRUCT_MEMBER( TConfBaseInfo, s8, achConfPwd )
    TYPESTRUCT_MEMBER( TConfBaseInfo, BOOL, bNeedPassword )
    TYPESTRUCT_MEMBER( TConfBaseInfo, u16, wConfDuration )
    TYPESTRUCT_MEMBER( TConfBaseInfo, EmVideoFormat, emVideoFormat )
    TYPESTRUCT_MEMBER( TConfBaseInfo, EmAudioFormat, emAudioFormat )
    TYPESTRUCT_MEMBER( TConfBaseInfo, EmVideoResolution, emResolution )
    TYPESTRUCT_MEMBER( TConfBaseInfo, BOOL, bIsAutoVMP )
    TYPESTRUCT_MEMBER( TConfBaseInfo, BOOL, bIsMix )
    TYPESTRUCT_MEMBER( TConfBaseInfo, u8, bySecVideoFormat )
    TYPESTRUCT_MEMBER( TConfBaseInfo, EmVideoResolution, emSecVidRes )
    TYPESTRUCT_MEMBER( TConfBaseInfo, u8, bySecVidFps )
TYPESTRUCT_END(  TConfBaseInfo )

//TConfListInfo
TYPESTRUCT_BEGIN( TConfListInfo )
    TYPESTRUCT_MEMBER( TConfListInfo, u8, byConfNum )
    TYPESTRUCT_MEMBER( TConfListInfo, TConfBaseInfo, atConfInfo )
TYPESTRUCT_END(  TConfListInfo )

//TMtInfo
TYPESTRUCT_BEGIN( TMtInfo )
    TYPESTRUCT_MEMBER( TMtInfo, TMtId, tLabel )
    TYPESTRUCT_MEMBER( TMtInfo, s8, achAlias )
TYPESTRUCT_END(  TMtInfo )

//TMtVideoCodecStatus
TYPESTRUCT_BEGIN( TMtVideoCodecStatus )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, BOOL, bRuning )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, EmVideoFormat, emFormat )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, EmVideoResolution, emRes )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, u16, wBitrate )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, u16, wAverageBitrate )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, BOOL, IsEncrypt )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, EmEncryptArithmetic, emArithmetic )
TYPESTRUCT_END(  TMtVideoCodecStatus )

//TTerStatus
TYPESTRUCT_BEGIN( TTerStatus )
    TYPESTRUCT_MEMBER( TTerStatus, EmMtModel, emMtModel )
    TYPESTRUCT_MEMBER( TTerStatus, EmFileSys, emFileSys )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byEncVol )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byDecVol )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsMute )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsQuiet )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsLoopBack )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsInMixing )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bRegGkStat )
    TYPESTRUCT_MEMBER( TTerStatus, EmAction, emPollStat )
    TYPESTRUCT_MEMBER( TTerStatus, EmSite, emCamCtrlSrc )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byLocalCamCtrlNo )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byRemoteCamCtrlNo )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byE1UnitNum )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bFECCEnalbe )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bLocalIsVAG )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bPVHasVideo )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bSVHasVideo )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsAudioPowerTest )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsLocalImageTest )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsRemoteImageTest )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsInConf )
    TYPESTRUCT_MEMBER( TTerStatus, EmConfMode, emConfMode )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bCallByGK )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bMatrixStatus )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byCamNum )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bCamStatus )
    TYPESTRUCT_MEMBER( TTerStatus, EmMtVideoPort, emVideoSrc )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsEncrypt )
    TYPESTRUCT_MEMBER( TTerStatus, EmAudioFormat, emADecFormat )
    TYPESTRUCT_MEMBER( TTerStatus, EmAudioFormat, emAEncFormat )
    TYPESTRUCT_MEMBER( TTerStatus, TMtVideoCodecStatus, tPVEncStatus )
    TYPESTRUCT_MEMBER( TTerStatus, TMtVideoCodecStatus, tSVEncStatus )
    TYPESTRUCT_MEMBER( TTerStatus, TMtVideoCodecStatus, tPVDecStatus )
    TYPESTRUCT_MEMBER( TTerStatus, TMtVideoCodecStatus, tSVDecStatus )
    TYPESTRUCT_MEMBER( TTerStatus, u16, wSysSleep )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsInVOD )
    TYPESTRUCT_MEMBER( TTerStatus, EmUIPosion, byVodUser )
TYPESTRUCT_END(  TTerStatus )

//TMtMixParam
TYPESTRUCT_BEGIN( TMtMixParam )
    TYPESTRUCT_MEMBER( TMtMixParam, u8, byMixNum )
    TYPESTRUCT_MEMBER( TMtMixParam, u8, byDIscussMode )
    TYPESTRUCT_MEMBER( TMtMixParam, TMtId, atMtMixItem )
TYPESTRUCT_END(  TMtMixParam )

//TMtVmpItem
TYPESTRUCT_BEGIN( TMtVmpItem )
    TYPESTRUCT_MEMBER( TMtVmpItem, TMtId, tMt )
    TYPESTRUCT_MEMBER( TMtVmpItem, EmVMPMmbType, emMmbType )
    TYPESTRUCT_MEMBER( TMtVmpItem, u32, adwReserved )
TYPESTRUCT_END(  TMtVmpItem )

//TMtVMPParam
TYPESTRUCT_BEGIN( TMtVMPParam )
    TYPESTRUCT_MEMBER( TMtVMPParam, BOOL, bIsCustomVMP )
    TYPESTRUCT_MEMBER( TMtVMPParam, BOOL, bIsAutoVMP )
    TYPESTRUCT_MEMBER( TMtVMPParam, BOOL, bIsBroadcast )
    TYPESTRUCT_MEMBER( TMtVMPParam, EmVMPStyle, emStyle )
    TYPESTRUCT_MEMBER( TMtVMPParam, TMtVmpItem, atMtVmpItem )
TYPESTRUCT_END(  TMtVMPParam )

//TMtPollInfo
TYPESTRUCT_BEGIN( TMtPollInfo )
    TYPESTRUCT_MEMBER( TMtPollInfo, EmMediaType, emMode )
    TYPESTRUCT_MEMBER( TMtPollInfo, EmAction, emStat )
    TYPESTRUCT_MEMBER( TMtPollInfo, u16, wKeepTime )
    TYPESTRUCT_MEMBER( TMtPollInfo, u8, byMtNum )
    TYPESTRUCT_MEMBER( TMtPollInfo, TMtInfo, atMtInfo )
TYPESTRUCT_END(  TMtPollInfo )

//TMtPollSchemeNameSet
TYPESTRUCT_BEGIN( TMtPollSchemeNameSet )
    TYPESTRUCT_MATRIX( TMtPollSchemeNameSet, s8, achMtPollSchemeName )
TYPESTRUCT_END(  TMtPollSchemeNameSet )

//TMtViewPollInfo
TYPESTRUCT_BEGIN( TMtViewPollInfo )
    TYPESTRUCT_MEMBER( TMtViewPollInfo, EmMediaType, emMode )
    TYPESTRUCT_MEMBER( TMtViewPollInfo, EmAction, emStat )
    TYPESTRUCT_MEMBER( TMtViewPollInfo, u16, wKeepTime )
    TYPESTRUCT_MEMBER( TMtViewPollInfo, u8, byMtNum )
    TYPESTRUCT_MEMBER( TMtViewPollInfo, TMtInfo, atMtInfo )
TYPESTRUCT_END(  TMtViewPollInfo )

//TMtSimpConfInfo
TYPESTRUCT_BEGIN( TMtSimpConfInfo )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, TMtId, tSpeaker )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, TMtId, tChairMan )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, BOOL, bIsVAC )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, BOOL, bIsDisc )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, BOOL, bIsAutoVMP )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, BOOL, bIsCustomVMP )
TYPESTRUCT_END(  TMtSimpConfInfo )

//TMtConfInfo
TYPESTRUCT_BEGIN( TMtConfInfo )
    TYPESTRUCT_MEMBER( TMtConfInfo, s8, chConfId )
    TYPESTRUCT_MEMBER( TMtConfInfo, TMtKdvTime, tStartTime )
    TYPESTRUCT_MEMBER( TMtConfInfo, u16, wDuration )
    TYPESTRUCT_MEMBER( TMtConfInfo, u16, wBitRate )
    TYPESTRUCT_MEMBER( TMtConfInfo, u16, wSecBitRate )
    TYPESTRUCT_MEMBER( TMtConfInfo, EmVideoResolution, emMainVideoResolution )
    TYPESTRUCT_MEMBER( TMtConfInfo, EmVideoResolution, emSecondVideoResolution )
    TYPESTRUCT_MEMBER( TMtConfInfo, EmVideoResolution, emDoubleVideoResolution )
    TYPESTRUCT_MEMBER( TMtConfInfo, u8, byTalkHoldTime )
    TYPESTRUCT_MEMBER( TMtConfInfo, s8, achConfPwd )
    TYPESTRUCT_MEMBER( TMtConfInfo, s8, achConfName )
    TYPESTRUCT_MEMBER( TMtConfInfo, s8, achConfE164 )
    TYPESTRUCT_MEMBER( TMtConfInfo, BOOL, bIsAudioPowerSel )
    TYPESTRUCT_MEMBER( TMtConfInfo, BOOL, bIsDiscussMode )
    TYPESTRUCT_MEMBER( TMtConfInfo, BOOL, bIsAutoVMP )
    TYPESTRUCT_MEMBER( TMtConfInfo, BOOL, bIsCustomVMP )
    TYPESTRUCT_MEMBER( TMtConfInfo, BOOL, bIsForceBroadcast )
    TYPESTRUCT_MEMBER( TMtConfInfo, TMtId, tChairman )
    TYPESTRUCT_MEMBER( TMtConfInfo, TMtId, tSpeaker )
    TYPESTRUCT_MEMBER( TMtConfInfo, TMtPollInfo, tPollInfo )
    TYPESTRUCT_MEMBER( TMtConfInfo, TMtVMPParam, tVMPParam )
TYPESTRUCT_END(  TMtConfInfo )

//TIPTransAddr
TYPESTRUCT_BEGIN( TIPTransAddr )
    TYPESTRUCT_MEMBER( TIPTransAddr, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TIPTransAddr, u16, wPort )
TYPESTRUCT_END(  TIPTransAddr )

//TMtAddr
TYPESTRUCT_BEGIN( TMtAddr )
    TYPESTRUCT_MEMBER( TMtAddr, EmMtAddrType, emType )
    TYPESTRUCT_MEMBER( TMtAddr, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TMtAddr, s8, achAlias )
TYPESTRUCT_END(  TMtAddr )

//TConfId
TYPESTRUCT_BEGIN( TConfId )
    TYPESTRUCT_MEMBER( TConfId, u8, byGuid )
    TYPESTRUCT_MEMBER( TConfId, TMtAddr, tAlias )
TYPESTRUCT_END(  TConfId )

//TLinkState
TYPESTRUCT_BEGIN( TLinkState )
    TYPESTRUCT_MEMBER( TLinkState, EmCallState, emCallState )
    TYPESTRUCT_MEMBER( TLinkState, u32_ip, dwIpAddr )
    TYPESTRUCT_MEMBER( TLinkState, s8, achAlias )
    TYPESTRUCT_MEMBER( TLinkState, BOOL, bCalling )
    TYPESTRUCT_MEMBER( TLinkState, EmCallDisconnectReason, emReason )
    TYPESTRUCT_MEMBER( TLinkState, BOOL, bGetChairToken )
    TYPESTRUCT_MEMBER( TLinkState, BOOL, bSeenByAll )
    TYPESTRUCT_MEMBER( TLinkState, u16, wCallRate )
    TYPESTRUCT_MEMBER( TLinkState, EmMtModel, emPeerMtModel )
TYPESTRUCT_END(  TLinkState )

//TEmbedFwNatProxy
TYPESTRUCT_BEGIN( TEmbedFwNatProxy )
    TYPESTRUCT_MEMBER( TEmbedFwNatProxy, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TEmbedFwNatProxy, u32_ip, dwFwNatProxyServIP )
    TYPESTRUCT_MEMBER( TEmbedFwNatProxy, s8, achPrxySrvName )
    TYPESTRUCT_MEMBER( TEmbedFwNatProxy, u16, wFwNatProxyServListenPort )
    TYPESTRUCT_MEMBER( TEmbedFwNatProxy, u16, wStreamBasePort )
TYPESTRUCT_END(  TEmbedFwNatProxy )

//TNATMapAddr
TYPESTRUCT_BEGIN( TNATMapAddr )
    TYPESTRUCT_MEMBER( TNATMapAddr, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TNATMapAddr, u32_ip, dwIP )
TYPESTRUCT_END(  TNATMapAddr )

//TSipRegistrarCfg
TYPESTRUCT_BEGIN( TSipRegistrarCfg )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, u32_ip, dwRegIP )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, u16, wRegPort )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, s8, achRegDomain )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, u16, wExpire )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, s8, achDisplayName )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, s8, achUserName )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, s8, achPassword )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, s8, achHostDomain )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, u32_ip, dwHostIP )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, u16, wHostPort )
TYPESTRUCT_END(  TSipRegistrarCfg )

//TGKCfg
TYPESTRUCT_BEGIN( TGKCfg )
    TYPESTRUCT_MEMBER( TGKCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TGKCfg, u32_ip, dwGKIP )
    TYPESTRUCT_MEMBER( TGKCfg, s8, achGkIpName )
    TYPESTRUCT_MEMBER( TGKCfg, s8, achGKPasswd )
TYPESTRUCT_END(  TGKCfg )

//TInnerGKCfg
TYPESTRUCT_BEGIN( TInnerGKCfg )
    TYPESTRUCT_MEMBER( TInnerGKCfg, BOOL, bGKUsed )
    TYPESTRUCT_MEMBER( TInnerGKCfg, u32_ip, dwIp )
    TYPESTRUCT_MEMBER( TInnerGKCfg, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TInnerGKCfg, u32_ip, dwGateWay )
TYPESTRUCT_END(  TInnerGKCfg )

//TInnerProxyCfg
TYPESTRUCT_BEGIN( TInnerProxyCfg )
    TYPESTRUCT_MEMBER( TInnerProxyCfg, BOOL, bInnerProxyUsed )
    TYPESTRUCT_MEMBER( TInnerProxyCfg, u32_ip, dwIp )
    TYPESTRUCT_MEMBER( TInnerProxyCfg, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TInnerProxyCfg, u32_ip, dwGateWay )
TYPESTRUCT_END(  TInnerProxyCfg )

//TWiFiNetCfg
TYPESTRUCT_BEGIN( TWiFiNetCfg )
    TYPESTRUCT_MEMBER( TWiFiNetCfg, BOOL, bWiFiUsed )
    TYPESTRUCT_MEMBER( TWiFiNetCfg, BOOL, bDHCP )
    TYPESTRUCT_MEMBER( TWiFiNetCfg, u32_ip, dwIp )
    TYPESTRUCT_MEMBER( TWiFiNetCfg, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TWiFiNetCfg, u32_ip, dwGateWay )
TYPESTRUCT_END(  TWiFiNetCfg )

//TMonitorService
TYPESTRUCT_BEGIN( TMonitorService )
    TYPESTRUCT_MEMBER( TMonitorService, BOOL, bSwitchEnable )
    TYPESTRUCT_MEMBER( TMonitorService, u32, dwSwitchTimeout )
TYPESTRUCT_END(  TMonitorService )

//TRect
TYPESTRUCT_BEGIN( TRect )
    TYPESTRUCT_MEMBER( TRect, u16, wLeft )
    TYPESTRUCT_MEMBER( TRect, u16, wTop )
    TYPESTRUCT_MEMBER( TRect, u16, wWidth )
    TYPESTRUCT_MEMBER( TRect, u16, wHeight )
TYPESTRUCT_END(  TRect )

//TDualRation
TYPESTRUCT_BEGIN( TDualRation )
    TYPESTRUCT_MEMBER( TDualRation, BOOL, bSecondSendRateType )
    TYPESTRUCT_MEMBER( TDualRation, BOOL, bSecondRecvRateType )
    TYPESTRUCT_MEMBER( TDualRation, u8, bySecondSendRate )
    TYPESTRUCT_MEMBER( TDualRation, u8, bySecondRecvRate )
    TYPESTRUCT_MEMBER( TDualRation, u8, byPrimaryRecvRate )
TYPESTRUCT_END(  TDualRation )

//TImageAdjustParam
TYPESTRUCT_BEGIN( TImageAdjustParam )
    TYPESTRUCT_MEMBER( TImageAdjustParam, u8, wBrightness )
    TYPESTRUCT_MEMBER( TImageAdjustParam, u8, wContrast )
    TYPESTRUCT_MEMBER( TImageAdjustParam, u8, wSaturation )
TYPESTRUCT_END(  TImageAdjustParam )

//TVideoEncodeParameter
TYPESTRUCT_BEGIN( TVideoEncodeParameter )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, EmVideoFormat, emVideoFormat )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u16, byMaxKeyFrameInterval )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u8, byMaxQuant )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u8, byMinQuant )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, BOOL, bUseFixedFrame )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u8, byFrameRate )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, BOOL, bFramePerSecond )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, EmEncodeMode, emEncodeMode )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, EmVideoResolution, emVideoResolution )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u32, wChanMaxBitrate )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u16, m_wWidth )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u16, m_wHeight )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, EmMediaType, emCapType )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, EmPCCapFormat, emPCCapFormat )
TYPESTRUCT_END(  TVideoEncodeParameter )

//TEncryptKey
TYPESTRUCT_BEGIN( TEncryptKey )
    TYPESTRUCT_MEMBER( TEncryptKey, u8, byLen )
    TYPESTRUCT_MEMBER( TEncryptKey, u8, byKey )
TYPESTRUCT_END(  TEncryptKey )

//TVideoChanParam
TYPESTRUCT_BEGIN( TVideoChanParam )
    TYPESTRUCT_MEMBER( TVideoChanParam, EmVideoFormat, emVideoFormat )
    TYPESTRUCT_MEMBER( TVideoChanParam, EmVideoResolution, emVideoResolution )
    TYPESTRUCT_MEMBER( TVideoChanParam, u32, wChanMaxBitrate )
    TYPESTRUCT_MEMBER( TVideoChanParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TVideoChanParam, TEncryptKey, tKey )
    TYPESTRUCT_MEMBER( TVideoChanParam, BOOL, bIsH239 )
    TYPESTRUCT_MEMBER( TVideoChanParam, u8, byFrameRate )
TYPESTRUCT_END(  TVideoChanParam )

//TAudioChanParam
TYPESTRUCT_BEGIN( TAudioChanParam )
    TYPESTRUCT_MEMBER( TAudioChanParam, EmAudioFormat, emAudioFormat )
    TYPESTRUCT_MEMBER( TAudioChanParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TAudioChanParam, TEncryptKey, tKey )
TYPESTRUCT_END(  TAudioChanParam )

//TVODUserInfo
TYPESTRUCT_BEGIN( TVODUserInfo )
    TYPESTRUCT_MEMBER( TVODUserInfo, TIPTransAddr, m_tIp )
    TYPESTRUCT_MEMBER( TVODUserInfo, s8, m_achUserName )
    TYPESTRUCT_MEMBER( TVODUserInfo, s8, m_achUserPass )
    TYPESTRUCT_MEMBER( TVODUserInfo, BOOL, m_bRecordNamePass )
TYPESTRUCT_END(  TVODUserInfo )

//TVODFile
TYPESTRUCT_BEGIN( TVODFile )
    TYPESTRUCT_MEMBER( TVODFile, s8, achName )
    TYPESTRUCT_MEMBER( TVODFile, BOOL, bIsFile )
    TYPESTRUCT_MEMBER( TVODFile, u32, dwFileSize )
    TYPESTRUCT_MEMBER( TVODFile, BOOL, bIsInfoValid )
    TYPESTRUCT_MEMBER( TVODFile, u32, dwRecordTime )
    TYPESTRUCT_MEMBER( TVODFile, u32, dwDuration )
    TYPESTRUCT_MEMBER( TVODFile, EmAudioFormat, emAudio )
    TYPESTRUCT_MEMBER( TVODFile, EmVideoFormat, emPrimoVideo )
    TYPESTRUCT_MEMBER( TVODFile, EmVideoFormat, emSecondVideo )
TYPESTRUCT_END(  TVODFile )

//TE1Group
TYPESTRUCT_BEGIN( TE1Group )
    TYPESTRUCT_MEMBER( TE1Group, u8, byGroupIndex )
    TYPESTRUCT_MEMBER( TE1Group, u32, dwE1Mask )
    TYPESTRUCT_MEMBER( TE1Group, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TE1Group, u32_ip, dwIPMask )
    TYPESTRUCT_MEMBER( TE1Group, EmDLProtocol, emProtocol )
    TYPESTRUCT_MEMBER( TE1Group, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TE1Group, EmAuthenticationType, emAuthenticationType )
    TYPESTRUCT_MEMBER( TE1Group, u32, dwFragMinPackageLen )
    TYPESTRUCT_MEMBER( TE1Group, s8, achSvrUsrName )
    TYPESTRUCT_MEMBER( TE1Group, s8, achSvrUsrPwd )
    TYPESTRUCT_MEMBER( TE1Group, s8, achSentUsrName )
    TYPESTRUCT_MEMBER( TE1Group, s8, achSentUsrPwd )
    TYPESTRUCT_MEMBER( TE1Group, u32, dwVal )
TYPESTRUCT_END(  TE1Group )

//TVideoSourceInfo
TYPESTRUCT_BEGIN( TVideoSourceInfo )
    TYPESTRUCT_MEMBER( TVideoSourceInfo, EmMtVideoPort, emVideoPort )
    TYPESTRUCT_MEMBER( TVideoSourceInfo, s8, achPortName )
TYPESTRUCT_END(  TVideoSourceInfo )

//TExternalMatrixInfo
TYPESTRUCT_BEGIN( TExternalMatrixInfo )
    TYPESTRUCT_MEMBER( TExternalMatrixInfo, s8, TypeName )
    TYPESTRUCT_MEMBER( TExternalMatrixInfo, u8, OutPort )
    TYPESTRUCT_MEMBER( TExternalMatrixInfo, u8, InPortTotal )
TYPESTRUCT_END(  TExternalMatrixInfo )

//TAVInnerMatrixScheme
TYPESTRUCT_BEGIN( TAVInnerMatrixScheme )
    TYPESTRUCT_MEMBER( TAVInnerMatrixScheme, EmMatrixType, emType )
    TYPESTRUCT_MEMBER( TAVInnerMatrixScheme, s8, achName )
    TYPESTRUCT_MEMBER( TAVInnerMatrixScheme, u8, byIndex )
    TYPESTRUCT_MEMBER( TAVInnerMatrixScheme, u8, abyOutPort2InPort )
    TYPESTRUCT_MATRIX( TAVInnerMatrixScheme, s8, achOutPortName )
    TYPESTRUCT_MATRIX( TAVInnerMatrixScheme, s8, achInPortName )
TYPESTRUCT_END(  TAVInnerMatrixScheme )

//TBitRateAdjust
TYPESTRUCT_BEGIN( TBitRateAdjust )
    TYPESTRUCT_MEMBER( TBitRateAdjust, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TBitRateAdjust, u16, wInterval )
    TYPESTRUCT_MEMBER( TBitRateAdjust, u16, wLostTimes )
    TYPESTRUCT_MEMBER( TBitRateAdjust, u16, wDescRatio )
    TYPESTRUCT_MEMBER( TBitRateAdjust, u16, wLowDescRatio )
    TYPESTRUCT_MEMBER( TBitRateAdjust, u16, wDelayInterval )
TYPESTRUCT_END(  TBitRateAdjust )

//TCodecPackStat
TYPESTRUCT_BEGIN( TCodecPackStat )
    TYPESTRUCT_MEMBER( TCodecPackStat, u16, wBitrate )
    TYPESTRUCT_MEMBER( TCodecPackStat, u16, wAvrBitrate )
    TYPESTRUCT_MEMBER( TCodecPackStat, u32, dwLostPacks )
    TYPESTRUCT_MEMBER( TCodecPackStat, u32, dwTotalPacks )
    TYPESTRUCT_MEMBER( TCodecPackStat, u32, dwFrames )
    TYPESTRUCT_MEMBER( TCodecPackStat, u8, byLostFrameRate )
TYPESTRUCT_END(  TCodecPackStat )

//TVideoStatistics
TYPESTRUCT_BEGIN( TVideoStatistics )
    TYPESTRUCT_MEMBER( TVideoStatistics, BOOL, bH239 )
    TYPESTRUCT_MEMBER( TVideoStatistics, EmVideoFormat, emFormat )
    TYPESTRUCT_MEMBER( TVideoStatistics, EmVideoResolution, emRes )
    TYPESTRUCT_MEMBER( TVideoStatistics, TCodecPackStat, tPack )
TYPESTRUCT_END(  TVideoStatistics )

//TAudioStatistics
TYPESTRUCT_BEGIN( TAudioStatistics )
    TYPESTRUCT_MEMBER( TAudioStatistics, EmAudioFormat, emFormat )
    TYPESTRUCT_MEMBER( TAudioStatistics, TCodecPackStat, tPack )
TYPESTRUCT_END(  TAudioStatistics )

//TCapType
TYPESTRUCT_BEGIN( TCapType )
    TYPESTRUCT_MEMBER( TCapType, s8, m_achCapFileName )
    TYPESTRUCT_MEMBER( TCapType, EmCapType, emCapType )
TYPESTRUCT_END(  TCapType )

//TCallInfoStatistics
TYPESTRUCT_BEGIN( TCallInfoStatistics )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, u16, wCallBitrate )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, EmEncryptArithmetic, emRecvEncrypt )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, EmEncryptArithmetic, emSendEncrypt )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TAudioStatistics, tRecvAudio )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TAudioStatistics, tSendAudio )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TVideoStatistics, tPrimoRecvVideo )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TVideoStatistics, tPrimoSendVideo )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TVideoStatistics, tSencodRecvVideo )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TVideoStatistics, tSecondSendVideo )
TYPESTRUCT_END(  TCallInfoStatistics )

//TDualStreamBoxInfo
TYPESTRUCT_BEGIN( TDualStreamBoxInfo )
    TYPESTRUCT_MEMBER( TDualStreamBoxInfo, BOOL, m_bUsed )
    TYPESTRUCT_MEMBER( TDualStreamBoxInfo, u32_ip, m_dwIp )
    TYPESTRUCT_MEMBER( TDualStreamBoxInfo, u16, m_wPort )
TYPESTRUCT_END(  TDualStreamBoxInfo )

//TFileTransfer
TYPESTRUCT_BEGIN( TFileTransfer )
    TYPESTRUCT_MEMBER( TFileTransfer, u16, wProtocolIdentifer )
    TYPESTRUCT_MEMBER( TFileTransfer, u16, wFileSliceNo )
    TYPESTRUCT_MEMBER( TFileTransfer, u8, byType )
    TYPESTRUCT_MEMBER( TFileTransfer, u8, byRspInfo )
    TYPESTRUCT_MEMBER( TFileTransfer, u16, wFileIdentifer )
    TYPESTRUCT_MEMBER( TFileTransfer, u16, wPakageMaxLen )
    TYPESTRUCT_MEMBER( TFileTransfer, u16, wDataLen )
TYPESTRUCT_END(  TFileTransfer )

//TDVBNetSession
TYPESTRUCT_BEGIN( TDVBNetSession )
    TYPESTRUCT_MEMBER( TDVBNetSession, u32_ip, m_dwRTPAddr )
    TYPESTRUCT_MEMBER( TDVBNetSession, u16, m_wRTPPort )
    TYPESTRUCT_MEMBER( TDVBNetSession, u32_ip, m_dwRTCPAddr )
    TYPESTRUCT_MEMBER( TDVBNetSession, u16, m_wRTCPPort )
TYPESTRUCT_END(  TDVBNetSession )

//TDVBNetSndParam
TYPESTRUCT_BEGIN( TDVBNetSndParam )
    TYPESTRUCT_MEMBER( TDVBNetSndParam, u8, m_byNum )
    TYPESTRUCT_MEMBER( TDVBNetSndParam, TDVBNetSession, m_tLocalNet )
    TYPESTRUCT_MEMBER( TDVBNetSndParam, TDVBNetSession, m_tRemoteNet )
TYPESTRUCT_END(  TDVBNetSndParam )

//TDVBLocalNetParam
TYPESTRUCT_BEGIN( TDVBLocalNetParam )
    TYPESTRUCT_MEMBER( TDVBLocalNetParam, TDVBNetSession, m_tLocalNet )
    TYPESTRUCT_MEMBER( TDVBLocalNetParam, u32_ip, m_dwRtcpBackAddr )
    TYPESTRUCT_MEMBER( TDVBLocalNetParam, u16, m_wRtcpBackPort )
TYPESTRUCT_END(  TDVBLocalNetParam )

//TDVBVideoEncParam
TYPESTRUCT_BEGIN( TDVBVideoEncParam )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byEncType )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byRcMode )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u16, m_byMaxKeyFrameInterval )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byMaxQuant )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byMinQuant )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byReserved1 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byReserved2 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byReserved3 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u16, m_wBitRate )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u16, m_wReserved4 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u32, m_dwSndNetBand )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u32, m_dwReserved5 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byPalNtsc )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byCapPort )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byFrameRate )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byImageQulity )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byReserved6 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u16, m_wVideoWidth )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u16, m_wVideoHeight )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byFrameFmt )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byFrmRateCanSet )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byFrmRateLittleThanOne )
TYPESTRUCT_END(  TDVBVideoEncParam )

//TSitecallInformation
TYPESTRUCT_BEGIN( TSitecallInformation )
    TYPESTRUCT_MEMBER( TSitecallInformation, BOOL, m_bIsCustomConf )
    TYPESTRUCT_MEMBER( TSitecallInformation, s8, m_achConfName )
    TYPESTRUCT_MEMBER( TSitecallInformation, s8, m_achConfPwd )
    TYPESTRUCT_MEMBER( TSitecallInformation, BOOL, m_bLocalPay )
    TYPESTRUCT_MEMBER( TSitecallInformation, s8, m_achConfCard )
    TYPESTRUCT_MEMBER( TSitecallInformation, s8, m_achConfCardPwd )
    TYPESTRUCT_MEMBER( TSitecallInformation, u8, m_byMultiPicCount )
    TYPESTRUCT_MEMBER( TSitecallInformation, EmCallRate, m_emRate )
    TYPESTRUCT_MEMBER( TSitecallInformation, EmVideoFormat, m_emVideoType )
    TYPESTRUCT_MEMBER( TSitecallInformation, EmVideoResolution, m_emVideoFormat )
    TYPESTRUCT_MEMBER( TSitecallInformation, EmAudioFormat, m_emAudioFormat )
    TYPESTRUCT_MEMBER( TSitecallInformation, u8, m_byTerninalCount )
    TYPESTRUCT_MEMBER( TSitecallInformation, TMtAddr, m_atTerminalE164Info )
    TYPESTRUCT_MEMBER( TSitecallInformation, TMtAddr, m_atTerminalH323Info )
TYPESTRUCT_END(  TSitecallInformation )

//TTransparentSerial
TYPESTRUCT_BEGIN( TTransparentSerial )
    TYPESTRUCT_MEMBER( TTransparentSerial, EmSerialType, m_emComType )
    TYPESTRUCT_MEMBER( TTransparentSerial, u32, m_nDataLen )
    TYPESTRUCT_MEMBER( TTransparentSerial, s8, m_achData )
TYPESTRUCT_END(  TTransparentSerial )

//TPeerCapabilityInfo
TYPESTRUCT_BEGIN( TPeerCapabilityInfo )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bMix )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bVAC )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bCustomVMP )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bAutoVMP )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bEndConf )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bInvateMt )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bDropMt )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bSelSpeaker )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bSelChair )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bSelSource )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bFECC )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bQuiet )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bMute )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bConfReq )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bOnlineList )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bOfflineList )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bPicSwitch )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bSelSpeakingUser )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bForceBroadcast )
TYPESTRUCT_END(  TPeerCapabilityInfo )

//TRapidKey
TYPESTRUCT_BEGIN( TRapidKey )
    TYPESTRUCT_MEMBER( TRapidKey, EmMtVideoPort, emMainVidSrcBtn )
    TYPESTRUCT_MEMBER( TRapidKey, EmHotKeyType, emRedBtn )
    TYPESTRUCT_MEMBER( TRapidKey, EmHotKeyType, emYellowBtn )
    TYPESTRUCT_MEMBER( TRapidKey, EmHotKeyType, emGreenBtn )
TYPESTRUCT_END(  TRapidKey )

//TVerFileInfo
TYPESTRUCT_BEGIN( TVerFileInfo )
    TYPESTRUCT_MEMBER( TVerFileInfo, EmMtOSType, m_emFileType )
    TYPESTRUCT_MEMBER( TVerFileInfo, u32, m_dwFileSize )
    TYPESTRUCT_MEMBER( TVerFileInfo, s8, m_szFileName )
TYPESTRUCT_END(  TVerFileInfo )

//TVerInfo
TYPESTRUCT_BEGIN( TVerInfo )
    TYPESTRUCT_MEMBER( TVerInfo, u8, m_byFileNum )
    TYPESTRUCT_MEMBER( TVerInfo, s8, m_achBugReport )
    TYPESTRUCT_MEMBER( TVerInfo, s8, m_achSoftVer )
    TYPESTRUCT_MEMBER( TVerInfo, TVerFileInfo, m_atVerFile )
TYPESTRUCT_END(  TVerInfo )

//TFecInfo
TYPESTRUCT_BEGIN( TFecInfo )
    TYPESTRUCT_MEMBER( TFecInfo, BOOL, m_bEnableFec )
    TYPESTRUCT_MEMBER( TFecInfo, u8, m_byAlgorithm )
    TYPESTRUCT_MEMBER( TFecInfo, u16, m_wPackLen )
    TYPESTRUCT_MEMBER( TFecInfo, BOOL, m_bIntraFrame )
    TYPESTRUCT_MEMBER( TFecInfo, u32, m_dwDataPackNum )
    TYPESTRUCT_MEMBER( TFecInfo, u32, m_dwCrcPackNum )
TYPESTRUCT_END(  TFecInfo )

//TVInnerMatrixScheme
TYPESTRUCT_BEGIN( TVInnerMatrixScheme )
    TYPESTRUCT_MEMBER( TVInnerMatrixScheme, u8, byIndex )
    TYPESTRUCT_MEMBER( TVInnerMatrixScheme, s8, achName )
    TYPESTRUCT_MEMBER( TVInnerMatrixScheme, u8, abyOutPort2InPort )
    TYPESTRUCT_MEMBER( TVInnerMatrixScheme, u8, abyDVIMode )
    TYPESTRUCT_MATRIX( TVInnerMatrixScheme, s8, achOutPortName )
    TYPESTRUCT_MATRIX( TVInnerMatrixScheme, s8, achInPortName )
TYPESTRUCT_END(  TVInnerMatrixScheme )

//TAddrEntry
TYPESTRUCT_BEGIN( TAddrEntry )
    TYPESTRUCT_MEMBER( TAddrEntry, s8, m_achEntryName )
    TYPESTRUCT_MEMBER( TAddrEntry, s8, m_achIpaddr )
    TYPESTRUCT_MEMBER( TAddrEntry, u32, m_dwCallTime )
    TYPESTRUCT_MEMBER( TAddrEntry, u16, m_wCallRate )
    TYPESTRUCT_MEMBER( TAddrEntry, BOOL, m_bTeleCall )
TYPESTRUCT_END(  TAddrEntry )

//TPxyIPCfg
TYPESTRUCT_BEGIN( TPxyIPCfg )
    TYPESTRUCT_MEMBER( TPxyIPCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TPxyIPCfg, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TPxyIPCfg, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TPxyIPCfg, u32_ip, dwGateway )
TYPESTRUCT_END(  TPxyIPCfg )

//TWifiLinkInfo
TYPESTRUCT_BEGIN( TWifiLinkInfo )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, s8, achSSID )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, s8, achBssMacAddr )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u32, dwSignalLevel )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u32, dwLinkRate )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u32, dwChannel )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u8, byAuthType )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u8, byEncrytoType )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u8, byNetType )
TYPESTRUCT_END(  TWifiLinkInfo )

//TWifiScanResult
TYPESTRUCT_BEGIN( TWifiScanResult )
    TYPESTRUCT_MEMBER( TWifiScanResult, u32, dwBssNum )
    TYPESTRUCT_MEMBER( TWifiScanResult, TWifiLinkInfo, tLinkInfo )
TYPESTRUCT_END(  TWifiScanResult )

//TWifiLinkCfgItem
TYPESTRUCT_BEGIN( TWifiLinkCfgItem )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, u32, dwId )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achCfgName )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, TWifiLinkInfo, tWifiLinkInfo )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achWepKey1 )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achWepKey2 )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achWepKey3 )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achWepKey4 )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achWpaPasswd )
TYPESTRUCT_END(  TWifiLinkCfgItem )

//TWiFiBSSIDInfo
TYPESTRUCT_BEGIN( TWiFiBSSIDInfo )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, u8, byPSKOFF )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, EmWiFiNetType, emNetType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, EmWiFiEncryptType, emEncryptType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, EmWiFiEncryptArithmetic, emArithType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, BOOL, bEncrypt )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, u32, dwChannel )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, u32, dwBeaconInterval )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, u32, dwLinkRate )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, u32, dwSignalLevel )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, s8, achBSSMacAddr )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, s8, achSSID )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, s8, achPasswd )
TYPESTRUCT_END(  TWiFiBSSIDInfo )

//TWiFiBSSIDCfg
TYPESTRUCT_BEGIN( TWiFiBSSIDCfg )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, u8, byPSKOFF )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, EmWiFiNetType, emNetType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, EmWiFiEncryptType, emEncryptType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, EmWiFiEncryptArithmetic, emArithType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, BOOL, bEncrypt )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, u32, dwCfgPri )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, u32, dwChannel )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, s8, achSSID )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, s8, achPassword )
TYPESTRUCT_END(  TWiFiBSSIDCfg )

//TGkRegInfo
TYPESTRUCT_BEGIN( TGkRegInfo )
    TYPESTRUCT_MEMBER( TGkRegInfo, BOOL, bRegisted )
    TYPESTRUCT_MEMBER( TGkRegInfo, EmGKRegFailedReason, emReason )
TYPESTRUCT_END(  TGkRegInfo )

//TSipRegResult
TYPESTRUCT_BEGIN( TSipRegResult )
    TYPESTRUCT_MEMBER( TSipRegResult, BOOL, bRegistered )
    TYPESTRUCT_MEMBER( TSipRegResult, EmSipRegFailedReason, emReason )
TYPESTRUCT_END(  TSipRegResult )

//THdAudioPort
TYPESTRUCT_BEGIN( THdAudioPort )
    TYPESTRUCT_MEMBER( THdAudioPort, u8, abHdAudPortIn )
    TYPESTRUCT_MEMBER( THdAudioPort, u8, abHdAudPortOut )
TYPESTRUCT_END(  THdAudioPort )

//TMiscCfg
TYPESTRUCT_BEGIN( TMiscCfg )
    TYPESTRUCT_MEMBER( TMiscCfg, BOOL, bUseSlice )
TYPESTRUCT_END(  TMiscCfg )

//TVideoDisplayFrm
TYPESTRUCT_BEGIN( TVideoDisplayFrm )
    TYPESTRUCT_MEMBER( TVideoDisplayFrm, u32, m_dw1080PFrm )
    TYPESTRUCT_MEMBER( TVideoDisplayFrm, u32, m_dw1080IFrm )
    TYPESTRUCT_MEMBER( TVideoDisplayFrm, u32, m_dwVGAFrm )
    TYPESTRUCT_MEMBER( TVideoDisplayFrm, u32, m_dw720PFrm )
    TYPESTRUCT_MEMBER( TVideoDisplayFrm, u32, m_dwSDFrm )
TYPESTRUCT_END(  TVideoDisplayFrm )

//TDownLoadPara
TYPESTRUCT_BEGIN( TDownLoadPara )
    TYPESTRUCT_MEMBER( TDownLoadPara, u8, byFileType )
    TYPESTRUCT_MEMBER( TDownLoadPara, u8, byFileCount )
    TYPESTRUCT_MEMBER( TDownLoadPara, s8, m_achFileName )
TYPESTRUCT_END(  TDownLoadPara )

//TSecurePwd
TYPESTRUCT_BEGIN( TSecurePwd )
    TYPESTRUCT_MEMBER( TSecurePwd, BOOL, bUserCfgPwd )
    TYPESTRUCT_MEMBER( TSecurePwd, s8, achUserCfgPwd )
TYPESTRUCT_END(  TSecurePwd )

//TMtBackBGDColor
TYPESTRUCT_BEGIN( TMtBackBGDColor )
    TYPESTRUCT_MEMBER( TMtBackBGDColor, u8, RColor )
    TYPESTRUCT_MEMBER( TMtBackBGDColor, u8, GColor )
    TYPESTRUCT_MEMBER( TMtBackBGDColor, u8, BColor )
    TYPESTRUCT_MEMBER( TMtBackBGDColor, u8, u8Transparency )
TYPESTRUCT_END(  TMtBackBGDColor )

//TSipCfg
TYPESTRUCT_BEGIN( TSipCfg )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achDisplayName )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achUserName )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achPassword )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achHostDomain )
    TYPESTRUCT_MEMBER( TSipCfg, u16, wHostPort )
    TYPESTRUCT_MEMBER( TSipCfg, BOOL, bUseRegistrar )
    TYPESTRUCT_MEMBER( TSipCfg, u32_ip, dwRegistrarIp )
    TYPESTRUCT_MEMBER( TSipCfg, u16, wRegistrarPort )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achRegistrarDomain )
    TYPESTRUCT_MEMBER( TSipCfg, u16, wExpire )
    TYPESTRUCT_MEMBER( TSipCfg, BOOL, bUseProxy )
    TYPESTRUCT_MEMBER( TSipCfg, u32_ip, dwProxyIp )
    TYPESTRUCT_MEMBER( TSipCfg, u16, wProxyPort )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achProxyDomain )
TYPESTRUCT_END(  TSipCfg )

//TMtAddBannerParam
TYPESTRUCT_BEGIN( TMtAddBannerParam )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwXPos )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwYPos )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwWidth )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwHeight )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwBMPWight )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwBMPHeight )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwBannerCharHeight )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, TMtBackBGDColor, tBackBGDColor )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwBGDClarity )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwPicClarity )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwRunMode )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwRunSpeed )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwRunTimes )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, bRunForever )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwHaltTime )
TYPESTRUCT_END(  TMtAddBannerParam )

//TMtBmpInfo
TYPESTRUCT_BEGIN( TMtBmpInfo )
    TYPESTRUCT_MEMBER( TMtBmpInfo, u32, dwWidth )
    TYPESTRUCT_MEMBER( TMtBmpInfo, u32, dwHeight )
TYPESTRUCT_END(  TMtBmpInfo )

//TMtFullBannerParam
TYPESTRUCT_BEGIN( TMtFullBannerParam )
    TYPESTRUCT_MEMBER( TMtFullBannerParam, TMtBmpInfo, tBmpInfo )
    TYPESTRUCT_MEMBER( TMtFullBannerParam, TMtAddBannerParam, tBannerParam )
    TYPESTRUCT_MEMBER( TMtFullBannerParam, u32, Reserver )
TYPESTRUCT_END(  TMtFullBannerParam )

//TMTBmpInfo
TYPESTRUCT_BEGIN( TMTBmpInfo )
    TYPESTRUCT_MEMBER( TMTBmpInfo, u32, dwWidth )
    TYPESTRUCT_MEMBER( TMTBmpInfo, u32, dwHeight )
TYPESTRUCT_END(  TMTBmpInfo )

//TMTAddLogoParam
TYPESTRUCT_BEGIN( TMTAddLogoParam )
    TYPESTRUCT_MEMBER( TMTAddLogoParam, u32, dwXPos )
    TYPESTRUCT_MEMBER( TMTAddLogoParam, u32, dwYPos )
    TYPESTRUCT_MEMBER( TMTAddLogoParam, u32, dwLogoWidth )
    TYPESTRUCT_MEMBER( TMTAddLogoParam, u32, dwLogoHeight )
    TYPESTRUCT_MEMBER( TMTAddLogoParam, TMtBackBGDColor, tBackBGDColor )
TYPESTRUCT_END(  TMTAddLogoParam )

//TMTFullLogoParam
TYPESTRUCT_BEGIN( TMTFullLogoParam )
    TYPESTRUCT_MEMBER( TMTFullLogoParam, TMTBmpInfo, tBmpInfo )
    TYPESTRUCT_MEMBER( TMTFullLogoParam, TMTAddLogoParam, tLogoParam )
TYPESTRUCT_END(  TMTFullLogoParam )

//TMtcBoxCallCfg
TYPESTRUCT_BEGIN( TMtcBoxCallCfg )
    TYPESTRUCT_MEMBER( TMtcBoxCallCfg, u8, byUseIndex )
    TYPESTRUCT_MEMBER( TMtcBoxCallCfg, u32_ip, dwIp )
    TYPESTRUCT_MEMBER( TMtcBoxCallCfg, s8, achE164 )
    TYPESTRUCT_MEMBER( TMtcBoxCallCfg, s8, achMtAlias )
    TYPESTRUCT_MEMBER( TMtcBoxCallCfg, u16, wCallRate )
TYPESTRUCT_END(  TMtcBoxCallCfg )

//TMTRSParam
TYPESTRUCT_BEGIN( TMTRSParam )
    TYPESTRUCT_MEMBER( TMTRSParam, u16, m_wFirstTimeSpan )
    TYPESTRUCT_MEMBER( TMTRSParam, u16, m_wSecondTimeSpan )
    TYPESTRUCT_MEMBER( TMTRSParam, u16, m_wThirdTimeSpan )
    TYPESTRUCT_MEMBER( TMTRSParam, u16, m_wRejectTimeSpan )
TYPESTRUCT_END(  TMTRSParam )

//TMtRecStartParam
TYPESTRUCT_BEGIN( TMtRecStartParam )
    TYPESTRUCT_MEMBER( TMtRecStartParam, EmSite, emSite )
    TYPESTRUCT_MEMBER( TMtRecStartParam, BOOL, bIsRecSecVideo )
    TYPESTRUCT_MEMBER( TMtRecStartParam, u8, m_byPublishMode )
    TYPESTRUCT_MEMBER( TMtRecStartParam, s8, achFileName )
TYPESTRUCT_END(  TMtRecStartParam )

//TMtRecRegParam
TYPESTRUCT_BEGIN( TMtRecRegParam )
    TYPESTRUCT_MEMBER( TMtRecRegParam, u32_ip, dwRecIp )
    TYPESTRUCT_MEMBER( TMtRecRegParam, u32_ip, dwHostIp )
    TYPESTRUCT_MEMBER( TMtRecRegParam, s8, achDirName )
TYPESTRUCT_END(  TMtRecRegParam )

//TMtRecParam
TYPESTRUCT_BEGIN( TMtRecParam )
    TYPESTRUCT_MEMBER( TMtRecParam, u8, byState )
    TYPESTRUCT_MEMBER( TMtRecParam, TMtRecRegParam, tMtRecRegParam )
    TYPESTRUCT_MEMBER( TMtRecParam, TMtRecStartParam, tMtRecStartParam )
TYPESTRUCT_END(  TMtRecParam )

//TMtCnsParam
TYPESTRUCT_BEGIN( TMtCnsParam )
    TYPESTRUCT_MEMBER( TMtCnsParam, u32_ip, dwCnsIp )
    TYPESTRUCT_MEMBER( TMtCnsParam, s8, achRoomName )
    TYPESTRUCT_MEMBER( TMtCnsParam, u16, wPos )
    TYPESTRUCT_MEMBER( TMtCnsParam, u16, wPosCount )
    TYPESTRUCT_MEMBER( TMtCnsParam, BOOL, bIsDual )
TYPESTRUCT_END(  TMtCnsParam )

//TLoginRet
TYPESTRUCT_BEGIN( TLoginRet )
    TYPESTRUCT_MEMBER( TLoginRet, EmTpLoginUmsRet, m_emRet )
    TYPESTRUCT_MEMBER( TLoginRet, u32, m_dwUserID )
    TYPESTRUCT_MEMBER( TLoginRet, u32, m_dwErrorCode )
    TYPESTRUCT_MEMBER( TLoginRet, u8, m_byNumber )
    TYPESTRUCT_MEMBER( TLoginRet, u8, m_byLockNumber )
TYPESTRUCT_END(  TLoginRet )

//TTPTransAddr
TYPESTRUCT_BEGIN( TTPTransAddr )
    TYPESTRUCT_MEMBER( TTPTransAddr, u32_ip, m_dwIP )
    TYPESTRUCT_MEMBER( TTPTransAddr, u16, m_wPort )
TYPESTRUCT_END(  TTPTransAddr )

//TTPName
TYPESTRUCT_BEGIN( TTPName )
    TYPESTRUCT_MEMBER( TTPName, s8, m_abyAlias )
TYPESTRUCT_END(  TTPName )

//TTPAlias
TYPESTRUCT_BEGIN( TTPAlias )
    TYPESTRUCT_MEMBER( TTPAlias, EmTpAliasType, m_byType )
    TYPESTRUCT_MEMBER( TTPAlias, s8, m_abyAlias )
TYPESTRUCT_END(  TTPAlias )

//TTpCallAddr
TYPESTRUCT_BEGIN( TTpCallAddr )
    TYPESTRUCT_MEMBER( TTpCallAddr, TTPAlias, m_tAlias )
    TYPESTRUCT_MEMBER( TTpCallAddr, TTPAlias, m_tE164 )
    TYPESTRUCT_MEMBER( TTpCallAddr, u32_ip, m_dwIP )
    TYPESTRUCT_MEMBER( TTpCallAddr, BOOL32, m_bAliasIP )
    TYPESTRUCT_MEMBER( TTpCallAddr, EmTpAliasType, m_byCallType )
TYPESTRUCT_END(  TTpCallAddr )

//TTpCallEp
TYPESTRUCT_BEGIN( TTpCallEp )
    TYPESTRUCT_MEMBER( TTpCallEp, BOOL32, m_bAliasIP )
    TYPESTRUCT_MEMBER( TTpCallEp, TTpCallAddr, m_tCallAddr )
    TYPESTRUCT_MEMBER( TTpCallEp, u16, m_wConfID )
TYPESTRUCT_END(  TTpCallEp )

//TTpEncryptKey
TYPESTRUCT_BEGIN( TTpEncryptKey )
    TYPESTRUCT_MEMBER( TTpEncryptKey, u8, byLen )
    TYPESTRUCT_MEMBER( TTpEncryptKey, u8, byKey )
    TYPESTRUCT_MEMBER( TTpEncryptKey, EmTPEncryptType, emTPEncryptType )
    TYPESTRUCT_MEMBER( TTpEncryptKey, EmQtEncryptFrequency, emQtKeyFrequency )
TYPESTRUCT_END(  TTpEncryptKey )

//TTpQtEncryptCfg
TYPESTRUCT_BEGIN( TTpQtEncryptCfg )
    TYPESTRUCT_MEMBER( TTpQtEncryptCfg, BOOL, m_bOpen )
    TYPESTRUCT_MEMBER( TTpQtEncryptCfg, u32_ip, m_dwQtIP )
    TYPESTRUCT_MEMBER( TTpQtEncryptCfg, u32, m_dwQtID )
TYPESTRUCT_END(  TTpQtEncryptCfg )

//TTpQtEncryptKey
TYPESTRUCT_BEGIN( TTpQtEncryptKey )
    TYPESTRUCT_MEMBER( TTpQtEncryptKey, u32, m_dwMediaHandl )
    TYPESTRUCT_MEMBER( TTpQtEncryptKey, u32, m_dwKeyLen )
    TYPESTRUCT_MEMBER( TTpQtEncryptKey, u8, m_byMediaKey1 )
    TYPESTRUCT_MEMBER( TTpQtEncryptKey, u8, m_byMediaKey2 )
    TYPESTRUCT_MEMBER( TTpQtEncryptKey, u8, m_byMediaKey3 )
    TYPESTRUCT_MEMBER( TTpQtEncryptKey, u8, m_byMediaKey4 )
    TYPESTRUCT_MEMBER( TTpQtEncryptKey, EmQtEncryptFrequency, m_emQtKeyFrequency )
    TYPESTRUCT_MEMBER( TTpQtEncryptKey, u32, m_dwQtFlag )
    TYPESTRUCT_MEMBER( TTpQtEncryptKey, u16, m_wConverIndex )
TYPESTRUCT_END(  TTpQtEncryptKey )

//TTPMediaTransAddr
TYPESTRUCT_BEGIN( TTPMediaTransAddr )
    TYPESTRUCT_MEMBER( TTPMediaTransAddr, TTPTransAddr, m_tRtpAddr )
    TYPESTRUCT_MEMBER( TTPMediaTransAddr, TTPTransAddr, m_tRtcpAddr )
    TYPESTRUCT_MEMBER( TTPMediaTransAddr, TTPTransAddr, m_tBackRtcpAddr )
TYPESTRUCT_END(  TTPMediaTransAddr )

//TTPVideoCap
TYPESTRUCT_BEGIN( TTPVideoCap )
    TYPESTRUCT_MEMBER( TTPVideoCap, EmTpVideoFormat, m_emFormat )
    TYPESTRUCT_MEMBER( TTPVideoCap, EmTpVideoResolution, m_emRes )
    TYPESTRUCT_MEMBER( TTPVideoCap, u16, m_byMaxFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoCap, u16, m_wBitrate )
    TYPESTRUCT_MEMBER( TTPVideoCap, TTpEncryptKey, m_tEnc )
    TYPESTRUCT_MEMBER( TTPVideoCap, u16, m_wStaticPayload )
    TYPESTRUCT_MEMBER( TTPVideoCap, u16, m_wDynamicPayload )
    TYPESTRUCT_MEMBER( TTPVideoCap, EmTpVideoQualityLevel, emTpVideoQualityLevel )
TYPESTRUCT_END(  TTPVideoCap )

//TTPAudCap
TYPESTRUCT_BEGIN( TTPAudCap )
    TYPESTRUCT_MEMBER( TTPAudCap, EmTpAudioFormat, m_emFormat )
    TYPESTRUCT_MEMBER( TTPAudCap, u16, m_wStaticPayload )
    TYPESTRUCT_MEMBER( TTPAudCap, u16, m_wDynamicPayload )
    TYPESTRUCT_MEMBER( TTPAudCap, u16, m_wBitrate )
    TYPESTRUCT_MEMBER( TTPAudCap, TTpEncryptKey, m_tEnc )
TYPESTRUCT_END(  TTPAudCap )

//TUmsVidFormat
TYPESTRUCT_BEGIN( TUmsVidFormat )
    TYPESTRUCT_MEMBER( TUmsVidFormat, EmTpVideoFormat, m_emFormat )
    TYPESTRUCT_MEMBER( TUmsVidFormat, EmTpVideoResolution, m_emRes )
    TYPESTRUCT_MEMBER( TUmsVidFormat, u16, m_wFrameRate )
    TYPESTRUCT_MEMBER( TUmsVidFormat, u16, m_wBitrate )
    TYPESTRUCT_MEMBER( TUmsVidFormat, EmTpVideoQualityLevel, m_emQualityLvl )
TYPESTRUCT_END(  TUmsVidFormat )

//TUmsRSParam
TYPESTRUCT_BEGIN( TUmsRSParam )
    TYPESTRUCT_MEMBER( TUmsRSParam, u16, m_wFirstTimeSpan )
    TYPESTRUCT_MEMBER( TUmsRSParam, u16, m_wSecondTimeSpan )
    TYPESTRUCT_MEMBER( TUmsRSParam, u16, m_wThirdTimeSpan )
    TYPESTRUCT_MEMBER( TUmsRSParam, u16, m_wRejectTimeSpan )
TYPESTRUCT_END(  TUmsRSParam )

//TEpAddr
TYPESTRUCT_BEGIN( TEpAddr )
    TYPESTRUCT_MEMBER( TEpAddr, TTpCallAddr, m_tEpAddr )
    TYPESTRUCT_MEMBER( TEpAddr, u16, m_wEpID )
TYPESTRUCT_END(  TEpAddr )

//TAuxMixList
TYPESTRUCT_BEGIN( TAuxMixList )
    TYPESTRUCT_MEMBER( TAuxMixList, u16, m_awList )
    TYPESTRUCT_MEMBER( TAuxMixList, BOOL32, m_bAudMixOn )
    TYPESTRUCT_MEMBER( TAuxMixList, BOOL32, m_bVacOn )
TYPESTRUCT_END(  TAuxMixList )

//TConfAuxMixVacOpr
TYPESTRUCT_BEGIN( TConfAuxMixVacOpr )
    TYPESTRUCT_MEMBER( TConfAuxMixVacOpr, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfAuxMixVacOpr, BOOL32, m_bVacOn )
    TYPESTRUCT_MEMBER( TConfAuxMixVacOpr, u16, m_wOprRet )
TYPESTRUCT_END(  TConfAuxMixVacOpr )

//TConfAuxMixInfo
TYPESTRUCT_BEGIN( TConfAuxMixInfo )
    TYPESTRUCT_MEMBER( TConfAuxMixInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfAuxMixInfo, BOOL32, m_bStart )
    TYPESTRUCT_MEMBER( TConfAuxMixInfo, BOOL32, m_bVacOn )
    TYPESTRUCT_MEMBER( TConfAuxMixInfo, TAuxMixList, m_atAuxMixList )
    TYPESTRUCT_MEMBER( TConfAuxMixInfo, EmDiscussRspRet, m_emRet )
TYPESTRUCT_END(  TConfAuxMixInfo )

//TTPPollInfo
TYPESTRUCT_BEGIN( TTPPollInfo )
    TYPESTRUCT_MEMBER( TTPPollInfo, BOOL, bIsPoll )
    TYPESTRUCT_MEMBER( TTPPollInfo, u16, wPollExpire )
TYPESTRUCT_END(  TTPPollInfo )

//TTPConfBaseInfo
TYPESTRUCT_BEGIN( TTPConfBaseInfo )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, s8, achConfId )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, s8, achConfName )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, s8, achConfNumber )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, s8, achConfPwd )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, BOOL32, bNeedPassword )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u16, wConfDuration )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpVideoFormat, emTpVideoFormat )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpAudioFormat, emTpAudioFormat )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpVideoResolution, emTpResolution )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, BOOL32, bIsAutoVMP )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, BOOL32, bIsMix )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u8, bySecVideoFormat )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpVideoResolution, emTpSecVidRes )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u8, bySecVidFps )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpVideoQualityLevel, emPriVideoQualityLevel )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpVideoQualityLevel, emDualVideoQualityLevel )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u8, byPriVidFps )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u16, wCallRate )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u16, wDualCallRate )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, TTPPollInfo, tPollInfo )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, TConfAuxMixInfo, tConfAudMixInfo )
TYPESTRUCT_END(  TTPConfBaseInfo )

//TUmsAudFormat
TYPESTRUCT_BEGIN( TUmsAudFormat )
    TYPESTRUCT_MEMBER( TUmsAudFormat, EmTpAudioFormat, m_emFormat )
    TYPESTRUCT_MEMBER( TUmsAudFormat, EmTPAACSampleFreq, m_emSampleFreq )
    TYPESTRUCT_MEMBER( TUmsAudFormat, EmTPAACChnlCfg, m_emChnlCfg )
    TYPESTRUCT_MEMBER( TUmsAudFormat, u8, m_byReserve1 )
    TYPESTRUCT_MEMBER( TUmsAudFormat, u8, m_byReserve2 )
TYPESTRUCT_END(  TUmsAudFormat )

//TTPEncrypt
TYPESTRUCT_BEGIN( TTPEncrypt )
    TYPESTRUCT_MEMBER( TTPEncrypt, EmTPEncryptType, m_emEncryptModel )
    TYPESTRUCT_MEMBER( TTPEncrypt, u8, m_byKeyLen )
    TYPESTRUCT_MEMBER( TTPEncrypt, s8, m_achEncKey )
TYPESTRUCT_END(  TTPEncrypt )

//TTPVmpCfgChnl
TYPESTRUCT_BEGIN( TTPVmpCfgChnl )
    TYPESTRUCT_MEMBER( TTPVmpCfgChnl, u16, m_wScrIndx )
    TYPESTRUCT_MEMBER( TTPVmpCfgChnl, TTPAlias, m_tEpAlias )
TYPESTRUCT_END(  TTPVmpCfgChnl )

//TTpVmpMemberCfg
TYPESTRUCT_BEGIN( TTpVmpMemberCfg )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfg, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfg, EMVmpStyle, m_emStyle )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfg, u16, m_wFlag )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfg, u16, m_wTotalNum )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfg, u16, m_wEpNum )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfg, u16, m_wSpeakerIndx )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfg, u16, m_wDualIndx )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfg, BOOL32, m_bFirst )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfg, TTPVmpCfgChnl, m_atEpList )
TYPESTRUCT_END(  TTpVmpMemberCfg )

//TSaveVmpCfg
TYPESTRUCT_BEGIN( TSaveVmpCfg )
    TYPESTRUCT_MEMBER( TSaveVmpCfg, EMVmpStyle, m_emStyle )
    TYPESTRUCT_MEMBER( TSaveVmpCfg, u16, m_wEpNum )
    TYPESTRUCT_MEMBER( TSaveVmpCfg, TTPAlias, m_atEpList )
TYPESTRUCT_END(  TSaveVmpCfg )

//TUmsConfBase
TYPESTRUCT_BEGIN( TUmsConfBase )
    TYPESTRUCT_MEMBER( TUmsConfBase, s8, m_achConfName )
    TYPESTRUCT_MEMBER( TUmsConfBase, s8, m_achConfE164 )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wConfBitRate )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wBpConfBitRate )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wHpDualBitRate )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wBpDualBitRate )
    TYPESTRUCT_MEMBER( TUmsConfBase, u32, m_dwPersistenceTime )
    TYPESTRUCT_MEMBER( TUmsConfBase, time_t, m_tStartTime )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wAudFmtNum )
    TYPESTRUCT_MEMBER( TUmsConfBase, TUmsAudFormat, m_atAudFmt )
    TYPESTRUCT_MEMBER( TUmsConfBase, TUmsRSParam, m_tRsParam )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wDefaultChairMan )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wMainNum )
    TYPESTRUCT_MEMBER( TUmsConfBase, TUmsVidFormat, m_atTpMainVideoRes )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wMinorNum )
    TYPESTRUCT_MEMBER( TUmsConfBase, TUmsVidFormat, m_atTpMinorVideoRes )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wUpBandWid )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wDownBandWid )
    TYPESTRUCT_MEMBER( TUmsConfBase, TTPEncrypt, m_tEncrypt )
    TYPESTRUCT_MEMBER( TUmsConfBase, TSaveVmpCfg, m_tVmpPlanCfg )
TYPESTRUCT_END(  TUmsConfBase )

//TChairConfInfo
TYPESTRUCT_BEGIN( TChairConfInfo )
    TYPESTRUCT_MEMBER( TChairConfInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TChairConfInfo, u32, m_dwBeginTime )
    TYPESTRUCT_MEMBER( TChairConfInfo, TTPAlias, m_tConfName )
    TYPESTRUCT_MEMBER( TChairConfInfo, TTPAlias, m_tChairName )
TYPESTRUCT_END(  TChairConfInfo )

//TEpAddrList
TYPESTRUCT_BEGIN( TEpAddrList )
    TYPESTRUCT_MEMBER( TEpAddrList, u16, m_wNum )
    TYPESTRUCT_MEMBER( TEpAddrList, TEpAddr, m_tCnsList )
TYPESTRUCT_END(  TEpAddrList )

//TConfTurnList
TYPESTRUCT_BEGIN( TConfTurnList )
    TYPESTRUCT_MEMBER( TConfTurnList, u16, m_wInterval )
    TYPESTRUCT_MEMBER( TConfTurnList, u16, m_wNum )
    TYPESTRUCT_MEMBER( TConfTurnList, BOOL32, m_bPollOn )
    TYPESTRUCT_MEMBER( TConfTurnList, u16, m_awList )
TYPESTRUCT_END(  TConfTurnList )

//TTpVmpMemberCfgInd
TYPESTRUCT_BEGIN( TTpVmpMemberCfgInd )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfgInd, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfgInd, u16, m_wFlag )
    TYPESTRUCT_MEMBER( TTpVmpMemberCfgInd, BOOL32, m_bRet )
TYPESTRUCT_END(  TTpVmpMemberCfgInd )

//TTPConfTemplate
TYPESTRUCT_BEGIN( TTPConfTemplate )
    TYPESTRUCT_MEMBER( TTPConfTemplate, s8, m_achConfName )
    TYPESTRUCT_MEMBER( TTPConfTemplate, s8, m_achConfE164 )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wConfBitRate )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wBpConfBitRate )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wHpDualBitRate )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wBpDualBitRate )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u32, m_dwPersistenceTime )
    TYPESTRUCT_MEMBER( TTPConfTemplate, time_t, m_tStartTime )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wAudFmtNum )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TUmsAudFormat, m_atAudFmt )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TUmsRSParam, m_tRsParam )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wDefaultChairMan )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wMainNum )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TUmsVidFormat, m_atTpMainVideoRes )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wMinorNum )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TUmsVidFormat, m_atTpMinorVideoRes )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wUpBandWid )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wDownBandWid )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TTPEncrypt, m_tEncrypt )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TSaveVmpCfg, m_tVmpPlanCfg )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wID )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u32, m_dwTimeID )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TEpAddrList, m_atEpList )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TAuxMixList, m_atAuxMixList )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TConfTurnList, m_tTurnList )
TYPESTRUCT_END(  TTPConfTemplate )

//TOprConfTmpResult
TYPESTRUCT_BEGIN( TOprConfTmpResult )
    TYPESTRUCT_MEMBER( TOprConfTmpResult, u16, m_wID )
    TYPESTRUCT_MEMBER( TOprConfTmpResult, EmTpConfTemplateRet, m_emReason )
TYPESTRUCT_END(  TOprConfTmpResult )

//TDelRefreshConfTemplate
TYPESTRUCT_BEGIN( TDelRefreshConfTemplate )
    TYPESTRUCT_MEMBER( TDelRefreshConfTemplate, u16, m_wRefreshNum )
    TYPESTRUCT_MEMBER( TDelRefreshConfTemplate, u16, m_awTmpList )
TYPESTRUCT_END(  TDelRefreshConfTemplate )

//TConfEpID
TYPESTRUCT_BEGIN( TConfEpID )
    TYPESTRUCT_MEMBER( TConfEpID, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfEpID, u16, m_wEpID )
TYPESTRUCT_END(  TConfEpID )

//TConfEpIDInfo
TYPESTRUCT_BEGIN( TConfEpIDInfo )
    TYPESTRUCT_MEMBER( TConfEpIDInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfEpIDInfo, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TConfEpIDInfo, TTPAlias, m_tAlias )
TYPESTRUCT_END(  TConfEpIDInfo )

//TConfCallEpAddr
TYPESTRUCT_BEGIN( TConfCallEpAddr )
    TYPESTRUCT_MEMBER( TConfCallEpAddr, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfCallEpAddr, TTpCallAddr, m_tCallAddr )
TYPESTRUCT_END(  TConfCallEpAddr )

//TCnsInfo
TYPESTRUCT_BEGIN( TCnsInfo )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wParentEpID )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wChildEpID )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wBrotherEpID )
    TYPESTRUCT_MEMBER( TCnsInfo, EmTPEndpointType, m_emEpType )
    TYPESTRUCT_MEMBER( TCnsInfo, TTPAlias, m_tCalledAddr )
    TYPESTRUCT_MEMBER( TCnsInfo, BOOL32, m_bOnline )
    TYPESTRUCT_MEMBER( TCnsInfo, EmCnsCallReason, m_emCallReason )
    TYPESTRUCT_MEMBER( TCnsInfo, s8, m_achRoomName )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wLevel )
    TYPESTRUCT_MEMBER( TCnsInfo, BOOL32, m_bMute )
    TYPESTRUCT_MEMBER( TCnsInfo, BOOL32, m_bQuiet )
    TYPESTRUCT_MEMBER( TCnsInfo, BOOL32, m_bIsSpeaker )
    TYPESTRUCT_MEMBER( TCnsInfo, BOOL32, m_bIsChair )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wSpeakerNum )
    TYPESTRUCT_MATRIX( TCnsInfo, s8, m_achSpeakerName )
    TYPESTRUCT_MEMBER( TCnsInfo, s8, m_achRoomE164 )
    TYPESTRUCT_MEMBER( TCnsInfo, u32, m_dwRoomIp )
TYPESTRUCT_END(  TCnsInfo )

//TTPConfInfo
TYPESTRUCT_BEGIN( TTPConfInfo )
    TYPESTRUCT_MEMBER( TTPConfInfo, s8, m_achConfName )
    TYPESTRUCT_MEMBER( TTPConfInfo, s8, m_achConfE164 )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wConfBitRate )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wBpConfBitRate )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wHpDualBitRate )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wBpDualBitRate )
    TYPESTRUCT_MEMBER( TTPConfInfo, u32, m_dwPersistenceTime )
    TYPESTRUCT_MEMBER( TTPConfInfo, time_t, m_tStartTime )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wAudFmtNum )
    TYPESTRUCT_MEMBER( TTPConfInfo, TUmsAudFormat, m_atAudFmt )
    TYPESTRUCT_MEMBER( TTPConfInfo, TUmsRSParam, m_tRsParam )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wDefaultChairMan )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wMainNum )
    TYPESTRUCT_MEMBER( TTPConfInfo, TUmsVidFormat, m_atTpMainVideoRes )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wMinorNum )
    TYPESTRUCT_MEMBER( TTPConfInfo, TUmsVidFormat, m_atTpMinorVideoRes )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wUpBandWid )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wDownBandWid )
    TYPESTRUCT_MEMBER( TTPConfInfo, TTPEncrypt, m_tEncrypt )
    TYPESTRUCT_MEMBER( TTPConfInfo, TSaveVmpCfg, m_tVmpPlanCfg )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wSpeaker )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wDual )
TYPESTRUCT_END(  TTPConfInfo )

//TAddConfList
TYPESTRUCT_BEGIN( TAddConfList )
    TYPESTRUCT_MEMBER( TAddConfList, u16, m_wRefreshNum )
    TYPESTRUCT_MEMBER( TAddConfList, TTPConfInfo, m_atTmpList )
TYPESTRUCT_END(  TAddConfList )

//TDelConfList
TYPESTRUCT_BEGIN( TDelConfList )
    TYPESTRUCT_MEMBER( TDelConfList, u16, m_wRefreshNum )
    TYPESTRUCT_MEMBER( TDelConfList, u16, m_awConfIDList )
TYPESTRUCT_END(  TDelConfList )

//TStartConfResult
TYPESTRUCT_BEGIN( TStartConfResult )
    TYPESTRUCT_MEMBER( TStartConfResult, EmTpStartConfRet, m_emReason )
    TYPESTRUCT_MEMBER( TStartConfResult, u16, m_wConfTemplateID )
    TYPESTRUCT_MEMBER( TStartConfResult, u16, m_wConfID )
TYPESTRUCT_END(  TStartConfResult )

//TConfCnsInfo
TYPESTRUCT_BEGIN( TConfCnsInfo )
    TYPESTRUCT_MEMBER( TConfCnsInfo, EmTpOprType, m_emOpr )
    TYPESTRUCT_MEMBER( TConfCnsInfo, BOOL32, m_bLastPack )
    TYPESTRUCT_MEMBER( TConfCnsInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfCnsInfo, u16, m_wNum )
    TYPESTRUCT_MEMBER( TConfCnsInfo, TCnsInfo, m_tConfCnsList )
TYPESTRUCT_END(  TConfCnsInfo )

//TConfTurnInfo
TYPESTRUCT_BEGIN( TConfTurnInfo )
    TYPESTRUCT_MEMBER( TConfTurnInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfTurnInfo, TConfTurnList, m_atTurnList )
TYPESTRUCT_END(  TConfTurnInfo )

//TApplaySpeakRet
TYPESTRUCT_BEGIN( TApplaySpeakRet )
    TYPESTRUCT_MEMBER( TApplaySpeakRet, TConfEpID, m_tID )
    TYPESTRUCT_MEMBER( TApplaySpeakRet, EmTpApplySpeakRet, m_emReason )
TYPESTRUCT_END(  TApplaySpeakRet )

//TUmsConfStatus
TYPESTRUCT_BEGIN( TUmsConfStatus )
    TYPESTRUCT_MEMBER( TUmsConfStatus, BOOL32, m_bIsStartAudMix )
TYPESTRUCT_END(  TUmsConfStatus )

//TTPUmsReasonInd
TYPESTRUCT_BEGIN( TTPUmsReasonInd )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u32, m_dwReason )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u32, m_dwReserve1 )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u32, m_dwReserve2 )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u32, m_dwReserve3 )
TYPESTRUCT_END(  TTPUmsReasonInd )

//TTPMtVideoEncodeParameter
TYPESTRUCT_BEGIN( TTPMtVideoEncodeParameter )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, EmTpVideoFormat, emVideoFormat )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u16, byMaxKeyFrameInterval )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u8, byMaxQuant )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u8, byMinQuant )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, BOOL, bUseFixedFrame )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u8, byFrameRate )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, BOOL, bFramePerSecond )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, EmTpEncodeMode, emEncodeMode )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, EmTpVideoResolution, emVideoResolution )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, wChanMaxBitrate )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u16, m_wWidth )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u16, m_wHeight )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, EmTpMediaType, emCapType )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, EmTpPCCapFormat, emPCCapFormat )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwAvgQpI )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwAvgQpP )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u8, m_byLoopFilterMask )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwProfile )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwCabacDisable )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwSilceMbCont )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwRateControlAlg )
TYPESTRUCT_END(  TTPMtVideoEncodeParameter )

//TTpCodecComponent
TYPESTRUCT_BEGIN( TTpCodecComponent )
    TYPESTRUCT_MEMBER( TTpCodecComponent, u16, wPos )
    TYPESTRUCT_MEMBER( TTpCodecComponent, EmTpCodecComponent, emCope )
TYPESTRUCT_END(  TTpCodecComponent )

//TTPCnMediaTransPort
TYPESTRUCT_BEGIN( TTPCnMediaTransPort )
    TYPESTRUCT_MEMBER( TTPCnMediaTransPort, TTPTransAddr, m_tRtpPort )
    TYPESTRUCT_MEMBER( TTPCnMediaTransPort, TTPTransAddr, m_tRtcpPort )
    TYPESTRUCT_MEMBER( TTPCnMediaTransPort, TTPTransAddr, m_tBackRtcpPort )
TYPESTRUCT_END(  TTPCnMediaTransPort )

//TMtMPAddr
TYPESTRUCT_BEGIN( TMtMPAddr )
    TYPESTRUCT_MEMBER( TMtMPAddr, u16, wPos )
    TYPESTRUCT_MEMBER( TMtMPAddr, EmTpCodecComponent, emCope )
    TYPESTRUCT_MEMBER( TMtMPAddr, TTPCnMediaTransPort, m_tAddr )
TYPESTRUCT_END(  TMtMPAddr )

//TMtMPParam
TYPESTRUCT_BEGIN( TMtMPParam )
    TYPESTRUCT_MEMBER( TMtMPParam, u16, m_wMpType )
    TYPESTRUCT_MEMBER( TMtMPParam, TTPCnMediaTransPort, m_tAddr )
TYPESTRUCT_END(  TMtMPParam )

//TMtTPEpParam
TYPESTRUCT_BEGIN( TMtTPEpParam )
    TYPESTRUCT_MEMBER( TMtTPEpParam, u16, wLen )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tSndPrimarAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tRcvPrimarAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tSndSecondAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tRcvSecondAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tSndAudioAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tRcvAudioAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, u16, m_wPosCount )
    TYPESTRUCT_MEMBER( TMtTPEpParam, u16, m_wPos )
    TYPESTRUCT_MEMBER( TMtTPEpParam, s8, achRoomName )
    TYPESTRUCT_MEMBER( TMtTPEpParam, EmTPMtModel, m_emTPMtModel )
TYPESTRUCT_END(  TMtTPEpParam )

//TMtVDecParam
TYPESTRUCT_BEGIN( TMtVDecParam )
    TYPESTRUCT_MEMBER( TMtVDecParam, EmTpCodecComponent, emComp )
    TYPESTRUCT_MEMBER( TMtVDecParam, TTPCnMediaTransPort, tAddr )
    TYPESTRUCT_MEMBER( TMtVDecParam, EmTpLostPackageRestore, emLost )
    TYPESTRUCT_MEMBER( TMtVDecParam, EmTpVideoFormat, emFormat )
    TYPESTRUCT_MEMBER( TMtVDecParam, EmTpVideoResolution, emRes )
    TYPESTRUCT_MEMBER( TMtVDecParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TMtVDecParam, TTpEncryptKey, tEncryptKey )
    TYPESTRUCT_MEMBER( TMtVDecParam, u16, wPos )
TYPESTRUCT_END(  TMtVDecParam )

//TMtVEncParam
TYPESTRUCT_BEGIN( TMtVEncParam )
    TYPESTRUCT_MEMBER( TMtVEncParam, EmTpCodecComponent, emComp )
    TYPESTRUCT_MEMBER( TMtVEncParam, TTPCnMediaTransPort, tAddr )
    TYPESTRUCT_MEMBER( TMtVEncParam, TTPMtVideoEncodeParameter, tVideoEncodeParameter )
    TYPESTRUCT_MEMBER( TMtVEncParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TMtVEncParam, TTpEncryptKey, tEncryptKey )
    TYPESTRUCT_MEMBER( TMtVEncParam, u16, wPos )
TYPESTRUCT_END(  TMtVEncParam )

//TCnVideoParam
TYPESTRUCT_BEGIN( TCnVideoParam )
    TYPESTRUCT_MEMBER( TCnVideoParam, EmTpCodecComponent, emComp )
    TYPESTRUCT_MEMBER( TCnVideoParam, TTPCnMediaTransPort, tAddr )
    TYPESTRUCT_MEMBER( TCnVideoParam, EmTpVideoFormat, emFormat )
    TYPESTRUCT_MEMBER( TCnVideoParam, EmTpVideoResolution, emRes )
    TYPESTRUCT_MEMBER( TCnVideoParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TCnVideoParam, u32, wChanMaxBitrate )
    TYPESTRUCT_MEMBER( TCnVideoParam, u8, byFrameRate )
    TYPESTRUCT_MEMBER( TCnVideoParam, TTpEncryptKey, tEncryptKey )
    TYPESTRUCT_MEMBER( TCnVideoParam, u32, m_dwProfile )
TYPESTRUCT_END(  TCnVideoParam )

//TEpId
TYPESTRUCT_BEGIN( TEpId )
    TYPESTRUCT_MEMBER( TEpId, u8, byCnNo )
    TYPESTRUCT_MEMBER( TEpId, u8, byEpNo )
TYPESTRUCT_END(  TEpId )

//TTPRegName
TYPESTRUCT_BEGIN( TTPRegName )
    TYPESTRUCT_MEMBER( TTPRegName, EmTPAddrType, emPAAddrType )
    TYPESTRUCT_MEMBER( TTPRegName, s8, achUserName )
    TYPESTRUCT_MEMBER( TTPRegName, s8, achPassword )
    TYPESTRUCT_MEMBER( TTPRegName, s8, achDisplayName )
TYPESTRUCT_END(  TTPRegName )

//TTPRegNameRepeatInfo
TYPESTRUCT_BEGIN( TTPRegNameRepeatInfo )
    TYPESTRUCT_MEMBER( TTPRegNameRepeatInfo, u32, dwsize )
    TYPESTRUCT_MEMBER( TTPRegNameRepeatInfo, TTPRegName, atTPRegName )
TYPESTRUCT_END(  TTPRegNameRepeatInfo )

//TTPSipRegistrarCfg
TYPESTRUCT_BEGIN( TTPSipRegistrarCfg )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u32_ip, dwRegIP )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u16, wRegPort )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, s8, achRegDomain )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u16, wExpire )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, BOOL, bRegistered )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, TTPRegName, atTPRegName )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, s32, nTPRegNameSize )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, s8, achHostDomain )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u32_ip, dwHostIP )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u16, wHostPort )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, EmTPEndpointType, m_emEndType )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u32_ip, m_locolIP )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, s8, m_softversion )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, s8, m_compileTime )
TYPESTRUCT_END(  TTPSipRegistrarCfg )

//TTPGkRegistrarCfg
TYPESTRUCT_BEGIN( TTPGkRegistrarCfg )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, u32_ip, dwRegIP )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, u16, wRegPort )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, s8, achRegDomain )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, u16, wExpire )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, BOOL, bRegistered )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, TTPRegName, atTPRegName )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, s32, nTPRegNameSize )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, s8, achHostDomain )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, u32_ip, dwHostIP )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, u16, wHostPort )
TYPESTRUCT_END(  TTPGkRegistrarCfg )

//TTPGKCfg
TYPESTRUCT_BEGIN( TTPGKCfg )
    TYPESTRUCT_MEMBER( TTPGKCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TTPGKCfg, u32_ip, dwGKIP )
    TYPESTRUCT_MEMBER( TTPGKCfg, u16, wRegPort )
    TYPESTRUCT_MEMBER( TTPGKCfg, u16, wExpire )
    TYPESTRUCT_MEMBER( TTPGKCfg, BOOL, bRegistered )
    TYPESTRUCT_MEMBER( TTPGKCfg, s8, achGkIpName )
    TYPESTRUCT_MEMBER( TTPGKCfg, s8, achGKPasswd )
TYPESTRUCT_END(  TTPGKCfg )

//TTPSipRegPackInfo
TYPESTRUCT_BEGIN( TTPSipRegPackInfo )
    TYPESTRUCT_MEMBER( TTPSipRegPackInfo, u16, m_wPackSeq )
    TYPESTRUCT_MEMBER( TTPSipRegPackInfo, u16, m_wTotalPackNum )
TYPESTRUCT_END(  TTPSipRegPackInfo )

//TTPSipRegInfo
TYPESTRUCT_BEGIN( TTPSipRegInfo )
    TYPESTRUCT_MEMBER( TTPSipRegInfo, u16, m_wAliasNum )
    TYPESTRUCT_MEMBER( TTPSipRegInfo, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TTPSipRegInfo, EmTPEndpointType, m_emSelfType )
TYPESTRUCT_END(  TTPSipRegInfo )

//TTPSipPack
TYPESTRUCT_BEGIN( TTPSipPack )
    TYPESTRUCT_MEMBER( TTPSipPack, TTPSipRegPackInfo, m_tSipRegPackInfo )
    TYPESTRUCT_MEMBER( TTPSipPack, TTPSipRegInfo, m_tSipRegInfo )
TYPESTRUCT_END(  TTPSipPack )

//TTPAddrNtyUser
TYPESTRUCT_BEGIN( TTPAddrNtyUser )
    TYPESTRUCT_MEMBER( TTPAddrNtyUser, u32, m_dwIID )
    TYPESTRUCT_MEMBER( TTPAddrNtyUser, u32, m_wUserData )
    TYPESTRUCT_MEMBER( TTPAddrNtyUser, EmGetRegInfoType, m_emType )
TYPESTRUCT_END(  TTPAddrNtyUser )

//TUCSipRegResult
TYPESTRUCT_BEGIN( TUCSipRegResult )
    TYPESTRUCT_MEMBER( TUCSipRegResult, EmTpCnsRegUms, m_emTpCnsRegUms )
    TYPESTRUCT_MEMBER( TUCSipRegResult, TTPAlias, m_atTPAlias )
    TYPESTRUCT_MEMBER( TUCSipRegResult, s32, m_nAliasNum )
TYPESTRUCT_END(  TUCSipRegResult )

//TCnAddr
TYPESTRUCT_BEGIN( TCnAddr )
    TYPESTRUCT_MEMBER( TCnAddr, EmTPAddrType, emType )
    TYPESTRUCT_MEMBER( TCnAddr, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TCnAddr, u16, wPort )
    TYPESTRUCT_MEMBER( TCnAddr, s8, achAlias )
    TYPESTRUCT_MEMBER( TCnAddr, s8, achE164 )
    TYPESTRUCT_MEMBER( TCnAddr, BOOL, bCallByIPAndAlias )
TYPESTRUCT_END(  TCnAddr )

//TTPSipNstHeader
TYPESTRUCT_BEGIN( TTPSipNstHeader )
    TYPESTRUCT_MEMBER( TTPSipNstHeader, s8, m_achName )
    TYPESTRUCT_MEMBER( TTPSipNstHeader, s8, m_achValue )
TYPESTRUCT_END(  TTPSipNstHeader )

//TTPDialParam
TYPESTRUCT_BEGIN( TTPDialParam )
    TYPESTRUCT_MEMBER( TTPDialParam, EmTpConnectionType, emTpConnectionType )
    TYPESTRUCT_MEMBER( TTPDialParam, EmTpCallMode, emCallType )
    TYPESTRUCT_MEMBER( TTPDialParam, EmTpConfProtocol, emProtocol )
    TYPESTRUCT_MEMBER( TTPDialParam, u16, wCallRate )
    TYPESTRUCT_MEMBER( TTPDialParam, TCnAddr, tCallingAddr )
    TYPESTRUCT_MEMBER( TTPDialParam, TCnAddr, tCalledAddr )
    TYPESTRUCT_MEMBER( TTPDialParam, EmTPEndpointType, m_emEndpointType )
    TYPESTRUCT_MEMBER( TTPDialParam, BOOL32, m_bIsEncrypt )
    TYPESTRUCT_MEMBER( TTPDialParam, s32, m_nProductIdSize )
    TYPESTRUCT_MEMBER( TTPDialParam, u8, m_abyProductId )
    TYPESTRUCT_MEMBER( TTPDialParam, s32, m_nVerIdSize )
    TYPESTRUCT_MEMBER( TTPDialParam, u8, m_abyVersionId )
    TYPESTRUCT_MEMBER( TTPDialParam, u32_ip, dwRegIP )
    TYPESTRUCT_MEMBER( TTPDialParam, u16, wRegPort )
    TYPESTRUCT_MEMBER( TTPDialParam, s8, achRegDomain )
    TYPESTRUCT_MEMBER( TTPDialParam, s8, achDisplayName )
    TYPESTRUCT_MEMBER( TTPDialParam, s8, achUserName )
    TYPESTRUCT_MEMBER( TTPDialParam, s8, achPassword )
    TYPESTRUCT_MEMBER( TTPDialParam, s8, achHostDomain )
    TYPESTRUCT_MEMBER( TTPDialParam, BOOL, bCreateConf )
    TYPESTRUCT_MEMBER( TTPDialParam, TTPConfBaseInfo, tConfInfo )
    TYPESTRUCT_MEMBER( TTPDialParam, u8, byTerNum )
    TYPESTRUCT_MEMBER( TTPDialParam, TCnAddr, atList )
    TYPESTRUCT_MEMBER( TTPDialParam, EmTPSipLevel, m_emSipLevel )
    TYPESTRUCT_MEMBER( TTPDialParam, s32, m_nScreenNum )
    TYPESTRUCT_MEMBER( TTPDialParam, TTpEncryptKey, tEncryptKey )
    TYPESTRUCT_MEMBER( TTPDialParam, TTpQtEncryptCfg, tQtEncryptCfg )
    TYPESTRUCT_MEMBER( TTPDialParam, u8, m_byNonStdHdrNum )
    TYPESTRUCT_MEMBER( TTPDialParam, TTPSipNstHeader, m_atNonStdHdr )
TYPESTRUCT_END(  TTPDialParam )

//TTPEthnetInfo
TYPESTRUCT_BEGIN( TTPEthnetInfo )
    TYPESTRUCT_MEMBER( TTPEthnetInfo, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TTPEthnetInfo, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TTPEthnetInfo, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TTPEthnetInfo, u32_ip, dwGateWay )
TYPESTRUCT_END(  TTPEthnetInfo )

//TTPWEthnetInfo
TYPESTRUCT_BEGIN( TTPWEthnetInfo )
    TYPESTRUCT_MEMBER( TTPWEthnetInfo, TTPEthnetInfo, atTPEthnetInfo )
TYPESTRUCT_END(  TTPWEthnetInfo )

//TTPCnsInfo
TYPESTRUCT_BEGIN( TTPCnsInfo )
    TYPESTRUCT_MEMBER( TTPCnsInfo, s8, m_achRoomName )
    TYPESTRUCT_MEMBER( TTPCnsInfo, s8, m_achE164 )
    TYPESTRUCT_MEMBER( TTPCnsInfo, u16, m_wScreenNum )
    TYPESTRUCT_MEMBER( TTPCnsInfo, EmTPSipLevel, m_emLevel )
    TYPESTRUCT_MEMBER( TTPCnsInfo, u8, m_byDualPos )
    TYPESTRUCT_MEMBER( TTPCnsInfo, u32_ip, m_adwIP )
TYPESTRUCT_END(  TTPCnsInfo )

//TTPTime
TYPESTRUCT_BEGIN( TTPTime )
    TYPESTRUCT_MEMBER( TTPTime, u16, m_wYear )
    TYPESTRUCT_MEMBER( TTPTime, u8, m_byMonth )
    TYPESTRUCT_MEMBER( TTPTime, u8, m_byMDay )
    TYPESTRUCT_MEMBER( TTPTime, u8, m_byHour )
    TYPESTRUCT_MEMBER( TTPTime, u8, m_byMinute )
    TYPESTRUCT_MEMBER( TTPTime, u8, m_bySecond )
TYPESTRUCT_END(  TTPTime )

//TTPCnsConfStatus
TYPESTRUCT_BEGIN( TTPCnsConfStatus )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, EmCALLSTATE, emState )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, u16, wConfID )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, s8, achConfName )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, u32, m_dwStartTime )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, EmCallType, m_emCallType )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, BOOL32, m_bMixMotive )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, EmTpConfProtocol, m_emConfProtocal )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, TCnAddr, tCalledAddr )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, EmTPEncryptType, m_emTPEncryptType )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, TTpQtEncryptCfg, m_tQtEncryptCfg )
TYPESTRUCT_END(  TTPCnsConfStatus )

//TTPDualInfo
TYPESTRUCT_BEGIN( TTPDualInfo )
    TYPESTRUCT_MEMBER( TTPDualInfo, EmTPPayloadType, m_emPayload )
    TYPESTRUCT_MEMBER( TTPDualInfo, EmTpVideoResolution, m_emReslution )
    TYPESTRUCT_MEMBER( TTPDualInfo, u16, m_wFrameRate )
    TYPESTRUCT_MEMBER( TTPDualInfo, u16, m_wBitRate )
    TYPESTRUCT_MEMBER( TTPDualInfo, s32, m_nScreenNo )
    TYPESTRUCT_MEMBER( TTPDualInfo, s32, m_nEpId )
    TYPESTRUCT_MEMBER( TTPDualInfo, s8, m_achCascade )
    TYPESTRUCT_MEMBER( TTPDualInfo, TTPTransAddr, m_tRtp )
    TYPESTRUCT_MEMBER( TTPDualInfo, TTPTransAddr, m_tRtcp )
    TYPESTRUCT_MEMBER( TTPDualInfo, TTPTransAddr, m_tBackRtp )
TYPESTRUCT_END(  TTPDualInfo )

//TTPDualRequest
TYPESTRUCT_BEGIN( TTPDualRequest )
    TYPESTRUCT_MEMBER( TTPDualRequest, s8, m_achCascade )
    TYPESTRUCT_MEMBER( TTPDualRequest, s32, m_nEpId )
TYPESTRUCT_END(  TTPDualRequest )

//TTPDualInfoAck
TYPESTRUCT_BEGIN( TTPDualInfoAck )
    TYPESTRUCT_MEMBER( TTPDualInfoAck, BOOL, m_bAccept )
    TYPESTRUCT_MEMBER( TTPDualInfoAck, TTPDualInfo, m_tDualInfo )
TYPESTRUCT_END(  TTPDualInfoAck )

//TTPAudioInfo
TYPESTRUCT_BEGIN( TTPAudioInfo )
    TYPESTRUCT_MEMBER( TTPAudioInfo, u8, m_byInputVolume )
    TYPESTRUCT_MEMBER( TTPAudioInfo, u8, m_byOutputVolume )
TYPESTRUCT_END(  TTPAudioInfo )

//TTPHduRegInfo
TYPESTRUCT_BEGIN( TTPHduRegInfo )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, BOOL32, m_bIsOnline )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, u32_ip, m_dwIpAddr )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, u16, m_wStartPort )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, s8, m_achAlias )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, u16, m_dwChannelHandle )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, u16, m_wScreenNum )
TYPESTRUCT_END(  TTPHduRegInfo )

//TTPHduPlayReq
TYPESTRUCT_BEGIN( TTPHduPlayReq )
    TYPESTRUCT_MEMBER( TTPHduPlayReq, EmViewEpType, m_emType )
    TYPESTRUCT_MEMBER( TTPHduPlayReq, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPHduPlayReq, u16, m_wDstID )
    TYPESTRUCT_MEMBER( TTPHduPlayReq, u16, m_wScreenNum )
    TYPESTRUCT_MEMBER( TTPHduPlayReq, u16, m_wIndex )
    TYPESTRUCT_MEMBER( TTPHduPlayReq, u8, m_bySubIndex )
    TYPESTRUCT_MEMBER( TTPHduPlayReq, BOOL32, m_bVmp )
TYPESTRUCT_END(  TTPHduPlayReq )

//TPHduBaseInfo
TYPESTRUCT_BEGIN( TPHduBaseInfo )
    TYPESTRUCT_MEMBER( TPHduBaseInfo, u16, m_wIndex )
    TYPESTRUCT_MEMBER( TPHduBaseInfo, u8, m_bySubIndex )
TYPESTRUCT_END(  TPHduBaseInfo )

//THduSetVolInfo
TYPESTRUCT_BEGIN( THduSetVolInfo )
    TYPESTRUCT_MEMBER( THduSetVolInfo, TPHduBaseInfo, m_tInfo )
    TYPESTRUCT_MEMBER( THduSetVolInfo, u8, m_byVol )
    TYPESTRUCT_MEMBER( THduSetVolInfo, BOOL32, m_bMute )
TYPESTRUCT_END(  THduSetVolInfo )

//TTPCnLoginfo
TYPESTRUCT_BEGIN( TTPCnLoginfo )
    TYPESTRUCT_MEMBER( TTPCnLoginfo, s32, nVersion )
TYPESTRUCT_END(  TTPCnLoginfo )

//TTPCn
TYPESTRUCT_BEGIN( TTPCn )
    TYPESTRUCT_MEMBER( TTPCn, u8, byInsId )
    TYPESTRUCT_MEMBER( TTPCn, s8, achName )
TYPESTRUCT_END(  TTPCn )

//TTPCnList
TYPESTRUCT_BEGIN( TTPCnList )
    TYPESTRUCT_MEMBER( TTPCnList, u16, wNum )
    TYPESTRUCT_MEMBER( TTPCnList, TTPCn, tCn )
TYPESTRUCT_END(  TTPCnList )

//TAudMixStat
TYPESTRUCT_BEGIN( TAudMixStat )
    TYPESTRUCT_MEMBER( TAudMixStat, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TAudMixStat, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TAudMixStat, BOOL32, m_bIsStart )
    TYPESTRUCT_MEMBER( TAudMixStat, EmTpMixStatus, m_emMixStatus )
TYPESTRUCT_END(  TAudMixStat )

//TTPDisScreenStat
TYPESTRUCT_BEGIN( TTPDisScreenStat )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, BOOL32, m_bInDiscard )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, u16, m_wEpIDDst )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, u16, m_awScreenNum )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, u16, m_awSpeakerIndx )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, EmTPDisOprType, m_emOprType )
TYPESTRUCT_END(  TTPDisScreenStat )

//TTPGetRegInfo
TYPESTRUCT_BEGIN( TTPGetRegInfo )
    TYPESTRUCT_MEMBER( TTPGetRegInfo, EmGetRegInfoType, emType )
    TYPESTRUCT_MEMBER( TTPGetRegInfo, u32, dwRegIP )
    TYPESTRUCT_MEMBER( TTPGetRegInfo, u16, wRegPort )
    TYPESTRUCT_MEMBER( TTPGetRegInfo, u32, dwLocalIP )
    TYPESTRUCT_MEMBER( TTPGetRegInfo, u16, wLocalPort )
TYPESTRUCT_END(  TTPGetRegInfo )

//TTPAacCap
TYPESTRUCT_BEGIN( TTPAacCap )
    TYPESTRUCT_MEMBER( TTPAacCap, EmTpAudioFormat, m_emFormat )
    TYPESTRUCT_MEMBER( TTPAacCap, u16, m_wStaticPayload )
    TYPESTRUCT_MEMBER( TTPAacCap, u16, m_wDynamicPayload )
    TYPESTRUCT_MEMBER( TTPAacCap, u16, m_wBitrate )
    TYPESTRUCT_MEMBER( TTPAacCap, TTpEncryptKey, m_tEnc )
    TYPESTRUCT_MEMBER( TTPAacCap, EmTPAACSampleFreq, emPASampleFreq )
    TYPESTRUCT_MEMBER( TTPAacCap, EmTPAACChnlCfg, emPAChnlCfg )
TYPESTRUCT_END(  TTPAacCap )

//TTPG7221Cap
TYPESTRUCT_BEGIN( TTPG7221Cap )
    TYPESTRUCT_MEMBER( TTPG7221Cap, EmTpAudioFormat, m_emFormat )
    TYPESTRUCT_MEMBER( TTPG7221Cap, u16, m_wStaticPayload )
    TYPESTRUCT_MEMBER( TTPG7221Cap, u16, m_wDynamicPayload )
    TYPESTRUCT_MEMBER( TTPG7221Cap, u16, m_wBitrate )
    TYPESTRUCT_MEMBER( TTPG7221Cap, TTpEncryptKey, m_tEnc )
    TYPESTRUCT_MEMBER( TTPG7221Cap, u8, byBitRateType )
TYPESTRUCT_END(  TTPG7221Cap )

//TTPMediaStream
TYPESTRUCT_BEGIN( TTPMediaStream )
    TYPESTRUCT_MEMBER( TTPMediaStream, BOOL32, bActive )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTpMediaType, emTPMediaType )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPTransAddr, tLocalRtp )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPTransAddr, tRemPAoteRtp )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPTransAddr, tSendRtcp )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPTransAddr, tRecvRtcp )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTPPayloadType, aemTPMediaPT )
    TYPESTRUCT_MEMBER( TTPMediaStream, u8, byMediaCount )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPAudCap, tACap )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPAacCap, tAacCap )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPVideoCap, tVidCap )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTPPayloadType, emTPActivePT )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTPEncryptType, emTPEncryptType )
    TYPESTRUCT_MEMBER( TTPMediaStream, s32, nBitRate )
    TYPESTRUCT_MEMBER( TTPMediaStream, u32, dwLocalIp )
    TYPESTRUCT_MEMBER( TTPMediaStream, s32, nScreenNo )
    TYPESTRUCT_MEMBER( TTPMediaStream, s32, nPeerScreenNo )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTPCapSign, m_emTPCapSign )
    TYPESTRUCT_MEMBER( TTPMediaStream, BOOL32, bDual )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTPChanType, emTPChanType )
    TYPESTRUCT_MEMBER( TTPMediaStream, BOOL32, m_bAudMix )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTpEncryptKey, tEncryptKey )
TYPESTRUCT_END(  TTPMediaStream )

//TTPCnStream
TYPESTRUCT_BEGIN( TTPCnStream )
    TYPESTRUCT_MEMBER( TTPCnStream, u16, wIndex )
    TYPESTRUCT_MEMBER( TTPCnStream, s32, nScreenNo )
    TYPESTRUCT_MEMBER( TTPCnStream, EmTPChanType, emChanType )
    TYPESTRUCT_MEMBER( TTPCnStream, EmTpMediaType, emMediaType )
    TYPESTRUCT_MEMBER( TTPCnStream, EmTPChanSubType, emChanSubType )
    TYPESTRUCT_MEMBER( TTPCnStream, TTPMediaTransAddr, tTPMediaTransAddr )
    TYPESTRUCT_MEMBER( TTPCnStream, EmTPCapSign, m_emTPCapSign )
TYPESTRUCT_END(  TTPCnStream )

//TTPCnUnpackStream
TYPESTRUCT_BEGIN( TTPCnUnpackStream )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, u16, wIndex )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, s32, nScreenNo )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, EmTPChanType, emChanType )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, EmTpMediaType, emMediaType )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, EmTPChanSubType, emChanSubType )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, TTPMediaTransAddr, tTPMediaTransAddr )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, EmTPCapSign, m_emTPCapSign )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, u8, byMediaTransAddrIndex )
TYPESTRUCT_END(  TTPCnUnpackStream )

//TTPDualCap
TYPESTRUCT_BEGIN( TTPDualCap )
    TYPESTRUCT_MEMBER( TTPDualCap, u16, wDualVidCapNum )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPVideoCap, tVidCap )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAacCap, tAacCap )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAudCap, tG711a )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAudCap, tG711u )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAudCap, tG719 )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAudCap, tMP3 )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAacCap, taaclc )
    TYPESTRUCT_MEMBER( TTPDualCap, EmTPPayloadType, aemTPMediaPT )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPCnStream, tCnDualStream )
TYPESTRUCT_END(  TTPDualCap )

//TCnsCapset
TYPESTRUCT_BEGIN( TCnsCapset )
    TYPESTRUCT_MEMBER( TCnsCapset, EmTPEncryptType, emEncryptBits )
    TYPESTRUCT_MEMBER( TCnsCapset, u16, wFECBits )
    TYPESTRUCT_MEMBER( TCnsCapset, u16, wMaxBitRate )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPVideoCap, tVidCap )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAacCap, tAacCap )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAudCap, tG711a )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAudCap, tG711u )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAudCap, tG719 )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAudCap, tMP3 )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAacCap, taaclc )
    TYPESTRUCT_MEMBER( TCnsCapset, EmTPPayloadType, aemTPMediaPT )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPCnStream, tCnStream )
    TYPESTRUCT_MEMBER( TCnsCapset, u16, wChannelCount )
    TYPESTRUCT_MEMBER( TCnsCapset, u32, dwCnsIp )
TYPESTRUCT_END(  TCnsCapset )

//TTPYouAreSeeing
TYPESTRUCT_BEGIN( TTPYouAreSeeing )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, u32, m_dwVideoNum )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, u32, m_dwAudioNum )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, u16, m_CNSId )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, BOOL32, m_bExist )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, s8, m_achMeetingName )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, u16, m_wSpeakerIndex )
TYPESTRUCT_END(  TTPYouAreSeeing )

//TTPTerLabel
TYPESTRUCT_BEGIN( TTPTerLabel )
    TYPESTRUCT_MEMBER( TTPTerLabel, u8, m_byMcuNo )
    TYPESTRUCT_MEMBER( TTPTerLabel, u8, m_byTerNo )
TYPESTRUCT_END(  TTPTerLabel )

//TPModuleTerminalInfo
TYPESTRUCT_BEGIN( TPModuleTerminalInfo )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, u8, m_byMcuNo )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, u8, m_byTerNo )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, u8, m_byConfNo )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, s8, m_achTerminalId )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, BOOL32, m_bIsChair )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, BOOL32, m_bIsFloor )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, BOOL32, m_bLastPack )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, BOOL32, m_bOnline )
TYPESTRUCT_END(  TPModuleTerminalInfo )

//TTPPollDstName
TYPESTRUCT_BEGIN( TTPPollDstName )
    TYPESTRUCT_MEMBER( TTPPollDstName, s8, m_abyAlias )
    TYPESTRUCT_MEMBER( TTPPollDstName, u32, m_nScreenNum )
TYPESTRUCT_END(  TTPPollDstName )

//TMtADecParam
TYPESTRUCT_BEGIN( TMtADecParam )
    TYPESTRUCT_MEMBER( TMtADecParam, EmTpCodecComponent, emComp )
    TYPESTRUCT_MEMBER( TMtADecParam, TTPCnMediaTransPort, tAddr )
    TYPESTRUCT_MEMBER( TMtADecParam, EmTpAudioFormat, emAudioFormat )
    TYPESTRUCT_MEMBER( TMtADecParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TMtADecParam, TTpEncryptKey, tEncryptKey )
    TYPESTRUCT_MEMBER( TMtADecParam, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TMtADecParam, TTPAacCap, tAaclc )
    TYPESTRUCT_MEMBER( TMtADecParam, u16, wPos )
TYPESTRUCT_END(  TMtADecParam )

//TMtAEncParam
TYPESTRUCT_BEGIN( TMtAEncParam )
    TYPESTRUCT_MEMBER( TMtAEncParam, EmTpCodecComponent, emComp )
    TYPESTRUCT_MEMBER( TMtAEncParam, TTPCnMediaTransPort, tAddr )
    TYPESTRUCT_MEMBER( TMtAEncParam, EmTpAudioFormat, emAudioFormat )
    TYPESTRUCT_MEMBER( TMtAEncParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TMtAEncParam, TTpEncryptKey, tEncryptKey )
    TYPESTRUCT_MEMBER( TMtAEncParam, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TMtAEncParam, TTPAacCap, tAaclc )
    TYPESTRUCT_MEMBER( TMtAEncParam, u16, wPos )
TYPESTRUCT_END(  TMtAEncParam )

//TTPChanSelecteCascadRes
TYPESTRUCT_BEGIN( TTPChanSelecteCascadRes )
    TYPESTRUCT_MEMBER( TTPChanSelecteCascadRes, u32, nRes )
    TYPESTRUCT_MEMBER( TTPChanSelecteCascadRes, s8, achName )
TYPESTRUCT_END(  TTPChanSelecteCascadRes )

//TTPChanSelecteCascadCancelRes
TYPESTRUCT_BEGIN( TTPChanSelecteCascadCancelRes )
    TYPESTRUCT_MEMBER( TTPChanSelecteCascadCancelRes, s32, nPeerID )
    TYPESTRUCT_MEMBER( TTPChanSelecteCascadCancelRes, u32, nRes )
TYPESTRUCT_END(  TTPChanSelecteCascadCancelRes )

//TTerminalLabel
TYPESTRUCT_BEGIN( TTerminalLabel )
    TYPESTRUCT_MEMBER( TTerminalLabel, u8, m_byMcuNo )
    TYPESTRUCT_MEMBER( TTerminalLabel, u8, m_byTerNo )
TYPESTRUCT_END(  TTerminalLabel )

//TDiscussListOpr
TYPESTRUCT_BEGIN( TDiscussListOpr )
    TYPESTRUCT_MEMBER( TDiscussListOpr, u16, m_wConfId )
    TYPESTRUCT_MEMBER( TDiscussListOpr, u16, m_wNum )
    TYPESTRUCT_MEMBER( TDiscussListOpr, u16, m_awEpId )
    TYPESTRUCT_MEMBER( TDiscussListOpr, EmDisListOprType, m_emOprType )
    TYPESTRUCT_MEMBER( TDiscussListOpr, EmDiscussOprRes, m_aemRet )
TYPESTRUCT_END(  TDiscussListOpr )

//TTPRegistReq
TYPESTRUCT_BEGIN( TTPRegistReq )
    TYPESTRUCT_MEMBER( TTPRegistReq, s8, m_atH323Alias )
    TYPESTRUCT_MEMBER( TTPRegistReq, s8, m_atE164 )
    TYPESTRUCT_MEMBER( TTPRegistReq, TTPTransAddr, m_tLocalAddress )
    TYPESTRUCT_MEMBER( TTPRegistReq, TTPTransAddr, m_tGKAddress )
    TYPESTRUCT_MEMBER( TTPRegistReq, TTPTransAddr, m_tRegAddress )
    TYPESTRUCT_MEMBER( TTPRegistReq, s32, m_nTimeToLive )
TYPESTRUCT_END(  TTPRegistReq )

//TCnsAVCapset
TYPESTRUCT_BEGIN( TCnsAVCapset )
    TYPESTRUCT_MEMBER( TCnsAVCapset, EmTPEncryptType, emEncryptBits )
    TYPESTRUCT_MEMBER( TCnsAVCapset, u16, wFECBits )
    TYPESTRUCT_MEMBER( TCnsAVCapset, u16, wMaxBitRate )
    TYPESTRUCT_MEMBER( TCnsAVCapset, u16, wVidCapNum )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPVideoCap, atVidCap )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAacCap, tAacCap )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAudCap, tG711a )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAudCap, tG711u )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAudCap, tG719 )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAudCap, tMP3 )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAacCap, taaclc )
    TYPESTRUCT_MEMBER( TCnsAVCapset, EmTPPayloadType, aemTPMediaPT )
    TYPESTRUCT_MEMBER( TCnsAVCapset, u32, dwCnsIp )
TYPESTRUCT_END(  TCnsAVCapset )

//TCnsAddrCapset
TYPESTRUCT_BEGIN( TCnsAddrCapset )
    TYPESTRUCT_MEMBER( TCnsAddrCapset, TTPCnStream, tCnStream )
    TYPESTRUCT_MEMBER( TCnsAddrCapset, u16, wChannelCount )
    TYPESTRUCT_MEMBER( TCnsAddrCapset, u32, dwCnsIp )
TYPESTRUCT_END(  TCnsAddrCapset )

//TVgaInfo
TYPESTRUCT_BEGIN( TVgaInfo )
    TYPESTRUCT_MEMBER( TVgaInfo, EmVgaType, m_emVgaType )
    TYPESTRUCT_MEMBER( TVgaInfo, s8, m_achAlias )
TYPESTRUCT_END(  TVgaInfo )

//TTPNatCfg
TYPESTRUCT_BEGIN( TTPNatCfg )
    TYPESTRUCT_MEMBER( TTPNatCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TTPNatCfg, u32_ip, dwNatIP )
TYPESTRUCT_END(  TTPNatCfg )

//TUmsVersion
TYPESTRUCT_BEGIN( TUmsVersion )
    TYPESTRUCT_MEMBER( TUmsVersion, s8, m_abSoftVersion )
    TYPESTRUCT_MEMBER( TUmsVersion, s8, m_abHardVersion )
TYPESTRUCT_END(  TUmsVersion )

//TToolSysInfo
TYPESTRUCT_BEGIN( TToolSysInfo )
    TYPESTRUCT_MEMBER( TToolSysInfo, u32, m_dwCpuRate )
    TYPESTRUCT_MEMBER( TToolSysInfo, u32, m_dwMemRate )
TYPESTRUCT_END(  TToolSysInfo )

//THduChanInfo
TYPESTRUCT_BEGIN( THduChanInfo )
    TYPESTRUCT_MEMBER( THduChanInfo, BOOL32, m_bVmp )
    TYPESTRUCT_MEMBER( THduChanInfo, EmHduOutPort, m_emOutPortType )
    TYPESTRUCT_MEMBER( THduChanInfo, EmHduOutMode, m_emOutModeType )
    TYPESTRUCT_MEMBER( THduChanInfo, EmHduZoomRate, m_emZoomRate )
    TYPESTRUCT_MEMBER( THduChanInfo, EmHduShowMode, m_emShowMode )
TYPESTRUCT_END(  THduChanInfo )

//THduInfo
TYPESTRUCT_BEGIN( THduInfo )
    TYPESTRUCT_MEMBER( THduInfo, u8, m_byLayer )
    TYPESTRUCT_MEMBER( THduInfo, u8, m_bySlot )
    TYPESTRUCT_MEMBER( THduInfo, EMBrdType, m_emBrdType )
    TYPESTRUCT_MEMBER( THduInfo, THduChanInfo, m_atChanInfo )
    TYPESTRUCT_MEMBER( THduInfo, TTPName, m_tName )
TYPESTRUCT_END(  THduInfo )

//THduCfg
TYPESTRUCT_BEGIN( THduCfg )
    TYPESTRUCT_MEMBER( THduCfg, u8, m_byLayer )
    TYPESTRUCT_MEMBER( THduCfg, u8, m_bySlot )
    TYPESTRUCT_MEMBER( THduCfg, u32_ip, m_dwIP )
    TYPESTRUCT_MEMBER( THduCfg, u8, m_byChanNum )
    TYPESTRUCT_MEMBER( THduCfg, THduChanInfo, m_atChanInfo )
    TYPESTRUCT_MEMBER( THduCfg, TTPName, m_tName )
    TYPESTRUCT_MEMBER( THduCfg, BOOL32, m_bBrdReg )
    TYPESTRUCT_MEMBER( THduCfg, BOOL32, m_bServiceReg )
TYPESTRUCT_END(  THduCfg )

//THduStyleUnit
TYPESTRUCT_BEGIN( THduStyleUnit )
    TYPESTRUCT_MEMBER( THduStyleUnit, u8, m_byLayer )
    TYPESTRUCT_MEMBER( THduStyleUnit, u8, m_bySlot )
    TYPESTRUCT_MEMBER( THduStyleUnit, u8, m_byChanIndex )
    TYPESTRUCT_MEMBER( THduStyleUnit, TTPName, m_tName )
TYPESTRUCT_END(  THduStyleUnit )

//THduStyleData
TYPESTRUCT_BEGIN( THduStyleData )
    TYPESTRUCT_MEMBER( THduStyleData, u8, m_byRow )
    TYPESTRUCT_MEMBER( THduStyleData, u8, m_byCol )
    TYPESTRUCT_MEMBER( THduStyleData, THduStyleUnit, m_atUnits )
TYPESTRUCT_END(  THduStyleData )

//THduUnitPlayInfo
TYPESTRUCT_BEGIN( THduUnitPlayInfo )
    TYPESTRUCT_MEMBER( THduUnitPlayInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( THduUnitPlayInfo, u16, m_wDstID )
    TYPESTRUCT_MEMBER( THduUnitPlayInfo, u16, m_wScreenNum )
    TYPESTRUCT_MEMBER( THduUnitPlayInfo, EmViewEpType, m_emType )
    TYPESTRUCT_MEMBER( THduUnitPlayInfo, EmTPHduRunStatus, m_emStatus )
TYPESTRUCT_END(  THduUnitPlayInfo )

//THduPlanUnit
TYPESTRUCT_BEGIN( THduPlanUnit )
    TYPESTRUCT_MEMBER( THduPlanUnit, BOOL32, m_bReged )
    TYPESTRUCT_MEMBER( THduPlanUnit, u16, m_wIndex )
    TYPESTRUCT_MEMBER( THduPlanUnit, TTPName, m_tHduName )
    TYPESTRUCT_MEMBER( THduPlanUnit, BOOL32, m_bVmp )
    TYPESTRUCT_MEMBER( THduPlanUnit, u8, m_byVol )
    TYPESTRUCT_MEMBER( THduPlanUnit, BOOL32, m_bMute )
    TYPESTRUCT_MEMBER( THduPlanUnit, THduUnitPlayInfo, m_atPlayInfo )
TYPESTRUCT_END(  THduPlanUnit )

//THduPlanData
TYPESTRUCT_BEGIN( THduPlanData )
    TYPESTRUCT_MEMBER( THduPlanData, u8, m_byRow )
    TYPESTRUCT_MEMBER( THduPlanData, u8, m_byCol )
    TYPESTRUCT_MEMBER( THduPlanData, THduPlanUnit, m_atUnits )
TYPESTRUCT_END(  THduPlanData )

//THduStyleInfo
TYPESTRUCT_BEGIN( THduStyleInfo )
    TYPESTRUCT_MEMBER( THduStyleInfo, u8, m_byLayer )
    TYPESTRUCT_MEMBER( THduStyleInfo, u8, m_bySlot )
    TYPESTRUCT_MEMBER( THduStyleInfo, u8, m_byChanIndex )
    TYPESTRUCT_MEMBER( THduStyleInfo, TTPName, m_tName )
TYPESTRUCT_END(  THduStyleInfo )

//TTPNMServerCfg
TYPESTRUCT_BEGIN( TTPNMServerCfg )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, BOOL32, bIsServerOn )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, u32_ip, dwNMServerIP )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, u16, wNMGetSetPort )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, u16, WNMTrapPort )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, s8, achNMReadCommunity )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, s8, achNMWriteCommunity )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, u16, wNMServerNO )
TYPESTRUCT_END(  TTPNMServerCfg )

//TTPSysInfo
TYPESTRUCT_BEGIN( TTPSysInfo )
    TYPESTRUCT_MEMBER( TTPSysInfo, u8, m_byCpuRate )
    TYPESTRUCT_MEMBER( TTPSysInfo, u32, m_dwTotalByte )
    TYPESTRUCT_MEMBER( TTPSysInfo, u32, m_dwAllocByte )
TYPESTRUCT_END(  TTPSysInfo )

//TTPTPadList
TYPESTRUCT_BEGIN( TTPTPadList )
    TYPESTRUCT_MEMBER( TTPTPadList, u32_ip, m_adwTPadIP )
    TYPESTRUCT_MEMBER( TTPTPadList, u8, m_byTPadNum )
    TYPESTRUCT_MEMBER( TTPTPadList, u8, m_byUserId )
    TYPESTRUCT_MEMBER( TTPTPadList, u32, m_dwTPadNode )
    TYPESTRUCT_MATRIX( TTPTPadList, s8, m_aachTPadVersion )
TYPESTRUCT_END(  TTPTPadList )

//TTPSingleAudioPortCfg
TYPESTRUCT_BEGIN( TTPSingleAudioPortCfg )
    TYPESTRUCT_MEMBER( TTPSingleAudioPortCfg, u8, byMicVolume )
    TYPESTRUCT_MEMBER( TTPSingleAudioPortCfg, BOOL, bIsSimplexPoweringOpened )
    TYPESTRUCT_MEMBER( TTPSingleAudioPortCfg, u8, byAudioBNA )
TYPESTRUCT_END(  TTPSingleAudioPortCfg )

//TTpAudioPortInfo
TYPESTRUCT_BEGIN( TTpAudioPortInfo )
    TYPESTRUCT_MEMBER( TTpAudioPortInfo, u8, m_byGroupIndex )
    TYPESTRUCT_MEMBER( TTpAudioPortInfo, BOOL, m_abAudioPort )
    TYPESTRUCT_MEMBER( TTpAudioPortInfo, u8, m_abyVolume )
    TYPESTRUCT_MEMBER( TTpAudioPortInfo, TTPSingleAudioPortCfg, m_atSingleAudioPortCfg )
TYPESTRUCT_END(  TTpAudioPortInfo )

//TTPVideoPortInfo
TYPESTRUCT_BEGIN( TTPVideoPortInfo )
    TYPESTRUCT_MEMBER( TTPVideoPortInfo, EmSwitchState, emVideoState )
    TYPESTRUCT_MEMBER( TTPVideoPortInfo, EmTpVideoResolution, m_emRes )
    TYPESTRUCT_MEMBER( TTPVideoPortInfo, u8, m_byFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoPortInfo, BOOL, m_bIsHaveVideoSrcOutput )
    TYPESTRUCT_MEMBER( TTPVideoPortInfo, u8, m_byVolum )
TYPESTRUCT_END(  TTPVideoPortInfo )

//TTPVideoDiagInfo
TYPESTRUCT_BEGIN( TTPVideoDiagInfo )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, TTPVideoPortInfo, m_atPrimVideoInputPort )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, TTPVideoPortInfo, m_atPrimVideoOutputPort )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, u8, m_byInputDemoIndex )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, TTPVideoPortInfo, m_tDemoVideoInputPort )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, u8, m_byOutputDemoIndex )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, TTPVideoPortInfo, m_tDemoVideoOutputPort )
TYPESTRUCT_END(  TTPVideoDiagInfo )

//TTPAudioDiagInfo
TYPESTRUCT_BEGIN( TTPAudioDiagInfo )
    TYPESTRUCT_MEMBER( TTPAudioDiagInfo, TTpAudioPortInfo, m_atPrimAudioInputPort )
    TYPESTRUCT_MEMBER( TTPAudioDiagInfo, TTpAudioPortInfo, m_atPrimAudioOutputPort )
    TYPESTRUCT_MEMBER( TTPAudioDiagInfo, BOOL, m_abDemoAudioPort )
TYPESTRUCT_END(  TTPAudioDiagInfo )

//TTPUpDownNetSpeedInfo
TYPESTRUCT_BEGIN( TTPUpDownNetSpeedInfo )
    TYPESTRUCT_MEMBER( TTPUpDownNetSpeedInfo, u32, m_dwInputByteDvalue )
    TYPESTRUCT_MEMBER( TTPUpDownNetSpeedInfo, u32, m_dwOutputByteDvalue )
TYPESTRUCT_END(  TTPUpDownNetSpeedInfo )

//TTPUpDownSpeedInfo
TYPESTRUCT_BEGIN( TTPUpDownSpeedInfo )
    TYPESTRUCT_MEMBER( TTPUpDownSpeedInfo, u16, m_wUpSpeed )
    TYPESTRUCT_MEMBER( TTPUpDownSpeedInfo, u16, m_wDownSpeed )
TYPESTRUCT_END(  TTPUpDownSpeedInfo )

//TTPVgaMixInfo
TYPESTRUCT_BEGIN( TTPVgaMixInfo )
    TYPESTRUCT_MEMBER( TTPVgaMixInfo, EmVgaType, m_emCurrentType )
    TYPESTRUCT_MEMBER( TTPVgaMixInfo, EmDualOutputType, m_emDualOutputType )
    TYPESTRUCT_MEMBER( TTPVgaMixInfo, s8, m_achVgaOutputFstName )
    TYPESTRUCT_MEMBER( TTPVgaMixInfo, s8, m_achVgaOutputSndName )
TYPESTRUCT_END(  TTPVgaMixInfo )

//TCnCameraCfg
TYPESTRUCT_BEGIN( TCnCameraCfg )
    TYPESTRUCT_MEMBER( TCnCameraCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmCamType, emCamType )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byAddr )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmSerialType, emSerialType )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u32_ip, dwSerialServerIP )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wSerialServerPort )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wZoom )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmFocusMode, emFocusMode )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmOSDShow, emOSDShow )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmExpMode, emExpMode )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmGain, emGain )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmShutSpd, emShutSpd )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmBackLightType, emBackLightType )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byMulti )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byApt )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmWBMode, emWBMode )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wRGain )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wBGain )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmPicSceMode, emPicSceMode )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmGamma, emGamma )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byPicApt )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wContrast )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wHue )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wSaturat )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wBright )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmStmClean, emStmClean )
    TYPESTRUCT_MEMBER( TCnCameraCfg, Em3DNR, em3DNR )
    TYPESTRUCT_MEMBER( TCnCameraCfg, BOOL, bStmClen )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byLevel )
    TYPESTRUCT_MEMBER( TCnCameraCfg, BOOL, bBackLight )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmSensitivity, emFocusSensitivity )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byGainValue )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byGainLimit )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmAntiFlicker, emAntiFlicker )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmSpotLighet, emSpotLighet )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wSpotLighetX )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wSpotLighetY )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wExposureComp )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byBackLightLevel )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmWideDynamics, emWideDynamics )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byWideDynamicsLevel )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byColorTemperature )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmPicEffect, emPicEffect )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmPicFlip, emPicFlip )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmPicMode, emPicMode )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wPicSharpness )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byPicGamma )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, by2DNRValue )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, by3DNRValue )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmResolution, emOutputResolution )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmBaudRate, emBaudRate )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u32, dwIp )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u32, dwMask )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u32, dwGateWay )
TYPESTRUCT_END(  TCnCameraCfg )

//TCamNet
TYPESTRUCT_BEGIN( TCamNet )
    TYPESTRUCT_MEMBER( TCamNet, u32, dwIp )
    TYPESTRUCT_MEMBER( TCamNet, u32, dwMask )
    TYPESTRUCT_MEMBER( TCamNet, u32, dwGateWay )
TYPESTRUCT_END(  TCamNet )

//TTPSerialInfo
TYPESTRUCT_BEGIN( TTPSerialInfo )
    TYPESTRUCT_MEMBER( TTPSerialInfo, EmSerialType, emSerialType )
    TYPESTRUCT_MEMBER( TTPSerialInfo, TSerialCfg, tSerialCfg )
TYPESTRUCT_END(  TTPSerialInfo )

//TTVAct
TYPESTRUCT_BEGIN( TTVAct )
    TYPESTRUCT_MEMBER( TTVAct, u16, wEvent )
    TYPESTRUCT_MEMBER( TTVAct, u8, byemType )
    TYPESTRUCT_MEMBER( TTVAct, u8, byTVIndx )
    TYPESTRUCT_MEMBER( TTVAct, time_t, ttime )
TYPESTRUCT_END(  TTVAct )

//TCenDevSleepInfo
TYPESTRUCT_BEGIN( TCenDevSleepInfo )
    TYPESTRUCT_MEMBER( TCenDevSleepInfo, BOOL, bSleepUsed )
    TYPESTRUCT_MEMBER( TCenDevSleepInfo, u32, wSleepWaitTime )
TYPESTRUCT_END(  TCenDevSleepInfo )

//TCentreCurName
TYPESTRUCT_BEGIN( TCentreCurName )
    TYPESTRUCT_MEMBER( TCentreCurName, s8, achCurName )
TYPESTRUCT_END(  TCentreCurName )

//TDCamPresetInfo
TYPESTRUCT_BEGIN( TDCamPresetInfo )
    TYPESTRUCT_MEMBER( TDCamPresetInfo, u16, wZoom )
    TYPESTRUCT_MEMBER( TDCamPresetInfo, EmDCamAFMode, emDCamAFMode )
    TYPESTRUCT_MEMBER( TDCamPresetInfo, EmExpMode, emDCamExpMode )
    TYPESTRUCT_MEMBER( TDCamPresetInfo, EmDCamIris, emDCamIris )
    TYPESTRUCT_MEMBER( TDCamPresetInfo, EmDCamShutSpd, emDCamShutSpd )
    TYPESTRUCT_MEMBER( TDCamPresetInfo, EmDCamGain, emDCamGain )
    TYPESTRUCT_MEMBER( TDCamPresetInfo, EmDCamWBMode, emDCamWBMode )
    TYPESTRUCT_MEMBER( TDCamPresetInfo, u16, wRGain )
    TYPESTRUCT_MEMBER( TDCamPresetInfo, u16, wBGain )
TYPESTRUCT_END(  TDCamPresetInfo )

//TCentreDCamCfg
TYPESTRUCT_BEGIN( TCentreDCamCfg )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, BOOL, bDCamUsed )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, EmSerialType, emSerialType )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, EmDCamPower, emDCamPowerMode )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, EmDCamRecallNum, emDCamRecallNum )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, BOOL, bRecallPresetOne )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, TDCamPresetInfo, tDCamCurPresetInfo )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, TDCamPresetInfo, tDCamPresetInfo )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, EmDCamProType, emDcamProType )
TYPESTRUCT_END(  TCentreDCamCfg )

//TCentreSchCfg
TYPESTRUCT_BEGIN( TCentreSchCfg )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSchGatewayType, emCenSchGateType )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSerialType, emSerialType )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSchPower, emSchPower )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSchLight, emSchLight )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSchMidLight, emSchMidLight )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSchScrLight, emSchScrLight )
    TYPESTRUCT_MEMBER( TCentreSchCfg, u16, wSchTem )
TYPESTRUCT_END(  TCentreSchCfg )

//TCentreACCfg
TYPESTRUCT_BEGIN( TCentreACCfg )
    TYPESTRUCT_MEMBER( TCentreACCfg, u8, byID )
    TYPESTRUCT_MEMBER( TCentreACCfg, EmSerialType, emSerType )
    TYPESTRUCT_MEMBER( TCentreACCfg, EmCentreACPower, emACPower )
    TYPESTRUCT_MEMBER( TCentreACCfg, u8, bySetTemp )
    TYPESTRUCT_MEMBER( TCentreACCfg, u8, byCurTemp )
    TYPESTRUCT_MEMBER( TCentreACCfg, EmCentreACAirVol, emACAirVol )
    TYPESTRUCT_MEMBER( TCentreACCfg, EmCentreACMode, emACMode )
TYPESTRUCT_END(  TCentreACCfg )

//TCentreACInfo
TYPESTRUCT_BEGIN( TCentreACInfo )
    TYPESTRUCT_MEMBER( TCentreACInfo, TCentreACCfg, tCentreACCfg )
    TYPESTRUCT_MEMBER( TCentreACInfo, u8, byACNum )
    TYPESTRUCT_MEMBER( TCentreACInfo, BOOL, bACFlag )
TYPESTRUCT_END(  TCentreACInfo )

//TOprBoardResult
TYPESTRUCT_BEGIN( TOprBoardResult )
    TYPESTRUCT_MEMBER( TOprBoardResult, u8, m_byBrdLayer )
    TYPESTRUCT_MEMBER( TOprBoardResult, u8, m_byBrdSlot )
    TYPESTRUCT_MEMBER( TOprBoardResult, EmTpBoardRet, m_emReason )
TYPESTRUCT_END(  TOprBoardResult )

//TTPBrdPos
TYPESTRUCT_BEGIN( TTPBrdPos )
    TYPESTRUCT_MEMBER( TTPBrdPos, EMBrdType, m_emBrdType )
    TYPESTRUCT_MEMBER( TTPBrdPos, u8, m_byBrdLayer )
    TYPESTRUCT_MEMBER( TTPBrdPos, u8, m_byBrdSlot )
    TYPESTRUCT_MEMBER( TTPBrdPos, u32_ip, m_dwBrdIP )
TYPESTRUCT_END(  TTPBrdPos )

//TTPBrdCfg
TYPESTRUCT_BEGIN( TTPBrdCfg )
    TYPESTRUCT_MEMBER( TTPBrdCfg, u8, m_byBrdID )
    TYPESTRUCT_MEMBER( TTPBrdCfg, TTPBrdPos, m_tBrdPos )
TYPESTRUCT_END(  TTPBrdCfg )

//TTPEqpCfg
TYPESTRUCT_BEGIN( TTPEqpCfg )
    TYPESTRUCT_MEMBER( TTPEqpCfg, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TTPEqpCfg, EMEqpType, m_emEqpType )
    TYPESTRUCT_MEMBER( TTPEqpCfg, EMEqpModleType, m_emEqpMdlType )
    TYPESTRUCT_MEMBER( TTPEqpCfg, s8, m_szEqpAlias )
    TYPESTRUCT_MEMBER( TTPEqpCfg, u8, m_byBrdID )
    TYPESTRUCT_MEMBER( TTPEqpCfg, u8, m_byBrdLayer )
    TYPESTRUCT_MEMBER( TTPEqpCfg, u8, m_byBrdSlot )
    TYPESTRUCT_MEMBER( TTPEqpCfg, u8, m_byAudmixNum )
TYPESTRUCT_END(  TTPEqpCfg )

//TTPMdlCfg
TYPESTRUCT_BEGIN( TTPMdlCfg )
    TYPESTRUCT_MEMBER( TTPMdlCfg, EMEqpType, m_emEqpType )
    TYPESTRUCT_MEMBER( TTPMdlCfg, EMEqpModleType, m_emEqpMdlType )
    TYPESTRUCT_MEMBER( TTPMdlCfg, s8, m_szEqpAlias )
    TYPESTRUCT_MEMBER( TTPMdlCfg, u16, m_wEqpId )
    TYPESTRUCT_MEMBER( TTPMdlCfg, u8, m_byAudmixNum )
TYPESTRUCT_END(  TTPMdlCfg )

//TTPBrdInfo
TYPESTRUCT_BEGIN( TTPBrdInfo )
    TYPESTRUCT_MEMBER( TTPBrdInfo, TTPBrdCfg, m_tBrdCfg )
    TYPESTRUCT_MEMBER( TTPBrdInfo, TTPMdlCfg, m_tBrdMode )
    TYPESTRUCT_MEMBER( TTPBrdInfo, BOOL32, m_bReg )
    TYPESTRUCT_MEMBER( TTPBrdInfo, BOOL32, m_abEqpReg )
    TYPESTRUCT_MEMBER( TTPBrdInfo, BOOL32, m_bBrdUsed )
TYPESTRUCT_END(  TTPBrdInfo )

//TTPBrdMdlInfo
TYPESTRUCT_BEGIN( TTPBrdMdlInfo )
    TYPESTRUCT_MEMBER( TTPBrdMdlInfo, u8, m_byLayer )
    TYPESTRUCT_MEMBER( TTPBrdMdlInfo, u8, m_bySlot )
    TYPESTRUCT_MEMBER( TTPBrdMdlInfo, u8, m_byIndex )
    TYPESTRUCT_MEMBER( TTPBrdMdlInfo, TTPMdlCfg, m_atMdlCfg )
TYPESTRUCT_END(  TTPBrdMdlInfo )

//TTPBrdUsedInfo
TYPESTRUCT_BEGIN( TTPBrdUsedInfo )
    TYPESTRUCT_MEMBER( TTPBrdUsedInfo, EMEqpType, m_emType )
    TYPESTRUCT_MEMBER( TTPBrdUsedInfo, u16, m_wRegNum )
    TYPESTRUCT_MEMBER( TTPBrdUsedInfo, u16, m_wUsedNum )
TYPESTRUCT_END(  TTPBrdUsedInfo )

//TTPBrdUpGrade
TYPESTRUCT_BEGIN( TTPBrdUpGrade )
    TYPESTRUCT_MEMBER( TTPBrdUpGrade, u8, m_byLayer )
    TYPESTRUCT_MEMBER( TTPBrdUpGrade, u8, m_bySlot )
    TYPESTRUCT_MEMBER( TTPBrdUpGrade, s8, m_szFileName )
TYPESTRUCT_END(  TTPBrdUpGrade )

//TTPAudPower
TYPESTRUCT_BEGIN( TTPAudPower )
    TYPESTRUCT_MEMBER( TTPAudPower, u8, abyInput )
    TYPESTRUCT_MEMBER( TTPAudPower, u32, adwOutput )
TYPESTRUCT_END(  TTPAudPower )

//TTPHdAudioPort
TYPESTRUCT_BEGIN( TTPHdAudioPort )
    TYPESTRUCT_MEMBER( TTPHdAudioPort, u8, abHdAudPortIn )
    TYPESTRUCT_MEMBER( TTPHdAudioPort, u8, byPos )
TYPESTRUCT_END(  TTPHdAudioPort )

//TTPHdAudioOutPort
TYPESTRUCT_BEGIN( TTPHdAudioOutPort )
    TYPESTRUCT_MEMBER( TTPHdAudioOutPort, u8, abHdAudPortOut )
    TYPESTRUCT_MEMBER( TTPHdAudioOutPort, u8, byPos )
TYPESTRUCT_END(  TTPHdAudioOutPort )

//TTPHdDualAudioPort
TYPESTRUCT_BEGIN( TTPHdDualAudioPort )
    TYPESTRUCT_MEMBER( TTPHdDualAudioPort, u8, abHdAudPortIn )
    TYPESTRUCT_MEMBER( TTPHdDualAudioPort, u8, byPos )
TYPESTRUCT_END(  TTPHdDualAudioPort )

//TTPMPAudioInfo
TYPESTRUCT_BEGIN( TTPMPAudioInfo )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, BOOL, m_bIsAECEnable )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, BOOL, m_bIsAGCEnable )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, BOOL, m_bIsANSEnable )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, EmTpAudioFormat, m_emAudioFormatPriorStrategy )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, u8, m_byInputVolume )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, u8, m_byOutputVolume )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, EmTPLoudspeakerVal, m_emLoudspeakerVal )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, u8, m_abyOutputGain )
TYPESTRUCT_END(  TTPMPAudioInfo )

//TTPVideoDisplayFrm
TYPESTRUCT_BEGIN( TTPVideoDisplayFrm )
    TYPESTRUCT_MEMBER( TTPVideoDisplayFrm, u32, m_dw1080PFrm )
    TYPESTRUCT_MEMBER( TTPVideoDisplayFrm, u32, m_dw1080IFrm )
    TYPESTRUCT_MEMBER( TTPVideoDisplayFrm, u32, m_dwVGAFrm )
    TYPESTRUCT_MEMBER( TTPVideoDisplayFrm, u32, m_dw720PFrm )
    TYPESTRUCT_MEMBER( TTPVideoDisplayFrm, u32, m_dwSDFrm )
TYPESTRUCT_END(  TTPVideoDisplayFrm )

//TTPVideoParam
TYPESTRUCT_BEGIN( TTPVideoParam )
    TYPESTRUCT_MEMBER( TTPVideoParam, BOOL, bUseFixedFrame )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, EmTPFrameUnitType, emFrameUnit )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byQualMaxValue )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byQualMinValue )
    TYPESTRUCT_MEMBER( TTPVideoParam, u16, wIKeyRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, EmTpEncodeMode, emEncodeMode )
    TYPESTRUCT_MEMBER( TTPVideoParam, EmTpLostPackageRestore, emRestoreType )
    TYPESTRUCT_MEMBER( TTPVideoParam, u16, wH264IKeyRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byH264QualMaxValue )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byH264QualMinValue )
    TYPESTRUCT_MEMBER( TTPVideoParam, u16, wWidth )
    TYPESTRUCT_MEMBER( TTPVideoParam, u16, wHeight )
    TYPESTRUCT_MEMBER( TTPVideoParam, EmTpMediaType, emCapType )
    TYPESTRUCT_MEMBER( TTPVideoParam, EmTpPCCapFormat, emPCCapFormat )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, by720pFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byVgaFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byD1FrameRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, u32, dwProfile )
    TYPESTRUCT_MEMBER( TTPVideoParam, u32, dwAvgQpI )
    TYPESTRUCT_MEMBER( TTPVideoParam, u32, dwAvgQpP )
    TYPESTRUCT_MEMBER( TTPVideoParam, u16, wChanMaxBitrate )
TYPESTRUCT_END(  TTPVideoParam )

//TTPImageAdjustParam
TYPESTRUCT_BEGIN( TTPImageAdjustParam )
    TYPESTRUCT_MEMBER( TTPImageAdjustParam, u8, wBrightness )
    TYPESTRUCT_MEMBER( TTPImageAdjustParam, u8, wContrast )
    TYPESTRUCT_MEMBER( TTPImageAdjustParam, u8, wSaturation )
    TYPESTRUCT_MEMBER( TTPImageAdjustParam, u8, byNoiseReduction )
    TYPESTRUCT_MEMBER( TTPImageAdjustParam, u8, byChroma )
TYPESTRUCT_END(  TTPImageAdjustParam )

//TTPVideoInfo
TYPESTRUCT_BEGIN( TTPVideoInfo )
    TYPESTRUCT_MEMBER( TTPVideoInfo, TTPImageAdjustParam, m_atImageAdjustParam )
    TYPESTRUCT_MEMBER( TTPVideoInfo, EmTpVideoFormat, m_emVideoFormatPriorStrategy )
    TYPESTRUCT_MEMBER( TTPVideoInfo, EmTpVideoResolution, m_emVideoResolvePriorStrategy )
    TYPESTRUCT_MEMBER( TTPVideoInfo, EmTPVideoStandard, m_emOutVideoStandard )
    TYPESTRUCT_MEMBER( TTPVideoInfo, EmTPVideoStandard, m_emInVideoStandard )
TYPESTRUCT_END(  TTPVideoInfo )

//TTPSymboPoint
TYPESTRUCT_BEGIN( TTPSymboPoint )
    TYPESTRUCT_MEMBER( TTPSymboPoint, u16, X )
    TYPESTRUCT_MEMBER( TTPSymboPoint, u16, Y )
TYPESTRUCT_END(  TTPSymboPoint )

//TTPVgaOutCfg
TYPESTRUCT_BEGIN( TTPVgaOutCfg )
    TYPESTRUCT_MEMBER( TTPVgaOutCfg, BOOL, bVgaOut )
    TYPESTRUCT_MEMBER( TTPVgaOutCfg, u16, wRefreshRate )
TYPESTRUCT_END(  TTPVgaOutCfg )

//TTPFecInfo
TYPESTRUCT_BEGIN( TTPFecInfo )
    TYPESTRUCT_MEMBER( TTPFecInfo, BOOL, m_bEnableFec )
    TYPESTRUCT_MEMBER( TTPFecInfo, u8, m_byAlgorithm )
    TYPESTRUCT_MEMBER( TTPFecInfo, u16, m_wPackLen )
    TYPESTRUCT_MEMBER( TTPFecInfo, BOOL, m_bIntraFrame )
    TYPESTRUCT_MEMBER( TTPFecInfo, u32, m_dwDataPackNum )
    TYPESTRUCT_MEMBER( TTPFecInfo, u32, m_dwCrcPackNum )
TYPESTRUCT_END(  TTPFecInfo )

//TTPLostPackResend
TYPESTRUCT_BEGIN( TTPLostPackResend )
    TYPESTRUCT_MEMBER( TTPLostPackResend, BOOL, bUse )
    TYPESTRUCT_MEMBER( TTPLostPackResend, EmTPNetType, emNetType )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u8, byResendLevel )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u16, wFirstTimeSpan )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u16, wSecondTimeSpan )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u16, wThirdTimeSpan )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u16, wRejectTimeSpan )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u16, wSendBufTimeSpan )
    TYPESTRUCT_MEMBER( TTPLostPackResend, BOOL, bUseSmoothSend )
    TYPESTRUCT_MEMBER( TTPLostPackResend, BOOL, bUseAdaptSend )
TYPESTRUCT_END(  TTPLostPackResend )

//TTPBitRateAdjust
TYPESTRUCT_BEGIN( TTPBitRateAdjust )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, u16, wInterval )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, u16, wLostTimes )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, u16, wDescRatio )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, u16, wLowDescRatio )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, u16, wDelayInterval )
TYPESTRUCT_END(  TTPBitRateAdjust )

//TTPVideoStandard
TYPESTRUCT_BEGIN( TTPVideoStandard )
    TYPESTRUCT_MEMBER( TTPVideoStandard, EmTPVideoType, emVideoType )
    TYPESTRUCT_MEMBER( TTPVideoStandard, BOOL, bIsInPort )
    TYPESTRUCT_MEMBER( TTPVideoStandard, EmTPVideoStandard, emStandard )
TYPESTRUCT_END(  TTPVideoStandard )

//TTPVideoPort
TYPESTRUCT_BEGIN( TTPVideoPort )
    TYPESTRUCT_MEMBER( TTPVideoPort, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPVideoPort, EmTPMtVideoPort, emTPMtVideoPort )
    TYPESTRUCT_MEMBER( TTPVideoPort, EmTPMtVideoOutPort, emTPMtVideoOutPort )
    TYPESTRUCT_MEMBER( TTPVideoPort, EmTPDVIMode, emTPDVIInMode )
    TYPESTRUCT_MEMBER( TTPVideoPort, EmTPDVIMode, emTPDVIOutMode )
    TYPESTRUCT_MEMBER( TTPVideoPort, EmTPDVIMode, emTPDVI5OutMode )
TYPESTRUCT_END(  TTPVideoPort )

//TTPAutoTestMsg
TYPESTRUCT_BEGIN( TTPAutoTestMsg )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, EmTPAutoTestType, m_emAutoTestType )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, BOOL, m_bAutoTestStart )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, EmTPVideoType, m_emVideoType )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, TTPVideoPort, tTPVideoPort )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, TTPHdAudioPort, tTPHdAudioPort )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, TTPHdDualAudioPort, tTPHdDualAudioPort )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, TTPHdAudioOutPort, tTPHdAudioOutPort )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, u8, byMPCodecNum )
TYPESTRUCT_END(  TTPAutoTestMsg )

//TTPEqualizer
TYPESTRUCT_BEGIN( TTPEqualizer )
    TYPESTRUCT_MEMBER( TTPEqualizer, s32, anEqualizerGain )
    TYPESTRUCT_MEMBER( TTPEqualizer, BOOL, bEqualizer )
    TYPESTRUCT_MEMBER( TTPEqualizer, u8, byIndex )
TYPESTRUCT_END(  TTPEqualizer )

//TTPPIPMod
TYPESTRUCT_BEGIN( TTPPIPMod )
    TYPESTRUCT_MEMBER( TTPPIPMod, EmTPPIPMode, emTPPIPMode )
    TYPESTRUCT_MEMBER( TTPPIPMod, u8, byIndex )
TYPESTRUCT_END(  TTPPIPMod )

//TTPLostFrameRate
TYPESTRUCT_BEGIN( TTPLostFrameRate )
    TYPESTRUCT_MEMBER( TTPLostFrameRate, u8, byLostFrameRate )
    TYPESTRUCT_MEMBER( TTPLostFrameRate, TTpCodecComponent, tTpCodc )
    TYPESTRUCT_MEMBER( TTPLostFrameRate, BOOL, bvalid )
TYPESTRUCT_END(  TTPLostFrameRate )

//TTPVideoRecv
TYPESTRUCT_BEGIN( TTPVideoRecv )
    TYPESTRUCT_MEMBER( TTPVideoRecv, u8, abyVEncRecv )
    TYPESTRUCT_MEMBER( TTPVideoRecv, u8, abyVDecRecv )
TYPESTRUCT_END(  TTPVideoRecv )

//TTPVideoEncDecRes
TYPESTRUCT_BEGIN( TTPVideoEncDecRes )
    TYPESTRUCT_MEMBER( TTPVideoEncDecRes, EmTpVideoResolution, enRes )
    TYPESTRUCT_MEMBER( TTPVideoEncDecRes, TTpCodecComponent, tTpCodc )
    TYPESTRUCT_MEMBER( TTPVideoEncDecRes, BOOL, bvalid )
TYPESTRUCT_END(  TTPVideoEncDecRes )

//TTPVideoEncDecResPack
TYPESTRUCT_BEGIN( TTPVideoEncDecResPack )
    TYPESTRUCT_MEMBER( TTPVideoEncDecResPack, TTPVideoEncDecRes, atVideoRes )
    TYPESTRUCT_MEMBER( TTPVideoEncDecResPack, u8, byNum )
TYPESTRUCT_END(  TTPVideoEncDecResPack )

//TTPVideoFrameRate
TYPESTRUCT_BEGIN( TTPVideoFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoFrameRate, u16, wFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoFrameRate, TTpCodecComponent, tTpCodc )
    TYPESTRUCT_MEMBER( TTPVideoFrameRate, BOOL, bvalid )
TYPESTRUCT_END(  TTPVideoFrameRate )

//TTPVideoFrameRatePack
TYPESTRUCT_BEGIN( TTPVideoFrameRatePack )
    TYPESTRUCT_MEMBER( TTPVideoFrameRatePack, TTPVideoFrameRate, atVideoFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoFrameRatePack, u8, byNum )
TYPESTRUCT_END(  TTPVideoFrameRatePack )

//TTPCodecPackStat
TYPESTRUCT_BEGIN( TTPCodecPackStat )
    TYPESTRUCT_MEMBER( TTPCodecPackStat, TTPVideoFrameRatePack, tTPVideoFrameRatePack )
    TYPESTRUCT_MEMBER( TTPCodecPackStat, TTPVideoEncDecResPack, tTPVideoEncDecResPack )
    TYPESTRUCT_MEMBER( TTPCodecPackStat, TTPVideoRecv, tTPVideoRecv )
    TYPESTRUCT_MEMBER( TTPCodecPackStat, TTPAudPower, tTPAudPower )
TYPESTRUCT_END(  TTPCodecPackStat )

//TTPCnDsData
TYPESTRUCT_BEGIN( TTPCnDsData )
    TYPESTRUCT_MEMBER( TTPCnDsData, TTPTransAddr, m_tRcvFromAddr )
    TYPESTRUCT_MEMBER( TTPCnDsData, TTPTransAddr, m_tSndToAddr )
    TYPESTRUCT_MEMBER( TTPCnDsData, TTPTransAddr, m_tMapedAddr )
    TYPESTRUCT_MEMBER( TTPCnDsData, u32, m_dwType )
TYPESTRUCT_END(  TTPCnDsData )

//TTPCnNetBufPara
TYPESTRUCT_BEGIN( TTPCnNetBufPara )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, TTPTransAddr, m_wSndAddr )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, TTPTransAddr, m_tRcvRtpAddr )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, TTPTransAddr, m_tRcvRtcpAddr )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, TTPTransAddr, m_tRmtRtcpAddr )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, TTPTransAddr, m_tRmtRtpAddr )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, u32, m_Handle )
TYPESTRUCT_END(  TTPCnNetBufPara )

//TTPCnRSParam
TYPESTRUCT_BEGIN( TTPCnRSParam )
    TYPESTRUCT_MEMBER( TTPCnRSParam, u16, m_wFirstTimeSpan )
    TYPESTRUCT_MEMBER( TTPCnRSParam, u16, m_wSecondTimeSpan )
    TYPESTRUCT_MEMBER( TTPCnRSParam, u16, m_wThirdTimeSpan )
    TYPESTRUCT_MEMBER( TTPCnRSParam, u16, m_wRejectTimeSpan )
TYPESTRUCT_END(  TTPCnRSParam )

//TTPAllConfCnsInfo
TYPESTRUCT_BEGIN( TTPAllConfCnsInfo )
    TYPESTRUCT_MEMBER( TTPAllConfCnsInfo, TCnsInfo, m_tCnsInfo )
    TYPESTRUCT_MEMBER( TTPAllConfCnsInfo, u16, m_wNum )
TYPESTRUCT_END(  TTPAllConfCnsInfo )

//TCnDsType
TYPESTRUCT_BEGIN( TCnDsType )
    TYPESTRUCT_MEMBER( TCnDsType, u32, dwHandle )
    TYPESTRUCT_MEMBER( TCnDsType, u16, wDsType )
    TYPESTRUCT_MEMBER( TCnDsType, u16, wSubDsType )
TYPESTRUCT_END(  TCnDsType )

//TTPCnMixAddr
TYPESTRUCT_BEGIN( TTPCnMixAddr )
    TYPESTRUCT_MEMBER( TTPCnMixAddr, TTPMediaTransAddr, m_tRcv )
    TYPESTRUCT_MEMBER( TTPCnMixAddr, TTPMediaTransAddr, m_tSnd )
TYPESTRUCT_END(  TTPCnMixAddr )

//TTPCnMixChan
TYPESTRUCT_BEGIN( TTPCnMixChan )
    TYPESTRUCT_MEMBER( TTPCnMixChan, u16, m_wIndex )
    TYPESTRUCT_MEMBER( TTPCnMixChan, TTPCnMixAddr, m_tMixAddr )
TYPESTRUCT_END(  TTPCnMixChan )

//TTPCnMixParam
TYPESTRUCT_BEGIN( TTPCnMixParam )
    TYPESTRUCT_MEMBER( TTPCnMixParam, u16, m_wCurSpeaker )
    TYPESTRUCT_MEMBER( TTPCnMixParam, TTPCnMixChan, m_atAudMix )
    TYPESTRUCT_MEMBER( TTPCnMixParam, TTPTransAddr, m_tNSndRtpAddr )
    TYPESTRUCT_MEMBER( TTPCnMixParam, TTPTransAddr, m_tNSndMixBackRtcpAddr )
    TYPESTRUCT_MEMBER( TTPCnMixParam, TTPTransAddr, m_tNRcvRtpAddr )
    TYPESTRUCT_MEMBER( TTPCnMixParam, TTPTransAddr, m_tNRcvBackRtcpAddr )
TYPESTRUCT_END(  TTPCnMixParam )

//TTPNetAddress
TYPESTRUCT_BEGIN( TTPNetAddress )
    TYPESTRUCT_MEMBER( TTPNetAddress, u32, dwIp )
    TYPESTRUCT_MEMBER( TTPNetAddress, u16, wPort )
TYPESTRUCT_END(  TTPNetAddress )

//TTPMixerChannelParam
TYPESTRUCT_BEGIN( TTPMixerChannelParam )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tSrcNetAddr )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tRtcpBackAddr )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tRtcpLocalAddr )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tLocalNetAddr )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tLocalNetRtcpAddr )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tDstNetAddr )
TYPESTRUCT_END(  TTPMixerChannelParam )

//TTPCallSerInfo
TYPESTRUCT_BEGIN( TTPCallSerInfo )
    TYPESTRUCT_MEMBER( TTPCallSerInfo, u32_ip, dwCallServiceIP )
TYPESTRUCT_END(  TTPCallSerInfo )

//TTPVidSrcCutLines
TYPESTRUCT_BEGIN( TTPVidSrcCutLines )
    TYPESTRUCT_MEMBER( TTPVidSrcCutLines, u32, dwLCutLine )
    TYPESTRUCT_MEMBER( TTPVidSrcCutLines, u32, dwRCutline )
    TYPESTRUCT_MEMBER( TTPVidSrcCutLines, u8, byPos )
TYPESTRUCT_END(  TTPVidSrcCutLines )

//TVcrCfg
TYPESTRUCT_BEGIN( TVcrCfg )
    TYPESTRUCT_MEMBER( TVcrCfg, s8, m_achName )
    TYPESTRUCT_MEMBER( TVcrCfg, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TVcrCfg, u32_ip, m_dwIP )
TYPESTRUCT_END(  TVcrCfg )

//TAdjustFrameRate
TYPESTRUCT_BEGIN( TAdjustFrameRate )
    TYPESTRUCT_MEMBER( TAdjustFrameRate, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TAdjustFrameRate, u16, m_wFrameRate )
    TYPESTRUCT_MEMBER( TAdjustFrameRate, BOOL32, m_bReset )
    TYPESTRUCT_MEMBER( TAdjustFrameRate, u16, m_wScreenIndx )
TYPESTRUCT_END(  TAdjustFrameRate )

//TAdjustVidRes
TYPESTRUCT_BEGIN( TAdjustVidRes )
    TYPESTRUCT_MEMBER( TAdjustVidRes, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TAdjustVidRes, u32, m_dwVidRes )
    TYPESTRUCT_MEMBER( TAdjustVidRes, BOOL32, m_bReset )
    TYPESTRUCT_MEMBER( TAdjustVidRes, u16, m_wScreenIndx )
TYPESTRUCT_END(  TAdjustVidRes )

//TTPVGAInfo
TYPESTRUCT_BEGIN( TTPVGAInfo )
    TYPESTRUCT_MEMBER( TTPVGAInfo, u32, m_adwVGA_DF_PC )
    TYPESTRUCT_MEMBER( TTPVGAInfo, u32, m_adwVGA_DF_FS )
TYPESTRUCT_END(  TTPVGAInfo )

//TTPBmpInfo
TYPESTRUCT_BEGIN( TTPBmpInfo )
    TYPESTRUCT_MEMBER( TTPBmpInfo, u32, m_dwWidth )
    TYPESTRUCT_MEMBER( TTPBmpInfo, u32, m_dwHeight )
    TYPESTRUCT_MEMBER( TTPBmpInfo, u32, m_dwBmpLen )
TYPESTRUCT_END(  TTPBmpInfo )

//TTPAddLogoPos
TYPESTRUCT_BEGIN( TTPAddLogoPos )
    TYPESTRUCT_MEMBER( TTPAddLogoPos, u32, m_dwXPos )
    TYPESTRUCT_MEMBER( TTPAddLogoPos, u32, m_dwYPos )
TYPESTRUCT_END(  TTPAddLogoPos )

//TTPTranspDColor
TYPESTRUCT_BEGIN( TTPTranspDColor )
    TYPESTRUCT_MEMBER( TTPTranspDColor, u8, m_byRColor )
    TYPESTRUCT_MEMBER( TTPTranspDColor, u8, m_byGColor )
    TYPESTRUCT_MEMBER( TTPTranspDColor, u8, m_byBColor )
    TYPESTRUCT_MEMBER( TTPTranspDColor, u8, m_byTransparency )
TYPESTRUCT_END(  TTPTranspDColor )

//TTPAddLogoParam
TYPESTRUCT_BEGIN( TTPAddLogoParam )
    TYPESTRUCT_MEMBER( TTPAddLogoParam, u32, m_dwXPos )
    TYPESTRUCT_MEMBER( TTPAddLogoParam, u32, m_dwYPos )
    TYPESTRUCT_MEMBER( TTPAddLogoParam, u32, m_dwLogoWidth )
    TYPESTRUCT_MEMBER( TTPAddLogoParam, u32, m_dwLogoHeight )
    TYPESTRUCT_MEMBER( TTPAddLogoParam, TTPTranspDColor, m_tBackBGDColor )
TYPESTRUCT_END(  TTPAddLogoParam )

//TTPFullLogoParam
TYPESTRUCT_BEGIN( TTPFullLogoParam )
    TYPESTRUCT_MEMBER( TTPFullLogoParam, TTPBmpInfo, m_tBmpInfo )
    TYPESTRUCT_MEMBER( TTPFullLogoParam, TTPAddLogoParam, m_tLogoParam )
TYPESTRUCT_END(  TTPFullLogoParam )

//TCnProduceTestMsg
TYPESTRUCT_BEGIN( TCnProduceTestMsg )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, u16, m_wVersionNum )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, EmProducetestType, m_emProduceTestType )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, BOOL, m_bProduceTestStart )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, BOOL, m_bProduceTestReult )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, u8, m_byErrorReason )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, u32_ip, m_adwLocalIp )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, u32_ip, m_adwDstIp )
TYPESTRUCT_END(  TCnProduceTestMsg )

//TRecBaseInfo
TYPESTRUCT_BEGIN( TRecBaseInfo )
    TYPESTRUCT_MEMBER( TRecBaseInfo, s8, m_achName )
    TYPESTRUCT_MEMBER( TRecBaseInfo, u32, m_dwFreeSize )
    TYPESTRUCT_MEMBER( TRecBaseInfo, u32, m_dwTotalSize )
TYPESTRUCT_END(  TRecBaseInfo )

//TRecFileListInfo
TYPESTRUCT_BEGIN( TRecFileListInfo )
    TYPESTRUCT_MEMBER( TRecFileListInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TRecFileListInfo, u16, m_wTotalSize )
    TYPESTRUCT_MEMBER( TRecFileListInfo, u16, m_wCurSize )
    TYPESTRUCT_MATRIX( TRecFileListInfo, s8, m_achFileName )
TYPESTRUCT_END(  TRecFileListInfo )

//TRecFileInfo
TYPESTRUCT_BEGIN( TRecFileInfo )
    TYPESTRUCT_MEMBER( TRecFileInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TRecFileInfo, s8, m_szFilelName )
TYPESTRUCT_END(  TRecFileInfo )

//TRecorderConfInfo
TYPESTRUCT_BEGIN( TRecorderConfInfo )
    TYPESTRUCT_MEMBER( TRecorderConfInfo, TUmsVidFormat, m_tConfFormat )
TYPESTRUCT_END(  TRecorderConfInfo )

//TRecorderMTInfo
TYPESTRUCT_BEGIN( TRecorderMTInfo )
    TYPESTRUCT_MEMBER( TRecorderMTInfo, u16, m_wMtID )
TYPESTRUCT_END(  TRecorderMTInfo )

//TRecConfInfo
TYPESTRUCT_BEGIN( TRecConfInfo )
    TYPESTRUCT_MEMBER( TRecConfInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TRecConfInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TRecConfInfo, EmRecorderType, m_emType )
    TYPESTRUCT_MEMBER( TRecConfInfo, s8, m_achFileName )
    TYPESTRUCT_MEMBER( TRecConfInfo, BOOL32, m_bRecDual )
    TYPESTRUCT_MEMBER( TRecConfInfo, TUmsVidFormat, m_tDualFormat )
    TYPESTRUCT_MEMBER( TRecConfInfo, TRecorderConfInfo, m_tConfRecInfo )
    TYPESTRUCT_MEMBER( TRecConfInfo, TRecorderMTInfo, m_tMtRecInfo )
TYPESTRUCT_END(  TRecConfInfo )

//TConRecState
TYPESTRUCT_BEGIN( TConRecState )
    TYPESTRUCT_MEMBER( TConRecState, TRecConfInfo, m_tInfo )
    TYPESTRUCT_MEMBER( TConRecState, EmConfRecState, m_emState )
    TYPESTRUCT_MEMBER( TConRecState, u32, m_dwRecTime )
TYPESTRUCT_END(  TConRecState )

//TRecConfRes
TYPESTRUCT_BEGIN( TRecConfRes )
    TYPESTRUCT_MEMBER( TRecConfRes, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TRecConfRes, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TRecConfRes, EmRecorderType, m_emType )
    TYPESTRUCT_MEMBER( TRecConfRes, u16, m_wMtID )
TYPESTRUCT_END(  TRecConfRes )

//TRecPlayInfo
TYPESTRUCT_BEGIN( TRecPlayInfo )
    TYPESTRUCT_MEMBER( TRecPlayInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TRecPlayInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TRecPlayInfo, BOOL32, m_bPlayInDual )
    TYPESTRUCT_MEMBER( TRecPlayInfo, s8, m_szFileName )
    TYPESTRUCT_MEMBER( TRecPlayInfo, TUmsVidFormat, m_tConfFormat )
    TYPESTRUCT_MEMBER( TRecPlayInfo, TUmsVidFormat, m_tDualFormat )
TYPESTRUCT_END(  TRecPlayInfo )

//TPlayStatusMdyInfo
TYPESTRUCT_BEGIN( TPlayStatusMdyInfo )
    TYPESTRUCT_MEMBER( TPlayStatusMdyInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TPlayStatusMdyInfo, u16, m_wConfID )
TYPESTRUCT_END(  TPlayStatusMdyInfo )

//TConfPlayStatus
TYPESTRUCT_BEGIN( TConfPlayStatus )
    TYPESTRUCT_MEMBER( TConfPlayStatus, EmConfRecState, m_emState )
    TYPESTRUCT_MEMBER( TConfPlayStatus, TRecPlayInfo, m_tInfo )
    TYPESTRUCT_MEMBER( TConfPlayStatus, u32, m_dwTotalTime )
    TYPESTRUCT_MEMBER( TConfPlayStatus, u32, m_dwCurTime )
TYPESTRUCT_END(  TConfPlayStatus )

//TTPUpgradeSer
TYPESTRUCT_BEGIN( TTPUpgradeSer )
    TYPESTRUCT_MEMBER( TTPUpgradeSer, u32_ip, dwSerIP )
TYPESTRUCT_END(  TTPUpgradeSer )

//TTPSnapInfo
TYPESTRUCT_BEGIN( TTPSnapInfo )
    TYPESTRUCT_MEMBER( TTPSnapInfo, u8, byPos )
    TYPESTRUCT_MEMBER( TTPSnapInfo, s8, achSnapName )
    TYPESTRUCT_MEMBER( TTPSnapInfo, BOOL, bShow )
TYPESTRUCT_END(  TTPSnapInfo )

//TTPSingleLoopInfo
TYPESTRUCT_BEGIN( TTPSingleLoopInfo )
    TYPESTRUCT_MEMBER( TTPSingleLoopInfo, EmTpMediaType, emMediaType )
    TYPESTRUCT_MEMBER( TTPSingleLoopInfo, BOOL, bLoop )
    TYPESTRUCT_MEMBER( TTPSingleLoopInfo, u8, byPos )
TYPESTRUCT_END(  TTPSingleLoopInfo )

//TTPAllLoopInfo
TYPESTRUCT_BEGIN( TTPAllLoopInfo )
    TYPESTRUCT_MEMBER( TTPAllLoopInfo, u8, byPos )
    TYPESTRUCT_MEMBER( TTPAllLoopInfo, TTPSingleLoopInfo, tSingleLoopInfo )
TYPESTRUCT_END(  TTPAllLoopInfo )

//TTPMtTerminal
TYPESTRUCT_BEGIN( TTPMtTerminal )
    TYPESTRUCT_MEMBER( TTPMtTerminal, u32_ip, m_dwIp )
    TYPESTRUCT_MEMBER( TTPMtTerminal, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TTPMtTerminal, EmTPEndpointType, m_emType )
TYPESTRUCT_END(  TTPMtTerminal )

//TTPMtOnLineList
TYPESTRUCT_BEGIN( TTPMtOnLineList )
    TYPESTRUCT_MEMBER( TTPMtOnLineList, u16, m_wListNum )
    TYPESTRUCT_MEMBER( TTPMtOnLineList, TTPMtTerminal, m_atTerminal )
    TYPESTRUCT_MEMBER( TTPMtOnLineList, BOOL32, m_bIsEnd )
    TYPESTRUCT_MEMBER( TTPMtOnLineList, u32_ip, m_dwIP )
TYPESTRUCT_END(  TTPMtOnLineList )

//TTPMtRegInfo
TYPESTRUCT_BEGIN( TTPMtRegInfo )
    TYPESTRUCT_MEMBER( TTPMtRegInfo, u16, m_wListNum )
    TYPESTRUCT_MEMBER( TTPMtRegInfo, TTPMtTerminal, m_atTerminal )
    TYPESTRUCT_MEMBER( TTPMtRegInfo, BOOL32, m_bIsEnd )
TYPESTRUCT_END(  TTPMtRegInfo )

//TTPMcuRegInfo
TYPESTRUCT_BEGIN( TTPMcuRegInfo )
    TYPESTRUCT_MEMBER( TTPMcuRegInfo, u16, m_wListNum )
    TYPESTRUCT_MEMBER( TTPMcuRegInfo, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TTPMcuRegInfo, BOOL32, m_bIsEnd )
    TYPESTRUCT_MEMBER( TTPMcuRegInfo, u32_ip, m_dwIP )
TYPESTRUCT_END(  TTPMcuRegInfo )

//TRegPackInfoEx
TYPESTRUCT_BEGIN( TRegPackInfoEx )
    TYPESTRUCT_MEMBER( TRegPackInfoEx, TTPSipRegPackInfo, m_tPackInfo )
    TYPESTRUCT_MEMBER( TRegPackInfoEx, EmGetRegInfoType, m_emType )
    TYPESTRUCT_MEMBER( TRegPackInfoEx, EmTPEndpointType, m_emEndpointType )
TYPESTRUCT_END(  TRegPackInfoEx )

//TUmsRegInfoEx
TYPESTRUCT_BEGIN( TUmsRegInfoEx )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, u16, m_wAliasNum )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, TTPTransAddr, m_atContactAddr )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, u32, m_dwExpires )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, EmTPEndpointType, m_emEndpointType )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, u32_ip, m_locolIP )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, s8, m_softversion )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, s8, m_compileTime )
TYPESTRUCT_END(  TUmsRegInfoEx )

//TUmsRegPackEx
TYPESTRUCT_BEGIN( TUmsRegPackEx )
    TYPESTRUCT_MEMBER( TUmsRegPackEx, u16, m_wSize )
    TYPESTRUCT_MEMBER( TUmsRegPackEx, TUmsRegInfoEx, m_atRegInfo )
    TYPESTRUCT_MEMBER( TUmsRegPackEx, BOOL32, m_bIsEnd )
TYPESTRUCT_END(  TUmsRegPackEx )

//TCnsRegInfoEx
TYPESTRUCT_BEGIN( TCnsRegInfoEx )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, u16, m_wAliasNum )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, TTPTransAddr, m_atContactAddr )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, u32, m_dwExpires )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, EmTPEndpointType, m_emEndpointType )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, u32_ip, m_locolIP )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, s8, m_softversion )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, s8, m_compileTime )
TYPESTRUCT_END(  TCnsRegInfoEx )

//TCnsRegPackEx
TYPESTRUCT_BEGIN( TCnsRegPackEx )
    TYPESTRUCT_MEMBER( TCnsRegPackEx, u16, m_wSize )
    TYPESTRUCT_MEMBER( TCnsRegPackEx, TCnsRegInfoEx, m_atRegInfo )
    TYPESTRUCT_MEMBER( TCnsRegPackEx, BOOL32, m_bIsEnd )
TYPESTRUCT_END(  TCnsRegPackEx )

//TTPAudPlayMode
TYPESTRUCT_BEGIN( TTPAudPlayMode )
    TYPESTRUCT_MEMBER( TTPAudPlayMode, EmTPAudPlayMode, emAudPlayMode )
    TYPESTRUCT_MEMBER( TTPAudPlayMode, u8, abChnID )
TYPESTRUCT_END(  TTPAudPlayMode )

//TTPSmallPicRectInfo
TYPESTRUCT_BEGIN( TTPSmallPicRectInfo )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, BOOL32, bUsrCfg )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwMergeStyle )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwPosIndex )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwScaleX )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwScaleY )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwScaleW )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwScaleH )
TYPESTRUCT_END(  TTPSmallPicRectInfo )

//TTPRecMtFormat
TYPESTRUCT_BEGIN( TTPRecMtFormat )
    TYPESTRUCT_MEMBER( TTPRecMtFormat, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPRecMtFormat, u16, m_wMtID )
    TYPESTRUCT_MEMBER( TTPRecMtFormat, BOOL32, m_bValid )
    TYPESTRUCT_MEMBER( TTPRecMtFormat, TUmsVidFormat, m_tVidFormat )
TYPESTRUCT_END(  TTPRecMtFormat )

//TTPRebootTime
TYPESTRUCT_BEGIN( TTPRebootTime )
    TYPESTRUCT_MEMBER( TTPRebootTime, BOOL, bReboot )
    TYPESTRUCT_MEMBER( TTPRebootTime, u8, byHour )
TYPESTRUCT_END(  TTPRebootTime )

//TTPVidForamt
TYPESTRUCT_BEGIN( TTPVidForamt )
    TYPESTRUCT_MEMBER( TTPVidForamt, EmTpVideoQualityLevel, emTpVideoQualityLevel )
    TYPESTRUCT_MEMBER( TTPVidForamt, EmTpVideoResolution, emTpVideoResolution )
    TYPESTRUCT_MEMBER( TTPVidForamt, u16, wVidFrameRate )
TYPESTRUCT_END(  TTPVidForamt )

//TTPVidOffsetParam
TYPESTRUCT_BEGIN( TTPVidOffsetParam )
    TYPESTRUCT_MEMBER( TTPVidOffsetParam, EmTPMtVideoPort, emPort )
    TYPESTRUCT_MEMBER( TTPVidOffsetParam, s32, nHoff )
    TYPESTRUCT_MEMBER( TTPVidOffsetParam, s32, nVoff )
TYPESTRUCT_END(  TTPVidOffsetParam )

//TTPAllVidOffsetParam
TYPESTRUCT_BEGIN( TTPAllVidOffsetParam )
    TYPESTRUCT_MEMBER( TTPAllVidOffsetParam, TTPVidOffsetParam, tVidOffsetParam )
    TYPESTRUCT_MEMBER( TTPAllVidOffsetParam, BOOL, bSetSingle )
    TYPESTRUCT_MEMBER( TTPAllVidOffsetParam, EmTPMtVideoPort, emPort )
TYPESTRUCT_END(  TTPAllVidOffsetParam )

//TTPCnConfInfo
TYPESTRUCT_BEGIN( TTPCnConfInfo )
    TYPESTRUCT_MEMBER( TTPCnConfInfo, TCnVideoParam, tCnVideoParam )
    TYPESTRUCT_MEMBER( TTPCnConfInfo, EmTpAudioFormat, emTpAudioFormat )
    TYPESTRUCT_MEMBER( TTPCnConfInfo, u16, wDualCallBit )
TYPESTRUCT_END(  TTPCnConfInfo )

//TTPDisplayType
TYPESTRUCT_BEGIN( TTPDisplayType )
    TYPESTRUCT_MEMBER( TTPDisplayType, EmTVInputSelect, emTPT300Type )
    TYPESTRUCT_MEMBER( TTPDisplayType, EmTVInputSelect, emTPHduType )
TYPESTRUCT_END(  TTPDisplayType )

//TChairSingleStreenInfo
TYPESTRUCT_BEGIN( TChairSingleStreenInfo )
    TYPESTRUCT_MEMBER( TChairSingleStreenInfo, EMScreenLooked, emScreenInfo )
    TYPESTRUCT_MEMBER( TChairSingleStreenInfo, u16, wEpId )
TYPESTRUCT_END(  TChairSingleStreenInfo )

//TChanViewRes
TYPESTRUCT_BEGIN( TChanViewRes )
    TYPESTRUCT_MEMBER( TChanViewRes, EmTPViewResult, m_emRes )
    TYPESTRUCT_MEMBER( TChanViewRes, TTPAlias, m_tAlias )
TYPESTRUCT_END(  TChanViewRes )

//TChairStreenInfo
TYPESTRUCT_BEGIN( TChairStreenInfo )
    TYPESTRUCT_MEMBER( TChairStreenInfo, TConfEpID, tConfID )
    TYPESTRUCT_MEMBER( TChairStreenInfo, u16, wStreenNum )
    TYPESTRUCT_MEMBER( TChairStreenInfo, TChairSingleStreenInfo, tChairStreenInfo )
TYPESTRUCT_END(  TChairStreenInfo )

//TVmpRegistInfo
TYPESTRUCT_BEGIN( TVmpRegistInfo )
    TYPESTRUCT_MEMBER( TVmpRegistInfo, u8, m_byLayer )
    TYPESTRUCT_MEMBER( TVmpRegistInfo, u8, m_bySlot )
    TYPESTRUCT_MEMBER( TVmpRegistInfo, u16, m_wChanID )
    TYPESTRUCT_MEMBER( TVmpRegistInfo, u16, m_dwStartPort )
    TYPESTRUCT_MEMBER( TVmpRegistInfo, u16, m_wRcvChanNum )
    TYPESTRUCT_MEMBER( TVmpRegistInfo, u16, m_wSendChanNum )
TYPESTRUCT_END(  TVmpRegistInfo )

//TVmpRegAck
TYPESTRUCT_BEGIN( TVmpRegAck )
    TYPESTRUCT_MEMBER( TVmpRegAck, u32, m_dwRcvIP )
    TYPESTRUCT_MEMBER( TVmpRegAck, u16, m_wRcvPort )
TYPESTRUCT_END(  TVmpRegAck )

//TVmpTimeSpan
TYPESTRUCT_BEGIN( TVmpTimeSpan )
    TYPESTRUCT_MEMBER( TVmpTimeSpan, u16, m_wFirstTimeSpan )
    TYPESTRUCT_MEMBER( TVmpTimeSpan, u16, m_wSecondTimeSpan )
    TYPESTRUCT_MEMBER( TVmpTimeSpan, u16, m_wThirdTimeSpan )
    TYPESTRUCT_MEMBER( TVmpTimeSpan, u16, m_wRejectTimeSpan )
TYPESTRUCT_END(  TVmpTimeSpan )

//TVmpMemberInfo
TYPESTRUCT_BEGIN( TVmpMemberInfo )
    TYPESTRUCT_MEMBER( TVmpMemberInfo, BOOL32, m_bMerged )
    TYPESTRUCT_MEMBER( TVmpMemberInfo, u32, m_dwHandle )
TYPESTRUCT_END(  TVmpMemberInfo )

//TDBPayload
TYPESTRUCT_BEGIN( TDBPayload )
    TYPESTRUCT_MEMBER( TDBPayload, u8, m_byRealPayload )
    TYPESTRUCT_MEMBER( TDBPayload, u8, m_byActivePayload )
TYPESTRUCT_END(  TDBPayload )

//TVmpStyleInfo
TYPESTRUCT_BEGIN( TVmpStyleInfo )
    TYPESTRUCT_MEMBER( TVmpStyleInfo, EmUmsVmpStyle, m_emVmpStyle )
    TYPESTRUCT_MEMBER( TVmpStyleInfo, EmVmpShowMode, m_emShowMode )
    TYPESTRUCT_MEMBER( TVmpStyleInfo, u8, m_byMemberNum )
    TYPESTRUCT_MEMBER( TVmpStyleInfo, TVmpMemberInfo, m_atMemberInfo )
    TYPESTRUCT_MEMBER( TVmpStyleInfo, TDBPayload, m_atDoublePayload )
TYPESTRUCT_END(  TVmpStyleInfo )

//TVmpEncParam
TYPESTRUCT_BEGIN( TVmpEncParam )
    TYPESTRUCT_MEMBER( TVmpEncParam, u8, m_byEncType )
    TYPESTRUCT_MEMBER( TVmpEncParam, u8, m_byProfileType )
    TYPESTRUCT_MEMBER( TVmpEncParam, u8, m_byFrameRate )
    TYPESTRUCT_MEMBER( TVmpEncParam, u16, m_wBitRate )
    TYPESTRUCT_MEMBER( TVmpEncParam, u16, m_wVideoWidth )
    TYPESTRUCT_MEMBER( TVmpEncParam, u16, m_wVideoHeight )
TYPESTRUCT_END(  TVmpEncParam )

//TVmpMdyInfo
TYPESTRUCT_BEGIN( TVmpMdyInfo )
    TYPESTRUCT_MEMBER( TVmpMdyInfo, u16, m_wServiceID )
    TYPESTRUCT_MEMBER( TVmpMdyInfo, TVmpStyleInfo, m_tStyleInfo )
    TYPESTRUCT_MEMBER( TVmpMdyInfo, TVmpEncParam, m_tEncParam )
TYPESTRUCT_END(  TVmpMdyInfo )

//TVmpStartParam
TYPESTRUCT_BEGIN( TVmpStartParam )
    TYPESTRUCT_MEMBER( TVmpStartParam, u16, m_wChanID )
    TYPESTRUCT_MEMBER( TVmpStartParam, TTPEncrypt, m_tEncrypt )
    TYPESTRUCT_MEMBER( TVmpStartParam, TVmpStyleInfo, m_tStyleInfo )
    TYPESTRUCT_MEMBER( TVmpStartParam, TVmpEncParam, m_tEncParam )
TYPESTRUCT_END(  TVmpStartParam )

//TVmpStartRes
TYPESTRUCT_BEGIN( TVmpStartRes )
    TYPESTRUCT_MEMBER( TVmpStartRes, EmVmpRes, m_emRes )
    TYPESTRUCT_MEMBER( TVmpStartRes, u16, m_wChanID )
TYPESTRUCT_END(  TVmpStartRes )

//TVmpMdyRes
TYPESTRUCT_BEGIN( TVmpMdyRes )
    TYPESTRUCT_MEMBER( TVmpMdyRes, EmVmpRes, m_emRes )
    TYPESTRUCT_MEMBER( TVmpMdyRes, u16, m_wChanID )
TYPESTRUCT_END(  TVmpMdyRes )

//TVmpStopRes
TYPESTRUCT_BEGIN( TVmpStopRes )
    TYPESTRUCT_MEMBER( TVmpStopRes, EmVmpRes, m_emRes )
    TYPESTRUCT_MEMBER( TVmpStopRes, u16, m_wChanID )
TYPESTRUCT_END(  TVmpStopRes )

//TVmpChanRes
TYPESTRUCT_BEGIN( TVmpChanRes )
    TYPESTRUCT_MEMBER( TVmpChanRes, EmVmpRes, m_emRes )
    TYPESTRUCT_MEMBER( TVmpChanRes, u16, m_wChanID )
TYPESTRUCT_END(  TVmpChanRes )

//TVmpAskFrame
TYPESTRUCT_BEGIN( TVmpAskFrame )
    TYPESTRUCT_MEMBER( TVmpAskFrame, u16, m_wChanID )
    TYPESTRUCT_MEMBER( TVmpAskFrame, u16, m_wMemberIndx )
TYPESTRUCT_END(  TVmpAskFrame )

//TVmpChanInfo
TYPESTRUCT_BEGIN( TVmpChanInfo )
    TYPESTRUCT_MEMBER( TVmpChanInfo, u16, m_wChanIndex )
TYPESTRUCT_END(  TVmpChanInfo )

//TTPAudPackCheckInfo
TYPESTRUCT_BEGIN( TTPAudPackCheckInfo )
    TYPESTRUCT_MEMBER( TTPAudPackCheckInfo, u32, dwCheckTime )
    TYPESTRUCT_MEMBER( TTPAudPackCheckInfo, u32, dwLostNum )
TYPESTRUCT_END(  TTPAudPackCheckInfo )

//TTPSelViewReq
TYPESTRUCT_BEGIN( TTPSelViewReq )
    TYPESTRUCT_MEMBER( TTPSelViewReq, EmUIType, m_emUIType )
    TYPESTRUCT_MEMBER( TTPSelViewReq, BOOL32, m_bSel )
    TYPESTRUCT_MEMBER( TTPSelViewReq, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPSelViewReq, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TTPSelViewReq, u16, m_wScreenIndx )
    TYPESTRUCT_MEMBER( TTPSelViewReq, EmViewEpType, m_emType )
    TYPESTRUCT_MEMBER( TTPSelViewReq, u16, m_wDstID )
    TYPESTRUCT_MEMBER( TTPSelViewReq, u16, m_wDstScrIndx )
TYPESTRUCT_END(  TTPSelViewReq )

//TTPSelViewInd
TYPESTRUCT_BEGIN( TTPSelViewInd )
    TYPESTRUCT_MEMBER( TTPSelViewInd, TTPSelViewReq, m_tSelView )
    TYPESTRUCT_MEMBER( TTPSelViewInd, EmViewRetReason, m_emRet )
TYPESTRUCT_END(  TTPSelViewInd )

//TTPSelViewNtfy
TYPESTRUCT_BEGIN( TTPSelViewNtfy )
    TYPESTRUCT_MEMBER( TTPSelViewNtfy, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPSelViewNtfy, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TTPSelViewNtfy, TTPSelViewReq, m_atSelView )
TYPESTRUCT_END(  TTPSelViewNtfy )

//TEqpInfo
TYPESTRUCT_BEGIN( TEqpInfo )
    TYPESTRUCT_MEMBER( TEqpInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TEqpInfo, EMEqpType, m_emEqpType )
    TYPESTRUCT_MEMBER( TEqpInfo, s8, m_szEqpAlias )
TYPESTRUCT_END(  TEqpInfo )

//TRersvesEqpReq
TYPESTRUCT_BEGIN( TRersvesEqpReq )
    TYPESTRUCT_MEMBER( TRersvesEqpReq, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TRersvesEqpReq, BOOL32, m_bRersves )
    TYPESTRUCT_MEMBER( TRersvesEqpReq, TEqpInfo, m_tEqp )
TYPESTRUCT_END(  TRersvesEqpReq )

//TRersvesEqpRsp
TYPESTRUCT_BEGIN( TRersvesEqpRsp )
    TYPESTRUCT_MEMBER( TRersvesEqpRsp, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TRersvesEqpRsp, EmRervesVmpRet, m_emRet )
    TYPESTRUCT_MEMBER( TRersvesEqpRsp, TRersvesEqpReq, m_tRersvesReq )
TYPESTRUCT_END(  TRersvesEqpRsp )

//TBrdVmpReq
TYPESTRUCT_BEGIN( TBrdVmpReq )
    TYPESTRUCT_MEMBER( TBrdVmpReq, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TBrdVmpReq, BOOL32, m_bBrd )
    TYPESTRUCT_MEMBER( TBrdVmpReq, TEqpInfo, m_tEqp )
TYPESTRUCT_END(  TBrdVmpReq )

//TBrdVmpRsp
TYPESTRUCT_BEGIN( TBrdVmpRsp )
    TYPESTRUCT_MEMBER( TBrdVmpRsp, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TBrdVmpRsp, TBrdVmpReq, m_tReq )
    TYPESTRUCT_MEMBER( TBrdVmpRsp, EmBrdVmpRet, m_emRet )
TYPESTRUCT_END(  TBrdVmpRsp )

//TBrdVmpChnl
TYPESTRUCT_BEGIN( TBrdVmpChnl )
    TYPESTRUCT_MEMBER( TBrdVmpChnl, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TBrdVmpChnl, u16, m_wScrIndx )
TYPESTRUCT_END(  TBrdVmpChnl )

//TBrdVmpStyle
TYPESTRUCT_BEGIN( TBrdVmpStyle )
    TYPESTRUCT_MEMBER( TBrdVmpStyle, EMVmpStyle, m_emVmpStyle )
    TYPESTRUCT_MEMBER( TBrdVmpStyle, u16, m_wSpeakerIndx )
    TYPESTRUCT_MEMBER( TBrdVmpStyle, u16, m_wDualIndx )
    TYPESTRUCT_MEMBER( TBrdVmpStyle, u16, m_wChnlNum )
    TYPESTRUCT_MEMBER( TBrdVmpStyle, TBrdVmpChnl, m_atVmpChnl )
TYPESTRUCT_END(  TBrdVmpStyle )

//TSetVmpInfoReq
TYPESTRUCT_BEGIN( TSetVmpInfoReq )
    TYPESTRUCT_MEMBER( TSetVmpInfoReq, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TSetVmpInfoReq, TEqpInfo, m_tEqp )
    TYPESTRUCT_MEMBER( TSetVmpInfoReq, TBrdVmpStyle, m_tStyle )
TYPESTRUCT_END(  TSetVmpInfoReq )

//TSetVmpInfoRsp
TYPESTRUCT_BEGIN( TSetVmpInfoRsp )
    TYPESTRUCT_MEMBER( TSetVmpInfoRsp, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TSetVmpInfoRsp, TSetVmpInfoReq, m_tReq )
    TYPESTRUCT_MEMBER( TSetVmpInfoRsp, EmBrdVmpRet, m_emRet )
TYPESTRUCT_END(  TSetVmpInfoRsp )

//TVmpCasecadeNtfy
TYPESTRUCT_BEGIN( TVmpCasecadeNtfy )
    TYPESTRUCT_MEMBER( TVmpCasecadeNtfy, BOOL32, m_bBrdVmp )
    TYPESTRUCT_MEMBER( TVmpCasecadeNtfy, BOOL32, m_bSpeakerVmp )
    TYPESTRUCT_MEMBER( TVmpCasecadeNtfy, s8, m_szBrdVmpAlias )
TYPESTRUCT_END(  TVmpCasecadeNtfy )

//TBrdVmpResNtfy
TYPESTRUCT_BEGIN( TBrdVmpResNtfy )
    TYPESTRUCT_MEMBER( TBrdVmpResNtfy, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TBrdVmpResNtfy, BOOL32, m_bVmpAuto )
    TYPESTRUCT_MEMBER( TBrdVmpResNtfy, EmBrdVmpStat, m_emStat )
    TYPESTRUCT_MEMBER( TBrdVmpResNtfy, TEqpInfo, m_tEqpInfo )
    TYPESTRUCT_MEMBER( TBrdVmpResNtfy, TBrdVmpStyle, m_tVmpStyle )
    TYPESTRUCT_MEMBER( TBrdVmpResNtfy, EmTpOprType, m_emOpr )
TYPESTRUCT_END(  TBrdVmpResNtfy )

//TBrdVmpResArray
TYPESTRUCT_BEGIN( TBrdVmpResArray )
    TYPESTRUCT_MEMBER( TBrdVmpResArray, u16, m_wNum )
    TYPESTRUCT_MEMBER( TBrdVmpResArray, TBrdVmpResNtfy, m_atVmpNtfy )
TYPESTRUCT_END(  TBrdVmpResArray )

//TCasecadePollEpReq
TYPESTRUCT_BEGIN( TCasecadePollEpReq )
    TYPESTRUCT_MEMBER( TCasecadePollEpReq, BOOL32, m_bCreate )
    TYPESTRUCT_MEMBER( TCasecadePollEpReq, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TCasecadePollEpReq, TTPTransAddr, m_atPollAddr )
    TYPESTRUCT_MEMBER( TCasecadePollEpReq, TTPTransAddr, m_atSmallAddr )
TYPESTRUCT_END(  TCasecadePollEpReq )

//TCasecadePollEpRsp
TYPESTRUCT_BEGIN( TCasecadePollEpRsp )
    TYPESTRUCT_MEMBER( TCasecadePollEpRsp, TCasecadePollEpReq, m_tReq )
    TYPESTRUCT_MEMBER( TCasecadePollEpRsp, EmTPPollResult, m_emRes )
TYPESTRUCT_END(  TCasecadePollEpRsp )

//TTpPollListNtfy
TYPESTRUCT_BEGIN( TTpPollListNtfy )
    TYPESTRUCT_MEMBER( TTpPollListNtfy, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTpPollListNtfy, s32, m_nFlag )
    TYPESTRUCT_MEMBER( TTpPollListNtfy, u16, m_wInterval )
    TYPESTRUCT_MEMBER( TTpPollListNtfy, u16, m_wTotalNum )
    TYPESTRUCT_MEMBER( TTpPollListNtfy, u16, m_wCurNum )
    TYPESTRUCT_MEMBER( TTpPollListNtfy, u16, m_awList )
TYPESTRUCT_END(  TTpPollListNtfy )

//TTpPollListInd
TYPESTRUCT_BEGIN( TTpPollListInd )
    TYPESTRUCT_MEMBER( TTpPollListInd, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTpPollListInd, s32, m_nFlag )
    TYPESTRUCT_MEMBER( TTpPollListInd, u16, m_wRet )
    TYPESTRUCT_MEMBER( TTpPollListInd, u16, m_wCurRcvNum )
TYPESTRUCT_END(  TTpPollListInd )

//TTpPollStat
TYPESTRUCT_BEGIN( TTpPollStat )
    TYPESTRUCT_MEMBER( TTpPollStat, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTpPollStat, EmPollStat, m_emStat )
TYPESTRUCT_END(  TTpPollStat )

//TTPDataConfInfo
TYPESTRUCT_BEGIN( TTPDataConfInfo )
    TYPESTRUCT_MEMBER( TTPDataConfInfo, u32_ip, dwSerIP )
TYPESTRUCT_END(  TTPDataConfInfo )

//TTPCallTypePri
TYPESTRUCT_BEGIN( TTPCallTypePri )
    TYPESTRUCT_MEMBER( TTPCallTypePri, EmTpCallLevel, emTPIPLevel )
    TYPESTRUCT_MEMBER( TTPCallTypePri, EmTpCallLevel, emTPE164Level )
    TYPESTRUCT_MEMBER( TTPCallTypePri, EmTpCallLevel, emTPAliasLevel )
TYPESTRUCT_END(  TTPCallTypePri )

//TTPDualDisplayParam
TYPESTRUCT_BEGIN( TTPDualDisplayParam )
    TYPESTRUCT_MEMBER( TTPDualDisplayParam, BOOL, m_bIsAutoDisPlay )
    TYPESTRUCT_MEMBER( TTPDualDisplayParam, BOOL, m_abIsScreensDisPlay )
TYPESTRUCT_END(  TTPDualDisplayParam )

//TTPDualDisplayStrategy
TYPESTRUCT_BEGIN( TTPDualDisplayStrategy )
    TYPESTRUCT_MEMBER( TTPDualDisplayStrategy, TTPDualDisplayParam, m_tOnIdle )
    TYPESTRUCT_MEMBER( TTPDualDisplayStrategy, TTPDualDisplayParam, m_tOnConf )
TYPESTRUCT_END(  TTPDualDisplayStrategy )

//TTpObj
TYPESTRUCT_BEGIN( TTpObj )
    TYPESTRUCT_MEMBER( TTpObj, u16, m_wVidNum )
    TYPESTRUCT_MEMBER( TTpObj, u16, m_wAudNum )
    TYPESTRUCT_MEMBER( TTpObj, u16, m_wScrIndx )
    TYPESTRUCT_MEMBER( TTpObj, EMScreenObj, m_emObj )
    TYPESTRUCT_MEMBER( TTpObj, TTPAlias, m_tAlias )
TYPESTRUCT_END(  TTpObj )

//TTpYouAreSeeing
TYPESTRUCT_BEGIN( TTpYouAreSeeing )
    TYPESTRUCT_MEMBER( TTpYouAreSeeing, BOOL32, m_bSpeaker )
    TYPESTRUCT_MEMBER( TTpYouAreSeeing, u16, m_wVidNum )
    TYPESTRUCT_MEMBER( TTpYouAreSeeing, u16, m_wAudNum )
    TYPESTRUCT_MEMBER( TTpYouAreSeeing, TTpObj, m_atObj )
TYPESTRUCT_END(  TTpYouAreSeeing )

//TTPAddBannerParam
TYPESTRUCT_BEGIN( TTPAddBannerParam )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwXPos )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwYPos )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwWidth )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwHeight )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwBMPWight )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwBMPHeight )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwBannerCharHeight )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, TTPTranspDColor, tBackBGDColor )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwBGDClarity )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwPicClarity )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwRunMode )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwRunSpeed )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwRunTimes )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, bRunForever )
    TYPESTRUCT_MEMBER( TTPAddBannerParam, u32, dwHaltTime )
TYPESTRUCT_END(  TTPAddBannerParam )

//TTPBannerBmpInfo
TYPESTRUCT_BEGIN( TTPBannerBmpInfo )
    TYPESTRUCT_MEMBER( TTPBannerBmpInfo, u32, dwWidth )
    TYPESTRUCT_MEMBER( TTPBannerBmpInfo, u32, dwHeight )
    TYPESTRUCT_MEMBER( TTPBannerBmpInfo, u32, dwBmpLen )
TYPESTRUCT_END(  TTPBannerBmpInfo )

//TTPFullBannerParam
TYPESTRUCT_BEGIN( TTPFullBannerParam )
    TYPESTRUCT_MEMBER( TTPFullBannerParam, TTPBannerBmpInfo, tBmpInfo )
    TYPESTRUCT_MEMBER( TTPFullBannerParam, TTPAddBannerParam, tBannerParam )
    TYPESTRUCT_MEMBER( TTPFullBannerParam, u32, Reserver )
TYPESTRUCT_END(  TTPFullBannerParam )

//TTPBannerParam
TYPESTRUCT_BEGIN( TTPBannerParam )
    TYPESTRUCT_MEMBER( TTPBannerParam, u8, byPos )
    TYPESTRUCT_MEMBER( TTPBannerParam, BOOL, bAddBanner )
    TYPESTRUCT_MEMBER( TTPBannerParam, EmTpBannerTransparency, emTransparency )
    TYPESTRUCT_MEMBER( TTPBannerParam, EmTpBannerType, emBannerType )
TYPESTRUCT_END(  TTPBannerParam )

//TTPLogoParam
TYPESTRUCT_BEGIN( TTPLogoParam )
    TYPESTRUCT_MEMBER( TTPLogoParam, u8, byPos )
    TYPESTRUCT_MEMBER( TTPLogoParam, BOOL, bAddLogo )
    TYPESTRUCT_MEMBER( TTPLogoParam, BOOL, bUsedInitialLogo )
    TYPESTRUCT_MEMBER( TTPLogoParam, EmTpLogoType, emTpLogoType )
TYPESTRUCT_END(  TTPLogoParam )

//TTPConfEpInfo
TYPESTRUCT_BEGIN( TTPConfEpInfo )
    TYPESTRUCT_MEMBER( TTPConfEpInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPConfEpInfo, TTpCallAddr, m_tCallAddr )
    TYPESTRUCT_MEMBER( TTPConfEpInfo, u16, m_Index )
    TYPESTRUCT_MEMBER( TTPConfEpInfo, BOOL32, m_bPermit )
TYPESTRUCT_END(  TTPConfEpInfo )

//TTpVidCutLine
TYPESTRUCT_BEGIN( TTpVidCutLine )
    TYPESTRUCT_MEMBER( TTpVidCutLine, u8, byIndex )
    TYPESTRUCT_MEMBER( TTpVidCutLine, u32, m_dwLeft )
    TYPESTRUCT_MEMBER( TTpVidCutLine, u32, m_dwRight )
    TYPESTRUCT_MEMBER( TTpVidCutLine, u32, m_dwTop )
TYPESTRUCT_END(  TTpVidCutLine )

//TTpIconInfo
TYPESTRUCT_BEGIN( TTpIconInfo )
    TYPESTRUCT_MEMBER( TTpIconInfo, u8, byIndex )
    TYPESTRUCT_MEMBER( TTpIconInfo, BOOL, bOpen )
    TYPESTRUCT_MEMBER( TTpIconInfo, u32, dwXPos )
    TYPESTRUCT_MEMBER( TTpIconInfo, u32, dwYPos )
    TYPESTRUCT_MEMBER( TTpIconInfo, u32, dwIconID )
TYPESTRUCT_END(  TTpIconInfo )

//TTpAudMix
TYPESTRUCT_BEGIN( TTpAudMix )
    TYPESTRUCT_MEMBER( TTpAudMix, BOOL, abAudMix )
TYPESTRUCT_END(  TTpAudMix )

//TVidAliasInfo
TYPESTRUCT_BEGIN( TVidAliasInfo )
    TYPESTRUCT_MEMBER( TVidAliasInfo, u8, m_byIndex )
    TYPESTRUCT_MEMBER( TVidAliasInfo, s8, m_abyAlias )
TYPESTRUCT_END(  TVidAliasInfo )

//TVidSourceInfo
TYPESTRUCT_BEGIN( TVidSourceInfo )
    TYPESTRUCT_MEMBER( TVidSourceInfo, u8, m_byNum )
    TYPESTRUCT_MEMBER( TVidSourceInfo, TVidAliasInfo, m_atVidInfo )
TYPESTRUCT_END(  TVidSourceInfo )

//TTPKedaManuProductTP
TYPESTRUCT_BEGIN( TTPKedaManuProductTP )
    TYPESTRUCT_MEMBER( TTPKedaManuProductTP, u8, m_byAgentID )
TYPESTRUCT_END(  TTPKedaManuProductTP )

//TVidFeccInfo
TYPESTRUCT_BEGIN( TVidFeccInfo )
    TYPESTRUCT_MEMBER( TVidFeccInfo, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TVidFeccInfo, BOOL32, m_bAllowFecc )
    TYPESTRUCT_MEMBER( TVidFeccInfo, u8, m_byVidno )
    TYPESTRUCT_MEMBER( TVidFeccInfo, TVidSourceInfo, m_tVidSourceInfo )
TYPESTRUCT_END(  TVidFeccInfo )

//TConfVidFeccInfo
TYPESTRUCT_BEGIN( TConfVidFeccInfo )
    TYPESTRUCT_MEMBER( TConfVidFeccInfo, EmTpOprType, m_emOpr )
    TYPESTRUCT_MEMBER( TConfVidFeccInfo, BOOL32, m_bLastPack )
    TYPESTRUCT_MEMBER( TConfVidFeccInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfVidFeccInfo, u16, m_wNum )
    TYPESTRUCT_MEMBER( TConfVidFeccInfo, TVidFeccInfo, m_atVidFeccList )
TYPESTRUCT_END(  TConfVidFeccInfo )

//TTPMatrixServerInfo
TYPESTRUCT_BEGIN( TTPMatrixServerInfo )
    TYPESTRUCT_MEMBER( TTPMatrixServerInfo, u32_ip, m_dwSerIP )
TYPESTRUCT_END(  TTPMatrixServerInfo )

//TTpMic10Info
TYPESTRUCT_BEGIN( TTpMic10Info )
    TYPESTRUCT_MEMBER( TTpMic10Info, EmAudGroupIndex, m_emGroupIndex )
    TYPESTRUCT_MEMBER( TTpMic10Info, BOOL, m_bAudioPort )
    TYPESTRUCT_MEMBER( TTpMic10Info, u8, m_byVolume )
TYPESTRUCT_END(  TTpMic10Info )

//TTPTelnetInfo
TYPESTRUCT_BEGIN( TTPTelnetInfo )
    TYPESTRUCT_MEMBER( TTPTelnetInfo, BOOL, bOpen )
    TYPESTRUCT_MEMBER( TTPTelnetInfo, s8, achUserName )
    TYPESTRUCT_MEMBER( TTPTelnetInfo, s8, achPassword )
TYPESTRUCT_END(  TTPTelnetInfo )

//TTPFtpInfo
TYPESTRUCT_BEGIN( TTPFtpInfo )
    TYPESTRUCT_MEMBER( TTPFtpInfo, BOOL, bOpen )
    TYPESTRUCT_MEMBER( TTPFtpInfo, s8, achUserName )
    TYPESTRUCT_MEMBER( TTPFtpInfo, s8, achPassword )
TYPESTRUCT_END(  TTPFtpInfo )

//TTpMicState
TYPESTRUCT_BEGIN( TTpMicState )
    TYPESTRUCT_MEMBER( TTpMicState, BOOL, m_byMicState )
TYPESTRUCT_END(  TTpMicState )

//TTpMicSingleState
TYPESTRUCT_BEGIN( TTpMicSingleState )
    TYPESTRUCT_MEMBER( TTpMicSingleState, BOOL, m_byMicState )
TYPESTRUCT_END(  TTpMicSingleState )

//TTpNetIpRouteParam
TYPESTRUCT_BEGIN( TTpNetIpRouteParam )
    TYPESTRUCT_MEMBER( TTpNetIpRouteParam, u32, m_byEthId )
    TYPESTRUCT_MEMBER( TTpNetIpRouteParam, u32, m_dwDesIpNet )
    TYPESTRUCT_MEMBER( TTpNetIpRouteParam, u32, m_dwDesIpMask )
    TYPESTRUCT_MEMBER( TTpNetIpRouteParam, u32, m_dwGwIpAdrs )
    TYPESTRUCT_MEMBER( TTpNetIpRouteParam, u32, m_dwRoutePri )
TYPESTRUCT_END(  TTpNetIpRouteParam )

//TTpNetAllIpRouteInfo
TYPESTRUCT_BEGIN( TTpNetAllIpRouteInfo )
    TYPESTRUCT_MEMBER( TTpNetAllIpRouteInfo, u32, m_dwIpRouteNum )
    TYPESTRUCT_MEMBER( TTpNetAllIpRouteInfo, TTpNetIpRouteParam, m_tNetIpRouteParam )
TYPESTRUCT_END(  TTpNetAllIpRouteInfo )

//TTPNtpSer
TYPESTRUCT_BEGIN( TTPNtpSer )
    TYPESTRUCT_MEMBER( TTPNtpSer, u32_ip, dwSerIP )
TYPESTRUCT_END(  TTPNtpSer )

//TTpUserSafe
TYPESTRUCT_BEGIN( TTpUserSafe )
    TYPESTRUCT_MEMBER( TTpUserSafe, s8, m_achname )
    TYPESTRUCT_MEMBER( TTpUserSafe, u8, m_byNumber )
    TYPESTRUCT_MEMBER( TTpUserSafe, u32, m_dwTime )
    TYPESTRUCT_MEMBER( TTpUserSafe, BOOL, m_bIsExist )
TYPESTRUCT_END(  TTpUserSafe )

//TTpPasswordUpdateInfo
TYPESTRUCT_BEGIN( TTpPasswordUpdateInfo )
    TYPESTRUCT_MEMBER( TTpPasswordUpdateInfo, BOOL, m_bOpen )
    TYPESTRUCT_MEMBER( TTpPasswordUpdateInfo, EmUpdateFrequency, m_emUpdateFrequency )
    TYPESTRUCT_MEMBER( TTpPasswordUpdateInfo, TTPTime, m_tTime )
TYPESTRUCT_END(  TTpPasswordUpdateInfo )

//TTpAuxOutVolume
TYPESTRUCT_BEGIN( TTpAuxOutVolume )
    TYPESTRUCT_MEMBER( TTpAuxOutVolume, u8, byOut1Vol )
    TYPESTRUCT_MEMBER( TTpAuxOutVolume, u8, byOut2Vol )
TYPESTRUCT_END(  TTpAuxOutVolume )

//TTpSuperUser
TYPESTRUCT_BEGIN( TTpSuperUser )
    TYPESTRUCT_MEMBER( TTpSuperUser, u8, m_byLockNumber )
    TYPESTRUCT_MEMBER( TTpSuperUser, u32, m_dwLockTime )
TYPESTRUCT_END(  TTpSuperUser )

//TTPSingleMatrixInfo
TYPESTRUCT_BEGIN( TTPSingleMatrixInfo )
    TYPESTRUCT_MEMBER( TTPSingleMatrixInfo, BOOL, m_bHaveSrc )
    TYPESTRUCT_MEMBER( TTPSingleMatrixInfo, s8, m_achname )
TYPESTRUCT_END(  TTPSingleMatrixInfo )

//TTPMatrixInfo
TYPESTRUCT_BEGIN( TTPMatrixInfo )
    TYPESTRUCT_MEMBER( TTPMatrixInfo, TTPSingleMatrixInfo, m_tMatrixInfo )
TYPESTRUCT_END(  TTPMatrixInfo )

//TTPMatrixName
TYPESTRUCT_BEGIN( TTPMatrixName )
    TYPESTRUCT_MEMBER( TTPMatrixName, u8, m_byPose )
    TYPESTRUCT_MEMBER( TTPMatrixName, s8, m_achname )
TYPESTRUCT_END(  TTPMatrixName )

//TTPSlectView
TYPESTRUCT_BEGIN( TTPSlectView )
    TYPESTRUCT_MEMBER( TTPSlectView, u8, m_byPose )
    TYPESTRUCT_MEMBER( TTPSlectView, BOOL, m_bIsLocal )
    TYPESTRUCT_MEMBER( TTPSlectView, BOOL, m_bIsSet )
TYPESTRUCT_END(  TTPSlectView )

//TTPModulTerInfo
TYPESTRUCT_BEGIN( TTPModulTerInfo )
    TYPESTRUCT_MEMBER( TTPModulTerInfo, BOOL, m_bMute )
    TYPESTRUCT_MEMBER( TTPModulTerInfo, BOOL, m_bQuite )
    TYPESTRUCT_MEMBER( TTPModulTerInfo, u8, m_byInputVolme )
    TYPESTRUCT_MEMBER( TTPModulTerInfo, u8, m_byOutVolme )
    TYPESTRUCT_MEMBER( TTPModulTerInfo, BOOL, m_bPVHasVideo )
    TYPESTRUCT_MEMBER( TTPModulTerInfo, BOOL, m_bSVHasVideo )
TYPESTRUCT_END(  TTPModulTerInfo )

//TRmMgrMtMPAddr
TYPESTRUCT_BEGIN( TRmMgrMtMPAddr )
    TYPESTRUCT_MEMBER( TRmMgrMtMPAddr, TMtMPAddr, m_tMtMPAddr )
    TYPESTRUCT_MEMBER( TRmMgrMtMPAddr, BOOL, m_bUsed )
TYPESTRUCT_END(  TRmMgrMtMPAddr )

//TRmMgrDs
TYPESTRUCT_BEGIN( TRmMgrDs )
    TYPESTRUCT_MEMBER( TRmMgrDs, u16, m_wPos )
    TYPESTRUCT_MEMBER( TRmMgrDs, TTPTransAddr, m_tSendPort )
    TYPESTRUCT_MEMBER( TRmMgrDs, BOOL, m_bUsed )
TYPESTRUCT_END(  TRmMgrDs )

//TFtpFileInfo
TYPESTRUCT_BEGIN( TFtpFileInfo )
    TYPESTRUCT_MEMBER( TFtpFileInfo, u32, m_dwFtpServerIP )
    TYPESTRUCT_MEMBER( TFtpFileInfo, u16, m_wFtpServerPort )
    TYPESTRUCT_MEMBER( TFtpFileInfo, s8, m_achFtpUsrName )
    TYPESTRUCT_MEMBER( TFtpFileInfo, s8, m_achFtpPwd )
    TYPESTRUCT_MEMBER( TFtpFileInfo, u8, m_byFtpFileNum )
    TYPESTRUCT_MATRIX( TFtpFileInfo, s8, m_aachFtpFile )
TYPESTRUCT_END(  TFtpFileInfo )

//TTPCloudPlatServerCfg
TYPESTRUCT_BEGIN( TTPCloudPlatServerCfg )
    TYPESTRUCT_MEMBER( TTPCloudPlatServerCfg, BOOL, m_bEnable )
    TYPESTRUCT_MEMBER( TTPCloudPlatServerCfg, s8, m_achServerIP )
    TYPESTRUCT_MEMBER( TTPCloudPlatServerCfg, u16, m_wServerPort )
    TYPESTRUCT_MEMBER( TTPCloudPlatServerCfg, s8, m_achUsrName )
    TYPESTRUCT_MEMBER( TTPCloudPlatServerCfg, s8, m_achPwd )
TYPESTRUCT_END(  TTPCloudPlatServerCfg )

//TTPConfPassword
TYPESTRUCT_BEGIN( TTPConfPassword )
    TYPESTRUCT_MEMBER( TTPConfPassword, TTPTerLabel, m_tTer )
    TYPESTRUCT_MEMBER( TTPConfPassword, s32, m_nPassLen )
    TYPESTRUCT_MEMBER( TTPConfPassword, u8, m_abyPassword )
TYPESTRUCT_END(  TTPConfPassword )

//通讯数据结构编码表
TXDATAINFO* g_tTpStructData[]={
	(TXDATAINFO*)TTPFTPFileInfomembertable,
	(TXDATAINFO*)TTPDevmembertable,
	(TXDATAINFO*)TTPDevVerInfomembertable,
	(TXDATAINFO*)TTPLocalVerInfomembertable,
	(TXDATAINFO*)TTPLocalDevVerInfomembertable,
	(TXDATAINFO*)TTPTPadVerInfomembertable,
	(TXDATAINFO*)TH323Cfgmembertable,
	(TXDATAINFO*)TGuideCfgmembertable,
	(TXDATAINFO*)TSymboPointmembertable,
	(TXDATAINFO*)TOsdCfgmembertable,
	(TXDATAINFO*)TMtKdvTimemembertable,
	(TXDATAINFO*)TUserCfgmembertable,
	(TXDATAINFO*)TVgaOutCfgmembertable,
	(TXDATAINFO*)TMtEquipmentCapsetmembertable,
	(TXDATAINFO*)TInnerMcCfgmembertable,
	(TXDATAINFO*)TEthnetInfomembertable,
	(TXDATAINFO*)TE1Unitmembertable,
	(TXDATAINFO*)TE1Configmembertable,
	(TXDATAINFO*)TSerialCfgmembertable,
	(TXDATAINFO*)TRouteCfgmembertable,
	(TXDATAINFO*)TPPPOECfgmembertable,
	(TXDATAINFO*)TPPPoEStatesmembertable,
	(TXDATAINFO*)TPPPoEAuthFailedmembertable,
	(TXDATAINFO*)TPPPoEConnNotifymembertable,
	(TXDATAINFO*)TPPPoENoServermembertable,
	(TXDATAINFO*)TSNMPCfgmembertable,
	(TXDATAINFO*)TIPQoSmembertable,
	(TXDATAINFO*)TStreamMediamembertable,
	(TXDATAINFO*)TVideoParammembertable,
	(TXDATAINFO*)TAVPriorStrategymembertable,
	(TXDATAINFO*)TLostPackResendmembertable,
	(TXDATAINFO*)TCameraTypeInfomembertable,
	(TXDATAINFO*)TCameraCfgmembertable,
	(TXDATAINFO*)TVideoStandardmembertable,
	(TXDATAINFO*)TVideoSourcemembertable,
	(TXDATAINFO*)TSnapInfomembertable,
	(TXDATAINFO*)TBannerInfomembertable,
	(TXDATAINFO*)TMtIdmembertable,
	(TXDATAINFO*)TConfBaseInfomembertable,
	(TXDATAINFO*)TConfListInfomembertable,
	(TXDATAINFO*)TMtInfomembertable,
	(TXDATAINFO*)TMtVideoCodecStatusmembertable,
	(TXDATAINFO*)TTerStatusmembertable,
	(TXDATAINFO*)TMtMixParammembertable,
	(TXDATAINFO*)TMtVmpItemmembertable,
	(TXDATAINFO*)TMtVMPParammembertable,
	(TXDATAINFO*)TMtPollInfomembertable,
	(TXDATAINFO*)TMtPollSchemeNameSetmembertable,
	(TXDATAINFO*)TMtViewPollInfomembertable,
	(TXDATAINFO*)TMtSimpConfInfomembertable,
	(TXDATAINFO*)TMtConfInfomembertable,
	(TXDATAINFO*)TIPTransAddrmembertable,
	(TXDATAINFO*)TMtAddrmembertable,
	(TXDATAINFO*)TConfIdmembertable,
	(TXDATAINFO*)TLinkStatemembertable,
	(TXDATAINFO*)TEmbedFwNatProxymembertable,
	(TXDATAINFO*)TNATMapAddrmembertable,
	(TXDATAINFO*)TSipRegistrarCfgmembertable,
	(TXDATAINFO*)TGKCfgmembertable,
	(TXDATAINFO*)TInnerGKCfgmembertable,
	(TXDATAINFO*)TInnerProxyCfgmembertable,
	(TXDATAINFO*)TWiFiNetCfgmembertable,
	(TXDATAINFO*)TMonitorServicemembertable,
	(TXDATAINFO*)TRectmembertable,
	(TXDATAINFO*)TDualRationmembertable,
	(TXDATAINFO*)TImageAdjustParammembertable,
	(TXDATAINFO*)TVideoEncodeParametermembertable,
	(TXDATAINFO*)TEncryptKeymembertable,
	(TXDATAINFO*)TVideoChanParammembertable,
	(TXDATAINFO*)TAudioChanParammembertable,
	(TXDATAINFO*)TVODUserInfomembertable,
	(TXDATAINFO*)TVODFilemembertable,
	(TXDATAINFO*)TE1Groupmembertable,
	(TXDATAINFO*)TVideoSourceInfomembertable,
	(TXDATAINFO*)TExternalMatrixInfomembertable,
	(TXDATAINFO*)TAVInnerMatrixSchememembertable,
	(TXDATAINFO*)TBitRateAdjustmembertable,
	(TXDATAINFO*)TCodecPackStatmembertable,
	(TXDATAINFO*)TVideoStatisticsmembertable,
	(TXDATAINFO*)TAudioStatisticsmembertable,
	(TXDATAINFO*)TCapTypemembertable,
	(TXDATAINFO*)TCallInfoStatisticsmembertable,
	(TXDATAINFO*)TDualStreamBoxInfomembertable,
	(TXDATAINFO*)TFileTransfermembertable,
	(TXDATAINFO*)TDVBNetSessionmembertable,
	(TXDATAINFO*)TDVBNetSndParammembertable,
	(TXDATAINFO*)TDVBLocalNetParammembertable,
	(TXDATAINFO*)TDVBVideoEncParammembertable,
	(TXDATAINFO*)TSitecallInformationmembertable,
	(TXDATAINFO*)TTransparentSerialmembertable,
	(TXDATAINFO*)TPeerCapabilityInfomembertable,
	(TXDATAINFO*)TRapidKeymembertable,
	(TXDATAINFO*)TVerFileInfomembertable,
	(TXDATAINFO*)TVerInfomembertable,
	(TXDATAINFO*)TFecInfomembertable,
	(TXDATAINFO*)TVInnerMatrixSchememembertable,
	(TXDATAINFO*)TAddrEntrymembertable,
	(TXDATAINFO*)TPxyIPCfgmembertable,
	(TXDATAINFO*)TWifiLinkInfomembertable,
	(TXDATAINFO*)TWifiScanResultmembertable,
	(TXDATAINFO*)TWifiLinkCfgItemmembertable,
	(TXDATAINFO*)TWiFiBSSIDInfomembertable,
	(TXDATAINFO*)TWiFiBSSIDCfgmembertable,
	(TXDATAINFO*)TGkRegInfomembertable,
	(TXDATAINFO*)TSipRegResultmembertable,
	(TXDATAINFO*)THdAudioPortmembertable,
	(TXDATAINFO*)TMiscCfgmembertable,
	(TXDATAINFO*)TVideoDisplayFrmmembertable,
	(TXDATAINFO*)TDownLoadParamembertable,
	(TXDATAINFO*)TSecurePwdmembertable,
	(TXDATAINFO*)TMtBackBGDColormembertable,
	(TXDATAINFO*)TSipCfgmembertable,
	(TXDATAINFO*)TMtAddBannerParammembertable,
	(TXDATAINFO*)TMtBmpInfomembertable,
	(TXDATAINFO*)TMtFullBannerParammembertable,
	(TXDATAINFO*)TMTBmpInfomembertable,
	(TXDATAINFO*)TMTAddLogoParammembertable,
	(TXDATAINFO*)TMTFullLogoParammembertable,
	(TXDATAINFO*)TMtcBoxCallCfgmembertable,
	(TXDATAINFO*)TMTRSParammembertable,
	(TXDATAINFO*)TMtRecStartParammembertable,
	(TXDATAINFO*)TMtRecRegParammembertable,
	(TXDATAINFO*)TMtRecParammembertable,
	(TXDATAINFO*)TMtCnsParammembertable,
	(TXDATAINFO*)TLoginRetmembertable,
	(TXDATAINFO*)TTPTransAddrmembertable,
	(TXDATAINFO*)TTPNamemembertable,
	(TXDATAINFO*)TTPAliasmembertable,
	(TXDATAINFO*)TTpCallAddrmembertable,
	(TXDATAINFO*)TTpCallEpmembertable,
	(TXDATAINFO*)TTpEncryptKeymembertable,
	(TXDATAINFO*)TTpQtEncryptCfgmembertable,
	(TXDATAINFO*)TTpQtEncryptKeymembertable,
	(TXDATAINFO*)TTPMediaTransAddrmembertable,
	(TXDATAINFO*)TTPVideoCapmembertable,
	(TXDATAINFO*)TTPAudCapmembertable,
	(TXDATAINFO*)TUmsVidFormatmembertable,
	(TXDATAINFO*)TUmsRSParammembertable,
	(TXDATAINFO*)TEpAddrmembertable,
	(TXDATAINFO*)TAuxMixListmembertable,
	(TXDATAINFO*)TConfAuxMixVacOprmembertable,
	(TXDATAINFO*)TConfAuxMixInfomembertable,
	(TXDATAINFO*)TTPPollInfomembertable,
	(TXDATAINFO*)TTPConfBaseInfomembertable,
	(TXDATAINFO*)TUmsAudFormatmembertable,
	(TXDATAINFO*)TTPEncryptmembertable,
	(TXDATAINFO*)TTPVmpCfgChnlmembertable,
	(TXDATAINFO*)TTpVmpMemberCfgmembertable,
	(TXDATAINFO*)TSaveVmpCfgmembertable,
	(TXDATAINFO*)TUmsConfBasemembertable,
	(TXDATAINFO*)TChairConfInfomembertable,
	(TXDATAINFO*)TEpAddrListmembertable,
	(TXDATAINFO*)TConfTurnListmembertable,
	(TXDATAINFO*)TTpVmpMemberCfgIndmembertable,
	(TXDATAINFO*)TTPConfTemplatemembertable,
	(TXDATAINFO*)TOprConfTmpResultmembertable,
	(TXDATAINFO*)TDelRefreshConfTemplatemembertable,
	(TXDATAINFO*)TConfEpIDmembertable,
	(TXDATAINFO*)TConfEpIDInfomembertable,
	(TXDATAINFO*)TConfCallEpAddrmembertable,
	(TXDATAINFO*)TCnsInfomembertable,
	(TXDATAINFO*)TTPConfInfomembertable,
	(TXDATAINFO*)TAddConfListmembertable,
	(TXDATAINFO*)TDelConfListmembertable,
	(TXDATAINFO*)TStartConfResultmembertable,
	(TXDATAINFO*)TConfCnsInfomembertable,
	(TXDATAINFO*)TConfTurnInfomembertable,
	(TXDATAINFO*)TApplaySpeakRetmembertable,
	(TXDATAINFO*)TUmsConfStatusmembertable,
	(TXDATAINFO*)TTPUmsReasonIndmembertable,
	(TXDATAINFO*)TTPMtVideoEncodeParametermembertable,
	(TXDATAINFO*)TTpCodecComponentmembertable,
	(TXDATAINFO*)TTPCnMediaTransPortmembertable,
	(TXDATAINFO*)TMtMPAddrmembertable,
	(TXDATAINFO*)TMtMPParammembertable,
	(TXDATAINFO*)TMtTPEpParammembertable,
	(TXDATAINFO*)TMtVDecParammembertable,
	(TXDATAINFO*)TMtVEncParammembertable,
	(TXDATAINFO*)TCnVideoParammembertable,
	(TXDATAINFO*)TEpIdmembertable,
	(TXDATAINFO*)TTPRegNamemembertable,
	(TXDATAINFO*)TTPRegNameRepeatInfomembertable,
	(TXDATAINFO*)TTPSipRegistrarCfgmembertable,
	(TXDATAINFO*)TTPGkRegistrarCfgmembertable,
	(TXDATAINFO*)TTPGKCfgmembertable,
	(TXDATAINFO*)TTPSipRegPackInfomembertable,
	(TXDATAINFO*)TTPSipRegInfomembertable,
	(TXDATAINFO*)TTPSipPackmembertable,
	(TXDATAINFO*)TTPAddrNtyUsermembertable,
	(TXDATAINFO*)TUCSipRegResultmembertable,
	(TXDATAINFO*)TCnAddrmembertable,
	(TXDATAINFO*)TTPSipNstHeadermembertable,
	(TXDATAINFO*)TTPDialParammembertable,
	(TXDATAINFO*)TTPEthnetInfomembertable,
	(TXDATAINFO*)TTPWEthnetInfomembertable,
	(TXDATAINFO*)TTPCnsInfomembertable,
	(TXDATAINFO*)TTPTimemembertable,
	(TXDATAINFO*)TTPCnsConfStatusmembertable,
	(TXDATAINFO*)TTPDualInfomembertable,
	(TXDATAINFO*)TTPDualRequestmembertable,
	(TXDATAINFO*)TTPDualInfoAckmembertable,
	(TXDATAINFO*)TTPAudioInfomembertable,
	(TXDATAINFO*)TTPHduRegInfomembertable,
	(TXDATAINFO*)TTPHduPlayReqmembertable,
	(TXDATAINFO*)TPHduBaseInfomembertable,
	(TXDATAINFO*)THduSetVolInfomembertable,
	(TXDATAINFO*)TTPCnLoginfomembertable,
	(TXDATAINFO*)TTPCnmembertable,
	(TXDATAINFO*)TTPCnListmembertable,
	(TXDATAINFO*)TAudMixStatmembertable,
	(TXDATAINFO*)TTPDisScreenStatmembertable,
	(TXDATAINFO*)TTPGetRegInfomembertable,
	(TXDATAINFO*)TTPAacCapmembertable,
	(TXDATAINFO*)TTPG7221Capmembertable,
	(TXDATAINFO*)TTPMediaStreammembertable,
	(TXDATAINFO*)TTPCnStreammembertable,
	(TXDATAINFO*)TTPCnUnpackStreammembertable,
	(TXDATAINFO*)TTPDualCapmembertable,
	(TXDATAINFO*)TCnsCapsetmembertable,
	(TXDATAINFO*)TTPYouAreSeeingmembertable,
	(TXDATAINFO*)TTPTerLabelmembertable,
	(TXDATAINFO*)TPModuleTerminalInfomembertable,
	(TXDATAINFO*)TTPPollDstNamemembertable,
	(TXDATAINFO*)TMtADecParammembertable,
	(TXDATAINFO*)TMtAEncParammembertable,
	(TXDATAINFO*)TTPChanSelecteCascadResmembertable,
	(TXDATAINFO*)TTPChanSelecteCascadCancelResmembertable,
	(TXDATAINFO*)TTerminalLabelmembertable,
	(TXDATAINFO*)TDiscussListOprmembertable,
	(TXDATAINFO*)TTPRegistReqmembertable,
	(TXDATAINFO*)TCnsAVCapsetmembertable,
	(TXDATAINFO*)TCnsAddrCapsetmembertable,
	(TXDATAINFO*)TVgaInfomembertable,
	(TXDATAINFO*)TTPNatCfgmembertable,
	(TXDATAINFO*)TUmsVersionmembertable,
	(TXDATAINFO*)TToolSysInfomembertable,
	(TXDATAINFO*)THduChanInfomembertable,
	(TXDATAINFO*)THduInfomembertable,
	(TXDATAINFO*)THduCfgmembertable,
	(TXDATAINFO*)THduStyleUnitmembertable,
	(TXDATAINFO*)THduStyleDatamembertable,
	(TXDATAINFO*)THduUnitPlayInfomembertable,
	(TXDATAINFO*)THduPlanUnitmembertable,
	(TXDATAINFO*)THduPlanDatamembertable,
	(TXDATAINFO*)THduStyleInfomembertable,
	(TXDATAINFO*)TTPNMServerCfgmembertable,
	(TXDATAINFO*)TTPSysInfomembertable,
	(TXDATAINFO*)TTPTPadListmembertable,
	(TXDATAINFO*)TTPSingleAudioPortCfgmembertable,
	(TXDATAINFO*)TTpAudioPortInfomembertable,
	(TXDATAINFO*)TTPVideoPortInfomembertable,
	(TXDATAINFO*)TTPVideoDiagInfomembertable,
	(TXDATAINFO*)TTPAudioDiagInfomembertable,
	(TXDATAINFO*)TTPUpDownNetSpeedInfomembertable,
	(TXDATAINFO*)TTPUpDownSpeedInfomembertable,
	(TXDATAINFO*)TTPVgaMixInfomembertable,
	(TXDATAINFO*)TCnCameraCfgmembertable,
	(TXDATAINFO*)TCamNetmembertable,
	(TXDATAINFO*)TTPSerialInfomembertable,
	(TXDATAINFO*)TTVActmembertable,
	(TXDATAINFO*)TCenDevSleepInfomembertable,
	(TXDATAINFO*)TCentreCurNamemembertable,
	(TXDATAINFO*)TDCamPresetInfomembertable,
	(TXDATAINFO*)TCentreDCamCfgmembertable,
	(TXDATAINFO*)TCentreSchCfgmembertable,
	(TXDATAINFO*)TCentreACCfgmembertable,
	(TXDATAINFO*)TCentreACInfomembertable,
	(TXDATAINFO*)TOprBoardResultmembertable,
	(TXDATAINFO*)TTPBrdPosmembertable,
	(TXDATAINFO*)TTPBrdCfgmembertable,
	(TXDATAINFO*)TTPEqpCfgmembertable,
	(TXDATAINFO*)TTPMdlCfgmembertable,
	(TXDATAINFO*)TTPBrdInfomembertable,
	(TXDATAINFO*)TTPBrdMdlInfomembertable,
	(TXDATAINFO*)TTPBrdUsedInfomembertable,
	(TXDATAINFO*)TTPBrdUpGrademembertable,
	(TXDATAINFO*)TTPAudPowermembertable,
	(TXDATAINFO*)TTPHdAudioPortmembertable,
	(TXDATAINFO*)TTPHdAudioOutPortmembertable,
	(TXDATAINFO*)TTPHdDualAudioPortmembertable,
	(TXDATAINFO*)TTPMPAudioInfomembertable,
	(TXDATAINFO*)TTPVideoDisplayFrmmembertable,
	(TXDATAINFO*)TTPVideoParammembertable,
	(TXDATAINFO*)TTPImageAdjustParammembertable,
	(TXDATAINFO*)TTPVideoInfomembertable,
	(TXDATAINFO*)TTPSymboPointmembertable,
	(TXDATAINFO*)TTPVgaOutCfgmembertable,
	(TXDATAINFO*)TTPFecInfomembertable,
	(TXDATAINFO*)TTPLostPackResendmembertable,
	(TXDATAINFO*)TTPBitRateAdjustmembertable,
	(TXDATAINFO*)TTPVideoStandardmembertable,
	(TXDATAINFO*)TTPVideoPortmembertable,
	(TXDATAINFO*)TTPAutoTestMsgmembertable,
	(TXDATAINFO*)TTPEqualizermembertable,
	(TXDATAINFO*)TTPPIPModmembertable,
	(TXDATAINFO*)TTPLostFrameRatemembertable,
	(TXDATAINFO*)TTPVideoRecvmembertable,
	(TXDATAINFO*)TTPVideoEncDecResmembertable,
	(TXDATAINFO*)TTPVideoEncDecResPackmembertable,
	(TXDATAINFO*)TTPVideoFrameRatemembertable,
	(TXDATAINFO*)TTPVideoFrameRatePackmembertable,
	(TXDATAINFO*)TTPCodecPackStatmembertable,
	(TXDATAINFO*)TTPCnDsDatamembertable,
	(TXDATAINFO*)TTPCnNetBufParamembertable,
	(TXDATAINFO*)TTPCnRSParammembertable,
	(TXDATAINFO*)TTPAllConfCnsInfomembertable,
	(TXDATAINFO*)TCnDsTypemembertable,
	(TXDATAINFO*)TTPCnMixAddrmembertable,
	(TXDATAINFO*)TTPCnMixChanmembertable,
	(TXDATAINFO*)TTPCnMixParammembertable,
	(TXDATAINFO*)TTPNetAddressmembertable,
	(TXDATAINFO*)TTPMixerChannelParammembertable,
	(TXDATAINFO*)TTPCallSerInfomembertable,
	(TXDATAINFO*)TTPVidSrcCutLinesmembertable,
	(TXDATAINFO*)TVcrCfgmembertable,
	(TXDATAINFO*)TAdjustFrameRatemembertable,
	(TXDATAINFO*)TAdjustVidResmembertable,
	(TXDATAINFO*)TTPVGAInfomembertable,
	(TXDATAINFO*)TTPBmpInfomembertable,
	(TXDATAINFO*)TTPAddLogoPosmembertable,
	(TXDATAINFO*)TTPTranspDColormembertable,
	(TXDATAINFO*)TTPAddLogoParammembertable,
	(TXDATAINFO*)TTPFullLogoParammembertable,
	(TXDATAINFO*)TCnProduceTestMsgmembertable,
	(TXDATAINFO*)TRecBaseInfomembertable,
	(TXDATAINFO*)TRecFileListInfomembertable,
	(TXDATAINFO*)TRecFileInfomembertable,
	(TXDATAINFO*)TRecorderConfInfomembertable,
	(TXDATAINFO*)TRecorderMTInfomembertable,
	(TXDATAINFO*)TRecConfInfomembertable,
	(TXDATAINFO*)TConRecStatemembertable,
	(TXDATAINFO*)TRecConfResmembertable,
	(TXDATAINFO*)TRecPlayInfomembertable,
	(TXDATAINFO*)TPlayStatusMdyInfomembertable,
	(TXDATAINFO*)TConfPlayStatusmembertable,
	(TXDATAINFO*)TTPUpgradeSermembertable,
	(TXDATAINFO*)TTPSnapInfomembertable,
	(TXDATAINFO*)TTPSingleLoopInfomembertable,
	(TXDATAINFO*)TTPAllLoopInfomembertable,
	(TXDATAINFO*)TTPMtTerminalmembertable,
	(TXDATAINFO*)TTPMtOnLineListmembertable,
	(TXDATAINFO*)TTPMtRegInfomembertable,
	(TXDATAINFO*)TTPMcuRegInfomembertable,
	(TXDATAINFO*)TRegPackInfoExmembertable,
	(TXDATAINFO*)TUmsRegInfoExmembertable,
	(TXDATAINFO*)TUmsRegPackExmembertable,
	(TXDATAINFO*)TCnsRegInfoExmembertable,
	(TXDATAINFO*)TCnsRegPackExmembertable,
	(TXDATAINFO*)TTPAudPlayModemembertable,
	(TXDATAINFO*)TTPSmallPicRectInfomembertable,
	(TXDATAINFO*)TTPRecMtFormatmembertable,
	(TXDATAINFO*)TTPRebootTimemembertable,
	(TXDATAINFO*)TTPVidForamtmembertable,
	(TXDATAINFO*)TTPVidOffsetParammembertable,
	(TXDATAINFO*)TTPAllVidOffsetParammembertable,
	(TXDATAINFO*)TTPCnConfInfomembertable,
	(TXDATAINFO*)TTPDisplayTypemembertable,
	(TXDATAINFO*)TChairSingleStreenInfomembertable,
	(TXDATAINFO*)TChanViewResmembertable,
	(TXDATAINFO*)TChairStreenInfomembertable,
	(TXDATAINFO*)TVmpRegistInfomembertable,
	(TXDATAINFO*)TVmpRegAckmembertable,
	(TXDATAINFO*)TVmpTimeSpanmembertable,
	(TXDATAINFO*)TVmpMemberInfomembertable,
	(TXDATAINFO*)TDBPayloadmembertable,
	(TXDATAINFO*)TVmpStyleInfomembertable,
	(TXDATAINFO*)TVmpEncParammembertable,
	(TXDATAINFO*)TVmpMdyInfomembertable,
	(TXDATAINFO*)TVmpStartParammembertable,
	(TXDATAINFO*)TVmpStartResmembertable,
	(TXDATAINFO*)TVmpMdyResmembertable,
	(TXDATAINFO*)TVmpStopResmembertable,
	(TXDATAINFO*)TVmpChanResmembertable,
	(TXDATAINFO*)TVmpAskFramemembertable,
	(TXDATAINFO*)TVmpChanInfomembertable,
	(TXDATAINFO*)TTPAudPackCheckInfomembertable,
	(TXDATAINFO*)TTPSelViewReqmembertable,
	(TXDATAINFO*)TTPSelViewIndmembertable,
	(TXDATAINFO*)TTPSelViewNtfymembertable,
	(TXDATAINFO*)TEqpInfomembertable,
	(TXDATAINFO*)TRersvesEqpReqmembertable,
	(TXDATAINFO*)TRersvesEqpRspmembertable,
	(TXDATAINFO*)TBrdVmpReqmembertable,
	(TXDATAINFO*)TBrdVmpRspmembertable,
	(TXDATAINFO*)TBrdVmpChnlmembertable,
	(TXDATAINFO*)TBrdVmpStylemembertable,
	(TXDATAINFO*)TSetVmpInfoReqmembertable,
	(TXDATAINFO*)TSetVmpInfoRspmembertable,
	(TXDATAINFO*)TVmpCasecadeNtfymembertable,
	(TXDATAINFO*)TBrdVmpResNtfymembertable,
	(TXDATAINFO*)TBrdVmpResArraymembertable,
	(TXDATAINFO*)TCasecadePollEpReqmembertable,
	(TXDATAINFO*)TCasecadePollEpRspmembertable,
	(TXDATAINFO*)TTpPollListNtfymembertable,
	(TXDATAINFO*)TTpPollListIndmembertable,
	(TXDATAINFO*)TTpPollStatmembertable,
	(TXDATAINFO*)TTPDataConfInfomembertable,
	(TXDATAINFO*)TTPCallTypePrimembertable,
	(TXDATAINFO*)TTPDualDisplayParammembertable,
	(TXDATAINFO*)TTPDualDisplayStrategymembertable,
	(TXDATAINFO*)TTpObjmembertable,
	(TXDATAINFO*)TTpYouAreSeeingmembertable,
	(TXDATAINFO*)TTPAddBannerParammembertable,
	(TXDATAINFO*)TTPBannerBmpInfomembertable,
	(TXDATAINFO*)TTPFullBannerParammembertable,
	(TXDATAINFO*)TTPBannerParammembertable,
	(TXDATAINFO*)TTPLogoParammembertable,
	(TXDATAINFO*)TTPConfEpInfomembertable,
	(TXDATAINFO*)TTpVidCutLinemembertable,
	(TXDATAINFO*)TTpIconInfomembertable,
	(TXDATAINFO*)TTpAudMixmembertable,
	(TXDATAINFO*)TVidAliasInfomembertable,
	(TXDATAINFO*)TVidSourceInfomembertable,
	(TXDATAINFO*)TTPKedaManuProductTPmembertable,
	(TXDATAINFO*)TVidFeccInfomembertable,
	(TXDATAINFO*)TConfVidFeccInfomembertable,
	(TXDATAINFO*)TTPMatrixServerInfomembertable,
	(TXDATAINFO*)TTpMic10Infomembertable,
	(TXDATAINFO*)TTPTelnetInfomembertable,
	(TXDATAINFO*)TTPFtpInfomembertable,
	(TXDATAINFO*)TTpMicStatemembertable,
	(TXDATAINFO*)TTpMicSingleStatemembertable,
	(TXDATAINFO*)TTpNetIpRouteParammembertable,
	(TXDATAINFO*)TTpNetAllIpRouteInfomembertable,
	(TXDATAINFO*)TTPNtpSermembertable,
	(TXDATAINFO*)TTpUserSafemembertable,
	(TXDATAINFO*)TTpPasswordUpdateInfomembertable,
	(TXDATAINFO*)TTpAuxOutVolumemembertable,
	(TXDATAINFO*)TTpSuperUsermembertable,
	(TXDATAINFO*)TTPSingleMatrixInfomembertable,
	(TXDATAINFO*)TTPMatrixInfomembertable,
	(TXDATAINFO*)TTPMatrixNamemembertable,
	(TXDATAINFO*)TTPSlectViewmembertable,
	(TXDATAINFO*)TTPModulTerInfomembertable,
	(TXDATAINFO*)TRmMgrMtMPAddrmembertable,
	(TXDATAINFO*)TRmMgrDsmembertable,
	(TXDATAINFO*)TFtpFileInfomembertable,
	(TXDATAINFO*)TTPCloudPlatServerCfgmembertable,
	(TXDATAINFO*)TTPConfPasswordmembertable,
	(TXDATAINFO*)NULL
};

const TXENUMINFO enumEmTPDevRegUpdateSerDescript[]={
	{ "emDevInvalid", (int)emDevInvalid },
	{ "emTPTPad_Win7", (int)emTPTPad_Win7 },
	{ "emTPTPad_Android", (int)emTPTPad_Android },
	{ "emTPTPad_IOS", (int)emTPTPad_IOS },
	{ "emTPCns_T300A", (int)emTPCns_T300A },
	{ "emTPCns_T300B", (int)emTPCns_T300B },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPUpdateTypeDescript[]={
	{ "emTPUpdateForced", (int)emTPUpdateForced },
	{ "emTPUpdateSelected", (int)emTPUpdateSelected },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWiFiLinkStatDescript[]={
	{ "emWiFiIdle", (int)emWiFiIdle },
	{ "emWiFiConnecting", (int)emWiFiConnecting },
	{ "emWiFiConnectFailed", (int)emWiFiConnectFailed },
	{ "emWiFiConnected", (int)emWiFiConnected },
	{ "emWiFiDisconnecting", (int)emWiFiDisconnecting },
	{ "emWiFiDisconnected", (int)emWiFiDisconnected },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWiFiSelTypeDescript[]={
	{ "emWiFiCfgSel", (int)emWiFiCfgSel },
	{ "emWiFiScanSel", (int)emWiFiScanSel },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWiFiNetTypeDescript[]={
	{ "emWiFiAdHoc", (int)emWiFiAdHoc },
	{ "emWiFiInfra", (int)emWiFiInfra },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWiFiEncryptTypeDescript[]={
	{ "emWiFiEncryptNone", (int)emWiFiEncryptNone },
	{ "emWiFiEncryptWep", (int)emWiFiEncryptWep },
	{ "emWiFiEncryptWpa", (int)emWiFiEncryptWpa },
	{ "emWiFiEncryptWpa2", (int)emWiFiEncryptWpa2 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWiFiEncryptArithmeticDescript[]={
	{ "emWiFiArithNone", (int)emWiFiArithNone },
	{ "emWiFiArithWep40", (int)emWiFiArithWep40 },
	{ "emWiFiArithTkip", (int)emWiFiArithTkip },
	{ "emWiFiArithWrap", (int)emWiFiArithWrap },
	{ "emWiFiArithAes", (int)emWiFiArithAes },
	{ "emWiFiArithWep104", (int)emWiFiArithWep104 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVODRejCodeDescript[]={
	{ "emVODNoReason", (int)emVODNoReason },
	{ "emVODFileNotFound", (int)emVODFileNotFound },
	{ "emVODPalyNotStarted", (int)emVODPalyNotStarted },
	{ "emVODMaxUser", (int)emVODMaxUser },
	{ "emVODUserNotExist", (int)emVODUserNotExist },
	{ "emVODUserLogined", (int)emVODUserLogined },
	{ "emVODInvalidedPassword", (int)emVODInvalidedPassword },
	{ "emVODMEDIAVODInvalidedFileNameType", (int)emVODMEDIAVODInvalidedFileNameType },
	{ "emVODPlayBusy", (int)emVODPlayBusy },
	{ "emConnectFailed", (int)emConnectFailed },
	{ "emDisconnect", (int)emDisconnect },
	{ "emVODNoError", (int)emVODNoError },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVODStateDescript[]={
	{ "emVODIdle", (int)emVODIdle },
	{ "emVODLogin", (int)emVODLogin },
	{ "emVODFileListQuery", (int)emVODFileListQuery },
	{ "emVODFileInfoQuery", (int)emVODFileInfoQuery },
	{ "emVODPlay", (int)emVODPlay },
	{ "emVODPause", (int)emVODPause },
	{ "emVODStop", (int)emVODStop },
	{ "emVODSeek", (int)emVODSeek },
	{ "emVODActiveEnd", (int)emVODActiveEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTextAlignDescript[]={
	{ "emAlignLeft", (int)emAlignLeft },
	{ "emAlignCenter", (int)emAlignCenter },
	{ "emAlignRight", (int)emAlignRight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmRollModeDescript[]={
	{ "emStatic", (int)emStatic },
	{ "emRight2Left", (int)emRight2Left },
	{ "emDown2Up", (int)emDown2Up },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmRollSpeedDescript[]={
	{ "emSlower", (int)emSlower },
	{ "emSlow", (int)emSlow },
	{ "emNormal", (int)emNormal },
	{ "emFast", (int)emFast },
	{ "emFaster", (int)emFaster },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmStopBitsDescript[]={
	{ "em1StopBit", (int)em1StopBit },
	{ "em1HalfStopBits", (int)em1HalfStopBits },
	{ "em2StopBits", (int)em2StopBits },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmParityCheckDescript[]={
	{ "emNoCheck", (int)emNoCheck },
	{ "emOddCheck", (int)emOddCheck },
	{ "emEvenCheck", (int)emEvenCheck },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSerialTypeDescript[]={
	{ "emRS232", (int)emRS232 },
	{ "emRS422", (int)emRS422 },
	{ "emRS485", (int)emRS485 },
	{ "emSerialTcpip", (int)emSerialTcpip },
	{ "emRS422_1", (int)emRS422_1 },
	{ "emRS422_2", (int)emRS422_2 },
	{ "emRS422_3", (int)emRS422_3 },
	{ "emRSCom_1", (int)emRSCom_1 },
	{ "emRSCom_2", (int)emRSCom_2 },
	{ "emRSCom_3", (int)emRSCom_3 },
	{ "emRSCom_4", (int)emRSCom_4 },
	{ "emRSCom_5", (int)emRSCom_5 },
	{ "emRSCom_6", (int)emRSCom_6 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLanguageDescript[]={
	{ "emEnglish", (int)emEnglish },
	{ "emChineseSB", (int)emChineseSB },
	{ "emLangeEnd", (int)emLangeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmConfProtocolDescript[]={
	{ "emH323", (int)emH323 },
	{ "emH320", (int)emH320 },
	{ "emSIP", (int)emSIP },
	{ "emSat", (int)emSat },
	{ "emInvalidConfProtocel", (int)emInvalidConfProtocel },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmEncodeModeDescript[]={
	{ "emQualityFirst", (int)emQualityFirst },
	{ "emSpeedFirst", (int)emSpeedFirst },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLostPackageRestoreDescript[]={
	{ "emLPQualityFirst", (int)emLPQualityFirst },
	{ "emLPSpeedSlow", (int)emLPSpeedSlow },
	{ "emLPSpeedNormal", (int)emLPSpeedNormal },
	{ "emLPSpeedFast", (int)emLPSpeedFast },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMatrixTypeDescript[]={
	{ "emMatrixInner", (int)emMatrixInner },
	{ "emMatrixOuter", (int)emMatrixOuter },
	{ "emMatrixVas", (int)emMatrixVas },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDualVideoShowModeDescript[]={
	{ "emDualVideoOnSigleScreen", (int)emDualVideoOnSigleScreen },
	{ "emEachVideoOwnScreen", (int)emEachVideoOwnScreen },
	{ "emTripleVideoOnSingleScn", (int)emTripleVideoOnSingleScn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDisplayRatioDescript[]={
	{ "emDR4to3", (int)emDR4to3 },
	{ "emDR16to9", (int)emDR16to9 },
	{ "emDRAuto", (int)emDRAuto },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVideoTypeDescript[]={
	{ "emPriomVideo", (int)emPriomVideo },
	{ "emSecondVideo", (int)emSecondVideo },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVideoStandardDescript[]={
	{ "emPAL", (int)emPAL },
	{ "emNTSC", (int)emNTSC },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVideoInterfaceDescript[]={
	{ "emVidVGA", (int)emVidVGA },
	{ "emSVideo", (int)emSVideo },
	{ "emCVideo", (int)emCVideo },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtVideoPortDescript[]={
	{ "emMtVGA", (int)emMtVGA },
	{ "emMtSVid", (int)emMtSVid },
	{ "emMtPC", (int)emMtPC },
	{ "emMtC1Vid", (int)emMtC1Vid },
	{ "emMtC2Vid", (int)emMtC2Vid },
	{ "emMtC3Vid", (int)emMtC3Vid },
	{ "emMtC4Vid", (int)emMtC4Vid },
	{ "emMtC5Vid", (int)emMtC5Vid },
	{ "emMtC6Vid", (int)emMtC6Vid },
	{ "emMtExternalVid", (int)emMtExternalVid },
	{ "emMtVideoMaxCount", (int)emMtVideoMaxCount },
	{ "emMtVidInvalid", (int)emMtVidInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTripModeDescript[]={
	{ "emTripModeAuto", (int)emTripModeAuto },
	{ "emTripModeManu", (int)emTripModeManu },
	{ "emTripModeNegative", (int)emTripModeNegative },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLabelTypeDescript[]={
	{ "emLabelAuto", (int)emLabelAuto },
	{ "emLabelUserDef", (int)emLabelUserDef },
	{ "emLabelOff", (int)emLabelOff },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDLProtocolDescript[]={
	{ "emPPP", (int)emPPP },
	{ "emHDLC", (int)emHDLC },
	{ "emPPPOE", (int)emPPPOE },
	{ "emMP", (int)emMP },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAuthenticationTypeDescript[]={
	{ "emPAP", (int)emPAP },
	{ "emCHAP", (int)emCHAP },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFrameUnitTypeDescript[]={
	{ "emFrameSecond", (int)emFrameSecond },
	{ "emSecondFrame", (int)emSecondFrame },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMediaTypeDescript[]={
	{ "emMediaVideo", (int)emMediaVideo },
	{ "emMediaAudio", (int)emMediaAudio },
	{ "emMediaAV", (int)emMediaAV },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVideoFormatDescript[]={
	{ "emVH261", (int)emVH261 },
	{ "emVH262", (int)emVH262 },
	{ "emVH263", (int)emVH263 },
	{ "emVH263plus", (int)emVH263plus },
	{ "emVH264", (int)emVH264 },
	{ "emVMPEG4", (int)emVMPEG4 },
	{ "emVEnd", (int)emVEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAudioFormatDescript[]={
	{ "emAG711a", (int)emAG711a },
	{ "emAG711u", (int)emAG711u },
	{ "emAG722", (int)emAG722 },
	{ "emAG7231", (int)emAG7231 },
	{ "emAG728", (int)emAG728 },
	{ "emAG729", (int)emAG729 },
	{ "emAMP3", (int)emAMP3 },
	{ "emAG721", (int)emAG721 },
	{ "emAG7221", (int)emAG7221 },
	{ "emAG719", (int)emAG719 },
	{ "emAMpegAACLC", (int)emAMpegAACLC },
	{ "emAMpegAACLD", (int)emAMpegAACLD },
	{ "emAEnd", (int)emAEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVideoResolutionDescript[]={
	{ "emVResolutionAuto", (int)emVResolutionAuto },
	{ "emVSQCIF", (int)emVSQCIF },
	{ "emVQCIF", (int)emVQCIF },
	{ "emVCIF", (int)emVCIF },
	{ "emV2CIF", (int)emV2CIF },
	{ "emV4CIF", (int)emV4CIF },
	{ "emV16CIF", (int)emV16CIF },
	{ "emVHD480i720x480", (int)emVHD480i720x480 },
	{ "emVHD480p720x480", (int)emVHD480p720x480 },
	{ "emVHD576i720x576", (int)emVHD576i720x576 },
	{ "emVHD576p720x576", (int)emVHD576p720x576 },
	{ "emVHD720p1280x720", (int)emVHD720p1280x720 },
	{ "emVHD1080i1920x1080", (int)emVHD1080i1920x1080 },
	{ "emVHD1080p1920x1080", (int)emVHD1080p1920x1080 },
	{ "emVGA352x240", (int)emVGA352x240 },
	{ "emVGA704x480", (int)emVGA704x480 },
	{ "emVGA640x480", (int)emVGA640x480 },
	{ "emVGA800x600", (int)emVGA800x600 },
	{ "emVGA1024x768", (int)emVGA1024x768 },
	{ "emVGA1280x768", (int)emVGA1280x768 },
	{ "emVGA1280x800", (int)emVGA1280x800 },
	{ "emVGA1366x768", (int)emVGA1366x768 },
	{ "emVGA1280x854", (int)emVGA1280x854 },
	{ "emVGA1440x900", (int)emVGA1440x900 },
	{ "emVGA1280x1024", (int)emVGA1280x1024 },
	{ "emVGA1680x1050", (int)emVGA1680x1050 },
	{ "emVGA1600x1200", (int)emVGA1600x1200 },
	{ "emVGA1920x1200", (int)emVGA1920x1200 },
	{ "emVSQCIF112x96", (int)emVSQCIF112x96 },
	{ "emVSQCIF96x80", (int)emVSQCIF96x80 },
	{ "emV320x192", (int)emV320x192 },
	{ "emV432x240", (int)emV432x240 },
	{ "emV480x272", (int)emV480x272 },
	{ "emV640x368", (int)emV640x368 },
	{ "emV864x480", (int)emV864x480 },
	{ "emV960x544", (int)emV960x544 },
	{ "emV1440x816", (int)emV1440x816 },
	{ "emVResEnd", (int)emVResEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmQoSDescript[]={
	{ "emDiffServ", (int)emDiffServ },
	{ "emIPPrecedence", (int)emIPPrecedence },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTOSDescript[]={
	{ "emTOSNone", (int)emTOSNone },
	{ "emTOSMinCost", (int)emTOSMinCost },
	{ "emTOSMaxReliable", (int)emTOSMaxReliable },
	{ "emTOSMaxThruput", (int)emTOSMaxThruput },
	{ "emTOSMinDelay", (int)emTOSMinDelay },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSiteDescript[]={
	{ "emLocal", (int)emLocal },
	{ "emRemote", (int)emRemote },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmChanTypeDescript[]={
	{ "emChanSendAudio", (int)emChanSendAudio },
	{ "emChanSendPrimoVideo", (int)emChanSendPrimoVideo },
	{ "emChanSendSecondVideo", (int)emChanSendSecondVideo },
	{ "emChanSendFecc", (int)emChanSendFecc },
	{ "emChanSendT120", (int)emChanSendT120 },
	{ "emChanRecvAudio", (int)emChanRecvAudio },
	{ "emChanRecvPrimoVideo", (int)emChanRecvPrimoVideo },
	{ "emChanRecvSecondVideo", (int)emChanRecvSecondVideo },
	{ "emChanRecvFecc", (int)emChanRecvFecc },
	{ "emChanRecvT120", (int)emChanRecvT120 },
	{ "emChanTypeEnd", (int)emChanTypeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCodecComponentDescript[]={
	{ "emPriomVideoEncoder", (int)emPriomVideoEncoder },
	{ "emPriomVideoDecoder", (int)emPriomVideoDecoder },
	{ "emSecondVideoEncoder", (int)emSecondVideoEncoder },
	{ "emSecondVideoDecoder", (int)emSecondVideoDecoder },
	{ "emAudioEncoder", (int)emAudioEncoder },
	{ "emAudioDecoder", (int)emAudioDecoder },
	{ "emCodecComponentEnd", (int)emCodecComponentEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtModelDescript[]={
	{ "emUnknownMtModel", (int)emUnknownMtModel },
	{ "emPCMT", (int)emPCMT },
	{ "em8010", (int)em8010 },
	{ "em8010A", (int)em8010A },
	{ "em8010Aplus", (int)em8010Aplus },
	{ "em8010C", (int)em8010C },
	{ "em8010C1", (int)em8010C1 },
	{ "emIMT", (int)emIMT },
	{ "em8220A", (int)em8220A },
	{ "em8220B", (int)em8220B },
	{ "em8220C", (int)em8220C },
	{ "em8620A", (int)em8620A },
	{ "emTS6610E", (int)emTS6610E },
	{ "emTS6210", (int)emTS6210 },
	{ "em8010A_2", (int)em8010A_2 },
	{ "em8010A_4", (int)em8010A_4 },
	{ "em8010A_8", (int)em8010A_8 },
	{ "em7210", (int)em7210 },
	{ "em7610", (int)em7610 },
	{ "emTS5610", (int)emTS5610 },
	{ "emTS6610", (int)emTS6610 },
	{ "em7810", (int)em7810 },
	{ "em7910", (int)em7910 },
	{ "em7620_A", (int)em7620_A },
	{ "em7620_B", (int)em7620_B },
	{ "em7820_A", (int)em7820_A },
	{ "em7820_B", (int)em7820_B },
	{ "em7920_A", (int)em7920_A },
	{ "em7920_B", (int)em7920_B },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFileSysDescript[]={
	{ "emRAWFS", (int)emRAWFS },
	{ "emTFFS", (int)emTFFS },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmEncryptArithmeticDescript[]={
	{ "emEncryptNone", (int)emEncryptNone },
	{ "emDES", (int)emDES },
	{ "emAES", (int)emAES },
	{ "emEncryptAuto", (int)emEncryptAuto },
	{ "emEncryptEnd", (int)emEncryptEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmActionDescript[]={
	{ "emActStart", (int)emActStart },
	{ "emActStop", (int)emActStop },
	{ "emActPause", (int)emActPause },
	{ "emActResume", (int)emActResume },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmOptRetDescript[]={
	{ "emEnable", (int)emEnable },
	{ "emDisable", (int)emDisable },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmConfModeDescript[]={
	{ "emP2PConf", (int)emP2PConf },
	{ "emMCCConf", (int)emMCCConf },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtAddrTypeDescript[]={
	{ "emIPAddr", (int)emIPAddr },
	{ "emE164", (int)emE164 },
	{ "emH323id", (int)emH323id },
	{ "emDialNum", (int)emDialNum },
	{ "emSipAddr", (int)emSipAddr },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDirectionDescript[]={
	{ "emUP", (int)emUP },
	{ "emDown", (int)emDown },
	{ "emLeft", (int)emLeft },
	{ "emRight", (int)emRight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCallStateDescript[]={
	{ "emCS_Idle", (int)emCS_Idle },
	{ "emCS_Calling", (int)emCS_Calling },
	{ "emCS_P2P", (int)emCS_P2P },
	{ "emCS_MCC", (int)emCS_MCC },
	{ "emCS_Hanup", (int)emCS_Hanup },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCallSiteStateDescript[]={
	{ "emCSS_IDLE", (int)emCSS_IDLE },
	{ "emCSS_Init", (int)emCSS_Init },
	{ "emCSS_Waiting", (int)emCSS_Waiting },
	{ "emCSS_Connected", (int)emCSS_Connected },
	{ "emCSS_Failed", (int)emCSS_Failed },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTransModeDescript[]={
	{ "emUnicast", (int)emUnicast },
	{ "emBroadcast", (int)emBroadcast },
	{ "emMulticast", (int)emMulticast },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtInstTypeDescript[]={
	{ "emMtService", (int)emMtService },
	{ "emMtUI", (int)emMtUI },
	{ "emMtConsole", (int)emMtConsole },
	{ "emMtH323Service", (int)emMtH323Service },
	{ "emMtH320Service", (int)emMtH320Service },
	{ "emMtSipService", (int)emMtSipService },
	{ "emMtH323StackIn", (int)emMtH323StackIn },
	{ "emMtH323StackOut", (int)emMtH323StackOut },
	{ "emMtMP", (int)emMtMP },
	{ "emMtDevice", (int)emMtDevice },
	{ "emMtAgent", (int)emMtAgent },
	{ "emMtSipStackIn", (int)emMtSipStackIn },
	{ "emMtSipStackOut", (int)emMtSipStackOut },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVMPStyleDescript[]={
	{ "emVMPDynamic", (int)emVMPDynamic },
	{ "emVMPOne", (int)emVMPOne },
	{ "emVMPVTwo", (int)emVMPVTwo },
	{ "emVMPHTwo", (int)emVMPHTwo },
	{ "emVMPThree", (int)emVMPThree },
	{ "emVMPFour", (int)emVMPFour },
	{ "emVMPSix", (int)emVMPSix },
	{ "emVMPEight", (int)emVMPEight },
	{ "emVMPNine", (int)emVMPNine },
	{ "emVMPTen", (int)emVMPTen },
	{ "emVMPThirteen", (int)emVMPThirteen },
	{ "emVMPSixteen", (int)emVMPSixteen },
	{ "emVMPSpecFour", (int)emVMPSpecFour },
	{ "emVMPSeven", (int)emVMPSeven },
	{ "emVMPSpecThirteen", (int)emVMPSpecThirteen },
	{ "emVMPTwenty", (int)emVMPTwenty },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVMPMmbTypeDescript[]={
	{ "emVMPMmbMCSspec", (int)emVMPMmbMCSspec },
	{ "emVMPMmbSpeaker", (int)emVMPMmbSpeaker },
	{ "emVMPMmbChairman", (int)emVMPMmbChairman },
	{ "emVMPMmbPoll", (int)emVMPMmbPoll },
	{ "emVMPMmbVAC", (int)emVMPMmbVAC },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSMSTypeDescript[]={
	{ "emSMSSingleLine", (int)emSMSSingleLine },
	{ "emSMSPageTitle", (int)emSMSPageTitle },
	{ "emSMSRollTitle", (int)emSMSRollTitle },
	{ "emSMSStaticTitle", (int)emSMSStaticTitle },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtFileDescript[]={
	{ "emMtFileBegin", (int)emMtFileBegin },
	{ "emMtConfigFile", (int)emMtConfigFile },
	{ "emMtOldConfigBakFile", (int)emMtOldConfigBakFile },
	{ "emMtDebugConfiFile", (int)emMtDebugConfiFile },
	{ "emMtCameraCommandFile", (int)emMtCameraCommandFile },
	{ "emMtCameraPresetPostionFile", (int)emMtCameraPresetPostionFile },
	{ "emMtExternMaxtrixCommandFile", (int)emMtExternMaxtrixCommandFile },
	{ "emMtExternMaxtrixPortNameFile", (int)emMtExternMaxtrixPortNameFile },
	{ "emMtInnerMaxtrixSchemeFile", (int)emMtInnerMaxtrixSchemeFile },
	{ "emMtStreamMediaHtmlFile", (int)emMtStreamMediaHtmlFile },
	{ "emMtResourceFile", (int)emMtResourceFile },
	{ "emMtZipResourceFile", (int)emMtZipResourceFile },
	{ "emMtSymbolFile", (int)emMtSymbolFile },
	{ "emMtBannerFile", (int)emMtBannerFile },
	{ "emMtStaticPicFile", (int)emMtStaticPicFile },
	{ "emMtResInBin", (int)emMtResInBin },
	{ "emMtAddressBookEx", (int)emMtAddressBookEx },
	{ "emMtUpdateSysFile", (int)emMtUpdateSysFile },
	{ "emMtMinitorFile", (int)emMtMinitorFile },
	{ "emMtZipFile", (int)emMtZipFile },
	{ "emMtHintFile", (int)emMtHintFile },
	{ "emMtKeyFile", (int)emMtKeyFile },
	{ "emMtInnerPxyFile", (int)emMtInnerPxyFile },
	{ "emMtThreadBlockFile", (int)emMtThreadBlockFile },
	{ "emMtLogFile", (int)emMtLogFile },
	{ "emMtUserWordFile", (int)emMtUserWordFile },
	{ "emMtKdvLog", (int)emMtKdvLog },
	{ "emMtFileEnd", (int)emMtFileEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCallRateDescript[]={
	{ "emRaten64", (int)emRaten64 },
	{ "emRaten2m64", (int)emRaten2m64 },
	{ "emRaten3m64", (int)emRaten3m64 },
	{ "emRaten4m64", (int)emRaten4m64 },
	{ "emRaten5m64", (int)emRaten5m64 },
	{ "emRaten6m64", (int)emRaten6m64 },
	{ "emRater384", (int)emRater384 },
	{ "emRater1536", (int)emRater1536 },
	{ "emRater1920", (int)emRater1920 },
	{ "emRater128", (int)emRater128 },
	{ "emRater192", (int)emRater192 },
	{ "emRater256", (int)emRater256 },
	{ "emRater320", (int)emRater320 },
	{ "emRater512", (int)emRater512 },
	{ "emRater768", (int)emRater768 },
	{ "emRater1152", (int)emRater1152 },
	{ "emRater1472", (int)emRater1472 },
	{ "emRater3M", (int)emRater3M },
	{ "emRater4M", (int)emRater4M },
	{ "emRater6M", (int)emRater6M },
	{ "emRater8M", (int)emRater8M },
	{ "emRaterLastOne", (int)emRaterLastOne },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPCCapFormatDescript[]={
	{ "emCapPCFrameBMP", (int)emCapPCFrameBMP },
	{ "emCapPCFrameUYUY", (int)emCapPCFrameUYUY },
	{ "emCapPCFrameI420", (int)emCapPCFrameI420 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPiPModeDescript[]={
	{ "emPiPClose", (int)emPiPClose },
	{ "emPiPRightBottom", (int)emPiPRightBottom },
	{ "emPiPLeftBottom", (int)emPiPLeftBottom },
	{ "emPiPLeftTop", (int)emPiPLeftTop },
	{ "emPiPRightTop", (int)emPiPRightTop },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDVBComponentDescript[]={
	{ "emDVBEncoder", (int)emDVBEncoder },
	{ "emDVBPriomVideoDecoder", (int)emDVBPriomVideoDecoder },
	{ "emDVBSecondVideoDecoder", (int)emDVBSecondVideoDecoder },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmUIPosionDescript[]={
	{ "emMT", (int)emMT },
	{ "emMTC", (int)emMTC },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCallDisconnectReasonDescript[]={
	{ "emDisconnect_Busy", (int)emDisconnect_Busy },
	{ "emDisconnect_Normal", (int)emDisconnect_Normal },
	{ "emDisconnect_Rejected", (int)emDisconnect_Rejected },
	{ "emDisconnect_Unreachable", (int)emDisconnect_Unreachable },
	{ "emDisconnect_Local", (int)emDisconnect_Local },
	{ "emDisconnect_Nnknown", (int)emDisconnect_Nnknown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMCModeDescript[]={
	{ "emMcSpeech", (int)emMcSpeech },
	{ "emMcDiscuss", (int)emMcDiscuss },
	{ "emMcModeEnd", (int)emMcModeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmInnerVMPStyleDescript[]={
	{ "emInnerVMPAuto", (int)emInnerVMPAuto },
	{ "emInnerVMPOne", (int)emInnerVMPOne },
	{ "emInnerVMPTwo", (int)emInnerVMPTwo },
	{ "emInnerVMPThree", (int)emInnerVMPThree },
	{ "emInnerVMPFour", (int)emInnerVMPFour },
	{ "emInnerVMPFive", (int)emInnerVMPFive },
	{ "emInnerVMPSix", (int)emInnerVMPSix },
	{ "emInnerVMPTwoBigLittle", (int)emInnerVMPTwoBigLittle },
	{ "emInnerVMPThreeBigLittle", (int)emInnerVMPThreeBigLittle },
	{ "emInnerVMPFourBigLittle", (int)emInnerVMPFourBigLittle },
	{ "emInnerVMPEnd", (int)emInnerVMPEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVMPComponentDescript[]={
	{ "emVMPDecNull", (int)emVMPDecNull },
	{ "emVMPDec1th", (int)emVMPDec1th },
	{ "emVMPDec2th", (int)emVMPDec2th },
	{ "emVMPDec3th", (int)emVMPDec3th },
	{ "emVMPDec4th", (int)emVMPDec4th },
	{ "emVMPDec5th", (int)emVMPDec5th },
	{ "emVMPDecLocal", (int)emVMPDecLocal },
	{ "emVMPEnd", (int)emVMPEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCapTypeDescript[]={
	{ "emAudioOnly", (int)emAudioOnly },
	{ "emCameraOnly", (int)emCameraOnly },
	{ "emACBoth", (int)emACBoth },
	{ "emDesktopOnly", (int)emDesktopOnly },
	{ "emADBoth", (int)emADBoth },
	{ "emFileAVBoth", (int)emFileAVBoth },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPPPoEStateDescript[]={
	{ "emFree", (int)emFree },
	{ "emLinking", (int)emLinking },
	{ "emLinkup", (int)emLinkup },
	{ "emLinkdown", (int)emLinkdown },
	{ "emUserError", (int)emUserError },
	{ "emTimeOut", (int)emTimeOut },
	{ "emAgentError", (int)emAgentError },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDhcpStateDescript[]={
	{ "emDhcpFree", (int)emDhcpFree },
	{ "emDhcpLinkup", (int)emDhcpLinkup },
	{ "emDhcpLinkdown", (int)emDhcpLinkdown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAddrGroupOptTypeDescript[]={
	{ "emCallIn", (int)emCallIn },
	{ "emCallOut", (int)emCallOut },
	{ "emUserDef", (int)emUserDef },
	{ "emTemplate", (int)emTemplate },
	{ "emSiteCall", (int)emSiteCall },
	{ "emMissed", (int)emMissed },
	{ "emUserDefExt0", (int)emUserDefExt0 },
	{ "emUserDefExt1", (int)emUserDefExt1 },
	{ "emUserDefExt2", (int)emUserDefExt2 },
	{ "emUserDefExt3", (int)emUserDefExt3 },
	{ "emUserDefExt4", (int)emUserDefExt4 },
	{ "emUserDefExt5", (int)emUserDefExt5 },
	{ "emInvalid", (int)emInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHotKeyTypeDescript[]={
	{ "emApplySpeak", (int)emApplySpeak },
	{ "emApplyChair", (int)emApplyChair },
	{ "emPrevPage", (int)emPrevPage },
	{ "emNextPage", (int)emNextPage },
	{ "emBack", (int)emBack },
	{ "emLoop", (int)emLoop },
	{ "emHotkeyEnd", (int)emHotkeyEnd },
	{ "emAEC", (int)emAEC },
	{ "emDial", (int)emDial },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtOSTypeDescript[]={
	{ "emWindows", (int)emWindows },
	{ "emVxworks", (int)emVxworks },
	{ "emLinux", (int)emLinux },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFxoStateDescript[]={
	{ "emFxoIdle", (int)emFxoIdle },
	{ "emFxoCalling", (int)emFxoCalling },
	{ "emFxoConnect", (int)emFxoConnect },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtLoudspeakerValDescript[]={
	{ "emLoudspeakerLow", (int)emLoudspeakerLow },
	{ "emLoudspeakerMiddle", (int)emLoudspeakerMiddle },
	{ "emLoudspeakerHigh", (int)emLoudspeakerHigh },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmNetTypeDescript[]={
	{ "emInternet", (int)emInternet },
	{ "emSpecial", (int)emSpecial },
	{ "emVPN", (int)emVPN },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSysRunSuccessFlagDescript[]={
	{ "emSysNoUpdateOperation", (int)emSysNoUpdateOperation },
	{ "emSysUpdateVersionRollBack", (int)emSysUpdateVersionRollBack },
	{ "emSysUpdateVersionSuccess", (int)emSysUpdateVersionSuccess },
	{ "emSysSetUpdateFlagFailed", (int)emSysSetUpdateFlagFailed },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMcuNtfMsgTypeDescript[]={
	{ "emMsgNoneNtf", (int)emMsgNoneNtf },
	{ "emMsgBePolledNextNtf", (int)emMsgBePolledNextNtf },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAutoTestTypeDescript[]={
	{ "emAutoTestTypeBegin", (int)emAutoTestTypeBegin },
	{ "emAutoTestEth0Func", (int)emAutoTestEth0Func },
	{ "emAutoTestEth1Func", (int)emAutoTestEth1Func },
	{ "emAutoTestE1Func", (int)emAutoTestE1Func },
	{ "emAutoTestAudioLoopBackFunc", (int)emAutoTestAudioLoopBackFunc },
	{ "emAutoTestVideoLoopBackFunc", (int)emAutoTestVideoLoopBackFunc },
	{ "emAutoTestSDI1InAllOutFunc", (int)emAutoTestSDI1InAllOutFunc },
	{ "emAutoTestSDI2InAllOutFunc", (int)emAutoTestSDI2InAllOutFunc },
	{ "emAutoTestDVI1InAllOutFunc", (int)emAutoTestDVI1InAllOutFunc },
	{ "emAutoTestDVI2InAllOutFunc", (int)emAutoTestDVI2InAllOutFunc },
	{ "emAutoTestDVI3InAllOutFunc", (int)emAutoTestDVI3InAllOutFunc },
	{ "emAuotTestCInAllOutFunc", (int)emAuotTestCInAllOutFunc },
	{ "emAutoTestDVI1InAllOutFunc_YPbPr", (int)emAutoTestDVI1InAllOutFunc_YPbPr },
	{ "emAutoTestDVI1InAllOutFunc_OSDYPbPr", (int)emAutoTestDVI1InAllOutFunc_OSDYPbPr },
	{ "emAutoTestBluerayHDMIFunc", (int)emAutoTestBluerayHDMIFunc },
	{ "emAutoTestBluerayHDMI2Func", (int)emAutoTestBluerayHDMI2Func },
	{ "emAutoTestBluerayHDMI3Func", (int)emAutoTestBluerayHDMI3Func },
	{ "emAutoTestBluerayRCAFunc", (int)emAutoTestBluerayRCAFunc },
	{ "emAutoTestCanonMICFunc", (int)emAutoTestCanonMICFunc },
	{ "emAutoTestDigMICFunc", (int)emAutoTestDigMICFunc },
	{ "emAutoTestLoudspeakerFunc", (int)emAutoTestLoudspeakerFunc },
	{ "emAutoTestCameraRotaFor232Func", (int)emAutoTestCameraRotaFor232Func },
	{ "emAutoTestCameraRotaFor485Func", (int)emAutoTestCameraRotaFor485Func },
	{ "emAutoTestRTCFunc", (int)emAutoTestRTCFunc },
	{ "emAutoTestLightFunc", (int)emAutoTestLightFunc },
	{ "emAutoTestRemoteCtrlFunc", (int)emAutoTestRemoteCtrlFunc },
	{ "emAutoTestSetDefault", (int)emAutoTestSetDefault },
	{ "emAutoTestRebootSysFunc", (int)emAutoTestRebootSysFunc },
	{ "emAutoTestTypeEnd", (int)emAutoTestTypeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGKRegFailedReasonDescript[]={
	{ "emNone", (int)emNone },
	{ "emGKUnReachable", (int)emGKUnReachable },
	{ "emInvalidAliase", (int)emInvalidAliase },
	{ "emDupAlias", (int)emDupAlias },
	{ "emInvalidCallAddress", (int)emInvalidCallAddress },
	{ "emResourceUnavailable", (int)emResourceUnavailable },
	{ "emUnknown", (int)emUnknown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSleepStateDescript[]={
	{ "emSleepFail", (int)emSleepFail },
	{ "emWaitSleeping", (int)emWaitSleeping },
	{ "emSleeping", (int)emSleeping },
	{ "emSleeped", (int)emSleeped },
	{ "emWaking", (int)emWaking },
	{ "emWakeup", (int)emWakeup },
	{ "emWaitWaking", (int)emWaitWaking },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtAppNameDescript[]={
	{ "emMtAgentApp", (int)emMtAgentApp },
	{ "emMtServiceApp", (int)emMtServiceApp },
	{ "emMtGuardApp", (int)emMtGuardApp },
	{ "emMtUEApp", (int)emMtUEApp },
	{ "emMtStackInApp", (int)emMtStackInApp },
	{ "emMtStackOutApp", (int)emMtStackOutApp },
	{ "emMtRcpApp", (int)emMtRcpApp },
	{ "emMtH320StackApp", (int)emMtH320StackApp },
	{ "emMtRcSimApp", (int)emMtRcSimApp },
	{ "emMtMcApp", (int)emMtMcApp },
	{ "emMtSnmpApp", (int)emMtSnmpApp },
	{ "emMtConfigApp", (int)emMtConfigApp },
	{ "emMtUIApp", (int)emMtUIApp },
	{ "emMtDeviceApp", (int)emMtDeviceApp },
	{ "emMtCodecApp", (int)emMtCodecApp },
	{ "emMtConsoleApp", (int)emMtConsoleApp },
	{ "emMtSysApp", (int)emMtSysApp },
	{ "emMtH323ServiceApp", (int)emMtH323ServiceApp },
	{ "emMtH320ServiceApp", (int)emMtH320ServiceApp },
	{ "emMtSipServiceApp", (int)emMtSipServiceApp },
	{ "emMtDvbApp", (int)emMtDvbApp },
	{ "emMtDvbssnApp", (int)emMtDvbssnApp },
	{ "emMtVodClientApp", (int)emMtVodClientApp },
	{ "emMtPcdualvideoApp", (int)emMtPcdualvideoApp },
	{ "emMtUpgradeApp", (int)emMtUpgradeApp },
	{ "emMtbApp", (int)emMtbApp },
	{ "emMtAutotestApp", (int)emMtAutotestApp },
	{ "emMtAutotestClientApp", (int)emMtAutotestClientApp },
	{ "emMtRemoteSimApp", (int)emMtRemoteSimApp },
	{ "emMtThreadDetectApp", (int)emMtThreadDetectApp },
	{ "emMtLogRecvApp", (int)emMtLogRecvApp },
	{ "emMtLogIOApp", (int)emMtLogIOApp },
	{ "emMtProxyClientApp", (int)emMtProxyClientApp },
	{ "emMtSipStackInApp", (int)emMtSipStackInApp },
	{ "emMtSipStackOutApp", (int)emMtSipStackOutApp },
	{ "emMtSatServiceApp", (int)emMtSatServiceApp },
	{ "emMtTpRegApp", (int)emMtTpRegApp },
	{ "emMtMpRemoteMgrApp", (int)emMtMpRemoteMgrApp },
	{ "emMtAppEnd", (int)emMtAppEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumHD_PORT_MASKDescript[]={
	{ "PORT_SDI", (int)PORT_SDI },
	{ "PORT_HDMI", (int)PORT_HDMI },
	{ "PORT_YPrPb1", (int)PORT_YPrPb1 },
	{ "PORT_YPrPb2", (int)PORT_YPrPb2 },
	{ "PORT_VGA", (int)PORT_VGA },
	{ "PORT_C0", (int)PORT_C0 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHDAudPortInDescript[]={
	{ "emAudInCL", (int)emAudInCL },
	{ "emAudInCR", (int)emAudInCR },
	{ "emAudInCanonL", (int)emAudInCanonL },
	{ "emAudInCanonR", (int)emAudInCanonR },
	{ "emAudInHDMI1", (int)emAudInHDMI1 },
	{ "emAudInHDMI2", (int)emAudInHDMI2 },
	{ "emAudInHDMI3", (int)emAudInHDMI3 },
	{ "emAudInMic1", (int)emAudInMic1 },
	{ "emAudInMic2", (int)emAudInMic2 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHDAudPortOutDescript[]={
	{ "emAudOutCCanon", (int)emAudOutCCanon },
	{ "emAudOutHDMI1", (int)emAudOutHDMI1 },
	{ "emAudOutHDMI2", (int)emAudOutHDMI2 },
	{ "emAudOutHDMI3", (int)emAudOutHDMI3 },
	{ "emAudOutReproducer", (int)emAudOutReproducer },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLogStatusDescript[]={
	{ "emLogClose", (int)emLogClose },
	{ "emLogOpen", (int)emLogOpen },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLogExportResultDescript[]={
	{ "emLogExportFailed", (int)emLogExportFailed },
	{ "emLogExportSuccess", (int)emLogExportSuccess },
	{ "emLogExportNoDisk", (int)emLogExportNoDisk },
	{ "emLogExportNoFile", (int)emLogExportNoFile },
	{ "emLogExportTransing", (int)emLogExportTransing },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFecModeTypeDescript[]={
	{ "emMTFECTYPENONE", (int)emMTFECTYPENONE },
	{ "emMTFECTYPERAID5", (int)emMTFECTYPERAID5 },
	{ "emMTFECTYPERAID5INTERLEAVE", (int)emMTFECTYPERAID5INTERLEAVE },
	{ "emMTFECTYPERAID6", (int)emMTFECTYPERAID6 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLabelPosTypeDescript[]={
	{ "emTopLeft", (int)emTopLeft },
	{ "emTopRight", (int)emTopRight },
	{ "emBottomLeft", (int)emBottomLeft },
	{ "emBottomRight", (int)emBottomRight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtcBoxCallIndexDescript[]={
	{ "emShortCutCall1", (int)emShortCutCall1 },
	{ "emShortCutCall2", (int)emShortCutCall2 },
	{ "emShortCutCall3", (int)emShortCutCall3 },
	{ "emShortCutCall4", (int)emShortCutCall4 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSipRegFailedReasonDescript[]={
	{ "emLocalNormalUnreg", (int)emLocalNormalUnreg },
	{ "emInvalidUserNameAndPassword", (int)emInvalidUserNameAndPassword },
	{ "emRegistrarUnReachable", (int)emRegistrarUnReachable },
	{ "emInvalidAlias", (int)emInvalidAlias },
	{ "emUnknownReason", (int)emUnknownReason },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMtRecChnnlStateDescript[]={
	{ "STATE_IDLE", (int)STATE_IDLE },
	{ "STATE_RECREADY", (int)STATE_RECREADY },
	{ "STATE_RECORDING", (int)STATE_RECORDING },
	{ "STATE_RECPAUSE", (int)STATE_RECPAUSE },
	{ "STATE_PLAYREADY", (int)STATE_PLAYREADY },
	{ "STATE_PLAYREADYPLAY", (int)STATE_PLAYREADYPLAY },
	{ "STATE_PLAYING", (int)STATE_PLAYING },
	{ "STATE_PLAYPAUSE", (int)STATE_PLAYPAUSE },
	{ "STATE_FF", (int)STATE_FF },
	{ "STATE_FB", (int)STATE_FB },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMtRecChnnlTypeDescript[]={
	{ "TYPE_UNUSE", (int)TYPE_UNUSE },
	{ "TYPE_RECORD", (int)TYPE_RECORD },
	{ "TYPE_PLAY", (int)TYPE_PLAY },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMtRecModeDescript[]={
	{ "MODE_SKIPFRAME", (int)MODE_SKIPFRAME },
	{ "MODE_REALTIME", (int)MODE_REALTIME },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMtRecEnumDescript[]={
	{ "MT_MAXNUM_RECORDER_CHNNL", (int)MT_MAXNUM_RECORDER_CHNNL },
	{ "MT_MAXLEN_RECORD_NAME", (int)MT_MAXLEN_RECORD_NAME },
	{ "MT_MAXLEN_CONFNAME", (int)MT_MAXLEN_CONFNAME },
	{ "MT_RECLIST_PACKSIZE", (int)MT_RECLIST_PACKSIZE },
	{ "MT_MAX_REC_NAME", (int)MT_MAX_REC_NAME },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtRegResultDescript[]={
	{ "emMtRegSuccess", (int)emMtRegSuccess },
	{ "emMtRegPosError", (int)emMtRegPosError },
	{ "emMtRegTimeOut", (int)emMtRegTimeOut },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpRetDescript[]={
	{ "tp_Ret_FAILED", (int)tp_Ret_FAILED },
	{ "tp_Ret_Success", (int)tp_Ret_Success },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpHduPlayNackReasonDescript[]={
	{ "em_hdu_play_success", (int)em_hdu_play_success },
	{ "em_Hdu_Invalid_Index", (int)em_Hdu_Invalid_Index },
	{ "em_Hdu_Invalid_ID", (int)em_Hdu_Invalid_ID },
	{ "em_Hdu_No_Reged", (int)em_Hdu_No_Reged },
	{ "em_Hdu_Illegal", (int)em_Hdu_Illegal },
	{ "em_Alias_Illegal", (int)em_Alias_Illegal },
	{ "em_Monitor_Fail", (int)em_Monitor_Fail },
	{ "em_Hdu_PlayNack", (int)em_Hdu_PlayNack },
	{ "em_Same_Alias", (int)em_Same_Alias },
	{ "em_Same_Info", (int)em_Same_Info },
	{ "em_unknown", (int)em_unknown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpHduSetVolResDescript[]={
	{ "em_hdu_SetVol_Success", (int)em_hdu_SetVol_Success },
	{ "em_hdu_SetVol_Invalid_Index", (int)em_hdu_SetVol_Invalid_Index },
	{ "em_hdu_SetVol_UnReg", (int)em_hdu_SetVol_UnReg },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpLoginUmsRetDescript[]={
	{ "tp_LoginUms_sucess", (int)tp_LoginUms_sucess },
	{ "tp_LoginUms_NameError", (int)tp_LoginUms_NameError },
	{ "tp_LoginUms_PwdError", (int)tp_LoginUms_PwdError },
	{ "tp_LoginUms_MaxLogin", (int)tp_LoginUms_MaxLogin },
	{ "tp_LoginUms_Logged", (int)tp_LoginUms_Logged },
	{ "tp_LoginUms_SysIniting", (int)tp_LoginUms_SysIniting },
	{ "tp_LoginUms_steals_sucess", (int)tp_LoginUms_steals_sucess },
	{ "tp_LoginUms_steals_quit", (int)tp_LoginUms_steals_quit },
	{ "tp_LoginUms_locking", (int)tp_LoginUms_locking },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpAliasTypeDescript[]={
	{ "tp_Alias_Unknow", (int)tp_Alias_Unknow },
	{ "tp_Alias_e164", (int)tp_Alias_e164 },
	{ "tp_Alias_h323", (int)tp_Alias_h323 },
	{ "tp_Alias_IP", (int)tp_Alias_IP },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpOprTypeDescript[]={
	{ "tp_OprType_Add", (int)tp_OprType_Add },
	{ "tp_OprType_Del", (int)tp_OprType_Del },
	{ "tp_OprType_Update", (int)tp_OprType_Update },
	{ "tp_OprType_NULL", (int)tp_OprType_NULL },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmConfAddEpRetDescript[]={
	{ "TP_ConfAddEpRet_Unknow", (int)TP_ConfAddEpRet_Unknow },
	{ "TP_ConfAddEpRet_Success", (int)TP_ConfAddEpRet_Success },
	{ "TP_ConfAddEpRet_MaxNum", (int)TP_ConfAddEpRet_MaxNum },
	{ "TP_ConfAddEpRet_AliasReapeat", (int)TP_ConfAddEpRet_AliasReapeat },
	{ "TP_ConfAddEpRet_ParamError", (int)TP_ConfAddEpRet_ParamError },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpIFrameCheckTypeDescript[]={
	{ "TP_IFrameCheck_Speaker", (int)TP_IFrameCheck_Speaker },
	{ "TP_IFrameCheck_SingleSpeaker", (int)TP_IFrameCheck_SingleSpeaker },
	{ "TP_IFrameCheck_Poll", (int)TP_IFrameCheck_Poll },
	{ "TP_IFrameCheck_ChairWait", (int)TP_IFrameCheck_ChairWait },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPEncryptTypeDescript[]={
	{ "emTPEncryptTypeNone", (int)emTPEncryptTypeNone },
	{ "emTPEncryptTypeDES", (int)emTPEncryptTypeDES },
	{ "emTPEncryptTypeAES", (int)emTPEncryptTypeAES },
	{ "emTPEncryptTypeH239", (int)emTPEncryptTypeH239 },
	{ "emTPEncryptTypeQt", (int)emTPEncryptTypeQt },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmQtEncryptFrequencyDescript[]={
	{ "emQtFrequencyEverySeconds", (int)emQtFrequencyEverySeconds },
	{ "emQtFrequencyEveryMinutes", (int)emQtFrequencyEveryMinutes },
	{ "emQtFrequencyEveryConf", (int)emQtFrequencyEveryConf },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPQTReasonDescript[]={
	{ "emTPQtRetReason_Idle", (int)emTPQtRetReason_Idle },
	{ "emTPQtRetReason_Success", (int)emTPQtRetReason_Success },
	{ "emTPQtRetReason_Local", (int)emTPQtRetReason_Local },
	{ "emTPQtRetReason_DisConnect", (int)emTPQtRetReason_DisConnect },
	{ "emTPQtRetReason_ShakeFail", (int)emTPQtRetReason_ShakeFail },
	{ "emTPQtRetReason_ReqFail", (int)emTPQtRetReason_ReqFail },
	{ "emTPQtRetReason_GetFail", (int)emTPQtRetReason_GetFail },
	{ "emTPQtRetReason_PeerUnreach", (int)emTPQtRetReason_PeerUnreach },
	{ "emTPQtRetReason_PeerGetFail", (int)emTPQtRetReason_PeerGetFail },
	{ "emTPQtRetReason_ClearFail", (int)emTPQtRetReason_ClearFail },
	{ "emTPQtRetReason_TimeOut", (int)emTPQtRetReason_TimeOut },
	{ "emTPQtRetReason_NotMatch", (int)emTPQtRetReason_NotMatch },
	{ "emTPQtRetReason_MediaKeyFail", (int)emTPQtRetReason_MediaKeyFail },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPRcvAlignTypeDescript[]={
	{ "emTPRcvAlignTypeMidAlign", (int)emTPRcvAlignTypeMidAlign },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnsCallReasonDescript[]={
	{ "EmCnsCallReason_success", (int)EmCnsCallReason_success },
	{ "EmCnsCallReason_hungup", (int)EmCnsCallReason_hungup },
	{ "EmCnsCallReason_Unreachable", (int)EmCnsCallReason_Unreachable },
	{ "EmCnsCallReason_resourcefull", (int)EmCnsCallReason_resourcefull },
	{ "EmCnsCallReason_dstnotfind", (int)EmCnsCallReason_dstnotfind },
	{ "EmCnsCallReason_Busy", (int)EmCnsCallReason_Busy },
	{ "EmCnsCallReason_Local", (int)EmCnsCallReason_Local },
	{ "EmCnsCallReason_NoConf", (int)EmCnsCallReason_NoConf },
	{ "EmCnsCallReason_Exist", (int)EmCnsCallReason_Exist },
	{ "EmCnsCallReason_Rejected", (int)EmCnsCallReason_Rejected },
	{ "EmCnsCallReason_peerhungup", (int)EmCnsCallReason_peerhungup },
	{ "EmCnsCallReason_Abnormal", (int)EmCnsCallReason_Abnormal },
	{ "EmCnsCallReason_PeerAbnormal", (int)EmCnsCallReason_PeerAbnormal },
	{ "EmCnsCallReason_ConfOver", (int)EmCnsCallReason_ConfOver },
	{ "EmCnsCallReason_cncallexception", (int)EmCnsCallReason_cncallexception },
	{ "EmCnsCallReason_ConfExist", (int)EmCnsCallReason_ConfExist },
	{ "EmCnsCallReason_StreamEncryptFail", (int)EmCnsCallReason_StreamEncryptFail },
	{ "EmCnsCallReason_StreamEncryptKeyNotEqual", (int)EmCnsCallReason_StreamEncryptKeyNotEqual },
	{ "EmCnsCallReason_EncrypeErr", (int)EmCnsCallReason_EncrypeErr },
	{ "EmCnsCallReason_unknown", (int)EmCnsCallReason_unknown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPChannelReasonDescript[]={
	{ "emTPChannelReasonBegin", (int)emTPChannelReasonBegin },
	{ "emTPChannelDisconnectNormal", (int)emTPChannelDisconnectNormal },
	{ "emTPDualOffLine", (int)emTPDualOffLine },
	{ "emTPForceStop", (int)emTPForceStop },
	{ "emTPDualNotSend", (int)emTPDualNotSend },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCnsTypeDescript[]={
	{ "tp_CnsType_Unkonw", (int)tp_CnsType_Unkonw },
	{ "tp_CnsType_FiveScreen_FiveSpeeker", (int)tp_CnsType_FiveScreen_FiveSpeeker },
	{ "tp_CnsType_FiveScreen_ThreeSpeeker", (int)tp_CnsType_FiveScreen_ThreeSpeeker },
	{ "tp_CnsType_ThreeScreen_ThreeSpeeker", (int)tp_CnsType_ThreeScreen_ThreeSpeeker },
	{ "tp_CnsType_OneScreen_OneSpeeker", (int)tp_CnsType_OneScreen_OneSpeeker },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCnsRegUmsDescript[]={
	{ "tp_CnsRegRet_Unknow", (int)tp_CnsRegRet_Unknow },
	{ "tp_CnsRegRet_Success", (int)tp_CnsRegRet_Success },
	{ "tp_CnsRegRet_MaxRegNum", (int)tp_CnsRegRet_MaxRegNum },
	{ "tp_CnsRegRet_MaxAliasNum", (int)tp_CnsRegRet_MaxAliasNum },
	{ "tp_CnsRegRet_MsgError", (int)tp_CnsRegRet_MsgError },
	{ "tp_CnsRegRet_AliasRepeat", (int)tp_CnsRegRet_AliasRepeat },
	{ "tp_CnsRegRet_UnReg", (int)tp_CnsRegRet_UnReg },
	{ "tp_CnsRegRet_SysError", (int)tp_CnsRegRet_SysError },
	{ "tp_CnsRegRet_NotFind", (int)tp_CnsRegRet_NotFind },
	{ "tp_CnsRegRet_Fail", (int)tp_CnsRegRet_Fail },
	{ "tp_CnsRegRet_Unreachable", (int)tp_CnsRegRet_Unreachable },
	{ "tp_CnsRegRet_UnRegister", (int)tp_CnsRegRet_UnRegister },
	{ "tp_CnsRegRet_E164Repeat", (int)tp_CnsRegRet_E164Repeat },
	{ "tp_CnsRegRet_NameDup", (int)tp_CnsRegRet_NameDup },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpConfTemplateRetDescript[]={
	{ "TP_ConfTemplate_UnKonw", (int)TP_ConfTemplate_UnKonw },
	{ "TP_ConfTemplate_AddSuccess", (int)TP_ConfTemplate_AddSuccess },
	{ "TP_ConfTemplate_DelSuccess", (int)TP_ConfTemplate_DelSuccess },
	{ "TP_ConfTemplate_UpdateSuccess", (int)TP_ConfTemplate_UpdateSuccess },
	{ "TP_ConfTemplate_MaxNum", (int)TP_ConfTemplate_MaxNum },
	{ "TP_ConfTemplate_E164Repeat", (int)TP_ConfTemplate_E164Repeat },
	{ "TP_ConfTemplate_UnFindConf", (int)TP_ConfTemplate_UnFindConf },
	{ "TP_ConfTemplate_ParamInValid", (int)TP_ConfTemplate_ParamInValid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpStartConfRetDescript[]={
	{ "TP_StartConf_UnKonw", (int)TP_StartConf_UnKonw },
	{ "TP_StartConf_Success", (int)TP_StartConf_Success },
	{ "TP_StartConf_ConfTemplateUnExist", (int)TP_StartConf_ConfTemplateUnExist },
	{ "TP_StartConf_ConfFull", (int)TP_StartConf_ConfFull },
	{ "TP_StartConf_ConfExist", (int)TP_StartConf_ConfExist },
	{ "TP_StartConf_SipUnReg", (int)TP_StartConf_SipUnReg },
	{ "TP_StartConf_ResourceFull", (int)TP_StartConf_ResourceFull },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpApplySpeakerRetDescript[]={
	{ "TP_ApplySpeaker_Success", (int)TP_ApplySpeaker_Success },
	{ "TP_ApplySpeaker_ConfUnExist", (int)TP_ApplySpeaker_ConfUnExist },
	{ "TP_ApplySpeaker_EpIDError", (int)TP_ApplySpeaker_EpIDError },
	{ "TP_ApplySpeaker_EpStateError", (int)TP_ApplySpeaker_EpStateError },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpDropConfRetDescript[]={
	{ "TP_DropConf_Success", (int)TP_DropConf_Success },
	{ "TP_DropConf_ConfUnExit", (int)TP_DropConf_ConfUnExit },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpApplySpeakRetDescript[]={
	{ "TP_ApplySpeak_UnKonw", (int)TP_ApplySpeak_UnKonw },
	{ "TP_ApplySpeak_Success", (int)TP_ApplySpeak_Success },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmUmsConfNodeStateDescript[]={
	{ "ums_UmsConfNodeState_unused", (int)ums_UmsConfNodeState_unused },
	{ "ums_UmsConfNodeState_uncall", (int)ums_UmsConfNodeState_uncall },
	{ "ums_UmsConfNodeState_calling", (int)ums_UmsConfNodeState_calling },
	{ "ums_UmsConfNodeState_callfailed", (int)ums_UmsConfNodeState_callfailed },
	{ "ums_UmsConfNodeState_online", (int)ums_UmsConfNodeState_online },
	{ "ums_UmsConfNodeState_stopcall", (int)ums_UmsConfNodeState_stopcall },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFlowCtrlOprDescript[]={
	{ "emFlowCtrl_Speaker", (int)emFlowCtrl_Speaker },
	{ "emFlowCtrl_Chair", (int)emFlowCtrl_Chair },
	{ "emFlowCtrl_Poll", (int)emFlowCtrl_Poll },
	{ "emFlowCtrl_TvWall", (int)emFlowCtrl_TvWall },
	{ "emFlowCtrl_View", (int)emFlowCtrl_View },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMBrdTypeDescript[]={
	{ "em_unknow_brd", (int)em_unknow_brd },
	{ "em_eapu_brd", (int)em_eapu_brd },
	{ "em_mpc_brd", (int)em_mpc_brd },
	{ "em_mpu2ecard_brd", (int)em_mpu2ecard_brd },
	{ "em_hdu2_brd", (int)em_hdu2_brd },
	{ "em_is22_brd", (int)em_is22_brd },
	{ "em_cri2_brd", (int)em_cri2_brd },
	{ "em_mpu2_tp_brd", (int)em_mpu2_tp_brd },
	{ "em_apu2_tp_brd", (int)em_apu2_tp_brd },
	{ "em_mpu2basic_brd", (int)em_mpu2basic_brd },
	{ "em_brdtype_end", (int)em_brdtype_end },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMEqpTypeDescript[]={
	{ "em_unknow_mdl", (int)em_unknow_mdl },
	{ "em_adapter_mdl", (int)em_adapter_mdl },
	{ "em_dataswitch_mdl", (int)em_dataswitch_mdl },
	{ "em_netbuf_mdl", (int)em_netbuf_mdl },
	{ "em_audmix_mdl", (int)em_audmix_mdl },
	{ "em_mpc_mdl", (int)em_mpc_mdl },
	{ "em_bas_mdl", (int)em_bas_mdl },
	{ "em_vmp_mdl", (int)em_vmp_mdl },
	{ "em_hdu_mdl", (int)em_hdu_mdl },
	{ "em_regserver_mdl", (int)em_regserver_mdl },
	{ "em_recorder_mdl", (int)em_recorder_mdl },
	{ "em_vmp_tp_mdl", (int)em_vmp_tp_mdl },
	{ "em_audbas_mdl", (int)em_audbas_mdl },
	{ "em_max_mdl", (int)em_max_mdl },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMEqpModleTypeDescript[]={
	{ "em_unknow_eqp_mdl", (int)em_unknow_eqp_mdl },
	{ "em_bas_basic_eqp_mdl", (int)em_bas_basic_eqp_mdl },
	{ "em_bas_enhanced_eqp_mdl", (int)em_bas_enhanced_eqp_mdl },
	{ "em_vmp_basic_eqp_mdl", (int)em_vmp_basic_eqp_mdl },
	{ "em_vmp_enhanced_eqp_mdl", (int)em_vmp_enhanced_eqp_mdl },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMOsTypeDescript[]={
	{ "em_unknow_OsType", (int)em_unknow_OsType },
	{ "em_Win32_OsType", (int)em_Win32_OsType },
	{ "em_Linux_OsType", (int)em_Linux_OsType },
	{ "em_82xx_OsType", (int)em_82xx_OsType },
	{ "em_85xx_OsType", (int)em_85xx_OsType },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMVmpStyleDescript[]={
	{ "tp_VmpStyle_DYNAMIC", (int)tp_VmpStyle_DYNAMIC },
	{ "tp_VmpStyle_ONE", (int)tp_VmpStyle_ONE },
	{ "tp_VmpStyle_VTWO", (int)tp_VmpStyle_VTWO },
	{ "tp_VmpStyle_HTWO", (int)tp_VmpStyle_HTWO },
	{ "tp_VmpStyle_THREE", (int)tp_VmpStyle_THREE },
	{ "tp_VmpStyle_FOUR", (int)tp_VmpStyle_FOUR },
	{ "tp_VmpStyle_SIX", (int)tp_VmpStyle_SIX },
	{ "tp_VmpStyle_EIGHT", (int)tp_VmpStyle_EIGHT },
	{ "tp_VmpStyle_NINE", (int)tp_VmpStyle_NINE },
	{ "tp_VmpStyle_TEN", (int)tp_VmpStyle_TEN },
	{ "tp_VmpStyle_THIRTEEN", (int)tp_VmpStyle_THIRTEEN },
	{ "tp_VmpStyle_SIXTEEN", (int)tp_VmpStyle_SIXTEEN },
	{ "tp_VmpStyle_SPECFOUR", (int)tp_VmpStyle_SPECFOUR },
	{ "tp_VmpStyle_SEVEN", (int)tp_VmpStyle_SEVEN },
	{ "tp_VmpStyle_TWENTY", (int)tp_VmpStyle_TWENTY },
	{ "tp_VmpStyle_TEN_H", (int)tp_VmpStyle_TEN_H },
	{ "tp_VmpStyle_SIX_L2UP_S4DOWN", (int)tp_VmpStyle_SIX_L2UP_S4DOWN },
	{ "tp_VmpStyle_FOURTEEN", (int)tp_VmpStyle_FOURTEEN },
	{ "tp_VmpStyle_TEN_M", (int)tp_VmpStyle_TEN_M },
	{ "tp_VmpStyle_THIRTEEN_M", (int)tp_VmpStyle_THIRTEEN_M },
	{ "tp_VmpStyle_FIFTEEN", (int)tp_VmpStyle_FIFTEEN },
	{ "tp_VmpStyle_SIX_DIVIDE", (int)tp_VmpStyle_SIX_DIVIDE },
	{ "tp_VmpStyle_leftBig", (int)tp_VmpStyle_leftBig },
	{ "tp_VmpStyle_MidBig", (int)tp_VmpStyle_MidBig },
	{ "tp_VmpStyle_RightBig", (int)tp_VmpStyle_RightBig },
	{ "tp_VmpStyle_3VERTICAL", (int)tp_VmpStyle_3VERTICAL },
	{ "tp_VmpStyle_FOUR_3BOTTOMMIDDLE", (int)tp_VmpStyle_FOUR_3BOTTOMMIDDLE },
	{ "tp_VmpStyle_TWENTYFIVE", (int)tp_VmpStyle_TWENTYFIVE },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpVideoFormatDescript[]={
	{ "emTPVH261", (int)emTPVH261 },
	{ "emTPVH262", (int)emTPVH262 },
	{ "emTPVH263", (int)emTPVH263 },
	{ "emTPVH263plus", (int)emTPVH263plus },
	{ "emTPVH264", (int)emTPVH264 },
	{ "emTPVMPEG4", (int)emTPVMPEG4 },
	{ "emTPVH265", (int)emTPVH265 },
	{ "emTPVEnd", (int)emTPVEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpEncodeModeDescript[]={
	{ "emTPQualityFirst", (int)emTPQualityFirst },
	{ "emTPSpeedFirst", (int)emTPSpeedFirst },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpVideoQualityLevelDescript[]={
	{ "emTPH264BP", (int)emTPH264BP },
	{ "emTPH264HP", (int)emTPH264HP },
	{ "emTPH265ProfileMain", (int)emTPH265ProfileMain },
	{ "emTPH265ProfileMain10", (int)emTPH265ProfileMain10 },
	{ "emTPH265ProfileMainStill", (int)emTPH265ProfileMainStill },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCallLevelDescript[]={
	{ "emTpCallLevelUnknown", (int)emTpCallLevelUnknown },
	{ "emTPCallLevelFirst", (int)emTPCallLevelFirst },
	{ "emTPCallLevelSecond", (int)emTPCallLevelSecond },
	{ "emTpCallLevelThird", (int)emTpCallLevelThird },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpVideoResolutionDescript[]={
	{ "emTPVResolutionAuto", (int)emTPVResolutionAuto },
	{ "emTPVSQCIF", (int)emTPVSQCIF },
	{ "emTPVQCIF", (int)emTPVQCIF },
	{ "emTPVCIF", (int)emTPVCIF },
	{ "emTPV2CIF", (int)emTPV2CIF },
	{ "emTPV4CIF", (int)emTPV4CIF },
	{ "emTPV16CIF", (int)emTPV16CIF },
	{ "emTPVHD480i720x480", (int)emTPVHD480i720x480 },
	{ "emTPVHD480p720x480", (int)emTPVHD480p720x480 },
	{ "emTPVHD576i720x576", (int)emTPVHD576i720x576 },
	{ "emTPVHD576p720x576", (int)emTPVHD576p720x576 },
	{ "emTPVHD720p1280x720", (int)emTPVHD720p1280x720 },
	{ "emTPVHD1080i1920x1080", (int)emTPVHD1080i1920x1080 },
	{ "emTPVHD1080p1920x1080", (int)emTPVHD1080p1920x1080 },
	{ "emTPVGA352x240", (int)emTPVGA352x240 },
	{ "emTPVGA704x480", (int)emTPVGA704x480 },
	{ "emTPVGA640x480", (int)emTPVGA640x480 },
	{ "emTPVGA800x600", (int)emTPVGA800x600 },
	{ "emTPVGA1024x768", (int)emTPVGA1024x768 },
	{ "emTPVGA1280x768", (int)emTPVGA1280x768 },
	{ "emTPVGA1280x800", (int)emTPVGA1280x800 },
	{ "emTPVGA1366x768", (int)emTPVGA1366x768 },
	{ "emTPVGA1280x854", (int)emTPVGA1280x854 },
	{ "emTPVGA1440x900", (int)emTPVGA1440x900 },
	{ "emTPVGA1280x1024", (int)emTPVGA1280x1024 },
	{ "emTPVGA1680x1050", (int)emTPVGA1680x1050 },
	{ "emTPVGA1600x1200", (int)emTPVGA1600x1200 },
	{ "emTPVGA1920x1200", (int)emTPVGA1920x1200 },
	{ "emTPVSQCIF112x96", (int)emTPVSQCIF112x96 },
	{ "emTPVSQCIF96x80", (int)emTPVSQCIF96x80 },
	{ "emTPV320x192", (int)emTPV320x192 },
	{ "emTPV432x240", (int)emTPV432x240 },
	{ "emTPV480x272", (int)emTPV480x272 },
	{ "emTPV640x368", (int)emTPV640x368 },
	{ "emTPV864x480", (int)emTPV864x480 },
	{ "emTPV960x544", (int)emTPV960x544 },
	{ "emTPV1440x816", (int)emTPV1440x816 },
	{ "emTPW4CIF1024x576", (int)emTPW4CIF1024x576 },
	{ "emTPVRes2Kx1K", (int)emTPVRes2Kx1K },
	{ "emTPVRes2Kx1080", (int)emTPVRes2Kx1080 },
	{ "emTPVRes4XGA", (int)emTPVRes4XGA },
	{ "emTPVRes16VGA", (int)emTPVRes16VGA },
	{ "emTPVRes3616x1536", (int)emTPVRes3616x1536 },
	{ "emTPVRes3672x1536", (int)emTPVRes3672x1536 },
	{ "emTPVRes3840x2160", (int)emTPVRes3840x2160 },
	{ "emTPVRes4Kx2K", (int)emTPVRes4Kx2K },
	{ "emTPVRes4096x2160", (int)emTPVRes4096x2160 },
	{ "emTPVRes4096x2304", (int)emTPVRes4096x2304 },
	{ "emTPVRes7680x4320", (int)emTPVRes7680x4320 },
	{ "emTPVRes8192x4096", (int)emTPVRes8192x4096 },
	{ "emTPVRes8192x4320", (int)emTPVRes8192x4320 },
	{ "emTPWCIF", (int)emTPWCIF },
	{ "emTPVResEnd", (int)emTPVResEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpMediaTypeDescript[]={
	{ "emTPMediaVideo", (int)emTPMediaVideo },
	{ "emTPMediaAudio", (int)emTPMediaAudio },
	{ "emTPMediaAV", (int)emTPMediaAV },
	{ "emTPMediaMerge", (int)emTPMediaMerge },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpPCCapFormatDescript[]={
	{ "emTPCapPCFrameBMP", (int)emTPCapPCFrameBMP },
	{ "emTPCapPCFrameUYUY", (int)emTPCapPCFrameUYUY },
	{ "emTPCapPCFrameI420", (int)emTPCapPCFrameI420 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCodecComponentDescript[]={
	{ "emTPPriomVideoEncoder", (int)emTPPriomVideoEncoder },
	{ "emTPPriomVideoDecoder", (int)emTPPriomVideoDecoder },
	{ "emTPSecondVideoEncoder", (int)emTPSecondVideoEncoder },
	{ "emTPSecondVideoDecoder", (int)emTPSecondVideoDecoder },
	{ "emTPAudioEncoder", (int)emTPAudioEncoder },
	{ "emTPAudioDecoder", (int)emTPAudioDecoder },
	{ "emTPSecondAudioEncoder", (int)emTPSecondAudioEncoder },
	{ "emTPSecondAudioDecoder", (int)emTPSecondAudioDecoder },
	{ "emTPPriomLeftVideoDecoder", (int)emTPPriomLeftVideoDecoder },
	{ "emTPPriomRightVideoDecoder", (int)emTPPriomRightVideoDecoder },
	{ "emTPMiniVideoEncoder", (int)emTPMiniVideoEncoder },
	{ "emTPMergeVideoEncoder", (int)emTPMergeVideoEncoder },
	{ "emTPCodecComponentEnd", (int)emTPCodecComponentEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpAudioFormatDescript[]={
	{ "emTPAG711a", (int)emTPAG711a },
	{ "emTPAG711u", (int)emTPAG711u },
	{ "emTPAG722", (int)emTPAG722 },
	{ "emTPAG7231", (int)emTPAG7231 },
	{ "emTPAG728", (int)emTPAG728 },
	{ "emTPAG729", (int)emTPAG729 },
	{ "emTPAMP3", (int)emTPAMP3 },
	{ "emTPAG721", (int)emTPAG721 },
	{ "emTPAG7221", (int)emTPAG7221 },
	{ "emTPAG719", (int)emTPAG719 },
	{ "emTPAMpegAACLC", (int)emTPAMpegAACLC },
	{ "emTPAMpegAACLD", (int)emTPAMpegAACLD },
	{ "emTPAEnd", (int)emTPAEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpLostPackageRestoreDescript[]={
	{ "emTPLPQualityFirst", (int)emTPLPQualityFirst },
	{ "emTPLPSpeedSlow", (int)emTPLPSpeedSlow },
	{ "emTPLPSpeedNormal", (int)emTPLPSpeedNormal },
	{ "emTPLPSpeedFast", (int)emTPLPSpeedFast },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCallModeDescript[]={
	{ "emTpJoin", (int)emTpJoin },
	{ "emTpCreate", (int)emTpCreate },
	{ "emTpInvite", (int)emTpInvite },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpConnectionTypeDescript[]={
	{ "emTPConnectionBegin", (int)emTPConnectionBegin },
	{ "emTPTCPConnection", (int)emTPTCPConnection },
	{ "emTPUDPConnection", (int)emTPUDPConnection },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpConfProtocolDescript[]={
	{ "emTpInvalidConfProtocel", (int)emTpInvalidConfProtocel },
	{ "emTpH323", (int)emTpH323 },
	{ "emTpH320", (int)emTpH320 },
	{ "emTpSIP", (int)emTpSIP },
	{ "emTpSat", (int)emTpSat },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAddrTypeDescript[]={
	{ "emTpUnknown", (int)emTpUnknown },
	{ "emTpIPAddr", (int)emTpIPAddr },
	{ "emTpDomain", (int)emTpDomain },
	{ "emTpAlias", (int)emTpAlias },
	{ "emTpE164Num", (int)emTpE164Num },
	{ "emTpIP6Addr", (int)emTpIP6Addr },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPEndpointTypeDescript[]={
	{ "emTPEndpointTypeUnknown", (int)emTPEndpointTypeUnknown },
	{ "emTPEndpointTypeCNS", (int)emTPEndpointTypeCNS },
	{ "emTPEndpointTypeUMS", (int)emTPEndpointTypeUMS },
	{ "emTPEndpointTypeRegister", (int)emTPEndpointTypeRegister },
	{ "emTPEndpointH323MT", (int)emTPEndpointH323MT },
	{ "emTPEndpointH323MCU", (int)emTPEndpointH323MCU },
	{ "emTPEndpointH323SingleMCU", (int)emTPEndpointH323SingleMCU },
	{ "emTPEndpointH323G400", (int)emTPEndpointH323G400 },
	{ "emTPEndpointTypeVRS", (int)emTPEndpointTypeVRS },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPSipLevelDescript[]={
	{ "emTPSipCounty", (int)emTPSipCounty },
	{ "emTPSipCity", (int)emTPSipCity },
	{ "emTPSipProvince", (int)emTPSipProvince },
	{ "emTPSipUnKnown", (int)emTPSipUnKnown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCALLSTATEDescript[]={
	{ "em_CALL_IDLE", (int)em_CALL_IDLE },
	{ "em_CALL_CALLING", (int)em_CALL_CALLING },
	{ "em_CALL_CONNECTED", (int)em_CALL_CONNECTED },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCallTypeDescript[]={
	{ "emCallType_Invalid", (int)emCallType_Invalid },
	{ "emCallType_P2P", (int)emCallType_P2P },
	{ "emCallType_Conf", (int)emCallType_Conf },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPVideoTypeDescript[]={
	{ "emTpPriomVideo", (int)emTpPriomVideo },
	{ "emTpMiniVideo", (int)emTpMiniVideo },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPVideoPortDescript[]={
	{ "emTpVGA", (int)emTpVGA },
	{ "emTpSVid", (int)emTpSVid },
	{ "emTpPC", (int)emTpPC },
	{ "emTpC1Vid", (int)emTpC1Vid },
	{ "emTpC2Vid", (int)emTpC2Vid },
	{ "emTpC3Vid", (int)emTpC3Vid },
	{ "emTpC4Vid", (int)emTpC4Vid },
	{ "emTpC5Vid", (int)emTpC5Vid },
	{ "emTpC6Vid", (int)emTpC6Vid },
	{ "emTpExternalVid", (int)emTpExternalVid },
	{ "emTpVideoMaxCount", (int)emTpVideoMaxCount },
	{ "emTpVidInvalid", (int)emTpVidInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPCNSInfoRstDescript[]={
	{ "emTPCNSInfoSuccess", (int)emTPCNSInfoSuccess },
	{ "emTPCNSRepeatE164", (int)emTPCNSRepeatE164 },
	{ "emTPCNSRepeatAliasName", (int)emTPCNSRepeatAliasName },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPRegResultDescript[]={
	{ "emTPRegResultBegin", (int)emTPRegResultBegin },
	{ "emTPRegResultReg", (int)emTPRegResultReg },
	{ "emTPRegResultUnReg", (int)emTPRegResultUnReg },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnMtRegResultDescript[]={
	{ "emCnMtSuccess", (int)emCnMtSuccess },
	{ "emCnMtPosError", (int)emCnMtPosError },
	{ "emCnMtTimeOut", (int)emCnMtTimeOut },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnModelDescript[]={
	{ "emUnknownCnModel", (int)emUnknownCnModel },
	{ "em7920", (int)em7920 },
	{ "T300", (int)T300 },
	{ "T300E", (int)T300E },
	{ "T300E_CS", (int)T300E_CS },
	{ "T300E_4K", (int)T300E_4K },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFocusModeDescript[]={
	{ "emFocusAuto", (int)emFocusAuto },
	{ "emFocusManuel", (int)emFocusManuel },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSensitivityDescript[]={
	{ "emHigh", (int)emHigh },
	{ "emMedium", (int)emMedium },
	{ "emLow", (int)emLow },
	{ "emUltraLow", (int)emUltraLow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFocusDescript[]={
	{ "emFar", (int)emFar },
	{ "emNear", (int)emNear },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmZoomDescript[]={
	{ "emTele", (int)emTele },
	{ "emWide", (int)emWide },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmZoomStatusDescript[]={
	{ "emStart", (int)emStart },
	{ "emStop", (int)emStop },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnActionDescript[]={
	{ "emCnStart", (int)emCnStart },
	{ "emCnStop", (int)emCnStop },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmOSDShowDescript[]={
	{ "emOSDOff", (int)emOSDOff },
	{ "emOSDOn", (int)emOSDOn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWBModeDescript[]={
	{ "emWBAuto", (int)emWBAuto },
	{ "emWBManual", (int)emWBManual },
	{ "emOnePush", (int)emOnePush },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmExpModeDescript[]={
	{ "emExpAuto", (int)emExpAuto },
	{ "emExpManuel", (int)emExpManuel },
	{ "emShutterPriority", (int)emShutterPriority },
	{ "emIrisPriority", (int)emIrisPriority },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGainDescript[]={
	{ "em0dB", (int)em0dB },
	{ "em3dB", (int)em3dB },
	{ "em6dB", (int)em6dB },
	{ "em9dB", (int)em9dB },
	{ "em12dB", (int)em12dB },
	{ "em15dB", (int)em15dB },
	{ "em18dB", (int)em18dB },
	{ "em21dB", (int)em21dB },
	{ "em24dB", (int)em24dB },
	{ "em27dB", (int)em27dB },
	{ "em30dB", (int)em30dB },
	{ "em33dB", (int)em33dB },
	{ "em36dB", (int)em36dB },
	{ "em39dB", (int)em39dB },
	{ "em42dB", (int)em42dB },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmShutSpdDescript[]={
	{ "emShutSpd0", (int)emShutSpd0 },
	{ "emShutSpd1", (int)emShutSpd1 },
	{ "emShutSpd2", (int)emShutSpd2 },
	{ "emShutSpd3", (int)emShutSpd3 },
	{ "emShutSpd4", (int)emShutSpd4 },
	{ "emShutSpd5", (int)emShutSpd5 },
	{ "emShutSpd6", (int)emShutSpd6 },
	{ "emShutSpd7", (int)emShutSpd7 },
	{ "emShutSpd8", (int)emShutSpd8 },
	{ "emShutSpd9", (int)emShutSpd9 },
	{ "emShutSpdA", (int)emShutSpdA },
	{ "emShutSpdB", (int)emShutSpdB },
	{ "emShutSpdC", (int)emShutSpdC },
	{ "emShutSpdD", (int)emShutSpdD },
	{ "emShutSpdE", (int)emShutSpdE },
	{ "emShutSpdF", (int)emShutSpdF },
	{ "emShutSpd10", (int)emShutSpd10 },
	{ "emShutSpd11", (int)emShutSpd11 },
	{ "emShutSpd12", (int)emShutSpd12 },
	{ "emShutSpd13", (int)emShutSpd13 },
	{ "emShutSpd14", (int)emShutSpd14 },
	{ "emShutSpd15", (int)emShutSpd15 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAntiFlickerDescript[]={
	{ "emAntiFlickerOff", (int)emAntiFlickerOff },
	{ "emAntiFlicker50Hz", (int)emAntiFlicker50Hz },
	{ "emAntiFlicker60Hz", (int)emAntiFlicker60Hz },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSpotLighetDescript[]={
	{ "emSpotLighetOff", (int)emSpotLighetOff },
	{ "emSpotLighetOn", (int)emSpotLighetOn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmBackLightTypeDescript[]={
	{ "emBLOff", (int)emBLOff },
	{ "emBLmulti", (int)emBLmulti },
	{ "emBLcenter", (int)emBLcenter },
	{ "emBLfacedetect", (int)emBLfacedetect },
	{ "emBLAuto", (int)emBLAuto },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWideDynamicsDescript[]={
	{ "emWDROff", (int)emWDROff },
	{ "emWDROn", (int)emWDROn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPicSceModeDescript[]={
	{ "emLamp", (int)emLamp },
	{ "emSun", (int)emSun },
	{ "emManuel", (int)emManuel },
	{ "emPicSceStandard", (int)emPicSceStandard },
	{ "emPicSceProjector", (int)emPicSceProjector },
	{ "emPicScePeopleFeature", (int)emPicScePeopleFeature },
	{ "emPeopleBacklight", (int)emPeopleBacklight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGammaDescript[]={
	{ "emGammaOff", (int)emGammaOff },
	{ "emGammaOn", (int)emGammaOn },
	{ "emSmart1", (int)emSmart1 },
	{ "emSmart2", (int)emSmart2 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmStmCleanDescript[]={
	{ "emNRoff", (int)emNRoff },
	{ "emNRlow", (int)emNRlow },
	{ "emNRmid", (int)emNRmid },
	{ "emNRhigh", (int)emNRhigh },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEm3DNRDescript[]={
	{ "em3DNROff", (int)em3DNROff },
	{ "em3DNROn", (int)em3DNROn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPicEffectDescript[]={
	{ "emEffectOff", (int)emEffectOff },
	{ "emEffectOn", (int)emEffectOn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPicFlipDescript[]={
	{ "emCloseFlip", (int)emCloseFlip },
	{ "emHorizontalFlip", (int)emHorizontalFlip },
	{ "emVerticalFlip", (int)emVerticalFlip },
	{ "emBothFlip", (int)emBothFlip },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPicModeDescript[]={
	{ "emPicStandard", (int)emPicStandard },
	{ "emPicBright", (int)emPicBright },
	{ "emPicSoftLight", (int)emPicSoftLight },
	{ "emPicManual", (int)emPicManual },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmResolutionDescript[]={
	{ "emImage4K2Kp60", (int)emImage4K2Kp60 },
	{ "emImage4K2Kp50", (int)emImage4K2Kp50 },
	{ "emImage4K2Kp30", (int)emImage4K2Kp30 },
	{ "emImage4K2Kp25", (int)emImage4K2Kp25 },
	{ "emImage4K2Kp24", (int)emImage4K2Kp24 },
	{ "emImage1080P60", (int)emImage1080P60 },
	{ "emImage1080P50", (int)emImage1080P50 },
	{ "emImage1080P30", (int)emImage1080P30 },
	{ "emImage1080P25", (int)emImage1080P25 },
	{ "emImage1080I60", (int)emImage1080I60 },
	{ "emImage1080I50", (int)emImage1080I50 },
	{ "emImage720P60", (int)emImage720P60 },
	{ "emImage720P50", (int)emImage720P50 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmBaudRateDescript[]={
	{ "emBaudRate2400", (int)emBaudRate2400 },
	{ "emBaudRate4800", (int)emBaudRate4800 },
	{ "emBaudRate9600", (int)emBaudRate9600 },
	{ "emBaudRate38400", (int)emBaudRate38400 },
	{ "emBaudRate115200", (int)emBaudRate115200 },
	{ "emBaudRate230400", (int)emBaudRate230400 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCamPowerModeDescript[]={
	{ "emCamPowerOn", (int)emCamPowerOn },
	{ "emCamPowerOff", (int)emCamPowerOff },
	{ "emCamPowerDowm", (int)emCamPowerDowm },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCenSchModeDescript[]={
	{ "emSchSleep", (int)emSchSleep },
	{ "emSchWakeup", (int)emSchWakeup },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSonyIrisDescript[]={
	{ "emIrisOFF", (int)emIrisOFF },
	{ "emIrisF9_6", (int)emIrisF9_6 },
	{ "emIrisF8", (int)emIrisF8 },
	{ "emIrisF6_8", (int)emIrisF6_8 },
	{ "emIrisF5_6", (int)emIrisF5_6 },
	{ "emIrisF4_8", (int)emIrisF4_8 },
	{ "emIrisF4", (int)emIrisF4 },
	{ "emIrisF3_4", (int)emIrisF3_4 },
	{ "emIrisF2_8", (int)emIrisF2_8 },
	{ "emIrisF2_4", (int)emIrisF2_4 },
	{ "emIrisF2", (int)emIrisF2 },
	{ "emIrisF1_8", (int)emIrisF1_8 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMoon904K60IrisDescript[]={
	{ "emM904kIrisOFF", (int)emM904kIrisOFF },
	{ "emM904kIrisF1_6", (int)emM904kIrisF1_6 },
	{ "emM904kIrisF1_8", (int)emM904kIrisF1_8 },
	{ "emM904kIrisF2_0", (int)emM904kIrisF2_0 },
	{ "emM904kIrisF2_4", (int)emM904kIrisF2_4 },
	{ "emM904kIrisF2_8", (int)emM904kIrisF2_8 },
	{ "emM904kIrisF3_4", (int)emM904kIrisF3_4 },
	{ "emM904kIrisF4_0", (int)emM904kIrisF4_0 },
	{ "emM904kIrisF4_8", (int)emM904kIrisF4_8 },
	{ "emM904kIrisF5_6", (int)emM904kIrisF5_6 },
	{ "emM904kIrisF6_8", (int)emM904kIrisF6_8 },
	{ "emM904kIrisF8_0", (int)emM904kIrisF8_0 },
	{ "emM904kIrisF9_6", (int)emM904kIrisF9_6 },
	{ "emM904kIrisF11", (int)emM904kIrisF11 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCamTypeDescript[]={
	{ "emCamHD95D", (int)emCamHD95D },
	{ "emCamSony", (int)emCamSony },
	{ "emCamMoon904K60", (int)emCamMoon904K60 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCamCfgTypeDescript[]={
	{ "emCfgSensitivity", (int)emCfgSensitivity },
	{ "emCfgGainValue", (int)emCfgGainValue },
	{ "emCfgGainLimit", (int)emCfgGainLimit },
	{ "emCfgAntiFlicker", (int)emCfgAntiFlicker },
	{ "emCfgSpotLight", (int)emCfgSpotLight },
	{ "emCfgSpotLighetPos", (int)emCfgSpotLighetPos },
	{ "emCfgExposureComp", (int)emCfgExposureComp },
	{ "emCfgBackLight", (int)emCfgBackLight },
	{ "emCfgBackLightLevel", (int)emCfgBackLightLevel },
	{ "emCfgWDR", (int)emCfgWDR },
	{ "emCfgWDRLevel", (int)emCfgWDRLevel },
	{ "emCfgColorTemperature", (int)emCfgColorTemperature },
	{ "emCfgPicEffect", (int)emCfgPicEffect },
	{ "emCfgPicFlip", (int)emCfgPicFlip },
	{ "emCfgPicMode", (int)emCfgPicMode },
	{ "emCfgPicSharpness", (int)emCfgPicSharpness },
	{ "emCfgPicGamma", (int)emCfgPicGamma },
	{ "emCfgPic2DNR", (int)emCfgPic2DNR },
	{ "emCfgPic3DNR", (int)emCfgPic3DNR },
	{ "emCfgCamResolution", (int)emCfgCamResolution },
	{ "emCfgCamBaudRate", (int)emCfgCamBaudRate },
	{ "emCfgCamNet", (int)emCfgCamNet },
	{ "emCfgCamPersetReset", (int)emCfgCamPersetReset },
	{ "emCfgCamPersetSet", (int)emCfgCamPersetSet },
	{ "emCfgCamPersetCall", (int)emCfgCamPersetCall },
	{ "emCfgCamStartUpPerset", (int)emCfgCamStartUpPerset },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTvPowerModeDescript[]={
	{ "emTVPowerOFF", (int)emTVPowerOFF },
	{ "emTVPowerON", (int)emTVPowerON },
	{ "emTVPowerDown", (int)emTVPowerDown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTvSrcPowerModeDescript[]={
	{ "emTVSrcPowerOFF", (int)emTVSrcPowerOFF },
	{ "emTVSrcPowerON", (int)emTVSrcPowerON },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTVAudVisModeDescript[]={
	{ "emTVAVStandardMode", (int)emTVAVStandardMode },
	{ "emTVAVMovieMode", (int)emTVAVMovieMode },
	{ "emTVAVUserMode", (int)emTVAVUserMode },
	{ "emTVAVComputerMode", (int)emTVAVComputerMode },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTVDisplayModeDescript[]={
	{ "emTVDisFullScrMode", (int)emTVDisFullScrMode },
	{ "emTVDisPanoramaMode", (int)emTVDisPanoramaMode },
	{ "emTVDisPointMode", (int)emTVDisPointMode },
	{ "emTVDisStandardMode", (int)emTVDisStandardMode },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTVInputSelectDescript[]={
	{ "emTVHDMI1", (int)emTVHDMI1 },
	{ "emTVHDMI2", (int)emTVHDMI2 },
	{ "emTVHDMI3", (int)emTVHDMI3 },
	{ "emTVHDMI4", (int)emTVHDMI4 },
	{ "emTVYpbPr", (int)emTVYpbPr },
	{ "emTVCVBS1", (int)emTVCVBS1 },
	{ "emTVCVBS2", (int)emTVCVBS2 },
	{ "emTVComputer", (int)emTVComputer },
	{ "emTVVGA", (int)emTVVGA },
	{ "emTVDVI", (int)emTVDVI },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamWBModeDescript[]={
	{ "emDcamWBAuto", (int)emDcamWBAuto },
	{ "emDCamWBManual", (int)emDCamWBManual },
	{ "emDCamOnePush", (int)emDCamOnePush },
	{ "emDCamWBInvalid", (int)emDCamWBInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamAFModeDescript[]={
	{ "emDcamAFOff", (int)emDcamAFOff },
	{ "emDCamAFOn", (int)emDCamAFOn },
	{ "emDCamAFToggle", (int)emDCamAFToggle },
	{ "emDCamAFInvalid", (int)emDCamAFInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamPowerDescript[]={
	{ "emDCamPowerOff", (int)emDCamPowerOff },
	{ "emDCamPowerOn", (int)emDCamPowerOn },
	{ "emDCamPowerToggle", (int)emDCamPowerToggle },
	{ "emDCamPowerDown", (int)emDCamPowerDown },
	{ "emDCamPowerInvalid", (int)emDCamPowerInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamZoomDescript[]={
	{ "emDCamZoomWide", (int)emDCamZoomWide },
	{ "emDCamZoomTele", (int)emDCamZoomTele },
	{ "emDCamZoomInvalid", (int)emDCamZoomInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamPresetNumDescript[]={
	{ "emDCamPresetOne", (int)emDCamPresetOne },
	{ "emDCamPresetTwo", (int)emDCamPresetTwo },
	{ "emDCamPresetThree", (int)emDCamPresetThree },
	{ "emDCamPresetInvalid", (int)emDCamPresetInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamRecallNumDescript[]={
	{ "emDCamRecallOne", (int)emDCamRecallOne },
	{ "emDCamRecallTwo", (int)emDCamRecallTwo },
	{ "emDCamRecallThree", (int)emDCamRecallThree },
	{ "emDCamRecallInvalid", (int)emDCamRecallInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamGainDescript[]={
	{ "emN10_5dB", (int)emN10_5dB },
	{ "emN9dB", (int)emN9dB },
	{ "emN7_5dB", (int)emN7_5dB },
	{ "emN6dB", (int)emN6dB },
	{ "emN4_5dB", (int)emN4_5dB },
	{ "emN3dB", (int)emN3dB },
	{ "emN1_5dB", (int)emN1_5dB },
	{ "emD0dB", (int)emD0dB },
	{ "emP1_5dB", (int)emP1_5dB },
	{ "emP3dB", (int)emP3dB },
	{ "emP4_5dB", (int)emP4_5dB },
	{ "emP6dB", (int)emP6dB },
	{ "emP7_5dB", (int)emP7_5dB },
	{ "emP9dB", (int)emP9dB },
	{ "emP10_5dB", (int)emP10_5dB },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamShutSpdDescript[]={
	{ "emDShutSpd0", (int)emDShutSpd0 },
	{ "emDShutSpd1", (int)emDShutSpd1 },
	{ "emDShutSpd2", (int)emDShutSpd2 },
	{ "emDShutSpd3", (int)emDShutSpd3 },
	{ "emDShutSpd4", (int)emDShutSpd4 },
	{ "emDShutSpd5", (int)emDShutSpd5 },
	{ "emDShutSpd6", (int)emDShutSpd6 },
	{ "emDShutSpd7", (int)emDShutSpd7 },
	{ "emDShutSpd8", (int)emDShutSpd8 },
	{ "emDShutSpd9", (int)emDShutSpd9 },
	{ "emDShutSpdA", (int)emDShutSpdA },
	{ "emDShutSpdB", (int)emDShutSpdB },
	{ "emDShutSpdC", (int)emDShutSpdC },
	{ "emDShutSpdD", (int)emDShutSpdD },
	{ "emDShutSpdE", (int)emDShutSpdE },
	{ "emDShutSpdF", (int)emDShutSpdF },
	{ "emDShutSpd10", (int)emDShutSpd10 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamIrisDescript[]={
	{ "emDIrisClose", (int)emDIrisClose },
	{ "emDIrisF14", (int)emDIrisF14 },
	{ "emDIrisF11", (int)emDIrisF11 },
	{ "emDIrisF9_6", (int)emDIrisF9_6 },
	{ "emDIrisF8", (int)emDIrisF8 },
	{ "emDIrisF6_8", (int)emDIrisF6_8 },
	{ "emDIrisF5_6", (int)emDIrisF5_6 },
	{ "emDIrisF4_8", (int)emDIrisF4_8 },
	{ "emDIrisF4", (int)emDIrisF4 },
	{ "emDIrisF3_4", (int)emDIrisF3_4 },
	{ "emDIrisF2_8", (int)emDIrisF2_8 },
	{ "emDIrisF2_4", (int)emDIrisF2_4 },
	{ "emDIrisF2", (int)emDIrisF2 },
	{ "emDIrisF1_6", (int)emDIrisF1_6 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchPowerDescript[]={
	{ "emSchPowerOff", (int)emSchPowerOff },
	{ "emSchPowerOn", (int)emSchPowerOn },
	{ "emSchPowerToggle", (int)emSchPowerToggle },
	{ "emSchPowerInvalid", (int)emSchPowerInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchLightDescript[]={
	{ "emSchLightOff", (int)emSchLightOff },
	{ "emSchLightOn", (int)emSchLightOn },
	{ "emSchLightInvalid", (int)emSchLightInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchMidLightDescript[]={
	{ "emSchMidLightOff", (int)emSchMidLightOff },
	{ "emSchMidLightOn", (int)emSchMidLightOn },
	{ "emSchMidLightInvalid", (int)emSchMidLightInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchScrLightDescript[]={
	{ "emSchScrLightOff", (int)emSchScrLightOff },
	{ "emSchScrLightOn", (int)emSchScrLightOn },
	{ "emSchScrLightInvalid", (int)emSchScrLightInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchCameraAndTVPowerDescript[]={
	{ "emPowerOff", (int)emPowerOff },
	{ "emPowerOn", (int)emPowerOn },
	{ "emPowerInvalid", (int)emPowerInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchArgusDescript[]={
	{ "emSchArgusUnlock", (int)emSchArgusUnlock },
	{ "emSchArgusLock", (int)emSchArgusLock },
	{ "emSchArgusInvalid", (int)emSchArgusInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCentreACPowerDescript[]={
	{ "emCenACPowerOff", (int)emCenACPowerOff },
	{ "emCenACPowerOn", (int)emCenACPowerOn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCentreACAirVolDescript[]={
	{ "emCenACVolAuto", (int)emCenACVolAuto },
	{ "emCenACVol1", (int)emCenACVol1 },
	{ "emCenACVol2", (int)emCenACVol2 },
	{ "emCenACVol3", (int)emCenACVol3 },
	{ "emCenACVol4", (int)emCenACVol4 },
	{ "emCenACVol5", (int)emCenACVol5 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCentreACModeDescript[]={
	{ "emCenACBlowIn", (int)emCenACBlowIn },
	{ "emCenACheat", (int)emCenACheat },
	{ "emCenAcref", (int)emCenAcref },
	{ "emCenACAuto", (int)emCenACAuto },
	{ "emCenACChaAir", (int)emCenACChaAir },
	{ "emCenACdeh", (int)emCenACdeh },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCurActionDescript[]={
	{ "emCurUp", (int)emCurUp },
	{ "emCurDown", (int)emCurDown },
	{ "emCurStop", (int)emCurStop },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCurChannelModeDescript[]={
	{ "emCurChanFirst", (int)emCurChanFirst },
	{ "emCurChanSecond", (int)emCurChanSecond },
	{ "emCurChanFirASec", (int)emCurChanFirASec },
	{ "emCurChanThird", (int)emCurChanThird },
	{ "emCurChanFirAThi", (int)emCurChanFirAThi },
	{ "emCurChanSecAThi", (int)emCurChanSecAThi },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchGatewayTypeDescript[]={
	{ "emGatewayOld", (int)emGatewayOld },
	{ "emGatewayNew", (int)emGatewayNew },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpMixStatusDescript[]={
	{ "emAudMixIdle", (int)emAudMixIdle },
	{ "emAudOpenChan_Fail", (int)emAudOpenChan_Fail },
	{ "emAudOpenChan_Success", (int)emAudOpenChan_Success },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDualReasonDescript[]={
	{ "emTpDualAccept", (int)emTpDualAccept },
	{ "emTpDualBusy", (int)emTpDualBusy },
	{ "emTpDualPreemptive", (int)emTpDualPreemptive },
	{ "emTpDualPeerReject", (int)emTpDualPeerReject },
	{ "emTpDualPeerStop", (int)emTpDualPeerStop },
	{ "emTpDualNoVideo", (int)emTpDualNoVideo },
	{ "emTpDualLocalStop", (int)emTpDualLocalStop },
	{ "emTpDualSndFail", (int)emTpDualSndFail },
	{ "emTpDualInit", (int)emTpDualInit },
	{ "emTpDualBitrateIs0", (int)emTpDualBitrateIs0 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPPayloadTypeDescript[]={
	{ "emTpPayloadTypeBegin", (int)emTpPayloadTypeBegin },
	{ "emTpAudioTypeBegin", (int)emTpAudioTypeBegin },
	{ "emTpG711a", (int)emTpG711a },
	{ "emTpG711u", (int)emTpG711u },
	{ "emTpG722", (int)emTpG722 },
	{ "emTpG7231", (int)emTpG7231 },
	{ "emTpG728", (int)emTpG728 },
	{ "emTpG729", (int)emTpG729 },
	{ "emTpMp3", (int)emTpMp3 },
	{ "emTpG723", (int)emTpG723 },
	{ "emTpG7221", (int)emTpG7221 },
	{ "emTpMpegaaclc", (int)emTpMpegaaclc },
	{ "emTpMpegaacld", (int)emTpMpegaacld },
	{ "emTpG719", (int)emTpG719 },
	{ "emTpAudioTypeEnd", (int)emTpAudioTypeEnd },
	{ "emTpVideoTypeBegin", (int)emTpVideoTypeBegin },
	{ "emTpH261", (int)emTpH261 },
	{ "emTpH263", (int)emTpH263 },
	{ "emTpH263plus", (int)emTpH263plus },
	{ "emTpH264", (int)emTpH264 },
	{ "emTpH262", (int)emTpH262 },
	{ "emTpMpeg4", (int)emTpMpeg4 },
	{ "emTpVideoTypeEnd", (int)emTpVideoTypeEnd },
	{ "emTpDataTypeBegin", (int)emTpDataTypeBegin },
	{ "emTpT120", (int)emTpT120 },
	{ "emTpH224", (int)emTpH224 },
	{ "emTpDataTypeEnd", (int)emTpDataTypeEnd },
	{ "emTpPayloadTypeEnd", (int)emTpPayloadTypeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPPosStatusDescript[]={
	{ "emPosInAcitve", (int)emPosInAcitve },
	{ "emPosAcitve", (int)emPosAcitve },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPPollResultDescript[]={
	{ "emPollSucceed", (int)emPollSucceed },
	{ "emPollFailUnKown", (int)emPollFailUnKown },
	{ "emPollInvalidEp", (int)emPollInvalidEp },
	{ "emPollResFull", (int)emPollResFull },
	{ "emPollResFull_Bw", (int)emPollResFull_Bw },
	{ "emPollResFull_Bas", (int)emPollResFull_Bas },
	{ "emPollNoChair", (int)emPollNoChair },
	{ "emPollChairNoLine", (int)emPollChairNoLine },
	{ "emPollServerBusy", (int)emPollServerBusy },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPollStatDescript[]={
	{ "EmPollStat_Error", (int)EmPollStat_Error },
	{ "EmPollStat_Stop", (int)EmPollStat_Stop },
	{ "EmPollStat_Start", (int)EmPollStat_Start },
	{ "EmPollStat_Suspend", (int)EmPollStat_Suspend },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPViewResultDescript[]={
	{ "emViewSucceed", (int)emViewSucceed },
	{ "emViewFailUnKown", (int)emViewFailUnKown },
	{ "emViewFailStatusError", (int)emViewFailStatusError },
	{ "emViewFailOffline", (int)emViewFailOffline },
	{ "emViewFailNotChair", (int)emViewFailNotChair },
	{ "emViewFailNoResource", (int)emViewFailNoResource },
	{ "emViewFailDstNoVid", (int)emViewFailDstNoVid },
	{ "emViewRequesting", (int)emViewRequesting },
	{ "emViewFailIllegalPos", (int)emViewFailIllegalPos },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPViewLocalResultDescript[]={
	{ "emViewLocalSucceed", (int)emViewLocalSucceed },
	{ "emViewLocalFailUnKown", (int)emViewLocalFailUnKown },
	{ "emViewLocalFailStatusError", (int)emViewLocalFailStatusError },
	{ "emViewLocalFailOffline", (int)emViewLocalFailOffline },
	{ "emViewLocalFailIllegalPos", (int)emViewLocalFailIllegalPos },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDisOprTypeDescript[]={
	{ "emDisOprType_Idle", (int)emDisOprType_Idle },
	{ "emDisOprType_StartAll", (int)emDisOprType_StartAll },
	{ "emDisOprType_AddChnl", (int)emDisOprType_AddChnl },
	{ "emDisOprType_ChangeSeat", (int)emDisOprType_ChangeSeat },
	{ "emDisOprType_RemoveChnl", (int)emDisOprType_RemoveChnl },
	{ "emDisOprType_DisConnectChnl", (int)emDisOprType_DisConnectChnl },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMPosPicDescript[]={
	{ "emPic_Invalid", (int)emPic_Invalid },
	{ "emPic_Local", (int)emPic_Local },
	{ "emPic_Static", (int)emPic_Static },
	{ "emPic_Speaker", (int)emPic_Speaker },
	{ "emPic_Dual", (int)emPic_Dual },
	{ "emPic_Poll", (int)emPic_Poll },
	{ "emPic_SelView", (int)emPic_SelView },
	{ "emPic_SelDual", (int)emPic_SelDual },
	{ "emPic_SelLocal", (int)emPic_SelLocal },
	{ "emPic_Discuss", (int)emPic_Discuss },
	{ "emPic_SelTVS", (int)emPic_SelTVS },
	{ "emPic_Chair", (int)emPic_Chair },
	{ "emPic_VmpBrd", (int)emPic_VmpBrd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMDSCREATETYPEDescript[]={
	{ "emDS_CreateType_Invalid", (int)emDS_CreateType_Invalid },
	{ "emDS_CreateType_SndBoundary", (int)emDS_CreateType_SndBoundary },
	{ "emDS_CreateType_RcvBoundary", (int)emDS_CreateType_RcvBoundary },
	{ "emDS_CreateType_SndAndRcvBoundary", (int)emDS_CreateType_SndAndRcvBoundary },
	{ "emDS_CreateType_NotBoundary", (int)emDS_CreateType_NotBoundary },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAddDualRcvResultDescript[]={
	{ "emAddDualRcvSucceed", (int)emAddDualRcvSucceed },
	{ "emAddDualRcvFailNoDual", (int)emAddDualRcvFailNoDual },
	{ "emAddDualRcvFailIllegalPos", (int)emAddDualRcvFailIllegalPos },
	{ "emAddDualRcvFailNoPos", (int)emAddDualRcvFailNoPos },
	{ "emAddDualRcvFailStatusError", (int)emAddDualRcvFailStatusError },
	{ "emAddDualRcvFailUnKown", (int)emAddDualRcvFailUnKown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDeleteDualRcvResultDescript[]={
	{ "emDeleteDualRcvSucceed", (int)emDeleteDualRcvSucceed },
	{ "emDeleteDualRcvFailNoDual", (int)emDeleteDualRcvFailNoDual },
	{ "emDeleteDualRcvFailIllegalPos", (int)emDeleteDualRcvFailIllegalPos },
	{ "emDeleteDualRcvFailUnKown", (int)emDeleteDualRcvFailUnKown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPMtModelDescript[]={
	{ "emTPUnknownMtModel", (int)emTPUnknownMtModel },
	{ "emTPPCMT", (int)emTPPCMT },
	{ "emTP8010", (int)emTP8010 },
	{ "emTP8010A", (int)emTP8010A },
	{ "emTP8010Aplus", (int)emTP8010Aplus },
	{ "emTP8010C", (int)emTP8010C },
	{ "emTP8010C1", (int)emTP8010C1 },
	{ "emTPIMT", (int)emTPIMT },
	{ "emTP8220A", (int)emTP8220A },
	{ "emTP8220B", (int)emTP8220B },
	{ "emTP8220C", (int)emTP8220C },
	{ "emTP8620A", (int)emTP8620A },
	{ "emTPTS6610E", (int)emTPTS6610E },
	{ "emTPTS6210", (int)emTPTS6210 },
	{ "emTP8010A_2", (int)emTP8010A_2 },
	{ "emTP8010A_4", (int)emTP8010A_4 },
	{ "emTP8010A_8", (int)emTP8010A_8 },
	{ "emTP7210", (int)emTP7210 },
	{ "emTP7610", (int)emTP7610 },
	{ "emTPTS5610", (int)emTPTS5610 },
	{ "emTPTS6610", (int)emTPTS6610 },
	{ "emTP7810", (int)emTP7810 },
	{ "emTP7910", (int)emTP7910 },
	{ "emTP7620_A", (int)emTP7620_A },
	{ "emTP7620_B", (int)emTP7620_B },
	{ "emTP7820_A", (int)emTP7820_A },
	{ "emTP7820_B", (int)emTP7820_B },
	{ "emTP7920_A", (int)emTP7920_A },
	{ "emTP7920_B", (int)emTP7920_B },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDsTypeDescript[]={
	{ "em_DsType_Invalid", (int)em_DsType_Invalid },
	{ "em_Ds_Remote_ASnd_0", (int)em_Ds_Remote_ASnd_0 },
	{ "em_Ds_Remote_ASnd_1", (int)em_Ds_Remote_ASnd_1 },
	{ "em_Ds_Remote_ASnd_2", (int)em_Ds_Remote_ASnd_2 },
	{ "em_Ds_Remote_ARcv_0", (int)em_Ds_Remote_ARcv_0 },
	{ "em_Ds_Remote_ARcv_1", (int)em_Ds_Remote_ARcv_1 },
	{ "em_Ds_Remote_ARcv_2", (int)em_Ds_Remote_ARcv_2 },
	{ "em_Ds_Remote_VSnd_0", (int)em_Ds_Remote_VSnd_0 },
	{ "em_Ds_Remote_VSnd_1", (int)em_Ds_Remote_VSnd_1 },
	{ "em_Ds_Remote_VSnd_2", (int)em_Ds_Remote_VSnd_2 },
	{ "em_Ds_Remote_VRcv_0", (int)em_Ds_Remote_VRcv_0 },
	{ "em_Ds_Remote_VRcv_1", (int)em_Ds_Remote_VRcv_1 },
	{ "em_Ds_Remote_VRcv_2", (int)em_Ds_Remote_VRcv_2 },
	{ "em_Ds_Remote_VSnd_Mini_0", (int)em_Ds_Remote_VSnd_Mini_0 },
	{ "em_Ds_Remote_VSnd_Mini_1", (int)em_Ds_Remote_VSnd_Mini_1 },
	{ "em_Ds_Remote_VSnd_Mini_2", (int)em_Ds_Remote_VSnd_Mini_2 },
	{ "em_Ds_Remote_VRcv_0_Mini_0", (int)em_Ds_Remote_VRcv_0_Mini_0 },
	{ "em_Ds_Remote_VRcv_0_Mini_1", (int)em_Ds_Remote_VRcv_0_Mini_1 },
	{ "em_Ds_Remote_VRcv_1_Mini_0", (int)em_Ds_Remote_VRcv_1_Mini_0 },
	{ "em_Ds_Remote_VRcv_1_Mini_1", (int)em_Ds_Remote_VRcv_1_Mini_1 },
	{ "em_Ds_Remote_VRcv_2_Mini_0", (int)em_Ds_Remote_VRcv_2_Mini_0 },
	{ "em_Ds_Remote_VRcv_2_Mini_1", (int)em_Ds_Remote_VRcv_2_Mini_1 },
	{ "em_Ds_Remote_Mix_Snd", (int)em_Ds_Remote_Mix_Snd },
	{ "em_Ds_Remote_Mix_Rcv", (int)em_Ds_Remote_Mix_Rcv },
	{ "em_Ds_RemoteDual_ASnd", (int)em_Ds_RemoteDual_ASnd },
	{ "em_Ds_RemoteDual_VSnd", (int)em_Ds_RemoteDual_VSnd },
	{ "em_Ds_RemoteDual_ARcv", (int)em_Ds_RemoteDual_ARcv },
	{ "em_Ds_RemoteDual_VRcv", (int)em_Ds_RemoteDual_VRcv },
	{ "em_Ds_VirRemote_ASnd_0", (int)em_Ds_VirRemote_ASnd_0 },
	{ "em_Ds_VirRemote_ASnd_1", (int)em_Ds_VirRemote_ASnd_1 },
	{ "em_Ds_VirRemote_ASnd_2", (int)em_Ds_VirRemote_ASnd_2 },
	{ "em_Ds_VirRemote_ARcv_0", (int)em_Ds_VirRemote_ARcv_0 },
	{ "em_Ds_VirRemote_ARcv_1", (int)em_Ds_VirRemote_ARcv_1 },
	{ "em_Ds_VirRemote_ARcv_2", (int)em_Ds_VirRemote_ARcv_2 },
	{ "em_Ds_VirRemote_VSnd_0", (int)em_Ds_VirRemote_VSnd_0 },
	{ "em_Ds_VirRemote_VSnd_1", (int)em_Ds_VirRemote_VSnd_1 },
	{ "em_Ds_VirRemote_VSnd_2", (int)em_Ds_VirRemote_VSnd_2 },
	{ "em_Ds_VirRemote_VRcv_0", (int)em_Ds_VirRemote_VRcv_0 },
	{ "em_Ds_VirRemote_VRcv_1", (int)em_Ds_VirRemote_VRcv_1 },
	{ "em_Ds_VirRemote_VRcv_2", (int)em_Ds_VirRemote_VRcv_2 },
	{ "em_Ds_VirRemote_VSnd_Mini_0", (int)em_Ds_VirRemote_VSnd_Mini_0 },
	{ "em_Ds_VirRemote_VSnd_Mini_1", (int)em_Ds_VirRemote_VSnd_Mini_1 },
	{ "em_Ds_VirRemote_VSnd_Mini_2", (int)em_Ds_VirRemote_VSnd_Mini_2 },
	{ "em_Ds_VirRemote_VRcv_0_Mini_0", (int)em_Ds_VirRemote_VRcv_0_Mini_0 },
	{ "em_Ds_VirRemote_VRcv_0_Mini_1", (int)em_Ds_VirRemote_VRcv_0_Mini_1 },
	{ "em_Ds_VirRemote_VRcv_1_Mini_0", (int)em_Ds_VirRemote_VRcv_1_Mini_0 },
	{ "em_Ds_VirRemote_VRcv_1_Mini_1", (int)em_Ds_VirRemote_VRcv_1_Mini_1 },
	{ "em_Ds_VirRemote_VRcv_2_Mini_0", (int)em_Ds_VirRemote_VRcv_2_Mini_0 },
	{ "em_Ds_VirRemote_VRcv_2_Mini_1", (int)em_Ds_VirRemote_VRcv_2_Mini_1 },
	{ "em_Ds_VirRemote_Mix_Snd", (int)em_Ds_VirRemote_Mix_Snd },
	{ "em_Ds_VirRemote_Mix_Rcv", (int)em_Ds_VirRemote_Mix_Rcv },
	{ "em_Ds_VirRemote_End", (int)em_Ds_VirRemote_End },
	{ "em_Ds_MT_ASnd_0", (int)em_Ds_MT_ASnd_0 },
	{ "em_Ds_MT_ASnd_1", (int)em_Ds_MT_ASnd_1 },
	{ "em_Ds_MT_ASnd_2", (int)em_Ds_MT_ASnd_2 },
	{ "em_Ds_MT_ASnd_3", (int)em_Ds_MT_ASnd_3 },
	{ "em_Ds_MT_ARcv_0", (int)em_Ds_MT_ARcv_0 },
	{ "em_Ds_MT_ARcv_1", (int)em_Ds_MT_ARcv_1 },
	{ "em_Ds_MT_ARcv_2", (int)em_Ds_MT_ARcv_2 },
	{ "em_Ds_MT_ARcv_3", (int)em_Ds_MT_ARcv_3 },
	{ "em_Ds_MT_VSnd_0", (int)em_Ds_MT_VSnd_0 },
	{ "em_Ds_MT_VSnd_1", (int)em_Ds_MT_VSnd_1 },
	{ "em_Ds_MT_VSnd_2", (int)em_Ds_MT_VSnd_2 },
	{ "em_Ds_MT_VSnd_3", (int)em_Ds_MT_VSnd_3 },
	{ "em_Ds_MT_VRcv_0", (int)em_Ds_MT_VRcv_0 },
	{ "em_Ds_MT_VRcv_1", (int)em_Ds_MT_VRcv_1 },
	{ "em_Ds_MT_VRcv_2", (int)em_Ds_MT_VRcv_2 },
	{ "em_Ds_MT_VRcv_3", (int)em_Ds_MT_VRcv_3 },
	{ "em_Ds_MT_VSnd_Mini_0", (int)em_Ds_MT_VSnd_Mini_0 },
	{ "em_Ds_MT_VSnd_Mini_1", (int)em_Ds_MT_VSnd_Mini_1 },
	{ "em_Ds_MT_VSnd_Mini_2", (int)em_Ds_MT_VSnd_Mini_2 },
	{ "em_Ds_MT_VRcv_0_Mini_0", (int)em_Ds_MT_VRcv_0_Mini_0 },
	{ "em_Ds_MT_VRcv_0_Mini_1", (int)em_Ds_MT_VRcv_0_Mini_1 },
	{ "em_Ds_MT_VRcv_1_Mini_0", (int)em_Ds_MT_VRcv_1_Mini_0 },
	{ "em_Ds_MT_VRcv_1_Mini_1", (int)em_Ds_MT_VRcv_1_Mini_1 },
	{ "em_Ds_MT_VRcv_2_Mini_0", (int)em_Ds_MT_VRcv_2_Mini_0 },
	{ "em_Ds_MT_VRcv_2_Mini_1", (int)em_Ds_MT_VRcv_2_Mini_1 },
	{ "em_Ds_Mt_Mix_ASnd", (int)em_Ds_Mt_Mix_ASnd },
	{ "em_Ds_VirMt_ASnd_0", (int)em_Ds_VirMt_ASnd_0 },
	{ "em_Ds_VirMt_ASnd_1", (int)em_Ds_VirMt_ASnd_1 },
	{ "em_Ds_VirMt_ASnd_2", (int)em_Ds_VirMt_ASnd_2 },
	{ "em_Ds_VirMt_ARcv_0", (int)em_Ds_VirMt_ARcv_0 },
	{ "em_Ds_VirMt_ARcv_1", (int)em_Ds_VirMt_ARcv_1 },
	{ "em_Ds_VirMt_ARcv_2", (int)em_Ds_VirMt_ARcv_2 },
	{ "em_Ds_VirMt_VSnd_0", (int)em_Ds_VirMt_VSnd_0 },
	{ "em_Ds_VirMt_VSnd_1", (int)em_Ds_VirMt_VSnd_1 },
	{ "em_Ds_VirMt_VSnd_2", (int)em_Ds_VirMt_VSnd_2 },
	{ "em_Ds_VirMt_VRcv_0", (int)em_Ds_VirMt_VRcv_0 },
	{ "em_Ds_VirMt_VRcv_1", (int)em_Ds_VirMt_VRcv_1 },
	{ "em_Ds_VirMt_VRcv_2", (int)em_Ds_VirMt_VRcv_2 },
	{ "em_Ds_VirMt_VSnd_Mini_0", (int)em_Ds_VirMt_VSnd_Mini_0 },
	{ "em_Ds_VirMt_VSnd_Mini_1", (int)em_Ds_VirMt_VSnd_Mini_1 },
	{ "em_Ds_VirMt_VSnd_Mini_2", (int)em_Ds_VirMt_VSnd_Mini_2 },
	{ "em_Ds_VirMt_VRcv_0_Mini_0", (int)em_Ds_VirMt_VRcv_0_Mini_0 },
	{ "em_Ds_VirMt_VRcv_0_Mini_1", (int)em_Ds_VirMt_VRcv_0_Mini_1 },
	{ "em_Ds_VirMt_VRcv_1_Mini_0", (int)em_Ds_VirMt_VRcv_1_Mini_0 },
	{ "em_Ds_VirMt_VRcv_1_Mini_1", (int)em_Ds_VirMt_VRcv_1_Mini_1 },
	{ "em_Ds_VirMt_VRcv_2_Mini_0", (int)em_Ds_VirMt_VRcv_2_Mini_0 },
	{ "em_Ds_VirMt_VRcv_2_Mini_1", (int)em_Ds_VirMt_VRcv_2_Mini_1 },
	{ "em_Ds_VirMt_Mix_ASnd", (int)em_Ds_VirMt_Mix_ASnd },
	{ "em_Ds_Mt_Merge_VSnd", (int)em_Ds_Mt_Merge_VSnd },
	{ "em_Ds_VirMt_Merge_VSnd", (int)em_Ds_VirMt_Merge_VSnd },
	{ "em_Ds_Mt_End", (int)em_Ds_Mt_End },
	{ "em_Ds_Innerspeaker_ASnd", (int)em_Ds_Innerspeaker_ASnd },
	{ "em_Ds_Innerspeaker_VSnd", (int)em_Ds_Innerspeaker_VSnd },
	{ "em_Ds_Innerspeaker_End", (int)em_Ds_Innerspeaker_End },
	{ "em_Ds_VirDual_ASnd", (int)em_Ds_VirDual_ASnd },
	{ "em_Ds_VirDual_VSnd", (int)em_Ds_VirDual_VSnd },
	{ "em_Ds_VirDual_ARcv", (int)em_Ds_VirDual_ARcv },
	{ "em_Ds_VirDual_VRcv", (int)em_Ds_VirDual_VRcv },
	{ "em_Ds_VirDual_Adapter_VSnd", (int)em_Ds_VirDual_Adapter_VSnd },
	{ "em_Ds_MtDual_Adapter", (int)em_Ds_MtDual_Adapter },
	{ "em_Ds_Dual_End", (int)em_Ds_Dual_End },
	{ "em_Ds_Addr_Type_End", (int)em_Ds_Addr_Type_End },
	{ "em_DsOtherType_Begin", (int)em_DsOtherType_Begin },
	{ "em_Ds_VirMtToInnerspeaker_ASnd_0", (int)em_Ds_VirMtToInnerspeaker_ASnd_0 },
	{ "em_Ds_VirMtToInnerspeaker_ASnd_1", (int)em_Ds_VirMtToInnerspeaker_ASnd_1 },
	{ "em_Ds_VirMtToInnerspeaker_ASnd_2", (int)em_Ds_VirMtToInnerspeaker_ASnd_2 },
	{ "em_Ds_VirMtToInnerspeaker_VSnd_0", (int)em_Ds_VirMtToInnerspeaker_VSnd_0 },
	{ "em_Ds_VirMtToInnerspeaker_VSnd_1", (int)em_Ds_VirMtToInnerspeaker_VSnd_1 },
	{ "em_Ds_VirMtToInnerspeaker_VSnd_2", (int)em_Ds_VirMtToInnerspeaker_VSnd_2 },
	{ "em_Ds_DualRcvToVirMt_Rcv_0", (int)em_Ds_DualRcvToVirMt_Rcv_0 },
	{ "em_Ds_DualRcvToVirMt_Rcv_1", (int)em_Ds_DualRcvToVirMt_Rcv_1 },
	{ "em_Ds_DualRcvToVirMt_Rcv_2", (int)em_Ds_DualRcvToVirMt_Rcv_2 },
	{ "em_Ds_VirRemoteToVirMt_ASnd_0", (int)em_Ds_VirRemoteToVirMt_ASnd_0 },
	{ "em_Ds_VirRemoteToVirMt_ASnd_1", (int)em_Ds_VirRemoteToVirMt_ASnd_1 },
	{ "em_Ds_VirRemoteToVirMt_ASnd_2", (int)em_Ds_VirRemoteToVirMt_ASnd_2 },
	{ "em_Ds_VirRemoteToVirMt_VSnd_0", (int)em_Ds_VirRemoteToVirMt_VSnd_0 },
	{ "em_Ds_VirRemoteToVirMt_VSnd_1", (int)em_Ds_VirRemoteToVirMt_VSnd_1 },
	{ "em_Ds_VirRemoteToVirMt_VSnd_2", (int)em_Ds_VirRemoteToVirMt_VSnd_2 },
	{ "em_Ds_VirRemoteToVirMt_ARcv_0", (int)em_Ds_VirRemoteToVirMt_ARcv_0 },
	{ "em_Ds_VirRemoteToVirMt_ARcv_1", (int)em_Ds_VirRemoteToVirMt_ARcv_1 },
	{ "em_Ds_VirRemoteToVirMt_ARcv_2", (int)em_Ds_VirRemoteToVirMt_ARcv_2 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_0", (int)em_Ds_VirRemoteToVirMt_VRcv_0 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_1", (int)em_Ds_VirRemoteToVirMt_VRcv_1 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_2", (int)em_Ds_VirRemoteToVirMt_VRcv_2 },
	{ "em_Ds_VirDualNB_VRcv", (int)em_Ds_VirDualNB_VRcv },
	{ "em_Ds_VirDualNB_VSnd", (int)em_Ds_VirDualNB_VSnd },
	{ "em_Ds_VirDualNB_ARcv", (int)em_Ds_VirDualNB_ARcv },
	{ "em_Ds_VirDualNB_ASnd", (int)em_Ds_VirDualNB_ASnd },
	{ "em_Ds_VirRemoteToVirMt_VSnd_Mini_0", (int)em_Ds_VirRemoteToVirMt_VSnd_Mini_0 },
	{ "em_Ds_VirRemoteToVirMt_VSnd_Mini_1", (int)em_Ds_VirRemoteToVirMt_VSnd_Mini_1 },
	{ "em_Ds_VirRemoteToVirMt_VSnd_Mini_2", (int)em_Ds_VirRemoteToVirMt_VSnd_Mini_2 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_0_Mini_0", (int)em_Ds_VirRemoteToVirMt_VRcv_0_Mini_0 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_0_Mini_1", (int)em_Ds_VirRemoteToVirMt_VRcv_0_Mini_1 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_1_Mini_0", (int)em_Ds_VirRemoteToVirMt_VRcv_1_Mini_0 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_1_Mini_1", (int)em_Ds_VirRemoteToVirMt_VRcv_1_Mini_1 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_2_Mini_0", (int)em_Ds_VirRemoteToVirMt_VRcv_2_Mini_0 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_2_Mini_1", (int)em_Ds_VirRemoteToVirMt_VRcv_2_Mini_1 },
	{ "em_Ds_VirRemoteToVirMt_Mix_ASnd", (int)em_Ds_VirRemoteToVirMt_Mix_ASnd },
	{ "em_Ds_VirRemoteToPad_VSnd", (int)em_Ds_VirRemoteToPad_VSnd },
	{ "em_Ds_VirRemoteToPad_ASnd", (int)em_Ds_VirRemoteToPad_ASnd },
	{ "em_Ds_VirMidRcvToVirMt_VRcv_0", (int)em_Ds_VirMidRcvToVirMt_VRcv_0 },
	{ "em_Ds_VirMidRcvToVirMt_VRcv_2", (int)em_Ds_VirMidRcvToVirMt_VRcv_2 },
	{ "em_Ds_VirDual_ARcv_Pad_Begin", (int)em_Ds_VirDual_ARcv_Pad_Begin },
	{ "em_Ds_VirDual_ARcv_Pad_End", (int)em_Ds_VirDual_ARcv_Pad_End },
	{ "em_Ds_VirDual_VRcv_Pad_Begin", (int)em_Ds_VirDual_VRcv_Pad_Begin },
	{ "em_Ds_VirDual_VRcv_Pad_End", (int)em_Ds_VirDual_VRcv_Pad_End },
	{ "em_Ds_VirDual_VSnd_Pad", (int)em_Ds_VirDual_VSnd_Pad },
	{ "em_Ds_VirTran_VSnd_0", (int)em_Ds_VirTran_VSnd_0 },
	{ "em_Ds_VirTran_VSnd_1", (int)em_Ds_VirTran_VSnd_1 },
	{ "em_Ds_VirTran_VSnd_2", (int)em_Ds_VirTran_VSnd_2 },
	{ "em_Ds_VirTran_ASnd_0", (int)em_Ds_VirTran_ASnd_0 },
	{ "em_Ds_VirTran_ASnd_1", (int)em_Ds_VirTran_ASnd_1 },
	{ "em_Ds_VirTran_ASnd_2", (int)em_Ds_VirTran_ASnd_2 },
	{ "em_Ds_VirTran_VRSnd_0", (int)em_Ds_VirTran_VRSnd_0 },
	{ "em_Ds_VirTran_VRSnd_1", (int)em_Ds_VirTran_VRSnd_1 },
	{ "em_Ds_VirTran_VRSnd_2", (int)em_Ds_VirTran_VRSnd_2 },
	{ "em_Ds_VirTran_ARSnd_0", (int)em_Ds_VirTran_ARSnd_0 },
	{ "em_Ds_VirTran_ARSnd_1", (int)em_Ds_VirTran_ARSnd_1 },
	{ "em_Ds_VirTran_ARSnd_2", (int)em_Ds_VirTran_ARSnd_2 },
	{ "em_Ds_VirTranDual_VSnd", (int)em_Ds_VirTranDual_VSnd },
	{ "em_Ds_VirTranDual_ASnd", (int)em_Ds_VirTranDual_ASnd },
	{ "em_Ds_VirTranS_VSnd_0", (int)em_Ds_VirTranS_VSnd_0 },
	{ "em_Ds_VirTranS_VSnd_1", (int)em_Ds_VirTranS_VSnd_1 },
	{ "em_Ds_VirTranS_VSnd_2", (int)em_Ds_VirTranS_VSnd_2 },
	{ "em_Ds_VirTranS_ASnd_0", (int)em_Ds_VirTranS_ASnd_0 },
	{ "em_Ds_VirTranS_ASnd_1", (int)em_Ds_VirTranS_ASnd_1 },
	{ "em_Ds_VirTranS_ASnd_2", (int)em_Ds_VirTranS_ASnd_2 },
	{ "em_Ds_VirTranS_VRSnd_0", (int)em_Ds_VirTranS_VRSnd_0 },
	{ "em_Ds_VirTranS_VRSnd_1", (int)em_Ds_VirTranS_VRSnd_1 },
	{ "em_Ds_VirTranS_VRSnd_2", (int)em_Ds_VirTranS_VRSnd_2 },
	{ "em_Ds_VirTranS_ARSnd_0", (int)em_Ds_VirTranS_ARSnd_0 },
	{ "em_Ds_VirTranS_ARSnd_1", (int)em_Ds_VirTranS_ARSnd_1 },
	{ "em_Ds_VirTranS_ARSnd_2", (int)em_Ds_VirTranS_ARSnd_2 },
	{ "em_Ds_VirTranSDual_VSnd", (int)em_Ds_VirTranSDual_VSnd },
	{ "em_Ds_VirTranSDual_ASnd", (int)em_Ds_VirTranSDual_ASnd },
	{ "em_Ds_CloudView_VRcv_0", (int)em_Ds_CloudView_VRcv_0 },
	{ "em_Ds_CloudView_VRcv_1", (int)em_Ds_CloudView_VRcv_1 },
	{ "em_Ds_CloudView_VRcv_2", (int)em_Ds_CloudView_VRcv_2 },
	{ "em_Ds_Debug", (int)em_Ds_Debug },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnAudioMixIDDescript[]={
	{ "emCnAMix_INVALID", (int)emCnAMix_INVALID },
	{ "emCnAMix_Speaker", (int)emCnAMix_Speaker },
	{ "emCnAMix_Dual", (int)emCnAMix_Dual },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGetRegInfoTypeDescript[]={
	{ "emGetRegInfoType_CNS", (int)emGetRegInfoType_CNS },
	{ "emGetRegInfoType_UMS", (int)emGetRegInfoType_UMS },
	{ "emGetRegInfoType_ALL", (int)emGetRegInfoType_ALL },
	{ "emGetRegInfoType_MT", (int)emGetRegInfoType_MT },
	{ "emGetRefInfoType_MCU", (int)emGetRefInfoType_MCU },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGetRegInfoOprDescript[]={
	{ "emGetRegInfoOpr_Update", (int)emGetRegInfoOpr_Update },
	{ "emGetRegInfoOpr_Add", (int)emGetRegInfoOpr_Add },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPChanTypeDescript[]={
	{ "emTPChanNone", (int)emTPChanNone },
	{ "emTPChanRecv", (int)emTPChanRecv },
	{ "emTPChanSend", (int)emTPChanSend },
	{ "emTPChanSendRecv", (int)emTPChanSendRecv },
	{ "emTPChanTypeEnd", (int)emTPChanTypeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAACSampleFreqDescript[]={
	{ "emTPFs96000", (int)emTPFs96000 },
	{ "emTPFs88200", (int)emTPFs88200 },
	{ "emTPFs64000", (int)emTPFs64000 },
	{ "emTPFs48000", (int)emTPFs48000 },
	{ "emTPFs44100", (int)emTPFs44100 },
	{ "emTPFs32000", (int)emTPFs32000 },
	{ "emTPFs24000", (int)emTPFs24000 },
	{ "emTPFs22050", (int)emTPFs22050 },
	{ "emTPFs16000", (int)emTPFs16000 },
	{ "emTPFs12000", (int)emTPFs12000 },
	{ "emTPFs11025", (int)emTPFs11025 },
	{ "emTPFs8000", (int)emTPFs8000 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPG7221RateDescript[]={
	{ "emTPG7221Rate24", (int)emTPG7221Rate24 },
	{ "emTPG7221Rate32", (int)emTPG7221Rate32 },
	{ "emTPG7221Rate48", (int)emTPG7221Rate48 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAACChnlCfgDescript[]={
	{ "emTPChnlCust", (int)emTPChnlCust },
	{ "emTPChnl1", (int)emTPChnl1 },
	{ "emTPChnl2", (int)emTPChnl2 },
	{ "emTPChnl3", (int)emTPChnl3 },
	{ "emTPChnl4", (int)emTPChnl4 },
	{ "emTPChnl5", (int)emTPChnl5 },
	{ "emTPChnl5dot1", (int)emTPChnl5dot1 },
	{ "emTPChnl7dot1", (int)emTPChnl7dot1 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPTpApplySpeakerRetDescript[]={
	{ "emTP_ApplySpeaker_Success", (int)emTP_ApplySpeaker_Success },
	{ "emTP_ApplySpeaker_ConfUnExist", (int)emTP_ApplySpeaker_ConfUnExist },
	{ "emTP_ApplySpeaker_EpIDError", (int)emTP_ApplySpeaker_EpIDError },
	{ "emTP_ApplySpeaker_EpStateError", (int)emTP_ApplySpeaker_EpStateError },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPChanSubTypeDescript[]={
	{ "EmTPChanSubType_Normal", (int)EmTPChanSubType_Normal },
	{ "EmTPChanSubType_Mini", (int)EmTPChanSubType_Mini },
	{ "EmTPChanSubType_Dual", (int)EmTPChanSubType_Dual },
	{ "EmTPChanSubType_AMix", (int)EmTPChanSubType_AMix },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMakeCallTypeDescript[]={
	{ "em_sip_call_type", (int)em_sip_call_type },
	{ "em_323_call_type", (int)em_323_call_type },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpRegTypeDescript[]={
	{ "em_sip_reg", (int)em_sip_reg },
	{ "em_323_reg", (int)em_323_reg },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDisListOprTypeDescript[]={
	{ "em_DisListOpr_Add", (int)em_DisListOpr_Add },
	{ "em_DisListOpr_Del", (int)em_DisListOpr_Del },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDisListOprResltDescript[]={
	{ "em_DisListOpr_Sucess", (int)em_DisListOpr_Sucess },
	{ "em_DisListOpr_Fail", (int)em_DisListOpr_Fail },
	{ "em_DisListOpr_Reject", (int)em_DisListOpr_Reject },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVgaTypeDescript[]={
	{ "emVgaTypeFullScreenCamera", (int)emVgaTypeFullScreenCamera },
	{ "emVgaType001", (int)emVgaType001 },
	{ "emVgaType002", (int)emVgaType002 },
	{ "emVgaType003", (int)emVgaType003 },
	{ "emVgaTypeDocCamera", (int)emVgaTypeDocCamera },
	{ "emVgaTypeInValid", (int)emVgaTypeInValid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDualInputTypeDescript[]={
	{ "emDualInputFullScreenCamera", (int)emDualInputFullScreenCamera },
	{ "emDualInput001", (int)emDualInput001 },
	{ "emDualInput002", (int)emDualInput002 },
	{ "emDualInput003", (int)emDualInput003 },
	{ "emDualInputDocCamera", (int)emDualInputDocCamera },
	{ "emDualInputInvalid", (int)emDualInputInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDualOutputTypeDescript[]={
	{ "emDualOutputInvalid", (int)emDualOutputInvalid },
	{ "emDualOutput001", (int)emDualOutput001 },
	{ "emDualOutput002", (int)emDualOutput002 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVgaSwitchResultDescript[]={
	{ "em_VgaSwitchInvalid", (int)em_VgaSwitchInvalid },
	{ "em_VgaSwitchFail", (int)em_VgaSwitchFail },
	{ "em_VgaSwitchSucc", (int)em_VgaSwitchSucc },
	{ "em_CurVgaNoSignal", (int)em_CurVgaNoSignal },
	{ "em_TpNoDual", (int)em_TpNoDual },
	{ "em_VgaBusying", (int)em_VgaBusying },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVgaSwitchReasonDescript[]={
	{ "em_SwitchVgaInvalid", (int)em_SwitchVgaInvalid },
	{ "em_SwitchDemoVga", (int)em_SwitchDemoVga },
	{ "em_SwitchCurVga", (int)em_SwitchCurVga },
	{ "em_ResetVga", (int)em_ResetVga },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnStateDescript[]={
	{ "emCnsRunning", (int)emCnsRunning },
	{ "emCnsSleep", (int)emCnsSleep },
	{ "emCnsPoweroff", (int)emCnsPoweroff },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPCapSignDescript[]={
	{ "emTPCapBig", (int)emTPCapBig },
	{ "emTPCapLeft", (int)emTPCapLeft },
	{ "emTPCapSmall", (int)emTPCapSmall },
	{ "emTPCapRight", (int)emTPCapRight },
	{ "emTPCapEnd", (int)emTPCapEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSwitchStateDescript[]={
	{ "emStateON", (int)emStateON },
	{ "emStateOFF", (int)emStateOFF },
	{ "emStateStandby", (int)emStateStandby },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpBoardRetDescript[]={
	{ "emTP_Board_UnKonw", (int)emTP_Board_UnKonw },
	{ "emTP_Board_AddSuccess", (int)emTP_Board_AddSuccess },
	{ "emTP_Board_DelSuccess", (int)emTP_Board_DelSuccess },
	{ "emTP_Board_ModifySuccess", (int)emTP_Board_ModifySuccess },
	{ "emTP_Board_MaxNum", (int)emTP_Board_MaxNum },
	{ "emTP_Board_Mode_AddSuccess", (int)emTP_Board_Mode_AddSuccess },
	{ "emTP_Board_Mode_DelSuccess", (int)emTP_Board_Mode_DelSuccess },
	{ "emTP_Board_Mode_ModifySuccess", (int)emTP_Board_Mode_ModifySuccess },
	{ "emTP_Board_UnFind", (int)emTP_Board_UnFind },
	{ "emTP_Board_UnKnowLoc", (int)emTP_Board_UnKnowLoc },
	{ "emTP_Board_Repeat", (int)emTP_Board_Repeat },
	{ "emTP_BrdType_NotMatch_EqpType", (int)emTP_BrdType_NotMatch_EqpType },
	{ "emTP_BrdMode_Repeat", (int)emTP_BrdMode_Repeat },
	{ "emTP_BrdMode_MaxNum", (int)emTP_BrdMode_MaxNum },
	{ "emTP_BrdMode_NoConfig", (int)emTP_BrdMode_NoConfig },
	{ "emTp_BrdMode_Resource_Full", (int)emTp_BrdMode_Resource_Full },
	{ "emTp_BrdMode_AudMix_MaxNum", (int)emTp_BrdMode_AudMix_MaxNum },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHduOutPortDescript[]={
	{ "em_hdu_outport_YPbPr", (int)em_hdu_outport_YPbPr },
	{ "em_hdu_outport_VGA", (int)em_hdu_outport_VGA },
	{ "em_hdu_outport_DVI", (int)em_hdu_outport_DVI },
	{ "em_hdu_outport_HDMI", (int)em_hdu_outport_HDMI },
	{ "em_hdu_outport_unknow", (int)em_hdu_outport_unknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHduZoomRateDescript[]={
	{ "em_hdu_zoomrate_4_3", (int)em_hdu_zoomrate_4_3 },
	{ "em_hdu_zoomrate_16_9", (int)em_hdu_zoomrate_16_9 },
	{ "em_hdu_zoomrate_unknow", (int)em_hdu_zoomrate_unknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHduOutModeDescript[]={
	{ "em_hdu_outmode_YPbPr_1080P_24fps", (int)em_hdu_outmode_YPbPr_1080P_24fps },
	{ "em_hdu_outmode_YPbPr_1080P_25fps", (int)em_hdu_outmode_YPbPr_1080P_25fps },
	{ "em_hdu_outmode_YPbPr_1080P_30fps", (int)em_hdu_outmode_YPbPr_1080P_30fps },
	{ "em_hdu_outmode_YPbPr_1080P_50fps", (int)em_hdu_outmode_YPbPr_1080P_50fps },
	{ "em_hdu_outmode_YPbPr_1080P_60fps", (int)em_hdu_outmode_YPbPr_1080P_60fps },
	{ "em_hdu_outmode_YPbPr_1080i_50HZ", (int)em_hdu_outmode_YPbPr_1080i_50HZ },
	{ "em_hdu_outmode_YPbPr_1080i_60HZ", (int)em_hdu_outmode_YPbPr_1080i_60HZ },
	{ "em_hdu_outmode_YPbPr_720P_60fps", (int)em_hdu_outmode_YPbPr_720P_60fps },
	{ "em_hdu_outmode_YPbPr_576i_50HZ", (int)em_hdu_outmode_YPbPr_576i_50HZ },
	{ "em_hdu_outmode_YPbPr_480i_60HZ", (int)em_hdu_outmode_YPbPr_480i_60HZ },
	{ "em_hdu_outmode_VGA_SXGA_60HZ", (int)em_hdu_outmode_VGA_SXGA_60HZ },
	{ "em_hdu_outmode_VGA_XGA_60HZ", (int)em_hdu_outmode_VGA_XGA_60HZ },
	{ "em_hdu_outmode_VGA_XGA_75HZ", (int)em_hdu_outmode_VGA_XGA_75HZ },
	{ "em_hdu_outmode_VGA_SVGA_60HZ", (int)em_hdu_outmode_VGA_SVGA_60HZ },
	{ "em_hdu_outmode_VGA_SVGA_75HZ", (int)em_hdu_outmode_VGA_SVGA_75HZ },
	{ "em_hdu_outmode_VGA_VGA_60HZ", (int)em_hdu_outmode_VGA_VGA_60HZ },
	{ "em_hdu_outmode_VGA_VGA_75HZ", (int)em_hdu_outmode_VGA_VGA_75HZ },
	{ "em_hdu_outmode_VGA_SXGA_75HZ", (int)em_hdu_outmode_VGA_SXGA_75HZ },
	{ "em_hdu_outmode_YPbPr_720P_50fps", (int)em_hdu_outmode_YPbPr_720P_50fps },
	{ "em_hdu_outmode_VGA_WXGA_1280_768_60HZ", (int)em_hdu_outmode_VGA_WXGA_1280_768_60HZ },
	{ "em_hdu_outmode_VGA_WXGA_1280_800_60HZ", (int)em_hdu_outmode_VGA_WXGA_1280_800_60HZ },
	{ "em_hdu_outmode_VGA_WSXGA_60HZ", (int)em_hdu_outmode_VGA_WSXGA_60HZ },
	{ "em_hdu_outmode_VGA_SXGAPlus_60HZ", (int)em_hdu_outmode_VGA_SXGAPlus_60HZ },
	{ "em_hdu_outmode_VGA_UXGA_60HZ", (int)em_hdu_outmode_VGA_UXGA_60HZ },
	{ "em_hdu_outmode_YPbPr_1080P_29970HZ", (int)em_hdu_outmode_YPbPr_1080P_29970HZ },
	{ "em_hdu_outmode_YPbPr_1080P_59940HZ", (int)em_hdu_outmode_YPbPr_1080P_59940HZ },
	{ "em_hdu_outmode_WXGA_1280_800_75HZ", (int)em_hdu_outmode_WXGA_1280_800_75HZ },
	{ "em_hdu_outmode_unknow", (int)em_hdu_outmode_unknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHduShowModeDescript[]={
	{ "em_hdu_showmode_NONGEOMETRIC", (int)em_hdu_showmode_NONGEOMETRIC },
	{ "em_hdu_showmode_CUTEDGEGEOME", (int)em_hdu_showmode_CUTEDGEGEOME },
	{ "em_hdu_showmode_BLACKEDGEGEOME", (int)em_hdu_showmode_BLACKEDGEGEOME },
	{ "em_hdu_showmode_unknow", (int)em_hdu_showmode_unknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmModifyNMServerRetDescript[]={
	{ "em_nmserver_modify_success", (int)em_nmserver_modify_success },
	{ "em_nmserver_resource_full", (int)em_nmserver_resource_full },
	{ "em_nmserver_invalid_handle", (int)em_nmserver_invalid_handle },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmModifyVcrRetDescript[]={
	{ "em_vcr_modify_success", (int)em_vcr_modify_success },
	{ "em_vcr_invalid", (int)em_vcr_invalid },
	{ "em_vcr_full", (int)em_vcr_full },
	{ "em_vcr_no_exist", (int)em_vcr_no_exist },
	{ "em_vcr_exist", (int)em_vcr_exist },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmModifyHduRetDescript[]={
	{ "em_hdu_modify_success", (int)em_hdu_modify_success },
	{ "em_hdu_invalid_index", (int)em_hdu_invalid_index },
	{ "em_hdu_brd_no_cfg", (int)em_hdu_brd_no_cfg },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmUpdateHduRetDescript[]={
	{ "em_hdu_update_success", (int)em_hdu_update_success },
	{ "em_hdu_update_ing", (int)em_hdu_update_ing },
	{ "em_hdu_update_unreg", (int)em_hdu_update_unreg },
	{ "em_hdu_update_unknow", (int)em_hdu_update_unknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMPCodecDescript[]={
	{ "emMPCodec1", (int)emMPCodec1 },
	{ "emMPCodec2", (int)emMPCodec2 },
	{ "emMPCodec3", (int)emMPCodec3 },
	{ "emMPDualCodec", (int)emMPDualCodec },
	{ "emEndMPCodec", (int)emEndMPCodec },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPHDAudPortInDescript[]={
	{ "emTPAudInCanon1", (int)emTPAudInCanon1 },
	{ "emTPAudInCanon2", (int)emTPAudInCanon2 },
	{ "emTPAudInCanon3", (int)emTPAudInCanon3 },
	{ "emTPAudInCanon4", (int)emTPAudInCanon4 },
	{ "emTPAudInCanon5", (int)emTPAudInCanon5 },
	{ "emTPAudInCanon6", (int)emTPAudInCanon6 },
	{ "emTPAudInCanon7", (int)emTPAudInCanon7 },
	{ "emTPAudInCanon8", (int)emTPAudInCanon8 },
	{ "emTPAudInCanon9", (int)emTPAudInCanon9 },
	{ "emTPAudInCanon10", (int)emTPAudInCanon10 },
	{ "emTPAudInDigit0", (int)emTPAudInDigit0 },
	{ "emTPAudInDigit1", (int)emTPAudInDigit1 },
	{ "emTPAudInDigit2", (int)emTPAudInDigit2 },
	{ "emTPAudInEnd", (int)emTPAudInEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPHDDualAudPortInDescript[]={
	{ "emTPAudInTrs1", (int)emTPAudInTrs1 },
	{ "emTPAudInTrs2", (int)emTPAudInTrs2 },
	{ "emTPAudInTrs3", (int)emTPAudInTrs3 },
	{ "emTPAudInTrs4", (int)emTPAudInTrs4 },
	{ "emTPAudInRcaL", (int)emTPAudInRcaL },
	{ "emTPAudInRcaR", (int)emTPAudInRcaR },
	{ "emTPDualAudInEnd", (int)emTPDualAudInEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPHDAudPortOutDescript[]={
	{ "emTPAudOutCCanon1", (int)emTPAudOutCCanon1 },
	{ "emTPAudOutCCanon2", (int)emTPAudOutCCanon2 },
	{ "emTPAudOutCCanon3", (int)emTPAudOutCCanon3 },
	{ "emTPAudOutCCanon4", (int)emTPAudOutCCanon4 },
	{ "emTPAudOutCCanon5", (int)emTPAudOutCCanon5 },
	{ "emTPAudOutReproducer", (int)emTPAudOutReproducer },
	{ "emTPAudOutEnd", (int)emTPAudOutEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPMtVideoPortDescript[]={
	{ "emTPC1Vid", (int)emTPC1Vid },
	{ "emTPC2Vid", (int)emTPC2Vid },
	{ "emTPC3Vid", (int)emTPC3Vid },
	{ "emTPC4Vid", (int)emTPC4Vid },
	{ "emTPC5Vid", (int)emTPC5Vid },
	{ "emTPC6Vid", (int)emTPC6Vid },
	{ "emTPC7Vid", (int)emTPC7Vid },
	{ "emTPC8Vid", (int)emTPC8Vid },
	{ "emTPC9Vid", (int)emTPC9Vid },
	{ "emTPC10Vid", (int)emTPC10Vid },
	{ "emTPC11Vid", (int)emTPC11Vid },
	{ "emTPVidEnd", (int)emTPVidEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPMtVideoOutPortDescript[]={
	{ "emTPC1OutVid", (int)emTPC1OutVid },
	{ "emTPC2OutVid", (int)emTPC2OutVid },
	{ "emTPC3OutVid", (int)emTPC3OutVid },
	{ "emTPC4OutVid", (int)emTPC4OutVid },
	{ "emTPC5OutVid", (int)emTPC5OutVid },
	{ "emTPVidOutEnd", (int)emTPVidOutEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAutoTestTypeDescript[]={
	{ "emTPAutoTestBegin", (int)emTPAutoTestBegin },
	{ "emTPAutoTestAudioLoopBackFunc", (int)emTPAutoTestAudioLoopBackFunc },
	{ "emTPAutoTestPriomVideoLoopBackFunc", (int)emTPAutoTestPriomVideoLoopBackFunc },
	{ "emTPAutoTestSecondVideoLoopBackFunc", (int)emTPAutoTestSecondVideoLoopBackFunc },
	{ "emTPAutoTestEnd", (int)emTPAutoTestEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPHduRunStatusDescript[]={
	{ "emTPHduIdle", (int)emTPHduIdle },
	{ "emTPHduWaiting", (int)emTPHduWaiting },
	{ "emTPHduPlaying", (int)emTPHduPlaying },
	{ "emTPHduUnknow", (int)emTPHduUnknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPLoudspeakerValDescript[]={
	{ "emTPLoudspeakerLow", (int)emTPLoudspeakerLow },
	{ "emTPLoudspeakerMiddle", (int)emTPLoudspeakerMiddle },
	{ "emTPLoudspeakerHigh", (int)emTPLoudspeakerHigh },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPFrameUnitTypeDescript[]={
	{ "emTPFrameSecond", (int)emTPFrameSecond },
	{ "emTPSecondFrame", (int)emTPSecondFrame },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPVideoStandardDescript[]={
	{ "emTPPAL", (int)emTPPAL },
	{ "emTPNTSC", (int)emTPNTSC },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPLabelTypeDescript[]={
	{ "emTPLabelAuto", (int)emTPLabelAuto },
	{ "emTPLabelUserDef", (int)emTPLabelUserDef },
	{ "emTPLabelOff", (int)emTPLabelOff },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPLabelPosTypeDescript[]={
	{ "emTPTopLeft", (int)emTPTopLeft },
	{ "emTPTopRight", (int)emTPTopRight },
	{ "emTPBottomLeft", (int)emTPBottomLeft },
	{ "emTPBottomRight", (int)emTPBottomRight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDualVideoShowModeDescript[]={
	{ "emTPDualVideoOnSigleScreen", (int)emTPDualVideoOnSigleScreen },
	{ "emTPEachVideoOwnScreen", (int)emTPEachVideoOwnScreen },
	{ "emTPTripleVideoOnSingleScn", (int)emTPTripleVideoOnSingleScn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDisplayRatioDescript[]={
	{ "emTPDR4to3", (int)emTPDR4to3 },
	{ "emTPDR16to9", (int)emTPDR16to9 },
	{ "emTPDRAuto", (int)emTPDRAuto },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPFecModeTypeDescript[]={
	{ "emTPFECTYPENONE", (int)emTPFECTYPENONE },
	{ "emTPFECTYPERAID5", (int)emTPFECTYPERAID5 },
	{ "emTPFECTYPERAID5INTERLEAVE", (int)emTPFECTYPERAID5INTERLEAVE },
	{ "emTPFECTYPERAID6", (int)emTPFECTYPERAID6 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPNetTypeDescript[]={
	{ "emTPInternet", (int)emTPInternet },
	{ "emTPSpecial", (int)emTPSpecial },
	{ "emTPVPN", (int)emTPVPN },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPEqualizerRateDescript[]={
	{ "emTPRate100", (int)emTPRate100 },
	{ "emTPRate200", (int)emTPRate200 },
	{ "emTPRate400", (int)emTPRate400 },
	{ "emTPRate600", (int)emTPRate600 },
	{ "emTPRate1k", (int)emTPRate1k },
	{ "emTPRate3k", (int)emTPRate3k },
	{ "emTPRate6k", (int)emTPRate6k },
	{ "emTPRate12k", (int)emTPRate12k },
	{ "emTPRate14k", (int)emTPRate14k },
	{ "emTPRate16k", (int)emTPRate16k },
	{ "emTPRateend", (int)emTPRateend },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPPIPModeDescript[]={
	{ "TP_VIDEO_PIPMODE_IDLE", (int)TP_VIDEO_PIPMODE_IDLE },
	{ "TP_VIDEO_PIPMODE_LOOP", (int)TP_VIDEO_PIPMODE_LOOP },
	{ "TP_VIDEO_PIPMODE_ONE_LOCAL", (int)TP_VIDEO_PIPMODE_ONE_LOCAL },
	{ "TP_VIDEO_PIPMODE_ONE_OTHER", (int)TP_VIDEO_PIPMODE_ONE_OTHER },
	{ "TP_VIDEO_PIPMODE_ONE_AUX_LOCAL", (int)TP_VIDEO_PIPMODE_ONE_AUX_LOCAL },
	{ "TP_VIDEO_PIPMODE_STATIC", (int)TP_VIDEO_PIPMODE_STATIC },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDVIModeDescript[]={
	{ "TP_DVI_MODE_HDMI", (int)TP_DVI_MODE_HDMI },
	{ "TP_DVI_MODE_VGA", (int)TP_DVI_MODE_VGA },
	{ "TP_DVI_MODE_DVI", (int)TP_DVI_MODE_DVI },
	{ "TP_DVI_MODE_Ypbpr", (int)TP_DVI_MODE_Ypbpr },
	{ "TP_DVI_MODE_INVALID", (int)TP_DVI_MODE_INVALID },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPMCModeDescript[]={
	{ "emTPMcSpeech", (int)emTPMcSpeech },
	{ "emTPMcDiscuss", (int)emTPMcDiscuss },
	{ "emTPMcModeEnd", (int)emTPMcModeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnsUpdateStateDescript[]={
	{ "emCnsIdle", (int)emCnsIdle },
	{ "emCnsDownloading", (int)emCnsDownloading },
	{ "emCnsDownloaded", (int)emCnsDownloaded },
	{ "emCnsUpdating", (int)emCnsUpdating },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPCnLoginUpdateRetDescript[]={
	{ "emTPCnLoginUpdateInvalid", (int)emTPCnLoginUpdateInvalid },
	{ "emTPCnLoginUpdateFail", (int)emTPCnLoginUpdateFail },
	{ "emTPCnLoginUpdateSuccess", (int)emTPCnLoginUpdateSuccess },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPFileSrvUsedVersionDescript[]={
	{ "emTPFileSrvUsedVersion1", (int)emTPFileSrvUsedVersion1 },
	{ "emTPFileSrvUsedVersion2", (int)emTPFileSrvUsedVersion2 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPFileSrvFileTypeDescript[]={
	{ "emTPFileSrvFileTypeUnknown", (int)emTPFileSrvFileTypeUnknown },
	{ "emTPFileSrvFileTypeService", (int)emTPFileSrvFileTypeService },
	{ "emTPFileSrvFileTypeConsole", (int)emTPFileSrvFileTypeConsole },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPOSTypeDescript[]={
	{ "emTPWindows", (int)emTPWindows },
	{ "emTPLinux", (int)emTPLinux },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMPAudEncCodecDescript[]={
	{ "emMPAudEncCodec1", (int)emMPAudEncCodec1 },
	{ "emMPAudEncCodec2", (int)emMPAudEncCodec2 },
	{ "emMPAudEncCodec3", (int)emMPAudEncCodec3 },
	{ "emMPAudEncDualCodec", (int)emMPAudEncDualCodec },
	{ "emMPAudEncMixCodec", (int)emMPAudEncMixCodec },
	{ "emEndMPAudEncCodec", (int)emEndMPAudEncCodec },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmToolTypeDescript[]={
	{ "emMainTerabceTool", (int)emMainTerabceTool },
	{ "emProTestTool", (int)emProTestTool },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmProducetestTypeDescript[]={
	{ "emProducetestTypeBegin", (int)emProducetestTypeBegin },
	{ "emTestVideoMAIN1InOut", (int)emTestVideoMAIN1InOut },
	{ "emTestVideoMAIN2InOut", (int)emTestVideoMAIN2InOut },
	{ "emTestVideoMAIN3InOut", (int)emTestVideoMAIN3InOut },
	{ "emTestVideoSUB1InMAIN3AUX12Out", (int)emTestVideoSUB1InMAIN3AUX12Out },
	{ "emTestDualSUB2InTurnHDMIAUX1Out", (int)emTestDualSUB2InTurnHDMIAUX1Out },
	{ "emTestDualAUX1InTurnHDMIAUX1Out", (int)emTestDualAUX1InTurnHDMIAUX1Out },
	{ "emTestDualAUX2InTurnHDMIAUX1Out", (int)emTestDualAUX2InTurnHDMIAUX1Out },
	{ "emTestDualAUX3InTurnHDMIAUX1Out", (int)emTestDualAUX3InTurnHDMIAUX1Out },
	{ "emTestDualAUX4InTurnHDMIAUX2Out", (int)emTestDualAUX4InTurnHDMIAUX2Out },
	{ "emTestDualAUX5InTurnHDMIAUX2Out", (int)emTestDualAUX5InTurnHDMIAUX2Out },
	{ "emTestDualAUX6InTurnHDMIAUX2Out", (int)emTestDualAUX6InTurnHDMIAUX2Out },
	{ "emTestDualSUB2InTurnVGAAUX1Out", (int)emTestDualSUB2InTurnVGAAUX1Out },
	{ "emTestDualAUX1InTurnVGAAUX1Out", (int)emTestDualAUX1InTurnVGAAUX1Out },
	{ "emTestDualAUX2InTurnVGAAUX1Out", (int)emTestDualAUX2InTurnVGAAUX1Out },
	{ "emTestDualAUX3InTurnVGAAUX1Out", (int)emTestDualAUX3InTurnVGAAUX1Out },
	{ "emTestDualAUX4InTurnVGAAUX2Out", (int)emTestDualAUX4InTurnVGAAUX2Out },
	{ "emTestDualAUX5InTurnVGAAUX2Out", (int)emTestDualAUX5InTurnVGAAUX2Out },
	{ "emTestDualAUX6InTurnVGAAUX2Out", (int)emTestDualAUX6InTurnVGAAUX2Out },
	{ "emTestAudioMIC1InMAIN1Out", (int)emTestAudioMIC1InMAIN1Out },
	{ "emTestAudioMIC2InMAIN2Out", (int)emTestAudioMIC2InMAIN2Out },
	{ "emTestAudioMIC3InMAIN3Out", (int)emTestAudioMIC3InMAIN3Out },
	{ "emTestAudioCANNON1InMAIN1Out", (int)emTestAudioCANNON1InMAIN1Out },
	{ "emTestAudioCANNON2InMAIN1Out", (int)emTestAudioCANNON2InMAIN1Out },
	{ "emTestAudioCANNON3InMAIN1Out", (int)emTestAudioCANNON3InMAIN1Out },
	{ "emTestAudioCANNON4InMAIN2Out", (int)emTestAudioCANNON4InMAIN2Out },
	{ "emTestAudioCANNON5InMAIN2Out", (int)emTestAudioCANNON5InMAIN2Out },
	{ "emTestAudioCANNON6InMAIN2Out", (int)emTestAudioCANNON6InMAIN2Out },
	{ "emTestAudioCANNON7InMAIN3Out", (int)emTestAudioCANNON7InMAIN3Out },
	{ "emTestAudioCANNON8InMAIN3Out", (int)emTestAudioCANNON8InMAIN3Out },
	{ "emTestAudioCANNON9InMAIN3Out", (int)emTestAudioCANNON9InMAIN3Out },
	{ "emTestAudioCANNON10InMAIN2Out", (int)emTestAudioCANNON10InMAIN2Out },
	{ "emTestAudioAUX1InAUX1Out", (int)emTestAudioAUX1InAUX1Out },
	{ "emTestAudioAUX2InAUX1Out", (int)emTestAudioAUX2InAUX1Out },
	{ "emTestAudioAUX3InAUX1Out", (int)emTestAudioAUX3InAUX1Out },
	{ "emTestAudioAUX4InAUX2Out", (int)emTestAudioAUX4InAUX2Out },
	{ "emTestAudioAUX5InAUX2Out", (int)emTestAudioAUX5InAUX2Out },
	{ "emTestAudioAUX6InAUX2Out", (int)emTestAudioAUX6InAUX2Out },
	{ "emTestUSB1Func", (int)emTestUSB1Func },
	{ "emTestUSB2Func", (int)emTestUSB2Func },
	{ "emTestRTCFunc", (int)emTestRTCFunc },
	{ "emTestLightFunc", (int)emTestLightFunc },
	{ "emTestLAN1Func", (int)emTestLAN1Func },
	{ "emTestLAN2Func", (int)emTestLAN2Func },
	{ "emTestRS232LoopbackFunc", (int)emTestRS232LoopbackFunc },
	{ "emTestRS422LoopbackFunc", (int)emTestRS422LoopbackFunc },
	{ "emTestRS485LoopbackFunc", (int)emTestRS485LoopbackFunc },
	{ "emTestRS232ANDCOM1LoopbackFunc", (int)emTestRS232ANDCOM1LoopbackFunc },
	{ "emTestRS422ANDCOM2LoopbackFunc", (int)emTestRS422ANDCOM2LoopbackFunc },
	{ "emTestCOM3ANDCOM4LoopbackFunc", (int)emTestCOM3ANDCOM4LoopbackFunc },
	{ "emTestCOM5ANDCOM6LoopbackFunc", (int)emTestCOM5ANDCOM6LoopbackFunc },
	{ "emTestInfraredRecFunc", (int)emTestInfraredRecFunc },
	{ "emTestInfraredSendFunc", (int)emTestInfraredSendFunc },
	{ "emTestALMLoopBackFunc", (int)emTestALMLoopBackFunc },
	{ "emTestAudioInMain1OutCannon1In", (int)emTestAudioInMain1OutCannon1In },
	{ "emTestAudioInMain1OutCannon2In", (int)emTestAudioInMain1OutCannon2In },
	{ "emTestAudioInMain1OutCannon3In", (int)emTestAudioInMain1OutCannon3In },
	{ "emTestAudioInMain1OutCannon4In", (int)emTestAudioInMain1OutCannon4In },
	{ "emTestAudioInMain1OutCannon5In", (int)emTestAudioInMain1OutCannon5In },
	{ "emTestAudioInMain1OutCannon6In", (int)emTestAudioInMain1OutCannon6In },
	{ "emTestAudioInMain1OutCannon7In", (int)emTestAudioInMain1OutCannon7In },
	{ "emTestAudioInMain1OutCannon8In", (int)emTestAudioInMain1OutCannon8In },
	{ "emTestAudioInMain1OutCannon9In", (int)emTestAudioInMain1OutCannon9In },
	{ "emTestAudioInMain1OutCannon10In", (int)emTestAudioInMain1OutCannon10In },
	{ "emTestAudioOutMainL1OutCannon1In", (int)emTestAudioOutMainL1OutCannon1In },
	{ "emTestAudioOutMainR1OutCannon1In", (int)emTestAudioOutMainR1OutCannon1In },
	{ "emTestAudioOutMainL2OutCannon1In", (int)emTestAudioOutMainL2OutCannon1In },
	{ "emTestAudioOutMainR2OutCannon1In", (int)emTestAudioOutMainR2OutCannon1In },
	{ "emTestAudioOutMainL3OutCannon1In", (int)emTestAudioOutMainL3OutCannon1In },
	{ "emTestAudioOutMainR3OutCannon1In", (int)emTestAudioOutMainR3OutCannon1In },
	{ "emVidMAINIn1_HDMI_MAINOut1_Priom", (int)emVidMAINIn1_HDMI_MAINOut1_Priom },
	{ "emVidMAINIn1_HDMI_MAINOut1_Mini", (int)emVidMAINIn1_HDMI_MAINOut1_Mini },
	{ "emVidSUBIn1_HDMI_MAINOut1_Priom", (int)emVidSUBIn1_HDMI_MAINOut1_Priom },
	{ "emVidSUBIn1_HDMI_MAINOut1_Mini", (int)emVidSUBIn1_HDMI_MAINOut1_Mini },
	{ "emVidMAINIn2_HDMI_MAINOut2_Priom", (int)emVidMAINIn2_HDMI_MAINOut2_Priom },
	{ "emVidMAINIn2_HDMI_MAINOut2_Mini", (int)emVidMAINIn2_HDMI_MAINOut2_Mini },
	{ "emVidSUBIn2_HDMI_MAINOut2_Priom", (int)emVidSUBIn2_HDMI_MAINOut2_Priom },
	{ "emVidSUBIn2_HDMI_MAINOut2_Mini", (int)emVidSUBIn2_HDMI_MAINOut2_Mini },
	{ "emVidMAINIn3_HDMI_MAINOut3_Priom", (int)emVidMAINIn3_HDMI_MAINOut3_Priom },
	{ "emVidMAINIn3_HDMI_MAINOut3_Mini", (int)emVidMAINIn3_HDMI_MAINOut3_Mini },
	{ "emVidSUBIn3_HDMI_MAINOut3_Priom", (int)emVidSUBIn3_HDMI_MAINOut3_Priom },
	{ "emVidSUBIn3_HDMI_MAINOut3_Mini", (int)emVidSUBIn3_HDMI_MAINOut3_Mini },
	{ "emVidAuxIn4_HDMI_MAINOut2_Priom", (int)emVidAuxIn4_HDMI_MAINOut2_Priom },
	{ "emVidAuxIn4_HDMI_MAINOut2_Mini", (int)emVidAuxIn4_HDMI_MAINOut2_Mini },
	{ "emVidSUBIn1_VGA_MAINOut1_Priom", (int)emVidSUBIn1_VGA_MAINOut1_Priom },
	{ "emVidSUBIn1_VGA_MAINOut1_Mini", (int)emVidSUBIn1_VGA_MAINOut1_Mini },
	{ "emVidSUBIn2_VGA_MAINOut2_Priom", (int)emVidSUBIn2_VGA_MAINOut2_Priom },
	{ "emVidSUBIn2_VGA_MAINOut2_Mini", (int)emVidSUBIn2_VGA_MAINOut2_Mini },
	{ "emVidSUBIn3_VGA_MAINOut3_Priom", (int)emVidSUBIn3_VGA_MAINOut3_Priom },
	{ "emVidSUBIn3_VGA_MAINOut3_Mini", (int)emVidSUBIn3_VGA_MAINOut3_Mini },
	{ "emDualAuxIn1_HDMI_AUXOut1", (int)emDualAuxIn1_HDMI_AUXOut1 },
	{ "emDualAuxIn2_HDMI_AUXOut1", (int)emDualAuxIn2_HDMI_AUXOut1 },
	{ "emDualAuxIn3_HDMI_AUXOut2", (int)emDualAuxIn3_HDMI_AUXOut2 },
	{ "emDualAuxIn4_HDMI_AUXOut2", (int)emDualAuxIn4_HDMI_AUXOut2 },
	{ "emDualSDIIn_HDMI_AUXOut2", (int)emDualSDIIn_HDMI_AUXOut2 },
	{ "emDualAuxIn1_VGA_AUXOut1_VGA", (int)emDualAuxIn1_VGA_AUXOut1_VGA },
	{ "emDualAuxIn2_VGA_AUXOut1_VGA", (int)emDualAuxIn2_VGA_AUXOut1_VGA },
	{ "emDualAuxIn3_VGA_AUXOut2_VGA", (int)emDualAuxIn3_VGA_AUXOut2_VGA },
	{ "emDualAuxIn4_HDMI_AUXOut2_VGA", (int)emDualAuxIn4_HDMI_AUXOut2_VGA },
	{ "emT300ERS485Loopback_FirstFunc", (int)emT300ERS485Loopback_FirstFunc },
	{ "emT300ERS485Loopback_SecondFunc", (int)emT300ERS485Loopback_SecondFunc },
	{ "emT300ERS422Loopback_FirstFunc", (int)emT300ERS422Loopback_FirstFunc },
	{ "emT300ERS422Loopback_SecondFunc", (int)emT300ERS422Loopback_SecondFunc },
	{ "emT300ERS232LoopbackFunc", (int)emT300ERS232LoopbackFunc },
	{ "emProducetestTypeEnd", (int)emProducetestTypeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMdyRecFileResDescript[]={
	{ "em_rec_file_unknow", (int)em_rec_file_unknow },
	{ "em_rec_file_success", (int)em_rec_file_success },
	{ "em_rec_file_longnamesize", (int)em_rec_file_longnamesize },
	{ "em_rec_file_inuse", (int)em_rec_file_inuse },
	{ "em_rec_file_nameexist", (int)em_rec_file_nameexist },
	{ "em_rec_file_invalidrecorder", (int)em_rec_file_invalidrecorder },
	{ "em_rec_file_noregisted", (int)em_rec_file_noregisted },
	{ "em_rec_file_invalid_info", (int)em_rec_file_invalid_info },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmUseReccorderResDescript[]={
	{ "em_rec_success", (int)em_rec_success },
	{ "em_rec_invalid", (int)em_rec_invalid },
	{ "em_rec_unregisted", (int)em_rec_unregisted },
	{ "em_rec_no_resource", (int)em_rec_no_resource },
	{ "em_rec_invalid_conf", (int)em_rec_invalid_conf },
	{ "em_rec_invalid_format", (int)em_rec_invalid_format },
	{ "em_rec_unknow_rectype", (int)em_rec_unknow_rectype },
	{ "em_rec_invalid_mt", (int)em_rec_invalid_mt },
	{ "em_rec_recordering", (int)em_rec_recordering },
	{ "em_rec_playing", (int)em_rec_playing },
	{ "em_rec_chair_playing", (int)em_rec_chair_playing },
	{ "em_rec_server_reject", (int)em_rec_server_reject },
	{ "em_rec_invalid_rec_info", (int)em_rec_invalid_rec_info },
	{ "em_rec_invalid_play_info", (int)em_rec_invalid_play_info },
	{ "em_rec_no_in_pause", (int)em_rec_no_in_pause },
	{ "em_rec_mt_offline", (int)em_rec_mt_offline },
	{ "em_rec_name_hasunderline", (int)em_rec_name_hasunderline },
	{ "em_rec_longnamesize", (int)em_rec_longnamesize },
	{ "em_rec_fileexist", (int)em_rec_fileexist },
	{ "em_rec_fileinuse", (int)em_rec_fileinuse },
	{ "em_rec_loadlib_failed", (int)em_rec_loadlib_failed },
	{ "em_rec_setrecmode_failed", (int)em_rec_setrecmode_failed },
	{ "em_rec_publicfailed", (int)em_rec_publicfailed },
	{ "em_rec_inrequesting", (int)em_rec_inrequesting },
	{ "em_rec_req_failed", (int)em_rec_req_failed },
	{ "em_rec_norecord", (int)em_rec_norecord },
	{ "em_rec_file_damange", (int)em_rec_file_damange },
	{ "em_rec_in_stopping", (int)em_rec_in_stopping },
	{ "em_rec_in_pausing", (int)em_rec_in_pausing },
	{ "em_rec_no_in_working", (int)em_rec_no_in_working },
	{ "em_rec_invalid_channel", (int)em_rec_invalid_channel },
	{ "em_rec_unmatch_format", (int)em_rec_unmatch_format },
	{ "em_rec_unknow_reason", (int)em_rec_unknow_reason },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmRecorderTypeDescript[]={
	{ "em_rec_recorder_unknow", (int)em_rec_recorder_unknow },
	{ "em_rec_recorder_conf", (int)em_rec_recorder_conf },
	{ "em_rec_recorder_mt", (int)em_rec_recorder_mt },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmConfRecStateDescript[]={
	{ "em_rec_unknow", (int)em_rec_unknow },
	{ "em_rec_init", (int)em_rec_init },
	{ "em_rec_working", (int)em_rec_working },
	{ "em_rec_pause", (int)em_rec_pause },
	{ "em_rec_finish", (int)em_rec_finish },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpProfileDescript[]={
	{ "emTpProfileBaseline", (int)emTpProfileBaseline },
	{ "emTpProfileMain", (int)emTpProfileMain },
	{ "emTpProfileExtend", (int)emTpProfileExtend },
	{ "emTpProfileHigh", (int)emTpProfileHigh },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPHandleCfgTypeDescript[]={
	{ "emTPShowCfg", (int)emTPShowCfg },
	{ "emTPSetCfg", (int)emTPSetCfg },
	{ "emTPPostCfg", (int)emTPPostCfg },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCodecTypeDescript[]={
	{ "emTpVEnc", (int)emTpVEnc },
	{ "emTpVDec", (int)emTpVDec },
	{ "emTpAEnc", (int)emTpAEnc },
	{ "emTpADec", (int)emTpADec },
	{ "emTpMerge", (int)emTpMerge },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmToolStateDescript[]={
	{ "em_Tool_IDLE", (int)em_Tool_IDLE },
	{ "em_Tool_READY", (int)em_Tool_READY },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAudPlayModeDescript[]={
	{ "emTP_PLAY_FULL", (int)emTP_PLAY_FULL },
	{ "emTP_PLAY_SINGLE", (int)emTP_PLAY_SINGLE },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAudDualInModeDescript[]={
	{ "emTP_AUD_DUAL_AUTO", (int)emTP_AUD_DUAL_AUTO },
	{ "emTP_AUD_DUAL_HDMI", (int)emTP_AUD_DUAL_HDMI },
	{ "emTP_AUD_DUAL_LINEIN", (int)emTP_AUD_DUAL_LINEIN },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDualTypeDescript[]={
	{ "emTP_TPad_DUAL_VEDIO", (int)emTP_TPad_DUAL_VEDIO },
	{ "emTP_DV_DUAL_VEDIO", (int)emTP_DV_DUAL_VEDIO },
	{ "emTP_NONE_DUAL_VEDIO", (int)emTP_NONE_DUAL_VEDIO },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDsNodeDescript[]={
	{ "emTp_Ds", (int)emTp_Ds },
	{ "emTp_Node", (int)emTp_Node },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMScreenLookedDescript[]={
	{ "emScreenInvalid", (int)emScreenInvalid },
	{ "emScreenSelf", (int)emScreenSelf },
	{ "emScreenSpeaker", (int)emScreenSpeaker },
	{ "emScreenPoll", (int)emScreenPoll },
	{ "emScreenView", (int)emScreenView },
	{ "emScreenDiscard", (int)emScreenDiscard },
	{ "emScreenRecPlay", (int)emScreenRecPlay },
	{ "emScreenLookedEnd", (int)emScreenLookedEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmUmsVmpStyleDescript[]={
	{ "em_ums_vmp_invalid", (int)em_ums_vmp_invalid },
	{ "em_ums_vmp_one", (int)em_ums_vmp_one },
	{ "em_ums_vmp_two_pic", (int)em_ums_vmp_two_pic },
	{ "em_ums_vmp_three_pic", (int)em_ums_vmp_three_pic },
	{ "em_ums_vmp_four_pic", (int)em_ums_vmp_four_pic },
	{ "em_ums_vmp_five_pic", (int)em_ums_vmp_five_pic },
	{ "em_ums_vmp_six_pic", (int)em_ums_vmp_six_pic },
	{ "em_ums_vmp_seven_pic", (int)em_ums_vmp_seven_pic },
	{ "em_ums_vmp_eight_pic", (int)em_ums_vmp_eight_pic },
	{ "em_ums_vmp_nine_pic", (int)em_ums_vmp_nine_pic },
	{ "em_ums_vmp_ten_pic", (int)em_ums_vmp_ten_pic },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVmpEncModeDescript[]={
	{ "em_ums_vmp_enc_none", (int)em_ums_vmp_enc_none },
	{ "em_ums_vmp_enc_des", (int)em_ums_vmp_enc_des },
	{ "em_ums_vmp_enc_aes", (int)em_ums_vmp_enc_aes },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVmpShowModeDescript[]={
	{ "ums_vmp_black_mode", (int)ums_vmp_black_mode },
	{ "ums_vmp_lastframe_mode", (int)ums_vmp_lastframe_mode },
	{ "ums_vmp_defaultpic_mode", (int)ums_vmp_defaultpic_mode },
	{ "ums_vmp_userdefpic_mode", (int)ums_vmp_userdefpic_mode },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVmpResDescript[]={
	{ "em_ums_vmp_success", (int)em_ums_vmp_success },
	{ "em_ums_vmp_failed", (int)em_ums_vmp_failed },
	{ "em_ums_vmp_invalid_chan", (int)em_ums_vmp_invalid_chan },
	{ "em_ums_vmp_chan_working", (int)em_ums_vmp_chan_working },
	{ "em_ums_vmp_invalid_param", (int)em_ums_vmp_invalid_param },
	{ "em_ums_vmp_set_param_failed", (int)em_ums_vmp_set_param_failed },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAudPlayModeDescript[]={
	{ "emAudMode_Invalid", (int)emAudMode_Invalid },
	{ "emAudMode_Synchronous", (int)emAudMode_Synchronous },
	{ "emAudMode_NoSynchronous", (int)emAudMode_NoSynchronous },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmResetAudModeDescript[]={
	{ "emResetAudMode_Invalid", (int)emResetAudMode_Invalid },
	{ "emResetAudMode_Start", (int)emResetAudMode_Start },
	{ "emResetAudMode_End", (int)emResetAudMode_End },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCheckAudPakDescript[]={
	{ "emCheckAudPak_Invalid", (int)emCheckAudPak_Invalid },
	{ "emCheckAudPak_End", (int)emCheckAudPak_End },
	{ "emCheckAudPak_Start", (int)emCheckAudPak_Start },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmViewEpTypeDescript[]={
	{ "EmEpType_Invalid", (int)EmEpType_Invalid },
	{ "EmEpType_Ter", (int)EmEpType_Ter },
	{ "EmEpType_Eqp", (int)EmEpType_Eqp },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmViewRetReasonDescript[]={
	{ "EmViewRetReason_Success", (int)EmViewRetReason_Success },
	{ "EmViewRetReason_Selected", (int)EmViewRetReason_Selected },
	{ "EmViewRetReason_UnSelected", (int)EmViewRetReason_UnSelected },
	{ "EmViewRetReason_EpNotLine", (int)EmViewRetReason_EpNotLine },
	{ "EmViewRetReason_DstEpNotLine", (int)EmViewRetReason_DstEpNotLine },
	{ "EmViewRetReason_DstEqpNoExists", (int)EmViewRetReason_DstEqpNoExists },
	{ "EmViewRetReason_SelFull", (int)EmViewRetReason_SelFull },
	{ "EmViewRetReason_EpTypeError", (int)EmViewRetReason_EpTypeError },
	{ "EmViewRetReason_SelDstNoVid", (int)EmViewRetReason_SelDstNoVid },
	{ "EmViewRetReason_SelNoVid", (int)EmViewRetReason_SelNoVid },
	{ "EmViewRetReason_SelDstNotLvl", (int)EmViewRetReason_SelDstNotLvl },
	{ "EmViewRetReason_NoBasRes", (int)EmViewRetReason_NoBasRes },
	{ "EmViewRetReason_InValidEp", (int)EmViewRetReason_InValidEp },
	{ "EmViewRetReason_NoBwRes", (int)EmViewRetReason_NoBwRes },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmUITypeDescript[]={
	{ "EmUI_CNC", (int)EmUI_CNC },
	{ "EmUI_UMC", (int)EmUI_UMC },
	{ "EmUI_Tools", (int)EmUI_Tools },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGetVidResDescript[]={
	{ "em_GetVid_Success", (int)em_GetVid_Success },
	{ "em_GetVid_Invalid_Param", (int)em_GetVid_Invalid_Param },
	{ "em_GetVid_No_BandWidth", (int)em_GetVid_No_BandWidth },
	{ "em_GetVid_No_AddrResource", (int)em_GetVid_No_AddrResource },
	{ "em_GetVide_No_BasResource", (int)em_GetVide_No_BasResource },
	{ "em_GitVid_No_Resource", (int)em_GitVid_No_Resource },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmBrdVmpRetDescript[]={
	{ "EmBrdVmpRet_Succes", (int)EmBrdVmpRet_Succes },
	{ "EmBrdVmpRet_Busy", (int)EmBrdVmpRet_Busy },
	{ "EmBrdVmpRet_NoExist", (int)EmBrdVmpRet_NoExist },
	{ "EmBrdVmpRet_Fail", (int)EmBrdVmpRet_Fail },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmBrdVmpStatDescript[]={
	{ "EmBrdVmpStat_Invalid", (int)EmBrdVmpStat_Invalid },
	{ "EmBrdVmpStat_Idle", (int)EmBrdVmpStat_Idle },
	{ "EmBrdVmpStat_Normal", (int)EmBrdVmpStat_Normal },
	{ "EmBrdVmpStat_Brd", (int)EmBrdVmpStat_Brd },
	{ "EmBrdVmpStat_Error", (int)EmBrdVmpStat_Error },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmRervesVmpRetDescript[]={
	{ "EmRervesVmpRet_Success", (int)EmRervesVmpRet_Success },
	{ "EmRervesVmpRet_DisCnnt", (int)EmRervesVmpRet_DisCnnt },
	{ "EmRervesVmpRet_ResFull", (int)EmRervesVmpRet_ResFull },
	{ "EmRervesVmpRet_Busy", (int)EmRervesVmpRet_Busy },
	{ "EmRervesVmpRet_NoExist", (int)EmRervesVmpRet_NoExist },
	{ "EmRervesVmpRet_unKnow", (int)EmRervesVmpRet_unKnow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnmpLogTypeDescript[]={
	{ "EmCnmpLogType_Off", (int)EmCnmpLogType_Off },
	{ "EmCnmpLogType_All", (int)EmCnmpLogType_All },
	{ "EmCnmpLogType_VSend", (int)EmCnmpLogType_VSend },
	{ "EmCnmpLogType_VRcv", (int)EmCnmpLogType_VRcv },
	{ "EmCnmpLogType_ASend", (int)EmCnmpLogType_ASend },
	{ "EmCnmpLogType_ARcv", (int)EmCnmpLogType_ARcv },
	{ "EmCnmpLogType_KeyFrame", (int)EmCnmpLogType_KeyFrame },
	{ "EmCnmpLogType_VMSend", (int)EmCnmpLogType_VMSend },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnmpLogCtDescript[]={
	{ "EmCnmpLogCt_First", (int)EmCnmpLogCt_First },
	{ "EmCnmpLogCt_Second", (int)EmCnmpLogCt_Second },
	{ "EmCnmpLogCt_Third", (int)EmCnmpLogCt_Third },
	{ "EmCnmpLogCt_Fourth", (int)EmCnmpLogCt_Fourth },
	{ "EmCnmpLogCt_Fifth", (int)EmCnmpLogCt_Fifth },
	{ "EmCnmpLogCt_All", (int)EmCnmpLogCt_All },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAudAecTypeDescript[]={
	{ "EmTpAec", (int)EmTpAec },
	{ "EmTpAns", (int)EmTpAns },
	{ "EmTpAgc", (int)EmTpAgc },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGetVidTypeDescript[]={
	{ "em_GetVid_Invalid", (int)em_GetVid_Invalid },
	{ "em_GetVid_View", (int)em_GetVid_View },
	{ "em_GetVid_Poll", (int)em_GetVid_Poll },
	{ "em_GetVid_Vmp", (int)em_GetVid_Vmp },
	{ "em_GetVid_Hdu", (int)em_GetVid_Hdu },
	{ "em_GetVid_Dis", (int)em_GetVid_Dis },
	{ "em_GetVid_ViewEp", (int)em_GetVid_ViewEp },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVidEncResizeModeDescript[]={
	{ "EmTpBlackSide", (int)EmTpBlackSide },
	{ "EmTpCuttingEdge", (int)EmTpCuttingEdge },
	{ "EmTpNonGeometricDrawing", (int)EmTpNonGeometricDrawing },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpVendorIDDescript[]={
	{ "EmTp_vendor_MICROSOFT_NETMEETING", (int)EmTp_vendor_MICROSOFT_NETMEETING },
	{ "EmTp_vendor_KEDA", (int)EmTp_vendor_KEDA },
	{ "EmTp_vendor_KEDA_IPC", (int)EmTp_vendor_KEDA_IPC },
	{ "EmTp_vendor_HUAWEI", (int)EmTp_vendor_HUAWEI },
	{ "EmTp_vendor_POLYCOM", (int)EmTp_vendor_POLYCOM },
	{ "EmTp_vendor_POLYCOM_MCU", (int)EmTp_vendor_POLYCOM_MCU },
	{ "EmTp_vendor_TANDBERG", (int)EmTp_vendor_TANDBERG },
	{ "EmTp_vendor_RADVISION", (int)EmTp_vendor_RADVISION },
	{ "EmTp_vendor_VCON", (int)EmTp_vendor_VCON },
	{ "EmTp_vendor_SONY", (int)EmTp_vendor_SONY },
	{ "EmTp_vendor_VTEL", (int)EmTp_vendor_VTEL },
	{ "EmTp_vendor_ZTE", (int)EmTp_vendor_ZTE },
	{ "EmTp_vendor_ZTE_MCU", (int)EmTp_vendor_ZTE_MCU },
	{ "EmTp_vendor_CODIAN", (int)EmTp_vendor_CODIAN },
	{ "EmTp_vendor_AETHRA", (int)EmTp_vendor_AETHRA },
	{ "EmTp_vendor_CHAORAN", (int)EmTp_vendor_CHAORAN },
	{ "EmTp_vendor_UNKNOWN", (int)EmTp_vendor_UNKNOWN },
	{ "EmTp_vendor_END", (int)EmTp_vendor_END },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMScreenObjDescript[]={
	{ "emObjSelf", (int)emObjSelf },
	{ "emObjSpeaker", (int)emObjSpeaker },
	{ "emObjChair", (int)emObjChair },
	{ "emObjPoll", (int)emObjPoll },
	{ "emObjView", (int)emObjView },
	{ "emObjDiscard", (int)emObjDiscard },
	{ "emObjVmpBrd", (int)emObjVmpBrd },
	{ "emObjLookedEnd", (int)emObjLookedEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpBannerTransparencyDescript[]={
	{ "EmTpFullTransparent", (int)EmTpFullTransparent },
	{ "EmTpTranslucent", (int)EmTpTranslucent },
	{ "EmTpOpaque", (int)EmTpOpaque },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpBannerTypeDescript[]={
	{ "EmTpBannerType0", (int)EmTpBannerType0 },
	{ "EmTpBannerType1", (int)EmTpBannerType1 },
	{ "EmTpBannerType2", (int)EmTpBannerType2 },
	{ "EmTpBannerType3", (int)EmTpBannerType3 },
	{ "EmTpBannerType4", (int)EmTpBannerType4 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpLogoTypeDescript[]={
	{ "EmTpLogoType_UpperLeft", (int)EmTpLogoType_UpperLeft },
	{ "EmTpLogoType_UpperMid", (int)EmTpLogoType_UpperMid },
	{ "EmTpLogoType_UpperRight", (int)EmTpLogoType_UpperRight },
	{ "EmTpLogoType_LowerLeft", (int)EmTpLogoType_LowerLeft },
	{ "EmTpLogoType_LowerMid", (int)EmTpLogoType_LowerMid },
	{ "EmTpLogoType_LowerRight", (int)EmTpLogoType_LowerRight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpSnapShotTypeDescript[]={
	{ "EmTpSnatShot_ThreeVideo", (int)EmTpSnatShot_ThreeVideo },
	{ "EmTpSnatShot_PanoramicCamera", (int)EmTpSnatShot_PanoramicCamera },
	{ "EmTpSnatShot_Docamera", (int)EmTpSnatShot_Docamera },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCtrlModeDescript[]={
	{ "emTpModeInvalid", (int)emTpModeInvalid },
	{ "emTpModeCommand", (int)emTpModeCommand },
	{ "emTpModeRequest", (int)emTpModeRequest },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDiscussOprResDescript[]={
	{ "em_Disucss_Opr_Successed", (int)em_Disucss_Opr_Successed },
	{ "em_Discuss_Invalid_Ep", (int)em_Discuss_Invalid_Ep },
	{ "em_Discuss_Screen_Full", (int)em_Discuss_Screen_Full },
	{ "em_Disccuss_GetVid_Error", (int)em_Disccuss_GetVid_Error },
	{ "em_Discuss_No_BandWith", (int)em_Discuss_No_BandWith },
	{ "em_Discuss_AssignAudChan_Error", (int)em_Discuss_AssignAudChan_Error },
	{ "em_Discuss_No_MixChan", (int)em_Discuss_No_MixChan },
	{ "em_Discuss_OtherFail", (int)em_Discuss_OtherFail },
	{ "em_Disccuss_Opr_End", (int)em_Disccuss_Opr_End },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDiscussRspRetDescript[]={
	{ "em_DiscussOprRsp_Ok", (int)em_DiscussOprRsp_Ok },
	{ "em_Start_AssginVmpFail", (int)em_Start_AssginVmpFail },
	{ "em_Start_AssignMixFail", (int)em_Start_AssignMixFail },
	{ "em_Start_AssignBasFail", (int)em_Start_AssignBasFail },
	{ "em_Start_OtherFail", (int)em_Start_OtherFail },
	{ "em_Start_RollCall_Mode", (int)em_Start_RollCall_Mode },
	{ "em_Start_ConfAudMix_Mode", (int)em_Start_ConfAudMix_Mode },
	{ "em_DiscussOprRsp_End", (int)em_DiscussOprRsp_End },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamProTypeDescript[]={
	{ "emDcamInvalid", (int)emDcamInvalid },
	{ "emVISCAPro", (int)emVISCAPro },
	{ "emPELCOPro", (int)emPELCOPro },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmIconTypeDescript[]={
	{ "em_Icon_PackLost", (int)em_Icon_PackLost },
	{ "em_Icon_NetIsSue", (int)em_Icon_NetIsSue },
	{ "em_Icon_Max", (int)em_Icon_Max },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAudMixTypeDescript[]={
	{ "em_Mix_Local", (int)em_Mix_Local },
	{ "em_Mix_Peer", (int)em_Mix_Peer },
	{ "em_Mix_LP", (int)em_Mix_LP },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAudExtendDescript[]={
	{ "em_Conf_Mix", (int)em_Conf_Mix },
	{ "em_Local_Extend", (int)em_Local_Extend },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmRollCallRspRetDescript[]={
	{ "em_RollCallOprRsp_Ok", (int)em_RollCallOprRsp_Ok },
	{ "em_StartRollCall_begin", (int)em_StartRollCall_begin },
	{ "em_StartRollCall_AssignMixFail", (int)em_StartRollCall_AssignMixFail },
	{ "em_StartRollCall_DisMode", (int)em_StartRollCall_DisMode },
	{ "em_StartRollCall_ConfAudMixMode", (int)em_StartRollCall_ConfAudMixMode },
	{ "em_StartRollCall_AlreadyStart", (int)em_StartRollCall_AlreadyStart },
	{ "em_StartRollCall_AssignAddrFail", (int)em_StartRollCall_AssignAddrFail },
	{ "em_StartRollCall_NotTopUms", (int)em_StartRollCall_NotTopUms },
	{ "em_StartRollCall_CreateChanFail", (int)em_StartRollCall_CreateChanFail },
	{ "em_StartRollCall_OtherFail", (int)em_StartRollCall_OtherFail },
	{ "em_UpdateRollCalList_begin", (int)em_UpdateRollCalList_begin },
	{ "em_UpdateRollCalList_ListFull", (int)em_UpdateRollCalList_ListFull },
	{ "em_UpdateRollCalList_NotTopUms", (int)em_UpdateRollCalList_NotTopUms },
	{ "em_UpdateRollCalList_InvalidEp", (int)em_UpdateRollCalList_InvalidEp },
	{ "em_UpdateRollCalList_EpoffLine", (int)em_UpdateRollCalList_EpoffLine },
	{ "em_UpdateRollCalList_Fail", (int)em_UpdateRollCalList_Fail },
	{ "em_RollCallNextEp_begin", (int)em_RollCallNextEp_begin },
	{ "em_RollCallNextEp_NotStart", (int)em_RollCallNextEp_NotStart },
	{ "em_RollCallNextEp_NotTopUms", (int)em_RollCallNextEp_NotTopUms },
	{ "em_RollCallNextEp_CallerChg", (int)em_RollCallNextEp_CallerChg },
	{ "em_RollCallNextEp_EpError", (int)em_RollCallNextEp_EpError },
	{ "em_RollCallNextEp_CreateChanFail", (int)em_RollCallNextEp_CreateChanFail },
	{ "em_RollCallNextEp_OtherFail", (int)em_RollCallNextEp_OtherFail },
	{ "em_RollcallNotify_begin", (int)em_RollcallNotify_begin },
	{ "em_Error_StopRollCall", (int)em_Error_StopRollCall },
	{ "em_RollCallMixer_Error", (int)em_RollCallMixer_Error },
	{ "em_RollCaller_OffLine", (int)em_RollCaller_OffLine },
	{ "em_RollCallTarget_OffLine", (int)em_RollCallTarget_OffLine },
	{ "em_CallTarget_ReConnect_Success", (int)em_CallTarget_ReConnect_Success },
	{ "em_Chair_ReConnect_notice", (int)em_Chair_ReConnect_notice },
	{ "em_RollCallOprRsp_End", (int)em_RollCallOprRsp_End },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAudMixModeDescript[]={
	{ "em_umsaudmixmode_idle", (int)em_umsaudmixmode_idle },
	{ "em_umsaudmixmode_smart", (int)em_umsaudmixmode_smart },
	{ "em_umsaudmixmode_custom", (int)em_umsaudmixmode_custom },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAudMixListOprDescript[]={
	{ "em_umsaudmixlistopr_add", (int)em_umsaudmixlistopr_add },
	{ "em_umsaudmixlistopr_del", (int)em_umsaudmixlistopr_del },
	{ "em_umsaudmixlistopr_unkown", (int)em_umsaudmixlistopr_unkown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAudMixResDescript[]={
	{ "em_umsaudmixres_sucess", (int)em_umsaudmixres_sucess },
	{ "em_umsaudmixres_listopr_begin", (int)em_umsaudmixres_listopr_begin },
	{ "em_umsaudmixres_add_invalidep", (int)em_umsaudmixres_add_invalidep },
	{ "em_umsaudmixres_add_getaudfail", (int)em_umsaudmixres_add_getaudfail },
	{ "em_umsaudmixres_add_assignaudfail", (int)em_umsaudmixres_add_assignaudfail },
	{ "em_umsaudmixres_add_mixchanfull", (int)em_umsaudmixres_add_mixchanfull },
	{ "em_umsaudmixres_add_repeatadd", (int)em_umsaudmixres_add_repeatadd },
	{ "em_umsaudmixres_del_notfind", (int)em_umsaudmixres_del_notfind },
	{ "em_umsaudmixres_modeopr_begin", (int)em_umsaudmixres_modeopr_begin },
	{ "em_umsaudmixres_start_nomix", (int)em_umsaudmixres_start_nomix },
	{ "em_umsaudmixres_start_novalidep", (int)em_umsaudmixres_start_novalidep },
	{ "em_umsaudmixres_samemode", (int)em_umsaudmixres_samemode },
	{ "em_umsaudmixres_unauthorized", (int)em_umsaudmixres_unauthorized },
	{ "em_umsaudmixres_dismode", (int)em_umsaudmixres_dismode },
	{ "em_umsaudmixres_rollcallmode", (int)em_umsaudmixres_rollcallmode },
	{ "em_umsaudmixres_unkown", (int)em_umsaudmixres_unkown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmRollCallPresentStateDescript[]={
	{ "em_RollCallPresentState_Ok", (int)em_RollCallPresentState_Ok },
	{ "em_RollCallPresentState_Target", (int)em_RollCallPresentState_Target },
	{ "em_RollCallPresentState_Absent", (int)em_RollCallPresentState_Absent },
	{ "em_RollCallPresentState_OffLine", (int)em_RollCallPresentState_OffLine },
	{ "em_RollCallPresentState_PendingTarget", (int)em_RollCallPresentState_PendingTarget },
	{ "em_RollCallPresentState_OtherFail", (int)em_RollCallPresentState_OtherFail },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVidMergeStyleDescript[]={
	{ "em_MERGE_M1", (int)em_MERGE_M1 },
	{ "em_MERGE_M3", (int)em_MERGE_M3 },
	{ "em_MERGE_M4", (int)em_MERGE_M4 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMeetingRoomSizeDescript[]={
	{ "em_MR_Close", (int)em_MR_Close },
	{ "em_MR_1080P", (int)em_MR_1080P },
	{ "em_MR_720P", (int)em_MR_720P },
	{ "em_MR_4CIF", (int)em_MR_4CIF },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAudGroupIndexDescript[]={
	{ "em_GroupNum1", (int)em_GroupNum1 },
	{ "em_GroupNum2", (int)em_GroupNum2 },
	{ "em_GroupNum3", (int)em_GroupNum3 },
	{ "em_GroupNum4", (int)em_GroupNum4 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmUpdateFrequencyDescript[]={
	{ "em_OneMonth", (int)em_OneMonth },
	{ "em_TwoMonths", (int)em_TwoMonths },
	{ "em_ThreeMonths", (int)em_ThreeMonths },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmQCamProTypeDescript[]={
	{ "emQamInvalid", (int)emQamInvalid },
	{ "em120E", (int)em120E },
	{ "emMoon50", (int)emMoon50 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmP2PCallStrategyLevelDescript[]={
	{ "emHangUpAfterCall_Level1", (int)emHangUpAfterCall_Level1 },
	{ "emCallSuccNoStream_Level2", (int)emCallSuccNoStream_Level2 },
	{ "emCallSuccPartStream_Level3", (int)emCallSuccPartStream_Level3 },
	{ "emCallSuccTroubleStream_Level4", (int)emCallSuccTroubleStream_Level4 },
	{ "emNormalPairNormalStream_Level8", (int)emNormalPairNormalStream_Level8 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMDS_SUBTYPEDescript[]={
	{ "emDS_SubType_Unknow", (int)emDS_SubType_Unknow },
	{ "emDS_SubType_RTP", (int)emDS_SubType_RTP },
	{ "emDS_SubType_RTCP", (int)emDS_SubType_RTCP },
	{ (char*)NULL, (int)-1 }
};

//枚举描述字符串表
TXENUMINFO* enumTpXDescript[]={
	(TXENUMINFO*)enumEmTPDevRegUpdateSerDescript, 
	(TXENUMINFO*)enumEmTPUpdateTypeDescript, 
	(TXENUMINFO*)enumEmWiFiLinkStatDescript, 
	(TXENUMINFO*)enumEmWiFiSelTypeDescript, 
	(TXENUMINFO*)enumEmWiFiNetTypeDescript, 
	(TXENUMINFO*)enumEmWiFiEncryptTypeDescript, 
	(TXENUMINFO*)enumEmWiFiEncryptArithmeticDescript, 
	(TXENUMINFO*)enumEmVODRejCodeDescript, 
	(TXENUMINFO*)enumEmVODStateDescript, 
	(TXENUMINFO*)enumEmTextAlignDescript, 
	(TXENUMINFO*)enumEmRollModeDescript, 
	(TXENUMINFO*)enumEmRollSpeedDescript, 
	(TXENUMINFO*)enumEmStopBitsDescript, 
	(TXENUMINFO*)enumEmParityCheckDescript, 
	(TXENUMINFO*)enumEmSerialTypeDescript, 
	(TXENUMINFO*)enumEmLanguageDescript, 
	(TXENUMINFO*)enumEmConfProtocolDescript, 
	(TXENUMINFO*)enumEmEncodeModeDescript, 
	(TXENUMINFO*)enumEmLostPackageRestoreDescript, 
	(TXENUMINFO*)enumEmMatrixTypeDescript, 
	(TXENUMINFO*)enumEmDualVideoShowModeDescript, 
	(TXENUMINFO*)enumEmDisplayRatioDescript, 
	(TXENUMINFO*)enumEmVideoTypeDescript, 
	(TXENUMINFO*)enumEmVideoStandardDescript, 
	(TXENUMINFO*)enumEmVideoInterfaceDescript, 
	(TXENUMINFO*)enumEmMtVideoPortDescript, 
	(TXENUMINFO*)enumEmTripModeDescript, 
	(TXENUMINFO*)enumEmLabelTypeDescript, 
	(TXENUMINFO*)enumEmDLProtocolDescript, 
	(TXENUMINFO*)enumEmAuthenticationTypeDescript, 
	(TXENUMINFO*)enumEmFrameUnitTypeDescript, 
	(TXENUMINFO*)enumEmMediaTypeDescript, 
	(TXENUMINFO*)enumEmVideoFormatDescript, 
	(TXENUMINFO*)enumEmAudioFormatDescript, 
	(TXENUMINFO*)enumEmVideoResolutionDescript, 
	(TXENUMINFO*)enumEmQoSDescript, 
	(TXENUMINFO*)enumEmTOSDescript, 
	(TXENUMINFO*)enumEmSiteDescript, 
	(TXENUMINFO*)enumEmChanTypeDescript, 
	(TXENUMINFO*)enumEmCodecComponentDescript, 
	(TXENUMINFO*)enumEmMtModelDescript, 
	(TXENUMINFO*)enumEmFileSysDescript, 
	(TXENUMINFO*)enumEmEncryptArithmeticDescript, 
	(TXENUMINFO*)enumEmActionDescript, 
	(TXENUMINFO*)enumEmOptRetDescript, 
	(TXENUMINFO*)enumEmConfModeDescript, 
	(TXENUMINFO*)enumEmMtAddrTypeDescript, 
	(TXENUMINFO*)enumEmDirectionDescript, 
	(TXENUMINFO*)enumEmCallStateDescript, 
	(TXENUMINFO*)enumEmCallSiteStateDescript, 
	(TXENUMINFO*)enumEmTransModeDescript, 
	(TXENUMINFO*)enumEmMtInstTypeDescript, 
	(TXENUMINFO*)enumEmVMPStyleDescript, 
	(TXENUMINFO*)enumEmVMPMmbTypeDescript, 
	(TXENUMINFO*)enumEmSMSTypeDescript, 
	(TXENUMINFO*)enumEmMtFileDescript, 
	(TXENUMINFO*)enumEmCallRateDescript, 
	(TXENUMINFO*)enumEmPCCapFormatDescript, 
	(TXENUMINFO*)enumEmPiPModeDescript, 
	(TXENUMINFO*)enumEmDVBComponentDescript, 
	(TXENUMINFO*)enumEmUIPosionDescript, 
	(TXENUMINFO*)enumEmCallDisconnectReasonDescript, 
	(TXENUMINFO*)enumEmMCModeDescript, 
	(TXENUMINFO*)enumEmInnerVMPStyleDescript, 
	(TXENUMINFO*)enumEmVMPComponentDescript, 
	(TXENUMINFO*)enumEmCapTypeDescript, 
	(TXENUMINFO*)enumEmPPPoEStateDescript, 
	(TXENUMINFO*)enumEmDhcpStateDescript, 
	(TXENUMINFO*)enumEmAddrGroupOptTypeDescript, 
	(TXENUMINFO*)enumEmHotKeyTypeDescript, 
	(TXENUMINFO*)enumEmMtOSTypeDescript, 
	(TXENUMINFO*)enumEmFxoStateDescript, 
	(TXENUMINFO*)enumEmMtLoudspeakerValDescript, 
	(TXENUMINFO*)enumEmNetTypeDescript, 
	(TXENUMINFO*)enumEmSysRunSuccessFlagDescript, 
	(TXENUMINFO*)enumEmMcuNtfMsgTypeDescript, 
	(TXENUMINFO*)enumEmAutoTestTypeDescript, 
	(TXENUMINFO*)enumEmGKRegFailedReasonDescript, 
	(TXENUMINFO*)enumEmSleepStateDescript, 
	(TXENUMINFO*)enumEmMtAppNameDescript, 
	(TXENUMINFO*)enumHD_PORT_MASKDescript, 
	(TXENUMINFO*)enumEmHDAudPortInDescript, 
	(TXENUMINFO*)enumEmHDAudPortOutDescript, 
	(TXENUMINFO*)enumEmLogStatusDescript, 
	(TXENUMINFO*)enumEmLogExportResultDescript, 
	(TXENUMINFO*)enumEmFecModeTypeDescript, 
	(TXENUMINFO*)enumEmLabelPosTypeDescript, 
	(TXENUMINFO*)enumEmMtcBoxCallIndexDescript, 
	(TXENUMINFO*)enumEmSipRegFailedReasonDescript, 
	(TXENUMINFO*)enumEMtRecChnnlStateDescript, 
	(TXENUMINFO*)enumEMtRecChnnlTypeDescript, 
	(TXENUMINFO*)enumEMtRecModeDescript, 
	(TXENUMINFO*)enumEMtRecEnumDescript, 
	(TXENUMINFO*)enumEmMtRegResultDescript, 
	(TXENUMINFO*)enumEmTpRetDescript, 
	(TXENUMINFO*)enumEmTpHduPlayNackReasonDescript, 
	(TXENUMINFO*)enumEmTpHduSetVolResDescript, 
	(TXENUMINFO*)enumEmTpLoginUmsRetDescript, 
	(TXENUMINFO*)enumEmTpAliasTypeDescript, 
	(TXENUMINFO*)enumEmTpOprTypeDescript, 
	(TXENUMINFO*)enumEmConfAddEpRetDescript, 
	(TXENUMINFO*)enumEmTpIFrameCheckTypeDescript, 
	(TXENUMINFO*)enumEmTPEncryptTypeDescript, 
	(TXENUMINFO*)enumEmQtEncryptFrequencyDescript, 
	(TXENUMINFO*)enumEmTPQTReasonDescript, 
	(TXENUMINFO*)enumEmTPRcvAlignTypeDescript, 
	(TXENUMINFO*)enumEmCnsCallReasonDescript, 
	(TXENUMINFO*)enumEmTPChannelReasonDescript, 
	(TXENUMINFO*)enumEmTpCnsTypeDescript, 
	(TXENUMINFO*)enumEmTpCnsRegUmsDescript, 
	(TXENUMINFO*)enumEmTpConfTemplateRetDescript, 
	(TXENUMINFO*)enumEmTpStartConfRetDescript, 
	(TXENUMINFO*)enumEmTpApplySpeakerRetDescript, 
	(TXENUMINFO*)enumEmTpDropConfRetDescript, 
	(TXENUMINFO*)enumEmTpApplySpeakRetDescript, 
	(TXENUMINFO*)enumEmUmsConfNodeStateDescript, 
	(TXENUMINFO*)enumEmFlowCtrlOprDescript, 
	(TXENUMINFO*)enumEMBrdTypeDescript, 
	(TXENUMINFO*)enumEMEqpTypeDescript, 
	(TXENUMINFO*)enumEMEqpModleTypeDescript, 
	(TXENUMINFO*)enumEMOsTypeDescript, 
	(TXENUMINFO*)enumEMVmpStyleDescript, 
	(TXENUMINFO*)enumEmTpVideoFormatDescript, 
	(TXENUMINFO*)enumEmTpEncodeModeDescript, 
	(TXENUMINFO*)enumEmTpVideoQualityLevelDescript, 
	(TXENUMINFO*)enumEmTpCallLevelDescript, 
	(TXENUMINFO*)enumEmTpVideoResolutionDescript, 
	(TXENUMINFO*)enumEmTpMediaTypeDescript, 
	(TXENUMINFO*)enumEmTpPCCapFormatDescript, 
	(TXENUMINFO*)enumEmTpCodecComponentDescript, 
	(TXENUMINFO*)enumEmTpAudioFormatDescript, 
	(TXENUMINFO*)enumEmTpLostPackageRestoreDescript, 
	(TXENUMINFO*)enumEmTpCallModeDescript, 
	(TXENUMINFO*)enumEmTpConnectionTypeDescript, 
	(TXENUMINFO*)enumEmTpConfProtocolDescript, 
	(TXENUMINFO*)enumEmTPAddrTypeDescript, 
	(TXENUMINFO*)enumEmTPEndpointTypeDescript, 
	(TXENUMINFO*)enumEmTPSipLevelDescript, 
	(TXENUMINFO*)enumEmCALLSTATEDescript, 
	(TXENUMINFO*)enumEmCallTypeDescript, 
	(TXENUMINFO*)enumEmTPVideoTypeDescript, 
	(TXENUMINFO*)enumEmTPVideoPortDescript, 
	(TXENUMINFO*)enumEmTPCNSInfoRstDescript, 
	(TXENUMINFO*)enumEmTPRegResultDescript, 
	(TXENUMINFO*)enumEmCnMtRegResultDescript, 
	(TXENUMINFO*)enumEmCnModelDescript, 
	(TXENUMINFO*)enumEmFocusModeDescript, 
	(TXENUMINFO*)enumEmSensitivityDescript, 
	(TXENUMINFO*)enumEmFocusDescript, 
	(TXENUMINFO*)enumEmZoomDescript, 
	(TXENUMINFO*)enumEmZoomStatusDescript, 
	(TXENUMINFO*)enumEmCnActionDescript, 
	(TXENUMINFO*)enumEmOSDShowDescript, 
	(TXENUMINFO*)enumEmWBModeDescript, 
	(TXENUMINFO*)enumEmExpModeDescript, 
	(TXENUMINFO*)enumEmGainDescript, 
	(TXENUMINFO*)enumEmShutSpdDescript, 
	(TXENUMINFO*)enumEmAntiFlickerDescript, 
	(TXENUMINFO*)enumEmSpotLighetDescript, 
	(TXENUMINFO*)enumEmBackLightTypeDescript, 
	(TXENUMINFO*)enumEmWideDynamicsDescript, 
	(TXENUMINFO*)enumEmPicSceModeDescript, 
	(TXENUMINFO*)enumEmGammaDescript, 
	(TXENUMINFO*)enumEmStmCleanDescript, 
	(TXENUMINFO*)enumEm3DNRDescript, 
	(TXENUMINFO*)enumEmPicEffectDescript, 
	(TXENUMINFO*)enumEmPicFlipDescript, 
	(TXENUMINFO*)enumEmPicModeDescript, 
	(TXENUMINFO*)enumEmResolutionDescript, 
	(TXENUMINFO*)enumEmBaudRateDescript, 
	(TXENUMINFO*)enumEmCamPowerModeDescript, 
	(TXENUMINFO*)enumEmCenSchModeDescript, 
	(TXENUMINFO*)enumEmSonyIrisDescript, 
	(TXENUMINFO*)enumEmMoon904K60IrisDescript, 
	(TXENUMINFO*)enumEmCamTypeDescript, 
	(TXENUMINFO*)enumEmCamCfgTypeDescript, 
	(TXENUMINFO*)enumEmTvPowerModeDescript, 
	(TXENUMINFO*)enumEmTvSrcPowerModeDescript, 
	(TXENUMINFO*)enumEmTVAudVisModeDescript, 
	(TXENUMINFO*)enumEmTVDisplayModeDescript, 
	(TXENUMINFO*)enumEmTVInputSelectDescript, 
	(TXENUMINFO*)enumEmDCamWBModeDescript, 
	(TXENUMINFO*)enumEmDCamAFModeDescript, 
	(TXENUMINFO*)enumEmDCamPowerDescript, 
	(TXENUMINFO*)enumEmDCamZoomDescript, 
	(TXENUMINFO*)enumEmDCamPresetNumDescript, 
	(TXENUMINFO*)enumEmDCamRecallNumDescript, 
	(TXENUMINFO*)enumEmDCamGainDescript, 
	(TXENUMINFO*)enumEmDCamShutSpdDescript, 
	(TXENUMINFO*)enumEmDCamIrisDescript, 
	(TXENUMINFO*)enumEmSchPowerDescript, 
	(TXENUMINFO*)enumEmSchLightDescript, 
	(TXENUMINFO*)enumEmSchMidLightDescript, 
	(TXENUMINFO*)enumEmSchScrLightDescript, 
	(TXENUMINFO*)enumEmSchCameraAndTVPowerDescript, 
	(TXENUMINFO*)enumEmSchArgusDescript, 
	(TXENUMINFO*)enumEmCentreACPowerDescript, 
	(TXENUMINFO*)enumEmCentreACAirVolDescript, 
	(TXENUMINFO*)enumEmCentreACModeDescript, 
	(TXENUMINFO*)enumEmCurActionDescript, 
	(TXENUMINFO*)enumEmCurChannelModeDescript, 
	(TXENUMINFO*)enumEmSchGatewayTypeDescript, 
	(TXENUMINFO*)enumEmTpMixStatusDescript, 
	(TXENUMINFO*)enumEmTPDualReasonDescript, 
	(TXENUMINFO*)enumEmTPPayloadTypeDescript, 
	(TXENUMINFO*)enumEmTPPosStatusDescript, 
	(TXENUMINFO*)enumEmTPPollResultDescript, 
	(TXENUMINFO*)enumEmPollStatDescript, 
	(TXENUMINFO*)enumEmTPViewResultDescript, 
	(TXENUMINFO*)enumEmTPViewLocalResultDescript, 
	(TXENUMINFO*)enumEmTPDisOprTypeDescript, 
	(TXENUMINFO*)enumEMPosPicDescript, 
	(TXENUMINFO*)enumEMDSCREATETYPEDescript, 
	(TXENUMINFO*)enumEmTPAddDualRcvResultDescript, 
	(TXENUMINFO*)enumEmTPDeleteDualRcvResultDescript, 
	(TXENUMINFO*)enumEmTPMtModelDescript, 
	(TXENUMINFO*)enumEmDsTypeDescript, 
	(TXENUMINFO*)enumEmCnAudioMixIDDescript, 
	(TXENUMINFO*)enumEmGetRegInfoTypeDescript, 
	(TXENUMINFO*)enumEmGetRegInfoOprDescript, 
	(TXENUMINFO*)enumEmTPChanTypeDescript, 
	(TXENUMINFO*)enumEmTPAACSampleFreqDescript, 
	(TXENUMINFO*)enumEmTPG7221RateDescript, 
	(TXENUMINFO*)enumEmTPAACChnlCfgDescript, 
	(TXENUMINFO*)enumEmTPTpApplySpeakerRetDescript, 
	(TXENUMINFO*)enumEmTPChanSubTypeDescript, 
	(TXENUMINFO*)enumEmMakeCallTypeDescript, 
	(TXENUMINFO*)enumEmTpRegTypeDescript, 
	(TXENUMINFO*)enumEmDisListOprTypeDescript, 
	(TXENUMINFO*)enumEmDisListOprResltDescript, 
	(TXENUMINFO*)enumEmVgaTypeDescript, 
	(TXENUMINFO*)enumEmDualInputTypeDescript, 
	(TXENUMINFO*)enumEmDualOutputTypeDescript, 
	(TXENUMINFO*)enumEmVgaSwitchResultDescript, 
	(TXENUMINFO*)enumEmVgaSwitchReasonDescript, 
	(TXENUMINFO*)enumEmCnStateDescript, 
	(TXENUMINFO*)enumEmTPCapSignDescript, 
	(TXENUMINFO*)enumEmSwitchStateDescript, 
	(TXENUMINFO*)enumEmTpBoardRetDescript, 
	(TXENUMINFO*)enumEmHduOutPortDescript, 
	(TXENUMINFO*)enumEmHduZoomRateDescript, 
	(TXENUMINFO*)enumEmHduOutModeDescript, 
	(TXENUMINFO*)enumEmHduShowModeDescript, 
	(TXENUMINFO*)enumEmModifyNMServerRetDescript, 
	(TXENUMINFO*)enumEmModifyVcrRetDescript, 
	(TXENUMINFO*)enumEmModifyHduRetDescript, 
	(TXENUMINFO*)enumEmUpdateHduRetDescript, 
	(TXENUMINFO*)enumEmMPCodecDescript, 
	(TXENUMINFO*)enumEmTPHDAudPortInDescript, 
	(TXENUMINFO*)enumEmTPHDDualAudPortInDescript, 
	(TXENUMINFO*)enumEmTPHDAudPortOutDescript, 
	(TXENUMINFO*)enumEmTPMtVideoPortDescript, 
	(TXENUMINFO*)enumEmTPMtVideoOutPortDescript, 
	(TXENUMINFO*)enumEmTPAutoTestTypeDescript, 
	(TXENUMINFO*)enumEmTPHduRunStatusDescript, 
	(TXENUMINFO*)enumEmTPLoudspeakerValDescript, 
	(TXENUMINFO*)enumEmTPFrameUnitTypeDescript, 
	(TXENUMINFO*)enumEmTPVideoStandardDescript, 
	(TXENUMINFO*)enumEmTPLabelTypeDescript, 
	(TXENUMINFO*)enumEmTPLabelPosTypeDescript, 
	(TXENUMINFO*)enumEmTPDualVideoShowModeDescript, 
	(TXENUMINFO*)enumEmTPDisplayRatioDescript, 
	(TXENUMINFO*)enumEmTPFecModeTypeDescript, 
	(TXENUMINFO*)enumEmTPNetTypeDescript, 
	(TXENUMINFO*)enumEmTPEqualizerRateDescript, 
	(TXENUMINFO*)enumEmTPPIPModeDescript, 
	(TXENUMINFO*)enumEmTPDVIModeDescript, 
	(TXENUMINFO*)enumEmTPMCModeDescript, 
	(TXENUMINFO*)enumEmCnsUpdateStateDescript, 
	(TXENUMINFO*)enumEmTPCnLoginUpdateRetDescript, 
	(TXENUMINFO*)enumEmTPFileSrvUsedVersionDescript, 
	(TXENUMINFO*)enumEmTPFileSrvFileTypeDescript, 
	(TXENUMINFO*)enumEmTPOSTypeDescript, 
	(TXENUMINFO*)enumEmMPAudEncCodecDescript, 
	(TXENUMINFO*)enumEmToolTypeDescript, 
	(TXENUMINFO*)enumEmProducetestTypeDescript, 
	(TXENUMINFO*)enumEmMdyRecFileResDescript, 
	(TXENUMINFO*)enumEmUseReccorderResDescript, 
	(TXENUMINFO*)enumEmRecorderTypeDescript, 
	(TXENUMINFO*)enumEmConfRecStateDescript, 
	(TXENUMINFO*)enumEmTpProfileDescript, 
	(TXENUMINFO*)enumEmTPHandleCfgTypeDescript, 
	(TXENUMINFO*)enumEmTpCodecTypeDescript, 
	(TXENUMINFO*)enumEmToolStateDescript, 
	(TXENUMINFO*)enumEmTPAudPlayModeDescript, 
	(TXENUMINFO*)enumEmTPAudDualInModeDescript, 
	(TXENUMINFO*)enumEmTPDualTypeDescript, 
	(TXENUMINFO*)enumEmTPDsNodeDescript, 
	(TXENUMINFO*)enumEMScreenLookedDescript, 
	(TXENUMINFO*)enumEmUmsVmpStyleDescript, 
	(TXENUMINFO*)enumEmVmpEncModeDescript, 
	(TXENUMINFO*)enumEmVmpShowModeDescript, 
	(TXENUMINFO*)enumEmVmpResDescript, 
	(TXENUMINFO*)enumEmAudPlayModeDescript, 
	(TXENUMINFO*)enumEmResetAudModeDescript, 
	(TXENUMINFO*)enumEmCheckAudPakDescript, 
	(TXENUMINFO*)enumEmViewEpTypeDescript, 
	(TXENUMINFO*)enumEmViewRetReasonDescript, 
	(TXENUMINFO*)enumEmUITypeDescript, 
	(TXENUMINFO*)enumEmGetVidResDescript, 
	(TXENUMINFO*)enumEmBrdVmpRetDescript, 
	(TXENUMINFO*)enumEmBrdVmpStatDescript, 
	(TXENUMINFO*)enumEmRervesVmpRetDescript, 
	(TXENUMINFO*)enumEmCnmpLogTypeDescript, 
	(TXENUMINFO*)enumEmCnmpLogCtDescript, 
	(TXENUMINFO*)enumEmAudAecTypeDescript, 
	(TXENUMINFO*)enumEmGetVidTypeDescript, 
	(TXENUMINFO*)enumEmVidEncResizeModeDescript, 
	(TXENUMINFO*)enumEmTpVendorIDDescript, 
	(TXENUMINFO*)enumEMScreenObjDescript, 
	(TXENUMINFO*)enumEmTpBannerTransparencyDescript, 
	(TXENUMINFO*)enumEmTpBannerTypeDescript, 
	(TXENUMINFO*)enumEmTpLogoTypeDescript, 
	(TXENUMINFO*)enumEmTpSnapShotTypeDescript, 
	(TXENUMINFO*)enumEmTpCtrlModeDescript, 
	(TXENUMINFO*)enumEmDiscussOprResDescript, 
	(TXENUMINFO*)enumEmDiscussRspRetDescript, 
	(TXENUMINFO*)enumEmDCamProTypeDescript, 
	(TXENUMINFO*)enumEmIconTypeDescript, 
	(TXENUMINFO*)enumEmAudMixTypeDescript, 
	(TXENUMINFO*)enumEmAudExtendDescript, 
	(TXENUMINFO*)enumEmRollCallRspRetDescript, 
	(TXENUMINFO*)enumEmAudMixModeDescript, 
	(TXENUMINFO*)enumEmAudMixListOprDescript, 
	(TXENUMINFO*)enumEmAudMixResDescript, 
	(TXENUMINFO*)enumEmRollCallPresentStateDescript, 
	(TXENUMINFO*)enumEmVidMergeStyleDescript, 
	(TXENUMINFO*)enumEmMeetingRoomSizeDescript, 
	(TXENUMINFO*)enumEmAudGroupIndexDescript, 
	(TXENUMINFO*)enumEmUpdateFrequencyDescript, 
	(TXENUMINFO*)enumEmQCamProTypeDescript, 
	(TXENUMINFO*)enumEmP2PCallStrategyLevelDescript, 
	(TXENUMINFO*)enumEMDS_SUBTYPEDescript, 
	(TXENUMINFO*)NULL
};

#endif //_TP_COMMON_XML_STRUCT_H_
