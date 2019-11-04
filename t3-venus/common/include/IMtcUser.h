#ifndef __IMTCUSER_H__
#define __IMTCUSER_H__

#include "dispevent.h"

class IMtcUser : public CDispEvent
{
public:
	/*功能	修改用户
	参数	user	用户
			bAdmin	是否让用户具有管理员权限
	返回值	成功返回0;失败返回非0错误码
	说明	仅能修改当前登录的用户*/
	virtual u16 Modify(const CUserFullInfo& user) = 0;
	/*功能	增加用户
	参数	user	用户
	返回值	成功返回0;失败返回非0错误码
	说明	需要管理员权限*/
	virtual u16 Add(const CUserFullInfo& user) = 0; 
	/*功能	删除用户
	参数	user	用户
	返回值	成功返回0;失败返回非0错误码
	说明	需要管理员权限*/
	virtual u16 Delete(const CUserFullInfo& user) = 0;
	/*功能	请求全部用户列表
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	MTC_UI_USERS_UPDATED消息后调用GetUsers获取用户列表*/
	virtual u16 ReqUsers() = 0;
	/*功能	获取用户列表
	参数	无
	返回值	用户列表
	说明	参见ReqUsers*/
	virtual const vector<CUserFullInfo>& GetUsers()const = 0;
}; // IMtcUser

#endif
