/*=============================================================================
模   块   名: 终端控制台业务功能库
文   件   名: mtclibssndata.h
相 关  文 件: mtclibssndata.cpp
文件实现功能: mtclib实例数据维护区
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2007 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/05/28  4.0     王昊        创建
=============================================================================*/

#ifndef _MTCLIBSSNDATA_20070528_H_
#define _MTCLIBSSNDATA_20070528_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MtclibStruct.h"
#include "MtclibSsnInst.h"
#include "addrbook.h"
#include "ummessagestruct.h"

class CMtclibSsnData
{
public:
    CMtclibSsnData();
    virtual ~CMtclibSsnData();

//供UI调用的接口
public:
    //设置当前会话位置
    void SetCurSession(s32 nSession);

    //获取当前会话位置
    s32 GetCurSession(void);

    //获取下一个可用于连接新MT的会话
    BOOL32 GetNextFreeInterface(u32 dwIP, CMtclibSsnInst* &pcInterface);

    //获取VOD参数
    BOOL32 GetVODParam(s32 nSession, CVODParam &cParam);

    //获取矩阵参数
    BOOL32 GetMatrix(s32 nSession, CMatrix &cMatrix);

    //获取配置参数
    BOOL32 GetConfig(s32 nSession, CMTConfig &cConfig);

    //获取终端状态
    BOOL32 GetStatus(s32 nSession, CMtStatus &cStatus);

    //获取监控参数
    BOOL32 GetMonitorParam(s32 nSession, CMonitorParam &cParam);

    //获取多点会议参数
    BOOL32 GetMultiConfStatus(s32 nSession, CMultiConfStatus &cStatus);

    //获取点对点会议参数
    BOOL32 GetP2PConfStatus(s32 nSession, CP2PConfStatus &cStatus);

    //获取地址簿
    BOOL32 GetAddrbook(s32 nSession, CAddrBook &cAddrbook);

    //获取用户列表
    BOOL32 GetUserList(s32 nSession, vector<CUserFullInfo> &vctUserList);

//LIB内部接口
protected:
    //锁定数据
    inline void Lock(void) { EnterCriticalSection( &m_cSect ); }

    //解锁数据
    inline void Unlock(void) { LeaveCriticalSection( &m_cSect ); }

    //设置实例状态
    BOOL32 SetInstState(s32 nInstID, EMInstState emState);

    //获取实例状态
    EMInstState GetInstState(s32 nInstID);

    //设置终端IP地址
    BOOL32 SetMtIP(s32 nInstID, u32 dwIP);

    //获取终端IP地址
    u32 GetMtIP(s32 nInstID);

    //设置会话
    void SetSsnInst(CMtclibSsnInst *pcInst, s32 nInstID);

    //清空
    void SetNull(void);

    //判断终端是否休眠
    BOOL32 IsMtDormancy(s32 nInstIndex);

protected:
    EMInstState         m_aenumInstState[MAX_MTCLIB_SSN_NUM];   //实例状态
    u32                 m_adwMtIP[MAX_MTCLIB_SSN_NUM];          //实例连接的MT地址

    CVODParam           *m_pcVodParam;                          //VOD参数
    CMatrix             *m_pcMatrix;                            //矩阵参数
    CMTConfig           *m_pcMtConfig;                          //配置参数
    CMtStatus           *m_pcMtStatus;                          //终端状态
    CMonitorParam       *m_pcMonitorParam;                      //监控参数
    CMultiConfStatus    *m_pcMultiConfStatus;                   //多点会议参数
    CP2PConfStatus      *m_pcP2PConfStatus;                     //点对点会议参数
    CAddrBook            *m_pcAddrbook;                         //地址簿
    vector<vector<CUserFullInfo> >  m_vvctUserList;             //用户列表

protected:
    CMtclibSsnInst*     m_apcInst[MAX_MTCLIB_SSN_NUM];

private:
    s32                 m_nCurSession;
    CRITICAL_SECTION    m_cSect;

    friend EMMtclibErrorCode MtclibQuit(void);
    friend class CMtclibInterface;
    friend class CMtclibSsnInst;
};

#endif//_MTCLIBSSNDATA_20070528_H_
