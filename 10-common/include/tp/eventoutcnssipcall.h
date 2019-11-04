#ifndef _h_eventoutcnssipcall_h__
#define _h_eventoutcnssipcall_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSCALLEVENT
{
#endif 

_ev_segment( outercnssipcall  )
/***********************<< 呼叫会议命令 >>********************	
 *[消息体]
 * TTPDialParam 呼叫参数
 *[消息方向]
 *  cnc -> cns, cns	 ->  cncall
*/
	  _event(  ev_TppMakeCall_Cmd )
	  _body( TTPDialParam ,1 )			
	  _ev_end

	  _event(  ev_TppAnswerCall_Cmd )
	  _ev_end

 /***********************<< 挂断会议命令 >>********************	
 *[消息体]
 * NULL
 *[消息方向]
 * cnc -> cns, cns	 ->  cncall
 */
	  _event(  ev_TppHangUp_Cmd )
	  _ev_end
	  
 /***********************<< 呼叫会议响应 >>********************	
 *[消息体]
 * s32 呼叫ID
 * TTPDialParam 呼叫参数
 *[消息方向]
 *  cns	 <-  cncall
 */	  
	  _event(  ev_TppCallIncoming_Ind )
	  _body( s32 ,1 )						// 呼叫ID
	  _body( TTPDialParam ,1 )				//呼叫参数
	  _ev_end

 /***********************<< 双流通道建立失败回应 >>********************	
 *[消息体]
 * NULL
 *[消息方向]
 *  cns	 <-  cncall
 */	
	  _event( ev_TppDualChannelEstablishFail_Ind )
	  _ev_end

 /***********************<< 建立通道连接回应 >>********************	
 *[消息体]
 * s32
 * s32
 * TTPCapPack
 *[消息方向]
 *  cns	 <-  cncall
 */
	  _event(  ev_TppChannelConnect_Ind )
	  _body( s32 , 1)								//呼叫ID
	  _body( s32, 1)								//能力集数量
	  _body( TTPCapPack, 1)							//拆包
	  _ev_end
	
 /***********************<< 断开通道连接的回应 >>********************	
 *[消息体]
 * s32
 * s32
 * EmTPChannelReason
 *[消息方向]
 *  cns	 <-  cncall
 */
	  _event(  ev_TppChannelDisConnect_Ind )
	  _body( s32 , 1)					//呼叫ID
	  _body( s32, 1)					//通道ID
	  _body( EmTPChannelReason, 1)		//通道断开原因
	  _body( EmTpChannelHandle, 1)
	  _ev_end
	
 /***********************<< 建立呼叫连接的回应 >>********************	
 *[消息体]
 * s32 呼叫ID
 * TTPDialParam 呼叫参数
 *[消息方向]
 *  cns	 <-  cncall
 */
	  _event(  ev_TppCallConnect_Ind )
	  _body( s32, 1 )
	  _body( TTPDialParam, 1 )
	  _ev_end
	
 /***********************<< 建立呼叫连接的回应 >>********************	
 *[消息体]
 * s32 呼叫ID
 * TTPDialParam 呼叫参数
 *[消息方向]
 *  cns	 <-  cncall
 */
	  _event(  ev_TppCallDisconnect_Ind )
	  _body( s32, 1 )					//呼叫ID
	  _body( EmCnsCallReason, 1)		//断开原因
	  _ev_end
	  
	  _event(  ev_TppCapSet_Nty )
	  _ev_end
	
 /***********************<< 挂断回应 >>********************** 
*[消息体]
+EmCnsCallReason
*[消息方向]
*  cns	  ->  cnc
*/
_event(  ev_TppHangUp_Ind )
_body ( EmCnsCallReason, 1 )
_ev_end
 

 /***********************<< 请求添加会议模版 >>********************** 
*[消息体]
+TTPConfTemplate
*[消息方向]
*  cnc	  ->  cns
*/
_event(  ev_CnAddConfTemplate_Req )
_body ( TTPConfTemplate    , 1    )
 _ev_end


  /***********************<< 请求添加会议模版结果 >>********************** 
*[消息体]
+TTPConfTemplate
*[消息方向]
*  cnc	  ->  cns
*/
_event(  ev_CnAddConfTemplate_Rsp )
_body ( TTPConfTemplate    , 1    )
_body( TOprConfTmpResult, 1 )
_ev_end


  /***********************<< CNS发送CNCALL协议栈初始化 >>********************** 
*[消息体]
* TTPDialParam			呼叫参数
*[消息方向]
*  cns	  ->  cncall
*/
_event(  ev_Cn_MakeCall_Cmd )
_body( TTPDialParam, 1 )
_ev_end


  /***********************<< CNS发送CNCALL协议栈初始化 >>********************** 
*[消息体]
* s32				呼叫ID
* BOOL32			回应Answer
* TTPDialParam		呼叫参数
* EmCnsCallReason	呼叫Reason	
*[消息方向]
*  cns	  ->  cncall
*/
_event(  ev_Cn_AnswerCall_Cmd )
_body( s32, 1 )
_body( BOOL32, 1 )
_body( TTPDialParam, 1 )
_body( EmCnsCallReason, 1)
_ev_end


  /***********************<< CNS发送CNCALL协议栈初始化 >>********************** 
*[消息体]
* s32					呼叫ID
* EmCnsCallReason		挂断原因
*[消息方向]
*  cns	  ->  cncall
*/
_event(  ev_Cn_HangUp_Cmd )
_body( s32, 1 )
_body( EmCnsCallReason, 1 )
_ev_end


  /***********************<< CNS发送CNCALL协议栈初始化 >>********************** 
*[消息体]
* s32		呼叫ID
* s32		通道ID
* s32		消息类型
* u16		类容长度
* u8*		类型
*[消息方向]
*  cns	  ->  cncall
*/
_event(  ev_Cn_SendChanCtrl_Cmd )
_body( s32, 1 )
_body( s32, 1 )
_body( s32, 1 )
_body( u16, 1 )
_body( u8, TP_NAME_LEN_256 )
_ev_end


  /***********************<< CNS发送CNAdapter请求Sip注册 >>********************** 
*[消息体]
* TTPSipRegistrarCfg	注册服务器配置信息
* u32					注册句柄
*[消息方向]
*  CNS	 ->  CnAdapter
*/
_event(  ev_Cn_Register_Cmd )
_body( TTPSipRegistrarCfg, 1 )
_body( u32, 1 )
_ev_end


  /***********************<< CNS发送CNAdapter请求不注册 >>********************** 
*[消息体]
* u32					注册句柄
*[消息方向]
*  CNS	  ->  CnAdapter
*/
_event(  ev_Cn_UnRegister_Cmd )
_body( u32, 1 )
_ev_end


  /***********************<< CNS发送CNAdapter设置 >>********************** 
*[消息体]
*[消息方向]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_SetStrategy_Cmd )
_ev_end


  /***********************<< CNS发送CNAdapter设置回调函数 >>********************** 
*[消息体]
*[消息方向]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_SetPAEvent_Cmd )
_ev_end


  /***********************<< CNS发送CNAdapter配置 >>********************** 
*[消息体]
* s32					呼叫ID
* s32					消息类型
* u16					buf长度
* u8*					buf
*[消息方向]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_SendConfCtrl_Cmd )
_body( s32, 1 )
_body( s32, 1 )
_body( u16, 1 )
_body( u8, TP_NAME_LEN_256 )
_ev_end


  /***********************<< CNS发送CNAdapter退出 >>********************** 
*[消息体]
*[消息方向]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_Quit_Cmd )
_ev_end


  /***********************<< CNS发送CNAdapter发送双流 >>********************** 
*[消息体]
* s32					呼叫ID
* TTPMediaStream		双流
* s32					cap数量
*[消息方向]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_SendDual_Cmd )
_body( s32, 1 )
_body( TTPDualCap, 1 )
_ev_end


  /***********************<< CNS发送CNAdapter双流应答 >>********************** 
*[消息体]
* s32					呼叫ID
* CPAMediaStream		双流
* s32					cap数量
*[消息方向]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_AnswerDual_Cmd )
_body( s32, 1 )
_body( TTPDualCap, 1 )
_body( TTPDualCap, 1 )
_ev_end


  /***********************<< CNS发送CNAdapter停止双流 >>********************** 
*[消息体]
* s32					呼叫ID
*[消息方向]
*  CNS	  ->  CNAdapter
*/
_event( ev_Cn_StopDual_Cmd )
_body( s32, 1 )
_body( EmTPChannelReason, 1 )
_ev_end


  /***********************<< CNS发送CNAdapter打印 >>********************** 
*[消息体]
*[消息方向]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_Printf_Cmd )
_ev_end


  /***********************<< CNAdapter发送CNS请求注册 >>********************** 
*[消息体]
*[消息方向]
*  CNAdapter    ->  CNS
*/
_event(  ev_tppregcncall_req )
_ev_end


  /***********************<< CNS回复CNAdapter注册请求 >>********************** 
*[消息体]
*[消息方向]
*  CNS	  ->  CNAdapter
*/
_event(  ev_tppregistercall_rsp )
_ev_end


  /***********************<< 能力集通知 >>********************** 
*[消息体]	
* TCnsCapset				能力集(拆包发，先发能力集)		
*[消息方向]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_CallAVCapset_Nty )
_body( TCnsAVCapset, 1 )
_ev_end

  /***********************<< 全局地址簿获取 >>********************** 
*[消息体]	
	
*[消息方向]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_GetRegInfo )
_body( u32, 1 )
_body( TTPGetRegInfo, 1 )
_ev_end

  /***********************<< CNS发送CNAdapter请求h323去注册 >>********************** 
*[消息体]
* u32					注册句柄
*[消息方向]
*  CNS	  ->  CnAdapter
*/
_event(  ev_Cn_UnGkRegister_Cmd )
_body( u32, 1 )
_ev_end

  /***********************<< 设置音频类型通知>>********************** 
*[消息体]
* EmTpAudioFormat					
*[消息方向]
*  CNS	  ->  CnAdapter
*/
_event(  ev_tppSetAudioFromat_Cmd )
_body( EmTpAudioFormat, 1 )
_ev_end

/***********************<< cns自动挂掉定时器>>********************** 
*					
*[消息方向]
*  CNS	  ->  CNS
*/
_event(  ev_TppAutoHangup_Cmd_timer )
_ev_end

/***********************<<量子加密秘钥通知>>********************** 
*					
*[消息方向]
*  CNCall	  ->  CNS
*/
_event(  ev_tppQtEncryptKey_Nty )
_body( TTpQtEncryptKey, 1 )
_ev_end

/***********************<<量子加密秘钥获取成功或失败的原因通知>>********************** 
*					
*[消息方向]
*  CNCall	  ->  CNS
*/
_event(  ev_tppQtRetReason_Nty )
_body( EmTPQTReason, 1 )
_ev_end

/***********************<<开定制等音效通知>>********************** 
*					
*[消息方向]
*  CNCall	  ->  CNS
*/
_event(  ev_tppStartMix_Nty )
_ev_end

/***********************<<停定制等音效通知>>********************** 
*					
*[消息方向]
*  CNCall	  ->  CNS
*/
_event(  ev_tppStopMix_Nty )
_ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnssipcall )
};
#endif
#endif //TPP_EVENT_H