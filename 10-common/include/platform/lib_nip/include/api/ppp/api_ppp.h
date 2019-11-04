/*
 * NIP APIS of ppp module
 * Copyright (C) 2005 kedacom
 * Author:WanJiang
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2, or (at your
 * option) any later version.
 * 
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA. 
 */
#ifndef API_PPP_H
#define API_PPP_H

#include <sys/time.h>

#define NIP_USENAME_LEN 	32
#define NIP_PASSWORD_LEN	32

/*callback msg*/
#define   NIP_PPPOE_MSG_BASE				1000
#define 	NIP_PPPOE_LINK_UP_MSG			NIP_PPPOE_MSG_BASE+1
#define 	NIP_PPPOE_LINK_DOWN_MSG			NIP_PPPOE_MSG_BASE+2
#define 	NIP_PPPOE_AUTH_FAILED_MSG		NIP_PPPOE_MSG_BASE+3
#define  	NIP_PPPOE_SERVER_ERROR_MSG			NIP_PPPOE_MSG_BASE+4

#define 	NIP_PPPOE_PROTOCOL_UP			0x01
#define	NIP_PPPOE_RUNNING					0x02
#define 	NIP_PPPOE_CHAP_AUTH				0x04
#define	NIP_PPPOE_PAP_AUTH				0x08

#define 	NIP_DEFAULT_VIRTUAL_INTERFACE 	16

typedef   struct nip_callback_msg {
	/*attached with NIP_PPPOE_LINK_UP_MSG*/
	unsigned long  local_ipaddr;
	unsigned long  peer_ipaddr;
	/*attached with  NIP_PPPOE_LINK_DOWN_MSG*/
	/*attached with  NIP_PPPOE_AUTH_FAILED_MSG*/
	char username[NIP_USENAME_LEN];
	char password[NIP_PASSWORD_LEN];
	int unit;
}NIP_CALLBACK_MSG;

typedef void (*nip_pppoe_callback) (int msgid , NIP_CALLBACK_MSG *nip_callback_msg);



#define NIP_MAX_VERSION_LEN	100
typedef struct nip_pppoe_version_info{
	char pppoe_version[NIP_MAX_VERSION_LEN];
}NIP_PPPOE_VERSION_INFO;

#define NIP_IP_ADDR_LEN 		32
#define NIP_IP_MASK_LEN 		32
#define NIP_MAX_NIP_USENAME_LEN	32
#define NIP_MAX_NIP_PASSWORD_LEN	32
#define NIP_IF_NAME_LEN			20

typedef struct nip_pppoe_cfg_param{
	int	virtual_unit;
	char ethname[NIP_IF_NAME_LEN];
	char	eth_ip_addr[NIP_IP_ADDR_LEN];
	char	eth_ip_mask[NIP_IP_MASK_LEN];
	char	username[NIP_MAX_NIP_USENAME_LEN];
	char password[NIP_MAX_NIP_PASSWORD_LEN];
	int  	enable_defaultroute;
	int 	echo_interval;
	int 	echo_retry; 
}NIP_PPPOE_CFG_PARAM;


typedef struct nip_pppoe_if_state{
	unsigned long 	pppoe_flags;				
	unsigned long input_pkts;		
	unsigned long output_pkts;		
	unsigned long	if_address;		
	unsigned long 	peer_addr;			
	int		link_down_times;	
	int		pppoe_dialer_times;
	unsigned long 	link_keep_time;	
	unsigned long 	dns_ipaddr[2];		
}NIP_PPPOE_IF_STATE;



extern int nip_ppp_set_lcpinterval(char *ifname,int ifunit ,unsigned long lcp_interval,int handle_type);
extern int nip_ppp_set_echointerval(char *ifname,int ifunit ,unsigned long echo_interval,int handle_type);

extern int nip_ppp_set_echomaxretry(char *ifname,int ifunit ,unsigned long echo_maxretry,int handle_type);
extern int nip_ppp_set_echopaddinglen(char *ifname,int ifunit ,unsigned long echo_paddinglen,int handle_type);
extern int nip_ppp_set_ipcpinterval(char *ifname,int ifunit ,unsigned long ipcp_interval,int handle_type);
extern int nip_ppp_set_ipcpmaxretry(char *ifname,int ifunit ,unsigned long ipcp_maxretry,int handle_type);

extern int nip_ppp_set_auth(char * ifname,int ifunit,char * pppauth_type,int opcode );
extern int nip_ppp_set_papinfo (char *ifname ,int ifunit , char * username, char * password, int  opcode );
extern int nip_ppp_set_chaphostname(char *  ifname, int   ifunit, char * chap_hostname , int opcode);
extern int nip_ppp_set_chappassword(char * ifname,int  ifunit,char *chap_password,int  opcode);
extern int nip_ppp_set_authen_info(char *ifname,int ifunit,char *username , char *password, int  opcode);
extern int nip_ppp_set_peeraddr(char *ifname , int ifunit , char *peer_addr, int opcode);
extern int nip_srl_set_mgroup(char *ifname,int ifunit ,int mgroup,int handle_type);
extern int nip_ppp_set_lcpmaxretry(char *ifname,int ifunit ,unsigned long lcp_maxretry,int handle_type);
extern int nip_ppp_set_lcpmaxwait(char *ifname,int ifunit ,unsigned long lcp_maxwait,int handle_type);
extern int nip_ppp_set_multilink(char *   ifname ,int  ifunit ,	int   opcode );
extern int nip_srl_set_encpt(char *ifname ,int  ifunit ,char * encpt,int opcode );
extern int nip_ppp_set_mode(char *   ifname ,int  ifunit ,	char *mode , int   opcode );
extern int nip_ppp_set_defaultroute(char *   ifname ,int  ifunit, int optcode);
extern int nip_ppp_set_shutdown(char *   ifname ,int  ifunit ,	int   opcode );
/*get routine start*/
extern int nip_ppp_get_echointerval(char *ifname,int ifunit ,unsigned long  *echo_interval);
extern int nip_ppp_get_auth(char * ifname,int ifunit,char * pppauth_type);
extern int nip_ppp_get_papinfo (char *ifname ,int ifunit , char * username, char * password );
extern int nip_ppp_get_chaphostname(char *  ifname, int   ifunit, char * chap_hostname );
extern int nip_ppp_get_chappassword(char * ifname,int  ifunit,char *chap_password);
extern int nip_ppp_get_peeraddr(char *ifname , int ifunit , char *peer_addr);
extern int nip_ppp_get_lcpinterval(char *ifname,int ifunit ,unsigned long *lcp_interval);
extern int nip_ppp_get_shutdown(char *   ifname ,int  ifunit, int *shutdown_flag);
extern int nip_ppp_get_defaultroute(char *   ifname ,int  ifunit, int *multi_flag);
extern int nip_srl_get_mgroup(char *ifname,int ifunit ,int *mgroup);
extern int nip_ppp_get_lcpmaxretry(char *ifname,int ifunit ,unsigned long *lcp_maxretry);
extern int nip_ppp_get_lcpmaxwait(char *ifname,int ifunit ,unsigned long *lcp_maxwait);
extern int nip_ppp_get_multilink(char *   ifname ,int  ifunit, int *multi_flag);
extern int nip_srl_get_encpt(char * ifname,int  ifunit,char *encapt);
extern int nip_ppp_get_mode(char *   ifname ,int  ifunit, char *mode);
extern int nip_ppp_is_loopback(char *   ifname ,int  ifunit, int *loopback);

extern int nip_ppp_get_echomaxretry(char *ifname,int ifunit ,unsigned long *echo_maxretry);
extern int nip_ppp_get_echopaddinglen(char *ifname,int ifunit ,unsigned long *echo_paddinglen);
extern int nip_ppp_get_ipcpinterval(char *ifname,int ifunit ,unsigned long *ipcp_interval);
extern int nip_ppp_get_ipcpmaxretry(char *ifname,int ifunit ,unsigned long *ipcp_maxretry);
extern int ppp_sysif_if_loopback (long *ipaddr);
extern int nip_eth_set_pppoe(char *eth, int vir_unit, int handle_type);
extern int nip_eth_get_pppoe(char *eth, int *vir_unit);
extern int nip_pppoe_start( int vir_unit);
extern int nip_pppoe_stop( int vir_unit);
extern int nip_pppoe_get_versioninfo(NIP_PPPOE_VERSION_INFO  *nip_pppoe_version_info);
extern int nip_pppoe_init(NIP_PPPOE_CFG_PARAM *pppoe_cfg) ;
extern int nip_poevif_get_pppoe_state (int virtual_unit, NIP_PPPOE_IF_STATE *pppoe_state);
extern int nip_pppoe_debug_off(void );
extern int nip_pppoe_debug_on(void );

extern int nip_pppoe_register_callbackfunction(unsigned long  usearg,int virtual_unit, nip_pppoe_callback  call_function );
extern int nip_pppoe_unregister_callbackfunction(unsigned long  usearg,int virtual_unit);
extern int nip_ppp_callback_init(void);
extern int nip_ppp_callback_free(void);

#endif


