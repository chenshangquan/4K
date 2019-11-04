/*****************************************************************************
模块名      : 窗口相关的cnclib数据模块
文件名      : cnclibdatamgr.h
相关文件    : cnclib.h
文件实现功能: 转发来自cnclib的消息，提供访问cnclib的接口
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/23     1.0						创建
******************************************************************************/
#include "cnsToolDll.h"
#include "cnclib.h"
#include "msgdispatch.h"
#include "sessionmgr.h"

#ifndef CCNCLIBDATAMGR_H
#define CCNCLIBDATAMGR_H

class CCnclibDataMgr : public CWnd
{
public:

	~CCnclibDataMgr();
	/** 功能   初始化CCnclibDataMgr类
	*  @param[out]
	*  @return 
	*/
	void InitDataMgr();
	
	//判断是否使用新用户名和密码
	bool CheckVerNew();

	u16 GetSoftVersionInfo( s8 achVerInfo[] );

	u16 GetEmCnModelInfo(EmCnModel *pEmCnModel) const;
    /**
	* 功能:  获取本地cns会议状态
	* @param [out]tConfInfo  本级cns参加的会议信息
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
    TTPCnsConfStatus GetLocalCnsConfState() const; 

   
	/** 功能:  判断本地cns会议是否连接 
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*/
	BOOL32 IsInConf();
    
	/** 功能   获得网络配置
	*  @param[out] tInfo 网络配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetEthnetCfg( TTPEthnetInfo& tInfo );

	/** 功能   获得SIP配置
	*  @param[in] tSipCfg SIP配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetSipCfg( TTPSipRegistrarCfg& tSipCfg )const;


    /** 功能   获得Gk配置
	*  @param[in] tGkCfg
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetGkCfg( TTPGKCfg& tGkCfg )const;
	
	/** 功能   获得CCnclibDataMgr自身的指针
	*  @param[in] 
	*  @return 成功返回CCnclibDataMgr类型的指针
	*/
	static CCnclibDataMgr* GetDataMgrIF();

	/** 功能   获得云配置
	*  @param[in] tGkCfg
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetCloudCfg(  TTPCloudPlatServerCfg& tCloudCfg )const;

	/**
	* 功能:	获取登录cns的IP
	*  @param[in] u32  IP
	*  @return  
    */
	u16 GetLoginIp( u32 &dwIP )const;

	/**
	* 功能:  获取cns信息:CNS会场名称、号码、地址、屏数、是否有双流源 
	*  @param[in] tCnsInfo：本CNS信息
	*  @return 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	u16 GetLocalCnsInfo( TTPCnsInfo& tCnsInfo )const;

	/** 功能   获得NAT配置
	*  @param[in] tInfo NAT配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetNATCfg( TTPNatCfg& tInfo )const;

	/** 功能   获取中控显示器信息
	*  @param[in]tCentreTVCfg  显示器开关状态信息
	*  @return 成功返回0,失败返回非0错误码
	*/
	TCentreTVCfg* GetCentreTVCfg()const;

	/** 功能   获取中控摄像机信息
	*  @param[in]vecTCnCameraCfg  摄像机开关状态信息
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetCamInfo( vector<TCnCameraCfg>& vecTCnCameraCfg )const;

	/** 功能   获得音频接口信息
	*  @param[in]pAudioPortInfo   音频接口信息
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetAudioPortInfo( TTpAudioPortInfo** pAudioPortInfo )const;

	/** 功能   获得音频均衡器信息
	*  @param[in]pAudioPortInfo   音频均衡器信息
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetAudioEqualizer( TTPEqualizer** pEqualizer )const;

	/** 功能   获得音频混音数信息
	*  @param[in]pAudioPortInfo   音频混音数信息
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetAudiotMixer( u8** pAudioMixerInfo )const;

	/** 功能   获得网络丢包信息
	*  @param[in]tLostPacketInfo  网络丢包信息
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetLostPacketInfo( CString& tLostPacketInfo )const;

	/** 功能   获得上下行速率信息
	*  @param[in]TTPUpDownSpeedInfo   上传速率信息
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetUpDownstreamRate( TTPUpDownSpeedInfo& tUpDownSpeedInfo )const;

	/** 功能   获取视频端口诊断结果
	*  @param[in]tVideoDiagInfo  视频端口诊断信息
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetVideoDiagInfo( TTPVideoDiagInfo& tVideoDiagInfo )const;

	/** 功能   获取音频端口诊断结果
	*  @param[in]tAudioDiagInfo  音频端口诊断信息
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetAudioDiagInfo( TTPAudioDiagInfo& tAudioDiagInfo )const;

	//获取网络安全FTP和TELNET信息
	u16 GetFtpInfo( TTPFtpInfo& tTPFtpInfo )const;

	u16 GetTelnetInfo( TTPTelnetInfo& tTPTelnetInfo)const;

	/** 功能   获得Tpad列表信息
	*  @param[in]tTPadList   Tpad列表信息
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetTpadList( TTPTPadList& tTPadList )const;

	/** 功能   获得CPU/内存信息
	*  @param[in]
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetSysInfo( TTPSysInfo& tSysInfo )const;


	/** 功能   获得会议信息
	*  @param[in]
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetCnConfStatus( TTPCnsConfStatus& tCnsConfStatus )const;

	/** 功能   获得会议信息2
	*  @param[in]
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetCnConfVideoParam( TTPCnConfInfo& tCnVideoParam )const;

	/** 
	* 功能  	获取被选中的摄像机
	* @param [in] 	 
	* @return  成功返回0,失败返回非0错误码
	*/		
	u16 GetCamSel( u8& byCameraIndx )const;

	/** 
	* 功能  	获取视野是否在OSD上显示比例
	* @param [in] 	 
	* @return  成功返回0,失败返回非0错误码
	*/	
	u16 GetCamOSD( EmOSDShow& emOSDShow )const;

	/** 
	* 功能  	获取开机是否调用预置位1状态
	* @param [in] 	 
	* @return  成功返回0,失败返回非0错误码
	*/	
	u16 GetCamPresetMove( BOOL& bUsed )const;

	/** 
	* 功能  	获取摄像机增益值
	* @param [in] 	 
	* @return  成功返回0,失败返回非0错误码 
	*/	
	u16 GetCamGain( EmGain& emGain )const;

	/** 
	* 功能  	获取摄像机快门值
	* @param [in] 	 
	* @return  成功返回0,失败返回非0错误码 
	*/	
	u16 GetCamShutSpd( EmShutSpd& emShutSpd )const;

	/** 
	* 功能  	获取摄像机背光模式
	* @param [in] 	 
	* @return  成功返回0,失败返回非0错误码
	*/	
	u16 GetCamBackLightType( EmBackLightType& emBackLightType )const;

	/** 
	* 功能  	获取摄像机背光模式对应的值
	* @param [in] 	 
	* @return  成功返回0,失败返回非0错误码
	*/	
	u16 GetCamBackLightIndex( u8& byMulti)const;

	/** 
	* 功能  	获取摄像机光圈大小
	* @param [in] 	 
	* @return  成功返回0,失败返回非0错误码
	*/	
	u16 GetCamAperture( u8& byAperture )const;

	/** 
	* 功能  	获取摄像机白平衡调节模式RGain
	* @param [in] 	 
	* @return  
	*/	
	u16 GetCamRGain( u16& wRGain )const;

	/** 
	* 功能  	获取摄像机白平衡调节模式BGain
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamBGain( u16& wBGain)const;

	/** 
	* 功能  	获取摄像机Pic模式调节状态
	* @param [in] 	 
	* @return  EmPicSceMode  分为:日光灯/太阳灯/手动
	* @remarks 
	*/	
	u16 GetCamPicSceneMode( EmPicSceMode& emPicSceMode )const;

	/** 
	* 功能  	获取摄像机Pic模式CAMMA调节状态
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamGamma( EmGamma& emGamma )const;

	/** 
	* 功能  	获取摄像机Pic模式光圈调节值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamPicSceApt( u8& byPicSceApt )const;

	/** 
	* 功能  	获取摄像机图片调节中的对比度值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamContrast( u16& wContrast )const;

	/** 
	* 功能  	获取摄像机图片调节中的色度值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamHue( u16& wHue )const;

	/** 
	* 功能  	获取摄像机图片调节中的饱和度值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamSaturat( u16& wSaturat )const;

	/** 
	* 功能  	获取摄像机图片调节中的亮度值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamBright( u16& wBright )const;

	/** 
	* 功能  	获取摄像机噪点过滤模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamNRStmClean( EmStmClean& emStmClean )const;

	/** 
	* 功能  	获取摄像机3D降噪过滤模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCam3DNR( Em3DNR& em3DNR )const;	

	/** 
	* 功能  	获取当前摄像机配置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamCfg( TCnCameraCfg& tCnCameraCfg )const;

	/** 
	* 功能  	获取曝光模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamExpMode( EmExpMode& emExpMode )const;

	/** 
	* 功能  	获取白平衡模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamWBMode( EmWBMode& emExpMode )const;

	/** 
	* 功能  	获取zoom
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamZoom( u16& wZoom )const;

	/** 
	* 功能  	获取网管服务器数据
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )const;

	u16 GetRouteInfoData( vector<TRouteCfg> &vecTRouteCfg )const;

    /** 功能   获得演示源信息
	*  @param[out] tDualSrcinfo 演示源配置
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 GetDualSrcInfo( TDualSrcInfo& tDualSrcinfo );

	/** 
	* 功能  	获取演示源输出接口信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetVgaMixInfo( TTPVgaMixInfo &tVgaMixInfo )const;
	/** 
	* 功能  	获取呼叫服务器信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCallServerInfo( TTPCallSerInfo& tCallSerInfo )const;
	/** 
	* 功能  	获取升级服务器地址
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetUpgradeSerInfo( TTPUpgradeSer& tUpgradeSer )const;

	u16 GetWBSerIp( TTPDataConfInfo& tWBSerIp )const;

	u16 GetQtEncryptCfg(TTpQtEncryptCfg& tTpQtEncryptCfg) const;

	u16 GetNtpSerIP( TTPNtpSer& tTpNtpSer ) const;

	u16 GetMatrixSerInfo(TTPMatrixServerInfo& tTPMatrixServerInfo) const;
	/** 
	* 功能  	获取会议优选格式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* 功能  	获取演示优选格式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* 功能  	获取单屏码率
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCallRateInfo( u16& wCallRate )const;
	/** 
	* 功能  	获取演示码率
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualCallRateInfo( u16& wDualCallRate )const;
	/** 
	* 功能  	获取会议轮询信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfPollInfo( TTPPollInfo& tPollInfo )const;
	/** 
	* 功能  	获取会议讨论信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfDisInfo( BOOL& bDis )const;
	/** 
	* 功能  	获取音频格式信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	EmTpAudioFormat GetAudioFormatInfo()const;
	/** 
	* 功能  	获取会场是否接收演示
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	bool IsRcvDual();
	/** 
	* 功能  	获取中控电视墙开启状态
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	BOOL GetDisplayState() const;

	BOOL GetDisplayShowState() const;
	/** 
	* 功能  	获取中控电视墙显示器1的信号源
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	TTPDisplayType GetDisplayType1() const;
	/** 
	* 功能  	获取中控电视墙显示器3的信号源
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	TTPDisplayType GetDisplayType3() const;

	TCentreCurInfo GetCurtainInfo() const;

	u16 GetAudioInfo( TTPMPAudioInfo* pAudioInfo )const;

	u16 GetWhiteNoiseInfo( BOOL **pWhiteNoise )const;

	u16 GetMainAudioInfo( TTPVideoInfoTool *pVideoSource ) const;
	
	u16 GetDisplaySourceList( TVgaInfo ** pDisplaySource ) const;
	
	u16 GetDisplayStrategy( TTPDualDisplayStrategy *pDualDisplayStrategy ) const;
	
	u16 GetDefaultDisplay( EmVgaType *pDefaultDisplay ) const;

	u16 GetImageParam( TTPImageAdjustParam **pImageParam ) const;

	u16 GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg ) const;
   	/** 
	* 功能  	获取Moon904k摄像机曝光增益
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetMoon90CamExpGain(u8& byExpGain) const;

    /** 
	* 功能  	获取Moon904k摄像机曝光补偿
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
    u16 GetMoon90CamExCompRate(u16& wExCompRate) const;

    /** 
	* 功能  	获取Moon904k摄像机背光补偿等级
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
    u16 GetMoon90CamBLCRate(u8& byLevel) const;

    /** 
	* 功能  	获取Moon904k摄像机宽动态等级
	* @param [in] 	 
    * @return  
    * @remarks 
    */	
    u16 GetMoon90CamWDRRate(u8& byLevel) const;
protected:
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam); 
private:
	CCnclibDataMgr();

private:
	static CCnclibDataMgr* m_pThis;
};

#define LIBDATAMGRPTR   CCnclibDataMgr::GetDataMgrIF()

#endif