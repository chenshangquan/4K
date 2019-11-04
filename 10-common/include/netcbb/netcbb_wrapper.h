#ifndef _NETCBB_WRAPPER_H_
#define _NETCBB_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "netcbb_def.h"
#include "netcbb_interface.h"
#include "netcbb_dhcpc.h"
#include "netcbb_pppoe.h"
#include "netcbb_sntp.h"
#include "netcbb_webs.h"
#include "netcbb_dhcps.h"
#include "netcbb_ntpc.h"
#include "netcbb_serv.h"
#include "netcbb_e1.h"
#include "netcbb_ping.h"
#include "netcbb_traceroute.h"

/************************************************************
 * 函数名 : NetInit
 *
 * 功能 : 本模块的初始化函数
 *
 * 描述 : 无
 *
 * 参数说明 :
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetInit(void);

/************************************************************
 * 函数名 : NetQueryNetcbbVersion
 *
 * 功能 : 提供给业务层调用的os版本号查询
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      pchVer    - 获取版本的字符串指针
 *      dwBufLen  - 该字符串的长度
 *      pdwVerLen - 获取版本的实际字符串长度，该长度返回之前必须和dwBufLen比较是否溢出，正常时才对pVer赋值
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetQueryVersion(char* pchVer, u32 dwBufLen);

/************************************************************
 * 函数名 : NetLogSwitch
 *
 * 功能 : 本模块打印开关(默认关闭)
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      1  -  打开log
 *      0  -  关闭log
 *       默认关闭
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetLogSwitch(u32 dwSwitch);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_WRAPPER_H_ */

