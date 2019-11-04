#ifdef LTP_NIP_TEST

#ifndef __NL_H__
#define __NL_H__

#include "lib/zebra.h"
#include "ltp/lib/msg.h"
#include "glib/glib.h"
#include <ltp/lib/nip_ltp.h>

int tunnel_send(int, void *, int);

int tunnel_recv(int, void *, int);

int tunnel_get(NL_HANDLE *);

int nl_register_tst(NL_MODULE tst);

struct tst_list *nl_get_tst(NL_MODULE tst);

int nl_register_item(MODULE_TST_ITEM item, struct nl_opts *opt);


#endif

#endif
