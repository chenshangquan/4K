/*=======================================================================
模块名      : CNC控制台
文件名      : addrmsgdriver.cpp
相关文件    : 
文件实现功能: 地址簿消息驱动器
作者        : 
版本        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/7/25   1.0         肖楚然        创建
=======================================================================*/
#include "StdAfx.h"
#include "addrmsgdriver.h"
#include "cncmsgrecver.h"

////////////////////////////////////////////////////////////////////////////
// CMsgDriver

CAddrMsgDriver* CAddrMsgDriver::s_pMsgDriver = NULL;

CAddrMsgDriver::CAddrMsgDriver()
{
    // 构造事件名称表
    //MappingEventName();
    // 创建消息接收窗口
    m_hWndOsp = ::CreateWindowEx(0, _T("Static"), _T("AddrMsgDriver"), WS_DISABLED,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, 0, 0);

	if ( m_hWndOsp != NULL )
	{
		m_wndprocOld = reinterpret_cast<WNDPROC>(GetWindowLong(m_hWndOsp, GWL_WNDPROC));
		SetWindowLong(m_hWndOsp, GWL_WNDPROC, reinterpret_cast<s32>(WndProc));
	} 
	else
	{
		m_wndprocOld = NULL;
	}
    m_nTimer = 0;
    m_pCurDispEvent = NULL;
    m_wCurSendEvent = 0;
    s_pMsgDriver = this;
}

CAddrMsgDriver::~CAddrMsgDriver()
{
    ::KillTimer(m_hWndOsp, m_nTimer);
    // 关闭消息接收窗口

	::DestroyWindow( m_hWndOsp );
	m_hWndOsp = NULL;
	s_pMsgDriver = NULL;
}


/*=======================================================================
函 数 名:   GetMtMsgPtr
功    能:   得到发送消息指针(发送TKdvMsg)
参    数:   BOOL bClear = TRUE         [in]返回消息指针时是否清空消息体
返 回 值:   发送消息的消息指针
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/09/30  4.0   liuruifei  创建
=======================================================================*/
CTpMsg* CAddrMsgDriver::GetKdvMsgPtr(BOOL32 bClear)
{
    if (bClear) 
    {
        ZeroMemory(&m_cTpMsg, sizeof(CTpMsg));
    }

    return &m_cTpMsg;
}
/*=======================================================================
函 数 名:   GetCMsgPtr
功    能:   得到发送消息指针(发送TMtMsg)
参    数:   BOOL bClear = TRUE         [in]返回消息指针时是否清空消息体
返 回 值:   发送消息的消息指针
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/09/30  4.0   liuruifei  修改
=======================================================================*/
CMessage* CAddrMsgDriver::GetCMsgPtr(BOOL32 bClear /* = TRUE */)
{
	if (bClear)
	{
		ZeroMemory(&m_cMsg, sizeof(CMessage));
	}

	return &m_cMsg;
}

/*=======================================================================
函 数 名:   PostMsg
功    能:   发送命令型消息，不需要终端有回应。调用接口前要要通过GetPostMsgPtr
            来设置消息体
参    数:   u32 dwType = TYPE_CMESSAGE   [in]消息类型TYPE_CMESSAGE或TYPE_MTMSG
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/25  3.5   李洪强  创建
=======================================================================*/
u16 CAddrMsgDriver::PostMsg(u32 dwType)
{  
    u32 dwDesIID = MAKEIID(AID_CN_UE, 1/*m_wInsID*/);	 // 目的：CNS
	u32 dwSrcIID = MAKEIID(AID_CNCADDRBOOK_APP);	         // 源  ：CNS控制台
	
	u16 wRet = NO_ERROR;
	u16 wEvent = 0;
	if (TYPE_TPMSG == dwType) 
	{  
		//发送CMtMsg消息体
		{
			wRet = m_cTpMsg.Post(dwDesIID, g_AddrBookApp.GetNodeId(), dwSrcIID);
		}
		wEvent = m_cTpMsg.GetEvent();
    }
	else
	{
		//发送Osp CMessage消息
		if(m_cMsg.dstid != INVALID_NODE)
		{
			dwDesIID = m_cMsg.dstid;
		}
		if(m_cMsg.srcid != INVALID_NODE)
		{
			dwSrcIID = m_cMsg.srcid;
		}

		wRet = OspPost(dwDesIID, m_cMsg.event, m_cMsg.content, m_cMsg.length,
        g_AddrBookApp.GetNodeId(), dwSrcIID);

		wEvent = m_cMsg.event;
	}
	//打印输出   
	if(wRet == NO_ERROR)
	{  
		if( IS_PRINT_OUT_MSG )
		{
			CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(wEvent);
	        PrtMsg( "[CncLib]: 发送消息:%s(%u).\n", strEvent,wEvent);
		}
	}
	else
	{   
		CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(wEvent);
	    PrtMsg( "[CncLib]: 发送消息:%s(%u)失败,错误码：%d\n", strEvent, wEvent, wRet ); 
	}
	
    return wRet;
}



/*=======================================================================
函 数 名:   PostCommand
功    能:   发送请求型消息，一般会需要终端有回应，如无回应则报超时。调用接口前
要通过GetPostMsgPtr来设置消息体
参    数:   CDispEvent *pDispEvent     [in]响应消息的处理指针
u16 *pwWaitEvent           [in]期待响应的消息数组
s32 nEventNum = 1          [in]期待响应的消息数量
u32 dwTimeOut = 1000       [in]期待响应的消息超时时间
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/25  3.5   李洪强  创建
=======================================================================*/
u16 CAddrMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 *pwWaitEvent,
                            s32 nEventNum, u32 dwType, u32 dwTimeOut)
{
    // 检测是否有前一个命令正在执行中
    if(IsHandleCmd())
    {
        m_cCommandQueue.PushCommand(m_cMsg, m_cTpMsg, pDispEvent, pwWaitEvent,
                                    nEventNum, dwType, dwTimeOut);

        return ERR_CNC_WAIT_FOR_SEND_CMD;
    }
    // 保存当前命令参数
    if(TYPE_CMESSAGE == dwType)
    {
        m_wCurSendEvent = m_cMsg.event;
    }
    else
    {
        m_wCurSendEvent = m_cTpMsg.GetEvent();
    }
    m_pCurDispEvent = pDispEvent;
    
    for(s32 nIndex = 0; nIndex < nEventNum; nIndex++)
    {
        m_vWaitingEvents.push_back(pwWaitEvent[nIndex]);
    }
    // 超时计时器
    m_nTimer = SetTimer(m_hWndOsp, 1, dwTimeOut, NULL);
    // 发送
    u16 wRet = PostMsg(dwType);
    if(wRet != NO_ERROR)
    {
        // 发送失败
        ::KillTimer(m_hWndOsp, m_nTimer);
        ClearWaiting();
        PostNextCommand();
    }
    return wRet;
}

/*=======================================================================
函 数 名:   PostCommand
功    能:   发送请求型消息，一般会需要终端有回应，如无回应则报超时。调用接口前
            要要通过GetPostMsgPtr来设置消息体（单个等待消息）
参    数:   CDispEvent *pDispEvent     [in]响应消息的处理指针
            u16 wWaitEvent             [in]期待响应的消息
            u32 dwTimeOut = 1000       [in]期待响应的消息超时时间
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/25  3.5   李洪强  创建
2004/10/28  3.5   王慧琛   修改
=======================================================================*/
u16 CAddrMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 wWaitEvent, u32 dwType, u32 dwTimeOut)
{
    return PostCommand(pDispEvent, &wWaitEvent, 1, dwType, dwTimeOut);
}


/*=======================================================================
函 数 名:   RegHandler
功    能:   注册一个处理消息的类的指针
参    数:   CDispEvent* const pDispEvnet       [in]处理消息的类指针
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
void CAddrMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
{
    m_vpDispEvent.push_back(pDispEvnet);
}

/*=======================================================================
函 数 名:   RegHandler
功    能:   注销一个处理消息的类的指针
参    数:   CDispEvent* const pDispEvnet       [in]处理消息的类指针
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
void CAddrMsgDriver::UnregHandler(CKdvDispEvent* const pDispEvnet)
{
    vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
    for(; itr != m_vpDispEvent.end(); itr++)
    {
        if (*itr == pDispEvnet) 
        {
            m_vpDispEvent.erase(itr);
            break;
        }
    }
}

/*=======================================================================
函 数 名:   ClearHandler
功    能:   清空所有注册的类的指针
参    数:
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
void CAddrMsgDriver::ClearHandler()
{
    m_vpDispEvent.clear();
}

void CAddrMsgDriver::ClearAllCommand()
{
    m_cCommandQueue.ClearCommand();
}

/*=============================================================================
  函 数 名： OnOspMessageComing
  功    能： 从OSP回调线程提取消息，打印消息分发消息
  算法实现： 
  全局变量： 
  参    数： WPARAM wParam  0
             LPARAM lParam  0
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
void CAddrMsgDriver::OnOspMessageComing(WPARAM wParam, LPARAM lParam)
{
    // 从OSP回调线程提取消息
    CAddrMsgHandler *pHandler = CAddrMsgHandler::GetMsgHandler();
    if (!pHandler) 
    {
        return;
    }
    CCncMsgQueue cMsgQue;
    pHandler->PopAllMsg(cMsgQue);
    // 分发消息
    while(!cMsgQue.IsEmpty())
    {
        const CMessage &cMsg = cMsgQue.Front();

		//打印输出
		CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(cMsg.event);
		if( IS_PRINT_OUT_MSG )
		{   	 
			PrtMsg( "[CncLib]: 收到消息:%s(%u).\n", strEvent,cMsg.event);
		}

        // 检索命令应答消息
        if(IsHandleCmd())
        {	
            vector<u16>::iterator itr = m_vWaitingEvents.begin();
            for(; itr != m_vWaitingEvents.end(); itr++)
            {
                if(*itr == cMsg.event)
                {
                    // 2004/08/24 李洪强 得到回应，清除定时器
                    ::KillTimer(m_hWndOsp, m_nTimer);
                    ClearWaiting();
                    PostNextCommand();
                    break;
                }
            }
        }
        // 检索消息分发表
        vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
        BOOL bFind = FALSE;
        for(; itr != m_vpDispEvent.end(); itr++)
        {
            if ((*itr)->HasRegEvent(cMsg.event)) 
            {
                (*itr)->DispEvent(cMsg);
                bFind = TRUE;
            }
        }
        if (!bFind) 
        {	  	 
			PrtMsg( "[CncLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n", strEvent, cMsg.event);		
        }

        cMsgQue.Pop();
    }
}

/*=============================================================================
  函 数 名： OnOspSyncMsgComing
  功    能： 同步消息处理
  算法实现： 
  全局变量： 
  参    数： WPARAM wParam 消息指针
             LPARAM lParam 0
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/11/30     3.5		    王慧琛                   创建
=============================================================================*/
void CAddrMsgDriver::OnOspSyncMsgComing(WPARAM wParam, LPARAM lParam)
{    
    CMessage *pMsg = (CMessage *)wParam;
   
	//打印输出
	CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(pMsg->event);
	if( IS_PRINT_OUT_MSG )
	{   	 
		PrtMsg( "[CncLib]: 收到消息:%s(%u).\n", strEvent, pMsg->event);
	}

    // 检索消息分发表
    vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
    BOOL bFind = FALSE;
    for(; itr != m_vpDispEvent.end(); itr++)
    {
        if ((*itr)->HasRegEvent(pMsg->event)) 
        {
            (*itr)->DispEvent(*pMsg);
            bFind = TRUE;
        }
    }
    if (!bFind) 
    {
		PrtMsg( "[CncLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n", strEvent, pMsg->event);
    }

}

/*=============================================================================
  函 数 名： OnTimer
  功    能： 超时计时器消息，等待的消息超时回应，清空等待消息数组
  算法实现： 
  全局变量： 
  参    数： WPARAM wParam
             LPARAM lParam
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
void CAddrMsgDriver::OnTimer(WPARAM wParam, LPARAM lParam)
{
    if (wParam == m_nTimer)
    {
        // 超时计时器消息
        ::KillTimer(m_hWndOsp, m_nTimer);
        if(IsHandleCmd())
        {
            if (m_pCurDispEvent) 
            {
                m_pCurDispEvent->OnTimeOut(m_wCurSendEvent);
            }
            ClearWaiting();
            PostNextCommand();
        }
    }
    
}

/*=============================================================================
  函 数 名： WndProc
  功    能： 自定义的窗口处理函数，来区分windows消息和OSP消息以及超时消息
  算法实现： 
  全局变量： 
  参    数： HWND hWnd
             UINT uMsg
             WPARAM wParam
             LPARAM lParam
  返 回 值： LRESULT CALLBACK 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
LRESULT CALLBACK CAddrMsgDriver::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // 拦截OSP消息和超时计时器消息
    if (CAddrMsgDriver::s_pMsgDriver) 
    {
        if (uMsg == CCncMsgHandler::WM_OSPMESSAGECOMING) 
        {
            CAddrMsgDriver::s_pMsgDriver->OnOspMessageComing(wParam, lParam);
        }
        else if (uMsg == CCncMsgHandler::WM_OSPSYNCMSGCOMING)
        {
            CAddrMsgDriver::s_pMsgDriver->OnOspSyncMsgComing(wParam, lParam);            
        }
        else if (uMsg == WM_TIMER) 
        {
            CAddrMsgDriver::s_pMsgDriver->OnTimer(wParam, lParam);
        }
        else
        {
			if ( CAddrMsgDriver::s_pMsgDriver->m_wndprocOld != NULL )
			{
				return CallWindowProc(CAddrMsgDriver::s_pMsgDriver->m_wndprocOld,
                                hWnd, uMsg, wParam, lParam);
			}
            
        }
    }
    return 0;
}

/*=============================================================================
  函 数 名： ClearWaiting
  功    能： 清空等待消息数组，以便调用IsHandleCmd时为FALSE，使消息得以继续发送
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
void CAddrMsgDriver::ClearWaiting()
{
    m_vWaitingEvents.clear();
    m_pCurDispEvent = NULL;
    m_wCurSendEvent = 0;
}

void CAddrMsgDriver::PostNextCommand()
{
    ClearWaiting();

    // 没有待发送消息时直接返回
    if(TRUE == m_cCommandQueue.IsEmpty())
    {
        return;
    }

    // 取出下一条待发送的命令
    TCOMMAND tCommand;
    BOOL32 bSucess = m_cCommandQueue.GetNextCommand(tCommand);
    if(FALSE == bSucess)
    {
        return;
    }
    
    u16* pwWaitEvent = new u16[tCommand.m_nEventNum];

    ASSERT(tCommand.m_nEventNum == tCommand.m_vctWaitEvent.size());
    
    for(u32 nIndex = 0; nIndex < tCommand.m_nEventNum; nIndex++)
    {
        pwWaitEvent[nIndex] = tCommand.m_vctWaitEvent[nIndex];
    }

    if(TYPE_CMESSAGE == tCommand.m_dwType)
    {
        m_cMsg = tCommand.m_cMsg;
    }
    else
    {
        m_cTpMsg = tCommand.m_cMtMsg;
    }

    // 将该条命令发送出去
    PostCommand(tCommand.m_pCDispEvent, pwWaitEvent, tCommand.m_nEventNum,
                tCommand.m_dwType, tCommand.m_dwTimeout);

    delete []pwWaitEvent;
}

