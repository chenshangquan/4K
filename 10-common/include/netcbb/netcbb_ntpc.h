#ifndef _NETCBB_NTPC_H_
#define _NETCBB_NTPC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define NETCBB_NTPC_INTERVAL_MIN              (u32)5                           /* 请求与NTP-Servr进行时间同步的时间间隔的最小值 */
#define NETCBB_NTPC_INTERVAL_MAX              (u32)1024                        /* 请求与NTP-Servr进行时间同步的时间间隔的最大值 */
#define NETCBB_NTPC_MSG_BASE                  (u32)30000                       /*NTP中调用主动向NTP-Server同步时间时回调函数的消息码基址 */
#define NETCBB_NTPC_SYNC_TIME_SUCCESS_MSG     (u32)(NETCBB_NTPC_MSG_BASE + 1)  /*向NTP-Server同步时间校时成功，消息体：无*/
#define NETCBB_NTPC_SYNC_TIME_FAILED_MSG      (u32)(NETCBB_NTPC_MSG_BASE + 2)  /*向NTP-Server同步时间校时失败，消息体：无*/


/************************************************************
 * 函数名 : NetCbbNTPCSyncTimeCallBack
 *
 * 功能 : 调用主同向NTP-Server同步系统时间时，通知用户操作结果的回调函数
 *
 * 描述 : 无
 *
 *
 * 参数说明 :
 *      dwMsgID   - 事件类型，见上面的消息类型定义
 *      pMsg      - 与该事件类型相匹配的消息内容，目前都设置为NULL，以后可以扩展
 *
 * 返回值 : 暂时都定为0，以后可以扩展
 ***********************************************************/
typedef int(*NetCbbNtpcSyncTimeCallBack)(u32 dwMsgID, void* pMsg);


/************************************************************
 * 函数名 : NetCbbNTPCStart
 *
 * 功能 : 开启NTP-Client端功能
 *
 * 描述 : 无
 *
 *
 * 参数说明:
 *      dwServerIp          - NTP-Server的IP地址，网络字节序
 *      dwSyncTimeInterval  - 与NTP-Server进行时间同步的时间间隔，以秒为单位，范围：64s~1024s，
 *                            开启该功能之后，底层会按照用户设置的时间间隔，
 *                            每隔一段时间便向NTP-Server同步系统时间并设置到本地系统中
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetCbbNtpcStart(u32 dwServerIp, u32 dwSyncTimeInterval, NetCbbNtpcSyncTimeCallBack ptCallBack);


/************************************************************
 * 函数名 : NetCbbNTPCStop
 *
 * 功能 : 关闭NTP-Client端功能
 *
 * 描述 : 无
 *
 * 参数说明 :
 *        无
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetCbbNtpcStop(void);


/************************************************************
 * 函数名 : NetCheckNtpcServer
 *
 * 功能 : 检测NTP-Server是否可正常使用
 *
 * 描述 : 无
 *
 * 参数说明 :
 *        dwServerIp      - NTP-Server的IP地址，网络字节序
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetCheckNtpcServer(u32 dwServerIp);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_NETCBB_NTP_H_*/

