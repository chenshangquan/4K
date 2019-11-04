/* Interface related header.
   Copyright (C) 1997, 98, 99 Kunihiro Ishiguro

This file is part of GNU Zebra.

GNU Zebra is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 2, or (at your
option) any later version.

GNU Zebra is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Zebra; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#ifndef _ZEBRA_IF_H
#define _ZEBRA_IF_H

#include "lib/zebra.h"
#include "lib/linklist.h"
#include "lib/aligned.h"
/*
  Interface name length.

   Linux define value in /usr/include/linux/if.h.
   #define IFNAMSIZ        16

   FreeBSD define value in /usr/include/net/if.h.
   #define IFNAMSIZ        16
*/
/* MOD MP */
#define ARPHRD_VIRTUAL 803
#define ARPHRD_SUB_VLAN 804
#define INTERFACE_NAMSIZ      20
#define INTERFACE_HWADDR_MAX  20

#define HW_LINE_DOWN		0
#define HW_LINE_UP			1

/* Internal If indexes start at 0xFFFFFFFF and go down to 1 greater
   than this */
#define IFINDEX_INTERNBASE 0x80000000

struct interface;
typedef int (*IF_FOREACH_FUNCPTR)(struct interface *ifp, void *param);

/* Must start from 0 */
enum if_type {
  IFT_ETH = 0, /* ethernet */
#ifdef MOD_INTF_ADD_FE_GE_NODE
  IFT_FETH, /* fastethernet */
  IFT_GETH, /* gigabitethernet */
#endif
  IFT_SER,     /* serial */
  IFT_LO,      /* loopback */
#ifdef ZHZS_ADD_VIRTUAL_INTF
  IFT_VIR,     /* virtual */
#endif
#ifdef SUB_VLAN_ZHANKA
  IFT_SUB_VLAN_ETH,    /* sub vlan */  
  IFT_SUB_VLAN_FETH,
  IFT_SUB_VLAN_GETH,
#endif
#ifdef ZHZS_ADD_NEW_INTF_TYPE
#error "HERE, adding new interface type"
#endif
  IFT_MAX
};
struct if_type_str {
  enum if_type type;
  char *kernel;
  char *zebra;
};

#ifdef HAVE_PROC_NET_DEV
struct if_stats
{
  unsigned long rx_packets;   /* total packets received       */
  unsigned long tx_packets;   /* total packets transmitted    */
  unsigned long rx_bytes;     /* total bytes received         */
  unsigned long tx_bytes;     /* total bytes transmitted      */
  unsigned long rx_errors;    /* bad packets received         */
  unsigned long tx_errors;    /* packet transmit problems     */
  unsigned long rx_dropped;   /* no space in linux buffers    */
  unsigned long tx_dropped;   /* no space available in linux  */
  unsigned long rx_multicast; /* multicast packets received   */
  unsigned long rx_compressed;
  unsigned long tx_compressed;
  unsigned long collisions;

  /* detailed rx_errors: */
  unsigned long rx_length_errors;
  unsigned long rx_over_errors;       /* receiver ring buff overflow  */
  unsigned long rx_crc_errors;        /* recved pkt with crc error    */
  unsigned long rx_frame_errors;      /* recv'd frame alignment error */
  unsigned long rx_fifo_errors;       /* recv'r fifo overrun          */
  unsigned long rx_missed_errors;     /* receiver missed packet     */
  /* detailed tx_errors */
  unsigned long tx_aborted_errors;
  unsigned long tx_carrier_errors;
  unsigned long tx_fifo_errors;
  unsigned long tx_heartbeat_errors;
  unsigned long tx_window_errors;
/* MOD MP */

	unsigned long rx_mppackets;			/* recved mp frame */
	unsigned long tx_mppackets;			/* trans mp frame */
	unsigned long rx_mpbytes;				/* recved mp bytes */
	unsigned long tx_mpbytes;				/* trans mp bytes */
	unsigned long rx_mperrors;			/* recved mp errors */
	unsigned long tx_mperrors;			/* trans mp errors */
	unsigned long rx_repackets;			/* recved mp repacket */
	unsigned long rx_repacketserrors;		/* recved mp repacket errors */
	unsigned long tx_depackets;
	unsigned long tx_depacketserrors;
};
#endif /* HAVE_PROC_NET_DEV */

#ifdef ETHERNET_FUNCTION
struct eth_hw_info {
	/* speed & duplex mode */
	int speed;
	int duplex;

	unsigned long flags;
};
#endif

/* Interface structure */
struct interface
{
  /* Interface name. */
  char name[INTERFACE_NAMSIZ + 1];

  int refcnt;
  ZLOCK_T lock;

  enum if_type iftype;
  unsigned int ifunit;

  /* Interface index. */
  unsigned int ifindex;

  /* Zebra internal interface status */
  volatile u_char status;
#define ZEBRA_INTERFACE_ACTIVE     (1 << 0)
#define ZEBRA_INTERFACE_SUB        (1 << 1)
#ifdef ZHZS_PERMIT_DEL_INTF
#define ZEBRA_INTERFACE_CAN_DELETED (1 << 2)
#endif

  /* Interface flags. */
  unsigned long flags;

  /* Interface metric */
  int metric;

  /* Interface MTU. */
  int mtu;

  /* Hardware address. */
#ifdef HAVE_SOCKADDR_DL
  struct sockaddr_dl sdl;
#else
  unsigned short hw_type_def;
  unsigned short hw_type;
#ifndef MOD_PPP_VER_4
  u_char hw_addr[INTERFACE_HWADDR_MAX];
#else
  u_char hw_addr[INTERFACE_HWADDR_MAX] aligned_def;
#endif
  int hw_addr_len;
#endif /* HAVE_SOCKADDR_DL */

#ifdef ETHERNET_FUNCTION
	/* for ethernet cmd */
	struct eth_hw_info eth_info;
#endif

  /* interface bandwidth, kbits */
  unsigned int bandwidth;
 int set_bandwidth_flag;

  /* description of the interface. */
  char *desc;

#ifdef ZHZS_UNUSED
  /* Distribute list. */
  void *distribute_in;
  void *distribute_out;
#endif /* ZHZS_UNUSED */

  /* Connected address list. */
  struct list* connected;

  /* Daemon specific interface data pointer. */
  void *info;

  /* Statistics fileds. */
#ifdef HAVE_PROC_NET_DEV
  struct if_stats stats;
#endif /* HAVE_PROC_NET_DEV */
#ifdef HAVE_NET_RT_IFLIST
  struct if_data stats;
#endif /* HAVE_NET_RT_IFLIST */
#ifdef MOD_QOS_VER_1
  struct
  {
    void *policy_map_in;
    int  parent_in;
    void *policy_map_out;
    int parent_out;
  }qos_info;
#endif /* HAVE_NET_RT_IFLIST */

#ifdef MOD_IGMP_HOST_VER_0
  struct list* ip_mc_addr;
  int igmp_version;
#endif
	int line_status;	/* 0 means line down, 1 means line up ,-1 other*/

	unsigned long if_queue_len;
	unsigned long if_queue_len_def;
};


/* Connected address structure. */
struct connected
{
  /* Attached interface. */
  struct interface *ifp;

  /* Flags for configuration. */
  volatile u_char conf;
#define ZEBRA_IFC_REAL         (1 << 0)
#define ZEBRA_IFC_CONFIGURED   (1 << 1)

/* this flag means the ip add should not be set by zebra*/
#define ZEBRA_IFC_UNIQUE	(1<<2)


  /* Flags for connected address. */
  u_char flags;
#define ZEBRA_IFA_SECONDARY   (1 << 0)

  /* Address of connected network. */
  struct prefix *address;
  struct prefix *destination;

  /* Label for Linux 2.2.X and upper. */
  char *label;
  
  u_char config_prefixlen;
  
};

/* Interface hook sort. */
#define IF_NEW_HOOK   0
#define IF_DELETE_HOOK 1

/* There are some interface flags which are only supported by some
   operating system. */

#ifndef IFF_NOTRAILERS
#define IFF_NOTRAILERS 0x0
#endif /* IFF_NOTRAILERS */
#ifndef IFF_OACTIVE
#define IFF_OACTIVE 0x0
#endif /* IFF_OACTIVE */
#ifndef IFF_SIMPLEX
#define IFF_SIMPLEX 0x0
#endif /* IFF_SIMPLEX */
#ifndef IFF_LINK0
#define IFF_LINK0 0x0
#endif /* IFF_LINK0 */
#ifndef IFF_LINK1
#define IFF_LINK1 0x0
#endif /* IFF_LINK1 */
#ifndef IFF_LINK2
#define IFF_LINK2 0x0
#endif /* IFF_LINK2 */

/* Inline functions. */
static inline struct if_type_str *get_if_type_str (enum if_type type)
{
  extern struct if_type_str if_type_strs[];
  return &if_type_strs[type];
}

static inline int if_is_type(struct interface *ifp, enum if_type if_type)
{
	return (ifp->iftype == if_type) ? 1 : 0;
}

/* Prototypes. */
#define IFLOCK_WAIT(ifp) \
do{\
	if_wait_iflist();\
	ZLOCK_WAIT(&(ifp)->lock);\
}while(0);

#define IFLOCK_POST(ifp) \
do{\
	ZLOCK_POST(&(ifp)->lock);\
	if_post_iflist();\
}while(0);

enum if_type if_get_type_by_match_zebratype (char *ztype);
enum if_type if_get_type_by_lookup_zebratype (char *ztype);
int if_get_type_and_unit_by_name (char *, enum if_type *, int *);

struct interface *if_new (void);
struct interface *if_create (char *name);
struct interface *if_lookup_by_index (unsigned int);
struct interface *if_lookup_by_name (char *);
struct interface *if_lookup_by_type_and_unit (enum if_type, unsigned int);
char * if_get_name_by_lookup_iftype (int type);
struct interface *if_lookup_exact_address (struct in_addr add);
struct interface *if_lookup_address (struct in_addr add);
struct interface *if_get_by_name (char *);
void if_delete (struct interface *);
void if_unlock (struct interface *ifp);
int if_has_address (struct interface *);
int if_is_up (struct interface *);
int if_is_loopback (struct interface *);
int if_is_broadcast (struct interface *);
int if_is_pointopoint (struct interface *);
int if_is_multicast (struct interface *);
void if_add_hook (int, int (*)(struct interface *));
void if_init ();
void if_dump_all ();
#if 0
char *ifindex2ifname (unsigned int);
#endif

/* Connected address functions. */
struct connected *connected_new ();
void connected_free (struct connected *);
void connected_add (struct interface *, struct connected *);
struct connected  *connected_delete_by_prefix (struct interface *, struct prefix *);
int ifc_pointopoint (struct connected *);

#ifndef HAVE_IF_NAMETOINDEX
unsigned int if_nametoindex (const char *);
#endif
#ifndef HAVE_IF_INDEXTONAME
char *if_indextoname (unsigned int, char *);
#endif
int if_foreach (IF_FOREACH_FUNCPTR func, void *param);
int if_foreach_nolock (IF_FOREACH_FUNCPTR func, void *param);

void _no_interface_desc_cmd(struct interface *ifp);
char *is_if_name_vlan(char *name);

void if_wait_iflist();
void if_post_iflist();

#endif /* _ZEBRA_IF_H */
