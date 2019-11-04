/*****************************************************************************
模块名      : CMS控制台
文件名      : confCtrl.h
相关文件    : 
文件实现功能: 会议相关的所有操作
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2011/4/25  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_)
#define AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_
#include "cnsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmcConfCtrl : public CUmcConfCtrlIF  
{

/** @defgroup  会议控制实现部分
 *   @{
 */
public:
 	friend class CCncSession; 
 
	CUmcConfCtrl( CCnsSession &cCnsSession );
	CUmcConfCtrl( const CUmcConfCtrl &){};
    

public:
  /**
    * 功能:	获取会议列表
	* @param [out]  tplConfList	 会议列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16 GetConf(  TCMSConf &tplConfList ) const ; 

  /**
    * 功能:	获取会议中cns列表
	* @param [int]  tplConfList	 会议列表
    * @param [out]  tplConfList	 CNS列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
   virtual u16 GetConfCnsList(  TplArray<TCnsInfo> &tplConfCnsList ) const ;

    /**
    * 功能:	获取会议混音列表
	* @param [int]  wConfID:会议ID  
    * @param [out]  tConfAudmixList	 混音列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
   virtual u16 GetConfAudmixList( TAuxMixList&tConfAudmixList ) const ;

  /**
    * 功能:	获取会议轮询列表
	* @param [int]  wConfID:会议ID  
    * @param [out]  tplConfPollList	 轮询列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
   virtual u16 GetConfPollList(  TplArray<u16> &tplConfPollList ) const ;


 
   
	 
  /**
    * 功能:	邀请某cns会场加入某会议
	* @param [int]  tEp	 会议和会场信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 消息：cms->ums  evtp_CallEP_cmd  \n
                       应回复：ums->cms evtp_CallEP_result   \n
	                   若成功，还应发：ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
	virtual u16 InviteCnsReq( const TConfCallEpAddr &tEp );




    /**
    * 功能:	呼叫会议中已经存在的cns会场加入某会议
	* @param [int]  tEp	 会议和会场信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 消息：cms->ums  evtp_CallEP_cmd  \n
                       应回复：ums->cms evtp_CallEP_result   \n
	                   若成功，还应发：ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
	virtual u16 CallConfCnsReq( const TConfEpID &tEp );
   



  /**
    * 功能:	挂断会议
	* @param [int]  wConfID 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16 HangupConfReq( );



   /**
    * 功能:	挂断某会场
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 会议列表中依然存在该会场，只是不在线
	*/
	virtual u16 HangupCNSReq( const TConfEpID &tConfEpInfo );


	/**
    * 功能:	从会议中移除某会场
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 会议列表中不存在该会场
	*/
	virtual u16 RemoveCNSReq( const TConfEpID &tConfEpInfo ) ;



  	/**
    * 功能:	设置发言会场
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetSpokeCnsReq( const TConfEpID &tConfEpInfo ) ;

   
    /**
    * 功能:	设置远程cns静音
	* @param [int]  wConfID	 会议ID
    * @param [int]  bQuiet  TRUE:开启静音，FALSE：停止静音
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetQuietCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bQuiet) ;


    /**
    * 功能:	设置远程cns哑音
	* @param [int]  wConfID	 会议ID
    * @param [int]  bMute  TRUE:开启哑音，FALSE：停止哑音
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetMuteCnsReq( const TConfEpID &tConfEpInfo , BOOL32 bMute) ;



     /**
    * 功能:	设置远程cns发起双流
	* @param [int]  wConfID	 会议ID
    * @param [int]  bStart  TRUE:开启双流，FALSE：停止双流
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetDualCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bStart ) ;


	/**
    * 功能:	更新混音列表请求
	* @param [int]  tMixInfo	 混音列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 UpdateAudMixListReq( const TConfAuxMixInfo &tMixInfoList );


	/**
    * 功能:	操作混音列表请求
	* @param [int]  tDisListOpr	 一个混音列表操作
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 AudMixDisListOprCmd( const TDiscussListOpr &tDisListOpr );
  /**
    * 功能:	更新轮询列表请求
	* @param [int]  tTurnInfoList	 轮询列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 UpdatePollListReq( const TConfTurnInfo &tTurnInfoList );


	
  /**
    * 功能:	开启混音
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StartAuxMixReq( const u16 wConfID );

 /**
    * 功能:	停止混音
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StopAuxMixReq( const u16 wConfID );


   /**
    * 功能:	开启轮询
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StartPollReq( const u16 wConfID );


  /**
    * 功能:	停止轮询 
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StopPollReq( const u16 wConfID );

    
 
 
protected: 

    void OnChairCnsNotify( const CMessage& cMsg );
	void OnConfStateNty( const CMessage& cMsg );

	void OnHungUpConfRsp( const CMessage& cMsg ); 
	void OnInviteCnsRsp( const CMessage& cMsg ); 
    void OnCallConfCnsRsp( const CMessage& cMsg ); 
    void OnHangupCnsInd( const CMessage& cMsg );
	void OnUpdateConfCnsListNotify( const CMessage& cMsg ); 
	void OnUpdateConfAuxMixlistNotify( const CMessage& cMsg ); 
	void OnUpdateConfAuxMixlistInd( const CMessage& cMsg ); 
	void OnUpdateConfPolllistNotify( const CMessage& cMsg ); 
    void OnUpdateConfSpeakerNotify( const CMessage& cMsg ); 
	void OnAudMixDisListOprNotify( const CMessage& cMsg );
   
	void OnSetSpokeCnsRsp( const CMessage& cMsg ); 
    void OnSetMuteCnsRsp( const CMessage& cMsg ); 
    void OnSetSilenceCnsRsp( const CMessage& cMsg ); 
    void OnSetDualCnsRsp( const CMessage& cMsg ); 
    void OnDualCnsNotify( const CMessage& cMsg ); 
    
	void OnCnsLeaveNotify( const CMessage& cMsg ); 

    void OnUmsCommonReasonInd( const CMessage& cMsg ); 

    void OnLinkBreak( const CMessage& cMsg ); 

	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent);
    
private:
	 void  BuildEventsMap();
  
	 
private:
    CCnsSession *m_pCncSession;
	TCMSConf     m_tConfInfo; 

/** @}*/ //会议控制实现部分
};

#endif // !defined(AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_)
