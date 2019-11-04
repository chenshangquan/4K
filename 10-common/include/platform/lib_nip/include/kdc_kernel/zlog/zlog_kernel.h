#ifndef _ZLOG_KERNEL_H
#define _ZLOG_KERNEL_H

#define NETLINK_ZLOG		17	/* 16 to 31 are ethertap */

#define  ZLOG_SEND_BASE         0x30
#define  ZLOG_INFO_PACKET		ZLOG_SEND_BASE + 1

#define  ZLOG_SEND_MAX          ZLOG_SEND_BASE + 2


#define   ZLOG_REC_MSG_BASE     0x10
#define	 ZLOG_NOTIFY_MSG        ZLOG_REC_MSG_BASE+1

#define	 ZLOG_REC_MSG_MAX     	ZLOG_REC_MSG_BASE+2

#define ZLOG_DEBUG				7
#define ZLOG_INFO				6
#define ZLOG_NOTIFY				5
#define ZLOG_WARN				4
#define ZLOG_ERROR				3
#define ZLOG_CRITICAL			2
#define ZLOG_ALERT				1
#define ZLOG_EMERGE				0



struct zlog_kernel
{
	int 	level;
	char 	data[512];
	char 	proto[32];
};


struct zlog_user
{
    int     type;
    int     zlog_pid;
};

extern int zlog_kernel_init(void);

#endif
