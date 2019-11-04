/*=============================================================================
模   块   名: 终端控制台业务功能库
文   件   名: mtclibssninst.h
相 关  文 件: mtclibssninst.cpp
文件实现功能: mtclib实例
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2007 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/05/28  4.0     王昊        创建
=============================================================================*/

#ifndef _MTCLIBSSNINST_20070528_H_
#define _MTCLIBSSNINST_20070528_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MtclibInterface.h"

class CMtclibSsnInst : public CMtclibInterface
{
public:
    CMtclibSsnInst();

    virtual ~CMtclibSsnInst();

public:
    virtual void DaemonInstanceEntry(CMessage * const pcMsg, CApp *pcApp);

    virtual void InstanceEntry(CMessage * const pcMsg);

    virtual void InstanceExit(void);

    //获取接收消息队列
    void GetRecvMsgQueue(queue<CMessage> &queueMsg);

    //销毁定时器
    void MtclibKillTimer(u32 dwTimer);

private:
    //处理超时事件
    void ProcTimeout(void);

    //处理断链事件
    void ProcOspDisconnect(CMessage * const pcMsg);

protected:
    u8              m_abyMsgDealBuf[MAX_MSG_LEN];
    queue<CMessage> m_queueRecvMsg;
};


#endif//_MTCLIBSSNINST_20070528_H_
