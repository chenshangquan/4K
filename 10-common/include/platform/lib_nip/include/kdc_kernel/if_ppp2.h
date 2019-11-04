/*	$Id: if_ppp2.h,v 1.00 2005/12/14 06:03:36 paulus Exp $	*/

/*
 * if_ppp2.h - Point-to-Point Protocol definitions.
 *
 * Copyright (c) 1989 Carnegie Mellon University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by Carnegie Mellon University.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 *  ==FILEVERSION 20051214==
 *
 *  NOTE TO MAINTAINERS:
 *     If you modify this file at all, please set the above date.
 *     if_ppp.h is shipped with a PPP distribution as well as with the kernel;
 *     if everyone increases the FILEVERSION number above, then scripts
 *     can do the right thing when deciding whether to install a new if_ppp.h
 *     file.  Don't change the format of that line otherwise, so the
 *     installation script can recognize it.
 */

#ifndef _IF_PPP2_H_
#define _IF_PPP2_H_

struct ppp_newunit_data {
	int unit;
	char name[IFNAMSIZ];
};

/*
 * Ioctl definitions.
 */

#define PPPIOCNEWUNIT2	_IOWR('t', 91, struct ppp_newunit_data)	/* create new ppp unit */
#define PPPORIGNCONNECT	_IOW('t', 92, int)						/* orign connect channel to unit */
#define PPPORIGNIDSCONNECT	_IOW('t', 93, int)						/* orign connect channel to unit */
#endif /* _IF_PPP2_H_ */
