/* Queue information for QoS
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

#ifndef __QUEUE_H
#define __QUEUE_H

extern int queue_debug;

enum {
  PQ_SET_DEFAULT,
  PQ_ADD_RULE,
  PQ_DEL_RULE,
  PQ_SET_LIMITS,
  CQ_SET_DEFAULT,
  CQ_ADD_RULE,
  CQ_DEL_RULE,
  CQ_SET_LIMITS,
  CQ_SET_BYTE_COUNT,
  FQ_SET_LIMIT,
};

enum {
  PRIORITY_QUEUE = 0,
  CUSTOM_QUEUE = 1,
  FIFO_QUEUE = 2,
  MAX_QUEUE_TYPE = 3,
};

enum {
  HIGH = 0,
  MEDIUM = 1,
  NORMAL = 2,
  LOW = 3,
};

struct queue_disc_rule
{
  int   number;                /* queue number packet will enqueue */
  char  name[MAXNAMSIZ];       /* class name */
};

struct priority_queue_disc
{
  int dft;
  int limits[4];                /* queue limit */

  GList* rules;
};

struct custom_queue_disc
{
  int dft;
  int limits[17];
  int bc[17];                   /* byte count */

  GList* rules;
};

struct fifo_queue_disc
{
  int limit;
};

struct queue_disc_ops
{
  struct queue_disc* (*create)(char**);
  struct queue_disc* (*lookup)(char**);
  int (*modify)(int, char**, struct queue_disc*);
  
  void (*destroy)(struct queue_disc*);

  int (*doit)(struct queue_disc*, struct nlmsghdr*);
  int (*undo)(struct queue_disc*, struct nlmsghdr*);

  void (*display)(struct vty*, struct queue_disc*, char*);
  void (*config_write)(struct vty*, struct queue_disc*);
  void (*config_erase)(struct queue_disc*);
  
  int (*get_prio)(char*, struct queue_disc*);
};

struct queue_disc
{
  int id;
  int type;
  void *priv;
  int ref;
  struct queue_disc_ops* ops;

  void (*display)(struct vty*, struct queue_disc*, char*);
};

struct queue_disc* queue_disc_create(int, char**);
struct queue_disc* queue_disc_lookup(int, char**);
int queue_disc_modify(int, char**, struct queue_disc*);
void queue_disc_hold(struct queue_disc*);
void queue_disc_release(struct queue_disc*);

void queue_disc_config_write(struct vty* vty, int type);
void queue_disc_config_erase(int type);

#endif
