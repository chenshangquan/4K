/*****************************************************************************
模块名      : CMS控制台
文件名      : umsconfigctrl.h
相关文件    : 
文件实现功能: ums的配置
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/25  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_UMSCONFIGCTRL_H__F54D1163_86D6_4D90_BDB4_104A0673B42A__INCLUDED_)
#define AFX_UMSCONFIGCTRL_H__F54D1163_86D6_4D90_BDB4_104A0673B42A__INCLUDED_
#include "umsConfigCtrlIF.h"
#include "umssession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsConfigCtrl:public CUmsConfigCtrlIF  
{ 

/** @defgroup  ums配置实现部分
 *  @{
 */

	friend class CUmsSession;
private:
	CUmsConfigCtrl( const CUmsConfigCtrl &){};
    CUmsConfigCtrl( CUmsSession &cUmsSession );

public:
    ~CUmsConfigCtrl();
	/**	 
	* 功能:  sip注册	 
	* @param [in]  tSipCfg sip服务器配置
	* @return u16 成功返回0;失败返回非0错误码 
	* @remarks	 消息：cms->ums    ev_umsreg_cmd \n
	*                   应回复：uｍs ->cms  ev_umsRegResult_notify  
	*/ 
	virtual u16 RegSipService( const TTPSipRegistrarCfg &tSipCfg )    ;


  
	/**	 
	* 功能:  注销sip 	 
	* @param [in]  tSipCfg sip服务器配置
	* @return u16 成功返回0;失败返回非0错误码	 
	* @remarks	 
	*/ 
	virtual u16 UnRegSipService( const TTPSipRegistrarCfg &tSipCfg )  ;


 
	/** 
	* 功能:  获取sip配置	 
	* @param [out]  tSipCfg sip服务器配置
	* @return u16 成功返回0;失败返回非0错误码
	* @remarks	 
	*/ 
	virtual u16 GetSipCfg( TTPSipRegistrarCfg &tSipCfg ) ;


    /* 功能:  获取IP配置	 
        * @param [out]   
        * @return u16 成功返回0;失败返回非0错误码
        * @remarks	 
        */ 
	virtual u16 GetEthnetCfg( TTPEthnetInfo &tEthnetCfg ) ;

	    /* 功能:  获取GK配置	 
        * @param [out]   
        * @return u16 成功返回0;失败返回非0错误码
        * @remarks	 
        */ 
	virtual u16 GetGkCfg( TTPGKCfg &tGKRegCfg ) ;

	/* 功能:  获取Sip注册结果
    * @param
    * @return BOOL 成功返回TRUE;失败返回FALSE
    * @remarks	 
    */ 
	virtual BOOL GetSipRegRsp();

	/* 功能:  获取GK注册结果
    * @param
    * @return BOOL 成功返回TRUE;失败返回FALSE
    * @remarks	 
    */
	virtual BOOL GetGKRegRsp();

	/** 
	* 功能  UI得到系统时间接口
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsSystime(TTPTime& pTTime);

    
/** 
	* 功能:  设置IP	 
	* @param [out]  cfg ：ip信息
	* @return u16 成功返回0;失败返回非0错误码
	* @remarks	如果 
	*/ 
	virtual u16  UpdateEthnetCfg( const TTPEthnetInfo& cfg );


    /**
    * 功能:	 	        发送ums重启请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  RebootReq();

protected:

     /**
    * 功能:	  
    * @param [out]  cMsg 消息
    * @return  无
    * @remarks   
    */
    void  OnUmsIPNotify(const CMessage& cMsg);



	/** 
	* 功能:  注册sip服务器的回复 
	* @param [in] cMsg:消息内容
	* @return  无	 
	* @remarks	 
	*/
   void OnRegSigServRsp( const CMessage& cMsg );


 
   /** 
	* 功能:  注册sip服务器的通知 
	* @param [in] cMsg:消息内容
	* @return  无
	* @remarks  消息 UMS->CMS: ev_umsreg_notify
	*/
   void OnRegSigServNotify( const CMessage& cMsg );

   void OnLinkBreak( const CMessage& cMsg );
    
   

	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent);


   	     /**
    * 功能:	 gk 注册请求
    * @param [int]  TTPGKCfg：
    * @return    
    * @remarks  成功返回0，失败返回错误码
    */
	virtual u16 GkRegReq( const TTPGKCfg & tGkwInfo ); 

	    /**
    * 功能:	  注册gk 服务器的信息 响应ev_umsGKReg_notify
    * @param [out]  cMsg 消息
    * @return  无
    * @remarks   set TTPGKCfg Info
    */
    virtual void  OnGkRegNotify(const CMessage& cMsg);

	    /**
    * 功能:	  得到 服务器发回的gk注册回应
    * @param [out]  cMsg 消息
    * @return  无
    * @remarks   TUCSipRegResult
    */
    virtual void  OnGkRegRsp(const CMessage& cMsg);


	    /**
    * 功能:	  注册sip 服务器结果    for维护工具   用于注册 如注册读IP 未注册 BOOL为FALSE     
    * @param [out]  cMsg 消息
    * @return  无
    * @remarks   set TTPGKCfg Info
    */
    virtual void  OnSipRegResultNotify(const CMessage& cMsg);

	    /**
    * 功能:	  注册gk 服务器结果    for维护工具   用于注册 如注册读IP 未注册 BOOL为FALSE     
    * @param [out]  cMsg 消息
    * @return  无
    * @remarks   set TTPGKCfg Info
    */
    virtual void  OnGkRegResultNotify(const CMessage& cMsg);

		/**
    * 功能:	  UMS系统时间设置
    * @param [out]  cMsg 消息
    * @return  无
    * @remarks   
    */
	virtual u16 OnSysTimeSetReq(const TTPTime& time);

		/** 
	* 功能  获取Cns注册信息
	* @param [in]  
	* @return  
	*/
	//virtual const vector<TTPAlias>& GetCnsRegInfo() const;

	/** 
	* 功能  获取Ums注册信息
	* @param [in]  
	* @return  
	*/
	//virtual const vector<TTPAlias>& GetUmsRegInfo() const;

		/** 
	* 功能  获取所有注册信息
	* @param [in]  
	* @return  
	*/
	//virtual const vector<TTPAlias>& GetAllRegInfo() const;

	/** 
	* 功能  获取所有注册信息
	* @param [in]  
	* @return  
	*/
	virtual const vector<TAliasEx>& GetAllTAliasEx() const;

	/** 
	* 功能  请求SIP注册信息
	* @param [in]  
	* @return  
	* @remarks 
	*/
	virtual u16 ReqSipRegInfo( EmGetRegInfoType emType );

	//消息处理
	//void OnRegInfoRsp(const CMessage& cMsg);

	//B2版本UMS注册信息
	void OnRegInfoUmsRspEx(const CMessage& cMsg);
	//B2版本CNS注册信息
	void OnRegInfoCnsRspEx(const CMessage& cMsg);
	//B2版本MT注册信息
	void OnRegInfoMtRspEx(const CMessage& cMsg);
	//B2版本MCU注册信息
	void OnRegInfoMcuRspEx(const CMessage& cMsg);
	
	
	/**
    * 功能:	  得到UMS系统时间
    * @param [out]  cMsg 消息
    * @return  无
    * @remarks   
    */
	void OnGetSystimeRsp(const CMessage& cMsg);

private:
	void  BuildEventsMap();
	TAliasEx* FindTAliasEx( TAliasEx tCMSAlias );

private:
	CUmsSession *m_pUmsSession;     
	TTPSipRegistrarCfg m_tSipRegCfg; ///< sip服务器配置
    TTPEthnetInfo   m_tEthnet;
	TTPGKCfg m_tGKRegCfg;
	TTPTime			m_tTime;
	BOOL     m_bIsSipRegistered;   //Sip注册结果
	BOOL     m_bIsGKRegistered;    //Gk注册结果

// 	vector<TTPAlias>  m_vctCnsRegInfo;
// 	vector<TTPAlias>  m_vctUmsRegInfo;
// 	vector<TTPAlias>  m_vctAllRegInfo;


	vector<TAliasEx> m_vecAllTAliasEx;

/** @}*/ 
};

#endif // !defined(AFX_UMSCONFIGCTRL_H__F54D1163_86D6_4D90_BDB4_104A0673B42A__INCLUDED_)
