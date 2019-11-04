/*
 * Copyright (c) 2005
 *	 All rights reserved by kedacom.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
 
#ifndef _NIP_NETLINK_KERNEL_H
#define _NIP_NETLINK_KERNEL_H

#define NETLINK_NIP		18	/* 16 to 31 are ethertap */

#define  NIP_SEND_BASE         0x10
#define  NIP_IP_CHECK_REG		NIP_SEND_BASE + 1
#define  NIP_IP_CHECK_UNREG          NIP_SEND_BASE + 2
#define NIP_IP_CHECK_DETECT         NIP_SEND_BASE+3

#define   NIP_SEND_MAX          NIP_SEND_BASE + 4


#define   NIP_REC_MSG_BASE     0x30
#define	NIP_DUPLIT_IP_MSG        NIP_REC_MSG_BASE+1

#define	NIP_REC_MSG_MAX     	NIP_REC_MSG_BASE+2
#define NIP_IP_CHECK_GROUP       1

struct kernel_ip_conflict
{
    u_long 	ipadd;
    u_long        device;
    char macadd[32];
};

struct ip_conflict_user
{
    int     type;
    int     mypid;
    u_long ipadd;
    u_long device;
};

extern int nip_netlink_kernel_init(void);
extern int nip_ip_conflict_event(ulong ip, char *macaddr, ulong device);

#endif







