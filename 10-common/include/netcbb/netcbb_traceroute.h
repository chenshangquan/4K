#ifndef _NETCBB_TRACEROUTE_H_
#define _NETCBB_TRACEROUTE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* TNetTracerouteCallBack 返回值。对应TNetTracerouteCallBack 中 nResult 参数 */
#define  NET_TRACEROUTE_CB_ERROR                               101
#define  NET_TRACEROUTE_CB_TIMEOUT                             102
#define  NET_TRACEROUTE_CB_MIDDLE_ROUTE                        103
#define  NET_TRACEROUTE_CB_REACH_DST                           104
#define  NET_TRACEROUTE_CB_NETWORK_UNREACHABLE                 105
#define  NET_TRACEROUTE_CB_HOST_UNREACHABLE                    106        /* 回调此类型时 traceroute会自动停止 */

#define  NET_TRACEROUTE_CREAT_CB_THREAD_FAILED                 (NET_TRACEROUTE_BASE_ERROR + 1)
#define  NET_TRACEROUTE_STASRT_FAILED                          (NET_TRACEROUTE_BASE_ERROR + 2)
#define  NET_TRACEROUTE_STOP_FAILED                            (NET_TRACEROUTE_BASE_ERROR + 3)
#define  NET_TRACEROUTE_CREAT_SEM_FAILED                       (NET_TRACEROUTE_BASE_ERROR + 4)

typedef struct
{
    u32 dwDstIp;               /* 网络序ip地址 */
    u32 dwTtl;                 /* TTL值 适用范围0-255, 0或者255可以取到, 业务可自行进行限制，但最大不超过255 */
}TTraceroutePara;

/************************************************************
 * 函数名 : TNetTracerouteCallBack
 *
 * 功能 : Traceroute 回调函数
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      nResult    - Traceroute 回调结果(NET_TRACEROUTE_CB_ERROR, NET_TRACEROUTE_CB_TIMEOUT, 
 *                                             NET_TRACEROUTE_CB_MIDDLE_ROUTE, NET_TRACEROUTE_CB_REACH_DST)
 *      nTtl       - TTL值
 *      nTripTime  - 网络传输时间值(注意:单位是微秒, 不是毫秒)
 *      dwIp       - 路由ip地址
 *      achDomName - 路由域名(暂不支持)
 *      nUserID    - 用户ID标志，用户区分不同的用户调用(暂时不支持多用户调用，赋值0)
 *      nErrType   - 错误类型(暂时可以忽略,还未支持)
 *      nErrCode   - 错误码(暂时可以忽略,还未支持)
 *
 * 返回值 : 由上层业务实现
 ***********************************************************/
typedef int(*TNetTracerouteCallBack)(s32 nResult, s32 nTtl, s32 nTripTime, u32 dwIp, s8* achDomName, s32 nUserID, s32 nErrType, s32 nErrCode);

/************************************************************
 * 函数名 : NetTracerouteStart
 *
 * 功能 : 以太网Traceroute开始
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      ptTraceroutePara   - traceroute 参数
 *      nUserID            - 用户ID标志，用户区分不同的用户调用(暂时不支持多用户调用，请赋值0)
 *      ptCallBackFunc     - traceroute结果的回调函数
 *
 * 返回值 : NET_CALLBACK_NULL                       - 回调函数没有定义
 *          NET_TRACEROUTE_CREAT_CB_THREAD_FAILED   - 创建回调线程失败
 *          NET_TRACEROUTE_CREAT_SEM_FAILED         - 创建信号量失败
 *          NET_TRACEROUTE_STASRT_FAILED            - 启动失败
 *          OK                                      - 成功
 ***********************************************************/
s32 NetTracerouteStart(TTraceroutePara* ptTraceroutePara, s32 nUserID, TNetTracerouteCallBack ptCallBackFunc);

/************************************************************
 * 函数名 : NetTracerouteStop
 *
 * 功能 : 以太网Traceroute终止
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      nUserID            - 用户ID(暂时不支持，请赋值0)
 *
 * 返回值 : NET_TRACEROUTE_STOP_FAILED   - 终止失败
 *          OK                           - 成功
 ***********************************************************/
s32 NetTracerouteStop(s32 nUserID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_INTERFACE_H_ */

