/*****************************************************************************
   模块名      : PCDV
   文件名      : mtssn.h
   相关文件    : 
   文件实现功能: 终端会话连接 OSP实例定义
   作者        : 
   版本        : V4.0  Copyright(C) 2004-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2006/12/28  4.0         顾振华      创建
******************************************************************************/
#ifndef MTINST_H
#define MTINST_H

#pragma once

#include "osp.h"
#include "pcdvcomm.h"
#include "mtconst.h"
#include "mtmsg.h"

void dvCritical(s8*  pszFmt, ...);
void dvWarning(s8*  pszFmt, ...);
void dvInfo(s8*  pszFmt, ...);

API void dvsetlog(u8 byLevel);

// 桌面双流性能测试回调函数
// byProgress - [in] 当前进度
// bCancel    - [out] 是否取消
typedef  void (*CB_PcdvPfmTest) (u8 byProgress, BOOL32 &bCancel);

#define MAXLEN_UIMSG_BUF        8192

class CUIMsg
{
public:
    CUIMsg()
    {
        m_wLen = 0;
        m_wErrCode = PCDV_RET_OK;
        memset( m_abyBuf, 0, sizeof(m_abyBuf) );
    }
    ~CUIMsg () 
    {
    }

    void SetMsgBody( const u8* const pbyBody = NULL, u16 wLen = 0)
    {
        m_wLen = (wLen < MAXLEN_UIMSG_BUF ? wLen : MAXLEN_UIMSG_BUF);
        if (m_wLen > 0)    
        {
            memcpy ( m_abyBuf, pbyBody, m_wLen );
        }
    }

    void CatMsgBody( const u8* const pbyBody, u16  wLen )
    {
        if ( pbyBody == NULL || wLen == 0 )
            return;
        wLen = min( wLen, MAXLEN_UIMSG_BUF - GetMsgBodyLen() );
        memcpy( m_abyBuf + GetMsgBodyLen(), pbyBody, wLen );
	    m_wLen += wLen;        
    }

    void SetErrorCode(u16 wErr)
    {
        m_wErrCode = wErr;
    }
    u16 GetErrorCode() const
    {
        return m_wErrCode;
    }
    u16 GetMsgBodyLen() const
    {
        return m_wLen;
    }
    const u8* GetMsgBody() const
    {
        return m_abyBuf;
    }
private:
    u8   m_abyBuf[MAXLEN_UIMSG_BUF];
    u16  m_wLen;
    u16  m_wErrCode;
};


// 终端通知的相关参数:会议状态、双流状态、编码类型、编码参数、网络参数等
struct TMtAllParam
{
    TMtAllParam()
    {
        SetNull();
    }

    void SetNull()
    {
        memset(this, 0, sizeof(TMtAllParam));
    }

    void SetConnected(BOOL32 bIs)
    {
        m_bConnected = bIs;
    }

    BOOL32 IsConnected() const
    {
        return m_bConnected;
    }
    
    void SetMtModel(EmMtModel emModel)
    {
        m_emMtModel = emModel;
    }
    EmMtModel GetMtModel() const
    {
        return m_emMtModel;
    }
    void SetInConf(BOOL bIn)
    {
        m_bInConf = bIn;
    }
    BOOL IsInConf() const
    {
        return m_bInConf;
    }
    void SetConfMode(EmConfMode emMode)
    {
        m_emConfMode = emMode;
    }
    EmConfMode GetConfMode() const
    {
        return m_emConfMode;
    }
    void SetSendDual(BOOL bSend)
    {
        m_bSendDual = bSend;
    }
    BOOL IsSendDual() const
    {
        return m_bSendDual;
    }
    void SetRecvDual(BOOL bRecv)
    {
        m_bRecvDual = bRecv;
    }
    BOOL IsRecvDual() const
    {
        return m_bRecvDual;
    }

    void SetCanSendVideo(BOOL bCan)
    {
        m_bCanSendVideo = bCan;
    }
    BOOL IsCanSendVideo() const
    {
        return m_bCanSendVideo;
    }

    void SetDualFromSelf(BOOL bSelf)
    {
        m_bDualFromSelf = bSelf;
    }
    BOOL IsDualFromSelf() const
    {
        return m_bDualFromSelf;
    }
    void SetCapRes(EmVideoResolution emRes)
    {
        m_emCapRes = emRes;       
    }
    EmVideoResolution GetCapRes() const
    {
        return m_emCapRes;
    }
    void SetCapWidth(u16 wWidth)
    {
        m_wCapWidth = wWidth;
    }
    u16  GetCapWidth() const
    {
        return m_wCapWidth;
    }
    void SetCapHeight(u16 wHeight)
    {
        m_wCapHeight = wHeight;
    }
    u16 GetCapHeight() const
    {
        return m_wCapHeight;
    }

    void SetRtpDestAddr(const TIPTransAddr& tAddr)
    {
        m_tRtpDestAddr = tAddr;
    }
    TIPTransAddr GetRtpDestAddr() const 
    {
        return m_tRtpDestAddr;
    }

    void SetRtcpDestAddr(const TIPTransAddr& tAddr)
    {
        m_tRtcpDestAddr = tAddr;
    }
    TIPTransAddr GetRtcpDestAddr() const 
    {
        return m_tRtcpDestAddr;
    }

    void SetRtcpLocalAddr(const TIPTransAddr& tAddr)
    {
        m_tRtcpLocalAddr = tAddr;
    }
    TIPTransAddr GetRtpLocalAddr() const 
    {
        return m_tRtcpLocalAddr;
    }
    
    void SetEncParam(const TVideoEncodeParameter& tParam)
    {
        m_tEncParam = tParam;
    }

    TVideoEncodeParameter GetEncParam() const 
    {
        return m_tEncParam;
    }
    
    void SetActivePayload(u8 byPayload)
    {
        m_byActivePayload = byPayload;
    }
    u8 GetActivePayload() const
    {
        return m_byActivePayload;
    }

    void SetEncryptKey(const TEncryptKey& tKey)
    {
        m_tEncryptKey = tKey;
    }
    TEncryptKey GetEncryptKey() const
    {
        return m_tEncryptKey;
    }

    void Print() const
    {
        dvCritical( "TMtAllParam\n" );
        dvCritical( "\t m_bConnected : %d\n", m_bConnected );
        dvCritical( "\t m_emMtModel : %d\n", m_emMtModel );
        dvCritical( "\t m_bInConf:%d\n", m_bInConf);
        dvCritical( "\t m_emConfMode:%d\n", m_emConfMode);
        dvCritical( "\t m_bSendDual:%d\n", m_bSendDual);
        dvCritical( "\t m_bRecvDual:%d\n", m_bRecvDual);
        dvCritical( "\t m_bCanSendVideo:%d\n", m_bCanSendVideo);
        dvCritical( "\t m_bDualFromSelf:%d\n", m_bDualFromSelf);        
        dvCritical( "\t m_wCapWidth/m_wCapHeight: %d/%d\n", m_wCapWidth, m_wCapHeight);
        dvCritical( "\t m_tRtpDestAddr: 0x%x:%d\n", m_tRtpDestAddr.dwIP, m_tRtpDestAddr.wPort);
        dvCritical( "\t m_tRtcpDestAddr: 0x%x:%d\n", m_tRtcpDestAddr.dwIP, m_tRtcpDestAddr.wPort);
        dvCritical( "\t m_tRtcpLocalAddr: 0x%x:%d\n", m_tRtcpLocalAddr.dwIP, m_tRtcpLocalAddr.wPort);

        dvCritical( "\t m_byActivePayload:%d\n", m_byActivePayload);
    }

protected:
    BOOL32        m_bConnected;          // 是否已经连接

    EmMtModel     m_emMtModel;           // 终端型号
    BOOL          m_bInConf;             // 是否在会议中
    EmConfMode    m_emConfMode;          // 会议类型
    BOOL          m_bSendDual;           // 是否在发送双流
    BOOL          m_bRecvDual;           // 是否在接收双流

    BOOL          m_bCanSendVideo;       // 当前本端是否能发双流
    
    BOOL32        m_bDualFromSelf;       // 是否本端发起的双流

    // 终端双流能力宽/高
    EmVideoResolution m_emCapRes;
    u16           m_wCapWidth;           
    u16           m_wCapHeight;

    // 发送地址相关参数
    TIPTransAddr  m_tRtpDestAddr;        // 终端RTP/RCTP地址
    TIPTransAddr  m_tRtcpDestAddr;
    TIPTransAddr  m_tRtcpLocalAddr;      // 本地RTCP地址
    
    // 编码参数
    TVideoEncodeParameter m_tEncParam;  
    // 动态载荷
    u8            m_byActivePayload; 
    // 密钥
    TEncryptKey   m_tEncryptKey;
};


// 本端PC的相关参数:系统分辨率,本端地址等
struct TPCSysParam
{
    TPCSysParam()
    {
        // 本端不变的常数
        m_cemCodecComponent = emSecondVideoEncoder;
        m_cemMtVideoPort = emMtPC;        
    }

    void SetConnectParam( const u32 dwMtIp, LPSTR lpszName, LPSTR lpszPass )
    {
        m_dwMtAddr = dwMtIp;

        m_cUser.Empty();
        m_cUser.SetName( lpszName );
        m_cUser.SetPassword( lpszPass );
    }

    void SetScrParam( u16 wWidth, u16 wHeight, EmVideoResolution emRes )
    {
        m_wScrWidth  = wWidth;
        m_wScrHeigth = wHeight;
        m_emRes      = emRes;
    }
    u16  GetScrWidth() const
    {
        return m_wScrWidth;
    }
    u16  GetScrHeight() const
    {
        return m_wScrHeigth;
    }
    EmVideoResolution GetScrRes() const
    {
        return m_emRes;
    }

    void SetTransAddr( u32_ip dwIp )
    {
        m_tTransAddr.dwIP = dwIp;
        m_tTransAddr.wPort = RTP_LOCALSNAP_PORT;         // 默认端口为 RTP_LOCALSNAP_PORT
    }
    TIPTransAddr GetTransAddr()
    {
        return m_tTransAddr;
    }

    u32_ip GetMtAddr() const
    {
        return m_dwMtAddr;
    }
    const CLoginRequest& GetUserInfo() const
    {
        return m_cUser;
    }    
    EmMtVideoPort GetMtVideoPort() const
    {
        return m_cemMtVideoPort;
    }   

    void SetMaxH263CapSVGA(u8 byCap)
    {
        m_byMaxH263CapSVGA = byCap;
    }
    u8   GetMaxH263CapSVGA() const
    {
        return m_byMaxH263CapSVGA;
    }
    void SetMaxH263CapXGA(u8 byCap)
    {
        m_byMaxH263CapXGA = byCap;
    }
    u8   GetMaxH263CapXGA() const
    {
        return m_byMaxH263CapXGA;
    }

    //设置H.264/SVGA下的最大捕捉能力
    inline void SetMaxH264CapSVGA(u8 byCap) { m_byMaxH264CapSVGA = byCap; }

    //获取H.264/SVGA下的最大捕捉能力
    inline u8 GetMaxH264CapSVGA(void) const { return m_byMaxH264CapSVGA; }

    //设置H.264/XGA下的最大捕捉能力
    inline void SetMaxH264CapXGA(u8 byCap) { m_byMaxH264CapXGA = byCap; }

    //获取H.264/XGA下的最大捕捉能力
    inline u8 GetMaxH264CapXGA(void) const { return m_byMaxH264CapXGA; }

    void Print() const
    {
        dvCritical( "TPCSysParam\n" );
        dvCritical( "\t Screen Res : %d(%d*%d)\n", m_emRes, m_wScrWidth, m_wScrHeigth );
        dvCritical( "\t m_tTransAddr : 0x%x:%d\n", m_tTransAddr.dwIP, m_tTransAddr.wPort);

        dvCritical( "\t m_cemCodecComponent : %d\n", m_cemCodecComponent);
        dvCritical( "\t m_cemMtVideoPort : %d\n", m_cemMtVideoPort);
        dvCritical( "\t m_byMaxH263CapSVGA : %d\n", m_byMaxH263CapSVGA);
        dvCritical( "\t m_byMaxH263CapXGA : %d\n", m_byMaxH263CapXGA);
        dvCritical( "\t m_byMaxH264CapSVGA : %d\n", m_byMaxH264CapSVGA);
        dvCritical( "\t m_byMaxH264CapXGA : %d\n", m_byMaxH264CapXGA);

        dvCritical( "\t m_dwMtAddr : 0x%x\n", m_dwMtAddr);
        CLoginRequest cTmpUsr = m_cUser;
        dvCritical( "\t m_cUser : %s\n", cTmpUsr.GetName());
    }

protected:
    // 屏幕宽/高
    u16           m_wScrWidth;          
    u16           m_wScrHeigth;
    EmVideoResolution m_emRes;

    TIPTransAddr  m_tTransAddr;         // 本端地址

    // 本端的两个常数
    EmCodecComponent m_cemCodecComponent;
    EmMtVideoPort    m_cemMtVideoPort;
    
    // 本端捕捉能力
    u8            m_byMaxH263CapSVGA;
    u8            m_byMaxH263CapXGA;

    u8              m_byMaxH264CapSVGA;
    u8              m_byMaxH264CapXGA;

    // 缓存
    u32_ip        m_dwMtAddr;           // 连接终端的IP地址
    CLoginRequest m_cUser;              // 当前用户

};


class CMtInst : public CInstance
{
public:
	CMtInst();
	~CMtInst();	
public:
	enum enState
    {
		STATE_IDLE    = 0,
        STATE_CONNECT,
		STATE_NORMAL
	};   
    
    virtual void DaemonInstanceEntry(CMessage *const, CApp* );
    virtual void InstanceEntry( CMessage *const);

protected:
    /////////////////////
    // Daemon 消息处理 //
    /////////////////////

    // 用户请求登陆
    void DaemonProcConnectReq(CMessage *const, CApp*);


    /////////////////////
    // 普通消息处理    //
    /////////////////////

    // 用户请求登陆
    void ProcConnectReq(CMessage *const);
    // 处理登陆回应
    void ProcConnectRsp(CMessage *const);

    // 起停双流请求/回应
    void ProcDualReq(CMessage *const);
    void ProcDualRsp(CMessage *const);  
    
    void ProcGeneralReqTimeout(CMessage *const);  

    // 注销
    void ProcLogoutReq(CMessage *const);
    
    // 终端上报的参数
    void ProcMtParamInd(CMessage *const);
    // 终端命令开始/停止编码
    void ProcMtCodecCmd(CMessage *const);

    void ProcPCVideoTest(CMessage *const);

    // 断链
    void ProcDisconnect(CMessage *const);

private:
    // 清空实例状态
    void ClearInst();

    // 起停桌面捕捉
    BOOL32 StartCap();
    BOOL32 StopCap();

    // 通知界面消息
    void NotifyUI(u16 wMsg);

    //测试指定参数下的双流能力
    u16 TestCapAblity(u8 byMediaType, u8 byMaxQuan, u8 byMinQuan,
                      CB_PcdvPfmTest pfCbFunc, u8 byTestCount,
                      u8 &bySVGA, u8 &byXGA, BOOL32 &bUserStop);
private:
	BOOL32 m_bFecCapacity;
};

class CPcdvCfg
{
public:
    CPcdvCfg();
    ~CPcdvCfg();

public:
    u32    m_dwMtNode;          // MT 的节点号码
    u32    m_dwMtIId;           // MT APPID和Instance ID
    
    BOOL32 m_bPromptTest;       // 是否提示过要进行能力测试
    static CString  m_s_cstrCfgFile;

public:
    // 返回工作路径
    LPCSTR  GetWorkingPath() ; 

    // 初始化
    u16 Initialize(HWND hWnd, CString strCfgFile);
    void Uninitialize();
   
    // 发送内部消息
    void SendMsgToMtSsnDaemon( u16 wEvent, const u8* const pbyMsg = NULL, u16 wLen = 0 );
    void SendMsgToMtSsn( u16 wEvent, const u8* const pbyMsg = NULL, u16 wLen = 0 );

    // 发送消息给终端
    void SendMsgToMt( CMtMsg* const pcMtMsg );
    void SendMsgToMt( u16 wEvent, const u8* const pbyMsg = NULL, u16 wLen = 0 );

    u8 GetDebugLevel()
    {
        return byDebugLevel;
    }
    void SetDebugLevel(u8 byLevel)
    {
        if (byLevel > PCDV_DEBUG_INFO)
            byLevel = PCDV_DEBUG_INFO;
        byDebugLevel = byLevel;
    }


/*=============================================================================

  以下是提供给上层的应用接口

  ----------------------------------------------------------------------------
  修改记录    ：
  日  期		版本		修改人		走读人    修改内容
  2006/12/31    4.0			顾振华                  创建
=============================================================================*/

public:
    /*=============================================================================
      函 数 名： ConnectMtReq
      功    能： 请求连接终端
      算法实现： 
      全局变量： 
      参    数：
      返 回 值： 错误码
      ----------------------------------------------------------------------------
      修改记录    ：
      日  期		版本		修改人		走读人    修改内容
      2006/12/31    4.0			顾振华                  创建
    =============================================================================*/
    u16 ConnectMtReq( );
    u16 ConnectMtReq( u32_ip dwMtIp, LPSTR lpszUser, LPSTR lpszPwd );

    /*=============================================================================
      函 数 名： StartDualVideo
      功    能： 开始PC双流
      算法实现： 
      全局变量： 
      参    数：
      返 回 值： 错误码
      ----------------------------------------------------------------------------
      修改记录    ：
      日  期		版本		修改人		走读人    修改内容
      2006/12/31    4.0			顾振华                  创建
    =============================================================================*/
    u16 StartDualVideo();

    /*=============================================================================
      函 数 名： StopDualVideo
      功    能： 停止PC双流
      算法实现： 
      全局变量： 
      参    数：
      返 回 值： 错误码
      ----------------------------------------------------------------------------
      修改记录    ：
      日  期		版本		修改人		走读人    修改内容
      2006/12/31    4.0			顾振华                  创建
    =============================================================================*/
    u16 StopDualVideo();

    /*=============================================================================
      函 数 名： LogoutMT
      功    能： 断开终端连接
      算法实现： 
      全局变量： 
      参    数：
      返 回 值： 错误码
      ----------------------------------------------------------------------------
      修改记录    ：
      日  期		版本		修改人		走读人    修改内容
      2006/12/31    4.0			顾振华                  创建
    =============================================================================*/
    u16 LogoutMT();

    /*=============================================================================
      函 数 名： PCVideoTest
      功    能： 桌面双流能力测试
      算法实现： 
      全局变量： 
      参    数：
      返 回 值：              
      ----------------------------------------------------------------------------
      修改记录    ：
      日  期		版本		修改人		走读人    修改内容
      2007/1/26    4.0			顾振华                  创建
    =============================================================================*/
    u16 PCVideoTest(CB_PcdvPfmTest pfCbFunc);    

public:
    /*=============================================================================
      函 数 名： GetMTParam
      功    能： 获取终端相关参数：会议状态、双流状态、编码类型、编码参数、网络参数等
      算法实现： 
      全局变量： 
      参    数：TMtAllParam &tMtParam           [out]
      返 回 值： 错误码
      ----------------------------------------------------------------------------
      修改记录    ：
      日  期		版本		修改人		走读人    修改内容
      2006/12/31    4.0			顾振华                  创建
    =============================================================================*/
    u16 GetMTParam(TMtAllParam &tMtParam) const
    {
        tMtParam = m_tMtParam;
        return PCDV_RET_OK;
    }

    void SetMTParam(const TMtAllParam &tMtParam)
    {
        m_tMtParam = tMtParam;
    }

    /*=============================================================================
      函 数 名： GetPCSysParam
      功    能： 获取系统相关参数
      算法实现： 
      全局变量： 
      参    数：
      返 回 值： 错误码
      ----------------------------------------------------------------------------
      修改记录    ：
      日  期		版本		修改人		走读人    修改内容
      2006/12/31    4.0			顾振华                  创建
    =============================================================================*/
    u16 GetPCSysParam(TPCSysParam &tPcParam) const
    {
        tPcParam = m_tSysParam;
        return PCDV_RET_OK;
    }
    void SetPCSysParam(const TPCSysParam &tPcParam)
    {
        m_tSysParam = tPcParam;
    }

    void SetMainWnd( HWND hWnd )
    {
        m_hMainWnd = hWnd;
    }
    HWND GetMainWnd() const
    {
        return m_hMainWnd;
    }

    void SetConnectedMt(BOOL32 bIs)
    {
       m_tMtParam.SetConnected(bIs);
    }
    BOOL32 IsConnectedMt() const
    {
        return m_tMtParam.IsConnected();
    }

private:
    u8 byDebugLevel;

    TMtAllParam m_tMtParam;
    TPCSysParam m_tSysParam;

    HWND        m_hMainWnd;
};

typedef zTemplate< CMtInst, 1, CPcdvCfg > CMtSsn;

extern CMtSsn g_cMtSsn;

#endif //!MTINST_H

