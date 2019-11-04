#ifndef _NETCBB_WEBS_H_
#define _NETCBB_WEBS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define NET_WEBS_ENABLE          1
#define NET_WEBS_DISABLE         2
#define NET_WEBS_INSPECT_ENABLE  3
#define NET_WEBS_INSPECT_DISABLE 4

#define NET_WEBS_ERR_BASE        100

#define NET_WEBS_PORT_ERR       (NET_WEBS_ERR_BASE+1)  /* 端口绑定出错 */

/************************************************************
 * 函数名 : NetWebsEnable
 *
 * 功能 : 启动或停止web server
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      port     - 要启用端口号
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetWebsEnable(s32 port);

/************************************************************
 * 函数名 : NetWebsDisable
 *
 * 功能 : 启动或停止web server
 *
 * 描述 : 无
 *
 * 参数说明 :
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetWebsDisable(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_WEBS_H_ */

