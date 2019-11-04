/*=======================================================================
模块名      : MTCLib
文件名      : CommandQueue.cpp
相关文件    : 
文件实现功能: 命令型消息的队列缓冲
作者        : 王廖荣
版本        : V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本  修改人  修改内容
2006/08/22  4.0   王廖荣    创建
=======================================================================*/

#include "stdafx.h"
#include "CommandQueue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommandQueue::CCommandQueue()
{
    ClearCommand();
}

CCommandQueue::~CCommandQueue()
{
    ClearCommand();
}

/*=============================================================================
  函 数 名： GetCommandCount
  功    能： 返回缓冲队列的消息个数
  算法实现： 
  全局变量： 
  参    数： 

  返 回 值： u32
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2006/08/22    4.0		    王廖荣                  创建
=============================================================================*/
u32 CCommandQueue::GetCommandCount()
{
    return m_vctCommandQueue.size();
}

/*=============================================================================
  函 数 名： ClearCommand
  功    能： 清空缓冲队列的消息
  算法实现： 
  全局变量： 
  参    数： 

  返 回 值： void
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2006/08/22    4.0		    王廖荣                  创建
=============================================================================*/
void CCommandQueue::ClearCommand()
{
    u32 nSize = m_vctCommandQueue.size();
    for(u32 nIndex = 0; nIndex < nSize; nIndex++)
    {
        m_vctCommandQueue.pop();
    }
}

/*=============================================================================
  函 数 名： PushCommand
  功    能： 增加一条命令到缓冲队列中
  算法实现： 
  全局变量： 
  参    数： TCOMMAND &tCommand

  返 回 值： void
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2006/08/22    4.0		    王廖荣                  创建
=============================================================================*/
void CCommandQueue::PushCommand(TCOMMAND &tCommand)
{
    m_vctCommandQueue.push(tCommand);
}

/*=============================================================================
  函 数 名： PushCommand
  功    能： 增加一条命令到缓冲队列中
  算法实现： 
  全局变量： 
  参    数： CMessage& cMsg, CMtMsg& cMtMsg, CDispEvent *pDispEvent,
             u16 *pwWaitEvent, s32 nEventNum, u32 dwType, u32 dwTimeOut

  返 回 值： void
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2006/08/22    4.0		    王廖荣                  创建
=============================================================================*/
void CCommandQueue::PushCommand(CMessage& cMsg, CTpMsg& cMtMsg, CKdvDispEvent *pDispEvent,
                                u16 *pwWaitEvent, s32 nEventNum, u32 dwType, u32 dwTimeOut)
{
    TCOMMAND tCommand;
    tCommand.m_cMsg = cMsg;
    tCommand.m_cMtMsg = cMtMsg;
    tCommand.m_pCDispEvent = pDispEvent;
    tCommand.m_nEventNum = nEventNum;
    tCommand.m_dwType = dwType;
    tCommand.m_dwTimeout = dwTimeOut;

    for(s32 nIndex = 0; nIndex < nEventNum; nIndex++)
    {
        tCommand.m_vctWaitEvent.push_back(*pwWaitEvent);
        pwWaitEvent++;
    }

    PushCommand(tCommand);
}

/*=============================================================================
  函 数 名： GetNextCommand
  功    能： 获取缓冲队列中的一条命令，并将该条消息从队列中删除
  算法实现： 
  全局变量： 
  参    数： TCOMMAND &tCommand

  返 回 值： BOOL32
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2006/08/22    4.0		    王廖荣                  创建
=============================================================================*/
BOOL32 CCommandQueue::GetNextCommand(TCOMMAND& tCommand)
{
    if(!IsEmpty())
    {
        FrontCommand(tCommand);
        PopCommand();
        return TRUE;
    }

    return FALSE;
}

/*=============================================================================
  函 数 名： PopCommand
  功    能： 删除缓冲队列中的一条命令
  算法实现： 
  全局变量： 
  参    数： 

  返 回 值： void
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2006/08/22    4.0		    王廖荣                  创建
=============================================================================*/
void CCommandQueue::PopCommand()
{
    if(m_vctCommandQueue.size() > 0)
    {
        m_vctCommandQueue.pop();
    }
}

/*=============================================================================
  函 数 名： FrontCommand
  功    能： 取得缓冲队列中的第一条命令
  算法实现： 
  全局变量： 
  参    数： TCOMMAND& tCommand

  返 回 值： void
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2006/08/22    4.0		    王廖荣                  创建
=============================================================================*/
void CCommandQueue::FrontCommand(TCOMMAND& tCommand)
{
    tCommand = m_vctCommandQueue.front();
}