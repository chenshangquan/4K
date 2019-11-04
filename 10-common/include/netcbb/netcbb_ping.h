#ifndef _NETCBB_PING_H_
#define _NETCBB_PING_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* TPingCallBack回调的返回值，对应参数为nResult */
#define    NET_PING_REPLY          0    /* ping包正常回应 */
#define    NET_PING_TIMEOUT        1    /* ping包超时 */
#define    NET_PING_ERROR          2    /* ping包系统错误 */
#define    NET_PING_NET_UNREACH    3    /* ping包网络不可达 */


#define    NET_PING_CREAT_CB_THREAD_FAILED    (NET_PING_BASE_ERROR + 1)
#define    NET_PING_STASRT_FAILED             (NET_PING_BASE_ERROR + 2)
#define    NET_PING_STOP_FAILED               (NET_PING_BASE_ERROR + 3)
#define    NET_PING_ALREADY_START             (NET_PING_BASE_ERROR + 4)
#define    NET_PING_ALREADY_STOP              (NET_PING_BASE_ERROR + 5)


/* NetPing接口传入参数结构体 */
typedef struct{
    s32 nPktSize;   /* 要ping的数据报的大小，以字节为单位不得小于56，如果小于56，将赋值56 */
    s32 nTimeOut;   /* ping的超时值，以秒为单位 */
    s32 nTtl;       /* TTL值 适用范围0-255, 0或者255可以取到, 业务可自行进行限制，但最大不超过255 */
    s32 nCount;     /* ping包数目 */
}TPingOpt;

/************************************************************
 * 函数名 : TNetPingCallBack
 *
 * 功能 : ping回调函数
 *
 * 描述 :
 *
 * 参数说明 :
 *      nResult   - ping 回调结果(NET_PING_REPLY, NET_PING_TIMEOUT, NET_PING_ERROR)
 *      nTtl      - TTL值
 *      nTripTime - 网络传输时间值(注意:单位是微秒, 不是毫秒)
 *      nSeq      - ping包次序
 *      nUserID   - 用户ID标志，用户区分不同的用户调用(暂时不支持多用户调用
 *      nErrType  - 错误类型(暂时可以忽略,还未支持)
 *      nErrCode  - 错误码(暂时可以忽略,还未支持)
 * 返回值 : 由上层业务实现
 ***********************************************************/
typedef int(*TNetPingCallBack)(s32 nResult, s32 nTtl, s32 nTripTime, s32 nSeq, s32 nUserID, s32 nErrType, s32 nErrCode);

/************************************************************
 * 函数名 : NetPingStart
 *
 * 功能 : 以太网ping接口
 *
 * 描述 :
 *
 * 参数说明 :
 *      dwDestIP       - Ping的目的IP地址(网络序)
 *      ptPingOpt      - Ping的参数结构体指针
 *      nUserID        - 用户ID标志，用户区分不同的用户调用(暂时不支持多用户调用，请赋值0)
 *      ptCallBackFunc - Ping结果的回调函数
 * 返回值 : ok - 成功
 *          NET_CALLBACK_NULL  - 回调函数没有定义
 *          NET_PING_CREAT_CB_THREAD_FAILED  - 创建回调线程失败
 *          NET_PING_STASRT_FAILED  - 启动失败
 ***********************************************************/
s32 NetPingStart(u32 dwDestIP, TPingOpt* ptPingOpt, s32 nUserID, TNetPingCallBack ptCallBackFunc);

/************************************************************
 * 函数名 : NetPing
 *
 * 功能 : 以太网ping终止
 *
 * 描述 :
 *
 * 参数说明 :
 *      nUserID        - 用户ID标志，用户区分不同的用户调用(暂时不支持多用户调用，请赋值0)
 * 返回值 : ok - 成功
 *          NET_PING_STOP_FAILED  - 终止失败
 ***********************************************************/
s32 NetPingStop(s32 nUserID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_NETCBB_INTERFACE_H_*/

