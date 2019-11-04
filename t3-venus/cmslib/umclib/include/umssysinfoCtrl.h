/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umssysinfoCtrl.h
相关文件    : 
文件实现功能: ums系统信息的所有操作
作者        : 刘德印
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/11/23  1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_SYSINFOCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_SYSINFOCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "umssysinfoCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsSysInfoCtrl :public CUmsSysInfoCtrlIF 
{  

/** @defgroup  操作ums系统信息实现部分
 *  @{
 */


	friend class CUmsSession;
private:
	CUmsSysInfoCtrl( const CUmsSysInfoCtrl &){};
    CUmsSysInfoCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsSysInfoCtrl();

	/**
    * 功能:	 获取ums版本信息数据
	* @param [out]  tUmsVer	 ums版本
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsVerData( TUmsVersion& tUmsVer) const;

	/**
    * 功能:	 获取ums CPU、内存等信息数据
	* @param [out]  tUmsSysInfo	 ums cpu、内存信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsSysInfoData( TToolSysInfo& tUmsSysInfo) const;

	
    /**
    * 功能:	 	        刷新ums系统信息请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  RefreshUmsSysInfoReq();
	
    /**
    * 功能:	 	        获取ums会议数目
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  ConfCountReq();

	/**
    * 功能:	 获取ums会议数目
	* @param [out]  body	u32   数目 
	* @return  会议数目
	* @remarks 
	*/
	virtual u32  GetConfCountData(){ return m_nConfCount;};


    /**
    * 功能:	 	        发送授权数目请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  AuthCountReq();

	/**
    * 功能:	 获取ums授权数目
	* @param [out]  body	u32   数目 
	* @return  会议数目
	* @remarks 
	*/
	virtual std::pair<int,int>  GetAuthCountData(){ return m_nAuthCount;};

    /**
    * 功能:	 	        发送电视墙占用情况请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwUsedCountReq();

		/**
    * 功能:	 获取电视墙占用情况信息数据
	* @param [out]  TTPBrdUsedInfo	电视墙板占用信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsTvwUsedData( TTPBrdUsedInfo& tTvwUsed) const;


protected:
 
  /**
    * 功能:	  
	* @param [out]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  OnRefreshUmsVerNotify(const CMessage& cMsg);

  /**
    * 功能:	  刷新ums CPU、内存基本信息通知
	* @param [out]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  OnRefreshUmsSysInfoNotify(const CMessage& cMsg);

  /**
    * 功能:	  刷新ums CPU、内存基本信息通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnConfCountNotify(const CMessage& cMsg);
	
  /**
    * 功能:	  授权数目通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnAuthCountNotify(const CMessage& cMsg);

  /**
    * 功能:	  电视墙使用情况通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnTvwUsedNotify(const CMessage& cMsg);



	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent); 
   

    void  OnLinkBreak(const CMessage& cMsg);
private:
 
	/**
    * 功能:	  注册消息响应函数
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  BuildEventsMap();

private:
	CUmsSession *m_pUmsSession; 
	
	TUmsVersion m_tUmsVer;				//ums版本信息
	TToolSysInfo m_tUmsSysInfo;			//ums CPU、内存信息
	u32 m_nConfCount;
	std::pair<int,int> m_nAuthCount;    //数目和总数
	TTPBrdUsedInfo m_tTvwUsed;          //电视墙占用情况
 
/** @}*/ // 操作ums系统信息接口实现部分
};

#endif // !defined(AFX_SYSINFOCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
