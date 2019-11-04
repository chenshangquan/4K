/*=============================================================================
模   块   名: 终端控制台业务功能库
文   件   名: mtclibconnectmsgdeal.h
相 关  文 件: mtclibconnectmsgdeal.cpp
文件实现功能: mtclib连接消息处理类
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2007 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/06/02  4.0     王昊        创建
=============================================================================*/

#ifndef _MTCLIBCONNECTMSGDEAL_20070602_H_
#define _MTCLIBCONNECTMSGDEAL_20070602_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMtclibConnectMsgDeal
{
public:
    CMtclibConnectMsgDeal() {}
    virtual ~CMtclibConnectMsgDeal() {}

public:
    //消息处理
    BOOL32 MessageProc(CMessage * const pcMsg, s32 nInstIndex);

private:
    //
};

#endif//_MTCLIBCONNECTMSGDEAL_20070602_H_