#ifndef _NETCBB_DHCPC_H_
#define _NETCBB_DHCPC_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* DHCPC回调函数的消息码基址 */
#define DHCPC_MSG_BASE                 (u32)30000
/* 通知用户DHCP获得的IP地址的回调消息，消息体：TNetDhcpcNotify  */
#define DHCPC_GET_IP_MSG               (u32)(DHCPC_MSG_BASE+1)
/* 通知用户设备失去DHCP获得的IP地址的回调消息，消息体：TNetDhcpcNotify */
#define DHCPC_LOSS_IP_MSG              (u32)(DHCPC_MSG_BASE+2)
/* 通知用户因租约到期但又得不到地址原因导致设备失去DHCP获得的IP地址的回调消息，消息体：TNetDhcpcNotify */
#define DHCPC_RENEW_FAIL_MSG           (u32)(DHCPC_MSG_BASE+3)

#define DHCPC_IFDOWN_LOSS_IP_MSG       (u32)(DHCPC_MSG_BASE+4)
#define DHCPC_IFERROR_LOSS_IP_MSG      (u32)(DHCPC_MSG_BASE+5)
#define DHCPC_DNS_MAX_DNS_SERVER            64

/* DHCPC读文件时buffer缓冲区的最大值 */
#define DHCPC_MAX_READ_FILE_BUFFER_LENGTH   128

/* DHCP 启动状态 */
#define DHCPC_ALREADY_START          1
#define DHCPC_NOT_START              0


/* DNS 配置命令 */
#define DNS_CMD_AUTO        1
#define DNS_CMD_STATIC      0

/* resolv.conf keywords */
#define DNS_KEYWORD_NAMSERV    "nameserver"  /* 定义DNS服务器的IP 地址 */
#define DNS_KEYWORD_DOMAIN     "domain" 　   /* 定义本地域名 */
#define DNS_KEYWORD_SEARCH     "search"      /* 定义域名的搜索列表 */
#define DNS_KEYWORD_SORTLIST   "sortlist"    /* 对返回的域名进行排序 */

/* 通知用户DHCP获得或者失去的IP地址的结构体 */
typedef struct{
    u32 byEthId;    /* 取得/失去IP地址的网口号 */
    u32 dwIpAddrs;  /* 取得/失去的IP地址，网络字节序 */
    u32 dwMask;     /* 取得/失去的IP地址子网掩码，网络字节序 */
    u32 dwGateWay;  /* 取得/失去的默认网关，网络字节序，有可能为0，因为有的DHCP-Server不一定为设备指定默认网关 */
    u32 dwDnsNum;   /* DNS Server 数量最多为64个 */
    u32 dwDnsServer[DHCPC_DNS_MAX_DNS_SERVER];  /* 取得/失去的DNS Server ，网络字节序 */
}TNetDhcpcNotify;

/* 开启了DHCP-Client端功能的网口上获取的IP地址、租约等相关信息结构体 */
typedef struct{
    u32 byEthId;     /* 取得IP地址的网口号 */
    u32 dwIpAddrs;   /* 取得的IP地址，网络字节序 */
    u32 dwMask;      /* 取得的IP地址子网掩码，网络字节序 */
    u32 dwGateWay;   /* 取得的默认网关，网络字节序，有可能为0，因为有的DHCP-Server不一定为设备指定默认网关 */
    u32 dwLeaseInfo; /* 总的租约时间，以秒为单位 */
    u32 dwDnsNum;    /*DNS Server 数量最多为64个 */
    u32 dwDnsServer[DHCPC_DNS_MAX_DNS_SERVER];  /* 取得/失去的DNS Server ，网络字节序 */
}TNetDhcpcLeaseInfo;

typedef struct
{
    u32 dwDhcpcIsRun;
}TNetDhcpcState;

/************************************************************
 * 函数名 : NetDhcpcNotifyCallBack
 *
 * 功能 : 当DHCP获得IP地址或者因某种原因失去已获得的IP地址时，
 *        通知用户的回调函数
 * 描述 : 无
 *
 * 参数说明 :
 *      dwMsgID   - 事件类型，见上面的消息类型定义
 *      pMsg      - 与该事件类型相匹配的消息内容，见上面消息类型说明
 *
 * 返回值 : 暂时都定为0，以后可以扩展 
 ***********************************************************/
typedef int(*NetDhcpcNotifyCallBack)(u32 dwMsgID, void* pMsg);

/************************************************************
 * 函数名 : NetDhcpcStart
 *
 * 功能 : 在指定的网口上开启DHCP-Client端功能
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      byEthId         - 要开启DHCP-Client端功能的网口号(从0开始)
 *      ptDhcpcCallBack - 上层注册的回调函数指针
 *      bSetDefautGate  - 回调网关是否设为默认网关
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetDhcpcStart(u32 byEthId, NetDhcpcNotifyCallBack ptDhcpcCallBack, BOOL32 bSetDefautGate);

/************************************************************
 * 函数名 : NetDhcpcRenew
 *
 * 功能 : 在开启了DHCP-Client端功能的网口上主动请求更新租约
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      byEthId         - 要更新租约的网口号(从0开始)
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 *          NET_PROCESS_NOT_EXIST - 进程不存在
 ***********************************************************/
s32 NetDhcpcRenew(u32 byEthId);

/************************************************************
 * 函数名 : NetDhcpcGetLeaseInfo
 *
 * 功能 : 在开启了DHCP-Client端功能的网口上获取租约等相关信息
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      byEthId            - 开启了DHCP-Client端功能的网口号(从0开始)
 *      ptNetDhcpLeaseInfo - 返回的包含租约等信息的结构体指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetDhcpcGetLeaseInfo(u32 byEthId, TNetDhcpcLeaseInfo* ptNetDhcpcLeaseInfo);

/************************************************************
 * 函数名 : NetDhcpcStop
 *
 * 功能 : 在指定的网口上关闭DHCP-Client端功能
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      byEthId   - 要关闭DHCP-Client端功能的网口号(从0开始)
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetDhcpcStop(u32 byEthId);

/************************************************************
 * 函数名 : NetDhcpcGetIfstate
 *
 * 功能 : 在指定的网口上的dhcp信息
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      byEthId   - 网口号(从0开始)
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 *          NET_PROCESS_NOT_EXIST - UDHCPC进程不存在
 ***********************************************************/
s32 NetDhcpcGetIfstate(u32 byEthId, TNetDhcpcState* ptNetdhcpcIfState);

/************************************************************
 * 函数名 : NetDNSSet
 *
 * 功能 : 设置静态DNS
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      byEthId   - 网口号(从0开始)
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetDNSSet(u32 byEthId, s32 DNSCmd, s8* pchDNSset[], s32 dwNum);

/************************************************************
 * 函数名 : NetDNSSetEx
 *
 * 功能 : 设置DNS
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      byEthId   - 网口号(从0开始)
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetDNSSetEx(u32 byEthId, u32 adwDns[], s32 dwNum);

/************************************************************
 * 函数名 : NetDNSDel
 *
 * 功能 : 删除DNS
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      byEthId   - 网口号(从0开始)
 *      adwDNSset - dns数组(网络序)
 *      dwNum     - dns个数
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetDNSDel(u32 dwEthId, u32 adwDNSset[], s32 dwNum);

/************************************************************
 * 函数名 : NetDNSAdd
 *
 * 功能 : 增加DNS
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      byEthId   - 网口号(从0开始)
 *      adwDNSset - dns数组(网络序)
 *      dwNum     - dns 个数
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetDNSAdd(u32 dwEthId, u32 adwDNSset[], s32 dwNum);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
