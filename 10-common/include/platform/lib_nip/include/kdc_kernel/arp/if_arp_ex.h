/* Extend for arp
   Copyright (C) 2005 kedacom Yuanyi Zhang

 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */

#ifndef __IF_ARP_EX_H
#define __IF_ARP_EX_H

/* extend ARP ioctl request. */
struct arpreq_ex {
  int arp_ex_cmd;			/* extend command		*/
  int arp_ex_flags;			/* extend flags 			*/
  int arp_ex_para;			/* extend parameter		*/
};

/* extend ARP command. */
#define ARP_EX_SETTIMER	0x01	/* Set timeout value for arp timer */
#define ARP_EX_GETTIMER	0x02	/* Get timeout value of arp timer */
#define ARP_EX_CLEARCACHE	0x03	/* Clear arp cache */

/* extend ARP flag values. */
#define ATF_EX_REACHABLE   	0x01 	/* Reachable timer */

/* Added by Gaoqi on 2006-9-1, 
    Add one more ARP flag values. */
#define	ATF_INACT		0x01 	/*	Validation pending, NUD_STALE|NUD_DELAY|NUD_PROBE		*/
/* Ended by Gaoqi */

#define SIOCARPEX    	0x895f          	/* extended ARP control calls */

#endif

