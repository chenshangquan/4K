#ifndef _h_eventoutsipadapter_h__
#define _h_eventoutsipadapter_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumssipadaper
{
#endif
	
	_ev_segment( tpumswithumssipadapter )
		
 
/***********************<<  ums发起呼叫 >>********************/
_event(  ev_MakeCall_Req )
	_body ( TUmsHandle  , 1  )	
	_body(TMakeCallPara, 1)
_ev_end

/***********************<<  主叫发起二次协商 >>********************/
_event(  ev_MakeChan_Req )
_body ( TUmsHandle  , 1  )	
_body(TUmsNodeCapset, 1)
_body(BOOL32, 1) //是否是双流
_ev_end

/***********************<<  ums应答呼叫 >>*********************/
_event(  ev_AnwserCall_IND )
	_body ( TUmsHandle  , 1  )	
	_body(BOOL32, 1)
	_body(EmCnsCallReason, 1)
	_body(TMakeCallPara, 1)
_ev_end
 
/***********************<<  ums向下级打开主席通道 >>*********************/
_event(  evtp_cascade_OpenChairChan_cmd )
_body ( TUmsHandle  , 1  )	
_body(TCascadeOpenChanCmd, 1)
_ev_end

/***********************<<  ums向下级打开主席应答 >>*********************/
_event(  evtp_cascade_OpenChairChan_ack )
_body ( TUmsHandle  , 1  )	
_body(TCascadeOpenChanAck, 1)
_ev_end


 /***********************<<  ums挂断呼叫 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_HungUp_Req )
_body ( TUmsHandle  , 1  )	
_body ( EmCnsCallReason  , 1  )	
 _ev_end

 /***********************<<  ums发起注册 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_Register_Req )
_body ( TUmsHandle  , 1  )	
_body ( TUmsSipRegCfg  , 1  )	
_body ( u16  , 1  )	
_body ( TTPAlias  , TP_CONFTEMPGROUP_MAXNUM  )		
 _ev_end

  /***********************<<  ums发起gk注册 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_gk_Register_Req )
_body ( TUmsHandle  , 1  )	
_body ( TRegCfg  , 1  )	
_body ( u16  , 1  )		
 _ev_end

   /***********************<<  注册句柄信息 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_register_handle_info )
_body ( TUmsHandle  , 1  )	
_body ( EmTpRegType  , 1  )		
 _ev_end

 /***********************<<  注册结果 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */
 _event(  evtp_ums_reg_ret )
	_body ( TUmsHandle  , 1  )
	_body ( TCnsRegRetResult  , 1  )
 _ev_end	


 /***********************<<  ums发起取消注册 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_UnRegister_Req )
_body ( TUmsHandle  , 1  )	
_body (EmTpRegType, 1 )
 _ev_end

 /***********************<<  请求删除注册结果 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  evtp_ums_unreg_ret )
	_body ( TUmsHandle  , 1  )
	_body ( TUCSipRegResult  , 1  )
   _ev_end	

 /***********************<<  323注册失败 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  evtp_ums_323_unreg_ret )
	_body ( TUmsHandle  , 1  )
	_body ( TUCSipRegResult  , 1  )
   _ev_end	

/***********************<<  呼叫到来 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	call	--> service
 *
 */
_event(  evtp_UmsConfIncoming )
_body ( TUmsHandle  , 1  )
_body ( TUmsCallInfo  , 1  )
_ev_end

/***********************<<  创建会议 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	call	--> service
 *
 */
_event(  evtp_UmsConfCreateMeeting )
_body ( TUmsHandle  , 1  )
_body ( TUmsCallInfo  , 1  )
_body ( TTPConfTemplate  , 1  )
_ev_end

/***********************<<  会场呼叫成功 >>********************	 
 *[消息体]			 
 *   
 *[消息方向]	call	--> service
 *
 */
_event(  evtp_Conf_UmsCallConnect )
_body ( TUmsHandle  , 1  )		
_body ( TUmsCallInfo, 1)
_ev_end

/***********************<<  会议挂断 >>********************	 
 *[消息体]			 
 *   
 *[消息方向]	call	--> service
 *
 */
_event(  evtp_Conf_UmsCallDisConnect )
_body ( TUmsHandle  , 1  )	
_body ( EmCnsCallReason  , 1  )	
_ev_end


/***********************<<  通道打开 >>********************	 
 *[消息体]			 
 *   
 *[消息方向]	call	--> service
 *
 */
_event(  evtp_Conf_UmsChannelConnect )
_body ( TUmsHandle  , 1  )	
_body ( TUmsNodeCapset  , 1  )	
_ev_end

/***********************<<  通道关闭 >>********************	 
 *[消息体]			 
 *   
 *[消息方向]	call	--> service
 *
 */
_event(  evtp_Conf_UmsChannelDisConnect )
_body ( TUmsHandle  , 1  )	
_ev_end


 /***********************<<  通道消息开始 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event( ev_SipAdapter_ChanBegin )
_ev_end


/***********************<<  关键帧请求 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_AskKeyFrame )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  CNS通知Ums会场发言人 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_CnsSpeaker_Notify )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<   >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Chan_FlowCtrol )
_body ( TUmsHandle  , 1  )	
_body( u16 , 1)//带宽
_ev_end


/***********************<<  通知通道看本地  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_ChanSeeLocal_Ind )
_body ( TUmsHandle  , 1  )	
_ev_end



/***********************<<  通知通道取消看本地  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_ChanSeeLocalCancel_Ind )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  选看结果  >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_ViewObj_Ind )
_body ( TUmsHandle  , 1  )	
_body( TChanViewRes, 1)	
_ev_end


/***********************<<  取消选看结果  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_UndoViewObj_Ind )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)	//屏号	
_ev_end



 /***********************<<  双流消息开始 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event( ev_SipAdapter_DualBegin )
_ev_end


/***********************<<  打开双流通道 >>********************/
_event(  ev_OpenDualChan_Req )
_body ( TUmsHandle  , 1  )	
_body(TUmsNodeCapset, 1)
_ev_end

/***********************<<  打开双流通道 >>********************/
_event(  ev_OpenDualChan_Incoming )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  双流通道打开应答 >>********************/
_event(  ev_MakeSendDual_Answer )
_body ( TUmsHandle  , 1  )
_body ( BOOL32, 1)	
_body(TUmsNodeCapset, 1)
_ev_end

/***********************<<  双流通道打开 >>********************/
_event(  ev_OpenDualChan_Connect )
_body ( TUmsHandle  , 1  )	
_body(TUmsNodeCapset, 1)
_ev_end

/***********************<<  双流通道断开>********************/
_event(  ev_OpenDualChan_Failed )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  停止双流 >>********************/
_event(  ev_DualChan_DisConnect )
_body ( TUmsHandle  , 1  )
_body ( EmTPChannelReason, 1 )	
_ev_end

/************************<<  请求双流 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_RequestDualStream_cmd  )
_body ( TUmsHandle  , 1  )	
_body( TEpKey, 1)	
_ev_end

/************************<<  请求双流结果 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_RequestDualStream_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TDualRequestAckTr, 1)	
_ev_end


/************************<<  请求双流 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_cascade_OpenDualChan_Cmd  )
_body ( TUmsHandle  , 1  )	
_body(TDualInfoTr, 1)	
_ev_end


/************************<<  请求双流应答 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_cascade_OpenDualChan_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TDualInfoAckTr, 1)	
_ev_end

/************************<<  停止接收双流 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_StopRcvDual_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( EmTPDualReason  , 1  )	
_ev_end

/************************<<  请求双流关键帧 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_DualFastUpdate_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( BOOL32  , 1  )	
_ev_end

/************************<<  开始接收双流 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_StartRcvDual_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( TEpKey  , 1  )		//发送方
_ev_end


/************************<<  停止发送双流 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_StopSendDual_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( TEpKey  , 1  )	
_ev_end


/************************<<  双流源名称通知 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_SrcDualName_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TTPAlias, 1)
_body ( TEpKey  , 1  )	
_ev_end


/***********************<<多点会议双流请求  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfStartDual_Cmd )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_ev_end

/***********************<<多点会议双流请求应答  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfStartDual_Ind )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_body ( EmTPDualReason , 1 )
_ev_end

/***********************<<多点会议停双流请求  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfStopDual_Cmd )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_ev_end

/***********************<<多点会议双流请求应答  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfStopDual_Ind )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_body ( EmTPDualReason , 1 )
_ev_end

/***********************<<多点会议双流会场广播通知  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfDualEp_Nty )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_ev_end




 /***********************<<  轮询消息开始 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event( ev_SipAdapter_PollBegin )
_ev_end

/************************<<  当前轮询目标的名称 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_PollDstName_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TPollInfoNtf, 1)
_ev_end

/***********************<<  上级请求下级开始论询 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_StartPoll_cmd )
_body ( TUmsHandle  , 1  )	
_body( TPollCmdTr, 1)	
_ev_end
		
/***********************<<  下级应答上级开始论询 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_StartPoll_ack )
_body ( TUmsHandle  , 1  )	
_body( TPollAckTr, 1)	
_ev_end
/***********************<<  下级通知上级轮询结点变换 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_Poll_NodeChange )
_body ( TUmsHandle  , 1  )	
_body( TEpKey, 1)	
_ev_end
/***********************<<  通知轮询结束 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *	UMS -> UMS
 */
_event( evtp_Conf_Poll_End )	
_body ( TUmsHandle  , 1  )	
_body ( BOOL32	 , 1  )		//是否暂停
_ev_end

/***********************<<  轮询关键帧请求 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_Poll_AskKeyFrame )	
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  开启轮询  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_StartPoll_Req	 )
_body ( TUmsHandle  , 1  )	
_ev_end


/***********************<<  开启轮询结果  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_StartPoll_Ind	 )
_body ( TUmsHandle  , 1  )	
_body( EmTPPollResult, 1)	//结果	
_ev_end

/***********************<<  停止轮询  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_StopPoll_Req	 )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  停止轮询结果  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_StopPoll_Ind	 )
_body ( TUmsHandle  , 1  )	
_body( EmTPPollResult, 1)	//结果	
_ev_end

/***********************<<  暂停轮询  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_SuspendPoll_Req	 )
_body ( TUmsHandle  , 1  )	
_body ( BOOL32, 1 )
_ev_end

/***********************<<  暂停轮询结果  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_SuspendPoll_Ind	 )
_body ( TUmsHandle  , 1  )	
_body( EmTPPollResult, 1)	//结果	
_ev_end

/***********************<<  级联 通知下级 新的轮询目标  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_CasecadePollEp_Req	 )
_body ( TUmsHandle  , 1  )	
_body( TCasecadePollEpReq, 1) 	
_ev_end

/***********************<<  级联 回应上级 轮询目标请求结果  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_CasecadePollEp_Rsp	 )
_body ( TUmsHandle  , 1  )	
_body( TCasecadePollEpRsp, 1) 	
_ev_end


/***********************<<  通知CNS当前轮询状态  >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_PollStatus_Notif	 )
_body ( TUmsHandle  , 1  )	
_body( TTpPollStat, 1)//是否开启轮询	
_ev_end


/***********************<<  选看  >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_ViewObj_Req )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)	
_ev_end





/***********************<<  取消选看  >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_UndoViewObj_Req )
_body ( TUmsHandle  , 1  )	
_ev_end



/***********************<< 更新轮询列表  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsUpdateConfTurnlist_Nty )
_body (TUmsHandle, 1)
_body ( TTpPollListNtfy , 1 )	
_ev_end

/***********************<< 更新轮询列表回应  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsUpdateConfTurnlist_Ind )
_body (TUmsHandle, 1)
_body ( TTpPollListInd , 1 )	
_ev_end


 /***********************<<  讨论消息开始 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event( ev_SipAdapter_UmsDiscussBegin )
_ev_end

/***********************<< 多点会议讨论开启  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfAMixUpdate_Cmd )
_body (TUmsHandle, 1)
_body ( TConfAuxMixInfo , 1 )	
_ev_end

  /***********************<<  上级UMS请求打开一路视频通道 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] 上级UMS - 下级UMS 
 *
 */
 _event(  evtp_OpenVidChan_Cmd )
 	_body (TUmsHandle, 1)
 	_body(TVidChanCmd, 1)
 _ev_end


  /***********************<<  下级回复上级打开视频通道的指示 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] 下级UMS - 上级UMS 
 *
 */
 _event(  evtp_OpenVidChan_Ack )
 	_body (TUmsHandle, 1)
 	_body(TVidChanAck, 1)
 _ev_end

   /***********************<<  通知下级停止视频通道 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] 下级UMS - 上级UMS 
 *
 */
 _event(  evtp_CloseVidChan_Cmd )
 	_body (TUmsHandle, 1)
 	_body(u16, 1)
 _ev_end

 /***********************<<  通知CNS三个屏的状态和别名 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] UMS->CNS 
 *
 */
_event(  evtp_UmsDiscussScreenStat_Notify )
	_body (TUmsHandle, 1)
	_body ( TDiscussCasecadeNtfy  , 1  )	
_ev_end

 /***********************<<  讨论请求关键帧 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] UMS->CNS 
 *
 */
_event(  evtp_UmsDiscussFastUpdate_Req )
	_body (TUmsHandle, 1)
	_body (TDisAskKeyFrame  , 1  )	
_ev_end


/***********************<< 讨论会场操作（添加、删除）  >>********************	
*[消息方向]	CNC - UMS
*
*/
_event(  ev_UmsAudMixDisListOpr_Cmd )
_body (TUmsHandle, 1)
_body (TDiscussListOpr , 1 )	
_ev_end

/***********************<< 讨论会场操作（添加、删除）  >>********************	
*[消息方向]	CNC - UMS
*
*/
_event(  ev_UmsAudMixDisListOpr_Ind )
_body (TUmsHandle, 1)
_body (TDiscussListOpr , 1 )	
_ev_end

/***********************<< 多点会议讨论开启回应  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfAMixUpdate_Ind )
_body (TUmsHandle, 1)
_body ( TConfAuxMixInfo , 1 )	
_ev_end

/***********************<< 多点会议讨论开启通知  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfAMixUpdate_Nty )
_body (TUmsHandle, 1)
_body ( TConfAuxMixInfo , 1 )	
_ev_end

/***********************<< 语音激励开启和关闭  >>********************	
*[消息方向]	cns	-->  ums
*
*/
_event( ev_UmsConfAMixVacSwitch)
_body(TUmsHandle, 1)
_body(TConfAuxMixVacOpr, 1)
_ev_end

/***********************<< 语音激励开启和关闭回应  >>********************	
*[消息方向]	cns	-->  ums
*
*/

_event( ev_UmsConfAMixVacSwitchInd)
_body(TUmsHandle, 1)
_body(TConfAuxMixVacOpr, 1)
_ev_end 

 /***********************<<  语音激励相关消息 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event( ev_SipAdapter_UmsEapuBegin )
_ev_end

/***********************<< 会场语音激励状态通知  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsAudMixStatus_Nty )
_body (TUmsHandle, 1)
_body ( TAudMixStat , 1 )	
_ev_end

 /***********************<<  通知下级和CNS更新会场的发言坐席索引 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] UMS->CNS 
 *
 */
_event(  evtp_UmsCnsSpeakerIndxAdjust_Notify )
	_body (TUmsHandle, 1)
	_body (TCnsSpeakerAdjust  , 1  )	
_ev_end

/***********************<<  上级请求打开一路音频通道 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] UMS - 下级UMS 
 *
 */
 _event(  evtp_OpenAudChan_Cmd )
	_body (TUmsHandle, 1)
	_body(TAudChanCmd, 1)
 _ev_end

   /***********************<<  下级回复上级打开音频通道的指示 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] 下级UMS - 上级UMS 
 *
 */
 _event(  evtp_OpenAudChan_Ack )
 	_body (TUmsHandle, 1)
 	_body(TAudChanAck, 1)
 _ev_end

 /***********************<<  需要通知CNS的会议状态信息 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event( ev_SipAdapter_CnsConfStatBegin )
_ev_end

//////////////////////////////////////////////////////////////////////////
//通知UI的状态信息，改为走Sip发送给CNS


/***********************<< 多点会议切换发言人  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfApplySpeaker_Cmd )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )	
_ev_end

/***********************<< 多点会议切换发言人回应  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfApplySpeaker_Ind )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( EmTpApplySpeakerRet , 1 )
_ev_end

/***********************<< 多点会议切换发言人通知  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfApplySpeaker_Nty )
_body ( TUmsHandle, 1 )
_body ( TConfEpID , 1 )	
_ev_end

/***********************<< 多点会议控制远端哑音  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfMute_Cmd )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUE指示远端哑音，FALSE取消远端哑音_
_ev_end

/***********************<< 多点会议控制远端哑音回应  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfMute_Ind )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUE指示远端哑音，FALSE取消远端哑音_
_ev_end

/***********************<< 多点会议控制远端哑音通知  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfMute_Nty )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUE指示远端哑音，FALSE取消远端哑音_
_ev_end

/***********************<< 多点会议控制远端静音  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfQuiet_Cmd )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUE指示远端静音，FALSE取消远端静音
_ev_end

/***********************<< 多点会议控制远端静音回应  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfQuiet_Ind )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUE指示远端静音，FALSE取消远端静音
_ev_end

/***********************<<多点会议控制远端静音通知  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfQuiet_Nty )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUE指示远端静音，FALSE取消远端静音
_ev_end

/***********************<<多点会议中通过名字邀请列表中不存在的会场  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  ev_UmsInviteCnsByAlias_Cmd )
	_body (TUmsHandle, 1)
	_body ( TTpCallAddr , 1 )
_ev_end

/***********************<<多点会议中通过名字邀请列表中不存在的会场回应  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsInviteCnsByAlias_Ind )
	_body (TUmsHandle, 1)
	_body ( TTpCallAddr , 1 )
	_body ( EmCnsCallReason , 1 )
_ev_end

/***********************<<多点会议中通过名字呼叫列表中存在的不在线会场  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  ev_UmsInviteCnsByEpId_Cmd )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
_ev_end

/***********************<<多点会议中通过名字呼叫列表中存在的不在线会场回应  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsInviteCnsByEpId_Ind )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
	_body ( EmCnsCallReason , 1 )
_ev_end

/***********************<<多点挂断指定会场  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  ev_UmsHangupCns_Cmd )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
_ev_end

/***********************<<多点挂断指定会场回应  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsHangupCns_Ind )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
	_body ( EmCnsCallReason , 1 )
_ev_end

/***********************<<挂断会议  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  ev_UmsHangupConf_Cmd )
	_body (TUmsHandle, 1)
_ev_end

/***********************<< 通知主席会议信息  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsChairConfInfo_Nty )
	_body (TUmsHandle, 1)
	_body ( TChairConfInfo , 1 )	
_ev_end

/***********************<< 通知界面原因提示 通用  >>********************	
*[消息方向]	UMS	-->  CNS -> cnc
*
*/
_event(  ev_UmsCommonReasonToUI_Ind )
	_body (TUmsHandle, 1)
	_body ( TTPUmsReasonInd , 1 )	
_ev_end


_event( ev_SipAdapter_GetVid_Begin )
_ev_end

/***********************<<  上级请求下级的视频图像 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_cascade_GetVid_cmd )
_body ( TUmsHandle  , 1  )	
_body( TViewCmdTr, 1)	
_ev_end
		
/***********************<<  上级请求下级的视频图像应答 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_cascade_GetVid_ack )
_body ( TUmsHandle  , 1  )	
_body( TViewAckTr, 1)	
_ev_end

/***********************<<  上级停止下级的图像 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_cascade_StopGetVid_cmd )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)		//句柄
_ev_end




 /***********************<<  其他消息开始 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event( ev_SipAdapter_OtherConfBegin )
_ev_end

/***********************<<获取全域内UMS和CNS的全部注册信息  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  ev_UmsGetRegInfo_Req )
	_body ( TUmsHandle, 1)
	_body ( TUmsSipRegCfg, 1)
	_body ( EmGetRegInfoType , 1 )
	_body ( u32,	1)	//SIP 注册句柄
	_body ( u32,	1)	//GK 注册句柄
_ev_end

/***********************<< 获取全域内CNS的全部注册信息回复  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsGetRegInfo_Rsp )
	_body ( TUmsHandle, 1)
	_body ( TTPSipRegPackInfo , 1 )
	_body ( EmGetRegInfoType , 1 )
	_body ( TTPSipRegInfo , 1 )
_ev_end

/***********************<< 全局地址薄UMS注册信息  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsGetRegInfo_UmsRspEx )
_body ( TUmsHandle, 1)
_body ( TRegPackInfoEx, 1)
_body ( TUmsRegPackEx, 1)
_ev_end

/***********************<< 全局地址薄CNS注册信息  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  ev_UmsGetRegInfo_CnsRspEx )
_body ( TUmsHandle, 1)
_body ( TRegPackInfoEx, 1)
_body ( TCnsRegPackEx, 1)
_ev_end

/***********************<< MT 注册信息  >>********************	
*
*/
_event(  ev_UmsGetGkRegInfo_MtRsp )
_body ( TUmsHandle, 1)
_body ( EmGetRegInfoType, 1)
_body ( TTPMtRegInfo, 1)
_ev_end

/***********************<< MCU 注册信息  >>********************	
*
*/
_event(  ev_UmsGetGkRegInfo_McuRsp )
_body ( TUmsHandle, 1)
_body ( EmGetRegInfoType, 1)
_body ( TTPMcuRegInfo, 1)
_ev_end


/***********************<<  下级向上级更新会议结点 >>********************	 
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event(  evtp_Conf_EpCallInfo_Update )
_body ( TUmsHandle  , 1  )	
_body ( TConfNodeCallUpdateTrList, 1 )
_ev_end

/***********************<<  下级向上级更新会议结点 >>********************	 
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event(  evtp_Conf_EpChanInfo_Update )
_body ( TUmsHandle  , 1  )	
_body ( TConfNodeChanUpdateTrList, 1 )
_ev_end

/***********************<<  下级向上级删除会议结点 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event(  evtp_Conf_EpInfo_Del )
_body ( TUmsHandle  , 1  )	
_body( TConfNodeDelTrList, 1)
_ev_end

/***********************<<  上级向下级通知发言人能力 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_YouAreSeeing_Ind )
_body ( TUmsHandle  , 1  )	
_body( TSpeakerCapTr, 1)
_ev_end

/***********************<<  通知终端在多点会议中 H323 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向] 终端 - > UMS	
 *
 */
_event( evtpH323_Conf_MultipleConference_Ind )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  请求终端列表 H323 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向] 终端 - > UMS	
 *
 */
_event( evtpH323_Conf_TerminalListRequest )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  Ums通知CNS主席情况 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_IsChair_Notify )
_body ( TUmsHandle  , 1  )	
_body( BOOL32, 1)
_ev_end

/***********************<<  Ums通知主席有会场离会 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_LeftConf_Notify )
_body ( TUmsHandle  , 1  )	
_body( TConfEpIDInfo, 1)
_ev_end

/***********************<<  Ums通知主席有会场入会 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_JoinConf_Notify )
_body ( TUmsHandle  , 1  )	
_body( TConfEpIDInfo, 1)
_ev_end

/***********************<<  Ums通知CNS加入多点会议  >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_MultConf_Notify )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  Ums通知CNS离开多点会议  >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_CancelMultConf_Notify )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  Ums通知CNS会议状态 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_StatusInfo_Notify )
_body ( TUmsHandle  , 1  )	
_body( TTPConfInfoNtfy, 1)
_ev_end


/***********************<<  Ums通知Ums会场发言人 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_CnsSpeakerCascad_Notify )
_body ( TUmsHandle  , 1  )	
_body(TCnsSpeakerAdjust, 1)
_ev_end

/***********************<<  通知远端哑音 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_MuteRemoteEp_Cmd )
_body ( TUmsHandle  , 1  )	
_body(TMuteRmtEpCmd, 1)
_ev_end


/***********************<<  远端哑音指示 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_MuteRemoteEp_Ind )
_body ( TUmsHandle  , 1  )	
_body(TMuteRmtEpInd, 1)
_ev_end


/***********************<<  通知远端静音 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_QuietRemoteEp_Cmd )
_body ( TUmsHandle  , 1  )	
_body(TQuietRmtEpCmd, 1)
_ev_end


/***********************<<  远端静音指示 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_QuietRemoteEp_Ind )
_body ( TUmsHandle  , 1  )	
_body(TQuietRmtEpInd, 1)
_ev_end

/***********************<<  呼叫未上线会场 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_CallExistEPTr_cmd )
_body ( TUmsHandle  , 1  )	
_body(u16, 1)	//epID
_body(TTPAlias, 1)
_ev_end

/***********************<<  挂断会场 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_DropEPTr_cmd )
_body ( TUmsHandle  , 1  )	
_body(TDropEpCmd, 1)	
_ev_end

/************************<<  电视墙监控 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_TvMonitor_Cmd  )
_body ( TUmsHandle  , 1  )	
_body( TTvMonitorCmdTr, 1)
_ev_end

/************************<<  电视墙监控 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_TvMonitor_Ind  )
_body ( TUmsHandle  , 1  )	
_body( TTvMonitorIndTr, 1)
_ev_end

/************************<<  电视墙监控 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_TvMonitor_stop  )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)
_ev_end

/************************<<  关键帧请求 >>********************
*[消息体]			 
*   NULL	
*[消息方向]	
*
*/
_event( evtp_Conf_AskKeyByScreen  )
_body ( TUmsHandle  , 1  )	
_body( TAskKeyByScreenTr, 1)
_ev_end


/***********************<<  Ums通知UMS主席能力 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_ChairCap_Notify )
_body ( TUmsHandle  , 1  )	
_body( TChairInfoTr, 1)
_ev_end


/***********************<<  UMS通知CMS会议CNS列表 >>********************	
 *[消息方向]	UMS	-->  CMS
 *
 */_event(  evtp_Conf_CnsList_Notify )
 _body ( TUmsHandle  , 1  )	
	_body ( TConfCnsInfo  , 1  )
   _ev_end

   /************************<<  viewlocal >>********************
   *[消息体]			 
   *   NULL	
   *[消息方向]	
   *
   */
   _event( evtp_Conf_ViewLocal_Cmd  )
   _body ( TUmsHandle  , 1  )	
   _ev_end
   
   /************************<<  cannelviewlocal >>********************
   *[消息体]			 
   *   NULL	
   *[消息方向]	
   *
   */
   _event( evtp_Conf_CancelViewLocal_Cmd  )
   _body ( TUmsHandle  , 1  )	
   _ev_end
   
/***********************<<   >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_FlowCtrol )
_body ( TUmsHandle  , 1  )	
_body ( TEpKey  , 1  )	
_body( u16 , 1)//带宽
_ev_end

/***********************<<  调整帧率 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_AdjustFrameRate )
_body ( TUmsHandle  , 1  )	
_body ( TAdjustFrameRate  , 1  )	
_ev_end

/***********************<<  调整分辨率 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_AdjustVidRes )
_body ( TUmsHandle  , 1  )	
_body ( TAdjustVidRes  , 1  )	
_ev_end


/***********************<<清理会议信息   >>********************
 */
_event( evtp_Conf_Clear )
_body ( TUmsHandle  , 1  )	
_ev_end


/***********************<<放像状态更新  >>********************
 */
_event( evtp_Conf_RecPlayState_Nty )
_body ( TUmsHandle  , 1  )
_body ( TUpRecPlayState, 1)
_ev_end

/***********************<< 上级通知下级停止放像  >>********************
 */

 _event( evtp_Conf_StopRecPlay_Req )
 _body ( TUmsHandle  , 1  )
 _body ( u32,	1)
_ev_end


/***********************<< 清除关键帧保护  >>********************
 */

 _event( evtp_Conf_ResetFastUpdate )
 _body ( TUmsHandle  , 1  )
 _body ( u32,	1)
_ev_end

/***********************<< 关闭通道请求  >>********************
 */

 _event( evtp_Close_Chan_Req )
 _body ( TUmsHandle  , 1  )
 _body ( EmChanType,	1) //关闭通道类型
 _body ( TUmsNodeCapset, 1)
_ev_end


//////////////////////////////////////////////////////////////////////////
//码流调度
 _event(ev_GetVid_Req)
 	_body (TUmsHandle, 1)
 	_body(TGetVidInfo, 1)
 _ev_end

 _event(ev_GetVid_Res)
	_body (TUmsHandle, 1)
 	_body(TGetVidInfoRes, 1)
 _ev_end

 _event(ev_GetVid_Stop_Req)
 	_body (TUmsHandle, 1)
 	_body(TGetVidBaseInfo, 1)
 _ev_end

 _event(ev_GetVid_Stop_Res)
 	_body (TUmsHandle, 1)
 	_body(TStopGetVid, 1)
 _ev_end


 /***********************<<  B4通知终端所看目标 >>********************
 *[消息体]			 
 *   NULL	
 *[消息方向]	
 *
 */
_event( evtp_Conf_YouAreSeeingEx_Ind )
_body ( TUmsHandle  , 1  )	
_body( TTpYouAreSeeing, 1)
_ev_end

#ifndef _MakeTpEventDescription_
_ev_segment_end(tpumswithumssipadapter)
};
#endif


#endif // _h_eventoutsipadapter_h__
