#ifndef __SWITCH_H_
#define __SWITCH_H_

//#include <asm/type.h>
#define NO_PORT				0xFF
#define MAX_SWPORT_NUM		26
#define MAX_TRUNK_NUM		3

#define DISABLE	0
#define ENABLE	1

#define FAST_PORT	1
#define GIGA_PORT	2

#define UNICAST		1
#define MULTICAST 	2

#define BOTH			1
#define RX			2
#define TX			3

#define SW_DUPLEX_FULL	1
#define SW_DUPLEX_HALF	2
#define SW_DUPLEX_AUTO	(SW_DUPLEX_FULL | SW_DUPLEX_HALF)

#define SW_SPEED_10		1
#define SW_SPEED_100	2
#define SW_SPEED_1000	4
#define SW_SPEED_FAST_AUTO	(SW_SPEED_10 | SW_SPEED_100)
#define SW_SPEED_GIGA_AUTO	(SW_SPEED_10 | SW_SPEED_100 | SW_SPEED_1000)

#define DEFAULT_AGING_TIME	1

#define FAST_PORT_TRUNK		1
#define GIGA_PORT_TRUNK 	2

#define SADA_MAC_TRUNK		1
#define SA_MAC_TRUNK	 	2
#define DA_MAC_TRUNK		3


/* sw_ioctl command */
#define SW_CMD_NO	   		0x0080			/* del configuration */

#define SW_VLAN_CFG	   		0x0001  		/* vlan configuration */  
#define SW_MSPORT_CFG  		0x0002  		/* mirror source port configuration  */
#define SW_MDPORT_CFG   		0x0003  		/* mirror desitination port configuration  */
#define SW_MAC_CFG   		0x0004  		/* mac address configuration */
#define SW_AGE_CFG   		0x0005  		/* mac address age configuration */
#define SW_PORTSPEED_CFG 	0x0006  		/* switchport speed configuration */
#define SW_PORTDUPLEX_CFG	0x0007  		/* switchport dupelx configuration */
#define SW_CPUPORT_CFG   	0x0008  		/* CPU port enable */
#define SW_STP_CFG   			0x0009  		/* STP enable*/
#define SW_IGMP_CFG   		0x000A  		/* IGMP-SNOOPING enable */
#define SW_SHUTDOWN_CFG	0x000B		/* shutdown switchport */
#define SW_TRUNKP_CFG		0x000C		/* trunk port configuration */

#define GET_MAC_AGE   		0x0100  		/* get MAC address table age time */
#define GET_PORT_INFO 		0x0200  		/* get port statistic */
#define SET_STP_STATE 		0x0300  		/* set port STP state */
#define GET_STP_STATE 		0x0400  		/* get port STP state*/
#define GET_MAC_TBL   		0x0500  		/* get MAC address table */
#define SET_TRUNK_MODE 		0x0600  		/* trunk mode configuration */

#define SW_CMD_END        		0xFFFF

/* sw_ioctl command end */


/* sw err no */
#define SW_OPEN_DEV_ERR	1
#define SW_USER_CFG_ERR	2
#define SW_SAME_CFG_ERR	3
#define SW_NO_CFG_ERR		4
#define SW_CFG_CONFLICT		5
#define SW_MAC_ADDR_ERR	6

/* sw err no end */

struct vlan_cfg {
	int vlan_id;
	int port_map;	/* vlan port map */
	int non_vlan_port_map;
};

struct mac_cfg {
	unsigned char mac_addr[6];
	int maddr_type;
	int f_port;
	int vlan_id;
};

struct port_mirror_cfg{
	int source_port;
	int destination_port;
	int mode;					/* mirror date type: both/rx/tx */
	int enable;
};

struct swport_cfg{
	char port_name[64]; 	/* port name, reservered */
	int index; 			/* port index */
	int port_type;			/*type: FAST_PORT/GIGA_PORT */
	int speed;			/* speed: SPEED_10/SPEED_100/SPEED_1000/SPEED_AUTO */
	int duplex;			/* duplex: DUPLEX_FULL/DUPLEX_HALF/DUPLEX_AUTO */
	int shutdown;
};

struct globe_manage_cfg{
	int cpu_port_en;		/* cpu port: 1-enable£¬0-disable */
	int stp_en; 			/* stp: 1-enable, 0-disable */
	int igmp_en; 			/* igmp: 1-enable, 0-disable */
	int age_time;			/* MAC addr age time, its unit is second, default 300s, set time is 0 means addr is static.  */
};

struct trunk_port_cfg{
	int index;				/* trunk number: 0/1 */
	int port_map; 			/* trunked-port map */
	int trunk_ptype; 		/* trunk port type: 1-100M port trunk, 2-1000M port trunk */
	int exist;				/* other 100M trunk existence: 1-yes, 0-no (used when del trunk) */
};

struct port_transfer_statistic {
	int index;
	
	long long tx_octets;
	int  tx_drop_pkts;
	int  tx_boardcast_pkts;
	int  tx_multicast_pkts;
	int  tx_unicast_pkts;
	int  tx_collisions;
	int  tx_single_collision;
	int  tx_multicast_collision;
	int  tx_deferred_transmit;
	int  tx_late_collision;
	int  tx_excessiver_collision;
	int  tx_frame_lndisc;
	int  tx_pause_pkts;
	long long tx_qos_octets;
	long long rx_octets;
	int  rx_undersize_pkts;
	int  rx_pause_pkts;
	int  pkts_64_octets;
	int  pkts_65to127_octets;
	int  pkts_128to255_octets;
	int  pkts_512to1023_octets;
	int  pkts_1024to1522_octets;
	int  rx_oversize_pkts;
	int  rx_jabbers;
	int  rx_alignment_errors;
	int  rx_fcs_errors;
	long long rx_good_octets;
	int  rx_drop_pkts;
	int  rx_unicast_pkts;
	int  rx_multicast_pkts;
	int  rx_broadcast_pkts;
	int  rx_sa_changes;
	int  rx_fragments;
	int  rx_excess_size_disc;
	int  rx_symbol_error;
	int  rx_qos_pkts;
	long long rx_qos_octets;
};

struct sw_cfg{	
	struct mac_cfg *mac_cfg;
	struct list *mac_list_head;

	struct swport_cfg port_cfg[MAX_SWPORT_NUM];
  	struct port_mirror_cfg mirror_cfg;
	struct globe_manage_cfg manage_cfg;
	struct trunk_port_cfg trunk_cfg[MAX_TRUNK_NUM];
	int vlan_baseport_map[MAX_SWPORT_NUM];
	
	int trunk_mtype; 		/* trunk mac type: 1-da & sa trunk, 2-sa trunk, 3-da trunk, 0-default */
	int non_vlan_port_map;
	int non_trunk_port_map;
};

#endif /* __SWITCH_H_ */
