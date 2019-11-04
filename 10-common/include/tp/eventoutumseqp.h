#ifndef _h_eventoutumseqp_h__
#define _h_eventoutumseqp_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emouterumseqp
{
#endif

	_ev_segment( outerumseqp )

  /***********************<<  混音管理器向设备管理器进行注册 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] audiomix -> audiomixeqp	
 *
 */
 _event(  ev_AudioMixInitCfg_Req )
	_body( TModelProp, 1 )
 _ev_end

  /***********************<<  混音管理器初始化成功后更新设备管理器中自身的注册状态 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] audiomix -> audiomixeqp
 *
 */
 _event(  ev_AudioMixInitSuccess_Ind )
  _body( u16, 1 )
  _body( BOOL32, 1)
 _ev_end


   /***********************<<  Mpc向主控注册 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] Mpc -> Mpceqp	
 *
 */
 _event(  ev_MpcInitCfg_Req )
	_body( TModelProp, 1 )
	_body( TTPTime, 1 )	//配置时间的时间
	_body( TTPTime, 1 )	//系统当前时间
 _ev_end

 /***********************<<  Mpc注册成功 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] Mpceqp -> Mpc	
 *
 */
 _event(  ev_MpcInitCfg_ACK )
	_body( TModelProp, 1 )
 _ev_end


   /***********************<<  Mpc注册失败 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] Mpceqp -> Mpc	
 *
 */
 _event(  ev_MpcInitCfg_NACK )	
 _ev_end

   /***********************<<  Mpc主备 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] Mpceqp -> Mpc	
 *
 */
 _event(  ev_MpcIsMaster_Ntf )
	_body( BOOL32, 1 )		//是否主板
 _ev_end

    /***********************<<  设置Mpc时间 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向] Mpceqp -> Mpc	
 *
 */
 _event(  ev_MpcSetTime_Cmd )
	_body( TTPTime, 1 )		//配置时间
	_body( TTPTime, 1 )		//当前时间
 _ev_end

 /***********************<<  adapter注册 >>*********************/
_event(  ev_SipAdapterInitCfg_Req ) //adapter -> ums
_body(TModelProp, 1)
_body(EmTpConfProtocol, 1)
_ev_end

/***********************<<  adapter注册失败 >>*********************/
_event(  ev_SipAdapterInitCfg_NACK )
_ev_end

/***********************<<  adapter注册成功 >>*********************/
_event(  ev_SipAdapterInitCfg_ACK )
_body(TUmsStackCallCfg, 1)
_ev_end

/***********************<<  adapter启动成功 >>*********************/
_event(  ev_SipAdapterInitSuccess_Ind )
_body(u16, 1)//ums的设备索引
_ev_end
 

/***********************<<  转发注册 >>*********************/
_event(  ev_MediaTrans_Req ) //adapter -> ums
_body(TModelProp, 1)
_ev_end
_event(  ev_MediaTrans_NACK ) //adapter -> ums
_ev_end
_event(  ev_MediaTrans_ACK ) //adapter -> ums
_body(TUmsMediatransCfg, 1)
_ev_end
/***********************<<  启动成功 >>*********************/
_event(  ev_MediatransInitSuccess_Ind )
_body(u16, 1)//ums的设备索引
_ev_end




/***********************<<  Netbuf注册 >>*********************/
_event(  ev_Netbuf_Req ) //Netbuf -> ums
_body(TModelProp, 1)
_ev_end
_event(  ev_Netbuf_NACK ) //Netbuf -> ums
_ev_end
_event(  ev_Netbuf_ACK ) //Netbuf -> ums
_body(TUmsNetbufCfg, 1)
_ev_end
/***********************<<  启动成功 >>*********************/
_event(  ev_NetbufInitSuccess_Ind )
_body(u16, 1)//ums的设备索引
_ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end(outerumseqp)
};
#endif


#endif // _h_eventoutumseqp_h__
