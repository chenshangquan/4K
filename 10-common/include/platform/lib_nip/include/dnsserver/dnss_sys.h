#ifndef _DNS_SYS_H
#define _DNS_SYS_H

#include <netinet/in.h>
//#include <resolv/Resolv.h>
//#include <G_module.h>

#define ZMSG_ZEBRA_TO_DNSS_CMD    ZMSG_DNS_BASE + 3

#define DNS_NUM_RRS 5
#define DNS_CLINET_TIMEOUT 3
#define 	DNS_DEF_TTL 	0
#define DNS_IP_NUM 10
#define DNSS_DEBUG_UPDATE 0x01
#define DNSS_DEBUG_QUERY 0x02
#define DNSS_SHOW_REPLY_TTL 0x01
#define DNSS_SHOW_FOREIGN_SER 0x02

typedef struct dns_request_s
{
  char cname[DNS_NAME_SIZE];
  char ip[20];
  u_long multi_ip[DNS_IP_NUM];
  int ttl;
  int time_pending; /* request age in seconds */

  /* the actual dns request that was recieved */
  struct dns_message message;

  /* where the request came from */
  struct in_addr src_addr;
  int src_port;

  /* the orginal packet */
  char original_buf[DNS_MAX_PACKET_SIZE];
  int numread;
  char *here;

  /* next node in list */
  struct dns_request_s *next;
  char dnss_debug_tmp[DNS_DEBUG_MAX_SIZE];
}dns_request_t;

typedef struct dnss_manul_deal
{
    int add;
    int ttl;
    char hostname[DNS_MAX_HOSTNAME];
    char ip[20];
}dnss_manul_d;

typedef struct dnss_set
{
    ulong for_ip;
    int ttl;
} dnss_set_t;

struct dnss_msg
{
    int ddnsc_cmd_type;
    int reply_ttl;
    char new_domain[DNS_MAX_HOSTNAME];
    ulong foreign_ip;
    dnss_manul_d manul_host;
    struct vty *p_vty;
};


enum
{
    DNSS_DOMAIN_CHANGE = 0,
    DNSS_EXIT_THREAD,
    DNSS_MANUAL_HOST,
    DNSS_CFG_MAX
};

void dnss_init(void);

#endif
