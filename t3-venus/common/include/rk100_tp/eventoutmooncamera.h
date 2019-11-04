#ifndef _h_eventoutmooncamera_h__
#define _h_eventoutmooncamera_h__

#include "mooneventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSCAMERAEVENT
{
#endif 
	
	_ev_segment( outermooncamera  )


  /**********************<< 摄像机上电通知 >>**********************
  *[消息体]
  *
  *    + BOOL    =TRUE tptools抢登时发送正在上电的通知 FALSE 正常情况
  *
  *[消息方向]
  *
  *   cnDevice => cnDevice
  */_event( ev_Cn_CameraPowerOnNty )
	_body(  BOOL,      1           )
    _ev_end

/***********************<<中间屏延时操作>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon
 */
_event(  ev_TpSetMidDelay_Cmd )
_body( u32, 1)//开关
_ev_end 
/***********************<<sony机芯降噪设置>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cam <- moon
 */
_event(  ev_TpCamNoiseLevel_Cmd )
_body( EmTPCamNoiseLevel, 1)
_body( u8, 1)
_ev_end 

#ifndef _MakeTpEventDescription_
		_ev_segment_end( outermooncamera )
};
#endif
#endif 