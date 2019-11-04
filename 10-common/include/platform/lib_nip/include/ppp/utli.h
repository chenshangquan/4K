#ifndef __API_UTLI_H
#define __API_UTLI_H

/* 
 * Database functions
 * Copyright (C) Andrew Tridgell 1999
 * 
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms AND provided that this software or
 * any derived work is only used as part of the PPP daemon (pppd)
 * and related utilities.
 * The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Note: this software is also available under the Gnu Public License
 * version 2 or later.
 */
#include "api/lib/zipc/zipc.h"
#include "g_module.h"
int zebra_sendto_nip(void *getback, unsigned int type, int len,ZIPC_ID to);




#endif /* ! __TDB_H */
