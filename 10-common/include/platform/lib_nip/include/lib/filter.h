#ifndef _FILTER_H
#define _FILTER_H

#include "lib/if.h"
//#include <f_list.h>

/* Filter type is made by `permit', `deny' and `dynamic'. */
#if 0
enum filter_type 
{
  FILTER_DENY,
  FILTER_PERMIT,
  FILTER_DYNAMIC
};

enum access_type
{
  ACCESS_TYPE_STRING,
  ACCESS_TYPE_NUMBER
};
#endif


#if 0
/* Access list */
struct access_list
{
  char *name;
  char *remark;

  struct access_master *master;

  enum access_type type;

  struct access_list *next;
  struct access_list *prev;

  struct filter *head;
  struct filter *tail;
};
#endif


#if 0
/* Prototypes for access-list. */
void access_list_init (void);
void access_list_reset (void);
void access_list_add_hook (void (*func)(struct access_list *));
void access_list_delete_hook (void (*func)(struct access_list *));
struct access_list *access_list_lookup (afi_t, char *);
enum filter_type access_list_apply (struct access_list *, void *);
#endif

#endif /* _ZEBRA_FILTER_H */
