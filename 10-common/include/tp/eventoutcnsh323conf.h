#ifndef _h_eventoutcnsh323conf_h__
#define _h_eventoutcnsh323conf_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSH323CONFEVENT
{
#endif 

  _ev_segment( outercnsh323conf  )


/***********************<< 开始多点会议指示 >>********************** 
*[消息体]

*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleMultipleConference )
_ev_end
	  
/***********************<< 取消多点会议指示 >>********************** 
*[消息体]

*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleCancelMultipleConference )
_ev_end

/***********************<< 分配终端编号 >>********************** 
*[消息体]
TTPMDLTERLABEL
*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleTerminalNumberAssign )
_body(TTPTerLabel, 1)
_ev_end

/***********************<< 被别人看，发言人 >>********************** 
*[消息体]

*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleSeenByAll )
_ev_end

/***********************<< 取消被别人看 >>********************** 
*[消息体]

*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleCancelSeenByAll )
_ev_end

/***********************<< 请求列表 >>********************** 
*[消息体]

*[消息方向]
*  cncall	  <- cns
*/
_event(  ev_CnModuleTerminalListRequest )

_ev_end

/***********************<< 请求列表 >>********************** 
*[消息体]

*[消息方向]
*  cncall	  <- cns
*/
_event(  ev_CnModuleTerminalIDListRequest )

_ev_end



/***********************<< 加入会议 >>********************** 
*[消息体]
TTPMDLTERLABEL
*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleTerminalJoinConf )
_body( TCnsInfo, 1 )
_ev_end

/***********************<< 离开会议 >>********************** 
*[消息体]
TTPMDLTERLABEL
*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleterminalLeftConf )
_body( TCnsInfo, 1 )
_ev_end

/***********************<< cnc远遥切源>>****************************
*					
*[消息方向]
*  CNC	 ->  CNS
*/

_event(  ev_Cn_FeccChangeSrc_Cmd )
_body( TConfEpID, 1 )
_body( u8, 1 )
_ev_end

/***************<< cnc发送远遥摄像机PT指令给cns>>*******************
*					
*[消息方向]
*  CNC	  ->  CNS    CNS   ->   CNCALL
*/

_event(  ev_Cn_FeccCamPT_Cmd )
_body( TConfEpID, 1 )
_body( EmDirection, 1 )
_body( EmCnAction, 1 )
_ev_end
/******************<< cnc发送远遥自动聚焦指令给cns>>*******************
*					
*[消息方向]
*  CNC	  ->  CNS    CNS   ->   CNCALL
*/

_event(  ev_Cn_FeccCamAutoFocus_Cmd )
_body( TConfEpID, 1 )
_ev_end
/******************<< cnc发送远遥聚焦指令给cns>>***********************
*					
*[消息方向]
*  CNC	  ->  CNS    CNS   ->   CNCALL
*/

_event(  ev_Cn_FeccCamFocus_Cmd )
_body( TConfEpID, 1 )
_body( EmFocus, 1 )
_body( EmCnAction, 1 )
_ev_end
/******************<< cnc发送远遥Zoom调节指令给cns>>***********************
*					
*[消息方向]
*  CNC	  ->  CNS    CNS   ->   CNCALL
*/

_event(  ev_Cn_FeccCamZoom_Cmd )
_body( TConfEpID, 1 )
_body( EmZoom, 1 )
_body( EmCnAction, 1 )
_ev_end
/******************<< cnc发送远遥亮度调节指令给cns>>***********************
*					
*[消息方向]
*  CNC	  ->  CNS    CNS   ->   CNCALL
*/

_event(  ev_Cn_FeccCamBackLight_Cmd )
_body( TConfEpID, 1 )
_body( EmPanCamBright, 1 )
_body( EmCnAction, 1 )
_ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnsh323conf )
};
#endif
#endif //TPP_EVENT_H
