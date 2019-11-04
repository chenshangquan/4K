/*! \file libsswrap.h
    \brief 提供报文平滑发送支持.

    平滑发送模块允许上层应用通过API设置发往指定目地的报文的平均发送速率,
    并允许一定范围内的突发流量.

    版权所有 2007 kedacom \n
    版本: 1.0 \n
    历史:  \n
      - 初始版本.     张元一(070131)

    \author 张元一
    \date 2007-1-30
*/

/** @defgroup ss 平滑发送
 *  提供报文平滑发送支持.
 *  @{
 */


#ifndef SSWRAP_H
#define SSWRAP_H

#ifdef __cplusplus
extern "C" {
#endif
    
/**
 * 错误码定义.
 */
enum ErrCode
{
    ENOSUPP,  ///< 内核不支持
    ENOROUTE, ///< 目地地址不可达
    ENORULE,  ///< 规则不存在
    EINTERNAL,///< 内部错误
    ETOOMANY, ///< 太多的规则
};

extern int SSErrno; ///< 平滑发送模块错误码,可通过此变量获取错误细节

/**
 * 添加/修改一条平滑发送规则,如果端口号为0,则不匹配端口号.\n
 * <b>注意</b>: 峰值速率必须大于或者等于平均速率,并且这个函数目前不是线程安全的
 *
 * \param dwDestIp     要进行限速的报文的目地IP,必须为主机字节序.
 * \param wDestPort    要进行限速的报文的目地端口,必须为主机字节序.
 * \param dwRate       报文的平均发送速率,单位为KBps
 * \param dwPeak       报文的峰值速率,单位为KBps.
 * \param dwSec        峰值速率持续时间
 * \return 如果成功返回1,失败则返回0 <br>
 *         可以通过SSErrno变量获取错误细节,可能的错误包括: <br>
 *           - <b>EINVAL</b>    无效的参数 <br>
 *           - <b>ENOROUTE</b>  目地地址不可达. <br>
 *           - <b>ENOSUPP</b>   内核不支持. <br>
 *           - <b>ETOOMANY</b>  太多的规则.<br>
 *           - <b>EINTERNAL</b> 内部错误.<br>
 */
s32 SetSSRule(u32 dwDestIp, u16 wDestPort, u32 dwRate, u32 dwPeak, u32 dwSec);

/**
 * 删除一条平滑发送规则,如果端口号为0,则不匹配端口号.<br>
 * <b>注意</b>: 这个函数目前不是线程安全的.
 *
 * \param dwDestIp   要删除的规则的目地IP.
 * \param wDestPort  要删除的规则的目地端口.
 * \return 如果成功返回1,失败则返回0 <br>
 *         可以通过SSErrno变量获取错误细节,可能的错误包括: <br>
 *           - <b>EINVAL</b>    无效的参数 <br>
 *           - <b>ENOROUTE</b>  目地地址不可达. <br>
 *           - <b>ENOSUPP</b>   内核不支持. <br>
 *           - <b>EINTERNAL</b> 内部错误.<br>
 */
s32 UnsetSSRule(u32 dwDestIp, u16 wDestPort);

/**
 * 在所有接口上关闭平滑发送功能.<br>
 * <b>注意</b>: 这个函数目前不是线程安全的.
 *
 * \return 如果成功返回1,失败则返回0 <br>
 *         可以通过SSErrno变量获取错误细节,可能的错误包括: <br>
 *           - <b>ENOSUPP</b>   内核不支持. <br>
 *           - <b>EINTERNAL</b> 内部错误.<br> 
 */
s32 CloseSmoothSending();

#ifdef __cplusplus
}
#endif

/* @} */

#endif /* SS_H */

