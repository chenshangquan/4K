/*
 * SUB VLAN       function.
 * Copyright (C) 2006 KEDACOM
 *
 * Version:	@(#)interface_sub_vlan.h	1.0.0	13/03/06
 *
 * Authors: zhanka
 */
#ifndef _INCLUDE_SUB_VLAN_H_
#define  _INCLUDE_SUB_VLAN_H_

#define ADD_VLAN_BY_IFNAME_AND_ID_CMD       		1
#define DEL_VLAN_BY_IFVLAN_NAME_CMD        	 		2
#define DUB_VLAN_BY_IFVLAN_NAME_CMD         		3
#define UNDUB_VLAN_BY_IFVLAN_NAME_CMD       		4
#define ADD_VLAN_DEV_NO_GRP_CMD 				  	5
#define ADD_VLAN_TO_GRP_CMD					  	6
#define DEL_VLAN_DEV_FROM_GRP_CMD                     	7
#define DEL_VLAN_DEV_CMD						  	8
#define NO_SUB_VLAN_ID                         				-1

/*
 *unit: sub vlan unit like 23
 *id  : sub vlan id like 45
 *name: the eth name sub vlan attached like feth1
 */
struct sub_vlan_config_info {
	int  vlan_ID;
    	int sub_if_unit;
	char if_name[24];
};

/*
 *id   : check the id isn't used.
 *name : whitch vlan interface used the id.
 *flag : isn't used: CMD_SUCCESS(unused),CMD_WARNING(used). 
 */
struct check_pram {
	int id;
	int flag;
	char name[24];
};

int encap_sub_vlan(struct interface *ifp);
int detach_sub_vlan(struct interface *ifp);
int sub_vlan_show(struct interface *ifp, struct vty *vty);
int sub_vlan_config(struct interface *ifp, struct vty *vty);
int sub_vlan_erase (struct interface * ifp) ;
int sub_vlan_config_info_init(struct interface *ifp, int *errid);
int sub_vlan_config_info_mod(struct interface *ifp, unsigned int *unit,
	int *id, char *name ,int *errid);
int set_sub_vlan_config_info_vlanID(struct zebra_if_link *if_link,int ID);
int show_sub_vlan_info(struct interface *ifp, struct vty *vty, int *space);
int sub_vlan_config_info_free(struct interface *ifp, int *errid);
int check_vlan_id_flag(struct interface *ifp, struct check_pram *pram);
int check_vlan_id(struct check_pram *pram);
int chk_id(struct interface *ifp, int vlan_ID, struct vty *vty);
int show_vlan_flag(struct interface *ifp, struct vty *vty);
int show_vlan(struct vty *vty);
int set_vlan_debug_flag(struct interface *ifp, unsigned int cmd);
int set_vlan_debug(unsigned int type);
char *get_if_name_vlan(char *name, int *unit);
int set_encapsulation_dot1Q(struct interface *ifp, int *vlan_ID, int sub_vlam_cmd);
void  install_if_sub_vlan (void);
int print_sub_vlan_errstr(struct vty *vty,int error_id);
int sub_vlan_config_info_get(struct interface *ifp, int *errid);
char *is_if_name_vlan(char *name);


#endif /* INCLUDE_SUB_VLAN */



