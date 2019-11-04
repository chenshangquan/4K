/***********************************************************************
        Copyright (c) 2014 KEDACOM Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to KEDACOM Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by KEDACOM Ltd..

KEDACOM Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

/*****************************************************************************
MODULE      : kdvsocket for re-write socket APIs with a wrapper
FILES       : kdvsocket.cpp
INCLDUES    : kdvsocket.h
DESCERIPTION: re-write h.323 stack socket operations.
AUTHOR      : Jacky Wei
Version     : V1.0  Copyright(C) 2003-2004 KDC, All rights reserved.
-----------------------------------------------------------------------------
Revision	:
Date		Version     Revisor      Reviewer(s)   Description
2013/12/10	1.0         Jacky Wei			       File created
******************************************************************************/

#ifndef _KDV_SOCKET_H
#define _KDV_SOCKET_H

#pragma once

#include "rvstdio.h"
#include "rvaddress.h"
#include "rvlock.h"
#include "rvthread.h"
#include "rvsocket.h"
#include "cmH245GeneralDefs.h"


#define _TCP_ENC_
//#define _UDP_ENC_

#ifndef _MSC_VER
//#undef FAR
#define FAR
#include <sys/socket.h>
#else
#define socklen_t RvInt32
#endif

#if defined(__cplusplus)
extern "C" {
#endif
	
#define _LEN_OF_TPKT_HDR_   4
#define _LEN_OF_KEDA_HDR_	4
#define _KEDA323_UDP_HDR_	"keda"

void		SetupHAPP	(HAPP hApp);
#ifdef WIN32
RvInt32		kdvrecvfrom (RvSocket s, RvUint8 FAR * buf, RvInt32 len, RvInt32 flags, struct sockaddr FAR *from, RvInt32 FAR * fromlen);
RvInt32		kdvsendto	(RvSocket s, const char FAR * buf, int len, int flags, const struct sockaddr FAR *to, int tolen);
#else
RvInt32		kdvsendto	(RvSocket s, const RvUint8 FAR * buf, RvInt32 len, RvInt32 flags, const struct sockaddr FAR *to, RvInt32 tolen);
RvInt32		kdvrecvfrom	(RvSocket s, RvUint8 FAR * buf, RvInt32 len, RvInt32 flags, struct sockaddr FAR *from, socklen_t * fromlen);
#endif
RvInt32		kdvsend		(RvSocket s, const RvUint8 FAR * buf, RvInt32 len, RvInt32 flags);
RvInt32		kdvrecv		(RvSocket s, RvUint8 FAR * buf, RvInt32 len, RvInt32 flags);

RVAPI void		kdv323logon ();
RVAPI void		kdv323logoff();

RVAPI void		kdv323savefile(RvBool bSaveRecv, RvBool bSaveSend);

#if defined(__cplusplus)
}
#endif

#endif // _KDV_SOCKET_H
