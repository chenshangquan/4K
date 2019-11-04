/*! \file libipconf.h
    \brief 提供IP冲突检测支持

    IP冲突检测模块允许上层应用通过API设置检测IP冲突的时间将隔,如果检测到存在IP冲突
    则上层应用设置的回调函数会被调用.

    版权所有 2007 kedacom \n
    版本: 1.0 \n
    历史:  \n
      - 初始版本.     张元一(070601)

    \author 张元一
    \date 2007-6-01
*/

/** @defgroup ipconf IP冲突检测
    提供IP冲突检测支持<br><br>
    <b>演示程序命令如下:</b>
    - <b>start interval</b> <br>
    启动IP冲突检测, interval为检测时间间隔,如果存在IP冲突,则将打印如下信息:
    "MAC地址为 XX:XX:XX:XX:XX:XX 的机器与我们配置了相同的IP地址: X.X.X.X",
    否则打印"检测已启动."
    - <b>stop</b><br>
    停止IP冲突检测,如果不存在IP冲突,则打印:"没有检测到IP地址冲突提供IP冲突检测API支持",
    否则打印:"检测已停止."
    - <b>help</b><br>
    显示帮助信息
    - <b>exit</b><br>
    退出演示程序
 *  @{
 */

#ifndef IPCONFLICT_H
#define IPCONFLICT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 回调函数
 *
 * \param mac_addr     产生冲突的主机的MAC地址
 * \param addr         产生冲突的IP地址.
 * \return 无返回值
 */
typedef void(*ipconf_func)(const u_char* mac_addr, const struct in_addr* addr);

/**
 * 开始IP冲突检测
 *
 * \param user_func    发生冲突时的回调函数
 * \return 如果成功返回0, 失败返回-1.
 */
extern s32 ipconf_start(ipconf_func func,int tval);

/**
 * 停止IP冲突检测
 *
 * \return 如果成功返回0, 失败返回-1
 */
extern s32 ipconf_stop(void);

#ifdef __cplusplus
}
#endif

/* @} */

#endif /* IPCONFLICT_H */

