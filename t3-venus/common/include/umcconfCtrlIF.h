/*****************************************************************************
模块名      : CMS控制台
文件名      : confTemplateCtrlIF.h
相关文件    : 
文件实现功能: 会议相关的所有操作
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/25  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_UMCCONFCTRLIF_H__10B44268_D175_431C_ACCA_A0A559086730__INCLUDED_)
#define AFX_UMCCONFCTRLIF_H__10B44268_D175_431C_ACCA_A0A559086730__INCLUDED_
#include "kdvdispevent.h"
#include "cmsstruct.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmcConfCtrlIF:public  CKdvDispEvent   
{

public:
 
/** @defgroup  会议控制部分接口
 *  @{
 */



  /**
    * 功能:	获取会议列表
	* @param [out]  tplConfList	 会议列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16 GetConf(  TCMSConf &tplConf  ) const = 0;
  
   
  /**
    * 功能:	获取会议中cns列表
	* @param [int]  tplConfList	 会议列表
    * @param [out]  tplConfList	 CNS列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
   virtual u16 GetConfCnsList(  TplArray<TCnsInfo> &tplConfCnsList ) const  = 0 ;

   
  /**
    * 功能:	获取会议混音列表
	* @param [int]  wConfID:会议ID  
    * @param [out]  tplConfAudmixList	 混音列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
   virtual u16 GetConfAudmixList( TAuxMixList&tConfAudmixList ) const = 0 ;

  
    /**
    * 功能:	获取会议轮询列表
	* @param [int]  wConfID:会议ID  
    * @param [out]  tplConfPollList	 轮询列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
   virtual u16 GetConfPollList(  TplArray<u16> &tplConfPollList ) const = 0;

 
 
	 
	 

 
   /**
    * 功能:	邀请某cns会场加入某会议
	* @param [int]  tEp	 会议和会场信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16 InviteCnsReq( const TConfCallEpAddr &tEp )  = 0;

  

    /**
    * 功能:	呼叫会议中已经存在的cns会场加入某会议
	* @param [int]  tEp	 会议和会场信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 消息：cms->ums  evtp_CallEP_cmd  \n
                       应回复：ums->cms evtp_CallEP_result   \n
	                   若成功，还应发：ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
	virtual u16 CallConfCnsReq( const TConfEpID &tEp ) = 0;



  
   /**
    * 功能:	挂断会议
	* @param [int]  wConfID 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16 HangupConfReq( ) = 0;


 
  /**
    * 功能:	挂断某会场
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 会议列表中依然存在该会场，只是不在线
	*/
	virtual u16 HangupCNSReq( const TConfEpID &tConfEpInfo ) = 0;


 
  /**
    * 功能:	从会议中移除某会场
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 会议列表中不存在该会场
	*/
	virtual u16 RemoveCNSReq( const TConfEpID &tConfEpInfo )  = 0;


 
	/**
    * 功能:	设置发言会场
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetSpokeCnsReq( const TConfEpID &tConfEpInfo )    = 0;


    /**
    * 功能:	设置远程cns静音
	* @param [int]  wConfID	 会议ID
    * @param [int]  bQuiet  TRUE:开启静音，FALSE：停止静音
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetQuietCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bQuiet)    = 0;


    /**
    * 功能:	设置远程cns哑音
	* @param [int]  wConfID	 会议ID
    * @param [int]  bMute  TRUE:开启哑音，FALSE：停止哑音
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetMuteCnsReq( const TConfEpID &tConfEpInfo , BOOL32 bMute)    = 0;




     /**
    * 功能:	设置远程cns发起双流
	* @param [int]  wConfID	 会议ID
    * @param [int]  bStart  TRUE:开启双流，FALSE：停止双流
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetDualCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bStart )    = 0; 


 
	/**
    * 功能:	更新混音列表请求
	* @param [int]  tMixInfo	 混音列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 UpdateAudMixListReq( const TConfAuxMixInfo &tMixInfoList ) = 0;

	/**
    * 功能:	操作混音列表请求
	* @param [int]  tDisListOpr	 一个混音列表操作
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 AudMixDisListOprCmd( const TDiscussListOpr &tDisListOpr ) = 0;

 
  /**
    * 功能:	更新轮询列表请求
	* @param [int]  tTurnInfoList	 轮询列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 UpdatePollListReq( const TConfTurnInfo &tTurnInfoList ) = 0;


	
 
  /**
    * 功能:	开启混音
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StartAuxMixReq( const u16 wConfID ) = 0;
 
  /**
    * 功能:	停止混音
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StopAuxMixReq( const u16 wConfID ) = 0;

 
  /**
    * 功能:	开启轮询
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StartPollReq( const u16 wConfID ) = 0;


  
  /**
    * 功能:	停止轮询 
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StopPollReq( const u16 wConfID ) = 0;

 
   
/** @}*/  //会议控制部分接口

};

#endif // !defined(AFX_CONFCTRLIF_H__10B44268_D175_431C_ACCA_A0A559086730__INCLUDED_)
