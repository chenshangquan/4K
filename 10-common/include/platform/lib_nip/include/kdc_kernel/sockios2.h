/*
 * INET		An implementation of the TCP/IP protocol suite for the LINUX
 *		operating system.  INET is implemented using the  BSD Socket
 *		interface as the means of communication with the user level.
 *
 *		Definitions for the Interfaces handler.
 *
 * Readme:    This file is a supplement for 'linux/sockios.h'.
 *
 * NOTE: This is an internal header file, included by 'linux/sockios.h'.
 *           You should not attempt to use it directly.
 *
 * Version:	@(#)sockios2.h	0.0.1	2004/12/15
 *
 * Authors:	Zhishuang Zhang,<zhangzhishuang@kedacom.com>
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 *
 */
#ifndef _LINUX_SOCKIOS2_H
#define _LINUX_SOCKIOS2_H

#include <asm/ioctl.h>

#define SIOCGIFBANDWIDTH   _IOWR(0x8a, 1, struct ifreq)
#define SIOCSIFBANDWIDTH   _IOW(0x8a, 2, struct ifreq)

#define SIOCGIFSERLOOP   _IOWR(0x8a, 3, struct ifreq)
#define SIOCSIFSERLOOP   _IOW(0x8a, 4, struct ifreq)
#define SIOCCIFSERLOOP   _IOW(0x8a, 5, struct ifreq)

#define SIOCSIGMPVER   _IOW(0x8a, 6, struct ifreq)

#define SIOCGIFLINE	_IOR(0x8a, 7, struct ifreq)
#define SIOCCIFBANDWIDTH	_IO(0x8a, 8)


#define SIOCADDLOOP   (SIOCDEVPRIVATE + 0)
#define SIOCDELLOOP   (SIOCDEVPRIVATE + 1) 


#endif	/* _LINUX_SOCKIOS2_H */

