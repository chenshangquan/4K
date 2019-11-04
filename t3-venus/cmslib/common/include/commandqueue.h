/*=======================================================================
模块名      : MTCLib
文件名      : CommandQueue.h
相关文件    : 
文件实现功能: 命令型消息的队列缓冲
作者        : 王廖荣
版本        : V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本  修改人  修改内容
2006/08/22  4.0   王廖荣    创建
=======================================================================*/

#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "kdvdispevent.h"
#include "tpmsg.h"

#include <queue>
using namespace std;

typedef struct tagCommand
{
    CMessage        m_cMsg;
    CTpMsg          m_cMtMsg;
    CKdvDispEvent*     m_pCDispEvent;
    vector<u16>     m_vctWaitEvent;
    u32             m_nEventNum;
    u32             m_dwType;
    u32             m_dwTimeout;
}TCOMMAND;

class CCommandQueue  
{
public:
    // 增加一条命令到缓冲队列中
	void PushCommand(CMessage& cMsg, CTpMsg& cMtMsg, CKdvDispEvent *pDispEvent,
                     u16 *pwWaitEvent, s32 nEventNum, u32 dwType, u32 dwTimeOut);
    
    // 获取缓冲队列中的一条命令，并将该条消息从队列中删除
    BOOL32 GetNextCommand(TCOMMAND& tCommand);

    // 清空缓冲队列的消息
	void ClearCommand();
    // 返回缓冲队列的消息个数
	u32 GetCommandCount();
    // 判断队列是否为空
    BOOL32 IsEmpty(){   return m_vctCommandQueue.empty();  }

	CCommandQueue();
	virtual ~CCommandQueue();

private:
    // 增加一条命令到缓冲队列中
	void PushCommand(TCOMMAND& tCommand);
    // 删除缓冲队列中的一条命令
    void PopCommand();
    // 取得缓冲队列中的第一条命令
    void FrontCommand(TCOMMAND& tCommand);

    queue<TCOMMAND>     m_vctCommandQueue;
};

#endif
