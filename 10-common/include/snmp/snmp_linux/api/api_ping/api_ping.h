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

#define PING_MAXPACKET		1472	/* max packet size */
#define PING_INTERVAL		1	    /* default packet interval in seconds */

#define MAXINETNAME         16      /* "111.111.111.111\0" */
#define PingClkRate     1000000
#define MAXHOSTNAMELEN 64

/* flags */
#define	PING_OPT_SILENT		0x1	    /* work silently */
#define	PING_OPT_DONTROUTE	0x2	    /* dont route option */
#define	PING_OPT_DEBUG		0x4	    /* print debugging messages */

#define PING_DEFAULT_PKTSIZE    64
#define PING_DEFAULT_TMO        2
#define PING_DEFAULT_TTL    0x40

#define PING_TIMEOUT   3
#define PING_REPLY   2
#define PING_ERROR  1

typedef void (*PING_USER_CALL_BACK) (int result, int ttl,  int trip_time, int echoid, int err_type, int err_code);

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
    unsigned int	           trip_time;			                /* min RT time (ms) */
    int			            flags;		                /* option flags */
    int                               time_out;
    int                               result;
    int                               ttl;
    int                               err_type;
    int                               err_code;
    struct timeval          txtime;
    PING_USER_CALL_BACK user_call_back;
    
    } PING_STAT;

struct pingopts
{
	int packetsize;  /*包的大小*/
	int timeout;    /*超时时间*/
	int ttl;        /*ttl值*/
};

int Ping1( char *Host, struct pingopts *opts, int  dwOptions, int echoid, \
              PING_USER_CALL_BACK usrcall);

#ifdef __cplusplus
}
#endif

#endif /* __INCpingLibh */
