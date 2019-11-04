/*=============================================================================
模   块   名: 终端控制台业务功能库
文   件   名: mtclibcom.h
相 关  文 件: mtclibcom.cpp
文件实现功能: mtclib供UI使用接口
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2007 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/06/01  4.0     王昊        创建
=============================================================================*/

#ifndef _MTCLIBCOM_20070601_H_
#define _MTCLIBCOM_20070601_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MtclibSsnData.h"

//LIB线程
extern zTemplate<CMtclibSsnInst, MAX_MTCLIB_SSN_NUM, CMtclibSsnData> *g_pcMtclibApp;
//消息发送接口类(UI->MT)
extern CMtclibSsnInst           *g_pcCurInterface;

typedef zTemplate<CMtclibSsnInst, MAX_MTCLIB_SSN_NUM, CMtclibSsnData> CMtclibApp;


/*=============================================================================
函 数 名: MtclibInit
功    能: MTCLIB初始化
参    数: HWND hWnd                         [in]    UI窗口句柄
          u16 wListenPort                   [in]    telnet端口
          BOOL32 bOpenTelnet                [in]    是否打开telnet窗口
注    意: 无
返 回 值: 成功返回enumMtclibErrorCodeNoError, 失败返回错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/06/01  4.0     王昊    创建
=============================================================================*/
EMMtclibErrorCode MtclibInit(HWND hWnd, u16 wListenPort = 0, BOOL32 bOpenTelnet = FALSE);


/*=============================================================================
函 数 名: MtclibQuit
功    能: MTCLIB退出
参    数: 无
注    意: 无
返 回 值: 成功返回enumMtclibErrorCodeNoError, 失败返回错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/06/01  4.0     王昊    创建
=============================================================================*/
EMMtclibErrorCode MtclibQuit(void);


#endif//_MTCLIBCOM_20070601_H_
