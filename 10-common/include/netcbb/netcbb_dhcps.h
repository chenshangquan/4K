#ifndef _NETCBB_DHCPS_H_
#define _NETCBB_DHCPS_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* DHCP-Server 回调函数的消息码基址 */
#define DHCPS_MSG_BASE        (u32)80000

/* DHCP-Server 最大网卡数*/
#define DHCPS_MAX_ETH_NUM     (u32)16

/* dhcp 服务器的DNS配置信息 */
typedef struct{
    u8 IsAssignDns;           /* 0 : 不指定(启用默认 dns 服务器); 1: 指定 */
    u32 dwDnsIp;              /* 网络序 : DNS的IP地址 */
    s8 achDnsName[128];       /* 网络序 : DNS 服务器 名字 */
}TDhcpServerDnsInfo;

/* dhcp 服务器的网卡结构体定义 */
typedef struct{
    u32 dwNetMask;            /* 网络序 : 掩码 */
    u32 dwSubNetMask;         /* 网络序 : 子网掩码 */
    u32 dwIpPoolStart;        /* 网络序 : 起始分配的地址 */
    u32 dwIpPoolEnd;          /* 网络序 : 终止分配的地址 */
    u32 dwRoutes;             /* 网络序 : 默认网关或者路由器地址 */
    u32 dwEthIp;              /* 网络序 : 网卡地址 */
    u32 dwEthId;              /* 网卡ID */
}TDhcpServerEthInfo;

/* dhcp 服务器的配置信息结构体定义 */
typedef struct{
    TDhcpServerEthInfo achTDhcpServerEthInfo[DHCPS_MAX_ETH_NUM];
    u32 dwDhcpServerEthCount; /* dhcp-server 网卡数目 */
    TDhcpServerDnsInfo tTDhcpServerDnsInfo;
}TDhcpServerConfInfo;

typedef struct
{
    u32 dwDhcpsIsRun;         /* 0:停止; 1: 运行 */
}TNetDhcpsState;

/************************************************************
 * 函数名 : NetDhcpsNotifyCallBack
 *
 * 功能 : 当DHCP-Server通知用户的回调函数
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      dwMsgID   - 事件类型，见上面的消息类型定义
 *                 (暂时不需要回调，因此未定义任何回调值)
 *      pMsg      - 与该事件类型相匹配的消息内容，见上面消息类型说明
 *
 * 返回值 : 暂时都定为0，以后可以扩展
 ***********************************************************/
typedef int(*NetDhcpsNotifyCallBack)(u32 dwMsgID, void* pMsg);

/************************************************************
 * 函数名 : NetDhcpsStart
 *
 * 功能 : 开启DHCP-Server功能
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      ptTDhcpsServerConfInfo   - dhcp-server 配置信息结构体指针
 *      ptDhcpsCallBack          - 上层注册的回调函数指针
 *
 * 返回值 : 暂时都定为0，以后可以扩展
 ***********************************************************/
s32 NetDhcpsStart(TDhcpServerConfInfo* ptDhcpServerConfInfo, NetDhcpsNotifyCallBack ptDhcpsCallBack);

/************************************************************
 * 函数名 : NetDhcpsStop
 *
 * 功能 : 关闭DHCP-Server功能
 *
 * 描述 : 无
 *
 * 参数说明 :
 *     无
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetDhcpsStop();

/************************************************************
 * 函数名 : NetDhcpsStopOneEth
 *
 * 功能 : 关闭某张网卡的DHCP-Server功能
 *
 * 描述 : 无
 *
 * 参数说明 :
 *     dwEthId - 网卡Id
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetDhcpsStopOneEth(u32 dwEthId);

/************************************************************
 * 函数名 : NetDhcpsGetState
 *
 * 功能 : 获取dhcp-server 运行状态
 *
 * 描述 : 无
 *
 * 参数说明 :
 *     dwEthId          - 网卡Id
 *     ptNetdhcpsState  - dhcp-server的运行状态
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetDhcpsGetState(u32 dwEthId, TNetDhcpsState* ptNetdhcpsState);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif