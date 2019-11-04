#ifndef _DNS_SYSYTEM_H
#define _DNS_SYSYTEM_H
#include <lib/zlog.h>
#include <lib/nip_byteorder.h>
#define DNS_DEBUG_MAX_SIZE 512
#define DNS_MAX_PACKET_SIZE 512
#define DNS_NUM_RRS 5
#define DNS_NAME_SIZE   256
#define DNS_MAX_HOSTNAME 32

#define DNS_PRINT(fmt, args...)   vty_out(vty, fmt, ##args)
#define DNS_PRINT2(fmt1,fmt2, args...)  vty_out2(vty, fmt1, fmt2, ##args)

#define DNS_ZLOG_OK
#ifdef DNS_ZLOG_OK
#define DNS_DEBUG(fmt, args...)   zlog_msg("dns", ZLOG_DEBUG, fmt, ##args)
#define DNS_INFO(fmt, args...)     zlog_msg("dns", ZLOG_DEBUG, fmt, ##args)
#define DNS_NOTIF(fmt, args...)    zlog_msg("dns", ZLOG_NOTIFY, fmt, ##args)
#define DNS_WARN(fmt, args...)   zlog_msg("dns", ZLOG_WARN, fmt, ##args)
#define DNS_ERROR(fmt, args...)    zlog_msg("dns", ZLOG_ERROR, fmt, ##args)
#else
#define DNS_DEBUG(fmt, args...)   printf(fmt, ##args)
#define DNS_INFO(fmt, args...)     printf(fmt, ##args)
#define DNS_NOTIF(fmt, args...)   printf(fmt, ##args)
#define DNS_WARN(fmt, args...)    printf(fmt, ##args)
#define DNS_ERROR(fmt, args...)    printf(fmt, ##args)
#endif
          
typedef unsigned char	bool;
typedef unsigned short int uint16;
typedef unsigned long unit32;

//#define SET_UINT16_TO_N(buf, val, count)  *(uint16*)(buf) = htons(val);count += 2; buf += 2
//#define SET_UINT32_TO_N(buf, val, count)  *(unit32*)(buf) = htonl(val);count += 4; buf += 4
//#define SET_UINT32_TO_N_R(buf, val, count)  *(unit32*)(buf) = val;count += 4; buf += 4
#define SET_UINT16_TO_N(buf, val, count, net_val) net_val = htons(val); memcpy((char *)buf, (char *)&net_val, 2);count += 2; buf += 2
#define SET_UINT32_TO_N(buf, val, count, net_val) net_val = htonl(val); memcpy((char *)buf, (char *)&net_val, 4);count += 4; buf += 4
#define SET_UINT32_TO_N_R(buf, val, count)  memcpy((char *)buf, (char *)&val, 4);count += 4; buf += 4

#if 0
#define QUERY		0x0		/* standard query */
#define IQUERY		0x1		/* inverse query */
#endif
#define DNS_STATUS	0x2		         /* nameserver status query*/
#define DNS_UPDATE    0x5         /*update*/
#if 0
/*
 * Currently defined response codes
 */
#define NOERROR		0		/* no error */
#define FORMERR		1		/* format error */
#define SERVFAIL	       2		/* server failure */
#define NXDOMAIN	3		/* non existent domain */
#define NOTIMP		4		/* not implemented */
#define REFUSED		5		/* query refused */
/*added by yumilin*/
#define  YXDOMAIN     6
#define  NOTAUTH      9
	/* non standard */
#define NOCHANGE	0xf		/* update failed to change db */
#endif
#if 0
/*
 * Type values for resources and queries
 */
#define T_A		1		/* host address */
#define T_NS		2		/* authoritative server */
#define T_MD		3		/* mail destination */
#define T_MF		4		/* mail forwarder */
#define T_CNAME		5		/* connonical name */
#define T_SOA		6		/* start of authority zone */
#define T_MB		7		/* mailbox domain name */
#define T_MG		8		/* mail group member */
#define T_MR		9		/* mail rename name */
#define T_NULL_RR	10		/* null resource record */
#define T_WKS		11		/* well known service */
#define T_PTR		12		/* domain name pointer */
#define T_HINFO		13		/* host information */
#define T_MINFO		14		/* mailbox information */
#define T_MX		15		/* mail routing information */
#define T_TXT		16		/* text strings */
#define T_RP		17		/* responsible person */
#define T_AFSDB		18		/* AFS cell database */
#define T_NSAP		22		/* NSAP address */
#define T_NSAP_PTR	23		/* reverse lookup for NSAP */
	/* non standard */
#define T_UINFO		100		/* user (finger) information */
#define T_UID		101		/* user ID */
#define T_GID		102		/* group ID */
#define T_UNSPEC	103		/* Unspecified format (binary data) */
#define T_SA		200		/* shuffle address */
	/* Query type values which do not appear in resource records */
#define T_AXFR		252		/* transfer zone of authority */
#define T_MAILB		253		/* transfer mailbox records */
#define T_MAILA		254		/* transfer mail agent records */
#define T_ANY		255		/* wildcard match */
#endif
#define DNS_NONE      254        /*added by yumilin used for update*/

#define DNS_RR_TTL    86400   /*default ttl time a day*/

#if 0
/*
 * Values for class field
 */
#define C_IN		1		/* the arpa internet */
#define C_CHAOS		3		/* for chaos net at MIT */
#define C_HS		4		/* for Hesiod name server at MIT */
	/* Query class values which do not appear in resource records */
#define C_ANY		255		/* wildcard match */
#endif

struct dns_rr{
  char name[DNS_NAME_SIZE];
  char data[DNS_NAME_SIZE];
  uint16 type;
  uint16 class;
  unit32 ttl;
  uint16 rdatalen;
};

union header_flags 
{
   uint16  flags;
  
  struct {
#if defined (NIP_BIG_ENDIAN)
    uint16 question:1;
    uint16 opcode:4;
    uint16 authorative:1;
    uint16 truncated:1;
    uint16 want_recursion:1;
    
    uint16 recursion_avail:1;
    uint16 unused:3;
    uint16 rcode:4;
#elif defined (NIP_LITTLE_ENDIAN)
    uint16 rcode:4;
    uint16 unused:3;
    uint16 recursion_avail:1;
    uint16 want_recursion:1;
    uint16 truncated:1;

    uint16 authorative:1;
    uint16 opcode:4;
    uint16 question:1;
#endif
} f;
};

struct dns_header_s
{
  uint16 id;
  union header_flags flags;
  uint16 qdcount;
  uint16 ancount;
  uint16 nscount;
  uint16 arcount;
};

struct dns_message
{
  struct dns_header_s header;
  struct dns_rr question[DNS_NUM_RRS];
  struct dns_rr answer[DNS_NUM_RRS];
};

 int dns_ipaddress_valid_check (char *dot_addr);
 int dns_domain_check(char *domain);

#endif


