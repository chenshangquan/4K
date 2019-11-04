#ifndef API_DHCPC_H_
#define API_DHCPC_H_

//#include "api/nip_api.h"
//#include "lib/if.h"

#define NIP_DHCPC_SET_ENABLE NIP_DHCPC_BASE + 1
#define NIP_DHCPC_SET_DISABLE NIP_DHCPC_BASE + 2
#define NIP_DHCPC_RENEW NIP_DHCPC_BASE + 3
#define NIP_DHCPC_GET_LEASEINFO NIP_DHCPC_BASE + 4
#define NIP_DHCPC_GETIP_CALLBACK_REG NIP_DHCPC_BASE + 5
#define NIP_DHCPC_GETIP_CALLBACK_UNREG NIP_DHCPC_BASE + 6
#define NIP_DHCPC_RMVIP_CALLBACK_REG NIP_DHCPC_BASE + 7
#define NIP_DHCPC_RMVIP_CALLBACK_UNREG NIP_DHCPC_BASE + 8

#define DHCPC_CALLBACK_ID				"dhcpc_callback_listen_fd"
#define DHCPC_ZIPC_ID				"dhcpc"

#define DHCPC_MSG_BASE 2000
#define DHCPC_GETIP_MSG DHCPC_MSG_BASE + 1
#define DHCPC_RMVIP_MSG DHCPC_MSG_BASE + 2

struct api_dhcpc_enable
{
    int enable;
    char ifname[8];
};

struct api_dhcpc_get_leaseinfo
{
    int err;
    char ifname[8];
    unsigned long ip;
    unsigned long mask;
    unsigned long gateway;
    int leasetime;
};

struct api_dhcpc_getip_callback
{
    int err;
    char ifname[8];
    unsigned long ip;
    unsigned long mask;
    unsigned long gateway;
};

struct api_dhcpc_rmvip_callback
{
    int err;
    char ifname[8];
    unsigned long ip;
    unsigned long mask;
    unsigned long gateway;
};

typedef int(*dhcpc_getip_callback)(struct api_dhcpc_getip_callback*);
typedef int(*dhcpc_rmvip_callback)(struct api_dhcpc_rmvip_callback*);

extern int nip_api_dhcpc_enable(int enable, char* ifname);
extern int nip_api_dhcpc_renew(char* ifname);

#endif  /* API_DHCPC_H_ */

