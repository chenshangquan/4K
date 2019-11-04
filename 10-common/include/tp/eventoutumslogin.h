#ifndef _h_eventoutumslogin_h__
#define _h_eventoutumslogin_h__

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumslogin
{
#endif
	
	_ev_segment( outerumslogin )
		
/***********************<<   >>********************	
 *[消息方向]	CMS	-->  UMS
 *登录请求，参数为CLoginReques，此消息直接用OSP发送，不经过XML编解码
 */
_event(  ev_UMSLoginReq )
	_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CMS
 *登录反馈
 */
_event(  ev_UMSLoginRet )
	_body(TLoginRet,	1)
	_ev_end

/***********************<<   >>********************	
 *[消息方向]	CMS	-->  UMS
 *添加用户请求，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
 */
_event(  ev_UMSAddUserReq )
	_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CMS
 *添加反馈
 */
_event(  ev_UMSAddUserRet )
	_body(EmTpRet,	1)	//操作结果
	_body(u16,	1)		//结果代码，如果错误，此处为错误原因
	_ev_end

/***********************<<   >>********************	
 *[消息方向]	CMS	-->  UMS
 *删除用户请求，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
 */
_event(  ev_UMSDelUserReq )
	_ev_end	

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CMS
 *删除反馈
 */
_event(  ev_UMSDelUserRet )
	_body(EmTpRet,	1)	//操作结果
	_body(u16,	1)	//结果代码，如果错误，此处为错误原因
	_ev_end

/***********************<<   >>********************	
 *[消息方向]	CMS	-->  UMS
 *修改用户密码，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
 */
_event(  ev_UMSChangePWDReq )
	_ev_end	

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CMS
 *修改反馈
 */
_event(  ev_UMSChangePWDRet )
	_body(EmTpRet,	1)	//操作结果
	_body(u16,	1)	//结果代码，如果错误，此处为错误原因
	_ev_end	

/***********************<< UMS通知CMS，有一个用户登录  >>********************	
 *[消息方向]	UMS	-->  CMS
 *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
 */
_event(  ev_UmsAddUser_Notify )
_ev_end	
	
/***********************<< UMS通知CMS，有一个用户退出登录  >>********************	
 *[消息方向]	UMS	-->  CMS
 *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
 */
_event(  ev_UmsDelUser_Notify )
_ev_end	
	
/***********************<< UMS通知CMS，修改用户  >>********************	
 *[消息方向]	UMS	-->  CMS
 *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
 */
_event(  ev_UmsUpdateUser_Notify )
_ev_end	


/***********************<< UMS通知CMS，用户在其它地方登录  >>********************	
 *[消息方向]	UMS	-->  CMS
 *
 */
_event(  ev_UmsLoginByOther_Notify )
_body(u32_ip, 1)
_ev_end	


#ifndef _MakeTpEventDescription_
		_ev_segment_end(outerumslogin)
};
#endif




#endif // _h_eventoutumslogin_h__
