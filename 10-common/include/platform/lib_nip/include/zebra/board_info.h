/* Interface function header.
 * Copyright (C) 2004 KEDACOM
 *
 * Version:	@(#)board_info.h	1.0.0	01/29/05
 *
 * Authors:	Zhishuang Zhang
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

#ifndef _ZEBRA_BOARD_INFO_H
#define _ZEBRA_BOARD_INFO_H

#include <lib/zebra.h>

/* Structures. */
struct board_info 
{
  int eth_num;
  int eth_support;
#ifdef MOD_INTF_ADD_FE_GE_NODE
  int feth_num;
  int feth_support;
  int geth_num;
  int geth_support;
#endif
#ifdef ZHZS_ADD_NEW_INTF_TYPE
#error "HERE, adding new interface type"
#endif
  int v35_num;
  int v35_support;
  int e1_num;
  int e1_support; 
  int channel_group_num;
  char timeslots_range[20];

  int ser_num;
  int ser_support;
  
  long memory_size;
  long flash_size;
  long cpu_freq;
  long cpm_freq;
  long bus_freq;
};

/* Extern variables */
extern struct board_info board_info;

/* Prototypes. */
extern void board_info_init (void);

#endif /* _ZEBRA_BOARD_INFO_H */

