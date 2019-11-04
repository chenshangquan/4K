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

#ifndef _NIP_IPCHK_H
#define _NIP_IPCHK_H
#include <linux/netlink.h>

#define DEF_TIME_TO_DETECT_IPCONFLICT 3

typedef void(*ARP_IP_VIOLATE_CALLBACK)(u_char* mac_addr, struct in_addr* addr);

struct nip_ipchk_kernel_info{
    struct nlmsghdr nh;
    int     type;
    int     my_pid;
    u_long ipadd;
    u_long device;
};

/*used to store the kernel information */
struct ipconflict_Msg
{
    u_long 	ipadd;
    u_long        device;
    char macadd[32];
};

extern int nip_ip_conflict_check_register(void);
extern void nip_ip_conflict_callback (unsigned long arg, unsigned long user_arg);
extern void arp_ip_violate_reg(ARP_IP_VIOLATE_CALLBACK usrcall);
extern void arp_ip_violate_reg2(ARP_IP_VIOLATE_CALLBACK usrcall, int time_to_detect);
extern void arp_ip_violate_unreg(void);
#endif











