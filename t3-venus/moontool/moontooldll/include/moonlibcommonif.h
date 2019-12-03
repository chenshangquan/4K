/*****************************************************************************
模块名      : 窗口向moon90申请数据的接口模块
文件名      : moonlibcommonif.h
相关文件    : moonlib.h
文件实现功能: UI调用cnclib对cns的访问
作者        : 吴蒨蒨
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/11/26     1.0						创建
******************************************************************************/
#include "rkclib.h"
#include "moonToolDll.h"
#ifndef CMOONLIBCOMMONIF_H
#define CMOONLIBCOMMONIF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CMoonlibCommonIF
{
public:

	static CMoonlibCommonIF* GetComIF();
	~CMoonlibCommonIF();

    /**** rkcsysctrl ***/

    //建立Socket连接
    //u16 SocketConnect(s8* pchIP, u32 dwPort);
    //断开Socket连接
    //u16 CloseSocket();
    //发送Socket消息
    //u16 SendLoginReq(TRK100LoginInfo tRK100LoginInfo);
    //发送修改密码请求消息
    //u16 SendModifyPasswordReq(TRK100LoginInfo tRK100LoginInfo);
    //判断是否登录
    //bool IsLoginState();
    
    //获得登录错误反馈
    //u16 GetLoginBackInfo(TRK100MsgHead& tRK100MsgHead);

    /**** camerconfig ***/

	u16 LinkMoon();
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

    /** 
	* 功能  输出制式设置
	* @param [in]
	* @return  
	* @remarks 
	*/	
	u16 SetOutputFormatCmd( const TPOutputFmt& tOutputFmt);

	/** 
	* 功能: 视野设置
	* @param [in]  EmZoom 分为:远/近
	* @return  
	* @remarks 
	*/	
	u16 SetCamZoomCmd( const EmTPZOOM& emZoom, u8 byIndex);	
    //moon904k30
    u16 SetCamZoomValCmd( const TCamZoomVal& tCamZoomVal);

	u16 SetCamZoomValueCmd( const u32& dwZoom, u8 byIndex );

	u16 SetCamZoomStopCmd(u8 byIndex);

	/** 
	* 功能: 摄像机自动聚焦
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	u16 SetCamAutoFocusCmd(const EmTPMOOMMode& emFocusMode);

	/** 
	* 功能: 选择摄像机
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	u16 CamSelCmd( const u8& byCameraIndx );

	/** 
	* 功能: 同步摄像机参数
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	u16 SetMoonCamCfgSyncCmd( const u8& byCameraIndx );

	/** 
	* 功能: 选择摄像机
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	u16 CamStyleSelCmd( const EmTPMechanism& emTPMechanism );

	/** 
	* 功能: 选择Gamma
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	u16 GammaStyleSelCmd( const EmH650Gamma& enH650Gamma );
	/** 
	* 功能: 鼠标D时发送拉近消息
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/	
	u16 SetCamFocusNearCmd();

	/** 
	* 功能: 鼠标Up时发送拉近消息
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/	
	u16 SetCamFocusStopCmd();

	/** 
	* 功能: 鼠标D时发送拉远消息
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/	
	u16 SetCamFocusFarCmd();

    /** 
	* 功能: 光圈设置命令
	* @param [in] 	 TIrisAutoManuMode  
	* @return  
	* @remarks 
	*/
	u16 SetCamApertreCmd( const TIrisAutoManuMode& tIrisAutoManuMode );

	/** 
	* 功能: 是否自动曝光
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/
	u16 CamAutoExposureCmd( EmTPMOOMMode emExpAuto );

	/** 
	* 功能: 光圈切换消息发送
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/
	u16 CamApertureCmd( const EmTPAperture &emTPAperture );

	/** 
	* 功能: 快门切换消息发送
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/
	u16 CamShutSpdCmd( const EmTPSOrThShutter& emShutSpd );

	u16 CamTwShutSpdCmd( const EmTPFOrTwShutter& emTwShutter);

	/** 
	* 功能: 增益切换消息发送
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/
	u16 CamGainCmd( const EmTPExpGain& emGain );

    /** 
	* 功能: 增益设置消息发送
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/
    u16 SetCamGainCmd( const TGainMode& tGainMode );

	/** 
	* 功能: 是否自动白平衡
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamAutoWBCmd( const TCamWBMode& tCamWBMode );

	/** 
	* 功能: 红色增益调节命令
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamRGainCmd( const u32& dwRGain );

	/** 
	* 功能: 蓝色增益调节命令
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamBGainCmd( const u32& dwBGain );

	u16 CamAdjustRangeCmd( const u32& dwAdjustRange );

	u16 CamHoriStretchCmd( const u32& dwHoriStretch );

	/** 
	* 功能: 图片参数调节
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamImageParaCmd( EmTPImagePara emImagePara, const u32& dwImagePara );

	/** 
	* 功能: 图片参数调节
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamLightPensation( BOOL bIsOpen );

	u16 CamKeystoneAdjust(const TTPDistortParam& tTPDistortParam,EmTPCorrect emMyOpetion);

	u16 SetColorRGBDirectCmd(u8 nPosition, EmTPColorConsistency emMyCorConsOption, const u32& dwRGBDirectValue);

	/** 
	* 功能: 降噪
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamNRCmd(BOOL bIsOpen, EmTPFpgaReduNoise emTPReduNoise);

	/** 
	* 功能: 2D降噪
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 Cam2DNRCmd(BOOL bIsOpen, EmTPReduNoise emTPReduNoise);

	/** 
	* 功能: 3D降噪
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 Cam3DNRCmd(BOOL bIsOpen, EmTPReduNoise emTPReduNoise);

	u16 CamOrderPosCheckCmd( const TCamPresetNumberList& tCamPreset );

    /** 
	* 功能: 预置位保存
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
    u16 CamPreSet1SaveCmd();

	u16 SetOutPortTypeCmd( EmTPDVIOutPortType emDVIOutPortType, EmTPMOONOutMode emMOONOutMode );

	u16 SetImageAdjustCmd( EmTPImageAdjust emImageAdjust );

	/** 功能:  更新网络配置
	*  @param[in] tInfo 网络配置
	*  @return 成功返回0,失败返回非0错误码
	*  @remarks 
	*/
	u16 UpdateEthnetCfg( const TRK100NetParam& tInfo );

    //获取网络配置
    u16 GetNetWorkConfig();
    //获取网络配置内容
    u16 GetNetWorkConfig(TRK100NetParam& tRK100NetParam);

	u16 CamPreSetSaveCmd( const TTPCamPre& tTPCamPre );

	u16 OrderPosDeleteReq( const TTPCamPre& tTPCamPre );

	u16 OrderPosInvokeCmd( const TTPCamPre& tTPCamPre );
	
	u16 CamPreSetModifyCmd( const TTPCamPre& tTPCamPre );

	u16 CamParamUploadCmd();
	
	u16 CamParamUploadNty(BOOL bSuccess);

	u16 UpgradeMoon( const s8* chVerFileInfo );

	u16 UpdateMoonMechanism( const s8* chVerFileInfo );

	/** 功能   	重启moon
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/		
	u16 RebootMoon();

	u16 MoonCamResetCmd(u8 byIndex);
	/** 功能   	设置LVDS波特率
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetBaudRateCmd( EmTPLVDSBaud emBaudRate );
	/** 功能   	参考线设置
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetReferenceLineCmd( BOOL bOpen );
	/** 功能   	水平翻转设置
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetHorizontalFlipCmd( BOOL bOpen );
	/** 功能   	设置梯形矫正开启设置
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetTrapezoidalCorCmd( BOOL bOpen );

    u16 SetShowRectRegionCmd( BOOL bOpen );

	u16 SetRgbConsistSwitchCmd(BOOL bOpen);
	/** 功能   增加、减少梯形参数
	 *  @param[in] emMyCorOption 对哪个参数进行操作  emChangeOption 增加或减少
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	u16 SetTraCorParamCmd( EmTPCorrect emMyCorOption,EmTPCorrectChange emChangeOption );

	//设置颜色一致性RGB
	u16 SetCorConsistRGBCmd( u8 nPosition, EmTPColorConsistency emMyCorConsOption,EmTPCorrectChange emChangeOption );

	u16 SetChangeDistortCmd( u8 byIndex, EmTPCorrectChange emTPCorrectChange, EmTPDistortPosition emTPDistortPosition );

	u16 SetDirectDistortCmd( const TTPDistortInfo& tTpDistortInfo );

	u16 SetAutoSetColorConstancyCmd();

	u16 SetChooseRectangleCmd(const TTPMoonRectRegion& tTPMoonRectRegion);

	u16 SnapShotCmd( );

	//设置延时矫正命令
    u16 SetDelayCorrectCmd( u8 nPosition, u32 dwDelay );

public:
    //获取登陆的camera IP
    u32 GetLoginIp(){ return htonl(m_tCamLoginInfo.dwIp); }

private:
	CMoonlibCommonIF();
private:
	static CMoonlibCommonIF*	m_pThis;
	TCamLoginInfo m_tCamLoginInfo;		//存储登陆参数信息(此处只用到ip)
};

#define COMIFMGRPTR   CMoonlibCommonIF::GetComIF()

#endif