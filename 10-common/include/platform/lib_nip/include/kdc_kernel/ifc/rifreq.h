/*	Copyright(C) 2005 KEDACOM 
*
*	filename	: rifreq.h
*	createdate	: 2005-9-6 16:45
*	function	: for nip and driver.
*	modify		: 
*/
#ifndef __RIFREQ_H__
#define __RIFREQ_H__

#ifndef unchar
#define unchar unsigned char
#endif

#define SER_CE1_BASE	16

#define NO_INDEX		-1
#define NO_CHANNEL		-1

#define ALL_INDEX		0xffffffff
#define WHOLE_E1		0xff

/* command support */
#define CLOCK_SUPPORT	0x01
#define FRAME_SUPPORT	0x02
#define USING_SUPPORT	0x04
#define LOOP_SUPPORT	0x08

/* interface type */
#define E1_IF			0x00000001
#define V35_IF			0x00000002
#define ETH_IF			0x00000004
#define CAP_IF			0x00000008
#define E1_V35_IF		E1_IF | V35_IF
#define ALL_IF			0x0000ffff
#define IFTYPE_MASK		0x0000ffff
#define IF_BASE			E1_IF

/* ===========interface work mode=========== */
#define ON 		1
#define OFF 	0

#define YES		1
#define NO		0

#define RBD		1
#define TBD		0

#define CONIFG_MASK		0xf0

#define CE1				0x01
#define NO_CE1			0x00

#define SHUTDOWN		0x01
#define NO_SHUTDOWN		0x00

/* clock dce/dte command */
#define DEFAULT_CLOCK	0x00
#define NO_CLOCK_DTE	0x00
#define NO_CLOCK_DCE	0x01
#define CLOCK_DTE		0x10
#define CLOCK_DCE		0x11

/* frame crc4 command */
#define DEFAULT_FRAME	0x00
#define NO_FRAM_NOCRC4	0x00
#define NO_FRAM_CRC4	0x01
#define FRAM_NOCRC4		0x10
#define FRAM_CRC4		0x11

/* loop command*/
#define REG_LOOP		0x03
#define NO_REG_LOOP		0x02

#define LOCAL_LOOP		0x0c
#define NO_LOCAL_LOOP	0x08

#define REMOTE_LOOP		0x30
#define NO_REMOTE_LOOP	0x20

#define SET_BANDWIDTH	0x80

/* e1 mode */
#define DEFAULT_MODE	0x00
#define NO_CE1_MODE		0x00
#define NO_E1_MODE		0x01
#define CE1_MODE		0x10
#define E1_MODE			0x20

/* debug command */
#define DEBUG_TYPE		0x7f
#define DEBUG_SWITCH	0x80

#define DEBUG_INTERRUPT	0x01
#define DEBUG_RX		0x02
#define DEBUG_TX		0x04
#define DEBUG_ALL		0x7f

#define DEBUG_ON		0x80
#define DEBUG_OFF		0x00

#define HDLC			0x00
#define TRANSPARENT		0x01

#define GET_E1MODE	0x01
#define GET_FRAME	0x02
#define GET_LOOP	0x03
#define GET_CLOCK	0x04


/*============user command===============*/
 /* FUNCTION_IF_CFG */                                         
#define IF_CHECK_CFG   		0x00  		/* 检查配置 */    
#define IF_NEW_CFG	   		0x01  		/* 新增配置*/  
#define IF_MORIFY_CFG  		0x02  		/* 更改配置*/ 
#define IF_DELETE_CFG   	0x03  		/* 删除配置*/ 
#define TTY_GET_NAME   		0x04  		/* 得到tty设备名*/  
#define TTY_IS_EXIST    	0x05  		/* 检查tty设备是否存在 */  
#define IF_GET_CFG     		0x06  		/* 得到e1配置*/  
                                                        
/* FUNCTION_SET_WORK */                                
#define IF_SET_CLOCK   		0x07  		/* clock命令*/ 
#define IF_USE_CE1     		0x08  		/* ce1 命令*/  
#define IF_SET_BANDWTH 		0x09 		/* 设置带宽*/ 
#define IF_GET_BANDWTH 		0x0a  		/* 得到带宽*/ 
#define IF_SET_LOOP    		0x0b  		/* loop命令*/  
#define IF_FRAME_CRC4  		0x0c  		/* fram crc命令 */ 
#define IF_SHUT_DOWN   		0x0d  		/* shutdown命令 */    

/* FUNCTION_DEBUG */                             
#define IF_DEBUG_FUNC       0x0e  		/* 打印调试信息*/ 
#define IF_SHOW_STATC     	0x0f  		/* 打印驱动信息*/ 
#define IF_SHOW_BD	    	0x10  		/* 打印BD信息*/ 
#define IF_SHOW_RATE   		0x11  		/* 统计收发速率*/  
	
/* end */
#define IF_CMD_END        	0xff


#define MAX_IFNAME_LEN 16
#define MAX_TTYNAME_LEN 16
#define MAX_TIMESLOTS_LEN 128


/*
 * Interface request structure used for config
 * if_cfg : the logic intercace config
 * if_mode: the interface work mode
 * if_debug : for inner debug
 */

struct rifreq{
	char name[MAX_IFNAME_LEN];		/*接口名字*/
	unchar cmd;						/*用户命令*/
	int type;						/*接口类型 e1/v35/eth …*/
	int index;						/*接口号 e1/v35/eth … index*/
	union{
		struct logif{
			int 	channel_group;
			int 	serial;
			int    mtu;
			char timeslots[MAX_TIMESLOTS_LEN];
		}logic_cfg;
		struct commchnlif{	//commchnl configure
			int	timeslot;
			int 	serial;
			int	mtu;
		}commchnl_cfg;
	}if_cfg;
	struct rif_mode{
		int	   protocol;		/* to E1: for hdlc, transparent, etc */
							/* to commchnl: lapd, ppp, null */
		unchar loop;			/*loop&0x03--reg loop&0x0c--local loop&0x30--remote */             
		unchar usece1;    		/*1--usece1     0 --no usece1 */                    
		unchar shutdown;		/*1--shutdown 	0--no shutdown*/                    
		unchar clock;      		/*clock&0x0f 1--clock dce 	0--dte */                           
		unchar framecrc4;   	/*1--frame crc4 0--fram no crc4 */	                
		int bandwidth;			/* set or get band width */	                        
	}if_mode;
	union{
		unchar debug;			/*1—debug on   		0 –debug off*/	
		unchar showstatc;		/*1—show   			0 –clear*/
		unchar xbd;				/*1—rbd   	 		0 –tbd*/	
		unchar intertime;		/*>0 — stastics start   	0 – stop*/	
	}if_debug;
	unchar ret_flag;			/*是否有返回参数 copy_to_user */	
#ifdef TRANSPARENT
	int     accessed_by; 		/* ifm accessed by: console,API */ 
	ulong   attribute;			/* 接口属性show run/del cfg/modify cfg: enable/disable */
#endif
	void *drv_ops;				/*接口驱动对应的操作*/
	void *ifc_ops;				/*接口配置对应的操作*/
	void *private;				/*操作的私有结构*/
	void *drvnode;
	char tty_name[MAX_TTYNAME_LEN];		/*返回tty 设备名*/
};

#define log_channel  		if_cfg.logic_cfg.channel_group
#define log_timeslots  		if_cfg.logic_cfg.timeslots
#define log_serial			if_cfg.logic_cfg.serial
#define log_mtu			if_cfg.logic_cfg.mtu
#define rif_protocol		if_mode.protocol
#define rif_loop			if_mode.loop
#define rif_usece1			if_mode.usece1
#define rif_shutdown		if_mode.shutdown
#define rif_framecrc4		if_mode.framecrc4
#define rif_clock			if_mode.clock
#define rif_bandwidth		if_mode.bandwidth
#define rif_debug			if_debug.debug
#define rif_showst			if_debug.showstatc
#define rif_showbd			if_debug.xbd
#define rif_intertime		if_debug.intertime

#ifdef TRANSPARENT
#define ATTR_DEFAULT			0x00000000

#define ATTR_API_UN_SHOW	0x0001  /* 不能通过API函数看接口状态 */
#define ATTR_API_UN_DEL	0x0002  /* 不能通过API函数删除接口 */
#define ATTR_API_UN_MOD	0x0004  /* 不能通过API函数修改接口配置 */
#define ATTR_API_RESERVE	0x00FF
#define ATTR_API_MASK		0x0007

#define ATTR_CON_UN_SHOW	0x0100  /* 不能用console命令观察接口状态 */
#define ATTR_CON_UN_DEL	0x0200  /* 不能用console命令删除接口 */
#define ATTR_CON_UN_MOD	0x0400  /* 不能用console命令修改接口配置 */
#define ATTR_CON_RESERVE	0xFF00
#define ATTR_CON_MASK		0x0700

#define ACCESSED_BY_CON		0x0001
#define ACCESSED_BY_API		0x0002														// x -- on/off bit  y -- flag bit                       	
#endif
														// loop_flag 	- - y x y x y x
#define cmd_is_remoteloop(rif_loop)	(rif_loop & 0x30) 	//	             	R | | | | |	 
#define cmd_is_localloop(rif_loop)	(rif_loop & 0x0c) 	//                 	  | L | | |
#define cmd_is_regloop(rif_loop)	(rif_loop & 0x03) 	//      		   	  |   | C |				                  
#define remoteloop(rif_loop)	(rif_loop & 0x10)		//				      R   |   |		
#define localloop(rif_loop)		(rif_loop & 0x04)       //                        L   |
#define regloop(rif_loop)		(rif_loop & 0x01)       //                            C

#define clock(rif_clock)		(rif_clock & 0x0f)		// clock_flag  x x x x y y y y
#define crc4(rif_framecrc4)		(rif_framecrc4 & 0x0f)	// 	x -- set flag  y -- dte/dce   

#define bandflag(rif_bandwidth) (rif_bandwidth & 0x80)	// bandwidth   x y y y y y y y y
#define bandsize(rif_bandwidth) (rif_bandwidth & 0x7f)	//   x -- set/no   y -- bandwidth

#endif //__RIFREQ_H__     
