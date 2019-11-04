
/*=============[ KDR SOFT  ]============
FILE		: zclient_if.c
DATE	: 05/09/02 
AUTHOR 	: zhuzhenming
MODULE	: 	
VERSION	: zebra	
===================================*/

#ifndef _ZCLIENT_IF_H
#define _ZCLIENT_IF_H

#include "lib/linklist.h"
#include "lib/if.h"

/* Interface structure */
struct zclient_interface 
{
  /* Interface name. */
  char name[INTERFACE_NAMSIZ + 1];

  enum if_type iftype;
  unsigned int ifunit;

  /* Interface index. */
  unsigned int ifindex;

  /* Zebra internal interface status */
  u_char status;
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
  u_char hw_addr[INTERFACE_HWADDR_MAX];
  int hw_addr_len;
#endif /* HAVE_SOCKADDR_DL */

#ifdef ETHERNET_FUNCTION
	/* for ethernet cmd */
	struct eth_hw_info eth_info;
#endif
	
  /* interface bandwidth, kbits */
  unsigned int bandwidth;
  
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
};

/* Connected address structure. */
struct zclient_connected
{
  /* Attached interface. */
  struct zclient_interface *ifp;

  /* Flags for configuration. */
  u_char conf;
#define ZEBRA_IFC_REAL         (1 << 0)
#define ZEBRA_IFC_CONFIGURED   (1 << 1)

  /* Flags for connected address. */
  u_char flags;
#define ZEBRA_IFA_SECONDARY   (1 << 0)

  /* Address of connected network. */
  struct prefix *address;
  struct prefix *destination;

  /* Label for Linux 2.2.X and upper. */
  char *label;
};

/* One for each program.  This structure is needed to store hooks. */
struct zclient_if_master
{
  int (*if_new_hook) (struct zclient_interface *);
  int (*if_delete_hook) (struct zclient_interface *);
} ;

struct if_table
{
  /* Master list of interfaces. */
  struct list *iflist;
  
  /* Interface's IPv4 address reverse lookup table. */
  struct route_table *ifaddr_ipv4_table;
  /* struct route_table *ifaddr_ipv6_table; */

  /* One for each program.  This structure is needed to store hooks. */
  struct zclient_if_master zclient_if_master;
  
#ifdef ZCLIENT_ZHZS_ADD_INTF_LOCK
  ZLOCK_T iflist_lock;
  ZLOCK_T *p_iflist_lock;
#endif
};

/* Prototypes. */
struct zclient_interface *zclient_if_new (void);
struct zclient_interface *zclient_if_create (struct if_table *if_table, char *name);
struct zclient_interface *zclient_if_lookup_by_index (struct if_table *if_table, unsigned int);
struct zclient_interface *zclient_if_lookup_by_name (struct if_table *, char *);
struct zclient_interface *zclient_if_lookup_by_type_and_unit (
  struct if_table *if_table, enum if_type, unsigned int);
struct zclient_interface *zclient_if_lookup_exact_address (struct if_table *, struct in_addr);
struct zclient_interface *zclient_if_lookup_address (struct if_table *, struct in_addr);
struct prefix *zclient_connected_ipaddr_lookup(struct if_table *, struct in_addr);
struct zclient_connected *zclient_connected_ipaddr_match(struct zclient_interface *ifp, struct prefix *addr);
struct zclient_interface *zclient_if_get_by_name (struct if_table *, char *);
void zclient_if_delete (struct if_table *, struct zclient_interface *);
#ifdef ZCLIENT_ZHZS_ADD_INTF_LOCK
#define zclient_if_unlock(if_table, ifp) zclient_if_delete (if_table, ifp)
#endif
int zclient_if_is_up (struct zclient_interface *);
int zclient_if_is_loopback (struct zclient_interface *);
int zclient_if_is_broadcast (struct zclient_interface *);
int zclient_if_is_pointopoint (struct zclient_interface *);
int zclient_if_is_multicast (struct zclient_interface *);
void zclient_if_add_hook (struct if_table *, int, int (*)(struct zclient_interface *));
struct if_table *zclient_if_init ();
void zclient_if_clean (struct if_table *if_table);
void zclient_if_dump_all (struct if_table *);
char *zclient_ifindex2ifname (struct if_table *if_table, unsigned int);

/* Connected address functions. */
struct zclient_connected *zclient_connected_new ();
void zclient_connected_free (struct zclient_connected *);
void zclient_connected_add (struct zclient_interface *, struct zclient_connected *);
struct zclient_connected  *zclient_connected_delete_by_prefix (struct zclient_interface *, struct prefix *);
int zclient_ifc_pointopoint (struct zclient_connected *);
/* for LTP test */
int zclient_connected_same_prefix (struct prefix *p1, struct prefix *p2);

#ifndef HAVE_IF_NAMETOINDEX
unsigned int zclient_if_nametoindex (struct if_table *, const char *);
#endif
#ifndef HAVE_IF_INDEXTONAME
char *zclient_if_indextoname (struct if_table *, unsigned int, char *);
#endif

#endif /* _ZCLIENT_IF_H */

