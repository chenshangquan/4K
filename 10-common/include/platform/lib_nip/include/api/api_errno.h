
/* api_errno.h -
 *
 * Copyright 1997-2003 suzhou Keda co.
 *
 * description :
 * -------------------------
 * Purpose: for nip api.
 *
 * modification history
 * -------------------------
 * 2005-11-30 zhuzhenming write first.
 */

#ifndef _API_ERRNO_H_
#define _API_ERRNO_H_

/* zhuzhm : vxworks errer number , must reserve */
#define VX_ERR_BASE            0
#define VX_ERR_MAX            255
#define VX_ERR_CFGITEM_EXIST   (VX_ERR_BASE+0x40)

#define NORMAL_ERR_BASE 10000
#define NORMAL_ERR_MAX  10099

#define IF_ERR_BASE 10100
#define IF_ERR_MAX  10199

#define RT_ERR_BASE 10200
#define RT_ERR_MAX  10299

#define ETH_ERR_BASE 10300
#define ETH_ERR_MAX  10399

#define WEBS_ERR_BASE 10400
#define WEBS_ERR_MAX  10499

#define FTP_ERR_BASE 10400
#define FTP_ERR_MAX  10499

#define E1_ERR_BASE 10500
#define E1_ERR_MAX  10599

#define SNTP_ERR_BASE 10600
#define SNTP_ERR_MAX  10699

#define DHCPC_ERR_BASE 10700
#define DHCPC_ERR_MAX 10799

/*feixp: general module error*/
#define GENERAL_ERR_BASE 11100
#define GENERAL_ERR_MAX   11199
#define GENERAL_FILENANME_ERROR          GENERAL_ERR_BASE + 1
#define GENERAL_CREATE_FILE_ERROR       GENERAL_ERR_BASE + 2
#define GENERAL_FILE_DIR_ERROR              GENERAL_ERR_BASE + 3

/* zhuzhm : general error num */
#define NIP_API_ARGV_ERROR                          NORMAL_ERR_BASE+1
#define NIP_API_COMM_ERROR                          NORMAL_ERR_BASE+2
#define NIP_API_IF_NOT_EXIST                        NORMAL_ERR_BASE+3
#define NIP_API_ADDR_NOT_EXIST                  NORMAL_ERR_BASE+4
#define NIP_API_ROUTE_NOT_EXIST                 NORMAL_ERR_BASE+5
#define NIP_API_NEXTHOP_NOT_EXIST                 NORMAL_ERR_BASE+6
#define IF_DEL_ERROR_DECAP_FAULT                    NORMAL_ERR_BASE+7
#define IF_DEL_ERROR                                   NORMAL_ERR_BASE+8
#define NIP_API_CALLBACK_REG_ERROR                  NORMAL_ERR_BASE+9
#define NIP_API_NOMEMORY_ERROR                   NORMAL_ERR_BASE+10
#define NIP_API_XMALLOC_ERROR                    NORMAL_ERR_BASE+11

/*zhangyunping: webserver err num*/
#define WEBS_CFG_ERROR		WEBS_ERR_BASE+1

/* zhuzhm : address */
#define IF_E_MALFORMED_ADDR                       IF_ERR_BASE+1
#define IF_E_HIGHEST_ADDR_ERROR                IF_ERR_BASE+2
#define IF_E_PREFIX_IS_ZERO                          IF_ERR_BASE+3
#define IF_E_ADDR_IS_MULTI                           IF_ERR_BASE+4
#define IF_E_CONFLIT_WITH_LOOPBACK           IF_ERR_BASE+5
#define IF_E_PREFIX_LEN_INVALID                   IF_ERR_BASE+6
#define IF_E_PREFIX_INVALID                            IF_ERR_BASE+7
#define IF_E_CONFLIT_WITH_OTHER_ADDR       IF_ERR_BASE+8
#define IF_E_CONFLIT_WITH_ADDR                   IF_ERR_BASE+9
#define IF_E_NO_MASTER_ADDR                        IF_ERR_BASE+10
#define IF_E_SET_ADDR_FAILED                        IF_ERR_BASE+12
#define IF_E_ADDR_NOT_FOUND                        IF_ERR_BASE+13
#define IF_E_DELETE_SECOND_ADDR_FIRST      IF_ERR_BASE+14
#define IF_E_UNSET_ADDR_FAILED                    IF_ERR_BASE+15
#define IF_E_NOT_CONF_ADDR                           IF_ERR_BASE+16

#define IF_SHUTDOWN_ERROR                           IF_ERR_BASE+17
#define IF_SHUTDOWN_NOT_SUPPORT              IF_ERR_BASE+18
#define IF_E_SECOND_IP_ADDR_REACH_MAX          IF_ERR_BASE+19

#define IF_E_ADDR_EXIST                                     IF_ERR_BASE+20

/* for group address */
#define IF_E_ADDR_IS_NOT_GROUP          IF_ERR_BASE+20
#define IF_E_GROUP_IS_WELLKNOW          IF_ERR_BASE+21
#define IF_E_GROUP_NOT_FOUND               IF_ERR_BASE+22
#define IF_E_JOIN_GROUP_FAILED              IF_ERR_BASE+23
#define IF_E_LEAVE_GROUP_FAILED             IF_ERR_BASE+24
#define IF_E_CFG_GROUP_REACH_MAX          IF_ERR_BASE+25

/* interface state */
#define IF_E_NOT_UP                     IF_ERR_BASE+26
#define IF_E_NOT_MULTICAST          IF_ERR_BASE+27

/* zhuzhm : route */
#define RT_E_MALFORMED_PREFIX             RT_ERR_BASE+1
#define RT_E_INVALID_PREFIX             RT_ERR_BASE+2
#define RT_E_MALFORMED_MASK             RT_ERR_BASE+3
#define RT_E_INVALID_MASK             RT_ERR_BASE+4
#define RT_E_INVALID_GATE             RT_ERR_BASE+5
#define RT_E_NO_MATCH_ROUTE             RT_ERR_BASE+6
#define RT_E_INVALID_DISTANCE             RT_ERR_BASE+7

/* zhuzhm : ethernet */
#define ETH_E_INVALID_MAC_ADDR             ETH_ERR_BASE+1
#define ETH_E_SET_MAC_ADDR_FAILED       ETH_ERR_BASE+2
#define ETH_E_NO_CONFIG                         ETH_ERR_BASE+3
#define ETH_E_CONFIG_NOT_EXIST            ETH_ERR_BASE+4
#define ETH_E_DEL_MAC_ADDR_FAILED       ETH_ERR_BASE+5

/* linzhe: ftp */
#define FTP_E_ERROR   FTP_ERR_BASE + 1
#define FTP_E_ALREADY_RUNNING   FTP_ERR_BASE + 2
#define FTP_E_NOT_RUNNING   FTP_ERR_BASE + 3
#define FTP_E_ENABLE_FAILED   FTP_ERR_BASE + 4

/* linzhe: dhcpc */
#define DHCPC_E_ERROR   DHCPC_ERR_BASE + 1
#define DHCPC_E_NOT_RUNNING   DHCPC_ERR_BASE + 2
#define DHCPC_E_ALREADY_RUNNING   DHCPC_ERR_BASE + 3

/* luchen: e1 */
#define E1_E_ERROR   	  		  E1_ERR_BASE + 1
#define E1_E_NO_CONFIG    		  E1_ERR_BASE + 2
#define E1_E_CFG_TS_CONFLICT  	  E1_ERR_BASE + 3
#define E1_E_CFG_SER_CONFLICT     E1_ERR_BASE + 4
#define E1_E_CFG_MODE_CONFLICT 	  E1_ERR_BASE + 5
#define E1_E_NO_ALLOW_ACCESS  	  E1_ERR_BASE + 6
#define E1_E_PARAM_ERROR		  E1_ERR_BASE + 7

/* Yuanyi Zhang: ntp */
#define SNTP_E_INVALID_IPADDR        SNTP_ERR_BASE + 2
#define SNTP_E_UPDATE                SNTP_ERR_BASE + 3
#define SNTP_E_THREAD_CREATE         SNTP_ERR_BASE + 4
#define SNTP_E_THREAD_INIT           SNTP_ERR_BASE + 5
#define SNTP_E_SERVICE_ALREADY_START SNTP_ERR_BASE + 6
#define SNTP_E_SERVICE_NOT_AVAIL     SNTP_ERR_BASE + 7
#define SNTP_E_UNKNOWN               SNTP_ERR_BASE + 8

#endif

