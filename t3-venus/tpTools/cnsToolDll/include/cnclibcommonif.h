/*****************************************************************************
模块名      : 窗口向cns申请数据的接口模块
文件名      : cnclibcommonif.h
相关文件    : cnclib.h
文件实现功能: UI调用cnclib对cns的访问
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/23     1.0						创建
******************************************************************************/
#include "cnclib.h"
#include "cnsToolDll.h"
#ifndef CCNCLIBCOMMONIF_H
#define CCNCLIBCOMMONIF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CCnclibCommonIF
{
public:

	static CCnclibCommonIF* GetComIF();
	~CCnclibCommonIF();
	u16 LinkCns();
	/** 功能:  连接cns 
	*  @param[in] dwIp登录IP,nPort登录端口
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 connect( u32 dwIp, u32 dwPort);

	/** 功能:  断开cns 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16	DisConnect(); 
	
	/** 功能:  更新网络配置
	*  @param[in] tInfo 网络配置
	*  @return 成功返回0,失败返回非0错误码
	*  @remarks 
	*/
	u16 UpdateEthnetCfg( const TTPEthnetInfo& tInfo,EmTpIpNameNatSyn emTpIpType);

	u16 SaveWEthnetCfgCmd( const TTPWEthnetInfo& tTPWEthnetInfo, EmTpIpNameNatSyn emTpIpType );

	/** 功能:  CNS设置SIP注册配置 
	*  @param[in] tSipCfg Sip注册配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 CnsRegSipService( const TTPSipRegistrarCfg &tSipCfg );


	/** 功能:  CNS设置Gk注册配置 
	*  @param[in] tSipCfg Sip注册配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 CnsRegGkService( const TTPGKCfg &tCfg );

	/** 功能: 设置云服务器配置
	* @param [in]       
	* @returnu16 成功返回0,失败返回非0错误码
	*/
	u16 SetCloudServerInfo(const TTPCloudPlatServerCfg& tTpCloudServerInfo);

	/**
	* 功能:  更新cns信息 
	* @param[in] tInfo CNS信息  byIndex 消息来自哪里(0为cnc 1为维护工具)
	* @return 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex ,EmTpIpNameNatSyn emTpIpType);

	/** 功能:  更新NAT配置
	*  @param[in] tInfo NAT配置
	*  @return 成功返回0,失败返回非0错误码
	*  @remarks 
	*/
	u16 UpdateNATCfg( const TTPNatCfg& tInfo,EmTpIpNameNatSyn emTpIpType);

	/** 功能   设置音频接口
	*  @param[in] atAudioPortInfo[3]  3组音频接口信息
	*  @return 成功返回0,失败返回非0错误码
	*/						
	u16 SetAudioPortInfoCmd( const TTpAudioPortInfo* atAudioPortInfo );
	/** 功能   设置Gannon10音频接口
	*  @param[in]tTPMic10Info 音频接口信息
	*  @return 成功返回0,失败返回非0错误码
	*/	
	u16 SetMic10InfoCmd( const TTpMic10Info &tTPMic10Info );
	/** 功能   设置非桌面麦克风
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/						
	u16 SetNoDeskAudioCmd( bool bNoDeskAudio );	

	/** 功能   设置音频均衡器
	*  @param[in] atAudioEqualizer[3]  3组音频均衡器信息
	*  @return 成功返回0,失败返回非0错误码
	*/						
	u16 SetAudioEqualizerCmd( const TTPEqualizer* atAudioEqualizer );		
				
	/** 功能   设置音频混音数
	*  @param[in] aAudioMixerInfo[4]  4组混音数
	*  @return 成功返回0,失败返回非0错误码
	*/					
	u16 SetAudiotMixerCmd( const u8* aAudioMixerInfo );		
					
	/** 功能   请求默认音频混音数
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/					
	u16 SetDefaultMixerCmd( const u8* aAudioMixerInfo );		
						
	/** 功能   请求默认音频接口
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/					
	u16 SetDefaultAudioPortCmd( const TTpAudioPortInfo* atAudioPortInfo );		
						
	/** 功能   请求默认音频均衡器
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/					
	u16 SetDefaultEqCmd( const TTPEqualizer* atAudioEqualizer );		
	
	/** 功能   更新网络丢包信息
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 LostPacketInfoReq();

	/** 功能   配置音视频矩阵方案
	*  @param[in] tVideoDiagInfo  视频方案
				  tAudioDiagInfo  音频方案
	*  @return 成功返回0,失败返回非0错误码
	*/	
	u16 SelAVMatrixCmd( const TTPVgaMixInfo& tVgaMixInfo );

	/** 功能   停止诊断测试请求
	*  @param[in]
	*  @return 成功返回0,失败返回非0错误码
	*/	
	u16 StopAVMatrixReq();

	/** 功能   更新Tpad列表	
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/								
	u16 UpdateTpadListReq();	

	/** 功能   	重启cns
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/		
	u16 RebootCns();

	/** 功能   	升级cns
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/		
	u16 UpgradeCns( const TTPFTPFileInfo& tVerFileInfo );

	/** 功能   	更新基本信息页面信息
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/		
	u16 RefreshBasicInfo();
	/** 
	* 功能  	选择摄像机
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	u16 CamSelCmd( const u8& byCameraIndx );	
	/** 
	* 功能  	恢复摄像机默认参数
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	u16 CamResetCmd();	

	/** 
	* 功能  	视野设置
	* @param [in] 	 EmZoom  分为:远，近
	* @return  
	* @remarks 
	*/	
	u16 SetCamZoomCmd( const EmZoom& emZoom, const EmZoomStatus& emZoomStatus );	

	/** 
	* 功能  	视野是否在OSD上显示比例
	* @param [in] 	 EmOSDShow  分为:on，off
	* @return  
	* @remarks 
	*/	
	u16 SetCamOSDCmd( const EmOSDShow& emOSDShow );	
	/** 
	* 功能  	摄像机自动聚焦
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	u16 SetCamAutoFocusCmd(const EmFocusMode& emFocusMode);
	/** 
	* 功能  	摄像机手动聚焦
	* @param [in] 	 EmFocus : 远焦/近焦	EmCnAction :  开始/停止
	* @return  
	* @remarks 
	*/	
	u16 SetCamFocusCmd( const EmFocus& emFocus, const EmCnAction& emCnAction );	

	/** 
	* 功能  	设置预置位参数
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 CamPresetSaveCmd();		
	/** 
	* 功能  	设置开机调用预置位1
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 SetCamPresetMoveCmd( const BOOL& bPresetMove );	
	/** 
	* 功能  	设置自动曝光
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 CamAutoExposureCmd( EmExpMode emExpAuto );
	/** 
	* 功能  	增益
	* @param [in] 	 EmGain 增益范围 0dB  3dB  6dB ···42dB
	* @return  
	* @remarks 
	*/	
	u16 CamGainCmd( const EmGain& emGain );	

	/** 
	* 功能  快门调节	快门范围 1/60  1/120 1/250.....1/4000  1/10000
	* @param [in]  EmShutSpd
	* @return  
	* @remarks 
	*/
	u16 CamShutSpdCmd( const EmShutSpd& emShutSpd );

	/** 
	* 功能  背光模式调节
	* @param [in]  EmBackLightType  背光模式:关闭，multi（默认7，范围0-15），center，face detect
	*			   u8  = TP_INVALID_INDEX 非multi模式  0--15 multi模式调节
	* @return  
	* @remarks 
	*/
	u16 CamBackLightCmd( const EmBackLightType& emBackLightType, const u8& byMulti );

	/** 
	* 功能  光圈大小调节
	* @param [in]  u8  光圈大小 范围 0--100			   
	* @return  
	* @remarks 
	*/	
	u16 CamAperture( const u8& byAperture);	

	/** 
	* 功能  白平衡调节(分为自动和手动)
	* @param [in] 		   
	* @return  
	* @remarks 
	*/		
	u16 CamAutoWBCmd( const EmWBMode& emWBMode );	

	/** 
	* 功能  R+调节
	* @param [in] 	u16  R Gain 范围 0--100	   
	* @return  
	* @remarks 
	*/		
	u16 CamRGainCmd( const u16& wRGain );

	/** 
	* 功能  B+调节
	* @param [in] 	u16  B Gain 范围 0--100	   
	* @return  
	* @remarks 
	*/		
	u16 CamBGainCmd( const u16& wBGain );

	/** 
	* 功能  模式调节  
	* @param [in] 	EmPicSceMode  分为:日光灯/太阳灯/手动
	* @return  
	* @remarks 
	*/	
	u16 CamPicSceneModeCmd( const EmPicSceMode& emPicSceMode );	

	/** 
	* 功能  手动模式中的CAMMA调节  
	* @param [in] 	EmGamma  分为:emGammaOff、emGammaOn 、emSmart1、 emStrat2
	* @return  
	* @remarks 
	*/	
	u16 CamGammaCmd( const EmGamma& emGamma );

	/** 
	* 功能  手动模式中的光圈调节  
	* @param [in]   u8 光圈大小  1--15
	* @return  
	* @remarks 
	*/	
    u16 CamPicSceAptCmd( const u8& byPicSceApt );

	/** 
	* 功能  图片调节中的对比度调节
	* @param [in]   u16  大小  0--200
	* @return  
	* @remarks 
	*/		
	u16 CamContrastCmd( const u16& wContrast );	

	/** 
	* 功能  图片调节中的色度调节
	* @param [in]   u16  大小  0--200
	* @return  
	* @remarks 
	*/		
	u16 CamHueCmd( const u16& wHue );

	/** 
	* 功能  图片调节中的饱和度调节
	* @param [in]   u16  大小  0--200
	* @return  
	* @remarks 
	*/	
	u16 CamSaturatCmd( const u16& wSaturat );

	/** 
	* 功能  图片调节中的亮度调节
	* @param [in]   u16  大小  0--200
	* @return  
	* @remarks 
	*/	
	u16 CamBrightCmd( const u16& wBright );	

	/** 
	* 功能  降噪---摄像机噪点过滤调节命令
	* @param [in]   EmStmClean  默认LOW  范围OFF,LOW,MID,HIGH
	* @return  
	* @remarks 
	*/	
	u16 CamNRStmCleanCmd( const EmStmClean& emStmClean );

	/** 
	* 功能  降噪---3D降噪调节命令
	* @param [in]   Em3DNR   em3DNROff 关OFF，em3DNROn 开
	* @return  
	* @remarks 
	*/	
	u16 Cam3DNRCmd( const Em3DNR& em3DNR );	

	/** 
	* 功能  	向服务器发送导入通知
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 SetLoadCameraFileNty();

	/** 
	* 功能  设置zoom
	* @param [in]
	* @return  
	* @remarks 
	*/	
	u16 SetCamZoomCmd( const u16& wZoom );	

	/**
    * 功能:	 	        发送添加网管命令
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送修改网管命令
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送删除网管命令
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        设置呼叫服务器地址及呼叫格式
	* @param [in]       呼叫服务器信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  CallServerCmd( const TTPCallSerInfo& tCallSerInfo );
   
	/**
    * 功能:	 	        设置升级服务器地址
	* @param [in]       升级服务器地址
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer );

	u16  SetDataConfSerCmd( const TTPDataConfInfo& tWBSerIp);

	u16  SetMatrixSerCmd( const TTPMatrixServerInfo& tTPMatrixServerInfo);

	u16 SetNtpSerCmd( const TTPNtpSer& tTpNtpSer);

	u16 SetQtEncryptSerCmd( const TTpQtEncryptCfg& tTpQtEncryptCfg);

	//添加和删除路由
	u16  RouteMngAddCmd( const TRouteCfg& tRouteCfg );
	u16  RouteMngDelCmd( const TRouteCfg& tRouteCfg );

	/** 功能   台标文件上传成功通知
	*  @param[in] byIndex 消息来自哪里(0为cnc 1为维护工具)
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 ConfSignCmd( const BOOL& bOk, u8 byIndex );
 
	/**
    * 功能:	 	        设置会议优选格式
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  VideoFormatCmd( const TTPVidForamt& tVidForamt );
 
	/**
    * 功能:	 	        设置演示优选格式
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  DualVideoFormatCmd( const TTPVidForamt& tVidForamt );
 
	/**
    * 功能:	 	        设置单屏码率
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  CallRateCmd( const u16 wCallRate );
 
	/**
    * 功能:	 	        设置演示码率
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  DualCallRateCmd( const u16 wDualCallRate );
 
	/**
    * 功能:	 	        设置会议讨论状态
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  ConfDisCmd( const BOOL& bDis );
 
	/**
    * 功能:	 	        设置会议轮询信息
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  ConfPollCmd( const TTPPollInfo& tPollInfo );
  
	/**
    * 功能:	 	        设置音频格式信息
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  AudioFormatCmd( const EmTpAudioFormat& emAudioFormat );
  
	/**
    * 功能:	 	        设置中控电视墙信息
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  SetDisplayCmd( BOOL bDisplay, const TTPDisplayType& tDisplayType1, const TTPDisplayType& tDisplayType3 );
	
	/** 
	* 功能  	设置摄像机类型
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 SetCamTypeCmd( const EmCamType& emCamType );

	/** 
	* 功能  	Sony摄像机背光调节命令
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 SonyBackLightCmd( const BOOL& bLight );

	/** 
	* 功能  	Sony摄像机降噪设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 SonyStmClenCmd( const BOOL& bClen, const u8& bylevel );

    /** 
	* 功能  	Moon904K摄像机设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 SetMoon904KCamCfgCmd( const EmCamCfgType& emCamCfgType, const u32& dwValue );

	u16 SetDefaultAudioCmd( const TTPMPAudioInfo* atAudioInfo );

	u16 SetDefaultListenPortCmd( const EmAudMixType emAudioMixtype, const u8 byAudMixVolume );

	u16 SetDefaultAux2OutCmd( const EmAudExtend emAudExtend, const u8 byAudExtendVolume );

	u16 SetAudioInfoCmd( const TTPMPAudioInfo* atAudioInfo );

	u16 SetListenPortCmd(const EmAudMixType emAudioMixtype, CONST u8 byAudMixVolume );

    u16 SetAux2OutCmd( const EmAudExtend emAudExtend, const u8 byAudExtendVolume);

	u16 SetAudioWhiteNoiseCmd(BOOL bIsOpen ,u32 dwWhiteNoisePort);

	u16 SetDefaultMainAudioCmd( const TTPVideoInfoTool* ptAudioInfo );

	u16 SnapShotCmd();

	u16 SetMainAudioInfoCmd( const TTPVideoInfoTool* ptAudioInfo );

	u16 SetDefaultDemonStrationCmd(const TVgaInfo *ptDisplaySource, 
		const TTPDualDisplayStrategy *ptDualDisplayStrategy, const EmVgaType emDefaultDisplay);

	u16 SetDemonStrationCmd(const TVgaInfo *ptDisplaySource,
		const TTPDualDisplayStrategy *ptDualDisplayStrategy, const EmVgaType emDefaultDisplay);

	u16 SetDefParameterCmd(const TTPImageAdjustParam * pImageAdjustParam );

	u16 SetParameterCmd(const TTPImageAdjustParam * pImageAdjustParam );
	/** 
	* 功能  	设置显示器型号
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	u16 SetCentreTVModleCmd( EmTVModle emTvMode );
	u16 SetDisplayShowCmd(BOOL bDisplayShow);
	u16 SetPanCamNumberCmd( u8 byPanCamNum );
	u16 SetDCCamZoomCmd( const EmDCamZoom emZoom ,const EmCnAction emAction );
	u16 SetDCCamZoomValue( const u16& wZoom );
	u16 SetDCCamAFModeCmd( EmDCamAFMode emMode );
	u16 SetDCCamFocusCmd( EmFocus emFocusMode ,EmCnAction emAction);
	u16 SetDCCamWBModeCmd( EmDCamWBMode emWBMode );
	u16 SetDCCamExposureCmd( EmExpMode emExpMode );
	u16 SetDCCamApertureCmd( EmDCamIris emAperture );
	u16 SetDCCamExpGain( EmDCamGain emDCCamExpGain );
	u16 SetDCCamShut( EmDCamShutSpd emDCCamExpShut );
	u16 SetDcCamRGain( u16 wRGain );
	u16 SetDcCamBGain( u16 wRGain );
	u16 SetDCamRecallCmd( EmDCamRecallNum emNum );
	u16 SetDCamSavePresetCmd( EmDCamPresetNum emNum );
	u16 SetCurtainNumber( u8 byCurNum );
	u16 SetCurtainNameCmd( u8 byCurIndex , TCentreCurName tCurtainName );
	u16 SetCurtainOpenCmd( BOOL bOpen );
	u16 SetAesEncrypCmd( const TTpEncryptKey& tEncryptKey );
	u16 SetLostPacketCmd( EmTpLostPackageRestore emLostPackage );
	u16 SetFtpInfoRsq( const TTPFtpInfo &tTPFtpInfo );
	u16 SetTelInfoRsp( const TTPTelnetInfo &tTPTelnetInfo);
	u16 SetDuoVideoCmd( BOOL bOpen );
	u16 SetDCCamOpenCmd( BOOL bOpen );
	u16 SetDCCamPreset( BOOL bPreset );
	u16 SetAirConditionCmd( u8 byAcNum );
	u16 SetDcCamModel( EmDCamProType emDcCamType );
	u16 SetPaCamModel( EmQCamProType emPaCamType );
	u16 SetCaptureStateCmd(bool bCapture);
private:
	CCnclibCommonIF();
private:
	static CCnclibCommonIF*	m_pThis;
	TLoginInfo m_tLoginInfo;		//存储登陆参数信息

};

#define COMIFMGRPTR   CCnclibCommonIF::GetComIF()

#endif