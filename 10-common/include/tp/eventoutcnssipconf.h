#ifndef _h_eventoutcnssipconf_h__
#define _h_eventoutcnssipconf_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSSIPCONFEVENT
{
#endif 

  _ev_segment( outercnssipconf  )

_event(  ev_CnBeChairMan_Ind )
_body( BOOL, 1 )
_ev_end
/***********************<< 设置发言屏 >>********************** 
*[消息体]
+u8		屏序号
*[消息方向]
*  cns	  <- cnc
*/
_event(  ev_CnSetInnerSpeaker_Cmd )
_body( u8, 1 )
_ev_end

/***********************<< 设置发言屏回应 >>********************** 
*[消息体]
+u8		当前发言屏序号
*[消息方向]
*  cns	  -> cnc
*/
_event(  ev_CnSetInnerSpeaker_Ind )
_body( u8, 1 )
_ev_end

/***********************<< 设置发言会场回应 >>********************** 
*[消息体]
+u8		屏序号
+s8		屏所看得会场名
*[消息方向]
*  cns	  -> cnc
*/
_event(  ev_CnYouAreSeeing_Ind )
_body( TTPYouAreSeeing, 1 )
_ev_end

/***********************<< 会议状态指示 >>********************** 
*[消息体]
+EmCALLSTATE		会议状态
*[消息方向]
*  cns	  -> cnc
*/
_event( ev_CnConfState_Nty )
_body( TTPCnsConfStatus, 1 )
_ev_end


/***********************<<  开启轮询 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_CnStartPoll_Cmd )
_ev_end

/***********************<<  开启轮询回应 >>********************	
 *[消息体]
 +EmPollReason 
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_CnStartPoll_Ind )
_body ( EmTPPollResult  , 1  )
_ev_end

/***********************<<  关闭轮询 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_CnStopPoll_Cmd )
_ev_end

/***********************<<  关闭轮询回应 >>********************	
 *[消息体]
 +EmPollReason 
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_CnStopPoll_Ind )
_body ( EmTPPollResult  , 1  )
_ev_end

/***********************<<  轮询状态通知 >>********************	
 *[消息体]
 +BOOL  开 or 关
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_CnPollStatus_Nty )
_body ( TTpPollStat  , 1  )
_ev_end


/***********************<<  开启选看 >>********************	
 *[消息体]
 +u8 屏序号
 +u16 要选看会场的epid
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_CnSingleView_Cmd )
_body ( u8  , 1  )
_body ( u16  , 1  )
_ev_end

/***********************<<  开启选看回应 >>********************	
 *[消息体]
 +u8 屏序号
 +EmTPViewResult 成功与否
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_CnSingleView_Ind )
_body ( u8  , 1  )
_body ( EmTPViewResult, 1 )
_ev_end

/***********************<<  关闭选看 >>********************	
 *[消息体]
 +u8 屏序号
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_CnCancelSingleView_Cmd )
_body ( u8  , 1  )
_ev_end

/***********************<<  关闭选看回应 >>********************	
 *[消息体]
 +u8 屏序号
 +EmTPViewResult 结果
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_CnCancelSingleView_Ind )
_body ( u8  , 1  )
_body ( EmTPViewResult, 1 )
_ev_end

//由于接入模块单独一个进程，这里移植到外部消息
_event(  ev_CnChanViewLocalCmd )
_ev_end

_event(  ev_CnChanCancelViewLocalCmd )
_ev_end

/***********************<< 请求双流回应  >>********************	
 *[消息体]
 +BOOL
 +EmTPDualReason
 *[消息方向]
 *  cncall  -> cns
*/
_event(  ev_CnRequestDualStreamInd )
_body( BOOL, 1 )
_body( EmTPDualReason, 1 )
_ev_end

/***********************<< 通知双流终端名字  >>********************	
 *[消息体]
 +s8 双流终端名
 *[消息方向]
 *  cncall  -> cns
*/
_event(  ev_Cn_DualNameNty )
_body( s8, TP_MAX_NAME_LEN +1 )
_ev_end

/***********************<< 通知轮询会场名字  >>********************	
 *[消息体]
 +TTPPollDstName
 *[消息方向]
 *  cncall  -> cns
*/
_event(  ev_Cn_PollNameNty )
_body( TTPPollDstName, 1 )
_ev_end

/***********************<<  激活屏状态通知 >>********************	
 *[消息体]
 u8 屏序号
 EmTPPosStatus 状态
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_CnActivePos_Nty )
_body( u8 , 1 )
_body( EmTPPosStatus , 1 )
_body( EMPosPic , 1 )
_ev_end




/***********************<< 会议ep列表 >>********************	
 *[消息体]
TConfCnsInfo
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_CnConfEpList_Nty )
_body( TConfCnsInfo , 1 )
_ev_end

/***********************<< 看本地选看信令 >>********************	
 *[消息体]
u8
 *[消息方向]
 *  cnc	 -> cns
*/
_event(  ev_CnViewLocal_Cmd )
_body( u8 , 1 )
_ev_end

/***********************<< 看本地选看信令回复 >>********************	
 *[消息体]
u8
 *[消息方向]
 *  cns	 -> cnc
*/
_event(  ev_CnViewLocal_Ind )
_body( u8 , 1 )
_body( EmTPViewLocalResult, 1 )
_ev_end


/***********************<< 取消本地选看信令 >>********************	
 *[消息体]
u8
 *[消息方向]
 *  cnc	 -> cns
*/
_event(  ev_CnCancelViewLocal_Cmd )
_body( u8 , 1 )
_ev_end

/***********************<< 取消本地选看信令回复 >>********************	
 *[消息体]
u8
 *[消息方向]
 *  cns	 -> cnc
*/
_event(  ev_CnCancelViewLocal_Ind )
_body( u8 , 1 )
_body( EmTPViewLocalResult, 1 )
_ev_end


/***********************<<  屏幕状态及名称统一显示 >>********************	
 *[消息体]
 u8 屏序号
 EMPosPic 状态
 s8 屏幕名称
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_CnPosAllStatus_Nty )
_body( u8 , 1 )
_body( EMPosPic , 1 )
_body( s8, TP_MAX_NAME_LEN+1 )
_ev_end


/***********************<<  多点会议讨论开启 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_TppConfAMixUpdate_Cmd )
_body( TConfAuxMixInfo , 1 )
_ev_end


/***********************<<  多点会议讨论开启回应 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppConfAMixUpdate_Ind )
_body( TConfAuxMixInfo , 1 )
_ev_end

/***********************<<  多点会议讨论开启通知 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppConfAMixUpdate_Nty )
_body( TConfAuxMixInfo , 1 )
_ev_end


/***********************<<  多点会议切换发言人 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_TppConfApplySpeaker_Cmd )
_body( TConfEpID , 1 )
_ev_end


/***********************<<  多点会议切换发言人 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppConfApplySpeaker_Ind )
_body( TConfEpID , 1 )
_body( EmTpApplySpeakerRet, 1 )
_ev_end


/***********************<<  多点会议切换发言人 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppConfApplySpeaker_Nty )
_body( TConfEpID , 1 )
_ev_end

/***********************<<  多点会议控制远端哑音 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_TppConfMute_Cmd )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUE指示远端哑音，FALSE取消远端哑音_
_ev_end

/***********************<<  多点会议控制远端哑音 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppConfMute_Ind )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUE指示远端哑音，FALSE取消远端哑音_
_ev_end


/***********************<<  多点会议控制远端哑音 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppConfMute_Nty )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUE指示远端哑音，FALSE取消远端哑音_
_ev_end

/***********************<<  多点会议控制远端静音 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_TppConfQuiet_Cmd )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUE指示远端静音，FALSE取消远端静音_
_ev_end

/***********************<<  多点会议控制远端静音 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppConfQuiet_Ind )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUE指示远端静音，FALSE取消远端静音_
_ev_end


/***********************<<  多点会议控制远端静音 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppConfQuiet_Nty )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUE指示远端静音，FALSE取消远端静音_
_ev_end

/***********************<<  多点会议中通过名字邀请列表中不存在的会场 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppInviteCnsByAlias_Cmd )
_body( TTpCallAddr , 1 )
_ev_end

/***********************<<  多点会议中通过名字邀请列表中不存在的会场回应 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppInviteCnsByAlias_Ind )
_body( TTpCallAddr ,1 )
_body( EmCnsCallReason    , 1    )
_ev_end

/***********************<<  多点会议中通过EPID呼叫列表中存在的不在线会场 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppInviteCnsByEpId_Cmd )
_body( u16 ,1 )
_ev_end

/***********************<<  多点会议中通过EPID呼叫列表中存在的不在线会场回应 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppInviteCnsByEpId_Ind )
_body( u16 ,1 )
_body( EmCnsCallReason    , 1    )
_ev_end

/***********************<<  多点挂断指定会场 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppHangupCns_Cmd )
_body( u16 ,1 )
_ev_end

/***********************<<  多点挂断指定会场回应 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppHangupCns_Ind )
_body( u16 ,1 )
_body( EmCnsCallReason, 1 )
_ev_end

/***********************<<  挂断会议 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppHangupConf_Cmd )
_ev_end

/***********************<<  轮询列表通知 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppUpdateConfTurnlist_Nty )
_body( TConfTurnInfo  , 1  )
_ev_end

/***********************<<  通知主席会议信息 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppChairConfInfo_Nty )
_body( TChairConfInfo  , 1  )
_ev_end


/***********************<<  会场语音激励状态通知 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppAudMixStatus_Nty )
_body( TAudMixStat  , 1  )
_ev_end

/***********************<<  会议讨论通知 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppDiscussScreenStat_Notify )
_body( TTPDisScreenStat  , 1  )
_ev_end

/***********************<<  讨论会场操作（添加、删除） >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_TppAudMixDisListOpr_Cmd )
_body( TDiscussListOpr  , 1  )
_ev_end

/***********************<<  讨论会场操作（添加、删除） >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppAudMixDisListOpr_Ind )
_body( TDiscussListOpr  , 1  )
_ev_end

/***********************<< 加入会议 >>********************** 
*[消息体]
TTPMDLTERLABEL
*[消息方向]
*  cnc	  <- cns
*/
_event(  ev_TppModuleTerminalJoinConf )
_body( TCnsInfo, 1 )
_ev_end

/***********************<< 离开会议 >>********************** 
*[消息体]
TTPMDLTERLABEL
*[消息方向]
*  cnc	  <- cns
*/
_event(  ev_TppModuleterminalLeftConf )
_body( TCnsInfo, 1 )
_ev_end

/***********************<<  >>********************** 
*[消息体]
TTPUmsReasonInd
*[消息方向]
*  cnc	  <- cns
*/
_event( ev_TppUmsCommonReasonToUI_Ind )
_body( TTPUmsReasonInd, 1 )
_ev_end

/***********************<< 看本地画中画 >>********************** 
*[消息体]
*u8 屏号
*BOOL 本地画中画是否开启
*[消息方向]
*  cnc	-> cns
*/
_event( ev_CnViewLocalPIP_Cmd )
_body( u8, 1 )
_body( BOOL, 1 )
_ev_end

/***********************<< 看本地画中画 >>********************** 
*[消息体]
*u8 屏号
*EmTPViewLocalResult
*[消息方向]
*  cnc	<- cns
*/
_event( ev_CnViewLocalPIP_Ind )
_body( u8, 1 )
_body( EmTPViewLocalResult, 1 )
_ev_end

/***********************<< 看本地画中画 >>********************** 
*[消息体]
*u8 屏号
*BOOL 本地画中画是否开启
*[消息方向]
*  cnc	<- cns
*/
_event( ev_CnViewLocalPIP_Nty )
_body( u8, 1 )
_body( BOOL, 1 )
_ev_end


/***********************<<  开启选看电视墙 >>********************	
 *[消息体]
 +u8 屏序号
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_CnSelTVSView_Cmd )
_body ( u8  , 1  )
_ev_end

/***********************<<  开启选看电视墙回应 >>********************	
 *[消息体]
 +u8 屏序号
 +BOOL 成功与否
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_CnSelTVSView_Ind )
_body ( u8  , 1  )
_body ( BOOL, 1 )
_ev_end

/***********************<<  关闭选看电视墙 >>********************	
 *[消息体]
 +u8 屏序号
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_CnCancelSelTVSView_Cmd )
_body ( u8  , 1  )
_ev_end

/***********************<<  关闭选看电视墙回应 >>********************	
 *[消息体]
 +u8 屏序号
 +BOOL 结果
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_CnCancelSelTVSView_Ind )
_body ( u8  , 1  )
_body ( BOOL, 1 )
_ev_end

/***********************<<  渠道号通知  >>********************	
*[消息体]
+u8 屏序号
+BOOL 结果
*[消息方向]
*  cnc	  <- cns
*/
_event(  ev_CnManuProductID_Nty )
_body ( TTPKedaManuProductTP  , 1  )
_ev_end


/***********************<<  点对点呼叫是否设置问题码流通知  >>********************	
*[消息体]
+BOOL 结果
*[消息方向]
*  cns	  --> cnds
*/
_event(  ev_CnIsFalseStream_Nty )
_body ( BOOL32  , 1  )
_ev_end

/***********************<<  对端是否是科达终端通知  >>********************	
*[消息体]
+BOOL 结果
*[消息方向]
*  cncall	  --> cns
*/
_event(  ev_CnCheckPeerIsKedaMT_Nty )
_body ( BOOL32  , 1  )
_ev_end

/***********************<<  通知cncall CN上线  >>********************	
*[消息体]
+BOOL 结果
*[消息方向]
*  cncall	  <- cns
*/
_event(  ev_CnOnline_Nty )
_body ( BOOL  , 1  )
_ev_end

/***********************<<  mc询问ter会议密码  >>********************	
*[消息体]
*[消息方向]
*  cnc	  <- cns
*/
_event(  ev_CnEnterH243Password_Req )
_ev_end

/***********************<<  ter回答mc会议密码  >>********************	
*[消息体]
*[消息方向]
*  cnc	  -> cns
*/
_event(  ev_CnEnterH243Password_Rsp )
_body( TTPConfPassword , 1 )
_ev_end

/***********************<<  会议密码询问定时器  >>********************	
*[消息体]
*[消息方向]
*  cns	  -> cns
*/
_event(  ev_CnEnterH243Password_Timer )
_ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnssipconf )
};
#endif
#endif //TPP_EVENT_H
