// cncconfig.h: interface for the CCncConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_)
#define AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rkcSession.h"

#define DELAY_SEND_CMD     200  //输入指令间隔

class CCamConfig : public CCamConfigIF 
{
	friend class CRkcSession;
public:

	CCamConfig(CRkcSession &cSession);
	virtual ~CCamConfig();

    /** 
	* 功能  输出制式设置
	* @param [in]
	* @return  
	* @remarks 
	*/	
	virtual u16 SetOutputFormatCmd( const TPOutputFmt& tOutputFmt);

    // 获取输出制式参数
    virtual TPOutputFmt GetOutputFormat();

	/** 
	* 功能  视野设置
	* @param [in] 	 EmZoom 分为:远/近
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCamZoomCmd( const EmTPZOOM& emZoom, u8 byIndex);	
    virtual u16 SetCamZoomValCmd( const TCamZoomVal& tCamZoomVal);

	virtual u16 SetCamZoomStopCmd(u8 byIndex);

	virtual u16 SetCamZoomValueCmd( const u32& dwZoom, u8 byIndex );

	/** 
	* 功能  	获取zoom
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u32 GetCamZoom();

	virtual u32 GetExtCamZoom();

	/** 
	* 功能  	摄像机自动聚焦
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u16 SetCamAutoFocusCmd(const EmTPMOOMMode& emFocusMode);

	/** 
	* 功能  	选择摄像机
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 CamSelCmd( const u8& byCameraIndx );

	/** 
	* 功能  	同步摄像机参数
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 SetMoonCamCfgSyncCmd( const u8& byCameraIndx );

	/** 
	* 功能  	选择摄像机机芯
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 CamStyleSelCmd( const EmTPMechanism& emTPMechanism );

	/** 
	* 功能  	选择Gamma
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 GammaStyleSelCmd( const EmH650Gamma& enH650Gamma );
	/** 
	* 功能  	获取当前摄像机配置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TTPMoonCamInfo GetCamCfg();
    /** 
	* 功能  	设置当前所有机芯配置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
    virtual void SetAllCamCfg(TTPMoonCamInfo tCamInfo[]);
    /** 
	* 功能  	获取当前所有机芯配置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
    virtual void GetAllCamCfg(TTPMoonCamInfo* ptCamInfo[]);
    /** 
	* 功能  	获取当前界面状态
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
    virtual void GetCurStatus(BOOL &bSetCamCfgOver, BOOL &bOutputFmtChg);
    // 清理当前界面状态
    virtual void ClearCurStatus();

	/** 
	* 功能  	获取被选中的摄像机
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u8 GetCamSel()const;

	/** 
	* 功能  	鼠标D时给底层发拉近消息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetCamFocusNearCmd();

	/** 
	* 功能 鼠标Up时给底层发停止拉近/拉远消息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetCamFocusStopCmd();

	/** 
	* 功能  	鼠标D时给底层发拉远消息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetCamFocusFarCmd();

    /** 
	* 功能  	光圈设置消息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetCamApertreCmd( const TIrisAutoManuMode& tIrisAutoManuMode );

	/** 
	* 功能  	是否开启自动曝光
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamAutoExposureCmd( const EmTPMOOMMode& emExpAuto );

	/** 
	* 功能  快门切换
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamShutSpdCmd( const EmTPSOrThShutter& emShutSpd );

	virtual u16 CamTwShutSpdCmd( const EmTPFOrTwShutter& emTwShutter );

    u16 SetCamShutterCmd( const TShutterMode& tShutterMode );

	/** 
	* 功能  界面获取快门参数接口
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual TPSOrThShutter GetCamShutSpd();

	virtual TPFOrTwShutter GetTwCamShutSpd();

	/** 
	* 功能  光圈切换
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamApertureCmd( const EmTPAperture& emAperture );

	/** 
	* 功能  增益切换
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamGainCmd( const EmTPExpGain& emExpGain );

    virtual u16 SetCamGainCmd( const TGainMode& tGainMode );

	virtual EmTPExpGain GetCamGain();

	virtual EmTPAperture GetCamAperture();

	virtual EmTPMOOMMode GetCamMoonMode();

	virtual EmTPMOOMMode GetCamWBMode();

	/** 
	* 功能  白平衡调节(分为自动和手动)
	* @param [in] 		   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamAutoWBCmd( const TCamWBMode& tCamWBMode );	
	/** 
	* 功能  R+调节
	* @param [in] 	u16  R Gain 范围 0--100	   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamRGainCmd( const u32& dwRGain );
	/** 
	* 功能  	获取摄像机白平衡调节模式R+调节值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u32 GetCamRGain();
	/** 
	* 功能  B+调节
	* @param [in] 	u16  B Gain 范围 0--100	   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamBGainCmd( const u32& dwBGain );
	/** 
	* 功能  	获取摄像机白平衡调节模式B+调节值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u32 GetCamBGain();

	virtual	u16 CamAdjustRangeCmd( const u32& dwAdjustRange );

	virtual	u16 CamHoriStretchCmd( const u32& dwHoriStretch );

	virtual u32 GetCamAdjustRange();

	virtual u32 GetCamHoriStretch();
	/** 
	* 功能  	设置图片参数值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamImageParaCmd( EmTPImagePara emImagePara, const u32& dwImagePara );
    virtual u16 CamImageParaCmd( TCamImagParam &tCamImagParam );
	/** 
	* 功能  	获取图片参数值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
//	virtual u16 GetCamImagePara();
	/** 
	* 功能  	是否开启背光补偿
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamLightPensation( BOOL bIsOpen);

	virtual u16 CamKeystoneAdjust(const TTPDistortParam& tTPDistortParam,EmTPCorrect emMyOpetion );

	virtual u16 SetColorRGBDirectCmd(u8 nPosition, EmTPColorConsistency emMyCorConsOption, const u32& dwRGBDirectValue);

	/** 
	* 功能  	降噪参数设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamNRCmd( BOOL bIsOpen, EmTPFpgaReduNoise emTPReduNoise );

	/** 
	* 功能  	2D降噪参数设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 Cam2DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise );
    virtual u16 Cam2DNRCmd( TCamD2NRMode &tCamD2NRMode );

	/** 
	* 功能  	3D降噪参数设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 Cam3DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise );
    virtual u16 Cam3DNRCmd( TCamD3NRMode &tCamD3NRMode );

    virtual u16 CamOrderPosCheckCmd( const TCamPresetNumberList& tCamPreset );

    /** 
	* 功能  	预置位1保存
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
    virtual u16 CamPreSet1SaveCmd();

	/** 
	* 功能  获取电视机配置
	* @return TCentreTVCfg*  电视机配置数组指针
	*/
    virtual TTPCamPre* GetCamPreInfo();

	virtual u16 CamPreSetSaveCmd( const TTPCamPre& tTPCamPre );

	virtual u16 CamPreSetModifyCmd( const TTPCamPre& tTPCamPre );

	virtual u16 OrderPosDeleteReq( const TTPCamPre& tTPCamPre );

	virtual u16 OrderPosInvokeCmd( const TTPCamPre& tTPCamPre );

	virtual u16 CamParamUploadCmd();

	virtual u16 CamParamUploadNty( BOOL bSuccess );

	virtual u16 UpgradeMoon( const s8* chVerFileInfo );

	virtual u16 UpdateMoonMechanism( const s8* chVerFileInfo );

	//重启moon
	virtual u16 RebootMoon();

	virtual u16 MoonCamResetCmd(u8 byIndex);
	//设置参考线
	virtual	u16 SetReferenceLineCmd( BOOL bOpen );
	//设置水平翻转
	virtual u16 SetHorizontalFlipCmd( BOOL bOpen );

	virtual u16 SetTrapezoidalCorCmd( BOOL bOpen );

	virtual u16 SetShowRectRegionCmd( BOOL bOpen );

	virtual u16 SetRgbConsistSwitchCmd(BOOL bOpen);
	//增加或减少梯形矫正的参数
	virtual	u16 SetTraCorParamCmd( EmTPCorrect emMyCorOption,EmTPCorrectChange emChangeOption );
	//设置颜色一致性RGB
	virtual	u16 SetCorConsistRGBCmd( u8 nPosition, EmTPColorConsistency emMyCorConsOption,EmTPCorrectChange emChangeOption );

	virtual u16 SetChangeDistortCmd( u8 byIndex, EmTPCorrectChange emTPCorrectChange, EmTPDistortPosition emTPDistortPosition );

	virtual u16 SetDirectDistortCmd( const TTPDistortInfo&tTpDistortInfo );

	virtual	u16 SetAutoSetColorConstancyCmd();

	virtual u16 SetChooseRectangleCmd(const TTPMoonRectRegion& tTPMoonRectRegion);

	virtual u16 SnapShotCmd( );

	//设置延时矫正
    virtual u16 SetDelayCorrectCmd(u8 nPosition, u32 dwDelay);

    /** 
	* 功能  获取图像参数
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TCamImagParam GetCamImagParam();

    /** 
	* 功能  界面参数设置已完成
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 InputCamParamOverCmd();

protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();

	//消息处理
	void OnLinkBreak(const CMessage& cMsg);

	void OnMoonCamCfgNty(const CMessage& cMsg);

    void OnOutputFormatRsp(const CMessage& cMsg);

	void OnCamZoomInd(const CMessage& cMsg);

	void OnCamZoomStopInd(const CMessage& cMsg);

	void OnCamZoomValueInd(const CMessage& cMsg);

	void OnCamSelInd(const CMessage& cMsg);

	void OnCamParaSynchronizeInd(const CMessage& cMsg);

	void OnCamStyleSelInd(const CMessage& cMsg); //机芯

	void OnGammaSelInd(const CMessage& cMsg);  //Gamma

	void OnMechanismSelectNty( const CMessage& cMsg);

	void OnTpMechverNty( const CMessage& cMsg);//版本号

	void OnCamSelNty(const CMessage& cMsg);

	void OnCamAutoFocusInd(const CMessage& cMsg);

	void OnCamFocusNearInd(const CMessage& cMsg);

	void OnCamFocusStopInd(const CMessage& cMsg);

	void OnCamFocusFarInd(const CMessage& cMsg);

	void OnAutoExposureInd(const CMessage& cMsg);
	
	void OnCamShutSpdCInd(const CMessage& cMsg);

	void OnCamTwShutSpdCInd(const CMessage& cMsg);

	void OnCamApertureInd(const CMessage& cMsg);

	void OnCamGainInd(const CMessage& cMsg);

	void OnCamAutoWBInd(const CMessage& cMsg);

	void OnCamRGainInd(const CMessage& cMsg);

	void OnCamBGainInd(const CMessage& cMsg);

	void OnCamImageParaInd(const CMessage& cMsg);

	void OnCamLightPensationInd(const CMessage& cMsg);

	void OnCamNRInd(const CMessage& cMsg);

	void OnCam2DNRInd(const CMessage& cMsg);

	void OnCam3DNRInd(const CMessage& cMsg);

	void OnCamOrderPosSelInd(const CMessage& cMsg);

	void OnCamPreSetNty(const CMessage& cMsg);

	void OnCamPreSetInd(const CMessage& cMsg);

	void OnCamPreResetInd(const CMessage& cMsg);

	void OnCamPreRecallInd(const CMessage& cMsg);

	void OnCamPreSetModifyInd(const CMessage& cMsg);

	void OnCamParamDefaultInd(const CMessage& cMsg);

	void OnSetColorRGBInd(const CMessage& cMsg);

	void OnChooseRectangleInd(const CMessage& cMsg);

	void OnSetAutoColorConstancyInd(const CMessage& cMsg);

	void OnChangeSideRGBNty(const CMessage& cMsg);

	void OnSetColorRGBDirectInd(const CMessage& cMsg);

	void OnCamDistortAdjustInd(const CMessage& cMsg);

	void OnMoonUpgradeInd(const CMessage& cMsg);

	void OnUpdateMechanismInd(const CMessage& cMsg);
	//设置参考线通知
	void OnReferenceLineInd( const CMessage& cMsg );

	void OnReferenceLineNty( const CMessage& cMsg );
	//设置水平翻转通知
	void OnHorizontalFlipInd( const CMessage& cMsg );

	void OnHorizontalFlipNty( const CMessage& cMsg );

	void OnTrapezoidalCorInd( const CMessage& cMsg );

	void OnShowRectRegionInd( const CMessage& cMsg );

	void OnColorSwitchInd( const CMessage& cMsg );

	void OnTraCorParamInd( const CMessage& cMsg );

	void SnapShotInd( const CMessage& cMsg );

	void OnChangeDistortInd( const CMessage& cMsg );

	void OnDirectSetDistortInd( const CMessage& cMsg );

	void OnSecDefaultNty( const CMessage& cMsg );

	void OnSecBoundaryNty( const CMessage& cMsg );

	//延时矫正
	void OnDelayCorrectInd( const CMessage& cMsg );
	void OnDelayCorrectNty( const CMessage& cMsg );

    //moon904k30
    void OnSetCamZoomValRsp( const CMessage& cMsg );
    void OnSetCamApertreRsp( const CMessage& cMsg );
    void OnReBootRkRsp( const CMessage& cMsg );
    void OnCamPreSet1SaveRsp( const CMessage& cMsg );
    void OnCamParamInputOverRsp( const CMessage& cMsg );

public:
	void SetCameraCfgPtr();
	void SetCameraParamSync();
    void AllCamCfgCmdSend();

private:
	CRkcSession        *m_pSession;
	TTPMoonCamInfo  m_tCnCameraCfg1;
	TTPMoonCamInfo  m_tCnCameraCfg2;
	TTPMoonCamInfo  m_tCnCameraCfg3;
    TTPMoonCamInfo *m_pTPMoonCamCfg;
    TTPMoonCamInfo  m_atOldCamCfg[3];  //导入界面参数时，原摄像机参数
				
	u8	m_byCameraSel;
	u8  m_byCameraSyncSel;
	EmH650Gamma    m_emH650Gamma;

	TTPCamPre       m_atTPCamPre[MAX_CAMERA_Pre_NUM];   //显示器信息 
    EmTPMechanism  m_emTPMechanism;  //机芯类型
    BOOL           m_bSetAllCamCfg;  //是否在设置界面参数
    BOOL           m_bOutputFmtChg;  //输出制式是否改变  /*仅用于导入界面参数时*/
};

#endif // !defined(AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_)
