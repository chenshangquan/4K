/*=============================================================================
模   块   名: 终端控制台业务功能库
文   件   名: mtclibconst.h
相 关  文 件: mtclibconst.cpp
文件实现功能: mtclib宏定义
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2007 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/05/28  4.0     王昊        创建
=============================================================================*/

#ifndef _MTCLIBCONST_20070528_H_
#define _MTCLIBCONST_20070528_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//最大连接终端数
#ifndef MAX_MTCLIB_SSN_NUM
#define MAX_MTCLIB_SSN_NUM              (s32)16
#endif

//发送消息类型
enum EMSendMsgType
{
    enumSendMsgTypeUnKnown      = (s32)0,
    enumSendMsgTypeCMessage     = (s32)1,//普通CMessage
    enumSendMsgTypeCMtMsg       = (s32)2//CMtMsg
};

//错误码
enum EMMtclibErrorCode
{
    enumMtclibErrorCodeNoError      = (u16)0,//成功
    enumMtclibErrorCodeDeliver      = (u16)1,//发送失败
    enumMtclibErrorCodeUnknownType  = (u16)2,//未知消息类型
    enumMtclibErrorCodeOspInit      = (u16)3,//OSP初始化失败
    enumMtclibErrorCodeCreateApp    = (u16)4,//创建LIB线程失败
    enumMtclibErrorCodeMemory       = (u16)5,//内存不足
};

//实例状态
enum EMInstState
{
    enumInstStateIdle           = (s32)0,//空闲
    enumInstStateConnecting     = (s32)1,//连接中
    enumInstStateService        = (s32)2//服务中
};


#ifndef MTCLIB_MSG_BGN
#define MTCLIB_MSG_BGN              WM_USER + 0x500
#endif
#ifndef MTCLIB_MSG_END
#define MTCLIB_MSG_END              WM_USER + 0x900
#endif


//  消息栈最大长度
#ifndef QUEUE_SIZE
#define QUEUE_SIZE                  (u16)2000
#endif

//外接矩阵最大个数
#ifndef MAX_OUTER_MATRIX_NUM
#define MAX_OUTER_MATRIX_NUM        (s32)64
#endif


//MC画面合成终端最大个数
#ifndef MAX_MC_CP_MEMBER_NUM
#define MAX_MC_CP_MEMBER_NUM        (s32)6
#endif

#endif//_MTCLIBCONST_20070528_H_
