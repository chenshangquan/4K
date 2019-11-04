/*****************************************************************************
   模块名      : PCDV
   文件名      : evpcdv.h
   相关文件    : 
   文件实现功能: PCDV 内部消息定义
   作者        : 
   版本        : V4.0  Copyright(C) 2004-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2006/12/31  4.0         顾振华      创建
******************************************************************************/


#ifndef EVPCDV_H
#define EVPCDV_H

#include "osp.h"

#define EVPCDV_BEGIN            (WM_USER+976)       // 2000

// 连接终端
OSPEVENT( UI_SSN_CONNECT_REQ    ,      (EVPCDV_BEGIN + 1) );
OSPEVENT( SSN_UI_CONNECT_ACK    ,      (EVPCDV_BEGIN + 2) );
OSPEVENT( SSN_UI_CONNECT_NACK   ,      (EVPCDV_BEGIN + 3) ); // 消息体:CUIMsg*, 带错误码

// 开始双流
OSPEVENT( UI_SSN_STARTDUAL_REQ  ,      (EVPCDV_BEGIN + 6) );
OSPEVENT( SSN_UI_STARTDUAL_ACK  ,      (EVPCDV_BEGIN + 7) );
OSPEVENT( SSN_UI_STARTDUAL_NACK ,      (EVPCDV_BEGIN + 8) );

// 停止双流
OSPEVENT( UI_SSN_STOPDUAL_REQ   ,      (EVPCDV_BEGIN + 11) );
OSPEVENT( SSN_UI_STOPDUAL_ACK   ,      (EVPCDV_BEGIN + 12) );
OSPEVENT( SSN_UI_STOPDUAL_NACK  ,      (EVPCDV_BEGIN + 13) );

// 挂断终端
OSPEVENT( UI_SSN_LOGOUT_REQ     ,      (EVPCDV_BEGIN + 16) );

// 桌面捕捉测试
OSPEVENT( UI_SSN_CAPTEST_CMD    ,      (EVPCDV_BEGIN + 19) );
OSPEVENT( SSN_UI_CAPTEST_PROGNOTIF,    (EVPCDV_BEGIN + 20) );

OSPEVENT( SSN_UI_MTPARAMCHANGED_NOTIF, (EVPCDV_BEGIN + 21) );

// 定时器
OSPEVENT( CONNECTMT_TIMER       ,      (EVPCDV_BEGIN + 31) );
OSPEVENT( REQUEST_TIMER         ,      (EVPCDV_BEGIN + 32) );   

//双流分辨率终端和pc机不一直
OSPEVENT(DIFF_RES_BETWEEN_MTANDPC,     (EVPCDV_BEGIN + 33) );

#define  PCDV_MSG_END                  (EVPCDV_BEGIN + 50)

#endif //EVPCDV_H