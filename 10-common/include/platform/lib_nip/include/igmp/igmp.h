
/*=============[ KDR SOFT  ]============
FILE		: igmp_cfg.c
DATE	: 06/04/03 
AUTHOR 	: zhuzhenming
MODULE	: IGMP	
VERSION	: MOD_IGMP_HOST_VER_0	
===================================*/

#ifndef _IGMP_H_
#define _IGMP_H_

#define IGMP_VERSION_DEFAULT 2

struct ip_mc_addr
{
    /* Attached interface. */
    struct interface *ifp;

    /* Address */
    ulong group;

    /* Flags for configuration. */
    u_char conf;
#define ZEBRA_IPMC_REAL         (1 << 0)
#define ZEBRA_IPMC_CONFIGURED   (1 << 1)

    /* states */
    int users;
    int reporter;
};

void ip_igmp_leave_group_all (struct interface *ifp, int del);
void ip_igmp_join_group_all (struct interface *ifp);
int igmp_set_version(struct interface *ifp, int version);

#endif      /*  _IGMP_H_ */
