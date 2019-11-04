/*
 * Register callback to nip
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

#ifndef __PPPCODE_H
#define __PPPCODE_H

#include "zebra/zserv.h"
#include "lib/aligned.h"


#define NIP_CMDBUF_MAX      256
#define NIP_RECEIVEBUF_MAX	256
#define NIP_API_MIN_UNIT_NUM			0
//#define NIP_IFNAME_MAX      64

//#define NIP_API_ADD_CFG     1   /* add config-item */
//#define NIP_API_DEL_CFG     2   /* delete config-item */
//#define NIP_API_DEF_CFG     4   /* not match whole command */
//#define NIP_API_DEL_DEF     (NIP_API_DEL_CFG|NIP_API_DEF_CFG)
//#define NIP_API_DEL_DEF		2

#define PAP_SENTNAME_MAX_LEN 		32
#define PAP_PASSWORDE_MAX_LEN 	32
#define CHAP_HOSTNAME_MAX_LEN 	32
#define CHAP_PASSWORD_MAX_LEN 	32

#define LCP_INTERVAL_MIN			1
#define LCP_INTERVAL_MAX			30
#define LCP_MAXRETRY_MIN			1
#define LCP_MAXRETRY_MAX			256
#define LCP_MAXWAIT_MIN			1
#define LCP_MAXWAIT_MAX			256
#define PROTOCOL_LEN				5
#define PEER_IP_LEN 					32


#define LCP_ECHO_INTERVAL_MIN		0
#define LCP_ECHO_INTERVAL_MAX		256
#define LCP_ECHO_RETRY_MIN			1
#define LCP_ECHO_RETRY_MAX		256
#define LCP_ECHO_PADDING_MIN		1
#define LCP_ECHO_PADDING_MAX		1492
#define IPCP_INTERVAL_MIN			1
#define IPCP_INTERVAL_MAX			30
#define IPCP_MAXRETRY_MIN			1
#define IPCP_MAXRETRY_MAX			256



#define MGROUP_MIN					0
#define MGROUP_MAX					15
#define NIP_API_MIN_VIR_UNIT_NUM	0
#define NIP_E1_MAX_VIR_UNIT_NUM	15

#define MULTILINK_USER_MAX_LEN	32
#define NIP_API_CHAR_LEN			32

#define MP_MAX_FRAGS_MIN 			1
#define MP_MAX_FRAGS_MAX			20

#define MP_MIN_PKTLEN_MIN			20
#define MP_MIN_PKTLEN_MAX			1500	

#define PPPOE_VIRTUAL_MIN_UNIT	16
#define PPPOE_VIRTUAL_MAX_UNIT	23

#define INTERFACE_NAMSIZ			20

#ifndef NULL
#define NULL 0
#endif

#define 	NIP_PPPOE_VERSION_NUMBER		"1.1"









#define NIP_PPP_SET_ECHOINTERVAL	ZMSG_PPP_BASE + 1
#define NIP_PPP_DEL_ECHOINTERVAL	ZMSG_PPP_BASE + 2
#define NIP_PPP_DEL_DEF_ECHOINTERVAL	ZMSG_PPP_BASE + 3

#define NIP_PPP_SET_ECHOMAXTRY	ZMSG_PPP_BASE + 4
#define NIP_PPP_DEL_ECHOMAXTRY	ZMSG_PPP_BASE + 5
#define NIP_PPP_DEL_DEF_ECHOMAXTRY	ZMSG_PPP_BASE + 6

#define NIP_PPP_SET_PPPAUTHEN	ZMSG_PPP_BASE + 7
#define NIP_PPP_DEL_PPPAUTHEN ZMSG_PPP_BASE + 8
#define NIP_PPP_DEL_DEF_PPPAUTHEN ZMSG_PPP_BASE + 9

#define NIP_PPP_SET_PAPINFO	ZMSG_PPP_BASE + 10
#define NIP_PPP_DEL_PAPINFO	ZMSG_PPP_BASE + 11
#define NIP_PPP_DEL_DEF_PAPINFO	ZMSG_PPP_BASE + 12

#define NIP_PPP_SET_CHAPHOSTNAME	ZMSG_PPP_BASE + 13
#define NIP_PPP_DEL_CHAPHOSTNAME	ZMSG_PPP_BASE + 14
#define NIP_PPP_DEL_DEF_CHAPHOSTNAME	ZMSG_PPP_BASE + 15

#define NIP_PPP_SET_CHAPPASSWORD	ZMSG_PPP_BASE + 16
#define NIP_PPP_DEL_CHAPPASSWORD	ZMSG_PPP_BASE + 17
#define NIP_PPP_DEL_DEF_CHAPPASSWORD	ZMSG_PPP_BASE + 18

#define NIP_PPP_SET_PEERIPADDR	ZMSG_PPP_BASE + 19
#define NIP_PPP_DEL_PEERIPADDR	ZMSG_PPP_BASE + 20
#define NIP_PPP_DEL_DEF_PEERIPADDR	ZMSG_PPP_BASE + 21

#define NIP_PPP_SET_LCPINTERVAL	ZMSG_PPP_BASE + 22
#define NIP_PPP_DEL_LCPINTERVAL	ZMSG_PPP_BASE + 23
#define NIP_PPP_DEL_DEF_LCPINTERVAL	ZMSG_PPP_BASE + 24

#define NIP_PPP_SET_LCPMAXTRY	ZMSG_PPP_BASE + 25
#define NIP_PPP_DEL_LCPMAXTRY	ZMSG_PPP_BASE + 26
#define NIP_PPP_DEL_DEF_LCPMAXTRY	ZMSG_PPP_BASE + 27

#define NIP_PPP_SET_IPCPINTERVAL	ZMSG_PPP_BASE + 28
#define NIP_PPP_DEL_IPCPINTERVAL	ZMSG_PPP_BASE + 29
#define NIP_PPP_DEL_DEF_IPCPINTERVAL	ZMSG_PPP_BASE + 30

#define NIP_PPP_SET_IPCPMAXTRY	ZMSG_PPP_BASE + 31
#define NIP_PPP_DEL_IPCPMAXTRY	ZMSG_PPP_BASE + 32
#define NIP_PPP_DEL_DEF_IPCPMAXTRY	ZMSG_PPP_BASE + 33

#define NIP_PPP_SET_MULTILINK	ZMSG_PPP_BASE + 34
#define NIP_PPP_DEL_MULTILINK	ZMSG_PPP_BASE + 35
#define NIP_PPP_DEL_DEF_MULTILINK	ZMSG_PPP_BASE + 36

#define NIP_PPP_SET_LCPMAXWAIT	ZMSG_PPP_BASE + 37
#define NIP_PPP_DEL_LCPMAXWAIT	ZMSG_PPP_BASE + 38
#define NIP_PPP_DEL_DEF_LCPMAXWAIT	ZMSG_PPP_BASE + 39
#ifdef NIP_API_PPP
#define NIP_PPP_SET_ENCAPT	ZMSG_PPP_BASE + 40
#define NIP_PPP_DEL_ENCAPT	ZMSG_PPP_BASE + 41
#define NIP_PPP_DEL_DEF_ENCAPT	ZMSG_PPP_BASE + 42
#endif
#define NIP_PPP_SET_LOOPBACKMODE	ZMSG_PPP_BASE +43
#define NIP_PPP_DEL_LOOPBACKMODE	ZMSG_PPP_BASE +44
#define NIP_PPP_DEL_DEF_LOOPBACKMODE	ZMSG_PPP_BASE +45

#define NIP_PPP_SET_MGROUP	ZMSG_PPP_BASE + 46
#define NIP_PPP_DEL_MGROUP	ZMSG_PPP_BASE + 47
#define NIP_PPP_DEL_DEF_MGROUP	ZMSG_PPP_BASE +48

#define NIP_PPP_SET_ECHOPADDINGLEN	ZMSG_PPP_BASE + 49
#define NIP_PPP_DEL_ECHOPADDINGLEN	ZMSG_PPP_BASE + 50
#define NIP_PPP_DEL_DEF_ECHOPADDINGLEN	ZMSG_PPP_BASE + 51

#define NIP_PPP_SET_PPPOE_PROTOCOL			ZMSG_PPP_BASE + 52
#define NIP_PPP_DEL_PPPOE_PROTOCOL			ZMSG_PPP_BASE + 53
#define NIP_PPP_DEL_DEF_PPPOE_PROTOCOL			ZMSG_PPP_BASE + 54

#define NIP_PPP_SET_SHUTDOWN			ZMSG_PPP_BASE + 55
#define NIP_PPP_DEL_SHUTDOWN			ZMSG_PPP_BASE + 56
#define NIP_PPP_DEL_DEF_SHUTDOWN			ZMSG_PPP_BASE + 57

#define NIP_PPP_SET_DEFROUTE			ZMSG_PPP_BASE + 58
#define NIP_PPP_DLE_DEFROUTE			ZMSG_PPP_BASE + 59
#define NIP_PPP_DEL_DEF_DEFROUTE			ZMSG_PPP_BASE + 60

#define NIP_PPP_SET_DEBUG_PPP		ZMSG_PPP_BASE + 61
#define NIP_PPP_SET_NO_DEBUG_PPP		ZMSG_PPP_BASE + 62

#define NIP_PPP_SET_DEBUG_PPPOE		ZMSG_PPP_BASE + 63
#define NIP_PPP_SET_NO_DEBUG_PPPOE		ZMSG_PPP_BASE + 64


#define NIP_PPP_GET_ECHOINTERVAL	ZMSG_PPP_BASE + 101
#define NIP_PPP_GET_ECHOMAXTRY	ZMSG_PPP_BASE + 102
#define NIP_PPP_GET_PPPAUTHEN	ZMSG_PPP_BASE + 103
#define NIP_PPP_GET_PAPINFO	ZMSG_PPP_BASE + 104
#define NIP_PPP_GET_CHAPHOSTNAME	ZMSG_PPP_BASE + 105
#define NIP_PPP_GET_CHAPPASSWORD	ZMSG_PPP_BASE + 106
#define NIP_PPP_GET_PEERIPADDR		ZMSG_PPP_BASE + 107
#define NIP_PPP_GET_LCPINTERVAL	ZMSG_PPP_BASE + 108
#define NIP_PPP_GET_LCPMAXTRY	ZMSG_PPP_BASE + 109
#define NIP_PPP_GET_MULTILINK	ZMSG_PPP_BASE + 110
#define NIP_PPP_GET_LCPMAXWAIT	ZMSG_PPP_BASE + 111
#ifdef NIP_API_PPP
#define NIP_PPP_GET_ENCAPT	ZMSG_PPP_BASE + 112
#endif
#define NIP_PPP_GET_LOOPBACKMODE	ZMSG_PPP_BASE +113
#define NIP_PPP_GET_MGROUP		ZMSG_PPP_BASE+114

#define NIP_PPP_GET_LOOPBACKSTATUS	ZMSG_PPP_BASE +115

#define NIP_PPP_GET_ECHOPADDINGLEN	ZMSG_PPP_BASE + 116
#define NIP_PPP_GET_IPCPINTERVAL	ZMSG_PPP_BASE + 117
#define NIP_PPP_GET_IPCPMAXRETRY	ZMSG_PPP_BASE + 118

#define NIP_PPP_GET_LOOPBACKIPADD		ZMSG_PPP_BASE  + 119
#define NIP_PPP_GET_PPPOE_PROTOCOL			ZMSG_PPP_BASE  + 120
#define NIP_PPP_GET_SHUTDOWN			ZMSG_PPP_BASE + 121
#define NIP_PPP_GET_DEFROUTE			ZMSG_PPP_BASE + 122
#define NIP_PPP_GET_PPPOESTATE		ZMSG_PPP_BASE + 123

#define NIP_MP_SET_MP_USER	ZMSG_MPAPI_BASE + 1
#define NIP_MP_DEL_MP_USER	ZMSG_MPAPI_BASE + 2
#define NIP_MP_DEL_DEF_MP_USER	ZMSG_MPAPI_BASE + 3
#define NIP_MP_GET_MP_USER	ZMSG_MPAPI_BASE + 4

#define NIP_MP_SET_BANDWITH	ZMSG_MPAPI_BASE + 5
#define NIP_MP_DEL_BANDWITH	ZMSG_MPAPI_BASE + 6
#define NIP_MP_DEL_DEF_BANDWITH	ZMSG_MPAPI_BASE + 7
#define NIP_MP_GET_BANDWITH	ZMSG_MPAPI_BASE + 8
#define NIP_MP_GET_LOOKBACKSTATUS	ZMSG_MPAPI_BASE + 9

//#define NIP_MP_GET_LOOKBACK_STATE	ZMSG_MPAPI_BASE + 9

#define NIP_MP_SET_MAX_FRAG	ZMSG_MPAPI_BASE + 10
#define NIP_MP_DEL_MAX_FRAG	ZMSG_MPAPI_BASE + 11
#define NIP_MP_DEL_DEF_MAX_FRAG	ZMSG_MPAPI_BASE + 12
#define NIP_MP_GET_MAX_FRAG	ZMSG_MPAPI_BASE + 13

#define NIP_MP_SET_MIN_PKT		ZMSG_MPAPI_BASE + 14
#define NIP_MP_GET_MIN_PKT		ZMSG_MPAPI_BASE + 15
#define NIP_MP_DEL_MIN_PKT		ZMSG_MPAPI_BASE + 16
#define NIP_MP_DEL_DEF_MIN_PKT		ZMSG_MPAPI_BASE + 17
struct ppp_intparam
{
#ifndef MOD_PPP_VER_4
	char ifname[INTERFACE_NAMSIZ+1];
#else
	char ifname[INTERFACE_NAMSIZ+1] aligned_def;
#endif
	int ifunit;
	int numpara;
};
struct ppp_numparam{
#ifndef MOD_PPP_VER_4
	char ifname[INTERFACE_NAMSIZ+1];
#else
	char ifname[INTERFACE_NAMSIZ+1] aligned_def;
#endif
	int ifunit;
	unsigned long numpara;
};

struct api_ifname{
#ifndef MOD_PPP_VER_4
	char ifname[INTERFACE_NAMSIZ+1];
#else
	char ifname[INTERFACE_NAMSIZ+1] aligned_def;
#endif
	int ifunit;
};
struct ppp_strparam{
#ifndef MOD_PPP_VER_4
	char ifname[INTERFACE_NAMSIZ+1];
#else
	char ifname[INTERFACE_NAMSIZ+1] aligned_def;
#endif
	int ifunit;
#ifndef MOD_PPP_VER_4
	char str[NIP_API_CHAR_LEN+1];
#else
	char str[NIP_API_CHAR_LEN+1] aligned_def;
#endif
};
struct ppp_papparam{
#ifndef MOD_PPP_VER_4
	char ifname[INTERFACE_NAMSIZ+1];
#else
	char ifname[INTERFACE_NAMSIZ+1] aligned_def;
#endif
	int ifunit;
#ifndef MOD_PPP_VER_4
	char username[PAP_SENTNAME_MAX_LEN +1];
	char password[PAP_PASSWORDE_MAX_LEN+1];
#else
	char username[PAP_SENTNAME_MAX_LEN +1] aligned_def;
	char password[PAP_PASSWORDE_MAX_LEN+1] aligned_def;
#endif
};
struct mpbind_param{
	int virunit;
#ifndef MOD_PPP_VER_4
	char name[MULTILINK_USER_MAX_LEN+1];
#else
	char name[MULTILINK_USER_MAX_LEN+1] aligned_def;
#endif
};

struct mp_num_getback{
	int errid;
	int numpara;
};

struct mp_numparam{
#ifndef MOD_PPP_VER_4
	char ifname[INTERFACE_NAMSIZ+1];
#else
	char ifname[INTERFACE_NAMSIZ+1] aligned_def;
#endif
	int ifunit;
	int  numpara;
};

struct ppp_pppoe_state_getback
{
	int errid;
	NIP_PPPOE_IF_STATE  buf ;
};

struct ppp_int_getback
{
	int errid;
	int numpara;
};
struct ppp_num_getback{
	int errid;
	unsigned long numpara;
};

struct ppp_str_getback{
	int errid;
#ifndef MOD_PPP_VER_4
	char str[NIP_API_CHAR_LEN+1];
#else
	char str[NIP_API_CHAR_LEN+1] aligned_def;
#endif
};
struct ppp_papgetback{
	int errid;
#ifndef MOD_PPP_VER_4
	char username[PAP_SENTNAME_MAX_LEN +1];
	char password[PAP_PASSWORDE_MAX_LEN+1];
#else
	char username[PAP_SENTNAME_MAX_LEN +1] aligned_def;
	char password[PAP_PASSWORDE_MAX_LEN+1] aligned_def;
#endif
};
#define MAX_VIR_USERNAME 20
#define MAX_MPBIND_USER_LEN 32
struct mpbind_getback{
	int errid;
#ifndef MOD_PPP_VER_4
	char usernames[MAX_VIR_USERNAME][MAX_MPBIND_USER_LEN];
#else
	char usernames[MAX_VIR_USERNAME][MAX_MPBIND_USER_LEN] aligned_def;
#endif
	int num;
};
struct lookback_state{
	int errid;
	int flag;
};













#endif

