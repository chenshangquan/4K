#ifndef _h_eventoutcnsmp_h__
#define _h_eventoutcnsmp_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSMPPEVENT
{
#endif 

  _ev_segment( outercnsmp  )

/***********************<< 终端注册cns请求 >>********************	
 *[消息体]
 * TMtTPEpParam
 *[消息方向]
 *  cns	  <- mt
*/
  _event(  ev_tppregister_req )
  _body( TMtTPEpParam, 1)
  _ev_end

/***********************<< 终端注册cns的回应 >>********************	
 *[消息体]
 * EmCnMtRegResult
 *[消息方向]
 *  cns	  -> mt
*/
  _event(  ev_tppregister_rsp )
  _body( EmCnMtRegResult, 1 )
  _ev_end

/***********************<< 设置音频解码参数 >>********************	
 *[消息体]
 * TMtADecParam
 *[消息方向]
 *  cns	  -> mt
 */
  _event(  ev_tppSetADecParamCmd )
  _body( TMtADecParam, 1)
  _ev_end

/***********************<< 设置音频编码参数 >>********************	
 *[消息体]
 * TMtAEncParam
 *[消息方向]
 *  cns	  -> mt
 */
  _event(  ev_tppSetAEncParamCmd )
  _body( TMtAEncParam, 1)
  _ev_end

/***********************<< 设置视频解码参数 >>********************	
 *[消息体]
 * TMtVDecParam
 *[消息方向]
 *  cns	  -> mt
 */
  _event(  ev_tppSetVDecParamCmd )
  _body( TMtVDecParam, 1)
  _ev_end     

  /***********************<< 设置视频编码参数 >>********************	
 *[消息体]
 * TMtVEncParam
 *[消息方向]
 *  cns	  -> mt
 */
  _event(  ev_tppSetVEncParamCmd )
  _body( TMtVEncParam, 1)
  _ev_end

 /***********************<< 开启编解码命令 >>********************	
 *[消息体]
 * TTpCodecComponent
 *[消息方向]
 *  cns	  -> mt
 */
  _event(  ev_tppCodecStartCmd )
  _body( TTpCodecComponent, 1 )
  _ev_end

 /***********************<< 停止编解码器命令 >>********************	
 *[消息体]
 * TTpCodecComponent
 *[消息方向]
 *  cns	  -> mt
 */
  _event(  ev_tppCodecStopCmd )
  _body( TTpCodecComponent, 1 )
  _ev_end

 /***********************<< 向终端请求关键帧的命令 >>********************	
 *[消息体]
 * TTpCodecComponent
 *[消息方向]
 *  cns	  -> mt
 */
  _event(  ev_tppSndKeyFrame_Req )
  _body( TTpCodecComponent, 1)
  _ev_end
  
 /***********************<< 调整编解码器码率的命令 >>********************	
 *[消息体]
 * TTpCodecComponent
 *u16 码率
 *[消息方向]
 *  cns	  -> mt
 */
  _event(  ev_tppFlowCtrl_Cmd )
  _body( TTpCodecComponent, 1)
  _body( u16, 1)
  _ev_end

/***********************<< 选看本地的命令 >>********************	
 *[消息体]
 * u16
 *[消息方向]
 *  cns	  -> mt
 */
  _event(  ev_tppViewLocal_Cmd )
  _body( u16, 1)
  _ev_end
  
/***********************<< 选看其他会场的命令 >>********************	
 *[消息体]
 * u16
 *[消息方向]
 *  cns	  -> mt
 */
  _event(  ev_tppViewcViewOther_Cmd )
  _body( u16, 1)
 _ev_end

/***********************<< 向终端请求关键帧的命令 >>********************	
 *[消息体]
 * EmTPVideoType 视频类型
 * EmTPMtVideoPort 视频端口
 * u8 DVIMode
 * u8 编解码位置
 *[消息方向]
 *  cns	  -> mt
 */
  _event( ev_tppVideoSourceSelCmd )
  _body ( EmTPVideoType    , 1    )
  _body ( EmTPMtVideoPort    , 1    )
  _body ( u8    , 1    )
  _body ( u8    , 1    )
  _ev_end

  ///////////////////////////////////////
  /***********************<< 哑音命令 >>********************	
 *[消息体]
 * BOOL
 *[消息方向]
 *  cns	  -> mt,cnc->cns
 */
  _event(  ev_tppMute_Cmd )
  _body( BOOL, 1)
  _ev_end

/***********************<< 静音命令 >>********************	
 *[消息体]
 * BOOL
 *[消息方向]
 *  cns	  -> mt,cnc->cns
 */
  _event(  ev_tppQuiet_Cmd )
  _body( BOOL, 1)
  _ev_end
  
/***********************<< 静音消息回应 >>********************	
 *[消息体]
 * BOOL
 *[消息方向]
 *  cns	  <- mt,cnc<-cns
 */
	_event( ev_tppQuietInd    )
   _body ( BOOL    , 1    )
   _ev_end

/***********************<< 哑音消息回应 >>********************	
 *[消息体]
 * BOOL
 *[消息方向]
 *  cns	  <- mt, cnc<-cns
 */
   _event( ev_tppMuteInd    )
   _body ( BOOL    , 1    )
   _ev_end

  /***********************<< 调整输入音量的命令 >>********************	
 *[消息体]
 * u8 输入音量
 * u8 编解码器位置
 *[消息方向]
 *  cns	  -> mt,cnc->cns
 */
 _event( ev_tppInputVolumeCmd )
   _body ( u8    , 1    )
   _body ( u8, 1 )
   _ev_end

  /***********************<< 调整输入音量的回应 >>********************	
 *[消息体]
 * u8 输入音量
 *[消息方向]
 *  cns	  <- mt,cnc<-cns
 */
 _event(  ev_tppInputVolumeInd  )
   _body ( u8    , 1    )
   _ev_end

  /***********************<< 调整输出音量的命令 >>********************	
 *[消息体]
 * u8 输出音量
 * u8 编解码器位置
 *[消息方向]
 *  cns	  -> mt,cnc->cns
 */
_event( ev_tppOutputVolumeCmd )
   _body ( u8    , 1    )
   _body ( u8, 1 )
   _ev_end

  /***********************<< 调整输出音量的回应 >>********************	
 *[消息体]
 * u8 输出音量
 *[消息方向]
 *  cns	  <- mt,cnc<-cns
 */
_event(  ev_tppOutputVolumeInd  )
   _body ( u8    , 1    )
   _ev_end
///////////////////////

/***********************************/
 /***********************<< 设置音频的Aac参数的命令 >>********************	
 *[消息体]
 * EmTpCodecComponent 
 * u8 Aac通道类型
 * u32 Aac采样率
 * u16 Aac码率
 * EmTpAudioFormat 音频格式
 * u16 编解码器位置
 *[消息方向]
 *  cns	  -> mt,cnc->cns
 */
_event( ev_tppAudAacParam_Cmd )
_body( EmTpCodecComponent, 1 )
_body( u8, 1 )
_body( u32, 1 )
_body( u16, 1 )
_body( EmTpAudioFormat, 1 )
_body( u16, 1 )
_ev_end




_event( ev_tppSetDvi2IntoDvi1Out )
_ev_end

_event( ev_tppSetMainDecIntoDvi1Out )
_ev_end

/***********************<< 获取视频源状态的命令 >>********************	
 *[消息体]
 * EmTpCodecComponent
 * BOOL 是否正在切换视频源
 *[消息方向]
 *  cns	  -> mt
 */
_event( ev_tppGetVidSrcStatusCmd )
_body( EmTpCodecComponent, 1 )
_body( BOOL, 1 )
_ev_end

/***********************<< 获取视频源状态的消息回应>>********************	
 *[消息体]
 * EmTpCodecComponent
 * BOOL 该视频是否有输入源
 * BOOL 是否正在切换视频源
 *[消息方向]
 *  cns	  <- mt
 */
_event( ev_tppGetVidSrcStatusInd )
_body( EmTpCodecComponent, 1 )
_body( BOOL , 1 )
_body( BOOL, 1 )
_ev_end

/***********************<< 会议ep列表 >>********************	
 *[消息体]
s8* 文件全路径名
 *[消息方向]
 *  cns	  <- mt
*/
_event(  ev_CnSnapshotShow_Cmd )
_body ( s8    , 128    )
_ev_end

/***********************<< 调整通道码率的命令 >>********************	
 *[消息体]
 * s32 通道ID
 * u16 码率
 *[消息方向]
 *  cncall	  -> cns
 */
_event( ev_tppFlowCtrlFromStack_Cmd )
_body( s32, 1 )
_body( u16, 1 )
_ev_end

/***********************<< 请求关键帧的命令 >>********************	
 *[消息体]
 * s32 通道ID
 *[消息方向]
 *  cncall	  -> cns
 */
_event( ev_tppSndKeyFrameFromStack_Req )
_body( s32, 1 )
_ev_end

/***********************<< 选看远端命令的消息回应 >>********************	
 *[消息体]
 * s32 通道ID
 * TTPChanSelecteCascadRes 
 *[消息方向]
 *  cncall	  -> cns
 */
_event( ev_CnSingleViewFromStack_Ind )
_body( s32, 1 )
_body( TTPChanSelecteCascadRes, 1 )
_ev_end

/***********************<< 取消选看远端命令的消息回应 >>********************	
 *[消息体]
 * s32 通道ID
 * TTPChanSelecteCascadCancelRes 
 *[消息方向]
 *  cncall	  -> cns
 */
_event( ev_CnCancelSingleViewFromStack_Ind )
_body( s32, 1 )
_body( TTPChanSelecteCascadCancelRes, 1 )
_ev_end

/***********************<< 选看远端命令 >>********************	
 *[消息体]
 * s32 通道ID
 *[消息方向]
 *  cncall	  -> cns
 */
_event( ev_CnChanViewLocalCmdFromStack )
_body( s32, 1 )
_ev_end

/***********************<< 取消选看远端命令 >>********************	
 *[消息体]
 * s32 通道ID
 *[消息方向]
 *  cncall	  -> cns
 */
_event( ev_CnChanCancelViewLocalCmdFromStack )
_body( s32, 1 )
_ev_end

 /***********************<<添加网管服务器 >>************************	
 *[消息体]			 
 *  TTPNMServerCfg 
 *[消息方向]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtAddNMServerCmd  )
 _body( TTPNMServerCfg, 1 )
 _ev_end
 
 /***********************<<删除网管服务器 >>************************	
 *[消息体]			 
 *  TTPNMServerCfg 
 *
 *[消息方向]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtDelNMServerCmd  )
 _body( TTPNMServerCfg, 1 )
 _ev_end
 
 /***********************<<修改网管服务器 >>************************	
 *[消消息体]			 
 *  TTPNMServerCfg
 *[消息方向]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtModifyNMServerCmd  )
 _body( TTPNMServerCfg, 1 )
 _ev_end

  /***********************<< 向终端请求关键帧的命令 >>********************	
 *[消息体]
 * TTpCodecComponent
 *[消息方向]
 *  cnmp	  -> cns
 */
  _event(  ev_tppFastUpdate_Cmd )
  _body( TTpCodecComponent, 1)
  _ev_end

   /***********************<< 向ums请求去除关键帧保护 >>********************	
 *[消息体]
 * u32
 *[消息方向]
 * cns	  -> ums
 */
  _event(  ev_tppChanResetKeyFrame_Req )
  _body( u32, 1)
  _ev_end

   /***********************<< 主视频设置通知 >>********************	
  *[消息体]
  *TTPVideoInfoTool    主视频配置项  
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetVedioInfo_Nty)
  _body(TTPVideoInfoTool , 1)
  _ev_end

  _event(  ev_tppMicPower )
  _body( TTpMicState, 1 )
  _ev_end

  _event(  ev_tppMicSinglePower )
  _body( u8, 1 )
  _body( BOOL, 1 )
  _ev_end

  /***********************<< 哑音消息通知 >>********************	
 *[消息体]
 * BOOL
 *[消息方向]
 *  cns	  <- mt, cnc<-cns
 */
   _event( ev_tppMicMuteNty    )
   _body ( BOOL    , 1    )
   _ev_end
   /***********************<< 哑音消息通知 >>********************	
 *[消息体]
 * BOOL
 *[消息方向]
 *  cns	  <- mt, cnc<-cns
 */
   _event( ev_tppCncMuteNty    )
   _ev_end
#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnsmp )
};
#endif
#endif //TPP_EVENT_H
