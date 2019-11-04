
/* api_interface.h -
 *
 * Copyright 1997-2003 suzhou Keda co.
 *
 * description :
 * -------------------------
 * Purpose: for nip api.
 *
 * modification history
 * -------------------------
 * 2005-11-30 zhuzhenming write first.
 */

#ifndef _API_INTERFACE_H_
#define _API_INTERFACE_H_

#include "api/nip_api.h"

#define NIP_INTERFACE_SET_IP    NIP_INTERFACE_BASE+1
#define NIP_INTERFACE_GET_MASTER_IP    NIP_INTERFACE_BASE+2
#define NIP_INTERFACE_GET_ALL_IP    NIP_INTERFACE_BASE+3
#define NIP_INTERFACE_GET_STATUS    NIP_INTERFACE_BASE+4
#define NIP_INTERFACE_DEL_IF            NIP_INTERFACE_BASE+5
#ifdef NIP_API_BANDWIDTH
#define NIP_INTERFACE_SET_BANDWIDTH            NIP_INTERFACE_BASE+6
#define NIP_INTERFACE_DEL_BANDWIDTH            NIP_INTERFACE_BASE+7
#define NIP_INTERFACE_GET_BANDWIDTH            NIP_INTERFACE_BASE+8
#endif
#define NIP_INTERFACE_GET_LOOPBACKSTATUS	NIP_INTERFACE_BASE +9
/* if status */
#define IP_ADDR_NOT_SET			0
#define IP_ADDR_SET_AND_UP		1
#define IP_ADDR_SET_AND_DOWN		2

#define NIP_API_ADD_IP     1 
#define NIP_API_DEL_IP     2   
/* linux */
#define NIP_API_ADD_SEC_IP     9
#define NIP_API_DEL_SEC_IP     10
#define NIP_API_DEL_ALL_IP     11

struct api_get_ip_status
{
    int errid;
    u_long ipaddr;
    int status;
};

struct api_ip
{
    u_long ipaddr;
    u_long mask;
};

struct api_get_ip
{
    int errid;
    u_long ipaddr;
    u_long mask;
};

struct api_set_ip
{
    int errid;
    char ifname[API_IFNAME_LEN];
    char addr_str[API_PREFIX_STR_LEN];
    int opcode;
};

#ifdef NIP_API_BANDWIDTH
struct api_set_num
{
    char ifname[API_IFNAME_LEN];
    unsigned long numparams;
    int opcode;
};
struct api_get_num
{
    int errid;
    unsigned long numparams;
};
struct api_get_int
{
	int errid;
	int numparams;
};
#endif
extern void nip_api_interface_register();

extern int nip_if_get_ipaddr(char *ifname, int ifunit, char *ip_addr, char *ip_mask);
extern int nip_if_get_ipaddr2(char *ifname, int ifunit, unsigned long *ip_addr, unsigned long *ip_mask);
extern int nip_if_get_master_ipaddr(char *ifname, unsigned long *ip_addr, unsigned long *ip_mask);
extern int nip_if_get_all_ipaddr(char *ifname, int *num, struct api_ip **ip);
extern int nip_if_set_ipaddr(char *ifname, int ifunit, char *ip_addr, char *ip_mask, int opcode);
extern int nip_if_set_ipaddr_linux(char *ifname, char *ip_addr, char *ip_mask, int opcode);
extern int api_if_get_ipaddr_status(unsigned long ip_addr);
extern int api_if_get_ipaddr_status_linux(unsigned long ip_addr, int *status);
extern int nip_if_del (char *ifname, int ifunit);
extern int nip_if_del_linux (char *ifname);
extern void api_print_interface_errstr(int error_no);
extern int nip_set_interface_config_mode(char *ifname);
#ifdef NIP_API_BANDWIDTH
extern int nip_if_set_bandwidth(char *ifname ,int  ifunit ,unsigned long bandwidth,int opcode );
extern int nip_if_get_bandwidth(char *ifname,int ifunit ,unsigned long  *bandwidth);
#endif
extern int nip_if_get_loopbackstatus(char *ifname,int ifunit ,int *loopback);

#endif  /* _API_INTERFACE_H_ */
