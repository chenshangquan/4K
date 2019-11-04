/* Interface function header.
 * Copyright (C) 1999 Kunihiro Ishiguro
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "lib/aligned.h"
#include <lib/zebra.h>
#include"lib/zipc.h"
#include "lib/vty.h"
#include <lib/if.h>
#include "zebra/hw_type.h"
#ifndef ZHZS_ADD_VIRTUAL_INTF_MP	/* MOD MP */
#define ARPHRD_VIRTUAL 803
#endif
#ifndef ARPHRD_SUB_VLAN
#define ARPHRD_SUB_VLAN 804
#endif /*ARPHRD_SUB_VLAN*/

/* Exist specific type interface ? */
#define IF_EXIST_ETH     (board_info.eth_num > 0)
#ifdef MOD_INTF_ADD_FE_GE_NODE
#define IF_EXIST_FETH     (board_info.feth_num > 0)
#define IF_EXIST_GETH     (board_info.geth_num > 0)
#endif
#define IF_EXIST_SER_V35 (board_info.v35_num > 0)
#define IF_EXIST_SER_E1  (board_info.e1_num > 0)
#ifdef ZHUZHM_CFG_LOOPBACK
#define IF_EXIST_LO      (1)
#else
#define IF_EXIST_LO      (0)
#endif
#ifdef ZHZS_ADD_VIRTUAL_INTF
#ifdef MOD_INTF_ADD_FE_GE_NODE
#define IF_EXIST_VIR     (IF_EXIST_ETH || IF_EXIST_FETH || IF_EXIST_GETH)
#else
#define IF_EXIST_VIR     (IF_EXIST_ETH)
#endif
#define IF_EXIST_VIR_MULTILINK  (IF_EXIST_SER_E1 || IF_EXIST_SER_V35)
#endif
#ifdef ZHZS_ADD_NEW_INTF_TYPE
#error "HERE, adding new interface type"
#endif

/* Interface number lower limit */
#define IF_NUMBER_LOWER_LIMIT_ETH      0 /* ethernet */
#ifdef MOD_INTF_ADD_FE_GE_NODE
#define IF_NUMBER_LOWER_LIMIT_FETH      0 /* fastethernet */
#define IF_NUMBER_LOWER_LIMIT_GETH      0 /* gigabitethernet */
#endif
#define IF_NUMBER_LOWER_LIMIT_SER_V35  0 /* V35 serial */
#define IF_NUMBER_LOWER_LIMIT_SER_E1  16 /* E1 serail */
#define IF_NUMBER_LOWER_LIMIT_LO       1 /* loopback */
#ifdef ZHZS_ADD_VIRTUAL_INTF
#define IF_NUMBER_LOWER_LIMIT_VIR_MULTILINK  0 /* multilink virtual */
#define IF_NUMBER_LOWER_LIMIT_VIR     16 /* pppoe virtual */
#endif
#ifdef ZHZS_ADD_NEW_INTF_TYPE
#error "HERE, adding new interface type"
#endif

/* Interface secondary ip address max number added by zhanka */
#define INTERFACE_IP_ADDR_SECOND_MAX 15

/* Interface number upper limit */
#define IF_NUMBER_UPPER_LIMIT_ETH \
  (board_info.eth_num - 1 - IF_NUMBER_LOWER_LIMIT_ETH)
#ifdef MOD_INTF_ADD_FE_GE_NODE
#define IF_NUMBER_UPPER_LIMIT_FETH \
  (board_info.feth_num - 1 - IF_NUMBER_LOWER_LIMIT_FETH)
#define IF_NUMBER_UPPER_LIMIT_GETH \
  (board_info.geth_num - 1 - IF_NUMBER_LOWER_LIMIT_GETH)
#endif
#define IF_NUMBER_UPPER_LIMIT_SER_V35 \
  (board_info.v35_num - 1 - IF_NUMBER_LOWER_LIMIT_SER_V35)
#define IF_NUMBER_UPPER_LIMIT_SER_E1  63 /* E1 serail */
#define IF_NUMBER_UPPER_LIMIT_LO      15 /* loopback */
#ifdef ZHZS_ADD_VIRTUAL_INTF
#define IF_NUMBER_UPPER_LIMIT_VIR_MULTILINK     (IF_NUMBER_LOWER_LIMIT_VIR-1) /* multilink virtual */
#define IF_NUMBER_UPPER_LIMIT_VIR     23 /* pppoe virtual */
#endif
#ifdef ZHZS_ADD_NEW_INTF_TYPE
#error "HERE, adding new interface type"
#endif

/* For interface multicast configuration. */
#define IF_ZEBRA_MULTICAST_UNSPEC 0
#define IF_ZEBRA_MULTICAST_ON     1
#define IF_ZEBRA_MULTICAST_OFF    2

/* For interface shutdown configuration. */
#define IF_ZEBRA_SHUTDOWN_UNSPEC 0
#define IF_ZEBRA_SHUTDOWN_ON     1
#define IF_ZEBRA_SHUTDOWN_OFF    2

/* Router advertisement feature. */
#if (defined(LINUX_IPV6) && (defined(__GLIBC__) && __GLIBC__ >= 2 && __GLIBC_MINOR__ >= 1)) || defined(KAME)
#define RTADV
#endif

#ifdef RTADV
/* Router advertisement parameter.  From RFC2461. */
struct rtadvconf
{
  /* A flag indicating whether or not the router sends periodic Router
     Advertisements and responds to Router Solicitations.
     Default: FALSE */
  int AdvSendAdvertisements;

  /* The maximum time allowed between sending unsolicited multicast
     Router Advertisements from the interface, in seconds.  MUST be no
     less than 4 seconds and no greater than 1800 seconds.

     Default: 600 seconds */
  int MaxRtrAdvInterval;
#define RTADV_MAX_RTR_ADV_INTERVAL 600

  /* The minimum time allowed between sending unsolicited multicast
     Router Advertisements from the interface, in seconds.  MUST be no
     less than 3 seconds and no greater than .75 * MaxRtrAdvInterval.

     Default: 0.33 * MaxRtrAdvInterval */
  int MinRtrAdvInterval;
#define RTADV_MIN_RTR_ADV_INTERVAL (0.33 * RTADV_MAX_RTR_ADV_INTERVAL)

  /* Unsolicited Router Advertisements' interval timer. */
  int AdvIntervalTimer;

  /* The TRUE/FALSE value to be placed in the "Managed address
     configuration" flag field in the Router Advertisement.  See
     [ADDRCONF].

     Default: FALSE */
  int AdvManagedFlag;


  /* The TRUE/FALSE value to be placed in the "Other stateful
     configuration" flag field in the Router Advertisement.  See
     [ADDRCONF].

     Default: FALSE */
  int AdvOtherConfigFlag;

  /* The value to be placed in MTU options sent by the router.  A
     value of zero indicates that no MTU options are sent.

     Default: 0 */
  int AdvLinkMTU;


  /* The value to be placed in the Reachable Time field in the Router
     Advertisement messages sent by the router.  The value zero means
     unspecified (by this router).  MUST be no greater than 3,600,000
     milliseconds (1 hour).

     Default: 0 */
  u_int32_t AdvReachableTime;
#define RTADV_MAX_REACHABLE_TIME 3600000


  /* The value to be placed in the Retrans Timer field in the Router
     Advertisement messages sent by the router.  The value zero means
     unspecified (by this router).

     Default: 0 */
  int AdvRetransTimer;

  /* The default value to be placed in the Cur Hop Limit field in the
     Router Advertisement messages sent by the router.  The value
     should be set to that current diameter of the Internet.  The
     value zero means unspecified (by this router).

     Default: The value specified in the "Assigned Numbers" RFC
     [ASSIGNED] that was in effect at the time of implementation. */
  int AdvCurHopLimit;

  /* The value to be placed in the Router Lifetime field of Router
     Advertisements sent from the interface, in seconds.  MUST be
     either zero or between MaxRtrAdvInterval and 9000 seconds.  A
     value of zero indicates that the router is not to be used as a
     default router.

     Default: 3 * MaxRtrAdvInterval */
  int AdvDefaultLifetime;
#define RTADV_ADV_DEFAULT_LIFETIME (3 * RTADV_MAX_RTR_ADV_INTERVAL)


  /* A list of prefixes to be placed in Prefix Information options in
     Router Advertisement messages sent from the interface.

     Default: all prefixes that the router advertises via routing
     protocols as being on-link for the interface from which the
     advertisement is sent. The link-local prefix SHOULD NOT be
     included in the list of advertised prefixes. */
  list AdvPrefixList;
};

#endif /* RTADV */

struct zebra_if_link
{
  struct hwtype *hwt;
  char hard_devname[32] aligned_def;
  void *priv;
 };

enum zebra_if_app_type
{
#ifdef MOD_DHCPC_VER_0
  ZIA_TYPE_DHCPC,
#endif  
#ifdef MOD_ACL_VER_0
  ZIA_TYPE_ACL,
#endif    
#ifdef MOD_NAT_VER_0
  ZIA_TYPE_NAT,
#endif    
  ZIA_TYPE_RIP,
  ZIA_TYPE_OSPF,
#ifdef MOD_DDNSC_VER_0
 ZIA_TYPE_DDNSC
#endif 
};

struct zebra_if_app
{
  enum zebra_if_app_type type;
  int (*config)(void *data, struct vty *vty);
  int (*erase)(void *data, struct interface *ifp);
  void *priv;
};

/* `zebra' daemon local interface structure. */
struct zebra_if
{
  /* Shutdown configuration. */
  u_char shutdown;

  /* Multicast configuration. */
  u_char multicast;

  /* Router advertise configuration. */
  u_char rtadv_enable;
  /* IP address type, ZEBRA_IF_ADDR_* */
  u_char ip_addr_type;
#define ZEBRA_IF_ADDR_NONE    0  /* ex. no config             */
#define ZEBRA_IF_ADDR_MANUAL  1  /* ex. ip address 1.1.1.1/8  */
#define ZEBRA_IF_ADDR_DHCP    2  /* ex. ip address dhcp       */
#define ZEBRA_IF_ADDR_NEGO    3  /* ex. ip address negotiated */

  struct zebra_if_link link;

  struct list* apps;     /* struct zebra_if_app */

#ifdef ZHZS_UNUSED
  /* Interface's address. */
  struct list* address;
#endif /* ZHZS_UNUSED */

#ifdef RTADV
  struct rtadvconf rtadv;
#endif /* RTADV */
  int (* zebra_sendto)(struct interface *ifp ,void *ptr, int len, unsigned long type);
};

extern struct cmd_element zebra_interface_cmd;
extern struct cmd_element no_zebra_interface_cmd;
#ifdef V35_PPPoE_ZHANKA
extern struct cmd_element zebra_interface_vir_cmd;
extern struct cmd_element no_zebra_interface_vir_cmd;
#endif /* V35_PPPoE_ZHANKA */
extern int get_dev_name(char *dev_name, int serial);
extern int dev_exist(int serial);
void if_delete_update (struct interface *ifp);
void if_add_update (struct interface *ifp);
#ifdef ZHUZHM_MULTICAST_CHANGE
void if_multicast_change (struct interface *, int);
#endif
void if_up (struct interface *);
void if_down (struct interface *);
void if_refresh (struct interface *);
void zebra_interface_up_update (struct interface *ifp);
void zebra_interface_down_update (struct interface *ifp);

int if_node_add (struct vty *vty, struct cmd_element *cmd, 
  enum if_type type, int unit);
int if_node_add_and_return (struct vty *vty, 
  struct cmd_element *new_cmd, enum if_type new_type, int new_unit,
  struct cmd_element *old_cmd, enum if_type old_type, int old_unit);
int if_force_delete (int (*func)(enum if_type, int, int *), enum if_type type, int unit, int *errid);

char *zebra_get_if_name (char *name, enum if_type iftype, int ifunit);
char *zebra_get_if_show_name (char *name, enum if_type iftype, unsigned int ifunit, int with_space);
char *zebra_get_if_show_name_by_ifp (char *name, struct interface *ifp, int with_space);

int set_ipaddr_func (struct interface *ifp, struct connected *ifc);
int clear_ipaddr_func (struct interface *ifp, struct connected *ifc);
int shutdown_if_func(struct interface *ifp);
int no_shutdown_if_func(struct interface *ifp);

#ifdef HAVE_PROC_NET_DEV
int ifstat_update_proc ();
#endif /* HAVE_PROC_NET_DEV */
#ifdef HAVE_NET_RT_IFLIST
void ifstat_update_sysctl ();

#endif /* HAVE_NET_RT_IFLIST */
#ifdef HAVE_PROC_NET_DEV
int interface_list_proc ();
#endif /* HAVE_PROC_NET_DEV */
#ifdef HAVE_PROC_NET_IF_INET6
int ifaddr_proc_ipv6 ();
#endif /* HAVE_PROC_NET_IF_INET6 */

#ifdef BSDI
int if_kvm_get_mtu (struct interface *);
#endif /* BSDI */

#ifdef SUB_VLAN_ZHANKA
extern struct cmd_element zebra_interface_sub_vlan_cmd;
extern struct cmd_element no_zebra_interface_sub_vlan_cmd;
int _zebra_interface_vlan_cmd (enum if_type iftype, 
                           int ifunit, int sub_no, int *errid);
int _no_zebra_interface_vlan_cmd (enum if_type iftype, 
	          			   int ifunit, int sub_no, int *errid);
#ifdef ETH_FETH_ZHANKA
extern struct cmd_element zebra_interface_sub_vlan_eth_cmd;
extern struct cmd_element zebra_interface_sub_vlan_geth_cmd;
#endif /* ETH_FETH_ZHANKA */
#endif /* SUB_VLAN_ZHANKA */
/* zhuzhm : for api begin --------------------------------------------------*/
int ip_address_install (struct interface *ifp, char *addr_str, char *peer_str, 
                        char *label, int secondary, int *errid);
int ip_address_uninstall (struct interface *ifp, char *addr_str, char *peer_str, 
                                char *label, int secondry, int *errid);
void ip_address_uninstall_all (struct interface *ifp, int *errid);

extern void print_interface_errstr(struct vty *vty, int error_no);

int __if_config_erase (struct interface *ifp, void *param);
int _no_zebra_interface_cmd (enum if_type iftype, int ifunit, int *errid);
void print_del_if_error(struct vty *vty, char *ifname, int errid);
int _zebra_interface_cmd (enum if_type iftype, int ifunit,int *errid);
/* zhuzhm : for api end --------------------------------------------------*/

/* if app begin --------------------------------------------------------------*/
inline struct zebra_if_app *if_app_new ();
struct zebra_if_app *if_app_create (struct zebra_if *if_data);
void if_app_delete (struct zebra_if *if_data, struct zebra_if_app *ap);
void if_app_list_del (void *ap);
void if_app_delete_all (struct interface *ifp);
struct zebra_if_app *if_app_lookup (struct zebra_if *if_data, enum zebra_if_app_type type);
struct zebra_if_app *if_app_get (struct zebra_if *if_data, enum zebra_if_app_type type);
int if_app_set_config_func (struct zebra_if_app *ap, int (*config)(void *, struct vty *));
int if_app_set_erase_func (struct zebra_if_app *ap, int (*erase)(void *, struct interface *));
#ifdef NIP_API_PPP
int set_interface_encapt(struct interface *ifp,  char *paramter,int isno);
#endif
/* if app end ----------------------------------------------------------------*/

void create_thread(int *ppp_key);
void ip_address_reinstall_all (struct interface *ifp);
void _no_bandwidth_if_cmd(struct interface *ifp);
void  show_line_status(struct interface *ifp, struct vty* vty);
void if_line_status_check(struct interface *ifp);

#endif  /* _INTERFACE_H_ */

