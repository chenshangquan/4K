/*=============================================================================
模   块   名: 会议控制台业务功能库
文   件   名: evmcslib.h
相 关  文 件: 无
文件实现功能: mcslib中消息常量定义
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2005/04/26  4.0     王昊        创建
=============================================================================*/

#ifndef _EVMCSLIB_20050426_H_
#define _EVMCSLIB_20050426_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "eventid.h"


//会控消息的上限，跳过部分WM_USER 往上几十的控件消息
#define MCS_DISP_MSG_BGN                                (WM_USER + 0x80)
//1 与MCU通信消息
//1.1   建立连接

//1.1.1	建链
    //MCU准入应答, 消息体: s32(在TCtrlData中的连接索引)
    #define MCS_DISP_CONNECT_ACK                        (MCS_DISP_MSG_BGN + 1)
    //MCU拒绝应答, 消息体: u32(主MCU的IP地址, 为0表示没有主MCU)
    #define MCS_DISP_CONNECT_NACK                       (MCS_DISP_MSG_BGN + 2)
    //连接MCU超时, 消息体: 无
    #define MCS_DISP_CONNECT_MCU_TIMEOUT                (MCS_DISP_MSG_BGN + 3)
    //Osp断链, 消息体: s32(会话索引) + s8[MAXLEN_MCU_NAME](MCU名)
    #define MCS_DISP_OSP_DISCONNECT                     (MCS_DISP_MSG_BGN + 4)
    //MCU连接的控制台数满, 消息体: 无
    #define MCS_DISP_OSP_OVERFLOW                       (MCS_DISP_MSG_BGN + 5)

//1.1.2	同步本地时间
    //系统同步时间成功, 消息体: 无
    #define MCS_DISP_SYNCTIME_ACK                       (MCS_DISP_MSG_BGN + 6)
    //系统同步时间失败, 消息体: 无
    #define MCS_DISP_SYNCTIME_NACK                      (MCS_DISP_MSG_BGN + 7)

//1.1.3 级联MCU控制
	//下级MCU的锁定状态通知, 消息体: CConfId + n * ( TMCU + u8 (1-锁定，0-解锁) )
	#define MCS_DISP_MCULOCKSTATUS_NOTIF                (MCS_DISP_MSG_BGN + 8)

	//会议中级联的Mcu媒体源通知, 消息体: CConfId + n * ( TMcu + TMt )
	#define MCS_DISP_MCUMEDIASRC_NOTIF                  (MCS_DISP_MSG_BGN + 9)

//1.2   MCU操作
//1.2.1 MCU状态
    //获取TMcuStatus成功应答, 消息体: TMcuStatus
    #define MCS_DISP_GETMCUSTATUS_ACK                   (MCS_DISP_MSG_BGN + 20)
    //获取TMcuStatus失败应答, 消息体: 无
    #define MCS_DISP_GETMCUSTATUS_NACK                  (MCS_DISP_MSG_BGN + 21)
    //TMcuStatus通知, 消息体: TMcuStatus
    #define MCS_DISP_MCUSTATUS_NOTIF                    (MCS_DISP_MSG_BGN + 22)

//1.2.2 CPU使用率
    //获取CPU使用率成功应答, 消息体: 无
    #define MCS_DISP_GETMCUCPUUSAGE_ACK                 (MCS_DISP_MSG_BGN + 25)
    //获取CPU使用率失败应答, 消息体: 无
    #define MCS_DISP_GETMCUCPUUSAGE_NACK                (MCS_DISP_MSG_BGN + 26)
    //CPU使用率通知, 消息体: u8(0-100)(%)
    #define MCS_DISP_MCUCPUUSAGE_NOTIF                  (MCS_DISP_MSG_BGN + 27)

//1.2.3 获取MCU配置
    //获取MCU设备配置成功应答, 消息体: 无
    #define MCS_DISP_GETMCUCFG_ACK                      (MCS_DISP_MSG_BGN + 28)
    //获取MCU设备配置失败应答, 消息体: 无
    #define MCS_DISP_GETMCUCFG_NACK                     (MCS_DISP_MSG_BGN + 29)

//1.2.4 修改MCU外设配置
    //修改MCU外设配置成功应答, 消息体: 无
    #define MCS_DISP_MODIFYMCUEQPCFG_ACK                (MCS_DISP_MSG_BGN + 30)
    //修改MCU外设配置失败应答, 消息体: 无
    #define MCS_DISP_MODIFYMCUEQPCFG_NACK               (MCS_DISP_MSG_BGN + 31)
    //MCU设备配置通知, 消息体: TMcuEqpCfg
    #define MCS_DISP_MCUEQPCFG_NOTIF                    (MCS_DISP_MSG_BGN + 32)

//1.2.5 修改MCU单板配置
    //修改MCU单板配置成功应答, 消息体: 无
    #define MCS_DISP_MODIFYMCUBRDCFG_ACK                (MCS_DISP_MSG_BGN + 33)
    //修改MCU单板配置失败应答, 消息体: 无
    #define MCS_DISP_MODIFYMCUBRDCFG_NACK               (MCS_DISP_MSG_BGN + 34)
    //单板配置通知(消息体可能大于32K), 消息体: CBrdCfg数组
    #define MCS_DISP_MCUBRDCFG_NOTIF                    (MCS_DISP_MSG_BGN + 35)

    //录像机配置通知, 消息体: TEqpRecCfgInfo数组(可能为空)
    #define MCS_DISP_RECCFG_NOTIF                       (MCS_DISP_MSG_BGN + 36)

    //高清BAS配置通知, 消息体: TEqpBasHDCfgInfo数组(可能为空)
    #define MCS_DISP_BAS_HD_CFG_NOTIF                   (MCS_DISP_MSG_BGN + 37)

//1.2.6 修改MCU基本配置
    //修改MCU基本配置成功应答, 消息体: 无
    #define MCS_DISP_MODIFYMCUGENERALCFG_ACK            (MCS_DISP_MSG_BGN + 40)
    //修改MCU基本配置失败应答, 消息体: 无
    #define MCS_DISP_MODIFYMCUGENERALCFG_NACK           (MCS_DISP_MSG_BGN + 41)
    //MCU基本配置通知, 消息体: TMcuGeneralCfg
    #define MCS_DISP_MCUGENERALCFG_NOTIF                (MCS_DISP_MSG_BGN + 42)

//1.2.7 获取MCU时间
    //会控获取mcu系统时间成功, 消息体: TKdvTime(当前mcu系统时间)
    #define MCS_DISP_GETMCUTIME_ACK                     (MCS_DISP_MSG_BGN + 43)
    //会控获取mcu系统时间失败, 消息体: 无
    #define MCS_DISP_GETMCUTIME_NACK                    (MCS_DISP_MSG_BGN + 44)

//1.2.8 修改MCU时间
    //会控修改mcu系统时间成功, 消息体: TKdvTime(当前mcu系统时间)
    #define MCS_DISP_MODIFYMCUTIME_ACK                  (MCS_DISP_MSG_BGN + 45)
    //会控修改mcu系统时间失败, 消息体: 无
    #define MCS_DISP_MODIFYMCUTIME_NACK                 (MCS_DISP_MSG_BGN + 46)

//1.2.9 重起单板
    //会控重起单板成功, 消息体: u8(单板索引)
    #define MCS_DISP_REBOOTBRD_ACK                      (MCS_DISP_MSG_BGN + 47)
    //会控重起单板失败, 消息体: u8(单板索引)
    #define MCS_DISP_REBOOTBRD_NACK                     (MCS_DISP_MSG_BGN + 48)
    //单板在线状态通知(MCU主动发送), 消息体: TBoardStatusNotify
    #define MCS_DISP_BRDSTATUS_NOTIF                    (MCS_DISP_MSG_BGN + 49)
// liuruifei [4/4/2006]
//1.2.10 配置上传/下载
	//下载配置文件成功
	#define MCS_DISP_DOWNLOADCFG_ACK				    (MCS_DISP_MSG_BGN + 50)
	//下载配置文件失败
	#define MCS_DISP_DOWNLOADCFG_NACK				    (MCS_DISP_MSG_BGN + 51)
	//上传配置文件成功
	#define MCS_DISP_UPLOADCFG_ACK					    (MCS_DISP_MSG_BGN + 52)
	//上传配置文件失败
	#define MCS_DISP_UPLOADCFG_NACK			    		(MCS_DISP_MSG_BGN + 53)
	//升级文件成功
	#define MCS_DISP_UPGRADE_ACK					    (MCS_DISP_MSG_BGN + 54)
	//升级文件失败
	#define MCS_DISP_UPGRADE_NACK					    (MCS_DISP_MSG_BGN + 55)

//1.2.11 板卡升级
    #define MCS_DISP_UPDATEBRDFILE_NOTIF                (MCS_DISP_MSG_BGN + 56)

//1.2.12 主备失败通知
	//主备失败通知 ，消息体:TMSEnvConflict
	#define MCS_MSSYN_FAILED_NOTIF						(MCS_DISP_MSG_BGN + 57)

//1.2.13 会控操作失败通知(可以是任何操作, 主要通知级联情况下的消息)
    #define MCS_DISP_ALARMINFO_NOTIF                    (MCS_DISP_MSG_BGN + 58)

//1.2.14 N+1备份 备份端 将数据同步到 N端 消息通知
    //N+1备份 备份端 将数据同步到 N端 同步成功
    #define MCS_DISP_NPLUSROLLBACK_ACK                  (MCS_DISP_MSG_BGN + 59)
    //N+1备份 备份端 将数据同步到 N端 同步失败
    #define MCS_DISP_NPLUSROLLBACK_NACK                 (MCS_DISP_MSG_BGN + 60)

//1.2.15 上传文件
    //MCU同意进行升级
    #define MCS_DISP_STARTUPDATEDSCVERSION_ACK          (MCS_DISP_MSG_BGN + 61)
    //MCU不同意进行升级
    #define MCS_DISP_STARTUPDATEDSCVERSION_NACK         (MCS_DISP_MSG_BGN + 62)
    //MCU向MCS发出的接收成功回应
    #define MCS_DISP_DSCUPDATEFILE_ACK                  (MCS_DISP_MSG_BGN + 63)
    //MCU向MCS发出的接收失败回应
    #define MCS_DISP_DSCUPDATEFILE_NACK                 (MCS_DISP_MSG_BGN + 64)
    //上传文件超时
    #define MCS_DISP_UPLOAD_FILE_TIMEOUT                (MCS_DISP_MSG_BGN + 65)

//1.2.16 更新telnet密码
    //更新telnet密码成功回应
    #define MCS_DISP_UPDATETELNETLOGININFO_ACK          (MCS_DISP_MSG_BGN + 66)
    //更新telnet密码失败回应
    #define MCS_DISP_UPDATETELNETLOGININFO_NACK         (MCS_DISP_MSG_BGN + 67)

//1.3	会议管理
//1.3.1	请求会议列表
    //即时会议完整信息通知, 消息体: CConfId + TConfInfo
    #define MCS_DISP_CONFINFO_NOTIF                     (MCS_DISP_MSG_BGN + 70)
    //即时会议简单信息通知, 消息体: CConfId + TBasicConfInfo
    #define MCS_DISP_SIMCONFINFO_NOTIF                  (MCS_DISP_MSG_BGN + 71)
    //会议模板(预约会议)信息通知, 消息体: CConfId + TConfInfo
    #define MCS_DISP_TEMSCHCONFINFO_NOTIF               (MCS_DISP_MSG_BGN + 72)

//1.3.2	创建会议
    //会议控制台在MCU上创建一个会议成功应答, 消息体: CConfId + u8(CONF_TAKEMODE_*)
    #define MCS_DISP_CREATECONF_ACK                     (MCS_DISP_MSG_BGN + 73)
    //会议控制台在MCU上创建一个会议失败, 消息体: 无
    #define MCS_DISP_CREATECONF_NACK                    (MCS_DISP_MSG_BGN + 74)

    //会议模板成功地转变成即时/预约会议, 消息体: CConfId + u8(CONF_TAKEMODE_*)
    #define MCS_DISP_HOLDCONF_BYTEMPLATE_ACK            (MCS_DISP_MSG_BGN + 75)
    //会议模板转变成即时/预约会议失败, 消息体: 无
    #define MCS_DISP_HOLDCONF_BYTEMPLATE_NACK           (MCS_DISP_MSG_BGN + 76)

    //会议在GK上注册成功通知, 消息体: CConfId
    #define MCS_DISP_CONFREGGKSUCCESS_NOTIF             (MCS_DISP_MSG_BGN + 77)	
    //会议在GK上注册失败通知, 消息体: CConfId, 参见消息头中的错误码
    #define MCS_DISP_CONFREGGKFAIL_NOTIF                (MCS_DISP_MSG_BGN + 78)

//1.3.3	结束会议
    //MCU成功结束会议应答, 消息体: CConfId
    #define MCS_DISP_RELEASECONF_ACK                    (MCS_DISP_MSG_BGN + 80)
    //MCU拒绝结束会议, 消息体: CConfId
    #define MCS_DISP_RELEASECONF_NACK                   (MCS_DISP_MSG_BGN + 81)
    //MCU结束会议通知, 消息体: CConfId + u8(CONF_TAKEMODE_*)
    #define MCS_DISP_RELEASECONF_NOTIF                  (MCS_DISP_MSG_BGN + 82)

//1.3.4	保护会议
//1.3.4.1	锁定会议
    //MCU成功改变会议保护方式会议应答, 消息体: CConfId + BOOL(TRUE or FALSE)
    #define MCS_DISP_CHANGECONFLOCKMODE_ACK             (MCS_DISP_MSG_BGN + 85)
    //MCU拒绝改变会议保护方式会议, 消息体: 无
    #define MCS_DISP_CHANGECONFLOCKMODE_NACK            (MCS_DISP_MSG_BGN + 86)
    //MCU改变会议保护方式, 消息体: CConfId + u8(会议保护方式)
    #define MCS_DISP_CONFLOCKMODE_NOTIF                 (MCS_DISP_MSG_BGN + 87)

//1.3.4.2	会议独享
    //MCU给会议控制台的当前独享会议的控制台的信息,
	//消息体: CConfId + 4byte(独享会控的IP,网络序)+32byte(独享会控的用户名)
    #define MCS_DISP_LOCKUSERINFO_NOTIF                 (MCS_DISP_MSG_BGN + 88)

//1.3.4.3	输入密码
    //MCU要求会议控制台输入会议密码, 消息体: CConfId
    #define MCS_DISP_ENTERCONFPWD_REQ                   (MCS_DISP_MSG_BGN + 90)
    //MCU提示会议控制台密码错误, 消息体: CConfId
    #define MCS_DISP_WRONGCONFPWD_NOTIF                 (MCS_DISP_MSG_BGN + 91)

//1.3.4.4	更改会议密码
    //MCU成功更改会议密码应答, 消息体: CConfId + 32byte字符串
    #define MCS_DISP_CHANGECONFPWD_ACK                  (MCS_DISP_MSG_BGN + 92)
    //MCU拒绝更改会议密码, 消息体: CConfId
    #define MCS_DISP_CHANGECONFPWD_NACK                 (MCS_DISP_MSG_BGN + 93)
    //MCU修改会议密码通知, 消息体: CConfId + 32byte字符串
    #define MCS_DISP_CONFPWD_NOTIF                      (MCS_DISP_MSG_BGN + 94)

//1.3.5	保存会议
    //MCU成功保存会议应答, 消息体: CConfId
    #define MCS_DISP_SAVECONF_ACK                       (MCS_DISP_MSG_BGN + 96)
    //MCU拒绝保存会议, 消息体: CConfId
    #define MCS_DISP_SAVECONF_NACK                      (MCS_DISP_MSG_BGN + 97)

//1.3.6	修改预约会议
    //MCU成功修改预约会议, 消息体: CConfId + u8(TakeMode)
    #define MCS_DISP_MODIFYCONF_ACK                     (MCS_DISP_MSG_BGN + 100)
    //MCU拒绝修改预约会议, 消息体: CConfId
    #define MCS_DISP_MODIFYCONF_NACK                    (MCS_DISP_MSG_BGN + 101)  

//1.3.7	延长会议
    //MCU成功延长会议应答, 消息体: CConfId + u16(分钟)
	#define MCS_DISP_DELAYCONF_ACK                      (MCS_DISP_MSG_BGN + 102)
	//MCU拒绝延长会议应答, 消息体: CConfId
	#define MCS_DISP_DELAYCONF_NACK                     (MCS_DISP_MSG_BGN + 103)
	//MCU延长会议通知, 消息体: CConfId + u16(延长时间，单位：分钟)
	#define MCS_DISP_DELAYCONF_NOTIF                    (MCS_DISP_MSG_BGN + 104)	
	//MCU通知会控会议结束剩余时间, 消息体: CConfId + u16(会议结束剩余时间, 单位: 分钟)
	#define MCS_DISP_CONFTIMELEFT_NOTIF                 (MCS_DISP_MSG_BGN + 105)
//1.3.8 MAU状态 //xts20081125
    //获取TMAuStatus成功应答, 消息体: TMauStatus
    #define MCS_DISP_GETMAUSTATUS_ACK                   (MCS_DISP_MSG_BGN + 106)
    //获取TMcuStatus失败应答, 消息体: 无
    #define MCS_DISP_GETMAUSTATUS_NACK                  (MCS_DISP_MSG_BGN + 107)
    //TMcuStatus通知, 消息体: TMcuStatus
    #define MCS_DISP_MAUSTATUS_NOTIF                    (MCS_DISP_MSG_BGN + 108)
//1.4	会议操作
//1.4.1	指定主席
	//MCU成功指定会议主席应答, 消息体: CConfId
	#define MCS_DISP_SPECCHAIRMAN_ACK                   (MCS_DISP_MSG_BGN + 110)
	//MCU拒绝指定会议主席应答, 消息体: CConfId
	#define MCS_DISP_SPECCHAIRMAN_NACK                  (MCS_DISP_MSG_BGN + 111)
	//指定主席通知, 
    //上层可以通过处理MCS_DISP_SIMCONFINFO_NOTIF忽略此消息,
    //消息体: CConfId + TMt(做主席的终端) 
	#define MCS_DISP_SPECCHAIRMAN_NOTIF                 (MCS_DISP_MSG_BGN + 112)
	//终端申请主席通知, 消息体: CConfId + TMt(申请的终端) 
	#define MCS_DISP_MTAPPLYCHAIRMAN_NOTIF              (MCS_DISP_MSG_BGN + 113)

//1.4.2	取消主席
	//MCU成功取消会议主席应答, 消息体: CConfId
    #define MCS_DISP_CANCELCHAIRMAN_ACK                 (MCS_DISP_MSG_BGN + 115)
	//会议中无主席, 消息体: CConfId
	#define MCS_DISP_CANCELCHAIRMAN_NACK                (MCS_DISP_MSG_BGN + 116)
	//取消主席通知, 
    //上层可以通过处理MCS_DISP_SIMCONFINFO_NOTIF忽略此消息,
    //消息体: CConfId
	#define MCS_DISP_CANCELCHAIRMAN_NOTIF               (MCS_DISP_MSG_BGN + 117)

//1.4.3 主席模式
    //MCU通知主席模式, 消息体: CConfId
    #define MCS_DISP_CONFCHAIRMODE_NOTIF                (MCS_DISP_MSG_BGN + 118)

//1.4.4	指定发言 
    //MCU成功指定发言者, 消息体: CConfId
    #define MCS_DISP_SPECSPEAKER_ACK                    (MCS_DISP_MSG_BGN + 120)
    //指定之前的发言者被取消, 消息体: CConfId
    #define MCS_DISP_SPECSPEAKER_NACK                   (MCS_DISP_MSG_BGN + 121)
    //指定发言通知, 
    //上层可以通过处理MCS_DISP_SIMCONFINFO_NOTIF忽略此消息,
    //消息体: CConfId + TMt(发言终端)
    #define MCS_DISP_SPECSPEAKER_NOTIF                  (MCS_DISP_MSG_BGN + 122)

    //MCU通知会控终端申请发言, 消息体: CConfId + TMt(申请终端)
    #define MCS_DISP_MTAPPLYSPEAKER_NOTIF               (MCS_DISP_MSG_BGN + 123)

//1.4.5	取消发言
    //MCU成功取消会议主席应答, 消息体: CConfId
    #define MCS_DISP_CANCELSPEAKER_ACK                  (MCS_DISP_MSG_BGN + 125)
    //取消发言人失败, 消息体: CConfId
	#define MCS_DISP_CANCELSPEAKER_NACK                 (MCS_DISP_MSG_BGN + 126)
	//取消发言人通知, 
    //上层可以通过处理MCS_DISP_SIMCONFINFO_NOTIF忽略此消息,
    //消息体: CConfId
	#define MCS_DISP_CANCELSPEAKER_NOTIF                (MCS_DISP_MSG_BGN + 127)

//1.4.6	增加终端
	//MCU同意会议控制台增加终端, 消息体: CConfId
	#define MCS_DISP_ADDMT_ACK                          (MCS_DISP_MSG_BGN + 130)
	//MCU拒绝会议控制台增加终端, 消息体: CConfId
	#define MCS_DISP_ADDMT_NACK                         (MCS_DISP_MSG_BGN + 131)

//1.4.7	删除终端
	//终端被成功驱逐, 消息体: CConfId
	#define MCS_DISP_DELMT_ACK                          (MCS_DISP_MSG_BGN + 132)
	//消息描述：拒绝驱逐终端, 消息体: CConfId
	#define MCS_DISP_DELMT_NACK                         (MCS_DISP_MSG_BGN + 133)

//1.4.8	开始监控
	//MCU应答会议控制台监控终端, MCU_MCS_STARTSWITCHMC_ACK,
	//消息体: u8(监控通道)
	#define MCS_DISP_STARTMONITOR_ACK                   (MCS_DISP_MSG_BGN + 135)
	//MCU拒绝会议控制台监控终端, MCU_MCS_STARTSWITCHMC_NACK, 消息体: 无
	#define MCS_DISP_STARTMONITOR_NACK                  (MCS_DISP_MSG_BGN + 136)
	//MCU给会控的开始监控通知, MCU_MCS_STARTPLAY_NOTIF,
	//消息体: u8(监控通道)
    //注：MCU传过来的消息内容已经整理到CMcuSession::m_atMonitorMember里
	#define MCS_DISP_STARTMONITOR_NOTIF                 (MCS_DISP_MSG_BGN + 137)

//1.4.9 停止监控
	//MCU应答会议控制台监控终端, MCU_MCS_STOPSWITCHMC_ACK, 消息体: u8(通道号)
	#define MCS_DISP_STOPMONITOR_ACK                    (MCS_DISP_MSG_BGN + 138)
	//MCU拒绝会议控制台监控终端, MCU_MCS_STOPSWITCHMC_NACK, 消息体: 无
	#define MCS_DISP_STOPMONITOR_NACK                   (MCS_DISP_MSG_BGN + 139)
	//MCU给会控的停止监控通知, MCU_MCS_STOPPLAY_NOTIF, 消息体: u8(通道号)
	#define MCS_DISP_STOPMONITOR_NOTIF                  (MCS_DISP_MSG_BGN + 140)

//1.4.10 发送短消息
	//MCU给会议控制台的发送短消息通知, 消息体: CConfId + TRunMsgInfo 
    #define MCS_DISP_SENDRUNMSG_NOTIF                   (MCS_DISP_MSG_BGN + 145)

//1.4.11 请求终端列表
    //MCU发给会议控制台的终端列表通知, 消息体: CConfId + TMcu + TMtExt数组
    #define MCS_DISP_MTLIST_NOTIF                       (MCS_DISP_MSG_BGN + 150)
    //MCU发给会议控制台的终端所有信息通知, 消息体: CConfId + TConfAllMtInfo
    #define MCS_DISP_CONFALLMTINFO_NOTIF                (MCS_DISP_MSG_BGN + 151)

//1.4.12 指定本会场向上级回传的终端
    //MCU成功指定本会场向上级回传的终端 ,消息体：  TMt
    #define MCS_DISP_SPECOUTVIEW_ACK                    (MCS_DISP_MSG_BGN + 152)
    //指定本会场向上级回传的终端失败，消息体：  TMt
    #define MCS_DISP_SPECOUTVIEW_NACK                   (MCS_DISP_MSG_BGN + 153)

//1.5	会议控制
//1.5.1	查询轮询参数
    //MCU应答会议控制台查询会议轮询参数, 消息体: CConfId + TPollInfo + TMtPollParam数组
    #define MCS_DISP_GETPOLLPARAM_ACK                   (MCS_DISP_MSG_BGN + 155) 
    //MCU拒绝会议控制台查询会议轮询参数, 消息体: CConfId
    #define MCS_DISP_GETPOLLPARAM_NACK                  (MCS_DISP_MSG_BGN + 156)
    //MCU通知会议控制台当前的轮询状态, 消息体: CConfId + TPollInfo
    #define MCS_DISP_POLLSTATE_NOTIF                    (MCS_DISP_MSG_BGN + 157)
    //MCU会议轮询参数改变通知, 消息体: CConfId + TPollInfo + TMtPollParam数组
    #define MCS_DISP_POLLPARAMCHANGE_NTF                (MCS_DISP_MSG_BGN + 158) 
    //MCU应答改变当前轮询终端, 消息体: CConfId
    #define MCS_DISP_SPECPOLLPOS_ACK                    (MCS_DISP_MSG_BGN + 159) 
    //MCU拒绝改变当前轮询终端, 消息体: CConfId
    #define MCS_DISP_SPECPOLLPOS_NACK                   (MCS_DISP_MSG_BGN + 160) 

//1.5.2 查询电视墙轮询参数
    //MCU应答会议控制台查询电视墙轮询参数, 消息体: CConfId + TTvWallPollInfo + TMtPollParam数组
    #define MCS_DISP_GETTWPOLLPARAM_ACK                   (MCS_DISP_MSG_BGN + 161) 
    //MCU拒绝会议控制台查询电视墙轮询参数, 消息体: CConfId
    #define MCS_DISP_GETTWPOLLPARAM_NACK                  (MCS_DISP_MSG_BGN + 162)
    //MCU通知会议控制台当前的电视墙轮询状态, 消息体: CConfId + TTvWallPollInfo
    #define MCS_DISP_TWPOLLSTATE_NOTIF                    (MCS_DISP_MSG_BGN + 163)

//1.5.3 改变语音激励切换时间
    //MCU同意会议控制台改变语音激励切换时间的请求, 消息体: CConfId + 1byte(单位:秒)
    #define MCS_DISP_CHANGEVACHOLDTIME_ACK              (MCS_DISP_MSG_BGN + 164)
    //MCU拒绝会议控制台改变语音激励切换时间的请求, 消息体: CConfId + 1byte(单位:秒)
    #define MCS_DISP_CHANGEVACHOLDTIME_NACK             (MCS_DISP_MSG_BGN + 165)
    //MCU给会议控制台改变语音激励切换时间的通知, 消息体: CConfId + 1byte(单位:秒)
    #define MCS_DISP_CHANGEVACHOLDTIME_NOTIF            (MCS_DISP_MSG_BGN + 166)

//1.5.4	会议状态通知
    //MCU给会议控制台的会议状态通知, 消息体: CConfId + TConfStatus
    #define MCS_DISP_CONFSTATUS_NOTIF                   (MCS_DISP_MSG_BGN + 167)
    //MCU给会议控制台的会议模式通知, 消息体: CConfId + TConfMode
    #define MCS_DISP_CONFMODE_NOTIF                     (MCS_DISP_MSG_BGN + 168)

//1.5.5	点名操作
    //MCU同意开始点名请求 消息体：  点名模式 u8 (ROLLCALL_MODE_NONE 等)
    #define MCU_DISP_STARTROLLCALL_ACK                  (MCS_DISP_MSG_BGN + 170)
    //MCU拒绝开始点名请求 消息体：  
    #define MCU_DISP_STARTROLLCALL_NACK                 (MCS_DISP_MSG_BGN + 171)
    //MCU给会议控制台的开始点名通知, 消息体：  点名模式 u8
    #define MCU_DISP_STARTROLLCALL_NOTIF                (MCS_DISP_MSG_BGN + 172)

    //MCU同意停止点名请求 消息体：  
    #define MCU_DISP_STOPROLLCALL_ACK                   (MCS_DISP_MSG_BGN + 173)
    //MCU拒绝停止点名请求 消息体：  
    #define MCU_DISP_STOPROLLCALL_NACK                  (MCS_DISP_MSG_BGN + 174)
    //MCU给会议控制台的停止点名通知, 消息体：  
    #define MCU_DISP_STOPROLLCALL_NOTIF                 (MCS_DISP_MSG_BGN + 175)

    //MCU同意点名变更请求 消息体：  TMt＋TMt
    #define MCU_DISP_CHANGEROLLCALL_ACK                 (MCS_DISP_MSG_BGN + 176)
    //MCU拒绝点名变更请求 消息体：  
    #define MCU_DISP_CHANGEROLLCALL_NACK                (MCS_DISP_MSG_BGN + 177)
    //MCU给会议控制台的点名变更通知, 消息体：  TMt＋TMt
    #define MCU_DISP_CHANGEROLLCALL_NOTIF               (MCS_DISP_MSG_BGN + 178)

//1.6	终端操作
//1.6.1	呼叫终端
    //MCU同意呼叫终端应答, 消息体: CConfId + TMt(入会终端)
    #define MCS_DISP_CALLMT_ACK                         (MCS_DISP_MSG_BGN + 180)
    //MCU拒绝呼叫终端, 消息体: CConfId
    #define MCS_DISP_CALLMT_NACK                        (MCS_DISP_MSG_BGN + 181)
    //终端在线状态变化通知, 消息体: CConfId + TMt + u8(状态:0-离线 1-上线) + u8(离线原因: 0-异常 1-正常挂断 2-线路断)
    #define MCS_DISP_MTONLINECHANGE_NOTIF               (MCS_DISP_MSG_BGN + 182)
    //终端呼叫不成功通知, 消息体: CConfId + TMt 原因见错误码
    #define MCS_DISP_CALLMTFAILURE_NOTIF                (MCS_DISP_MSG_BGN + 183)

//1.6.2	设置呼叫终端方式
    //成功设置MCU呼叫终端方式  消息体: CConfId + TMt(被呼叫终端) + u8(呼叫方式)
    #define MCS_DISP_SETMTCALLMODE_ACK                  (MCS_DISP_MSG_BGN + 185)
    //拒绝设置MCU呼叫终端方式, 消息体: CConfId
    #define MCS_DISP_SETMTCALLMODE_NACK                 (MCS_DISP_MSG_BGN + 186)
    //MCU呼叫终端方式通知  消息体: CConfId + TMtExt
    #define MCS_DISP_MTCALLMODE_NOTIF                   (MCS_DISP_MSG_BGN + 187)

//1.6.3	挂断终端
    //终端被成功挂断, 消息体: CConfId
    #define MCS_DISP_DROPMT_ACK                         (MCS_DISP_MSG_BGN + 190)
    //MCU拒绝挂断该终端, 消息体: CConfId
    #define MCS_DISP_DROPMT_NACK	                    (MCS_DISP_MSG_BGN + 191)

    //主席选看vmp
    #define MCS_DISP_STARTVMPSEE_ACK                     (MCS_DISP_MSG_BGN + 192)
    #define MCS_DISP_STARTVMPSEE_NACK                    (MCS_DISP_MSG_BGN + 193)

//1.6.4	强制终端选看
    //MCU应答会控强制目的终端选看源终端, MCS_MCU_STARTSWITCHMT_ACK, 
    //消息体: CConfId + TSwitchInfo
    #define MCS_DISP_STARTMTSEE_ACK                     (MCS_DISP_MSG_BGN + 195)
    //拒绝会控强制目的终端选看源终端, MCS_MCU_STARTSWITCHMT_NACK, 
    //消息体: CConfId
    #define MCS_DISP_STARTMTSEE_NACK                    (MCS_DISP_MSG_BGN + 196)

//1.6.5	取消终端选看
    //MCU应答会控取消目的终端选看源终端, MCU_MCS_STOPSWITCHMT_ACK,
    //消息体: CConfId + TMt
    #define MCS_DISP_STOPMTSEE_ACK                      (MCS_DISP_MSG_BGN + 197)
    //MCU拒绝会控取消目的终端选看源终端, MCU_MCS_STOPSWITCHMT_NACK,
    //消息体: CConfId
    #define MCS_DISP_STOPMTSEE_NACK                     (MCS_DISP_MSG_BGN + 198)

//1.6.6	查询终端状态
    //MCU给会议控制台的查询终端状态通知, 消息体: CConfId + TMtStatus数组
    #define MCS_DISP_MTSTATUS_NOTIF                     (MCS_DISP_MSG_BGN + 200)

//高清电视墙音量调节
    #define MCS_DISP_SETCHANNELVOLUME_ACK               (MCS_DISP_MSG_BGN + 201)
    #define MCS_DISP_SETCHANNELVOLUME_NACK              (MCS_DISP_MSG_BGN + 202)


//1.6.7 查询终端别名
    //MCU应答会议控制台查询终端别名, 消息体: CConfId + TMt + TMtAlias数组
    #define MCS_DISP_GETMTALIAS_ACK                     (MCS_DISP_MSG_BGN + 205)
    //MCU没有终端的别名信息, 消息体: CConfId + TMt(要查询的终端)
    #define MCS_DISP_GETMTALIAS_NACK                    (MCS_DISP_MSG_BGN + 206)
    //MCU给会议控制台的终端别名通知, 消息体: CConfId + TMt + TMtAlias数组
    #define MCS_DISP_MTALIAS_NOTIF                      (MCS_DISP_MSG_BGN + 207)

    //MCU应答会议控制台查询所有终端别名, 消息体: CConfId + TMCU + 别名打包缓存(多个 TMt+1byte(别名类型)+2byte(别名长度)+别名缓存 )
    #define MCS_DISP_GETALLMTALIAS_ACK                  (MCS_DISP_MSG_BGN + 208)
    //MCU拒绝会议控制台的查询所有终端别名, 消息体: CConfId + TMCU
    #define MCS_DISP_GETALLMTALIAS_NACK                 (MCS_DISP_MSG_BGN + 209)
    //MCU给会议控制台的查询所有终端别名通知, 消息体: CConfId + TMCU + 别名打包缓存(多个 TMt+1byte(别名类型)+2byte(别名长度)+别名缓存 )
    #define MCS_DISP_ALLMTALIAS_NOTIF                   (MCS_DISP_MSG_BGN + 210)

//1.6.8 获取终端码率
    //MCU应答会议控制台查询终端码率, 消息体: CConfId 
    #define MCS_DISP_GETMTBITRATE_ACK                   (MCS_DISP_MSG_BGN + 211)
    //MCU拒绝会议控制台查询终端码率, 消息体: CConfId
    #define MCS_DISP_GETMTBITRATE_NACK                  (MCS_DISP_MSG_BGN + 212)
    //MCU拒绝会议控制台查询终端码率, 消息体: CConfId + TMtBitrate数组
    #define MCS_DISP_GETMTBITRATE_NOTIF                 (MCS_DISP_MSG_BGN + 213)

//1.6.9	设置终端静音
    //MCU应答会议控制台设置终端静音, 消息体: CConfId + TMt + u8(1- MUTE 0-NOMUTE) + u8(1-DECODER 2-CAPTURE) 
    #define MCS_DISP_MTAUDMUTE_ACK                      (MCS_DISP_MSG_BGN + 215)
    //MCU拒绝会议控制台设置终端静音, 消息体: CConfId + TMt
    #define MCS_DISP_MTAUDMUTE_NACK                     (MCS_DISP_MSG_BGN + 216)
    //MCU通知会议控制台设置终端静音, 消息体: CConfId + TMt + u8(1- MUTE 0-NOMUTE) + u8(1-DECODER 2-CAPTURE)
    #define MCS_DISP_MTAUDMUTE_NOTIF                    (MCS_DISP_MSG_BGN + 217)

//1.6.10有关视频矩阵操作

//1.6.10.1	内置矩阵
    //所有矩阵信息: CConfId + TMt(操作终端) + u8( 方案数 ) + ITInnerMatrixScheme[]
    #define MCS_DISP_MATRIX_ALLSCHE_NOTIF               (MCS_DISP_MSG_BGN + 220)

    //单个矩阵信息 消息体: CConfId + TMt(操作终端) + ITInnerMatrixScheme
    #define MCS_DISP_MATRIX_ONESCHE_NOTIF               (MCS_DISP_MSG_BGN + 221) 

    //当前方案信息, 消息体: CConfId + TMt(操作终端) + u8(0, 1-6)
    #define MCS_DISP_MATRIX_CURSCHE_NOTIF               (MCS_DISP_MSG_BGN + 222)

//1.6.10.2 外置矩阵，已经废弃
    //终端外置矩阵信息通知, 消息体: CConfId + TMt(操作终端) + u8(矩阵输入端口数 0表示没有矩阵) 
    #define MCS_DISP_MATRIXEXINFO_NOTIF                 (MCS_DISP_MSG_BGN + 225)

    //终端外置矩阵连接端口获取成功, 消息体: CConfId + TMt(操作终端)
    #define MCS_DISP_MATRIXEXGETPORT_ACK                (MCS_DISP_MSG_BGN + 226)

    //终端外置矩阵连接端口获取失败, 消息体: CConfId + TMt(操作终端)
    #define MCS_DISP_MATRIXEXGETPORT_NACK               (MCS_DISP_MSG_BGN + 227)

    //终端外置矩阵连接端口通知, 消息体: CConfId + TMt(操作终端) + u8(1-64)
    #define MCS_DISP_MATRIXEXGETPORT_NOTIF              (MCS_DISP_MSG_BGN + 228)

    //终端外置矩阵端口名通知, 消息体: CConfId + TMt(操作终端) + u8(1-64 )+s8[MAXLEN_MATRIXPORTNAME] 0结尾的字符串
    #define MCS_DISP_MATRIXEXPORTNAME_NOTIF             (MCS_DISP_MSG_BGN + 229)

    //终端外置矩阵所有端口名通知, 消息体: CConfId + TMt(操作终端) + s8[][MAXLEN_MATRIXPORTNAME] 索引0 表示输出端口名 其余为输入端口，（字符串数组）
    #define MCS_DISP_MATRIXEXGETALLPORTNAME_NOTIF       (MCS_DISP_MSG_BGN + 230)

//1.6.10.3 扩展视频源
    //终端扩展视频源所有端口名通知, 消息体: CConfId + TMt(操作终端) + tagITVideoSourceInfo[]
    #define MCS_DISP_VIDEOEXALLINFO_NOTIF               (MCS_DISP_MSG_BGN + 231)

    //终端扩展视频源信息通知, 消息体: CConfId + TMt(操作终端) + tagITVideoSourceInfo
    #define MCS_DISP_VIDEOEXINFO_NOTIF                  (MCS_DISP_MSG_BGN + 232)

//1.6.11 级联MCU控制
    //锁定下级MCU请求成功应答 消息体: CConfId + TMcu + BOOL
    #define MCS_DISP_LOCKSMCU_ACK                       (MCS_DISP_MSG_BGN + 235)
    //锁定下级MCU请求失败应答 消息体: CConfId + TMcu
    #define MCS_DISP_LOCKSMCU_NACK                      (MCS_DISP_MSG_BGN + 236)

//1.6.12 获取终端版本信息
    //获取终端版本信息成功应答 消息体: CConfId
    #define MCS_DISP_GETMTVERSION_ACK                   (MCS_DISP_MSG_BGN + 237)
    //获取终端版本信息失败应答 消息体: CConfId
    #define MCS_DISP_GETMTVERSION_NACK                  (MCS_DISP_MSG_BGN + 238)

//1.7	外设操作
//1.7.1	录放像机操作
//1.7.1.1	录像操作
//1.7.1.1.1	请求录像
    //会控向MCU请求录像
    //MCU同意会控放像请求, 消息体: CConfId + TMt + TEqp
    #define MCS_DISP_STARTREC_ACK                       (MCS_DISP_MSG_BGN + 240)
    //MCU拒绝会控放像请求, 消息体: CConfId + TMt + TEqp
    #define MCS_DISP_STARTREC_NACK                      (MCS_DISP_MSG_BGN + 241)
    //MCU通知会控录像进度, 消息体: CConfId + TMt + TEqp + TRecProg
    #define MCS_DISP_RECPROG_NOTIF                      (MCS_DISP_MSG_BGN + 242)

//1.7.1.1.2	暂停录像请求
    //MCU同意会控暂停放像请求, 消息体: CConfId + TMt
    #define MCS_DISP_PAUSEREC_ACK                       (MCS_DISP_MSG_BGN + 243)
    //MCU拒绝会控暂停放像请求, 消息体: CConfId + TMt
    #define MCS_DISP_PAUSEREC_NACK                      (MCS_DISP_MSG_BGN + 244)

//1.7.1.1.3	恢复录像
    //MCU同意会控恢复放像请求,消息体: CConfId + TMt
    #define MCS_DISP_RESUMEREC_ACK                      (MCS_DISP_MSG_BGN + 245)
    //MCU拒绝会控恢复放像请求,消息体: CConfId + TMt
    #define MCS_DISP_RESUMEREC_NACK                     (MCS_DISP_MSG_BGN + 246)

//1.7.1.1.4	停止录像
    //MCU同意会控停止放像请求, 消息体: CConfId + TMt
    #define MCS_DISP_STOPREC_ACK                        (MCS_DISP_MSG_BGN + 247)
    //MCU拒绝会控停止放像请求, 消息体: CConfId + TMt
    #define MCS_DISP_STOPREC_NACK                       (MCS_DISP_MSG_BGN + 248)

//1.7.1.2	放像操作
//1.7.1.2.1	开始播放
    //MCU开始放像应答, 消息体: CConfId + TEqp
    #define MCS_DISP_STARTPLAY_ACK                      (MCS_DISP_MSG_BGN + 250)
    //MCU拒绝开始放像, 消息体: CConfId + TEqp
    #define MCS_DISP_STARTPLAY_NACK                     (MCS_DISP_MSG_BGN + 251)
    //放像进度通知, 消息体: CConfId + TEqp + TRecProg
    #define MCS_DISP_PLAYPROG_NOTIF                     (MCS_DISP_MSG_BGN + 252)

//1.6.1.2.2	暂停播放
    //MCU暂停放像应答, 消息体: CConfId + TEqp
    #define MCS_DISP_PAUSEPLAY_ACK                      (MCS_DISP_MSG_BGN + 253)
    //MCU拒绝暂停放像, 消息体: CConfId + TEqp
    #define MCS_DISP_PAUSEPLAY_NACK                     (MCS_DISP_MSG_BGN + 254)

//1.7.1.2.3	恢复放像
    //MCU恢复放像应答, 消息体: CConfId + TEqp
    #define MCS_DISP_RESUMEPLAY_ACK                     (MCS_DISP_MSG_BGN + 255)
    //MCU拒绝恢复放像, 消息体: CConfId + TEqp
    #define MCS_DISP_RESUMEPLAY_NACK                    (MCS_DISP_MSG_BGN + 256)

//1.7.1.2.4	停止放像
    //MCU停止放像应答, 消息体: CConfId + TEqp
    #define MCS_DISP_STOPPLAY_ACK                       (MCS_DISP_MSG_BGN + 257)
    //MCU停止恢复放像, 消息体: CConfId + TEqp
    #define MCS_DISP_STOPPLAY_NACK                      (MCS_DISP_MSG_BGN + 258)

//1.7.1.2.5	放像进度调整
    //MCU同意调整放像进度应答, 消息体: CConfId + TEqp
    #define MCS_DISP_SEEKPLAY_ACK                       (MCS_DISP_MSG_BGN + 259)
    //MCU拒绝调整放像进度应答, 消息体: CConfId + TEqp
    #define MCS_DISP_SEEKPLAY_NACK                      (MCS_DISP_MSG_BGN + 260)

//1.7.1.3   录放像异常
    //会议录放像异常通知, 消息体: CConfId + TEqp
    #define MCS_DISP_RECORDERABNORMAL_NOTIF             (MCS_DISP_MSG_BGN + 261)

//1.7.1.4	录像文件列表操作
//1.7.1.4.1	获取文件列表请求
    //获取录像文件列表应答, 消息体: TEqp
    #define MCS_DISP_GETRECFILELIST_ACK                 (MCS_DISP_MSG_BGN + 265)
    //获取录像文件列表拒绝, 消息体: TEqp
    #define MCS_DISP_GETRECFILELIST_NACK                (MCS_DISP_MSG_BGN + 266)
    //录像文件列表通知消息, 消息体: TEqp
    #define MCS_DISP_RECFILELIST_NOTIF                  (MCS_DISP_MSG_BGN + 267)
	//录像文件文件个数超过1000通知消息
    #define  MCS_DISP_REACH_MAX_REC_FILE_NOTIF			(MCS_DISP_MSG_BGN + 264)

//1.7.1.4.2 修改录像文件名
    //修改录像文件名成功, 消息体: TEqp
    #define MCS_DISP_MODIFYRECFILE_ACK                  (MCS_DISP_MSG_BGN + 268)
    //修改录像文件名失败, 消息体: TEqp
    #define MCS_DISP_MODIFYRECFILE_NACK                 (MCS_DISP_MSG_BGN + 269)

//1.7.1.4.3	删除记录文件请求
    //会控请求删除文件应答, 消息体: TEqp + 记录名
    #define MCS_DISP_DELRECFILE_ACK                     (MCS_DISP_MSG_BGN + 270)
    //会控请求MCU_MCS_删除文件拒绝, 消息体: TEqp
    #define MCS_DISP_DELRECFILE_NACK                    (MCS_DISP_MSG_BGN + 271)

//1.7.1.5 文件发布操作
//1.7.1.5.1 会控请求MCU发布文件
    //同意，消息体: TEqp + u8(PUBLISH_LEVEL) + 录像名
    #define MCS_DISP_PUBLISHRECFILE_ACK                 (MCS_DISP_MSG_BGN + 272)
    //反对，消息体: TEqp + u8(PUBLISH_LEVEL) + 录像名
    #define MCS_DISP_PUBLISHRECFILE_NACK                (MCS_DISP_MSG_BGN + 273)

//1.7.1.5.2 会控请求MCU取消发布文件
    //同意，消息体: TEqp + 录像名
    #define MCS_DISP_CANCELRECFILEPUBLISH_ACK           (MCS_DISP_MSG_BGN + 274)
    //反对，消息体: TEqp + 录像名
    #define MCS_DISP_CANCELRECFILEPUBLISH_NACK          (MCS_DISP_MSG_BGN + 275)

//1.7.2	混音
//1.7.3.1	开始本级混音(智能/定制)
	//MCU同意开始本级混音, 消息体: CConfId + TMcu + u8(同时参加讨论(混音)的成员个数) + TMt数组(指定成员混音时才有)
	#define MCS_DISP_STARTMIX_ACK                       (MCS_DISP_MSG_BGN + 280)
	//MCU拒绝开始本级混音, 消息体: CConfId + TMcu + u8(同时参加讨论(混音)的成员个数) + TMt数组(指定成员混音时才有)
	#define MCS_DISP_STARTMIX_NACK                      (MCS_DISP_MSG_BGN + 281)
	//MCU开始本级混音通知, 消息体: CConfId + TMcu + u8(同时参加讨论(混音)的成员个数)
	#define MCS_DISP_STARTMIX_NOTIF                     (MCS_DISP_MSG_BGN + 282)
    //MCU给会议控制台的混音参数通知, 消息体: CConfId + n * (TMcu + TDiscussParam )
    #define MCS_DISP_MIXPARAM_NOTIF                     (MCS_DISP_MSG_BGN + 283)

//1.7.3.2	结束本级混音(智能/定制)
    //MCU同意会议控制台结束本级混音的请求, 消息体: CConfId + TMcu
    #define MCS_DISP_STOPMIX_ACK                        (MCS_DISP_MSG_BGN + 284)
    //MCU拒绝会议控制台结束本级混音的请求, 消息体: CConfId + TMcu
    #define MCS_DISP_STOPMIX_NACK                       (MCS_DISP_MSG_BGN + 285)
    //MCU给会议控制台结束本级混音的通知, 消息体: CConfId + TMcu
    #define MCS_DISP_STOPMIX_NOTIF                      (MCS_DISP_MSG_BGN + 286)

//1.7.3.3  混音成员控制
    //终端申请加入混音通知, 消息体: CConfId + TMt(申请终端)
    #define MCS_DISP_MTAPPLYMIX_NOTIF                   (MCS_DISP_MSG_BGN + 287)

//1.7.3.4  混音延时
    //MCU同意会议控制台混音延时请求, 消息体: CConfId
    #define MCS_DISP_MODIFYMIXDELAY_ACK                 (MCS_DISP_MSG_BGN + 288)
    //MCU拒绝会议控制台混音延时请求, 消息体: CConfId
    #define MCS_DISP_MODIFYMIXDELAY_NACK                (MCS_DISP_MSG_BGN + 289)
    //混音延时通知, 消息体: CConfId + u16(延时毫秒数)
    #define MCS_DISP_MIXDELAY_NOTIF                     (MCS_DISP_MSG_BGN + 290)

//1.7.3.5	启用语音激励控制发言
    //MCU同意会议控制台开始语音激励控制发言的请求, 消息体: CConfId
    #define MCS_DISP_STARTVAC_ACK                       (MCS_DISP_MSG_BGN + 295)
    //MCU拒绝会议控制台开始语音激励控制发言的请求, 消息体: CConfId
    #define MCS_DISP_STARTVAC_NACK                      (MCS_DISP_MSG_BGN + 296)
    //MCU给会议控制台开始语音激励控制发言的通知, 
    //上层可以通过处理MCS_DISP_CONFSTATUS_NOTIF忽略此消息,
    //消息体: CConfId
    #define MCS_DISP_STARTVAC_NOTIF                     (MCS_DISP_MSG_BGN + 297)

//1.7.3.6	取消语音激励控制发言
    //MCU同意会议控制台停止语音激励控制发言的请求, 消息体: CConfId
    #define MCS_DISP_STOPVAC_ACK                        (MCS_DISP_MSG_BGN + 300)
    //MCU拒绝会议控制台停止语音激励控制发言的请求, 消息体: CConfId
    #define MCS_DISP_STOPVAC_NACK                       (MCS_DISP_MSG_BGN + 301)
    //MCU给会议控制台停止语音激励控制发言的通知, 
    //上层可以通过处理MCS_DISP_CONFSTATUS_NOTIF忽略此消息,
    //消息体: CConfId
    #define MCS_DISP_STOPVAC_NOTIF                      (MCS_DISP_MSG_BGN + 302)

//1.7.4	画面合成控制
//1.7.4.1	开始画面合成
    //MCU同意画面合成请求, 消息体: CConfId
    #define MCS_DISP_STARTVMP_ACK                       (MCS_DISP_MSG_BGN + 310)
    //MCU不同意画面合成请求, 消息体: CConfId
    #define MCS_DISP_STARTVMP_NACK                      (MCS_DISP_MSG_BGN + 311)
    //画面合成成功开始通知, 
    //上层可以通过处理MCS_DISP_CONFSTATUS_NOTIF忽略此消息,
    //消息体: CConfId + TVMPParam
    #define MCS_DISP_STARTVMP_NOTIF                     (MCS_DISP_MSG_BGN + 312)
    //MCU给会议控制台的画面合成参数通知,
    //上层可以通过处理MCS_DISP_CONFSTATUS_NOTIF忽略此消息,
    //消息体: CConfId + TVMPParam
    #define MCS_DISP_VMPPARAM_NOTIF                     (MCS_DISP_MSG_BGN + 313)

//1.7.4.2 停止画面合成	
    //MCU同意视频结束复合请求, 消息体: CConfId
    #define MCS_DISP_STOPVMP_ACK                        (MCS_DISP_MSG_BGN + 314)
    //MCU不同意结束画面合成请求, 消息体: CConfId
    #define MCS_DISP_STOPVMP_NACK                       (MCS_DISP_MSG_BGN + 315)
    //画面合成成功结束通知, 
    //上层可以通过处理MCS_DISP_CONFSTATUS_NOTIF忽略此消息,
    //消息体: CConfId
    #define MCS_DISP_STOPVMP_NOTIF                      (MCS_DISP_MSG_BGN + 316)

//1.7.4.3	改变画面合成参数
    //MCU同意会议控制台的改变画面合成参数请求, 消息体: CConfId + TVMPParam
    #define MCS_DISP_CHANGEVMPPARAM_ACK                 (MCS_DISP_MSG_BGN + 317)
    //MCU拒绝会议控制台的改变画面合成参数请求, 消息体: CConfId
    #define MCS_DISP_CHANGEVMPPARAM_NACK                (MCS_DISP_MSG_BGN + 318)
    //MCU同意会议控制台的改变画面合成参数请求, 消息体: CConfId + TVMPParam
    #define MCS_DISP_CHANGEVMPPARAM_NOTIF               (MCS_DISP_MSG_BGN + 319)

//1.7.4.4	画面合成广播控制
    //MCU同意广播画面合成码流, 消息体: CConfId
    #define MCS_DISP_STARTVMPBRDST_ACK                  (MCS_DISP_MSG_BGN + 321)
    //MCU拒绝广播画面合成码流, 消息体: CConfId
    #define MCS_DISP_STARTVMPBRDST_NACK                 (MCS_DISP_MSG_BGN + 322)

    //MCU同意停止广播画面合成码流, 消息体: CConfId
    #define MCS_DISP_STOPVMPBRDST_ACK                   (MCS_DISP_MSG_BGN + 323)
    //MCU拒绝停止广播画面合成码流, 消息体: CConfId
    #define MCS_DISP_STOPVMPBRDST_NACK                  (MCS_DISP_MSG_BGN + 324)

    //高清电视墙
    #define MCS_DISP_STARTHDTVWALL_ACK                  (MCS_DISP_MSG_BGN + 325)
    #define MCS_DISP_STARTHDTVWALL_NACK                 (MCS_DISP_MSG_BGN + 326)
    #define MCS_DISP_STOPHDTVWALL_ACK                   (MCS_DISP_MSG_BGN + 327)
    //MCU拒绝停止交换图像, 消息体: CConfId + TTWSwitchInfo
    #define MCS_DISP_STOPHDTVWALL_NACK                  (MCS_DISP_MSG_BGN + 328)

//1.7.5	电视墙操作
//1.7.5.1	电视墙操作
    //MCU同意开始交换图像, 消息体: CConfId + TTWSwitchInfo
    #define MCS_DISP_STARTTVWALL_ACK                    (MCS_DISP_MSG_BGN + 330)
    //MCU拒绝开始交换图像, 消息体: CConfId + TTWSwitchInfo
    #define MCS_DISP_STARTTVWALL_NACK                   (MCS_DISP_MSG_BGN + 331)

    //MCU同意停止交换图像, 消息体: CConfId + TTWSwitchInfo
    #define MCS_DISP_STOPTVWALL_ACK                     (MCS_DISP_MSG_BGN + 332)
    //MCU拒绝停止交换图像, 消息体: CConfId + TTWSwitchInfo
    #define MCS_DISP_STOPTVWALL_NACK                    (MCS_DISP_MSG_BGN + 333)

//1.7.5.1	多画面电视墙操作
    //MCU同意复合电视墙请求, 消息体: CConfId
    #define MCS_DISP_STARTMULTITVWALL_ACK               (MCS_DISP_MSG_BGN + 334)
    //MCU拒绝复合电视墙请求, 消息体: CConfId
    #define MCS_DISP_STARTMULTITVWALL_NACK              (MCS_DISP_MSG_BGN + 335)
    //复合电视墙成功开始通知, 消息体: CConfId + TVMPParam
    #define MCS_DISP_STARTMULTITVWALL_NOTIF             (MCS_DISP_MSG_BGN + 336)

    //MCU同意结束复合电视墙请求, 消息体: CConfId
    #define MCS_DISP_STOPMULTITVWALL_ACK                (MCS_DISP_MSG_BGN + 337)
    //MCU拒绝结束复合电视墙请求, 消息体: CConfId
    #define MCS_DISP_STOPMULTITVWALL_NACK               (MCS_DISP_MSG_BGN + 338)
    //复合电视墙成功结束通知, 消息体: CConfId
    #define MCS_DISP_STOPMULTITVWALL_NOTIF              (MCS_DISP_MSG_BGN + 339)

    //MCU同意会议控制台的改变复合电视墙参数请求, 消息体: CConfId + TVMPParam
    #define MCS_DISP_CHANGEMULTITVWALLPARAM_ACK         (MCS_DISP_MSG_BGN + 340)
    //MCU拒绝会议控制台的改变复合电视墙参数请求, 消息体: CConfId
    #define MCS_DISP_CHANGEMULTITVWALLPARAM_NACK        (MCS_DISP_MSG_BGN + 341)
    //视频复合参数通知, 消息体: CConfId + TVMPParam
    //上层可以通过处理MCS_DISP_CONFSTATUS_NOTIF忽略掉此消息
    #define MCS_DISP_MULTITVWALLPARAM_NOTIF             (MCS_DISP_MSG_BGN + 342)

    //mpu--vmp相关操作
    //消息体: u8 byMtId+TChnnlMemberInfo[]
    #define MCS_DISP_VMPPPRISEIZE_REQ                   (MCS_DISP_MSG_BGN + 343)
    #define MCS_DISP_VMPOVERHDCHNNLLMT_NOTIF            (MCS_DISP_MSG_BGN + 344)


//1.7.6	外设状态
    //MCU应答会议控制台的查询外设状态请求, 消息体: TPeriEqpStatus  
    #define MCS_DISP_GETMCUPERIEQPSTATUS_ACK            (MCS_DISP_MSG_BGN + 360)
    //MCU拒会议控制台的查询外设状态请求, 消息体: 无
    #define MCS_DISP_GETMCUPERIEQPSTATUS_NACK           (MCS_DISP_MSG_BGN + 361)	
    //通知会控外设状态改变,消息体: TPeriEqpStatus
    #define MCS_DISP_MCUPERIEQPSTATUS_NOTIF             (MCS_DISP_MSG_BGN + 362)

	//MCU应答会议控制台的查询DCS外设状态请求, 消息体: TPeriDCSStatus
	#define MCS_DISP_GETMCUDCSSTATUS_ACK				(MCS_DISP_MSG_BGN + 363)
	//MCU拒会议控制台的查询外设状态请求, 消息体: TEqp
	#define MCS_DISP_GETMCUDCSSTATUS_NACK				(MCS_DISP_MSG_BGN + 364)
    //通知会控外设状态改变,消息体: TPeriDCSStatus
	#define MCS_DISP_GETMCUDCSSTATUS_NOTIF				(MCS_DISP_MSG_BGN + 365)
    //通知MCS码流转发能力超限,消息体: u8 byMpId + s8* achIp
	#define MCS_DISP_MPFLUXOVERRUN_NOTIF				(MCS_DISP_MSG_BGN + 366)
    //通知MCS码流转发能力超限,消息体: u8(DSC类型),u32(DSC ip (网络序)),u32(DSC连接的本地MCU的IP)
	#define MCS_DISP_NEWDSCREGREQ_NOTIF				    (MCS_DISP_MSG_BGN + 367)

//1.8	MCU用户管理
//1.8.1	添加用户
    //MCU接受会议控制台的添加用户请求, 消息体: 用户名[MAX_CHARLENGTH]
    #define MCS_DISP_ADDUSER_ACK                        (MCS_DISP_MSG_BGN + 380)
    //MCU拒绝会议控制台的添加用户请求, 消息体: 用户名[MAX_CHARLENGTH]
    #define MCS_DISP_ADDUSER_NACK                       (MCS_DISP_MSG_BGN + 381)
    //MCU通知会议控制台添加用户, 消息体: CUserFullInfo
    #define MCS_DISP_ADDUSER_NOTIF                      (MCS_DISP_MSG_BGN + 382)

//1.8.2	删除用户
    //MCU接受会议控制台的删除用户请求, 消息体: 用户名[MAX_CHARLENGTH]
    #define MCS_DISP_DELUSER_ACK                        (MCS_DISP_MSG_BGN + 383)
    //MCU拒绝会议控制台的删除用户请求, 消息体: 用户名[MAX_CHARLENGTH]
    #define MCS_DISP_DELUSER_NACK                       (MCS_DISP_MSG_BGN + 384)
    //MCU通知会议控制台删除用户, 消息体: 用户名[MAX_CHARLENGTH]
    #define MCS_DISP_DELUSER_NOTIF                      (MCS_DISP_MSG_BGN + 385)

//1.8.3	用户列表
    //用户列表通知，消息体: CLongMessage + CUserFullInfo数组
    #define MCS_DISP_USERLIST_NOTIF                     (MCS_DISP_MSG_BGN + 386)

//1.8.4	修改用户
    //MCU接受会议控制台的修改用户请求, 消息体: 用户名[MAX_CHARLENGTH]
    #define MCS_DISP_MODIFYUSER_ACK                     (MCS_DISP_MSG_BGN + 387)
    //MCU拒绝会议控制台的修改用户请求, 消息体: 用户名[MAX_CHARLENGTH]
    #define MCS_DISP_MODIFYUSER_NACK                    (MCS_DISP_MSG_BGN + 388)
    //MCU通知会议控制台修改用户, 消息体: CUserFullInfo
    #define MCS_DISP_MODIFYUSER_NOTIF                   (MCS_DISP_MSG_BGN + 389)
//1.8.5 增加用户组
	//MCU接受会议控制台的增加用户请求, 消息体: NULL
	#define MCS_DISP_ADDUSERGROUP_ACK					(MCS_DISP_MSG_BGN + 390)
	//MCU拒绝会议控制台的增加用户请求, 消息体: NULL
	#define MCS_DISP_ADDUSERGROUP_NACK					(MCS_DISP_MSG_BGN + 391)
	//MCU通知会议控制台增加用户, 消息体: NULL
	#define MCS_DISP_ADDUSERGROUP_NOTIF					(MCS_DISP_MSG_BGN + 392)

//1.8.6  删除用户组
	//MCU接受会议控制台的删除用户请求, 消息体: NULL
	#define MCS_DISP_DELUSERGROUP_ACK					(MCS_DISP_MSG_BGN + 393)
	//MCU拒绝会议控制台的删除用户请求, 消息体: NULL
	#define MCS_DISP_DELUSERGROUP_NACK					(MCS_DISP_MSG_BGN + 394)
	//MCU通知会议控制台删除用户, 消息体: NULL
	#define MCS_DISP_DELUSERGROUP_NOTIF					(MCS_DISP_MSG_BGN + 395)

//1.8.7  修改用户组
	//MCU接受会议控制台的修改用户请求  消息体: NULL
	#define MCS_DISP_MODIFYUSERGROUP_ACK				(MCS_DISP_MSG_BGN + 396)
	//MCU拒绝会议控制台的修改用户请求  消息体: NULL
	#define MCS_DISP_MODIFYUSERGROUP_NACK				(MCS_DISP_MSG_BGN + 397)
	//MCU通知会议控制台修改用户  消息体: NULL
	#define MCS_DISP_MODIFYUSERGROUP_NOTIF				( MCS_DISP_MSG_BGN + 398 )

	//MCU通知会议控制台用户组列表信息 消息体 : NULL
	#define MCS_DISP_USERGROUPLIST_NOTIF				(MCS_DISP_MSG_BGN + 399)

//2   地址簿

//2.1   增加地址簿条目
    //增加地址簿条目成功确认, 消息体: 无
    #define MCS_DISP_ADDRBOOK_ADDENTRY_ACK              (MCS_DISP_MSG_BGN + 400)
    //增加地址簿条目拒绝, 消息体: 无
    #define MCS_DISP_ADDRBOOK_ADDENTRY_NACK             (MCS_DISP_MSG_BGN + 401)

//2.2   删除地址簿条目
    //删除地址簿条目成功确认, 消息体: 无
    #define MCS_DISP_ADDRBOOK_DELENTRY_ACK              (MCS_DISP_MSG_BGN + 402)
    //删除地址簿条目拒绝或失败, 消息体: 无
    #define MCS_DISP_ADDRBOOK_DELENTRY_NACK             (MCS_DISP_MSG_BGN + 403)
    //删除地址簿条目通知, 消息体: u32(条目索引号)
    #define MCS_DISP_ADDRBOOK_DELENTRY_NOTIF            (MCS_DISP_MSG_BGN + 404)

//2.3   修改地址簿条目
    //修改地址簿条目成功确认, 消息体: 无
    #define MCS_DISP_ADDRBOOK_MODIFYENTRY_ACK           (MCS_DISP_MSG_BGN + 405)
    //修改地址簿条目拒绝或失败, 消息体: 无
    #define MCS_DISP_ADDRBOOK_MODIFYENTRY_NACK          (MCS_DISP_MSG_BGN + 406)

//2.4   增加会议组条目
    //增加地址簿会议条目成功确认 , 消息体: 无
    #define MCS_DISP_ADDRBOOK_ADDGROUP_ACK              (MCS_DISP_MSG_BGN + 407)
    //增加地址簿会议组条目拒绝或失败, 消息体: 无
    #define MCS_DISP_ADDRBOOK_ADDGROUP_NACK             (MCS_DISP_MSG_BGN + 408)

//2.5   删除会议组条目
    //删除地址簿会议组条目成功确认, 消息体: 无
    #define MCS_DISP_ADDRBOOK_DELGROUP_ACK              (MCS_DISP_MSG_BGN + 409)
    //删除地址簿会议组条目拒绝或失败, 消息体: 无
    #define MCS_DISP_ADDRBOOK_DELGROUP_NACK             (MCS_DISP_MSG_BGN + 410)
    //删除地址簿会议组条目通知, 消息体: u32(会议组索引号)
    #define MCS_DISP_ADDRBOOK_DELGROUP_NOTIF            (MCS_DISP_MSG_BGN + 411)

//2.6   修改会议组条目
    //修改地址簿会议组条目成功确认, 消息体: 无
    #define MCS_DISP_ADDRBOOK_MODIFYGROUP_ACK           (MCS_DISP_MSG_BGN + 412)
    //修改地址簿会议组条目拒绝或失败, 消息体: 无
    #define MCS_DISP_ADDRBOOK_MODIFYGROUP_NACK          (MCS_DISP_MSG_BGN + 413)

//2.7   向会议组增加终端
    //向会议组中增加与会终端成功确认, 消息体: 无
    #define MCS_DISP_ADDRBOOK_ADDENTRYTOGROUP_ACK       (MCS_DISP_MSG_BGN + 414)
    //向会议组中增加与会终端拒绝或失败, 消息体: 无
    #define MCS_DISP_ADDRBOOK_ADDENTRYTOGROUP_NACK      (MCS_DISP_MSG_BGN + 415)

//2.8   从会议组中删除终端
    //删除会议组中的终端成功确认, 消息体: 无
    #define MCS_DISP_ADDRBOOK_DELENTRYFROMGROUP_ACK     (MCS_DISP_MSG_BGN + 416)
    //删除会议组中的终端成功拒绝或失败, 消息体: 无
    #define MCS_DISP_ADDRBOOK_DELENTRYFROMGROUP_NACK    (MCS_DISP_MSG_BGN + 417)

//2.9   地址簿消息通知
    //地址簿条目通知, 消息体: TMcuAddrEntry
    #define MCS_DISP_ADDRBOOK_REFRESHENTRY_NOTIF        (MCS_DISP_MSG_BGN + 419)
    //地址簿会议组通知, 消息体: TMcuAddrGroup
    #define MCS_DISP_ADDRBOOK_REFRESHGROUP_NOTIF        (MCS_DISP_MSG_BGN + 420)

//1.2.5 修改MCU高清电视墙配置
    //修改MCU高清电视墙配置成功应答, 消息体: 无
    #define MCS_DISP_CHANGEHDUSCHEMEINFO_ACK                (MCS_DISP_MSG_BGN + 421)
    //修改MCU高清电视墙配置失败应答, 消息体: 无
    #define MCS_DISP_CHANGEHDUSCHEMEINFO_NACK               (MCS_DISP_MSG_BGN + 422)
    //高清电视墙配置通知(消息体可能大于32K), 消息体: THduStyleCfgInfo数组
    #define MCS_DISP_MCU_HDUSCHEMEINFO_NOTIF                (MCS_DISP_MSG_BGN + 423)

//高清电视墙通道批量轮询
    //开始
    #define MCS_DISP_STARTHDUBATCHPOLL_ACK               (MCS_DISP_MSG_BGN + 424)
    #define MCS_DISP_STARTHDUBATCHPOLL_NACK              (MCS_DISP_MSG_BGN + 425)

    //停止
    #define MCS_DISP_STOPHDUBATCHPOLL_ACK               (MCS_DISP_MSG_BGN + 426)
    #define MCS_DISP_STOPHDUBATCHPOLL_NACK              (MCS_DISP_MSG_BGN + 427)

    //暂停
    #define MCS_DISP_PAUSEHDUBATCHPOLL_ACK               (MCS_DISP_MSG_BGN + 428)
    #define MCS_DISP_PAUSEHDUBATCHPOLL_NACK              (MCS_DISP_MSG_BGN + 429)

    //继续
    #define MCS_DISP_RESUMEHDUBATCHPOLL_ACK              (MCS_DISP_MSG_BGN + 430)
    #define MCS_DISP_RESUMEHDUBATCHPOLL_NACK             (MCS_DISP_MSG_BGN + 431)

    //通知
    #define MCS_DISP_HDUBATCHPOLLSTATUS_NOTIF            (MCS_DISP_MSG_BGN + 432)


//3   其他
//3.1 操作超时
    #define MCS_DISP_OPERATE_TIMEOUT                    (MCS_DISP_MSG_BGN + 498) 
//3.2 检测到业务消息长度不合理，通知上层将光标恢复
    #define MCS_DISP_SERVMSGLENERROR                    (MCS_DISP_MSG_BGN + 499)

//4   会议调度相关消息
//4.1 修改调度模式
    #define MCU_DISP_VCS_CHANGE_MODE_ACK                (MCS_DISP_MSG_BGN + 600)
    #define MCU_DISP_VCS_CHANGE_MODE_NACK               (MCS_DISP_MSG_BGN + 601)
    #define MCU_DISP_VCS_CHANGE_MODE_NOTIF              (MCS_DISP_MSG_BGN + 602)

//4.2 调度终端
    #define MCS_DISP_VCS_SHEDUALE_MT_ACK                (MCS_DISP_MSG_BGN + 603)
    #define MCS_DISP_VCS_SHEDUALE_MT_NACK               (MCS_DISP_MSG_BGN + 604)
    #define MCS_DISP_VCS_SHEDUALE_MT_NOTIF              (MCS_DISP_MSG_BGN + 605)

//4.3 调度状态通知
    #define MCS_DISP_VCS_CONF_STATUS_NOTIF              (MCS_DISP_MSG_BGN + 606)

//4.4 进入调度
    #define MCU_DISP_VCS_ENTER_CONF_ACK                 (MCS_DISP_MSG_BGN + 607)
    #define MCU_DISP_VCS_ENTER_CONF_NACK                (MCS_DISP_MSG_BGN + 608)

//4.5 离开调度
    #define MCU_DISP_VCS_QUIT_CONF_ACK                  (MCS_DISP_MSG_BGN + 609)
    #define MCU_DISP_VCS_QUIT_CONF_NACK                 (MCS_DISP_MSG_BGN + 610)

//4.6 声音控制
    #define MCU_DISP_VCS_SOUND_CONTROL_ACK              (MCS_DISP_MSG_BGN + 611)
    #define MCU_DISP_VCS_SOUND_CONTROL_NACK             (MCS_DISP_MSG_BGN + 612)

//4.7 VCS名称
    #define MCU_DISP_VCS_CHANGE_VCS_NAME_ACK            (MCS_DISP_MSG_BGN + 613)
    #define MCU_DISP_VCS_CHANGE_VCS_NAME_NACK           (MCS_DISP_MSG_BGN + 614)
    #define MCU_DISP_VCS_CHANGE_VCS_NAME_NOTIF          (MCS_DISP_MSG_BGN + 615)

//5.1 请求呼叫组呼组
    #define MCU_DISP_VCS_CALL_GROUP_ACK                 (MCS_DISP_MSG_BGN + 616)
    #define MCU_DISP_VCS_CALL_GROUP_NACK                (MCS_DISP_MSG_BGN + 617)
    #define MCU_DISP_VCS_CALL_GROUP_NOTIF               (MCS_DISP_MSG_BGN + 618)

//5.2 批量挂断组呼组终端
    #define MCU_DISP_VCS_DROP_CALL_GROUP_MT_ACK         (MCS_DISP_MSG_BGN + 619)
    #define MCU_DISP_VCS_DROP_CALL_GROUP_MT_NACK        (MCS_DISP_MSG_BGN + 620)

//5.3 开启本地轮询
    #define MCU_DISP_VCS_START_CHAIRMANPOLL_ACK         (MCS_DISP_MSG_BGN + 621)
    #define MCU_DISP_VCS_START_CHAIRMANPOLL_NACK        (MCS_DISP_MSG_BGN + 622)

//5.4 关闭本地轮询
    #define MCU_DISP_VCS_STOP_CHAIRMANPOLL_ACK         (MCS_DISP_MSG_BGN + 623)
    #define MCU_DISP_VCS_STOP_CHAIRMANPOLL_NACK        (MCS_DISP_MSG_BGN + 624)

//5.5 临时添加终端
    #define MCU_DISP_VCS_ADD_MT_ACK                     (MCS_DISP_MSG_BGN + 625)
    #define MCU_DISP_VCS_ADD_MT_NACK                    (MCS_DISP_MSG_BGN + 626)

//5.6 删除终端
    #define MCU_DISP_VCS_DELETE_MT_ACK                  (MCS_DISP_MSG_BGN + 627)
    #define MCU_DISP_VCS_DELETE_MT_NACK                 (MCS_DISP_MSG_BGN + 628)

//7 用户设置
    #define MCU_DISP_VCS_USER_SETTING_ACK               (MCS_DISP_MSG_BGN + 629)
    #define MCU_DISP_VCS_USER_SETTING_NACK              (MCS_DISP_MSG_BGN + 630)
    #define MCU_DISP_VCS_USER_SETTING_NOTIF             (MCS_DISP_MSG_BGN + 631)

//8 平级强拆
    #define MCU_DISP_VCS_RELEASE_MT_REQ                 (MCS_DISP_MSG_BGN + 632)
    #define MCU_DISP_VCS_RELEASE_MT_NOTIF               (MCS_DISP_MSG_BGN + 633)

// 连接上备板时通知界面的消息
    #define MCU_DISP_CONNECT_SLAVE_MCU_ACK              (MCS_DISP_MSG_BGN + 699)

//会控消息的下限
#define MCS_DISP_MSG_END                                (MCS_DISP_MSG_BGN + 700)

//vcslib消息
#define VCSLIB_DISP_MSG_BGN                             (MCS_DISP_MSG_END + 500)
#define VCSLIB_DISP_MSG_END                             (VCSLIB_DISP_MSG_BGN + 300)

//4 mcslib内部消息
//4.1   定时消息
    OSPEVENT( EV_SET_TIMER,                             EV_MC_BGN );
    OSPEVENT( TIMER_WAIT_REPLY,                         EV_MC_BGN + 1 );
    //连接备用MCU, 向MCU注册(发送MCS_MCU_CONNECT_REQ后等待回应)
    OSPEVENT( TIMER_REG_BAKMCU,                         EV_MC_BGN + 2 );
    //查询MCU定时(CPU使用率、TMcuStatus)
    OSPEVENT( TIMER_REFRESHMCU,                         EV_MC_BGN + 6 );

//5 测试查询消息
//5.1   地址簿
    //地址簿条目使用数, 消息体
    //发送: 无
    //返回: u32
    OSPEVENT( MCSLIB_QUERY_ADDRENTRYUSEDNUM,            EV_MC_BGN + 20 );
#define MCSLIB_QUERY_MSG_BEGIN          MCSLIB_QUERY_ADDRENTRYUSEDNUM
    //地址簿会议组使用数, 消息体
    //发送: 无
    //返回: u32
    OSPEVENT( MCSLIB_QUERY_ADDRGROUPUSEDNUM,            EV_MC_BGN + 21 );
    //地址簿所有条目, 消息体
    //发送: u32(已接收个数)
    //返回: u32(总个数) + u32(已发送个数) + u32(这次发送个数) + n * CAddrEntry
    OSPEVENT( MCSLIB_QUERY_ADDRALLENTRY,                EV_MC_BGN + 22 );
    //地址簿所有会议组, 消息体
    //发送: u32(已接收个数)
    //返回: u32(总个数) + u32(已发送个数) + u32(这次发送个数) + n * CAddrMultiSetEntry
    OSPEVENT( MCSLIB_QUERY_ADDRALLGROUP,                EV_MC_BGN + 23 );
    //地址簿条目是否存在, 消息体
    //发送: TADDRENTRYINFO
    //返回: BOOL
    OSPEVENT( MCSLIB_QUERY_ENTRYEXIST,                  EV_MC_BGN + 24 );
    //会议组是否存在, 消息体
    //发送: TMULTISETENTRYINFO
    //返回: BOOL
    OSPEVENT( MCSLIB_QUERY_GROUPEXIST,                  EV_MC_BGN + 25 );
    //地址簿条目是否存在于会议组中, 消息体
    //发送: TADDRENTRYINFO + TMULTISETENTRYINFO
    //返回: BOOL
    OSPEVENT( MCSLIB_QUERY_ENTRYEXISTINGROUP,           EV_MC_BGN + 26 );

//5.2   用户
    //用户总数, 消息体
    //发送: 无
    //返回: u32
    OSPEVENT( MCSLIB_QUERY_USERNUM,                     EV_MC_BGN + 35 );
    //所有用户, 消息体
    //发送: 无
    //返回: u32(总个数) + n * CUserFullInfo
    OSPEVENT( MCSLIB_QUERY_USERTABLE,                   EV_MC_BGN + 36 );

//5.3   会议
    //所有会议ID, 消息体
    //发送: 无
    //返回: u32(会议个数) + n * CConfId
    OSPEVENT( MCSLIB_QUERY_ALLCONFID,                   EV_MC_BGN + 45 );
    //TConfInfo, 消息体
    //发送: CConfId
    //返回: TConfInfo
    OSPEVENT( MCSLIB_QUERY_CONFINFO,                    EV_MC_BGN + 46 );
    //TConfAllMtInfo, 消息体
    //发送: CConfId
    //返回: TConfAllMtInfo
    OSPEVENT( MCSLIB_QUERY_CONFALLMTINFO,               EV_MC_BGN + 47 );
    //会议其他信息, 消息体
    //发送: CConfId
    //返回: TTvWallModule + TVmpModule + u8(m_byLockBySelf) + u32(m_dwLockMcsIP)
    //      + u8[33](m_abyLockUserName) + TEqp(m_tRecEqp) + TEqp(m_tPlayEqp)
    OSPEVENT( MCSLIB_QUERY_CONFOTHERINFO,               EV_MC_BGN + 48 );
    //会议所有MCU, 消息体
    //发送: CConfId
    //返回: u8(MCU个数) + n * TMcu
    OSPEVENT( MCSLIB_QUERY_CONFALLMCU,                  EV_MC_BGN + 49 );
    //其他MCU下信息, 消息体
    //发送: CConfId + TMcu
    //返回: TMt(m_tMediaSrcMt) + u8(m_byLockStatus) + TDiscussParam(m_tMixParam)
    OSPEVENT( MCSLIB_QUERY_CONFMCUOTHERINFO,            EV_MC_BGN + 50 );
    //会议终端列表, 消息体
    //发送: CConfId + TMcu + u32(本张列表已接收终端个数)
    //返回: u32(总个数) + u32(已发送个数) + u32(这次发送个数) + n * CMt
    OSPEVENT( MCSLIB_QUERY_MTTABLE,                     EV_MC_BGN + 51 );
    //终端, 消息体
    //发送: CConfId + TMt
    //返回: CMt
    OSPEVENT( MCSLIB_QUERY_MT,                          EV_MC_BGN + 52 );
    //监控通道信息, 消息体
    //发送: u8(通道号)
    //返回: TMonitorParam
    OSPEVENT( MCSLIB_QUERY_MONITORPARAM,                EV_MC_BGN + 53 );

//5.4   外设
    //外设列表, 消息体
    //发送: u32(已接受个数)
    //返回: u32(总个数) + u32(已发送个数) + u32(这次发送个数) + n * ( TPeriEqpStatus + u32(IP) )
    OSPEVENT( MCSLIB_QUERY_PERITABLE,                   EV_MC_BGN + 60 );
    //指定外设, 消息体
    //发送: TEqp
    //返回: TPeriEqpStatus
    OSPEVENT( MCSLIB_QUERY_PERISTATUS,                  EV_MC_BGN + 61 );

//5.5   当前MCU状态
    //是否有用户登录, 消息体
    //发送: 无
    //返回: BOOL
    OSPEVENT( MCSLIB_QUERY_USERLOGON,                   EV_MC_BGN + 70 );
    //TMcuExt, 消息体
    //发送: 无
    //返回: TMcuExt
    OSPEVENT( MCSLIB_QUERY_MCUSTATUS,                   EV_MC_BGN + 71);

//5.6   设置查询MCU的索引, 消息体
    //发送: u32(MCU IP地址)
    //返回: BOOL
    OSPEVENT( MCSLIB_QUERY_SETMCUSESSION,               EV_MC_BGN + 75 );
#define MCSLIB_QUERY_MSG_END          MCSLIB_QUERY_SETMCUSESSION

//6 mcslib单元测试消息
//6.1   模拟MCU与测试库
    //  模拟MCU请求测试库响应
    OSPEVENT(MCU_TESTER_REQ,                            EV_MC_BGN + 200);
    //  测试库回应模拟MCU响应请求
    OSPEVENT(TESTER_MCU_ACK,                            EV_MC_BGN + 201);

    //  测试库发送模拟MCU消息完毕请求
    OSPEVENT(TESTER_MCU_END_REQ,                        EV_MC_BGN + 202);
    //  模拟MCU回应测试库消息发送完毕请求
    OSPEVENT(MCU_TESTER_END_ACK,                        EV_MC_BGN + 203);

#endif  //  _EVMCSLIB_20050426_H_