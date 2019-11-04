/* Interface function header.
 * Copyright (C) 2004 KEDACOM
 *
 * This file is programed by zhangzhishuang.
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

#ifndef _ZEBRA_GLOBAL_INFO_H
#define _ZEBRA_GLOBAL_INFO_H

struct ipv4_info
{
#ifdef ZHZS_ADD_CFG_CMD_MAXIMUM_PATHS
  int maximum_paths;
#endif
#ifdef ZHUZHM_MULTIPATH_SELECT
  int multipath_select;
#endif
};

#ifdef ZHZS_ADD_CFG_CMD_MAXIMUM_PATHS
#define MAXIMUM_PATHS_DEFAULT 6
#endif
#ifdef ZHUZHM_MULTIPATH_SELECT
#define MULTIPATH_SELECT_DEFAULT 0
#endif

/* */
extern struct ipv4_info ipv4_info;

/* Prototypes */
void global_info_init (void);

#endif /* _ZEBRA_GLOBAL_INFO_H */
