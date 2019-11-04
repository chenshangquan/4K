#ifndef _h_eventoutupdateservice_h__
#define _h_eventoutupdateservice_h__


#include "tpserviceeventcommon.h"

#ifndef _MakeTpEventDescription_
enum Emtpouterupdateservice
{
#endif
	_ev_segment( tpupdateservice )

	/***********************<<远端向升级服务器发出登录请求 >>********************** 
	*[消息体]
	*	TTPLocalDevVerInfo 远端本地版本信息
	*[消息方向]
	*  远端 -> updateserver
	*/
	_event( ev_CnLogin_UpdateSer_Req )
		_body( TTPLocalDevVerInfo, 1 )
	_ev_end

	/***********************<<远端收到升级服务器请求登录的回复消息 >>********************** 
	*[消息体]
	*EmTPCnLoginUpdateRet 登录是否成功
	*[消息方向]
	*  远端 <- updateserver
	*/
	_event( ev_CnLogin_UpdateSer_Rsp )
	_body(EmTPCnLoginUpdateRet, 1)
	_ev_end

	/***********************<<远端主动发出升级请求 >>********************** 
	*[消息体]
	* EmTPUpdateSysFileType  升级设备类型
	*TTPLocalDevVerInfo      远端版本信息
	*[消息方向]
	*  远端 -> updateserver
	*/
	_event( ev_UpdateSystem_Req )
		_body(TTPLocalDevVerInfo, 1)
	_ev_end

	/***********************<<远端收到升级服务器发送的升级回应消息 >>********************** 
	*[消息体]
	*TTPDevVerInfo       远端 版本信息
	*[消息方向]
	*   远端 <- updateserver
	*/
	_event( ev_UpdateSystem_Rsp )
	_body(TTPDevVerInfo ,1)
	_ev_end

	/***********************<<远端收到升级服务器发出的通知升级消息 >>********************** 
	*[消息体]
	*TTPDevVerInfo  远端 版本信息
	*[消息方向]
	*   远端 <- updateserver
	*/
	_event( ev_UpdateSystem_Nty )
		_body(TTPDevVerInfo ,1)
	_ev_end

#ifndef _MakeTpEventDescription_
_ev_segment_end(tpupdateservice)
};
#endif


#endif // _h_eventoutupdateservice_h__
