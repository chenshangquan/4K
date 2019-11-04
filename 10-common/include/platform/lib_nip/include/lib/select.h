/* Zebra select library.
 * Copyright (C) 2005 kedacom
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
 * along with GNU Zebra; see the file COPYING.  If not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, 
 * Boston, MA 02111-1307, USA.  
 */

#ifndef _ZEBRA_SELECT_H
#define _ZEBRA_SELECT_H

#define MAX_SEL_ITEM_NUM 32

typedef enum _select_priority
{
  HI_PRI = 1,
  MID_PRI = 2,
  LO_PRI = 3,
}select_priority;

#define prior_foreach(p) \
        for(p = HI_PRI; p <= LO_PRI; p++)

typedef struct _select_item
{
  int fd;
  select_priority prior;
  int (*proc)(int fd);
}select_item;

int select_item_add(int fd, select_priority prior, int (*proc)(int fd));
void select_start();

#endif
