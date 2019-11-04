#ifndef _h_innereventcns_h__
#define _h_innereventcns_h__


#include "cnseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsInnerToCns
{
#endif

_ev_segment( innercns )

 /***********************<<cncall链接cns的内部定时器>>************************	
 *[消消息体]			 
 *  NULL
 *[消息方向]
 *    cncall => cncall
 */
_event(  ev_tppregcall_timer )
_ev_end

/***********************<<cncall链接cns超时重连>>************************	
 *[消消息体]			 
 *  NULL
 *[消息方向]
 *    cncall => cncall
 */
_event(  ev_tppregcall_connect_time_out_timer )
_ev_end

/***********************<<cns各模块启动命令>>************************	
 *[消消息体]			 
 *  NULL
 *[消息方向]
 *    cns => cns
 */
_event(  ev_TpModuleStartCmd )
_ev_end

/***********************<<cncall链接上cnsubroutinemgr,然后cnsubroutinemgr通知cnservice>>************************	
 *[消消息体]			 
 *  NULL
 *[消息方向]
 *    cns => cns
 */
_event(  ev_TpCnCallConnSuccessCmd )
_ev_end

/***********************<<ccncall断开cnsubroutinemgr,然后cnsubroutinemgr通知cnservice>>************************	
 *[消消息体]			 
 *  NULL
 *[消息方向]
 *    cns => cns
 */
_event(  ev_TpCnCallConnFailCmd )
_ev_end

/***********************<<cncall断开cnsubroutinemgr,然后cncall重新连接上cnsubroutinemgr>>************************	
 *[消消息体]			 
 *  NULL
 *[消息方向]
 *    cns => cns
 */
_event(  ev_TpCnCallRepeatConnCmd )
_ev_end

/***********************<<会场上线>>************************	
 *[消消息体]			 
 *  TMtTPEpParam 会场参数
 *[消息方向]
 *   terinterface->cnservice 
 */
_event(  ev_TpCnOnline_Nty )
_ev_end
 
/***********************<<双流会场上线>>************************	
 *[消消息体]			 
 *  TMtTPEpParam 会场参数
 *[消息方向]
 *   terinterface->cnservice 
 */
_event(  ev_TpCnDualOnline_Nty )
_ev_end

/***********************<<会场掉线>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *   terinterface<->cnservice 
 */
_event(  ev_TpCnOffline_Nty )
_ev_end

/***********************<<双流会场掉线>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *   terinterface<->cnservice 
 */
_event(  ev_TpCnDualOffline_Nty )
_ev_end

/***********************<<会场掉线挂断>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *   cns-> cns
 */
_event(  ev_TppOffLineHangUp_Cmd )
 _ev_end

 /***********************<<设置音频解码参数>>************************	
 *[消消息体]			 
 * TMtADecParam 音频解码参数
 *[消息方向]
 *   mediatransservice-> terinterface
 */
_event(  ev_Cn_SetADecParamCmd )
_body( TMtADecParam, 1)
_ev_end

 /***********************<<设置音频编码参数>>************************	
 *[消消息体]			 
 * TMtAEncParam 音频编码参数
 *[消息方向]
 *   mediatransservice-> terinterface
 */
_event(  ev_Cn_SetAEncParamCmd )
_body( TMtAEncParam, 1)
_ev_end

 /***********************<<设置音视频解码参数>>************************	
 *[消消息体]			 
 * TCnVideoParam 视频参数
 *[消息方向]
 *   mediatransservice-> terinterface
 */
_event(  ev_Cn_SetVDecParamCmd )
_body( TMtVDecParam, 1)
_ev_end

 /***********************<<设置视频编码参数>>************************	
 *[消消息体]			 
 * TCnVideoParam 视频参数
 *[消息方向]
 *   mediatransservice-> terinterface
 */
_event(  ev_Cn_SetVEncParamCmd )
_body( TCnVideoParam, 1)
_ev_end

 /***********************<<显示在线会场>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cns->cns
 */
_event(  ev_Cn_ShowActiveConf_Dump )
_ev_end

 /***********************<<cnc登录>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cns->cns
 */
_event(  ev_CnCncLogin_Ind )
_body( TLoginUserMsg, MAX_CNC_USER )
_ev_end

 /***********************<<cnc退出>>************************	
 *[消消息体]			 
 * u8 Pad ID
 *[消息方向]
 *  cns->cns
 */
_event(  ev_CnCncLogout_Ind )
_body( u8, 1)
_ev_end

 /***********************<<请求关键帧定时器>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cns->cns
 */
_event(  ev_CnRequestKeyFrame_Timer )
_ev_end

 /***********************<<请求双流关键帧定时器>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cns->cns
 */
_event(  ev_CnRequestDualKeyFrame_Timer )
_ev_end

 /***********************<<cns重启命令>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cns->cns
 */
_event(  ev_TpModuleRebootCmd )
_ev_end

 /***********************<<修改系统时间通知>>************************	
 *[消消息体]			 
 * time_t
 *[消息方向]
 *  cns->cns
 */
_event(  ev_CnSysTimeChangeNotify )
_body( time_t, 1)
_ev_end

 /***********************<<设置备用网卡>>************************	
 *[消消息体]			 
 * BOOL 备用网卡是否有效
 *[消息方向]
 *  cnc->cns
 */
_event( ev_CnSetEth1_Cmd )
_body( BOOL, 1)
_ev_end


 //Added by meifang
 ////////////////////CnAgent模块消息//////////////////////

  /***********************<< Guard获取cns系统信息 >>********************	
 *[消息体]			 
 *   无
 *[消息方向]
 *   cnGuard => cnGuard
 */_event(  ev_CnScanSystem  )
   _ev_end

 /***********************<< NotifyObzerver结束 >>********************	
 *[消息体]			 
 *   无
 *[消息方向]
 *    UE => UE
 */_event(  ev_CnNotifyObzerverCompletedInd  )
   _ev_end

 /***********************<< 初始化告警APP  >>************************	
 *[消息体]			 
 *    TSNMPCfg
 *
 *[消息方向]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtInitInd  )
 _body( TTPNMServerCfg, 2 )
 _ev_end

 /***********************<< 系统重启后通知 >>************************	
 *[消息体]			 
 *
 *[消息方向]
 *    CNS => AGENT
 */_event(  ev_CnAgtSysRestarInd  )
 _body( u16, 1 )
 _ev_end
 
 //Added by meifang
 /***********************<< Cpu状态改变 >>************************	
 *[消息体]			 
 *    u32 CPU使用率
 *
 *[消息方向]
 *    GUARD => AGENT
 */
 _event(  ev_CnAgtCpuInd  )
 _body( u32, 1 )
 _ev_end

 /***********************<< 内存状态改变 >>************************	
 *[消息体]			 
 *    TAlarmCode
 *
 *[消息方向]
 *    CNS => AGENT
 */_event(  ev_CnAgtMemoryInd  )
 _body( u32, 1 )
 _ev_end

 /***********************<<获取 cns 会场信息 >>************************	
 *[消息体]			 
 *    TTPCnsInfo 
 *
 *[消息方向]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtGetCnsInfoInd  )
 _body( TTPCnsInfo, 1 )
 _ev_end
 
 /***********************<<获取 cns 会场状态 >>************************	
 *[消息体]			 
 *  TTPCurCnsConfStatus 
 *
 *[消息方向]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtGetCnsStateInd  )
 _body( TTPCurCnsConfStatus, 1 )
 _ev_end
 
 /***********************<<获取 cns 注册状态 >>************************	
 *[消息体]			 
 *  TTPGkRegistrarCfg 
 *
 *[消息方向]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtGetCnsRegStateInd  )
 _body( TTPCnsRegStatus, 1 )
 _ev_end
 

  /***********************<<网管服务器配置信息 >>************************	
 *[消消息体]			 
 *  TTPNMServerCfg
 *  u16 网管服务器索引
 *[消息方向]
 *    CNS => AGENT
 */
 _event(  ev_CnNMServerCfgInd )
 _body( TTPNMServerCfg, 1 )
 _ev_end

 ////////////////////网管升级cns消息//////////////////////
 
 /***********************<< 系统升级状态    >>********************	
  * [消消息体]
 * BOOL 上传成功 TRUE , 上传失败FALSE
 * [消息方向] 
 * cns -> cns
 */_event(ev_CnSysfileUploadStatus)
 _body(BOOL , 1)
 _ev_end

 /***********************<< 防火墙配置    >>********************	
  * [消消息体]
 * TEmbedFwNatProxy 
 * [消息方向] 
 *
 */_event(ev_CfgFireWallInd)
 _body(TEmbedFwNatProxy , 1)
 _ev_end
 
 

 //End to add

/***********************<< cnds链接上cnsubroutinemgr,然后cnsubroutinemgr通知cnservice   >>********************	
 * [消消息体]
 * NULL
 * [消息方向] 
 * cns -> cns
 */
 _event(  ev_TpCnDsConnSuccessCmd )
 _ev_end	

/***********************<< cns注册升级服务器的内部定时器 >>********************	
 * [消消息体]
 * NULL
 * [消息方向] 
 * cns -> cns
 */
 _event( ev_TpCnRegUpdateSer_Timer )
 _ev_end

 /***********************<< cns升级的内部定时器 >>********************	
 * [消消息体]
 * NULL
 * [消息方向] 
 * cns -> cns
 */
 _event( ev_TpCnsUpdate_Timer )
 _ev_end

 /***********************<< cns会场呼叫状态通知 >>********************	
 * [消消息体]
 * EmCALLSTATE 会场呼叫状态
 * [消息方向] 
 * cns -> cns
 */
 _event( ev_TpCnCallState_Nty )
 _body( EmCALLSTATE, 1 )
 _ev_end

  /***********************<< Guard获取cns系统状态 >>********************	
 *[消息体]			 
 *   无
 *[消息方向]
 *   cnGuard => cnGuard
 */
 _event( ev_SystemStatistic )
 _ev_end

 /***********************<< 统计通知 >>************************	
 *[消息体]			 
 *
 *[消息方向]
 *    Guard => AGENT
 */_event(  ev_AgtStatisticsInd  )
 _ev_end


  /***********************<< 调试小图像 >>************************	
 *[消息体]			 
 *
 *[消息方向]
 *    usr => cnservice
 */_event(  ev_CreateDsDebug_Cmd  )
 _body( u32, 1 )
 _body( u32, 1 )
 _body( u16, 1 )
 _body( u16, 1 )
 _body( u16, 1 )
 _body( BOOL, 1 )
 _ev_end

 /***********************<< 通知生产测试连接 >>************************	
 *[消息体]			 
 *
 *[消息方向]
 *    Terinferface => ProductTest
 */_event(  ev_TpCnProducetTestOnline_Nty  )
 _ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end(innercns)
};
#endif



#endif // _h_innereventregsrv_h__
