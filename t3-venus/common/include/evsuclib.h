/*=============================================================================
模   块   名: 文件升级客户端业务功能库
文   件   名: evsuclib.h
相 关  文 件: 无
文件实现功能: suclib 向界面发送的消息
作        者: 王昊
版        本: V1.0  Copyright(C) 2006-2007 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/02/13  1.0     王昊        创建
=============================================================================*/

#ifndef _EVSUCLIB_
#define _EVSUCLIB_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//1. 连接
    //连接成功，消息体：u32(服务器IP地址，网络序)
    SUC_EVENT( SUC_DISP_CONNECT_ACK,            SUCLIB_MSG_BGN )
    //连接失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_CONNECT_NACK,           SUCLIB_MSG_BGN + 1 )

    //断开成功，消息体：u32(服务器IP地址，网络序)
    SUC_EVENT( SUC_DISP_LOGOUT_ACK,             SUCLIB_MSG_BGN + 2 )
    //断开失败，消息体：无，含错误码，不会发送该消息
    SUC_EVENT( SUC_DISP_LOGOUT_NACK,            SUCLIB_MSG_BGN + 3 )

    //允许重启，消息体：无
    SUC_EVENT( SUC_DISP_RESET_ACK,              SUCLIB_MSG_BGN + 4 )
    //拒绝重启，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_RESET_NACK,             SUCLIB_MSG_BGN + 5 )

//2. 用户
    //获取用户列表成功，消息体：无
    SUC_EVENT( SUC_DISP_GETUSERLIST_ACK,        SUCLIB_MSG_BGN + 10 )
    //获取用户列表失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_GETUSERLIST_NACK,       SUCLIB_MSG_BGN + 11 )
    //用户列表通知，消息体：无
    SUC_EVENT( SUC_DISP_USERLIST_NOTIF,         SUCLIB_MSG_BGN + 12 )

    //添加用户成功，消息体：无
    SUC_EVENT( SUC_DISP_ADDUSER_ACK,            SUCLIB_MSG_BGN + 13 )
    //添加用户失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_ADDUSER_NACK,           SUCLIB_MSG_BGN + 14 )

    //编辑用户成功，消息体：无
    SUC_EVENT( SUC_DISP_EDITUSER_ACK,           SUCLIB_MSG_BGN + 15 )
    //编辑用户失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_EDITUSER_NACK,          SUCLIB_MSG_BGN + 16 )

    //删除用户成功，消息体：无
    SUC_EVENT( SUC_DISP_DELUSER_ACK,            SUCLIB_MSG_BGN + 17 )
    //删除用户失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_DELUSER_NACK,           SUCLIB_MSG_BGN + 18 )

//3. 版本消息
    //获取所有推荐版本成功(与SUC_DISP_ALLRECOMMENDEDVER_NOTIF互斥)，消息体：无
    SUC_EVENT( SUC_DISP_GETALLRECOMMENDEDVER_ACK,   SUCLIB_MSG_BGN + 30 )
    //获取所有推荐版本失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_GETALLRECOMMENDEDVER_NACK,  SUCLIB_MSG_BGN + 31 )
    //所有推荐版本通知，(与SUC_DISP_GETALLRECOMMENDEDVER_ACK互斥)，消息体：无
    SUC_EVENT( SUC_DISP_ALLRECOMMENDEDVER_NOTIF,    SUCLIB_MSG_BGN + 32 )

    //获取指定设备所有版本成功，与SUC_DISP_ONEDEVVERINFO_NOTIF互斥
    //消息体：IFCSrvDevVerFullInfo * n
    SUC_EVENT( SUC_DISP_GETONEDEVVERINFO_ACK,       SUCLIB_MSG_BGN + 35 )
    //获取指定设备所有版本失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_GETONEDEVVERINFO_NACK,      SUCLIB_MSG_BGN + 36 )
    //某一设备所有版本通知，与SUC_DISP_GETONEDEVVERINFO_ACK互斥
    //消息体：IFCSrvDevVerFullInfo * n
    SUC_EVENT( SUC_DISP_ONEDEVVERINFO_NOTIF,        SUCLIB_MSG_BGN + 37 )

    //设置推荐版本成功，消息体：无
    SUC_EVENT( SUC_DISP_SETRECOMMENDEDVER_ACK,      SUCLIB_MSG_BGN + 40 )
    //设置推荐版本失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_SETRECOMMENDEDVER_NACK,     SUCLIB_MSG_BGN + 41 )
    //设置推荐版本失败通知，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_SETRECOMM_FAIL_NOTIF,       SUCLIB_MSG_BGN + 42 )
    //设置推荐版本进度通知，消息体：u16(除以10得到百分数，主机序)
    SUC_EVENT( SUC_DISP_SETRECOMM_PRO_NOTIF,        SUCLIB_MSG_BGN + 43 )
    //推荐版本变更通知，消息体：
    //u32(原有推荐版本设备编号，网络序，如果为-1则说明原来没有推荐版本)
    //+ IFCSrvDevVerFullInfo(新的推荐版本)
    SUC_EVENT( SUC_DISP_RECOMMENDEDVER_NOTIF,       SUCLIB_MSG_BGN + 44 )

    //删除某一版本成功，与SUS_DISP_DELONEVER_NOTIF互斥
    //消息体：u32(版本编号，主机序)
    SUC_EVENT( SUC_DISP_DELONEVER_ACK,              SUCLIB_MSG_BGN + 50 )
    //删除某一版本失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_DELONEVER_NACK,             SUCLIB_MSG_BGN + 51 )
    //删除某一版本通知，与SUS_DISP_DELONEVER_ACK互斥
    //消息体：u32(版本编号，主机序)
    SUC_EVENT( SUC_DISP_DELONEVER_NOTIF,            SUCLIB_MSG_BGN + 52 )

    //编辑某一版本成功，与SUS_DISP_EDITONEVER_NOTIF互斥
    //消息体：u32(设备编号，网络序) + IFCHardwareVer + s8[MAX_FILESRV_BUG_REPORT_LEN]
    SUC_EVENT( SUC_DISP_EDITONEVER_ACK,             SUCLIB_MSG_BGN + 55 )
    //编辑某一版本失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_EDITONEVER_NACK,            SUCLIB_MSG_BGN + 56 )
    //编辑某一版本通知，与SUS_DISP_EDITONEVER_ACK互斥
    //消息体：u32(设备编号，网络序) + IFCHardwareVer + s8[MAX_FILESRV_BUG_REPORT_LEN]
    SUC_EVENT( SUC_DISP_EDITONEVER_NOTIF,           SUCLIB_MSG_BGN + 57 )

//4. 配置消息
    //获取配置成功，消息体：ISusConfig
    SUC_EVENT( SUC_DISP_GETCFG_ACK,                 SUCLIB_MSG_BGN + 70 )
    //获取配置失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_GETCFG_NACK,                SUCLIB_MSG_BGN + 71 )


    //修改配置成功，与SUS_DISP_CFG_NOTIF互斥
    //消息体：ISusConfig
    SUC_EVENT( SUC_DISP_EDITCFG_ACK,                SUCLIB_MSG_BGN + 80 )
    //修改配置失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_EDITCFG_NACK,               SUCLIB_MSG_BGN + 81 )
    //配置更新通知，与SUS_DISP_EDITCFG_ACK互斥
    //消息体：ISusConfig
    SUC_EVENT( SUC_DISP_CFG_NOTIF,                  SUCLIB_MSG_BGN + 82 )

//5. 文件消息
    //停止上传成功，消息体：无
    SUC_EVENT( SUC_DISP_STOPUPGRADE_ACK,            SUCLIB_MSG_BGN + 100 )
    //停止上传失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_STOPUPGRADE_NACK,           SUCLIB_MSG_BGN + 101 )

    //开始上传成功，消息体：无
    SUC_EVENT( SUC_DISP_STARTUPGRADE_ACK,           SUCLIB_MSG_BGN + 105 )
    //开始上传失败，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_STARTUPGRADE_NACK,          SUCLIB_MSG_BGN + 106 )
    //上传过程错误，消息体：无，含错误码
    SUC_EVENT( SUC_DISP_UPGRADEFAIL_NOTIF,          SUCLIB_MSG_BGN + 107 )
    //上传进度通知，消息体：u16(进度，精确到%前小数点后一位，主机序)
    SUC_EVENT( SUC_DISP_UPGRADEPROGRESS_NOTIF,      SUCLIB_MSG_BGN + 108 )
    //上传结果通知，消息体：
    //u8(文件个数)
    //+ [ s8[MAX_FILESRV_FILENAME_LEN](文件名) + u32(0为成功，否则为错误码，网络序) ]
    //  * n
    SUC_EVENT( SUC_DISP_UPGRADERESULT_NOTIF,        SUCLIB_MSG_BGN + 109 )

//6. 特殊消息
    //超时，含错误码
    SUC_EVENT( SUC_DISP_TIMEOUT,                SUCLIB_MSG_BGN + 300 )
    //断链，消息体：u32(服务器IP地址，网络序)
    SUC_EVENT( SUC_DISP_DISCONNECTED,           SUCLIB_MSG_BGN + 301 )

#endif//_EVSUCLIB_