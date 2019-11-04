/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umsNetMngCtrl.h
相关文件    : 
文件实现功能: ums网管的所有操作
作者        : 石城
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2013/1/8    1.0         石城         创建
******************************************************************************/
#if !defined(AFX_NETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_NETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "umsNetMngCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsNetMngCtrl :public CUmsNetMngCtrlIF
{  

/** @defgroup  操作单板接口实现部分
 *  @{
 */
	friend class CUmsSession;
private:
	CUmsNetMngCtrl( const CUmsNetMngCtrl &){};
    CUmsNetMngCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsNetMngCtrl();
	
	/**
    * 功能:	 	        发送添加网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtAddNMServerCmd
	*/
	virtual u16  NetMngAddReq( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送修改网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtDelNMServerCmd
	*/
	virtual u16  NetMngModifyReq( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送删除网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtModifyNMServerCmd
	*/
	virtual u16  NetMngDeleteReq( const TTPNMServerCfg& tTPNMServerCfg );

	/** 
	* 功能  获取网管信息
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg );


protected:
 
	/**
    * 功能:	  添加网管通知
	* @param [out]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  OnAddNetMngRsp(const CMessage& cMsg);
 
	/**
    * 功能:	  删除网管通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnDelNetMngRsp(const CMessage& cMsg);

	/**
    * 功能:	  修改网管通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnModifyNetMngRsp(const CMessage& cMsg);

	/**
    * 功能:	  网管信息通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnNetMngNty(const CMessage& cMsg);

	/**
    * 功能:	  断链通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnLinkBreak(const CMessage& cMsg);

	/**
    * 功能:	 超时通知
	* @param [in]  u16 wEvent
	* @return  无
	* @remarks   
	*/
	virtual void OnTimeOut(u16 wEvent);

	virtual void DispEvent(const CMessage &cMsg);
   	


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

	vector<TTPNMServerCfg> m_vecTTPNMServerCfg;		//网管服务器信息

/** @}*/ // 操作ums单板信息接口实现部分
};

#endif // !defined(AFX_NETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
