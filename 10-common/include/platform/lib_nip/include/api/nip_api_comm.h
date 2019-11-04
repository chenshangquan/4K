/*
 * Communication library for NIP API
 * Copyright (C) 2005 kedacom
 * Author: Yuanyi Zhang
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2, or (at your
 * option) any later version.
 * 
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA. 
 */

#ifndef __NIP_API_COMM_H
#define __NIP_API_COMM_H

#include "api/lib/zipc/zipc.h"

#define ZMSG_NIP_API ZMSG_NIP_API_BASE

/* zhuzhm : nip_api message type */
#define NIP_ETHERNET_BASE           0x100
#define NIP_INTERFACE_BASE          0x200
#define NIP_ROUTE_BASE                  0x300
#define NIP_FTP_BASE                       0x400
#define NIP_WEBSERVER_BASE	 0x500
#define NIP_E1_BASE				 0x600
#define NIP_DRV_BASE				 0x700
#define NIP_SNTP_BASE                  0x800
#define NIP_DHCPC_BASE                       0x900
#define NIP_GENERAL_BASE              0x1000

/* zhuzhm : compatible with vxworks */
#ifdef WIN32
#define STATUS              int
#endif

#define NIP_RETURN_OK       0x0     /* success */
#define NIP_RETURN_NO_CFG   0x100   /* no config item returned */
#define NIP_RETURN_DEF_CFG  0x101   /* no config item, returnd default */
#define NIP_RETURN_ERROR    (~0)    /* other error */

#define NIP_API_ADD_CFG     1   /* add config-item */
#define NIP_API_DEL_CFG     2   /* delete config-item */
#define NIP_API_DEF_CFG     4   /* not match whole command */
#define NIP_API_DEL_DEF     (NIP_API_DEL_CFG|NIP_API_DEF_CFG)


/* zhuzhm : general constant */
#ifndef INTERFACE_HWADDR_MAX
#define INTERFACE_HWADDR_MAX 20
#endif
#define API_MAC_LEN INTERFACE_HWADDR_MAX
#ifndef INTERFACE_NAMSIZ
#define INTERFACE_NAMSIZ 20
#endif
#define API_IFNAME_LEN INTERFACE_NAMSIZ + 1
#define API_ADDR_STR_LEN 16
#define API_PREFIX_STR_LEN 20
#define ZIPC_API_PACKET_MAX_SIZE ZMSG_MAX_LEN

#define NIP_API_UNFINISHED 1

typedef int (*NIP_API_FUNC)(unsigned int, void*, int, ZIPC_ID);

int nip_api_sendmsg(int, unsigned int, void*, int, unsigned long);
int nip_api_recvmsg(int, unsigned int, void*, int, unsigned long*);
int nip_api_send_and_recv(unsigned int, void*, int, void*, int);
int nip_api_register(unsigned int, NIP_API_FUNC);
int nip_api_init_comm();
int nip_api_sendto(int fd, unsigned int type, ZIPC_ID addr, 
		   char* buf, int len, unsigned long flags);

/* nip api comm type define here.
 */

#endif
