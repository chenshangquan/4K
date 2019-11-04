/* ddns client update*/
#ifndef _DNSC_UPDATE
#define _DNSC_UPDATE
#define DNSC_MAX_IFNAME 16
#define DNSC_MAX_IFIP 5
#define DNSC_INVALID_IP  0xffffffff
#define DNS_UPDATE_NO_REGISTER   0
#define DNS_UPDATE_REGISTER     1
#define DNS_UPDATE_MODIFY       2
#define DNSC_MAX_R_IP     5    /*the max num of ip to register */

#define sys_get_ddns_debug()  (_ddnsc_debug)


typedef struct ddnsc_update_request_s
{
  char cname[DNS_NAME_SIZE];   /*主机名*/
  int update_mode;                  /*指明是注册、注销还是修改*/
  int retry;
  struct dns_message message;    /*更新请求的部分信息*/
  char original_buf[DNS_MAX_PACKET_SIZE];    /* 原始数据用于直接重发 */
  int buflen;                                                       /*数据包长度*/
  char *here;
  char ddnsc_debug_tmp[DNS_DEBUG_MAX_SIZE];
}ddnsc_update_request_t;

typedef struct ddnsc_cfg
{
    struct	sockaddr_in server;
    ulong ddns_packet_id;
    char	defdname[DNS_NAME_SIZE];	/* default domain */
    char local_name[DNS_NAME_SIZE];    /*注册的主机名*/
    int ip_change;
    int host_change;
}ddnsc_cfg_t;

typedef struct ddnsc_register_info
{
    int ddnsc_reg_ena;
    int ifunit;
    int ip_num;
    char  ifname[DNSC_MAX_IFNAME];
    ulong  ip[DNSC_MAX_IFIP];
}ddnscr_info;

void ddnsc_interface_process(char *ifname, int ifunit, int add);
void ddnsc_if_ipaddress_change_process(char *ifname, int ifunit, ulong ip, int add);
//static int ddns_construct_name(char *name, char *encoded_name);
//static int  ddns_name_process_pre(char *old_name, char *full_name, struct vty *vty);
int ddns_client_mk_update( int mode);
void ddnsc_update_process();
void ddns_update_list_deal (GList  **list);
GList *ddns_update_list_find_by_id(GList *list, int head_id);
GList *ddnsc_register_list_look_up(char *ifname , int ifunit);

#endif


