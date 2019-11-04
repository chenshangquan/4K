/* pingLib.h - Packet InterNet Grouper (PING) library header */

/* Copyright 2005 linux Systems, Inc. */

/*
modification history
--------------------

*/

#ifndef _API_GENERAL_H_
#define _API_GENERAL_H_
#ifdef __cplusplus
extern "C" {
#endif

/* defines */
#include "api/nip_api.h"
#include "lib/user_pass.h"

#define NIP_GENERAL_WRITE_CONFIG     NIP_GENERAL_BASE + 1
#define NIP_GENERAL_SET_USER             NIP_GENERAL_BASE + 2
#define NIP_GENERAL_SET_PATH             NIP_GENERAL_BASE + 3
#define NIP_GENERAL_SET_SHELL             NIP_GENERAL_BASE + 4
#define NIP_GENERAL_SET_SHELL_DEFAULT     NIP_GENERAL_BASE + 5
#define NIP_GENERAL_GET_SHELL_DEFAULT     NIP_GENERAL_BASE + 6
#define NIP_GENERAL_ROB_RS232             NIP_GENERAL_BASE + 7

#define API_GENERAL_FILENAME_LEN 250
#define API_GENERAL_USERNAME_LEN 32
#define API_GENERAL_PATHNAME_LEN 255


#define API_GENERAL_CHANGE_PATH 1
#define API_GENERAL_UNCHANGE_PATH 0

struct api_general_write
{
    int retid;
    int option; /*0 == default 1 == not default*/
    char fname[API_GENERAL_FILENAME_LEN];
};

struct api_general_user
{
    int retid;
    int option;
    int service_type;
    char user_name[API_GENERAL_USERNAME_LEN + 1];
    char password[API_GENERAL_USERNAME_LEN + 1];
};

struct api_general_path
{
    int retid;
    int option;/*1 == set 0 == unset*/
    char fpath[API_GENERAL_PATHNAME_LEN];
};

struct api_general_shell
{
    int retid;
    int option;/**/
};

struct api_general_rob
{
    int retid;
    int option;
};

int nip_write( char *              fname   /* file name to write to */);
  
/*********************
*service_type参数由以下枚举变量指定，可见user_name.h
*
typedef enum user_password
{
  USER_PASS_EXEC = 0,     //EXEC 验证
  USER_PASS_EXEC_SUPER,     //EXEC SUPER 验证
  USER_PASS_FTP,         //FTP 验证
  USER_PASS_TELNET,     //TELNET 验证
  USER_PASS_TELNET_SUPER,     //TELNET 验证
  USER_PASS_PPP,         //PPP链路 验证
  USER_PASS_HTTP, //HTTP链路 验证
  USER_PASS_MAX,         //验证类型的最大值
}user_password
*****/

int nip_gnl_set_usrinfo
	(
		char * 			usrname, /*用户名*/
		char * 			password,/*密码*/
		int  			service_type, /*类型*/
		int 			opcode/*操作符*/
	);

int nip_pathInit();
int nip_pathReg(char  * pathname);
int nip_pathUnReg();
int nip_gnl_set_shell_auto_start (int opcode);
int nip_gnl_set_shell_default(int opcode);
int nip_gnl_get_shell_default();
int rs232_fd_rob();
int rs232_fd_restitute();

void nip_api_general_register();

#ifdef __cplusplus
}
#endif
#endif /* __INCpingLibh */
