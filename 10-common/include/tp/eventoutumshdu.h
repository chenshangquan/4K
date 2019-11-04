#ifndef _eventoutumshdu_h_
#define _eventoutumshdu_h_

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsHduEvent
{
#endif

	_ev_segment( outerumshdu )

/***********************<<  hdu注册 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	Hduserver	--> UI
 *
 */_event(  ev_SysHduEpReg )
	_body( TTPHduRegInfo,		1)
   _ev_end

   /***********************<<  hdu掉线 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	hduserver	--> UI and ums
 *
 */_event(  ev_SysHduEpDrop )
   _body( u32,		1)//channelhandle
   _ev_end
   /***********************<<  请求播放  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	UI	--> hduserver
 *
 */_event(  ev_SysHduPlayReq )
	_body( TTPHduPlayReq,		1) 
   _ev_end

      /***********************<<  请求播放回应  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	hduserver	--> UI
 *
 */_event(  ev_SysHduPlayAck )
	_body( TTPHduPlayReq,		1)//channelhandle
   _ev_end


         /***********************<<  请求播放回应  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	hduserver	--> UI
 *
 */_event(  ev_SysHduPlayNAck )
	_body( TTPHduPlayReq,      1)//channelhandle
	_body( EmTpHduPlayNackReason,     1)
	_ev_end


/***********************<<  stopplay  >>********************	
 *[消息体]			 删除电视墙的监控
 *   NULL
 *[消息方向]	UI	--> hduserver
 *
 */_event(  ev_SysHduStopPlay )
	_body( TTPHduPlayReq,				  1)
	_ev_end

			         /***********************<<  stopplayack  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	hduserver  -->  UI	
 *
 */_event(  ev_SysHduStopPlayAck )
	_body( TTPHduPlayReq,				  1)
	_ev_end

				         /***********************<<  stopplaynack  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	hduserver  -->  UI	
 *
 */_event(  ev_SysHduStopPlayNAck )
	_body( TTPHduPlayReq,				  1)
	_ev_end

/************************<<通知界面会场是否有码流>>*************************
*[消息体]			 
*   NULL
*[消息方向]	hduserver  -->  UI	
*
*/_event(  ev_SysHduCallIsValid )
  _body( TTPHduPlayReq,      1)
  _body( BOOL,				  1)
  _ev_end






#ifndef _MakeTpEventDescription_
   _ev_segment_end(outerumshdu)
};
#endif





#endif //_eventoutumshdu_h_