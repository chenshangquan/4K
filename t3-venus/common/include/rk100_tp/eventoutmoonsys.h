#ifndef _h_eventoutmoonsys_h__
#define _h_eventoutmoonsys_h__

#include "mooneventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSSYSEVENT
{
#endif 

  _ev_segment( outermoonsys  )

/***********************<< 设置moon时间 >>********************** 
*[消息体]
+TTPTime		
*[消息方向]
*  moon	  <- camCP
*/
_event( ev_TpMoonSetSysTime_Cmd )
_body( TTPTime, 1 )
_ev_end

/***********************<< 查询moon时间 >>********************** 
*[消息体]
*NULL
*[消息方向]
*  moon	  <- camCP
*/
_event( ev_TpMoonGetSysTime_Req)
_ev_end


/***********************<< 查询moon时间响应 >>********************** 
*[消息体]
+TTPTime
*[消息方向]
*  moon  -> camCP
*/
_event( ev_TpMoonGetSysTime_Rsp)
_body( TTPTime, 1 )
_ev_end

/***********************<< 设置网络信息 >>********************** 
*[消息体]
+TTPEthnetInfo		moon网络配置信息
*[消息方向]
*  camCP  -> moon
*/
_event( ev_TpMoonCfgEthnet_Cmd )
_body(TTPEthnetInfo, 1 )
_ev_end

/***********************<< 通知网络回应 >>********************** 
*[消息体]
+TTPEthnetInfo		moon网络配置信息
*[消息方向]
*  moon	  -> camCP
*/
_event(  ev_TpMoonCfgEthnet_Ind )
_body(TTPEthnetInfo, 1 )
_ev_end

  /***********************<<  moon 升级 >>********************	
  *[消息体]
  *[消息方向]
  *  camCP -> moon
  */_event(   ev_TpMoonUpgrade_Cmd )
  _body(s8,  TP_MAX_FILENAME_LEN + 1)
  _ev_end

  /***********************<<  Moon 升级响应 >>********************	
  *[消息体]
  *[消息方向]
  *  moon -> camCP
  */_event(   ev_TpMoonUpgrade_Ind )
  _body(BOOL,  1)
  _ev_end

  /***********************<< 重启Moon命令  >>********************	
  *[消息体]
  *NULL
  *[消息方向]	  camCP	-->  Moon
  *
  */
  _event(  ev_tpMoonReboot_Cmd )
_ev_end

/***********************<<  Moon 升级响应 >>********************	
  *[消息体]
  *[消息方向]
  *  moon -> camCP
  */_event(   ev_TpMoonUpgradeCleanEnv_Ind )
  _ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outermoonsys )
};
#endif
#endif //TPP_EVENT_H
