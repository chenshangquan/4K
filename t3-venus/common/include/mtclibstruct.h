/*=============================================================================
模   块   名: 终端控制台业务功能库
文   件   名: mtclibstruct.h
相 关  文 件: mtclibstruct.cpp
文件实现功能: mtclib上层接口实现
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2007 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/04/20  4.0     王昊        创建
=============================================================================*/

#ifndef _MTCLIBSTRUCT_20070420_H_
#define _MTCLIBSTRUCT_20070420_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MtclibConst.h"
#include "MtMsg.h"

///////////////////////////////////////////////////////////////////////////////
//  a. UI/LIB公用结构
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//  1. 终端配置
///////////////////////////////////////////////////////////////////////////////
class CMTConfig
{
public:
    //构造函数
    CMTConfig();
    //析构函数
    virtual ~CMTConfig();

public:
    //清空
    void SetNull(void);

    //设置是否开启回声抵消
    inline void SetAECEnabled(BOOL32 bEnabled) { m_bIsAEC = bEnabled; }

    //判断是否开启回声抵消
    inline BOOL32 IsAECEnabled(void) const { return m_bIsAEC; }

    //设置是否自动增益
    inline void SetAGCEnabled(BOOL32 bEnabled) { m_bIsAGC = bEnabled; }

    //判断是否自动增益
    inline BOOL32 IsAGCEnabled(void) const { return m_bIsAGC; }

    //设置是否开启自动噪声抑制
    inline void SetANSEnabled(BOOL32 bEnabled) { m_bIsANS = bEnabled; }

    //判断是否开启自动噪声抑制
    inline BOOL32 IsANSEnabled(void) const { return m_bIsANS; }

    //T2设置主视频输出是否到VIDEO
    inline void SetMainVideoToVideo(BOOL32 bEnabled)
    { m_bMainVideoToVideo = bEnabled; }

    //T2判断主视频输出是否到VIDEO
    inline BOOL32 IsMainVideoToVideo(void) const { return m_bMainVideoToVideo; }
 
    //设置摄像头状态
    inline void SetCamState(s32 nIndex, BOOL32 bState)
    {
        if (    nIndex >= 0
             && nIndex < sizeof (m_abCamState) / sizeof (m_abCamState[0]) )
        {
            m_abCamState[nIndex] = bState;
        }
    }

    //获取摄像头状态
    inline BOOL32 GetCamState(s32 nIndex) const
    {
        if (    nIndex >= 0
             && nIndex < sizeof (m_abCamState) / sizeof (m_abCamState[0]) )
        {
            return m_abCamState[nIndex];
        }
        else
        {
            return FALSE;
        }
    }

    //设置控制类型
    inline void SetSerialType(EmSerialType emType) { m_emSerialType = emType; }

    //获取控制类型
    inline EmSerialType GetSerialType(void) const { return m_emSerialType; }

    //设置VGA显示是否是本地
    inline void SetVGAShowLocal(BOOL32 bEnabled) { m_bVGAShowLocal = bEnabled; }

    //获取VGA显示是否是本地
    inline BOOL32 IsVGAShowLocal(void) const { return m_bVGAShowLocal; }

    //设置第二路视频是否输出到VGA
    inline void Set2ndVideoToVGA(BOOL32 bEnabled)
    { m_bSecondVideoToVGA = bEnabled; }

    //获取第二路视频是否输出到VGA
    inline BOOL32 Is2ndVideoToVGA(void) const { return m_bSecondVideoToVGA; }

    //设置是否允许切换到监控
    inline void SetEnableMonitor(BOOL32 bEnabled)
    { m_bEnableMonitor = bEnabled; }

    //获取是否允许切换到监控
    inline BOOL32 IsEnableMonitor(void) const { return m_bEnableMonitor; }

    //设置是否允许发送静态图片
    inline void SetSendStaticPic(BOOL32 bEnabled) { m_bSendStaticPic = bEnabled; }

    //获取是否允许发送静态图片
    inline BOOL32 IsSendStaticPic(void) const { return m_bSendStaticPic; }

    //设置是否启用DHCP
    inline void SetUseDHCP(BOOL32 bEnabled) { m_bUseDHCP = bEnabled; }

    //获取是否启用DHCP
    inline BOOL32 IsUseDHCP(void) const { return m_bUseDHCP; }

    //设置呼叫速率(主机序)
    inline void SetCallRate(u32 dwCallRate) { m_dwCallRate = dwCallRate; }

    //获取呼叫速率(主机序)
    inline u32 GetCallRate(void) const { return m_dwCallRate; }

    //设置网关(网络序)
    inline void SetGateway(u32 dwNetGateway)
    { m_dwGateWay = ntohl( dwNetGateway ); }

    //获取网关(主机序)
    inline u32 GetGateway(void) const { return m_dwGateWay; }

    //设置DNS服务器IP(网络序)
    inline void SetDNSIP(u32 dwNetDNSIP)
    { m_dwDNSServerIP = ntohl( dwNetDNSIP ); }

    //获取DNS服务器IP(主机序)
    inline u32 GetDNSIP(void) const { return m_dwDNSServerIP; }

    //设置MTU值(主机序)
    inline void SetMTU(u32 dwMTU) { m_dwMTU = dwMTU; }

    //获取MTU值(主机序)
    inline u32 GetMTU(void) const { return m_dwMTU; }

    //设置UDP起始端口(主机序)
    inline void SetUDPStartPort(u16 wPort) { m_wUDPStartPort = wPort; }

    //获取UDP起始端口(主机序)
    inline u16 GetUDPStartPort(void) const { return m_wUDPStartPort; }

    //设置TCP起始端口(主机序)
    inline void SetTCPStartPort(u16 wPort) { m_wTCPStartPort = wPort; }

    //获取TCP起始端口(主机序)
    inline u16 GetTCPStartPort(void) const { return m_wTCPStartPort; }

    //设置当前语言类型
    inline void SetCurLanguage(EmLanguage emLan) { m_emCurLanguage = emLan; }

    //获取当前语言类型
    inline EmLanguage GetCurLanguage(void) const { return m_emCurLanguage; }

    //设置麦克风增益控制
    inline void SetMicAdjust(u8 byMic) { m_byMicAdjust = byMic; }

    //获取麦克风增益控制
    inline u8 GetMicAdjust(void) const { return m_byMicAdjust; }

    //设置LDAP服务器
    inline void SetLDAPAddr(LPCSTR lptrLDAP)
    {
        memset( m_szLDAPServer, 0, sizeof (m_szLDAPServer) );
        if ( lptrLDAP != NULL )
        {
            strncpy( m_szLDAPServer, lptrLDAP,
                     sizeof (m_szLDAPServer) - 1 );
        }
    }

    //获取LDAP服务器
    inline LPCSTR GetLDAPAddr(void) const { return m_szLDAPServer; }

    //设置编码音量
    inline void SetEncVol(u8 byVol) { m_byEncVol = byVol; }

    //获取编码音量
    inline u8 GetEncVol(void) const { return m_byEncVol; }

    //设置解码音量
    inline void SetDecVol(u8 byVol) { m_byDecVol = byVol; }

    //获取解码音量
    inline u8 GetDecVol(void) const { return m_byDecVol; }

public:
    //打印
    void Print(void);

public:
    TH323Cfg            m_tH323Cfg;                         //H.323配置信息
    TUserCfg            m_tUserCfg;                         //用户设置配置信息

    TOsdCfg             m_tOSDCfg;                          //终端显示配置信息

    TEthnetInfo         m_atEthnetInfo[MT_MAX_ETHNET_NUM];  //以太网配置信息
    TE1Config           m_tE1Cfg;                           //E1信息配置
    TSerialCfg          m_atSerialCfg[4];                   //串口信息配置
    vector<TRouteCfg>   m_vctRouteCfg;                      //路由信息配置
    TPPPOECfg           m_tPPPoECfg;                        //PPPoE信息配置
    TSNMPCfg            m_tNetManageCfg;                    //网管信息配置
    TIPQoS              m_tIPQoSCfg;                        //IPQoS信息配置
    TEmbedFwNatProxy    m_tEmbedFwCfg;                      //防火墙信息配置
    TNATMapAddr         m_tNatMap;                          //静态映射

    TLostPackResend     m_tRetransCfg;                      //发送重传信息配置
    TStreamMedia        m_tStreamCfg;                       //流媒体信息配置
    TVideoParam         m_atVideoParam[2];                  //视频编码参数配置
    TVideoParam         m_tPCVideoParam;                    //PC双流配置
    TAVPriorStrategy    m_tAVPriorCfg;                      //优选协议信息配置
    vector<TCameraTypeInfo> m_vctCamTypeInfo;               //摄像头能力类型
    TCameraCfg          m_atCameraCfg[MT_MAX_CAMERA_NUM];   //摄像头信息配置
    TVideoStandard      m_atVideoStandInput[2];             //视频输入制式
    TVideoStandard      m_atVideoStandOutput[2];            //视频输出制式
    TImageAdjustParam   m_tImageAdjust;                     //图像参数
    TBannerInfo         m_tBannerInfo;                      //横幅设置
    TIPTransAddr        m_tIPAddr;                          //串口控制时地址
    TMonitorService     m_tMonitorService;                  //监控切换业务配置
    TDualRation         m_tDualRatio;                       //双流比率
    TMtEquipmentCapset  m_tMTEquipmentCapset;               //MT设备能力集
    TInnerMcCfg         m_tInnerMcCfg;                      //内置MC配置
    TInnerGKCfg         m_tInnerGKCfg;                      //内置GK防火墙配置
    TRapidKey           m_tShortcutKey;                     //遥控器快捷键配置

    TCapType            m_tCapType;                         //PCMT视频源信息

    TVgaOutCfg          m_tVGAOutCfg;                       //8010C配置VGA输出参数

protected:
    BOOL32              m_bIsAEC;                           //是否开启回声抵消
    BOOL32              m_bIsAGC;                           //是否自动增益
    BOOL32              m_bIsANS;                           //是否开启自动噪声抑制

    BOOL32              m_bMainVideoToVideo;                //T2主视频输出是否到VIDEO

    BOOL32              m_abCamState[MT_MAX_CAMERA_NUM];    //摄像头状态
    EmSerialType        m_emSerialType;                     //控制类型
    BOOL32              m_bVGAShowLocal;                    //VGA显示是否是本地
    BOOL32              m_bSecondVideoToVGA;                //第二路视频是否输出到VGA
    BOOL32              m_bEnableMonitor;                   //是否允许切换到监控
    BOOL32              m_bSendStaticPic;                   //是否允许发送静态图片
    BOOL32              m_bUseDHCP;                         //是否启用DHCP

    u32                 m_dwCallRate;                       //呼叫速率(主机序)
    u32                 m_dwGateWay;                        //网关(主机序)
    u32                 m_dwDNSServerIP;                    //DNS服务器IP(主机序)
    u32                 m_dwMTU;                            //MTU值(主机序)

    u16                 m_wUDPStartPort;                    //UDP起始端口(主机序)
    u16                 m_wTCPStartPort;                    //TCP起始端口(主机序)

    EmLanguage          m_emCurLanguage;                    //当前语言类型

    s8                  m_szLDAPServer[MT_MAX_LDAPSERVER_NAME_LEN]; //LDAP服务器
    u8                  m_byMicAdjust;                      //麦克风增益控制

    u8                  m_byEncVol;                         //编码音量
    u8                  m_byDecVol;                         //解码音量
};

///////////////////////////////////////////////////////////////////////////////
//  2. 终端状态(与会议无关)
///////////////////////////////////////////////////////////////////////////////
class CMtStatus
{
public:
    CMtStatus();
    virtual ~CMtStatus();

public:
    //清空
    void SetNull();

    //设置是否休眠
    inline void SetDormancy(BOOL32 bDormancy) { m_bDormancy = bDormancy; }

    //判断是否休眠
    inline BOOL32 IsDormancy(void) const { return m_bDormancy; }

    //设置内置扬声器音量
    inline void SetInnerSpeakerVol(EmMtLoudspeakerVal emVol)
    { m_emInnerSpeakerVol = emVol; }

    //获取内置扬声器音量
    inline EmMtLoudspeakerVal GetInnerSpeakerVol(void) const
    { return m_emInnerSpeakerVol; }

    //设置终端操作系统类型
    inline void SetOSType(EmMtOSType emType) { m_emMTOSType = emType; }

    //获取终端操作系统类型
    inline u8 GetOSType(void) const { return m_emMTOSType; }

    //设置终端硬件版本号
    inline void SetHardVer(u8 byHardVer) { m_byMTHardwareVersion = byHardVer; }

    //获取终端硬件版本号
    inline u8 GetHardVer(void) const { return m_byMTHardwareVersion; }

    //设置终端操作系统版本号
    inline void SetOSVer(LPCSTR lptrOSVer)
    {
        memset( m_szMTOSVersion, 0, sizeof (m_szMTOSVersion) );
        if ( lptrOSVer != NULL )
        {
            strncpy( m_szMTOSVersion, lptrOSVer, sizeof (m_szMTOSVersion) - 1 );
        }
    }

    //获取终端操作系统版本号
    inline LPCSTR GetOSVer(void) const { return m_szMTOSVersion; }

    //设置终端软件版本号
    inline void SetSoftVer(LPCSTR lptrSoftVer)
    {
        memset( m_szMTSoftwareVersion, 0, sizeof (m_szMTSoftwareVersion) );
        if ( lptrSoftVer != NULL )
        {
            strncpy( m_szMTSoftwareVersion, lptrSoftVer,
                     sizeof (m_szMTSoftwareVersion) - 1 );
        }
    }

    //获取终端软件版本号
    inline LPCSTR GetSoftVer(void) const { return m_szMTSoftwareVersion; }

    //设置终端MAC地址
    inline void SetMACAddr(LPCSTR lptrMACAddr)
    {
        memset( m_szMTMac, 0, sizeof (m_szMTMac) );
        if ( lptrMACAddr != NULL )
        {
            strncpy( m_szMTMac, lptrMACAddr, sizeof (m_szMTMac) - 1 );
        }
    }

    //获取终端MAC地址
    inline LPCSTR GetMACAddr(void) const { return m_szMTMac; }

    //设置是否启用MC功能
    inline void SetMCEnabled(BOOL32 bEnabled) { m_bUseMC = bEnabled; }

    //获取是否启用MC功能
    inline BOOL32 IsMCEnabled(void) const { return m_bUseMC; }

    //设置MC工作模式
    inline void SetMCMode(EmMCMode emMode) { m_emMCMode = emMode; }

    //获取MC工作模式
    inline EmMCMode GetMCMode(void) const { return m_emMCMode; }

    //设置FXO状态
    inline void SetFXOStatus(EmFxoState emStatus) { m_emFXOStatus = emStatus; }

    //获取FXO状态
    inline EmFxoState GetFXOStatus(void) const { return m_emFXOStatus; }

    //设置是否正在声音测试
    inline void SetVolumeTest(BOOL32 bTesting) { m_bVolumeTest = bTesting; }

    //获取是否正在声音测试
    inline BOOL32 IsVolumeTest(void) const { return m_bVolumeTest; }

    //设置是否正在本地图像测试
    inline void SetLocalImageTest(BOOL32 bTesting)
    { m_bLocalImageTest = bTesting; }

    //获取是否正在本地图像测试
    inline BOOL32 IsLocalImageTest(void) const { return m_bLocalImageTest; }

    //设置是否正在远端图像测试
    inline void SetRemoteImageTest(BOOL32 bTesting)
    { m_bRemoteImageTest = bTesting; }

    //获取是否正在远端图像测试
    inline BOOL32 IsRemoteImageTest(void) const { return m_bRemoteImageTest; }

    //设置发送双流状态
    inline void SetSendDual(BOOL32 bSendDual) { m_bSendDual = bSendDual; }

    //获取发送双流状态
    inline BOOL32 IsSendDual(void) const { return m_bSendDual; }

    //设置接收双流状态
    inline void SetRecvDual(BOOL32 bRecvDual) { m_bRecvDual = bRecvDual; }

    //获取接收双流状态
    inline BOOL32 IsRecvDual(void) const { return m_bRecvDual; }

    //设置当前双流类型
    inline void SetCurDualType(EmMtVideoPort emCurType)
    { m_emCurDualType = emCurType; }

    //获取当前双流类型
    inline EmMtVideoPort GetCurDualType(void) const { return m_emCurDualType; }

    //设置是否远端环回测试
    inline void SetRemoteLoopbackTest(BOOL32 bTesting)
    { m_bRemoteLoopBackTest = bTesting; }

    //获取是否远端环回测试
    inline BOOL32 IsRemoteLoopbackTest(void) { return m_bRemoteLoopBackTest; }

    //设置远端环回测试类型
    inline void SetRemoteLoopbackTestType(EmVideoType emType)
    { m_emRemoteLoopBackVideoType = emType; }

    //获取远端环回测试类型
    inline EmVideoType GetRemoteLoopbackTestType(void) const
    { return m_emRemoteLoopBackVideoType; }

    //设置CPU使用率
    inline void SetCPUUsage(u8 byCPUUsage) { m_byCPUUsage = byCPUUsage; }

    //获取CPU使用率
    inline u8 GetCPUUsage(void) const { return m_byCPUUsage; }

    //设置终端物理内存大小(主机序)
    inline void SetPhysicMem(u32 dwMem) { m_dwPhysicMem = dwMem; }

    //获取终端物理内存大小(主机序)
    inline u32 GetPhysicMem(void) const { return m_dwPhysicMem; }

    //设置终端已使用内存大小(主机序)
    inline void SetUsedMem(u32 dwMem) { m_dwUsedMem = dwMem; }

    //获取终端已使用内存大小(主机序)
    inline u32 GetUsedMem(void) const { return m_dwUsedMem; }

    //设置终端空闲内存大小(主机序)
    inline void SetFreeMem(u32 dwMem) { m_dwFreeMem = dwMem; }

    //获取终端空闲内存大小(主机序)
    inline u32 GetFreeMem(void) const { return m_dwFreeMem; }

    //设置是否静音
    inline void SetMute(BOOL32 bMute) { m_tMtStatus.bIsQuiet = bMute; }

    //判断是否静音
    inline BOOL32 IsMute(void) const { return m_tMtStatus.bIsQuiet; }

    //设置是否哑音
    inline void SetDumb(BOOL32 bDumb) { m_tMtStatus.bIsMute = bDumb; }

    //判断是否哑音
    inline BOOL32 IsDumb(void) const { return m_tMtStatus.bIsMute; }

    //设置MIC音量
    inline void SetMicVol(u8 byVol) { m_tMtStatus.byEncVol = byVol; }

    //获取MIC音量
    inline u8 GetMicVol(void) const { return m_tMtStatus.byEncVol; }

    //设置扬声器音量
    inline void SetSpeakerVol(u8 byVol) { m_tMtStatus.byDecVol = byVol; }

    //获取扬声器音量
    inline u8 GetSpeakerVol(void) const { return m_tMtStatus.byDecVol; }

    //获取终端类型
    inline EmMtModel GetModel(void) const { return m_tMtStatus.emMtModel; }

    //判断是否在VOD状态中
    inline BOOL32 IsInVOD(void) const { return m_tMtStatus.bIsInVOD; }

public:
    //打印
    void Print(void);

protected:
    BOOL32              m_bDormancy;                        //终端是否休眠

    EmMtLoudspeakerVal  m_emInnerSpeakerVol;                //内置扬声器音量

    EmMtOSType          m_emMTOSType;                       //终端操作系统类型

    u8                  m_byMTHardwareVersion;              //终端硬件版本号
    u8                  m_abyReserved1[3];

    s8                  m_szMTOSVersion[256];               //终端操作系统版本号
    s8                  m_szMTSoftwareVersion[256];         //终端软件版本号
    s8                  m_szMTMac[256];                     //终端MAC地址

    BOOL32              m_bUseMC;                           //是否使用MC
    EmMCMode            m_emMCMode;                         //MC的工作模式

    EmFxoState          m_emFXOStatus;                      //FXO状态

    BOOL32              m_bVolumeTest;                      //是否正在声音测试
    BOOL32              m_bLocalImageTest;                  //是否正在本地图像测试
    BOOL32              m_bRemoteImageTest;                 //是否正在远端图像测试

    BOOL32              m_bSendDual;                        //当前是否发送双流
    BOOL32              m_bRecvDual;                        //当前是否接收双流
    EmMtVideoPort       m_emCurDualType;                    //当前双流类型

    BOOL32              m_bRemoteLoopBackTest;              //是否远端环回测试
    EmVideoType         m_emRemoteLoopBackVideoType;        //远端环回测试类型

    u8                  m_byCPUUsage;                       //CPU使用率
    u8                  m_abyReserved2[3];
    u32                 m_dwPhysicMem;                      //终端物理内存大小(按字节计算，主机序)
    u32                 m_dwUsedMem;                        //终端已使用内存大小(按字节计算，主机序)
    u32                 m_dwFreeMem;                        //终端空闲内存大小(按字节计算，主机序)

public:
    TTerStatus          m_tMtStatus;                        //终端状态
    TSnapInfo           m_tSnapInfo;                        //快照信息

    EmVideoType         m_aaDualCap[2][MT_MAXNUM_VIDSOURCE];//双流能力

    TCallInfoStatistics m_tMtStatics;                       //统计信息
};

namespace kdvmtc
{

    class CMt
    {
    public:
        CMt();
        CMt(u8 byMcuID, u16 wMtID, LPCSTR lptrMtAlias = NULL,
            LPCSTR lptrE164ID = NULL);
        CMt(const CMt &cMt);
        virtual ~CMt();

    public:
        //清空
        void SetNull(void);

        //判断是否为空
        inline BOOL32 IsNull(void)
        { return ( m_byMcuId == 0 && m_wMtId == 0 ); }

        //设置MCU ID
        inline void SetMcuID(u8 byMcuID) { m_byMcuId = byMcuID; }

        //获取MCU ID
        inline u8 GetMcuID(void) const { return m_byMcuId; }

        //设置MT ID
        inline void SetMtID(u16 wMtID) { m_wMtId = wMtID; }

        //获取MT ID
        inline u16 GetMtID(void) const { return m_wMtId; }

        //设置终端别名
        inline void SetMtAlias(LPCSTR lptrAlias)
        {
            memset( m_szMtAlias, 0, sizeof (m_szMtAlias) );
            if ( lptrAlias != NULL )
            {
                strncpy( m_szMtAlias, lptrAlias, sizeof (m_szMtAlias) - 1 );
            }
        }

        //获取终端别名
        inline LPCSTR GetMtAlias(void) const { return m_szMtAlias; }

        //设置终端E.164号码
        inline void SetMtE164ID(LPCSTR lptrE164ID)
        {
            memset( m_szMtE164ID, 0, sizeof (m_szMtE164ID) );
            if ( lptrE164ID != NULL )
            {
                strncpy( m_szMtE164ID, lptrE164ID, sizeof (m_szMtE164ID) - 1 );
            }
        }

        //获取终端E.164号码
        inline LPCSTR GetMtE164ID(void) const { return m_szMtE164ID; }

        //设置是否哑音
        inline void SetDumb(BOOL32 bDumb) { m_byDumb = (bDumb ? 1 : 0); }

        //判断是否哑音
        inline BOOL32 IsDumb(void) const
        { return ( m_byDumb > 0 ? TRUE: FALSE ); }

        //设置合并终端号
        inline void SetID(u8 byMcuID, u16 wMtID)
        {
            m_byMcuId = byMcuID;
            m_wMtId = wMtID;
        }

        //设置合并终端号
        inline void SetID(u32 dwMtID)
        {
            m_byMcuId = HIWORD(LOBYTE(dwMtID));
            m_wMtId = LOWORD(dwMtID);
        }

        //获取合并终端号
        inline u32 GetID(void) const
        {
            return MAKELONG(m_wMtId, MAKEWORD(m_byMcuId, 0));
        }

        //比较
        inline BOOL32 operator==(const CMt &cMt) const
        { return ( m_byMcuId == cMt.m_byMcuId && m_wMtId == cMt.m_wMtId ); }

        //比较
        inline BOOL32 operator==(const TMtId &tMt) const
        { return ( m_byMcuId == tMt.byMcuNo && m_wMtId == tMt.byTerNo ); }

        //比较
        inline BOOL32 operator==(const TMtInfo &tMt) const
        { return ( m_byMcuId == tMt.tLabel.byMcuNo && m_wMtId == tMt.tLabel.byTerNo ); }

        //比较
        inline BOOL32 operator!=(const CMt &cMt) const
        { return ( m_byMcuId != cMt.m_byMcuId || m_wMtId != cMt.m_wMtId ); }

        //比较
        inline BOOL32 operator!=(const TMtId &tMt) const
        { return ( m_byMcuId != tMt.byMcuNo || m_wMtId != tMt.byTerNo ); }

        //比较
        inline BOOL32 operator!=(const TMtInfo &tMt) const
        { return ( m_byMcuId != tMt.tLabel.byMcuNo || m_wMtId != tMt.tLabel.byTerNo ); }

        //赋值
        CMt& operator=(const CMt &cMt);

        //赋值
        CMt& operator=(const TMtId &tMt);

        //赋值
        CMt& operator=(const TMtInfo &tMt);

        //获取合并终端号(静态函数，与本类内部变量无关)
        inline static u32 GetID(u8 byMcuID, u16 wMtID)
        { return MAKELONG(wMtID, MAKEWORD(byMcuID, 0)); }

    public:
        //打印
        void Print(void);

    private:
        u8  m_byMcuId;                          //MCU ID
        u8  m_byDumb;                           //哑音状态(MC时有效) 哑音: 1; 未哑音: 0
        u16 m_wMtId;                            //MT ID
        s8  m_szMtAlias[MT_MAX_H323ALIAS_LEN];  //终端别名
        s8  m_szMtE164ID[MT_MAX_E164NUM_LEN];   //E.164号码
    };

}



///////////////////////////////////////////////////////////////////////////////
//  3. 矩阵参数
///////////////////////////////////////////////////////////////////////////////
class CMatrix
{
public:
    CMatrix();
    virtual ~CMatrix();

public:
    //清空
    void SetNull(void);

    //设置当前内部视频源
    inline void SetCurInnerVSource(EmMtVideoPort emPort)
    {
        m_emCurInnerVSource = ( emPort < emMtExternalVid ? emPort : emMtC1Vid );
    }

    //获取当前内部视频源
    inline EmMtVideoPort GetCurInnerVSource(void) const
    { return m_emCurInnerVSource; }

    //设置当前外接矩阵端口
    inline void SetCurOuterPort(EmMtVideoPort emPort)
    {
        m_byCurOuterVPort = ( emPort < emMtExternalVid ? -1 : (u8)(emPort - emMtExternalVid) );
    }

    //获取当前外接矩阵端口
    inline u8 GetCurOuterPort(void) const { return m_byCurOuterVPort; }

    //设置当前外接矩阵方案
    inline void SetCurOuterScheme(u8 bySchemeNo)
    { m_byCurOuterScheme = bySchemeNo; }

    //获取当前外接矩阵方案
    inline u8 GetCurOuterScheme(void) const { return m_byCurOuterScheme; }

    //设置外接矩阵的能力级
    inline void SetOuterMatrixCap(u8 byCap) { m_byOuterMatrixCap = byCap; }

    //获取外接矩阵的能力级
    inline u8 GetOuterMatrixCap(void) const { return m_byOuterMatrixCap; }

public:
    //打印
    void Print(void);

protected:
    EmMtVideoPort                   m_emCurInnerVSource;    //当前内部视频源
    u8                              m_byCurOuterVPort;      //当前外接矩阵端口
    u8                              m_byCurOuterScheme;     //当前外接矩阵方案
    u8                              m_byOuterMatrixCap;     //外接矩阵的能力级
    u8                              m_byReserved1;

public:
    vector<TVideoSourceInfo>        m_vctInnerVSourceInfo;  //内部视频源的信息
    vector<TAVInnerMatrixScheme>    m_vctAVMatrixScheme;    //全部内部矩阵方案

    TExternalMatrixInfo             m_tOuterMatrixInfo;     //外接矩阵信息
    vector<TVideoSourceInfo>        m_vctOuterMatrixName;   //外接矩阵端口名
};


///////////////////////////////////////////////////////////////////////////////
//  4. 监控参数
///////////////////////////////////////////////////////////////////////////////
typedef struct tagMtcMonitorParam
{
public:
    tagMtcMonitorParam() { SetNull(); }

    //清空
    inline void SetNull(void) { memset( this, 0, sizeof (tagMtcMonitorParam) ); }

public:
    //打印
    void Print(void);

public:
    EmSite              m_emSite;                           //本地/远端
    u8                  m_abyRealPayload[2];                //视频和音频的真实载荷类型
    u8                  m_abyDynamicPayload[2];             //视频和音频的动态载荷类型
    TEncryptKey         m_atEncryptKey[2];                  //视频和音频的密钥
} TMtcMonitorParam;

class CMonitorParam
{
public:
    CMonitorParam();
    virtual ~CMonitorParam();

public:
    //清空
    void SetNull(void);

public:
    //打印
    void Print(void);

public:
    TMtcMonitorParam        m_atMonitorParam[2];            //本地/远端 监控参数
    TVideoEncodeParameter   m_tPCDualParam;                 //PC双流参数
    u8                      m_byPCDynamicPayload;           //PC双流动态载荷
    TEncryptKey             m_tPCDualEncryptKey;            //PC双流秘钥
    TIPTransAddr            m_tRTPSendAddr;                 //RTP发送地址
    TIPTransAddr            m_tRTCPSendAddr;                //RTCP发送地址
};


///////////////////////////////////////////////////////////////////////////////
//  5. VOD参数
///////////////////////////////////////////////////////////////////////////////
class CVODParam
{
public:
    CVODParam();
    virtual ~CVODParam();

public:
    //清空
    void SetNull(void);

    //设置VOD点播状态
    inline void SetVODState(EmVODState emState) { m_emVODState = emState; }

    //获取VOD点播状态
    inline EmVODState GetVODState(void) const { return m_emVODState; }

    //设置当前文件播放状态
    inline void SetCurFileState(EmAction emState) { m_emCurFileState = emState; }

    //获取当前文件播放状态
    inline EmAction GetCurFileState(void) const { return m_emCurFileState; }

    //设置播放总时长(主机序)
    inline void SetDuration(u32 dwDuration) { m_dwDuration = dwDuration; }

    //获取播放总时长(主机序)
    inline u32 GetDuration(void) const { return m_dwDuration; }

    //设置已播放时间(主机序)
    inline void SetProgress(u32 dwProgress) { m_dwProgress = dwProgress; }

    //获取已播放时间(主机序)
    inline u32 GetProgress(void) const { return m_dwProgress; }

public:
    //打印
    void Print(void);

protected:
    EmVODState                      m_emVODState;           //VOD点播状态
    EmAction                        m_emCurFileState;       //当前文件的播放的状态
    u32                             m_dwDuration;           //播放总时长(毫秒，主机序)
    u32                             m_dwProgress;           //已播放时间(毫秒，主机序)

public:
    vector<TVODFileNameInfo>        m_vctCurDirFileList;    //当前目录下的所有文件名和目录
    TVODFileInfo                    m_tCurSelectFile;       //指定文件的详细信息
    TVODFileNameInfo                m_tCurSelectFileName;   //指定文件的名称信息
};


///////////////////////////////////////////////////////////////////////////////
//  6. 点对点会议状态
///////////////////////////////////////////////////////////////////////////////
class CP2PConfStatus
{
public:
    CP2PConfStatus();
    virtual ~CP2PConfStatus();

public:
    //清空
    void SetNull(void);

    //设置点对点会议状态
    inline void SetInConf(BOOL32 bInConf) { m_bInConf = bInConf; }

    //获取点对点会议状态
    inline BOOL32 IsInConf(void) const { return m_bInConf; }

    //设置呼叫状态
    inline void SetInCalling(BOOL32 bInCalling) { m_bInCalling = bInCalling; }

    //获取呼叫状态
    inline BOOL32 IsInCalling(void) const { return m_bInCalling; }

    //设置是否主终端
    inline void SetMaster(BOOL32 bMaster) { m_bMaster = bMaster; }

    //判断是否主终端
    inline BOOL32 IsMaster(void) const { return m_bMaster; }

    //设置自身
    inline void SetLocalMt(const kdvmtc::CMt &cMt) { m_cMtLocal = cMt; }

    //获取自身
    inline const kdvmtc::CMt& GetLocalMt(void) const { return m_cMtLocal; }

    //设置对端
    inline void SetRemoteMt(const kdvmtc::CMt &cMt) { m_cMtRemote = cMt; }

    //获取对端
    inline const kdvmtc::CMt& GetRemoteMt(void) const { return m_cMtRemote; }

    //设置呼叫参数
    inline void SetCallParam(const TDialParam &tParam) { m_tCallParam = tParam; }

    //获取呼叫参数
    inline const TDialParam& GetCallParam(void) const { return m_tCallParam; }

public:
    //打印
    void Print(void);

protected:
    BOOL32      m_bInConf;      //是否在点对点会议中
    BOOL32      m_bInCalling;   //是否在呼叫中
    BOOL32      m_bMaster;      //(入会后)是否主终端

    kdvmtc::CMt m_cMtLocal;     //自身
    kdvmtc::CMt m_cMtRemote;    //对端
    TDialParam  m_tCallParam;   //呼叫参数
};


///////////////////////////////////////////////////////////////////////////////
//  7. 多点会议状态
///////////////////////////////////////////////////////////////////////////////

//MCU会议列表
typedef struct tagJoinConfList
{
public:
    tagJoinConfList() { memset( this, 0, sizeof (tagJoinConfList) ); }

public:
    //清空
    void SetNull(void) { memset( this, 0, sizeof (tagJoinConfList) ); }

    //设置会议号
    void SetConfID(LPCSTR lptrConfID);

    //获取会议号
    inline const u8* GetConfID(void) const { return m_abyConfID; }

    //获取会议号字符串
    void GetConfIdString(LPSTR lptrConfId, s32 nBufLen) const;

    //设置会议名
    inline void SetConfName(LPCSTR lptrConfName)
    {
        memset( m_szConfName, 0, sizeof (m_szConfName) );
        if ( lptrConfName != NULL )
        {
            strncpy( m_szConfName, lptrConfName, sizeof (m_szConfName) - 1 );
        }
    }

    //获取会议名
    inline LPCSTR GetConfName(void) const { return m_szConfName; }

public:
    //打印
    void Print(void);

protected:
    u8  m_abyConfID[MT_MAX_CONF_ID_LEN];    //Conf ID
    s8  m_szConfName[MT_MAX_CONF_NAME_LEN]; //会议名
} TJoinConfList;

//多点会议状态
class CMultiConfStatus : public TMtConfInfo
{
public:
    CMultiConfStatus();
    virtual ~CMultiConfStatus();
    CMultiConfStatus(const CMultiConfStatus &cConf);

public:
    //清空
    void SetNull(void);

    //重载运算符, 用新的会议信息更新内容
    const CMultiConfStatus& operator+=(const TMtConfInfo &tInfo);

    //赋值运算符重载
    const CMultiConfStatus& operator=(const CMultiConfStatus &cConf);

    //获取主席终端
    const kdvmtc::CMt& GetChairman(void) const;

    //获取发言终端
    const kdvmtc::CMt& GetSpeaker(void) const;

    //获取轮询终端列表
    BOOL32 GetPollMtList(vector<kdvmtc::CMt> &vctMtList) const;

    //获取终端
    const kdvmtc::CMt& GetMt(const TMtId &tMt) const;

    //获取终端
    const kdvmtc::CMt& GetMt(const TMtInfo &tMt) const;

    //获取终端
    const kdvmtc::CMt& GetMt(u8 byMcuID, u16 wMtID) const;

    //获取终端
    const kdvmtc::CMt& GetMt(u32 dwID) const;

    //设置终端
    BOOL32 SetMt(const kdvmtc::CMt &cMt);

    //设置是否在多点会议中
    inline void SetInConf(BOOL32 bInConf) { m_bInConf = bInConf; }

    //判断是否在多点会议中
    inline BOOL32 IsInConf(void) const { return m_bInConf; }

    //设置是否申请混音
    inline void SetApplyMixing(BOOL32 bApply) { m_bApplyMixing = bApply; }

    //判断是否申请混音
    inline BOOL32 IsApplyMixing(void) const { return m_bApplyMixing; }

    //设置是否获取了会议信息
    inline void SetGetConfInfo(BOOL32 bGet) { m_bGetConfInfo = bGet; }

    //判断是否获取了会议信息
    inline BOOL32 IsGetConfInfo(void) const { return m_bGetConfInfo; }

    //设置会议是否加密
    inline void SetConfEncrypted(BOOL32 bEncrypted)
    { m_bConfEncrypted = bEncrypted; }

    //判断会议是否加密
    inline BOOL32 IsConfEncrypted(void) const { return m_bConfEncrypted; }

    //设置当前视频源终端
    inline void SetVideoSource(const TMtId &tMt) { m_tVideoSrc = tMt; }

    //获取当前视频源终端
    const kdvmtc::CMt& GetVideoSource(void) const;

    //设置会议延长时间
    inline void SetDelayTime(u16 wTime) { m_wDelayTime = wTime; }

    //获取会议延长时间
    inline u16 GetDelayTime(void) const { return m_wDelayTime; }

//MC接口
public:
    //设置是否激活MC功能
    inline void SetMCActivate(BOOL32 bActivate) { m_bMCActivate = bActivate; }

    //判断是否激活MC功能
    inline BOOL32 IsMCActivate(void) const { return m_bMCActivate; }

    //设置当前MC模式
    inline void SetMCMode(EmMCMode emMode) { m_emMCMode = emMode; }

    //获取当前MC模式
    inline EmMCMode GetMCMode(void) const { return m_emMCMode; }

    //设置MC在当前会议中是否可用
    inline void SetMCEnabledInConf(BOOL32 bEnabled)
    { m_bMCEnabledInConf = bEnabled; }

    //判断MC在当前会议中是否可用
    inline BOOL32 IsMCEnabledInConf(void) const { return m_bMCEnabledInConf; }

    //设置MC是否自动画面合成
    inline void SetMCAutoCP(BOOL32 bAutoCP) { m_bMCAutoCP = bAutoCP; }

    //判断MC是否自动画面合成
    inline BOOL32 IsMCAutoCP(void) const { return m_bMCAutoCP; }

    //设置MC时轮询信息
    inline void SetMCPollInfo(const TMtPollInfo &tInfo)
    { m_tMCPollInfo = tInfo; }

    //获取MC时轮询信息
    inline const TMtPollInfo& GetMCPollInfo(void) const
    { return m_tMCPollInfo; }

    //设置MC画面合成风格
    inline void SetMCCPStyle(EmInnerVMPStyle emStyle)
    { m_emMCCPStyle = emStyle; }

    //获取MC画面合成风格
    inline EmInnerVMPStyle GetMCCPStyle(void) const { return m_emMCCPStyle; }

    //设置MC远遥终端
    inline void SetMCRemoteControlMt(const TMtId &tMt)
    { m_tMCRemoteControlMt = tMt; }

    //获取MC远遥终端
    const kdvmtc::CMt& GetMCRemoteControlMt(void) const;

//打印
public:
    //打印
    void Print(void);

public:
    vector<kdvmtc::CMt>         m_vctMtList;        //与会终端列表
    vector<kdvmtc::CMt>         m_vctApplyChairman; //申请主席的终端列表
    vector<kdvmtc::CMt>         m_vctApplySpeaker;  //申请发言的终端列表
    vector<kdvmtc::CMt>         m_vctApplyMixing;   //申请混音的终端列表
    vector<TJoinConfList>       m_vctJoinConfList;  //可选择加入会议列表

protected:
    BOOL32                      m_bInConf;          //是否在多点会议中
    BOOL32                      m_bApplyMixing;     //是否申请混音
    BOOL32                      m_bGetConfInfo;     //是否获取了会议信息
    BOOL32                      m_bConfEncrypted;   //会议是否加密

    TMtId                       m_tVideoSrc;        //当前视频源终端
    u16                         m_wDelayTime;       //会议延长时间(终端不做记录，所以MTC发出指令后记录时间)

    BOOL32                      m_bMCActivate;      //MC是否激活
    EmMCMode                    m_emMCMode;         //当前MC模式
    BOOL32                      m_bMCEnabledInConf; //MC在当前会议中是否可用
    TMtPollInfo                 m_tMCPollInfo;      //MC时轮询信息
    BOOL32                      m_bMCAutoCP;        //MC是否自动画面合成
    EmInnerVMPStyle             m_emMCCPStyle;      //MC画面合成风格

public:
    TMtId                       m_atMCCPMember[6];  //MC画面合成成员

protected:
    TMtId                       m_tMCRemoteControlMt;   //MC远遥终端

private:
    static kdvmtc::CMt          s_cNullMt;
};

///////////////////////////////////////////////////////////////////////////////
//  8. 向界面发送消息的结构
///////////////////////////////////////////////////////////////////////////////

//发送给上层的消息结构，在消息的WPARAM是指向此结构的指针
typedef struct tagMtclibParam
{
    tagMtclibParam() : m_pbyMsgBody(NULL), m_nMsgBodySize(0),
                       m_dwErrorCode(0) {}

    u8      *m_pbyMsgBody;          //消息体
    s32     m_nMsgBodySize;         //消息体长度
    BOOL32  m_bTimeout;             //是否超时
    u32     m_dwErrorCode;          //错误码
    u16     m_wTimeout;             //超时事件
} TMtclibParam;


///////////////////////////////////////////////////////////////////////////////
//  b. LIB内部使用结构
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//  1. 消息发送类封装，用于发送消息存储队列
///////////////////////////////////////////////////////////////////////////////
typedef struct tagSendCMessage
{
public:
    tagSendCMessage();

    tagSendCMessage(const tagSendCMessage &tMsg);

    //清空
    void SetNull(void);

    //设置消息类型
    inline void SetMsgType(EMSendMsgType emType) { m_enumMsgType = emType; }

    //获取消息类型
    inline EMSendMsgType GetMsgType(void) const { return m_enumMsgType; }

    //设置对端节点
    inline void SetDstNode(u32 dwDstNode) { m_dwDstNode = dwDstNode; }

    //获取对端节点
    inline u32 GetDstNode(void) const { return m_dwDstNode; }

    //设置对端IID
    inline void SetDstIID(u32 dwDstIID) { m_dwDstIID = dwDstIID; }

    //获取对端IID
    inline u32 GetDstIID(void) const { return m_dwDstIID; }

    //设置超时时间
    inline void SetTimeout(s32 nTimeout) { m_nTimeout = nTimeout; }

    //获取超时时间
    inline s32 GetTimeout(void) const { return m_nTimeout; }

    //设置是否允许撤销
    inline void SetCancelEnabled(BOOL32 bEnable) { m_bCancelEnabled = bEnable; }

    //判断是否允许撤销
    inline BOOL32 IsCancelEnabled(void) const { return m_bCancelEnabled; }

    //设置发送事件
    inline void SetEvent(u16 wEvent) { m_wEvent = wEvent; }

    //获取发送事件
    inline u16 GetEvent(void) const { return m_wEvent; }

    //设置第一等待事件
    inline void SetWaitEvent1(u16 wEvent) { m_wWaitEvent1 = wEvent; }

    //获取第一等待事件
    inline u16 GetWaitEvent1(void) const { return m_wWaitEvent1; }

    //设置第二等待事件
    inline void SetWaitEvent2(u16 wEvent) { m_wWaitEvent2 = wEvent; }

    //获取第二等待事件
    inline u16 GetWaitEvent2(void) const { return m_wWaitEvent2; }

    //设置消息体
    void SetMsgBody(u8 *pbyMsg = NULL, u16 wLen = 0);

    //添加消息体
    void CatMsgBody(u8 *pbyMsg, u16 wLen);

    //清空消息体
    inline void ClearMsgBody(void)
    {
        memset( m_abyMsg, 0, sizeof (m_abyMsg) );
        m_wMsgLen = 0;
    }

    //获取消息体
    inline const void* GetMsgBody(void) const { return m_abyMsg; }

    //获取消息体长度
    inline u16 GetBodyLen(void) const { return m_wMsgLen; }

protected:
    EMSendMsgType   m_enumMsgType;
    u32             m_dwDstNode;
    u32             m_dwDstIID;
    s32             m_nTimeout;
    BOOL32          m_bCancelEnabled;
    u16             m_wEvent;
    u16             m_wWaitEvent1;
    u16             m_wWaitEvent2;
    u16             m_wMsgLen;
    u8              m_abyMsg[MAX_MSG_LEN - 28];
} TSendCMessage;


#endif//_MTCLIBSTRUCT_20070420_H_
