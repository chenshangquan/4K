#ifndef _h_eventoutumscfg_h__
#define _h_eventoutumscfg_h__

//#include "tpeventcomm.h"
#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emtpouterumscfg
{
#endif
	
	_ev_segment( outerumscfg )
		
/***********************<<   >>********************	
 *[消息方向]	CMS	-->  UMS
 *设置UMSIP
 */
_event(  ev_UmsIPCfg )
_body(TTPEthnetInfo, 1)
_ev_end


_event(  ev_UmsIPCfg_Ind )
_body(TTPEthnetInfo, 1)
_ev_end



/***********************<< 设置时间 >>********************** 
*[消息体]
+TTPTime		
*[消息方向]
*  ums	  <- umc
*/
_event( ev_UmsSetSysTime_Cmd )
_body( TTPTime, 1 )
_ev_end

/***********************<< 查询时间 >>********************** 
*[消息体]
+TTPTime
*[消息方向]
*  ums	  <- umc
*/
_event( ev_UmsGetSysTime_Req)
_ev_end


/***********************<< 查询时间响应 >>********************** 
*[消息体]
+TTPTime
*[消息方向]
*  ums	  -> umc
*/
_event( ev_UmsGetSysTime_Rsp)
_body( TTPTime, 1 )
_ev_end


/***********************<<  添加网管服务器  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	tool  -->  ums	
 *
 */
 _event(  ev_NMServerAdd_req )
	_body(TTPNMServerCfg, 1)
_ev_end

/***********************<<  添加网管服务器应答  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	ums  -->  umc	
 *
 */
 _event(  ev_NMServerAdd_rsp )
	_body(EmModifyNMServerRet, 1)
	_body(TTPNMServerCfg, 1)
_ev_end

/***********************<<  修改网管服务器  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	tool  -->  ums	
 *
 */
 _event(  ev_NMServerMdy_req )
	_body(TTPNMServerCfg, 1)
_ev_end

/***********************<<  修改网管服务器应答  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	ums  -->  umc	
 *
 */
 _event(  ev_NMServerMdy_rsp )
	_body(EmModifyNMServerRet, 1)
	_body(TTPNMServerCfg, 1)
_ev_end

/***********************<<  删除网管服务器  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	tool  -->  ums	
 *
 */
 _event(  ev_NMServerDel_req )
	_body(TTPNMServerCfg, 1)
_ev_end

/***********************<<  删除网管服务器应答  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	ums  -->  umc	
 *
 */
 _event(  ev_NMServerDel_rsp )
	_body(EmModifyNMServerRet, 1)
	_body(TTPNMServerCfg, 1)
_ev_end


/***********************<<  网管服务器列表  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	tool  -->  ums	
 *
 */
 _event(  ev_NMServer_nty )
	_body(u16,	1)
	_body(TTPNMServerCfg, TP_MAX_NMSERVER)
_ev_end

/***********************<<  添加录像机  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	tool  -->  ums	
 *
 */
 _event(  ev_VcrAdd_req )
	_body(TVcrCfg, 1)
_ev_end

/***********************<<  添加录像机应答  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	ums  -->  umc	
 *
 */
 _event(  ev_VcrAdd_rsp )
	_body(EmModifyVcrRet, 1)
	_body(TVcrCfg, 1)
_ev_end

/***********************<<  修改录像机  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	tool  -->  ums	
 *
 */
 _event(  ev_VcrMdy_req )
	_body(TVcrCfg,	1)	//修改前信息
	_body(TVcrCfg,	1)	//修改后信息
_ev_end

/***********************<<  修改录像机应答  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	ums  -->  umc	
 *
 */
 _event(  ev_VcrMdy_rsp )
	_body(EmModifyVcrRet, 1)
	_body(TVcrCfg, 1)
_ev_end

/***********************<<  删除录像机  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	tool  -->  ums	
 *
 */
 _event(  ev_VcrDel_req )
	_body(TVcrCfg, 1)
_ev_end

/***********************<<  删除录像机应答  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	ums  -->  umc	
 *
 */
 _event(  ev_VcrDel_rsp )
	_body(EmModifyVcrRet, 1)
	_body(TVcrCfg, 1)
_ev_end


/***********************<<  录像机列表  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	tool  -->  ums	
 *
 */
 _event(  ev_Vcr_nty )
	_body(u16, 1)
	_body(TVcrCfg, TP_MAX_VCR)
_ev_end



#ifndef _MakeTpEventDescription_
_ev_segment_end(outerumscfg)
};
#endif




#endif // _h_eventoutumscfg_h__
