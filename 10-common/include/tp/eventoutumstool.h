#ifndef  _h_eventoutumstool_h__ 
#define  _h_eventoutumstool_h__

#include "tpeventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmEventToolMsg
{
#endif
	_ev_segment( outerumstool )

/***********************<<通知软硬件版本信息>>********************	
 *[消息方向]	ums	-->  tool
 *
 */
_event(  ev_verInfo_Nty )
	_body(TUmsVersion,	1)	//版本信息
_ev_end

/***********************<<获取系统信息包括CPU和内存>>********************	
 *[消息方向]	tool	-->  ums
 *
 */
_event(  ev_sysInfo_req )
_ev_end

/***********************<<CPU，内存系统信息>>********************	
 *[消息方向]	ums	-->  tool
 *
 */
_event(  ev_sysInfo_Nty )
	_body(TToolSysInfo,	1)//版本信息
_ev_end

/***********************<<请求开会的会议数量>>********************	
 *[消息方向]	tool	-->  ums
 *
 */
_event(  ev_confCount_req )
_ev_end

/***********************<<通知开会的数量>>********************	
 *[消息方向]	ums	-->  tool
 *
 */
_event(  ev_confCount_Nty )
	_body(u32, 1 )	//开会数量
_ev_end

/***********************<<重启UMS>>********************	
 *[消息方向]	tool	-->  ums
 *
 */
_event(  ev_rebootUms_cmd )
_ev_end

/***********************<<请求授权使用数量>>********************	
 *[消息方向]	tool	-->  ums
 *
 */
_event(  ev_authCount_req )
_ev_end

/***********************<<授权使用信息>>********************	
 *[消息方向]	ums	-->  tool
 *
 */
_event(  ev_authCount_Nty )
	_body(u32, 1)	//总量
	_body(u32, 1)	//已用数量
_ev_end

/***********************<<电视墙使用情况>>********************	
 *[消息方向]	tool	-->  ums
 *
 */
_event(  ev_hduCount_req )
_ev_end

/***********************<<电视墙使用情况应答>>********************	
 *[消息方向]	ums	-->  tool
 *
 */
_event(  ev_hduCount_Nty )
	_body(TTPBrdUsedInfo,	1)
_ev_end

/***********************<<授权文件导出>>********************	
 *[消息方向]	tool	-->  ums
 *
 */
_event(  ev_licenseOutput_req )
_ev_end

/***********************<<授权文件导出应答>>********************	
 *[消息方向]	ums	-->  tool
 *
 */
_event(  ev_licenseOutput_Ind )
_body(BOOL32, 1)	//是否成功
_body(s8, 255)	//绝对路径+文件名
_ev_end

#ifndef _MakeTpEventDescription_
	_ev_segment_end( outerumstool )
};
#endif


#endif