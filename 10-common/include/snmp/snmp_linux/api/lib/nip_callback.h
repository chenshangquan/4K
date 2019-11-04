/*
 * Header file for nip callback routine.
 * Copyright (C) 2005 kedacom
 * Author: Yuanyi Zhang
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2, or (at your
 * option) any later version.
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

#ifndef __NIP_CALLBACK_H
#define __NIP_CALLBACK_H

#define CALLBACK_TYPE(e)  ((e) >> 20)
#define CALLBACK_CODE(e)  ((e) & 0xfffff)

typedef void (*EVENT_CALLBACK)(unsigned long arg, unsigned long user_arg);
typedef void (*EVENT_TIMEOUT)(unsigned long arg);

struct nip_callback_type;

struct nip_callback_ops
{
	int (*init)(struct nip_callback_type* t);
	int (*doit)(struct nip_callback_type* t);
	int (*destroy)(struct nip_callback_type* t);
};

struct nip_callback_type
{
	unsigned int type;
	int fd;

	struct nip_callback_ops* ops;
	GList* node_list;
	
	unsigned int time_left;
};

struct nip_callback_node
{
	unsigned int code;
	unsigned int timeout;
	unsigned int time_left;
	
	EVENT_CALLBACK callback_func;
	EVENT_TIMEOUT timeout_func;
	unsigned long arg;
};

int nip_api_register_callback(int event, EVENT_CALLBACK callback, EVENT_TIMEOUT timeout_func, int timeout, unsigned long arg);
int nip_api_unregister_callback(int event, EVENT_CALLBACK callback);

int nip_api_register_type(int type, struct nip_callback_ops *ops);
int nip_api_unregister_type(int type);
int nip_callback(int type, int code, unsigned long arg);

int nip_api_callback_init();

#endif
