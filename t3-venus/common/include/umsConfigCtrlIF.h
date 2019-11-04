/*****************************************************************************
模块名      : CMS控制台
文件名      : umsconfigctrlIF.h
相关文件    : 
文件实现功能: ums的配置
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/25  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_UMSCONFIGCTRLIF_H__DD124CB2_4C14_4570_A2F4_F6411FA98B52__INCLUDED_)
#define AFX_UMSCONFIGCTRLIF_H__DD124CB2_4C14_4570_A2F4_F6411FA98B52__INCLUDED_
#include "kdvdispevent.h"
#include "eventoutumsreg.h"
#include "cmsstruct.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsConfigCtrlIF:public  CKdvDispEvent   
{
public:

/** @defgroup  ums配置部分接口
 *  @{
*/

 /*功  能	sip注册
	参  数	 
	返回值	成功返回0,失败返回非0错误码
	说  明	 */
	virtual u16 RegSipService( const TTPSipRegistrarCfg &tSipCfg )   = 0;


 /*功  能	注销sip 
	参  数	 
	返回值	成功返回0,失败返回非0错误码
	说  明	 */
	virtual u16 UnRegSipService( const TTPSipRegistrarCfg &tSipCfg )   = 0;


 /*功  能	获取sip配置
	参  数	 
	返回值	成功返回0,失败返回非0错误码
	说  明	 */
	virtual u16 GetSipCfg( TTPSipRegistrarCfg &tSipCfg )   = 0;

    /* 功能:  获取IP配置	 
        * @param [out]   
        * @return u16 成功返回0;失败返回非0错误码
        * @remarks	 
        */ 
	virtual u16 GetEthnetCfg( TTPEthnetInfo &tEthnetCfg ) = 0 ;

	/** 
	* 功能:  设置IP	 
	* @param [out]  cfg ：ip信息
	* @return u16 成功返回0;失败返回非0错误码
	* @remarks	 
	*/ 
	virtual u16  UpdateEthnetCfg( const TTPEthnetInfo& cfg ) = 0;


			     /**
    * 功能:	 gk 注册请求
    * @param [int]  tTvwInfo：请求播放的电视墙信息
    * @return    
    * @remarks  成功返回0，失败返回错误码
    */
	virtual u16 GkRegReq( const TTPGKCfg & tGkwInfo ) = 0; 

		    /* 功能:  获取GK配置	 
        * @param [out]   
        * @return u16 成功返回0;失败返回非0错误码
        * @remarks	 
        */ 
	virtual u16 GetGkCfg( TTPGKCfg &tGKRegCfg ) = 0;

			/**
    * 功能:	  UMS系统时间设置
    * @param [out]  cMsg 消息
    * @return  无
    * @remarks   
    */
	virtual u16 OnSysTimeSetReq(const TTPTime& time) = 0;

		/** 
	* 功能  UI得到系统时间接口
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsSystime(TTPTime& pTTime) = 0;

		/** 
	* 功能  请求SIP注册信息
	* @param [in]  emType 注册类型
	* @return  
	* @remarks 
	*/
	virtual u16 ReqSipRegInfo( EmGetRegInfoType emType ) = 0;

	    /**
    * 功能:	 	        发送ums重启请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  RebootReq() = 0;

	/** 
	* 功能  获取Cns注册信息
	* @return  vector<TTPAlias>  Cns注册信息
	* @remarks 
	*/
	//virtual const vector<TTPAlias>& GetCnsRegInfo() const = 0;

	/** 
	* 功能  获取Ums注册信息
	* @return  vector<TTPAlias>  Ums注册信息
	* @remarks
	*/
	//virtual const vector<TTPAlias>& GetUmsRegInfo() const = 0;

			/** 
	* 功能  获取所有注册信息
	* @param [in]  
	* @return  
	*/
	//virtual const vector<TTPAlias>& GetAllRegInfo() const = 0;

	/** 
	* 功能  获取所有注册信息
	* @param [in]  
	* @return  
	*/
	virtual const vector<TAliasEx>& GetAllTAliasEx() const = 0;

	/* 功能:  获取Sip注册结果
    * @param
    * @return BOOL 成功返回TRUE;失败返回FALSE
    * @remarks	 
    */ 
	virtual BOOL GetSipRegRsp() = 0;

	/* 功能:  获取GK注册结果
    * @param
    * @return BOOL 成功返回TRUE;失败返回FALSE
    * @remarks	 
    */
	virtual BOOL GetGKRegRsp() = 0;


/** @}*/ 
};

#endif // !defined(AFX_UMSCONFIGCTRLIF_H__DD124CB2_4C14_4570_A2F4_F6411FA98B52__INCLUDED_)
