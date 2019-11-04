#ifndef _h_eventoutumsbrdvmp_h_
#define _h_eventoutumsbrdvmp_h_

//#include "tpeventcomm.h"
#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emtpouterumsbrdvmp
{
#endif

	_ev_segment( outerumsbrdvmp )
		
/***********************<<   >>********************	
 *[消息方向]	UMC	-->  UMS
 *  UMC 请求 占用合成
 */
_event(  ev_UMC_UMS_RervesBrdVmp_Req )
_body(TRersvesEqpReq, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	CNC	-->  UMS
 *  CNC 请求 占用合成
 */
_event(  ev_CNC_UMS_RervesBrdVmp_Req )
_body(TUmsHandle, 1)
_body(TRersvesEqpReq, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  UMC
 *  UMS给umc  占用合成 的回应
 */
_event(  ev_UMS_UMC_RervesBrdVmp_Ind )
_body(TRersvesEqpRsp, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CNC
 *  UMS给cnc 占用合成 的回应
 */
_event(  ev_UMS_CNC_RervesBrdVmp_Ind )
_body(TUmsHandle, 1)
_body(TRersvesEqpRsp, 1)
_ev_end


/***********************<<   >>********************	
 *[消息方向]	UMC	-->  UMS
 *  UMC 请求 配置合成
 */
_event(  ev_UMC_UMS_SetBrdVmp_Req )
_body(TSetVmpInfoReq, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	CNC	-->  UMS
 *  CNC 请求 配置合成
 */
_event(  ev_CNC_UMS_SetBrdVmp_Req )
_body(TUmsHandle, 1)
_body(TSetVmpInfoReq, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  UMC
 *  UMS给umc  配置合成 的回应
 */
_event(  ev_UMS_UMC_SetBrdVmp_Ind )
_body(TSetVmpInfoRsp, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CNC
 *  UMS给cnc 配置合成 的回应
 */
_event(  ev_UMS_CNC_SetBrdVmp_Ind )
_body(TUmsHandle, 1)
_body(TSetVmpInfoRsp, 1)
_ev_end


/***********************<<   >>********************	
 *[消息方向]	UMC	-->  UMS
 *  UMC 请求 广播合成
 */
_event(  ev_UMC_UMS_BrdVmp_Req )
_body(TBrdVmpReq, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	CNC	-->  UMS
 *  CNC 请求 广播合成
 */
_event(  ev_CNC_UMS_BrdVmp_Req )
_body(TUmsHandle, 1)
_body(TBrdVmpReq, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  UMC
 *  UMS给umc  广播合成 的回应
 */
_event(  ev_UMS_UMC_BrdVmp_Ind )
_body(TBrdVmpRsp, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CNC
 *  UMS给cnc 广播合成 的回应
 */
_event(  ev_UMS_CNC_BrdVmp_Ind )
_body(TUmsHandle, 1)
_body(TBrdVmpRsp, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  UMC
 *  通知UMC的合成器状态
 */
_event(  ev_UMS_UMC_BrdVmp_Ntfy )
_body(TBrdVmpResArray, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CNC
 *  通知CNC的合成器状态
 */
_event(  ev_UMS_CNC_BrdVmp_Ntfy )
_body(TUmsHandle, 1)
_body(TBrdVmpResArray, 1)
_ev_end

/***********************<<   >>********************	

 *[消息方向]	UMS	-->  UMS
 *  通知下UMS，合成广播、发言人合成等状态
 */
_event(  ev_UMS_UMS_VmpCasecade_Ntfy )
_body(TUmsHandle, 1)
_body(TVmpCasecadeNtfy, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMC	-->  UMS
 *  UMC 请求 保存合成预案
 */
_event(  ev_UMC_UMS_SaveVmpCfg_Cmd )
_body(TTpVmpMemberCfg, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	CNC	-->  UMS
 *  CNC 请求 保存合成预案
 */
_event(  ev_CNC_UMS_SaveVmpCfg_Cmd )
_body(TUmsHandle, 1)
_body(TTpVmpMemberCfg, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  UMC
 *  UMS给umc  保存合成预案 的回应
 */
_event(  ev_UMS_UMC_SaveVmpCfg_Ind )
_body(TTpVmpMemberCfgInd, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CNC
 *  UMS给cnc 保存合成预案 的回应
 */
_event(  ev_UMS_CNC_SaveVmpCfg_Ind )
_body(TUmsHandle, 1)
_body(TTpVmpMemberCfgInd, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  call
 *  UMS给cnc 保存合成预案 的回应
 */
_event(  ev_Save_VmpCfg_Ack )
_body(u16, 1)         //合成预案数组下标
_body(BOOL32, 1)	  //保存结果
_ev_end


#ifndef _MakeTpEventDescription_
_ev_segment_end(outerumsbrdvmp)
};
#endif




#endif // _h_eventoutumsbrdvmp_h_
