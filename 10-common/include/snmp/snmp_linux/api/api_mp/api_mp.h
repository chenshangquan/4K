#ifndef _API_MP_H_
#define _API_MP_H_

extern int  nip_mpvif_set_maxfrags(char *ifname,int  ifunit,	char *max_frags,	int handle_type);
extern int  nip_mpvif_get_maxfrags(char *ifname,int ifunit, 	char * max_frags);	
extern int  nip_mpvif_set_maxfrags_auto_length(char *ifname, int ifunit ,int  min_pktlen,int	handle_type );
extern int  nip_mpvif_get_maxfrags_auto_length(char *ifname,int  ifunit ,int *min_pktlen);	
extern int  nip_gnl_set_vir_multilink_user(char *usrname, int virnum, int opcode);
extern  int  nip_gnl_get_vir_multilink_user(int virnum, char  **mluser, int *num);
//extern int  nip_if_get_lookback_state(int virname ,int *flag);
extern int nip_mp_is_loopback(char *   ifname ,int  ifunit, int *loopback);
extern int mp_api_get_bandwidth(int ifunit ,unsigned long *bandwidth);

#endif


