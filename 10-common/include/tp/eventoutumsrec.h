#ifndef __h_eventoutumsrec_h_
#define __h_eventoutumsrec_h_

#include "tpeventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmEventRecMsg
{
#endif
	_ev_segment( outerumsrec )

/***********************<<通知录播服务器基本信息>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
_event(  ev_rec_base_info_nty )
	_body(TRecBaseInfo,	TP_MAX_VCR)	
_ev_end

/***********************<<更新录播服务器注册状态>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
_event(  ev_rec_reg_status_nty )
	_body(u8, 1)	//设备ID
	_body(BOOL32, 1) //是否注册
_ev_end


/***********************<<录播服务器文件列表>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
_event(  ev_rec_file_list_info )
	_body( TRecFileListInfo, 1)	//文件列表信息
_ev_end

/***********************<<删除文件>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
_event(  ev_rec_del_file_req )
	_body( TRecFileInfo, 1)	//文件列表信息
_ev_end

/***********************<<删除文件成功>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
_event( ev_rec_del_file_ack)
_ev_end

/***********************<<删除文件失败>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
_event( ev_rec_del_file_nack)
	_body(EmMdyRecFileRes, 1)
_ev_end

/***********************<<修改文件>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
_event(  ev_rec_mdy_file_req )
	_body( TRecFileInfo, 1)	//修改前的信息
	_body( TRecFileInfo, 1)	//修改后的信息
_ev_end

//修改失败
_event(  ev_rec_mdy_file_nack )
	_body( TRecFileInfo, 1)	//修改前的信息
	_body( TRecFileInfo, 1)	//修改后的信息
	_body( EmMdyRecFileRes, 1)//出错原因
_ev_end

//修改成功
_event(  ev_rec_mdy_file_ack )
	_body( TRecFileInfo, 1)	//修改前的信息
	_body( TRecFileInfo, 1)	//修改后的信息
_ev_end

/***********************<<会议录制信息>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
_event( ev_rec_conf_rec_info)
	_body(TConRecState, 1)
_ev_end

/***********************<<会议放像信息>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
_event( ev_rec_conf_play_info)
	_body(TConfPlayStatus, 1)
_ev_end


/***********************<<会议录像请求>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event( ev_rec_recorder_conf_req)
	_body(TRecConfInfo, 1)
 _ev_end

 /***********************<<会议录像应答>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event( ev_rec_recorder_conf_rsp)
	_body(TRecConfRes, 1)
	_body(EmUseReccorderRes, 1)	//结果
 _ev_end

 /***********************<<暂停会议录像>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event( ev_rec_pause_conf_req)
	_body(TRecConfRes, 1)
 _ev_end

  /***********************<<暂停会议录像应答>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event( ev_rec_pause_conf_rsp)
	_body(TRecConfRes, 1)
	_body(EmUseReccorderRes, 1)	//结果
 _ev_end

 /***********************<<继续会议录像>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event( ev_rec_resume_conf_req)
	_body(TRecConfRes, 1)
 _ev_end

  /***********************<<继续会议录像应答>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event( ev_rec_resume_conf_rsp)
	_body(TRecConfRes, 1)
	_body(EmUseReccorderRes, 1)	//结果
 _ev_end


/***********************<<停止录像>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event( ev_rec_stop_recorder_req)
	_body(TRecConfRes, 1)
 _ev_end

  /***********************<<停止录像应答>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event( ev_rec_stop_recorder_rsp)
	_body(TRecConfRes, 1)
	_body(EmUseReccorderRes, 1)	//结果
 _ev_end

 /***********************<<放像请求>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event( ev_rec_start_play_req)
	_body(TRecPlayInfo, 1)
 _ev_end

 /***********************<<放像应答>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event( ev_rec_start_play_rsp)
	_body(TRecPlayInfo, 1)
	_body(EmUseReccorderRes, 1)	//结果
 _ev_end

 /***********************<<暂停放像>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event( ev_rec_pause_play_req)
	_body(TPlayStatusMdyInfo, 1)
 _ev_end

 /***********************<<暂停放像应答>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event( ev_rec_pause_play_rsp)
	_body(TPlayStatusMdyInfo, 1)
	_body(EmUseReccorderRes, 1)	//结果
 _ev_end

  /***********************<<重启放像>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event( ev_rec_resume_play_req)
	_body(TPlayStatusMdyInfo, 1)
 _ev_end

 /***********************<<应答>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event( ev_rec_resume_play_rsp)
	_body(TPlayStatusMdyInfo, 1)
	_body(EmUseReccorderRes, 1)	//结果
 _ev_end

/***********************<<停止放像>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event( ev_rec_stop_play_req)
	_body(TPlayStatusMdyInfo, 1)
 _ev_end

  /***********************<<停止放像应答>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event( ev_rec_stop_play_rsp)
	_body(TPlayStatusMdyInfo, 1)
	_body(EmUseReccorderRes, 1)	//结果
 _ev_end

/***********************<<请求会场格式>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event( ev_rec_mt_format)
	_body(u16,	1)	//会议ID
	_body(u16, 1)	//会场ID
 _ev_end

 /***********************<<请求会场格式结果>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event( ev_rec_mt_format_rsp)
	_body(TTPRecMtFormat,	1)	//会议ID
 _ev_end




#ifndef _MakeTpEventDescription_
	_ev_segment_end( outerumsrec )
};
#endif

#endif
