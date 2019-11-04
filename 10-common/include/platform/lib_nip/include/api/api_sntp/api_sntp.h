/* NIP NTP API header
   Copyright (C) 2006 Kedacom
   Author: Yuanyi Zhang

This file is part of GNU Zebra.

GNU Zebra is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

GNU Zebra is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Zebra; see the file COPYING.  If not, write to the Free
Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

#ifndef __NIP_NTP_H
#define __NIP_NTP_H

#ifdef __cplusplus
extern "C" {
#endif

//error info callback
typedef  void (*SNTP_CALLBACK)(int error_code);

struct api_sntp_req
{
	union{
		struct {
			char ipaddr[16];
			int interval;
		}client_en_req;
		struct {
			int counter;
			int interval;
		}para_req;
		struct {
			int timeout;
		}adjtime_req;
		struct {
			int offset;
		}timezone_req;
	}params;
	int cmd;
	int res;
};

/* define ntp req command */
#define SNTP_CLIENT_START 		100
#define SNTP_CLIENT_STOP 		101
#define SNTP_SERVER_START 		102
#define SNTP_SERVER_STOP 		103
#define SNTP_ADJTIME 			104
#define SNTP_SYNCTIME 			105
#define SNTP_ERROR_CALL   		106
#define SNTPC_CFG_UPDATE 		107
#define SNTP_SET_TIMEZONE		108
#define SNTP_RM_CALLBACK		109
	
/* flags indicate if adj time succ */
#define SNTP_ADJTIME_SUCC    0
#define SNTP_ADJTIME_FAILED  1
#define SNTP_ADJTIME_SYSERROR 3
#define SNTP_ADJTIME_TIMEOUT 4

#define SNTP_SYNCTIME_SUCC    5
#define SNTP_SYNCTIME_FAILED  6
#define SNTP_SYNCTIME_SYSERROR 7
#define SNTP_ERROR_SYSERROR	8

#define SNTP_DO_ERROR			9
#define SNTP_RM_ERROR_CALL  	11


/*SNTP ERROR CODE*/
//#define SNTP_ERROR_TIMEOUT			0x1000					/* Recvive packet time out*/
//#define SNTP_ERROR_SETTIME			0x1001					/* Set System time error*/
#define SNTP_ERROR_RECVPACK			0x1002					/* Receiving pack error*/
#define SNTP_ERROR_RECVSCK			0x1003					/* Receiving SOCKETS error*/
#define SNTP_ERROR_SENSCK			0x1004					/* Sending socket error*/
#define SNTP_ERROR_INISOCK			0x1005					/* Init socket error*/
//#define SNTP_ERROR_BINDCLIENT		0x1006					/* Bind client socket error */
#define SNTP_ERROR_HOSTIP			0x1007					/* NTP/SNTP server ip error*/
#define SNTP_ERROR_CRETHRD			0x1008					/* Create client thread error*/
#define	SNTP_ERROR_STOPSCK			0x1009					/* Stop client socket error*/
#define SNTP_ERROR_INTERVAL			0x1010					/* Set interval error*/	
#define SNTP_ERROR_CLIEXIST			0x1011					/* Client has already started*/
#define SNTP_ERROR_SRVEXIST			0x1012					/* Server has already started*/
#define SNTP_ERROR_SYNCCOUNT        0x1013					/* Sync counter error*/



#define NIP_API_SNTP_REQ (NIP_SNTP_BASE + 1)

int sntp_client_start(char* ip, int time_interval);
int sntp_stop_client();
int sntp_adjtime(void (*callback)(int), int timeout);
int sntp_server_start();
int sntp_server_stop();
#ifdef __cplusplus
}
#endif

#endif
