/* pingLib.h - Packet InterNet Grouper (PING) library header */

/* Copyright 2005 linux Systems, Inc. */

/*
modification history
--------------------

*/

#ifndef __INCpingLibh
#define __INCpingLibh
#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define PING_MAXPACKET		4096	/* max packet size */
#define PING_INTERVAL		1	    /* default packet interval in seconds */

#define MAXINETNAME         16      /* "111.111.111.111\0" */

/* flags */
#define	PING_OPT_SILENT		0x1	    /* work silently */
#define	PING_OPT_DONTROUTE	0x2	    /* dont route option */
#define	PING_OPT_DEBUG		0x4	    /* print debugging messages */

#define PING_DEFAULT_PKTSIZE    64
#define PING_DEFAULT_PKTNUM     5
#define PING_DEFAULT_TMO        2

#define PING_COUNT_RANGE  "<1-2147483646>"
#define PING_SIZE_RANGE  "<0-1472>"
#define PING_TIME_RANGE  "<0-3600>"

typedef struct pingStat				                        /* PING_STAT */
    {
    int			            pingFd;                         /* socket file descriptor */

    char		            toHostName [MAXHOSTNAMELEN];/* name to ping - PAD */
    char		            toInetName [MAXINETNAME];       /* IP addr to ping */

    u_char		            bufTx [PING_MAXPACKET];	        /* transmit buffer */
    u_char		            bufRx [PING_MAXPACKET];	        /* receive buffer */

    struct  ip  *           pBufIp;                         /* ptr to ip    */
    struct icmp	*	        pBufIcmp;		                /* ptr to icmp */
    int			            dataLen;		                /* size of data portion */
    int			            numPacket;		                /* total # of packets to send */
    int			            numTx;			                /* number of packets sent */
    int			            numRx;			                /* number of packets received */
    int			            idRx;			                /* id of Rx task */
    unsigned int			        tMin;			                /* min RT time (ms) */
    unsigned int			        tMax;			                /* max RT time (ms) */
    unsigned int			        tSum;			                /* sum of all times */
    int			            flags;		                /* option flags */
    struct timeval          txtime;
    } PING_STAT;


extern int ping (char *host,
                 char *soruce_addr,
                 int numPackets,
                 int packetsize,
                 int txTmo,
                 int options,
                 struct vty *vty);
extern void ping_sigint();
#ifdef __cplusplus
}
#endif

#endif /* __INCpingLibh */
