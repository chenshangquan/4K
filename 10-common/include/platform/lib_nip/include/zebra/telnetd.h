/***************************************************************************
                          telnet.h  -  description
                             -------------------
    begin                : Îå 11ÔÂ 5 2004
    copyright            : (C) 2004 by Yuanyi Zhang
    email                : zhangyuanyi@kedacom.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
 #ifndef _ZEBRA_TELNET_H
 #define _ZEBRA_TELNET_H


//added by swp 2005-10-8 14:23
#define     TND_MANAGE_CLOSE    0x2eee0001
#define     TND_MANAGE_TIMEOUT  0x2eee0002
#define     TND_MANAGE_EXCEPT   0x2eee0003

#define  	TND_TIMEOUT		10 //sec


 int telnetd_init( const char *hostname, unsigned short port );
int telnetd_def_user(void);

 #endif
 
