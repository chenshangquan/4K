#ifndef _h_eventoutumscommonbrd_h__
#define _h_eventoutumscommonbrd_h__

#include "tpeventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emouterumscommonbrd
{
#endif
	_ev_segment( outerumscommonbrd )	
	
	/***********************<<单板注册请求>>********************	
	*[消息方向]	umsboard  -->  EqpApp
	*
	*/
	_event(  ev_TPBrdReg_Req )
	_body(TTPBrdRegInfo, 1)
	_ev_end
	
	/***********************<<单板注册Ack>>********************	
	*[消息方向]	EqpApp  -->  umsboard
	*
	*/
	_event(  ev_TPBrdReg_Ack )
	_ev_end

	/***********************<<单板注册Nack>>********************	
	*[消息方向]	EqpApp  -->  umsboard
	*
	*/
	_event(  ev_TPBrdReg_NAck )
	_ev_end
	
	/***********************<<单板获取配置请求>>********************	
	*[消息方向]	umsboard   -->  EqpApp
	*
	*/
	_event(  ev_TPBrdGetCfg_Req )
	_body(TTPBrdPos, 1)
	_ev_end
	
	/***********************<<单板获取配置Ack>>********************	
	*[消息方向]	EqpApp    -->  umsboard
	*
	*/
	_event(  ev_TPMcuBrdGetCfg_Ack )
	_body(u8, 256)
	_ev_end
	
	/***********************<<单板获取配置Nack>>********************	
	*[消息方向]	EqpApp    -->  umsboard
	*
	*/
	_event(  ev_TPBrdGetCfg_NAck )// EqpApp -> 板子
	_ev_end
	
	/***********************<<单板获取配置Nack>>********************	
	*[消息方向]	umsboard     -->  EqpApp
	*
	*/
	_event(  ev_TPBrdConnect_Timer )
	_ev_end

	/***********************<<单板重启Cmd>>********************	
	*[消息方向]	EqpApp     -->  umsboard
	*
	*/
	_event(  ev_TPBrdReboot_Cmd )
	_ev_end
	
	/***********************<<通知单板同步主控时间>>********************	
	*[消息方向]	EqpApp     -->  umsboard
	*
	*/
	_event(  ev_TPBrdSetSysTime_Cmd )
	_body( TTPTime, 1 )
	_ev_end

	/***********************<<单板获取版本请求>>********************	
	*[消息方向]	EqpApp      -->  umsboard
	*
	*/
	_event(  ev_TPBrdHDVersion_Req )
	_ev_end

	/***********************<<单板获取版本Ack>>********************	
	*[消息方向]	umsboard     -->  EqpApp
	*
	*/
	_event(  ev_TPBrdHDVersion_Ack )
	_body( TBrdVersion , 1)
	_ev_end

	/***********************<<单板升级请求>>********************	
	*[消息方向]	EqpApp      -->  umsboard
	*
	*/
	_event(  ev_TPBrdSoftWareUpdate_Req )
	_body( TBrdUpInfo, 1 )
	_ev_end

	/***********************<<单板升级结果响应>>********************	
	*[消息方向]	umsboard      -->  EqpApp
	*
	*/
	_event(  ev_TPBrdSoftWareUpdate_Ack )
	_body( BOOL32, 1 )
	_ev_end
	
#ifndef _MakeTpEventDescription_
	_ev_segment_end( outerumscommonbrd )
};
#endif

#endif