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

struct api_sntp_req
{
	union{
		struct {
			char ipaddr[16];
			int interval;
		}client_en_req;
		struct {
			int timeout;
		}adjtime_req;
	}params;

	int cmd;
	int res;
};

/* define ntp req command */
#define SNTP_CLIENT_START 1
#define SNTP_CLIENT_STOP 2
#define SNTP_SERVER_START 3
#define SNTP_SERVER_STOP 4
#define SNTP_ADJTIME 5

/* flags indicate if adj time succ */
#define SNTP_ADJTIME_SUCC    0
#define SNTP_ADJTIME_FAILED  1
#define SNTP_ADJTIME_TIMEOUT 2
#define SNTP_ADJTIME_SYSERROR 3

#define NIP_API_SNTP_REQ (NIP_SNTP_BASE + 1)

int sntp_client_start(char*, int);
int sntp_client_stop();
int sntp_server_start();
int sntp_server_stop();
int sntp_adjtime(void (*callback)(int), int);

#ifdef __cplusplus
}
#endif

#endif
