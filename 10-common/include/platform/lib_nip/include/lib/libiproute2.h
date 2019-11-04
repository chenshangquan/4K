/* iproute2 library
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

#ifndef _LIBIPROUTE2_H
#define _LIBIPROUTE2_H

#define TC_H_ROOT (0xFFFFFFFFU)
#define TC_H_INGRESS    (0xFFFFFFF1U)

#define TCA_BUF_MAX (64*1024)
#define MAX_MSG 16384

#define H_MAJ_MASK (0xFFFF0000U)
#define H_MIN_MASK (0x0000FFFFU)
#define MAX_MAJ    (0xFFFF)
#define MAX_MIN    (0xFFFF)
#define H_MAJ(h) ((h)&H_MAJ_MASK)
#define H_MIN(h) ((h)&H_MIN_MASK)
#define H_MAKE(maj,min) (((maj)&H_MAJ_MASK)|((min)&H_MIN_MASK))

int pack_key8(struct tc_u32_sel *sel, __u32 key, __u32 mask, int off, int offmask, int type);
int pack_key16(struct tc_u32_sel *sel, __u32 key, __u32 mask, int off, int offmask, int type);
int pack_key32(struct tc_u32_sel *sel, __u32 key, __u32 mask, int off, int offmask, int type);

unsigned tc_calc_xmittime(unsigned rate, unsigned size);
int tc_calc_rtable(unsigned bps, __u32 *rtab, int cell_log, unsigned mtu, unsigned mpu);
int tc_core_init();

int ll_proto_a2n(unsigned short *id, char *buf);
const char * ll_proto_n2a(unsigned short id, char *buf, int len);

#endif

