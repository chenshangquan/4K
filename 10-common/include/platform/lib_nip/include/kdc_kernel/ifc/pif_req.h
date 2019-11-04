#ifndef __PIF_REQ_H_
#define __PIF_REQ_H_

#ifndef unchar
#define unchar unsigned char
#endif

#define E1_CPM_MINOR 	60
#define V35_CPM_MINOR 	61
#define E1_PHY_MINOR 	70
#define V35_PHY_MINOR 	71

#define SER_CE1_BASE	16

#define HDLC		0x00
#define TRANSPARENT	0x01

/* ===========interface work mode=========== */
#define ON 		1
#define OFF 	0

#define YES		1
#define NO		0

#define RBD		1
#define TBD		0

//#define CONIFG_MASK		0xf0

#define SHUTDOWN		0x01
#define NO_SHUTDOWN		0x02

#define NO_INDEX		-1
#define NO_CHANNEL		-1

#define ALL_INDEX		0xffffffff
#define WHOLE_E1		0xff

/* command support */
#define CLOCK_SUPPORT	0x01
#define FRAME_SUPPORT	0x02
#define USING_SUPPORT	0x04
#define LOOP_SUPPORT	0x08
#define RATE_SUPPORT	0x10
#define TS_SUPPORT		0x20
#define SIGNAL_SUPPORT	0x40

/* clock dce/dte command */
#define DEFAULT_CLOCK	0x00
#define NO_CLOCK_DTE	0x01
#define NO_CLOCK_DCE	0x02
#define CLOCK_DTE		0x10
#define CLOCK_DCE		0x20

/* frame crc4 command */
#define DEFAULT_FRAME	0x00
#define NO_FRAM_NOCRC4	0x01
#define NO_FRAM_CRC4	0x02
#define FRAM_NOCRC4		0x10
#define FRAM_CRC4		0x20

/* frame crc4 command */
#define DEFAULT_SIGNAL	0x00
#define NO_SIGNAL_CCS	0x01
#define NO_SIGNAL_CAS	0x02
#define SIGNAL_CCS		0x10
#define SIGNAL_CAS		0x20


/* loop command*/
#define REG_LOOP		0x01
#define NO_REG_LOOP		0x02

#define LOCAL_LOOP		0x03
#define NO_LOCAL_LOOP	0x04

#define REMOTE_LOOP		0x05
#define NO_REMOTE_LOOP	0x06

/* e1 mode */
#define DEFAULT_MODE	0x00
#define NO_CE1			0x00
#define NO_E1			0x01
#define CE1				0x10
#define E1				0x20

/* cmd: NO */
//#define CMD_NO			0x80

//#define SET_BANDWIDTH	0x70

/* debug command */
#define DEBUG_TYPE		0x7f
#define DEBUG_SWITCH	0x80

#define DEBUG_INTERRUPT	0x01
#define DEBUG_RX		0x02
#define DEBUG_TX		0x04
#define DEBUG_ALL		0x7f

#define REG_LOOP		0x01

#define DEBUG_ON		0x80
#define DEBUG_OFF		0x00

#define PIF_CMD_SHIFT	8
#define PIF_CHECK_CFG 	0x0001
#define PIF_NEW_CFG 	0x0002 
#define PIF_MORIFY_CFG 	0x0003 
#define PIF_DELETE_CFG	0x0004 
#define PIF_GET_TTYNAME 0x0005
#define PIF_TTY_EXIST 	0x0006
#define PIF_GET_CFG		0x0007
#define PIF_SET_IFMODE	0x0008
#define PIF_DEBUG_FUNC  0x0009
#define PIF_SHUT_DOWN	0x000a /* now not support! reserved */
#define PIF_CMD_END		0xFFFF

/* child debug function */
#define DEBUG_IF_INFO 	0x0001
#define DEBUG_BD_STATE	0x0002
#define DEBUG_BIT_RATE  0x0003
#define DEBUG_IF_STATE  0x0004
#define DEBUG_REG_LOOP  0x0005

/* child set phy chip mode function */
#define SET_MODE_LOOP		0x0001
#define SET_MODE_CLOCK		0x0002
#define SET_MODE_CE1		0x0003
#define SET_MODE_CRC		0x0004
#define SET_MODE_BINDWDT	0x0005
#define SET_MODE_TS			0x0006
#define SET_MODE_SIGNAL		0x0006
#define SET_MODE_DEF		0x00FF

/* interface type */
#define PIF_E1			0x00000001
#define PIF_V35			0x00000002
#define PIF_ETH			0x00000004
#define PIF_CAP			0x00000008
#define PIF_E1_V35		PIF_E1 | PIF_V35
#define PIF_ALL			0x0000ffff
#define IFTYPE_MASK		0x0000ffff
#define PIF_BASE		PIF_E1

/* pif visitor */
#define ACCESSED_BY_CON		0x0001
#define ACCESSED_BY_API		0x0002	

#define MAX_IFNAME_LEN 		16
#define MAX_TTYNAME_LEN 	16
#define MAX_TIMESLOTS_LEN 	128
#define MAX_SERIALNAME_LEN  32

struct pifreq{
	char name[MAX_IFNAME_LEN];		/*接口名字, reserved */
	int cmd;						/*用户命令*/
	int type;						/*接口类型 e1/v35/eth …*/
	int index;						/*接口号 e1/v35/eth … index*/
	union{
		struct{
			int  channel_group;
			int  serial;
			int  mtu;
			char serialn[MAX_SERIALNAME_LEN];
			char timeslots[MAX_TIMESLOTS_LEN];
		}e1_cfg;
	}subif;
	struct rif_mode{
		unchar protocol;		/* for hdld,transparent and so on */
		unchar loop;			/* loop&0x03--reg loop&0x0c--local loop&0x30--remote */
		unchar usece1;    		/* 1--usece1     0 --no usece1 */
		unchar shutdown;		/* 1--shutdown 	0--no shutdown */
		unchar clock;      		/* clock&0x0f 1--clock dce 	0--dte */
		unchar framecrc4;   	/* 1--frame crc4 0--fram no crc4 */
		unchar bandwidth;		/* set or get band width */
		unchar signal;			/* set or get signal mode */
		char   timeslots[MAX_TIMESLOTS_LEN];	/* for serial timeslots configure */
	}if_mode;
	union{
		unchar debug;			/*1—debug on   		0 –debug off*/	
		unchar showstatc;		/*1—show   			0 –clear*/
		unchar xbd;				/*1—rbd   	 		0 –tbd*/	
		unchar intertime;		/*>0 — stastics start   	0 – stop*/	
	}if_debug;

	int  	accessed_by;					/* type of pifcm visitor */
	long   	attribute;					
	char 	tty_name[MAX_TTYNAME_LEN];		/* 返回tty 设备名*/
	int 	drv_fd;						/* fd of cpm misc device */
	int 	phy_fd;						/* fd of phy misc device */
};
#define log_channel  		subif.e1_cfg.channel_group
#define log_timeslots  		subif.e1_cfg.timeslots
#define log_serial			subif.e1_cfg.serial
#define log_mtu				subif.e1_cfg.mtu
#define rif_protocol		if_mode.protocol
#define rif_loop			if_mode.loop
#define rif_usece1			if_mode.usece1
#define rif_shutdown		if_mode.shutdown
#define rif_framecrc4		if_mode.framecrc4
#define rif_clock			if_mode.clock
#define rif_bandwidth		if_mode.bandwidth
#define rif_timeslots		if_mode.timeslots
#define rif_signal			if_mode.signal
#define rif_debug			if_debug.debug
#define rif_showst			if_debug.showstatc
#define rif_showbd			if_debug.xbd
#define rif_intertime		if_debug.intertime

/* e1 check return */
#define CHECK_ERROR	0x01	/* check config error */
#define SAME_CONFIG	0x02	/* same config with already exist */
#define NEW_CONFIG	0x03	/* config is new config */
#define CLOSE_CHGTS	0x04	/* no open change timeslots */
#define OPEN_CHGTS	0x05	/* open, change timeslots */
#define CHGSER_ONLY	0x06	/* open or not, change serial only */
#define CHGSER_TSBT	0x07	/* open or not, change both serial and timeslots */

/* error number*/
#define ERR_PIF_UNREGISTER 		1
#define ERR_CPM_UNREGISTER 		2
#define ERR_ACCESS_PRIVILEGE 	3
#define ERR_CPM_NULLPOINT		4
#define ERR_PIF_FUNCPOINT		5
#define ERR_FUNC_NULLPOINT		6
#define ERR_NO_CFG				7
#define ERR_CMD					8
#define ERR_SER_CONFLICT		9
#define ERR_TS_CONFLICT			10
#define ERR_MOD_CONFLICT		11
#define ERR_SIGNAL_CONFLICT  	12
#define ERR_FD					13

/* get e1 mode configuration */
#define GET_E1MODE	0x01
#define GET_FRAME	0x02
#define GET_LOOP	  	0x03
#define GET_CLOCK	0x04
#define GET_SIGNAL	0x05

#endif /*__PIF_REQ_H_ */
