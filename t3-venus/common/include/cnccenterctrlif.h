/*****************************************************************************
模块名      : cnclib中控信息的接口
文件名      : cncconfctrlif.h
相关文件    : 
文件实现功能: cnstool中控信息查看
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/11/27   1.0					  创建
******************************************************************************/
#ifndef _CNCCENTERCONTROLIF_H_
#define _CNCCENTERCONTROLIF_H_

#include "kdvdispevent.h"

class CCncCenterCtrlIF : public CKdvDispEvent
{
public:
    /** 
	* 功能  设置系统电源
	* @param [in]  emPower  开关
	* @return 
	* @remarks 
	*/
    virtual u16 SetSysPower( EmSchPower emPower ) = 0;

    virtual u16 SetSysAllLight( EmSchLight emLight ) = 0;
    /** 
	* 功能  设置主灯开关
	* @param [in]  emMidLight  开关
	* @return 
	* @remarks 
	*/
    virtual u16 SetMainLight( EmSchMidLight emMidLight ) = 0;
    /** 
	* 功能  设置辅灯开关
	* @param [in]  emScrLight  开关
	* @return 
	* @remarks 
	*/
    virtual u16 SetAuxiLight( EmSchScrLight emScrLight ) = 0;

    /** 
	* 功能  选择电视机
	* @param [in]  byIndex  序号
	* @return 
	* @remarks 
	*/
    virtual u16 SelectTV( u8 byIndex ) = 0;
    /** 
	* 功能  设置电视机电源
	* @param [in]  byIndex  索引
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVPowerMode( u8 byIndex, EmTvPowerMode emMode ) = 0;
    /** 
	* 功能  设置电视机视听模式
	* @param [in]  emMode  视听模式
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVAudVisMode( EmTVAudVisMode emMode ) = 0;
    /** 
	* 功能  设置电视机显示模式
	* @param [in]  emMode  显示模式
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVDisMode( EmTVDisplayMode emMode ) = 0;
    /** 
	* 功能  设置电视机输入选择
	* @param [in]  emSelect  输入选择
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVInpSelect( u8 byIndex, EmTVInputSelect emSelect ) = 0;
    /** 
	* 功能  获取电视机配置
	* @return TCentreTVCfg*  电视机配置数组指针
	*/
    virtual TCentreTVCfg* GetCentreTVCfg() = 0; 

    /** 
	* 功能  设置文档摄像机开关
    * @param [in]  emPower  开关
	* @return 
	*/
    virtual u16 SetDCamPower( EmDCamPower emPower ) = 0;
    /** 
	* 功能  设置文档摄像机自动聚焦模式
	* @param [in]  emMode  模式
	* @return 
	*/
    virtual u16 SetDCamAFMode( EmDCamAFMode emMode ) = 0;
    /** 
	* 功能  设置文档摄像机白平衡模式
	* @param [in]  emMode  模式
	* @return 
	*/
    virtual u16 SetDCamWBMode( EmDCamWBMode emMode ) = 0;
    /** 
	* 功能  设置文档摄像机视野调节
	* @param [in]  emZoom  视野操作 zoom+/zoom- ,emAction 开始 /停止 
	* @return 
	*/
    virtual u16 SetDCamZoom( EmDCamZoom emZoom, EmCnAction emAction ) = 0;
	/** 
	* 功能  设置文档摄像机视眼值
	* @param [in]  wZoom  视野值
	* @return 
	*/
	virtual	u16 SetDCamZoomValueCmd( const u16& wZoom ) = 0;
	/** 
	* 功能  保存文档摄像机预置位
	* @param [in]  emNum  预置位
	* @return 
	*/
    virtual u16 SetDCamPreset( EmDCamPresetNum emNum ) = 0;
    /** 
	* 功能  调度文档摄像机预置位
	* @param [in]  emNum  预置位
	* @return 
	*/
    virtual u16 SetDCamRecall( EmDCamRecallNum emNum ) = 0;
	/** 
	* 功能  设置空调界面的电源开关
	* @param [in] emPower 电源开关
	* @return 
	*/
/*    virtual u16 SetAirPower( EmCentreACPower emPower ) = 0;*/
	/** 
	* 功能  设置空调界面的空调模式
	* @param [in]  emMode 空调模式
	* @return 
	*/
    virtual u16 SetACMode( EmCentreACMode emMode ) = 0;
	/** 
	* 功能  设置空调温度
	* @param [in]  byTemp  温度
	* @return 
	* @remarks 
	*/
    virtual u16 SetACTemp( u8 byTemp ) = 0;
	/** 
	* 功能  设置空调界面新风模式
	* @param [in] byVol 新风模式
	* @return 
	* @remarks 
	*/
    virtual u16 SetACAirVol( EmCentreACAirVol emAirVol ) = 0;
	/** 
	* 功能  选择空调
	* @param [in]  byIndex  序号
	* @return 
	* @remarks 
	*/
    virtual u16 SelectAir( u8 byIndex ) = 0;
	/** 
	* 功能  获取空调界面配置
	* @return TCentreTVCfg*  空调界面配置数组指针
	*/
    virtual void GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg )const = 0;
    /** 
	* 功能  设置空调电源
	* @param [in]  byIndex  索引
	* @return 
	* @remarks 
	*/
    virtual u16 SetACPowerMode( u8 byIndex, EmCentreACPower emMode ) = 0;
	/** 
	* 功能  设置应用到所有
	* @param [in]  byIndex  索引
	* @return 
	* @remarks 
	*/
    virtual u16 SetApplyToAll( u8 byIndex, BOOL** atbIsCtrl ) = 0;
	/** 
	* 功能  设置应用到所有
		* @param [in]  byIndex  索引
		* @return 
		* @remarks 
	*/
	virtual BOOL* GetApplyToAllInfo() = 0;

	/** 
	* 功能  设置中控电视墙
		* @param [in]  
		* @return 
		* @remarks 
	*/
	virtual u16 SetDisplayCmd( BOOL bDisplay, const TTPDisplayType& tDisplayType1, const TTPDisplayType& tDisplayType3 ) = 0;
	/** 
	* 功能  设置电视机型号
		* @param [in]  
		* @return 
		* @remarks 
	*/
	virtual u16 SetCentreTVModle( EmTVModle emTvMode) = 0;
	virtual u16 SetDisplayShowCmd( BOOL bDisplayShow) = 0;
	//获取电视墙内信号源状态
	virtual const BOOL& GetDisplayState() const = 0;
	virtual const TTPDisplayType& GetDisplayType1() const = 0;
	virtual const TTPDisplayType& GetDisplayType3() const = 0;

	virtual const BOOL& GetDisplayShowState() const = 0;

		/** 
	* 功能  窗帘界面操作命令
		* @param [in]  
		* @return 
		* @remarks 
	*/
	virtual u16 SetCurtainState( BOOL** bIsCtrl, EmCurAction emCurAction ) = 0;	
	/** 
	* 功能  获取底层发送的窗帘名称数组
		* @param [in]  
		* @return 
		* @remarks 
	*/
	virtual void GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName )const = 0;

	virtual const TCentreCurInfo& GetCurtainInfo( ) const = 0;

	virtual	u16 SetPanCamNumber( const u8 &byPanCamNum ) const = 0;

	virtual u16 SetDCCamFocus( EmFocus emFocusMode ,EmCnAction emAction ) const = 0;

	virtual	u16 SetDCCamExposure( EmExpMode emExpMode ) const = 0;

	virtual	u16 SetDCCamExpGainCmd( EmDCamGain emExpGain ) const = 0;
	
	virtual	u16 SetDCCamAperture( EmDCamIris emAperture ) const = 0;

	virtual	u16 SetDCCamShutCmd( EmDCamShutSpd emShutSpd ) const = 0;

	virtual	u16 SetDcCamRGainCmd( const u16& wRGain ) const =0;
	virtual	u16 SetDcCamBGainCmd( const u16& wRGain ) const =0;
	virtual u16 SetCurtainNumberCmd( const u8& byCurNum ) const = 0;
	virtual u16 SetCurtainName( const u8& byCurIndex, const TCentreCurName &tCurtainName) const =0;
	virtual u16 SetCurtainOpen( const BOOL& bOpen ) const = 0;
	virtual u16 SetDuoVideoCmd( const BOOL& bOpen ) const = 0;
	virtual u16 SetDCCamOpenCmd( const BOOL& bOpen ) const = 0;
	virtual u16 SetDCCamPreset( const BOOL& bOpen ) const = 0;
	virtual u16 SetAirConditionCmd( const u8& byAcNum ) const = 0;
	virtual u16 SetDcCamModel( EmDCamProType emDcCamType ) const = 0;
	virtual u16 SetPaCamModel( EmQCamProType emDPaCamType ) const = 0;
};
#endif