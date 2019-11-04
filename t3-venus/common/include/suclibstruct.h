/*=============================================================================
模   块   名: 文件升级客户端业务功能库
文   件   名: suclibstruct.h
相 关  文 件: suclibstruct.cpp
文件实现功能: suclib内部结构定义
作        者: 王昊
版        本: V1.0  Copyright(C) 2006-2007 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/02/11  1.0     王昊        创建
=============================================================================*/

#ifndef _SUCLIBSTRUCT_
#define _SUCLIBSTRUCT_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "filesrvconst.h"


enum EMSessionState
{
    enumSessionStateIdle    = (s32)0,
    enumSessionStatePrepare = (s32)1,
    enumSessionStateService = (s32)2
};

//界面消息
typedef struct tagSucParam
{
public:
    tagSucParam() : m_dwErrorCode(0), m_bTimedout(FALSE), m_wLen(0),
                    m_pbyMsg(NULL) {}

public:
    u32     m_dwErrorCode;  //错误码(超时则为超时的REQ消息号)
    BOOL32  m_bTimedout;    //是否超时
    u16     m_wLen;         //消息长度(主机序)
    u8      *m_pbyMsg;      //消息体(主机序)
} TSucParam;


class CSucFile
{
public:
    CSucFile() : m_dwFileSize(0), m_dwSizePerPkt(0), m_wTotalPkt(0),
                 m_wCurPkt(0), m_pbyFile(NULL)
    { memset( m_szFilename, 0, sizeof (m_szFilename) ); }

    virtual ~CSucFile() { DEL_PTR_ARRAY(m_pbyFile); };

public:
    s8  m_szFilename[MAX_FILESRV_FILENAME_LEN];
    u32 m_dwFileSize;
    u32 m_dwSizePerPkt;
    u16 m_wTotalPkt;
    u16 m_wCurPkt;
    u8  *m_pbyFile;
};


#endif//_SUCLIBSTRUCT_
