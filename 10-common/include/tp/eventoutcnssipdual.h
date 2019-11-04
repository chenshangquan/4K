#ifndef _h_eventoutcnssipdual_h__
#define _h_eventoutcnssipdual_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSSIPDUALEVENT
{
#endif 

  _ev_segment( outercnssipdual  )
//双流

/***********************<<  请求双流命令 >>********************	
 *[消息体]
 TTPDualRequest
 *[消息方向]
 *  cnc	  -> cns ，cncall->cns
*/
  _event(  ev_TppRequestDualStream_Cmd )
  _body (TTPDualRequest, 1)
  _ev_end
  
/***********************<<  发送双流命令 >>********************	
 *[消息体]
 TTPDualInfo 双流信息
 *[消息方向]
 *  cnc	  -> cns ，cncall->cns
*/
  _event(  ev_TppSendDual_Cmd )
  _body( TTPDualInfo, 1 )
  _ev_end
 
/***********************<<  停止发送双流命令 >>********************	
 *[消息体]
 * NULL
 *[消息方向]
 *  cnc	  -> cns 
*/
  _event(  ev_TppStopDual_Cmd )
  _ev_end
  
/***********************<<  停止发送双流回应 >>********************	
 *[消息体]
 * NULL
 *[消息方向]
 *  cnc	  <- cns 
*/
  _event(  ev_TppStopDual_Ind )
  _body( EmTPDualReason , 1 )
  _ev_end
 
 /***********************<<  请求发送双流回应 >>********************	
 *[消息体]
 * TTPDualInfoAck
 *[消息方向]
 *  cncall	-> cns 
*/
  _event(  ev_TppSendDualStream_Ind )
  _body( TTPDualInfoAck, 1)
  _ev_end
  
/***********************<<  请求双流关键帧命令>>********************	
 *[消息体]
 * NULL
 *[消息方向]
 *  cncall	-> cns 
*/
  _event(  ev_TppDualSendKeyFrame_Cmd )
  _body(BOOL, 1)
 _ev_end

/***********************<<  开始接收双流回应>>********************	
 *[消息体]
 * u32
 *[消息方向]
 *  cncall	-> cns 
*/
 _event( ev_tppStartRcvDual_Ind )
 _body( u32, 1 )
 _ev_end
 
/***********************<<  停止接收双流回应>>********************	
 *[消息体]
 * u32
 *[消息方向]
 *  cncall	-> cns 
*/
 _event( ev_tppStopRcvDual_Ind )
  _body( u32, 1 )
_ev_end

/***********************<<  发送双流 >>********************	
 *[消息体]
 * NULL 
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_TppStartDual_Cmd )
_ev_end

/***********************<<  发送双流回应 >>********************	
 *[消息体]
 EmTPDualReason
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppStartDual_Ind )
_body( EmTPDualReason , 1 )
_ev_end


/***********************<<  是否在发双流通知 >>********************	
 *[消息体]
 BOOL
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppIsDual_Nty )
_body( BOOL , 1 )
_ev_end


/***********************<<  是否在收双流通知 >>********************	
 *[消息体]
 BOOL
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppIsRcvDual_Nty )
_body( BOOL , 1 )
_ev_end

/***********************<<  增加双流接受地址 >>********************	
 *[消息体]
 *[消息方向]
 *  cnc	  -> cns
 *  BODY中分别放入视频和音频能力（顺序不能颠倒）
*/
_event(  ev_TppAddDualRcvAddr_Cmd )
_body( TTPCnMediaTransPort, 2 )
_ev_end

/***********************<<  增加双流接受地址回应 >>********************	
 *[消息体]
 EmTPDualReason
 *[消息方向]
 *  cnc	  <- cns
 * BODY中分别放入加入视频和音频能力的结果，本地视音頻能力和标识（顺序不能颠倒)
*/
_event(  ev_TppAddDualRcvAddr_Ind )
_body( EmTPAddDualRcvResult, 2 )
_body( TTPCnMediaTransPort, 2 )
_body( u16,  2 )
_ev_end

/***********************<<  删除双流接受地址 >>********************	
 *[消息体]
 *　u16　槽位号　　
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_TppDelDualRcvAddr_Cmd )
_body( u16,  1 )
_ev_end


/***********************<<  删除双流接受地址回应 >>********************	
 *[消息体]
 * EmTPDeleteDualRcvResult
 * u16 槽位号
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_TppDelDualRcvAddr_Ind )
_body( EmTPDeleteDualRcvResult, 1 )
_body( u16, 1 )
_ev_end



/***********************<<  双流通道打开请求到来 >>********************	
 *[消息体]
 * NULL
 *[消息方向]
 * cncall -> cns
*/
_event(  ev_TppDualChannelIncoming_Nty )
_body(TTPDualCap, 1)
_ev_end

/***********************<<  请求选看双流 >>********************	
 *[消息体]
 * u16 屏号
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_TppSelDualView_Cmd )
_body( u16, 1 )
_ev_end
  

/***********************<<  请求选看双流回应>>********************	
 *[消息体]
 * u16 屏号
 * EmTPAddDualRcvResult 添加结果
 * s8 双流终端名称
 *[消息方向]
 *  cns	  -> cnc
*/
_event(  ev_TppSelDualView_Ind )
_body( u16, 1 )
_body( EmTPAddDualRcvResult, 1 )
_body( s8, TP_MAX_NAME_LEN +1 )
_ev_end


/***********************<<  取消选看双流 >>********************	
 *[消息体]
 * u16 屏号
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_TppCancelSelDualView_Cmd )
_body( u16, 1 )
_ev_end
  

/***********************<<  取消选看双流回应>>********************	
 *[消息体]
 *[消息方向]
 *  cns	  -> cnc
*/
_event(  ev_TppCancelSelDualView_Ind )
_body( u16, 1 )
_body( EmTPDeleteDualRcvResult, 1 )
_ev_end

/***********************<<  PAD双流关键帧请求>>********************	
 *[消息体]
 *[消息方向]
 *u16 SlotID
 *BOOL bForce 是否强制
 *  cnc	  -> cns
*/
_event(  ev_TppPadDualKeyFrame_Req )
_body( u16, 1 )
_body( BOOL, 1 )
_ev_end


/***********************<<  多点会议双流请求 >>********************	
 *[消息体]
 *TConfEpID 会议ID
 *[消息方向]
 *  cnc	  -> cns
*/
_event(  ev_TppConfStartDual_Cmd )
_body( TConfEpID, 1 )
_ev_end

/***********************<<  多点会议双流请求应答 >>********************	
 *[消息体]
 *TConfEpID 会议ID
 *EmTPDualReason 发送双流结果
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppConfStartDual_Ind )
_body( TConfEpID, 1 )
_body( EmTPDualReason, 1 )
_ev_end

/***********************<<  多点会议双流会场广播通知 >>********************	
 *[消息体]
 *TConfEpID 会议ID
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppConfDualEp_Nty )
_body( TConfEpID, 1 )
_ev_end

/***********************<<  双流终端掉线挂断双流 >>********************	
 *[消息体]
 *NULL
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppStopDualOffLine_Cmd )
_ev_end

/***********************<<  双流终端掉线挂断双流 >>********************	
 *[消息体]
 * EmTPChannelReason
 *[消息方向]
 *  cnc	  <- cns
*/
_event(  ev_TppDualRcvInterrupt_Nty )
_body( EmTPChannelReason, 1 )
_ev_end



/***********************<<  多点会议停双流请求 >>********************	
 *[消息体]
 *TConfEpID 会议ID
 *[消息方向]
 *  cnc	  -> cns
*/
_event( ev_TppConfStopDual_Cmd )
_body( TConfEpID, 1 )
_ev_end

/***********************<<  多点会议停双流请求回应 >>********************	
 *[消息体]
 *TConfEpID 会议ID
 *EmTPDualReason 发送双流结果
 *[消息方向]
 *  cnc	  <- cns
*/
_event( ev_TppConfStopDual_Ind )
_body( TConfEpID, 1 )
_body( EmTPDualReason, 1)
_ev_end

//Add by tanxiaodong 2012-07-17.
/***********************<<设置双流输入端口名称请求  >>********************
*[消息体]
* TVgaInfo 双流源Vga信息
* BOOL 是否设置成功
*[消息方向]
*  cnc	  -> cns
*/
_event( ev_TppSetDualInputPortName_Cmd )
_body(TVgaInfo, 1)
_body(BOOL, 1)
_ev_end

/***********************<<设置双流输入端口名称回应  >>********************
*[消息体]
* BOOL是否设置成功
*[消息方向]
*  cns	  -> cnc
*/
_event( ev_TppSetDualInputPortName_Ind )
_body( BOOL, 1)
_ev_end
  
/***********************<<选择双流输入端口请求  >>************************
*[消息体]
*EmVgaType 要切换的输入演示源类型
*EmVgaType 输出演示源类型
*[消息方向]
*  cns	  -> mt
*/
_event( ev_TppSelDualInputPort_Cmd )
_body(EmVgaType, 2)
_ev_end
	
/***********************<<选择双流输入端口回应  >>************************
*[消息体]
*BOOL 切换结果
*EmVgaType 切换后的演示源输入类型
*EmVgaSwitchResult切换结果
*[消息方向]
*  mt	   -> cns
*/
_event( ev_TppSelDualInputPort_Ind )
_body(BOOL, 1)
_body(EmVgaType, 1)
_body(EmVgaSwitchResult, 1)
_ev_end

/***********************<<当前VGA接口信息通知  >>************************
*[消息体]
* TVgaInfo 7个演示源信息
* TVgaInfo 默认演示源信息
* EmVgaType 当前演示源类型
*TTPVgaMixInfo
*[消息方向]
*  cns	   -> cnc
*/
_event( ev_TppCurrentVgaInfo_Nty )
_body(TVgaInfo, CNS_VGA_TYPE_NUM)
_body(TVgaInfo, 1)
_body(EmVgaType, 1)
_body(TTPVgaMixInfo, 1)
_ev_end

/***********************<<当前会议VGA接口信息通知  >>************************
*[消息体]
* EmVgaType 当前演示源类型
*[消息方向]
*  cns	   -> cnc
*/
_event( ev_TppConfVgaInfo_Nty )
_body(EmVgaType, 1)
_ev_end
//End to add.

/***********************<<检测双流源接口是否有源的定时器  >>************************
*[消息体]
*NULL
*[消息方向]
*  cns	   -> cns
*/
_event( ev_TppCheckDualSrc_Timer )
_ev_end

/***********************<< 串口功能测试消息 >>************************
*[消息体]
*NULL
*[消息方向]
*  cns	   -> cns
*/
_event( ev_TppProduceTestSerial_Cmd )
_body(EmSerialType, 1)
_body(EmSerialType, 1)
_ev_end

/***********************<<选择双流输入端口定时器  >>************************
*[消息体] vcs是否开启双流
*[消息方向]
*  cncall	   -> cns
*/
_event( ev_TppChgSecVidSend_Cmd )
_body( BOOL, 1 )
_ev_end

/***********************<<  是否开始文件双流通知 >>********************	
 *[消息体]
 *  +BOOL                  TRUE=开始 FALSE =停止
 *[消息方向]
 *  TPad	  -> cns
*/
_event(  ev_TppTPadDualVideo_Cmd )
_body( BOOL , 1 )
_ev_end

/***********************<< 开始文件双流命令  >>************************
 *[消息体]			 
 *  +BOOL             TRUE=PC双流 FALSE =非PC双流
 *[消息方向]
 *
 *    cns => TPad
 */_event(  ev_TppTPadDualVideo_Ind   )
   _body ( BOOL, 1 )
   _ev_end

/***********************<<  开始文件双流命令 >>********************	
 *[消息体]
 *  +TTPCnMediaTransPort   本地接收的rtp地址和端口 
 *[消息方向]
 *  TPad <- cns
*/
_event(  ev_TppTPadDualRcvAddr_Cmd )
_body( TTPCnMediaTransPort, 1 )
_ev_end

/***********************<<  增加文件双流接受地址回应 >>********************	
 *[消息体]
 *EmTPAddDualRcvResult
 *TTPCnMediaTransPort
 *u16
 *[消息方向]
 *  TPad -> cns
 * BODY中加入视频结果，本地视頻能力和标识
*/
_event(  ev_TppTPadDualRcvAddr_Ind )
_body( EmTPAddDualRcvResult, 1 )
_body( TTPCnMediaTransPort, 1 )
_body( u16,  1 )
_ev_end

/***********************<<检测演示源接口状态  >>************************
*[消息体]
*BOOL 演示源接口是否有源
*[消息方向]
*  cnmp	   -> cns
*/
_event( ev_TppGetDualVidSrc_Nty )
_body( BOOL, 1 )
_ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnssipdual )
};
#endif
#endif //TPP_EVENT_H
