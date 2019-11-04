#ifndef _h_eventoutcnremotemp_h__
#define _h_eventoutcnremotemp_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmUMSCNREMOREMPEVENT
{
#endif 
	
	_ev_segment( outercnremotemp  )
  /***********************<< 通知业务>>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppRmMgrAddr_Ind )  
  _body( BOOL32, 1 ) //TRUE: 码流发送 FALSE:接收地址
  _body( TRmMgrMtMPAddr, 4)
  _body( BOOL, 1 )
  _ev_end

  /***********************<< 通知业务>>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppFtpInfoOpreateCmd )  
  _body( u8, 1 ) //0:台标 1：横幅 2：快照
  _body( u8, 1 ) //pos
  _body( TFtpFileInfo, 1 )
  _ev_end

  /***********************<< 通知业务>>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppMsgRcvCheck_Timer )  
   _ev_end

    /***********************<< 通知业务>>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppMgrCodecLostPackInd )  
  _body( u32, 1 ) //丢包数
  _body( u32, 1 ) //总包数
   _ev_end  

   /***********************<< 通知业务>>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppMpRemoteStatus_Nty )  
  _body( BOOL32, 1 ) //是否所有外界编解码器都已经连接成功 
  _body( u8, 1 ) //屏索引
  _ev_end

    /***********************<<云化平台的服务器命令>>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppCloudPlatServerCfgCmd)  
  _body( TTPCloudPlatServerCfg, 1 )
  _ev_end

     /***********************<<云化平台的服务器配置命令回应>>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppCloudPlatServerCfgInd)  
  _body( TTPCloudPlatServerCfg, 1 )
  _body( BOOL, 1 ) //成功和失败
   _ev_end

     /***********************<<云化平台的服务器配置通知>>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppCloudPlatServerCfgNty)  
  _body( TTPCloudPlatServerCfg, 1 )
  _ev_end

  /***********************<< 音视频端口通知  >>********************	
  *[消息体]
  *u8 位置
  *EmTpCodecComponent 音视频类型
  *TTPCnMediaTransPort 音视频端口信息
  *[消息方向]	cns   -->   cnc
  */
  _event( ev_CnAVPortInfo_Nty )
  _body( u8, 1 )
  _body( EmTpCodecComponent, 1 )
  _body( TTPCnMediaTransPort, 1 )
  _ev_end

  /***********************<< 云化选看请求  >>********************	
  *[消息体]
  *u8 位置
  *BOOL 是否选看
  *EmTpCodecComponent 音视频类型
  *TTPCnMediaTransPort 对端端口信息
  *[消息方向]	cnc   -->   cns
  */
  _event( ev_CnCloudView_Cmd )
  _body( u8, 1 )
  _body( BOOL, 1 )
  _body( EmTpCodecComponent, 1 )
  _ev_end

  /***********************<< 云化选看通知  >>********************	
  *[消息体]
  *u8 位置
  *BOOL 是否选看
  *[消息方向]	cns   -->   cnc
  */
  _event( ev_CnCloudView_Nty )
  _body( u8, 1 )
  _body( BOOL, 1 )
  _ev_end

  /***********************<< 云化选看回应  >>********************	
  *[消息体]
  *u8 位置
  *BOOL 是否选看
  *[消息方向]	cns   -->   cnc
  */
  _event( ev_CnCloudView_Ind )
  _body( u8, 1 )
  _body( BOOL, 1 )
  _ev_end

  /***********************<< 是否起用双流屏，仅测试  >>********************	
  *[消息体]
  *BOOL 是否启用
  *[消息方向]
  */
  _event( ev_tppMgrSetDualScreenEnable)
  _body( BOOL, 1 )
  _ev_end


  /***********************<< 注册网管>>********************	
  *[消息体]
  * 
  *[消息方向]
  * 
  */
  _event(  ev_tppRegNms_Timer )  
   _ev_end

   /***********************<< 网管返回的消息通知>>********************	
  *[消息体]
  * 
  *[消息方向]
  * 
  */
  _event(  ev_tppNmsInd )  
  _body( u8, 1024 )
   _ev_end

   _event(  ev_tppUpdateRegNmsCmd )  
   _body( u8, 1 ) //0：无需重新注册，1:需要重新注册，
   _body( TTPCloudPlatServerCfg, 1 )
   _ev_end
   
    /***********************<< 视频源掉线通知通知 >>********************	
	 * [消消息体]
	 *
	 * [消息方向] 
	 * cnservice -> cnc
	 */
   _event(ev_TpSrcOffLine_Nty)
   _body( u8, 1 )
   _ev_end

     /***********************<< 建临时连接用的定时器 >>********************	
	 * [消消息体]
	 *
	 * [消息方向] 
	 * 
	 */
   _event(  ev_tppregtocn_timer )
   _ev_end

	/***********************<< 最后一个用户信息的通知  >>********************	
	*[消息方向]	CNS	-->  CNC
	*参数为BOOL，此消息直接用OSP发送，不经过XML编解码
	*/
	_event(  ev_CNSLastUser_Notify )
	_body(BOOL , 1)
	_ev_end	

#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnremotemp )
};
#endif
#endif 