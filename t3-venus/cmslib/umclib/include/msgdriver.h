/*=======================================================================
模块名      : 终端控制台
文件名      : MsgDriver.h
相关文件    : 
文件实现功能: 消息驱动器
作者        : 熊广化
版本        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/12/22  3.0         熊广化      创建
2003/03/02	3.0			熊广化		化简
2004/08/23  3.5         李洪强      规范代码，增加CDispEvent类
=======================================================================*/
#ifndef MSGDRIVER_H
#define MSGDRIVER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include "kdvdispevent.h"
#include "tpmsg.h"                       //发送信息的消息结构
#include "CommandQueue.h"

using namespace std;

#define MTC_TRANSFILETIMER 99
#define MTC_TRANSFILE_INTERVAL 300
#define MTC_TRANSFILE_SIZE		16 * 1024


//#define ev_mcViewPollCmd	9999 //临时加以下
//#define ev_mcViewPollInd	9998//临时加以下
// #define ev_CodecVideoEncDecResInd 9997//临时加以下
class CMsgDriver
{
public:
    CMsgDriver();
    ~CMsgDriver();
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

	void SetSndInstID( u32 dwDstInstID );
	u32  GetSndInstID();

	void SetAppID( u32 dwAppID ){ m_dwAppID = dwAppID;};
	u32  GetAppID(){ return m_dwAppID;};

public:
    static CMsgDriver *s_pMsgDriver;

protected:
    // 响应WM_OSPMESSAGECOMING消息
    void OnOspMessageComing(WPARAM wParam, LPARAM lParam);
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

    CTpMsg       m_cKdvMsg;             // 用于发送 tp消息的消息结构
	CMessage	 m_cMsg;				//用于发送其他非终端消息的消息结构
    //状态打印
    virtual void Dump() {return;};
	virtual void ReqIKey(u8 byLocal) {return;};
private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    // 是否正在处理命令
    BOOL IsHandleCmd() const { return !m_vWaitingEvents.empty(); }
    HWND            m_hWndOsp;          // 内嵌接收消息的窗口
    WNDPROC         m_wndprocOld;       // 系统窗口过程
    vector<CKdvDispEvent*> m_vpDispEvent;  // 消息分发表
    vector<u16>     m_vWaitingEvents;	// 正在等待应答的消息
    CKdvDispEvent      *m_pCurDispEvent;   // 正在处理的消息对应的响应类的指针
    u16             m_wCurSendEvent;       // 当前发送出去的消息
    s32             m_nTimer;
	u32             m_dwInstID;             //实例ID
	u32             m_dwAppID;
    // 消息分类映射表
    enum CATALOG{
        DEFAULT = 0,
        MULTI_CONF,
        P2P,
        AUD,
        VID,
        CAMERA,
        CFG,
        ADDR,
        MATRIX,
        REMOTECTRL,
        USERMANAGE,
        MISC,
		VOD,
		FXO,
		LOG
    };
    void MappingHelper(u16 wEvent, const CString& strName, CATALOG catalog = DEFAULT);
    void MappingEventName();
    BOOL CanBeTraceOut(u16 wEvent) const;       // 信息输出裁判
protected:
    CCommandQueue       m_cCommandQueue;        // 命令缓冲队列
    map<u16, u32>       m_mapEventType;         // 消息分类映射表
    map<u16, CString>   m_mapEventsName;        // 消息名称映射表
    u8*                 m_pbyFile;              // 文件内存块指针
    u32                 m_dwFileLength;         // 文件长度
    u32                 m_dwFileCurPos;         // 文件当前位置 
    u32                 m_dwFileFragIndex;      // 文件块序号
    u8                  m_byTransferStatus;     // 文件传输状态
    s32                 m_nFileTransferTimer;   // 文件传输定时器
    u16                 m_wFileType;            // 文件类型
    u32                 m_dwTimeOut;            // 超时时间
	u16					m_wMaxPackageLen;		// 包最大长度
    //传输状态
    enum TRANSFERSTATUS{
        FREE = 0,   //空闲
        READY,      //准备
        BUSY,       //传输中
    };
    
protected:
    // 大型文件传输接口
    /*函数名： TransferFile
    功    能： 传输文件接口, 开启定时器
    参    数： 
    返 回 值： u16 
    说    明： */
    u16 TransferFile();
	
    void StopTransferFile();

    /*函数名： PostFile
    功    能： 发送文件段
    参    数： u8 *pbyBuf      文件段指针
               u32 dwBufLenth  文件段长度
               u32 nIndex      文件段序号
    返 回 值： u16 
    说    明： */
    u16 PostFile(u8 *pbyBuf, u32 dwBufLenth, u32 nIndex);
    virtual void EndTransFile(){return;}
};


#endif //MSGDRIVER_H
