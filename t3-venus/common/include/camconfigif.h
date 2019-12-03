/*****************************************************************************
模块名      : moon90 moonlib接口
文件名      : camconfigif.h
相关文件    : 
文件实现功能: 摄像调节/配置
作者        : 吴蒨蒨
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2014/11/26  1.0         吴蒨蒨        创建
******************************************************************************/
#ifndef __CAMCONFIGIF_H__
#define __CAMCONFIGIF_H__

#include "kdvdispevent.h"
#include "moonstruct.h"
#include <vector>

class CCamConfigIF : public CKdvDispEvent
{
public:
	/** 
	* 功能  	选择摄像机
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 CamSelCmd( const u8& byCameraIndx ) = 0;

	/** 
	* 功能  	同步摄像机参数
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 SetMoonCamCfgSyncCmd( const u8& byCameraIndx ) = 0;
	
	/** 
	* 功能  	选择摄像机机芯
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 CamStyleSelCmd( const EmTPMechanism& emTPMechanism ) = 0;

	/** 
	* 功能  	选择Gamma
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/	
	virtual u16 GammaStyleSelCmd( const EmH650Gamma& enH650Gamma ) = 0;

    /** 
	* 功能  输出制式设置
	* @param [in]
	* @return  
	* @remarks 
	*/	
	virtual u16 SetOutputFormatCmd( const TPOutputFmt& tOutputFmt) = 0;

    // 获取输出制式参数
    virtual TPOutputFmt GetOutputFormat() = 0;

	/** 
	* 功能  视野设置
	* @param [in] 	 EmZoom  分为:远，近
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCamZoomCmd( const EmTPZOOM& emZoom, u8 byIndex ) = 0;
    //moon904k30
    virtual u16 SetCamZoomValCmd( const TCamZoomVal& tCamZoomVal) = 0;

	virtual u16 SetCamZoomStopCmd(u8 byIndex) = 0;

	/** 
	* 功能  设置zoom值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCamZoomValueCmd( const u32& dwZoom, u8 byIndex ) = 0;

	/** 
	* 功能  	获取zoom
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u32 GetCamZoom() = 0;

	virtual u32 GetExtCamZoom() = 0;

	/** 
	* 功能  摄像机自动聚焦
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u16 SetCamAutoFocusCmd(const EmTPMOOMMode& emFocusMode) = 0;

	/** 
	* 功能  手动聚焦拉近D
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
    virtual u16 SetCamFocusNearCmd() = 0;

	/** 
	* 功能  手动聚焦拉近/拉远up
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
    virtual u16 SetCamFocusStopCmd() = 0;

	/** 
	* 功能  手动聚焦拉远D
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
    virtual u16 SetCamFocusFarCmd() = 0;

    /** 
	* 功能: 光圈设置命令
	* @param [in] 	TIrisAutoManuMode  
	* @return  
	* @remarks 
	*/
	virtual u16 SetCamApertreCmd( const TIrisAutoManuMode& tIrisAutoManuMode ) = 0;

	/** 
	* 功能: 是否开启自动曝光
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamAutoExposureCmd( const EmTPMOOMMode& emExpAuto ) = 0;

	/** 
	* 功能  	获取曝光模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmTPMOOMMode GetCamMoonMode() = 0;

	/** 
	* 功能: 光圈切换消息发送
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamApertureCmd( const EmTPAperture &emTPAperture ) = 0;

	virtual EmTPAperture GetCamAperture() = 0;

	/** 
	* 功能: 快门切换消息发送
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamShutSpdCmd( const EmTPSOrThShutter& emShutSpd ) = 0;

	virtual u16 CamTwShutSpdCmd( const EmTPFOrTwShutter& emTwShutter ) = 0;

	virtual TPSOrThShutter GetCamShutSpd() = 0;

	virtual TPFOrTwShutter GetTwCamShutSpd() = 0;
	
	/** 
	* 功能: 增益切换消息发送
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamGainCmd( const EmTPExpGain& emGain ) = 0;

    virtual u16 SetCamGainCmd( const TGainMode& tGainMode ) = 0;

	virtual EmTPExpGain GetCamGain() = 0;

	/** 
	* 功能: 是否自动白平衡
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamAutoWBCmd( const TCamWBMode& tCamWBMode ) = 0;

	/** 
	* 功能: 红色增益调节命令
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamRGainCmd( const u32& dwRGain ) = 0;

	/** 
	* 功能: 蓝色增益调节命令
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamBGainCmd( const u32& dwBGain ) = 0;

	virtual u16 CamAdjustRangeCmd( const u32& dwAdjustRange ) = 0;

	virtual u16 CamHoriStretchCmd( const u32& dwHoriStretch ) = 0;

	/** 
	* 功能 获取红色增益值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u32 GetCamRGain() = 0;

	/** 
	* 功能 获取蓝色增益值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u32 GetCamBGain() = 0;

	virtual u32 GetCamAdjustRange() = 0;

	virtual u32 GetCamHoriStretch() = 0;

	/** 
	* 功能 图片参数设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamImageParaCmd( EmTPImagePara emImagePara, const u32& dwImagePara ) = 0;

	/** 
	* 功能 获取当前摄像机配置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TTPMoonCamInfo GetCamCfg() = 0;

    /** 
	* 功能 设置当前所有机芯配置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual void SetAllCamCfg(TTPMoonCamInfo tCamInfo[]) = 0;

    /** 
	* 功能 获取当前所有机芯配置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual void GetAllCamCfg(TTPMoonCamInfo* ptCamInfo[]) = 0;
	
    /** 
	* 功能 获取当前界面状态
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual BOOL GetCurStatus() = 0;

	/** 
	* 功能 获取被选中的摄像机
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u8 GetCamSel()const = 0;

	/** 
	* 功能 获取白平衡模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmTPMOOMMode GetCamWBMode() = 0;

	/** 
	* 功能 是否开启背光补偿
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual	u16 CamLightPensation( BOOL bIsOpen ) = 0;

	virtual	u16 CamKeystoneAdjust(const TTPDistortParam& tTPDistortParam,EmTPCorrect emMyOpetion ) = 0;

	virtual u16 SetColorRGBDirectCmd(u8 nPosition, EmTPColorConsistency emMyCorConsOption, const u32& dwRGBDirectValue) = 0;

	virtual	u16 CamOrderPosCheckCmd( const TCamPresetNumberList& tCamPreset ) = 0;

	/** 
	* 功能 降噪设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual	u16 CamNRCmd( BOOL bIsOpen, EmTPFpgaReduNoise emTPReduNoise ) = 0;

	/** 
	* 功能 2D降噪设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual	u16 Cam2DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise ) = 0;

	/** 
	* 功能 3D降噪设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual	u16 Cam3DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise ) = 0;

    //预置位1保存
    virtual	u16 CamPreSet1SaveCmd() = 0;

    virtual TTPCamPre* GetCamPreInfo() = 0; 

	/** 功能   保存预置位
	 *  @param[in] cfg 保存预置位
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 CamPreSetSaveCmd( const TTPCamPre& tTPCamPre ) = 0;

	virtual u16 CamPreSetModifyCmd( const TTPCamPre& tTPCamPre ) = 0;

	virtual u16 OrderPosDeleteReq( const TTPCamPre& tTPCamPre ) = 0;

	virtual u16 OrderPosInvokeCmd( const TTPCamPre& tTPCamPre ) = 0;

	virtual u16 CamParamUploadCmd() = 0;

	virtual u16 CamParamUploadNty( BOOL bSuccess ) = 0;

	virtual u16 UpgradeMoon( const s8* chVerFileInfo ) = 0;

	virtual u16 UpdateMoonMechanism( const s8* chVerFileInfo ) = 0;

	//重启Moon
	virtual u16 RebootMoon() = 0;

	virtual u16 MoonCamResetCmd(u8 byIndex) = 0;
	/** 功能   设置参考线
	 *  @param[in] bOpen 是否打开
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 SetReferenceLineCmd( BOOL bOpen ) = 0;
	/** 功能   设置水平翻转
	 *  @param[in] bOpen 是否打开
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 SetHorizontalFlipCmd( BOOL bOpen ) =0;

	virtual u16 SetTrapezoidalCorCmd( BOOL bOpen ) =0;

	virtual u16 SetShowRectRegionCmd( BOOL bOpen ) = 0;

	virtual u16 SetRgbConsistSwitchCmd(BOOL bOpen) = 0;
	/** 功能   增加、减少梯形参数
	 *  @param[in] emMyCorOption 对哪个参数进行操作  emChangeOption 增加或减少
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual	u16 SetTraCorParamCmd( EmTPCorrect emMyCorOption,EmTPCorrectChange emChangeOption ) = 0;
	
	//设置颜色一致性RGB
	virtual	u16 SetCorConsistRGBCmd( u8 nPosition, EmTPColorConsistency emMyCorConsOption,EmTPCorrectChange emChangeOption ) = 0;

	virtual u16 SetChangeDistortCmd( u8 byIndex, EmTPCorrectChange emTPCorrectChange, EmTPDistortPosition emTPDistortPosition ) = 0;

	virtual u16 SetDirectDistortCmd( const TTPDistortInfo&tTpDistortInfo ) = 0;

	virtual	u16 SetAutoSetColorConstancyCmd() = 0;

	virtual u16 SetChooseRectangleCmd(const TTPMoonRectRegion& tTPMoonRectRegion) = 0;

	virtual u16 SnapShotCmd( ) =0;

	//设置延时矫正
    virtual u16 SetDelayCorrectCmd(u8 nPosition, u32 dwDelay) = 0;
};

#endif