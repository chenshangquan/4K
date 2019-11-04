/*
 * Header file for nip api lib
 * Copyright (C) 2005 kedacom
 * Author: Yuanyi Zhang
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2, or (at your
 * option) any later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __NIP_API_H
#define __NIP_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "api/lib/glib/glib.h"
#include "api/nip_api_comm.h"
#include "lib/nip_callback.h"
#include "event.h"
#include "api/api_ping/api_ping.h"
#include "api/api_ipconflict/api_ip_conflict_check.h"
#include "api/api_dataswitch/api_vc_ioctl.h"

/* include modules' header file here*/
#include "api/api_ethernet/api_ethernet.h"
#include "api/api_interface/api_interface.h"
#include "api/api_route/api_route.h"
#include "api/api_driver/api_driver.h"
#include "api/api_e1/api_e1.h"
#include "api/api_sntp/api_sntp.h"
#include "api/api_snmp/api_snmp.h"
#include "api/api_dhcpc/api_dhcpc.h"
#include "api/webserver/api_webserver.h"

/*suppose: for general module
* author:feixp
*/
#include "api/api_general/api_general.h"

#include "api/ppp/api_ppp.h"
#include "api/api_mp/api_mp.h"



extern int nip_api_init();

#ifdef __cplusplus
}
#endif

#endif
