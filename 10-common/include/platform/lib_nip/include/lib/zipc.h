/*
 * ipc interface
 * Copyright (C) 2005 kedacom
 * Author: Yuanyi Zhang
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
#ifndef ZIPC_H
#define ZIPC_H

#define ZIPC_PATH          "/tmp/"                       /* Prefix of path to bind socket. */
#define ZIPC_ID_LEN        103                           /* ZIPC id */
#define ZMSG_HDR_LEN       8                             /* ZMSG header length, type and length */
#define ZMSG_MAX_LEN       1024
#define ZMSG_SNMP_BASE	 0x00012
#define ZMSG_HTTP_BASE	 0x380000
typedef char ZIPC_ID[ZIPC_ID_LEN];

struct zmsg
{
  u_long type;
  struct stream* bs;                                      /* Buffer stream. */
  struct stream* us;                                      /* User stream. */
};

int zipc_create(ZIPC_ID name);
int zipc_sendmsg(int socket, struct zmsg* zmsg, ZIPC_ID dest);
int zipc_recvmsg(int socket, struct zmsg* zmsg, ZIPC_ID from);
int zipc_send_and_recv(ZIPC_ID dest, struct zmsg* send_msg, struct zmsg* recv_msg);
void zipc_close(int socket);

struct zmsg* zmsg_new(int len);
struct zmsg* zmsg_copy(struct zmsg*);
void zmsg_free(struct zmsg* msg);

inline u_long zmsg_get_len(struct zmsg* msg);
inline void zmsg_set_type(struct zmsg* msg, u_long type);
inline u_long zmsg_get_type(struct zmsg* msg);
inline struct stream* zmsg_get_stream(struct zmsg* msg);

#endif
