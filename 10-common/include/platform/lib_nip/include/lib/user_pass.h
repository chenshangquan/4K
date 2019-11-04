#ifndef _USER_PASS_H_
#define _USER_PASS_H_

/* user_pass.h - 
 *
 * Copyright 1997-2002 suzhu Keda co.
 *
 * description :
 * -------------------------
 * Purpose: for user and password logging in
 *
 * modification history
 * -------------------------
 * 2004/12/14, feixp write.
 * say: 如果函数类型为int，则函数失败返回0，反之返回值大于0
 *      如果函数类型为user_pass_node *，则函数失败返回NULL
 */
#if 0
#include "lib/zebra.h"
#include "lib/vty.h"
#endif

struct vty;

#ifdef __cplusplus
extern "C" {
#endif
#define USERNAME_CONFIG_ZLOG    1
#define USERNAME_LOG_LENGTH                                     512
#define  USER_PASS_LEN 32                     /*用户名和密码的字符串的最大长度*/
#define  USER_PASS_NODE_LIMIT 20         /*最多可以配置EXEC验证的用户名和密码的记录数*/
#define  ZMSG_USER_PASS_OPTION ZMSG_USER_PASS_BASE + 1
#define ORDER_CHAR 				 4



typedef enum user_password
{
  USER_PASS_EXEC = 0,     /*EXEC 验证*/
  USER_PASS_EXEC_SUPER,     /*EXEC SUPER 验证*/
  USER_PASS_FTP,         /*FTP 验证*/
  USER_PASS_TELNET,      /*TELNET 验证*/
  USER_PASS_TELNET_SUPER,      /*TELNET 验证*/
  USER_PASS_PPP,         /*PPP链路 验证*/
  USER_PASS_HTTP,
  USER_PASS_MAX,         /*验证类型的最大值*/
}user_password;

#ifdef SERVICE_TYPE_DIS
char *service_display[USER_PASS_MAX] = {"exec","exec super", "ftp","telnet","telnet super","ppp","http"};
#endif

typedef enum user_pass_option
{
	user_pass_check_option = 0,
	user_pass_get_option,
	user_pass_add_option,
	user_pass_del_option,
}user_pass_option;




/*****************************************************************
*   this four internface function is called by user
*
******************************************************************/


/*初始化全局数组*/
extern int user_pass_init( );
extern int user_pass_init_forppp( );



/*找到与id相符的链表，并且插入链表*/

extern int user_pass_add_usepass( int id, char * pstr_user, 
						 char * pstr_pass);

/*找到与id相符的链表, 并且按照用户名查找相应的密码，如有，
则返回值为1，在char ** pstr_pass返回相应的密码， 否则返回值为0*/
extern int user_pass_get_pass(int id, char * pstr_user, char * pstr_pass);

/*找到与id相符的链表，并且删除链表*/
extern int  user_pass_del_usepass(int id, char * pstr_user//, 
						  /*char * pstr_pass*/);
/*验证用户名和密码*/
extern int user_pass_check(int id, char * pstr_user, char * pass);

/*这个函数显示用户名和密码的配置信息 */
extern int config_user_pass_write_host(struct vty *vty);

/*这个函数擦除用户名和密码的配置信息 */
extern int config_user_pass_erase_host(struct vty *vty);

/*验证用户名和密码,在跨进程下被调用*/
extern int user_pass_check_interproc(int id, char * pstr_user, char * pass);

/*作用与user_pass_get_pass相同，只是在跨进程下被调用*/
extern int user_pass_get_pass_interproc(int id, char * pstr_user, char * pstr_pass);

/*增加用户名和密码,在跨进程下被调用*/
extern int user_pass_add_usepass_interproc(int id, char *user, char * pass);

/*删除用户名和密码,在跨进程下被调用*/
extern int user_pass_del_usepass_interproc(int id, char *user);

/*创建链表，并且初始化全局数组*/
extern void  _user_pass_init( );


extern int username_config_error_logging(const char * fmt, ...);

/*返回指定链表的纪录个数*/
extern int user_pass_num(int id);


#ifdef __cplusplus
}
#endif

#endif/* _USER_PASS_H_ */





