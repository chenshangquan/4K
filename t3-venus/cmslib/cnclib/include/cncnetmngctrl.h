/*****************************************************************************
模块名      : cnclib接口
文件名      : cncnetmngctrl.h
相关文件    : 
文件实现功能: cns网管配置
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2013/1/17   1.0         石城         创建
******************************************************************************/
#if !defined(AFX_CNCNETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_CNCNETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "cncnetmngctrlif.h"
#include "cnsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCncNetMngCtrl :public CCncNetMngCtrlIF
{
public:
	CCncNetMngCtrl(CCnsSession &cSession);
	virtual ~CCncNetMngCtrl();
	
	/**
    * 功能:	 	        发送添加网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtAddNMServerCmd
	*/
	virtual u16  NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送修改网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtDelNMServerCmd
	*/
	virtual u16  NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送删除网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtModifyNMServerCmd
	*/
	virtual u16  NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg );

	/** 
	* 功能  获取网管信息
	* @param [in]  
	* @return  
	*/
	virtual void GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )const;


protected:
 
	/**
    * 功能:	  添加网管通知
	* @param [out]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  OnAddNetMngInd(const CMessage& cMsg);
 
	/**
    * 功能:	  删除网管通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnDelNetMngInd(const CMessage& cMsg);

	/**
    * 功能:	  修改网管通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnModifyNetMngInd(const CMessage& cMsg);

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
	CCnsSession				*m_pSession;

	vector<TTPNMServerCfg>	m_vecTTPNMServerCfg;		//网管服务器信息
};

#endif // !defined(AFX_CNCNETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
