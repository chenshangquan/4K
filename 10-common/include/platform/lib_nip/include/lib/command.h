/*
 * Zebra configuration command interface routine
 * Copyright (C) 1997, 98 Kunihiro Ishiguro
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



#ifndef _ZEBRA_COMMAND_H
#define _ZEBRA_COMMAND_H

#include "lib/vector.h"
#include "lib/vty.h"

#define FILENAME_MAX_LEN 32

/* Host configuration variable */
struct host
{
  /* Host name of this router. */
  char *name;

#ifndef MOD_USER_PASS_VER_0
  /* Password for vty interface. */
  char *password;
  char *password_encrypt;

  /* Enable password */
  char *enable;
  char *enable_encrypt;
#endif
  /* System wide terminal lines. */
  int lines;

  /* Log filename. */
  char *logfile;

  /* Log stdout. */
  u_char log_stdout;

  /* Log syslog. */
  u_char log_syslog;

  /* config file name of this host */
  char *config;

  /*config file name dir*/
  char * config_dir;
  /* Flags for services */
#ifndef MOD_USER_PASS_VER_0
  int advanced;
#endif
  int encrypt;

  /* Banner configuration. */
  char *motd;
#ifdef NIP_CTN_VER_4
  int language_type;   
#endif
};

/* There are some command levels which called from command node. */
enum node_type
{
#ifdef MOD_USER_PASS_VER_0
  AUTH_USER_NODE = 1,			/* Authentication user mode of vty interface. */
  AUTH_PASS_NODE,			/* Authentication  password mode of vty interface. */
#else
  AUTH_NODE = 1,			/* Authentication mode of vty interface. */
#endif
  VIEW_NODE,			/* View node. Default mode of vty interface. */
#ifdef MOD_USER_PASS_VER_0
  AUTH_ENABLE_USER_NODE,		/* Authentication mode for change enable. */
  AUTH_ENABLE_PASS_NODE,		/* Authentication mode for change enable. */
#else
  AUTH_ENABLE_NODE,		/* Authentication mode for change enable. */
#endif
  ENABLE_NODE,			/* Enable node. */
  CONFIG_NODE,			/* Config node. Default mode of config file. */
  DEBUG_NODE,			/* Debug node. */
  AAA_NODE,			/* AAA node. */
  KEYCHAIN_NODE,		/* Key-chain node. */
  KEYCHAIN_KEY_NODE,		/* Key-chain key node. */
#ifdef MOD_QOS_VER_1
  PQ_DISC_NODE,
  CQ_DISC_NODE,
  CLASS_NODE,
  POLICY_NODE,
  POLICY_CLASS_NODE,
#endif

#ifdef MOD_DNSS_VER_0
  DNSS_NODE,
#endif
  
#ifdef MOD_DDNSC_VER_0
  DDNSC_NODE,
#endif
  
#if 1
  /* zhuzhm : for config table, route rip must do first */
  RIP_NODE,			/* RIP protocol mode node. */
  RIPNG_NODE,			/* RIPng protocol mode node. */
#endif
  CONTROLLER_E1_NODE,		/* Interface E1 mode node. */
  INTERFACE_SWITCHPORT_NODE,		/* Interface switchport mode node. */
  INTERFACE_NODE,       /* Interface mode node. */
  INTERFACE_ETH_NODE,		/* Interface ethernet mode node. */
  INTERFACE_MIN_NODE = INTERFACE_ETH_NODE, /* Minimal interface mode node. */
#ifdef MOD_INTF_ADD_FE_GE_NODE
  INTERFACE_FETH_NODE,
  INTERFACE_GETH_NODE,
#endif
  INTERFACE_SER_NODE,		/* Interface serial mode node. */
#ifdef ZHZS_ADD_VIRTUAL_INTF
  INTERFACE_VIR_NODE,		/* Interface virtaul mode (pppoe) node. */
  INTERFACE_VIR_MULTILINK_NODE,		/* Interface virtaul mode (multilink) node. */
#endif
#ifdef SUB_VLAN_ZHANKA
  INTERFACE_SUB_VLAN_NODE,   /* Interface sub vlan node */
#endif
#ifdef ZHZS_ADD_NEW_INTF_TYPE
#error "HERE, adding new interface type"
#endif
  INTERFACE_LOOP_NODE,		/* Interface loopback mode node. */
  INTERFACE_MAX_NODE = INTERFACE_LOOP_NODE, /* Maximal interface mode node. */
MULTILINK_NODE,

  ZEBRA_NODE,			/* zebra connection node. */
  TABLE_NODE,			/* rtm_table selection node. */
/*The intial step of SNTP module must after all interfaces'*/
#ifdef MOD_SNTP_VER_0
	SNTP_NODE,
#endif
#if 0
  /* zhuzhm : for config table, route rip must do first */
  RIP_NODE,			/* RIP protocol mode node. */
  RIPNG_NODE,			/* RIPng protocol mode node. */
#endif
  BGP_NODE,			/* BGP protocol mode which includes BGP4+ */
  BGP_VPNV4_NODE,		/* BGP MPLS-VPN PE exchange. */
  BGP_IPV4_NODE,		/* BGP IPv4 unicast address family.  */
  BGP_IPV4M_NODE,		/* BGP IPv4 multicast address family.  */
  BGP_IPV6_NODE,		/* BGP IPv6 address family */
  OSPF_NODE,			/* OSPF protocol mode */
  OSPF6_NODE,			/* OSPF protocol for IPv6 mode */
  MASC_NODE,			/* MASC for multicast.  */
  IRDP_NODE,			/* ICMP Router Discovery Protocol mode. */
  IP_NODE,			/* Static ip route node. */
  ACCESS_NODE,			/* Access list node. */
  PREFIX_NODE,			/* Prefix list node. */
  ACCESS_IPV6_NODE,		/* Access list node. */
  PREFIX_IPV6_NODE,		/* Prefix list node. */
  AS_LIST_NODE,			/* AS list node. */
  COMMUNITY_LIST_NODE,		/* Community list node. */
  RMAP_NODE,			/* Route map node. */
  SMUX_NODE,			/* SNMP configuration node. */
  DUMP_NODE,			/* Packet dump node. */
  FORWARDING_NODE,		/* IP forwarding node. */
  NAT_NODE,                     /* NAT node. */
  VTY_NODE,			/* Vty node. */
  ARP_NODE,
  HTTP_NODE,		/*HTTP node*/
  SNMP_NODE,		/*snmp node*/
  
  
#ifdef NIP_CTN_VER_1
  INSIDE_NODE,		/*inside node*/
#endif
#ifdef MOD_IPDBG_VER_1
  IPDEBUG_NODE,        /*ip debug node*/
#endif
  MAX_NODE          /* end of enum */    
};

#ifdef NIP_CTN_VER_4
enum language_type
{
    ENGLISH_LANGUAGE = 0,
    CHINESE_LANGUAGE,
    MAX_LANGUAGE
};
#endif

/* Node which has some commands and prompt string and configuration
   function pointer . */
struct cmd_node
{
  /* Node index. */
  enum node_type node;

  /* Prompt character at vty interface. */
  char *prompt;

  /* Is this node's configuration goes to vtysh ? */
  int vtysh;

  /*Node's configuration erase function*/
  int(*write_func)(struct vty *);

  /*Node's configuration erase function*/
  int(*erase_func)(struct vty *);

  /* Vector of this node's command list. */
  vector cmd_vector;
};

#ifdef NIP_CTN_VER_2
typedef struct mutl_node_info{
	unsigned int flag;/*(node1 node2 | node3 node4) type node has been started*/
	unsigned int begin_pos; /*the position of (node1 node2 | node3 node4) type node begin*/
	unsigned int index;/*the index of correctly node by (node1 node2 | node3 node4) type node*/
	unsigned int add_desc_list_num;/*the added number at correctly index vector*/
	unsigned int add_current_desc_list_num;/*the current added number at at correctly index vector*/
}mutl_node_info;
#endif

/* Structure of command element. */
struct cmd_element
{
  char *string;			/* Command specification by string. */
  int (*func) (struct cmd_element *, struct vty *, int, char **);
  char *doc;			/* Documentation of this command. */
  int daemon;                   /* Daemon to which this command belong. */
  vector strvec;		/* Pointing out each description vector. */
  int cmdsize;			/* Command index count. */
  char *config;			/* Configuration string */
  vector subconfig;		/* Sub configuration string */
#ifdef NIP_CTN_VER_2
  mutl_node_info mutl_info;
#endif
};

/* Command description structure. */
struct desc
{
  char *cmd;			/* Command string. */
  char *str;			/* Command's description. */
 #ifdef NIP_CTN_VER_2
 struct desc * next;
 #endif
};


#ifdef NIP_CTN_VER_3
typedef struct changed_node_info{
	char   * index_str;
	char   * des_cmdstr;
	char   * des_docstr;
}changed_node_info;

#define DEF_CHANGED_NODE(nodeinfo, indexstr)	\
	changed_node_info nodeinfo = 					\
	{											\
		indexstr,								\
		NULL,									\
		NULL									\
	}											

void collect_changed_node_info
	(
	changed_node_info * node,
	char * des_cmd,
	char * des_doc
	);

#define BEGIN_SEP_STR			"#"
#define END_SEP_STR				"$"
/*add the changed node index string */


#endif
/* Return value of the commands. */
#define CMD_SUCCESS              0
#define CMD_WARNING              1
#define CMD_ERR_NO_MATCH         2
#define CMD_ERR_AMBIGUOUS        3
#define CMD_ERR_INCOMPLETE       4
#define CMD_ERR_EXEED_ARGC_MAX   5
#define CMD_ERR_NOTHING_TODO     6
#define CMD_COMPLETE_FULL_MATCH  7
#define CMD_COMPLETE_MATCH       8
#define CMD_COMPLETE_LIST_MATCH  9
#define CMD_SUCCESS_DAEMON      10

/* Argc max counts. */
#define CMD_ARGC_MAX   25

/* Turn off these macros when uisng cpp with extract.pl */
#ifndef VTYSH_EXTRACT_PL

/* DEFUN for vty command interafce. Little bit hacky ;-). */
#define DEFUN(funcname, cmdname, cmdstr, helpstr) \
  int funcname (struct cmd_element *, struct vty *, int, char **); \
  struct cmd_element cmdname = \
  { \
    cmdstr, \
    funcname, \
    helpstr \
  }; \
  int funcname \
  (struct cmd_element *self, struct vty *vty, int argc, char **argv)

/* DEFUN_NOSH for commands that vtysh should ignore */
#define DEFUN_NOSH(funcname, cmdname, cmdstr, helpstr) \
  DEFUN(funcname, cmdname, cmdstr, helpstr)

/* DEFSH for vtysh. */
#define DEFSH(daemon, cmdname, cmdstr, helpstr) \
  struct cmd_element cmdname = \
  { \
    cmdstr, \
    NULL, \
    helpstr, \
    daemon \
  }; \

/* DEFUN + DEFSH */
#define DEFUNSH(daemon, funcname, cmdname, cmdstr, helpstr) \
  int funcname (struct cmd_element *, struct vty *, int, char **); \
  struct cmd_element cmdname = \
  { \
    cmdstr, \
    funcname, \
    helpstr, \
    daemon \
  }; \
  int funcname \
  (struct cmd_element *self, struct vty *vty, int argc, char **argv)

/* ALIAS macro which define existing command's alias. */
#define ALIAS(funcname, cmdname, cmdstr, helpstr) \
  struct cmd_element cmdname = \
  { \
    cmdstr, \
    funcname, \
    helpstr \
  };

#endif /* VTYSH_EXTRACT_PL */

/* Some macroes */
#define CMD_OPTION(S)   ((S[0]) == '[')
#define CMD_VARIABLE(S) (((S[0]) >= 'A' && (S[0]) <= 'Z') || ((S[0]) == '<'))
#define CMD_VARARG(S)   ((S[0]) == '.')
#ifdef NIP_CTN_VER_0
#define CMD_RANGE(S)	((S[0] == '<') && NULL == strstr((S), ">.<") && NULL == strstr((S), ">:<") && NULL == strstr((S), ">/<"))
#define CMD_RANGE_MULTI(s)  ((s[0] == '{') && NULL == strstr((s), ","))
#define CMD_MAC(S)     ((strcmp ((S), "A:B:C:D:E:F") == 0))
#define CMD_MULTI_RANGE(s)  ((s[0] == '{') && NULL != strstr((s), ","))
#else
#define CMD_RANGE(S)	((S[0] == '<'))
#endif

#define CMD_IPV4(S)	   ((strcmp ((S), "A.B.C.D") == 0))
#define CMD_IPV4_PREFIX(S) ((strcmp ((S), "A.B.C.D/M") == 0))
#define CMD_IPV6(S)        ((strcmp ((S), "X:X::X:X") == 0))
#define CMD_IPV6_PREFIX(S) ((strcmp ((S), "X:X::X:X/M") == 0))
#ifdef NIP_CTN_VER_5
#define CMD_INTER1(S) (NULL != strstr((S), ">.<"))
#define CMD_INTER2(S) (NULL != strstr((S), ">:<"))
#define CMD_INTER3(S) (NULL != strstr((S), ">/<") && (NULL == strstr((S), ">:<") || NULL == strstr((S), ">/<")))
#define CMD_INTER4(S) (NULL != strstr((S), ">/<") && NULL != strstr((S), ">.<"))
#define CMD_INTER5(S) (NULL != strstr((S), ">/<") && NULL != strstr((S), ">:<"))
#endif
/* Common descriptions. */
#define SHOW_STR "Show running system information|显示系统运行信息\n"
#define IP_STR "IP information|配置IP\n"
#define IPV6_STR "IPv6 information\n"
#define NO_STR "Negate a command or set its defaults|关闭某些参数开关\n"
#define CLEAR_STR "Reset functions\n"
#define RIP_STR "Routing Information Protocol(RIP) information|路由信息协议(RIP)信息\n"
#define BGP_STR "BGP information\n"
#define OSPF_STR "OSPF information\n"
#define IGMP_STR "IGMP information|IGMP信息\n"
#define IGMP_HOST_STR "IGMP host information|IGMP主机侧信息\n"
#define NEIGHBOR_STR "Specify neighbor router\n"
#define DEBUG_STR "Debugging functions (see also 'undebug')|开启调试开关\n"
#define UNDEBUG_STR "Disable debugging functions (see also 'debug')\n"
#define ROUTER_STR "Enable a routing process\n"
#define AS_STR "AS number\n"
#define MBGP_STR "MBGP information\n"
#define MATCH_STR "Match values from routing table\n"
#define SET_STR "Set values in destination routing protocol\n"
#define OUT_STR "Filter outgoing routing updates\n"
#define IN_STR  "Filter incoming routing updates\n"
#define V4NOTATION_STR "specify by IPv4 address notation(e.g. 0.0.0.0)\n"
#define OSPF6_NUMBER_STR "Specify by number\n"
#define INTERFACE_STR "Interface infomation\n"
#define IFNAME_STR "Interface name(e.g. ep0)\n"
#define IP6_STR "IPv6 Information\n"
#define OSPF6_STR "Open Shortest Path First (OSPF) for IPv6\n"
#define OSPF6_ROUTER_STR "Enable a routing process\n"
#define OSPF6_INSTANCE_STR "<1-65535> Instance ID\n"
#define SECONDS_STR "<1-65535> Seconds\n"
#define ROUTE_STR "Routing Table\n"
#define PREFIX_LIST_STR "Build a prefix list\n"
#define OSPF6_DUMP_TYPE_LIST \
"(neighbor|interface|area|lsa|zebra|config|dbex|spf|route|lsdb|redistribute|hook|asbr|prefix|abr)"

#define CONF_BACKUP_EXT ".sav"

/* IPv4 only machine should not accept IPv6 address for peer's IP
   address.  So we replace VTY command string like below. */
#ifdef HAVE_IPV6
#define NEIGHBOR_CMD       "neighbor (A.B.C.D|X:X::X:X) "
#define NO_NEIGHBOR_CMD    "no neighbor (A.B.C.D|X:X::X:X) "
#define NEIGHBOR_ADDR_STR  "Neighbor address\nIPv6 address\n"
#define NEIGHBOR_CMD2      "neighbor (A.B.C.D|X:X::X:X|WORD) "
#define NO_NEIGHBOR_CMD2   "no neighbor (A.B.C.D|X:X::X:X|WORD) "
#define NEIGHBOR_ADDR_STR2 "Neighbor address\nNeighbor IPv6 address\nNeighbor tag\n"
#else
#define NEIGHBOR_CMD       "neighbor A.B.C.D "
#define NO_NEIGHBOR_CMD    "no neighbor A.B.C.D "
#define NEIGHBOR_ADDR_STR  "Neighbor address\n"
#define NEIGHBOR_CMD2      "neighbor (A.B.C.D|WORD) "
#define NO_NEIGHBOR_CMD2   "no neighbor (A.B.C.D|WORD) "
#define NEIGHBOR_ADDR_STR2 "Neighbor address\nNeighbor tag\n"
#endif /* HAVE_IPV6 */
/* Command vector which includes some level of command lists. Normally
   each daemon maintains each own cmdvec. */
extern vector cmdvec;

/* Host information structure. */
extern struct host host;

#define CHANGED_NODE_IF_ALL			"#ALL_IF_NAME_NUM$"
#define CHANGED_NODE_IF_ETH			"#ETH_IF_NAME_NUM$"
#define CHANGED_NODE_IF_FETH		"#FETH_IF_NAME_NUM$"
#define CHANGED_NODE_IF_GETH		"#GETH_IF_NAME_NUM$"
#ifdef SUB_VLAN_ZHANKA
#define CHANGED_NODE_IF_ETH_ALL		"#ALL_ETH_IF_NAME_NUM$"
#endif /* SUB_VLAN_ZHANKA */
#define CHANGED_NODE_IF_SER_V35		"#SER_V35_IF_NAME_NUM$"
#define CHANGED_NODE_IF_SER_E1		"#SER_E1_IF_NAME_NUM$"
#define CHANGED_NODE_IF_LO			"#LOOPBACK_IF_NAME_NUM$"
#define CHANGED_NODE_IF_VIR_MP		"#VIR_MP_IF_NAME_NUM$"
#define CHANGED_NODE_IF_VIR_PPPOE	"#VIR_PPPOE_IF_NAME_NUM$"
extern changed_node_info cni_if_all;
extern changed_node_info cni_if_eth;
extern changed_node_info cni_if_feth;
extern changed_node_info cni_if_geth;
#ifdef SUB_VLAN_ZHANKA
extern changed_node_info cni_if_eth_all;
#endif /* SUB_VLAN_ZHANKA */
extern changed_node_info cni_if_ser_v35;
extern changed_node_info cni_if_ser_e1;
extern changed_node_info cni_if_lo;
extern changed_node_info cni_if_vir_mp;
extern changed_node_info cni_if_vir_pppoe;

#ifdef NIP_CTN_VER_5
extern unsigned char inter_flag;
extern unsigned char inter_flag1;
extern char inter_cmd_dst[128];
extern char inter_cmd_src[128];
#endif
/* Prototypes. */
typedef void (*IF_NODE_FOREACH_FUNCPTR)(enum node_type node, void *param);
void if_node_foreach (IF_NODE_FOREACH_FUNCPTR func, void *param);

void install_node (struct cmd_node *, int (*) (struct vty *), int (*) (struct vty *));
void install_default (enum node_type);
void install_element (enum node_type, struct cmd_element *);
void sort_node ();

char *argv_concat (char **, int, int);
vector cmd_make_strvec (char *);
void cmd_free_strvec (vector);
vector cmd_describe_command ();
char **cmd_complete_command ();
char *cmd_prompt (enum node_type);
int config_from_file (struct vty*, struct vty *, FILE *);
int cmd_execute_command (vector, struct vty *, struct cmd_element **);
int cmd_execute_command_strict (vector, struct vty *, struct cmd_element **);
void config_replace_string (struct cmd_element *, char *, ...);
void cmd_init (int);

/* Export typical functions. */
extern struct cmd_element config_end_cmd;
extern struct cmd_element config_exit_cmd;
extern struct cmd_element config_help_cmd;
extern struct cmd_element config_list_cmd;
int config_exit (struct cmd_element *, struct vty *, int, char **);
int config_help (struct cmd_element *, struct vty *, int, char **);
char *host_config_file ();
void host_config_set (char *);
void host_config_dir_set (char *pathname);
void host_config_unset (char *);
void host_config_dir_unset (char *);
int config_info_memory_erase(struct vty * vty);
int config_info_write_file(struct vty * vty,char * config_file);
void cmd_inter_help(char * dst, char * src, char ch);
void cmd_inter_help_ex(char * dst, char * src, char ch1, char ch2);
#endif /* _ZEBRA_COMMAND_H */
