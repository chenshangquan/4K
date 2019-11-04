#ifndef _UMCOSNT_H_
#define _UMCONST_H_
/// 错误码
#define UM_USER_ERR		    (u16)19001
#define UM_PSW_ERR 		    (u16)19002
#define UM_ACTOR_NOTMATCH	(u16)19003
#define UM_USER_DUPLICATE	(u16)19004
#define UM_USER_NOTEXIST	(u16)19005
#define UM_NOT_ENOUGHMEM	(u16)19006
#define UM_ACTOR_ONLY		(u16)19007
#define UM_OPERATE_NOTPERMIT    (u16)19008
#define UM_MULTILOGIN		(u16)0xffff ///< 终端定义的一个返回，不允许重复登录的错误码

#define UM_OK			0xAA    ///< 返回成功
/// 定义最大的用户数目
#define MAX_USERNUM		128
#define MAX_CHARLENGTH		32
/// 定义用户身份
#define UM_ADMIN		0x01
#define UM_OPERATOR		0x02
#define MAX_USERINFO_PER_MSG    15    ///< 每条UM_MCS_GETALLUSER_NOTIF返回的用户信息数

#define MAX_UMFILENAME_LEN      32    ///< 最大文件名长度


#endif
