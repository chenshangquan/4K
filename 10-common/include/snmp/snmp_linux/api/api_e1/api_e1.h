
/* api_e1.h -
 *
 * Copyright 2006 suzhou Keda co.
 *
 * description :
 * -------------------------
 * Purpose: for nip api.
 *
 * modification history
 * -------------------------
 * 2006-2-7 10:55 luchen write first.
 */

#ifndef _API_E1_H_
#define _API_E1_H_

#include "api/nip_api.h"

#define NIP_E1_ADD_INTF		NIP_E1_BASE + 1
#define NIP_E1_DEL_INTF		NIP_E1_BASE + 2
#define NIP_E1_ADD_LOGIC	NIP_E1_BASE + 3
#define NIP_E1_DEL_LOGIC  	NIP_E1_BASE + 4
#define NIP_E1_ADD_MODE  	NIP_E1_BASE + 5
#define NIP_E1_DEL_MODE  	NIP_E1_BASE + 6
#define NIP_E1_GET_MODE  	NIP_E1_BASE + 7
#define NIP_E1_ADD_FRAME 	NIP_E1_BASE + 8
#define NIP_E1_DEL_FRAME 	NIP_E1_BASE + 9
#define NIP_E1_GET_FRAME 	NIP_E1_BASE + 10
#define NIP_E1_ADD_LOOP  	NIP_E1_BASE + 11
#define NIP_E1_DEL_LOOP  	NIP_E1_BASE + 12
#define NIP_E1_GET_LOOP  	NIP_E1_BASE + 13
#define NIP_E1_ADD_CLOCK 	NIP_E1_BASE + 14
#define NIP_E1_DEL_CLOCK 	NIP_E1_BASE + 15
#define NIP_E1_GET_CLOCK 	NIP_E1_BASE + 16
#define NIP_E1_GET_INFO  	NIP_E1_BASE + 17
#define NIP_E1_GET_TRANS	NIP_E1_BASE + 18

#define MAX_IFMODE_LEN 16
#define MAX_E1_CFG_LEN 128
#define MAX_IFNAME_LEN 		16
#define MAX_TTYNAME_LEN 	16
#define MAX_TIMESLOTS_LEN 	128
#define MAX_SERIALNAME_LEN   32

struct e1_param{
	int  e1;
	int  channel;
	int  serial;
	char ifname[MAX_IFNAME_LEN];
	char timeslot[MAX_TIMESLOTS_LEN];
	char ifmode[MAX_IFMODE_LEN];
};

struct e1_getback{
	int  ret;
	char e1_cfg[MAX_E1_CFG_LEN];
};

extern int nip_e1_set_intf(char *, int, int);
extern int nip_e1_set_bind(char *, int, int, char *, int, int);
extern int nip_e1_set_mode(char *, int, char *, int, int);
extern int nip_e1_set_fcs(char *, int, char *, int);
extern int nip_e1_set_loopback(char *, int, char *, int);
extern int nip_e1_set_clock(char *, int, char *, int);
extern int nip_e1_get_info(char * ifname, int serial, char * cfg_str);
extern int nip_e1_get_mode(char * ifname, int e1, char * mode);
extern int nip_e1_get_fcs(char * ifname, int e1, char * frame);
extern int nip_e1_get_clock(char * ifname, int e1, char * clock);
extern int nip_e1_get_loopback(char * ifname, int e1, char * loop);
extern void nip_api_e1_register();

#endif  /* _API_E1_H_ */

