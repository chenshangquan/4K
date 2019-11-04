/* NIP NTP API header
   Copyright (C) 2006 Kedacom
   Author: Yuanyi Zhang

This file is part of GNU Zebra.

GNU Zebra is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

GNU Zebra is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Zebra; see the file COPYING.  If not, write to the Free
Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

#ifndef __NIP_SNMP_H
#define __NIP_SNMP_H

#ifdef __cplusplus
extern "C" {
#endif

enum
{
	SNMP_V1 = 0,
	SNMP_V2C,
	SNMP_V3,
};

int snmp_config_server_enable() ;
int snmp_config_server_no_enable();
int snmp_config_community_info_add_interproc(char *, char *, unsigned int);
int snmp_config_community_info_del_interproc(char *);
int snmp_config_view_info_add_interproc(char *,	u_char,	char *);
int snmp_config_view_info_del_interproc(char *,	char *);
int snmp_config_group_info_add_interproc(char *, u_char, u_char, char *, char *, char *, u_short);
int snmp_config_group_info_del_interproc(char *, u_char);
int snmp_config_user_info_add_interproc(char *,	u_char,	u_char,	char *,	char *,	char *,	unsigned int);
int snmp_config_user_info_del_interproc(char *);
int snmp_config_traphost_info_add_interproc(char *,	char *,	u_short,u_char,	u_char);
int snmp_config_traphost_info_del_interproc(char *, u_short);

#ifdef __cplusplus
}
#endif

#endif
