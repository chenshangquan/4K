/*****************************************************************************
模块名      : 终端控制台
文件名      : MtcLibError.h
相关文件    : 
文件实现功能: 声明错误代码
作者        : 熊广化
版本        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/12/16  3.0         熊广化      创建
******************************************************************************/
#pragma once

/* 摘自errorid.h
终端控制台错误(14001-16000)
#define ERR_MTC_BGN		ERR_MC_END + 0x0001
#define ERR_MTC_END		ERR_MTC_BGN + 0x07cf*/
#include "errorid.h"	// 错误码范围段定义

// 终端控制台错误
#define ERR_MTC						ERR_MTC_BGN + 0x0000

// 登录失败,未知的用户名或错误的密码
#define ERR_MTC_LOGON_FAILURE		ERR_MTC_BGN + 0x0001

// 当前已无法再同此终端连接,因为已达到终端的连接数目极限
#define ERR_MTC_CAPACITY_LIMIT		ERR_MTC_BGN + 0x0002

// 不能同新的终端连接,因为当前的连接还没有被关闭
#define ERR_MTC_ACTIVE_CONNECTION	ERR_MTC_BGN + 0x0003

// TCP网络通信故障
#define ERR_MTC_TCP					ERR_MTC_BGN + 0x0004

// 无效的句柄
#define	ERR_MTC_INVALID_HANDLE		ERR_MTC_BGN + 0x0005

// OSP初始化失败
#define ERR_MTC_OSP_INIT_FAILURE	ERR_MTC_BGN + 0x0006

// OSP没有初始化
#define ERR_MTC_OSP_NOT_INIT		ERR_MTC_BGN + 0x0007

// 无效的通信节点
#define ERR_MTC_INVALID_NODE		ERR_MTC_BGN + 0x0008

// 创建对象实例失败
#define ERR_MTC_CREATEINSTANCE		ERR_MTC_BGN + 0x0009

// 接口无效
#define ERR_MTC_INTERFACE			ERR_MTC_BGN + 0x000a

// 超时
#define ERR_MTC_TIMEOUT				ERR_MTC_BGN + 0x000b

// 未决
#define ERR_MTC_PENDING				ERR_MTC_BGN + 0x000c

// 无效索引
#define ERR_MTC_INDEX				ERR_MTC_BGN + 0x000d

// 没有实现
#define ERR_MTC_NOT_IMPLEMENT		ERR_MTC_BGN + 0x000e

// 超过设计容量
#define ERR_MTC_EXCEED_CAPACITY		ERR_MTC_BGN + 0x000f

// 不支持并发命令
#define ERR_MTC_CONCURRENT_CMD		ERR_MTC_BGN + 0x0010

// 已经有一个文件正在传输
#define ERR_MTC_BUSY_TRANSFER		ERR_MTC_BGN + 0x0011

// 将命令放入缓冲队列中，等待发送
#define MTC_WAIT_FOR_SEND_CMD		ERR_MTC_BGN + 0x0010