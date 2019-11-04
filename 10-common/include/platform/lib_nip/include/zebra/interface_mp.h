#ifndef __INTERFACE_MP__
#define __INTERFACE_MP__

#include "ppp/tdb.h"
#include "lib/aligned.h"
#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 64
#define SERIAL_to_VIRTUAL 256


struct mp_config_info {
	char ifname[16] aligned_def;
	int mrru;
	unsigned char isshut;
#define PEER_IP_LEN 32
	char peer_default_ip[PEER_IP_LEN+1] aligned_def;
	int minipktlen;
	int maxfrag;
	int ipcp_interval;
	int ipcp_maxretry;
};

void install_if_mp (void);
void zebra_mp_init (void);
int zebra_sendto_mp(struct interface *ifp ,void * ptr, int len,unsigned long  type);
int mp_encap (struct interface *ifp);
int mp_detach (struct interface *ifp);
 int mp_set_mrru (struct interface *ifp, unsigned mrru);
int mp_set_ipaddr (struct interface *ifp,  struct connected *ifc);
int mp_clear_ipaddr (struct interface *ifp, struct connected *ifc);
 int mp_show (struct interface *ifp, struct vty *vty);
 int mp_config (struct interface *ifp, struct vty *vty);
int mp_erase (struct interface *ifp);
int mp_shutdown (struct interface *ifp);
int mp_no_shutdown (struct interface *ifp);
int mp_get_ml_virnum (int virnum,char *usernames);
int mp_ml_user_add (char *username, int vir_unit);
int mp_ml_user_del (char *username);


int zebra_msgfd_init(struct zebra_if *if_link,char *name);

int set_mp_max_fragment(struct interface *ifp, int maxfrag);
int set_mp_min_pktlen(struct interface *ifp , int pktlen);
int set_debug_multilink(int type);

int set_mp_ipcp_maxretry (struct interface *ifp,  unsigned long paramter,char isno);
int set_mp_ipcp_interval (struct interface *ifp,  unsigned long paramter,char isno);


#endif


