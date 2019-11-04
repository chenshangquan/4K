#ifndef _PA_XML_TYPE_H_
#define _PA_XML_TYPE_H_

#include "xmlengine.h"

//Data struct type begin
enum EmPAXDataType
{
  empaxAtomTypeBegin =0, //原子类型数据(kdvtype.h)
	empax_s32,
	empax_BOOL32,
	empax_BOOL,
	empax_u8,
	empax_s8,
	empax_u16,
	empax_u32,
	empax_u32_ip,
	empax_u8_blob,
	empax_time_t,
	empax_string,
  empaxEnumTypeBegin = 20, //枚举类型数据(mttype.h 业务层枚举头文件的解析结果)
	empax_EmBegin,
	empax_EmPAVendorID,
	empax_EmPAMediaType,
	empax_EmPAProfileMask,
	empax_EmPAVideoFormat,
	empax_EmPAAudioFormat,
	empax_EmPAPayloadType,
	empax_EmPAResolution,
	empax_EmPAVideoResolution,
	empax_EmDualReason,
	empax_EmPAOprType,
	empax_EmPATPEndpointType,
	empax_EmPATpApplySpeakerRet,
	empax_EmPATPDualReason,
	empax_EmPACnsCallReason,
	empax_EmPATpMixStatus,
	empax_EmPAAliasType,
	empax_EmPADisListOprType,
	empax_EmPADisListOprReslt,
	empax_EmPAAACSampleFreq,
	empax_EmPAAACChnlCfg,
	empax_EmPATPVMPStyle,
	empax_EmPATPVMPType,
	empax_EmPAViewEpType,
	empax_EmPAUIType,
	empax_EmPAGetVidType,
	empax_EmPAGetVidRes,
	empax_EmPAPollStat,
	empax_EMPAScreenObj,
	empax_EmPADiscussRspRet,
	empax_EmPADiscussOprRes,
	empax_EmPAHduRunStatus,
	empax_EmPAHduPlayNackReason,
	empax_EmPAHduSetVolRes,
	empax_EmPAHduChangeChanModeRes,
	empax_EmPAModuleOperateType,
	empax_EmPAProtocolType,
  empaxStructTypeBegin = 200, //数据结构类型数据(mtstruct.h 业务层结构类型头文件的解析结果)
	empax_TYouAreSeeing,
	empax_TPAIPAddress,
	empax_TPAConfStatusInd,
	empax_TPAEpPathKey,
	empax_TPAEpKey,
	empax_TPAPollNodeChange,
	empax_TPACascadingSpeaker,
	empax_TPAPeerMuteCmd,
	empax_TPAPeerMuteInd,
	empax_THangupCascadingConf,
	empax_TPAName,
	empax_TPAPollDstName,
	empax_TPAAskKeyByScreenTr,
	empax_TPAAlias,
	empax_TPAEpKeyID,
	empax_TPAUmsVidFormat,
	empax_TPAUmsAudFormat,
	empax_TPAConfNodeUpdateTr,
	empax_TPAConfNodeUpdateTrList,
	empax_TPAConfNodeUpdateB2NEWTr,
	empax_TPAConfNodeUpdateB2NEWTrList,
	empax_TPAConfNodeDelTrList,
	empax_TPAAudMixEpCmdTr,
	empax_TPAAudMixEpAckTr,
	empax_TDualInfo,
	empax_TDualInfoAck,
	empax_TDualRequest,
	empax_TPATvMonitorCmd,
	empax_TPATvMonitorInd,
	empax_TPANodeCapsetTr,
	empax_TPaMediaTransAddr,
	empax_TPACnsInfo,
	empax_TConfCnsList,
	empax_TPAConfCnsList,
	empax_TPAChanSelecteCascad,
	empax_TPAChanSelecteCascadRes,
	empax_TPATmpChanSelecteCascadRes,
	empax_TPAChanSelecteCascadCancelRes,
	empax_TPAPollCmd,
	empax_TPAPollAck,
	empax_TPAViewCmd,
	empax_TPAAdjustFrameRate,
	empax_TPAAdjustVidRes,
	empax_TPAViewAck,
	empax_TPACascadeOpenChanCmd,
	empax_TPACascadeOpenChanAck,
	empax_TPAUmsReasonInd,
	empax_TPAUmsUpRecPlayState,
	empax_TPAFlowControl,
	empax_TPAAudChanCmd,
	empax_TPAAudChanAck,
	empax_TPAVidUpAddr,
	empax_TPAVidDownAddr,
	empax_TPAVidChanCmd,
	empax_TPAVidChanAck,
	empax_TPAAuxMixList,
	empax_TPAConfAuxMixInfo,
	empax_TPAConfEpID,
	empax_TPAConfTurnList,
	empax_TPAConfTurnInfo,
	empax_TPAConfCallEpAddr,
	empax_TPAChairConfInfo,
	empax_TPAAudMixStat,
	empax_TPADisAskKeyFrame,
	empax_TPADisListOpr,
	empax_TPATerminalLabel,
	empax_TPATerLabelList,
	empax_TPATerminalInfo,
	empax_TPATPVMPChanInfo,
	empax_TPATPVMPInfo,
	empax_TPATPSelViewReq,
	empax_TPATPSelViewInd,
	empax_TPATPSelViewNtfy,
	empax_TPASelViewNtfy,
	empax_TPAGetVidBaseInfo,
	empax_TPAGetVidInfo,
	empax_TPAGetVidInfoRes,
	empax_TPAStopGetVid,
	empax_TPACasecadePollEpReq,
	empax_TPACasecadePollEpRsp,
	empax_TPAPollListNtfy,
	empax_TPAPollListInd,
	empax_TPAPollStat,
	empax_TPADiscussObjInfo,
	empax_TPADiscussCasecadeNtfy,
	empax_TPAEqpInfo,
	empax_TPARersvesEqpReq,
	empax_TPARersvesEqpRsp,
	empax_TPABrdVmpChnl,
	empax_TPABrdVmpStyle,
	empax_TPASetVmpInfoReq,
	empax_TPASetVmpInfoRsp,
	empax_TPABrdVmpReq,
	empax_TPABrdVmpRsp,
	empax_TPAVmpCasecadeNtfy,
	empax_TPABrdVmpResNtfy,
	empax_TPABrdVmpResArray,
	empax_TPAConfAuxMixVacOpr,
	empax_TPAVmpCfgChnl,
	empax_TPAVmpMemberCfg,
	empax_TPAVmpMemberCfgInd,
	empax_TPAObj,
	empax_TPAYouAreSeeing,
	empax_TPACallAddr,
	empax_TPAConfEpInfo,
	empax_TPAHduUnitPlayInfo,
	empax_TPAHduPlanUnit,
	empax_TPAHduPlanPackData,
	empax_TPAHduPlayReq,
	empax_TPAHduBaseInfo,
	empax_TPAHduSetVolInfo,
	empax_TPAHduChanModeSetInfo,
	empax_TPAUmsAudMixList,
	empax_TPAUmsAudMixInfo,
	empax_TPAUmsAudMixModeCmdRes,
	empax_TPAUmsAudMixListCmd,
	empax_TPAUmsAudMixListCmdRes,
	empax_TPAUmsAudMixCasecadeInfo,
	empax_TPARollCallList,
	empax_TPAConfRollCallInfo,
	empax_TPARollCallNextEpInfo,
	empax_TPARollCallEpNodeInfo,
	empax_TPARollCallCasecadeNtfy,
	empax_TPAUpdataRollCallList,
	empax_TPAUpdataRollCallListRes,
	empax_TPARollCallPresentStateEpInfo,
	empax_TPARollCallPresentStateMsg,
	empax_TPAVidAliasInfo,
	empax_TPAVidSourceInfo,
	empax_TPAVidFeccInfo,
	empax_TPAEpVidFeccInfo,
	empax_TPAConfEpVidFeccList,
	empax_TPAConfVidFeccInfo,
	empax_TPAConfGetTempPwdReq,
	empax_TPAConfGetTempPwdNtfy,
	empax_TPAUmsVacInfo,
empaxDataTypeEnd = 500 //类型定义结束
};
//	Data struct type end

extern TXDATAINFO* g_tPAAtomDataInfo[];
extern TXDATAINFO* g_tPAEnumDataInfo[];
extern TXDATAINFO* g_tPAStructDataInfo[];
#define _InitPAAtomType( type ) InitAtomType_##type( empax_##type )
#define _InitPABlobType( type ) InitAtomType_##type##_blob( empax_##type##_blob )

#define UserInitPAXmlEngine() do { \
	_InitPAAtomType( s32    ); \
	_InitPAAtomType( BOOL32 ); \
	_InitPAAtomType( BOOL   ); \
	_InitPAAtomType( u8     ); \
	_InitPAAtomType( s8     ); \
	_InitPAAtomType( u16    ); \
	_InitPAAtomType( u32    ); \
	_InitPAAtomType( u32_ip ); \
	_InitPABlobType( u8     ); \
	_InitPAAtomType( time_t ); \
	                         \
} while (0)

#define XML_MARSHAL( Type, pSrcBuf, pOutBuf, dwOutputLen, dwOverFlow ) \
	XML_Encode( empax_##Type, pSrcBuf, em_PAXMLNone, pOutBuf, dwOutputLen, dwOverFlow )

#define XML_UNMARSHAL( Type, pSrcBuf, dwSrcBufLen, pOutBuf, dwOutputLen, dwOverFlow ) \
	XML_Decode( empax_##Type, pSrcBuf, dwSrcBufLen, em_PAXMLNone, pOutBuf, dwOutputLen, dwOverFlow )
 

const char XmlTypeVersion[] = "2019-5-8 3:17:33";

#endif //_XML_TYPE_H_
