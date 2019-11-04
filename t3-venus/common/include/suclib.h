/*=============================================================================
模   块   名: 文件升级客户端业务功能库
文   件   名: suclib.h
相 关  文 件: suclib.cpp
文件实现功能: suc模块接口实现
作        者: 王昊
版        本: V1.0  Copyright(C) 2006-2007 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/02/11  1.0     王昊        创建
=============================================================================*/

#ifndef _SUCLIB_
#define _SUCLIB_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "succonst.h"
#include "suclibstruct.h"
#include "sucstruct.h"
#include <afxmt.h>
#include <vector>
#include "filesrvclientstruct.h"

using namespace std;

class CPrepareMsgDeal;
class CConnectMsgDeal;
class CUserMsgDeal;
class CVersionMsgDeal;
class CMsgHandler;
class CConfigMsgDeal;
class CFileMsgDeal;

//数据处理、接口调用类
class CSucSession
{
public:
    CSucSession();

    virtual ~CSucSession();

    //获取服务器IP
    inline u32 GetSusIP(void) const { return m_dwSusIP; }

    //获取服务状态
    inline EMSessionState GetState(void) const { return m_emState; }

    //获取InstID
    inline s32 GetInstID(void) const { return m_nInstID; }

    //设置InstID
    inline void SetInstID(s32 nInstID) { m_nInstID = nInstID; }

    //创建
    u16 Create(HWND hWnd);

    //清空
    u16 Free(void);

    //消息处理
    void OnDealMsg(CMessage * const pcMsg, CMsgHandler *pcHandler);

    //准备状态下的消息处理
    void OnPrepare(CMessage * const pcMsg, CMsgHandler *pcHandler);

    //正常状态下的消息处理
    void OnService(CMessage * const pcMsg, CMsgHandler *pcHandler);

    //向服务器发送消息
    BOOL32 PostMsgToSus(u16 wEventID, const u8 * const pbyMsg, u16 wMsgLen,
                        u32 dwTimeout = DEFAULT_TIMEOUT,
                        u16 *pwTotalPkt = NULL, u16 *pwCurPkt = NULL);

    //向上层界面发消息
    void SendMsgToUI(u16 wEventId, const TSucParam &tParam);

    //检查消息长度
    BOOL32 CheckMsgLen(u16 wEventId, u16 wExpectLen, u16 wRecvLen);

    //服务状态超时消息处理
    void OnTimerService(CMessage * const pcMsg, CMsgHandler *pcHandler);

//接口
public:
    //1. 连接
    //连接
    u16 ConnectSusReq(u32 dwIP, u16 wPort, LPCTSTR lptrUsername, LPCTSTR lptrPwd);

    //断开
    u16 DisconnectSusReq(void);

    //重启
    u16 ResetSusReq(BOOL32 bNoResetIfMtLogin);

    //2. 用户
    //获取用户列表
    u16 GetUserListReq(void);

    //添加用户
    u16 AddUserReq(const CUserFullInfo &tInfo);

    //编辑用户
    u16 EditUserReq(const CFCSrvUserInfo &tInfo);

    //删除用户
    u16 DelUserReq(u32 dwUserNo);

    //3. 配置
    //获取配置
    u16 GetCfgReq(void);

    //编辑配置
    u16 EditCfgReq(const ISusConfig &tCfg);

    //4. 文件
    //4.1 版本修改
    //查询所有推荐版本
    u16 GetAllRecommendedVerReq(void);

    //查询某一设备历史版本详细信息(包含推荐版本)
    u16 GetDevVerInfoReq(const IFCSrvDev &tDev);
    //设置推荐版本
    u16 SetRecommendedVerReq(u32 dwDevNo);

    //删除版本
    u16 DelVerReq(u32 dwDevNo);

    //编辑版本
    u16 EditVerReq(u32 dwDevNo, const IFCHardwareVer &tHardVer,
                   LPCSTR lptrBugReport);

    //4.2 文件上传
    //开始上传
    u16 StartUpgradeReq(const CAddVerInfo &cInfo);

    //停止上传
    u16 StopUpgradeReq(void);

//获取存储信息
public:
    //获取用户列表
    void GetUserList(vector<CFCSrvUserInfo> &vctUserList);

    //获取服务器配置
    void GetSuSCfg(ISusConfig &tCfg);

    //获取推荐版本列表
    void GetRecommendedVerList(vector<IFCSrvDevVerFullInfo> &vctVerList);

    //获取权限
    u8 GetRight(void) const { return m_byRight; }

//刷新存储信息
private:
    //刷新用户信息
    void UpdateUserList(const u8 * const pbyMsg);

    //刷新服务器配置
    void UpdateSusCfg(const u8 * const pbyMsg);

private:
    u32     m_dwSusNode;        //服务器节点
//    u32     m_dwSusIID;         //服务器IID

    u32     m_dwSusIP;          //服务器IP
    u32     m_dwSusSn;          //服务器服务号

    EMSessionState  m_emState;  //本Ins服务状态
    HWND            m_hWnd;     //上层消息发送界面句柄
    u16             m_wWaitEvent;   //等待消息
    u16             m_wSendACKNOTIF;//部分REQ后服务器发送ACK和NOTIF，
                                    //但是lib只需要向界面发送一条消息即可
                                    //本消息号区分到底发送ACK还是NOTIF

    u8              m_byRight;      //用户权限
    u8              m_byUpgrading;  //是否处于版本升级状态
    u8              m_byCurFileIdx; //当前传输文件序号

    s32     m_nInstID;          //本会话在g_ptCtrlData->m_acSucSession中的位置
    vector<CSucFile>    m_vctFile;  //本次上传的文件信息

    CCriticalSection    m_cLock;

    friend class CPrepareMsgDeal;
    friend class CConnectMsgDeal;
    friend class CUserMsgDeal;
    friend class CVersionMsgDeal;
    friend class CConfigMsgDeal;
    friend class CFileMsgDeal;

//存储数据
    vector<CFCSrvUserInfo>          m_vctUserInfo;  //用户列表
    ISusConfig                      m_tSusCfg;      //服务器配置
    vector<IFCSrvDevVerFullInfo>    m_vctDevList;   //推荐版本列表

    s8                              m_szUsername[MAX_FILESRV_USERNAME_LEN];
    //临时存储数据
    IFCSrvDevVerFullInfo            *m_ptDevVer;    //某一设备所有版本信息
};









#endif//_SUCLIB_
