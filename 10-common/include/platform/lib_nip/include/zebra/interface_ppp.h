#ifndef __INTERFACE_PPP__
#define  __INTERFACE_PPP__
#include "lib/aligned.h"
#define FALSE 0
#define TRUE 1

extern int pppd(void);
typedef unsigned char	bool;

struct ppp_config_info{
	char  auth_type[10] aligned_def;
#define PAP_SENTNAME_MAX_LEN 32
	char pap_sentname[PAP_SENTNAME_MAX_LEN+1] aligned_def;
#define PAP_PASSWORDE_MAX_LEN 32
	char pap_password[PAP_PASSWORDE_MAX_LEN+1] aligned_def;
#define CHAP_HOSTNAME_MAX_LEN 32
	char chap_hostname[CHAP_HOSTNAME_MAX_LEN+1] aligned_def;
	int lcp_interval;
	int lcp_maxretry;
	int lcp_echo_interval;
	int lcp_echo_maxretry;
	int lcp_echo_padding_len;
	int ipcp_interval;
	int ipcp_maxretry;
	int waitforrequest;
	int mtu;
	bool isshut;
	bool ismultilink;
#define PEER_IP_LEN 32
	char peer_default_ip[PEER_IP_LEN+1] aligned_def;
#define CHAP_PASSWORD_MAX_LEN 32
	char chap_password[CHAP_PASSWORD_MAX_LEN+1] aligned_def;	
	int multilink_group;
	int loopback_mode;
	bool default_route;
};
extern struct cmd_element encapsulation_ppp_cmd;
extern struct cmd_element no_encapsulation_ppp_cmd;
extern struct cmd_element ppp_authentication_cmd;
extern struct cmd_element no_ppp_authentication_cmd;
extern struct cmd_element ppp_pap_sentusername_cmd;
extern struct cmd_element no_ppp_pap_sentusername_cmd;
extern struct cmd_element ppp_chap_host_cmd;
extern struct cmd_element no_ppp_chap_host_cmd;
extern struct cmd_element ppp_lcp_interval_cmd;
extern struct cmd_element no_ppp_lcp_interval_cmd;
extern struct cmd_element ppp_lcp_maxwaitforrequest_cmd;
extern struct cmd_element no_ppp_lcp_maxwaitforrequest_cmd;
extern struct cmd_element ppp_lcp_maxretry_cmd;
extern struct cmd_element no_ppp_lcp_maxretry_cmd;
extern struct cmd_element ppp_lcp_echo_paddinglen_cmd;
extern struct cmd_element no_ppp_lcp_echo_paddinglen_cmd;
extern struct cmd_element ppp_lcp_echo_maxretry_cmd;
extern struct cmd_element no_ppp_lcp_echo_maxretry_cmd;
extern struct cmd_element ppp_ipcp_interval_cmd;
extern struct cmd_element no_ppp_ipcp_interval_cmd;
extern struct cmd_element ppp_ipcp_maxretry_cmd;
extern struct cmd_element no_ppp_ipcp_maxretry_cmd;
extern struct cmd_element ppp_lcp_echo_cmd;
extern struct cmd_element no_ppp_lcp_echo_cmd;
extern struct cmd_element ppp_chap_password_cmd;
extern struct cmd_element no_ppp_chap_password_cmd;
extern struct cmd_element ppp_default_route_cmd;
extern struct cmd_element no_ppp_default_route_cmd;


void  install_if_ser_ppp (void);
int set_ppp_ipaddr(struct interface *ifp,  struct connected *ifc);
int clear_ppp_ipaddr(struct interface *ifp, struct connected *ifc);
int ppp_shutdown(struct interface *ifp);
int no_ppp_shutdown(struct interface *ifp);
int set_ppp_mtu(struct interface *ifp, unsigned mtu);
int ppp_show(struct interface *ifp, struct vty *vty);
int ppp_config(struct interface *ifp, struct vty *vty);
int ppp_erase (struct interface *ifp);
int encap_ppp(struct interface *ifp);
int detach_ppp(struct interface *ifp);
int set_ppp_multilink (struct interface *ifp, char isno);
int set_ppp_authentication (struct interface *ifp,  char *paramter,char isno);
int set_ppp_pap_sentusername (struct interface *ifp,  char *sentname,char *password, char isno);
int set_ppp_chap_host (struct interface *ifp,  char *paramter,char isno);
int set_ppp_chap_password(struct interface *ifp, char *paramter ,char isno);
int set_ppp_lcp_interval (struct interface *ifp,  unsigned long paramter,char isno);
int set_ppp_lcp_maxretry (struct interface *ifp,  unsigned long paramter,char isno);
int set_ppp_lcp_echo (struct interface *ifp,  unsigned long paramter,char isno);
int set_ppp_lcp_maxwaitforrequest (struct interface *ifp,  unsigned long paramter,char isno);
int set_ppp_echo_paddlen (struct interface *ifp,  unsigned long paramter,char isno);
int set_ppp_echo_maxretry (struct interface *ifp,  unsigned long paramter,char isno);
int set_ppp_ipcp_interval (struct interface *ifp,  unsigned long paramter,char isno);
int set_ppp_ipcp_maxretry (struct interface *ifp,  unsigned long paramter,char isno);
int set_ppp_peerip (struct interface *ifp,  char *paramter,int isno);//wj
int set_ppp_loopback_mode(struct interface *ifp, int loopback_mode);
int set_ppp_multilink_group(struct interface *ifp ,int vir);
int set_ppp_default_route(struct interface *ifp, char isno);
int set_ppp_shut (struct interface *ifp,  char isno);
int set_debug_ppp(int type);

int  ppp_strtoint(char *paramter, unsigned long *ptr);
void print_ppp_errstr(struct vty *vty,int error_no);
void zebra_ppp_init (void);
int new_ppp_config_info(struct zebra_if *if_link);
void del_ppp_config_info(struct zebra_if *if_link);
int ppp_phy_state_change(struct interface *ifp, int flag);




int  api_ppp_set_echointerval( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_lcpinterval( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_lcpmaxtry( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_lcpmaxwait( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_chaphost( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_chappasswd( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_papinfo( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_multilink( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_auth( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_peeripadd( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_encapt( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_mgroup(unsigned int type ,void *recvbuf, int len ,ZIPC_ID to);
int  api_ppp_set_loopbackmode( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int api_ppp_set_shutdown(unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_defaultroute( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_debug_ppp( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_no_debug_ppp( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_echointerval( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_lcpinterval( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_lcpmaxretry( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_lcpmaxwait( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_chaphost( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_chappasswd( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_papinfo( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_multilink( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_auth( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_peeripadd( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_encapt( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_loopbackmode( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_mgroup(unsigned int type ,void *recvbuf,int len ,ZIPC_ID to);
int  api_ppp_get_loopbackstatus( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_echomaxtry( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_echopaddinglen( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_ipcpinterval( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_set_ipcpmaxtry( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_echomaxtry( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_echopaddinglen( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_ipcpinterval( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_ipcpmaxtry( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_loopbackipaddr( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int api_ppp_get_shutdown(unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_defaultroute( unsigned int type,void* recvbuf,int len,ZIPC_ID to);
int  api_ppp_get_pppoe_state( unsigned int type,void* recvbuf,int len,ZIPC_ID to);

#endif
