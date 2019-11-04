/* dns client header.
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

#ifndef _ZEBRA_DNSC_H
#define _ZEBRA_DNSC_H

#define DDNSC_CMD_ID         "ddnsccmd"                  /* zipc id for ddnsc cmd. */
#define ZMSG_ZEBRA_TO_DNSC     ZMSG_DNS_BASE+1
#define ZMSG_ZEBRA_TO_DNSC_CMD    ZMSG_DNS_BASE + 2
#define DNSC_TIMEOUT    3
#define DNSS_PORT       53

enum
{
    DDNSC_EXIT_THREAD_CMD = 0,
    DDNSC_IF_REG_CMD,
    DDNSC_NO_IF_REG_CMD,
    DDNSC_HOST_CHANGE_CMD,
    DDNSC_CFG_CHANGE,
    DDNSC_REG_RENEW,
    DDNSC_CFG_ERASE,
    DDNSC_CMD_TYPE_MAX
};

struct ddnsc_intf_cfg
{
    unsigned char ddnscEnable;
};

typedef struct ddnsc_change_config
{
    char domain[DNS_NAME_SIZE];
    ulong ser_ip;
}ddnsc_change_cfg;

struct ddnsc_msg
{
    int ddnsc_cmd_type;
    int ifunit;
    char ifname[DNSC_MAX_IFNAME];
    char newhost[DNS_MAX_HOSTNAME];
    ddnsc_change_cfg new_cfg;
};

void ddnsc_thread(void);
void ddnsc_cmd_message_send (int ddnsc_cmd_type, char *ifname, int ifunit, char *host, \
                                                                ddnsc_change_cfg *new_cfg, struct vty *vty);
int  ddns_config_interface(void* data, struct vty *vty);
int ddns_config_if_erase(void* data, struct interface *ifp);
void ddnsc_init();
#endif

