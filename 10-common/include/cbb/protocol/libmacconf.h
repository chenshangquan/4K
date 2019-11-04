/*! \file libmacconf.h
    \brief 提供MAC冲突检测支持

    MAC冲突检测模块允许上层应用通过API启动,如果检测到存在MAC冲突
    则上层应用设置的回调函数会被调用.

    版权所有 2008 kedacom \n
    版本: 1.0 \n
    历史:  \n
      - 初始版本.     邹岱桂(080108)

    \author 邹岱桂
    \date 2008-01-08
*/

/** @defgroup macconf MAC冲突检测
    提供MAC冲突检测支持<br><br>
    <b>演示程序命令如下:</b>
    - <b>start</b> <br>
    启动MAC冲突检测,如果存在MAC冲突,则将打印如下信息:
    "IP地址为 X.X.X.X 的机器与我们配置了相同的MAC地址: XX:XX:XX:XX:XX:XX ",
    否则打印"检测已启动."
    - <b>stop</b><br>
    停止MAC冲突检测,如果不存在MAC冲突,
    否则打印:"检测已停止."
    - <b>help</b><br>
    显示帮助信息
    - <b>exit</b><br>
    退出演示程序
 *  @{
 */

#ifndef MACCONFLICT_H
#define MACCONFLICT_H

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
typedef void(*macconf_func)(const u_char* mac_addr, const struct in_addr* addr,const char *local);

/**
 * 开始MAC冲突检测
 *
 * \param user_func    发生冲突时的回调函数
 * \return 如果成功返回0, 失败返回-1.
 */
extern s32 macconf_start(macconf_func user_func);

/**
 * 停止MAC冲突检测
 *
 * \return 如果成功返回0, 失败返回-1
 */
extern s32 macconf_stop(void);

#ifdef __cplusplus
}
#endif

/* @} */

#endif /* MACCONFLICT_H */

