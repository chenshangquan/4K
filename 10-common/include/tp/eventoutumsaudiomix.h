#ifndef _h_eventoutumsaudiomix_h__
#define _h_eventoutumsaudiomix_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emouterumsaudiomix
{
#endif

	_ev_segment( tpumswithumsaudiomix )

 /***********************<<  设备管理器反馈注册失败 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] audiomixeqp -> audiomix
 *
 */
 _event(  ev_AudioMixInitCfg_NACK )
 _ev_end
   
 /***********************<<  设备管理器反馈注册成功 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] audiomixeqp -> audiomix
 *
 */
 _event(  ev_AudioMixInitCfg_ACK )
 	_body(u16,1)
	_body(TUmsRSParam, 1)
 _ev_end

   /***********************<<  会议开启初始化一组混音 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] umscall -> audiomix
 *
 */
 _event(  ev_InitOneAudMixGrp_Req )
	_body(u16,1)   //会议ID
	_body(u16,1)   //起始端口
	_body(EmTpAudioFormat,1) //音频格式
	_body(EmTPEncryptType, 1) //加密方式
	_body(u16,1)   //语音激励保护时间
 _ev_end

  /***********************<<  会议结束取消一组混音 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] umscall -> audiomix
 *
 */
 _event(  ev_QuiteOneAudMixGrp_Req )
	_body(u16, 1)
 _ev_end

 /***********************<<  请求打开一路混音 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] umscall -> audiomix
 *
 */
 _event(  ev_OpenOneAudMixChan_Req )
	_body(u16, 1)//EpID
	_body(u16, 1)//AudSndNum
	_body(u16, 1)//Ep ChanIndex
	_body(TTPTransAddr, 1)
 _ev_end

  /***********************<<  请求取消一路混音 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] umscall -> audiomix
 *
 */
 _event(  ev_CloseOneAudMixChan_Req )
	_body(u16 , 1 )//EpID
	_body(u16 , 1 )//Ep Chan Index
	_body(TEqpRes , 1 )//Ep Chan Index
 _ev_end

 /***********************<<  请求打开一路混音 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] audiomix->umscall 
 *
 */
 _event(  ev_OpenOneAudMixChan_Ind )
	_body( u16, 1 )     //EpID
	_body( u16, 1 )     //EpChanIndex
	_body( u16, 1 )  //AudMix ChanIndex
	_body( BOOL32, 1 )   //状态
 _ev_end

 /***********************<<  混音模块中，MediaRcv向混音器设置接收时 出错 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] audiomix->umscall 
 *
 */
 _event(  ev_AudMixSetMediaRev_Ind )
	_body(BOOL32, 1 )   //状态
	_body( u16, 1 )     //EpID
 _ev_end

  /***********************<<  请求取消一路混音 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] audiomix->umscall 
 *
 */
 _event(  ev_CloseOneAudMixChan_Ind )
	_body(u16, 1)
	_body(BOOL32, 1)
	_body(TEqpRes, 1)
 _ev_end		

 /***********************<<  激励出来的标识 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] audiomix->umscall 
 *
 */
 _event(  ev_AudMixExciteToCall_Ind )
	_body(u16 , 1)
	_body(u16 , 1)
	_body(u32 , 1)
 _ev_end

  /***********************<<  手动切换发言人后，更新混音器发言人 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] audiomix->umscall 
 *
 */
 _event(  ev_CallExciteToAudMix_Ind )
	_body(u16 , 1)
	_body(u16 , 1)
 _ev_end

  /***********************<<  通知界面混音器状态 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] audiomix->CMC 
 *
 */
_event(  evtp_AudMixStatus_Notify )
	_body ( TAudMixStat  , 1  )		//会议ID
_ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end(tpumswithumsaudiomix)
};
#endif


#endif // _h_eventoutumsaudiomix_h__
