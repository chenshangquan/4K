#ifndef _NETCBB_DEF_H_
#define _NETCBB_DEF_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* api 返回值错误码定义，所有的返回值都已经统一，业务可以创建一个函数来处理返回值。不在头文件描述中一一介绍 */
#define NET_BASE_ERROR            1100
#define NET_IF_BASE_ERROR         1200
#define NET_E1_BASE_ERROR         1300
#define NET_PING_BASE_ERROR       1400
#define NET_TRACEROUTE_BASE_ERROR 1500
#define NET_BOND_BASE_ERROR       1600

/* 根据这4种TIMEOUT返回值，可以采取对应的措施,例如重新调用对应函数或者忽略 */
#define NET_IPC_SENDC_TIMEOUT        (NET_BASE_ERROR+1)    /* client 发送消息超时 */
#define NET_IPC_RECVC_TIMEOUT        (NET_BASE_ERROR+2)    /* client 接受消息超时 */
#define NET_IPC_SENDD_TIMEOUT        (NET_BASE_ERROR+3)	   /* daemon发送消息超时 */
#define NET_IPC_RECVD_TIMEOUT        (NET_BASE_ERROR+4)    /* daemon接受消息超时 */
#define NET_INVALID_PARAMETER        (NET_BASE_ERROR+5)    /* 无效的参数 */
#define NET_CALLBACK_NULL            (NET_BASE_ERROR+6)    /* 回调函数没有定义 */
#define NET_FORK_ERROR               (NET_BASE_ERROR+7)    /* 创建子进程失败 */
#define NET_PROCESS_NOT_EXIST        (NET_BASE_ERROR+8)    /* 进程不存在 */
#define NET_MODULE_INIT_ERROR        (NET_BASE_ERROR+9)    /* 模块启动失败 */
#define NET_GET_MODULE_INFO_ERROR    (NET_BASE_ERROR+10)   /* 获取模块信息失败 */
#define NET_NOT_THE_SAME_NET         (NET_BASE_ERROR+11)   /* 网络参数不在同一个网段 */


#define NET_IF_NOT_EXIST             (NET_IF_BASE_ERROR+1) /* 接口不存在 */
#define NET_IF_ADDR_NOT_EXIST        (NET_IF_BASE_ERROR+2) /* 地址不存在 */
#define NET_IF_UP                    (NET_IF_BASE_ERROR+3) /* 接口打开 */
#define NET_IF_DOWN                  (NET_IF_BASE_ERROR+4) /* 接口关闭 */
#define NET_IF_BUSY                  (NET_IF_BASE_ERROR+5) /* 接口使用中 */

#define NET_BOND_HAS_STARTED         (NET_BOND_BASE_ERROR+1) /* bond模式已经启动 */

#define IP_ROUTE_MAX_NUM          10
#define IP_ADDR_MAX_NUM           16   /* 在Linux下一个网口可以配置的最多的IP地址 */
#define NET_MAX_VERSION_LEN       256  /* 版本号的最大长度 */


/* NetSetEthParam函数中byIpOrMac输入值的宏定义 */
#define Net_SET_IP_AND_MASK         1      /* 设置IP地址和子网掩码 */
#define Net_SET_MAC_ADDR            2      /* 设置MAC地址 */
#define Net_SET_ETH_ALL_PARAM       3      /* 设置以太网的IP地址、子网掩码和MAC地址 */
#define Net_SET_ETH_SEC_IP          4      /* 设置以太网第二IP 地址 */


#define NET_DEF_FILE_PATH_LEN       100
#define NET_DEF_FILE_LEN            32
#define NET_DEF_STR_LEN             32
#define NET_DEF_STR_LEN_LONGER      100

#define MAX_NIC_NUM                 3      /* 最多支持网卡数目 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

