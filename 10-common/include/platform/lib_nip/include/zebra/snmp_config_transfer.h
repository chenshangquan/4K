#ifndef __SNMP_CONFIG_TRANSFER__
#define __SNMP_CONFIG_TRANSFER__
#include "zebra/snmp_config.h"

#define SNMP_COMMUNITY_TOKEN 								"com2sec"
#define SNMP_GROUP_TOKEN 										"group"
#define SNMP_VIEW_TOKEN                    	"view"
#define SNMP_SYSCONTACT_TOKEN        				"syscontact"
#define SNMP_SYSLOCATION_TOKEN      				"syslocation"
#define SNMP_ACCESS_TOKEN                		"access"
#define SNMP_USER_TOKEN                    	"createUser"
#define SNMP_TRAP_TOKEN                    	"trapsink"
#define SNMP_TRAP2_TOKEN                   	"trap2sink"
#define SNMP_INFORM_TOKEN                 	"informsink"
#define SNMP_ENGINEID_TOKEN               	"engineID"
#define SNMP_PACKETSIZE_TOKEN          			"packetsize"
#define SNMP_MASTER_TOKEN                		"master"
#define SNMP_MASTER_SHUTDOWN_TOKEN          "shutdown"
#define SNMP_LOGGING_OUTPUT          "debug"

int snmp_config_community_info_send( struct community_info_node * pcur_comminfo,int no_option);

int snmp_config_groupsec_relation_info_send(struct user_info_node * pcur_user,int no_option);

int snmp_config_view_info_send(struct view_info_node * pcur_view ,int no_option);

int snmp_config_group_access_info_send(struct group_info_node * pcur_groupinfo,int no_option);

int snmp_config_user_info_send(struct user_info_node * pcur_user,int no_option);

int snmp_config_trap_info_send(struct traphost_info_node * pcur_traphost,int no_option);

int snmp_config_engineid_info_send(char * engineID,int no_option);

int snmp_config_paketsize_info_send( int  packetsize,int no_option);

int snmp_config_syscontact_info_send( char * syscontact,int no_option);

int snmp_config_syslocation_info_send(char * syslocation,int no_option);

int snmp_config_master_enable_info_send(int no_option);

void snmp_config_all_info_send(int no_option);

int snmp_config_debug_output(int no_option);

#endif
