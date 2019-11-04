#ifndef _h_eventoutumscall_h__
#define _h_eventoutumscall_h__


#include "tpeventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumscall
{
#endif
	
	_ev_segment( outerumscall )

// Notify类消息
/***********************<<  UMS通知UMC增加会议列表 >>********************	
 *[消息方向]	UMS	-->  UMC
 *
 */
 _event(  evtp_AddConfList_Notify )
_body ( TAddConfList  , 1  )
 _ev_end

/***********************<<  UMS通知UMC删除的会议列表 >>********************	
 *[消息方向]	UMS	-->  UMC
 *
 */_event(  evtp_DelConflist_Notify )
	_body ( TDelConfList  , 1  )
   _ev_end

/***********************<<  UMS通知UMC会议会场列表 >>********************	
 *[消息方向]	UMS	-->  UMC
 *
 */_event(  evtp_UpdateConfCnsList_Notify )
	_body ( TConfCnsInfo  , 1  )
   _ev_end

/***********************<<  UMS通知UMC发言人改变 >>********************	
 *[消息方向]	UMS	-->  UMC
 *
 */
_event(  evtp_SpeakerChange_Notify )  //brd
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  UMS通知CMS主席改变 >>********************	
 *[消息方向]	UMS	-->  CMS
 *
 */
_event(  evtp_ChairManChange_Notify )
_body ( TConfEpID  , 1  )
_ev_end

/***********************<<  UMS通知UMC主席屏幕状态 >>********************	
 *[消息方向]	UMS	-->  UMC
 *
 */
_event(  evtp_ChairStreenStatus_Notify )  //brd
_body ( TChairStreenInfo, 1)
_ev_end

// begin edit by gaoyong
/***********************<<  UMS通知UMC会议讨论列表 >>********************	
 *[消息方向]	UMS	-->  UMC
 *
 */
_event(  evtp_AuxMixInfo_Notify ) //brd
_body ( TConfAuxMixInfo  , 1  )
_ev_end

/***********************<<  UMS通知UMC会议轮询列表 >>********************	
 *[消息方向]	UMS	-->  UMC
 *
 */
_event(  evtp_UpdateConfTurnlist_Notify )  //brd
_body ( TTpPollListNtfy  , 1  )
_ev_end


// cmd消息
/***********************<<  UMC请求UMS添加和删除讨论成员（讨论下用） >>********************	
 *[消息方向]	UMC	-->  UMS
 *
 */
_event(  evtp_UpdateAudMixInfo_cmd )
_body (TDiscussListOpr , 1 )
_ev_end


/***********************<<  回应 >>********************	
 *[消息方向]	UMS	-->  UMC
 *
 */
_event(  evtp_UpdateAudMixInfo_Ind )
_body (TDiscussListOpr , 1 )
_ev_end

/***********************<<  UMC请求UMS开启和关闭讨论，开启和关闭语音激励， 或者非讨论下，更新讨论成员 >>********************	
 *[消息方向]	UMC	-->  UMS
 *
 */
_event(  evtp_StartAuxMix_cmd )
_body (TConfAuxMixInfo , 1 )
_ev_end


/***********************<<  回应 >>********************	
 *[消息方向]	UMS	-->  UMC
 *
 */
_event(  evtp_StartAuxMix_ind )
_body (TConfAuxMixInfo , 1 )
_ev_end

/***********************<< 语音激励开启和关闭  >>********************	
*[消息方向]	umc	-->  ums
*
*/
_event( ev_AuxMixVacSwitch)
_body(TConfAuxMixVacOpr, 1)
_ev_end

/***********************<< 语音激励开启和关闭回应  >>********************	
*[消息方向]	ums	-->  umc
*
*/
_event( ev_AuxMixVacSwitchInd)
_body(TConfAuxMixVacOpr, 1)
_ev_end 

/***********************<<  UMC请求UMS更新轮询列表 >>********************	
*[消息方向]	  UMC	-->  UMS
*
*/
_event(  evtp_UpdateTurn_cmd )
_body ( TConfTurnInfo  , 1  )
_ev_end


/***********************<<  UMC请求UMS更新轮询列表回应 >>********************	
*[消息方向]	UMC	-->  UMS
*
*/
_event(  evtp_UpdateTurn_ind )
_body ( TTpPollListInd  , 1  )
_ev_end

/***********************<<  UMC请求UMS开启轮询 >>********************	
*[消息方向]	UMC	-->  UMS
*	参数为会议ID
*/
_event(  evtp_StartTurn_cmd )
_body ( u16  , 1  )
_ev_end

/***********************<<  UMC请求UMS开启轮询回应>>********************	
*[消息方向]	UMS -->  UMC
*	参数为会议ID
*/
_event(  evtp_StartTurn_ind )
_body ( u16  , 1  )
_body ( EmTPPollResult, 1)
_ev_end


/***********************<<  UMC请求UMS关闭轮询 >>********************	
*[消息方向]	UMC	-->  UMS
*	参数为会议ID
*/
_event(  evtp_StopTurn_cmd )
_body ( u16  , 1  )
_ev_end

/***********************<<  UMC请求UMS关闭轮询回应 >>********************	
*[消息方向]	UMS	-->  UMC
*	参数为会议ID
*/
_event(  evtp_StopTurn_ind )
_body ( u16  , 1  )
_body ( EmTPPollResult, 1) 
_ev_end

/***********************<<  UMC请求UMS暂停暂停轮询 >>********************	
*[消息方向]	UMC	-->  UMS
*	参数为会议ID
*/
_event(  evtp_SuspendTurn_cmd )
_body ( u16  , 1  )
_body ( BOOL32, 1 )
_ev_end

/***********************<<  UMC请求UMS暂停暂停轮询回应 >>********************	
*[消息方向]	UMC	-->  UMS
*	参数为会议ID
*/
_event(  evtp_SuspendTurn_ind )
_body ( u16  , 1  )
_body ( EmTPPollResult, 1)
_ev_end

/***********************<<  UMS通知UMC轮询状态 >>********************	
*[消息方向]	UMS	-->  UMC
*	参数为会议ID
*/
_event(  evtp_TurnStat_ntfy )
_body ( TTpPollStat  , 1  )
_ev_end

/***********************<<  UMC请求UMS选看会场 >>********************	
*[消息方向]	UMC	-->  UMS
*	参数为会议ID
*/
_event(  evtp_ViewObj_cmd )
_body ( TConfEpID  , 1  ) // 填会议id和所要选看会场的id
_body ( u16  , 1  ) // // 选看屏序号 0 1 2
_ev_end

/***********************<<  UMC请求UMS选看会场回应 >>********************	
*[消息方向]	UMS	-->  UMC
*	参数为会议ID
*/
_event(  evtp_ViewObj_ind )
_body ( TConfEpID  , 1  ) // 填会议id和所要选看会场的id
_body ( u16  , 1  ) // // 选看屏序号 0 1 2
_body ( TChanViewRes, 1) 
_ev_end

/***********************<<  UMC请求UMS取消选看会场 >>********************	
*[消息方向]	UMC	-->  UMS
*	参数为会议ID
*/
_event(  evtp_UndoViewObj_cmd )
_body ( u16  , 1) // confid
_body ( u16, 1)  // 选看屏的序号 0 1 2
_ev_end


/***********************<<  UMC请求UMS取消选看会场回应 >>********************	
*[消息方向]	UMS	-->  UMC
*	参数为会议ID
*/
_event(  evtp_UndoViewObj_ind )
_body ( u16  , 1  ) // confid
_body ( u16, 1)  // 选看屏的序号 0 1 2
_body ( EmTPViewResult, 1) 
_ev_end

// end edit by gaoyong 

/***********************<<  CMS请求召开会议 >>********************	
*[消息方向]	UMS	-->  CMS
*
*/
_event(  evtp_StartConfTemplate_Req )
_body ( u16  , 1  )
_ev_end


/***********************<<  CMS请求UMS召开会议结果 >>********************	
*[消息方向]	CMS	-->  UMS
*
*/
_event(  evtp_StartConfTemplate_Ret )
_body ( TStartConfResult  , 1  )
_ev_end


/***********************<<  CMS请求UMS挂断会议 >>********************	
*[消息方向]	CMS	-->  UMS
*	参数为会议ID
*/	
_event(  evtp_HungUpConf_cmd )
_body ( u16  , 1  )
_ev_end

/***********************<<  CMS请求UMS挂断会议结果 >>********************	
*[消息方向]	UMS	-->  CMS
*	参数为会议ID
*/	
_event(  evtp_HungUpConf_result )
_body ( u16  , 1  )			//会议ID
_body ( EmTpDropConfRet, 1) //结果
_ev_end


// begin edit by gaoyong
/***********************<<  UMC临时邀请EP >>********************	
*[消息方向]	UMC	-->  UMS
*
*/ 
_event(  evtp_CallEP_cmd )
_body ( TConfCallEpAddr  , 1  )
_ev_end


/***********************<<  UMC请求UMS呼叫已经存在的EP : 未上线 >>********************	
*[消息方向]	UMS	-->  UMC
*
*/
_event(  evtp_CallExistEP_cmd )
_body ( TConfEpID  , 1  )
_ev_end

/***********************<<  UMC临时邀请EP结果 >>********************	
*[消息方向]	UMC	-->  UMS
*
*/
_event(  evtp_CallEP_result )
_body ( TConfCallEpAddr  , 1  )
_body ( EmCnsCallReason  , 1  )
_ev_end

/***********************<<  UMC请求UMS呼叫已经存在的EP结果>>********************	
*[消息方向]	UMS	-->  UMC
*
*/
_event(  evtp_CallExistEP_result )
_body ( TConfEpID  , 1  )
_body ( EmCnsCallReason  , 1  )
_ev_end

/***********************<<  UMC请求UMS挂断EP >>********************	
*[消息方向]	UMC	-->  UMS
*
*/
_event(  evtp_DropEp_cmd )
_body ( TConfEpID  , 1  )	
_ev_end


/***********************<<  UMC请求UMS挂断EP结果 >>********************	
*[消息方向]	UMS	-->  UMC
*
*/
_event(  evtp_DropEp_Ind )
_body ( TConfEpID  , 1  )
_body ( EmCnsCallReason, 1)	//EmCnsCallReason_hungup 本地挂断成功  EmCnsCallReason_dstnotfind 目标不存在
_ev_end

/***********************<<  CMS请求UMS删除EP >>********************	
*[消息方向]	CMS	-->  UMS   // ums未处理
*
*/
_event(  evtp_DeleteEp_cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  UMC请求UMS指定发言人 >>********************	
*[消息方向]	UMC	-->  UMS
*
*/
_event(  evtp_ApplySpeaker_cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  UMS通知UMC指定发言人结果 >>********************	
*[消息方向]	UMS	-->  UMC
*
*/
_event(  evtp_ApplySpeaker_result )
_body ( TConfEpID  , 1  )	
_body ( EmTpApplySpeakerRet  , 1  )	
_ev_end


/***********************<<  UMC指定远端哑音 >>********************	
*[消息方向]	UMC	-->  UMS
*
*/
_event(  evtp_MuteEp_cmd )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUE指示远端哑音，FALSE取消远端哑音
_ev_end

/***********************<<  UMC指定远端哑音回应 >>********************	
*[消息方向]	UMS	-->  UMC
*
*/
_event(  evtp_MuteEp_Ind )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUE指示远端哑音，FALSE取消远端哑音
_ev_end


/***********************<<  UMC指定远端静音 >>********************	
*[消息方向]	UMC	-->  UMS
*
*/
_event(  evtp_QuietEp_cmd )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUE指示远端静音，FALSE取消远端静音
_ev_end

/***********************<<  UMC指定远端静音回应 >>********************	
*[消息方向]	UMC	-->  UMS
*
*/
_event(  evtp_QuietEp_Ind )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUE指示远端静音，FALSE取消远端静音
_ev_end


/***********************<<  请求开启双流 >>********************	
*[消息方向]	UMC	-->  UMS
*
*/
_event(  evtp_StartDual_Cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  请求开启双流结果  >>********************	
*[消息方向]	UMS	-->  UMC
*
*/
_event(  evtp_StartDual_Ind )
_body ( TConfEpID  , 1  )	
_body ( EmTPDualReason  , 1  )	
_ev_end

/***********************<<  请求关闭双流 >>********************	
*[消息方向]	UMC	-->  UMS
*
*/
_event(  evtp_StopDual_Cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  请求关闭双流结果  >>********************	
*[消息方向]	UMS	-->  UMC
*
*/
_event(  evtp_StopDual_Ind )
_body ( TConfEpID  , 1  )	
_body ( EmTPDualReason  , 1  )	
_ev_end
// end eidt by gaoyong 

/***********************<<  UMS通知CMS双流源改变 >>********************	
 *[消息方向]	UMS	-->  CMS
 *
 */
_event(  evtp_DualEp_Notify )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<< 通知主席会议信息  >>********************	
*[消息方向]	UMS	-->  CMS
*
*/
_event(  evtp_ChairConfInfo_Notify )
_body ( TChairConfInfo  , 1  )	
_ev_end

/***********************<< 会议挂断的原因  >>********************	
*[消息方向]	UMS	-->  CMS
*
*/
_event(  evtp_HungUp_Conf_Reason)
_body ( u16,   1  )    //ConfID
_body ( u32  , 1  )	   //挂断原因
_ev_end

/***********************<< 通知UMC提示信息 >>********************
*[消息方向] UMS -- > CMS
*
*/
_event( evtp_UmsCommonReasonToUI_Ind )
_body ( TTPUmsReasonInd, 1 )
_ev_end
/***********************<< UMS申请加入会议回应 >>********************
*[消息方向] UMS -- > CMS
*
*/
_event( evtp_UmsJoinConf_Req )
_body ( TTPConfEpInfo, 1 )
_ev_end


/***********************<< UMS申请加入会议回应 >>********************
*[消息方向] UMS -- > CMS
*
*/
_event( evtp_UmsJoinConf_Ack )
_body ( TTPConfEpInfo, 1 )
_ev_end
/***********************<< UMS入会后通知 >>********************
*[消息方向] UMS -- > CMS
*
*/
_event( evtp_UmsJoinConf_Notify )
_body ( u16, 1 )
_body ( TTpCallAddr ,1)
_ev_end


/***********************<< CNS申请加入会议回应 >>********************
*[消息方向] UMS -- > CMS
*
*/
_event( evtp_CnsJoinConf_Req )
_body ( TUmsHandle  , 1  )	
_body ( TTPConfEpInfo, 1 )
_ev_end


/***********************<< CNS申请加入会议回应 >>********************
*[消息方向] UMS -- > CMS
*
*/
_event( evtp_CnsJoinConf_Ack )
_body ( TUmsHandle  , 1  )	
_body ( TTPConfEpInfo, 1 )
_ev_end

/***********************<< CNS入会后通知 >>********************
*[消息方向] UMS -- > CMS
*
*/
_event( evtp_CnsJoinConf_Notify )
_body ( TUmsHandle  , 1  )	
_body ( u16, 1 )
_body ( TTpCallAddr ,1)
_ev_end



#ifndef _MakeTpEventDescription_
		_ev_segment_end(outerumscall)
};
#endif


#endif // _h_eventoutumscall_h__
