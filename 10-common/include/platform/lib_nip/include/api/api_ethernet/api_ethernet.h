
/* api_ethernet.h -
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

#ifndef _API_ETHERNET_H_
#define _API_ETHERNET_H_

#include "api/nip_api.h"

#define NIP_ETHERNET_GET_MACADDR NIP_ETHERNET_BASE+1
#define NIP_ETHERNET_SET_MACADDR NIP_ETHERNET_BASE+2

struct api_get_mac
{
    int errid;
    char if_name[API_IFNAME_LEN];
    char mac[API_MAC_LEN];
};

struct api_set_mac
{
    int errid;
    int opcode;
    char if_name[API_IFNAME_LEN];
    char mac[32];
};

extern void nip_api_ethernet_register();

#ifdef MOD_INTF_ADD_FE_GE_NODE
extern int nip_eth_get_macaddr_linux(char *ifname, char *macaddr);
#else
extern int nip_eth_get_macaddr(int ifunit, char *macaddr);
extern int nip_eth_get_macaddr_linux(int ifunit, char *macaddr);
#endif
#ifdef MOD_INTF_ADD_FE_GE_NODE
extern int nip_eth_set_macaddr_linux(char *ifname, char *macaddr, int opcode);
#else
extern int nip_eth_set_macaddr(int ifunit, char *macaddr, int opcode);
extern int nip_eth_set_macaddr_linux(int ifunit, char *macaddr, int opcode);
#endif
extern void api_print_ethernet_errstr(int error_no);

#endif  /* _API_ETHERNET_H_ */

