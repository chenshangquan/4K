#ifndef _eventoutumshdu2_h__
#define _eventoutumshdu2_h__
#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emouterumshdu2
{
#endif
	
	_ev_segment( tpumswithumshdu2 )
	
	/***********************<<电视墙信息>>********************	
 *[消息方向]	ums	-->  tool
 *
 */
_event(  ev_hduInfo_Nty )
	_body(THduCfg, 1)	
_ev_end

	/***********************<<升级电视墙单板>>********************	
 *[消息方向]	ums	-->  tool
 *
 */
_event(  ev_hduUpdate_req )
	_body(TTPBrdUpGrade, 1)	
_ev_end

	/***********************<<升级电视墙单板结果>>********************	
 *[消息方向]	ums	-->  tool
 *
 */
_event(  ev_hduUpdate_rsp )
	_body(TTPBrdUpGrade, 1)	
	_body(EmUpdateHduRet, 1)
_ev_end

/***********************<<添加电视墙配置>>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduBrdAdd_req )
	_body(TTPBrdPos, 1)	
_ev_end

/***********************<<添加电视墙配置>>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduBrdAdd_rsp )
	_body(EmModifyHduRet, 1)
	_body(TTPBrdPos, 1)	
_ev_end


/***********************<<修改电视墙配置>>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduBrdModify_req )
	_body(TTPBrdPos, 1)	
_ev_end

/***********************<<修改电视墙配置应答>>********************	
 *[消息方向]	ums -->  tool
 *
 */
_event(  ev_hduBrdModify_rsp )
	_body(EmModifyHduRet, 1)	//原因 
	_body(TTPBrdPos, 1)			//修改信息
_ev_end

/***********************<<添加通道>>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduChanAdd_req )
	_body(THduInfo, 1)	
_ev_end


/***********************<<添加通道参数应答>>********************	
 *[消息方向]	ums -->  tool
 *
 */
_event(  ev_hduChanAdd_rsp )
	_body(EmModifyHduRet, 1)	//原因 
	_body(THduInfo, 1)	
_ev_end

/***********************<<修改通道参数>>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduChanModify_req )
	_body(THduInfo, 1)	
_ev_end

/***********************<<修改通道参数应答>>********************	
 *[消息方向]	ums -->  tool
 *
 */
_event(  ev_hduChanModify_rsp )
	_body(EmModifyHduRet, 1)	//原因 
	_body(THduInfo, 1)	
_ev_end

/***********************<<删除电视墙通道配置>>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduChanDel_req )
	_body(TTPBrdPos, 1)	
_ev_end


/***********************<<删除电视墙通道配置>>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduChanDel_rsp )
	_body(EmModifyHduRet, 1)	//原因 
	_body(TTPBrdPos, 1)	
_ev_end


/***********************<<删除电视墙>>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduDel_req )
	_body(TTPBrdPos, 1)	
_ev_end

/***********************<<删除电视墙配置应答>>********************	
 *[消息方向]	ums -->  tool
 *
 */
_event(  ev_hduDel_rsp )
	_body(EmModifyHduRet, 1)	//操作结果
	_body(TTPBrdPos, 1)	
_ev_end

/***********************<<重启电视墙>>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduReboot_req )
	_body(TTPBrdPos, 1)	
_ev_end

/***********************<<重启电视墙应答>>********************	
 *[消息方向]	ums -->  tool
 *
 */
_event(  ev_hduReboot_rsp )
	_body(EmModifyHduRet, 1)
	_body(TTPBrdPos, 1)	
_ev_end



/*				电视墙风格消息                               */
/***********************<<通知电视墙风格>>********************	
 *[消息方向]	ums -->  tool/
 *
 */
_event(  ev_hduStyle_Nty )
	_body(THduStyleData,	1)
_ev_end

/***********************<<通知电视墙风格>>********************	
 *[消息方向]	ums -->  umc
 *
 */
_event(  ev_hduPlan_Nty )
	_body(THduPlanData,	1)
_ev_end

/***********************<< 添加电视墙风格 >>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduStyle_Add )
	_body(THduStyleData,	1)
_ev_end

/***********************<< 添加电视墙风格应答 >>********************	
 *[消息方向]	ums -->  tool
 *
 */
_event(  ev_hduStyle_Add_Rsp )
	_body(EmModifyHduRet, 1)	//操作结果
	_body(THduStyleData, 1)
_ev_end

/***********************<< 删除电视墙预案请求 >>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduStyle_Del_Req )
_ev_end

/***********************<< 删除电视墙预案应答 >>********************	
 *[消息方向]	ums -->  tool
 *
 */
_event(  ev_hduStyle_Del_Rsp )
	_body(EmModifyHduRet, 1)	//删除结果
_ev_end

/***********************<< 更新电视墙预案 >>********************	
 *[消息方向]	tool -->  ums
 *
 */
_event(  ev_hduStyle_update_Req )
	_body(THduStyleData, 1)	
_ev_end

/***********************<< 更新电视墙预案 >>********************	
 *[消息方向]	ums -->  tool
 *
 */
_event(  ev_hduStyle_update_Rsp )
	_body(EmModifyHduRet, 1)
	_body(THduStyleData, 1)
_ev_end

/*				电视墙同UMC 交互消息                       */
/***********************<<  请求播放  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	umc	--> ums
 *
 */
 _event(  ev_HduPlay_Req )
	_body( TTPHduPlayReq,		1)	//信息
_ev_end

/***********************<<  请求播放回应  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	ums	--> umc
 *
 */
 _event(  ev_HduPlay_Ack )
	_body(u16,		1)
 _ev_end

/***********************<<  请求播放回应  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	ums	--> umc
 *
 */
 _event(  ev_HduPlay_NAck )
	_body( u16,		1)
	_body( EmTpHduPlayNackReason,     1)
_ev_end

/************************<<通知界面会场是否有码流>>*************************
*[消息体]			 
*   NULL
*[消息方向]	ums  -->  umc	
*
*/_event(  ev_HduCall_Valid )
		_body( TTPHduPlayReq,      1)
		_body( BOOL32,				  1)
  _ev_end

/***********************<<  停止播放  >>********************	
 *[消息体]			 删除电视墙的监控
 *   NULL
 *[消息方向]	umc	--> ums
 *
 */	_event(  ev_HduAllStopPlay_Req )
	_ev_end

/***********************<<  停止播放  >>********************	
 *[消息体]			 删除电视墙的监控
 *   NULL
 *[消息方向]	umc	--> ums
 *
 */_event(  ev_HduStopPlay_Req )
	_body( TTPHduPlayReq,		1)	//信息
	_ev_end

/***********************<<  停止播放应答  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	ums  -->  umc	
 *
 */_event(  ev_HduStopPlay_Ack )
	_body(TPHduBaseInfo,		1)
	_ev_end

/***********************<<  停止播放应答  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	ums  -->  umc	
 *
 */
 _event(  ev_HduStopPlay_NAck )
	_body(TPHduBaseInfo,		1)
_ev_end

/***********************<<  HDU注册状态  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	ums  -->  umc	
 *
 */
 _event(  ev_HduReg_Status_Nty )
	_body( u16, 1) //索引
	_body( BOOL32, 1)	//是否在在线
_ev_end

_event( ev_Hdu_SetVol)
	_body(THduSetVolInfo, 1)
_ev_end

_event( ev_Hdu_SetVol_Res)
	_body(THduSetVolInfo, 1)
	_body(EmTpHduSetVolRes, 1)
_ev_end	
		
#ifndef _MakeTpEventDescription_
	_ev_segment_end(tpumswithumshdu2)
};
#endif


#endif