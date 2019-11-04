#include "cnsSession.h"
#include "eventoutcnsmp.h"
#include "eventoutcnscamera.h"

class CCncSysCtrl : public CCncSysCtrlIF
{
public:
	CCncSysCtrl( CCnsSession &cSession );
	~CCncSysCtrl();
	/** 
	* 功能  	向服务器请求cpu/内存的信息
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual u16 ReqSysInfo();
	/** 
	* 功能  	接收服务器发来的cpu/内存的信息
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual const TTPSysInfo& GetSysInfo()const;
	/** 
	* 功能  	获取会议信息
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
 	virtual const TTPCnsConfStatus& GetCnConfStatus()const;
	/** 
	* 功能  	获取会议信息
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual	const TTPCnConfInfo& GetCnConfVideoParam()const;	
	/** 
	* 功能  	选择摄像机
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 CamSelCmd( const u8& byCameraIndx );	
	/** 
	* 功能  	获取被选中的摄像机
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u8 GetCamSel()const;
	/** 
	* 功能  	恢复摄像机默认参数
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamResetCmd();			
	/** 
	* 功能  	视野设置
	* @param [in] 	 EmZoom  分为:远，近
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCamZoomCmd( const EmZoom& emZoom, const EmZoomStatus& emZoomStatus );		
	/** 
	* 功能  	视野是否在OSD上显示比例
	* @param [in] 	 EmOSDShow  分为:on，off
	* @return  
	* @remarks 
	*/	
	virtual	u16 SetCamOSDCmd( const EmOSDShow& emOSDShow );	
	/** 
	* 功能  	获取视野是否在OSD上显示比例
	* @param [in] 	 
	* @return  EmOSDShow  分为:on，off
	* @remarks 
	*/	
	virtual EmOSDShow GetCamOSD();
	/** 
	* 功能  	摄像机自动聚焦
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u16 SetCamAutoFocusCmd(const EmFocusMode& emFocusMode);
	/** 
	* 功能  	摄像机手动聚焦
	* @param [in] 	 EmFocus : 远焦/近焦	EmCnAction :  开始/停止
	* @return  
	* @remarks 
	*/	
	virtual	u16 SetCamFocusCmd( const EmFocus& emFocus, const EmCnAction& emCnAction );		
	/** 
	* 功能  	设置预置位参数
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamPresetSaveCmd();
	/** 
	* 功能  	设置开机调用预置位1
	* @param [in] 	 BOOL
	* @return  
	* @remarks 
	*/	
	virtual	u16 SetCamPresetMoveCmd( const BOOL& bPresetMove );
	/** 
	* 功能  	获取开机调用预置位1状态
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual BOOL GetCamPresetMove();
	/** 
	* 功能  	设置自动曝光
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 CamAutoExposureCmd( const EmExpMode& emExpAuto );
	/** 
	* 功能  	增益
	* @param [in] 	 EmGain 增益范围 0dB  3dB  6dB ···42dB
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamGainCmd( const EmGain& emGain );	
	/** 
	* 功能  	获取摄像机增益值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmGain GetCamGain();
	/** 
	* 功能  快门调节	快门范围 1/60  1/100 1/250.....1/4000  1/10000
	* @param [in]  EmShutSpd
	* @return  
	* @remarks 
	*/
	virtual	u16 CamShutSpdCmd( const EmShutSpd& emShutSpd );
	/** 
	* 功能  	获取摄像机快门值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmShutSpd GetCamShutSpd();
	/** 
	* 功能  背光模式调节
	* @param [in]  EmBackLightType  背光模式:关闭，multi（默认7，范围0-15），center，face detect
	*			   u8  = TP_INVALID_INDEX 非multi模式  0--15 multi模式调节
	* @return  
	* @remarks 
	*/
	virtual	u16 CamBackLightCmd( const EmBackLightType& emBackLightType, const u8& byMulti );
	/** 
	* 功能  	获取摄像机背光模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmBackLightType GetCamBackLightType();
	/** 
	* 功能  	获取摄像机背光模式对应的值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u8 GetCamBackLightIndex();
	/** 
	* 功能  光圈大小调节
	* @param [in]  u8  光圈大小 范围 0--100			   
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamAperture( const u8& byAperture);	
	/** 
	* 功能  	获取摄像机光圈大小
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u8 GetCamAperture();
	/** 
	* 功能  白平衡调节(分为自动和手动)
	* @param [in] 		   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamAutoWBCmd( const EmWBMode& emWBMode );	
	/** 
	* 功能  R+调节
	* @param [in] 	u16  R Gain 范围 0--100	   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamRGainCmd( const u16& wRGain );
	/** 
	* 功能  	获取摄像机白平衡调节模式R+调节值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamRGain();
	/** 
	* 功能  B+调节
	* @param [in] 	u16  B Gain 范围 0--100	   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamBGainCmd( const u16& wBGain );
	/** 
	* 功能  	获取摄像机白平衡调节模式B+调节值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamBGain();
	/** 
	* 功能  模式调节  
	* @param [in] 	EmPicSceMode  分为:日光灯/太阳灯/手动
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamPicSceneModeCmd( const EmPicSceMode& emPicSceMode );	
	/** 
	* 功能  	获取摄像机Pic模式调节状态
	* @param [in] 	 
	* @return  EmPicSceMode  分为:日光灯/太阳灯/手动
	* @remarks 
	*/	
	virtual EmPicSceMode GetCamPicSceneMode();
	/** 
	* 功能  手动模式中的CAMMA调节  
	* @param [in] 	EmGamma  分为:emGammaOff、emGammaOn 、emSmart1、 emStrat2
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamGammaCmd( const EmGamma& emGamma );
	/** 
	* 功能  	获取摄像机Pic模式CAMMA调节状态
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmGamma GetCamGamma();
	/** 
	* 功能  手动模式中的光圈调节  
	* @param [in]   u8 光圈大小  1--15
	* @return  
	* @remarks 
	*/	
    virtual	u16 CamPicSceAptCmd( const u8& byPicSceApt );
	/** 
	* 功能  	获取摄像机Pic模式光圈调节值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u8 GetCamPicSceApt();
	/** 
	* 功能  图片调节中的对比度调节
	* @param [in]   u16  大小  0--200
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamContrastCmd( const u16& wContrast );	
	/** 
	* 功能  	获取摄像机图片调节中的对比度值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamContrast();
	/** 
	* 功能  图片调节中的色度调节
	* @param [in]   u16  大小  0--200
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamHueCmd( const u16& wHue );
	/** 
	* 功能  	获取摄像机图片调节中的色度值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamHue();
	/** 
	* 功能  图片调节中的饱和度调节
	* @param [in]   u16  大小  0--200
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamSaturatCmd( const u16& wSaturat );
	/** 
	* 功能  	获取摄像机图片调节中的饱和度值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamSaturat();
	/** 
	* 功能  图片调节中的亮度调节
	* @param [in]   u16  大小  0--200
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamBrightCmd( const u16& wBright );	
	/** 
	* 功能  	获取摄像机图片调节中的亮度值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamBright();
	/** 
	* 功能  降噪---摄像机噪点过滤调节命令
	* @param [in]   EmStmClean  默认LOW  范围OFF,LOW,MID,HIGH
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamNRStmCleanCmd( const EmStmClean& emStmClean );
	/** 
	* 功能  	获取摄像机噪点过滤模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmStmClean GetCamNRStmClean();
	/** 
	* 功能  降噪---3D降噪调节命令
	* @param [in]   Em3DNR   em3DNROff 关OFF，em3DNROn 开
	* @return  
	* @remarks 
	*/	
	virtual	u16 Cam3DNRCmd( const Em3DNR& em3DNR );	
	/** 
	* 功能  	获取摄像机3D降噪过滤模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual Em3DNR GetCam3DNR();

	/** 
	* 功能  	获取全部摄像机配置
	* @param [in] 	 摄像机信息
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamCfgAll( vector<TCnCameraCfg>& vecTCnCameraCfg );

	/** 
	* 功能  	获取当前摄像机配置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TCnCameraCfg GetCamCfg();

	/** 
	* 功能  	获取曝光模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmExpMode GetCamExpMode();

	/** 
	* 功能  	获取白平衡模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmWBMode GetCamWBMode();

	/** 
	* 功能  	向服务器发送导入通知
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual	u16 SetLoadCameraFileNty();

	/** 
	* 功能  	获取zoom
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamZoom();

	/** 
	* 功能  	设置zoom值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCamZoomCmd( const u16& wZoom );

	/** 
	* 功能  	设置摄像机类型
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCamTypeCmd( const EmCamType& emCamType );

	/** 
	* 功能  	Sony摄像机背光调节命令
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SonyBackLightCmd( const BOOL& bLight );

	/** 
	* 功能  	Sony摄像机降噪设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SonyStmClenCmd( const BOOL& bClen, const u8& bylevel );

    /** 
	* 功能  	Moon904K摄像机设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SetMoon904KCamCfgCmd( const EmCamCfgType& emCamCfgType, const u32& dwValue );

   	/** 
	* 功能  	获取Moon904k摄像机曝光增益
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u8 GetMoon90CamExpGain();

    /** 
	* 功能  	获取Moon904k摄像机曝光补偿
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
    virtual u16 GetMoon90CamExCompRate();

    /** 
	* 功能  	获取Moon904k摄像机背光补偿等级
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
    virtual u8 GetMoon90CamBLCRate();

    /** 
	* 功能  	获取Moon904k摄像机宽动态等级
	* @param [in] 	 
    * @return  
    * @remarks 
    */	
    virtual u8 GetMoon90CamWDRRate();

protected:
	virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();
	void OnLinkBreak(const CMessage& cMsg);

	void OnSysInfoRsp(const CMessage& cMsg);
	void OnSysInfoNty(const CMessage& cMsg);
	void OnCnConfInfoNty(const CMessage& cMsg);
	void OnCameraCfgNty(const CMessage& cMsg);
	void OnCamSelInd(const CMessage& cMsg);
	void OnCamResetInd(const CMessage& cMsg);
	void OnCamZoomInd(const CMessage& cMsg);
	void OnCamOSDInd(const CMessage& cMsg);	
	void OnCamAutoFocusInd(const CMessage& cMsg);
	void OnCamFocusInd(const CMessage& cMsg);
	void OnCamPresetSaveInd(const CMessage& cMsg);
	void OnAutoExposureInd(const CMessage& cMsg);
	void OnCamGainInd(const CMessage& cMsg);
	void OnCamShutSpdCInd(const CMessage& cMsg);
	void OnCamBackLightInd(const CMessage& cMsg);
	void OnCamApertureInd(const CMessage& cMsg);
	void OnCamAutoWBInd(const CMessage& cMsg);
	void OnCamRGainInd(const CMessage& cMsg);
	void OnCamBGainInd(const CMessage& cMsg);
	void OnCamPicSceneModeInd(const CMessage& cMsg);
	void OnCamGammaInd(const CMessage& cMsg);
	void OnCamPicSceAptInd(const CMessage& cMsg);
	void OnCamContrastInd(const CMessage& cMsg);
	void OnCamHueInd(const CMessage& cMsg);
	void OnCamSaturatInd(const CMessage& cMsg);
	void OnCamBrightInd(const CMessage& cMsg);
	void OnCamNRStmCleanInd(const CMessage& cMsg);
	void OnCam3DNRInd(const CMessage& cMsg);
	void OnCamPresetMoveInd(const CMessage& cMsg);
	void OnSetCameraZoomInd(const CMessage& cMsg);
	void OnCameraPowerOnNty(const CMessage& cMsg);
	void OnSonyStmClenInd(const CMessage& cMsg);
    void OnMoon904KCamCfgInd(const CMessage& cMsg);
    void OnSrcOffLineNty(const CMessage& cMsg);

public:
	void SetCameraCfgPtr();

private:
	CCnsSession		*m_pSession;
	TTPSysInfo	     m_tSysInfo;
	TTPCnsConfStatus m_tConfStatus;
	TTPCnConfInfo    m_tVideoParam;
	u8	m_byCameraSel;
	TCnCameraCfg m_tCnCameraCfg1;
	TCnCameraCfg m_tCnCameraCfg2;
	TCnCameraCfg m_tCnCameraCfg3;
	TCnCameraCfg *m_pTCnCameraCfg;
};
