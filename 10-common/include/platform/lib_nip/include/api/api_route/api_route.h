
/* api_route.h -
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

#ifndef _API_ROUTE_H_
#define _API_ROUTE_H_

#include "api/nip_api.h"

#define NIP_ROUTE_SET_ROUTE     NIP_ROUTE_BASE+1
#define NIP_ROUTE_GET_ROUTE     NIP_ROUTE_BASE+2
#define NIP_ROUTE_GET_STATIC_ROUTE     NIP_ROUTE_BASE+3
#define NIP_ROUTE_GET_ALL_STATIC_ROUTE     NIP_ROUTE_BASE+4
#define NIP_ROUTE_SET_DEFAULT_GATEWAY   NIP_ROUTE_BASE+5
#define NIP_ROUTE_GET_DEFAULT_GATEWAY   NIP_ROUTE_BASE+6
#define NIP_ROUTE_GET_NEXTHOP               NIP_ROUTE_BASE+7

struct api_set_route
{
    int errid;
    int opcode;
    char dest[API_PREFIX_STR_LEN];
    char mask[API_ADDR_STR_LEN];
    char gate[API_ADDR_STR_LEN];
    char distance[16];
};

struct api_srt_entry {
	u_char flags;
	u_char prio;
	u_long net;
	u_long mask;
	u_long nexthop;
	char if_name[32];
	u_long if_unit;
	u_long tag;
	u_long metric;
};

struct api_route_static_info
{
    struct api_route_static_info *prev;
    struct api_route_static_info *next;
    u_long dest;
    u_long mask;
    int  type;
#define API_ROUTE_GATEWAY     1
#define API_ROUTE_IFNAME        2
#define API_ROUTE_BLACKHOLE   3
    u_long gate;
    char ifname[API_IFNAME_LEN];
    u_char distance;
    u_long tag;
    u_long metric;
};

struct api_nexthop_info
{
    struct api_nexthop_info *prev;
    struct api_nexthop_info *next;
    u_char flag;
    u_char type;
    u_long gate;
    u_long ifindex;
    char ifname[API_ADDR_STR_LEN];
};

struct api_route_info
{
    struct api_route_info *prev;
    struct api_route_info *next;
    u_long type;
    u_char flag;
    u_long dest;
    u_long mask;
    u_char distance;
    u_long metric;
    u_long nexthop_num;
    struct api_nexthop_info *nexthop;
};

extern void nip_api_route_register();

extern int nip_static_get_ip_routeinfo_ex (char **title, int *tsize, char **pdata, int *dsize);
extern int nip_static_get_ip_routeinfo_linux (int *num, struct api_route_static_info **rtinfo);
extern int nip_static_set_ip_route (char *ip_net, char *ip_mask, 
                                char *intfName_or_address, char *unit, int pri, int opcode);
extern int nip_static_set_ip_route_linux (char *dest_str, char *mask_str, 
                                char *gate_str, int distance, int opcode);
extern int nip_get_static_route_nexthop (char *dest_str, char *mask_str, int *num, u_long **gate);
#if 1
extern int netlink_get_route_gw(char *dest, u_long *gw);
#endif
extern int nip_get_route_nexthop (char *dest_str, char *mask_str, int *num, struct api_nexthop_info **gate);

#if 1   /* zhuzhm : not support now */
extern int nip_static_set_ip_route_distance (int distance, int opcode);
extern int nip_static_get_ip_route_distance (int *distance);
extern int nip_static_get_ip_route_distance_ex (int *distance);
#endif
    
extern void api_free_static_rtinfo (struct api_route_static_info *rtinfo);
extern void api_free_nexthop (struct api_nexthop_info *rtinfo);

extern void api_print_route_errstr(int error_no);

#endif  /* _API_ROUTE_H_ */
