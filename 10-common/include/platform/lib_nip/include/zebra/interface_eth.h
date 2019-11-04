#ifndef __INTERFACE_ETH__
#define __INTERFACE_ETH__

#include "lib/zebra.h"
#include <lib/zlog.h>

struct eth_info {
#ifdef ZHZS_IMP_PPPOE
  int cfg_pppoe;
  int cfg_pppoe_unit;
  int def;
#endif
};

extern int eth_encap (struct interface *ifp);
//extern void eth_no_encap (struct interface *ifp);
extern int eth_no_encap (struct interface *ifp);
extern int eth_show (struct interface *ifp, struct vty *vty);
extern int eth_config (struct interface *ifp, struct vty *vty);
extern int eth_erase (struct interface *ifp);
 
#ifdef ETHERNET_FUNCTION
/*	Ethernet speed/duplex/mac address cmd header
*	function		: negotiation and mac address relate cmd header
*	author			: zhangyan
*	data			: 2005-05
*	modify record	:
*/
#define ETH_INFO(fmt, args...)   zlog_msg("interface_eth", ZLOG_INFO, fmt, ##args)

#define ETHER_DEBUG
#define IF_HWADDR_LEN	6

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned long long u64;

/* used in ethernet nego */
#define MII_SPEED_10		0x01
#define MII_SPEED_100		0x02
#define MII_SPEED_1000		0x04
#define MII_SPEED_AUTO		(MII_SPEED_10 | MII_SPEED_100)
#define GMII_SPEED_AUTO		(MII_SPEED_AUTO | MII_SPEED_1000)
#define MII_DUPLEX_FULL		0x10
#define MII_DUPLEX_HALF 	0x20
#define MII_DUPLEX_AUTO		(MII_DUPLEX_FULL | MII_DUPLEX_HALF)

/* mac address is configure */
#define ETHER_MAC_CONFIG	0x00000001


/* ethernet debug information */
#ifndef ETHER_DEBUG
#ifndef __KERNEL__
enum {
	NETIF_MSG_DRV		= 0x0001,
	NETIF_MSG_PROBE		= 0x0002,
	NETIF_MSG_LINK		= 0x0004,
	NETIF_MSG_TIMER		= 0x0008,
	NETIF_MSG_IFDOWN	= 0x0010,
	NETIF_MSG_IFUP		= 0x0020,
	NETIF_MSG_RX_ERR	= 0x0040,
	NETIF_MSG_TX_ERR	= 0x0080,
	NETIF_MSG_TX_QUEUED	= 0x0100,
	NETIF_MSG_INTR		= 0x0200,
	NETIF_MSG_TX_DONE	= 0x0400,
	NETIF_MSG_RX_STATUS	= 0x0800,
	NETIF_MSG_PKTDATA	= 0x1000,
	NETIF_MSG_HW		= 0x2000,
	NETIF_MSG_WOL		= 0x4000,
};
#endif
#define ETHER_DEBUG_OFF 0
#define ETHER_DEBUG_ON	0xffff	/* all of up enum */

#define ETHER_SHOW_TBD	0
#define ETHER_SHOW_RBD	1
#else	/* ETHER_DEBUG */
#define PARAM_MASK	0xffff0000
#define FUNC_MASK	0x0000ffff

#define TBD_SHOW	0
#define RBD_SHOW	1
#define STATE_SHOW	2
#define RATE_SHOW	3
#endif	/* ETHER_DEBUG */

/* pre-declare */
void install_if_ethernet_driver();
void install_if_feth_driver();
void install_if_geth_driver();
int if_ioctl (u_long, caddr_t);
void ether_config_write (struct interface *, struct vty *);
void ether_nego_show(struct interface * , struct vty *);
int get_eth_hwaddr(struct interface *);
int set_eth_hwaddr(struct interface *);

/* zhuzhm : for api */
void print_ethernet_errstr(struct vty *vty, int error_no);
int set_eth_macaddr(struct interface *ifp, char *macaddr, int *errid);
int del_eth_macaddr(struct interface *ifp, int *errid);
void ether_config_erase(struct interface * ifp);
int eth_phy_state_change(struct interface *ifp, int flag);
int shutdown_if_eth(struct interface * ifp) ;
int no_shutdown_if_eth(struct interface * ifp) ;

#endif

#endif

