/*
 * HDLC      function.
 * Copyright (C) 2006 KEDACOM
 *
 * Version:	@(#)interface_hdlc.h	1.0.0	20/02/06
 *
 * Authors: zhanka
 */

 
#ifndef _INCLUDE_HDLC_H_
#define _INCLUDE_HDLC_H_

#define HDLC_KEEPALIVE                10
#define HDLC_TIMEOUT                  25
#define HDLC_SET_KEEPALIVE_DEFAULT    1
#define HDLC_SET_TIMEOUT_DEFAULT      2
#define HDLC_NOT_SET_DEFAULT          0



struct hdlc_config_info {
	int keepalive;
	int timeout;
	int ttyfd;
};

int encap_hdlc(struct interface *ifp);
int detach_hdlc(struct interface *ifp);
int hdlc_show(struct interface *ifp, struct vty *vty);
int hdlc_config (struct interface *ifp, struct vty *vty);
int hdlc_erase (struct interface * ifp) ;
int shutdown_if_hdlc(struct interface * ifp) ;
int no_shutdown_if_hdlc(struct interface * ifp) ;
int set_hdlc_tty(struct interface *ifp);
int unset_hdlc_tty(struct interface *ifp);
int sifup_hdlc(struct interface *ifp);
int sifdown_hdlc(struct interface *ifp);
int link_hdlc_config_info_init(struct zebra_if_link *if_link, int *errid);
int link_hdlc_config_info_show(struct zebra_if_link *if_link, int *errid, struct vty *vty);
int link_hdlc_config_info_mod(struct zebra_if_link *if_link, unsigned int interval,
    unsigned int timeout_interval,int *errid);
int set_hdlc_config_info_ttyfd(struct zebra_if_link *if_link,int tty_fd);
int get_hdlc_config_info_ttyfd(struct zebra_if_link *if_link);
int link_hdlc_config_info_free(struct zebra_if_link *if_link, int *errid);
int set_hdlc_debug_flag(struct interface *ifp,unsigned int cmd);
int set_hdlc_debug(unsigned int type);
int check_value_range(unsigned int value, unsigned int min, unsigned int max);
int create_sock_for_hdlc(void);
int set_proto_cisco(struct interface *ifp,unsigned int *interval,
	unsigned int *timeout,int *errid, unsigned int cmd_type, int set_default);
void  install_if_ser_hdlc (void);
int print_hdlc_errstr(struct vty *vty,int error_id);
int get_hdlc_config_info_keepalive(struct zebra_if_link *if_link);
int get_hdlc_config_info_timeout(struct zebra_if_link *if_link);
int hdlc_phy_state_change(struct interface *ifp, int flag);


#endif /* INCLUDE_HDLC */


 
