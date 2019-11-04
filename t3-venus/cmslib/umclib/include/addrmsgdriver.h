/*=======================================================================
模块名      : CNC控制台
文件名      : addrmsgdriver.h
相关文件    : 
文件实现功能: 地址簿消息驱动器
作者        : 
版本        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容

=======================================================================*/
#ifndef ADDRMSGDRIVER_H
#define ADDRMSGDRIVER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include "kdvdispevent.h"
#include "tpmsg.h"                       //发送信息的消息结构
#include "CommandQueue.h"

using namespace std;


class CAddrMsgDriver
{
public:
    CAddrMsgDriver();
    ~CAddrMsgDriver();
    // 获取内嵌的窗口句柄
    HWND GetOspRecvWindow(){ return m_hWndOsp;};
    // 得到发送消息指针
    CMessage* GetCMsgPtr(BOOL32 bClear = TRUE);
	// 得到发送终端消息的指针
	CTpMsg* GetKdvMsgPtr(BOOL32 bClear = TRUE);
    // 发送命令型消息 可发送普通CMessage或CMtMsg类型的消息
    virtual u16 PostMsg(u32 dwType = TYPE_CMESSAGE);
    // 发送请求型消息, 期待多个响应
    u16 PostCommand(CKdvDispEvent *pDispEvent, u16 *pwWaitEvent, s32 nEventNum = 1, 
        u32 dwType = TYPE_CMESSAGE, u32 dwTimeOut = 1500);
    // 发送请求型消息，期待单个响应
    u16 PostCommand(CKdvDispEvent *pDispEvent, u16 wWaitEvent, u32 dwType = TYPE_CMESSAGE, u32 dwTimeOut = 1500);
    // 注册一个处理消息的类的指针
    void RegHandler(CKdvDispEvent* const pDispEvnet);
    // 注销一个处理消息的类的指针
    void UnregHandler(CKdvDispEvent* const pDispEvnet);
    // 清空所有注册的类的指针
    void ClearHandler();
    // 清空所有命令消息队列
    void ClearAllCommand();

public:
    static CAddrMsgDriver *s_pMsgDriver;

	// 响应WM_OSPMESSAGECOMING消息
    void OnOspMessageComing(WPARAM wParam, LPARAM lParam);

protected:

    // 响应WM_OSPSYNCMSGCOMING消息
	void OnOspSyncMsgComing(WPARAM wParam, LPARAM lParam);
    // 响应WM_TIMER消息
    void OnTimer(WPARAM wParam, LPARAM lParam);
    // 清空等待的消息
    void ClearWaiting();
    // 缺省超时消息处理方法
    virtual void OnTimeOut(u16 wEvent){ return; }
    // 当一条命令发送完成后，发送下一条命令
    void PostNextCommand();

    CTpMsg       m_cTpMsg;              //用于发送TP消息的消息结构
	CMessage	 m_cMsg;				//用于发送其他消息的消息结构

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    // 是否正在处理命令
    BOOL IsHandleCmd() const { return !m_vWaitingEvents.empty(); }
    HWND            m_hWndOsp;          // 内嵌接收消息的窗口
    WNDPROC         m_wndprocOld;       // 系统窗口过程
    vector<CKdvDispEvent*> m_vpDispEvent;  // 消息分发表
    vector<u16>     m_vWaitingEvents;	// 正在等待应答的消息
    CKdvDispEvent  *m_pCurDispEvent;    // 正在处理的消息对应的响应类的指针
    u16             m_wCurSendEvent;    // 当前发送出去的消息
    s32             m_nTimer;

protected:
    CCommandQueue       m_cCommandQueue;        // 命令缓冲队列
};


#endif //ADDRMSGDRIVER_H
