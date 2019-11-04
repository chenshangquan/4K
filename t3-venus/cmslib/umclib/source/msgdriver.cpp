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
#include "StdAfx.h"

#include "MsgDriver.h"
#include "OspMsgRecver.h"
#include "eventoutumsconftemplate.h"
#include "eventoutumscall.h"
#include "eventoutumscfg.h"
//#include "umshduevent.h"
#include "eventoutumsreg.h"
#include "umclib.h"
////////////////////////////////////////////////////////////////////////////
// CMsgDriver

CMsgDriver* CMsgDriver::s_pMsgDriver = NULL;

CMsgDriver::CMsgDriver()
           :m_dwInstID(1) 
{
    // 构造事件名称表
    MappingEventName();
    // 创建消息接收窗口
    m_hWndOsp = ::CreateWindowEx(0, _T("Static"), _T("MsgDriver"), WS_DISABLED,
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
    m_byTransferStatus = FREE;
    m_pbyFile = NULL;
    m_dwFileLength = 0;         // 文件长度
    m_dwFileFragIndex = 0;      // 文件块序号
    m_dwFileCurPos = 0;
}

CMsgDriver::~CMsgDriver()
{
    if (m_pbyFile != NULL)
    {
        free(m_pbyFile);
        m_pbyFile = NULL;
    }
    ::KillTimer(m_hWndOsp, m_nTimer);
    // 关闭消息接收窗口

	::DestroyWindow( m_hWndOsp );
	m_hWndOsp = NULL;
	s_pMsgDriver = NULL;
}


/*=======================================================================
函 数 名:   GetMtMsgPtr
功    能:   得到发送消息指针(发送TMtMsg)
参    数:   BOOL bClear = TRUE         [in]返回消息指针时是否清空消息体
返 回 值:   发送消息的消息指针
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/09/30  4.0   liuruifei  创建
=======================================================================*/
CTpMsg* CMsgDriver::GetKdvMsgPtr(BOOL32 bClear)
{
    if (bClear) 
    {
        ZeroMemory(&m_cKdvMsg, sizeof(CTpMsg));
    }

    return &m_cKdvMsg;
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
CMessage* CMsgDriver::GetCMsgPtr(BOOL32 bClear /* = TRUE */)
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
u16 CMsgDriver::PostMsg(u32 dwType)
{   
    u32 dwDesIID = MAKEIID(AID_UMSUE_APP, 1/*m_dwInstID*/ );		// 目的：UMS
	u32 dwSrcIID = MAKEIID(GetAppID());	// 源  ：终端控制台
	
	u16 wRet = NO_ERROR;
	u16 wEvent = 0;
	if (TYPE_TPMSG == dwType) 
	{  
		//发送CMtMsg消息体
		{
			wRet = m_cKdvMsg.Post(dwDesIID, g_UmcLibApp.GetNodeId(), dwSrcIID);
		}
		wEvent = m_cKdvMsg.GetEvent();
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
        g_UmcLibApp.GetNodeId(), dwSrcIID);

		wEvent = m_cMsg.event;
	}
	//打印输出
    CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(wEvent);
	if(wRet == NO_ERROR)
	{  
		if( IS_PRINT_OUT_MSG )
		{   	 
	        PrtMsg( "[UmcLib]: 发送消息:%s(%u).\n", strEvent,wEvent);
		}
	}
	else
	{    
	     PrtMsg( "[UmcLib]: 发送消息:%s(%du)失败,错误码：%d\n", strEvent,wEvent,wRet); 
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
u16 CMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 *pwWaitEvent,
                            s32 nEventNum, u32 dwType, u32 dwTimeOut)
{
    // 检测是否有前一个命令正在执行中
    if(IsHandleCmd())
    {
        m_cCommandQueue.PushCommand(m_cMsg, m_cKdvMsg, pDispEvent, pwWaitEvent,
                                    nEventNum, dwType, dwTimeOut);

        return ERR_UMC_WAIT_FOR_SEND_CMD;
    }
    // 保存当前命令参数
    if(TYPE_CMESSAGE == dwType)
    {
        m_wCurSendEvent = m_cMsg.event;
    }
    else
    {
        m_wCurSendEvent = m_cKdvMsg.GetEvent();
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
u16 CMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 wWaitEvent, u32 dwType, u32 dwTimeOut)
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
void CMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
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
void CMsgDriver::UnregHandler(CKdvDispEvent* const pDispEvnet)
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
void CMsgDriver::ClearHandler()
{
    m_vpDispEvent.clear();
}

void CMsgDriver::ClearAllCommand()
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
void CMsgDriver::OnOspMessageComing(WPARAM wParam, LPARAM lParam)
{
    // 从OSP回调线程提取消息
    CMsgHandler *pHandler = CMsgHandler::GetMsgHandler();
    if (!pHandler) 
    {
        return;
    }
    CMsgQueue cMsgQue;
    pHandler->PopAllMsg(cMsgQue);
    // 分发消息
    while(!cMsgQue.IsEmpty())
    {
        const CMessage &cMsg = cMsgQue.Front();

		//打印输出
		CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(cMsg.event);
	 	if( IS_PRINT_OUT_MSG )
		{   	 
			PrtMsg( "[UmcLib]: 收到消息:%s(%u).\n", strEvent,cMsg.event);
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
            // 没有注册处理函数的消息
            map<u16, CString>::iterator itrName = m_mapEventsName.find(cMsg.event);
            if(itrName != m_mapEventsName.end())
            {
                OspLog(1, "[UmcLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n",
                    (LPCTSTR)((*itrName).second), cMsg.event);

				TRACE("[UmcLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n",
                    (LPCTSTR)((*itrName).second), cMsg.event);
            }
            else
            {
                OspLog(1, "[UmcLib]: 消息:%d被抛弃,因为没有找到匹配的消息处理器.\n",
                    cMsg.event);
				TRACE("[UmcLib]: 消息:%d被抛弃,因为没有找到匹配的消息处理器.\n",
                    cMsg.event);
            }
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
void CMsgDriver::OnOspSyncMsgComing(WPARAM wParam, LPARAM lParam)
{    
    CMessage *pMsg = (CMessage *)wParam;
   
    map<u16, CString>::iterator itrName = m_mapEventsName.find(pMsg->event);
    if(itrName != m_mapEventsName.end())
    {
        OspLog(2, "[UmcLib]: 收到消息:%s(%d)\n", (LPCTSTR)((*itrName).second), pMsg->event);
        TRACE("[UmcLib]: 收到消息:%s(%d)\n", (LPCTSTR)((*itrName).second), pMsg->event);
    }
    else
    {
        OspLog(2, "[UmcLib: 收到消息:%d.\n", pMsg->event);
        TRACE("[UmcLib]: 收到消息:%d.\n", pMsg->event);
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
        // 没有注册处理函数的消息
        map<u16, CString>::iterator itrName = m_mapEventsName.find(pMsg->event);
        if(itrName != m_mapEventsName.end())
        {
            OspLog(1, "[UmcLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n",
                (LPCTSTR)((*itrName).second), pMsg->event);
        }
        else
        {
            OspLog(1, "[UmcLib]: 消息:%d被抛弃,因为没有找到匹配的消息处理器.\n",
                pMsg->event);
        }
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
void CMsgDriver::OnTimer(WPARAM wParam, LPARAM lParam)
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
	//发送文件超时,复位,即重头开始重新发送
    else if (wParam == m_nFileTransferTimer)
    {
        if (m_pbyFile == NULL)
        {
            EndTransFile();
            ::KillTimer(m_hWndOsp, m_nFileTransferTimer);
            return;
        }
        if (m_dwFileCurPos < m_dwFileLength)
        //未传送完文件，继续传送，每包30K字节
        {
            u32 dwLeft = m_dwFileLength - m_dwFileCurPos;
            if (dwLeft > 1024*30)
            {
                dwLeft = 1024*30;
            }
            PostFile(&m_pbyFile[m_dwFileCurPos], dwLeft, m_dwFileFragIndex);
            m_dwFileCurPos = m_dwFileCurPos + 1024 * 30;
            m_dwFileFragIndex++;
        }
        //传送完文件，发送停止传送请求
        else
        {
            if (m_pbyFile != NULL)
            {
                free(m_pbyFile);
                m_pbyFile = NULL;
            }
            m_dwFileCurPos = 0;
            m_dwFileFragIndex = 0;
            EndTransFile();
            ::KillTimer(m_hWndOsp, m_nFileTransferTimer);
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
LRESULT CALLBACK CMsgDriver::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // 拦截OSP消息和超时计时器消息
    if (CMsgDriver::s_pMsgDriver) 
    {
        if (uMsg == CMsgHandler::WM_OSPMESSAGECOMING) 
        {
            CMsgDriver::s_pMsgDriver->OnOspMessageComing(wParam, lParam);
        }
        else if (uMsg == CMsgHandler::WM_OSPSYNCMSGCOMING)
        {
            CMsgDriver::s_pMsgDriver->OnOspSyncMsgComing(wParam, lParam);            
        }
        else if (uMsg == WM_TIMER) 
        {
            CMsgDriver::s_pMsgDriver->OnTimer(wParam, lParam);
        }
        else if (uMsg == CMsgHandler::WM_REQMTCSTATUS)
        {
            CMsgDriver::s_pMsgDriver->Dump();
        }
		else if (uMsg == CMsgHandler::WM_REQIKEY)
		{
			CMsgDriver::s_pMsgDriver->ReqIKey(wParam);
		}
        else
        {
			if ( CMsgDriver::s_pMsgDriver->m_wndprocOld != NULL )
			{
				return CallWindowProc(CMsgDriver::s_pMsgDriver->m_wndprocOld,
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
void CMsgDriver::ClearWaiting()
{
    m_vWaitingEvents.clear();
    m_pCurDispEvent = NULL;
    m_wCurSendEvent = 0;
}

void CMsgDriver::PostNextCommand()
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
        m_cKdvMsg = tCommand.m_cMtMsg;
    }

    // 将该条命令发送出去
    PostCommand(tCommand.m_pCDispEvent, pwWaitEvent, tCommand.m_nEventNum,
                tCommand.m_dwType, tCommand.m_dwTimeout);

    delete []pwWaitEvent;
}

/*=============================================================================
  函 数 名： CanBeTraceOut
  功    能： 信息输出裁判，判断改事件是否需要输出打印
  算法实现： 
  全局变量： 
  参    数： u16 wEvent  需要判断的事件ID
  返 回 值： BOOL        TRUE需要输出打印
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
BOOL CMsgDriver::CanBeTraceOut(u16 wEvent) const
{
	//yjj
//    static u32 dwSN = 0;
//    static u32 dwCatalog[MTC_MSGCATALOG_COUNT];
//   //yjj CMtcLib::GetTraceStatus(dwSN, dwCatalog);
//    
//    map<u16, u32>::const_iterator itr = m_mapEventType.find(wEvent);
//    if(itr != m_mapEventType.end())
//    {
//        return dwCatalog[itr->second];
//    }
//    else
//    {
//        return dwCatalog[0];
//    }

	return TRUE;
}

/*=============================================================================
  函 数 名： TransferFile
  功    能： 开启发送定时器
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： u16 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/12/27     3.5		    王慧琛                   创建
=============================================================================*/
u16 CMsgDriver::TransferFile()
{
    if (m_pbyFile == NULL) return 1;
    //先发送第一包
    m_dwFileCurPos = 0;
    m_dwFileFragIndex = 0;
	u16 wResult = 0;
    if (m_dwFileCurPos < m_dwFileLength)
    {
        u32 dwLeft = m_dwFileLength - m_dwFileCurPos;
        if (dwLeft > m_wMaxPackageLen)
        {
            dwLeft = m_wMaxPackageLen;
        }
		TRACE("\n开始传输文件");
        wResult = PostFile(&m_pbyFile[m_dwFileCurPos], dwLeft, m_dwFileFragIndex);
        m_dwFileCurPos = m_dwFileCurPos + m_wMaxPackageLen;
        m_dwFileFragIndex++;
    }

	return wResult;
}

void CMsgDriver::StopTransferFile()
{
    m_byTransferStatus = FREE;
	if (m_pbyFile != NULL)
    {
        free(m_pbyFile);
        m_pbyFile = NULL;
    }
    
}

/*函数名： PostFile
功    能： 发送文件段
参    数： u8 *pbyBuf      文件段指针
           u32 dwBufLenth  文件段长度
           u32 nIndex      文件段序号
返 回 值： u16 
说    明： */
u16 CMsgDriver::PostFile(u8 *pbyBuf, u32 dwBufLenth, u32 nIndex)
{
    //包头必须附带：传输协议版本号，文件标识符，文件类型，文件分片号，包长度。
	//包体：文件数据
//    ZeroMemory(&m_cMtMsg, sizeof(CKdvMsg));
//    //传输文件
//    TFileTransfer tMsgHead;
//    memset( &tMsgHead, 0, sizeof (tMsgHead) );
//	tMsgHead.wProtocolIdentifer = MTC_MT_FILE_VER;
//	tMsgHead.wFileSliceNo = MTC_MT_MSG_BGN + nIndex;
//	tMsgHead.byType = m_wFileType;
//	tMsgHead.wDataLen = dwBufLenth + sizeof(TFileTransfer);
//
//	//设置消息体
////	m_cMtMsg.SetEvent(ev_FTSendFileCmd);
//	m_cMtMsg.SetBody(&tMsgHead, sizeof( TFileTransfer ));
//	m_cMtMsg.CatBody( pbyBuf, dwBufLenth );
// 
////	OspPrintf(TRUE, FALSE, "传送的数据长度%d\n", dwBufLenth);
//	TRACE("传送的数据长度%d\n", dwBufLenth);
//
//    u16 wResult = PostMsg(TYPE_KDVMSG);
    
    return NO_ERROR;//wResult;
}

/*=============================================================================
  函 数 名： MappingHelper
  功    能： 映射事件名称，同时注册到事件类别数组里面
  算法实现： 
  全局变量： 
  参    数： u16 wEvent                 事件ID
             const CString& strName     事件名称
             CATALOG catalog            类别
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgDriver::MappingHelper(u16 wEvent, const CString& strName, CATALOG catalog)
{
    m_mapEventsName[wEvent] = strName;
    m_mapEventType[wEvent] = catalog;
}

/*=============================================================================
  函 数 名： MappingEventName
  功    能： 注册事件
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgDriver::MappingEventName()
{   

    
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UmsLoginByOther_Notify, _T("ev_UmsLoginByOther_Notify"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_UmsCommonReasonToUI_Ind, _T("evtp_UmsCommonReasonToUI_Ind"));
	
    	//用户相关
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UMSLoginReq, _T("ev_UMLoginReq"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UMSLoginRet, _T("ev_UMSLoginRet"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UMSAddUserReq, _T("ev_UMSAddUserReq"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UMSAddUserRet, _T("ev_UMSAddUserRet"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UMSDelUserReq, _T("ev_UMSDelUserReq"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UMSDelUserRet, _T("ev_UMSDelUserRet"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UMSChangePWDReq, _T("ev_UMSChangePWDReq"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UMSChangePWDRet, _T("ev_UMSChangePWDRet"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UmsAddUser_Notify, _T("ev_UmsAddUser_Notify"), 3 );
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UmsDelUser_Notify, _T("ev_UmsDelUser_Notify"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UmsUpdateUser_Notify, _T("ev_UmsUpdateUser_Notify"));

	//会议模板相关
	CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_AddConfTemplate_req, _T("evtp_AddConfTemplate_req") );
	CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_DelConftemplate_Req, _T("evtp_DelConftemplate_Req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_Updateconftemplate_Req, _T("evtp_Updateconftemplate_Req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(evpt_OperatorConfTemplate_Ret, _T("evpt_OperatorConfTemplate_Ret"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_AddConftemplate_Notify, _T("evtp_AddConftemplate_Notify"),3 );
	CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_Delconftemplate_Notify, _T("evtp_Delconftemplate_Notify"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_Updateconftemplate_Notify, _T("evtp_Updateconftemplate_Notify"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_StartConfTemplate_Req, _T("evtp_StartConfTemplate_Req"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_StartConfTemplate_Ret, _T("evtp_StartConfTemplate_Ret"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_conf_bas_used_nty, _T("ev_conf_bas_used_nty"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_del_all_conftemp_req, _T("ev_del_all_conftemp_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_del_all_conftemp_rsp, _T("ev_del_all_conftemp_rsp"));

    //会议相关
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_HungUpConf_cmd, _T("evtp_HungUpConf_cmd"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_HungUpConf_result, _T("evtp_HungUpConf_result"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_CallEP_cmd, _T("evtp_CallEP_cmd"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_CallExistEP_cmd, _T("evtp_CallExistEP_cmd")); 
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_CallEP_result, _T("evtp_CallEP_result"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_DropEp_cmd, _T("evtp_DropEp_cmd"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_ApplySpeaker_cmd, _T("evtp_ApplySpeaker_cmd"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_ApplySpeaker_result, _T("evtp_ApplySpeaker_result"));
    //CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_AudMixStatus_Notify, _T("evtp_AudMixStatus_Notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_AddConfList_Notify, _T("evtp_AddConfList_Notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_DelConflist_Notify, _T("evtp_DelConflist_Notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_UpdateConfCnsList_Notify, _T("evtp_UpdateConfCnsList_Notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_AuxMixInfo_Notify, _T("evtp_AuxMixInfo_Notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_UpdateConfTurnlist_Notify, _T("evtp_UpdateConfTurnlist_Notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_SpeakerChange_Notify, _T("evtp_SpeakerChange_Notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_ChairManChange_Notify, _T("evtp_ChairManChange_Notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_UpdateAudMixInfo_cmd, _T("evtp_UpdateAudMixInfo_cmd"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_UpdateTurn_cmd, _T("evtp_UpdateTurn_cmd"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_StartTurn_cmd, _T("evtp_StartTurn_cmd"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_ChairConfInfo_Notify, _T("evtp_ChairConfInfo_Notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_HungUp_Conf_Reason, _T("evtp_HungUp_Conf_Reason"));


   //配置相关
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UmsIPCfg_Ind, _T("ev_UmsIPCfg_Ind"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UmsIPCfg, _T("ev_UmsIPCfg"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_umsreg_cmd, _T("ev_umsreg_cmd"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_umsreg_notify, _T("ev_umsreg_notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_umsRegResult_notify, _T("ev_umsRegResult_notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_umsGKReg_notify, _T("ev_umsGKReg_notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_UmsGetSysTime_Rsp, _T("ev_UmsGetSysTime_Rsp"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_ums_sipreg_state_nty, _T("ev_ums_sipreg_state_nty"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_ums_gkreg_state_nty, _T("ev_ums_gkreg_state_nty"));

	//全局地址簿
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_umsGetRegInfo_Req, _T("ev_umsGetRegInfo_Req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_umsGetRegInfo_Rsp, _T("ev_umsGetRegInfo_Rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_umsGetRegInfo_McuRspEx, _T("ev_umsGetRegInfo_McuRspEx"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_umsGetRegInfo_MtRspEx, _T("ev_umsGetRegInfo_MtRspEx"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_umsGetRegInfo_CnsRspEx, _T("ev_umsGetRegInfo_CnsRspEx"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_umsGetRegInfo_UmsRspEx, _T("ev_umsGetRegInfo_UmsRspEx"));
	
	


    //静音哑音
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_MuteEp_cmd, _T("evtp_MuteEp_cmd"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_MuteEp_Ind, _T("evtp_MuteEp_Ind"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_QuietEp_cmd, _T("evtp_QuietEp_cmd"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_QuietEp_Ind, _T("evtp_QuietEp_Ind"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_StartDual_Cmd, _T("evtp_StartDual_Cmd"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_StartDual_Ind, _T("evtp_StartDual_Ind"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_DualEp_Notify, _T("evtp_DualEp_Notify"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(evtp_StopDual_Cmd, _T("evtp_StopDual_Cmd")); 


    //电视墙  
    /*
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_SysHduEpReg, _T("ev_SysHduEpReg"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_SysHduEpDrop, _T("ev_SysHduEpDrop"));

    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_SysHduPlayReq, _T("ev_SysHduPlayReq"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_SysHduPlayAck, _T("ev_SysHduPlayAck"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_SysHduPlayNAck, _T("ev_SysHduPlayNAck")); 

    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_SysHduStopPlay, _T("ev_SysHduStopPlay"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_SysHduStopPlayAck, _T("ev_SysHduStopPlayAck"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_SysHduStopPlayNAck, _T("ev_SysHduStopPlayNAck")); 

    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_SysHduCallIsValid, _T("ev_SysHduCallIsValid")); 
    */
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduPlan_Nty, _T("ev_hduPlan_Nty")); 
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_HduPlay_Req, _T("ev_HduPlay_Req"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_HduPlay_Ack, _T("ev_HduPlay_Ack"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_HduPlay_NAck, _T("ev_HduPlay_NAck"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_HduCall_Valid, _T("ev_HduCall_Valid"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_HduStopPlay_Req, _T("ev_HduStopPlay_Req"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_HduStopPlay_Ack, _T("ev_HduStopPlay_Ack"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_HduStopPlay_NAck, _T("ev_HduStopPlay_NAck"));       
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_HduAllStopPlay_Req, _T("ev_HduAllStopPlay_Req")); 
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_HduReg_Status_Nty, _T("ev_HduReg_Status_Nty"));
   

	//地址簿
	MAPPING_HELPER( ADDRBOOK_REGISTER_REQ, _T("ADDRBOOK_REGISTER_REQ") );
    MAPPING_HELPER( ADDRBOOK_REGISTER_ACK, _T("ADDRBOOK_REGISTER_ACK") );
    MAPPING_HELPER( ADDRBOOK_REGISTER_NACK, _T("ADDRBOOK_REGISTER_NACK"));
    MAPPING_HELPER( ADDRBOOK_UNREG_REQ, _T("ADDRBOOK_UNREG_REQ") );
	MAPPING_HELPER( ADDRBOOK_UNREG_CMD, _T("ADDRBOOK_UNREG_CMD") );
    MAPPING_HELPER( ADDRBOOK_SAVE_ACK, _T("ADDRBOOK_SAVE_ACK") );
    MAPPING_HELPER( ADDRBOOK_SAVE_NACK, _T("ADDRBOOK_SAVE_NACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRY_REQ, _T("ADDRBOOK_ADD_ENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRY_ACK, _T("ADDRBOOK_ADD_ENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRY_NACK, _T("ADDRBOOK_ADD_ENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_MULSETENTRY_REQ, _T("ADDRBOOK_ADD_MULSETENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_ADD_MULSETENTRY_ACK, _T("ADDRBOOK_ADD_MULSETENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_MULSETENTRY_NACK, _T("ADDRBOOK_ADD_MULSETENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRY_REQ, _T("ADDRBOOK_DEL_ENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRY_ACK, _T("ADDRBOOK_DEL_ENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRY_NACK, _T("ADDRBOOK_DEL_ENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_MULSETENTRY_REQ, _T("ADDRBOOK_DEL_MULSETENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_DEL_MULSETENTRY_ACK, _T("ADDRBOOK_DEL_MULSETENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_MULSETENTRY_NACK, _T("ADDRBOOK_DEL_MULSETENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRYTOMULSET_REQ, _T("ADDRBOOK_ADD_ENTRYTOMULSET_REQ") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRYTOMULSET_ACK, _T("ADDRBOOK_ADD_ENTRYTOMULSET_ACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRYTOMULSET_NACK, _T("ADDRBOOK_ADD_ENTRYTOMULSET_NACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRYFRMULSET_REQ, _T("ADDRBOOK_DEL_ENTRYFRMULSET_REQ") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRYFRMULSET_ACK, _T("ADDRBOOK_DEL_ENTRYFRMULSET_ACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRYFRMULSET_NACK, _T("ADDRBOOK_DEL_ENTRYFRMULSET_NACK") );
    MAPPING_HELPER( ADDRBOOK_MODIFYENTRY_REQ, _T("ADDRBOOK_MODIFYENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_MODIFYENTRY_ACK, _T("ADDRBOOK_MODIFYENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_MODIFYENTRY_NACK, _T("ADDRBOOK_MODIFYENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_MODIFYMULSETENTRY_REQ, _T("ADDRBOOK_MODIFYMULSETENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_MODIFYMULSETENTRY_ACK, _T("ADDRBOOK_MODIFYMULSETENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_MODIFYMULSETENTRY_NACK, _T("ADDRBOOK_MODIFYMULSETENTRY_NACK") );
	MAPPING_HELPER( ADDRBOOK_ADD_MULSETTOMULSET_REQ, _T("ADDRBOOK_ADD_MULSETTOMULSET_REQ") );
	MAPPING_HELPER( ADDRBOOK_ADD_MULSETTOMULSET_ACK, _T("ADDRBOOK_ADD_MULSETTOMULSET_ACK") );
	MAPPING_HELPER( ADDRBOOK_ADD_MULSETTOMULSET_NACK, _T("ADDRBOOK_ADD_MULSETTOMULSET_NACK") );
	MAPPING_HELPER( ADDRBOOK_DEL_MULSETFROMMULSET_REQ, _T("ADDRBOOK_DEL_MULSETFROMMULSET_REQ") );
	MAPPING_HELPER( ADDRBOOK_DEL_MULSETFROMMULSET_ACK, _T("ADDRBOOK_DEL_MULSETFROMMULSET_ACK") );
	MAPPING_HELPER( ADDRBOOK_DEL_MULSETFROMMULSET_NACK, _T("ADDRBOOK_DEL_MULSETFROMMULSET_NACK") );
	
    MAPPING_HELPER( ADDRBOOK_GETENTRYNUM_REQ, _T("ADDRBOOK_GETENTRYNUM_REQ") );
    MAPPING_HELPER( ADDRBOOK_GETENTRYNUM_ACK, _T("ADDRBOOK_GETENTRYNUM_ACK") );
    MAPPING_HELPER( ADDRBOOK_GETENTRYNUM_NACK, _T("ADDRBOOK_GETENTRYNUM_NACK") );
    MAPPING_HELPER( ADDRBOOK_GETENTRY_REQ, _T("ADDRBOOK_GETENTRY_REQ"), 3 );
    MAPPING_HELPER( ADDRBOOK_GETENTRY_ACK, _T("ADDRBOOK_GETENTRY_ACK"), 3 );
    MAPPING_HELPER( ADDRBOOK_GETENTRY_NACK, _T("ADDRBOOK_GETENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRYNUM_REQ, _T("ADDRBOOK_GETMULSETENTRYNUM_REQ") );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRYNUM_ACK, _T("ADDRBOOK_GETMULSETENTRYNUM_ACK") );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRYNUM_NACK, _T("ADDRBOOK_GETMULSETENTRYNUM_NACK") );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRY_REQ, _T("ADDRBOOK_GETMULSETENTRY_REQ"), 3 );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRY_ACK, _T("ADDRBOOK_GETMULSETENTRY_ACK"), 3 );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRY_NACK, _T("ADDRBOOK_GETMULSETENTRY_NACK") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATIONNUM_REQ, _T("ADDRBOOK_GETMULSETRELATIONNUM_REQ") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATIONNUM_ACK, _T("ADDRBOOK_GETMULSETRELATIONNUM_ACK") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATIONNUM_NACK, _T("ADDRBOOK_GETMULSETRELATIONNUM_NACK") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATION_REQ, _T("ADDRBOOK_GETMULSETRELATION_REQ") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATION_ACK, _T("ADDRBOOK_GETMULSETRELATION_ACK") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATION_NACK, _T("ADDRBOOK_GETMULSETRELATION_NACK") );
    MAPPING_HELPER( ADDRBOOK_REFRESHENTRY_NOTIF, _T("ADDRBOOK_REFRESHENTRY_NOTIF") );
    MAPPING_HELPER( ADDRBOOK_DELENTRY_NOTIF, _T("ADDRBOOK_DELENTRY_NOTIF") );
    MAPPING_HELPER( ADDRBOOK_REFRESHMULSETENTRY_NOTIF, _T("ADDRBOOK_REFRESHMULSETENTRY_NOTIF") );
    MAPPING_HELPER( ADDRBOOK_DELMULSETENTRY_NOTIF, _T("ADDRBOOK_DELMULSETENTRY_NOTIF") );
	MAPPING_HELPER( ADDRBOOK_REFRESHMULSETRELATION_NOTIF, _T("ADDRBOOK_REFRESHMULSETRELATION_NOTIF") );	
    MAPPING_HELPER( ADDRBOOK_UPDATEINMT_CMD, _T("ADDRBOOK_UPDATEINMT_CMD") );
    MAPPING_HELPER( ADDRBOOK_UPDATEOUTMT_CMD, _T("ADDRBOOK_UPDATEOUTMT_CMD") );


	//---umstool消息名称映射---
	//ums基本信息
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_sysInfo_req, _T("ev_sysInfo_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_sysInfo_Nty, _T("ev_sysInfo_Nty"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_confCount_req, _T("ev_confCount_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_confCount_Nty, _T("ev_confCount_Nty"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rebootUms_cmd, _T("ev_rebootUms_cmd"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_authCount_req, _T("ev_authCount_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_authCount_Nty, _T("ev_authCount_Nty"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduCount_req, _T("ev_hduCount_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduCount_Nty, _T("ev_hduCount_Nty"));


	//ums单板信息
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardInfo_Nty, _T("ev_cardInfo_Nty"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardModify_req, _T("ev_cardModify_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardModify_rsp, _T("ev_cardModify_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardDel_req, _T("ev_cardDel_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardDel_rsp, _T("ev_cardDel_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardAdd_req, _T("ev_cardAdd_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardAdd_rsp, _T("ev_cardAdd_rsp"));
//	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardModeAdd_req, _T("ev_cardModeAdd_req"));
//	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardModeAdd_rsp, _T("ev_cardModeAdd_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardModeDel_req, _T("ev_cardModeDel_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardModeDel_rsp, _T("ev_cardModeDel_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardModeModify_req, _T("ev_cardModeModify_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_cardModeModify_rsp, _T("ev_cardModeModify_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_card_reboot_req, _T("ev_card_reboot_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_card_audiomix_used_req, _T("ev_card_audiomix_used_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_card_vmp_used_req, _T("ev_card_vmp_used_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_card_bas_used_req, _T("ev_card_bas_used_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_card_used_nty, _T("ev_card_used_nty"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_card_upgrade_req, _T("ev_card_upgrade_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_card_upgrade_res, _T("ev_card_upgrade_res"));

	//ums电视墙单板
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduBrdAdd_req, _T("ev_hduBrdAdd_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduBrdModify_req, _T("ev_hduBrdModify_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduChanAdd_req, _T("ev_hduChanAdd_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduChanModify_req, _T("ev_hduChanModify_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduChanDel_req, _T("ev_hduChanDel_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduDel_req, _T("ev_hduDel_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduInfo_Nty, _T("ev_hduInfo_Nty"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduBrdAdd_rsp, _T("ev_hduBrdAdd_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduBrdModify_rsp, _T("ev_hduBrdModify_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduDel_rsp, _T("ev_hduDel_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduChanAdd_rsp, _T("ev_hduChanAdd_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduChanModify_rsp, _T("ev_hduChanModify_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduChanDel_rsp, _T("ev_hduChanDel_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduReboot_req, _T("ev_hduReboot_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduUpdate_rsp, _T("ev_hduUpdate_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduUpdate_req, _T("ev_hduUpdate_req"));

	//ums电视墙预案
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduStyle_Add, _T("ev_hduStyle_Add"));   
//	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduStyle_Del_Req, _T("ev_hduStyle_Del_Req"));
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduStyle_Nty, _T("ev_hduStyle_Nty"));    
    CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduStyle_Add_Rsp, _T("ev_hduStyle_Add_Rsp"));  
//	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduStyle_Del_Rsp, _T("ev_hduStyle_Del_Rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduStyle_update_Req, _T("ev_hduStyle_update_Req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_hduStyle_update_Rsp, _T("ev_hduStyle_update_Rsp"));

	//netmng配置
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_NMServer_nty, _T("ev_NMServer_nty"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_NMServerAdd_req, _T("ev_NMServerAdd_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_NMServerAdd_rsp, _T("ev_NMServerAdd_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_NMServerMdy_req, _T("ev_NMServerMdy_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_NMServerMdy_rsp, _T("ev_NMServerMdy_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_NMServerDel_req, _T("ev_NMServerDel_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_NMServerDel_rsp, _T("ev_NMServerDel_rsp"));

	//ums录像机配置
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_Vcr_nty, _T("ev_Vcr_nty"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_VcrAdd_req, _T("ev_VcrAdd_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_VcrAdd_rsp, _T("ev_VcrAdd_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_VcrMdy_req, _T("ev_VcrMdy_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_VcrMdy_rsp, _T("ev_VcrMdy_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_VcrDel_req, _T("ev_VcrDel_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_VcrDel_rsp, _T("ev_VcrDel_rsp"));


	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_base_info_nty, _T("ev_rec_base_info_nty"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_reg_status_nty, _T("ev_rec_reg_status_nty"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_file_list_info, _T("ev_rec_file_list_info"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_del_file_req, _T("ev_rec_del_file_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_mdy_file_req, _T("ev_rec_mdy_file_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_mdy_file_nack, _T("ev_rec_mdy_file_nack"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_mdy_file_ack, _T("ev_rec_mdy_file_ack"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_conf_rec_info, _T("ev_rec_conf_rec_info"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_conf_play_info, _T("ev_rec_conf_play_info"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_recorder_conf_req, _T("ev_rec_recorder_conf_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_recorder_conf_rsp, _T("ev_rec_recorder_conf_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_pause_conf_req, _T("ev_rec_pause_conf_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_pause_conf_rsp, _T("ev_rec_pause_conf_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_resume_conf_req, _T("ev_rec_resume_conf_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_resume_conf_rsp, _T("ev_rec_resume_conf_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_stop_recorder_req, _T("ev_rec_stop_recorder_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_stop_recorder_rsp, _T("ev_rec_stop_recorder_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_start_play_req, _T("ev_rec_start_play_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_start_play_rsp, _T("ev_rec_start_play_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_pause_play_req, _T("ev_rec_pause_play_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_pause_play_rsp, _T("ev_rec_pause_play_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_resume_play_req, _T("ev_rec_resume_play_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_resume_play_rsp, _T("ev_rec_resume_play_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_stop_play_req, _T("ev_rec_stop_play_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_stop_play_rsp, _T("ev_rec_stop_play_rsp"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_rec_mt_format_rsp, _T("ev_rec_mt_format_rsp"));


	//会议模板导入导出
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_uploadConftemp_req, _T("ev_uploadConftemp_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_uploadConftemp_rsq, _T("ev_uploadConftemp_rsq"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_downloadConftemp_req, _T("ev_downloadConftemp_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_downloadConftemp_rsq, _T("ev_downloadConftemp_rsq"));

	//授权文件导出
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_licenseOutput_req, _T("ev_licenseOutput_req"));
	CPrintCtrl::GetPrintCtrl()->MappingHelper(ev_licenseOutput_Ind, _T("ev_licenseOutput_Ind"));


}



void CMsgDriver::SetSndInstID( u32 dwInstID )
{
	m_dwInstID = dwInstID;
}

u32  CMsgDriver::GetSndInstID()
{
	return m_dwInstID;
}
