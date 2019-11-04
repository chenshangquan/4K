/*************************************************************
  Copyright (C), 2000-2005, keda Tech. Co., Ltd.
  File name:      sntp.h
  Author: leyi     Version:  0.1      Date: 2005-11-1
  Description:    This file is used for sntp service for a head file.
    
  History:    
  
    1. Date:		2005-11-1
       Author:		leyi
       Modification:	create file
*************************************************************/
#ifndef _ZEBRA_SNTP_H
#define _ZEBRA_SNTP_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <lib/zebra.h>
#include <pthread.h>
#include <semaphore.h>
#include "lib/command.h"
#include "lib/thread.h"
#include "lib/zipc.h"
#include "lib/memory.h"

#include "lib/zlog.h"
#include "zebra/zserv.h"
#include "lib/acllib.h"

#define ZMSG_SNTP_ID		"sntp"

#define SNTP_DEBUG(fmt, args...)	zlog_msg("SNTP", ZLOG_DEBUG, fmt, ##args)
#define SNTP_INFO(fmt, args...)		zlog_msg("SNTP", ZLOG_INFO, fmt, ##args)
#define SNTP_NOTIF(fmt, args...)	zlog_msg("SNTP", ZLOG_NOTIFY, fmt, ##args)
#define SNTP_WARN(fmt, args...)		zlog_msg("SNTP", ZLOG_WARN, fmt, ##args)
#define SNTP_ERROR(fmt, args...)	zlog_msg("SNTP", ZLOG_ERROR, fmt, ##args)

#define ZMSG_SNTPC_BASE				1
#define ZMSG_SNTPS_BASE				100
#define ZMSG_SNTP_CMD				200
#define ZMSG_SNTPS_START			ZMSG_SNTPS_BASE+1
#define ZMSG_SNTPC_START			ZMSG_SNTPC_BASE+1
#define ZMSG_SNTPS_STOP				ZMSG_SNTPS_BASE+2
#define ZMSG_SNTPC_STOP				ZMSG_SNTPC_BASE+2
#define ZMSG_SNTPS_CFG				ZMSG_SNTPS_BASE+3
#define ZMSG_SNTPC_CFG				ZMSG_SNTPC_BASE+3
#define ZMSG_SNTPC_SYNCCALLER			ZMSG_SNTPC_BASE+4
#define ZMSG_SNTPC_CALLER			ZMSG_SNTPC_BASE+5
#define ZMSG_SNTPC_DO_ERROR		ZMSG_SNTPC_BASE+6
#define ZMSG_SNTPC_SET_TIMEZONE	ZMSG_SNTPC_BASE+7
#define ZMSG_SNTPC_RMCALLBACK		ZMSG_SNTPC_BASE+8


#define SNTP_IS_CLIENT(fd)			( fd < ZMSG_SNTPS_BASE && fd > ZMSG_SNTPC_BASE )
#define SNTP_IS_SERVER(fd)			( fd > ZMSG_SNTPS_BASE )

#define JAN_1970					2208988800.0			/* 1970 - 1900 in seconds */
#define NTP_SCALE					4294967296.0			/* 2^32, of course! */
#define NTP_EPOCH					1970					/* start epoch year */
#define NTP_MAX_YEAR				2036					/* end max year */

#define NTP_PACKET_MIN				48						/* Without authentication */
#define NTP_PACKET_MAX				68						/* With authentication (ignored) */
#define NTP_DISP_FIELD				8						/* Offset of dispersion field */
#define NTP_REFERENCE				16						/* Offset of reference timestamp */
#define NTP_ORIGINATE				24						/* Offset of originate timestamp */
#define NTP_RECEIVE					32						/* Offset of receive timestamp */
#define NTP_TRANSMIT				40						/* Offset of transmit timestamp */

#define NTP_LI_FUDGE				0						/* The current 'status' */
#define NTP_VERSION					3						/* The current version */
#define NTP_VERSION_MIN				1						/* The minmum valid version */
#define NTP_VERSION_MAX				4						/* The maximum valid version */
#define NTP_SER_STRATUM				15						/* The current stratum as a server */
#define NTP_CLI_STRATUM				0						/* The current stratum as a client */
#define NTP_STRATUM_MAX				15						/* The maximum valid stratum */
#define NTP_POLLING					6						/* The current 'polling interval' */
#define NTP_PRECISION				0						/* The current 'precision' - 1 sec. */

#define NTP_ACTIVE					1						/* NTP symmetric active request */
#define NTP_PASSIVE					2						/* NTP symmetric passive response */
#define NTP_CLIENT					3						/* NTP client request */
#define NTP_SERVER					4						/* NTP server response */
#define NTP_BROADCAST				5						/* NTP server broadcast */
#define NTP_PORT					123						/* NTP service port */	
#define NTP_INSANITY				3600.0					/* Errors beyond this are hopeless */
#define RESET_MIN					15						/* Minimum period between resets */
#define MILLION_L					1000000l				/* For conversion to/from timeval */
#define MILLION_D					1.0e6					/* Must be equal to MILLION_L */

#define NTP_MAXIPLEN				20						/*  input max ipaddr lengh */
#define NTPClkRate					1000000					/*  time rate value */
#define NTP_DEFAULT_CYCLE			64						/* default of ntp synchronization cycle */
#define NTP_MAX_CYCLE				1024					/* max ntp synchronization cycle */
#define NTP_WAIT_TICK				3						/* time to wait thread init */

#define SNTP_ETIMEDOUT				ETIMEDOUT				/* time of init client thread */
#define SNTP_CYCLE_RANGE			"<64-1024>"				/* cycle range of sntp */
#define SNTP_ACL_RANGE				"<1-99>"				/* acl number range of sntp */
#define SNTP_UDP_NUM				17						/* UDP protocol number  */

/* return value for sntp function */
#define SNTP_SERVICE_ALREADY_START		-1				/* sntp service alread start */
#define SNTP_SERVICE_NOT_START          -2
#define SNTP_COMM_ERR                   -3                     			       /* failed to send ctrl msg */
#define SNTP_THREAD_ERR			        -4					/* failed to start sntp thread */
#define SNTP_INIT_THREAD_ERR		    -5			              /* failed to init sntp thread */

#define SNTP_SUCCESS                    0

typedef struct SNTP_PARAM
{
	int						cycle;						/* input cycle value from user */
	char					servip[NTP_MAXIPLEN];		/* server ip address (client mode) */
} sntp_param;

/*sntp params list*/
typedef struct SNTP_VAR
{	
	int						sntp_sockc;					/* sntp client socket file descriptor */ 
	int						sntp_socks;					/* sntp server socket file descriptor */ 
	int						is_adjcall;					/* flag of upper call */
	int 						is_synccall;
	int 						counter;						/*sync counter*/
	int 						time_zone_offset;			/*time zone offset*/
	int 						is_do_error;					/* flag of do error*/
	double					offset;						/* offset time */
	double					error;						/* error time */
	double					latest_server;				/* Server's latest send timestamp */
	double					latest_client;				/*Client's latest send timestamp*/
	double					calltime;					/* send timestamp of upper caller (latest) */
	struct sockaddr_in		toc;						/* client target sockaddr_in struct */
	struct sockaddr_in		fromc;						/* client source sockaddr_in struct */
	struct sockaddr_in		tos;						/* server target sockaddr_in struct */
	struct sockaddr_in		froms;						/* server source sockaddr_in struct */
	fd_set 					allset;						/* fd all set of sntp */
	struct timeval			cycle;						/* cycle of synchronization */
	unsigned char			transmit[NTP_PACKET_MIN];	/* send request buffer */
	unsigned char			receive[NTP_PACKET_MAX+1];	/* receive response buffer */
} sntp_var;

/* The unpacked NTP data structure, with all the fields */
/* even remotely relevant to SNTP. */
typedef struct NTP_DATA {
   	double					dispersion;					/* root dispersion */
	double					reference;					/* reference timestamp */	 
	double					originate;					/* original timestamp */
	double					receive;					/* receiving timestamp */
	double					transmit;					/* transmit timestamp */
	double					current;					/* current timestamp */
	unsigned char			status;						/* leap indicator */
	unsigned char			version;					/* version number */
	unsigned char			mode;						/* mode */
	unsigned char			stratum;					/* stratum */
	unsigned char			polling;					/* poll interval */
	unsigned char			precision;					/* precision */
} ntp_data;

/* sntp message structure */
struct sntp_msg {
	long					type;						/* sntp cmd type */
	int						cycle;						/* set cycle of synchronization */	
	int						acl_num;					/* sntp acl-number (server mode) */
	int 					counter;						/*sync counter*/
	char					addr[NTP_MAXIPLEN];			/* input server ip addr (client mode) */
	int 					timezone_offst;				/*timezone offset*/
	
};

extern void sntp_init();
extern void stream_get (struct stream *s, void *dst, size_t size);
extern void stream_put (struct stream *s, void *src, size_t size);
extern int acl_pkt_match(ACL_TUPLE *tuple, unsigned int rulenum);
int sntp_send_msg(struct sntp_msg  *send_msg, char * msg_id);
int sntp_ipaddr_check (char *dot_addr);
int sntp_client_start_internal(char *ipaddr, int cy);
int sntp_client_stop_internal(void);
int sntp_server_start_internal(void);
int sntp_server_stop_internal(void);
int sntp_adjtime_internal();
/*int sntp_synctime_internal();*/
int sntp_para_internal(const int interval,const int counter);
int sntp_do_error_internal();
int sntp_set_timezone_internal(int offset);
int sntp_rmcallback_internal();

#endif
