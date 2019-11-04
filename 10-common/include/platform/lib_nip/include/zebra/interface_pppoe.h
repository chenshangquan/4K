/*
 * Controller function.
 * Copyright (C) 2004 KEDACOM
 *
 * Version:	@(#)interface_pppoe.h	1.0.0	04/01/2005
 *
 * Authors:	Zhishuang Zhang
 *
 */

#ifndef _ZEBRA_INTERFACE_PPPOE_H
#define _ZEBRA_INTERFACE_PPPOE_H

#include "zebra/interface_ppp.h"

struct pppoe 
{
  int dev_fd;
  int kernel_unit;
  struct ppp_config_info ppp_info;
};

extern int pppoe_show (struct interface *ifp, struct vty *vty);
extern int pppoe_config (struct interface *ifp, struct vty *vty);
extern int encap_pppoe (struct interface *ifp);
extern int decap_pppoe (struct interface *ifp);
void zebra_pppoe_init (void);
int __pppoe_set_debug (struct interface *ifp, int debug_type);
int protocol_pppoe(struct interface *ifp, int pppoe_unit,struct vty *vty, int def);
int no_protocol_pppoe(struct interface *ifp,struct vty *vty);
int _no_zebra_protocol_pppoe_cmd(struct interface *ifp, int *errid);
int zebra_sendto_pppoe(struct interface *ifp, void * ptr,int len,unsigned long  type);
int pppoe_get_bind_by_eth(enum if_type iftype  ,int unit);
int pppoe_check(struct interface *e_ifp);

int  api_ppp_get_pppoe_protocol( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_pppoe_protocol( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_debug_pppoe( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_no_debug_pppoe( unsigned int type,void* recvbuf,int len,ZIPC_ID to);

#endif
