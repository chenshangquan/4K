#ifndef _h_eventoutumsconftemplate_h__
#define _h_eventoutumsconftemplate_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumsconftemplate
{
#endif
	
	_ev_segment( outerumsconftemplate )
		
/***********************<<  请求添加会议模板 >>********************	
 *[消息方向]	CMS	-->  UMS
 *
 */_event(  evtp_AddConfTemplate_req )
	_body ( TTPConfTemplate  , 1  )				//轮询列表有几个
	_ev_end

/***********************<<  请求删除会议模板 >>********************	
 *[消息方向]	CMS	-->  UMS
 *参数为m_wID
 */_event(  evtp_DelConftemplate_Req )
	_body ( u16  , 1  )
   _ev_end

/***********************<<  请求更新会议模板 >>********************	
 *[消息方向]	CMS	-->  UMS
 *以m_wID为索引
 */_event(  evtp_Updateconftemplate_Req )
	_body ( TTPConfTemplate  , 1  )
	_ev_end

/***********************<<  会议模板操作结果 >>********************	
 *[消息方向]	UMS	-->  CMS
 *添加，删除，更新都以返回此消息，具体原因在结构中定义
 */_event(  evpt_OperatorConfTemplate_Ret )		
	_body ( TOprConfTmpResult  , 1  )
   _ev_end


/***********************<<  UMS通知CMS增加模板列表 >>********************	
 *[消息方向]	UMS	-->  CMS
 *登录或者添加时，都以此消息向界面增加模板列表
 */_event(  evtp_AddConftemplate_Notify )		
	_body ( TTPConfTemplate  , 1  )
	_body ( BOOL32 , 1) //为界面大量刷新添加是否为最后一条标志位
	_ev_end

/***********************<<  UMS通知CMS删除的模板列表 >>********************	
 *[消息方向]	UMS	-->  CMS
 *
 */_event(  evtp_Delconftemplate_Notify )
	_body ( TDelRefreshConfTemplate  , 1  )
   _ev_end

/***********************<<  UMS通知CMS修改的模板列表 >>********************	
 *[消息方向]	UMS	-->  CMS
 *
 */_event(  evtp_Updateconftemplate_Notify )
	_body ( TTPConfTemplate  , 1  )
	_body ( BOOL32 , 1)
   _ev_end

/***********************<<导入模板文件>>********************	
 *[消息方向]	tool	-->  ums
 *
 */
_event(  ev_uploadConftemp_req )
	_body(s8, TP_UPLOAD_FILE_NAME_LENGTH)	//模板文件名  最大长度为 TP_UPLOAD_FILE_NAME_LENGTH
_ev_end


/***********************<<导入模板文件完成>>********************	
 *[消息方向]	ums	-->  tool
 *
 */
_event(  ev_uploadConftemp_rsq )
_ev_end


/***********************<<下载模板文件请求>>********************	
 *[消息方向]	tool	-->  ums
 *
 */
 _event(  ev_downloadConftemp_req )
_ev_end


/***********************<<下载模板文件应答>>********************	
 *[消息方向]	tool	-->  ums
 *
 */
 _event(  ev_downloadConftemp_rsq  )
	_body(s8, TP_UPLOAD_FILE_NAME_LENGTH)	//模板文件名  最大长度为 TP_UPLOAD_FILE_NAME_LENGTH
_ev_end

/***********************<<删除全部模板消息>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event(  ev_del_all_conftemp_req  )
_ev_end

/***********************<<删除全部模板消息应答>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event(  ev_del_all_conftemp_rsp  )
	_body ( TOprConfTmpResult  , 1  )
 _ev_end



#ifndef _MakeTpEventDescription_
		_ev_segment_end(outerumsconftemplate)
};
#endif


#endif // _h_eventoutumsconftemplate_h__
