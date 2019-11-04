#ifndef __PPP_ZEBRA__
#define __PPP_ZEBRA__

#include <lib/zebra.h>
#include <g_module.h>
#include "lib/aligned.h"

#include "lib/zipc.h"
#define ZTOP_PIPEPATH "/tmp/ppp/"
#define PTOZ_PIPEPATH "/tmp/ppp/"
#define TMP_PIPEPATH "/tmp/ppp/"

#define NUM_PPP		512	/* */
#define ZMSG_MP_BASE 				0x00002000
/* zebra to MP */
#define ZEBRA_CREATE_VIRTUAL		ZMSG_MP_BASE +1
#define ZEBRA_CREATE_BIND			ZMSG_MP_BASE +2
#define ZEBRA_SET_IPADDR			ZMSG_MP_BASE +3
#define ZEBRA_NO_VIRTUAL_UNIT		ZMSG_MP_BASE +4
#define ZEBRA_NO_BIND				ZMSG_MP_BASE +5
#define ZEBRA_NO_IPADDR			ZMSG_MP_BASE +6
#define ZEBRA_ERASE 				ZMSG_MP_BASE +7
#define ZEBRA_SHOW_BIND_INFO		ZMSG_MP_BASE +8
#define DEBUG_MULTILINK_ALL		ZMSG_MP_BASE +9
#define DEBUG_MULTILINK_EVENT		ZMSG_MP_BASE +10
#define DEBUG_MULTILINK_ERROR		ZMSG_MP_BASE +12
#define DEBUG_MULTILINK_WARN		ZMSG_MP_BASE +13

#define NO_DEBUG_MULTILINK_ALL	ZMSG_MP_BASE +15
#define NO_DEBUG_MULTILINK_EVENT	ZMSG_MP_BASE +16
#define NO_DEBUG_MULTILINK_ERROR	ZMSG_MP_BASE +18
#define NO_DEBUG_MULTILINK_WARN	ZMSG_MP_BASE +19
/* ppp to MP */	
#define PPP_JOIN_MP_REQ 			ZMSG_MP_BASE +21
#define PPP_LEAVE_MP_REQ			ZMSG_MP_BASE +22

#define ZEBRA_CREATE_BIND_GROUP	ZMSG_MP_BASE +23
#define ZEBRA_NO_BIND_GROUP 		ZMSG_MP_BASE +24


#define MULTILINK_USER_MAX_LEN 	32
#define MP_ZMSG_MAXLEN 			512
#define PPPD_ZMSG_MAXLEN			512
#define ZEBRA_MSG_LEN				128

#define MP_ZIPC_ID 					"mpd"
#define PPPD_ZIPC_ID				"pppd"

#define  PPPD_TMP					"pppdtmp"
#define  MPD_TMP					"mpdtmp"
#define PPP_CALLBACK_ID				"pppd_callback_listen_fd"

struct zebra2ppp_msg{
	int unit;
	unsigned char info[ZEBRA_MSG_LEN];
};


struct zebra2mp_msg{
	int virtual_unit;
	char username[MULTILINK_USER_MAX_LEN] aligned_def;
	u_int32_t ip_address;
	u_int32_t ip_mask;
#define INTERFACE_NAMSIZ 20
	char ifname[INTERFACE_NAMSIZ+1] aligned_def;
	int serial;
	int loopback_mode;
};


struct ppp2mp_msg{
	int serial_unit;
	char username[MULTILINK_USER_MAX_LEN] aligned_def;
	ZIPC_ID  tmp_mul;
	int mrru;
	unsigned long flag;	
	int loopback;
};

struct ppp_if_state_msg{
	unsigned long	if_address;		
	unsigned long 	peer_addr;			
	unsigned long dnsaddr[2];
	int		link_down_times;	
	int		pppoe_dialer_times;
	unsigned int	flags;
	unsigned long link_keep_times;	
	unsigned long i_pkts;
	unsigned long o_pkts;
 };


#define NEW_PPP_UNIT							1
#define NO_PPP_UNIT								2

#define MULTILINK_USER 							3
#define NO_MULTILINK_USER 						4
#define MULTILINK_MAXBIND 						5
#define NO_MULTILINK_MAXBIND 					6
#define MULTILINK_MAXFRAGS 					7
#define NO_MULTILINK_MAXFRAGS 				8
#define PPP_EXIT                                				9
#define PPP_SHUT  								10
#define NO_PPP_SHUT  							11
#define SHOW_PPP_STATE							12

#define NEW_MP_UNIT							13
#define NO_MP_UNIT								14
#define NEW_PPPOE_UNIT							15
#define NO_PPPOE_UNIT							16
#define NEW_PPP_DAILER_UNIT					17
#define NO_PPP_DAILER_UNIT						18
#define PPP_DAILER_IN							19
#define PPP_DAILER_OUT							20

#define PPP_DEBUG_ALL							30
#define NO_PPP_DEBUG_ALL						31
#define DEBUG_SYS								32
#define NO_DEBUG_SYS							33
#define DEBUG_INFORM							34
#define NO_DEBUG_INFORM						35
#define DEBUG_NOTE								36
#define NO_DEBUG_NOTE							37
#define DEBUG_WARN								38
#define NO_DEBUG_WARN							39
#define DEBUG_ERROR							40
#define NO_DEBUG_ERROR							41
#define DEBUG_FATAL							42
#define NO_DEBUG_FATAL							43
#define DEBUG_EVENT							50
#define NO_DEBUG_EVENT							51
#define DEBUG_EVENT_LCP						52
#define NO_DEBUG_EVENT_LCP					53
#define DEBUG_EVENT_PAP						54
#define NO_DEBUG_EVENT_PAP					55
#define DEBUG_EVENT_CHAP		     				56
#define NO_DEBUG_EVENT_CHAP					57
#define DEBUG_EVENT_IPCP						58
#define NO_DEBUG_EVENT_IPCP					59

#define DEBUG_PACKET							60
#define NO_DEBUG_PACKET		    				61
#define DEBUG_PACKET_LCP						62
#define NO_DEBUG_PACKET_LCP					63
#define DEBUG_PACKET_PAP						64
#define NO_DEBUG_PACKET_PAP					65
#define DEBUG_PACKET_CHAP						66
#define NO_DEBUG_PACKET_CHAP					67
#define DEBUG_PACKET_IPCP						68
#define NO_DEBUG_PACKET_IPCP					69

#define DEBUG_FLOW								70
#define NO_DEBUG_FLOW			     				71
#define DEBUG_FLOW_LCP							72
#define NO_DEBUG_FLOW_LCP	     					73
#define DEBUG_FLOW_PAP						74
#define NO_DEBUG_FLOW_PAP	     					75
#define DEBUG_FLOW_CHAP						76
#define NO_DEBUG_FLOW_CHAP	     				77
#define DEBUG_FLOW_IPCP						78
#define NO_DEBUG_FLOW_IPCP	     				79
#define DEBUG_FLOW_MAIN						80
#define NO_DEBUG_FLOW_MAIN	     				81
#define DEBUG_FLOW_SYS							82
#define NO_DEBUG_FLOW_SYS	     					83
#define DEBUG_FLOW_FSM						84
#define NO_DEBUG_FLOW_FSM	     					85
#define DEBUG_FLOW_OPTION						86
#define NO_DEBUG_FLOW_OPTION   				87
#define DEBUG_EVENT_MULTILINK					88
#define NO_DEBUG_EVENT_MULTILINK				89
#define DEBUG_PACKET_MULTILINK				90
#define NO_DEBUG_PACKET_MULTILINK			91


#define PPP_MULTILINK  							101
#define NO_PPP_MULTILINK  						102
#define LCP_INTERVAL   							103
#define NO_LCP_INTERVAL   						104
#define LCP_MAXRETRY  							105
#define NO_LCP_MAXRETRY  						106
#define LCP_ECHO         							107
#define NO_LCP_ECHO         						108
#define LCP_MAXWAITFORREQUEST  				109
#define NO_LCP_MAXWAITFORREQUEST  			110
#define LCP_MTU									111
#define NO_LCP_MTU								112
#define LCP_ECHO_MAXRETRY  					113
#define NO_LCP_ECHO_MAXRETRY  					114
#define IPCP_INTERVAL   							115
#define NO_IPCP_INTERVAL   						116
#define IPCP_MAXRETRY  							117
#define NO_IPCP_MAXRETRY  						118
#define LCP_ECHO_PADDINGLEN  					119
#define NO_LCP_ECHO_PADDINGLEN  				120

#define PPP_AUTH         							201
#define NO_PPP_AUTH   							202
#define PAP_SENTNAME_PASSWORD 				203
#define NO_PAP_SENTNAME_PASSWORD 			204
#define CHAP_HOSTNAME 							205
#define NO_CHAP_HOSTNAME 						206
//2005.6.29 xu
#define CHAP_PASSWORD							207
#define NO_CHAP_PASSWORD						208
/* MOD MP */
#define MP_ALLOW								209
#define MP_REFUSE 								210
#define MP_RESET								211
#define MP_FIRST								212
#define MP_LAST									213
#define MP_SET_MRRU							214
#define MP_SET_FLAG								215
#define MP_LEAVE								216

#define SET_LOOPBACK_MODE						217
#define NO_SET_LOOPBACK_MODE					218
/* means virtual interface is loopback */
#define MP_SET_LOOPBACK_MODE					219
#define NO_MP_SET_LOOPBACK_MODE				220
#define IPCP_NAK_CLOSE							221
#define IPCP_NAK_OPEN							222
#define PPPOE_RESET								223

#define CHANNEL_IP     							301
#define NO_CHANNEL_IP     						302
#define NO_PEER_IP                                                	306
#define PEER_IP                                                      	305
#define SET_MINIPKTLEN							307
#define NO_SET_MINIPKTLEN						308
#define SET_MAX_FRAG							309	
#define NO_SET_MAX_FRAG						310

#define USER_PASSWORD 							311  
#define NO_USER_PASSWORD 						312 
#define PPP_DEF_ROUTE							313
#define NO_PPP_DEF_ROUTE						314
#define PPP_GET_IF_STATE						315						
#define PPP_ENABLE_CALLBACK					316
#define PPP_DISABLE_CALLBACK					317
#define PPP_PHYSICAL_UP						318
#define PPP_PHYSICAL_DOWN						319



#define PLUGIN_BASE						0x80000000
#define SHOW_PPPOE_STATE				(PLUGIN_BASE)
#define DEBUG_PPPOE_BASE				(PLUGIN_BASE + 0x10000000)
#define DEBUG_PPPOE_ALL					(DEBUG_PPPOE_BASE)
#define NO_DEBUG_PPPOE_ALL				(DEBUG_PPPOE_BASE + 1)
#define DEBUG_PPPOE_PACKET				(DEBUG_PPPOE_BASE + 2)
#define NO_DEBUG_PPPOE_PACKET			(DEBUG_PPPOE_BASE + 3)
#define DEBUG_PPPOE_EVENT				(DEBUG_PPPOE_BASE + 4)
#define NO_DEBUG_PPPOE_EVENT			(DEBUG_PPPOE_BASE + 5)
#define DEBUG_PPPOE_ERROR				(DEBUG_PPPOE_BASE + 6)
#define NO_DEBUG_PPPOE_ERROR			(DEBUG_PPPOE_BASE + 7)
#define DEBUG_PPPOE_DATA				(DEBUG_PPPOE_BASE + 8)
#define NO_DEBUG_PPPOE_DATA				(DEBUG_PPPOE_BASE + 9)
#define DEBUG_PPPOE_PACKET_DETAIL			(DEBUG_PPPOE_BASE + 10)
#define NO_DEBUG_PPPOE_PACKET_DETAIL			(DEBUG_PPPOE_BASE + 11)
//wj 0802 debug data
//#define DEBUG_PPPOE_DATA				(DEBUG_PPPOE_BASE + 12)
//#define NO_DEBUG_PPPOE_DATA			(DEBUG_PPPOE_BASE + 13)
#define DEBUG_PPPOE_DATA_DETAIL			(DEBUG_PPPOE_BASE + 14)
#define NO_DEBUG_PPPOE_DATA_DETAIL			(DEBUG_PPPOE_BASE + 15)


int  zebra2mp (u_long type,struct zebra2mp_msg *zebramsg);

#endif

