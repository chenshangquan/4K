/* QoS classifier.
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

#ifndef _CLASS_H
#define _CLASS_H

struct class_filter;
struct class_filter_ops;
struct class_map;
struct policy_class_map;
struct policy_class_map_ops;
struct policy_map;
struct policy_map_ops;

/* filter type */
#define    ACL_FILTER    0         /* filter by access group */
#define    DSCP_FILTER   1         /* filter by dscp value */
#define    INDEV_FILTER  2         /* filter by input interface */
#define    PROTOCOL_FILTER 3     /* filter by protocol */
#define    MATCHALL_FILTER 4
#define    MAX_FILTER_TYPE 5

#define MAXNAMSIZ  255
#define QOS_MAX_SEL_KEYS    20
#define QOS_DFT_BUFFER      100000
#define ACL_NOTIFY_QOS      "qos"

#define MAXCLSNUM    512
#define MAXPOLNUM    128

struct class_dscp_filter_priv* fp;

extern int class_debug;
extern char last_errstr[255];

/* private data for acl filter
 */
struct class_acl_filter_priv
{
  int rulenum;

  ACL_RULE_ENTRY* entries;
  int entry_count;
  
  ACL_NOTIFY notify;
};

/* private data for protocol filter
 */
struct class_protocol_filter_priv
{
  char protocol[16];
};

/* private data for indev filter
 */
struct class_indev_filter_priv
{
  char name[16];
  char unit[16];
};

/* private data for dscp filter
 */
struct class_dscp_filter_priv
{
  int value;
};

/* filter for classifier */
struct class_filter
{
  int type;              /* filter type */
  void* priv;            /* parameters to filter packet, different filter will need different parameters */
  int ref;               /* reference count of this filter, filter can be destroyed only when ref is zero */
  __u32 protocol;        /* protocol of this filter */
  __u32 prio;            /* priority of this filter */

  //  int handle;
  struct class_map* parent;

  struct class_filter_ops * ops;  /* operations filter supported */
};

/* filter stat */
struct class_filter_stat
{
  int pkts;           /* packets matched by this filter */
  int bytes;          /* bytes matched by this filter */
};

/* filter operations */
struct class_filter_ops
{
  struct class_filter* (*create)(char **, struct class_map*);
  struct class_filter* (*lookup)(char **, struct class_map*);
  void (*destroy)(struct class_filter*);
  
  int (*doit)(struct class_filter*, struct policy_class_map*, struct nlmsghdr*, int parent);    /* register filter to kernel */
  int (*undo)(struct class_filter*, char* dev, int parent);    /* unregister filter from kernel */
  
  void (*config_write)(struct vty* vty, struct class_filter*);
  void (*config_erase)(struct class_filter*);
};

struct class_filter* class_filter_create(int, char **, struct class_map*);
struct class_filter* class_filter_lookup(int , char**, struct class_map*);
void class_filter_hold(struct class_filter*);
void class_filter_release(struct class_filter*);

/* class map stat */
struct class_map_stat
{
  int pkts;    /* total number of packets */
  int bytes;   /* total number of bytes */
};

/* class map definition */
struct class_map
{
  char name[MAXNAMSIZ];    /* class name */
  int  ref;                /* reference count */

  //  int handle;              /* handle of this class */

  GList * filter_list;     /* filter list of this class */

  int (*doit)(struct class_map*, char*, int, struct policy_class_map*); /* register class to kernel */
  int (*undo)(struct class_map*, char*, int, struct policy_class_map*); /* unregister class from kernel */

  void (*add_filter)(struct class_map*, struct class_filter*);
  void (*remove_filter)(struct class_map*, struct class_filter*);
};
  
struct class_map* class_map_create(char*); /* create a new class with ref count 1 */
struct class_map* class_map_lookup(char* ); /* lookup class map from global class map list by name */
void class_map_hold(struct class_map *);    /* increment the ref count of class map */
void class_map_release(struct class_map *); /* decrement the ref count of class map, if ref equal zere
                                               then this class map will be destroy. */
void class_map_config_write(struct vty*);   
void class_map_config_erase();

void class_cmd_init();
void qos_notify(ACL_NOTIFY*);

int class_map_priority(struct class_map* c);

#endif
