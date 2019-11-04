/* Zebra daemon server header.
 * Copyright (C) 1997, 98 Kunihiro Ishiguro
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

#ifndef _ZEBRA_ZSERV_H
#define _ZEBRA_ZSERV_H

#include "lib/prefix.h"
#include "zebra/rib.h"
#include "lib/sockunion.h"
#include "lib/zclient.h"
#include "lib/zipc.h"

/* Default port information. */
#define ZEBRA_PORT                    2600
#define ZEBRA_VTY_PORT                23           
#define NIP_PROCESS_PROTECT_PORT 2601  //added by yml
#define ZEBRA_VTYSH_PATH              "/tmp/.zebra"
#define ZEBRA_SERV_PATH               "/tmp/.zserv"

#define ZSERVER_ID         "zserv"                  /* zipc id for zebra server. */
#define ZSERVER_MAX_REQ_THD_NUM     256             /* max number of thread to receive user request. */

/* ZMSG type base, Yuanyi Zhang 2005.2.23 16:18 */
#ifdef MOD_FTP_SERVER_VER_1
#else
#define ZMSG_FTPD_BASE          0x00001
#endif
#define ZMSG_DHCP_BASE         0x00002
#define ZMSG_NOTIFY_MC_BASE     0x00004
#define ZMSG_USER_PASS_BASE	0x00008
#define ZMSG_ACL_BASE   0x00010
#ifdef MOD_NAT_VER_0
#define ZMSG_NAT_BASE   0x00020
#endif
#define ZMSG_NIP_API_BASE 0x00030
/* zhuzhm :reference to linux_ipc_API_v1.0.doc */
#define ZMSG_ROUTER_BASE			0x490000
#define ZMSG_RIP_BASE					0x470000
/* end ZMSG type base */

/* yumilin :reference to linux_ipc_API_v1.0.doc */
#define ZMSG_DNS_BASE			0x610000
/* end ZMSG type base */

/* zhuzhm 051202 */
#define ZMSG_API_BASE			0x620000

#ifdef NIP_API_V35
#define ZMSG_PPP_BASE			0x660000
#endif
#ifdef MOD_MP_VER_1
#define ZMSG_MPAPI_BASE			0x670000
#endif
#define ZMSG_ZLOG_BASE			0x680000
struct zreq
{
  u_long type;
  int (*req_func)(struct zmsg*, ZIPC_ID, void*);
  void* user_data;
};


/* Client structure. */
struct zserv
{
  /* client zipc name(id) */
  ZIPC_ID id;

  /* zmsg type */
  int type;

  /* Input/output buffer to the client. */
  struct stream *ibuf;
  struct stream *obuf;

  /* default routing table this client munges */
  int rtm_table;

  /* This client's redistribute flag. */
  u_char redist[ZEBRA_ROUTE_MAX];

  /* Redistribute default route flag. */
  u_char redist_default;

  /* Interface information. */
  u_char ifinfo;
};

int zserv_req_register(u_long, int (*req)(struct zmsg*, ZIPC_ID, void*), void*);
void zserv_req_unregister(u_long);
void zserv_init(ZIPC_ID);

/* Prototypes. */
void zebra_init ();
void zebra_if_init ();
void hostinfo_get ();
void rib_init ();
void interface_list ();
int  kernel_init ();
void route_read ();
void rtadv_init ();
void zebra_snmp_init ();

int
zsend_interface_add (struct zserv *, struct interface *);
int
zsend_interface_delete (struct zserv *, struct interface *);

int
zsend_interface_address_add (struct zserv *, struct interface *,
			     struct connected *);

int
zsend_interface_address_delete (struct zserv *, struct interface *,
				struct connected *);

#ifdef ZHUZHM_MULTICAST_CHANGE
int zsend_interface_mc_change (struct zserv *, struct interface *, int);
#endif

int
zsend_interface_up (struct zserv *, struct interface *);

int
zsend_interface_down (struct zserv *, struct interface *);

int
zsend_ipv4_add (struct zserv *client, int type, int flags,
		struct prefix_ipv4 *p, struct in_addr *nexthop,
		unsigned int ifindex);

int
zsend_ipv4_delete (struct zserv *client, int type, int flags,
		   struct prefix_ipv4 *p, struct in_addr *nexthop,
		   unsigned int ifindex);

int
zsend_ipv4_add_multipath (struct zserv *, struct prefix *, struct rib *);

int
zsend_ipv4_delete_multipath (struct zserv *, struct prefix *, struct rib *);

#ifdef HAVE_IPV6
int
zsend_ipv6_add (struct zserv *client, int type, int flags,
		struct prefix_ipv6 *p, struct in6_addr *nexthop,
		unsigned int ifindex);

int
zsend_ipv6_delete (struct zserv *client, int type, int flags,
		   struct prefix_ipv6 *p, struct in6_addr *nexthop,
		   unsigned int ifindex);

int
zsend_ipv6_add_multipath (struct zserv *, struct prefix *, struct rib *);

int
zsend_ipv6_delete_multipath (struct zserv *, struct prefix *, struct rib *);

#endif /* HAVE_IPV6 */

void zebra_cmd_init();

extern void zebra_client_create (ZIPC_ID name, int type);
extern int zebra_client_read (struct zmsg* zmsg, ZIPC_ID from);

/* zhuzhm : 060109 */
#define CLIENT_LIST_LOCK 1

extern struct list* client_list;
extern ZLOCK_T *p_client_list_lock;

#endif /* _ZEBRA_ZEBRA_H */
