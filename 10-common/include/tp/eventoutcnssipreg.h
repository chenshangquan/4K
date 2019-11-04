#ifndef _h_eventoutcnssipreg_h__
#define _h_eventoutcnssipreg_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSSIPREGEVENT
{
#endif 

  _ev_segment( outercnssipreg  )

	 //注册
/***********************<<注册网呈服务器定时器  >>************************
*[消息体]
*NULL
*[消息方向]
*  cns	   -> cns
*/
	 _event(  ev_tppRegisterRs_Timer )
	 _ev_end
  
/***********************<<注册网呈服务器请求  >>************************
*[消息体]
*TTPSipRegistrarCfg  SIP Register配置
*[消息方向]
*  cns	   -> cns，cns->cnc,cns->tool
*/
	 _event(  ev_tppRegisterRs_Req )
	 _body( TTPSipRegistrarCfg,1 )
	 _ev_end

/***********************<<注册网呈服务器请求的回应  >>************************
*[消息体]
*EmTpConfProtocol  会议协议
*u32句柄
*EmTPRegResult 注册结果
*[消息方向]
*  cns	   -> cncall
*/
	_event(  ev_tppRegisterRs_Rsp )
	_body( EmTpConfProtocol,1 )
	_body( u32,1 )						//句柄
	_body( EmTPRegResult,1 )			//注册结果
	_ev_end
	
/***********************<<取消注册网呈服务器请求  >>************************
*[消息体]
*NULL
*[消息方向]
*  cns	   -> cns
*/
	_event(  ev_tppUnRegisterRs_Req )
	 _ev_end

/***********************<<取消注册网呈服务器请求的回应  >>************************
*[消息体]
*EmTpConfProtocol  会议协议
*EmTPRegResult 注册网呈服务器结果
*EmTpCnsRegUms 注册ums结果
*s32
*TTPRegName 注册网呈服务器名称
*u32        取消注册回调反馈句柄
*[消息方向]
*  cns	   -> cncall
*/
	_event(  ev_tppUnRegisterRs_Rsp )
	_body( EmTpConfProtocol,1 )
	_body( EmTPRegResult,1 )
	_body( EmTpCnsRegUms,1 )
	_body( s32, 1 )
	_body( TTPRegName,2 )
	_body( u32, 1 )
	_ev_end

	/***********************<< 通知注册结果回应 >>********************** 
*[消息体]
+BOO	TRUE :成功  FALSE:失败
+s8[]		会场名
*[消息方向]
*  cns	  -> cnc
*/
_event( ev_tpRegisterResult_Nty )
_body( BOOL , 1)
_body( s8, TP_MAX_NAME_LEN+1)
_ev_end



/***********************<< 通知注册结果回应--失败 >>********************** 
*[消息体]
+s8[]		会场名
*EmTpCnsRegUms 注册UMS结果
*TTPRegNameRepeatInfo 注册别名重复信息
*[消息方向]
*  cns	  -> cnc
*/
_event( ev_tpRegisterResultFail_Nty )
//_body( BOOL , 1)
_body( s8, TP_MAX_NAME_LEN+1)
_body( EmTpCnsRegUms, 1)
//_body( s32, 1 )
//_body( TTPRegName,2 )
_body(TTPRegNameRepeatInfo, 1)
_ev_end
  
/***********************<< 获取全域内UMS和CNS的全部注册信息 >>********************** 
*[消息体]
*EmGetRegInfoType 获取注册信息
*[消息方向]
*  cnc	  -> cns
*/
_event( ev_tppGetRegInfo_Req )
_body( EmGetRegInfoType, 1 )
_ev_end

/***********************<< 获取全域内UMS和CNS的全部注册信息回复 >>********************** 
*[消息体]
*TTPSipRegPackInfo 注册网呈服务器信息包
*EmGetRegInfoType 获取注册信息
*TTPSipRegInfo 从SIP注册服务器得到全域信息
*[消息方向]
* cncall->cns, cns	  -> cnc
*/
_event( ev_tppGetRegInfo_Rsp )
_body( TTPSipRegPackInfo, 1 )
_body( EmGetRegInfoType, 1 )
_body( TTPSipRegInfo, 1 )
_ev_end
/***********************<< 通知cnc全域内UMS和CNS的全部注册信息 >>********************** 
*[消息体]
*TTPSipRegInfo 从SIP注册服务器得到全域信息
*[消息方向]
*  cns	  -> cnc
*/
_event( ev_tppGetRegInfo_Nty )
_body( TTPSipRegInfo, 1 )
_ev_end

/***********************<< gk设置 >>********************** 
*[消息体]
* TTPGKCfg 注册GK配置
*[消息方向]
*  cns	 <- cnc，cns <- tool
*/
_event( ev_CnsGKReg_Cmd )
_body(TTPGKCfg, 1)
_ev_end

/***********************<< gk设置回应 >>********************** 
*[消息体]
*TTPGKCfg 注册GK配置
*[消息方向]
*  cns	  -> cnc，cns->tool
*/
_event( ev_CnsGKReg_Nty )
//_body(BOOL, 1 )
_body(TTPGKCfg, 1)
_ev_end

/***********************<< gk注册结果 >>********************** 
*[消息体]
* TUCSipRegResult UMS,CNS接收协议栈注册结果信息
*[消息方向]
*  cns	  -> cnc，cns->tool
*/
_event( ev_CnsGKReg_Ret )
_body(TUCSipRegResult, 1)
_ev_end

/***********************<< 全局地址簿解锁 >>********************** 
*[消息体]
*NULL
*[消息方向]
*cns -> cns
*/
_event( ev_UnlockRegList_Timer )
_ev_end

/***********************<<  定时自动呼叫 >>********************** 
*[消息体]
*NULL
*[消息方向]
*cns -> cns
*/
_event( ev_TppAutoMakeCall_Cmd_timer )
_ev_end

/***********************<<  取消GK注册请求 >>********************** 
*[消息体]
*NULL
*[消息方向]
*cns -> cns
*/
_event( ev_tppUnGkRegisterRs_Req )
_ev_end

/***********************<<  GK注册定时器 >>********************** 
*[消息体]
*NULL
*[消息方向]
*cns -> cns
*/
_event( ev_tppGkRegisterRs_Timer )
_ev_end

/***********************<<  注册句柄 >>********************** 
*[消息体]
*EmTpConfProtocol 会议呼叫协议
*u32 注册句柄
*[消息方向]
*cncall -> cns
*/
_event( ev_tppRegisterHandle_Nty )
_body(EmTpConfProtocol, 1)
_body( u32, 1)
_ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnssipreg )
};
#endif
#endif //TPP_EVENT_H
