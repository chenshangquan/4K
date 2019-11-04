
#ifndef _DNS_SYS_PROXY
#define _DNS_SYS_PROXY

#define DNS_SERVER_PORT 53
#define DNS_FILE_BUF_SIZE 255
#define DNS_SERV_TIMEOUT 3
#define MAXDNSNAME	256

#define DNSS_MAX_RR_NUM 100

typedef struct dns_server_config
{
    struct in_addr foreign_server;
    char	defdname[MAXDNSNAME]; 
    int reply_rr_ttl;
} dns_server_cfg_t;

 typedef struct dnss_stat 
{
    ulong dns_query_a_num;
    ulong dns_query_ptr_num;
    ulong dns_local_answer;
    ulong dns_query_sendto_foreign;
    ulong dns_foreign_answer;
    ulong dns_not_find_answer;
    ulong dns_update_num;    
    ulong dns_update_format_error;
    ulong dns_not_auth_error;
    ulong host_dynamic_num;
    ulong host_manual_num;
    ulong host_foreign_num;
} dnss_stat_t;

void dns_server_main_loop(void);
void show_dnss_details(struct vty *vty);

#endif

