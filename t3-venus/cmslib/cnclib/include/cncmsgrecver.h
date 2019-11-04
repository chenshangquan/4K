/*=======================================================================
模块名      : 终端控制台
文件名      : cncmsgrecver.h
相关文件    : 
文件实现功能: 声明接收OSP消息所需的CInstance派生类
作者        : 熊广化
版本        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/12/16  3.0         熊广化      创建
2003/03/02	3.0			熊广化		化简
2004/08/23  3.5         李洪强      规范代码，修改结构
2005/03/16  3.6         王灰尘      添加状态打印
=======================================================================*/

#if !defined(AFX_OSPMSGRECVER_H__3FB841FA_784C_41CD_AFF4_A6DC381619A8__INCLUDED_)
#define AFX_OSPMSGRECVER_H__3FB841FA_784C_41CD_AFF4_A6DC381619A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define INSTANCE_COUNT	1	// 接收消息的实例的数目

#include <queue>
#include <vector>
#include "kdvtype.h"                                                                                            
#include "kdvdef.h" 
#include "osp.h"
//#include "MtConst.h"

using namespace std;

/************************************************************************/
/*                        消息队列定义                                  */
/************************************************************************/
class CCncMsgQueue
{
public:
    CCncMsgQueue();
    ~CCncMsgQueue();
    // 将一条消息压入队列中
    void PushMsg(CMessage* const pMsg);
    // 从队列中取出一条消息
    void PopMsg(CCncMsgQueue &cOutQue);
    // 从队列中弹出一条消息
    void Pop() 
    { 
        CMessage *pMsg = &m_queMsg.front(); 
        delete []pMsg->content;
        m_queMsg.pop(); 
    }
    // 队列是否为空
    BOOL IsEmpty();
    // 清空队列
    void Clear();
    // 得到队列最前面元素
    CMessage& Front() { return m_queMsg.front();}
    // 得到队列的大小
    s32 Size() { return m_queMsg.size(); }
private:
    queue<CMessage> m_queMsg;
};

/************************************************************************/
/*                        OSP实例定义                                  */
/************************************************************************/
class CCncMsgHandler : public CInstance  
{
public:
    CCncMsgHandler();
    ~CCncMsgHandler();

    // 实现CInstance中的纯虚方法(线程安全)
    virtual void InstanceEntry(CMessage *const pMsg);
    // 提取缓冲的消息队列(线程安全)
    void PopAllMsg(CCncMsgQueue &cMsgQue);
    // 清空消息队列
    void ClearQueue();
    // 同步消息反馈
    u32 PutSyncAck(const void* pAckBuf=NULL, u16 u16AckSize=0);
public:
    static u32 WM_OSPMESSAGECOMING;
    static u32 WM_OSPSYNCMSGCOMING;
    static u32 WM_REQMTCSTATUS;
	static u32 WM_REQIKEY;
    static CCncMsgHandler* GetMsgHandler() { return s_pMsgHandler; }
protected:
    // 消息缓冲队列及其保护关键区
    CCncMsgQueue       m_cMsgQue;
    CRITICAL_SECTION m_csQueueOspMsg;
private:
    static CCncMsgHandler *s_pMsgHandler;
};

class CCncAppBase
{
public:
    CCncAppBase();
    ~CCncAppBase();
    // 获取当前连接节点的标识(线程安全)
    u32 GetNodeId(){ return m_dwNodeId;}
    // 设置当前连接节点的标识(线程安全)
    void SetNodeId(u32 dwId) { m_dwNodeId = dwId; }
    // 获取当前Osp消息报告窗口
    HWND GetNotifyWindow() { return m_hWndTarget;}
    // 设置当前Osp消息报告窗口
    void SetNotifyWindow(HWND hWnd) { m_hWndTarget = hWnd; }
    //清空消息队列
    void ClearOspMsg();
protected:
    u32                     m_dwNodeId;     // 当前建立连接的节点标识
    HWND                    m_hWndTarget;   // 收到Osp消息后向此窗口报告
};

/************************************************************************/
/*                        地址簿实例定义                                */
/************************************************************************/
class CAddrMsgHandler : public CInstance  
{
public:
    CAddrMsgHandler();
    ~CAddrMsgHandler();
	
    // 实现CInstance中的纯虚方法(线程安全)
    virtual void InstanceEntry(CMessage *const pMsg);
    // 提取缓冲的消息队列(线程安全)
    void PopAllMsg(CCncMsgQueue &cMsgQue);
    // 清空消息队列
    void ClearQueue();

    static CAddrMsgHandler* GetMsgHandler() { return s_pAddrMsgHandler; }
protected:
    // 消息缓冲队列及其保护关键区
    CCncMsgQueue       m_cMsgQue;
    CRITICAL_SECTION   m_csQueueOspMsg;
private:
    static CAddrMsgHandler *s_pAddrMsgHandler;
};


//extern zTemplate<CMsgHandler, INSTANCE_COUNT, COspAppBase> g_OspApp;
extern zTemplate<CCncMsgHandler, INSTANCE_COUNT, CCncAppBase> g_CncApp;

extern zTemplate<CAddrMsgHandler, INSTANCE_COUNT, CCncAppBase> g_AddrBookApp;

#endif // !defined(AFX_OSPMSGRECVER_H__3FB841FA_784C_41CD_AFF4_A6DC381619A8__INCLUDED_)
