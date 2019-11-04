/* policy map
   Copyright (C) 2005 kedacom Yuanyi Zhang

This file is part of GNU Zebra.

GNU Zebra is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 2, or (at your
option) any later version.

GNU Zebra is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Zebra; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#ifndef _POLICY_H
#define _POLICY_H

#include <qos/class.h>

struct policy_class_map;
struct policy_map;
struct queue_info;
struct queue_disc;

struct police_action
{
  int action;
  int para;
};

struct policy_class_map_stat
{
  int total_pkts;
  int total_bytes;
  int passed_pkts;
  int passed_bytes;
  int dropped_pkts;
  int dropped_bytes;
  int shapped_pkts;
  int shapped_bytes;
};

struct police_info
{
  int bit_rate;                        /* kbps */
  int burst_size;                      
  int excessburst_size;                /* not used at now */

  struct police_action conform_action; /* not used at now */
  struct police_action exceed_action;  
  struct police_action violate_action; /* not used at now */
};
  
struct policy_class_map
{
  struct class_map* c;                    /* reference to class_map */
  int ref;

  /* bandwidth information */
  int bandwidth;
  int priority;

  struct police_info pi;

  /* handle */
  int handle;

  struct policy_map * parent;             /* parent policy */
  struct policy_map * child;              /* not impleemnted */

  int (*doit)(struct policy_class_map*, char*, int);
  int (*undo)(struct policy_class_map*, char*, int);
  
  void (*config_write)(struct vty*, struct policy_class_map*);
  void (*config_erase)(struct policy_class_map*);
};

struct policy_class_map* policy_class_map_create(struct policy_map*, char*);
struct policy_class_map* policy_class_map_lookup(struct policy_map*, char*);
void policy_class_map_hold(struct policy_class_map*);
void policy_class_map_release(struct policy_class_map*);

struct policy_map_stat
{
  int reserved;
};

struct policy_map
{
  char name[MAXNAMSIZ];
  int ref;

  GList *class_list;

  
  struct policy_class_map* dft_class;

  struct queue_disc* qdisc;
  char queue_kind[16];

  int handle;

  int (*doit)(struct policy_map*, char*, int);
  int (*undo)(struct policy_map*, char*, int);
  int (*update)(struct policy_map*, char*, int);

  void (*add_class)(struct policy_map*, struct policy_class_map*);
  void (*remove_class)(struct policy_map*, struct policy_class_map*);

  void (*config_write)(struct vty* vty, struct policy_map*);
  void (*config_erase)(struct vty* vty, struct policy_map*);
};

struct policy_map* policy_map_create(char* name);
struct policy_map* policy_map_lookup(char* name);
void policy_map_release(struct policy_map* p);
void policy_map_hold(struct policy_map* p);
int policy_map_set_default_class(struct policy_map* p, char* name);

void policy_map_config_write(struct vty*);
void policy_map_config_erase();

void policy_map_update_all();
void policy_map_do_all();
void policy_map_undo_all();

void policy_map_if_delete(struct interface* ifp);
void policy_map_if_up(struct interface* ifp);
void policy_map_if_down(struct interface* ifp);
#endif
