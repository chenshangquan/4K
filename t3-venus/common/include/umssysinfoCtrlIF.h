/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umssysinfoCtrlIF.h
相关文件    : 
文件实现功能: ums系统信息的所有操作
作者        : 刘德印
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/11/23  1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_SYSINFOCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
#define AFX_SYSINFOCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_
#include "kdvdispevent.h"
#include "ummessagestruct.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsSysInfoCtrlIF :public  CKdvDispEvent  
{
public:

	/**
    * 功能:	 获取ums版本信息数据
	* @param [out]  tUmsVer	 ums版本
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsVerData( TUmsVersion& tUmsVer) const = 0;

	/**
    * 功能:	 获取ums CPU、内存等信息数据
	* @param [out]  tUmsSysInfo	 ums cpu、内存信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsSysInfoData( TToolSysInfo& tUmsSysInfo) const = 0;


	
    /**
    * 功能:	 	        刷新ums系统信息请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  RefreshUmsSysInfoReq() = 0;
	
    /**
    * 功能:	 	        获取ums会议数目
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  ConfCountReq() = 0;

	/**
    * 功能:	 获取ums会议数目
	* @param [out]  body	u32   数目 
	* @return  会议数目
	* @remarks 
	*/
	virtual u32  GetConfCountData() = 0;

    /**
    * 功能:	 	        发送授权数目请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  AuthCountReq() = 0;

	/**
    * 功能:	 获取ums授权数目
	* @param [out]  body	u32   数目 
	* @return  会议数目
	* @remarks 
	*/
	virtual std::pair<int,int>  GetAuthCountData() = 0;


    /**
    * 功能:	 	        发送电视墙占用情况请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwUsedCountReq() = 0;

		/**
    * 功能:	 获取电视墙占用情况信息数据
	* @param [out]  TTPBrdUsedInfo	电视墙板占用信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsTvwUsedData( TTPBrdUsedInfo& tTvwUsed) const = 0;

 /** @}*/ // 操作ums系统信息接口

};

#endif // !defined(AFX_SYSINFOCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
