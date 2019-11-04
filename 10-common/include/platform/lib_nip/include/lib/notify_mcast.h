/*
 * NOTIFY MULTICAST LIB
 * Copyright (C) 2005 kedacom
 * Author: Justin S.
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
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */
#ifndef _NOTIFY_MCAST_H_
#define _NOTIFY_MCAST_H_

#include <semaphore.h>

#define     MAX_COMP_DATA_LEN   256

typedef int (*NOTIFY_MC_FUNC)();

typedef int NOTIFY_MC_TYPE;

typedef struct notify_node
{
    struct notify_node *next;

    ZIPC_ID  to;
    int  datalen;
    char data[MAX_COMP_DATA_LEN];

} NOTIFY_NODE;


typedef struct notify_list
{
    NOTIFY_MC_TYPE  type;

    int advance;
    union
    {
        int (*func)(void *, void *, void *, int);
        int (*func_adv)(void *);
        int used;
    } func;

    NOTIFY_NODE *node;

} NOTIFY_LIST;


struct notify_mc_id
{
    sem_t       sem;
    int         tbsize;
    NOTIFY_LIST *table;
};


typedef struct notify_mc_id* NOTIFY_MC_ID;

#define NOTIFY_MC_OP_REG    0x01
#define NOTIFY_MC_OP_UNREG    0x02

#define     NOTIFY_MC_REG_MSG      ZMSG_NOTIFY_MC_BASE + 1

/* FUNCTION */
NOTIFY_MC_ID notify_mc_create(int notify_mc_tb_size);

void notify_mc_free(NOTIFY_MC_ID notify_mc_id);

int notify_mc_set_type(NOTIFY_MC_ID notify_mc_id,
                       NOTIFY_MC_TYPE type,
                       NOTIFY_MC_FUNC func,
                       int advance);

void notify_mc_clr_type(NOTIFY_MC_ID notify_mc_id,
                        NOTIFY_MC_TYPE type);

int notify_mc_reg_specdata(NOTIFY_MC_ID notify_mc_id,
                           NOTIFY_MC_TYPE type,
                           ZIPC_ID to,
                           void *data,
                           int datalen);

int notify_mc_unreg_specdata (NOTIFY_MC_ID notify_mc_id,
                              NOTIFY_MC_TYPE type,
                              ZIPC_ID to,
                              void *data,
                              int datalen);

int notify_mcast(NOTIFY_MC_ID notify_mc_id,
                 NOTIFY_MC_TYPE type,
                 void *compare);

void notify_mcast_show(NOTIFY_MC_ID notify_mc_id);

int notify_mc_reg_specdata_interproc(ZIPC_ID serv,
                                     NOTIFY_MC_TYPE type,
                                     ZIPC_ID to,
                                     void *data,
                                     int datalen);

int notify_mc_unreg_specdata_interproc(ZIPC_ID serv,
                                       NOTIFY_MC_TYPE type,
                                       ZIPC_ID to,
                                       void *data,
                                       int datalen);

int notify_mc_do_register(struct zmsg* zmsg,
                          ZIPC_ID reply,
                          NOTIFY_MC_ID notify_mc_id);
void notify_mcast_show(NOTIFY_MC_ID notify_mc_id);
#endif

