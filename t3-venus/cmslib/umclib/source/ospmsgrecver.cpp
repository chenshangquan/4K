/*=======================================================================
模块名      : 终端控制台
文件名      : OspMsgRecver.h
相关文件    : 
文件实现功能: 实现接收OSP消息所需的CInstance派生类，消息缓存队列定义，
作者        : 熊广化
版本        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/12/16  3.0         熊广化      创建
2003/03/02	3.0			熊广化		化简
2004/08/23  3.5         李洪强      规范代码，修改结构
2004/10/11  3.5         王慧琛      整理代码，填加注释
=======================================================================*/

#include "stdafx.h"
#include "OspMsgRecver.h"
#include "addrmsgdriver.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////
// CMsgQueue
// 
CMsgQueue::CMsgQueue()
{
}
CMsgQueue::~CMsgQueue()
{
    Clear();
}

/*=============================================================================
  函 数 名： PushMsg
  功    能： 添加一条消息到消息队列
  算法实现： 
  全局变量： 
  参    数： CMessage* const pMsg  消息指针
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgQueue::PushMsg(CMessage* const pMsg)
{
    CMessage cMsg;
    cMsg = *pMsg;
    cMsg.content = new u8[pMsg->length];
    memcpy(cMsg.content, pMsg->content, pMsg->length);
    m_queMsg.push(cMsg);
}

/*=============================================================================
  函 数 名： PopMsg
  功    能： 从消息队列里弹出一条消息，并添加到目标队列里
  算法实现： 
  全局变量： 
  参    数： CMsgQueue &cOutQue 目标队列
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgQueue::PopMsg(CMsgQueue &cOutQue)
{
    CMessage *pMsg = &m_queMsg.front(); 
    cOutQue.PushMsg(pMsg);
    delete []pMsg->content;
    m_queMsg.pop();
}

/*=============================================================================
  函 数 名： Clear
  功    能： 清空队列
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgQueue::Clear()
{
    while (!m_queMsg.empty()) 
    {
        CMessage *pMsg = &m_queMsg.front();
        delete []pMsg->content;
        m_queMsg.pop();
    }
}

/*=============================================================================
  函 数 名： IsEmpty
  功    能： 判断消息队列是否为空
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： BOOL 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
BOOL CMsgQueue::IsEmpty()
{
    return m_queMsg.empty();
}


////////////////////////////////////////////////////////////////////////////////
// 全局Osp应用程序对象
  zTemplate<CMsgHandler, INSTANCE_COUNT, COspAppBase> g_UmcLibApp;
////////////////////////////////////////////////////////////////////////////////




// CMsgHandler
u32 CMsgHandler::WM_OSPMESSAGECOMING = WM_USER + 5;
u32 CMsgHandler::WM_OSPSYNCMSGCOMING = WM_USER + 6;
u32 CMsgHandler::WM_REQMTCSTATUS     = WM_USER + 7;
u32 CMsgHandler::WM_REQIKEY			= WM_USER + 8;

CMsgHandler* CMsgHandler::s_pMsgHandler = NULL;

CMsgHandler::CMsgHandler()
{
    InitializeCriticalSection(&m_csQueueOspMsg);
    // 2004/08/24 李洪强 目前只支持一个实例就可以了
    s_pMsgHandler = this;
}

CMsgHandler::~CMsgHandler()
{
    s_pMsgHandler = NULL;
    DeleteCriticalSection(&m_csQueueOspMsg);
}

/*=============================================================================
  函 数 名： PutSyncAck
  功    能： 同步消息反馈，目前全部用于集成测试消息的回应
  算法实现： 
  全局变量： 
  参    数： const void* pAckBuf 消息实际内容指针
             u16 u16AckSize      消息长度
  返 回 值： u32                 成功与否
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
u32 CMsgHandler::PutSyncAck(const void* pAckBuf, u16 u16AckSize)
{
    return SetSyncAck(pAckBuf, u16AckSize);
}


/*=============================================================================
  函 数 名： InstanceEntry
  功    能： OSP消息入口，转存消息队列到本地
  算法实现： 
  全局变量： 
  参    数： CMessage *const pMsg   消息指针
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgHandler::InstanceEntry(CMessage *const pMsg)
{
    if (pMsg->type !=3) //异步消息
    {
        EnterCriticalSection(&m_csQueueOspMsg);
        if(m_cMsgQue.Size() == 0)
            //原OSP消息队列为空时，通知本地消息队列再次来取消息
        {
            m_cMsgQue.PushMsg(pMsg);
            ::PostMessage(g_UmcLibApp.GetNotifyWindow(), WM_OSPMESSAGECOMING, 0, 0);        
        }
        else
            //本地消息队列正在取消息时，不发通知－－此步不可省，在同时收到多个OSP消息时，
            //有可能会走到这一步
        {
            m_cMsgQue.PushMsg(pMsg);
        }
        LeaveCriticalSection(&m_csQueueOspMsg);
    }
    else
    {
        // 同步消息
        SendMessage(g_UmcLibApp.GetNotifyWindow(), WM_OSPSYNCMSGCOMING,
             reinterpret_cast<WPARAM>(pMsg), 0);
    }    
}

/*=============================================================================
  函 数 名： PopAllMsg
  功    能： 清空OSP消息队列，并将其转入工作消息队列
  算法实现： 
  全局变量： 
  参    数： CMsgQueue &cMsgQue
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgHandler::PopAllMsg(CMsgQueue &cMsgQue)
{
    EnterCriticalSection(&m_csQueueOspMsg);
    while (!m_cMsgQue.IsEmpty()) 
    {
        m_cMsgQue.PopMsg(cMsgQue);
    }
    LeaveCriticalSection(&m_csQueueOspMsg);
}

/*=============================================================================
  函 数 名： ClearQueue
  功    能： 清空OSP消息队列，主要用于系统退出时
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgHandler::ClearQueue()
{
    EnterCriticalSection(&m_csQueueOspMsg);
    m_cMsgQue.Clear();
    LeaveCriticalSection(&m_csQueueOspMsg);
}

//////////////////////////////////////////////////////////////////////////
//  COspAppBase
//

COspAppBase::COspAppBase()
{
    m_dwNodeId = INVALID_NODE;
    m_hWndTarget = NULL;
}

COspAppBase::~COspAppBase()
{
}

/*=============================================================================
  函 数 名： ClearOspMsg
  功    能： 系统退出时清空OSP消息队列，防止出现刷新IE时的过期OSP消息
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void COspAppBase::ClearOspMsg()
{
    CMsgHandler *pHandler = CMsgHandler::GetMsgHandler();
    if (pHandler) 
    {
        pHandler->ClearQueue();
    }
}


////////////////////////////////////////////////////////////////////////////////
// 地址簿Osp应用程序对象
zTemplate<CAddrMsgHandler, INSTANCE_COUNT, COspAppBase> g_AddrBookApp;

////////////////////////////////////////////////////////////////////////////////
// CAddrMsgHandler
CAddrMsgHandler* CAddrMsgHandler::s_pAddrMsgHandler = NULL;

CAddrMsgHandler::CAddrMsgHandler()
{
    InitializeCriticalSection(&m_csQueueOspMsg);
    // 2004/08/24 李洪强 目前只支持一个实例就可以了
    s_pAddrMsgHandler = this;
}

CAddrMsgHandler::~CAddrMsgHandler()
{
    s_pAddrMsgHandler = NULL;
    DeleteCriticalSection(&m_csQueueOspMsg);
}

/*=============================================================================
  函 数 名： InstanceEntry
  功    能： OSP消息入口，转存消息队列到本地
  算法实现： 
  全局变量： 
  参    数： CMessage *const pMsg   消息指针
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容

=============================================================================*/
void CAddrMsgHandler::InstanceEntry(CMessage *const pMsg)
{
    if (pMsg->type !=3) //异步消息
    {
        EnterCriticalSection(&m_csQueueOspMsg);
        if(m_cMsgQue.Size() == 0)
            //原OSP消息队列为空时，通知本地消息队列再次来取消息
        {
            m_cMsgQue.PushMsg(pMsg);
            //::PostMessage(g_AddrBookApp.GetNotifyWindow(), CCncMsgHandler::WM_OSPMESSAGECOMING, 0, 0);     
			CAddrMsgDriver::s_pMsgDriver->OnOspMessageComing( 0, 0 );
        }
        else
            //本地消息队列正在取消息时，不发通知－－此步不可省，在同时收到多个OSP消息时，
            //有可能会走到这一步
        {
            m_cMsgQue.PushMsg(pMsg);
        }
        LeaveCriticalSection(&m_csQueueOspMsg);
    }
    else
    {
        // 同步消息
        SendMessage(g_AddrBookApp.GetNotifyWindow(), CMsgHandler::WM_OSPSYNCMSGCOMING,
             reinterpret_cast<WPARAM>(pMsg), 0);
    }    
}

/*=============================================================================
  函 数 名： PopAllMsg
  功    能： 清空OSP消息队列，并将其转入工作消息队列
  算法实现： 
  全局变量： 
  参    数： CMsgQueue &cMsgQue
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容

=============================================================================*/
void CAddrMsgHandler::PopAllMsg(CMsgQueue &cMsgQue)
{
    EnterCriticalSection(&m_csQueueOspMsg);
    while (!m_cMsgQue.IsEmpty()) 
    {
        m_cMsgQue.PopMsg(cMsgQue);
    }
    LeaveCriticalSection(&m_csQueueOspMsg);
}

/*=============================================================================
  函 数 名： ClearQueue
  功    能： 清空OSP消息队列，主要用于系统退出时
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容

=============================================================================*/
void CAddrMsgHandler::ClearQueue()
{
    EnterCriticalSection(&m_csQueueOspMsg);
    m_cMsgQue.Clear();
    LeaveCriticalSection(&m_csQueueOspMsg);
}