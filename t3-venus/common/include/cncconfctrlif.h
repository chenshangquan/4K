/*****************************************************************************
模块名      : cmc cnclib接口
文件名      : cncconfctrlif.h
相关文件    : 
文件实现功能: cns会议控制
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/30   1.0         肖楚然        创建
******************************************************************************/
#ifndef __CNCCONFCTRLIF_H__
#define __CNCCONFCTRLIF_H__

#include "kdvdispevent.h"
#include "tpstruct.h"

class CCncConfCtrlIF : public CKdvDispEvent
{
public:  //请求
	

     /** 
	* 功能  开启点对点会议
	* @return tDialParam 相应参数
	* @remarks 
	*/
    virtual const u16 MakeCall( TTPDialParam &tDialParam ) = 0 ;

    /** 功能 结束ptp会议
	 *  @return T 
	 *  @remarks 
	 */
    virtual const u16 HungupPtpConf() = 0;

	/** 
	* 功能  设置会场内发言人
	* @param [in]  byIndex  序号
	* @return 
	* @remarks 
	*/
	virtual u16 SetInnerSpeaker( u8 byIndex ) = 0;

	/** 
	* 功能  开启/关闭本地哑音
	* @param [in]  bMute  开启/关闭
	* @return  
	* @remarks 
	*/
	virtual u16 SetCnsMute( BOOL bMute = TRUE ) = 0;
	/** 
	* 功能  开启/关闭本地静音
	* @param [in]  bQutie  开启/关闭
	* @return  
	* @remarks 
	*/
    virtual u16 SetCnsQutie( BOOL bQutie = TRUE ) = 0;
	
	/** 
	* 功能  调节输入声音
	* @return byVolume 音量
	* @remarks 
	*/
	virtual u16 AdjustInputVol( u8 byVolume ) = 0;
	
	/** 
	* 功能  调节输出声音
	* @return byVolume 音量
	* @remarks 
	*/
	virtual u16 AdjustOutputVol( u8 byVolum ) = 0;

	/** 
	* 功能  清空屏信息
	* @return vector<TScreenInfo> 屏信息
	* @remarks 
	*/
	virtual void ClearCnsScreenInfo() = 0;

    /** 
	* 功能  设置选看
    * @param [in]  byScreenID  屏号
    * @param [in]  wEpID  选看的cnsID
	* @return  
	* @remarks 
	*/
	virtual u16 SetSelView( u8 byScreenID, u16 wEpID ) = 0;

    /** 
	* 功能  取消选看
    * @param [in]  byScreenID  屏号 
	* @return  
	* @remarks 
	*/
	virtual u16 CancleSelView( u8 byScreenID ) = 0;

    /** 
	* 功能  开启/停止轮询
    * @param [in]  bStart   true:开启，false：关闭
	* @return  
	* @remarks 
	*/
	virtual u16 StartPoll( BOOL  bStart ) = 0;

	
    /** 
	* 功能  开启/停止双流
    * @param [in]  bStart   true:开启，false：关闭
	* @return  
	* @remarks 
	*/
	virtual u16 StartDual( BOOL  bStart ) = 0;



     /** 
	* 功能  开启/停止双流码流
	* @return  BOOL  TRUE:开启， FALSE:停止
	* @remarks 
	*/
    virtual u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVideoTransAddr , const TTPCnMediaTransPort  &tAudioTransAddr ) const = 0;

    virtual u16 StopDualCodeStream() const = 0;

    virtual u16 ReqKeyFrame( BOOL32 bForce ) const = 0;

     /** 
	* 功能  屏幕显示双流图像
	* @return   
	* @remarks 
	*/
    virtual u16 ScrnDisplayDual( const u16 wScrnID ) const = 0 ;

     /** 
	* 功能  屏幕显示双流图像
	* @return  
	* @remarks 
	*/
    virtual u16 ScrnStopDisplayDual( const u16 wScrnID ) const = 0 ;


    /** 
	* 功能  屏幕回显
	* @return    
	* @remarks 
	*/
    virtual u16 ScrnDisplayLocal( const u16 wScrnID ) const = 0 ;


    /** 
	* 功能  取消屏幕回显
	* @return    
	* @remarks 
	*/
    virtual u16 ScrnStopDisplayLocal( const u16 wScrnID ) const = 0 ;

    /** 
	* 功能  设置选看电视墙
    * @param [in]  byScreenID  屏号
	* @return  
	* @remarks 
	*/
	virtual u16 SelTVSView( u8 byScreenID ) = 0 ;

    /** 
	* 功能  取消选看电视墙
    * @param [in]  byScreenID  屏号 
	* @return  
	* @remarks 
	*/
	virtual u16 CancelSelTVSView( u8 byScreenID ) = 0 ;

public:  //获取结果

      /** 功能  获取CNS会议状态
	 *  @return TTPCnsConfStatus 会议状态
	 *  @remarks 
	 */
	virtual const TTPCnsConfStatus& GetCnsConfStatus() const =0;


    	/** 
	* 功能  获取会场内发言人
	* @return  byIndex  序号
	* @remarks 
	*/
	virtual u8 GetInnerSpeaker() const = 0;
	/** 
	* 功能  本地CNS是否哑音
	* @return  BOOL  是否哑音
	* @remarks 
	*/
	virtual BOOL IsLocalCnsMute() const = 0;
	/** 
	* 功能  本地CNS是否静音
	* @return  BOOL  是否静音
	* @remarks 
	*/
    virtual BOOL IsLocalCnsQuite() const = 0;


    /** 
	* 功能  获取输入声音
	* @return  u8  音量
	* @remarks 
	*/
	virtual const u8& GetInputVol() const = 0;


    /** 
	* 功能  获取输出声音
	* @return  u8  音量
	* @remarks 
	*/
	virtual const u8& GetOutputVol() const = 0;


    	/** 
	* 功能  获取屏信息
	* @return vector<TScreenInfo> 屏信息
	* @remarks 
	*/
	virtual const vector<TScreenInfo>& GetCnsScreenInfo() const = 0;


    /** 
	* 功能  本地CNS是否开启轮询
	* @return  BOOL  是否轮询
	* @remarks 
	*/
	virtual BOOL IsLocalCnsPoll() const = 0;

	/** 
	* 功能  本地CNS是否开启双流
	* @return  BOOL  是否双流
	* @remarks 
	*/
    virtual BOOL IsLocalCnsDual() const = 0;

    virtual TTPCnMediaTransPort GetVedioTransAddr() const = 0;

    virtual TTPCnMediaTransPort GetAudioTransAddr() const = 0;

	//开启画中画
	virtual u16 ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP ) = 0;

	virtual BOOL IsViewLocalPIP() const = 0;
   
    virtual BOOL32 IsRcvDual() const = 0;
};

#endif
