
/* api_errno_fmt.h -
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

#ifndef _API_ERRNO_FMT_H_
#define _API_ERRNO_FMT_H_

/* zhuzhm : general */
#define NIP_API_ARGV_ERROR_FMT                          "%% Invalid parameter %s"
#define NIP_API_ARGV_ERROR_FMT_C                      "%% 无效的参数 %s"
#define NIP_API_COMM_ERROR_FMT                          "%% Nip api communication error %s"
#define NIP_API_IF_NOT_EXIST_FMT                        "%% Interface not exist %s"
#define NIP_API_IF_NOT_EXIST_FMT_C                    "%% 接口不存在 %s"
#define NIP_API_ADDR_NOT_EXIST_FMT                  "%% Address not eixst %s"
#define NIP_API_ADDR_NOT_EXIST_FMT_C               "%% 地址不存在%s"

/* zhuzhm : interface */
#define IF_E_MALFORMED_ADDR_FMT     "%% Malformed address %s"
#define IF_E_MALFORMED_ADDR_FMT_C     "%%无效的地址格式%s"
#define IF_E_HIGHEST_ADDR_ERROR_FMT     "%% Highest byte shouldn't be 0 or 127 %s"
#define IF_E_HIGHEST_ADDR_ERROR_FMT_C   "%%地址不能以0和127开头%s"
#define IF_E_PREFIX_IS_ZERO_FMT     "%% Prefix shouldn't be 0 %s"
#define IF_E_PREFIX_IS_ZERO_FMT_C   "%%掩码长度不能是0%s"
#define IF_E_ADDR_IS_MULTI_FMT     "%% Highest byte should be smaller than 224 %s"
#define IF_E_ADDR_IS_MULTI_FMT_C    "%%地址开头不能比224大%s"
#define IF_E_CONFLIT_WITH_LOOPBACK_FMT     "%% Prefix shouldn't conflict with loopback address %s"
#define IF_E_CONFLIT_WITH_LOOPBACK_FMT_C    "%%和环回接口地址冲突%s"
#define IF_E_PREFIX_LEN_INVALID_FMT     "%% Prefix length shouldn't be 32 %s"
#define IF_E_PREFIX_LEN_INVALID_FMT_C   "%%掩码长度不能是32%s"
#define IF_E_PREFIX_INVALID_FMT     "%% Prefix shouldn't be network address or broadcast address %s"
#define IF_E_PREFIX_INVALID_FMT_C   "%%不能是网络地址和广播地址%s"
#define IF_E_CONFLIT_WITH_OTHER_ADDR_FMT     "%% Conflict with other interface's addresses %s"
#define IF_E_CONFLIT_WITH_OTHER_ADDR_FMT_C  "%%和其它接口上的地址冲突%s"
#define IF_E_CONFLIT_WITH_ADDR_FMT     "%% Conflict with the interface's addresses %s"
#define IF_E_CONFLIT_WITH_ADDR_FMT_C    "%%和本接口上的地址冲突%s"
#define IF_E_NO_MASTER_ADDR_FMT   "%% Must add primary before adding secondary %s"
#define IF_E_NO_MASTER_ADDR_FMT_C   "%%在配置第二地址前必须先配置主地址%s"
#define IF_E_SET_ADDR_FAILED_FMT   "%% Can't set interface IP address: %s.%s"
#define IF_E_SET_ADDR_FAILED_FMT_C  "%%设置地址失败:%s.%s"

#define IF_E_ADDR_NOT_FOUND_FMT   "%% Can't find address%s"
#define IF_E_ADDR_NOT_FOUND_FMT_C   "%%找不到地址%s"
#define IF_E_DELETE_SECOND_ADDR_FIRST_FMT   "%% Must delete secondary before deleting primary%s"
#define IF_E_DELETE_SECOND_ADDR_FIRST_FMT_C "%%删除主地址前必须先删除第二地址%s"
#define IF_E_UNSET_ADDR_FAILED_FMT   "%% Can't unset interface IP address: %s.%s"
#define IF_E_UNSET_ADDR_FAILED_FMT_C "%%删除地址失败%s%s"
#define IF_E_NOT_CONF_ADDR_FMT   "%% This is not configured address %s"
#define IF_E_NOT_CONF_ADDR_FMT_C    "%%这不是配置的地址%s"
#define IF_E_SECOND_IP_ADDR_REACH_MAX_FMT  "%% Secondary ip addresses have reached max.%s"
#define IF_E_SECOND_IP_ADDR_REACH_MAX_FMT_C "%%第二地址可配置数目达到最大%s"

#define IF_E_ADDR_IS_NOT_GROUP_FMT          "%% Not a IP multicast group address%s"
#define IF_E_ADDR_IS_NOT_GROUP_FMT_C      "%% 不是组播地址%s"
#define IF_E_GROUP_IS_WELLKNOW_FMT          "%% Illegal multicast group address%s"
#define IF_E_GROUP_IS_WELLKNOW_FMT_C         "%%不能加入知名组%s"
#define IF_E_GROUP_NOT_FOUND_FMT                "%%Group not found%s"
#define IF_E_GROUP_NOT_FOUND_FMT_C              "%%组地址不存在%s"
#define IF_E_CFG_GROUP_REACH_MAX_FMT        "%%Configed group address reach max%s"
#define IF_E_CFG_GROUP_REACH_MAX_FMT_C      "%%可配置的组播地址数目达到最大%s"
#define IF_E_JOIN_GROUP_FAILED_FMT              "%%Join group failed%s"
#define IF_E_JOIN_GROUP_FAILED_FMT_C          "%%加入组失败%s"
#define IF_E_LEAVE_GROUP_FAILED_FMT             "%%Leave group failed%s"
#define IF_E_LEAVE_GROUP_FAILED_FMT_C           "%%离开组失败%s"

#define IF_SHUTDOWN_ERROR_FMT                   "%% Can't shutdown interface%s"
#define IF_SHUTDOWN_ERROR_FMT_C     "%%关闭接口失败%s"
#define IF_SHUTDOWN_NOT_SUPPORT_FMT      "%% Shutdown not allowed on the interface.%s"
#define IF_SHUTDOWN_NOT_SUPPORT_FMT_C   "%%此接口不允许关闭%s"

/* interface status */
#define IF_E_NOT_UP_FMT                     "%%Interface not up%s"
#define IF_E_NOT_UP_FMT_C                   "%%接口没有UP%s"
#define IF_E_NOT_MULTICAST_FMT          "%%Interface not multicast%s"
#define IF_E_NOT_MULTICAST_FMT_C        "%%接口不支持多播%s"

/* zhuzhm : route */
#define RT_E_MALFORMED_PREFIX_FMT         "%% Malformed prefix address%s"
#define RT_E_MALFORMED_PREFIX_FMT_C "%%无效的地址格式%s"
#define RT_E_INVALID_PREFIX_FMT         "%% Invalid prefix address %s"
#define RT_E_INVALID_PREFIX_FMT_C       "%%无效的地址%s"
#define RT_E_MALFORMED_MASK_FMT         "%% Malformed mask address%s"
#define RT_E_MALFORMED_MASK_FMT_C       "%%无效的掩码格式%s"
#define RT_E_INVALID_MASK_FMT         "%% Invalid mask address%s"
#define RT_E_INVALID_MASK_FMT_C     "%%无效的掩码%s"
#define RT_E_INVALID_GATE_FMT         "%% Invalid nexthop address%s"
#define RT_E_INVALID_GATE_FMT_C     "%%无效的下一跳地址%s"
#define RT_E_NO_MATCH_ROUTE_FMT		"%%No matching route to delete%s"
#define RT_E_NO_MATCH_ROUTE_FMT_C	"%%没有找到该配置%s"
#define RT_E_INVALID_DISTANCE_FMT		"%%Invalid distance%s"
#define RT_E_INVALID_DISTANCE_FMT_C	"%%无效的距离%s"


/* zhuzhm : ethernet */
#define ETH_E_INVALID_MAC_ADDR_FMT          "%% Invalidation mac address%s"
#define ETH_E_INVALID_MAC_ADDR_FMT_C        "%%无效的MAC地址%s"
#define ETH_E_SET_MAC_ADDR_FAILED_FMT    "%% Can't set mac address%s"
#define ETH_E_SET_MAC_ADDR_FAILED_FMT_C "%%设置MAC地址失败%s"
#define ETH_E_NO_CONFIG_FMT                                 "%% There is no configure%s"
#define ETH_E_NO_CONFIG_FMT_C                   "%%没有配置%s"
#define ETH_E_CONFIG_NOT_EXIST_FMT                   "%% Configure not exist%s"
#define ETH_E_CONFIG_NOT_EXIST_FMT_C            "%%配置已经存在%s"
#define ETH_E_DEL_MAC_ADDR_FAILED_FMT                     "%% Can't delete mac address%s"
#define ETH_E_DEL_MAC_ADDR_FAILED_FMT_C     "%%删除MAC地址失败%s"

#endif  /* _API_ERRNO_FMT_H_ */

