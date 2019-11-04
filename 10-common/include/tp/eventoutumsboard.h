#ifndef _h_eventoutumsboard_h__
#define _h_eventoutumsboard_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmEventBoardMsg
{
#endif

	_ev_segment( outerumsboard )

/***********************<<通知单板信息>>********************	
 *[消息方向]	ums	-->  tool
 *
 */
_event(  ev_cardInfo_Nty )
	_body(TTPBrdInfo, 1)  //单板信息
	_body(s8, TP_BOARD_VERSION_LEN)  //单板硬件版本号
	_body(s8, TP_BOARD_VERSION_LEN)  //单板软件版本号
_ev_end

/***********************<<请求修改单板>>********************	
 *[消息方向]	tool  -->  ums
 *
 */
_event(  ev_cardModify_req )
	_body(TTPBrdCfg,	1)	//
_ev_end

/***********************<<单板修改响应>>********************	
 *[消息方向]	ums  -->  tool
 *
 */
_event(  ev_cardModify_rsp )
	_body(TTPBrdCfg,	1)	
	_body(EmTpBoardRet, 1)  //操作结果
_ev_end

/***********************<<请求删除单板>>********************	
 *[消息方向]	tool  -->  ums
 *
 */
_event(  ev_cardDel_req )
	_body(TTPBrdCfg,	1)	//
_ev_end

/***********************<<单板删除响应>>********************	
 *[消息方向]	ums  -->  tool
 *
 */
_event(  ev_cardDel_rsp )
	_body(TTPBrdCfg,	1)	//
	_body(EmTpBoardRet, 1)  //操作结果
_ev_end

/***********************<<请求添加单板>>********************	
 *[消息方向]	tool  -->  ums
 *
 */
_event(  ev_cardAdd_req )
	_body(TTPBrdCfg,	1)	//
_ev_end

/***********************<<单板添加响应>>********************	
 *[消息方向]	ums  -->  tool
 *
 */
_event(  ev_cardAdd_rsp )
	_body(TTPBrdCfg,	1)	//
	_body(EmTpBoardRet, 1)
_ev_end

// **********************<<请求添加单板模式>>********************	
//  *[消息方向]	tool  -->  ums
//  *
//  _event(  ev_cardModeAdd_req )
// 	_body(TTPBrdMdlInfo,	1)	//
// _ev_end
// 
// **********************<<单板模式添加响应>>********************	
//  *[消息方向]	ums  -->  tool
//  *
//  _event(  ev_cardModeAdd_rsp )
// 	_body(TTPBrdMdlInfo,	1)	//
// 	_body(EmTpBoardRet, 1)
// _ev_end

/***********************<<请求删除单板模式>>********************	
 *[消息方向]	tool  -->  ums
 *
 */
_event(  ev_cardModeDel_req )
	_body(TTPBrdMdlInfo,	1)	//
_ev_end

/***********************<<单板模式删除响应>>********************	
 *[消息方向]	ums  -->  tool
 *
 */
_event(  ev_cardModeDel_rsp )
	_body(TTPBrdMdlInfo,	1)	//
	_body(EmTpBoardRet, 1)
_ev_end

/***********************<<请求修改单板模式>>********************	
 *[消息方向]	tool  -->  ums
 *
 */
_event(  ev_cardModeModify_req )
	_body(TTPBrdMdlInfo,	1)	//
_ev_end

/***********************<<单板模式修改响应>>********************	
 *[消息方向]	ums  -->  tool
 *
 */
_event(  ev_cardModeModify_rsp )
	_body(TTPBrdMdlInfo,	1)	//
	_body(EmTpBoardRet, 1)
_ev_end

/***********************<<单板重启请求>>********************	
 *[消息方向]	tool  -->  ums
 *
 */
_event( ev_card_reboot_req )
	_body(TTPBrdPos, 1)       
_ev_end

/***********************<<混音器占用请求>>********************	
 *[消息方向]	tool  -->  ums
 *
 */
_event( ev_card_audiomix_used_req )     
_ev_end

/***********************<<画面合成占用请求>>********************	
 *[消息方向]	tool  -->  ums
 *
 */
_event( ev_card_vmp_used_req )     
_ev_end

/***********************<<码流适配占用请求>>********************	
 *[消息方向]	tool  -->  ums
 *
 */
_event( ev_card_bas_used_req )      
_ev_end

/***********************<<占用情况通知>>********************	
 *[消息方向]	ums  -->  tool
 *
 */
_event( ev_card_used_nty )
	_body(TTPBrdUsedInfo, 1)       
_ev_end

/***********************<<会议适配资源占用情况通知>>********************	
 *[消息方向]	ums  -->  umc
 *
 */
_event( ev_conf_bas_used_nty )
	_body(u16, 1)   //表示注册的外设数*7    
_ev_end

/***********************<<单板升级请求>>********************	
 *[消息方向]	ums  -->  tool
 *
 */
_event( ev_card_upgrade_req )
	_body(TTPBrdUpGrade, 1)       
_ev_end

/***********************<<单板升级结果>>********************	
 *[消息方向]	ums  -->  tool
 *
 */
_event( ev_card_upgrade_res )
	_body(u8, 1)  //板子层号
	_body(u8, 1)  //板子槽号
	_body(BOOL32, 1)       
_ev_end

#ifndef _MakeTpEventDescription_
	_ev_segment_end( outerumsboard )
};
#endif

#endif  //_h_eventoutumsboard_h__
