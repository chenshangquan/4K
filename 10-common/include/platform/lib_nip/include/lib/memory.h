#ifndef _MEMORY_LIB_H
#define _MEMORY_LIB_H
/**
 *  ____________________________________
 * |               |                    |
 * | mtype_header_t|actual need alloced |
 * |_______________|____________________|
 *
 */
#include <sys/types.h>
#include <stdio.h>
#include <lib/thread.h>
#include <pthread.h>

#include "lib/mm_shm.h"
#include "lib/mm_config.h"
#include <g_module.h>


struct vty;
struct mm_message
{
  	int 	key;
  	char	*str;
};

/* For pretty printing of memory allocate information. */
struct memory_list
{
	int index;
	char *format;
};

/**
  * If you add a memory type , MTYPE_XXX_XXX, 
  * you should add MM_MESSAGE_0 && MM_MESSAGE_1 below for its description
  * */

enum
{
  MTYPE_ZERO =0,
  MTYPE_TMP,
  MTYPE_STRVEC,
  MTYPE_VECTOR,
  MTYPE_VECTOR_INDEX,
  MTYPE_LINK_LIST,
  MTYPE_LINK_NODE,
  MTYPE_THREAD,
  MTYPE_THREAD_MASTER,
  MTYPE_VTY,
  MTYPE_VTY_HIST,
  MTYPE_VTY_OUT_BUF,
  MTYPE_IF,
  MTYPE_IF_DESC,
  MTYPE_CONNECTED,
  MTYPE_BUFFER,
  MTYPE_BUFFER_DATA,
  MTYPE_STREAM,
  MTYPE_STREAM_DATA,
  MTYPE_STREAM_FIFO,
  MTYPE_PREFIX,
  MTYPE_PREFIX_IPV4,
  MTYPE_PREFIX_IPV6,
  MTYPE_HASH,
  MTYPE_HASH_INDEX,
  MTYPE_HASH_BACKET,
  MTYPE_ROUTE_TABLE,
  MTYPE_ROUTE_NODE,
  MTYPE_ACCESS_LIST,
  MTYPE_ACCESS_LIST_STR,
  MTYPE_ACCESS_FILTER,
  MTYPE_PREFIX_LIST,
  MTYPE_PREFIX_LIST_STR,
  MTYPE_PREFIX_LIST_ENTRY,
  MTYPE_ROUTE_MAP,
  MTYPE_ROUTE_MAP_NAME,
  MTYPE_ROUTE_MAP_INDEX,
  MTYPE_ROUTE_MAP_RULE,
  MTYPE_ROUTE_MAP_RULE_STR,
  MTYPE_ROUTE_MAP_COMPILED,

  MTYPE_RIB,
  MTYPE_DISTRIBUTE,
  MTYPE_ZLOG,
  MTYPE_TIMER,
  MTYPE_ZCLIENT,
  MTYPE_NEXTHOP,
  MTYPE_RTADV_PREFIX,
  MTYPE_IF_RMAP,
  MTYPE_SOCKUNION,
  MTYPE_STATIC_IPV4,
  MTYPE_STATIC_IPV6,

  MTYPE_DESC,
  MTYPE_KEYCHAIN,
  MTYPE_KEY,

  MTYPE_OSPF_TOP ,
  MTYPE_OSPF_AREA,
  MTYPE_OSPF_AREA_RANGE,
  MTYPE_OSPF_NETWORK,
  MTYPE_OSPF_NEIGHBOR_STATIC,
  MTYPE_OSPF_IF,
  MTYPE_OSPF_NEIGHBOR,
  MTYPE_OSPF_ROUTE,
  MTYPE_OSPF_TMP,
  MTYPE_OSPF_LSA,
  MTYPE_OSPF_LSA_DATA,
  MTYPE_OSPF_LSDB,
  MTYPE_OSPF_PACKET,
  MTYPE_OSPF_FIFO,
  MTYPE_OSPF_VERTEX,
  MTYPE_OSPF_NEXTHOP,
  MTYPE_OSPF_PATH,
  MTYPE_OSPF_VL_DATA,
  MTYPE_OSPF_CRYPT_KEY,
  MTYPE_OSPF_EXTERNAL_INFO,
  MTYPE_OSPF_MESSAGE,
  MTYPE_OSPF_DISTANCE,
  MTYPE_OSPF_IF_INFO,
  MTYPE_OSPF_IF_PARAMS,

  MTYPE_OSPF6_TOP,
  MTYPE_OSPF6_AREA,
  MTYPE_OSPF6_IF,
  MTYPE_OSPF6_NEIGHBOR,
  MTYPE_OSPF6_ROUTE,
  MTYPE_OSPF6_PREFIX,
  MTYPE_OSPF6_MESSAGE,
  MTYPE_OSPF6_LSA,
  MTYPE_OSPF6_LSA_SUMMARY,
  MTYPE_OSPF6_LSDB,
  MTYPE_OSPF6_VERTEX,
  MTYPE_OSPF6_SPFTREE,
  MTYPE_OSPF6_NEXTHOP,
  MTYPE_OSPF6_EXTERNAL_INFO,
  MTYPE_OSPF6_OTHER,

  MTYPE_BGP  ,
  MTYPE_AS_SEG,
  MTYPE_AS_STR,
  MTYPE_AS_PATH,
  MTYPE_CLUSTER,
  MTYPE_CLUSTER_VAL,
  MTYPE_ATTR,
  MTYPE_TRANSIT,
  MTYPE_TRANSIT_VAL,

  MTYPE_BGP_PEER,
  MTYPE_PEER_GROUP,
  MTYPE_PEER_DESC,
  MTYPE_PEER_UPDATE_SOURCE,
  MTYPE_BGP_STATIC,
  MTYPE_BGP_AGGREGATE,
  MTYPE_BGP_CONFED_LIST,
  MTYPE_BGP_NEXTHOP_CACHE,
  MTYPE_BGP_DAMP_INFO,
  MTYPE_BGP_DAMP_ARRAY,
  MTYPE_BGP_ANNOUNCE,
  MTYPE_BGP_ATTR_QUEUE,
  MTYPE_BGP_ROUTE_QUEUE,
  MTYPE_BGP_DISTANCE,
  MTYPE_BGP_ROUTE,
  MTYPE_BGP_TABLE,
  MTYPE_BGP_NODE,
  MTYPE_BGP_ADVERTISE_ATTR,
  MTYPE_BGP_ADVERTISE,
  MTYPE_BGP_ADJ_IN,
  MTYPE_BGP_ADJ_OUT,
  MTYPE_BGP_REGEXP,
  MTYPE_AS_FILTER,
  MTYPE_AS_FILTER_STR,
  MTYPE_AS_LIST,

  MTYPE_COMMUNITY,
  MTYPE_COMMUNITY_VAL,
  MTYPE_COMMUNITY_STR,

  MTYPE_ECOMMUNITY,
  MTYPE_ECOMMUNITY_VAL,
  MTYPE_ECOMMUNITY_STR,

  /* community-list and extcommunity-list.  */
  MTYPE_COMMUNITY_LIST_HANDLER,
  MTYPE_COMMUNITY_LIST,
  MTYPE_COMMUNITY_LIST_NAME,
  MTYPE_COMMUNITY_LIST_ENTRY,
  MTYPE_COMMUNITY_LIST_CONFIG,

  MTYPE_ZCLIENT_IF,
  MTYPE_ZCLIENT_CONNECTED,
  MTYPE_ZCLIENT_IF_TABLE,
  MTYPE_ZCLIENT_LIST,
  MTYPE_RIP ,
  MTYPE_RIP_INTERFACE,
  MTYPE_RIP_DISTANCE,
  MTYPE_RIP_OFFSET_LIST,
  MTYPE_RIP_INFO,
  MTYPE_RIP_PEER,
  MTYPE_RIP_CONFIG,
  MTYPE_RIP_TIMER_LIST,
  MTYPE_RIP_TIMER,
  MTYPE_RIP_IF_CONFIG,

  MTYPE_VRF,
  MTYPE_VRF_NAME,

  MTYPE_DDNSC_IF_INFO,
  MTYPE_DDNSC_UPDATE_REQ,
  MTYPE_DDNSC_CFG_IF,
  MTYPE_DNSS_LOOK_REQ,

  MTYPE_PING,
  MTYPE_TRACEROUTE,
  MTYPE_WEBSERVER,

  #ifdef MOD_DHCPC_VER_1_1
  /*dhcp module */ 
  MTYPE_DHCP_INTF_CFG,
  MTYPE_DHCP_PARAMS,
  MTYPE_DHCP_OPTIONS, 
  MTYPE_DHCP_TSD, 
 #endif

 #ifdef MOD_ACL_VER_0_2
 MTYPE_ACL_IPT,
 MTYPE_ACL_PROC,
 MTYPE_ACL_LIB,
 MTYPE_FILTER,
 #endif

 #ifdef MOD_FTP_SERVER_VER_1_1
 MTYPE_FTP_LISTENER,
 MTYPE_FTP_DATA_TRANS,
 #endif
 
/*snmp memory module*/
  MTYPE_SNMP,

 /*user name memory module*/
  MTYPE_USERNAME,
  
  MTYPE_RIPNG_ROUTE,
  MTYPE_RIPNG_AGGREGATE,
 
  MTYPE_VTYSH_CONFIG ,
  MTYPE_VTYSH_CONFIG_LINE,
  MTYPE_MEM,
  MTYPE_MEM_STRING,
  MTYPE_MEM_2,
  MTYPE_MEM_3,
  MTYPE_MEM_4,
  MTYPE_MEM_5,
  MTYPE_MEM_6,
  MTYPE_MEM_MAX,
  MTYPE_IOVEC,
  MTYPE_CFG_FILE,
  MTYPE_NOTIFY_MC,
  MTYPE_ZMSG,
  MTYPE_TELNET,
  MTYPE_ZSERV,
  /*changed node memory module*/
  MTYPE_CHANGED_NODE,
#ifdef MOD_PPP_VER_5
  MTYPE_PPP_WORDLIST,
  MTYPE_PPP_PERMED_IP,
  MTYPE_PPP_PAMRESP,
  MTYPE_PPP_TEMP,
  MTYPE_PPP_FRAME,
  MTYPE_PPP_PACKET,
  MTYPE_PPP_INITSTRING,
  MTYPE_PPP_CONFIG_INFO,
  MTYPE_PPP_DBDATA,
  MTYPE_PPP_OPTIONPATH,
  MTYPE_PPP_OPTIONVALUE,
  MTYPE_PPP_OPTIONLIST,
  MTYPE_PPP_TIMEOUT,
  MTYPE_PPP_SUBPROCESS,
  MTYPE_PPP_NOTIFIER,
  MTYPE_PPP_GLOBAL,
  MTYPE_PPP_GLOBAL_PRIV,
  MTYPE_PPP_SCRIPT_ENV,
  MTYPE_PPP_SCRIPTENV_STR,
  MTYPE_PPP_TDB_GENERAL,
  MTYPE_PPP_TDB_CONTEXT, 
  MTYPE_PPP_TDB_NAME,
  MTYPE_PPP_TDB_MAP,
  MTYPE_PPP_TDB_LOCKED,

  MTYPE_PPPOE_GENERAL,
  MTYPE_PPPOE_CONNECTION,
  MTYPE_PPP_API,
#endif
#ifdef PPP_AND_PPPOE_MEM_ZHANKA
  MTYPE_MP_TMP,
#endif /* PPP_AND_PPPOE_MEM_ZHANKA */
#ifdef HDLC_ZHANKA_INIT
  MTYPE_HDLC_INFO,
#endif 
#ifdef SUB_VLAN_ZHANKA
  MTYPE_SUB_VLAN_INFO,
#endif 
#ifdef MOD_IPDBG_VER_1
  MTYPE_IPDEBUG_BPF,
  MTYPE_IPDEBUG_HANDLE,
  MTYPE_IPDEBUG_RCVBUF,
#endif
#ifdef MOD_IGMP_HOST_VER_0
  MTYPE_IPMC_INFO,
#endif
#ifdef MOD_QOS_VER_1
  MTYPE_CLASS_FILTER,
  MTYPE_CLASS_MAP,
  MTYPE_POLICY_CLASS_MAP,
  MTYPE_POLICY_MAP,
  MTYPE_QDISC_RULE,
  MTYPE_QDISC,
#endif
  MTYPE_MAX
};

#ifdef MOD_MEMORY_LIB
/* If you add a memory type ,you should add MM_MESSAGE_0 && MM_MESSAGE_1 below */
#ifdef MM_MESSAGE_0

struct mm_message mstr [] =
{
	{ MTYPE_TMP, "tmp memory" },
	{ MTYPE_STRVEC, "strvec" },
	{ MTYPE_LINK_LIST, "link list" },
	{ MTYPE_LINK_NODE, "link node" },
	{ MTYPE_VTY, "vty" },
	{ MTYPE_VTY_HIST, "vty hist" },
	{ MTYPE_VTY_OUT_BUF, "vty out buf" },
	{ MTYPE_THREAD, "thread" },
	{ MTYPE_THREAD_MASTER, "thread_master" },
	{ MTYPE_VECTOR, "vector" },
	{ MTYPE_VECTOR_INDEX, "vector_index" },
	{ MTYPE_IF, "interface" },
	{ MTYPE_BUFFER, "buffer" },
	{ MTYPE_STREAM, "stream" },
	{ MTYPE_STREAM_DATA, "stream data" },
	{ MTYPE_STREAM_FIFO, "stream fifo" },
	{ MTYPE_STREAM, "stream" },
	{ MTYPE_STREAM_DATA, "stream data" },
	{ MTYPE_STREAM_FIFO, "stream fifo" },
	{ MTYPE_PREFIX, "prefix" },
	{ MTYPE_HASH, "hash" },

	{ MTYPE_ZLOG, "zlog" },
	{ MTYPE_KEY, "key" },

    {MTYPE_DDNSC_IF_INFO, "ddnsclient if info"},
	{MTYPE_DDNSC_UPDATE_REQ, "ddns update request"},
	{MTYPE_DDNSC_CFG_IF, "ddns config if"},
    {MTYPE_DNSS_LOOK_REQ, "dnsser query request"},

	{MTYPE_PING, "ping state"},
    {MTYPE_TRACEROUTE, "traceroute state"},
	{MTYPE_TELNET,"telnet state"},
#ifdef MOD_PPP_VER_5
	{MTYPE_PPP_WORDLIST,"ppp wordlist"},
	{MTYPE_PPP_PERMED_IP,"ppp permitted ip"},
	{MTYPE_PPP_PAMRESP,"ppp pam_response"},
	{MTYPE_PPP_FRAME,"ppp frame"},
	{MTYPE_PPP_PACKET,"ppp packet"},
	{MTYPE_PPP_INITSTRING,"ppp initstring"},
	{MTYPE_PPP_CONFIG_INFO,"ppp config_info"},
	{MTYPE_PPP_DBDATA,"ppp db data"},
	{MTYPE_PPP_OPTIONPATH,"ppp options path"},
	{MTYPE_PPP_OPTIONVALUE,"ppp options value"},
	{MTYPE_PPP_OPTIONLIST,"ppp options list"},
	{MTYPE_PPP_TIMEOUT,"ppp timeout callout"},
	{MTYPE_PPP_SUBPROCESS,"ppp subprocess"},
	{MTYPE_PPP_NOTIFIER,"ppp notifier"},
	{MTYPE_PPP_GLOBAL,"ppp global"},
	{MTYPE_PPP_GLOBAL_PRIV,"ppp global priv"},
	{MTYPE_PPP_SCRIPT_ENV,"ppp script env"},
	{MTYPE_PPP_SCRIPTENV_STR,"ppp script env string"},
	{MTYPE_PPPOE_GENERAL,"pppoe general"},
	{MTYPE_PPPOE_CONNECTION,"pppoe connection"},
	{MTYPE_PPP_API,"ppp api"},
	{MTYPE_MP_TMP,"MP temp"},
#endif
#ifdef HDLC_ZHANKA_INIT
    {MTYPE_HDLC_INFO,"HDLC info struct"},
#endif 
#ifdef SUB_VLAN_ZHANKA
	{MTYPE_SUB_VLAN_INFO,"Sub vlan info struct"},
#endif /* SUB_VLAN_ZHANKA */ 
#ifdef MOD_IPDBG_VER_1
	{MTYPE_IPDEBUG_BPF, "IP debug bfp"},
	{MTYPE_IPDEBUG_RCVBUF, "IP debug recvbuf"},
	{MTYPE_IPDEBUG_HANDLE, "IP debug handle"},
#endif
#ifdef MOD_IGMP_HOST_VER_0
	{MTYPE_IPMC_INFO, "IP muticast address info struct"},
#endif
#ifdef MOD_QOS_VER_1
	{MTYPE_CLASS_FILTER, "QoS class filter"},
	{MTYPE_CLASS_MAP, "QoS class map"},
	{MTYPE_POLICY_MAP, "QoS policy map"},
	{MTYPE_POLICY_CLASS_MAP, "QoS policy class map"},
	{MTYPE_QDISC_RULE, "QoS queue disc rule"},
	{MTYPE_QDISC, "QoS queue disc"},
#endif
#ifdef MOD_FTP_SERVER_VER_1_1
    { MTYPE_FTP_LISTENER, "FTP server listener"},
    { MTYPE_FTP_DATA_TRANS, "FTP data link"},
#endif
    { 0, NULL },
};

#endif

#ifdef MM_MESSAGE_1
/*snmp memory module*/
struct memory_list memory_list_snmp[] =
{
       {MTYPE_SNMP, "snmp module"},
       { -1, NULL },
};

struct memory_list memory_list_thread[] =
{
       {MTYPE_THREAD, "thread"},
       {-1, NULL },
};

/*snmp memory module*/
struct memory_list memory_list_username[] =
{
       {MTYPE_USERNAME, "username module"},
       { -1, NULL },
};

struct memory_list memory_list_ddnsc[] =
{
    {MTYPE_DDNSC_IF_INFO, "ddnsclient if info"},
	{MTYPE_DDNSC_UPDATE_REQ, "ddns update request"},
	{MTYPE_DDNSC_CFG_IF, "ddns config if"},
    { -1, NULL },
};

struct memory_list memory_list_dnsser[] =
{
        {MTYPE_DNSS_LOOK_REQ, "dnsser query request"},
        { -1, NULL },
};
struct memory_list memory_list_http[] =
{
       {MTYPE_WEBSERVER, "Http Webserver"},
       { -1, NULL },
};

struct memory_list memory_list_ping[] =
{
        {MTYPE_PING, "ping state"},
        { -1, NULL },
};

struct memory_list memory_list_trace[] =
{
        {MTYPE_TRACEROUTE, "traceroute state"},
        { -1, NULL },
};

struct memory_list memory_list_telnet[] =
{
        {MTYPE_TELNET, "telnet state"},
        { -1, NULL },
};

struct memory_list memory_list_timer[] = 
{
	{MTYPE_TIMER, "timer"},
	{-1, NULL },
};

struct memory_list memory_list_lib[] =
{
  { MTYPE_TMP,                "Temporary memory" },
  { MTYPE_ROUTE_TABLE,        "Route table     " },
  { MTYPE_ROUTE_NODE,         "Route node      " },
  { MTYPE_RIB,                "RIB             " },
  { MTYPE_NEXTHOP,            "Nexthop         " },
  { MTYPE_LINK_LIST,          "Link List       " },
  { MTYPE_LINK_NODE,          "Link Node       " },
  { MTYPE_HASH,               "Hash            " },
  { MTYPE_HASH_BACKET,        "Hash Bucket     " },
  { MTYPE_ACCESS_LIST,        "Access List     " },
  { MTYPE_ACCESS_LIST_STR,    "Access List Str " },
  { MTYPE_ACCESS_FILTER,      "Access Filter   " },
  { MTYPE_PREFIX_LIST,        "Prefix List     " },
  { MTYPE_PREFIX_LIST_STR,    "Prefix List Str " },
  { MTYPE_PREFIX_LIST_ENTRY,  "Prefix List Entry "},
  { MTYPE_ROUTE_MAP,          "Route map       " },
  { MTYPE_ROUTE_MAP_NAME,     "Route map name  " },
  { MTYPE_ROUTE_MAP_INDEX,    "Route map index " },
  { MTYPE_ROUTE_MAP_RULE,     "Route map rule  " },
  { MTYPE_ROUTE_MAP_RULE_STR, "Route map rule str" },
  { MTYPE_DESC,               "Command desc    " },
  { MTYPE_BUFFER,             "Buffer          " },
  { MTYPE_BUFFER_DATA,        "Buffer data     " },
  { MTYPE_STREAM,             "Stream          " },
  { MTYPE_KEYCHAIN,           "Key chain       " },
  { MTYPE_KEY,                "Key             " },
  { MTYPE_VTY,                "VTY             " },
  { MTYPE_TIMER,              "TIMER module   " },
  { -1, NULL }
};

struct memory_list memory_list_route[] =
{
  { MTYPE_ROUTE_TABLE,        "Route table     " },
  { MTYPE_STATIC_IPV4,         "Static route      " },
  { MTYPE_ROUTE_NODE,         "Route node      " },
  { MTYPE_RIB,                "RIB             " },
  { MTYPE_NEXTHOP,            "Nexthop         " },
  { -1, NULL }
};

struct memory_list memory_list_bgp[] =
{
  { MTYPE_BGP_PEER,               "BGP peer" },
  { MTYPE_ATTR,                   "BGP attribute" },
  { MTYPE_AS_PATH,                "BGP aspath" },
  { MTYPE_AS_SEG,                 "BGP aspath seg" },
  { MTYPE_AS_STR,                 "BGP aspath str" },
  { 0, NULL },
  { MTYPE_BGP_TABLE,              "BGP table" },
  { MTYPE_BGP_NODE,               "BGP node" },
  { MTYPE_BGP_ADVERTISE_ATTR,     "BGP adv attr" },
  { MTYPE_BGP_ADVERTISE,          "BGP adv" },
  { MTYPE_BGP_ADJ_IN,             "BGP adj in" },
  { MTYPE_BGP_ADJ_OUT,            "BGP adj out" },
  { 0, NULL },
  { MTYPE_AS_LIST,                "BGP AS list" },
  { MTYPE_AS_FILTER,              "BGP AS filter" },
  { MTYPE_AS_FILTER_STR,          "BGP AS filter str" },
  { 0, NULL },
  { MTYPE_COMMUNITY,              "community" },
  { MTYPE_COMMUNITY_VAL,          "community val" },
  { MTYPE_COMMUNITY_STR,          "community str" },
  { 0, NULL },
  { MTYPE_ECOMMUNITY,             "extcommunity" },
  { MTYPE_ECOMMUNITY_VAL,         "extcommunity val" },
  { MTYPE_ECOMMUNITY_STR,         "extcommunity str" },
  { 0, NULL },
  { MTYPE_COMMUNITY_LIST,         "community-list" },
  { MTYPE_COMMUNITY_LIST_NAME,    "community-list name" },
  { MTYPE_COMMUNITY_LIST_ENTRY,   "community-list entry" },
  { MTYPE_COMMUNITY_LIST_CONFIG,  "community-list config" },
  { 0, NULL },
  { MTYPE_CLUSTER,                "Cluster list" },
  { MTYPE_CLUSTER_VAL,            "Cluster list val" },
  { 0, NULL },
  { MTYPE_TRANSIT,                "BGP transit attr" },
  { MTYPE_TRANSIT_VAL,            "BGP transit val" },
  { 0, NULL },
  { MTYPE_BGP_DISTANCE,           "BGP distance" },
  { MTYPE_BGP_NEXTHOP_CACHE,      "BGP nexthop" },
  { MTYPE_BGP_CONFED_LIST,        "BGP confed list" },
  { MTYPE_PEER_UPDATE_SOURCE,     "peer update if" },
  { MTYPE_BGP_DAMP_INFO,          "Dampening info" },
  { MTYPE_BGP_REGEXP,             "BGP regexp" },
  { -1, NULL }
};

struct memory_list memory_list_rip[] =
{
  { MTYPE_RIP,                "RIP structure   " },
  { MTYPE_RIP_INFO,           "RIP route info  " },
  { MTYPE_RIP_INTERFACE,      "RIP interface   " },
  { MTYPE_RIP_PEER,           "RIP peer        " },
  { MTYPE_RIP_OFFSET_LIST,    "RIP offset list " },
  { MTYPE_RIP_DISTANCE,       "RIP distance    " },
  { MTYPE_RIP_IF_CONFIG,        "RIP interface config"},
  { -1, NULL }
};

struct memory_list memory_list_interface[] =
{
  { MTYPE_IF,                "interface" },
  { MTYPE_IF_DESC, 	"interface description"},
  { MTYPE_CONNECTED,   "connected" },
  { -1, NULL }
};

struct memory_list memory_list_zebra[] =
{
  { MTYPE_ZCLIENT_IF,                "Zclient interface" },
  { MTYPE_ZCLIENT_CONNECTED,           "Zclient connected" },
  { MTYPE_ZCLIENT_IF_TABLE,      "Zclient if table" },
  { MTYPE_ZCLIENT_LIST,           "Zclient list" },
  { -1, NULL }
};

struct memory_list memory_list_ospf[] =
{
  { MTYPE_OSPF_TOP,           "OSPF top        " },
  { MTYPE_OSPF_AREA,          "OSPF area       " },
  { MTYPE_OSPF_AREA_RANGE,    "OSPF area range " },
  { MTYPE_OSPF_NETWORK,       "OSPF network    " },
#ifdef NBMA_ENABLE
  { MTYPE_OSPF_NEIGHBOR_STATIC,"OSPF static nbr " },
#endif  /* NBMA_ENABLE */
  { MTYPE_OSPF_IF,            "OSPF interface  " },
  { MTYPE_OSPF_NEIGHBOR,      "OSPF neighbor   " },
  { MTYPE_OSPF_ROUTE,         "OSPF route      " },
  { MTYPE_OSPF_TMP,           "OSPF tmp mem    " },
  { MTYPE_OSPF_LSA,           "OSPF LSA        " },
  { MTYPE_OSPF_LSA_DATA,      "OSPF LSA data   " },
  { MTYPE_OSPF_LSDB,          "OSPF LSDB       " },
  { MTYPE_OSPF_PACKET,        "OSPF packet     " },
  { MTYPE_OSPF_FIFO,          "OSPF FIFO queue " },
  { MTYPE_OSPF_VERTEX,        "OSPF vertex     " },
  { MTYPE_OSPF_NEXTHOP,       "OSPF nexthop    " },
  { MTYPE_OSPF_PATH,	      "OSPF path       " },
  { MTYPE_OSPF_VL_DATA,       "OSPF VL data    " },
  { MTYPE_OSPF_CRYPT_KEY,     "OSPF crypt key  " },
  { MTYPE_OSPF_EXTERNAL_INFO, "OSPF ext. info  " },
  { MTYPE_OSPF_DISTANCE,      "OSPF distance   " },
  { MTYPE_OSPF_IF_INFO,       "OSPF if info    " },
  { MTYPE_OSPF_IF_PARAMS,     "OSPF if params  " },
  { -1, NULL },
};

struct memory_list memory_list_ospf6[] =
{
  { MTYPE_OSPF6_TOP,          "OSPF6 top         " },
  { MTYPE_OSPF6_AREA,         "OSPF6 area        " },
  { MTYPE_OSPF6_IF,           "OSPF6 interface   " },
  { MTYPE_OSPF6_NEIGHBOR,     "OSPF6 neighbor    " },
  { MTYPE_OSPF6_ROUTE,        "OSPF6 route       " },
  { MTYPE_OSPF6_PREFIX,       "OSPF6 prefix      " },
  { MTYPE_OSPF6_MESSAGE,      "OSPF6 message     " },
  { MTYPE_OSPF6_LSA,          "OSPF6 LSA         " },
  { MTYPE_OSPF6_LSA_SUMMARY,  "OSPF6 LSA summary " },
  { MTYPE_OSPF6_LSDB,         "OSPF6 LSA database" },
  { MTYPE_OSPF6_VERTEX,       "OSPF6 vertex      " },
  { MTYPE_OSPF6_SPFTREE,      "OSPF6 SPF tree    " },
  { MTYPE_OSPF6_NEXTHOP,      "OSPF6 nexthop     " },
  { MTYPE_OSPF6_EXTERNAL_INFO,"OSPF6 ext. info   " },
  { MTYPE_OSPF6_OTHER,        "OSPF6 other       " },
  { -1, NULL },
};

#ifdef PPP_AND_PPPOE_MEM_ZHANKA
struct memory_list memory_list_ppp[] = 
{
  {MTYPE_PPP_WORDLIST,        "ppp wordlist"},
  {MTYPE_PPP_PERMED_IP,       "ppp permitted ip"},
  {MTYPE_PPP_PAMRESP,		  "ppp pam_response"},
  {MTYPE_PPP_FRAME,           "ppp frame"},
  {MTYPE_PPP_PACKET,          "ppp packet"},
  {MTYPE_PPP_INITSTRING,      "ppp initstring"},
  {MTYPE_PPP_CONFIG_INFO,     "ppp config_info"},
  {MTYPE_PPP_DBDATA,          "ppp db data"},
  {MTYPE_PPP_OPTIONPATH,      "ppp options path"},
  {MTYPE_PPP_OPTIONVALUE,     "ppp options value"},
  {MTYPE_PPP_OPTIONLIST,      "ppp options list"},
  {MTYPE_PPP_TIMEOUT,         "ppp timeout callout"},
  {MTYPE_PPP_SUBPROCESS,      "ppp subprocess"},
  {MTYPE_PPP_NOTIFIER,        "ppp notifier"},
  {MTYPE_PPP_GLOBAL,          "ppp global"},
  {MTYPE_PPP_GLOBAL_PRIV,     "ppp global priv"},
  {MTYPE_PPP_SCRIPT_ENV,      "ppp script env"},
  {MTYPE_PPP_SCRIPTENV_STR,   "ppp script env string"},
  {MTYPE_PPP_API,             "ppp api"},
  { -1, NULL },	
};

struct memory_list memory_list_pppoe[] = 
{
  {MTYPE_PPPOE_GENERAL,       "pppoe general"},
  {MTYPE_PPPOE_CONNECTION,    "pppoe connection"},
  { -1, NULL },	
};

struct memory_list memory_list_mp[] = 
{
  {MTYPE_MP_TMP,               "MP temp"},
  { -1, NULL },	
};
#endif /* ppp_AND_PPPOE_MEM_ZHANKA */
#ifdef HDLC_ZHANKA_INIT
struct memory_list memory_list_hdlc[] = 
{
  {MTYPE_HDLC_INFO,           "HDLC info struct"},
  { -1, NULL },	
};
#endif 

#ifdef SUB_VLAN_ZHANKA
struct memory_list memory_list_sub_vlan[] = 
{
  {MTYPE_SUB_VLAN_INFO,           "Sub vlan info struct"},
  { -1, NULL },	
};
#endif /* SUB_VLAN_ZHANKA */

#ifdef MOD_IPDBG_VER_1
struct memory_list memory_list_ipdbg[] = 
{
  {MTYPE_IPDEBUG_BPF,             "IP debug bpf module"},
  {MTYPE_IPDEBUG_RCVBUF,          "IP debug recvbuf"},
  {MTYPE_IPDEBUG_HANDLE,          "IP debug handle"},
  {-1, NULL},
};
#endif

struct memory_list memory_list_separator[] =
{
  { 0, NULL},
  {-1, NULL}
};

/* for my show mem test */
struct memory_list memory_list_mem[]=
{
	{ MTYPE_MEM_STRING,	"PPP String"},
	{ MTYPE_MEM_2,		"PPP 2"},
	{ MTYPE_MEM_3,		"PPP 3"},
	{ MTYPE_MEM_4,		"PPP 4"},
	{ MTYPE_MEM_5,		"PPP 4"},
	{ MTYPE_MEM_MAX,	"PPP Max"},
	{ -1,NULL}
};

#ifdef MOD_DHCPC_VER_1_1
struct memory_list memory_list_dhcp[]=
{
	{MTYPE_DHCP_INTF_CFG, "DHCP interface"},
	{MTYPE_DHCP_PARAMS, "DHCP params"},
	{MTYPE_DHCP_OPTIONS, "DHCP options"},
	{MTYPE_DHCP_TSD, "DHCP TSD"},
	{-1, NULL}
};
#endif

#ifdef MOD_ACL_VER_0_2
struct memory_list memory_list_acl[]=
{
	{MTYPE_ACL_IPT, "ACL ipt"},
	{MTYPE_ACL_PROC, "ACL proc"},
	{MTYPE_ACL_LIB, "ACL lib"},
	{MTYPE_FILTER, "FILTER"},
	{-1, NULL}
};
#endif

#ifdef MOD_FTP_SERVER_VER_1_1
struct memory_list memory_list_ftp[]=
{
    { MTYPE_FTP_LISTENER, "FTP server listener"},
    { MTYPE_FTP_DATA_TRANS, "FTP data link"},
	{-1, NULL}
};
#endif


#ifdef MOD_IGMP_HOST_VER_0
struct memory_list memory_list_igmp_cfg[]=
{
	{MTYPE_IPMC_INFO, "IGMP configed group"},
	{-1, NULL}
};
#endif

#ifdef MOD_QOS_VER_1
struct memory_list memory_list_qos[] = 
{
	{MTYPE_CLASS_FILTER, "QoS class filter"},
	{MTYPE_CLASS_MAP, "QoS class map"},
	{MTYPE_POLICY_MAP, "QoS policy map"},
	{MTYPE_POLICY_CLASS_MAP, "QoS policy class map"},
	{MTYPE_QDISC_RULE, "QoS queue disc rule"},
	{MTYPE_QDISC, "QoS queue disc"},
	{-1, NULL}
};
#endif /* MOD_QOS_VER_1 */

#endif      /* MM_MESSAGE_1 */

#define MTYPE_HEADER_SIZE  sizeof(mtype_header_t)  

#ifndef NOT_MEMORY_LIB
struct mm_node;

typedef struct mtype_header_struct
{
	struct  mm_node *node_ptr;
}mtype_header_t;      

struct mstat
{
  	unsigned int alloc;
  	unsigned int alloc_size;  		
} ;       		


/*  may be permission also~~*/
struct mm_node
{
	char	file[12];
	char	func[10];
	int	line;
	int	mtype;
	int 	alloc_size;
	char	alloc_time[12];
	int	pid;
	int 	addr;
	int 	free;

};

#define MM_DATA_INIT 256*1024
#define MNODE_MAX 4096

struct mstat *mstat;
struct mm_node *mnode;

/* macro definition */
/* public interface */
#define XMALLOC(mtype,size)         _XMALLOC(mtype,size,(char*)__FILE__,(char*)__func__,(int)__LINE__)

#define XCALLOC(mtype,size)          _XCALLOC(mtype,size,(char*)__FILE__,(char*)__func__,(int)__LINE__)

#define XREALLOC(mtype,ptr,size)  _XREALLOC(mtype,ptr,size,(char*)__FILE__,(char*)__func__,(int)__LINE__)

#define XFREE(mtype,ptr)               _XFREE(mtype,ptr,(char*)__FILE__,(char*)__func__,(int)__LINE__)

#define XSTRDUP(mtype,str)            _XSTRDUP(mtype,str,(char*)__FILE__,(char*)__func__,(int)__LINE__)

void* _XMALLOC(int mtype,size_t size,char*file,char*func,int line);

void* _XCALLOC(int mtype,size_t size,char*file,char*func,int line);

void* _XREALLOC(int mtype,void* ptr,size_t size,char*file,char*func,int line);

void  _XFREE(int mtype,void* ptr,char*file,char*func,int line);

void* _XSTRDUP(int mtype,char* str,char*file,char*func,int line);


/* mm_global.c */
extern char memory_log;
extern char memory_debug;

void *zmalloc (char* file,char*func,int line,int type, size_t size);
void *zcalloc (char*file,char*func,int line,int type, size_t size);
void *zrealloc (char*file,char*func,int line,int type, void *ptr, size_t size);
void  zfree (char*file,char*func,int line,int type, void *ptr);
char *zstrdup (char*file,char*func,int line,int type, char *str);
                     
void *zmalloc_log ( char *file,
                     char *func,
                     int line,
                     int type,
                     size_t size);
                  
void *zcalloc_log ( char *file,
                     char *func,
                     int line,
                     int type,
                //     size_t num,
                     size_t size);
                     
void *zrealloc_log ( char *file,
                     char *func,
                     int line,
                     int type, 
                     void *ptr,
                     size_t size);

void zfree_log (char *file,
                  char *func,
                  int line,
                  int type,
                  void *ptr);

char *zstrdup_log ( char *file,
                     char *func,
                     int line,
                     int type,
                     char* str);
                                                                   

/* mm_lock.c */
extern void mm_down();
extern void mm_up();

/* mm_init.c */

extern void memory_init_mstat();

/* mm_shm.c */
extern int MM_create(size_t size,const char*file);
extern void * MM_malloc(size_t size);
extern void MM_free(void* ptr);
extern int MM_lock(mm_lock_mode mode);
extern int MM_unlock(void);

/* mm_list.c */
extern char alloc_time[12];

extern void mem_node_add_file(struct mm_node**n,char*file);
extern void mem_node_add_func(struct mm_node**n,char*func);
extern void mem_node_add_mtype(struct mm_node**n,int mtype);
extern void mem_node_add_size(struct mm_node**n,int size);
extern void mem_node_add_time(struct mm_node**n,int time);
extern void mem_node_add_line(struct mm_node**n,int line);
extern void mem_node_add_pid(struct mm_node**n,int pid);
extern void mem_node_add_addr(struct mm_node**n,unsigned int addr);
extern void mem_list_print(struct vty* vty);
extern void mem_list_pid(struct vty* vty,int pid);
#else /* NOT_MEMORY_LIB for vector.c command.c  buffer.c vty.c command tree */

#if 0
#define XMALLOC(mtype, size)       malloc ((size))
#define XCALLOC(mtype, size)       calloc (1,(size))
#define XREALLOC(mtype, ptr, size) realloc ((ptr), (size))
#define XFREE(mtype, ptr)          free ((ptr))
#define XSTRDUP(mtype, str)        strdup ((str))
#else

void* malloc_log(int type,size_t size,char*file,char*func,int line);

void* calloc_log(int type,size_t size,char*file,char*func,int line);

void* realloc_log(int type,void* ptr,size_t size,char*file,char*func,int line);

void  free_log(int type,void* ptr,char*file,char*func,int line);

void* strdup_log(int type,char* str,char*file,char*func,int line);


#define XMALLOC(mtype,size)         malloc_log(mtype,size,(char*)__FILE__,(char*)__func__,(int)__LINE__)

#define XCALLOC(mtype,size)          calloc_log(mtype,size,(char*)__FILE__,(char*)__func__,(int)__LINE__)

#define XREALLOC(mtype,ptr,size)  realloc_log(mtype,ptr,size,(char*)__FILE__,(char*)__func__,(int)__LINE__)

#define XFREE(mtype,ptr)               free_log(mtype,ptr,(char*)__FILE__,(char*)__func__,(int)__LINE__)

#define XSTRDUP(mtype,str)           strdup_log(mtype,str,(char*)__FILE__,(char*)__func__,(int)__LINE__)
#endif

#endif 

#else //MOD_MEMORY_LIB
#define XMALLOC(mtype, size)       malloc ((size))
#define XCALLOC(mtype, size)       calloc (1,(size))
#define XREALLOC(mtype, ptr, size) realloc ((ptr), (size))
#define XFREE(mtype, ptr)          free ((ptr))
#define XSTRDUP(mtype, str)        strdup ((str))
#endif 

#endif /* _ZEBRA_MEMORY_H */
