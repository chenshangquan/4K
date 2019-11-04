#ifndef _NETCBB_INTERFACE_H_
#define _NETCBB_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 以太网相关的结构定义 */
/* 以太网参数结构 */
typedef struct{
    u32 dwIpAdrs;  /* 网络字节序 */
    u32 dwIpMask;  /* 网络字节序 */
    u8 byMacAdrs[6];
}TNetEthParam;

/* 以太网mac地址结构 */
typedef struct{
    u8 byMacAdrs[6];
}TNetEthMac;

/* 以太网参数结构 */
typedef struct{
    u32 dwIpNum;                                  /* 有效的IP地址数 */
    TNetEthParam atNetEthParam[IP_ADDR_MAX_NUM];  /* 存放IP地址等信息的数组 */
}TNetEthParamAll;

/* 单个路由参数结构 */
typedef struct{
    u32 byEthId;         /* 网口id */
    u32 dwDesIpNet;      /* 目的子网，网络字节序 */
    u32 dwDesIpMask;     /* 掩码，网络字节序 */
    u32 dwGwIpAdrs;      /* 网关ip地址，网络字节序 */
    u32 dwRoutePri;      /* 路由优先级(1-255)，默认为0 */
}TNetIpRouteParam;

/* 多个路由参数结构 */
typedef struct{
    u32 dwIpRouteNum;    /* 得到的实际路由个数 */
    TNetIpRouteParam tNetIpRouteParam[IP_ROUTE_MAX_NUM];
}TNetAllIpRouteInfo;

/* 网卡统计信息 */
typedef struct{
	u32 byEthId;
	u64 dwBandSended; /* (bit/s) 1Gbit/s == 1000Mbit/s == 1000*1000kbit/s == 1000*1000*1000 bit/s */
	u64 dwBandRecved; /* (bit/s) */
}TNetDevStat;

typedef struct{
	u32 byEthId;
	u32 dwIpaddr;
	u8 abyMacAddr[6];
}TNetConflictInfo;

#define NETCBB_IP_CONFLICT    1
#define NETCBB_MAC_CONFLICT   2

/* IP地址冲突回调函数类型定义 */
typedef void (*TIpConflictCallBack)(u32 dwType, u8* pbyMacAddr, u32 dwIpAdrs);

typedef void (*TIpConflictCallBackEx)(u32 dwType, TNetConflictInfo *ptConflictInfo);

/* 网卡统计通知函数 */
typedef void (*TDevStatNotifyCallBack)(TNetDevStat aptdevStat[], u32 dwEthNum);

/************************************************************
 * 函数名 : NetGetEthParam
 *
 * 功能 : 读取以太网参数，含ip、mask、mac *
 * 描述 : 无
 *
 * 参数说明 :
 *      byEthId       - 以太网ID号（0~x）
 *      ptNetEthParam -存放以太网信息的结构指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetGetEthParam(u32 byEthId, TNetEthParam* ptNetEthParam);

/************************************************************
 * 函数名 : NetGetEthMac
 *
 * 功能 : 读取以太网参数，含ip、mask、mac
 *
 * 描述 : 该api不提供支持，和NetGetEthParam有重合地方
 *
 * 参数说明 :
 *      byEthId       - 以太网ID号（0~x）
 *      ptNetEthMac   - 存放以太网mac信息的结构指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetGetEthMac(u32 byEthId, TNetEthMac* ptNetEthMac);

/************************************************************
 * 函数名 : NetGetEthParamAll
 *
 * 功能 : 获取一个网口上所有的以太网参数，多个IP地址的情况
 *
 * 描述 :
 *
 * 参数说明 :
 *      byEthId          - 以太网ID号（0~x）
 *      ptNetEthParamAll - 存放以太网信息的结构指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetGetEthParamAll(u32 byEthId, TNetEthParamAll* ptNetEthParamAll);

/************************************************************
 * 函数名 : NetGetEthParamSecIP
 *
 * 功能 : 获取一个网口上所有第二IP地址
 *
 * 描述 : 不提供支持，和NetGetEthParamAll重复，读取NetGetEthParamAll
 *        的第2、3数组可以获取到对应的ip。
 *
 * 参数说明 :
 *      byEthId          - 以太网ID号（0~x）
 *      ptNetEthParamAll - 存放以太网信息的结构指针
 *                         用于返回第二IP地址的，返回的地址个数由
 *                         dwIpNum指定，结构中的atNetEthParam数组成员
 *                         只有IP和Mask有效，Mac地址没有效
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetGetEthParamSecIP(u32 byEthId, TNetEthParamAll* ptNetEthParamAll);

/************************************************************
 * 函数名 : NetSetEthParam
 *
 * 功能 : 设置以太网参数
 *
 * 描述 :
 *
 * 参数说明 :
 *      byEthId      - 以太网ID号（0~x）
 *      byIpOrMac    - 为设置命令选择（见Netcbb_def.h中相关的宏定义），可以
 *                     设置主IP，第二IP和Mac
 *                        Net_SET_IP_AND_MASK    1   设置IP地址和子网掩码(会先清除当前网卡所有的地址)
                          Net_SET_MAC_ADDR       2   设置MAC地址(设mac功能不支持，无实际意义)
                          Net_SET_ETH_ALL_PARAM  3   设置以太网的IP地址、子网掩码和MAC地址(不支持)
                          Net_SET_ETH_SEC_IP     4   设置以太网第二IP 地址
 *      ptNetEthParam - 指向存放设定值的TNetEthParam数据结构的指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 系统错误
 *          NET_INVALID_PARAMETER - 网络参数无效
 ***********************************************************/
s32 NetSetEthParam(u32 byEthId, u32 byIpOrMac, TNetEthParam* ptNetEthParam);

/************************************************************
 * 函数名 : NetDelEthParamSecIP
 *
 * 功能 : 删除第二IP地址
 *
 * 描述 : 不提供支持，和NetDelEthParamIPAndMask重复
 *
 * 参数说明 :
 *      byEthId       - 以太网ID号（0~x），x视不同的板子而定
 *      ptNetEthParam - 指向存放设定值的TNetEthParam数据结构的指针，结构中只有IP和Mask有效
 *
 * 返回值 : OK    - 成功
 *          ERROR - 系统错误
 *          NET_INVALID_PARAMETER - 网络参数无效
 ***********************************************************/
s32 NetDelEthParamSecIP(u32 byEthId, TNetEthParam* ptNetEthParam);

/************************************************************
 * 函数名 : NetAddEthParamIPAndMask
 *
 * 功能 : 增加指定IP地址
 *
 * 描述 :
 *
 * 参数说明 :
 *      byEthId       - 以太网ID号（0~x），x视不同的板子而定
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetAddEthParamIPAndMask(u32 byEthId, TNetEthParam* ptNetEthParam);

/************************************************************
 * 函数名 : NetDelEthParamIPAndMask
 *
 * 功能 : 删除指定IP地址
 *
 * 描述 :
 *
 * 参数说明 :
 *      byEthId       - 以太网ID号（0~x）
 *      ptNetEthParam - 指向存放设定值的TNetEthParam数据结构的指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetDelEthParamIPAndMask(u32 byEthId, TNetEthParam* ptNetEthParam);

/************************************************************
 * 函数名 : NetDelEthParam
 *
 * 功能 : 删除指定的以太网接口
 *
 * 描述 : 在Linux下，一个网口可以配置多个IP地址，该接口会删除
 *        该接口上的所有IP地址
 *
 * 参数说明 :
 *      byEthId       - 以太网ID号（0~x），x视不同板子而定
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetDelEthParam(u32 byEthId);

/************************************************************
 * 函数名 : NetSetDefGateway
 *
 * 功能 : 设置默认网关ip
 *
 * 描述 :
 *
 * 参数说明 :
 *      byEthId     - 以太网ID号（0~x）
 *      dwGateway   - 默认网关ip地址，长整型，网络序
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetSetDefGateway(u32 byEthId, u32 dwGateway);

/************************************************************
 * 函数名 : NetGetDefGateway
 *
 * 功能 : 获取默认网关ip
 *
 * 描述 :
 *
 * 参数说明 :
 *      byEthId     - 以太网ID号（0~x）
 *      pdwGateway  - 默认网关ip地址，长整型，网络序
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetGetDefGateway(u32 byEthId, u32* pdwGateway);

/************************************************************
 * 函数名 : NetDelDefGateway
 *
 * 功能 : 删除默认网关ip
 *
 * 描述 :
 *
 * 参数说明 :
 *      byEthId     - 以太网ID号（0~x）
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetDelDefGateway(u32 byEthId);

/************************************************************
 * 函数名 : NetSetMtu
 *
 * 功能 : 设置某一网卡的MTU值
 *
 * 描述 :
 *        暂时不支持hisi3536
 * 参数说明 :
 *      byEthId   - 以太网ID号（0~x）
 *      dwMtu     - 设置的MTU值
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 *          NET_IF_BUSY - 网卡正在使用中，设置失败
 ***********************************************************/
s32 NetSetMtu(u32 byEthId, u32 dwMtu);

/************************************************************
 * 函数名 : NetGetMtu
 *
 * 功能 : 获取某一网卡的MTU值
 *
 * 描述 :
 *      对于hisi3536暂时不支持，会报错
 *
 * 参数说明 :
 *      byEthId   - 以太网ID号（0~x）
 *      pdwMtu    - 存储mtu值的buffer指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetGetMtu(u32 byEthId, u32* pdwMtu);

/************************************************************
 * 函数名 : NetGetNextHopIpAddr
 *
 * 功能 : 获取通往指定ip的第一跳路由ip地址
 *
 * 描述 : 暂不支持，意义不大，实现较麻烦。完全可以由NetPing
 *        来判断地址是否可以到达
 *
 * 参数说明 :
 *      dwDstIpAddr  - 目的ip地址，长整型，网络序
 *      dwDstMask    - 目的掩码，长整型，网络序
 *
 * 返回值 : 成功返回第一跳路由ip地址，长整型
 ***********************************************************/
u32 NetGetNextHopIpAddr(u32 dwDstIpAddr, u32 dwDstMask);

/************************************************************
 * 函数名 : NetAddOneIpRoute
 *
 * 功能 : 增加一条路由
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      byEthId   - 以太网ID号（0~x）
 *      ptNetIpRouteParam    - 指向存放路由信息的TNetIpRouteParam结构指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetAddOneIpRoute(u32 byEthId, TNetIpRouteParam* ptNetIpRouteParam);

/************************************************************
 * 函数名 : NetDelOneIpRoute
 *
 * 功能 : 删除一条路由
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      byEthId   - 以太网ID号（0~x）
 *      ptNetIpRouteParam    - 指向存放路由信息的TNetIpRouteParam结构指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetDelOneIpRoute(u32 byEthId, TNetIpRouteParam* ptNetIpRouteParam);

/************************************************************
 * 函数名 : NetGetAllIpRoute
 *
 * 功能 : 读取所有路由信息
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      ptNetIpRouteParam    - 指向存放路由信息的TNetIpRouteParam结构指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetGetAllIpRoute(TNetAllIpRouteInfo* ptNetAllIpRouteInfo);

/************************************************************
 * 函数名 : NetIpConflictCallBackReg
 *
 * 功能 : 注册ip地址冲突时回调函数,当设备的IP地址和外部设备冲
 *        突时，会调用该函数通知业务程序
 *
 * 描述 :
 *        此函数与NetIpConflictCallBackRegEx互斥使用
 *
 * 参数说明 :
 *      ptFunc    - 执行业务程序注册的回调函数指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetIpConflictCallBackReg(TIpConflictCallBack ptFunc);

/************************************************************
 * 函数名 : NetIpConflictCallBackRegEx
 *
 * 功能 : 注册ip地址冲突时回调函数,当设备的IP地址和外部设备冲
 *        突时，会调用该函数通知业务程序
 *
 * 描述 :
 *        此函数与NetIpConflictCallBackReg互斥使用
 *
 * 参数说明 :
 *      ptFunc    - 执行业务程序注册的回调函数指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetIpConflictCallBackRegEx(TIpConflictCallBackEx ptFunc);

/************************************************************
 * 函数名 : NetIpOnceConflicted
 *
 * 功能 : 查询系统是否发生过ip地址冲突
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      无
 *
 * 返回值 : TRUE or FALSE
 ***********************************************************/
BOOL32 NetIpOnceConflicted(void);

/************************************************************
 * 函数名 : NetSetDscp
 *
 * 功能 : 设置ip包头dscp值(0-63)
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      nSockfd    - 要设置的套接字描述符
 *      byDscp     - 要设置的dscp值(0-63)
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetSetDscp(s32 nSockfd, u8 byDscp);

/************************************************************
 * 函数名 : NetInterfaceShutdown
 *
 * 功能 : 关闭网卡
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      byEthId    - 以太网的编号
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetInterfaceShutdown(u32 byEthId);

/************************************************************
 * 函数名 : NetInterfaceNoShutdown
 *
 * 功能 : 打开网卡
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      byEthId    - 以太网的编号
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetInterfaceNoShutdown(u32 byEthId);

/************************************************************
 * 函数名 : NetCheckTheSameNet
 *
 * 功能 : 校验ip和网关是否在同一网段
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      dwIpAddr  - ip 地址
 *      dwMask    - 掩码
 *      dwGateway - 网关
 *
 * 返回值 : OK    - 校验成功, 在同一个网段
 *          NET_NOT_THE_SAME_NET  - 不在同一个网段
 *          NET_INVALID_PARAMETER - 参数本身错误
 ***********************************************************/
s32 NetCheckTheSameNet(u32 dwIpAddr, u32 dwMask, u32 dwGateway);

/************************************************************
 * 函数名 : NetGetEthNum
 *
 * 功能 : 获取网卡数量
 *
 * 描述 :
 *
 * 参数说明 :
 *      pnEthNum  - 指向需要获取的网卡号
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetGetEthNum(s32* pnEthNum);

/************************************************************
 * 函数名 : NetGetEthState
 *
 * 功能 : 获取网卡状态
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      nEthNum  - 指向需要获取的网卡号
 *      pdwFlag  - 网卡状态：NET_IF_UP     网卡up
 *                           NET_IF_DOWN   网卡down
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetGetEthState(s32 nEthNum, u32* pdwFlag);

/************************************************************
 * 函数名 : NetModifyNetPwd
 *
 * 功能 : 设置网络基础协议密码 (涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      pUser    - 用户名 *      pPasswd  - 用户设置密码
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetModifyNetPwd(s8* pUser, s8* pPasswd);

/************************************************************
 * 函数名 : NetAddNetUser
 *
 * 功能 : 增加用户(涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *     调用此函数增加的为管理员用户
 *
 * 参数说明 :
 *      pUser    - 用户名
 *      pPasswd  - 用户设置密码
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetAddNetUser(s8* pUser, s8* pPasswd);

/************************************************************
 * 函数名 : NetAddNetCommonUser
 *
 * 功能 : 增加用户(涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *     调用此函数增加的为普通用户
 *
 * 参数说明 :
 *      pUser    - 用户名
 *      pPasswd  - 用户设置密码
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetAddNetCommonUser(s8* pUser, s8* pPasswd);

/************************************************************
 * 函数名 : NetDelNetUser
 *
 * 功能 : 删除用户(涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      pUser    - 用户名
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetDelNetUser(s8* pUser);

/************************************************************
 * 函数名 : NetModifyIpRouteMetric
 *
 * 功能 : 修改一条路由的metric
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      ptNetIpRouteParam    - 指向存放路由信息的TNetIpRouteParam结构指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetModifyIpRouteMetric(TNetIpRouteParam* ptNetIpRouteParam);

/************************************************************
 * 函数名 : NetStatCallBackRegister
 *
 * 功能 : 注册设备统计值回调函数
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      nInterval  - 回调间隔，同时根据此间隔计算发送以及接收的间隔.
 *      pfNotifyCb - 回调通知函数.
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetStatNotifyCallbackReg(int nInterval, TDevStatNotifyCallBack pfNotifyCb);

/************************************************************
 * 函数名 : NetStatStop
 *
 * 功能 : 关闭注册设备统计值
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *     		无
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetStatStop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_INTERFACE_H_ */
