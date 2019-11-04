#ifndef _NETCBB_SNTP_H_
#define _NETCBB_SNTP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#define SNTP_INTERVEL_MIN            (u32)64                 /* 请求与SNTP-Servr进行时间同步的时间间隔的最小值 */
#define SNTP_INTERVEL_MAX            (u32)1024               /* 请求与SNTP-Servr进行时间同步的时间间隔的最大值 */
#define SNTP_MSG_BASE                (u32)40000              /* SNTP中调用主动向SNTP-Server同步时间时回调函数的消息码基址 */
#define SNTP_SYNC_TIME_SUCCESS_MSG   (u32)( SNTP_MSG_BASE+1) /* 向SNTP-Server同步时间校时成功，消息体：无 */
#define SNTP_SYNC_TIME_FAILED_MSG    (u32)( SNTP_MSG_BASE+2) /* 向SNTP-Server同步时间校时失败，消息体：无 */


/************************************************************
 * 函数名 : NetSNTPSyncTimeCallBack
 *
 * 功能 : 调用主同向SNTP-Server同步系统时间时，通知用户操作结果的回调函数
 *
 * 描述 :
 *
 * 参数说明 :
 *      dwMsgID    - 事件类型，见上面的消息类型定义
 *      pMsg       - 与该事件类型相匹配的消息内容，目前都设置为NULL，以后可以扩展
 *
 * 返回值 : 暂时都定为0，以后可以扩展
 ***********************************************************/
typedef int(*NetSNTPSyncTimeCallBack)(u32 dwMsgID, void* pMsg);

/************************************************************
 * 函数名 : NetSNTPStart
 *
 * 功能 : 开启SNTP-Client端功能
 *
 * 描述 :
 *
 * 参数说明 :
 *      dwServerIp         - SNTP-Server的IP地址，网络字节序
 *      dwSyncTimeInterval - 与SNTP-Server进行时间同步的时间间隔，
 *                               以秒为单位，范围：64s~1024s，开启该功能之后，底层
 *                               会按照用户设置的时间间隔，每隔一段时间便向
 *                               SNTP-Server同步系统时间并设置到本地系统中
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetSNTPStart(u32 dwServerIp, u32 dwSyncTimeInterval, NetSNTPSyncTimeCallBack ptCallBack);

/************************************************************
 * 函数名 : NetSNTPStop
 *
 * 功能 : 关闭SNTP-Client端功能
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetSNTPStop(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_SNTP_H_ */

