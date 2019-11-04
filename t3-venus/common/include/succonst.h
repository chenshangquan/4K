/*=============================================================================
模   块   名: 文件升级客户端业务功能库
文   件   名: succonst.h
相 关  文 件: 无
文件实现功能: suc模块公用宏定义
作        者: 王昊
版        本: V1.0  Copyright(C) 2006-2007 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/02/11  1.0     王昊        创建
=============================================================================*/

#ifndef _SUCCONST_
#define _SUCCONST_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//suclib最大实例数
#define MAXINST_SUCLIB_NUM              (s32)16

//超时时间(6秒)
#define DEFAULT_TIMEOUT                 (u32)(6 * 1000)

//权限
#define RIGHT_ADMIN                     (u8)1//管理员
#define RIGHT_OPERATOR                  (u8)0//操作员

//错误码
#define SUCLIB_ERRORCODE_BEGIN          (u16)10000
#define SUCLIB_ERRORCODE_END            (u16)20000
#define SUCLIB_OK                       (u16)0
//#define SUCLIB_PWD_EMPTY                (SUCLIB_ERRORCODE_BEGIN + 1)
#define SUCLIB_ALREADY_CONNECT          (SUCLIB_ERRORCODE_BEGIN + 2)
#define SUCLIB_CONNECT_FAIL             (SUCLIB_ERRORCODE_BEGIN + 3)
#define SUCLIB_POST_MSG_TO_SUS_FAIL     (SUCLIB_ERRORCODE_BEGIN + 4)
#define SUCLIB_MSG_LEN_ERROR            (SUCLIB_ERRORCODE_BEGIN + 5)
#define SUCLIB_BUSY_LAST_REQ            (SUCLIB_ERRORCODE_BEGIN + 6)
#define SUCLIB_NO_RIGHT                 (SUCLIB_ERRORCODE_BEGIN + 7)
#define SUCLIB_READ_FILE_FAIL           (SUCLIB_ERRORCODE_BEGIN + 8)


#define SUC_EVENT(msg, id)      const u16 msg = (u16)(id);


#define SUCLIB_MSG_BGN              WM_USER + 0x500
#define SUCLIB_MSG_END              WM_USER + 0x800



#endif//_SUCCONST_
