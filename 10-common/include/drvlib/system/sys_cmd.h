#ifndef EXEC_SYSTEMCMD_H
#define EXEC_SYSTEMCMD_H

#ifdef __cplusplus
extern "C" {
#endif

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/syscall.h>
#define SYSCMD_BUFF_SIZE	1024

/*needn't response*/
#define SYSCMD_REQ_0		0	/*不用返回状态与结果的请求*/
/*need exec status to response*/
#define SYSCMD_REQ_1		1	/*要返回执行状态的请求*/
/*need exec status&result to response*/
#define SYSCMD_REQ_2		2	/*要返回执行状态与执行结果的请求*/


/* exec sucess*/
#define SYSCMD_REPLY_SUCESS	0	/*执行成功*/
/*exec fail*/
#define SYSCMD_REPLY_FAILED	1	/*执行失败*/

struct syscmd {
	/*请求类型或者返回状态*/
	unsigned int code;
	/*请求指令或者指令输出*/
	char data[SYSCMD_BUFF_SIZE];
};

struct msg_buf{
	/*内核线程号*/
	long mtype;

	/*传送信息体*/
	struct syscmd cmd;
};


int SysExecCmd( const char *cmd, const char *retbuf);

#ifdef __cplusplus
}
#endif

#endif

