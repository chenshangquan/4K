// cncconfctrl.h: interface for the CCncConfCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCCONFCTRL_H__2EF9234D_820A_40F3_9DC4_967387311945__INCLUDED_)
#define AFX_CNCCONFCTRL_H__2EF9234D_820A_40F3_9DC4_967387311945__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnsSession.h"

class CCncConfCtrl : public CCncConfCtrlIF 
{
public:
	CCncConfCtrl(CCnsSession &cSession);
	virtual ~CCncConfCtrl();

    
    /** 
	* 功能  开启点对点会议
	* @return tDialParam 相应参数
	* @remarks 
	*/
    virtual const u16 MakeCall( TTPDialParam &tDialParam )  ;

    virtual const u16 HungupPtpConf();
	

	/** 
	* 功能  设置会场内发言人
	* @param [in]  byIndex  序号
	* @return 
	* @remarks 
	*/
	virtual u16 SetInnerSpeaker( u8 byIndex );


	/** 
	* 功能  开启/关闭本地哑音
	* @param [in]  bMute  开启/关闭
	* @return  
	* @remarks 
	*/
	virtual u16 SetCnsMute( BOOL bMute = TRUE );
	/** 
	* 功能  开启/关闭本地静音
	* @param [in]  bQutie  开启/关闭
	* @return  
	* @remarks 
	*/
    virtual u16 SetCnsQutie( BOOL bQutie = TRUE );

	/** 
	* 功能  调节输入声音
	* @return byVolume 音量
	* @remarks 
	*/
	virtual u16 AdjustInputVol( u8 byVolume );

	/** 
	* 功能  调节输出声音
	* @return byVolume 音量
	* @remarks 
	*/
	virtual u16 AdjustOutputVol( u8 byVolum );

	/** 
	* 功能  清空屏信息
	* @remarks 
	*/
	virtual void ClearCnsScreenInfo();


    /** 
	* 功能  设置选看
    * @param [in]  byScreenID  屏号
    * @param [in]  wEpID  选看的cnsID
	* @return  
	* @remarks 
	*/
	virtual u16 SetSelView( u8 byScreenID, u16 wEpID );

    /** 
	* 功能  取消选看
    * @param [in]  byScreenID  屏号 
	* @return  
	* @remarks 
	*/
	virtual u16 CancleSelView( u8 byScreenID );

   /** 
	* 功能  开启/停止轮询
    * @param [in]  bStart   true:开启，false：关闭
	* @return  
	*/
	virtual u16 StartPoll( BOOL  bStart );

	

    /** 
	* 功能  开启/停止双流
    * @param [in]  bStart   true:开启，false：关闭
	* @return  
	*/
	virtual u16 StartDual( BOOL  bStart );
 


    /** 
	* 功能  开启/停止双流码流
	* @return  BOOL  TRUE:开启， FALSE:停止
	* @remarks 
	*/
    virtual u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVideoTransAddr , const TTPCnMediaTransPort  &tAudioTransAddr ) const;
   
    virtual u16 StopDualCodeStream() const  ;

	/** 
	* 功能  请求关键帧
	* @return  BOOL  TRUE:不受关键帧保护约束，强制发送关键帧， FALSE:受关键帧包含约束 2012.8.16 by yjj
	* @remarks 
	*/
    virtual u16 ReqKeyFrame( BOOL32 bForce ) const ;


     /** 
	* 功能  屏幕显示双流图像
	* @return    
	* @remarks 
	*/
    virtual u16 ScrnDisplayDual( const u16 wScrnID ) const ;


    /** 
	* 功能  屏幕显示双流图像
	* @return  
	* @remarks 
	*/
    virtual u16 ScrnStopDisplayDual( const u16 wScrnID ) const ;

     
    /** 
	* 功能  屏幕回显
	* @return    
	* @remarks 
	*/
    virtual u16 ScrnDisplayLocal( const u16 wScrnID ) const ;


    /** 
	* 功能  取消屏幕回显
	* @return    
	* @remarks 
	*/
    virtual u16 ScrnStopDisplayLocal( const u16 wScrnID ) const ;
 
	//开启画中画
	virtual u16 ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP );

    /** 
	* 功能  设置选看电视墙
    * @param [in]  byScreenID  屏号
	* @return  
	* @remarks 
	*/
	virtual u16 SelTVSView( u8 byScreenID );

    /** 
	* 功能  取消选看电视墙
    * @param [in]  byScreenID  屏号 
	* @return  
	* @remarks 
	*/
	virtual u16 CancelSelTVSView( u8 byScreenID );

public: //获取lib中缓存信息
   /** 
	* 功能  获取输出声音
	* @return  u8  音量
	* @remarks 
	*/
	virtual const u8& GetOutputVol() const;


   /** 
	* 功能  获取输入声音
	* @return  u8  音量
	* @remarks 
	*/
	virtual const u8& GetInputVol() const;


   /** 
	* 功能  获取会场内发言人
	* @return byIndex  序号
	* @remarks 
	*/
	virtual u8 GetInnerSpeaker() const;

	/** 
	* 功能  本地CNS是否哑音
	* @return  BOOL  是否哑音
	* @remarks 
	*/
	virtual BOOL IsLocalCnsMute() const;
	/** 
	* 功能  本地CNS是否静音
	* @return  BOOL  是否静音
	* @remarks 
	*/
    virtual BOOL IsLocalCnsQuite() const;

	/** 
	* 功能  本地画中画是否开启
	* @return  
	* @remarks 
	*/
    virtual BOOL IsViewLocalPIP() const;

    /** 
	* 功能  获取CNS会议状态
	* @return TTPCnsConfStatus 会议状态
	* @remarks 
	*/
	virtual const TTPCnsConfStatus& GetCnsConfStatus() const;


   /** 
	* 功能  获取屏信息
	* @return vector<TScreenInfo> 屏信息
	* @remarks 
	*/
	virtual const vector<TScreenInfo>& GetCnsScreenInfo() const;


    /** 
	* 功能  本地CNS是否开启轮询
	* @return  BOOL  是否静音
	* @remarks 
	*/
	virtual BOOL IsLocalCnsPoll() const;

   /** 
	* 功能  本地CNS是否开启双流
	* @return  BOOL  是否静音
	* @remarks 
	*/
    virtual BOOL IsLocalCnsDual() const;

    virtual TTPCnMediaTransPort GetVedioTransAddr() const { return m_tVideoTranAddr ;}
    virtual TTPCnMediaTransPort GetAudioTransAddr() const { return m_tAudioTranAddr ;}


/*    virtual TScreenInfo *GetScreenInfoByID( const u8 byScreenID )  ;*/

    virtual BOOL32 IsRcvDual() const { return m_bRecvDual; }

protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();

	void OnLinkBreak(const CMessage& cMsg);

	/** 功能  会议状态通知
	* @param [in]  cMsg  消息内容
	* @return 
	* @remarks 消息  cns->cms  ev_CnConfState_Nty
	*/
	void OnConfStateNty(const CMessage& cMsg);
	/**
    * 功能: 哑音通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_tppMuteInd
	*/
	void OnMuteInd(const CMessage &cMsg);
	/**
    * 功能: 静音通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_tppQuietInd
	*/
	void OnQuietInd(const CMessage &cMsg);
	/**
    * 功能: 输入音量通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_tppInputVolumeInd  
	*/
	void OnInputVolInd(const CMessage &cMsg);
	/**
	* 功能: 输出音量通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_tppOutputVolumeInd  
	*/
	void OnOutPutVolInd(const CMessage &cMsg);
	/**
	* 功能: 设置会场发言人通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_CnSetInnerSpeaker_Ind  
	*/
	void OnSetInnerSpeaker( const CMessage &cMsg);
	/**
	* 功能: 屏显示会场通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_CnYouAreSeeing_Ind  
	*/
	void OnScreenDisplayInd(const CMessage &cMsg);

	void UpdateScreenInfo( u8 byScreen, s8* achCnsName );
    void UpdateScreenInfo( u8 byScreen, s8* achCnsName,EMPosPic emPic );
	void UpdateScreenInfo( u8 byScreen, EmTPPosStatus emStatus, EMPosPic emPos );
     
    void OnScreenStateNotify( const CMessage &cMsg );
    void OnSetSelViewRsp( const CMessage &cMsg );
    void OnStartPollRsp( const CMessage &cMsg );
    void OnStartDualRsp( const CMessage &cMsg );
	void OnPollStatusNty( const CMessage &cMsg ); 
	void OnDualStatusNty( const CMessage &cMsg );
    void OnHungupNotify( const CMessage &cMsg );

    void OnStartDualCdStrmRsp( const CMessage &cMsg );
    void OnStopDualCdStrmRsp( const CMessage &cMsg );

    void OnScrnDisplayDualRsp( const CMessage &cMsg );
    void OnStopScrnDisplayDualRsp( const CMessage &cMsg );
    
    void OnScrnDisplayLocalRsp( const CMessage &cMsg );
    void OnStopDisplayLocalRsp( const CMessage &cMsg );

    void OnRecvDualNty( const CMessage &cMsg );
	void OnCnDualOfflineNty( const CMessage &cMsg );
    void OnDualRcvInterruptNty( const CMessage &cMsg );

	void OnViewLocalPIPInd( const CMessage &cMsg );
	void OnViewLocalPIPNty( const CMessage &cMsg );
	void OnSetSelTVSViewRsp( const CMessage &cMsg );
	void OnDualCodeEnCryptKeyNty( const CMessage &cMsg );
private:
	CCnsSession      *m_pSession;

	TTPCnsConfStatus m_tCnsConfStatus;

    TTPCnMediaTransPort m_tVideoTranAddr;
    TTPCnMediaTransPort m_tAudioTranAddr;
    u16              m_nVideoNode;
    u16              m_nAudioNode;
	u8               m_bySpeakSeat; //发言坐席ID
	u8	             m_byInputVol;	//输入声音
	u8				 m_byOutputVol;	//输出声音
	BOOL32			 m_bMute;	    //是否哑音		
	BOOL32			 m_bQuite;      //是否静音
    BOOL32           m_bPoll;       //是否开启轮询
    BOOL32           m_bDual;
    BOOL32           m_bRecvDual;
	vector<TScreenInfo>  m_vctScreenInfo;
	vector<TTPNMServerCfg> m_vecTTPNMServerCfg;		//网管服务器信息
    BOOL32           m_bLocalPIP;	//是否开启画中画
};

#endif // !defined(AFX_CNCCONFCTRL_H__2EF9234D_820A_40F3_9DC4_967387311945__INCLUDED_)
