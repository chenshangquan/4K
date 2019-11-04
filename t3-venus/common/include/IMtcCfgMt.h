/*******************************************************************************
 *  模块名   : MtcLib                                                          *
 *  文件名   : IMtcCfgMt.h													   *
 *  相关文件 :                                                                 *
 *  实现功能 : 提供配置信息操作的接口                                          *
 *  作者     : 刘瑞飞                                                          *
 *  版本     : V4.0  Copyright(c) 2003 - 2006 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  修改记录:                                                                  *
 *    日  期    版本        修改人      修改内容                               *
 *  2006/2/21  4.0         刘瑞飞       注视                                   *
 *                                                                             *
 *******************************************************************************/

#ifndef __IMTCCFGMT_H__
#define __IMTCCFGMT_H__

#include "dispevent.h"
#include "mtstruct.h"
#include <vector>
using std::vector;


typedef struct tagMcDualParamCfg
{
	EmVideoFormat	emVidFormat;
	EmVideoResolution emVidRes;
	u32				  dwFrame;
	u32              dwRemain1;
	u32				dwRemain2;
	tagMcDualParamCfg() { emVidFormat =  emVEnd; emVidRes = emVResEnd; 
							dwFrame = 0; dwRemain1 = 0; dwRemain2 = 0;}
}TMcDualParamCfg;


class IMtcCfgMt : public CDispEvent
{
public:
    /*函数名： EmLanguage& GetLanguage
    功    能： 获取终端和OSD当前使用的语言信息
    参    数： 
    返 回 值： const EmLanguage&
    说    明： */
	virtual const EmLanguage& GetLanguage() const = 0;
	virtual u16 UpdateLanguage(const EmLanguage& em) = 0;

    /*函数名： ResetSystem
    功    能： 将配置重新设置成出厂默认值
    参    数： 
    返 回 值： BOOL32
    说    明： */
	virtual BOOL32 ResetSystem() = 0;

	/*功能	本地信息配置
	参数	cfg		配置信息
	返回值	配置信息
			成功返回0;失败返回错误码
	说明	无*/
	virtual const TH323Cfg& GetH323Cfg() const = 0;
	virtual u16 UpdateH323Cfg(const TH323Cfg& cfg) = 0;
	virtual u16 ResetH323Cfg() = 0;
	virtual BOOL IsGKSupportDN() const = 0;
	virtual void ResetIsGKSupportDN() = 0;
	virtual const s8* GetGKDomainName() const = 0;
	virtual u16 UpdateGKDomainName(s8 achGKDomainName[MT_MAX_H323GKSERVER_NAME_LEN]) = 0;
	/*功能	网络信息配置
	参数	cfg		配置信息
	返回值	配置信息
			成功返回0;失败返回错误码
	说明	无*/
	virtual const TEthnetInfo& GetEthnetCfg(u8 byIndex) const = 0;
	virtual u16 UpdateEthnetCfg(u8 byIndex, const TEthnetInfo& cfg) = 0;
	virtual u16 ResetEthnetCfg( u8 byIndex ) = 0;
	/*功能	H.460配置
	参数	cfg		配置信息
	返回值	配置信息
			成功返回0;失败返回错误码
	说明	无*/
//	virtual const TH460Info& GetH460Cfg() const = 0;
//	virtual u16 UpdateH460Cfg(const TH460Info& cfg) = 0;
//	virtual u16 ResetH460Cfg() = 0;
	/*功能	呼叫信息配置
	参数	cfg		配置信息
	返回值	配置信息
			成功返回0;失败返回错误码
	说明	无*/
	virtual const TUserCfg& GetUserCfg() const = 0;
	virtual u16 UpdateUserCfg(const TUserCfg& cfg) = 0;
	virtual u16 ResetUserCfg() = 0;
	/*功能	视频信息配置
	参数	byIndex	索引号
			cfg		配置信息
	返回值	配置信息
			成功返回0;失败返回错误码
	说明	无*/	
	virtual const TVideoParam& GetVideoCfg(EmVideoType emType) const = 0;
	virtual u16 UpdateVideoCfg(EmVideoType emType, const TVideoParam& cfg) = 0;
	virtual u16 ResetVideoCfg(EmVideoType emType, EmMtModel emModel) = 0;
	virtual u16 UpdateH264FomateSel(u32 dwSel) = 0;

    /*函数名： TVideoParam& GetPCVideoCfg
    功    能： PC双流的配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TVideoParam& GetPCVideoCfg() const = 0;
	virtual u16 UpdatePCVideoCfg(const TVideoParam& cfg) = 0;
	virtual u16 ResetPCVideoCfg(EmMtModel emModel) = 0;

    /*函数名： TOsdCfg& GetOSDCfg
    功    能： 显示配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TOsdCfg& GetOSDCfg() const = 0;
	virtual u16 UpdateOSDCfg(const TOsdCfg& cfg) = 0;
	virtual u16 ResetOSDCfg() = 0;

    /*函数名： TE1Config& GetE1Cfg
    功    能： E1 配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TE1Config& GetE1Cfg() const = 0;
	virtual u16 UpdateE1Cfg(const TE1Config& cfg) = 0;
	virtual u16 DeleteE1Cfg() = 0;
	virtual u16 ResetE1Config() = 0;
	
    /*函数名： TSerialCfg& GetSerialCfg
    功    能： 串口配置信息
    参    数： EmSerialType emType
    返 回 值： virtual const 
    说    明： */
	virtual const TSerialCfg& GetSerialCfg(EmSerialType emType) const = 0;
	virtual u16 UpdateSerialCfg(EmSerialType emType, const TSerialCfg& cfg) = 0;
	virtual u16 ResetSerialCfg(EmSerialType emType) = 0;
	virtual EmSerialType GetSerialIndex() = 0;
    /*函数名： TplArray<TRouteCfg>& GetAllRouteCfg
    功    能： 路由配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TplArray<TRouteCfg>& GetAllRouteCfg() const = 0;
	virtual u16 AddRouteCfg(const TRouteCfg& cfg) = 0;
	virtual u16 DelRouteCfg(const TRouteCfg& cfg) = 0;

    /*函数名： TPPPOECfg& GetPPPOECfg
    功    能： PPPoE配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TPPPOECfg& GetPPPOECfg() const = 0;
	virtual u16 UpdatePPPOECfg(const TPPPOECfg& cfg) = 0;
	virtual u16 ResetPPPoECfg() = 0;

    /*函数名： TSNMPCfg& GetSNMPCfg
    功    能： SNMP配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TSNMPCfg& GetSNMPCfg() const = 0;
	virtual u16 UpdateSNMPCfg(const TSNMPCfg& cfg) = 0;
	virtual u16 ResetSNMPCfg() = 0;

    /*函数名： TIPQoS& GetIPQoS
    功    能： Qos配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TIPQoS& GetIPQoS() const = 0;
	virtual u16 UpdateIPQos(const TIPQoS& cfg) = 0;
	virtual u16 ResetIPQos() = 0;

    /*函数名： TEmbedFwNatProxy& GetFireWallCfg
    功    能： 防火墙配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TEmbedFwNatProxy& GetFireWallCfg() const = 0;
	virtual u16 UpdateFireWallCfg(const TEmbedFwNatProxy& cfg) =0;
	virtual u16 ResetFireWallCfg() = 0;
	virtual u8  GetProxyDomainInd() = 0;
	virtual BOOL IsFirewallSupportDN() const = 0;
	virtual void ResetIsFirewallSupportDN() = 0;
	virtual const s8* GetFirewallDomainName() const = 0;
//	virtual u16 UpdateFirewallDomainName(s8 achFirewallDomainName[MT_MAX_H323GKSERVER_NAME_LEN]) = 0;
    /*函数名： u16& GetUDPBasePort
    功    能： 端口配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const u16& GetUDPBasePort() const = 0;
	virtual const u16& GetTCPBasePort() const = 0;
	virtual u16 UpdateCommonBasePort(u16 wUDPPort, u16 wTCPPort) = 0;
	virtual u16 ResetCommonBasePort() = 0;

    /*函数名： TNATMapAddr& GetNapMapAddr
    功    能： 静态nap影射配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TNATMapAddr& GetNapMapAddr() const = 0;
	virtual u16 UpdateNapMapAddr(const TNATMapAddr& cfg) = 0;
	virtual u16 ResetNapMapAddr() = 0;

	virtual const TLostPackResend& GetRetransCfg() const = 0;
	virtual u16 UpdateRetransCfg(const TLostPackResend& cfg , BOOL IsCustomized = 0) = 0;
	virtual u16 ResetRetransCfg() = 0;

	//音质优先
	virtual const u32& GetSoundPriority() const = 0;
	virtual u16 UpdateSoundPriority(u32 dwSoundPriority) = 0;
	virtual u16 ResetSoundPriority() = 0;

    /*函数名： TStreamMedia& GetStreamCfg
    功    能： 流媒体配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TStreamMedia& GetStreamCfg() const = 0;
	virtual u16 UpdateStreamCfg(const TStreamMedia& cfg) = 0;
	virtual u16 ResetStreamCfg() = 0;

    /*函数名： TAVPriorStrategy& GetAVPriorCfg
    功    能： 视频优选协议配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TAVPriorStrategy& GetAVPriorCfg() const = 0;
	virtual u16 UpdateAVPriorCfg(const TAVPriorStrategy& cfg) = 0;
	virtual u16 ResetAVPriorCfg() = 0;

    /*函数名： TCameraCfg* GetCameraCfg
    功    能： 摄像头配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TCameraCfg* GetCameraCfg() const = 0;
	virtual u16 UpdateCameraCfg(u8 byIndex, const TCameraCfg& cfg) = 0;
	virtual const vector<TCameraTypeInfo>& GetCamTypeInfo() const = 0;
	virtual u16 ResetCameraCfg(u8 byIndex) = 0;

    /*函数名： TVideoStandard& GetVStandard
    功    能： 视频制式配置信息
    参    数： EmVideoType emType
               BOOL32 bIsInPort
    返 回 值： virtual const 
    说    明： */
	virtual const TVideoStandard& GetVStandard(EmVideoType emType, BOOL32 bIsInPort) const = 0;

//	virtual const TVideoStandard& GetVStandard(EmVideoType emType, BOOL32 bIsInPort) coideoStandard& tVideoStandard) = 0;
	virtual u16 UpdateVStandard(const TVideoStandard& tVideoStandard) = 0;
	
    /*函数名： TImageAdjustParam& GetImageAdjustCfg
    功    能： 图像调节配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
//	virtual const TImageAdjustParam& GetImageAdjustCfg(u8 byIndex) const = 0;
//	virtual u16 UpdateImageAdjustCfg(const u8 byIndex, const TImageAdjustParam& cfg) = 0;
//	virtual u16 ResetImageAdjustCfg(const u8 byIndex, EmMtModel emModel) = 0;
	virtual const TImageAdjustParam* GetImageAdjustCfg() const = 0;
	virtual u16 UpdateImageAdjustCfg(const u8 byIndex, const TImageAdjustParam* pCfg) = 0;
	virtual u16 ResetImageAdjustCfg(const u8 byIndex, EmMtModel emModel) = 0;
	//pmct
	virtual u16 UpdateImageAdjustCfg(const TImageAdjustParam& cfg) = 0;
	virtual u16 ResetImageAdjustCfg(EmMtModel emModel) = 0;

	//AEC配置
	virtual const BOOL32& IsAEC() const = 0;
	virtual u16 UpdateAEC(BOOL32 bEnable) = 0;
	//AGC配置
	virtual const BOOL32& IsAGC() const = 0;
	virtual u16 UpdateAGC(BOOL32 bEnable) = 0;
    //音频端口选择配置
    virtual const THdAudioPort& GetHDAudioPortCfg() const = 0;
    virtual u16 UpdateHDAudioPortCfg(const THdAudioPort& tAudioPort) = 0;	
	//ANS配置
	virtual const BOOL32& IsANS() const = 0;
	virtual u16 UpdateANS(BOOL32 bEnable) = 0;

	//输入声音
	virtual const u8& GetInputVol() const = 0;
	virtual u16 UpdateInputVol(u8 byVolume) = 0 ;
	//输出声音
	virtual const u8& GetOutputVol() const = 0;
	virtual u16 UpdateOutputVol(u8 byVolum) = 0;
	
    /*函数名： TBannerInfo& GetBannerInfo
    功    能： 横幅配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TBannerInfo& GetBannerInfo() const = 0;
	virtual u16 UpdateBannerInfo( TBannerInfo &tBanner, s8 *pContent = 0) = 0;
	virtual u16 ResetBannerInfo() = 0;
	virtual s8* GetBannerContent() = 0;
	//返回网关的IP地址（主机序）
	virtual const u32& GetGatewayIP() const = 0;
	//网关的IP(主机序)
	virtual u16 UpdateGatewayIP(u32 dwIP) = 0; 
	

	//设置CNS的IP 和 别名 2011-4-19 by yjj 
    virtual const TMtCnsParam& GetCnsInfo() const = 0; 
	virtual u16 UpdateCns(TMtCnsParam &tParam) = 0 ; 

	
    /*函数名： GetExMatrixCtrlType
    功    能： 矩阵控制配置信息
    参    数： 
    返 回 值： virtual EmSerialType& 
    说    明： */
	virtual EmSerialType& GetExMatrixCtrlType() = 0;
	virtual const TIPTransAddr& GetEXMatrixCtrlIp() = 0;
	//获取终端支持外部矩阵配置请求
	virtual u16 ReqExtenalMatrixCfg() = 0;
	//终端外部矩阵配置
	virtual u16 UpdateExtenalMatrixCfg(EmSerialType emType, const TIPTransAddr &tIPAddr) = 0;
	
	/*功能	请求全部配置信息
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 ReqAllCfg() = 0;

    /*函数名：  BOOL& GetVGAShowCfg
    功    能： VGA输出配置信息
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const  BOOL& GetVGAShowCfg() = 0 ;
	virtual u16 UpdateVGAShowCfg( BOOL32 bLocal ) = 0 ;
	
    /*函数名：  BOOL& GetVGAShowCfg
    功    能： 第二路视频是否输出到VGA
    参    数： 
    返 回 值： virtual const BOOL32&
    说    明： */
    virtual const BOOL32& GetSecondVideoToVGA() = 0;
    virtual u16 UpdateSecondVideoToVGA(BOOL32 bToVGA) = 0;

    /*函数名： GetMonitorService
    功    能： 自动切换为监控终端配置信息
    参    数： 
    返 回 值： virtual TMonitorService& 
    说    明： */
	virtual TMonitorService& GetMonitorService() = 0;
	virtual u16 UpdateMonitorService( TMonitorService& tMonService ) = 0;
	virtual BOOL32 IsEnablwMonitor() = 0;
	/*函数名： SendStaticPic
    功    能： 发送静态图片
    参    数： BOOL32 bSend  True 发送 / False 不发送
    返 回 值： virtual u16 
    说    明： */
	virtual u16 SendStaticPic(BOOL32 bSend) = 0;
    /*函数名： IsSendStaticPic
    功    能： 是否发送静态图片
    参    数： 
    返 回 值： virtual BOOL 
    说    明： */
	virtual inline BOOL32& IsSendStaticPic() = 0;
    
    // 获取终端硬件、操作系统、软件版本信息
    virtual const u8 GetHardwareVersion() = 0;
    virtual const u8 GetSubHardwareVersion() = 0;
    virtual const EmMtOSType GetMtOSType() = 0;
    virtual const s8* GetOSVersion() = 0;
    virtual const s8* GetSoftwareVersion() = 0;
	//获取终端Mac地址
	virtual const s8* GetMacAddr()=0;      

    // 设置PCMT视频源信息
    virtual u16 UpdatePcmtVidSource(const TCapType& cfg) = 0;
    // 获取PCMT视频源信息
    virtual const TCapType& GetPcmtVidSource() const = 0;
    // PCMT视频源信息置成默认值
    virtual u16 ResetPcmtVidSource() = 0;
	// 设置PCMT视频采集参数, 捕获图像宽度/高度
	virtual u16 UpdatePcmtCapParam(u16 wWidth, u16 wHeight) = 0;
    
    /*函数名： GetVGAOutCfg
    功    能： 8010c显示VGA或者video参数
    参    数： 
    返 回 值： TVgaOutCfg& 
    说    明： */
    virtual const TVgaOutCfg& GetVGAOutCfg() const = 0;
    virtual u16 UpdateVGAOutCfg(const TVgaOutCfg& cfg) = 0;
    virtual u16 ResetVGAOutCfg() = 0;

    // 双流码率比
    /*=============================================================================
    函 数 名:GetDualRatio
    功    能:获取双流比率
    参    数:无
    注    意:无
    返 回 值:双流比率结构
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/06/30  4.0     王昊    创建
    =============================================================================*/
    virtual const TDualRation& GetDualRatio(void) const = 0;
    /*=============================================================================
    函 数 名:UpdateDualRatio
    功    能:更新双流比率
    参    数:const TDualRation &tDualRatio      [in]    双流比率
    注    意:发送消息接口
    返 回 值:消息发送接口返回值
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/06/30  4.0     王昊    创建
    =============================================================================*/
    virtual u16 UpdateDualRatio(const TDualRation &tDualRatio) = 0;
    /*=============================================================================
    函 数 名:ResetDualRatio
    功    能:恢复双流比率默认值
    参    数:无
    注    意:发送消息接口
    返 回 值:消息发送接口返回值
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/06/30  4.0     王昊    创建
    =============================================================================*/
    virtual u16 ResetDualRatio(void) = 0;
    
    // mt设备能力指示
    virtual const TMtEquipmentCapset& GetMtEquipmentCapset() const = 0;
    // Mic增益
    virtual const u8 GetMicAdjust() const = 0;
    // Mic增益控制
    virtual u16 AdjustMic(const u8 byMicAdjust) = 0;
    // 回声抵消
	virtual const u32 GetAecAdjust() const = 0;
	virtual u16 AdjustAec(const u32 dwAecAdjust) = 0;
    // 设置使用或不使用DHCP服务
    virtual u16 UseDHCP(const BOOL32 bUseDHCP) = 0;
    virtual BOOL32& IsUseDHCP() = 0;

    // 获取DHCP IP
    virtual u16 GetDHCPIP() = 0;
    // 关闭DHCP 服务
    virtual u16 ShutDownDHCPIP() = 0;

    // 获取DNS服务器IP
    virtual u32_ip& GetDNSServer() = 0;
    // 设置DNS服务器IP
    virtual u16 SetDNSServer(u32_ip dwDNSServer) = 0;
    //是否有可用的DNS服务器（dhcp获取到的；手动输入的）
	virtual u8 IsUseDNS() = 0;

    // 内嵌mc配置
    virtual u16 UpdateInnerMcCfg(const TInnerMcCfg &tInnerMcCfg) = 0;
    virtual const TInnerMcCfg& GetInnerMcCfg() = 0;

	//内置扬声器音量配置
	virtual const EmMtLoudspeakerVal &GetSpeakerVal()=0;
	virtual u16 UpdateSpeakerVal(const EmMtLoudspeakerVal emLoudVal)=0;
	//LDAP 服务器配置
	virtual const CHAR* GetLdapServer()=0;
	virtual u16  UpdateLdapServer(const CString &strLdapServer)=0;
	
	//T2主视频配置命令  TRUE表示输出在Video 
	virtual const BOOL32&  GetMainVideoToVideo()=0;
	virtual u16     UpdateMainVideoToVideo(const BOOL32 bOutVideo)=0;

	//遥控器热键设置
	virtual const TRapidKey& GetRemoteHotKey()=0;
	virtual u16   UpdateRemoteHotKey(const TRapidKey& tHotKey)=0;
	
	//内置GK防火墙设置
	virtual const TInnerGKCfg& GetInnerGKCfg()=0;
	virtual u16   UpdateInnerGKCfg(const TInnerGKCfg& tInnerGkCfg)=0;
	virtual u16 UpdateMultiGKCfg(const TPxyIPCfg &tPxyIPCfg, u32 dwOperateType)=0;
	virtual const TPxyIPCfg * GetMultiGKConfig() = 0;
	
	//MTU 设置
	virtual const  u32& GetUseSliceCfg() = 0;
	virtual u16 UpdateUseSliceCfg(const u32 dwIsUseMTU) = 0;	
	virtual const u32& GetMTUCfg()=0;
	virtual u16   UpdateMTUCfg(const u32 dwMTU)=0;
	//系统时间
	virtual const TMtKdvTime& GetMTSysTime()=0;
	virtual u16   UpdateMTSysTime(const TMtKdvTime& tMTTime)=0;
	virtual const u32 &GetCfgH264FormatSel() const= 0;
	virtual u16 UpdateInnerProxyCfg(const TInnerProxyCfg &tInnerProxyCfg) = 0;
	
	virtual BOOL32 IsMasterIPConflict() = 0;
	virtual u32_ip GetMasterIP() = 0;
	virtual BOOL32 IsSlaveIPconflict() = 0;
	virtual u32_ip GetSlaveIP() = 0;
	virtual const TInnerProxyCfg& GetInnerProxyCfg() = 0;
	virtual const u8 GetNetMask() = 0;
	virtual u16 UpdateNetMask(u8 byNetMask) = 0;
	
	//fec
	virtual u16 UpdateFecTypeCfg(const TFecInfo &tFecInfo) = 0;
	virtual const TFecInfo &GetFecType() = 0;
	virtual u16 ResetFecTypeCfg() = 0;

	//网口模式
	virtual BOOL32 UpdateCfgEthMode( u32 dwCfgEthMode ) = 0;
	virtual u32& GetCfgEthMode() = 0;
	//telnet 密码
	virtual u16 UpdateTelnetPwd(const char *pTelnetPwd) = 0;
	virtual const char *GetTelnetPwd() = 0;
	//系统运行时间
	virtual BOOL32 QuerySystemRunTime() = 0;
	virtual u32& GetSystemRunTime() = 0;

	//重置系统
	//virtual BOOL32 ResetSystem() = 0;

// 	//wifi
// 	virtual u16 AddWifiCfg(TWiFiBSSIDCfg &tWiFiBSSIDCfg) = 0;
// 	virtual u16 DelWifiCfg(TWiFiBSSIDCfg &tWiFiBSSIDCfg) = 0;
// 	virtual u16 ConnectWifi(TWiFiBSSIDInfo &tWiFiBSSIDInfo) = 0;
// 	virtual u16 ConnectWifi(TWiFiBSSIDCfg &tWiFiBSSIDCfg) = 0;
// 	virtual u16 DisconnectWifi() = 0;
// 	virtual TWiFiLinkStatus &GetWifiCurrentLinkState() = 0;
// 	virtual u16 ScanWifiLink() = 0;
// 	virtual TWiFiBSSIDCfg *GetWifiCfgInfo() = 0;
// 	virtual TWiFiBSSIDInfo *GetWifiScanResult() = 0;
// 	virtual TWiFiNetCfg &GetWiFiNetIP() = 0;
// 	virtual u16 UpdateWifiNetIP(const TWiFiNetCfg &tWiFiNetCfg) = 0;
// 	virtual u16 ModifyWiFiItem(u32 nItem, const TWiFiBSSIDCfg &tWiFiBSSIDCfg) = 0;

	//Socket5
//	virtual TSocks5Proxy& GetSock5Info() = 0;
//    virtual u16 UpdateSock5Info(const TSocks5Proxy& cfg) = 0;

	/*函数名： GetOutputModel& UpdateOutputModel
    功    能： 输出方式
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const u32& GetOutputModel() const = 0;
	virtual u16 UpdateOutputModel(const u32 dwOutputModel) = 0;
// 	virtual u16 ResetOutputModel() = 0;
	
	//图像参数：图像增强   TRUE表示图像增强 
	virtual const BOOL32& GetImgEnhance() const = 0;
	virtual u16 UpdateImgEnhance(const BOOL32 &bEnable) = 0;
	virtual u16 ResetImgEnhance() = 0;

	//硬件软件编码模式 //081121 sq添加
	virtual u16 UpdateVideoEncodeDecodeModel(u8 model1, u8 model2 = 0, u32 param1 = 0, u32 param2 = 0) = 0;
	virtual u8  GetVideoEncodeDecodeModel() = 0;
	
	//电视机制式配置
	virtual const TVideoDisplayFrm& GetVidFrm() const = 0;
	virtual u16 UpdateVidFrm(const TVideoDisplayFrm& tVidDisplayFrm ) = 0;
	virtual u16 ResetVidDisplayFrm() = 0;

	//呼叫协议配置
	virtual const u8& GetCallProtocolCfg() const = 0;
	virtual u16 UpdateCallProtocol(const u8& byCallProtocol) = 0;
	virtual u16 UpdateCallProtocol(const TGuideCfg& tGuidCfg) = 0;
	virtual u16 ResetCallProtocol() = 0;

	//MTU
	virtual u16 ResetMTUCfg() = 0;
	//发送静态图片
	virtual u16 ResetSendStaticPic() = 0;
	//切包
	virtual u16 ResetUseSliceCfg() = 0;


	//当前网口
	virtual u16 UpdateCurrentEthNo(u8 No) = 0;
	virtual u8 GetCurrentEthNo() = 0;


	//E1 Unit
	virtual u16 UpdateE1Units(const TE1Unit* cfg) = 0;
	virtual	TE1Unit* GetE1Units() = 0;
	
	//E1 Group
	virtual u16 UpdateE1Group(const TE1Group* cfg, u8 E1Num) = 0;
	virtual TE1Group* GetE1Groups() = 0;
	virtual u8 GetE1GroupNum() = 0;

	//加密机
	virtual u16  UpdateUsePassThrough(u32 used) = 0;
	virtual u32  GetUsePassThrough() = 0;


	virtual u16 UpdateLastFrame(u32 dwBlue, u32 dwTime) = 0;
	virtual u32& GetLastFrameShow() = 0;
	virtual u32& GetLastFrameSwitchTime() = 0;
	
	virtual u16 UpdateShowApplication(u32 val) = 0;
	virtual BOOL32& IsShowApplication() = 0;

	virtual BOOL &IsResendCustomized() = 0;

	//内置mc双流格式
	virtual u16 UpdateMcDualParamCfg(TMcDualParamCfg& cfg)  = 0;
	virtual TMcDualParamCfg& GetMcDualParamCfg() = 0;

	//mtcbox
	virtual u16 UpdateMtcBoxCallCfg(TMtcBoxCallCfg &tCfg, u8 MtcBoxBtnNo) = 0;
	virtual vector<TMtcBoxCallCfg>& GetMtcBoxCallCfg() = 0;
	virtual TSipCfg& GetSipServiceCfg() = 0;
	virtual u16 ResetSipCfg() = 0;
	virtual u16 UpdateSipSrvInfo(const TSipCfg& tSipCfg) = 0;
	virtual const u32& GetVGAFhaseClock(u32 nIndex) = 0;
	virtual const u32& GetVGAFilterStatus(u32 nIndex) = 0;
	virtual const BOOL GetVGACtrlStatus(u32 nIndex) = 0;
	virtual u16 UpdateVGAPhaseClock(u32 anPos[3]) = 0;
	virtual u16 UpdateVGAFilterStatus(BOOL abStatus[3]) = 0;
	virtual u16 UpdateVGAPhaseClockDirctly(u32 anPos[3]) = 0;
	virtual u16 UpdateVGAFiltStatusDirctly(BOOL nStatus[3]) = 0;
}; // IMtCfgMt

#endif